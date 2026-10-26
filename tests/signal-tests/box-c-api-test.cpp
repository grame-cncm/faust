// Gate 5, the C box API : every function libfaust-box-c.h declares must be exported by the
// shared libfaust (a declaration without a definition fails the link).
#include "faust/dsp/libfaust-box-c.h"
#include <cstddef>
#include <iostream>

#include "box-c-api-references.inc"

int main()
{
    const std::size_t linked = checkApiLinks();
    std::cout << "C box API: " << linked << " function signatures linked" << std::endl;
    return linked == 0 ? 1 : 0;
}
