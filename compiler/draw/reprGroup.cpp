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
 
 
 
// reprGroup.cpp

#include "reprGroup.h"
#include <iostream>
#include <string.h>


reprGroup::reprGroup(representation* bA,const char* label)
{
	A=bA;
	nom="";
	hauteur=A->getHauteur()+2*delta_hb+delta_hlabel;
	largeur=A->getLargeur()+2*delta_lb;
	
	int i;
	for(i=0;i<(int)A->getIns().size();i++)  
		ins.push_back(A->getIns()[i]+delta_hlabel+delta_hb);
	for(i=0;i<(int)A->getOuts().size();i++)  
		outs.push_back(A->getOuts()[i]+delta_hlabel+delta_hb);

	nom=label;

//	cout<<"Groupe cree"<<endl;
}

void reprGroup::draw(device& dev,vector<wire*>& allWires,float x,float y,vector<wire*> wi,vector<wire*> wo,int sens)
{
	int i;
	vector <wire*> iA,oA;
	wire*	w;
	float 	marge_label = 3.0;
	//float l_letter=(float)3.5;
	float 	wletter = 3.75;
	float	wlabel = strlen(nom) * wletter;

	if(sens==1)
	{
		dev.dasharray(x,y+delta_hlabel,x,y+hauteur);
		dev.dasharray(x,y+hauteur,x+largeur,y+hauteur);
		dev.dasharray(x+largeur,y+delta_hlabel,x+largeur,y+hauteur);
		// redefinition du positionnement du label
		dev.dasharray(x, y+delta_hlabel, x+delta_lb, y+delta_hlabel);
		dev.label(x+delta_lb, y+delta_hlabel, nom);
		dev.dasharray(min(x + delta_lb + wlabel + marge_label, x + largeur), y + delta_hlabel,
					 x + largeur, y + delta_hlabel);
#if 0
		dev.dasharray(x,y+delta_hlabel,x+largeur/8-marge_label,y+delta_hlabel);
		dev.label(x+largeur/8,y+delta_hlabel,nom);
		dev.dasharray(x+largeur/8+strlen(nom)*l_letter+marge_label,y+delta_hlabel,x+largeur,y+delta_hlabel);
#endif
		if(wi.size() != 0)
			for(i=0;i<(int)ins.size();i++) // i:ins
			{
				wi[i]->addSeg(x,y+ins[i],x+delta_lb,y+ins[i]);
				wi[i]->setLastSegment(wi[i]->getLSeg()[(int)wi[i]->getLSeg().size()-1]);
				iA.push_back(wi[i]);
			}
		else
			for(i=0;i<(int)ins.size();i++) // i:ins
			{
				w = new wire();
				w->addSeg(x,y+ins[i],x+delta_lb,y+ins[i]);
				w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
				iA.push_back(w);
				allWires.push_back(w);
			}


		if(wo.size() != 0)
			for(i=0;i<(int)outs.size();i++) // i:outs
			{
				wo[i]->addSeg(x+largeur-delta_lb,y+outs[i],x+largeur,y+outs[i]);
				oA.push_back(wo[i]);
			}
		else
			for(i=0;i<(int)outs.size();i++) // i:outs
			{
					w = new wire();
					w->addSeg(x+largeur-delta_lb,y+outs[i],x+largeur,y+outs[i]);
					w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
					oA.push_back(w);
					allWires.push_back(w);
			}

		A->draw(dev,allWires,x+delta_lb,y+delta_hb+delta_hlabel,iA,oA,sens);
	}
	else //sens -
	{
		dev.dasharray(x,y-delta_hlabel,x,y-hauteur);
		dev.dasharray(x,y-hauteur,x-largeur,y-hauteur);
		dev.dasharray(x-largeur,y-delta_hlabel,x-largeur,y-hauteur);

		dev.dasharray(x, y - delta_hlabel, x - delta_lb, y - delta_hlabel);
		dev.label(x -  delta_lb - wlabel - marge_label, y - delta_hlabel, nom);
		dev.dasharray(x - largeur, y - delta_hlabel, x - delta_lb - wlabel, y - delta_hlabel);
#if 0
		dev.dasharray(x, y+delta_hlabel, x+delta_lb, y+delta_hlabel);
		dev.label(x+delta_lb, y+delta_hlabel, nom);
		dev.dasharray(min(x + delta_lb + wlabel + marge_label, x + largeur), y + delta_hlabel,
					 x + largeur, y + delta_hlabel);

		dev.dasharray(x,y-delta_hlabel,x-largeur/8+marge_label,y-delta_hlabel);
		dev.label(x-largeur/8-strlen(nom)*l_letter, y-delta_hlabel, nom);
		dev.dasharray(x-largeur/8-strlen(nom)*l_letter-marge_label,y-delta_hlabel,x-largeur,y-delta_hlabel);
#endif
		if(wi.size() != 0)
			for(i=0;i<(int)ins.size();i++) // i:ins
			{
				wi[i]->addSeg(x,y-ins[i],x-delta_lb,y-ins[i]);
				wi[i]->setLastSegment(wi[i]->getLSeg()[(int)wi[i]->getLSeg().size()-1]);
				iA.push_back(wi[i]);
			}
		else
			for(i=0;i<(int)ins.size();i++) // i:ins
			{
				w = new wire();
				w->addSeg(x,y-ins[i],x-delta_lb,y-ins[i]);
				w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
				iA.push_back(w);
				allWires.push_back(w);
			}
	
		if(wo.size() != 0)
			for(i=0;i<(int)outs.size();i++) // i:outs
			{
				wo[i]->addSeg(x-largeur+delta_lb,y-outs[i],x-largeur,y-outs[i]);
				oA.push_back(wi[i]);
			}
		else
			for(i=0;i<(int)outs.size();i++) // i:outs
			{
					w = new wire();
					w->addSeg(x-largeur+delta_lb,y-outs[i],x-largeur,y-outs[i]);
					w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
					oA.push_back(w);
					allWires.push_back(w);
			}

		A->draw(dev,allWires,x-delta_lb,y-delta_hb-delta_hlabel,iA,oA,sens);
	}

	cout<<"Groupe dessine"<<endl;
}
reprGroup::~reprGroup()
{

}


