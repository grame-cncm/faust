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
            fMathLibTable["abs"] = "Math.abs";
            fMathLibTable["absf"] = "Math.abs";
            fMathLibTable["fabsf"] = "Math.abs";
            fMathLibTable["acosf"] = "Math.acos";
            fMathLibTable["asinf"] = "Math.asin";
            fMathLibTable["atanf"] = "Math.atan";
            fMathLibTable["atan2f"] = "Math.atan2";
            fMathLibTable["ceilf"] = "Math.ceil";
            fMathLibTable["cosf"] = "Math.cos";
            fMathLibTable["expf"] = "Math.exp";
            fMathLibTable["floorf"] = "Math.floor";
            fMathLibTable["fmodf"] = "function fmod(a, b) { return a % b; }";
            fMathLibTable["logf"] = "Math.log";
            fMathLibTable["log10f"] = "function log10(a) { return Math.log(a)/Math.log(10); }";
            fMathLibTable["max"] = "Math.max";
            fMathLibTable["min"] = "Math.min";
            fMathLibTable["powf"] = "Math.pow";
            fMathLibTable["roundf"] = "Math.round";
            fMathLibTable["sinf"] = "Math.sin";
            fMathLibTable["sqrtf"] = "Math.sqrt";
            fMathLibTable["tanf"] = "Math.tan";
            
            fObjPrefix = "that.";
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
            *fOut << "ui_interface.declare(\"" << inst->fZone << "\", \"" << inst->fKey << "\", \"" << inst->fValue << "\")";
            fJSON.declare(NULL, inst->fKey.c_str(), inst->fValue.c_str());
            EndLine();
        }

        virtual void visit(OpenboxInst* inst)
        {
            string name;
            switch (inst->fOrient) {
                case 0:
                    name = "ui_interface.openVerticalBox"; 
                    fJSON.openVerticalBox(inst->fName.c_str());
                    break;
                case 1:
                    name = "ui_interface.openHorizontalBox";
                    fJSON.openHorizontalBox(inst->fName.c_str());
                    break;
                case 2:
                    name = "ui_interface.openTabBox";
                    fJSON.openTabBox(inst->fName.c_str());
                    break;
            }
            *fOut << name << "(" << "\"" << inst->fName << "\"" << ")";
            EndLine();
        }

        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "ui_interface.closeBox();"; tab(fTab, *fOut);
            fJSON.closeBox();
        }
        
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                *fOut << "ui_interface.addButton(" << "\"" << inst->fLabel << "\"" << ", ";
                fJSON.addButton(inst->fLabel.c_str(), NULL);
            } else {
                *fOut << "ui_interface.addCheckButton(" << "\"" << inst->fLabel << "\"" << ", ";
                fJSON.addCheckButton(inst->fLabel.c_str(), NULL);
            }
            
            fPathTable[inst->fZone] = fJSON.buildPath(inst->fLabel);
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this))";
            EndLine();
        }
        
        virtual void visit(AddSliderInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    name = "ui_interface.addHorizontalSlider"; 
                    fJSON.addHorizontalSlider(inst->fLabel.c_str(), NULL, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                    break;
                case AddSliderInst::kVertical:
                    name = "ui_interface.addVerticalSlider";
                    fJSON.addVerticalSlider(inst->fLabel.c_str(), NULL, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                    break;
                case AddSliderInst::kNumEntry:
                    name = "ui_interface.addNumEntry"; 
                    fJSON.addNumEntry(inst->fLabel.c_str(), NULL, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                    break;
            }
            
            fPathTable[inst->fZone] = fJSON.buildPath(inst->fLabel);
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", ";
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this)";
            *fOut << ", " << inst->fInit << ", " << inst->fMin << ", " << inst->fMax << ", " << inst->fStep << ")";
            EndLine();
        }

        virtual void visit(AddBargraphInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    name = "ui_interface.addHorizontalBargraph"; 
                    fJSON.addHorizontalBargraph(inst->fLabel.c_str(), NULL, inst->fMin, inst->fMax);
                    break;
                case AddBargraphInst::kVertical:
                    name = "ui_interface.addVerticalBargraph"; 
                    fJSON.addVerticalBargraph(inst->fLabel.c_str(), NULL, inst->fMin, inst->fMax);
                    break;
            }
            
            fPathTable[inst->fZone] = fJSON.buildPath(inst->fLabel);
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", ";
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this)";
            *fOut << ", " << inst->fMin << ", " << inst->fMax << ")";
            EndLine();
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
            
            // Do not declare Math library functions
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                return;
            }
        
            // Prototype
            *fOut << fObjPrefix << generateFunName(inst->fName) << " = " << "function";
            generateFunDefArgs(inst);
            generateFunDefBody(inst);
        }
        
        
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
        
        /*
        virtual void visit(LoadVarInst* inst)
        {
            *fOut << "(";
            TextInstVisitor::visit(inst);
            
            if (gGlobal->gVarTypeTable.find(inst->getName()) != gGlobal->gVarTypeTable.end()) {
                fCurType = gGlobal->gVarTypeTable[inst->getName()]->getType();
                if (dynamic_cast<IndexedAddress*>(inst->fAddress)) {
                    fCurType = Typed::getTypeFromPtr(fCurType);
                }
            } else {
                fCurType = Typed::kNoType;
            }
            
            if (fCurType == Typed::kInt) {
                *fOut << " | 0)";
            } else {
                *fOut << ")";
            }
        } 
        */
        
        virtual void visit(NamedAddress* named)
        {   
            if (named->getAccess() & Address::kStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[named->getName()];
                if (tmp.second == Typed::kFloatMacro || tmp.second == Typed::kFloat) {
                    *fOut << "Module.HEAPF32[dsp + " << tmp.first << " >> 2]";
                } else {
                    *fOut << "Module.HEAP32[dsp + " << tmp.first << " >> 2]";
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
            
            // To test : completely adhoc code for input/output...
            if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
                *fOut << "Module.HEAP32[" << indexed->getName() << " + ";  
                *fOut << "(";
                indexed->fIndex->accept(this);
                *fOut << " << 2)";       
                *fOut << " >> 2]";
            } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
                *fOut << "Module.HEAPF32[" << indexed->getName() << " + ";  
                *fOut << "(";
                indexed->fIndex->accept(this);
                *fOut << " << 2)";       
                *fOut << " >> 2]";
            } else if (indexed->getAccess() & Address::kStruct) {
                pair<int, Typed::VarType> tmp = fFieldTable[indexed->getName()];
                if (tmp.second == Typed::kFloatMacro || tmp.second == Typed::kFloat) {
                    *fOut << "Module.HEAPF32[dsp + " << tmp.first << " + ";  
                    *fOut << "(";
                    indexed->fIndex->accept(this);
                    *fOut << " << 2)";       
                    *fOut << " >> 2]";
                } else {
                    *fOut << "Module.HEAP32[dsp + " << tmp.first << " + ";  
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
            *fOut << inst->fNum;
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
        
        // No . syntax for double in JS
        virtual void visit(DoubleNumInst* inst)
        {
            *fOut << inst->fNum;
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
                *fOut << " | 0)";
                fCurType = Typed::kBool;
            } else {
                
                inst->fInst1->accept(fGlobalVisitor);
                Typed::VarType type1 = fGlobalVisitor->fCurType;
                
                inst->fInst2->accept(fGlobalVisitor);
                Typed::VarType type2 = fGlobalVisitor->fCurType;
                
                if (type1 == Typed::kInt && type2 == Typed::kInt) {
                    if (inst->fOpcode == kMul) {
                        *fOut << "(";
                        *fOut << "Math.imul(";
                        inst->fInst1->accept(this);
                        *fOut << ", ";
                        inst->fInst2->accept(this);
                        *fOut << ") | 0";
                        *fOut << ")";
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
                } else if (type1 == Typed::kInt && type2 == Typed::kFloat) {
                    *fOut << "+(";
                    //*fOut << "(float)";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                    *fOut << ")";
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kFloat && type2 == Typed::kInt) {
                    *fOut << "+(";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    //*fOut << "(float)";
                    inst->fInst2->accept(this); 
                    *fOut << ")";
                    fCurType = Typed::kFloat;   
                } else if (type1 == Typed::kFloat && type2 == Typed::kFloat) {
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
                } else if (type1 == Typed::kFloat && type2 == Typed::kBool) {
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
                } else if (type1 == Typed::kBool && type2 == Typed::kFloat) {
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
        */
        
        
        virtual void visit(CastNumInst* inst)
        {
            // No explicit cast generation
            inst->fInst->accept(this);
        }
        
        /*
        virtual void visit(CastNumInst* inst)
        {
            if (generateType(inst->fType) == "int") {
                *fOut << "(";
                inst->fInst->accept(this);
                *fOut << " | 0)";
                fCurType = Typed::kInt;
            } else {
                *fOut << "+(";
                inst->fInst->accept(this);
                *fOut << ")";
                fCurType = Typed::kFloat;
            }
        }
        */
     
        virtual void visit(FunCallInst* inst)
        {
            string fun_name = (fMathLibTable.find(inst->fName) != fMathLibTable.end()) ? fMathLibTable[inst->fName] : inst->fName;
            generateFunCall(inst, fun_name);
        }

};

#endif
