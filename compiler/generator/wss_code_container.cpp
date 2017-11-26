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

#include "wss_code_container.hh"
#include "global.hh"
#include "fir_to_fir.hh"

using namespace std;

#define WORK_STEALING_INDEX 0
#define LAST_TASK_INDEX 1
#define START_TASK_INDEX LAST_TASK_INDEX + 1
#define START_TASK_MAX 2

#define fullcount "fCount"

void WSSCodeContainer::moveCompute2ComputeThread()
{
    // Move stack variable from "compute" to "computeThread"
    struct Compute2ComputeThread : public DispatchVisitor {

        WSSCodeContainer* fContainer;
        string fName;

        void visit(DeclareVarInst* inst)
        {
            BasicCloneVisitor cloner;
            if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {
                // For local thread access (in computeThread)
                fContainer->fComputeThreadBlockInstructions->pushBackInst(inst->clone(&cloner));
                // Mark inst to be removed
                inst->fAddress->setAccess(Address::kLink);
            }
            
            // Then dispatch and possibly rewrite 'value' access
            DispatchVisitor::visit(inst);
        }

        Compute2ComputeThread(WSSCodeContainer* container, const string& name)
            :fContainer(container), fName(name)
        {}
    };
     
    // Transform stack variables in struct variables
    VariableMover::Move(this, "Rec");
    VariableMover::Move(this, "tmp");
    VariableMover::Move(this, "Zec");
    VariableMover::Move(this, "Yec");

    // To move variable in "computeThread"
    Compute2ComputeThread mover1(this, "Slow");
    fComputeBlockInstructions->accept(&mover1);

    // To move variable in "computeThread"
    Compute2ComputeThread mover2(this, "Vec");
    fComputeBlockInstructions->accept(&mover2);
    
    // To move variable in "computeThread"
    Compute2ComputeThread mover3(this, "fInput");
    fComputeBlockInstructions->accept(&mover3);
    
    // To move variable in "computeThread"
    Compute2ComputeThread mover4(this, "fOutput");
    fComputeBlockInstructions->accept(&mover4);

    // Remove marked variables from fComputeBlockInstructions
    RemoverCloneVisitor remover;
    fComputeBlockInstructions = static_cast<BlockInst*>(fComputeBlockInstructions->clone(&remover));
}

void WSSCodeContainer::generateDAGLoopWSSAux1(lclgraph dag, BlockInst* gen_code, int cur_thread)
{
    
    // Last stage connected to end task
    if (dag[0].size() > 1) {
        list<ValueInst*> fun_args;
        fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
        fun_args.push_back(InstBuilder::genInt32NumInst(LAST_TASK_INDEX));
        fun_args.push_back(InstBuilder::genInt32NumInst(dag[0].size()));
        gen_code->pushBackInst(InstBuilder::genLabelInst("/* Initialize end task, if more than one input */"));
        gen_code->pushBackInst(InstBuilder::genVoidFunCallInst("initTask", fun_args));
    } else {
        gen_code->pushBackInst(InstBuilder::genLabelInst("/* End task has only one input, so will be directly activated */"));
    }

    // Compute init section
    gen_code->pushBackInst(InstBuilder::genLabelInst("/* Only initialize tasks with more than one input */"));
    for (int l = dag.size() - 1; l >= 0; l--) {
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
            if ((*p)->getBackwardLoopDependencies().size() > 1)  { // Only initialize tasks with more than 1 input, since tasks with one input are "directly" activated.
                list<ValueInst*> fun_args;
                fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
                fun_args.push_back(InstBuilder::genInt32NumInst((*p)->getIndex()));
                fun_args.push_back(InstBuilder::genInt32NumInst((*p)->getBackwardLoopDependencies().size()));
                gen_code->pushBackInst(InstBuilder::genVoidFunCallInst("initTask", fun_args));
            }
        }
    }
    
    list<ValueInst*> fun_args1;
    fun_args1.push_back(InstBuilder::genLoadStructVar("fScheduler"));
    if (cur_thread == -1) {
        // Push ready tasks in each thread WSQ 
        gen_code->pushBackInst(InstBuilder::genLabelInst("/* Push ready tasks in each thread WSQ */"));
        fun_args1.push_back(InstBuilder::genInt32NumInst(cur_thread));
    } else {
        // Push ready tasks in 'num_thread' WSQ
        gen_code->pushBackInst(InstBuilder::genLabelInst("/* Push ready tasks in 'num_thread' WSQ */"));
        fun_args1.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
    }
    gen_code->pushBackInst(InstBuilder::genVoidFunCallInst("initTaskList", fun_args1));
}

void WSSCodeContainer::generateDAGLoopWSSAux2(lclgraph dag, const string& counter)
{
    string index = "fIndex";
    BlockInst* loop_code = fComputeBlockInstructions;

    loop_code->pushBackInst(InstBuilder::genStoreStructVar(fullcount, InstBuilder::genLoadFunArgsVar(counter)));
    loop_code->pushBackInst(InstBuilder::genVolatileStoreStructVar(index, InstBuilder::genInt32NumInst(0)));
    
    generateDAGLoopWSSAux1(dag, loop_code, -1); // -1 means dispath ready tasks on all WSQ

    list<ValueInst*> fun_args1;
    fun_args1.push_back(InstBuilder::genLoadStructVar("fScheduler"));
    loop_code->pushBackInst(InstBuilder::genVoidFunCallInst("signalAll", fun_args1));

    list<ValueInst*> fun_args2;
    if (fObjName != "this") {
        fun_args2.push_back(InstBuilder::genLoadFunArgsVar(fObjName));
    }
    fun_args2.push_back(InstBuilder::genInt32NumInst(0));
    loop_code->pushBackInst(InstBuilder::genVoidFunCallInst("computeThread", fun_args2));
    
    loop_code->pushBackInst(InstBuilder::genVoidFunCallInst("syncAll", fun_args1));
}

void WSSCodeContainer::generateDAGLoopWSSAux3(int loop_count, const vector<int>& ready_loop)
{
    string index = "fIndex";
    
    // Needed in the struct
    pushDeclare(InstBuilder::genDecVolatileStructVar(index, InstBuilder::genBasicTyped(Typed::kInt32)));
    pushDeclare(InstBuilder::genDecStructVar(fullcount, InstBuilder::genBasicTyped(Typed::kInt32)));
    pushDeclare(InstBuilder::genDecStructVar("fScheduler", InstBuilder::genBasicTyped(Typed::kVoid_ptr)));
  
    // Scheduler prototypes declaration
    pushGlobalDeclare(InstBuilder::genLabelInst("#ifdef __cplusplus"));
    pushGlobalDeclare(InstBuilder::genLabelInst("extern \"C\""));
    pushGlobalDeclare(InstBuilder::genLabelInst("{"));
    pushGlobalDeclare(InstBuilder::genLabelInst("#endif"));
  
    pushGlobalDeclare(InstBuilder::genFunction2("createScheduler", Typed::kVoid_ptr, "task_queue_size", Typed::kInt32, "init_task_list_size", Typed::kInt32));
    pushGlobalDeclare(InstBuilder::genFunction1("deleteScheduler", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(InstBuilder::genFunction2("startAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "dsp", Typed::kVoid_ptr));
    pushGlobalDeclare(InstBuilder::genFunction1("stopAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(InstBuilder::genFunction1("initAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(InstBuilder::genFunction1("signalAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(InstBuilder::genFunction1("syncAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(InstBuilder::genFunction3("pushHead", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "cur_thread", Typed::kInt32, "task", Typed::kInt32));
    pushGlobalDeclare(InstBuilder::genFunction2("getNextTask", Typed::kInt32, "scheduler", Typed::kVoid_ptr, "cur_thread", Typed::kInt32));
    pushGlobalDeclare(InstBuilder::genFunction3("initTask", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "task_num", Typed::kInt32, "count", Typed::kInt32));
    pushGlobalDeclare(InstBuilder::genFunction4("activateOutputTask1", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "cur_thread", Typed::kInt32, "task", Typed::kInt32, "task_num", Typed::kInt32_ptr));
    pushGlobalDeclare(InstBuilder::genFunction3("activateOutputTask2", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "cur_thread", Typed::kInt32, "task", Typed::kInt32));
    pushGlobalDeclare(InstBuilder::genFunction4("activateOneOutputTask", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "cur_thread", Typed::kInt32, "task", Typed::kInt32, "task_num", Typed::kInt32_ptr));
    pushGlobalDeclare(InstBuilder::genFunction3("getReadyTask", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "cur_thread", Typed::kInt32, "task_num", Typed::kInt32_ptr));
    pushGlobalDeclare(InstBuilder::genFunction2("initTaskList", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "cur_thread", Typed::kInt32));
    pushGlobalDeclare(InstBuilder::genFunction2("addReadyTask", Typed::kVoid, "scheduler", Typed::kVoid_ptr, "task_num", Typed::kInt32));
    
    pushGlobalDeclare(InstBuilder::genLabelInst("#ifdef __cplusplus"));
    pushGlobalDeclare(InstBuilder::genLabelInst("}"));
    pushGlobalDeclare(InstBuilder::genLabelInst("#endif"));

    // Specific allocate instructions
    list<ValueInst*> fun_args;
    fun_args.push_back(InstBuilder::genInt32NumInst(loop_count));
    fun_args.push_back(InstBuilder::genInt32NumInst(ready_loop.size()));
    pushAllocateMethod(InstBuilder::genStoreStructVar("fScheduler", InstBuilder::genFunCallInst("createScheduler", fun_args)));
    
    for (unsigned int i = 0; i < ready_loop.size(); i++) {
        list<ValueInst*> fun_args;
        fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
        fun_args.push_back(InstBuilder::genInt32NumInst(ready_loop[i]));
        pushAllocateMethod(InstBuilder::genVoidFunCallInst("addReadyTask", fun_args));
    }
    list<ValueInst*> fun_args2;
    fun_args2.push_back(InstBuilder::genLoadStructVar("fScheduler"));
    fun_args2.push_back(InstBuilder::genLoadFunArgsVar(fObjName));
    pushAllocateMethod(InstBuilder::genVoidFunCallInst("startAll", fun_args2));
 
    // Specific destroy instructions
    list<ValueInst*> fun_args4;
    fun_args4.push_back(InstBuilder::genLoadStructVar("fScheduler"));
    pushDestroyMethod(InstBuilder::genVoidFunCallInst("deleteScheduler", fun_args4));
}

void WSSCodeContainer::generateLocalInputs(BlockInst* loop_code, const string& index_string)
{
    // Generates line like: fInput0 = &fInput0_ptr[index];
    for (int index = 0; index < inputs(); index++) {
        string name1 = subst("fInput$0", T(index));
        string name2 = subst("fInput$0_ptr", T(index));
        loop_code->pushBackInst(InstBuilder::genStoreStackVar(name1,
                InstBuilder::genLoadArrayStructVarAddress(name2, InstBuilder::genVolatileLoadStructVar(index_string))));
    }
}

void WSSCodeContainer::generateLocalOutputs(BlockInst* loop_code, const string& index_string)
{
    // Generates line like: fOutput0 = &fOutput0_ptr[index];
    for (int index = 0; index < outputs(); index++) {
        string name1 = subst("fOutput$0", T(index));
        string name2 = subst("fOutput$0_ptr", T(index));
        loop_code->pushBackInst(InstBuilder::genStoreStackVar(name1,
                InstBuilder::genLoadArrayStructVarAddress(name2, InstBuilder::genVolatileLoadStructVar(index_string))));
    }
}

StatementInst* WSSCodeContainer::generateDAGLoopWSS(lclgraph dag)
{
    string index = "fIndex";
    
    BlockInst* loop_code = fComputeThreadBlockInstructions;
    loop_code->pushBackInst(InstBuilder::genDecStackVar("tasknum", InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(WORK_STEALING_INDEX)));
    
    DeclareVarInst* count_dec = InstBuilder::genDecStackVar("count", InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genLoadStructVar(fullcount));
    loop_code->pushFrontInst(count_dec);

    ValueInst* switch_cond = InstBuilder::genLoadStackVar("tasknum");
    ::SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);
    
    // Work stealing task
    BlockInst* ws_block = InstBuilder::genBlockInst();
    ws_block->pushBackInst(InstBuilder::genLabelInst("/* Work Stealing task */"));
    list<ValueInst*> fun_args2;
    fun_args2.push_back(InstBuilder::genLoadStructVar("fScheduler"));
    fun_args2.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
    
    ws_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genFunCallInst("getNextTask", fun_args2)));
    switch_block->addCase(WORK_STEALING_INDEX, ws_block);

    // Last task
    BlockInst* last_block = InstBuilder::genBlockInst();
    last_block->pushBackInst(InstBuilder::genLabelInst("/* Last task */"));
    last_block->pushBackInst(InstBuilder::genVolatileStoreStructVar(index, InstBuilder::genAdd(InstBuilder::genVolatileLoadStructVar(index), gGlobal->gVecSize)));
  
    ValueInst* if_cond = InstBuilder::genLessThan(InstBuilder::genVolatileLoadStructVar(index), InstBuilder::genLoadStructVar(fullcount));
   
    BlockInst* then_block = InstBuilder::genBlockInst();
    BlockInst* else_block = InstBuilder::genBlockInst();
    
    else_block->pushBackInst(InstBuilder::genRetInst());
    
    // Generates init DAG and ready tasks activations
    generateDAGLoopWSSAux1(dag, then_block);
    //last_block->pushBackInst(InstBuilder::genIfInst(if_cond, then_block, else_block));
    last_block->pushBackInst(InstBuilder::genIfInst(if_cond, then_block));
    
    // Generates tasknum
    last_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genInt32NumInst(0)));
    
    // Push if block as last_task
    switch_block->addCase(LAST_TASK_INDEX, last_block);
  
    // Generates global "switch/case"
    int loop_num = START_TASK_MAX;  // First index to be used for remaining tasks

    ValueInst* while_cond = InstBuilder::genLessThan(InstBuilder::genVolatileLoadStructVar(index), InstBuilder::genLoadStructVar(fullcount));
    BlockInst* switch_block_code = InstBuilder::genBlockInst();

    // Generates switch/case block "header"
    ValueInst* init1 = InstBuilder::genLoadStructVar(fullcount);
    ValueInst* init2 = InstBuilder::genSub(init1, InstBuilder::genVolatileLoadStructVar(index));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genInt32NumInst(gGlobal->gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    
    StoreVarInst* count_store = InstBuilder::genStoreStackVar("count", init3);
    
    // Generate input/output access
    generateLocalInputs(switch_block_code, index);
    generateLocalOutputs(switch_block_code, index);
  
    switch_block_code->pushBackInst(count_store);

    for (int l = dag.size() - 1; l > 0; l--) {
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++, loop_num++) {

            // Generates a "case" block for each task
            BlockInst* case_block = InstBuilder::genBlockInst();
            generateDAGLoopAux(*p, case_block, count_dec, loop_num);

            // Add output tasks activation code

            // One output only
            if ((*p)->getForwardLoopDependencies().size() == 1) {

                case_block->pushBackInst(InstBuilder::genLabelInst("/* One output only */"));
                lclset::const_iterator p1 = (*p)->getForwardLoopDependencies().begin();
                if ((*p1)->getBackwardLoopDependencies().size () == 1) {
                    case_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genInt32NumInst((*p1)->getIndex())));
                } else {
                    list<ValueInst*> fun_args;
                    fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
                    fun_args.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
                    fun_args.push_back(InstBuilder::genInt32NumInst((*p1)->getIndex()));
                    fun_args.push_back(InstBuilder::genLoadStackVarAddress("tasknum"));
                    case_block->pushBackInst(InstBuilder::genVoidFunCallInst("activateOneOutputTask", fun_args));
                }

            } else {

                CodeLoop* keep = NULL;
                
                // Find one output with only one backward dependencies
                for (lclset::const_iterator p1 = (*p)->getForwardLoopDependencies().begin(); p1 != (*p)->getForwardLoopDependencies().end(); p1++) {
                    if ((*p1)->getBackwardLoopDependencies().size () == 1) {
                        keep = *p1;
                        break;
                    }
                }

                if (keep == NULL) {
                    case_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genInt32NumInst(WORK_STEALING_INDEX)));
                }

                for (lclset::const_iterator p1 = (*p)->getForwardLoopDependencies().begin(); p1 != (*p)->getForwardLoopDependencies().end(); p1++) {
                    if ((*p1)->getBackwardLoopDependencies().size () == 1) {  // Task is the only input
                        if (*p1 != keep) {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
                            fun_args.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
                            fun_args.push_back(InstBuilder::genInt32NumInst((*p1)->getIndex()));
                            case_block->pushBackInst(InstBuilder::genVoidFunCallInst("pushHead", fun_args));
                        }
                    } else {
                        if (keep == NULL) {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
                            fun_args.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
                            fun_args.push_back(InstBuilder::genInt32NumInst((*p1)->getIndex()));
                            fun_args.push_back(InstBuilder::genLoadStackVarAddress("tasknum"));
                            case_block->pushBackInst(InstBuilder::genVoidFunCallInst("activateOutputTask1", fun_args));
                        } else {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
                            fun_args.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
                            fun_args.push_back(InstBuilder::genInt32NumInst((*p1)->getIndex()));
                            case_block->pushBackInst(InstBuilder::genVoidFunCallInst("activateOutputTask2", fun_args));
                        }
                    }
                }

                if (keep != NULL) {
                    case_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genInt32NumInst(keep->getIndex())));
                } else {
                    list<ValueInst*> fun_args;
                    fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
                    fun_args.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
                    fun_args.push_back(InstBuilder::genLoadStackVarAddress("tasknum"));
                    case_block->pushBackInst(InstBuilder::genVoidFunCallInst("getReadyTask", fun_args));
                }
            }

            // Add the "case" block
            switch_block->addCase(loop_num, case_block);
        }
    }

    // Last stage
    lclset level = dag[0];

    if (level.size() == 1) {
        BlockInst* case_block = InstBuilder::genBlockInst();
        generateDAGLoopAux(*level.begin(), case_block, count_dec, loop_num);
        case_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genInt32NumInst(LAST_TASK_INDEX)));
        // Add the "case" block
        switch_block->addCase(loop_num, case_block);
    } else {
        for (lclset::const_iterator p = level.begin(); p != level.end(); p++, loop_num++) {
            BlockInst* case_block = InstBuilder::genBlockInst();
            generateDAGLoopAux(*p, case_block, count_dec, loop_num);

            list<ValueInst*> fun_args;
            fun_args.push_back(InstBuilder::genLoadStructVar("fScheduler"));
            fun_args.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
            fun_args.push_back(InstBuilder::genInt32NumInst(LAST_TASK_INDEX));
            fun_args.push_back(InstBuilder::genLoadStackVarAddress("tasknum"));
            
            case_block->pushBackInst(InstBuilder::genVoidFunCallInst("activateOneOutputTask", fun_args));
            // Add the "case" block
            switch_block->addCase(loop_num, case_block);
        }
    }

    // Finishes switch block
    switch_block_code->pushBackInst(switch_block);
    WhileLoopInst* while_block = InstBuilder::genWhileLoopInst(while_cond, switch_block_code);

    // Add the "while" block
    loop_code->pushBackInst(while_block);
    return loop_code;
}

void WSSCodeContainer::processFIR(void)
{
    // Default FIR to FIR transformations
    CodeContainer::processFIR();
 
    // Transform some stack variables in struct variables, move some variables from "compute" to "computeThread"
    moveCompute2ComputeThread();

    lclgraph dag;
    vector<int> ready_loop;
    int loop_count;
    CodeLoop::sortGraph(fCurLoop, dag);
    
    computeForwardDAG(dag, loop_count, ready_loop);
    
    generateDAGLoopWSSAux3(loop_count, ready_loop);

    // Prepare global loop
    fThreadLoopBlock = generateDAGLoopWSS(dag);

    generateDAGLoopWSSAux2(dag, fFullCount);

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortArrayDeclarations);
    
    /*
    // Verify code
    CodeVerifier verifier;
    BlockInst global_block;
    // Declaration part
    global_block.merge(fExtGlobalDeclarationInstructions);
    global_block.merge(fGlobalDeclarationInstructions);
    global_block.merge(fDeclarationInstructions);
    // Init method
    global_block.merge(fInitInstructions);
    global_block.merge(fPostInitInstructions);
    global_block.merge(fStaticInitInstructions);
    global_block.merge(fPostStaticInitInstructions);
    // Compute method
    global_block.merge(fComputeBlockInstructions);
    global_block.pushBackInst(fDAGBlock);
    global_block.accept(&verifier);
    */
}

BlockInst* WSSCodeContainer::flattenFIR(void)
{
    BlockInst* global_block = CodeContainer::flattenFIR();
    global_block->pushBackInst(InstBuilder::genLabelInst("========== Compute DSP Thread =========="));
    global_block->pushBackInst(fThreadLoopBlock);
    return global_block;
}
