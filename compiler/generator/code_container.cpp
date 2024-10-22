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

#include <fstream>
#include <string>

#include "code_container.hh"
#include "fir_to_fir.hh"
#include "floats.hh"
#include "global.hh"
#include "instructions_complexity.hh"
#include "recursivness.hh"
#include "struct_manager.hh"
#include "text_instructions.hh"
#include "timing.hh"
#include "type_manager.hh"

using namespace std;

void CodeContainer::initialize(int numInputs, int numOutputs)
{
    fNumInputs  = numInputs;
    fNumOutputs = numOutputs;
}

CodeContainer::CodeContainer()
    : fParentContainer(nullptr),
      fNumInputs(-1),
      fNumOutputs(-1),
      fNumActives(0),
      fNumPassives(0),
      fSubContainerType(kInt),
      fGeneratedSR(false),
      fExtGlobalDeclarationInstructions(IB::genBlockInst()),
      fGlobalDeclarationInstructions(IB::genBlockInst()),
      fDeclarationInstructions(IB::genBlockInst()),
      fControlDeclarationInstructions(IB::genBlockInst()),
      fInitInstructions(IB::genBlockInst()),
      fConstantFromMem(nullptr),
      fConstantToMem(nullptr),
      fResetUserInterfaceInstructions(IB::genBlockInst()),
      fClearInstructions(IB::genBlockInst()),
      fPostInitInstructions(IB::genBlockInst()),
      fAllocateInstructions(IB::genBlockInst()),
      fDestroyInstructions(IB::genBlockInst()),
      fStaticInitInstructions(IB::genBlockInst()),
      fPostStaticInitInstructions(IB::genBlockInst()),
      fStaticDestroyInstructions(IB::genBlockInst()),
      fComputeBlockInstructions(IB::genBlockInst()),
      fPostComputeBlockInstructions(IB::genBlockInst()),
      fComputeFunctions(IB::genBlockInst()),
      fUserInterfaceInstructions(IB::genBlockInst())
{
    fCurLoop = new CodeLoop(0, gGlobal->getFreshID("i"));

    Address::AccessType access;
    if (gGlobal->gMemoryManager == 2) {
        access = Address::kStruct;
    }
    // Special version for SYFALA where iControl/fControl and iZone/fZone have to be parameters
    if (gGlobal->gMemoryManager == 3) {
        access = Address::kFunArgs;
    }

    // iControl/fControl are created when -ec and -mem1/2/3 are used together
    if (gGlobal->gExtControl && gGlobal->gMemoryManager >= 1) {
        fIntControl  = new ControlArray("iControl", access);
        fRealControl = new ControlArray("fControl", access);
    } else {
        fIntControl  = nullptr;
        fRealControl = nullptr;
    }

    // Memory handling with gMemoryManager
    if (gGlobal->gMemoryManager >= 1 && !gGlobal->gIntZone && !gGlobal->gRealZone) {
        // Allocation done once to be shared by all containers
        ZoneArray::gInternalMemorySize = gGlobal->gFPGAMemory;
        gGlobal->gIntZone              = new ZoneArray("iZone", access, Typed::kInt32, 4);
        gGlobal->gRealZone             = new ZoneArray("fZone", access, itfloat(), 4);
    }
}

int ZoneArray::gInternalMemorySize = 0;

CodeContainer::~CodeContainer()
{
}

void CodeContainer::transformDAG(DispatchVisitor* visitor)
{
    lclgraph G;
    CodeLoop::sortGraph(fCurLoop, G);
    for (int l = int(G.size() - 1); l >= 0; l--) {
        for (const auto& p : G[l]) {
            p->transform(visitor);
        }
    }
}

/**
 * Store the loop used to compute a signal
 */
void CodeContainer::setLoopProperty(Tree sig, CodeLoop* l)
{
    fLoopProperty.set(sig, l);
}

/**
 * Returns the loop used to compute a signal
 */
bool CodeContainer::getLoopProperty(Tree sig, CodeLoop*& l)
{
    faustassert(sig);
    return fLoopProperty.get(sig, l);
}

void CodeContainer::listAllLoopProperties(Tree sig, set<CodeLoop*>& L, set<Tree>& visited)
{
    if (visited.count(sig) == 0) {
        visited.insert(sig);
        CodeLoop* l;
        if (getLoopProperty(sig, l)) {
            L.insert(l);
        } else {
            // we go down the expression
            tvec subsigs;
            int  n = getSubSignals(sig, subsigs, false);
            for (int i = 0; i < n; i++) {
                listAllLoopProperties(subsigs[i], L, visited);
            }
        }
    }
}

/**
 * Open a non-recursive loop on top of the stack of open loops.
 * @param size the number of iterations of the loop
 */
void CodeContainer::openLoop(const string& index_name, int size)
{
    fCurLoop = new CodeLoop(fCurLoop, index_name, size);
}

/**
 * Open a recursive loop on top of the stack of open loops.
 * @param recsymbol the recursive symbol defined in this loop
 * @param size the number of iterations of the loop
 */
void CodeContainer::openLoop(Tree recsymbol, const string& index_name, int size)
{
    fCurLoop = new CodeLoop(recsymbol, fCurLoop, index_name, size);
}

/**
 * Close the top loop and either keep it
 * or absorb it within its enclosing loop.
 */
void CodeContainer::closeLoop(Tree sig)
{
    faustassert(fCurLoop);

    // fix the missing dependencies
    set<CodeLoop*> L;
    set<Tree>      V;
    listAllLoopProperties(sig, L, V);
    for (CodeLoop* l : L) {
        fCurLoop->fBackwardLoopDependencies.insert(l);
    }

    CodeLoop* l = fCurLoop;
    fCurLoop    = l->fEnclosingLoop;
    faustassert(fCurLoop);

    Tree S = symlist(sig);
    if (l->isEmpty() || fCurLoop->hasRecDependencyIn(S)) {
        fCurLoop->absorb(l);
    } else {
        // cout << " will NOT absorb" << endl;
        // we have an independent loop
        setLoopProperty(sig, l);  // associate the signal
        fCurLoop->fBackwardLoopDependencies.insert(l);
        // we need to indicate that all recursive symbols defined
        // in this loop are defined in this loop
        for (Tree lsym = l->fRecSymbolSet; !isNil(lsym); lsym = tl(lsym)) {
            this->setLoopProperty(hd(lsym), l);
            // cerr << "loop " << l << " defines " << *hd(lsym) << endl;
        }
    }
}

/**
 * Print the required C++ libraries as comments in source code
 */
void CodeContainer::printLibrary(ostream& fout)
{
    set<string>           S;
    set<string>::iterator f;

    string sep;
    collectLibrary(S);
    if (S.size() > 0) {
        fout << "/* link with ";
        for (f = S.begin(), sep = ": "; f != S.end(); f++, sep = ", ") {
            fout << sep << *f;
        }
        fout << " */\n";
    }
}

/**
 * Print the required include files
 */
void CodeContainer::printIncludeFile(ostream& fout)
{
    set<string> S;
    collectIncludeFile(S);
    for (const auto& inc : S) {
        // Only print non-empty include (inc is actually quoted)
        if (inc.size() > 2) {
            fout << "#include " << inc << "\n";
        }
    }
}

/**
 * Print the loop graph in dot format
 */
void CodeContainer::printGraphDotFormat(ostream& fout)
{
    lclgraph G;
    CodeLoop::sortGraph(fCurLoop, G);

    fout << "strict digraph loopgraph {" << endl;
    fout << '\t' << "rankdir=LR;" << endl;
    fout << '\t' << "node[color=blue, fillcolor=lightblue, style=filled, fontsize=9];" << endl;

    int lnum = 0;  // used for loop numbers
    // for each level of the graph
    for (int l = int(G.size() - 1); l >= 0; l--) {
        // for each task in the level
        for (const auto& t : G[l]) {
            // print task label "Lxxx : 0xffffff"
            fout << '\t' << 'L' << t << "[label=<<font face=\"verdana,bold\">L" << lnum++
                 << "</font> : " << t << ">];" << endl;
            // for each source of the task
            for (const auto& src : t->fBackwardLoopDependencies) {
                // print the connection Lxxx -> Lyyy;
                fout << '\t' << 'L' << src << "->" << 'L' << t << ';' << endl;
            }
        }
    }
    fout << "}" << endl;
}

/**
 *  Adds forward dependencies in the DAG and returns loop count
 */
void CodeContainer::computeForwardDAG(lclgraph dag, int& loop_count, vector<int>& ready_loop)
{
#define START_TASK_MAX 2

    int loop_index = START_TASK_MAX;  // First index to be used for remaining tasks

    for (int l = int(dag.size() - 1); l >= 0; l--) {
        for (const auto& p : dag[l]) {
            // Setup forward dependancy
            for (const auto& p1 : p->fBackwardLoopDependencies) {
                p1->fForwardLoopDependencies.insert(p);
            }

            // Setup loop index
            p->fIndex = loop_index;
            loop_index++;

            // Keep ready loops
            if (p->getBackwardLoopDependencies().size() == 0) {
                ready_loop.push_back(p->getIndex());
            }
        }
    }

    loop_count = loop_index;
}

ValueInst* CodeContainer::pushFunction(const string& name, Typed::VarType result,
                                       vector<Typed::VarType>& types, const Values& args)
{
    Names named_args;
    for (size_t i = 0; i < types.size(); i++) {
        named_args.push_back(
            IB::genNamedTyped("dummy" + to_string(i), IB::genBasicTyped(types[i])));
    }
    pushGlobalDeclare(
        IB::genDeclareFunInst(name, IB::genFunTyped(named_args, IB::genBasicTyped(result))));
    return IB::genFunCallInst(name, args);
}

void CodeContainer::sortDeepFirstDAG(CodeLoop* l, set<CodeLoop*>& visited, list<CodeLoop*>& result)
{
    // Avoid printing already printed loops
    if (isElement(visited, l)) {
        return;
    }

    // Remember we have printed this loop
    visited.insert(l);

    // Compute the dependencies loops (that need to be computed before this one)
    for (const auto& p : l->fBackwardLoopDependencies) {
        sortDeepFirstDAG(p, visited, result);
    }

    // Keep the non-empty loops in result
    if (!l->isEmpty()) {
        result.push_back(l);
    }
}

// Functions are coded with a "class" prefix, so to stay separated in "gGlobalTable"
void CodeContainer::produceInfoFunctions(int tabs, const string& classname, const string& obj,
                                         bool ismethod, FunTyped::FunAttribute funtype,
                                         TextInstVisitor* producer, const string& in_fun,
                                         const string& out_fun)
{
    // Input/Output method
    producer->Tab(tabs);
    generateGetInputs(in_fun + classname, obj, ismethod, funtype)->accept(producer);
    generateGetOutputs(out_fun + classname, obj, ismethod, funtype)->accept(producer);
}

void CodeContainer::generateDAGLoopInternal(CodeLoop* loop, BlockInst* block, ValueInst* count,
                                            bool omp)
{
    loop->generateDAGScalarLoop(block, count, omp);
}

void CodeContainer::generateDAGLoopAux(CodeLoop* loop, BlockInst* loop_code, ValueInst* count,
                                       int loop_num, bool omp)
{
    if (gGlobal->gFunTaskSwitch) {
        BlockInst* block = IB::genBlockInst();
        // Generates scalar or vectorized loop
        generateDAGLoopInternal(loop, block, count, omp);
        Loop2FunctionBuider builder(subst("fun$0" + getClassName(), T(loop_num)), block,
                                    gGlobal->gDSPStruct);
        pushOtherComputeMethod(builder.fFunctionDef);
        loop_code->pushBackInst(IB::genLabelInst(
            (loop->fIsRecursive) ? subst("/* Recursive function $0 */", T(loop_num))
                                 : subst("/* Vectorizable function $0 */", T(loop_num))));
        loop_code->pushBackInst(builder.fFunctionCall);
    } else {
        loop_code->pushBackInst(IB::genLabelInst(
            (loop->fIsRecursive) ? subst("/* Recursive loop $0 */", T(loop_num))
                                 : subst("/* Vectorizable loop $0 */", T(loop_num))));
        // Generates scalar or vectorized loop
        generateDAGLoopInternal(loop, loop_code, count, omp);
    }
}

void CodeContainer::generateDAGLoop(BlockInst* block, ValueInst* count)
{
    int loop_num = 0;

    if (gGlobal->gDeepFirstSwitch) {
        set<CodeLoop*>  visited;
        list<CodeLoop*> result;
        sortDeepFirstDAG(fCurLoop, visited, result);
        for (const auto& p : result) {
            generateDAGLoopAux(p, block, count, loop_num++);
        }
    } else {
        lclgraph G;
        CodeLoop::sortGraph(fCurLoop, G);
        for (int l = int(G.size() - 1); l >= 0; l--) {
            for (const auto& p : G[l]) {
                generateDAGLoopAux(p, block, count, loop_num++);
            }
        }
    }
}

void CodeContainer::processFIR(void)
{
    // Types used in 'compute' prototype
    gGlobal->setVarType("count", Typed::kInt32);
    gGlobal->setVarType("inputs", Typed::kFloatMacro_ptr_ptr);
    gGlobal->setVarType("outputs", Typed::kFloatMacro_ptr_ptr);

    // Type used in several methods using 'sample_rate' parameter
    gGlobal->setVarType("sample_rate", Typed::kInt32);

    // ==========================================================================================
    // FIR to FIR passes that are generic for all backends, depending of the compilation options
    // ==========================================================================================

    if (gGlobal->gInlineTable) {
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and
        // 'fill' function call
        fStaticInitInstructions = inlineSubcontainersFunCalls(fStaticInitInstructions);

        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and
        // 'fill' function call
        fInitInstructions = inlineSubcontainersFunCalls(fInitInstructions);
    }

    // Additional iControl/fControl fields
    if (gGlobal->gExtControl && gGlobal->gMemoryManager >= 1) {
        if (fIntControl->getSize() > 0 && fIntControl->fAccess == Address::kStruct) {
            pushDeclare(IB::genDecStructVar(
                "iControl", IB::genArrayTyped(Typed::kInt32, fIntControl->getSize())));
        }
        if (fRealControl->getSize() > 0 && fRealControl->fAccess == Address::kStruct) {
            pushDeclare(IB::genDecStructVar("fControl",
                                            IB::genArrayTyped(itfloat(), fRealControl->getSize())));
        }
    }

    // Prepare fConstantFromMem/fConstantToMem blocks
    if (gGlobal->gMemoryManager >= 2) {
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and
        // 'fill' function call
        BlockInst* declare_block = inlineSubcontainersFunCalls(fInitInstructions);
        gGlobal->gIntZone->declareConstant(declare_block);
        gGlobal->gRealZone->declareConstant(declare_block);

        fConstantFromMem = gGlobal->gIntZone->getLoadConstantCode(declare_block);
        fConstantFromMem = gGlobal->gRealZone->getLoadConstantCode(fConstantFromMem);

        fConstantToMem = gGlobal->gIntZone->getStoreConstantCode(declare_block);
        fConstantToMem = gGlobal->gRealZone->getStoreConstantCode(fConstantToMem);
    }

    // Additional iZone/fZone fields
    if (gGlobal->gMemoryManager >= 1) {
        if (gGlobal->gIntZone->getSize() > 0 && gGlobal->gIntZone->fAccess == Address::kStruct) {
            pushDeclare(IB::genDecStructVar(
                "iZone", IB::genArrayTyped(Typed::kInt32, gGlobal->gIntZone->getSize())));
        }
        if (gGlobal->gRealZone->getSize() > 0 && gGlobal->gRealZone->fAccess == Address::kStruct) {
            pushDeclare(IB::genDecStructVar(
                "fZone", IB::genArrayTyped(itfloat(), gGlobal->gRealZone->getSize())));
        }
    }

    // Possibly rewrite arrays access using iZone/fZone
    rewriteInZones();

    // Possibly add "fSamplingRate" field
    generateSR();

    // Possibly groups tasks (used by VectorCodeContainer, OpenMPCodeContainer and WSSCodeContainer)
    if (gGlobal->gGroupTaskSwitch) {
        CodeLoop::computeUseCount(fCurLoop);
        set<CodeLoop*> visited;
        CodeLoop::groupSeqLoops(fCurLoop, visited);
    }

    if (gGlobal->gMemoryManager >= 0) {
        createMemoryLayout();
    }

    // Possibly generate JSON
    generateJSONFile();

    // Sort struct fields by size and type
    // 05/16/17 : deactivated since it slows down the code...
    /*
     fDeclarationInstructions->fCode.sort(sortArrayDeclarations);
     fDeclarationInstructions->fCode.sort(sortTypeDeclarations);
     */

    // Soundfile fields moved first
    fDeclarationInstructions->fCode.sort(sortSoundfiles);

    // Check FIR code
    if (global::isDebug("FIR_CHECKER")) {
        startTiming("FIR checker");
        FIRChecker fir_checker;
        flattenFIR()->accept(&fir_checker);
        endTiming("FIR checker");
    }

    if (global::isDebug("FIR_VAR_CHECKER")) {
        startTiming("FIR var checker");
        // Check variable scope in 'compute'
        FIRVarChecker fir_var_checker(fComputeBlockInstructions,
                                      fCurLoop->generateScalarLoop("count"));
        endTiming("FIR var checker");
    }
}

// Possibly rewrite arrays access using iZone/fZone
void CodeContainer::rewriteInZones()
{
    if (gGlobal->gMemoryManager >= 1) {
        if (gGlobal->gIntZone->getSize() > 0) {
            // Rewrite DSP struct access in iZone access
            fGlobalDeclarationInstructions =
                gGlobal->gIntZone->getCode(fGlobalDeclarationInstructions);
            fStaticInitInstructions = gGlobal->gIntZone->getCode(fStaticInitInstructions);
            fInitInstructions       = gGlobal->gIntZone->getCode(fInitInstructions);
            fControlDeclarationInstructions =
                gGlobal->gIntZone->getCode(fControlDeclarationInstructions);
            fComputeBlockInstructions = gGlobal->gIntZone->getCode(fComputeBlockInstructions);
            fComputeFunctions         = gGlobal->gIntZone->getCode(fComputeFunctions);
            fClearInstructions        = gGlobal->gIntZone->getCode(fClearInstructions);
        }
        if (gGlobal->gRealZone->getSize() > 0) {
            // Rewrite DSP struct access in fZone access
            fGlobalDeclarationInstructions =
                gGlobal->gRealZone->getCode(fGlobalDeclarationInstructions);
            fStaticInitInstructions = gGlobal->gRealZone->getCode(fStaticInitInstructions);
            fInitInstructions       = gGlobal->gRealZone->getCode(fInitInstructions);
            fControlDeclarationInstructions =
                gGlobal->gRealZone->getCode(fControlDeclarationInstructions);
            fComputeBlockInstructions = gGlobal->gRealZone->getCode(fComputeBlockInstructions);
            fComputeFunctions         = gGlobal->gRealZone->getCode(fComputeFunctions);
            fClearInstructions        = gGlobal->gRealZone->getCode(fClearInstructions);
        }
    }
}

void CodeContainer::mergeSubContainers()
{
    for (const auto& it : fSubContainers) {
        // Merge the subcontainer in the main one
        fExtGlobalDeclarationInstructions->merge(it->fExtGlobalDeclarationInstructions);
        fGlobalDeclarationInstructions->merge(it->fGlobalDeclarationInstructions);
        fDeclarationInstructions->merge(it->fDeclarationInstructions);
        fControlDeclarationInstructions->merge(it->fControlDeclarationInstructions);
        // TO CHECK (used for waveform initialisation which has to be moved first...)
        fStaticInitInstructions->mergeFront(it->fStaticInitInstructions);
        // Then clear it
        it->fGlobalDeclarationInstructions->fCode.clear();
        it->fExtGlobalDeclarationInstructions->fCode.clear();
        it->fDeclarationInstructions->fCode.clear();
        it->fControlDeclarationInstructions->fCode.clear();
        it->fStaticInitInstructions->fCode.clear();
    }

    // Possibly rewrite access in iZone/fZone
    rewriteInZones();
}

/*
 Create memory layout, to be used in C++ backend and JSON generation.
 The description order follows what will be done at allocation time.
 Subcontainers are ignored when gGlobal->gInlineTable == true.

 // Create static tables
 mydsp::classInit();

 // Create DSP
 dsp* DSP = mydsp::create();

 // Init DSP
 DSP->instanceInit(44100);
 */

void CodeContainer::createMemoryLayout()
{
    // Subcontainers used in classInit
    if (!gGlobal->gInlineTable) {
        // Compute DSP struct arrays size
        StructInstVisitor struct_visitor;

        // Add the global static tables
        fGlobalDeclarationInstructions->accept(&struct_visitor);

        // Compute R/W access for each subcontainer
        ForLoopInst* loop = fCurLoop->generateScalarLoop("count");
        loop->accept(&struct_visitor);

        for (const auto& it : fSubContainers) {
            // Check that the subcontainer name appears as a type name in fStaticInitInstructions
            SearchSubcontainer search_class(it->getClassName());
            fStaticInitInstructions->accept(&search_class);
            if (search_class.fFound) {
                // Subcontainer size
                VariableSizeCounter struct_size(Address::kStruct);
                it->generateDeclarations(&struct_size);
                fMemoryLayout.push_back(MemoryLayoutItem{it->getClassName(), "kObj_ptr", 0,
                                                         struct_size.fSizeBytes, 0, 0});
                // Get the associated table size and access
                pair<string, int> field = gGlobal->gTablesSize[it->getClassName()];

                // Check the table name memory description
                MemoryDesc& decs = struct_visitor.getMemoryDesc(field.first);
                fMemoryLayout.push_back(MemoryLayoutItem{field.first,
                                                         Typed::gTypeString[decs.fType], 0,
                                                         field.second, decs.fRAccessCount, 0});
            }
        }
    }

    {
        // Compute DSP struct arrays size and R/W access
        StructInstVisitor struct_visitor;

        // Add the DSP fields
        fDeclarationInstructions->accept(&struct_visitor);

        // To generate R/W access in the DSP loop
        ForLoopInst* loop = fCurLoop->generateScalarLoop("count");
        loop->accept(&struct_visitor);

        // DSP object
        int read_access  = 0;
        int write_access = 0;
        for (const auto& it : struct_visitor.getFieldTable()) {
            // Scalar types are kept in the DSP
            if (it.second.fIsScalar) {
                read_access += it.second.fRAccessCount;
                write_access += it.second.fWAccessCount;
            }
        }

        {
            // Array fields are transformed in pointers
            ArrayToPointer      array_pointer;
            VariableSizeCounter struct_size(Address::kStruct);
            array_pointer.getCode(fDeclarationInstructions)->accept(&struct_size);

            // TODO: rework DSP site comptations with local arrays

            fMemoryLayout.push_back(
                MemoryLayoutItem{fKlassName, "kObj_ptr", 0,
                                 // Raised value:
                                 // - add virtual method pointer (8 bytes in 64 bits)
                                 // - add 8 bytes for memory alignment
                                 struct_size.fSizeBytes + 8 + 8, read_access, write_access});
        }

        // Arrays and scalars inside the DSP struct
        for (const auto& it : struct_visitor.getFieldTable()) {
            if (!it.second.fIsControl) {
                /*
                std::cout << "it.first " << it.first << std::endl;
                std::cout << "Typed::gTypeString[it.second.fType] " <<
                Typed::gTypeString[it.second.fType] << std::endl; std::cout << "it.second.fSize " <<
                it.second.fSize << std::endl; std::cout << "it.second.fSizeBytes " <<
                it.second.fSizeBytes << std::endl;
                */
                fMemoryLayout.push_back(MemoryLayoutItem{
                    it.first,
                    Typed::gTypeString[(it.second.fIsScalar)
                                           ? it.second.fType
                                           : Typed::getPtrFromType(it.second.fType)],
                    it.second.fSize, it.second.fSizeBytes, it.second.fRAccessCount,
                    it.second.fWAccessCount});
            }
        }

        // Subcontainers used in instanceConstants
        if (!gGlobal->gInlineTable) {
            for (const auto& it : fSubContainers) {
                // Check that the subcontainer name appears as a type name in fInitInstructions
                SearchSubcontainer search_class(it->getClassName());
                fInitInstructions->accept(&search_class);
                if (search_class.fFound) {
                    VariableSizeCounter struct_size(Address::kStruct);
                    it->generateDeclarations(&struct_size);
                    fMemoryLayout.push_back(MemoryLayoutItem{it->getClassName(), "kObj_ptr", 0,
                                                             struct_size.fSizeBytes, 0, 0});
                }
            }
        }
    }
}

BlockInst* CodeContainer::flattenFIR(void)
{
    BlockInst* global_block = IB::genBlockInst();

    // Declaration part
    global_block->pushBackInst(IB::genLabelInst("========== Declaration part =========="));
    global_block->merge(fExtGlobalDeclarationInstructions);
    global_block->merge(fGlobalDeclarationInstructions);
    global_block->merge(fDeclarationInstructions);

    // Init method
    global_block->pushBackInst(IB::genLabelInst("========== Init method =========="));
    global_block->merge(fInitInstructions);
    global_block->merge(fResetUserInterfaceInstructions);
    global_block->merge(fClearInstructions);
    global_block->merge(fPostInitInstructions);

    // Static init method
    global_block->pushBackInst(IB::genLabelInst("========== Static init method =========="));
    global_block->merge(fStaticInitInstructions);
    global_block->merge(fPostStaticInitInstructions);

    // Subcontainers
    global_block->pushBackInst(IB::genLabelInst("========== Subcontainers =========="));
    for (const auto& it : fSubContainers) {
        global_block->merge(it->flattenFIR());
    }

    // Control method
    global_block->pushBackInst(IB::genLabelInst("========== Control =========="));
    global_block->merge(fControlDeclarationInstructions);

    // Compute method
    global_block->pushBackInst(IB::genLabelInst("========== Compute control =========="));
    global_block->merge(fComputeBlockInstructions);
    global_block->pushBackInst(IB::genLabelInst("========== Compute DSP =========="));
    global_block->pushBackInst(fCurLoop->generateScalarLoop(fFullCount));
    global_block->pushBackInst(IB::genLabelInst("========== Post compute DSP =========="));
    global_block->merge(fPostComputeBlockInstructions);

    return global_block;
}

BlockInst* CodeContainer::inlineSubcontainersFunCalls(BlockInst* block)
{
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    block = DspRenamer().getCode(block);

    // Inline subcontainers 'instanceInit' and 'fill' function call
    for (const auto& it : fSubContainers) {
        // Build the function to be inlined (prototype and code)
        DeclareFunInst* inst_init_fun =
            it->generateInstanceInitFun("instanceInit" + it->getClassName(), "dsp", true, false);
        block = FunctionCallInliner(inst_init_fun).getCode(block);

        // Build the function to be inlined (prototype and code)
        DeclareFunInst* fill_fun =
            it->generateFillFun("fill" + it->getClassName(), "dsp", true, false);
        block = FunctionCallInliner(fill_fun).getCode(block);
    }

    // Rename all loop variables name to avoid name clash
    LoopVariableRenamer loop_renamer;
    block = loop_renamer.getCode(block);
    return block;
}

void CodeContainer::printMacros(ostream& fout, int n)
{
    // generate user interface macros if needed
    if (gGlobal->gUIMacroSwitch) {
        if (gGlobal->gOutputLang == "c" || gGlobal->gOutputLang == "cpp") {
            tab(n, fout);
            fout << "#ifdef FAUST_UIMACROS";
            tab(n + 1, fout);
            tab(n + 1, fout);
            for (const auto& it : gGlobal->gMetaDataSet) {
                if (it.first == tree("filename")) {
                    fout << "#define FAUST_FILE_NAME " << **(it.second.begin());
                    break;
                }
            }
            tab(n + 1, fout);
            fout << "#define FAUST_CLASS_NAME "
                 << "\"" << fKlassName << "\"";
            tab(n + 1, fout);
            fout << "#define FAUST_COMPILATION_OPIONS \"" << gGlobal->printCompilationOptions1()
                 << "\"";
            tab(n + 1, fout);
            fout << "#define FAUST_INPUTS " << fNumInputs;
            tab(n + 1, fout);
            fout << "#define FAUST_OUTPUTS " << fNumOutputs;
            tab(n + 1, fout);
            fout << "#define FAUST_ACTIVES " << fNumActives;
            tab(n + 1, fout);
            fout << "#define FAUST_PASSIVES " << fNumPassives;
            tab(n, fout);
            printlines(n + 1, fUIMacro, fout);
            tab(n, fout);
            tab(n, fout);
            {
                fout << "\t"
                     << "#define FAUST_LIST_ACTIVES(p) \\";
                printlines(n + 2, fUIMacroActives, fout);
                tab(n, fout);
                tab(n, fout);
            }
            {
                fout << "\t"
                     << "#define FAUST_LIST_PASSIVES(p) \\";
                printlines(n + 2, fUIMacroPassives, fout);
                tab(n, fout);
                tab(n, fout);
            }
            fout << "#endif" << endl;
        } else {
            cerr << "ASSERT : incorrect backend : " << gGlobal->gOutputLang << endl;
            faustassert(false);
        }
    }
}

// DSP API generation

DeclareFunInst* CodeContainer::generateGetIO(const string& name, const string& obj, int io,
                                             bool ismethod, FunTyped::FunAttribute funtype)
{
    Names      args  = genMethod(obj, ismethod);
    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(IB::genRetInst(IB::genInt32NumInst(io)));

    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genInt32Typed(), funtype);
    return IB::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateGetInputs(const string& name, const string& obj,
                                                 bool ismethod, FunTyped::FunAttribute funtype)
{
    return generateGetIO(name, obj, fNumInputs, ismethod, funtype);
}

DeclareFunInst* CodeContainer::generateGetOutputs(const string& name, const string& obj,
                                                  bool ismethod, FunTyped::FunAttribute funtype)
{
    return generateGetIO(name, obj, fNumOutputs, ismethod, funtype);
}

DeclareFunInst* CodeContainer::generateAllocate(const string& name, const string& obj,
                                                bool ismethod, bool isvirtual)
{
    Names args = genMethod(obj, ismethod);

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(fAllocateInstructions);

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateDestroy(const string& name, const string& obj, bool ismethod,
                                               bool isvirtual)
{
    Names args = genMethod(obj, ismethod);

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(fDestroyInstructions);

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateGetIORate(const string& name, const string& obj,
                                                 vector<int>& io, bool ismethod, bool isvirtual)
{
    Names args = genMethod(obj, ismethod);
    args.push_back(IB::genNamedTyped("channel", Typed::kInt32));

    BlockInst*    block        = IB::genBlockInst();
    ValueInst*    switch_cond  = IB::genLoadFunArgsVar("channel");
    ::SwitchInst* switch_block = IB::genSwitchInst(switch_cond);
    block->pushBackInst(IB::genDecStackVar("rate", IB::genInt32Typed()));
    block->pushBackInst(switch_block);

    int i = 0;
    for (const auto& it : io) {
        // Creates "case" block
        BlockInst* case_block = IB::genBlockInst();
        // Compiles "case" block
        case_block->pushBackInst(IB::genStoreStackVar("rate", IB::genInt32NumInst(it)));
        // Add it into the switch
        switch_block->addCase(i++, case_block);
    }

    // Default case
    BlockInst* default_case_block = IB::genBlockInst();
    default_case_block->pushBackInst(IB::genStoreStackVar("rate", IB::genInt32NumInst(-1)));
    switch_block->addCase(-1, default_case_block);

    // Return "rate" result
    block->pushBackInst(IB::genRetInst(IB::genLoadStackVar("rate")));

    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genInt32Typed(),
                                         (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return IB::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateInstanceClear(const string& name, const string& obj,
                                                     bool ismethod, bool isvirtual)
{
    Names args = genMethod(obj, ismethod);

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(fClearInstructions);

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateInstanceConstants(const string& name, const string& obj,
                                                         bool ismethod, bool isvirtual)
{
    Names args = genMethod(obj, ismethod);
    args.push_back(IB::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(fInitInstructions);

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateStaticInitFun(const string& name, bool isstatic)
{
    Names args;
    args.push_back(IB::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(fStaticInitInstructions);
    block->pushBackInst(fPostStaticInitInstructions);

    //  20/11/16 : added in generateInstanceInitFun, is this needed here ?
    /*
    init_block->pushBackInst(fResetUserInterfaceInstructions);
    init_block->pushBackInst(fClearInstructions);
    */

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genVoidTyped(),
                                         (isstatic) ? FunTyped::kStatic : FunTyped::kDefault);
    return IB::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateInstanceInitFun(const string& name, const string& obj,
                                                       bool ismethod, bool isvirtual)
{
    Names args = genMethod(obj, ismethod);
    args.push_back(IB::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* init_block = IB::genBlockInst();
    init_block->pushBackInst(fInitInstructions);
    init_block->pushBackInst(fPostInitInstructions);
    init_block->pushBackInst(fResetUserInterfaceInstructions);
    init_block->pushBackInst(fClearInstructions);

    // Explicit return
    init_block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, init_block, isvirtual);
}

DeclareFunInst* CodeContainer::generateFillFun(const string& name, const string& obj, bool ismethod,
                                               bool isvirtual)
{
    Names args = genMethod(obj, ismethod);
    args.push_back(IB::genNamedTyped("count", Typed::kInt32));
    if (fSubContainerType == kInt) {
        args.push_back(IB::genNamedTyped(fTableName, Typed::kInt32_ptr));
    } else {
        args.push_back(IB::genNamedTyped(fTableName, itfloatptr()));
    }

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(fComputeBlockInstructions);
    // Hack for Julia
    if (gGlobal->gOutputLang == "julia" || gGlobal->gOutputLang == "jax") {
        block->pushBackInst(fCurLoop->generateSimpleScalarLoop("count"));
    } else {
        block->pushBackInst(fCurLoop->generateScalarLoop("count"));
    }

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateInit(const string& name, const string& obj, bool ismethod,
                                            bool isvirtual)
{
    Names args = genMethod(obj, ismethod);
    args.push_back(IB::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = IB::genBlockInst();
    {
        Values args1 = genObjArg(obj, ismethod);
        args1.push_back(IB::genLoadFunArgsVar("sample_rate"));
        block->pushBackInst(IB::genVoidFunCallInst("classInit", args1));
    }

    {
        Values args1 = genObjArg(obj, ismethod);
        args1.push_back(IB::genLoadFunArgsVar("sample_rate"));
        block->pushBackInst(IB::genVoidFunCallInst("instanceInit", args1));
    }

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateInstanceInit(const string& name, const string& obj,
                                                    bool ismethod, bool isvirtual)
{
    Names args = genMethod(obj, ismethod);
    args.push_back(IB::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = IB::genBlockInst();
    {
        Values args1 = genObjArg(obj, ismethod);
        args1.push_back(IB::genLoadFunArgsVar("sample_rate"));
        block->pushBackInst(IB::genVoidFunCallInst("instanceConstants", args1));
    }

    {
        Values args1 = genObjArg(obj, ismethod);
        block->pushBackInst(IB::genVoidFunCallInst("instanceResetUserInterface", args1));
    }

    {
        Values args1 = genObjArg(obj, ismethod);
        block->pushBackInst(IB::genVoidFunCallInst("instanceClear", args1));
    }

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateGetSampleRate(const string& name, const string& obj,
                                                     bool ismethod, bool isvirtual)
{
    Names args = genMethod(obj, ismethod);

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(IB::genRetInst(IB::genLoadStructVar("fSampleRate")));

    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genInt32Typed(),
                                         (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return IB::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateComputeFun(const string& name, const string& obj,
                                                  bool ismethod, bool isvirtual)
{
    Names args = genMethod(obj, ismethod);
    args.push_back(IB::genNamedTyped("count", Typed::kInt32));
    args.push_back(IB::genNamedTyped("inputs", Typed::kFloatMacro_ptr_ptr));
    args.push_back(IB::genNamedTyped("outputs", Typed::kFloatMacro_ptr_ptr));

    // Generates control + DSP block
    BlockInst* block = generateComputeAux();

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

// Memory methods

DeclareFunInst* CodeContainer::generateCalloc()
{
    Names args;
    args.push_back(IB::genNamedTyped("count", Typed::kInt64));
    args.push_back(IB::genNamedTyped("size", Typed::kInt64));

    // Creates function
    FunTyped* fun_type =
        IB::genFunTyped(args, IB::genBasicTyped(Typed::kVoid_ptr), FunTyped::kDefault);
    return IB::genDeclareFunInst("calloc", fun_type);
}

DeclareFunInst* CodeContainer::generateFree()
{
    Names args;
    args.push_back(IB::genNamedTyped("ptr", Typed::kVoid_ptr));

    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return IB::genDeclareFunInst("free", fun_type);
}

DeclareFunInst* CodeContainer::generateNewDsp(const string& name, int size)
{
    Names args;

    BlockInst* block = IB::genBlockInst();
    {
        Values args1;
        args1.push_back(IB::genInt64NumInst(1));
        args1.push_back(IB::genInt64NumInst(size));
        block->pushBackInst(IB::genRetInst(IB::genCastInst(IB::genFunCallInst("calloc", args1),
                                                           IB::genBasicTyped(Typed::kObj_ptr))));
    }

    // Creates function
    FunTyped* fun_type =
        IB::genFunTyped(args, IB::genBasicTyped(Typed::kObj_ptr), FunTyped::kLocal);
    return IB::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateDeleteDsp(const string& name, const string& obj)
{
    Names args;
    args.push_back(IB::genNamedTyped(obj, Typed::kObj_ptr));

    BlockInst* block = IB::genBlockInst();
    {
        Values args1;
        args1.push_back(
            IB::genCastInst(IB::genLoadFunArgsVar(obj), IB::genBasicTyped(Typed::kVoid_ptr)));
        block->pushBackInst(IB::genDropInst(IB::genFunCallInst("free", args1)));
    }

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genBasicTyped(Typed::kVoid), FunTyped::kLocal);
    return IB::genDeclareFunInst(name, fun_type, block);
}

void CodeContainer::generateJSONFile()
{
    // Generate JSON (which checks for non duplicated path)
    if (gGlobal->gPrintJSONSwitch) {
        if (gGlobal->gFloatSize == 1) {
            generateJSONFile<float>();
        } else {
            generateJSONFile<double>();
        }
    } else {
        // Checks for non duplicated path
        JSONInstVisitor<float> path_checker;
        generateUserInterface(&path_checker);
    }
}
