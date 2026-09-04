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

#include <cstdint>
#include <string>
#include <vector>

//=====================================================================================================================
// A Faust Algebra is a class grouping the set of primitive operations available
// on Faust signals. Derived algebras specify the carrier type T and implement
// each primitive operation for that type. Examples include interval, type
// inference, expression tree and compiler algebras.
//=====================================================================================================================

template <typename T>
class FaustAlgebra
{
   public:
    //--------------------------------------------------------------------------------
    // List of all the primitive operations
    //--------------------------------------------------------------------------------

    // Injections of external values (numbers and strings)
    // NB : lists (cons/nil) are STRUCTURE, not signals -- they never cross the
    // algebra boundary, so there is no Nil operation. An adapter that must produce a
    // value for structural syntax uses its domain's inert default.
    virtual T IntNum(int x) const = 0;
    virtual T Int64Num(int64_t x) const = 0;
    virtual T FloatNum(double x) const = 0;
    virtual T Label(const std::string& s) const = 0;

    // Used when searching for fixpoint
    virtual T FixPointUpdate(const T& x, const T& y) const = 0;

    // Input Output Operations
    virtual T Input(const T& chan) const = 0;
    virtual T Output(const T& chan, const T& x) const = 0;

    // User Interface Elements
    virtual T Button(const T& name) const = 0;
    virtual T Checkbox(const T& name) const = 0;
    virtual T VSlider(const T& name, const T& init, const T& lo, const T& hi, const T& step) const = 0;
    virtual T HSlider(const T& name, const T& init, const T& lo, const T& hi, const T& step) const = 0;
    // Bargraphs are signal nodes, so the displayed signal must participate in
    // every interpretation rather than being supplied by an implicit caller.
    virtual T HBargraph(const T& name, const T& lo, const T& hi, const T& signal) const = 0;
    virtual T VBargraph(const T& name, const T& lo, const T& hi, const T& signal) const = 0;
    virtual T NumEntry(const T& name, const T& init, const T& lo, const T& hi, const T& step) const = 0;
    // Effect and control wrappers expose both dependencies even when an
    // interpretation ultimately preserves the value carried by x.
    virtual T Attach(const T& x, const T& y) const = 0;
    virtual T Enable(const T& x, const T& control) const = 0;
    virtual T Control(const T& x, const T& control) const = 0;

    // Numerical Operations
    virtual T Abs(const T& x) const = 0;
    virtual T Highest(const T& x) const = 0;
    virtual T Lowest(const T& x) const = 0;
    virtual T Add(const T& x, const T& y) const = 0;
    virtual T Sub(const T& x, const T& y) const = 0;
    virtual T Mul(const T& x, const T& y) const = 0;
    virtual T Div(const T& x, const T& y) const = 0;
    virtual T Inv(const T& x) const = 0;
    virtual T Neg(const T& x) const = 0;
    virtual T Mod(const T& x, const T& y) const = 0;
    // The `%` binop and the `fmod` primitive share the modulo semantics but not
    // the nature : `%` on two integers is an integer, `fmod` is the C function and
    // is real whatever its operands. One operation cannot answer both, so fmod
    // gets its own : every domain but the nature answers it with Mod.
    virtual T Fmod(const T& x, const T& y) const = 0;
    virtual T Acos(const T& x) const = 0;
    virtual T Acosh(const T& x) const = 0;
    virtual T And(const T& x, const T& y) const = 0;
    virtual T Asin(const T& x) const = 0;
    virtual T Asinh(const T& x) const = 0;
    virtual T Atan(const T& x) const = 0;
    virtual T Atan2(const T& x, const T& y) const = 0;
    virtual T Atanh(const T& x) const = 0;
    virtual T Ceil(const T& x) const = 0;
    virtual T Cos(const T& x) const = 0;
    virtual T Cosh(const T& x) const = 0;
    virtual T Eq(const T& x, const T& y) const = 0;
    virtual T Exp(const T& x) const = 0;
    virtual T Exp10(const T& x) const = 0;
    virtual T FloatCast(const T& x) const = 0;
    virtual T BitCast(const T& x) const = 0;
    virtual T Floor(const T& x) const = 0;
    virtual T Ge(const T& x, const T& y) const = 0;
    virtual T Gt(const T& x, const T& y) const = 0;
    virtual T IntCast(const T& x) const = 0;
    virtual T Le(const T& x, const T& y) const = 0;
    virtual T Log(const T& x) const = 0;
    virtual T Log10(const T& x) const = 0;
    virtual T Lsh(const T& x, const T& y) const = 0;
    virtual T Lt(const T& x, const T& y) const = 0;
    virtual T Max(const T& x, const T& y) const = 0;
    virtual T Min(const T& x, const T& y) const = 0;
    virtual T Ne(const T& x, const T& y) const = 0;
    virtual T Not(const T& x) const = 0;
    virtual T Or(const T& x, const T& y) const = 0;
    virtual T Pow(const T& x, const T& y) const = 0;
    // IEEE remainder is binary; the previous unary signature lost its divisor.
    virtual T Remainder(const T& x, const T& y) const = 0;
    virtual T Rint(const T& x) const = 0;
    virtual T Round(const T& x) const = 0;
    // Signed and logical right shifts have different semantics for negative
    // operands and therefore cannot share one algebra operation.
    virtual T ARsh(const T& x, const T& y) const = 0;
    virtual T LRsh(const T& x, const T& y) const = 0;
    virtual T Select2(const T& x, const T& y, const T& z) const = 0;
    virtual T Sin(const T& x) const = 0;
    virtual T Sinh(const T& x) const = 0;
    virtual T Sqrt(const T& x) const = 0;
    virtual T Tan(const T& x) const = 0;
    virtual T Tanh(const T& x) const = 0;
    virtual T Xor(const T& x, const T& y) const = 0;

    // Delays, Tables and SoundFiles
    virtual T Mem(const T& x) const = 0;
    virtual T Delay(const T& x, const T& y) const = 0;
    virtual T Prefix(const T& x, const T& y) const = 0;
    // Bounds refine numeric values but must still be visible to analyses that
    // validate their constancy and ordering.
    virtual T AssertBounds(const T& lo, const T& hi, const T& x) const = 0;
    virtual T RDTbl(const T& wtbl, const T& ri) const = 0;
    virtual T WRTbl(const T& n, const T& g, const T& wi, const T& ws) const = 0;
    virtual T Gen(const T& x) const = 0;
    virtual T SoundFile(const T& label) const = 0;
    virtual T SoundFileRate(const T& sf, const T& x) const = 0;
    virtual T SoundFileLength(const T& sf, const T& x) const = 0;
    virtual T SoundFileBuffer(const T& sf, const T& x, const T& y, const T& z) const = 0;
    virtual T Waveform(const std::vector<T>& w) const = 0;

    // Foreign functions.
    //
    // The declared type is passed as DATA rather than as a carrier value. Stating it as
    // a T assumes the carrier retains enough of a number to recover the declaration:
    // true of the interval ([0,0] vs [1,1]), false of a coarser abstraction, which maps
    // both to its integer element and loses it. `declaredNature` and `resultNature`
    // follow Faust's own encoding, 0 for integer and 1 for real.
    virtual T ForeignFunction(int resultNature, const std::vector<T>& args) const = 0;
    virtual T ForeignVar(int declaredNature, const T& name, const T& file) const = 0;
    virtual T ForeignConst(int declaredNature, const T& name, const T& file) const = 0;

    virtual ~FaustAlgebra() = default;

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