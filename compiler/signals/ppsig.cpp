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
#include <vector>
#include "Text.hh"
#include "binop.hh"
#include "exception.hh"
#include "global.hh"
#include "prim2.hh"
#include "recursivness.hh"
#include "xtended.hh"

using namespace std;

ppsig::ppsig(Tree s, int max_size)
    : fSig(s), fEnv(gGlobal->nil), fPriority(0), fHideRecursion(false), fMaxSize(max_size)
{
}

ostream& ppsig::printinfix(ostream& fout, const string& opname, int priority, Tree x, Tree y) const
{
#if 0
    if (fPriority > priority) {
        fout << "(";
    }
    fout << ppsig(x, fEnv, priority, fMaxSize) << opname << ppsig(y, fEnv, priority, fMaxSize);
    if (fPriority > priority) {
        fout << ")";
    }
    return fout;
#endif
    return printfun(fout, opname, x, y);
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize) << ','
                << ppsig(y, fEnv, 0, fMaxSize) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize) << ','
                << ppsig(y, fEnv, 0, fMaxSize) << ',' << ppsig(z, fEnv, 0, fMaxSize) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree zz) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize) << ','
                << ppsig(y, fEnv, 0, fMaxSize) << ',' << ppsig(z, fEnv, 0, fMaxSize) << ','
                << ppsig(zz, fEnv, 0, fMaxSize) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2,
                         Tree z3) const
{
    return fout << funame << '(' << ppsig(x, fEnv, 0, fMaxSize) << ','
                << ppsig(y, fEnv, 0, fMaxSize) << ',' << ppsig(z, fEnv, 0, fMaxSize) << ','
                << ppsig(z2, fEnv, 0, fMaxSize) << ',' << ppsig(z3, fEnv, 0, fMaxSize) << ')';
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
    return fout << ',' << ppsig(lo, fEnv, 0, fMaxSize) << ',' << ppsig(hi, fEnv, 0, fMaxSize) << ','
                << ppsig(step, fEnv, 0, fMaxSize) << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label, Tree cur, Tree lo, Tree hi,
                        Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsig(cur, fEnv, 0, fMaxSize) << ',' << ppsig(lo, fEnv, 0, fMaxSize)
                << ',' << ppsig(hi, fEnv, 0, fMaxSize) << ',' << ppsig(step, fEnv, 0, fMaxSize)
                << ')';
}

ostream& ppsig::printout(ostream& fout, int i, Tree x) const
{
    if (fPriority > 0) {
        fout << "(";
    }
    fout << "OUT" << i << " = " << ppsig(x, fEnv, 0, fMaxSize);
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
        fout << sep << ppsig(hd(largs), fEnv, 0, fMaxSize);
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
    // int d;

    // if (isSigInt(delay, &d) && (d == 1)) {
    //     fout << ppsig(exp, fEnv, 8, fMaxSize) << "'";
    // } else {
    //     printinfix(fout, "@", 8, exp, delay);
    // }
    printfun(fout, "Delay", exp, delay);
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
        str_rec << ppsig(lexp, addElement(var, fEnv), 0, fMaxSize);
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
    str_rec << ppsig(lexp, fEnv, 0, fMaxSize);
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
        fout << sep << ppsig(sig1->branch(i), fEnv, 0, fMaxSize);
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

    int    i;
    double r;
    Tree   c, sel, w, x, y, z, u, var, le, label, ff, largs, type, name, file, sf;

    if (isList(fSig)) {
        printlist(fout, fSig);
    } else if (isProj(fSig, &i, x)) {
        fout << "proj" << i << '(' << ppsig(x, fEnv, 0, fMaxSize) << ')';
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
        fout << T(r);
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
        if (y == gGlobal->nil) {
            // rtable
            printfun(fout, "WRTbl2p", w, x);
        } else {
            // rwtable
            fout << "sigWRTbl4p(" << ppsig(w, fEnv, 0, fMaxSize);
            fout << "; " << ppsig(x, fEnv, 0, fMaxSize);
            fout << "; " << ppsig(y, fEnv, 0, fMaxSize);
            fout << "; " << ppsig(z, fEnv, 0, fMaxSize) << " )";
        }
    } else if (isSigRDTbl(fSig, x, y)) {
        printfun(fout, "sigRDTbl", x, y);
    } else if (isSigGen(fSig, x)) {
        fout << "sigGen(" << ppsig(x, fEnv, fPriority, fMaxSize) << ")";
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

    else {
        // cerr << "[[" << *fSig << "]]";
    }
    return fout;
}

#define SIG_INSERT_ID(exp)                                                                        \
    if (gGlobal->gSignalTable.find(fSig) == gGlobal->gSignalTable.end()) {                        \
        stringstream s;                                                                           \
        (exp);                                                                                    \
        gGlobal->gSignalTable[fSig] = make_pair(gGlobal->gSignalCounter, s.str());                \
        gGlobal->gSignalTrace.push_back("ID_" + std::to_string(gGlobal->gSignalCounter) + " = " + \
                                        s.str() + ";\n");                                         \
        gGlobal->gSignalCounter++;                                                                \
    }                                                                                             \
    fout << "ID_" << gGlobal->gSignalTable[fSig].first;

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
        fout << T(r);
    } else if (isSigWaveform(fSig)) {
        fout << "waveform{...}";
    } else if (isSigInput(fSig, &i)) {
        fout << "IN[" << i << "]";
    } else if (isSigOutput(fSig, &i, x)) {
        SIG_INSERT_ID(printout(s, i, x));
    }

    else if (isSigDelay1(fSig, x)) {
        SIG_INSERT_ID(printDelay(s, x, sigInt(1)));
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
        if (y == gGlobal->nil) {
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
        std::sort(gGlobal->gSignalTrace.begin(), gGlobal->gSignalTrace.end());
    }
    fout << "// Size = " << gGlobal->gSignalTrace.size() << endl;
    for (const auto& it : gGlobal->gSignalTrace) {
        fout << it;
    }
}
