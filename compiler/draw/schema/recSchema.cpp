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

#include "exception.hh"
#include "recSchema.h"

using namespace std;

/**
 * Creates a new recursive schema (s1 ~ s2). The smallest component is
 * enlarged to the width of the other. The left and right horizontal
 * margins are computed according to the number of internal connections.
 */
schema* makeRecSchema (schema* s1, schema* s2)
{
	schema*	a = makeEnlargedSchema(s1, s2->width());
	schema*	b = makeEnlargedSchema(s2, s1->width());
	double 	m = dWire * max(b->inputs(), b->outputs());
	double 	w = a->width() + 2*m;

	return new recSchema(a,b,w);
}

/**
 * Constructor of a recursive schema (s1 ~ s2). The two components
 * are supposed to have the same width.
 */
recSchema::recSchema (schema* s1, schema* s2, double width)
	: 	schema(	s1->inputs() - s2->outputs(),
				s1->outputs(),
				width,
				s1->height() + s2->height() ),
		fSchema1(s1),
		fSchema2(s2)
{
	// this version only accepts legal expressions of same width
	faustassert(s1->inputs() >= s2->outputs());
	faustassert(s1->outputs() >= s2->inputs());
	faustassert(s1->width() >= s2->width());

	// create the input and output points
    for (unsigned int i=0; i<inputs(); i++) 	fInputPoint.push_back(point(0,0));
    for (unsigned int i=0; i<outputs(); i++) 	fOutputPoint.push_back(point(0,0));

}

/**
 * The two subschema are placed centered vertically, s2 on top of s1.
 * The input and output points are computed.
 */
void recSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	double dx1 = (width() - fSchema1->width())/2;
	double dx2 = (width() - fSchema2->width())/2;

	// place the two sub diagrams
	if (orientation == kLeftRight) {
		fSchema2->place(ox+dx2, oy, kRightLeft);
		fSchema1->place(ox+dx1, oy+fSchema2->height(), kLeftRight);
	} else {
		fSchema1->place(ox+dx1, oy, kRightLeft);
		fSchema2->place(ox+dx2, oy+fSchema1->height(), kLeftRight);
	}


	// adjust delta space to orientation
	if (orientation == kRightLeft) { dx1 = -dx1; }

	// place input points
	for (unsigned int i=0; i<inputs(); i++) {
		point p = fSchema1->inputPoint(i+fSchema2->outputs());
		fInputPoint[i] = point(p.x-dx1, p.y);
	}

	// place output points
	for (unsigned int i=0; i<outputs(); i++) {
		point p = fSchema1->outputPoint(i);
		fOutputPoint[i] = point(p.x+dx1, p.y);
	}

	endPlace();
}


/**
 * The input points s1 ~ s2
 */
point recSchema::inputPoint(unsigned int i) const
{
	return fInputPoint[i];
}


/**
 * The output points s1 ~ s2
 */
point recSchema::outputPoint(unsigned int i) const
{
	return fOutputPoint[i];
}


/**
 * Draw the two subschema s1 and s2 as well as the implicit feedback
 * delays between s1 and s2.
 */
void recSchema::draw(device& dev)
{
    faustassert(placed());

    // draw the two subdiagrams
    fSchema1->draw(dev);
    fSchema2->draw(dev);

    // draw the implicit feedback delay to each fSchema2 input
    double dw = (orientation()==kLeftRight) ? dWire : -dWire;
    for (unsigned int i=0; i<fSchema2->inputs(); i++) {
        const point& p = fSchema1->outputPoint(i);
        drawDelaySign(dev, p.x + i*dw, p.y, dw/2);

    }
}

/**
 * Draw the delay sign of a feedback connection
 */
void recSchema::drawDelaySign(device& dev, double x, double y, double size)
{
    dev.trait(x-size/2, y, x-size/2, y-size);
    dev.trait(x-size/2, y-size, x+size/2, y-size);
    dev.trait(x+size/2, y-size, x+size/2, y);
}


/**
 * Draw the two subschema s1 and s2 as well as the feedback
 * connections between s1 and s2, and the feedfrom connections
 * beetween s2 and s1.
 */
void recSchema::collectTraits(collector& c)
{
    faustassert(placed());

    // draw the two subdiagrams
    fSchema1->collectTraits(c);
    fSchema2->collectTraits(c);

    // draw the feedback connections to each fSchema2 input
    for (unsigned int i=0; i<fSchema2->inputs(); i++) {
        collectFeedback(c, fSchema1->outputPoint(i), fSchema2->inputPoint(i), i*dWire, outputPoint(i));
    }

    // draw the non recursive output lines
    for (unsigned int i=fSchema2->inputs(); i<outputs(); i++) {
        point p = fSchema1->outputPoint(i);
        point q = outputPoint(i);
        c.addTrait(trait(p,q));     // in->out order
    }

    // draw the input lines
    unsigned int skip = fSchema2->outputs();
    for (unsigned int i=0; i<inputs(); i++) {
        point p = inputPoint(i);
        point q = fSchema1->inputPoint(i+skip);
        c.addTrait(trait(p,q));     // in->out order
    }

    // draw the feedfront connections from each fSchema2 output
    for (unsigned int i=0; i<fSchema2->outputs(); i++) {
        collectFeedfront(c, fSchema2->outputPoint(i), fSchema1->inputPoint(i), i*dWire);
    }
}



/**
 * Draw a feedback connection between two points with an horizontal
 * displacement dx
 */
void recSchema::collectFeedback(collector& c, const point& src, const point& dst, double dx, const point& out)
{
    double	ox = src.x + ((orientation()==kLeftRight) ? dx : -dx);
    double	ct = (orientation()==kLeftRight) ? dWire/2 : -dWire/2;

    point   up(ox, src.y-ct);
    point   br(ox+ct/2.0, src.y);

    c.addOutput(up);
    c.addOutput(br);
    c.addInput(br);

    c.addTrait(trait(up, point(ox, dst.y)));
    c.addTrait(trait(point(ox, dst.y), point(dst.x, dst.y)));
    c.addTrait(trait(src,br));
    c.addTrait(trait(br,out));

}


/**
 * Draw a feedfrom connection between two points with an horizontal
 * displacement dx
 */
void recSchema::collectFeedfront(collector& c, const point& src, const point& dst, double dx)
{
    double	ox = src.x + ((orientation()==kLeftRight) ? -dx : dx);

    c.addTrait(trait(point(src.x, src.y), point(ox, src.y)));
    c.addTrait(trait(point(ox, src.y), point(ox, dst.y)));
    c.addTrait(trait(point(ox, dst.y), point(dst.x, dst.y)));
}
