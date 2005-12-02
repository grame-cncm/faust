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
 
 
 

// construction des representations graphiques


#include <stdio.h>
#include <string.h>
#include <string>
#include "boxes.hh"
#include "ppbox.hh"
#include "prim2.hh"

#include <vector>
#include "reprLib.h"
#include "devLib.h"
#include "treeLib.h"
#include "drawblock.hh"
#include "constrFonctions.h"
#include "ppbox.hh"
#include "xtended.hh"
#include "eval.hh"

#include <ostream>
#include <sstream>

using namespace std;

treeRepr* graphicBlockDiagram (Tree bd);
treeRepr* graphicPrim (int i);
treeRepr* graphicPrim (float f);
treeRepr* graphicPrim (const char* name, int ins, int outs);


void drawBlockDiagram(Tree bd, const char* dev)
{
	Tree		id;
	treeRepr* 	tR =  (getDefNameProperty(bd, id)) ? graphicBlockDiagram(bd) : new treeGroup(graphicBlockDiagram(bd), "process");
	if(find_config_param(tR))
	{
		representation* ENDrepr = tR->treeToRepr();
		draw_All(ENDrepr, dev);  // dev doit etre "PS" ou "SVG"
	}
	else
	{
		cout<<endl<<"Representation impossible."<<endl<<endl;
	}
}

treeRepr* graphicUI(Tree t)
{
	stringstream 	s;
	s << boxpp(t);
	
	return graphicPrim(strdup(s.str().c_str()), 0, 1);
}

treeRepr* bargraph(Tree t)
{
	stringstream 	s;
	s << boxpp(t);
	
	return graphicPrim(strdup(s.str().c_str()), 1, 1);
}

treeRepr* graphicInputSlot(Tree a)
{
	Tree id; assert(getDefNameProperty(a, id));
	stringstream s; s << boxpp(id);
	return graphicPrim(strdup(s.str().c_str()), 1, 0);
}

treeRepr* graphicOutputSlot(Tree a)
{
	Tree id; assert(getDefNameProperty(a, id));
	stringstream s; s << boxpp(id);
	return graphicPrim(strdup(s.str().c_str()), 0, 1);
}

treeRepr* graphicAbstraction(treeRepr* x, Tree t)
{
	Tree 	a,b;
	//Tree 	id;
	//bool	isnamed = getDefNameProperty(t, id);

	while (isBoxSymbolic(t,a,b)) {
		x = new treeNormal("Para", x, graphicInputSlot(a));
		t = b;
	}

	//if (isnamed) {
		return new treeNormal("Serie", x, graphicBlockDiagram(t));
	//} else {
	//	return new treeGroup(new treeNormal("Serie", x, graphicBlockDiagram(t)), "abstraction");
	//} 
}

static treeRepr* realGraphicBlockDiagram(Tree t);

treeRepr* graphicBlockDiagram(Tree t)
{
	
	Tree	id;
	if (getDefNameProperty(t, id) && ! isBoxSlot(t)) {
		stringstream 	s; s << boxpp(id);
		return new treeGroup(realGraphicBlockDiagram(t), strdup(s.str().c_str()));
	} else {
		return realGraphicBlockDiagram(t);
	}		
}


static treeRepr* realGraphicBlockDiagram(Tree t)
{
	Tree a, b, ff, l, type,name,file;
	int		i;
	float	r;
	prim0	p0;
	prim1	p1;
	prim2	p2;
	prim3	p3;
	prim4	p4;
	prim5	p5;
	
	
	xtended* xt = (xtended*)getUserData(t);
	
	if (xt)	{
		return graphicPrim(xt->name(), xt->arity(), 1);
	}
		
	else if (isBoxSlot(t, &i))		{ 
		return graphicOutputSlot(t);
		//char c[64]; snprintf(c, 63, "slot(%d)",i);
		//return graphicPrim(strdup(c), 0, 1); 
	}
	else if (isBoxSymbolic(t,a,b))	{
		Tree 	id;
		if (getDefNameProperty(t, id)) {
			return graphicAbstraction(graphicInputSlot(a), b); 
		} else {
			return new treeGroup(graphicAbstraction(graphicInputSlot(a), b), "Abstraction"); 
		}
#if 0
		assert(isBoxSlot(a,&i));
		char c[64]; snprintf(c, 63, "slot(%d)",i);
//		return new treeNormal("Serie", graphicPrim(strdup(c), 1, 0), graphicBlockDiagram(b)); 
		return new treeGroup(new treeNormal("Serie", graphicPrim(strdup(c), 1, 0), graphicBlockDiagram(b)), "abstraction"); 
#endif
	}
		
	else if (isBoxVBargraph(t))		{return bargraph(t); }
	else if (isBoxHBargraph(t))		{return bargraph(t); }
	
	//--------------------------------------------------------
	else if (isBoxInt(t, &i))		{ return graphicPrim(i); }
	else if (isBoxReal(t, &r)) 		{ return graphicPrim(r); } 
	else if (isBoxWire(t)) 			{ return graphicPrim("_", 1, 1); }
	else if (isBoxCut(t)) 			{ return graphicPrim("!", 1, 0);  } 
	
	else if (isBoxPrim0(t, &p0)) 	{ return graphicPrim(prim0name(p0), 0, 1); } 
	else if (isBoxPrim1(t, &p1)) 	{ return graphicPrim(prim1name(p1), 1, 1); } 
	else if (isBoxPrim2(t, &p2)) 	{ return graphicPrim(prim2name(p2), 2, 1);  } 
	else if (isBoxPrim3(t, &p3)) 	{ return graphicPrim(prim3name(p3), 3, 1);  } 
	else if (isBoxPrim4(t, &p4)) 	{ return graphicPrim(prim4name(p4), 4, 1);  } 
	else if (isBoxPrim5(t, &p5)) 	{ return graphicPrim(prim5name(p5), 5, 1);  } 
		
	else if (isBoxFFun(t, ff)) 					{ return graphicPrim(ffname(ff), ffarity(ff), 1); } 
	else if (isBoxFConst(t, type,name,file)) 	{ return graphicPrim(tree2str(name), 0, 1); } 

	else if (isBoxButton(t)) 		{ return graphicUI(t); } 
	else if (isBoxCheckbox(t)) 		{ return graphicUI(t); } 
	else if (isBoxVSlider(t)) 		{ return graphicUI(t); } 
	else if (isBoxHSlider(t)) 		{ return graphicUI(t); } 
	else if (isBoxNumEntry(t)) 		{ return graphicUI(t); } 
	
	else if (isBoxVGroup(t,l,a))	{ return new treeGroup(graphicBlockDiagram(a), tree2str(l)); }
	else if (isBoxHGroup(t,l,a))	{ return new treeGroup(graphicBlockDiagram(a), tree2str(l)); }
	else if (isBoxTGroup(t,l,a))	{ return new treeGroup(graphicBlockDiagram(a), tree2str(l)); }

	else if (isBoxSeq(t, a, b)) 	{ return new treeNormal("Serie",graphicBlockDiagram(a), graphicBlockDiagram(b)); }
	else if (isBoxPar(t, a, b)) 	{ return new treeNormal("Para",graphicBlockDiagram(a), graphicBlockDiagram(b)); }
	else if (isBoxSplit(t, a, b)) 	{ return new treeNormal("Split",graphicBlockDiagram(a), graphicBlockDiagram(b)); }
	else if (isBoxMerge(t, a, b)) 	{ return new treeNormal("Merge",graphicBlockDiagram(a), graphicBlockDiagram(b)); }
	else if (isBoxRec(t, a, b)) 	{ return new treeNormal("Recurs",graphicBlockDiagram(a), graphicBlockDiagram(b)); }

	// pour parametrable: return new treeParam(const char* nom,int nb_i_min,int nb_i_Max,int nb_o_min,int nb_o_Max);


	else {

		fprintf(stderr, "Internal Error, box expression not recognized : "); print(t, stderr); fprintf(stderr, "\n");
		exit(1);

	}
}	
		

treeRepr* graphicPrim (int i)
{
	char name[256];
	snprintf(name, 256, "%d", i);
	return graphicPrim(strdup(name), 0, 1);
}


treeRepr* graphicPrim (float f)
{
	char name[256];
	snprintf(name, 256, "%f", f);
	return graphicPrim(strdup(name), 0, 1);
}


static int length (const char* s)
{
	int i = 0;
	while (s[i] != 0) i++;
	return i;
}
 

treeRepr* graphicPrim (const char* name, int ins, int outs)
{
	if ( (name[0]=='_' || name[0]=='_') && name[1]==0 ) { 
		// Special case for cut and wire which have a width of 0
		int MARGE = 8;
		int m = (ins>outs) ? ins : outs;
		int c = MARGE*(m+1);
		int	i;
				
		vector<float> ipos(ins);
		vector<float> opos(outs);

		for (i = 0; i < ins; i++) 	ipos[i] = c/ins * (i+0.5);
		for (i = 0; i < outs; i++) 	opos[i] = c/outs * (i+0.5);
		
		return new treeBloc(name, 0, c, ipos, opos);
		
	} else {
		int Hsize = 5;
		const int MARGE = 8;
		int m = (ins>outs) ? ins : outs;
		int c = MARGE*(m+1);
		int	i;
				
		vector<float> ipos(ins);
		vector<float> opos(outs);
		
		/*
		char* name2 = strdup(name);
	
		if(name2[0]=='!' && name2[1]==0)  // Wire
		{
			c=0;
			Hsize=0;
		}
		*/
		for (i = 0; i < ins; i++) 	ipos[i] = c/ins * (i+0.5);
		for (i = 0; i < outs; i++) 	opos[i] = c/outs * (i+0.5);
		
		return new treeBloc(name, max(24,MARGE+Hsize*length(name)), c, ipos, opos);
	}
}
	

