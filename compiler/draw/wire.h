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
 
 
 
// wire.h

#include "device.h"
#include <vector>
using namespace std;

#if !defined WIRE_H
#define WIRE_H

class segment //(a wire is made of segments)
{
	public:
		segment() {};
		segment(float _x1,float _y1,float _x2,float _y2)
		{
			x2=_x2;
			x1=_x1;
			y2=_y2;
			y1=_y1;
		};
		~segment(){};

		float x1;
		float y1;
		float x2;
		float y2;
};

class wire  
{
	public:

		wire();
		~wire();

		// list of segments:
		vector<segment> getLSeg()			{ return lSeg; }
		void addSeg(segment);
		void addSeg(float,float);
		void addSeg(float,float,float,float);
		
		// list of linked wires:
		wire* getLinkedTo(int i)			{ return linkedTo[i]; }
		int getLinkedToSize()				{ return (int)linkedTo.size(); }
		void addLinkedTo(wire* pw);	
	
		// last segment:
		void setLastSegment(segment s)		{ lastSegment = s; }
		segment getLastSegment()			{ return lastSegment; }

		// blockEndCut, linked and carre:
		void setBlockEndCut(bool b)			{ blockEndCut = b;}
		void setLinked(bool b)				{ linked = b;}
		void setCarre(float,float,float);
		segment getCarre()					{ return carre; }

		// to draw the wire:
		void draw(device&);

	private:

		vector<segment> lSeg;   // wire's list of segments
		bool blockEndCut;		// for cut block
		bool linked;			// for merge
		vector<wire*> linkedTo; // for merge
		segment lastSegment;	// to find the arrow's direction
		segment carre;			// for recurs: carre=segment(x,y,cote_carre,X)
};


#endif 

