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
 
 
 
/*******************************************************************

						representation.h

********************************************************************/


#if !defined REPRESENTATION_H
#define REPRESENTATION_H

#include "device.h"
#include "wire.h"
#include <vector>
using namespace std;

// constant values linked to the geometric construction:

const float delta_hb = 5;       // height between two blocks
const float delta_hf = 5;       // height between two wires
const float delta_lf = 5;	    // width between two wires
const float delta_lb = 5;		// width between two blocks
const float delta_lbSM = 7;	    // width between two blocks for split ans merge
const float cote_carre = 2.5;   // square for the recursion
const float rayonIO = 2;	    // discs for ins and outs
const float delta_hlabel = 2;	// height added for groups' label

static vector<wire*> allWires;

class representation  
{
	public:
		virtual ~representation() 		{}
	 	virtual void draw(device&,vector<wire*>&,float,float,vector<wire*>,vector<wire*>,int)=0; 
	
		float getHauteur()				{ return hauteur; }
		float getLargeur()				{ return largeur; }
		const char* getNom()			{ return nom; }
		const vector <float>& getIns()	{ return ins; }
		const vector <float>& getOuts()	{ return outs; }
		int getNb_error()				{ return nb_error; }
	
	protected:
		float hauteur;
		float largeur;
		const char* nom;
		vector <float> ins;  //block's ins
		vector <float> outs; //block's outs

		static int nb_error; // errors nomber on not parametric blocks

		float max(float lA,float lB)    {if(lA>lB) return lA; else return lB;}
		float min(float lA,float lB)    {if(lA>lB) return lB; else return lA;}
};

#endif 


