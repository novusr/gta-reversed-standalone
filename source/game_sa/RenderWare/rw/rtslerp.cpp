#include "StdInc.h"

#include "rtslerp.h"

void RtQuatSetupSlerpCache(RtQuat* qpFrom, RtQuat* qpTo, RtQuatSlerpCache* sCache) {
#ifdef NOTSA_STANDALONE_NATIVE
    // Standalone native: no-op stub cache
#else
    ((void(__cdecl*)(RtQuat*, RtQuat*, RtQuatSlerpCache*))0x7EC220)(qpFrom, qpTo, sCache);
#endif
}
