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

#include <unordered_map>
#include <vector>

#include "sigs-export.hh"
#include "sigtreealgebra.hh"
#include "sigtyperules.hh"

/**
 * The carrier of ANALYSIS-CONSULTING tree transformations: each value carries the
 * ORIGINAL subtree next to the transformed OUTPUT. The original is the type-annotated
 * one -- questions about a child (its nature, its interval) are asked of `orig`,
 * construction uses `out`. This is the product-carrier doctrine: the analysis travels
 * with the reconstruction instead of being re-derived syntactically.
 */
struct XSig {
    Tree orig = nullptr;  ///< the original, annotated subtree
    Tree out  = nullptr;  ///< the transformed subtree
};

/**
 * The base class of tree TRANSFORMATIONS over the XSig carrier.
 *
 * Every operation defaults to the IDENTITY reconstruction (delegated to TreeAlgebra
 * on the `out` components); a transformation overrides the operations it cares about
 * and reads its children's types through typeOf(). The driver (signalTransform) fills
 * the `orig` side, gives every recursive group a fresh variable (the immutability
 * protocol), and rebuilds structure structurally.
 *
 * Two applications carry their ORIGINAL node, because their algebra operation cannot:
 * ffApp (the ffunction node embeds its whole signature while ForeignFunction only
 * carries the return type) and xtdApp (an extended primitive is rebuilt from the
 * xtended itself, and a pass usually needs the node's own stored type).
 */
class SIGS_API TransformAlgebra : public SignalDispatch<XSig> {
   protected:
    TreeAlgebra fBuild;  ///< the initial algebra: default = identity reconstruction

   public:
    /// The stored type of a child's ORIGINAL subtree.
    static Type typeOf(const XSig& s) { return getCertifiedSigType(s.orig); }

    //--- transform-level applications (carry their original node) ---------------------
    /// An extended-primitive application. Default: identity rebuild from the xtended.
    virtual XSig xtdApp(Tree orig, xtended* p, const std::vector<XSig>& c) const;
    /// An ffunction application. Default: identity rebuild around the signature.
    virtual XSig ffApp(Tree orig, Tree ff, const std::vector<XSig>& args) const;

    //--- the recursive-definition seam ------------------------------------------------
    /// Applied to each definition of a recursive group after its transformation,
    /// before the group is tied. The wrap lives at the definition slot only: a
    /// subtree shared with an inner position keeps its unwrapped transform there.
    virtual XSig recDef(const XSig& def) const { return def; }

    //--- the top-down guard -----------------------------------------------------------
    /// Consulted on each ORIGINAL signal node before its children are visited. A
    /// non-null result replaces the whole subtree (R1: the premise is a judgment on
    /// the source term -- a type, an interval -- that would not survive
    /// reconstruction); children are then never visited and no other operation is
    /// applied. Default: no cut. Never consulted on structure or recursive nodes.
    virtual Tree cut(Tree) const { return nullptr; }

    //--- injections -------------------------------------------------------------------
    XSig IntNum(int x) const override { return o(fBuild.IntNum(x)); }
    XSig Int64Num(int64_t x) const override { return o(fBuild.Int64Num(x)); }
    XSig FloatNum(double x) const override { return o(fBuild.FloatNum(x)); }
    XSig Label(const std::string& s) const override { return o(fBuild.Label(s)); }
    XSig FixPointUpdate(const XSig&, const XSig& y) const override { return y; }

    //--- input / output ---------------------------------------------------------------
    XSig Input(const XSig& c) const override { return o(fBuild.Input(c.out)); }
    XSig Output(const XSig& c, const XSig& x) const override
    {
        return o(fBuild.Output(c.out, x.out));
    }

    //--- user interface ---------------------------------------------------------------
    XSig Button(const XSig& n) const override { return o(fBuild.Button(n.out)); }
    XSig Checkbox(const XSig& n) const override { return o(fBuild.Checkbox(n.out)); }
    XSig VSlider(const XSig& n, const XSig& i, const XSig& lo, const XSig& hi,
                 const XSig& st) const override
    {
        return o(fBuild.VSlider(n.out, i.out, lo.out, hi.out, st.out));
    }
    XSig HSlider(const XSig& n, const XSig& i, const XSig& lo, const XSig& hi,
                 const XSig& st) const override
    {
        return o(fBuild.HSlider(n.out, i.out, lo.out, hi.out, st.out));
    }
    XSig NumEntry(const XSig& n, const XSig& i, const XSig& lo, const XSig& hi,
                  const XSig& st) const override
    {
        return o(fBuild.NumEntry(n.out, i.out, lo.out, hi.out, st.out));
    }
    XSig HBargraph(const XSig& n, const XSig& lo, const XSig& hi,
                   const XSig& s) const override
    {
        return o(fBuild.HBargraph(n.out, lo.out, hi.out, s.out));
    }
    XSig VBargraph(const XSig& n, const XSig& lo, const XSig& hi,
                   const XSig& s) const override
    {
        return o(fBuild.VBargraph(n.out, lo.out, hi.out, s.out));
    }
    XSig Attach(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Attach(x.out, y.out));
    }
    XSig Enable(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Enable(x.out, y.out));
    }
    XSig Control(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Control(x.out, y.out));
    }

    //--- time and memory --------------------------------------------------------------
    XSig Mem(const XSig& x) const override { return o(fBuild.Mem(x.out)); }
    XSig Delay(const XSig& x, const XSig& n) const override
    {
        return o(fBuild.Delay(x.out, n.out));
    }
    XSig Prefix(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Prefix(x.out, y.out));
    }

    //--- casts ------------------------------------------------------------------------
    XSig IntCast(const XSig& x) const override { return o(fBuild.IntCast(x.out)); }
    XSig BitCast(const XSig& x) const override { return o(fBuild.BitCast(x.out)); }
    XSig FloatCast(const XSig& x) const override { return o(fBuild.FloatCast(x.out)); }

    //--- foreign ----------------------------------------------------------------------
    XSig ForeignConst(int t, const XSig& n, const XSig& f) const override
    {
        return o(fBuild.ForeignConst(t, n.out, f.out));
    }
    XSig ForeignVar(int t, const XSig& n, const XSig& f) const override
    {
        return o(fBuild.ForeignVar(t, n.out, f.out));
    }
    /// Unreachable: the driver routes ffunction applications to ffApp above.
    XSig ForeignFunction(int, const std::vector<XSig>&) const override
    {
        tlib::error("ASSERT : TransformAlgebra::ForeignFunction -- see ffApp\n");
        return {};
    }

    //--- tables, waveforms, soundfiles ------------------------------------------------
    XSig Table(const XSig& s, const XSig& c) const override
    {
        return o(fBuild.Table(s.out, c.out));
    }
    XSig WRTbl(const XSig& s, const XSig& g, const XSig& wi, const XSig& ws) const override
    {
        return o(fBuild.WRTbl(s.out, g.out, wi.out, ws.out));
    }
    XSig RDTbl(const XSig& t, const XSig& ri) const override
    {
        return o(fBuild.RDTbl(t.out, ri.out));
    }
    XSig Gen(const XSig& x) const override { return o(fBuild.Gen(x.out)); }
    XSig DocConstantTbl(const XSig& n, const XSig& i) const override
    {
        return o(fBuild.DocConstantTbl(n.out, i.out));
    }
    XSig DocWriteTbl(const XSig& n, const XSig& i, const XSig& wi,
                     const XSig& ws) const override
    {
        return o(fBuild.DocWriteTbl(n.out, i.out, wi.out, ws.out));
    }
    XSig DocAccessTbl(const XSig& t, const XSig& ri) const override
    {
        return o(fBuild.DocAccessTbl(t.out, ri.out));
    }
    XSig Register(int n, const XSig& s) const override
    {
        return o(fBuild.Register(n, s.out));
    }
    XSig Waveform(const std::vector<XSig>& w) const override
    {
        std::vector<Tree> ws;
        ws.reserve(w.size());
        for (const XSig& v : w) {
            ws.push_back(v.out);
        }
        return o(fBuild.Waveform(ws));
    }
    XSig SoundFile(const XSig& l) const override { return o(fBuild.SoundFile(l.out)); }
    XSig SoundFileLength(const XSig& sf, const XSig& p) const override
    {
        return o(fBuild.SoundFileLength(sf.out, p.out));
    }
    XSig SoundFileRate(const XSig& sf, const XSig& p) const override
    {
        return o(fBuild.SoundFileRate(sf.out, p.out));
    }
    XSig SoundFileBuffer(const XSig& sf, const XSig& c, const XSig& p,
                         const XSig& ri) const override
    {
        return o(fBuild.SoundFileBuffer(sf.out, c.out, p.out, ri.out));
    }

    //--- selection and bounds ---------------------------------------------------------
    XSig Select2(const XSig& s, const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Select2(s.out, x.out, y.out));
    }
    XSig AssertBounds(const XSig& lo, const XSig& hi, const XSig& x) const override
    {
        return o(fBuild.AssertBounds(lo.out, hi.out, x.out));
    }
    XSig Highest(const XSig& x) const override { return o(fBuild.Highest(x.out)); }
    XSig Lowest(const XSig& x) const override { return o(fBuild.Lowest(x.out)); }

    //--- the 17 binary operators ------------------------------------------------------
    XSig Add(const XSig& x, const XSig& y) const override { return o(fBuild.Add(x.out, y.out)); }
    XSig Sub(const XSig& x, const XSig& y) const override { return o(fBuild.Sub(x.out, y.out)); }
    XSig Mul(const XSig& x, const XSig& y) const override { return o(fBuild.Mul(x.out, y.out)); }
    XSig Div(const XSig& x, const XSig& y) const override { return o(fBuild.Div(x.out, y.out)); }
    XSig Mod(const XSig& x, const XSig& y) const override { return o(fBuild.Mod(x.out, y.out)); }
    XSig Lsh(const XSig& x, const XSig& y) const override { return o(fBuild.Lsh(x.out, y.out)); }
    XSig ARsh(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.ARsh(x.out, y.out));
    }
    XSig LRsh(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.LRsh(x.out, y.out));
    }
    XSig Gt(const XSig& x, const XSig& y) const override { return o(fBuild.Gt(x.out, y.out)); }
    XSig Lt(const XSig& x, const XSig& y) const override { return o(fBuild.Lt(x.out, y.out)); }
    XSig Ge(const XSig& x, const XSig& y) const override { return o(fBuild.Ge(x.out, y.out)); }
    XSig Le(const XSig& x, const XSig& y) const override { return o(fBuild.Le(x.out, y.out)); }
    XSig Eq(const XSig& x, const XSig& y) const override { return o(fBuild.Eq(x.out, y.out)); }
    XSig Ne(const XSig& x, const XSig& y) const override { return o(fBuild.Ne(x.out, y.out)); }
    XSig And(const XSig& x, const XSig& y) const override { return o(fBuild.And(x.out, y.out)); }
    XSig Or(const XSig& x, const XSig& y) const override { return o(fBuild.Or(x.out, y.out)); }
    XSig Xor(const XSig& x, const XSig& y) const override { return o(fBuild.Xor(x.out, y.out)); }

    //--- extended primitives (per-op forms: ex-nihilo construction only) --------------
    XSig Abs(const XSig& x) const override { return o(fBuild.Abs(x.out)); }
    XSig Acos(const XSig& x) const override { return o(fBuild.Acos(x.out)); }
    XSig Asin(const XSig& x) const override { return o(fBuild.Asin(x.out)); }
    XSig Atan(const XSig& x) const override { return o(fBuild.Atan(x.out)); }
    XSig Atan2(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Atan2(x.out, y.out));
    }
    XSig Ceil(const XSig& x) const override { return o(fBuild.Ceil(x.out)); }
    XSig Cos(const XSig& x) const override { return o(fBuild.Cos(x.out)); }
    XSig Exp(const XSig& x) const override { return o(fBuild.Exp(x.out)); }
    XSig Exp10(const XSig& x) const override { return o(fBuild.Exp10(x.out)); }
    XSig Floor(const XSig& x) const override { return o(fBuild.Floor(x.out)); }
    XSig Fmod(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Fmod(x.out, y.out));
    }
    XSig Log(const XSig& x) const override { return o(fBuild.Log(x.out)); }
    XSig Log10(const XSig& x) const override { return o(fBuild.Log10(x.out)); }
    XSig Max(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Max(x.out, y.out));
    }
    XSig Min(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Min(x.out, y.out));
    }
    XSig Pow(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Pow(x.out, y.out));
    }
    XSig Remainder(const XSig& x, const XSig& y) const override
    {
        return o(fBuild.Remainder(x.out, y.out));
    }
    XSig Rint(const XSig& x) const override { return o(fBuild.Rint(x.out)); }
    XSig Round(const XSig& x) const override { return o(fBuild.Round(x.out)); }
    XSig Sin(const XSig& x) const override { return o(fBuild.Sin(x.out)); }
    XSig Sqrt(const XSig& x) const override { return o(fBuild.Sqrt(x.out)); }
    XSig Tan(const XSig& x) const override { return o(fBuild.Tan(x.out)); }

    //--- shorthands with no signal constructor ----------------------------------------
    XSig Neg(const XSig& x) const override { return o(fBuild.Neg(x.out)); }
    XSig Inv(const XSig& x) const override { return o(fBuild.Inv(x.out)); }
    XSig Not(const XSig& x) const override { return o(fBuild.Not(x.out)); }
    XSig Sinh(const XSig& x) const override { return o(fBuild.Sinh(x.out)); }
    XSig Cosh(const XSig& x) const override { return o(fBuild.Cosh(x.out)); }
    XSig Tanh(const XSig& x) const override { return o(fBuild.Tanh(x.out)); }
    XSig Asinh(const XSig& x) const override { return o(fBuild.Asinh(x.out)); }
    XSig Acosh(const XSig& x) const override { return o(fBuild.Acosh(x.out)); }
    XSig Atanh(const XSig& x) const override { return o(fBuild.Atanh(x.out)); }

   protected:
    /// Wrap a built tree as a value; the driver fills the `orig` side.
    static XSig o(Tree out) { return {nullptr, out}; }

    /// Unreachable through the driver (xtended applications go to xtdApp).
    XSig xtendedOp(xtended* p, const std::vector<XSig>& c) const override;
};

/**
 * Run a transformation over L: bottom-up over the DAG (treeRewritePaired), a FRESH
 * variable per recursive group (a definition is written once), structure rebuilt
 * structurally, signal nodes dispatched through the algebra with each child value
 * carrying its annotated original. L must have been through typeAnnotation().
 */
SIGS_API Tree signalTransform(Tree L, const TransformAlgebra& A);

/**
 * Same, with a caller-owned memo surviving across calls: a pure-function cache
 * (original -> transformed) for transformations invoked repeatedly on overlapping
 * trees. The cache is sound only while the algebra is deterministic and the trees
 * it maps are alive; the caller owns both concerns.
 */
SIGS_API Tree signalTransform(Tree L, const TransformAlgebra& A,
                              std::unordered_map<Tree, Tree>& memo);
