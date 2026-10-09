#include "StdInc.h"

#include "rpskin.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

void RpSkinSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Managed natively by librw
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7C67F0)(blockSize, numBlocksToPrealloc);
#endif
}

RwBool RpSkinPluginAttach() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Skin::registerPlugin();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7C6820)();
#endif
}

RpAtomic* RpSkinAtomicSetHAnimHierarchy(RpAtomic* atomic, RpHAnimHierarchy* hierarchy) {
#ifdef NOTSA_STANDALONE_NATIVE
    return atomic;
#else
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RpHAnimHierarchy*))0x7C7520)(atomic, hierarchy);
#endif
}

RpHAnimHierarchy* RpSkinAtomicGetHAnimHierarchy(const RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (!atomic) return nullptr;
    auto* a = reinterpret_cast<const rw::Atomic*>(atomic);
    return a->getFrame() ? (RpHAnimHierarchy*)rw::HAnimHierarchy::get(a->getFrame()) : nullptr;
#else
    return ((RpHAnimHierarchy*(__cdecl *)(const RpAtomic*))0x7C7540)(atomic);
#endif
}

RpGeometry* RpSkinGeometrySetSkin(RpGeometry* geometry, RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return geometry;
#else
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RpSkin*))0x7C7560)(geometry, skin);
#endif
}

RpSkin* RpSkinGeometryGetSkin(RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    return geometry ? (RpSkin*)rw::Skin::get(reinterpret_cast<rw::Geometry*>(geometry)) : nullptr;
#else
    return ((RpSkin*(__cdecl *)(RpGeometry*))0x7C7550)(geometry);
#endif
}

RpSkin* RpSkinCreate(RwUInt32 numVertices, RwUInt32 numBones, RwMatrixWeights* vertexWeights, RwUInt32* vertexIndices, RwMatrix* inverseMatrices) {
#ifdef NOTSA_STANDALONE_NATIVE
    auto* skin = new rw::Skin();
    skin->init(numBones, numBones, numVertices);
    return (RpSkin*)skin;
#else
    return ((RpSkin*(__cdecl *)(RwUInt32, RwUInt32, RwMatrixWeights*, RwUInt32*, RwMatrix*))0x7C75B0)(numVertices, numBones, vertexWeights, vertexIndices, inverseMatrices);
#endif
}

RpSkin* RpSkinDestroy(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (skin) {
        delete reinterpret_cast<rw::Skin*>(skin);
    }
    return nullptr;
#else
    return ((RpSkin*(__cdecl *)(RpSkin*))0x7C77A0)(skin);
#endif
}

RwUInt32 RpSkinGetNumBones(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return skin ? reinterpret_cast<rw::Skin*>(skin)->numBones : 0;
#else
    return ((RwUInt32(__cdecl *)(RpSkin*))0x7C77E0)(skin);
#endif
}

/*const*/ RwMatrixWeights* RpSkinGetVertexBoneWeights(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return skin ? reinterpret_cast<RwMatrixWeights*>(reinterpret_cast<rw::Skin*>(skin)->weights) : nullptr;
#else
    return ((RwMatrixWeights*(__cdecl *)(RpSkin*))0x7C77F0)(skin);
#endif
}

const RwUInt32* RpSkinGetVertexBoneIndices(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((const RwUInt32*(__cdecl *)(RpSkin*))0x7C7800)(skin);
#endif
}

const RwMatrix* RpSkinGetSkinToBoneMatrices(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return skin ? reinterpret_cast<const RwMatrix*>(reinterpret_cast<rw::Skin*>(skin)->inverseMatrices) : nullptr;
#else
    return ((const RwMatrix*(__cdecl *)(RpSkin*))0x7C7810)(skin);
#endif
}

RwBool RpSkinIsSplit(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RpSkin*))0x7C7820)(skin);
#endif
}

RpAtomic* RpSkinAtomicSetType(RpAtomic* atomic, RpSkinType type) {
#ifdef NOTSA_STANDALONE_NATIVE
    return atomic;
#else
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RpSkinType))0x7C7830)(atomic, type);
#endif
}

RpSkinType RpSkinAtomicGetType(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rpSKINTYPEMATRIXBLEND;
#else
    return ((RpSkinType(__cdecl *)(RpAtomic*))0x7C7880)(atomic);
#endif
}

RpGeometry* _rpSkinInitialize(RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    return geometry;
#else
    return ((RpGeometry*(__cdecl *)(RpGeometry*))0x7C8740)(geometry);
#endif
}

RpGeometry* _rpSkinDeinitialize(RpGeometry* geometry) {
#ifdef NOTSA_STANDALONE_NATIVE
    return geometry;
#else
    return ((RpGeometry*(__cdecl *)(RpGeometry*))0x7C8820)(geometry);
#endif
}

RwUInt8* _rpSkinGetMeshBoneRemapIndices(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwUInt8*(__cdecl *)(RpSkin*))0x7C8A40)(skin);
#endif
}

RwUInt8* _rpSkinGetMeshBoneRLECount(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwUInt8*(__cdecl *)(RpSkin*))0x7C8A50)(skin);
#endif
}

RwUInt8* _rpSkinGetMeshBoneRLE(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwUInt8*(__cdecl *)(RpSkin*))0x7C8A60)(skin);
#endif
}

RpSkin* _rpSkinSplitDataCreate(RpSkin* skin, RwUInt32 boneLimit, RwUInt32 numMatrices, RwUInt32 numMeshes, RwUInt32 numRLE) {
#ifdef NOTSA_STANDALONE_NATIVE
    return skin;
#else
    return ((RpSkin*(__cdecl *)(RpSkin*, RwUInt32, RwUInt32, RwUInt32, RwUInt32))0x7C8A70)(skin, boneLimit, numMatrices, numMeshes, numRLE);
#endif
}

RwBool _rpSkinSplitDataDestroy(RpSkin* skin) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpSkin*))0x7C8B10)(skin);
#endif
}

RxNodeDefinition* RxNodeDefinitionGetD3D9SkinAtomicAllInOne() {
#ifdef NOTSA_STANDALONE_NATIVE
    static RxNodeDefinition s_SkinNodeDef{};
    return &s_SkinNodeDef;
#else
    return ((RxNodeDefinition*(__cdecl *)(void))0x7CB2A0)();
#endif
}
