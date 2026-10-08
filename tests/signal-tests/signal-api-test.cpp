#include "faust/dsp/libfaust-signal.h"
#include <iostream>
#include <cstddef>

#include "signal-api-references.inc"

int main()
{
    const std::size_t linked = checkApiLinks();
    if (linked == 0) return 1;
    createLibContext();
    Signal input = sigInput(0);
    Signal integer = sigInt(7);
    Signal sum = sigAdd(input, integer);
    int index = -1;
    int value = -1;
    int operation = -1;
    Signal left = nullptr;
    Signal right = nullptr;
    bool ok = isSigInput(input, &index) && index == 0
           && isSigInt(integer, &value) && value == 7
           && isSigBinOp(sum, &operation, left, right)
           && operation == kAdd && left == input && right == integer;
    destroyLibContext();
    if (!ok) {
        std::cerr << "C++ signal API checks failed\n";
        return 1;
    }
    std::cout << "C++ signal API: " << linked << " function signatures linked; "
              << "constructors and predicates passed\n";
    return 0;
}
