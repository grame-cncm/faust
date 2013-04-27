/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>
#include <assert.h>

#include "instructions.hh"

class StringTypeManager {

    protected:

        map <Typed::VarType, string> fTypeDirectTable;
        map <string, Typed::VarType> fInvertTypeTable;

        string fPtrPosfix;

    public:

        StringTypeManager(string float_macro_name, string ptr_postfix)
        {
            fPtrPosfix = ptr_postfix;
            fillTypeDirectTable(float_macro_name, float_macro_name + ptr_postfix);
        }

        void fillTypeDirectTable(string float_macro_name, string float_macro_name_ptr)
        {
            fTypeDirectTable[Typed::kFloatMacro] = float_macro_name;
            fTypeDirectTable[Typed::kFloatMacro_ptr] = float_macro_name_ptr;

            fTypeDirectTable[Typed::kFloat] = "float";
            fTypeDirectTable[Typed::kFloat_ptr] = "float" + fPtrPosfix;
            fTypeDirectTable[Typed::kFloat_vec] = "vector<float>";

            fTypeDirectTable[Typed::kInt] = "int";
            fTypeDirectTable[Typed::kInt_ptr] = "int" + fPtrPosfix;
            fTypeDirectTable[Typed::kInt_vec] = "vector<int>";

            fTypeDirectTable[Typed::kDouble] = "double";
            fTypeDirectTable[Typed::kDouble_ptr] = "double" + fPtrPosfix;
            fTypeDirectTable[Typed::kDouble_vec] = "vector<double>";

            fTypeDirectTable[Typed::kQuad] = "quad";
            fTypeDirectTable[Typed::kQuad_ptr] = "quad" + fPtrPosfix;

            fTypeDirectTable[Typed::kBool] = "bool";
            fTypeDirectTable[Typed::kBool_ptr] = "bool" + fPtrPosfix;
            fTypeDirectTable[Typed::kBool_vec] = "vector<bool>";

            fTypeDirectTable[Typed::kVoid] = "void";
            fTypeDirectTable[Typed::kVoid_ptr] = "void" + fPtrPosfix;

            fTypeDirectTable[Typed::kObj] = "";
            fTypeDirectTable[Typed::kObj_ptr] = fPtrPosfix;

            fInvertTypeTable[FLOATMACRO] = Typed::kFloatMacro;
            fInvertTypeTable[FLOATMACROPTR] = Typed::kFloatMacro_ptr;

            fInvertTypeTable["float"] = Typed::kFloat;
            fInvertTypeTable["float" + fPtrPosfix] = Typed::kFloat_ptr;
            fInvertTypeTable["vector<float>"] = Typed::kFloat_vec;

            fInvertTypeTable["int"] =  Typed::kInt;
            fInvertTypeTable["int" + fPtrPosfix] = Typed::kInt_ptr;
            fInvertTypeTable["vector<int>"] = Typed::kInt_vec;

            fInvertTypeTable["double"] = Typed::kDouble;
            fInvertTypeTable["double" + fPtrPosfix] = Typed::kDouble_ptr;
            fInvertTypeTable["vector<double>"] = Typed::kDouble_vec;

            fInvertTypeTable["quad"] = Typed::kQuad;
            fInvertTypeTable["quad" + fPtrPosfix] = Typed::kQuad_ptr;

            fInvertTypeTable["bool"] = Typed::kBool;
            fInvertTypeTable["bool" + fPtrPosfix] = Typed::kBool_ptr;
            fInvertTypeTable["vector<bool>"] = Typed::kBool_vec;

            fInvertTypeTable["void"] = Typed::kVoid;
            fInvertTypeTable["void" + fPtrPosfix] = Typed::kVoid_ptr;
        }

        /*
        string generateType(Typed* type)
        {
            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
            NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
            FunTyped* fun_typed = dynamic_cast<FunTyped*>(type);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
            VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);

            if (basic_typed) {
                return fTypeDirectTable[basic_typed->fType];
            } else if (named_typed) {
                return generateType(named_typed->fType) + " " + named_typed->fName;
            } else if (fun_typed) {
                return "FUN TYPE";
            } else if (array_typed) {
                BasicTyped* basic_typed1 = dynamic_cast<BasicTyped*>(array_typed->fType);
                ArrayTyped* array_typed1 = dynamic_cast<ArrayTyped*>(array_typed->fType);
                NamedTyped* named_typed1 = dynamic_cast<NamedTyped*>(array_typed->fType);
                StructTyped* struct_typed1 = dynamic_cast<StructTyped*>(array_typed->fType);
                std::ostringstream num_str;
                num_str << array_typed->fSize;
                if (basic_typed1) {
                    return (array_typed->fSize == 0)
                        ? fTypeDirectTable[array_typed->getType()]
                        : generateType(array_typed->fType) + "[" + num_str.str() + "]";
                } else if (array_typed1) {
                    return generateType(array_typed1) + "[" + num_str.str() + "]";
                } else if (named_typed1) {
                    return named_typed1->fName + "[" + num_str.str() + "]";
                } else if (struct_typed1) {
                    return struct_typed1->fName + " f" + "[" + num_str.str() + "]";
                } else {
                    assert(false);
                    return "";
                }
            } else if (vector_typed) {
                std::ostringstream num_str;
                num_str << vector_typed->fSize;
                return (vector_typed->fSize == 0)
                    ? "valarray<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "()"
                    : "valarray<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "(" + num_str.str() + ")";
            } else {
                assert(false);
                return "";
            }
        }

        string generateType(Typed* type, const string& name)
        {
            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
            NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
            FunTyped* fun_typed = dynamic_cast<FunTyped*>(type);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
            VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);

            if (basic_typed) {
                return fTypeDirectTable[basic_typed->fType] + " " + name;
            } else if (named_typed) {
                // TODO : break code with subclasses
                return named_typed->fName + generateType(named_typed->fType) + " " + name;
                //return named_typed->fName + " " + name;
            } else if (fun_typed) {
                return "FUN TYPE";
            } else if (array_typed) {
                BasicTyped* basic_typed1 = dynamic_cast<BasicTyped*>(array_typed->fType);
                ArrayTyped* array_typed1 = dynamic_cast<ArrayTyped*>(array_typed->fType);
                NamedTyped* named_typed1 = dynamic_cast<NamedTyped*>(array_typed->fType);
                StructTyped* struct_typed1 = dynamic_cast<StructTyped*>(array_typed->fType);
                std::ostringstream num_str;
                num_str << array_typed->fSize;
                if (basic_typed1) {
                    return (array_typed->fSize == 0)
                        ? generateType(array_typed->fType) + fPtrPosfix + " " + name
                        : generateType(array_typed->fType) + " " + name + "[" + num_str.str() + "]";
                        //: generateType(array_typed->fType) + "[" + num_str.str() + "] " + name;
                } else if (array_typed1) {
                    return generateType(array_typed1) + " " + name + "[" + num_str.str() + "]";
                } else if (named_typed1) {
                    return named_typed1->fName + " " + name + "[" + num_str.str() + "]";
                } else if (struct_typed1) {
                    return struct_typed1->fName + " " + name +  + "[" + num_str.str() + "]";
                } else {
                    assert(false);
                    return "";
                }
            } else if (vector_typed) {
                std::ostringstream num_str;
                num_str << vector_typed->fSize;
                return (vector_typed->fSize == 0)
                    ? "valarray<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "()"
                    : "valarray<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "(" + num_str.str() + ")";
            } else {
                assert(false);
                return "";
            }
        }
        */

        string generateType(Typed* type)
        {
            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
            NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
            FunTyped* fun_typed = dynamic_cast<FunTyped*>(type);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
            VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);

            if (basic_typed) {
                return fTypeDirectTable[basic_typed->fType];
            } else if (named_typed) {
                return generateType(named_typed->fType) + " " + named_typed->fName;
            } else if (fun_typed) {
                return "FUN TYPE";
            } else if (array_typed) {
                return fTypeDirectTable[array_typed->getType()];
            } else if (vector_typed) {
                std::ostringstream num_str;
                num_str << vector_typed->fSize;
                return (vector_typed->fSize == 0)
                    ? "valarray<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "()"
                    : "valarray<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "(" + num_str.str() + ")";
            } else {
                assert(false);
                return "";
            }
        }

        string generateType(Typed* type, const string& name)
        {
            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
            NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
            FunTyped* fun_typed = dynamic_cast<FunTyped*>(type);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
            VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);

            if (basic_typed) {
                return fTypeDirectTable[basic_typed->fType] + " " + name;
            } else if (named_typed) {
                return named_typed->fName + generateType(named_typed->fType) + " " + name;
            } else if (fun_typed) {
                return "FUN TYPE";
            } else if (array_typed) {
                std::ostringstream num_str;
                num_str << array_typed->fSize;
                return (array_typed->fSize == 0)
                    ? generateType(array_typed->fType) + fPtrPosfix + " " + name
                    : generateType(array_typed->fType) + " " + name + "[" + num_str.str() + "]";
            } else if (vector_typed) {
                std::ostringstream num_str;
                num_str << vector_typed->fSize;
                return (vector_typed->fSize == 0)
                    ? "valarray<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "()"
                    : "valarray<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "(" + num_str.str() + ")";
            } else {
                assert(false);
                return "";
            }
        }
};

#endif
