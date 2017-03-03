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

#include "cableSchema.h"
#include "exception.hh"

using namespace std;

/**
 * Build n cables in parallel
 */
schema* makeCableSchema (unsigned int n)
{
	faustassert(n>0);
	return new cableSchema(n);
}

/**
 * Build n cables in parallel
 */
cableSchema::cableSchema (unsigned int n)
	: 	schema (n, n, 0, n*dWire)
{
    for (unsigned int i=0; i<n; i++) 	fPoint.push_back(point(0,0));
}

/**
 * Place the communication points vertically spaced by dWire
 */
void cableSchema::place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);
	if (orientation == kLeftRight) {
		for (unsigned int i=0; i<inputs(); i++) {
			fPoint[i] = point(ox, oy + dWire/2.0 + i*dWire);
		}
	} else {
		for (unsigned int i=0; i<inputs(); i++) {
			fPoint[i] = point(ox, oy + height() - dWire/2.0 - i*dWire);
		}
	}
	endPlace();
}

/**
 * Nothing to draw. Actual drawing will take place when the wires
 * are enlargered
 */
void cableSchema::draw(device& dev)
{}

/**
 * Nothing to collect. Actual collect will take place when the wires
 * are enlargered
 */
void cableSchema::collectTraits(collector& c)
{}

/**
 *input and output points are the same as the width is 0
 */
point cableSchema::inputPoint(unsigned int i) const
{
	faustassert(i<inputs());
	return fPoint[i];
}

/**
 *input and output points are the same as the width is 0
 */
point cableSchema::outputPoint(unsigned int i) const
{
	faustassert(i<outputs());
	return fPoint[i];
}
