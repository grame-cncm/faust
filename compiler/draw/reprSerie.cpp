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
 
 
 
// reprSerie.cpp

#include "reprSerie.h"
#include <vector>
#include <iostream>
using namespace std;


reprSerie::reprSerie(representation* bA,representation* bB)
{
	A=bA;
	B=bB;
	nom="";
	
	// height:	
	if((int)A->getOuts().size()<(int)B->getIns().size())
	{	
		hisuppl=A->getHauteur()+((int)B->getIns().size()-(int)A->getOuts().size()+1)*delta_hf;
		hauteur=max(B->getHauteur(),hisuppl);
	}

	if((int)A->getOuts().size()>(int)B->getIns().size())
	{
		hisuppl=B->getHauteur()+((int)A->getOuts().size()-(int)B->getIns().size()+1)*delta_hf;
		hauteur=max(A->getHauteur(),hisuppl);
	}

	if((int)A->getOuts().size()==(int)B->getIns().size())
		hauteur=max(A->getHauteur(),B->getHauteur());
	

	// Width:
	largeur=A->getLargeur()+B->getLargeur()+(max((int)A->getOuts().size(),(int)B->getIns().size())+1)*delta_lf;


	// ins:
	int i;
	if((int)A->getOuts().size()<(int)B->getIns().size())
	{	
		for(i=0;i<(int)A->getIns().size();i++)	
			ins.push_back(A->getIns()[i]+0.5*(hauteur-hisuppl));
		
		for(i=0;i<(int)B->getIns().size()-(int)A->getOuts().size();i++)
			ins.push_back(0.5*(hauteur-hisuppl)+A->getHauteur()+(i+1)*delta_hf);					
	}
	else
		for(i=0;i<(int)A->getIns().size();i++)
			ins.push_back(A->getIns()[i]+0.5*(hauteur-A->getHauteur()));
	
	// outs
	if((int)A->getOuts().size()<=(int)B->getIns().size())
	{
		for(i=0;i<(int)B->getOuts().size();i++)
			outs.push_back(B->getOuts()[i]+0.5*(hauteur-B->getHauteur()));
	}
	else
	{	
		for(i=0;i<(int)B->getOuts().size();i++)
			outs.push_back(B->getOuts()[i]+0.5*(hauteur-hisuppl));
		for(i=0;i<(int)A->getOuts().size()-(int)B->getIns().size();i++)
			outs.push_back(0.5*(hauteur-hisuppl)+B->getHauteur()+(i+1)*delta_hf);
	}

//	cout<<"Serie creee"<<endl;
};

void reprSerie::draw(device& dev,vector<wire*>& allWires,float x,float y,vector<wire*> wi,vector<wire*> wo,int sens)
{	
	float xa; // "x angle" : were the wire changes its direction
	int i,j;
	vector <wire*> iA,oA,iB,oB;
	wire *w;

	if (sens == 1)
	{
		if((int)A->getOuts().size()==(int)B->getIns().size())
		{
			XaInit((int)A->getOuts().size());
			
			for(i=0;i<(int)A->getOuts().size();i++)
			{
				if(0.5*(hauteur-A->getHauteur())+A->getOuts()[i]>0.5*(hauteur-B->getHauteur())+B->getIns()[i])
					xa=premXaLibre()*delta_lf;
				else
					xa=dernXaLibre()*delta_lf;
					
				w = new wire();
				w->addSeg(x+A->getLargeur(),y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i],x+A->getLargeur()+xa,y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i]);
				w->addSeg(x+A->getLargeur()+xa,y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
				w->addSeg(x+largeur-B->getLargeur(),y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
				w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
				oA.push_back(w);
				iB.push_back(w);
				allWires.push_back(w);
			}
			A->draw(dev,allWires,x,y+0.5*(hauteur-A->getHauteur()),wi,oA,sens);
			B->draw(dev,allWires,x+largeur-B->getLargeur(),y+0.5*(hauteur-B->getHauteur()),iB,wo,sens);
		}

		if((int)A->getOuts().size()<(int)B->getIns().size())
		{
			XaInit((int)B->getIns().size());
			
			int cptwi=0;
			if((int)wi.size() != 0)
				for(cptwi=0; cptwi<(int)A->getIns().size(); cptwi++)
					iA.push_back(wi[cptwi]);

			// wires linking the 2 blocks:
			for(i=0; i<(int)A->getOuts().size(); i++)
			{
				if(A->getOuts()[i]+0.5*(hauteur-hisuppl)>0.5*(hauteur-B->getHauteur())+B->getIns()[i])
					xa=premXaLibre()*delta_lf;
				else
					xa=dernXaLibre()*delta_lf;
				w = new wire();
				w->addSeg(x+A->getLargeur(),y+0.5*(hauteur-hisuppl)+A->getOuts()[i],x+A->getLargeur()+xa,y+0.5*(hauteur-hisuppl)+A->getOuts()[i]);
				w->addSeg(x+A->getLargeur()+xa,y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
				w->addSeg(x+largeur-B->getLargeur(),y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
				w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
				oA.push_back(w);
				iB.push_back(w);
				allWires.push_back(w);
			}
			
			// wires linking directly ins to B
			float d;
			for(j=1; i<(int)B->getIns().size();i++,j++,cptwi++)
			{
				if(0.5*(hauteur-B->getHauteur())+B->getIns()[i]>0.5*(hauteur-hisuppl)+A->getHauteur()+j*delta_hf)
					d=dernXaLibre()*delta_lf;
				else
					d=premXaLibre()*delta_lf;
			
				if((int)wi.size() != 0)
				{				
					wi[cptwi]->addSeg(x,y+0.5*(hauteur-hisuppl)+A->getHauteur()+j*delta_hf,x+A->getLargeur()+d,y+0.5*(hauteur-hisuppl)+A->getHauteur()+j*delta_hf);
					wi[cptwi]->addSeg(x+A->getLargeur()+d,y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
					wi[cptwi]->addSeg(x+largeur-B->getLargeur(),y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
					wi[cptwi]->setLastSegment(wi[cptwi]->getLSeg()[wi[cptwi]->getLSeg().size()-1]);
					iB.push_back(wi[cptwi]);
				}
				else
				{
					w = new wire();
					w->addSeg(x,y+0.5*(hauteur-hisuppl)+A->getHauteur()+j*delta_hf,x+A->getLargeur()+d,y+0.5*(hauteur-hisuppl)+A->getHauteur()+j*delta_hf);
					w->addSeg(x+A->getLargeur()+d,y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
					w->addSeg(x+largeur-B->getLargeur(),y+0.5*(hauteur-B->getHauteur())+B->getIns()[i]);
					w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
					iB.push_back(w);
					allWires.push_back(w);
				}
			}

			A->draw(dev,allWires,x,y+0.5*(hauteur-hisuppl),iA,oA,sens);
			B->draw(dev,allWires,x+largeur-B->getLargeur(),y+0.5*(hauteur-B->getHauteur()),iB,wo,sens);	
		}

		if((int)A->getOuts().size()>(int)B->getIns().size())
		{
			XaInit((int)A->getOuts().size());
			
			int cptwo=0;
			if((int)wo.size() != 0)
				for(cptwo=0; cptwo<(int)B->getOuts().size(); cptwo++)
					oB.push_back(wo[cptwo]);

			// wires linking the 2 blocks:
			for(i=0; i<(int)B->getIns().size(); i++)
			{
				if(0.5*(hauteur-A->getHauteur())+A->getOuts()[i]>B->getIns()[i]+0.5*(hauteur-hisuppl))
					xa=premXaLibre()*delta_lf;
				else
					xa=dernXaLibre()*delta_lf;
				w = new wire();
				w->addSeg(x+A->getLargeur(),y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i],x+A->getLargeur()+xa,y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i]);
				w->addSeg(x+A->getLargeur()+xa,y+0.5*(hauteur-hisuppl)+B->getIns()[i]);
				w->addSeg(x+largeur-B->getLargeur(),y+0.5*(hauteur-hisuppl)+B->getIns()[i]);
				w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
				oA.push_back(w);
				iB.push_back(w);
				allWires.push_back(w);
			}
			
			//wires linking directly A to outs
			float d;
			for(j=1;i<(int)A->getOuts().size(); i++,j++,cptwo++)
			{
				if(0.5*(hauteur-A->getHauteur())+A->getOuts()[i]>0.5*(hauteur-hisuppl)+B->getHauteur()+j*delta_hf)
					d=premXaLibre()*delta_lf;
				else
					d=dernXaLibre()*delta_lf;
			
				if((int)wo.size() != 0)
				{
					wo[cptwo]->addSeg(x+A->getLargeur(),y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i],x+A->getLargeur()+d,y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i]);		
					wo[cptwo]->addSeg(x+A->getLargeur()+d,y+0.5*(hauteur-hisuppl)+B->getHauteur()+j*delta_hf);
					wo[cptwo]->addSeg(x+largeur,y+0.5*(hauteur-hisuppl)+B->getHauteur()+j*delta_hf);
					oA.push_back(wo[cptwo]);
				}
				else
				{
					w = new wire();
					w->addSeg(x+A->getLargeur(),y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i],x+A->getLargeur()+d,y+0.5*(hauteur-A->getHauteur())+A->getOuts()[i]);
					w->addSeg(x+A->getLargeur()+d,y+0.5*(hauteur-hisuppl)+B->getHauteur()+j*delta_hf);
					w->addSeg(x+largeur,y+0.5*(hauteur-hisuppl)+B->getHauteur()+j*delta_hf);
					w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
					oA.push_back(w);
					allWires.push_back(w);
				}
			}

			A->draw(dev,allWires,x,y+0.5*(hauteur-A->getHauteur()),wi,oA,sens);
			B->draw(dev,allWires,x+largeur-B->getLargeur(),y+0.5*(hauteur-hisuppl),iB,oB,sens);
		}

	}
	else  // sens -
	{
		if((int)A->getOuts().size()==(int)B->getIns().size())
		{
			XaInit((int)A->getOuts().size());
			
			for(i=0;i<(int)A->getOuts().size();i++)
			{
				
				if(0.5*(hauteur-A->getHauteur())+A->getOuts()[i]>0.5*(hauteur-B->getHauteur())+B->getIns()[i])
					xa=premXaLibre()*delta_lf;
				else
					xa=dernXaLibre()*delta_lf;
					
				w = new wire();
				w->addSeg(x-A->getLargeur(),y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i],x-A->getLargeur()-xa,y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i]);
				w->addSeg(x-A->getLargeur()-xa,y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);
				w->addSeg(x-largeur+B->getLargeur(),y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);
				w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
				oA.push_back(w);
				iB.push_back(w);
				allWires.push_back(w);
			}

			A->draw(dev,allWires,x,y-0.5*(hauteur-A->getHauteur()),wi,oA,sens);
			B->draw(dev,allWires,x-largeur+B->getLargeur(),y-0.5*(hauteur-B->getHauteur()),iB,wo,sens);
		}

		if((int)A->getOuts().size()<(int)B->getIns().size())
		{
			XaInit((int)B->getIns().size());
			
			int cptwi=0;
			if((int)wi.size() != 0)
				for(cptwi=0; cptwi<(int)A->getIns().size(); cptwi++)
					iA.push_back(wi[cptwi]);

			// wires linking the 2 blocks:
			for(i=0; i<(int)A->getOuts().size(); i++)
			{
				if(A->getOuts()[i]+0.5*(hauteur-hisuppl)>0.5*(hauteur-B->getHauteur())+B->getIns()[i])
					xa=premXaLibre()*delta_lf;
				else
					xa=dernXaLibre()*delta_lf;
		 		w = new wire();
				w->addSeg(x-A->getLargeur(),y-0.5*(hauteur-hisuppl)-A->getOuts()[i],x-A->getLargeur()-xa,y-0.5*(hauteur-hisuppl)-A->getOuts()[i]);
				w->addSeg(x-A->getLargeur()-xa,y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);
				w->addSeg(x-largeur+B->getLargeur(),y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);
				w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
				oA.push_back(w);
				iB.push_back(w);
				allWires.push_back(w);
			}
			
			// wires linking directly ins to B
			float d;
			for(j=1; i<(int)B->getIns().size();i++,j++,cptwi++)
			{
				if(0.5*(hauteur-B->getHauteur())+B->getIns()[i]>0.5*(hauteur-hisuppl)+A->getHauteur()+j*delta_hf)
					d=dernXaLibre()*delta_lf;
				else
					d=premXaLibre()*delta_lf;
				if((int)wi.size() != 0)
				{
					wi[cptwi]->addSeg(x,y-0.5*(hauteur-hisuppl)-A->getHauteur()-j*delta_hf,x-A->getLargeur()-d,y-0.5*(hauteur-hisuppl)-A->getHauteur()-j*delta_hf);
					wi[cptwi]->addSeg(x-A->getLargeur()-d,y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);
					wi[cptwi]->addSeg(x-largeur+B->getLargeur(),y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);			
					wi[cptwi]->setLastSegment(wi[cptwi]->getLSeg()[wi[cptwi]->getLSeg().size()-1]);
					iB.push_back(wi[cptwi]);
				}
				else
				{
					w = new wire();
					w->addSeg(x,y-0.5*(hauteur-hisuppl)-A->getHauteur()-j*delta_hf,x-A->getLargeur()-d,y-0.5*(hauteur-hisuppl)-A->getHauteur()-j*delta_hf);
					w->addSeg(x-A->getLargeur()-d,y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);
					w->addSeg(x-largeur+B->getLargeur(),y-0.5*(hauteur-B->getHauteur())-B->getIns()[i]);			
					w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
					iB.push_back(w);
					allWires.push_back(w);
				}
			}

			A->draw(dev,allWires,x,y-0.5*(hauteur-hisuppl),iA,oA,sens);
			B->draw(dev,allWires,x-largeur+B->getLargeur(),y-0.5*(hauteur-B->getHauteur()),iB,wo,sens);	
		}

		if((int)A->getOuts().size()>(int)B->getIns().size())
		{
			XaInit((int)A->getOuts().size());
			
			int cptwo=0;
			if((int)wo.size() != 0)
				for(cptwo=0; cptwo<(int)B->getOuts().size(); cptwo++)
					oB.push_back(wo[cptwo]);

			//  wires linking the 2 blocks:
			for(i=0; i<(int)B->getIns().size(); i++)
			{
				if(0.5*(hauteur-A->getHauteur())+A->getOuts()[i]>B->getIns()[i]+0.5*(hauteur-hisuppl))
					xa=premXaLibre()*delta_lf;
				else
					xa=dernXaLibre()*delta_lf;
				w = new wire();
				w->addSeg(x-A->getLargeur(),y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i],x-A->getLargeur()-xa,y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i]);
				w->addSeg(x-A->getLargeur()-xa,y-0.5*(hauteur-hisuppl)-B->getIns()[i]);
				w->addSeg(x-largeur+B->getLargeur(),y-0.5*(hauteur-hisuppl)-B->getIns()[i]);
				w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
				oA.push_back(w);
				iB.push_back(w);
				allWires.push_back(w);
			}
			//wires linking directly A to outs
			float d;
			for(j=1;i<(int)A->getOuts().size(); i++,j++,cptwo++)
			{
				if(0.5*(hauteur-A->getHauteur())+A->getOuts()[i]>0.5*(hauteur-hisuppl)+B->getHauteur()+j*delta_hf)
					d=premXaLibre()*delta_lf;
				else
					d=dernXaLibre()*delta_lf;
				if((int)wo.size() != 0)
				{
					wo[cptwo]->addSeg(x-A->getLargeur(),y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i],x-A->getLargeur()-d,y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i]);
					wo[cptwo]->addSeg(x-A->getLargeur()-d,y-0.5*(hauteur-hisuppl)-B->getHauteur()-j*delta_hf);
					wo[cptwo]->addSeg(x-largeur,y-0.5*(hauteur-hisuppl)-B->getHauteur()-j*delta_hf);
					oA.push_back(wo[cptwo]);
				}
				else
				{
					w = new wire();
					w->addSeg(x-A->getLargeur(),y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i],x-A->getLargeur()-d,y-0.5*(hauteur-A->getHauteur())-A->getOuts()[i]);
					w->addSeg(x-A->getLargeur()-d,y-0.5*(hauteur-hisuppl)-B->getHauteur()-j*delta_hf);
					w->addSeg(x-largeur,y-0.5*(hauteur-hisuppl)-B->getHauteur()-j*delta_hf);
					w->setLastSegment(w->getLSeg()[w->getLSeg().size()-1]);
					oA.push_back(w);
					allWires.push_back(w);
				}
			}

			A->draw(dev,allWires,x,y-0.5*(hauteur-A->getHauteur()),wi,oA,sens);
			B->draw(dev,allWires,x-largeur+B->getLargeur(),y-0.5*(hauteur-hisuppl),iB,oB,sens);
		}

	}
	//cout<<"Serie dessine"<<endl;
	delete Xa;
};

void reprSerie::XaInit(int nb)
{	
	int i;
	tailleXa=nb;
	Xa= new bool[nb];
	for (i=0 ; i<nb ; i++)
		Xa[i]=true;
}

int reprSerie::dernXaLibre()
{
	int i;
	for(i=tailleXa ; i>0 ;i--)
	{
		if(Xa[i-1]==true)
		{
			Xa[i-1]=false;
			break;
		}
	}
	return i;
}

int reprSerie::premXaLibre()
{	
	int i;
	for(i=0 ; i<tailleXa ;i++)
	{
		if(Xa[i]==true)
		{
			Xa[i]=false;
			break;
		}
	}
	return i+1;
}

reprSerie::~reprSerie() 
{	
}



