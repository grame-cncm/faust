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

class JAVAInstVisitor : public TextInstVisitor, public StringTypeManager {

    private:
 
        map <string, string> fMathLibTable;
        map<int, string> fPolyBinOpTable;
        Typed::VarType fCurType;

    public:

        JAVAInstVisitor(std::ostream* out, int tab = 0)
          :TextInstVisitor(out, tab), StringTypeManager(ifloat(), "[]"), fCurType(Typed::kNoType)
        {
            // Polymorphic arithmetic operations
            fPolyBinOpTable[kAdd] = "java_add";
            fPolyBinOpTable[kSub] = "java_sub";
            fPolyBinOpTable[kMul] = "java_mult";
            fPolyBinOpTable[kDiv] = "java_div";
            fPolyBinOpTable[kRem] = "java_rem";
            fPolyBinOpTable[kLsh] = "java_<<<";
            fPolyBinOpTable[kRsh] = "java_>>>";
            fPolyBinOpTable[kAND] = "java_and";
            fPolyBinOpTable[kOR] = "java_or";
            fPolyBinOpTable[kXOR] = "java_xor";

            fMathLibTable["abs"] = "java.lang.Math.abs";
            fMathLibTable["absf"] = "(float)java.lang.Math.abs";
            
            fMathLibTable["fabs"] = "java.lang.Math.abs";
            fMathLibTable["fabsf"] = "(float)java.lang.Math.abs";
            
            fMathLibTable["acos"] = "java.lang.Math.acos";
            fMathLibTable["acosf"] = "(float)java.lang.Math.acos";
            
            fMathLibTable["asin"] = "java.lang.Math.asin";
            fMathLibTable["asinf"] = "(cloat)java.lang.Math.asin";
            
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
            
            // Pointer to JAVA object is actually the object itself...
            fTypeDirectTable[Typed::kObj_ptr] = "";
        }

        virtual ~JAVAInstVisitor()
        {}
   
        string createVarAccess(string varname)
        {
            return "new FaustVarAccess() {\n"
                "\t\t\t\tpublic String getId() { return \"" + varname + "\"; }\n"
                "\t\t\t\tpublic void set(float val) { " + varname + " = val; }\n"
                "\t\t\t\tpublic float get() { return (float)" + varname + "; }\n"
                "\t\t\t}\n"
                "\t\t\t";
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
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ", " << checkFloat(inst->fInit) << ", " << checkFloat(inst->fMin) << ", " << checkFloat(inst->fMax) << ", " << checkFloat(inst->fStep) << ")";
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
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ", "<< checkFloat(inst->fMin) << ", " << checkFloat(inst->fMax) << ")";
            EndLine();
        }

        virtual void visit(LabelInst* inst)
        {
            // Empty
        }

        virtual void visit(DeclareVarInst* inst)
        {
            if (inst->fAddress->getAccess() & Address::kGlobal) {
                if (gGlobal->gGlobalTable.find(inst->fAddress->getName()) == gGlobal->gGlobalTable.end()) {
                    // If global is not defined
                    gGlobal->gGlobalTable[inst->fAddress->getName()] = 1;
                } else {
                    return;
                }
            }

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
            /*
                Do not declare Math library functions, they are defined in java.lang.Math and used in a polymorphic way.
            */
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                return;
            }
            
            // If function is actually a method (that is "xx::name"), then keep "xx::name" in gGlobalTable but print "name"
            string fun_name = inst->fName;
            size_t pos;
            if ((pos = inst->fName.find("::")) != string::npos) {
                fun_name = inst->fName.substr(pos + 2); // After the "::"
            }
            
            // Prototype
            *fOut << generateType(inst->fType->fResult, fun_name);
            *fOut << "(";
            list<NamedTyped*>::const_iterator it;
            int size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << generateType((*it));
                if (i < size - 1) *fOut << ", ";
            }

            if (inst->fCode->fCode.size() == 0) {
                *fOut << ");" << endl;  // Pure prototype
            } else {
                // Function body
                *fOut << ") {";
                    fTab++;
                    tab(fTab, *fOut);
                    inst->fCode->accept(this);
                    fTab--;
                    tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            }
        }

        virtual void visit(LoadVarAddressInst* inst)
        {   
            // Not implemented in JAVA
            assert(false);
        }
   
        virtual void visit(FloatNumInst* inst)
        {
            TextInstVisitor::visit(inst);
            fCurType = Typed::kFloat;
        }

        virtual void visit(IntNumInst* inst)
        {
            TextInstVisitor::visit(inst);
            fCurType = Typed::kInt;
        }

        virtual void visit(BoolNumInst* inst)
        {
            TextInstVisitor::visit(inst);
            fCurType = Typed::kBool;
        }

        virtual void visit(DoubleNumInst* inst)
        {
            TextInstVisitor::visit(inst);
            fCurType = Typed::kDouble;
        }
    
        bool isBoolOpcode(int o)
        {
            return o == kGT || o == kLT || o == kLE || o == kEQ || o == kNE;
        }

        virtual void visit(BinopInst* inst)
        {
            if (inst->fOpcode >= kGT && inst->fOpcode < kAND) {
                /*
                *fOut << "((";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
                *fOut << ")?true:false)";
                fCurType = Typed::kBool;
                */
                *fOut << "(";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
                *fOut << ")";
            } else {
                
                // Polymorphic
                *fOut << fPolyBinOpTable[inst->fOpcode] << "(";
                inst->fInst1->accept(this);
                *fOut << ", ";
                inst->fInst2->accept(this);
                *fOut << ")";
                
                /*
                // Using explicit type of the current value
                stringstream str;
                JAVAInstVisitor temp_visitor1(&str, 0);
                inst->fInst1->accept(&temp_visitor1);
                Typed::VarType type1 = temp_visitor1.fCurType;
                //assert(type1 != Typed::kNoType);
                
                JAVAInstVisitor temp_visitor2(&str, 0);
                inst->fInst2->accept(&temp_visitor2);
                Typed::VarType type2 = temp_visitor2.fCurType;
                //assert(type2 != Typed::kNoType);
                
                *fOut << "(";
                
                if (type1 == Typed::kFloat) {
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    if (type2 == Typed::kBool) {
                        *fOut << " ((";
                        inst->fInst2->accept(this);
                        *fOut << ")?1.f:0f)";
                    } else {
                        *fOut << " ";
                        inst->fInst2->accept(this);
                    }
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kInt) { 
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    if (type2 == Typed::kBool) {
                        *fOut << " ((";
                        inst->fInst2->accept(this);
                        *fOut << ")?1:0)";
                    } else {
                        *fOut << " ";
                        inst->fInst2->accept(this);
                    }
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kDouble) { 
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    if (type2 == Typed::kBool) {
                        *fOut << " ((";
                        inst->fInst2->accept(this);
                        *fOut << ")?1:0)";
                    } else {
                        *fOut << " ";
                        inst->fInst2->accept(this);
                    }
                    fCurType = Typed::kDouble;
                } else if (type1 == Typed::kBool) { 
                    if (type2 == Typed::kBool) {
                        inst->fInst1->accept(this);
                        fCurType = Typed::kBool;
                    } else if (type2 == Typed::kFloat) { 
                        *fOut << "((";
                        inst->fInst1->accept(this);
                        *fOut << ")?1.f:0.f)";
                        fCurType = Typed::kFloat;
                    } else if (type2 == Typed::kInt) { 
                        *fOut << "((";
                        inst->fInst1->accept(this);
                        *fOut << ")?1:0)";
                        fCurType = Typed::kInt;
                    } else if (type2 == Typed::kDouble) { 
                        *fOut << "((";
                        inst->fInst1->accept(this);
                        *fOut << ")?1:0)";
                        fCurType = Typed::kDouble;
                    }
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                } else {   // Typed::kNoType
                    inst->fInst1->accept(this);
                    *fOut << " ";
                    *fOut << gBinOpTable[inst->fOpcode]->fName;
                    *fOut << " ";
                    inst->fInst2->accept(this);
                }
                                                
                *fOut << ")";
                */
            }
        }

        virtual void visit(CastNumInst* inst)
        {
            // Generate a call to a polymorphic cast
            string cast_type = generateType(inst->fType);
            if (cast_type == "int") {
                *fOut << "cast_int("; inst->fInst->accept(this); *fOut << ")";
                fCurType = Typed::kInt;
            } else {
                *fOut << "cast_float("; inst->fInst->accept(this); *fOut << ")";
                fCurType = Typed::kFloat;
            }
        }
    
        virtual void visit(FunCallInst* inst)
        {
            string java_name = (fMathLibTable.find(inst->fName) != fMathLibTable.end()) ? fMathLibTable[inst->fName] : inst->fName;
              
            if (inst->fMethod) {
                list<ValueInst*>::const_iterator it = inst->fArgs.begin();
                // Compile object arg
                (*it)->accept(this);
                // Compile parameters
                *fOut << "." << java_name << "(";
                compileArgs(++it, inst->fArgs.end(), inst->fArgs.size() - 1);
            } else {
                *fOut << java_name << "(";
                // Compile parameters
                compileArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
            }
            *fOut << ")";
        }
  
        virtual void visit(Select2Inst* inst)
        {
            *fOut << "(cast_boolean(";
            inst->fCond->accept(this);
            *fOut << ")?";
            inst->fThen->accept(this);
            *fOut << ":";
            inst->fElse->accept(this);
            *fOut << ")";
        }
        
};

#endif
