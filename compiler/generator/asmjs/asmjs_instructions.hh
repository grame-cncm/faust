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

#ifndef _ASMJAVASCRIPT_INSTRUCTIONS_H
#define _ASMJAVASCRIPT_INSTRUCTIONS_H

using namespace std;

#include "text_instructions.hh"
#include "typing_instructions.hh"

#define NUM_SIZE 4

class ASMJAVAScriptInstVisitor : public TextInstVisitor {

    private:
    
        TypingVisitor fTypingVisitor;
        map <string, int> fFunctionSymbolTable; 
        map <string, string> fMathLibTable;
       
        string fObjPrefix;
        
        int fStructOffset;                                      // Keep the offset in bytes of the structure
        map <string, pair<int, Typed::VarType> > fFieldTable;   // Table : field_name, <byte offset in structure, type>
        
        inline bool isRealType(Typed::VarType type) 
        { 
            return (type == Typed::kFloat 
                || type == Typed::kFloatMacro 
                || type == Typed::kFloatish 
                || type == Typed::kDouble
                || type == Typed::kDoublish); 
        }
        
        inline bool isIntType(Typed::VarType type) 
        { 
            return (type == Typed::kInt || type == Typed::kIntish); 
        }
  
    public:
    
        ASMJAVAScriptInstVisitor(std::ostream* out, int tab = 0)
            :TextInstVisitor(out, ".", ifloat(), "", tab)
        {
            fMathLibTable["abs"] = "global.Math.abs";
            fMathLibTable["absf"] = "global.Math.abs";
            fMathLibTable["fabsf"] = "global.Math.abs";
            fMathLibTable["acosf"] = "global.Math.acos";
            fMathLibTable["asinf"] = "global.Math.asin";
            fMathLibTable["atanf"] = "global.Math.atan";
            fMathLibTable["atan2f"] = "global.Math.atan2";
            fMathLibTable["ceilf"] = "global.Math.ceil";
            fMathLibTable["cosf"] = "global.Math.cos";
            fMathLibTable["expf"] = "global.Math.exp";
            fMathLibTable["floorf"] = "global.Math.floor";
            fMathLibTable["fmodf"] = "manual";      // Manually generated
            fMathLibTable["logf"] = "global.Math.log";
            fMathLibTable["log10f"] = "manual";     // Manually generated
            fMathLibTable["max"] = "global.Math.max";
            fMathLibTable["min"] = "global.Math.min";
            fMathLibTable["powf"] = "global.Math.pow";
            fMathLibTable["roundf"] = "global.Math.round";
            fMathLibTable["sinf"] = "global.Math.sin";
            fMathLibTable["sqrtf"] = "global.Math.sqrt";
            fMathLibTable["tanf"] = "global.Math.tan";
            
            fObjPrefix = "";
            fStructOffset = 0;
        }

        virtual ~ASMJAVAScriptInstVisitor()
        {}
    
        int getStructSize() { return fStructOffset; }
        map <string, pair<int, Typed::VarType> >& getFieldTable() { return fFieldTable; }
        map <string, string>& getMathLibTable() { return fMathLibTable; }

        // Struct variables are not generated at all, their offset in memory is kept in fFieldTable
        virtual void visit(DeclareVarInst* inst)
        {
            bool is_struct = (inst->fAddress->getAccess() & Address::kStruct) || (inst->fAddress->getAccess() & Address::kStaticStruct); 
            string prefix = is_struct ? fObjPrefix : "var ";
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
            
            if (array_typed && array_typed->fSize > 1) {
                if (is_struct) {
                    // Keep pointer type
                    fFieldTable[inst->fAddress->getName()] = make_pair(fStructOffset, Typed::getPtrFromType(array_typed->fType->getType()));
                    fStructOffset += array_typed->fSize * NUM_SIZE;
                  } else {
                    if (!inst->fValue) {
                        assert(false);
                        string type = (array_typed->fType->getType() == Typed::kFloat) ? "Float32Array" : "Int32Array";
                        *fOut << prefix << inst->fAddress->getName() << " = new " << type << "(" << array_typed->fSize << ")";
                    }
                }
            } else {
                if (is_struct) {
                    fFieldTable[inst->fAddress->getName()] = make_pair(fStructOffset, inst->fType->getType());
                    fStructOffset += NUM_SIZE;
                } else {
                    *fOut << prefix << inst->fAddress->getName();
                    if (inst->fValue) {
                        *fOut << " = "; inst->fValue->accept(this);
                    } 
                }
            }
            
            if (!is_struct) {
                EndLine();
            }
        }
     
        virtual void generateFunDefArgs(DeclareFunInst* inst)
        {
            *fOut << "(";
            list<NamedTyped*>::const_iterator it;
            int size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                // No type is generated...
                *fOut << (*it)->fName;
                if (i < size - 1) *fOut << ", ";
            }
        }
        
        virtual void generateFunDefBody(DeclareFunInst* inst)
        {
            if (inst->fCode->fCode.size() == 0) {
                *fOut << ");" << endl;  // Pure prototype
            } else {
                // Function body
                *fOut << ") {";
                fTab++;
                tab(fTab, *fOut);
                // Explicit typing needed for function arguments
                list<NamedTyped*>::const_iterator it;
                for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                    *fOut << (*it)->fName;
                    Typed* type = (*it)->fType;
                    if (type->getType() == Typed::kInt || type->getType() == Typed::kObj_ptr) {
                        *fOut << " = (" << (*it)->fName << " | 0);";
                    } else {
                        *fOut << " = +(" << (*it)->fName << ");";
                    }
                    tab(fTab, *fOut); 
                }
                inst->fCode->accept(this);
                fTab--;
                tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            }
        }
    
        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (fFunctionSymbolTable.find(inst->fName) != fFunctionSymbolTable.end()) {
                return;
            } else {
                fFunctionSymbolTable[inst->fName] = 1;
            }
            
            // Math library functions are part of the 'global' module, 'fmodf' and 'log10f' will be manually generated
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                if (fMathLibTable[inst->fName] != "manual") {
                    tab(fTab, *fOut); *fOut << "var " << inst->fName << " = " << fMathLibTable[inst->fName] << ";";
                }
            } else {
                // Prototype
                tab(fTab, *fOut); *fOut << fObjPrefix << "function " << generateFunName(inst->fName);
                generateFunDefArgs(inst);
                generateFunDefBody(inst);
            }
        }
         
        virtual void visit(LoadVarInst* inst)
        {
            fTypingVisitor.visit(inst);
            
            if (fTypingVisitor.fCurType == Typed::kInt
                || fTypingVisitor.fCurType == Typed::kInt_ptr
                || fTypingVisitor.fCurType == Typed::kFloat_ptr
                || fTypingVisitor.fCurType == Typed::kFloatMacro_ptr
                || fTypingVisitor.fCurType == Typed::kObj_ptr) {
                *fOut << "(";
                TextInstVisitor::visit(inst);
                *fOut << " | 0)";
            } else if (fTypingVisitor.fCurType == Typed::kFloatMacro 
                       || fTypingVisitor.fCurType == Typed::kFloat 
                       || fTypingVisitor.fCurType == Typed::kDouble) {      
                *fOut << "+(";
                TextInstVisitor::visit(inst);
                *fOut << ")";
            } else {
                // HACK : completely adhoc code for input/output/count/samplingFreq...
                if ((startWith(inst->getName(), "inputs") 
                    || startWith(inst->getName(), "outputs") 
                    || startWith(inst->getName(), "count")
                    || startWith(inst->getName(), "samplingFreq"))) {
                    *fOut << "(";
                    TextInstVisitor::visit(inst);
                    *fOut << " | 0)";
                } else {
                    TextInstVisitor::visit(inst);
                }
            }
        } 
        
        virtual void visit(NamedAddress* named)
        {   
            if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[named->getName()];
                switch (tmp.second) {
                    case Typed::kFloatMacro:
                    case Typed::kFloat:
                    case Typed::kDouble:
                        *fOut << "HEAPF32[dsp + " << tmp.first << " >> 2]";
                        break;
                    case Typed::kInt:
                        *fOut << "HEAP32[dsp + " << tmp.first << " >> 2]";
                        break;
                    case Typed::kFloatMacro_ptr: 
                    case Typed::kFloat_ptr:
                    case Typed::kDouble_ptr:
                    case Typed::kInt_ptr:
                        *fOut << "dsp + " << tmp.first;
                        break;
                    default:
                        assert(false);
                        break;
                }
            } else {
                *fOut << named->fName;
            }
        }
        
        virtual void visit(IndexedAddress* indexed)
        {
            // HACK : completely adhoc code for inputs/outputs...
            if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
                *fOut << "HEAP32[" << indexed->getName() << " + (";  
                indexed->fIndex->accept(this);
                *fOut << " << 2) >> 2]"; 
            // HACK : completely adhoc code for input/output...
            } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
                *fOut << "HEAPF32[" << indexed->getName() << " + (";  
                indexed->fIndex->accept(this);
                *fOut << " << 2) >> 2]"; 
            } else if (indexed->getAccess() & Address::kStruct || indexed->getAccess() & Address::kStaticStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[indexed->getName()];
                if (tmp.second == Typed::kFloatMacro_ptr || tmp.second == Typed::kFloat_ptr || tmp.second == Typed::kDouble_ptr) {
                    *fOut << "HEAPF32[dsp + " << tmp.first << " + ";  
                    *fOut << "(";
                    indexed->fIndex->accept(this);
                    *fOut << " << 2) >> 2]"; 
                } else {
                    *fOut << "HEAP32[dsp + " << tmp.first << " + "; 
                    *fOut << "(";
                    indexed->fIndex->accept(this);
                    *fOut << " << 2) >> 2]"; 
                }
            } else {
                indexed->fAddress->accept(this);
                *fOut << "["; indexed->fIndex->accept(this); *fOut << "]";
            }
        }
  
        virtual void visit(LoadVarAddressInst* inst)
        {
            // TODO (for vector mode...)
            IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
            if (indexed) {
                if (indexed->getAccess() & Address::kStruct || indexed->getAccess() & Address::kStaticStruct) {
                    pair<int, Typed::VarType> tmp = fFieldTable[indexed->getName()];
                    *fOut << "dsp + " << tmp.first << " + ";  
                    *fOut << "(";
                    indexed->fIndex->accept(this);
                    *fOut << " << 2) >> 2"; 
                } else {
                    assert(false);
                }
            } else {
                assert(false);
            }
        }
                
        // No .f syntax for float in JS
        virtual void visit(FloatNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            // 'dot' syntax for float
            *fOut << checkDouble(inst->fNum);
        }
        
        virtual void visit(IntNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << inst->fNum;
        }
        
        virtual void visit(BoolNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << inst->fNum;
        }
        
        virtual void visit(DoubleNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << checkDouble(inst->fNum);
        }
                 
        virtual void visit(Select2Inst* inst)
        {
            fTypingVisitor.visit(inst);
            
            string fStart = isIntType(fTypingVisitor.fCurType) ? "((" : "+(";
            string fEnd = isIntType(fTypingVisitor.fCurType) ? ") | 0)" : ")";
            
            *fOut << fStart;
            inst->fCond->accept(this);
            *fOut << "?";
            inst->fThen->accept(this);
            *fOut << ":";
            inst->fElse->accept(this);
            *fOut << fEnd;
        }
        
        void visitAuxFloat(BinopInst* inst)
        {
            *fOut << "+(";
            inst->fInst1->accept(this);
            *fOut << " ";
            *fOut << gBinOpTable[inst->fOpcode]->fName;
            *fOut << " ";
            inst->fInst2->accept(this);
            *fOut << ")";
        }
        
        void visitAuxInt(BinopInst* inst)
        {
            // Special case of 32 bits integer multiply
            if (inst->fOpcode == kMul) {
                *fOut << "(imul(";
                inst->fInst1->accept(this);
                *fOut << ", ";
                inst->fInst2->accept(this);
                *fOut << ") | 0)";
            } else {
                *fOut << "((";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
                *fOut << ") | 0)";
            }
        }
        
        virtual void visit(BinopInst* inst)
        {
            if (isBoolOpcode(inst->fOpcode)) {
                *fOut << "((";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
                *fOut << ") | 0)";
            } else {
            
                inst->fInst1->accept(&fTypingVisitor);
                Typed::VarType type1 = fTypingVisitor.fCurType;
                
                if (isRealType(type1)) {
                    visitAuxFloat(inst);
                } else {
                    inst->fInst2->accept(&fTypingVisitor);
                    Typed::VarType type2 = fTypingVisitor.fCurType;
                     if (isRealType(type2)) {
                        visitAuxFloat(inst);
                    } else if (isIntType(type1) || isIntType(type2)) {
                        visitAuxInt(inst);
                    } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                        visitAuxInt(inst);
                    } else {
                        *fOut << "(";
                        inst->fInst1->accept(this);
                        *fOut << " ";
                        *fOut << gBinOpTable[inst->fOpcode]->fName;
                        *fOut << " ";
                        inst->fInst2->accept(this);
                        *fOut << ")";
                    }
                }
            }
            
            fTypingVisitor.visit(inst);
        }
        
        virtual void visit(CastNumInst* inst)
        {
            if (inst->fType->getType() == Typed::kInt) {
                *fOut << "~~(";
                inst->fInst->accept(this);
                *fOut << ")";
            } else if (inst->fType->getType() == Typed::kIntish) {
                *fOut << "((";
                inst->fInst->accept(this);
                *fOut << ") | 0)";
            } else if (isRealType(inst->fType->getType())) {
                *fOut << "+(";
                inst->fInst->accept(this);
                *fOut << ")";
            } else {
                assert(false);
            }
            fTypingVisitor.visit(inst);
        }
     
        // Generate standard funcall (not 'method' like funcall...)
        virtual void visit(FunCallInst* inst)
        {
            *fOut << inst->fName << "(";
            generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
            *fOut << ")";
        }
        
        virtual void visit(ForLoopInst* inst)
        {
            // Don't generate empty loops...
            if (inst->fCode->size() == 0) return;
            
            DeclareVarInst* c99_declare_inst = dynamic_cast<DeclareVarInst*>(inst->fInit);
            StoreVarInst* c99_init_inst = NULL;
            
            if (c99_declare_inst) {
                InstBuilder::genLabelInst("/* C99 loop */")->accept(this);
                *fOut << "{";
                fTab++;
                tab(fTab, *fOut);
                
                // To generate C99 compatible loops...
                c99_init_inst = InstBuilder::genStoreStackVar(c99_declare_inst->getName(), c99_declare_inst->fValue);
                c99_declare_inst = InstBuilder::genDecStackVar(c99_declare_inst->getName(), 
                                                                InstBuilder::genBasicTyped(Typed::kInt), 
                                                                InstBuilder::genIntNumInst(0));
                // C99 loop variable declared outside the loop
                c99_declare_inst->accept(this);
            }
            
            *fOut << "for (";
                fFinishLine = false;
                if (c99_declare_inst) {
                    // C99 loop initialized here
                    c99_init_inst->accept(this);
                } else {
                    // Index already defined
                    inst->fInit->accept(this);
                }
                *fOut << "; ";
                inst->fEnd->accept(this);
                *fOut << "; ";
                inst->fIncrement->accept(this);
                fFinishLine = true;
            *fOut << ") {";
                fTab++;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                fTab--;
                tab(fTab, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
            
            if (c99_declare_inst) {
                fTab--;
                tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            }
        }
};

// Moves all variables declaration at the beginning of the block
struct MoveVariablesInFront1 : public BasicCloneVisitor {
    
    list<DeclareVarInst*> fVarTable;
    
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        fVarTable.push_back(dynamic_cast<DeclareVarInst*>(inst->clone(&cloner)));
        return new DropInst();
    }
    
    BlockInst* getCode(BlockInst* src)
    {
        BlockInst* dst = dynamic_cast<BlockInst*>(src->clone(this));
        // Moved in front..
        for (list<DeclareVarInst*>::reverse_iterator it = fVarTable.rbegin(); it != fVarTable.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        return dst;
    }
    
};

// Moves all variables declaration at the beginning of the block and rewrite them as 'declaration' followed by 'store'
struct MoveVariablesInFront2 : public BasicCloneVisitor {
    
    list<StatementInst*> fVarTable;
      
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        
        if (inst->fValue) {
            if (dynamic_cast<NumValueInst*>(inst->fValue)) {
                fVarTable.push_back(dynamic_cast<DeclareVarInst*>(inst->clone(&cloner)));
                return new StoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
            // "In extension" array definition
            } else if (array_typed) {
                fVarTable.push_back(new DeclareVarInst(inst->fAddress->clone(&cloner), 
                                                        inst->fType->clone(&cloner), 
                                                        InstBuilder::genTypedZero(inst->fType->getType())));
                Typed::VarType ctype = array_typed->fType->getType();
                if (array_typed->fSize > 0) {
                    if (ctype == Typed::kInt) {
                        IntArrayNumInst* int_num_array = dynamic_cast<IntArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(), 
                                                InstBuilder::genIntNumInst(i), 
                                                InstBuilder::genIntNumInst(int_num_array->getValue(i))));
                        }
                    } else if (ctype == Typed::kFloat || ctype == Typed::kFloatMacro) {
                        FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(), 
                                                InstBuilder::genIntNumInst(i), 
                                                InstBuilder::genFloatNumInst(float_array->getValue(i))));
                        }
                    } else if (ctype == Typed::kDouble) {
                        DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(), 
                                                InstBuilder::genIntNumInst(i), 
                                                InstBuilder::genDoubleNumInst(double_array->getValue(i))));
                        }
                    } else {
                        assert(false);
                    }
                    return new DropInst(); 
                } else {
                    return new StoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
                }
            } else {
                fVarTable.push_back(new DeclareVarInst(inst->fAddress->clone(&cloner), 
                                    inst->fType->clone(&cloner), 
                                    InstBuilder::genTypedZero(inst->fType->getType())));
                return new StoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
            }
           
        } else {
            fVarTable.push_back(dynamic_cast<DeclareVarInst*>(inst->clone(&cloner)));
            return new DropInst();
        }
    }
    
    BlockInst* getCode(BlockInst* src)
    {
        BlockInst* dst = dynamic_cast<BlockInst*>(src->clone(this));
        // Moved in front..
        for (list<StatementInst*>::reverse_iterator it = fVarTable.rbegin(); it != fVarTable.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        return dst;
    }
    
};

// Used for subcontainers table generation : rename 'sig' in 'dsp' 
struct DspRenamer : public BasicCloneVisitor {
    
    DspRenamer() 
    {}
    
    // change access
    virtual Address* visit(NamedAddress* named)
    {  
         if (startWith(named->getName(), "sig")) {
             return new NamedAddress("dsp", named->fAccess);
         } else {
             return BasicCloneVisitor::visit(named);
         }
    }
    
    // remove allocation
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        if (startWith(inst->fAddress->getName(), "sig")) {
            return new DropInst();
        } else {
            BasicCloneVisitor cloner;
            return inst->clone(&cloner);
        }
    }
    
    BlockInst* getCode(BlockInst* src)
    {
        return dynamic_cast<BlockInst*>(src->clone(this));
    }
    
};

// Mathematical functions are declared as variables, they have to be generated before any other function (like 'faustpower')
struct sortDeclareFunctions
{
    map <string, string> fMathLibTable;
    
    sortDeclareFunctions(const map <string, string>& table) : fMathLibTable(table)
    {}
    
    bool operator()(StatementInst* a, StatementInst* b)
    { 
        DeclareFunInst* inst1 = dynamic_cast<DeclareFunInst*>(a);
        DeclareFunInst* inst2 = dynamic_cast<DeclareFunInst*>(b);
        
        if (inst1) {
            if (inst2) {
                if (fMathLibTable.find(inst1->fName) != fMathLibTable.end()) {
                    if (fMathLibTable.find(inst2->fName) != fMathLibTable.end()) {
                        return inst1->fName < inst2->fName;
                    } else {
                        return true;
                    }
                } 
            }
        }
        return false;
    }
};

#endif
