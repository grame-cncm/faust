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
 
 
 
#include "constrFonctions.h"
#include <typeinfo>
#include <string.h>

using namespace std;


/*******************************************************************/
/*																   */
/*						Processing fonctions:					   */
/*																   */
/*******************************************************************/

long cpt_combi = 0;
bool param_OK=false;


/***********************************************************************/
/* Combinaisons: Tests every possibility for parametric's ins and outs */
/***********************************************************************/
void combinaisons(treeParam* B,vector<treeParam*>& listParam,treeRepr* T) 
{															
	int i,j;
	treeParam* RP;

	for(i=B->get_nb_i_Min(); i<B->get_nb_i_Max()+1 ; i++)
	{
		for(j=B->get_nb_o_Min(); j<B->get_nb_o_Max()+1 ; j++)
		{
			if(!param_OK) // solution not found
			{
				RP=B;
				RP = new treeParam(B,i,j,listParam);
			
				if(RP->get_index_list()<(int)listParam.size()-1)
				{
					combinaisons(listParam[RP->get_index_list()+1],listParam,T);
				}
				else
				{
					cpt_combi++;
					/*//to display each possibility:
					for(int k=0;k<(int)listParam.size();k++)
					  cout<<"i: "<<listParam[k]->nb_i_courant<<"  o:"<<listParam[k]->nb_o_courant<<"  ";
					cout<<endl;*/
					pair<int,int> p = T->testTreeNbIo();
					param_OK=(p.first!=-1 && p.second!=-1);
				}
			}
		}
	} 

	if(B->get_index_list()==0)
	{
		if(param_OK == false)
			cout<<"Pas de solution trouvee."<<endl;
		cout<<"Nombre de possibilites etudiees: "<<cpt_combi<<endl;
	}
}


/**********************************************************************/
/* find_config_param: find the first right ins and outs configuration */
/*					  for parametric blocks if it exists.	          */
/**********************************************************************/
bool find_config_param(treeRepr* END) 
{
	bool OKtoRepr=false;
	int i;
	vector<treeRepr*> list;
	END->extractParam(list); // Puts the tree's parametric Blocks in the list
	vector<treeParam*> listParam;

	for(i=0;i<(int)list.size();i++) //conversion *treeRepr to *treeParam
	{
		listParam.push_back((treeParam*)list[i]); 
		listParam[i]->set_index_list(i);
	}

	if(listParam.empty()) 
	{
		//cout<<"Pas de bloc parametrable."<<endl<<endl;
		OKtoRepr=true;
	}
	else
	{
		cout<<(int)listParam.size()<<" blocs parametrables."<<endl<<"Recherche d'une solution:"<<endl<<endl;
		combinaisons(listParam[0],listParam,END); // test every possibility for parametric blocks
		if(param_OK)
		{
			cout<<"Solution trouvee:"<<endl;
			for(int k=0;k<(int)listParam.size();k++)
				cout<<"Bloc "<<listParam[k]->getName()<<":  nb ins: "<<listParam[k]->get_nb_i_courant()<<"  nb outs:"<<listParam[k]->get_nb_o_courant()<<"  "<<endl;
			cout<<endl;
			OKtoRepr=true;
		}		
	}

	return OKtoRepr;
}

static bool isSVGFile(const char* fname)
{
	int i = strlen(fname);
	return (i>4) && (strcmp(&fname[i-4], ".svg") == 0);
}

static bool isPSFile(const char* fname)
{
	int i = strlen(fname);
	return (i>3) && (strcmp(&fname[i-3], ".ps") == 0);
}

 

/*********************************************************/
/* draw_All: draws the final representation (SVG or PS). */
/*********************************************************/
void draw_All(representation* END, const char* devName) //Draws the final representation
{
	int marge = 5;
	int i;
	vector<wire*> allWires,tmp;

//	if(strcmp(devName,"SVG")==0)
	if (isSVGFile(devName))
	{
		SVGDev mydev(devName,END->getLargeur()+2*marge, END->getHauteur()+2*marge);
		END->draw(mydev,allWires,marge,marge,tmp,tmp,1);
		for(i=0;i<(int)allWires.size();i++)
			allWires[i]->draw(mydev);
		//cout<<"Representation terminee dans reprSVG.svg"<<endl;
	}
//	else if(strcmp(devName,"PS")==0)
	else if (isPSFile(devName))
	{
		PSDev mydev(devName,END->getLargeur()+2*marge, END->getHauteur()+2*marge);
		END->draw(mydev,allWires,marge,marge,tmp,tmp,1);
		for(i=0;i<(int)allWires.size();i++)
			allWires[i]->draw(mydev);
		//cout<<"Representation terminee dans reprPS.ps"<<endl;
	} else {
		cout << "ERROR, unrecognized graphic file format : " << devName << endl;
	}
}


