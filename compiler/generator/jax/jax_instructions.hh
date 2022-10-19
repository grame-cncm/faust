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
            *fOut << "np.zeros((" << array_type->fSize << ",), dtype=np.int32)";
        } else if (isFloatType(typed->getType())) {
            *fOut << "np.zeros((" << array_type->fSize << ",), dtype=np.float32)";
        } else {
            *fOut << "np.zeros((" << array_type->fSize << ",), dtype=np.float64)";
        }
    }
    
    // Needed for waveforms
    virtual void visit(Int32ArrayNumInst* inst)
    {
        *fOut << "np.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << "], dtype=np.int32)";
    }
    
    virtual void visit(FloatArrayNumInst* inst)
    {
        *fOut << "np.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=np.float32)";
    }
    
    virtual void visit(DoubleArrayNumInst* inst)
    {
        *fOut << "np.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=np.float64)";
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
        
    // bool for "is storing left-hand-side".
    // Suppose the output code will be `state['foo'] = bar`.
    // This boolean indicates that we are starting this line but haven't yet reached the equals sign.
    bool fIsStoringLhs = false; 

    // bool for "will set array".
    // jax has a special syntax for setting items of arrays:
    // https://jax.readthedocs.io/en/latest/_autosummary/jax.numpy.ndarray.at.html
    // This bool helps us know that we're going to use the .at[X] operator followed by the set(Y) operator.
    // This bool is used in tandem with fIsStoringLhs.
    bool fWillSetArray = false;

    // This bool is not related to fIsStoringLhs or fWillSetArray.
    // It is used so that we don't cast to integers in the condition of a while (cond) loop.
    bool fIsDoingWhile = false;

    std::set<std::string> fLogSet;  // set of widget zone having a log UI scale
    std::set<std::string> fExpSet;  // set of widget zone having an exp UI scale
   
   public:
    using TextInstVisitor::visit;

    // This bool indicates that we should use the numpy functions, so the prefix "np."
    // If false, use jax.numpy "jnp."
    // We want to use numpy when initializing arrays and sound files because it's faster than JAX.
    bool fUseNumpy = true;

    JAXInstVisitor(std::ostream* out, const string& struct_name, int tab = 0)
        : TextInstVisitor(out, ".", new JAXStringTypeManager(xfloat(), "*", struct_name), tab)
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
        gFunctionSymbolTable["exp10f"]     = false;
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
        gFunctionSymbolTable["exp10"]     = false;
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
        gFunctionSymbolTable["exp10l"]     = false;
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
        gPolyMathLibTable["exp10f"]     = "jnp.exp10f";
        gPolyMathLibTable["floorf"]     = "jnp.floor";
        gPolyMathLibTable["fmodf"]      = "jnp.mod";
        gPolyMathLibTable["logf"]       = "jnp.log";
        gPolyMathLibTable["log2f"]      = "jnp.log2";
        gPolyMathLibTable["log10f"]     = "jnp.log10";
        gPolyMathLibTable["powf"]       = "jnp.power";
        gPolyMathLibTable["remainderf"] = "remainder";  // todo: we currently rely on a custom remainder implementation in the architecture file.
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
        gPolyMathLibTable["atan2"]     = "jnp.arctan2";
        gPolyMathLibTable["ceil"]      = "jnp.ceil";
        gPolyMathLibTable["cos"]       = "jnp.cos";
        gPolyMathLibTable["exp"]       = "jnp.exp";
        gPolyMathLibTable["exp2"]      = "jnp.exp2";
        gPolyMathLibTable["exp10"]     = "jnp.exp10";
        gPolyMathLibTable["floor"]     = "jnp.floor";
        gPolyMathLibTable["fmod"]      = "jnp.mod";
        gPolyMathLibTable["log"]       = "jnp.log";
        gPolyMathLibTable["log2"]      = "jnp.log2";
        gPolyMathLibTable["log10"]     = "jnp.log10";
        gPolyMathLibTable["pow"]       = "jnp.power";
        gPolyMathLibTable["remainder"] = "remainder"; // todo: we currently rely on a custom remainder implementation in the architecture file.
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

    virtual void visit(OpenboxInst* inst)
    {
        *fOut << "ui_path.append(" << quote(inst->fName) << ")";
        EndLine(' ');
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "ui_path.pop()";
        tab(fTab, *fOut);
    }
    
    virtual void visit(AddButtonInst* inst)
    {
        *fOut << "self.add_button(state, " << quote(inst->fZone) << ", ui_path," << quote(inst->fLabel) << ")";
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

        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
            case AddSliderInst::kVertical:
                // clang-format off
                *fOut << "self.add_slider(state, " 
                    << quote(inst->fZone) << ", ui_path, "
                    << quote(inst->fLabel) << ", "
                    << checkReal(inst->fInit) << ", "
                    << checkReal(inst->fMin) << ", "
                    << checkReal(inst->fMax) << ", "
                    << scaleMode << ")";
                break;
                // clang-format on
            case AddSliderInst::kNumEntry:
                // clang-format off
                *fOut << "self.add_nentry(state, " 
                    << quote(inst->fZone) << ", ui_path, "
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
        *fOut << "state[" + quote(inst->fZone) + "] = 0.";
        EndLine(' ');
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "self.add_soundfile(state, " << quote(inst->fSFZone) << ", ui_path, " << quote(inst->fLabel) << ", " << quote(inst->fURL) << ", x)";
        EndLine(' ');
    }

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

            bool opCodeIsBoolean = inst->fOpcode >= kGT && inst->fOpcode <= kXOR;
            if (opCodeIsBoolean && !fIsDoingWhile) {
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
        if (fUseNumpy) {

            indexed->fAddress->accept(this);
            DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
            if (struct_type) {
                Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->getIndex());
                *fOut << "[\"" << struct_type->fType->getName(field_index->fNum) << "\"]";
            } else {
                Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(indexed->getIndex());
                if (field_index) {
                    *fOut << "[" << field_index->fNum << "]";
                } else {
                    *fOut << "[";
                    indexed->getIndex()->accept(this);
                    *fOut << "]";
                }
            }
        
        } else {
        
            indexed->fAddress->accept(this);
            DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
            if (struct_type) {
                Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->getIndex());
                *fOut << "[\"" << struct_type->fType->getName(field_index->fNum) << "\"]";
            } else {
                if (fIsStoringLhs) {
                    fWillSetArray = true;
                    return;
                }

                if (fWillSetArray) {
                    *fOut << ".at";
                    fWillSetArray = false;
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
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        faustassert(false);
    }
    
    virtual void visit(StoreVarInst* inst)
    {
        fIsStoringLhs = true;
        inst->fAddress->accept(this);
        fIsStoringLhs = false;
        *fOut << " = ";

        if (fWillSetArray) {
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
            *fOut << "jnp.int32(";
            inst->fInst->accept(this);
            *fOut << ")";
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
        if (fUseNumpy && name.rfind("jnp.") == 0) {
            // turn "jnp." into "np."
            name = name.substr(1, name.size() - 1);
        }
        *fOut << name << "(";
        // Compile parameters
        generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
        *fOut << ")";
    }
    
    virtual void visit(IfInst* inst)
    {
        *fOut << "if ";
        visitCond(inst->fCond);
        *fOut << ":";
        fTab++;
        tab(fTab, *fOut);
        inst->fThen->accept(this);
        fTab--;
        back(1, *fOut);
        if (inst->fElse->fCode.size() > 0) {
            *fOut << "else:";
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

        fIsDoingWhile = true;

        fFinishLine = false;
        inst->fInit->accept(this);
        tab(fTab, *fOut);
        *fOut << "while ";
        inst->fEnd->accept(this);
        fIsDoingWhile = false;
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
                *fOut << "range(" << lower_bound->fNum << ", " << upper_bound->fNum;

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
