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
 
 
 
// treeNormal.h

#if !defined TREENORMAL_H
#define TREENORMAL_H


#include "treeRepr.h"

class treeNormal : public treeRepr  
{
	public:
		treeNormal(const char* op,treeRepr* tA,treeRepr* tB) { op_name=op; A=tA; B=tB; nb_i=0; nb_o=0; };
		~treeNormal();

		void extractParam(vector<treeRepr*>&);
		pair<int,int> testTreeNbIo();
		representation* treeToRepr();

	private:
		const char* op_name;
		treeRepr* A;
		treeRepr* B;
		int nb_i;
		int nb_o;

};

#endif



