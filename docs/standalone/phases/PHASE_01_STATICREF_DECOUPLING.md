# Phase 1: StaticRef & Storage Decoupling

* **Status**: **IN PROGRESS**
* **Prerequisites**: Phase 0 (Baseline Validation & Architectural Setup).

---

## 1. Objective
Decouple game state and global singletons from hardcoded virtual memory addresses in `gta_sa.exe` so the codebase can compile and allocate runtime state natively, while preserving exact behavior in ASI mode.

---

## 2. Technical Challenge
* In ASI mode, `StaticRef<T>(addr)` resolves to `*reinterpret_cast<T*>(addr)`.
* In standalone mode, addresses like `0xB74490` (`CPedPool*`) are unmapped, causing access violations.
* In the current dummy standalone mode (`NOTSA_STANDALONE_DUMP_HOOKS_ONLY`), `StaticRef` returns a single per-type static buffer (`source/Base.h:171`), which aliases unrelated globals of the same type.
* There are 2,369 declarations across 278+ files.

---

## 3. Implementation Strategy

### 3.1 Non-Aliasing Native Storage Abstraction
Introduce a compile mode `NOTSA_STANDALONE_NATIVE`:
```cpp
#if defined(NOTSA_STANDALONE_NATIVE)
    // Standalone native mode: Provide unique storage per address or symbol
    template<typename T, uintptr Addr>
    struct StaticStorage {
        inline static T s_Value{};
    };

    template<uintptr Addr, typename T>
    T& NativeStaticRef() {
        return StaticStorage<T, Addr>::s_Value;
    }
#elif defined(NOTSA_STANDALONE_DUMP_HOOKS_ONLY)
    // CI hook dumping only
    template<typename T>
    T& StaticRef(uintptr addr) {
        alignas(alignof(T)) static uint8 buf[sizeof(T)]{};
        return *reinterpret_cast<T*>(buf);
    }
#else
    // Vanilla GTA.exe injected ASI mode
    template<typename T>
    T& StaticRef(uintptr addr) {
        return *reinterpret_cast<T*>(addr);
    }
#endif
```

### 3.2 Dual-Mode Variable Definition Pattern
For progressive migration, adopt a macro or template pattern that preserves identical call syntax while resolving to native storage in standalone builds and pointer casts in ASI builds.

### 3.3 Allocator Detachment
In `source/game_sa/MemoryMgr.cpp`:
* In standalone mode, bypass hooking `operator new` and `operator delete` to addresses `0x82119A` and `0x8214BD`.
* Use the host compiler's standard runtime heap.

---

## 4. Key Milestones & Verification
- [ ] Add `GTASA_STANDALONE_NATIVE` build option in CMake and Conan.
- [ ] Update `source/Base.h` with non-aliasing storage for standalone compilation.
- [ ] Decouple CRT allocator hooks in `MemoryMgr.cpp`.
- [ ] Verify that ASI target compiles with zero behavioral changes.
- [ ] Verify that standalone target compiles a subset of core classes with native storage without crashing.
