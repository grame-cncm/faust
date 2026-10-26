// Gate 5, the C signal API : every function libfaust-signal-c.h declares must be exported by the
// shared libfaust (a declaration without a definition fails the link).
#include "faust/dsp/libfaust-signal-c.h"
#include <cstddef>
#include <iostream>

#include "signal-c-api-references.inc"

int main()
{
    const std::size_t linked = checkApiLinks();
    std::cout << "C signal API: " << linked << " function signatures linked" << std::endl;
    return linked == 0 ? 1 : 0;
}
