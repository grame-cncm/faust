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
 
 
 
// treeParam.cpp

#include "treeParam.h"

treeParam::treeParam(treeParam* Bloc,int nb_i,int nb_o,vector<treeParam*>& listParam)
{ //construction of the Param bloc used for the construction as a copy and complement of the current Param Block.
	name=Bloc->getName();

	nb_i_Min=Bloc->nb_i_Min;
	nb_i_Max=Bloc->nb_i_Max;
	nb_o_Min=Bloc->nb_o_Min;
	nb_o_Max=Bloc->nb_o_Max;
	nb_i_courant=nb_i;
	nb_o_courant=nb_o;

	index_list=Bloc->index_list;
	*listParam[index_list]=*this;
}

void treeParam::extractParam(vector<treeRepr*>& list)
{
	int i;
	bool ok=true;
	for(i=0;i<(int)list.size();i++)
		ok=ok && strcmp(this->getName(),list[i]->getName());
	
	if(ok) //"this" is not already in the list
		list.push_back(this);
}

pair<int,int> treeParam::testTreeNbIo()
{
	pair<int,int> p;
	p.first=nb_i_courant;
	p.second=nb_o_courant;
	return p;
}

representation* treeParam::treeToRepr()
{
	//The size is set according to nb ins and nb outs: 
	float hauteur;
	if(nb_i_courant>nb_o_courant)
		hauteur=(nb_i_courant+1)*delta_hf;
	else
		hauteur=(nb_o_courant+1)*delta_hf;
		
	float largeur=20+hauteur/5;

	int i;
	vector<float> ins,outs;

	for(i=0;i<nb_i_courant;i++)  
		ins.push_back((i+1)*delta_hf);

	for(i=0;i<nb_o_courant;i++)  
		outs.push_back((i+1)*delta_hf);
	
	return new reprParam(name,largeur,hauteur,ins,outs);
}

treeParam::~treeParam()
{

}




