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

#include "omp_code_container.hh"
#include "fir_to_fir.hh"
#include "global.hh"

using namespace std;

// Analysis to discover which stack variables have to be used in the "firstprivate" list
struct StackVarAnalyser : public DispatchVisitor {
    list<string> fFirstPrivateTable;

    virtual void visit(DeclareVarInst* inst)
    {
        DispatchVisitor::visit(inst);
        ArrayTyped* array_typed;

        // Keep "simple" stack variables and pointers on simple variables (that is everything but
        // arrays)
        if (inst->fAddress->isStack() &&
            !((array_typed = dynamic_cast<ArrayTyped*>(inst->fType)) && array_typed->fSize > 0)) {
            fFirstPrivateTable.push_back(inst->getName());
        }
    }
};

void OpenMPCodeContainer::generateLocalInputs(BlockInst* loop_code, const string& index)
{
    // Generates line like: FAUSTFLOAT* input0 = &input0_ptr[index];
    Typed* type = IB::genArrayTyped(IB::genFloatMacroTyped(), 0);

    for (int i = 0; i < inputs(); i++) {
        string name1 = subst("input$0", T(i));
        string name2 = subst("input$0_ptr", T(i));
        loop_code->pushBackInst(IB::genDecStackVar(
            name1, type, IB::genLoadArrayStackVarAddress(name2, IB::genLoadLoopVar(index))));
    }
}

void OpenMPCodeContainer::generateLocalOutputs(BlockInst* loop_code, const string& index)
{
    // Generates line like: FAUSTFLOAT* ouput0 = &output0_ptr[index];
    Typed* type = IB::genArrayTyped(IB::genFloatMacroTyped(), 0);

    for (int i = 0; i < outputs(); i++) {
        string name1 = subst("output$0", T(i));
        string name2 = subst("output$0_ptr", T(i));
        loop_code->pushBackInst(IB::genDecStackVar(
            name1, type, IB::genLoadArrayStackVarAddress(name2, IB::genLoadLoopVar(index))));
    }
}

// LabelInst are used to add OMP directive in the code
StatementInst* OpenMPCodeContainer::generateDAGLoopOMP(const string& counter)
{
    BlockInst* result_code = IB::genBlockInst();
    string     index       = "index";

    // Setup "firstprivate" list
    StackVarAnalyser analyser;
    fComputeBlockInstructions->accept(&analyser);

    if (analyser.fFirstPrivateTable.size() == 0) {
        result_code->pushBackInst(IB::genLabelInst("#pragma omp parallel"));
    } else {
        stringstream firstprivate;
        firstprivate << "\t"
                     << "firstprivate(";
        list<string>::const_iterator it1;
        for (it1 = analyser.fFirstPrivateTable.begin(); it1 != analyser.fFirstPrivateTable.end();
             it1++) {
            firstprivate << (*it1);
            if (++it1 != analyser.fFirstPrivateTable.end()) {
                firstprivate << ", ";
            }
            it1--;
        }
        firstprivate << ")";
        result_code->pushBackInst(IB::genLabelInst("#pragma omp parallel\\"));
        result_code->pushBackInst(IB::genLabelInst(firstprivate.str()));
    }

    BlockInst* parallel_code = IB::genBlockInst();
    parallel_code->setIndent(true);

    BlockInst* loop_code = IB::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(loop_code, index);
    generateLocalOutputs(loop_code, index);

    // Generate : int count = min(32, (fullcount - index))
    ValueInst* init1 = IB::genLoadFunArgsVar(counter);
    ValueInst* init2 = IB::genSub(init1, IB::genLoadLoopVar(index));
    Values     min_fun_args;
    min_fun_args.push_back(IB::genInt32NumInst(gGlobal->gVecSize));
    min_fun_args.push_back(init2);
    ValueInst*      init3     = IB::genFunCallInst("min_i", min_fun_args);
    DeclareVarInst* count_dec = IB::genDecStackVar("vsize", IB::genInt32Typed(), init3);
    loop_code->pushBackInst(count_dec);

    // Generates the loop DAG
    lclgraph dag;
    CodeLoop::sortGraph(fCurLoop, dag);
    int  loop_num = 0;
    bool is_single =
        false;  // Generates "#pragma omp single" once when we stay if a sequence of "single" loops

    for (int l = int(dag.size()) - 1; l >= 0; l--) {
        BlockInst* omp_sections_block = IB::genBlockInst();
        if (dag[l].size() > 1) {
            loop_code->pushBackInst(IB::genLabelInst("#pragma omp sections"));
            omp_sections_block->setIndent(true);
        }
        for (const auto& p : dag[l]) {
            BlockInst* omp_section_block = IB::genBlockInst();
            if (dag[l].size() == 1) {  // Only one loop
                if (!p->isRecursive() && gGlobal->gOpenMPLoop) {
                    generateDAGLoopAux(p, omp_section_block, count_dec->load(), loop_num++, true);
                } else {
                    omp_section_block->setIndent(true);
                    if (!is_single) {
                        omp_sections_block->pushBackInst(IB::genLabelInst("#pragma omp single"));
                        is_single = true;
                    } else {
                        omp_sections_block->pushBackInst(
                            IB::genLabelInst("/* Still in a single section */"));
                    }
                    generateDAGLoopAux(p, omp_section_block, count_dec->load(), loop_num++);
                }
            } else {
                is_single = false;
                omp_section_block->setIndent(true);
                omp_sections_block->pushBackInst(IB::genLabelInst("#pragma omp section"));
                generateDAGLoopAux(p, omp_section_block, count_dec->load(), loop_num++);
            }
            omp_sections_block->pushBackInst(omp_section_block);
        }
        loop_code->pushBackInst(omp_sections_block);
    }

    // Generates the DAG enclosing loop
    DeclareVarInst* loop_decl =
        IB::genDecLoopVar(index, IB::genInt32Typed(), IB::genInt32NumInst(0));
    ValueInst*    loop_end = IB::genLessThan(loop_decl->load(), IB::genLoadFunArgsVar(counter));
    StoreVarInst* loop_increment =
        loop_decl->store(IB::genAdd(loop_decl->load(), gGlobal->gVecSize));

    StatementInst* loop = IB::genForLoopInst(loop_decl, loop_end, loop_increment, loop_code);

    parallel_code->pushBackInst(loop);
    result_code->pushBackInst(parallel_code);
    return result_code;
}

void OpenMPCodeContainer::processFIR()
{
    // Default FIR to FIR transformations
    CodeContainer::processFIR();

    // Sort arrays to be at the begining (break code genaration when 'soundfile' is used)
    // fComputeBlockInstructions->fCode.sort(sortArrayDeclarations);

    // Prepare global loop
    fGlobalLoopBlock = generateDAGLoopOMP(fFullCount);
}
