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

#ifndef __FAUST_GARBAGE__
#define __FAUST_GARBAGE__

#include <stdio.h>
#include <new>

#include "exception.hh"
#include "faust/export.h"

// To be inherited by all garbageable classes

class LIBFAUST_API Garbageable {
   public:
    Garbageable() {}
    virtual ~Garbageable() {}

    static void* operator new(size_t size);
    static void* operator new[](size_t size);
    static void  operator delete(void* ptr);
    static void  operator delete[](void* ptr);

#if defined(__cpp_sized_deallocation)
    // Sized forms (C++14)
    static void operator delete(void* p, std::size_t sz) noexcept;
    static void operator delete[](void* p, std::size_t sz) noexcept;
#endif

#if defined(__cpp_aligned_new)
    // Aligned forms (C++17)
    static void* operator new(std::size_t sz, std::align_val_t al);
    static void  operator delete(void* p, std::align_val_t al) noexcept;

    static void* operator new[](std::size_t sz, std::align_val_t al);
    static void  operator delete[](void* p, std::align_val_t al) noexcept;

#if defined(__cpp_sized_deallocation)
    // Sized + aligned forms
    static void operator delete(void* p, std::size_t sz, std::align_val_t al) noexcept;
    static void operator delete[](void* p, std::size_t sz, std::align_val_t al) noexcept;
#endif
#endif

    static void cleanup();
};

template <class P>
class GarbageablePtr : public virtual Garbageable {
   private:
    P* fPtr;

   public:
    GarbageablePtr(const P& data) { fPtr = new P(data); }

    virtual ~GarbageablePtr() { delete (fPtr); }

    P* getPointer() { return fPtr; }
};

#endif
