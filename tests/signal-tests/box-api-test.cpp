#include "faust/dsp/libfaust-box.h"
#include <iostream>
#include <cstddef>

#include "box-api-references.inc"

int main()
{
    const std::size_t linked = checkApiLinks();
    if (linked == 0) return 1;
    createLibContext();
    Box integer = boxInt(7);
    Box wire = boxWire();
    Box pair = boxPar(wire, integer);
    int value = -1;
    int inputs = -1;
    int outputs = -1;
    Box left = nullptr;
    Box right = nullptr;
    bool ok = isBoxInt(integer) && isBoxInt(integer, &value) && value == 7
           && isBoxWire(wire) && isBoxPar(pair, left, right)
           && left == wire && right == integer
           && getBoxType(pair, &inputs, &outputs) && inputs == 1 && outputs == 2;
    destroyLibContext();
    if (!ok) {
        std::cerr << "C++ box API checks failed\n";
        return 1;
    }
    std::cout << "C++ box API: " << linked << " function signatures linked; "
              << "constructors, predicates and arity passed\n";
    return 0;
}
