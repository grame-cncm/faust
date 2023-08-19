/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2023 GRAME, Centre National de Creation Musicale
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

#ifndef _CODEBOX_INSTRUCTIONS_H
#define _CODEBOX_INSTRUCTIONS_H

#include <string>

#include "text_instructions.hh"
#include "struct_manager.hh"
#include "json_instructions.hh"

// Variable identifier cannot end by a number, so add a suffix
inline std::string codeboxVarName(const std::string& name) { return name + "_cb"; }

// When testing, for rnbo_dsp class to properly decode controllers
inline std::string buildButtonLabel(AddButtonInst::ButtonType type, const std::string& label)
{
    if (gGlobal->gOutputLang == "codebox-test") {
        switch (type) {
            case AddButtonInst::kDefaultButton:
                return("RB_button_" + label);
            case AddButtonInst::kCheckButton:
                return("RB_checkbox_" + label);
            default:
                faustassert(false);
                break;
        }
    }
    return label;
}

// When testing, for rnbo_dsp class to properly decode controllers
inline std::string buildSliderLabel(AddSliderInst::SliderType type, const std::string& label)
{
    if (gGlobal->gOutputLang == "codebox-test") {
        switch (type) {
            case AddSliderInst::kHorizontal:
                return("RB_hslider_" + label);
            case AddSliderInst::kVertical:
                return("RB_vslider_" + label);
            case AddSliderInst::kNumEntry:
                return("RB_nentry_" + label);
            default:
                faustassert(false);
                break;
        }
    }
    return label;
}

// Visitor used to fill the 'update' function and associate control labels with their parameter names
// (using 2 passes, one to build shortname, the second to use them)
struct CodeboxUpdateParamsVisitor : public ShortnameInstVisitor {
    std::ostream* fOut;
    int           fTab;
    
    CodeboxUpdateParamsVisitor(std::ostream* out, int tab = 0) : fOut(out), fTab(tab) {}
    
     void print(const std::string& shortname, const std::string& zone)
    {
        *fOut << "fUpdated = int(fUpdated) | (" << shortname << " != "
              << codeboxVarName(zone) << "); " << codeboxVarName(zone) << " = " << shortname << ";";
        tab(fTab, *fOut);
    }
    
    void visit(AddButtonInst* inst) override
    {
        if (hasShortname()) {
            print(buildButtonLabel(inst->fType, buildShortname(inst->fLabel)), inst->fZone);
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }
    
    void visit(AddSliderInst* inst) override
    {
        if (hasShortname()) {
            print(buildSliderLabel(inst->fType, buildShortname(inst->fLabel)), inst->fZone);
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }
    
};

// Visitor used to create 'update' function prototype by printing the list of shortnames, used as parameters
// (using 2 passes, one to build shortname, the second to use them)
struct CodeboxLabelsVisitor : public ShortnameInstVisitor {

    std::vector<std::string> fUILabels;
    std::ostream* fOut;
    
    CodeboxLabelsVisitor(std::ostream* out) : fOut(out) {}
     
    void visit(AddButtonInst* inst) override
    {
        if (hasShortname()) {
            fUILabels.push_back(buildButtonLabel(inst->fType, buildShortname(inst->fLabel)));
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }
    
    void visit(AddSliderInst* inst) override
    {
        if (hasShortname()) {
            fUILabels.push_back(buildSliderLabel(inst->fType, buildShortname(inst->fLabel)));
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }
 
    void visit(AddSoundfileInst* inst) override
    {
        throw(faustexception("ERROR : Soundfile is not available in Codebox\n"));
    }
    
    void printArgs()
    {
        for (size_t i = 0; i < fUILabels.size(); i++) {
            *fOut << fUILabels[i];
            if (i < fUILabels.size() - 1) *fOut << ",";
        }
    }
    
    // Identifiers ending with a number have to be accessed with "this."
    void printArgsCall()
    {
        for (size_t i = 0; i < fUILabels.size(); i++) {
            std::string label = fUILabels[i];
            bool is_digit = isdigit(label.back());
            *fOut << (is_digit ? "this." : "") << label;
            if (i < fUILabels.size() - 1) *fOut << ",";
        }
    }
};

// Visitor used to initialize array fields into the DSP structure
struct CodeboxInitArraysVisitor : public DispatchVisitor {
    std::ostream* fOut;
    int           fTab;
    
    // The name of the currently generated array
    std::string   fCurArray;
    
    CodeboxInitArraysVisitor(std::ostream* out, int tab = 0) : fOut(out), fTab(tab) {}
    
    virtual void visit(DeclareVarInst* inst) override
    {
        // Keep the array name
        if (inst->fType->isArrayTyped() && inst->fValue) {
            fCurArray = codeboxVarName(inst->fAddress->getName());
            inst->fValue->accept(this);
        }
    }
      
    // Needed for waveforms
    virtual void visit(Int32ArrayNumInst* inst) override
    {
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << fCurArray << "[" << i << "] = " << inst->fNumTable[i] << ";";
            tab(fTab, *fOut);
        }
    }
    
    virtual void visit(FloatArrayNumInst* inst) override
    {
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << fCurArray << "[" << i << "] = " << std::fixed << inst->fNumTable[i] << ";";
            tab(fTab, *fOut);
        }
    }
    
    virtual void visit(DoubleArrayNumInst* inst) override
    {
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << fCurArray << "[" << i << "] = " << std::fixed << inst->fNumTable[i] << ";";
            tab(fTab, *fOut);
        }
    }
    
};

// Visitor to keep bargraph variables
struct CodeboxBargraphVisitor : public DispatchVisitor {

    std::vector<std::string> fVariables;
    
    virtual void visit(DeclareVarInst* inst) override
    {
        std::string name = inst->fAddress->getName();
        if (startWith(name, "fHbargraph") || startWith(name, "fVbargraph")) {
            fVariables.push_back(codeboxVarName(name));
        }
    }
};

// Visitor used to generate @params with shortnames (using 2 passes, one to build shortname, the second to use them)
struct CodeboxParamsVisitor : public ShortnameInstVisitor {

    std::ostream* fOut;
    int           fTab;
   
    CodeboxParamsVisitor(std::ostream* out, int tab = 0) : fOut(out), fTab(tab) {}

    virtual void visit(AddButtonInst* inst) override
    {
        if (hasShortname()) {
            *fOut << "@param({min: 0., max: 1.}) " << buildButtonLabel(inst->fType, buildShortname(inst->fLabel)) << " = 0.;";
            tab(fTab, *fOut);
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }

    virtual void visit(AddSliderInst* inst) override
    {
        if (hasShortname()) {
            *fOut << "@param({min: " << checkReal(inst->fMin) << ", max: "
            << checkReal(inst->fMax) << "}) "
            << buildSliderLabel(inst->fType, buildShortname(inst->fLabel)) << " = " << checkReal(inst->fInit) << ";";
            tab(fTab, *fOut);
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }

};

class CodeboxInstVisitor : public TextInstVisitor {
   private:
    
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static std::map<std::string, bool> gFunctionSymbolTable;
    
    // Polymorphic math functions
    std::map<std::string, std::string> gPolyMathLibTable;
    
   public:
    using TextInstVisitor::visit;

    CodeboxInstVisitor(std::ostream* out, const std::string& struct_name, int tab = 0)
        : TextInstVisitor(out, ".", new CodeboxStringTypeManager(xfloat(), "*", struct_name), tab)
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
        gFunctionSymbolTable["acosh"] = true;
        gFunctionSymbolTable["asinh"] = true;
        gFunctionSymbolTable["atanh"] = true;
        gFunctionSymbolTable["coshf"] = true;
        gFunctionSymbolTable["sinh"]  = true;
        gFunctionSymbolTable["tanh"]  = true;
        
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
        gPolyMathLibTable["exp10f"]     = "exp10";
        gPolyMathLibTable["floorf"]     = "floor";
        // fmodf is not there
        gPolyMathLibTable["fmodf"]      = "safemod";
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
        //gPolyMathLibTable["isinff"]     = "isinf";
        //gPolyMathLibTable["copysignf"]  = "copysign";
        
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
        // fmod is not there
        gPolyMathLibTable["fmod"]      = "safemod";
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
        //gPolyMathLibTable["isinf"]     = "isinf";
        //gPolyMathLibTable["copysign"]  = "copysign";
    }

    virtual ~CodeboxInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {}

    virtual void visit(AddSoundfileInst* inst)
    {
        throw(faustexception("ERROR : Soundfile is not available in Codebox\n"));
    }
    
    virtual void visit(DeclareVarInst* inst)
    {
        // Do not generate 
        if (startWith(inst->fAddress->getName(), "input") || startWith(inst->fAddress->getName(), "output")) {
            return;
        }
        // Struct variables should persist across the codebox lifetime
        if (inst->fAddress->isStruct() || inst->fAddress->isStaticStruct()) {
            *fOut << "@state ";
        // Stack variables need a 'let'
        } else if (inst->fAddress->isStack() || inst->fAddress->isLoop()) {
            *fOut << "let ";
        }
        *fOut << fTypeManager->generateType(inst->fType, codeboxVarName(inst->fAddress->getName()));
        // Arrays are set in CodeboxInitArraysVisitor
        if (inst->fValue && inst->fType->isBasicTyped()) {
            *fOut << " = ";
            inst->fValue->accept(this);
        // @state with a type have to be initialized
        } else if (inst->fType->isBasicTyped() && (inst->fAddress->isStruct() || inst->fAddress->isStaticStruct())) {
            *fOut << " = 0";
        }
        EndLine();
    }
    
    // Empty here and done in CodeboxInitArraysVisitor
    virtual void visit(Int32ArrayNumInst* inst)
    {}
    virtual void visit(FloatArrayNumInst* inst)
    {}
    virtual void visit(DoubleArrayNumInst* inst)
    {}
    
    virtual void visit(DropInst* inst)
    {}
    
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
     
    virtual void visit(NamedAddress* named)
    {
        // On the fly renaming
        if (named->fName == "sample_rate") {
            // Special name for accessing global SR
            *fOut << "samplerate()";
        } else {
            *fOut << codeboxVarName(named->fName);
        }
    }
   
    virtual void visit(::CastInst* inst)
    {
        if (isIntType(inst->fType->getType())) {
            // int(X) is incorrectly using floor in the generated code
            // *fOut << "int(";
            *fOut << "trunc(";
            inst->fInst->accept(this);
            *fOut << ")";
        } else {
            inst->fInst->accept(this);
        }
    }
    
    virtual void visit(BinopInst* inst)
    {
        Typed::VarType type1 = TypingVisitor::getType(inst->fInst1);
        Typed::VarType type2 = TypingVisitor::getType(inst->fInst2);
    
        // Some special cases for integers 
        if (isInt32Type(type1) && isInt32Type(type2)) {
            static std::map<int, std::string> iop = { {kRem, "imod("}, {kAdd, "iadd("}, {kMul, "imul("} };
            if (iop.find(inst->fOpcode) != iop.end()) {
                *fOut << iop[inst->fOpcode];
                inst->fInst1->accept(this);
                *fOut << ", ";
                inst->fInst2->accept(this);
                *fOut << ")";
                return;
            }
        }
    
        // Operator precedence is possibly not like C/C++, so for simplicity, we keep the fully parenthesized version
        *fOut << "(";
        inst->fInst1->accept(this);
        *fOut << " ";
        *fOut << gBinOpTable[inst->fOpcode]->fName;
        *fOut << " ";
        inst->fInst2->accept(this);
        *fOut << ")";
    }
    
    // Generate standard funcall (not 'method' like funcall...)
    virtual void visit(FunCallInst* inst)
    {
        std::string name = (gPolyMathLibTable.find(inst->fName) != gPolyMathLibTable.end()) ? gPolyMathLibTable[inst->fName] : inst->fName;
        *fOut << name << "(";
        // Compile parameters
        generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
        *fOut << ")";
    }
    
    static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif

