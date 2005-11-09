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
 
 
 
// SVGDev.cpp

#include "SVGDev.h"
#include "stdio.h"
#include <iostream>
using namespace std;

SVGDev::SVGDev(const char* ficName,float largeur, float hauteur)
{
	if((fic_repr = fopen(ficName,"w+")) == NULL) { cout<<"Impossible de creer ou d'ouvrir "<<ficName<<endl; }

	// representation file:
	fprintf(fic_repr,"<?xml version=\"1.0\"?>\n");
	// + DTD ...
	// viewBox:
	fprintf(fic_repr,"<svg preserveAspectRatio=\"xMidYMid meet\" viewBox=\"0 0 %f %f\" width=\"200mm\" height=\"150mm\" >\n",largeur,hauteur);
}

SVGDev::~SVGDev()
{
	fprintf(fic_repr,"</svg>\n");
	fclose(fic_repr);
}



void SVGDev::rect(float x,float y,float l,float h)
{
	// dessine l'ombre
	fprintf(fic_repr,"<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" rx=\"0\" ry=\"0\" style=\"stroke:none;fill:#cccccc;\"/>\n",x+1,y+1,l,h);
	
	// dessine le rectangle
	fprintf(fic_repr,"<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" rx=\"0\" ry=\"0\" style=\"stroke: black;stroke-width:0.25;fill:#ffffd7;\"/>\n",x,y,l,h);
}

void SVGDev::rond(float x,float y,float rayon)
{
	//fprintf(fic_repr,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\"/>\n",x,y,rayon);
}

void SVGDev::fleche(float x,float y,float rotation,int sens)
{
	float dx = 3; 
	float dy = 1;
	
	if(sens == 1)
	{
		fprintf(fic_repr,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  transform=\"rotate(%f,%f,%f)\" style=\"stroke: black; stroke-width:0.25;\"/>\n",x-dx,y-dy,x,y,rotation,x,y);
		fprintf(fic_repr,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  transform=\"rotate(%f,%f,%f)\" style=\"stroke: black; stroke-width:0.25;\"/>\n",x-dx,y+dy,x,y,rotation,x,y);
	}
	else //for recursion
	{
		fprintf(fic_repr,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  transform=\"rotate(%f,%f,%f)\" style=\"stroke: black; stroke-width:0.25;\"/>\n",x+dx,y-dy,x,y,rotation,x,y);
		fprintf(fic_repr,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  transform=\"rotate(%f,%f,%f)\" style=\"stroke: black; stroke-width:0.25;\"/>\n",x+dx,y+dy,x,y,rotation,x,y);
	}
}

void SVGDev::carre(float x,float y,float cote)
{
	fprintf(fic_repr,"<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"stroke: black;stroke-width:0.5;fill:none;\"/>\n",x-0.5*cote,y-cote,cote,cote);
}

void SVGDev::trait(float x1,float y1,float x2,float y2)
{
	fprintf(fic_repr,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  style=\"stroke: black; stroke-linecap:round; stroke-width:0.25;\"/>\n",x1,y1,x2,y2);
}

void SVGDev::dasharray(float x1,float y1,float x2,float y2)
{
	fprintf(fic_repr,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  style=\"stroke: black; stroke-linecap:round; stroke-width:1; stroke-dasharray:3,3;\"/>\n",x1,y1,x2,y2);
}

void SVGDev::text(float x,float y,const char* name)
{
	int	i,j;

	// SUBSTITUTION DES CARACTeRES INTERDITS EN XML
	char name2[256];

	for (i=0, j=0; (name[i] != 0) && (j < 250); i++) {
		switch (name[i]) {
			case '<' 	: name2[j++] = '&'; name2[j++] = 'l'; name2[j++] = 't'; name2[j++] = ';'; 	break;
			case '>' 	: name2[j++] = '&'; name2[j++] = 'g'; name2[j++] = 't'; name2[j++] = ';'; 	break;
			case '\'' 	: name2[j++] = '&'; name2[j++] = 'a'; name2[j++] = 'p'; name2[j++] = 'o'; name2[j++] = 's'; name2[j++] = ';'; 	break;
			case '"' 	: name2[j++] = '&'; name2[j++] = 'q'; name2[j++] = 'u'; name2[j++] = 'o'; name2[j++] = 't'; name2[j++] = ';'; 	break;
			case '&' 	: name2[j++] = '&'; name2[j++] = 'a'; name2[j++] = 'm'; name2[j++] = 'p'; name2[j++] = ';'; 	break;
			default 	: name2[j++] = name[i]; 
		}
	}
	name2[j] = 0;
	
	cout << "text : " << name << " -> " << name2 << endl;;
	
	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\" style=\"font-family:Courier;font-weight:normal;font-style:normal;font-size:8;text-anchor:middle\">%s</text>\n",x,y+3,name2);
}

void SVGDev::label(float x,float y,const char* name)
{
	int	i,j;

	// SUBSTITUTION DES CARACTeRES INTERDITS EN XML
	char name2[256];

	for (i=0, j=0; (name[i] != 0) && (j < 250); i++) {
		switch (name[i]) {
			case '<' 	: name2[j++] = '&'; name2[j++] = 'l'; name2[j++] = 't'; name2[j++] = ';'; 	break;
			case '>' 	: name2[j++] = '&'; name2[j++] = 'g'; name2[j++] = 't'; name2[j++] = ';'; 	break;
			case '\'' 	: name2[j++] = '&'; name2[j++] = 'a'; name2[j++] = 'p'; name2[j++] = 'o'; name2[j++] = 's'; name2[j++] = ';'; 	break;
			case '"' 	: name2[j++] = '&'; name2[j++] = 'q'; name2[j++] = 'u'; name2[j++] = 'o'; name2[j++] = 't'; name2[j++] = ';'; 	break;
			case '&' 	: name2[j++] = '&'; name2[j++] = 'a'; name2[j++] = 'm'; name2[j++] = 'p'; name2[j++] = ';'; 	break;
			default 	: name2[j++] = name[i]; 
		}
	}
	name2[j] = 0;
	
	cout << "label : " << name << " -> " << name2 << endl;
	
	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\" style=\"font-family:Courier;font-weight:normal;font-style:normal;font-size:7\">%s</text>\n",x,y+2,name2);
}

void SVGDev::markSens(float x,float y,int sens)
{	
	int offset = (sens == 1) ? 2 : -2;
	
	
	fprintf(fic_repr,"<circle cx=\"%f\" cy=\"%f\" r=\"1\"/>\n", x+offset, y+offset);
#if 0
	if (sens==1)
		fprintf(fic_repr,"<rect x=\"%f\" y=\"%f\" width=\"4\" height=\"4\" rx=\"2\" ry=\"1\" style=\"stroke: black;stroke-width:0.5;fill:none;\"/>\n",x,y);
	else
		fprintf(fic_repr,"<rect x=\"%f\" y=\"%f\" width=\"4\" height=\"4\" rx=\"2\" ry=\"1\" style=\"stroke: black;stroke-width:0.5;fill:none;\"/>\n",x-4,y-4);
#endif
}

void SVGDev::Error(const char* message, const char* reason,int nb_error,float x,float y,float largeur)
{
	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\"  textLength=\"%f\" lengthAdjust=\"spacingAndGlyphs\" style=\"stroke: red; stroke-width:0.3; fill:red; text-anchor:middle;\">%d : %s</text>\n",x,y-7,largeur,nb_error,message);
	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\"  textLength=\"%f\" lengthAdjust=\"spacingAndGlyphs\" style=\"stroke: red; stroke-width:0.3; fill:none; text-anchor:middle;\">%s</text>\n",x,y+7,largeur,reason);
}



