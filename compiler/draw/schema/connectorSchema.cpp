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

#include "connectorSchema.h"
#include "exception.hh"

using namespace std;

/**
 * Connectors are used to ensure unused inputs and outputs
 * are drawn
 */
schema* makeConnectorSchema()
{
    return new connectorSchema();
}

/**
 * A connector is an invisible square fo dWire size
 * with 1 input and 1 output
 */
connectorSchema::connectorSchema() : schema(1, 1, dWire, dWire)
{
    fInputPoint.push_back(point(0,0));
    fOutputPoint.push_back(point(0,0));
}

/**
 * Define the graphic position of the connectorSchema. Computes the graphic
 * position of all the elements, in particular the inputs and outputs.
 * This method must be called before draw(), otherwise draw is not allowed
 */
void connectorSchema::place(double x, double y, int orientation)
{
    beginPlace(x, y, orientation);

    placeInputPoints();
    placeOutputPoints();

    endPlace();
}

/**
 * Returns an input point
 */
point connectorSchema::inputPoint(unsigned int i) const
{
    faustassert(placed());
    faustassert(i < inputs());
    return fInputPoint[i];
}

/**
 * Returns an output point
 */
point connectorSchema::outputPoint(unsigned int i) const
{
    faustassert(placed());
    faustassert(i < outputs());
    return fOutputPoint[i];
}

/**
 * Computes the input points according to the position and the
 * orientation of the connectorSchema
 */
void connectorSchema::placeInputPoints()
{
    int N = inputs();

    if (orientation() == kLeftRight) {

        double 	px = x();
        double 	py = y() + (height() - dWire*(N-1))/2;

        for (int i=0; i<N; i++) {
            fInputPoint[i] = point(px, py+i*dWire);
        }

    } else {

        double px = x() + width();
        double py = y() + height() - (height() - dWire*(N-1))/2;

        for (int i=0; i<N; i++) {
            fInputPoint[i] = point(px, py-i*dWire);
        }
    }
}

/**
 * Computes the output points according to the position and the
 * orientation of the connectorSchema
 */
void connectorSchema::placeOutputPoints()
{
    int N = outputs();

    if (orientation() == kLeftRight) {

        double px = x() + width();
        double py = y() + (height() - dWire*(N-1))/2;

        for (int i=0; i<N; i++) {
            fOutputPoint[i] = point(px, py + i*dWire);
        }

    } else {

        double px = x();
        double py = y() + height() - (height() - dWire*(N-1))/2;

        for (int i=0; i<N; i++) {
            fOutputPoint[i] = point(px, py - i*dWire);
        }
    }
}

/**
 * Draw the connectorSchema on the device. This methos can only
 * be called after the connectorSchema have been placed
 */
void connectorSchema::draw(device& dev)
{
    faustassert(placed());
    // nothing to do
}

/**
 * Draw horizontal arrows from the input points to the
 * connectorSchema rectangle
 */
void connectorSchema::collectTraits(collector& c)
{
    collectInputWires(c);
    collectOutputWires(c);
}

/**
 * Draw horizontal arrows from the input points to the
 * connectorSchema rectangle
 */
void connectorSchema::collectInputWires(collector& c)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i=0; i<inputs(); i++) {
        point p = fInputPoint[i];
        c.addTrait(trait(point(p.x, p.y), point(p.x+dx, p.y)));     // in->out direction
        c.addInput(point(p.x+dx, p.y));
    }
}

/**
 * Draw horizontal line from the connectorSchema rectangle to the
 * output points
 */
void connectorSchema::collectOutputWires(collector& c)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i=0; i<outputs(); i++) {
        point p = fOutputPoint[i];
        c.addTrait(trait(point(p.x-dx, p.y), point(p.x, p.y)));     // in->out direction
        c.addOutput(point(p.x-dx, p.y));
    }
}
