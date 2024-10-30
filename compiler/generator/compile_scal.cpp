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

/*****************************************************************************
    HISTORY
    22/01/05 : corrected bug on bool signals cached in float variables
*****************************************************************************/

#include <math.h>
#include <stdio.h>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Schedule.hh"
#include "compatibility.hh"
#include "compile.hh"
#include "compile_scal.hh"
#include "dlcodegen.hh"
#include "floats.hh"
#include "normalform.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "recursivness.hh"
#include "sharing.hh"
#include "sigDependenciesGraph.hh"
#include "sigNewConstantPropagation.hh"
#include "sigPromotion.hh"
#include "sigRecursiveDependencies.hh"
#include "sigRetiming.hh"
#include "sigToGraph.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "timing.hh"
#include "xtended.hh"

#undef TRACE

// Old delays are supposed to work while new delays are in progress
#define OLDDELAY 0

using namespace std;

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

Tree ScalarCompiler::prepare(Tree LS)
{
    startTiming("prepare");
    Tree L1 = simplifyToNormalForm(LS);

    // dump normal form
    if (gGlobal->gDumpNorm == 0) {
        cout << ppsig(L1) << endl;
        throw faustexception("Dump normal form finished...\n");
    } else if (gGlobal->gDumpNorm == 1) {
        ppsigShared(L1, cout);
        throw faustexception("Dump shared normal form finished...\n");
    } else if (gGlobal->gDumpNorm == 2) {
        // Print signal tree type
        SignalTypePrinter printer(L1);
        throw faustexception("Dump signal type finished...\n");
    }
    // No more table privatisation
    Tree L2 = newConstantPropagation(L1);

    startTiming("conditionAnnotation");
    conditionAnnotation(L2);
    endTiming("conditionAnnotation");

    startTiming("recursivnessAnnotation");
    recursivnessAnnotation(L2);  // Annotate L2 with recursivness information
    endTiming("recursivnessAnnotation");

    startTiming("L2 typeAnnotation");
    typeAnnotation(L2, true);  // Annotate L2 with type information and check causality
    endTiming("L2 typeAnnotation");

    startTiming("sharingAnalysis");
    sharingAnalysis(L2, fSharingKey);  // Annotate L2 with sharing count
    endTiming("sharingAnalysis");

    startTiming("occurrences analysis");
    delete fOccMarkup;
    fOccMarkup = new OccMarkup(fConditionProperty);
    fOccMarkup->mark(L2);  // Annotate L2 with occurrences analysis
    endTiming("occurrences analysis");

    endTiming("prepare");

    if (gGlobal->gDrawSignals) {
        if (gGlobal->gDrawRetiming) {
            startTiming("retiming");
            Tree L3 = sigRetiming(L2);
            endTiming("retiming");
            startTiming("retimed type annotation");
            typeAnnotation(L3, true);
            endTiming("retimed type annotation");
            ofstream dotfile(subst("$0-rtsig.dot", gGlobal->makeDrawPath()).c_str());
            sigToGraph(L3, dotfile);
        }
        ofstream dotfile(subst("$0-sig.dot", gGlobal->makeDrawPath()).c_str());
        sigToGraph(L2, dotfile);
    }

    return L2;
}

Tree ScalarCompiler::prepare2(Tree L0)
{
    startTiming("ScalarCompiler::prepare2");

    recursivnessAnnotation(L0);        // Annotate L0 with recursivness information
    typeAnnotation(L0, true);          // Annotate L0 with type information
    sharingAnalysis(L0, fSharingKey);  // annotate L0 with sharing count

    delete fOccMarkup;
    fOccMarkup = new OccMarkup();
    fOccMarkup->mark(L0);  // annotate L0 with occurrences analysis

    endTiming("ScalarCompiler::prepare2");
    return L0;
}

/*****************************************************************************
 Condition annotation due to enabled expressions
 *****************************************************************************/

#if _DNF_
#define CND2CODE dnf2code
#define _OR_ dnfOr
#define _AND_ dnfAnd
#define _CND_ dnfCond
#else
#define CND2CODE cnf2code
#define _OR_ cnfOr
#define _AND_ cnfAnd
#define _CND_ cnfCond
#endif

string ScalarCompiler::dnf2code(Tree cc)
{
    if (cc == gGlobal->nil) {
        return "";
    }
    Tree c1 = hd(cc);
    cc      = tl(cc);
    if (cc == gGlobal->nil) {
        return and2code(c1);
    } else {
        return subst("($0 || $1)", and2code(c1), dnf2code(cc));
    }
}

string ScalarCompiler::and2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return "";
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        return subst("($0 && $1)", CS(c1), and2code(cs));
    }
}

string ScalarCompiler::cnf2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return "";
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return or2code(c1);
    } else {
        return subst("(($0) && $1)", or2code(c1), cnf2code(cs));
    }
}

string ScalarCompiler::or2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return "";
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        return subst("($0 || $1)", CS(c1), or2code(cs));
    }
}

// Temporary implementation for test purposes
string ScalarCompiler::getConditionCode(Tree sig)
{
    Tree cc = fConditionProperty[sig];
    if ((cc != 0) && (cc != gGlobal->nil)) {
        return CND2CODE(cc);
    } else {
        return "";
    }
}

#if 0
void ScalarCompiler::conditionStatistics(Tree l)
{
    for (const auto& p : fConditionProperty) {
        fConditionStatistics[p.second]++;
    }
    std::cout << "\nConditions statistics" << std::endl;
    for (const auto& p : fConditionStatistics) {
        std::cout << ppsig(p.first) << ":" << p.second << std::endl;
        
    }
}
#endif

void ScalarCompiler::conditionStatistics(Tree l)
{
    map<Tree, int>
        fConditionStatistics;  // used with the new X,Y:enable --> sigEnable(X*Y,Y>0) primitive
    for (const auto& p : fConditionProperty) {
        for (Tree lc = p.second; !isNil(lc); lc = tl(lc)) {
            fConditionStatistics[hd(lc)]++;
        }
    }
    std::cout << "\nConditions statistics" << std::endl;
    for (const auto& p : fConditionStatistics) {
        std::cout << ppsig(p.first) << ":" << p.second << std::endl;
    }
}

void ScalarCompiler::conditionAnnotation(Tree l)
{
    while (isList(l)) {
        conditionAnnotation(hd(l), gGlobal->nil);
        l = tl(l);
    }
}

void ScalarCompiler::conditionAnnotation(Tree t, Tree nc)
{
    // Check if we need to annotate the tree with new conditions
    auto p = fConditionProperty.find(t);
    if (p != fConditionProperty.end()) {
        Tree cc = p->second;
        Tree xc = _OR_(cc, nc);
        if (cc == xc) {
            // Tree t already correctly annotated, nothing to change
            return;
        } else {
            // we need to re-annotate the tree with a new condition
            nc        = xc;
            p->second = nc;
        }
    } else {
        // first visit
        fConditionProperty[t] = nc;
    }

    // Annotate the subtrees with the new condition nc
    // which is either the nc passed as argument or nc <- (cc v nc)
    Tree x, y;
    if (isSigControl(t, x, y)) {
        // specific annotation case for SigControl
        conditionAnnotation(y, nc);
        conditionAnnotation(x, _AND_(nc, _CND_(y)));
    } else {
        // general annotation case
        // Annotate the sub signals with nc
        tvec subsig;
        int  n = getSubSignals(t, subsig);
        if (n > 0 && !isSigGen(t)) {
            for (int i = 0; i < n; i++) {
                conditionAnnotation(subsig[i], nc);
            }
        }
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
    string old;
    if (fCompileProperty.get(sig, old) && (old != cexp)) {
        // stringstream error;
        // error << "ERROR already a compiled expression attached : " << old << " replaced by " <<
        // cexp << endl; throw faustexception(error.str());
    }

    fCompileProperty.set(sig, cexp);
    return cexp;
}

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
    faustassert(vecname.size() > 0);
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
 * Make sure sig has a vector name property, if not use the one passed in parameter.
 * @param a name in case not already named
 * @param sig the signal expression.
 * @return the vector name associated with sig
 */

std::string ScalarCompiler::ensureVectorNameProperty(const std::string altname, Tree sig)
{
    std::string vecname;
    if (!getVectorNameProperty(sig, vecname)) {
        vecname = altname;
        setVectorNameProperty(sig, vecname);
    }
    return vecname;
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */

string ScalarCompiler::CS(Tree sig)
{
    // contextor contextRecursivness;
    string code;

    if (!getCompiledExpression(sig, code)) {
// not compiled yet
/*
 if (getRecursivness(sig) != contextRecursivness.get()) {
    contextRecursivness.set(getRecursivness(sig));
 }
 */
#ifdef TRACE
        int step = gGlobal->gSTEP;
        std::cerr << "\n"
                  << step << " [order: " << fScheduleOrder[sig] << "] "
                  << "::" << sig << "\t: generateCode( " << ppsig(sig, 10) << " )" << std::endl;
#endif
        code = generateCode(sig);
        setCompiledExpression(sig, code);

#ifdef TRACE
        std::cerr << "\n"
                  << step << " [order: " << fScheduleOrder[sig] << "] "
                  << "::" << sig << "\t: ============> " << code << std::endl;
#endif
    }
    return code;
}

/*****************************************************************************
 compileMultiSignal
 *****************************************************************************/

void ScalarCompiler::compileMultiSignal(Tree L)
{
    // contextor recursivness(0);
    L = prepare(L);  // optimize, share and annotate expression

    for (int i = 0; i < fClass->inputs(); i++) {
        fClass->addZone3(subst("$1* input$0 = &input[$0][index]; // Zone 3", T(i), xfloat()));
        // Deactivated for now
        // if (gGlobal->gInPlace) {
        //     CS(sigInput(i));
        // }
    }
    for (int i = 0; i < fClass->outputs(); i++) {
        fClass->addZone3(subst("$1* output$0 = &output[$0][index]; // Zone 3", T(i), xfloat()));
    }

    // force a specific compilation order
    auto G = immediateGraph(L);
    auto S = dfschedule(G);
    // register the compilation order S for debug purposes
    {
        int jj = 0;
        for (auto& s : S.elements()) {
            int  pnum;
            Tree rg;
            fScheduleOrder[s] = ++jj;
#if 0
            if (isProj(s, &pnum, rg)) {
                if (isSignalRecursive(s)) {
                    // std::cerr << jj << " proj " << pnum << " of " << *rg << " is recursive"
                    //<< std::endl;
                } else {
                    std::cerr << jj << " proj " << pnum << " of " << *rg
                              << " is NOT recursive and could be simplified: "
                              /*<< ppsig(getProjDefinition(s))*/
                              << std::endl;
                }
            }
#endif
        }
    }

#ifdef TRACE
    std::cerr << "\nBEFORE COMPILING" << std::endl;
    std::cerr << G << std::endl;
    std::cerr << S << std::endl;

    std::cerr << "\nCOMPILE SCHEDULE" << std::endl;
#endif
    // gGlobal->gSTEP = 0;
    for (auto& s : S.elements()) {
        if (isNil(s)) {
            std::cerr << "NOT SUPPOSED TO HAPPEN: We have a Nil in the schedule !" << std::endl;
            faustassert(false);
        }
        int lSTEP = gGlobal->gSTEP;  // conveninient for debug
        CS(s);
        gGlobal->gSTEP++;
    }

    for (int i = 0; isList(L); L = tl(L), i++) {
        Tree s = hd(L);
        fClass->addExecCode(Statement("", subst("output$0[i] = $2($1);  // Zone Exec Code", T(i),
                                                generateCacheCode(s, CS(s)), xcast())));
    }

    generateMetaData();
    generateUserInterfaceTree(fUITree.prepareUserInterfaceTree(), true);
    generateMacroInterfaceTree("", fUITree.prepareUserInterfaceTree());
    if (fDescription) {
        fDescription->ui(fUITree.prepareUserInterfaceTree());
    }

    if (gGlobal->gPrintJSONSwitch) {
        ofstream xout(subst("$0.json", gGlobal->makeDrawPath()).c_str());
        xout << fJSON.JSON();
    }

    ensureIotaCode();
}

/*****************************************************************************
 compileSingleSignal
 *****************************************************************************/

void ScalarCompiler::compileSingleSignal(Tree sig)
{
    // contextor recursivness(0);
    sig = prepare2(sig);  // optimize and annotate expression

#ifdef TRACE
    std::cerr << "\nSTART COMPILING SINGLE SIGNAL: " << ppsig(sig, 20) << std::endl;
#endif
    // force a specific compilation order
    auto G = immediateGraph(cons(sig, gGlobal->nil));
    auto S = dfschedule(G);
#ifdef TRACE
    std::cerr << "\nBEFORE COMPILING SINGLE SIGNAL" << std::endl;
    std::cerr << G << std::endl;
    std::cerr << S << std::endl;
#endif
    // register the compilation order S for debug purposes
    {
        int jj = 1000;
        for (auto& s : S.elements()) {
            fScheduleOrder[s] += ++jj;
        }
    }
#ifdef TRACE
    std::cerr << "\nCOMPILE SINGLE SIGNAL SCHEDULE" << std::endl;
#endif
    for (auto& s : S.elements()) {
        if (isNil(s)) {
            std::cerr << "NOT SUPPOSED TO HAPPEN: We have a Nil in the schedule !" << std::endl;
            faustassert(false);
        }
        int lSTEP = gGlobal->gSTEP;  // convenient for debug
        CS(s);
        gGlobal->gSTEP++;
    }

    fClass->addExecCode(Statement("", subst("output[i] = $0;", CS(sig))));
    generateUserInterfaceTree(fUITree.prepareUserInterfaceTree(), true);
    generateMacroInterfaceTree("", fUITree.prepareUserInterfaceTree());
    if (fDescription) {
        fDescription->ui(fUITree.prepareUserInterfaceTree());
    }

    ensureIotaCode();
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
    int     i;
    int64_t i64;
    double  r;
    Tree    size, gen, wi, ws, ri, c, sel, x, y, z, label, tb, ff, largs, type, name, file, sf;

    // printf("compilation of %p : ", sig); print(sig); printf("\n");

    if (getUserData(sig)) {
        return generateXtended(sig);
    } else if (isSigInt(sig, &i)) {
        return generateNumber(sig, T(i));
    } else if (isSigInt64(sig, &i64)) {
        return generateNumber(sig, T(i64));
    } else if (isSigReal(sig, &r)) {
        return generateNumber(sig, T(r));
    } else if (isSigWaveform(sig)) {
        return generateWaveform(sig);
    } else if (isSigInput(sig, &i)) {
        return generateInput(sig, T(i));
    } else if (isSigOutput(sig, &i, x)) {
        return generateOutput(sig, T(i), CS(x));
    }

    else if (isSigDelay(sig, x, y)) {
        return generateDelayAccess(sig, x, y);
    } else if (isSigPrefix(sig, x, y)) {
        return generatePrefix(sig, x, y);
    } else if (isSigBinOp(sig, &i, x, y)) {
        return generateBinOp(sig, i, x, y);
    } else if (isSigFFun(sig, ff, largs)) {
        return generateFFun(sig, ff, largs);
    } else if (isSigFConst(sig, type, name, file)) {
        return generateFConst(sig, tree2str(file), tree2str(name));
    } else if (isSigFVar(sig, type, name, file)) {
        return generateFVar(sig, tree2str(file), tree2str(name));
    }

    else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        return generateWRTbl(sig, size, gen, wi, ws);
    } else if (isSigRDTbl(sig, tb, ri)) {
        return generateRDTbl(sig, tb, ri);
    } else if (isSigGen(sig, x)) {
        return generateSigGen(sig, x);
    }

    else if (isSigSelect2(sig, sel, x, y)) {
        return generateSelect2(sig, sel, x, y);
    }

    else if (isProj(sig, &i, x)) {
        return generateRecProj(sig, x, i);
    }

    else if (isSigIntCast(sig, x)) {
        return generateIntCast(sig, x);
    } else if (isSigBitCast(sig, x)) {
        return generateBitCast(sig, x);
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
    }

    else if (isSigSoundfile(sig, label)) {
        return generateSoundfile(sig, label);
    } else if (isSigSoundfileLength(sig, sf, x)) {
        return generateCacheCode(sig, subst("$0cache->fLength[$1]", CS(sf), CS(x)));
    } else if (isSigSoundfileRate(sig, sf, x)) {
        return generateCacheCode(sig, subst("$0cache->fSR[$1]", CS(sf), CS(x)));
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        return generateCacheCode(sig, subst("(($1)$0cache->fBuffers)[$2][$0cache->fOffset[$3]+$4]",
                                            CS(sf), ifloatptrptr(), CS(x), CS(y), CS(z)));
    }

    else if (isSigAttach(sig, x, y)) {
        CS(y);
        return generateCacheCode(sig, CS(x));
    } else if (isSigControl(sig, x, y)) {
        return generateControl(sig, x, y);
    } else if (isSigAssertBounds(sig, x, y, z)) {
        /* no debug option for the moment */
        return generateCode(z);
    }
    /* we should not have any control at this stage */
    else {
        cerr << "ASSERT : when compiling, unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
    return "error in generated code";
}

/*****************************************************************************
 NUMBERS
 *****************************************************************************/

string ScalarCompiler::generateNumber(Tree sig, const string& exp)
{
    string       ctype, vname;
    Occurrences* o = fOccMarkup->retrieve(sig);

    // check for number occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay(), o->getDelayCount());
    }
    return exp;
}

/*****************************************************************************
 FOREIGN CONSTANTS
 *****************************************************************************/

string ScalarCompiler::generateFConst(Tree sig, const string& file, const string& exp_aux)
{
    // Special case for 02/25/19 renaming
    string exp = (exp_aux == "fSamplingFreq") ? "fSampleRate" : exp_aux;

    string       ctype, vname;
    Occurrences* o = fOccMarkup->retrieve(sig);

    addIncludeFile(file);

    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay(), o->getDelayCount());
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
    if (gGlobal->gInPlace) {
        // inputs must be cached for in-place transformations
        return forceCacheCode(sig, subst("$1input$0[i]", idx, icast()));
    } else {
        return generateCacheCode(sig, subst("$1input$0[i]", idx, icast()));
    }
}

string ScalarCompiler::generateOutput(Tree sig, const string& idx, const string& arg)
{
    string dst = subst("output$0[i]", idx);
    fClass->addExecCode(Statement("", subst("$0 = $2$1;", dst, arg, xcast())));
    return dst;
}

/*****************************************************************************
 BINARY OPERATION
 *****************************************************************************/

string ScalarCompiler::generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2)
{
    // Special case for -1*a2
    if ((opcode == kMul) && isMinusOne(arg1)) {
        std::string res = CS(arg2);
        if ((res[0] == '(') || (res[0] == 'f') || (res[0] == 'i')) {
            return subst("-$0", res);
        } else {
            return subst("-($0)", res);
        }
        // Special case for a1*-1
    } else if ((opcode == kMul) && isMinusOne(arg2)) {
        std::string res = CS(arg1);
        if ((res[0] == '(') || (res[0] == 'f') || (res[0] == 'i')) {
            return subst("-$0", res);
        } else {
            return subst("-($0)", res);
        }
    } else {
        return generateCacheCode(
            sig, subst("($0 $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2)));
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
    if (t->nature() == kInt) {
        ctype = "int";
        vname = subst("i$0", getFreshID(prefix));
    } else {
        ctype = ifloat();
        vname = subst("f$0", getFreshID(prefix));
    }
}

/**
 * @brief Avoid multiple computation of the same iota expression
 *
 * @param iota expression
 * @return variable name
 */
string ScalarCompiler::generateIotaCache(const std::string& exp)
{
    if (fIotaCache.find(exp) == fIotaCache.end()) {
        string vname = getFreshID("vIota");
        fClass->addExecCode(Statement("", subst("int $0 = $1;", vname, exp)));
        fIotaCache[exp] = vname;
    }
    return fIotaCache[exp];
}

string ScalarCompiler::generateCacheCode(Tree sig, const string& exp)
{
    string code;

    // check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    string       vname, ctype;
    int          sharing = getSharingCount(sig, fSharingKey);
    Occurrences* o       = fOccMarkup->retrieve(sig);
    faustassert(o);

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        if (sharing > 1) {
            return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname,
                                    o->getMaxDelay(), o->getDelayCount());
        } else {
            return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay(), o->getDelayCount());
        }

    } else if ((sharing > 1) || (o->hasMultiOccurrences())) {
        return generateVariableStore(sig, exp);

    } else if (sharing == 1) {
        return exp;

    } else {
        cerr << "ASSERT : sharing count (" << sharing << ") for " << *sig << endl;
        faustassert(false);
        return {};
    }
}

// like generateCacheCode but we force caching like if sharing was always > 1
string ScalarCompiler::forceCacheCode(Tree sig, const string& exp)
{
    string code;

    // check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    string       vname, ctype;
    Occurrences* o = fOccMarkup->retrieve(sig);
    faustassert(o);

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname,
                                o->getMaxDelay(), o->getDelayCount());
    } else {
        return generateVariableStore(sig, exp);
    }
}

// Definition of variables: Const (computed at init time), Slow (computed at control rate) and
// "Temp" (computed at sample rate)
string ScalarCompiler::generateVariableStore(Tree sig, const string& exp)
{
    string       vname, vname_perm, ctype;
    Type         t = getCertifiedSigType(sig);
    Occurrences* o = fOccMarkup->retrieve(sig);
    faustassert(o);

    switch (t->variability()) {
        case kKonst:
            getTypedNames(t, "Const", ctype, vname);
            // The variable is used in compute (kBlock or kSamp), so define is as a field in the DSP
            // struct
            if (o->getOccurrence(kBlock) || o->getOccurrence(kSamp)) {
                fClass->addDeclCode(subst("$0 \t$1; // step: $2", ctype, vname, T(gGlobal->gSTEP)));
                fClass->addInitCode(subst("$0 = $1; // step: $2", vname, exp, T(gGlobal->gSTEP)));
            } else {
                // Otherwise it can stay as a local variable
                // fClass->addInitCode(subst("$0 \t$1 = $2; // step: $3", ctype, vname, exp,
                // T(gGlobal->gSTEP))); FIX Bug const ???
                fClass->addDeclCode(subst("$0 \t$1; // step: $2", ctype, vname, T(gGlobal->gSTEP)));
                fClass->addInitCode(subst("$0 = $1; // step: $2", vname, exp, T(gGlobal->gSTEP)));
            }
            break;

        case kBlock:
            getTypedNames(t, "Slow", ctype, vname);
            fClass->addFirstPrivateDecl(vname);
            fClass->addZone2(
                subst("$0 \t$1 = $2; // step: $3", ctype, vname, exp, T(gGlobal->gSTEP)));
            break;

        case kSamp:
            getTypedNames(t, "Temp", ctype, vname);
            if (getConditionCode(sig) == "") {
                fClass->addExecCode(Statement(
                    "", subst("$0 \t$1 = $2; // step: $3", ctype, vname, exp, T(gGlobal->gSTEP))));
            } else {
                getTypedNames(t, "TempPerm", ctype, vname_perm);
                // need to be preserved because of new enable and control primitives
                fClass->addDeclCode(subst("$0 \t$1;", ctype, vname_perm));
                fClass->addInitCode(subst("$0 = 0;", vname_perm));
                // copy the object variable to the local one
                fClass->addZone2(subst("$0 \t$1 = $2;", ctype, vname, vname_perm));
                // execute the code
                fClass->addExecCode(
                    Statement(getConditionCode(sig), subst("$0 = $1;", vname, exp)));
                // copy the local variable to the object one
                fClass->addZone4(subst("$0 = $1;", vname_perm, vname));
            }
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

string ScalarCompiler::generateBitCast(Tree sig, Tree x)
{
    if (gGlobal->gFloatSize == 1) {
        return generateCacheCode(sig, subst("(*(int*)&$0)", CS(x)));
    } else if (gGlobal->gFloatSize == 2) {
        return generateCacheCode(sig, subst("((*(int64_t*)&$0)", CS(x)));
    } else {
        faustassert(false);
        return "";
    }
}

string ScalarCompiler::generateFloatCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, subst("$1($0)", CS(x), ifloat()));
}

/*****************************************************************************
 User interface elements
 *****************************************************************************/

string ScalarCompiler::generateButton(Tree sig, Tree path)
{
    string varname = getFreshID("fbutton");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = 0.0;", varname));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateCheckbox(Tree sig, Tree path)
{
    string varname = getFreshID("fcheckbox");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = 0.0;", varname));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fslider");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fslider");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max,
                                        Tree step)
{
    string varname = getFreshID("fentry");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
    string varname = getFreshID("fbargraph");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    Type t = getCertifiedSigType(sig);
    switch (t->variability()) {
        case kKonst:
            fClass->addInitUICode(subst("$0 = $1;", varname, exp));
            break;

        case kBlock:
            fClass->addZone2(subst("$0 = $1;", varname, exp));
            break;

        case kSamp:
            fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", varname, exp)));
            break;
    }

    // return varname;
    return generateCacheCode(sig, varname);
}

string ScalarCompiler::generateHBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
    string varname = getFreshID("fbargraph");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    Type t = getCertifiedSigType(sig);
    switch (t->variability()) {
        case kKonst:
            fClass->addInitUICode(subst("$0 = $1;", varname, exp));
            break;

        case kBlock:
            fClass->addZone2(subst("$0 = $1;", varname, exp));
            break;

        case kSamp:
            fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", varname, exp)));
            break;
    }

    // return varname;
    return generateCacheCode(sig, varname);
}

/*****************************************************************************
 Soundfile
 *****************************************************************************/

string ScalarCompiler::generateSoundfile(Tree sig, Tree path)
{
    string varname = getFreshID("fSoundfile");

    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    fClass->addDeclCode(subst("Soundfile* \t$0;", varname));

    fClass->addInitUICode(subst("if (uintptr_t($0) == 0) $0 = defaultsound;", varname));
    fClass->addFirstPrivateDecl(subst("$0cache", varname));

    fClass->addZone2(subst("Soundfile* $0cache = $0;", varname));
    fClass->addZone4(subst("$0 = $0cache;", varname));
    return varname;
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
    int  size;
    bool res = isSigInt(tsize, &size);
    // Size type is previously checked in sigWriteReadTable or sigReadOnlyTable
    faustassert(res);

    string generator(CS(content));
    Tree   g;
    string cexp;
    string ctype, vname;

    // Already compiled but check if we need to add declarations
    faustassert(isSigGen(content, g));
    pair<string, string> kvnames;
    if (!fInstanceInitProperty.get(g, kvnames)) {
        // Not declared here, we add a declaration
        bool b = fStaticInitProperty.get(g, kvnames);
        faustassert(b);
        fClass->addInitCode(subst("$0 $1;", kvnames.first, kvnames.second));
    }

    // Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    // Table declaration
    fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(size)));

    // Initialization of the content generator
    fClass->addInitCode(subst("$0.init(sample_rate);", generator));
    // Filling the table
    fClass->addInitCode(subst("$0.fill($1,$2);", generator, T(size), vname));

    // Returning the table name
    return vname;
}

string ScalarCompiler::generateStaticTable(Tree sig, Tree tsize, Tree content)
{
    int  size;
    bool res = isSigInt(tsize, &size);
    // Size type is previously checked in sigWriteReadTable or sigReadOnlyTable
    faustassert(res);

    Tree   g;
    string cexp;
    string ctype, vname;

    faustassert(isSigGen(content, g));

    if (!getCompiledExpression(content, cexp)) {
        cexp = setCompiledExpression(content, generateStaticSigGen(content, g));
    } else {
        // already compiled but check if we need to add declarations
        pair<string, string> kvnames;
        if (!fStaticInitProperty.get(g, kvnames)) {
            // not declared here, we add a declaration
            bool b = fInstanceInitProperty.get(g, kvnames);
            faustassert(b);
            fClass->addStaticInitCode(subst("$0 $1;", kvnames.first, kvnames.second));
        }
    }

    // Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    // Table declaration
    if (gGlobal->gMemoryManager >= 0) {
        fClass->addDeclCode(subst("static $0* \t$1;", ctype, vname));
        fClass->addStaticFields(subst("$0* \t$1::$2 = 0;", ctype, fClass->getClassName(), vname));
        fClass->addStaticInitCode(subst(
            "$0 = static_cast<$1*>(fManager->allocate(sizeof($1) * $2));", vname, ctype, T(size)));
        fClass->addStaticDestroyCode(subst("fManager->destroy($0);", vname));
    } else {
        fClass->addDeclCode(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
        fClass->addStaticFields(
            subst("$0 \t$1::$2[$3];", ctype, fClass->getClassName(), vname, T(size)));
    }

    // Initialization of the content generator
    fClass->addStaticInitCode(subst("$0.init(sample_rate);", cexp));
    // Filling the table
    fClass->addStaticInitCode(subst("$0.fill($1,$2);", cexp, T(size), vname));

    // Returning the table name
    return vname;
}

/*----------------------------------------------------------------------------
                        sigWRTable : table assignement
----------------------------------------------------------------------------*/

string ScalarCompiler::generateWRTbl(Tree sig, Tree size, Tree gen, Tree wi, Tree ws)
{
    string tblName = generateTable(sig, size, gen);
    // std::cerr << "wi = " << *wi << " ws = " << *ws << "\n";
    std::string swi = CS(wi);
    std::string sws = CS(ws);

    switch (getCertifiedSigType(sig)->variability()) {
        case kKonst:
            fClass->addInitCode(subst("$0[$1] = $2;", tblName, swi, sws));
            break;
        case kBlock:
            fClass->addZone2(subst("$0[$1] = $2;", tblName, swi, sws));
            break;
        default:
            fClass->addExecCode(
                Statement(getConditionCode(sig), subst("$0[$1] = $2;", tblName, swi, sws)));
            break;
    }

    // Return table access
    return tblName;
}

/*----------------------------------------------------------------------------
                        sigRDTable : table access
----------------------------------------------------------------------------*/

string ScalarCompiler::generateRDTbl(Tree sig, Tree tbl, Tree ri)
{
    // Test the special case of a read only table that can be compiled as a static member
    Occurrences* o = fOccMarkup->retrieve(sig);
#ifdef TRACE
    std::cerr << "generateRDTbl : " << sig << "; mxd=" << o->getMaxDelay()
              << "; delay count=" << o->getDelayCount() << "\n";
#endif
    Tree size, gen;
    if (isSigWRTbl(tbl, size, gen)) {
        // rdtable
        string tblname;
        if (!getCompiledExpression(tbl, tblname)) {
            tblname = setCompiledExpression(tbl, generateStaticTable(tbl, size, gen));
        }
        std::string ricode = CS(ri);
        std::string instr  = subst("$0[$1]", tblname, ricode);
        std::string result = generateCacheCode(sig, instr);
        return result;
    } else {
        // rwtable
        return generateCacheCode(sig, subst("$0[$1]", CS(tbl), CS(ri)));
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
    string pname, ctype;
    Tree   var, le;

    // if (!getVectorNameProperty(sig, vname)) {
    //     faustassert(isRec(r, var, le));
    //     // generateRec(r, var, le);
    //     // faustassert(getVectorNameProperty(sig, vname));
    //     std::string ctype;
    //     Type        ty = getCertifiedSigType(sig);
    //     getTypedNames(ty, "Reec", ctype, vname);
    //     setVectorNameProperty(sig, vname);
    //     int  delay = fOccMarkup->retrieve(sig)->getMaxDelay();
    //     int  count = fOccMarkup->retrieve(sig)->getDelayCount();
    //     bool mono  = isSigSimpleRec(sig);
    //     Tree def   = nth(le, i);
    //     fClass->addDeclCode(subst("// Recursion delay $0 is of type $1", vname,
    //     nameDelayType(analyzeDelayType(sig)))); fClass->addDeclCode(subst("// While its
    //     definition is of type $0", nameDelayType(analyzeDelayType(def))));
    //     generateDelayLine(analyzeDelayType(sig), ctype, vname, delay, count, mono, CS(def),
    //     getConditionCode(def));
    // }

    Type ty = getCertifiedSigType(sig);
    getTypedNames(ty, "Riiic", ctype, pname);
    string vecname = ensureVectorNameProperty(pname, sig);
    int    delay   = fOccMarkup->retrieve(sig)->getMaxDelay();
    int    count   = fOccMarkup->retrieve(sig)->getDelayCount();
    bool   mono    = isSigSimpleRec(sig);

    faustassert(isRec(r, var, le));
    Tree def = nth(le, i);
    fClass->addDeclCode(subst("// Recursion delay $0 is of type $1", vecname,
                              nameDelayType(analyzeDelayType(sig))));
    fClass->addDeclCode(
        subst("// While its definition is of type $0", nameDelayType(analyzeDelayType(def))));
    std::string dl0 = generateDelayLine(analyzeDelayType(sig), ctype, vecname, delay, count, mono,
                                        CS(def), getConditionCode(def));

    return dl0;
}

/**
 * @brief Check if sig is a simple recursive signal that can be expressed using a single variable
 *
 * @param sig the signal to analyse, typically proj(i,X)
 * @return true if sig is of type x = f(x') and x' is used only once. In this case the same variable
 * can be used both for x and x'
 * @return false
 */
bool ScalarCompiler::isSigSimpleRec(Tree sig)
{
    int  i;
    Tree x;

    // sig is a recursive projection
    if (isProj(sig, &i, x)) {
        Tree var, le;
        // the recursive group contains only one recursive signal
        if (isRec(x, var, le) && (len(le) == 1)) {
            int mxd   = fOccMarkup->retrieve(sig)->getMaxDelay();
            int count = fOccMarkup->retrieve(sig)->getDelayCount();
            // The maximum delay of sig is 1 and the delay count is 1
            if ((mxd == 1) && (count == 1)) {
                // sig@1 has only a single occurence (therefore in the definition of sig)
                Tree f = sigDelay(sig, sigInt(1));  // check if it is a delay
                if (fOccMarkup->retrieve(f)) {
                    // this projection is used
                    return !fOccMarkup->retrieve(f)->hasMultiOccurrences();
                }
            }
        }
    }
    return false;
}

/**
 * @brief indicate best delay implementation type for a signal according to its max delay and
 * various compilation options
 *
 * @param sig
 * @return DelayType
 */
DelayType ScalarCompiler::analyzeDelayType(Tree sig)
{
    Occurrences* occ = fOccMarkup->retrieve(sig);
    faustassert(occ != nullptr);
    int mxd   = occ->getMaxDelay();
    int count = occ->getDelayCount();

    if (mxd == 0) {
        return DelayType::kZeroDelay;
    }
    if (mxd == 1) {
        // check for special mono delay case
        int  i;
        Tree x, var, le;
        if (count == 1 && isProj(sig, &i, x) && isRec(x, var, le) && (len(le) == 1)) {
            // potential simple recursion if sig@1 is used only once
            Tree f = sigDelay(sig, sigInt(1));  // check if it is a delay
            if (fOccMarkup->retrieve(f) && !fOccMarkup->retrieve(f)->hasMultiOccurrences()) {
                return DelayType::kMonoDelay;
            }
        }
        return DelayType::kSingleDelay;
    }
    if (mxd <= gGlobal->gMaxCopyDelay) {
        return DelayType::kCopyDelay;
    }
    int dnsty = (100 * count) / mxd;
    if ((mxd <= gGlobal->gMaxDenseDelay) && (dnsty >= gGlobal->gMinDensity)) {
        return DelayType::kDenseDelay;
    }
    if (mxd <= gGlobal->gMaskDelayLineThreshold) {
        return DelayType::kMaskRingDelay;
    }
    return DelayType::kSelectRingDelay;
}

/**
 * Generate code for a group of mutually recursive definitions
 */
void ScalarCompiler::generateRec(Tree sig, Tree var, Tree le)
{
    faustassert(false);

    int N = len(le);

    vector<bool>   used(N);
    vector<int>    delay(N);
    vector<int>    count(N);
    vector<Tree>   exp(N);
    vector<string> vname(N);
    vector<string> ctype(N);
    vector<bool>   mono(N);

    // prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i, sig);  // recreate each recursive definition
        if (fOccMarkup->retrieve(e)) {
            // this projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(e), "Rec", ctype[i], vname[i]);
            setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup->retrieve(e)->getMaxDelay();
            count[i] = fOccMarkup->retrieve(e)->getDelayCount();
            mono[i]  = isSigSimpleRec(e);
            exp[i]   = e;

        } else {
            // this projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }
    // generate delayline for each element of a recursive definition
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            Tree def = nth(le, i);
            fClass->addDeclCode(subst("// Recursion delay $0 is of type $1", vname[i],
                                      nameDelayType(analyzeDelayType(exp[i]))));
            fClass->addDeclCode(subst("// While its definition is of type $0",
                                      nameDelayType(analyzeDelayType(def))));
            generateDelayLine(analyzeDelayType(exp[i]), ctype[i], vname[i], delay[i], count[i],
                              mono[i], CS(def), getConditionCode(def));
        }
    }
}

/*****************************************************************************
 Control
 *****************************************************************************/

string ScalarCompiler::generateControl(Tree sig, Tree x, Tree y)
{
    CS(y);
    return generateCacheCode(x, CS(x));
}

/*****************************************************************************
 PREFIX, DELAY A PREFIX VALUE
 *****************************************************************************/

string ScalarCompiler::generatePrefix(Tree sig, Tree x, Tree e)
{
    string vperm = getFreshID("pfPerm");
    string vtemp = getFreshID("pfTemp");
    string type  = (getCertifiedSigType(sig)->nature() == kInt) ? "int" : ifloat();

    fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
    fClass->addInitCode(subst("$0 = $1;", vperm, CS(x)));

    fClass->addExecCode(
        Statement(getConditionCode(sig), subst("$0 \t$1 = $2;", type, vtemp, vperm)));

    /*
    string res = CS(e);
    string vname;
    if (getVectorNameProperty(e, vname)) {
        setVectorNameProperty(sig, vname);
    } else {
        faustassert(false);
    }
    */

    fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", vperm, CS(e))));
    return vtemp;
}

/*****************************************************************************
 SELECT
 *****************************************************************************/

string ScalarCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    return generateCacheCode(sig, subst("(($0) ? $1 : $2)", CS(sel), CS(s2), CS(s1)));
}

/*****************************************************************************
 EXTENDED
 *****************************************************************************/

string ScalarCompiler::generateXtended(Tree sig)
{
    xtended*       p = (xtended*)getUserData(sig);
    vector<string> args;
    vector<Type>   types;

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

/*****************************************************************************
 N-SAMPLE FIXED DELAY : sig = exp@delay

 case 1-sample max delay :
 Y(t-0)	Y(t-1)
 V[0]	V[1]

 case max delay < gMaxCopyDelay :
 Y(t-0)	Y(t-1)	Y(t-2)  ...
 V[0]	V[1]	V[2]	...

 case max delay >= gMaxCopyDelay :
 Y(t-0)	Y(t-1)	Y(t-2)  ...
 V[0]	V[1]	V[2]	...

 *****************************************************************************/

/**
 * Generate code for accessing a delayed signal. The generated code depend of
 * the maximum delay attached to exp.
 */
string ScalarCompiler::generateDelayAccess(Tree sig, Tree exp, Tree delay)
{
#if OLDDELAY
    // cerr << "ScalarCompiler::generateDelayAccess sig = " << *sig << endl;
    // cerr << "ScalarCompiler::generateDelayAccess exp = " << *exp << endl;
    // cerr << "ScalarCompiler::generateDelayAccess del = " << *delay << endl;

    string code  = CS(exp);  // ensure exp is compiled to have a vector name
    int    mxd   = fOccMarkup->retrieve(exp)->getMaxDelay();
    int    count = fOccMarkup->retrieve(exp)->getDelayCount();
    bool   mono  = isSigSimpleRec(exp);
    string vecname;

    if (!getVectorNameProperty(exp, vecname)) {
        if (mxd == 0) {
            // cerr << "it is a pure zero delay : " << code << endl;
            return code;
        } else {
            cerr << "ASSERT : no vector name for : " << ppsig(exp, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }
    }

    if (mono || mxd == 0) {
        // not a real vector name but a scalar name
        return vecname;

    } else if (mxd <= count * gGlobal->gMaxCopyDelay) {
        return generateCacheCode(sig, subst("$0[$1]", vecname, CS(delay)));
#if 0 
        int d;
        if (isSigInt(delay, &d)) {
            return subst("$0[$1]", vecname, CS(delay));
        } else {
            return generateCacheCode(sig, subst("$0[$1]", vecname, CS(delay)));
        }
#endif
    } else {
        int         N   = pow2limit(mxd + 1);
        std::string idx = subst("(IOTA-$0)&$1", CS(delay), T(N - 1));
        return generateCacheCode(sig, subst("$0[$1]", vecname, generateIotaCache(idx)));
    }
#else
    // FIX: We don't compile the delayed signal anymore. This is done by the general scheduling.
    // But we make sure the delayed signal has a vector name.

    // string    code = CS(exp);  // ensure exp is compiled to have a vector name
    std::string ctype, pname;
    getTypedNames(getCertifiedSigType(sig), "Veeec", ctype, pname);
    string    vecname = ensureVectorNameProperty(pname, exp);
    int       mxd     = fOccMarkup->retrieve(exp)->getMaxDelay();
    DelayType dt      = analyzeDelayType(exp);
#ifdef TRACE
    std::cerr << "\nDELAYED: We expect this delayed signal to be compiled elsewhere at step "
              << fScheduleOrder[exp] << " -- " << exp << " :: " << ppsig(exp, 10) << std::endl;
#endif
    std::string result;
    switch (dt) {
        case DelayType::kNotADelay:
            faustexception("Try to compile has a delay something that is not a delay");
            result = "";
            break;

        case DelayType::kZeroDelay:
            result = vecname;
            break;

        case DelayType::kMonoDelay:
            result = vecname;
            break;

        case DelayType::kSingleDelay:
        case DelayType::kCopyDelay:
        case DelayType::kDenseDelay:
            result = subst("$0[$1]", vecname, CS(delay));
            break;

        case DelayType::kMaskRingDelay:
        case DelayType::kSelectRingDelay:
            int         N   = pow2limit(mxd + 1);
            std::string idx = subst("(IOTA-$0)&$1", CS(delay), T(N - 1));
            result          = subst("$0[$1]", vecname, generateIotaCache(idx));
            break;
    }
    return generateCacheCode(sig, result);

#endif
}

/**
 * Generate code for the delay mechanism. The generated code depend of the
 * maximum delay attached to exp and the "less temporaries" switch
 */
string ScalarCompiler::generateDelayVec(Tree sig, const string& exp, const string& ctype,
                                        const string& vname, int mxd, int count)
{
    string s = generateDelayVecNoTemp(sig, exp, ctype, vname, mxd, count);
    if (getCertifiedSigType(sig)->variability() < kSamp) {
        return exp;
    } else {
        return s;
    }
}

/**
 * Generate code for the delay mechanism without using temporary variables
 */

/*
    DlCodeGen g(ctype, vname, gGlobal->gVecSize, mxd);
    fClass->addDeclCode(g.globalDeclare());
    fClass->addClearCode(g.globalInit());
    fClass->addZone2(g.localDeclare());
    fClass->addZone3(g.pointerSetup());
    fClass->addZone3(g.copyGlobalToLocal());
    fClass->addPostCode(Statement(ccs, g.advance()));
    fClass->addZone3Post(g.copyLocalToGlobal());
*/
string ScalarCompiler::generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype,
                                              const string& pname, int mxd, int count)
{
    faustassert(mxd > 0);

    // We make sure to use the vector name associated with signal, or we provide one
    std::string vecname = ensureVectorNameProperty(pname, sig);
    bool        mono    = isSigSimpleRec(sig);
    // bool odocc = fOccMarkup->retrieve(sig)->hasOutDelayOccurrences();
    string    ccs = getConditionCode(sig);
    DelayType dt  = analyzeDelayType(sig);
    // fClass->addDeclCode(subst("// Normal delay $0 is of type $1", vname, nameDelayType(dt)));
    string access = generateDelayLine(dt, ctype, vecname, mxd, count, mono, exp, ccs);
    // setVectorNameProperty(sig, vname);
    return access;
#if 0
#if OLDDELAY
    if (mono) {
        return vname;
    } else if (mxd <= count * gGlobal->gMaxCopyDelay) {
        return subst("$0[0]", vname);
    } else {
        int         N   = pow2limit(mxd + 1);
        std::string idx = subst("IOTA&$0", T(N - 1));
        return subst("$0[$1]", vname, generateIotaCache(idx));
    }
#else
    switch (dt) {
        case DelayType::kZeroDelay:
            return vname;

        case DelayType::kMonoDelay:
            return vname;

        case DelayType::kSingleDelay:
        case DelayType::kCopyDelay:
        case DelayType::kDenseDelay:
            return subst("$0[0]", vname);

        case DelayType::kMaskRingDelay:
        case DelayType::kSelectRingDelay:
            int         N   = pow2limit(mxd + 1);
            std::string idx = subst("IOTA&$0", T(N - 1));
            return subst("$0[$1]", vname, generateIotaCache(idx));
    }
#endif
#endif
}

/**
 * Generate code for the delay mechanism without using temporary variables
 */

string ScalarCompiler::generateDelayLine(DelayType dt, const string& ctype, const string& vname,
                                         int mxd, int count, bool mono, const string& exp,
                                         const string& ccs)
{
#if OLDDELAY
    if (mxd == 0) {
        cerr << "MXD==0 :  " << vname << " := " << exp << endl;
        // no need for a real vector
        if (ccs == "") {
            fClass->addExecCode(Statement(ccs, subst("$0 \t$1 = $2;", ctype, vname, exp)));
        } else {
            fClass->addZone2(subst("$0 \t$1 = 0;", ctype, vname));
            fClass->addExecCode(Statement(ccs, subst("\t$0 = $1;", vname, exp)));
        }

    } else if (mono || (mxd <= count * gGlobal->gMaxCopyDelay)) {
        // Generate code for short or dense delay lines
        DlCodeGen g(ctype, vname, gGlobal->gVecSize, mxd, mono);
        fClass->addDeclCode(g.globalDeclare());
        fClass->addClearCode(g.globalInit());
        fClass->addZone2(g.localDeclare());
        fClass->addZone3(g.pointerSetup());
        fClass->addZone3(g.copyGlobalToLocal());
        if (mono) {
            fClass->addExecCode(Statement(ccs, subst("$0 = $1;", vname, exp)));
        } else {
            fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
        }
        fClass->addPostCode(Statement(ccs, g.advance()));
        fClass->addZone3Post(g.copyLocalToGlobal());

    } else {
        // generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
        int N = pow2limit(mxd + 1);

        // we need an iota index
        fMaxIota = 0;

        // declare and init
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(N)));
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(N)));

        // execute
        std::string idx = subst("IOTA&$0", T(N - 1));
        fClass->addExecCode(
            Statement(ccs, subst("$0[$1] = $2;", vname, generateIotaCache(idx), exp)));
    }
#else
    switch (dt) {
        case DelayType::kNotADelay:
            faustexception("Try to compile has a delay something that is not a delay");
            return "";

        case DelayType::kZeroDelay:
            // cerr << "MXD==0 :  " << vname << " := " << exp << endl;
            // no need for a real vector
            if (ccs == "") {
                fClass->addExecCode(
                    Statement(ccs, subst("$0 \t$1 = $2; // Zero delay", ctype, vname, exp)));
            } else {
                fClass->addZone2(subst("$0 \t$1 = 0;", ctype, vname));
                fClass->addExecCode(Statement(ccs, subst("\t$0 = $1;", vname, exp)));
            }
            return vname;

        case DelayType::kMonoDelay:
            fClass->addDeclCode(subst("$0 \t$1State; // Mono Delay", ctype, vname));
            fClass->addClearCode(subst("$0State = 0;", vname));
            fClass->addZone2(subst("$0 \t$1;", ctype, vname));
            fClass->addZone3(subst("$0 = $0State;", vname));
            fClass->addExecCode(Statement(ccs, subst("$0 = $1;", vname, exp)));
            fClass->addZone3Post(subst("$0State = $0;", vname));
            return vname;

        case DelayType::kSingleDelay:
            fClass->addDeclCode(subst("$0 \t$1State; // Single Delay", ctype, vname));
            fClass->addClearCode(subst("$0State = 0;", vname));
            fClass->addZone2(subst("$0 \t$1[$2];", ctype, vname, T(mxd + 1)));
            fClass->addZone3(subst("$0[1] = $0State;", vname));
            fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
            fClass->addPostCode(Statement("", subst("$0[1] = $0[0];", vname)));
            fClass->addZone3Post(subst("$0State = $0[1];", vname));
            return subst("$0[0]", vname);

        case DelayType::kCopyDelay:
            fClass->addDeclCode(subst("$0 \t$1State[$2]; // Copy Delay", ctype, vname, T(mxd)));
            fClass->addClearCode(
                subst("for (int j = 0; j < $0; j++) { $1State[j] = 0; }", T(mxd), vname));
            fClass->addZone2(subst("$0 \t$1[$2];", ctype, vname, T(mxd + 1)));
            for (int j = 0; j < mxd; j++) {
                fClass->addZone3(subst("$0[$1] = $0State[$2];", vname, T(j + 1), T(j)));
            }
            fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
            for (int j = 0; j < mxd; j++) {
                // warning ; line stacked in reverse order !!!
                fClass->addPostCode(
                    Statement("", subst("$0[$1] = $0[$2];", vname, T(j + 1), T(j))));
            }
            for (int j = 0; j < mxd; j++) {
                fClass->addZone3Post(subst("$0State[$1] = $0[$2];", vname, T(j), T(j + 1)));
            }
            return subst("$0[0]", vname);

        case DelayType::kDenseDelay:

            fClass->addDeclCode(subst("$0 \t$1State[$2]; // Dense Delay", ctype, vname, T(mxd)));
            fClass->addClearCode(
                subst("for (int j = 0; j < $0; j++) { $1State[j] = 0; }", T(mxd), vname));
            fClass->addZone2(
                subst("$0 \t$1Cache[$2+$3];", ctype, vname, T(gGlobal->gVecSize), T(mxd)));
            fClass->addZone3(
                subst("$0* \t$1 = $1Cache + $2 - 1;", ctype, vname, T(gGlobal->gVecSize)));
            fClass->addZone3(
                subst("for (int j = 0; j < $0; j++) { $1[j+1] = $1State[j]; }", T(mxd), vname));
            fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
            fClass->addPostCode(Statement("", subst("--$0;", vname)));
            fClass->addZone3Post(
                subst("for (int j = 0; j < $0; j++) { $1State[j] = $1[j+1]; }", T(mxd), vname));
            return subst("$0[0]", vname);

        case DelayType::kMaskRingDelay:
        case DelayType::kSelectRingDelay:

            // generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
            int N = pow2limit(mxd + 1);

            // we need an iota index
            fMaxIota++;
            // std::cerr << "MaxIota increased" << std::endl;

            // declare and init
            fClass->addDeclCode(subst("$0 \t$1[$2]; // Ring Delay", ctype, vname, T(N)));
            fClass->addClearCode(subst("for (int i = 0; i < $1; i++) { $0[i] = 0; }", vname, T(N)));

            // execute
            std::string idx      = subst("IOTA&$0", T(N - 1));
            std::string cacheidx = generateIotaCache(idx);
            fClass->addExecCode(Statement(ccs, subst("$0[$1] = $2;", vname, cacheidx, exp)));
            return subst("$0[$1]", vname, cacheidx);
    }
#endif
}

/**
 * Generate code for a unique IOTA variable increased at each sample
 * and used to index delay buffers.
 */
void ScalarCompiler::ensureIotaCode()
{
    // std::cerr << "ensureIotaCode called " << fMaxIota << std::endl;
    if (fMaxIota >= 0) {
        fClass->addDeclCode("int \tIOTA;");
        fClass->addClearCode(subst("IOTA = $0;", T(fMaxIota)));
        fClass->addPostCode(Statement("", "IOTA = IOTA+1;"));
    }
}

/*****************************************************************************
 WAVEFORM
 *****************************************************************************/

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
        subst("$0 \t$1::$2[$3] = ", ctype, fClass->getFullClassName(), vname, T(size)) +
        content.str() + ";");
}

string ScalarCompiler::generateWaveform(Tree sig)
{
    string vname;
    int    size;

    declareWaveform(sig, vname, size);
    fClass->addPostCode(
        Statement(getConditionCode(sig), subst("idx$0 = (idx$0 + 1) % $1;", vname, T(size))));
    return generateCacheCode(sig, subst("$0[idx$0]", vname));
}
