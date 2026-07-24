/************************************************************************
 ************************************************************************
    FAUST signal library
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

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "FaustAlgebra.hh"
#include "binop.hh"
#include "fixpoint.hh"
#include "prim2.hh"
#include "sigOpcode.hh"
#include "signals.hh"
#include "tlib.hh"
#include "xtended.hh"

/**
 * The adapter between signal trees and a semantic algebra.
 *
 * This is the `SignalInterpreter` layer of FAUSTALGEBRA.md: it is the only place that
 * knows both `Tree` and the algebra. It carries THE dense switch over signal
 * constructors -- written once, shared by every attribute (nature, variability, ...,
 * and eventually the interval) instead of being re-derived as a chain of `isSigXXX`
 * tests in each one.
 *
 * A SignalAlgebra is both:
 *   - a FixPointDomain, which is what the fixpoint iterators require, and
 *   - a FaustAlgebra, which is the exhaustive list of the operations to implement.
 *
 * The junction lives HERE rather than in FaustAlgebra itself, because FixPointDomain is
 * intrinsically tree-aware (`combine`, `bottom(Tree var)`, `widen(Tree var, ...)`) and
 * lives in tlib. Making FaustAlgebra derive from it would drag tlib into the standalone
 * `interval` library, whose `interval_algebra : FaustAlgebra<interval>` is built without
 * it -- exactly the dependency the migration removed.
 *
 * Concrete algebras derive from SignalAlgebra<V> and implement every operation. Nothing
 * is defaulted: a constructor left unhandled is a compile error, not a silent join.
 */
template <typename V>
class SignalAlgebra : public FixPointDomain<V>, public FaustAlgebra<V> {
   public:
    V combine(Tree sig, const std::vector<V>& c, FixPointEvaluator<V>& ev) const override;

    //----------------------------------------------------------------------------------
    // Constructors of the SIGNAL language that FaustAlgebra does not name.
    //
    // FaustAlgebra is the numeric/semantic core shared with interval_algebra; these have
    // no meaning there. Documentation tables belong to the documentation generator, and
    // registers and tuples are compiler-internal.
    //----------------------------------------------------------------------------------
    /// A READ-ONLY table: `sigWRTbl` whose write index is nil. FaustAlgebra names only
    /// the writable form, but the two are distinct constructors -- and the difference is
    /// structural, legible in the tree and not in any value, so it is resolved here
    /// rather than pushed onto the algebra as a flag to re-derive.
    virtual V Table(const V& size, const V& content) const = 0;

    virtual V DocConstantTbl(const V& n, const V& sig) const = 0;
    virtual V DocWriteTbl(const V& n, const V& sig, const V& widx, const V& wsig) const = 0;
    virtual V DocAccessTbl(const V& tbl, const V& ridx) const = 0;
    virtual V Register(int n, const V& s) const = 0;
    virtual V Tuple(int mode, const std::vector<V>& ls) const = 0;
    virtual V TupleAccess(const V& ts, const V& idx) const = 0;

   protected:
    SignalAlgebra() : fSignalSignature(sigs::signalSignature()) {}

   private:
    /// Hoisted out of the walk: signalOpcode() would otherwise hit the symbol registry
    /// on every node. Captured at construction, which is inside one TLIB session.
    Signature fSignalSignature;

    V unreachable(const char* what) const
    {
        tlib::error(std::string("ASSERT : SignalAlgebra never calls FaustAlgebra::") + what +
                    " (see the payload-carrying variant)\n");
        return V{};
    }

    V binaryOp(int op, const V& x, const V& y) const;
    V xtendedOp(xtended* p, const std::vector<V>& c) const;
};

//--------------------------------------------------------------------------------------
// The 17 binary operators of the signal language.
//--------------------------------------------------------------------------------------
template <typename V>
V SignalAlgebra<V>::binaryOp(int op, const V& x, const V& y) const
{
    switch (op) {
        case kAdd: return this->Add(x, y);
        case kSub: return this->Sub(x, y);
        case kMul: return this->Mul(x, y);
        case kDiv: return this->Div(x, y);
        case kRem: return this->Mod(x, y);
        case kLsh: return this->Lsh(x, y);
        case kARsh: return this->ARsh(x, y);
        case kLRsh: return this->LRsh(x, y);
        case kGT: return this->Gt(x, y);
        case kLT: return this->Lt(x, y);
        case kGE: return this->Ge(x, y);
        case kLE: return this->Le(x, y);
        case kEQ: return this->Eq(x, y);
        case kNE: return this->Ne(x, y);
        case kAND: return this->And(x, y);
        case kOR: return this->Or(x, y);
        case kXOR: return this->Xor(x, y);
        default: return unreachable("binaryOp (unknown SOperator)");
    }
}

//--------------------------------------------------------------------------------------
// The extended primitives.
//
// They live outside every signature -- an xtended attaches itself to an ordinary symbol
// through user data -- so they are dispatched by NAME, which is the Faust primitive name
// and therefore part of the language rather than of any one build. The 22 names below
// are the complete set registered by the compiler.
//--------------------------------------------------------------------------------------
template <typename V>
V SignalAlgebra<V>::xtendedOp(xtended* p, const std::vector<V>& c) const
{
    enum class XOp {
        Abs, Acos, Asin, Atan, Atan2, Ceil, Cos, Exp, Exp10, Floor, Fmod, Log, Log10,
        Max, Min, Pow, Remainder, Rint, Round, Sin, Sqrt, Tan
    };
    static const std::unordered_map<std::string, XOp> kTable = {
        {"abs", XOp::Abs},         {"acos", XOp::Acos},   {"asin", XOp::Asin},
        {"atan", XOp::Atan},       {"atan2", XOp::Atan2}, {"ceil", XOp::Ceil},
        {"cos", XOp::Cos},         {"exp", XOp::Exp},     {"exp10", XOp::Exp10},
        {"floor", XOp::Floor},     {"fmod", XOp::Fmod},   {"log", XOp::Log},
        {"log10", XOp::Log10},     {"max", XOp::Max},     {"min", XOp::Min},
        {"pow", XOp::Pow},         {"remainder", XOp::Remainder},
        {"rint", XOp::Rint},       {"round", XOp::Round}, {"sin", XOp::Sin},
        {"sqrt", XOp::Sqrt},       {"tan", XOp::Tan},
    };

    auto it = kTable.find(p->sname());
    if (it == kTable.end()) {
        return unreachable((std::string("xtendedOp : unknown primitive ") + p->name()).c_str());
    }
    switch (it->second) {
        case XOp::Abs: return this->Abs(c[0]);
        case XOp::Acos: return this->Acos(c[0]);
        case XOp::Asin: return this->Asin(c[0]);
        case XOp::Atan: return this->Atan(c[0]);
        case XOp::Atan2: return this->Atan2(c[0], c[1]);
        case XOp::Ceil: return this->Ceil(c[0]);
        case XOp::Cos: return this->Cos(c[0]);
        case XOp::Exp: return this->Exp(c[0]);
        case XOp::Exp10: return this->Exp10(c[0]);
        case XOp::Floor: return this->Floor(c[0]);
        case XOp::Fmod: return this->Mod(c[0], c[1]);
        case XOp::Log: return this->Log(c[0]);
        case XOp::Log10: return this->Log10(c[0]);
        case XOp::Max: return this->Max(c[0], c[1]);
        case XOp::Min: return this->Min(c[0], c[1]);
        case XOp::Pow: return this->Pow(c[0], c[1]);
        case XOp::Remainder: return this->Remainder(c[0], c[1]);
        case XOp::Rint: return this->Rint(c[0]);
        case XOp::Round: return this->Round(c[0]);
        case XOp::Sin: return this->Sin(c[0]);
        case XOp::Sqrt: return this->Sqrt(c[0]);
        case XOp::Tan: return this->Tan(c[0]);
    }
    return unreachable("xtendedOp");
}

//--------------------------------------------------------------------------------------
// THE dense switch.
//
// The iterator handles rec / ref / proj itself, so combine never sees them. Everything
// else a walk of a signal term meets is routed here.
//--------------------------------------------------------------------------------------
template <typename V>
V SignalAlgebra<V>::combine(Tree sig, const std::vector<V>& c,
                            FixPointEvaluator<V>& ev) const
{
    int     i;
    int64_t i64;
    double  r;
    Tree    x, y, z, u, label, cur, lo, hi, step, type, name, file, ff, ls;

    // Extended primitives first: they head ordinary symbols, outside every signature.
    if (void* ud = getUserData(sig)) {
        return xtendedOp(static_cast<xtended*>(ud), c);
    }

    // Numeric leaves. A signal constant IS a bare numeric tree, so this also covers the
    // non-signal integer leaves a walk meets (a binop's opcode, a register's index).
    if (isSigInt(sig, &i)) return this->IntNum(i);
    if (isSigInt64(sig, &i64)) return this->Int64Num(i64);
    if (isSigReal(sig, &r)) return this->FloatNum(r);

    sigs::SignalOpcode op;
    if (sigs::signalOpcode(sig, fSignalSignature, op)) {
        switch (op) {
            case sigs::SignalOpcode::Input: return this->Input(c[0]);
            case sigs::SignalOpcode::Output: return this->Output(c[0], c[1]);
            case sigs::SignalOpcode::Delay1: return this->Mem(c[0]);
            case sigs::SignalOpcode::Delay: return this->Delay(c[0], c[1]);
            case sigs::SignalOpcode::Prefix: return this->Prefix(c[0], c[1]);
            case sigs::SignalOpcode::ReadTable: return this->RDTbl(c[0], c[1]);
            case sigs::SignalOpcode::WriteTable:
                isSigWRTbl(sig, x, y, z, u);
                return (z == ::nil()) ? this->Table(c[0], c[1])
                                      : this->WRTbl(c[0], c[1], c[2], c[3]);
            case sigs::SignalOpcode::Generator: return this->Gen(c[0]);
            case sigs::SignalOpcode::DocConstantTable: return this->DocConstantTbl(c[0], c[1]);
            case sigs::SignalOpcode::DocWriteTable:
                return this->DocWriteTbl(c[0], c[1], c[2], c[3]);
            case sigs::SignalOpcode::DocAccessTable: return this->DocAccessTbl(c[0], c[1]);
            case sigs::SignalOpcode::Select2: return this->Select2(c[0], c[1], c[2]);
            case sigs::SignalOpcode::AssertBounds:
                return this->AssertBounds(c[0], c[1], c[2]);
            case sigs::SignalOpcode::Highest: return this->Highest(c[0]);
            case sigs::SignalOpcode::Lowest: return this->Lowest(c[0]);

            case sigs::SignalOpcode::BinOp:
                // branch 0 is the opcode leaf, not a signal
                isSigBinOp(sig, &i, x, y);
                return binaryOp(i, c[1], c[2]);

            case sigs::SignalOpcode::ForeignFunction: {
                isSigFFun(sig, ff, ls);
                std::vector<V> args;
                for (Tree l = ls; isList(l); l = tl(l)) {
                    args.push_back(ev.eval(hd(l)));
                }
                return this->ForeignFunction(ffrestype(ff), args);
            }
            case sigs::SignalOpcode::ForeignConstant:
                isSigFConst(sig, type, name, file);
                return this->ForeignConst(tree2int(type), c[1], c[2]);
            case sigs::SignalOpcode::ForeignVariable:
                isSigFVar(sig, type, name, file);
                return this->ForeignVar(tree2int(type), c[1], c[2]);

            case sigs::SignalOpcode::IntCast: return this->IntCast(c[0]);
            case sigs::SignalOpcode::BitCast: return this->BitCast(c[0]);
            case sigs::SignalOpcode::FloatCast: return this->FloatCast(c[0]);
            case sigs::SignalOpcode::Button: return this->Button(c[0]);
            case sigs::SignalOpcode::Checkbox: return this->Checkbox(c[0]);
            case sigs::SignalOpcode::Waveform: return this->Waveform(c);

            // The three range widgets keep their four range signals in a NESTED list, so
            // the node has two branches while the operation takes five arguments. This is
            // what the evaluator is for.
            case sigs::SignalOpcode::HSlider:
                isSigHSlider(sig, label, cur, lo, hi, step);
                return this->HSlider(c[0], ev.eval(cur), ev.eval(lo), ev.eval(hi),
                                     ev.eval(step));
            case sigs::SignalOpcode::VSlider:
                isSigVSlider(sig, label, cur, lo, hi, step);
                return this->VSlider(c[0], ev.eval(cur), ev.eval(lo), ev.eval(hi),
                                     ev.eval(step));
            case sigs::SignalOpcode::NumEntry:
                isSigNumEntry(sig, label, cur, lo, hi, step);
                return this->NumEntry(c[0], ev.eval(cur), ev.eval(lo), ev.eval(hi),
                                      ev.eval(step));

            case sigs::SignalOpcode::HBargraph:
                return this->HBargraph(c[0], c[1], c[2], c[3]);
            case sigs::SignalOpcode::VBargraph:
                return this->VBargraph(c[0], c[1], c[2], c[3]);
            case sigs::SignalOpcode::Attach: return this->Attach(c[0], c[1]);
            case sigs::SignalOpcode::Enable: return this->Enable(c[0], c[1]);
            case sigs::SignalOpcode::Control: return this->Control(c[0], c[1]);
            case sigs::SignalOpcode::Soundfile: return this->SoundFile(c[0]);
            case sigs::SignalOpcode::SoundfileLength:
                return this->SoundFileLength(c[0], c[1]);
            case sigs::SignalOpcode::SoundfileRate: return this->SoundFileRate(c[0], c[1]);
            case sigs::SignalOpcode::SoundfileBuffer:
                return this->SoundFileBuffer(c[0], c[1], c[2], c[3]);

            case sigs::SignalOpcode::Register:
                isSigRegister(sig, &i, x);
                return this->Register(i, c[1]);
            case sigs::SignalOpcode::Tuple:
                isSigTuple(sig, &i, ls);
                return this->Tuple(i, c);
            case sigs::SignalOpcode::TupleAccess: return this->TupleAccess(c[0], c[1]);

            case sigs::SignalOpcode::Count: break;  // not a constructor
        }
        return unreachable("combine (signal opcode out of range)");
    }

    // Everything left is syntax rather than signal: labels, identifiers, list spines,
    // foreign-function signatures. Their value is never consumed -- the constructors that
    // need what they hold read it as data -- but the walk still reaches them.
    Sym s;
    if (isSym(sig->node(), &s) && sig->arity() == 0) {
        return this->Label(::name(s));
    }
    return this->Nil();
}
