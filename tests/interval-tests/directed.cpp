/*
 The directed rounding of the interval library (interval_def.hh : addDown, mulUp...)
 against the rounding modes of the machine, on random operands and edge cases.
*/

#include <cfenv>
#include <cstdio>
#include <random>

#include "interval_def.hh"

#pragma STDC FENV_ACCESS ON

using namespace itv;

// the reference : the operation computed by the machine in the rounding mode
static double machine(int op, double a, double b, int mode)
{
    volatile double x = a, y = b, r;
    std::fesetround(mode);
    switch (op) {
        case 0:
            r = x + y;
            break;
        case 1:
            r = x * y;
            break;
        case 2:
            r = x / y;
            break;
        default:
            r = std::sqrt(x);
            break;
    }
    std::fesetround(FE_TONEAREST);
    return r;
}

static float machineFloat(double a, int mode)
{
    volatile double x = a;
    volatile float  r;
    std::fesetround(mode);
    r = float(x);
    std::fesetround(FE_TONEAREST);
    return r;
}

int main()
{
    std::mt19937_64                        g(42);
    std::uniform_real_distribution<double> mantissa(1.0, 2.0);
    std::uniform_int_distribution<int>     exponent(-60, 60), sign(0, 1);
    auto                                   operand = [&]() {
        double v = std::ldexp(mantissa(g), exponent(g));
        return sign(g) ? -v : v;
    };
    long bad = 0, checks = 0;
    for (int i = 0; i < 1000000; i++) {
        double a = operand(), b = operand();
        if (i % 3 == 0) {  // float operands : exact products
            a = double(float(a));
            b = double(float(b));
        }
        double got[8] = {addDown(a, b), addUp(a, b),  mulDown(a, b),          mulUp(a, b),
                         divDown(a, b), divUp(a, b),  sqrtDown(std::fabs(a)), sqrtUp(std::fabs(a))};
        double ref[8] = {machine(0, a, b, FE_DOWNWARD),
                         machine(0, a, b, FE_UPWARD),
                         machine(1, a, b, FE_DOWNWARD),
                         machine(1, a, b, FE_UPWARD),
                         machine(2, a, b, FE_DOWNWARD),
                         machine(2, a, b, FE_UPWARD),
                         machine(3, std::fabs(a), 0, FE_DOWNWARD),
                         machine(3, std::fabs(a), 0, FE_UPWARD)};
        for (int k = 0; k < 8; k++, checks++) {
            if (got[k] != ref[k] && bad++ < 5) {
                printf("operation %d, a = %a, b = %a : %a instead of %a\n", k, a, b, got[k], ref[k]);
            }
        }
        checks += 3;
        if (floatBound(a, -1) != machineFloat(a, FE_DOWNWARD) ||
            floatBound(a, 1) != machineFloat(a, FE_UPWARD) || floatBound(a, 0) != double(float(a))) {
            if (bad++ < 5) printf("floatBound, a = %a\n", a);
        }
    }
    const double dmax = std::numeric_limits<double>::max();
    const double fmax = std::numeric_limits<float>::max();
    struct {
        double      got, ref;
        const char* what;
    } edges[] = {
        {addDown(1, 2), 3, "exact sum"},
        {mulUp(3, 0.5), 1.5, "exact product"},
        {divDown(1, 4), 0.25, "exact quotient"},
        {sqrtUp(9), 3, "exact square root"},
        {mulDown(0, HUGE_VAL), 0, "0 times inf"},
        {addUp(HUGE_VAL, 1), HUGE_VAL, "inf + 1"},
        {addDown(1e308, 1e308), dmax, "overflow, rounded down"},
        {addUp(1e308, 1e308), HUGE_VAL, "overflow, rounded up"},
        {divUp(1, 0), HUGE_VAL, "1 / 0"},
        {floatBound(1e300, -1), fmax, "beyond the floats, rounded down"},
        {floatBound(1e300, 1), HUGE_VAL, "beyond the floats, rounded up"},
    };
    for (auto& e : edges) {
        checks++;
        if (e.got != e.ref) {
            bad++;
            printf("%s : %a instead of %a\n", e.what, e.got, e.ref);
        }
    }
    printf("directed rounding : %ld checks, %ld errors\n", checks, bad);
    return bad != 0;
}
