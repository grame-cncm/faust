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

#ifndef _INSTRUCTIONS_TYPE_H
#define _INSTRUCTIONS_TYPE_H

// ============================
// Base class for instructions
// ============================

struct Printable : public virtual Garbageable
{
    static std::ostream* fOut;

    int fTab;

    Printable()
    {}
    virtual ~Printable()
    {}

};

// ==========================
//  Instruction with a type
// ==========================

struct CloneVisitor;

struct Typed : public Printable
{
    enum VarType { kInt32, kInt32ish, kInt32_ptr, kInt32_vec, kInt32_vec_ptr,
                kInt64, kInt64_ptr, kInt64_vec, kInt64_vec_ptr,
                kBool, kBool_ptr, kBool_vec, kBool_vec_ptr,
                kFloat, kFloatish, kFloat_ptr, kFloat_vec, kFloat_vec_ptr,
                kFloatMacro, kFloatMacro_ptr,
                kDouble, kDoublish, kDouble_ptr, kDouble_vec, kDouble_vec_ptr,
                kQuad, kQuad_ptr, kQuad_vec, kQuad_vec_ptr,
                kVoid, kVoid_ptr, kVoid_ptr_ptr, kObj, kObj_ptr, kNoType };
    
    static string gTypeString[];
    
    static void init();

    Typed()
    {}

    virtual VarType getType() = 0;
    
    static int getSizeOf(VarType type)
    {
        switch (type) {
            case kFloat:
            case kInt32:
                return 4;
            case kDouble:
                return 8;
            default:
                // Not supposed to happen
                cerr << "getSizeOf " << type << endl;
                faustassert(false);
                return -1;
        }
    }
  
    // Returns the pointer type version of a primitive type
    static VarType getPtrFromType(VarType type)
    {
        switch (type) {
            case kFloatMacro:
                return kFloatMacro_ptr;
            case kFloat:
                return kFloat_ptr;
            case kFloat_vec:
                return kFloat_vec_ptr;
            case kInt32:
                return kInt32_ptr;
            case kInt32_vec:
                return kInt32_vec_ptr;
            case kDouble:
                return kDouble_ptr;
            case kDouble_vec:
                return kDouble_vec_ptr;
            case kQuad:
                return kQuad_ptr;
            case kBool:
                return kBool_ptr;
            case kBool_vec:
                return kBool_vec_ptr;
            case kVoid:
                return kVoid_ptr;
            case kVoid_ptr:
                return kVoid_ptr_ptr;
            default:
                // Not supposed to happen
                cerr << "getPtrFromType " << type << endl;
                faustassert(false);
                return kVoid;
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
            case kBool:
                return kBool_vec;
            default:
                // Not supposed to happen
                cerr << "getVecFromType " << type << endl;
                faustassert(false);
                return kVoid;
        }
    }

    // Returns the type version from pointer on a primitive type
    static VarType getTypeFromPtr(VarType type)
    {
        switch (type) {
            case kFloatMacro_ptr:
                return kFloatMacro;
            case kFloat_ptr:
                return kFloat;
            case kFloat_vec_ptr:
                return kFloat_vec;
            case kInt32_ptr:
                return kInt32;
            case kInt32_vec_ptr:
                return kInt32_vec;
            case kDouble_ptr:
                return kDouble;
            case kQuad_ptr:
                return kQuad;
            case kDouble_vec_ptr:
                return kDouble_vec;
            case kBool_ptr:
                return kBool;
            case kBool_vec_ptr:
                return kBool_vec;
            case kVoid_ptr:
                return kVoid;
            case kVoid_ptr_ptr:
                return kVoid_ptr;
            default:
                // Not supposed to happen
                cerr << "getTypeFromPtr " << Typed::gTypeString[type] << endl;
                faustassert(false);
                return kVoid;
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
            case kBool_vec:
                return kBool;
            default:
                // Not supposed to happen
                cerr << "getTypeFromVec " << Typed::gTypeString[type] << endl;
                faustassert(false);
                return kVoid;
        }
    }
    
    virtual int getSize() = 0;

    virtual Typed* clone(CloneVisitor* cloner) = 0;
};

#endif
