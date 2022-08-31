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

#ifndef _JAX_INSTRUCTIONS_H
#define _JAX_INSTRUCTIONS_H

#include <string>

#include "text_instructions.hh"
#include "struct_manager.hh"

using namespace std;

// Visitor used to initialize array fields into the DSP structure
struct JAXInitFieldsVisitor : public DispatchVisitor {
    std::ostream* fOut;
    int           fTab;
    
    JAXInitFieldsVisitor(std::ostream* out, int tab = 0) : fOut(out), fTab(tab) {}
    
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
            *fOut << "state[\"";
        }
        *fOut << named->fName;
        if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
            *fOut << "\"]";
        }
    }
    
    static void ZeroInitializer(std::ostream* fOut, Typed* typed)
    {
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(typed);
        faustassert(array_type);
        if (isIntPtrType(typed->getType())) {
            *fOut << "jnp.zeros((" << array_type->fSize << ",), dtype=jnp.int32)";
        } else if (isFloatType(typed->getType())) {
            *fOut << "jnp.zeros((" << array_type->fSize << ",), dtype=jnp.float32)";
        } else {
            *fOut << "jnp.zeros((" << array_type->fSize << ",), dtype=jnp.float32)";  // todo: maybe should be jnp.float64
        }
    }
    
    // Needed for waveforms
    
    virtual void visit(Int32ArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << "], dtype=jnp.int32)";
    }
    
    virtual void visit(FloatArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=jnp.float32)";
    }
    
    virtual void visit(DoubleArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=jnp.float64)";
    }
    
};

class JAXInstVisitor : public TextInstVisitor {
   private:
     
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static map<string, bool> gFunctionSymbolTable;

    // Polymorphic math functions
    map<string, string> gPolyMathLibTable;
    
    bool fMutateFun;
    bool is_storing_lhs = false;
    bool will_set_array = false;

    std::set<std::string> fLogSet;  // set of widget zone having a log UI scale
    std::set<std::string> fExpSet;  // set of widget zone having an exp UI scale
    
    string cast2FAUSTFLOAT(const string& str) { return "FAUSTFLOAT(" + str + ")"; }
    
   public:
    using TextInstVisitor::visit;

    JAXInstVisitor(std::ostream* out, const string& struct_name, int tab = 0, bool mutate_fun = false)
        : TextInstVisitor(out, ".", new JAXStringTypeManager(xfloat(), "*", struct_name), tab), fMutateFun(mutate_fun)
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
        gPolyMathLibTable["abs"]   = "jnp.abs";
        gPolyMathLibTable["max_i"] = "jnp.maximum";
        gPolyMathLibTable["min_i"] = "jnp.minimum";

        // Polymath mapping float version
        gPolyMathLibTable["max_f"] = "jnp.maximum";
        gPolyMathLibTable["min_f"] = "jnp.minimum";

        gPolyMathLibTable["fabsf"]      = "jnp.abs";
        gPolyMathLibTable["acosf"]      = "jnp.arccos";
        gPolyMathLibTable["asinf"]      = "jnp.arcsin";
        gPolyMathLibTable["atanf"]      = "jnp.arctan";
        gPolyMathLibTable["atan2f"]     = "jnp.arctan2";
        gPolyMathLibTable["ceilf"]      = "jnp.ceil";
        gPolyMathLibTable["cosf"]       = "jnp.cos";
        gPolyMathLibTable["expf"]       = "jnp.exp";
        gPolyMathLibTable["exp2f"]      = "jnp.exp2";
        gPolyMathLibTable["exp10f"]     = "jnp.exp10f";  // todo:
        gPolyMathLibTable["floorf"]     = "jnp.floor";
        gPolyMathLibTable["fmodf"]      = "jnp.mod";
        gPolyMathLibTable["logf"]       = "jnp.log";
        gPolyMathLibTable["log2f"]      = "jnp.log2";
        gPolyMathLibTable["log10f"]     = "jnp.log10";
        gPolyMathLibTable["powf"]       = "jnp.power";
        gPolyMathLibTable["remainderf"] = "jnp.remainder";
        gPolyMathLibTable["rintf"]      = "jnp.rint";
        gPolyMathLibTable["roundf"]     = "jnp.round";
        gPolyMathLibTable["sinf"]       = "jnp.sin";
        gPolyMathLibTable["sqrtf"]      = "jnp.sqrt";
        gPolyMathLibTable["tanf"]       = "jnp.tan";
                             
        // Hyperbolic
        gPolyMathLibTable["acoshf"]     = "jnp.arccosh";
        gPolyMathLibTable["asinhf"]     = "jnp.arcsinh";
        gPolyMathLibTable["atanhf"]     = "jnp.arctanh";
        gPolyMathLibTable["coshf"]      = "jnp.cosh";
        gPolyMathLibTable["sinhf"]      = "jnp.sinh";
        gPolyMathLibTable["tanhf"]      = "jnp.tanh";
    
        gPolyMathLibTable["isnanf"]     = "jnp.isnan";
        gPolyMathLibTable["isinff"]     = "jnp.isinf";
        gPolyMathLibTable["copysignf"]  = "jnp.copysign";
        
        // Polymath mapping double version
        gPolyMathLibTable["max_"] = "jnp.maximum";
        gPolyMathLibTable["min_"] = "jnp.minimum";

        gPolyMathLibTable["fabs"]      = "jnp.abs";
        gPolyMathLibTable["acos"]      = "jnp.arccos";
        gPolyMathLibTable["asin"]      = "jnp.arcsin";
        gPolyMathLibTable["atan"]      = "jnp.arctan";
        gPolyMathLibTable["atan2"]     = "jnp.arctan";
        gPolyMathLibTable["ceil"]      = "jnp.ceil";
        gPolyMathLibTable["cos"]       = "jnp.cos";
        gPolyMathLibTable["exp"]       = "jnp.exp";
        gPolyMathLibTable["exp2"]      = "jnp.exp2";
        gPolyMathLibTable["exp10"]     = "jnp.exp10";  // todo:
        gPolyMathLibTable["floor"]     = "jnp.floor";
        gPolyMathLibTable["fmod"]      = "jnp.mod";
        gPolyMathLibTable["log"]       = "jnp.log";
        gPolyMathLibTable["log2"]      = "jnp.log2";
        gPolyMathLibTable["log10"]     = "jnp.log10";
        gPolyMathLibTable["pow"]       = "jnp.power";
        gPolyMathLibTable["remainder"] = "jnp.remainder";
        gPolyMathLibTable["rint"]      = "jnp.rint";
        gPolyMathLibTable["round"]     = "jnp.round";
        gPolyMathLibTable["sin"]       = "jnp.sin";
        gPolyMathLibTable["sqrt"]      = "jnp.sqrt";
        gPolyMathLibTable["tan"]       = "jnp.tan";
    
        // Hyperbolic
        gPolyMathLibTable["acosh"]     = "jnp.arccosh";
        gPolyMathLibTable["asinh"]     = "jnp.arcsinh";
        gPolyMathLibTable["atanh"]     = "jnp.arctanh";
        gPolyMathLibTable["cosh"]      = "jnp.cosh";
        gPolyMathLibTable["sinh"]      = "jnp.sinh";
        gPolyMathLibTable["tanh"]      = "jnp.tanh";

        gPolyMathLibTable["isnan"]     = "jnp.isnan";
        gPolyMathLibTable["isinf"]     = "jnp.isinf";
        gPolyMathLibTable["copysign"]  = "jnp.copysign";
    }

    virtual ~JAXInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        if (inst->fKey == "scale") {
            if (inst->fValue == "exp") {
                fExpSet.emplace(inst->fZone);
            } else if (inst->fValue == "log") {
                fLogSet.emplace(inst->fZone);
            } else {
				// it's linear by default
			}
		}
    }

    virtual void visit(OpenboxInst* inst) {}

    virtual void visit(CloseboxInst* inst) {}
    
    virtual void visit(AddButtonInst* inst)
    {
        *fOut << "state[\"" << inst->fZone << "\"] = ";
        *fOut << "self.add_button(" << quote(inst->fLabel) << ")";
        EndLine(' ');
    }

    virtual void visit(AddSliderInst* inst)
    {
        std::string scaleMode = "";
        if (fExpSet.count(inst->fZone)) {
            scaleMode = "\"exp\"";
        } else if (fLogSet.count(inst->fZone)) {
            scaleMode = "\"log\"";
        } else {
            scaleMode = "\"linear\"";
		}

        *fOut << "state[\"" << inst->fZone << "\"] = ";
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
            case AddSliderInst::kVertical:
				// clang-format off
                *fOut << "self.add_slider(" 
					//<< quote(inst->fZone) << ", "
					<< quote(inst->fLabel) << ", "
					<< checkReal(inst->fInit) << ", "
					<< checkReal(inst->fMin) << ", "
					<< checkReal(inst->fMax) << ", "
					<< scaleMode << ")";
                break;
				// clang-format on
            case AddSliderInst::kNumEntry:
                // clang-format off
                *fOut << "self.add_nentry(" 
					//<< quote(inst->fZone) << ", "
					<< quote(inst->fLabel) << ", "
					<< checkReal(inst->fInit) << ", "
					<< checkReal(inst->fMin) << ", "
					<< checkReal(inst->fMax) << ", "
					<< checkReal(inst->fStep) << ")";
                break;
                // clang-format on
        }
        EndLine(' ');
    }

    virtual void visit(AddBargraphInst* inst)
    {
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                *fOut << "ui_interface.addHorizontalBargraph(";
                break;
            case AddBargraphInst::kVertical:
                *fOut << "ui_interface.addVerticalBargraph(";
                break;
        }
        // todo: fix this
        *fOut << quote(inst->fLabel) << ", self." << inst->fZone << ", "
              << checkReal(inst->fMin) << ", "
              << checkReal(inst->fMax) << ")";
        EndLine(' ');
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "self.add_soundfile(state, x, " << quote(inst->fLabel) << ", " << quote(inst->fURL) << ", " << quote(inst->fSFZone)
              << ")";
        EndLine(' ');
    }
    
    // virtual void visit(Int32NumInst* inst) { *fOut << "jnp.array([" << inst->fNum << "], dtype=jnp.int32)"; }
    
    // virtual void visit(Int64NumInst* inst) { *fOut << "jnp.array([" << inst->fNum << "], dtype=jnp.int64)"; }

    virtual void visit(Int32NumInst* inst) { *fOut << inst->fNum; }
    
    virtual void visit(Int64NumInst* inst) { *fOut << inst->fNum; }
    
    virtual void visit(Int32ArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << "], dtype=jnp.int32)";
    }
    
    virtual void visit(FloatArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=jnp.float32)";
    }
    
    virtual void visit(DoubleArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=jnp.float64)";
    }
    
    virtual void visit(BinopInst* inst)
    {
        if (inst->fOpcode == kXOR) {
            *fOut << "(";
            inst->fInst1->accept(this);
            *fOut << " ^ ";
             inst->fInst2->accept(this);
            *fOut << ")";
        } else {
            // Operator prededence is not like C/C++, so for simplicity, we keep the fully parenthezid version
            *fOut << "(";
            inst->fInst1->accept(this);
            *fOut << " ";
            *fOut << gBinOpTable[inst->fOpcode]->fName;
            *fOut << " ";
            inst->fInst2->accept(this);
            *fOut << ")";

			if (inst->fOpcode > 7) {
                // these opcodes (>,>=,<,<= etc.) result in bools which should be re-cast to integers
                *fOut << ".astype(jnp.int32)";
			}
        }
    }
   
    virtual void visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
            *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
            // Allocation is actually done in JAXInitFieldsVisitor
        } else {
            *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
            if (inst->fValue) {
                *fOut << " = ";
                inst->fValue->accept(this);
            }
        }
        EndLine(' ');
    }

    // virtual void visit(RetInst* inst)
    // {
    //     *fOut << "return ";
    //     if (inst->fResult) {
    //         inst->fResult->accept(this);
    //     } else {
    //         *fOut << "output0";
    //     }
    //     EndLine();
    // }

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
        
        *fOut << "def " << inst->fName;
        generateFunDefArgs(inst);
        generateFunDefBody(inst);

    }
    
    virtual void visit(DeclareBufferIterators* inst)
    {
        // Don't generate if no channels
        if (inst->fChannels == 0) return;
    
        for (int i = 0; i < inst->fChannels; ++i) {
            *fOut << inst->fBufferName1 << i << " = " << inst->fBufferName2 << "[ " << i << ":" << i+1 << ",:]";
            tab(fTab, *fOut);
        }
    }
    
    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        if (inst->fCode->fCode.size() == 0) {
            *fOut << "):";
            fTab++;
            tab(fTab, *fOut);
            *fOut << "pass";
            fTab--;
            tab(fTab, *fOut);
            tab(fTab, *fOut);
        } else {
            // Function body
            *fOut << "):";
            fTab++;
            tab(fTab, *fOut);
            inst->fCode->accept(this);
            fTab--;
            back(1, *fOut);
            tab(fTab, *fOut);
        }
    }

    virtual void visit(NamedAddress* named)
    {
		//kStruct      1 // self.fHslider, self.fVec0
		//kStaticStruct = 0x2,  // Static shared variable between all DSPs
		//kFunArgs = 0x4,  self.sample_rate, self.inputs
		//kStack = 0x8,  fSlow0, fTemp0
		//kGlobal = 0x10,
		//kLink = 0x20,
		//kLoop = 0x40,
		//kVolatile = 0x80,
		//kReference   = 0x100,  // Access by reference (for Rust backend)
		//kMutable = 0x200,  // Mutable access (for Rust backend)
		//kConst   = 0x400   // Const access

        // kStaticStruct are actually merged in the main DSP
        if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
            *fOut << "state[\"";
        }
        *fOut << named->fName;
        if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
            *fOut << "\"]";
        }
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
            *fOut << "[\"" << struct_type->fType->getName(field_index->fNum) << "\"]";
        } else {

			if (is_storing_lhs) {
                *fOut << " ";
                will_set_array = true;
                return;
            }

			if (will_set_array) {
                *fOut << ".at";
                will_set_array = false;
			}
            
            Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(indexed->getIndex());
            if (field_index) {
                *fOut << "[" << field_index->fNum << "]";
            } else {
                *fOut << "[";
                indexed->getIndex()->accept(this);
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
        is_storing_lhs = true;
        inst->fAddress->accept(this);
        is_storing_lhs = false;
        *fOut << " = ";

		if (will_set_array) {
            inst->fAddress->accept(this);
            *fOut << ".set(";
            inst->fValue->accept(this);
            *fOut << ")";
        } else {
            inst->fValue->accept(this);
		}

        EndLine(' ');
    }
      
    virtual void visit(::CastInst* inst)
    {
        if (isIntType(inst->fType->getType())) {
            // todo: better casting?
            // fTypeManager->generateType(inst->fType) might be jnp.int32
            // *fOut << fTypeManager->generateType(inst->fType) << "(math.floor(";
            *fOut << "jnp.int32(jnp.floor(";
            inst->fInst->accept(this);
            *fOut << "))";
        } else {
            *fOut << fTypeManager->generateType(inst->fType) << "(";
            inst->fInst->accept(this);
            *fOut << ")";
        }
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
		*fOut << "jnp.where(";
        visitCond(inst->fCond);
        *fOut << ", ";
        inst->fThen->accept(this);
        *fOut << ", ";
         inst->fElse->accept(this);
        *fOut << ")";
    }

    // Generate standard funcall (not 'method' like funcall...)
    virtual void visit(FunCallInst* inst)
    {
        string name = (gPolyMathLibTable.find(inst->fName) != gPolyMathLibTable.end()) ? gPolyMathLibTable[inst->fName] : inst->fName;
        *fOut << name << "(";
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
            *fOut << "elif";
            fTab++;
            tab(fTab, *fOut);
            inst->fElse->accept(this);
            fTab--;
            back(1, *fOut);
        }
        tab(fTab, *fOut);
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;

        fFinishLine = false;
        inst->fInit->accept(this);
        tab(fTab, *fOut);
        *fOut << "while ";
        inst->fEnd->accept(this);
        *fOut << ":";
        tab(fTab, *fOut);
        fFinishLine = true;
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        tab(fTab, *fOut);
        inst->fIncrement->accept(this);
        fTab--;
        back(1, *fOut);
        tab(fTab, *fOut);
    }
    
    virtual void visit(SimpleForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;
        
        *fOut << "for " << inst->getName() << " in ";
    
        if (inst->fReverse) {
            // todo:
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
            Int32NumInst* upper_bound = dynamic_cast<Int32NumInst*>(inst->fUpperBound);

            if (upper_bound) {
                *fOut << "range(" << lower_bound->fNum << ", " << upper_bound->fNum-1;

                if (upper_bound->fNum <= lower_bound->fNum) {
                    *fOut << ", -1";
                }
            } else {
                *fOut << "range(" << lower_bound->fNum << ", ";
                inst->fUpperBound->accept(this);
            }

            *fOut << "):";
        }

        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
        back(1, *fOut);
        tab(fTab, *fOut);
    }
    
    static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif
