# Phase 3: Filesystem & VFS Normalization

* **Status**: **COMPLETED**
* **Prerequisites**: Phase 2 (Platform Abstraction Layer).

---

## 1. Objective
Ensure robust, case-insensitive asset loading across Windows, Linux, and macOS, resolving GTA San Andreas's legacy Windows backslash separators and mixed-case directory structures.

---

## 2. Scope & Key Tasks
1. **Path Normalization**:
   - Implemented `CFileMgr::NormalizePath`: automatically normalizes Windows backslashes (`\`) to standard forward slashes (`/`), collapses duplicate slashes (`//`), strips redundant `./`, and trims whitespace and quotes.
2. **Case-Insensitive VFS Lookup**:
   - Implemented `CFileMgr::ResolvePath` with thread-safe resolution caches (`s_PathCache`, `s_DirCache`).
   - Recursively traverses path segments case-insensitively, resolving requested assets (such as `DATA/DEFAULT.DAT` or `DATA/GTA.DAT`) to the true casing on disk (e.g. `data/default.dat`).
   - Integrated into `CFileMgr::OpenFile`, `OpenFileForWriting`, `OpenFileForAppending`, `ChangeDir`, `SetDir`, and `SetDirMyDocuments`.
3. **Archive Mount Interface**:
   - Updated `CdStreamOpen` in `source/game_sa/CdStreamInfo.cpp` to resolve archive paths (`MODELS/GTA3.IMG`, `MODELS/GTA_INT.IMG`) through `CFileMgr::ResolvePath`.
   - Updated audio stream table loaders in `CAEMP3TrackLoader` (`AEMP3TrackLoader.cpp`) to route through `CFileMgr`.

---

## 3. Verification Protocol
- [x] Unit tests for `CFileMgr` path normalization on Windows and Linux (`NormalizePath` verified).
- [x] Successfully locate and parse sample text assets (`DATA/GTA.DAT`, `DATA/HANDLING.CFG`, `DATA/SCRIPT/MAIN.SCM`) from retail directories on Linux without manual renaming.
- [x] Thread-safe caching and write path resolution verified.
