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
 
 
 
// reprMerge.cpp

#include "reprMerge.h"
#include <vector>
#include <iostream>
using namespace std;


reprMerge::reprMerge(representation* bA,representation* bB)
{
	A=bA;
	B=bB;
	nom="";
	
	// heigth:
	hauteur=max(A->getHauteur(),B->getHauteur());

	// width:
	largeur=A->getLargeur()+B->getLargeur()+((int)((int)A->getOuts().size()/(int)B->getIns().size())+1)*delta_lbSM;
			
	// ins:
	int i;
	for(i=0;i<(int)A->getIns().size();i++)
		ins.push_back(A->getIns()[i]+0.5*(hauteur-A->getHauteur()));

	// outs:
	for(i=0;i<(int)B->getOuts().size();i++)
		outs.push_back(B->getOuts()[i]+0.5*(hauteur-B->getHauteur()));

//	cout<<"Merge cree"<<endl;
}


void reprMerge::draw(device& dev,vector<wire*>& allWires,float x,float y,vector<wire*> wi,vector<wire*> wo,int sens)	
{
	int i,j;
	vector <wire*> oA,iB;
	wire *w,*wtoB;

	if(sens == 1)
	{
		//if wrong merge:
		if ((int)B->getIns().size()==0 || (int)A->getOuts().size()%(int)B->getIns().size()!=0 || (int)A->getOuts().size()<(int)B->getIns().size())
		{
			nb_error++;
			if ((int)B->getIns().size()==0)
				dev.Error("Wrong Merge","Nb insB = 0",nb_error,x+0.5*largeur,y+0.5*hauteur,largeur);
			else
			{
				if ((int)A->getOuts().size()<(int)B->getIns().size() )
					dev.Error("Wrong Merge","Nb outsA < Nb insB",nb_error,x+0.5*largeur,y+0.5*hauteur,largeur);
				if ((int)A->getOuts().size()%(int)B->getIns().size()!=0 )
					dev.Error("Wrong Merge","Nb outsA != k*Nb insB",nb_error,x+0.5*largeur,y+0.5*hauteur,largeur);
			}
		}
		else
		{
			for(i=0;i<(int)A->getOuts().size();i++) // i: A->getOuts()
			{
				for(j=0;j<(int)B->getIns().size();j++) // j:B->getIns()
				{
					if((i+(int)B->getIns().size()-j)%(int)B->getIns().size() == 0)
					{
						w = new wire();
						w->addSeg(x+A->getLargeur(),y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i],x+A->getLargeur()+((int)((int)A->getOuts().size()/(int)B->getIns().size())+1)*delta_lbSM,y+0.5*(hauteur-B->getHauteur())+B->getIns()[j]);
						w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
						w->setLinked(true);
						if(i<(int)B->getIns().size())
						{
							wtoB = new wire();
							wtoB->addSeg(x+A->getLargeur(),y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i],x+A->getLargeur(),y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i]);
							iB.push_back(wtoB);
							allWires.push_back(wtoB);
						}
						iB[j]->addLinkedTo(w);
						oA.push_back(w);
						allWires.push_back(w);
					}
				}
			}
		}

		A->draw(dev,allWires,x,y+0.5*(hauteur-A->getHauteur()),wi,oA,sens);
		B->draw(dev,allWires,x+A->getLargeur()+((int)((int)A->getOuts().size()/(int)B->getIns().size())+1)*delta_lbSM,y+0.5*(hauteur-B->getHauteur()),iB,wo,sens);
	}
	else //sens -
	{
		//if wrong merge:
		if ((int)B->getIns().size()==0 || (int)A->getOuts().size()%(int)B->getIns().size()!=0 || (int)A->getOuts().size()<(int)B->getIns().size())
		{
			nb_error++;
			if ((int)B->getIns().size()==0)
				dev.Error("Wrong Merge","Nb insB = 0",nb_error,x-0.5*largeur,y-0.5*hauteur,largeur);
			else
			{
				if ((int)A->getOuts().size()<(int)B->getIns().size() )
					dev.Error("Wrong Merge","Nb outsA < Nb insB",nb_error,x-0.5*largeur,y-0.5*hauteur,largeur);
				if ((int)A->getOuts().size()%(int)B->getIns().size()!=0 )
					dev.Error("Wrong Merge","Nb outsA != k*Nb insB",nb_error,x-0.5*largeur,y-0.5*hauteur,largeur);
			}
		}
		else
		{
			for(i=0;i<(int)A->getOuts().size();i++) // i: A->getOuts()
			{
				for(j=0;j<(int)B->getIns().size();j++) // j:B->getIns()
				{

					if((i+(int)B->getIns().size()-j)%(int)B->getIns().size() == 0)
					{
						w = new wire();
						w->addSeg(x-A->getLargeur(),y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i],x-A->getLargeur()-((int)A->getOuts().size()/(int)B->getIns().size()+1)*delta_lbSM,y-0.5*(hauteur-B->getHauteur())-B->getIns()[j]);
						w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
						w->setLinked(true);
						if(i<(int)B->getIns().size())
						{
							wtoB = new wire();
							wtoB->addSeg(x-A->getLargeur(),y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i],x-A->getLargeur(),y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i]);
							iB.push_back(wtoB);
							allWires.push_back(wtoB);
						}
						iB[j]->addLinkedTo(w);
						oA.push_back(w);
						allWires.push_back(w);
					}
				}
			}
		}
		A->draw(dev,allWires,x,y-0.5*(hauteur-A->getHauteur()),wi,oA,sens);
		B->draw(dev,allWires,x-A->getLargeur()-((int)A->getOuts().size()/(int)B->getIns().size()+1)*delta_lbSM,y-0.5*(hauteur-B->getHauteur()),iB,wo,sens);
	}

	cout<<"Merge dessine"<<endl;
}


reprMerge::~reprMerge()
{
}



