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
 
 
 
// device.h


#if !defined DEVICE_H
#define DEVICE_H

#include "stdio.h"

class device  
{
	public:
        virtual ~device() {}
        virtual void rect(float,float,float,float)=0;
		virtual void rond(float,float,float)=0;
		virtual void carre(float,float,float)=0;
		virtual void fleche(float,float,float,int)=0;
		virtual void trait(float,float,float,float)=0;
		virtual void dasharray(float,float,float,float)=0;
		virtual void text(float,float,const char*)=0;
		virtual void label(float,float,const char*)=0;
		virtual void markSens(float,float,int)=0;
		virtual void Error(const char*,const char*,int,float,float,float)=0;
	
	protected:
		FILE* fic_repr;

};

#endif 


