/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#ifndef _IRM_ERROR_FORM_
#define _IRM_ERROR_FORM_

#include <algorithm>
#include <cmath>

#include "global.hh"
#include "interval_def.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

/**
 * The smoother y = mix(p, x, y') of a slow x written by its error e = y - x (IrmForm::kError),
 * in single precision : once per block, where x is constant, the jump of x is added to the
 * error, e' = fl(e' + fl(x' - x)), and x' = x ; per sample, e = fl(p e') and y = fl(x + e).
 * The error decays to 0 : the output reaches x, where the weighted sum stops up to
 * ulp(x) / (2 (1 - p)) short of it. Within a block x' - x is 0 and e' + 0 is e' : the values
 * are those of the definition computed at every sample, e = fl(p fl(e' + fl(x' - x))).
 *
 * Once per block as well, an error that x + e' no longer moves is 0 : |e| only decreases,
 * x + e stays between x and x + e', rounded to x, and no output changes. So is an error below
 * the smallest normal float, which only x = 0 (or a subnormal x) still reads : the output
 * moves by less than it. Without them the error stays on a subnormal value, fl(p e) = e, and
 * every product of the loop is subnormal (several times slower on x86 without flush-to-zero).
 *
 * The bound. With g = x + e the output before its rounding, and e' = g' - x' exactly,
 * g = (1 - p) x + p g' - p a D - p k (x - g' + a D), D = x - x', |a| <= u, |k| <= 2u + u^2 :
 * |g - mix(p, x, g')| <= p W (3u + 3u^2 + u^3), W the width of the hull of x, 0 and the
 * values of g (x(-1) = 0, g(-1) = 0). An interval G = [h_lo - m, h_hi + m] around the hull
 * [h_lo, h_hi] of x and 0 is then an invariant when (1 - p) m >= p k3 (W_h + 2m) for every p,
 * k3 = 3u + 3u^2 + u^3 : m = c k3 W_h / (1 - c - 2 c k3), c the largest pole. The block
 * operations keep g in G : a flush makes g = x. The outputs are fl(g), between the floats
 * around G.
 *
 * The certified interval of the node may be narrower on a side : the envelopes of the
 * interval rule (a smoother of a nonnegative x is nonnegative, Irm) hold for the
 * interpolations and the weighted sum, not for this form, which may cross 0 by a rounding
 * when x jumps close to it. The output is then bounded on that side by the certified bound,
 * rounded inwards to a float : the values the certificate states are the values computed.
 */
struct IrmErrorBounds {
    bool   clampLo = false;  ///< the output bounded from below, by lo
    bool   clampHi = false;  ///< the output bounded from above, by hi
    double lo      = 0;      ///< a float, within the certified interval
    double hi      = 0;
};

namespace irmerror {

inline float floatDown(double v)
{
    float f = float(v);
    return (double(f) > v) ? std::nextafter(f, -HUGE_VALF) : f;
}

inline float floatUp(double v)
{
    float f = float(v);
    return (double(f) < v) ? std::nextafter(f, HUGE_VALF) : f;
}

}  // namespace irmerror

/**
 * The bounds of the error form of IRM(x; p), node sig, against its certified interval :
 * false when the form does not apply (an unbounded x, a pole beyond [0, 1[)
 */
inline bool irmErrorBounds(Tree sig, Tree x, Tree p, IrmErrorBounds& b)
{
    const itv::interval X = getCertifiedSigType(x)->getInterval();
    const itv::interval C = getCertifiedSigType(p)->getInterval();
    const itv::interval Y = getCertifiedSigType(sig)->getInterval();
    if (X.isEmpty() || C.isEmpty() || Y.isEmpty() || !X.isBounded() || !Y.isBounded() || X.mayBeInvalid() ||
        C.mayBeInvalid() || C.lo() < 0 || !(C.hi() < 1)) {
        return false;
    }
    const double u   = std::ldexp(1.0, -24);
    const double k3  = 3 * u + 3 * u * u + u * u * u;
    const double c   = C.hi();
    const double den = 1 - c - 2 * c * k3;
    if (!(den > 0)) return false;
    const double hlo = std::min(X.lo(), 0.0), hhi = std::max(X.hi(), 0.0);
    const double mag = std::max(std::abs(hlo), std::abs(hhi));
    const double m   = (c * k3 * (hhi - hlo) / den) * (1 + std::ldexp(1.0, -20)) + std::ldexp(1.0, -50) * mag +
                     std::ldexp(1.0, -122);
    if (!std::isfinite(m)) return false;
    const double glo = irmerror::floatDown(hlo - m), ghi = irmerror::floatUp(hhi + m);
    b         = IrmErrorBounds();
    b.clampLo = glo < Y.lo();
    b.clampHi = ghi > Y.hi();
    b.lo      = irmerror::floatUp(Y.lo());
    b.hi      = irmerror::floatDown(Y.hi());
    return !(b.clampLo && b.clampHi && b.lo > b.hi);
}

/**
 * The error form applies : a real slow smoother in single precision, in the C and C++
 * generators, whose compute function runs the block code before its samples (not under -ec
 * or -os) ; not under -ls, whose emission reads the smoother's own past
 */
inline bool irmErrorFormApplies(Tree sig, Tree x, Tree p)
{
    const int vr = std::max(getCertifiedSigType(x)->variability(), getCertifiedSigType(p)->variability());
    if (gGlobal->gFloatSize != 1 || gGlobal->gExtControl || gGlobal->gOneSample || gGlobal->gLoopSplit || vr == kSamp ||
        getCertifiedSigType(sig)->nature() != kReal || getCertifiedSigType(x)->nature() != kReal) {
        return false;
    }
    if (gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "c" && gGlobal->gOutputLang != "ocpp") {
        return false;
    }
    IrmErrorBounds b;
    return irmErrorBounds(sig, x, p, b);
}

#endif
