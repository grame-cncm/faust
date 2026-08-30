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

#include "sigs-export.hh"
#include "sigs-state.hh"
#include "signalAlgebra.hh"

/**
 * THE INITIAL ALGEBRA: the interpretation whose carrier is the signal tree itself.
 *
 * Every operation builds the corresponding node, so rebuilding a term through
 * TreeAlgebra is the identity -- up to alpha-renaming, since the rebuild driver gives
 * every recursive group a FRESH variable (the immutability protocol: a definition is
 * written once, never redefined). On a rec-free term the rebuild is pointer-EQUAL,
 * hash-consing collapsing the reconstruction.
 *
 * This is the base class of tree TRANSFORMATIONS: a transformation derives from
 * TreeAlgebra and overrides the operations it cares about -- it never walks trees,
 * never handles recursion, never manages a memo; the driver does.
 *
 * TreeAlgebra derives from SignalDispatch<Tree>, NOT SignalAlgebra<Tree>: rebuilding
 * is not a fixpoint, the tree carrier has no lattice.
 *
 * CONSTRUCTION IS DIRECT AND PURE: the operations build their nodes from the interned
 * signal symbols, not through the legacy sigXXX constructors -- this class is meant to
 * REPLACE them, and three of them are not even plain constructors (sigIntCast and
 * sigFloatCast fold constants, sigRem raises on a constant zero divisor). Those
 * behaviors belong to DERIVED algebras (a normalizing one) and to the diagnostics,
 * never to the initial algebra: here, what you ask is what gets built.
 */
class SIGS_API TreeAlgebra : public SignalDispatch<Tree> {
   public:
    //--- injections -------------------------------------------------------------------
    Tree IntNum(int x) const override { return tree(x); }
    Tree Int64Num(int64_t x) const override { return tree(x); }
    Tree FloatNum(double x) const override { return tree(x); }
    Tree Label(const std::string& s) const override { return tree(s.c_str()); }

    //--- engine hook (identity: keep the fresh value) ---------------------------------
    Tree FixPointUpdate(const Tree&, const Tree& y) const override { return y; }

    //--- input / output ---------------------------------------------------------------
    Tree Input(const Tree& chan) const override { return tree(sigs::g.SIGINPUT, chan); }
    Tree Output(const Tree& chan, const Tree& x) const override
    {
        return tree(sigs::g.SIGOUTPUT, chan, x);
    }

    //--- user interface ---------------------------------------------------------------
    Tree Button(const Tree& name) const override { return tree(sigs::g.SIGBUTTON, name); }
    Tree Checkbox(const Tree& name) const override { return tree(sigs::g.SIGCHECKBOX, name); }
    Tree VSlider(const Tree& n, const Tree& i, const Tree& lo, const Tree& hi,
                 const Tree& st) const override
    {
        return tree(sigs::g.SIGVSLIDER, n, list4(i, lo, hi, st));
    }
    Tree HSlider(const Tree& n, const Tree& i, const Tree& lo, const Tree& hi,
                 const Tree& st) const override
    {
        return tree(sigs::g.SIGHSLIDER, n, list4(i, lo, hi, st));
    }
    Tree NumEntry(const Tree& n, const Tree& i, const Tree& lo, const Tree& hi,
                  const Tree& st) const override
    {
        return tree(sigs::g.SIGNUMENTRY, n, list4(i, lo, hi, st));
    }
    Tree HBargraph(const Tree& n, const Tree& lo, const Tree& hi,
                   const Tree& s) const override
    {
        return tree(sigs::g.SIGHBARGRAPH, n, lo, hi, s);
    }
    Tree VBargraph(const Tree& n, const Tree& lo, const Tree& hi,
                   const Tree& s) const override
    {
        return tree(sigs::g.SIGVBARGRAPH, n, lo, hi, s);
    }
    Tree Attach(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGATTACH, x, y); }
    Tree Enable(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGENABLE, x, y); }
    Tree Control(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGCONTROL, x, y); }

    //--- time and memory --------------------------------------------------------------
    Tree Mem(const Tree& x) const override { return tree(sigs::g.SIGDELAY1, x); }
    Tree Delay(const Tree& x, const Tree& n) const override { return tree(sigs::g.SIGDELAY, x, n); }
    Tree Prefix(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGPREFIX, x, y); }

    //--- casts ------------------------------------------------------------------------
    Tree IntCast(const Tree& x) const override { return tree(sigs::g.SIGINTCAST, x); }
    Tree BitCast(const Tree& x) const override { return tree(sigs::g.SIGBITCAST, x); }
    Tree FloatCast(const Tree& x) const override { return tree(sigs::g.SIGFLOATCAST, x); }

    //--- foreign ----------------------------------------------------------------------
    Tree ForeignConst(int t, const Tree& name, const Tree& file) const override
    {
        return tree(sigs::g.SIGFCONST, tree(t), name, file);
    }
    Tree ForeignVar(int t, const Tree& name, const Tree& file) const override
    {
        return tree(sigs::g.SIGFVAR, tree(t), name, file);
    }
    /// Unreachable: the ffunction node embeds its whole signature (name, argument
    /// types, include files) while this operation only carries the return type, so the
    /// node cannot be rebuilt through it. The driver passes ffunction applications
    /// through STRUCTURALLY -- and this asymmetry is a recorded candidate for a
    /// signature evolution (carry the signature as data, like ForeignConst does).
    Tree ForeignFunction(int, const std::vector<Tree>&) const override
    {
        tlib::error(
            "ASSERT : TreeAlgebra::ForeignFunction -- the driver rebuilds ffunction "
            "applications structurally\n");
        return nullptr;
    }

    //--- tables, waveforms, soundfiles ------------------------------------------------
    Tree Table(const Tree& size, const Tree& content) const override
    {
        return tree(sigs::g.SIGWRTBL, size, content, ::nil(), ::nil());
    }
    Tree WRTbl(const Tree& size, const Tree& gen, const Tree& wi,
               const Tree& ws) const override
    {
        return tree(sigs::g.SIGWRTBL, size, gen, wi, ws);
    }
    Tree RDTbl(const Tree& tbl, const Tree& ri) const override { return tree(sigs::g.SIGRDTBL, tbl, ri); }
    Tree Gen(const Tree& x) const override { return tree(sigs::g.SIGGEN, x); }
    Tree DocConstantTbl(const Tree& n, const Tree& init) const override
    {
        return tree(sigs::g.SIGDOCONSTANTTBL, n, init);
    }
    Tree DocWriteTbl(const Tree& n, const Tree& init, const Tree& wi,
                     const Tree& ws) const override
    {
        return tree(sigs::g.SIGDOCWRITETBL, n, init, wi, ws);
    }
    Tree DocAccessTbl(const Tree& tbl, const Tree& ri) const override
    {
        return tree(sigs::g.SIGDOCACCESSTBL, tbl, ri);
    }
    Tree Register(int n, const Tree& s) const override { return tree(sigs::g.SIGREGISTER, tree(n), s); }
    Tree Waveform(const std::vector<Tree>& w) const override
    {
        return tree(sigs::g.SIGWAVEFORM, tvec(w.begin(), w.end()));
    }
    Tree SoundFile(const Tree& label) const override { return tree(sigs::g.SIGSOUNDFILE, label); }
    Tree SoundFileLength(const Tree& sf, const Tree& part) const override
    {
        return tree(sigs::g.SIGSOUNDFILELENGTH, sf, part);
    }
    Tree SoundFileRate(const Tree& sf, const Tree& part) const override
    {
        return tree(sigs::g.SIGSOUNDFILERATE, sf, part);
    }
    Tree SoundFileBuffer(const Tree& sf, const Tree& chan, const Tree& part,
                         const Tree& ri) const override
    {
        return tree(sigs::g.SIGSOUNDFILEBUFFER, sf, chan, part, ri);
    }

    //--- selection and bounds ---------------------------------------------------------
    Tree Select2(const Tree& sel, const Tree& x, const Tree& y) const override
    {
        return tree(sigs::g.SIGSELECT2, sel, x, y);
    }
    Tree AssertBounds(const Tree& lo, const Tree& hi, const Tree& x) const override
    {
        return tree(sigs::g.SIGASSERTBOUNDS, lo, hi, x);
    }
    Tree Highest(const Tree& x) const override { return tree(sigs::g.SIGHIGHEST, x); }
    Tree Lowest(const Tree& x) const override { return tree(sigs::g.SIGLOWEST, x); }

    //--- the 17 binary operators ------------------------------------------------------
    Tree Add(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kAdd), x, y); }
    Tree Sub(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kSub), x, y); }
    Tree Mul(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kMul), x, y); }
    Tree Div(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kDiv), x, y); }
    Tree Mod(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kRem), x, y); }
    Tree Lsh(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kLsh), x, y); }
    Tree ARsh(const Tree& x, const Tree& y) const override
    {
        return tree(sigs::g.SIGBINOP, tree(kARsh), x, y);
    }
    Tree LRsh(const Tree& x, const Tree& y) const override
    {
        return tree(sigs::g.SIGBINOP, tree(kLRsh), x, y);
    }
    Tree Gt(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kGT), x, y); }
    Tree Lt(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kLT), x, y); }
    Tree Ge(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kGE), x, y); }
    Tree Le(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kLE), x, y); }
    Tree Eq(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kEQ), x, y); }
    Tree Ne(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kNE), x, y); }
    Tree And(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kAND), x, y); }
    Tree Or(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kOR), x, y); }
    Tree Xor(const Tree& x, const Tree& y) const override { return tree(sigs::g.SIGBINOP, tree(kXOR), x, y); }

    //--- extended primitives ----------------------------------------------------------
    // Rebuilt from the xtended itself (see xtendedOp below): one override covers the 22
    // primitives and disambiguates the shared interpretations (fmod vs %). The
    // per-operation methods below are therefore only reached when a DERIVED
    // transformation builds a primitive EX NIHILO; they construct by primitive name.
    Tree Abs(const Tree& x) const override { return xt("abs", {x}); }
    Tree Acos(const Tree& x) const override { return xt("acos", {x}); }
    Tree Asin(const Tree& x) const override { return xt("asin", {x}); }
    Tree Atan(const Tree& x) const override { return xt("atan", {x}); }
    Tree Atan2(const Tree& x, const Tree& y) const override { return xt("atan2", {x, y}); }
    Tree Ceil(const Tree& x) const override { return xt("ceil", {x}); }
    Tree Cos(const Tree& x) const override { return xt("cos", {x}); }
    Tree Exp(const Tree& x) const override { return xt("exp", {x}); }
    Tree Exp10(const Tree& x) const override { return xt("exp10", {x}); }
    Tree Floor(const Tree& x) const override { return xt("floor", {x}); }
    Tree Log(const Tree& x) const override { return xt("log", {x}); }
    Tree Log10(const Tree& x) const override { return xt("log10", {x}); }
    Tree Max(const Tree& x, const Tree& y) const override { return xt("max", {x, y}); }
    Tree Min(const Tree& x, const Tree& y) const override { return xt("min", {x, y}); }
    Tree Pow(const Tree& x, const Tree& y) const override { return xt("pow", {x, y}); }
    Tree Remainder(const Tree& x, const Tree& y) const override
    {
        return xt("remainder", {x, y});
    }
    Tree Rint(const Tree& x) const override { return xt("rint", {x}); }
    Tree Round(const Tree& x) const override { return xt("round", {x}); }
    Tree Sin(const Tree& x) const override { return xt("sin", {x}); }
    Tree Sqrt(const Tree& x) const override { return xt("sqrt", {x}); }
    Tree Tan(const Tree& x) const override { return xt("tan", {x}); }

    //--- operations with no signal constructor ----------------------------------------
    // Not produced by the dense switch; derived transformations may use them as
    // shorthands, interpreted through the constructors they abbreviate.
    Tree Neg(const Tree& x) const override { return tree(sigs::g.SIGBINOP, tree(kSub), tree(0), x); }
    Tree Inv(const Tree& x) const override { return tree(sigs::g.SIGBINOP, tree(kDiv), tree(1.0), x); }
    Tree Not(const Tree& x) const override { return tree(sigs::g.SIGBINOP, tree(kEQ), x, tree(0)); }
    Tree Sinh(const Tree& x) const override { return xt("sinh", {x}); }
    Tree Cosh(const Tree& x) const override { return xt("cosh", {x}); }
    Tree Tanh(const Tree& x) const override { return xt("tanh", {x}); }
    Tree Asinh(const Tree& x) const override { return xt("asinh", {x}); }
    Tree Acosh(const Tree& x) const override { return xt("acosh", {x}); }
    Tree Atanh(const Tree& x) const override { return xt("atanh", {x}); }

   protected:
    /// Rebuild an extended-primitive node from the xtended itself: its interned symbol
    /// (with its user data) heads the node, the interpreted children are its branches.
    Tree xtendedOp(xtended* p, const std::vector<Tree>& c) const override
    {
        return CTree::make(Node(symbol(p->name())), tvec(c.begin(), c.end()));
    }

    /// Build a primitive application by name (ex-nihilo construction by a derived
    /// transformation; the symbol carries the xtended user data if registered).
    static Tree xt(const char* name, const tvec& args)
    {
        return CTree::make(Node(symbol(name)), args);
    }
};

/**
 * Rebuild L through an algebra: bottom-up over the DAG (treeRewrite), a FRESH variable
 * for every recursive group (a definition is written once -- TLIB_REC_STRICT clean),
 * structure (lists, labels, projections) rebuilt structurally. With the base
 * TreeAlgebra the result is alpha-equivalent to L, and pointer-equal on rec-free terms.
 */
SIGS_API Tree signalRebuild(Tree L, const TreeAlgebra& A);
