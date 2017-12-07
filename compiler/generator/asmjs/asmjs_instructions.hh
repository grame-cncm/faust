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

#include <iomanip>
#include <sstream>
#include <iostream>

#include "text_instructions.hh"
#include "typing_instructions.hh"

using namespace std;

#define offStr ((gGlobal->gFloatSize == 1) ? "2" : ((gGlobal->gFloatSize == 2) ? "3" : ""))

class ASMJAVAScriptInstVisitor : public TextInstVisitor {

    private:
    
        TypingVisitor fTypingVisitor;
        map <string, int> fFunctionSymbolTable; 
        map <string, string> fMathLibTable;
        map <string, pair<int, Typed::VarType> > fFieldTable;   // Table : field_name, <byte offset in structure, type>
        int fStructOffset;                                      // Keep the offset in bytes of the structure
        int fSubContainerType;
    
        string ensureFloat(string str)
        {
            bool dot = false;
            int e_pos = -1;
            for (unsigned int i = 0; i < str.size(); i++) {
                if (str[i] == '.') {
                    dot = true;
                    break;
                } else if (str[i] == 'e') {
                    e_pos = i;
                    break;
                }
            }
            
            if (e_pos >= 0) {
                return str.insert(e_pos, 1, '.');
            } else {
                return (dot) ? str : (str + ".");
            }
        }
        
        // Special version without termination
        template <class T>
        string checkReal(T val)
        {
            std::stringstream num;
            num << std::setprecision(std::numeric_limits<T>::max_digits10) << val;
            return ensureFloat(num.str());
        }
    
    public:
    
        ASMJAVAScriptInstVisitor(std::ostream* out, int tab = 0)
            :TextInstVisitor(out, ".", ifloat(), "", tab)
        {
            // Integer version
            fMathLibTable["abs"] = "foreign.abs";
            fMathLibTable["min_i"] = "foreign.min";
            fMathLibTable["max_i"] = "foreign.max";
            
            // Float version
            fMathLibTable["fabsf"] = "foreign.abs";
            fMathLibTable["acosf"] = "foreign.acos";
            fMathLibTable["asinf"] = "foreign.asin";
            fMathLibTable["atanf"] = "foreign.atan";
            fMathLibTable["atan2f"] = "foreign.atan2";
            fMathLibTable["ceilf"] = "foreign.ceil";
            fMathLibTable["cosf"] = "foreign.cos";
            fMathLibTable["expf"] = "foreign.exp";
            fMathLibTable["floorf"] = "foreign.floor";
            fMathLibTable["fmodf"] = "manual";          // Manually generated
            fMathLibTable["logf"] = "foreign.log";
            fMathLibTable["log10f"] = "manual";         // Manually generated
            fMathLibTable["max_f"] = "foreign.max";
            fMathLibTable["min_f"] = "foreign.min";
            fMathLibTable["powf"] = "foreign.pow";
            fMathLibTable["remainderf"] = "manual";     // Manually generated
            fMathLibTable["roundf"] = "foreign.round";
            fMathLibTable["sinf"] = "foreign.sin";
            fMathLibTable["sqrtf"] = "foreign.sqrt";
            fMathLibTable["tanf"] = "foreign.tan";
            
            // Double version
            fMathLibTable["fabs"] = "foreign.abs";
            fMathLibTable["acos"] = "foreign.acos";
            fMathLibTable["asin"] = "foreign.asin";
            fMathLibTable["atan"] = "foreign.atan";
            fMathLibTable["atan2"] = "foreign.atan2";
            fMathLibTable["ceil"] = "foreign.ceil";
            fMathLibTable["cos"] = "foreign.cos";
            fMathLibTable["exp"] = "foreign.exp";
            fMathLibTable["floor"] = "foreign.floor";
            fMathLibTable["fmod"] = "manual";           // Manually generated
            fMathLibTable["log"] = "foreign.log";
            fMathLibTable["log10"] = "manual";          // Manually generated
            fMathLibTable["max_"] = "foreign.max";
            fMathLibTable["min_"] = "foreign.min";
            fMathLibTable["pow"] = "foreign.pow";
            fMathLibTable["remainder"] = "manual";      // Manually generated
            fMathLibTable["round"] = "foreign.round";
            fMathLibTable["sin"] = "foreign.sin";
            fMathLibTable["sqrt"] = "foreign.sqrt";
            fMathLibTable["tan"] = "foreign.tan";
            
            fStructOffset = 0;
            fSubContainerType = -1;
        }

        virtual ~ASMJAVAScriptInstVisitor()
        {}
    
        void setSubContainerType(int type) { fSubContainerType = type; }
    
        int getStructSize() { return fStructOffset; }
    
        map <string, pair<int, Typed::VarType> >& getFieldTable() { return fFieldTable; }
    
        map <string, string>& getMathLibTable() { return fMathLibTable; }
    
        int getFieldOffset(const string& name)
        {
            return (fFieldTable.find(name) != fFieldTable.end()) ? fFieldTable[name].first : -1;
        }

        // Struct variables are not generated at all, their offset in memory is kept in fFieldTable
        virtual void visit(DeclareVarInst* inst)
        {
            bool is_struct = (inst->fAddress->getAccess() & Address::kStruct) || (inst->fAddress->getAccess() & Address::kStaticStruct); 
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
            
            if (array_typed && array_typed->fSize > 1) {
                if (is_struct) {
                    // Keep pointer type
                    fFieldTable[inst->fAddress->getName()] = make_pair(fStructOffset, Typed::getPtrFromType(array_typed->fType->getType()));
                    fStructOffset += (array_typed->fSize * audioSampleSize()); // Always use biggest size so that int/real access are correctly aligned
                } else {
                    // Should never happen...
                    faustassert(false);
                }
            } else {
                if (is_struct) {
                    fFieldTable[inst->fAddress->getName()] = make_pair(fStructOffset, inst->fType->getType());
                    fStructOffset += audioSampleSize(); // Always use biggest size so that int/real access are correctly aligned
                } else {
                    *fOut << "var " << inst->fAddress->getName();
                    if (inst->fValue) {
                        *fOut << " = "; inst->fValue->accept(this);
                    }
                    EndLine();
                }
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
                    if (type->getType() == Typed::kInt32 || type->getType() == Typed::kObj_ptr) {
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
                tab(fTab, *fOut); *fOut << "function " << generateFunName(inst->fName);
                generateFunDefArgs(inst);
                generateFunDefBody(inst);
            }
        }
         
        virtual void visit(LoadVarInst* inst)
        {
            fTypingVisitor.visit(inst);
            
            if (isIntOrPtrType(fTypingVisitor.fCurType)) {
                *fOut << "(";
                inst->fAddress->accept(this);
                *fOut << " | 0)";
            } else if (isRealType(fTypingVisitor.fCurType)) {
                *fOut << "+(";
                inst->fAddress->accept(this);
                *fOut << ")";
            } else {
                // HACK : completely adhoc code for inputs/outputs...
                if (startWith(inst->getName(), "inputs") || startWith(inst->getName(), "outputs")) {
                    *fOut << "(";
                    inst->fAddress->accept(this);
                    *fOut << " | 0)";
                } else {
                    inst->fAddress->accept(this);
                }
            }
        }
        
        virtual void visit(NamedAddress* named)
        {
            // Fields in struct are accessed using 'dsp' and an offset
            if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[named->getName()];
                if (isRealType(tmp.second)) {
                    *fOut << "HEAPF[dsp + " << tmp.first << " >> " << offStr << "]";
                } else if (isIntType(tmp.second)) {
                    *fOut << "HEAP32[dsp + " << tmp.first << " >> 2]";
                } else if (isPtrType(tmp.second)) {
                    *fOut << "dsp + " << tmp.first;
                } else {
                    faustassert(false);
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
                // Force "output" access to be coherent with fSubContainerType (integer or real)
                *fOut << ((fSubContainerType == kInt) ? "HEAP32[" : "HEAPF[") << indexed->getName() << " + (";
                indexed->fIndex->accept(this);
                // Force "output" access to be coherent with fSubContainerType (integer or real)
                if (fSubContainerType == kInt) {
                    *fOut << " << 2) >> 2]";
                } else {
                    *fOut << " << " << offStr << ") >> " << offStr << "]";
                }
            } else {
                // Fields in struct are accessed using 'dsp' and an offset
                pair<int, Typed::VarType> tmp = fFieldTable[indexed->getName()];
                if (isRealPtrType(tmp.second)) {
                    *fOut << "HEAPF[dsp + " << tmp.first << " + (";
                    indexed->fIndex->accept(this);
                    *fOut << " << " << offStr << ") >> " << offStr << "]";
                 } else {
                    *fOut << "HEAP32[dsp + " << tmp.first << " + (";
                    indexed->fIndex->accept(this);
                    *fOut << " << 2) >> 2]"; 
                }
            }
        }
  
        virtual void visit(LoadVarAddressInst* inst)
        {
            // TODO (for vector mode...)
            IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
            if (indexed) {
                // Fields in struct are accessed using 'dsp' and an offset
                if (indexed->getAccess() & Address::kStruct || indexed->getAccess() & Address::kStaticStruct) {
                    pair<int, Typed::VarType> tmp = fFieldTable[indexed->getName()];
                    *fOut << "dsp + " << tmp.first << " + (";
                    indexed->fIndex->accept(this);
                    *fOut << " << 2) >> 2"; 
                } else {
                    // Should never happen...
                    faustassert(false);
                }
            } else {
                // Should never happen...
                faustassert(false);
            }
        }
    
        virtual void visit(FloatNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << checkReal<float>(inst->fNum);
        }
        
        virtual void visit(Int32NumInst* inst)
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
            *fOut << checkReal<double>(inst->fNum);
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
            // Special case for 32 bits integer multiply
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
                        // Should never happen...
                        faustassert(false);
                    }
                }
            }
            
            fTypingVisitor.visit(inst);
        }
        
        virtual void visit(::CastInst* inst)
        {
            if (inst->fType->getType() == Typed::kInt32) {
                *fOut << "~~(";
                inst->fInst->accept(this);
                *fOut << ")";
            } else if (inst->fType->getType() == Typed::kInt32ish) {
                *fOut << "((";
                inst->fInst->accept(this);
                *fOut << ") | 0)";
            } else if (isRealType(inst->fType->getType())) {
                *fOut << "+(";
                inst->fInst->accept(this);
                *fOut << ")";
            } else {
                faustassert(false);
            }
            fTypingVisitor.visit(inst);
        }
    
        virtual void visit(BitcastInst* inst) { faustassert(false); }
     
        // Generate standard funcall (not 'method' like funcall...)
        virtual void visit(FunCallInst* inst)
        {
            *fOut << inst->fName << "(";
            generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
            *fOut << ")";
        }

};

#endif
