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


#include "seqSchema.h"
#include <iostream>
#include <assert.h>

using namespace std;

static double computeHorzGap(schema* a, schema* b);


//----------------------------INTERFACE--------------------------------

/**
 * Make a sequential schema. May add cables to ensure the internal
 * connections are between the same number of outputs and inputs.
 * Compute an horizontal gap based on the number of upward and
 * downward connections.
 */
schema * makeSeqSchema (schema* s1, schema* s2)
{
	unsigned int o = s1->outputs();
	unsigned int i = s2->inputs();

	schema* a = (o < i) ? makeParSchema(s1, makeCableSchema(i-o)) : s1;
	schema* b = (o > i) ? makeParSchema(s2, makeCableSchema(o-i)) : s2;

	return new seqSchema(a, b, computeHorzGap(a,b));
}



//-----------------------IMPLEMENTATION------------------------------

/**
 * Constructor for a sequential schema (s1:s2). The components s1 and s2
 * are supposed to be "compatible" (s1 : n->m and s2 : m->q)
 */
seqSchema::seqSchema (schema* s1, schema* s2, double hgap)
	: 	schema(	s1->inputs(),
				s2->outputs(),
				s1->width() + hgap + s2->width(),
				max(s1->height(), s2->height()) ),
		fSchema1(s1),
		fSchema2(s2),
		fHorzGap(hgap)
{
	assert(s1->outputs() == s2->inputs());
}


//-----------------------placement------------------------------


/**
 * Place the two components horizontally with enough space
 * for the connections
 */
void seqSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	if (orientation == kLeftRight) {
		fSchema1->place(ox, oy, orientation);
		fSchema2->place(ox+fSchema1->width()+fHorzGap, oy, orientation);
	} else {
		fSchema2->place(ox, oy, orientation);
		fSchema1->place(ox+fSchema2->width()+fHorzGap, oy, orientation);
	}
	endPlace();
}


/**
 * The input points are the input points of the first component
 */
point seqSchema::inputPoint(unsigned int i)
{
	return fSchema1->inputPoint(i);
}


/**
 * The output points are the output points of the second component
 */
point seqSchema::outputPoint(unsigned int i)
{
	return fSchema2->outputPoint(i);
}



//--------------------------drawing------------------------------


/**
 * Draw the two components as well as the internal wires
 */
void seqSchema::draw(device& dev)
{
	assert(placed());
	assert(fSchema1->outputs() == fSchema2->inputs());

	fSchema1->draw(dev);
	fSchema2->draw(dev);
	drawInternalWires(dev);
}


/**
 * Draw the internal wires aligning the vertical segments in
 * a symetric way when possible.
 */
void seqSchema::drawInternalWires(device& dev)
{
	double 	dUp = 0;
	double 	dDw = 0;

	if (orientation() == kLeftRight) {

		for (unsigned int i=0; i<fSchema1->outputs(); i++) {

			point src = fSchema1->outputPoint(i);
			point dst = fSchema2->inputPoint(i);

			if (src.y > dst.y) 			{
				// draw an upward cable
				dev.trait(src.x, src.y, src.x+dUp, src.y);
				dev.trait(src.x+dUp, src.y, src.x+dUp, dst.y);
				dev.trait(src.x+dUp, dst.y, dst.x, dst.y);
				dUp += dWire;
			} else if (src.y < dst.y) 	{
				// draw an downward cable
				dev.trait(src.x, src.y, src.x+dDw, src.y);
				dev.trait(src.x+dDw, src.y, src.x+dDw, dst.y);
				dev.trait(src.x+dDw, dst.y, dst.x, dst.y);
				dDw += dWire;
			} else {
				dev.trait(src.x, src.y, dst.x, dst.y);
			}
		}

	} else {

		// draw connections starting from the end
		for (int i = int(fSchema1->outputs())-1; i >= 0; i--) {

			point src = fSchema1->outputPoint(i);
			point dst = fSchema2->inputPoint(i);

			if (src.y > dst.y) 			{
				// draw an upward cable
				dev.trait(src.x, src.y, src.x-dUp, src.y);
				dev.trait(src.x-dUp, src.y, src.x-dUp, dst.y);
				dev.trait(src.x-dUp, dst.y, dst.x, dst.y);
				dUp += dWire;
			} else if (src.y < dst.y) 	{
				// draw an downward cable
				dev.trait(src.x, src.y, src.x-dDw, src.y);
				dev.trait(src.x-dDw, src.y, src.x-dDw, dst.y);
				dev.trait(src.x-dDw, dst.y, dst.x, dst.y);
				dDw += dWire;
			} else {
				dev.trait(src.x, src.y, dst.x, dst.y);
			}
		}
	}
}



//--------------------------helpers------------------------------


/**
 * Compute the horizontal gap needed to draw the internal wires.
 */
static double computeHorzGap(schema* a, schema* b)
{
	assert(a->outputs() == b->inputs());

	// place a and b to have valid connection points
	a->place(0,0,kLeftRight);
	b->place(0,0,kLeftRight);

	// count the connection types according to the vertical differences
	int		up	=0;
	int 	down=0;
	for (unsigned int i=0; i<a->outputs(); i++) {

		point src = a->outputPoint(i);
		point dst = b->inputPoint(i);

		if (src.y > dst.y) 			{ up++;		}
		else if (src.y < dst.y) 	{ down++;	}
	}

	// the gap required for the connections
	return dWire * max(up,down);
}
