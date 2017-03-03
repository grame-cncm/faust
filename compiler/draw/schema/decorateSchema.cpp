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

#include "decorateSchema.h"
#include "exception.hh"

using namespace std;

/**
 * Creates a new decorated schema
 */
schema* makeDecorateSchema ( schema* s, double margin, const string& text )
{
	return new decorateSchema (s, margin, text);
}


/**
 * A decorateSchema is a schema surrounded by a dashed rectangle with a
 * label on the top left. The rectangle is placed at half the margin
 * parameter. The constructor is made private to enforce the usage of
 * makeDecorateSchema
 */
decorateSchema::decorateSchema( schema* s, double margin, const string& text )
	: 	schema(s->inputs(), s->outputs(), s->width()+2*margin, s->height()+2*margin),
	 	fSchema(s),
	 	fMargin(margin),
	 	fText(text)
{
    for (unsigned int i=0; i<inputs(); i++) 	fInputPoint.push_back(point(0,0));
    for (unsigned int i=0; i<outputs(); i++) 	fOutputPoint.push_back(point(0,0));
}


/**
 * Define the graphic position of the schema. Computes the graphic
 * position of all the elements, in particular the inputs and outputs.
 * This method must be called before draw(), otherwise draw is not allowed
 */
void decorateSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	fSchema->place(ox+fMargin, oy+fMargin, orientation);

	double m = fMargin;
	if (orientation == kRightLeft) {
		m = -m;
	}

	for (unsigned int i=0; i < inputs(); i++) {
		point p = fSchema->inputPoint(i);
        fInputPoint[i] = point(p.x-m, p.y); //, p.z);
	}

	for (unsigned int i=0; i < outputs(); i++) {
		point p = fSchema->outputPoint(i);
        fOutputPoint[i] = point(p.x+m, p.y); //, p.z);
	}

	endPlace();
}

/**
 * Returns an input point
 */
point decorateSchema::inputPoint(unsigned int i) const
{
	faustassert(placed());
	faustassert(i < inputs());
	return fInputPoint[i];
}

/**
 * Returns an output point
 */
point decorateSchema::outputPoint(unsigned int i) const
{
	faustassert(placed());
	faustassert(i < outputs());
	return fOutputPoint[i];
}

/**
 * Draw the enlarged schema. This methods can only
 * be called after the block have been placed
 */
void decorateSchema::draw(device& dev)
{
    faustassert(placed());

    fSchema->draw(dev);
#if 0
    // draw enlarge input wires
    for (unsigned int i=0; i<inputs(); i++) {
        point p = inputPoint(i);
        point q = fSchema->inputPoint(i);
        dev.trait(p.x, p.y, q.x, q.y);
    }

    // draw enlarge output wires
    for (unsigned int i=0; i<outputs(); i++) {
        point p = outputPoint(i);
        point q = fSchema->outputPoint(i);
        dev.trait(p.x, p.y, q.x, q.y);
    }
#endif
    // define the coordinates of the frame
    double tw = (2+fText.size())*dLetter*0.75;
    double x0 = x() + fMargin/2;				// left
    double y0 = y() + fMargin/2;				// top
    double x1 = x() + width() - fMargin/2;		// right
    double y1 = y() + height() - fMargin/2;		// bottom
    //double tl = x0 + 2*dWire;					// left of text zone
    double tl = x() + fMargin;					// left of text zone
    double tr = min(tl+tw, x1);					// right of text zone

    // draw the surronding frame
    dev.dasharray(x0, y0, x0, y1);				// left line
    dev.dasharray(x0, y1, x1, y1);				// bottom line
    dev.dasharray(x1, y1, x1, y0);				// right line
    dev.dasharray(x0, y0, tl, y0);				// top segment before text
    dev.dasharray(tr, y0, x1, y0);				// top segment after text

    // draw the label
    dev.label(tl, y0, fText.c_str());	//
}

/**
 * Draw the enlarged schema. This methods can only
 * be called after the block have been placed
 */
void decorateSchema::collectTraits(collector& c)
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
        point p = fSchema->outputPoint(i);
        point q = outputPoint(i);
        c.addTrait(trait(p,q));     // in->out direction
    }
}
