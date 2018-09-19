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

/*****************************************************************************
    HISTORY
    22/01/05 : corrected bug on bool signals cached in float variables
*****************************************************************************/

#include "compile_scal.hh"
#include "timing.hh"

#include "compile.hh"
#include "sigtype.hh"

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "floats.hh"
#include "prim2.hh"
#include "privatise.hh"
#include "recursivness.hh"
#include "sigprint.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "xtended.hh"

#include "Text.hh"
#include "compatibility.hh"
#include "ppsig.hh"
#include "sigToGraph.hh"

using namespace std;

extern bool   gInPlace;
extern bool   gDrawSignals;
extern bool   gPrintJSONSwitch;
extern bool   gDrawSignals;
extern int    gMaxCopyDelay;
extern string gClassName;
extern string gMasterDocument;

string makeDrawPath();

static Klass* signal2klass(Klass* parent, const string& name, Tree sig)
{
    Type t = getCertifiedSigType(sig);  //, NULLENV);
    if (t->nature() == kInt) {
        ScalarCompiler C(new SigIntGenKlass(parent, name));
        C.compileSingleSignal(sig);
        return C.getClass();

    } else {
        ScalarCompiler C(new SigFloatGenKlass(parent, name));
        C.compileSingleSignal(sig);
        return C.getClass();
    }
}

/*****************************************************************************
                        getFreshID
*****************************************************************************/

map<string, int> ScalarCompiler::fIDCounters;

string ScalarCompiler::getFreshID(const string& prefix)
{
    if (fIDCounters.find(prefix) == fIDCounters.end()) {
        fIDCounters[prefix] = 0;
    }
    int n               = fIDCounters[prefix];
    fIDCounters[prefix] = n + 1;
    return subst("$0$1", prefix, T(n));
}

/*****************************************************************************
                            prepare
*****************************************************************************/

extern bool gDumpNorm;

Tree ScalarCompiler::prepare(Tree LS)
{
    startTiming("ScalarCompiler::prepare");
    startTiming("deBruijn2Sym");
    Tree L1 = deBruijn2Sym(LS);  // convert debruijn recursion into symbolic recursion
    endTiming("deBruijn2Sym");
    Tree L2 = simplify(L1);   // simplify by executing every computable operation
    Tree L3 = privatise(L2);  // Un-share tables with multiple writers

    // dump normal form
    if (gDumpNorm) {
        cout << ppsig(L3) << endl;
        exit(0);
    }

    recursivnessAnnotation(L3);  // Annotate L3 with recursivness information

    startTiming("typeAnnotation");
    typeAnnotation(L3);  // Annotate L3 with type information
    endTiming("typeAnnotation");

    sharingAnalysis(L3);                    // annotate L3 with sharing count
    fRates = new RateInferrer(L3);          // annotate L3 with rates
    fOccMarkup.markOccurences(fRates, L3);  // annotate L3 with occurences analysis
    // annotationStatistics();
    endTiming("ScalarCompiler::prepare");

    if (gDrawSignals) {
        ofstream dotfile(subst("$0-sig.dot", makeDrawPath()).c_str());
        sigToGraph(L3, dotfile, fRates);
    }

    return L3;
}

Tree ScalarCompiler::prepare2(Tree L0)
{
    startTiming("ScalarCompiler::prepare2");
    recursivnessAnnotation(L0);             // Annotate L0 with recursivness information
    typeAnnotation(L0);                     // Annotate L0 with type information
    sharingAnalysis(L0);                    // annotate L0 with sharing count
    fRates = new RateInferrer(L0);          // annotate L0 with rates
    fOccMarkup.markOccurences(fRates, L0);  // annotate L0 with occurences analysis
    endTiming("ScalarCompiler::prepare2");

    return L0;
}

/*****************************************************************************
                            compileMultiSignal
*****************************************************************************/

void ScalarCompiler::compileMultiSignal(Tree L)
{
    // contextor recursivness(0);
    L = prepare(L);  // optimize, share and annotate expression

    // std::cerr << "least common multiple rate (multiple) = " << fRates->commonRate() << std::endl;

    fClass->setCommonRate(fRates->commonRate());

    for (int i = 0; i < fClass->inputs(); i++) {
        fClass->addZone3(subst("$1* input$0 = input[$0];", T(i), xfloat()));
        if (gInPlace) {
            CS(sigInput(i));
        }
    }
    for (int i = 0; i < fClass->outputs(); i++) {
        fClass->addZone3(subst("$1* output$0 = output[$0];", T(i), xfloat()));
    }

    for (int i = 0; isList(L); L = tl(L), i++) {
        Tree sig = hd(L);
        fClass->setOutputRate(i, fRates->rate(sig));
        int p = fRates->periodicity(sig);
        if (p == 1) {
            fClass->addExecCode(subst("output$0[i] = $2$1;", T(i), CS(sig), xcast()));
        } else {
            fClass->addExecCode(subst("if ((i%$3)==0) { output$0[i/$3] = $2$1; }", T(i), CS(sig), xcast(), T(p)));
        }
    }

    generateMetaData();
    generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
    generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
    if (fDescription) {
        fDescription->ui(prepareUserInterfaceTree(fUIRoot));
    }

    if (gPrintJSONSwitch) {
        ofstream xout(subst("$0.json", makeDrawPath()).c_str());
        xout << fJSON.JSON();
    }
}

/*****************************************************************************
                            compileSingleSignal
*****************************************************************************/

void ScalarCompiler::compileSingleSignal(Tree sig)
{
    // contextor recursivness(0);
    sig = prepare2(sig);  // optimize and annotate expression
                          // std::cerr << "least common multiple rate (single) = " << fRates->commonRate() << std::endl;
    fClass->addExecCode(subst("output[i] = $0;", CS(sig)));
    generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
    generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
    if (fDescription) {
        fDescription->ui(prepareUserInterfaceTree(fUIRoot));
    }
}

/*****************************************************************************
                             CS : compile a signal
*****************************************************************************/

/**
 * Test if a signal is already compiled
 * @param sig the signal expression to compile.
 * @param name the string representing the compiled expression.
 * @return true is already compiled
 */
bool ScalarCompiler::getCompiledExpression(Tree sig, string& cexp)
{
    return fCompileProperty.get(sig, cexp);
}

/**
 * Set the string of a compiled expression is already compiled
 * @param sig the signal expression to compile.
 * @param cexp the string representing the compiled expression.
 * @return the cexp (for commodity)
 */
string ScalarCompiler::setCompiledExpression(Tree sig, const string& cexp)
{
    // cerr << "ScalarCompiler::setCompiledExpression : " << cexp << " ==> " << ppsig(sig) << endl;
    string old;
    if (fCompileProperty.get(sig, old) && (old != cexp)) {
        cerr << "ERROR already a compiled expression attached : " << old << " replaced by " << cexp << endl;
        exit(1);
    }
    fCompileProperty.set(sig, cexp);
    return cexp;
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string ScalarCompiler::CS(Tree sig)
{
    // contextor   contextRecursivness;
    string code;

    if (!getCompiledExpression(sig, code)) {
        // not compiled yet
        /*        if (getRecursivness(sig) != contextRecursivness.get()) {
                    contextRecursivness.set(getRecursivness(sig));
                }*/
        code = generateCode(sig);
        setCompiledExpression(sig, code);
    }
    return code;
}

/*****************************************************************************
                        generateCode : dispatch according to signal
*****************************************************************************/
/**
 * Main code generator dispatch.
 * @param sig the signal expression to compile.
 * @return the C code translation of sig
 */

string ScalarCompiler::generateCode(Tree sig)
{
#if 0
    fprintf(stderr, "CALL generateCode(");
    printSignal(sig, stderr);
    fprintf(stderr, ")\n");
#endif

    int    i;
    double r;
    Tree   c, sel, x, y, z, label, id, ff, largs, type, name, file;

    // printf("compilation of %p : ", sig); print(sig); printf("\n");

    if (getUserData(sig)) {
        return generateXtended(sig);
    } else if (isSigInt(sig, &i)) {
        return generateNumber(sig, T(i));
    } else if (isSigReal(sig, &r)) {
        return generateNumber(sig, T(r));
    } else if (isSigWaveform(sig)) {
        return generateWaveform(sig);
    } else if (isSigInput(sig, &i)) {
        fClass->setInputRate(i, fRates->rate(sig));
        return generateInput(sig, T(i));
    } else if (isSigOutput(sig, &i, x)) {
        return generateOutput(sig, T(i), CS(x));
    }

    else if (isSigFixDelay(sig, x, y)) {
        return generateFixDelay(sig, x, y);
    } else if (isSigPrefix(sig, x, y)) {
        return generatePrefix(sig, x, y);
    } else if (isSigIota(sig, x)) {
        return generateIota(sig, x);
    }

    else if (isSigBinOp(sig, &i, x, y)) {
        return generateBinOp(sig, i, x, y);
    } else if (isSigFFun(sig, ff, largs)) {
        return generateFFun(sig, ff, largs);
    } else if (isSigFConst(sig, type, name, file)) {
        return generateFConst(sig, tree2str(file), tree2str(name));
    } else if (isSigFVar(sig, type, name, file)) {
        return generateFVar(sig, tree2str(file), tree2str(name));
    }

    else if (isSigTable(sig, id, x, y)) {
        return generateTable(sig, x, y);
    } else if (isSigWRTbl(sig, id, x, y, z)) {
        return generateWRTbl(sig, x, y, z);
    } else if (isSigRDTbl(sig, x, y)) {
        return generateRDTbl(sig, x, y);
    }

    else if (isSigSelect2(sig, sel, x, y)) {
        return generateSelect2(sig, sel, x, y);
    } else if (isSigSelect3(sig, sel, x, y, z)) {
        return generateSelect3(sig, sel, x, y, z);
    }

    else if (isSigGen(sig, x)) {
        return generateSigGen(sig, x);
    }

    else if (isProj(sig, &i, x)) {
        return generateRecProj(sig, x, i);
    }

    else if (isSigIntCast(sig, x)) {
        return generateIntCast(sig, x);
    } else if (isSigFloatCast(sig, x)) {
        return generateFloatCast(sig, x);
    }

    else if (isSigButton(sig, label)) {
        return generateButton(sig, label);
    } else if (isSigCheckbox(sig, label)) {
        return generateCheckbox(sig, label);
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        return generateVSlider(sig, label, c, x, y, z);
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        return generateHSlider(sig, label, c, x, y, z);
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        return generateNumEntry(sig, label, c, x, y, z);
    }

    else if (isSigVBargraph(sig, label, x, y, z)) {
        return generateVBargraph(sig, label, x, y, CS(z));
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        return generateHBargraph(sig, label, x, y, CS(z));
    } else if (isSigAttach(sig, x, y)) {
        CS(y);
        return generateCacheCode(sig, CS(x));
    }

    else if (isSigUpSample(sig, x, y)) {
        return generateUpSample(sig, x, y);
    } else if (isSigDownSample(sig, x, y)) {
        return generateDownSample(sig, x, y);
    } else if (isSigVectorize(sig, x, y)) {
        return generateVectorize(sig, x, y);
    } else if (isSigSerialize(sig, x)) {
        return generateSerialize(sig, x);
    } else if (isSigConcat(sig, x, y)) {
        return generateConcat(sig, x, y);
    } else if (isSigVectorAt(sig, x, y)) {
        return generateVectorAt(sig, x, y);
    }

    else {
        printf("Error in compiling signal, unrecognized signal : ");
        print(sig);
        printf("\n");
        exit(1);
    }
    return "error in generate code";
}

/*****************************************************************************
                               NUMBERS
*****************************************************************************/

string ScalarCompiler::generateNumber(Tree sig, const string& exp)
{
    string      ctype, vname;
    Occurences* o = fOccMarkup.retrieveOccurences(sig);

    // check for number occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
    }
    return exp;
}

/*****************************************************************************
                               FOREIGN CONSTANTS
*****************************************************************************/

string ScalarCompiler::generateFConst(Tree sig, const string& file, const string& exp)
{
    string      ctype, vname;
    Occurences* o = fOccMarkup.retrieveOccurences(sig);

    addIncludeFile(file);

    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
    }
    return exp;
}

/*****************************************************************************
                               FOREIGN VARIABLES
*****************************************************************************/

string ScalarCompiler::generateFVar(Tree sig, const string& file, const string& exp)
{
    string ctype, vname;

    addIncludeFile(file);
    return generateCacheCode(sig, exp);
}

/*****************************************************************************
                               INPUTS - OUTPUTS
*****************************************************************************/

string ScalarCompiler::generateInput(Tree sig, const string& idx)
{
    int p = fRates->periodicity(sig);
    if (p == 1) {
        if (gInPlace) {
            // inputs must be cached for in-place transformations
            return generateVariableStore(sig, subst("$1input$0[i]", idx, icast()));
        } else {
            return generateCacheCode(sig, subst("$1input$0[i]", idx, icast()));
        }
    } else {
        if (gInPlace) {
            // inputs must be cached for in-place transformations
            return generateVariableStore(sig, subst("$1input$0[i/$2]", idx, icast(), T(p)));
        } else {
            return generateCacheCode(sig, subst("$1input$0[i/$2]", idx, icast(), T(p)));
        }
    }
}

string ScalarCompiler::generateOutput(Tree sig, const string& idx, const string& arg)
{
    string dst = subst("NEVERUSED output$0[i]", idx);
    fClass->addExecCode(subst("$0 = $2$1;", dst, arg, xcast()));
    return dst;
}

/*****************************************************************************
                               BINARY OPERATION
*****************************************************************************/
// dst, d3, src1, d1, src2, d2
void ScalarCompiler::pointwise(const string& op, int idx, const string& dst, const vector<int>& d3, const string& src1,
                               const vector<int>& d1, const string& src2, const vector<int>& d2)
{
    if (idx == 0) {
        fClass->addExecCode(subst("$0 = $1 $2 $3;", dst, src1, op, src2));
    } else {
        fClass->addExecCode(subst("for (int k$0=0; k$0<$1; k$0++) {", T(idx), T(d3[idx - 1])));
        if (idx > d1.size()) {
            pointwise(op, idx - 1, subst("$0.data[k$1]", dst, T(idx)), d3, src1, d1,
                      subst("$0.data[k$1]", src2, T(idx)), d2);
        } else if (idx > d2.size()) {
            pointwise(op, idx - 1, subst("$0.data[k$1]", dst, T(idx)), d3, subst("$0.data[k$1]", src1, T(idx)), d1,
                      src2, d2);
        } else {
            pointwise(op, idx - 1, subst("$0.data[k$1]", dst, T(idx)), d3, subst("$0.data[k$1]", src1, T(idx)), d1,
                      subst("$0.data[k$1]", src2, T(idx)), d2);
        }
        fClass->addExecCode("}");
    }
}
// dst, d3, src1, d1, src2, d2
void ScalarCompiler::unarywise(xtended* foo, Type t, int idx, const string& dst, const vector<int>& D,
                               const string& src1)
{
    if (idx == 0) {
        vector<string> args;
        vector<Type>   types;
        args.push_back(src1);
        types.push_back(t);

        string exp = foo->generateCode(fClass, args, types);
        fClass->addExecCode(subst("$0 = $1;", dst, exp));
    } else {
        fClass->addExecCode(subst("for (int k$0=0; k$0<$1; k$0++) {", T(idx), T(D[idx - 1])));
        unarywise(foo, t, idx - 1, subst("$0.data[k$1]", dst, T(idx)), D, subst("$0.data[k$1]", src1, T(idx)));
        fClass->addExecCode("}");
    }
}
// dst, d3, src1, d1, src2, d2
void ScalarCompiler::binarywise(xtended* foo, Type t1, Type t2, int idx, const string& dst, const vector<int>& d3,
                                const string& src1, const vector<int>& d1, const string& src2, const vector<int>& d2)
{
    if (idx == 0) {
        vector<string> args;
        vector<Type>   types;
        args.push_back(src1);
        args.push_back(src2);
        types.push_back(t1);
        types.push_back(t2);

        string exp = foo->generateCode(fClass, args, types);
        fClass->addExecCode(subst("$0 = $1;", dst, exp));
    } else {
        fClass->addExecCode(subst("for (int k$0=0; k$0<$1; k$0++) {", T(idx), T(d3[idx - 1])));
        if (idx > d1.size()) {
            binarywise(foo, t1, t2, idx - 1, subst("$0.data[k$1]", dst, T(idx)), d3, src1, d1,
                       subst("$0.data[k$1]", src2, T(idx)), d2);
        } else if (idx > d2.size()) {
            binarywise(foo, t1, t2, idx - 1, subst("$0.data[k$1]", dst, T(idx)), d3,
                       subst("$0.data[k$1]", src1, T(idx)), d1, src2, d2);
        } else {
            binarywise(foo, t1, t2, idx - 1, subst("$0.data[k$1]", dst, T(idx)), d3,
                       subst("$0.data[k$1]", src1, T(idx)), d1, subst("$0.data[k$1]", src2, T(idx)), d2);
        }
        fClass->addExecCode("}");
    }
}
string ScalarCompiler::generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2)
{
    Type t0 = getCertifiedSigType(sig);
    Type t1 = getCertifiedSigType(arg1);
    Type t2 = getCertifiedSigType(arg2);

    // get dimensions of arguments
    vector<int> d1;
    t1->dimensions(d1);
    vector<int> d2;
    t2->dimensions(d2);

    if ((d1.size() == 0) && (d2.size() == 0)) {
        // we deal with scalars
        if (opcode == kDiv) {
            // special handling for division, we always want a float division

            if (t1->nature() == kInt && t2->nature() == kInt) {
                return generateCacheCode(
                    sig, subst("($3($0) $1 $3($2))", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2), ifloat()));
            } else if (t1->nature() == kInt && t2->nature() == kReal) {
                return generateCacheCode(
                    sig, subst("($3($0) $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2), ifloat()));
            } else if (t1->nature() == kReal && t2->nature() == kInt) {
                return generateCacheCode(
                    sig, subst("($0 $1 $3($2))", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2), ifloat()));
            } else {
                return generateCacheCode(sig,
                                         subst("($0 $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2), ifloat()));
            }
        } else {
            return generateCacheCode(sig, subst("($0 $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2)));
        }
    } else {
        // we have to deal with at least one vector
        vector<int> d3;
        if (maxdimensions(d1, d2, d3)) {
            // vectors are compatibles
            string src1   = CS(arg1);
            string src2   = CS(arg2);
            string vtname = declareCType(sig);
            string dst    = getFreshID("V");
            fClass->addZone2(subst("$0 $1;", vtname, dst));
            fClass->addExecCode(subst("if ($0) {", fRates->tick(sig)));
            pointwise(gBinOpTable[opcode]->fName, d3.size(), dst, d3, src1, d1, src2, d2);
            fClass->addExecCode("}");
            return dst;
        } else {
            // incompatible
        }
    }
}

/*****************************************************************************
                               Primitive Operations
*****************************************************************************/

string ScalarCompiler::generateFFun(Tree sig, Tree ff, Tree largs)
{
    addIncludeFile(ffincfile(ff));  // printf("inc file %s\n", ffincfile(ff));
    addLibrary(fflibfile(ff));      // printf("lib file %s\n", fflibfile(ff));

    string code = ffname(ff);
    code += '(';
    string sep = "";
    for (int i = 0; i < ffarity(ff); i++) {
        code += sep;
        code += CS(nth(largs, i));
        sep = ", ";
    }
    code += ')';
    return generateCacheCode(sig, code);
}

/*****************************************************************************
                               CACHE CODE
*****************************************************************************/

void ScalarCompiler::getTypedNames(Type t, const string& prefix, string& ctype, string& vname)
{
    vector<int> D;
    t->dimensions(D);

    int dim = D.size();  // O is scalar
    if (dim > 0) {
        // t is a vector
        for (int i = D.size() - 1; i >= 0; i--) {
            ctype += "v" + T(D[i]);
        }
        if (t->nature() == kInt) {
            ctype += "int";
            vname = subst("vi$0", getFreshID(prefix));
        } else {
            ctype += ifloat();
            vname = subst("vf$0", getFreshID(prefix));
        }
    } else {
        if (t->nature() == kInt) {
            ctype = "int";
            vname = subst("i$0", getFreshID(prefix));
        } else {
            ctype = ifloat();
            vname = subst("f$0", getFreshID(prefix));
        }
    }
    std::cerr << "CTYPE : " << ctype << std::endl;
}

string ScalarCompiler::generateCacheCode(Tree sig, const string& exp)
{
    string      vname, ctype, code;
    int         sharing = getSharingCount(sig);
    Occurences* o       = fOccMarkup.retrieveOccurences(sig);

    // check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    // check for expression occuring in a different rate expression, thus needing
    // to be compiled in a separate statement event if they are not shared

    int  rate     = fRates->rate(sig);
    bool separate = (rate != o->getMinRate()) || (rate != o->getMaxRate());

    // if (separate) {
    // std::cerr << ppsig(sig) << " has rate " << rate << " in context [" << o->getMinRate() << "," << o->getMaxRate()
    // << "]" << std::endl;
    //}

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        if (sharing > 1) {
            return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname, o->getMaxDelay());
        } else {
            return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
        }

    } else if ((sharing > 1) || separate) {
        return generateVariableStore(sig, exp);

    } else if (sharing == 1) {
        return exp;

    } else {
        cerr << "Error in sharing count (" << sharing << ") for " << *sig << endl;
        exit(1);
    }

    return "Error in generateCacheCode";
}

// called by up and down

string ScalarCompiler::generateSeparateCode(Tree sig, const string& exp)
{
    string      vname, ctype, code;
    int         sharing = getSharingCount(sig);
    Occurences* o       = fOccMarkup.retrieveOccurences(sig);

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        if (sharing > 1) {
            return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname, o->getMaxDelay());
        } else {
            return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
        }

    } else {
        return generateVariableStore(sig, exp);
    }
}

string wrapPeriodicity(int p, const string& code)
{
    if (p == 1) {
        return subst("$0;", code);
    } else {
        return subst("if ((i%$0)==0) { $1; }", T(p), code);
    }
}

string wrapPostPeriodicity(int p, const string& code)
{
    if (p == 1) {
        return subst("$0;", code);
    } else {
        return subst("if (((i+1)%$0)==0) { $1; }", T(p), code);
    }
}

// like generateCacheCode but we force caching like if sharing was always > 1
string ScalarCompiler::forceCacheCode(Tree sig, const string& exp)
{
    string      vname, ctype, code;
    Occurences* o = fOccMarkup.retrieveOccurences(sig);

    // check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname, o->getMaxDelay());

    } else {
        return generateVariableStore(sig, exp);
    }
}

string ScalarCompiler::generateVariableStore(Tree sig, const string& exp)
{
    string vname, ctype;
    Type   t = getCertifiedSigType(sig);

    switch (t->variability()) {
        case kKonst:

            getTypedNames(t, "Const", ctype, vname);
            fClass->addDeclCode(subst("$0 \t$1;", ctype, vname));
            fClass->addInitCode(subst("$0 = $1;", vname, exp));
            break;

        case kBlock:

            getTypedNames(t, "Slow", ctype, vname);
            fClass->addFirstPrivateDecl(vname);
            fClass->addZone2(subst("$0 \t$1 = $2;", ctype, vname, exp));
            break;

        case kSamp:

            getTypedNames(t, "Temp", ctype, vname);
            //          fClass->addExecCode(subst("$0 $1;", ctype, vname));
            fClass->addZone2(subst("$0 $1;", ctype, vname));
            fClass->addExecCode(wrapPeriodicity(fRates->periodicity(sig), subst("$0 = $1", vname, exp)));
            break;
    }
    return vname;
}

/*****************************************************************************
                                    CASTING
*****************************************************************************/

string ScalarCompiler::generateIntCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, subst("int($0)", CS(x)));
}

string ScalarCompiler::generateFloatCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, subst("$1($0)", CS(x), ifloat()));
}

/*****************************************************************************
                            user interface elements
*****************************************************************************/

string ScalarCompiler::generateButton(Tree sig, Tree path)
{
    string varname = getFreshID("fbutton");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitCode(subst("$0 = 0.0;", varname));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateCheckbox(Tree sig, Tree path)
{
    string varname = getFreshID("fcheckbox");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitCode(subst("$0 = 0.0;", varname));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fslider");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fslider");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fentry");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
    string varname = getFreshID("fbargraph");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    Type t = getCertifiedSigType(sig);
    switch (t->variability()) {
        case kKonst:
            fClass->addInitCode(subst("$0 = $1;", varname, exp));
            break;

        case kBlock:
            fClass->addZone2(subst("$0 = $1;", varname, exp));
            break;

        case kSamp:
            fClass->addExecCode(subst("$0 = $1;", varname, exp));
            break;
    }

    // return varname;
    return generateCacheCode(sig, varname);
}

string ScalarCompiler::generateHBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
    string varname = getFreshID("fbargraph");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    Type t = getCertifiedSigType(sig);
    switch (t->variability()) {
        case kKonst:
            fClass->addInitCode(subst("$0 = $1;", varname, exp));
            break;

        case kBlock:
            fClass->addZone2(subst("$0 = $1;", varname, exp));
            break;

        case kSamp:
            fClass->addExecCode(subst("$0 = $1;", varname, exp));
            break;
    }

    // return varname;
    return generateCacheCode(sig, varname);
}

/*****************************************************************************
                                    TABLES
*****************************************************************************/

/*----------------------------------------------------------------------------
                        sigGen : initial table content
----------------------------------------------------------------------------*/

string ScalarCompiler::generateSigGen(Tree sig, Tree content)
{
    string klassname = getFreshID("SIG");
    string signame   = getFreshID("sig");

    fClass->addSubKlass(signal2klass(fClass, klassname, content));
    fClass->addInitCode(subst("$0 $1;", klassname, signame));
    fInstanceInitProperty.set(content, pair<string, string>(klassname, signame));

    return signame;
}

string ScalarCompiler::generateStaticSigGen(Tree sig, Tree content)
{
    string klassname = getFreshID("SIG");
    string signame   = getFreshID("sig");

    fClass->addSubKlass(signal2klass(fClass, klassname, content));
    fClass->addStaticInitCode(subst("$0 $1;", klassname, signame));
    fStaticInitProperty.set(content, pair<string, string>(klassname, signame));

    return signame;
}

/*----------------------------------------------------------------------------
                        sigTable : table declaration
----------------------------------------------------------------------------*/

string ScalarCompiler::generateTable(Tree sig, Tree tsize, Tree content)
{
    string generator(CS(content));
    Tree   g;
    string cexp;
    string ctype, vname;
    int    size;

    // already compiled but check if we need to add declarations

    assert(isSigGen(content, g));
    pair<string, string> kvnames;
    if (!fInstanceInitProperty.get(g, kvnames)) {
        // not declared here, we add a declaration
        bool b = fStaticInitProperty.get(g, kvnames);
        assert(b);
        fClass->addInitCode(subst("$0 $1;", kvnames.first, kvnames.second));
    }

    if (!isSigInt(tsize, &size)) {
        // fprintf(stderr, "error in ScalarCompiler::generateTable()\n"); exit(1);
        cerr << "error in ScalarCompiler::generateTable() : " << *tsize
             << " is not a constant integer table size expression " << endl;
        exit(1);
    }
    // definition du nom et du type de la table
    // A REVOIR !!!!!!!!!
    Type t = getCertifiedSigType(content);  //, tEnv);
    if (t->nature() == kInt) {
        vname = getFreshID("itbl");
        ctype = "int";
    } else {
        vname = getFreshID("ftbl");
        ctype = ifloat();
    }

    // declaration de la table
    fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(size)));

    // initialisation du generateur de contenu
    fClass->addInitCode(subst("$0.init(samplingFreq);", generator));
    // remplissage de la table
    fClass->addInitCode(subst("$0.fill($1,$2);", generator, T(size), vname));

    // on retourne le nom de la table
    return vname;
}

string ScalarCompiler::generateStaticTable(Tree sig, Tree tsize, Tree content)
{
    // string 		generator(CS(content));
    Tree   g;
    string cexp;
    string ctype, vname;
    int    size;

    assert(isSigGen(content, g));

    if (!getCompiledExpression(content, cexp)) {
        cexp = setCompiledExpression(content, generateStaticSigGen(content, g));
    } else {
        // already compiled but check if we need to add declarations
        pair<string, string> kvnames;
        if (!fStaticInitProperty.get(g, kvnames)) {
            // not declared here, we add a declaration
            bool b = fInstanceInitProperty.get(g, kvnames);
            assert(b);
            fClass->addStaticInitCode(subst("$0 $1;", kvnames.first, kvnames.second));
        }
    }

    if (!isSigInt(tsize, &size)) {
        // fprintf(stderr, "error in ScalarCompiler::generateTable()\n"); exit(1);
        cerr << "error in ScalarCompiler::generateTable() : " << *tsize
             << " is not a constant integer table size expression " << endl;
        exit(1);
    }
    // definition du nom et du type de la table
    // A REVOIR !!!!!!!!!
    Type t = getCertifiedSigType(content);  //, tEnv);
    if (t->nature() == kInt) {
        vname = getFreshID("itbl");
        ctype = "int";
    } else {
        vname = getFreshID("ftbl");
        ctype = ifloat();
    }

    // declaration de la table
    fClass->addDeclCode(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
    fClass->addStaticFields(subst("$0 \t$1::$2[$3];", ctype, fClass->getClassName(), vname, T(size)));

    // initialisation du generateur de contenu
    fClass->addStaticInitCode(subst("$0.init(samplingFreq);", cexp));
    // remplissage de la table
    fClass->addStaticInitCode(subst("$0.fill($1,$2);", cexp, T(size), vname));

    // on retourne le nom de la table
    return vname;
}

/*----------------------------------------------------------------------------
                        sigWRTable : table assignement
----------------------------------------------------------------------------*/

string ScalarCompiler::generateWRTbl(Tree sig, Tree tbl, Tree idx, Tree data)
{
    string tblName(CS(tbl));
    fClass->addExecCode(subst("$0[$1] = $2;", tblName, CS(idx), CS(data)));
    return tblName;
}

/*----------------------------------------------------------------------------
                        sigRDTable : table access
----------------------------------------------------------------------------*/

string ScalarCompiler::generateRDTbl(Tree sig, Tree tbl, Tree idx)
{
    // YO le 21/04/05 : La lecture des tables n'�ait pas mise dans le cache
    // et donc le code �ait dupliqu�(dans tester.dsp par exemple)
    // return subst("$0[$1]", CS(tEnv, tbl), CS(tEnv, idx));

    // cerr << "generateRDTable " << *sig << endl;
    // test the special case of a read only table that can be compiled
    // has a static member
    Tree id, size, content;
    if (isSigTable(tbl, id, size, content)) {
        string tblname;
        if (!getCompiledExpression(tbl, tblname)) {
            tblname = setCompiledExpression(tbl, generateStaticTable(tbl, size, content));
        }
        return generateCacheCode(sig, subst("$0[$1]", tblname, CS(idx)));
    } else {
        return generateCacheCode(sig, subst("$0[$1]", CS(tbl), CS(idx)));
    }
}

/*****************************************************************************
                               RECURSIONS
*****************************************************************************/

/**
 * Generate code for a projection of a group of mutually recursive definitions
 */
string ScalarCompiler::generateRecProj(Tree sig, Tree r, int i)
{
    string vname;
    Tree   var, le;

    if (!getVectorNameProperty(sig, vname)) {
        assert(isRec(r, var, le));
        generateRec(r, var, le);
        assert(getVectorNameProperty(sig, vname));
    }
    return "[[UNUSED EXP]]";  // make sure the resulting expression is never used in the generated code
}

/**
 * Generate code for a group of mutually recursive definitions
 */
void ScalarCompiler::generateRec(Tree sig, Tree var, Tree le)
{
    int N = len(le);

    vector<bool>   used(N);
    vector<int>    delay(N);
    vector<string> vname(N);
    vector<string> ctype(N);

    // prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i, sig);  // recreate each recursive definition
        if (fOccMarkup.retrieveOccurences(e)) {
            // this projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(e), "Rec", ctype[i], vname[i]);
            setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup.retrieveOccurences(e)->getMaxDelay();
        } else {
            // this projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }

    // generate delayline for each element of a recursive definition
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            Tree s = nth(le, i);
            generateDelayLine(s, ctype[i], vname[i], delay[i], CS(s));
        }
    }
}

/*****************************************************************************
                               PREFIX, DELAY A PREFIX VALUE
*****************************************************************************/

string ScalarCompiler::generatePrefix(Tree sig, Tree x, Tree e)
{
    Type te = getCertifiedSigType(sig);  //, tEnv);

    string vperm = getFreshID("M");
    string vtemp = getFreshID("T");

    string type = cType(te);

    fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
    fClass->addInitCode(subst("$0 = $1;", vperm, CS(x)));

    fClass->addExecCode(subst("$0 $1 = $2;", type, vtemp, vperm));
    fClass->addExecCode(subst("$0 = $1;", vperm, CS(e)));
    return vtemp;
}

/*****************************************************************************
                               IOTA(n)
*****************************************************************************/
static bool isPowerOf2(int n)
{
    return !(n & (n - 1));
}

string ScalarCompiler::generateIota(Tree sig, Tree n)
{
    int size;
    if (!isSigInt(n, &size)) {
        fprintf(stderr, "error in generateIota\n");
        exit(1);
    }

    string vperm = getFreshID("iota");

    fClass->addDeclCode(subst("int \t$0;", vperm));
    fClass->addInitCode(subst("$0 = 0;", vperm));

    if (isPowerOf2(size)) {
        fClass->addExecCode(subst("$0 = ($0+1)&$1;", vperm, T(size - 1)));
    } else {
        fClass->addExecCode(subst("if (++$0 == $1) $0=0;", vperm, T(size)));
    }
    return vperm;
}

// a revoir en utilisant la lecture de table et en partageant la construction de la paire de valeurs

/**
 * Generate a select2 code
 */

string ScalarCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    return generateCacheCode(sig, subst("(($0)?$1:$2)", CS(sel), CS(s2), CS(s1)));
}

/**
 * Generate a select3 code (using if-then-else)
 * ((int n = sel==0)? s0 : ((sel==1)? s1 : s2))
 * int nn; ((nn=sel) ? ((nn==1)? s1 : s2) : s0);
 */
string ScalarCompiler::generateSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
    return generateCacheCode(sig, subst("(($0==0)? $1 : (($0==1)?$2:$3) )", CS(sel), CS(s1), CS(s2), CS(s3)));
}

#if 0
string ScalarCompiler::generateSelect3  (Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
    Type t  = getCertifiedSigType(sig);
    Type t1 = getCertifiedSigType(s1);
    Type t2 = getCertifiedSigType(s2);
    Type t3 = getCertifiedSigType(s3);
    Type w  = min(t1,min(t2,t3));

    string type = cType(t);
    string var  = getFreshID("S");

    switch (w->variability())
    {
        case kKonst :
            fClass->addDeclCode(subst("$0 \t$1[3];", type, var));
            break;
        case kBlock :
            //fClass->addLocalDecl(type, subst("$0[3]", var));
            //fClass->addLocalVecDecl(type, var, 3);
            fClass->addSharedDecl(var);
            fClass->addZone1(subst("$0 \t$1[3];", type, var));
            break;
        case kSamp :
            fClass->addExecCode(subst("$0 \t$1[3];", type, var));
            break;
    }

    switch (t1->variability())
    {
        case kKonst :
            fClass->addInitCode(subst("$0[0] = $1;", var, CS(s1)));
            break;
        case kBlock :
            fClass->addZone2b(subst("$0[0] = $1;", var, CS(s1)));
            break;
        case kSamp :
            fClass->addExecCode(subst("$0[0] = $1;", var, CS(s1)));
            break;
    }

    switch (t2->variability())
    {
        case kKonst :
            fClass->addInitCode(subst("$0[1] = $1;", var, CS(s2)));
            break;
        case kBlock :
            fClass->addZone2b(subst("$0[1] = $1;", var, CS(s2)));
            break;
        case kSamp :
            fClass->addExecCode(subst("$0[1] = $1;", var, CS(s2)));
            break;
    }

    switch (t3->variability())
    {
        case kKonst :
            fClass->addInitCode(subst("$0[2] = $1;", var, CS(s3)));
            break;
        case kBlock :
            fClass->addZone2b(subst("$0[2] = $1;", var, CS(s3)));
            break;
        case kSamp :
            fClass->addExecCode(subst("$0[2] = $1;", var, CS(s3)));
            break;
    }

    return generateCacheCode(sig, subst("$0[$1]", var, CS(sel)));
}
#endif

/**
 * retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
string ScalarCompiler::generateXtended(Tree sig)
{
    xtended*       p = (xtended*)getUserData(sig);
    vector<string> args;
    vector<Type>   types;

    Type        t = getCertifiedSigType(sig);
    vector<int> D;
    t->dimensions(D);
    if ((sig->arity() == 1) && (D.size() > 0)) {
        string src    = CS(sig->branch(0));
        string vtname = declareCType(sig);
        string dst    = getFreshID("V");
        fClass->addZone2(subst("$0 $1;", vtname, dst));
        fClass->addExecCode(subst("if ($0) {", fRates->tick(sig)));
        unarywise(p, t, D.size(), dst, D, src);
        fClass->addExecCode("}");
        return dst;
    } else if ((sig->arity() == 2) && (D.size() > 0)) {
        string      src1 = CS(sig->branch(0));
        string      src2 = CS(sig->branch(1));
        Type        t1   = getCertifiedSigType(sig->branch(0));
        Type        t2   = getCertifiedSigType(sig->branch(1));
        vector<int> D1;
        t1->dimensions(D1);
        vector<int> D2;
        t2->dimensions(D2);

        string vtname = declareCType(sig);
        string dst    = getFreshID("V");
        fClass->addZone2(subst("$0 $1;", vtname, dst));
        fClass->addExecCode(subst("if ($0) {", fRates->tick(sig)));
        binarywise(p, t1, t2, D.size(), dst, D, src1, D1, src2, D2);
        fClass->addExecCode("}");
        return dst;
    } else {
        for (int i = 0; i < sig->arity(); i++) {
            args.push_back(CS(sig->branch(i)));
            types.push_back(getCertifiedSigType(sig->branch(i)));
        }

        if (p->needCache()) {
            return generateCacheCode(sig, p->generateCode(fClass, args, types));
        } else {
            return p->generateCode(fClass, args, types);
        }
    }
}

//------------------------------------------------------------------------------------------------

/*****************************************************************************
                        vector name property
*****************************************************************************/

/**
 * Set the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string representing the vector name.
 * @return true is already compiled
 */
void ScalarCompiler::setVectorNameProperty(Tree sig, const string& vecname)
{
    fVectorProperty.set(sig, vecname);
}

/**
 * Get the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string where to store the vector name.
 * @return true if the signal has this property, false otherwise
 */

bool ScalarCompiler::getVectorNameProperty(Tree sig, string& vecname)
{
    return fVectorProperty.get(sig, vecname);
}

/**
 * Compute the minimal power of 2 greater than x
 */

int ScalarCompiler::pow2limit(int x)
{
    int n = 2;
    while (n < x) {
        n = 2 * n;
    }
    return n;
}

/*****************************************************************************
                               N-SAMPLE FIXED DELAY : sig = exp@delay

    case 1-sample max delay :
        Y(t-0)	Y(t-1)
        Temp	Var						gLessTempSwitch = false
        V[0]	V[1]					gLessTempSwitch = true

    case max delay < gMaxCopyDelay :
        Y(t-0)	Y(t-1)	Y(t-2)  ...
        Temp	V[0]	V[1]	...		gLessTempSwitch = false
        V[0]	V[1]	V[2]	...		gLessTempSwitch = true

    case max delay >= gMaxCopyDelay :
        Y(t-0)	Y(t-1)	Y(t-2)  ...
        Temp	V[0]	V[1]	...
        V[0]	V[1]	V[2]	...


*****************************************************************************/

/**
 * Generate code for accessing a delayed signal. The generated code depend of
 * the maximum delay attached to exp and the gLessTempSwitch.
 */

string ScalarCompiler::generateFixDelay(Tree sig, Tree exp, Tree delay)
{
    int    mxd, d;
    string vecname;

    int period = fRates->periodicity(sig);

    // cerr << "ScalarCompiler::generateFixDelay sig = " << *sig << endl;
    // cerr << "ScalarCompiler::generateFixDelay exp = " << *exp << endl;
    // cerr << "ScalarCompiler::generateFixDelay del = " << *delay << endl;

    // ******** for debug purposes ********
    // std::cerr << ppsig(sig) << " has rate (in fix delay) " << rate << " in context [" << o->getMinRate() << "," <<
    // o->getMaxRate() << "]" << std::endl;
    string code = CS(exp);  // ensure exp is compiled to have a vector name

    mxd = fOccMarkup.retrieveOccurences(exp)->getMaxDelay();

    if (!getVectorNameProperty(exp, vecname)) {
        if (mxd == 0) {
            // cerr << "it is a pure zero delay : " << code << endl;
            return code;
        } else {
            cerr << "No vector name for : " << ppsig(exp) << endl;
            assert(0);
        }
    }

    if (mxd == 0) {
        // not a real vector name but a scalar name
        return vecname;

    } else if (mxd < gMaxCopyDelay) {
        if (isSigInt(delay, &d)) {
            return subst("$0[$1]", vecname, CS(delay));
        } else {
            return generateCacheCode(sig, subst("$0[$1]", vecname, CS(delay)));
        }

    } else {
        // long delay : we use a ring buffer of size 2^x
        int N = pow2limit(mxd + 1);
        return generateCacheCode(sig, subst("$0[(IOTA/$3-$1)&$2]", vecname, CS(delay), T(N - 1), T(period)));
    }
}

/**
 * Generate code for the delay mecchanism. The generated code depend of the
 * maximum delay attached to exp and the "less temporaries" switch
 */

string ScalarCompiler::generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
    string s = generateDelayVecNoTemp(sig, exp, ctype, vname, mxd);
    if (getCertifiedSigType(sig)->variability() < kSamp) {
        return exp;
    } else {
        return s;
    }
}

/**
 * Generate code for the delay mecchanism without using temporary variables
 */

string ScalarCompiler::generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype, const string& vname,
                                              int mxd)
{
    assert(mxd > 0);
    int p = fRates->periodicity(sig);

    // bool odocc = fOccMarkup.retrieveOccurences(sig)->hasOutDelayOccurences();

    if (mxd < gMaxCopyDelay) {
        // short delay : we copy
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(mxd + 1)));
        fClass->addInitCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(mxd + 1)));
        fClass->addExecCode(wrapPeriodicity(p, subst("$0[0] = $1", vname, exp)));

        // generate post processing copy code to update delay values
        if (mxd == 1) {
            fClass->addPostCode(wrapPostPeriodicity(p, subst("$0[1] = $0[0]", vname)));
        } else if (mxd == 2) {
            // fClass->addPostCode(subst("$0[2] = $0[1];", vname));
            fClass->addPostCode(wrapPostPeriodicity(p, subst("$0[2] = $0[1]; $0[1] = $0[0]", vname)));
        } else {
            fClass->addPostCode(
                wrapPostPeriodicity(p, subst("for (int i=$0; i>0; i--) $1[i] = $1[i-1]", T(mxd), vname)));
        }
        setVectorNameProperty(sig, vname);
        return subst("$0[0]", vname);

    } else {
        // generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
        int N = pow2limit(mxd + 1);

        // we need a iota index
        ensureIotaCode();

        // declare and init
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(N)));
        fClass->addInitCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(N)));

        // execute
        fClass->addExecCode(wrapPeriodicity(p, subst("$0[(IOTA/$3)&$1] = $2", vname, T(N - 1), exp, T(p))));
        setVectorNameProperty(sig, vname);
        return subst("$0[(IOTA/$2)&$1]", vname, T(N - 1), T(p));
    }
}

/**
 * Generate code for the delay lines induced by recursive definitions
 */

void ScalarCompiler::generateDelayLine(Tree sig, const string& ctype, const string& vname, int mxd, const string& exp)
{
    int p = fRates->periodicity(sig);

    // assert(mxd > 0);
    if (mxd == 0) {
        // cerr << "MXD==0 :  " << vname << " := " << exp << endl;
        // no need for a real vector
        fClass->addExecCode(subst("$0 \t$1;", ctype, vname));
        fClass->addExecCode(wrapPeriodicity(p, subst("$0 = $1", vname, exp)));

    } else if (mxd < gMaxCopyDelay) {
        // cerr << "small delay : " << vname << "[" << mxd << "]" << endl;

        // short delay : we copy
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(mxd + 1)));
        fClass->addInitCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(mxd + 1)));
        fClass->addExecCode(wrapPeriodicity(p, subst("$0[0] = $1", vname, exp)));

        // generate post processing copy code to update delay values
        if (mxd == 1) {
            fClass->addPostCode(wrapPostPeriodicity(p, subst("$0[1] = $0[0]", vname)));
        } else if (mxd == 2) {
            fClass->addPostCode(wrapPostPeriodicity(p, subst("$0[2] = $0[1]; $0[1] = $0[0]", vname)));
        } else {
            fClass->addPostCode(
                wrapPostPeriodicity(p, subst("for (int i=$0; i>0; i--) $1[i] = $1[i-1]", T(mxd), vname)));
        }

    } else {
        // generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
        int N = pow2limit(mxd + 1);

        // we need a iota index
        ensureIotaCode();

        // declare and init
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(N)));
        fClass->addInitCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(N)));

        // execute
        fClass->addExecCode(wrapPeriodicity(p, subst("$0[(IOTA/$3)&$1] = $2", vname, T(N - 1), exp, T(p))));
    }
}

/**
 * Generate up sampling code
 */

string ScalarCompiler::generateUpSample(Tree sig, Tree x, Tree n)
{
    return generateSeparateCode(sig, CS(x));
    //    return CS(x);
}

/**
 * Generate down sampling code
 */

string ScalarCompiler::generateDownSample(Tree sig, Tree x, Tree n)
{
    return generateSeparateCode(sig, CS(x));
}

/**
 * Generate s = vectorize(n:int, x:(A,r))
 *  A is the type of samples of x
 *  r is the rate of x
 *  c is the clock of x
 *  tick(x) = clock(x)!=clock(x)'
 *
 *  decl: struct VnA { A data[n]; }
 *  decl: VnA I1, I2, *Iw, *Ir;
 *  init: Iw=&I1; Ir=&I2;
 *  stmt: if (tick(x)) (*Iw).data[(clock(x)+(n-1))%n] = CS[[x]];
 *  stmt: if (tick(s)) swap(Iw,Ir);
 *  ------------------------------
 *  rtrn: (*Ir)
 */

string ScalarCompiler::generateVectorize(Tree sig, Tree n, Tree x)
{
    int vsize;
    if (isSigInt(n, &vsize)) {
        string code = CS(x);
        Type   t1   = getCertifiedSigType(sig);
        string typ1 = declareCType(sig);
        Type   t2   = getCertifiedSigType(x);
        string typ2 = t2->typeName();
        string id   = getFreshID("V");

        fClass->addDeclCode(subst("$0    $1_1,$1_2,*$1w,*$1r;", typ1, id));
        fClass->addInitCode(subst("$0w=&$0_1; $0r=&$0_2;", id));
        fClass->addExecCode(subst("if ($0) $5w->data[($1+$2)%$3]=$4;", fRates->tick(x), fRates->clock(x), T(vsize - 1),
                                  T(vsize), code, id));
        fClass->addExecCode(subst("if ($0) {$1* t=$2w; $2w=$2r; $2r=t;}", fRates->tick(sig), typ1, id));
        return generateCacheCode(sig, subst("(*$0r)", id));
    } else {
        return "vectorize error";
    }
}

/**
 * Generate Serialize
 */

string ScalarCompiler::generateSerialize(Tree sig, Tree x)
{
    string      code = CS(x);
    Type        t1   = getCertifiedSigType(x);
    VectorType* vt   = isVectorType(t1);
    if (vt) {
        return generateCacheCode(sig, subst("$0.data[$1%$2]", code, fRates->clock(sig), T(vt->size())));
    } else {
        return "error serialize";
    }
    //(*RD).data[i%5];
}

/**
 * declareCType(sig) : generate c++ declaration for the type of sig.
 * the declaration is added to the class only if it is a vector type
 * not declared yet.
 *
 */
string ScalarCompiler::declareCType(Tree sig)
{
    return declareCType(getCertifiedSigType(sig));
    /*
    Type t = getCertifiedSigType(sig);
    string vtname = t->typeName();
    if (fDeclaredTypes.count(vtname)==0) {
        VectorType* vt = isVectorType(t);
        if (vt) {
            string ctname = declareCType()
            string decl = subst("struct $0 { $2 data[$1]; $0(int n=0) { for(int i=0;i<$1;i++) data[i]=0;} };", vtname,
    T(vt->size()), vt->content()->typeName());
            //std::cerr << "DECLARATION : " << decl << std::endl;
            fClass->addDeclCode(decl);
        }
        fDeclaredTypes.insert(vtname);
    }
    return vtname;
    */
}

string ScalarCompiler::declareCType(Type t)
{
    string vtname = t->typeName();
    if (fDeclaredTypes.count(vtname) == 0) {
        VectorType* vt = isVectorType(t);
        if (vt) {
            string ctname = declareCType(vt->content());
            string decl   = subst("struct $0 { $2 data[$1]; $0(int n=0) { for(int i=0;i<$1;i++) data[i]=0;} };", vtname,
                                T(vt->size()), ctname);
            // std::cerr << "DECLARATION : " << decl << std::endl;
            fClass->addDeclCode(decl);
        }
        fDeclaredTypes.insert(vtname);
    }
    return vtname;
}

/**
 * Generate Concat
 * 			// vTemp4 = concat(vTemp1,vTemp3)
 *           if ((i%5)==0) {
 *				for (int j=0; j<3; j++) vTemp4.data[j]   = vTemp1.data[j];
 *				for (int j=0; j<2; j++) vTemp4.data[j+3] = vTemp3.data[j];
 *			}
 */
string ScalarCompiler::generateConcat(Tree sig, Tree x, Tree y)
{
    string      c1 = CS(x);
    string      c2 = CS(y);
    Type        t1 = getCertifiedSigType(sig);
    Type        tx = getCertifiedSigType(x);
    Type        ty = getCertifiedSigType(y);
    VectorType* vt = isVectorType(t1);
    VectorType* vx = isVectorType(tx);
    VectorType* vy = isVectorType(ty);
    if (vt && vx && vy) {
        string vtname = declareCType(sig);
        string id     = getFreshID("V");

        // create temporary variable to store the concatenation
        fClass->addZone2(subst("$0 $1;", vtname, id));
        fClass->addExecCode(
            subst("if ($0) { for (int j=0; j<$1; j++) $2.data[j] = $3.data[j]; for (int j=0; j<$4; j++) $2.data[j+$1] "
                  "= $5.data[j]; }",
                  fRates->tick(sig), T(vx->size()), id, c1, T(vy->size()), c2));
        return id;
    } else {
        return "concat internal error";
    }
}

/**
 * Generate vector access
 */

string ScalarCompiler::generateVectorAt(Tree sig, Tree x, Tree y)
{
    string c1 = CS(x);
    string c2 = CS(y);
    return subst("$0.data[$1]", c1, c2);
}

/**
 * Generate code for a unique IOTA variable increased at each sample
 * and used to index ring buffers.
 */
void ScalarCompiler::ensureIotaCode()
{
    if (!fHasIota) {
        fHasIota = true;
        fClass->addDeclCode("int \tIOTA;");
        fClass->addInitCode("IOTA = 0;");
        fClass->addPostCode("IOTA = IOTA+1;");
    }
}

/**
 * Generate code for a waveform. The waveform will be declared as a static field.
 * The name of the waveform is returned in vname and its size in size.
 */
void ScalarCompiler::declareWaveform(Tree sig, string& vname, int& size)
{
    // computes C type and unique name for the waveform
    string ctype;
    getTypedNames(getCertifiedSigType(sig), "Wave", ctype, vname);

    size = sig->arity();

    // Converts waveform into a string : "{a,b,c,...}"
    stringstream content;

    char sep = '{';
    for (int i = 0; i < size; i++) {
        content << sep << ppsig(sig->branch(i));
        sep = ',';
    }
    content << '}';

    // Declares the Waveform
    fClass->addDeclCode(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
    fClass->addDeclCode(subst("int \tidx$0;", vname));
    fClass->addInitCode(subst("idx$0 = 0;", vname));
    fClass->getTopParentKlass()->addStaticFields(
        subst("$0 \t$1::$2[$3] = ", ctype, fClass->getFullClassName(), vname, T(size)) + content.str() + ";");
}

string ScalarCompiler::generateWaveform(Tree sig)
{
    string vname;
    int    size;

    declareWaveform(sig, vname, size);
    fClass->addPostCode(subst("idx$0 = (idx$0 + 1) % $1;", vname, T(size)));
    return generateCacheCode(sig, subst("$0[idx$0]", vname));
}
