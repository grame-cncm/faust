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

#include "parSchema.h"
#include "exception.hh"

using namespace std;

schema* makeParSchema(schema* s1, schema* s2)
{
	// make sure s1 and s2 have same width
	return new parSchema( 	makeEnlargedSchema(s1, s2->width()),
							makeEnlargedSchema(s2, s1->width()) );
}

parSchema::parSchema (schema* s1, schema* s2)
	: 	schema(	s1->inputs()+s2->inputs(),
				s1->outputs()+s2->outputs(),
				s1->width(),
				s1->height() + s2->height() ),
		fSchema1(s1),
		fSchema2(s2),
		fInputFrontier(s1->inputs()),
		fOutputFrontier(s1->outputs())
{
	faustassert(s1->width() == s2->width());
}

void parSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	if (orientation == kLeftRight) {
		fSchema1->place(ox, oy, orientation);
		fSchema2->place(ox, oy+fSchema1->height(), orientation);
	} else {
		fSchema2->place(ox, oy, orientation);
		fSchema1->place(ox, oy+fSchema2->height(), orientation);
	}

	endPlace();
}

point parSchema::inputPoint(unsigned int i) const
{
	return (i < fInputFrontier)
		? fSchema1->inputPoint(i)
		: fSchema2->inputPoint(i-fInputFrontier);
}

point parSchema::outputPoint(unsigned int i) const
{
	return (i < fOutputFrontier)
		? fSchema1->outputPoint(i)
		: fSchema2->outputPoint(i-fOutputFrontier);
}

void parSchema::draw(device& dev)
{
    fSchema1->draw(dev);
    fSchema2->draw(dev);
}

void parSchema::collectTraits(collector& c)
{
    fSchema1->collectTraits(c);
    fSchema2->collectTraits(c);
}
