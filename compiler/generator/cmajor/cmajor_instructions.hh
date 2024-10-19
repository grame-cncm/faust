/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#ifndef _CMAJ_INSTRUCTIONS_H
#define _CMAJ_INSTRUCTIONS_H

#include <cctype>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "faust/gui/PathBuilder.h"
#include "text_instructions.hh"

inline std::string buildLabel(const std::string& label)
{
    return replaceCharList(label, {' ', '(', ')', '\\', '/', '.', '-'}, '_');
}

struct CmajorInstUIVisitor : public ShortnameInstVisitor {
    std::stringstream       fOut;
    CmajorStringTypeManager fTypeManager;
    int                     fTab;
    bool                    fHasBargraph;  // Whether the DSP code has some Bargraphs

    std::vector<std::pair<std::string, std::string>> fMetaAux;

    using DispatchVisitor::visit;

    CmajorInstUIVisitor(int tab = 1) : fTypeManager(xfloat(), "*"), fTab(tab), fHasBargraph(false)
    {
    }

    void Tab(int tab) { fTab = tab; }

    // Add metadata to the output if available and clear the metadata container
    void addMeta()
    {
        for (const auto& [key, value] : fMetaAux) {
            if (!std::isdigit(key[0])) {
                fOut << ", meta_" << gGlobal->getFreshID(key) << ": " << quote(value);
            }
        }
        fMetaAux.clear();
    }

    // Retrieve the "cmajor" metadata if present
    std::string getCmajorMetadata() const
    {
        for (const auto& [key, value] : fMetaAux) {
            if (key == "cmajor") {
                return value;
            }
        }
        return "";
    }

    virtual void visit(AddMetaDeclareInst* inst)
    {
        fMetaAux.emplace_back(inst->fKey, inst->fValue);
    }

    virtual void visit(AddButtonInst* inst)
    {
        if (hasShortname()) {
            std::string short_name = buildShortname(inst->fLabel);
            if (gGlobal->gOutputLang == "cmajor-poly") {
                fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()] << " event_"
                     << short_name << " [[ name: " << quote(short_name)
                     << ", group: " << quote(buildPath(inst->fLabel));
                if (inst->fType != AddButtonInst::kDefaultButton) {
                    fOut << ", latching";
                }
                fOut << ", text: \"off|on\""
                     << ", boolean";
                addMeta();
                fOut << " ]];";
            } else if (gGlobal->gOutputLang == "cmajor-hybrid") {
                std::string cmajor_meta = getCmajorMetadata();
                fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()] << " "
                     << ((cmajor_meta != "") ? cmajor_meta : short_name)
                     << " [[ name: " << quote(short_name)
                     << ", group: " << quote(buildPath(inst->fLabel));
                if (inst->fType != AddButtonInst::kDefaultButton) {
                    fOut << ", latching";
                }
                fOut << ", text: \"off|on\""
                     << ", boolean";
                addMeta();
                fOut << " ]];";
            } else {
                fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()] << " event"
                     << inst->fZone << " [[ name: " << quote(short_name)
                     << ", group: " << quote(buildPath(inst->fLabel));
                if (inst->fType != AddButtonInst::kDefaultButton) {
                    fOut << ", latching";
                }
                fOut << ", text: \"off|on\""
                     << ", boolean";
                addMeta();
                fOut << " ]];";
            }
            tab(fTab, fOut);
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }

    virtual void visit(AddSliderInst* inst)
    {
        if (hasShortname()) {
            std::string short_name = buildShortname(inst->fLabel);
            if (gGlobal->gOutputLang == "cmajor-poly") {
                fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()] << " event_"
                     << short_name << " [[ name: " << quote(short_name)
                     << ", group: " << quote(buildPath(inst->fLabel))
                     << ", min: " << checkReal(inst->fMin) << ", max: " << checkReal(inst->fMax)
                     << ", init: " << checkReal(inst->fInit)
                     << ", step: " << checkReal(inst->fStep);
                addMeta();
                fOut << " ]];";
            } else if (gGlobal->gOutputLang == "cmajor-hybrid") {
                std::string cmajor_meta = getCmajorMetadata();
                fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()] << " "
                     << ((cmajor_meta != "") ? cmajor_meta : short_name)
                     << " [[ name: " << quote(short_name)
                     << ", group: " << quote(buildPath(inst->fLabel))
                     << ", min: " << checkReal(inst->fMin) << ", max: " << checkReal(inst->fMax)
                     << ", init: " << checkReal(inst->fInit)
                     << ", step: " << checkReal(inst->fStep);
                addMeta();
                fOut << " ]];";
            } else {
                fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()] << " event"
                     << inst->fZone << " [[ name: " << quote(inst->fLabel)
                     << ", group: " << quote(buildPath(inst->fLabel))
                     << ", min: " << checkReal(inst->fMin) << ", max: " << checkReal(inst->fMax)
                     << ", init: " << checkReal(inst->fInit)
                     << ", step: " << checkReal(inst->fStep);
                addMeta();
                fOut << " ]];";
            }
            tab(fTab, fOut);
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }

    virtual void visit(AddBargraphInst* inst)
    {
        if (hasShortname()) {
            std::string short_name = buildShortname(inst->fLabel);

            // We have bargraphs
            fHasBargraph = true;

            if (gGlobal->gOutputLang == "cmajor-poly") {
                fOut << "output event " << fTypeManager.fTypeDirectTable[itfloat()] << " event_"
                     << short_name << " [[ name: " << quote(short_name)
                     << ", group: " << quote(buildPath(inst->fLabel))
                     << ", min: " << checkReal(inst->fMin) << ", max: " << checkReal(inst->fMax);
                addMeta();
                fOut << " ]];";
            } else {
                fOut << "output event " << fTypeManager.fTypeDirectTable[itfloat()] << " event"
                     << inst->fZone << " [[ name: " << quote(short_name)
                     << ", group: " << quote(buildPath(inst->fLabel))
                     << ", min: " << checkReal(inst->fMin) << ", max: " << checkReal(inst->fMax);
                addMeta();
                fOut << " ]];";
            }
            tab(fTab, fOut);
        } else {
            ShortnameInstVisitor::visit(inst);
        }
    }

    virtual void visit(OpenboxInst* inst)
    {
        /*
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                pushLabel("v:" + inst->fName);
                break;
            case OpenboxInst::kHorizontalBox:
                pushLabel("h:" + inst->fName);
                break;
            case OpenboxInst::kTabBox:
                pushLabel("t:" + inst->fName);
                break;
        }
        */
        ShortnameInstVisitor::visit(inst);
        fMetaAux.clear();
    }

    virtual void visit(CloseboxInst* inst)
    {
        ShortnameInstVisitor::visit(inst);
        fMetaAux.clear();
    }
};

class CmajorInstVisitor : public TextInstVisitor {
   private:
    // Polymorphic math functions
    std::map<std::string, std::string> gPolyMathLibTable;
    ShortnameInstVisitor               fShortNameVisitor;

    std::vector<std::pair<std::string, std::string>> fMetaAux;

    inline std::string checkFloat(float val) { return (std::isinf(val)) ? "inf" : T(val); }
    inline std::string checkDouble(double val) { return (std::isinf(val)) ? "inf" : T(val); }

    std::string getCmajorMetadata() const
    {
        for (const auto& meta : fMetaAux) {
            if (meta.first == "cmajor") {
                return meta.second;
            }
        }
        return "";
    }

   public:
    CmajorInstVisitor(std::ostream* out, int tab = 0)
        : TextInstVisitor(out, ".", new CmajorStringTypeManager(xfloat(), ""), tab)
    {
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
        gPolyMathLibTable["atan2f"]     = "atan2";
        gPolyMathLibTable["ceilf"]      = "ceil";
        gPolyMathLibTable["cosf"]       = "cos";
        gPolyMathLibTable["expf"]       = "exp";
        gPolyMathLibTable["exp2f"]      = "exp2";
        gPolyMathLibTable["exp10f"]     = "exp10f";
        gPolyMathLibTable["floorf"]     = "floor";
        gPolyMathLibTable["fmodf"]      = "fmod";
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

        // Additional hyperbolic math functions are included in Cmajor
        gPolyMathLibTable["acoshf"] = "acosh";
        gPolyMathLibTable["asinhf"] = "asinh";
        gPolyMathLibTable["atanhf"] = "atanh";
        gPolyMathLibTable["coshf"]  = "cosh";
        gPolyMathLibTable["sinhf"]  = "sinh";
        gPolyMathLibTable["tanhf"]  = "tanh";

        gPolyMathLibTable["isnanf"] = "isnan";
        gPolyMathLibTable["isinff"] = "isinf";
        // Manually implemented
        gPolyMathLibTable["copysignf"] = "copysign";

        // Polymath mapping double version
        gPolyMathLibTable["max_"] = "max";
        gPolyMathLibTable["min_"] = "min";

        gPolyMathLibTable["fabs"]      = "abs";
        gPolyMathLibTable["acos"]      = "acos";
        gPolyMathLibTable["asin"]      = "asin";
        gPolyMathLibTable["atan"]      = "atan";
        gPolyMathLibTable["atan2"]     = "atan2";
        gPolyMathLibTable["ceil"]      = "ceil";
        gPolyMathLibTable["cos"]       = "cos";
        gPolyMathLibTable["exp"]       = "exp";
        gPolyMathLibTable["exp2"]      = "exp2";
        gPolyMathLibTable["exp10"]     = "exp10";
        gPolyMathLibTable["floor"]     = "floor";
        gPolyMathLibTable["fmod"]      = "fmod";
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

        // Additional hyperbolic math functions are included in Cmajor
        gPolyMathLibTable["acosh"] = "acosh";
        gPolyMathLibTable["asinh"] = "asinh";
        gPolyMathLibTable["atanh"] = "atanh";
        gPolyMathLibTable["cosh"]  = "cosh";
        gPolyMathLibTable["sinh"]  = "sinh";
        gPolyMathLibTable["tanh"]  = "tanh";

        gPolyMathLibTable["isnan"] = "isnan";
        gPolyMathLibTable["isinf"] = "isinf";
        // Manually implemented
        gPolyMathLibTable["copysignf"] = "copysign";
    }

    virtual ~CmajorInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        fMetaAux.push_back(std::make_pair(inst->fKey, inst->fValue));
    }

    virtual void visit(OpenboxInst* inst)
    {
        fShortNameVisitor.visit(inst);
        fMetaAux.clear();
    }

    virtual void visit(CloseboxInst* inst)
    {
        fShortNameVisitor.visit(inst);
        fMetaAux.clear();
    }

    virtual void visit(AddButtonInst* inst)
    {
        if (fShortNameVisitor.hasShortname()) {
            std::string short_name = fShortNameVisitor.buildShortname(inst->fLabel);
            *fOut << "// " << short_name;
            EndLine(' ');
            if (gGlobal->gOutputLang == "cmajor-poly") {
                *fOut << "event event_" << short_name << " ("
                      << fTypeManager->fTypeDirectTable[itfloat()] << " val) { "
                      << "fUpdated ||= (" << inst->fZone << " != val); " << inst->fZone
                      << " = val; }";
            } else if (gGlobal->gOutputLang == "cmajor-hybrid") {
                std::string cmajor_meta = getCmajorMetadata();
                *fOut << "event " << ((cmajor_meta != "") ? cmajor_meta : short_name) << " ("
                      << fTypeManager->fTypeDirectTable[itfloat()] << " val) { "
                      << "fUpdated ||= (" << inst->fZone << " != val); " << inst->fZone
                      << " = val; }";
                fMetaAux.clear();
            } else {
                *fOut << "event event" << inst->fZone << " ("
                      << fTypeManager->fTypeDirectTable[itfloat()] << " val) { "
                      << "fUpdated ||= (" << inst->fZone << " != val); " << inst->fZone
                      << " = val; }";
            }
            EndLine(' ');
        } else {
            fShortNameVisitor.visit(inst);
        }
    }

    virtual void visit(AddSliderInst* inst)
    {
        if (fShortNameVisitor.hasShortname()) {
            std::string short_name = fShortNameVisitor.buildShortname(inst->fLabel);
            *fOut << "// " << short_name << " [init = " << checkReal(inst->fInit)
                  << ", min = " << checkReal(inst->fMin) << ", max = " << checkReal(inst->fMax)
                  << ", step = " << checkReal(inst->fStep) << "]";
            EndLine(' ');
            if (gGlobal->gOutputLang == "cmajor-poly") {
                *fOut << "event event_" << short_name << " ("
                      << fTypeManager->fTypeDirectTable[itfloat()] << " val) { "
                      << "fUpdated ||= (" << inst->fZone << " != val); " << inst->fZone
                      << " = val; }";
            } else if (gGlobal->gOutputLang == "cmajor-hybrid") {
                std::string cmajor_meta = getCmajorMetadata();
                *fOut << "event " << ((cmajor_meta != "") ? cmajor_meta : short_name) << " ("
                      << fTypeManager->fTypeDirectTable[itfloat()] << " val) { "
                      << "fUpdated ||= (" << inst->fZone << " != val); " << inst->fZone
                      << " = val; }";
                fMetaAux.clear();
            } else {
                *fOut << "event event" << inst->fZone << " ("
                      << fTypeManager->fTypeDirectTable[itfloat()] << " val) { "
                      << "fUpdated ||= (" << inst->fZone << " != val); " << inst->fZone
                      << " = val; }";
            }
            EndLine(' ');
        } else {
            fShortNameVisitor.visit(inst);
        }
    }

    virtual void visit(AddBargraphInst* inst)
    {
        if (fShortNameVisitor.hasShortname()) {
            std::string short_name = fShortNameVisitor.buildShortname(inst->fLabel);
            *fOut << "// " << short_name << " [min = " << checkReal(inst->fMin)
                  << ", max = " << checkReal(inst->fMax) << "]";
            EndLine(' ');
        } else {
            fShortNameVisitor.visit(inst);
        }
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        // Not supported for now
        throw faustexception("ERROR : 'soundfile' primitive not yet supported for Cmajor\n");
    }

    virtual void visit(DeclareVarInst* inst)
    {
        std::string name = inst->getName();

        // special case for input/output considered as 'streams'
        if (startWith(name, "input")) {
            *fOut << "input stream " << fTypeManager->fTypeDirectTable[itfloat()] << " " << name;
        } else if (startWith(name, "output")) {
            *fOut << "output stream " << fTypeManager->fTypeDirectTable[itfloat()] << " " << name;
        } else {
            if (inst->getAccess() & Address::kConst) {
                *fOut << "const ";
            }
            *fOut << fTypeManager->generateType(inst->fType, name);
            if (inst->fValue) {
                *fOut << " = ";
                inst->fValue->accept(this);
            }
        }
        EndLine();
    }

    virtual void visit(DeclareFunInst* inst) {}

    /*
     Indexed adresses can actually be values in an array or fields in a struct type
     */
    virtual void visit(IndexedAddress* indexed)
    {
        indexed->fAddress->accept(this);
        DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
        if (struct_type) {
            Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->getIndex());
            *fOut << "." << struct_type->fType->getName(field_index->fNum);
        } else {
            if (isInt32Num(indexed->getIndex())) {
                *fOut << "[";
                indexed->getIndex()->accept(this);
                *fOut << "]";
            } else {
                // wrap code is automatically added by the Cmajor compiler (and the same if [idex]
                // syntax is used)
                *fOut << ".at (";
                indexed->getIndex()->accept(this);
                *fOut << ")";
            }
        }
    }

    virtual void visit(StoreVarInst* inst)
    {
        std::string name = inst->getName();
        // special case for 'output' considered as a 'stream'
        if (startWith(name, "output")) {
            inst->fAddress->accept(this);
            *fOut << " <- ";
            inst->fValue->accept(this);
            EndLine();
            // special case for 'bargraph' considered as an 'output event'
        } else if (startWith(name, "fHbargraph") || startWith(name, "fVbargraph")) {
            // value is stored in the bargraph variable
            {
                inst->fAddress->accept(this);
                *fOut << " = ";
                inst->fValue->accept(this);
                EndLine();
            }
            // and the bargraph variable is sent using the 'output' event handler
            {
                *fOut << "if (fControlSlice == 0) { ";
                *fOut << "event";
                inst->fAddress->accept(this);
                *fOut << " <- ";
                inst->fAddress->accept(this);
                *fOut << "; }";
                tab(fTab, *fOut);
            }
        } else {
            inst->fAddress->accept(this);
            *fOut << " = ";
            inst->fValue->accept(this);
            EndLine();
        }
    }

    virtual void visit(FloatNumInst* inst) { *fOut << checkFloat(inst->fNum); }

    virtual void visit(FloatArrayNumInst* inst)
    {
        char sep = '(';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << ')';
    }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        char sep = '(';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << ')';
    }

    virtual void visit(Int64NumInst* inst) { *fOut << inst->fNum << "L"; }

    virtual void visit(DoubleNumInst* inst) { *fOut << checkDouble(inst->fNum); }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        char sep = '(';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << ')';
    }

    virtual void visit(::CastInst* inst)
    {
        std::string type = fTypeManager->generateType(inst->fType);
        *fOut << type << " (";
        inst->fInst->accept(this);
        *fOut << ")";
    }

    virtual void visit(BitcastInst* inst) { faustassert(false); }

    virtual void visitCond(ValueInst* cond)
    {
        *fOut << "(bool (";
        cond->accept(this);
        *fOut << "))";
    }

    virtual void visit(IfInst* inst)
    {
        *fOut << "if ";
        visitCond(inst->fCond);
        *fOut << " {";
        fTab++;
        tab(fTab, *fOut);
        inst->fThen->accept(this);
        fTab--;
        back(1, *fOut);
        if (inst->fElse->fCode.size() > 0) {
            *fOut << "} else {";
            fTab++;
            tab(fTab, *fOut);
            inst->fElse->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << "}";
        } else {
            *fOut << "}";
        }
        tab(fTab, *fOut);
    }

    virtual void visit(FunCallInst* inst)
    {
        std::string name;
        if (gPolyMathLibTable.find(inst->fName) != gPolyMathLibTable.end()) {
            name = gPolyMathLibTable[inst->fName];
        } else {
            name = inst->fName;
        }

        *fOut << gGlobal->getMathFunction(name) << ((inst->fArgs.size() > 0) ? " (" : "(");

        // Compile parameters
        generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
        *fOut << ")";
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) {
            return;
        }

        *fOut << "for (";

        fFinishLine = false;
        inst->fInit->accept(this);
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
        back(1, *fOut);
        *fOut << "}";
        tab(fTab, *fOut);
    }

    StringTypeManager* getTypeManager() { return fTypeManager; }
};

// For subcontainers: variable access is specific
class CmajorSubContainerInstVisitor : public CmajorInstVisitor {
   public:
    CmajorSubContainerInstVisitor(std::ostream* out, int tab = 0) : CmajorInstVisitor(out, tab) {}

    virtual void visit(NamedAddress* named)
    {
        if (named->isStruct()) {
            *fOut << "this.";
        }
        *fOut << named->fName;
    }
};

#endif
