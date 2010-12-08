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

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include "wss_code_container.hh"

using namespace std;

void WSSCodeContainer::generateDAGLoopWSSAux1(lclgraph dag, BlockInst* loop_code, bool master_thread)
{
    // Compute ready tasks list
    vector<int> task_num;
    for (int l = dag.size() - 1; l >= 0; l--) {
        lclset::const_iterator next;
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
            if ((*p)->getBackwardLoopDependencies().size() == 0) {
                task_num.push_back((*p)->getIndex());
            }
        }
    }

    BlockInst* gen_code;
    BlockInst* then_block = NULL;

    if (master_thread) {
        then_block = InstBuilder::genBlockInst();
        gen_code = then_block;
    } else {
        gen_code = loop_code;
    }

    // Last stage connected to end task
    if (dag[0].size() > 1) {
        list<ValueInst*> fun_args;
        fun_args.push_back(InstBuilder::genLoadStructVar("fTaskGraph"));
        fun_args.push_back(InstBuilder::genIntNumInst(LAST_TASK_INDEX));
        fun_args.push_back(InstBuilder::genIntNumInst(dag[0].size()));
        gen_code->pushBackInst(InstBuilder::genLabelInst("// Initialize end task, if more than one input"));
        gen_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("initTask", fun_args)));
    } else {
        gen_code->pushBackInst(InstBuilder::genLabelInst("// End task has only one input, so will be directly activated"));
    }

    // Compute init section
    gen_code->pushBackInst(InstBuilder::genLabelInst("// Only initialize tasks with more than one input"));
    for (int l = dag.size() - 1; l >= 0; l--) {
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
            if ((*p)->getBackwardLoopDependencies().size() > 1)  { // Only initialize taks with more than 1 input, since taks with one input are "directly" activated.
                list<ValueInst*> fun_args;
                fun_args.push_back(InstBuilder::genLoadStructVar("fTaskGraph"));
                fun_args.push_back(InstBuilder::genIntNumInst((*p)->getIndex()));
                fun_args.push_back(InstBuilder::genIntNumInst((*p)->getBackwardLoopDependencies().size()));
                gen_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("initTask", fun_args)));
            }
        }
    }

    // Push n - 1 ready tasks
    for (unsigned int i = 0; i < task_num.size() - 1; i++) {
        list<ValueInst*> fun_args;
        fun_args.push_back(InstBuilder::genLoadStackVar("taskqueue"));
        fun_args.push_back(InstBuilder::genIntNumInst(task_num[i]));
        gen_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("pushHead", fun_args)));
    }

    gen_code->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genIntNumInst(task_num[task_num.size() - 1])));

    if (master_thread) {
        loop_code->pushBackInst(InstBuilder::genLabelInst("// Master thread init processing"));
        ValueInst* if_cond = InstBuilder::genBinopInst(kEQ, InstBuilder::genLoadFunArgsVar("num_thread"), InstBuilder::genIntNumInst(0));
        loop_code->pushBackInst(InstBuilder::genIfInst(if_cond, then_block));
    }
}

void WSSCodeContainer::generateDAGLoopWSSAux2(bool obj)
{
    BlockInst* loop_code = fComputeBlockInstructions;

    loop_code->pushBackInst(InstBuilder::genStoreStructVar("fFullcount", InstBuilder::genLoadFunArgsVar("fullcount")));
    loop_code->pushBackInst(InstBuilder::genStoreStructVar("fIndex", InstBuilder::genIntNumInst(0)));

    list<ValueInst*> fun_args0;
    loop_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("GetRealTime", fun_args0)));

    list<ValueInst*> fun_args3;
    fun_args3.push_back(InstBuilder::genLoadStructVar("fDynamicNumThreads"));
    loop_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("initAllTaskQueue", fun_args3)));

    list<NamedTyped*> callback_args;
    callback_args.push_back(InstBuilder::genNamedTyped("dsp", InstBuilder::genBasicTyped(Typed::kVoid_ptr)));
    callback_args.push_back(InstBuilder::genNamedTyped("cur_thread", InstBuilder::genBasicTyped(Typed::kInt)));

    list<ValueInst*> fun_args1;
    fun_args1.push_back(InstBuilder::genLoadStructVar("fThreadPool"));
    fun_args1.push_back(InstBuilder::genBinopInst(kSub, InstBuilder::genLoadStructVar("fDynamicNumThreads"), InstBuilder::genIntNumInst(1)));

    if (obj)
        fun_args1.push_back(InstBuilder::genLoadFunArgsVar("dsp"));
    else
        fun_args1.push_back(InstBuilder::genLoadFunArgsVar("this"));
    loop_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("signalAll", fun_args1)));

    list<ValueInst*> fun_args2;
    if (obj)
        fun_args2.push_back(InstBuilder::genLoadFunArgsVar("dsp"));
    fun_args2.push_back(InstBuilder::genIntNumInst(0));
    loop_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("computeThread", fun_args2)));
}

void WSSCodeContainer::generateDAGLoopWSSAux3()
{
    // Needed in the struct
    pushDeclare(InstBuilder::genDecVar("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile), InstBuilder::genBasicTyped(Typed::kInt)));
    pushDeclare(InstBuilder::genDecStructVar("fFullcount", InstBuilder::genBasicTyped(Typed::kInt)));
    pushDeclare(InstBuilder::genDecStructVar("fStaticNumThreads", InstBuilder::genBasicTyped(Typed::kInt)));
    pushDeclare(InstBuilder::genDecStructVar("fDynamicNumThreads", InstBuilder::genBasicTyped(Typed::kInt)));
    pushDeclare(InstBuilder::genDecStructVar("fThreadPool", InstBuilder::genBasicTyped(Typed::kVoid_ptr)));
    pushDeclare(InstBuilder::genDecStructVar("fTaskGraph", InstBuilder::genBasicTyped(Typed::kVoid_ptr)));
    pushDeclare(InstBuilder::genDecStructVar("fTaskQueueTable", InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kVoid_ptr), 16)));

    // Scheduler prototypes declaration
    pushGlobalDeclare(InstBuilder::genLabelInst("#ifdef __cplusplus"));
    pushGlobalDeclare(InstBuilder::genLabelInst("extern \"C\""));
    pushGlobalDeclare(InstBuilder::genLabelInst("{"));
    pushGlobalDeclare(InstBuilder::genLabelInst("#endif"));

    createVoidFunction("GetRealTime");

    createFunction0("createThreadPool", Typed::kVoid_ptr);
    createFunction1("deleteThreadPool", Typed::kVoid, "pool", Typed::kVoid_ptr);
    createFunction2("startAll", Typed::kVoid, "pool", Typed::kVoid_ptr, "num_threads", Typed::kInt);
    createFunction3("signalAll", Typed::kVoid, "pool", Typed::kVoid_ptr, "num_threads", Typed::kInt, "dsp", Typed::kVoid_ptr);

    createVoidFunction("initTaskQueue");
    createFunction1("initAllTaskQueue", Typed::kVoid, "num_threads", Typed::kInt);
    createFunction1("createTaskQueue", Typed::kVoid_ptr, "cur_thread", Typed::kInt);
    createFunction1("deleteTaskQueue", Typed::kVoid, "queue", Typed::kVoid_ptr);
    createFunction2("pushHead", Typed::kVoid, "queue", Typed::kVoid_ptr, "task", Typed::kInt);
    createFunction1("popHead", Typed::kInt, "queue", Typed::kVoid_ptr);
    createFunction2("getNextTask", Typed::kInt, "cur_thread", Typed::kInt, "dynamic_threads", Typed::kInt);

    createFunction0("createTaskGraph", Typed::kVoid_ptr);
    createFunction1("deleteTaskGraph", Typed::kVoid, "graph", Typed::kVoid_ptr);
    createFunction3("initTask", Typed::kVoid, "graph", Typed::kVoid_ptr, "task", Typed::kInt, "count", Typed::kInt);
    createFunction4("activateOutputTask1", Typed::kVoid, "graph", Typed::kVoid_ptr, "queue", Typed::kVoid_ptr, "task", Typed::kInt, "tasknum", Typed::kInt_ptr);
    createFunction3("activateOutputTask2", Typed::kVoid, "graph", Typed::kVoid_ptr, "queue", Typed::kVoid_ptr, "task", Typed::kInt);
    createFunction4("activateOneOutputTask", Typed::kVoid, "graph", Typed::kVoid_ptr, "queue", Typed::kVoid_ptr, "task", Typed::kInt, "tasknum", Typed::kInt_ptr);
    createFunction3("getReadyTask", Typed::kVoid, "graph", Typed::kVoid_ptr, "queue", Typed::kVoid_ptr, "tasknum", Typed::kInt_ptr);

    createFunction0("getStaticThreadsNum", Typed::kInt);
    createFunction0("getDynamicThreadsNum", Typed::kInt);

    pushGlobalDeclare(InstBuilder::genLabelInst("#ifdef __cplusplus"));
    pushGlobalDeclare(InstBuilder::genLabelInst("}"));
    pushGlobalDeclare(InstBuilder::genLabelInst("#endif"));

    // Specific init instructions
    list<ValueInst*> fun_args;
    pushInitMethod(InstBuilder::genStoreStructVar("fStaticNumThreads", InstBuilder::genFunCallInst("getStaticThreadsNum", fun_args)));
    pushInitMethod(InstBuilder::genStoreStructVar("fDynamicNumThreads", InstBuilder::genFunCallInst("getDynamicThreadsNum", fun_args)));
    pushInitMethod(InstBuilder::genStoreStructVar("fThreadPool",InstBuilder::genFunCallInst("createThreadPool", fun_args)));
    pushInitMethod(InstBuilder::genStoreStructVar("fTaskGraph",InstBuilder::genFunCallInst("createTaskGraph", fun_args)));

    pushInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("initTaskQueue", fun_args)));

    StatementInst* init_loop1 = InstBuilder::genDecLoopVar("i", InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
    ValueInst* end_loop1 = InstBuilder::genBinopInst(kLT, InstBuilder::genLoadLoopVar("i"), InstBuilder::genIntNumInst(16));
    StoreVarInst* inc_loop1 = InstBuilder::genStoreLoopVar("i", InstBuilder::genBinopInst(kAdd, InstBuilder::genLoadLoopVar("i"), InstBuilder::genIntNumInst(1)));

    list<StatementInst*> code1;
    list<ValueInst*> fun_args1;
    fun_args1.push_back(InstBuilder::genLoadLoopVar("i"));
    code1.push_back(InstBuilder::genStoreArrayStructVar("fTaskQueueTable", InstBuilder::genLoadLoopVar("i"), InstBuilder::genFunCallInst("createTaskQueue", fun_args1)));

    pushInitMethod(InstBuilder::genForLoopInst(init_loop1, end_loop1, inc_loop1, InstBuilder::genBlockInst(code1)));

    list<ValueInst*> fun_args2;
    fun_args2.push_back(InstBuilder::genLoadStructVar("fThreadPool"));
    fun_args2.push_back(InstBuilder::genBinopInst(kSub, InstBuilder::genLoadStructVar("fStaticNumThreads"), InstBuilder::genIntNumInst(1)));
    pushInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("startAll", fun_args2)));

    // Specific destroy instructions
    list<ValueInst*> fun_args3;
    fun_args3.push_back(InstBuilder::genLoadStructVar("fThreadPool"));
    pushDestroyMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("deleteThreadPool", fun_args3)));
    list<ValueInst*> fun_args4;
    fun_args4.push_back(InstBuilder::genLoadStructVar("fTaskGraph"));
    pushDestroyMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("deleteTaskGraph", fun_args4)));

    StatementInst* init_loop2 = InstBuilder::genDecLoopVar("i", InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
    ValueInst* end_loop2 = InstBuilder::genBinopInst(kLT, InstBuilder::genLoadLoopVar("i"), InstBuilder::genIntNumInst(16));
    StoreVarInst* inc_loop2 = InstBuilder::genStoreLoopVar("i", InstBuilder::genBinopInst(kAdd, InstBuilder::genLoadLoopVar("i"), InstBuilder::genIntNumInst(1)));

    list<StatementInst*> code2;
    list<ValueInst*> fun_args5;
    fun_args5.push_back(InstBuilder::genLoadArrayStructVar("fTaskQueueTable", InstBuilder::genLoadLoopVar("i")));
    code2.push_back(InstBuilder::genDropInst(InstBuilder::genFunCallInst("deleteTaskQueue", fun_args5)));
    pushDestroyMethod(InstBuilder::genForLoopInst(init_loop2, end_loop2, inc_loop2, InstBuilder::genBlockInst(code2)));
}

StatementInst* WSSCodeContainer::generateDAGLoopWSS(lclgraph dag)
{
    BlockInst* loop_code = fComputeThreadBlockInstructions;
    loop_code->pushBackInst(InstBuilder::genDecStackVar("tasknum", InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(WORK_STEALING_INDEX)));

    ValueInst* switch_cond = InstBuilder::genLoadStackVar("tasknum");
    SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);

    // Generate input/output access
    // Generates line like: fInput0 = &fInput0_ptr[index];
    for (int index = 0; index < inputs(); index++) {
        string name1 = subst("fInput$0", T(index));
        string name2 = subst("fInput$0_ptr", T(index));
        loop_code->pushBackInst(InstBuilder::genStoreStructVar(name1,
                InstBuilder::genLoadArrayStructAddressVar(name2, InstBuilder::genLoadVar("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)))));
    }

    // Generates line like: fOutput0 = &fOutput0_ptr[index];
    for (int index = 0; index < outputs(); index++) {
        string name1 = subst("fOutput$0", T(index));
        string name2 = subst("fOutput$0_ptr", T(index));
        loop_code->pushBackInst(InstBuilder::genStoreStructVar(name1,
                InstBuilder::genLoadArrayStructAddressVar(name2, InstBuilder::genLoadVar("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)))));
   }

    loop_code->pushBackInst(InstBuilder::genDecStackVar("taskqueue", InstBuilder::genBasicTyped(Typed::kVoid_ptr),
        InstBuilder::genLoadArrayStructVar("fTaskQueueTable", InstBuilder::genLoadFunArgsVar("num_thread"))));

    list<ValueInst*> fun_args;
    fun_args.push_back(InstBuilder::genLoadStackVar("taskqueue"));

    generateDAGLoopWSSAux1(dag, loop_code, true);

    // Work stealing task
    BlockInst* ws_block = InstBuilder::genBlockInst();
    ws_block->pushBackInst(InstBuilder::genLabelInst("// Work Stealing task"));
    list<ValueInst*> fun_args2;
    fun_args2.push_back(InstBuilder::genLoadFunArgsVar("num_thread"));
    fun_args2.push_back(InstBuilder::genLoadStructVar("fDynamicNumThreads"));
    ws_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genFunCallInst("getNextTask", fun_args2)));
    switch_block->addCase(WORK_STEALING_INDEX, ws_block);

    // Last task
    BlockInst* last_block = InstBuilder::genBlockInst();
    last_block->pushBackInst(InstBuilder::genLabelInst("// Last task"));
    last_block->pushBackInst(InstBuilder::genStoreVar("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile),
                                InstBuilder::genBinopInst(kAdd,
                                    InstBuilder::genLoadVar("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)),
                                    InstBuilder::genIntNumInst(gVecSize))));

    // Generates line like: fInput0 = &fInput0_ptr[index];
    for (int index = 0; index < inputs(); index++) {
        string name1 = subst("fInput$0", T(index));
        string name2 = subst("fInput$0_ptr", T(index));
        last_block->pushBackInst(InstBuilder::genStoreStructVar(name1, InstBuilder::genLoadArrayStructAddressVar(name2,
                            InstBuilder::genLoadVar("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)))));
    }

    // Generates line like: fOutput0 = &fOuput0_ptr[index];
    for (int index = 0; index < outputs(); index++) {
        string name1 = subst("fOutput$0", T(index));
        string name2 = subst("fOutput$0_ptr", T(index));
        last_block->pushBackInst(InstBuilder::genStoreStructVar(name1, InstBuilder::genLoadArrayStructAddressVar(name2,
                            InstBuilder::genLoadVar("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)))));
    }

    // Generates init DAG and ready tasks activations
    generateDAGLoopWSSAux1(dag, last_block, false);
    switch_block->addCase(LAST_TASK_INDEX, last_block);

    // Generates global "switch/case"
    int loop_num = START_TASK_MAX;  // First index to be used for remaining tasks

    ValueInst* while_cond = InstBuilder::genBinopInst(kLT, InstBuilder::genLoadVar("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)),
                                InstBuilder::genLoadStructVar("fFullcount"));
    BlockInst* switch_block_code = InstBuilder::genBlockInst();

    // Generates switch/case block "header"
    ValueInst* init1 = InstBuilder::genLoadStructVar("fFullcount");
    ValueInst* init2 = InstBuilder::genBinopInst(kSub, init1, InstBuilder::genLoadStructVar("fIndex"));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genIntNumInst(gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    StatementInst* count_dec = InstBuilder::genDecStackVar("count", InstBuilder::genBasicTyped(Typed::kInt), init3);
    switch_block_code->pushBackInst(count_dec);

    for (int l = dag.size() - 1; l > 0; l--) {
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++, loop_num++) {

            // Generates a "case" block for each task
            BlockInst* case_block = InstBuilder::genBlockInst();
            generateDAGLoopAux(*p, case_block, loop_num);

            // Add output tasks activation code

            // One output only
            if ((*p)->getForwardLoopDependencies().size() == 1) {

                lclset::const_iterator p1 = (*p)->getForwardLoopDependencies().begin();
                if ((*p1)->getBackwardLoopDependencies().size () == 1) {
                    case_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genIntNumInst((*p1)->getIndex())));
                } else {
                    list<ValueInst*> fun_args;
                    fun_args.push_back(InstBuilder::genLoadStructVar("fTaskGraph"));
                    fun_args.push_back(InstBuilder::genLoadStackVar("taskqueue"));
                    fun_args.push_back(InstBuilder::genIntNumInst((*p1)->getIndex()));
                    fun_args.push_back(InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress("tasknum", Address::kStack)));
                    case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("activateOneOutputTask", fun_args)));
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
                    case_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genIntNumInst(WORK_STEALING_INDEX)));
                }

                for (lclset::const_iterator p1 = (*p)->getForwardLoopDependencies().begin(); p1 != (*p)->getForwardLoopDependencies().end(); p1++) {
                    if ((*p1)->getBackwardLoopDependencies().size () == 1) {  // Task is the only input
                        if (*p1 != keep) {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadStackVar("taskqueue"));
                            fun_args.push_back(InstBuilder::genIntNumInst((*p1)->getIndex()));
                            case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("pushHead", fun_args)));
                        }
                    } else {
                        if (keep == NULL) {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadStructVar("fTaskGraph"));
                            fun_args.push_back(InstBuilder::genLoadStackVar("taskqueue"));
                            fun_args.push_back(InstBuilder::genIntNumInst((*p1)->getIndex()));
                            fun_args.push_back(InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress("tasknum", Address::kStack)));
                            case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("activateOutputTask1", fun_args)));
                        } else {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadStructVar("fTaskGraph"));
                            fun_args.push_back(InstBuilder::genLoadStackVar("taskqueue"));
                            fun_args.push_back(InstBuilder::genIntNumInst((*p1)->getIndex()));
                            case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("activateOutputTask2", fun_args)));
                        }
                    }
                }

                if (keep != NULL) {
                    case_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genIntNumInst(keep->getIndex())));
                } else {
                    list<ValueInst*> fun_args;
                    fun_args.push_back(InstBuilder::genLoadStructVar("fTaskGraph"));
                    fun_args.push_back(InstBuilder::genLoadStackVar("taskqueue"));
                    fun_args.push_back(InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress("tasknum", Address::kStack)));
                    case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("getReadyTask", fun_args)));
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
        generateDAGLoopAux(*level.begin(), case_block, loop_num);
        case_block->pushBackInst(InstBuilder::genStoreStackVar("tasknum", InstBuilder::genIntNumInst(LAST_TASK_INDEX)));
        // Add the "case" block
        switch_block->addCase(loop_num, case_block);
    } else {
        for (lclset::const_iterator p = level.begin(); p != level.end(); p++, loop_num++) {
            BlockInst* case_block = InstBuilder::genBlockInst();
            generateDAGLoopAux(*p, case_block, loop_num);

            list<ValueInst*> fun_args;
            fun_args.push_back(InstBuilder::genLoadStructVar("fTaskGraph"));
            fun_args.push_back(InstBuilder::genLoadStackVar("taskqueue"));
            fun_args.push_back(InstBuilder::genIntNumInst(LAST_TASK_INDEX));
            fun_args.push_back(InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress("tasknum", Address::kStack)));
            case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("activateOneOutputTask", fun_args)));
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

