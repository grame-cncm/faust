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

#include <stdlib.h>
#include <iostream>
#include <cstdlib>

#include "exception.hh"
#include "topSchema.h"

using namespace std;

/**
 * Creates a new top schema
 */
schema* makeTopSchema (schema* s, double margin, const string& text, const string& link)
{
	return new topSchema (makeDecorateSchema(s, margin/2, text), margin/2, "", link);
}

/**
 * A topSchema is a schema surrounded by a dashed rectangle with a
 * label on the top left. The rectangle is placed at half the margin
 * parameter. Arrows are added to the outputs. The constructor is
 * made private to enforce the usage of makeTopSchema.
 */
topSchema::topSchema( schema* s, double margin, const string& text, const string& link )
	: 	schema(0, 0, s->width()+2*margin, s->height()+2*margin),
	 	fSchema(s),
	 	fMargin(margin),
	 	fText(text),
	 	fLink(link)
{}

/**
 * Define the graphic position of the schema. Computes the graphic
 * position of all the elements, in particular the inputs and outputs.
 * This method must be called before draw(), otherwise draw is not allowed
 */
void topSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	fSchema->place(ox+fMargin, oy+fMargin, orientation);
	endPlace();
}

/**
 * Top schema has no input
 */
point topSchema::inputPoint(unsigned int i) const
{
	faustassert(placed());
	faustassert(i < inputs());
    throw faustexception("topSchema::inputPoint\n");
}

/**
 * Top schema has no output
 */
point topSchema::outputPoint(unsigned int i) const
{
	faustassert(placed());
	faustassert(i < outputs());
    throw faustexception("topSchema::outputPoint\n");
}

/**
 * Draw the enlarged schema. This methos can only
 * be called after the block have been placed
 */
void topSchema::draw(device& dev)
{
    faustassert(placed());

    // draw a background white rectangle
    dev.rect(x(), y(), width()-1, height()-1, "#ffffff", fLink.c_str());

    // draw the label
    dev.label(x()+fMargin, y()+fMargin/2, fText.c_str());

    fSchema->draw(dev);

    // draw arrows at output points of schema
    for (unsigned int i=0; i<fSchema->outputs(); i++) {
        point p = fSchema->outputPoint(i);
        dev.fleche(p.x, p.y, 0, orientation());
    }
}

/**
 * Draw the enlarged schema. This methos can only
 * be called after the block have been placed
 */
void topSchema::collectTraits(collector& c)
{
    faustassert(placed());
    fSchema->collectTraits(c);

    // draw arrows at output points of schema
    for (unsigned int i=0; i<fSchema->inputs(); i++) {
        point p = fSchema->inputPoint(i);
        c.addOutput(p);;
    }

    // draw arrows at output points of schema
    for (unsigned int i=0; i<fSchema->outputs(); i++) {
        point p = fSchema->outputPoint(i);
        c.addInput(p);;
    }
}
