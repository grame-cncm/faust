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

#include "enlargedSchema.h"
#include "exception.hh"

using namespace std;

/**
 * Returns an enlarged schema, but only if really needed
 * that is if the requiered width is greater that the schema width.
 */
schema* makeEnlargedSchema ( schema* s, double width )
{
	if (width > s->width()) {
		return new enlargedSchema(s, width);
	} else {
		return s;
	}
}

/**
 * Put additional space left and right of a schema so that the result has
 * a certain width. The wires are prolonged accordingly.
 */
enlargedSchema::enlargedSchema( schema* s, double width )
	: 	schema(s->inputs(), s->outputs(), width, s->height()),
	 	fSchema(s)
{
    for (unsigned int i=0; i<inputs(); i++) 	fInputPoint.push_back(point(0,0));
    for (unsigned int i=0; i<outputs(); i++) 	fOutputPoint.push_back(point(0,0));
}

/**
 * Define the graphic position of the schema. Computes the graphic
 * position of all the elements, in particular the inputs and outputs.
 * This method must be called before draw(), otherwise draw is not allowed
 */
void enlargedSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	double dx = (width() - fSchema->width())/2;
	fSchema->place(ox+dx, oy, orientation);

	if (orientation == kRightLeft) {
		dx = -dx;
	}

	for (unsigned int i=0; i < inputs(); i++) {
		point p = fSchema->inputPoint(i);
        fInputPoint[i] = point(p.x-dx, p.y); //, p.z);
	}

	for (unsigned int i=0; i < outputs(); i++) {
		point p = fSchema->outputPoint(i);
        fOutputPoint[i] = point(p.x+dx, p.y); //, p.z);
	}

	endPlace();
}

/**
 * Returns an input point
 */
point enlargedSchema::inputPoint(unsigned int i)	const
{
	faustassert(placed());
	faustassert(i < inputs());
	return fInputPoint[i];
}

/**
 * Returns an output point
 */
point enlargedSchema::outputPoint(unsigned int i)	const
{
	faustassert(placed());
	faustassert(i < outputs());
	return fOutputPoint[i];
}

/**
 * Draw the enlarged schema. This methos can only
 * be called after the block have been placed
 */
void enlargedSchema::draw(device& dev)
{
    faustassert(placed());

    fSchema->draw(dev);
#if 0
    // draw enlarge input wires
    for (unsigned int i=0; i<inputs(); i++) {
        point p = inputPoint(i);
        point q = fSchema->inputPoint(i);
        if ( (p.z>=0) && (q.z>=0) ) dev.trait(p.x, p.y, q.x, q.y);
    }

    // draw enlarge output wires
    for (unsigned int i=0; i<outputs(); i++) {
        point p = outputPoint(i);
        point q = fSchema->outputPoint(i);
        if ( (p.z>=0) && (q.z>=0) ) dev.trait(p.x, p.y, q.x, q.y);
    }
#endif
}

/**
 * Draw the enlarged schema. This methos can only
 * be called after the block have been placed
 */
void enlargedSchema::collectTraits(collector& c)
{
    faustassert(placed());

    fSchema->collectTraits(c);

    // draw enlarge input wires
    for (unsigned int i=0; i<inputs(); i++) {
        point p = inputPoint(i);
        point q = fSchema->inputPoint(i);
        c.addTrait(trait(p,q));     // in->out direction
    }

    // draw enlarge output wires
    for (unsigned int i=0; i<outputs(); i++) {
        point q = fSchema->outputPoint(i);
        point p = outputPoint(i);
        c.addTrait(trait(q,p));     // in->out direction
    }
}
