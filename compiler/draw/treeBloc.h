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
 
 
 
// treeBloc.h

#if !defined TREEBLOC_H
#define TREEBLOC_H

#include "treeRepr.h"

class treeBloc : public treeRepr  
{
	public:
		treeBloc(const char*,float,float,vector<float>,vector<float>);	
		
		~treeBloc();

		void extractParam(vector<treeRepr*>&);
		pair<int,int> testTreeNbIo();
		representation* treeToRepr();

	private:
		int nb_i;
		int nb_o;
		float hauteur;
		float largeur;
		vector <float> ins;
		vector <float> outs;
};

#endif 


