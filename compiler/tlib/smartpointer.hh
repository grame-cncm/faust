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

#ifndef _SMARTPOINTER_H
#define _SMARTPOINTER_H

#include <cstdio>
#include <cstdlib>

#include "exception.hh"

template <class T>
class P {
   private:
    T* p;

   public:
    P() : p(nullptr) {}
    P(T* rawptr) : p(rawptr) {}
    P(const P& ptr) : p((T*)ptr) {}

    template <class T2>
    P(const P<T2>& ptr) : p((T*)ptr)
    {
    }

    ~P() {}

       operator T*() const { return p; }
    T& operator*() const
    {
        if (p == nullptr) {
            cerr << "ERROR : null dereference in P<?>::operator*() const \n";
            faustassert(false);
        }
        return *p;
    }
    T* operator->() const
    {
        if (p == nullptr) {
            cerr << "ERROR : null dereference in P<?>::operator->() const \n";
            faustassert(false);
        }
        return p;
    }
    T* pointee() const { return p; }
    P& operator=(T* p_)
    {
        p = p_;
        return *this;
    }

    P& operator=(const P<T>& p_) { return operator=((T*)p_); }
    template <class T2>
    P& cast(T2* p_)
    {
        return operator=(dynamic_cast<T*>(p_));
    }
    template <class T2>
    P& cast(const P<T2>& p_)
    {
        return operator=(dynamic_cast<T*>(p_));
    }
};

#endif
