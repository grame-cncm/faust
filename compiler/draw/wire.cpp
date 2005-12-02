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
 
 
 
// wire.cpp


#include "wire.h"
#include <iostream>
#include <vector>
#include <set>

using namespace std;

wire::wire()
{
	blockEndCut=false;
	linked=false;
	carre.x1=-1; // <-> no square at the wire's construction (only if recursion)
}

wire::~wire()
{

}


void wire::draw(device& dev)
{
	int i,j;
	if(blockEndCut==false && linked==false)
	{
		for(i=0;i<(int)lSeg.size();i++)
		{
			dev.trait(lSeg[i].x1,lSeg[i].y1,lSeg[i].x2,lSeg[i].y2);
			if(!linkedTo.empty())
			{
				for(j=0;j<(int)linkedTo.size();j++)
				{
					linkedTo[j]->linked=false;
					linkedTo[j]->draw(dev);
				}
			}
		}
		if(carre.x1 >= 0)
			dev.carre(carre.x1,carre.x2,carre.y1);
	}
}

static void checkjoint(const segment& a, const segment& b)
{
	if (a.x2 == b.x1 && a.y2 == b.y1) {
	} else {
		fprintf(stderr, "join [%f,%f : %f,%f] [%f,%f : %f,%f]\n", a.x1, a.y1, a.x2, a.y2, b.x1, b.y1, b.x2, b.y2);
	} 
}
set<segment> gSegSet;

void wire::addSeg(float x1,float y1,float x2,float y2)
{
	segment s(x1,y1,x2,y2);
	if (gSegSet.find(s) !=  gSegSet.end()) {
		//fprintf(stderr, "segment already exists  [%f,%f : %f,%f] \n", s.x1, s.y1, s.x2, s.y2);
		return;
	}
	gSegSet.insert(s);
	//if (lSeg.size() > 0) { checkjoint(lSeg[lSeg.size()-1], s); }
	lSeg.push_back(s);
}

void wire::addSeg(float x2,float y2)
{
	segment s(lSeg[lSeg.size()-1].x2,lSeg[lSeg.size()-1].y2,x2,y2);
	if (gSegSet.find(s) !=  gSegSet.end()) {
		//fprintf(stderr, "segment already exists  [%f,%f : %f,%f] \n", s.x1, s.y1, s.x2, s.y2);
		return;
	}
	gSegSet.insert(s);
	lSeg.push_back(s);
}

void wire::addSeg(segment s)
{
	if (gSegSet.find(s) !=  gSegSet.end()) {
		//fprintf(stderr, "segment already exists  [%f,%f : %f,%f] \n", s.x1, s.y1, s.x2, s.y2);
		return;
	}
	gSegSet.insert(s);
	//if (lSeg.size() > 0) { checkjoint(lSeg[lSeg.size()-1], s); }
	lSeg.push_back(s);
}

void wire::addLinkedTo(wire* pw)
{
	linkedTo.push_back(pw);
}


void wire::setCarre(float x,float y,float cote)
{
	carre.x1=x;
	carre.x2=y;
	carre.y1=cote;
}



