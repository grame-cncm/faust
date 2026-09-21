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
        kInt64,
        kBool,
        kFloat,
        kDouble,
        kQuad,
        kFixedPoint,
        kFloatMacro,
        kVoid,
        kObj,
        kMeta,
        kSound,
        kUI,
        kUint,

        kInt32_ptr, // 14
        kInt64_ptr,
        kBool_ptr,
        kFloat_ptr,
        kDouble_ptr,
        kQuad_ptr,
        kFixedPoint_ptr,
        kFloatMacro_ptr,
        kVoid_ptr,
        kObj_ptr,
        kMeta_ptr,
        kSound_ptr,
        kUI_ptr,
        kUint_ptr,

        kInt32_vec, // 28
        kInt64_vec,
        kBool_vec,
        kFloat_vec,
        kDouble_vec,
        kQuad_vec,
        kFixedPoint_vec,

        kFloat_ptr_ptr, // 35
        kDouble_ptr_ptr,
        kQuad_ptr_ptr,
        kFixedPoint_ptr_ptr,
        kFloatMacro_ptr_ptr,

        kInt32_vec_ptr, // 40
        kInt64_vec_ptr,
        kBool_vec_ptr,
        kFloat_vec_ptr,
        kDouble_vec_ptr,
        kQuad_vec_ptr,
        kFixedPoint_vec_ptr,

        kNoType, // 47
    };

    Typed() {}
    virtual ~Typed() {}

    static bool isBasicType(VarType type)
    {
        return kInt32 <= type && type <= kUint;
    }

    static bool isBasicReal(VarType type)
    {
        return kFloat <= type && type <= kFloatMacro;
    }

    static bool isPtrType(VarType type)
    {
        return kInt32_ptr <= type && type <= kUint_ptr;
    }

    static bool isPtrReal(VarType type)
    {
        return kFloat_ptr <= type && type <= kFloatMacro_ptr;
    }

    static bool isPtrPtrReal(VarType type)
    {
        return kFloat_ptr_ptr <= type && type <= kFloatMacro_ptr_ptr;
    }

    static bool isVecType(VarType type)
    {
        return kInt32_vec <= type && type <= kFixedPoint_vec;
    }

    static bool isVecPtrType(VarType type)
    {
        return kInt32_vec_ptr <= type && type <= kFixedPoint_vec_ptr;
    }

    static bool isVecConvertibleType(VarType type)
    {
        return type == kInt32 || type == kInt64 || type == kBool ||
               (kFloat <= type && type <= kFixedPoint);
    }

    // Returns the pointer type version of a primitive type
    static VarType getPtrFromType(VarType type)
    {
        if (isBasicType(type)) {
            return VarType(type + (kInt32_ptr - kInt32));
        }
        if (isPtrReal(type)) {
            return VarType(type + (kFloat_ptr_ptr - kFloat_ptr));
        }
        if (isVecType(type)) {
            return VarType(type + (kInt32_vec_ptr - kInt32_vec));
        }
        std::cerr << "ASSERT : getPtrFromType " << type << std::endl;
        faustassert(false);
        return kNoType;
    }

    // Returns the vector type version of a primitive type
    static VarType getVecFromType(VarType type)
    {
        if (isVecConvertibleType(type)) {
            return VarType(type + (kInt32_vec - kInt32));
        }
        std::cerr << "ASSERT : getVecFromType " << type << std::endl;
        faustassert(false);
        return kNoType;
    }

    // Returns the type version from pointer on a primitive type
    static VarType getTypeFromPtr(VarType type)
    {
        if (isPtrType(type)) {
            return VarType(type - (kInt32_ptr - kInt32));
        }
        if (isPtrPtrReal(type)) {
            return VarType(type - (kFloat_ptr_ptr - kFloat_ptr));
        }
        if (isVecPtrType(type)) {
            return VarType(type - (kInt32_vec_ptr - kInt32_vec));
        }
        std::cerr << "ASSERT : getTypeFromPtr " << type << std::endl;
        faustassert(false);
        return kNoType;
    }

    // Returns the type version from vector on a primitive type
    static VarType getTypeFromVec(VarType type)
    {
        if (isVecType(type)) {
            return VarType(type - (kInt32_vec - kInt32));
        }
        std::cerr << "ASSERT : getTypeFromVec " << type << std::endl;
        faustassert(false);
        return kNoType;
    }

    static std::string gTypeString[];

    static void init();

    virtual VarType getType() const = 0;

    virtual int getSizeBytes() const = 0;

    virtual void accept(InstVisitor* visitor) = 0;

    virtual Typed* clone(CloneVisitor* cloner) = 0;

    bool isBasicTyped();
    bool isNamedTyped();
    bool isArrayTyped();
    bool isStructTyped();
    bool isVectorTyped();

    virtual std::string toString() = 0;
};
#endif
