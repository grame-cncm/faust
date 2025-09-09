/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2025 GRAME, Centre National de Creation Musicale
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

#include "signalFIRCompiler.hh"
#include "compatibility.hh"  // For basename, pathToContent
#include "xtended.hh"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//-------------------------SignalFIRCompiler-------------------------------
//
// SignalFIRCompiler is designed to directly compile signals. The compilation process is divided
// into two main stages:
//
// 1) Preparation Stage (SignalBuilder). The SignalBuilder class traverses all output signal trees
// to:
//      - Allocate delay lines (both integer and real types) for sample-accurate delays and
//      recursive constructs.
//      - Allocate tables (both integer and real types) required for table-based signal generation.
//      - Collect and configure input and output control signals (e.g., sliders, buttons,
//      bargraphs).
//
// 2) Compilation Stage (SignalFIRCompiler). The SignalFIRCompiler class:
//      - Traverses all output signal trees.
//      - Compile the value of each output signal sample by recursively compiling the expression
//      tree.
//      - Uses a value stack to manage intermediate compilation results.
//
// After SignalBuilder has prepared the signal trees, the tables are precompiled once during
// the initialization phase via the `compileTables` method.
//
// `compile()` iterates over every output in the linked list `fOutputSig`.
// * For each signal it:
// * 1. Recursively traverses the expression tree with `self()`.
// * 2. Retrieves the resulting FIR value from `fValueStack`.
// * 3. Stores that value in the outputs.
//
//----------------------------------------------------------------------

void SignalFIRCompiler::compileXtended(Tree sig, xtended* xt)
{
    list<ValueInst*>       args;
    vector<Typed::VarType> atypes;
    int                    rtype = getCertifiedSigType(sig)->nature();
    // Compiles all arguments
    for (Tree b : sig->branches()) {
        self(b);
        args.push_back(popRes());
        atypes.push_back(convert2FIRType(getCertifiedSigType(b)->nature()));
    }
    // Compiles the function declaration
    fGlobalBlock->pushBackInst(IB::genFunction(xt->fname(rtype), convert2FIRType(rtype), atypes));
    // Compiles the function call
    pushRes(IB::genFunCallInst(xt->fname(rtype), args));
}

void SignalFIRCompiler::compileSigInt(Tree sig, int i_val)
{
    pushRes(IB::genInt32NumInst(i_val));
}

void SignalFIRCompiler::compileSigInt64(Tree sig, int64_t i64_val)
{
    pushRes(IB::genInt32NumInst(i64_val));
}

void SignalFIRCompiler::compileSigReal(Tree sig, double r_val)
{
    pushRes(IB::genRealNumInst(itfloat(), r_val));
}

void SignalFIRCompiler::compileSigInput(Tree sig, int idx)
{
    ValueInst* res =
        IB::genLoadArrayStackVar(subst("input$0", T(idx)), IB::genLoadLoopVar("sample"));
    pushRes(res);
}

void SignalFIRCompiler::compileSigOutput(Tree sig, int i_val, Tree x_tree)
{
    self(x_tree);  // Evaluate the expression connected to the output
}

void SignalFIRCompiler::compileSigDelay1(Tree sig, Tree x_tree)
{
    self(x_tree);
    ValueInst* v1  = popRes();
    ValueInst* one = IB::genInt32NumInst(1);
    pushRes(writeReadDelay(x_tree, v1, one));
}

void SignalFIRCompiler::compileSigDelay(Tree sig, Tree x_tree, Tree y_tree)
{
    if (isZeroDelay(y_tree)) {
        self(x_tree);
    } else {
        self(x_tree);
        ValueInst* v1 = popRes();
        self(y_tree);
        ValueInst* v2 = popRes();
        pushRes(writeReadDelay(x_tree, v1, v2));
    }
}

void SignalFIRCompiler::compileSigSelect2(Tree sig, Tree sel, Tree x_tree, Tree y_tree)
{
    // Interpret the condition and both branches
    self(sel);
    ValueInst* sel_val = popRes();
    self(x_tree);
    ValueInst* x_val = popRes();
    self(y_tree);
    ValueInst* y_val = popRes();
    // Inverted
    pushRes(IB::genSelect2Inst(sel_val, y_val, x_val));
}

void SignalFIRCompiler::compileSigPrefix(Tree sig, Tree x_tree, Tree y_tree)
{
    /*
     // Generate a condition: if (fIOTA == 0) use x, else use y
     ValueInst* iota_zero = IB::genEq(loadIOTA(), IB::genInt32NumInst(0));
     // Compile both branches
     self(x_tree);
     ValueInst* init_val = popRes();
     self(y_tree);
     ValueInst* next_val = popRes();
     // Select between init_val and next_val
     pushRes(IB::genSelect2Inst(iota_zero, init_val, next_val));
     */
    /*
     // TODO
     self(y_tree);
     if (fIOTA == 0) {
     self(x_tree);
     }
     */
    self(y_tree);
}

void SignalFIRCompiler::compileSigBinOp(Tree sig, int opt_op, Tree x_tree, Tree y_tree)
{
    self(x_tree);
    ValueInst* v1 = popRes();
    self(y_tree);
    ValueInst* v2 = popRes();
    if ((opt_op == kMul) && isMinusOne(x_tree)) {
        pushRes(IB::genNeg(v2));
    } else if ((opt_op == kMul) && isMinusOne(y_tree)) {
        pushRes(IB::genNeg(v1));
    } else {
        pushRes(IB::genBinopInst(opt_op, v1, v2));
    }
}

void SignalFIRCompiler::compileSigFConst(Tree sig, Tree type_tree, Tree name_tree, Tree file_tree)
{
    // Special case for SR constant
    if (string(tree2str(name_tree)) == "fSamplingFreq") {
        pushRes(IB::genLoadStructVar("fSampleRate"));
    } else {
        // TODO
        faustassert(false);
        pushRes(IB::genTypedZero(itfloat()));
    }
}

void SignalFIRCompiler::compileSigWRTbl(Tree sig, Tree size_tree, Tree gen_tree, Tree wi_tree,
                                        Tree ws_tree)
{
    if (isNil(wi_tree)) {
        // Nothing
    } else {
        self(wi_tree);
        ValueInst* write_idx = popRes();
        self(ws_tree);
        ValueInst* val = popRes();
        writeTable(sig, write_idx, val);
    }
}

void SignalFIRCompiler::compileSigRDTbl(Tree sig, Tree tbl_tree, Tree ri_tree)
{
    // Compiles table
    self(tbl_tree);
    // Then compile the access
    self(ri_tree);
    ValueInst* read_idx = popRes();
    pushRes(readTable(tbl_tree, read_idx));
}

void SignalFIRCompiler::compileSigGen(Tree sig, Tree x_tree)
{
    if (fVisitGen) {
        self(x_tree);
    } else {
        pushRes(IB::genTypedZero(itfloat()));
    }
}

void SignalFIRCompiler::compileSigWaveform(Tree sig)
{
    // Modulo based access in the waveform
    // int size  = sig->arity();
    // int index = fIOTA % size;
    // self(sig->branch(index));
    // TODO
    self(sig->branch(0));
}

void SignalFIRCompiler::compileProjRec(Tree sig, int proj_idx, Tree rec_expr_tree, Tree rec_vars,
                                       Tree rec_exprs)
{
    // First visit of the recursive signal
    if (fVisited.find(sig) == fVisited.end()) {
        faustassert(isRec(rec_expr_tree, rec_vars, rec_exprs));
        fVisited[sig]++;
        // Render the actual projection
        self(nth(rec_exprs, proj_idx));
        ValueInst* res = popRes();
        /*
         if (global::isDebug("SIG_RENDERER")) {
         std::cout << "Proj : " << res << "\n";
         }
         */
        ValueInst* zero = IB::genInt32NumInst(0);
        pushRes(writeReadDelay(sig, res, zero));

    } else {
        /*
         if (global::isDebug("SIG_RENDERER")) {
         std::cout << "SignalFIRCompiler : next visit of the recursive signal\n";
         }
         */
        ValueInst* zero = IB::genInt32NumInst(0);
        pushRes(readDelay(sig, zero));
    }
}

void SignalFIRCompiler::compileSigIntCast(Tree sig, Tree x_tree)
{
    self(x_tree);
    ValueInst* cur = popRes();
    pushRes(IB::genCastInt32Inst(cur));
}

void SignalFIRCompiler::compileSigBitCast(Tree sig, Tree x_tree)
{
    // Bitcast is complex. For a simple renderer, it might be an identity if types are
    // "close enough" or a reinterpretation of bits (e.g., float bits as int). This renderer
    // doesn't have type info readily on Node to do a true bitcast. Assuming it's a numeric
    // pass-through for now.
    self(x_tree);
}

void SignalFIRCompiler::compileSigFloatCast(Tree sig, Tree x_tree)
{
    self(x_tree);
    ValueInst* cur = popRes();
    pushRes(IB::genCastInst(cur, IB::genBasicTyped(itfloat())));
}

void SignalFIRCompiler::compileSigButton(Tree sig, Tree label_tree)
{
    pushRes(fInputControls[sig].getValue());
}

void SignalFIRCompiler::compileSigCheckbox(Tree sig, Tree label_tree)
{
    pushRes(fInputControls[sig].getValue());
}

void SignalFIRCompiler::compileSigVSlider(Tree sig, Tree label_tree, Tree c_tree, Tree x_tree,
                                          Tree y_tree, Tree z_tree)
{
    pushRes(fInputControls[sig].getValue());
}

void SignalFIRCompiler::compileSigHSlider(Tree sig, Tree label_tree, Tree c_tree, Tree x_tree,
                                          Tree y_tree, Tree z_tree)
{
    pushRes(fInputControls[sig].getValue());
}

void SignalFIRCompiler::compileSigNumEntry(Tree sig, Tree label_tree, Tree c_tree, Tree x_tree,
                                           Tree y_tree, Tree z_tree)
{
    pushRes(fInputControls[sig].getValue());
}

void SignalFIRCompiler::compileSigVBargraph(Tree sig, Tree label_tree, Tree x_tree, Tree y_tree,
                                            Tree z_tree)
{
    self(z_tree);
    ValueInst* val = topRes();
    writeStatement(z_tree, fOutputControls[sig].setValue(val));
}

void SignalFIRCompiler::compileSigHBargraph(Tree sig, Tree label_tree, Tree x_tree, Tree y_tree,
                                            Tree z_tree)
{
    self(z_tree);
    ValueInst* val = topRes();
    writeStatement(z_tree, fOutputControls[sig].setValue(val));
}

void SignalFIRCompiler::compileSigSoundfile(Tree sig, Tree label_tree)
{
    // TODO: Implement soundfile reading. Requires state management for file handlers,
    // position, etc.
    pushRes(IB::genTypedZero(itfloat()));
}

void SignalFIRCompiler::compileSigSoundfileLength(Tree sig, Tree sf_tree, Tree x_tree)
{
    // TODO
    self(sf_tree);
    popRes();
    self(x_tree);
    popRes();
    pushRes(IB::genTypedZero(itfloat()));
}

void SignalFIRCompiler::compileSigSoundfileRate(Tree sig, Tree sf_tree, Tree x_tree)
{
    // TODO
    self(sf_tree);
    popRes();
    self(x_tree);
    popRes();
    pushRes(IB::genTypedZero(itfloat()));
}

void SignalFIRCompiler::compileSigSoundfileBuffer(Tree sig, Tree sf_tree, Tree x_tree, Tree y_tree,
                                                  Tree z_tree)
{
    // TODO
    self(sf_tree);
    popRes();
    self(x_tree);
    popRes();
    self(y_tree);
    popRes();
    self(z_tree);
    popRes();
    pushRes(IB::genTypedZero(itfloat()));
}

void SignalFIRCompiler::compileSigAttach(Tree sig, Tree x_tree, Tree y_tree)
{
    // Interpret second arg then drop it
    self(y_tree);
    popRes();
    // And return the first one
    self(x_tree);
}

void SignalFIRCompiler::compileSigEnable(Tree sig, Tree x_tree, Tree y_tree)
{
    // x_tree is condition, y_tree is signal
    self(x_tree);
    Node enable = popRes();
    if (enable.getInt() != 0) {
        self(y_tree);
    } else {
        pushRes(IB::genTypedZero(itfloat()));
    }
}

void SignalFIRCompiler::compileSigControl(Tree sig, Tree x_tree, Tree y_tree)
{
    // x_tree is name, y_tree is signal
    self(y_tree);
}

/**
 * @brief Visits a signal tree node and recursively compiles its value.
 *
 * This method implements the core compiler logic for the
 * signal graph. It uses a recursive traversal to process each node type,
 * compiles its sub-expressions, and produce the resulting FIR value. The
 * intermediate results are stored on a value stack (`fValueStack`).
 *
 * The method supports a wide variety of Faust signal constructs, including:
 * - Constants (integer, real)
 * - Inputs and outputs
 * - Delay lines and feedback structures
 * - Control structures (sliders, buttons, bargraphs)
 * - Mathematical operations (binary operators, conditional expressions)
 * - Table-based operations (read/write table)
 * - Recursive signals and projections
 *
 * Key implementation notes:
 * - For each recognized node type, it performs the appropriate compilation logic
 * and pushes the result onto the value stack.
 * - For recursive signals (e.g., projections), it uses the `fVisited` map to
 * detect cycles and avoid infinite recursion.
 * - It handles the compilation of user interface controls by compilation loding values
 * from `fInputControls` and updating `fOutputControls`.
 * - For unimplemented or unrecognized nodes, it triggers an assertion failure
 * to ensure correctness.
 *
 * @param sig The signal tree node to compile.
 */
void SignalFIRCompiler::visit(Tree sig)
{
    int     i_val;
    int64_t i64_val;
    double  r_val;
    Tree    size_tree, gen_tree, wi_tree, ws_tree, tbl_tree, ri_tree;
    Tree    c_tree, x_tree, y_tree, z_tree;
    Tree    label_tree, type_tree, name_tree, file_tree, sf_tree, sel;
    Tree    rec_vars, rec_exprs;
    int     opt_op;
    int     proj_idx;

    /*
     if (global::isDebug("SIG_RENDERER")) {
     std::cout << "SignalFIRCompiler : " << ppsig(sig, 64) << std::endl;
     std::cout << "SignalFIRCompiler : fIOTA " << fIOTA << std::endl;
     }
     */

    if (xtended* xt = (xtended*)getUserData(sig)) {
        compileXtended(sig, xt);
    } else if (isSigInt(sig, &i_val)) {
        compileSigInt(sig, i_val);
    } else if (isSigInt64(sig, &i64_val)) {
        compileSigInt64(sig, i64_val);
    } else if (isSigReal(sig, &r_val)) {
        compileSigReal(sig, r_val);
    } else if (isSigInput(sig, &i_val)) {
        compileSigInput(sig, i_val);
    } else if (isSigOutput(sig, &i_val, x_tree)) {
        compileSigOutput(sig, i_val, x_tree);
    } else if (isSigDelay1(sig, x_tree)) {
        compileSigDelay1(sig, x_tree);
    } else if (isSigDelay(sig, x_tree, y_tree)) {
        compileSigDelay(sig, x_tree, y_tree);
    } else if (isSigSelect2(sig, sel, x_tree, y_tree)) {
        compileSigSelect2(sig, sel, x_tree, y_tree);
    } else if (isSigPrefix(sig, x_tree, y_tree)) {
        compileSigPrefix(sig, x_tree, y_tree);
    } else if (isSigBinOp(sig, &opt_op, x_tree, y_tree)) {
        compileSigBinOp(sig, opt_op, x_tree, y_tree);
    } else if (isSigFConst(sig, type_tree, name_tree, file_tree)) {
        compileSigFConst(sig, type_tree, name_tree, file_tree);
    } else if (isSigWRTbl(sig, size_tree, gen_tree, wi_tree, ws_tree)) {
        compileSigWRTbl(sig, size_tree, gen_tree, wi_tree, ws_tree);
    } else if (isSigRDTbl(sig, tbl_tree, ri_tree)) {
        compileSigRDTbl(sig, tbl_tree, ri_tree);
    } else if (isSigGen(sig, x_tree)) {
        compileSigGen(sig, x_tree);
    } else if (isSigWaveform(sig)) {
        compileSigWaveform(sig);
    } else if (isProj(sig, &proj_idx, x_tree) && isRec(x_tree, rec_vars, rec_exprs)) {
        compileProjRec(sig, proj_idx, x_tree, rec_vars, rec_exprs);
    } else if (isSigIntCast(sig, x_tree)) {
        compileSigIntCast(sig, x_tree);
    } else if (isSigBitCast(sig, x_tree)) {
        compileSigBitCast(sig, x_tree);
    } else if (isSigFloatCast(sig, x_tree)) {
        compileSigFloatCast(sig, x_tree);
    } else if (isSigButton(sig, label_tree)) {
        compileSigButton(sig, label_tree);
    } else if (isSigCheckbox(sig, label_tree)) {
        compileSigCheckbox(sig, label_tree);
    } else if (isSigVSlider(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        compileSigVSlider(sig, label_tree, c_tree, x_tree, y_tree, z_tree);
    } else if (isSigHSlider(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        compileSigHSlider(sig, label_tree, c_tree, x_tree, y_tree, z_tree);
    } else if (isSigNumEntry(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        compileSigNumEntry(sig, label_tree, c_tree, x_tree, y_tree, z_tree);
    } else if (isSigVBargraph(sig, label_tree, x_tree, y_tree, z_tree)) {
        compileSigVBargraph(sig, label_tree, x_tree, y_tree, z_tree);
    } else if (isSigHBargraph(sig, label_tree, x_tree, y_tree, z_tree)) {
        compileSigHBargraph(sig, label_tree, x_tree, y_tree, z_tree);
    } else if (isSigSoundfile(sig, label_tree)) {
        compileSigSoundfile(sig, label_tree);
    } else if (isSigSoundfileLength(sig, sf_tree, x_tree)) {
        compileSigSoundfileLength(sig, sf_tree, x_tree);
    } else if (isSigSoundfileRate(sig, sf_tree, x_tree)) {
        compileSigSoundfileRate(sig, sf_tree, x_tree);
    } else if (isSigSoundfileBuffer(sig, sf_tree, x_tree, y_tree, z_tree)) {
        compileSigSoundfileBuffer(sig, sf_tree, x_tree, y_tree, z_tree);
    } else if (isSigAttach(sig, x_tree, y_tree)) {
        compileSigAttach(sig, x_tree, y_tree);
    } else if (isSigEnable(sig, x_tree, y_tree)) {
        compileSigEnable(sig, x_tree, y_tree);
    } else if (isSigControl(sig, x_tree, y_tree)) {
        compileSigControl(sig, x_tree, y_tree);
    } else {
        // Default case and recursion
        SignalVisitor::visit(sig);
    }
}

/**
 * @brief Compile the DSP graph for all output signals.
 *
 * This method traverses the list of DSP output signals (`fOutputSig`),
 * compiles each one into a `ValueInst*`, and emits the corresponding
 * store statements into the generated DSP code.
 *
 * Workflow:
 * 1. Clears the `fVisited` set to ensure each signal is compiled only once.
 * 2. Iterates through the list of output signals.
 * 3. For each signal:
 * - Invokes `self(out_sig)` to recursively compile the signal graph.
 * - Retrieves the resulting compiled value from the stack (`popRes()`).
 * - Generates a `StoreVar` instruction to write the computed value to
 * an output slot, applying the appropriate type casting if necessary.
 * 4. Appends the generated statement to the correct DSP block via `writeStatement`.
 *
 * @note Each output is stored in a stack variable named `"output"` with a unique ID.
 * @note This function is responsible for compiling only output signals; inputs and
 * intermediate nodes are compiled as part of the recursive traversal.
 */
void SignalFIRCompiler::compile()
{
    Tree output_list = fOutputSig;
    fVisited.clear();  // Clear visited for each top-level signal evaluation per sample

    while (!isNil(output_list)) {
        // Compile each output
        Tree out_sig = hd(output_list);
        // std::cerr << "compile " << ppsig(out_sig) << std::endl;
        self(out_sig);
        // Get compiled value and store in the output
        ValueInst* res = popRes();
        writeStatement(out_sig, IB::genStoreArrayFunArgsVar(
                                    gGlobal->getFreshID("output"), IB::genLoadLoopVar("sample"),
                                    genCastedOutput(getCertifiedSigType(out_sig)->nature(), res)));
        // Compile next output
        output_list = tl(output_list);
    }

    // fIOTA is used in delays lines
    fSampleBlock->pushBackInst(IB::genStoreStructVar("fIOTA", (FIRIndex(loadIOTA()) + 1)));

    // Close UI block
    fUIBlock->pushBackInst(IB::genCloseboxInst());
}

/**
 * @brief Initializes lookup tables used in the signal graph.
 *
 * This method precomputes all lookup tables (both integer and real-valued)
 * that are defined in the signal expression. It ensures that any table-based
 * signals are filled with their corresponding precomputed values before
 * rendering begins.
 *
 * Implementation details:
 * - Enables the generator flag (`fVisitGen = true`) to allow recursive
 * evaluation of table-generating signals.
 * - Iterates over all integer tables (`fTables`) and computes their
 * contents using `compileSample`.
 * - Resets the generator flag (`fVisitGen = false`) once table initialization
 * is complete.
 *
 * This method must be called once before starting processing
 * to ensure that all table-based signals are correctly initialized.
 */

// TODO: use sub modules
void SignalFIRCompiler::compileTables()
{
    // So that sigGen are properly visited
    fVisitGen = true;

    // Tables
    for (auto& [x, table] : fTables) {
        int          nature = getCertifiedSigType(x)->nature();  // Nature of the signal generator
        std::string  loop_index = (nature == kInt) ? "i_loop" : "r_loop";
        ForLoopInst* loop       = IB::genForLoopInst(loop_index, 0, table.size(), 1);
        ValueInst*   val        = compileSample(table.fSigGen);
        loop->pushFrontInst(table.write(IB::genLoadLoopVar(loop_index), val));

        // Register loop in init block
        fInitBlock->pushFrontInst(loop);
    }

    /*
     // Initialize waveform tables
     for (auto& it : fWaveforms) {
         const Tree& w_sig = it.first;
         TableData& table = it.second;

         // Create a loop to fill the table with waveform samples
         std::string  loop_index = "w_loop";
         ForLoopInst* loop       = IB::genForLoopInst(loop_index, table.size(), 1);

         for (int i = 0; i < table.fSize; i++) {
             // Compile each waveform sample at index i
             ValueInst* value = compileSample(w_sig->branch(i));
             loop->pushBackInst(table.write(IB::genInt32NumInst(i), value));
         }

         // Register loop in init block
         fInitBlock->pushBackInst(loop);
     }
     */

    fVisitGen = false;
}

/**
 * @brief Generates a FIR DSP module instance.
 *
 * This function creates and configures a new `ModuleInst` representing
 * a complete DSP module for FIR signal processing. It sets up all the
 * required functions for:
 * - Input/output management
 * - Sample rate access
 * - Initialization and state reset
 * - DSP compute routine
 *
 * The generated module is fully self-contained and ready for integration
 * into the DSP runtime.
 *
 * @return A pointer to the newly created FIR module.
 */
ModuleInst* SignalFIRCompiler::genFIRModule(const std::string& obj)
{
    // Compile tables
    compileTables();
    // Compile outputs signals to FIR
    compile();

    // Create the FIR module using the generated FIR blocks
    ModuleInst* fir_module = IB::genModuleInst(fModuleName, fDeclareBlock, fGlobalBlock);

    // Metadata
    fir_module->pushFunction(IB::generateMetadata("metadata", obj, true, true, fMetadataBlock));

    // Inputs/outputs
    fir_module->pushFunction(
        IB::generateGetInputs("getNumInputs", obj, true, FunTyped::kDefault, fNumInputs));
    fir_module->pushFunction(
        IB::generateGetInputs("getNumOutputs", obj, true, FunTyped::kDefault, fNumOutputs));

    // SampleRate
    fir_module->pushFunction(IB::generateGetSampleRate("getSampleRate", obj, true, true));

    // Init
    fir_module->pushFunction(IB::generateInit("init", obj, true, true));
    fir_module->pushFunction(IB::generateClassInit("classInit", obj, true, true, fTablesBlock));
    fir_module->pushFunction(IB::generateInstanceInit("instanceInit", obj, true, true));
    fir_module->pushFunction(
        IB::generateInstanceConstants("instanceConstants", obj, true, true, fInitBlock));
    fir_module->pushFunction(IB::generateInstanceResetUserInterface("instanceResetUserInterface",
                                                                    obj, true, true, fResetBlock));
    fir_module->pushFunction(
        IB::generateInstanceClear("instanceClear", obj, true, true, fClearBlock));

    // User Interface
    fir_module->pushFunction(
        IB::generateBuildUserInterace("buildUserInterface", obj, true, true, fUIBlock));

    // Clone
    fir_module->pushFunction(IB::generateClone("clone", fModuleName, true, true));

    // Compute
    Typed* type     = IB::genFloatMacroTyped();
    Typed* ptr_type = IB::genArrayTyped(type, 0);
    for (int index = 0; index < fNumInputs; index++) {
        string name = subst("input$0", T(index));
        fControlBlock->pushFrontInst(IB::genDecStackVar(
            name, ptr_type, IB::genLoadArrayFunArgsVar("inputs", IB::genInt32NumInst(index))));
    }
    for (int index = 0; index < fNumOutputs; index++) {
        string name = subst("output$0", T(index));
        fControlBlock->pushFrontInst(IB::genDecStackVar(
            name, ptr_type, IB::genLoadArrayFunArgsVar("outputs", IB::genInt32NumInst(index))));
    }

    fir_module->pushFunction(
        IB::generateComputeFun("compute", obj, true, true, fControlBlock, fSampleBlock));

    return fir_module;
}
