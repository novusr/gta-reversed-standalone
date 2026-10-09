#include "StdInc.h"

#include "rpanisot.h"

RwInt8 RpAnisotGetMaxSupportedMaxAnisotropy() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 16;
#else
    return ((RwInt8(__cdecl *)())0x748F20)();
#endif
}

RwTexture* RpAnisotTextureSetMaxAnisotropy(RwTexture* tex, RwInt8 val) {
#ifdef NOTSA_STANDALONE_NATIVE
    return tex;
#else
    return ((RwTexture*(__cdecl *)(RwTexture*, RwInt8))0x748F30)(tex, val);
#endif
}

RwInt8 RpAnisotTextureGetMaxAnisotropy(RwTexture* tex) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 1;
#else
    return ((RwInt8(__cdecl *)(RwTexture*))0x748F50)(tex);
#endif
}

RwBool RpAnisotPluginAttach() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)())0x748F70)();
#endif
}
