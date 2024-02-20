/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    Copyright (C) 2023-2023 INRIA
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

#include "ppbox.hh"
#include "Text.hh"
#include "boxes.hh"
#include "exception.hh"
#include "global.hh"
#include "list.hh"
#include "prim2.hh"
#include "signals.hh"
#include "xtended.hh"

using namespace std;

const char* prim0name(CTree* (*ptr)())
{
    return "prim0???";
}

const char* prim1name(CTree* (*ptr)(CTree*))
{
    if (ptr == sigDelay1) return "mem";
    if (ptr == sigIntCast) return "int";
    if (ptr == sigFloatCast) return "float";
    if (ptr == sigLowest) return "lowest";
    if (ptr == sigHighest) return "highest";
    return "prim1???";
}

const char* prim2name(CTree* (*ptr)(CTree*, CTree*))
{
    if (ptr == sigAdd) return "+";
    if (ptr == sigSub) return "-";
    if (ptr == sigMul) return "*";
    if (ptr == sigDiv) return "/";
    if (ptr == sigRem) return "%";

    if (ptr == sigAND) return "&";
    if (ptr == sigOR) return "|";
    if (ptr == sigXOR) return "xor";

    if (ptr == sigLeftShift) return "<<";
    if (ptr == sigARightShift) return ">>";
    if (ptr == sigLRightShift) return ">>>";

    if (ptr == sigLT) return "<";
    if (ptr == sigLE) return "<=";
    if (ptr == sigGT) return ">";
    if (ptr == sigGE) return ">=";
    if (ptr == sigEQ) return "==";
    if (ptr == sigNE) return "!=";

    if (ptr == sigDelay) return "@";
    if (ptr == sigPrefix) return "prefix";
    if (ptr == sigAttach) return "attach";
    if (ptr == sigEnable) return "enable";
    if (ptr == sigControl) return "control";

    return "prim2???";
}

const char* prim3name(CTree* (*ptr)(CTree*, CTree*, CTree*))
{
    if (ptr == sigReadOnlyTable) return "rdtable";
    if (ptr == sigSelect2) return "select2";
    if (ptr == sigAssertBounds) return "assertbounds";
    return "prim3???";
}

const char* prim4name(CTree* (*ptr)(CTree*, CTree*, CTree*, CTree*))
{
    if (ptr == sigSelect3) return "select3";
    return "prim4???";
}

const char* prim5name(CTree* (*ptr)(CTree*, CTree*, CTree*, CTree*, CTree*))
{
    if (ptr == sigWriteReadTable) return "rwtable";
    return "prim5???";
}

// Limit the box description string to max_size characters
string mBox(Tree b, int max_size)
{
    stringstream error;
    error << boxpp(b);
    string str = error.str();
    return (int(str.size()) > max_size) ? (str.substr(0, max_size) + " ...") : str;
}

static void streambinop(ostream& fout, Tree t1, const char* op, Tree t2, int curPriority, int upPriority)
{
    if (upPriority > curPriority) fout << '(';
    fout << boxpp(t1, curPriority) << op << boxpp(t2, curPriority);
    if (upPriority > curPriority) fout << ')';
}

static void streambinopShared(ostream& fout, Tree t1, const char* op, Tree t2, int curPriority, int upPriority)
{
    if (upPriority > curPriority) fout << '(';
    fout << boxppShared(t1, curPriority) << op << boxppShared(t2, curPriority);
    if (upPriority > curPriority) fout << ')';
}

static void printRule(ostream& fout, Tree rule)
{
    Tree lhs = left(rule);
    Tree rhs = right(rule);
    char sep = '(';
    while (!isNil(lhs)) {
        fout << sep << boxpp(hd(lhs));
        sep = ',';
        lhs = tl(lhs);
    }
    fout << ") => " << boxpp(rhs) << "; ";
}

/*****************************************************************************
     Convert type as a string
*****************************************************************************/

static string type2str(int type)
{
    switch (type) {
        case 0:
            return "int";

        case 1:
            return "float";

        default:
            return "";
    }
}

// If t has a node of type symbol, return its name, otherwise error
ostream& boxpp::print(ostream& fout) const
{
    int    i, id;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    Tree t1, t2, t3, ff, label, cur, min, max, step, type, name, file, arg, body, fun, args, abstr, genv, vis, lenv,
        ldef, slot, ident, rules, chan, ins, outs, lroutes;

    const char* str;
    xtended*    xt = (xtended*)getUserData(fBox);

    // Primitive elements
    if (xt)
        fout << xt->name();
    else if (isBoxInt(fBox, &i))
        fout << i;
    else if (isBoxReal(fBox, &r))
        fout << T(r);
    else if (isBoxCut(fBox))
        fout << '!';
    else if (isBoxWire(fBox))
        fout << '_';
    else if (isBoxIdent(fBox, &str))
        fout << str;
    else if (isBoxPrim0(fBox, &p0))
        fout << prim0name(p0);
    else if (isBoxPrim1(fBox, &p1))
        fout << prim1name(p1);
    else if (isBoxPrim2(fBox, &p2))
        fout << prim2name(p2);
    else if (isBoxPrim3(fBox, &p3))
        fout << prim3name(p3);
    else if (isBoxPrim4(fBox, &p4))
        fout << prim4name(p4);
    else if (isBoxPrim5(fBox, &p5))
        fout << prim5name(p5);

    else if (isBoxAbstr(fBox, arg, body))
        fout << "\\" << boxpp(arg) << ".(" << boxpp(body) << ")";
    else if (isBoxAppl(fBox, fun, args))
        fout << boxpp(fun) << boxpp(args);

    else if (isBoxWithLocalDef(fBox, body, ldef))
        fout << boxpp(body) << " with { " << envpp(ldef) << " }";

    // Foreign elements
    else if (isBoxFFun(fBox, ff)) {
        fout << "ffunction(" << type2str(ffrestype(ff));
        Tree namelist = nth(ffsignature(ff), 1);
        char sep      = ' ';
        for (int i1 = 0; i1 < gGlobal->gFloatSize; i1++) {
            fout << sep << tree2str(nth(namelist, i1));
            sep = '|';
        }
        sep = '(';
        for (int i1 = 0; i1 < ffarity(ff); i1++) {
            fout << sep << type2str(ffargtype(ff, i1));
            sep = ',';
        }
        fout << ')';
        fout << ',' << ffincfile(ff) << ',' << fflibfile(ff) << ')';
    } else if (isBoxFConst(fBox, type, name, file))
        fout << "fconstant(" << type2str(tree2int(type)) << ' ' << tree2str(name) << ", " << tree2str(file) << ')';
    else if (isBoxFVar(fBox, type, name, file))
        fout << "fvariable(" << type2str(tree2int(type)) << ' ' << tree2str(name) << ", " << tree2str(file) << ')';

    // Block diagram binary operator
    else if (isBoxSeq(fBox, t1, t2))
        streambinop(fout, t1, " : ", t2, 1, fPriority);
    else if (isBoxSplit(fBox, t1, t2))
        streambinop(fout, t1, "<:", t2, 1, fPriority);
    else if (isBoxMerge(fBox, t1, t2))
        streambinop(fout, t1, ":>", t2, 1, fPriority);
    else if (isBoxPar(fBox, t1, t2))
        streambinop(fout, t1, ",", t2, 2, fPriority);
    else if (isBoxRec(fBox, t1, t2))
        streambinop(fout, t1, "~", t2, 4, fPriority);

    // Iterative block diagram construction
    else if (isBoxIPar(fBox, t1, t2, t3))
        fout << "par(" << boxpp(t1) << ", " << boxpp(t2) << ") {" << boxpp(t3) << "}";
    else if (isBoxISeq(fBox, t1, t2, t3))
        fout << "seq(" << boxpp(t1) << ", " << boxpp(t2) << ") {" << boxpp(t3) << "}";
    else if (isBoxISum(fBox, t1, t2, t3))
        fout << "sum(" << boxpp(t1) << ", " << boxpp(t2) << ") {" << boxpp(t3) << "}";
    else if (isBoxIProd(fBox, t1, t2, t3))
        fout << "prod(" << boxpp(t1) << ", " << boxpp(t2) << ") {" << boxpp(t3) << "}";

    else if (isBoxInputs(fBox, t1))
        fout << "inputs(" << boxpp(t1) << ")";
    else if (isBoxOutputs(fBox, t1))
        fout << "outputs(" << boxpp(t1) << ")";

    // User interface
    else if (isBoxButton(fBox, label))
        fout << "button(" << tree2quotedstr(label) << ')';
    else if (isBoxCheckbox(fBox, label))
        fout << "checkbox(" << tree2quotedstr(label) << ')';
    else if (isBoxVSlider(fBox, label, cur, min, max, step)) {
        fout << "vslider(" << tree2quotedstr(label) << ", " << boxpp(cur) << ", " << boxpp(min) << ", " << boxpp(max)
             << ", " << boxpp(step) << ')';
    } else if (isBoxHSlider(fBox, label, cur, min, max, step)) {
        fout << "hslider(" << tree2quotedstr(label) << ", " << boxpp(cur) << ", " << boxpp(min) << ", " << boxpp(max)
             << ", " << boxpp(step) << ')';
    } else if (isBoxVGroup(fBox, label, t1)) {
        fout << "vgroup(" << tree2quotedstr(label) << ", " << boxpp(t1, 0) << ')';
    } else if (isBoxHGroup(fBox, label, t1)) {
        fout << "hgroup(" << tree2quotedstr(label) << ", " << boxpp(t1, 0) << ')';
    } else if (isBoxTGroup(fBox, label, t1)) {
        fout << "tgroup(" << tree2quotedstr(label) << ", " << boxpp(t1, 0) << ')';
    } else if (isBoxHBargraph(fBox, label, min, max)) {
        fout << "hbargraph(" << tree2quotedstr(label) << ", " << boxpp(min) << ", " << boxpp(max) << ')';
    } else if (isBoxMetadata(fBox, t1, t2)) {
        fout << boxpp(t1, 0) << "/* md */";
    } else if (isBoxVBargraph(fBox, label, min, max)) {
        fout << "vbargraph(" << tree2quotedstr(label) << ", " << boxpp(min) << ", " << boxpp(max) << ')';
    } else if (isBoxNumEntry(fBox, label, cur, min, max, step)) {
        fout << "nentry(" << tree2quotedstr(label) << ", " << boxpp(cur) << ", " << boxpp(min) << ", " << boxpp(max)
             << ", " << boxpp(step) << ')';
    } else if (isBoxSoundfile(fBox, label, chan)) {
        fout << "soundfile(" << tree2quotedstr(label) << ", " << boxpp(chan) << ')';
    }

    else if (isNil(fBox)) {
        fout << "()";
    } else if (isList(fBox)) {
        Tree l   = fBox;
        char sep = '(';

        do {
            fout << sep << boxpp(hd(l));
            sep = ',';
            l   = tl(l);
        } while (isList(l));

        fout << ')';

    } else if (isBoxWaveform(fBox)) {
        fout << "waveform";
        char sep = '{';
        for (int i1 = 0; i1 < fBox->arity(); i1++) {
            fout << sep << boxpp(fBox->branch(i1));
            sep = ',';
        }
        fout << '}';
        /*
        size_t n = fBox->arity();
        if (n < 6) {
            // small waveform, print all data
            fout << "waveform";
            char sep = '{';
            for (size_t i=0; i<n; i++) {
                fout << sep << boxpp(fBox->branch(i));
                sep = ',';
            }
            fout << '}';
        } else {
            // large waveform print only first and last values
            fout << "waveform{" << fBox->branch(0) << ", ..<" << n-2 << ">..," << fBox->branch(n-1)   << "}";
        }
        */

    } else if (isBoxEnvironment(fBox)) {
        fout << "environment";

    } else if (isClosure(fBox, abstr, genv, vis, lenv)) {
        fout << "closure[" << boxpp(abstr) << ", genv = " << envpp(genv) << ", lenv = " << envpp(lenv) << "]";
    } else if (isBoxComponent(fBox, label)) {
        fout << "component(" << tree2quotedstr(label) << ')';
    } else if (isBoxAccess(fBox, t1, t2)) {
        fout << boxpp(t1) << '.' << boxpp(t2);
    } else if (isImportFile(fBox, label)) {
        fout << "import(" << tree2quotedstr(label) << ')';
    } else if (isBoxSlot(fBox, &id)) {
        // fout << "#" << id;
        fout << "x" << id;
    } else if (isBoxSymbolic(fBox, slot, body)) {
        fout << "\\(" << boxpp(slot) << ").(" << boxpp(body) << ")";
    }

    // pattern Matching Extensions
    else if (isBoxCase(fBox, rules)) {
        fout << "case {";
        while (!isNil(rules)) {
            printRule(fout, hd(rules));
            rules = tl(rules);
        }
        fout << "}";
    }
#if 1
    // More useful for debugging output
    else if (isBoxPatternVar(fBox, ident)) {
        fout << "<" << boxpp(ident) << ">";
    }
#else
    // Beautify messages involving lhs patterns
    else if (isBoxPatternVar(fBox, ident)) {
        fout << boxpp(ident);
    }
#endif

    else if (isBoxPatternMatcher(fBox)) {
        fout << "PM[" << fBox << "]";
    }

    else if (isBoxRoute(fBox, ins, outs, lroutes)) {
        fout << "route(" << boxpp(ins) << "," << boxpp(outs) << "," << boxpp(lroutes) << ")";
    }

    else if (isBoxModulation(fBox, ident, body)) {
        fout << "modulate(" << *(ident) << ").(" << boxpp(body) << ")";
    }

    else if (isBoxError(fBox)) {
        fout << "ERROR";
    }

    // else if (isImportFile(box, filename)) {
    //    printf("filename %s\n", tree2str(filename));
    //    fout << tree2quotedstr(filename);
    //}

    // None of the previous tests succeded, then it is not a valid box
    else {
        stringstream error;
        error << "ERROR : box::print() : " << *fBox << " is not a valid box" << endl;
        throw faustexception(error.str());
    }

    return fout;
}

#define BOX_INSERT_ID(exp)                                                                                    \
    if (gGlobal->gBoxTable.find(fBox) == gGlobal->gBoxTable.end()) {                                          \
        stringstream s;                                                                                       \
        (exp);                                                                                                \
        gGlobal->gBoxTable[fBox] = make_pair(gGlobal->gBoxCounter, s.str());                                  \
        gGlobal->gBoxTrace.push_back("ID_" + std::to_string(gGlobal->gBoxCounter) + " = " + s.str() + ";\n"); \
        gGlobal->gBoxCounter++;                                                                               \
    }                                                                                                         \
    fout << "ID_" << gGlobal->gBoxTable[fBox].first;

ostream& boxppShared::print(ostream& fout) const
{
    int    i, id;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    Tree t1, t2, t3, ff, label, cur, min, max, step, type, name, file, arg, body, fun, args, abstr, genv, vis, lenv,
        ldef, slot, ident, rules, chan, ins, outs, lroutes;

    const char* str;
    xtended*    xt = (xtended*)getUserData(fBox);

    // Primitive elements
    if (xt)
        fout << xt->name();
    else if (isBoxInt(fBox, &i))
        fout << i;
    else if (isBoxReal(fBox, &r))
        fout << T(r);
    else if (isBoxCut(fBox))
        fout << '!';
    else if (isBoxWire(fBox))
        fout << '_';
    else if (isBoxIdent(fBox, &str))
        fout << str;
    else if (isBoxPrim0(fBox, &p0))
        fout << prim0name(p0);
    else if (isBoxPrim1(fBox, &p1))
        fout << prim1name(p1);
    else if (isBoxPrim2(fBox, &p2))
        fout << prim2name(p2);
    else if (isBoxPrim3(fBox, &p3))
        fout << prim3name(p3);
    else if (isBoxPrim4(fBox, &p4))
        fout << prim4name(p4);
    else if (isBoxPrim5(fBox, &p5))
        fout << prim5name(p5);

    else if (isBoxAbstr(fBox, arg, body)) {
        // BoxAbstr cannot be safely expanded with 'boxppShared' since 'arg' used in 'body' will be somewhat free
        fout << "\\" << boxpp(arg) << ".(" << boxpp(body) << ")";
    } else if (isBoxAppl(fBox, fun, args)) {
        BOX_INSERT_ID(s << boxppShared(fun) << boxppShared(args));
    } else if (isBoxWithLocalDef(fBox, body, ldef)) {
        BOX_INSERT_ID(s << boxppShared(body) << " with { " << envpp(ldef) << " }");
        // Foreign elements
    } else if (isBoxFFun(fBox, ff)) {
        if (gGlobal->gBoxTable.find(fBox) == gGlobal->gBoxTable.end()) {
            stringstream s;

            s << "ffunction(" << type2str(ffrestype(ff));
            Tree namelist = nth(ffsignature(ff), 1);
            char sep      = ' ';
            for (int i1 = 0; i1 < gGlobal->gFloatSize; i1++) {
                s << sep << tree2str(nth(namelist, i1));
                sep = '|';
            }
            sep = '(';
            for (int i1 = 0; i1 < ffarity(ff); i1++) {
                s << sep << type2str(ffargtype(ff, i1));
                sep = ',';
            }
            s << ')';
            s << ',' << ffincfile(ff) << ',' << fflibfile(ff) << ')';

            gGlobal->gBoxTable[fBox] = make_pair(gGlobal->gBoxCounter, s.str());
            gGlobal->gBoxTrace.push_back("ID_" + std::to_string(gGlobal->gBoxCounter) + " = " + s.str() + ";\n");
            gGlobal->gBoxCounter++;
        }
        // gGlobal->gBoxCounter used a ID
        fout << "ID_" << gGlobal->gBoxTable[fBox].first;
    } else if (isBoxFConst(fBox, type, name, file)) {
        BOX_INSERT_ID(s << "fconstant(" << type2str(tree2int(type)) << ' ' << tree2str(name) << ", " << tree2str(file)
                        << ')');
    } else if (isBoxFVar(fBox, type, name, file)) {
        BOX_INSERT_ID(s << "fvariable(" << type2str(tree2int(type)) << ' ' << tree2str(name) << ", " << tree2str(file)
                        << ')');
        // Block diagram binary operator
    } else if (isBoxSeq(fBox, t1, t2)) {
        BOX_INSERT_ID(streambinopShared(s, t1, " : ", t2, 1, fPriority));
    } else if (isBoxSplit(fBox, t1, t2)) {
        BOX_INSERT_ID(streambinopShared(s, t1, " <: ", t2, 1, fPriority));
    } else if (isBoxMerge(fBox, t1, t2)) {
        BOX_INSERT_ID(streambinopShared(s, t1, " :> ", t2, 1, fPriority));
    } else if (isBoxPar(fBox, t1, t2)) {
        BOX_INSERT_ID(streambinopShared(s, t1, ", ", t2, 2, fPriority));
    } else if (isBoxRec(fBox, t1, t2)) {
        BOX_INSERT_ID(streambinopShared(s, t1, " ~ ", t2, 4, fPriority));
        // Iterative block diagram construction
    } else if (isBoxIPar(fBox, t1, t2, t3)) {
        BOX_INSERT_ID(s << "par(" << boxppShared(t1) << ", " << boxppShared(t2) << ") {" << boxppShared(t3) << "}");
    } else if (isBoxISeq(fBox, t1, t2, t3)) {
        BOX_INSERT_ID(s << "seq(" << boxppShared(t1) << ", " << boxppShared(t2) << ") {" << boxppShared(t3) << "}");
    } else if (isBoxISum(fBox, t1, t2, t3)) {
        BOX_INSERT_ID(s << "sum(" << boxppShared(t1) << ", " << boxppShared(t2) << ") {" << boxppShared(t3) << "}");
    } else if (isBoxIProd(fBox, t1, t2, t3)) {
        BOX_INSERT_ID(s << "prod(" << boxppShared(t1) << ", " << boxppShared(t2) << ") {" << boxppShared(t3) << "}");
    } else if (isBoxInputs(fBox, t1)) {
        BOX_INSERT_ID(s << "inputs(" << boxppShared(t1) << ")");
    } else if (isBoxOutputs(fBox, t1)) {
        BOX_INSERT_ID(s << "outputs(" << boxppShared(t1) << ")");

        // User interface
    } else if (isBoxButton(fBox, label)) {
        BOX_INSERT_ID(s << "button(" << tree2quotedstr(label) << ')');
    } else if (isBoxCheckbox(fBox, label)) {
        BOX_INSERT_ID(s << "checkbox(" << tree2quotedstr(label) << ')');
    } else if (isBoxVSlider(fBox, label, cur, min, max, step)) {
        BOX_INSERT_ID(s << "vslider(" << tree2quotedstr(label) << ", " << boxppShared(cur) << ", " << boxppShared(min)
                        << ", " << boxppShared(max) << ", " << boxppShared(step) << ')');
    } else if (isBoxHSlider(fBox, label, cur, min, max, step)) {
        BOX_INSERT_ID(s << "hslider(" << tree2quotedstr(label) << ", " << boxppShared(cur) << ", " << boxppShared(min)
                        << ", " << boxppShared(max) << ", " << boxppShared(step) << ')');
    } else if (isBoxVGroup(fBox, label, t1)) {
        BOX_INSERT_ID(s << "vgroup(" << tree2quotedstr(label) << ", " << boxppShared(t1, 0) << ')');
    } else if (isBoxHGroup(fBox, label, t1)) {
        BOX_INSERT_ID(s << "hgroup(" << tree2quotedstr(label) << ", " << boxppShared(t1, 0) << ')');
    } else if (isBoxTGroup(fBox, label, t1)) {
        BOX_INSERT_ID(s << "tgroup(" << tree2quotedstr(label) << ", " << boxppShared(t1, 0) << ')');
    } else if (isBoxHBargraph(fBox, label, min, max)) {
        BOX_INSERT_ID(s << "hbargraph(" << tree2quotedstr(label) << ", " << boxppShared(min) << ", " << boxppShared(max)
                        << ')');
    } else if (isBoxMetadata(fBox, t1, t2)) {
        BOX_INSERT_ID(s << boxppShared(t1, 0) << "/* md */");
    } else if (isBoxVBargraph(fBox, label, min, max)) {
        BOX_INSERT_ID(s << "vbargraph(" << tree2quotedstr(label) << ", " << boxppShared(min) << ", " << boxppShared(max)
                        << ')');
    } else if (isBoxNumEntry(fBox, label, cur, min, max, step)) {
        BOX_INSERT_ID(s << "nentry(" << tree2quotedstr(label) << ", " << boxppShared(cur) << ", " << boxppShared(min)
                        << ", " << boxppShared(max) << ", " << boxppShared(step) << ')');
    } else if (isBoxSoundfile(fBox, label, chan)) {
        BOX_INSERT_ID(s << "soundfile(" << tree2quotedstr(label) << ", " << boxppShared(chan) << ')');
    }

    else if (isNil(fBox)) {
        fout << "()";
    } else if (isList(fBox)) {
        if (gGlobal->gBoxTable.find(fBox) == gGlobal->gBoxTable.end()) {
            stringstream s;
            Tree         l   = fBox;
            char         sep = '(';

            do {
                s << sep << boxppShared(hd(l));
                sep = ',';
                l   = tl(l);
            } while (isList(l));

            s << ')';
            gGlobal->gBoxTable[fBox] = make_pair(gGlobal->gBoxCounter, s.str());
            gGlobal->gBoxTrace.push_back("ID_" + std::to_string(gGlobal->gBoxCounter) + " = " + s.str() + ";\n");
            gGlobal->gBoxCounter++;
        }
        // gGlobal->gBoxCounter used a ID
        fout << "ID_" << gGlobal->gBoxTable[fBox].first;
    } else if (isBoxWaveform(fBox)) {
        if (gGlobal->gBoxTable.find(fBox) == gGlobal->gBoxTable.end()) {
            stringstream s;
            s << "waveform";
            char sep = '{';
            for (int i1 = 0; i1 < fBox->arity(); i1++) {
                s << sep << boxpp(fBox->branch(i1));
                sep = ',';
            }
            s << '}';
            gGlobal->gBoxTable[fBox] = make_pair(gGlobal->gBoxCounter, s.str());
            gGlobal->gBoxTrace.push_back("ID_" + std::to_string(gGlobal->gBoxCounter) + " = " + s.str() + ";\n");
            gGlobal->gBoxCounter++;
        }
        // gGlobal->gBoxCounter used a ID
        fout << "ID_" << gGlobal->gBoxTable[fBox].first;
    } else if (isBoxEnvironment(fBox)) {
        fout << "environment";
    } else if (isClosure(fBox, abstr, genv, vis, lenv)) {
        BOX_INSERT_ID(s << "closure[" << boxppShared(abstr) << ", genv = " << envpp(genv) << ", lenv = " << envpp(lenv)
                        << "]");
    } else if (isBoxComponent(fBox, label)) {
        fout << "component(" << tree2quotedstr(label) << ')';
    } else if (isBoxAccess(fBox, t1, t2)) {
        fout << boxppShared(t1) << '.' << boxppShared(t2);
    } else if (isImportFile(fBox, label)) {
        fout << "import(" << tree2quotedstr(label) << ')';
    } else if (isBoxSlot(fBox, &id)) {
        // fout << "#" << id;
        fout << "x" << id;
    } else if (isBoxSymbolic(fBox, slot, body)) {
        // BoxSymbolic cannot be safely expanded with 'boxppShared' since 'slot' used in 'body' will be somewhat free
        fout << "\\(" << boxpp(slot) << ").(" << boxpp(body) << ")";
    }

    // pattern Matching Extensions
    else if (isBoxCase(fBox, rules)) {
        fout << "case {";
        while (!isNil(rules)) {
            printRule(fout, hd(rules));
            rules = tl(rules);
        }
        fout << "}";
    }
#if 1
    // More useful for debugging output
    else if (isBoxPatternVar(fBox, ident)) {
        fout << "<" << boxppShared(ident) << ">";
    }
#else
    // Beautify messages involving lhs patterns
    else if (isBoxPatternVar(fBox, ident)) {
        fout << boxppShared(ident);
    }
#endif

    else if (isBoxPatternMatcher(fBox)) {
        fout << "PM[" << fBox << "]";
    }

    else if (isBoxRoute(fBox, ins, outs, lroutes)) {
        BOX_INSERT_ID(s << "route(" << boxppShared(ins) << "," << boxppShared(outs) << "," << boxppShared(lroutes)
                        << ")");
    }

    else if (isBoxError(fBox)) {
        fout << "ERROR";
    }

    // None of the previous tests succeded, then it is not a valid box
    else {
        stringstream error;
        error << "ERROR : boxppShared::print() : " << *fBox << " is not a valid box" << endl;
        throw faustexception(error.str());
    }

    return fout;
}

void boxppShared::printIDs(ostream& fout)
{
    for (const auto& it : gGlobal->gBoxTrace) { fout << it; }
}

/*****************************************************************************
     Environment printing
*****************************************************************************/

ostream& envpp::print(ostream& fout) const
{
    Tree l = fEnv;

    fout << '{';
    // const char* sep = "";
    // while (isList(l)) {
    //     fout << sep << boxpp(hd(hd(l))) << "=" << boxpp(tl(hd(l)));
    //     sep = ", ";
    //     l   = tl(l);
    // }
    fout << *l;
    fout << '}';
    return fout;
}
