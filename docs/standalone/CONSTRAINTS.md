# Architectural & Migration Constraints: GTA Reversed

This document defines the strict, non-negotiable architectural constraints and engineering boundaries governing all development on `gta-reversed`.

---

## 1. Core Constraints

### Constraint 1: Preserve GTA Gameplay & Physics Behavior
* **Rule**: Do not casually alter gameplay formulas, task execution behavior, physics formulas, AI perception algorithms, SCM script semantics, or entity lifecycle rules.
* **Rationale**: The core value of `gta-reversed` lies in 5+ years of meticulous reverse-engineering of Rockstar North's actual logic. Altering formulas destroys behavioral authenticity.
* **Implication**: Any bug fix must be explicitly isolated or toggleable via `ReversibleBugFixes` rather than altering the default canonical behavior.

### Constraint 2: Preserve the Established Class Hierarchy (No ECS)
* **Rule**: Retain the monolithic, object-oriented inheritance tree:
  ```text
  CEntity
    └── CPhysical
          ├── CPed
          │     └── CPlayerPed
          └── CVehicle
                ├── CAutomobile
                ├── CBike
                └── ...
  ```
* **Rationale**: The game's 291 AI tasks, 83 event handlers, handling data calculations, and 800+ SCM opcodes assume direct pointer casts across this exact inheritance model.
* **Prohibition**: Do NOT attempt to convert the architecture to an Entity-Component-System (ECS) or generic data-oriented engine.

### Constraint 3: Maintain Dual-Mode Compatibility (Preserve ASI Mode)
* **Rule**: Standalone features and abstractions must not break or remove the injected ASI build (`gta_reversed.asi`).
* **Rationale**: The ASI target running inside the original `gta_sa.exe` is the definitive golden standard for behavioral comparison and regression testing.
* **Implication**: Code must use preprocessor conditionals (`NOTSA_STANDALONE_NATIVE` vs ASI) or clean compile-time abstractions to allow both targets to build and function.

### Constraint 4: Avoid Speculative Rewrites & Modernization for Its Own Sake
* **Rule**: Do not refactor large blocks of working code simply to use newer C++ syntax, smart pointers, or modern design patterns unless strictly necessary for standalone decoupling.
* **Rationale**: Speculative refactoring introduces subtle regressions, alters memory layouts, causes merge conflicts with upstream work, and distracts from standalone milestones.
* **Focus**: The objective is **migration to standalone**, not modernization for style points.

### Constraint 5: Respect Phase Discipline (Do Not Prematurely Solve Future Phases)
* **Rule**: Work within the designated active phase. Do not implement complex subsystems (e.g., full rendering passes, multiplayer networking, advanced shaders) before their prerequisite phases (e.g., storage decoupling, platform abstraction, VFS) are solved and verified.
* **Rationale**: Building future systems on unvalidated or shifting foundational abstractions causes cascading rework.

### Constraint 6: Memory Layout & Binary File Format Preservation
* **Rule**: Data structures that represent binary file formats on disk (`.dff`, `.txd`, `.col`, `.ifp`, `.ipl`, `.ide`, `.dat`, `.scm`, save files) must maintain exact byte offsets, packing, and endian awareness.
* **Rationale**: The standalone engine must consume original, unmodded game assets directly from retail GTA San Andreas installations.

### Constraint 7: Platform Agnosticism in Shared Code
* **Rule**: Game logic and engine subsystems under `source/game_sa/` must remain platform-agnostic.
* **Rule**: Win32 APIs (`HWND`, `HINSTANCE`, `GetTickCount`, `DirectInput8`, `IDirect3DDevice9`) must NOT leak into shared gameplay classes.
* **Resolution**: All OS-specific operations must be delegated to the platform abstraction layer (SDL3 / native standard library).
