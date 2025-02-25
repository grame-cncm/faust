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

#include "propagate.hh"
#include "Text.hh"
#include "aterm.hh"
#include "exception.hh"
#include "floats.hh"
#include "global.hh"
#include "labels.hh"
#include "names.hh"
#include "ppbox.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "sigIdentity.hh"
#include "sigvisitor.hh"
#include "simplify.hh"
#include "xtended.hh"

////////////////////////////////////////////////////////////////////////
/**
 * propagate : box listOfSignal-> listOfSignal'
 *
 * Propagate a list of signals into a box expression representing a
 * signal processor
 */
///////////////////////////////////////////////////////////////////////

using namespace std;

// Private Implementation
//------------------------

//! mix a list of signals on n bus
static siglist mix(const siglist& lsig, int nbus)
{
    int nlines = (int)lsig.size();

    siglist dst(nbus);

    for (int b = 0; b < nbus; b++) {
        Tree t = (b < nlines) ? lsig[b] : sigInt(0);
        for (int i = b + nbus; i < nlines; i += nbus) {
            t = sigAdd(t, lsig[i]);
        }
        dst[b] = t;
    }
    return dst;
}

//! split a list of signals on n bus
static siglist split(const siglist& inputs, int nbus)
{
    int nlines = (int)inputs.size();

    siglist outputs(nbus);

    for (int b = 0; b < nbus; b++) {
        outputs[b] = inputs[b % nlines];
    }
    return outputs;
}

//! build a list of n projections of a recursive group
static siglist makeSigProjList(Tree t, int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) {
        l[i] = sigDelay0(sigProj(i, t));
    }
    return l;
}

//! build a list of n mem projections of a recursive group
static siglist makeMemSigProjList(Tree clockenv, Tree t, int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) {
        l[i] = sigClocked(clockenv, sigDelay1(sigProj(i, t)));  // To be verified
        // l[i] = sigDelay1(sigProj(i, t));  // To be verified
    }
    return l;
}

static inline siglist makeList(Tree t)
{
    siglist l(1);
    l[0] = t;
    return l;
}

static siglist listRange(const siglist& l, int i, int j)
{
    siglist r(j - i);
    for (int x = i; x < j; x++) {
        r[x - i] = l[x];
    }
    return r;
}

static siglist listConcat(const siglist& a, const siglist& b)
{
    int     n1 = (int)a.size();
    int     n2 = (int)b.size();
    siglist r(n1 + n2);

    for (int x = 0; x < n1; x++) {
        r[x] = a[x];
    }
    for (int x = 0; x < n2; x++) {
        r[x + n1] = b[x];
    }
    return r;
}

/**
 * Convert a tree list of signals into an stl vector of signals
 */
static void treelist2siglist(Tree l, siglist& r)
{
    r.clear();
    while (!isNil(l)) {
        r.push_back(hd(l));
        l = tl(l);
    }
}

static siglist listLift(const siglist& l)
{
    int     n = (int)l.size();
    siglist r(n);

    for (int i = 0; i < n; i++) {
        r[i] = lift(l[i]);
    }
    return r;
}

/**
 * Store the propagation result as a property of the arguments tuplet.
 *
 * @param args propagation arguments
 * @param value propagation result
 */
static void setPropagateProperty(Tree args, const siglist& lsig)
{
    setProperty(args, tree(gGlobal->PROPAGATEPROPERTY), listConvert(lsig));
}

/**
 * Retreive the propagation result as a property of the arguments tuplet.
 *
 * @param args propagation arguments
 * @param lsig the propagation result if any
 * @return true if a propagation result was stored
 */
static bool getPropagateProperty(Tree args, siglist& lsig)
{
    Tree value;
    if (getProperty(args, tree(gGlobal->PROPAGATEPROPERTY), value)) {
        treelist2siglist(value, lsig);
        return true;
    } else {
        return false;
    }
}

/**
 * Propagate a list of signals into a block diagram.
 *
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */
static siglist realPropagate(Tree clockenv, Tree slotenv, Tree path, Tree box, const siglist& lsig);

// Collect the leaf numbers of tree l into vector v.
// return true if l is a number or a parallel tree of numbers.
static bool isIntTree(Tree l, vector<int>& v)
{
    int    n;
    double r;
    Tree   x, y;

    if (isBoxInt(l, &n)) {
        v.push_back(n);
        return true;

    } else if (isBoxReal(l, &r)) {
        v.push_back(int(r));
        return true;

    } else if (isBoxPar(l, x, y)) {
        return isIntTree(x, v) && isIntTree(y, v);

    } else {
        stringstream error;
        error << "ERROR : file " << __FILE__ << ':' << __LINE__
              << ", not a valid list of numbers : " << boxpp(l) << endl;
        throw faustexception(error.str());
    }
}

/**
 * Propagate a list of signals into a block diagram. Actual function.
 *
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */
static siglist realPropagate(Tree clockenv, Tree slotenv, Tree path, Tree box, const siglist& lsig)
{
    int    i;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    Tree t1, t2, t3, ff, label, cur, min, max, step, type, name, file, slot, body, chan;
    tvec wf;

    xtended* xt = (xtended*)getUserData(box);

    // Extended Primitives

    if (xt) {
        faustassert(lsig.size() == xt->arity());
        return makeList(xt->computeSigOutput(lsig));
    }

    // Numbers and Constants

    else if (isBoxInt(box, &i)) {
        faustassert(lsig.size() == 0);
        return makeList(sigInt(i));
    } else if (isBoxReal(box, &r)) {
        faustassert(lsig.size() == 0);
        return makeList(sigReal(r));
    }

    // A Waveform has two outputs it size and a period signal representing its content

    else if (isBoxWaveform(box)) {
        faustassert(lsig.size() == 0);
        tvec br = box->branches();
        // ONDEMAND: We make sure that the waveform is only for
        // the current time reference by adding a clock signal
        // to the first value (it's enough)
        br[0] = sigClocked(clockenv, br[0]);  // Make sure
        return listConcat(makeList(sigInt(int(br.size()))), makeList(sigWaveform(br)));
    }

    else if (isBoxFConst(box, type, name, file)) {
        faustassert(lsig.size() == 0);

        // Specific case for sampling rate (ma.SR)
        string vname = string(tree2str(name));
        if ((clockenv != gGlobal->nil) &&
            ((vname == "fSamplingFreq") || (vname == "fSamplingRate"))) {
            Tree adapted_sr = sigFConst(type, name, file);
            Tree clocks     = clockenv;
            // Unroll the stack of all US/DS to compute the adapted SR
            do {
                Tree sr_factor = hd(clocks);
                Tree us_ds     = hd(tl(clocks));
                if (us_ds == tree("Upsampling")) {
                    adapted_sr = sigMul(adapted_sr, sr_factor);
                } else if (us_ds == tree("Downsampling")) {
                    adapted_sr = sigDiv(adapted_sr, sr_factor);
                }
                clocks = tl(tl(clocks));
            } while (clocks != gGlobal->nil);

            return makeList(simplify(adapted_sr));
        }

        return makeList(sigFConst(type, name, file));
    }

    else if (isBoxFVar(box, type, name, file)) {
        faustassert(lsig.size() == 0);
        return makeList(sigFVar(type, name, file));
    }

    // Wire and Cut

    else if (isBoxCut(box)) {
        faustassert(lsig.size() == 1);
        return siglist();
    }

    else if (isBoxWire(box)) {
        faustassert(lsig.size() == 1);
        return lsig;
    }

    // Slots and Symbolic Boxes

    else if (isBoxSlot(box)) {
        Tree sig;
        faustassert(lsig.size() == 0);
        if (!searchEnv(box, sig, slotenv)) {
            sig = sigInput(++gGlobal->gDummyInput);
        }
        return makeList(sig);
    }

    else if (isBoxSymbolic(box, slot, body)) {
        faustassert(lsig.size() > 0);
        return propagate(clockenv, pushEnv(slot, lsig[0], slotenv), path, body,
                         listRange(lsig, 1, (int)lsig.size()));
    }

    // Primitives

    else if (isBoxPrim0(box, &p0)) {
        faustassert(lsig.size() == 0);
        return makeList(p0());
    }

    else if (isBoxPrim1(box, &p1)) {
        faustassert(lsig.size() == 1);
        if (p1 == &sigDelay1) {
            return makeList(sigDelay1(sigClocked(clockenv, lsig[0])));
        }
        num n;
        if (isNum(lsig[0], n)) {
            return makeList(simplify(p1(lsig[0])));
        } else {
            return makeList(p1(lsig[0]));
        }
    }

    else if (isBoxPrim2(box, &p2)) {
        // cerr << "prim2 receive : " << ppsig(lsig) << endl;
        faustassert(lsig.size() == 2);
        if (p2 == &sigEnable) {
            if (gGlobal->gEnableFlag) {
                // special case for sigEnable that requires a transformation
                // enable(X,Y) -> sigControl(X*Y, Y!=0)
                return makeList(sigControl(sigMul(lsig[0], lsig[1]), sigNE(lsig[1], sigReal(0.0))));
            } else {
                // If gEnableFlag is false we replace enable by a simple multiplication
                return makeList(sigMul(lsig[0], lsig[1]));
            }
        } else if (p2 == &sigControl) {
            if (gGlobal->gEnableFlag) {
                // special case for sigControl that requires a transformation
                // control(X,Y) -> sigControl(X, Y!=0)
                return makeList(sigControl(lsig[0], sigNE(lsig[1], sigReal(0.0))));
            } else {
                // If gEnableFlag is false we replace control by identity function
                return makeList(lsig[0]);
            }
        } else if (p2 == &sigDelay) {
            return makeList(sigDelay(sigClocked(clockenv, lsig[0]), lsig[1]));

        } else if (p2 == &sigPrefix) {
            return makeList(sigPrefix(lsig[0], sigClocked(clockenv, lsig[1])));

        } else {
            num n, m;
            if (isNum(lsig[0], n) && isNum(lsig[1], m)) {
                return makeList(simplify(p2(lsig[0], lsig[1])));
            } else {
                return makeList(p2(lsig[0], lsig[1]));
            }
        }
    }

    else if (isBoxPrim3(box, &p3)) {
        faustassert(lsig.size() == 3);
        if (p3 == sigReadOnlyTable) {
            /*
            Tree sig = sigReadOnlyTable(unclockSignal(lsig[0]), unclockSignal(lsig[1]),
                                        sigClocked(clockenv, lsig[2]));
            */
            Tree sig = sigReadOnlyTable(lsig[0], lsig[1], sigClocked(clockenv, lsig[2]));
            // std::cout << "sigReadOnlyTable : " << ppsig(sig) << std::endl;
            return makeList(sig);
        }
        return makeList(p3(lsig[0], lsig[1], lsig[2]));
    }

    else if (isBoxPrim4(box, &p4)) {
        faustassert(lsig.size() == 4);
        return makeList(p4(lsig[0], lsig[1], lsig[2], lsig[3]));
    }

    else if (isBoxPrim5(box, &p5)) {
        if (p5 == sigWriteReadTable) {
            Tree sig =
                sigWriteReadTable(lsig[0], lsig[1], sigClocked(clockenv, lsig[2]),
                                  sigClocked(clockenv, lsig[3]), sigClocked(clockenv, lsig[4]));
            // std::cout << "sigWriteReadTable : " << ppsig(sig) << std::endl;
            return makeList(sig);
        }
        return makeList(p5(lsig[0], lsig[1], lsig[2], lsig[3], lsig[4]));
    }

    else if (isBoxFFun(box, ff)) {
        faustassert(int(lsig.size()) == ffarity(ff));
        return makeList(sigFFun(ff, listConvert(lsig)));
    }

    // User Interface Widgets

    else if (isBoxButton(box, label)) {
        faustassert(lsig.size() == 0);
        return makeList(sigButton(normalizePath(cons(label, path))));
    }

    else if (isBoxCheckbox(box, label)) {
        faustassert(lsig.size() == 0);
        return makeList(sigCheckbox(normalizePath(cons(label, path))));
    }

    else if (isBoxVSlider(box, label, cur, min, max, step)) {
        faustassert(lsig.size() == 0);
        return makeList(sigVSlider(normalizePath(cons(label, path)), cur, min, max, step));
    }

    else if (isBoxHSlider(box, label, cur, min, max, step)) {
        faustassert(lsig.size() == 0);
        return makeList(sigHSlider(normalizePath(cons(label, path)), cur, min, max, step));
    }

    else if (isBoxNumEntry(box, label, cur, min, max, step)) {
        faustassert(lsig.size() == 0);
        return makeList(sigNumEntry(normalizePath(cons(label, path)), cur, min, max, step));
    }

    else if (isBoxVBargraph(box, label, min, max)) {
        faustassert(lsig.size() == 1);
        // we add a clock signal so that we know, when we compile a bargraph,
        // if it occurs in an ondemand
        return makeList(sigVBargraph(normalizePath(cons(label, path)), min, max,
                                     sigClocked(clockenv, lsig[0])));
    }

    else if (isBoxHBargraph(box, label, min, max)) {
        faustassert(lsig.size() == 1);
        // we add a clock signal so that we know, when we compile a bargraph,
        // if it occurs in an ondemand
        return makeList(sigHBargraph(normalizePath(cons(label, path)), min, max,
                                     sigClocked(clockenv, lsig[0])));
    }

    else if (isBoxSoundfile(box, label, chan)) {
        faustassert(lsig.size() == 2);
        Tree    soundfile = sigSoundfile(normalizePath(cons(label, path)));
        Tree    part      = lsig[0];
        int     c         = tree2int(chan);
        siglist lsig2(c + 2);
        lsig2[0] = sigSoundfileLength(soundfile, part);
        lsig2[1] = sigSoundfileRate(soundfile, part);

        // compute bound limited read index : int(max(0, min(ridx,length-1)))
        Tree ridx = sigMax(sigInt(0), sigMin(lsig[1], sigSub(lsig2[0], sigInt(1))));
        for (int i1 = 0; i1 < c; i1++) {
            lsig2[i1 + 2] = sigSoundfileBuffer(soundfile, sigInt(i1), part, ridx);
        }
        return lsig2;
    }

    // User Interface Groups

    else if (isBoxVGroup(box, label, t1)) {
        return propagate(clockenv, slotenv, cons(cons(tree(0), label), path), t1, lsig);
    }

    else if (isBoxHGroup(box, label, t1)) {
        return propagate(clockenv, slotenv, cons(cons(tree(1), label), path), t1, lsig);
    }

    else if (isBoxTGroup(box, label, t1)) {
        return propagate(clockenv, slotenv, cons(cons(tree(2), label), path), t1, lsig);
    }

    // Block Diagram Composition Algebra

    else if (isBoxSeq(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // Connection coherency is checked in evaluateBlockDiagram
        faustassert(out1 == in2);
        return propagate(clockenv, slotenv, path, t2, propagate(clockenv, slotenv, path, t1, lsig));
    }

    else if (isBoxPar(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // No restriction in connection
        return listConcat(propagate(clockenv, slotenv, path, t1, listRange(lsig, 0, in1)),
                          propagate(clockenv, slotenv, path, t2, listRange(lsig, in1, in1 + in2)));
    }

    else if (isBoxSplit(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // Connection coherency is checked in evaluateBlockDiagram
        siglist l1 = propagate(clockenv, slotenv, path, t1, lsig);
        siglist l2 = split(l1, in2);
        return propagate(clockenv, slotenv, path, t2, l2);
    }

    else if (isBoxMerge(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // Connection coherency is checked in evaluateBlockDiagram
        siglist l1 = propagate(clockenv, slotenv, path, t1, lsig);
        siglist l2 = mix(l1, in2);
        return propagate(clockenv, slotenv, path, t2, l2);
    }

    else if (isBoxRec(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // The environment must also be lifted
        Tree slotenv2 = lift(slotenv);

        // Connection coherency is checked in evaluateBlockDiagram
        siglist l0 = makeMemSigProjList(clockenv, ref(1), in2);
        siglist l1 = propagate(clockenv, slotenv2, path, t2, l0);
        siglist l2 = propagate(clockenv, slotenv2, path, t1, listConcat(l1, listLift(lsig)));
        Tree    g  = rec(listConvert(l2));

        // Compute output list of recursive signals
        siglist ol(out1);  // output list
        int     p = 0;     // projection number

        for (const auto& exp : l2) {
            if (exp->aperture() > 0) {
                // it is a regular recursive expression branch
                ol[p] = sigDelay0(sigProj(p, g));
            } else {
                // this expression is a closed term,
                // it doesn't need to be inside this recursion group.
                // cerr << "degenerate recursion " << exp << endl;
                ol[p] = exp;
            }
            p++;
        }

        return ol;
    }

    else if (isBoxEnvironment(box)) {
        faustassert(lsig.size() == 0);
        return siglist();

    } else if (isBoxRoute(box, t1, t2, t3)) {
        int         ins, outs;
        vector<int> route;
        siglist     outsigs;
        // ins, outs, route are casted to int in realeval
        if (isBoxInt(t1, &ins) && isBoxInt(t2, &outs) && isIntTree(t3, route)) {
            // initialize output signals
            for (int i1 = 0; i1 < outs; i1++) {
                outsigs.push_back(sigInt(0));
            }

            // route propagation
            size_t m = route.size() - 1;
            for (size_t i1 = 0; i1 < m; i1 += 2) {
                int src = route[i1];
                int dst = route[i1 + 1];
                if ((dst > 0) & (dst <= outs)) {
                    // we have a destination
                    Tree exp = outsigs[dst - 1];
                    if ((src > 0) & (src <= ins)) {
                        // we have a source
                        outsigs[dst - 1] = simplifyingAdd(exp, lsig[src - 1]);
                    }
                }
            }
            return outsigs;

        } else {
            stringstream error;
            error << "ERROR : file " << __FILE__ << ':' << __LINE__
                  << ", invalid route expression : " << boxpp(box) << endl;
            throw faustexception(error.str());
        }

    } else if (isBoxOndemand(box, t1)) {
        // std::cerr << "we are in ONDEMAND" << std::endl;
        // Propagate lsig into the ondemand version of circuit t1

        // 1/ The first signal is the clock signal
        Tree H = lsig[0];

        // We check if the clock signal is a constant
        bool h0 = false;  // clock signal is zero constant
        bool h1 = false;  // clock signal is non-zero constant

        if (double f; isSigReal(H, &f)) {
            h0 = int(f) == 0;
            h1 = int(f) == 1;
        } else if (int n; isSigInt(H, &n)) {
            h0 = n == 0;
            h1 = n == 1;
        }

        // 2/ We check for trivial cases where we don't need the ondemand circuit
        if (h0) {
            // std::cerr
            //     << "If the clock signal is zero, we don't need to compute the ondemand circuit"
            //     << std::endl;
            int n, m;
            getBoxType(t1, &n, &m);
            // because the cicuit is never activated, its m outputs will remain zero
            return siglist(m, sigInt(0));
        }
        if (h1) {
            // std::cerr << "If the clock signal is one, we don't need an if" << std::endl;
            return propagate(clockenv, slotenv, path, t1, {lsig.begin() + 1, lsig.end()});
        }

        // 3/ We compute the clock environment inside the ondemand by combining the clock, the
        // address of the circuit, and the current clock environment
        Tree addr      = boxPrim0((prim0)box);
        Tree clockenv2 = cons(H, cons(addr, clockenv));

        // 4/ We compute X1 the inputs of the ondemand using temporary variables
        siglist X1;
        for (unsigned int i = 1; i < lsig.size(); i++) {
            X1.push_back(sigTempVar(lsig[i]));
        }

        // 5/ We propagate X2, the clocked version of X1, into the ondemand circuit -> Y0
        siglist X2;
        for (Tree s : X1) {
            X2.push_back(sigClocked(clockenv2, s));
        }
        siglist Y0 = propagate(clockenv2, slotenv, path, t1, X2);

        // 6/ We store the Y0 output signals into perm variables -> Y1
        siglist Y1;
        for (unsigned int i = 0; i < Y0.size(); i++) {
            Y1.push_back(sigPermVar(sigClocked(clockenv2, Y0[i])));
        }

        // 7/ We create on ondemand signal that contain all the information : OD = (H, X1, NIL, Y1)
        tvec W;
        W.push_back(H);      // the clock signal
        for (Tree s : X1) {  // the input signals are X1
            W.push_back(s);
        }
        W.push_back(gGlobal->nil);  // the output signals are Y1
        for (Tree s : Y1) {
            W.push_back(s);
        }
        // The resulting ondemand signal with all the information
        Tree od = sigOD(W);
        // std::cerr << "od = " << ppsig(od) << std::endl;

        // 8/ Finally, we create the output signals making sure that od is computed first
        // using sigSeq(od, y)
        siglist Y2;
        for (Tree y : Y1) {
            Tree y2 = sigSeq(od, y);
            // Tree y2 = sigSeq(od, sigClocked(clockenv, y));
            //  std::cerr << "y2 = " << ppsig(y2) << std::endl;
            Y2.push_back(y2);
        }

        return Y2;

    } else if (isBoxUpsampling(box, t1)) {
        // std::cerr << "we are in UPSAMPLING" << std::endl;
        // Propagate lsig into the upsampled version of circuit t1

        // 1/ The first signal is the clock signal
        Tree H = lsig[0];
        
        // We check if the clock signal is a constant
        bool h0 = false;  // clock signal is zero constant
        bool h1 = false;  // clock signal is non-zero constant
        
        if (double f; isSigReal(H, &f)) {
            h0 = int(f) == 0;
            h1 = int(f) == 1;
        } else if (int n; isSigInt(H, &n)) {
            h0 = n == 0;
            h1 = n == 1;
        }
        
        // 2/ We check for trivial cases where we don't need the upsampling circuit
        if (h0) {
            // std::cerr
            //     << "If the clock signal is zero, we don't need to compute the upsampling circuit"
            //     << std::endl;
            int n, m;
            getBoxType(t1, &n, &m);
            // because the cicuit is never activated, its m outputs will remain zero
            return siglist(m, sigInt(0));
        }
        if (h1) {
            // std::cerr << "If the clock signal is one, we don't need an if" << std::endl;
            return propagate(clockenv, slotenv, path, t1, {lsig.begin() + 1, lsig.end()});
        }

        /*
        int up_factor;
        if (isSigInt(H, &up_factor)) {
            if (up_factor <= 1) {
                throw faustexception("ERROR : upsampling parameter must be an integer > 1\n");
            }
        } else {
            throw faustexception("ERROR : upsampling parameter must be an integer\n");
        }
        */

        // 3/ We compute the clock environment inside the upsampling by combining the clock, the
        // address of the circuit, and the current clock environment
        Tree addr = boxPrim0((prim0)box);
        // Tree clockenv2 = cons(H, cons(addr, clockenv));
        Tree clockenv2 = cons(H, cons(tree("Upsampling"), clockenv));

        // 4/ We compute X1 the inputs of the upsampling using temporary variables
        siglist X1;
        for (unsigned int i = 1; i < lsig.size(); i++) {
            // X1.push_back(sigZeroPad(sigTempVar(lsig[i]), sigInt(up_factor)));
            X1.push_back(sigZeroPad(sigTempVar(lsig[i]), H));
        }

        // 5/ We propagate X2, the clocked version of X1, into the upsampling circuit -> Y0
        siglist X2;
        for (Tree s : X1) {
            X2.push_back(sigClocked(clockenv2, s));
        }
        siglist Y0 = propagate(clockenv2, slotenv, path, t1, X2);

        // 6/ We store the Y0 output signals into perm variables -> Y1
        siglist Y1;
        for (unsigned int i = 0; i < Y0.size(); i++) {
            Y1.push_back(sigPermVar(sigClocked(clockenv2, Y0[i])));
        }

        // 7/ We create on us signal that contain all the information : US = (H, X1, NIL, Y1)
        tvec W;
        W.push_back(H);      // the clock signal
        for (Tree s : X1) {  // the input signals are X1
            W.push_back(s);
        }
        W.push_back(gGlobal->nil);  // the output signals are Y1
        for (Tree s : Y1) {
            W.push_back(s);
        }
        // The resulting upsampled signal with all the information
        Tree us = sigUS(W);
        // std::cerr << "us = " << ppsig(us) << std::endl;

        // 8/ Finally, we create the output signals making sure that us is computed first
        // using sigSeq(us, y)
        siglist Y2;
        for (Tree y : Y1) {
            Tree y2 = sigSeq(us, y);
            // Tree y2 = sigSeq(us, sigClocked(clockenv, y));
            //  std::cerr << "y2 = " << ppsig(y2) << std::endl;
            Y2.push_back(y2);
        }

        return Y2;
    } else if (isBoxDownsampling(box, t1)) {
        // std::cerr << "we are in DOWNSAMPLING" << std::endl;
        // Propagate lsig into the downsampled version of circuit t1

        // 1/ The first signal is the clock signal
        Tree H = lsig[0];
        
        // We check if the clock signal is a constant
        bool h0 = false;  // clock signal is zero constant
        bool h1 = false;  // clock signal is non-zero constant

        if (double f; isSigReal(H, &f)) {
            h0 = int(f) == 0;
            h1 = int(f) == 1;
        } else if (int n; isSigInt(H, &n)) {
            h0 = n == 0;
            h1 = n == 1;
        }
        
        // 2/ We check for trivial cases where we don't need the downsampling circuit
        if (h0) {
            // std::cerr
            //     << "If the clock signal is zero, we don't need to compute the downsampling circuit"
            //     << std::endl;
            int n, m;
            getBoxType(t1, &n, &m);
            // because the cicuit is never activated, its m outputs will remain zero
            return siglist(m, sigInt(0));
        }
        if (h1) {
            // std::cerr << "If the clock signal is one, we don't need an if" << std::endl;
            return propagate(clockenv, slotenv, path, t1, {lsig.begin() + 1, lsig.end()});
        }
        
        /*
        int ds_factor;
        if (isSigInt(H, &ds_factor)) {
            if (ds_factor <= 1) {
                throw faustexception("ERROR : downsampling parameter must be an integer > 1\n");
            }
        } else {
            throw faustexception("ERROR : downsampling parameter must be an integer\n");
        }
        */

        // 3/ We compute the clock environment inside the downsampling by combining the clock, the
        // address of the circuit, and the current clock environment
        Tree addr = boxPrim0((prim0)box);
        // Tree clockenv2 = cons(H, cons(addr, clockenv));
        Tree clockenv2 = cons(H, cons(tree("Downsampling"), clockenv));

        // 4/ We compute X1 the inputs of the downsampling using temporary variables
        siglist X1;
        for (unsigned int i = 1; i < lsig.size(); i++) {
            X1.push_back(sigTempVar(lsig[i]));
        }

        // 5/ We propagate X2, the clocked version of X1, into the downsampling circuit -> Y0
        siglist X2;
        for (Tree s : X1) {
            // X2.push_back(sigClocked(clockenv2, sigDecimate(s, sigInt(ds_factor))));
            X2.push_back(sigClocked(clockenv2, sigDecimate(s, H)));
        }
        siglist Y0 = propagate(clockenv2, slotenv, path, t1, X2);

        // 6/ We store the Y0 output signals into perm variables -> Y1
        siglist Y1;
        for (unsigned int i = 0; i < Y0.size(); i++) {
            Y1.push_back(sigPermVar(sigClocked(clockenv2, Y0[i])));
        }

        // 7/ We create on ds signal that contain all the information : DS = (H, X1, NIL, Y1)
        tvec W;
        W.push_back(H);      // the clock signal
        for (Tree s : X1) {  // the input signals are X1
            W.push_back(s);
        }
        W.push_back(gGlobal->nil);  // the output signals are Y1
        for (Tree s : Y1) {
            W.push_back(s);
        }
        // The resulting downsampled signal with all the information
        Tree ds = sigDS(W);
        // std::cerr << "ds = " << ppsig(ds) << std::endl;

        // 8/ Finally, we create the output signals making sure that ds is computed first
        // using sigSeq(ds, y)
        siglist Y2;
        for (Tree y : Y1) {
            Tree y2 = sigSeq(ds, y);
            // Tree y2 = sigSeq(od, sigClocked(clockenv, y));
            //  std::cerr << "y2 = " << ppsig(y2) << std::endl;
            Y2.push_back(y2);
        }

        return Y2;
    }

    cerr << "ASSERT : file " << __FILE__ << ':' << __LINE__
         << ", unrecognised box expression : " << boxpp(box) << endl;
    faustassert(false);

    return siglist();
}

//------------------
// Public Interface
//------------------

/**
 * Propagate a list of signals into a block diagram. Do memoization.
 *
 * @param clockenv surronnding ondemand clock
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */

siglist propagate(Tree clockenv, Tree slotenv, Tree path, Tree box, const siglist& lsig)
{
    Tree args = tree(gGlobal->PROPAGATEPROPERTY, clockenv, slotenv, path, box, listConvert(lsig));
    siglist result;
    if (!getPropagateProperty(args, result)) {
        // cerr << "propagate within clock " << *clockenv << " into " << boxpp(box) << endl;
        // for (int i = 0; i < lsig.size(); i++) {
        //     cerr << " -> signal " << i << " : " << *(lsig[i]) << endl;
        // }
        // cerr << endl;

        result = realPropagate(clockenv, slotenv, path, box, lsig);
        setPropagateProperty(args, result);
        // cerr << "propagate within clock " << *clockenv << " into " << boxpp(box) << endl;
        // for (int i = 0; i < result.size(); i++) {
        //     cerr << " -> result " << i << " : " << *(result[i]) << endl;
        // }
        // cerr << endl;
    }
    // cerr << "propagate in " << boxpp(box) << endl;
    // for (int i = 0; i < lsig.size(); i++) { cerr << " -> signal " << i << " : " << *(lsig[i]) <<
    // endl; } cerr << endl;
    return result;
}

//! build a list of n inputs
siglist makeSigInputList(int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) {
        l[i] = sigClocked(gGlobal->nil, sigInput(i));
    }
    return l;
}
/**
 * Top level propagate a list of signals into a block diagram. Do memoization.
 *
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */

Tree boxPropagateSig(Tree path, Tree box, const siglist& lsig)
{
    return listConvert(propagate(gGlobal->nil, gGlobal->nil, path, box, lsig));
}
