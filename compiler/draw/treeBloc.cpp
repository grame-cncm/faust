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
 
 
 
// treeBloc.cpp

#include "treeBloc.h"

treeBloc::treeBloc(const char* n,float l,float h,vector<float> i,vector<float> o)	
{
	name=n;
	hauteur=h;
	largeur=l;
	ins=i;
	outs=o;
	nb_i=(int)i.size();
	nb_o=(int)o.size();
}

void treeBloc::extractParam(vector<treeRepr*>& liste)
{ /* do nothing */
}

pair<int,int> treeBloc::testTreeNbIo()
{
	pair<int,int> p;
	p.first=nb_i;
	p.second=nb_o;
	return p;
}

representation* treeBloc::treeToRepr()
{
	return new reprBloc(name,largeur,hauteur,ins,outs);
}

treeBloc::~treeBloc()
{

}





