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

/*
 FBC -> YDSP compiler: phase 0 prototype of ANALYSE_YDSP_JIT.md (root of the repository).

 The DSP block of an interpreter factory is translated to a YdspIrFunction (the typed, non-SSA, block-structured
 IR of YDSP, in the YUP library), optimised by YDSP's scalar passes, and compiled to machine code by YDSP's asmjit
 code generator. It is compiled in C++20 with the flags of YUP's modules, and linked with a libfaust built with
 INTERP_COMP and INTERP_YDSP_BUILD (which only sees the declaration in fbc_ydsp_compiler.hh). See README.md.

 Translation
 -----------
 FBC is a stack machine; the translator keeps a stack of YDSP value ids (for a binary instruction the value pushed
 last is the left operand). Control flow becomes YDSP blocks: kLoop is the init block, then a body block that
 kCondBranch closes with a branchIf back to it (a do-while, as the interpreter runs it); kSelectReal / kSelectInt
 and kIf are diamonds that only run the chosen branch, as the interpreter does (YDSP's if-conversion pass turns a
 diamond into a select only when both branches are speculatable). Comparisons give a YDSP bool, converted to
 int32 0 / 1 where FBC uses the result as an int.

 Memory (solution M2 of the analysis): the kernel context's scalar segment 'state' is the int heap, read and
 written with constant offsets only (loadStateI / storeStateI); the array segment 'stateArrays' is the REAL heap
 (loadStateArrayF / storeStateArrayF, a constant index for a cell, the region base and an index for an indexed
 access). An int heap access with a computed index cannot be expressed: the block is not compiled.

 Promotion (FAUST_INTERP_YDSP_PROMOTE, on by default): a heap cell accessed only with a constant offset, and
 outside every region the DSP block accesses with a computed index (the FBC indexed instructions carry the region
 size in fOffset2), lives in a YDSP value for the whole DSP block: loaded once at entry, stored back at exit if the
 block writes it. Nothing else runs on the heaps during the DSP block, so this is exact. Without promotion every
 FBC heap access is a memory access, as in the MIR compiler.

 Exactness: every operation computes what the interpreter computes. YDSP's passes run in strict mode (no fast
 math, no contraction), no vectorisation; integer +, -, * wrap (no saturation flag); real min / max are a compare
 and a select, as std::min and std::max; isnan / isinf are compares. One exception: in strict mode YDSP evaluates
 a float32 transcendental (sin, cos, tan, exp, pow, atan...) in float64 and rounds once, which is more accurate
 than the interpreter's float32 libm call and differs from it by about one ulp. So by default
 (FAUST_INTERP_YDSP_LIBMF32, on) the function is marked fastMath after the passes, for the code generator only:
 it then calls the float32 libm like the interpreter, except for exp, which it inlines as a polynomial on AArch64
 (the trace says when the DSP block has a float32 exp). Not compiled: std::remainder (kRemReal), bitcasts
 (-ftz 2), soundfiles, kBlockStore*, an int heap access with a computed index.

 Environment: FAUST_INTERP_YDSP_TRACE=1 prints what was compiled; FAUST_INTERP_YDSP_PROMOTE=0 turns promotion off;
 FAUST_INTERP_YDSP_LIBMF32=0 keeps YDSP's strict float32 transcendentals; FAUST_INTERP_YDSP_OPT=0 skips YDSP's
 optimiser.
*/

#include <yup_dsp_jit/yup_dsp_jit.h>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "fbc_ydsp_compiler.hh"

namespace {

struct Unsupported {
    std::string why;
};

bool envFlag(const char* name, bool def)
{
    const char* v = std::getenv(name);
    if (!v || !*v) return def;
    return std::strcmp(v, "0") != 0;
}

asmjit::JitRuntime& jitRuntime()
{
    static asmjit::JitRuntime runtime;
    return runtime;
}

template <class REAL>
class FBCYdspCompiler : public FBCExecuteFun<REAL> {
    using Op   = yup::YdspIrOp;
    using VT   = yup::YdspValueType;
    using Inst = yup::YdspIrInst;
    using Block = FBCBlockInstruction<REAL>;
    using Ins  = FBCBasicInstruction<REAL>;

    static constexpr VT kReal = (sizeof(REAL) == sizeof(double)) ? VT::float64Type : VT::float32Type;

    yup::YdspIrFunction fFn;
    int                 fCur = 0;
    std::vector<int>    fStack;
    std::map<int, int>  fConstInt;  // value id defined by a constI -> its value
    std::vector<int>    fLoopHeads;

    int  fCountOffset;
    bool fPromote;
    bool fOptimise;
    bool fLibmF32;

    std::map<int, int> fRealCells, fIntCells;  // promoted heap cell -> value id
    std::set<int>      fRealStored, fIntStored;

    int fMaxReal = -1, fMaxInt = -1, fNumInputs = 0, fNumOutputs = 0;

    yup::YdspKernelFn fKernel = nullptr;
    std::string       fWhy;
    bool              fExpF32   = false;  // a float32 exp in the DSP block
    int               fIrBefore = 0, fIrAfter = 0;
    size_t            fCodeSize = 0;
    double            fCompileMs = 0;

    // ------------------------------------------------------------------ IR helpers

    int newValue(VT t)
    {
        fFn.valueTypes.push_back(t);
        return int(fFn.valueTypes.size()) - 1;
    }
    VT  typeOf(int v) const { return fFn.valueTypes[size_t(v)]; }
    int newBlock()
    {
        fFn.blocks.emplace_back();
        return int(fFn.blocks.size()) - 1;
    }
    void emit(const Inst& i) { fFn.blocks[size_t(fCur)].insts.push_back(i); }
    void term(int block, yup::YdspIrTerm t, int cond = -1, int target = -1, int target2 = -1)
    {
        auto& b       = fFn.blocks[size_t(block)];
        b.term        = t;
        b.termCond    = cond;
        b.termTarget  = target;
        b.termTarget2 = target2;
    }
    int result(Op op, VT t, int a = -1, int b = -1, int c = -1, int mem = -1)
    {
        Inst i;
        i.op       = op;
        i.result   = newValue(t);
        i.a        = a;
        i.b        = b;
        i.c        = c;
        i.memIndex = mem;
        emit(i);
        return i.result;
    }
    void effect(Op op, int a = -1, int b = -1, int mem = -1)
    {
        Inst i;
        i.op       = op;
        i.a        = a;
        i.b        = b;
        i.memIndex = mem;
        emit(i);
    }
    int constReal(double v)
    {
        Inst i;
        i.op     = Op::constF;
        i.result = newValue(kReal);
        i.fvalue = double(REAL(v));
        emit(i);
        return i.result;
    }
    int constInt(int v)
    {
        Inst i;
        i.op               = Op::constI;
        i.result           = newValue(VT::int32Type);
        i.ivalue           = v;
        fConstInt[i.result] = v;
        emit(i);
        return i.result;
    }
    // FBC ints and YDSP bools: a comparison gives a bool, used as int 0 / 1 elsewhere
    int toInt(int v)
    {
        if (typeOf(v) != VT::boolType) return v;
        int one  = constInt(1);
        int zero = constInt(0);
        return result(Op::selectB, VT::int32Type, v, one, zero);
    }
    int toBool(int v)
    {
        if (typeOf(v) == VT::boolType) return v;
        return result(Op::neI, VT::boolType, toInt(v), constInt(0));
    }
    bool isConst(int v, int& c) const
    {
        auto it = fConstInt.find(v);
        if (it == fConstInt.end()) return false;
        c = it->second;
        return true;
    }

    int pop()
    {
        if (fStack.empty()) throw Unsupported{"stack underflow"};
        int v = fStack.back();
        fStack.pop_back();
        return v;
    }
    int popReal()
    {
        int v = pop();
        if (typeOf(v) != kReal) throw Unsupported{"a REAL operand of another type"};
        return v;
    }
    int  popInt() { return toInt(pop()); }
    void push(int v) { fStack.push_back(v); }

    // ------------------------------------------------------------------ heaps

    void seeReal(int off) { fMaxReal = std::max(fMaxReal, off); }
    void seeInt(int off) { fMaxInt = std::max(fMaxInt, off); }

    int loadReal(int off)
    {
        seeReal(off);
        auto it = fRealCells.find(off);
        if (it != fRealCells.end()) return result(Op::movF, kReal, it->second);
        return result(Op::loadStateArrayF, kReal, constInt(off), -1, -1, 0);
    }
    int loadInt(int off)
    {
        seeInt(off);
        auto it = fIntCells.find(off);
        if (it != fIntCells.end()) return result(Op::movI, VT::int32Type, it->second);
        return result(Op::loadStateI, VT::int32Type, off);
    }
    void storeReal(int off, int v)
    {
        seeReal(off);
        if (typeOf(v) != kReal) throw Unsupported{"a REAL store of another type"};
        auto it = fRealCells.find(off);
        if (it != fRealCells.end()) {
            Inst i;
            i.op     = Op::movF;
            i.result = it->second;
            i.a      = v;
            emit(i);
            fRealStored.insert(off);
            return;
        }
        effect(Op::storeStateArrayF, constInt(off), v, 0);
    }
    void storeInt(int off, int v)
    {
        seeInt(off);
        v       = toInt(v);
        auto it = fIntCells.find(off);
        if (it != fIntCells.end()) {
            Inst i;
            i.op     = Op::movI;
            i.result = it->second;
            i.a      = v;
            emit(i);
            fIntStored.insert(off);
            return;
        }
        effect(Op::storeStateI, v, -1, off);
    }
    void moveReal(int dst, int src) { storeReal(dst, loadReal(src)); }
    void moveInt(int dst, int src) { storeInt(dst, loadInt(src)); }

    // ------------------------------------------------------------------ promotion analysis

    struct Accesses {
        std::set<int>                    realCells, intCells;
        std::vector<std::pair<int, int>> realRegions, intRegions;  // [base, base + size)
    };

    static bool inRegions(int off, const std::vector<std::pair<int, int>>& regions)
    {
        for (auto& r : regions) {
            if (off >= r.first && off < r.first + r.second) return true;
        }
        return false;
    }

    static void collect(Block* block, Accesses& acc)
    {
        if (!block) return;
        Ins* prev = nullptr;
        for (Ins* ins : block->fInstructions) {
            int o1 = ins->fOffset1, o2 = ins->fOffset2;
            switch (ins->fOpcode) {
                case FBCInstruction::kLoadReal:
                case FBCInstruction::kStoreReal:
                case FBCInstruction::kStoreRealValue:
                    acc.realCells.insert(o1);
                    break;
                case FBCInstruction::kLoadInt:
                case FBCInstruction::kStoreInt:
                case FBCInstruction::kStoreIntValue:
                    acc.intCells.insert(o1);
                    break;
                case FBCInstruction::kMoveReal:
                    acc.realCells.insert(o1);
                    acc.realCells.insert(o2);
                    break;
                case FBCInstruction::kMoveInt:
                    acc.intCells.insert(o1);
                    acc.intCells.insert(o2);
                    break;
                case FBCInstruction::kPairMoveReal:
                case FBCInstruction::kPairMoveInt: {
                    auto& s = (ins->fOpcode == FBCInstruction::kPairMoveReal) ? acc.realCells : acc.intCells;
                    s.insert({o1, o1 - 1, o2, o2 - 1});
                    break;
                }
                case FBCInstruction::kBlockPairMoveReal:
                case FBCInstruction::kBlockPairMoveInt:
                case FBCInstruction::kBlockShiftReal:
                case FBCInstruction::kBlockShiftInt: {
                    bool  real = ins->fOpcode == FBCInstruction::kBlockPairMoveReal ||
                                ins->fOpcode == FBCInstruction::kBlockShiftReal;
                    auto& s    = real ? acc.realCells : acc.intCells;
                    for (int i = std::min(o1, o2) - 1; i <= std::max(o1, o2) + 1; i++) s.insert(i);
                    break;
                }
                case FBCInstruction::kLoadIndexedReal:
                case FBCInstruction::kStoreIndexedReal:
                case FBCInstruction::kLoadIndexedInt:
                case FBCInstruction::kStoreIndexedInt: {
                    bool real = ins->fOpcode == FBCInstruction::kLoadIndexedReal ||
                                ins->fOpcode == FBCInstruction::kStoreIndexedReal;
                    // the index is the value pushed just before: a constant when that is a kInt32Value
                    if (prev && prev->fOpcode == FBCInstruction::kInt32Value) {
                        (real ? acc.realCells : acc.intCells).insert(o1 + prev->fIntValue);
                    } else {
                        (real ? acc.realRegions : acc.intRegions).push_back({o1, o2});
                    }
                    break;
                }
                default:
                    break;
            }
            // only these own their branches: kCondBranch's branch is the loop body it jumps back to
            if (ins->fOpcode == FBCInstruction::kLoop || ins->fOpcode == FBCInstruction::kSelectReal ||
                ins->fOpcode == FBCInstruction::kSelectInt || ins->fOpcode == FBCInstruction::kIf) {
                collect(ins->fBranch1, acc);
                collect(ins->fBranch2, acc);
            }
            prev = ins;
        }
    }

    // ------------------------------------------------------------------ translation

    void unaryReal(Op op) { push(result(op, kReal, popReal())); }
    void binaryReal(Op op)
    {
        int a = popReal();
        int b = popReal();
        push(result(op, kReal, a, b));
    }
    void binaryInt(Op op)
    {
        int a = popInt();
        int b = popInt();
        push(result(op, VT::int32Type, a, b));
    }
    void compareReal(Op op)
    {
        int a = popReal();
        int b = popReal();
        push(result(op, VT::boolType, a, b));
    }
    void compareInt(Op op)
    {
        int a = popInt();
        int b = popInt();
        push(result(op, VT::boolType, a, b));
    }
    // and / or: on two bools they stay bools (no boolean xor in YDSP: xor goes through int32)
    void logic(Op intOp, Op boolOp, bool hasBoolOp)
    {
        int a = pop();
        int b = pop();
        if (hasBoolOp && typeOf(a) == VT::boolType && typeOf(b) == VT::boolType) {
            push(result(boolOp, VT::boolType, a, b));
        } else {
            int ia = toInt(a);
            int ib = toInt(b);
            push(result(intOp, VT::int32Type, ia, ib));
        }
    }

    // A diamond that runs only one branch; each branch pushes one value (select) or none (if).
    void diamond(int cond, Block* thenBlock, Block* elseBlock, bool hasValue, VT type)
    {
        int c      = toBool(cond);
        int res    = hasValue ? newValue(type) : -1;
        int head   = fCur;
        int thenB  = newBlock();
        fCur       = thenB;
        size_t depth = fStack.size();
        translate(thenBlock);
        if (hasValue) {
            int v = pop();
            v     = (type == VT::int32Type) ? toInt(v) : v;
            Inst i;
            i.op     = (type == VT::int32Type) ? Op::movI : Op::movF;
            i.result = res;
            i.a      = v;
            emit(i);
        }
        if (fStack.size() != depth) throw Unsupported{"a branch leaves values on the stack"};
        int thenEnd = fCur;
        int elseB   = newBlock();
        fCur        = elseB;
        translate(elseBlock);
        if (hasValue) {
            int v = pop();
            v     = (type == VT::int32Type) ? toInt(v) : v;
            Inst i;
            i.op     = (type == VT::int32Type) ? Op::movI : Op::movF;
            i.result = res;
            i.a      = v;
            emit(i);
        }
        if (fStack.size() != depth) throw Unsupported{"a branch leaves values on the stack"};
        int join = newBlock();
        term(head, yup::YdspIrTerm::branchIf, c, thenB, elseB);
        term(thenEnd, yup::YdspIrTerm::branch, -1, join);
        fCur = join;  // the else branch falls through into the join block
        if (hasValue) push(res);
    }

    void translate(Block* block)
    {
        if (!block) return;
        for (Ins* ins : block->fInstructions) {
            FBCInstruction::Opcode o  = ins->fOpcode;
            int                    o1 = ins->fOffset1, o2 = ins->fOffset2;
            switch (o) {
                case FBCInstruction::kRealValue:
                    push(constReal(double(ins->fRealValue)));
                    break;
                case FBCInstruction::kInt32Value:
                    push(constInt(ins->fIntValue));
                    break;

                case FBCInstruction::kLoadReal:
                    push(loadReal(o1));
                    break;
                case FBCInstruction::kLoadInt:
                    push(loadInt(o1));
                    break;
                case FBCInstruction::kStoreReal:
                    storeReal(o1, popReal());
                    break;
                case FBCInstruction::kStoreInt:
                    storeInt(o1, pop());
                    break;
                case FBCInstruction::kStoreRealValue:
                    storeReal(o1, constReal(double(ins->fRealValue)));
                    break;
                case FBCInstruction::kStoreIntValue:
                    storeInt(o1, constInt(ins->fIntValue));
                    break;

                case FBCInstruction::kMoveReal:
                    moveReal(o1, o2);
                    break;
                case FBCInstruction::kMoveInt:
                    moveInt(o1, o2);
                    break;
                case FBCInstruction::kPairMoveReal:
                    moveReal(o1, o1 - 1);
                    moveReal(o2, o2 - 1);
                    break;
                case FBCInstruction::kPairMoveInt:
                    moveInt(o1, o1 - 1);
                    moveInt(o2, o2 - 1);
                    break;
                case FBCInstruction::kBlockPairMoveReal:
                    for (int i = o1; i < o2; i += 2) moveReal(i + 1, i);
                    break;
                case FBCInstruction::kBlockPairMoveInt:
                    for (int i = o1; i < o2; i += 2) moveInt(i + 1, i);
                    break;
                case FBCInstruction::kBlockShiftReal:
                    if (o1 - o2 > 256) throw Unsupported{"a long block shift"};
                    for (int i = o1; i > o2; i -= 1) moveReal(i, i - 1);
                    break;
                case FBCInstruction::kBlockShiftInt:
                    if (o1 - o2 > 256) throw Unsupported{"a long block shift"};
                    for (int i = o1; i > o2; i -= 1) moveInt(i, i - 1);
                    break;

                case FBCInstruction::kLoadIndexedReal: {
                    int idx = popInt(), c;
                    if (isConst(idx, c)) {
                        push(loadReal(o1 + c));
                    } else {
                        seeReal(o1 + o2 - 1);
                        push(result(Op::loadStateArrayF, kReal, idx, -1, -1, o1));
                    }
                    break;
                }
                case FBCInstruction::kStoreIndexedReal: {
                    int idx = popInt(), c;
                    int v   = popReal();
                    if (isConst(idx, c)) {
                        storeReal(o1 + c, v);
                    } else {
                        seeReal(o1 + o2 - 1);
                        effect(Op::storeStateArrayF, idx, v, o1);
                    }
                    break;
                }
                case FBCInstruction::kLoadIndexedInt: {
                    int idx = popInt(), c;
                    if (!isConst(idx, c)) throw Unsupported{"an int heap access with a computed index"};
                    push(loadInt(o1 + c));
                    break;
                }
                case FBCInstruction::kStoreIndexedInt: {
                    int idx = popInt(), c;
                    int v   = pop();
                    if (!isConst(idx, c)) throw Unsupported{"an int heap access with a computed index"};
                    storeInt(o1 + c, v);
                    break;
                }

                case FBCInstruction::kLoadInput: {
                    int idx    = popInt();
                    fNumInputs = std::max(fNumInputs, o1 + 1);
                    push(result(Op::loadInput, kReal, idx, -1, -1, o1));
                    break;
                }
                case FBCInstruction::kStoreOutput: {
                    int idx     = popInt();
                    int v       = popReal();
                    fNumOutputs = std::max(fNumOutputs, o1 + 1);
                    effect(Op::storeOutput, idx, v, o1);
                    break;
                }

                case FBCInstruction::kCastReal:
                    push(result(Op::itof, kReal, popInt()));
                    break;
                case FBCInstruction::kCastInt: {
                    Inst i;
                    i.op     = Op::ftoi;
                    i.result = newValue(VT::int32Type);
                    i.a      = popReal();
                    emit(i);
                    push(i.result);
                    break;
                }

                case FBCInstruction::kAddReal: binaryReal(Op::addF); break;
                case FBCInstruction::kSubReal: binaryReal(Op::subF); break;
                case FBCInstruction::kMultReal: binaryReal(Op::mulF); break;
                case FBCInstruction::kDivReal: binaryReal(Op::divF); break;
                case FBCInstruction::kFmodf: binaryReal(Op::fmodF); break;
                case FBCInstruction::kPowf: binaryReal(Op::powF); break;
                case FBCInstruction::kAtan2f: binaryReal(Op::atan2F); break;
                case FBCInstruction::kCopysignf: binaryReal(Op::copysignF); break;
                case FBCInstruction::kMinf: {
                    // std::min(v1, v2) = (v2 < v1) ? v2 : v1
                    int v1 = popReal();
                    int v2 = popReal();
                    int lt = result(Op::ltF, VT::boolType, v2, v1);
                    push(result(Op::selectB, kReal, lt, v2, v1));
                    break;
                }
                case FBCInstruction::kMaxf: {
                    // std::max(v1, v2) = (v1 < v2) ? v2 : v1
                    int v1 = popReal();
                    int v2 = popReal();
                    int lt = result(Op::ltF, VT::boolType, v1, v2);
                    push(result(Op::selectB, kReal, lt, v2, v1));
                    break;
                }

                case FBCInstruction::kGTReal: compareReal(Op::gtF); break;
                case FBCInstruction::kLTReal: compareReal(Op::ltF); break;
                case FBCInstruction::kGEReal: compareReal(Op::geF); break;
                case FBCInstruction::kLEReal: compareReal(Op::leF); break;
                case FBCInstruction::kEQReal: compareReal(Op::eqF); break;
                case FBCInstruction::kNEReal: compareReal(Op::neF); break;

                case FBCInstruction::kAddInt: binaryInt(Op::addI); break;
                case FBCInstruction::kSubInt: binaryInt(Op::subI); break;
                case FBCInstruction::kMultInt: binaryInt(Op::mulI); break;
                case FBCInstruction::kDivInt: binaryInt(Op::divI); break;
                case FBCInstruction::kRemInt: binaryInt(Op::modI); break;
                case FBCInstruction::kLshInt: binaryInt(Op::shlI); break;
                case FBCInstruction::kARshInt: binaryInt(Op::shrI); break;
                case FBCInstruction::kLRshInt: binaryInt(Op::shrI); break;  // as the interpreter
                case FBCInstruction::kANDInt: logic(Op::andI, Op::andB, true); break;
                case FBCInstruction::kORInt: logic(Op::orI, Op::orB, true); break;
                case FBCInstruction::kXORInt: logic(Op::xorI, Op::xorI, false); break;
                case FBCInstruction::kMin: binaryInt(Op::minI); break;
                case FBCInstruction::kMax: binaryInt(Op::maxI); break;

                case FBCInstruction::kGTInt: compareInt(Op::gtI); break;
                case FBCInstruction::kLTInt: compareInt(Op::ltI); break;
                case FBCInstruction::kGEInt: compareInt(Op::geI); break;
                case FBCInstruction::kLEInt: compareInt(Op::leI); break;
                case FBCInstruction::kEQInt: compareInt(Op::eqI); break;
                case FBCInstruction::kNEInt: compareInt(Op::neI); break;

                case FBCInstruction::kAbs: push(result(Op::absI, VT::int32Type, popInt())); break;
                case FBCInstruction::kAbsf: unaryReal(Op::absF); break;
                case FBCInstruction::kAcosf: unaryReal(Op::acosF); break;
                case FBCInstruction::kAcoshf: unaryReal(Op::acoshF); break;
                case FBCInstruction::kAsinf: unaryReal(Op::asinF); break;
                case FBCInstruction::kAsinhf: unaryReal(Op::asinhF); break;
                case FBCInstruction::kAtanf: unaryReal(Op::atanF); break;
                case FBCInstruction::kAtanhf: unaryReal(Op::atanhF); break;
                case FBCInstruction::kCeilf: unaryReal(Op::ceilF); break;
                case FBCInstruction::kCosf: unaryReal(Op::cosF); break;
                case FBCInstruction::kCoshf: unaryReal(Op::coshF); break;
                case FBCInstruction::kExpf:
                    fExpF32 = fExpF32 || kReal == VT::float32Type;
                    unaryReal(Op::expF);
                    break;
                case FBCInstruction::kFloorf: unaryReal(Op::floorF); break;
                case FBCInstruction::kLogf: unaryReal(Op::logF); break;
                case FBCInstruction::kLog10f: unaryReal(Op::log10F); break;
                case FBCInstruction::kRintf: unaryReal(Op::rintF); break;
                case FBCInstruction::kRoundf: unaryReal(Op::roundF); break;
                case FBCInstruction::kSinf: unaryReal(Op::sinF); break;
                case FBCInstruction::kSinhf: unaryReal(Op::sinhF); break;
                case FBCInstruction::kSqrtf: unaryReal(Op::sqrtF); break;
                case FBCInstruction::kTanf: unaryReal(Op::tanF); break;
                case FBCInstruction::kTanhf: unaryReal(Op::tanhF); break;
                case FBCInstruction::kIsnanf: {
                    int v = popReal();
                    push(result(Op::neF, VT::boolType, v, v));
                    break;
                }
                case FBCInstruction::kIsinff: {
                    int v   = popReal();
                    int a   = result(Op::absF, kReal, v);
                    int inf = constReal(std::numeric_limits<double>::infinity());
                    push(result(Op::eqF, VT::boolType, a, inf));
                    break;
                }

                case FBCInstruction::kSelectReal:
                    diamond(pop(), ins->fBranch1, ins->fBranch2, true, kReal);
                    break;
                case FBCInstruction::kSelectInt:
                    diamond(pop(), ins->fBranch1, ins->fBranch2, true, VT::int32Type);
                    break;
                case FBCInstruction::kIf:
                    diamond(pop(), ins->fBranch1, ins->fBranch2, false, VT::int32Type);
                    break;

                case FBCInstruction::kLoop: {
                    translate(ins->fBranch1);  // init, in the current block
                    int body = newBlock();     // the current block falls through into it
                    fCur     = body;
                    fLoopHeads.push_back(body);
                    translate(ins->fBranch2);  // ends with kCondBranch
                    fLoopHeads.pop_back();
                    break;
                }
                case FBCInstruction::kCondBranch: {
                    if (fLoopHeads.empty()) throw Unsupported{"a kCondBranch outside a loop"};
                    int c    = toBool(pop());
                    int from = fCur;
                    int next = newBlock();
                    term(from, yup::YdspIrTerm::branchIf, c, fLoopHeads.back(), next);
                    fCur = next;
                    return;  // the end of the loop body
                }
                case FBCInstruction::kReturn:
                    return;

                default:
                    throw Unsupported{std::string("FBC instruction ") + gFBCInstructionTable[o]};
            }
        }
    }

    // ------------------------------------------------------------------ optimisation (YDSP's scalar passes)

    // The order of YdspOptimizer::runPasses (private in YUP), with what is off here left out: loop fusion,
    // vectorisation, unrolling, reduction splitting and contraction. LICM needs YdspIrLoop records, which this
    // translator does not build: promotion already keeps the loop-invariant heap cells in values.
    void optimise()
    {
        yup::YdspDiagnostics diagnostics;
        yup::YdspOptimizer   opt(diagnostics);
        opt.setFastMath(false);
        opt.setContractionEnabled(false);
        opt.setVectorizationEnabled(false);
        opt.setUnrollingEnabled(false);
        opt.setReductionSplittingEnabled(false);
        fFn.fastMath           = false;
        fFn.vectorMathEnabled  = false;
        fFn.packedFmaAvailable = false;
        for (int i = 0; i < 4; ++i) {
            bool changed = opt.constantFolding(fFn);
            changed |= opt.algebraicSimplification(fFn);
            changed |= opt.ifConversion(fFn);
            changed |= opt.storeToLoadForwarding(fFn);
            changed |= opt.copyPropagation(fFn);
            changed |= opt.eliminateProvenBoundsChecks(fFn);
            changed |= opt.commonSubexpressionElimination(fFn);
            changed |= opt.deadCodeElimination(fFn);
            if (!changed) break;
        }
        opt.commonSubexpressionElimination(fFn);
        opt.deadCodeElimination(fFn);
        opt.foldStateWriteBacks(fFn);
        opt.rematerializePostCallLeaves(fFn);
        opt.deadCodeElimination(fFn);
        opt.removeUnreachableBlocks(fFn);
        if (diagnostics.hasErrors()) throw Unsupported{"YDSP optimiser: " + diagnostics.toString().toStdString()};
    }

    void compile(Block* block)
    {
        auto t0 = std::chrono::steady_clock::now();

        fFn.name         = "faust_dsp_block";
        fFn.isSampleMode = false;
        fCur             = newBlock();

        if (fPromote) {
            Accesses acc;
            collect(block, acc);
            for (int off : acc.realCells) {
                if (off >= 0 && !inRegions(off, acc.realRegions)) {
                    fRealCells[off] = result(Op::loadStateArrayF, kReal, constInt(off), -1, -1, 0);
                    seeReal(off);
                }
            }
            for (int off : acc.intCells) {
                if (off >= 0 && !inRegions(off, acc.intRegions)) {
                    fIntCells[off] = result(Op::loadStateI, VT::int32Type, off);
                    seeInt(off);
                }
            }
        }

        translate(block);
        if (!fStack.empty()) throw Unsupported{"the DSP block leaves values on the stack"};

        // store the promoted cells the block writes
        for (int off : fRealStored) effect(Op::storeStateArrayF, constInt(off), fRealCells[off], 0);
        for (int off : fIntStored) effect(Op::storeStateI, fIntCells[off], -1, off);

        fFn.numInputs  = fNumInputs;
        fFn.numOutputs = fNumOutputs;
        fFn.inputTypes.assign(size_t(fNumInputs), kReal);
        fFn.outputTypes.assign(size_t(fNumOutputs), kReal);
        // Region offsets only depend on the counts of the regions before them: f32 and i32 come first, so with
        // the int heap as i32 scalars and the REAL heap as f32 or f64 array elements, both start at offset 0.
        fFn.int32Scalars = fMaxInt + 1;
        if (kReal == VT::float32Type) {
            fFn.float32ArrayElements = fMaxReal + 1;
        } else {
            fFn.float64ArrayElements = fMaxReal + 1;
        }

        fIrBefore = fFn.getInstructionCount();
        if (fOptimise) optimise();
        fIrAfter = fFn.getInstructionCount();

        // In strict mode YDSP's code generator evaluates a float32 transcendental in float64 and rounds once
        // (more accurate than the float32 libm, but not what the interpreter computes). fastMath on the function,
        // set after the passes ran in strict mode, makes it call the float32 libm like the interpreter; it also
        // inlines a polynomial exp on AArch64 (scalar float32 only): fExpF32 tells it. On by default;
        // FAUST_INTERP_YDSP_LIBMF32=0 keeps YDSP's strict mode.
        if (fLibmF32) fFn.fastMath = true;

        yup::YdspDiagnostics diagnostics;
        fKernel = yup::YdspAsmJitCodegen::compile(jitRuntime(), fFn, diagnostics, &fCodeSize);
        if (!fKernel) throw Unsupported{"YDSP code generation: " + diagnostics.toString().toStdString()};

        fCompileMs = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
    }

   public:
    FBCYdspCompiler(Block* block, soundTable& sound_table, int count_offset)
        : FBCExecuteFun<REAL>(block, sound_table),
          fCountOffset(count_offset),
          fPromote(envFlag("FAUST_INTERP_YDSP_PROMOTE", true)),
          fOptimise(envFlag("FAUST_INTERP_YDSP_OPT", true)),
          fLibmF32(envFlag("FAUST_INTERP_YDSP_LIBMF32", true))
    {
        try {
            compile(block);
        } catch (const Unsupported& e) {
            fKernel = nullptr;
            fWhy    = e.why;
        }
        if (envFlag("FAUST_INTERP_YDSP_TRACE", false)) {
            if (fKernel) {
                std::fprintf(stderr,
                             "interp-ydsp: DSP block compiled to %zu bytes of machine code (%d IR instructions, %d "
                             "before optimisation, %zu blocks), %zu real and %zu int heap cells promoted, %.2f ms%s\n",
                             fCodeSize, fIrAfter, fIrBefore, fFn.blocks.size(), fRealCells.size(), fIntCells.size(),
                             fCompileMs,
                             !fLibmF32 ? ", strict libm (float32 transcendentals in float64)"
                             : fExpF32 ? ", float32 exp inlined by YDSP (not the interpreter's expf)" : "");
            } else {
                std::fprintf(stderr, "interp-ydsp: DSP block not compiled (%s), the interpreter runs it\n",
                             fWhy.c_str());
            }
        }
    }

    virtual ~FBCYdspCompiler()
    {
        if (fKernel) jitRuntime().release(fKernel);
    }

    bool isCompiled() const { return fKernel != nullptr; }

    void execute(int* int_heap, REAL* real_heap, REAL** inputs, REAL** outputs)
    {
        yup::YdspKernelContext ctx;
        ctx.inputs      = reinterpret_cast<void* const*>(inputs);
        ctx.outputs     = reinterpret_cast<void* const*>(outputs);
        ctx.state       = int_heap;
        ctx.stateArrays = real_heap;
        ctx.numSamples  = int_heap[fCountOffset];
        fKernel(&ctx);
    }
};

}  // namespace

template <class REAL>
FBCExecuteFun<REAL>* createFBCYdspCompiler(FBCBlockInstruction<REAL>* block, soundTable& sound_table,
                                           int count_offset)
{
    auto* c = new FBCYdspCompiler<REAL>(block, sound_table, count_offset);
    if (c->isCompiled()) return c;
    delete c;
    return nullptr;
}

template FBCExecuteFun<float>*  createFBCYdspCompiler<float>(FBCBlockInstruction<float>*, soundTable&, int);
template FBCExecuteFun<double>* createFBCYdspCompiler<double>(FBCBlockInstruction<double>*, soundTable&, int);
