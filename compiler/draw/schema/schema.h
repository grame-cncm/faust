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

#ifndef __SCHEMA__
#define __SCHEMA__

#include "device.h"
#include "garbageable.hh"

#include <vector>
#include <string>
#include <set>

using namespace std;

const double dWire = 8; 			///< distance between two wires
//const double dLetter = 6;			///< width of a letter
const double dLetter = 4.3;			///< width of a letter
const double dHorz = 4;       		///< marge horizontale
const double dVert = 4;				///< marge verticale

struct point  : public virtual Garbageable
{
    double  x;
    double  y;

    point() : x(0.0), y(0.0) {}
    point(double u, double v) : x(u), y(v) {}
    point(const point& p) : x(p.x), y(p.y) {}

    bool operator<(const point& p) const {
        if (x < p.x)        return true;
        else if (x > p.x)   return false;
        else if (y < p.y)   return true;
        else                return false;
    }
};

struct trait : public virtual Garbageable
{
    point   start;
    point   end;
    bool    hasRealInput;
    bool    hasRealOutput;

    trait(const point& p1, const point& p2) : start(p1), end(p2)    {}
    void draw(device& dev) const { dev.trait(start.x, start.y, end.x, end.y); }

    bool operator<(const trait& t) const {
        if (start < t.start)        return true;
        else if (t.start < start)   return false;
        else if (end < t.end)       return true;
        else                        return false;
    }
};

struct collector : public virtual Garbageable 
{
    set<point>  fOutputs;       // collect real outputs
    set<point>  fInputs;        // collect real inputs
    set<trait>  fTraits;        // collect traits to draw
    set<trait>  fWithInput;     // collect traits with a real input
    set<trait>  fWithOutput;    // collect traits with a real output

    void addOutput(const point& p)  { fOutputs.insert(p); }
    void addInput(const point& p)   { fInputs.insert(p); }
    void addTrait(const trait& t)   { fTraits.insert(t); }
    void computeVisibleTraits();
    bool isVisible(const trait& t);
    void draw(device& dev);
};

enum { kLeftRight=1, kRightLeft=-1 };

/**
 * An abstract block diagram schema
 */
 
class schema : public virtual Garbageable
{
  private:
	const unsigned int	fInputs;
	const unsigned int	fOutputs;
	const double		fWidth;
	const double		fHeight;

	// fields only defined after place() is called
  	bool			fPlaced;		///< false until place() is called
	double 			fX;
	double 			fY;
	int				fOrientation;

  public:

 	schema(unsigned int inputs, unsigned int outputs, double width, double height)
 	 	: 	fInputs(inputs),
 	 		fOutputs(outputs),
 	 		fWidth(width),
 	 		fHeight(height),
 	 		fPlaced(false),
			fX(0),
			fY(0),
			fOrientation(0)
 	{}
  	virtual ~schema() {}

 	// constant fields
 	double			width()		const		{ return fWidth; }
 	double			height()	const		{ return fHeight; }
 	unsigned int	inputs()	const		{ return fInputs; }
 	unsigned int	outputs()	const		{ return fOutputs; }

 	// starts and end placement
	void 			beginPlace (double x, double y, int orientation)
							{ fX = x; fY = y; fOrientation = orientation; }
 	void			endPlace ()			{ fPlaced = true; }

 	// fields available after placement
 	bool			placed()	const		{ return fPlaced; }
 	double 			x()			const		{ return fX; }
	double 			y()			const		{ return fY; }
	int				orientation()	const	{ return fOrientation; }


 	// abstract interface for subclasses
	virtual void 	place(double x, double y, int orientation) 	= 0;
    virtual void 	draw(device& dev) 							= 0;
    virtual point	inputPoint(unsigned int i) const			= 0;
	virtual point 	outputPoint(unsigned int i)const			= 0;
    virtual void 	collectTraits(collector& c)					= 0;
};

// various functions to create schemas

schema* makeBlockSchema 	(unsigned int inputs,
							 unsigned int outputs,
  							 const string& name,
							 const string& color,
							 const string& link);
schema* makeCableSchema 	(unsigned int n=1);
schema* makeInverterSchema 	(const string& color);
schema* makeCutSchema 		();
schema* makeEnlargedSchema 	(schema* s, double width);
schema* makeParSchema 		(schema* s1, schema* s2);
schema* makeSeqSchema 		(schema* s1, schema* s2);
schema* makeMergeSchema 	(schema* s1, schema* s2);
schema* makeSplitSchema 	(schema* s1, schema* s2);
schema* makeRecSchema 		(schema* s1, schema* s2);
schema* makeTopSchema 		(schema* s1, double margin, const string& text, const string& link);
schema* makeDecorateSchema 	(schema* s1, double margin, const string& text);
schema* makeConnectorSchema ();

#endif


