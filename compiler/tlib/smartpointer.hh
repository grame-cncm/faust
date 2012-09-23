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
 
#ifndef _SMARTPOINTER_H
#define _SMARTPOINTER_H

#include <cstdlib>
#include <cstdio>

template<class T>
class P {
	private:
		T* p;
	public:
		P()	: p(0) 							{ }
		P(T* rawptr) : p(rawptr)			{ }
		P(const P& ptr) : p((T*)ptr) 		{ }

		template<class T2> 
		P(const P<T2>& ptr) : p((T*)ptr) 	{ }
		
		~P() 								{ }
		
		operator T*() const					{ return p;	}
		T& operator*() const {
			if (p == 0) {
				//throw std::runtime_error("Null dereference in P<?>::operator*() const ");
				fprintf(stderr, "Null dereference in P<?>::operator*() const \n ");
				exit(1);
			}
			return *p;
		}
		T* operator->() const	{ 
			if (p == 0) {
				fprintf(stderr, "Null dereference in P<?>::operator->() const \n ");
				//throw std::runtime_error("Null dereference in P<?>::operator->() const ");
				//std::cerr << "Null dereference in P<?>::operator->() const " << std::endl;
				exit(1);
			}
			return p;
		}
		T* pointee() const	{ return p;}
		P& operator=(T* p_)	{ p = p_;  return *this;}
		
		P& operator=(const P<T>& p_)		{ return operator=((T *) p_); }
		template<class T2> P& cast(T2* p_)	{ return operator=(dynamic_cast<T*>(p_)); }
		template<class T2> P& cast(const P<T2>& p_) { return operator=(dynamic_cast<T*>(p_)); }
};

#endif
