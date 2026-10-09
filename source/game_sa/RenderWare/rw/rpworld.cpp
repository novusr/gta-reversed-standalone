#ifndef NOTSA_STANDALONE_NATIVE
#include "StdInc.h"
#else
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "Base.h"
#include "RenderWare/RenderWare.h"
#endif

#include "rpworld.h"
#ifndef NOTSA_STANDALONE_NATIVE
#include <rpdbgerr.h>
#endif

#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
using namespace notsa::rwbridge;
#endif

void _rwD3D9VSSetActiveWorldMatrix(const RwMatrix* worldMatrix) {
    ((void(__cdecl *)(const RwMatrix*))0x764650)(worldMatrix);
}

void _rwD3D9VSGetComposedTransformMatrix() {
    ((void(__cdecl *)(void))0x7646E0)();
}

void _rwD3D9VSGetWorldViewTransposedMatrix() {
    ((void(__cdecl *)(void))0x764730)();
}

void _rwD3D9VSGetWorldViewMatrix() {
    ((void(__cdecl *)(void))0x764760)();
}

void _rwD3D9VSGetInverseWorldMatrix() {
    ((void(__cdecl *)(void))0x7647B0)();
}

void _rwD3D9VSGetWorldMultiplyMatrix(RwMatrix* worldMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(RwMatrix*, const RwMatrix*))0x764920)(worldMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldMultiplyTransposeMatrix(void* worldMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(void*, const RwMatrix*))0x764960)(worldMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldViewMultiplyTransposeMatrix(void* worldViewMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(void*, const RwMatrix*))0x7649D0)(worldViewMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldNormalizedMultiplyTransposeMatrix(void* worldMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(void*, const RwMatrix*))0x764A70)(worldMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldNormalizedViewMultiplyTransposeMatrix(void* worldViewMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(void*, const RwMatrix*))0x764B50)(worldViewMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldNormalizedTransposeMatrix() {
    ((void(__cdecl *)(void))0x764C60)();
}

void _rwD3D9VSGetProjectionTransposedMatrix() {
    ((void(__cdecl *)(void))0x764D20)();
}

void _rwD3D9VSGetNormalInLocalSpace(const RwV3d* normalWorldSpace, RwV3d* normalLocalSpace) {
    ((void(__cdecl *)(const RwV3d*, RwV3d*))0x764D30)(normalWorldSpace, normalLocalSpace);
}

void _rwD3D9VSGetPointInLocalSpace(const RwV3d* pointWorldSpace, RwV3d* pointLocalSpace) {
    ((void(__cdecl *)(const RwV3d*, RwV3d*))0x764E70)(pointWorldSpace, pointLocalSpace);
}

void _rwD3D9VSGetRadiusInLocalSpace(RwReal radiusWorldSpace, RwReal* radiusLocalSpace) {
    ((void(__cdecl *)(RwReal, RwReal*))0x764F60)(radiusWorldSpace, radiusLocalSpace);
}

void _rpD3D9VertexShaderCachePurge() {
    ((void(__cdecl *)(void))0x75EE60)();
}

void* _rpD3D9GetVertexShader(const _rpD3D9VertexShaderDescriptor* desc, _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    return ((void*(__cdecl *)(const _rpD3D9VertexShaderDescriptor*, _rpD3D9VertexShaderDispatchDescriptor*))0x75EED0)(desc, dispatch);
}

RwUInt32 _rpD3D9GetNumConstantsUsed(const _rpD3D9VertexShaderDescriptor* desc) {
    return ((RwUInt32(__cdecl *)(const _rpD3D9VertexShaderDescriptor*))0x75EDD0)(desc);
}

void _rxD3D9VertexShaderDefaultBeginCallBack(void* object, RwUInt32 type, _rpD3D9VertexShaderDescriptor* desc) {
    ((void(__cdecl *)(void*, RwUInt32, _rpD3D9VertexShaderDescriptor*))0x760DF0)(object, type, desc);
}

RwV4d* _rxD3D9VertexShaderDefaultLightingCallBack(void* object, RwUInt32 type, RwV4d* shaderConstantPtr, _rpD3D9VertexShaderDescriptor* desc) {
    return ((RwV4d*(__cdecl *)(void*, RwUInt32, RwV4d*, _rpD3D9VertexShaderDescriptor*))0x761170)(object, type, shaderConstantPtr, desc);
}

void* _rxD3D9VertexShaderDefaultGetMaterialShaderCallBack(const RpMaterial* material, _rpD3D9VertexShaderDescriptor* desc, _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    return ((void*(__cdecl *)(const RpMaterial*, _rpD3D9VertexShaderDescriptor*, _rpD3D9VertexShaderDispatchDescriptor*))0x761010)(material, desc, dispatch);
}

void _rxD3D9VertexShaderDefaultMeshRenderCallBack(RxD3D9ResEntryHeader* resEntryHeader, RxD3D9InstanceData* instancedMesh, const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RxD3D9ResEntryHeader*, RxD3D9InstanceData*, const _rpD3D9VertexShaderDescriptor*, const _rpD3D9VertexShaderDispatchDescriptor*))0x761030)(resEntryHeader, instancedMesh, desc, dispatch);
}

void _rxD3D9VertexShaderDefaultEndCallBack(void* object, RwUInt32 type, _rpD3D9VertexShaderDescriptor* desc) {
    ((void(__cdecl *)(void*, RwUInt32, _rpD3D9VertexShaderDescriptor*))0x761000)(object, type, desc);
}

void _rpD3D9VertexShaderUpdateLightsColors(RwV4d* shaderConstantPtr, const _rpD3D9VertexShaderDescriptor* desc, RwReal ambientCoef, RwReal diffuseCoef) {
    ((void(__cdecl *)(RwV4d*, const _rpD3D9VertexShaderDescriptor*, RwReal, RwReal))0x761720)(shaderConstantPtr, desc, ambientCoef, diffuseCoef);
}

void _rpD3D9VertexShaderUpdateMaterialColor(const RwRGBA* color, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(const RwRGBA*, const _rpD3D9VertexShaderDispatchDescriptor*))0x761820)(color, dispatch);
}

void _rpD3D9VertexShaderUpdateFogData(const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(const _rpD3D9VertexShaderDescriptor*, const _rpD3D9VertexShaderDispatchDescriptor*))0x7618B0)(desc, dispatch);
}

void _rpD3D9VertexShaderUpdateMorphingCoef(RwReal morphingCoef, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RwReal, const _rpD3D9VertexShaderDispatchDescriptor*))0x761950)(morphingCoef, dispatch);
}

void _rpD3DVertexShaderSetUVAnimMatrix(RwMatrix* matrix, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RwMatrix*, const _rpD3D9VertexShaderDispatchDescriptor*))0x7619A0)(matrix, dispatch);
}

void _rpD3D9VertexShaderSetEnvMatrix(RwFrame* frame, const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RwFrame*, const _rpD3D9VertexShaderDescriptor*, const _rpD3D9VertexShaderDispatchDescriptor*))0x761A10)(frame, desc, dispatch);
}

void _rpD3D9VertexShaderSetBumpMatrix(RwFrame* frame, RwReal factor, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RwFrame*, RwReal, const _rpD3D9VertexShaderDispatchDescriptor*))0x761B70)(frame, factor, dispatch);
}

RxNodeDefinition* RxNodeDefinitionGetD3D9WorldSectorAllInOne() {
    return ((RxNodeDefinition*(__cdecl *)(void))0x75E9F0)();
}

RxNodeDefinition* RxNodeDefinitionGetD3D9AtomicAllInOne() {
    return ((RxNodeDefinition*(__cdecl *)(void))0x7582E0)();
}

void RpMaterialSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x74D8C0)(blockSize, numBlocksToPrealloc);
}

RpMaterial* RpMaterialCreate() {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Material::create());
#else
    return ((RpMaterial*(__cdecl *)(void))0x74D990)();
#endif
}

RwBool RpMaterialDestroy(RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) {
        ToRw(material)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpMaterial*))0x74DA20)(material);
#endif
}

RpMaterial* RpMaterialClone(RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material ? FromRw(ToRw(material)->clone()) : nullptr;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*))0x74DA80)(material);
#endif
}

RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) {
        ToRw(material)->setTexture(ToRw(texture));
    }
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x74DBC0)(material, texture);
#endif
}

RwInt32 RpMaterialRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Material::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74DBF0)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RpMaterialRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Material::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74DC20)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RpMaterialSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Material::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74DC50)(pluginID, alwaysCB);
#endif
}

RwInt32 RpMaterialSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Material::setStreamRightsCallback(pluginID, (rw::RightsCallback)rightsCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkRightsCallBack))0x74DC70)(pluginID, rightsCB);
#endif
}

RwInt32 RpMaterialGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Material::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x74DC90)(pluginID);
#endif
}

RwBool RpMaterialValidatePlugins(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)material;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RpMaterial*))0x74DCB0)(material);
#endif
}

RwUInt32 RpMaterialStreamGetSize(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material ? ToRw(const_cast<RpMaterial*>(material))->streamGetSize() : 0;
#else
    return ((RwUInt32(__cdecl *)(const RpMaterial*))0x74E010)(material);
#endif
}

RpMaterial* RpMaterialStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Material::streamRead(ToRw(stream)));
#else
    return ((RpMaterial*(__cdecl *)(RwStream*))0x74DD30)(stream);
#endif
}

const RpMaterial* RpMaterialStreamWrite(const RpMaterial* material, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) ToRw(const_cast<RpMaterial*>(material))->streamWrite(ToRw(stream));
    return material;
#else
    return ((const RpMaterial*(__cdecl *)(const RpMaterial*, RwStream*))0x74E050)(material, stream);
#endif
}

RpMaterialChunkInfo* _rpMaterialChunkInfoRead(RwStream* stream, RpMaterialChunkInfo* materialChunkInfo, RwInt32* bytesRead) {
    return ((RpMaterialChunkInfo*(__cdecl *)(RwStream*, RpMaterialChunkInfo*, RwInt32*))0x74DCC0)(stream, materialChunkInfo, bytesRead);
}

RpMaterialList* _rpMaterialListInitialize(RpMaterialList* matList) {
    return ((RpMaterialList*(__cdecl *)(RpMaterialList*))0x74E1B0)(matList);
}

RpMaterialList* _rpMaterialListDeinitialize(RpMaterialList* matList) {
    return ((RpMaterialList*(__cdecl *)(RpMaterialList*))0x74E150)(matList);
}

RpMaterial** _rpMaterialListAlloc(RwUInt32 count) {
    return ((RpMaterial**(__cdecl *)(RwUInt32))0x74E1C0)(count);
}

RpMaterial* _rpMaterialListGetMaterial(const RpMaterialList* matList, RwInt32 matIndex) {
    return ((RpMaterial*(__cdecl *)(const RpMaterialList*, RwInt32))0x74E2B0)(matList, matIndex);
}

RpMaterialList* _rpMaterialListSetSize(RpMaterialList* matList, RwInt32 size) {
    return ((RpMaterialList*(__cdecl *)(RpMaterialList*, RwInt32))0x74E2C0)(matList, size);
}

RpMaterialList* _rpMaterialListCopy(RpMaterialList* matListOut, const RpMaterialList* matListIn) {
    return ((RpMaterialList*(__cdecl *)(RpMaterialList*, const RpMaterialList*))0x74E1F0)(matListOut, matListIn);
}

RwInt32 _rpMaterialListAppendMaterial(RpMaterialList* matList, RpMaterial* material) {
    return ((RwInt32(__cdecl *)(RpMaterialList*, RpMaterial*))0x74E350)(matList, material);
}

RwInt32 _rpMaterialListFindMaterialIndex(const RpMaterialList* matList, const RpMaterial* material) {
    return ((RwInt32(__cdecl *)(const RpMaterialList*, const RpMaterial*))0x74E420)(matList, material);
}

RwUInt32 _rpMaterialListStreamGetSize(const RpMaterialList* matList) {
    return ((RwUInt32(__cdecl *)(const RpMaterialList*))0x74E450)(matList);
}

RpMaterialList* _rpMaterialListStreamRead(RwStream* stream, RpMaterialList* matList) {
    return ((RpMaterialList*(__cdecl *)(RwStream*, RpMaterialList*))0x74E600)(stream, matList);
}

const RpMaterialList* _rpMaterialListStreamWrite(const RpMaterialList* matList, RwStream* stream) {
    return ((const RpMaterialList*(__cdecl *)(const RpMaterialList*, RwStream*))0x74E4B0)(matList, stream);
}

void* _rpMeshOpen(void* instance, RwInt32 offset, RwInt32 size) {
    return ((void*(__cdecl *)(void*, RwInt32, RwInt32))0x758970)(instance, offset, size);
}

void* _rpMeshClose(void* instance, RwInt32 offset, RwInt32 size) {
    return ((void*(__cdecl *)(void*, RwInt32, RwInt32))0x758940)(instance, offset, size);
}

RwInt16 _rpMeshGetNextSerialNumber(void) {
    return ((RwInt16(__cdecl *)(void))0x7590E0)();
}

RpBuildMesh* _rpBuildMeshCreate(RwUInt32 bufferSize) {
    return ((RpBuildMesh*(__cdecl *)(RwUInt32))0x758A90)(bufferSize);
}

RwBool _rpBuildMeshDestroy(RpBuildMesh* mesh) {
    return ((RwBool(__cdecl *)(RpBuildMesh*))0x758B80)(mesh);
}

RwBool _rpMeshDestroy(RpMeshHeader* mesh) {
    return ((RwBool(__cdecl *)(RpMeshHeader*))0x758BC0)(mesh);
}

RpBuildMesh* _rpBuildMeshAddTriangle(RpBuildMesh* mesh, RpMaterial* material, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3, RwUInt16 matIndex, RwUInt16 textureIndex, RwUInt16 rasterIndex, RwUInt16 pipelineIndex) {
    return ((RpBuildMesh*(__cdecl *)(RpBuildMesh*, RpMaterial*, RwInt32, RwInt32, RwInt32, RwUInt16, RwUInt16, RwUInt16, RwUInt16))0x758C00)(mesh, material, vert1, vert2, vert3, matIndex, textureIndex, rasterIndex, pipelineIndex);
}

RpMeshHeader* _rpMeshHeaderForAllMeshes(RpMeshHeader* meshHeader, RpMeshCallBack fpCallBack, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpMeshHeader*, RpMeshCallBack, void*))0x758D30)(meshHeader, fpCallBack, data);
}

RwStream* _rpMeshWrite(const RpMeshHeader* meshHeader, const void* object, RwStream* stream, const RpMaterialList* matList) {
    return ((RwStream*(__cdecl *)(const RpMeshHeader*, const void*, RwStream*, const RpMaterialList*))0x758D70)(meshHeader, object, stream, matList);
}

RpMeshHeader* _rpMeshRead(RwStream* stream, const void* object, const RpMaterialList* matList) {
    return ((RpMeshHeader*(__cdecl *)(RwStream*, const void*, const RpMaterialList*))0x758EC0)(stream, object, matList);
}

RwInt32 _rpMeshSize(const RpMeshHeader* meshHeader, const void* object) {
    return ((RwInt32(__cdecl *)(const RpMeshHeader*, const void*))0x759090)(meshHeader, object);
}

void _rpMeshHeaderDestroy(RpMeshHeader* meshHeader) {
    ((void(__cdecl *)(RpMeshHeader*))0x758910)(meshHeader);
}

RpMeshHeader* _rpMeshHeaderCreate(RwUInt32 size) {
    return ((RpMeshHeader*(__cdecl *)(RwUInt32))0x758920)(size);
}

RpTriStripPolygon* RpTriStripPolygonFollowStrip(RpTriStripPolygon* curr, RpTriStripPolygon* prev) {
    return ((RpTriStripPolygon*(__cdecl *)(RpTriStripPolygon*, RpTriStripPolygon*))0x75C330)(curr, prev);
}

RwUInt32 RpTriStripDefaultCost(RpTriStripPolygon* startPolygon, RwUInt32 testFrame, void* data) {
    return ((RwUInt32(__cdecl *)(RpTriStripPolygon*, RwUInt32, void*))0x75B500)(startPolygon, testFrame, data);
}

RpTriStripMesh* RpTriStripMeshTunnel(RpTriStripMesh* mesh, void* data) {
    return ((RpTriStripMesh*(__cdecl *)(RpTriStripMesh*, void*))0x75B780)(mesh, data);
}

RpTriStripMesh* RpTriStripMeshQuick(RpTriStripMesh* mesh, void* data) {
    return ((RpTriStripMesh*(__cdecl *)(RpTriStripMesh*, void*))0x75BD80)(mesh, data);
}

RpMeshHeader* RpBuildMeshGenerateTriStrip(RpBuildMesh* buildMesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75C380)(buildMesh, data);
}

RpMeshHeader* RpBuildMeshGenerateTrivialTriStrip(RpBuildMesh* buildMesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x759100)(buildMesh, data);
}

RpMeshHeader* RpBuildMeshGenerateDefaultTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x7591B0)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGeneratePreprocessTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75A900)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGenerateExhaustiveTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75A940)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGenerateDefaultIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75A8E0)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGeneratePreprocessIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75A920)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGenerateExhaustiveIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75B4E0)(buildmesh, data);
}

RwBool RpMeshSetTriStripMethod(RpTriStripMeshCallBack callback, void* data) {
    return ((RwBool(__cdecl *)(RpTriStripMeshCallBack, void*))0x75D4C0)(callback, data);
}

RwBool RpMeshGetTriStripMethod(RpTriStripMeshCallBack* callback, void* data) {
    return ((RwBool(__cdecl *)(RpTriStripMeshCallBack*, void*))0x75D500)(callback, data);
}

RpMeshHeader* _rpTriListMeshGenerate(RpBuildMesh* buildMesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75D530)(buildMesh, data);
}

RpMeshHeader* _rpMeshOptimise(RpBuildMesh* buildmesh, RwUInt32 flags) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, RwUInt32))0x75D970)(buildmesh, flags);
}

RpGeometry* RpGeometryTransform(RpGeometry* geometry, const RwMatrix* matrix) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*, const RwMatrix*))0x74BFE0)(geometry, matrix);
}

RpGeometry* RpGeometryCreateSpace(RwReal radius) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)radius;
    return RpGeometryCreate(0, 0, 0);
#else
    return ((RpGeometry*(__cdecl *)(RwReal))0x74C130)(radius);
#endif
}

const RpMorphTarget* RpMorphTargetCalcBoundingSphere(const RpMorphTarget* morphTarget, RwSphere* boundingSphere) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)morphTarget;
    (void)boundingSphere;
    return morphTarget;
#else
    return ((const RpMorphTarget*(__cdecl *)(const RpMorphTarget*, RwSphere*))0x74C200)(morphTarget, boundingSphere);
#endif
}

RwInt32 RpGeometryAddMorphTargets(RpGeometry* geometry, RwInt32 mtcount) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (geometry) {
        ToRw(geometry)->addMorphTargets(mtcount);
    }
    return geometry ? ToRw(geometry)->numMorphTargets : 0;
#else
    return ((RwInt32(__cdecl *)(RpGeometry*, RwInt32))0x74C310)(geometry, mtcount);
#endif
}

RwInt32 RpGeometryAddMorphTarget(RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    return RpGeometryAddMorphTargets(geometry, 1);
#else
    return ((RwInt32(__cdecl *)(RpGeometry*))0x74C4D0)(geometry);
#endif
}

RpGeometry* RpGeometryRemoveMorphTarget(RpGeometry* geometry, RwInt32 morphTarget) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)morphTarget;
    return geometry;
#else
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RwInt32))0x74C4E0)(geometry, morphTarget);
#endif
}

const RpGeometry* RpGeometryTriangleSetVertexIndices(const RpGeometry* geometry, RpTriangle* triangle, RwUInt16 vert1, RwUInt16 vert2, RwUInt16 vert3) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (triangle) {
        triangle->vertIndex[0] = vert1;
        triangle->vertIndex[1] = vert2;
        triangle->vertIndex[2] = vert3;
    }
    return geometry;
#else
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, RpTriangle*, RwUInt16, RwUInt16, RwUInt16))0x74C690)(geometry, triangle, vert1, vert2, vert3);
#endif
}

RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* geometry, RpTriangle* triangle, RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (geometry && triangle && material) {
        triangle->matIndex = (RwUInt16)ToRw(geometry)->matList.findIndex(ToRw(material));
    }
    return geometry;
#else
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RpTriangle*, RpMaterial*))0x74C6C0)(geometry, triangle, material);
#endif
}

const RpGeometry* RpGeometryTriangleGetVertexIndices(const RpGeometry* geometry, const RpTriangle* triangle, RwUInt16* vert1, RwUInt16* vert2, RwUInt16* vert3) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (triangle) {
        if (vert1) *vert1 = triangle->vertIndex[0];
        if (vert2) *vert2 = triangle->vertIndex[1];
        if (vert3) *vert3 = triangle->vertIndex[2];
    }
    return geometry;
#else
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, const RpTriangle*, RwUInt16*, RwUInt16*, RwUInt16*))0x74C720)(geometry, triangle, vert1, vert2, vert3);
#endif
}

RpMaterial* RpGeometryTriangleGetMaterial(const RpGeometry* geometry, const RpTriangle* triangle) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (geometry && triangle) {
        return FromRw(ToRw(geometry)->matList.materials[triangle->matIndex]);
    }
    return nullptr;
#else
    return ((RpMaterial*(__cdecl *)(const RpGeometry*, const RpTriangle*))0x74C760)(geometry, triangle);
#endif
}

RpGeometry* RpGeometryForAllMaterials(RpGeometry* geometry, RpMaterialCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (geometry && fpCallBack) {
        auto& ml = ToRw(geometry)->matList;
        for (int32 i = 0; i < ml.numMaterials; i++) {
            if (!fpCallBack(FromRw(ml.materials[i]), data))
                break;
        }
    }
    return geometry;
#else
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RpMaterialCallBack, void*))0x74C790)(geometry, fpCallBack, data);
#endif
}

RpGeometry* RpGeometryLock(RpGeometry* geometry, RwInt32 lockMode) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (geometry) {
        ToRw(geometry)->lock(lockMode);
    }
    return geometry;
#else
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RwInt32))0x74C7D0)(geometry, lockMode);
#endif
}

RpGeometry* RpGeometryUnlock(RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (geometry) {
        ToRw(geometry)->unlock();
    }
    return geometry;
#else
    return ((RpGeometry*(__cdecl *)(RpGeometry*))0x74C800)(geometry);
#endif
}

const RpGeometry* RpGeometryForAllMeshes(const RpGeometry* geometry, RpMeshCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)fpCallBack;
    (void)data;
    return geometry;
#else
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, RpMeshCallBack, void*))0x74CA60)(geometry, fpCallBack, data);
#endif
}

RpGeometry* RpGeometryCreate(RwInt32 numVert, RwInt32 numTriangles, RwUInt32 format) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Geometry::create(numVert, numTriangles, format));
#else
    return ((RpGeometry*(__cdecl *)(RwInt32, RwInt32, RwUInt32))0x74CA90)(numVert, numTriangles, format);
#endif
}

RwBool RpGeometryDestroy(RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (geometry) {
        ToRw(geometry)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpGeometry*))0x74CCC0)(geometry);
#endif
}

RwInt32 RpGeometryRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Geometry::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74CD70)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RpGeometryRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Geometry::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74CDA0)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RpGeometrySetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Geometry::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74CDD0)(pluginID, alwaysCB);
#endif
}

RwInt32 RpGeometryGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Geometry::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x74CDF0)(pluginID);
#endif
}

RwBool RpGeometryValidatePlugins(const RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)geometry;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RpGeometry*))0x74CE10)(geometry);
#endif
}

RwUInt32 RpGeometryStreamGetSize(const RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    return geometry ? ToRw(const_cast<RpGeometry*>(geometry))->streamGetSize() : 0;
#else
    return ((RwUInt32(__cdecl *)(const RpGeometry*))0x74CE20)(geometry);
#endif
}

const RpGeometry* RpGeometryStreamWrite(const RpGeometry* geometry, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (geometry) ToRw(const_cast<RpGeometry*>(geometry))->streamWrite(ToRw(stream));
    return geometry;
#else
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, RwStream*))0x74CED0)(geometry, stream);
#endif
}

RpGeometry* RpGeometryStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Geometry::streamRead(ToRw(stream)));
#else
    return ((RpGeometry*(__cdecl *)(RwStream*))0x74D190)(stream);
#endif
}

RpGeometryChunkInfo* _rpGeometryChunkInfoRead(RwStream* stream, RpGeometryChunkInfo* geometryChunkInfo, RwInt32* bytesRead) {
    return ((RpGeometryChunkInfo*(__cdecl *)(RwStream*, RpGeometryChunkInfo*, RwInt32*))0x74D750)(stream, geometryChunkInfo, bytesRead);
}

RpWorldSector* RpWorldSectorRender(RpWorldSector* worldSector) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*))0x761C50)(worldSector);
}

const RpWorldSector* RpWorldSectorForAllMeshes(const RpWorldSector* sector, RpMeshCallBack fpCallBack, void* data) {
    return ((const RpWorldSector*(__cdecl *)(const RpWorldSector*, RpMeshCallBack, void*))0x761C60)(sector, fpCallBack, data);
}

RwInt32 RpWorldSectorRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x761C90)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RpWorldSectorRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x761CC0)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RpWorldSectorSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x761CF0)(pluginID, alwaysCB);
}

RwInt32 RpWorldSectorSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkRightsCallBack))0x761D10)(pluginID, rightsCB);
}

RwInt32 RpWorldSectorGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x761D30)(pluginID);
}

RwBool RpWorldSectorValidatePlugins(const RpWorldSector* sector) {
    return ((RwBool(__cdecl *)(const RpWorldSector*))0x761D50)(sector);
}

void RpLightSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x752250)(blockSize, numBlocksToPrealloc);
}

RpLight* RpLightCreate(RwInt32 type) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Light::create(type));
#else
    return ((RpLight*(__cdecl *)(RwInt32))0x752110)(type);
#endif
}

RwBool RpLightDestroy(RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (light) {
        ToRw(light)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpLight*))0x7520D0)(light);
#endif
}

RpLight* RpLightSetRadius(RpLight* light, RwReal radius) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (light) {
        ToRw(light)->radius = radius;
    }
    return light;
#else
    return ((RpLight*(__cdecl *)(RpLight*, RwReal))0x751A70)(light, radius);
#endif
}

RpLight* RpLightSetColor(RpLight* light, const RwRGBAReal* color) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (light && color) {
        ToRw(light)->setColor(color->red, color->green, color->blue);
    }
    return light;
#else
    return ((RpLight*(__cdecl *)(RpLight*, const RwRGBAReal*))0x751A90)(light, color);
#endif
}

RwReal RpLightGetConeAngle(const RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    return light ? ToRw(const_cast<RpLight*>(light))->getAngle() : 0.0f;
#else
    return ((RwReal(__cdecl *)(const RpLight*))0x751AE0)(light);
#endif
}

RpLight* RpLightSetConeAngle(RpLight* light, RwReal angle) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (light) {
        ToRw(light)->setAngle(angle);
    }
    return light;
#else
    return ((RpLight*(__cdecl *)(RpLight*, RwReal))0x751D20)(light, angle);
#endif
}

RwUInt32 RpLightStreamGetSize(const RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    return light ? ToRw(const_cast<RpLight*>(light))->streamGetSize() : 0;
#else
    return ((RwUInt32(__cdecl *)(const RpLight*))0x751E10)(light);
#endif
}

RpLight* RpLightStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Light::streamRead(ToRw(stream)));
#else
    return ((RpLight*(__cdecl *)(RwStream*))0x751F00)(stream);
#endif
}

RpLightChunkInfo* _rpLightChunkInfoRead(RwStream* stream, RpLightChunkInfo* lightChunkInfo, RwInt32* bytesRead) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    (void)lightChunkInfo;
    (void)bytesRead;
    return lightChunkInfo;
#else
    return ((RpLightChunkInfo*(__cdecl *)(RwStream*, RpLightChunkInfo*, RwInt32*))0x752060)(stream, lightChunkInfo, bytesRead);
#endif
}

RwInt32 RpLightRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Light::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x751D60)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RpLightRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Light::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x751D90)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RpLightSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Light::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x751DC0)(pluginID, alwaysCB);
#endif
}

RwInt32 RpLightGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Light::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x751DE0)(pluginID);
#endif
}

RwBool RpLightValidatePlugins(const RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)light;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RpLight*))0x751E00)(light);
#endif
}

void RpD3D9LightSetAttenuationParams(RpLight* light, const RpD3D9AttenuationParams* params) {
    ((void(__cdecl *)(RpLight*, const RpD3D9AttenuationParams*))0x755D20)(light, params);
}

void RpD3D9LightGetAttenuationParams(const RpLight* light, RpD3D9AttenuationParams* params) {
    ((void(__cdecl *)(const RpLight*, RpD3D9AttenuationParams*))0x755D50)(light, params);
}

RwBool _rwD3D9LightsOpen(void) {
    return ((RwBool(__cdecl *)(void))0x755D80)();
}

RwBool _rwD3D9LightsGlobalEnable(RpLightFlag flags) {
    return ((RwBool(__cdecl *)(RpLightFlag))0x756070)(flags);
}

RwBool _rwD3D9LightDirectionalEnable(RpLight* light) {
    return ((RwBool(__cdecl *)(RpLight*))0x756260)(light);
}

RwBool _rwD3D9LightLocalEnable(RpLight* light) {
    return ((RwBool(__cdecl *)(RpLight*))0x756390)(light);
}

void _rwD3D9LightsEnable(RwBool enable, RwUInt32 type) {
    ((void(__cdecl *)(RwBool, RwUInt32))0x756600)(enable, type);
}

void _rwD3D9LightsClose(void) {
    ((void(__cdecl *)(void))0x755FE0)();
}

void RpAtomicSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x749720)(blockSize, numBlocksToPrealloc);
}

void RpClumpSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x749740)(blockSize, numBlocksToPrealloc);
}

RpAtomic* AtomicDefaultRenderCallBack(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (atomic) {
        ToRw(atomic)->render();
    }
    return atomic;
#else
    return ((RpAtomic * (__cdecl *)(RpAtomic*))0x7491C0)(atomic);
#endif
}

void _rpAtomicResyncInterpolatedSphere(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)atomic;
#else
    ((void(__cdecl *)(RpAtomic*))0x7491F0)(atomic);
#endif
}

const RwSphere* RpAtomicGetWorldBoundingSphere(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    return atomic ? reinterpret_cast<const RwSphere*>(ToRw(atomic)->getWorldBoundingSphere()) : nullptr;
#else
    return ((const RwSphere*(__cdecl *)(RpAtomic*))0x749330)(atomic);
#endif
}

void RpClumpGtaCancelStream() {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    plugin::Call<0x72E700>();
#endif
}

RpClump* RpClumpForAllAtomics(RpClump* clump, RpAtomicCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && callback) {
        FORLIST(lnk, ToRw(clump)->atomics) {
            rw::Atomic* a = rw::Atomic::fromClump(lnk);
            if (!callback(FromRw(a), data))
                break;
        }
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RpAtomicCallBack, void*))0x749B70)(clump, callback, data);
#endif
}

RpClump* RpClumpForAllLights(RpClump* clump, RpLightCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && callback) {
        FORLIST(lnk, ToRw(clump)->lights) {
            rw::Light* l = rw::Light::fromClump(lnk);
            if (!callback(FromRw(l), data))
                break;
        }
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RpLightCallBack, void*))0x749C00)(clump, callback, data);
#endif
}

RpClump* RpClumpForAllCameras(RpClump* clump, RwCameraCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && callback) {
        FORLIST(lnk, ToRw(clump)->cameras) {
            rw::Camera* c = rw::Camera::fromClump(lnk);
            if (!callback(FromRw(c), data))
                break;
        }
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RwCameraCallBack, void*))0x749BB0)(clump, callback, data);
#endif
}

RpAtomic* RpAtomicSetFrame(RpAtomic* atomic, RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (atomic) {
        ToRw(atomic)->setFrame(ToRw(frame));
    }
    return atomic;
#else
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RwFrame*))0x74BF20)(atomic, frame);
#endif
}

RpClump* RpClumpCreateSpace(const RwV3d* position, RwReal radius) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)position;
    (void)radius;
    return RpClumpCreate();
#else
    return ((RpClump*(__cdecl *)(const RwV3d*, RwReal))0x749970)(position, radius);
#endif
}

RpClump* RpClumpRender(RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump) {
        ToRw(clump)->render();
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*))0x749B20)(clump);
#endif
}

RpClump* RpClumpRemoveAtomic(RpClump* clump, RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && atomic) {
        ToRw(clump)->removeAtomic(ToRw(atomic));
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RpAtomic*))0x74A4C0)(clump, atomic);
#endif
}

RpClump* RpClumpAddAtomic(RpClump* clump, RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && atomic) {
        ToRw(clump)->addAtomic(ToRw(atomic));
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RpAtomic*))0x74A490)(clump, atomic);
#endif
}

RpClump* RpClumpRemoveLight(RpClump* clump, RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && light) {
        ToRw(clump)->removeLight(ToRw(light));
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RpLight*))0x74A520)(clump, light);
#endif
}

RpClump* RpClumpAddLight(RpClump* clump, RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && light) {
        ToRw(clump)->addLight(ToRw(light));
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RpLight*))0x74A4F0)(clump, light);
#endif
}

RpClump* RpClumpRemoveCamera(RpClump* clump, RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && camera) {
        ToRw(clump)->removeCamera(ToRw(camera));
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RwCamera*))0x74A580)(clump, camera);
#endif
}

RpClump* RpClumpAddCamera(RpClump* clump, RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump && camera) {
        ToRw(clump)->addCamera(ToRw(camera));
    }
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RwCamera*))0x74A550)(clump, camera);
#endif
}

RwBool RpClumpDestroy(RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump) {
        ToRw(clump)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpClump*))0x74A310)(clump);
#endif
}

RpClump* RpClumpCreate(void) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Clump::create());
#else
    return ((RpClump*(__cdecl *)(void))0x74A290)();
#endif
}

RpClump* RpClumpClone(RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    return clump ? FromRw(ToRw(clump)->clone()) : nullptr;
#else
    return ((RpClump*(__cdecl *)(RpClump*))0x749F70)(clump);
#endif
}

RwBool RpAtomicDestroy(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (atomic) {
        ToRw(atomic)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpAtomic*))0x749DC0)(atomic);
#endif
}

RpAtomic* RpAtomicClone(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    return atomic ? FromRw(ToRw(atomic)->clone()) : nullptr;
#else
    return ((RpAtomic*(__cdecl *)(RpAtomic*))0x749E60)(atomic);
#endif
}

RpAtomic* RpAtomicCreate(void) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Atomic::create());
#else
    return ((RpAtomic*(__cdecl *)(void))0x749C50)();
#endif
}

RpAtomic* RpAtomicSetGeometry(RpAtomic* atomic, RpGeometry* geometry, RwUInt32 flags) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (atomic) {
        ToRw(atomic)->setGeometry(ToRw(geometry), flags);
    }
    return atomic;
#else
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RpGeometry*, RwUInt32))0x749D40)(atomic, geometry, flags);
#endif
}

RpClump* RpClumpSetCallBack(RpClump* clump, RpClumpCallBack callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)clump;
    (void)callback;
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RpClumpCallBack))0x74A240)(clump, callback);
#endif
}

RpClumpCallBack RpClumpGetCallBack(const RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)clump;
    return nullptr;
#else
    return ((RpClumpCallBack(__cdecl *)(const RpClump*))0x74A270)(clump);
#endif
}

RwInt32 RpClumpGetNumAtomics(RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    return clump ? ToRw(clump)->countAtomics() : 0;
#else
    return ((RwInt32(__cdecl *)(RpClump*))0x7498E0)(clump);
#endif
}

RwInt32 RpClumpGetNumLights(RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    return clump ? ToRw(clump)->countLights() : 0;
#else
    return ((RwInt32(__cdecl *)(RpClump*))0x749910)(clump);
#endif
}

RwInt32 RpClumpGetNumCameras(RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    return clump ? ToRw(clump)->countCameras() : 0;
#else
    return ((RwInt32(__cdecl *)(RpClump*))0x749940)(clump);
#endif
}

RpClump* RpLightGetClump(const RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    return light ? FromRw(ToRw(light)->clump) : nullptr;
#else
    return ((RpClump*(__cdecl *)(const RpLight*))0x749E40)(light);
#endif
}

RpClump* RwCameraGetClump(const RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    return camera ? FromRw(ToRw(camera)->clump) : nullptr;
#else
    return ((RpClump*(__cdecl *)(const RwCamera*))0x749E50)(camera);
#endif
}

RwUInt32 RpAtomicStreamGetSize(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    return atomic ? ToRw(atomic)->streamGetSize() : 0;
#else
    return ((RwUInt32(__cdecl *)(RpAtomic*))0x74A5B0)(atomic);
#endif
}

RpAtomic* RpAtomicStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    return nullptr;
#else
    return ((RpAtomic*(__cdecl *)(RwStream*))0x74B030)(stream);
#endif
}

RpAtomic* RpAtomicStreamWrite(RpAtomic* atomic, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)atomic;
    (void)stream;
    return atomic;
#else
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RwStream*))0x74A850)(atomic, stream);
#endif
}

RwUInt32 RpClumpStreamGetSize(RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    return clump ? ToRw(clump)->streamGetSize() : 0;
#else
    return ((RwUInt32(__cdecl *)(RpClump*))0x74A5E0)(clump);
#endif
}

RpClump* RpClumpStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (!stream) return nullptr;
    auto* s = ToRw(stream);
    rw::ChunkHeaderInfo header;
    uint32 pos = s->tell();
    if (rw::readChunkHeaderInfo(s, &header)) {
        if (header.type != rw::ID_CLUMP) {
            s->seek(pos, 0);
        }
    }
    return FromRw(rw::Clump::streamRead(s));
#else
    return ((RpClump*(__cdecl *)(RwStream*))0x74B420)(stream);
#endif
}

RpClump* RpClumpStreamWrite(RpClump* clump, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (clump) ToRw(clump)->streamWrite(ToRw(stream));
    return clump;
#else
    return ((RpClump*(__cdecl *)(RpClump*, RwStream*))0x74AA10)(clump, stream);
#endif
}

RpClumpChunkInfo* _rpClumpChunkInfoRead(RwStream* stream, RpClumpChunkInfo* clumpChunkInfo, RwInt32* bytesRead) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    (void)clumpChunkInfo;
    (void)bytesRead;
    return clumpChunkInfo;
#else
    return ((RpClumpChunkInfo*(__cdecl *)(RwStream*, RpClumpChunkInfo*, RwInt32*))0x74BD40)(stream, clumpChunkInfo, bytesRead);
#endif
}

RwInt32 RpAtomicRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Atomic::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74BDA0)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RpClumpRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Clump::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74BDD0)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RpAtomicRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Atomic::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74BE00)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RpAtomicSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Atomic::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74BE30)(pluginID, alwaysCB);
#endif
}

RwInt32 RpAtomicSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Atomic::setStreamRightsCallback(pluginID, (rw::RightsCallback)rightsCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkRightsCallBack))0x74BE50)(pluginID, rightsCB);
#endif
}

RwInt32 RpClumpRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Clump::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74BE70)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RpClumpSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Clump::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74BEA0)(pluginID, alwaysCB);
#endif
}

RwInt32 RpAtomicGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Atomic::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x74BEC0)(pluginID);
#endif
}

RwInt32 RpClumpGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Clump::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x74BEE0)(pluginID);
#endif
}

RwBool RpAtomicValidatePlugins(const RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)atomic;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RpAtomic*))0x74BF00)(atomic);
#endif
}

RwBool RpClumpValidatePlugins(const RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)clump;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RpClump*))0x74BF10)(clump);
#endif
}

RwBool RpAtomicInstance(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (atomic) {
        ToRw(atomic)->instance();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpAtomic*))0x74BF40)(atomic);
#endif
}

RwBool _rpWorldFindBBox(RpWorld* world, RwBBox* boundingBox) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world; (void)boundingBox;
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RpWorld*, RwBBox*))0x74EFA0)(world, boundingBox);
#endif
}

RpWorld* _rpWorldSetupSectorBoundingBoxes(RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*))0x74F020)(world);
#endif
}

void _rpWorldSectorDeinstanceAll(RpSector* sector) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector;
#else
    ((void(__cdecl *)(RpSector*))0x74ECA0)(sector);
#endif
}

void _rpWorldSectorDestroyRecurse(RpSector* sector) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector;
#else
    ((void(__cdecl *)(RpSector*))0x74ED50)(sector);
#endif
}

RwBool _rpWorldForAllGlobalLights(RpLightCallBack callBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)callBack; (void)data;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpLightCallBack, void*))0x74EF10)(callBack, data);
#endif
}

RpWorldSector* _rpWorldSectorForAllLocalLights(RpWorldSector* sector, RpLightCallBack callBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector; (void)callBack; (void)data;
    return sector;
#else
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*, RpLightCallBack, void*))0x74EF60)(sector, callBack, data);
#endif
}

RpWorldSector* _rpSectorDefaultRenderCallBack(RpWorldSector* sector) {
#ifdef NOTSA_STANDALONE_NATIVE
    return sector;
#else
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*))0x74EEC0)(sector);
#endif
}

RpWorld* RpWorldLock(RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*))0x74F1A0)(world);
#endif
}

RpWorld* RpWorldUnlock(RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*))0x74F210)(world);
#endif
}

void _rpWorldRegisterWorld(RpWorld* world, RwUInt32 memorySize) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world; (void)memorySize;
#else
    ((void(__cdecl *)(RpWorld*, RwUInt32))0x74F0C0)(world, memorySize);
#endif
}

void _rpWorldUnregisterWorld(RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world;
#else
    ((void(__cdecl *)(RpWorld*))0x74F140)(world);
#endif
}

RwBool RpWorldPluginAttach() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x74FDA0)();
#endif
}

RpWorld* RpWorldForAllClumps(RpWorld* world, RpClumpCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && fpCallBack) {
        rw::World* rwWorld = ToRw(world);
        FORLIST(lnk, rwWorld->clumps) {
            rw::Clump* clump = rw::Clump::fromWorld(lnk);
            if (!fpCallBack(FromRw(clump), data))
                break;
        }
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpClumpCallBack, void*))0x74FB80)(world, fpCallBack, data);
#endif
}

RpWorld* RpWorldForAllMaterials(RpWorld* world, RpMaterialCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world; (void)fpCallBack; (void)data;
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpMaterialCallBack, void*))0x74FBC0)(world, fpCallBack, data);
#endif
}

RpWorld* RpWorldForAllLights(RpWorld* world, RpLightCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && fpCallBack) {
        rw::World* rwWorld = ToRw(world);
        FORLIST(lnk, rwWorld->globalLights) {
            rw::Light* light = rw::Light::fromWorld(lnk);
            if (!fpCallBack(FromRw(light), data))
                return world;
        }
        FORLIST(lnk, rwWorld->localLights) {
            rw::Light* light = rw::Light::fromWorld(lnk);
            if (!fpCallBack(FromRw(light), data))
                return world;
        }
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpLightCallBack, void*))0x74FC00)(world, fpCallBack, data);
#endif
}

RpWorld* RpWorldForAllWorldSectors(RpWorld* world, RpWorldSectorCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world; (void)fpCallBack; (void)data;
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpWorldSectorCallBack, void*))0x74FC70)(world, fpCallBack, data);
#endif
}

RpWorld* RpWorldRender(RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world) {
        ToRw(world)->render();
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*))0x74F570)(world);
#endif
}

RwBool RpWorldDestroy(RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world) {
        ToRw(world)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpWorld*))0x74F610)(world);
#endif
}

RpWorld* RpWorldCreate(RwBBox* boundingBox) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::World::create(ToRw(boundingBox)));
#else
    return ((RpWorld*(__cdecl *)(RwBBox*))0x74F760)(boundingBox);
#endif
}

RpWorld* RpWorldSetSectorRenderCallBack(RpWorld* world, RpWorldSectorCallBackRender fpCallBack) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world; (void)fpCallBack;
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpWorldSectorCallBackRender))0x74F730)(world, fpCallBack);
#endif
}

RpWorldSectorCallBackRender RpWorldGetSectorRenderCallBack(const RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world;
    return nullptr;
#else
    return ((RpWorldSectorCallBackRender(__cdecl *)(const RpWorld*))0x74F750)(world);
#endif
}

RpWorld* RpWorldSectorGetWorld(const RpWorldSector* sector) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector;
    return nullptr;
#else
    return ((RpWorld*(__cdecl *)(const RpWorldSector*))0x74F4E0)(sector);
#endif
}

RwInt32 RpWorldRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::World::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74FCD0)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RpWorldRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::World::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74FD00)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RpWorldSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::World::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74FD30)(pluginID, alwaysCB);
#endif
}

RwInt32 RpWorldSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::World::setStreamRightsCallback(pluginID, (rw::RightsCallback)rightsCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkRightsCallBack))0x74FD50)(pluginID, rightsCB);
#endif
}

RwInt32 RpWorldGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::World::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x74FD70)(pluginID);
#endif
}

RwBool RpWorldValidatePlugins(RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpWorld*))0x74FD90)(world);
#endif
}

void RpD3D9GeometrySetUsageFlags(RpGeometry* geometry, RpD3D9GeometryUsageFlag flags) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)geometry; (void)flags;
#else
    ((void(__cdecl *)(RpGeometry*, RpD3D9GeometryUsageFlag))0x7588B0)(geometry, flags);
#endif
}

RpD3D9GeometryUsageFlag RpD3D9GeometryGetUsageFlags(const RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)geometry;
    return static_cast<RpD3D9GeometryUsageFlag>(0);
#else
    return ((RpD3D9GeometryUsageFlag(__cdecl *)(const RpGeometry*))0x7588D0)(geometry);
#endif
}

void RpD3D9WorldSectorSetUsageFlags(RpWorldSector* sector, RpD3D9WorldSectorUsageFlag flags) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector; (void)flags;
#else
    ((void(__cdecl *)(RpWorldSector*, RpD3D9WorldSectorUsageFlag))0x7588E0)(sector, flags);
#endif
}

RpD3D9WorldSectorUsageFlag RpD3D9WorldSectorGetUsageFlags(const RpWorldSector* sector) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector;
    return static_cast<RpD3D9WorldSectorUsageFlag>(0);
#else
    return ((RpD3D9WorldSectorUsageFlag(__cdecl *)(const RpWorldSector*))0x758900)(sector);
#endif
}

void RxD3D9AllInOneSetInstanceCallBack(RxPipelineNode* node, RxD3D9AllInOneInstanceCallBack callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)node; (void)callback;
#else
    ((void(__cdecl *)(RxPipelineNode*, RxD3D9AllInOneInstanceCallBack))0x757380)(node, callback);
#endif
}

RxD3D9AllInOneInstanceCallBack RxD3D9AllInOneGetInstanceCallBack(RxPipelineNode* node) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)node;
    return nullptr;
#else
    return ((RxD3D9AllInOneInstanceCallBack(__cdecl *)(RxPipelineNode*))0x757390)(node);
#endif
}

void RxD3D9AllInOneSetReinstanceCallBack(RxPipelineNode* node, RxD3D9AllInOneReinstanceCallBack callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)node; (void)callback;
#else
    ((void(__cdecl *)(RxPipelineNode*, RxD3D9AllInOneReinstanceCallBack))0x7573A0)(node, callback);
#endif
}

RxD3D9AllInOneReinstanceCallBack RxD3D9AllInOneGetReinstanceCallBack(RxPipelineNode* node) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)node;
    return nullptr;
#else
    return ((RxD3D9AllInOneReinstanceCallBack(__cdecl *)(RxPipelineNode*))0x7573B0)(node);
#endif
}

void RxD3D9AllInOneSetLightingCallBack(RxPipelineNode* node, RxD3D9AllInOneLightingCallBack callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)node; (void)callback;
#else
    ((void(__cdecl *)(RxPipelineNode*, RxD3D9AllInOneLightingCallBack))0x7573C0)(node, callback);
#endif
}

RxD3D9AllInOneLightingCallBack RxD3D9AllInOneGetLightingCallBack(RxPipelineNode* node) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)node;
    return nullptr;
#else
    return ((RxD3D9AllInOneLightingCallBack(__cdecl *)(RxPipelineNode*))0x7573D0)(node);
#endif
}

void RxD3D9AllInOneSetRenderCallBack(RxPipelineNode* node, RxD3D9AllInOneRenderCallBack callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)node; (void)callback;
#else
    ((void(__cdecl *)(RxPipelineNode*, RxD3D9AllInOneRenderCallBack))0x7573E0)(node, callback);
#endif
}

RxD3D9AllInOneRenderCallBack RxD3D9AllInOneGetRenderCallBack(RxPipelineNode* node) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)node;
    return nullptr;
#else
    return ((RxD3D9AllInOneRenderCallBack(__cdecl *)(RxPipelineNode*))0x7573F0)(node);
#endif
}

void _rpD3D9AddDynamicGeometry(RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)geometry;
#else
    ((void(__cdecl *)(RpGeometry*))0x74E970)(geometry);
#endif
}

void _rpD3D9RemoveDynamicGeometry(RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)geometry;
#else
    ((void(__cdecl *)(RpGeometry*))0x74E9E0)(geometry);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationGetSize(RwUInt32 type) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32))0x7522E0)(type);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationGetStride(const void* vertexDeclaration) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)vertexDeclaration;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(const void*))0x7522F0)(vertexDeclaration);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationInstV3d(RwUInt32 type, RwUInt8* mem, const RwV3d* src, RwInt32 numVerts, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)mem; (void)src; (void)numVerts; (void)stride;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV3d*, RwInt32, RwUInt32))0x752AD0)(type, mem, src, numVerts, stride);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationInstV3dComp(RwUInt32 type, RwUInt8* mem, const RpVertexNormal* src, RwInt32 numVerts, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)mem; (void)src; (void)numVerts; (void)stride;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RpVertexNormal*, RwInt32, RwUInt32))0x7531B0)(type, mem, src, numVerts, stride);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationInstV3dMorph(RwUInt32 type, RwUInt8* mem, const RwV3d* src1, const RwV3d* src2, RwReal scale, RwInt32 numVerts, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)mem; (void)src1; (void)src2; (void)scale; (void)numVerts; (void)stride;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV3d*, const RwV3d*, RwReal, RwInt32, RwUInt32))0x753B60)(type, mem, src1, src2, scale, numVerts, stride);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationInstV2d(RwUInt32 type, RwUInt8* mem, const RwV2d* src, RwInt32 numVerts, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)mem; (void)src; (void)numVerts; (void)stride;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV2d*, RwInt32, RwUInt32))0x7544E0)(type, mem, src, numVerts, stride);
#endif
}

RwBool _rpD3D9VertexDeclarationInstColor(RwUInt8* mem, const RwRGBA* color, RwInt32 numVerts, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)mem; (void)color; (void)numVerts; (void)stride;
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RwUInt8*, const RwRGBA*, RwInt32, RwUInt32))0x754AE0)(mem, color, numVerts, stride);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationInstIndices(RwUInt32 type, RwUInt8* mem, const RwUInt32* indices, RwInt32 numVerts, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)mem; (void)indices; (void)numVerts; (void)stride;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwUInt32*, RwInt32, RwUInt32))0x754B40)(type, mem, indices, numVerts, stride);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationInstIndicesRemap(RwUInt32 type, RwUInt8* mem, const RwUInt32* indices, const RwUInt8* remap, RwInt32 numVerts, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)mem; (void)indices; (void)remap; (void)numVerts; (void)stride;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwUInt32*, const RwUInt8*, RwInt32, RwUInt32))0x754C80)(type, mem, indices, remap, numVerts, stride);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationInstWeights(RwUInt32 type, RwUInt8* mem, const RwV4d* src, RwInt32 numVerts, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)mem; (void)src; (void)numVerts; (void)stride;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV4d*, RwInt32, RwUInt32))0x752320)(type, mem, src, numVerts, stride);
#endif
}

RwUInt32 _rpD3D9VertexDeclarationInstTangent(RwUInt32 type, RwUInt8* mem, const RwV3d* pos, const RwTexCoords* texCoord, RxD3D9ResEntryHeader* meshHeader, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)mem; (void)pos; (void)texCoord; (void)meshHeader; (void)stride;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV3d*, const RwTexCoords*, RxD3D9ResEntryHeader*, RwUInt32))0x754E20)(type, mem, pos, texCoord, meshHeader, stride);
#endif
}

void _rpD3D9VertexDeclarationUnInstV3d(RwUInt32 type, RwV3d* dst, const RwUInt8* src) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)dst; (void)src;
#else
    ((void(__cdecl *)(RwUInt32, RwV3d*, const RwUInt8*))0x7551F0)(type, dst, src);
#endif
}

void _rpD3D9VertexDeclarationUnInstV2d(RwUInt32 type, RwV2d* dst, const RwUInt8* src) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)type; (void)dst; (void)src;
#else
    ((void(__cdecl *)(RwUInt32, RwV2d*, const RwUInt8*))0x7555E0)(type, dst, src);
#endif
}

void _rpD3D9GetMinMaxValuesV3d(const RwV3d* src, RwInt32 numElements, RwV3d* min, RwV3d* max) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)src; (void)numElements; (void)min; (void)max;
#else
    ((void(__cdecl *)(const RwV3d*, RwInt32, RwV3d*, RwV3d*))0x755830)(src, numElements, min, max);
#endif
}

void _rpD3D9GetMinMaxValuesV2d(const RwV2d* src, RwInt32 numElements, RwV2d* min, RwV2d* max) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)src; (void)numElements; (void)min; (void)max;
#else
    ((void(__cdecl *)(const RwV2d*, RwInt32, RwV2d*, RwV2d*))0x7558F0)(src, numElements, min, max);
#endif
}

RwUInt32 _rpD3D9FindFormatV3d(const RwV3d* src, RwInt32 numElements) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)src; (void)numElements;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(const RwV3d*, RwInt32))0x755980)(src, numElements);
#endif
}

RwUInt32 _rpD3D9FindFormatV2d(const RwV2d* src, RwInt32 numElements) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)src; (void)numElements;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(const RwV2d*, RwInt32))0x755AA0)(src, numElements);
#endif
}

RxPipeline* RpWorldSetDefaultSectorPipeline(RxPipeline* pipeline) {
#ifdef NOTSA_STANDALONE_NATIVE
    return pipeline;
#else
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x75E270)(pipeline);
#endif
}

RxPipeline* RpAtomicSetDefaultPipeline(RxPipeline* pipeline) {
#ifdef NOTSA_STANDALONE_NATIVE
    return pipeline;
#else
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x75E2A0)(pipeline);
#endif
}

RxPipeline* RpMaterialSetDefaultPipeline(RxPipeline* pipeline) {
#ifdef NOTSA_STANDALONE_NATIVE
    return pipeline;
#else
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x75E2D0)(pipeline);
#endif
}

const RpGeometry* RpGeometryIsCorrectlySorted(const RpGeometry* geometry, RwBool* result) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (result) *result = TRUE;
    return geometry;
#else
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, RwBool*))0x75D9D0)(geometry, result);
#endif
}

RpGeometry* RpGeometrySortByMaterial(const RpGeometry* geometry, RpGeometrySortByMaterialCallBack callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)callback;
    return const_cast<RpGeometry*>(geometry);
#else
    return ((RpGeometry*(__cdecl *)(const RpGeometry*, RpGeometrySortByMaterialCallBack))0x75DAE0)(geometry, callback);
#endif
}

void RpTieSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)blockSize; (void)numBlocksToPrealloc;
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x74FF60)(blockSize, numBlocksToPrealloc);
#endif
}

void RpLightTieSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)blockSize; (void)numBlocksToPrealloc;
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x74FF80)(blockSize, numBlocksToPrealloc);
#endif
}

RpWorld* RpWorldRemoveCamera(RpWorld* world, RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && camera) {
        ToRw(world)->removeCamera(ToRw(camera));
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RwCamera*))0x750F50)(world, camera);
#endif
}

RpWorld* RpWorldAddCamera(RpWorld* world, RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && camera) {
        ToRw(world)->addCamera(ToRw(camera));
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RwCamera*))0x750F20)(world, camera);
#endif
}

RpWorld* RwCameraGetWorld(const RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    return camera ? FromRw(ToRw(camera)->world) : nullptr;
#else
    return ((RpWorld*(__cdecl *)(const RwCamera*))0x750F80)(camera);
#endif
}

RpWorld* RpWorldRemoveAtomic(RpWorld* world, RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && atomic) {
        ToRw(world)->removeAtomic(ToRw(atomic));
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpAtomic*))0x750FC0)(world, atomic);
#endif
}

RpWorld* RpWorldAddAtomic(RpWorld* world, RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && atomic) {
        ToRw(world)->addAtomic(ToRw(atomic));
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpAtomic*))0x750F90)(world, atomic);
#endif
}

RpWorld* RpAtomicGetWorld(const RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    return atomic ? FromRw(ToRw(atomic)->world) : nullptr;
#else
    return ((RpWorld*(__cdecl *)(const RpAtomic*))0x751050)(atomic);
#endif
}

RpWorld* RpWorldAddClump(RpWorld* world, RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && clump) {
        ToRw(world)->addClump(ToRw(clump));
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpClump*))0x751300)(world, clump);
#endif
}

RpWorld* RpWorldRemoveClump(RpWorld* world, RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && clump) {
        ToRw(world)->removeClump(ToRw(clump));
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpClump*))0x751460)(world, clump);
#endif
}

RpWorld* RpClumpGetWorld(const RpClump* clump) {
#ifdef NOTSA_STANDALONE_NATIVE
    return clump ? FromRw(ToRw(clump)->world) : nullptr;
#else
    return ((RpWorld*(__cdecl *)(const RpClump*))0x7516B0)(clump);
#endif
}

RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && light) {
        ToRw(world)->addLight(ToRw(light));
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpLight*))0x751910)(world, light);
#endif
}

RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (world && light) {
        ToRw(world)->removeLight(ToRw(light));
    }
    return world;
#else
    return ((RpWorld*(__cdecl *)(RpWorld*, RpLight*))0x751960)(world, light);
#endif
}

RpWorld* RpLightGetWorld(const RpLight* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    return light ? FromRw(ToRw(light)->world) : nullptr;
#else
    return ((RpWorld*(__cdecl *)(const RpLight*))0x7519E0)(light);
#endif
}

RwCamera* RwCameraForAllClumpsInFrustum(RwCamera* camera, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)camera; (void)data;
    return camera;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*, void*))0x7516C0)(camera, data);
#endif
}

RwCamera* RwCameraForAllAtomicsInFrustum(RwCamera* camera, RpAtomicCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera && callback && ToRw(camera)->world) {
        FORLIST(lnk, ToRw(camera)->world->clumps) {
            rw::Clump* clump = rw::Clump::fromWorld(lnk);
            FORLIST(alnk, clump->atomics) {
                rw::Atomic* a = rw::Atomic::fromClump(alnk);
                if (!callback(FromRw(a), data))
                    return camera;
            }
        }
    }
    return camera;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*, RpAtomicCallBack, void*))0x7517F0)(camera, callback, data);
#endif
}

RwCamera* RwCameraForAllSectorsInFrustum(RwCamera* camera, RpWorldSectorCallBack callBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)camera; (void)callBack; (void)data;
    return camera;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*, RpWorldSectorCallBack, void*))0x751660)(camera, callBack, data);
#endif
}

RpLight* RpLightForAllWorldSectors(RpLight* light, RpWorldSectorCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)light; (void)callback; (void)data;
    return light;
#else
    return ((RpLight*(__cdecl *)(RpLight*, RpWorldSectorCallBack, void*))0x7519F0)(light, callback, data);
#endif
}

RpAtomic* RpAtomicForAllWorldSectors(RpAtomic* atomic, RpWorldSectorCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)atomic; (void)callback; (void)data;
    return atomic;
#else
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RpWorldSectorCallBack, void*))0x751060)(atomic, callback, data);
#endif
}

RpWorldSector* RpWorldSectorForAllAtomics(RpWorldSector* sector, RpAtomicCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector; (void)callback; (void)data;
    return sector;
#else
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*, RpAtomicCallBack, void*))0x7510A0)(sector, callback, data);
#endif
}

RpWorldSector* RpWorldSectorForAllCollisionAtomics(RpWorldSector* sector, RpAtomicCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector; (void)callback; (void)data;
    return sector;
#else
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*, RpAtomicCallBack, void*))0x751140)(sector, callback, data);
#endif
}

RpWorldSector* RpWorldSectorForAllLights(RpWorldSector* sector, RpLightCallBack callback, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)sector; (void)callback; (void)data;
    return sector;
#else
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*, RpLightCallBack, void*))0x7511E0)(sector, callback, data);
#endif
}

RwUInt32 RpWorldStreamGetSize(const RpWorld* world) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(const RpWorld*))0x761EA0)(world);
#endif
}

RpWorld* RpWorldStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    return nullptr;
#else
    return ((RpWorld*(__cdecl *)(RwStream*))0x762960)(stream);
#endif
}

const RpWorld* RpWorldStreamWrite(const RpWorld* world, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)world; (void)stream;
    return world;
#else
    return ((const RpWorld*(__cdecl *)(const RpWorld*, RwStream*))0x762150)(world, stream);
#endif
}

RpWorldSectorChunkInfo* _rpWorldSectorChunkInfoRead(RwStream* stream, RpWorldSectorChunkInfo* worldSectorChunkInfo, RwInt32* bytesRead) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream; (void)bytesRead;
    return worldSectorChunkInfo;
#else
    return ((RpWorldSectorChunkInfo*(__cdecl *)(RwStream*, RpWorldSectorChunkInfo*, RwInt32*))0x7635B0)(stream, worldSectorChunkInfo, bytesRead);
#endif
}

RpPlaneSectorChunkInfo* _rpPlaneSectorChunkInfoRead(RwStream* stream, RpPlaneSectorChunkInfo* planeSectorChunkInfo, RwInt32* bytesRead) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream; (void)bytesRead;
    return planeSectorChunkInfo;
#else
    return ((RpPlaneSectorChunkInfo*(__cdecl *)(RwStream*, RpPlaneSectorChunkInfo*, RwInt32*))0x763620)(stream, planeSectorChunkInfo, bytesRead);
#endif
}

RpWorldChunkInfo* _rpWorldChunkInfoRead(RwStream* stream, RpWorldChunkInfo* worldChunkInfo, RwInt32* bytesRead) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream; (void)bytesRead;
    return worldChunkInfo;
#else
    return ((RpWorldChunkInfo*(__cdecl *)(RwStream*, RpWorldChunkInfo*, RwInt32*))0x763690)(stream, worldChunkInfo, bytesRead);
#endif
}


/****************************************************************************
_rwD3D9EnableClippingIfNeeded
Purpose:
On entry:
On exit :
*/
void
_rwD3D9EnableClippingIfNeeded(void *object,
    RwUInt32 type)
{
#ifndef NOTSA_STANDALONE_NATIVE
    RwCamera    *camera;
    RwBool      fullyInsideFrustum;

    RWFUNCTION(RWSTRING("_rwD3D9EnableClippingIfNeeded"));
    RWASSERT(object != NULL);

    camera = RwCameraGetCurrentCamera();
    RWASSERT(camera != NULL);

    if (type == rpATOMIC)
    {
        RpAtomic    *atomic;

        atomic = (RpAtomic *)object;

        fullyInsideFrustum =
            RwD3D9CameraIsSphereFullyInsideFrustum(camera,
                RpAtomicGetWorldBoundingSphere(atomic));
    }
    else
    {
        const RpWorldSector   *worldSector;

        RWASSERT(type == ((RwUInt8)rwSECTORATOMIC));

        worldSector = (const RpWorldSector *)object;

        fullyInsideFrustum =
            RwD3D9CameraIsBBoxFullyInsideFrustum(camera,
                RpWorldSectorGetTightBBox(worldSector));
    }

    RwD3D9SetRenderState(D3DRS_CLIPPING, (fullyInsideFrustum == FALSE));

    RWRETURNVOID();
#else
    (void)object;
    (void)type;
#endif
}
