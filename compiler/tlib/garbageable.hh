/************************************************************************
 ************************************************************************
    TLIB : tree library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

/** \file garbageable.hh
 * The memory model of tlib: every object allocated through Garbageable's
 * operator new is registered in a global table and freed in one sweep by
 * Garbageable::cleanup() (called by tlib::cleanup()). This trades individual
 * deallocation for a very fast "free everything at the end of the session"
 * model, which fits the hash-consing design: trees are immutable, maximally
 * shared, and their lifetime is the whole session by construction.
 */

#ifndef __TLIB_GARBAGEABLE__
#define __TLIB_GARBAGEABLE__

#include <cstddef>
#include <new>

#include "export.hh"

// To be inherited by all garbageable classes

class TLIB_API Garbageable {
   public:
    Garbageable() {}
    virtual ~Garbageable() {}

    static void* operator new(std::size_t size);
    static void* operator new[](std::size_t size);
    static void  operator delete(void* ptr);
    static void  operator delete[](void* ptr);

    /// Delete every Garbageable allocated since the last cleanup.
    /// All Tree/Sym pointers obtained before this call become invalid.
    static void cleanup();
};

template <class P>
class GarbageablePtr : public Garbageable {
   private:
    P* fPtr;

   public:
    GarbageablePtr(const P& data) { fPtr = new P(data); }

    virtual ~GarbageablePtr() { delete (fPtr); }

    P* getPointer() { return fPtr; }
};

#endif
