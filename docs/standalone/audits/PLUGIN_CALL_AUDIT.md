# Audit & Classification: 838 `plugin::Call` Sites

Generated during Phase 4 implementation. Total active `plugin::Call` occurrences: **805** across **187** files.

## Summary by Subsystem

| Subsystem | Call Sites | Default Fallback Strategy |
| :--- | :---: | :--- |
| Pedestrians & Tasks | 229 | Diagnostic stub (`nullptr` / `false` / `0`) |
| Vehicles & Traffic AI | 189 | Safe traffic AI degradation (bypasses unreversed AI routes) |
| Miscellaneous | 136 | Diagnostic stub (`nullptr` / `false` / `0`) |
| Interiors & Furniture | 73 | Native minimal stubs (`Init`, `AddInterior`, `Exit`, `GetEntity`) + Safe defaults |
| Rendering & Special FX | 55 | Diagnostic stub (`nullptr` / `false` / `0`) |
| Audio System | 40 | Diagnostic stub (`nullptr` / `false` / `0`) |
| Camera Subsystem | 24 | Safe matrix retention; unreversed sequence stubs |
| Scripting & SCM | 24 | Diagnostic stub (`nullptr` / `false` / `0`) |
| UI & Frontend | 15 | Diagnostic stub (`nullptr` / `false` / `0`) |
| Memory & Platform | 12 | Native CRT allocator decoupling (`malloc`/`free`/`realloc`) |
| Collision & World Geometry | 8 | Diagnostic stub (`nullptr` / `false` / `0`) |

---

## Detailed Subsystem Breakdown

### Pedestrians & Tasks (229 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/Attractors/PedShelterAttractor.cpp` | 7 | `0x5EF420` | `plugin::CallAndReturn` |
| `source/game_sa/Attractors/PedShelterAttractor.cpp` | 25 | `0x5EF570` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Conversations/ConversationForPed.cpp` | 24 | `0x43C190` | `plugin::CallMethod` |
| `source/game_sa/Conversations/ConversationForPed.cpp` | 29 | `0x43AC40` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Conversations/PedToPlayerConversations.cpp` | 28 | `0x43B0F0` | `plugin::Call` |
| `source/game_sa/DecisionMakers/Decision.cpp` | 24 | `0x600530` | `plugin::CallMethod` |
| `source/game_sa/DecisionMakers/Decision.cpp` | 39 | `0x600570` | `plugin::CallMethod` |
| `source/game_sa/DecisionMakers/DecisionMakerTypes.cpp` | 12 | `0x607050` | `plugin::CallMethodAndReturn` |
| `source/game_sa/DecisionMakers/DecisionMakerTypes.cpp` | 17 | `0x4684F0` | `plugin::CallAndReturn` |
| `source/game_sa/DecisionMakers/DecisionMakerTypes.cpp` | 22 | `0x606E70` | `plugin::CallMethod` |
| `source/game_sa/DecisionMakers/DecisionMakerTypes.cpp` | 27 | `0x6043A0` | `plugin::CallMethod` |
| `source/game_sa/DecisionMakers/DecisionMakerTypes.cpp` | 38 | `0x6044C0` | `plugin::CallMethod` |
| `source/game_sa/DecisionMakers/DecisionMakerTypes.cpp` | 43 | `0x604490` | `plugin::CallMethod` |
| `source/game_sa/DecisionMakers/DecisionMakerTypes.cpp` | 47 | `0x600840` | `plugin::CallMethod` |
| `source/game_sa/Entity/Ped/Ped.cpp` | 2219 | `0x5E57F0` | `plugin::CallMethod` |
| `source/game_sa/Entity/Ped/Ped.cpp` | 3694 | `0x5E8CD0` | `plugin::CallMethod` |
| `source/game_sa/Entity/Ped/Ped.cpp` | 3729 | `0x5E3C30` | `plugin::CallMethod` |
| `source/game_sa/Entity/Ped/Ped.cpp` | 3737 | `0x5E3E90` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Entity/Ped/Ped.cpp` | 3974 | `0x5E2530` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Entity/Ped/PedSaveStructure.cpp` | 5 | `0x5D44B0` | `plugin::CallMethod` |
| `source/game_sa/Entity/Ped/PedSaveStructure.cpp` | 9 | `0x5D43D0` | `plugin::CallMethod` |
| `source/game_sa/Entity/Ped/PlayerPed.cpp` | 347 | `0x6098F0` | `plugin::CallMethod` |
| `source/game_sa/Entity/Ped/PlayerPed.cpp` | 678 | `0x60A610` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Entity/Ped/PlayerPed.cpp` | 684 | `0x60A820` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Entity/Ped/PlayerPed.cpp` | 723 | `0x60A9C0` | `plugin::CallMethod` |
| *(and 204 more call sites)* | ... | ... | ... |

### Vehicles & Traffic AI (189 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/CarCtrl.cpp` | 136 | `0x424CE0` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 166 | `0x423F00` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 171 | `0x422760` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 256 | `0x42C740` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 261 | `0x42C2B0` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 266 | `0x428040` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 271 | `0x42EC90` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 276 | `0x4325C0` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 281 | `0x4226F0` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 286 | `0x42B470` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 291 | `0x434400` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 296 | `0x42BD20` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 301 | `0x422090` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 306 | `0x422620` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 311 | `0x421770` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 316 | `0x4224E0` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 321 | `0x424130` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 325 | `0x422370` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 330 | `0x42B270` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 335 | `0x429A70` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 340 | `0x423940` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 345 | `0x423000` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 350 | `0x424210` | `plugin::CallAndReturn` |
| `source/game_sa/CarCtrl.cpp` | 355 | `0x42F9C0` | `plugin::Call` |
| `source/game_sa/CarCtrl.cpp` | 360 | `0x42B7D0` | `plugin::CallAndReturn` |
| *(and 164 more call sites)* | ... | ... | ... |

### Miscellaneous (136 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/app/platform/platform.cpp` | 245 | `0x745510` | `plugin::CallAndReturn` |
| `source/app/platform/preset_view.cpp` | 122 | `0x619D60` | `plugin::Call` |
| `source/app/platform/preset_view.cpp` | 127 | `0x619FA0` | `plugin::Call` |
| `source/game_sa/Animation/AnimBlendHierarchy.cpp` | 173 | `0x4CF800` | `plugin::CallMethod` |
| `source/game_sa/AttractorScanner.cpp` | 7 | `0x5FFF90` | `plugin::CallMethod` |
| `source/game_sa/AutoPilot.cpp` | 47 | `0x41B980` | `plugin::CallMethod` |
| `source/game_sa/AutoPilot.cpp` | 52 | `0x41B950` | `plugin::CallMethod` |
| `source/game_sa/ClothesBuilder.cpp` | 87 | `0x5A44C0` | `plugin::Call` |
| `source/game_sa/ClothesBuilder.cpp` | 262 | `0x5A5340` | `plugin::CallAndReturn` |
| `source/game_sa/ClothesBuilder.cpp` | 492 | `0x5A6040` | `plugin::Call` |
| `source/game_sa/ClothesBuilder.cpp` | 497 | `0x5A6530` | `plugin::Call` |
| `source/game_sa/Conversations/Conversations.cpp` | 157 | `0x43ADB0` | `plugin::Call` |
| `source/game_sa/Cover.cpp` | 247 | `0x6987F0` | `plugin::CallAndReturn` |
| `source/game_sa/Cover.cpp` | 252 | `0x698990` | `plugin::CallAndReturn` |
| `source/game_sa/Cover.cpp` | 276 | `0x6988E0` | `plugin::Call` |
| `source/game_sa/EntityScanner.cpp` | 42 | `0x5FFA20` | `plugin::CallMethod` |
| `source/game_sa/EntryExit.cpp` | 321 | `0x4404A0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Events/EventHandler.cpp` | 1470 | `0x4B9FF0` | `plugin::CallMethod` |
| `source/game_sa/Events/EventHandler.cpp` | 1564 | `0x4BDB80` | `plugin::CallMethod` |
| `source/game_sa/Events/EventHandler.cpp` | 1569 | `0x4BE7D0` | `plugin::CallMethod` |
| `source/game_sa/Events/EventScanner.cpp` | 16 | `0x607E30` | `plugin::CallMethod` |
| `source/game_sa/Events/EventScanner.cpp` | 35 | `0x603720` | `plugin::CallMethod` |
| `source/game_sa/Events/EventSource.cpp` | 6 | `0x4ABAC0` | `plugin::CallAndReturn` |
| `source/game_sa/Events/GroupEventHandler.cpp` | 359 | `0x5F8900` | `plugin::CallAndReturn` |
| `source/game_sa/Events/GroupEventHandler.cpp` | 469 | `0x5F9530` | `plugin::CallAndReturn` |
| *(and 111 more call sites)* | ... | ... | ... |

### Interiors & Furniture (73 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/Interior/FurnitureSubGroup_c.cpp` | 15 | `0x5C00C0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/FurnitureSubGroup_c.cpp` | 20 | `0x590EE0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/FurnitureSubGroup_c.cpp` | 25 | `0x590FD0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 56 | `0x5947E0` | `plugin::CallMethod` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 62 | `0x5968E0` | `plugin::CallMethod` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 77 | `0x594840` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 83 | `0x596890` | `plugin::CallMethod` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 88 | `0x596830` | `plugin::CallMethod` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 93 | `0x5965E0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 98 | `0x595590` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 103 | `0x595380` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 108 | `0x595320` | `plugin::CallMethod` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 124 | `0x595290` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 130 | `0x595250` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 135 | `0x595200` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 163 | `0x594E90` | `plugin::CallMethod` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 168 | `0x594E30` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 173 | `0x594C10` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 178 | `0x594BF0` | `plugin::CallMethod` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 186 | `0x594BD0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 198 | `0x594B90` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 210 | `0x594970` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 215 | `0x594920` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/InteriorGroup_c.cpp` | 220 | `0x5948C0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Interior/Interior_c.cpp` | 72 | `0x593BF0` | `plugin::CallMethodAndReturn` |
| *(and 48 more call sites)* | ... | ... | ... |

### Rendering & Special FX (55 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/Fx/Blueprints/FxInfoAttractLine.cpp` | 18 | `0x4A4880` | `plugin::Call` |
| `source/game_sa/Fx/Blueprints/Interp/FxInterpInfo255.cpp` | 41 | `0x4A8B80` | `plugin::CallMethod` |
| `source/game_sa/Fx/Blueprints/Interp/FxInterpInfo32.cpp` | 41 | `0x4A89C0` | `plugin::CallMethod` |
| `source/game_sa/Fx/Blueprints/Interp/FxInterpInfoFloat.cpp` | 41 | `0x4A85C0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Fx/Blueprints/Interp/FxInterpInfoFloat.cpp` | 46 | `0x4A8470` | `plugin::CallMethod` |
| `source/game_sa/Fx/Blueprints/Interp/FxInterpInfoU255.cpp` | 41 | `0x4A8800` | `plugin::CallMethod` |
| `source/game_sa/Fx/FxEmitter.cpp` | 122 | `0x4A41E0` | `plugin::CallMethod` |
| `source/game_sa/Fx/FxEmitter.cpp` | 178 | `0x4A2580` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Fx/FxEmitterBP.cpp` | 35 | `0x4A1940` | `plugin::CallMethod` |
| `source/game_sa/Fx/FxEmitterBP.cpp` | 40 | `0x4A21D0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Fx/FxEmitterBP.cpp` | 113 | `0x4A2C40` | `plugin::CallMethod` |
| `source/game_sa/Fx/FxEmitterBP.cpp` | 182 | `0x4A2510` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Fx/FxFrustumInfo.cpp` | 7 | `0x4AA030` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Fx/FxInfoManager.cpp` | 140 | `0x5C0B70` | `plugin::CallMethod` |
| `source/game_sa/Fx/FxPrimBP.cpp` | 39 | `0x5C2010` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Pipelines/CustomBuilding/CustomBuildingRenderer.cpp` | 43 | `0x5D7F00` | `plugin::Call` |
| `source/game_sa/Pipelines/CustomBuilding/CustomBuildingRenderer.cpp` | 48 | `0x5D7F40` | `plugin::CallAndReturn` |
| `source/game_sa/Pipelines/CustomBuilding/CustomBuildingRenderer.cpp` | 53 | `0x5D7F80` | `plugin::Call` |
| `source/game_sa/Pipelines/CustomBuilding/CustomBuildingRenderer.cpp` | 87 | `0x5D8050` | `plugin::Call` |
| `source/game_sa/RealTimeShadowManager.cpp` | 67 | `0x706870` | `plugin::CallMethod` |
| `source/game_sa/RealTimeShadowManager.cpp` | 121 | `0x706970` | `plugin::CallMethodAndReturn` |
| `source/game_sa/RenderWare/D3DResourceSystem.cpp` | 12 | `0x730900` | `plugin::Call` |
| `source/game_sa/RenderWare/D3DResourceSystem.cpp` | 17 | `0x7307F0` | `plugin::CallAndReturn` |
| `source/game_sa/RenderWare/D3DResourceSystem.cpp` | 22 | `0x730660` | `plugin::CallAndReturn` |
| `source/game_sa/RenderWare/D3DResourceSystem.cpp` | 27 | `0x730830` | `plugin::Call` |
| *(and 30 more call sites)* | ... | ... | ... |

### Audio System (40 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/Audio/Entities/AEFrontendAudioEntity.cpp` | 37 | `0x4DD4A0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEFrontendAudioEntity.cpp` | 760 | `0x4DEDA0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEPedAudioEntity.cpp` | 498 | `0x4E1A40` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEPedAudioEntity.cpp` | 503 | `0x4E1CC0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEPedAudioEntity.cpp` | 508 | `0x4E2350` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEPedAudioEntity.cpp` | 565 | `0x4E2EE0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEPoliceScannerAudioEntity.cpp` | 37 | `0x4E71E0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEPoliceScannerAudioEntity.cpp` | 131 | `0x4E6F60` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 45 | `0x4EC100` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 50 | `0x4EC040` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 55 | `0x4EBFE0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 60 | `0x4EBF60` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 70 | `0x4EC0C0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 75 | `0x4EC4D0` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 80 | `0x4EC6D0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 123 | `0x4EC270` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 128 | `0x4EC190` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 133 | `0x4ECCF0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEScriptAudioEntity.cpp` | 771 | `0x4EC970` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEVehicleAudioEntity.cpp` | 3765 | `0x4FF900` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEVehicleAudioEntity.cpp` | 3818 | `0x500F50` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEVehicleAudioEntity.cpp` | 4324 | `0x4FFDC0` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEVehicleAudioEntity.cpp` | 4329 | `0x500040` | `plugin::CallMethod` |
| `source/game_sa/Audio/Entities/AEWeatherAudioEntity.cpp` | 82 | `0x505A00` | `plugin::CallMethod` |
| `source/game_sa/Audio/Hardware/AEAudioHardware.cpp` | 314 | `0x4D86B0` | `plugin::CallMethod` |
| *(and 15 more call sites)* | ... | ... | ... |

### Camera Subsystem (24 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/Camera.cpp` | 510 | `0x50AFA0` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1099 | `0x50C910` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1119 | `0x515BD0` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1125 | `0x50CB90` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1226 | `0x420C40` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Camera.cpp` | 1268 | `0x50CFA0` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1274 | `0x50D090` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1279 | `0x50D160` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1284 | `0x50D1D0` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1431 | `0x516440` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1436 | `0x50D350` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1456 | `0x50D430` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1470 | `0x50D510` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1475 | `0x5164A0` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1481 | `0x51A6F0` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1487 | `0x516560` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Camera.cpp` | 1502 | `0x52B730` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1612 | `0x514D60` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1617 | `0x5150E0` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1622 | `0x516B20` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1660 | `0x51E560` | `plugin::CallMethodAndReturn` |
| `source/game_sa/Camera.cpp` | 1665 | `0x520190` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1670 | `0x527FA0` | `plugin::CallMethod` |
| `source/game_sa/Camera.cpp` | 1683 | `0x5B24D0` | `plugin::CallMethod` |

### Scripting & SCM (24 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/ScriptResourceManager.cpp` | 24 | `0x4704B0` | `plugin::Call` |
| `source/game_sa/ScriptResourceManager.cpp` | 29 | `0x470510` | `plugin::CallAndReturn` |
| `source/game_sa/ScriptResourceManager.cpp` | 34 | `0x470620` | `plugin::CallAndReturn` |
| `source/game_sa/Scripts/Commands/CharacterCommands.cpp` | 3288 | `0x64F110` | `plugin::CallAndReturn` |
| `source/game_sa/Scripts/RunningScript.cpp` | 208 | `0x465AA0` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 281 | `0x470150` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 286 | `0x487A20` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 291 | `0x486D80` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 296 | `0x487D10` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 301 | `0x487420` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 306 | `0x4870F0` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 311 | `0x487720` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 316 | `0x488EC0` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 321 | `0x488B50` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 326 | `0x489150` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 331 | `0x487F60` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 336 | `0x488780` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 341 | `0x4883F0` | `plugin::CallMethod` |
| `source/game_sa/Scripts/RunningScript.cpp` | 463 | `0x46AF50` | `plugin::CallMethod` |
| `source/game_sa/Scripts/TheScripts.cpp` | 1805 | `0x485C20` | `plugin::Call` |
| `source/game_sa/ScriptsForBrains.cpp` | 31 | `0x46FF20` | `plugin::CallMethod` |
| `source/game_sa/ScriptsForBrains.cpp` | 35 | `0x46AAE0` | `plugin::CallMethod` |
| `source/game_sa/ScriptsForBrains.cpp` | 39 | `0x46AA80` | `plugin::CallMethod` |
| `source/game_sa/ScriptsForBrains.cpp` | 43 | `0x46B270` | `plugin::CallMethodAndReturn` |

### UI & Frontend (15 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/Font.cpp` | 183 | `0x718A10` | `plugin::Call` |
| `source/game_sa/Font.cpp` | 595 | `0x719840` | `plugin::Call` |
| `source/game_sa/Font.cpp` | 661 | `0x71A220` | `plugin::CallAndReturn` |
| `source/game_sa/Font.cpp` | 762 | `0x719670` | `plugin::CallAndReturn` |
| `source/game_sa/Hud.cpp` | 596 | `0x58E020` | `plugin::Call` |
| `source/game_sa/Hud.cpp` | 598 | `0x58E020` | `plugin::Call` |
| `source/game_sa/Hud.cpp` | 935 | `0x58B6E0` | `plugin::Call` |
| `source/game_sa/Hud.cpp` | 940 | `0x58B180` | `plugin::Call` |
| `source/game_sa/Hud.cpp` | 1241 | `0x58C250` | `plugin::Call` |
| `source/game_sa/Hud.cpp` | 1246 | `0x58C6A0` | `plugin::Call` |
| `source/game_sa/Hud.cpp` | 1349 | `0x589650` | `plugin::Call` |
| `source/game_sa/Hud.cpp` | 1461 | `0x58EAF0` | `plugin::Call` |
| `source/game_sa/Hud.cpp` | 1559 | `0x58D9A0` | `plugin::Call` |
| `source/game_sa/MenuSystem.cpp` | 572 | `0x581B30` | `plugin::Call` |
| `source/game_sa/MenuSystem.cpp` | 606 | `0x5820E0` | `plugin::Call` |

### Memory & Platform (12 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/Memory/MemoryHeap.cpp` | 331 | `0x72E8E0` | `plugin::CallMethod` |
| `source/game_sa/MemoryMgr.cpp` | 104 | `0x72F480` | `plugin::Call` |
| `source/game_sa/MemoryMgr.cpp` | 240 | `0x72F420` | `plugin::CallAndReturn` |
| `source/game_sa/MemoryMgr.cpp` | 262 | `0x72F430` | `plugin::Call` |
| `source/game_sa/MemoryMgr.cpp` | 299 | `0x72F440` | `plugin::CallAndReturn` |
| `source/game_sa/MemoryMgr.cpp` | 309 | `0x72F460` | `plugin::CallAndReturn` |
| `source/game_sa/MemoryMgr.cpp` | 326 | `0x72F4F0` | `plugin::Call` |
| `source/game_sa/MemoryMgr.cpp` | 392 | `0x72F4C0` | `plugin::CallAndReturn` |
| `source/game_sa/MemoryMgr.cpp` | 457 | `0x82119A` | `plugin::CallAndReturn` |
| `source/game_sa/MemoryMgr.cpp` | 461 | `0x821195` | `plugin::CallAndReturn` |
| `source/game_sa/MemoryMgr.cpp` | 465 | `0x8214BD` | `plugin::Call` |
| `source/game_sa/MemoryMgr.cpp` | 469 | `0x8213AE` | `plugin::Call` |

### Collision & World Geometry (8 calls)

| File | Line | Address | Invocation Type |
| :--- | :---: | :---: | :--- |
| `source/game_sa/Collision/Collision.cpp` | 1881 | `0x418580` | `plugin::Call` |
| `source/game_sa/Collision/Collision.cpp` | 1889 | `0x4185A0` | `plugin::Call` |
| `source/game_sa/Collision/Collision.cpp` | 3547 | `0x411EC0` | `plugin::Call` |
| `source/game_sa/Collision/Collision.cpp` | 3576 | `0x412130` | `plugin::Call` |
| `source/game_sa/Collision/Collision.cpp` | 3672 | `0x412AA0` | `plugin::CallAndReturn` |
| `source/game_sa/Collision/Collision.cpp` | 3780 | `0x413100` | `plugin::CallAndReturn` |
| `source/game_sa/Collision/CollisionEventScanner.cpp` | 7 | `0x604500` | `plugin::CallMethod` |
| `source/game_sa/Plugins/CollisionPlugin/CollisionPlugin.cpp` | 36 | `0x41B1D0` | `plugin::CallAndReturn` |

