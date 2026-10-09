#include "StdInc.h"

#include "rpuvanim.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

_rpUVAnimCustomData* _rpUVAnimCustomDataStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((_rpUVAnimCustomData*(__cdecl *)(RwStream*))0x7CBF70)(stream);
#endif
}

const _rpUVAnimCustomData* _rpUVAnimCustomDataStreamWrite(const _rpUVAnimCustomData* customData, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return customData;
#else
    return ((const _rpUVAnimCustomData*(__cdecl *)(const _rpUVAnimCustomData*, RwStream*))0x7CBFD0)(customData, stream);
#endif
}

RwUInt32 _rpUVAnimCustomDataStreamGetSize(const _rpUVAnimCustomData* customData) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwUInt32(__cdecl *)(const _rpUVAnimCustomData*))0x7CC010)(customData);
#endif
}

RwBool RpUVAnimPluginAttach() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::UVAnimPluginAttach();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7CB940)();
#endif
}

void RpUVAnimLinearKeyFrameApply(void* matrix, void* voidIFrame) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*))0x7CC9F0)(matrix, voidIFrame);
#endif
}

void RpUVAnimLinearKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*, void*, RwReal))0x7CCAC0)(voidOut, voidIn1, voidIn2, alpha);
#endif
}

void RpUVAnimLinearKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*, void*, RwReal, void*))0x7CCA40)(voidOut, voidIn1, voidIn2, time, customData);
#endif
}

void RpUVAnimLinearKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*, void*))0x7CCBE0)(voidOut, voidIn1, voidIn2);
#endif
}

void RpUVAnimLinearKeyFrameMulRecip(void* voidFrame, void* voidStart) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*))0x7CCB30)(voidFrame, voidStart);
#endif
}

void RpUVAnimParamKeyFrameApply(void* matrix, void* voidIFrame) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*))0x7CC560)(matrix, voidIFrame);
#endif
}

void RpUVAnimParamKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*, void*, RwReal))0x7CC6A0)(voidOut, voidIn1, voidIn2, alpha);
#endif
}

void RpUVAnimParamKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*, void*, RwReal, void*))0x7CC600)(voidOut, voidIn1, voidIn2, time, customData);
#endif
}

void RpUVAnimParamKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*, void*))0x7CC750)(voidOut, voidIn1, voidIn2);
#endif
}

void RpUVAnimParamKeyFrameMulRecip(void* voidFrame, void* voidStart) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void*, void*))0x7CC740)(voidFrame, voidStart);
#endif
}

RtAnimAnimation* RpUVAnimKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RtAnimAnimation*)rw::Animation::streamRead(reinterpret_cast<rw::Stream*>(stream));
#else
    return ((RtAnimAnimation*(__cdecl *)(RwStream*, RtAnimAnimation*))0x7CC870)(stream, animation);
#endif
}

RwBool RpUVAnimKeyFrameStreamWrite(const RtAnimAnimation* animation, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return animation && stream ? (RwBool)reinterpret_cast<const rw::Animation*>(animation)->streamWrite(reinterpret_cast<rw::Stream*>(stream)) : FALSE;
#else
    return ((RwBool(__cdecl *)(const RtAnimAnimation*, RwStream*))0x7CC920)(animation, stream);
#endif
}

RwInt32 RpUVAnimKeyFrameStreamGetSize(const RtAnimAnimation* animation) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(const RtAnimAnimation*))0x7CC9D0)(animation);
#endif
}

RpUVAnim* RpUVAnimCreate(const RwChar* name, RwUInt32 numNodes, RwUInt32 numFrames, RwReal duration, RwUInt32* nodeIndexToUVChannelMap, RpUVAnimKeyFrameType keyframeType) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RpUVAnim*(__cdecl *)(const RwChar*, RwUInt32, RwUInt32, RwReal, RwUInt32*, RpUVAnimKeyFrameType))0x7CC020)(name, numNodes, numFrames, duration, nodeIndexToUVChannelMap, keyframeType);
#endif
}

RwBool RpUVAnimDestroy(RpUVAnim* anim) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RpUVAnim*))0x7CC0C0)(anim);
#endif
}

RpUVAnim* RpUVAnimAddRef(RpUVAnim* anim) {
#ifdef NOTSA_STANDALONE_NATIVE
    return anim;
#else
    return ((RpUVAnim*(__cdecl *)(RpUVAnim*))0x7CC100)(anim);
#endif
}

const RwChar* RpUVAnimGetName(const RpUVAnim* anim) {
#ifdef NOTSA_STANDALONE_NATIVE
    return "";
#else
    return ((const RwChar*(__cdecl *)(const RpUVAnim*))0x7CC3A0)(anim);
#endif
}

RpMaterial* RpMaterialSetUVAnim(RpMaterial* material, RpUVAnim* anim, RwUInt32 slot) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RpUVAnim*, RwUInt32))0x7CC3B0)(material, anim, slot);
#endif
}

RpUVAnimInterpolator* RpMaterialUVAnimGetInterpolator(RpMaterial* material, RwUInt32 slot) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RpUVAnimInterpolator*(__cdecl *)(RpMaterial*, RwUInt32))0x7CC430)(material, slot);
#endif
}

RpMaterial* RpMaterialUVAnimSetInterpolator(RpMaterial* material, RpUVAnimInterpolator* interp, RwUInt32 slot) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RpUVAnimInterpolator*, RwUInt32))0x7CC450)(material, interp, slot);
#endif
}

RpMaterial* RpMaterialUVAnimSetCurrentTime(RpMaterial* material, RwReal time) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x7CC470)(material, time);
#endif
}

RpMaterial* RpMaterialUVAnimAddAnimTime(RpMaterial* material, RwReal deltaTime) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x7CC4B0)(material, deltaTime);
#endif
}

RpMaterial* RpMaterialUVAnimSubAnimTime(RpMaterial* material, RwReal deltaTime) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x7CC4F0)(material, deltaTime);
#endif
}

RpMaterial* RpMaterialUVAnimApplyUpdate(RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return plugin::CallAndReturn<RpMaterial*, 0x7CC110, RpMaterial*>(material);
#endif
}

RwBool RpMaterialUVAnimExists(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FALSE;
#else
    return ((RwBool(__cdecl *)(const RpMaterial*))0x7CC530)(material);
#endif
}
