#include "StdInc.h"

#include "rphanim.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

void RpHAnimHierarchySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Managed natively by librw
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7C45E0)(blockSize, numBlocksToPrealloc);
#endif
}

RpHAnimHierarchy* RpHAnimHierarchyCreate(RwInt32 numNodes, RwUInt32* nodeFlags, RwInt32* nodeIDs, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RpHAnimHierarchy*)rw::HAnimHierarchy::create(numNodes, reinterpret_cast<int32*>(nodeFlags), nodeIDs, static_cast<int32>(flags), maxInterpKeyFrameSize);
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RwInt32, RwUInt32*, RwInt32*, RpHAnimHierarchyFlag, RwInt32))0x7C4C30)(numNodes, nodeFlags, nodeIDs, flags, maxInterpKeyFrameSize);
#endif
}

RpHAnimHierarchy* RpHAnimHierarchyCreateFromHierarchy(RpHAnimHierarchy* hierarchy, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (!hierarchy) return nullptr;
    return (RpHAnimHierarchy*)rw::HAnimHierarchy::create(hierarchy->numNodes, nullptr, nullptr, static_cast<int32>(flags), maxInterpKeyFrameSize);
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*, RpHAnimHierarchyFlag, RwInt32))0x7C4ED0)(hierarchy, flags, maxInterpKeyFrameSize);
#endif
}

RpHAnimHierarchy* RpHAnimHierarchyDestroy(RpHAnimHierarchy* hierarchy) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (hierarchy) {
        reinterpret_cast<rw::HAnimHierarchy*>(hierarchy)->destroy();
    }
    return hierarchy;
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*))0x7C4D30)(hierarchy);
#endif
}

RpHAnimHierarchy* RpHAnimHierarchyCreateSubHierarchy(RpHAnimHierarchy* parentHierarchy, RwInt32 startNode, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (!parentHierarchy) return nullptr;
    return (RpHAnimHierarchy*)rw::HAnimHierarchy::create(parentHierarchy->numNodes - startNode, nullptr, nullptr, static_cast<int32>(flags), maxInterpKeyFrameSize);
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*, RwInt32, RpHAnimHierarchyFlag, RwInt32))0x7C4DB0)(parentHierarchy, startNode, flags, maxInterpKeyFrameSize);
#endif
}

RpHAnimHierarchy* RpHAnimHierarchyAttach(RpHAnimHierarchy* hierarchy) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (hierarchy) {
        reinterpret_cast<rw::HAnimHierarchy*>(hierarchy)->attach();
    }
    return hierarchy;
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*))0x7C4F40)(hierarchy);
#endif
}

RpHAnimHierarchy* RpHAnimHierarchyDetach(RpHAnimHierarchy* hierarchy) {
#ifdef NOTSA_STANDALONE_NATIVE
    return hierarchy;
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*))0x7C4FF0)(hierarchy);
#endif
}

RpHAnimHierarchy* RpHAnimHierarchyAttachFrameIndex(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (hierarchy) {
        reinterpret_cast<rw::HAnimHierarchy*>(hierarchy)->attachByIndex(nodeIndex);
    }
    return hierarchy;
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*, RwInt32))0x7C5020)(hierarchy, nodeIndex);
#endif
}

RpHAnimHierarchy* RpHAnimHierarchyDetachFrameIndex(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex) {
#ifdef NOTSA_STANDALONE_NATIVE
    return hierarchy;
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*, RwInt32))0x7C5100)(hierarchy, nodeIndex);
#endif
}

RwBool RpHAnimFrameSetHierarchy(RwFrame* frame, RpHAnimHierarchy* hierarchy) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwFrame*, RpHAnimHierarchy*))0x7C5130)(frame, hierarchy);
#endif
}

RpHAnimHierarchy* RpHAnimFrameGetHierarchy(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    return frame ? (RpHAnimHierarchy*)rw::HAnimHierarchy::get(reinterpret_cast<rw::Frame*>(frame)) : nullptr;
#else
    return ((RpHAnimHierarchy*(__cdecl *)(RwFrame*))0x7C5160)(frame);
#endif
}

RwMatrix* RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy* hierarchy) {
#ifdef NOTSA_STANDALONE_NATIVE
    return hierarchy ? reinterpret_cast<RwMatrix*>(reinterpret_cast<rw::HAnimHierarchy*>(hierarchy)->matrices) : nullptr;
#else
    return ((RwMatrix*(__cdecl *)(RpHAnimHierarchy*))0x7C5120)(hierarchy);
#endif
}

// NOTSA
RwMatrix* RpHAnimHierarchyGetNodeMatrix(RpHAnimHierarchy* hierarchy, RwInt32 nodeID) {
    const auto i = RpHAnimIDGetIndex(hierarchy, nodeID);
    assert(i >= 0 && i < hierarchy->numNodes);
    return &RpHAnimHierarchyGetMatrixArray(hierarchy)[i];
}

RwBool RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy* hierarchy) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (hierarchy) {
        reinterpret_cast<rw::HAnimHierarchy*>(hierarchy)->updateMatrices();
        return TRUE;
    }
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RpHAnimHierarchy*))0x7C51D0)(hierarchy);
#endif
}

RwInt32 RpHAnimIDGetIndex(RpHAnimHierarchy* hierarchy, RwInt32 ID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return hierarchy ? reinterpret_cast<rw::HAnimHierarchy*>(hierarchy)->getIndex(ID) : -1;
#else
    return ((RwInt32(__cdecl *)(RpHAnimHierarchy*, RwInt32))0x7C51A0)(hierarchy, ID);
#endif
}

RwBool RpHAnimPluginAttach() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::HAnimPluginAttach();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7C4600)();
#endif
}

void RpHAnimKeyFrameApply(void* matrix, void* voidIFrame) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Fallback keyframe apply
#else
    ((void(__cdecl *)(void*, void*))0x7C5B80)(matrix, voidIFrame);
#endif
}

void RpHAnimKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Fallback keyframe blend
#else
    ((void(__cdecl *)(void*, void*, void*, RwReal))0x7C60C0)(voidOut, voidIn1, voidIn2, alpha);
#endif
}

void RpHAnimKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Fallback keyframe interpolate
#else
    ((void(__cdecl *)(void*, void*, void*, RwReal, void*))0x7C5CA0)(voidOut, voidIn1, voidIn2, time, customData);
#endif
}

void RpHAnimKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Fallback keyframe add
#else
    ((void(__cdecl *)(void*, void*, void*))0x7C6720)(voidOut, voidIn1, voidIn2);
#endif
}

void RpHAnimKeyFrameMulRecip(void* voidFrame, void* voidStart) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Fallback keyframe mul recip
#else
    ((void(__cdecl *)(void*, void*))0x7C65C0)(voidFrame, voidStart);
#endif
}

RtAnimAnimation* RpHAnimKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RtAnimAnimation*)rw::Animation::streamRead(reinterpret_cast<rw::Stream*>(stream));
#else
    return ((RtAnimAnimation*(__cdecl *)(RwStream*, RtAnimAnimation*))0x7C64C0)(stream, animation);
#endif
}

RwBool RpHAnimKeyFrameStreamWrite(const RtAnimAnimation* animation, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return animation && stream ? (RwBool)reinterpret_cast<const rw::Animation*>(animation)->streamWrite(reinterpret_cast<rw::Stream*>(stream)) : FALSE;
#else
    return ((RwBool(__cdecl *)(const RtAnimAnimation*, RwStream*))0x7C6540)(animation, stream);
#endif
}

RwInt32 RpHAnimKeyFrameStreamGetSize(const RtAnimAnimation* animation) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(const RtAnimAnimation*))0x7C65B0)(animation);
#endif
}

RwBool RpHAnimFrameSetID(RwFrame* frame, RwInt32 id) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwFrame*, RwInt32))0x7C5170)(frame, id);
#endif
}

RwInt32 RpHAnimFrameGetID(RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(RwFrame*))0x7C5190)(frame);
#endif
}
