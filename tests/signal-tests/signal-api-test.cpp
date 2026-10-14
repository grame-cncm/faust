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

    // the nodes of the normal form : built and read back, and a sum written by the
    // normal form as a Sum node
    Signal operand = nullptr;
    Signal c = nullptr, a = nullptr, b = nullptr;
    tvec   terms;
    Signal neg = sigNeg(input);
    Signal nsum = sigSum({input, integer});
    Signal mix = sigMix(sigReal(0.5), input, integer);
    ok = ok && isSigNeg(neg, operand) && operand == input
            && isSigSum(nsum, terms) && terms.size() == 2 && terms[0] == input
            && isSigMix(mix, c, a, b) && a == input && b == integer;
    // the infinite recursive mix IRM(x; p) : its input and its pole
    Signal irm = sigIRM(input, sigReal(0.9));
    Signal ix = nullptr, ip = nullptr;
    ok = ok && isSigIRM(irm, ix, ip) && ix == input && !isSigIRM(mix, ix, ip);
    // the break-point function Bpf(x; t; r) : x, its thresholds, its regions
    Signal bpf = sigBpf(input, {sigReal(0.0), sigReal(1.0)}, {sigReal(0.0), input, sigReal(1.0)});
    Signal bx  = nullptr;
    tvec   bt, br;
    ok = ok && isSigBpf(bpf, bx, bt, br) && bx == input && bt.size() == 2 && br.size() == 3 && br[1] == input;
    // simplifyToNormalForm of one signal returns the list of that signal : its first
    // branch is the signal in normal form
    Signal sum2 = sigAdd(sum, sigInput(1));
    tvec   list = sigBranches(simplifyToNormalForm(sum2));
    tvec   normal;
    ok = ok && list.size() == 2 && isSigSum(list[0], normal) && normal.size() == 3;
    destroyLibContext();
    if (!ok) {
        std::cerr << "C++ signal API checks failed\n";
        return 1;
    }
    std::cout << "C++ signal API: " << linked << " function signatures linked; "
              << "constructors and predicates passed, nodes of the normal form included\n";
    return 0;
}
