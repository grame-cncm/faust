/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _C_INSTRUCTIONS_H
#define _C_INSTRUCTIONS_H

#include <string>

#include "text_instructions.hh"
#include "struct_manager.hh"

/**
 * Implement C FIR visitor.
 */

class CInstVisitor : public TextInstVisitor {
   private:
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static std::map<std::string, bool> gFunctionSymbolTable;

    // Polymorphic math functions
    std::map<std::string, std::string> fPolyMathLibTable;
    
    std::string cast2FAUSTFLOAT(const std::string& str) { return "(FAUSTFLOAT)" + str; }
    
   public:
    using TextInstVisitor::visit;

    CInstVisitor(std::ostream* out, const std::string& struct_name, int tab = 0)
        : TextInstVisitor(out, "->", new CStringTypeManager(xfloat(), "*", struct_name), tab)
    {
        // Mark all math.h functions as generated...
        gFunctionSymbolTable["abs"] = true;

        gFunctionSymbolTable["min_i"] = true;
        gFunctionSymbolTable["max_i"] = true;
    
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
    
        // Fx version
        gFunctionSymbolTable["fabsfx"]      = true;
        gFunctionSymbolTable["acosfx"]      = true;
        gFunctionSymbolTable["asinfx"]      = true;
        gFunctionSymbolTable["atanfx"]      = true;
        gFunctionSymbolTable["atan2fx"]     = true;
        gFunctionSymbolTable["ceilfx"]      = true;
        gFunctionSymbolTable["cosfx"]       = true;
        gFunctionSymbolTable["expfx"]       = true;
        gFunctionSymbolTable["exp10fx"]     = true;
        gFunctionSymbolTable["floorfx"]     = true;
        gFunctionSymbolTable["fmodfx"]      = true;
        gFunctionSymbolTable["logfx"]       = true;
        gFunctionSymbolTable["log10fx"]     = true;
        gFunctionSymbolTable["powfx"]       = true;
        gFunctionSymbolTable["remainderfx"] = true;
        gFunctionSymbolTable["rintfx"]      = true;
        gFunctionSymbolTable["roundfx"]     = true;
        gFunctionSymbolTable["sinfx"]       = true;
        gFunctionSymbolTable["sqrtfx"]      = true;
        gFunctionSymbolTable["tanfx"]       = true;
        
        // Polymath mapping int version
        fPolyMathLibTable["min_i"] = "min";
        fPolyMathLibTable["max_i"] = "max";
        
        // Polymath mapping float version
        fPolyMathLibTable["min_f"]  = "fminf";
        fPolyMathLibTable["max_f"]  = "fmaxf";
        
        // Polymath mapping double version
        fPolyMathLibTable["min_"]   = "fmin";
        fPolyMathLibTable["max_"]   = "fmax";
        
        // Polymath mapping quad version
        fPolyMathLibTable["min_l"]  = "fminl";
        fPolyMathLibTable["max_l"]  = "fmaxl";
    
        // Polymath mapping fx version
        fPolyMathLibTable["min_fx"]  = "fminfx";
        fPolyMathLibTable["max_fx"]  = "fmaxfx";
    }

    virtual ~CInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        // Special case
        if (inst->fZone == "0") {
            *fOut << "ui_interface->declare(ui_interface->uiInterface, " << inst->fZone << ", " << quote(inst->fKey)
                  << ", " << quote(inst->fValue) << ")";
        } else {
            *fOut << "ui_interface->declare(ui_interface->uiInterface, &dsp->" << inst->fZone << ", "
                  << quote(inst->fKey) << ", " << quote(inst->fValue) << ")";
        }
        EndLine();
    }

    virtual void visit(OpenboxInst* inst)
    {
        std::string name;
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                name = "ui_interface->openVerticalBox(";
                break;
            case OpenboxInst::kHorizontalBox:
                name = "ui_interface->openHorizontalBox(";
                break;
            case OpenboxInst::kTabBox:
                name = "ui_interface->openTabBox(";
                break;
        }
        *fOut << name << "ui_interface->uiInterface, " << quote(inst->fName) << ")";
        EndLine();
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "ui_interface->closeBox(ui_interface->uiInterface);";
        tab(fTab, *fOut);
    }
    
    virtual void visit(AddButtonInst* inst)
    {
        std::string name;
        if (inst->fType == AddButtonInst::kDefaultButton) {
            name = "ui_interface->addButton(";
        } else {
            name = "ui_interface->addCheckButton(";
        }
        *fOut << name << "ui_interface->uiInterface, " << quote(inst->fLabel) << ", &dsp->" << inst->fZone << ")";
        EndLine();
    }

    virtual void visit(AddSliderInst* inst)
    {
        std::string name;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                name = "ui_interface->addHorizontalSlider(";
                break;
            case AddSliderInst::kVertical:
                name = "ui_interface->addVerticalSlider(";
                break;
            case AddSliderInst::kNumEntry:
                name = "ui_interface->addNumEntry(";
                break;
        }
        *fOut << name << "ui_interface->uiInterface, " << quote(inst->fLabel) << ", &dsp->" << inst->fZone << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fInit)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMin)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMax)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fStep)) << ")";
        EndLine();
    }

    virtual void visit(AddBargraphInst* inst)
    {
        std::string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "ui_interface->addHorizontalBargraph(";
                break;
            case AddBargraphInst::kVertical:
                name = "ui_interface->addVerticalBargraph(";
                break;
        }
        *fOut << name << "ui_interface->uiInterface, " << quote(inst->fLabel) << ", &dsp->" << inst->fZone << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMin)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMax)) << ")";
        EndLine();
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "ui_interface->addSoundfile(ui_interface->uiInterface, " << quote(inst->fLabel) << ", "
              << quote(inst->fURL) << ", &dsp->" << inst->fSFZone << ")";
        EndLine();
    }

    virtual void visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
            *fOut << "static ";
        }

        if (inst->fAddress->getAccess() & Address::kVolatile) {
            *fOut << "volatile ";
        }

        *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
        if (inst->fValue) {
            *fOut << " = ";
            inst->fValue->accept(this);
        }
        EndLine();
    }

    virtual void visit(DeclareFunInst* inst)
    {
        // Already generated
        if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
            return;
        } else {
            gFunctionSymbolTable[inst->fName] = true;
        }

        // Defined as macro in the architecture file...
        if (checkMinMax(inst->fName)) {
            return;
        }

        // Prototype
        if (inst->fType->fAttribute & FunTyped::kInline) {
            *fOut << "inline ";
        }

        if (inst->fType->fAttribute & FunTyped::kLocal || inst->fType->fAttribute & FunTyped::kStatic) {
            *fOut << "static ";
        }

        *fOut << fTypeManager->generateType(inst->fType->fResult, inst->fName);
        generateFunDefArgs(inst);
        generateFunDefBody(inst);
    }
    
    virtual void generateFunDefArgs(DeclareFunInst* inst)
    {
        *fOut << "(";
        
        size_t size = inst->fType->fArgsTypes.size(), i = 0;
        for (const auto& it : inst->fType->fArgsTypes) {
            // Pointers are set with 'noalias' for non paired arguments, which are garantied to be unique
            // TODO: better associate a proper kNoalias atribute at FIR creation time
            if (isPtrType(it->getType()) && !inst->fType->isPairedFunArg(it->fName)) {
                *fOut << fTypeManager->generateType(it, NamedTyped::kNoalias);
            } else {
                *fOut << fTypeManager->generateType(it);
            }
            if (i++ < size - 1) *fOut << ", ";
        }
    }

    virtual void visit(NamedAddress* named)
    {
        if (named->getAccess() & Address::kStruct) {
            *fOut << "dsp->";
        }
        *fOut << named->fName;
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        *fOut << "&";
        inst->fAddress->accept(this);
    }
    
    virtual void visit(BinopInst* inst)
    {
        // Special case for 'logical right-shift'
        if (strcmp(gBinOpTable[inst->fOpcode]->fName, ">>>") == 0) {
            Typed::VarType type = TypingVisitor::getType(inst->fInst1);
            if (isInt64Type(type)) {
                *fOut << "((int64_t)((uint64_t)";
            } else if (isInt32Type(type)) {
                *fOut << "((int32_t)(uint32_t)";
            } else {
                faustassert(false);
            }
            inst->fInst1->accept(this);
            *fOut << " >> ";
            inst->fInst2->accept(this);
            *fOut << "))";
        } else {
            TextInstVisitor::visit(inst);
        }
    }
    virtual void visit(FixedPointNumInst* inst) { *fOut << "(fixpoint_t)" << checkFloat(inst->fNum); }
    
    virtual void visit(FixedPointArrayNumInst* inst)
    {
        char sep = '{';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << "(fixpoint_t)" << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << '}';
    }

    virtual void visit(::CastInst* inst)
    {
        *fOut << "(" << fTypeManager->generateType(inst->fType) << ")(";
        inst->fInst->accept(this);
        *fOut << ")";
    }

    // TODO : does not work, put this code in a function
    virtual void visit(BitcastInst* inst)
    {
        switch (inst->fType->getType()) {
            case Typed::kInt32:
                *fOut << "*((int*)&";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kInt64:
                *fOut << "*((int64_t*)&";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kFloat:
                *fOut << "*((float*)&";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kDouble:
                *fOut << "*((double*)&";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            default:
                faustassert(false);
                break;
        }
    }

    // Generate standard funcall (not 'method' like funcall...)
    virtual void visit(FunCallInst* inst)
    {
        std::string name = (fPolyMathLibTable.find(inst->fName) != fPolyMathLibTable.end()) ? fPolyMathLibTable[inst->fName] : inst->fName;
        *fOut << gGlobal->getMathFunction(name) << "(";

        // Compile parameters
        generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
        *fOut << ")";
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;

        DeclareVarInst* c99_declare_inst = dynamic_cast<DeclareVarInst*>(inst->fInit);
        StoreVarInst*   c99_init_inst    = nullptr;

        if (c99_declare_inst) {
            InstBuilder::genLabelInst("/* C99 loop */")->accept(this);
            *fOut << "{";
            fTab++;
            tab(fTab, *fOut);

            // To generate C99 compatible loops...
            c99_init_inst    = InstBuilder::genStoreStackVar(c99_declare_inst->getName(), c99_declare_inst->fValue);
            c99_declare_inst = InstBuilder::genDecStackVar(c99_declare_inst->getName(), InstBuilder::genInt32Typed());
            // C99 loop variable declared outside the loop
            c99_declare_inst->accept(this);
        }

        if (gGlobal->gClang && !inst->fIsRecursive) {
            *fOut << "#pragma clang loop vectorize(enable) interleave(enable)";
            tab(fTab, *fOut);
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
        back(1, *fOut);
        *fOut << "}";
        tab(fTab, *fOut);

        if (c99_declare_inst) {
            fTab--;
            back(1, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
        }
    }

    static void cleanup() { gFunctionSymbolTable.clear(); }
};

/**
 Implement C FIR visitor: used for -os1 mode (TODO : does not work with 'soundfile').
 */

class CInstVisitor1 : public CInstVisitor {
    
    private:
    
        // Fields are moved in iZone/fZone model
        StructInstVisitor fStructVisitor;
    
    public:
    
        CInstVisitor1(std::ostream* out, const std::string& structname, int tab = 0)
        :CInstVisitor(out, structname, tab)
        {}
    
        virtual void visit(AddSoundfileInst* inst)
        {
            // Not supported for now
            throw faustexception("ERROR : AddSoundfileInst not supported for -os1 mode\n");
        }
    
        virtual void visit(DeclareVarInst* inst)
        {
            Address::AccessType access = inst->fAddress->getAccess();
            std::string name = inst->fAddress->getName();
            if (((access & Address::kStruct) || (access & Address::kStaticStruct)) && !isControl(name)) {
                fStructVisitor.visit(inst);
            } else {
                CInstVisitor::visit(inst);
            }
        }
    
        virtual void visit(NamedAddress* named)
        {
            Typed::VarType type;
            std::string name = named->getName();
            
            if (fStructVisitor.hasField(name, type)) {
                if (type == Typed::kInt32) {
                    FIRIndex value = FIRIndex(fStructVisitor.getFieldIntOffset(name)/sizeof(int));
                    InstBuilder::genIndexedFunArgsAddress("iZone", value)->accept(this);
                } else {
                    FIRIndex value = FIRIndex(fStructVisitor.getFieldRealOffset(name)/ifloatsize());
                    InstBuilder::genIndexedFunArgsAddress("fZone", value)->accept(this);
                }
            } else {
                CInstVisitor::visit(named);
            }
        }
    
        virtual void visit(IndexedAddress* indexed)
        {
            Typed::VarType type;
            std::string name = indexed->getName();
            
            if (fStructVisitor.hasField(name, type)) {
                if (type == Typed::kInt32) {
                    FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldIntOffset(name)/sizeof(int);
                    InstBuilder::genIndexedFunArgsAddress("iZone", value)->accept(this);
                } else {
                    FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldRealOffset(name)/ifloatsize();
                    InstBuilder::genIndexedFunArgsAddress("fZone", value)->accept(this);
                }
            } else {
                CInstVisitor::visit(indexed);
            }
        }
    
        // Size is expressed in unit of the actual type (so 'int' or 'float/double')
        int getIntZoneSize() { return fStructVisitor.getStructIntSize()/sizeof(int); }
        int getRealZoneSize() { return fStructVisitor.getStructRealSize()/ifloatsize(); }
   
};

/**
 Implement C FIR visitor: used for -os2 and -os3 modes, accessing iZone/fZone.
 */

class CInstVisitor2 : public CInstVisitor {
    
    protected:
        
        // Fields are distributed between the DSP struct and iZone/fZone arrays
        StructInstVisitor1 fStructVisitor;
    
        Address::AccessType fAccess;
         
    public:
        
        CInstVisitor2(std::ostream* out, const std::string& structname, int external_memory, Address::AccessType access, int tab = 0)
        :CInstVisitor(out, structname, tab), fStructVisitor(external_memory, 4), fAccess(access)
        {}
        
        virtual void visit(DeclareVarInst* inst)
        {
            Address::AccessType access = inst->fAddress->getAccess();
            std::string name = inst->fAddress->getName();
            if (((access & Address::kStruct) || (access & Address::kStaticStruct)) && !isControl(name)) {
                // Separate access between kLocal and kExternal
                fStructVisitor.visit(inst);
                // Local fields have to be generated
                if (fStructVisitor.getFieldMemoryType(name) == MemoryDesc::kLocal) {
                    CInstVisitor::visit(inst);
                }
            } else {
                CInstVisitor::visit(inst);
            }
        }
        
        virtual void visit(IndexedAddress* indexed)
        {
            Typed::VarType type;
            std::string name = indexed->getName();
            
            if (fStructVisitor.hasField(name, type) && fStructVisitor.getFieldMemoryType(name) == MemoryDesc::kExternal) {
                if (type == Typed::kInt32) {
                    FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldIntOffset(name)/sizeof(int);
                    InstBuilder::genIndexedAddress("iZone", fAccess, value)->accept(this);
                } else {
                    FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldRealOffset(name)/ifloatsize();
                    InstBuilder::genIndexedAddress("fZone", fAccess, value)->accept(this);
                }
            } else {
                CInstVisitor::visit(indexed);
            }
        }
      
        // Size is expressed in unit of the actual type (so 'int' or 'float/double')
        int getIntZoneSize() { return fStructVisitor.getStructIntSize()/sizeof(int); }
        int getRealZoneSize() { return fStructVisitor.getStructRealSize()/ifloatsize(); }
    
};

#endif
