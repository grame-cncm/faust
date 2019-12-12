/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _TYPE_MANAGER_H
#define _TYPE_MANAGER_H

#include <list>
#include <map>
#include <set>
#include <string>

#include "exception.hh"
#include "instructions.hh"

struct StringTypeManager {
    std::map<Typed::VarType, std::string> fTypeDirectTable;
    std::string                           fPtrPosfix;

    StringTypeManager(const std::string& float_macro_name, const std::string& posfix)
    {
        fTypeDirectTable[Typed::kFloatMacro]         = float_macro_name;
        fTypeDirectTable[Typed::kFloatMacro_ptr]     = float_macro_name + posfix;
        fTypeDirectTable[Typed::kFloatMacro_ptr_ptr] = float_macro_name + posfix + posfix;
    }

    virtual ~StringTypeManager() {}

    virtual std::string generateType(Typed* type)                          = 0;
    virtual std::string generateType(Typed* type, const std::string& name) = 0;
};

// StringTypeManager for C/C++ and Java backends

class CStringTypeManager : public StringTypeManager {
   public:
    CStringTypeManager(const std::string& float_macro_name, const std::string& ptr_postfix, const std::string& struct_name = "")
        : StringTypeManager(float_macro_name, ptr_postfix)
    {
        fPtrPosfix = ptr_postfix;

        fTypeDirectTable[Typed::kInt32]     = "int";
        fTypeDirectTable[Typed::kInt32_ptr] = "int" + fPtrPosfix;
        fTypeDirectTable[Typed::kInt32_vec] = "vector<int>";

        fTypeDirectTable[Typed::kInt64]     = "long long";
        fTypeDirectTable[Typed::kInt64_ptr] = "long long" + fPtrPosfix;
        fTypeDirectTable[Typed::kInt64_vec] = "vector<long long>";

        fTypeDirectTable[Typed::kFloat]         = "float";
        fTypeDirectTable[Typed::kFloat_ptr]     = "float" + fPtrPosfix;
        fTypeDirectTable[Typed::kFloat_ptr_ptr] = "float" + fPtrPosfix + fPtrPosfix;
        fTypeDirectTable[Typed::kFloat_vec]     = "vector<float>";

        fTypeDirectTable[Typed::kDouble]         = "double";
        fTypeDirectTable[Typed::kDouble_ptr]     = "double" + fPtrPosfix;
        fTypeDirectTable[Typed::kDouble_ptr_ptr] = "double" + fPtrPosfix + fPtrPosfix;
        fTypeDirectTable[Typed::kDouble_vec]     = "vector<double>";

        fTypeDirectTable[Typed::kQuad]     = "quad";
        fTypeDirectTable[Typed::kQuad_ptr] = "quad" + fPtrPosfix;
        fTypeDirectTable[Typed::kQuad_vec] = "vector<quad>";

        fTypeDirectTable[Typed::kBool]     = "bool";
        fTypeDirectTable[Typed::kBool_ptr] = "bool" + fPtrPosfix;
        fTypeDirectTable[Typed::kBool_vec] = "vector<bool>";

        fTypeDirectTable[Typed::kVoid]     = "void";
        fTypeDirectTable[Typed::kVoid_ptr] = "void" + fPtrPosfix;

        fTypeDirectTable[Typed::kSound]     = "Soundfile";
        fTypeDirectTable[Typed::kSound_ptr] = "Soundfile" + fPtrPosfix;

        // DSP has to be empty here
        fTypeDirectTable[Typed::kObj]     = struct_name;
        fTypeDirectTable[Typed::kObj_ptr] = struct_name + fPtrPosfix;

        fTypeDirectTable[Typed::kUint_ptr] = "uintptr_t";
    }

    virtual std::string generateType(Typed* type)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            return generateType(named_typed->fType) + " " + named_typed->fName;
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
            return fTypeDirectTable[basic_typed->fType] + " " + name;
        } else if (named_typed) {
            return named_typed->fName + generateType(named_typed->fType) + " " + name;
        } else if (array_typed) {
            return (array_typed->fSize == 0 || array_typed->fIsPtr)
                       ? generateType(array_typed->fType) + fPtrPosfix + " " + name
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
    RustStringTypeManager(const std::string& float_macro_name, const std::string& ptr_postfix)
        : StringTypeManager(float_macro_name, float_macro_name + ptr_postfix)
    {
        fPtrPosfix = ptr_postfix;

        fTypeDirectTable[Typed::kInt32]     = "i32";
        fTypeDirectTable[Typed::kInt32_ptr] = "i32" + fPtrPosfix;
        fTypeDirectTable[Typed::kInt32_vec] = "vector<i32>";

        fTypeDirectTable[Typed::kInt64]     = "i64";
        fTypeDirectTable[Typed::kInt64_ptr] = "i64" + fPtrPosfix;
        fTypeDirectTable[Typed::kInt64_vec] = "vector<i64>";

        fTypeDirectTable[Typed::kFloat]     = "f32";
        fTypeDirectTable[Typed::kFloat_ptr] = "f32" + fPtrPosfix;
        fTypeDirectTable[Typed::kFloat_vec] = "vector<f32>";

        fTypeDirectTable[Typed::kDouble]     = "f64";
        fTypeDirectTable[Typed::kDouble_ptr] = "f64" + fPtrPosfix;
        fTypeDirectTable[Typed::kDouble_vec] = "vector<f64>";

        fTypeDirectTable[Typed::kQuad]     = "quad";
        fTypeDirectTable[Typed::kQuad_ptr] = "quad" + fPtrPosfix;

        fTypeDirectTable[Typed::kBool]     = "bool";
        fTypeDirectTable[Typed::kBool_ptr] = "bool" + fPtrPosfix;
        fTypeDirectTable[Typed::kBool_vec] = "vector<bool>";

        fTypeDirectTable[Typed::kVoid]     = "void";
        fTypeDirectTable[Typed::kVoid_ptr] = "void" + fPtrPosfix;

        // TODO : handling Soundfile

        fTypeDirectTable[Typed::kObj]     = "";
        fTypeDirectTable[Typed::kObj_ptr] = fPtrPosfix;

        // TODO : handling kUint_ptr
    }

    virtual std::string generateType(Typed* type)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            string ty_str = generateType(named_typed->fType);
            return named_typed->fName + ((ty_str != "") ? (": " + ty_str) : "");
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
            return name + ": " + fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            string ty_str = named_typed->fName + generateType(named_typed->fType);
            return name + ((ty_str != "") ? (": " + ty_str) : "");
        } else if (array_typed) {
            return (array_typed->fSize == 0)
                       ? name + ": " + fPtrPosfix + generateType(array_typed->fType)
                       : name + ": [" + generateType(array_typed->fType) + ";" + std::to_string(array_typed->fSize) + "]";
        } else {
            faustassert(false);
            return "";
        }
    }
};

// StringTypeManager for SOUL backend

class SOULStringTypeManager : public StringTypeManager {
   public:
    SOULStringTypeManager(const std::string& float_macro_name, const std::string& ptr_postfix)
        : StringTypeManager(float_macro_name, float_macro_name + ptr_postfix)
    {
        fPtrPosfix = ptr_postfix;

        fTypeDirectTable[Typed::kInt32]     = "int32";
        fTypeDirectTable[Typed::kInt32_ptr] = "int32" + fPtrPosfix;
        fTypeDirectTable[Typed::kInt32_vec] = "vector<i32>";

        fTypeDirectTable[Typed::kInt64]     = "int64";
        fTypeDirectTable[Typed::kInt64_ptr] = "int64" + fPtrPosfix;
        fTypeDirectTable[Typed::kInt64_vec] = "vector<i64>";

        fTypeDirectTable[Typed::kFloat]     = "float32";
        fTypeDirectTable[Typed::kFloat_ptr] = "float32" + fPtrPosfix;
        fTypeDirectTable[Typed::kFloat_vec] = "vector<float32>";

        fTypeDirectTable[Typed::kDouble]     = "float64";
        fTypeDirectTable[Typed::kDouble_ptr] = "float64" + fPtrPosfix;
        fTypeDirectTable[Typed::kDouble_vec] = "vector<float64>";

        fTypeDirectTable[Typed::kQuad]     = "quad";
        fTypeDirectTable[Typed::kQuad_ptr] = "quad" + fPtrPosfix;

        fTypeDirectTable[Typed::kBool]     = "bool";
        fTypeDirectTable[Typed::kBool_ptr] = "bool" + fPtrPosfix;
        fTypeDirectTable[Typed::kBool_vec] = "vector<bool>";

        fTypeDirectTable[Typed::kVoid]     = "void";
        fTypeDirectTable[Typed::kVoid_ptr] = "void" + fPtrPosfix;

        // TODO : handling Soundfile

        fTypeDirectTable[Typed::kObj]     = "";
        fTypeDirectTable[Typed::kObj_ptr] = fPtrPosfix;

        // TODO : handling kUint_ptr
    }

    virtual std::string generateType(Typed* type)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
        NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);

        if (basic_typed) {
            return fTypeDirectTable[basic_typed->fType];
        } else if (named_typed) {
            return generateType(named_typed->fType) + " " + named_typed->fName;
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
            return fTypeDirectTable[basic_typed->fType] + " " + name;
        } else if (named_typed) {
            return named_typed->fName + generateType(named_typed->fType) + " " + name;
        } else if (array_typed) {
            return (array_typed->fSize == 0 || array_typed->fIsPtr)
                       ? generateType(array_typed->fType) + fPtrPosfix + " " + name
                       : generateType(array_typed->fType) + "[" + std::to_string(array_typed->fSize) + "] " + name;
        } else {
            faustassert(false);
            return "";
        }
    }
};

#endif
