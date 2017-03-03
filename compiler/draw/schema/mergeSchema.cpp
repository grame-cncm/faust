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

#include <iostream>
#include <algorithm>

#include "mergeSchema.h"
#include "exception.hh"

using namespace std;

/**
 * Creates a new merge schema. Cables are enlarged to dWire.
 * The horizontal gap between the two subschema is such that
 * the connections are not too slopy.
 */
schema* makeMergeSchema (schema* s1, schema* s2)
{
	// avoid ugly diagram by ensuring at least dWire width
	schema * a = makeEnlargedSchema(s1, dWire);
	schema * b = makeEnlargedSchema(s2, dWire);
	double	hgap = (a->height()+b->height())/4;
	return new mergeSchema(a,b,hgap);
}

/**
 * Constructor for a merge schema s1 :> s2 where the outputs
 * of s1 are merged to the inputs of s2. The constructor is
 * private in order to enforce the usage of makeMergeSchema
 */
mergeSchema::mergeSchema (schema* s1, schema* s2, double hgap)
	: 	schema(	s1->inputs(),
				s2->outputs(),
				s1->width() + s2->width() + hgap,
				max(s1->height(), s2->height()) ),
		fSchema1(s1),
		fSchema2(s2),
		fHorzGap(hgap)
{}

/**
 * Places the two subschema horizontaly, centered, with enough gap for
 * the connections
 */
void mergeSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	double dy1 = max(0.0, fSchema2->height()-fSchema1->height()) / 2.0;
	double dy2 = max(0.0, fSchema1->height()-fSchema2->height()) / 2.0;

	if (orientation == kLeftRight) {
		fSchema1->place(ox, oy+dy1, orientation);
		fSchema2->place(ox+fSchema1->width()+fHorzGap, oy+dy2, orientation);
	} else {
		fSchema2->place(ox, oy+dy2, orientation);
		fSchema1->place(ox+fSchema2->width()+fHorzGap, oy+dy1, orientation);
	}
	endPlace();
}

/**
 * The inputs of s1 :> s2 are the inputs of s1
 */
point mergeSchema::inputPoint(unsigned int i) const
{
	return fSchema1->inputPoint(i);
}

/**
 * The outputs of s1 :> s2 are the outputs of s2
 */
point mergeSchema::outputPoint(unsigned int i) const
{
	return fSchema2->outputPoint(i);
}

/**
 * Draw the two sub schema and the connections between them
 */
void mergeSchema::draw(device& dev)
{
    faustassert(placed());

    // draw the two subdiagrams
    fSchema1->draw(dev);
    fSchema2->draw(dev);

#if 0
    unsigned int r = fSchema2->inputs();
    faustassert(r>0);

    // draw the connections between them
    for (unsigned int i=0; i<fSchema1->outputs(); i++) {
        point p = fSchema1->outputPoint(i);
        point q = fSchema2->inputPoint(i%r);
        dev.trait(p.x, p.y, q.x, q.y);
    }
#endif
}

/**
 * Draw the two sub schema and the connections between them
 */
void mergeSchema::collectTraits(collector& c)
{
    faustassert(placed());

    // draw the two subdiagrams
    fSchema1->collectTraits(c);
    fSchema2->collectTraits(c);

    unsigned int r = fSchema2->inputs();
    faustassert(r>0);

    // draw the connections between them
    for (unsigned int i=0; i<fSchema1->outputs(); i++) {
        point p = fSchema1->outputPoint(i);
        point q = fSchema2->inputPoint(i%r);
        c.addTrait(trait(p,q));
    }
}
