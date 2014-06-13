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
#include "../../architecture/faust/gui/JSONUI.h"

class ASMJAVAScriptInstVisitor : public TextInstVisitor {

    private:
    
        JSONUI fJSON;

        /*
         Global functions names table as a static variable in the visitor
         so that each function prototye is generated as most once in the module.
         */
        static map <string, int> gFunctionSymbolTable; 
        map <string, string> fMathLibTable;
        Typed::VarType fCurType;
    
        string fObjPrefix;
        int fStructSize;    // Keep the size in bytes of the structure
    
        map <string, pair<int, Typed::VarType> > fFieldTable;  // Table : field_name, <byte offset in structure, type>
        map <string, string> fPathTable;                       // Table : field_name, complete path

    public:
    
        // Only one shared visitor
        static ASMJAVAScriptInstVisitor* fGlobalVisitor;

        ASMJAVAScriptInstVisitor(std::ostream* out, int tab = 0)
        :TextInstVisitor(out, ".", tab), fJSON(0,0), fCurType(Typed::kNoType) 
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
            fMathLibTable["fmodf"] = "function fmodf(x, y) { x = +x; y = +y; return +(x % y); }";   // Manually generated
            fMathLibTable["logf"] = "global.Math.log";
            fMathLibTable["log10f"] = "function log10f(a) { a = +a; return +(a / +log(10.)); }";    // Manually generated
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
        string getJSON(bool flat) { return fJSON.JSON(flat); }
        map <string, string>& getPathTable() { return fPathTable; }
        map <string, pair<int, Typed::VarType> >& getFieldTable() { return fFieldTable; }

        virtual void visit(AddMetaDeclareInst* inst)
        {
            fJSON.declare(NULL, inst->fKey.c_str(), inst->fValue.c_str());
        }

        virtual void visit(OpenboxInst* inst)
        {
            switch (inst->fOrient) {
                case 0:
                    fJSON.openVerticalBox(inst->fName.c_str());
                    break;
                case 1:
                    fJSON.openHorizontalBox(inst->fName.c_str());
                    break;
                case 2:
                    fJSON.openTabBox(inst->fName.c_str());
                    break;
            }
        }

        virtual void visit(CloseboxInst* inst)
        {
            fJSON.closeBox();
        }
        
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                fJSON.addButton(inst->fLabel.c_str(), NULL);
            } else {
                fJSON.addCheckButton(inst->fLabel.c_str(), NULL);
            }
            
            fPathTable[inst->fZone] = fJSON.buildPath(inst->fLabel);
        }
        
        virtual void visit(AddSliderInst* inst)
        {
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    fJSON.addHorizontalSlider(inst->fLabel.c_str(), NULL, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                    break;
                case AddSliderInst::kVertical:
                    fJSON.addVerticalSlider(inst->fLabel.c_str(), NULL, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                    break;
                case AddSliderInst::kNumEntry:
                    fJSON.addNumEntry(inst->fLabel.c_str(), NULL, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                    break;
            }
            
            fPathTable[inst->fZone] = fJSON.buildPath(inst->fLabel);
        }

        virtual void visit(AddBargraphInst* inst)
        {
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    fJSON.addHorizontalBargraph(inst->fLabel.c_str(), NULL, inst->fMin, inst->fMax);
                    break;
                case AddBargraphInst::kVertical:
                    fJSON.addVerticalBargraph(inst->fLabel.c_str(), NULL, inst->fMin, inst->fMax);
                    break;
            }
            
            fPathTable[inst->fZone] = fJSON.buildPath(inst->fLabel);
        }

        virtual void visit(LabelInst* inst)
        {
            // Empty
        }

        virtual void visit(DeclareVarInst* inst)
        {
            bool is_struct = (inst->fAddress->getAccess() & Address::kStruct);  // Do no generate structure variable, since they are in the global HEAP
            string prefix = (inst->fAddress->getAccess() & Address::kStruct) ? fObjPrefix : "var ";

            if (inst->fValue) {
                if (!is_struct)
                    *fOut << prefix << inst->fAddress->getName() << " = "; inst->fValue->accept(this);
            } else {
                ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
                if (array_typed && array_typed->fSize > 1) {
                    string type = (array_typed->fType->getType() == Typed::kFloat) ? "Float32Array" : "Int32Array";
                    if (!is_struct)
                        *fOut << prefix << inst->fAddress->getName() << " = new " << type << "(" << array_typed->fSize << ")";
                    fFieldTable[inst->fAddress->getName()] = make_pair(fStructSize, array_typed->fType->getType());
                    fStructSize += array_typed->fSize * 4;
                } else {
                    if (!is_struct)
                        *fOut << prefix << inst->fAddress->getName();
                    fFieldTable[inst->fAddress->getName()] = make_pair(fStructSize, inst->fType->getType());
                    fStructSize += 4;
                }
            }
            if (!is_struct)
                EndLine();
        }
        
        virtual void generateFunArgs(DeclareFunInst* inst)
        {
            *fOut << "(";
            list<NamedTyped*>::const_iterator it;
            int size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << (*it)->fName;
                if (i < size - 1) *fOut << ", ";
            }
        }
  
        virtual void generateFunDefArgs(DeclareFunInst* inst)
        {
            *fOut << "(";
            list<NamedTyped*>::const_iterator it;
            int size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << (*it)->fName;
                if (i < size - 1) *fOut << ", ";
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
            
            // Math library functions are part of the 'global' module, fmod and log10 are manually generated
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                tab(fTab, *fOut); *fOut << "var " << inst->fName << " = " << fMathLibTable[inst->fName] << ";";
            } else {
            
                // Prototype
                tab(fTab, *fOut); *fOut << fObjPrefix << "function " << generateFunName(inst->fName);
                generateFunDefArgs(inst);
                generateFunDefBody(inst);
                
            }
        }
        
        /*
        virtual void visit(LoadVarInst* inst)
        {
            TextInstVisitor::visit(inst);
            
            if (gGlobal->gVarTypeTable.find(inst->getName()) != gGlobal->gVarTypeTable.end()) {
                fCurType = gGlobal->gVarTypeTable[inst->getName()]->getType();
                if (dynamic_cast<IndexedAddress*>(inst->fAddress)) {
                    fCurType = Typed::getTypeFromPtr(fCurType);
                }
            } else {
                fCurType = Typed::kNoType;
            }
        } 
        */
        
        
        virtual void visit(LoadVarInst* inst)
        {
            //printf("LoadVarInst inst->getName() %s\n", inst->getName().c_str());
            
            if (gGlobal->gVarTypeTable.find(inst->getName()) != gGlobal->gVarTypeTable.end()) {
                fCurType = gGlobal->gVarTypeTable[inst->getName()]->getType();
                if (dynamic_cast<IndexedAddress*>(inst->fAddress)) {
                    fCurType = Typed::getTypeFromPtr(fCurType);
                }
            } else {
                fCurType = Typed::kNoType;
            }
            
            if (fCurType == Typed::kInt) {
                 
                *fOut << "(";
                TextInstVisitor::visit(inst);
                *fOut << " | 0)";
            
            } else if (fCurType == Typed::kFloatMacro || fCurType == Typed::kFloat) {
                
                *fOut << "+(";
                TextInstVisitor::visit(inst);
                *fOut << ")";
                
            } else {
                // HACK : completely adhoc code for input/output/count...
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
            if (named->getAccess() & Address::kStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[named->getName()];
                if (tmp.second == Typed::kFloatMacro || tmp.second == Typed::kFloat) {
                    *fOut << "HEAPF32[dsp + " << tmp.first << " >> 2]";
                } else {
                    *fOut << "HEAP32[dsp + " << tmp.first << " >> 2]";
                }
            } else {
                *fOut << named->fName;
            }
        }
    
        inline bool startWith(const string& str, const string& prefix)
        {
            return (str.substr(0, prefix.size()) == prefix);
        }
        
        virtual void visit(IndexedAddress* indexed)
        {
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
            } else if (indexed->getAccess() & Address::kStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[indexed->getName()];
                if (tmp.second == Typed::kFloatMacro || tmp.second == Typed::kFloat) {
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
           // Not implemented in JavaScript
            assert(false);
        }
                
        // No .f syntax for float in JS
        virtual void visit(FloatNumInst* inst)
        {
            //*fOut << inst->fNum;
            
            // 'dot' syntax for float
            *fOut << checkDouble(inst->fNum);
            fCurType = Typed::kFloat;
        }
        
        virtual void visit(IntNumInst* inst)
        {
            *fOut << inst->fNum;
            fCurType = Typed::kInt;
        }
        
        virtual void visit(BoolNumInst* inst)
        {
            *fOut << inst->fNum;
            fCurType = Typed::kBool;
        }
        
        virtual void visit(DoubleNumInst* inst)
        {
            //*fOut << inst->fNum;
            *fOut << checkDouble(inst->fNum);
            fCurType = Typed::kInt;
        }
    
        /*
        // No .f syntax for float in JS
        virtual void visit(FloatNumInst* inst)
        {
            *fOut << "+(" << inst->fNum << ")";
            fCurType = Typed::kFloat;
        }
        
        virtual void visit(IntNumInst* inst)
        {
            *fOut << "(" << inst->fNum << " | 0)";
            fCurType = Typed::kInt;
        }
        
        virtual void visit(BoolNumInst* inst)
        {
            *fOut << "(" << inst->fNum << " | 0)";
            fCurType = Typed::kBool;
        }
        
        // No . syntax for double in JS
        virtual void visit(DoubleNumInst* inst)
        {
            *fOut << inst->fNum;
            fCurType = Typed::kInt;
        }
        */
    
        /*
        virtual void visit(BinopInst* inst)
        {
            if (inst->fOpcode >= kGT && inst->fOpcode < kAND) {
                *fOut << "(";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
                *fOut << ")";
                fCurType = Typed::kBool;
            } else {
                
                inst->fInst1->accept(fGlobalVisitor);
                Typed::VarType type1 = fGlobalVisitor->fCurType;
                
                inst->fInst2->accept(fGlobalVisitor);
                Typed::VarType type2 = fGlobalVisitor->fCurType;
                
                if (type1 == Typed::kInt && type2 == Typed::kInt) {
                    if (inst->fOpcode == kMul) {
                        *fOut << "Math.imul(";
                        inst->fInst1->accept(this);
                        *fOut << ", ";
                        inst->fInst2->accept(this);
                        *fOut << ")";
                    } else {
                        *fOut << "(";
                        inst->fInst1->accept(this);
                        *fOut << " ";
                        *fOut << gBinOpTable[inst->fOpcode]->fName;
                        *fOut << " ";
                        inst->fInst2->accept(this);
                        *fOut << ")";
                    }
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kInt && type2 == Typed::kFloat) {
                    *fOut << "(";
                    //*fOut << "(float)";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kFloat && type2 == Typed::kInt) {
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "(float)";
                    inst->fInst2->accept(this); 
                    *fOut << ")";
                    fCurType = Typed::kFloat;   
                } else if (type1 == Typed::kFloat && type2 == Typed::kFloat) {
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kInt && type2 == Typed::kBool) {
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "((";
                    inst->fInst2->accept(this);
                    //*fOut << ")?1:0)";
                    *fOut << ")";
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kBool && type2 == Typed::kInt) {
                    *fOut << "(";
                    //*fOut << "((";
                    inst->fInst1->accept(this);
                    //*fOut << ")?1:0)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << " | 0)";
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                    *fOut << "(";
                    //*fOut << "((";
                    inst->fInst1->accept(this);
                    //*fOut << ")?1:0)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "((";
                    inst->fInst2->accept(this);
                    //*fOut << ")?1:0)";
                    *fOut << ")";
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kFloat && type2 == Typed::kBool) {
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "((";
                    inst->fInst2->accept(this);
                    //*fOut << ")?1.f:0.f)";
                    *fOut << ")";
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kBool && type2 == Typed::kFloat) {
                    *fOut << "(";
                    //*fOut << "((";
                    inst->fInst1->accept(this);
                    //*fOut << ")?1.f:0.f)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    fCurType = Typed::kFloat;
                    *fOut << ")";
                } else { // Default
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    fCurType = Typed::kNoType;
                    *fOut << ")";
                }  
            }
        }
        */
        
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
                fCurType = Typed::kBool;
            } else {
                
                inst->fInst1->accept(fGlobalVisitor);
                Typed::VarType type1 = fGlobalVisitor->fCurType;
                
                inst->fInst2->accept(fGlobalVisitor);
                Typed::VarType type2 = fGlobalVisitor->fCurType;
                
                //printf("visit(BinopInst* inst) %d %d\n", type1, type2);
                
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
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kInt && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro)) {
                    *fOut << "+(";
                    //*fOut << "(float)";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                    fCurType = Typed::kFloat;
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro) && type2 == Typed::kInt) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "(float)";
                    inst->fInst2->accept(this); 
                    *fOut << ")";
                    fCurType = Typed::kFloat;   
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro) && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro)) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kInt && type2 == Typed::kBool) {
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "((";
                    inst->fInst2->accept(this);
                    //*fOut << ")?1:0)";
                    *fOut << " | 0)";
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kBool && type2 == Typed::kInt) {
                    *fOut << "(";
                    //*fOut << "((";
                    inst->fInst1->accept(this);
                    //*fOut << ")?1:0)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << " | 0)";
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                    *fOut << "(";
                    //*fOut << "((";
                    inst->fInst1->accept(this);
                    //*fOut << ")?1:0)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "((";
                    inst->fInst2->accept(this);
                    //*fOut << ")?1:0)";
                    *fOut << " | 0)";
                    fCurType = Typed::kInt;
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro) && type2 == Typed::kBool) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "((";
                    inst->fInst2->accept(this);
                    //*fOut << ")?1.f:0.f)";
                    *fOut << ")";
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kBool && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro)) {
                    *fOut << "+(";
                    //*fOut << "((";
                    inst->fInst1->accept(this);
                    //*fOut << ")?1.f:0.f)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    fCurType = Typed::kFloat;
                    *fOut << ")";
                } else { // Default
                    *fOut << "(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    fCurType = Typed::kNoType;
                    *fOut << ")";
                }  
            }
        }
        
        /*
        virtual void visit(CastNumInst* inst)
        {
            // No explicit cast generation
            inst->fInst->accept(this);
        }
        */
        
        virtual void visit(CastNumInst* inst)
        {
            if (generateType(inst->fType) == "int") {
                //if (fCurType != Typed::kInt) {
                    *fOut << "~~(";
                    //*fOut << "(";
                    inst->fInst->accept(this);
                    *fOut << ")";
                    //*fOut << " | 0)";
                    fCurType = Typed::kInt;
                /*
                } else {
                    // No explicit cast generation
                    inst->fInst->accept(this);
                }
                 */
            } else {
                //if (fCurType == Typed::kFloat || fCurType == Typed::kFloatMacro) {
                    // No explicit cast generation
                //    inst->fInst->accept(this);
                
                //} else {
                    *fOut << "+(";
                    inst->fInst->accept(this);
                    *fOut << ")";
                    fCurType = Typed::kFloat;
               // }
                 
            }
        }
        
        
        /*
        virtual void visit(FunCallInst* inst)
        {
            string fun_name = (fMathLibTable.find(inst->fName) != fMathLibTable.end()) ? fMathLibTable[inst->fName] : inst->fName;
            generateFunCall(inst, fun_name);
        }
        */
    
        // All function calls are casted with the correct function result type
        virtual void visit(FunCallInst* inst)
        {
            generateFunCall(inst, inst->fName);
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
        return dst;
    }
    
};

#endif
