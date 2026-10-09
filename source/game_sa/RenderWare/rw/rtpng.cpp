#include "StdInc.h"

#include "rtpng.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

RwImage* RtPNGImageWrite(RwImage* image, const RwChar* imageName) {
#ifdef NOTSA_STANDALONE_NATIVE
    return image && imageName ? (RwImage*)rw::writePNG((rw::Image*)image, imageName) : nullptr;
#else
    return ((RwImage*(__cdecl *)(RwImage*, const RwChar*))0x7CF600)(image, imageName);
#endif
}

RwImage* RtPNGImageRead(const RwChar* imageName) {
#ifdef NOTSA_STANDALONE_NATIVE
    return imageName ? (RwImage*)rw::readPNG(imageName) : nullptr;
#else
    return ((RwImage*(__cdecl *)(const RwChar*))0x7CF9B0)(imageName);
#endif
}
