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
 
 
 
// treeParam.h

#if !defined TREEPARAM_H
#define TREEPARAM_H

#include "treeRepr.h"

class treeParam : public treeRepr  
{
	public:
		treeParam(const char* n,int im,int iM,int om,int oM)	{ name=n; nb_i_Min=im; nb_i_Max=iM; nb_o_Min=om; nb_o_Max=oM;};
		treeParam(treeParam*,int,int,vector<treeParam*>&); //recopie

		void extractParam(vector<treeRepr*>&);
		pair<int,int> testTreeNbIo();
		representation* treeToRepr();

		virtual ~treeParam();
		int get_nb_i_Min()			  { return nb_i_Min; };
		int get_nb_i_Max()			  { return nb_i_Max; };
		int get_nb_o_Min()			  { return nb_o_Min; };
		int get_nb_o_Max()			  { return nb_o_Max; };
		int get_index_list()		  { return index_list; };
		void set_index_list(int indL) { index_list=indL; }
		int get_nb_i_courant()		  { return nb_i_courant; };
		int get_nb_o_courant()		  { return nb_o_courant; };
	
	private:
		int nb_i_Min;
		int nb_i_Max;
		int nb_o_Min;
		int nb_o_Max;
		int index_list;
		int nb_i_courant;
		int nb_o_courant;
};

#endif



