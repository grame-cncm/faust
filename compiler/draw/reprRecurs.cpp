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
 
 
 
// reprRecurs.cpp: implementation of the reprRecurs class.
//
//////////////////////////////////////////////////////////////////////

#include "reprRecurs.h"
#include <vector>
#include <iostream>
using namespace std;

reprRecurs::reprRecurs(representation* bA,representation* bB)
{
	A=bA;
	B=bB;
	nom="";	
	// height:
	hauteur=A->getHauteur()+B->getHauteur()+delta_hb;
	
	// width:
	largeur=max(A->getLargeur(),B->getLargeur())+((int)B->getIns().size()+(int)B->getOuts().size()+2)*delta_lf;
	
	// ins:
	int i;
	for(i=0;i<(int)A->getIns().size();i++)	
		if(i+1>(int)B->getOuts().size())
			ins.push_back(A->getIns()[i]+B->getHauteur()+delta_hb);
	
	// outs:
	for(i=0;i<(int)A->getOuts().size();i++)  
		outs.push_back(A->getOuts()[i]+B->getHauteur()+delta_hb);
	
//	cout<<"Recursion cree"<<endl;
}

void reprRecurs::draw(device& dev,vector<wire*>& allWires,float x,float y,vector<wire*> wi,vector<wire*> wo,int sens)	
{
	int i;
	vector <wire*> iA,oA,iB,oB;
	wire *w,*wtiB,*wtoA,*wout;

	if (sens ==1)
	{
		//if wrong recursion:
		if ((int)A->getOuts().size()<(int)B->getIns().size() || (int)A->getIns().size()<(int)B->getOuts().size())
		{
			nb_error++;
			if ((int)A->getOuts().size()<(int)B->getIns().size() )
				dev.Error("Wrong Recursion","Nb insB > Nb outsA",nb_error,x+0.5*largeur,y+0.5*hauteur,largeur);
			if ((int)A->getIns().size()<(int)B->getOuts().size() )
				dev.Error("Wrong Recursion","Nb outsB > Nb insA",nb_error,x+0.5*largeur,y+0.5*hauteur,largeur);
		}
		else
		{
			//outs:
			for(i=0;i<(int)outs.size();i++) //i:outs
			{
				if((int)wo.size()!=0)
				{
					if(i<(int)B->getIns().size())
					{
						wo[i]->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+outs[i],x+largeur,y+outs[i]);

						wtiB = new wire();
						wtiB->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+B->getHauteur()+delta_hb+A->getOuts()[i],x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+B->getHauteur()-B->getIns()[i]);
						wtiB->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())+B->getLargeur()),y+B->getHauteur()-B->getIns()[i]);
						wtiB->setLastSegment(wtiB->getLSeg()[(int)wtiB->getLSeg().size()-1]);
						wtiB->setCarre(x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+B->getHauteur()+delta_hb+A->getOuts()[i],cote_carre);
						iB.push_back(wtiB);
						allWires.push_back(wtiB);

						wtoA = new wire();
						wtoA->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y+outs[i],x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+outs[i]);
						oA.push_back(wtoA);
						allWires.push_back(wtoA);
					}
					else
					{
						wo[i]->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y+outs[i],x+largeur,y+outs[i]);
						oA.push_back(wo[i]);
					}
				}
				else
				{
					if(i<(int)B->getIns().size())
					{
						wout = new wire();
						wout->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+outs[i],x+largeur,y+outs[i]);
						wout->setLastSegment(wout->getLSeg()[(int)wout->getLSeg().size()-1]);
						allWires.push_back(wout);

						wtiB = new wire();
						wtiB->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+B->getHauteur()+delta_hb+A->getOuts()[i],x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+B->getHauteur()-B->getIns()[i]);
						wtiB->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())+B->getLargeur()),y+B->getHauteur()-B->getIns()[i]);		
						wtiB->setLastSegment(wtiB->getLSeg()[(int)wtiB->getLSeg().size()-1]);
						wtiB->setCarre(x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+B->getHauteur()+delta_hb+A->getOuts()[i],cote_carre);	
						iB.push_back(wtiB);
						allWires.push_back(wtiB);

						wtoA = new wire();
						wtoA->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y+outs[i],x+((int)B->getOuts().size()+1)*delta_lf+max(A->getLargeur(),B->getLargeur())+(i+1)*delta_lf,y+outs[i]);
						oA.push_back(wtoA);
						allWires.push_back(wtoA);
					}
					else
					{
						w = new wire();
						w->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y+outs[i],x+largeur,y+outs[i]);
						w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
						oA.push_back(w);
						allWires.push_back(w);
					}
				}
			}

			// return left:
			for(i=0;i<(int)A->getIns().size();i++)  //i:A->getIns() et B->getOuts()
			{	
				if(i<(int)B->getOuts().size())
				{
					w = new wire();
					w->addSeg(x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())-B->getLargeur()),y+B->getHauteur()-B->getOuts()[i],x+((int)B->getOuts().size()-i)*delta_lf,y+B->getHauteur()-B->getOuts()[i]);
					w->addSeg(x+((int)B->getOuts().size()-i)*delta_lf,y+B->getHauteur()+delta_hb+A->getIns()[i]);
					w->addSeg(x+((int)B->getOuts().size()-i)*delta_lf,y+B->getHauteur()+delta_hb+A->getIns()[i],x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())-A->getLargeur()),y+B->getHauteur()+delta_hb+A->getIns()[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					iA.push_back(w);
					oB.push_back(w);
					allWires.push_back(w);
				}
				else
				{
					if((int)wi.size()!=0)
					{
						wi[i-(int)B->getOuts().size()]->addSeg(x,y+B->getHauteur()+delta_hb+A->getIns()[i],x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())-A->getLargeur()),y+B->getHauteur()+delta_hb+A->getIns()[i]);
						wi[i-(int)B->getOuts().size()]->setLastSegment(wi[i-(int)B->getOuts().size()]->getLSeg()[(int)wi[i-(int)B->getOuts().size()]->getLSeg().size()-1]);
						iA.push_back(wi[i-(int)B->getOuts().size()]);
					}
					else
					{
						w = new wire();
						w->addSeg(x,y+B->getHauteur()+delta_hb+A->getIns()[i],x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())-A->getLargeur()),y+B->getHauteur()+delta_hb+A->getIns()[i]);
						w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
						iA.push_back(w);
						allWires.push_back(w);
					}
				}
			}
		}
		A->draw(dev,allWires,x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())-A->getLargeur()),y+hauteur-A->getHauteur(),iA,oA,sens);
		B->draw(dev,allWires,x+((int)B->getOuts().size()+1)*delta_lf+0.5*(max(A->getLargeur(),B->getLargeur())+B->getLargeur()),y+B->getHauteur(),iB,oB,1-sens);
	}
	else //sens -
	{
		//if wrong recursion:
		if ((int)A->getOuts().size()<(int)B->getIns().size() || (int)A->getIns().size()<(int)B->getOuts().size())
		{
			nb_error++;
			if ((int)A->getOuts().size()<(int)B->getIns().size() )
				dev.Error("Wrong Recursion","Nb insB > Nb outsA",nb_error,x-0.5*largeur,y-0.5*hauteur,largeur);
			if ((int)A->getIns().size()<(int)B->getOuts().size() )
				dev.Error("Wrong Recursion","Nb outsB > Nb insA",nb_error,x-0.5*largeur,y-0.5*hauteur,largeur);
		}
		else
		{
			//outs:
			for(i=0;i<(int)outs.size();i++) //i:outs
			{
				if((int)wo.size()!=0)
				{
					if(i<(int)B->getIns().size())
					{
						wo[i]->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-outs[i],x-largeur,y-outs[i]);

						wtiB = new wire();
						wtiB->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-B->getHauteur()-delta_hb-A->getOuts()[i],x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-B->getHauteur()+B->getIns()[i]);
						wtiB->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())+B->getLargeur()),y-B->getHauteur()+B->getIns()[i]);
						wtiB->setLastSegment(wtiB->getLSeg()[(int)wtiB->getLSeg().size()-1]);
						wtiB->setCarre(x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-B->getHauteur()-delta_hb-A->getOuts()[i]+cote_carre,cote_carre);
						iB.push_back(wtiB);
						allWires.push_back(wtiB);

						wtoA = new wire();
						wtoA->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y-outs[i],x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-outs[i]);
						oA.push_back(wtoA);
						allWires.push_back(wtoA);
					}
					else
					{
						wo[i]->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y-outs[i],x-largeur,y-outs[i]);
						oA.push_back(wo[i]);
					}
				}
				else
				{
					if(i<(int)B->getIns().size())
					{
						wout = new wire();
						wout->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-outs[i],x-largeur,y-outs[i]);
						wout->setLastSegment(wout->getLSeg()[(int)wout->getLSeg().size()-1]);
						allWires.push_back(wout);

						wtiB = new wire();
						wtiB->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-B->getHauteur()-delta_hb-A->getOuts()[i],x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-B->getHauteur()+B->getIns()[i]);
						wtiB->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())-B->getLargeur()),y-B->getHauteur()+B->getIns()[i]);
						wtiB->setLastSegment(wtiB->getLSeg()[(int)wtiB->getLSeg().size()-1]);
						wtiB->setCarre(x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-B->getHauteur()-delta_hb-A->getOuts()[i]+cote_carre,cote_carre);
						iB.push_back(wtiB);
						allWires.push_back(wtiB);

						wtoA = new wire();
						wtoA->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y-outs[i],x-((int)B->getOuts().size()+1)*delta_lf-max(A->getLargeur(),B->getLargeur())-(i+1)*delta_lf,y-outs[i]);
						oA.push_back(wtoA);
						allWires.push_back(wtoA);
					}
					else
					{
						w = new wire();
						w->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y-outs[i],x-largeur,y-outs[i]);
						w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
						oA.push_back(w);
						allWires.push_back(w);
					}
				}
			}

			// return left:
			for(i=0;i<(int)A->getIns().size();i++)  //i:A->getIns() et B->getOuts()
			{
				if(i<(int)B->getOuts().size())
				{
					w = new wire();
					w->addSeg(x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())-B->getLargeur()),y-B->getHauteur()+B->getOuts()[i],x-((int)B->getOuts().size()-i)*delta_lf,y-B->getHauteur()+B->getOuts()[i]);
					w->addSeg(x-((int)B->getOuts().size()-i)*delta_lf,y-B->getHauteur()-delta_hb-A->getIns()[i]);
					w->addSeg(x-((int)B->getOuts().size()-i)*delta_lf,y-B->getHauteur()-delta_hb-A->getIns()[i],x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())-A->getLargeur()),y-B->getHauteur()-delta_hb-A->getIns()[i]);
					w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
					iA.push_back(w);
					oB.push_back(w);
					allWires.push_back(w);
				}
				else
				{
					if((int)wi.size()!=0)
					{
						wi[i-(int)B->getOuts().size()]->addSeg(x,y-B->getHauteur()-delta_hb-A->getIns()[i],x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())-A->getLargeur()),y-B->getHauteur()-delta_hb-A->getIns()[i]);
						wi[i-(int)B->getOuts().size()]->setLastSegment(wi[i-(int)B->getOuts().size()]->getLSeg()[(int)wi[i-(int)B->getOuts().size()]->getLSeg().size()-1]);
						iA.push_back(wi[i-(int)B->getOuts().size()]);
					}
					else
					{
						w = new wire();
						w->addSeg(x,y-B->getHauteur()-delta_hb-A->getIns()[i],x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())+A->getLargeur()),y-B->getHauteur()-delta_hb-A->getIns()[i]);
						w->setLastSegment(w->getLSeg()[(int)w->getLSeg().size()-1]);
						iA.push_back(w);
						allWires.push_back(w);
					}
				}
			}
		}
		A->draw(dev,allWires,x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())-A->getLargeur()),y-hauteur+A->getHauteur(),iA,oA,sens);
		B->draw(dev,allWires,x-((int)B->getOuts().size()+1)*delta_lf-0.5*(max(A->getLargeur(),B->getLargeur())+B->getLargeur()),y-B->getHauteur(),iB,oB,1-sens);
	}

	cout<<"Recursion dessinee"<<endl;
}

reprRecurs::~reprRecurs()
{
}


