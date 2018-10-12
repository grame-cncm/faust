/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "propagate.hh"
#include "Text.hh"
#include "exception.hh"
#include "floats.hh"
#include "global.hh"
#include "labels.hh"
#include "names.hh"
#include "ppbox.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "simplify.hh"
#include "xtended.hh"

////////////////////////////////////////////////////////////////////////
/**
 * propagate : box listOfSignal-> listOfSignal'
 *
 * Propage a list of signals into a box expression representing a
 * signal processor
 */
///////////////////////////////////////////////////////////////////////

//! mix une liste de signaux sur n bus
siglist mix(const siglist& lsig, int nbus)
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

//! split une liste de signaux sur n bus
siglist split(const siglist& inputs, int nbus)
{
    int nlines = (int)inputs.size();

    siglist outputs(nbus);

    for (int b = 0; b < nbus; b++) {
        outputs[b] = inputs[b % nlines];
    }
    return outputs;
}

//! Fabrique une liste de n projections d'un groupe récursif
siglist makeSigProjList(Tree t, int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) l[i] = sigDelay0(sigProj(i, t));
    return l;
}

//! Fabrique une liste de n mem projections d'un groupe récursif
siglist makeMemSigProjList(Tree t, int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) l[i] = sigDelay1(sigProj(i, t));
    return l;
}

//! Fabrique une liste de n entrées
siglist makeSigInputList(int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) l[i] = sigInput(i);
    return l;
}

inline siglist makeList(Tree t)
{
    siglist l(1);
    l[0] = t;
    return l;
}

siglist listRange(const siglist& l, int i, int j)
{
    siglist r(j - i);
    for (int x = i; x < j; x++) r[x - i] = l[x];
    return r;
}

siglist listConcat(const siglist& a, const siglist& b)
{
    int     n1 = (int)a.size();
    int     n2 = (int)b.size();
    siglist r(n1 + n2);

    for (int x = 0; x < n1; x++) r[x] = a[x];
    for (int x = 0; x < n2; x++) r[x + n1] = b[x];
    return r;
}

/**
 * Convert an stl list of signals into a tree list of signals
 */
Tree listConvert(const siglist& a)
{
    int  n = (int)a.size();
    Tree t = gGlobal->nil;

    while (n--) t = cons(a[n], t);
    return t;
}

/**
 * Convert a tree list of signals into an stl list of signals
 */
void treelist2siglist(Tree l, siglist& r)
{
    r.clear();
    while (!isNil(l)) {
        r.push_back(hd(l));
        l = tl(l);
    }
}

siglist listLift(const siglist& l)
{
    int     n = (int)l.size();
    siglist r(n);

    for (int i = 0; i < n; i++) r[i] = lift(l[i]);
    return r;
}

/**
 * Propagate computes the outputs signals of a block-diagram according to a list of input signals.
 *
 *\param slotenv input signals associated with symbolic slots
 *\param path stack of user interface groups : (type,label)*
 *\param box block-diagram where we propagate the signals
 *\param lsig list of signals to be propagated into box
 *\return list of resulting signals
 */

/**
 * Store the propagation result as a property of the arguments tuplet
 * @param args propagation arguments
 * @param value propagation result
 */
void setPropagateProperty(Tree args, const siglist& lsig)
{
    setProperty(args, tree(gGlobal->PROPAGATEPROPERTY), listConvert(lsig));
}

/**
 * Retreive the propagation result as a property of the arguments tuplet
 * @param args propagation arguments
 * @param lsig the propagation result if any
 * @return true if a propagation result was stored
 */
bool getPropagateProperty(Tree args, siglist& lsig)
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
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */

siglist realPropagate(Tree slotenv, Tree path, Tree box, const siglist& lsig);

/**
 * Propagate a list of signals into a block diagram. Do memoization.
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */

siglist propagate(Tree slotenv, Tree path, Tree box, const siglist& lsig)
{
    Tree    args = tree(gGlobal->PROPAGATEPROPERTY, slotenv, path, box, listConvert(lsig));
    siglist result;
    if (!getPropagateProperty(args, result)) {
        result = realPropagate(slotenv, path, box, lsig);
        setPropagateProperty(args, result);
    }
    // cerr << "propagate in " << boxpp(box) << endl;
    // for (int i=0; i<lsig.size(); i++) { cerr << " -> signal " << i << " : " << *(lsig[i]) << endl; }
    // cerr << endl;
    return result;
}

// Apply sigFTZ() to all signals of a vector
static siglist wrapWithFTZ(const siglist& l1)
{
    siglist l2;
    for (auto x : l1) {
        l2.push_back(sigFTZ(x));
    }
    return l2;
}

/**
 * Propagate a list of signals into a block diagram. Actual function.
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */

siglist realPropagate(Tree slotenv, Tree path, Tree box, const siglist& lsig)
{
    int    i;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    Tree t1, t2, ff, label, cur, min, max, step, type, name, file, slot, body, chan;
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
        const tvec br = box->branches();
        return listConcat(makeList(sigInt(int(br.size()))), makeList(sigWaveform(br)));
    }

    else if (isBoxFConst(box, type, name, file)) {
        faustassert(lsig.size() == 0);
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
            // test YO simplification des diagrammes
            // fprintf(stderr, "propagate : internal error (slot undefined)\n");
            sig = sigInput(++gGlobal->gDummyInput);
        }
        return makeList(sig);
    }

    else if (isBoxSymbolic(box, slot, body)) {
        faustassert(lsig.size() > 0);
        return propagate(pushEnv(slot, lsig[0], slotenv), path, body, listRange(lsig, 1, (int)lsig.size()));
    }

    // Primitives

    else if (isBoxPrim0(box, &p0)) {
        faustassert(lsig.size() == 0);
        return makeList(p0());
    }

    else if (isBoxPrim1(box, &p1)) {
        faustassert(lsig.size() == 1);
        num n;
        if (isNum(lsig[0], n)) {
            // cerr << "simplify 335" << endl;
            return makeList(simplify(p1(lsig[0])));
        } else {
            return makeList(p1(lsig[0]));
        }
    }

    else if (isBoxPrim2(box, &p2)) {
        //		printf("prim2 recoit : "); print(lsig); printf("\n");
        faustassert(lsig.size() == 2);
        if (p2 == &sigEnable) {
            if (gGlobal->gEnableFlag) {
                // special case for sigEnable that requires a transformation
                // enable(X,Y) -> sigEnable(X*Y, Y!=0)
                return makeList(sigEnable(sigMul(lsig[0], lsig[1]), sigNE(lsig[1], sigReal(0.0))));
            } else {
                // We gEnableFlag is false we replace enable by a simple multiplication
                return makeList(sigMul(lsig[0], lsig[1]));
            }
        } else if (p2 == &sigControl) {
            if (gGlobal->gEnableFlag) {
                // special case for sigControl that requires a transformation
                // control(X,Y) -> sigEnable(X, Y!=0)
                return makeList(sigEnable(lsig[0], sigNE(lsig[1], sigReal(0.0))));
            } else {
                // If gEnableFlag is false we replace control by identity function
                return makeList(lsig[0]);
            }
        } else {
            num n, m;
            if (isNum(lsig[0], n) && isNum(lsig[1], m)) {
                // cerr << "simplify 369" << endl;
                return makeList(simplify(p2(lsig[0], lsig[1])));
            } else {
                return makeList(p2(lsig[0], lsig[1]));
            }
        }
    }

    else if (isBoxPrim3(box, &p3)) {
        faustassert(lsig.size() == 3);
        return makeList(p3(lsig[0], lsig[1], lsig[2]));
    }

    else if (isBoxPrim4(box, &p4)) {
        faustassert(lsig.size() == 4);
        return makeList(p4(lsig[0], lsig[1], lsig[2], lsig[3]));
    }

    else if (isBoxPrim5(box, &p5)) {
        faustassert(lsig.size() == 5);
        return makeList(p5(lsig[0], lsig[1], lsig[2], lsig[3], lsig[4]));
    }

    else if (isBoxFFun(box, ff)) {
        // cerr << "propagate en boxFFun of arity " << ffarity(ff) << endl;
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
        return makeList(sigVBargraph(normalizePath(cons(label, path)), min, max, lsig[0]));
    }

    else if (isBoxHBargraph(box, label, min, max)) {
        faustassert(lsig.size() == 1);
        return makeList(sigHBargraph(normalizePath(cons(label, path)), min, max, lsig[0]));
    }

    else if (isBoxSoundfile(box, label, chan)) {
        faustassert(lsig.size() == 2);
        Tree    soundfile = sigSoundfile(normalizePath(cons(label, path)));
        Tree    part      = sigIntCast(lsig[0]);
        int     c         = tree2int(chan);
        siglist lsig2(c + 2);
        lsig2[0] = sigSoundfileLength(soundfile, part);
        lsig2[1] = sigSoundfileRate(soundfile, part);

        // compute bound limited read index : int(max(0, min(ridx,length-1)))
        Tree ridx = sigIntCast(tree(gGlobal->gMaxPrim->symbol(), sigInt(0),
                                    tree(gGlobal->gMinPrim->symbol(), lsig[1], sigAdd(lsig2[0], sigInt(-1)))));
        for (int i = 0; i < c; i++) {
            lsig2[i + 2] = sigSoundfileBuffer(soundfile, sigInt(i), part, ridx);
        }
        return lsig2;
    }

    // User Interface Groups

    else if (isBoxVGroup(box, label, t1)) {
        return propagate(slotenv, cons(cons(tree(0), label), path), t1, lsig);
    }

    else if (isBoxHGroup(box, label, t1)) {
        return propagate(slotenv, cons(cons(tree(1), label), path), t1, lsig);
    }

    else if (isBoxTGroup(box, label, t1)) {
        return propagate(slotenv, cons(cons(tree(2), label), path), t1, lsig);
    }

    // Block Diagram Composition Algebra

    else if (isBoxSeq(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        faustassert(out1 == in2);

        if (out1 == in2) {
            return propagate(slotenv, path, t2, propagate(slotenv, path, t1, lsig));
        } else if (out1 > in2) {
            siglist lr = propagate(slotenv, path, t1, lsig);
            return listConcat(propagate(slotenv, path, t2, listRange(lr, 0, in2)), listRange(lr, in2, out1));
        } else {
            return propagate(slotenv, path, t2,
                             listConcat(propagate(slotenv, path, t1, listRange(lsig, 0, in1)),
                                        listRange(lsig, in1, in1 + in2 - out1)));
        }
    }

    else if (isBoxPar(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        return listConcat(propagate(slotenv, path, t1, listRange(lsig, 0, in1)),
                          propagate(slotenv, path, t2, listRange(lsig, in1, in1 + in2)));
    }

    else if (isBoxSplit(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        siglist l1 = propagate(slotenv, path, t1, lsig);
        siglist l2 = split(l1, in2);
        return propagate(slotenv, path, t2, l2);
    }

    else if (isBoxMerge(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        siglist l1 = propagate(slotenv, path, t1, lsig);
        siglist l2 = mix(l1, in2);
        return propagate(slotenv, path, t2, l2);
    }

    else if (isBoxRec(box, t1, t2)) {
        // Bug Corrected
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        Tree slotenv2 = lift(slotenv);  // the environment must also be lifted

        siglist l0 = makeMemSigProjList(ref(1), in2);
        siglist l1 = propagate(slotenv2, path, t2, l0);
        siglist l2 = propagate(slotenv2, path, t1, listConcat(l1, listLift(lsig)));
        siglist l3 = (gGlobal->gFTZMode > 0) ? wrapWithFTZ(l2) : l2;
        Tree    g  = rec(listConvert(l3));

        // compute output list of recursive signals
        siglist ol(out1);  // output list
        int     p = 0;     // projection number

        for (auto exp : l3) {
            if (exp->aperture() > 0) {
                // it is a regular recursive expression branch
                ol[p] = sigDelay0(sigProj(p, g));
            } else {
                // this expression is a closed term,
                // it don't need to be inside this recursion group.
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
    }

    stringstream error;
    error << "ERROR in file " << __FILE__ << ':' << __LINE__ << ", unrecognised box expression : " << boxpp(box)
          << endl;
    throw faustexception(error.str());

    return siglist();
}

/**
 * Top level propagate a list of signals into a block diagram. Do memoization.
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */

Tree boxPropagateSig(Tree path, Tree box, const siglist& lsig)
{
    return listConvert(propagate(gGlobal->nil, path, box, lsig));
}
