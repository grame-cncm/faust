/* Copyright 2023-2026 Yann Orlarey
 * SPDX-License-Identifier: Apache-2.0
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

#ifndef COMPUTEALGEBRA_HH
#define COMPUTEALGEBRA_HH

#include <vector>

#include "FaustCoreAlgebra.hh"

//=====================================================================================================================
// The signature of the computation form : the program as the code computes it, derived
// from the certified normal form. Beyond the common base (FaustCoreAlgebra.hh), its
// operations carry the decisions the certification took on the normal form, as DATA (an
// int, a bool, an enumeration), never as a carrier value : the size of a delay line, the
// certified bounds of a delay amount, the form of a mix, of a smoother or of a phase, the
// certificate of an integer operation. A rewrite that rebuilds a node rebuilds its data ;
// the code generation reads them, never an interval.
//
// The integer arithmetic is apart from the real one, and binary : a sum or a product of
// integers is a chain in the order of the code, each step with its certificate. The
// rewrites of the computation form recognize the real arithmetic only, so that a
// certificate taken on the normal form stays true in the emitted code.
//=====================================================================================================================

/// The form of mix(c, a, b) = (1 - c) * a + c * b in the code
enum class MixForm {
    kFromA,      ///< a + c * (b - a)
    kFromB,      ///< b + (1 - c) * (a - b), 1 - c exact : c may be near 1
    kFromWeight  ///< b + t * (a - b), c written 1 - t and t read as it is
};

/// The form of the smoother y = mix(c, x, y') in the code, y' its previous value
enum class IrmForm {
    kWeighted,   ///< (1 - c) * x + c * y', 1 - c and (1 - c) * x at their rates
    kFromX,      ///< x + c * (y' - x)
    kFromState   ///< y' + w * (x - y'), w the weight 1 - c (read as it is when c is 1 - w)
};

template <typename T>
class ComputeAlgebra : public FaustCoreAlgebra<T>
{
   public:
    // The real arithmetic : no data ; the only operations the rewrites of the
    // computation form touch. Faust's division is always real.
    virtual T Add(const T& x, const T& y) const = 0;
    virtual T Sub(const T& x, const T& y) const = 0;
    virtual T Mul(const T& x, const T& y) const = 0;
    virtual T Div(const T& x, const T& y) const = 0;
    virtual T Inv(const T& x) const = 0;
    virtual T Neg(const T& x) const = 0;
    virtual T Abs(const T& x) const = 0;
    virtual T Mod(const T& x, const T& y) const = 0;
    //   Sum(t)       = ((t[0] + t[1]) + ...) + t[n]
    //   Prod(f)      = ((f[0] * f[1]) * ...) * f[n]
    //   Fir(line, c) = sum_k c[k] * x(n - k), the taps read in the line of x
    virtual T Sum(const std::vector<T>& terms) const                = 0;
    virtual T Prod(const std::vector<T>& factors) const             = 0;
    virtual T Fir(const T& line, const std::vector<T>& coefs) const = 0;

    // The integer arithmetic : binary, in the order of the code, each operation with its
    // certificate. fits : the exact result stays in Int32, the plain C operation is then
    // the same value ; defined : the shift count is in [0, 31] and a left shift does not
    // overflow. A false certificate (the default, and the only one under -nocert) emits
    // the defined form (faust_wrap_*). The remainder has no data : its defined form is a
    // signal of the normal form already.
    virtual T IntAdd(const T& x, const T& y, bool fits) const     = 0;
    virtual T IntSub(const T& x, const T& y, bool fits) const     = 0;
    virtual T IntMul(const T& x, const T& y, bool fits) const     = 0;
    virtual T IntNeg(const T& x, bool fits) const                 = 0;
    virtual T IntAbs(const T& x, bool fits) const                 = 0;
    virtual T IntLsh(const T& x, const T& k, bool defined) const  = 0;
    virtual T IntARsh(const T& x, const T& k, bool defined) const = 0;
    virtual T IntLRsh(const T& x, const T& k, bool defined) const = 0;
    virtual T IntMod(const T& x, const T& y) const                = 0;

    // The delays : the line of a signal, shared by its reads, and its reads. n is the
    // largest delay the line serves (its representation holds n + 1 values at least) ; a
    // read of amount d carries the certified bounds dmin <= d <= dmax, and is in its line
    // when dmax <= n.
    virtual T DelayLine(const T& x, int n) const                          = 0;
    virtual T Delay(const T& line, const T& d, int dmin, int dmax) const = 0;

    // The operations whose code the certification decides
    virtual T Mix(const T& c, const T& a, const T& b, MixForm form) const = 0;
    //   Irm(x, c, form) = y, where y(n) = mix(c(n), x(n), y(n - 1)) and y(n < 0) = 0
    virtual T Irm(const T& x, const T& c, IrmForm form) const = 0;
    //   (x % p) / p, the division a product by 1 / p computed at the rate of p when
    //   byInverse
    virtual T Phase(const T& x, const T& p, bool byInverse) const = 0;
    //   floor and ceil, computed from the integer conversion when approx (-mapp, |x| < 2^31) ;
    //   x - floor(x), its floor alike
    virtual T Floor(const T& x, bool approx) const = 0;
    virtual T Ceil(const T& x, bool approx) const  = 0;
    virtual T Frac(const T& x, bool approx) const  = 0;

   protected:
    //--------------------------------------------------------------------------------
    // Copy and move operations are protected: derived algebras keep theirs, but
    // copying through a ComputeAlgebra& (which would slice) is not allowed.
    //--------------------------------------------------------------------------------
    ComputeAlgebra()                                     = default;
    ComputeAlgebra(const ComputeAlgebra&)                = default;
    ComputeAlgebra& operator=(const ComputeAlgebra&)     = default;
    ComputeAlgebra(ComputeAlgebra&&) noexcept            = default;
    ComputeAlgebra& operator=(ComputeAlgebra&&) noexcept = default;
};

#endif
