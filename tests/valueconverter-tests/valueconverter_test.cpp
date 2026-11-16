/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

// Checks the LogValueConverter and ExpValueConverter of ValueConverter.h:
// - a log scale over positive values follows exp(log(min) + t*(log(max)-log(min))),
// - a log scale with a bound 0 and the other one positive follows
//   exp(log(min+f) + t*(log(max+f)-log(min+f))) - f, with a floor f 60 dB under the
//   other bound, reaches both bounds and goes back to the same ui value,
// - a log scale with a bound < 0, or both bounds 0, is the linear conversion,
// - an exp scale stays finite, monotonic and within [min, max], reaches both bounds
//   and goes back to the same ui value, including ranges where exp(min) or exp(max)
//   overflow or underflow, and follows log((1-t)*exp(min) + t*exp(max)) where these
//   exponentials can be computed.

#include <cmath>
#include <cstdio>

#include "faust/gui/ValueConverter.h"

static int gErrors = 0;
static int gChecks = 0;

static void check(bool cond, const char* scale, double fmin, double fmax, const char* what, double u, double got, double expected)
{
    gChecks++;
    if (!cond) {
        if (gErrors < 40) {
            printf("FAIL %s %g..%g: %s at ui %.17g: got %.17g, expected %.17g\n", scale, fmin, fmax, what, u, got, expected);
        }
        gErrors++;
    }
}

static double ulps(double x, int n) { return n * (std::nextafter(std::fabs(x), INFINITY) - std::fabs(x)); }

static const int N = 10000;

static void checkLog(double fmin, double fmax)
{
    LogValueConverter c(0., 1., fmin, fmax);
    bool floor = (fmin == 0 && fmax > 0) || (fmin > 0 && fmax == 0);
    if (floor) {
        double f = 1e-3 * std::max(fmin, fmax), hi = std::max(fmin, fmax);
        double lmin = std::log(fmin + f), lmax = std::log(fmax + f);
        check(c.ui2faust(0.) == fmin, "log", fmin, fmax, "floor, bottom", 0., c.ui2faust(0.), fmin);
        check(c.ui2faust(1.) == fmax, "log", fmin, fmax, "floor, top", 1., c.ui2faust(1.), fmax);
        check(c.faust2ui(fmin) == 0., "log", fmin, fmax, "floor, faust2ui(min)", fmin, c.faust2ui(fmin), 0.);
        check(std::fabs(c.faust2ui(fmax) - 1.) <= 1e-15, "log", fmin, fmax, "floor, faust2ui(max)", fmax, c.faust2ui(fmax), 1.);
        double prev = fmin;
        for (int i = 0; i <= N; i++) {
            double u = double(i) / N;
            double y = c.ui2faust(u);
            double expected = (i == 0) ? fmin : (i == N) ? fmax : std::max(0., std::exp(lmin + u * (lmax - lmin)) - f);
            check(std::fabs(y - expected) <= ulps(hi, 8), "log", fmin, fmax, "floor, value", u, y, expected);
            check(y >= 0. && y <= hi, "log", fmin, fmax, "floor, within the range", u, y, y);
            check((fmax >= fmin) ? (y >= prev) : (y <= prev), "log", fmin, fmax, "floor, monotonic", u, y, prev);
            prev = y;
            double back = c.faust2ui(y);
            check(std::fabs(back - u) <= 1e-9, "log", fmin, fmax, "floor, round trip", u, back, u);
        }
    } else if (fmin > 0 && fmax > 0) {
        double lmin = std::log(fmin), lmax = std::log(fmax);
        for (int i = 0; i <= N; i++) {
            double u = double(i) / N;
            double expected = std::exp(lmin + u * (lmax - lmin));
            double y = c.ui2faust(u);
            check(std::fabs(y - expected) <= ulps(expected, 8), "log", fmin, fmax, "geometric value", u, y, expected);
            if (fmin != fmax) {
                double back = c.faust2ui(y);
                check(std::fabs(back - u) <= 1e-12, "log", fmin, fmax, "round trip", u, back, u);
            }
        }
    } else {
        LinearValueConverter lin(0., 1., fmin, fmax);
        for (int i = 0; i <= N; i++) {
            double u = double(i) / N;
            check(c.ui2faust(u) == lin.ui2faust(u), "log", fmin, fmax, "linear fallback, ui2faust", u, c.ui2faust(u), lin.ui2faust(u));
            double y = fmin + u * (fmax - fmin);
            check(c.faust2ui(y) == lin.faust2ui(y), "log", fmin, fmax, "linear fallback, faust2ui", y, c.faust2ui(y), lin.faust2ui(y));
        }
    }
}

static void checkExp(double fmin, double fmax)
{
    ExpValueConverter c(0., 1., fmin, fmax);
    double lo = std::min(fmin, fmax), hi = std::max(fmin, fmax);
    check(c.ui2faust(0.) == fmin, "exp", fmin, fmax, "bottom", 0., c.ui2faust(0.), fmin);
    check(c.ui2faust(1.) == fmax, "exp", fmin, fmax, "top", 1., c.ui2faust(1.), fmax);
    check(c.ui2faust(-1.) == fmin, "exp", fmin, fmax, "below the ui range", -1., c.ui2faust(-1.), fmin);
    check(c.ui2faust(2.) == fmax, "exp", fmin, fmax, "above the ui range", 2., c.ui2faust(2.), fmax);
    bool exact = std::fabs(fmin) < 700 && std::fabs(fmax) < 700;
    double prev = fmin;
    for (int i = 0; i <= N; i++) {
        double u = double(i) / N;
        double y = c.ui2faust(u);
        check(std::isfinite(y) && y >= lo && y <= hi, "exp", fmin, fmax, "finite and within the range", u, y, y);
        check((fmax >= fmin) ? (y >= prev) : (y <= prev), "exp", fmin, fmax, "monotonic", u, y, prev);
        prev = y;
        if (exact) {
            double expected = std::log((1. - u) * std::exp(fmin) + u * std::exp(fmax));
            double tol = 1e-12 * (hi - lo) + ulps(std::max(std::fabs(fmin), std::fabs(fmax)), 4);
            check(std::fabs(y - expected) <= tol, "exp", fmin, fmax, "value", u, y, expected);
        }
        if (fmin != fmax) {
            double back = c.faust2ui(y);
            check(std::isfinite(back) && std::fabs(back - u) <= 1e-9, "exp", fmin, fmax, "round trip", u, back, u);
        }
    }
    check(c.faust2ui(fmin) == 0., "exp", fmin, fmax, "faust2ui(min)", fmin, c.faust2ui(fmin), 0.);
    check(c.faust2ui(fmax) == 1., "exp", fmin, fmax, "faust2ui(max)", fmax, c.faust2ui(fmax), 1.);
    check(c.faust2ui(lo - 1.) == ((fmax >= fmin) ? 0. : 1.), "exp", fmin, fmax, "faust2ui below the range", lo - 1., c.faust2ui(lo - 1.), 0.);
    check(c.faust2ui(hi + 1.) == ((fmax >= fmin) ? 1. : 0.), "exp", fmin, fmax, "faust2ui above the range", hi + 1., c.faust2ui(hi + 1.), 1.);
}

int main()
{
    const double logRanges[][2] = {
        {20, 20000}, {20000, 20}, {0.001, 1}, {1, 1000}, {5, 5},
        {0, 1}, {0, 20000}, {1, 0}, {0, 1e-6}, {0, 1e300},
        {-1, 1}, {-60, 0}, {-60, -1}, {0, 0}, {0, -1}
    };
    for (const auto& r : logRanges) checkLog(r[0], r[1]);

    // A 60 dB floor: the middle of a gain from 0 to 1 is about -30 dB, the middle of a
    // frequency from 0 to 20000 is close to the one of a log scale from 20 to 20000 (632)
    LogValueConverter gain(0., 1., 0., 1.), freq(0., 1., 0., 20000.);
    double g = gain.ui2faust(0.5), f = freq.ui2faust(0.5);
    double ge = std::sqrt(1e-3 * 1.001) - 1e-3, fe = std::sqrt(20. * 20020.) - 20.;
    check(std::fabs(g - ge) <= 1e-12, "log", 0., 1., "floor, middle of a gain", 0.5, g, ge);
    check(std::fabs(f - fe) <= 1e-9, "log", 0., 20000., "floor, middle of a frequency", 0.5, f, fe);
    printf("log 0..1: middle %.6g (%.2f dB), log 0..20000: middle %.6g\n", g, 20 * std::log10(g), f);

    const double expRanges[][2] = {
        {1, 10}, {0, 1}, {-1, 1}, {10, 1}, {0, 100}, {1, 1.000001}, {0, 700},
        {0, 1000}, {-1000, 0}, {20, 20000}, {-800, -790}, {1000, 1010}, {1000, 0}
    };
    for (const auto& r : expRanges) checkExp(r[0], r[1]);

    // Degenerate exp range: the bound, and the middle of the ui range
    ExpValueConverter flat(0., 1., 5., 5.);
    for (int i = 0; i <= N; i++) {
        double u = double(i) / N;
        check(flat.ui2faust(u) == 5., "exp", 5., 5., "degenerate range", u, flat.ui2faust(u), 5.);
    }
    check(flat.faust2ui(5.) == 0.5, "exp", 5., 5., "degenerate range, faust2ui", 5., flat.faust2ui(5.), 0.5);

    printf("%d checks, %d failures\n", gChecks, gErrors);
    return (gErrors == 0) ? 0 : 1;
}
