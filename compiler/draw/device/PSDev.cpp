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
 
// PSDev.cpp

#include "PSDev.h"
#include "compatibility.hh"
#include "global.hh"
#include "exception.hh"

#include <string.h>
#include <math.h>
#include <iostream>
#include <sstream>

using namespace std;

static char * addFileNum(const char* fname)
{
	char 	f[256];
	char 	s[256]; 
	int 	i;

 	// remove suffixes (.xxx.yyy)
	for (i=0; (fname[i] != 0) && (fname[i] != '.'); i++) {
		f[i] = fname[i];
	}
	f[i] = 0;

	// add number and .ps suffix
	snprintf(s, 255, "%s-%d.ps", f, ++gGlobal->gFileNum);
	//cerr << "file name " << s << endl;
	return strdup(s);
}

PSDev::PSDev(const char* ficName, double largeur, double hauteur)
{
	if ((fic_repr = fopen(addFileNum(ficName),"w+")) == NULL) { 
		stringstream error;
		error << "Impossible to create or open " << ficName << endl;
        throw faustexception(error.str());
	}

	if (largeur < hauteur)
		largeur = hauteur;

	fprintf(fic_repr,"%%!PS-Adobe-3.0 \n");
	//fprintf(fic_repr,"%%%%Pages: (atend) \n");
	fprintf(fic_repr,"%%%%BoundingBox: 0 0 450 %d\n",(int)floor((hauteur*450/largeur)+1));

	fprintf(fic_repr,"/unit {%f mul} def\n\n",450/largeur);
	fprintf(fic_repr,"0 %f unit translate\n",hauteur);  
	fprintf(fic_repr,"1 -1 scale\n\n");				// postscript's origin = lower left corner (SVG:upper left)
	fprintf(fic_repr,"0.6 unit setlinewidth\n");	// lines' width

	fprintf(fic_repr,"/Times-Roman findfont   %% Get the basic font for text\n");
	//fprintf(fic_repr,"15 unit scalefont       %% Scale the font to 15 units\n");
	fprintf(fic_repr,"10 unit scalefont       %% Scale the font to 10 units\n");
	fprintf(fic_repr,"setfont                 %% Make it the current font\n\n");
}

PSDev::~PSDev()
{
	fprintf(fic_repr,"showpage\n"); //eject the page
	fclose(fic_repr);
}

void PSDev::rect(double x,double y,double l,double h, const char*, const char*)
{
    fprintf(fic_repr,"gsave\n");
    fprintf(fic_repr,"newpath\n");
    //fprintf(fic_repr,"1.5 unit setlinewidth\n");
    fprintf(fic_repr,"1.0 unit setlinewidth\n");
    fprintf(fic_repr,"%f unit %f unit moveto\n",x,y);
    fprintf(fic_repr,"0 unit %f unit rlineto\n",h);
    fprintf(fic_repr,"%f unit 0 unit rlineto\n",l);
    fprintf(fic_repr,"0 unit %f unit rlineto\n",-h);
    fprintf(fic_repr,"closepath\n");
    fprintf(fic_repr,"stroke\n");
    fprintf(fic_repr,"grestore\n");
}

void PSDev::triangle(double x,double y,double l,double h, const char*, const char*, bool leftright)
{
    fprintf(fic_repr,"gsave\n");
    fprintf(fic_repr,"newpath\n");
    //fprintf(fic_repr,"1.5 unit setlinewidth\n");
    fprintf(fic_repr,"1.0 unit setlinewidth\n");
    fprintf(fic_repr,"%f unit %f unit moveto\n",x,y);
    fprintf(fic_repr,"0 unit %f unit rlineto\n",h);
    fprintf(fic_repr,"%f unit 0 unit rlineto\n",l);
    fprintf(fic_repr,"0 unit %f unit rlineto\n",-h);
    fprintf(fic_repr,"closepath\n");
    fprintf(fic_repr,"stroke\n");
    fprintf(fic_repr,"grestore\n");
}

void PSDev::rond(double x,double y,double rayon)
{
	fprintf(fic_repr,"gsave\n");
	fprintf(fic_repr,"newpath\n");
	fprintf(fic_repr,"%f unit %f unit %f unit 0 360 arc\n",x,y,rayon);
	fprintf(fic_repr,"fill\n");
	fprintf(fic_repr,"grestore\n");
}

void PSDev::fleche(double x,double y,double rotation,int sens)
{
	if(sens == 1)
	{	
		fprintf(fic_repr,"gsave\n");
		fprintf(fic_repr,"newpath\n");
		fprintf(fic_repr,"0.3 setgray\n");
		fprintf(fic_repr,"%f unit %f unit moveto\n",x,y);
		fprintf(fic_repr,"%f rotate\n",rotation);
		fprintf(fic_repr,"%f unit %f unit rlineto\n",(double)-4,(double)-2);
		fprintf(fic_repr,"%f rotate\n",(double)-rotation);
		fprintf(fic_repr,"%f unit %f unit moveto\n",x,y);  
		fprintf(fic_repr,"%f rotate\n",rotation); 
		fprintf(fic_repr,"%f unit %f unit rlineto\n",(double)-4,(double)+2);
		fprintf(fic_repr,"closepath\n");  
		fprintf(fic_repr,"stroke\n");
		fprintf(fic_repr,"grestore\n");
	}
	else //for the recursion
	{
		fprintf(fic_repr,"gsave\n");
		fprintf(fic_repr,"newpath\n");
		fprintf(fic_repr,"0.3 setgray\n");
		fprintf(fic_repr,"%f unit %f unit moveto\n",x,y);
		fprintf(fic_repr,"%f rotate\n",rotation);
		fprintf(fic_repr,"%f unit %f unit rlineto\n",(double)4,(double)-2);
		fprintf(fic_repr,"%f rotate\n",(double)-rotation);
		fprintf(fic_repr,"%f unit %f unit moveto\n",x,y);  
		fprintf(fic_repr,"%f rotate\n",rotation); 
		fprintf(fic_repr,"%f unit %f unit rlineto\n",(double)4,(double)+2);
		fprintf(fic_repr,"closepath\n");  
		fprintf(fic_repr,"stroke\n");
		fprintf(fic_repr,"grestore\n");
	}
}

void PSDev::carre(double x,double y,double cote)
{
	fprintf(fic_repr,"gsave\n");
	fprintf(fic_repr,"newpath\n");
	fprintf(fic_repr,"0.3 setgray\n");
	fprintf(fic_repr,"%f unit %f unit moveto\n",x-cote/2,y);    
	fprintf(fic_repr,"0 unit %f unit rlineto\n",-cote);
	fprintf(fic_repr,"%f unit 0 unit rlineto\n",cote);
	fprintf(fic_repr,"0 unit %f unit rlineto\n",cote);
	fprintf(fic_repr,"closepath\n");              
	fprintf(fic_repr,"stroke\n");
	fprintf(fic_repr,"grestore\n");
}

void PSDev::trait(double x1,double y1,double x2,double y2)
{
	fprintf(fic_repr,"gsave\n");
	fprintf(fic_repr,"0.3 setgray\n");
	fprintf(fic_repr,"newpath\n");
	fprintf(fic_repr,"%f unit %f unit moveto\n",x1,y1);    
	fprintf(fic_repr,"%f unit %f unit lineto\n",x2,y2);
	fprintf(fic_repr,"stroke\n");
	fprintf(fic_repr,"grestore\n");
}

void PSDev::dasharray(double x1,double y1,double x2,double y2)
{
	fprintf(fic_repr,"gsave\n");
	fprintf(fic_repr,"newpath\n");
	fprintf(fic_repr,"0.6 setgray\n");
	fprintf(fic_repr,"0.8 unit setlinewidth\n");
	fprintf(fic_repr,"%f unit %f unit moveto\n",x1,y1); 
	fprintf(fic_repr,"%f unit %f unit lineto\n",x2,y2);
	fprintf(fic_repr,"stroke\n");
	fprintf(fic_repr,"grestore\n");
}

void PSDev::text(double x,double y,const char* nom, const char* link)
{
	fprintf(fic_repr,"newpath\n");
    //fprintf(fic_repr,"%f unit %f unit moveto\n",(x-4)-(strlen(nom)-1)*3.8,y+2);
   fprintf(fic_repr,"%f unit %f unit moveto\n",(x-0)-(strlen(nom)-1)*3.8,y+2);
    fprintf(fic_repr,"gsave\n");
	fprintf(fic_repr,"1 -1 scale\n\n");
	fprintf(fic_repr,"(%s) show\n",nom);
	fprintf(fic_repr,"grestore\n");
}

void PSDev::label(double x,double y,const char* label)
{
	fprintf(fic_repr,"gsave\n");
	fprintf(fic_repr,"/Times-Roman findfont   %% Get the basic font for text\n");
	fprintf(fic_repr,"7 unit scalefont        %% Scale the font to 10 points\n");
	fprintf(fic_repr,"setfont                 %% Make it the current font\n\n");
	fprintf(fic_repr,"newpath\n");
    fprintf(fic_repr,"%f unit %f unit moveto\n",(x+2),y+1.2);
	fprintf(fic_repr,"1 -1 scale\n");
    fprintf(fic_repr,"(%s) show\n",label);
	fprintf(fic_repr,"grestore\n");
}

void PSDev::markSens(double x,double y,int sens)
{
	if (sens==1)
	{
		fprintf(fic_repr,"newpath\n");
		fprintf(fic_repr,"%f unit %f unit moveto\n",x,y+4);    
		fprintf(fic_repr,"%f unit %f unit rlineto\n",(double)4,(double)-4);
		fprintf(fic_repr,"closepath\n");
	}
	else //for the recursion
	{
		fprintf(fic_repr,"newpath\n");
		fprintf(fic_repr,"%f unit %f unit moveto\n",x,y-4);    
		fprintf(fic_repr,"%f unit %f unit rlineto\n",(double)-4,(double)4);
		fprintf(fic_repr,"closepath\n");      
	}
	fprintf(fic_repr,"stroke\n");
}

void PSDev::Error(const char* message, const char* reason,int nb_error,double x,double y,double largeur)
{
	fprintf(fic_repr,"gsave\n");
	fprintf(fic_repr,"/Times-Roman findfont   %% Get the basic font for text\n");
	fprintf(fic_repr,"17 unit scalefont       %% Scale the font to 10 points\n");
	fprintf(fic_repr,"setfont                 %% Make it the current font\n\n");
	fprintf(fic_repr,"newpath\n");
    fprintf(fic_repr,"%f unit %f unit moveto\n",(x-8)-(strlen(message)-1)*3.8,y-10);
	fprintf(fic_repr,"1 -1 scale\n");
    fprintf(fic_repr,"(%s) show\n",message);
	fprintf(fic_repr,"1 -1 scale\n");
	fprintf(fic_repr,"%f unit %f unit moveto\n",(x-8)-(strlen(reason)-1)*3.8,y+10);
	fprintf(fic_repr,"1 -1 scale\n");
	fprintf(fic_repr,"(%s) show\n",reason);
	fprintf(fic_repr,"grestore\n");
	
}


