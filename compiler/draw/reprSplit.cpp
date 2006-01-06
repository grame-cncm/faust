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
 
 
 
// reprSplit.cpp

#include "reprSplit.h"
#include <vector>
#include <iostream>
using namespace std;

reprSplit::reprSplit(representation* bA,representation* bB)
{
	A=bA;
	B=bB;
	nom="";

	// heigth:
	hauteur=max(A->getHauteur(),B->getHauteur());
	
	// width:
	largeur=A->getLargeur()+B->getLargeur()+((int)((int)B->getIns().size()/(int)A->getOuts().size())+1)*delta_lbSM;
	
	// ins:
	int i;
	for(i=0;i<(int)A->getIns().size();i++)
		ins.push_back(A->getIns()[i]+0.5*(hauteur-A->getHauteur()));

	// outs:
	for(i=0;i<(int)B->getOuts().size();i++)
		outs.push_back(B->getOuts()[i]+0.5*(hauteur-B->getHauteur()));
//	cout<<"Split cree"<<endl;
}


void reprSplit::draw(device& dev,vector<wire*>& allWires,float x,float y,vector<wire*> wi,vector<wire*> wo,int sens)	
{
	int i,j;
	vector <wire*> oA,iB;
	wire *w;

	if (sens == 1)
	{
		//if wrong split:
		if ((int)A->getOuts().size()==0 || (int)B->getIns().size()%(int)A->getOuts().size()!=0 || (int)A->getOuts().size()>(int)B->getIns().size())
		{
			nb_error++;
			if ((int)A->getOuts().size()==0)
				dev.Error("Wrong Split","Nb outsA = 0",nb_error,x+0.5*largeur,y+0.5*hauteur,largeur);
			else
			{
				if ((int)A->getOuts().size()>(int)B->getIns().size())
					dev.Error("Wrong Split","Nb outsA > Nb insB",nb_error,x+0.5*largeur,y+0.5*hauteur,largeur);
				if ((int)B->getIns().size()%(int)A->getOuts().size()!=0 )
					dev.Error("Wrong Split","Nb insB != k*Nb outsA",nb_error,x+0.5*largeur,y+0.5*hauteur,largeur);
			}
		}
		else
		{
			for(i=0;i<(int)B->getIns().size();i++) // i: B->getIns()
			{
				for(j=0;j<(int)A->getOuts().size();j++) // j:A->getOuts()
				{
					if((i+(int)A->getOuts().size()-j)%(int)A->getOuts().size() == 0)
					{
						w = new wire();
						w->addSeg(x+A->getLargeur(),y+0.5*(hauteur-A->getHauteur())+A->getOuts()[j],x+A->getLargeur()+((int)((int)B->getIns().size()/(int)A->getOuts().size())+1)*delta_lbSM,y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
						w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
						iB.push_back(w);
						allWires.push_back(w);
					}
				}
			}
		}

		A->draw(dev,allWires,x,y+0.5*(hauteur-A->getHauteur()),wi,oA,sens);
		B->draw(dev,allWires,x+A->getLargeur()+((int)((int)B->getIns().size()/(int)A->getOuts().size())+1)*delta_lbSM,y+0.5*(hauteur-B->getHauteur()),iB,wo,sens);
	}
	else // sens -
	{

		//if wrong split:
		if ((int)A->getOuts().size()==0 || (int)B->getIns().size()%(int)A->getOuts().size()!=0 || (int)A->getOuts().size()>(int)B->getIns().size())
		{
			nb_error++;
			if ((int)A->getOuts().size()==0)
				dev.Error("Wrong Split","Nb outsA = 0",nb_error,x-0.5*largeur,y-0.5*hauteur,largeur);
			else
			{
				if ((int)A->getOuts().size()>(int)B->getIns().size())
					dev.Error("Wrong Split","Nb outsA > Nb insB",nb_error,x-0.5*largeur,y-0.5*hauteur,largeur);
				if ((int)B->getIns().size()%(int)A->getOuts().size()!=0 )
					dev.Error("Wrong Split","Nb insB != k*Nb outsA",nb_error,x-0.5*largeur,y-0.5*hauteur,largeur);
			}
		}
		else
		{
			for(i=0;i<(int)B->getIns().size();i++) // i: B->getIns()
			{
				for(j=0;j<(int)A->getOuts().size();j++) // j:A->getOuts()
				{
					if((i+(int)A->getOuts().size()-j)%(int)A->getOuts().size() == 0)
					{
						w = new wire();
						w->addSeg(x-A->getLargeur(),y-0.5*(hauteur-A->getHauteur())-A->getOuts()[j],x-A->getLargeur()-((int)((int)B->getIns().size()/(int)A->getOuts().size())+1)*delta_lbSM,y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);
						w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
						iB.push_back(w);
						allWires.push_back(w);
					}
				}
			}
		}

		A->draw(dev,allWires,x,y-0.5*(hauteur-A->getHauteur()),wi,oA,sens);
		B->draw(dev,allWires,x-A->getLargeur()-((int)((int)B->getIns().size()/(int)A->getOuts().size())+1)*delta_lbSM,y-0.5*(hauteur-B->getHauteur()),iB,wo,sens);
	}

	//cout<<"Split dessine"<<endl;
}

reprSplit::~reprSplit()
{
}


