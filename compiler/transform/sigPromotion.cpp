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
#include <sstream>

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
        return o(fBuild.Div(smartFloatCast(tx, x.out), smartFloatCast(ty, y.out)));
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
        return o(fBuild.Prefix(smartFloatCast(tx, x.out), smartFloatCast(ty, y.out)));
    }

    XSig Select2(const XSig& sel, const XSig& x, const XSig& y) const override
    {
        Type ts = typeOf(sel);
        Type tx = typeOf(x);
        Type ty = typeOf(y);
        if (tx->nature() == ty->nature()) {
            return o(fBuild.Select2(smartIntCast(ts, sel.out), x.out, y.out));
        }
        return o(fBuild.Select2(smartIntCast(ts, sel.out), smartFloatCast(tx, x.out),
                                smartFloatCast(ty, y.out)));
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
        return o(fBuild.WRTbl(s.out, g.out, smartIntCast(typeOf(wi), wi.out),
                              smartCast(typeOf(g), typeOf(ws), ws.out)));
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
        return o(fBuild.SoundFileBuffer(sf.out, c.out, smartIntCast(typeOf(p), p.out),
                                        smartIntCast(typeOf(ri), ri.out)));
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
        return o(tree(sigs::g.SIGBINOP, tree(op), smartFloatCast(tx, x.out),
                      smartFloatCast(ty, y.out)));
    }
    XSig intArgs(int op, const XSig& x, const XSig& y) const
    {
        return o(tree(sigs::g.SIGBINOP, tree(op), smartIntCast(typeOf(x), x.out),
                      smartIntCast(typeOf(y), y.out)));
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

//-------------------------TablePromotionAlgebra--------------------------
// Generate safe access to rdtable/rwtable (wdx/rdx in [0..size-1]). Both guards
// are decided at the read node, and the write clamp is applied only when the
// read index is itself out of bounds -- the historical behaviour, reproduced
// exactly (the warning, however, is always emitted).
//------------------------------------------------------------------------
class TablePromotionAlgebra final : public TransformAlgebra {
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
            if (wi_i.lo() < 0 || wi_i.hi() >= size) {
                if (gAllWarning) {
                    stringstream error;
                    error << "WARNING : WRTbl write index [" << wi_i.lo() << ":" << wi_i.hi()
                          << "] is outside of table size (" << size << ") in "
                          << ppsig(t.orig, MAX_ERROR_SIZE) << endl;
                    gWarningMessages.push_back(error.str());
                }
                Tree s2, g2, wi2, ws2;
                isSigWRTbl(t.out, s2, g2, wi2, ws2);
                tblOut =
                    sigWRTbl(s2, g2, sigMax(sigInt(0), sigMin(wi2, sigInt(size - 1))), ws2);
            }
        }

        if (size <= 0) {
            stringstream error;
            error << "ERROR : RDTbl size = " << size << " should be > 0 \n";
            throw faustexception(error.str());
        }
        interval ri_i = typeOf(ri)->getInterval();
        if (ri_i.lo() < 0 || ri_i.hi() >= size) {
            if (gAllWarning) {
                stringstream error;
                error << "WARNING : RDTbl read index [" << ri_i.lo() << ":" << ri_i.hi()
                      << "] is outside of table size (" << size << ") in "
                      << ppsig(fBuild.RDTbl(t.orig, ri.orig), MAX_ERROR_SIZE) << endl;
                gWarningMessages.push_back(error.str());
            }
            return o(sigRDTbl(tblOut, sigMax(sigInt(0), sigMin(ri.out, sigInt(size - 1)))));
        }
        return o(fBuild.RDTbl(t.out, ri.out));
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
            return o(sigIntCast(sigMin(sigReal(INT32_MAX), sigMax(x.out, sigReal(INT32_MIN)))));
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
            return o(
                sigSelect2(sigGT(sigAbs(def.out), sigReal(inummin())), sigReal(0.0), def.out));
        }
        if (gGlobal->gFTZMode == 2) {
            // Bitcast the recursive value and test only its IEEE-754 exponent field.
            // An all-zero exponent denotes zero or a subnormal, which is replaced by +0.0;
            // normal values, infinities, and NaNs have a nonzero exponent and are preserved.
            // The generated integer literals are printed in decimal:
            //   binary32: 0x7F800000         = 2139095040
            //   binary64: 0x7FF0000000000000 = 9218868437227405312
            if (gGlobal->gFloatSize == 1) {
                return o(sigSelect2(sigAND(sigBitCast(def.out), sigInt(inummax())),
                                    sigReal(0.0), def.out));
            }
            if (gGlobal->gFloatSize == 2) {
                return o(sigSelect2(sigAND(sigBitCast(def.out), sigInt64(inummax())),
                                    sigReal(0.0), def.out));
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

//-------------SignalAutoDifferentiate---------------
// Auto Differentiate a signal (upstream -diff feature), grafted
// verbatim from the pre-decoupling sigPromotion
//---------------------------------------------------

Tree SignalAutoDifferentiate::transformation(Tree sig)
{
    int     op;
    int     i;
    int64_t i64;
    double  r;
    Tree    w, x, y, z, label, init, min, max, step, var, body;
    Tree    d;

    // Math primitives
    xtended* p = (xtended*)getUserData(sig);
    if (p) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "math primitive: " << ppsig(sig) << "\n";
        }

        if (p == gGlobal->gPowPrim || p == gGlobal->gFmodPrim || p == gGlobal->gRemainderPrim ||
            p == gGlobal->gMaxPrim || p == gGlobal->gMinPrim) {
            // Derivative of these primitives require f, g, f' and g'.
            auto branches{sig->branches()};
            branches.push_back(self(sig->branch(0)));
            branches.push_back(self(sig->branch(1)));
            d = p->diff(branches);
        } else {
            // chain rule for unary function: f(g(x))' = f'(g(x)) * g'(x)
            d = sigMul(p->diff(sig->branches()), self(sig->branch(0)));
        }
    }

    else if (isSigInt(sig, &i)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Int: " << ppsig(sig) << "\n";
        }
        d = sigInt(0);
    } else if (isSigInt64(sig, &i64)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Int64: " << ppsig(sig) << "\n";
        }
        d = sigInt64(0);
    } else if (isSigReal(sig, &r)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Real: " << ppsig(sig) << "\n";
        }
        d = sigReal(0.0);
    }

    // Binary operations
    // kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR,
    // kXOR
    else if (isSigBinOp(sig, &op, x, y)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "x: " << ppsig(x) << "\ty: " << ppsig(y) << "\top: ";
        }

        switch (op) {
            case kAdd:
                if (gGlobal->gDetailsSwitch) {
                    std::cout << "ADD\n";
                }
                // (f + g)' = f' + g'
                d = sigAdd(self(x), self(y));
                break;
            case kSub:
                if (gGlobal->gDetailsSwitch) {
                    std::cout << "SUB\n";
                }
                // (f - g)' = f' - g'
                d = sigSub(self(x), self(y));
                break;
            case kMul:
                if (gGlobal->gDetailsSwitch) {
                    std::cout << "MUL\n";
                }
                // (f * g)' = f' * g + f * g'
                d = sigAdd(sigMul(self(x), y), sigMul(x, self(y)));
                break;
            case kDiv:
                if (gGlobal->gDetailsSwitch) {
                    std::cout << "DIV\n";
                }
                // (f / g)' = (f' * g - f * g') / (g * g)
                d = sigDiv(sigSub(sigMul(self(x), y), sigMul(x, self(y))), sigMul(y, y));
                break;
            case kRem:
                // NB, this *is* the modulo operator (not the remainder primitive).
                if (gGlobal->gDetailsSwitch) {
                    std::cout << "REM\n";
                }
                // (f % g)' = f' - g' * floor(f / g), sin(pi * f / g) != 0
                // TODO: use `sigSelect2` to handle the indeterminate case?
                d = sigSub(self(x), sigMul(self(y), sigFloor(sigDiv(x, y))));
                break;
            case kLsh:
            case kARsh:
            case kLRsh:
                if (gGlobal->gDetailsSwitch) {
                    std::cout << "Bitshift\n";
                }
                // e.g., (f << g)' = 0, sin(pi * f / g) != 0
                d = sigZero(getCertifiedSigType(sig)->nature());
                break;
            case kGT:
            case kLT:
            case kGE:
            case kLE:
            case kEQ:
            case kNE:
            case kAND:
            case kOR:
            case kXOR:
                if (gGlobal->gDetailsSwitch) {
                    std::cout << "Binary comparison\n";
                }
                d = sigZero(getCertifiedSigType(sig)->nature());
                break;
            default:
                if (gGlobal->gDetailsSwitch) {
                    std::cout << "Unhandled sigBinOp: " << op << "\n";
                }
                d = sigBinOp(op, self(x), self(y));
                break;
        }
    }

    // init, min, max, and step must be real constant numerical expressions,
    // i.e. they are not differentiable.
    else if (isSigButton(sig, label) || isSigCheckbox(sig, label) ||
             isSigVSlider(sig, label, init, min, max, step) ||
             isSigHSlider(sig, label, init, min, max, step) ||
             isSigNumEntry(sig, label, init, min, max, step)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "UI element: " << ppsig(sig) << "\n";
        }
        d = diff(sig, getCertifiedSigType(sig)->nature());
    }

    else if (isSigInput(sig, &i)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Input: " << ppsig(sig) << "\n";
        }
        d = diff(sig, getCertifiedSigType(sig)->nature());
    }

    else if (isSigDelay1(sig, x)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Mem: "
                      << "\t" << ppsig(sig) << "\tx: " << ppsig(x) << "\n";
        }
        // Derivative of a single sample delay wrt. any parameter is the delayed
        // differentiated signal.
        d = sigDelay1(self(x));
    }

    else if (isSigDelay(sig, x, y)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Delay: "
                      << "\tx: " << ppsig(x) << "\t@y: " << ppsig(y) << "\n";
        }

        // Don't differentiate zero delay.
        if (y == sigZero(kInt)) {
            d = sigDelay0(self(x));
        } else {
            // For signal x and delay y = y(p), differentiating wrt. delay entails finding the
            // product of:
            // - the derivative wrt. time of the delayed signal and;
            // - the derivative wrt. p of y.
            // (x@y)' = (x(t - y(p)))' = d/dt(x(t - y(p)) * -d/dp(y(p))
            //
            // e.g. let x = IN[0], y(p) = p
            //     (x@y)' = d/dt(IN[0][t - p]) * -1
            //
            // For the more general case:
            //     d/dp x(t - y(p), p) = -d/dp y(p) d/dt x(t - y(p), p) + d/dp x(t - y(p), p)
            //                         = d/dp x(t - y(p), p) - d/dp y(p) d/dt x(t - y(p), p)
            //
            // e.g. let y(p) = 2p, and x(t - 2p, p) = px(t - 2p):
            //     dx/dp = x(t - 2p) - 2p d/dt x(t - 2p)
            d = sigSub(self(x), sigMul(self(y),
                                       // derivative calculated numerically wrt. sample index:
                                       // d/dn(x[n]) = (x[n] - x[n-1]) / 1
                                       // This is equivalent to convolution with a differentiated
                                       // rectangular pulse of 1-sample duration.
                                       sigSub(sigDelay(x, y), sigDelay(x, sigAdd(y, sigInt(1))))));
        }
    }

    else if (isProj(sig, &i, x)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Projection: "
                      << "\tsig: " << ppsig(sig) << "\ti: " << i << "\tx: " << ppsig(x) << "\n";
        }

        // cf. propagate.cpp:504
        d = sigProj(i, self(x));
    }

    else if (isRec(sig, var, body)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Recursion: "
                      << "\tsig: " << ppsig(sig) << "\tvar: " << extractName(var)
                      << "\tbody: " << ppsig(body) << "\n";
        }

        if (isNil(body)) {
            // we are already visiting this recursive group
            siglist l;
            l.push_back(sigDelay1(sigProj(0, ref(var))));
            //                auto var1{t1ree(unique("w"))};
            //                for (int j = 0; j < 2; j++) l[j] = sigDelay1(sigProj(j, ref(var)));

            //                d = deBruijn2Sym(rec(listConvert(l)));
            //                d = rec(var, sigDelay1(sigProj(0, sig)));
            d = rec(var, deBruijn2Sym(listConvert(l)));
        } else {
            auto myvar(tree(unique("W")));
            // first visit
            rec(var, gGlobal->nil);  // to avoid infinite recursions
            d = rec(myvar, mapselfRec(body));

            //            siglist l;
            //            l.push_back(sigDelay1(sigProj(0, ref(var))));
            //            d = rec(var, deBruijn2Sym(listConvert(l)));
        }
    }

    else if (isSigIntCast(sig, x)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Int cast: " << ppsig(sig) << "\t" << ppsig(x) << "\n";
        }
        // Acts like flooring operation. Derivative is not 0 at `sin(pi*x) != 0`,
        // but let's try this for a start.
        d = sigZero(getCertifiedSigType(x)->nature());
    } else if (isSigFloatCast(sig, x)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Float cast: " << ppsig(sig) << "\t" << ppsig(x) << "\n";
        }
        // In principle, float casting doesn't change the real value of a signal.
        d = self(x);
    } else if (isSigBitCast(sig, x)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Bit cast: " << ppsig(sig) << "\t" << ppsig(x) << "\n";
        }
        // No idea just yet.
        d = SignalIdentity::transformation(sig);
    }

    else if (isSigWRTbl(sig, w, x, y, z)) {
        if (y == gGlobal->nil) {
            // rdtable
            if (gGlobal->gDetailsSwitch) {
                tab(fIndent, cout);
                std::cout << "rdtable: " << ppsig(sig) << "\tw:" << ppsig(w) << "\tx:" << ppsig(x)
                          << "\n";
            }
            return diff(sig, getCertifiedSigType(sig)->nature());
        } else {
            // rwtable
            if (gGlobal->gDetailsSwitch) {
                tab(fIndent, cout);
                std::cout << "rwtable: " << ppsig(sig) << "\tw:" << ppsig(w) << "\tx:" << ppsig(x)
                          << "\ty:" << ppsig(y) << "\tz:" << ppsig(z) << "\n";
            }
            return diff(sig, getCertifiedSigType(sig)->nature());
        }
    } else if (isSigRDTbl(sig, x, y)) {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "rdtable: " << ppsig(sig) << "\tx:" << ppsig(x) << "\ty:" << ppsig(y)
                      << "\n";
        }
        return diff(sig, getCertifiedSigType(sig)->nature());
    }

    else {
        if (gGlobal->gDetailsSwitch) {
            tab(fIndent, cout);
            std::cout << "Unhandled case: " << ppsig(sig) << "\n";
        }
        // Other cases => identity transformation
        d = SignalIdentity::transformation(sig);
    }

    if (gGlobal->gDetailsSwitch) {
        tab(fIndent, cout);
        std::cout << "DERIVATIVE: " << ppsig(d) << "\n";
    }

    return d;
}

Tree signalAutoDifferentiate(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);

    // Collect input differentiable variables
    DiffVarCollector collector(sig);

    // Compute differentiated tree for each variable and collect the result in a list of outputs
    if (!collector.inputs.empty()) {
        siglist outputs;
        for (const auto& var : collector.inputs) {
            SignalAutoDifferentiate SP(var);
            // Insert at beginning so order of differentiated outputs matches order of
            // differentiable parameters.
            outputs.insert(outputs.begin(), hd(SP.mapself(sig)));
            if (gGlobal->gDetailsSwitch) {
                std::cout << "\n";
            }
        }
        return listConvert(outputs);
    } else {
        return sig;
    }
}
