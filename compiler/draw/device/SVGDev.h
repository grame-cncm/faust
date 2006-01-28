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
 
 
 
// SVGDev.h

#if !defined SVGDEV_H
#define SVGDEV_H

#include "device.h"

class SVGDev : public device
{
	public:
		SVGDev(const char*,float,float);
		~SVGDev();
		void rect(float,float,float,float, const char*, const char*);
		void rond(float,float,float);
		void carre(float,float,float);
		void fleche(float,float,float,int);
		void trait(float,float,float,float);
		void dasharray(float,float,float,float);
		void text(float,float,const char*);
		void label(float,float,const char*);
		void markSens(float,float,int);
		void Error(const char*,const char*,int,float,float,float);

};

#endif 


