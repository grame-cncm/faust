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

static inline bool startWith(const string& str, const string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

static inline string startWithRes(const string& str, const string& prefix)
{   
    return (str.substr(0, prefix.size()) == prefix) ? str.substr(prefix.size()) : "";
}

class ASMJAVAScriptInstVisitor : public TextInstVisitor {

    private:
    
        TypingVisitor fTypingVisitor;

        /*
         Global functions names table as a static variable in the visitor
         so that each function prototye is generated as most once in the module.
         */
        map <string, int> gFunctionSymbolTable; 
        map <string, string> fMathLibTable;
       
        string fObjPrefix;
        int fStructSize;    // Keep the size in bytes of the structure
    
        map <string, pair<int, Typed::VarType> > fFieldTable;  // Table : field_name, <byte offset in structure, type>
    
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
            fStructSize = 0;
        }

        virtual ~ASMJAVAScriptInstVisitor()
        {}
    
        int getStructSize() { return fStructSize; }
        map <string, pair<int, Typed::VarType> >& getFieldTable() { return fFieldTable; }
        map <string, string>& getMathLibTable() { return fMathLibTable; }

        virtual void visit(LabelInst* inst)
        {
            // Empty
        }

        // Struct variables are not generated at all, their offset in memory is kept in fFieldTable
        virtual void visit(DeclareVarInst* inst)
        {
            //bool is_struct = (inst->fAddress->getAccess() & Address::kStruct);  // Do no generate structure variable, since they are in the global HEAP
            //string prefix = (inst->fAddress->getAccess() & Address::kStruct) ? fObjPrefix : "var ";
            
            bool is_struct = (inst->fAddress->getAccess() & Address::kStruct) 
                || (inst->fAddress->getAccess() & Address::kStaticStruct);  // Do no generate structure variable, since they are in the global HEAP
            string prefix = is_struct ? fObjPrefix : "var ";
         
            if (inst->fValue) {
                if (!is_struct)
                    *fOut << prefix << inst->fAddress->getName() << " = "; inst->fValue->accept(this);
            } else {
                ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
                if (array_typed && array_typed->fSize > 1) {
                    string type = (array_typed->fType->getType() == Typed::kFloat) ? "Float32Array" : "Int32Array";
                    if (!is_struct)
                        *fOut << prefix << inst->fAddress->getName() << " = new " << type << "(" << array_typed->fSize << ")";
                    //fFieldTable[inst->fAddress->getName()] = make_pair(fStructSize, array_typed->fType->getType());
                    
                    // KEEP PTR type
                    fFieldTable[inst->fAddress->getName()] = make_pair(fStructSize, Typed::getPtrFromType(array_typed->fType->getType()));
                    //printf("DeclareVarInst %s offset %d  size %d \n", inst->fAddress->getName().c_str(), fStructSize, array_typed->fSize * 4);
                    fStructSize += array_typed->fSize * 4;
                } else {
                    if (!is_struct)
                        *fOut << prefix << inst->fAddress->getName();
                    fFieldTable[inst->fAddress->getName()] = make_pair(fStructSize, inst->fType->getType());
                    //printf("DeclareVarInst %s offset %d  size %d \n", inst->fAddress->getName().c_str(), fStructSize, 4);
                    fStructSize += 4;
                }
            }
            if (!is_struct)
                EndLine();
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
                    Typed* type = (*it)->fType;
                    if (type->getType() == Typed::kInt || type->getType() == Typed::kObj_ptr) {
                        *fOut << (*it)->fName << " = " << (*it)->fName << " | 0;";
                    } else {
                        *fOut << (*it)->fName << " = " << "+" << (*it)->fName << ";";
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
            if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
                return;
            } else {
                gFunctionSymbolTable[inst->fName] = 1;
            }
            
            //printf("visit(DeclareFunInst* inst) %s\n", inst->fName.c_str());
            
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
            
            //printf("LoadVarInst %s\n", inst->fAddress->getName().c_str());
            
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
                
                // HACK : completely adhoc code for input/output/count... (TO CHEK ??)
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
                 
                //TextInstVisitor::visit(inst);
            }
        } 
        
        virtual void visit(NamedAddress* named)
        {   
            //printf("NamedAddress %s\n", named->getName().c_str());
            
            if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[named->getName()];
                switch (tmp.second) {
                    case Typed::kFloatMacro:
                    case Typed::kFloat:
                    case Typed::kDouble:
                        *fOut << "HEAPF32[dsp + " << tmp.first << " >> 2]";
                        break;
                    case Typed::kFloatMacro_ptr: 
                    case Typed::kFloat_ptr:
                    case Typed::kDouble_ptr:
                        *fOut << "dsp + " << tmp.first;
                        break;
                    case Typed::kInt:
                        *fOut << "HEAP32[dsp + " << tmp.first << " >> 2]";
                        break;
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
            //printf("IndexedAddress %s\n", indexed->getName().c_str());
            // PTR size is 4 bytes
            
            // HACK : completely adhoc code for input/output...
            if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
                *fOut << "HEAP32[" << indexed->getName() << " + ";  
                *fOut << "(";
                indexed->fIndex->accept(this);
                *fOut << " << 2)"; 
                *fOut << " >> 2]";
            } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
                *fOut << "HEAPF32[" << indexed->getName() << " + ";  
                *fOut << "(";
                indexed->fIndex->accept(this);
                *fOut << " << 2)";       
                *fOut << " >> 2]";
            //} else if (indexed->getAccess() & Address::kStruct) {
            } else if (indexed->getAccess() & Address::kStruct || indexed->getAccess() & Address::kStaticStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[indexed->getName()];
                //printf("IndexedAddress %s %d\n", indexed->getName().c_str(), tmp.second);
                //if (tmp.second == Typed::kFloatMacro || tmp.second == Typed::kFloat || tmp.second == Typed::kDouble) {
                // KEEP PTR
                if (tmp.second == Typed::kFloatMacro_ptr || tmp.second == Typed::kFloat_ptr || tmp.second == Typed::kDouble_ptr) {
                    *fOut << "HEAPF32[dsp + " << tmp.first << " + ";  
                    *fOut << "(";
                    indexed->fIndex->accept(this);
                    *fOut << " << 2)";       
                    *fOut << " >> 2]";
                } else {
                    *fOut << "HEAP32[dsp + " << tmp.first << " + "; 
                    *fOut << "(";
                    indexed->fIndex->accept(this);
                    *fOut << " << 2)";        
                    *fOut << " >> 2]";
                }
            } else {
                indexed->fAddress->accept(this);
                *fOut << "["; indexed->fIndex->accept(this); *fOut << "]";
            }
        }
  
        virtual void visit(LoadVarAddressInst* inst)
        {
           // Not implemented in ASMJavaScript
            assert(false);
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
           
        virtual void visit(BinopInst* inst)
        {
            if (inst->fOpcode >= kGT && inst->fOpcode < kAND) {
                *fOut << "(";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
                *fOut << " | 0)";
            } else {
                
                inst->fInst1->accept(&fTypingVisitor);
                Typed::VarType type1 = fTypingVisitor.fCurType;
                
                inst->fInst2->accept(&fTypingVisitor);
                Typed::VarType type2 = fTypingVisitor.fCurType;
                
                if (type1 == Typed::kInt && type2 == Typed::kInt) {
                    // Special case of 32 bits integer multiply
                    if (inst->fOpcode == kMul) {
                        *fOut << "(imul(";
                        inst->fInst1->accept(this);
                        *fOut << ", ";
                        inst->fInst2->accept(this);
                        *fOut << ") | 0)";
                    } else {
                        *fOut << "(";
                        inst->fInst1->accept(this);
                        *fOut << " ";
                        *fOut << gBinOpTable[inst->fOpcode]->fName;
                        *fOut << " ";
                        inst->fInst2->accept(this);
                        *fOut << " | 0)";
                    }
                } else if (type1 == Typed::kInt && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro || type2 == Typed::kDouble)) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro || type1 == Typed::kDouble) && type2 == Typed::kInt) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this); 
                    *fOut << ")";
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro || type1 == Typed::kDouble) 
                            && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro || type2 == Typed::kDouble)) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                } else if (type1 == Typed::kInt && type2 == Typed::kBool) {
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << " | 0)";
                } else if (type1 == Typed::kBool && type2 == Typed::kInt) {
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << " | 0)";
                } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << " | 0)";
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro || type1 == Typed::kDouble) && type2 == Typed::kBool) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                } else if (type1 == Typed::kBool && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro || type2 == Typed::kDouble)) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                } else { // Default
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
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
                *fOut << "(";
                inst->fInst->accept(this);
                *fOut << " | 0)";
            } else if (inst->fType->getType() == Typed::kFloatMacro 
                       || inst->fType->getType() == Typed::kFloat
                       || inst->fType->getType() == Typed::kFloatish
                       || inst->fType->getType() == Typed::kDouble
                       || inst->fType->getType() == Typed::kDoublish) {
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
                c99_declare_inst = InstBuilder::genDecStackVar(c99_declare_inst->getName(), InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
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
    
    list<DeclareVarInst*> fVarTable;
    
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        // For variable declaration that is not a number, separate the declaration and the store
        if (inst->fValue && !dynamic_cast<NumValueInst*>(inst->fValue)) {
            fVarTable.push_back(new DeclareVarInst(inst->fAddress->clone(&cloner), inst->fType->clone(&cloner), InstBuilder::genTypedZero(inst->fType->getType())));
            return new StoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
        } else {
            fVarTable.push_back(dynamic_cast<DeclareVarInst*>(inst->clone(&cloner)));
            return new DropInst();
        }
    }
    
    BlockInst* getCode(BlockInst* src)
    {
        BlockInst* dst = dynamic_cast< BlockInst*>(src->clone(this));
        // Moved in front..
        for (list<DeclareVarInst*>::reverse_iterator it = fVarTable.rbegin(); it != fVarTable.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        BasicCloneVisitor cloner;
        return dst;
    }
    
};

// Used for subcontainers table generation
struct DspRenamer : public BasicCloneVisitor {
    
    map <string, pair<int, Typed::VarType> > fFieldTable;
    
    DspRenamer(const map <string, pair<int, Typed::VarType> >& field_table) : fFieldTable(field_table)
    {}
 
    
    virtual Address* visit(NamedAddress* named)
    {  
         if (startWith(named->getName(), "sig")) {
             return new NamedAddress("dsp", named->fAccess);
         } else {
             return BasicCloneVisitor::visit(named);
         }
    }
    
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
        BlockInst* dst = dynamic_cast< BlockInst*>(src->clone(this));
        return dst;
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
