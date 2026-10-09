#include "StdInc.h"

#include "rpmatfx.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

void RpMatFXMaterialDataSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Handled by librw
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x810700)(blockSize, numBlocksToPrealloc);
#endif
}

RwBool RpMatFXPluginAttach() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::MatFX::registerPlugin();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x810AA0)();
#endif
}

RpAtomic* RpMatFXAtomicEnableEffects(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    return atomic;
#else
    return ((RpAtomic*(__cdecl *)(RpAtomic*))0x811C00)(atomic);
#endif
}

RwBool RpMatFXAtomicQueryEffects(RpAtomic* atomic) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RpAtomic*))0x811C30)(atomic);
#endif
}

RpWorldSector* RpMatFXWorldSectorEnableEffects(RpWorldSector* worldSector) {
#ifdef NOTSA_STANDALONE_NATIVE
    return worldSector;
#else
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*))0x811C40)(worldSector);
#endif
}

RwBool RpMatFXWorldSectorQueryEffects(RpWorldSector* worldSector) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RpWorldSector*))0x811C70)(worldSector);
#endif
}

RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* material, RpMatFXMaterialFlags flags) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) {
        rw::MatFX::setEffects(reinterpret_cast<rw::Material*>(material), flags);
    }
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RpMatFXMaterialFlags))0x811C80)(material, flags);
#endif
}

RpMaterial* RpMatFXMaterialSetupBumpMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwReal coef) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwFrame*, RwReal))0x811E00)(material, texture, frame, coef);
#endif
}

RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwBool useFrameBufferAlpha, RwReal coef) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) {
        auto* m = rw::MatFX::get(reinterpret_cast<rw::Material*>(material));
        if (m) {
            m->setEnvTexture(reinterpret_cast<rw::Texture*>(texture));
            m->setEnvCoefficient(coef);
        }
    }
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwFrame*, RwBool, RwReal))0x811ED0)(material, texture, frame, useFrameBufferAlpha, coef);
#endif
}

RpMaterial* RpMatFXMaterialSetupDualTexture(RpMaterial* material, RwTexture* texture, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwBlendFunction, RwBlendFunction))0x812040)(material, texture, srcBlendMode, dstBlendMode);
#endif
}

RpMatFXMaterialFlags RpMatFXMaterialGetEffects(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rpMATFXEFFECTNULL;
#else
    return ((RpMatFXMaterialFlags(__cdecl *)(const RpMaterial*))0x812140)(material);
#endif
}

RpMaterial* RpMatFXMaterialSetBumpMapTexture(RpMaterial* material, RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812160)(material, texture);
#endif
}

RpMaterial* RpMatFXMaterialSetBumpMapFrame(RpMaterial* material, RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwFrame*))0x812320)(material, frame);
#endif
}

RpMaterial* RpMatFXMaterialSetBumpMapCoefficient(RpMaterial* material, RwReal coef) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x812380)(material, coef);
#endif
}

RwTexture* RpMatFXMaterialGetBumpMapTexture(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x812430)(material);
#endif
}

RwTexture* RpMatFXMaterialGetBumpMapBumpedTexture(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x8123E0)(material);
#endif
}

RwFrame* RpMatFXMaterialGetBumpMapFrame(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwFrame*(__cdecl *)(const RpMaterial*))0x812480)(material);
#endif
}

RwReal RpMatFXMaterialGetBumpMapCoefficient(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0.0f;
#else
    return ((RwReal(__cdecl *)(const RpMaterial*))0x8124D0)(material);
#endif
}

RpMaterial* RpMatFXMaterialSetEnvMapTexture(RpMaterial* material, RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) {
        auto* m = rw::MatFX::get(reinterpret_cast<rw::Material*>(material));
        if (m) m->setEnvTexture(reinterpret_cast<rw::Texture*>(texture));
    }
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812530)(material, texture);
#endif
}

RpMaterial* RpMatFXMaterialSetEnvMapFrame(RpMaterial* material, RwFrame* frame) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwFrame*))0x8125B0)(material, frame);
#endif
}

RpMaterial* RpMatFXMaterialSetEnvMapFrameBufferAlpha(RpMaterial* material, RwBool useFrameBufferAlpha) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwBool))0x812610)(material, useFrameBufferAlpha);
#endif
}

RpMaterial* RpMatFXMaterialSetEnvMapCoefficient(RpMaterial* material, RwReal coef) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) {
        auto* m = rw::MatFX::get(reinterpret_cast<rw::Material*>(material));
        if (m) m->setEnvCoefficient(coef);
    }
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x812680)(material, coef);
#endif
}

RwTexture* RpMatFXMaterialGetEnvMapTexture(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) {
        auto* m = rw::MatFX::get(reinterpret_cast<const rw::Material*>(material));
        if (m) return reinterpret_cast<RwTexture*>(m->getEnvTexture());
    }
    return nullptr;
#else
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x8126F0)(material);
#endif
}

RwFrame* RpMatFXMaterialGetEnvMapFrame(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwFrame*(__cdecl *)(const RpMaterial*))0x812740)(material);
#endif
}

RwBool RpMatFXMaterialGetEnvMapFrameBufferAlpha(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return FALSE;
#else
    return ((RwBool(__cdecl *)(const RpMaterial*))0x812790)(material);
#endif
}

RwReal RpMatFXMaterialGetEnvMapCoefficient(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (material) {
        auto* m = rw::MatFX::get(reinterpret_cast<const rw::Material*>(material));
        if (m) return m->getEnvCoefficient();
    }
    return 0.0f;
#else
    return ((RwReal(__cdecl *)(const RpMaterial*))0x8127E0)(material);
#endif
}

RpMaterial* RpMatFXMaterialSetDualTexture(RpMaterial* material, RwTexture* texture) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812830)(material, texture);
#endif
}

RpMaterial* RpMatFXMaterialSetDualBlendModes(RpMaterial* material, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwBlendFunction, RwBlendFunction))0x8128C0)(material, srcBlendMode, dstBlendMode);
#endif
}

RwTexture* RpMatFXMaterialGetDualTexture(const RpMaterial* material) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x812930)(material);
#endif
}

const RpMaterial* RpMatFXMaterialGetDualBlendModes(const RpMaterial* material, RwBlendFunction* srcBlendMode, RwBlendFunction* dstBlendMode) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((const RpMaterial*(__cdecl *)(const RpMaterial*, RwBlendFunction*, RwBlendFunction*))0x812980)(material, srcBlendMode, dstBlendMode);
#endif
}

RpMaterial* RpMatFXMaterialSetUVTransformMatrices(RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwMatrix*, RwMatrix*))0x8129E0)(material, baseTransform, dualTransform);
#endif
}

const RpMaterial* RpMatFXMaterialGetUVTransformMatrices(const RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform) {
#ifdef NOTSA_STANDALONE_NATIVE
    return material;
#else
    return ((const RpMaterial*(__cdecl *)(const RpMaterial*, RwMatrix*, RwMatrix*))0x812A50)(material, baseTransform, dualTransform);
#endif
}

RxPipeline* RpMatFXGetD3D9Pipeline(RpMatFXD3D9Pipeline d3d9Pipeline) {
#ifdef NOTSA_STANDALONE_NATIVE
    static RxPipeline s_MatFXPipeline{};
    return &s_MatFXPipeline;
#else
    return ((RxPipeline*(__cdecl *)(RpMatFXD3D9Pipeline))0x8162F0)(d3d9Pipeline);
#endif
}
