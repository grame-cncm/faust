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
#include <algorithm>

#include "exception.hh"

using namespace std;

enum {kHorDir, kUpDir, kDownDir}; ///< directions of connections

static double computeHorzGap(schema* a, schema* b);
static int direction(const point& a, const point& b);

//----------------------------INTERFACE--------------------------------

/**
 * Make a sequential schema. May add cables to ensure the internal
 * connections are between the same number of outputs and inputs.
 * Compute an horizontal gap based on the number of upward and
 * downward connections.
 */
schema* makeSeqSchema (schema* s1, schema* s2)
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
	faustassert(s1->outputs() == s2->inputs());
}

//-----------------------placement------------------------------


/**
 * Place the two components horizontally with enough space
 * for the connections
 */
void seqSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	double y1 = max(0.0, 0.5*(fSchema2->height() - fSchema1->height()));
	double y2 = max(0.0, 0.5*(fSchema1->height() - fSchema2->height()));

	if (orientation == kLeftRight) {
		fSchema1->place(ox, oy+y1, orientation);
		fSchema2->place(ox+fSchema1->width()+fHorzGap, oy+y2, orientation);
	} else {
		fSchema2->place(ox, oy+y2, orientation);
		fSchema1->place(ox+fSchema2->width()+fHorzGap, oy+y1, orientation);
	}
	endPlace();
}

/**
 * The input points are the input points of the first component
 */
point seqSchema::inputPoint(unsigned int i) const
{
	return fSchema1->inputPoint(i);
}

/**
 * The output points are the output points of the second component
 */
point seqSchema::outputPoint(unsigned int i) const
{
	return fSchema2->outputPoint(i);
}

//--------------------------drawing------------------------------
/**
 * Draw the two components as well as the internal wires
 */
void seqSchema::draw(device& dev)
{
    faustassert(placed());
    faustassert(fSchema1->outputs() == fSchema2->inputs());

    fSchema1->draw(dev);
    fSchema2->draw(dev);
    //drawInternalWires(dev);
}

/**
 * Draw the two components as well as the internal wires
 */
void seqSchema::collectTraits(collector& c)
{
    faustassert(placed());
    faustassert(fSchema1->outputs() == fSchema2->inputs());

    fSchema1->collectTraits(c);
    fSchema2->collectTraits(c);
    collectInternalWires(c);
}

/**
 * Draw the internal wires aligning the vertical segments in
 * a symetric way when possible.
 */

void seqSchema::drawInternalWires(device& dev)
{
	faustassert(fSchema1->outputs() == fSchema2->inputs());

	const int 	N 	= fSchema1->outputs();
	double 		dx 	= 0;
	double		mx 	= 0;
	int			dir	=-1;

	if (orientation() == kLeftRight) {
		// draw left right cables
		for (int i=0; i<N; i++) {
			point src = fSchema1->outputPoint(i);
			point dst = fSchema2->inputPoint(i);

            int d = direction(src,dst);
            if (d != dir) {
                // compute attributes of new direction
                switch (d) {
                    case kUpDir 	: mx = 0; dx = dWire; break;
                    case kDownDir	: mx = fHorzGap; dx = -dWire; break;
                    default			: mx = 0; dx = 0; break;
                }
                dir = d;
            } else {
                // move in same direction
                mx = mx +dx;
            }
            if (src.y == dst.y) {
                // draw straight cable
                dev.trait(src.x, src.y, dst.x, dst.y);
            } else {
                // draw zizag cable
                dev.trait(src.x, src.y, src.x+mx, src.y);
                dev.trait(src.x+mx, src.y, src.x+mx, dst.y);
                dev.trait(src.x+mx, dst.y, dst.x, dst.y);
            }

        }
	} else {
		// draw right left cables
		for (int i=0; i<N; i++) {
			point src = fSchema1->outputPoint(i);
			point dst = fSchema2->inputPoint(i);

            int d = direction(src,dst);
            if (d != dir) {
                // compute attributes of new direction
                switch (d) {
                    case kUpDir 	: mx = -fHorzGap; dx = dWire; break;
                    case kDownDir	: mx = 0; dx = -dWire; break;
                    default			: mx = 0; dx = 0; break;
                }
                dir = d;
            } else {
                // move in same direction
                mx = mx +dx;
            }
            if (src.y == dst.y) {
                // draw straight cable
                dev.trait(src.x, src.y, dst.x, dst.y);
            } else {
                // draw zizag cable
                dev.trait(src.x, src.y, src.x+mx, src.y);
                dev.trait(src.x+mx, src.y, src.x+mx, dst.y);
                dev.trait(src.x+mx, dst.y, dst.x, dst.y);
            }

        }
	}
}

/**
 * Draw the internal wires aligning the vertical segments in
 * a symetric way when possible.
 */

void seqSchema::collectInternalWires(collector& c)
{
    faustassert(fSchema1->outputs() == fSchema2->inputs());

    const int 	N 	= fSchema1->outputs();
    double 		dx 	= 0;
    double		mx 	= 0;
    int			dir	=-1;

    if (orientation() == kLeftRight) {
        // draw left right cables
        for (int i=0; i<N; i++) {
            point src = fSchema1->outputPoint(i);
            point dst = fSchema2->inputPoint(i);

            int d = direction(src,dst);
            if (d != dir) {
                // compute attributes of new direction
                switch (d) {
                    case kUpDir 	: mx = 0; dx = dWire; break;
                    case kDownDir	: mx = fHorzGap; dx = -dWire; break;
                    default			: mx = 0; dx = 0; break;
                }
                dir = d;
            } else {
                // move in same direction
                mx = mx +dx;
            }
            if (src.y == dst.y) {
                // draw straight cable
                c.addTrait(trait(point(src.x, src.y), point(dst.x, dst.y)));
            } else {
                // draw zizag cable
                c.addTrait(trait(point(src.x, src.y), point(src.x+mx, src.y)));
                c.addTrait(trait(point(src.x+mx, src.y), point(src.x+mx, dst.y)));
                c.addTrait(trait(point(src.x+mx, dst.y), point(dst.x, dst.y)));
            }

        }
    } else {
        // draw right left cables
        for (int i=0; i<N; i++) {
            point src = fSchema1->outputPoint(i);
            point dst = fSchema2->inputPoint(i);

            int d = direction(src,dst);
            if (d != dir) {
                // compute attributes of new direction
                switch (d) {
                    case kUpDir 	: mx = -fHorzGap; dx = dWire; break;
                    case kDownDir	: mx = 0; dx = -dWire; break;
                    default			: mx = 0; dx = 0; break;
                }
                dir = d;
            } else {
                // move in same direction
                mx = mx +dx;
            }
            if (src.y == dst.y) {
                // draw straight cable
                c.addTrait(trait(point(src.x, src.y), point(dst.x, dst.y)));
            } else {
                // draw zizag cable
                c.addTrait(trait(point(src.x, src.y), point(src.x+mx, src.y)));
                c.addTrait(trait(point(src.x+mx, src.y), point(src.x+mx, dst.y)));
                c.addTrait(trait(point(src.x+mx, dst.y), point(dst.x, dst.y)));
            }

        }
    }
}

//--------------------------helpers------------------------------
/**
 * Compute the direction of a connection. Note that
 * Y axis goes from top to bottom
 */
static int direction(const point& a, const point& b)
{
	if (a.y > b.y) return kUpDir; 		// upward connections
	if (a.y < b.y) return kDownDir; 	// downward connection
	return kHorDir;						// horizontal connections
}

/**
 * Compute the horizontal gap needed to draw the internal wires.
 * It depends on the largest group of connections that go in the same
 * direction.
 */
static double computeHorzGap(schema* a, schema* b)
{
	faustassert(a->outputs() == b->inputs());

	if (a->outputs() == 0) {
		return 0;
	} else {
		// store here the size of the largest group for each direction
		int	MaxGroupSize[3]; for(int i=0; i<3; i++) MaxGroupSize[i]=0;

		// place a and b to have valid connection points
		double ya = max(0.0, 0.5*(b->height() - a->height()));
		double yb = max(0.0, 0.5*(a->height() - b->height()));
		a->place(0,ya,kLeftRight);
		b->place(0,yb,kLeftRight);

		// init current group direction and size
		int	gdir 	= direction(a->outputPoint(0), b->inputPoint(0));
		int	gsize 	= 1;

		// analyze direction of remaining points
		for (unsigned int i=1; i<a->outputs(); i++) {
			int d = direction(a->outputPoint(i), b->inputPoint(i));
			if (d == gdir) {
				gsize++;
			} else {
				if (gsize > MaxGroupSize[gdir])  MaxGroupSize[gdir]=gsize;
				gsize = 1;
				gdir = d;
			}
		}

		// update for last group
		if (gsize > MaxGroupSize[gdir])  MaxGroupSize[gdir]=gsize;

		// the gap required for the connections
		return dWire * max(MaxGroupSize[kUpDir],MaxGroupSize[kDownDir]);
	}
}
