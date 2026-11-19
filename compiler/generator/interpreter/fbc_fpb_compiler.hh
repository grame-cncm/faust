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
    ---------------------------------------------------------------------
    Portions of this file are adapted from FPB (float patch bytecode), part
    of Audio System Design Tool++ (https://github.com/manicken/manicken.github.io),
    under the following license:

    MIT License

    Copyright (c) 2026 Jannik Svensson (manicken)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 ************************************************************************
 ************************************************************************/

#ifndef _FBC_FPB_COMPILER_H
#define _FBC_FPB_COMPILER_H

/*
 FBC -> FPB compiler: the 'compute' DSP block of a factory, compiled to FPB-style steps.

 FPB (float patch bytecode) is a register bytecode for targets that cannot compile code: each operation is a
 small function, and a compiled block is an array of steps { fn, operand pointers } that run with no decoding.
 Like the LLVM and MIR FBC compilers, this one replaces the interpreter for the DSP block only; the other blocks
 (static init, constants, reset UI, clear, control) stay interpreted.

 Origin
 ------
 FPB is developed by Jannik Svensson (manicken) in Audio System Design Tool++ (ASDT++), a graphical editor for
 the Teensy Audio Library: https://github.com/manicken/manicken.github.io. There, Faust code is compiled to FBC
 (faust -lang interp), then to an FPB patch that a Teensy loads and runs with no compiler on board (specs:
 specs/fpb-bytecode.md). This file brings that design into the interpreter, for a host where the FBC compiler
 cannot generate machine code:
  - the compilation method comes from ASDT++'s FBC -> FPB compiler (red/fpb/fpb-compile-fbc.js): the sample loop
    run symbolically into expression trees, 3-address instructions that write straight into their destination,
    multiply-adds (madd / msub);
  - the steps { fn, operand pointers }, the OPFN / NEXT operations and the operation set with its signatures
    ("f=ff"...), including mov2, the delay line operations (dlyrd, rdfm, wrfm), rem and the 12 fused pairs, come
    from the FPB library for the Teensy (fpb/teensy/FPB/src/FPB_oplist.h, FPB_ops.cpp).
 It differs from FPB where the interpreter needs it: no binary patch format and no op numbers (the steps are
 built in memory, with absolute pointers into the interpreter's heaps), REAL may be double, and the heap is shared
 with the interpreted blocks instead of being folded into constants at one sample rate. It also goes from one
 operation to the next with a guaranteed tail call where the C++ compiler has one (see Dispatch below).

 Where it sits
 -------------
 With INTERP_FPB_BUILD defined (fbc_interpreter.hh, or on the command line) and the INTERP_COMP backend,
 FBCCompiler (fbc_compiler.hh) creates an FBCFPBCompiler the first time it meets the DSP block, keeps it if
 isCompiled() and then calls its execute() instead of interpreting the block; otherwise it deletes it and the
 interpreter keeps running the block. The compiled block is shared by all the instances of the factory. The
 factory's compile options show "-lang interp-fpb".
 tests/interp-tests/interp-fpb has a bench and the instructions to build and test it.

 The input: the DSP block of a scalar-mode factory
 -------------------------------------------------
 In scalar mode the DSP block is exactly one sample loop, which this compiler expects:

     kLoop                          init block:  kInt32Value 0, kStoreInt i0 [, kReturn]
                                    body block:  ... one sample ..., i0 = i0 + 1, kLT(i0, count), kCondBranch
     kReturn

 FBC is a stack machine. For a binary instruction the value pushed LAST is the LEFT operand. Inputs and outputs
 are read and written as inputs[ch][i0] and outputs[ch][i0]. The state (recursions, delay lines, sliders...)
 lives in two heaps, one of REAL and one of int, shared by every block of the instance.

 How the FBC becomes steps (compile())
 -------------------------------------
  1. Symbolic execution (exec()). The body is run on a stack of expression trees (Node) instead of values.
     Every write to memory becomes a statement (Stmt) holding the tree of the stored value: heap stores, indexed
     stores, outputs, and the loop condition. FBC's move instructions (kMove, kPairMove, kBlockPairMove,
     kBlockShift, used for short delay lines) become one store per moved element. An indexed access with a
     constant index becomes a plain heap access. If a store would change a location that a value still on the
     stack reads, that value is first saved in a "saved value" slot (hazard()): the tree must keep reading the
     value from before the store.
  2. Code generation (statement(), gen()). Each statement becomes 3-address instructions (Instr), and the last
     one writes straight into the statement's destination, with no final move. Temporaries only live within
     one statement. Operands are symbolic locations (Loc) at this stage.
  3. Peephole optimisations:
     - in gen(): a*b + c and c - a*b become MADD / MSUB; delay line accesses arr[(a - b) & mask] and
       arr[x & mask] on a power-of-two region become DLYRD, RDFM and WRFM (one operation instead of three);
     - pairMoves(): two consecutive real moves become one MOV2;
     - fuse(): two consecutive operations where the first one writes a temporary that only the second one
       reads become one fused operation (12 of them, the most frequent pairs in compiled Faust code).
  4. Binding (bind()). The steps hold absolute pointers, so they are built per pair of heaps (that is, per
     instance) the first time execute() runs with it, and kept: each Loc becomes the address of its heap
     cell, temporary, constant, frame sample or array descriptor.

 Operand locations (Loc::k) and where they point once bound:

     R  real heap cell (offset)        I  int heap cell (offset)
     t  real temporary                 u  int temporary              (Bound::fRealTemps / fIntTemps)
     s  real saved value               v  int saved value            (after the temporaries, same vectors)
     K  real constant                  J  int constant               (fRealConsts / fIntConsts, shared)
     n  input sample of the frame      o  output sample of the frame (Bound::fIO: inputs, then outputs)
     A  array descriptor (ArrayRef)    c  loop condition             (Bound::fArrays / fCond)

 Execution (execute())
 ---------------------
 For each frame: copy the input samples into fIO, run the steps from the first one to END, copy fIO's
 output part to the output buffers, and go on while the loop condition is true. The steps themselves
 increment the loop variable (it is an ordinary int heap store), as in the FBC code.

 Semantics
 ---------
 Every operation computes exactly what the FBC interpreter computes: the same C++ expressions, a result rounded
 to REAL after each operation, no contraction into FMA (FBC_FPB_NOCONTRACT / FBC_FPB_FNATTR), and integer
 wrap-around on +, - and *. So the outputs are the same as the interpreter's, bit for bit. Fusion keeps the
 order of operations and the intermediate roundings, so it does not change the results either.

 Selects
 -------
 FBC's kSelectReal / kSelectInt (Faust's select2) pop a condition and have two sub-blocks, one per branch, that
 each push one value. The interpreter runs only the branch the condition chooses. The steps have no jumps, so
 here both branches are computed, each into its own location, and a SELECT / ISELECT step keeps one of the two
 values (d = c ? x : y). This is the same result only when computing the other branch has no visible effect:
  - A store in a branch would happen even when its branch is not chosen, so it is refused (exec() with
    inSelect). Faust never generates one: the branches come from FIR value expressions (Select2Inst::fThen and
    fElse), and stores only come from FIR statements; an 'if' with stores is a kIf, which is refused too.
  - A branch must not fault when its operands are what the other case makes them. Floating point is harmless
    (an inf or a NaN is computed, then dropped). Known limit: integer division and remainder are not. With
       n = int(_ * 10); process = select2(n == 0, 100 % n, 0);
    the remainder is in a branch, and the interpreter (and Faust's C++, "(n == 0) ? 0 : 100 % n") only computes
    it when n != 0, while these steps compute 100 % 0 as well: undefined behaviour in C++, a SIGFPE on x86 (arm64
    returns 0 and nothing shows). The same goes for INT_MIN / -1, and for an array read in a branch with an
    index out of the region.
 Both branches are also always computed, so a select costs both of them.

 What is not compiled
 --------------------
 Anything this compiler does not handle throws Unsupported while compiling. The block is then left to the
 interpreter, and isCompiled() / why() tell why. This covers vector mode and any block that is not one plain
 sample loop, soundfiles and other instructions without a case in exec(), a select branch with a store,
 inputs or outputs indexed by something other than the loop variable (or accessed after its increment), and
 block shifts of more than 256 elements.

 Dispatch
 --------
 With clang >= 13 or GCC >= 15 each operation jumps to the next one with a guaranteed tail call (musttail), so
 one call from execute() runs every step of a frame. Elsewhere each operation returns the next step to the loop
 in execute(). Define FBC_FPB_NO_TAILCALL to force the loop. Set FAUST_INTERP_FPB_TRACE in the environment to
 print what was compiled (step count, fused pairs, temporaries) or why not.

 Why steps are faster than the interpreter
 -----------------------------------------
 Both execute an instruction list, but the register form executes far fewer instructions for the same work, and
 in an interpreter going from one instruction to the next costs as much as, or more than, an add or a multiply.
 For y = a*b + c:

     FBC (stack):      kLoadReal c, kLoadReal b, kLoadReal a, kMultReal, kAddReal, kStoreReal y   6 instructions
     FPB (registers):  MADD y, a, b, c                                                            1 step

  1. Fewer dispatches. About half of the instructions of a stack machine only move values (loads, stores,
     constants); a register instruction names its operands and its destination, so those moves disappear.
     fi.resonlp goes from 47 FBC instructions per sample to 11 steps, virtual_analog_oscillator from 3390 to 910.
  2. Less memory traffic. On a stack every intermediate value is written by a push and read back by a pop, with
     the stack pointer updated each time (5 writes and 5 reads above). A step reads its operands where they live
     and writes its result straight into its destination. FPB's "registers" are memory too (heap cells,
     temporaries), but nothing is copied in between.
  3. Operands resolved in advance. The interpreter reads each instruction's offsets and computes heap + offset
     every time; a step holds absolute pointers, computed once by bind().
  4. Work done once at compile time, and the optimisations it allows. The symbolic execution does once what the
     stack redoes at every sample: find which instruction consumes which value. With the data flow explicit
     (named operands instead of implicit stack positions), patterns that are scattered in stack code are easy to
     match: MADD / MSUB, delay line accesses (three operations to one), MOV2, and the fused pairs (about a quarter
     fewer steps).

 The dispatch technique is not the difference: the interpreter already uses threaded code (computed goto in
 fbc_interpreter.hh), and musttail is the same thing with functions. The gain comes from executing fewer
 instructions and copying fewer values.

 What it costs: a step is larger (one pointer per operand, instead of one offset), so each one does a bit more
 work. When the time goes into the operations themselves (sin, exp, pow, divisions), cutting the dispatch matters
 less, and a select pays for both of its branches where the interpreter computes one. This is the likely reason
 (not profiled) why the bench in tests/interp-tests/interp-fpb gives x1.55 on virtual_analog_oscillator and
 x5.36 on vocoder, a long chain of multiply-adds; x2.45 on geometric mean over 12 DSPs. For the register form
 alone, see Shi, Gregg, Beatty and Ertl, "Virtual Machine Showdown: Stack versus Registers" (2005), on Java
 bytecode: far fewer instructions executed, for somewhat larger code. The fusion, the resolved operands and the
 delay line operations add to that here.

 Extending it
 ------------
 - A new operation: a line in FBC_FPB_OPLIST (name and signature) and an OPFN in Ops (its arity in OPFN is the
   signature's operand count). Then make gen() or fuse() emit it.
 - A new fused pair: the operation as above, plus a FuseRule in fuse(). The fused expression must round like
   the pair it replaces.
 - A new FBC instruction: a case in exec() that builds the tree, or throws Unsupported.
*/

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "fbc_executor.hh"
#include "interpreter_bytecode.hh"

#if !defined(FBC_FPB_NO_TAILCALL) && defined(__has_attribute)
#if __has_attribute(musttail)
#define FBC_FPB_TAIL 1
#endif
#endif
#ifndef FBC_FPB_TAIL
#define FBC_FPB_TAIL 0
#endif

// No contraction of a*b + c into one FMA: the interpreter rounds the product and the sum separately.
#if defined(__clang__)
#define FBC_FPB_NOCONTRACT _Pragma("clang fp contract(off)")
#define FBC_FPB_FNATTR
#elif defined(__GNUC__)
#define FBC_FPB_NOCONTRACT
#define FBC_FPB_FNATTR __attribute__((optimize("fp-contract=off")))
#else
#define FBC_FPB_NOCONTRACT
#define FBC_FPB_FNATTR
#endif

namespace fbcfpb {

struct Step;

// An operation: runs the step it is given, then returns the next step (call dispatch) or tail-calls it and
// returns what END returns, nullptr (tail dispatch).
typedef const Step* (*StepFn)(const Step*);

// One step: the operation, then one pointer per operand, in the order of its signature (written operands
// first). The steps of a block are packed one after the other in a vector of words (Bound::fWords), so a step
// takes 1 + arity words and the next step starts at &p[arity]. The block ends with an END step.
struct Step {
    StepFn fn;
    void*  p[1];  // really p[arity]
};

// An array operand: a heap region accessed with a computed index (the 'A' operands). Not bounds-checked, as in
// the interpreter.
struct ArrayRef {
    void*    base;
    uint32_t len;
    uint32_t mask;  // len - 1 when len is a power of two, else 0
};

// The operations: name and signature "<written operands>=<read operands>", one letter per operand: f (REAL),
// i (int), a (array). "f=ff" writes one REAL and reads two; "=aif" (a store into an array) writes no operand.
// The order of the list is free (nothing is stored, the steps hold function pointers), only the signatures
// matter: they give the arity of each step and which operands are written (used by fuse()).
//   - MOV..TANH, ITOF..IBITS: one FBC instruction each (kAddReal -> ADD, kCastInt -> FTOI...);
//   - LT..NE, ISNAN, ISINF: comparisons and tests on REAL, with an int result;
//   - MOV2: two moves, MADD / MSUB: a*b + c and c - a*b;
//   - RDF..WRI: indexed reads and writes; DLYRD, RDFM, WRFM: the same with the index masked (delay lines);
//   - MULSUB..WRFMADD: fused pairs (see Ops and fuse()).
#define FBC_FPB_OPLIST(X)                                                                        \
    X(END, "")                                                                                   \
    X(MOV, "f=f") X(MOV2, "ff=ff") X(ADD, "f=ff") X(SUB, "f=ff") X(MUL, "f=ff") X(DIV, "f=ff")   \
    X(REM, "f=ff") X(FMOD, "f=ff") X(POW, "f=ff") X(ATAN2, "f=ff") X(MIN, "f=ff")                \
    X(MAX, "f=ff") X(COPYSIGN, "f=ff") X(MADD, "f=fff") X(MSUB, "f=fff")                         \
    X(ABS, "f=f") X(ACOS, "f=f") X(ACOSH, "f=f") X(ASIN, "f=f") X(ASINH, "f=f") X(ATAN, "f=f")   \
    X(ATANH, "f=f") X(CEIL, "f=f") X(COS, "f=f") X(COSH, "f=f") X(EXP, "f=f") X(FLOOR, "f=f")    \
    X(LOG, "f=f") X(LOG10, "f=f") X(RINT, "f=f") X(ROUND, "f=f") X(SIN, "f=f") X(SINH, "f=f")    \
    X(SQRT, "f=f") X(TAN, "f=f") X(TANH, "f=f")                                                  \
    X(LT, "i=ff") X(LE, "i=ff") X(GT, "i=ff") X(GE, "i=ff") X(EQ, "i=ff") X(NE, "i=ff")          \
    X(ISNAN, "i=f") X(ISINF, "i=f") X(SELECT, "f=iff")                                           \
    X(IMOV, "i=i") X(IADD, "i=ii") X(ISUB, "i=ii") X(IMUL, "i=ii") X(IDIV, "i=ii")               \
    X(IREM, "i=ii") X(ISHL, "i=ii") X(ISHR, "i=ii") X(IAND, "i=ii") X(IOR, "i=ii")               \
    X(IXOR, "i=ii") X(IMIN, "i=ii") X(IMAX, "i=ii") X(ILT, "i=ii") X(ILE, "i=ii")                \
    X(IGT, "i=ii") X(IGE, "i=ii") X(IEQ, "i=ii") X(INE, "i=ii") X(IABS, "i=i")                   \
    X(ISELECT, "i=iii")                                                                          \
    X(ITOF, "f=i") X(FTOI, "i=f") X(FBITS, "i=f") X(IBITS, "f=i")                                \
    X(RDF, "f=ai") X(WRF, "=aif") X(RDI, "i=ai") X(WRI, "=aii") X(DLYRD, "f=aii")                \
    X(RDFM, "f=ai") X(WRFM, "=aif")                                                              \
    X(MULSUB, "f=fff") X(ADD3, "f=fff") X(DOT2, "f=ffff") X(SMADD, "f=ffff")                     \
    X(SUBMADD, "f=ffff") X(MULMADD, "f=ffff") X(MADD2, "f=fffff") X(SMUL, "f=fff")               \
    X(MUL3, "f=fff") X(AMUL, "f=fff") X(SELGT, "f=ffff") X(WRFMADD, "=aifff")

enum Op {
#define FBC_FPB_ENUM(n, s) OP_##n,
    FBC_FPB_OPLIST(FBC_FPB_ENUM)
#undef FBC_FPB_ENUM
        OP_COUNT
};

// signature of an operation, e.g. "f=ff"
inline const char* opSig(Op op)
{
    static const char* const sigs[] = {
#define FBC_FPB_SIG(n, s) s,
        FBC_FPB_OPLIST(FBC_FPB_SIG)
#undef FBC_FPB_SIG
    };
    return sigs[op];
}

inline const char* opName(Op op)
{
    static const char* const names[] = {
#define FBC_FPB_NAME(n, s) #n,
        FBC_FPB_OPLIST(FBC_FPB_NAME)
#undef FBC_FPB_NAME
    };
    return names[op];
}

// number of written operands (0 or 1 here, 2 for MOV2): they come first in a step
inline int opWritten(Op op)
{
    return int(strchr(opSig(op), '=') - opSig(op));
}

// number of operands, written and read
inline int opArity(Op op)
{
    return int(strlen(opSig(op))) - 1;
}

// The operation functions, for one REAL type. Each one computes exactly what the FBC interpreter computes for
// the corresponding instruction(s) (fbc_interpreter.hh), reads all its operands before writing its result (so
// a destination may also be a source), and goes on with the next step: the address right after its operand
// pointers.
//
//   F(k), I(k), A(k)    operand k as a REAL, an int or an array descriptor
//   OPFN(name, n, body) defines h_<name>, whose step has n operands; NEXT(n) goes to the next step
template <class REAL>
struct Ops {
#define F(k) (*(REAL*)s->p[k])
#define I(k) (*(int*)s->p[k])
#define A(k) (*(const ArrayRef*)s->p[k])
#if FBC_FPB_TAIL
#define NEXT(n)                                                    \
    do {                                                           \
        const Step* next_ = (const Step*)&s->p[n];                 \
        __attribute__((musttail)) return next_->fn(next_);         \
    } while (0)
#else
#define NEXT(n) return (const Step*)&s->p[n]
#endif
#define OPFN(name, n, body)                                   \
    FBC_FPB_FNATTR static const Step* h_##name(const Step* s) \
    {                                                         \
        FBC_FPB_NOCONTRACT                                    \
        body;                                                 \
        NEXT(n);                                              \
    }

    // int arithmetic wraps around, as in the interpreter (no undefined behaviour on overflow)
    static inline int wrapAdd(int a, int b) { return (int)((unsigned int)a + (unsigned int)b); }
    static inline int wrapSub(int a, int b) { return (int)((unsigned int)a - (unsigned int)b); }
    static inline int wrapMul(int a, int b) { return (int)((unsigned int)a * (unsigned int)b); }
    static inline int fbits(REAL v)
    {
        int r;
        memcpy(&r, &v, sizeof(int));  // as the interpreter: *reinterpret_cast<int*>(&v)
        return r;
    }
    static inline REAL ibits(int v)
    {
        REAL r = REAL(0);
        memcpy(&r, &v, sizeof(int));
        return r;
    }

    // the last step of a block: stops the dispatch
    static const Step* h_END(const Step*) { return nullptr; }

    OPFN(MOV, 2, F(0) = F(1))
    OPFN(MOV2, 4, F(0) = F(2); F(1) = F(3))
    OPFN(ADD, 3, F(0) = F(1) + F(2))
    OPFN(SUB, 3, F(0) = F(1) - F(2))
    OPFN(MUL, 3, F(0) = F(1) * F(2))
    OPFN(DIV, 3, F(0) = F(1) / F(2))
    OPFN(REM, 3, F(0) = std::remainder(F(1), F(2)))
    OPFN(FMOD, 3, F(0) = std::fmod(F(1), F(2)))
    OPFN(POW, 3, F(0) = std::pow(F(1), F(2)))
    OPFN(ATAN2, 3, F(0) = std::atan2(F(1), F(2)))
    OPFN(MIN, 3, F(0) = std::min(F(1), F(2)))
    OPFN(MAX, 3, F(0) = std::max(F(1), F(2)))
    OPFN(COPYSIGN, 3, F(0) = std::copysign(F(1), F(2)))
    OPFN(MADD, 4, F(0) = F(1) * F(2) + F(3))
    OPFN(MSUB, 4, F(0) = F(3) - F(1) * F(2))
    OPFN(ABS, 2, F(0) = std::fabs(F(1)))
    OPFN(ACOS, 2, F(0) = std::acos(F(1)))
    OPFN(ACOSH, 2, F(0) = std::acosh(F(1)))
    OPFN(ASIN, 2, F(0) = std::asin(F(1)))
    OPFN(ASINH, 2, F(0) = std::asinh(F(1)))
    OPFN(ATAN, 2, F(0) = std::atan(F(1)))
    OPFN(ATANH, 2, F(0) = std::atanh(F(1)))
    OPFN(CEIL, 2, F(0) = std::ceil(F(1)))
    OPFN(COS, 2, F(0) = std::cos(F(1)))
    OPFN(COSH, 2, F(0) = std::cosh(F(1)))
    OPFN(EXP, 2, F(0) = std::exp(F(1)))
    OPFN(FLOOR, 2, F(0) = std::floor(F(1)))
    OPFN(LOG, 2, F(0) = std::log(F(1)))
    OPFN(LOG10, 2, F(0) = std::log10(F(1)))
    OPFN(RINT, 2, F(0) = std::rint(F(1)))
    OPFN(ROUND, 2, F(0) = std::round(F(1)))
    OPFN(SIN, 2, F(0) = std::sin(F(1)))
    OPFN(SINH, 2, F(0) = std::sinh(F(1)))
    OPFN(SQRT, 2, F(0) = std::sqrt(F(1)))
    OPFN(TAN, 2, F(0) = std::tan(F(1)))
    OPFN(TANH, 2, F(0) = std::tanh(F(1)))
    OPFN(LT, 3, I(0) = F(1) < F(2))
    OPFN(LE, 3, I(0) = F(1) <= F(2))
    OPFN(GT, 3, I(0) = F(1) > F(2))
    OPFN(GE, 3, I(0) = F(1) >= F(2))
    OPFN(EQ, 3, I(0) = F(1) == F(2))
    OPFN(NE, 3, I(0) = F(1) != F(2))
    OPFN(ISNAN, 2, I(0) = std::isnan(F(1)))
    OPFN(ISINF, 2, I(0) = std::isinf(F(1)))
    OPFN(SELECT, 4, F(0) = I(1) ? F(2) : F(3))
    OPFN(IMOV, 2, I(0) = I(1))
    OPFN(IADD, 3, I(0) = wrapAdd(I(1), I(2)))
    OPFN(ISUB, 3, I(0) = wrapSub(I(1), I(2)))
    OPFN(IMUL, 3, I(0) = wrapMul(I(1), I(2)))
    OPFN(IDIV, 3, I(0) = I(1) / I(2))
    OPFN(IREM, 3, I(0) = I(1) % I(2))
    OPFN(ISHL, 3, I(0) = I(1) << I(2))
    OPFN(ISHR, 3, I(0) = I(1) >> I(2))  // kARshInt and kLRshInt, as the interpreter
    OPFN(IAND, 3, I(0) = I(1) & I(2))
    OPFN(IOR, 3, I(0) = I(1) | I(2))
    OPFN(IXOR, 3, I(0) = I(1) ^ I(2))
    OPFN(IMIN, 3, I(0) = std::min(I(1), I(2)))
    OPFN(IMAX, 3, I(0) = std::max(I(1), I(2)))
    OPFN(ILT, 3, I(0) = I(1) < I(2))
    OPFN(ILE, 3, I(0) = I(1) <= I(2))
    OPFN(IGT, 3, I(0) = I(1) > I(2))
    OPFN(IGE, 3, I(0) = I(1) >= I(2))
    OPFN(IEQ, 3, I(0) = I(1) == I(2))
    OPFN(INE, 3, I(0) = I(1) != I(2))
    OPFN(IABS, 2, I(0) = std::abs(I(1)))
    OPFN(ISELECT, 4, I(0) = I(1) ? I(2) : I(3))
    OPFN(ITOF, 2, F(0) = REAL(I(1)))
    OPFN(FTOI, 2, I(0) = int(F(1)))
    OPFN(FBITS, 2, I(0) = fbits(F(1)))
    OPFN(IBITS, 2, F(0) = ibits(I(1)))
    // arrays: a heap region accessed with a computed index (not checked, as the interpreter)
    OPFN(RDF, 3, F(0) = ((const REAL*)A(1).base)[I(2)])
    OPFN(WRF, 3, ((REAL*)A(0).base)[I(1)] = F(2))
    OPFN(RDI, 3, I(0) = ((const int*)A(1).base)[I(2)])
    OPFN(WRI, 3, ((int*)A(0).base)[I(1)] = I(2))
    // delay lines (power-of-two lengths): arr[(i - d) & mask], arr[i & mask]
    OPFN(DLYRD, 4, F(0) = ((const REAL*)A(1).base)[wrapSub(I(2), I(3)) & int(A(1).mask)])
    OPFN(RDFM, 3, F(0) = ((const REAL*)A(1).base)[I(2) & int(A(1).mask)])
    OPFN(WRFM, 3, ((REAL*)A(0).base)[I(1) & int(A(0).mask)] = F(2))
    // fused pairs (t is the temporary that only the second operation of the pair read)
    OPFN(MULSUB, 4, F(0) = F(1) * F(2) - F(3))                  // t = a*b; d = t - c
    OPFN(ADD3, 4, F(0) = F(1) + (F(2) + F(3)))                  // t = a+b; d = x + t
    OPFN(DOT2, 5, F(0) = F(1) * F(2) + F(3) * F(4))             // t = a*b; d = x*y + t
    OPFN(SMADD, 5, F(0) = F(1) * (F(2) - F(3)) + F(4))          // t = a-b; d = x*t + y
    OPFN(SUBMADD, 5, F(0) = F(1) - (F(2) * F(3) + F(4)))        // t = a*b+c; d = x - t
    OPFN(MULMADD, 5, F(0) = F(1) * (F(2) * F(3) + F(4)))        // t = a*b+c; d = x*t
    OPFN(MADD2, 6, F(0) = F(1) * F(2) + (F(3) * F(4) + F(5)))   // t = a*b+c; d = x*y + t
    OPFN(SMUL, 4, F(0) = F(1) * (F(2) - F(3)))                  // t = a-b; d = x*t
    OPFN(MUL3, 4, F(0) = F(1) * (F(2) * F(3)))                  // t = a*b; d = x*t
    OPFN(AMUL, 4, F(0) = F(1) * (F(2) + F(3)))                  // t = a+b; d = x*t
    OPFN(SELGT, 5, F(0) = (F(1) > F(2)) ? F(3) : F(4))          // t = a > b; d = t ? x : y
    OPFN(WRFMADD, 5, ((REAL*)A(0).base)[I(1) & int(A(0).mask)] = F(2) * F(3) + F(4))

#undef OPFN
#undef NEXT
#undef A
#undef I
#undef F

    // the function that runs an operation
    static StepFn fn(Op op)
    {
        static const StepFn fns[] = {
#define FBC_FPB_FN(n, s) &h_##n,
            FBC_FPB_OPLIST(FBC_FPB_FN)
#undef FBC_FPB_FN
        };
        return fns[op];
    }
};

}  // namespace fbcfpb

/*
 * The compiler of one DSP block, and its executor (FBCExecuteFun). The constructor compiles; execute() runs one
 * cycle (the whole sample loop) on the heaps of one instance. See the comment at the top of this file.
 */
template <class REAL>
class FBCFPBCompiler : public FBCExecuteFun<REAL> {
   private:
    typedef fbcfpb::Op       Op;
    typedef fbcfpb::Step     Step;
    typedef fbcfpb::StepFn   StepFn;
    typedef fbcfpb::ArrayRef ArrayRef;

    // thrown while compiling when the block uses something this compiler does not handle
    struct Unsupported {
        std::string why;
    };

    // ------------------------------------------------------------------ expression nodes

    // A value computed by the sample loop, as a tree. Built by exec(), turned into instructions by gen().
    // Each node belongs to one tree: FBC has no instruction that duplicates a stack value.
    struct Node {
        enum Kind {
            kConstReal,    // rv
            kConstInt,     // iv
            kLoad,         // heap cell off of type t (also an indexed access with a constant index)
            kLoadIndexed,  // heap region [base, base + size) of type t, indexed by a[0]
            kInput,        // input sample of channel ch, for the current frame
            kOp,           // operation op on the arguments a
            kSelect,       // a[0] ? a[1] : a[2] (both branches are computed)
            kSaved         // saved value n (see hazard())
        } k;
        char               t;  // 'f' (REAL) or 'i' (int)
        REAL               rv  = 0;
        int                iv  = 0;
        int                off = 0, base = 0, size = 0, ch = 0, n = 0;
        Op                 op  = fbcfpb::OP_END;
        std::vector<Node*> a;  // kOp: arguments; kSelect: condition, then, else; kLoadIndexed: index
    };

    // A write to memory, in the order of the FBC code; v is the value written.
    struct Stmt {
        enum Kind {
            kStore,         // heap cell off of type t = v
            kStoreIndexed,  // heap region [base, base + size) of type t, at index idx, = v
            kOutput,        // output sample of channel ch = v
            kSave,          // saved value n = v (before a store that would change what v reads)
            kCond           // loop condition = v (the last statement)
        } k;
        char  t   = 'f';
        int   off = 0, base = 0, size = 0, ch = 0, n = 0;
        Node* idx = nullptr;
        Node* v   = nullptr;
    };

    // An operand, before binding: a kind (see the table at the top of this file) and an index (heap offset,
    // temporary, saved value, constant, channel or array number).
    struct Loc {
        char k;
        int  i;
        bool operator==(const Loc& o) const { return k == o.k && i == o.i; }
    };

    // A 3-address instruction: the operation and its operands, in the order of its signature.
    struct Instr {
        Op               op;
        std::vector<Loc> ops;
    };

    // The steps bound to one pair of heaps (one instance), with the storage that belongs to that instance.
    struct Bound {
        std::vector<REAL>     fRealTemps;  // real temporaries, then real saved values
        std::vector<int>      fIntTemps;   // int temporaries, then int saved values
        std::vector<REAL>     fIO;         // inputs, then outputs, of the current frame
        std::vector<ArrayRef> fArrays;     // one descriptor per fArrayDefs entry, pointing into the heaps
        std::vector<void*>    fWords;      // the steps (see Step)
        int                   fCond = 0;   // the loop condition, written by the last statement
    };

    // compile time
    std::vector<std::unique_ptr<Node>> fNodes;  // owns every Node
    std::vector<Stmt>                  fStmts;  // the sample loop body, after exec()
    std::vector<Instr>                 fCode;   // the instructions, after statement() and the peephole passes
    std::vector<REAL>                  fRealConsts;  // constant pools ('K', 'J'), shared by all the bindings
    std::vector<int>                   fIntConsts;
    std::vector<std::pair<char, std::pair<int, int>>> fArrayDefs;  // 'A' operands: type, (base, size)

    bool        fCompiled  = false;
    std::string fWhy;                   // why the block is not compiled
    int         fLoopVar   = -1;        // int heap offset of the loop variable (i0)
    bool        fLoopVarStored = false; // the body has already incremented it (later input/output accesses refused)
    int         fNumInputs = 0, fNumOutputs = 0;  // channels used by the block
    int         fSaved     = 0;         // number of saved values
    int         fTmpReal = 0, fTmpInt = 0, fMaxTmpReal = 0, fMaxTmpInt = 0;  // temporaries in use, and the maximum
    int         fFused = 0, fUnfused = 0;  // statistics: fused pairs, instructions before the peephole passes

    // run time: the bindings, one per pair of heaps, and the last one used (instances usually run one by one)
    std::mutex                                     fMutex;
    std::map<std::pair<int*, REAL*>, Bound*>       fBound;
    std::pair<int*, REAL*>                         fLastKey{nullptr, nullptr};
    Bound*                                         fLast = nullptr;

    static bool trace() { return getenv("FAUST_INTERP_FPB_TRACE") != nullptr; }

    // node constructors

    Node* node(typename Node::Kind k, char t)
    {
        fNodes.emplace_back(new Node());
        Node* n = fNodes.back().get();
        n->k    = k;
        n->t    = t;
        return n;
    }
    Node* constReal(REAL v)
    {
        Node* n = node(Node::kConstReal, 'f');
        n->rv   = v;
        return n;
    }
    Node* constInt(int v)
    {
        Node* n = node(Node::kConstInt, 'i');
        n->iv   = v;
        return n;
    }
    Node* load(char t, int off)
    {
        Node* n = node(Node::kLoad, t);
        n->off  = off;
        return n;
    }
    Node* mkOp(char t, Op op, std::vector<Node*> args)
    {
        Node* n = node(Node::kOp, t);
        n->op   = op;
        n->a    = std::move(args);
        return n;
    }
    static bool isConst(Node* n) { return n->k == Node::kConstReal || n->k == Node::kConstInt; }

    // Does the value read heap type t in [lo, hi)? Conservative for an indexed load: any overlap of its region.
    static bool reads(Node* n, char t, int lo, int hi)
    {
        switch (n->k) {
            case Node::kLoad:
                return n->t == t && n->off >= lo && n->off < hi;
            case Node::kLoadIndexed:
                if (n->t == t && n->base < hi && n->base + n->size > lo) return true;
                return reads(n->a[0], t, lo, hi);
            case Node::kOp:
            case Node::kSelect:
                for (Node* x : n->a) {
                    if (reads(x, t, lo, hi)) return true;
                }
                return false;
            default:
                return false;
        }
    }

    // ------------------------------------------------------------------ symbolic execution

    // A store to heap type t, [lo, hi) is about to happen. A value still on the stack that reads that range was
    // computed (in FBC) before the store, so it must not see the new value: it is computed now into a saved
    // value (a kSave statement), and the stack holds a kSaved node instead. Example: "kLoadReal a, kLoadReal b,
    // kStoreReal a, kLoadReal a, kAddReal" computes old a + new a, so the first load is saved before the store.
    void hazard(std::vector<Node*>& st, char t, int lo, int hi)
    {
        for (Node*& x : st) {
            if (!isConst(x) && reads(x, t, lo, hi)) {
                Stmt s;
                s.k = Stmt::kSave;
                s.t = x->t;
                s.n = fSaved;
                s.v = x;
                fStmts.push_back(s);
                Node* h = node(Node::kSaved, x->t);
                h->n    = fSaved++;
                x       = h;
            }
        }
    }

    // heap cell off of type t = v
    void store(std::vector<Node*>& st, char t, int off, Node* v)
    {
        hazard(st, t, off, off + 1);
        Stmt s;
        s.k   = Stmt::kStore;
        s.t   = t;
        s.off = off;
        s.v   = v;
        fStmts.push_back(s);
    }

    // heap[dst] = heap[src], for FBC's move instructions: a load and a store, so that hazard() applies
    void moves(std::vector<Node*>& st, char t, int dst, int src)
    {
        store(st, t, dst, load(t, src));
    }

    static Node* pop(std::vector<Node*>& st)
    {
        if (st.empty()) throw Unsupported{"stack underflow"};
        Node* n = st.back();
        st.pop_back();
        return n;
    }

    // is n the loop variable, as inputs and outputs are indexed?
    bool isLoopIndex(Node* n) const { return n->k == Node::kLoad && n->t == 'i' && n->off == fLoopVar; }

    // a branch of kSelectReal / kSelectInt: a block with no store that pushes one value
    Node* branch(FBCBlockInstruction<REAL>* block)
    {
        std::vector<Node*> st;
        exec(block, st, true);
        if (st.size() != 1) throw Unsupported{"a select branch does not leave one value"};
        return st[0];
    }

    void binary(std::vector<Node*>& st, char t, Op op)
    {
        Node* a = pop(st);  // pushed last: the left operand
        Node* b = pop(st);
        st.push_back(mkOp(t, op, {a, b}));
    }
    void unary(std::vector<Node*>& st, char t, Op op) { st.push_back(mkOp(t, op, {pop(st)})); }

    // Runs an FBC block symbolically on the stack st: values become Node trees, and writes become statements
    // appended to fStmts. inSelect: the block is a select branch, where stores (and kCondBranch) are refused:
    // both branches are computed, so a store would happen even when its branch is not chosen (see "Selects").
    // Throws Unsupported for anything not handled. For the loop body, it stops at kCondBranch.
    void exec(FBCBlockInstruction<REAL>* block, std::vector<Node*>& st, bool inSelect)
    {
        using namespace fbcfpb;
        for (FBCBasicInstruction<REAL>* ins : block->fInstructions) {
            FBCInstruction::Opcode o = ins->fOpcode;
            switch (o) {
                case FBCInstruction::kRealValue:
                    st.push_back(constReal(ins->fRealValue));
                    break;
                case FBCInstruction::kInt32Value:
                    st.push_back(constInt(ins->fIntValue));
                    break;
                case FBCInstruction::kLoadReal:
                    st.push_back(load('f', ins->fOffset1));
                    break;
                case FBCInstruction::kLoadInt:
                    st.push_back(load('i', ins->fOffset1));
                    break;
                case FBCInstruction::kStoreReal:
                case FBCInstruction::kStoreInt:
                case FBCInstruction::kStoreRealValue:
                case FBCInstruction::kStoreIntValue: {
                    if (inSelect) throw Unsupported{"a select branch with a store"};
                    char  t = (o == FBCInstruction::kStoreReal || o == FBCInstruction::kStoreRealValue) ? 'f' : 'i';
                    Node* v = (o == FBCInstruction::kStoreRealValue) ? constReal(ins->fRealValue)
                              : (o == FBCInstruction::kStoreIntValue) ? constInt(ins->fIntValue)
                                                                      : pop(st);
                    if (t == 'i' && ins->fOffset1 == fLoopVar) fLoopVarStored = true;
                    store(st, t, ins->fOffset1, v);
                    break;
                }
                case FBCInstruction::kMoveReal:
                case FBCInstruction::kMoveInt:
                    if (inSelect) throw Unsupported{"a select branch with a store"};
                    moves(st, o == FBCInstruction::kMoveReal ? 'f' : 'i', ins->fOffset1, ins->fOffset2);
                    break;
                case FBCInstruction::kPairMoveReal:
                case FBCInstruction::kPairMoveInt: {
                    if (inSelect) throw Unsupported{"a select branch with a store"};
                    char t = (o == FBCInstruction::kPairMoveReal) ? 'f' : 'i';
                    moves(st, t, ins->fOffset1, ins->fOffset1 - 1);
                    moves(st, t, ins->fOffset2, ins->fOffset2 - 1);
                    break;
                }
                case FBCInstruction::kBlockPairMoveReal:
                case FBCInstruction::kBlockPairMoveInt: {
                    if (inSelect) throw Unsupported{"a select branch with a store"};
                    char t = (o == FBCInstruction::kBlockPairMoveReal) ? 'f' : 'i';
                    for (int i = ins->fOffset1; i < ins->fOffset2; i += 2) moves(st, t, i + 1, i);
                    break;
                }
                case FBCInstruction::kBlockShiftReal:
                case FBCInstruction::kBlockShiftInt: {
                    if (inSelect) throw Unsupported{"a select branch with a store"};
                    if (ins->fOffset1 - ins->fOffset2 > 256) throw Unsupported{"a long block shift"};
                    char t = (o == FBCInstruction::kBlockShiftReal) ? 'f' : 'i';
                    for (int i = ins->fOffset1; i > ins->fOffset2; i -= 1) moves(st, t, i, i - 1);
                    break;
                }
                case FBCInstruction::kLoadIndexedReal:
                case FBCInstruction::kLoadIndexedInt: {
                    char  t   = (o == FBCInstruction::kLoadIndexedReal) ? 'f' : 'i';
                    Node* idx = pop(st);
                    if (idx->k == Node::kConstInt) {
                        st.push_back(load(t, ins->fOffset1 + idx->iv));
                    } else {
                        Node* n = node(Node::kLoadIndexed, t);
                        n->base = ins->fOffset1;
                        n->size = ins->fOffset2;
                        n->a    = {idx};
                        st.push_back(n);
                    }
                    break;
                }
                case FBCInstruction::kStoreIndexedReal:
                case FBCInstruction::kStoreIndexedInt: {
                    if (inSelect) throw Unsupported{"a select branch with a store"};
                    char  t   = (o == FBCInstruction::kStoreIndexedReal) ? 'f' : 'i';
                    Node* idx = pop(st);
                    Node* v   = pop(st);
                    if (idx->k == Node::kConstInt) {
                        store(st, t, ins->fOffset1 + idx->iv, v);
                    } else {
                        hazard(st, t, ins->fOffset1, ins->fOffset1 + ins->fOffset2);
                        Stmt s;
                        s.k    = Stmt::kStoreIndexed;
                        s.t    = t;
                        s.base = ins->fOffset1;
                        s.size = ins->fOffset2;
                        s.idx  = idx;
                        s.v    = v;
                        fStmts.push_back(s);
                    }
                    break;
                }
                case FBCInstruction::kLoadInput: {
                    Node* idx = pop(st);
                    if (!isLoopIndex(idx) || fLoopVarStored) throw Unsupported{"an input read with another index"};
                    Node* n = node(Node::kInput, 'f');
                    n->ch   = ins->fOffset1;
                    fNumInputs = std::max(fNumInputs, n->ch + 1);
                    st.push_back(n);
                    break;
                }
                case FBCInstruction::kStoreOutput: {
                    if (inSelect) throw Unsupported{"a select branch with a store"};
                    Node* idx = pop(st);
                    Node* v   = pop(st);
                    if (!isLoopIndex(idx) || fLoopVarStored) throw Unsupported{"an output write with another index"};
                    Stmt s;
                    s.k  = Stmt::kOutput;
                    s.ch = ins->fOffset1;
                    s.v  = v;
                    fNumOutputs = std::max(fNumOutputs, s.ch + 1);
                    fStmts.push_back(s);
                    break;
                }
                case FBCInstruction::kCastReal: {
                    Node* x = pop(st);
                    st.push_back(x->k == Node::kConstInt ? constReal(REAL(x->iv)) : mkOp('f', OP_ITOF, {x}));
                    break;
                }
                case FBCInstruction::kCastInt:
                    unary(st, 'i', OP_FTOI);
                    break;
                case FBCInstruction::kBitcastInt:
                    unary(st, 'i', OP_FBITS);
                    break;
                case FBCInstruction::kBitcastReal:
                    unary(st, 'f', OP_IBITS);
                    break;

                case FBCInstruction::kAddReal: binary(st, 'f', OP_ADD); break;
                case FBCInstruction::kSubReal: binary(st, 'f', OP_SUB); break;
                case FBCInstruction::kMultReal: binary(st, 'f', OP_MUL); break;
                case FBCInstruction::kDivReal: binary(st, 'f', OP_DIV); break;
                case FBCInstruction::kRemReal: binary(st, 'f', OP_REM); break;
                case FBCInstruction::kFmodf: binary(st, 'f', OP_FMOD); break;
                case FBCInstruction::kPowf: binary(st, 'f', OP_POW); break;
                case FBCInstruction::kAtan2f: binary(st, 'f', OP_ATAN2); break;
                case FBCInstruction::kMinf: binary(st, 'f', OP_MIN); break;
                case FBCInstruction::kMaxf: binary(st, 'f', OP_MAX); break;
                case FBCInstruction::kCopysignf: binary(st, 'f', OP_COPYSIGN); break;
                case FBCInstruction::kGTReal: binary(st, 'i', OP_GT); break;
                case FBCInstruction::kLTReal: binary(st, 'i', OP_LT); break;
                case FBCInstruction::kGEReal: binary(st, 'i', OP_GE); break;
                case FBCInstruction::kLEReal: binary(st, 'i', OP_LE); break;
                case FBCInstruction::kEQReal: binary(st, 'i', OP_EQ); break;
                case FBCInstruction::kNEReal: binary(st, 'i', OP_NE); break;

                case FBCInstruction::kAddInt: binary(st, 'i', OP_IADD); break;
                case FBCInstruction::kSubInt: binary(st, 'i', OP_ISUB); break;
                case FBCInstruction::kMultInt: binary(st, 'i', OP_IMUL); break;
                case FBCInstruction::kDivInt: binary(st, 'i', OP_IDIV); break;
                case FBCInstruction::kRemInt: binary(st, 'i', OP_IREM); break;
                case FBCInstruction::kLshInt: binary(st, 'i', OP_ISHL); break;
                case FBCInstruction::kARshInt: binary(st, 'i', OP_ISHR); break;
                case FBCInstruction::kLRshInt: binary(st, 'i', OP_ISHR); break;
                case FBCInstruction::kANDInt: binary(st, 'i', OP_IAND); break;
                case FBCInstruction::kORInt: binary(st, 'i', OP_IOR); break;
                case FBCInstruction::kXORInt: binary(st, 'i', OP_IXOR); break;
                case FBCInstruction::kMin: binary(st, 'i', OP_IMIN); break;
                case FBCInstruction::kMax: binary(st, 'i', OP_IMAX); break;
                case FBCInstruction::kGTInt: binary(st, 'i', OP_IGT); break;
                case FBCInstruction::kLTInt: binary(st, 'i', OP_ILT); break;
                case FBCInstruction::kGEInt: binary(st, 'i', OP_IGE); break;
                case FBCInstruction::kLEInt: binary(st, 'i', OP_ILE); break;
                case FBCInstruction::kEQInt: binary(st, 'i', OP_IEQ); break;
                case FBCInstruction::kNEInt: binary(st, 'i', OP_INE); break;

                case FBCInstruction::kAbs: unary(st, 'i', OP_IABS); break;
                case FBCInstruction::kAbsf: unary(st, 'f', OP_ABS); break;
                case FBCInstruction::kAcosf: unary(st, 'f', OP_ACOS); break;
                case FBCInstruction::kAcoshf: unary(st, 'f', OP_ACOSH); break;
                case FBCInstruction::kAsinf: unary(st, 'f', OP_ASIN); break;
                case FBCInstruction::kAsinhf: unary(st, 'f', OP_ASINH); break;
                case FBCInstruction::kAtanf: unary(st, 'f', OP_ATAN); break;
                case FBCInstruction::kAtanhf: unary(st, 'f', OP_ATANH); break;
                case FBCInstruction::kCeilf: unary(st, 'f', OP_CEIL); break;
                case FBCInstruction::kCosf: unary(st, 'f', OP_COS); break;
                case FBCInstruction::kCoshf: unary(st, 'f', OP_COSH); break;
                case FBCInstruction::kExpf: unary(st, 'f', OP_EXP); break;
                case FBCInstruction::kFloorf: unary(st, 'f', OP_FLOOR); break;
                case FBCInstruction::kLogf: unary(st, 'f', OP_LOG); break;
                case FBCInstruction::kLog10f: unary(st, 'f', OP_LOG10); break;
                case FBCInstruction::kRintf: unary(st, 'f', OP_RINT); break;
                case FBCInstruction::kRoundf: unary(st, 'f', OP_ROUND); break;
                case FBCInstruction::kSinf: unary(st, 'f', OP_SIN); break;
                case FBCInstruction::kSinhf: unary(st, 'f', OP_SINH); break;
                case FBCInstruction::kSqrtf: unary(st, 'f', OP_SQRT); break;
                case FBCInstruction::kTanf: unary(st, 'f', OP_TAN); break;
                case FBCInstruction::kTanhf: unary(st, 'f', OP_TANH); break;
                case FBCInstruction::kIsnanf: unary(st, 'i', OP_ISNAN); break;
                case FBCInstruction::kIsinff: unary(st, 'i', OP_ISINF); break;

                case FBCInstruction::kSelectReal:
                case FBCInstruction::kSelectInt: {
                    // Both branches are turned into trees (branch() refuses a store in them), and become one
                    // kSelect node: gen() computes both, then SELECT keeps one (see "Selects" at the top of this
                    // file). With a constant condition, only the chosen branch is kept.
                    char  t = (o == FBCInstruction::kSelectReal) ? 'f' : 'i';
                    Node* c = pop(st);
                    Node* x = branch(ins->fBranch1);
                    Node* y = branch(ins->fBranch2);
                    if (c->k == Node::kConstInt) {
                        st.push_back(c->iv ? x : y);
                    } else {
                        Node* n = node(Node::kSelect, t);
                        n->a    = {c, x, y};
                        st.push_back(n);
                    }
                    break;
                }
                case FBCInstruction::kCondBranch: {
                    if (inSelect) throw Unsupported{"a branch in a select"};
                    Stmt s;
                    s.k = Stmt::kCond;
                    s.v = pop(st);
                    fStmts.push_back(s);
                    return;  // the end of the loop body
                }
                case FBCInstruction::kReturn:
                    return;
                default:
                    throw Unsupported{std::string("FBC instruction ") + gFBCInstructionTable[o]};
            }
        }
    }

    // ------------------------------------------------------------------ code generation

    // a constant's slot in the pool, shared by equal constants (compared bit for bit: -0 is not 0)
    Loc constLoc(Node* n)
    {
        if (n->t == 'f') {
            for (size_t k = 0; k < fRealConsts.size(); k++) {
                if (memcmp(&fRealConsts[k], &n->rv, sizeof(REAL)) == 0) return Loc{'K', int(k)};
            }
            fRealConsts.push_back(n->rv);
            return Loc{'K', int(fRealConsts.size()) - 1};
        } else {
            for (size_t k = 0; k < fIntConsts.size(); k++) {
                if (fIntConsts[k] == n->iv) return Loc{'J', int(k)};
            }
            fIntConsts.push_back(n->iv);
            return Loc{'J', int(fIntConsts.size()) - 1};
        }
    }

    // the array descriptor of a heap region, shared by the accesses to the same region
    Loc arrayLoc(char t, int base, int size)
    {
        for (size_t k = 0; k < fArrayDefs.size(); k++) {
            if (fArrayDefs[k].first == t && fArrayDefs[k].second.first == base &&
                fArrayDefs[k].second.second == size) {
                return Loc{'A', int(k)};
            }
        }
        fArrayDefs.push_back({t, {base, size}});
        return Loc{'A', int(fArrayDefs.size()) - 1};
    }

    // a new temporary for the current statement (fTmpReal / fTmpInt are reset at each statement)
    Loc newTmp(char t)
    {
        if (t == 'f') {
            Loc l{'t', fTmpReal++};
            fMaxTmpReal = std::max(fMaxTmpReal, fTmpReal);
            return l;
        } else {
            Loc l{'u', fTmpInt++};
            fMaxTmpInt = std::max(fMaxTmpInt, fTmpInt);
            return l;
        }
    }

    void emit(Op op, std::vector<Loc> ops) { fCode.push_back(Instr{op, std::move(ops)}); }

    // dst = r, unless they are the same location
    Loc mov(const Loc& dst, const Loc& r, char t)
    {
        if (!(dst == r)) emit(t == 'f' ? fbcfpb::OP_MOV : fbcfpb::OP_IMOV, {dst, r});
        return dst;
    }

    static bool isMul(Node* n) { return n->k == Node::kOp && n->op == fbcfpb::OP_MUL; }

    // Is idx a delay line index on a REAL region of power-of-two size: (x & mask) or ((a - b) & mask), with
    // mask = size - 1? Sets x (and a, b for the second form, else nullptr).
    static bool delayIndex(char t, int size, Node* idx, Node*& x, Node*& a, Node*& b)
    {
        if (t != 'f' || size <= 0 || (size & (size - 1)) != 0) return false;
        if (idx->k != Node::kOp || idx->op != fbcfpb::OP_IAND) return false;
        int mask = size - 1;
        if (idx->a[1]->k == Node::kConstInt && idx->a[1]->iv == mask) {
            x = idx->a[0];
        } else if (idx->a[0]->k == Node::kConstInt && idx->a[0]->iv == mask) {
            x = idx->a[1];
        } else {
            return false;
        }
        a = b = nullptr;
        if (x->k == Node::kOp && x->op == fbcfpb::OP_ISUB) {
            a = x->a[0];
            b = x->a[1];
        }
        return true;
    }

    // Emits the instructions that compute n, and returns where the result is. With dst, the result goes there:
    // the last instruction writes dst directly, or a move is added when n is already a location (a load, a
    // constant...). Without dst, a location is returned as it is (no instruction), and a computed value goes
    // into a new temporary. MADD / MSUB and the delay line operations are chosen here.
    Loc gen(Node* n, const Loc* dst)
    {
        using namespace fbcfpb;
        Loc r{'?', 0};
        switch (n->k) {
            case Node::kConstReal:
            case Node::kConstInt:
                r = constLoc(n);
                break;
            case Node::kLoad:
                r = Loc{n->t == 'f' ? 'R' : 'I', n->off};
                break;
            case Node::kInput:
                r = Loc{'n', n->ch};
                break;
            case Node::kSaved:
                r = Loc{n->t == 'f' ? 's' : 'v', n->n};
                break;
            case Node::kLoadIndexed: {
                Node *x, *a, *b;
                Loc   arr = arrayLoc(n->t, n->base, n->size);
                if (delayIndex(n->t, n->size, n->a[0], x, a, b)) {
                    if (a) {
                        Loc la = gen(a, nullptr), lb = gen(b, nullptr);
                        Loc d  = dst ? *dst : newTmp(n->t);
                        emit(OP_DLYRD, {d, arr, la, lb});
                        return d;
                    }
                    Loc lx = gen(x, nullptr);
                    Loc d  = dst ? *dst : newTmp(n->t);
                    emit(OP_RDFM, {d, arr, lx});
                    return d;
                }
                Loc li = gen(n->a[0], nullptr);
                Loc d  = dst ? *dst : newTmp(n->t);
                emit(n->t == 'f' ? OP_RDF : OP_RDI, {d, arr, li});
                return d;
            }
            case Node::kSelect: {
                // The condition and both branches are computed unconditionally, then one value is kept: there
                // are no jumps between steps (see "Selects" at the top of this file).
                Loc c = gen(n->a[0], nullptr), x = gen(n->a[1], nullptr), y = gen(n->a[2], nullptr);
                Loc d = dst ? *dst : newTmp(n->t);
                emit(n->t == 'f' ? OP_SELECT : OP_ISELECT, {d, c, x, y});
                return d;
            }
            case Node::kOp: {
                Op                 op   = n->op;
                std::vector<Node*> args = n->a;
                if (n->t == 'f' && op == OP_ADD && isMul(args[0])) {
                    op   = OP_MADD;
                    args = {args[0]->a[0], args[0]->a[1], args[1]};
                } else if (n->t == 'f' && op == OP_ADD && isMul(args[1])) {
                    op   = OP_MADD;
                    args = {args[1]->a[0], args[1]->a[1], args[0]};
                } else if (n->t == 'f' && op == OP_SUB && isMul(args[1])) {
                    op   = OP_MSUB;
                    args = {args[1]->a[0], args[1]->a[1], args[0]};
                }
                std::vector<Loc> ops(1);
                for (Node* x : args) ops.push_back(gen(x, nullptr));
                ops[0] = dst ? *dst : newTmp(n->t);
                Loc d  = ops[0];
                emit(op, std::move(ops));
                return d;
            }
        }
        return dst ? mov(*dst, r, n->t) : r;
    }

    // emits the instructions of one statement
    void statement(const Stmt& s)
    {
        using namespace fbcfpb;
        fTmpReal = fTmpInt = 0;  // temporaries live within one statement
        switch (s.k) {
            case Stmt::kStore: {
                Loc d{s.t == 'f' ? 'R' : 'I', s.off};
                gen(s.v, &d);
                break;
            }
            case Stmt::kStoreIndexed: {
                Loc   arr = arrayLoc(s.t, s.base, s.size);
                Node *x, *a, *b;
                if (delayIndex(s.t, s.size, s.idx, x, a, b) && !a) {
                    Loc lx = gen(x, nullptr), lv = gen(s.v, nullptr);
                    emit(OP_WRFM, {arr, lx, lv});
                    break;
                }
                Loc li = gen(s.idx, nullptr), lv = gen(s.v, nullptr);
                emit(s.t == 'f' ? OP_WRF : OP_WRI, {arr, li, lv});
                break;
            }
            case Stmt::kOutput: {
                Loc d{'o', s.ch};
                gen(s.v, &d);
                break;
            }
            case Stmt::kSave: {
                Loc d{s.t == 'f' ? 's' : 'v', s.n};
                gen(s.v, &d);
                break;
            }
            case Stmt::kCond: {
                Loc d{'c', 0};
                gen(s.v, &d);
                break;
            }
        }
    }

    // ------------------------------------------------------------------ peephole

    // Two real moves in a row become one MOV2, which does the two copies in the same order (the second one may
    // read what the first one wrote).
    void pairMoves()
    {
        std::vector<Instr> out;
        for (size_t k = 0; k < fCode.size(); k++) {
            if (fCode[k].op == fbcfpb::OP_MOV && k + 1 < fCode.size() && fCode[k + 1].op == fbcfpb::OP_MOV) {
                out.push_back(Instr{fbcfpb::OP_MOV2,
                                    {fCode[k].ops[0], fCode[k + 1].ops[0], fCode[k].ops[1], fCode[k + 1].ops[1]}});
                k++;
            } else {
                out.push_back(fCode[k]);
            }
        }
        fCode.swap(out);
    }

    // A fusion: a: first op, b: second op, p: which read operand of b is a's temporary (0 = b's first read
    // operand), fused: the fused op, order: the fused op's operands, one character each: '0'..'9' for a's operand
    // k, 'A'..'J' for b's operand k. Example: {MUL, SUB, 0, MULSUB, "A12C"}: t = x*y; d = t - z becomes
    // MULSUB d, x, y, z (b.ops = d, t, z, so 'A' = d and 'C' = z; a.ops = t, x, y, so '1' = x and '2' = y).
    struct FuseRule {
        Op          a, b;
        int         p;
        Op          fused;
        const char* order;
    };

    // Fuses the pairs of consecutive instructions that match a rule, when the temporary written by the first one
    // is read exactly once by the second one, is not written by it, and is not read again before it is written
    // again. One pass, left to right; a fused instruction is not fused again.
    void fuse()
    {
        using namespace fbcfpb;
        // operand codes: '0'..'9' = a.ops[k], 'A'..'J' = b.ops[k]
        static const FuseRule rules[] = {
            {OP_MUL, OP_SUB, 0, OP_MULSUB, "A12C"},     {OP_ADD, OP_ADD, 1, OP_ADD3, "AB12"},
            {OP_ADD, OP_ADD, 0, OP_ADD3, "AC12"},       {OP_MUL, OP_MADD, 2, OP_DOT2, "ABC12"},
            {OP_SUB, OP_MADD, 1, OP_SMADD, "AB12D"},    {OP_SUB, OP_MADD, 0, OP_SMADD, "AC12D"},
            {OP_MADD, OP_SUB, 1, OP_SUBMADD, "AB123"},  {OP_MADD, OP_MUL, 1, OP_MULMADD, "AB123"},
            {OP_MADD, OP_MUL, 0, OP_MULMADD, "AC123"},  {OP_MADD, OP_MADD, 2, OP_MADD2, "ABC123"},
            {OP_SUB, OP_MUL, 1, OP_SMUL, "AB12"},       {OP_SUB, OP_MUL, 0, OP_SMUL, "AC12"},
            {OP_MUL, OP_MUL, 1, OP_MUL3, "AB12"},       {OP_MUL, OP_MUL, 0, OP_MUL3, "AC12"},
            {OP_ADD, OP_MUL, 1, OP_AMUL, "AB12"},       {OP_ADD, OP_MUL, 0, OP_AMUL, "AC12"},
            {OP_GT, OP_SELECT, 0, OP_SELGT, "A12CD"},   {OP_MADD, OP_WRFM, 2, OP_WRFMADD, "AB123"},
        };
        auto isTmp = [](const Loc& l) { return l.k == 't' || l.k == 'u'; };
        auto readsLoc = [](const Instr& in, const Loc& t) {
            for (size_t j = opWritten(in.op); j < in.ops.size(); j++) {
                if (in.ops[j] == t) return true;
            }
            return false;
        };
        auto writesLoc = [](const Instr& in, const Loc& t) {
            for (int j = 0; j < opWritten(in.op); j++) {
                if (in.ops[j] == t) return true;
            }
            return false;
        };
        std::vector<Instr> out;
        for (size_t k = 0; k < fCode.size(); k++) {
            bool done = false;
            if (k + 1 < fCode.size() && opWritten(fCode[k].op) == 1 && isTmp(fCode[k].ops[0])) {
                const Instr& a  = fCode[k];
                const Instr& b  = fCode[k + 1];
                const Loc    t  = a.ops[0];
                int          wb = opWritten(b.op);
                for (const FuseRule& r : rules) {
                    if (r.a != a.op || r.b != b.op || !(b.ops[wb + r.p] == t)) continue;
                    int uses = 0;
                    for (size_t j = wb; j < b.ops.size(); j++) uses += (b.ops[j] == t);
                    if (uses != 1 || writesLoc(b, t)) continue;
                    bool dead = true;  // not read again before it is written again
                    for (size_t j = k + 2; j < fCode.size(); j++) {
                        if (readsLoc(fCode[j], t)) {
                            dead = false;
                            break;
                        }
                        if (writesLoc(fCode[j], t)) break;
                    }
                    if (!dead) continue;
                    std::vector<Loc> ops;
                    for (const char* c = r.order; *c; c++) {
                        ops.push_back(*c >= 'A' ? b.ops[*c - 'A'] : a.ops[*c - '0']);
                    }
                    out.push_back(Instr{r.fused, ops});
                    fFused++;
                    k++;
                    done = true;
                    break;
                }
            }
            if (!done) out.push_back(fCode[k]);
        }
        fCode.swap(out);
    }

    // ------------------------------------------------------------------ compile

    // Checks the shape of the DSP block (one sample loop, see the top of this file), runs its body symbolically,
    // and generates the instructions. Throws Unsupported.
    void compile(FBCBlockInstruction<REAL>* block)
    {
        std::vector<FBCBasicInstruction<REAL>*>& top = block->fInstructions;
        if (!(top.size() == 2 && top[0]->fOpcode == FBCInstruction::kLoop &&
              top[1]->fOpcode == FBCInstruction::kReturn)) {
            throw Unsupported{"the DSP block is not one sample loop (scalar mode)"};
        }
        std::vector<FBCBasicInstruction<REAL>*>& init = top[0]->fBranch1->fInstructions;
        if (!(init.size() >= 2 && init[0]->fOpcode == FBCInstruction::kInt32Value && init[0]->fIntValue == 0 &&
              init[1]->fOpcode == FBCInstruction::kStoreInt &&
              (init.size() == 2 || (init.size() == 3 && init[2]->fOpcode == FBCInstruction::kReturn)))) {
            throw Unsupported{"unexpected sample loop header"};
        }
        fLoopVar = init[1]->fOffset1;

        std::vector<Node*> st;
        exec(top[0]->fBranch2, st, false);
        if (!st.empty()) throw Unsupported{"the sample loop leaves values on the stack"};
        if (fStmts.empty() || fStmts.back().k != Stmt::kCond) throw Unsupported{"the sample loop has no condition"};

        for (const Stmt& s : fStmts) statement(s);
        fUnfused = int(fCode.size());
        pairMoves();
        fuse();
        fCompiled = true;
    }

    // the address of an operand, for binding b on the heaps ih / rh
    void* ptr(Bound* b, int* ih, REAL* rh, const Loc& l)
    {
        switch (l.k) {
            case 'R': return &rh[l.i];
            case 'I': return &ih[l.i];
            case 't': return &b->fRealTemps[l.i];
            case 'u': return &b->fIntTemps[l.i];
            case 's': return &b->fRealTemps[fMaxTmpReal + l.i];
            case 'v': return &b->fIntTemps[fMaxTmpInt + l.i];
            case 'K': return &fRealConsts[l.i];
            case 'J': return &fIntConsts[l.i];
            case 'n': return &b->fIO[l.i];
            case 'o': return &b->fIO[fNumInputs + l.i];
            case 'A': return &b->fArrays[l.i];
            case 'c': return &b->fCond;
        }
        faustassert(false);
        return nullptr;
    }

    // The steps for the heaps of one instance: built the first time, then found again (under fMutex). The
    // bindings live as long as the compiler, that is as long as the factory's compiled block.
    Bound* bind(int* ih, REAL* rh)
    {
        std::pair<int*, REAL*> key(ih, rh);
        std::lock_guard<std::mutex> lock(fMutex);
        if (fLast && fLastKey == key) return fLast;
        auto it = fBound.find(key);
        if (it != fBound.end()) {
            fLastKey = key;
            fLast    = it->second;
            return fLast;
        }
        Bound* b = new Bound();
        b->fRealTemps.assign(fMaxTmpReal + fSaved, REAL(0));
        b->fIntTemps.assign(fMaxTmpInt + fSaved, 0);
        b->fIO.assign(fNumInputs + fNumOutputs, REAL(0));
        for (auto& d : fArrayDefs) {
            int      base = d.second.first, size = d.second.second;
            uint32_t mask = (size > 0 && (size & (size - 1)) == 0) ? uint32_t(size - 1) : 0;
            void*    p    = (d.first == 'f') ? (void*)&rh[base] : (void*)&ih[base];
            b->fArrays.push_back(ArrayRef{p, uint32_t(size), mask});
        }
        static_assert(sizeof(StepFn) == sizeof(void*), "steps assume function and data pointers of the same size");
        auto word = [](StepFn f) {
            void* w;
            memcpy(&w, &f, sizeof(w));
            return w;
        };
        for (const Instr& in : fCode) {
            b->fWords.push_back(word(fbcfpb::Ops<REAL>::fn(in.op)));
            for (const Loc& l : in.ops) b->fWords.push_back(ptr(b, ih, rh, l));
        }
        b->fWords.push_back(word(fbcfpb::Ops<REAL>::fn(fbcfpb::OP_END)));
        fBound[key] = b;
        fLastKey    = key;
        fLast       = b;
        return b;
    }

   public:
    // Compiles the block; isCompiled() says whether it worked. Nothing is bound yet.
    FBCFPBCompiler(FBCBlockInstruction<REAL>* fbc_block, soundTable& sound_table)
        : FBCExecuteFun<REAL>(fbc_block, sound_table)
    {
        try {
            compile(fbc_block);
        } catch (const Unsupported& e) {
            fCompiled = false;
            fWhy      = e.why;
        }
        if (trace()) {
            if (fCompiled) {
                std::fprintf(stderr,
                             "interp-fpb: DSP block compiled to %d steps (%d before fusion, %d fused pairs), "
                             "%d real and %d int temporaries, %d saved values, %s dispatch\n",
                             int(fCode.size()), fUnfused, fFused, fMaxTmpReal, fMaxTmpInt, fSaved,
                             FBC_FPB_TAIL ? "tail" : "call");
            } else {
                std::fprintf(stderr, "interp-fpb: DSP block not compiled (%s), the interpreter runs it\n",
                             fWhy.c_str());
            }
        }
    }

    virtual ~FBCFPBCompiler()
    {
        for (auto& it : fBound) delete it.second;
    }

    bool               isCompiled() const { return fCompiled; }
    const std::string& why() const { return fWhy; }  // why it is not compiled

    /*
     * The function to be executed each cycle: the sample loop, as the FBC loop does it (the body runs, then
     * the condition decides whether to go on). For each frame, the input samples are copied into fIO, the steps
     * run (one call with tail dispatch, which then returns nullptr; one call per step otherwise), and the
     * output samples are copied out of fIO. The steps increment the loop variable themselves.
     */
    void execute(int* int_heap, REAL* real_heap, REAL** inputs, REAL** outputs)
    {
        Bound*      b     = bind(int_heap, real_heap);
        REAL*       io    = b->fIO.data();
        const Step* first = (const Step*)b->fWords.data();
        int_heap[fLoopVar] = 0;
        do {
            int i = int_heap[fLoopVar];
            for (int c = 0; c < fNumInputs; c++) io[c] = inputs[c][i];
            for (const Step* s = first; s != nullptr; s = s->fn(s)) {
            }
            for (int c = 0; c < fNumOutputs; c++) outputs[c][i] = io[fNumInputs + c];
        } while (b->fCond);
    }
};

#endif
