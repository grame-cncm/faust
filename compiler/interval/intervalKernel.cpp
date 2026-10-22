/* Copyright 2020-2026 Yann Orlarey, Agathe Herrou, Stéphane Letz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <map>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <vector>

#include "directed_rounding.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {

//------------------------------------------------------------------------------------------
// The kernels Sum, Fir and Iir.
//
// Sum and Fir are bounded as their definitions : the delayed samples of a FIR are distinct
// values of x, so the sum of the products of their intervals is the bound of the program.
//
// Iir is a recursion, y(n) = x(n) + sum_j c[j] y(n-1-j) : its definition read as interval
// arithmetic multiplies the coefficients in absolute value at every step and diverges
// even for a stable filter. A stable filter with constant coefficients is bounded by the
// L1 norm L of its impulse response h : y = h * x. filterGain certifies an upper bound
// of L ; the output is bounded by the signs of the first values of h applied to the bounds
// of x, the rest of h by L, and the rounding errors of the program, amplified by L, are
// added. When no bound can be certified (variable coefficients, an unstable or too slow
// filter), Iir may be anything, NaN included.
//------------------------------------------------------------------------------------------

namespace {

using detail::BinaryOp;
using detail::Direction;
using detail::directedBinary;

double addUp(double a, double b)
{
    return directedBinary(BinaryOp::Add, a, b, Direction::Up);
}

double mulUp(double a, double b)
{
    return directedBinary(BinaryOp::Mul, a, b, Direction::Up);
}

double divUp(double a, double b)
{
    return directedBinary(BinaryOp::Div, a, b, Direction::Up);
}

double subDown(double a, double b)
{
    return directedBinary(BinaryOp::Sub, a, b, Direction::Down);
}

/// gamma_k = k u / (1 - k u), the relative error bound of k rounded operations, rounded up
double gammaBound(int k, double u)
{
    const double ku = mulUp(double(k), u);
    return divUp(ku, subDown(1.0, ku));
}

using Matrix = std::vector<std::vector<double>>;

}  // namespace

// The impulse response h (h(0) = 1, h(n) = sum_j c[j] h(n-1-j)) is computed in double over
// 2m samples, m being a block length after which the companion matrix A of the recursion
// contracts : ||A^m||_inf <= rho <= 1/2, A^m computed by squarings in double, the
// rounding error of every product bounded by gamma_p |M||M|. The residual d(n) of each
// computed value bounds its own rounding ; the computed response then differs from h by at
// most L * sum|d|. With the state s(n) = (h(n), ..., h(n-p+1)), s(n + m) = A^m s(n), so the
// samples beyond m are bounded by the windows of the second block over (1 - rho) :
//   L <= S_head + m L D + (W + m L D) / (1 - rho),
// solved for L. False : no bound (unstable, too slow, or too imprecise).
bool filterGain(const std::vector<double>& c, FilterGain& gain)
{
    const int    p = int(c.size());
    const double u = std::ldexp(1.0, -53);
    if (p == 0) {
        gain = FilterGain{1, 1, 0, 0, 1};
        return true;
    }
    for (double v : c) {
        if (!std::isfinite(v)) return false;
    }
    const double g = gammaBound(p + 1, u);

    // 1. the block length : A^m by squarings, with its rounding error E
    Matrix M(p, std::vector<double>(p, 0.0)), E(p, std::vector<double>(p, 0.0));
    for (int j = 0; j < p; j++) M[0][j] = c[j];
    for (int i = 1; i < p; i++) M[i][i - 1] = 1;
    auto norm = [&]() {
        double n = 0;
        for (int i = 0; i < p; i++) {
            double r = 0;
            for (int j = 0; j < p; j++) r = addUp(r, addUp(std::abs(M[i][j]), E[i][j]));
            n = std::max(n, r);
        }
        return n;
    };
    long   m   = 1;
    double rho = norm();
    for (int k = 0; rho > 0.5 && k < 22; k++) {
        Matrix M2(p, std::vector<double>(p, 0.0)), E2(p, std::vector<double>(p, 0.0));
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < p; j++) {
                double s = 0, mm = 0, me = 0, em = 0, ee = 0;
                for (int l = 0; l < p; l++) {
                    s  = s + M[i][l] * M[l][j];
                    mm = addUp(mm, mulUp(std::abs(M[i][l]), std::abs(M[l][j])));
                    me = addUp(me, mulUp(std::abs(M[i][l]), E[l][j]));
                    em = addUp(em, mulUp(E[i][l], std::abs(M[l][j])));
                    ee = addUp(ee, mulUp(E[i][l], E[l][j]));
                }
                M2[i][j] = s;
                E2[i][j] = addUp(addUp(me, em), addUp(ee, mulUp(g, mm)));
            }
        }
        M   = M2;
        E   = E2;
        m   = 2 * m;
        rho = norm();
    }
    if (!(rho <= 0.5)) return false;

    // 2. the impulse response, a head of H samples (H a multiple of m, doubled until the
    //    rest of h is negligible) and one more block for the windows, with the residuals
    //    of its rounding
    const double        tailFactor = divUp(1.0, subDown(1.0, rho));
    const long          cap        = 1L << 21;
    std::vector<double> h;
    double              D    = 0;
    auto                grow = [&](long n) {
        while (long(h.size()) < n) {
            const long k   = long(h.size());
            double     acc = (k == 0) ? 1.0 : 0.0;
            double     mag = acc;
            for (int j = 0; j < p && k - 1 - j >= 0; j++) {
                acc = acc + c[j] * h[k - 1 - j];
                mag = addUp(mag, mulUp(std::abs(c[j]), std::abs(h[k - 1 - j])));
            }
            if (!std::isfinite(acc)) return false;
            h.push_back(acc);
            D = addUp(D, mulUp(g, mag));
        }
        return true;
    };
    auto window = [&](long H) {  // sum over the block after H of the state norms
        double W = 0;
        for (long r = 0; r < m; r++) {
            double w = 0;
            for (int i = 0; i < p; i++) w = std::max(w, std::abs(h[H + r - i]));
            W = addUp(W, w);
        }
        return W;
    };
    long   H = m;
    double head = 0, pos = 0, neg = 0, W = 0;
    long   counted = 0;
    for (;;) {
        if (!grow(H + m)) return false;
        for (; counted < H; counted++) {
            const double v = h[counted];
            head           = addUp(head, std::abs(v));
            if (v > 0) pos = addUp(pos, v);
            if (v < 0) neg = addUp(neg, -v);
        }
        W = window(H);
        if (mulUp(W, tailFactor) <= head * 1e-12 || 2 * H + m > cap) break;
        H = 2 * H;
    }

    // 3. the bound : L <= head + H L D + (W + m L D) / (1 - rho)
    const double HD    = mulUp(double(H), D);
    const double mD    = mulUp(double(m), D);
    const double lost  = addUp(HD, mulUp(mD, tailFactor));
    const double denom = subDown(1.0, lost);
    if (!(denom >= 0.5)) return false;
    const double L = divUp(addUp(head, mulUp(W, tailFactor)), denom);
    if (!std::isfinite(L)) return false;
    // the head computed within H L D, the rest of h within (W + m L D) / (1 - rho)
    const double spread = addUp(mulUp(HD, L), mulUp(addUp(W, mulUp(mD, L)), tailFactor));
    gain                = FilterGain{L, pos, neg, spread, H};
    return std::isfinite(gain.spread);
}

// Sum : the sum of the terms, from left to right ; it may overflow when one of its
// partial sums may
interval interval_algebra::Sum(const std::vector<interval>& terms) const
{
    if (terms.empty()) return IntNum(0);
    interval acc      = terms[0];
    bool     overflow = false;
    for (size_t k = 1; k < terms.size(); k++) {
        acc      = Add(acc, terms[k]);
        overflow = overflow || acc.mayOverflow();
    }
    return acc.withOverflow(overflow);
}

// Prod : the products from left to right ; it may overflow when one of its partial
// products may
interval interval_algebra::Prod(const std::vector<interval>& factors) const
{
    if (factors.empty()) return IntNum(1);
    interval acc      = factors[0];
    bool     overflow = false;
    for (size_t k = 1; k < factors.size(); k++) {
        acc      = Mul(acc, factors[k]);
        overflow = overflow || acc.mayOverflow();
    }
    return acc.withOverflow(overflow);
}

// Fir : the products of the coefficients by the delayed samples, a null coefficient
// skipped (the definition, as the signal dispatch expanded it) ; it may overflow when one
// of its products or partial sums may
interval interval_algebra::Fir(const interval& x, const std::vector<interval>& coefs) const
{
    bool     first    = true;
    bool     overflow = false;
    interval acc;
    for (size_t k = 0; k < coefs.size(); k++) {
        const interval& ck = coefs[k];
        if (!ck.isEmpty() && ck.lo() == 0 && ck.hi() == 0 && !ck.mayBeInvalid()) continue;
        const interval term = (k == 0) ? Mul(ck, x) : Mul(ck, Delay(x, IntNum(int(k))));
        acc                 = first ? term : Add(acc, term);
        overflow            = overflow || term.mayOverflow() || acc.mayOverflow();
        first               = false;
    }
    return first ? IntNum(0) : acc.withOverflow(overflow);
}

namespace {

// the output of the filter of coefficients c (the program's values) on x : [-lo, hi]
// the gain of a filter depends on its coefficients only : computed once per coefficient
// vector (an analysis evaluates the same filter at every step of its fixpoints)
bool cachedFilterGain(const std::vector<double>& c, FilterGain& fg)
{
    thread_local std::map<std::vector<double>, std::pair<bool, FilterGain>> cache;
    auto it = cache.find(c);
    if (it == cache.end()) {
        FilterGain g;
        const bool ok = filterGain(c, g);
        it            = cache.emplace(c, std::make_pair(ok, g)).first;
    }
    fg = it->second.second;
    return it->second.first;
}

bool filterOutput(const std::vector<double>& c, const interval& fx, double& lo, double& hi)
{
    FilterGain fg;
    if (!cachedFilterGain(c, fg)) return false;
    const double L = fg.L;
    // the exact output : y(n) = sum_k h(k) x(n-k), each term between 0 (not yet started)
    // and h(k) times an end of x ; the head by the signs of its computed values, its error
    // and the rest of h by their absolute bound ; never beyond L max|x|
    const double xl     = fx.lo(), xh = fx.hi();
    const double mx     = std::max(std::abs(xl), std::abs(xh));
    const double spread = mulUp(fg.spread, mx);
    hi = addUp(addUp(mulUp(fg.pos, std::max(xh, 0.0)), mulUp(fg.neg, std::max(-xl, 0.0))), spread);
    lo = addUp(addUp(mulUp(fg.pos, std::max(-xl, 0.0)), mulUp(fg.neg, std::max(xh, 0.0))), spread);
    // the rounding of the program : y = h * (x + e), |e(n)| <= gamma (|x| + sum|c| |y|)
    const double u  = (programPrecision() == 1) ? std::ldexp(1.0, -24) : std::ldexp(1.0, -53);
    const double gp = gammaBound(int(c.size()) + 1, u);
    double       C1 = 0;
    for (double v : c) C1 = addUp(C1, std::abs(v));
    const double LgC = mulUp(mulUp(L, gp), C1);
    if (!(LgC < 0.5)) return false;
    const double Y = divUp(mulUp(mulUp(L, mx), addUp(1.0, gp)), subDown(1.0, LgC));
    const double E = mulUp(mulUp(L, gp), addUp(mx, mulUp(C1, Y)));
    hi             = addUp(std::min(hi, mulUp(L, mx)), E);
    lo             = addUp(std::min(lo, mulUp(L, mx)), E);
    // nonnegative coefficients keep the sign of the input, rounding included (a rounded
    // sum or product of nonnegative values is nonnegative)
    bool positive = true;
    for (double v : c) positive = positive && v >= 0;
    if (positive && xl >= 0) lo = 0;
    if (positive && xh <= 0) hi = 0;
    return std::isfinite(hi) && std::isfinite(lo);
}

}  // namespace

// Bpf : the selection of the regions that x may reach. A threshold is a constant ; a
// threshold that is not a point leaves both of its sides possible.
interval interval_algebra::Bpf(const interval& x, const std::vector<interval>& t,
                               const std::vector<interval>& r) const
{
    // a malformed node (|r| != |t| + 1) bounds nothing
    if (r.size() != t.size() + 1) return interval(-HUGE_VAL, HUGE_VAL, -24, true);
    if (x.isEmpty()) {
        bool alert = x.mayBeInvalid();
        for (const interval& ti : t) alert = alert || ti.mayBeInvalid();
        for (const interval& ri : r) alert = alert || ri.mayBeInvalid();
        return empty().withInvalid(alert);
    }
    interval acc     = empty();
    bool     invalid = false;
    for (size_t i = 0; i < r.size(); i++) {
        // the range [lo, hi[ of region i ; the last one is also reached by a NaN x
        const double lo   = (i == 0) ? -HUGE_VAL : t[i - 1].lo();
        const double hi   = (i == t.size()) ? HUGE_VAL : t[i].hi();
        const bool   last = (i == t.size());
        const bool   meet = (x.hi() >= lo && x.lo() < hi) || (last && x.mayBeInvalid());
        if (!meet) continue;
        if (r[i].isEmpty()) continue;
        acc     = acc.isEmpty() ? r[i] : interval(std::min(acc.lo(), r[i].lo()), std::max(acc.hi(), r[i].hi()),
                                                  std::min(acc.lsb(), r[i].lsb()));
        invalid = invalid || r[i].mayBeInvalid();
    }
    for (const interval& ti : t) invalid = invalid || ti.mayBeInvalid();
    return acc.withInvalid(invalid);
}

// Iir : the certified gain of a stable filter with constant coefficients, the program's
// rounding included ; anything, NaN included, otherwise
interval interval_algebra::Iir(const interval& x, const std::vector<interval>& coefs) const
{
    // A filter whose non null coefficients sit at the multiples of a step d,
    // y(n) = x(n) + c_d y(n-d) + c_2d y(n-2d) + ..., has the impulse response of the filter
    // c_d, c_2d, ... with d - 1 zeros between its samples : the same sum of |h|, the same
    // signed parts, the same terms per step. Its bound is that filter's, of order n/d (a
    // comb x + g y(n-N) is a first-order filter) : the companion matrices stay small.
    {
        auto isNull = [](const interval& c) { return !c.isEmpty() && c.lo() == 0 && c.hi() == 0 && !c.mayBeInvalid(); };
        size_t d = 0;
        for (size_t k = 0; k < coefs.size(); k++) {
            if (!isNull(coefs[k])) d = std::gcd(d, k + 1);
        }
        if (d > 1) {
            std::vector<interval> reduced;
            for (size_t k = d - 1; k < coefs.size(); k += d) reduced.push_back(coefs[k]);
            return Iir(x, reduced);
        }
    }
    if (x.isEmpty() || std::any_of(coefs.begin(), coefs.end(), [](const interval& c) { return c.isEmpty(); })) {
        bool alert = x.mayBeInvalid();
        for (const interval& ci : coefs) alert = alert || ci.mayBeInvalid();
        return empty().withInvalid(alert);
    }
    bool invalid = x.mayBeInvalid();
    int  lsb     = std::min(x.lsb(), -1);
    for (const interval& ci : coefs) {
        invalid = invalid || ci.mayBeInvalid();
        lsb     = std::min(lsb, ci.lsb());
    }
    const interval anything = interval(-HUGE_VAL, HUGE_VAL, lsb, true);

    // an integer recursion wraps modulo 2^32 : whatever its coefficients, its values stay
    // in int32, and it never makes a NaN (a congruential noise generator) ; its operations
    // may wrap
    bool integer = x.lsb() >= 0;
    for (const interval& ci : coefs) integer = integer && ci.lsb() >= 0;
    if (integer) return interval(-2147483648.0, 2147483647.0, 0).withInvalid(invalid).withOverflow();

    // the coefficients of the program : constants at the program's precision, one value,
    // or the two neighbours enclosing a constant the precision cannot represent (the
    // program uses one of them : every combination is bounded, and joined)
    std::vector<std::vector<double>> choices;
    size_t                           combos = 1;
    for (const interval& ci : coefs) {
        const interval fc = detail::floatingOperand(ci);
        if (!std::isfinite(fc.lo()) || !std::isfinite(fc.hi())) return anything;
        std::vector<double> vs;
        if (programPrecision() == 1) {
            const float a = float(fc.lo()), b = float(fc.hi());
            if (double(a) != fc.lo() && double(a) > fc.lo()) return anything;
            vs.push_back(double(a));
            if (b != a) {
                if (std::nextafter(a, HUGE_VALF) != b) return anything;
                vs.push_back(double(b));
            }
        } else {
            if (fc.lo() != fc.hi()) return anything;
            vs.push_back(fc.lo());
        }
        combos *= vs.size();
        if (combos > 256) return anything;
        choices.push_back(vs);
    }
    const interval fx = detail::floatingOperand(x);
    if (!fx.isBounded()) return anything;

    double lo = 0, hi = 0;  // the result is [-lo, hi]
    bool   firstCombo = true;
    for (size_t combo = 0; combo < combos; combo++) {
        std::vector<double> c;
        size_t              rest = combo;
        for (const auto& vs : choices) {
            c.push_back(vs[rest % vs.size()]);
            rest /= vs.size();
        }
        double clo, chi;
        if (!filterOutput(c, fx, clo, chi)) return anything;
        lo         = firstCombo ? clo : std::max(lo, clo);
        hi         = firstCombo ? chi : std::max(hi, chi);
        firstCombo = false;
    }
    return interval(-lo, hi, lsb).withInvalid(invalid);
}

}  // namespace itv
