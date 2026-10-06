/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <stdlib.h>
#include <cstdlib>
#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "floats.hh"
#include "global.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "sigPromotion.hh"
#include "sigtransform.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "xtended.hh"

using namespace std;

SignalTypePrinter::SignalTypePrinter(Tree L)
{
    // Check that the root tree is properly type annotated
    certifySignalsTyped(L);
    visitRoot(L);
}

string SignalTypePrinter::print()
{
    /*
     HACK: since the signal tree shape is still not deterministic,
     we sort the list to be sure it stays the same.
     To be removed if the tree shape becomes deterministic.
     */
    stringstream out;
    sort(fPrinted.begin(), fPrinted.end());
    out << "Size = " << fPrinted.size() << std::endl;
    for (const auto& it : fPrinted) {
        out << it;
    }
    return out.str();
}

void SignalTypePrinter::visit(Tree sig)
{
    stringstream type;
    type << "Type = " << getCertifiedSigType(sig) << endl;
    fPrinted.push_back(type.str());

    // Default case and recursion
    SignalVisitor::visit(sig);
}

void SignalChecker::isRange(Tree sig, Tree init_aux, Tree min_aux, Tree max_aux)
{
    std::stringstream error;
    double            init = tree2double(init_aux);
    double            min  = tree2double(min_aux);
    double            max  = tree2double(max_aux);
    if (min > max) {
        error << "ERROR : min = " << min << " should be less than max = " << max << " in '"
              << ppsig(sig) << "'\n";
        throw faustexception(error.str());
    } else if (init < min || init > max) {
        error << "ERROR : init = " << init << " outside of [" << min << " " << max << "] range in '"
              << ppsig(sig) << "'\n";
        throw faustexception(error.str());
    }
}

void SignalChecker::visit(Tree sig)
{
    int  opnum;
    Tree size, gen, wi, ri, x, y, sel, sf, ff, largs, chan, part, tb, ws, label, init, min, max,
        step, t0;

    // Extended
    xtended* p = (xtended*)getUserData(sig);
    if (p) {
        // The node's stored type IS the primitive's result type (the annotation just
        // computed it): no need to re-infer it from the argument types.
        Type tx = getCertifiedSigType(sig);
        for (Tree b : sig->branches()) {
            if (tx->nature() != getCertifiedSigType(b)->nature()) {
                cerr << "ASSERT : xtended with args of incorrect types : "
                     << ppsig(sig, MAX_ERROR_SIZE) << endl;
                faustassert(false);
            }
        }

        // Binary operations
    } else if (isSigBinOp(sig, &opnum, x, y)) {
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);
        if (tx->nature() != ty->nature()) {
            cerr << "ASSERT : isSigBinOp of args with different types : "
                 << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Foreign functions
    } else if (isSigFFun(sig, ff, largs)) {
        int len = ffarity(ff) - 1;
        for (int i = 0; i < ffarity(ff); i++) {
            int type = ffargtype(ff, len - i);
            if (getCertifiedSigType(nth(largs, i))->nature() != type && type != kAny) {
                cerr << "ASSERT : isSigFFun of args with incoherent types : "
                     << ppsig(sig, MAX_ERROR_SIZE) << endl;
                faustassert(false);
            }
        }
        if (ffrestype(ff) != getCertifiedSigType(sig)->nature()) {
            cerr << "ASSERT : isSigFFun of res with incoherent type : "
                 << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Select2 (and Select3 expressed with Select2)
    } else if (isSigSelect2(sig, sel, x, y)) {
        if (getCertifiedSigType(sel)->nature() != kInt) {
            cerr << "ASSERT : isSigSelect2 with wrong typed selector : "
                 << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Delay
    } else if (isSigDelay(sig, x, y)) {
        if (getCertifiedSigType(y)->nature() != kInt) {
            cerr << "ASSERT : isSigDelay with a wrong typed delay : " << ppsig(sig, MAX_ERROR_SIZE)
                 << endl;
            faustassert(false);
        }

        // Int, Bit and Float Cast
    } else if (isSigIntCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kInt) {
            cerr << "ASSERT : isSigIntCast of a kInt signal : " << ppsig(sig, MAX_ERROR_SIZE)
                 << endl;
            faustassert(false);
        }

    } else if (isSigBitCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kInt) {
            cerr << "ASSERT : isSigBitCast of a kInt signal : " << ppsig(sig, MAX_ERROR_SIZE)
                 << endl;
            faustassert(false);
        }

    } else if (isSigFloatCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kReal) {
            cerr << "ASSERT : isSigFloatCast of a kReal signal : " << ppsig(sig, MAX_ERROR_SIZE)
                 << endl;
            faustassert(false);
        }

        // Tables
    } else if (isSigRDTbl(sig, tb, ri)) {
        if (getCertifiedSigType(ri)->nature() != kInt) {
            cerr << "ASSERT : isSigRDTbl with a wrong typed rdx : " << ppsig(sig, MAX_ERROR_SIZE)
                 << endl;
            faustassert(false);
        }

    } else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        if ((wi != gGlobal->nil) && getCertifiedSigType(wi)->nature() != kInt) {
            cerr << "ASSERT : isSigWRTbl with a wrong typed wdx : " << ppsig(sig, MAX_ERROR_SIZE)
                 << endl;
            faustassert(false);
        }
        if ((wi != gGlobal->nil) &&
            getCertifiedSigType(gen)->nature() != getCertifiedSigType(ws)->nature()) {
            cerr << "ASSERT : isSigWRTbl with non matching gen and ws types : "
                 << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Soundfiles
    } else if (isSigSoundfileLength(sig, sf, part)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ASSERT : isSigSoundfileLength with a wrong typed part : "
                 << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

    } else if (isSigSoundfileRate(sig, sf, part)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ASSERT : isSigSoundfileRate with a wrong typed part : "
                 << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

    } else if (isSigSoundfileBuffer(sig, sf, chan, part, ri)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ASSERT : isSigSoundfileBuffer with a wrong typed part : "
                 << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }
        if (getCertifiedSigType(ri)->nature() != kInt) {
            cerr << "ASSERT : isSigSoundfileBuffer with a wrong typed ri : "
                 << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Sliders and nentry
    } else if (isSigVSlider(sig, label, init, min, max, step) ||
               isSigHSlider(sig, label, init, min, max, step) ||
               isSigNumEntry(sig, label, init, min, max, step)) {
        isRange(sig, init, min, max);

        // Bargraph
    } else if (isSigHBargraph(sig, label, min, max, t0)) {
        if (getCertifiedSigType(t0)->nature() == kInt) {
            cerr << "ASSERT : isSigHBargraph of a kInt signal : " << ppsig(sig, MAX_ERROR_SIZE)
                 << endl;
            faustassert(false);
        }

    } else if (isSigVBargraph(sig, label, min, max, t0)) {
        if (getCertifiedSigType(t0)->nature() == kInt) {
            cerr << "ASSERT : isSigVBargraph of a kInt signal : " << ppsig(sig, MAX_ERROR_SIZE)
                 << endl;
            faustassert(false);
        }

        // Waveform
    } else if (isSigWaveform(sig)) {
        int ty = getCertifiedSigType(sig->branch(0))->nature();
        for (int i = 1; i < sig->arity(); i++) {
            if (ty != getCertifiedSigType(sig->branch(i))->nature()) {
                cerr << "ASSERT : isSigWaveform with mixed kInt and kReal values : "
                     << ppsig(sig, MAX_ERROR_SIZE) << endl;
                faustassert(false);
            }
        }

        // Signal bounds
    } else if (isSigLowest(sig, x) || isSigHighest(sig, x)) {
        cerr << "ASSERT : annotations should have been deleted in simplification process" << endl;
        faustassert(false);

        // enable/control
    } else if (isSigControl(sig, x, y) && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : 'control/enable' can only be used in scalar mode\n");
    }

    // Default case and recursion
    SignalVisitor::visit(sig);
}

// Public API
//-------------------------SignalPromotionAlgebra------------------------
// The cast-promotion pass expressed as a TransformAlgebra: adds explicit int or
// float casts where the stored types require them, prior to any optimisation.
// Type questions are asked of the ORIGINAL children (the XSig carrier); recursion,
// memoization and structure belong to the driver -- and every recursive group gets a
// fresh variable, so this pass never redefines a definition.
//------------------------------------------------------------------------

class SignalPromotionAlgebra : public TransformAlgebra {
   public:
    //--- extended primitives: promote every argument to the node's own nature --------
    XSig xtdApp(Tree orig, xtended*, const std::vector<XSig>& c) const override
    {
        Type tr = getCertifiedSigType(orig);
        tvec br;
        br.reserve(c.size());
        for (const XSig& b : c) {
            br.push_back(smartCast(tr, typeOf(b), b.out));
        }
        return o(tree(orig->node(), br));
    }

    //--- the delay amount is an int ---------------------------------------------------
    XSig Delay(const XSig& x, const XSig& n) const override
    {
        return o(fBuild.Delay(x.out, smartIntCast(typeOf(n), n.out)));
    }

    //--- binary operators, by family --------------------------------------------------
    XSig Add(const XSig& x, const XSig& y) const override { return sameNature(kAdd, x, y); }
    XSig Sub(const XSig& x, const XSig& y) const override { return sameNature(kSub, x, y); }
    XSig Mul(const XSig& x, const XSig& y) const override { return sameNature(kMul, x, y); }
    XSig Gt(const XSig& x, const XSig& y) const override { return sameNature(kGT, x, y); }
    XSig Lt(const XSig& x, const XSig& y) const override { return sameNature(kLT, x, y); }
    XSig Ge(const XSig& x, const XSig& y) const override { return sameNature(kGE, x, y); }
    XSig Le(const XSig& x, const XSig& y) const override { return sameNature(kLE, x, y); }
    XSig Eq(const XSig& x, const XSig& y) const override { return sameNature(kEQ, x, y); }
    XSig Ne(const XSig& x, const XSig& y) const override { return sameNature(kNE, x, y); }

    XSig Mod(const XSig& x, const XSig& y) const override
    {
        Type tx = typeOf(x);
        Type ty = typeOf(y);
        if (tx->nature() == kInt && ty->nature() == kInt) {
            return o(fBuild.Mod(x.out, y.out));
        }
        // float promotion needed, rem (%) replaced by fmod
        std::vector<Tree> lsig = {smartFloatCast(tx, x.out), smartFloatCast(ty, y.out)};
        return o(gGlobal->gFmodPrim->computeSigOutput(lsig));
    }

    XSig Div(const XSig& x, const XSig& y) const override
    {
        Type     tx = typeOf(x);
        Type     ty = typeOf(y);
        interval i1 = tx->getInterval();
        interval j1 = ty->getInterval();
        if (i1.isValid() && j1.isValid() && gGlobal->gMathExceptions && j1.hasZero()) {
            stringstream error;
            error << "WARNING : potential division by zero (" << i1 << "/" << j1 << ")"
                  << endl;
            gWarningMessages.push_back(error.str());
        }
        // the result of a division is always a float
        Tree fx = smartFloatCast(tx, x.out);
        Tree fy = smartFloatCast(ty, y.out);
        return o(fBuild.Div(fx, fy));
    }

    XSig And(const XSig& x, const XSig& y) const override { return intArgs(kAND, x, y); }
    XSig Or(const XSig& x, const XSig& y) const override { return intArgs(kOR, x, y); }
    XSig Xor(const XSig& x, const XSig& y) const override { return intArgs(kXOR, x, y); }
    XSig Lsh(const XSig& x, const XSig& y) const override { return shift(kLsh, x, y); }
    XSig ARsh(const XSig& x, const XSig& y) const override { return shift(kARsh, x, y); }
    XSig LRsh(const XSig& x, const XSig& y) const override { return shift(kLRsh, x, y); }

    //--- ffunction: promote each argument to its declared type ------------------------
    XSig ffApp(Tree, Tree ff, const std::vector<XSig>& args) const override
    {
        siglist clargs;
        int     len = ffarity(ff) - 1;
        for (int i = 0; i < int(args.size()); i++) {
            clargs.push_back(
                smartCast(ffargtype(ff, len - i), typeOf(args[i])->nature(), args[i].out));
        }
        return o(sigFFun(ff, listConvert(clargs)));
    }

    XSig Prefix(const XSig& x, const XSig& y) const override
    {
        Type tx = typeOf(x);
        Type ty = typeOf(y);
        if (tx->nature() == ty->nature()) {
            return o(fBuild.Prefix(x.out, y.out));
        }
        Tree fx = smartFloatCast(tx, x.out);
        Tree fy = smartFloatCast(ty, y.out);
        return o(fBuild.Prefix(fx, fy));
    }

    XSig Select2(const XSig& sel, const XSig& x, const XSig& y) const override
    {
        Type ts = typeOf(sel);
        Type tx = typeOf(x);
        Type ty = typeOf(y);
        if (tx->nature() == ty->nature()) {
            return o(fBuild.Select2(smartIntCast(ts, sel.out), x.out, y.out));
        }
        Tree isel = smartIntCast(ts, sel.out);
        Tree fx   = smartFloatCast(tx, x.out);
        Tree fy   = smartFloatCast(ty, y.out);
        return o(fBuild.Select2(isel, fx, fy));
    }

    //--- casts: drop the node when the child already has the nature -------------------
    XSig IntCast(const XSig& x) const override
    {
        return o(smartIntCast(typeOf(x), x.out));
    }
    XSig FloatCast(const XSig& x) const override
    {
        return o(smartFloatCast(typeOf(x), x.out));
    }

    //--- tables and soundfiles: integer indices, write signal cast to the content -----
    XSig RDTbl(const XSig& t, const XSig& ri) const override
    {
        return o(fBuild.RDTbl(t.out, smartIntCast(typeOf(ri), ri.out)));
    }
    XSig WRTbl(const XSig& s, const XSig& g, const XSig& wi, const XSig& ws) const override
    {
        Tree iwi = smartIntCast(typeOf(wi), wi.out);
        Tree cws = smartCast(typeOf(g), typeOf(ws), ws.out);
        return o(fBuild.WRTbl(s.out, g.out, iwi, cws));
    }
    XSig SoundFileLength(const XSig& sf, const XSig& p) const override
    {
        return o(fBuild.SoundFileLength(sf.out, smartIntCast(typeOf(p), p.out)));
    }
    XSig SoundFileRate(const XSig& sf, const XSig& p) const override
    {
        return o(fBuild.SoundFileRate(sf.out, smartIntCast(typeOf(p), p.out)));
    }
    XSig SoundFileBuffer(const XSig& sf, const XSig& c, const XSig& p,
                         const XSig& ri) const override
    {
        Tree ip  = smartIntCast(typeOf(p), p.out);
        Tree iri = smartIntCast(typeOf(ri), ri.out);
        return o(fBuild.SoundFileBuffer(sf.out, c.out, ip, iri));
    }

    //--- bargraphs display a float ----------------------------------------------------
    XSig HBargraph(const XSig& n, const XSig& lo, const XSig& hi,
                   const XSig& s) const override
    {
        return o(fBuild.HBargraph(n.out, lo.out, hi.out, smartFloatCast(typeOf(s), s.out)));
    }
    XSig VBargraph(const XSig& n, const XSig& lo, const XSig& hi,
                   const XSig& s) const override
    {
        return o(fBuild.VBargraph(n.out, lo.out, hi.out, smartFloatCast(typeOf(s), s.out)));
    }

    //--- waveforms: all-int stays, otherwise every value floats -----------------------
    XSig Waveform(const std::vector<XSig>& w) const override
    {
        bool iflag = true;
        for (const XSig& v : w) {
            if (!isInt(v.orig->node())) {
                iflag = false;
                break;
            }
        }
        if (iflag) {
            std::vector<Tree> ws;
            ws.reserve(w.size());
            for (const XSig& v : w) {
                ws.push_back(v.out);
            }
            return o(fBuild.Waveform(ws));
        }
        std::vector<Tree> ws;
        ws.reserve(w.size());
        for (const XSig& v : w) {
            ws.push_back(smartFloatCast(typeOf(v), v.out));
        }
        return o(fBuild.Waveform(ws));
    }

   private:
    //--- the cast policy of the pass (folding casts: this is a NORMALIZING pass) ------
    static Tree cast(int t, Tree sig)
    {
        if (t == kReal) {
            return sigFloatCast(sig);
        }
        if (t == kInt) {
            return sigIntCast(sig);
        }
        faustassert(t == kAny);
        return sig;
    }
    static Tree smartCast(int t1, int t2, Tree sig) { return (t1 != t2) ? cast(t1, sig) : sig; }
    static Tree smartCast(Type t1, Type t2, Tree sig)
    {
        return smartCast(t1->nature(), t2->nature(), sig);
    }
    static Tree smartIntCast(Type t, Tree sig)
    {
        return (t->nature() == kReal) ? sigIntCast(sig) : sig;
    }
    static Tree smartFloatCast(Type t, Tree sig)
    {
        return (t->nature() == kInt) ? sigFloatCast(sig) : sig;
    }

    XSig sameNature(int op, const XSig& x, const XSig& y) const
    {
        Type tx = typeOf(x);
        Type ty = typeOf(y);
        if (tx->nature() == ty->nature()) {
            return o(tree(sigs::g.SIGBINOP, tree(op), x.out, y.out));
        }
        Tree top = tree(op);
        Tree fx  = smartFloatCast(tx, x.out);
        Tree fy  = smartFloatCast(ty, y.out);
        return o(tree(sigs::g.SIGBINOP, top, fx, fy));
    }
    XSig intArgs(int op, const XSig& x, const XSig& y) const
    {
        Tree top = tree(op);
        Tree ix  = smartIntCast(typeOf(x), x.out);
        Tree iy  = smartIntCast(typeOf(y), y.out);
        return o(tree(sigs::g.SIGBINOP, top, ix, iy));
    }
    XSig shift(int op, const XSig& x, const XSig& y) const
    {
        Type     ty = typeOf(y);
        interval i1 = ty->getInterval();
        if (i1.isValid() && gGlobal->gMathExceptions && i1.lo() < 0) {
            stringstream error;
            error << "WARNING : bit shift operation with negative argument (" << i1 << ")"
                  << endl;
            gWarningMessages.push_back(error.str());
        }
        return intArgs(op, x, y);
    }
};

Tree signalPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    certifySignalsTyped(sig);

    SignalPromotionAlgebra A;
    return signalTransform(sig, A);
}

//-------------------------Bool2IntPromotionAlgebra-----------------------
// Cast bool binary operations (comparison operations) to int.
//------------------------------------------------------------------------
class Bool2IntPromotionAlgebra final : public TransformAlgebra {
    XSig cmp(int op, const XSig& x, const XSig& y) const
    {
        return o(sigIntCast(sigBinOp(op, x.out, y.out)));
    }

   public:
    XSig Gt(const XSig& x, const XSig& y) const override { return cmp(kGT, x, y); }
    XSig Lt(const XSig& x, const XSig& y) const override { return cmp(kLT, x, y); }
    XSig Ge(const XSig& x, const XSig& y) const override { return cmp(kGE, x, y); }
    XSig Le(const XSig& x, const XSig& y) const override { return cmp(kLE, x, y); }
    XSig Eq(const XSig& x, const XSig& y) const override { return cmp(kEQ, x, y); }
    XSig Ne(const XSig& x, const XSig& y) const override { return cmp(kNE, x, y); }
};

// An index computed in integers only is exact : its proven interval decides its guard.
// An index fed by a float converted to an integer is not : the proven bounds are those
// of a program that rounds every operation apart and in the written order, while the
// C++ compiler may fuse a*b + c into an FMA, reassociate a sum under -ffast-math, and
// the libm is not correctly rounded. The error is bounded by the size of the terms, not
// of the result, and int(x) can pass a proven bound by several units : such an index
// always keeps its guard. A comparison proven undecided ([0:1]) stays within its bounds
// whatever the error of its operands, the delay of a value and the choice of a select2
// do not change its range, a user interface element is a stored value with no
// operation : none of them makes an index float-fed. A comparison proven decided by
// float bounds is not exact : x < 0.5 with x proven >= 0.5 at the edge can be 1.
static bool isUIElement(Tree t)
{
    return isSigHSlider(t) || isSigVSlider(t) || isSigNumEntry(t) || isSigButton(t) ||
           isSigCheckbox(t);
}

static bool isReal(Tree t)
{
    ::Type ty = getSigType(t);
    return ty && ty->nature() == kReal;
}

// memo : an exact index makes exact every node its walk visits (what they reach, it
// reached), a float-fed one only itself (the walk stops at the first float).
static bool floatFedIndex(Tree idx, std::map<Tree, bool>& memo)
{
    auto known = memo.find(idx);
    if (known != memo.end()) return known->second;
    if (isReal(idx)) return memo[idx] = true;
    std::set<Tree>    seen;
    std::vector<Tree> todo{idx};
    while (!todo.empty()) {
        Tree t = todo.back();
        todo.pop_back();
        if (!seen.insert(t).second) continue;
        if (isReal(t)) continue;  // a float only reaches an integer through a node seen here
        auto m = memo.find(t);
        if (m != memo.end()) {
            if (m->second) return memo[idx] = true;
            continue;
        }
        int  op;
        Tree x, y, z;
        if (isSigBinOp(t, &op, x, y) && op >= kGT && op <= kNE) {
            interval c = getCertifiedSigType(t)->getInterval();
            if (c.lo() <= 0 && c.hi() >= 1) {
                continue;  // undecided : within [0:1] whatever its operands
            }
        }
        if (isSigDelay(t, x, y)) {
            todo.push_back(x);
            continue;
        }
        if (isSigSelect2(t, x, y, z)) {
            todo.push_back(y);
            todo.push_back(z);
            continue;
        }
        if (isSigRDTbl(t, x, y)) {
            todo.push_back(x);
            continue;
        }
        if (isSigIntCast(t, x) && isUIElement(x)) continue;
        tvec subs;
        getSubSignals(t, subs);
        for (Tree u : subs) {
            if (isReal(u)) return memo[idx] = true;
            todo.push_back(u);
        }
    }
    for (Tree t : seen) {
        if (!isReal(t)) memo[t] = false;
    }
    return false;
}

// An integer min or max returns one of its operands : its constant operand bounds it
// exactly on one side, whatever the error of the other one. So max(k0, min(x, k1)) is
// within [k0, k1] even when x is fed by a float -- the clamp of ba.tabulate(1, ...)
// (basics.lib rid). Not a float min or max : it may let a NaN through, depending on the
// order of its operands, and int(NaN) is undefined. Elsewhere, an exact index is
// bounded by its proven interval.
static bool boundedSide(Tree t, bool low, int bound, std::map<Tree, bool>& memo)
{
    int k;
    if (isSigInt(t, &k)) {
        return low ? k >= bound : k <= bound;
    }
    xtended* p = (xtended*)getUserData(t);
    if ((p == gGlobal->gMinPrim || p == gGlobal->gMaxPrim) && t->arity() == 2 && !isReal(t)) {
        bool a = boundedSide(t->branch(0), low, bound, memo);
        bool b = boundedSide(t->branch(1), low, bound, memo);
        // max(a, b) >= k when one of them is, <= k when both are ; the converse for min
        return (low == (p == gGlobal->gMaxPrim)) ? (a || b) : (a && b);
    }
    if (floatFedIndex(t, memo)) {
        return false;
    }
    interval i_t = getCertifiedSigType(t)->getInterval();
    return low ? i_t.lo() >= bound : i_t.hi() <= bound;
}

// The guard of an index is needed unless the index is proven within [0, size-1] :
// exact and within by its interval, or clamped by constants (boundedSide).
static bool needsGuard(Tree idx, const interval& idx_i, int size, std::map<Tree, bool>& memo)
{
    if (idx_i.lo() >= 0 && idx_i.hi() < size && !floatFedIndex(idx, memo)) {
        return false;
    }
    return !(boundedSide(idx, true, 0, memo) && boundedSide(idx, false, size - 1, memo));
}

// The warning of a guarded index : out of the table, or within it but fed by a float
static string guardWarning(const char* what, const interval& idx_i, int size, Tree sig)
{
    stringstream error;
    error << "WARNING : " << what << " [" << idx_i.lo() << ":" << idx_i.hi() << "] ";
    if (idx_i.lo() < 0 || idx_i.hi() >= size) {
        error << "is outside of table size (" << size << ")";
    } else {
        error << "is within table size (" << size
              << ") but computed from a float, so it keeps its guard";
    }
    error << " in " << ppsig(sig, MAX_ERROR_SIZE) << endl;
    return error.str();
}

//-------------------------TablePromotionAlgebra--------------------------
// Generate safe access to rdtable/rwtable (wdx/rdx in [0..size-1]). Both guards
// are decided at the read node, each one on its own index : the write guard does not
// depend on the read one (it used to be dropped with an exact read index).
//------------------------------------------------------------------------
class TablePromotionAlgebra final : public TransformAlgebra {
    mutable std::map<Tree, bool> fFloatFed;  // memo of floatFedIndex

   public:
    XSig RDTbl(const XSig& t, const XSig& ri) const override
    {
        Tree size0, gen0, wi0, ws0;
        isSigWRTbl(t.orig, size0, gen0, wi0, ws0);
        int size = tree2int(size0);

        Tree tblOut = t.out;
        if (wi0 != gGlobal->nil) {
            // rwtable: the write guard runs first
            if (size <= 0) {
                stringstream error;
                error << "ERROR : WRTbl size = " << size << " should be > 0 \n";
                throw faustexception(error.str());
            }
            interval wi_i = getCertifiedSigType(wi0)->getInterval();
            if (needsGuard(wi0, wi_i, size, fFloatFed)) {
                if (gAllWarning) {
                    gWarningMessages.push_back(
                        guardWarning("WRTbl write index", wi_i, size, t.orig));
                }
                Tree s2, g2, wi2, ws2;
                isSigWRTbl(t.out, s2, g2, wi2, ws2);
                Tree zero = sigInt(0);
                Tree last = sigMin(wi2, sigInt(size - 1));
                tblOut    = sigWRTbl(s2, g2, sigMax(zero, last), ws2);
            }
        }

        if (size <= 0) {
            stringstream error;
            error << "ERROR : RDTbl size = " << size << " should be > 0 \n";
            throw faustexception(error.str());
        }
        interval ri_i = typeOf(ri)->getInterval();
        if (needsGuard(ri.orig, ri_i, size, fFloatFed)) {
            if (gAllWarning) {
                gWarningMessages.push_back(
                    guardWarning("RDTbl read index", ri_i, size, fBuild.RDTbl(t.orig, ri.orig)));
            }
            Tree zero = sigInt(0);
            Tree last = sigMin(ri.out, sigInt(size - 1));
            return o(sigRDTbl(tblOut, sigMax(zero, last)));
        }
        return o(fBuild.RDTbl(tblOut, ri.out));
    }
};

//-------------------------IntCastPromotionAlgebra------------------------
// Float to integer conversion, checking the range.
//------------------------------------------------------------------------
class IntCastPromotionAlgebra final : public TransformAlgebra {
   public:
    XSig IntCast(const XSig& x) const override
    {
        interval x_i = typeOf(x)->getInterval();
        if (x_i.lo() <= INT32_MIN || x_i.hi() >= INT32_MAX) {
            if (gAllWarning) {
                stringstream error;
                error << "WARNING : float to integer conversion [" << x_i.lo() << ":" << x_i.hi()
                      << "] is outside of integer range in "
                      << ppsig(fBuild.IntCast(x.orig), MAX_ERROR_SIZE) << endl;
                gWarningMessages.push_back(error.str());
            }
            Tree hi = sigReal(INT32_MAX);
            Tree lo = sigMax(x.out, sigReal(INT32_MIN));
            return o(sigIntCast(sigMin(hi, lo)));
        }
        return o(fBuild.IntCast(x.out));
    }
};

//-------------------------UIPromotionAlgebra-----------------------------
// Generate safe access to range UI items (sliders and nentry).
//------------------------------------------------------------------------
class UIPromotionAlgebra final : public TransformAlgebra {
    XSig clamp(const XSig& lo, const XSig& hi, Tree w) const
    {
        return o(sigMax(lo.out, sigMin(hi.out, w)));
    }

   public:
    XSig VSlider(const XSig& n, const XSig& i, const XSig& lo, const XSig& hi,
                 const XSig& st) const override
    {
        return clamp(lo, hi, fBuild.VSlider(n.out, i.out, lo.out, hi.out, st.out));
    }
    XSig HSlider(const XSig& n, const XSig& i, const XSig& lo, const XSig& hi,
                 const XSig& st) const override
    {
        return clamp(lo, hi, fBuild.HSlider(n.out, i.out, lo.out, hi.out, st.out));
    }
    XSig NumEntry(const XSig& n, const XSig& i, const XSig& lo, const XSig& hi,
                  const XSig& st) const override
    {
        return clamp(lo, hi, fBuild.NumEntry(n.out, i.out, lo.out, hi.out, st.out));
    }
};

//-------------------------UIFreezePromotionAlgebra-----------------------
// Freeze range UI items (sliders and nentry) to their init value. Everything
// that depends on sliders and nentry will be computed at compile time.
//------------------------------------------------------------------------
class UIFreezePromotionAlgebra final : public TransformAlgebra {
   public:
    XSig VSlider(const XSig&, const XSig& i, const XSig&, const XSig&,
                 const XSig&) const override
    {
        return o(i.out);
    }
    XSig HSlider(const XSig&, const XSig& i, const XSig&, const XSig&,
                 const XSig&) const override
    {
        return o(i.out);
    }
    XSig NumEntry(const XSig&, const XSig& i, const XSig&, const XSig&,
                  const XSig&) const override
    {
        return o(i.out);
    }
};

//-------------------------FTZPromotionAlgebra----------------------------
// Wrap the real-typed definitions of recursive groups with flush-to-zero code,
// through the recursive-definition seam. This option should be used only when
// FTZ is not available on the CPU.
//------------------------------------------------------------------------
class FTZPromotionAlgebra final : public TransformAlgebra {
   public:
    XSig recDef(const XSig& def) const override
    {
        if (typeOf(def)->nature() != kReal) {
            return def;
        }
        if (gGlobal->gFTZMode == 1) {
            Tree mag  = sigAbs(def.out);
            Tree eps  = sigReal(inummin());
            Tree cond = sigGT(mag, eps);
            Tree zero = sigReal(0.0);
            return o(sigSelect2(cond, zero, def.out));
        }
        if (gGlobal->gFTZMode == 2) {
            // Bitcast the recursive value and test only its IEEE-754 exponent field.
            // An all-zero exponent denotes zero or a subnormal, which is replaced by +0.0;
            // normal values, infinities, and NaNs have a nonzero exponent and are preserved.
            // The generated integer literals are printed in decimal:
            //   binary32: 0x7F800000         = 2139095040
            //   binary64: 0x7FF0000000000000 = 9218868437227405312
            if (gGlobal->gFloatSize == 1) {
                Tree bits = sigBitCast(def.out);
                Tree mask = sigInt(inummax());
                Tree cond = sigAND(bits, mask);
                Tree zero = sigReal(0.0);
                return o(sigSelect2(cond, zero, def.out));
            }
            if (gGlobal->gFloatSize == 2) {
                Tree bits = sigBitCast(def.out);
                Tree mask = sigInt64(inummax());
                Tree cond = sigAND(bits, mask);
                Tree zero = sigReal(0.0);
                return o(sigSelect2(cond, zero, def.out));
            }
        }
        return def;
    }
};

Tree signalBool2IntPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    certifySignalsTyped(sig);

    Bool2IntPromotionAlgebra A;
    return signalTransform(sig, A);
}

Tree signalTablePromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    certifySignalsTyped(sig);

    TablePromotionAlgebra A;
    return signalTransform(sig, A);
}

Tree signalIntCastPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    certifySignalsTyped(sig);

    IntCastPromotionAlgebra A;
    return signalTransform(sig, A);
}

Tree signalUIPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    certifySignalsTyped(sig);

    UIPromotionAlgebra A;
    return signalTransform(sig, A);
}

Tree signalUIFreezePromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    certifySignalsTyped(sig);

    UIFreezePromotionAlgebra A;
    return signalTransform(sig, A);
}

Tree signalFTZPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    certifySignalsTyped(sig);

    FTZPromotionAlgebra A;
    return signalTransform(sig, A);
}

