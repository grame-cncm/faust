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

#include <algorithm>
#include <string>

#include "mixForm.hh"
#include "aterm.hh"
#include "Text.hh"
#include "dsp_aux.hh"
#include "fir_to_fir.hh"
#include "floats.hh"
#include "instructions.hh"
#include "instructions_compiler.hh"
#include "exactWeights.hh"
#include "sumLanes.hh"
#include "shareSums.hh"
#include "instructions_compiler1.hh"
#include "instructions_compiler_jax.hh"
#include "interpreter_code_container.hh"
#include "nnx_base_instructions.hh"
#include "normalform.hh"
#include "prim2.hh"
#include "recursivness.hh"
#include "sharing.hh"
#include "sigNewConstantPropagation.hh"
#include "sigPromotion.hh"
#include "sigRetiming.hh"
#include "sigToGraph.hh"
#include "signal2Elementary.hh"
#include "signalFIRCompiler.hh"
#include "signalVisitor.hh"
#include "sigprint.hh"
#include "compile.hh"
#include "irm_weight.hh"
#include "bpf_table.hh"
#include "sigtyperules.hh"
#include "timing.hh"
#include "xtendedCodegen.hh"

#include "c_instructions.hh"
#include "cpp_instructions.hh"
#include "global.hh"

using namespace std;

ostream* Printable::fOut = &cout;

static inline BasicTyped* genBasicFIRTyped(int sig_type)
{
    return IB::genBasicTyped(convert2FIRType(sig_type));
}

static inline BasicTyped* genBasicFIRTyped(Tree sig)
{
    return IB::genBasicTyped(convert2FIRType(getCertifiedSigType(sig)->nature()));
}

ValueInst* InstructionsCompiler::genCastedOutput(int type, ValueInst* value)
{
    bool need_cast = (type == kInt) || !gGlobal->gFAUSTFLOAT2Internal;
    return (need_cast) ? IB::genCastFloatMacroInst(value) : value;
}

ValueInst* InstructionsCompiler::genCastedOutput(ValueInst* value)
{
    return (gGlobal->gFAUSTFLOAT2Internal) ? value : IB::genCastFloatMacroInst(value);
}

ValueInst* InstructionsCompiler::genCastedInput(ValueInst* value)
{
    return (gGlobal->gFAUSTFLOAT2Internal) ? value : IB::genCastInst(value, IB::genItFloatTyped());
}

InstructionsCompiler::InstructionsCompiler(CodeContainer* container)
    : fContainer(container), fSharingKey(nullptr), fOccMarkup(nullptr), fDescription(nullptr)
{
}

/*****************************************************************************
 prepare
 *****************************************************************************/

Tree InstructionsCompiler::prepare(Tree LS)
{
    startTiming("prepare");
    Tree L0 = simplifyToNormalForm(LS);
    Tree L1 = L0;

    /*
     Possibly cast bool binary operations (comparison operations) to int.
     Done after simplifyToNormalForm which does SignalTreeChecker,
     that would fail after sigBool2IntPromote which adds additional
     sigIntCast on bool producing BinOp operations.
     */
    if (gGlobal->gBool2Int) {
        L1 = signalBool2IntPromote(L1);
    }

    // -norm prints the certified program, typed below ; a program refused before is
    // printed in its normal form
    if (gGlobal->gDumpNorm == 0) {
        try {
            typeAnnotation(L1, true);
        } catch (faustexception&) {
            dumpEquations(L1);
        }
    }

    // The interval constant propagation, as in the ocpp compiler : a signal whose
    // interval is a single value becomes that value (0*x with x bounded, cos(0*x)).
    // The normal form leaves typed : only the delay causality is left to check.
    if (L1 == L0 && !gGlobal->gLocalCausalityCheck) {
        typeCheckDelayCausality(L1);
    } else {
        typeAnnotation(L1, true);
    }
    Tree L2 = newConstantPropagation(L1);
    if (gGlobal->gShareSums) {
        // the dense sums factored by coefficient, their common sub-sums shared (-noshs),
        // before the certified typing, which bounds the rewritten program
        startTiming("shareSums");
        L2 = shareSums(L2);
        endTiming("shareSums");
    }
    if (gGlobal->gExactWeights) {
        // -xw : (1 + w) * y written w * y + y, a small w read exactly, not through 1 + w
        // rounded, before the certified typing
        startTiming("exactWeights");
        L2 = exactWeights(L2);
        endTiming("exactWeights");
    }
    if (gGlobal->gSumLanes) {
        // the long sums in interleaved partial sums (-nosl), before the certified typing,
        // which bounds the rewritten program
        startTiming("sumLanes");
        L2 = sumLanes(L2);
        endTiming("sumLanes");
    }

    startTiming("conditionAnnotation");
    conditionAnnotation(L2);
    endTiming("conditionAnnotation");

    startTiming("recursivnessAnnotation");
    recursivnessAnnotation(L2);  // Annotate L2 with recursivness information
    endTiming("recursivnessAnnotation");

    if (gGlobal->gDumpNorm == 0) {
        dumpEquations(L2);  // -norm : the program the certified typing bounds
    }
    startTiming("L2 typeAnnotation");
    typeAnnotation(L2, true);  // Annotate L2 with type information and check causality
    endTiming("L2 typeAnnotation");
    checkCertificates();  // a program bounded for less than 10 seconds is refused
    checkLightTypes(L2);  // FAUST_CHECK_LIGHT_TYPES : the light typing against the certified one

    startTiming("sharingAnalysis");
    sharingAnalysis(L2, fSharingKey);  // Annotate L2 with sharing count
    endTiming("sharingAnalysis");

    startTiming("occurrences analysis");
    delete fOccMarkup;
    fOccMarkup = new OccMarkup(fConditionProperty);
    fOccMarkup->mark(L2);  // Annotate L2 with occurrences analysis
    fDefinitions.build(L2);  // the subterms of compound definitions the program holds
    fDefinitions.countReads(fSharingKey);
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

Tree InstructionsCompiler::prepare2(Tree L0)
{
    startTiming("prepare2");

    recursivnessAnnotation(L0);        // Annotate L0 with recursivness information
    typeAnnotation(L0, true);          // Annotate L0 with type information
    sharingAnalysis(L0, fSharingKey);  // Annotate L0 with sharing count

    delete fOccMarkup;
    fOccMarkup = new OccMarkup();
    fOccMarkup->mark(L0);  // Annotate L0 with occurrences analysis

    endTiming("prepare2");
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

ValueInst* InstructionsCompiler::dnf2code(Tree cc)
{
    if (cc == gGlobal->nil) {
        return IB::genNullValueInst();
    }
    Tree c1 = hd(cc);
    cc      = tl(cc);
    if (cc == gGlobal->nil) {
        return and2code(c1);
    } else {
        ValueInst* v1 = and2code(c1);
        ValueInst* v2 = dnf2code(cc);
        return IB::genOr(v1, v2);
    }
}

ValueInst* InstructionsCompiler::and2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return IB::genNullValueInst();
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        ValueInst* v1 = CS(c1);
        ValueInst* v2 = and2code(cs);
        return IB::genAnd(v1, v2);
    }
}

ValueInst* InstructionsCompiler::cnf2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return IB::genNullValueInst();
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return or2code(c1);
    } else {
        ValueInst* v1 = or2code(c1);
        ValueInst* v2 = cnf2code(cs);
        return IB::genAnd(v1, v2);
    }
}

ValueInst* InstructionsCompiler::or2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return IB::genNullValueInst();
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        ValueInst* v1 = CS(c1);
        ValueInst* v2 = or2code(cs);
        return IB::genOr(v1, v2);
    }
}

// Temporary implementation for test purposes
ValueInst* InstructionsCompiler::getConditionCode(Tree sig)
{
    Tree cc = fConditionProperty[sig];
    if ((cc != nullptr) && (cc != gGlobal->nil)) {
        return CND2CODE(cc);
    } else {
        return IB::genNullValueInst();
    }
}

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
    map<Tree, int, treeorder>
        fConditionStatistics;  // used with the new X,Y:enable --> sigEnable(X*Y,Y != 0) primitive
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
bool InstructionsCompiler::getCompiledExpression(Tree sig, ValueType& cexp)
{
    return fCompileProperty.get(sig, cexp);
}

/**
 * Set the ValueType of a compiled expression is already compiled
 * @param sig the signal expression to compile.
 * @param cexp the ValueType representing the compiled expression.
 * @return the cexp (for commodity)
 */
ValueType InstructionsCompiler::setCompiledExpression(Tree sig, const ValueType& cexp)
{
    ValueType old;
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

// Generate BasicTyped with float/double/quad
BasicTyped* InstructionsCompiler::genFloatType(::Type type)
{
    return IB::genBasicTyped(itfloat());
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

    if (gGlobal->gOutputLang == "rust" || gGlobal->gOutputLang == "julia" ||
        gGlobal->gOutputLang == "asc") {
        InstructionsCompiler1 C(container);
        C.compileSingleSignal(sig);
    } else if (gGlobal->isPythonBackend()) {
        InstructionsCompilerJAX C(container);
        C.compileSingleSignal(sig);
    } else if (gGlobal->gOutputLang == "interp") {
        InterpreterInstructionsCompiler C(container);
        C.compileSingleSignal(sig);
    } else {
        // Special compiler for -fx mode
        if (gGlobal->gFloatSize == 4) {
            InstructionsFXCompiler C(container);
            C.compileSingleSignal(sig);
        } else {
            InstructionsCompiler C(container);
            C.compileSingleSignal(sig);
        }
    }
    return container;
}

/*****************************************************************************
 compileMultiSignal
 *****************************************************************************/

void InstructionsCompiler::compileMultiSignal(Tree L)
{
    // Compile inputs
    struct InputCompiler : public SignalVisitor {
        InstructionsCompiler* fComp;

        InputCompiler(Tree L, InstructionsCompiler* comp)
        {
            fComp = comp;
            visitRoot(L);
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
    if (gGlobal->gInPlace) {
        InputCompiler(L, this);
    }

#ifdef LLVM_DEBUG
    // Add function declaration
    pushGlobalDeclare(IB::genFunction1("printInt32", Typed::kVoid, "val", Typed::kInt32));
    pushGlobalDeclare(IB::genFunction1("printFloat", Typed::kVoid, "val", Typed::kFloat));
    pushGlobalDeclare(IB::genFunction1("printDouble", Typed::kVoid, "val", Typed::kDouble));
    pushGlobalDeclare(IB::genFunction1("printPtr", Typed::kVoid, "val", Typed::kVoid_ptr));
#endif

    Typed* type     = IB::genFloatMacroTyped();
    Typed* ptr_type = IB::genArrayTyped(type, 0);

    if (!gGlobal->gOpenCLSwitch && !gGlobal->gCUDASwitch) {  // HACK

        // Input declarations
        if (gGlobal->gOutputLang == "rust" && !gGlobal->gInPlace) {
            // special handling for Rust backend
            pushComputeBlockMethod(IB::genDeclareBufferIterators(
                "*input", "inputs", fContainer->inputs(), type, false));
        } else if (gGlobal->gOutputLang == "rust" && gGlobal->gInPlace) {
            // Nothing...
        } else if (gGlobal->gOutputLang == "julia") {
            // special handling Julia backend
            pushComputeBlockMethod(IB::genDeclareBufferIterators(
                "input", "inputs", fContainer->inputs(), ptr_type, false));
        } else if (!gGlobal->isPythonBackend()) {
            // "input" and "inputs" used as a name convention
            if (gGlobal->gOneSampleIO) {
                for (int index = 0; index < fContainer->inputs(); index++) {
                    string name = subst("input$0", T(index));
                    pushDeclare(IB::genDecStructVar(name, type));
                }
            } else if (gGlobal->gOneSample) {
                // Nothing...
            } else {
                for (int index = 0; index < fContainer->inputs(); index++) {
                    string name = subst("input$0", T(index));
                    pushComputeBlockMethod(IB::genDecStackVar(
                        name, ptr_type,
                        IB::genLoadArrayFunArgsVar("inputs", IB::genInt32NumInst(index))));
                }
            }
        }

        // Output declarations
        if (gGlobal->gOutputLang == "rust" && !gGlobal->gInPlace) {
            // special handling for Rust backend
            pushComputeBlockMethod(IB::genDeclareBufferIterators(
                "*output", "outputs", fContainer->outputs(), type, true));
        } else if (gGlobal->gOutputLang == "rust" && gGlobal->gInPlace) {
            // TODO: what if there are more inputs than outputs?
            int ios = max(fContainer->outputs(), fContainer->inputs());
            pushComputeBlockMethod(IB::genDeclareBufferIterators("*io", "ios", ios, type, true));
        } else if (gGlobal->gOutputLang == "julia") {
            // special handling for Julia backend
            pushComputeBlockMethod(IB::genDeclareBufferIterators(
                "output", "outputs", fContainer->outputs(), ptr_type, true));
        } else if (!gGlobal->isPythonBackend()) {
            // "output" and "outputs" used as a name convention
            if (gGlobal->gOneSampleIO) {
                for (int index = 0; index < fContainer->outputs(); index++) {
                    string name = subst("output$0", T(index));
                    pushDeclare(IB::genDecStructVar(name, type));
                }
            } else if (gGlobal->gOneSample) {
                // Nothing...
            } else {
                for (int index = 0; index < fContainer->outputs(); index++) {
                    string name = subst("output$0", T(index));
                    pushComputeBlockMethod(IB::genDecStackVar(
                        name, ptr_type,
                        IB::genLoadArrayFunArgsVar("outputs", IB::genInt32NumInst(index))));
                }
            }
        }
    }

    // These two vars are only used for NNX/Linen
    string return_string = "state, jnp.stack([";
    string sep           = "";

    for (int index = 0; isList(L); L = tl(L), index++) {
        Tree sig = hd(L);

        // Possibly cast to external float
        ValueInst* res = genCastedOutput(getCertifiedSigType(sig)->nature(), CS(sig));

        // HACK for Rust backend
        string name;
        if (gGlobal->gOutputLang == "rust") {
            if (!gGlobal->gInPlace) {
                name = subst("*output$0", T(index));
            } else {
                name = subst("*io$0", T(index));
            }
            if (gGlobal->gComputeMix) {
                // take the cpp code and remove the the loop
                ValueInst* res1 = IB::genAdd(res, IB::genLoadStackVar(name));
                pushComputeDSPMethod(IB::genStoreStackVar(name, res1));
            } else {
                pushComputeDSPMethod(IB::genStoreStackVar(name, res));
            }

        } else if (gGlobal->isPythonBackend()) {
            string result_var = "_result" + to_string(index);
            return_string     = return_string + sep + result_var;
            sep               = ",";
            pushComputeDSPMethod(IB::genStoreStackVar(result_var, res));
        } else if (gGlobal->gOneSampleIO) {
            name = subst("output$0", T(index));
            if (gGlobal->gComputeMix) {
                ValueInst* res1 = IB::genAdd(res, IB::genLoadStackVar(name));
                pushComputeDSPMethod(IB::genStoreStackVar(name, res1));
            } else {
                pushComputeDSPMethod(IB::genStoreStackVar(name, res));
            }
        } else if (gGlobal->gOneSample) {
            name = "outputs";
            if (gGlobal->gComputeMix) {
                ValueInst* res1 =
                    IB::genAdd(res, IB::genLoadArrayStackVar(name, IB::genInt32NumInst(index)));
                pushComputeDSPMethod(
                    IB::genStoreArrayStackVar(name, IB::genInt32NumInst(index), res1));
            } else {
                pushComputeDSPMethod(
                    IB::genStoreArrayStackVar(name, IB::genInt32NumInst(index), res));
            }
        } else {
            name = subst("output$0", T(index));
            if (gGlobal->gComputeMix) {
                ValueInst* res1 =
                    IB::genAdd(res, IB::genLoadArrayStackVar(name, getCurrentLoopIndex()));
                pushComputeDSPMethod(IB::genStoreArrayStackVar(name, getCurrentLoopIndex(), res1));
            } else {
                pushComputeDSPMethod(IB::genStoreArrayStackVar(name, getCurrentLoopIndex(), res));
            }
        }
    }

    if (gGlobal->isPythonBackend()) {
        return_string = return_string + "])";
        pushPostComputeDSPMethod(IB::genRetInst(IB::genLoadStackVar(return_string)));
    }

    Tree ui = fUITree.prepareUserInterfaceTree();
    generateUserInterfaceTree(ui, true);
    generateMacroInterfaceTree("", ui);
    if (fDescription) {
        fDescription->ui(ui);
    }

    // Apply FIR to FIR transformations
    fContainer->processFIR();

    endTiming("compileMultiSignal");
}

/*****************************************************************************
 compileSingleSignal
 *****************************************************************************/

void InstructionsCompiler::compileSingleSignal(Tree sig)
{
    sig         = prepare2(sig);  // Optimize and annotate expression
    string name = fContainer->getTableName();

    pushComputeDSPMethod(IB::genStoreArrayFunArgsVar(name, getCurrentLoopIndex(), CS(sig)));

    Tree ui = fUITree.prepareUserInterfaceTree();
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

    int     i;
    int64_t i64;
    double  r;
    Tree    size, gen, wi, ws, ri, c, sel, x, y, z, label, tb, ff, largs, type, name, file, sf;

    // printf("compilation of %p : ", sig); print(sig); printf("\n");

    if (getUserData(sig)) {
        return generateXtended(sig);
    } else if (isSigInt(sig, &i)) {
        return generateIntNumber(sig, i);
    } else if (isSigInt64(sig, &i64)) {
        return generateInt64Number(sig, i64);
    } else if (isSigReal(sig, &r)) {
        return generateRealNumber(sig, r);
    } else if (isSigWaveform(sig)) {
        return generateWaveform(sig);
    } else if (isSigInput(sig, &i)) {
        return generateInput(sig, i);
    }

    else if (isSigDelay(sig, x, y)) {
        return generateDelayAccess(sig, x, y);
    } else if (isSigPrefix(sig, x, y)) {
        return generatePrefix(sig, x, y);
    } else if (isSigBinOp(sig, &i, x, y)) {
        return generateBinOp(sig, i, x, y);
    } else if (tvec subs; isSigSum(sig, subs)) {
        return generateSum(sig, subs);
    } else if (tvec fs; isSigProd(sig, fs)) {
        return generateProd(sig, fs);
    } else if (tvec fir; isSigFIR(sig, fir)) {
        return generateFIR(sig, fir);
    } else if (tvec iir; isSigIIR(sig, iir)) {
        return generateIIR(sig, iir);
    } else if (Tree ix, ip; isSigIRM(sig, ix, ip)) {
        return generateIRM(sig, ix, ip);
    } else if (isSigBpf(sig)) {
        return generateBpf(sig);
    } else if (isSigNeg(sig, x)) {
        return generateNeg(sig, x);
    } else if (isSigFrac(sig, x)) {
        return generateRemainder(sig, x, gGlobal->gFloorPrim);
    } else if (isSigCfrac(sig, x)) {
        return generateRemainder(sig, x, gGlobal->gRintPrim);
    } else if (isSigTpt(sig, x)) {
        return generateTpt(sig, x);
    } else if (Tree a, p; isSigPhase(sig, a, p)) {
        return generatePhase(sig, a, p);
    } else if (Tree c, a, b; isSigMix(sig, c, a, b)) {
        return generateMix(sig, c, a, b);
    } else if (isSigFFun(sig, ff, largs)) {
        return generateFFun(sig, ff, largs);
    } else if (isSigFConst(sig, type, name, file)) {
        return generateFConst(sig, type, tree2str(file), tree2str(name));
    } else if (isSigFVar(sig, type, name, file)) {
        return generateFVar(sig, type, tree2str(file), tree2str(name));
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
        return generateVSlider(sig, label, c);
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        return generateHSlider(sig, label, c);
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        return generateNumEntry(sig, label, c);
    }

    else if (isSigVBargraph(sig, label, x, y, z)) {
        return generateVBargraph(sig, label, CS(z));
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        return generateHBargraph(sig, label, CS(z));
    }

    else if (isSigSoundfile(sig, label)) {
        return generateSoundfile(sig, label);
    } else if (isSigSoundfileLength(sig, sf, x)) {
        ValueInst* vsf = CS(sf);
        ValueInst* vx  = CS(x);
        return generateCacheCode(sig, generateSoundfileLength(sig, vsf, vx));
    } else if (isSigSoundfileRate(sig, sf, x)) {
        ValueInst* vsf = CS(sf);
        ValueInst* vx  = CS(x);
        return generateCacheCode(sig, generateSoundfileRate(sig, vsf, vx));
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        ValueInst* vsf = CS(sf);
        ValueInst* vx  = CS(x);
        ValueInst* vy  = CS(y);
        ValueInst* vz  = CS(z);
        return generateCacheCode(sig, generateSoundfileBuffer(sig, vsf, vx, vy, vz));
    }

    else if (isSigAttach(sig, x, y)) {
        return generateAttach(sig, x, y);
    } else if (isSigControl(sig, x, y)) {
        return generateControl(sig, x, y);
    } else if (isSigAssertBounds(sig, x, y, z)) {
        /* no debug option for the moment */
        return generateCode(z);
        /* we should not have any control at this stage*/
    } else {
        cerr << "ASSERT : when compiling, unrecognized signal : " << ppsig(sig, MAX_ERROR_SIZE)
             << endl;
        faustassert(false);
    }
    return IB::genNullValueInst();
}

/*****************************************************************************
 NUMBERS
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateIntNumber(Tree sig, int num)
{
    Occurrences* o = fOccMarkup->retrieve(sig);

    // Check for number occuring in delays
    if (o->getMaxDelay() > 0) {
        BasicTyped* ctype;
        string      vname;
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, IB::genInt32NumInst(num), ctype, vname, o->getMaxDelay());
    }

    // No cache for numbers
    return IB::genInt32NumInst(num);
}

ValueInst* InstructionsCompiler::generateInt64Number(Tree sig, int64_t num)
{
    Occurrences* o = fOccMarkup->retrieve(sig);

    // Check for number occuring in delays
    if (o->getMaxDelay() > 0) {
        BasicTyped* ctype;
        string      vname;
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, IB::genInt64NumInst(num), ctype, vname, o->getMaxDelay());
    }

    // No cache for numbers
    return IB::genInt64NumInst(num);
}

ValueInst* InstructionsCompiler::generateRealNumber(Tree sig, double num)
{
    Typed::VarType ctype = itfloat();
    BasicTyped*    btype;
    Occurrences*   o = fOccMarkup->retrieve(sig);

    // Check for number occuring in delays
    if (o->getMaxDelay() > 0) {
        string vname;
        getTypedNames(getCertifiedSigType(sig), "Vec", btype, vname);
        generateDelayVec(sig, IB::genRealNumInst(ctype, num), btype, vname, o->getMaxDelay());
    }

    // No cache for numbers
    return IB::genRealNumInst(ctype, num);
}

/*****************************************************************************
 FOREIGN CONSTANTS
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateFConst(Tree sig, Tree type, const string& file,
                                                const string& name_aux)
{
    fContainer->addIncludeFile(file);

    // Special case for 02/25/19 renaming
    string name = (name_aux == "fSamplingFreq") ? "fSampleRate" : name_aux;

    // Check access (handling "fSampleRate" as a special case)
    if (name != "fSampleRate" && !gGlobal->gAllowForeignConstant) {
        stringstream error;
        error << "ERROR : accessing foreign constant '" << name << "'"
              << " is not allowed in this compilation mode" << endl;
        throw faustexception(error.str());
    }

    // Keep SR generation state
    if (name == "fSampleRate") {
        fContainer->setGeneratedSR();
    }

    // Check for number occuring in delays
    BasicTyped*  ctype;
    string       vname;
    Occurrences* o = fOccMarkup->retrieve(sig);

    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(
            sig, (name == "fSampleRate") ? IB::genLoadStructVar(name) : IB::genLoadGlobalVar(name),
            ctype, vname, o->getMaxDelay());
    }

    // Special case for 'fSampleRate' parameter of the class
    if (name == "fSampleRate") {
        pushDeclare(IB::genDecStructVar(name, genBasicFIRTyped(sig)));
        return IB::genLoadStructVar(name);
    } else {
        pushExtGlobalDeclare(IB::genDecGlobalVar(name, genBasicFIRTyped(sig)));
        return IB::genLoadGlobalVar(name);
    }
}

/*****************************************************************************
 FOREIGN VARIABLES
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateFVar(Tree sig, Tree type, const string& file,
                                              const string& name)
{
    // Check access (handling 'fFullCount' as a special case)
    if ((name != fFullCount && !gGlobal->gAllowForeignVar) ||
        (name == fFullCount && (gGlobal->gOneSample || gGlobal->gExtControl))) {
        stringstream error;
        error << "ERROR : accessing foreign variable '" << name << "'"
              << " is not allowed in this compilation mode" << endl;
        throw faustexception(error.str());
    }

    fContainer->addIncludeFile(file);

    // Special case for 'count' parameter of the 'compute' method
    if (name == fFullCount) {
        return generateCacheCode(sig, IB::genLoadFunArgsVar(name));
    } else {
        pushExtGlobalDeclare(IB::genDecGlobalVar(name, genBasicFIRTyped(sig)));
        return generateCacheCode(sig, IB::genLoadGlobalVar(name));
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
    if (gGlobal->gOutputLang == "rust" && !gGlobal->gInPlace) {
        res = IB::genLoadStackVar(subst("*input$0", T(idx)));
    } else if (gGlobal->gOutputLang == "rust" && gGlobal->gInPlace) {
        res = IB::genLoadStackVar(subst("*io$0", T(idx)));
    } else if (gGlobal->isPythonBackend()) {
        res = IB::genLoadArrayStackVar("inputs", IB::genInt32NumInst(idx));
    } else if (gGlobal->gOneSampleIO) {
        res = IB::genLoadStructVar(subst("input$0", T(idx)));
    } else if (gGlobal->gOneSample) {
        res = IB::genLoadArrayStackVar("inputs", IB::genInt32NumInst(idx));
    } else {
        res = IB::genLoadArrayStackVar(subst("input$0", T(idx)), getCurrentLoopIndex());
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
    if ((opcode == kMul) && isMinusOne(a1)) {
        return IB::genNeg(CS(a2));
    } else if ((opcode == kMul) && isMinusOne(a2)) {
        return IB::genNeg(CS(a1));
    } else {
        // CS compiles a whole subtree : fresh names, declarations, memoisation.
        // Two of them as arguments of one call run in the order the C++ compiler
        // picks for arguments, which GCC and clang pick differently, so the
        // emitted code depended on the compiler that built faust. Sequenced
        // left to right : the order clang used, hence the code emitted so far.
        ValueInst* v1 = CS(a1);
        ValueInst* v2 = CS(a2);
        return generateCacheCode(sig, IB::genBinopInst(opcode, v1, v2));
    }
}

/**
 * Prod(f0, ..., fn) : the chain of the node (emitProd), a slow prefix stored at its rate.
 */
ValueInst* InstructionsCompiler::generateProd(Tree sig, const tvec& factors)
{
    struct Ops {
        InstructionsCompiler* fC;
        bool                  fInt;
        ValueInst*            term(Tree t) { return fC->CS(t); }
        ValueInst*            mul(ValueInst* a, ValueInst* b) { return IB::genBinopInst(kMul, a, b); }
        ValueInst*            store(int variability, ValueInst* a) { return fC->compoundSlowStore(variability, a, fInt); }
    } ops{this, getCertifiedSigType(sig)->nature() == kInt};
    return generateCacheCode(sig, emitProd<ValueInst*>(sig, factors, ops));
}

/**
 * Sum(t0, ..., tn) : the chain of the node (emitSum), a slow prefix stored at its rate.
 */
ValueInst* InstructionsCompiler::generateSum(Tree sig, const tvec& subs)
{
    struct Ops {
        InstructionsCompiler* fC;
        bool                  fInt;
        ValueInst*            term(Tree t) { return fC->CS(t); }
        ValueInst*            negatedTerm(Tree t) { return fC->operandAtRate(t); }
        ValueInst*            add(ValueInst* a, ValueInst* b) { return IB::genBinopInst(kAdd, a, b); }
        ValueInst*            sub(ValueInst* a, ValueInst* b) { return IB::genBinopInst(kSub, a, b); }
        ValueInst*            neg(ValueInst* a) { return IB::genNeg(a); }
        ValueInst*            store(int variability, ValueInst* a) { return fC->compoundSlowStore(variability, a, fInt); }
        ValueInst*            zero()
        {
            return fInt ? static_cast<ValueInst*>(IB::genInt32NumInst(0))
                        : static_cast<ValueInst*>(IB::genRealNumInst(itfloat(), 0.0));
        }
        // acc +/- head * last as faust_fma(+/- head, last, acc), a product nothing else reads
        bool fuse(Tree t, bool positive, ValueInst* acc, ValueInst*& out)
        {
            tvec head;
            Tree last;
            if (fInt || !fusableProduct(t, head, last) || getSharingCount(t, fC->fSharingKey) > 1) {
                return false;
            }
            ValueInst* h;
            if (head.size() == 1) {
                h = fC->CS(head[0]);
            } else {
                struct ProdOps {
                    InstructionsCompiler* fC;
                    ValueInst*            term(Tree f) { return fC->CS(f); }
                    ValueInst*            mul(ValueInst* a, ValueInst* b) { return IB::genBinopInst(kMul, a, b); }
                    ValueInst*            store(int variability, ValueInst* a) { return fC->compoundSlowStore(variability, a, false); }
                } pops{fC};
                h = emitProd<ValueInst*>(t, head, pops);
            }
            if (!positive) h = IB::genNeg(h);
            ValueInst*             l     = fC->CS(last);
            std::vector<Typed::VarType> types = {itfloat(), itfloat(), itfloat()};
            out = fC->fContainer->pushFunction(subst("faust_fma$0", isuffix()), itfloat(), types, {h, l, acc});
            return true;
        }
    } ops{this, getCertifiedSigType(sig)->nature() == kInt};
    return generateCacheCode(sig, emitSum<ValueInst*>(sig, subs, ops));
}

/**
 * neg(x) = -x : a negation instruction, cached as every operation (a slow negation read in
 * a faster context is stored at its rate).
 */
ValueInst* InstructionsCompiler::generateNeg(Tree sig, Tree x)
{
    ValueInst* v = IB::genNeg(CS(x));
    return generateCacheCode(sig, v);
}

/*****************************************************************************
 Compound operations : the node is the operation of FaustAlgebra, its children
 the arguments ; the emitter writes the definition, as for a sum or a FIR.
 *****************************************************************************/

/**
 * x read where the occurrences did not see it (the operand of a neg that a sum, a FIR or an
 * IIR subtracts) : stored at its rate when slower than the sample, as it is otherwise.
 */
ValueInst* InstructionsCompiler::operandAtRate(Tree x)
{
    return (getCertifiedSigType(x)->variability() < kSamp) ? compoundOperand(x) : CS(x);
}

/**
 * An operand that the definition reads twice : a variable or a number as it is, an
 * expression in a variable of its own, placed at the operand's rate.
 */
ValueInst* InstructionsCompiler::compoundOperand(Tree x)
{
    ValueInst* vx = CS(x);
    if (dynamic_cast<LoadVarInst*>(vx) || dynamic_cast<NumValueInst*>(vx)) {
        return vx;
    }
    // the variable becomes the operand's compiled expression : a second read finds it
    return setCompiledExpression(x, generateVariableStore(x, vx));
}

/**
 * lead * t, written as the normal form writes a product : the factors slower than the
 * product (lead included) multiplied first and stored at their own rate, then the
 * others ; the whole stored when slower than its consumer.
 */
ValueInst* InstructionsCompiler::compoundProduct(ValueInst* lead, int vlead, Tree t, int consumer)
{
    std::vector<Tree>         factors;
    std::function<void(Tree)> flatten = [&](Tree u) {
        Tree x, y;
        tvec fs;
        if (isSigMul(u, x, y)) {
            flatten(x);
            flatten(y);
        } else if (isSigProd(u, fs)) {
            for (Tree f : fs) flatten(f);
        } else {
            factors.push_back(u);
        }
    };
    flatten(t);
    const int  vprod = std::max(vlead, getCertifiedSigType(t)->variability());
    ValueInst* slow     = nullptr;
    ValueInst* fast     = nullptr;
    int        vslow    = kKonst;
    bool       computed = false;  // the slow part is an operation, not a variable
    auto       join     = [](ValueInst* acc, ValueInst* f) {
        return acc ? IB::genBinopInst(kMul, acc, f) : f;
    };
    if (vlead < vprod) {
        slow     = lead;
        vslow    = vlead;
        computed = !(dynamic_cast<LoadVarInst*>(lead) || dynamic_cast<NumValueInst*>(lead));
    } else {
        fast = lead;
    }
    for (Tree f : factors) {
        const int  vf = getCertifiedSigType(f)->variability();
        ValueInst* cf = CS(f);
        if (vf < vprod) {
            computed = computed || slow != nullptr;
            slow     = join(slow, cf);
            vslow    = std::max(vslow, vf);
        } else {
            fast = join(fast, cf);
        }
    }
    if (computed && fast && vslow < kSamp) {
        slow = compoundSlowStore(vslow, slow);
    }
    ValueInst* r = fast ? join(slow, fast) : slow;
    return (vprod < consumer && vprod < kSamp) ? compoundSlowStore(vprod, r) : r;
}

/**
 * A part of a definition slower than its consumer, stored at its own rate : a constant
 * in the instance, a slow value at the block (what a slow node in a faster context is).
 */
ValueInst* InstructionsCompiler::compoundSlowStore(int variability, ValueInst* exp, bool isInt)
{
    faustassert(variability == kKonst || variability == kBlock);
    BasicTyped* ctype = IB::genBasicTyped(isInt ? Typed::kInt32 : itfloat());
    if (variability == kKonst) {
        string vname = subst("f$0", gGlobal->getFreshID("Const"));
        pushDeclare(IB::genDecStructVar(vname, ctype));
        pushInitMethod(IB::genStoreStructVar(vname, exp));
        return IB::genLoadStructVar(vname);
    }
    string vname = subst("f$0", gGlobal->getFreshID("Slow"));
    if (gGlobal->gExtControl) {
        if (gGlobal->gMemoryManager >= 1) {
            if (isInt) {
                pushControlDeclare(fContainer->fIntControl->store(exp));
                return fContainer->fIntControl->load();
            }
            pushControlDeclare(fContainer->fRealControl->store(exp));
            return fContainer->fRealControl->load();
        }
        pushDeclare(IB::genDecStructVar(vname, ctype));
        pushControlDeclare(IB::genStoreStructVar(vname, exp));
        return IB::genLoadStructVar(vname);
    }
    pushComputeBlockMethod(IB::genDecStackVar(vname, ctype, exp));
    return IB::genLoadStackVar(vname);
}

/**
 * frac(x) = x - floor(x), cfrac(x) = x - rint(x) : x computed once, the rounding by its
 * primitive, then the subtraction.
 */
ValueInst* InstructionsCompiler::generateRemainder(Tree sig, Tree x, xtended* round)
{
    // the program's own rounding of x, when it holds one
    Tree held = (round == gGlobal->gFloorPrim) ? fDefinitions.floorOf(x) : fDefinitions.rintOf(x);
    if (held != nullptr) {
        ValueInst* hx = compoundOperand(x);
        ValueInst* hr = compoundOperand(held);
        return generateCacheCode(sig, IB::genBinopInst(kSub, hx, hr));
    }
    ValueInst*     vx = compoundOperand(x);
    Values         args{vx};
    vector<::Type> types{getCertifiedSigType(x)};
    ValueInst*     r = static_cast<xtendedCodegen*>(round)->generateCode(fContainer, args,
                                                                         getCertifiedSigType(sig), types);
    return generateCacheCode(sig, IB::genBinopInst(kSub, vx, r));
}

/**
 * tpt(x) = x / (x + 1) : x computed once.
 */
ValueInst* InstructionsCompiler::generateTpt(Tree sig, Tree x)
{
    ValueInst* vx   = compoundOperand(x);
    Tree       held = fDefinitions.plusOneOf(x);  // the program's own x + 1
    ValueInst* d    = held ? compoundOperand(held)
                           : IB::genBinopInst(kAdd, vx, IB::genRealNumInst(itfloat(), 1.0));
    return generateCacheCode(sig, IB::genBinopInst(kDiv, vx, d));
}

/**
 * phase(x, p) = (x % p) / p : the program's own remainder when it holds one (the
 * definition of a counter, ba.period), read from its variable ; the division is real, a
 * product by 1/p when phaseByReciprocal says so.
 */
ValueInst* InstructionsCompiler::generatePhase(Tree sig, Tree x, Tree p)
{
    const bool isInt = getCertifiedSigType(x)->nature() == kInt && getCertifiedSigType(p)->nature() == kInt;
    ValueInst* vp    = compoundOperand(p);
    ValueInst* vr;
    if (Tree held = fDefinitions.remOf(x, p)) {
        vr = compoundOperand(held);
    } else if (isInt) {
        vr = IB::genBinopInst(kRem, compoundOperand(x), vp);
    } else {
        Values         args{compoundOperand(x), vp};
        vector<::Type> types{getCertifiedSigType(x), getCertifiedSigType(p)};
        vr = static_cast<xtendedCodegen*>(gGlobal->gFmodPrim)->generateCode(fContainer, args,
                                                                            getCertifiedSigType(x), types);
    }
    if (isInt) {
        BasicTyped* ft = genFloatType(getCertifiedSigType(sig));
        vr             = IB::genCastInst(vr, ft);
        vp             = IB::genCastInst(vp, ft);
        if (phaseByReciprocal(p)) {
            ValueInst* one = IB::genRealNumInst(itfloat(), 1.0);
            ValueInst* inv = compoundSlowStore(getCertifiedSigType(p)->variability(),
                                               IB::genBinopInst(kDiv, one, vp));
            // the product in a variable : the text printers write a product nested on the
            // right without parentheses (k * r * inv is (k * r) * inv in C) ; stored, the
            // phase is r * inv whatever multiplies it
            ValueInst* ph = IB::genBinopInst(kMul, vr, inv);
            return setCompiledExpression(sig, generateVariableStore(sig, ph));
        }
    }
    return generateCacheCode(sig, IB::genBinopInst(kDiv, vr, vp));
}

/**
 * mix(c, a, b) = (1 - c) * a + c * b, computed as an interpolation from the operand whose
 * weight may be near 1 (itv::mixFromB, on the interval of c) : b + (1 - c) * (a - b) when
 * c >= 1/2, 1 - c being then exact, a + c * (b - a) otherwise. Either keeps its fixed point
 * exactly, and costs about one rounding of the result when the weight of the difference is
 * small (a slow smoother) ; the interval of the node bounds this same computation.
 */
ValueInst* InstructionsCompiler::generateMix(Tree sig, Tree c, Tree a, Tree b)
{
    ValueInst* va = compoundOperand(a);
    ValueInst* vb = compoundOperand(b);
    // c written 1 - t : b + t * (a - b), 1 - t never computed (mixForm.hh)
    if (Tree t; mixFromWeight(c, getCertifiedSigType(c)->getInterval(), t)) {
        ValueInst* vt = compoundOperand(t);
        ValueInst* d  = IB::genBinopInst(kSub, va, vb);
        if (fmaWanted(sig)) return generateCacheCode(sig, genFma(vt, d, vb));
        ValueInst* p  = IB::genBinopInst(kMul, vt, d);
        return generateCacheCode(sig, IB::genBinopInst(kAdd, vb, p));
    }
    ValueInst* vc = compoundOperand(c);
    if (itv::mixFromB(getCertifiedSigType(c)->getInterval())) {
        const int  vrc = getCertifiedSigType(c)->variability();
        ValueInst* w   = IB::genBinopInst(kSub, IB::genRealNumInst(itfloat(), 1.0), vc);
        if (vrc < getCertifiedSigType(sig)->variability() && vrc != kSamp) {
            w = compoundSlowStore(vrc, w);  // 1 - c at the rate of c
        }
        ValueInst* d = IB::genBinopInst(kSub, va, vb);
        if (fmaWanted(sig)) return generateCacheCode(sig, genFma(w, d, vb));
        ValueInst* p = IB::genBinopInst(kMul, w, d);
        return generateCacheCode(sig, IB::genBinopInst(kAdd, vb, p));
    }
    ValueInst* d = IB::genBinopInst(kSub, vb, va);
    if (fmaWanted(sig)) return generateCacheCode(sig, genFma(vc, d, va));
    ValueInst* p = IB::genBinopInst(kMul, vc, d);
    return generateCacheCode(sig, IB::genBinopInst(kAdd, va, p));
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
        Names  args_types;

        int len = ffarity(ff) - 1;
        for (int i = 0; i < ffarity(ff); i++) {
            // Reversed...
            BasicTyped* argtype = genBasicFIRTyped(ffargtype(ff, len - i));
            args_types.push_back(IB::genNamedTyped("dummy" + to_string(i), argtype));
            args_value.push_back(CS(nth(largs, i)));
        }

        // Add function declaration
        FunTyped* fun_type = IB::genFunTyped(args_types, genBasicFIRTyped(ffrestype(ff)));
        pushExtGlobalDeclare(IB::genDeclareFunInst(funname, fun_type));

        // For the NNX/Linen backends, skip caching for random_* functions to ensure independent
        // streams Each call should generate fresh random values, not reuse cached results
        bool is_random_ffun = gGlobal->isPythonBackend() && isNNXRandomFunction(funname);

        if (is_random_ffun) {
            // Don't cache - each call should be independent
            return IB::genFunCallInst(funname, args_value);
        } else {
            // Normal caching behavior for other functions
            return generateCacheCode(sig, IB::genFunCallInst(funname, args_value));
        }
    } else {
        stringstream error;
        error << "ERROR : calling foreign function '" << funname << "'"
              << " is not allowed in this compilation mode" << endl;
        throw faustexception(error.str());
    }
}

/*****************************************************************************
 CACHE CODE
 *****************************************************************************/

void InstructionsCompiler::getTypedNames(::Type t, const string& prefix, Typed::VarType& ctype,
                                         string& vname)
{
    if (t->nature() == kInt) {
        ctype = Typed::kInt32;
        vname = subst("i$0", gGlobal->getFreshID(prefix));
    } else {
        ctype = itfloat();
        vname = subst("f$0", gGlobal->getFreshID(prefix));
    }
}

void InstructionsCompiler::getTypedNames(::Type t, const string& prefix, BasicTyped*& ctype,
                                         string& vname)
{
    if (t->nature() == kInt) {
        ctype = IB::genBasicTyped(Typed::kInt32);
        vname = subst("i$0", gGlobal->getFreshID(prefix));
    } else {
        ctype = genFloatType(t);
        vname = subst("f$0", gGlobal->getFreshID(prefix));
    }
}

ValueInst* InstructionsCompiler::generateCacheCode(Tree sig, ValueInst* exp)
{
    // Check reentrance
    ValueInst* code;
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    string       vname;
    BasicTyped*  ctype;
    int          sharing = getSharingCount(sig, fSharingKey);
    Occurrences* o       = fOccMarkup->retrieve(sig);
    faustassert(o);

    // Check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        string existing;
        if (getVectorNameProperty(sig, existing)) {
            // The line was pre-allocated by a deferred delay access
            // (decoupled write, see generateDelayAccess) : reuse its name,
            // the computation and the write are emitted now.
            ::Type t = getCertifiedSigType(sig);
            ctype    = (t->nature() == kInt) ? IB::genBasicTyped(Typed::kInt32) : genFloatType(t);
            if (sharing > 1) {
                return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, existing,
                                        o->getMaxDelay());
            } else {
                return generateDelayVec(sig, exp, ctype, existing, o->getMaxDelay());
            }
        }
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        if (sharing > 1) {
            return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname,
                                    o->getMaxDelay());
        } else {
            return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
        }

    } else if (sharing > 1 || (o->hasMultiOccurrences())) {
        return generateVariableStore(sig, exp);

    } else if (sharing == 1) {
        return exp;

    } else {
        cerr << "ASSERT : in sharing count (" << sharing << ") for " << *sig << endl;
        faustassert(false);
        return IB::genNullValueInst();
    }
}

// Like generateCacheCode but we force caching like if sharing was always > 1
ValueInst* InstructionsCompiler::forceCacheCode(Tree sig, ValueInst* exp)
{
    // check reentrance
    ValueInst* code;
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    string       vname;
    BasicTyped*  ctype;
    Occurrences* o = fOccMarkup->retrieve(sig);
    faustassert(o);

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname,
                                o->getMaxDelay());
    } else {
        return generateVariableStore(sig, exp);
    }
}

// Definition of variables: Const (computed at init time), Slow (computed at control rate) and
// "Temp" (computed at sample rate)
ValueInst* InstructionsCompiler::generateVariableStore(Tree sig, ValueInst* exp)
{
    string       vname, vname_perm;
    BasicTyped*  ctype;
    ::Type       t = getCertifiedSigType(sig);
    Occurrences* o = fOccMarkup->retrieve(sig);
    faustassert(o);

    switch (t->variability()) {
        case kKonst:
            getTypedNames(t, "Const", ctype, vname);

            /* TODO: deactivated for now since getOccurrence fails in some cases
            // The variable is used in compute (kBlock or kSamp), so define is as a field in the DSP
            struct if (o->getOccurrence(kBlock) || o->getOccurrence(kSamp)) {
                pushDeclare(IB::genDecStructVar(vname, ctype));
                pushInitMethod(IB::genStoreStructVar(vname, exp));
                return IB::genLoadStructVar(vname);
            } else {
                // Otherwise it can stay as a local variable
                pushInitMethod(IB::genDecStackVar(vname, ctype, exp));
                return IB::genLoadStackVar(vname);
            }
            */

            // Always put variables in DSP struct for now
            pushDeclare(IB::genDecStructVar(vname, ctype));
            pushInitMethod(IB::genStoreStructVar(vname, exp));
            return IB::genLoadStructVar(vname);

        case kBlock: {
            getTypedNames(t, "Slow", ctype, vname);

            if (gGlobal->gExtControl) {
                if (gGlobal->gMemoryManager >= 1) {
                    // "Slow" variables are grouped in a single iControl/fControl
                    // array in the DSP struct
                    if (t->nature() == kInt) {
                        pushControlDeclare(fContainer->fIntControl->store(exp));
                        return fContainer->fIntControl->load();
                    } else {
                        pushControlDeclare(fContainer->fRealControl->store(exp));
                        return fContainer->fRealControl->load();
                    }
                } else {
                    // "Slow" variables are moved in the DSP struct
                    pushDeclare(IB::genDecStructVar(vname, ctype));
                    pushControlDeclare(IB::genStoreStructVar(vname, exp));
                    return IB::genLoadStructVar(vname);
                }
            } else {
                // "Slow" variables are declared as locals in 'frame' or 'compute' functions
                pushComputeBlockMethod(IB::genDecStackVar(vname, ctype, exp));
                return IB::genLoadStackVar(vname);
            }
        }

        case kSamp:
            getTypedNames(t, "Temp", ctype, vname);
            // Only generated for the DSP loop
            if (gGlobal->gHasTeeLocal) {
                if (dynamic_cast<NullValueInst*>(getConditionCode(sig))) {
                    pushComputeDSPMethod(IB::genDecStackVar(vname, ctype));
                } else {
                    getTypedNames(t, "TempPerm", ctype, vname_perm);
                    pushDeclare(IB::genDecStructVar(vname_perm, ctype));
                    pushClearMethod(IB::genStoreStructVar(vname_perm, IB::genTypedZero(ctype)));

                    pushComputeBlockMethod(
                        IB::genDecStackVar(vname, ctype, IB::genLoadStructVar(vname_perm)));
                    pushPostComputeBlockMethod(
                        IB::genStoreStructVar(vname_perm, IB::genLoadStackVar(vname)));
                }
                return IB::genTeeVar(vname, exp);

            } else {
                if (dynamic_cast<NullValueInst*>(getConditionCode(sig))) {
                    // "Temp" variables are declared as locals in 'frame' or 'compute'
                    pushComputeDSPMethod(IB::genDecStackVar(vname, ctype, exp));
                    return IB::genLoadStackVar(vname);
                } else {
                    getTypedNames(t, "TempPerm", ctype, vname_perm);
                    // need to be preserved because of new enable and control primitives
                    pushDeclare(IB::genDecStructVar(vname_perm, ctype));
                    pushClearMethod(IB::genStoreStructVar(vname_perm, IB::genTypedZero(ctype)));

                    if (gGlobal->gExtControl) {
                        pushComputeDSPMethod(IB::genControlInst(
                            getConditionCode(sig), IB::genStoreStructVar(vname_perm, exp)));
                        return IB::genLoadStructVar(vname_perm);
                    } else {
                        // copy the object variable to the local one
                        pushComputeBlockMethod(
                            IB::genDecStackVar(vname, ctype, IB::genLoadStructVar(vname_perm)));
                        // execute the code
                        pushComputeDSPMethod(IB::genControlInst(getConditionCode(sig),
                                                                IB::genStoreStackVar(vname, exp)));
                        // copy the local variable to the object one
                        pushPostComputeBlockMethod(
                            IB::genStoreStructVar(vname_perm, IB::genLoadStackVar(vname)));
                        return IB::genLoadStackVar(vname);
                    }
                }
            }

        default:
            cerr << "ASSERT : incorrect variability\n";
            faustassert(false);
            return IB::genNullValueInst();
    }
}

/*****************************************************************************
 CASTING
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateIntCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, IB::genCastInt32Inst(CS(x)));
}

ValueInst* InstructionsCompiler::generateBitCast(Tree sig, Tree x)
{
    // Used in -ftz (1/2) mode to bitcast real (float/double) to integer (32 bits/64 bits)
    BasicTyped* type = (gGlobal->gFloatSize == 2) ? IB::genInt64Typed() : IB::genInt32Typed();
    return generateCacheCode(sig, IB::genBitcastInst(CS(x), type));
}

ValueInst* InstructionsCompiler::generateFloatCast(Tree sig, Tree x)
{
    ValueInst*  vx = CS(x);
    BasicTyped* ft = genFloatType(getCertifiedSigType(sig));
    return generateCacheCode(sig, IB::genCastInst(vx, ft));
}

/*****************************************************************************
 User interface elements
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateButtonAux(Tree sig, Tree path, const string& name)
{
    string varname = gGlobal->getFreshID(name);
    Typed* type    = IB::genFloatMacroTyped();

    pushDeclare(IB::genDecStructVar(varname, type));
    pushResetUIInstructions(
        IB::genStoreStructVar(varname, IB::genRealNumInst(Typed::kFloatMacro, 0)));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    // Cast to internal float
    return generateCacheCode(sig, genCastedInput(IB::genLoadStructVar(varname)));
}

ValueInst* InstructionsCompiler::generateButton(Tree sig, Tree path)
{
    return generateButtonAux(sig, path, "fButton");
}

ValueInst* InstructionsCompiler::generateCheckbox(Tree sig, Tree path)
{
    return generateButtonAux(sig, path, "fCheckbox");
}

ValueInst* InstructionsCompiler::generateSliderAux(Tree sig, Tree path, Tree cur,
                                                   const string& name)
{
    string varname = gGlobal->getFreshID(name);
    Typed* type    = IB::genFloatMacroTyped();

    pushDeclare(IB::genDecStructVar(varname, type));
    pushResetUIInstructions(
        IB::genStoreStructVar(varname, IB::genRealNumInst(Typed::kFloatMacro, tree2double(cur))));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    // Cast to internal float
    return generateCacheCode(sig, genCastedInput(IB::genLoadStructVar(varname)));
}

ValueInst* InstructionsCompiler::generateVSlider(Tree sig, Tree path, Tree cur)
{
    return generateSliderAux(sig, path, cur, "fVslider");
}
ValueInst* InstructionsCompiler::generateHSlider(Tree sig, Tree path, Tree cur)
{
    return generateSliderAux(sig, path, cur, "fHslider");
}

ValueInst* InstructionsCompiler::generateNumEntry(Tree sig, Tree path, Tree cur)
{
    return generateSliderAux(sig, path, cur, "fEntry");
}

ValueInst* InstructionsCompiler::generateBargraphAux(Tree sig, Tree path, ValueInst* exp,
                                                     const string& name)
{
    string varname = gGlobal->getFreshID(name);
    pushDeclare(IB::genDecStructVar(varname, IB::genFloatMacroTyped()));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    ::Type t = getCertifiedSigType(sig);

    // Cast to external float
    StoreVarInst* res = IB::genStoreStructVar(varname, genCastedOutput(exp));

    switch (t->variability()) {
        case kKonst:
            pushResetUIInstructions(res);
            break;

        case kBlock: {
            if (gGlobal->gExtControl) {
                pushControlDeclare(res);
            } else {
                pushComputeBlockMethod(res);
            }
            break;
        }

        case kSamp:
            pushComputeDSPMethod(IB::genControlInst(getConditionCode(sig), res));
            break;
    }

    return generateCacheCode(sig, genCastedInput(IB::genLoadStructVar(varname)));
}

ValueInst* InstructionsCompiler::generateVBargraph(Tree sig, Tree path, ValueInst* exp)
{
    return generateBargraphAux(sig, path, exp, "fVbargraph");
}

ValueInst* InstructionsCompiler::generateHBargraph(Tree sig, Tree path, ValueInst* exp)
{
    return generateBargraphAux(sig, path, exp, "fHbargraph");
}

/*****************************************************************************
 Soundfile
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateSoundfile(Tree sig, Tree path)
{
    string varname = gGlobal->getFreshID("fSoundfile");
    string SFcache = varname + "ca";

    Tree uipath   = reverse(tl(path));

    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);

    fUITree.addUIWidget(uipath, uiwidget);

    pushDeclare(IB::genDecStructVar(varname, Typed::kSound_ptr));

    if (gGlobal->gUseDefaultSound) {
        BlockInst* block = IB::genBlockInst();
        block->pushBackInst(IB::genStoreStructVar(varname, IB::genLoadGlobalVar("defaultsound")));

        pushAllocateMethod(IB::genStoreStructVar(varname, IB::genTypedZero(Typed::kSound_ptr)));

        pushResetUIInstructions(IB::genIfInst(
            IB::genEqual(
                IB::genCastInst(IB::genLoadStructVar(varname), IB::genBasicTyped(Typed::kUint_ptr)),
                IB::genTypedZero(Typed::kSound_ptr)),
            block, IB::genBlockInst()));
    }

    if (gGlobal->gExtControl) {
        pushDeclare(IB::genDecStructVar(SFcache, Typed::kSound_ptr));
        pushControlDeclare(IB::genStoreStructVar(SFcache, IB::genLoadStructVar(varname)));
        pushPostComputeBlockMethod(IB::genStoreStructVar(varname, IB::genLoadStructVar(SFcache)));
    } else {
        pushComputeBlockMethod(
            IB::genDecStackVar(SFcache, Typed::kSound_ptr, IB::genLoadStructVar(varname)));
        pushPostComputeBlockMethod(IB::genStoreStructVar(varname, IB::genLoadStackVar(SFcache)));
    }

    return IB::genLoadStructVar(varname);
}

ValueInst* InstructionsCompiler::generateSoundfileLength(Tree sig, ValueInst* sf, ValueInst* x)
{
    LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
    faustassert(load);

    Typed* type = IB::genBasicTyped(Typed::kInt32_ptr);

    string SFcache        = load->fAddress->getName() + "ca";
    string SFcache_length = gGlobal->getFreshID(SFcache + "_le");

    if (gGlobal->gExtControl) {
        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = IB::genLoadStructPtrVar(SFcache, Address::kStruct,
                                                IB::genInt32NumInst(Soundfile::kLength));

        pushDeclare(IB::genDecStructVar(SFcache_length, type));
        pushControlDeclare(IB::genStoreStructVar(SFcache_length, v1));
        return IB::genLoadArrayStructVar(SFcache_length, x);
    } else {
        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = IB::genLoadStructPtrVar(SFcache, Address::kStack,
                                                IB::genInt32NumInst(Soundfile::kLength));

        pushComputeBlockMethod(IB::genDecStackVar(SFcache_length, type, v1));
        return IB::genLoadArrayStackVar(SFcache_length, x);
    }
}

ValueInst* InstructionsCompiler::generateSoundfileRate(Tree sig, ValueInst* sf, ValueInst* x)
{
    LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
    faustassert(load);

    Typed* type = IB::genBasicTyped(Typed::kInt32_ptr);

    string SFcache      = load->fAddress->getName() + "ca";
    string SFcache_rate = gGlobal->getFreshID(SFcache + "_ra");

    if (gGlobal->gExtControl) {
        // Struct access using an index that will be converted as a field name
        ValueInst* v1 =
            IB::genLoadStructPtrVar(SFcache, Address::kStruct, IB::genInt32NumInst(Soundfile::kSR));

        pushDeclare(IB::genDecStructVar(SFcache_rate, type));
        pushControlDeclare(IB::genStoreStructVar(SFcache_rate, v1));
        return IB::genLoadArrayStructVar(SFcache_rate, x);
    } else {
        // Struct access using an index that will be converted as a field name
        ValueInst* v1 =
            IB::genLoadStructPtrVar(SFcache, Address::kStack, IB::genInt32NumInst(Soundfile::kSR));

        pushComputeBlockMethod(IB::genDecStackVar(SFcache_rate, type, v1));
        return IB::genLoadArrayStackVar(SFcache_rate, x);
    }
}

ValueInst* InstructionsCompiler::generateSoundfileBuffer(Tree sig, ValueInst* sf, ValueInst* x,
                                                         ValueInst* y, ValueInst* z)
{
    LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
    faustassert(load);

    Typed* type1 = IB::genBasicTyped(itfloatptrptr());
    Typed* type2 = IB::genItFloatTyped();
    Typed* type3 = IB::genBasicTyped(Typed::kInt32_ptr);

    string SFcache             = load->fAddress->getName() + "ca";
    string SFcache_buffer      = gGlobal->getFreshID(SFcache + "_bu");
    string SFcache_buffer_chan = gGlobal->getFreshID(SFcache + "_bu_ch");
    string SFcache_offset      = gGlobal->getFreshID(SFcache + "_of");

    /*
     The requested channel 'x' can be higher than the real number of channels of the soundfile
     (for instance a stereo file read with soundfile(label, 4)): the real channels are then
     duplicated by reading channel 'x % fChannels'. The runtime has to set fChannels >= 1 and
     to provide fChannels buffers. The channel is computed once per block, with the buffer.
    */
    auto wrapChannel = [&](Address::AccessType access) -> ValueInst* {
        // Channel 0 always exists
        Int32NumInst* chan = dynamic_cast<Int32NumInst*>(x);
        if (chan && chan->fNum == 0) {
            return x;
        }
        return IB::genRem(
            x, IB::genLoadStructPtrVar(SFcache, access, IB::genInt32NumInst(Soundfile::kChannels)));
    };

    if (gGlobal->gExtControl) {
        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = IB::genLoadStructPtrVar(SFcache, Address::kStruct,
                                                IB::genInt32NumInst(Soundfile::kOffset));

        pushDeclare(IB::genDecStructVar(SFcache_offset, type3));
        pushControlDeclare(IB::genStoreStructVar(SFcache_offset, v1));

        // Struct access using an index that will be converted as a field name
        LoadVarInst* load1 = IB::genLoadStructPtrVar(SFcache, Address::kStruct,
                                                     IB::genInt32NumInst(Soundfile::kBuffers));

        pushDeclare(IB::genDecStructVar(SFcache_buffer, type1));
        // SFcache_buffer type is void* and has to be casted in the runtime buffer type
        pushControlDeclare(IB::genStoreStructVar(SFcache_buffer, IB::genCastInst(load1, type1)));

        pushDeclare(IB::genDecStructVar(SFcache_buffer_chan, IB::genArrayTyped(type2, 0)));
        pushControlDeclare(IB::genStoreStructVar(
            SFcache_buffer_chan, IB::genLoadStructPtrVar(SFcache_buffer, Address::kStruct,
                                                         wrapChannel(Address::kStruct))));

        return IB::genLoadStructPtrVar(SFcache_buffer_chan, Address::kStruct,
                                       IB::genAdd(IB::genLoadArrayStructVar(SFcache_offset, y), z));
    } else {
        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = IB::genLoadStructPtrVar(SFcache, Address::kStack,
                                                IB::genInt32NumInst(Soundfile::kOffset));

        pushComputeBlockMethod(IB::genDecStackVar(SFcache_offset, type3, v1));

        // Struct access using an index that will be converted as a field name
        LoadVarInst* load1 = IB::genLoadStructPtrVar(SFcache, Address::kStack,
                                                     IB::genInt32NumInst(Soundfile::kBuffers));

        // SFcache_buffer type is void* and has to be casted in the runtime buffer type
        pushComputeBlockMethod(
            IB::genDecStackVar(SFcache_buffer, type1, IB::genCastInst(load1, type1)));
        pushComputeBlockMethod(
            IB::genDecStackVar(SFcache_buffer_chan, IB::genArrayTyped(type2, 0),
                               IB::genLoadStructPtrVar(SFcache_buffer, Address::kStack,
                                                       wrapChannel(Address::kStack))));
        return IB::genLoadStructPtrVar(SFcache_buffer_chan, Address::kStack,
                                       IB::genAdd(IB::genLoadArrayStackVar(SFcache_offset, y), z));
    }
}

ValueInst* InstructionsCompiler::generateAttach(Tree sig, Tree x, Tree y)
{
    CS(y);
    return generateCacheCode(sig, CS(x));
}
/*****************************************************************************
 TABLES
 *****************************************************************************/

/*----------------------------------------------------------------------------
 sigGen : initial table content
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateSigGen(Tree sig, Tree content)
{
    string cname   = gGlobal->getFreshID(fContainer->getClassName() + "SIG");
    string signame = gGlobal->getFreshID("sig");

    CodeContainer* subcontainer = signal2Container(cname, content);
    // Remember the element type the table will be declared with, so the
    // generated fill function agrees with it. genFloatType is virtual and
    // returns the interval-derived fixed type in fixed-point mode.
    ::Type content_type = getCertifiedSigType(content);
    if (content_type->nature() != kInt) {
        subcontainer->setTableElemType(genFloatType(content_type));
    }
    fContainer->addSubContainer(subcontainer);

    // We must allocate an object of type "cname"
    Values args;
    if (gGlobal->gMemoryManager >= 0) {
        args.push_back(IB::genLoadStaticStructVar("fManager"));
    }
    ValueInst* obj = IB::genFunCallInst("new" + cname, args);
    pushInitMethod(IB::genDecStackVar(
        signame, IB::genNamedTyped(cname, IB::genBasicTyped(Typed::kObj_ptr)), obj));

    // HACK for Rust, Julia and AssemblyScript backends
    if (gGlobal->gOutputLang != "rust" && gGlobal->gOutputLang != "julia" &&
        gGlobal->gOutputLang != "asc") {
        // Delete object
        Values args3;
        args3.push_back(IB::genLoadStackVar(signame));
        if (gGlobal->gMemoryManager >= 0) {
            args3.push_back(IB::genLoadStaticStructVar("fManager"));
        }
        pushPostInitMethod(IB::genVoidFunCallInst("delete" + cname, args3));
    }

    setTableNameProperty(sig, cname);
    fInstanceInitProperty.set(content, pair<string, string>(cname, signame));

    return IB::genLoadStackVar(signame);
}

ValueInst* InstructionsCompiler::generateStaticSigGen(Tree sig, Tree content)
{
    string cname   = gGlobal->getFreshID(fContainer->getClassName() + "SIG");
    string signame = gGlobal->getFreshID("sig");

    CodeContainer* subcontainer = signal2Container(cname, content);
    // Remember the element type the table will be declared with, so the
    // generated fill function agrees with it. genFloatType is virtual and
    // returns the interval-derived fixed type in fixed-point mode.
    ::Type content_type = getCertifiedSigType(content);
    if (content_type->nature() != kInt) {
        subcontainer->setTableElemType(genFloatType(content_type));
    }
    fContainer->addSubContainer(subcontainer);

    // We must allocate an object of type "cname"
    Values args;
    if (gGlobal->gMemoryManager >= 0) {
        args.push_back(IB::genLoadStaticStructVar("fManager"));
    }
    ValueInst* obj = IB::genFunCallInst("new" + cname, args);
    pushStaticInitMethod(IB::genDecStackVar(
        signame, IB::genNamedTyped(cname, IB::genBasicTyped(Typed::kObj_ptr)), obj));

    // HACK for Rust, Julia and AssemblyScript backends
    if (gGlobal->gOutputLang != "rust" && gGlobal->gOutputLang != "julia" &&
        gGlobal->gOutputLang != "asc") {
        // Delete object
        Values args3;
        args3.push_back(IB::genLoadStackVar(signame));
        if (gGlobal->gMemoryManager >= 0) {
            args3.push_back(IB::genLoadStaticStructVar("fManager"));
        }
        pushPostStaticInitMethod(IB::genVoidFunCallInst("delete" + cname, args3));
    }

    setTableNameProperty(sig, cname);
    fStaticInitProperty.set(content, pair<string, string>(cname, signame));

    return IB::genLoadStackVar(signame);
}

/*----------------------------------------------------------------------------
 sigTable : table declaration
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateTable(Tree sig, Tree tsize, Tree content)
{
    int  size;
    bool res = isSigInt(tsize, &size);
    // Size type is previously checked in sigWriteReadTable or sigReadOnlyTable
    faustassert(res);

    ValueInst*  signame = CS(content);
    BasicTyped* ctype;
    Tree        g;
    string      vname;

    // Already compiled but check if we need to add declarations
    faustassert(isSigGen(content, g));

    pair<string, string> kvnames;
    if (!fInstanceInitProperty.get(g, kvnames)) {
        // Not declared here, we add a declaration
        bool b = fStaticInitProperty.get(g, kvnames);
        faustassert(b);
        Values args;
        if (gGlobal->gMemoryManager >= 0) {
            args.push_back(IB::genLoadStaticStructVar("fManager"));
        }
        ValueInst* obj = IB::genFunCallInst("new" + kvnames.first, args);
        pushInitMethod(IB::genDecStackVar(
            kvnames.second, IB::genNamedTyped(kvnames.first, IB::genBasicTyped(Typed::kObj_ptr)),
            obj));

        // HACK for Rust, Julia and AssemblyScript backends
        if (gGlobal->gOutputLang != "rust" && gGlobal->gOutputLang != "julia" &&
            gGlobal->gOutputLang != "asc") {
            // Delete object
            Values args3;
            args3.push_back(signame);
            if (gGlobal->gMemoryManager >= 0) {
                args3.push_back(IB::genLoadStaticStructVar("fManager"));
            }
            pushPostInitMethod(IB::genVoidFunCallInst("delete" + kvnames.first, args3));
        }
    }

    // Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    // Table declaration
    pushDeclare(IB::genDecStructVar(vname, IB::genArrayTyped(ctype, size)));

    string tablename;
    getTableNameProperty(content, tablename);

    // Init content generator
    Values args1;
    args1.push_back(signame);
    args1.push_back(IB::genLoadFunArgsVar("sample_rate"));
    pushInitMethod(IB::genVoidFunCallInst("instanceInit" + tablename, args1, true));

    // Fill the table
    Values args2;
    args2.push_back(signame);
    args2.push_back(IB::genInt32NumInst(size));
    // HACK for Rust backend
    if (gGlobal->gInlineTable) {
        args2.push_back(IB::genLoadStructVar(vname));
    } else {
        args2.push_back(IB::genLoadMutRefStructVar(vname));
    }
    pushInitMethod(IB::genVoidFunCallInst("fill" + tablename, args2, true));

    // Return table access
    return IB::genLoadStructVar(vname);
}

ValueInst* InstructionsCompiler::generateStaticTable(Tree sig, Tree tsize, Tree content)
{
    int  size;
    bool res = isSigInt(tsize, &size);
    // Size type is previously checked in sigWriteReadTable or sigReadOnlyTable
    faustassert(res);

    Tree        g;
    ValueInst*  signame;
    BasicTyped* ctype;
    string      vname;

    faustassert(isSigGen(content, g));

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
            if (gGlobal->gMemoryManager >= 0) {
                args.push_back(IB::genLoadStaticStructVar("fManager"));
            }
            ValueInst* obj = IB::genFunCallInst("new" + kvnames.first, args);
            pushInitMethod(IB::genDecStackVar(
                kvnames.second,
                IB::genNamedTyped(kvnames.first, IB::genBasicTyped(Typed::kObj_ptr)), obj));

            // HACK for Rust, Julia and AssemblyScript backends
            if (gGlobal->gOutputLang != "rust" && gGlobal->gOutputLang != "julia" &&
                gGlobal->gOutputLang != "asc") {
                // Delete object
                Values args3;
                args3.push_back(signame);
                if (gGlobal->gMemoryManager >= 0) {
                    args3.push_back(IB::genLoadStaticStructVar("fManager"));
                }
                pushPostInitMethod(IB::genVoidFunCallInst("delete" + kvnames.first, args3));
            }
        }
    }

    // Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    string tablename;
    getTableNameProperty(content, tablename);
    vname += tablename;

    // Table declaration
    if (gGlobal->gInlineTable) {
        // The table is allocated in the DSP struct
        pushDeclare(IB::genDecStructVar(vname, IB::genArrayTyped(ctype, size)));
    } else if (gGlobal->gMemoryManager == 0) {
        // The table is defined as a pointer to be allocated by the memory manager
        pushGlobalDeclare(
            IB::genDecStaticStructVar(vname, IB::genArrayTyped(ctype, 0), IB::genInt32NumInst(0)));

        // The table has to be allocated and destroyed using the memory manager
        Values alloc_args;
        alloc_args.push_back(IB::genLoadStaticStructVar("fManager"));
        alloc_args.push_back(IB::genInt32NumInst(size * ctype->getSizeBytes()));
        pushStaticInitMethod(IB::genStoreStaticStructVar(
            vname, IB::genCastInst(IB::genFunCallInst("allocate", alloc_args, true),
                                   IB::genArrayTyped(ctype, 0))));

        Values destroy_args;
        destroy_args.push_back(IB::genLoadStaticStructVar("fManager"));
        destroy_args.push_back(IB::genLoadStaticStructVar(vname));
        pushStaticDestroyMethod(IB::genVoidFunCallInst("destroy", destroy_args, true));

    } else {
        // The table is statically allocated
        pushGlobalDeclare(IB::genDecStaticStructVar(vname, IB::genArrayTyped(ctype, size)));
    }

    // Keep table size in bytes
    gGlobal->gTablesSize[tablename] = make_pair(vname, size * ctype->getSizeBytes());

    // Init content generator
    Values args1;
    args1.push_back(signame);
    args1.push_back(IB::genLoadFunArgsVar("sample_rate"));
    pushStaticInitMethod(IB::genVoidFunCallInst("instanceInit" + tablename, args1, true));

    // Fill the table
    Values args2;
    args2.push_back(signame);
    args2.push_back(IB::genInt32NumInst(size));
    if (gGlobal->gInlineTable) {
        // The table is allocated in the DSP struct
        args2.push_back(IB::genLoadStructVar(vname));
    } else {
        // HACK for Rust backend
        args2.push_back(IB::genLoadStaticMutRefStructVar(vname));
    }
    pushStaticInitMethod(IB::genVoidFunCallInst("fill" + tablename, args2, true));

    // Return table access
    if (gGlobal->gInlineTable) {
        // The table is allocated in the DSP struct
        return IB::genLoadStructVar(vname);
    } else {
        return IB::genLoadStaticStructVar(vname);
    }
}

/*----------------------------------------------------------------------------
 sigWRTable : table assignment
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateWRTbl(Tree sig, Tree size, Tree gen, Tree wi, Tree ws)
{
    ValueInst* tblname = generateTable(sig, size, gen);

    /*
     // TODO
     Tree id, size, content;
     if (isSigTable(tbl, id, size, content)) {
        // The type of the allocated table has to take the type of the WRTbl
        // (which is the union of the 'init signal' and the 'input signal')
        setSigType(content, getCertifiedSigType(sig));
     }
     */

    LoadVarInst* load_value = dynamic_cast<LoadVarInst*>(tblname);
    faustassert(load_value);
    string vname = load_value->fAddress->getName();

    ValueInst* vwi = CS(wi);
    ValueInst* vws = CS(ws);
    switch (getCertifiedSigType(sig)->variability()) {
        case kKonst:
            pushInitMethod(IB::genStoreArrayStructVar(vname, vwi, vws));
            break;
        case kBlock:
            pushComputeBlockMethod(IB::genStoreArrayStructVar(vname, vwi, vws));
            break;
        default:
            pushComputeDSPMethod(IB::genControlInst(
                getConditionCode(sig), IB::genStoreArrayStructVar(vname, vwi, vws)));
            break;
    }

    // Return table access
    return IB::genLoadStructVar(vname);
}

/*----------------------------------------------------------------------------
 sigRDTable : table access
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateRDTbl(Tree sig, Tree tbl, Tree ri)
{
    // Test the special case of a read only table that can be compiled as a static member
    ValueInst*          tblname;
    Address::AccessType access;

    Tree size, gen;
    if (isSigWRTbl(tbl, size, gen)) {
        // rdtable (in DSP struct when gInlineTable)
        access = (gGlobal->gInlineTable) ? Address::kStruct : Address::kStaticStruct;
        if (!getCompiledExpression(tbl, tblname)) {
            tblname = setCompiledExpression(tbl, generateStaticTable(tbl, size, gen));
        }
    } else {
        // rwtable
        access  = Address::kStruct;
        tblname = CS(tbl);
    }

    LoadVarInst* load_value1 = dynamic_cast<LoadVarInst*>(tblname);
    faustassert(load_value1);

    LoadVarInst* load_value2 =
        IB::genLoadArrayVar(load_value1->fAddress->getName(), access, CS(ri));
    return generateCacheCode(sig, load_value2);
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
        faustassert(isRec(r, var, le));
        res = generateRec(r, var, le, i);
        faustassert(getVectorNameProperty(sig, vname));
    } else {
        res = IB::genNullValueInst();  // Result not used
    }
    return res;
}

/**
 * Generate code for a group of mutually recursive definitions
 */
/**
 * Is this delay amount always 1 or more ? A constant >= 1, or an amount
 * whose typed interval starts at 1 or more (the frontend places 1 + d on
 * a dissolved alias, and the interval typing keeps the 1). An amount that
 * may be 0 is an instantaneous read.
 */
static bool delayIsPositive(Tree y)
{
    int d;
    if (isSigInt(y, &d)) {
        return d >= 1;
    }
    ::Type t = getCertifiedSigType(y);
    if (t) {
        itv::interval it = t->getInterval();
        return it.isValid() && it.lo() >= 1;
    }
    return false;
}

/**
 * Is this delayed read of a projection a read of PAST state ?
 */
static bool isPastProjRead(Tree x, Tree y)
{
    int  i;
    Tree g;
    return isProj(x, &i, g) && delayIsPositive(y);
}

/**
 * Members of the recursive group `group` read at the CURRENT tick by
 * expression t : directly, or through a compound read at delay 0. Any read
 * at a delay of 1 or more is past state and stops the walk, a delayed
 * compound included : its line write is ordered by the deferral above,
 * not by the member order (descending into it would draw a dependency
 * edge for every past read and knot the members into false cycles).
 */
static void instantaneousReferees(Tree t, Tree group, std::set<int>& out, std::set<Tree>& seen)
{
    std::vector<Tree> work{t};
    while (!work.empty()) {
        Tree n = work.back();
        work.pop_back();
        if (!seen.insert(n).second) {
            continue;
        }
        int  i;
        Tree x, y;
        if (isProj(n, &i, x)) {
            if (x == group) {
                out.insert(i);
            }
            continue;
        }
        if (isSigDelay(n, x, y) && delayIsPositive(y)) {
            work.push_back(y);  // the amount only : the read is past state
            continue;
        }
        for (int k = 0; k < n->arity(); k++) {
            work.push_back(n->branch(k));
        }
    }
}

/**
 * Emission order of the members of a recursive group : every member after
 * the members it reads at the current tick (a topological order on the
 * instantaneous references, definition order among the free ones). An
 * instantaneous cycle cannot come from a causal program ; should one
 * remain, its members follow in definition order.
 */
std::vector<int> InstructionsCompiler::instantaneousMemberOrder(Tree sig, Tree le,
                                                                const std::vector<bool>& used)
{
    int                        N = len(le);
    std::vector<std::set<int>> deps(N);
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            std::set<Tree> seen;
            instantaneousReferees(nth(le, i), sig, deps[i], seen);
            deps[i].erase(i);
        }
    }
    std::vector<int>  order;
    std::vector<bool> done(N, false);
    bool              progress = true;
    while (progress) {
        progress = false;
        for (int i = 0; i < N; i++) {
            if (done[i]) {
                continue;
            }
            bool ready = true;
            for (int j : deps[i]) {
                if (!done[j] && used[j]) {
                    ready = false;
                    break;
                }
            }
            if (ready) {
                done[i] = true;
                order.push_back(i);
                progress = true;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        if (!done[i]) {
            order.push_back(i);
        }
    }
    return order;
}

ValueInst* InstructionsCompiler::generateRec(Tree sig, Tree var, Tree le, int index)
{
    int N = len(le);

    ValueInst*          res = nullptr;
    vector<bool>        used(N);
    vector<int>         delay(N);
    vector<string>      vname(N);
    vector<BasicTyped*> ctype(N);

    // Prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i, sig);  // recreate each recursive definition
        if (fOccMarkup->retrieve(e)) {
            // This projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(e), "Rec", ctype[i], vname[i]);
            setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup->retrieve(e)->getMaxDelay();
            // std::cout << "generateRec " << vname[i]  << " " << delay[i] << std::endl;
        } else {
            // This projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }

    // Members not yet stored : the line writes triggered while compiling
    // the definitions must not read their current value (decoupled write,
    // see generateDelayAccess)
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            fUnstoredRecMembers.insert(sigProj(i, sig));
        }
    }

    // Emission order : a member is stored before every member that reads
    // it at the current tick, directly or through a compound computed at
    // the current tick (the deferred line writes above rely on it : a
    // delay-0 access never meets a pending line when the referee is
    // already stored). Definition order otherwise. The frontend places
    // the one-tick delay on every ~ and letrec crossing, so definition
    // order was topological by construction ; the delayed-alias
    // dissolution of normalizeRecGroups produces instantaneous reads
    // between members in any order (fdnrev0 : three members read a
    // later member at the current tick, one sample late).
    std::vector<int> order = instantaneousMemberOrder(sig, le, used);

    // Generate delayline for each element of a recursive definition
    for (int i : order) {
        if (used[i]) {
            Address::AccessType access;
            ValueInst*          ccs = getConditionCode(nth(le, i));
            ValueInst*          def = CS(nth(le, i));
            if (index == i) {
                res = generateDelayLine(def, ctype[i], vname[i], delay[i], access, ccs);
            } else {
                generateDelayLine(def, ctype[i], vname[i], delay[i], access, ccs);
            }
            fUnstoredRecMembers.erase(sigProj(i, sig));
            flushPendingDelayWrites();
        }
    }

    return res;
}

/**
 * Deferred line writes (decoupled write, see generateDelayAccess) : emit the
 * pending expressions whose recursive reads are all stored by now. Compiling
 * one may defer new ones ; loop until stable. Expressions still reaching an
 * unstored member stay pending for a later store.
 */
void InstructionsCompiler::flushPendingDelayWrites()
{
    bool progress = true;
    while (progress) {
        progress = false;
        std::vector<Tree> work;
        work.swap(fPendingDelayWrites);
        for (Tree e : work) {
            if (reachesUnstoredRecMember(e)) {
                fPendingDelayWrites.push_back(e);
            } else {
                CS(e);  // emits the computation and, through the cache path,
                        // the write into the pre-allocated line
                progress = true;
            }
        }
    }
}

/**
 * Does this expression, compiled now, read the CURRENT value of a recursive
 * member whose store has not been emitted yet ? A delay sitting DIRECTLY on
 * a projection is a read of past state, hence safe ; a delayed compound is
 * computed at the current tick (only its result is shifted), so the walk
 * descends into it -- its own line write would be triggered too.
 */
bool InstructionsCompiler::reachesUnstoredRecMember(Tree t)
{
    std::set<Tree>    seen;
    std::vector<Tree> work{t};
    while (!work.empty()) {
        Tree n = work.back();
        work.pop_back();
        if (!seen.insert(n).second) {
            continue;
        }
        int  i;
        Tree x, y;
        if (isProj(n, &i, x)) {
            if (fUnstoredRecMembers.count(n)) {
                return true;
            }
            continue;
        }
        if (isSigDelay(n, x, y) && isPastProjRead(x, y)) {
            work.push_back(y);  // the amount only : the projection read is
                                // past state (constant or interval-typed
                                // delay >= 1 ; a variable delay that may
                                // be 0 was taken for an instantaneous
                                // read, deferring a line that its reader
                                // then read at delay 0 before the write :
                                // greyhole, a modulated fdelay4 into an
                                // sdelay)
            continue;
        }
        if (tvec fir; isSigFIR(n, fir)) {
            // the coefficients are read now ; a projection source with a null c0 only in
            // the past, as by a delay >= 1 (the FIR of a fractional delay in a feedback :
            // greyhole again)
            for (size_t k = 1; k < fir.size(); k++) {
                work.push_back(fir[k]);
            }
            int  i;
            Tree g;
            if (!(isProj(fir[0], &i, g) && isZero(fir[1]))) {
                work.push_back(fir[0]);
            }
            continue;
        }
        for (int k = 0; k < n->arity(); k++) {
            work.push_back(n->branch(k));
        }
    }
    return false;
}

/*****************************************************************************
 Control
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateControl(Tree sig, Tree x, Tree y)
{
    CS(y);
    return generateCacheCode(x, CS(x));
}

/*****************************************************************************
 PREFIX, DELAY A PREFIX VALUE
 *****************************************************************************/

ValueInst* InstructionsCompiler::generatePrefix(Tree sig, Tree x, Tree e)
{
    string         vperm = gGlobal->getFreshID("pfPerm");
    string         vtemp = gGlobal->getFreshID("pfTemp");
    Typed::VarType type  = convert2FIRType(getCertifiedSigType(sig)->nature());

    // Variable declaration
    pushDeclare(IB::genDecStructVar(vperm, type));

    // Init
    pushInitMethod(IB::genStoreStructVar(vperm, CS(x)));

    // Exec
    pushComputeDSPMethod(IB::genControlInst(
        getConditionCode(sig), IB::genDecStackVar(vtemp, type, IB::genLoadStructVar(vperm))));

    /*
    ValueInst* res = CS(e);
    string vname;
    if (getVectorNameProperty(e, vname)) {
        setVectorNameProperty(sig, vname);
    } else {
        faustassert(false);
    }
    */

    ValueInst* cond = getConditionCode(sig);
    ValueInst* ve   = CS(e);
    pushComputeDSPMethod(IB::genControlInst(cond, IB::genStoreStructVar(vperm, ve)));
    return IB::genLoadStackVar(vtemp);
}

/*****************************************************************************
 SELECT
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    ValueInst* cond = CS(sel);
    ValueInst* v1   = CS(s1);
    ValueInst* v2   = CS(s2);
    return generateSelect2Aux(sig, s1, s2, cond, v1, v2);
}

ValueInst* InstructionsCompiler::generateSelect2Aux(Tree sig, Tree s1, Tree s2, ValueInst* cond,
                                                    ValueInst* v1, ValueInst* v2)
{
    if (gGlobal->gStrictSelect) {
        ::Type ct1 = getCertifiedSigType(s1);
        ::Type ct2 = getCertifiedSigType(s2);

        string      v_then, v_else;
        BasicTyped *t_then, *t_else;
        getTypedNames(ct1, "Then", t_then, v_then);
        getTypedNames(ct2, "Else", t_else, v_else);

        // Create local variables to force proper execution of both branches of 'select2'
        switch (getCertifiedSigType(sig)->variability()) {
            case kBlock:
                // Local variable is only created if needed that is if the expression
                // is not already a 'simple value', constant or variable
                if (!v1->isSimpleValue()) {
                    pushComputeBlockMethod(IB::genDecStackVar(v_then, t_then, v1));
                    v1 = IB::genLoadStackVar(v_then);
                }
                if (!v2->isSimpleValue()) {
                    pushComputeBlockMethod(IB::genDecStackVar(v_else, t_else, v2));
                    v2 = IB::genLoadStackVar(v_else);
                }
                break;

            case kSamp:
                // Local variable is only created if needed that is if the expression
                // is not already a 'simple value', constant or variable
                if (!v1->isSimpleValue()) {
                    pushComputeDSPMethod(IB::genDecStackVar(v_then, t_then, v1));
                    v1 = IB::genLoadStackVar(v_then);
                }
                if (!v2->isSimpleValue()) {
                    pushComputeDSPMethod(IB::genDecStackVar(v_else, t_else, v2));
                    v2 = IB::genLoadStackVar(v_else);
                }
                break;
        }
    }

    return generateCacheCode(sig, IB::genSelect2Inst(cond, v2, v1));
}

/*****************************************************************************
 EXTENDED
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateXtended(Tree sig)
{
    xtendedCodegen* p = static_cast<xtendedCodegen*>((xtended*)getUserData(sig));
    Values         args;
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
/**
 * The name of the delay line of exp, read in the past : a line whose write is deferred
 * keeps its name, a line that cannot be written yet is reserved (decoupled write, see
 * generateDelayAccess), otherwise exp is compiled. immediate is the value of exp when it
 * has no line (mxd == 0), nullptr otherwise.
 */
std::string InstructionsCompiler::delayLineName(Tree exp, int mxd, const char* prefix, ValueInst*& immediate)
{
    string vname;
    immediate = nullptr;
    if (std::find(fPendingDelayWrites.begin(), fPendingDelayWrites.end(), exp) !=
        fPendingDelayWrites.end()) {
        getVectorNameProperty(exp, vname);
    } else if (!getVectorNameProperty(exp, vname) && mxd > 0 && !fUnstoredRecMembers.empty() &&
               reachesUnstoredRecMember(exp)) {
        BasicTyped* ctype;
        getTypedNames(getCertifiedSigType(exp), prefix, ctype, vname);
        setVectorNameProperty(exp, vname);
        fPendingDelayWrites.push_back(exp);
    } else {
        ValueInst* code = CS(exp);
        if (!getVectorNameProperty(exp, vname)) {
            faustassert(mxd == 0);
            immediate = code;
        }
    }
    return vname;
}

/**
 * exp@delay for a FIR tap, delay a constant : the read of the delay line, never cached on
 * the FIR node (the tap is not a node)
 */
ValueInst* InstructionsCompiler::generateTapAccess(Tree exp, int delay)
{
    // a source with a line is read in its line, at delay 0 too (a recursive projection
    // read at delay 0 is its stored value, not its definition)
    int        mxd = fOccMarkup->retrieve(exp)->getMaxDelay();
    ValueInst* immediate;
    string     vname = delayLineName(exp, mxd, "Vec", immediate);
    if (immediate != nullptr) {
        faustassert(delay == 0);
        return immediate;
    }
    if (mxd == 0) {
        return IB::genLoadStackVar(vname);
    }
    return lineRead(vname, mxd, delay);
}

/**
 * The sample delay ago of the line vname of maximum delay mxd (the structure
 * generateDelayLine gives it), the index never cached
 */
bool InstructionsCompiler::fmaWanted(Tree sig)
{
    const std::string& lang = gGlobal->gOutputLang;
    if (!gGlobal->gFMA || (lang != "c" && lang != "cpp")) return false;
    if (gGlobal->gFloatSize != 1 && gGlobal->gFloatSize != 2) return false;
    ::Type t = getCertifiedSigType(sig);
    return t->nature() == kReal && t->variability() == kSamp;
}

ValueInst* InstructionsCompiler::genFma(ValueInst* a, ValueInst* b, ValueInst* c)
{
    std::vector<Typed::VarType> types = {itfloat(), itfloat(), itfloat()};
    return fContainer->pushFunction(subst("faust_fma$0", isuffix()), itfloat(), types, {a, b, c});
}

ValueInst* InstructionsCompiler::lineRead(const string& vname, int mxd, int delay)
{
    faustassert(mxd >= delay);
    if (mxd < gGlobal->gMaxCopyDelay) {
        return IB::genLoadArrayStructVar(vname, IB::genInt32NumInst(delay));
    } else if (mxd < gGlobal->gMaskDelayLineThreshold) {
        int N = pow2limit(mxd + 1);
        ensureIotaCode();
        FIRIndex index = (FIRIndex(IB::genLoadStructVar(fCurrentIOTA)) - delay) & FIRIndex(N - 1);
        return IB::genLoadArrayStructVar(vname, index);
    } else {
        string   ridx_name = gGlobal->getFreshID(vname + "_ridx_tmp");
        FIRIndex widx1     = FIRIndex(IB::genLoadStructVar(vname + "_widx"));
        pushComputeDSPMethod(IB::genDecStackVar(ridx_name, Typed::kInt32, widx1 - delay));
        FIRIndex ridx1 = FIRIndex(IB::genLoadStackVar(ridx_name));
        FIRIndex ridx2 = FIRIndex(IB::genSelect2Inst(ridx1 < 0, ridx1 + FIRIndex(mxd + 1), ridx1));
        return IB::genLoadArrayStructVar(vname, ridx2);
    }
}

/**
 * IIR[x, c1, ...] : y = x + c1*y@1 + ..., the node reading its own past in its own line.
 * The line is named first, the chain of the definition (the association of its interval :
 * x, then the taps from the first delay to the last, a neg(c) or -1 coefficient
 * subtracted) reads it, and the line is written with the result.
 */
ValueInst* InstructionsCompiler::generateIIR(Tree sig, const tvec& iir)
{
    faustassert(iir.size() > 1);
    int mxd = fOccMarkup->retrieve(sig)->getMaxDelay();
    faustassert(mxd >= int(iir.size()) - 1);
    BasicTyped* ctype;
    string      vname;
    if (getVectorNameProperty(sig, vname)) {
        // the line was reserved by a deferred delay access (decoupled write)
        ::Type t = getCertifiedSigType(sig);
        ctype    = (t->nature() == kInt) ? IB::genBasicTyped(Typed::kInt32) : genFloatType(t);
    } else {
        getTypedNames(getCertifiedSigType(sig), "IIR", ctype, vname);
        setVectorNameProperty(sig, vname);
    }
    ValueInst* acc  = CS(iir[0]);
    const bool fuse = fmaWanted(sig);
    for (size_t i = 1; i < iir.size(); i++) {
        if (isZero(iir[i])) {
            continue;
        }
        ValueInst* access = lineRead(vname, mxd, int(i));
        Tree       m;
        const bool sub  = negativeCoefficient(iir[i], m);
        Tree       c    = sub ? m : iir[i];
        ValueInst* term = access;
        if (c != nullptr && !isOne(c)) {
            ValueInst* vc = sub ? operandAtRate(c) : CS(c);
            if (fuse) {  // acc +/- c * y@i as one rounding
                acc = genFma(sub ? IB::genNeg(vc) : vc, access, acc);
                continue;
            }
            term = IB::genBinopInst(kMul, vc, access);
        }
        acc = IB::genBinopInst(sub ? kSub : kAdd, acc, term);
    }
    return writeIIRLine(sig, acc, ctype, vname, mxd);
}

/**
 * IRM(x; p) = y, y = mix(p, x, y'). A slow smoother (x and p computed at most once per
 * block) is the weighted sum w * x + p * y' of the source (si.smooth), w * x at the rate of
 * x and p, w the weight of x when the normal form wrote the pole 1 - w (irmInputWeight),
 * 1 - p otherwise : in float, it stops nearer to its target than the interpolation, whose
 * increments vanish before it. Otherwise an interpolation. When the normal form wrote the
 * pole 1 - w, w is the exact weight of x : y' + w * (x - y'), the computation of the source
 * (the state of a TPT filter, s + 2g (x - s)). Otherwise from the operand whose weight may
 * be near 1, as generateMix : x + p * (y' - x) when p may be below 1/2, y' + (1 - p) *
 * (x - y'), 1 - p exact, otherwise. The interval of the node bounds all these forms (Irm).
 * The value is stored in the node's line, read back at delay 1.
 */
ValueInst* InstructionsCompiler::generateIRM(Tree sig, Tree x, Tree p)
{
    int mxd = fOccMarkup->retrieve(sig)->getMaxDelay();
    faustassert(mxd >= 1);
    BasicTyped* ctype;
    string      vname;
    if (getVectorNameProperty(sig, vname)) {
        ctype = genFloatType(getCertifiedSigType(sig));
    } else {
        getTypedNames(getCertifiedSigType(sig), "IRM", ctype, vname);
        setVectorNameProperty(sig, vname);
    }
    Tree       w = irmInputWeight(p);
    ValueInst* code;
    ValueInst* prev = lineRead(vname, mxd, 1);
    ValueInst* vx   = compoundOperand(x);
    const int  vr   = std::max(getCertifiedSigType(x)->variability(), getCertifiedSigType(p)->variability());
    if (getCertifiedSigType(sig)->nature() == kReal && vr != kSamp) {
        ValueInst* vw = w ? compoundOperand(w)
                          : IB::genBinopInst(kSub, IB::genRealNumInst(itfloat(), 1.0), compoundOperand(p));
        ValueInst* wx = compoundSlowStore(vr, IB::genBinopInst(kMul, vw, vx));
        ValueInst* vp = compoundOperand(p);
        code          = fmaWanted(sig) ? genFma(vp, prev, wx) : IB::genBinopInst(kAdd, wx, IB::genBinopInst(kMul, vp, prev));
    } else if (!w && !itv::mixFromB(getCertifiedSigType(p)->getInterval())) {
        ValueInst* d = IB::genBinopInst(kSub, prev, vx);
        code         = fmaWanted(sig) ? genFma(compoundOperand(p), d, vx)
                                      : IB::genBinopInst(kAdd, vx, IB::genBinopInst(kMul, compoundOperand(p), d));
    } else {
        ValueInst* vw;
        if (w) {
            vw = compoundOperand(w);
        } else {
            const int vrp = getCertifiedSigType(p)->variability();
            vw            = IB::genBinopInst(kSub, IB::genRealNumInst(itfloat(), 1.0), compoundOperand(p));
            if (vrp != kSamp) {
                vw = compoundSlowStore(vrp, vw);  // 1 - p at the rate of p
            }
        }
        ValueInst* d = IB::genBinopInst(kSub, vx, prev);
        code         = fmaWanted(sig) ? genFma(vw, d, lineRead(vname, mxd, 1))
                                      : IB::genBinopInst(kAdd, lineRead(vname, mxd, 1), IB::genBinopInst(kMul, vw, d));
    }
    return writeIIRLine(sig, code, ctype, vname, mxd);
}

/**
 * Bpf(x; t1, ..., tn; r0, ..., rn) : the chain of comparisons of ba.bpf, x computed once,
 * x < t1 ? r0 : (x < t2 ? r1 : ... rn) ; the regions are computed as the branches of a
 * select2.
 */
ValueInst* InstructionsCompiler::generateBpf(Tree sig)
{
    Tree x;
    tvec t, r;
    isSigBpf(sig, x, t, r);
    if (BpfTable tb; gGlobal->gMemoryManager < 1 && !gGlobal->gWaveformInDSP && bpfTableOf(sig, tb)) {
        return generateBpfTable(sig, x, tb);
    }
    std::vector<ValueInst*> vt, vr;
    for (Tree ti : t) vt.push_back(CS(ti));
    for (Tree ri : r) vr.push_back(CS(ri));
    ValueInst* acc = vr.back();
    for (size_t i = t.size(); i-- > 0;) {
        ValueInst* vx   = compoundOperand(x);
        ValueInst* cond = IB::genBinopInst(kLT, vx, vt[i]);
        acc             = IB::genSelect2Inst(cond, vr[i], acc);
    }
    return generateCacheCode(sig, acc);
}

/**
 * Bpf by its table of cells (bpf_table.hh) : constant static arrays, the region of x in
 * constant time, then a[r] + b[r] * (xc - c[r]). The comparisons are selects of 1 or 0,
 * whatever the backend's type of a comparison.
 */
ValueInst* InstructionsCompiler::generateBpfTable(Tree sig, Tree x, const BpfTable& tb)
{
    const Typed::VarType rtype = itfloat();
    auto declareReals = [&](const std::vector<double>& v) {
        const string name = subst("$0Bpf$1", fContainer->getClassName(), gGlobal->getFreshID("f"));
        ValueInst*   arr  = IB::genArrayNumInst(rtype, int(v.size()));
        if (rtype == Typed::kFloat) {
            FloatArrayNumInst* fa = dynamic_cast<FloatArrayNumInst*>(arr);
            faustassert(fa);
            for (size_t k = 0; k < v.size(); k++) fa->setValue(int(k), float(v[k]));
        } else {
            DoubleArrayNumInst* da = dynamic_cast<DoubleArrayNumInst*>(arr);
            faustassert(da);
            for (size_t k = 0; k < v.size(); k++) da->setValue(int(k), v[k]);
        }
        pushGlobalDeclare(IB::genDecConstStaticStructVar(name, IB::genArrayTyped(rtype, int(v.size())), arr));
        return name;
    };
    auto declareInts = [&](const std::vector<int>& v) {
        const string       name = subst("$0Bpf$1", fContainer->getClassName(), gGlobal->getFreshID("i"));
        Int32ArrayNumInst* ia   = dynamic_cast<Int32ArrayNumInst*>(IB::genArrayNumInst(Typed::kInt32, int(v.size())));
        faustassert(ia);
        for (size_t k = 0; k < v.size(); k++) ia->setValue(int(k), v[k]);
        pushGlobalDeclare(IB::genDecConstStaticStructVar(name, IB::genArrayTyped(Typed::kInt32, int(v.size())), ia));
        return name;
    };
    const string lo = declareReals(tb.lo), hi = declareReals(tb.hi);
    const string a = declareReals(tb.a), b = declareReals(tb.b), c = declareReals(tb.c);
    const string cell = declareInts(tb.cell);
    const string use  = tb.u ? declareInts(tb.useU) : string();

    BasicTyped* ftype = IB::genBasicTyped(rtype);
    BasicTyped* itype = IB::genInt32Typed();
    auto real   = [&](double v) { return IB::genRealNumInst(rtype, v); };
    auto intv   = [&](int v) { return IB::genInt32NumInst(v); };
    auto stackR = [&](const string& prefix, ValueInst* v) {
        const string n = gGlobal->getFreshID(prefix);
        pushComputeDSPMethod(IB::genDecStackVar(n, ftype, v));
        return n;
    };
    auto stackI = [&](const string& prefix, ValueInst* v) {
        const string n = gGlobal->getFreshID(prefix);
        pushComputeDSPMethod(IB::genDecStackVar(n, itype, v));
        return n;
    };
    auto loadR  = [&](const string& n) { return IB::genLoadStackVar(n); };
    auto loadI  = [&](const string& n) { return IB::genLoadStackVar(n); };
    auto one0   = [&](ValueInst* cond) { return IB::genSelect2Inst(cond, intv(1), intv(0)); };
    auto lt     = [&](ValueInst* p, ValueInst* q) { return IB::genBinopInst(kLT, p, q); };
    auto ge     = [&](ValueInst* p, ValueInst* q) { return IB::genBinopInst(kGE, p, q); };

    // xc : x inside [t1, tn[, t1 outside or NaN (a finite value for the conversion below)
    const string xs = stackR("fBpfS", compoundOperand(x));
    const string xc = stackR("fBpfX", IB::genSelect2Inst(lt(loadR(xs), real(tb.t1)), real(tb.t1),
                                                         IB::genSelect2Inst(lt(loadR(xs), real(tb.tn)), loadR(xs), real(tb.t1))));
    // k : the cell, bounded by an integer test
    ValueInst*   kf = IB::genBinopInst(kMul, IB::genBinopInst(kSub, loadR(xc), real(tb.t1)), real(tb.invh));
    const string k0 = stackI("iBpfK", IB::genCastInst(kf, itype));
    const string k1 = stackI("iBpfK", IB::genSelect2Inst(lt(loadI(k0), intv(tb.K)), loadI(k0), intv(tb.K - 1)));
    // r : the region of the cell, corrected by the thresholds (twice up, once down)
    const string r0 = stackI("iBpfR", IB::genLoadArrayStaticStructVar(cell, loadI(k1)));
    const string r1 = stackI("iBpfR", IB::genBinopInst(kAdd, loadI(r0), one0(ge(loadR(xc), IB::genLoadArrayStaticStructVar(hi, loadI(r0))))));
    const string r2 = stackI("iBpfR", IB::genBinopInst(kAdd, loadI(r1), one0(ge(loadR(xc), IB::genLoadArrayStaticStructVar(hi, loadI(r1))))));
    const string r3 = stackI("iBpfR", IB::genBinopInst(kSub, loadI(r2), one0(lt(loadR(xc), IB::genLoadArrayStaticStructVar(lo, loadI(r2))))));
    const string r  = stackI("iBpfR", IB::genSelect2Inst(lt(loadR(xs), real(tb.t1)), intv(0),
                                                         IB::genSelect2Inst(lt(loadR(xs), real(tb.tn)), loadI(r3), intv(tb.n))));
    // the variable of the region : x, or u inside [t1, tn[ (0 outside)
    ValueInst* var = loadR(xc);
    if (tb.u) {
        const string uc = stackR("fBpfU", IB::genSelect2Inst(lt(loadR(xs), real(tb.t1)), real(0),
                                                             IB::genSelect2Inst(lt(loadR(xs), real(tb.tn)), compoundOperand(tb.u), real(0))));
        var = IB::genSelect2Inst(IB::genBinopInst(kNE, IB::genLoadArrayStaticStructVar(use, loadI(r)), intv(0)), loadR(uc), loadR(xc));
    }
    ValueInst* d = IB::genBinopInst(kSub, var, IB::genLoadArrayStaticStructVar(c, loadI(r)));
    // the value in a variable : the text printers write a sum nested on the right without
    // parentheses (y + (a + p) would become (y + a) + p in C) ; stored, it is a + p whatever
    // adds it
    ValueInst* v = fmaWanted(sig)
                       ? genFma(IB::genLoadArrayStaticStructVar(b, loadI(r)), d, IB::genLoadArrayStaticStructVar(a, loadI(r)))
                       : IB::genBinopInst(kAdd, IB::genLoadArrayStaticStructVar(a, loadI(r)),
                                          IB::genBinopInst(kMul, IB::genLoadArrayStaticStructVar(b, loadI(r)), d));
    return setCompiledExpression(sig, generateVariableStore(sig, v));
}

/**
 * The value of an IIR, stored once in a variable : the line and the readers read it
 */
ValueInst* InstructionsCompiler::writeIIRLine(Tree sig, ValueInst* exp, BasicTyped* ctype, const string& vname, int mxd)
{
    ValueInst* v = generateVariableStore(sig, exp);
    return generateDelayVec(sig, v, ctype, vname, mxd);
}

/**
 * FIR[x, c0, c1, ...] : the chain of the definition, the association of its interval, the
 * taps c[k] * x@k from the first delay to the last, the null coefficients left out.
 */
ValueInst* InstructionsCompiler::generateFIR(Tree sig, const tvec& fir)
{
    faustassert(fir.size() > 1);
    Tree       x    = fir[0];
    ValueInst* acc  = nullptr;
    const bool fuse = fmaWanted(sig);
    for (size_t i = 1; i < fir.size(); i++) {
        if (isZero(fir[i])) {
            continue;
        }
        ValueInst* access = generateTapAccess(x, int(i) - 1);
        // a negative coefficient after the first tap : the tap subtracted
        Tree       m;
        const bool sub  = acc && negativeCoefficient(fir[i], m);
        Tree       c    = sub ? m : fir[i];
        ValueInst* term = access;
        if (c != nullptr && !isOne(c)) {
            ValueInst* vc = sub ? operandAtRate(c) : CS(c);
            if (fuse && acc) {  // acc +/- c * x@k as one rounding
                acc = genFma(sub ? IB::genNeg(vc) : vc, access, acc);
                continue;
            }
            term = IB::genBinopInst(kMul, vc, access);
        }
        acc = acc ? IB::genBinopInst(sub ? kSub : kAdd, acc, term) : term;
    }
    if (acc == nullptr) {
        acc = (getCertifiedSigType(sig)->nature() == kInt) ? static_cast<ValueInst*>(IB::genInt32NumInst(0))
                                                           : static_cast<ValueInst*>(IB::genRealNumInst(itfloat(), 0.0));
    }
    return generateCacheCode(sig, acc);
}

ValueInst* InstructionsCompiler::generateDelayAccess(Tree sig, Tree exp, Tree delay)
{
    int    mxd = fOccMarkup->retrieve(exp)->getMaxDelay();
    string vname;

    if (std::find(fPendingDelayWrites.begin(), fPendingDelayWrites.end(), exp) !=
        fPendingDelayWrites.end()) {
        // A further access to a line whose write is still deferred : the
        // name is known, nothing is compiled here. Without this test the
        // second access (a member reading s@n and s@n+1) found the name
        // set, took the eager branch below and emitted the write before
        // the member's store -- the very read-one-sample-late the deferral
        // exists to prevent (witness : a lowpass in the feedback of a
        // delay, fdnrev0 and greyhole in faustlibraries).
        getVectorNameProperty(exp, vname);
    } else if (!getVectorNameProperty(exp, vname) && mxd > 0 && !fUnstoredRecMembers.empty() &&
               reachesUnstoredRecMember(exp)) {
        // DECOUPLED LINE WRITE. Compiling exp right here would emit its line
        // write before the store of a recursive member it reads at the
        // current tick, making that read one sample late (shape : a member
        // definition d = f(d@1, s@n) where s reads d instantaneously).
        // Allocate the line name only ; the computation and the write are
        // deferred until every member exp reads has been stored -- see
        // generateRec and flushPendingDelayWrites. The accesses below only
        // need the name and mxd, and always target past slots : a delay-0
        // access cannot reach this state, because the member emission order
        // guarantees its referee is already stored.
        BasicTyped* ctype;
        getTypedNames(getCertifiedSigType(exp), "Vec", ctype, vname);
        setVectorNameProperty(exp, vname);
        fPendingDelayWrites.push_back(exp);
    } else {
        ValueInst* code = CS(exp);  // Ensure exp is compiled to have a vector name

        if (!getVectorNameProperty(exp, vname)) {
            if (mxd == 0) {
                // cerr << "it is a pure zero delay : " << code << endl;
                return code;
            } else {
                cerr << "ASSERT : no vector name for : " << ppsig(exp, MAX_ERROR_SIZE) << endl;
                faustassert(false);
            }
        }

        if (mxd == 0) {
            // not a real vector name but a scalar name
            return IB::genLoadStackVar(vname);
        }
    }

    if (mxd < gGlobal->gMaxCopyDelay) {
        int d;
        if (isSigInt(delay, &d)) {
            return IB::genLoadArrayStructVar(vname, CS(delay));
        } else {
            return generateCacheCode(sig, IB::genLoadArrayStructVar(vname, CS(delay)));
        }
    } else {
        if (mxd < gGlobal->gMaskDelayLineThreshold) {
            int N = pow2limit(mxd + 1);
            ensureIotaCode();

            FIRIndex value2 =
                (FIRIndex(IB::genLoadStructVar(fCurrentIOTA)) - CS(delay)) & FIRIndex(N - 1);
            return generateCacheCode(sig, IB::genLoadArrayStructVar(vname, value2));
        } else {
            string ridx_name = gGlobal->getFreshID(vname + "_ridx_tmp");

            // int ridx = widx - delay;
            FIRIndex widx1 = FIRIndex(IB::genLoadStructVar(vname + "_widx"));
            pushComputeDSPMethod(IB::genDecStackVar(ridx_name, Typed::kInt32, widx1 - CS(delay)));

            // dline[((ridx < 0) ? ridx + delay : ridx)];
            FIRIndex ridx1 = FIRIndex(IB::genLoadStackVar(ridx_name));
            FIRIndex ridx2 =
                FIRIndex(IB::genSelect2Inst(ridx1 < 0, ridx1 + FIRIndex(mxd + 1), ridx1));
            return generateCacheCode(sig, IB::genLoadArrayStructVar(vname, ridx2));
        }
    }
}

/**
 * Generate code for the delay mechanism. The generated code depends of the
 * maximum delay attached to exp and the "less temporaries" switch.
 */
ValueInst* InstructionsCompiler::generateDelayVec(Tree sig, ValueInst* exp, BasicTyped* ctype,
                                                  const string& vname, int mxd)
{
    setVectorNameProperty(sig, vname);
    Address::AccessType access;
    return generateDelayLine(exp, ctype, vname, mxd, access, getConditionCode(sig));
}

StatementInst* InstructionsCompiler::generateInitArray(const string& vname, BasicTyped* ctype,
                                                       int delay)
{
    ValueInst*  init  = IB::genTypedZero(ctype);
    BasicTyped* typed = ctype;
    string      index = gGlobal->getFreshID("l");

    // Generates table declaration
    pushDeclare(IB::genDecStructVar(vname, IB::genArrayTyped(typed, delay)));

    // Generates init table loop
    DeclareVarInst* loop_decl =
        IB::genDecLoopVar(index, IB::genInt32Typed(), IB::genInt32NumInst(0));
    ValueInst*    loop_end = IB::genLessThan(loop_decl->load(), IB::genInt32NumInst(delay));
    StoreVarInst* loop_inc = loop_decl->store(IB::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop = IB::genForLoopInst(loop_decl, loop_end, loop_inc);

    loop->pushFrontInst(IB::genStoreArrayStructVar(vname, loop_decl->load(), init));
    return loop;
}

StatementInst* InstructionsCompiler::generateShiftArray(const string& vname, int delay)
{
    if (gGlobal->gUseMemmove) {
        /*
            // Generate prototype
            Names fun_args;
            fun_args.push_back(IB::genNamedTyped("dst", Typed::kVoid_ptr));
            fun_args.push_back(IB::genNamedTyped("src", Typed::kVoid_ptr));
            fun_args.push_back(IB::genNamedTyped("size", Typed::kInt32));

            FunTyped* fun_type = IB::genFunTyped(fun_args,
           IB::genBasicTyped(Typed::kVoid_ptr), FunTyped::kDefault);
            pushGlobalDeclare(IB::genDeclareFunInst("memmove", fun_type));
        */

        // Return funcall
        Values args;
        args.push_back(IB::genLoadArrayStructVarAddress(vname, IB::genInt32NumInst(0)));
        args.push_back(IB::genLoadArrayStructVarAddress(vname, IB::genInt32NumInst(1)));
        args.push_back(IB::genInt32NumInst(delay * ifloatsize()));
        return IB::genDropInst(IB::genFunCallInst("memmove", args));

    } else {
        string index = gGlobal->getFreshID("j");

        // Generates init table loop
        DeclareVarInst* loop_decl =
            IB::genDecLoopVar(index, IB::genInt32Typed(), IB::genInt32NumInst(delay));
        ValueInst*    loop_end = IB::genGreaterThan(loop_decl->load(), IB::genInt32NumInst(0));
        StoreVarInst* loop_inc =
            loop_decl->store(IB::genSub(loop_decl->load(), IB::genInt32NumInst(1)));

        ForLoopInst* loop        = IB::genForLoopInst(loop_decl, loop_end, loop_inc);
        ValueInst*   load_value2 = IB::genSub(loop_decl->load(), IB::genInt32NumInst(1));
        ValueInst*   load_value3 = IB::genLoadArrayStructVar(vname, load_value2);

        loop->pushFrontInst(IB::genStoreArrayStructVar(vname, loop_decl->load(), load_value3));
        return loop;
    }
}

StatementInst* InstructionsCompiler::generateCopyArray(const string& vname, int index_from,
                                                       int index_to)
{
    ValueInst* inst1 = IB::genLoadArrayStructVar(vname, IB::genInt32NumInst(index_from));
    return IB::genStoreArrayStructVar(vname, IB::genInt32NumInst(index_to), inst1);
}

StatementInst* InstructionsCompiler::generateCopyArray(const string& vname_to,
                                                       const string& vname_from, int size)
{
    string index = gGlobal->getFreshID("j");

    // Generates init table loop
    DeclareVarInst* loop_decl =
        IB::genDecLoopVar(index, IB::genInt32Typed(), IB::genInt32NumInst(0));
    ValueInst*    loop_end = IB::genLessThan(loop_decl->load(), IB::genInt32NumInst(size));
    StoreVarInst* loop_inc = loop_decl->store(IB::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop       = IB::genForLoopInst(loop_decl, loop_end, loop_inc);
    ValueInst*   load_value = IB::genLoadArrayStructVar(vname_from, loop_decl->load());

    loop->pushFrontInst(IB::genStoreArrayStackVar(vname_to, loop_decl->load(), load_value));
    return loop;
}

ValueInst* InstructionsCompiler::generateDelayLine(ValueInst* exp, BasicTyped* ctype,
                                                   const string& vname, int mxd,
                                                   Address::AccessType& access, ValueInst* ccs)
{
    if (mxd == 0) {
        // Generate scalar use
        if (dynamic_cast<NullValueInst*>(ccs)) {
            pushComputeDSPMethod(IB::genDecStackVar(vname, ctype, exp));
        } else {
            pushPreComputeDSPMethod(IB::genDecStackVar(vname, ctype, IB::genTypedZero(ctype)));
            pushComputeDSPMethod(IB::genControlInst(ccs, IB::genStoreStackVar(vname, exp)));
        }

    } else if (mxd < gGlobal->gMaxCopyDelay) {
        // Generates table init
        pushClearMethod(generateInitArray(vname, ctype, mxd + 1));

        // Generate table use
        pushComputeDSPMethod(IB::genControlInst(
            ccs, IB::genStoreArrayStructVar(vname, IB::genInt32NumInst(0), exp)));

        // Generates post processing copy code to update delay values
        if (mxd == 1) {
            pushPostComputeDSPMethod(IB::genControlInst(ccs, generateCopyArray(vname, 0, 1)));
        } else if (mxd == 2) {
            pushPostComputeDSPMethod(IB::genControlInst(ccs, generateCopyArray(vname, 1, 2)));
            pushPostComputeDSPMethod(IB::genControlInst(ccs, generateCopyArray(vname, 0, 1)));
        } else {
            pushPostComputeDSPMethod(IB::genControlInst(ccs, generateShiftArray(vname, mxd)));
        }

    } else {
        if (mxd < gGlobal->gMaskDelayLineThreshold) {
            int N = pow2limit(mxd + 1);
            ensureIotaCode();

            // Generates table init
            pushClearMethod(generateInitArray(vname, ctype, N));

            // Generate table use
            if (gGlobal->gComputeIOTA) {  // Ensure IOTA base fixed delays are computed once
                if (fIOTATable.find(N) == fIOTATable.end()) {
                    string   iota_name = subst("i$0", gGlobal->getFreshID(fCurrentIOTA + "_temp"));
                    FIRIndex value2 =
                        FIRIndex(IB::genLoadStructVar(fCurrentIOTA)) & FIRIndex(N - 1);

                    pushPreComputeDSPMethod(
                        IB::genDecStackVar(iota_name, Typed::kInt32, IB::genInt32NumInst(0)));
                    pushComputeDSPMethod(
                        IB::genControlInst(ccs, IB::genStoreStackVar(iota_name, value2)));

                    fIOTATable[N] = iota_name;
                }

                pushComputeDSPMethod(IB::genControlInst(
                    ccs,
                    IB::genStoreArrayStructVar(vname, IB::genLoadStackVar(fIOTATable[N]), exp)));

            } else {
                FIRIndex value2 = FIRIndex(IB::genLoadStructVar(fCurrentIOTA)) & FIRIndex(N - 1);
                pushComputeDSPMethod(
                    IB::genControlInst(ccs, IB::genStoreArrayStructVar(vname, value2, exp)));
            }
        } else {
            // 'select' based delay
            string widx_tmp_name = vname + "_widx_tmp";
            string widx_name     = vname + "_widx";

            // Generates table write index
            pushDeclare(IB::genDecStructVar(widx_name, IB::genInt32Typed()));
            pushInitMethod(IB::genStoreStructVar(widx_name, IB::genInt32NumInst(0)));

            // Generates table init
            pushClearMethod(generateInitArray(vname, ctype, mxd + 1));

            // int w = widx;
            pushComputeDSPMethod(IB::genControlInst(
                ccs,
                IB::genDecStackVar(widx_tmp_name, Typed::kInt32, IB::genLoadStructVar(widx_name))));

            // dline[w] = v;
            pushComputeDSPMethod(IB::genControlInst(
                ccs, IB::genStoreArrayStructVar(vname, IB::genLoadStackVar(widx_tmp_name), exp)));

            // w = w + 1;
            FIRIndex widx_tmp1 = FIRIndex(IB::genLoadStackVar(widx_tmp_name));
            pushPostComputeDSPMethod(
                IB::genControlInst(ccs, IB::genStoreStackVar(widx_tmp_name, widx_tmp1 + 1)));

            // w = ((w == delay) ? 0 : w);
            FIRIndex widx_tmp2 = FIRIndex(IB::genLoadStackVar(widx_tmp_name));
            pushPostComputeDSPMethod(IB::genControlInst(
                ccs, IB::genStoreStackVar(widx_tmp_name,
                                          IB::genSelect2Inst(widx_tmp2 == FIRIndex(mxd + 1),
                                                             FIRIndex(0), widx_tmp2))));
            // *widx = w
            pushPostComputeDSPMethod(IB::genControlInst(
                ccs, IB::genStoreStructVar(widx_name, IB::genLoadStackVar(widx_tmp_name))));
        }
    }

    return exp;
}

/**
 * Generate code for a unique IOTA variable increased at each sample
 * and used to index ring buffers.
 */
void InstructionsCompiler::ensureIotaCode()
{
    if (fCurrentIOTA == "") {
        fCurrentIOTA = gGlobal->getFreshID("IOTA");
        pushDeclare(IB::genDecStructVar(fCurrentIOTA, IB::genInt32Typed()));
        pushClearMethod(IB::genStoreStructVar(fCurrentIOTA, IB::genInt32NumInst(0)));

        FIRIndex value = FIRIndex(IB::genLoadStructVar(fCurrentIOTA)) + 1;
        pushPostComputeDSPMethod(IB::genStoreStructVar(fCurrentIOTA, value));
    }
}

/*****************************************************************************
 WAVEFORM
 *****************************************************************************/

/**
 * Generate code for a waveform. The waveform will be declared as a static field.
 * The name of the waveform is returned in vname and its size in size.
 */

// In gMemoryManager >= 1 mode, all waveform values will be set in staticInit

#define setIntValue(vname, k, i) \
    pushStaticInitMethod(        \
        IB::genStoreArrayStaticStructVar(vname, IB::genInt32NumInst(k), IB::genInt32NumInst(i)));

#define setFloatValue(vname, k, i) \
    pushStaticInitMethod(          \
        IB::genStoreArrayStaticStructVar(vname, IB::genInt32NumInst(k), IB::genFloatNumInst(i)));

#define setDoubleValue(vname, k, i) \
    pushStaticInitMethod(           \
        IB::genStoreArrayStaticStructVar(vname, IB::genInt32NumInst(k), IB::genDoubleNumInst(i)));

void InstructionsCompiler::declareWaveform(Tree sig, string& vname, int& size)
{
    // computes C type and unique name for the waveform
    Typed::VarType ctype;
    getTypedNames(getCertifiedSigType(sig), fContainer->getClassName() + "Wave", ctype, vname);
    size = sig->arity();

    // Declares the waveform
    Typed*     type      = IB::genArrayTyped(ctype, size);
    ValueInst* num_array = IB::genArrayNumInst(ctype, size);

    double r;
    int    i;

    // A waveform contains values of the same type (see sigPromotion)
    if (ctype == Typed::kInt32) {
        Int32ArrayNumInst* int_array = dynamic_cast<Int32ArrayNumInst*>(num_array);
        faustassert(int_array);
        if (gGlobal->gMemoryManager >= 1) {
            for (int k = 0; k < size; k++) {
                isSigInt(sig->branch(k), &i);
                setIntValue(vname, k, i);
            }
        } else {
            for (int k = 0; k < size; k++) {
                isSigInt(sig->branch(k), &i);
                int_array->setValue(k, i);
            }
        }
    } else if (ctype == Typed::kFloat) {
        FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(num_array);
        faustassert(float_array);
        if (gGlobal->gMemoryManager >= 1) {
            for (int k = 0; k < size; k++) {
                isSigReal(sig->branch(k), &r);
                setFloatValue(vname, k, r);
            }
        } else {
            for (int k = 0; k < size; k++) {
                isSigReal(sig->branch(k), &r);
                float_array->setValue(k, float(r));
            }
        }

    } else if (ctype == Typed::kDouble) {
        DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(num_array);
        faustassert(double_array);
        if (gGlobal->gMemoryManager >= 1) {
            for (int k = 0; k < size; k++) {
                isSigReal(sig->branch(k), &r);
                setDoubleValue(vname, k, r);
            }
        } else {
            for (int k = 0; k < size; k++) {
                isSigReal(sig->branch(k), &r);
                double_array->setValue(k, r);
            }
        }
    } else if (ctype == Typed::kQuad) {
        QuadArrayNumInst* quad_array = dynamic_cast<QuadArrayNumInst*>(num_array);
        faustassert(quad_array);
        if (gGlobal->gMemoryManager >= 1) {
            for (int k = 0; k < size; k++) {
                isSigReal(sig->branch(k), &r);
                setDoubleValue(vname, k, r);
            }
        } else {
            for (int k = 0; k < size; k++) {
                isSigReal(sig->branch(k), &r);
                quad_array->setValue(k, double(r));
            }
        }
    } else if (ctype == Typed::kFixedPoint) {
        FixedPointArrayNumInst* fx_array = dynamic_cast<FixedPointArrayNumInst*>(num_array);
        faustassert(fx_array);
        if (gGlobal->gMemoryManager >= 1) {
            for (int k = 0; k < size; k++) {
                isSigReal(sig->branch(k), &r);
                setDoubleValue(vname, k, r);
            }
        } else {
            for (int k = 0; k < size; k++) {
                isSigReal(sig->branch(k), &r);
                fx_array->setValue(k, double(r));
            }
        }
    } else {
        faustassert(false);
    }

    if (gGlobal->gWaveformInDSP) {
        // waveform are allocated in the DSP struct
        pushStaticInitMethod(IB::genDecStaticStructVar(vname, type, num_array));
    } else {
        pushGlobalDeclare(IB::genDecConstStaticStructVar(vname, type, num_array));
    }

    string idx = subst("$0_idx", vname);
    pushDeclare(IB::genDecStructVar(idx, IB::genInt32Typed()));
    pushInitMethod(IB::genStoreStructVar(idx, IB::genInt32NumInst(0)));
}

ValueInst* InstructionsCompiler::generateWaveform(Tree sig)
{
    string vname;
    int    size;

    declareWaveform(sig, vname, size);

    string   idx   = subst("$0_idx", vname);
    FIRIndex index = (FIRIndex(1) + IB::genLoadStructVar(idx)) % FIRIndex(size);
    pushPostComputeDSPMethod(
        IB::genControlInst(getConditionCode(sig), IB::genStoreStructVar(idx, index)));
    return generateCacheCode(sig,
                             IB::genLoadArrayStaticStructVar(vname, IB::genLoadStructVar(idx)));
}

//=============================== BUILD USER INTERFACE METHOD ===============================

/**
 * Generate buildUserInterface corresponding to user interface element t
 */
void InstructionsCompiler::generateUserInterfaceTree(Tree t, bool root)
{
    Tree label, elements, varname, sig;

    if (isUiFolder(t, label, elements)) {
        OpenboxInst::BoxType orient = static_cast<OpenboxInst::BoxType>(tree2int(left(label)));
        // Empty labels will be renamed with a 0xABCD (address) that is ignored and not
        // displayed by UI architectures
        string str = tree2str(right(label));

        // extract metadata from group label str resulting in a simplifiedLabel
        // and metadata declarations for fictive zone at address 0
        string                   simplifiedLabel;
        map<string, set<string>> metadata;
        extractMetadata(str, simplifiedLabel, metadata);

        // add metadata if any
        for (const auto& i : metadata) {
            const string&      key    = i.first;
            const set<string>& values = i.second;
            for (const auto& j : values) {
                pushUserInterfaceMethod(
                    IB::genAddMetaDeclareInst("0", rmWhiteSpaces(key), rmWhiteSpaces(j)));
            }
        }
        // At root level and if label is empty, use the name kept in "metadata" (either
        // the one coded in 'declare name "XXX";' line, or the filename)
        string group = (root && (simplifiedLabel == ""))
                           ? unquote(tree2str(*(gGlobal->gMetaDataSet[tree("name")].begin())))
                           : checkNullLabel(t, simplifiedLabel);

        pushUserInterfaceMethod(IB::genOpenboxInst(group, orient));
        generateUserInterfaceElements(elements);
        pushUserInterfaceMethod(IB::genCloseboxInst());
    } else if (isUiWidget(t, label, varname, sig)) {
        generateWidgetCode(label, varname, sig);
    } else {
        cerr << "ASSERT : user interface generation\n";
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
    Tree                     path, c, x, y, z;
    map<string, set<string>> metadata;
    string                   label, url;

    extractMetadata(tree2str(fulllabel), label, metadata);

    // Extract "url" metadata to be given as parameter to 'addSoundfile' function
    if (isSigSoundfile(sig, path)) {
        for (const auto& i : metadata) {
            const string&      key    = i.first;
            const set<string>& values = i.second;
            for (const auto& j : values) {
                if (key == "url") {
                    url = prepareURL(j);
                } else if (gGlobal->isPythonBackend()) {
                    // The NNX/Linen backends forward widget metadata (e.g.
                    // [param:1]) to the generated add_soundfile call; other
                    // backends drop non-url soundfile metadata.
                    pushUserInterfaceMethod(IB::genAddMetaDeclareInst(
                        tree2str(varname), rmWhiteSpaces(key), rmWhiteSpaces(j)));
                }
            }
        }
    } else {
        // Add metadata if any
        for (const auto& i : metadata) {
            const string&      key    = i.first;
            const set<string>& values = i.second;
            for (const auto& j : values) {
                pushUserInterfaceMethod(IB::genAddMetaDeclareInst(
                    tree2str(varname), rmWhiteSpaces(key), rmWhiteSpaces(j)));
            }
        }
    }

    if (isSigButton(sig, path)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(
            IB::genAddButtonInst(checkNullLabel(varname, label), tree2str(varname)));

    } else if (isSigCheckbox(sig, path)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(
            IB::genAddCheckbuttonInst(checkNullLabel(varname, label), tree2str(varname)));

    } else if (isSigVSlider(sig, path, c, x, y, z)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(IB::genAddVerticalSliderInst(
            checkNullLabel(varname, label), tree2str(varname), tree2double(c), tree2double(x),
            tree2double(y), tree2double(z)));

    } else if (isSigHSlider(sig, path, c, x, y, z)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(IB::genAddHorizontalSliderInst(
            checkNullLabel(varname, label), tree2str(varname), tree2double(c), tree2double(x),
            tree2double(y), tree2double(z)));

    } else if (isSigNumEntry(sig, path, c, x, y, z)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(
            IB::genAddNumEntryInst(checkNullLabel(varname, label), tree2str(varname),
                                   tree2double(c), tree2double(x), tree2double(y), tree2double(z)));

    } else if (isSigVBargraph(sig, path, x, y, z)) {
        fContainer->incUIPassiveCount();
        pushUserInterfaceMethod(
            IB::genAddVerticalBargraphInst(checkNullBargraphLabel(varname, label, 1),
                                           tree2str(varname), tree2double(x), tree2double(y)));

    } else if (isSigHBargraph(sig, path, x, y, z)) {
        fContainer->incUIPassiveCount();
        pushUserInterfaceMethod(
            IB::genAddHorizontalBargraphInst(checkNullBargraphLabel(varname, label, 0),
                                             tree2str(varname), tree2double(x), tree2double(y)));

    } else if (isSigSoundfile(sig, path)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(IB::genAddSoundfileInst(checkNullLabel(varname, label),
                                                        ((url == "") ? prepareURL(label) : url),
                                                        tree2str(varname)));

    } else {
        cerr << "ASSERT : generating widget code\n";
        faustassert(false);
    }
}

//================================== USER INTERFACE MACROS ================================
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
        if (str.length() > 0) {
            pathname2 += str + "/";
        }
        generateMacroInterfaceElements(pathname2, elements);
    } else if (isUiWidget(t, label, varname, sig)) {
        generateWidgetMacro(pathname, label, varname, sig);
    } else {
        cerr << "ASSERT : user interface macro generation\n";
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
void InstructionsCompiler::generateWidgetMacro(const string& pathname, Tree fulllabel, Tree varname,
                                               Tree sig)
{
    Tree                     path, c, x, y, z;
    string                   label;
    map<string, set<string>> metadata;

    extractMetadata(tree2str(fulllabel), label, metadata);
    string pathlabel = pathname + label;
    string rawlabel  = label;
    replace(rawlabel.begin(), rawlabel.end(), ' ', '_');

    if (isSigButton(sig, path)) {
        fContainer->addUIMacro(subst("FAUST_ADDBUTTON(\"$0\", $1);", pathlabel, tree2str(varname)));
        fContainer->addUIMacroActives(subst("p(BUTTON, $0, \"$1\", $2, $3, $4, $5, $6) \\",
                                            rawlabel, pathlabel, tree2str(varname), T(0.), T(0.),
                                            T(1.0), T(1.0)));

    } else if (isSigCheckbox(sig, path)) {
        fContainer->addUIMacro(
            subst("FAUST_ADDCHECKBOX(\"$0\", $1);", pathlabel, tree2str(varname)));
        fContainer->addUIMacroActives(subst("p(CHECKBOX, $0, \"$1\", $2, $3, $4, $5, $6) \\",
                                            rawlabel, pathlabel, tree2str(varname), T(0.), T(0.),
                                            T(1.0), T(1.0)));

    } else if (isSigVSlider(sig, path, c, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDVERTICALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
                                     pathlabel, tree2str(varname), T(tree2double(c)),
                                     T(tree2double(x)), T(tree2double(y)), T(tree2double(z))));
        fContainer->addUIMacroActives(subst("p(VERTICALSLIDER, $0, \"$1\", $2, $3, $4, $5, $6) \\",
                                            rawlabel, pathlabel, tree2str(varname),
                                            T(tree2double(c)), T(tree2double(x)), T(tree2double(y)),
                                            T(tree2double(z))));

    } else if (isSigHSlider(sig, path, c, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDHORIZONTALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
                                     pathlabel, tree2str(varname), T(tree2double(c)),
                                     T(tree2double(x)), T(tree2double(y)), T(tree2double(z))));
        fContainer->addUIMacroActives(
            subst("p(HORIZONTALSLIDER, $0, \"$1\", $2, $3, $4, $5, $6) \\", rawlabel, pathlabel,
                  tree2str(varname), T(tree2double(c)), T(tree2double(x)), T(tree2double(y)),
                  T(tree2double(z))));

    } else if (isSigNumEntry(sig, path, c, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDNUMENTRY(\"$0\", $1, $2, $3, $4, $5);", pathlabel,
                                     tree2str(varname), T(tree2double(c)), T(tree2double(x)),
                                     T(tree2double(y)), T(tree2double(z))));
        fContainer->addUIMacroActives(subst("p(NUMENTRY, $0, \"$1\", $2, $3, $4, $5, $6) \\",
                                            rawlabel, pathlabel, tree2str(varname),
                                            T(tree2double(c)), T(tree2double(x)), T(tree2double(y)),
                                            T(tree2double(z))));

    } else if (isSigVBargraph(sig, path, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDVERTICALBARGRAPH(\"$0\", $1, $2, $3);", pathlabel,
                                     tree2str(varname), T(tree2double(x)), T(tree2double(y))));
        fContainer->addUIMacroPassives(
            subst("p(VERTICALBARGRAPH, $0, \"$1\", $2, 0.0, $3, $4, 0.0) \\", rawlabel, pathlabel,
                  tree2str(varname), T(tree2double(x)), T(tree2double(y))));

    } else if (isSigHBargraph(sig, path, x, y, z)) {
        fContainer->addUIMacro(subst("FAUST_ADDHORIZONTALBARGRAPH(\"$0\", $1, $2, $3);", pathlabel,
                                     tree2str(varname), T(tree2double(x)), T(tree2double(y))));
        fContainer->addUIMacroPassives(
            subst("p(HORIZONTALBARGRAPH, $0, \"$1\", $2, 0.0, $3, $4, 0.0) \\", rawlabel, pathlabel,
                  tree2str(varname), T(tree2double(x)), T(tree2double(y))));

    } else if (isSigSoundfile(sig, path)) {
        fContainer->addUIMacro(
            subst("FAUST_ADDSOUNDFILE(\"$0\", $1);", pathlabel, tree2str(varname)));

    } else {
        cerr << "ASSERT : generating widget code\n";
        faustassert(false);
    }
}

// =========================================
// Special version for -fx mode compilation
// =========================================

ValueInst* InstructionsFXCompiler::castFX(Tree sig, ValueInst* value)
{
    ::Type type = getCertifiedSigType(sig);
    if (type->nature() == kReal) {
        return IB::genCastInst(value, genFloatType(type));
    } else {
        return value;
    }
}

ValueInst* InstructionsFXCompiler::genCastedInput(ValueInst* value)
{
    // In -fx mode, inputs are properly casted with the 'castFX' method
    return value;
}

// Generate FixedTyped
BasicTyped* InstructionsFXCompiler::genFloatType(::Type type)
{
    itv::interval it = type->getInterval();
    return IB::genFixedTyped(it.msb(), it.lsb(), (it.lo() < 0));
}

ValueInst* InstructionsFXCompiler::generateCacheCode(Tree sig, ValueInst* inst)
{
    return InstructionsCompiler::generateCacheCode(sig, castFX(sig, inst));
}

/*
ValueInst* InstructionsFXCompiler::generateXtended(Tree sig)
{
    return castFX(sig, InstructionsCompiler::generateXtended(sig));
}
*/
ValueInst* InstructionsFXCompiler::generateRealNumber(Tree sig, double num)
{
    return castFX(sig, InstructionsCompiler::generateRealNumber(sig, num));
}

/*
ValueInst* InstructionsFXCompiler::generateWaveform(Tree sig)
{
    return castFX(sig, InstructionsCompiler::generateWaveform(sig));
}

ValueInst* InstructionsFXCompiler::generateInput(Tree sig, int input)
{
    return castFX(sig, InstructionsCompiler::generateInput(sig, input));
}

ValueInst* InstructionsFXCompiler::generateDelay(Tree sig, Tree x, Tree y)
{
    return castFX(sig, InstructionsCompiler::generateDelay(sig, x, y));
}

ValueInst* InstructionsFXCompiler::generatePrefix(Tree sig, Tree x, Tree y)
{
    return castFX(sig, InstructionsCompiler::generatePrefix(sig, x, y));
}

ValueInst* InstructionsFXCompiler::generateBinOp(Tree sig, int op, Tree x, Tree y)
{
    return castFX(sig, InstructionsCompiler::generateBinOp(sig, op, x, y));
}

ValueInst* InstructionsFXCompiler::generateFFun(Tree sig, Tree ff, Tree largs)
{
    return castFX(sig, InstructionsCompiler::generateFFun(sig, ff, largs));
}

ValueInst* InstructionsFXCompiler::generateFConst(Tree sig, Tree type, const string&
file, const string& name)
{
    return castFX(sig, InstructionsCompiler::generateFConst(sig, type, file, name));
}

ValueInst* InstructionsFXCompiler::generateFVar(Tree sig, Tree type, const string& file,
const string& name)
{
    return castFX(sig, InstructionsCompiler::generateFVar(sig, type, file, name));
}

ValueInst* InstructionsFXCompiler::generateTable(Tree sig, Tree x, Tree y)
{
    return castFX(sig, InstructionsCompiler::generateTable(sig, x, y));
}

ValueInst* InstructionsFXCompiler::generateRDTbl(Tree sig, Tree x, Tree y)
{
    return castFX(sig, InstructionsCompiler::generateRDTbl(sig, x, y));
}

ValueInst* InstructionsFXCompiler::generateSigGen(Tree sig, Tree x)
{
    return castFX(sig, InstructionsCompiler::generateSigGen(sig, x));
}
*/

ValueInst* InstructionsFXCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    // Cond is of type kInt
    ValueInst* cond = CS(sel);

    /*
    ValueInst* v1 = CS(s1);
    ValueInst* v2 = CS(s2);
    itv::interval it1 = getCertifiedSigType(s1)->getInterval();
    itv::interval it2 = getCertifiedSigType(s2)->getInterval();
    itv::interval it3 = getCertifiedSigType(sig)->getInterval();
    // Cast the branch different from select2 expression type
    if (it1.to_string() != it3.to_string()) {
        v1 = castFX(sig, v1);
    }
    if (it2.to_string() != it3.to_string()) {
        v2 = castFX(sig, v2);
    }
    */
    ValueInst* v1 = castFX(sig, CS(s1));
    ValueInst* v2 = castFX(sig, CS(s2));

    return generateSelect2Aux(sig, s1, s2, cond, v1, v2);
}

/*
ValueInst* InstructionsFXCompiler::generateRecProj(Tree sig, Tree x, int proj)
{
    return castFX(sig, InstructionsCompiler::generateRecProj(sig, x, proj));
}

ValueInst* InstructionsFXCompiler::generateFloatCast(Tree sig, Tree x)
{
    return castFX(sig, InstructionsCompiler::generateFloatCast(sig, x));
}

ValueInst* InstructionsFXCompiler::generateButtonAux(Tree sig, Tree path, const string&
name)
{
    return castFX(sig, InstructionsCompiler::generateButtonAux(sig, path, name));
}

ValueInst* InstructionsFXCompiler::generateSliderAux(Tree sig, Tree path, Tree cur,
const string& name)
{
    return castFX(sig, InstructionsCompiler::generateSliderAux(sig, path, cur, name));
}

ValueInst* InstructionsFXCompiler::generateBargraphAux(Tree sig, Tree path, ValueInst*
exp, const string& name)
{
    return castFX(sig, InstructionsCompiler::generateBargraphAux(sig, path, exp, name));
}

ValueInst* InstructionsFXCompiler::generateAttach(Tree sig, Tree x, Tree y)
{
    return castFX(sig, InstructionsCompiler::generateAttach(sig, x, y));
}
*/

/**
 * Generate code for a group of mutually recursive definitions
 */
ValueInst* InstructionsFXCompiler::generateRec(Tree sig, Tree var, Tree le, int index)
{
    int N = len(le);

    ValueInst*          res = nullptr;
    vector<bool>        used(N);
    vector<int>         delay(N);
    vector<string>      vname(N);
    vector<BasicTyped*> ctype(N);
    vector<Tree>        vsig(N);

    // Prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        vsig[i] = sigProj(i, sig);  // recreate each recursive definition
        if (fOccMarkup->retrieve(vsig[i])) {
            // This projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(vsig[i]), "Rec", ctype[i], vname[i]);
            setVectorNameProperty(vsig[i], vname[i]);
            delay[i] = fOccMarkup->retrieve(vsig[i])->getMaxDelay();
        } else {
            // This projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }

    // Generate delayline for each element of a recursive definition
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            Address::AccessType access;
            ValueInst*          ccs = getConditionCode(nth(le, i));
            if (index == i) {
                // Explicit cast in the projection type
                res = generateDelayLine(castFX(vsig[i], CS(nth(le, i))), ctype[i], vname[i],
                                        delay[i], access, ccs);
            } else {
                // Explicit cast in the projection type
                generateDelayLine(castFX(vsig[i], CS(nth(le, i))), ctype[i], vname[i], delay[i],
                                  access, ccs);
            }
        }
    }

    return res;
}
