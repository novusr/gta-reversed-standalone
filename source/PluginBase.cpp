/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "PluginBase.h"

#if !defined(NOTSA_STANDALONE_NATIVE)
#include "StdInc.h"
#include <Windows.h>
#endif

int _NOINLINE_ plugin::GetBaseAddress() {
#if defined(NOTSA_STANDALONE_NATIVE)
    return 0;
#else
    static int addr = reinterpret_cast<int>(GetModuleHandleA(NULL));
    return addr;
#endif
}

int _NOINLINE_ plugin::GetGlobalAddress(int address) {
#if defined(NOTSA_STANDALONE_NATIVE)
    return address;
#else
    return GetBaseAddress() - 0x400000 + address;
#endif
}
