/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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

#ifndef _INTERPRETER_INSTRUCTIONS_H
#define _INTERPRETER_INSTRUCTIONS_H

using namespace std;

#include "instructions.hh"
#include "typing_instructions.hh"
#include "fir_interpreter.hh"

#define NUM_SIZE 4

template <class T>
struct InterpreterInstVisitor : public DispatchVisitor {

        /*
         Global functions names table as a static variable in the visitor
         so that each function prototype is generated as most once in the module.
         */
        static map <string, int> gFunctionSymbolTable;      
        static map <string, string> gMathLibTable;
        
        int fRealHeapOffset;    // Offset in Real HEAP    
        int fIntHeapOffset;     // Offset in Integer HEAP    
                                     
        map <string, pair<int, Typed::VarType> > fFieldTable;   // Table : field_name, <byte offset in structure, type>
          
        TypingVisitor fTypingVisitor;
   
        FIRUserInterfaceBlockInstruction<T>* fUserInterfaceBlock;
        FIRBlockInstruction<T>* fCurrentBlock;
   
        InterpreterInstVisitor()
        {
            fUserInterfaceBlock = new FIRUserInterfaceBlockInstruction<T>();
            fCurrentBlock = new FIRBlockInstruction<T>();
            fRealHeapOffset = 0;
            fIntHeapOffset = 0;
        }
        
        inline bool isRealType(Typed::VarType type) 
        { 
            return (type == Typed::kFloat 
                || type == Typed::kFloatMacro 
                || type == Typed::kDouble); 
        }
        inline bool isRealPtrType(Typed::VarType type) 
        { 
            return (type == Typed::kFloat_ptr 
                || type == Typed::kFloatMacro_ptr 
                || type == Typed::kDouble_ptr); 
        }
        
        inline bool isInternalRealType(Typed::VarType type) 
        { 
            return (type == Typed::kFloat || type == Typed::kDouble); 
        }
    
        void initMathTable()
        {
            
        }
        
        virtual ~InterpreterInstVisitor()
        {}
   
        virtual void visit(AddMetaDeclareInst* inst)
        {
            printf("AddMetaDeclareInst : %s \n", inst->fZone.c_str());
            pair<int, Typed::VarType> tmp = fFieldTable[inst->fZone];
            if (inst->fZone == "0") {
                fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(FIRInstruction::kDeclare, -1, inst->fKey, inst->fValue));
            } else {
                fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(FIRInstruction::kDeclare, tmp.first, inst->fKey, inst->fValue));
            }
        }

        virtual void visit(OpenboxInst* inst)
        {
            FIRInstruction::Opcode opcode;
            switch (inst->fOrient) {
                case 0:
                    opcode = FIRInstruction::kOpenVerticalBox;
                    break;
                case 1:
                    opcode = FIRInstruction::kOpenHorizontalBox;
                    break;
                case 2:
                    opcode = FIRInstruction::kOpenTabBox;
                    break;
            }
            
            fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, inst->fName));
        }

        virtual void visit(CloseboxInst* inst)
        {
            fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(FIRInstruction::kCloseBox));
        }
        
        virtual void visit(AddButtonInst* inst)
        {
            FIRInstruction::Opcode opcode;
            if (inst->fType == AddButtonInst::kDefaultButton) {
                opcode = FIRInstruction::kAddButton;
            } else {
                opcode = FIRInstruction::kAddCheckButton;
            }
            
            pair<int, Typed::VarType> tmp = fFieldTable[inst->fZone];
            fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, tmp.first, inst->fLabel));
        }

        virtual void visit(AddSliderInst* inst)
        {
            FIRInstruction::Opcode opcode;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    opcode = FIRInstruction::kAddHorizontalSlider;
                    break;
                case AddSliderInst::kVertical:
                    opcode = FIRInstruction::kAddVerticalSlider;
                    break;
                case AddSliderInst::kNumEntry:
                    opcode = FIRInstruction::kAddNumEntry;
                    break;
            }
        
            pair<int, Typed::VarType> tmp = fFieldTable[inst->fZone];
            fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, tmp.first, inst->fLabel, inst->fInit, inst->fMin, inst->fMax, inst->fStep));
        }

        virtual void visit(AddBargraphInst* inst)
        {
            FIRInstruction::Opcode opcode;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    opcode = FIRInstruction::kAddHorizontalBargraph;
                    break;
                case AddBargraphInst::kVertical:
                    opcode = FIRInstruction::kAddVerticalBargraph;
                    break;
            }
            
            pair<int, Typed::VarType> tmp = fFieldTable[inst->fZone];
            fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, tmp.first, inst->fLabel, inst->fMin, inst->fMax));
        }
        
        virtual void visit(LabelInst* inst) {}

        // Declarations
        virtual void visit(DeclareVarInst* inst) 
        {
            // HACK : completely adhoc code for input/output...
            if ((startWith(inst->fAddress->getName(), "input") || startWith(inst->fAddress->getName(), "output"))) {
                return;
            }
            
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
            printf("DeclareVarInst name %s\n",inst->fAddress->getName().c_str());
            
            if (array_typed && array_typed->fSize > 1) {
                if (array_typed->fType->getType() == Typed::kInt) {
                    fFieldTable[inst->fAddress->getName()] = make_pair(fIntHeapOffset, Typed::getPtrFromType(array_typed->fType->getType()));
                    fIntHeapOffset += array_typed->fSize * NUM_SIZE;
                } else {
                    fFieldTable[inst->fAddress->getName()] = make_pair(fRealHeapOffset, Typed::getPtrFromType(array_typed->fType->getType()));
                    fRealHeapOffset += array_typed->fSize * NUM_SIZE;
                }
            } else {
                if (inst->fType->getType() == Typed::kInt) {
                    fFieldTable[inst->fAddress->getName()] = make_pair(fIntHeapOffset, inst->fType->getType());
                    fIntHeapOffset += NUM_SIZE;
                } else {
                    fFieldTable[inst->fAddress->getName()] = make_pair(fRealHeapOffset, inst->fType->getType());
                    fRealHeapOffset += NUM_SIZE;
                }
            }
            
            if (inst->fValue) {
                inst->fValue->accept(this);
            }
        }
        
        virtual void visit(DeclareFunInst* inst) {}
    
        // Memory
        /*
        virtual void visit(LoadVarInst* inst) 
        {
            if (startWith(inst->getName(), "inputs") || startWith(inst->getName(), "outputs")) {
                // Nothing 
            } else {
                fTypingVisitor.visit(inst);
                if (fTypingVisitor.fCurType == Typed::kInt) {
                    fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kLoadInt1, 0, 0));
                } else {
                    fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kLoadReal1, 0, 0));
                }
            }
        }
        */
        
        //virtual void visit(LoadVarAddressInst* inst) {}
        
        // Reverse order...
        virtual void visit(StoreVarInst* inst)
        {
            inst->fValue->accept(this);
            inst->fAddress->accept(this);
        }

        // Addresses
        virtual void visit(NamedAddress* named) 
        {
            pair<int, Typed::VarType> tmp = fFieldTable[named->getName()];
            switch (tmp.second) {
                case Typed::kFloatMacro:
                case Typed::kFloat:
                case Typed::kDouble:
                    fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kLoadReal1, 0, 0, tmp.first));
                    break;
                case Typed::kInt:
                    fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kLoadInt1, 0, 0, tmp.first));
                    break;
                case Typed::kFloatMacro_ptr: 
                case Typed::kFloat_ptr:
                case Typed::kDouble_ptr:
                case Typed::kInt_ptr:
                     assert(false);
                    break;
                default:
                    assert(false);
                    break;
            }
        }
        
        virtual void visit(IndexedAddress* indexed) 
        {   
            string num;
            
            indexed->fIndex->accept(this);
            
            // HACK : completely adhoc code for input/output...
            if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
                // Nothing  
            } else if (startWithRes(indexed->getName(), "input", num)) {
                printf("indexed->getName() %s %d\n", indexed->getName().c_str(), atoi(num.c_str()));
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kLoadInput1, 0, 0, atoi(num.c_str())));
            } else if (startWithRes(indexed->getName(), "output", num)) {
                printf("indexed->getName() %s %d\n", indexed->getName().c_str(), atoi(num.c_str()));
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kStoreOutput1, 0, 0, atoi(num.c_str())));
            } else {
                
                pair<int, Typed::VarType> tmp = fFieldTable[indexed->getName()];
                fCurrentBlock->push(new FIRBasicInstruction<T>(isRealPtrType(tmp.second) 
                        ? FIRInstruction::kStoreIndexedReal1 : FIRInstruction::kStoreIndexedInt1, 0, 0, tmp.first));
            }
        }

        // Primitives : numbers
        virtual void visit(FloatNumInst* inst) 
        {
            fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kRealValue1, 0, inst->fNum));
        }
        
        virtual void visit(FloatArrayNumInst* inst) {}
        
        virtual void visit(IntNumInst* inst)  
        {
            fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kIntValue1, inst->fNum, 0));
        }
        
        virtual void visit(IntArrayNumInst* inst) {}
        
        virtual void visit(BoolNumInst* inst) {}
        
        virtual void visit(DoubleNumInst* inst) {}
        
        virtual void visit(DoubleArrayNumInst* inst) {}

        // Numerical computation
        virtual void visit(BinopInst* inst) 
        {
            inst->fInst1->accept(&fTypingVisitor);
        
            // Compile sub-expressions
            inst->fInst1->accept(this);
            inst->fInst2->accept(this);
            
            if (fTypingVisitor.fCurType == Typed::kInt) {
                fCurrentBlock->push(new FIRBasicInstruction<T>(gBinOpTable[inst->fOpcode]->fInterpIntInst));
            } else {
                fCurrentBlock->push(new FIRBasicInstruction<T>(gBinOpTable[inst->fOpcode]->fInterpFloatInst));
            }
        }
        
        virtual void visit(CastNumInst* inst) 
        {
            inst->fInst->accept(this);
       
            // Typing the argument
            inst->fInst->accept(&fTypingVisitor);
            assert(fTypingVisitor.fCurType != Typed::kNoType);
            
            if (inst->fType->getType() == Typed::kInt) {
                printf("cast kFloatMacro or internal float ==> int\n");
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kCastInt1));
            } else if (isInternalRealType(inst->fType->getType()) && (fTypingVisitor.fCurType == Typed::kFloatMacro)) {
                // We assume that kFloatMacro and internal float are the same for now, so no cast...
                printf("cast kFloatMacro ==> internal float\n");
            } else if (isInternalRealType(fTypingVisitor.fCurType) && (inst->fType->getType() == Typed::kFloatMacro)) {
                // We assume that kFloatMacro and internal float are the same for now, so no cast...
                printf("cast internal float ==> kFloatMacro\n");
            } else {
                printf("cast int ==> kFloatMacro or internal float\n");
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kCastReal1));
            }
        }

        // Function call
        virtual void visit(FunCallInst* inst) {}
        virtual void visit(RetInst* inst) {}
        virtual void visit(DropInst* inst) {}

        // Conditionnal
        virtual void visit(Select2Inst* inst) {}
        virtual void visit(IfInst* inst) {}
        virtual void visit(SwitchInst* inst) {}

        // Loops
        virtual void visit(ForLoopInst* inst) 
        {
            // Loop variable declaration
            inst->fInit->accept(this);
           
            // Then generate loop block (in a new block)
            FIRBlockInstruction<T>* previous = fCurrentBlock;
            fCurrentBlock = new FIRBlockInstruction<T>();
            inst->fCode->accept(this);
           
            // Push Loop instruction
            pair<int, Typed::VarType> tmp = fFieldTable[inst->getVariableName()];
            previous->push(new FIRBasicInstruction<T>(FIRInstruction::kLoop, inst->getVariableCount(), 0, tmp.first, fCurrentBlock, NULL));
            fCurrentBlock = previous;
        }
        
        virtual void visit(WhileLoopInst* inst) {}

};

#endif
