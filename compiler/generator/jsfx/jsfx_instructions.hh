/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2022 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _JSFX_INSTRUCTIONS_H
#define _JSFX_INSTRUCTIONS_H

#include <string>

#include "text_instructions.hh"
#include "struct_manager.hh"

using namespace std;

// Visitor used to initialize array fields into the DSP structure
struct JSFXInitFieldsVisitor : public DispatchVisitor {
    std::ostream* fOut;
    int           fTab;
    // The name of the currently generated array
    string        fCurArray;
    
    JSFXInitFieldsVisitor(std::ostream* out, int tab = 0) : fOut(out), fTab(tab) {}
    
    virtual void visit(DeclareVarInst* inst)
    {
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(inst->fType);
        if (array_type) {
            //tab(fTab, *fOut);
            if (inst->fValue) {
                fCurArray = inst->fAddress->getName();
                inst->fValue->accept(this);
            } else {
                inst->fAddress->accept(this);
                *fOut << " = ";
                ZeroInitializer(fOut, inst->fType);
                *fOut << ";\n";
            }
        }
    }
    
    virtual void visit(NamedAddress* named)
    {
        // kStaticStruct are actually merged in the main DSP
         if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
         }
         *fOut << named->fName;
    }
    
    static void ZeroInitializer(std::ostream* fOut, Typed* typed)
    {
        // TO CHECK
         ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(typed);
         faustassert(array_type);
         if (isIntPtrType(typed->getType())) {
            *fOut << "zeros(" << array_type->fSize << ")";
         } else {
            *fOut << "zeros(" << array_type->fSize << ")";
         }
    }
    
    // Needed for waveforms
    virtual void visit(Int32ArrayNumInst* inst)
    {
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << fCurArray << "[" << i << "] = floor(" << inst->fNumTable[i] << ");\n";
        }
        *fOut << "\n";
    }
    
    virtual void visit(FloatArrayNumInst* inst)
    {
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << fCurArray << "[" << i << "] = " << inst->fNumTable[i] << ";\n";
        }
        *fOut << "\n";
    }
    
    virtual void visit(DoubleArrayNumInst* inst)
    {
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << fCurArray << "[" << i << "] = " << inst->fNumTable[i] << ";\n";
        }
        *fOut << "\n";
    }
};

/*
    A subclass of TextInstVisitor that implements a lot of generic behaviors.
    Some methods mays have to be redefined in this class, anf the exposed list
    of them is given as an example, to be adapted in the real case.
*/

class JSFXInstVisitor : public TextInstVisitor {
   private:
    
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static map<string, bool> gFunctionSymbolTable;
    // Polymorphic math functions
    map<string, string> gPolyMathLibTable; 

    // Global count for sliders
    size_t slider_count = 0;

   public:
    using TextInstVisitor::visit;

    JSFXInstVisitor(std::ostream* out, const string& struct_name, int tab = 0)
        : TextInstVisitor(out, ".", new JSFXStringTypeManager(xfloat(), "*", struct_name), tab)
    {
            // Mark all math.h functions as generated...
        gFunctionSymbolTable["abs"] = true;
    
        gFunctionSymbolTable["max_i"] = true;
        gFunctionSymbolTable["min_i"] = true;
        
        gFunctionSymbolTable["max_f"] = true;
        gFunctionSymbolTable["min_f"] = true;

        gFunctionSymbolTable["max_"] = true;
        gFunctionSymbolTable["min_"] = true;

        gFunctionSymbolTable["max_l"] = true;
        gFunctionSymbolTable["min_l"] = true;

        // Float version
        gFunctionSymbolTable["fabsf"]      = true;
        gFunctionSymbolTable["acosf"]      = true;
        gFunctionSymbolTable["asinf"]      = true;
        gFunctionSymbolTable["atanf"]      = true;
        gFunctionSymbolTable["atan2f"]     = true;
        gFunctionSymbolTable["ceilf"]      = true;
        gFunctionSymbolTable["cosf"]       = true;
        gFunctionSymbolTable["expf"]       = true;
        gFunctionSymbolTable["exp10f"]     = true;
        gFunctionSymbolTable["floorf"]     = true;
        gFunctionSymbolTable["fmodf"]      = true;
        gFunctionSymbolTable["logf"]       = true;
        gFunctionSymbolTable["log10f"]     = true;
        gFunctionSymbolTable["powf"]       = true;
        gFunctionSymbolTable["remainderf"] = true;
        gFunctionSymbolTable["rintf"]      = true;
        gFunctionSymbolTable["roundf"]     = true;
        gFunctionSymbolTable["sinf"]       = true;
        gFunctionSymbolTable["sqrtf"]      = true;
        gFunctionSymbolTable["tanf"]       = true;
    
        // Hyperbolic
        gFunctionSymbolTable["acoshf"] = false;
        gFunctionSymbolTable["asinhf"] = false;
        gFunctionSymbolTable["atanhf"] = false;
        gFunctionSymbolTable["coshf"]  = false;
        gFunctionSymbolTable["sinhf"]  = false;
        gFunctionSymbolTable["tanhf"]  = false;

        // Double version
        gFunctionSymbolTable["fabs"]      = true;
        gFunctionSymbolTable["acos"]      = true;
        gFunctionSymbolTable["asin"]      = true;
        gFunctionSymbolTable["atan"]      = true;
        gFunctionSymbolTable["atan2"]     = true;
        gFunctionSymbolTable["ceil"]      = true;
        gFunctionSymbolTable["cos"]       = true;
        gFunctionSymbolTable["exp"]       = true;
        gFunctionSymbolTable["exp10"]     = true;
        gFunctionSymbolTable["floor"]     = true;
        gFunctionSymbolTable["fmod"]      = true;
        gFunctionSymbolTable["log"]       = true;
        gFunctionSymbolTable["log10"]     = true;
        gFunctionSymbolTable["pow"]       = true;
        gFunctionSymbolTable["remainder"] = true;
        gFunctionSymbolTable["rint"]      = true;
        gFunctionSymbolTable["round"]     = true;
        gFunctionSymbolTable["sin"]       = true;
        gFunctionSymbolTable["sqrt"]      = true;
        gFunctionSymbolTable["tan"]       = true;
    
        // Hyperbolic
        gFunctionSymbolTable["acosh"] = false;
        gFunctionSymbolTable["asinh"] = false;
        gFunctionSymbolTable["atanh"] = false;
        gFunctionSymbolTable["coshf"]  = false;
        gFunctionSymbolTable["sinh"]  = false;
        gFunctionSymbolTable["tanh"]  = false;

        // Quad version
        gFunctionSymbolTable["fabsl"]      = false;
        gFunctionSymbolTable["acosl"]      = false;
        gFunctionSymbolTable["asinl"]      = false;
        gFunctionSymbolTable["atanl"]      = false;
        gFunctionSymbolTable["atan2l"]     = false;
        gFunctionSymbolTable["ceill"]      = false;
        gFunctionSymbolTable["cosl"]       = false;
        gFunctionSymbolTable["expl"]       = false;
        gFunctionSymbolTable["exp10l"]     = false;
        gFunctionSymbolTable["floorl"]     = false;
        gFunctionSymbolTable["fmodl"]      = false;
        gFunctionSymbolTable["logl"]       = false;
        gFunctionSymbolTable["log10l"]     = false;
        gFunctionSymbolTable["powl"]       = false;
        gFunctionSymbolTable["remainderl"] = false;
        gFunctionSymbolTable["rintl"]      = false;
        gFunctionSymbolTable["roundl"]     = false;
        gFunctionSymbolTable["sinl"]       = false;
        gFunctionSymbolTable["sqrtl"]      = false;
        gFunctionSymbolTable["tanl"]       = false;
    
        // Hyperbolic
        gFunctionSymbolTable["acoshl"] = false;
        gFunctionSymbolTable["asinhl"] = false;
        gFunctionSymbolTable["atanhl"] = false;
        gFunctionSymbolTable["coshl"]  = false;
        gFunctionSymbolTable["sinhl"]  = false;
        gFunctionSymbolTable["tanhl"]  = false;
   
        // Polymath mapping int version
        gPolyMathLibTable["abs"]   = "abs";
        gPolyMathLibTable["max_i"] = "max";
        gPolyMathLibTable["min_i"] = "min";

        // Polymath mapping float version
        gPolyMathLibTable["max_f"] = "max";
        gPolyMathLibTable["min_f"] = "min";

        gPolyMathLibTable["fabsf"]      = "abs";
        gPolyMathLibTable["acosf"]      = "acos";
        gPolyMathLibTable["asinf"]      = "asin";
        gPolyMathLibTable["atanf"]      = "atan";
        gPolyMathLibTable["atan2f"]     = "atan";
        gPolyMathLibTable["ceilf"]      = "ceil";
        gPolyMathLibTable["cosf"]       = "cos";
        gPolyMathLibTable["expf"]       = "exp";
        gPolyMathLibTable["exp2f"]      = "exp2";
        gPolyMathLibTable["exp10f"]     = "exp10";
        gPolyMathLibTable["floorf"]     = "floor";
        gPolyMathLibTable["fmodf"]      = "mod";
        gPolyMathLibTable["logf"]       = "log";
        gPolyMathLibTable["log2f"]      = "log2";
        gPolyMathLibTable["log10f"]     = "log10";
        gPolyMathLibTable["powf"]       = "pow";
        gPolyMathLibTable["remainderf"] = "remainder";
        gPolyMathLibTable["rintf"]      = "rint";
        gPolyMathLibTable["roundf"]     = "round";
        gPolyMathLibTable["sinf"]       = "sin";
        gPolyMathLibTable["sqrtf"]      = "sqrt";
        gPolyMathLibTable["tanf"]       = "tan";
                             
        // Hyperbolic - Not available in JSFX yet 
        /*
        gPolyMathLibTable["acoshf"]     = "acosh";
        gPolyMathLibTable["asinhf"]     = "asinh";
        gPolyMathLibTable["atanhf"]     = "atanh";
        gPolyMathLibTable["coshf"]      = "cosh";
        gPolyMathLibTable["sinhf"]      = "sinh";
        gPolyMathLibTable["tanhf"]      = "tanh";
    
        gPolyMathLibTable["isnanf"]     = "isnan";
        gPolyMathLibTable["isinff"]     = "isinf";
        gPolyMathLibTable["copysignf"]  = "copysign";
        */
        
        // Polymath mapping double version
        gPolyMathLibTable["max_"] = "max";
        gPolyMathLibTable["min_"] = "min";

        gPolyMathLibTable["fabs"]      = "abs";
        gPolyMathLibTable["acos"]      = "acos";
        gPolyMathLibTable["asin"]      = "asin";
        gPolyMathLibTable["atan"]      = "atan";
        gPolyMathLibTable["atan2"]     = "atan";
        gPolyMathLibTable["ceil"]      = "ceil";
        gPolyMathLibTable["cos"]       = "cos";
        gPolyMathLibTable["exp"]       = "exp";
        gPolyMathLibTable["exp2"]      = "exp2";
        gPolyMathLibTable["exp10"]     = "exp10";
        gPolyMathLibTable["floor"]     = "floor";
        gPolyMathLibTable["fmod"]      = "mod";
        gPolyMathLibTable["log"]       = "log";
        gPolyMathLibTable["log2"]      = "log2";
        gPolyMathLibTable["log10"]     = "log10";
        gPolyMathLibTable["pow"]       = "pow";
        gPolyMathLibTable["remainder"] = "remainder";
        gPolyMathLibTable["rint"]      = "rint";
        gPolyMathLibTable["round"]     = "round";
        gPolyMathLibTable["sin"]       = "sin";
        gPolyMathLibTable["sqrt"]      = "sqrt";
        gPolyMathLibTable["tan"]       = "tan";
    
        // Hyperbolic
        /*
        gPolyMathLibTable["acosh"]     = "acosh";
        gPolyMathLibTable["asinh"]     = "asinh";
        gPolyMathLibTable["atanh"]     = "atanh";
        gPolyMathLibTable["cosh"]      = "cosh";
        gPolyMathLibTable["sinh"]      = "sinh";
        gPolyMathLibTable["tanh"]      = "tanh";

        gPolyMathLibTable["isnan"]     = "isnan";
        gPolyMathLibTable["isinf"]     = "isinf";
        gPolyMathLibTable["copysign"]  = "copysign";
        */
    }

    virtual ~JSFXInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {}

    virtual void visit(OpenboxInst* inst)
    {
    }

    virtual void visit(CloseboxInst* inst)
    {
    }
    
    virtual void visit(AddButtonInst* inst)
    {
        throw(faustexception("ERROR : Button is not available in JSFX.\n"));
        /*
        string name;
        if (inst->fType == AddButtonInst::kDefaultButton) {
            name = "addButton!(";
        } else {
            name = "addCheckButton!(";
        }
        *fOut << name << "ui_interface, " << quote(inst->fLabel) << ", :" << inst->fZone << ")";
        EndLine(' ');
        */
    }

    virtual void visit(AddSliderInst* inst)
    {
        *fOut << "slider" << ++slider_count << ":" << inst->fZone << "=" << inst->fInit
              << "<" << inst->fMin << "," << inst->fMax << "," << inst->fStep << ">" << inst->fLabel;
              
        EndLine(' ');

    }

    virtual void visit(AddBargraphInst* inst)
    {
        throw(faustexception("ERROR : Bargraph is not available in JSFX.\n"));
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        throw(faustexception("ERROR : Soundfile is not available in JSFX.\n"));
    }
    
    virtual void visit(Int32NumInst* inst) {
        *fOut << "floor(" << inst->fNum << ")";
    }
    
    virtual void visit(Int64NumInst* inst) {
        *fOut << "floor(" << inst->fNum << ")";
    }

    virtual void visit(FloatNumInst* inst) {
        *fOut << fixed << inst->fNum;
    }

    virtual void visit(DoubleNumInst* inst) {
        *fOut << fixed << inst->fNum;
    }
    
    virtual void visit(Int32ArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << "floor(" << inst->fNumTable[i] << ")";
            sep = ',';
        }
        *fOut << ']';
    }
    
    virtual void visit(FloatArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << ']';
    }
    
    virtual void visit(DoubleArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << ']';

    }
    
    virtual void visit(BinopInst* inst)
    {
         if (inst->fOpcode == kXOR) {
            *fOut << "(";
            inst->fInst1->accept(this);
            *fOut << " ~ ";
             inst->fInst2->accept(this);
            *fOut << ")";
        } else {
            // Operator precedence is not like C/C++, so for simplicity, we keep the fully parenthesized version
            *fOut << "(";
            inst->fInst1->accept(this);
            *fOut << " ";
            *fOut << gBinOpTable[inst->fOpcode]->fName;
            *fOut << " ";
            inst->fInst2->accept(this);
            *fOut << ")";
        }   
    }
   
    virtual void visit(DeclareVarInst* inst)
    {
        //*fOut << inst->getName();
        std::string n = inst->fAddress->getName();
        if(n.find("output") != n.npos || n.find("input") != n.npos) 
            return;
        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
             *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
        } else {
            *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
            if (inst->fValue) {
                *fOut << " = ";
                inst->fValue->accept(this);
            }
        }
        EndLine();   
    }
    
    virtual void visit(DropInst* inst)
    {
            if (inst->fResult) {
            inst->fResult->accept(this);
            EndLine(' ');
        }
    }
    
    virtual void visit(DeclareFunInst* inst)
    {
        // Already generated
        if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
           return;
        } else {
           gFunctionSymbolTable[inst->fName] = true;
        }
        
        *fOut << "function " << inst->fName;
        generateFunDefArgs(inst);
        *fOut << " ";
        generateFunDefBody(inst);
    }

    virtual void generateFunDefArgs(DeclareFunInst* inst)
    {
        if(inst->fType->fArgsTypes.size() == 0) 
        {
            *fOut << "()";
            return;
        }
        *fOut << "(";
        size_t size = inst->fType->fArgsTypes.size(), i = 0;
        for (const auto& it : inst->fType->fArgsTypes) {
            *fOut << fTypeManager->generateType(it);
            if (i++ < size - 1) *fOut << ", ";
        }
        *fOut << ")";
    }
        
    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        if (inst->fCode->fCode.size() == 0) {
            *fOut << "()" << endl;  // Pure prototype
        } else {
            // Function body
            *fOut << "(" << endl; 
            fTab++;
            tab(fTab, *fOut);
            inst->fCode->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << ")";
            EndLine();
            tab(fTab, *fOut);
        }

    }

    virtual void visit(NamedAddress* named)
    {
        // kStaticStruct are actually merged in the main DSP
        if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
        }
        std::string name = named->fName;
        if(name.find("output") != name.npos) {
            name.replace(0, 6, "spl");
        } else if(name.find("input") != name.npos) {
            name.replace(0, 5, "spl");
        } else if(name.find("sample_rate") != name.npos) {
            name.replace(0, name.size(), "srate");
        }
        *fOut << name;
    }
    
    /*
    Indexed address can actually be values in an array or fields in a struct type
    */
    virtual void visit(IndexedAddress* indexed)
    {
        indexed->fAddress->accept(this);
        DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
        if (struct_type) {
            Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->getIndex());
            *fOut << "." << struct_type->fType->getName(field_index->fNum);
        } else {
            std::string name = indexed->fAddress->getName();
            if( (name.find("output") != name.npos) || (name.find("input") != name.npos) ) {
                return;
            }
            *fOut << "[";
            Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(indexed->getIndex());
            if (field_index) {
                *fOut << (field_index->fNum) << "]";
            } else {
                indexed->getIndex()->accept(this);
                *fOut << "]";
            }
        }
    }
      
    virtual void visit(::CastInst* inst)
    {
        if (isIntType(inst->fType->getType())) {
            *fOut << "floor(";
        } else {
            *fOut << "(";
        }
        inst->fInst->accept(this);
        *fOut << ")"; 
    }

    virtual void visit(BitcastInst* inst)
    {

    }
    
    virtual void visitCond(ValueInst* cond)
    {
        *fOut << "(";
        cond->accept(this);
        *fOut << " != 0)";
    }
    
    // Generate standard funcall (not 'method' like funcall...)
    virtual void visit(FunCallInst* inst)
    {
        string name = (gPolyMathLibTable.find(inst->fName) != gPolyMathLibTable.end()) ? gPolyMathLibTable[inst->fName] : inst->fName;
        // Function that mutate their arguments use the '!' syntax
        *fOut << name << "(";
        // Compile parameters
        generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
        *fOut << ")";
    }
    
    virtual void visit(IfInst* inst)
    {
        *fOut << "(";
        visitCond(inst->fCond);
        *fOut << ") ? (";
        inst->fThen->accept(this);
        *fOut << ")";
        if(inst->fElse->fCode.size() > 0) {
            *fOut << " : (";
            inst->fElse->accept(this);
            *fOut << ")";
        } 
    }
  
    virtual void visit(ForLoopInst* inst)
    {
        if (inst->fCode->size() == 0) return;

        inst->fInit->accept(this);
        *fOut << "while";
        inst->fEnd->accept(this);
        *fOut << "\n(";
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        inst->fIncrement->accept(this);
        fTab--;
        back(1, *fOut);
        *fOut << ")";
        EndLine();
        tab(fTab, *fOut);
    }


    // DSP Loop
    virtual void visit(SimpleForLoopInst* inst)
    {
        inst->fCode->accept(this);
        /*
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;
        Int32NumInst* lower_bound = dynamic_cast<Int32NumInst*>(inst->fLowerBound);
        faustassert(lower_bound);
        Int32NumInst* upper_bound = dynamic_cast<Int32NumInst*>(inst->fUpperBound);
        *fOut << "loop(";
        if(upper_bound) {
            *fOut << upper_bound->fNum;
        } else {
            inst->fUpperBound->accept(this);
        }
        *fOut << ",";
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
        tab(fTab, *fOut);
        *fOut << ")";
        EndLine();
        */
    }

    static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif

