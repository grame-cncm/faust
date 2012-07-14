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
 
// PSDev.h: interface for the PSDev class.

#if !defined PSDEV_H
#define PSDEV_H

#include "device.h"

class PSDev : public device  
{
	public:
		PSDev(const char*,double,double);
		~PSDev();
		void rect(double, double, double, double, const char*, const char*);
        void triangle(double x,double y,double l,double h, const char* color, const char* link, bool leftright);
        void rond(double,double,double);
		void carre(double,double,double);
		void fleche(double,double,double,int);
		void trait(double,double,double,double);
		void dasharray(double,double,double,double);
        void text(double,double,const char*, const char* link);
		void label(double,double,const char*);
		void markSens(double,double,int);
		void Error(const char*,const char*,int,double,double,double);

};

#endif 

