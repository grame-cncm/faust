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

#include <vector>
#include "ppsig.hh"
#include "Text.hh"
#include "binop.hh"
#include "exception.hh"
#include "global.hh"
#include "prim2.hh"
#include "recursivness.hh"
#include "xtended.hh"

ppsig::ppsig(Tree s) : fSig(s), fEnv(gGlobal->nil), fPriority(0), fHideRecursion(false)
{
}

ostream& ppsig::printinfix(ostream& fout, const string& opname, int priority, Tree x, Tree y) const
{
    if (fPriority > priority) fout << "(";
    fout << ppsig(x, fEnv, priority) << opname << ppsig(y, fEnv, priority);
    if (fPriority > priority) fout << ")";
    return fout;
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x) const
{
    return fout << funame << '(' << ppsig(x, fEnv) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y) const
{
    return fout << funame << '(' << ppsig(x, fEnv) << ',' << ppsig(y, fEnv) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z) const
{
    return fout << funame << '(' << ppsig(x, fEnv) << ',' << ppsig(y, fEnv) << ',' << ppsig(z, fEnv) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree zz) const
{
    return fout << funame << '(' << ppsig(x, fEnv) << ',' << ppsig(y, fEnv) << ',' << ppsig(z, fEnv) << ','
                << ppsig(zz, fEnv) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2, Tree z3) const
{
    return fout << funame << '(' << ppsig(x, fEnv) << ',' << ppsig(y, fEnv) << ',' << ppsig(z, fEnv) << ','
                << ppsig(z2, fEnv) << ',' << ppsig(z3, fEnv) << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label, Tree lo, Tree hi, Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsig(lo, fEnv) << ',' << ppsig(hi, fEnv) << ',' << ppsig(step, fEnv) << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label, Tree cur, Tree lo, Tree hi, Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsig(cur, fEnv) << ',' << ppsig(lo, fEnv) << ',' << ppsig(hi, fEnv) << ','
                << ppsig(step, fEnv) << ')';
}

ostream& ppsig::printout(ostream& fout, int i, Tree x) const
{
    if (fPriority > 0) fout << "(";
    fout << "OUT" << i << " = " << ppsig(x, fEnv, 0);
    if (fPriority > 0) fout << ")";
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
        fout << sep << ppsig(hd(largs), fEnv);
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
    int d;

    if (isSigInt(delay, &d) && (d == 1)) {
        fout << ppsig(exp, fEnv, 8) << "'";
    } else {
        printinfix(fout, "@", 8, exp, delay);
    }
    return fout;
}

ostream& ppsig::printrec(ostream& fout, Tree var, Tree lexp, bool hide) const
{
    if (isElement(var, fEnv)) {
        fout << *var;
    } else if (hide) {
        fout << *var;
    } else {
        fout << "letrec(" << *var << " = " << ppsig(lexp, addElement(var, fEnv)) << ")";
    }
    return fout;
}

ostream& ppsig::printrec(ostream& fout, Tree lexp, bool hide) const
{
    fout << "debruijn(" << ppsig(lexp, fEnv) << ")";
    return fout;
}

ostream& ppsig::printextended(ostream& fout, Tree sig1) const
{
    string   sep = "";
    xtended* p   = (xtended*)getUserData(fSig);

    fout << p->name() << '(';
    for (int i = 0; i < sig1->arity(); i++) {
        fout << sep << ppsig(sig1->branch(i), fEnv);
        sep = ", ";
    }
    fout << ')';
    return fout;
}

ostream& ppsig::print(ostream& fout) const
{
    int    i;
    double r;
    Tree   c, sel, x, y, z, u, var, le, label, id, ff, largs, type, name, file, sf;

    if (isList(fSig)) {
        printlist(fout, fSig);
    } else if (isProj(fSig, &i, x)) {
        fout << "proj" << i << '(' << ppsig(x, fEnv) << ')';
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
        fout << ppsig(x, fEnv, 9) << "'";
    }
    else if (isSigDelay(fSig, x, y)) {
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

    else if (isSigTable(fSig, id, x, y)) {
        printfun(fout, "TABLE", x, y);
    } else if (isSigWRTbl(fSig, id, x, y, z)) {
        printfun(fout, "write", x, y, z);
    } else if (isSigRDTbl(fSig, x, y)) {
        printfun(fout, "read", x, y);
    } else if (isSigGen(fSig, x)) {
        fout << ppsig(x, fEnv, fPriority);
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

    else {
        cerr << "[[" << *fSig << "]]";
    }
    return fout;
}

#define SIG_INSERT_ID(exp) \
    if (gGlobal->gSignalTable.find(fSig) == gGlobal->gSignalTable.end()) { \
        stringstream s; \
        (exp); \
        gGlobal->gSignalTable[fSig] = make_pair(gGlobal->gSignalCounter, s.str()); \
        gGlobal->gSignalTrace.push_back("ID_" + std::to_string(gGlobal->gSignalCounter) + " = " + s.str() + ";\n"); \
        gGlobal->gSignalCounter++;\
    } \
    fout << "ID_" << gGlobal->gSignalTable[fSig].first; \

ostream& ppsigShared::printinfix(ostream& fout, const string& opname, int priority, Tree x, Tree y) const
{
    if (fPriority > priority) fout << "(";
    fout << ppsigShared(x, fEnv, priority) << opname << ppsigShared(y, fEnv, priority);
    if (fPriority > priority) fout << ")";
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
    return fout << funame << '(' << ppsigShared(x, fEnv) << ',' << ppsigShared(y, fEnv) << ',' << ppsigShared(z, fEnv) << ')';
}

ostream& ppsigShared::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree zz) const
{
    return fout << funame << '(' << ppsigShared(x, fEnv) << ',' << ppsigShared(y, fEnv) << ',' << ppsigShared(z, fEnv) << ','
    << ppsigShared(zz, fEnv) << ')';
}

ostream& ppsigShared::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2, Tree z3) const
{
    return fout << funame << '(' << ppsigShared(x, fEnv) << ',' << ppsigShared(y, fEnv) << ',' << ppsigShared(z, fEnv) << ','
    << ppsigShared(z2, fEnv) << ',' << ppsigShared(z3, fEnv) << ')';
}

ostream& ppsigShared::printui(ostream& fout, const string& funame, Tree label) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ')';
}

ostream& ppsigShared::printui(ostream& fout, const string& funame, Tree label, Tree lo, Tree hi, Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsigShared(lo, fEnv) << ',' << ppsigShared(hi, fEnv) << ',' << ppsigShared(step, fEnv) << ')';
}

ostream& ppsigShared::printui(ostream& fout, const string& funame, Tree label, Tree cur, Tree lo, Tree hi, Tree step) const
{
    fout << funame << '(';
    printlabel(fout, label);
    return fout << ',' << ppsigShared(cur, fEnv) << ',' << ppsigShared(lo, fEnv) << ',' << ppsigShared(hi, fEnv) << ','
    << ppsigShared(step, fEnv) << ')';
}

ostream& ppsigShared::printout(ostream& fout, int i, Tree x) const
{
    if (fPriority > 0) fout << "(";
    fout << "OUT" << i << " = " << ppsigShared(x, fEnv, 0);
    if (fPriority > 0) fout << ")";
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
    Tree   c, sel, x, y, z, u, var, le, label, id, ff, largs, type, name, file, sf;
    
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
        SIG_INSERT_ID(s << ppsig(x, fEnv, 9) << "'");
    }
    else if (isSigDelay(fSig, x, y)) {
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
    
    else if (isSigTable(fSig, id, x, y)) {
        SIG_INSERT_ID(printfun(s, "TABLE", x, y));
    } else if (isSigWRTbl(fSig, id, x, y, z)) {
        SIG_INSERT_ID(printfun(s, "write", x, y, z));
    } else if (isSigRDTbl(fSig, x, y)) {
        SIG_INSERT_ID(printfun(s, "read", x, y));
    } else if (isSigGen(fSig, x)) {
        SIG_INSERT_ID(s << ppsig(x, fEnv, fPriority));
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
    
    else {
        cerr << "[[" << *fSig << "]]";
    }
    return fout;
}

void ppsigShared::printIDs(ostream& fout)
{
    for (const auto& it : gGlobal->gSignalTrace) {
        fout << it;
    }
}
