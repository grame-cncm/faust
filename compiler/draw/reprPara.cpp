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
 
 
 
// reprPara.cpp

#include "reprPara.h"
#include <vector>
#include <iostream>
using namespace std;


reprPara::reprPara(representation* bA,representation* bB)
{
	A=bA;
	B=bB;
	nom="";

	// Test if A or B is a cut block:
	int cut=0;
	if ( (A->getNom()[0]=='!' && A->getNom()[1]==0) || (B->getNom()[0]=='!' && B->getNom()[1]==0))  
		cut=1;

	// heigth:	
	hauteur=A->getHauteur()+B->getHauteur() + delta_hb*(1-cut);
	
	// width:
	largeur=max(A->getLargeur(),B->getLargeur());
			
	// ins:
	int i;

	for(i=0;i<(int)A->getIns().size();i++)
		ins.push_back(A->getIns()[i]);
	
	for(i=0;i<(int)B->getIns().size();i++) 
		ins.push_back(B->getIns()[i]+A->getHauteur()+delta_hb*(1-cut));
	
	// outs:
	for(i=0;i<(int)A->getOuts().size();i++)  
		outs.push_back(A->getOuts()[i]);
	for(i=0;i<(int)B->getOuts().size();i++)  
		outs.push_back(B->getOuts()[i]+A->getHauteur()+delta_hb*(1-cut));

//	cout<<"Para cree"<<endl;
}

void reprPara::draw(device& dev,vector<wire*>& allWires,float x,float y,vector<wire*> wi,vector<wire*> wo,int sens)	
{
	int i;
	vector <wire*> iA,oA,iB,oB;
	wire *w;


	// Tests if A or B is a cut block:
	int cut=0;
	if (((int)A->getIns().size()==1 && A->getIns()[0]==0) || ((int)B->getIns().size()==1 && B->getIns()[0]==0))  
		cut=1;

	if(sens == 1)
	{
		if(A->getLargeur()<B->getLargeur())
		{
			if((int)wi.size() != 0)
			{
				for(i=0;i<(int)A->getIns().size();i++)
				{
					wi[i]->addSeg(x,y+ins[i],x+0.5*(largeur-A->getLargeur()),y+ins[i]);
					wi[i]->setLastSegment(wi[i]->getLSeg()[(int)wi[i]->getLSeg().size()-1]);
					iA.push_back(wi[i]);
				}
				for(;i<(int)ins.size();i++)
				{
					iB.push_back(wi[i]);
				}
			}
			else
			{
				for(i=0;i<(int)A->getIns().size();i++)
				{
					w = new wire();
					w->addSeg(x,y+ins[i],x+0.5*(largeur-A->getLargeur()),y+ins[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					iA.push_back(w);
					allWires.push_back(w);
				}
			}
			if((int)wo.size() != 0)
			{
				for(i=0;i<(int)A->getOuts().size();i++)
				{
					wo[i]->addSeg(x+largeur-0.5*(largeur-A->getLargeur()),y+outs[i],x+largeur,y+outs[i]);
					oA.push_back(wo[i]);
				}
				for(;i<(int)outs.size();i++)
				{
					oB.push_back(wo[i]);
				}
			}
			else
			{			
				for(i=0;i<(int)A->getOuts().size();i++)
				{
					w = new wire();
					w->addSeg(x+largeur-0.5*(largeur-A->getLargeur()),y+outs[i],x+largeur,y+outs[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					oA.push_back(w);
					allWires.push_back(w);
				}
			}
		}
		else if(A->getLargeur()>B->getLargeur())
		{
			if((int)wi.size() != 0)
			{
				for(i=0;i<(int)A->getIns().size();i++)
				{
					iA.push_back(wi[i]);
				}
				for(;i<(int)ins.size();i++)
				{
					wi[i]->addSeg(x,y+ins[i],x+0.5*(largeur-B->getLargeur()),y+ins[i]);
					wi[i]->setLastSegment(wi[i]->getLSeg()[(int)wi[i]->getLSeg().size()-1]);
					iB.push_back(wi[i]);
				}
			}
			else
			{
				for(i=(int)A->getIns().size();i<(int)A->getIns().size()+(int)B->getIns().size();i++)
				{
					w = new wire();
					w->addSeg(x,y+ins[i],x+0.5*(largeur-B->getLargeur()),y+ins[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					iB.push_back(w);
					allWires.push_back(w);
				}
			}
			if((int)wo.size() != 0)
			{
				for(i=0;i<(int)A->getOuts().size();i++)
				{
					oA.push_back(wo[i]);
				}
				for(;i<(int)outs.size();i++)
				{
					wo[i]->addSeg(x+largeur-0.5*(largeur-B->getLargeur()),y+outs[i],x+largeur,y+outs[i]);
					oB.push_back(wo[i]);
				}
			}
			else
			{
				for(i=(int)A->getOuts().size();i<(int)A->getOuts().size()+(int)B->getOuts().size();i++)
				{
					w = new wire();
					w->addSeg(x+largeur-0.5*(largeur-B->getLargeur()),y+outs[i],x+largeur,y+outs[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					oB.push_back(w);
					allWires.push_back(w);
				}
			}
		}
		else   //A->getLargeur()=B->getLargeur()
		{
			for(i=0;i<(int)A->getIns().size();i++)
			{
				if((int)wi.size()!=0)
					iA.push_back(wi[i]);
			}
			for(;i<(int)ins.size();i++)
			{
				if((int)wi.size()!=0)
					iB.push_back(wi[i]);
			}
			for(i=0;i<(int)A->getOuts().size();i++)
			{
				if((int)wo.size()!=0)
					oA.push_back(wo[i]);
			}
			for(;i<(int)outs.size();i++)
			{
				if((int)wo.size()!=0)
					oB.push_back(wo[i]);
			}
		}
	
		A->draw(dev,allWires,x+0.5*(largeur-A->getLargeur()),y,iA,oA,sens);
		B->draw(dev,allWires,x+0.5*(largeur-B->getLargeur()),y+A->getHauteur()+delta_hb*(1-cut),iB,oB,sens);
	}
	else // sens -
	{
		if(A->getLargeur()<B->getLargeur())
		{
			if((int)wi.size() != 0)
			{
				for(i=0;i<(int)A->getIns().size();i++)
				{
					wi[i]->addSeg(x,y-ins[i],x-0.5*(largeur-A->getLargeur()),y-ins[i]);
					wi[i]->setLastSegment(wi[i]->getLSeg()[(int)wi[i]->getLSeg().size()-1]);
					iA.push_back(wi[i]);
				}
				for(;i<(int)ins.size();i++)
				{
					iB.push_back(wi[i]);
				}
			}
			else
			{
				for(i=0;i<(int)A->getIns().size();i++)
				{
					w = new wire();
					w->addSeg(x,y-ins[i],x-0.5*(largeur-A->getLargeur()),y-ins[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					iA.push_back(w);
					allWires.push_back(w);
				}
			}
			if((int)wo.size() != 0)
			{
				for(i=0;i<(int)A->getOuts().size();i++)
				{
					wo[i]->addSeg(x-largeur+0.5*(largeur-A->getLargeur()),y-outs[i],x-largeur,y-outs[i]);
					oA.push_back(wo[i]);
				}
				for(;i<(int)outs.size();i++)
				{
					oB.push_back(wo[i]);
				}
			}
			else
			{			
				for(i=0;i<(int)A->getOuts().size();i++)
				{
					w = new wire();
					w->addSeg(x-largeur+0.5*(largeur-A->getLargeur()),y-outs[i],x-largeur,y-outs[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					oA.push_back(w);
					allWires.push_back(w);
				}
			}
		}
		else if(A->getLargeur()>B->getLargeur())
		{
			if((int)wi.size() != 0)
			{
				for(i=0;i<(int)A->getIns().size();i++)
				{
					iA.push_back(wi[i]);
				}
				for(;i<(int)ins.size();i++)
				{
					wi[i]->addSeg(x,y-ins[i],x-0.5*(largeur-B->getLargeur()),y-ins[i]);
					wi[i]->setLastSegment(wi[i]->getLSeg()[(int)wi[i]->getLSeg().size()-1]);
					iB.push_back(wi[i]);
				}
			}
			else
			{
				for(i=(int)A->getIns().size();i<(int)A->getIns().size()+(int)B->getIns().size();i++)
				{
					w = new wire();
					w->addSeg(x,y-ins[i],x-0.5*(largeur-B->getLargeur()),y-ins[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					iB.push_back(w);
					allWires.push_back(w);
				}
			}
			if((int)wo.size() != 0)
			{
				for(i=0;i<(int)A->getOuts().size();i++)
				{
					oA.push_back(wo[i]);
				}
				for(;i<(int)outs.size();i++)
				{
					wo[i]->addSeg(x-largeur+0.5*(largeur-B->getLargeur()),y-outs[i],x-largeur,y-outs[i]);
					oB.push_back(wo[i]);
				}
			}
			else
			{
				for(i=(int)A->getOuts().size();i<(int)A->getOuts().size()+(int)B->getOuts().size();i++)
				{
					w = new wire();
					w->addSeg(x-largeur+0.5*(largeur-B->getLargeur()),y-outs[i],x-largeur,y-outs[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					oB.push_back(w);
					allWires.push_back(w);
				}
			}
		}
		else   //A->getLargeur()=B->getLargeur()
		{
			for(i=0;i<(int)A->getIns().size();i++)
			{
				if((int)wi.size()!=0)
					iA.push_back(wi[i]);
			}
			for(;i<(int)ins.size();i++)
			{
				if((int)wi.size()!=0)
					iB.push_back(wi[i]);
			}
			for(i=0;i<(int)A->getOuts().size();i++)
			{
				if((int)wo.size()!=0)
					oA.push_back(wo[i]);
			}
			for(;i<(int)outs.size();i++)
			{
				if((int)wo.size()!=0)
					oB.push_back(wo[i]);
			}
		}

		A->draw(dev,allWires,x-0.5*(largeur-A->getLargeur()),y,iA,oA,sens);
		B->draw(dev,allWires,x-0.5*(largeur-B->getLargeur()),y-A->getHauteur()-delta_hb*(1-cut),iB,oB,sens);
	 }
		//cout<<"Para dessine"<<endl;
}


reprPara::~reprPara()
{
}




