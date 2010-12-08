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
#ifndef _WSS_CODE_CONTAINER_H
#define _WSS_CODE_CONTAINER_H

#include "code_container.hh"

struct WSSCodeContainer : public virtual CodeContainer {

    BlockInst* fComputeThreadBlockInstructions;

    WSSCodeContainer(int numInputs, int numOutputs)
        :CodeContainer(numInputs, numOutputs), fComputeThreadBlockInstructions(InstBuilder::genBlockInst())
    {}

    void MoveStackArray2Struct()
    {
        // Analysis to promote stack variables to struct variables
        struct StackArray2StructAnalyser : public DispatchVisitor {

            WSSCodeContainer* fContainer;

            void visit(DeclareVarInst* inst)
            {
                DispatchVisitor::visit(inst);
                ArrayTyped* array_typed;
                BasicCloneVisitor cloner;
                if (inst->fAddress->getAccess() == Address::kStack && (array_typed = dynamic_cast<ArrayTyped*>(inst->fTyped))) {
                    if (array_typed->fSize > 0) {
                        fContainer->pushDeclare(InstBuilder::genDeclareVarInst(new NamedAddress(inst->fAddress->getName(), Address::kStruct), inst->fTyped->clone(&cloner), NULL));
                    } else {
                        // Define a special cloner that force access to kStruct
                        struct StructVarCloneVisitor : public BasicCloneVisitor {
                            virtual Address* visit(NamedAddress* address) { return new NamedAddress(address->fName, Address::kStruct); }
                        };
                        StructVarCloneVisitor cloner1;
                        // For local thread access (in computeThread)
                        fContainer->fComputeThreadBlockInstructions->pushBackInst(inst->clone(&cloner1));
                    }
                    inst->fAddress->setAccess(Address::kLink);
                }
            }

            StackArray2StructAnalyser(WSSCodeContainer* container):fContainer(container)
            {}
        };

        struct RemoverCloneVisitor : public BasicCloneVisitor {

            // Rewrite Declare as a no-op (DropInst)
            StatementInst* visit(DeclareVarInst* inst)
            {
                if (inst->fAddress->getAccess() == Address::kLink) {
                    return new DropInst();
                } else {
                    return BasicCloneVisitor::visit(inst);
                }
            }
        };

        // Transform stack array variables in struct variables
        StackArray2StructAnalyser analyser(this);
        fComputeBlockInstructions->accept(&analyser);

        // Remove marked variables from fComputeBlockInstructions
        RemoverCloneVisitor remover;
        fComputeBlockInstructions = static_cast<BlockInst*>(fComputeBlockInstructions->clone(&remover));
    }

    void MoveStack2Struct()
    {
        // Analysis to promote stack variables to struct variables
        struct Stack2StructAnalyser : public DispatchVisitor {

            WSSCodeContainer* fContainer;
            string fName;

            void visit(DeclareVarInst* inst)
            {
                DispatchVisitor::visit(inst);
                BasicCloneVisitor cloner;
                if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {

                    // Variable moved to the Struct
                    fContainer->pushDeclare(InstBuilder::genDeclareVarInst(new NamedAddress(inst->fAddress->getName(), Address::kStruct), inst->fTyped->clone(&cloner), NULL));

                    // For local thread access (in computeThread), rewrite the Declare instruction by a Store
                    if (inst->fValue)
                        fContainer->fComputeThreadBlockInstructions->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(inst->fAddress->getName(), Address::kStruct), inst->fValue->clone(&cloner)));
                    inst->fAddress->setAccess(Address::kLink);
                }
            }

            void visit(NamedAddress* address)
            {
                if (address->fAccess == Address::kStack && address->fName.find(fName) != string::npos) {
                    address->fAccess = Address::kStruct;
                }
            }

            Stack2StructAnalyser(WSSCodeContainer* container, const string& name)
                :fContainer(container), fName(name)
            {}
        };

        struct Stack2StructAnalyser2 : public DispatchVisitor {

            string fName;

            void visit(NamedAddress* address)
            {
                if (address->fAccess == Address::kStack && address->fName.find(fName) != string::npos) {
                    address->fAccess = Address::kStruct;
                }
            }

            Stack2StructAnalyser2(const string& name):fName(name)
            {}
        };

        struct Stack2StructAnalyser3 : public DispatchVisitor {

            WSSCodeContainer* fContainer;
            string fName;

            void visit(DeclareVarInst* inst)
            {
                DispatchVisitor::visit(inst);
                BasicCloneVisitor cloner;
                if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {
                    // For local thread access (in computeThread)
                    if (inst->fValue)
                        fContainer->fComputeThreadBlockInstructions->pushBackInst(inst->clone(&cloner));
                    inst->fAddress->setAccess(Address::kLink);
                }
            }

            Stack2StructAnalyser3(WSSCodeContainer* container, const string& name)
                :fContainer(container), fName(name)
            {}
        };

        struct RemoverCloneVisitor : public BasicCloneVisitor {

            // Rewrite Declare as a no-op (DropInst)
            StatementInst* visit(DeclareVarInst* inst)
            {
                if (inst->fAddress->getAccess() == Address::kLink) {
                    return new DropInst();
                } else {
                    return BasicCloneVisitor::visit(inst);
                }
            }
        };

        struct VariableMover {

            static void Move(WSSCodeContainer* container, const string& name)
            {
                // Transform stack variables in struct variables
                Stack2StructAnalyser analyser1(container, name);
                container->fComputeBlockInstructions->accept(&analyser1);

                Stack2StructAnalyser2 analyser2(name);
                container->transformDAG(&analyser2);
            }
        };

        // Transform stack variables in struct variables
        VariableMover::Move(this, "Rec");
        VariableMover::Move(this, "tmp");
        VariableMover::Move(this, "Zec");
        VariableMover::Move(this, "Yec");

        // To move variable in "computeThread"
        Stack2StructAnalyser3 analyser8(this, "Slow");
        fComputeBlockInstructions->accept(&analyser8);

        // To move variable in "computeThread"
        Stack2StructAnalyser3 analyser9(this, "Vec");
        fComputeBlockInstructions->accept(&analyser9);

        // Remove marked variables from fComputeBlockInstructions
        RemoverCloneVisitor remover;
        fComputeBlockInstructions = static_cast<BlockInst*>(fComputeBlockInstructions->clone(&remover));
    }

    void generateDAGLoopWSSAux1(lclgraph dag, BlockInst* loop_code, bool master_thread);
    void generateDAGLoopWSSAux2(bool obj);
    void generateDAGLoopWSSAux3();
    StatementInst* generateDAGLoopWSS(lclgraph dag);
};


#endif
