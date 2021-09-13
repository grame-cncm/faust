/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#ifndef _JULIA_INSTRUCTIONS_H
#define _JULIA_INSTRUCTIONS_H

#include <string>

#include "text_instructions.hh"
#include "struct_manager.hh"

using namespace std;

// Visitor used to initialize array fields into the DSP structure
struct JuliaInitFieldsVisitor : public DispatchVisitor {
    std::ostream* fOut;
    int           fTab;
    
    JuliaInitFieldsVisitor(std::ostream* out, int tab = 0) : fOut(out), fTab(tab) {}
    
    virtual void visit(DeclareVarInst* inst)
    {
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(inst->fType);
        if (array_type) {
            tab(fTab, *fOut);
            inst->fAddress->accept(this);
            *fOut << " = ";
            if (inst->fValue) {
                inst->fValue->accept(this);
            } else {
                ZeroInitializer(fOut, inst->fType);
            }
        }
    }
    
    virtual void visit(NamedAddress* named)
    {
        // kStaticStruct are actually merged in the main DSP
        if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
            *fOut << "dsp.";
        }
        *fOut << named->fName;
    }
    
    static void ZeroInitializer(std::ostream* fOut, Typed* typed)
    {
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(typed);
        faustassert(array_type);
        if (isIntPtrType(typed->getType())) {
            *fOut << "zeros(Int32, " << array_type->fSize << ")";
        } else {
            *fOut << "zeros(T, " << array_type->fSize << ")";
        }
    }
    
    // Needed for waveforms
    
    virtual void visit(Int32ArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << "Int32(" << inst->fNumTable[i] << ")";
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
    
};

class JuliaInstVisitor : public TextInstVisitor {
   private:
     
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static map<string, bool> gFunctionSymbolTable;

    // Polymorphic math functions
    map<string, string> gPolyMathLibTable;
    
    bool fMutateFun;
    
    string cast2FAUSTFLOAT(const string& str) { return "FAUSTFLOAT(" + str + ")"; }
    
   public:
    using TextInstVisitor::visit;

    JuliaInstVisitor(std::ostream* out, const string& struct_name, int tab = 0, bool mutate_fun = false)
        : TextInstVisitor(out, ".", new JuliaStringTypeManager(xfloat(), "*", struct_name), tab), fMutateFun(mutate_fun)
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
        gFunctionSymbolTable["acoshf"] = true;
        gFunctionSymbolTable["asinhf"] = true;
        gFunctionSymbolTable["atanhf"] = true;
        gFunctionSymbolTable["coshf"]  = true;
        gFunctionSymbolTable["sinhf"]  = true;
        gFunctionSymbolTable["tanhf"]  = true;

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
        gFunctionSymbolTable["acosh"] = true;
        gFunctionSymbolTable["asinh"] = true;
        gFunctionSymbolTable["atanh"] = true;
        gFunctionSymbolTable["coshf"]  = true;
        gFunctionSymbolTable["sinh"]  = true;
        gFunctionSymbolTable["tanh"]  = true;

        // Quad version
        gFunctionSymbolTable["fabsl"]      = true;
        gFunctionSymbolTable["acosl"]      = true;
        gFunctionSymbolTable["asinl"]      = true;
        gFunctionSymbolTable["atanl"]      = true;
        gFunctionSymbolTable["atan2l"]     = true;
        gFunctionSymbolTable["ceill"]      = true;
        gFunctionSymbolTable["cosl"]       = true;
        gFunctionSymbolTable["expl"]       = true;
        gFunctionSymbolTable["exp10l"]     = true;
        gFunctionSymbolTable["floorl"]     = true;
        gFunctionSymbolTable["fmodl"]      = true;
        gFunctionSymbolTable["logl"]       = true;
        gFunctionSymbolTable["log10l"]     = true;
        gFunctionSymbolTable["powl"]       = true;
        gFunctionSymbolTable["remainderl"] = true;
        gFunctionSymbolTable["rintl"]      = true;
        gFunctionSymbolTable["roundl"]     = true;
        gFunctionSymbolTable["sinl"]       = true;
        gFunctionSymbolTable["sqrtl"]      = true;
        gFunctionSymbolTable["tanl"]       = true;
    
        // Hyperbolic
        gFunctionSymbolTable["acoshl"] = true;
        gFunctionSymbolTable["asinhl"] = true;
        gFunctionSymbolTable["atanhl"] = true;
        gFunctionSymbolTable["coshl"]  = true;
        gFunctionSymbolTable["sinhl"]  = true;
        gFunctionSymbolTable["tanhl"]  = true;
   
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
        gPolyMathLibTable["exp10f"]     = "exp10f";
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
                             
        // Hyperbolic
        gPolyMathLibTable["acoshf"]     = "acosh";
        gPolyMathLibTable["asinhf"]     = "asinh";
        gPolyMathLibTable["atanhf"]     = "atanh";
        gPolyMathLibTable["coshf"]      = "cosh";
        gPolyMathLibTable["sinhf"]      = "sinh";
        gPolyMathLibTable["tanhf"]      = "tanh";
    
        gPolyMathLibTable["isnanf"]     = "isnan";
        gPolyMathLibTable["isinff"]     = "isinf";
        gPolyMathLibTable["copysignf"]  = "copysign";
        
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
        gPolyMathLibTable["acosh"]     = "acosh";
        gPolyMathLibTable["asinh"]     = "asinh";
        gPolyMathLibTable["atanh"]     = "atanh";
        gPolyMathLibTable["cosh"]      = "cosh";
        gPolyMathLibTable["sinh"]      = "sinh";
        gPolyMathLibTable["tanh"]      = "tanh";

        gPolyMathLibTable["isnan"]     = "isnan";
        gPolyMathLibTable["isinf"]     = "isinf";
        gPolyMathLibTable["copysign"]  = "copysign";
    }

    virtual ~JuliaInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        // Special case
        if (inst->fZone == "0") {
            *fOut << "declare!(ui_interface, :dummy, " << quote(inst->fKey)
            << ", " << quote(inst->fValue) << ")";
        } else {
            *fOut << "declare!(ui_interface, :" << inst->fZone << ", "
            << quote(inst->fKey) << ", " << quote(inst->fValue) << ")";
        }
        EndLine(' ');
    }

    virtual void visit(OpenboxInst* inst)
    {
        string name;
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                name = "openVerticalBox!(";
                break;
            case OpenboxInst::kHorizontalBox:
                name = "openHorizontalBox!(";
                break;
            case OpenboxInst::kTabBox:
                name = "openTabBox!(";
                break;
        }
        *fOut << name << "ui_interface, " << quote(inst->fName) << ")";
        EndLine(' ');
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "closeBox!(ui_interface)";
        tab(fTab, *fOut);
    }
    
    virtual void visit(AddButtonInst* inst)
    {
        string name;
        if (inst->fType == AddButtonInst::kDefaultButton) {
            name = "addButton!(";
        } else {
            name = "addCheckButton!(";
        }
        *fOut << name << "ui_interface, " << quote(inst->fLabel) << ", :" << inst->fZone << ")";
        EndLine(' ');
    }

    virtual void visit(AddSliderInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                name = "addHorizontalSlider!(";
                break;
            case AddSliderInst::kVertical:
                name = "addVerticalSlider!(";
                break;
            case AddSliderInst::kNumEntry:
                name = "addNumEntry!(";
                break;
        }
        *fOut << name << "ui_interface, " << quote(inst->fLabel) << ", :" << inst->fZone << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fInit)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMin)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMax)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fStep)) << ")";
        EndLine(' ');
    }

    virtual void visit(AddBargraphInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "addHorizontalBargraph!(";
                break;
            case AddBargraphInst::kVertical:
                name = "addVerticalBargraph!(";
                break;
        }
        *fOut << name << "ui_interface, " << quote(inst->fLabel) << ", :" << inst->fZone << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMin)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMax)) << ")";
        EndLine(' ');
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        // Not supported for now
        throw faustexception("ERROR : 'soundfile' primitive not yet supported for Julia\n");
    }
    
    virtual void visit(Int32NumInst* inst) { *fOut << "Int32(" << inst->fNum << ")"; }
    
    virtual void visit(Int64NumInst* inst) { *fOut << "Int64(" << inst->fNum << ")"; }
    
    virtual void visit(Int32ArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << "Int32(" << inst->fNumTable[i] << ")";
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
            *fOut << "xor(";
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
    }
   
    virtual void visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
            *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
            // Allocation is actually done in JuliaInitFieldsVisitor
        } else {
            *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
            if (inst->fValue) {
                *fOut << " = ";
                inst->fValue->accept(this);
            }
        }
        EndLine(' ');
    }

    virtual void visitAux(RetInst* inst, bool gen_empty)
    {
        if (inst->fResult) {
            *fOut << "return ";
            inst->fResult->accept(this);
            EndLine(' ');
        } else if (gen_empty) {
            *fOut << "return";
            EndLine(' ');
        }
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
        generateFunDefBody(inst);
    }
    
    virtual void visit(DeclareBufferIterators* inst)
    {
        // Don't generate if no channels
        if (inst->fNumChannels == 0) return;
    
        for (int i = 0; i < inst->fNumChannels; ++i) {
            *fOut << inst->fBufferName1 << i << " = @inbounds @view " << inst->fBufferName2 << "[:, " << (i+1) << "]";
            tab(fTab, *fOut);
        }
    }
    
    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        if (inst->fCode->fCode.size() == 0) {
            *fOut << ") where {T}" << endl;  // Pure prototype
        } else {
            // Function body
            *fOut << ") where {T}";
            fTab++;
            tab(fTab, *fOut);
            inst->fCode->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << "end";
            tab(fTab, *fOut);
        }
    }

    virtual void visit(NamedAddress* named)
    {
        // kStaticStruct are actually merged in the main DSP
        if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
            *fOut << "dsp.";
        }
        *fOut << named->fName;
    }
    
    /*
    Indexed address can actually be values in an array or fields in a struct type
    */
    virtual void visit(IndexedAddress* indexed)
    {
        indexed->fAddress->accept(this);
        DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
        if (struct_type) {
            Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->fIndex);
            *fOut << "." << struct_type->fType->getName(field_index->fNum);
        } else {
            *fOut << "[";
            Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(indexed->fIndex);
            // Julia arrays start at 1
            if (field_index) {
                *fOut << (field_index->fNum + 1) << "]";
            } else {
                indexed->fIndex->accept(this);
                *fOut << "+1]";
            }
        }
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        faustassert(false);
    }
    
    virtual void visit(StoreVarInst* inst)
    {
        inst->fAddress->accept(this);
        *fOut << " = ";
        inst->fValue->accept(this);
        EndLine(' ');
    }
      
    virtual void visit(::CastInst* inst)
    {
        if (isIntType(inst->fType->getType())) {
            *fOut << "trunc(";
            *fOut << fTypeManager->generateType(inst->fType) << ", ";
        } else {
            *fOut << fTypeManager->generateType(inst->fType) << "(";
        }
        inst->fInst->accept(this);
        *fOut << ")";
    }

    // TODO : does not work, put this code in a function
    virtual void visit(BitcastInst* inst)
    {}
    
    virtual void visitCond(ValueInst* cond)
    {
        *fOut << "(";
        cond->accept(this);
        *fOut << " != 0)";
    }
    
    virtual void visit(Select2Inst* inst)
    {
        *fOut << "(";
        visitCond(inst->fCond);
        *fOut << " ? ";
        inst->fThen->accept(this);
        *fOut << " : ";
        inst->fElse->accept(this);
        *fOut << ")";
    }

    // Generate standard funcall (not 'method' like funcall...)
    virtual void visit(FunCallInst* inst)
    {
        string name = (gPolyMathLibTable.find(inst->fName) != gPolyMathLibTable.end()) ? gPolyMathLibTable[inst->fName] : inst->fName;
        // Function that mutate their arguments use the '!' syntax
        *fOut << name << ((fMutateFun && inst->fArgs.size() > 0) ?  "!(" : "(");
        // Compile parameters
        generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
        *fOut << ")";
    }
    
    virtual void visit(IfInst* inst)
    {
        *fOut << "if ";
        visitCond(inst->fCond);
        fTab++;
        tab(fTab, *fOut);
        inst->fThen->accept(this);
        fTab--;
        back(1, *fOut);
        if (inst->fElse->fCode.size() > 0) {
            *fOut << "elseif";
            fTab++;
            tab(fTab, *fOut);
            inst->fElse->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << "end";
        } else {
            *fOut << "end";
        }
        tab(fTab, *fOut);
    }
  
    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;

        *fOut << "for ";
        fFinishLine = false;
        inst->fInit->accept(this);
        *fOut << ":";
        inst->fEnd->accept(this);
        *fOut << "; ";
        inst->fIncrement->accept(this);
        fFinishLine = true;
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
        back(1, *fOut);
        *fOut << "end";
        tab(fTab, *fOut);
    }
    
    virtual void visit(SimpleForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;
        
        *fOut << "@inbounds for " << inst->getName() << " in ";
    
        if (inst->fReverse) {
            *fOut << "reverse(";
            Int32NumInst* lower_bound = dynamic_cast<Int32NumInst*>(inst->fLowerBound);
            faustassert(lower_bound);
            *fOut << lower_bound->fNum << ":";
            Int32NumInst* upper_bound = dynamic_cast<Int32NumInst*>(inst->fUpperBound);
            if (upper_bound) {
                // If an Int32NumInst, we just generate it without any type information
                // (see visit(Int32NumInst* inst) which adds type information that we don't want here)
                *fOut << upper_bound->fNum;
            } else {
                inst->fUpperBound->accept(this);
            }
            *fOut << ")";
        } else {
            Int32NumInst* lower_bound = dynamic_cast<Int32NumInst*>(inst->fLowerBound);
            faustassert(lower_bound);
            *fOut << lower_bound->fNum << ":";
            Int32NumInst* upper_bound = dynamic_cast<Int32NumInst*>(inst->fUpperBound);
            if (upper_bound) {
                *fOut << (upper_bound->fNum - 1);
            } else {
                inst->fUpperBound->accept(this);
                *fOut << "-1";
            }
        }

        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
        back(1, *fOut);
        *fOut << "end";
        tab(fTab, *fOut);
    }
    
    static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif

