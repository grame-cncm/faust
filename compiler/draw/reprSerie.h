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
 
 
 
// reprSerie.h: interface for the reprSerie class.

#if !defined REPRSERIE_H
#define REPRSERIE_H

#include "representation.h"
#include <iostream>
#include <vector>

using namespace std;


class reprSerie : public representation  
{
	public:
		reprSerie(representation*,representation*);
				
		void draw(device&,vector<wire*>&,float,float,vector<wire*>,vector<wire*>,int);	
		~reprSerie();

	private:
		representation* A;
		representation* B;

		float hisuppl; // height for additional ins and outs 

		// tools for the choice of the right "x Angles":
		bool* Xa;
		int tailleXa;
		void XaInit(int);	
		int dernXaLibre();
		int premXaLibre();
};

#endif 


