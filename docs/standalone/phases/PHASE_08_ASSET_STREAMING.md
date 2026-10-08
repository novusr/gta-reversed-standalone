# Phase 8: Asset Loading & Streaming Hydration

* **Status**: **PLANNED**
* **Prerequisites**: Phase 3 (VFS), Phase 5 (`librw`), Phase 7 (Renderer Boot).

---

## 1. Objective
Mount original retail GTA San Andreas `.img` archives, parse data definition files, and hydrate textures, models, and animations through `CStreaming`.

---

## 2. Scope & Key Tasks
1. **Archive Mounting via `CdStream`**:
   - Open and map `models/gta3.img`, `models/gta_int.img`, `models/player.img`.
   - Implement asynchronous or prioritized synchronous archive block reading.
2. **Data File Parsing**:
   - Parse `DATA/DEFAULT.DAT` and `DATA/GTA.DAT` using `CFileLoader::LoadLevel()`.
   - Populate `CModelInfo` arrays with `IDE` definitions (peds, vehicles, weapons, 2dfx).
3. **Streaming Engine Validation**:
   - Test `CStreaming::RequestModel()`, `CStreaming::LoadAllRequestedModels()`.
   - Verify `CStreaming::ConvertBufferToObject` parsing DFF clumps, TXD dictionaries, and COL collision files into memory.

---

## 3. Verification Protocol
- [ ] Successfully load models, textures, and collisions for 500+ game objects.
- [ ] Memory budget enforcement correctly flushes unneeded models via LRU eviction.
