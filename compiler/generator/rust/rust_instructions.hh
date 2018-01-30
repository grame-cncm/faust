/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

#ifndef _RUST_INSTRUCTIONS_H
#define _RUST_INSTRUCTIONS_H

#include "text_instructions.hh"

using namespace std;

// Visitor used to initialize fields into the DSP constructor
struct RustInitFieldsVisitor : public DispatchVisitor {

    std::ostream* fOut;
    int fTab;
    
    RustInitFieldsVisitor(std::ostream* out, int tab = 0):fOut(out), fTab(tab) {}
    
    virtual void visit(DeclareVarInst* inst)
    {
        tab(fTab, *fOut);
        *fOut << inst->fAddress->getName() << ": ";
        ZeroInitializer(fOut, inst->fType);
    }
    
    // Generate zero intialisation code for simple int/real scalar and arrays types
    static void ZeroInitializer(std::ostream* fOut, Typed* typed)
    {
        Typed::VarType type = typed->getType();
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(typed);
        
        if (array_type) {
            if (isIntPtrType(type)) {
                *fOut << "[0;" << array_type->fSize << "],";
            } else if (isRealPtrType(type)) {
                *fOut << "[0.0;" << array_type->fSize << "],";
            }
        } else {
            if (isIntType(type)) {
                *fOut << "0,";
            } else if (isRealType(type)) {
                *fOut << "0.0,";
            }
        }
    }
    
};

class RustInstVisitor : public TextInstVisitor {
    
    private:

        /*
         Global functions names table as a static variable in the visitor
         so that each function prototype is generated as most once in the module.
         */
        static map <string, bool> gFunctionSymbolTable;
        map <string, string> fMathLibTable;
    
        void EndLine(char end_line = ';')
        {
            if (fFinishLine) {
                *fOut << end_line;
                tab(fTab, *fOut);
            }
        }

    public:
		using TextInstVisitor::visit;

        RustInstVisitor(std::ostream* out, const string& structname, int tab = 0)
            :TextInstVisitor(out, ".", new RustStringTypeManager(FLOATMACRO, "&"), tab)
        {
            fTypeManager->fTypeDirectTable[Typed::kObj] = "";
            fTypeManager->fTypeDirectTable[Typed::kObj_ptr] = "";
            
            // Integer version
            fMathLibTable["abs"] = "i32::abs";
            fMathLibTable["min_i"] = "std::cmp::min";
            fMathLibTable["max_i"] = "std::cmp::max";
            
            // Float version
            fMathLibTable["fabsf"] = "f32::abs";
            fMathLibTable["acosf"] = "f32::acos";
            fMathLibTable["asinf"] = "f32::asin";
            fMathLibTable["atanf"] = "f32::atan";
            fMathLibTable["atan2f"] = "f32::atan2";
            fMathLibTable["ceilf"] = "f32::ceil";
            fMathLibTable["cosf"] = "f32::cos";
            fMathLibTable["expf"] = "f32::exp";
            fMathLibTable["floorf"] = "f32::floor";
            fMathLibTable["fmodf"] = "f32::fmod";
            fMathLibTable["logf"] = "f32::log";
            fMathLibTable["log10f"] = "f32::log10";
            fMathLibTable["max_f"] = "f32::max";
            fMathLibTable["min_f"] = "f32::min";
            fMathLibTable["powf"] = "f32::powf";
            fMathLibTable["remainderf"] = "manual";        // Manually generated : TODO
            fMathLibTable["roundf"] = "f32::round";
            fMathLibTable["sinf"] = "f32::sin";
            fMathLibTable["sqrtf"] = "f32::sqrt";
            fMathLibTable["tanf"] = "f32::tan";
            
            // Double version
            fMathLibTable["fabs"] = "f64::abs";
            fMathLibTable["acos"] = "f64::acos";
            fMathLibTable["asin"] = "f64::asin";
            fMathLibTable["atan"] = "f64::atan";
            fMathLibTable["atan2"] = "f64::atan2";
            fMathLibTable["ceil"] = "f64::ceil";
            fMathLibTable["cos"] = "f64::cos";
            fMathLibTable["exp"] = "f64::exp";
            fMathLibTable["floor"] = "f64::floor";
            fMathLibTable["fmod"] = "f64::fmod";
            fMathLibTable["log"] = "f64::log";
            fMathLibTable["log10"] = "f32::log10";
            fMathLibTable["max_"] = "f64::max";
            fMathLibTable["min_"] = "f64::min";
            fMathLibTable["pow"] = "f64::powf";
            fMathLibTable["remainder"] = "manual";         // Manually generated : TODO
            fMathLibTable["round"] = "f64::round";
            fMathLibTable["sin"] = "f64::sin";
            fMathLibTable["sqrt"] = "f64::sqrt";
            fMathLibTable["tan"] = "f64::tan";
        }

        virtual ~RustInstVisitor()
        {}

        virtual void visit(AddMetaDeclareInst* inst)
        {
            // Special case
            if (inst->fZone == "0") {
                *fOut << "ui_interface.declare(&mut self.fDummy, " << quote(inst->fKey) << ", " << quote(inst->fValue) << ")";
            } else {
                *fOut << "ui_interface.declare(&mut self." << inst->fZone <<", " << quote(inst->fKey) << ", " << quote(inst->fValue) << ")";
            }
            EndLine();
        }
        
        virtual void visit(OpenboxInst* inst)
        {
            string name;
            switch (inst->fOrient) {
                case 0:
                    name = "ui_interface.openVerticalBox("; break;
                case 1:
                    name = "ui_interface.openHorizontalBox("; break;
                case 2:
                    name = "ui_interface.openTabBox("; break;
            }
            *fOut << name << quote(inst->fName) << ")";
            EndLine();
        }
        
        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "ui_interface.closeBox();"; tab(fTab, *fOut);
        }
        
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                *fOut << "ui_interface.addButton(" << quote(inst->fLabel) << ", &mut self." << inst->fZone << ")";
            } else {
                *fOut << "ui_interface.addCheckButton(" << quote(inst->fLabel) << ", &mut self." << inst->fZone << ")";
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
            *fOut << name << "(" << quote(inst->fLabel) << ", "
            << "&mut self." << inst->fZone
            << ", " << checkReal(inst->fInit)
            << ", " << checkReal(inst->fMin)
            << ", " << checkReal(inst->fMax)
            << ", " << checkReal(inst->fStep) << ")";
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
            *fOut << name << "(" << quote(inst->fLabel)
            << ", &mut self." << inst->fZone
            << ", " << checkReal(inst->fMin)
            << ", " << checkReal(inst->fMax) << ")";
            EndLine();
        }

        virtual void visit(DeclareVarInst* inst)
        {
            if (inst->fAddress->getAccess() & Address::kStaticStruct) {
                *fOut << "static ";
            }
  
            if (inst->fAddress->getAccess() & Address::kStack
                || inst->fAddress->getAccess() & Address::kLoop) {
                *fOut << "let mut ";
            }
            
            *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
            
            if (inst->fValue) {
                *fOut << " = "; inst->fValue->accept(this);
            } else if (inst->fAddress->getAccess() & Address::kStaticStruct) {
                RustInitFieldsVisitor::ZeroInitializer(fOut, inst->fType);
            }
            
            EndLine((inst->fAddress->getAccess() & Address::kStruct) ? ',' : ';');
        }

        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
                return;
            } else {
                gFunctionSymbolTable[inst->fName] = true;
            }
            
            // Only generates additional functions
            if (fMathLibTable.find(inst->fName) == fMathLibTable.end()) {
                // Prototype
                *fOut << "pub fn " << inst->fName;
                generateFunDefArgs(inst);
                generateFunDefBody(inst);
            }
        }
    
        virtual void generateFunDefBody(DeclareFunInst* inst)
        {
            *fOut << ") -> " << fTypeManager->generateType(inst->fType->fResult);
            if (inst->fCode->fCode.size() == 0) {
                *fOut << ";" << endl;  // Pure prototype
            } else {
                // Function body
                *fOut << " {";
                fTab++;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                fTab--;
                tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            }
        }
    
        virtual void visit(RetInst* inst)
        {
            if (inst->fResult) {
                //*fOut << "return ";
                inst->fResult->accept(this);
            } else {
                *fOut << "return";
                EndLine();
            }
        }
    
        virtual void visit(NamedAddress* named)
        {
            if (named->getAccess() & Address::kStruct) {
                if (named->getAccess() & Address::kReference
                    && named->getAccess() & Address::kMutable) {
                    *fOut << "&mut self.";
                } else {
                    *fOut << "self.";
                }
            } else if (named->getAccess() & Address::kStaticStruct) {
                if (named->getAccess() & Address::kReference
                    && named->getAccess() & Address::kMutable) {
                    *fOut << "&mut ";
                }
            }
            *fOut << named->getName();
        }
    
        virtual void visit(IndexedAddress* indexed)
        {
            indexed->fAddress->accept(this);
            if (dynamic_cast<Int32NumInst*>(indexed->fIndex)) {
                *fOut << "["; indexed->fIndex->accept(this); *fOut << "]";
            } else {
                // Array index expression casted to 'usize' type
                *fOut << "["; indexed->fIndex->accept(this); *fOut << " as usize]";
            }
        }
    
        virtual void visit(LoadVarAddressInst* inst)
        {
            *fOut << "&"; inst->fAddress->accept(this);
        }
    
        virtual void visit(FloatArrayNumInst* inst)
        {
            char sep = '[';
            for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
                *fOut << sep << checkFloat(inst->fNumTable[i]);
                sep = ',';
            }
            *fOut << ']';
        }
        
        virtual void visit(Int32ArrayNumInst* inst)
        {
            char sep = '[';
            for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
                *fOut << sep << inst->fNumTable[i];
                sep = ',';
            }
            *fOut << ']';
        }

        virtual void visit(DoubleArrayNumInst* inst)
        {
            char sep = '[';
            for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
                *fOut << sep << checkDouble(inst->fNumTable[i]);
                sep = ',';
            }
            *fOut << ']';
        }
    
        virtual void visit(::CastInst* inst)
        {
            *fOut << "(";
            inst->fInst->accept(this);
            *fOut << " as " << fTypeManager->generateType(inst->fType);
            *fOut << ")";
        }
    
        virtual void visit(BitcastInst* inst) { faustassert(false); }

        virtual void visit(FunCallInst* inst)
        {
            string fun_name;
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                fun_name = fMathLibTable[inst->fName];
            } else {
                fun_name = inst->fName;
            }
            generateFunCall(inst, fun_name);
        }
    
        virtual void visit(Select2Inst* inst)
        {
            *fOut << "if (";
            inst->fCond->accept(this);
            // Force 'cond' to bool type
            *fOut << " as i32 == 1) { ";
            inst->fThen->accept(this);
            *fOut << " } else { ";
            inst->fElse->accept(this);
            *fOut << " }";
        }
    
        virtual void visit(IfInst* inst)
        {
            *fOut << "if (";
            inst->fCond->accept(this);
            // Force 'cond' to bool type
            *fOut << " as i32 == 1) { ";
            fTab++;
            tab(fTab, *fOut);
            inst->fThen->accept(this);
            fTab--;
            tab(fTab, *fOut);
            if (inst->fElse->fCode.size() > 0) {
                *fOut << "} else {";
                fTab++;
                tab(fTab, *fOut);
                inst->fElse->accept(this);
                fTab--;
                tab(fTab, *fOut);
                *fOut << "}";
            } else {
                *fOut << "}";
            }
            tab(fTab, *fOut);
        }
   
        virtual void visit(ForLoopInst* inst)
        {
            // Don't generate empty loops...
            if (inst->fCode->size() == 0) return;
            
            inst->fInit->accept(this);
            *fOut << "loop {";
                fTab++;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                inst->fIncrement->accept(this);
                *fOut << "if "; inst->fEnd->accept(this); *fOut << " { continue; } else { break; }";
                 fTab--;
            tab(fTab, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
        }
    
        virtual void visit(::SwitchInst* inst)
        {
            *fOut << "match ("; inst->fCond->accept(this); *fOut << ") {";
                fTab++;
                tab(fTab, *fOut);
                list<pair <int, BlockInst*> >::const_iterator it;
                for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
                    if ((*it).first == -1) { // -1 used to code "default" case
                        *fOut << "_ => {";
                    } else {
                        *fOut << (*it).first << " => {";
                    }
                        fTab++;
                        tab(fTab, *fOut);
                        ((*it).second)->accept(this);
                        /*
                        if (!((*it).second)->hasReturn()) {
                            *fOut << "break;";
                        }
                        */
                        fTab--;
                        tab(fTab, *fOut);
                    *fOut << "},";
                    tab(fTab, *fOut);
                }
                fTab--;
                tab(fTab, *fOut);
                *fOut << "} ";
            tab(fTab, *fOut);
        }
    
        static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif
