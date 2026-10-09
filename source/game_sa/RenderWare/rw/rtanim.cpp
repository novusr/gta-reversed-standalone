#ifndef NOTSA_STANDALONE_NATIVE
#include "StdInc.h"
#else
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "Base.h"
#include "RenderWare/RenderWare.h"
#endif

#ifndef NOTSA_STANDALONE_NATIVE
#include "rpdbgerr.h"
#endif
#include "rtanim.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
using namespace notsa::rwbridge;
#endif

void RtAnimAnimationFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Handled by librw
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7CCC80)(blockSize, numBlocksToPrealloc);
#endif
}

RwBool RtAnimInitialize() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7CCCA0)();
#endif
}

RwBool RtAnimRegisterInterpolationScheme(RtAnimInterpolatorInfo* interpolatorInfo) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (interpolatorInfo) {
        auto* info = rw::AnimInterpolatorInfo::find(interpolatorInfo->typeID);
        if (!info) {
            info = new rw::AnimInterpolatorInfo();
            info->id = interpolatorInfo->typeID;
            info->interpKeyFrameSize = interpolatorInfo->interpKeyFrameSize;
            info->animKeyFrameSize = interpolatorInfo->animKeyFrameSize;
            info->customDataSize = 0;
            info->applyCB = (rw::AnimInterpolatorInfo::ApplyCB)interpolatorInfo->keyFrameApplyCB;
            info->blendCB = (rw::AnimInterpolatorInfo::BlendCB)interpolatorInfo->keyFrameBlendCB;
            info->interpCB = (rw::AnimInterpolatorInfo::InterpCB)interpolatorInfo->keyFrameInterpolateCB;
            info->addCB = (rw::AnimInterpolatorInfo::AddCB)interpolatorInfo->keyFrameAddCB;
            info->mulRecipCB = (rw::AnimInterpolatorInfo::MulRecipCB)interpolatorInfo->keyFrameMulRecipCB;
            rw::AnimInterpolatorInfo::registerInterp(info);
        }
        return TRUE;
    }
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolatorInfo*))0x7CCD40)(interpolatorInfo);
#endif
}

RtAnimInterpolatorInfo* RtAnimGetInterpolatorInfo(RwInt32 typeID) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)typeID;
    return nullptr;
#else
    return ((RtAnimInterpolatorInfo*(__cdecl *)(RwInt32))0x7CCDE0)(typeID);
#endif
}

RtAnimAnimation* RtAnimAnimationCreate(RwInt32 typeID, RwInt32 numFrames, RwInt32 flags, RwReal duration) {
#ifdef NOTSA_STANDALONE_NATIVE
    auto* info = rw::AnimInterpolatorInfo::find(typeID);
    if (!info) {
        auto* defaultInfo = new rw::AnimInterpolatorInfo();
        defaultInfo->id = typeID;
        defaultInfo->interpKeyFrameSize = 64;
        defaultInfo->animKeyFrameSize = 64;
        defaultInfo->customDataSize = 0;
        rw::AnimInterpolatorInfo::registerInterp(defaultInfo);
        info = defaultInfo;
    }
    return (RtAnimAnimation*)rw::Animation::create(info, numFrames, flags, duration);
#else
    return ((RtAnimAnimation*(__cdecl *)(RwInt32, RwInt32, RwInt32, RwReal))0x7CCE40)(typeID, numFrames, flags, duration);
#endif
}

RwBool RtAnimAnimationDestroy(RtAnimAnimation* animation) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (animation) {
        reinterpret_cast<rw::Animation*>(animation)->destroy();
        return TRUE;
    }
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RtAnimAnimation*))0x7CCF10)(animation);
#endif
}

RtAnimAnimation* RtAnimAnimationRead(const RwChar* filename) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RtAnimAnimation*(__cdecl *)(const RwChar*))0x7CCF30)(filename);
#endif
}

RwBool RtAnimAnimationWrite(const RtAnimAnimation* animation, const RwChar* filename) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FALSE;
#else
    return ((RwBool(__cdecl *)(const RtAnimAnimation*, const RwChar*))0x7CD160)(animation, filename);
#endif
}

RtAnimAnimation* RtAnimAnimationStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RtAnimAnimation*)rw::Animation::streamRead(reinterpret_cast<rw::Stream*>(stream));
#else
    return ((RtAnimAnimation*(__cdecl *)(RwStream*))0x7CD220)(stream);
#endif
}

RwBool RtAnimAnimationStreamWrite(const RtAnimAnimation* animation, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return animation && stream ? (RwBool)const_cast<rw::Animation*>(reinterpret_cast<const rw::Animation*>(animation))->streamWrite(reinterpret_cast<rw::Stream*>(stream)) : FALSE;
#else
    return ((RwBool(__cdecl *)(const RtAnimAnimation*, RwStream*))0x7CD410)(animation, stream);
#endif
}

RwInt32 RtAnimAnimationStreamGetSize(const RtAnimAnimation* animation) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(const RtAnimAnimation*))0x7CD4D0)(animation);
#endif
}

RwUInt32 RtAnimAnimationGetNumNodes(const RtAnimAnimation* animation) {
#ifdef NOTSA_STANDALONE_NATIVE
    return animation ? reinterpret_cast<const rw::Animation*>(animation)->numFrames : 0;
#else
    return ((RwUInt32(__cdecl *)(const RtAnimAnimation*))0x7CD4F0)(animation);
#endif
}

RtAnimInterpolator* RtAnimInterpolatorCreate(RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RtAnimInterpolator*)rw::AnimInterpolator::create(numNodes, maxInterpKeyFrameSize);
#else
    return ((RtAnimInterpolator*(__cdecl *)(RwInt32, RwInt32))0x7CD520)(numNodes, maxInterpKeyFrameSize);
#endif
}

void RtAnimInterpolatorDestroy(RtAnimInterpolator* anim) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (anim) {
        reinterpret_cast<rw::AnimInterpolator*>(anim)->destroy();
    }
#else
    ((void(__cdecl *)(RtAnimInterpolator*))0x7CD590)(anim);
#endif
}
 
/**
 * \ingroup rtanim
 * \ref RtAnimInterpolatorSetCurrentAnim sets the current animation on the
 * animation interpolator. It is assumed that the animation is designed for the
 * animation interpolator it is being set on since no animation interpolator structure
 * comparisons are made. The animation defines the interpolation schemes used
 * and they will be setup on the animation interpolator at this call. The maximum
 * keyframe size of the animation interpolator must be sufficient to support the
 * keyframe size required by the interpolation scheme. The animation is
 * initialized to time zero at this call.
 *
 * \param animI Pointer to the \ref RtAnimInterpolator.
 * \param anim Pointer to the \ref RtAnimAnimation.
 *
 * \return \ref RwBool, TRUE on success, FALSE if an error occurs.
 *
 */
RwBool
RtAnimInterpolatorSetCurrentAnim(RtAnimInterpolator *animI,
                               RtAnimAnimation *anim)
{
#ifdef NOTSA_STANDALONE_NATIVE
    if (animI && anim) {
        return reinterpret_cast<rw::AnimInterpolator*>(animI)->setCurrentAnim(reinterpret_cast<rw::Animation*>(anim)) ? TRUE : FALSE;
    }
    return FALSE;
#else
    RtAnimInterpolatorInfo     *interpInfo;
    RwInt32                     i;
    void                       *kf1, *kf2, *interpFrame;

    RWAPIFUNCTION(RWSTRING("RtAnimInterpolatorSetCurrentAnim"));
    RWASSERT(animI);
    RWASSERT(anim);
    RWASSERT(anim->numFrames >= animI->numNodes * 2);

    animI->pCurrentAnim = anim;
    animI->currentTime = 0.0f;

    /* Get interpolator functions */
    interpInfo = anim->interpInfo;
    animI->currentInterpKeyFrameSize = interpInfo->interpKeyFrameSize;
    RWASSERT(animI->currentInterpKeyFrameSize <= animI->maxInterpKeyFrameSize);
    animI->currentAnimKeyFrameSize = interpInfo->animKeyFrameSize;

    animI->keyFrameApplyCB = interpInfo->keyFrameApplyCB;
    animI->keyFrameBlendCB = interpInfo->keyFrameBlendCB;
    animI->keyFrameInterpolateCB = interpInfo->keyFrameInterpolateCB;
    animI->keyFrameAddCB = interpInfo->keyFrameAddCB;

    /*
     * Set up initial interpolation frames for time=0
     * First copy the time=0 keyframes to the interpolated frame array
     */
    //TODO: convert these don't copy
    for (i=0; i < animI->numNodes; i++)
    {
        animI->keyFrameInterpolateCB(rtANIMGETINTERPFRAME(animI, i),
                                     ((RwUInt8 *)anim->pFrames) + (i * animI->currentAnimKeyFrameSize),
                                     ((RwUInt8 *)anim->pFrames) + ((i + animI->numNodes) * animI->currentAnimKeyFrameSize),
                                     0.0f, anim->customData);
    }

    /*
     * Now initialize the interpolated frame headers to point to the initial
     * keyframe pairs.
     */
    if (!notsa::IsFixBugs() || anim->interpInfo->typeID != rwID_RPANIMBLENDPLUGIN) {
        /*
         * In RW there is an RtAnimAnimation, which holds the raw keyframes of an animation.
         * To play an animation, an RtAnimAnimation is given to an RtAnimInterpolator which
         * then interpolates the keyframes into interpolation frames which are then used to
         * animate e.g. a hierarchy by generating matrices from them.
         * But R* hasn't really used RW's animation system since III.
         * In III and VC R* wrote their own interpolated animation data into a dummy
         * RtAnimAnimation and practically didn't use the RtAnimInterpolator.
         * In SA they went a step further and now write into the interpolation frames of
         * the RtAnimInterpolator instead, almost completely avoid RtAnimAnimation.
         * Almost! They're still attaching an RtAnimAnimation to an RtAnimInterpolator
         * and this is where stuff breaks.
         *
         * So, instead of corrupting our lovely `RpHAnimBlendInterpFrame`'s, we leave them alone ;)
         *
         * For more info see: https://gtaforums.com/topic/669045-silentpatch/page/154/#comment-1068971599
         */

        interpFrame = rtANIMGETINTERPFRAME(animI, 0);
        kf1 = anim->pFrames;
        kf2 = (RwInt8 *)anim->pFrames + animI->numNodes * animI->currentAnimKeyFrameSize;

        for (i=0; i < animI->numNodes; i++)
        {
            RtAnimInterpFrameHeader  *hdr = (RtAnimInterpFrameHeader *)interpFrame;

            hdr->keyFrame1 = (RtAnimKeyFrameHeader*)kf1;
            hdr->keyFrame2 = (RtAnimKeyFrameHeader*)kf2;
           
            interpFrame = (RwInt8 *)interpFrame + animI->currentInterpKeyFrameSize;
            kf1 = (RwInt8 *)kf1 + animI->currentAnimKeyFrameSize;
            kf2 = (RwInt8 *)kf2 + animI->currentAnimKeyFrameSize;
        }
    }
    animI->pNextFrame = (RwUInt8 *)anim->pFrames + (animI->numNodes * animI->currentAnimKeyFrameSize * 2);

    RWRETURN(TRUE);
#endif
}

RwBool RtAnimInterpolatorSetKeyFrameCallBacks(RtAnimInterpolator* anim, RwInt32 keyFrameTypeID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RwInt32))0x7CD660)(anim, keyFrameTypeID);
#endif
}

void RtAnimInterpolatorSetAnimLoopCallBack(RtAnimInterpolator* anim, RtAnimCallBack callBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Standalone native: loop callback
#else
    ((void(__cdecl *)(RtAnimInterpolator*, RtAnimCallBack, void*))0x7CD6F0)(anim, callBack, data);
#endif
}

void RtAnimInterpolatorSetAnimCallBack(RtAnimInterpolator* anim, RtAnimCallBack callBack, RwReal time, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Standalone native: anim callback
#else
    ((void(__cdecl *)(RtAnimInterpolator*, RtAnimCallBack, RwReal, void*))0x7CD710)(anim, callBack, time, data);
#endif
}

RwBool RtAnimInterpolatorCopy(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*))0x7CD730)(outAnim, inAnim);
#endif
}

RwBool RtAnimInterpolatorSubAnimTime(RtAnimInterpolator* anim, RwReal time) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RwReal))0x7CD760)(anim, time);
#endif
}

RwBool RtAnimInterpolatorAddAnimTime(RtAnimInterpolator* anim, RwReal time) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (anim) {
        reinterpret_cast<rw::AnimInterpolator*>(anim)->addTime(time);
        return TRUE;
    }
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RwReal))0x7CD8D0)(anim, time);
#endif
}

RwBool RtAnimInterpolatorSetCurrentTime(RtAnimInterpolator* anim, RwReal time) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RwReal))0x7CDAB0)(anim, time);
#endif
}

RwBool RtAnimAnimationMakeDelta(RtAnimAnimation* animation, RwInt32 numNodes, RwReal time) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimAnimation*, RwInt32, RwReal))0x7CDB00)(animation, numNodes, time);
#endif
}

RwBool RtAnimInterpolatorBlend(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2, RwReal alpha) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*, RwReal))0x7CDBF0)(outAnim, inAnim1, inAnim2, alpha);
#endif
}

RwBool RtAnimInterpolatorAddTogether(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*))0x7CDC50)(outAnim, inAnim1, inAnim2);
#endif
}

RtAnimInterpolator* RtAnimInterpolatorCreateSubInterpolator(RtAnimInterpolator* parentAnim, RwInt32 startNode, RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RtAnimInterpolator*)rw::AnimInterpolator::create(numNodes, maxInterpKeyFrameSize);
#else
    return ((RtAnimInterpolator*(__cdecl *)(RtAnimInterpolator*, RwInt32, RwInt32, RwInt32))0x7CDCB0)(parentAnim, startNode, numNodes, maxInterpKeyFrameSize);
#endif
}

RwBool RtAnimInterpolatorBlendSubInterpolator(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2, RwReal alpha) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*, RwReal))0x7CDCF0)(outAnim, inAnim1, inAnim2, alpha);
#endif
}

RwBool RtAnimInterpolatorAddSubInterpolator(RtAnimInterpolator* outAnim, RtAnimInterpolator* mainAnim, RtAnimInterpolator* subAnim) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*))0x7CDEF0)(outAnim, mainAnim, subAnim);
#endif
}

void RtAnim::InjectHooks() {
#ifdef NOTSA_STANDALONE_NATIVE
    return;
#else
    RH_ScopedNamespaceName("RtAnim");
    RH_ScopedCategory("Plugins");

    RH_ScopedGlobalInstall(RtAnimInterpolatorSetCurrentAnim, 0x7CD5A0);
#endif
}
