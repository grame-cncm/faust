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

#include "ppsig.hh"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "sigs-config.hh"
#include "binop.hh"
#include "tlib-error.hh"
#include "sigs-state.hh"
#include "sigtyperules.hh"
#include "prim2.hh"
#include "recursivness.hh"
#include "xtended.hh"

using namespace std;

ppsig::ppsig(Tree s, int max_size)
    : fSig(s),
      fEnv(::nil()),
      fPriority(0),
      fHideRecursion(false),
      fMaxSize(max_size),
      fNames(nullptr),
      fExpand(false)
{
}

ostream& ppsig::printinfix(ostream& fout, const string& opname, int priority, Tree x, Tree y) const
{
    // x op y : the left operand at the priority of op, the right one above it, so that the
    // parentheses show the association (a-(b-c) is not a-b-c)
    if (fPriority > priority) {
        fout << "(";
    }
    fout << ppsig(x, fEnv, priority, fMaxSize, fNames) << opname << ppsig(y, fEnv, priority + 1, fMaxSize, fNames);
    if (fPriority > priority) {
        fout << ")";
    }
    return fout;
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize, fNames) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize, fNames) << ", "
                << ppsig(y, fEnv, 0, fMaxSize, fNames) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize, fNames) << ", "
                << ppsig(y, fEnv, 0, fMaxSize, fNames) << ", " << ppsig(z, fEnv, 0, fMaxSize, fNames) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree zz) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize, fNames) << ", "
                << ppsig(y, fEnv, 0, fMaxSize, fNames) << ", " << ppsig(z, fEnv, 0, fMaxSize, fNames) << ", "
                << ppsig(zz, fEnv, 0, fMaxSize, fNames) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2,
                         Tree z3) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize, fNames) << ", "
                << ppsig(y, fEnv, 0, fMaxSize, fNames) << ", " << ppsig(z, fEnv, 0, fMaxSize, fNames) << ", "
                << ppsig(z2, fEnv, 0, fMaxSize, fNames) << ", " << ppsig(z3, fEnv, 0, fMaxSize, fNames) << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label, Tree lo, Tree hi,
                        Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsig(lo, fEnv, 0, fMaxSize, fNames) << ',' << ppsig(hi, fEnv, 0, fMaxSize, fNames) << ','
                << ppsig(step, fEnv, 0, fMaxSize, fNames) << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label, Tree cur, Tree lo, Tree hi,
                        Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsig(cur, fEnv, 0, fMaxSize, fNames) << ',' << ppsig(lo, fEnv, 0, fMaxSize, fNames)
                << ',' << ppsig(hi, fEnv, 0, fMaxSize, fNames) << ',' << ppsig(step, fEnv, 0, fMaxSize, fNames)
                << ')';
}

ostream& ppsig::printout(ostream& fout, int i, Tree x) const
{
    if (fPriority > 0) {
        fout << "(";
    }
    fout << "OUT" << i << " = " << ppsig(x, fEnv, 0, fMaxSize, fNames);
    if (fPriority > 0) {
        fout << ")";
    }
    return fout;
}

ostream& ppsig::printlabel(ostream& fout, Tree pathname) const
{
    fout << '"' << *hd(pathname);
    pathname = tl(pathname);
    while (!isNil(pathname)) {
        fout << '/' << *tl(hd(pathname));
        pathname = tl(pathname);
    }
    fout << '"';
    return fout;
}

ostream& ppsig::printlist(ostream& fout, Tree largs) const
{
    string sep = "";
    fout << '(';
    while (!isNil(largs)) {
        fout << sep << ppsig(hd(largs), fEnv, 0, fMaxSize, fNames);
        sep   = ", ";
        largs = tl(largs);
    }
    fout << ')';
    return fout;
}

ostream& ppsig::printff(ostream& fout, Tree ff, Tree largs) const
{
    fout << ffname(ff);
    printlist(fout, largs);
    return fout;
}

ostream& ppsig::printDelay(ostream& fout, Tree exp, Tree delay) const
{
    // x' and x@d bind tighter than every binary operator, their operands above them ;
    // x@0 is x
    int d;
    if (isSigInt(delay, &d) && (d == 0)) {
        return fout << ppsig(exp, fEnv, fPriority, fMaxSize, fNames);
    }
    if (fPriority > 10) fout << "(";
    fout << ppsig(exp, fEnv, 11, fMaxSize, fNames);
    if (isSigInt(delay, &d) && (d == 1)) {
        fout << "'";
    } else {
        fout << "@" << ppsig(delay, fEnv, 11, fMaxSize, fNames);
    }
    if (fPriority > 10) fout << ")";
    return fout;
}

ostream& ppsig::printrec(ostream& fout, Tree var, Tree lexp, bool hide) const
{
    if (isElement(var, fEnv)) {
        fout << *var;
    } else if (hide) {
        fout << *var;
    } else {
        stringstream str_rec;
        str_rec << ppsig(lexp, addElement(var, fEnv), 0, fMaxSize, fNames);
        if (str_rec.tellp() == 0) {
            fout << "letrec(" << *var << " = ...)";
        } else {
            fout << "letrec(" << *var << " = " << str_rec.str() << ")";
        }
    }
    return fout;
}

ostream& ppsig::printrec(ostream& fout, Tree lexp, bool hide) const
{
    stringstream str_rec;
    str_rec << ppsig(lexp, fEnv, 0, fMaxSize, fNames);
    if (str_rec.tellp() == 0) {
        fout << "debruijn(...)";
    } else {
        fout << "debruijn(" << str_rec.str() << ")";
    }
    return fout;
}

ostream& ppsig::printextended(ostream& fout, Tree sig1) const
{
    string   sep = "";
    xtended* p   = (xtended*)getUserData(fSig);

    fout << p->name() << '(';
    for (int i = 0; i < sig1->arity(); i++) {
        fout << sep << ppsig(sig1->branch(i), fEnv, 0, fMaxSize, fNames);
        sep = ", ";
    }
    fout << ')';
    return fout;
}

ostream& ppsig::print(ostream& fout) const
{
    // Stops printing at fMaxSize characters
    if (fout.tellp() > fMaxSize) {
        fout << "...";
        return fout;
    }

    // a named node is printed as its name
    std::string named;
    if (fNames && !fExpand && fNames->lookup(fSig, named)) {
        return fout << named;
    }

    int    i;
    double r;
    Tree   c, sel, w, x, y, z, u, var, le, label, ff, largs, type, name, file, sf;

    if (isList(fSig)) {
        printlist(fout, fSig);
    } else if (isProj(fSig, &i, x)) {
        fout << "proj" << i << '(' << ppsig(x, fEnv, 0, fMaxSize, fNames) << ')';
    } else if (isRec(fSig, var, le)) {
        printrec(fout, var, le, fHideRecursion /*&& (getRecursivness(sig)==0)*/);
    }

    // debruinj notation
    else if (isRec(fSig, le)) {
        printrec(fout, le, fHideRecursion);
    } else if (isRef(fSig, i)) {
        fout << "REF[" << i << "]";
    }

    else if (getUserData(fSig)) {
        printextended(fout, fSig);
    } else if (isSigInt(fSig, &i)) {
        fout << i;
    } else if (isSigReal(fSig, &r)) {
        fout << sigs::printReal(r);
    } else if (isSigWaveform(fSig)) {
        fout << "waveform{...}";
    } else if (isSigInput(fSig, &i)) {
        fout << "IN[" << i << "]";
    } else if (isSigOutput(fSig, &i, x)) {
        printout(fout, i, x);
    }

    else if (isSigDelay1(fSig, x)) {
        printDelay(fout, x, sigInt(1));
    } else if (isSigDelay(fSig, x, y)) {
        printDelay(fout, x, y);
    } else if (isSigPrefix(fSig, x, y)) {
        printfun(fout, "prefix", x, y);
    } else if (isSigBinOp(fSig, &i, x, y)) {
        printinfix(fout, gBinOpTable[i]->fName, gBinOpTable[i]->fPriority, x, y);
    } else if (isSigFFun(fSig, ff, largs)) {
        printff(fout, ff, largs);
    } else if (isSigFConst(fSig, type, name, file)) {
        fout << tree2str(name);
    } else if (isSigFVar(fSig, type, name, file)) {
        fout << tree2str(name);
    }

    if (isSigWRTbl(fSig, w, x, y, z)) {
        if (y == ::nil()) {
            // rtable
            printfun(fout, "WRTbl2p", w, x);
        } else {
            // rwtable
            fout << "sigWRTbl4p(" << ppsig(w, fEnv, 0, fMaxSize, fNames);
            fout << "; " << ppsig(x, fEnv, 0, fMaxSize, fNames);
            fout << "; " << ppsig(y, fEnv, 0, fMaxSize, fNames);
            fout << "; " << ppsig(z, fEnv, 0, fMaxSize, fNames) << " )";
        }
    } else if (isSigRDTbl(fSig, x, y)) {
        printfun(fout, "sigRDTbl", x, y);
    } else if (isSigGen(fSig, x)) {
        fout << "sigGen(" << ppsig(x, fEnv, fPriority, fMaxSize, fNames) << ")";
    }

    else if (isSigDocConstantTbl(fSig, x, y)) {
        printfun(fout, "docConstantTbl", x, y);
    } else if (isSigDocWriteTbl(fSig, x, y, z, u)) {
        printfun(fout, "docWriteTbl", x, y, z, u);
    } else if (isSigDocAccessTbl(fSig, x, y)) {
        printfun(fout, "docAccessTbl", x, y);
    }

    else if (isSigSelect2(fSig, sel, x, y)) {
        printfun(fout, "select2", sel, x, y);
    }

    else if (isSigFrac(fSig, x)) {
        printfun(fout, "frac", x);
    } else if (isSigCfrac(fSig, x)) {
        printfun(fout, "cfrac", x);
    } else if (isSigMix(fSig, sel, x, y)) {
        printfun(fout, "mix", sel, x, y);
    } else if (isSigTpt(fSig, x)) {
        printfun(fout, "tpt", x);
    } else if (isSigPhase(fSig, x, y)) {
        printfun(fout, "phase", x, y);
    } else if (isSigNeg(fSig, x)) {
        // -x : its operand above the product, in parentheses when compound
        if (fPriority > 9) fout << "(";
        fout << "-" << ppsig(x, fEnv, 10, fMaxSize, fNames);
        if (fPriority > 9) fout << ")";
    }

    else if (isSigIntCast(fSig, x)) {
        printfun(fout, "int", x);
    } else if (isSigBitCast(fSig, x)) {
        printfun(fout, "bit", x);
    } else if (isSigFloatCast(fSig, x)) {
        printfun(fout, "float", x);
    }

    else if (isSigButton(fSig, label)) {
        printui(fout, "button", label);
    } else if (isSigCheckbox(fSig, label)) {
        printui(fout, "checkbox", label);
    } else if (isSigVSlider(fSig, label, c, x, y, z)) {
        printui(fout, "vslider", label, c, x, y, z);
    } else if (isSigHSlider(fSig, label, c, x, y, z)) {
        printui(fout, "hslider", label, c, x, y, z);
    } else if (isSigNumEntry(fSig, label, c, x, y, z)) {
        printui(fout, "nentry", label, c, x, y, z);
    } else if (isSigVBargraph(fSig, label, x, y, z)) {
        printui(fout, "vbargraph", label, x, y, z);
    } else if (isSigHBargraph(fSig, label, x, y, z)) {
        printui(fout, "hbargraph", label, x, y, z);
    }

    else if (isSigSoundfile(fSig, label)) {
        printui(fout, "soundfile", label);
    } else if (isSigSoundfileLength(fSig, sf, x)) {
        printfun(fout, "length", sf, x);
    } else if (isSigSoundfileRate(fSig, sf, x)) {
        printfun(fout, "rate", sf, x);
    } else if (isSigSoundfileBuffer(fSig, sf, x, y, z)) {
        printfun(fout, "buffer", sf, x, y, z);
    }

    else if (isSigAttach(fSig, x, y)) {
        printfun(fout, "attach", x, y);
    } else if (isSigEnable(fSig, x, y)) {
        printfun(fout, "enable", x, y);
    } else if (isSigControl(fSig, x, y)) {
        printfun(fout, "control", x, y);
    }

    else if (isSigRegister(fSig, &i, x)) {
        printfun(fout, "register", sigInt(i), x);
    }

    else if (isSigSum(fSig) || isSigProd(fSig)) {
        // the n-ary sum and product of the normal form : an infix chain, computed from left
        // to right ; a right operand of the same priority keeps its parentheses, so that the
        // association shows (2*(x*y) is not 2*x*y) ; a negative term of a sum is subtracted
        const bool sum = isSigSum(fSig);
        const int  pr  = gBinOpTable[sum ? kAdd : kMul]->fPriority;
        if (fPriority > pr) fout << "(";
        bool first = true;
        for (Tree b : fSig->branches()) {
            Tree u;
            if (first) {
                fout << ppsig(b, fEnv, pr, fMaxSize, fNames);
            } else if (sum && isSigNeg(b, u) && !(fNames && fNames->lookup(b, named))) {
                fout << "-" << ppsig(u, fEnv, pr + 1, fMaxSize, fNames);
            } else {
                fout << (sum ? "+" : "*") << ppsig(b, fEnv, pr + 1, fMaxSize, fNames);
            }
            first = false;
        }
        if (fPriority > pr) fout << ")";
    }

    else if (isSigBpf(fSig)) {
        // Bpf(x; t1, ..., tn; r0, ..., rn)
        Tree x;
        tvec t, r;
        isSigBpf(fSig, x, t, r);
        fout << "Bpf(" << ppsig(x, fEnv, 0, fMaxSize, fNames) << "; ";
        for (size_t k = 0; k < t.size(); k++) fout << (k ? ", " : "") << ppsig(t[k], fEnv, 0, fMaxSize, fNames);
        fout << "; ";
        for (size_t k = 0; k < r.size(); k++) fout << (k ? ", " : "") << ppsig(r[k], fEnv, 0, fMaxSize, fNames);
        fout << ')';
    }

    else if (isSigFIR(fSig) || isSigIIR(fSig) || isSigIRM(fSig)) {
        // FIR(x; c0, c1, ...), IIR(x; c1, ...) and IRM(x; c) : the source, then the
        // coefficients
        fout << (isSigFIR(fSig) ? "FIR(" : isSigIIR(fSig) ? "IIR(" : "IRM(");
        int k = 0;
        for (Tree b : fSig->branches()) {
            fout << (k == 0 ? "" : (k == 1 ? "; " : ", ")) << ppsig(b, fEnv, 0, fMaxSize, fNames);
            k++;
        }
        fout << ')';
    }

    else {
        // cerr << "[[" << *fSig << "]]";
    }
    return fout;
}

#define SIG_INSERT_ID(exp)                                                                        \
    if (sigs::g.gSignalTable.find(fSig) == sigs::g.gSignalTable.end()) {                        \
        stringstream s;                                                                           \
        (exp);                                                                                    \
        sigs::g.gSignalTable[fSig] = make_pair(sigs::g.gSignalCounter, s.str());                \
        sigs::g.gSignalTrace.push_back("ID_" + std::to_string(sigs::g.gSignalCounter) + " = " + \
                                        s.str() + ";\n");                                         \
        sigs::g.gSignalCounter++;                                                                \
    }                                                                                             \
    fout << "ID_" << sigs::g.gSignalTable[fSig].first;

ostream& ppsigShared::printinfix(ostream& fout, const string& opname, int priority, Tree x,
                                 Tree y) const
{
    if (fPriority > priority) {
        fout << "(";
    }
    fout << ppsigShared(x, fEnv, priority) << opname << ppsigShared(y, fEnv, priority);
    if (fPriority > priority) {
        fout << ")";
    }
    return fout;
}

ostream& ppsigShared::printfun(ostream& fout, const string& funame, Tree x) const
{
    return fout << funame << '(' << ppsigShared(x, fEnv) << ')';
}

ostream& ppsigShared::printfun(ostream& fout, const string& funame, Tree x, Tree y) const
{
    return fout << funame << '(' << ppsigShared(x, fEnv) << ',' << ppsigShared(y, fEnv) << ')';
}

ostream& ppsigShared::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z) const
{
    return fout << funame << '(' << ppsigShared(x, fEnv) << ',' << ppsigShared(y, fEnv) << ','
                << ppsigShared(z, fEnv) << ')';
}

ostream& ppsigShared::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z,
                               Tree zz) const
{
    return fout << funame << '(' << ppsigShared(x, fEnv) << ',' << ppsigShared(y, fEnv) << ','
                << ppsigShared(z, fEnv) << ',' << ppsigShared(zz, fEnv) << ')';
}

ostream& ppsigShared::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2,
                               Tree z3) const
{
    return fout << funame << '(' << ppsigShared(x, fEnv) << ',' << ppsigShared(y, fEnv) << ','
                << ppsigShared(z, fEnv) << ',' << ppsigShared(z2, fEnv) << ','
                << ppsigShared(z3, fEnv) << ')';
}

ostream& ppsigShared::printui(ostream& fout, const string& funame, Tree label) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ')';
}

ostream& ppsigShared::printui(ostream& fout, const string& funame, Tree label, Tree lo, Tree hi,
                              Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsigShared(lo, fEnv) << ',' << ppsigShared(hi, fEnv) << ','
                << ppsigShared(step, fEnv) << ')';
}

ostream& ppsigShared::printui(ostream& fout, const string& funame, Tree label, Tree cur, Tree lo,
                              Tree hi, Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsigShared(cur, fEnv) << ',' << ppsigShared(lo, fEnv) << ','
                << ppsigShared(hi, fEnv) << ',' << ppsigShared(step, fEnv) << ')';
}

ostream& ppsigShared::printout(ostream& fout, int i, Tree x) const
{
    if (fPriority > 0) {
        fout << "(";
    }
    fout << "OUT" << i << " = " << ppsigShared(x, fEnv, 0);
    if (fPriority > 0) {
        fout << ")";
    }
    return fout;
}

ostream& ppsigShared::printlist(ostream& fout, Tree largs) const
{
    string sep = "";
    fout << '(';
    while (!isNil(largs)) {
        fout << sep << ppsigShared(hd(largs), fEnv);
        sep   = ", ";
        largs = tl(largs);
    }
    fout << ')';
    return fout;
}

ostream& ppsigShared::printff(ostream& fout, Tree ff, Tree largs) const
{
    fout << ffname(ff);
    printlist(fout, largs);
    return fout;
}

ostream& ppsigShared::printDelay(ostream& fout, Tree exp, Tree delay) const
{
    int d;

    if (isSigInt(delay, &d) && (d == 1)) {
        fout << ppsigShared(exp, fEnv, 8) << "'";
    } else {
        printinfix(fout, "@", 8, exp, delay);
    }
    return fout;
}

ostream& ppsigShared::printrec(ostream& fout, Tree var, Tree lexp, bool hide) const
{
    if (isElement(var, fEnv)) {
        fout << *var;
    } else if (hide) {
        fout << *var;
    } else {
        fout << "letrec(" << *var << " = " << ppsigShared(lexp, addElement(var, fEnv)) << ")";
    }
    return fout;
}

ostream& ppsigShared::printrec(ostream& fout, Tree lexp, bool hide) const
{
    fout << "debruijn(" << ppsigShared(lexp, fEnv) << ")";
    return fout;
}

ostream& ppsigShared::printextended(ostream& fout, Tree sig1) const
{
    string   sep = "";
    xtended* p   = (xtended*)getUserData(fSig);

    fout << p->name() << '(';
    for (int i = 0; i < sig1->arity(); i++) {
        fout << sep << ppsigShared(sig1->branch(i), fEnv);
        sep = ", ";
    }
    fout << ')';
    return fout;
}

ostream& ppsigShared::print(ostream& fout) const
{
    int    i;
    double r;
    Tree   c, sel, w, x, y, z, u, var, le, label, ff, largs, type, name, file, sf;

    if (isList(fSig)) {
        printlist(fout, fSig);
    } else if (isProj(fSig, &i, x)) {
        SIG_INSERT_ID(s << "proj" << i << '(' << ppsigShared(x, fEnv) << ')');
    } else if (isRec(fSig, var, le)) {
        SIG_INSERT_ID(printrec(s, var, le, fHideRecursion));
    }

    // debruinj notation
    else if (isRec(fSig, le)) {
        SIG_INSERT_ID(printrec(s, le, fHideRecursion));
    } else if (isRef(fSig, i)) {
        fout << "REF[" << i << "]";
    }

    else if (getUserData(fSig)) {
        SIG_INSERT_ID(printextended(s, fSig));
    } else if (isSigInt(fSig, &i)) {
        fout << i;
    } else if (isSigReal(fSig, &r)) {
        fout << sigs::printReal(r);
    } else if (isSigWaveform(fSig)) {
        fout << "waveform{...}";
    } else if (isSigInput(fSig, &i)) {
        fout << "IN[" << i << "]";
    } else if (isSigOutput(fSig, &i, x)) {
        SIG_INSERT_ID(printout(s, i, x));
    }

    else if (isSigDelay1(fSig, x)) {
        SIG_INSERT_ID(printDelay(s, x, sigInt(1)));
    } else if (isSigDelay(fSig, x, y) && isSigInt(y, &i) && (i == 0)) {
        // x@0 is x
        fout << ppsigShared(x, fEnv);
    } else if (isSigDelay(fSig, x, y)) {
        SIG_INSERT_ID(printDelay(s, x, y));
    } else if (isSigPrefix(fSig, x, y)) {
        SIG_INSERT_ID(printfun(s, "prefix", x, y));
    } else if (isSigBinOp(fSig, &i, x, y)) {
        SIG_INSERT_ID(printinfix(s, gBinOpTable[i]->fName, gBinOpTable[i]->fPriority, x, y));
    } else if (isSigFFun(fSig, ff, largs)) {
        SIG_INSERT_ID(printff(s, ff, largs));
    } else if (isSigFConst(fSig, type, name, file)) {
        fout << tree2str(name);
    } else if (isSigFVar(fSig, type, name, file)) {
        fout << tree2str(name);
    }

    if (isSigWRTbl(fSig, w, x, y, z)) {
        if (y == ::nil()) {
            // rdtable
            SIG_INSERT_ID(printfun(s, "WRTbl2p", w, x));
        } else {
            // rwtable
            SIG_INSERT_ID(printfun(s, "sigWRTbl4p", w, x, y, z));
        }
    } else if (isSigRDTbl(fSig, x, y)) {
        SIG_INSERT_ID(printfun(s, "sigRDTbl", x, y));
    } else if (isSigGen(fSig, x)) {
        SIG_INSERT_ID(s << "sigGen(" << ppsigShared(x, fEnv, fPriority) << ")");
    }

    else if (isSigDocConstantTbl(fSig, x, y)) {
        SIG_INSERT_ID(printfun(s, "docConstantTbl", x, y));
    } else if (isSigDocWriteTbl(fSig, x, y, z, u)) {
        SIG_INSERT_ID(printfun(s, "docWriteTbl", x, y, z, u));
    } else if (isSigDocAccessTbl(fSig, x, y)) {
        SIG_INSERT_ID(printfun(fout, "docAccessTbl", x, y));
    }

    else if (isSigSelect2(fSig, sel, x, y)) {
        SIG_INSERT_ID(printfun(s, "select2", sel, x, y));
    }

    else if (isSigFrac(fSig, x)) {
        SIG_INSERT_ID(printfun(s, "frac", x));
    } else if (isSigCfrac(fSig, x)) {
        SIG_INSERT_ID(printfun(s, "cfrac", x));
    } else if (isSigMix(fSig, sel, x, y)) {
        SIG_INSERT_ID(printfun(s, "mix", sel, x, y));
    } else if (isSigTpt(fSig, x)) {
        SIG_INSERT_ID(printfun(s, "tpt", x));
    } else if (isSigPhase(fSig, x, y)) {
        SIG_INSERT_ID(printfun(s, "phase", x, y));
    } else if (isSigNeg(fSig, x)) {
        SIG_INSERT_ID(s << "-" << ppsigShared(x, fEnv, 10));
    }

    else if (isSigSum(fSig) || isSigProd(fSig)) {
        // the n-ary sum and product, as ppsig writes them
        const bool sum   = isSigSum(fSig);
        const int  pr    = gBinOpTable[sum ? kAdd : kMul]->fPriority;
        auto       chain = [&](std::ostream& o) {
            bool first = true;
            for (Tree b : fSig->branches()) {
                Tree u;
                if (first) {
                    o << ppsigShared(b, fEnv, pr);
                } else if (sum && isSigNeg(b, u)) {
                    o << "-" << ppsigShared(u, fEnv, pr + 1);
                } else {
                    o << (sum ? "+" : "*") << ppsigShared(b, fEnv, pr + 1);
                }
                first = false;
            }
        };
        SIG_INSERT_ID(chain(s));
    } else if (isSigBpf(fSig)) {
        auto bpf = [&](std::ostream& o) {
            Tree x;
            tvec t, r;
            isSigBpf(fSig, x, t, r);
            o << "Bpf(" << ppsigShared(x, fEnv, 0) << "; ";
            for (size_t k = 0; k < t.size(); k++) o << (k ? ", " : "") << ppsigShared(t[k], fEnv, 0);
            o << "; ";
            for (size_t k = 0; k < r.size(); k++) o << (k ? ", " : "") << ppsigShared(r[k], fEnv, 0);
            o << ')';
        };
        SIG_INSERT_ID(bpf(s));
    } else if (isSigFIR(fSig) || isSigIIR(fSig) || isSigIRM(fSig)) {
        auto kernel = [&](std::ostream& o) {
            o << (isSigFIR(fSig) ? "FIR(" : isSigIIR(fSig) ? "IIR(" : "IRM(");
            int k = 0;
            for (Tree b : fSig->branches()) {
                o << (k == 0 ? "" : (k == 1 ? "; " : ", ")) << ppsigShared(b, fEnv, 0);
                k++;
            }
            o << ')';
        };
        SIG_INSERT_ID(kernel(s));
    }

    else if (isSigIntCast(fSig, x)) {
        SIG_INSERT_ID(printfun(s, "int", x));
    } else if (isSigBitCast(fSig, x)) {
        SIG_INSERT_ID(printfun(s, "bit", x));
    } else if (isSigFloatCast(fSig, x)) {
        SIG_INSERT_ID(printfun(s, "float", x));
    }

    else if (isSigButton(fSig, label)) {
        SIG_INSERT_ID(printui(s, "button", label));
    } else if (isSigCheckbox(fSig, label)) {
        SIG_INSERT_ID(printui(s, "checkbox", label));
    } else if (isSigVSlider(fSig, label, c, x, y, z)) {
        SIG_INSERT_ID(printui(s, "vslider", label, c, x, y, z));
    } else if (isSigHSlider(fSig, label, c, x, y, z)) {
        SIG_INSERT_ID(printui(s, "hslider", label, c, x, y, z));
    } else if (isSigNumEntry(fSig, label, c, x, y, z)) {
        SIG_INSERT_ID(printui(s, "nentry", label, c, x, y, z));
    } else if (isSigVBargraph(fSig, label, x, y, z)) {
        SIG_INSERT_ID(printui(s, "vbargraph", label, x, y, z));
    } else if (isSigHBargraph(fSig, label, x, y, z)) {
        SIG_INSERT_ID(printui(s, "hbargraph", label, x, y, z));
    }

    else if (isSigSoundfile(fSig, label)) {
        SIG_INSERT_ID(printui(s, "soundfile", label));
    } else if (isSigSoundfileLength(fSig, sf, x)) {
        SIG_INSERT_ID(printfun(s, "length", sf, x));
    } else if (isSigSoundfileRate(fSig, sf, x)) {
        SIG_INSERT_ID(printfun(s, "rate", sf, x));
    } else if (isSigSoundfileBuffer(fSig, sf, x, y, z)) {
        SIG_INSERT_ID(printfun(s, "buffer", sf, x, y, z));
    }

    else if (isSigAttach(fSig, x, y)) {
        SIG_INSERT_ID(printfun(s, "attach", x, y));
    } else if (isSigEnable(fSig, x, y)) {
        SIG_INSERT_ID(printfun(s, "enable", x, y));
    } else if (isSigControl(fSig, x, y)) {
        SIG_INSERT_ID(printfun(s, "control", x, y));
    }

    else if (isSigRegister(fSig, &i, x)) {
        SIG_INSERT_ID(printfun(s, "register", sigInt(i), x));
    }

    else {
        // cerr << "[[" << *fSig << "]]";
    }
    return fout;
}

void ppsigShared::printIDs(ostream& fout, bool sort)
{
    /*
     HACK: since the signal tree shape is still not deterministic,
     we sort the list to be sure it stays the same.
     To be removed if the tree shape becomes deterministic.
     */
    if (sort) {
        std::sort(sigs::g.gSignalTrace.begin(), sigs::g.gSignalTrace.end());
    }
    fout << "// Size = " << sigs::g.gSignalTrace.size() << endl;
    for (const auto& it : sigs::g.gSignalTrace) {
        fout << it;
    }
}

/*****************************************************************************
                        Signals printed as equations
*****************************************************************************/

bool ppsigNames::lookup(Tree t, std::string& name) const
{
    int  i;
    Tree group;
    if (isProj(t, &i, group)) {
        auto g = fGroups.find(group);
        if (g != fGroups.end()) {
            name = "R" + std::to_string(g->second.first);
            if (g->second.second > 1) {
                name += "." + std::to_string(i);
            }
            return true;
        }
    }
    auto s = fShared.find(t);
    if (s != fShared.end()) {
        name = s->second;
        return true;
    }
    return false;
}

bool ppsigNames::groupName(Tree group, std::string& name) const
{
    auto g = fGroups.find(group);
    if (g == fGroups.end()) {
        return false;
    }
    name = "R" + std::to_string(g->second.first);
    return true;
}

// a number with the fewest significant digits that read back to it, as a single float
// when it is one
static std::string shortest(double x)
{
    if (std::isinf(x)) {
        return (x < 0) ? "-inf" : "inf";
    }
    if (std::abs(x) < 9007199254740992.0 && x == std::floor(x)) {
        std::ostringstream str;
        str << (long long)x;
        return str.str();
    }
    if (double(float(x)) == x) {
        for (int digits = 6; digits <= 9; digits++) {
            std::ostringstream str;
            str.precision(digits);
            str << x;
            if (std::strtof(str.str().c_str(), nullptr) == float(x)) {
                return str.str();
            }
        }
    }
    for (int digits = 6; digits <= 17; digits++) {
        std::ostringstream str;
        str.precision(digits);
        str << x;
        if (std::strtod(str.str().c_str(), nullptr) == x) {
            return str.str();
        }
    }
    std::ostringstream str;
    str.precision(17);
    str << x;
    return str.str();
}

// the type of a signal as a comment : nature, variability, interval, lsb, validity
// (the booleanity of the typing, an upper bound joined over operands, is left out)
static std::string typeComment(Type t)
{
    std::ostringstream str;
    str << "// "
        << ((t->nature() == kInt) ? "int" : "real") << ' '
        << ((t->variability() == kKonst) ? "konst"
            : (t->variability() == kBlock) ? "block"
                                           : "samp");
    const interval& i = t->getInterval();
    if (i.isEmpty()) {
        str << " []";
    } else {
        str << " [" << shortest(i.lo()) << ", " << shortest(i.hi()) << "]";
        if (i.isBounded()) {
            str << " lsb " << i.lsb();
        }
    }
    if (i.mayBeInvalid()) {
        str << " invalid";
    }
    return str.str();
}

// x@0, which is printed as x
static bool isDelay0(Tree t, Tree& x)
{
    Tree d;
    int  i;
    return isSigDelay(t, x, d) && isSigInt(d, &i) && (i == 0);
}

// a signal without subsignals : a number, an input, a user interface element, a constant
static bool isLeafSig(Tree t)
{
    int    i;
    double r;
    Tree   label, c, x, y, z, type, name, file;
    return (t->arity() == 0) || isSigInt(t, &i) || isSigReal(t, &r) || isSigInput(t, &i) ||
           isRef(t, i) || isSigWaveform(t) || isSigButton(t, label) || isSigCheckbox(t, label) ||
           isSigVSlider(t, label, c, x, y, z) || isSigHSlider(t, label, c, x, y, z) ||
           isSigNumEntry(t, label, c, x, y, z) || isSigSoundfile(t, label) ||
           isSigFConst(t, type, name, file) || isSigFVar(t, type, name, file);
}

// the subsignals that an equation printing visits
static void subsignals(Tree t, std::vector<Tree>& v)
{
    int  i;
    Tree x, var, le, ff, largs;
    if (isLeafSig(t)) {
        return;
    } else if (isProj(t, &i, x)) {
        v.push_back(x);
    } else if (isRec(t, var, le)) {
        for (; isList(le); le = tl(le)) {
            v.push_back(hd(le));
        }
    } else if (isList(t)) {
        for (Tree l = t; isList(l); l = tl(l)) {
            v.push_back(hd(l));
        }
    } else if (isSigFFun(t, ff, largs)) {
        for (; isList(largs); largs = tl(largs)) {
            v.push_back(hd(largs));
        }
    } else {
        for (Tree b : t->branches()) {
            if (!isNil(b)) {
                v.push_back(b);
            }
        }
    }
}

// a signal short enough to be printed at each use : a leaf, a recursion, or a delay or a
// cast or a negation of one of them
static bool isAtomicSig(Tree t)
{
    int  i;
    Tree x, d, var, le;
    if (isLeafSig(t) || isProj(t, &i, x) || isRec(t, var, le) || isList(t)) {
        return true;
    }
    if (isSigDelay1(t, x) || (isSigDelay(t, x, d) && isSigInt(d, &i)) || isSigIntCast(t, x) ||
        isSigFloatCast(t, x) || isSigNeg(t, x)) {
        return isAtomicSig(x);
    }
    return false;
}

// the number of distinct parents of each node ; x@0 is transparent, a parent of x@0 is a
// parent of x
void ppsigEquations::count(Tree t)
{
    Tree x;
    if (isDelay0(t, x)) {
        count(x);
        return;
    }
    if (fCount[t]++ > 0) {
        return;
    }
    std::vector<Tree> subs;
    subsignals(t, subs);
    for (Tree s : subs) {
        count(s);
    }
}

std::string ppsigEquations::expand(Tree t) const
{
    std::stringstream str;
    str << ppsig(t, ::nil(), 0, INT_MAX, &fNames, true);
    return str.str();
}

// whether t is defined by an equation of its own
// whether the interval of a type is invalid, or unbounded
static bool isInvalidType(Type t)
{
    return t && t->getInterval().mayBeInvalid();
}

static bool isUnboundedType(Type t)
{
    return t && !t->getInterval().isEmpty() && !t->getInterval().isBounded();
}

// what the typing of t shows wrong, if anything : a delay the compiler refuses (its amount
// has no valid bounds, or may be negative), or the birth of an invalid or unbounded
// interval, from operands that are not
std::string ppsigEquations::problemOf(Tree t) const
{
    auto memo = fProblems.find(t);
    if (memo != fProblems.end()) {
        return memo->second;
    }
    std::string problem;
    Type        ty = getSigType(t);
    Tree        x, d;
    int         i;
    if (ty && !isLeafSig(t) && !isProj(t, &i, x)) {
        Type td = nullptr;
        if (isSigDelay(t, x, d) && !isSigInt(d, &i)) {
            td = getSigType(d);
        }
        if (td && (!td->getInterval().isValid() || !td->getInterval().isBounded())) {
            problem = "REFUSED : delay amount " + td->getInterval().to_string();
        } else if (td && td->getInterval().lo() < 0) {
            problem = "REFUSED : delay amount may be negative " + td->getInterval().to_string();
        } else if (isInvalidType(ty) || isUnboundedType(ty)) {
            bool              opInvalid = false, opUnbounded = false;
            std::vector<Tree> subs;
            subsignals(t, subs);
            for (Tree s : subs) {
                Type ts = getSigType(s);
                opInvalid |= isInvalidType(ts);
                opUnbounded |= isUnboundedType(ts);
            }
            if (isInvalidType(ty) && !opInvalid) {
                // born from valid operands : from bounded ones, it is a cause ; from unbounded
                // ones (inf-inf, 0*inf), a consequence of the unbounded interval above
                problem = opUnbounded ? "invalid from unbounded operands" : "invalid from here";
            } else if (isUnboundedType(ty) && !opUnbounded) {
                problem = "unbounded from here";
            }
        }
    }
    fProblems[t] = problem;
    return problem;
}

// whether t reads a member of group at the current or a past sample
bool ppsigEquations::reaches(Tree t, Tree group) const
{
    auto key  = std::make_pair(t, group);
    auto memo = fReaches.find(key);
    if (memo != fReaches.end()) {
        return memo->second;
    }
    fReaches[key] = false;  // a cycle through another group does not reach it
    int  i;
    Tree g;
    bool result = false;
    if (isProj(t, &i, g) && g == group) {
        result = true;
    } else {
        std::vector<Tree> subs;
        subsignals(t, subs);
        for (Tree s : subs) {
            if (reaches(s, group)) {
                result = true;
                break;
            }
        }
    }
    fReaches[key] = result;
    return result;
}

// the problem of a member of a recursive group : its interval is invalid or unbounded
// while every value the group reads from outside itself is not -- the recursion is where
// it is born
std::string ppsigEquations::groupProblem(Tree group, Tree member) const
{
    Type ty = getSigType(member);
    if (!isInvalidType(ty) && !isUnboundedType(ty)) {
        return "";
    }
    Tree var, le;
    if (!isRec(group, var, le)) {
        return "";
    }
    bool              outInvalid = false, outUnbounded = false;
    std::set<Tree>    seen;
    std::vector<Tree> work;
    for (; isList(le); le = tl(le)) {
        work.push_back(hd(le));
    }
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) {
            continue;
        }
        if (!reaches(t, group)) {
            outInvalid |= isInvalidType(getSigType(t));
            outUnbounded |= isUnboundedType(getSigType(t));
            continue;
        }
        int  i;
        Tree g;
        if (isProj(t, &i, g) && g == group) {
            continue;
        }
        std::vector<Tree> subs;
        subsignals(t, subs);
        for (Tree s : subs) {
            work.push_back(s);
        }
    }
    if (isInvalidType(ty) && !outInvalid) {
        return outUnbounded ? "invalid from unbounded operands (the recursion)"
                            : "invalid from here (the recursion)";
    }
    if (isUnboundedType(ty) && !outUnbounded) {
        return "unbounded from here (the recursion)";
    }
    return "";
}

bool ppsigEquations::isNamed(Tree t) const
{
    if (isAtomicSig(t)) {
        return false;
    }
    // a cause gets an equation of its own ; a consequence is noted only on an equation
    std::string problem = problemOf(t);
    if (!problem.empty() && problem != "invalid from unbounded operands") {
        return true;
    }
    if (fAll) {
        // a negation used once is printed by its sum as a subtraction
        Tree x;
        return !isSigNeg(t, x) || (fCount.at(t) >= 2);
    }
    return fCount.at(t) >= 2;
}

std::string ppsigEquations::nameOf(Tree t)
{
    auto s = fNames.fShared.find(t);
    if (s != fNames.fShared.end()) {
        return s->second;
    }
    std::string name     = "E" + std::to_string(fNextShared++);
    fNames.fShared[t] = name;
    return name;
}

// defines the names that the printing of t uses, in a post-order traversal, then t's own
// equation. A node met again while it is being defined depends on a recursion that reads
// it : it is named at once, so that the equations of the recursion can refer to it.
void ppsigEquations::define(Tree t)
{
    int  i;
    Tree x, group, var, le;
    if (isDelay0(t, x)) {
        define(x);
        return;
    }
    if (!fVisited.insert(t).second) {
        if (fOnStack.count(t) && isNamed(t)) {
            nameOf(t);
        }
        return;
    }
    if (isProj(t, &i, group) && isRec(group, var, le)) {
        fProjs[std::make_pair(group, i)] = t;
        defineGroup(group);
        return;
    }
    fOnStack.insert(t);
    std::vector<Tree> subs;
    subsignals(t, subs);
    for (Tree s : subs) {
        define(s);
    }
    fOnStack.erase(t);
    if (isNamed(t)) {
        nameOf(t);
        fLines.push_back({t, nullptr, 0});
    }
}

// a recursive group : its number is given when it is first met, so that the members of an
// enclosing group, referenced from its body, already have a name ; its members are defined
// on consecutive lines, after the names their bodies use
void ppsigEquations::defineGroup(Tree group)
{
    Tree var, le;
    if (fNames.fGroups.count(group) || !isRec(group, var, le)) {
        return;
    }
    std::vector<Tree> members;
    for (; isList(le); le = tl(le)) {
        members.push_back(hd(le));
    }
    const int number              = fNextGroup++;
    fNames.fGroups[group]         = std::make_pair(number, int(members.size()));
    for (Tree e : members) {
        if (fVisited.insert(e).second) {
            std::vector<Tree> subs;
            subsignals(e, subs);
            for (Tree s : subs) {
                define(s);
            }
        }
    }
    for (size_t i = 0; i < members.size(); i++) {
        fLines.push_back({members[i], group, int(i)});
    }
}

// the equations that t reads at the current sample : the names met before a delay ; a
// delay of a constant amount of at least one sample ends the reading, and so does the
// source of a FIR whose first coefficient is zero
void ppsigEquations::instantDeps(Tree t, const std::map<Tree, int>& index,
                                 const std::map<Tree, int>& firstMember, std::set<Tree>& seen,
                                 std::set<int>& deps) const
{
    int    i;
    double r;
    Tree   x, d, group;
    if (!seen.insert(t).second) {
        return;
    }
    if (isProj(t, &i, group)) {
        auto g = firstMember.find(group);
        if (g != firstMember.end()) {
            deps.insert(g->second + i);
            return;
        }
    }
    auto e = index.find(t);
    if (e != index.end()) {
        deps.insert(e->second);
        return;
    }
    if (isSigDelay1(t, x) || (isSigDelay(t, x, d) && isSigInt(d, &i) && (i >= 1))) {
        return;
    }
    std::vector<Tree> subs;
    subsignals(t, subs);
    for (size_t k = 0; k < subs.size(); k++) {
        if (k == 0 && isSigFIR(t) && subs.size() > 1 &&
            ((isSigInt(subs[1], &i) && i == 0) || (isSigReal(subs[1], &r) && r == 0.0))) {
            continue;
        }
        instantDeps(subs[k], index, firstMember, seen, deps);
    }
}

// orders the equations so that every name read at the current sample is defined before :
// a topological order of the instantaneous readings, which exists in a causal program. The
// members of a recursive group stay together as soon as the equations they read outside
// the group are defined ; between equal choices, the order of definition decides. Should
// a cycle remain (a reading the structure cannot see as delayed), the first equation in
// the order of definition breaks it.
void ppsigEquations::order()
{
    const int              n = int(fLines.size());
    std::map<Tree, int>    index;        // a shared subexpression -> its equation
    std::map<Tree, int>    firstMember;  // a recursive group -> the equation of member 0
    std::vector<int>       groupOf(n, -1);
    std::map<Tree, int>    groupNumber;
    std::vector<std::vector<int>> members;
    for (int k = 0; k < n; k++) {
        const Equation& e = fLines[k];
        if (e.fGroup == nullptr) {
            index[e.fNode] = k;
        } else {
            if (e.fMember == 0) {
                firstMember[e.fGroup] = k;
                groupNumber[e.fGroup] = int(members.size());
                members.push_back({});
            }
            groupOf[k] = groupNumber[e.fGroup];
            members[groupOf[k]].push_back(k);
        }
    }

    // the instantaneous dependencies, and the unmet ones
    std::vector<std::vector<int>> dependents(n);
    std::vector<int>              unmet(n, 0);
    std::vector<int>              outside(members.size(), 0);  // unmet readings out of a group
    for (int k = 0; k < n; k++) {
        std::set<Tree> seen;
        std::set<int>  deps;
        const Equation& e = fLines[k];
        if (e.fGroup == nullptr) {
            // the equation's own expression, not its name
            std::vector<Tree> subs;
            subsignals(e.fNode, subs);
            seen.insert(e.fNode);
            Tree x, d;
            int  i;
            if (!(isSigDelay1(e.fNode, x) || (isSigDelay(e.fNode, x, d) && isSigInt(d, &i) && i >= 1))) {
                for (Tree s : subs) {
                    instantDeps(s, index, firstMember, seen, deps);
                }
            }
        } else {
            instantDeps(e.fNode, index, firstMember, seen, deps);
        }
        deps.erase(k);
        for (int dep : deps) {
            dependents[dep].push_back(k);
            unmet[k]++;
            if (groupOf[k] >= 0 && groupOf[dep] != groupOf[k]) {
                outside[groupOf[k]]++;
            }
        }
    }

    // candidates by their position in the order of definition : an equation (k, -1) out of
    // any group, or a whole group (first member, g)
    std::set<std::pair<int, int>> ready;
    std::set<int>                 remaining;
    std::vector<bool>             done(n, false);
    std::vector<Equation>         sorted;
    for (int k = 0; k < n; k++) {
        remaining.insert(k);
        if (groupOf[k] < 0 && unmet[k] == 0) {
            ready.insert({k, -1});
        }
    }
    for (size_t g = 0; g < members.size(); g++) {
        if (outside[g] == 0) {
            ready.insert({members[g][0], int(g)});
        }
    }

    auto emit = [&](int k) {
        done[k] = true;
        remaining.erase(k);
        sorted.push_back(fLines[k]);
        for (int dep : dependents[k]) {
            if (done[dep]) {
                continue;
            }
            unmet[dep]--;
            if (groupOf[dep] < 0) {
                if (unmet[dep] == 0) {
                    ready.insert({dep, -1});
                }
            } else if (groupOf[dep] != groupOf[k]) {
                if (--outside[groupOf[dep]] == 0) {
                    ready.insert({members[groupOf[dep]][0], groupOf[dep]});
                }
            }
        }
    };
    // a member emitted alone no longer counts in its group's unmet readings
    auto emitMember = [&](int k) {
        int g = groupOf[k];
        if (g >= 0) {
            // its unmet readings out of the group are dropped from the group's count
            int dropped = 0;
            std::set<Tree> seen;
            std::set<int>  deps;
            instantDeps(fLines[k].fNode, index, firstMember, seen, deps);
            for (int dep : deps) {
                if (!done[dep] && dep != k && groupOf[dep] != g) {
                    dropped++;
                }
            }
            outside[g] -= dropped;
            if (outside[g] == 0) {
                ready.insert({members[g][0], g});
            }
        }
        emit(k);
    };

    while (!remaining.empty()) {
        // the first candidate still to emit
        while (!ready.empty()) {
            auto c = *ready.begin();
            bool stale = (c.second < 0) ? done[c.first] : std::all_of(members[c.second].begin(),
                                                                      members[c.second].end(),
                                                                      [&](int m) { return done[m]; });
            if (!stale) {
                break;
            }
            ready.erase(ready.begin());
        }
        if (!ready.empty()) {
            auto c = *ready.begin();
            ready.erase(ready.begin());
            if (c.second < 0) {
                emit(c.first);
            } else {
                // the members of the group, each after the members it reads at once
                const std::vector<int>& ms = members[c.second];
                for (size_t left = std::count_if(ms.begin(), ms.end(), [&](int m) { return !done[m]; });
                     left > 0; left--) {
                    int pick = -1;
                    for (int m : ms) {
                        if (!done[m] && unmet[m] == 0) {
                            pick = m;
                            break;
                        }
                    }
                    if (pick < 0) {
                        for (int m : ms) {
                            if (!done[m]) {
                                pick = m;
                                break;
                            }
                        }
                    }
                    emit(pick);
                }
            }
            continue;
        }
        // nothing is ready as a whole : a member whose readings are met, alone, or else the
        // first remaining equation
        int pick = -1;
        for (int k : remaining) {
            if (groupOf[k] >= 0 && unmet[k] == 0) {
                pick = k;
                break;
            }
        }
        if (pick < 0) {
            pick = *remaining.begin();
        }
        emitMember(pick);
    }
    fLines = sorted;
}

ppsigEquations::ppsigEquations(Tree L, bool all) : fRoot(L), fAll(all)
{
    count(L);
    define(L);
    order();

    // the names numbered in the order of the equations
    int            shared = 0;
    int            groups = 0;
    std::set<Tree> numbered;
    for (const Equation& e : fLines) {
        if (e.fGroup == nullptr) {
            fNames.fShared[e.fNode] = "E" + std::to_string(shared++);
        } else if (numbered.insert(e.fGroup).second) {
            fNames.fGroups[e.fGroup].first = groups++;
        }
    }
}

ppsigEquations::ppsigEquations(Tree L, std::ostream& fout, bool all) : ppsigEquations(L, all)
{
    print(fout);
}

void ppsigEquations::print(std::ostream& fout) const
{
    struct Line {
        std::string name, text, type;
    };
    std::vector<Line> lines;
    size_t            width = 0;
    std::set<Tree>    marked;
    for (const Equation& e : fLines) {
        Line line;
        Tree typed = e.fNode;
        if (e.fGroup == nullptr) {
            line.name = fNames.fShared.at(e.fNode);
        } else {
            const std::pair<int, int>& g = fNames.fGroups.at(e.fGroup);
            line.name = "R" + std::to_string(g.first);
            if (g.second > 1) {
                line.name += "." + std::to_string(e.fMember);
            }
            auto p = fProjs.find(std::make_pair(e.fGroup, e.fMember));
            if (p != fProjs.end()) {
                typed = p->second;
            }
        }
        line.text = expand(e.fNode) + ";";
        Type t    = getSigType(typed);
        if (t) {
            line.type = typeComment(t);
            // the problem of a group is shown once, on its first member
            std::string problem;
            if (e.fGroup == nullptr) {
                problem = problemOf(e.fNode);
            } else if (marked.insert(e.fGroup).second) {
                problem = groupProblem(e.fGroup, typed);
            }
            if (!problem.empty()) {
                line.type += "  <-- " + problem;
            }
        }
        width = std::max(width, line.name.size());
        lines.push_back(line);
    }

    // the outputs, with their types
    Line out;
    out.name = "process";
    out.text = expand(fRoot) + ";";
    std::string sep;
    for (Tree l = fRoot; isList(l); l = tl(l)) {
        Type t = getSigType(hd(l));
        if (!t) {
            out.type.clear();
            break;
        }
        out.type += sep + typeComment(t).substr(sep.empty() ? 0 : 3);
        sep = " ; ";
    }

    // the equal signs aligned, and the types in a column when the lines are short enough
    const size_t maxColumn = 100;
    size_t       column    = 0;
    for (const Line& line : lines) {
        size_t len = width + 3 + line.text.size();
        if (len <= maxColumn) {
            column = std::max(column, len);
        }
    }
    // a type follows its equation in the column, or comes before a line too long for it
    auto printLine = [&](const std::string& head, const Line& line) {
        std::string text = head + line.text;
        if (line.type.empty()) {
            fout << text << "\n";
        } else if (text.size() > maxColumn) {
            fout << line.type << "\n" << text << "\n";
        } else {
            fout << text << std::string((text.size() < column) ? column - text.size() : 0, ' ')
                 << "  " << line.type << "\n";
        }
    };
    for (const Line& line : lines) {
        printLine(line.name + std::string(width - line.name.size(), ' ') + " = ", line);
    }
    printLine("process = ", out);
    fout << std::flush;
}
