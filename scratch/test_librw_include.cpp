#include <iostream>
#define NOTSA_STANDALONE_NATIVE 1
#include "Base.h"
#include "RenderWare/RenderWare.h"

#pragma push_macro("RWALIGN")
#undef RWALIGN
#include "rw.h"
#pragma pop_macro("RWALIGN")

int main() {
    bool ok = rw::Engine::init();
    std::cout << "librw Engine::init returned: " << ok << "\n";
    rw::Engine::term();
    std::cout << "librw Engine::term done!\n";
    return 0;
}
