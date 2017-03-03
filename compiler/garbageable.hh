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

#ifndef __FAUST_GARBAGE__
#define __FAUST_GARBAGE__

#include <stdio.h>
#include <new>

#include "exception.hh"

class Garbageable {

    public:

        Garbageable();
        virtual ~Garbageable();
        
        void* operator new(size_t size);
        void* operator new[](size_t size);
        void operator delete(void* ptr);
        void operator delete[](void* ptr);
        
        static void cleanup();
   
};

template<class P> class GarbageablePtr : public virtual Garbageable
{
       
    private:
    
         P* fPtr;
        
    public:
    
        GarbageablePtr(const P& data)
        {
            fPtr = new P(data);
        }
        
        virtual ~GarbageablePtr()
        {
            delete(fPtr);
        }
        
        P* getPointer() { return fPtr; }
};

#endif

