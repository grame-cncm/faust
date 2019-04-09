/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#ifndef _SOUL_INSTRUCTIONS_H
#define _SOUL_INSTRUCTIONS_H

#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cctype>

#include "Text.hh"
#include "text_instructions.hh"

using namespace std;

struct SOULInstUIVisitor : public DispatchVisitor {
    std::stringstream     fOut;
    SOULStringTypeManager fTypeManager;
    int                   fTab;
    std::vector<std::pair <std::string, std::string> > fMetaAux;

    using DispatchVisitor::visit;

    SOULInstUIVisitor(int tab) : fTypeManager(FLOATMACRO, "*"), fTab(tab) {}
    
    void addMeta()
    {
        if (fMetaAux.size() > 0) {
            for (size_t i = 0; i < fMetaAux.size(); i++) {
                if (!std::isdigit(fMetaAux[i].first[0])) {
                    fOut << ", " << fMetaAux[i].first << ": " << quote(fMetaAux[i].second);
                }
            }
        }
        fMetaAux.clear();
    }
   
    virtual void visit(AddMetaDeclareInst* inst)
    {
        fMetaAux.push_back(std::make_pair(inst->fKey, inst->fValue));
    }
   
    virtual void visit(AddButtonInst* inst)
    {
        if (gGlobal->gOutputLang == "soul-poly") {
            vector<char> rep = {' ', '(', ')', '/', '\\', '.'};
            fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()]
            << " event_" << replaceCharList(inst->fLabel, rep, '_')
            << " [[ label: " << quote(inst->fLabel)
            << ", min: 0.0f, max: 1.0f, init: 0.0f, step: 1.0f";
            addMeta();
            fOut << " ]];";
        } else {
            fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()]
            << " event" << inst->fZone
            << " [[ label: " << quote(inst->fLabel)
            << ", min: 0.0f, max: 1.0f, init: 0.0f, step: 1.0f";
            addMeta();
            fOut << " ]];";
        }
        tab(fTab, fOut);
    }

    virtual void visit(AddSliderInst* inst)
    {
        if (gGlobal->gOutputLang == "soul-poly") {
            vector<char> rep = {' ', '(', ')', '/', '\\', '.'};
            fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()]
            << " event_" << replaceCharList(inst->fLabel, rep, '_')
            << " [[ label: " << quote(inst->fLabel)
            << ", min: " << checkReal(inst->fMin)
            << ", max: " << checkReal(inst->fMax)
            << ", init: " << checkReal(inst->fInit)
            << ", step: " << checkReal(inst->fStep);
            addMeta();
            fOut << " ]];";
        } else {
            fOut << "input event " << fTypeManager.fTypeDirectTable[itfloat()]
            << " event" << inst->fZone
            << " [[ label: " << quote(inst->fLabel)
            << ", min: " << checkReal(inst->fMin)
            << ", max: " << checkReal(inst->fMax)
            << ", init: " << checkReal(inst->fInit)
            << ", step: " << checkReal(inst->fStep);
            addMeta();
            fOut << " ]];";
        }
        tab(fTab, fOut);
    }

    virtual void visit(AddBargraphInst* inst)
    {
        if (gGlobal->gOutputLang == "soul-poly") {
            vector<char> rep = {' ', '(', ')', '/', '\\', '.'};
            fOut << "output event " << fTypeManager.fTypeDirectTable[itfloat()]
            << " event_" << quote(replaceCharList(inst->fLabel, rep, '_'))
            << " [[ label: " << inst->fLabel
            << ", min: " << checkReal(inst->fMin)
            << ", max: " << checkReal(inst->fMax);
            addMeta();
            fOut << " ]];";
        } else {
            fOut << "output event " << fTypeManager.fTypeDirectTable[itfloat()]
            << " event" << inst->fZone
            << " [[ label: " << quote(inst->fLabel)
            << ", min: " << checkReal(inst->fMin)
            << ", max: " << checkReal(inst->fMax);
            addMeta();
            fOut << " ]];";
        }
        tab(fTab, fOut);
    }
    
    virtual void visit(OpenboxInst* inst)
    {
        fMetaAux.clear();
    }
    
    virtual void visit(CloseboxInst* inst)
    {
        fMetaAux.clear();
    }
};

class SOULInstVisitor : public TextInstVisitor {
   private:
    // Polymorphic math functions
    map<string, string> gPolyMathLibTable;

    // Whether to consider an 'int' as a 'boolean' later on in code generation
    bool fIntAsBool;

   public:
    SOULInstVisitor(std::ostream* out, int tab = 0)
        : TextInstVisitor(out, ".", new SOULStringTypeManager(FLOATMACRO, ""), tab)
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
        gPolyMathLibTable["roundf"]     = "round";
        gPolyMathLibTable["sinf"]       = "sin";
        gPolyMathLibTable["sqrtf"]      = "sqrt";
        gPolyMathLibTable["tanf"]       = "tan";
        
        // Additional hyperbolic math functions are included in SOUL
        gPolyMathLibTable["acoshf"] = "acosh";
        gPolyMathLibTable["asinhf"] = "asinh";
        gPolyMathLibTable["atanhf"] = "atanh";
        gPolyMathLibTable["coshf"]  = "cosh";
        gPolyMathLibTable["sinhf"]  = "sinh";
        gPolyMathLibTable["tanhf"]  = "tanh";

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
        gPolyMathLibTable["round"]     = "round";
        gPolyMathLibTable["sin"]       = "sin";
        gPolyMathLibTable["sqrt"]      = "sqrt";
        gPolyMathLibTable["tan"]       = "tan";

        // Additional hyperbolic math functions are included in SOUL
        gPolyMathLibTable["acosh"] = "acosh";
        gPolyMathLibTable["asinh"] = "asinh";
        gPolyMathLibTable["atanh"] = "atanh";
        gPolyMathLibTable["cosh"]  = "cosh";
        gPolyMathLibTable["sinh"]  = "sinh";
        gPolyMathLibTable["tanh"]  = "tanh";

        fIntAsBool = false;
    }

    virtual ~SOULInstVisitor() {}

    virtual void visit(AddButtonInst* inst)
    {
        *fOut << "// " << inst->fLabel;
        EndLine(' ');
        if (gGlobal->gOutputLang == "soul-poly") {
            vector<char> rep = {' ', '(', ')', '/', '\\', '.'};
            *fOut << "event event_" << replaceCharList(inst->fLabel, rep, '_') << " ("
                  << fTypeManager->fTypeDirectTable[itfloat()] << " val) { " << inst->fZone
                  << " = val; fUpdated = true; }";
        } else {
            *fOut << "event event" << inst->fZone << " (" << fTypeManager->fTypeDirectTable[itfloat()] << " val) { "
                  << inst->fZone << " = val; fUpdated = true; }";
        }
        EndLine(' ');
    }

    virtual void visit(AddSliderInst* inst)
    {
        *fOut << "// " << inst->fLabel << " [init = " << checkReal(inst->fInit)
              << ", min = " << checkReal(inst->fMin) << ", max = " << checkReal(inst->fMax)
              << ", step = " << checkReal(inst->fStep) << "]";
        EndLine(' ');
        if (gGlobal->gOutputLang == "soul-poly") {
            vector<char> rep = {' ', '(', ')', '/', '\\', '.'};
            *fOut << "event event_" << replaceCharList(inst->fLabel, rep, '_') << " ("
                  << fTypeManager->fTypeDirectTable[itfloat()] << " val) { " << inst->fZone
                  << " = val; fUpdated = true; }";
        } else {
            *fOut << "event event" << inst->fZone << " (" << fTypeManager->fTypeDirectTable[itfloat()] << " val) { "
                  << inst->fZone << " = val; fUpdated = true; }";
        }
        EndLine(' ');
    }

    virtual void visit(AddBargraphInst* inst)
    {
        *fOut << "// " << inst->fLabel << " [min = " << checkReal(inst->fMin) << ", max = " << checkReal(inst->fMax)
              << "]";
        EndLine(' ');
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        // Not supported for now
        throw faustexception("ERROR : AddSoundfileInst not supported for SOUL\n");
    }

    virtual void visit(DeclareVarInst* inst)
    {
        string name = inst->fAddress->getName();

        // special case for input/output considered as 'streams'
        if (startWith(name, "input")) {
            *fOut << "input stream " << fTypeManager->fTypeDirectTable[itfloat()] << " " << name;
        } else if (startWith(name, "output")) {
            *fOut << "output stream " << fTypeManager->fTypeDirectTable[itfloat()] << " " << name;
        } else {
            if (inst->fAddress->getAccess() & Address::kConst) {
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
            Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->fIndex);
            *fOut << "." << struct_type->fType->getName(field_index->fNum);
        } else {
            if (dynamic_cast<Int32NumInst*>(indexed->fIndex)) {
                *fOut << "[";
                indexed->fIndex->accept(this);
                *fOut << "]";
            } else {
                *fOut << ".at (";
                indexed->fIndex->accept(this);
                *fOut << ")";
            }
        }
    }

    virtual void visit(StoreVarInst* inst)
    {
        // special case for 'output' considered as a 'stream'
        if (startWith(inst->fAddress->getName(), "output")) {
            inst->fAddress->accept(this);
            *fOut << " << ";
            inst->fValue->accept(this);
            EndLine();
            // special case for 'bargraph' considered as an 'output event'
        } else if (startWith(inst->fAddress->getName(), "fHbargraph") ||
                   startWith(inst->fAddress->getName(), "fVbargraph")) {
            // value is stored in the bargraph variable
            {
                inst->fAddress->accept(this);
                *fOut << " = ";
                inst->fValue->accept(this);
                EndLine();
            }
            // and the bargraph variable is sent using the 'output' event handler
            {
                *fOut << "event";
                inst->fAddress->accept(this);
                *fOut << " << ";
                inst->fAddress->accept(this);
                EndLine();
            }
        } else {
            inst->fAddress->accept(this);
            *fOut << " = ";
            inst->fValue->accept(this);
            EndLine();
        }
    }

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
        string type = fTypeManager->generateType(inst->fType);
        *fOut << type << " (";
        inst->fInst->accept(this);
        *fOut << ")";
    }

    virtual void visit(BitcastInst* inst) { faustassert(false); }

    virtual void visit(Select2Inst* inst)
    {
        *fOut << "(bool (";

        fIntAsBool = true;
        inst->fCond->accept(this);
        fIntAsBool = false;
        *fOut << ") ? ";

        inst->fThen->accept(this);
        *fOut << " : ";
        inst->fElse->accept(this);
        *fOut << ")";
    }

    virtual void visit(BinopInst* inst)
    {
        if (isBoolOpcode(inst->fOpcode) && !fIntAsBool) {
            *fOut << "int (";
        }
        *fOut << "(";

        // Hack to make it work again with 'soul' version 0.0.6
        if (isLogicalOpcode(inst->fOpcode)) {
            *fOut << "int (";
        }

        inst->fInst1->accept(this);

        // Hack to make it work again with 'soul' version 0.0.6
        if (isLogicalOpcode(inst->fOpcode)) {
            *fOut << ")";
        }

        *fOut << " ";
        *fOut << gBinOpTable[inst->fOpcode]->fName;
        *fOut << " ";

        // Hack to make it work again with 'soul' version 0.0.6
        if (isLogicalOpcode(inst->fOpcode)) {
            *fOut << "int (";
        }

        inst->fInst2->accept(this);

        // Hack to make it work again with 'soul' version 0.0.6
        if (isLogicalOpcode(inst->fOpcode)) {
            *fOut << ")";
        }

        *fOut << ")";
        if (isBoolOpcode(inst->fOpcode) && !fIntAsBool) {
            *fOut << ")";
        }
    }

    virtual void visit(FunCallInst* inst)
    {
        string name;
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
        if (inst->fCode->size() == 0) return;

        *fOut << "for (";

        fFinishLine = false;
        inst->fInit->accept(this);
        *fOut << "; ";

        fIntAsBool = true;
        inst->fEnd->accept(this);
        fIntAsBool = false;
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
    }

    StringTypeManager* getTypeManager() { return fTypeManager; }
};

// For subcontainers: variable access is specific
class SOULSubContainerInstVisitor : public SOULInstVisitor {
   public:
    SOULSubContainerInstVisitor(std::ostream* out, int tab = 0) : SOULInstVisitor(out, tab) {}

    virtual void visit(NamedAddress* named)
    {
        if (named->getAccess() & Address::kStruct) {
            *fOut << "this.";
        }
        *fOut << named->fName;
    }
};

#endif
