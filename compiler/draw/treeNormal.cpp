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
 
 
 
// treeNormal.cpp

#include "treeNormal.h"
#include "string.h"

void treeNormal::extractParam(vector<treeRepr*>& liste)
{
	A->extractParam(liste);
	B->extractParam(liste);
}

pair<int,int> treeNormal::testTreeNbIo()
{
	pair<int,int> p,pA,pB;    // pA.first<=>insA    pA.second<=>outsA    and idem for pB

	pA=A->testTreeNbIo();
	pB=B->testTreeNbIo();

	if(pA.first==-1 || pB.first==-1)  // pA.first=-1 && pB.first=-1 <=> error
	{
		p.first=-1;
		p.second=-1;
	}
	else if(strcmp(op_name,"Serie")==0)
	{
		if(pA.second==0 || pB.first==0) { p.first=-1; p.second=-1; }
		else if(pA.second<pB.first) { p.first=pA.first+pB.first-pA.second; p.second=pB.second; }
		else { p.first=pA.first; p.second=pB.second+pA.second-pB.first; }
	}
	else if(strcmp(op_name,"Para")==0)
	{
		p.first=pA.first+pB.first;
		p.second=pA.second+pB.second;
	}
	else if(strcmp(op_name,"Split")==0)
	{
		//if wrong split:
		if(pA.second==0) { p.first=-1; p.second=-1; }
		else if(pB.first%pA.second!=0 || pA.second>pB.first) { p.first=-1; p.second=-1; }
		else { p.first=pA.first; p.second=pB.second; }
	}
	else if(strcmp(op_name,"Merge")==0)
	{
		//if wrong Merge:
		if(pB.first==0) { p.first=-1; p.second=-1; }
		else if(pA.second%pB.first!=0 || pA.second<pB.first) { p.first=-1; p.second=-1; }
		else { p.first=pA.first; p.second=pB.second; }
	}
	else if(strcmp(op_name,"Recurs")==0)
	{
		//if wrong Recurs:
		if(pB.second==0 && pB.first==0) { p.first=-1; p.second=-1; }
		else if(pA.second<pB.first || pA.first<pB.second) { p.first=-1; p.second=-1; }
		else { p.first=pA.first; p.second=pB.second; }
	}

	return p;
}

representation* treeNormal::treeToRepr()
{
	representation* repr=NULL;

	if(strcmp(op_name,"Serie")==0)
	{	repr=new reprSerie(A->treeToRepr(),B->treeToRepr());
	}
	else if(strcmp(op_name,"Para")==0)
	{	repr=new reprPara(A->treeToRepr(),B->treeToRepr());
	}
	else if(strcmp(op_name,"Split")==0)
	{	repr=new reprSplit(A->treeToRepr(),B->treeToRepr());
	}	
	else if(strcmp(op_name,"Merge")==0)
	{	repr=new reprMerge(A->treeToRepr(),B->treeToRepr());
	}
	else if(strcmp(op_name,"Recurs")==0)
	{	repr=new reprRecurs(A->treeToRepr(),B->treeToRepr());
	}

	return repr;
}

treeNormal::~treeNormal()
{

}






