
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

#include "inverterSchema.h"
#include "exception.hh"

using namespace std;

/**
 * Build n cables in parallel
 */
schema* makeInverterSchema (const string& color)
{
    return new inverterSchema(color);
}

/**
 * Build n cables in parallel
 */
inverterSchema::inverterSchema(const string& color)
    : 	blockSchema (1, 1, 2.5*dWire, dWire, "-1", color, "")
{}

/**
 * Nothing to draw. Actual drawing will take place when the wires
 * are enlargered
 */
void inverterSchema::draw(device& dev)
{
    dev.triangle(x() + dHorz, y()+0.5, width() - 2*dHorz, height()-1, fColor.c_str(),fLink.c_str(), orientation()==kLeftRight);
}
