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
            if (isIntPtrType(inst->fType->getType())) {
                *fOut << inst->fAddress->getName() << " = zeros(Int32, " << array_type->fSize << ")";
            } else {
                *fOut << inst->fAddress->getName() << " = zeros(T, " << array_type->fSize << ")";
            }
        }
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
    
   public:
    using TextInstVisitor::visit;

    JuliaInstVisitor(std::ostream* out, const string& struct_name, int tab = 0)
        : TextInstVisitor(out, ".", new JuliaStringTypeManager(xfloat(), "*", struct_name), tab)
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
   
        // Polymath mapping int version
        gPolyMathLibTable["abs"]   = "abs";
        gPolyMathLibTable["max_i"] = "max";
        gPolyMathLibTable["min_i"] = "min";

        // Polymath mapping float version
        gPolyMathLibTable["max_f"] = "max";
        gPolyMathLibTable["min_f"] = "min";

        gPolyMathLibTable["fabsf"]      = "fabs";
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

        // Polymath mapping double version
        gPolyMathLibTable["max_"] = "max";
        gPolyMathLibTable["min_"] = "min";

        gPolyMathLibTable["fabs"]      = "fabs";
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

        // Polymath mapping quad version
        gPolyMathLibTable["max_l"] = "max";
        gPolyMathLibTable["min_l"] = "min";

        gPolyMathLibTable["fabsl"]      = "fabs";
        gPolyMathLibTable["acosl"]      = "acos";
        gPolyMathLibTable["asinl"]      = "asin";
        gPolyMathLibTable["atanl"]      = "atan";
        gPolyMathLibTable["atan2l"]     = "atan2";
        gPolyMathLibTable["ceill"]      = "ceil";
        gPolyMathLibTable["cosl"]       = "cos";
        gPolyMathLibTable["expl"]       = "exp";
        gPolyMathLibTable["exp2l"]      = "exp2";
        gPolyMathLibTable["exp10l"]     = "exp10";
        gPolyMathLibTable["floorl"]     = "floor";
        gPolyMathLibTable["fmodl"]      = "fmod";
        gPolyMathLibTable["logl"]       = "log";
        gPolyMathLibTable["log2l"]      = "log2";
        gPolyMathLibTable["log10l"]     = "log10";
        gPolyMathLibTable["powl"]       = "pow";
        gPolyMathLibTable["remainderl"] = "remainder";
        gPolyMathLibTable["rintl"]      = "rint";
        gPolyMathLibTable["roundl"]     = "round";
        gPolyMathLibTable["sinl"]       = "sin";
        gPolyMathLibTable["sqrtl"]      = "sqrt";
        gPolyMathLibTable["tanl"]       = "tan";
    }

    virtual ~JuliaInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        
    }

    virtual void visit(OpenboxInst* inst)
    {
        
    }

    virtual void visit(CloseboxInst* inst)
    {
       
    }
    
    virtual void visit(AddButtonInst* inst)
    {
       
    }

    virtual void visit(AddSliderInst* inst)
    {
        
    }

    virtual void visit(AddBargraphInst* inst)
    {
        
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        
    }

    virtual void visit(DeclareVarInst* inst)
    {
        /*
        // TODO
        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
            *fOut << "static ";
        }

        if (inst->fAddress->getAccess() & Address::kVolatile) {
            *fOut << "volatile ";
        }
        */

        *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
        if (inst->fValue) {
            *fOut << " = ";
            inst->fValue->accept(this);
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
            *fOut << inst->fBufferName1 << i << " = @view " << inst->fBufferName2 << "[:, " << (i+1) << "]";
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
       if (named->getAccess() & Address::kStruct) {
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
            *fOut << "->" << struct_type->fType->getName(field_index->fNum);
        } else {
            *fOut << "[";
            Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(indexed->fIndex);
            if (field_index) {
                // Julia arrays start at 1
                *fOut << (field_index->fNum + 1) << "]";
            } else {
                indexed->fIndex->accept(this);
                *fOut << "]";
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
    
    /*
    virtual void visit(BinopInst* inst)
    {
       
    }
    */
    
    virtual void visit(::CastInst* inst)
    {
        string type = fTypeManager->generateType(inst->fType);
        if (endWith(type, "*")) {
            *fOut << "static_cast<" << type << ">(";
            inst->fInst->accept(this);
            *fOut << ")";
        } else {
            *fOut << type << "(";
            inst->fInst->accept(this);
            *fOut << ")";
        }
    }

    // TODO : does not work, put this code in a function
    virtual void visit(BitcastInst* inst)
    {
        
    }

    // Generate standard funcall (not 'method' like funcall...)
    
    virtual void visit(FunCallInst* inst)
    {
        string name = gGlobal->getMathFunction(inst->fName);
        name = (gPolyMathLibTable.find(name) != gPolyMathLibTable.end()) ? gPolyMathLibTable[name] : name;
        generateFunCall(inst, name);
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
        
        *fOut << "for " << inst->getName() << "::Int32 = ";
        if (inst->fReverse) {
            Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(inst->fUpperBound);
            faustassert(field_index);
            // Julia arrays start at 1
            *fOut << (field_index->fNum + 1) << ":";
            inst->fLowerBound->accept(this);
        } else {
            Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(inst->fLowerBound);
            faustassert(field_index);
            // Julia arrays start at 1
            *fOut << (field_index->fNum + 1) << ":";
            inst->fUpperBound->accept(this);
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

