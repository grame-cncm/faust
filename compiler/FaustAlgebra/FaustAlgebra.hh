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

#ifndef FAUSTALGEBRA_HH
#define FAUSTALGEBRA_HH

#include <vector>

#include "FaustCoreAlgebra.hh"

//=====================================================================================================================
// A Faust Algebra is a class grouping the set of primitive operations available
// on Faust signals in the normal form. Derived algebras specify the carrier type T and
// implement each primitive operation for that type. Examples include interval, type
// inference, expression tree and compiler algebras.
//=====================================================================================================================

template <typename T>
class FaustAlgebra : public FaustCoreAlgebra<T>
{
   public:
    //--------------------------------------------------------------------------------
    // The operations of the normal form beyond the common base (FaustCoreAlgebra.hh) :
    // the arithmetic, generic in nature, and the operations whose code the certification
    // decides, here without their decision. The computation form (ComputeAlgebra.hh)
    // has its own.
    //--------------------------------------------------------------------------------

    // Numerical Operations
    virtual T Abs(const T& x) const = 0;
    virtual T Add(const T& x, const T& y) const = 0;
    virtual T Sub(const T& x, const T& y) const = 0;
    virtual T Mul(const T& x, const T& y) const = 0;
    virtual T Div(const T& x, const T& y) const = 0;
    virtual T Inv(const T& x) const = 0;
    virtual T Neg(const T& x) const = 0;
    virtual T Mod(const T& x, const T& y) const = 0;
    virtual T Ceil(const T& x) const = 0;
    virtual T Floor(const T& x) const = 0;
    virtual T Lsh(const T& x, const T& y) const = 0;
    // Signed and logical right shifts have different semantics for negative
    // operands and therefore cannot share one algebra operation.
    virtual T ARsh(const T& x, const T& y) const = 0;
    virtual T LRsh(const T& x, const T& y) const = 0;

    // Compound operations (see FaustCoreAlgebra.hh)
    virtual T Frac(const T& x) const                        = 0;  // x - floor(x)
    virtual T Mix(const T& c, const T& a, const T& b) const = 0;  // (1 - c) * a + c * b
    virtual T Phase(const T& x, const T& p) const           = 0;  // (x % p) / p

    // The kernels of the signal language : an n-ary sum and product, a finite impulse
    // response filter, the infinite recursive mix (Iir and Bpf are in the common base).
    // A sum and a product associate from left to right : the order of their operands is
    // their association, for an analysis as for the code. No default, as above.
    //   Sum(t)    = ((t[0] + t[1]) + ...) + t[n]
    //   Prod(f)   = ((f[0] * f[1]) * ...) * f[n]
    //   Fir(x, c) = sum_k c[k] * x(n - k)
    //   Irm(x, c) = y, where y(n) = mix(c(n), x(n), y(n - 1)) and y(n < 0) = 0, the
    //               infinite recursive mix : a smoother of x whose pole is c
    virtual T Sum(const std::vector<T>& terms) const             = 0;
    virtual T Prod(const std::vector<T>& factors) const          = 0;
    virtual T Fir(const T& x, const std::vector<T>& coefs) const = 0;
    virtual T Irm(const T& x, const T& c) const                  = 0;

    // Delays
    virtual T Mem(const T& x) const               = 0;
    virtual T Delay(const T& x, const T& y) const = 0;

   protected:
    //--------------------------------------------------------------------------------
    // Copy and move operations are protected: derived algebras keep theirs, but
    // copying through a FaustAlgebra& (which would slice) is not allowed.
    //--------------------------------------------------------------------------------
    FaustAlgebra()                                   = default;
    FaustAlgebra(const FaustAlgebra&)                = default;
    FaustAlgebra& operator=(const FaustAlgebra&)     = default;
    FaustAlgebra(FaustAlgebra&&) noexcept            = default;
    FaustAlgebra& operator=(FaustAlgebra&&) noexcept = default;
};

#endif