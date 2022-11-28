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

#include <string>

#include "Text.hh"
#include "ensure.hh"
#include "fir_to_fir.hh"
#include "floats.hh"
#include "instructions.hh"
#include "instructions_compiler.hh"
#include "instructions_compiler1.hh"
#include "instructions_compiler_jax.hh"
#include "prim2.hh"
#include "privatise.hh"
#include "recursivness.hh"
#include "sigToGraph.hh"
#include "signal2vhdlVisitor.hh"
#include "signal2Elementary.hh"
#include "sigprint.hh"
#include "normalform.hh"
#include "timing.hh"
#include "sigtyperules.hh"
#include "signalVisitor.hh"
#include "sigPromotion.hh"

using namespace std;

ostream* Printable::fOut = &cout;

static inline BasicTyped* genBasicFIRTyped(int sig_type)
{
    return InstBuilder::genBasicTyped(convert2FIRType(sig_type));
}

ValueInst* InstructionsCompiler::genCastedOutput(int type, ValueInst* value)
{
    bool need_cast = (type == kInt) || !gGlobal->gFAUSTFLOAT2Internal;
    return (need_cast) ? InstBuilder::genCastFloatMacroInst(value) : value;
}

ValueInst* InstructionsCompiler::genCastedInput(ValueInst* value)
{
    return (gGlobal->gFAUSTFLOAT2Internal)
        ? value
        : InstBuilder::genCastInst(value, InstBuilder::genItFloatTyped());
}

InstructionsCompiler::InstructionsCompiler(CodeContainer* container)
    : fContainer(container),
      fSharingKey(nullptr),
      fOccMarkup(nullptr),
      fUIRoot(uiFolder(cons(tree(0), tree("")))),
      fDescription(nullptr)
{}

// Taken from sharing.cpp

int InstructionsCompiler::getSharingCount(Tree sig)
{
    Tree c;
    if (getProperty(sig, fSharingKey, c)) {
        return c->node().getInt();
    } else {
        return 0;
    }
}

void InstructionsCompiler::setSharingCount(Tree sig, int count)
{
    setProperty(sig, fSharingKey, tree(count));
}

void InstructionsCompiler::sharingAnalysis(Tree t)
{
    fSharingKey = shprkey(t);
    if (isList(t)) {
        while (isList(t)) {
            sharingAnnotation(kSamp, hd(t));
            t = tl(t);
        }
    } else {
        sharingAnnotation(kSamp, t);
    }
}

void InstructionsCompiler::sharingAnnotation(int vctxt, Tree sig)
{
    // cerr << "START sharing annotation of " << *sig << endl;
    int count = getSharingCount(sig);

    if (count > 0) {
        // it is not our first visit
        setSharingCount(sig, count + 1);

    } else {
        // it is our first visit,
        int v = getCertifiedSigType(sig)->variability();
       
        // check "time sharing" cases
        if (v < vctxt) {
            setSharingCount(sig, 2);  // time sharing occurence : slower expression in faster context
        } else {
            setSharingCount(sig, 1);  // regular occurence
        }

        // Annotate the sub signals
        vector<Tree> subsig;
        int          n = getSubSignals(sig, subsig);
        if (n > 0 && !isSigGen(sig)) {
            for (int i = 0; i < n; i++) sharingAnnotation(v, subsig[i]);
        }
    }
    // cerr << "END sharing annotation of " << *sig << endl;
}

//------------------------------------------------------------------------------
// Condition annotation due to enabled expressions
//------------------------------------------------------------------------------
#if 0
void InstructionsCompiler::conditionStatistics(Tree l)
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

void InstructionsCompiler::conditionStatistics(Tree l)
{
    map<Tree, int> fConditionStatistics;  // used with the new X,Y:enable --> sigEnable(X*Y,Y != 0) primitive
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

void InstructionsCompiler::conditionAnnotation(Tree l)
{
    while (isList(l)) {
        conditionAnnotation(hd(l), gGlobal->nil);
        l = tl(l);
    }
}

#if _DNF_

#define _OR_ dnfOr
#define _AND_ dnfAnd
#define _CND_ dnfCond

#else

#define _OR_ cnfOr
#define _AND_ cnfAnd
#define _CND_ cnfCond

#endif

void InstructionsCompiler::conditionAnnotation(Tree t, Tree nc)
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
        // specific annotation case for sigControl
        conditionAnnotation(y, nc);
        conditionAnnotation(x, _AND_(nc, _CND_(y)));
    } else {
        // general annotation case
        // Annotate the sub signals with nc
        vector<Tree> subsig;
        int          n = getSubSignals(t, subsig);
        if (n > 0 && !isSigGen(t)) {
            for (int i = 0; i < n; i++) conditionAnnotation(subsig[i], nc);
        }
    }
}

/*****************************************************************************
 prepare
 *****************************************************************************/

Tree InstructionsCompiler::prepare(Tree LS)
{
    startTiming("prepare");
    Tree L1 = simplifyToNormalForm(LS);
    
    /*
        Possibly cast bool binary operations (comparison operations) to int.
        Done after simplifyToNormalForm with does SignalTreeChecker,
        that would fail after sigBool2IntPromote which adds additional
        sigIntCast on bool producing BinOp operations.
    */
    if (gGlobal->gBool2Int) L1 = sigBool2IntPromote(L1);
    
    // dump normal form
    if (gGlobal->gDumpNorm == 0) {
        cout << ppsig(L1) << endl;
        throw faustexception("Dump normal form finished...\n");
    } else if (gGlobal->gDumpNorm == 1) {
        ppsigShared(L1, cout);
        throw faustexception("Dump shared normal form finished...\n");
    }
    
    startTiming("privatise");
    Tree L2 = privatise(L1);  // Un-share tables with multiple writers
    endTiming("privatise");
    
    startTiming("conditionAnnotation");
    conditionAnnotation(L2);
    endTiming("conditionAnnotation");
    
    startTiming("recursivnessAnnotation");
    recursivnessAnnotation(L2);  // Annotate L2 with recursivness information
    endTiming("recursivnessAnnotation");
    
    startTiming("L2 typeAnnotation");
    typeAnnotation(L2, true);     // Annotate L2 with type information and check causality
    endTiming("L2 typeAnnotation");
    
    startTiming("sharingAnalysis");
    sharingAnalysis(L2);         // Annotate L2 with sharing count
    endTiming("sharingAnalysis");
    
    startTiming("occurrences analysis");
    delete fOccMarkup;
    fOccMarkup = new old_OccMarkup(fConditionProperty);
    fOccMarkup->mark(L2);        // Annotate L2 with occurrences analysis
    endTiming("occurrences analysis");
    
    endTiming("prepare");
    
    if (gGlobal->gDrawSignals) {
        ofstream dotfile(subst("$0-sig.dot", gGlobal->makeDrawPath()).c_str());
        sigToGraph(L2, dotfile);
    }
    
    // Generate VHDL if -vhdl option is set
    if (gGlobal->gVHDLSwitch) {
        sigVHDLFile(fOccMarkup, L2, gGlobal->gVHDLTrace);
    }
    
    return L2;
}

Tree InstructionsCompiler::prepare2(Tree L0)
{
    startTiming("prepare2");

    recursivnessAnnotation(L0);  // Annotate L0 with recursivness information
    typeAnnotation(L0, true);    // Annotate L0 with type information
    sharingAnalysis(L0);         // Annotate L0 with sharing count
   
    delete fOccMarkup;
    fOccMarkup = new old_OccMarkup();
    fOccMarkup->mark(L0);        // Annotate L0 with occurrences analysis

    endTiming("prepare2");
    return L0;
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
bool InstructionsCompiler::getCompiledExpression(Tree sig, ValueType& cexp)
{
    return fCompileProperty.get(sig, cexp);
}

/**
 * Set the string of a compiled expression is already compiled
 * @param sig the signal expression to compile.
 * @param cexp the string representing the compiled expression.
 * @return the cexp (for commodity)
 */
ValueType InstructionsCompiler::setCompiledExpression(Tree sig, const ValueType& cexp)
{
    ValueType old;
    if (fCompileProperty.get(sig, old) && (old != cexp)) {
        // stringstream error;
        // error << "ERROR already a compiled expression attached : " << old << " replaced by " << cexp << endl;
        // throw faustexception(error.str());
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
 * @param vname the string representing the vector name.
 * @return true is already compiled
 */
void InstructionsCompiler::setVectorNameProperty(Tree sig, const string& vname)
{
    faustassert(vname.size() > 0);
    fVectorProperty.set(sig, vname);
}

/**
 * Get the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vname the string where to store the vector name.
 * @return true if the signal has this property, false otherwise
 */

bool InstructionsCompiler::getVectorNameProperty(Tree sig, string& vname)
{
    return fVectorProperty.get(sig, vname);
}

void InstructionsCompiler::setTableNameProperty(Tree sig, const string& name)
{
    faustassert(name.size() > 0);
    fTableProperty.set(sig, name);
}

bool InstructionsCompiler::getTableNameProperty(Tree sig, string& name)
{
    return fTableProperty.get(sig, name);
}

ValueInst* InstructionsCompiler::CS(Tree sig)
{
    ValueInst* code;

    if (!getCompiledExpression(sig, code)) {
        code = generateCode(sig);
        setCompiledExpression(sig, code);
    }

    return code;
}

CodeContainer* InstructionsCompiler::signal2Container(const string& name, Tree sig)
{
    ::Type t = getCertifiedSigType(sig);

    CodeContainer* container = fContainer->createScalarContainer(name, t->nature());
    
    if (gGlobal->gOutputLang == "rust" || gGlobal->gOutputLang == "julia") {
        InstructionsCompiler1 C(container);
        C.compileSingleSignal(sig);
    } else if (gGlobal->gOutputLang == "jax") {
        InstructionsCompilerJAX C(container);
        C.compileSingleSignal(sig);
    } else {
        InstructionsCompiler C(container);
        C.compileSingleSignal(sig);
    }
    return container;
}

/*****************************************************************************
 compileMultiSignal
 *****************************************************************************/

ValueInst* InstructionsCompiler::dnf2code(Tree cc)
{
    if (cc == gGlobal->nil) return InstBuilder::genNullValueInst();
    Tree c1 = hd(cc);
    cc      = tl(cc);
    if (cc == gGlobal->nil) {
        return and2code(c1);
    } else {
        return InstBuilder::genOr(and2code(c1), dnf2code(cc));
    }
}

ValueInst* InstructionsCompiler::and2code(Tree cs)
{
    if (cs == gGlobal->nil) return InstBuilder::genNullValueInst();
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        return InstBuilder::genAnd(CS(c1), and2code(cs));
    }
}

ValueInst* InstructionsCompiler::cnf2code(Tree cs)
{
    if (cs == gGlobal->nil) return InstBuilder::genNullValueInst();
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return or2code(c1);
    } else {
        return InstBuilder::genAnd(or2code(c1), cnf2code(cs));
    }
}

ValueInst* InstructionsCompiler::or2code(Tree cs)
{
    if (cs == gGlobal->nil) return InstBuilder::genNullValueInst();
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        return InstBuilder::genOr(CS(c1), or2code(cs));
    }
}

#if _DNF_
#define CND2CODE dnf2code
#else
#define CND2CODE cnf2code
#endif

// Temporary implementation for test purposes
ValueInst* InstructionsCompiler::getConditionCode(Tree sig)
{
    Tree cc = fConditionProperty[sig];
    if ((cc != 0) && (cc != gGlobal->nil)) {
        return CND2CODE(cc);
    } else {
        return InstBuilder::genNullValueInst();
    }
}

void InstructionsCompiler::compileMultiSignal(Tree L)
{
    // Compile inputs
    struct InputCompiler : public SignalVisitor {
        
        InstructionsCompiler* fComp;
        
        InputCompiler(Tree L, InstructionsCompiler* comp)
        {
            fComp = comp;
            while (!isNil(L)) {
                self(hd(L));
                L = tl(L);
            }
        }
        
        void visit(Tree sig)
        {
            int input;
            if (isSigInput(sig, &input)) {
                fComp->CS(sig);
            } else {
                SignalVisitor::visit(sig);
            }
        }
    };
    
    startTiming("compileMultiSignal");
    
    // Has to be done *after* gMachinePtrSize is set by the actual backend
    gGlobal->initTypeSizeMap();

    L = prepare(L);  // Optimize, share and annotate expression
    
    // Compile inputs when gInPlace (force caching for in-place transformations)
    if (gGlobal->gInPlace) InputCompiler(L, this);

#ifdef LLVM_DEBUG
    // Add function declaration
    pushGlobalDeclare(InstBuilder::genFunction1("printInt32", Typed::kVoid, "val", Typed::kInt32));
    pushGlobalDeclare(InstBuilder::genFunction1("printFloat", Typed::kVoid, "val", Typed::kFloat));
    pushGlobalDeclare(InstBuilder::genFunction1("printDouble", Typed::kVoid, "val", Typed::kDouble));
    pushGlobalDeclare(InstBuilder::genFunction1("printPtr", Typed::kVoid, "val", Typed::kVoid_ptr));
#endif

    Typed* type = InstBuilder::genFloatMacroTyped();
    Typed* ptr_type = InstBuilder::genArrayTyped(type, 0);

    if (!gGlobal->gOpenCLSwitch && !gGlobal->gCUDASwitch) {  // HACK

        // Input declarations
        if (gGlobal->gOutputLang == "rust") {
            // special handling for Rust backend
            pushComputeBlockMethod(InstBuilder::genDeclareBufferIterators("*input", "inputs", fContainer->inputs(), type, false));
        } else if (gGlobal->gOutputLang == "julia") {
            // special handling Julia backend
            pushComputeBlockMethod(InstBuilder::genDeclareBufferIterators("input", "inputs", fContainer->inputs(), ptr_type, false));
        } else if (gGlobal->gOutputLang != "jax") {
            // "input" and "inputs" used as a name convention
            if (gGlobal->gOneSampleControl) {
                for (int index = 0; index < fContainer->inputs(); index++) {
                    string name = subst("input$0", T(index));
                    pushDeclare(InstBuilder::genDecStructVar(name, type));
                }
            } else if (gGlobal->gOneSample >= 0) {
            // Nothing...
            } else {
                for (int index = 0; index < fContainer->inputs(); index++) {
                    string name = subst("input$0", T(index));
                    pushComputeBlockMethod(InstBuilder::genDecStackVar(name, ptr_type,
                        InstBuilder::genLoadArrayFunArgsVar("inputs", InstBuilder::genInt32NumInst(index))));
                }
            }
        }

        // Output declarations
        if (gGlobal->gOutputLang == "rust") {
            // special handling for Rust backend
            pushComputeBlockMethod(InstBuilder::genDeclareBufferIterators("*output", "outputs", fContainer->outputs(), type, true));
        } else if (gGlobal->gOutputLang == "julia") {
            // special handling for Julia backend
            pushComputeBlockMethod(InstBuilder::genDeclareBufferIterators("output", "outputs", fContainer->outputs(), ptr_type, true));
        } else if (gGlobal->gOutputLang != "jax") {
            // "output" and "outputs" used as a name convention
            if (gGlobal->gOneSampleControl) {
                for (int index = 0; index < fContainer->outputs(); index++) {
                    string name = subst("output$0", T(index));
                    pushDeclare(InstBuilder::genDecStructVar(name, type));
                }
            } else if (gGlobal->gOneSample >= 0) {
            // Nothing...
            } else {
                for (int index = 0; index < fContainer->outputs(); index++) {
                    string name = subst("output$0", T(index));
                    pushComputeBlockMethod(InstBuilder::genDecStackVar(name, ptr_type,
                        InstBuilder::genLoadArrayFunArgsVar("outputs", InstBuilder::genInt32NumInst(index))));
                }
            }
        }
    }

    // These two vars are only used for JAX
    std::string return_string = "state, jnp.stack([";
    std::string sep = "";

    for (int index = 0; isList(L); L = tl(L), index++) {
        Tree sig = hd(L);

        // Possibly cast to external float
        ValueInst* res = genCastedOutput(getCertifiedSigType(sig)->nature(), CS(sig));

        // HACK for Rust backend
        string name;
        if (gGlobal->gOutputLang == "rust") {
            name = subst("*output$0", T(index));
            pushComputeDSPMethod(InstBuilder::genStoreStackVar(name, res));
        } else if (gGlobal->gOutputLang == "jax") {
            res = CS(sig);
            string result_var = "_result" + to_string(index);
            return_string = return_string + sep + result_var;
            sep = ",";
            pushComputeDSPMethod(InstBuilder::genStoreStackVar(result_var, res));
        } else if (gGlobal->gOneSampleControl) {
            name = subst("output$0", T(index));
            if (gGlobal->gComputeMix) {
                ValueInst* res1 = InstBuilder::genAdd(res, InstBuilder::genLoadStackVar(name));
                pushComputeDSPMethod(InstBuilder::genStoreStackVar(name, res1));
            } else {
                pushComputeDSPMethod(InstBuilder::genStoreStackVar(name, res));
            }
        } else if (gGlobal->gOneSample >= 0) {
            name = "outputs";
            if (gGlobal->gComputeMix) {
                ValueInst* res1 = InstBuilder::genAdd(res, InstBuilder::genLoadArrayStackVar(name, InstBuilder::genInt32NumInst(index)));
                pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(name, InstBuilder::genInt32NumInst(index), res1));
            } else {
                pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(name, InstBuilder::genInt32NumInst(index), res));
            }
        } else {
            name = subst("output$0", T(index));
            if (gGlobal->gComputeMix) {
                ValueInst* res1 = InstBuilder::genAdd(res, InstBuilder::genLoadArrayStackVar(name, getCurrentLoopIndex()));
                pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(name, getCurrentLoopIndex(), res1));
            } else {
                pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(name, getCurrentLoopIndex(), res));
            }
        }
    }

    if (gGlobal->gOutputLang == "jax") {
        return_string = return_string + "])";
        pushPostComputeDSPMethod(InstBuilder::genRetInst(InstBuilder::genLoadStackVar(return_string)));
    }

    Tree ui = InstructionsCompiler::prepareUserInterfaceTree(fUIRoot);
    generateUserInterfaceTree(ui, true);
    generateMacroInterfaceTree("", ui);
    if (fDescription) {
        fDescription->ui(ui);
    }

    // Apply FIR to FIR transformations
    fContainer->processFIR();
    
    // Check FIR code
    if (global::isDebug("FIR_CHECKER")) {
        startTiming("FIR checker");
        FIRChecker fir_checker;
        fContainer->flattenFIR()->accept(&fir_checker);
        endTiming("FIR checker");
    }

    endTiming("compileMultiSignal");
}

/*****************************************************************************
 compileSingleSignal
 *****************************************************************************/

void InstructionsCompiler::compileSingleSignal(Tree sig)
{
    sig         = prepare2(sig);  // Optimize and annotate expression
    string name = fContainer->getTableName();

    pushComputeDSPMethod(InstBuilder::genStoreArrayFunArgsVar(name, getCurrentLoopIndex(), CS(sig)));

    Tree ui = InstructionsCompiler::prepareUserInterfaceTree(fUIRoot);
    generateUserInterfaceTree(ui);
    generateMacroInterfaceTree("", ui);
    if (fDescription) {
        fDescription->ui(ui);
    }
}

/*****************************************************************************
 generateCode : dispatch according to signal
 *****************************************************************************/
/**
 * Main code generator dispatch.
 * @param sig the signal expression to compile.
 * @return the FIR code translation of sig
 */

ValueInst* InstructionsCompiler::generateCode(Tree sig)
{
#if 0
    fprintf(stderr, "CALL generateCode(");
    printSignal(sig, stderr);
    fprintf(stderr, ")\n");
#endif

    ValueInst* code;
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    int    i;
    double r;
    Tree   c, sel, x, y, z, label, id, ff, largs, type, name, file, sf;

    // printf("compilation of %p : ", sig); print(sig); printf("\n");

    if (getUserData(sig)) {
        return generateXtended(sig);
    } else if (isSigInt(sig, &i)) {
        return generateIntNumber(sig, i);
    } else if (isSigReal(sig, &r)) {
        return generateRealNumber(sig, r);
    } else if (isSigWaveform(sig)) {
        return generateWaveform(sig);
    } else if (isSigInput(sig, &i)) {
        return generateInput(sig, i);
    }

    else if (isSigDelay(sig, x, y)) {
        return generateDelay(sig, x, y);
    } else if (isSigPrefix(sig, x, y)) {
        return generatePrefix(sig, x, y);
    } else if (isSigBinOp(sig, &i, x, y)) {
        return generateBinOp(sig, i, x, y);
    } else if (isSigFFun(sig, ff, largs)) {
        return generateFFun(sig, ff, largs);
    } else if (isSigFConst(sig, type, name, file)) {
        return generateFConst(sig, type, tree2str(file), tree2str(name));
    } else if (isSigFVar(sig, type, name, file)) {
        return generateFVar(sig, type, tree2str(file), tree2str(name));
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
    }

    else if (isSigSoundfile(sig, label)) {
        return generateSoundfile(sig, label);
    } else if (isSigSoundfileLength(sig, sf, x)) {
        return generateCacheCode(sig, generateSoundfileLength(sig, CS(sf), CS(x)));
    } else if (isSigSoundfileRate(sig, sf, x)) {
        return generateCacheCode(sig, generateSoundfileRate(sig, CS(sf), CS(x)));
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        return generateCacheCode(sig, generateSoundfileBuffer(sig, CS(sf), CS(x), CS(y), CS(z)));
    }

    else if (isSigAttach(sig, x, y)) {
        CS(y);
        return generateCacheCode(sig, CS(x));
       
    } else if (isSigControl(sig, x, y)) {
        if (gGlobal->gVectorSwitch) {
            throw faustexception("ERROR : 'control/enable' can only be used in scalar mode\n");
        }
        return generateControl(sig, x, y);
        
    } else if (isSigAssertBounds(sig, x, y, z)) {
        /* no debug option for the moment */
        return generateCode(z);
    } else if (isSigLowest(sig, x) || isSigHighest(sig, x)) {
        throw faustexception("ERROR : annotations should have been deleted in Simplification process\n");
        
    /* we should not have any control at this stage*/
    } else {
        cerr << "ERROR : when compiling, unrecognized signal : " << ppsig(sig) << endl;
        faustassert(false);
    }
    return InstBuilder::genNullValueInst();
}

/*****************************************************************************
 NUMBERS
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateIntNumber(Tree sig, int num)
{
    old_Occurences* o = fOccMarkup->retrieve(sig);

    // Check for number occuring in delays
    if (o->getMaxDelay() > 0) {
        Typed::VarType ctype;
        string         vname;
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, InstBuilder::genInt32NumInst(num), ctype, vname, o->getMaxDelay());
    }

    // No cache for numbers
    return InstBuilder::genInt32NumInst(num);
}

ValueInst* InstructionsCompiler::generateRealNumber(Tree sig, double num)
{
    Typed::VarType ctype = itfloat();
    old_Occurences*    o = fOccMarkup->retrieve(sig);

    // Check for number occuring in delays
    if (o->getMaxDelay() > 0) {
        string vname;
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, InstBuilder::genRealNumInst(ctype, num), ctype, vname, o->getMaxDelay());
    }

    // No cache for numbers
    return InstBuilder::genRealNumInst(ctype, num);
}

/*****************************************************************************
 FOREIGN CONSTANTS
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateFConst(Tree sig, Tree type, const string& file, const string& name_aux)
{
    fContainer->addIncludeFile(file);

    // Special case for 02/25/19 renaming
    string name = (name_aux == "fSamplingFreq") ? "fSampleRate" : name_aux;

    // Check access (handling "fSampleRate" as a special case)
    if (name != "fSampleRate" && !gGlobal->gAllowForeignConstant) {
        stringstream error;
        error << "ERROR : accessing foreign constant '" << name << "'"
        << " is not allowed in this compilation mode!" << endl;
        throw faustexception(error.str());
    }

    // Keep SR generation state
    if (name == "fSampleRate") {
        fContainer->setGeneratedSR();
    }

    // Check for number occuring in delays
    Typed::VarType ctype;
    string         vname;
    old_Occurences*    o = fOccMarkup->retrieve(sig);

    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(
            sig, (name == "fSampleRate") ? InstBuilder::genLoadStructVar(name) : InstBuilder::genLoadGlobalVar(name),
            ctype, vname, o->getMaxDelay());
    }

    // Special case for 'fSampleRate' parameter of the class
    int sig_type = getCertifiedSigType(sig)->nature();
    if (name == "fSampleRate") {
        pushDeclare(InstBuilder::genDecStructVar(name, genBasicFIRTyped(sig_type)));
        return InstBuilder::genLoadStructVar(name);
    } else {
        pushExtGlobalDeclare(InstBuilder::genDecGlobalVar(name, genBasicFIRTyped(sig_type)));
        return InstBuilder::genLoadGlobalVar(name);
    }
}

/*****************************************************************************
 FOREIGN VARIABLES
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateFVar(Tree sig, Tree type, const string& file, const string& name)
{
    // Check access (handling 'fFullCount' as a special case)
    if ((name != fFullCount && !gGlobal->gAllowForeignVar)
        || (name == fFullCount && (gGlobal->gOneSample >= 0 || gGlobal->gOneSampleControl))) {
        stringstream error;
        error << "ERROR : accessing foreign variable '" << name << "'"
        << " is not allowed in this compilation mode!" << endl;
        throw faustexception(error.str());
    }

    fContainer->addIncludeFile(file);

    // Special case for 'count' parameter of the 'compute' method
    if (name == fFullCount) {
        return generateCacheCode(sig, InstBuilder::genLoadFunArgsVar(name));
    } else {
        int sig_type = getCertifiedSigType(sig)->nature();
        pushExtGlobalDeclare(InstBuilder::genDecGlobalVar(name, genBasicFIRTyped(sig_type)));
        return generateCacheCode(sig, InstBuilder::genLoadGlobalVar(name));
    }
}

/*****************************************************************************
 INPUTS - OUTPUTS
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateInput(Tree sig, int idx)
{
    // Cast to internal float
    ValueInst* res;
    // HACK for Rust backend
    if (gGlobal->gOutputLang == "rust") {
        res = InstBuilder::genLoadStackVar(subst("*input$0", T(idx)));
    } else if (gGlobal->gOutputLang == "jax") {
        res = InstBuilder::genLoadArrayStackVar("inputs", InstBuilder::genInt32NumInst(idx));
    } else if (gGlobal->gOneSampleControl) {
        res = InstBuilder::genLoadStructVar(subst("input$0", T(idx)));
    } else if (gGlobal->gOneSample >= 0) {
        res = InstBuilder::genLoadArrayStackVar("inputs", InstBuilder::genInt32NumInst(idx));
    } else {
        res = InstBuilder::genLoadArrayStackVar(subst("input$0", T(idx)), getCurrentLoopIndex());
    }
    
    // Cast to internal float
    res = genCastedInput(res);

    if (gGlobal->gInPlace) {
        // inputs must be cached for in-place transformations
        return forceCacheCode(sig, res);
    } else {
        return generateCacheCode(sig, res);
    }
}

/*****************************************************************************
 BINARY OPERATION
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateBinOp(Tree sig, int opcode, Tree a1, Tree a2)
{
    return generateCacheCode(sig, InstBuilder::genBinopInst(opcode, CS(a1), CS(a2)));
}

/*****************************************************************************
 Primitive Operations
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateFFun(Tree sig, Tree ff, Tree largs)
{
    fContainer->addIncludeFile(ffincfile(ff));
    fContainer->addLibrary(fflibfile(ff));
    string funname = ffname(ff);

    if (gGlobal->gAllowForeignFunction || gGlobal->hasForeignFunction(funname, ffincfile(ff))) {

        Values args_value;
        Names args_types;

        int len = ffarity(ff) - 1;
        for (int i = 0; i < ffarity(ff); i++) {
            // Reversed...
            BasicTyped* argtype = genBasicFIRTyped(ffargtype(ff, len - i));
            args_types.push_back(InstBuilder::genNamedTyped("dummy" + to_string(i), argtype));
            args_value.push_back(CS(nth(largs, i)));
        }

        // Add function declaration
        FunTyped* fun_type = InstBuilder::genFunTyped(args_types, genBasicFIRTyped(ffrestype(ff)));
        pushExtGlobalDeclare(InstBuilder::genDeclareFunInst(funname, fun_type));
        return generateCacheCode(sig, InstBuilder::genFunCallInst(funname, args_value));
    } else {
        stringstream error;
        error << "ERROR : calling foreign function '" << funname << "'"
              << " is not allowed in this compilation mode!" << endl;
        throw faustexception(error.str());
    }
}

/*****************************************************************************
 CACHE CODE
 *****************************************************************************/

void InstructionsCompiler::getTypedNames(::Type t, const string& prefix, Typed::VarType& ctype, string& vname)
{
    if (t->nature() == kInt) {
        ctype = Typed::kInt32;
        vname = subst("i$0", gGlobal->getFreshID(prefix));
    } else {
        ctype = itfloat();
        vname = subst("f$0", gGlobal->getFreshID(prefix));
    }
}

ValueInst* InstructionsCompiler::generateCacheCode(Tree sig, ValueInst* exp)
{
    ValueInst* code;

    // Check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    string         vname;
    Typed::VarType ctype;
    int            sharing = getSharingCount(sig);
    old_Occurences* o      = fOccMarkup->retrieve(sig);
    faustassert(o);

    // Check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        if (sharing > 1) {
            return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname, o->getMaxDelay());
        } else {
            return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
        }

    } else if (sharing > 1 || (o->hasMultiOccurences())) {
        return generateVariableStore(sig, exp);

    } else if (sharing == 1) {
        return exp;

    } else {
        cerr << "ERROR : in sharing count (" << sharing << ") for " << *sig << endl;
        faustassert(false);
        return {};
    }
}

// Like generateCacheCode but we force caching like if sharing was always > 1
ValueInst* InstructionsCompiler::forceCacheCode(Tree sig, ValueInst* exp)
{
    ValueInst* code;

    // check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }
   
    string         vname;
    Typed::VarType ctype;
    old_Occurences*    o = fOccMarkup->retrieve(sig);
    faustassert(o);

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname, o->getMaxDelay());
    } else {
        return generateVariableStore(sig, exp);
    }
}

ValueInst* InstructionsCompiler::generateVariableStore(Tree sig, ValueInst* exp)
{
    string         vname, vname_perm;
    Typed::VarType ctype;
    ::Type         t = getCertifiedSigType(sig);
    old_Occurences* o = fOccMarkup->retrieve(sig);
    faustassert(o);

    switch (t->variability()) {
        case kKonst:
            getTypedNames(t, "Const", ctype, vname);
            // The variable is used in compute (kBlock or kSamp), so define is as a field in the DSP struct
            if (o->getOccurence(kBlock) || o->getOccurence(kSamp)) {
                pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genBasicTyped(ctype)));
                pushInitMethod(InstBuilder::genStoreStructVar(vname, exp));
                return InstBuilder::genLoadStructVar(vname);
            } else {
                // Otherwise it can stay as a local variable
                pushInitMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), exp));
                return InstBuilder::genLoadStackVar(vname);
            }
  
        case kBlock:
            if (gGlobal->gOneSample >= 0 || gGlobal->gOneSampleControl) {
                
                if (gGlobal->gOneSample == 3) {
                    if (t->nature() == kInt) {
                        pushComputeBlockMethod(InstBuilder::genStoreArrayStructVar(
                            "iControl", InstBuilder::genInt32NumInst(fContainer->fInt32ControlNum), exp));
                        ValueInst* res = InstBuilder::genLoadArrayStructVar(
                            "iControl", InstBuilder::genInt32NumInst(fContainer->fInt32ControlNum));
                        fContainer->fInt32ControlNum++;
                        return res;
                    } else {
                        pushComputeBlockMethod(InstBuilder::genStoreArrayStructVar(
                            "fControl", InstBuilder::genInt32NumInst(fContainer->fRealControlNum), exp));
                        ValueInst* res = InstBuilder::genLoadArrayStructVar(
                            "fControl", InstBuilder::genInt32NumInst(fContainer->fRealControlNum));
                        fContainer->fRealControlNum++;
                        return res;
                    }
                } else {
                    if (t->nature() == kInt) {
                        pushComputeBlockMethod(InstBuilder::genStoreArrayFunArgsVar(
                            "iControl", InstBuilder::genInt32NumInst(fContainer->fInt32ControlNum), exp));
                        ValueInst* res = InstBuilder::genLoadArrayFunArgsVar(
                            "iControl", InstBuilder::genInt32NumInst(fContainer->fInt32ControlNum));
                        fContainer->fInt32ControlNum++;
                        return res;
                    } else {
                        pushComputeBlockMethod(InstBuilder::genStoreArrayFunArgsVar(
                            "fControl", InstBuilder::genInt32NumInst(fContainer->fRealControlNum), exp));
                        ValueInst* res = InstBuilder::genLoadArrayFunArgsVar(
                            "fControl", InstBuilder::genInt32NumInst(fContainer->fRealControlNum));
                        fContainer->fRealControlNum++;
                        return res;
                    }
                }
            } else {
                getTypedNames(t, "Slow", ctype, vname);
                pushComputeBlockMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), exp));
                return InstBuilder::genLoadStackVar(vname);
            }

        case kSamp:
            getTypedNames(t, "Temp", ctype, vname);

            // Only generated for the DSP loop
            if (gGlobal->gHasTeeLocal) {

                if (dynamic_cast<NullValueInst*>(getConditionCode(sig))) {
                    pushComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype)));
                } else {
                    getTypedNames(t, "TempPerm", ctype, vname_perm);
                    pushDeclare(InstBuilder::genDecStructVar(vname_perm, InstBuilder::genBasicTyped(ctype)));
                    pushClearMethod(InstBuilder::genStoreStructVar(vname_perm, InstBuilder::genTypedZero(ctype)));

                    pushComputeBlockMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), InstBuilder::genLoadStructVar(vname_perm)));
                    pushPostComputeBlockMethod(InstBuilder::genStoreStructVar(vname_perm, InstBuilder::genLoadStackVar(vname)));
                }

                return InstBuilder::genTeeVar(vname, exp);
            } else {

                if (dynamic_cast<NullValueInst*>(getConditionCode(sig))) {
                    pushComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), exp));
                    return InstBuilder::genLoadStackVar(vname);
                } else {
                    getTypedNames(t, "TempPerm", ctype, vname_perm);
                    pushDeclare(InstBuilder::genDecStructVar(vname_perm, InstBuilder::genBasicTyped(ctype)));
                    pushClearMethod(InstBuilder::genStoreStructVar(vname_perm, InstBuilder::genTypedZero(ctype)));

                    if (gGlobal->gOneSample >= 0 || gGlobal->gOneSampleControl) {
                        pushComputeDSPMethod(InstBuilder::genControlInst(getConditionCode(sig), InstBuilder::genStoreStructVar(vname_perm, exp)));
                        return InstBuilder::genLoadStructVar(vname_perm);
                    } else {
                        pushComputeBlockMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), InstBuilder::genLoadStructVar(vname_perm)));
                        pushComputeDSPMethod(InstBuilder::genControlInst(getConditionCode(sig), InstBuilder::genStoreStackVar(vname, exp)));
                        pushPostComputeBlockMethod(InstBuilder::genStoreStructVar(vname_perm, InstBuilder::genLoadStackVar(vname)));
                        return InstBuilder::genLoadStackVar(vname);
                    }
                }
            }

        default:
            return InstBuilder::genNullValueInst();
    }
}

/*****************************************************************************
 CASTING
 *****************************************************************************/

// Generate cast only when really necessary...
ValueInst* InstructionsCompiler::generateIntCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, InstBuilder::genCastInt32Inst(CS(x)));
}

// Generate cast only when really necessary...
ValueInst* InstructionsCompiler::generateFloatCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, InstBuilder::genCastRealInst(CS(x)));
}

/*****************************************************************************
 user interface elements
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateButtonAux(Tree sig, Tree path, const string& name)
{
    string varname = gGlobal->getFreshID(name);
    Typed* type    = InstBuilder::genFloatMacroTyped();

    pushDeclare(InstBuilder::genDecStructVar(varname, type));
    pushResetUIInstructions(
        InstBuilder::genStoreStructVar(varname, InstBuilder::genRealNumInst(Typed::kFloatMacro, 0)));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // Cast to internal float
    return generateCacheCode(sig, genCastedInput(InstBuilder::genLoadStructVar(varname)));
}

ValueInst* InstructionsCompiler::generateButton(Tree sig, Tree path)
{
    return generateButtonAux(sig, path, "fButton");
}

ValueInst* InstructionsCompiler::generateCheckbox(Tree sig, Tree path)
{
    return generateButtonAux(sig, path, "fCheckbox");
}

ValueInst* InstructionsCompiler::generateSliderAux(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step,
                                                   const string& name)
{
    string varname = gGlobal->getFreshID(name);
    Typed* type    = InstBuilder::genFloatMacroTyped();

    pushDeclare(InstBuilder::genDecStructVar(varname, type));
    pushResetUIInstructions(
        InstBuilder::genStoreStructVar(varname, InstBuilder::genRealNumInst(Typed::kFloatMacro, tree2float(cur))));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // Cast to internal float
    return generateCacheCode(sig, genCastedInput(InstBuilder::genLoadStructVar(varname)));
}

ValueInst* InstructionsCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(sig, path, cur, min, max, step, "fVslider");
}
ValueInst* InstructionsCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(sig, path, cur, min, max, step, "fHslider");
}

ValueInst* InstructionsCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(sig, path, cur, min, max, step, "fEntry");
}

ValueInst* InstructionsCompiler::generateBargraphAux(Tree sig, Tree path, Tree min, Tree max, ValueInst* exp,
                                                     const string& name)
{
    string varname = gGlobal->getFreshID(name);
    pushDeclare(InstBuilder::genDecStructVar(varname, InstBuilder::genFloatMacroTyped()));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    ::Type t = getCertifiedSigType(sig);

    // Cast to external float
    ValueInst* val = (gGlobal->gFAUSTFLOAT2Internal) ? exp : InstBuilder::genCastFloatMacroInst(exp);
    StoreVarInst* res = InstBuilder::genStoreStructVar(varname, val);

    switch (t->variability()) {
        case kKonst:
            pushResetUIInstructions(res);
            break;

        case kBlock:
            pushComputeBlockMethod(res);
            break;

        case kSamp:
            pushComputeDSPMethod(InstBuilder::genControlInst(getConditionCode(sig), res));
            break;
    }

    return generateCacheCode(sig, InstBuilder::genLoadStructVar(varname));
}

ValueInst* InstructionsCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, ValueInst* exp)
{
    return generateBargraphAux(sig, path, min, max, exp, "fVbargraph");
}

ValueInst* InstructionsCompiler::generateHBargraph(Tree sig, Tree path, Tree min, Tree max, ValueInst* exp)
{
    return generateBargraphAux(sig, path, min, max, exp, "fHbargraph");
}

ValueInst* InstructionsCompiler::generateSoundfile(Tree sig, Tree path)
{
    string varname = gGlobal->getFreshID("fSoundfile");
    string SFcache = varname + "ca";

    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    pushDeclare(InstBuilder::genDecStructVar(varname, InstBuilder::genBasicTyped(Typed::kSound_ptr)));

    if (gGlobal->gUseDefaultSound) {
        BlockInst* block = InstBuilder::genBlockInst();
        block->pushBackInst(InstBuilder::genStoreStructVar(varname, InstBuilder::genLoadGlobalVar("defaultsound")));

        pushResetUIInstructions(InstBuilder::genIfInst(
            InstBuilder::genEqual(InstBuilder::genCastInst(InstBuilder::genLoadStructVar(varname),
                                                           InstBuilder::genBasicTyped(Typed::kUint_ptr)),
                                  InstBuilder::genTypedZero(Typed::kSound_ptr)),
            block, InstBuilder::genBlockInst()));
    }

    if (gGlobal->gOneSample >= 0) {
        pushDeclare(InstBuilder::genDecStructVar(SFcache, InstBuilder::genBasicTyped(Typed::kSound_ptr)));
        pushComputeBlockMethod(InstBuilder::genStoreStructVar(SFcache, InstBuilder::genLoadStructVar(varname)));
        pushPostComputeBlockMethod(InstBuilder::genStoreStructVar(varname, InstBuilder::genLoadStructVar(SFcache)));
    } else {
        pushComputeBlockMethod(InstBuilder::genDecStackVar(SFcache, InstBuilder::genBasicTyped(Typed::kSound_ptr),
                                                           InstBuilder::genLoadStructVar(varname)));
        pushPostComputeBlockMethod(InstBuilder::genStoreStructVar(varname, InstBuilder::genLoadStackVar(SFcache)));
    }

    return InstBuilder::genLoadStructVar(varname);
}

ValueInst* InstructionsCompiler::generateSoundfileLength(Tree sig, ValueInst* sf, ValueInst* x)
{
    LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
    faustassert(load);

    Typed* type = InstBuilder::genBasicTyped(Typed::kInt32_ptr);

    string SFcache        = load->fAddress->getName() + "ca";
    string SFcache_length = gGlobal->getFreshID(SFcache + "_le");

    if (gGlobal->gOneSample >= 0) {

        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = InstBuilder::genLoadStructPtrVar(SFcache, Address::kStruct, InstBuilder::genInt32NumInst(1));

        pushDeclare(InstBuilder::genDecStructVar(SFcache_length, type));
        pushComputeBlockMethod(InstBuilder::genStoreStructVar(SFcache_length, v1));
        return InstBuilder::genLoadArrayStructVar(SFcache_length, x);
    } else {

        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = InstBuilder::genLoadStructPtrVar(SFcache, Address::kStack, InstBuilder::genInt32NumInst(1));

        pushComputeBlockMethod(InstBuilder::genDecStackVar(SFcache_length, type, v1));
        return InstBuilder::genLoadArrayStackVar(SFcache_length, x);
    }
}

ValueInst* InstructionsCompiler::generateSoundfileRate(Tree sig, ValueInst* sf, ValueInst* x)
{
    LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
    faustassert(load);

    Typed* type = InstBuilder::genBasicTyped(Typed::kInt32_ptr);

    string SFcache      = load->fAddress->getName() + "ca";
    string SFcache_rate = gGlobal->getFreshID(SFcache + "_ra");

    if (gGlobal->gOneSample >= 0) {

        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = InstBuilder::genLoadStructPtrVar(SFcache, Address::kStruct, InstBuilder::genInt32NumInst(2));

        pushDeclare(InstBuilder::genDecStructVar(SFcache_rate, type));
        pushComputeBlockMethod(InstBuilder::genStoreStructVar(SFcache_rate, v1));
        return InstBuilder::genLoadArrayStructVar(SFcache_rate, x);
    } else {

        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = InstBuilder::genLoadStructPtrVar(SFcache, Address::kStack, InstBuilder::genInt32NumInst(2));

        pushComputeBlockMethod(InstBuilder::genDecStackVar(SFcache_rate, type, v1));
        return InstBuilder::genLoadArrayStackVar(SFcache_rate, x);
    }
}

ValueInst* InstructionsCompiler::generateSoundfileBuffer(Tree sig, ValueInst* sf, ValueInst* x, ValueInst* y,
                                                         ValueInst* z)
{
    LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
    faustassert(load);

    Typed* type1 = InstBuilder::genBasicTyped(itfloatptrptr());
    Typed* type2 = InstBuilder::genItFloatTyped();
    Typed* type3 = InstBuilder::genBasicTyped(Typed::kInt32_ptr);

    string SFcache             = load->fAddress->getName() + "ca";
    string SFcache_buffer      = gGlobal->getFreshID(SFcache + "_bu");
    string SFcache_buffer_chan = gGlobal->getFreshID(SFcache + "_bu_ch");
    string SFcache_offset      = gGlobal->getFreshID(SFcache + "_of");

    if (gGlobal->gOneSample >= 0) {

        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = InstBuilder::genLoadStructPtrVar(SFcache, Address::kStruct, InstBuilder::genInt32NumInst(3));

        pushDeclare(InstBuilder::genDecStructVar(SFcache_offset, type3));
        pushComputeBlockMethod(InstBuilder::genStoreStructVar(SFcache_offset, v1));

        // Struct access using an index that will be converted as a field name
        LoadVarInst* load1 =
            InstBuilder::genLoadStructPtrVar(SFcache, Address::kStruct, InstBuilder::genInt32NumInst(0));

        pushDeclare(InstBuilder::genDecStructVar(SFcache_buffer, type1));
        // SFcache_buffer type is void* and has to be casted in the runtime buffer type
        pushComputeBlockMethod(InstBuilder::genStoreStructVar(SFcache_buffer, InstBuilder::genCastInst(load1, type1)));

        pushDeclare(InstBuilder::genDecStructVar(SFcache_buffer_chan, InstBuilder::genArrayTyped(type2, 0)));
        pushComputeBlockMethod(InstBuilder::genStoreStructVar(
            SFcache_buffer_chan, InstBuilder::genLoadStructPtrVar(SFcache_buffer, Address::kStruct, x)));

        return InstBuilder::genLoadStructPtrVar(
            SFcache_buffer_chan, Address::kStruct,
            InstBuilder::genAdd(InstBuilder::genLoadArrayStructVar(SFcache_offset, y), z));
    } else {

        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = InstBuilder::genLoadStructPtrVar(SFcache, Address::kStack, InstBuilder::genInt32NumInst(3));

        pushComputeBlockMethod(InstBuilder::genDecStackVar(SFcache_offset, type3, v1));

        // Struct access using an index that will be converted as a field name
        LoadVarInst* load1 =
            InstBuilder::genLoadStructPtrVar(SFcache, Address::kStack, InstBuilder::genInt32NumInst(0));

        // SFcache_buffer type is void* and has to be casted in the runtime buffer type
        pushComputeBlockMethod(InstBuilder::genDecStackVar(SFcache_buffer, type1, InstBuilder::genCastInst(load1, type1)));
        pushComputeBlockMethod(
            InstBuilder::genDecStackVar(SFcache_buffer_chan, InstBuilder::genArrayTyped(type2, 0),
                                        InstBuilder::genLoadStructPtrVar(SFcache_buffer, Address::kStack, x)));
        return InstBuilder::genLoadStructPtrVar(
            SFcache_buffer_chan, Address::kStack,
            InstBuilder::genAdd(InstBuilder::genLoadArrayStackVar(SFcache_offset, y), z));
    }
}

/*****************************************************************************
 TABLES
 *****************************************************************************/

/*----------------------------------------------------------------------------
 sigTable : table declaration
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateTable(Tree sig, Tree tsize, Tree content)
{
    int size;
    if (!isSigInt(tsize, &size)) {
        stringstream error;
        error << "ERROR : generateTable : " << *tsize << " is not an integer expression " << endl;
        throw faustexception(error.str());
    }

    ValueInst*     signame = CS(content);
    Typed::VarType ctype;
    Tree           g;
    string         vname;

    // already compiled but check if we need to add declarations
    faustassert(isSigGen(content, g));
    pair<string, string> kvnames;
    if (!fInstanceInitProperty.get(g, kvnames)) {
        // not declared here, we add a declaration
        bool b = fStaticInitProperty.get(g, kvnames);
        faustassert(b);
        Values args;
        if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
            args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        }
        ValueInst* obj = InstBuilder::genFunCallInst("new" + kvnames.first, args);
        pushInitMethod(InstBuilder::genDecStackVar(
            kvnames.second, InstBuilder::genNamedTyped(kvnames.first, InstBuilder::genBasicTyped(Typed::kObj_ptr)),
            obj));

        // HACK for Rust and Julia backends
        if (gGlobal->gOutputLang != "rust" && gGlobal->gOutputLang != "julia") {
            // Delete object
            Values args3;
            args3.push_back(signame);
            if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
                args3.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
            }
            pushPostInitMethod(InstBuilder::genVoidFunCallInst("delete" + kvnames.first, args3));
        }
    }

    // Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    // Table declaration
    pushDeclare(
        InstBuilder::genDecStructVar(vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), size)));

    string tablename;
    getTableNameProperty(content, tablename);

    // Init content generator
    Values args1;
    args1.push_back(signame);
    args1.push_back(InstBuilder::genLoadFunArgsVar("sample_rate"));
    pushInitMethod(InstBuilder::genVoidFunCallInst("instanceInit" + tablename, args1, true));

    // Fill the table
    Values args2;
    args2.push_back(signame);
    args2.push_back(InstBuilder::genInt32NumInst(size));
    // HACK for Rust backend
    args2.push_back(InstBuilder::genLoadMutRefStructVar(vname));
    pushInitMethod(InstBuilder::genVoidFunCallInst("fill" + tablename, args2, true));

    // Return table access
    return InstBuilder::genLoadStructVar(vname);
}

ValueInst* InstructionsCompiler::generateStaticTable(Tree sig, Tree tsize, Tree content)
{
    int size;
    if (!isSigInt(tsize, &size)) {
        stringstream error;
        error << "ERROR : generateStaticTable : " << *tsize << " is not an integer expression " << endl;
        throw faustexception(error.str());
    }

    Tree           g;
    ValueInst*     signame;
    Typed::VarType ctype;
    string         vname;

    ensure(isSigGen(content, g));

    if (!getCompiledExpression(content, signame)) {
        signame = setCompiledExpression(content, generateStaticSigGen(content, g));
    } else {
        // already compiled but check if we need to add declarations
        pair<string, string> kvnames;
        if (!fStaticInitProperty.get(g, kvnames)) {
            // not declared here, we add a declaration
            bool b = fInstanceInitProperty.get(g, kvnames);
            faustassert(b);
            Values args;
            if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
                args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
            }
            ValueInst* obj = InstBuilder::genFunCallInst("new" + kvnames.first, args);
            pushInitMethod(InstBuilder::genDecStackVar(
                kvnames.second, InstBuilder::genNamedTyped(kvnames.first, InstBuilder::genBasicTyped(Typed::kObj_ptr)),
                obj));

            // HACK for Rust and Julia backends
            if (gGlobal->gOutputLang != "rust" && gGlobal->gOutputLang != "julia") {
                // Delete object
                Values args3;
                args3.push_back(signame);
                if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
                    args3.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
                }
                pushPostInitMethod(InstBuilder::genVoidFunCallInst("delete" + kvnames.first, args3));
            }
        }
    }

    // Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    string tablename;
    getTableNameProperty(content, tablename);
    vname += tablename;

    // Table declaration
    if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
        pushGlobalDeclare(InstBuilder::genDecStaticStructVar(
            vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), 0), InstBuilder::genInt32NumInst(0)));
    } else {
        pushGlobalDeclare(InstBuilder::genDecStaticStructVar(
            vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), size)));
    }
    
    // Keep table size in bytes
    gGlobal->gTablesSize[tablename] = make_pair(vname, size * gGlobal->gTypeSizeMap[ctype]);

    // Init content generator
    Values args1;
    args1.push_back(signame);
    args1.push_back(InstBuilder::genLoadFunArgsVar("sample_rate"));
    pushStaticInitMethod(InstBuilder::genVoidFunCallInst("instanceInit" + tablename, args1, true));

    if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
        Values alloc_args;
        alloc_args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        alloc_args.push_back(InstBuilder::genInt32NumInst(size * gGlobal->gTypeSizeMap[ctype]));
        pushStaticInitMethod(InstBuilder::genStoreStaticStructVar(
            vname, InstBuilder::genCastInst(InstBuilder::genFunCallInst("allocate", alloc_args, true),
                                            InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), 0))));

        Values destroy_args;
        destroy_args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        destroy_args.push_back(InstBuilder::genLoadStaticStructVar(vname));
        pushStaticDestroyMethod(InstBuilder::genVoidFunCallInst("destroy", destroy_args, true));
    }

    // Fill the table
    Values args2;
    args2.push_back(signame);
    args2.push_back(InstBuilder::genInt32NumInst(size));
    // HACK for Rust backend
    args2.push_back(InstBuilder::genLoadStaticMutRefStructVar(vname));
    pushStaticInitMethod(InstBuilder::genVoidFunCallInst("fill" + tablename, args2, true));

    // Return table access
    return InstBuilder::genLoadStaticStructVar(vname);
}

/*----------------------------------------------------------------------------
 sigWRTable : table assignment
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateWRTbl(Tree sig, Tree tbl, Tree idx, Tree data)
{
    ValueInst*   tblname    = CS(tbl);
    LoadVarInst* load_value = dynamic_cast<LoadVarInst*>(tblname);
    faustassert(load_value);

    ValueInst* cdata = CS(data);
    string vname = load_value->fAddress->getName();

    Type t2 = getCertifiedSigType(idx);
    Type t3 = getCertifiedSigType(data);
    // TODO : for a bug in type caching, t->variability() is not correct.
    // Therefore in the meantime we compute it manually. (YO 2020/03/30)
    int var = t2->variability() | t3->variability();
    switch (var) {
        case kKonst:
            pushInitMethod(InstBuilder::genStoreArrayStructVar(vname, CS(idx), cdata));
            break;
        case kBlock:
            pushComputeBlockMethod(InstBuilder::genStoreArrayStructVar(vname, CS(idx), cdata));
            break;
        default:
            pushComputeDSPMethod(InstBuilder::genControlInst(getConditionCode(sig), InstBuilder::genStoreArrayStructVar(vname, CS(idx), cdata)));
            break;
    }

    // Return table access
    return InstBuilder::genLoadStructVar(vname);
}

/*----------------------------------------------------------------------------
 sigRDTable : table access
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateRDTbl(Tree sig, Tree tbl, Tree idx)
{
    // Test the special case of a read only table that can be compiled as a static member
    Tree                id, size, content;
    ValueInst*          tblname;
    Address::AccessType access;

    if (isSigTable(tbl, id, size, content)) {
        access = Address::kStaticStruct;
        if (!getCompiledExpression(tbl, tblname)) {
            tblname = setCompiledExpression(tbl, generateStaticTable(tbl, size, content));
        }
    } else {
        access  = Address::kStruct;
        tblname = CS(tbl);
    }

    LoadVarInst* load_value1 = dynamic_cast<LoadVarInst*>(tblname);
    faustassert(load_value1);

    LoadVarInst* load_value2 = InstBuilder::genLoadArrayVar(load_value1->fAddress->getName(), access, CS(idx));
    return generateCacheCode(sig, load_value2);
}

ValueInst* InstructionsCompiler::generateSigGen(Tree sig, Tree content)
{
    string cname   = gGlobal->getFreshID(fContainer->getClassName() + "SIG");
    string signame = gGlobal->getFreshID("sig");

    CodeContainer* subcontainer = signal2Container(cname, content);
    fContainer->addSubContainer(subcontainer);

    // We must allocate an object of type "cname"
    Values args;
    if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
        args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
    }
    ValueInst* obj = InstBuilder::genFunCallInst("new" + cname, args);
    pushInitMethod(InstBuilder::genDecStackVar(
        signame, InstBuilder::genNamedTyped(cname, InstBuilder::genBasicTyped(Typed::kObj_ptr)), obj));

    // HACK for Rust an Julia backends
    if (gGlobal->gOutputLang != "rust" && gGlobal->gOutputLang != "julia") {
        // Delete object
        Values args3;
        args3.push_back(InstBuilder::genLoadStackVar(signame));
        if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
            args3.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        }
        pushPostInitMethod(InstBuilder::genVoidFunCallInst("delete" + cname, args3));
    }

    setTableNameProperty(sig, cname);
    fInstanceInitProperty.set(content, pair<string, string>(cname, signame));

    return InstBuilder::genLoadStackVar(signame);
}

ValueInst* InstructionsCompiler::generateStaticSigGen(Tree sig, Tree content)
{
    string cname   = gGlobal->getFreshID(fContainer->getClassName() + "SIG");
    string signame = gGlobal->getFreshID("sig");

    CodeContainer* subcontainer = signal2Container(cname, content);
    fContainer->addSubContainer(subcontainer);

    // We must allocate an object of type "cname"
    Values args;
    if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
        args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
    }
    ValueInst* obj = InstBuilder::genFunCallInst("new" + cname, args);
    pushStaticInitMethod(InstBuilder::genDecStackVar(
        signame, InstBuilder::genNamedTyped(cname, InstBuilder::genBasicTyped(Typed::kObj_ptr)), obj));

    // HACK for Rust and Julia backends
    if (gGlobal->gOutputLang != "rust" && gGlobal->gOutputLang != "julia") {
        // Delete object
        Values args3;
        args3.push_back(InstBuilder::genLoadStackVar(signame));
        if (gGlobal->gMemoryManager && (gGlobal->gOneSample == -1)) {
            args3.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        }
        pushPostStaticInitMethod(InstBuilder::genVoidFunCallInst("delete" + cname, args3));
    }

    setTableNameProperty(sig, cname);
    fStaticInitProperty.set(content, pair<string, string>(cname, signame));

    return InstBuilder::genLoadStackVar(signame);
}

/*****************************************************************************
 RECURSIONS
 *****************************************************************************/

/**
 * Generate code for a projection of a group of mutually recursive definitions
 */
ValueInst* InstructionsCompiler::generateRecProj(Tree sig, Tree r, int i)
{
    string     vname;
    Tree       var, le;
    ValueInst* res;

    if (!getVectorNameProperty(sig, vname)) {
        ensure(isRec(r, var, le));
        res = generateRec(r, var, le, i);
        ensure(getVectorNameProperty(sig, vname));
    } else {
        res = InstBuilder::genNullValueInst();  // Result not used
    }
    return res;
}

/**
 * Generate code for a group of mutually recursive definitions
 */
ValueInst* InstructionsCompiler::generateRec(Tree sig, Tree var, Tree le, int index)
{
    int N = len(le);

    ValueInst*             res = nullptr;
    vector<bool>           used(N);
    vector<int>            delay(N);
    vector<string>         vname(N);
    vector<Typed::VarType> ctype(N);

    // Prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i, sig);  // recreate each recursive definition
        if (fOccMarkup->retrieve(e)) {
            // This projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(e), "Rec", ctype[i], vname[i]);
            setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup->retrieve(e)->getMaxDelay();
        } else {
            // This projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }

    // Generate delayline for each element of a recursive definition
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            Address::AccessType var_access;
            ValueInst* ccs = getConditionCode(nth(le, i));
            if (index == i) {
                res = generateDelayLine(CS(nth(le, i)), ctype[i], vname[i], delay[i], var_access, ccs);
            } else {
                generateDelayLine(CS(nth(le, i)), ctype[i], vname[i], delay[i], var_access, ccs);
            }
        }
    }

    return res;
}

/*****************************************************************************
 PREFIX, DELAY A PREFIX VALUE
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateControl(Tree sig, Tree x, Tree y)
{
    CS(y);
    return generateCacheCode(x, CS(x));
}

ValueInst* InstructionsCompiler::generatePrefix(Tree sig, Tree x, Tree e)
{
    string         vperm = gGlobal->getFreshID("pfPerm");
    string         vtemp = gGlobal->getFreshID("pfTemp");
    Typed::VarType type  = convert2FIRType(getCertifiedSigType(sig)->nature());

    // Variable declaration
    pushDeclare(InstBuilder::genDecStructVar(vperm, InstBuilder::genBasicTyped(type)));

    // Init
    pushInitMethod(InstBuilder::genStoreStructVar(vperm, CS(x)));
    
    // Exec
    pushComputeBlockMethod(InstBuilder::genControlInst(getConditionCode(sig),
                                                       InstBuilder::genDecStackVar(vtemp,
                                                                                   InstBuilder::genBasicTyped(type),
                                                                                   InstBuilder::genTypedZero(type))));
    pushComputeDSPMethod(InstBuilder::genControlInst(getConditionCode(sig),
                                                     InstBuilder::genStoreStackVar(vtemp, InstBuilder::genLoadStructVar(vperm))));
    
    /*
    ValueInst* res = CS(e);
    string vname;
    if (getVectorNameProperty(e, vname)) {
        setVectorNameProperty(sig, vname);
    } else {
        faustassert(false);
    }
    */
    
    pushComputeDSPMethod(InstBuilder::genControlInst(getConditionCode(sig), InstBuilder::genStoreStructVar(vperm, CS(e))));
    return InstBuilder::genLoadStackVar(vtemp);
}

/**
 * Generate code for a unique IOTA variable increased at each sample
 * and used to index ring buffers.
 */
void InstructionsCompiler::ensureIotaCode()
{
     if (fCurrentIOTA == "") {
         fCurrentIOTA = gGlobal->getFreshID("IOTA");
         pushDeclare(InstBuilder::genDecStructVar(fCurrentIOTA, InstBuilder::genInt32Typed()));
         pushClearMethod(InstBuilder::genStoreStructVar(fCurrentIOTA, InstBuilder::genInt32NumInst(0)));

         FIRIndex value = FIRIndex(InstBuilder::genLoadStructVar(fCurrentIOTA)) + 1;
         pushPostComputeDSPMethod(InstBuilder::genStoreStructVar(fCurrentIOTA, value));
    }
}

/*****************************************************************************
 SELECT
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    ValueInst* cond = CS(sel);
    ValueInst* v1   = CS(s1);
    ValueInst* v2   = CS(s2);
    
    if (gGlobal->gStrictSelect) {
        
        ::Type ct1 = getCertifiedSigType(s1);
        ::Type ct2 = getCertifiedSigType(s2);
        
        string v_then, v_else;
        Typed::VarType t_then, t_else;
        getTypedNames(ct1, "Then", t_then, v_then);
        getTypedNames(ct2, "Else", t_else, v_else);
        
        // Create local variables to force proper execution of both branches of 'select2'
        switch (getCertifiedSigType(sig)->variability()) {
                
            case kBlock:
                // Local variable is only created if needed that is if the expression
                // is not already a 'simple value', constant or variable
                if (!v1->isSimpleValue()) {
                    pushComputeBlockMethod(InstBuilder::genDecStackVar(v_then, InstBuilder::genBasicTyped(t_then), v1));
                    v1 = InstBuilder::genLoadStackVar(v_then);
                }
                if (!v2->isSimpleValue()) {
                    pushComputeBlockMethod(InstBuilder::genDecStackVar(v_else, InstBuilder::genBasicTyped(t_else), v2));
                    v2 = InstBuilder::genLoadStackVar(v_else);
                }
                break;
                
            case kSamp:
                // Local variable is only created if needed that is if the expression
                // is not already a 'simple value', constant or variable
                if (!v1->isSimpleValue()) {
                    pushComputeDSPMethod(InstBuilder::genDecStackVar(v_then, InstBuilder::genBasicTyped(t_then), v1));
                    v1 = InstBuilder::genLoadStackVar(v_then);
                }
                if (!v2->isSimpleValue()) {
                    pushComputeDSPMethod(InstBuilder::genDecStackVar(v_else, InstBuilder::genBasicTyped(t_else), v2));
                    v2 = InstBuilder::genLoadStackVar(v_else);
                }
                break;
        }
    }
  
    return generateCacheCode(sig, InstBuilder::genSelect2Inst(cond, v2, v1));
}

/*****************************************************************************
 EXTENDED
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateXtended(Tree sig)
{
    xtended* p = (xtended*)getUserData(sig);
    Values args;
    vector<::Type> types;

    for (int i = 0; i < sig->arity(); i++) {
        args.push_back(CS(sig->branch(i)));
        types.push_back(getCertifiedSigType(sig->branch(i)));
    }
    
    ValueInst* res = p->generateCode(fContainer, args, getCertifiedSigType(sig), types);
    if (p->needCache()) {
        return generateCacheCode(sig, res);
    } else {
        return res;
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
ValueInst* InstructionsCompiler::generateDelay(Tree sig, Tree exp, Tree delay)
{
    ValueInst* code = CS(exp);  // Ensure exp is compiled to have a vector name
    int        mxd  = fOccMarkup->retrieve(exp)->getMaxDelay();
    string     vname;

    if (!getVectorNameProperty(exp, vname)) {
        if (mxd == 0) {
            // cerr << "it is a pure zero delay : " << code << endl;
            return code;
        } else {
            cerr << "ERROR : no vector name for : " << ppsig(exp) << endl;
            faustassert(false);
        }
    }

    if (mxd == 0) {

        // not a real vector name but a scalar name
        return InstBuilder::genLoadStackVar(vname);

    } else if (mxd < gGlobal->gMaxCopyDelay) {
        int d;
        if (isSigInt(delay, &d)) {
            return InstBuilder::genLoadArrayStructVar(vname, CS(delay));
        } else {
            return generateCacheCode(sig, InstBuilder::genLoadArrayStructVar(vname, CS(delay)));
        }
    } else {

        int N = pow2limit(mxd + 1);
        if (N <= gGlobal->gMaskDelayLineThreshold) {
            
            ensureIotaCode();
            
            FIRIndex value2 = (FIRIndex(InstBuilder::genLoadStructVar(fCurrentIOTA)) - CS(delay)) & FIRIndex(N - 1);
            return generateCacheCode(sig, InstBuilder::genLoadArrayStructVar(vname, value2));
        } else {
            string ridx_name = gGlobal->getFreshID(vname + "_ridx_tmp");

            // int ridx = widx - delay;
            FIRIndex widx1 = FIRIndex(InstBuilder::genLoadStructVar(vname + "_widx"));
            pushComputeDSPMethod(InstBuilder::genDecStackVar(ridx_name, InstBuilder::genBasicTyped(Typed::kInt32), widx1 - CS(delay)));

            // dline[((ridx < 0) ? ridx + delay : ridx)];
            FIRIndex ridx1 = FIRIndex(InstBuilder::genLoadStackVar(ridx_name));
            FIRIndex ridx2 = FIRIndex(InstBuilder::genSelect2Inst(ridx1 < 0, ridx1 + FIRIndex(mxd + 1), ridx1));
            return generateCacheCode(sig, InstBuilder::genLoadArrayStructVar(vname, ridx2));
        }
    }
}

/**
 * Generate code for the delay mechanism. The generated code depends of the
 * maximum delay attached to exp and the "less temporaries" switch.
 */
ValueInst* InstructionsCompiler::generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const string& vname,
                                                  int mxd)
{
    setVectorNameProperty(sig, vname);
    Address::AccessType var_access;
    return generateDelayLine(exp, ctype, vname, mxd, var_access, getConditionCode(sig));
}

StatementInst* InstructionsCompiler::generateInitArray(const string& vname, Typed::VarType ctype, int delay)
{
    ValueInst*  init  = InstBuilder::genTypedZero(ctype);
    BasicTyped* typed = InstBuilder::genBasicTyped(ctype);
    string      index = gGlobal->getFreshID("l");

    // Generates table declaration
    pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genArrayTyped(typed, delay)));

    // Generates init table loop
    DeclareVarInst* loop_decl =
        InstBuilder::genDecLoopVar(index, InstBuilder::genInt32Typed(), InstBuilder::genInt32NumInst(0));
    ValueInst*    loop_end = InstBuilder::genLessThan(loop_decl->load(), InstBuilder::genInt32NumInst(delay));
    StoreVarInst* loop_inc = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_inc);

    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loop_decl->load(), init));
    return loop;
}

StatementInst* InstructionsCompiler::generateShiftArray(const string& vname, int delay)
{
    string index = gGlobal->getFreshID("j");

    // Generates init table loop
    DeclareVarInst* loop_decl =
        InstBuilder::genDecLoopVar(index, InstBuilder::genInt32Typed(), InstBuilder::genInt32NumInst(delay));
    ValueInst*    loop_end = InstBuilder::genGreaterThan(loop_decl->load(), InstBuilder::genInt32NumInst(0));
    StoreVarInst* loop_inc = loop_decl->store(InstBuilder::genSub(loop_decl->load(), InstBuilder::genInt32NumInst(1)));

    ForLoopInst* loop        = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_inc);
    ValueInst*   load_value2 = InstBuilder::genSub(loop_decl->load(), InstBuilder::genInt32NumInst(1));
    ValueInst*   load_value3 = InstBuilder::genLoadArrayStructVar(vname, load_value2);

    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loop_decl->load(), load_value3));
    return loop;
}

StatementInst* InstructionsCompiler::generateCopyArray(const string& vname, int index_from, int index_to)
{
    ValueInst* inst1 = InstBuilder::genLoadArrayStructVar(vname, InstBuilder::genInt32NumInst(index_from));
    return InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genInt32NumInst(index_to), inst1);
}

StatementInst* InstructionsCompiler::generateCopyArray(const string& vname_to, const string& vname_from, int size)
{
    string index = gGlobal->getFreshID("j");

    // Generates init table loop
    DeclareVarInst* loop_decl =
        InstBuilder::genDecLoopVar(index, InstBuilder::genInt32Typed(), InstBuilder::genInt32NumInst(0));
    ValueInst*    loop_end = InstBuilder::genLessThan(loop_decl->load(), InstBuilder::genInt32NumInst(size));
    StoreVarInst* loop_inc = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop       = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_inc);
    ValueInst*   load_value = InstBuilder::genLoadArrayStructVar(vname_from, loop_decl->load());

    loop->pushFrontInst(InstBuilder::genStoreArrayStackVar(vname_to, loop_decl->load(), load_value));
    return loop;
}

ValueInst* InstructionsCompiler::generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd,
                                                   Address::AccessType& var_access, ValueInst* ccs)
{
    if (mxd == 0) {

        // Generate scalar use
        if (dynamic_cast<NullValueInst*>(ccs)) {
            pushComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), exp));
        } else {
            pushPreComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), InstBuilder::genTypedZero(ctype)));
            pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStackVar(vname, exp)));
        }

    } else if (mxd < gGlobal->gMaxCopyDelay) {

        // Generates table init
        pushClearMethod(generateInitArray(vname, ctype, mxd + 1));

        // Generate table use
        pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genInt32NumInst(0), exp)));

        // Generates post processing copy code to update delay values
        if (mxd == 1) {
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, generateCopyArray(vname, 0, 1)));
        } else if (mxd == 2) {
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, generateCopyArray(vname, 1, 2)));
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, generateCopyArray(vname, 0, 1)));
        } else {
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, generateShiftArray(vname, mxd)));
        }

    } else {

        int N = pow2limit(mxd + 1);
        if (N <= gGlobal->gMaskDelayLineThreshold) {

            ensureIotaCode();

            // Generates table init
            pushClearMethod(generateInitArray(vname, ctype, N));

            // Generate table use
            if (gGlobal->gComputeIOTA) {  // Ensure IOTA base fixed delays are computed once
                if (fIOTATable.find(N) == fIOTATable.end()) {
                    string   iota_name = subst("i$0", gGlobal->getFreshID(fCurrentIOTA + "_temp"));
                    FIRIndex value2 = FIRIndex(InstBuilder::genLoadStructVar(fCurrentIOTA)) & FIRIndex(N - 1);

                    pushPreComputeDSPMethod(InstBuilder::genDecStackVar(iota_name, InstBuilder::genInt32Typed(), InstBuilder::genInt32NumInst(0)));
                    pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStackVar(iota_name, value2)));

                    fIOTATable[N] = iota_name;
                }

                pushComputeDSPMethod(InstBuilder::genControlInst(ccs,
                    InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genLoadStackVar(fIOTATable[N]), exp)));

            } else {
                FIRIndex value2 = FIRIndex(InstBuilder::genLoadStructVar(fCurrentIOTA)) & FIRIndex(N - 1);
                pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreArrayStructVar(vname, value2, exp)));
            }
        } else {

            // 'select' based delay
            string widx_tmp_name = vname + "_widx_tmp";
            string widx_name = vname + "_widx";

            // Generates table write index
            pushDeclare(InstBuilder::genDecStructVar(widx_name, InstBuilder::genInt32Typed()));
            pushInitMethod(InstBuilder::genStoreStructVar(widx_name, InstBuilder::genInt32NumInst(0)));

            // Generates table init
            pushClearMethod(generateInitArray(vname, ctype, mxd + 1));

            // int w = widx;
            pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genDecStackVar(widx_tmp_name, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genLoadStructVar(widx_name))));

            // dline[w] = v;
            pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genLoadStackVar(widx_tmp_name), exp)));

            // w = w + 1;
            FIRIndex widx_tmp1 = FIRIndex(InstBuilder::genLoadStackVar(widx_tmp_name));
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStackVar(widx_tmp_name, widx_tmp1 + 1)));

            // w = ((w == delay) ? 0 : w);
            FIRIndex widx_tmp2 = FIRIndex(InstBuilder::genLoadStackVar(widx_tmp_name));
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStackVar(widx_tmp_name,
                                                                   InstBuilder::genSelect2Inst(widx_tmp2 == FIRIndex(mxd + 1),
                                                                                               FIRIndex(0),
                                                                                               widx_tmp2))));
            // *widx = w
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStructVar(widx_name, InstBuilder::genLoadStackVar(widx_tmp_name))));
        }
    }

    return exp;
}

/*****************************************************************************
 WAVEFORM
 *****************************************************************************/

/**
 * Generate code for a waveform. The waveform will be declared as a static field.
 * The name of the waveform is returned in vname and its size in size.
 */
void InstructionsCompiler::declareWaveform(Tree sig, string& vname, int& size)
{
    // computes C type and unique name for the waveform

    Typed::VarType ctype;
    getTypedNames(getCertifiedSigType(sig), fContainer->getClassName() + "Wave", ctype, vname);
    size = sig->arity();

    // Declares the Waveform
    Typed*     type      = InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), size);
    ValueInst* num_array = InstBuilder::genArrayNumInst(ctype, size);

    double r;
    int    i;

    if (ctype == Typed::kInt32) {
        Int32ArrayNumInst* int_array = dynamic_cast<Int32ArrayNumInst*>(num_array);
        faustassert(int_array);
        for (int k = 0; k < size; k++) {
            if (isSigInt(sig->branch(k), &i)) {
                int_array->setValue(k, i);
            } else if (isSigReal(sig->branch(k), &r)) {
                int_array->setValue(k, int(r));
            }
        }
    } else if (ctype == Typed::kFloat) {
        FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(num_array);
        faustassert(float_array);
        for (int k = 0; k < size; k++) {
            if (isSigInt(sig->branch(k), &i)) {
                float_array->setValue(k, float(i));
            } else if (isSigReal(sig->branch(k), &r)) {
                float_array->setValue(k, float(r));
            }
        }
    } else if (ctype == Typed::kDouble) {
        DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(num_array);
        faustassert(double_array);
        for (int k = 0; k < size; k++) {
            if (isSigInt(sig->branch(k), &i)) {
                double_array->setValue(k, double(i));
            } else if (isSigReal(sig->branch(k), &r)) {
                double_array->setValue(k, r);
            }
        }
    } else {
        faustassert(false);
    }

    if (gGlobal->gWaveformInDSP) {
        // waveform are allocated in the DSP and not as global data
        pushStaticInitMethod(InstBuilder::genDecStaticStructVar(vname, type, num_array));
    } else {
        pushGlobalDeclare(InstBuilder::genDecConstStaticStructVar(vname, type, num_array));
    }

    string idx = subst("$0_idx", vname);
    pushDeclare(InstBuilder::genDecStructVar(idx, InstBuilder::genInt32Typed()));
    pushInitMethod(InstBuilder::genStoreStructVar(idx, InstBuilder::genInt32NumInst(0)));
}

ValueInst* InstructionsCompiler::generateWaveform(Tree sig)
{
    string vname;
    int    size;

    declareWaveform(sig, vname, size);

    string   idx   = subst("$0_idx", vname);
    FIRIndex index = (FIRIndex(1) + InstBuilder::genLoadStructVar(idx)) % InstBuilder::genInt32NumInst(size);
    pushPostComputeDSPMethod(InstBuilder::genControlInst(getConditionCode(sig), InstBuilder::genStoreStructVar(idx, index)));
    return generateCacheCode(sig, InstBuilder::genLoadArrayStaticStructVar(vname, InstBuilder::genLoadStructVar(idx)));
}

/**
 * Add a widget with a certain path to the user interface tree
 */
void InstructionsCompiler::addUIWidget(Tree path, Tree widget)
{
    fUIRoot = putSubFolder(fUIRoot, path, widget);
}

/**
 * Remove fake root folder if not needed (that is if the UI
 * is completely enclosed in one folder)
 */
Tree InstructionsCompiler::prepareUserInterfaceTree(Tree t)
{
    Tree root, elems;
    if (isUiFolder(t, root, elems) && isList(elems) && isNil(tl(elems))) {
        Tree folder = right(hd(elems));
        return (isUiFolder(folder)) ? folder : t;
    }
    return t;
}

//================================= BUILD USER INTERFACE METHOD =================================

/**
 * Generate buildUserInterface corresponding to user interface element t
 */
void InstructionsCompiler::generateUserInterfaceTree(Tree t, bool root)
{
    Tree label, elements, varname, sig;

    if (isUiFolder(t, label, elements)) {
        OpenboxInst::BoxType orient = static_cast<OpenboxInst::BoxType>(tree2int(left(label)));
        // Empty labels will be renamed with a 0xABCD (address) that is ignored and not displayed by UI architectures
        string str = tree2str(right(label));

        // extract metadata from group label str resulting in a simplifiedLabel
        // and metadata declarations for fictive zone at address 0
        string                    simplifiedLabel;
        map<string, set<string> > metadata;
        extractMetadata(str, simplifiedLabel, metadata);

        // add metadata if any
        for (const auto& i : metadata) {
            const string&      key    = i.first;
            const set<string>& values = i.second;
            for (const auto& j : values) {
                pushUserInterfaceMethod(InstBuilder::genAddMetaDeclareInst("0", rmWhiteSpaces(key), rmWhiteSpaces(j)));
            }
        }
        // At rool level and if label is empty, use the name kept in "metadata" (either the one coded in 'declare name
        // "XXX";' line, or the filename)
        string group = (root && (simplifiedLabel == ""))
                           ? unquote(tree2str(*(gGlobal->gMetaDataSet[tree("name")].begin())))
                           : checkNullLabel(t, simplifiedLabel);

        pushUserInterfaceMethod(InstBuilder::genOpenboxInst(group, orient));
        generateUserInterfaceElements(elements);
        pushUserInterfaceMethod(InstBuilder::genCloseboxInst());
    } else if (isUiWidget(t, label, varname, sig)) {
        generateWidgetCode(label, varname, sig);
    } else {
        cerr << "ERROR : user interface generation\n";
        faustassert(false);
    }
}

/**
 * Iterate generateUserInterfaceTree on a list of user interface elements
 */
void InstructionsCompiler::generateUserInterfaceElements(Tree elements)
{
    while (!isNil(elements)) {
        generateUserInterfaceTree(right(hd(elements)));
        elements = tl(elements);
    }
}

/**
 * Generate buildUserInterface C++ lines of code corresponding
 * to user interface widget t
 */
void InstructionsCompiler::generateWidgetCode(Tree fulllabel, Tree varname, Tree sig)
{
    Tree                      path, c, x, y, z;
    map<string, set<string> > metadata;
    string                    label, url;

    extractMetadata(tree2str(fulllabel), label, metadata);

    // Extract "url" metadata to be given as parameter to 'addSoundfile' function
    if (isSigSoundfile(sig, path)) {
        for (const auto& i : metadata) {
            const string&      key    = i.first;
            const set<string>& values = i.second;
            for (const auto& j : values) {
                if (key == "url") {
                    url = prepareURL(j);
                }
            }
        }
    } else {
        // Add metadata if any
        for (const auto& i : metadata) {
            const string&      key    = i.first;
            const set<string>& values = i.second;
            for (const auto& j : values) {
                pushUserInterfaceMethod(InstBuilder::genAddMetaDeclareInst(tree2str(varname), rmWhiteSpaces(key), rmWhiteSpaces(j)));
            }
        }
    }

    if (isSigButton(sig, path)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddButtonInst(checkNullLabel(varname, label), tree2str(varname)));

    } else if (isSigCheckbox(sig, path)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddCheckbuttonInst(checkNullLabel(varname, label), tree2str(varname)));

    } else if (isSigVSlider(sig, path, c, x, y, z)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddVerticalSliderInst(checkNullLabel(varname, label), tree2str(varname),
                                                                      tree2float(c), tree2float(x), tree2float(y),
                                                                      tree2float(z)));

    } else if (isSigHSlider(sig, path, c, x, y, z)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddHorizontalSliderInst(checkNullLabel(varname, label),
                                                                        tree2str(varname), tree2float(c), tree2float(x),
                                                                        tree2float(y), tree2float(z)));

    } else if (isSigNumEntry(sig, path, c, x, y, z)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddNumEntryInst(checkNullLabel(varname, label), tree2str(varname),
                                                                tree2float(c), tree2float(x), tree2float(y),
                                                                tree2float(z)));

    } else if (isSigVBargraph(sig, path, x, y, z)) {
        fContainer->incUIPassiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddVerticalBargraphInst(
            checkNullLabel(varname, label, true), tree2str(varname), tree2float(x), tree2float(y)));

    } else if (isSigHBargraph(sig, path, x, y, z)) {
        fContainer->incUIPassiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddHorizontalBargraphInst(
            checkNullLabel(varname, label, true), tree2str(varname), tree2float(x), tree2float(y)));

    } else if (isSigSoundfile(sig, path)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddSoundfileInst(
            checkNullLabel(varname, label, true), ((url == "") ? prepareURL(label) : url), tree2str(varname)));

    } else {
        cerr << "ERROR : generating widget code\n";
        faustassert(false);
    }
}

//==================================== USER INTERFACE MACROS ==================================

/**
 * Generate user interface macros corresponding
 * to user interface element t
 */
void InstructionsCompiler::generateMacroInterfaceTree(const string& pathname, Tree t)
{
    Tree label, elements, varname, sig;

    if (isUiFolder(t, label, elements)) {
        string pathname2 = pathname;
        string str       = tree2str(right(label));
        if (str.length() > 0) pathname2 += str + "/";
        generateMacroInterfaceElements(pathname2, elements);
    } else if (isUiWidget(t, label, varname, sig)) {
        generateWidgetMacro(pathname, label, varname, sig);
    } else {
        cerr << "ERROR : user interface macro generation\n";
        faustassert(false);
    }
}

/**
 * Iterate generateMacroInterfaceTree on a list of user interface elements
 */
void InstructionsCompiler::generateMacroInterfaceElements(const string& pathname, Tree elements)
{
    while (!isNil(elements)) {
        generateMacroInterfaceTree(pathname, right(hd(elements)));
        elements = tl(elements);
    }
}

/**
 * Generate user interface macros corresponding
 * to a user interface widget
 */
void InstructionsCompiler::generateWidgetMacro(const string& pathname, Tree fulllabel, Tree varname, Tree sig)
{
    Tree                      path, c, x, y, z;
    string                    label;
    map<string, set<string>>  metadata;
  
    extractMetadata(tree2str(fulllabel), label, metadata);
    string pathlabel = pathname + label;
    string rawlabel = label;
    std::replace(rawlabel.begin(), rawlabel.end(), ' ', '_');

    if (isSigButton(sig, path)) {
        fContainer->addUIMacro(subst("FAUST_ADDBUTTON(\"$0\", $1);", pathlabel, tree2str(varname)));
        fContainer->addUIMacroActives(subst("p(BUTTON, $0, \"$1\", $2, $3, $4, $5, $6) \\", rawlabel, pathlabel, tree2str(varname), T(0.), T(0.), T(1.0), T(1.0)));

    } else if (isSigCheckbox(sig, path)) {
        fContainer->addUIMacro(subst("FAUST_ADDCHECKBOX(\"$0\", $1);", pathlabel, tree2str(varname)));
        fContainer->addUIMacroActives(subst("p(CHECKBOX, $0, \"$1\", $2, $3, $4, $5, $6) \\", rawlabel, pathlabel, tree2str(varname), T(0.), T(0.), T(1.0), T(1.0)));

    } else if (isSigVSlider(sig, path, c, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDVERTICALSLIDER(\"$0\", $1, $2, $3, $4, $5);", pathlabel,
                                     tree2str(varname), T(tree2float(c)), T(tree2float(x)), T(tree2float(y)),
                                     T(tree2float(z))));
        fContainer->addUIMacroActives(subst("p(VERTICALSLIDER, $0, \"$1\", $2, $3, $4, $5, $6) \\", rawlabel, pathlabel,
                                            tree2str(varname), T(tree2float(c)), T(tree2float(x)), T(tree2float(y)),
                                            T(tree2float(z))));

    } else if (isSigHSlider(sig, path, c, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDHORIZONTALSLIDER(\"$0\", $1, $2, $3, $4, $5);", pathlabel,
                                     tree2str(varname), T(tree2float(c)), T(tree2float(x)), T(tree2float(y)),
                                     T(tree2float(z))));
        fContainer->addUIMacroActives(subst("p(HORIZONTALSLIDER, $0, \"$1\", $2, $3, $4, $5, $6) \\", rawlabel, pathlabel,
                                            tree2str(varname), T(tree2float(c)), T(tree2float(x)), T(tree2float(y)),
                                            T(tree2float(z))));

    } else if (isSigNumEntry(sig, path, c, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDNUMENTRY(\"$0\", $1, $2, $3, $4, $5);", pathlabel, tree2str(varname),
                                     T(tree2float(c)), T(tree2float(x)), T(tree2float(y)), T(tree2float(z))));
        fContainer->addUIMacroActives(subst("p(NUMENTRY, $0, \"$1\", $2, $3, $4, $5, $6) \\", rawlabel, pathlabel,
                                            tree2str(varname), T(tree2float(c)), T(tree2float(x)), T(tree2float(y)),
                                            T(tree2float(z))));

    } else if (isSigVBargraph(sig, path, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDVERTICALBARGRAPH(\"$0\", $1, $2, $3);", pathlabel, tree2str(varname),
                                     T(tree2float(x)), T(tree2float(y))));
        fContainer->addUIMacroPassives(subst("p(VERTICALBARGRAPH, $0, \"$1\", $2, 0.0, $3, $4, 0.0) \\", rawlabel, pathlabel,
                                            tree2str(varname), T(tree2float(x)), T(tree2float(y))));

    } else if (isSigHBargraph(sig, path, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDHORIZONTALBARGRAPH(\"$0\", $1, $2, $3);", pathlabel, tree2str(varname),
                                     T(tree2float(x)), T(tree2float(y))));
        fContainer->addUIMacroPassives(subst("p(HORIZONTALBARGRAPH, $0, \"$1\", $2, 0.0, $3, $4, 0.0) \\", rawlabel, pathlabel,
                                            tree2str(varname), T(tree2float(x)), T(tree2float(y))));

    } else if (isSigSoundfile(sig, path)) {
        fContainer->addUIMacro(subst("FAUST_ADDSOUNDFILE(\"$0\", $1);", pathlabel, tree2str(varname)));

    } else {
        cerr << "ERROR : generating widget code\n";
        faustassert(false);
    }
}
