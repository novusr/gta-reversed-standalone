# Standalone Build Analysis: GTA Reversed

This document investigates the standalone build options, entry points, configuration flags, and actual runtime execution path of `gta-reversed`.

---

## 1. Build System Standalone Flags & Options

### 1.1 Conan Configuration (`conanfile.py:30-32`)
In `conanfile.py`:
```python
options = {
    ...
    # Standalone build mode
    "standalone": [False, 'dump_hooks_only'], # There's no `True` yet, as we can't build a fully standalone version yet
}

default_options = {
    ...
    "standalone": False,
}
```
> [!IMPORTANT]
> The repository maintainers explicitly state in code: **`There's no True yet, as we can't build a fully standalone version yet`**. The only allowed values for `standalone` in Conan are `False` or `'dump_hooks_only'`.

In `conanfile.py:67-68`:
```python
tc.cache_variables["GTASA_STANDALONE_DUMP_HOOKS_ONLY"] = self.options.standalone == 'dump_hooks_only'
tc.cache_variables["GTASA_STANDALONE"] = str(self.options.standalone) != 'False'
```

### 1.2 CMake Configuration (`source/CMakeLists.txt:10-24, 88-116`)
```cmake
option(${RE_PROJECT}_STANDALONE "Build standalone executable" OFF)
option(${RE_PROJECT}_STANDALONE_DUMP_HOOKS_ONLY "Dump hooks only" OFF)

if (${RE_PROJECT}_STANDALONE)
    add_compile_definitions(NOTSA_STANDALONE)
endif()

if (${RE_PROJECT}_STANDALONE_DUMP_HOOKS_ONLY)
    if (NOT ${RE_PROJECT}_STANDALONE)
        message(FATAL_ERROR "${RE_PROJECT}_STANDALONE_DUMP_HOOKS_ONLY requires ${RE_PROJECT}_STANDALONE=ON")
    endif()
    add_compile_definitions(NOTSA_STANDALONE_DUMP_HOOKS_ONLY)
endif()

if (${RE_PROJECT}_STANDALONE)
    add_executable(${RE_PROJECT_LIB_NAME} WIN32)
    set(TARGET_SUFFIX ".exe")
else()
    add_library(${RE_PROJECT_LIB_NAME} MODULE)
    set(TARGET_SUFFIX ".asi")
endif()
```
When `GTASA_STANDALONE=ON`, CMake produces `bin/<Config>/gta_reversed.exe` instead of `gta_reversed.asi`.

---

## 2. Standalone Entry Point & Execution Path

The entry point for the standalone executable target is located in `source/app/platform/win/WinMain.cpp:533-567`:

```cpp
#ifdef NOTSA_STANDALONE
INT WINAPI WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR cmdLine, INT nCmdShow) {
    CommandLine::Load(__argc, __argv);
    if (CommandLine::s_WaitForDebugger) {
        notsa::debug::WaitForDebugger();
    }

    notsa::debug::DisplayConsole();
    notsa::debug::LoadSymbols();
    notsa::Logging::CreateInstance();
    notsa::ScopeGuard cleanupLogging{ [] {
        notsa::Logging::DestroyInstance();
        notsa::debug::UnloadSymbols();
    } };

#ifdef NOTSA_STANDALONE_DUMP_HOOKS_ONLY
    ReversibleHooks::RHManager::CreateInstance();
    notsa::ScopeGuard cleanupRH{ [] {
        ReversibleHooks::RHManager::DestroyInstance();
    }};

    NOTSA_LOG_INFO("Dumping hooks only, no memory writing will be performed");

    InjectHooksMain(); // This will also end up calling the CLI to dump the hooks

    return 0;
#else
    notsa::ui::UIRenderer::CreateInstance();
    // code..
    notsa::ui::UIRenderer::CreateInstance();
    NOTSA_LOG_ERR("This executable is meant to be used for dumping hooks only, see `NOTSA_STANDALONE_DUMP_HOOKS_ONLY` option");
    return 1;
#endif
}
#endif
```

---

## 3. Step-by-Step Execution Trace

### Scenario A: Standalone Dump Hooks Mode (`NOTSA_STANDALONE_DUMP_HOOKS_ONLY`)
This is the only mode used in the project today (specifically by GitHub Actions CI in `.github/workflows/update-re-progress.yml:78`):

1. **Process Launch**: `gta_reversed.exe --dump-hooks-to=docs/hooks.json` starts as a native Windows process.
2. **Command Line & Logging Init**:
   * `CommandLine::Load(__argc, __argv)` parses arguments.
   * `notsa::debug::DisplayConsole()` attaches/allocates Windows console.
   * `notsa::Logging::CreateInstance()` initializes spdlog logger.
3. **Hook Manager Instantiation**:
   * `ReversibleHooks::RHManager::CreateInstance()` creates the hook category tree.
4. **Hook Registration**:
   * `InjectHooksMain()` (`source/InjectHooksMain.cpp:535`) executes.
   * Because `NOTSA_STANDALONE` is defined, game initialization is bypassed (`InjectHooksMain.cpp:544-548`).
   * Every class's `::InjectHooks()` is called (`CDoor::InjectHooks()`, `CGame::InjectHooks()`, `CWorld::InjectHooks()`, etc.).
   * Under `NOTSA_STANDALONE_DUMP_HOOKS_ONLY`, `RHManager::InstallStatic` creates `ReversibleHook::NullHook` instances rather than writing x86 assembly trampolines to memory (`source/reversiblehooks/RHManager.cpp:54`).
   * `StaticRef` dummy storage: `source/Base.h:165-175`:
     ```cpp
     alignas(alignof(T)) static uint8 buf[sizeof(T)]{};
     return *reinterpret_cast<T*>(buf);
     ```
     A single dummy static buffer is returned so static variable accesses during hook registration do not segfault.
5. **JSON Export**:
   * When `--dump-hooks-to` is detected, `RHManager::WriteHooksToFile()` writes the entire hook hierarchy to `docs/hooks.json`.
6. **Process Termination**:
   * `WinMain` returns `0`. The process cleanly exits without executing any game logic.

---

### Scenario B: Attempting to Run Standalone as a Game Engine
If a developer enables `GTASA_STANDALONE=ON` without `GTASA_STANDALONE_DUMP_HOOKS_ONLY`:

```
Process Starts (gta_reversed.exe)
      │
      ▼
WinMain (source/app/platform/win/WinMain.cpp:534)
      │
      ▼
CommandLine & Logging initialized
      │
      ▼
#ifndef NOTSA_STANDALONE_DUMP_HOOKS_ONLY branch
      │
      ▼
Logs Error: "This executable is meant to be used for dumping hooks only, see NOTSA_STANDALONE_DUMP_HOOKS_ONLY option"
      │
      ▼
Returns 1 (Immediate Exit)
```

---

### Scenario C: Hypothetical Path if `NOTSA_WinMain` Were Called Standalone
If someone bypasses the check and redirects the standalone entry point to `NOTSA_WinMain` (`source/app/platform/win/WinMain.cpp:393`):

```
NOTSA_WinMain (source/app/platform/win/WinMain.cpp:393)
      │
      ▼
RsEventHandler(rsINITIALIZE, nullptr) (platform.cpp:291)
      │
      ▼
AppEventHandler(rsINITIALIZE) (app.cpp:110)
      │
      ├─► CGame::InitialiseOnceBeforeRW() (Game.cpp:590)
      │     ├─► CMemoryMgr::Init()
      │     ├─► CLocalisation::Initialise()
      │     ├─► CFileMgr::Initialise()
      │     ├─► CdStreamInit(5)
      │     └─► CPad::Initialise()
      │
      └─► RsInitialize() (platform.cpp:164)
            └─► psInitialize() (WinPs.cpp:129)
                  └─► CRASH 1: Accesses StaticRef<RsGlobalType>(0xC17040)
                      Address 0xC17040 is unmapped in standalone process memory
                      Result: STATUS_ACCESS_VIOLATION (0xC0000005)
```

If `RsGlobal` were somehow allocated in heap:
```
NOTSA_WinMain continues to 0x748847:
RsEventHandler(rsRWINITIALIZE, PSGLOBAL(window)) (platform.cpp:309)
      │
      ▼
RsRwInitialize(param) (platform.cpp:259)
      │
      ├─► RwEngineInit(...) -> rwplcore.cpp:321 -> calls 0x7F3160
      ├─► RwEngineOpen(...) -> rwplcore.cpp:325 -> calls 0x7F2F70
      ├─► RwEngineStart()   -> rwplcore.cpp:329 -> calls 0x7F2E70
      │
      └─► CRASH 2: Direct call to raw address 0x7F2E70
          No executable code mapped at 0x7F2E70 in a standalone process
          Result: STATUS_ACCESS_VIOLATION / Jump to invalid memory
```

If RenderWare calls were stubbed:
```
CGame::Initialise("DATA\\GTA.DAT") (Game.cpp:547)
      │
      ├─► CGame::Init1("DATA\\GTA.DAT") (Game.cpp:337)
      │     ├─► CPools::Initialise() (Pools.cpp:69)
      │     │     └─► CRASH 3: ms_pPedPool = StaticRef<CPedPool*>(0xB74490)
      │     │         Writing pointer to unmapped address 0xB74490
      │     │
      │     ├─► CStreaming::InitImageList() (Streaming.cpp:1886)
      │     │     └─► CRASH 4: ms_aInfoForModel = StaticRef<...>(0x8E4CC0)
      │     │
      │     └─► plugin::Call<0x...>()
      │           └─► CRASH 5: 838 functions jump to unmapped gta_sa.exe code
```

---

## 4. Key Findings & Technical Conclusions

1. **No Standalone Game Loop Exists Today**:
   The standalone target in CMake and Conan was implemented exclusively for **metadata extraction and CI progress reporting**.
2. **Five Cascading Fatal Blockers for Standalone Boot**:
   * **Level 1**: Entry point deliberately halts with return code 1 unless `--dump-hooks-to` is given.
   * **Level 2**: Window/Display initialization reads `RsGlobal` from `0xC17040`.
   * **Level 3**: RenderWare engine boot calls function pointers `0x7F3160`, `0x7F2F70`, `0x7F2E70`.
   * **Level 4**: Object pools and world sectors write pointers directly to GTA data segment addresses (`0xB74490`, `0xB7D0B8`).
   * **Level 5**: Gameplay logic invokes 838 `plugin::Call` functions that don't exist outside `gta_sa.exe`.
3. **Implication for Evolution**:
   To evolve GTA Reversed into a standalone executable, the standalone mode must be repurposed from a "dummy hook dumper" into a real engine bootstrap that binds native memory and a real RenderWare implementation.
