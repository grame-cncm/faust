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

#include "cutSchema.h"
#include "exception.hh"

using namespace std;

/**
 * Creates a new Cut schema.
 */
schema* makeCutSchema ()
{
	return new cutSchema();
}

/**
 * A Cut is represented by a small black dot. It has 1 input
 * and no outputs. It has a 0 width and a 1 wire height. The
 * constructor is private in order to enforce the usage of
 * makeCutSchema.
 */
cutSchema::cutSchema ()
    : schema (1, 0, 0, dWire/100.0), fPoint(0,0)
{}

/**
 * The input point is placed in the middle
 */
void cutSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);
    fPoint = point(ox, oy + height()*0.5); //, -1);
	endPlace();
}

/**
 * A cut is represented by a small black dot
 */
void cutSchema::draw(device& dev)
{
    //dev.rond(fPoint.x, fPoint.y, dWire/8.0);
}

void cutSchema::collectTraits(collector& c)
{}

/**
 * By definition a Cut has only one input point
 */
point cutSchema::inputPoint(unsigned int i) const
{
	faustassert(i==0);
	return fPoint;
}

/**
 * By definition a Cut has no output point
 */
point cutSchema::outputPoint(unsigned int) const
{
	faustassert(false);
    return point(-1,-1);
}
