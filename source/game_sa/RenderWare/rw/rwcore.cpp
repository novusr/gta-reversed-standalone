#ifndef NOTSA_STANDALONE_NATIVE
#include "StdInc.h"
#else
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "Base.h"
#include "RenderWare/RenderWare.h"
#endif

#include "rwcore.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
using namespace notsa::rwbridge;
#endif

void RwCoreInjectHooks() {
#ifdef NOTSA_STANDALONE_NATIVE
    return;
#else
    RH_ScopedCategory("Renderware");
    RH_ScopedNamespaceName("RwCore");

    RH_ScopedGlobalInstall(RwCameraBeginUpdate, 0x7EE190);
    RH_ScopedGlobalInstall(RwCameraEndUpdate, 0x7EE180);
    RH_ScopedGlobalInstall(RwCameraClear, 0x7EE340);
    RH_ScopedGlobalInstall(RwCameraShowRaster, 0x7EE370);
#endif
}

RxHeap* RxHeapCreate(RwUInt32 size) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RxHeap*(__cdecl *)(RwUInt32))0x809F90)(size);
#endif
}

void RxHeapDestroy(RxHeap* heap) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)heap;
#else
    ((void(__cdecl *)(RxHeap*))0x809F30)(heap);
#endif
}

RwBool _rxHeapReset(RxHeap* heap) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)heap;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RxHeap*))0x809EC0)(heap);
#endif
}

void* RxHeapAlloc(RxHeap* heap, RwUInt32 size) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)heap;
    return malloc(size);
#else
    return ((void*(__cdecl *)(RxHeap*, RwUInt32))0x809AA0)(heap, size);
#endif
}

void RxHeapFree(RxHeap* heap, void* block) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)heap;
    free(block);
#else
    ((void(__cdecl *)(RxHeap*, void*))0x8098B0)(heap, block);
#endif
}

void* RxHeapRealloc(RxHeap* heap, void* block, RwUInt32 newSize, RwBool allowCopy) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)heap;
    (void)allowCopy;
    return realloc(block, newSize);
#else
    return ((void*(__cdecl *)(RxHeap*, void*, RwUInt32, RwBool))0x809D10)(heap, block, newSize, allowCopy);
#endif
}

void RxPipelineSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)blockSize;
    (void)numBlocksToPrealloc;
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x804FC0)(blockSize, numBlocksToPrealloc);
#endif
}

RwBool _rxPipelineOpen() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x804FE0)();
#endif
}

RwBool _rxPipelineClose() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x804F60)();
#endif
}

RxPipeline* RxPipelineCreate() {
#ifdef NOTSA_STANDALONE_NATIVE
    return new RxPipeline{};
#else
    return ((RxPipeline*(__cdecl *)(void))0x8057B0)();
#endif
}

void _rxPipelineDestroy(RxPipeline* Pipeline) {
#ifdef NOTSA_STANDALONE_NATIVE
    delete Pipeline;
#else
    ((void(__cdecl *)(RxPipeline*))0x805820)(Pipeline);
#endif
}

RxHeap* RxHeapGetGlobalHeap() {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RxHeap*(__cdecl *)(void))0x8052F0)();
#endif
}

RxPipeline* RxPipelineExecute(RxPipeline* pipeline, void* data, RwBool heapReset) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)data;
    (void)heapReset;
    return pipeline;
#else
    return ((RxPipeline*(__cdecl *)(RxPipeline*, void*, RwBool))0x805710)(pipeline, data, heapReset);
#endif
}

RxPacket* RxPacketCreate(RxPipelineNode* node) {
    return ((RxPacket*(__cdecl *)(RxPipelineNode*))0x805300)(node);
}

RxCluster* RxClusterSetStride(RxCluster* cluster, RwInt32 stride) {
    return ((RxCluster*(__cdecl *)(RxCluster*, RwInt32))0x805330)(cluster, stride);
}

RxCluster* RxClusterSetExternalData(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements) {
    return ((RxCluster*(__cdecl *)(RxCluster*, void*, RwInt32, RwInt32))0x805340)(cluster, data, stride, numElements);
}

RxCluster* RxClusterSetData(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements) {
    return ((RxCluster*(__cdecl *)(RxCluster*, void*, RwInt32, RwInt32))0x8053A0)(cluster, data, stride, numElements);
}

void _rxPacketDestroy(RxPacket* Packet) {
    ((void(__cdecl *)(RxPacket*))0x80F070)(Packet);
}

RxCluster* RxClusterInitializeData(RxCluster* cluster, RwUInt32 numElements, RwUInt16 stride) {
    return ((RxCluster*(__cdecl *)(RxCluster*, RwUInt32, RwUInt16))0x805400)(cluster, numElements, stride);
}

RxCluster* RxClusterResizeData(RxCluster* CurrentCluster, RwUInt32 NumElements) {
    return ((RxCluster*(__cdecl *)(RxCluster*, RwUInt32))0x805470)(CurrentCluster, NumElements);
}

RxCluster* RxClusterDestroyData(RxCluster* CurrentCluster) {
    return ((RxCluster*(__cdecl *)(RxCluster*))0x8054C0)(CurrentCluster);
}

RxCluster* RxClusterLockWrite(RxPacket* packet, RwUInt32 clusterIndex, RxPipelineNode* node) {
    return ((RxCluster*(__cdecl *)(RxPacket*, RwUInt32, RxPipelineNode*))0x8054F0)(packet, clusterIndex, node);
}

void RxClusterUnlock(RxCluster* cluster) {
    ((void(__cdecl *)(RxCluster*))0x8055C0)(cluster);
}

RwUInt32 RxPipelineNodeSendConfigMsg(RxPipelineNode* dest, RwUInt32 msg, RwUInt32 intparam, void* ptrparam) {
    return ((RwUInt32(__cdecl *)(RxPipelineNode*, RwUInt32, RwUInt32, void*))0x8055D0)(dest, msg, intparam, ptrparam);
}

RxPipelineNode* RxPipelineNodeForAllConnectedOutputs(RxPipelineNode* node, RxPipeline* pipeline, RxPipelineNodeOutputCallBack callbackfn, void* callbackdata) {
    return ((RxPipelineNode*(__cdecl *)(RxPipelineNode*, RxPipeline*, RxPipelineNodeOutputCallBack, void*))0x8055F0)(node, pipeline, callbackfn, callbackdata);
}

RxPipelineCluster* RxPipelineNodeGetPipelineCluster(RxPipelineNode* node, RwUInt32 clustersOfInterestIndex) {
    return ((RxPipelineCluster*(__cdecl *)(RxPipelineNode*, RwUInt32))0x805680)(node, clustersOfInterestIndex);
}

RwUInt32 RxPipelineClusterGetCreationAttributes(RxPipelineCluster* cluster) {
    return ((RwUInt32(__cdecl *)(RxPipelineCluster*))0x8056B0)(cluster);
}

RxPipelineCluster* RxPipelineClusterSetCreationAttributes(RxPipelineCluster* cluster, RwUInt32 creationAttributes) {
    return ((RxPipelineCluster*(__cdecl *)(RxPipelineCluster*, RwUInt32))0x8056C0)(cluster, creationAttributes);
}

RwUInt32 RxClusterGetAttributes(RxCluster* cluster) {
    return ((RwUInt32(__cdecl *)(RxCluster*))0x8056E0)(cluster);
}

RxCluster* RxClusterSetAttributes(RxCluster* cluster, RwUInt32 attributes) {
    return ((RxCluster*(__cdecl *)(RxCluster*, RwUInt32))0x8056F0)(cluster, attributes);
}

#ifdef NOTSA_STANDALONE_NATIVE
RxNodeOutput RxPipelineNodeFindOutputByName(RxPipelineNode* node, const RwChar* outputname) {
    (void)node; (void)outputname; return 0;
}

RxNodeOutput RxPipelineNodeFindOutputByIndex(RxPipelineNode* node, RwUInt32 outputindex) {
    (void)node; (void)outputindex; return 0;
}

RxNodeInput RxPipelineNodeFindInput(RxPipelineNode* node) {
    (void)node; return 0;
}

RxNodeDefinition* RxPipelineNodeCloneDefinition(RxPipelineNode* node, RxClusterDefinition* cluster2add) {
    (void)node; (void)cluster2add; return nullptr;
}

RxPipeline* RxPipelineNodeRequestCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* clusterDef) {
    (void)node; (void)clusterDef; return pipeline;
}

RxPipeline* RxPipelineNodeReplaceCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* oldClusterDef, RxClusterDefinition* newClusterDef) {
    (void)node; (void)oldClusterDef; (void)newClusterDef; return pipeline;
}

void* RxPipelineNodeGetInitData(RxPipelineNode* node) {
    (void)node; return nullptr;
}

void* RxPipelineNodeCreateInitData(RxPipelineNode* node, RwUInt32 size) {
    (void)node; return malloc(size);
}

RxPipeline* RxPipelineClone(RxPipeline* pipeline) {
    (void)pipeline; return nullptr;
}

RxPipelineNode* RxPipelineFindNodeByName(RxPipeline* pipeline, const RwChar* name, RxPipelineNode* start, RwInt32* nodeIndex) {
    (void)pipeline; (void)name; (void)start; if (nodeIndex) *nodeIndex = -1; return nullptr;
}

RxPipelineNode* RxPipelineFindNodeByIndex(RxPipeline* pipeline, RwUInt32 nodeindex) {
    (void)pipeline; (void)nodeindex; return nullptr;
}

RxLockedPipe* RxPipelineLock(RxPipeline* pipeline) {
    return (RxLockedPipe*)pipeline;
}

RxPipeline* RxLockedPipeUnlock(RxLockedPipe* pipeline) {
    return (RxPipeline*)pipeline;
}

RxPipeline* RxLockedPipeReplaceNode(RxLockedPipe* pipeline, RxPipelineNode* node, RxNodeDefinition* nodeDef) {
    (void)node; (void)nodeDef; return (RxPipeline*)pipeline;
}

RxPipeline* RxLockedPipeDeleteNode(RxLockedPipe* pipeline, RxPipelineNode* node) {
    (void)node; return (RxPipeline*)pipeline;
}

RxPipeline* RxLockedPipeSetEntryPoint(RxLockedPipe* pipeline, RxNodeInput in) {
    (void)in; return (RxPipeline*)pipeline;
}

RxLockedPipe* RxLockedPipeAddFragment(RxLockedPipe* pipeline, RwUInt32* firstIndex, RxNodeDefinition* nodeDef0, RxNodeDefinition* __va_end__) {
    (void)firstIndex; (void)nodeDef0; (void)__va_end__; return pipeline;
}

RxPipelineNode* RxLockedPipeGetEntryPoint(RxLockedPipe* pipeline) {
    (void)pipeline; return nullptr;
}

RxPipeline* RxLockedPipeAddPath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in) {
    (void)out; (void)in; return (RxPipeline*)pipeline;
}

RxPipeline* RxLockedPipeDeletePath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in) {
    (void)out; (void)in; return (RxPipeline*)pipeline;
}

RxPipeline* RxPipelineInsertDebugNode(RxPipeline* pipeline, RxPipelineNode* before, RxPipelineNode* after, RxNodeDefinition* debugNode) {
    (void)before; (void)after; (void)debugNode; return pipeline;
}

void RwD3D9VertexBufferManagerChangeDefaultSize(RwUInt32 defaultSize) {
    (void)defaultSize;
}

RwBool RwD3D9CreateVertexBuffer(RwUInt32 stride, RwUInt32 size, void* vertexBuffer, RwUInt32* offset) {
    (void)stride; (void)size; (void)vertexBuffer; (void)offset; return FALSE;
}

void RwD3D9DestroyVertexBuffer(RwUInt32 stride, RwUInt32 size, void* vertexBuffer, RwUInt32 offset) {
    (void)stride; (void)size; (void)vertexBuffer; (void)offset;
}

RwBool RwD3D9DynamicVertexBufferCreate(RwUInt32 size, void* vertexBuffer) {
    (void)size; (void)vertexBuffer; return FALSE;
}

void RwD3D9DynamicVertexBufferDestroy() {}

RwBool RwD3D9DynamicVertexBufferLock(RwUInt32 vertexSize, RwUInt32 numVertex, void* vertexBufferOut, void* vertexDataOut, RwUInt32* baseIndexOut) {
    (void)vertexSize; (void)numVertex; (void)vertexBufferOut; (void)vertexDataOut; (void)baseIndexOut; return FALSE;
}

RwBool RwD3D9DynamicVertexBufferUnlock() {
    return TRUE;
}
#else
RxNodeOutput RxPipelineNodeFindOutputByName(RxPipelineNode* node, const RwChar* outputname) {
    return ((RxNodeOutput(__cdecl *)(RxPipelineNode*, const RwChar*))0x805D10)(node, outputname);
}

RxNodeOutput RxPipelineNodeFindOutputByIndex(RxPipelineNode* node, RwUInt32 outputindex) {
    return ((RxNodeOutput(__cdecl *)(RxPipelineNode*, RwUInt32))0x805D70)(node, outputindex);
}

RxNodeInput RxPipelineNodeFindInput(RxPipelineNode* node) {
    return ((RxNodeInput(__cdecl *)(RxPipelineNode*))0x805DA0)(node);
}

RxNodeDefinition* RxPipelineNodeCloneDefinition(RxPipelineNode* node, RxClusterDefinition* cluster2add) {
    return ((RxNodeDefinition*(__cdecl *)(RxPipelineNode*, RxClusterDefinition*))0x8059C0)(node, cluster2add);
}

RxPipeline* RxPipelineNodeRequestCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* clusterDef) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*, RxPipelineNode*, RxClusterDefinition*))0x805DB0)(pipeline, node, clusterDef);
}

RxPipeline* RxPipelineNodeReplaceCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* oldClusterDef, RxClusterDefinition* newClusterDef) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*, RxPipelineNode*, RxClusterDefinition*, RxClusterDefinition*))0x805E20)(pipeline, node, oldClusterDef, newClusterDef);
}

void* RxPipelineNodeGetInitData(RxPipelineNode* node) {
    return ((void*(__cdecl *)(RxPipelineNode*))0x805F30)(node);
}

void* RxPipelineNodeCreateInitData(RxPipelineNode* node, RwUInt32 size) {
    return ((void*(__cdecl *)(RxPipelineNode*, RwUInt32))0x805EA0)(node, size);
}

RxPipeline* RxPipelineClone(RxPipeline* pipeline) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x806AC0)(pipeline);
}

RxPipelineNode* RxPipelineFindNodeByName(RxPipeline* pipeline, const RwChar* name, RxPipelineNode* start, RwInt32* nodeIndex) {
    return ((RxPipelineNode*(__cdecl *)(RxPipeline*, const RwChar*, RxPipelineNode*, RwInt32*))0x806B30)(pipeline, name, start, nodeIndex);
}

RxPipelineNode* RxPipelineFindNodeByIndex(RxPipeline* pipeline, RwUInt32 nodeindex) {
    return ((RxPipelineNode*(__cdecl *)(RxPipeline*, RwUInt32))0x806BC0)(pipeline, nodeindex);
}

RxLockedPipe* RxPipelineLock(RxPipeline* pipeline) {
    return ((RxLockedPipe*(__cdecl *)(RxPipeline*))0x806990)(pipeline);
}

RxPipeline* RxLockedPipeUnlock(RxLockedPipe* pipeline) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*))0x805F40)(pipeline);
}

RxPipeline* RxLockedPipeReplaceNode(RxLockedPipe* pipeline, RxPipelineNode* node, RxNodeDefinition* nodeDef) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxPipelineNode*, RxNodeDefinition*))0x806F20)(pipeline, node, nodeDef);
}

RxPipeline* RxLockedPipeDeleteNode(RxLockedPipe* pipeline, RxPipelineNode* node) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxPipelineNode*))0x807040)(pipeline, node);
}

RxPipeline* RxLockedPipeSetEntryPoint(RxLockedPipe* pipeline, RxNodeInput in) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxNodeInput))0x807070)(pipeline, in);
}

RxLockedPipe* RxLockedPipeAddFragment(RxLockedPipe* pipeline, RwUInt32* firstIndex, RxNodeDefinition* nodeDef0, RxNodeDefinition* __va_end__) {
    return plugin::CallAndReturn<RxPipeline*, 0x806BE0, RxLockedPipe*, RwUInt32*, RxNodeDefinition*, RxNodeDefinition*>(pipeline, firstIndex, nodeDef0, __va_end__);
}

RxPipelineNode* RxLockedPipeGetEntryPoint(RxLockedPipe* pipeline) {
    return ((RxPipelineNode*(__cdecl *)(RxLockedPipe*))0x8070D0)(pipeline);
}

RxPipeline* RxLockedPipeAddPath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxNodeOutput, RxNodeInput))0x807100)(pipeline, out, in);
}

RxPipeline* RxLockedPipeDeletePath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxNodeOutput, RxNodeInput))0x807170)(pipeline, out, in);
}

RxPipeline* RxPipelineInsertDebugNode(RxPipeline* pipeline, RxPipelineNode* before, RxPipelineNode* after, RxNodeDefinition* debugNode) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*, RxPipelineNode*, RxPipelineNode*, RxNodeDefinition*))0x8071B0)(pipeline, before, after, debugNode);
}

void RwD3D9VertexBufferManagerChangeDefaultSize(RwUInt32 defaultSize) {
    ((void(__cdecl *)(RwUInt32))0x7F57F0)(defaultSize);
}

RwBool RwD3D9CreateVertexBuffer(RwUInt32 stride, RwUInt32 size, void* vertexBuffer, RwUInt32* offset) {
    return ((RwBool(__cdecl *)(RwUInt32, RwUInt32, void*, RwUInt32*))0x7F5500)(stride, size, vertexBuffer, offset);
}

void RwD3D9DestroyVertexBuffer(RwUInt32 stride, RwUInt32 size, void* vertexBuffer, RwUInt32 offset) {
    ((void(__cdecl *)(RwUInt32, RwUInt32, void*, RwUInt32))0x7F56A0)(stride, size, vertexBuffer, offset);
}

RwBool RwD3D9DynamicVertexBufferCreate(RwUInt32 size, void* vertexBuffer) {
    return ((RwBool(__cdecl *)(RwUInt32, void*))0x7F5A00)(size, vertexBuffer);
}

void RwD3D9DynamicVertexBufferDestroy() {
    ((void(__cdecl *)(void))0x7F5AE0)();
}

RwBool RwD3D9DynamicVertexBufferLock(RwUInt32 vertexSize, RwUInt32 numVertex, void* vertexBufferOut, void* vertexDataOut, RwUInt32* baseIndexOut) {
    return ((RwBool(__cdecl *)(RwUInt32, RwUInt32, void*, void*, RwUInt32*))0x7F5B10)(vertexSize, numVertex, vertexBufferOut, vertexDataOut, baseIndexOut);
}

RwBool RwD3D9DynamicVertexBufferUnlock() {
    return ((RwBool(__cdecl *)(void))0x7F5C90)();
}
#endif

void RwRasterSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)blockSize;
    (void)numBlocksToPrealloc;
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7FB350)(blockSize, numBlocksToPrealloc);
#endif
}

RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags) {
#ifdef NOTSA_STANDALONE_NATIVE
    if ((flags & 0xF00) == 0 && (flags & 0x07) == rwRASTERTYPETEXTURE) {
        if (depth == 32) flags |= rwRASTERFORMAT8888;
        else if (depth == 24) flags |= rwRASTERFORMAT888;
        else if (depth == 16) flags |= rwRASTERFORMAT1555;
        else flags |= rwRASTERFORMAT8888;
    }
    return FromRw(rw::Raster::create(width, height, depth, flags));
#else
    return ((RwRaster*(__cdecl *)(RwInt32, RwInt32, RwInt32, RwInt32))0x7FB230)(width, height, depth, flags);
#endif
}

RwBool RwRasterDestroy(RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (raster) {
        ToRw(raster)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwRaster*))0x7FB020)(raster);
#endif
}

RwRaster* RwRasterGetOffset(RwRaster* raster, RwInt16* xOffset, RwInt16* yOffset) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (raster) {
        if (xOffset) *xOffset = (RwInt16)ToRw(raster)->offsetX;
        if (yOffset) *yOffset = (RwInt16)ToRw(raster)->offsetY;
    }
    return raster;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*, RwInt16*, RwInt16*))0x7FAEA0)(raster, xOffset, yOffset);
#endif
}

RwInt32 RwRasterGetNumLevels(RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    return raster ? ToRw(raster)->getNumLevels() : 0;
#else
    return ((RwInt32(__cdecl *)(RwRaster*))0x7FB160)(raster);
#endif
}

RwRaster* RwRasterSubRaster(RwRaster* subRaster, RwRaster* raster, RwRect* rect) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (subRaster && raster) {
        ToRw(subRaster)->subRaster(ToRw(raster), ToRw(rect));
    }
    return subRaster;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*, RwRaster*, RwRect*))0x7FB1D0)(subRaster, raster, rect);
#endif
}

RwRaster* RwRasterRenderFast(RwRaster* raster, RwInt32 x, RwInt32 y) {
#ifdef NOTSA_STANDALONE_NATIVE
    return raster ? (ToRw(raster)->renderFast(x, y) ? raster : nullptr) : nullptr;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*, RwInt32, RwInt32))0x7FAF50)(raster, x, y);
#endif
}

RwRaster* RwRasterRender(RwRaster* raster, RwInt32 x, RwInt32 y) {
#ifdef NOTSA_STANDALONE_NATIVE
    return raster ? (ToRw(raster)->renderFast(x, y) ? raster : nullptr) : nullptr;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*, RwInt32, RwInt32))0x7FAFB0)(raster, x, y);
#endif
}

RwRaster* RwRasterRenderScaled(RwRaster* raster, RwRect* rect) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)rect;
    return raster;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*, RwRect*))0x7FAE80)(raster, rect);
#endif
}

RwRaster* RwRasterPushContext(RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Raster::pushContext(ToRw(raster)));
#else
    return ((RwRaster*(__cdecl *)(RwRaster*))0x7FB060)(raster);
#endif
}

RwRaster* RwRasterPopContext() {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Raster::popContext());
#else
    return ((RwRaster*(__cdecl *)(void))0x7FB110)();
#endif
}

RwRaster* RwRasterGetCurrentContext() {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Raster::getCurrentContext());
#else
    return ((RwRaster*(__cdecl *)(void))0x7FAE60)();
#endif
}

RwBool RwRasterClear(RwInt32 pixelValue) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)pixelValue;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwInt32))0x7FAEE0)(pixelValue);
#endif
}

RwBool RwRasterClearRect(RwRect* rpRect, RwInt32 pixelValue) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)rpRect;
    (void)pixelValue;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwRect*, RwInt32))0x7FAF90)(rpRect, pixelValue);
#endif
}

RwRaster* RwRasterShowRaster(RwRaster* raster, void* dev, RwUInt32 flags) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)dev;
    if (raster) {
        ToRw(raster)->show(flags);
    }
    return raster;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*, void*, RwUInt32))0x7FB1A0)(raster, dev, flags);
#endif
}

//! NOTE: This function is responsible for calculating the `stride` in the `raster`
RwUInt8* RwRasterLock(RwRaster* raster, RwUInt8 level, RwInt32 lockMode) {
#ifdef NOTSA_STANDALONE_NATIVE
    return raster ? ToRw(raster)->lock(level, lockMode) : nullptr;
#else
    return ((RwUInt8*(__cdecl *)(RwRaster*, RwUInt8, RwInt32))0x7FB2D0)(raster, level, lockMode);
#endif
}

RwRaster* RwRasterUnlock(RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (raster) {
        ToRw(raster)->unlock(0);
    }
    return raster;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*))0x7FAEC0)(raster);
#endif
}

RwUInt8* RwRasterLockPalette(RwRaster* raster, RwInt32 lockMode) {
#ifdef NOTSA_STANDALONE_NATIVE
    return raster ? ToRw(raster)->lockPalette(lockMode) : nullptr;
#else
    return ((RwUInt8*(__cdecl *)(RwRaster*, RwInt32))0x7FB0E0)(raster, lockMode);
#endif
}

RwRaster* RwRasterUnlockPalette(RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (raster) {
        ToRw(raster)->unlockPalette();
    }
    return raster;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*))0x7FAFF0)(raster);
#endif
}

RwInt32 RwRasterRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Raster::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7FB0B0)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RwRasterGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Raster::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x7FAE40)(pluginID);
#endif
}

#ifdef NOTSA_STANDALONE_NATIVE
RwInt32 RwRasterGetWidth(const RwRaster* raster) {
    return raster ? ToRw(raster)->width : 0;
}

RwInt32 RwRasterGetHeight(const RwRaster* raster) {
    return raster ? ToRw(raster)->height : 0;
}

RwInt32 RwRasterGetStride(const RwRaster* raster) {
    return raster ? ToRw(raster)->stride : 0;
}

RwInt32 RwRasterGetDepth(const RwRaster* raster) {
    return raster ? ToRw(raster)->depth : 0;
}

RwInt32 RwRasterGetFormat(const RwRaster* raster) {
    return raster ? ToRw(raster)->format : 0;
}

RwInt32 RwRasterGetType(const RwRaster* raster) {
    return raster ? ToRw(raster)->type : 0;
}

RwRaster* RwRasterGetParent(const RwRaster* raster) {
    return raster ? FromRw(ToRw(raster)->parent) : nullptr;
}
#endif

RxRenderStateVector* RxRenderStateVectorSetDefaultRenderStateVector(RxRenderStateVector* rsvp) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rsvp;
#else
    return ((RxRenderStateVector*(__cdecl *)(RxRenderStateVector*))0x80EA40)(rsvp);
#endif
}

RwImage* RwImageCreate(RwInt32 width, RwInt32 height, RwInt32 depth) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Image::create(width, height, depth));
#else
    return ((RwImage*(__cdecl *)(RwInt32, RwInt32, RwInt32))0x8026E0)(width, height, depth);
#endif
}

RwBool RwImageDestroy(RwImage* image) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (image) {
        ToRw(image)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwImage*))0x802740)(image);
#endif
}

RwImage* RwImageAllocatePixels(RwImage* image) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (image) {
        ToRw(image)->allocate();
    }
    return image;
#else
    return ((RwImage*(__cdecl *)(RwImage*))0x8027A0)(image);
#endif
}

RwImage* RwImageFreePixels(RwImage* image) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (image) {
        ToRw(image)->free();
    }
    return image;
#else
    return ((RwImage*(__cdecl *)(RwImage*))0x802860)(image);
#endif
}

RwImage* RwImageApplyMask(RwImage* image, const RwImage* mask) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (image && mask) {
        ToRw(image)->applyMask(ToRw(const_cast<RwImage*>(mask)));
    }
    return image;
#else
    return ((RwImage*(__cdecl *)(RwImage*, const RwImage*))0x802AF0)(image, mask);
#endif
}

RwImage* RwImageMakeMask(RwImage* image) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (image) {
        ToRw(image)->makeMask();
    }
    return image;
#else
    return ((RwImage*(__cdecl *)(RwImage*))0x802A20)(image);
#endif
}

RwImage* RwImageReadMaskedImage(const RwChar* imageName, const RwChar* maskname) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Image::readMasked(imageName, maskname));
#else
    return ((RwImage*(__cdecl *)(const RwChar*, const RwChar*))0x8035C0)(imageName, maskname);
#endif
}

RwImage* RwImageRead(const RwChar* imageName) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Image::read(imageName));
#else
    return ((RwImage*(__cdecl *)(const RwChar*))0x802FD0)(imageName);
#endif
}

const RwChar* RwImageSetPath(const RwChar* path) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Image::setSearchPath(path);
    return path;
#else
    return ((const RwChar*(__cdecl *)(const RwChar*))0x802EA0)(path);
#endif
}

RwBool RwImageSetGamma(RwReal gammaValue) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)gammaValue;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwReal))0x803FE0)(gammaValue);
#endif
}

RwImage* RwImageGammaCorrect(RwImage* image) {
#ifdef NOTSA_STANDALONE_NATIVE
    return image;
#else
    return ((RwImage*(__cdecl *)(RwImage*))0x803E30)(image);
#endif
}

RwBool RwPalQuantInit(RwPalQuant* pq) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)pq;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwPalQuant*))0x80C470)(pq);
#endif
}

void RwPalQuantTerm(RwPalQuant* pq) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)pq;
#else
    ((void(__cdecl *)(RwPalQuant*))0x80C520)(pq);
#endif
}

void RwPalQuantAddImage(RwPalQuant* pq, RwImage* img, RwReal weight) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)pq;
    (void)img;
    (void)weight;
#else
    ((void(__cdecl *)(RwPalQuant*, RwImage*, RwReal))0x80AA80)(pq, img, weight);
#endif
}

RwInt32 RwPalQuantResolvePalette(RwRGBA* palette, RwInt32 maxcols, RwPalQuant* pq) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)palette;
    (void)maxcols;
    (void)pq;
    return 0;
#else
    return ((RwInt32(__cdecl *)(RwRGBA*, RwInt32, RwPalQuant*))0x80AF60)(palette, maxcols, pq);
#endif
}

void RwPalQuantMatchImage(RwUInt8* dstpixels, RwInt32 dststride, RwInt32 dstdepth, RwBool dstPacked, RwPalQuant* pq, RwImage* img) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)dstpixels;
    (void)dststride;
    (void)dstdepth;
    (void)dstPacked;
    (void)pq;
    (void)img;
#else
    ((void(__cdecl *)(RwUInt8*, RwInt32, RwInt32, RwBool, RwPalQuant*, RwImage*))0x80BF20)(dstpixels, dststride, dstdepth, dstPacked, pq, img);
#endif
}

RwBool RwTextureSetMipmapping(RwBool enable) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Texture::setMipmapping(enable);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwBool))0x7F3530)(enable);
#endif
}

RwBool RwTextureGetMipmapping() {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Texture::getMipmapping();
#else
    return ((RwBool(__cdecl *)(void))0x7F3550)();
#endif
}

RwBool RwTextureSetAutoMipmapping(RwBool enable) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Texture::setAutoMipmapping(enable);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwBool))0x7F3560)(enable);
#endif
}

RwBool RwTextureGetAutoMipmapping() {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Texture::getAutoMipmapping();
#else
    return ((RwBool(__cdecl *)(void))0x7F3580)();
#endif
}

RwBool RwTextureSetMipmapGenerationCallBack(RwTextureCallBackMipmapGeneration callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)callback;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwTextureCallBackMipmapGeneration))0x7F3C70)(callback);
#endif
}

RwTextureCallBackMipmapGeneration RwTextureGetMipmapGenerationCallBack() {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwTextureCallBackMipmapGeneration(__cdecl *)(void))0x7F3C90)();
#endif
}

RwBool RwTextureSetMipmapNameCallBack(RwTextureCallBackMipmapName callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)callback;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwTextureCallBackMipmapName))0x7F3CA0)(callback);
#endif
}

RwTextureCallBackMipmapName RwTextureGetMipmapNameCallBack() {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwTextureCallBackMipmapName(__cdecl *)(void))0x7F3CC0)();
#endif
}

RwBool RwTextureGenerateMipmapName(RwChar* name, RwChar* maskName, RwUInt8 mipLevel, RwInt32 format) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)name;
    (void)maskName;
    (void)mipLevel;
    (void)format;
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RwChar*, RwChar*, RwUInt8, RwInt32))0x7F3AA0)(name, maskName, mipLevel, format);
#endif
}

RwBool RwTextureRasterGenerateMipmaps(RwRaster* raster, RwImage* image) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)raster;
    (void)image;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwRaster*, RwImage*))0x7F3CD0)(raster, image);
#endif
}

RwBool _rwTextureSetAutoMipMapState(RwBool enable) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Texture::setAutoMipmapping(enable);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwBool))0x7F3590)(enable);
#endif
}

RwBool _rwTextureGetAutoMipMapState() {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Texture::getAutoMipmapping();
#else
    return ((RwBool(__cdecl *)(void))0x7F35C0)();
#endif
}

RwTextureCallBackRead RwTextureGetReadCallBack() {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwTextureCallBackRead)rw::Texture::readCB;
#else
    return ((RwTextureCallBackRead(__cdecl *)(void))0x7F3520)();
#endif
}

RwBool RwTextureSetReadCallBack(RwTextureCallBackRead callBack) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Texture::readCB = (rw::Texture* (*)(const char*, const char*))callBack;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwTextureCallBackRead))0x7F3500)(callBack);
#endif
}

RwTextureCallBackFind RwTextureGetFindCallBack() {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwTextureCallBackFind)rw::Texture::findCB;
#else
    return ((RwTextureCallBackFind(__cdecl *)(void))0x7F34F0)();
#endif
}

RwBool RwTextureSetFindCallBack(RwTextureCallBackFind callBack) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Texture::findCB = (rw::Texture* (*)(const char*))callBack;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwTextureCallBackFind))0x7F34D0)(callBack);
#endif
}

RwTexture* RwTextureSetName(RwTexture* texture, const RwChar* name) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (texture && name) {
        strncpy(ToRw(texture)->name, name, sizeof(ToRw(texture)->name));
        ToRw(texture)->name[sizeof(ToRw(texture)->name) - 1] = '\0';
    }
    return texture;
#else
    return ((RwTexture*(__cdecl *)(RwTexture*, const RwChar*))0x7F38A0)(texture, name);
#endif
}

RwTexture* RwTextureSetMaskName(RwTexture* texture, const RwChar* maskName) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (texture && maskName) {
        strncpy(ToRw(texture)->mask, maskName, sizeof(ToRw(texture)->mask));
        ToRw(texture)->mask[sizeof(ToRw(texture)->mask) - 1] = '\0';
    }
    return texture;
#else
    return ((RwTexture*(__cdecl *)(RwTexture*, const RwChar*))0x7F3910)(texture, maskName);
#endif
}

void RwTexDictionarySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)blockSize;
    (void)numBlocksToPrealloc;
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7F3E80)(blockSize, numBlocksToPrealloc);
#endif
}

RwTexDictionary* RwTexDictionaryCreate() {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::TexDictionary::create());
#else
    return ((RwTexDictionary*(__cdecl *)(void))0x7F3600)();
#endif
}

RwBool RwTexDictionaryDestroy(RwTexDictionary* dict) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (dict) {
        ToRw(dict)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwTexDictionary*))0x7F36A0)(dict);
#endif
}

RwTexture* RwTextureCreate(RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Texture::create(ToRw(raster)));
#else
    return ((RwTexture*(__cdecl *)(RwRaster*))0x7F37C0)(raster);
#endif
}

RwTexture* RwTextureRead(const char* name, const char* maskName) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Texture::read(name, maskName));
#else
    return plugin::CallAndReturn<RwTexture*, 0x7F3AC0, const char*, const char*>(name, maskName);
#endif
}

RwBool RwTextureDestroy(RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (texture) {
        ToRw(texture)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwTexture*))0x7F3820)(texture);
#endif
}

RwTexture* RwTextureSetRaster(RwTexture* texture, RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (texture) {
        ToRw(texture)->raster = ToRw(raster);
    }
    return texture;
#else
    return ((RwTexture*(__cdecl *)(RwTexture*, RwRaster*))0x7F35D0)(texture, raster);
#endif
}

RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (dict && texture) {
        ToRw(dict)->add(ToRw(texture));
    }
    return texture;
#else
    return ((RwTexture*(__cdecl *)(RwTexDictionary*, RwTexture*))0x7F3980)(dict, texture);
#endif
}

RwTexture* RwTexDictionaryRemoveTexture(RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (texture && ToRw(texture)->dict) {
        ToRw(texture)->dict->remove(ToRw(texture));
    }
    return texture;
#else
    return ((RwTexture*(__cdecl *)(RwTexture*))0x7F39C0)(texture);
#endif
}

RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, const RwChar* name) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (dict && name) ? FromRw(ToRw(dict)->find(name)) : nullptr;
#else
    return ((RwTexture*(__cdecl *)(RwTexDictionary*, const RwChar*))0x7F39F0)(dict, name);
#endif
}

RwTexDictionary* RwTexDictionaryGetCurrent() {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::TexDictionary::getCurrent());
#else
    return ((RwTexDictionary*(__cdecl *)(void))0x7F3A90)();
#endif
}

RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::TexDictionary::setCurrent(ToRw(dict));
    return dict;
#else
    return ((RwTexDictionary*(__cdecl *)(RwTexDictionary*))0x7F3A70)(dict);
#endif
}

const RwTexDictionary* RwTexDictionaryForAllTextures(const RwTexDictionary* dict, RwTextureCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (dict && fpCallBack) {
        FORLIST(lnk, ToRw(const_cast<RwTexDictionary*>(dict))->textures) {
            rw::Texture* t = rw::Texture::fromDict(lnk);
            if (!fpCallBack(FromRw(t), data))
                break;
        }
    }
    return dict;
#else
    return ((const RwTexDictionary*(__cdecl *)(const RwTexDictionary*, RwTextureCallBack, void*))0x7F3730)(dict, fpCallBack, data);
#endif
}

RwBool RwTexDictionaryForAllTexDictionaries(RwTexDictionaryCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)fpCallBack;
    (void)data;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwTexDictionaryCallBack, void*))0x7F3770)(fpCallBack, data);
#endif
}

RwInt32 RwTextureRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Texture::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7F3BB0)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RwTexDictionaryRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::TexDictionary::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7F3C10)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RwTextureGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Texture::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x7F3BE0)(pluginID);
#endif
}

RwInt32 RwTexDictionaryGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::TexDictionary::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x7F3C40)(pluginID);
#endif
}

RwBool RwTextureValidatePlugins(const RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)texture;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RwTexture*))0x7F3C00)(texture);
#endif
}

RwBool RwTexDictionaryValidatePlugins(const RwTexDictionary* dict) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)dict;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RwTexDictionary*))0x7F3C60)(dict);
#endif
}

rwIm3DPool* _rwIm3DGetPool() {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((rwIm3DPool*(__cdecl *)(void))0x7EFDD0)();
#endif
}

void* RwIm3DTransform(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::im3d::Transform(pVerts, numVerts, ToRw(ltm), flags);
    return pVerts;
#else
    return ((void*(__cdecl *)(RwIm3DVertex*, RwUInt32, RwMatrix*, RwUInt32))0x7EF450)(pVerts, numVerts, ltm, flags);
#endif
}

RwBool RwIm3DEnd() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::im3d::End();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7EF520)();
#endif
}

RwBool RwIm3DRenderLine(RwInt32 vert1, RwInt32 vert2) {
#ifdef NOTSA_STANDALONE_NATIVE
    RwImVertexIndex indices[2] = { (RwImVertexIndex)vert1, (RwImVertexIndex)vert2 };
    rw::im3d::RenderIndexedPrimitive(rw::PRIMTYPELINELIST, indices, 2);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwInt32, RwInt32))0x7EF900)(vert1, vert2);
#endif
}

RwBool RwIm3DRenderTriangle(RwInt32 vert1, RwInt32 vert2, RwInt32 vert3) {
#ifdef NOTSA_STANDALONE_NATIVE
    RwImVertexIndex indices[3] = { (RwImVertexIndex)vert1, (RwImVertexIndex)vert2, (RwImVertexIndex)vert3 };
    rw::im3d::RenderIndexedPrimitive(rw::PRIMTYPETRILIST, indices, 3);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwInt32, RwInt32, RwInt32))0x7EF810)(vert1, vert2, vert3);
#endif
}

RwBool RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType, RwImVertexIndex* indices, RwInt32 numIndices) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::im3d::RenderIndexedPrimitive((rw::PrimitiveType)primType, indices, numIndices);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwPrimitiveType, RwImVertexIndex*, RwInt32))0x7EF550)(primType, indices, numIndices);
#endif
}

RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::im3d::RenderPrimitive((rw::PrimitiveType)primType);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwPrimitiveType))0x7EF6B0)(primType);
#endif
}

RxPipeline* RwIm3DGetTransformPipeline() {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RxPipeline*(__cdecl *)(void))0x7EF9D0)();
#endif
}

RxPipeline* RwIm3DGetRenderPipeline(RwPrimitiveType primType) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)primType;
    return nullptr;
#else
    return ((RxPipeline*(__cdecl *)(RwPrimitiveType))0x7EF9E0)(primType);
#endif
}

RxPipeline* RwIm3DSetTransformPipeline(RxPipeline* pipeline) {
#ifdef NOTSA_STANDALONE_NATIVE
    return pipeline;
#else
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x7EFAC0)(pipeline);
#endif
}

RxPipeline* RwIm3DSetRenderPipeline(RxPipeline* pipeline, RwPrimitiveType primType) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)primType;
    return pipeline;
#else
    return ((RxPipeline*(__cdecl *)(RxPipeline*, RwPrimitiveType))0x7EFB10)(pipeline, primType);
#endif
}

RwRaster* RwD3D9RasterStreamReadDDS(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    return nullptr;
#else
    return ((RwRaster*(__cdecl *)(RwStream*))0x81F360)(stream);
#endif
}

RwTexture* RwD3D9DDSTextureRead(const RwChar* name, const RwChar* maskname) {
#ifdef NOTSA_STANDALONE_NATIVE
    return RwTextureRead(name, maskname);
#else
    return ((RwTexture*(__cdecl *)(const RwChar*, const RwChar*))0x820A10)(name, maskname);
#endif
}

RwBool RwD3D9RasterIsCompressed(const RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)raster;
    return FALSE;
#else
    return ((RwBool(__cdecl *)(const RwRaster*))0x820C90)(raster);
#endif
}

RwBool RwD3D9DeviceSupportsDXTTexture() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7F9C30)();
#endif
}

void* RwD3D9GetCurrentD3DDevice() { // IDirect3DDevice9
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((void*(__cdecl *)(void))0x7F9D50)();
#endif
}

RwUInt32 RwD3D9EngineGetMaxMultiSamplingLevels() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 1;
#else
    return ((RwUInt32(__cdecl *)(void))0x7F84E0)();
#endif
}

void RwD3D9EngineSetMultiSamplingLevels(RwUInt32 numLevels) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)numLevels;
#else
    ((void(__cdecl *)(RwUInt32))0x7F84F0)(numLevels);
#endif
}

void RwD3D9EngineSetRefreshRate(RwUInt32 refreshRate) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)refreshRate;
#else
    ((void(__cdecl *)(RwUInt32))0x7F8580)(refreshRate);
#endif
}

void RwD3D9EngineSetMultiThreadSafe(RwBool enable) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)enable;
#else
    ((void(__cdecl *)(RwBool))0x7F8620)(enable);
#endif
}

void RwD3D9EngineSetSoftwareVertexProcessing(RwBool enable) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)enable;
#else
    ((void(__cdecl *)(RwBool))0x7F8630)(enable);
#endif
}

void* RwD3D9GetCurrentD3DRenderTarget(RwUInt32 index) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)index;
    return nullptr;
#else
    return ((void*(__cdecl *)(RwUInt32))0x7F9E80)(index);
#endif
}

RwBool RwD3D9SetRenderTarget(RwUInt32 index, RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)index;
    (void)raster;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwUInt32, RwRaster*))0x7F9E90)(index, raster);
#endif
}

RwBool RwD3D9ChangeVideoMode(RwInt32 modeIndex) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)modeIndex;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwInt32))0x7F8640)(modeIndex);
#endif
}

RwBool RwD3D9ChangeMultiSamplingLevels(RwUInt32 numLevels) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)numLevels;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwUInt32))0x7F8A90)(numLevels);
#endif
}

RwBool RwD3D9CameraAttachWindow(void* camera, void* hwnd) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)camera;
    (void)hwnd;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void*, void*))0x7F8D70)(camera, hwnd);
#endif
}

void RwD3D9SetStreamSource(RwUInt32 streamNumber, void* streamData, RwUInt32 offset, RwUInt32 stride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)streamNumber;
    (void)streamData;
    (void)offset;
    (void)stride;
#else
    ((void(__cdecl *)(RwUInt32, void*, RwUInt32, RwUInt32))0x7FA030)(streamNumber, streamData, offset, stride);
#endif
}

void _rwD3D9RenderStateFlushCache() {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void))0x7FC200)();
#endif
}

void _rwD3D9DrawIndexedPrimitiveUP(RwUInt32 primitiveType, RwUInt32 minIndex, RwUInt32 numVertices, RwUInt32 primitiveCount, const void* indexData, const void* vertexStreamZeroData, RwUInt32 VertexStreamZeroStride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)primitiveType;
    (void)minIndex;
    (void)numVertices;
    (void)primitiveCount;
    (void)indexData;
    (void)vertexStreamZeroData;
    (void)VertexStreamZeroStride;
#else
   ((void(__cdecl *)(RwUInt32, RwUInt32, RwUInt32, RwUInt32, const void*, const void*, RwUInt32))0x7FA1F0)(primitiveType, minIndex, numVertices, primitiveCount, indexData, vertexStreamZeroData, VertexStreamZeroStride);
#endif
}

void _rwD3D9DrawPrimitiveUP(RwUInt32 primitiveType, RwUInt32 primitiveCount, const void* vertexStreamZeroData, RwUInt32 VertexStreamZeroStride) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)primitiveType;
    (void)primitiveCount;
    (void)vertexStreamZeroData;
    (void)VertexStreamZeroStride;
#else
   ((void(__cdecl *)(RwUInt32, RwUInt32, const void*, RwUInt32))0x7FA290)(primitiveType, primitiveCount, vertexStreamZeroData, VertexStreamZeroStride);
#endif
}

void _rwD3D9DrawIndexedPrimitive(RwUInt32 primitiveType, RwInt32 baseVertexIndex, RwUInt32 minIndex, RwUInt32 numVertices, RwUInt32 startIndex, RwUInt32 primitiveCount) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)primitiveType;
    (void)baseVertexIndex;
    (void)minIndex;
    (void)numVertices;
    (void)startIndex;
    (void)primitiveCount;
#else
   ((void(__cdecl *)(RwUInt32, RwInt32, RwUInt32, RwUInt32, RwUInt32, RwUInt32))0x7FA320)(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);
#endif
}

void _rwD3D9SetVertexShaderConstant(RwUInt32 registerAddress, const void* constantData, RwUInt32 constantCount) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)registerAddress;
    (void)constantData;
    (void)constantCount;
#else
   ((void(__cdecl *)(RwUInt32, const void*, RwUInt32))0x7FACA0)(registerAddress, constantData, constantCount);
#endif
}

void _rwD3D9SetPixelShaderConstant(RwUInt32 registerAddress, const void* constantData, RwUInt32 constantCount) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)registerAddress;
    (void)constantData;
    (void)constantCount;
#else
   ((void(__cdecl *)(RwUInt32, const void*, RwUInt32))0x7FAD00)(registerAddress, constantData, constantCount);
#endif
}

void _rwD3D9SetFVF(RwUInt32 fvf) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)fvf;
#else
   ((void(__cdecl *)(RwUInt32))0x7F9F30)(fvf);
#endif
}

void _rwD3D9SetVertexShader(void *shader) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)shader;
#else
   ((void(__cdecl *)(void *))0x7F9FB0)(shader);
#endif
}

void _rwD3D9SetPixelShader(void *shader) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)shader;
#else
   ((void(__cdecl *)(void *))0x7F9FF0)(shader);
#endif
}

void RwD3D9SetRenderState(RwUInt32 state, RwUInt32 value) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)state;
    (void)value;
#else
   ((void(__cdecl *)(RwUInt32, RwUInt32))0x7FC2D0)(state, value);
#endif
}

void RwD3D9GetRenderState(RwUInt32 state, void* value) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)state;
    (void)value;
#else
   ((void(__cdecl *)(RwUInt32, void*))0x7FC320)(state, value);
#endif
}

void RwD3D9SetTextureStageState(RwUInt32 stage, RwUInt32 type, RwUInt32 value) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stage;
    (void)type;
    (void)value;
#else
   ((void(__cdecl *)(RwUInt32, RwUInt32, RwUInt32))0x7FC340)(stage, type, value);
#endif
}

void RwD3D9GetTextureStageState(RwUInt32 stage, RwUInt32 type, void* value) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stage;
    (void)type;
    (void)value;
#else
   ((void(__cdecl *)(RwUInt32, RwUInt32, void*))0x7FC3A0)(stage, type, value);
#endif
}

void RwD3D9SetSamplerState(RwUInt32 stage, RwUInt32 type, RwUInt32 value) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stage;
    (void)type;
    (void)value;
#else
   ((void(__cdecl *)(RwUInt32, RwUInt32, RwUInt32))0x7FC3C0)(stage, type, value);
#endif
}

void RwD3D9GetSamplerState(RwUInt32 stage, RwUInt32 type, void* value) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stage;
    (void)type;
    (void)value;
#else
   ((void(__cdecl *)(RwUInt32, RwUInt32, void*))0x7FC400)(stage, type, value);
#endif
}

void RwD3D9SetStencilClear(RwUInt32 stencilClear) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stencilClear;
#else
   ((void(__cdecl *)(RwUInt32))0x7F9D30)(stencilClear);
#endif
}

RwUInt32 RwD3D9GetStencilClear() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
   return ((RwUInt32(__cdecl *)(void))0x7F9D40)();
#endif
}

RwBool RwD3D9SetTexture(RwTexture* texture, RwUInt32 stage) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)texture;
    (void)stage;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(RwTexture*, RwUInt32))0x7FDE70)(texture, stage);
#endif
}

RwBool RwD3D9SetTransform(RwUInt32 state, const void* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)state;
    (void)matrix;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(RwUInt32, const void*))0x7FA390)(state, matrix);
#endif
}

void RwD3D9GetTransform(RwUInt32 state, void* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)state;
    (void)matrix;
#else
   ((void(__cdecl *)(RwUInt32, void*))0x7FA4F0)(state, matrix);
#endif
}

RwBool RwD3D9SetMaterial(const void* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)material;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(const void*))0x7FC430)(material);
#endif
}

RwBool RwD3D9SetClipPlane(RwUInt32 index, const RwV4d* plane) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)index;
    (void)plane;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(RwUInt32, const RwV4d*))0x7FC4A0)(index, plane);
#endif
}

RwBool RwD3D9SetTransformWorld(const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)matrix;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(const RwMatrix*))0x7FA520)(matrix);
#endif
}

RwBool RwD3D9SetSurfaceProperties(const RwSurfaceProperties* surfaceProps, const RwRGBA* color, RwUInt32 flags) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)surfaceProps;
    (void)color;
    (void)flags;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(const RwSurfaceProperties*, const RwRGBA*, RwUInt32))0x7FC4D0)(surfaceProps, color, flags);
#endif
}

RwBool RwD3D9SetLight(RwInt32 index, const void* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)index;
    (void)light;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(RwInt32, const void*))0x7FA660)(index, light);
#endif
}

void RwD3D9GetLight(RwInt32 index, void* light) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)index;
    (void)light;
#else
   ((void(__cdecl *)(RwInt32, void*))0x7FA820)(index, light);
#endif
}

RwBool RwD3D9EnableLight(RwInt32 index, RwBool enable) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)index;
    (void)enable;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(RwInt32, RwBool))0x7FA860)(index, enable);
#endif
}

RwBool RwD3D9IndexBufferCreate(RwUInt32 numIndices, void* indexBuffer) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)numIndices;
    (void)indexBuffer;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(RwUInt32, void*))0x4C9970)(numIndices, indexBuffer);
#endif
}

RwBool RwD3D9CreateVertexDeclaration(const void* elements, void* vertexdeclaration) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)elements;
    (void)vertexdeclaration;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(const void*, void*))0x7FAA30)(elements, vertexdeclaration);
#endif
}

void RwD3D9DeleteVertexDeclaration() {
#ifdef NOTSA_STANDALONE_NATIVE
#else
   ((void(__cdecl *)(void))0x7FAC10)();
#endif
}

void RwD3D9DeleteVertexShader() {
#ifdef NOTSA_STANDALONE_NATIVE
#else
   ((void(__cdecl *)(void))0x7FAC90)();
#endif
}

RwBool RwD3D9CreatePixelShader(const RwUInt32* function, void* shader) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)function;
    (void)shader;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(const RwUInt32*, void*))0x7FACC0)(function, shader);
#endif
}

void RwD3D9DeletePixelShader() {
#ifdef NOTSA_STANDALONE_NATIVE
#else
   ((void(__cdecl *)(void))0x7FACF0)();
#endif
}

void _rwD3D9SetStreams(const RxD3D9VertexStream* streams, RwBool useOffsets) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)streams;
    (void)useOffsets;
#else
    plugin::CallAndReturn<void, 0x7FA090>(streams, useOffsets);
#endif
}

const void* RwD3D9GetCaps() { // D3DCAPS9*
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
   return ((const void*(__cdecl *)(void))0x7FAD20)();
#endif
}

RwBool RwD3D9CameraIsSphereFullyInsideFrustum(const void* camera, const void* sphere) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)camera;
    (void)sphere;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(const void*, const void*))0x7FAD30)(camera, sphere);
#endif
}

RwBool RwD3D9CameraIsBBoxFullyInsideFrustum(const void* camera, const void* boundingBox) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)camera;
    (void)boundingBox;
    return TRUE;
#else
   return ((RwBool(__cdecl *)(const void*, const void*))0x7FAD90)(camera, boundingBox);
#endif
}

void _rwD3D9RasterConvertToNonPalettized(RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)raster;
#else
   ((void(__cdecl *)(RwRaster*))0x4CD250)(raster);
#endif
}

RwBool _rwDeviceRegisterPlugin() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
   return ((RwBool(__cdecl *)(void))0x7F5F60)();
#endif
}

void _rwD3D9DeviceSetRestoreCallback(rwD3D9DeviceRestoreCallBack callback) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)callback;
#else
   ((void(__cdecl *)(rwD3D9DeviceRestoreCallBack))0x7FAE20)(callback);
#endif
}

rwD3D9DeviceRestoreCallBack _rwD3D9DeviceGetRestoreCallback() {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
   return ((rwD3D9DeviceRestoreCallBack(__cdecl *)(void))0x7FAE30)();
#endif
}

RwImage* RwImageResample(RwImage* dstImage, const RwImage* srcImage) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)dstImage;
    (void)srcImage;
    return dstImage;
#else
    return ((RwImage*(__cdecl *)(RwImage*, const RwImage*))0x80C600)(dstImage, srcImage);
#endif
}

RwImage* RwImageCreateResample(const RwImage* srcImage, RwInt32 width, RwInt32 height) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)srcImage;
    return RwImageCreate(width, height, 32);
#else
    return ((RwImage*(__cdecl *)(const RwImage*, RwInt32, RwInt32))0x80CD10)(srcImage, width, height);
#endif
}

RwImage* RwImageSetFromRaster(RwImage* image, RwRaster* raster) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (image && raster) {
        rw::Image* img = ToRw(raster)->toImage();
        if (img) {
            *image = *FromRw(img);
            img->destroy();
        }
    }
    return image;
#else
    return ((RwImage*(__cdecl *)(RwImage*, RwRaster*))0x804250)(image, raster);
#endif
}

RwRaster* RwRasterSetFromImage(RwRaster* raster, RwImage* image) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (raster && image) {
        ToRw(raster)->setFromImage(ToRw(image));
    }
    return raster;
#else
    return ((RwRaster*(__cdecl *)(RwRaster*, RwImage*))0x804290)(raster, image);
#endif
}

RwRaster* RwRasterRead(const RwChar* filename) {
#ifdef NOTSA_STANDALONE_NATIVE
    RwImage* img = RwImageRead(filename);
    if (!img) return nullptr;
    RwRaster* ras = RwRasterCreate(img->width, img->height, img->depth, rwRASTERTYPETEXTURE);
    if (ras) {
        RwRasterSetFromImage(ras, img);
    }
    RwImageDestroy(img);
    return ras;
#else
    return ((RwRaster*(__cdecl *)(const RwChar*))0x8043F0)(filename);
#endif
}

RwRaster* RwRasterReadMaskedRaster(const RwChar* filename, const RwChar* maskname) {
#ifdef NOTSA_STANDALONE_NATIVE
    RwImage* img = RwImageReadMaskedImage(filename, maskname);
    if (!img) return nullptr;
    RwRaster* ras = RwRasterCreate(img->width, img->height, img->depth, rwRASTERTYPETEXTURE);
    if (ras) {
        RwRasterSetFromImage(ras, img);
    }
    RwImageDestroy(img);
    return ras;
#else
    return ((RwRaster*(__cdecl *)(const RwChar*, const RwChar*))0x8044E0)(filename, maskname);
#endif
}

RwImage* RwImageFindRasterFormat(RwImage* ipImage, RwInt32 nRasterType, RwInt32* npWidth, RwInt32* npHeight, RwInt32* npDepth, RwInt32* npFormat) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (ipImage) {
        rw::Raster::imageFindRasterFormat(ToRw(ipImage), nRasterType, npWidth, npHeight, npDepth, npFormat);
    }
    return ipImage;
#else
    return ((RwImage*(__cdecl *)(RwImage*, RwInt32, RwInt32*, RwInt32*, RwInt32*, RwInt32*))0x8042C0)(ipImage, nRasterType, npWidth, npHeight, npDepth, npFormat);
#endif
}

RwFrame* RwFrameForAllObjects(RwFrame* frame, RwObjectCallBack callBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame && callBack) {
        FORLIST(lnk, ToRw(frame)->objectList) {
            rw::ObjectWithFrame* owf = rw::ObjectWithFrame::fromFrame(lnk);
            if (!callBack(reinterpret_cast<RwObject*>(owf), data))
                break;
        }
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*, RwObjectCallBack, void*))0x7F1200)(frame, callBack, data);
#endif
}

RwFrame* RwFrameTranslate(RwFrame* frame, const RwV3d* v, RwOpCombineType combine) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame && v) {
        ToRw(frame)->translate(ToRw(v), (rw::CombineOp)combine);
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*, const RwV3d*, RwOpCombineType))0x7F0E30)(frame, v, combine);
#endif
}

RwFrame* RwFrameRotate(RwFrame* frame, const RwV3d* axis, RwReal angle, RwOpCombineType combine) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame && axis) {
        ToRw(frame)->rotate(ToRw(axis), angle, (rw::CombineOp)combine);
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*, const RwV3d*, RwReal, RwOpCombineType))0x7F1010)(frame, axis, angle, combine);
#endif
}

RwFrame* RwFrameScale(RwFrame* frame, const RwV3d* v, RwOpCombineType combine) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame && v) {
        ToRw(frame)->scale(ToRw(v), (rw::CombineOp)combine);
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*, const RwV3d*, RwOpCombineType))0x7F0ED0)(frame, v, combine);
#endif
}

RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* m, RwOpCombineType combine) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame && m) {
        ToRw(frame)->transform(ToRw(m), (rw::CombineOp)combine);
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*, const RwMatrix*, RwOpCombineType))0x7F0F70)(frame, m, combine);
#endif
}

RwFrame* RwFrameOrthoNormalize(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame) {
        ToRw(frame)->matrix.optimize();
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F1170)(frame);
#endif
}

RwFrame* RwFrameSetIdentity(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame) {
        ToRw(frame)->matrix.setIdentity();
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F10B0)(frame);
#endif
}

RwFrame* RwFrameCloneHierarchy(RwFrame* root) {
#ifdef NOTSA_STANDALONE_NATIVE
    return root ? FromRw(ToRw(root)->cloneHierarchy()) : nullptr;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F0250)(root);
#endif
}

RwBool RwFrameDestroyHierarchy(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame) {
        ToRw(frame)->destroyHierarchy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwFrame*))0x7F08A0)(frame);
#endif
}

RwFrame* RwFrameForAllChildren(RwFrame* frame, RwFrameCallBack callBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame && callBack) {
        ToRw(frame)->forAllChildren((rw::Frame::Callback)callBack, data);
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*, RwFrameCallBack, void*))0x7F0DC0)(frame, callBack, data);
#endif
}

RwFrame* RwFrameRemoveChild(RwFrame* child) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (child) {
        ToRw(child)->removeChild();
    }
    return child;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F0CD0)(child);
#endif
}

RwFrame* RwFrameAddChild(RwFrame* parent, RwFrame* child) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (parent && child) {
        ToRw(parent)->addChild(ToRw(child));
    }
    return parent;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*, RwFrame*))0x7F0B00)(parent, child);
#endif
}

RwFrame* RwFrameAddChildNoUpdate(RwFrame* parent, RwFrame* child) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (parent && child) {
        ToRw(parent)->addChild(ToRw(child));
    }
    return parent;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*, RwFrame*))0x7F09C0)(parent, child);
#endif
}

RwFrame* RwFrameGetRoot(const RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    return frame ? FromRw(ToRw(frame)->root) : nullptr;
#else
    return ((RwFrame*(__cdecl *)(const RwFrame*))0x7F09B0)(frame);
#endif
}

RwMatrix* RwFrameGetLTM(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    return frame ? FromRw(ToRw(frame)->getLTM()) : nullptr;
#else
    return ((RwMatrix*(__cdecl *)(RwFrame*))0x7F0990)(frame);
#endif
}

RwFrame* RwFrameUpdateObjects(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame) {
        ToRw(frame)->updateObjects();
    }
    return frame;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F0910)(frame);
#endif
}

void RwFrameSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)blockSize;
    (void)numBlocksToPrealloc;
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7EFED0)(blockSize, numBlocksToPrealloc);
#endif
}

RwFrame* RwFrameCreate() {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Frame::create());
#else
    return ((RwFrame*(__cdecl *)(void))0x7F0410)();
#endif
}

RwBool RwFrameDestroy(RwFrame* frame) {
    assert(frame);
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame) {
        ToRw(frame)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwFrame*))0x7F05A0)(frame);
#endif
}

RwBool _rwFrameInit(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)frame;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwFrame*))0x7F0450)(frame);
#endif
}

RwBool _rwFrameDeInit(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)frame;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwFrame*))0x7F06F0)(frame);
#endif
}

RwBool RwFrameDirty(const RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    return frame ? (RwBool)ToRw(frame)->dirty() : FALSE;
#else
    return ((RwBool(__cdecl *)(const RwFrame*))0x7F0340)(frame);
#endif
}

RwInt32 RwFrameCount(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    return frame ? ToRw(frame)->count() : 0;
#else
    return ((RwInt32(__cdecl *)(RwFrame*))0x7F0E00)(frame);
#endif
}

RwInt32 RwFrameRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Frame::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7F1260)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RwFrameGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Frame::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x7F1290)(pluginID);
#endif
}

RwBool RwFrameValidatePlugins(const RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)frame;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RwFrame*))0x7F12B0)(frame);
#endif
}

RwFrame* _rwFrameCloneAndLinkClones(RwFrame* root) {
#ifdef NOTSA_STANDALONE_NATIVE
    return root ? FromRw(ToRw(root)->cloneAndLink()) : nullptr;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7EFFB0)(root);
#endif
}

RwFrame* _rwFramePurgeClone(RwFrame* root) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (root) ToRw(root)->purgeClone();
    return root;
#else
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F01A0)(root);
#endif
}

void _rwObjectHasFrameReleaseFrame() {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void))0x804F40)();
#endif
}

RwBool _rwFrameSyncDirty() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Frame::syncDirty();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x809550)();
#endif
}

void _rwFrameSyncHierarchyLTM(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frame) ToRw(frame)->syncHierarchyLTM();
#else
    ((void(__cdecl *)(RwFrame*))0x8097D0)(frame);
#endif
}

RwInt32 RwTextureRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Texture::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x804550)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RwTextureSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Texture::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x804580)(pluginID, alwaysCB);
#endif
}

RwUInt32 RwTextureStreamGetSize(const RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    return texture ? ToRw(const_cast<RwTexture*>(texture))->streamGetSize() : 0;
#else
    return ((RwUInt32(__cdecl *)(const RwTexture*))0x8045A0)(texture);
#endif
}

RwTexture* RwTextureStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Texture::streamRead(ToRw(stream)));
#else
    return ((RwTexture*(__cdecl *)(RwStream*))0x8046E0)(stream);
#endif
}

const RwTexture* RwTextureStreamWrite(const RwTexture* texture, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (texture) ToRw(const_cast<RwTexture*>(texture))->streamWrite(ToRw(stream));
    return texture;
#else
    return ((const RwTexture*(__cdecl *)(const RwTexture*, RwStream*))0x8045E0)(texture, stream);
#endif
}

RwInt32 RwTexDictionaryRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::TexDictionary::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x8048E0)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RwTexDictionarySetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::TexDictionary::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x804910)(pluginID, alwaysCB);
#endif
}

RwUInt32 RwTexDictionaryStreamGetSize(const RwTexDictionary* texDict) {
#ifdef NOTSA_STANDALONE_NATIVE
    return texDict ? ToRw(const_cast<RwTexDictionary*>(texDict))->streamGetSize() : 0;
#else
    return ((RwUInt32(__cdecl *)(const RwTexDictionary*))0x804930)(texDict);
#endif
}

RwTexDictionary* RwTexDictionaryStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (!stream) return nullptr;
    auto* s = ToRw(stream);
    rw::ChunkHeaderInfo header;
    uint32 pos = s->tell();
    if (rw::readChunkHeaderInfo(s, &header)) {
        if (header.type != rw::ID_TEXDICTIONARY) {
            s->seek(pos, 0);
        }
    }
    return FromRw(rw::TexDictionary::streamRead(s));
#else
    return ((RwTexDictionary*(__cdecl *)(RwStream*))0x804C30)(stream);
#endif
}

const RwTexDictionary* RwTexDictionaryStreamWrite(const RwTexDictionary* texDict, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (texDict) ToRw(const_cast<RwTexDictionary*>(texDict))->streamWrite(ToRw(stream));
    return texDict;
#else
    return ((const RwTexDictionary*(__cdecl *)(const RwTexDictionary*, RwStream*))0x8049F0)(texDict, stream);
#endif
}

RwTextureChunkInfo* _rwTextureChunkInfoRead(RwStream* stream, RwTextureChunkInfo* textureChunkInfo, RwInt32* bytesRead) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    (void)textureChunkInfo;
    (void)bytesRead;
    return textureChunkInfo;
#else
    return ((RwTextureChunkInfo*(__cdecl *)(RwStream*, RwTextureChunkInfo*, RwInt32*))0x804E60)(stream, textureChunkInfo, bytesRead);
#endif
}

void RwFrameListSetAutoUpdate(RwBool flag) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)flag;
#else
    ((void(__cdecl *)(RwBool))0x807570)(flag);
#endif
}

RwInt32 RwFrameRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Frame::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x807580)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RwFrameSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Frame::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x8075B0)(pluginID, alwaysCB);
#endif
}

rwFrameList* _rwFrameListInitialize(rwFrameList* frameList, RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frameList && frame) {
        frameList->numFrames = ToRw(frame)->count();
        frameList->frames = new RwFrame*[frameList->numFrames];
        rw::makeFrameList(ToRw(frame), reinterpret_cast<rw::Frame**>(frameList->frames));
    }
    return frameList;
#else
    return ((rwFrameList*(__cdecl *)(rwFrameList*, RwFrame*))0x8075D0)(frameList, frame);
#endif
}

RwBool _rwFrameListFindFrame(const rwFrameList* frameList, const RwFrame* frame, RwInt32* npIndex) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frameList && npIndex) {
        for (RwInt32 i = 0; i < frameList->numFrames; i++) {
            if (frameList->frames[i] == frame) {
                *npIndex = i;
                return TRUE;
            }
        }
    }
    return FALSE;
#else
    return ((RwBool(__cdecl *)(const rwFrameList*, const RwFrame*, RwInt32*))0x8076E0)(frameList, frame, npIndex);
#endif
}

rwFrameList* _rwFrameListDeinitialize(rwFrameList* frameList) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (frameList && frameList->frames) {
        delete[] frameList->frames;
        frameList->frames = nullptr;
        frameList->numFrames = 0;
    }
    return frameList;
#else
    return ((rwFrameList*(__cdecl *)(rwFrameList*))0x807720)(frameList);
#endif
}

RwUInt32 _rwFrameListStreamGetSize(const rwFrameList* frameList) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)frameList;
    return 0;
#else
    return ((RwUInt32(__cdecl *)(const rwFrameList*))0x807750)(frameList);
#endif
}

rwFrameList* _rwFrameListStreamRead(RwStream* stream, rwFrameList* fl) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    return fl;
#else
    return ((rwFrameList*(__cdecl *)(RwStream*, rwFrameList*))0x807970)(stream, fl);
#endif
}

const rwFrameList* _rwFrameListStreamWrite(const rwFrameList* frameList, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    return frameList;
#else
    return ((const rwFrameList*(__cdecl *)(const rwFrameList*, RwStream*))0x8077A0)(frameList, stream);
#endif
}

RwBBox* RwBBoxCalculate(RwBBox* boundBox, const RwV3d* verts, RwInt32 numVerts) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (!boundBox || !verts || numVerts <= 0) return boundBox;
    boundBox->inf = verts[0];
    boundBox->sup = verts[0];
    for (RwInt32 i = 1; i < numVerts; i++) {
        boundBox->inf.x = std::min(boundBox->inf.x, verts[i].x);
        boundBox->inf.y = std::min(boundBox->inf.y, verts[i].y);
        boundBox->inf.z = std::min(boundBox->inf.z, verts[i].z);
        boundBox->sup.x = std::max(boundBox->sup.x, verts[i].x);
        boundBox->sup.y = std::max(boundBox->sup.y, verts[i].y);
        boundBox->sup.z = std::max(boundBox->sup.z, verts[i].z);
    }
    return boundBox;
#else
    return ((RwBBox*(__cdecl *)(RwBBox*, const RwV3d*, RwInt32))0x808F60)(boundBox, verts, numVerts);
#endif
}

RwBBox* RwBBoxInitialize(RwBBox* boundBox, const RwV3d* vertex) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (boundBox && vertex) {
        boundBox->inf = *vertex;
        boundBox->sup = *vertex;
    }
    return boundBox;
#else
    return ((RwBBox*(__cdecl *)(RwBBox*, const RwV3d*))0x809020)(boundBox, vertex);
#endif
}

RwBBox* RwBBoxAddPoint(RwBBox* boundBox, const RwV3d* vertex) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (boundBox && vertex) {
        boundBox->inf.x = std::min(boundBox->inf.x, vertex->x);
        boundBox->inf.y = std::min(boundBox->inf.y, vertex->y);
        boundBox->inf.z = std::min(boundBox->inf.z, vertex->z);
        boundBox->sup.x = std::max(boundBox->sup.x, vertex->x);
        boundBox->sup.y = std::max(boundBox->sup.y, vertex->y);
        boundBox->sup.z = std::max(boundBox->sup.z, vertex->z);
    }
    return boundBox;
#else
    return ((RwBBox*(__cdecl *)(RwBBox*, const RwV3d*))0x809060)(boundBox, vertex);
#endif
}

RwBool RwBBoxContainsPoint(const RwBBox* boundBox, const RwV3d* vertex) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (!boundBox || !vertex) return FALSE;
    return vertex->x >= boundBox->inf.x && vertex->x <= boundBox->sup.x &&
           vertex->y >= boundBox->inf.y && vertex->y <= boundBox->sup.y &&
           vertex->z >= boundBox->inf.z && vertex->z <= boundBox->sup.z;
#else
    return ((RwBool(__cdecl *)(const RwBBox*, const RwV3d*))0x8090E0)(boundBox, vertex);
#endif
}

RwCamera* RwCameraBeginUpdate(RwCamera* camera) {
    ZoneScoped;
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera) {
        ToRw(camera)->beginUpdate();
    }
    return camera;
#else
    return camera->beginUpdate(camera);
#endif
}

RwCamera* RwCameraEndUpdate(RwCamera* camera) {
    ZoneScoped;
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera) {
        ToRw(camera)->endUpdate();
    }
    return camera;
#else
    return camera->endUpdate(camera);
#endif
}

RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colour, RwInt32 clearMode) {
    ZoneScoped;
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera) {
        ToRw(camera)->clear(colour ? ToRw(colour) : nullptr, clearMode);
    }
    return camera;
#else
    return RwEngineInstance->stdFunc[rwSTANDARDCAMERACLEAR](camera, colour, clearMode) ? camera : nullptr;
#endif
}

RwCamera* RwCameraShowRaster(RwCamera* camera, void* pDev, RwUInt32 flags) {
    ZoneScoped;
#ifdef NOTSA_STANDALONE_NATIVE
    (void)pDev;
    if (camera) {
        ToRw(camera)->showRaster(flags);
    }
    return camera;
#else
    return RwRasterShowRaster(RwCameraGetRaster(camera), pDev, flags) != 0 ? camera : nullptr;
#endif
}

void RwCameraSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)blockSize;
    (void)numBlocksToPrealloc;
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7EE0F0)(blockSize, numBlocksToPrealloc);
#endif
}

RwBool RwCameraDestroy(RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera) {
        ToRw(camera)->destroy();
    }
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwCamera*))0x7EE4B0)(camera);
#endif
}

RwCamera* RwCameraCreate() {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Camera::create());
#else
    return ((RwCamera*(__cdecl *)(void))0x7EE4F0)();
#endif
}

RwCamera* RwCameraClone(RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    return camera ? FromRw(ToRw(camera)->clone()) : nullptr;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*))0x7EF3B0)(camera);
#endif
}

RwCamera* RwCameraSetViewOffset(RwCamera* camera, const RwV2d* offset) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera && offset) {
        ToRw(camera)->setViewOffset(ToRw(offset));
    }
    return camera;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*, const RwV2d*))0x7EE1A0)(camera, offset);
#endif
}

RwCamera* RwCameraSetViewWindow(RwCamera* camera, const RwV2d* viewWindow) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera && viewWindow) {
        ToRw(camera)->setViewWindow(ToRw(viewWindow));
    }
    return camera;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*, const RwV2d*))0x7EE410)(camera, viewWindow);
#endif
}

RwCamera* RwCameraSetProjection(RwCamera* camera, RwCameraProjection projection) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera) {
        ToRw(camera)->setProjection(projection);
    }
    return camera;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*, RwCameraProjection))0x7EE3A0)(camera, projection);
#endif
}

RwCamera* RwCameraSetNearClipPlane(RwCamera* camera, RwReal nearClip) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera) {
        ToRw(camera)->setNearPlane(nearClip);
    }
    return camera;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*, RwReal))0x7EE1D0)(camera, nearClip);
#endif
}

RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, RwReal farClip) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera) {
        ToRw(camera)->setFarPlane(farClip);
    }
    return camera;
#else
    return ((RwCamera*(__cdecl *)(RwCamera*, RwReal))0x7EE2A0)(camera, farClip);
#endif
}

RwInt32 RwCameraRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Camera::registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7EE450)(size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 RwCameraGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Camera::getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x7EE480)(pluginID);
#endif
}

RwBool RwCameraValidatePlugins(const RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)camera;
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RwCamera*))0x7EE4A0)(camera);
#endif
}

RwFrustumTestResult RwCameraFrustumTestSphere(const RwCamera* camera, const RwSphere* sphere) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (camera && sphere) ? (RwFrustumTestResult)ToRw(const_cast<RwCamera*>(camera))->frustumTestSphere(ToRw(sphere)) : rwSPHEREOUTSIDE;
#else
    return ((RwFrustumTestResult(__cdecl *)(const RwCamera*, const RwSphere*))0x7EE2D0)(camera, sphere);
#endif
}

RwInt32 RwCameraRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Camera::registerPluginStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x808C90)(pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 RwCameraSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Camera::setStreamAlwaysCallback(pluginID, (rw::AlwaysCallback)alwaysCB);
#else
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x808CC0)(pluginID, alwaysCB);
#endif
}

RwUInt32 RwCameraStreamGetSize(const RwCamera* camera) {
#ifdef NOTSA_STANDALONE_NATIVE
    return camera ? ToRw(const_cast<RwCamera*>(camera))->streamGetSize() : 0;
#else
    return ((RwUInt32(__cdecl *)(const RwCamera*))0x808CE0)(camera);
#endif
}

RwCamera* RwCameraStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FromRw(rw::Camera::streamRead(ToRw(stream)));
#else
    return ((RwCamera*(__cdecl *)(RwStream*))0x808DE0)(stream);
#endif
}

const RwCamera* RwCameraStreamWrite(const RwCamera* camera, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (camera) ToRw(const_cast<RwCamera*>(camera))->streamWrite(ToRw(stream));
    return camera;
#else
    return ((const RwCamera*(__cdecl *)(const RwCamera*, RwStream*))0x808D00)(camera, stream);
#endif
}

RwCameraChunkInfo* RwCameraChunkInfoRead(RwStream* stream, RwCameraChunkInfo* cameraChunkInfo, RwInt32* bytesRead) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    (void)cameraChunkInfo;
    (void)bytesRead;
    return cameraChunkInfo;
#else
    return ((RwCameraChunkInfo*(__cdecl *)(RwStream*, RwCameraChunkInfo*, RwInt32*))0x808EF0)(stream, cameraChunkInfo, bytesRead);
#endif
}

void _rwObjectHasFrameSetFrame(void *object, RwFrame *frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (object) {
        reinterpret_cast<rw::ObjectWithFrame*>(object)->setFrame(ToRw(frame));
    }
#else
    plugin::Call<0x804EF0, void*, RwFrame*>(object, frame);
#endif
}

void _rwObjectHasFrameReleaseFrame(void *object) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (object) {
        reinterpret_cast<rw::ObjectWithFrame*>(object)->setFrame(nullptr);
    }
#else
    plugin::Call<0x804F40, void*>(object);
#endif
}

RwUInt32 RwRGBAToPixel(RwRGBA* rgbIn, RwInt32 rasterFormat) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)rasterFormat;
    if (!rgbIn) return 0;
    return (rgbIn->alpha << 24) | (rgbIn->red << 16) | (rgbIn->green << 8) | rgbIn->blue;
#else
    return plugin::CallAndReturn<RwUInt32, 0x803740, RwRGBA*, RwInt32>(rgbIn, rasterFormat);
#endif
}
