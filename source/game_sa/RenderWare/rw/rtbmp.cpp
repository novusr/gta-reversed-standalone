#include "StdInc.h"

#include "rtbmp.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

RwImage* RtBMPImageWrite(RwImage* image, const RwChar* imageName) {
#ifdef NOTSA_STANDALONE_NATIVE
    return image && imageName ? (RwImage*)rw::writeBMP((rw::Image*)image, imageName) : nullptr;
#else
    return ((RwImage*(__cdecl *)(RwImage*, const RwChar*))0x7CE990)(image, imageName);
#endif
}

RwImage* RtBMPImageRead(const RwChar* imageName) {
#ifdef NOTSA_STANDALONE_NATIVE
    return imageName ? (RwImage*)rw::readBMP(imageName) : nullptr;
#else
    return ((RwImage*(__cdecl *)(const RwChar*))0x7CDF60)(imageName);
#endif
}
