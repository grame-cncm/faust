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

#ifndef _JAVA_INSTRUCTIONS_H
#define _JAVA_INSTRUCTIONS_H

using namespace std;

#include "text_instructions.hh"
#include "typing_instructions.hh"

class JAVAInstVisitor : public TextInstVisitor {

    private:
    
        /*
         Global functions names table as a static variable in the visitor
         so that each function prototye is generated as most once in the module.
         */
        static map <string, int> gFunctionSymbolTable;      
        static map <string, string> fMathLibTable;
        TypingVisitor fTypingVisitor;
   
    public:
    
     
        JAVAInstVisitor(std::ostream* out, int tab = 0)
          :TextInstVisitor(out, ".", ifloat(), "[]", tab)
        {
            initMathTable();
                    
            // Pointer to JAVA object is actually the object itself...
            fTypeDirectTable[Typed::kObj_ptr] = "";
        }
        
        void initMathTable()
        {
            if (fMathLibTable.size()) {
                return;
            }

            fMathLibTable["abs"] = "java.lang.Math.abs";
            fMathLibTable["absf"] = "(float)java.lang.Math.abs";
            
            fMathLibTable["fabs"] = "java.lang.Math.abs";
            fMathLibTable["fabsf"] = "(float)java.lang.Math.abs";
            
            fMathLibTable["acos"] = "java.lang.Math.acos";
            fMathLibTable["acosf"] = "(float)java.lang.Math.acos";
            
            fMathLibTable["asin"] = "java.lang.Math.asin";
            fMathLibTable["asinf"] = "(float)java.lang.Math.asin";
            
            fMathLibTable["atan"] = "java.lang.Math.atan";
            fMathLibTable["atanf"] = "(float)java.lang.Math.atan";
            
            fMathLibTable["atan2"] = "java.lang.Math.atan2";
            fMathLibTable["atan2f"] = "(float)java.lang.Math.atan2";
            
            fMathLibTable["ceil"] = "java.lang.Math.ceil";
            fMathLibTable["ceilf"] = "(float)java.lang.Math.ceil";
            
            fMathLibTable["cos"] = "java.lang.Math.cos";
            fMathLibTable["cosf"] = "(float)java.lang.Math.cos";
            
            fMathLibTable["cosh"] = "java.lang.Math.cosh";
            fMathLibTable["coshf"] = "(float)java.lang.Math.cosh";
            
            fMathLibTable["exp"] = "java.lang.Math.exp";
            fMathLibTable["expf"] = "(float)java.lang.Math.exp";
            
            fMathLibTable["floor"] = "java.lang.Math.floor";
            fMathLibTable["floorf"] = "(float)java.lang.Math.floor";
            
            fMathLibTable["fmod"] = "java.lang.Math.IEEEremainder";
            fMathLibTable["fmodf"] = "(float)java.lang.Math.IEEEremainder";
            
            fMathLibTable["log"] = "java.lang.Math.log";
            fMathLibTable["logf"] = "(float)java.lang.Math.log";
            
            fMathLibTable["log10"] = "java.lang.Math.log10";
            fMathLibTable["log10f"] = "(float)java.lang.Math.log10";
            
            fMathLibTable["max"] = "java.lang.Math.max";
            fMathLibTable["min"] = "java.lang.Math.min";
            
            fMathLibTable["pow"] = "java.lang.Math.pow";
            fMathLibTable["powf"] = "(float)java.lang.Math.pow";
            
            fMathLibTable["round"] = "java.lang.Math.round";
            fMathLibTable["roundf"] = "(float)java.lang.Math.round";
             
            fMathLibTable["sin"] = "java.lang.Math.sin";
            fMathLibTable["sinf"] = "(float)java.lang.Math.sin";
            
            fMathLibTable["sinh"] = "java.lang.Math.sinh";
            fMathLibTable["sinhf"] = "(float)java.lang.Math.sinh";
             
            fMathLibTable["sqrt"] = "java.lang.Math.sqrt";
            fMathLibTable["sqrtf"] = "(float)java.lang.Math.sqrt";
            
            fMathLibTable["tan"] = "java.lang.Math.tan";
            fMathLibTable["tanf"] = "(float)java.lang.Math.tan";
            
            fMathLibTable["tanh"] = "java.lang.Math.tanh";
            fMathLibTable["tanhf"] = "(float)java.lang.Math.tanh";
        }

        virtual ~JAVAInstVisitor()
        {}
   
        string createVarAccess(string varname)
        {
            if (strcmp(ifloat(), "float") == 0) {
                return "new FaustVarAccess() {\n"
                    "\t\t\t\tpublic String getId() { return \"" + varname + "\"; }\n"
                    "\t\t\t\tpublic void set(float val) { " + varname + " = val; }\n"
                    "\t\t\t\tpublic float get() { return (float)" + varname + "; }\n"
                    "\t\t\t}\n"
                    "\t\t\t";
            } else {
                 return "new FaustVarAccess() {\n"
                    "\t\t\t\tpublic String getId() { return \"" + varname + "\"; }\n"
                    "\t\t\t\tpublic void set(double val) { " + varname + " = val; }\n"
                    "\t\t\t\tpublic float get() { return (double)" + varname + "; }\n"
                    "\t\t\t}\n"
                    "\t\t\t";
            }
        }

        virtual void visit(AddMetaDeclareInst* inst)
        {
            *fOut << "ui_interface.declare(\"" << inst->fZone << "\", \"" << inst->fKey << "\", \"" <<  inst->fValue << "\")";
            EndLine();
        }

        virtual void visit(OpenboxInst* inst)
        {
            string name;
            switch (inst->fOrient) {
                case 0:
                    name = "ui_interface.openVerticalBox"; break;
                case 1:
                    name = "ui_interface.openHorizontalBox"; break;
                case 2:
                    name = "ui_interface.openTabBox"; break;
            }
            *fOut << name << "(" << "\"" << inst->fName << "\"" << ")";
            EndLine();
        }

        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "ui_interface.closeBox();"; tab(fTab, *fOut);
        }
        
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                *fOut << "ui_interface.addButton(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ")";
            } else {
                *fOut << "ui_interface.addCheckButton(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ")"; 
            }
            EndLine();
        }

        virtual void visit(AddSliderInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    name = "ui_interface.addHorizontalSlider"; break;
                case AddSliderInst::kVertical:
                    name = "ui_interface.addVerticalSlider"; break;
                case AddSliderInst::kNumEntry:
                    name = "ui_interface.addNumEntry"; break;
            }
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ", " << checkReal(inst->fInit) << ", " << checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ", " << checkReal(inst->fStep) << ")";
            EndLine();
        }

        virtual void visit(AddBargraphInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    name = "ui_interface.addHorizontalBargraph"; break;
                case AddBargraphInst::kVertical:
                    name = "ui_interface.addVerticalBargraph"; break;
            }
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ", "<< checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ")";
            EndLine();
        }

        virtual void visit(LabelInst* inst)
        {
            // Empty
        }

        virtual void visit(DeclareVarInst* inst)
        {
            if (inst->fAddress->getAccess() & Address::kStaticStruct) {
                 *fOut << "static ";
            }
            
            if (inst->fValue) {
                *fOut << generateType(inst->fType, inst->fAddress->getName()) << " = "; inst->fValue->accept(this);
            } else {
                ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
                if (array_typed && array_typed->fSize > 1) {
                    string type = fTypeDirectTable[array_typed->fType->getType()];
                    *fOut << type << " " << inst->fAddress->getName() << "[] = new " << type << "[" << array_typed->fSize << "]";
                } else {
                    *fOut << generateType(inst->fType, inst->fAddress->getName());
                }
            }
            EndLine();
        }

        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
                return;
            } else {
                gFunctionSymbolTable[inst->fName] = 1;
            }
            
            // Do not declare Math library functions, they are defined in java.lang.Math and used in a polymorphic way.
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                return;
            }
            
            // Prototype
            *fOut << generateType(inst->fType->fResult, generateFunName(inst->fName));
            generateFunDefArgs(inst);
            generateFunDefBody(inst);
        }
        
        virtual void visit(LoadVarInst* inst)
        {
            fTypingVisitor.visit(inst);
            TextInstVisitor::visit(inst);
        }

        virtual void visit(LoadVarAddressInst* inst)
        {   
            // Not implemented in JAVA
            assert(false);
        }
   
        virtual void visit(FloatNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            TextInstVisitor::visit(inst);
        }

        virtual void visit(IntNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            TextInstVisitor::visit(inst);
        }

        virtual void visit(BoolNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            TextInstVisitor::visit(inst);
        }

        virtual void visit(DoubleNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            TextInstVisitor::visit(inst);
        }
    
        bool isBoolOpcode(int o)
        {
            return o == kGT || o == kLT || o == kLE || o == kEQ || o == kNE;
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
                *fOut << ")";
            } else {
                
                inst->fInst1->accept(&fTypingVisitor);
                Typed::VarType type1 = fTypingVisitor.fCurType;
                
                inst->fInst2->accept(&fTypingVisitor);
                Typed::VarType type2 = fTypingVisitor.fCurType;
                
                *fOut << "(";
                
                if (type1 == Typed::kInt && type2 == Typed::kInt) {
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                } else if (type1 == Typed::kInt && type2 == Typed::kFloat) {
                    *fOut << "(float)";
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                } else if (type1 == Typed::kFloat && type2 == Typed::kInt) {
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    *fOut << "(float)";
                    inst->fInst2->accept(this); 
                } else if (type1 == Typed::kFloat && type2 == Typed::kFloat) {
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                } else if (type1 == Typed::kInt && type2 == Typed::kBool) {
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    *fOut << "((";
                    inst->fInst2->accept(this);
                    *fOut << ")?1:0)";
                } else if (type1 == Typed::kBool && type2 == Typed::kInt) {
                    *fOut << "((";
                    inst->fInst1->accept(this);
                    *fOut << ")?1:0)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                    *fOut << "((";
                    inst->fInst1->accept(this);
                    *fOut << ")?1:0)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    *fOut << "((";
                    inst->fInst2->accept(this);
                    *fOut << ")?1:0)";
                } else if (type1 == Typed::kFloat && type2 == Typed::kBool) {
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    *fOut << "((";
                    inst->fInst2->accept(this);
                    *fOut << ")?1.f:0.f)";
                } else if (type1 == Typed::kBool && type2 == Typed::kFloat) {
                    *fOut << "((";
                    inst->fInst1->accept(this);
                    *fOut << ")?1.f:0.f)";
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                } else { // Default
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                }   
                
                *fOut << ")";
            }
            
            fTypingVisitor.visit(inst);
        }

        virtual void visit(CastNumInst* inst)
        {
            inst->fInst->accept(&fTypingVisitor);
                
            if (generateType(inst->fType) == "int") {
                switch (fTypingVisitor.fCurType) {
                    case Typed::kDouble:
                    case Typed::kFloat:
                    case Typed::kFloatMacro:
                        *fOut << "(int)"; inst->fInst->accept(this);
                        break;
                    case Typed::kInt:
                        inst->fInst->accept(this);
                        break;
                    case Typed::kBool:
                        *fOut << "(("; inst->fInst->accept(this); *fOut << ")?1:0)";
                        break;
                    default:
                        printf("visitor.fCurType %d\n", fTypingVisitor.fCurType);
                        assert(false);
                        break;
                }
            } else {
                switch (fTypingVisitor.fCurType) {
                    case Typed::kDouble:
                    case Typed::kInt:
                        *fOut << "(float)"; inst->fInst->accept(this);
                        break;
                     case Typed::kFloat:
                     case Typed::kFloatMacro:
                        inst->fInst->accept(this);
                        break;
                    case Typed::kBool:
                        *fOut << "(("; inst->fInst->accept(this); *fOut << ")?1.f:0.f)";
                        break;
                    default:
                        printf("visitor.fCurType %d\n", fTypingVisitor.fCurType);
                        assert(false);
                        break;
                }
            }
            fTypingVisitor.visit(inst);
        }
    
        virtual void visit(FunCallInst* inst)
        {
            string fun_name = (fMathLibTable.find(inst->fName) != fMathLibTable.end()) ? fMathLibTable[inst->fName] : inst->fName;
            generateFunCall(inst, fun_name);
        }
      
        virtual void visit(Select2Inst* inst)
        {
            inst->fCond->accept(&fTypingVisitor);
            
            switch (fTypingVisitor.fCurType) {
                case Typed::kDouble:
                case Typed::kInt:
                    *fOut << "((("; inst->fCond->accept(this); *fOut << "==0)?true:false)";
                    break;
                case Typed::kFloat:
                case Typed::kFloatMacro:
                    *fOut << "((("; inst->fCond->accept(this); *fOut << "==0.f)?true:false)";
                    break;
                case Typed::kBool:
                    *fOut << "(("; inst->fCond->accept(this); *fOut << ")";
                    break;
                default:
                    assert(false);
                    break;
            }
     
            *fOut << "?";
            inst->fThen->accept(this);
            *fOut << ":";
            inst->fElse->accept(this);
            *fOut << ")";
            
            fTypingVisitor.visit(inst);
        }
        
};

#endif
