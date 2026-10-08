#include <iostream>
#include <cassert>
#include <type_traits>

#define NOTSA_STANDALONE_NATIVE 1
#include "PluginBase.h"

struct DummyStruct {
    int x = 42;
};

class DummyClass {
public:
    int val = 99;
};

struct NonDefaultConstructible {
    int v;
    NonDefaultConstructible(int x) : v(x) {}
};

int main() {
    std::cout << "Testing plugin::Call stub...\n";
    plugin::Call<0x123456>(1, 2, 3);
    plugin::Call<0x123456>(4, 5, 6); // Should log only once

    std::cout << "Testing plugin::CallAndReturn<int>...\n";
    int i = plugin::CallAndReturn<int, 0x234567>(10);
    assert(i == 0);

    std::cout << "Testing plugin::CallAndReturn<bool>...\n";
    bool b = plugin::CallAndReturn<bool, 0x345678>();
    assert(!b);

    std::cout << "Testing plugin::CallAndReturn<void*>...\n";
    void* ptr = plugin::CallAndReturn<void*, 0x456789>();
    assert(ptr == nullptr);

    std::cout << "Testing plugin::CallMethod...\n";
    DummyClass dummyObj;
    plugin::CallMethod<0x56789A>(&dummyObj, 123);

    std::cout << "Testing plugin::CallMethodAndReturn<DummyStruct>...\n";
    DummyStruct ds = plugin::CallMethodAndReturn<DummyStruct, 0x6789AB>(&dummyObj);
    assert(ds.x == 42); // default constructed

    std::cout << "Testing plugin::CallMethodAndReturn<DummyClass&> (Reference return type)...\n";
    DummyClass& dcRef = plugin::CallMethodAndReturn<DummyClass&, 0x789ABC>(&dummyObj);
    std::cout << "dcRef.val: " << dcRef.val << "\n";

    std::cout << "Testing plugin::CallAndReturn<NonDefaultConstructible>...\n";
    NonDefaultConstructible ndc = plugin::CallAndReturn<NonDefaultConstructible, 0x89ABCD>();
    (void)ndc;

    std::cout << "Testing GetGlobalAddress...\n";
    assert(plugin::GetGlobalAddress(0x1234) == 0x1234);
    assert(plugin::GetBaseAddress() == 0);

    std::cout << "ALL PLUGIN STUB TESTS PASSED SUCCESSFULLY!\n";
    return 0;
}
