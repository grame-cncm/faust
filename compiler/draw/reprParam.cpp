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
 
 
 
// reprParam.cpp

#include "reprParam.h"
#include <iostream>
#include <string.h>
#include <complex> //for arctan()

reprParam::reprParam(const char* _nom,float l,float h,vector<float> i,vector<float> o) // in and out param
{
	nom=_nom;
	largeur=l;
	hauteur=h;
	ins=i;
	outs=o;
}

void reprParam::draw(device& dev,vector<wire*>& allWires,float x,float y,vector<wire*> wi,vector<wire*> wo,int sens)
{
	int i,j;
	float pente=0;
	if(sens == 1) //sens +
	{
	       	dev.rect(x,y,largeur,hauteur);
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

	       	for(i=0;i<(int)outs.size();i++)
			dev.rond(x+largeur,y+outs[i],rayonIO);

		   	// mark for sens:
	       	dev.markSens(x,y,sens);

	       	// display name:
	       	dev.text(x+largeur/2,y+hauteur/2,nom);
     }
	else //sens -
	{
	       	dev.rect(x-largeur,y-hauteur,largeur,hauteur);
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

	       	for(i=0;i<(int)outs.size();i++)
	        	dev.rond(x-largeur,y-outs[i],rayonIO);

	       	// mark for sens:
			dev.markSens(x,y,sens);

	       	// display name:
	       	dev.text(x-largeur/2,y-hauteur/2,nom);     
	}

	cout<<"Param dessine"<<endl;
}

