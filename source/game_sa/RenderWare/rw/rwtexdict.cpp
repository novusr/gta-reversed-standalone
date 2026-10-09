#include "StdInc.h"

#include "rwtexdict.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

RwTexture* GetFirstTextureCallback(RwTexture* texture, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    *reinterpret_cast<RwTexture**>(data) = texture;
    return nullptr;
#else
    return plugin::CallAndReturn<RwTexture*, 0x734930, RwTexture*, void*>(texture, data);
#endif
}

RwTexture* GetFirstTexture(RwTexDictionary* txd) {
#ifdef NOTSA_STANDALONE_NATIVE
    RwTexture* tex = nullptr;
    RwTexDictionaryForAllTextures(txd, GetFirstTextureCallback, &tex);
    return tex;
#else
    return plugin::CallAndReturn<RwTexture*, 0x734940, RwTexDictionary*>(txd);
#endif
}

RwTexture* RwTextureGtaStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwTexture*)rw::Texture::streamRead((rw::Stream*)stream);
#else
    return plugin::CallAndReturn<RwTexture*, 0x730E60, RwStream*>(stream);
#endif
}

RwTexDictionary* RwTexDictionaryGtaStreamRead(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwTexDictionary*)rw::TexDictionary::streamRead((rw::Stream*)stream);
#else
    return plugin::CallAndReturn<RwTexDictionary*, 0x730FC0, RwStream*>(stream);
#endif
}

RwTexDictionary* RwTexDictionaryGtaStreamRead1(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwTexDictionary*)rw::TexDictionary::streamRead((rw::Stream*)stream);
#else
    return plugin::CallAndReturn<RwTexDictionary*, 0x731070, RwStream*>(stream);
#endif
}

RwTexDictionary* RwTexDictionaryGtaStreamRead2(RwStream* stream, RwTexDictionary* txd) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwTexDictionary*)rw::TexDictionary::streamRead((rw::Stream*)stream);
#else
    return plugin::CallAndReturn<RwTexDictionary*, 0x731150, RwStream*, RwTexDictionary*>(stream, txd);
#endif
}

bool RpClumpGtaStreamRead1(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Clump::streamRead((rw::Stream*)stream) != nullptr;
#else
    return plugin::CallAndReturn<bool, 0x72E570, RwStream*>(stream);
#endif
}

RpClump* RpClumpGtaStreamRead2(RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RpClump*)rw::Clump::streamRead((rw::Stream*)stream);
#else
    return plugin::CallAndReturn<RpClump*, 0x72E620, RwStream*>(stream);
#endif
}
