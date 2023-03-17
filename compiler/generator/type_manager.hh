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

#ifndef _TYPE_MANAGER_H
#define _TYPE_MANAGER_H

#include <list>
#include <map>
#include <set>
#include <string>

#include "exception.hh"
#include "instructions.hh"

// Base class for type manager

struct StringTypeManager {
    std::map<Typed::VarType, std::string> fTypeDirectTable;
    std::string                           fPtrRef;

    StringTypeManager(const std::string& float_macro_name, const std::string& ptr_ref)
    {
        fTypeDirectTable[Typed::kFloatMacro]         = float_macro_name;
        fTypeDirectTable[Typed::kFloatMacro_ptr]     = float_macro_name + ptr_ref;
        fTypeDirectTable[Typed::kFloatMacro_ptr_ptr] = float_macro_name + ptr_ref + ptr_ref;
    }

    virtual ~StringTypeManager() {}

    virtual std::string generateType(Typed* type, NamedTyped::Attribute attr = NamedTyped::kDefault) = 0;
    virtual std::string generateType(Typed* type, const std::string& name) = 0;
};

// StringTypeManager for C/C++, Java and FIR backends

class CStringTypeManager : public StringTypeManager {
   public:
    CStringTypeManager(const std::string& float_macro_name, const std::string& ptr_ref, const std::string& struct_name = "")
        : StringTypeManager(float_macro_name, ptr_ref)
    {
        fPtrRef = ptr_ref;

        fTypeDirectTable[Typed::kInt32]     = "int";
        fTypeDirectTable[Typed::kInt32_ptr] = "int" + fPtrRef;
        fTypeDirectTable[Typed::kInt32_vec] = "vector<int>";

        fTypeDirectTable[Typed::kInt64]     = "int64_t";
        fTypeDirectTable[Typed::kInt64_ptr] = "int64_t" + fPtrRef;
        fTypeDirectTable[Typed::kInt64_vec] = "vector<int64_t>";

        fTypeDirectTable[Typed::kFloat]         = "float";
        fTypeDirectTable[Typed::kFloat_ptr]     = "float" + fPtrRef;
        fTypeDirectTable[Typed::kFloat_ptr_ptr] = "float" + fPtrRef + fPtrRef;
        fTypeDirectTable[Typed::kFloat_vec]     = "vector<float>";

        fTypeDirectTable[Typed::kDouble]         = "double";
        fTypeDirectTable[Typed::kDouble_ptr]     = "double" + fPtrRef;
        fTypeDirectTable[Typed::kDouble_ptr_ptr] = "double" + fPtrRef + fPtrRef;
        fTypeDirectTable[Typed::kDouble_vec]     = "vector<double>";

        fTypeDirectTable[Typed::kQuad]         = "quad";
        fTypeDirectTable[Typed::kQuad_ptr]     = "quad" + fPtrRef;
        fTypeDirectTable[Typed::kQuad_ptr_ptr] = "quad" + fPtrRef + fPtrRef;
        fTypeDirectTable[Typed::kQuad_vec]     = "vector<quad>";
        
        fTypeDirectTable[Typed::kFixedPoint]     = "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_ptr] = "fixpoint_t" + fPtrRef;
        fTypeDirectTable[Typed::kFixedPoint_ptr] = "fixpoint_t" + fPtrRef + fPtrRef;
        fTypeDirectTable[Typed::kFixedPoint_vec] = "vector<fixpoint_t>";

        fTypeDirectTable[Typed::kBool]     = "bool";
        fTypeDirectTable[Typed::kBool_ptr] = "bool" + fPtrRef;
        fTypeDirectTable[Typed::kBool_vec] = "vector<bool>";

        fTypeDirectTable[Typed::kVoid]     = "void";
        fTypeDirectTable[Typed::kVoid_ptr] = "void" + fPtrRef;

        fTypeDirectTable[Typed::kSound]     = "Soundfile";
        fTypeDirectTable[Typed::kSound_ptr] = "Soundfile" + fPtrRef;

        // DSP has to be empty here
        fTypeDirectTable[Typed::kObj]     = struct_name;
        fTypeDirectTable[Typed::kObj_ptr] = struct_name + fPtrRef;

        fTypeDirectTable[Typed::kUint_ptr] = "uintptr_t";
    }

    virtual std::string generateType(Typed* type, NamedTyped::Attribute attr = NamedTyped::kDefault)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        FixedTyped* fx_typed    = dynamic_cast<FixedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
        StructTyped* struct_typed = dynamic_cast<StructTyped*>(type);

        // fx_typed is a subclass of basic_typed, so has to be tested first
        if (fx_typed) {
            if (fx_typed->fIsSigned) {
                return "sfx_t(" + std::to_string(std::min<int>(20, std::abs(fx_typed->fMSB))) + "," + std::to_string(fx_typed->fLSB) + ")";
            } else {
                return "ufx_t(" + std::to_string(std::min<int>(20, std::abs(fx_typed->fMSB))) + "," + std::to_string(fx_typed->fLSB) + ")";
            }
        } else if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            return generateType(named_typed->fType) + NamedTyped::AttributeMap[attr] + named_typed->fName;
        } else if (array_typed) {
            return fTypeDirectTable[array_typed->getType()];
        } else if (struct_typed) {
            std::string res = "typedef struct " + struct_typed->fName + " { ";
            for (const auto& it : struct_typed->fFields) {
                res = res + generateType(it) + "; ";
            }
            res += "} " + struct_typed->fName + ";";
            return res;
        } else {
            faustassert(false);
            return "";
        }
    }

    virtual std::string generateType(Typed* type, const std::string& name)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        FixedTyped* fx_typed    = dynamic_cast<FixedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        // fx_typed is a subclass of basic_typed, so has to be tested first
        if (fx_typed) {
            if (fx_typed->fIsSigned) {
                return "sfx_t(" + std::to_string(std::min<int>(20, std::abs(fx_typed->fMSB))) + "," + std::to_string(fx_typed->fLSB) + ") " + name;
            } else {
                return "ufx_t(" + std::to_string(std::min<int>(20, std::abs(fx_typed->fMSB))) + "," + std::to_string(fx_typed->fLSB) + ") " + name;
            }
        } else if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType] + " " + name;
        } else if (named_typed) {
            return named_typed->fName + generateType(named_typed->fType) + " " + name;
        } else if (array_typed) {
            return (array_typed->fSize == 0)
                ? generateType(array_typed->fType) + fPtrRef + " " + name
                : generateType(array_typed->fType) + " " + name + "[" + std::to_string(array_typed->fSize) + "]";
        } else {
            faustassert(false);
            return "";
        }
    }
};

// StringTypeManager for Rust backend

class RustStringTypeManager : public StringTypeManager {
   public:
    RustStringTypeManager(const std::string& float_macro_name, const std::string& ptr_ref)
        : StringTypeManager(float_macro_name, ptr_ref)
    {
        fPtrRef = ptr_ref;

        fTypeDirectTable[Typed::kInt32]     = "i32";
        fTypeDirectTable[Typed::kInt32_ptr] = fPtrRef + "i32";
        fTypeDirectTable[Typed::kInt32_vec] = "vector<i32>";

        fTypeDirectTable[Typed::kInt64]     = "i64";
        fTypeDirectTable[Typed::kInt64_ptr] =  fPtrRef + "i64";
        fTypeDirectTable[Typed::kInt64_vec] = "vector<i64>";

        fTypeDirectTable[Typed::kFloat]     = "F32";
        fTypeDirectTable[Typed::kFloat_ptr] = fPtrRef + "F32";
        fTypeDirectTable[Typed::kFloat_ptr_ptr] =  fPtrRef + fPtrRef + "F32";
        fTypeDirectTable[Typed::kFloat_vec] = "vector<F32>";

        fTypeDirectTable[Typed::kDouble]     = "F64";
        fTypeDirectTable[Typed::kDouble_ptr] = fPtrRef + "F64";
        fTypeDirectTable[Typed::kDouble_ptr_ptr] = fPtrRef + fPtrRef + "F64";
        fTypeDirectTable[Typed::kDouble_vec] = "vector<F64>";

        fTypeDirectTable[Typed::kQuad]     = "quad";
        fTypeDirectTable[Typed::kQuad_ptr] = fPtrRef + "quad";
        
        fTypeDirectTable[Typed::kFixedPoint]     = "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_ptr] = fPtrRef + "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_ptr] = fPtrRef + fPtrRef + "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_vec] = "vector<fixpoint_t>";

        fTypeDirectTable[Typed::kBool]     = "bool";
        fTypeDirectTable[Typed::kBool_ptr] = fPtrRef + "bool";
        fTypeDirectTable[Typed::kBool_vec] = "vector<bool>";

        fTypeDirectTable[Typed::kVoid]     = "void";
        fTypeDirectTable[Typed::kVoid_ptr] = fPtrRef + "void";
        
        fTypeDirectTable[Typed::kSound]     = "Soundfile";
        fTypeDirectTable[Typed::kSound_ptr] = fPtrRef + "Soundfile";

        fTypeDirectTable[Typed::kObj]     = "";
        fTypeDirectTable[Typed::kObj_ptr] = fPtrRef;

        // TODO : handling kUint_ptr
    }

    virtual std::string generateType(Typed* type, NamedTyped::Attribute attr = NamedTyped::kDefault)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
  
        if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            std::string ty_str = generateType(named_typed->fType);
            return named_typed->fName + ((ty_str != "") ? (": " + ty_str) : "");
        } else if (array_typed) {
            return (array_typed->fSize == 0)
                ? fPtrRef + generateType(array_typed->fType)
                : "[" + generateType(array_typed->fType) + ";" + std::to_string(array_typed->fSize) + "]";
        } else {
            faustassert(false);
            return "";
        }
    }

    virtual std::string generateType(Typed* type, const std::string& name)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return name + ": " + fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            std::string ty_str = named_typed->fName + generateType(named_typed->fType);
            return name + ((ty_str != "") ? (": " + ty_str) : "");
        } else if (array_typed) {
            return name + ": " + generateType(type);
        } else {
            faustassert(false);
            return "";
        }
    }
};

// StringTypeManager for CMajor backend

class CmajorStringTypeManager : public StringTypeManager {
   public:
    CmajorStringTypeManager(const std::string& float_macro_name, const std::string& ptr_ref)
        : StringTypeManager(float_macro_name, ptr_ref)
    {
        fPtrRef = ptr_ref;

        fTypeDirectTable[Typed::kInt32]     = "int32";
        fTypeDirectTable[Typed::kInt32_ptr] = "int32" + fPtrRef;
        fTypeDirectTable[Typed::kInt32_vec] = "vector<i32>";

        fTypeDirectTable[Typed::kInt64]     = "int64";
        fTypeDirectTable[Typed::kInt64_ptr] = "int64" + fPtrRef;
        fTypeDirectTable[Typed::kInt64_vec] = "vector<i64>";

        fTypeDirectTable[Typed::kFloat]     = "float32";
        fTypeDirectTable[Typed::kFloat_ptr] = "float32" + fPtrRef;
        fTypeDirectTable[Typed::kFloat_ptr_ptr] = "float32" + fPtrRef + fPtrRef;
        fTypeDirectTable[Typed::kFloat_vec] = "vector<float32>";

        fTypeDirectTable[Typed::kDouble]     = "float64";
        fTypeDirectTable[Typed::kDouble_ptr] = "float64" + fPtrRef;
        fTypeDirectTable[Typed::kDouble_ptr_ptr] = "float64" + fPtrRef + fPtrRef;
        fTypeDirectTable[Typed::kDouble_vec] = "vector<float64>";

        fTypeDirectTable[Typed::kQuad]     = "quad";
        fTypeDirectTable[Typed::kQuad_ptr] = "quad" + fPtrRef;
        
        fTypeDirectTable[Typed::kFixedPoint]     = "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_ptr] = "fixpoint_t" + fPtrRef;
        fTypeDirectTable[Typed::kFixedPoint_ptr] = "fixpoint_t" + fPtrRef + fPtrRef;
        fTypeDirectTable[Typed::kFixedPoint_vec] = "vector<fixpoint_t>";

        fTypeDirectTable[Typed::kBool]     = "bool";
        fTypeDirectTable[Typed::kBool_ptr] = "bool" + fPtrRef;
        fTypeDirectTable[Typed::kBool_vec] = "vector<bool>";

        fTypeDirectTable[Typed::kVoid]     = "void";
        fTypeDirectTable[Typed::kVoid_ptr] = "void" + fPtrRef;

        // TODO : handling Soundfile

        fTypeDirectTable[Typed::kObj]     = "";
        fTypeDirectTable[Typed::kObj_ptr] = fPtrRef;

        // TODO : handling kUint_ptr
    }

    virtual std::string generateType(Typed* type, NamedTyped::Attribute attr = NamedTyped::kDefault)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            return generateType(named_typed->fType) + " " + named_typed->fName;
        } else if (array_typed) {
            return (array_typed->fSize == 0)
                ? generateType(array_typed->fType) + fPtrRef
                : generateType(array_typed->fType) + "[" + std::to_string(array_typed->fSize) + "]";
        } else {
            faustassert(false);
            return "";
        }
    }

    virtual std::string generateType(Typed* type, const std::string& name)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType] + " " + name;
        } else if (named_typed) {
            return named_typed->fName + generateType(named_typed->fType) + " " + name;
        } else if (array_typed) {
            return generateType(type) + " " + name;
        } else {
            faustassert(false);
            return "";
        }
    }
};

// StringTypeManager for Julia backend

class JuliaStringTypeManager : public StringTypeManager {
   public:
    JuliaStringTypeManager(const std::string& float_macro_name, const std::string& ptr_ref, const std::string& struct_name = "")
        : StringTypeManager(float_macro_name, ptr_ref)
    {
        fPtrRef = ptr_ref;

        fTypeDirectTable[Typed::kInt32]     = "Int32";
        fTypeDirectTable[Typed::kInt32_ptr] = "Int32";
        fTypeDirectTable[Typed::kInt32_vec] = "vector<Int32>";

        fTypeDirectTable[Typed::kInt64]     = "Int64";
        fTypeDirectTable[Typed::kInt64_ptr] = "Int64";
        fTypeDirectTable[Typed::kInt64_vec] = "vector<Int64>";

        fTypeDirectTable[Typed::kFloat]     = "T";
        fTypeDirectTable[Typed::kFloat_ptr] = "T";
        fTypeDirectTable[Typed::kFloat_ptr_ptr] = "T";
        fTypeDirectTable[Typed::kFloat_vec] = "vector<T>";
        
        fTypeDirectTable[Typed::kDouble]     = "T";
        fTypeDirectTable[Typed::kDouble_ptr] = "T";
        fTypeDirectTable[Typed::kDouble_ptr_ptr] = "T";
        fTypeDirectTable[Typed::kDouble_vec] = "vector<T>";

        fTypeDirectTable[Typed::kQuad]     = "quad";
        fTypeDirectTable[Typed::kQuad_ptr] = fPtrRef + "quad";
        
        fTypeDirectTable[Typed::kFixedPoint]     = "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_ptr] = fPtrRef + "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_ptr] = fPtrRef + fPtrRef + "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_vec] = "vector<fixpoint_t>";

        fTypeDirectTable[Typed::kBool]     = "bool";
        fTypeDirectTable[Typed::kBool_ptr] = fPtrRef + "bool";
        fTypeDirectTable[Typed::kBool_vec] = "vector<bool>";

        fTypeDirectTable[Typed::kVoid]     = "void";
        fTypeDirectTable[Typed::kVoid_ptr] = fPtrRef + "void";
        
        fTypeDirectTable[Typed::kSound]     = "Soundfile";
        fTypeDirectTable[Typed::kSound_ptr] = fPtrRef + "Soundfile";

        // DSP has to be empty here
        fTypeDirectTable[Typed::kObj]     = struct_name + "{T}";
        fTypeDirectTable[Typed::kObj_ptr] = struct_name + "{T}";

        fTypeDirectTable[Typed::kUint_ptr] = "uintptr_t";
    }

    virtual std::string generateType(Typed* type, NamedTyped::Attribute attr = NamedTyped::kDefault)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
  
        if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            std::string ty_str = generateType(named_typed->fType);
            return named_typed->fName + ((ty_str != "") ? ("::" + ty_str) : "");
        } else if (array_typed) {
            return (array_typed->fSize == 0)
                ? "::" + fPtrRef + generateType(array_typed->fType)
                : "::Vector{" + generateType(array_typed->fType) + "}";
        } else {
            faustassert(false);
            return "";
        }
    }

    virtual std::string generateType(Typed* type, const std::string& name)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return name + "::" + fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            std::string ty_str = named_typed->fName + generateType(named_typed->fType);
            return name + ((ty_str != "") ? ("::" + ty_str) : "");
        } else if (array_typed) {
            return name + generateType(type);
        } else {
            faustassert(false);
            return "";
        }
    }
};

// StringTypeManager for JAX backend

class JAXStringTypeManager : public StringTypeManager {
   public:
    JAXStringTypeManager(const std::string& float_macro_name, const std::string& ptr_ref, const std::string& struct_name = "")
        : StringTypeManager(float_macro_name, ptr_ref)
    {
        fPtrRef = ptr_ref;

        fTypeDirectTable[Typed::kInt32]     = "jnp.int32";
        fTypeDirectTable[Typed::kInt32_ptr] = "jnp.int32";
        fTypeDirectTable[Typed::kInt32_vec] = "vector<Int32>"; // todo:

        fTypeDirectTable[Typed::kInt64]     = "jnp.int64";
        fTypeDirectTable[Typed::kInt64_ptr] = "jnp.int64";
        fTypeDirectTable[Typed::kInt64_vec] = "vector<Int64>"; // todo:

        fTypeDirectTable[Typed::kFloat]     = "";
        fTypeDirectTable[Typed::kFloat_ptr] = "";
        fTypeDirectTable[Typed::kFloat_ptr_ptr] = "";
        fTypeDirectTable[Typed::kFloat_vec] = ""; // todo:

        fTypeDirectTable[Typed::kDouble]     = "";
        fTypeDirectTable[Typed::kDouble_ptr] = "";
        fTypeDirectTable[Typed::kDouble_ptr_ptr] = "";
        fTypeDirectTable[Typed::kDouble_vec] = ""; // todo:

        fTypeDirectTable[Typed::kQuad]     = "";
        fTypeDirectTable[Typed::kQuad_ptr] = "";

        fTypeDirectTable[Typed::kFixedPoint]     = "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_ptr] = "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_ptr] = "fixpoint_t";
        fTypeDirectTable[Typed::kFixedPoint_vec] = "vector<fixpoint_t>";

        fTypeDirectTable[Typed::kBool]     = "jnp.bool";
        fTypeDirectTable[Typed::kBool_ptr] = "jnp.bool";
        fTypeDirectTable[Typed::kBool_vec] = "jnp.array[jnp.bool]";  // todo:

        fTypeDirectTable[Typed::kVoid]     = "void";
        fTypeDirectTable[Typed::kVoid_ptr] = "void";

        fTypeDirectTable[Typed::kSound]     = "Soundfile";
        fTypeDirectTable[Typed::kSound_ptr] = "Soundfile";

        // DSP has to be empty here
        fTypeDirectTable[Typed::kObj]     = "";  // struct_name
        fTypeDirectTable[Typed::kObj_ptr] = "";

        fTypeDirectTable[Typed::kUint_ptr] = "uintptr_t";
    }

    virtual std::string generateType(Typed* type, NamedTyped::Attribute attr = NamedTyped::kDefault)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            std::string ty_str = generateType(named_typed->fType);
            if (ty_str != "") {
                return ty_str + "(" + named_typed->fName + ")";
            }
            return named_typed->fName;
        } else if (array_typed) {
            return fTypeDirectTable[array_typed->getType()];
        } else {
            faustassert(false);
            return "";
        }
    }

    virtual std::string generateType(Typed* type, const std::string& name)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return name;
            //return name + "::" + fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            std::string ty_str = named_typed->fName + generateType(named_typed->fType);
            //return name + ((ty_str != "") ? ("::" + ty_str) : "");
            return name;
        } else if (array_typed) {
            // return (array_typed->fSize == 0)
            //         ? name + "::" + fPtrRef + generateType(array_typed->fType)
            //         : name + "::Vector{" + generateType(array_typed->fType) + "}";
            return name;
        } else {
            faustassert(false);
            return "";
        }
    }
};

// StringTypeManager for Template backend

class TemplateStringTypeManager : public StringTypeManager {

    public:
    TemplateStringTypeManager(const std::string& float_macro_name, const std::string& ptr_ref, const std::string& struct_name = "")
        : StringTypeManager(float_macro_name, ptr_ref)
    {
        // TODO
    }
    
    virtual std::string generateType(Typed* type, NamedTyped::Attribute attr = NamedTyped::kDefault)
    {
        // TODO
        return "";
    }
    
    virtual std::string generateType(Typed* type, const std::string& name)
    {
        // TODO
        return "";
    }
};

#endif
