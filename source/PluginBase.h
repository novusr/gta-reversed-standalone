/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <cstddef>
#include <cstdint>

#include "Base.h"

namespace plugin {
int GetBaseAddress();

int GetGlobalAddress(int address);

// meta template for functions
#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__))
template <auto Func> struct meta;
#elif (defined(_MSC_VER))
template <typename FuncType, FuncType Func> struct meta;
#else

#endif

// Gets the virtual method table from the object @self
inline void** GetVMT(const void* self) {
    return *(void***)(self);
}

#ifdef NOTSA_STANDALONE_NATIVE

namespace detail {
template <typename Ret>
Ret SafeDefault() {
    if constexpr (std::is_reference_v<Ret>) {
        using ValType = std::remove_reference_t<Ret>;
        alignas(ValType) static char dummyBytes[sizeof(ValType)]{};
        return reinterpret_cast<ValType&>(dummyBytes);
    } else if constexpr (std::is_default_constructible_v<Ret>) {
        return Ret{};
    } else {
        alignas(Ret) static char dummyBytes[sizeof(Ret)]{};
        return reinterpret_cast<Ret&>(dummyBytes);
    }
}
} // namespace detail

template <unsigned int address, typename... Args> void Call(Args... args) {
    static bool loggedOnce = false;
    if (!loggedOnce) {
        NOTSA_LOG_WARN("Unreversed plugin::Call invoked at address 0x{:08X}", address);
        loggedOnce = true;
    }
}

template <typename Ret, unsigned int address, typename... Args>  Ret CallAndReturn(Args... args) {
    static bool loggedOnce = false;
    if (!loggedOnce) {
        NOTSA_LOG_WARN("Unreversed plugin::CallAndReturn invoked at address 0x{:08X}", address);
        loggedOnce = true;
    }
    if constexpr (std::is_void_v<Ret>) {
        return;
    } else {
        return detail::SafeDefault<Ret>();
    }
}

template <typename Ret, unsigned int address, typename C, typename... Args>
Ret CallMethodAndReturn(C _this, Args... args) requires std::is_class_v<std::remove_pointer_t<C>> {
    static bool loggedOnce = false;
    if (!loggedOnce) {
        NOTSA_LOG_WARN("Unreversed plugin::CallMethodAndReturn invoked at address 0x{:08X}", address);
        loggedOnce = true;
    }
    if constexpr (std::is_void_v<Ret>) {
        return;
    } else {
        return detail::SafeDefault<Ret>();
    }
}

template <unsigned int address, typename C, typename... Args>
void CallMethod(C _this, Args... args) requires std::is_class_v<std::remove_pointer_t<C>> {
    static bool loggedOnce = false;
    if (!loggedOnce) {
        NOTSA_LOG_WARN("Unreversed plugin::CallMethod invoked at address 0x{:08X}", address);
        loggedOnce = true;
    }
}

template <unsigned int tableIndex, typename C, typename... Args>
void CallVirtualMethod(C _this, Args... args) requires std::is_class_v<std::remove_pointer_t<C>> {
    static bool loggedOnce = false;
    if (!loggedOnce) {
        NOTSA_LOG_WARN("Unreversed plugin::CallVirtualMethod invoked at table index {}", tableIndex);
        loggedOnce = true;
    }
}

template <typename Ret, unsigned int tableIndex, typename C, typename... Args>
Ret CallVirtualMethodAndReturn(C _this, Args... args) requires std::is_class_v<std::remove_pointer_t<C>> {
    static bool loggedOnce = false;
    if (!loggedOnce) {
        NOTSA_LOG_WARN("Unreversed plugin::CallVirtualMethodAndReturn invoked at table index {}", tableIndex);
        loggedOnce = true;
    }
    if constexpr (std::is_void_v<Ret>) {
        return;
    } else {
        return detail::SafeDefault<Ret>();
    }
}

#else

template <unsigned int address, typename... Args> void Call(Args... args) {
    reinterpret_cast<void(__cdecl*)(Args...)>(address)(args...);
}

template <typename Ret, unsigned int address, typename... Args>  Ret CallAndReturn(Args... args) {
    return reinterpret_cast<Ret(__cdecl*)(Args...)>(address)(args...);
}

template <typename Ret, unsigned int address, typename C, typename... Args>
Ret CallMethodAndReturn(C _this, Args... args) requires std::is_class_v<std::remove_pointer_t<C>> {
    return reinterpret_cast<Ret(__thiscall*)(C, Args...)>(address)(_this, args...);
}

template <unsigned int address, typename C, typename... Args>
void CallMethod(C _this, Args... args) requires std::is_class_v<std::remove_pointer_t<C>> {
    return reinterpret_cast<void(__thiscall*)(C, Args...)>(address)(_this, args...);
}

template <unsigned int tableIndex, typename C, typename... Args>
void CallVirtualMethod(C _this, Args... args) requires std::is_class_v<std::remove_pointer_t<C>> {
    reinterpret_cast<void(__thiscall*)(C, Args...)>((*reinterpret_cast<void***>(_this))[tableIndex])(_this, args...);
}

template <typename Ret, unsigned int tableIndex, typename C, typename... Args>
Ret CallVirtualMethodAndReturn(C _this, Args... args) requires std::is_class_v<std::remove_pointer_t<C>> {
    return reinterpret_cast<Ret(__thiscall*)(C, Args...)>((*reinterpret_cast<void***>(_this))[tableIndex])(_this, args...);
}

#endif

} // namespace plugin
