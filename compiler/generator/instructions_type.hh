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

#ifndef _INSTRUCTIONS_TYPE_H
#define _INSTRUCTIONS_TYPE_H

#include <string>

#include "garbageable.hh"

// ============================
// Base class for instructions
// ============================

struct Printable : public virtual Garbageable {
    static std::ostream* fOut;

    Printable() {}
    virtual ~Printable() {}
};

// ========================
//  Base classes for types
// ========================

struct InstVisitor;
struct CloneVisitor;

struct Typed : public Printable {
    enum VarType {
        kInt32,
        kInt32_ptr,
        kInt32_vec,
        kInt32_vec_ptr,
        kInt64,
        kInt64_ptr,
        kInt64_vec,
        kInt64_vec_ptr,
        kBool,
        kBool_ptr,
        kBool_vec,
        kBool_vec_ptr,
        kFloat,
        kFloat_ptr,
        kFloat_ptr_ptr,
        kFloat_vec,
        kFloat_vec_ptr,
        kFloatMacro,
        kFloatMacro_ptr,
        kFloatMacro_ptr_ptr,
        kDouble,
        kDouble_ptr,
        kDouble_ptr_ptr,
        kDouble_vec,
        kDouble_vec_ptr,
        kQuad,
        kQuad_ptr,
        kQuad_ptr_ptr,
        kQuad_vec,
        kQuad_vec_ptr,
        kFixedPoint,
        kFixedPoint_ptr,
        kFixedPoint_ptr_ptr,
        kFixedPoint_vec,
        kFixedPoint_vec_ptr,
        kVoid,
        kVoid_ptr,
        kObj,
        kObj_ptr,
        kSound,
        kSound_ptr,
        kUint_ptr,
        kNoType
    };

    Typed() {}
    virtual ~Typed() {}

    // Returns the pointer type version of a primitive type
    static VarType getPtrFromType(VarType type)
    {
        switch (type) {
            case kFloatMacro:
                return kFloatMacro_ptr;
            case kFloatMacro_ptr:
                return kFloatMacro_ptr_ptr;
            case kFloat:
                return kFloat_ptr;
            case kFloat_ptr:
                return kFloat_ptr_ptr;
            case kFloat_vec:
                return kFloat_vec_ptr;
            case kInt32:
                return kInt32_ptr;
            case kInt32_vec:
                return kInt32_vec_ptr;
            case kDouble:
                return kDouble_ptr;
            case kDouble_ptr:
                return kDouble_ptr_ptr;
            case kDouble_vec:
                return kDouble_vec_ptr;
            case kQuad:
                return kQuad_ptr;
            case kQuad_ptr:
                return kQuad_ptr_ptr;
            case kQuad_vec:
                return kQuad_vec_ptr;
            case kFixedPoint:
                return kFixedPoint_ptr;
            case kFixedPoint_ptr:
                return kFixedPoint_ptr_ptr;
            case kFixedPoint_vec:
                return kFixedPoint_vec_ptr;
            case kBool:
                return kBool_ptr;
            case kBool_vec:
                return kBool_vec_ptr;
            case kVoid:
                return kVoid_ptr;
            case kObj:
                return kObj_ptr;
            case kSound:
                return kSound_ptr;
            default:
                // Not supposed to happen
                std::cerr << "ASSERT : getPtrFromType " << type << std::endl;
                faustassert(false);
                return kNoType;
        }
    }

    // Returns the vector type version of a primitive type
    static VarType getVecFromType(VarType type)
    {
        switch (type) {
            case kFloat:
                return kFloat_vec;
            case kInt32:
                return kInt32_vec;
            case kDouble:
                return kDouble_vec;
            case kQuad:
                return kQuad_vec;
            case kFixedPoint:
                return kFixedPoint_vec;
            case kBool:
                return kBool_vec;
            default:
                // Not supposed to happen
                std::cerr << "ASSERT : getVecFromType " << type << std::endl;
                faustassert(false);
                return kNoType;
        }
    }

    // Returns the type version from pointer on a primitive type
    static VarType getTypeFromPtr(VarType type)
    {
        switch (type) {
            case kFloatMacro_ptr:
                return kFloatMacro;
            case kFloatMacro_ptr_ptr:
                return kFloatMacro_ptr;
            case kFloat_ptr:
                return kFloat;
            case kFloat_ptr_ptr:
                return kFloat_ptr;
            case kFloat_vec_ptr:
                return kFloat_vec;
            case kInt32_ptr:
                return kInt32;
            case kInt32_vec_ptr:
                return kInt32_vec;
            case kDouble_ptr:
                return kDouble;
            case kDouble_ptr_ptr:
                return kDouble_ptr;
            case kDouble_vec_ptr:
                return kDouble_vec;
            case kQuad_ptr:
                return kQuad;
            case kQuad_ptr_ptr:
                return kQuad_ptr;
            case kQuad_vec_ptr:
                return kQuad_vec;
            case kFixedPoint_ptr:
                return kFixedPoint;
            case kFixedPoint_ptr_ptr:
                return kFixedPoint_ptr;
            case kFixedPoint_vec_ptr:
                return kFixedPoint_vec;
            case kBool_ptr:
                return kBool;
            case kBool_vec_ptr:
                return kBool_vec;
            case kVoid_ptr:
                return kVoid;
            case kObj_ptr:
                return kObj;
            case kSound_ptr:
                return kSound;
            default:
                // Not supposed to happen
                std::cerr << "ASSERT : getTypeFromPtr " << Typed::gTypeString[type] << std::endl;
                faustassert(false);
                return kNoType;
        }
    }

    // Returns the type version from vector on a primitive type
    static VarType getTypeFromVec(VarType type)
    {
        switch (type) {
            case kFloat_vec:
                return kFloat;
            case kInt32_vec:
                return kInt32;
            case kDouble_vec:
                return kDouble;
            case kQuad_vec:
                return kQuad;
            case kFixedPoint_vec:
                return kFixedPoint;
            case kBool_vec:
                return kBool;
            default:
                // Not supposed to happen
                std::cerr << "ASSERT : getTypeFromVec " << Typed::gTypeString[type] << std::endl;
                faustassert(false);
                return kNoType;
        }
    }

    static std::string gTypeString[];

    static void init();

    virtual VarType getType() const = 0;

    virtual int getSizeBytes() const = 0;

    virtual void accept(InstVisitor* visitor) = 0;

    virtual Typed* clone(CloneVisitor* cloner) = 0;
    
    virtual std::string toString() = 0;
};

#endif
