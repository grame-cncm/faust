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
 
 
 
// reprBloc.cpp


#include "reprBloc.h"
#include <vector>
#include <iostream>
#include <complex> //for arctan()

using namespace std;

reprBloc::reprBloc(const char* _nom,float l,float h,vector<float> i,vector<float> o)
{
	nom=_nom;
	hauteur=h;
	largeur=l;
	ins=i;
	outs=o;

//	cout<<"Bloc cree"<<endl;
}

void reprBloc::draw(device& dev,vector<wire*>& allWires,float x,float y,vector<wire*> wi,vector<wire*> wo,int sens)
{
	int i,j;
	wire* w;

	if(sens == 1) //sens +
	{
		if(nom[0]=='_' && nom[1]==0) 
		{ 
			if((int)wi.size()!=0 && (int)wo.size()!=0)
			{	
				wo[0]->addSeg(x, y+ins[0], x+largeur, y+outs[0]);
				
				if(wi[0]->getCarre().x1>0)
					wo[0]->setCarre(wi[0]->getCarre().x1,wi[0]->getCarre().x2,wi[0]->getCarre().y1);

				for(i=0;i<wi[0]->getLinkedToSize();i++)
					wo[0]->addLinkedTo(wi[0]->getLinkedTo(i));
				for(i=0;i<(int)wi[0]->getLSeg().size();i++)
					wo[0]->addSeg(wi[0]->getLSeg()[i]);

				wo[0]->addLinkedTo(wi[0]);
				wi[0]->setLinked(true);

   			}
			else 
			{
				if((int)wi.size()==0 && (int)wo.size()!=0)
					wo[0]->addSeg(x, y+ins[0], x+largeur, y+outs[0]);
				if((int)wo.size()==0 && (int)wi.size()!=0)
				{
					wi[0]->addSeg(x, y+ins[0], x+largeur, y+outs[0]);
					wi[0]->setLastSegment(wi[0]->getLSeg()[(int)wi[0]->getLSeg().size()-1]);
				}
				if((int)wo.size()==0 && (int)wi.size()==0)
				{
					w = new wire();
					w->addSeg(x, y+ins[0], x+largeur, y+outs[0]);
					allWires.push_back(w);
				}
			}
			
		} else if (nom[0]=='!' && nom[1]==0) { 
		
			if ((int)wo.size()>0) wi[0]->setBlockEndCut(true); 
			
		} else {
			dev.rect(x,y,largeur,hauteur);
				
			//disks and arrows for ins and outs:
			
			// ins:
			float pente=0;
			for(i=0;i<(int)ins.size();i++)
			{
				dev.rond(x,y+ins[i],rayonIO);
			
				if(wi.size() != 0)
				{
					if(wi[i]->getLinkedToSize() != 0 && (int)wi[i]->getLSeg().size()==1) // -> merge
						for(j=0;j<wi[i]->getLinkedToSize();j++)
						{
							if(wi[i]->getLinkedTo(j)->getLastSegment().x2-wi[i]->getLinkedTo(j)->getLastSegment().x1 != 0)
							{
								pente=(wi[i]->getLinkedTo(j)->getLastSegment().y2-wi[i]->getLinkedTo(j)->getLastSegment().y1)/(wi[i]->getLinkedTo(j)->getLastSegment().x2-wi[i]->getLinkedTo(j)->getLastSegment().x1);
								dev.fleche(x,y+ins[i],atan(pente)*360/(2*3.1415926),sens);
							}
						}	
					else if(wi[i]->getLastSegment().x2-wi[i]->getLastSegment().x1 != 0)
					{
						pente=(wi[i]->getLastSegment().y2-wi[i]->getLastSegment().y1)/(wi[i]->getLastSegment().x2-wi[i]->getLastSegment().x1);
						dev.fleche(x,y+ins[i],atan(pente)*360/(2*3.1415926),sens);
					}	
				}
			}

			//outs:
			for(i=0;i<(int)outs.size();i++)
				dev.rond(x+largeur,y+outs[i],rayonIO);
				
			// mark for sens:
			dev.markSens(x,y,sens);

			// display name:
			dev.text(x+largeur/2,y+hauteur/2,nom);
		}
	}
	else //sens -
	{
		if(nom[0]=='_' && nom[1]==0) 
		{ 
			if((int)wi.size()!=0 && (int)wo.size()!=0)
			{	
				wo[0]->addSeg(x, y-ins[0], x-largeur, y-outs[0]);
				
				if(wi[0]->getCarre().x1>0)
					wo[0]->setCarre(wi[0]->getCarre().x1,wi[0]->getCarre().x2,wi[0]->getCarre().y1);

				for(i=0;i<(int)wi[0]->getLinkedToSize();i++)
					wo[0]->addLinkedTo(wi[0]->getLinkedTo(i));
				
				for(i=0;i<(int)wi[0]->getLSeg().size();i++)
					wo[0]->addSeg(wi[0]->getLSeg()[i]);

				wo[0]->addLinkedTo(wi[0]);
				wi[0]->setLinked(true);
			}
			else 
			{
				if((int)wi.size()==0 && (int)wo.size()!=0)
					wo[0]->addSeg(x, y-ins[0], x-largeur, y-outs[0]);
				if((int)wo.size()==0 && (int)wi.size()!=0)
				{
					wi[0]->addSeg(x, y-ins[0], x-largeur, y-outs[0]);
					wi[0]->setLastSegment(wi[0]->getLSeg()[(int)wi[0]->getLSeg().size()-1]);
				}
				if((int)wo.size()==0 && (int)wi.size()==0)
				{
					w = new wire();
					w->addSeg(x, y-ins[0], x-largeur, y-outs[0]);
					allWires.push_back(w);
				}
			}
			
		}
		else if (nom[0]=='!' && nom[1]==0) { wi[0]->setBlockEndCut(true);}
		else
		{
			dev.rect(x-largeur,y-hauteur,largeur,hauteur);
			
			//disks and arrows for ins and outs:
			
			// ins:
			float pente=0;
			for(i=0;i<(int)ins.size();i++)
			{
				dev.rond(x,y-ins[i],rayonIO);
			
				if(wi.size() != 0)
				{
					if(wi[i]->getLinkedToSize() != 0 && (int)wi[i]->getLSeg().size()==1) // -> merge
						for(j=0;j<wi[i]->getLinkedToSize();j++)
						{
							if(wi[i]->getLinkedTo(j)->getLastSegment().x2-wi[i]->getLinkedTo(j)->getLastSegment().x1 != 0)
							{
								pente=(wi[i]->getLinkedTo(j)->getLastSegment().y2-wi[i]->getLinkedTo(j)->getLastSegment().y1)/(wi[i]->getLinkedTo(j)->getLastSegment().x2-wi[i]->getLinkedTo(j)->getLastSegment().x1);
								dev.fleche(x,y-ins[i],atan(pente)*360/(2*3.1415926),sens);
							}
						}	
					else if(wi[i]->getLastSegment().x2-wi[i]->getLastSegment().x1 != 0)
					{
						pente=(wi[i]->getLastSegment().y2-wi[i]->getLastSegment().y1)/(wi[i]->getLastSegment().x2-wi[i]->getLastSegment().x1);
						dev.fleche(x,y-ins[i],atan(pente)*360/(2*3.1415926),sens);
					}
				}
			}
			
			// outs:
			for(i=0;i<(int)outs.size();i++)
				dev.rond(x-largeur,y-outs[i],rayonIO);

			// mark for sens:
			dev.markSens(x,y,sens);

			// display name:
			dev.text(x-largeur/2,y-hauteur/2,nom);
		}
	}

	cout<<"Bloc dessine"<<endl;
}


reprBloc::~reprBloc()
{

}


