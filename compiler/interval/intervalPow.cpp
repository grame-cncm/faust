#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Pow
// interval Pow(const interval& x, const interval& y) const;
// void testPow() const;

interval interval_algebra::Pow(const interval& x, const interval& y) const
{
    if (x.lo() > 0) {
        // x all positive
        return Exp(Mul(y, Log(x)));

    } else {
#if 0
        int n;
        if (isInt(y, n)) {
            if (n >= 0) {
                if (x.hi() < 0) {
                    // x all negative
                    if (n % 2 == 0) {
                        // n is even
                        return interval(pow(x.hi(), n), pow(x.lo(), n));
                    } else {
                        // n is odd
                    return interval(pow(x.lo(), n), pow(x.hi()), n))
                    }
                } else {
                    // x is on both sides of 0
                    if (n % 2 == 0) {
                        // n is even
                        return interval(1, std::max(pow(x.lo(), n), pow(x.hi(), n)));
                    } else {
                        // n is odd
                        return interval(1, -1);
                    }
                }
            }
            if (n % 2 == 0) {
                return Pow(x, n);
            } else {
                return Pow(x, n - 1);
            }
        } else {
            return Exp(Mul(y, Log(x)));
        }
#endif
        return {};
    }
}

static double myPow(double x, double y)
{
    return pow(x, y);
}

void interval_algebra::testPow() const
{
    analyzeBinaryMethod(10, 2000, "Pow", interval(1, 1000), interval(-10, 10), myPow, &interval_algebra::Pow);
    analyzeBinaryMethod(10, 2000, "Pow", interval(0.001, 1), interval(-10, 10), myPow, &interval_algebra::Pow);
    analyzeBinaryMethod(10, 2000, "Pow", interval(0.001, 10), interval(-20, 20), myPow, &interval_algebra::Pow);
}
}  // namespace itv
