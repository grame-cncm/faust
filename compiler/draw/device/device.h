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

#if !defined DEVICE_H
#define DEVICE_H

#include "garbageable.hh"
#include <stdio.h>

class device : public virtual Garbageable
{
	public:
        virtual ~device() {}
        virtual void rect(double x,double y,double l,double h, const char* color, const char* link)=0;
        virtual void triangle(double x,double y,double l,double h, const char* color, const char* link, bool leftright)=0;
        virtual void rond(double x,double y,double rayon)=0;
        virtual void carre(double x,double y,double cote)=0;
        virtual void fleche(double x,double y,double rotation,int sens)=0;
        virtual void trait(double x1,double y1,double x2,double y2)=0;
        virtual void dasharray(double x1,double y1,double x2,double y2)=0;
        virtual void text(double x,double y,const char* name, const char* link)=0;
        virtual void label(double x,double y,const char* name)=0;
        virtual void markSens(double x,double y,int sens)=0;
        virtual void Error(const char* message, const char* reason,int nb_error,double x,double y,double largeur)=0;
	
	protected:
		FILE* fic_repr;

};

#endif 


