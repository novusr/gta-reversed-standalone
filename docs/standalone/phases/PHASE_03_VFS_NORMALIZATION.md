# Phase 3: Filesystem & VFS Normalization

* **Status**: **PLANNED**
* **Prerequisites**: Phase 2 (Platform Abstraction Layer).

---

## 1. Objective
Ensure robust, case-insensitive asset loading across Windows, Linux, and macOS, resolving GTA San Andreas's legacy Windows backslash separators and mixed-case directory structures.

---

## 2. Scope & Key Tasks
1. **Path Normalization**:
   - Update `CFileMgr`: automatically normalize all Windows backslashes (`\`) to standard forward slashes (`/`).
2. **Case-Insensitive VFS Lookup**:
   - Implement a case-insensitive directory cache for POSIX systems (Linux/macOS).
   - When a file query like `DATA/DEFAULT.DAT` is requested, search directory contents case-insensitively and resolve to the true casing on disk (e.g., `data/default.dat`).
3. **Archive Mount Interface**:
   - Ensure `CdStream` archive reader can open `.img` archives (`models/gta3.img`, `models/gta_int.img`) using normalized paths.

---

## 3. Verification Protocol
- [ ] Unit tests for `CFileMgr` path normalization on Windows and Linux.
- [ ] Successfully locate and parse sample text assets (`DATA/GTA.DAT`, `DATA/HANDLING.CFG`) from retail directories on Linux without manual renaming.
