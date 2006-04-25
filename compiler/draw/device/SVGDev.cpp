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

static char* xmlcode(const char* name, char* name2)
{
	int	i,j;

	// SUBSTITUTION DES CARACTeRES INTERDITS EN XML

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

	return name2;
}

SVGDev::SVGDev(const char* ficName,float largeur, float hauteur)
{
	float gScale = 0.5;
//	if ((fic_repr = fopen(addFileNum(ficName),"w+")) == NULL) {
	if ((fic_repr = fopen(ficName,"w+")) == NULL) {
	//if((fic_repr = fopen(ficName,"w+")) == NULL) {
		cout<<"Impossible de creer ou d'ouvrir "<<ficName<<endl;
	}

	// representation file:
	fprintf(fic_repr,"<?xml version=\"1.0\"?>\n");
	// + DTD ...
	// viewBox:
	//fprintf(fic_repr,"<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" preserveAspectRatio=\"xMidYMid meet\" viewBox=\"0 0 %f %f\" width=\"200mm\" height=\"150mm\" >\n",largeur,hauteur);
	fprintf(fic_repr,"<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" viewBox=\"0 0 %f %f\" width=\"%fmm\" height=\"%fmm\" version=\"1.1\">\n", largeur, hauteur, largeur*gScale, hauteur*gScale);
}

SVGDev::~SVGDev()
{
	fprintf(fic_repr,"</svg>\n");
	fclose(fic_repr);
}

void SVGDev::rect(float x,float y,float l,float h, const char* color, const char* link)
{
	char buf[512];
	if (link != 0) {
		// open the optional link tag
		fprintf(fic_repr,"<a xlink:href=\"%s\">\n", xmlcode(link, buf));
	}
	// draw the shadow
	fprintf(fic_repr,"<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" rx=\"0\" ry=\"0\" style=\"stroke:none;fill:#cccccc;\"/>\n",x+1,y+1,l,h);

	// draw the rectangle
	fprintf(fic_repr,"<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" rx=\"0\" ry=\"0\" style=\"shape-rendering: crispEdges; stroke: black;stroke-width:0.25;fill:%s;\"/>\n", x, y, l, h, color);
	if (link != 0) {
		// close the optional link tag
		fprintf(fic_repr,"</a>\n");
	}

}

void SVGDev::rond(float x,float y,float rayon)
{
	fprintf(fic_repr,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\"/>\n",x,y,rayon);
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
	fprintf(fic_repr,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  style=\"shape-rendering: crispEdges; stroke:black; stroke-linecap:round; stroke-width:0.25;\"/>\n",x1,y1,x2,y2);
}

void SVGDev::dasharray(float x1,float y1,float x2,float y2)
{
	fprintf(fic_repr,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  style=\"stroke: black; stroke-linecap:round; stroke-width:0.25; stroke-dasharray:3,3;\"/>\n",x1,y1,x2,y2);
}

void SVGDev::text(float x,float y,const char* name)
{
	char name2[256];
	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\" font-family=\"Courier\" font-size=\"8\" text-anchor=\"middle\">%s</text>\n",x,y+3,xmlcode(name,name2));
}

void SVGDev::label(float x,float y,const char* name)
{
	char name2[256];
//	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\" style=\"font-family:Courier;font-weight:normal;font-style:normal;font-size:7\">%s</text>\n",x,y+2,xmlcode(name,name2));
	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\" font-family=\"Courier\" font-size=\"7\">%s</text>\n",x,y+2,xmlcode(name,name2));
}

void SVGDev::markSens(float x,float y,int sens)
{
	int offset = (sens == 1) ? 2 : -2;
	fprintf(fic_repr,"<circle cx=\"%f\" cy=\"%f\" r=\"1\"/>\n", x+offset, y+offset);
}

void SVGDev::Error(const char* message, const char* reason,int nb_error,float x,float y,float largeur)
{
	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\"  textLength=\"%f\" lengthAdjust=\"spacingAndGlyphs\" style=\"stroke: red; stroke-width:0.3; fill:red; text-anchor:middle;\">%d : %s</text>\n",x,y-7,largeur,nb_error,message);
	fprintf(fic_repr,"<text x=\"%f\" y=\"%f\"  textLength=\"%f\" lengthAdjust=\"spacingAndGlyphs\" style=\"stroke: red; stroke-width:0.3; fill:none; text-anchor:middle;\">%s</text>\n",x,y+7,largeur,reason);
}



