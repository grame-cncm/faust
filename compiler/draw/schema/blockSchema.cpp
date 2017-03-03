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

#include <algorithm>

#include "blockSchema.h"
#include "exception.hh"

using namespace std;

static double quantize(int n)
{
	int q = 3;
	return dLetter * (q *((n+q-1)/q));
}


/**
 * Build a simple colored blockSchema with a certain number of
 * inputs and outputs, a text to be displayed, and an optional link.
 * Computes the size of the box according to the length of the text
 * and the maximum number of ports.
 */
schema* makeBlockSchema (unsigned int inputs,
                        unsigned int outputs,
                        const string& text,
                        const string& color,
                        const string& link)
{
    // determine the optimal size of the box
    double minimal = 3*dWire;
    double w = 2*dHorz + max( minimal, quantize((int)text.size()) );
    double h = 2*dVert + max( minimal, max(inputs, outputs) * dWire );

    return new blockSchema(inputs, outputs, w, h, text, color, link);
}

/**
 * Build a simple colored blockSchema with a certain number of
 * inputs and outputs, a text to be displayed, and an optional link.
 * The length of the text as well as th number of inputs and outputs
 * are used to compute the size of the blockSchema
 */
blockSchema::blockSchema (unsigned int inputs,
                        unsigned int outputs,
                        double width,
                        double height,
                        const string& text,
                        const string& color,
                        const string& link)

	: 	schema( inputs, outputs, width, height ),
	  	fText(text),
	  	fColor(color),
        fLink(link)
{
    for (unsigned int i=0; i<inputs; i++) 	fInputPoint.push_back(point(0,0));
    for (unsigned int i=0; i<outputs; i++) 	fOutputPoint.push_back(point(0,0));
}

/**
 * Define the graphic position of the blockSchema. Computes the graphic
 * position of all the elements, in particular the inputs and outputs.
 * This method must be called before draw(), otherwise draw is not allowed
 */
void blockSchema::place(double x, double y, int orientation)
{
	beginPlace(x, y, orientation);

	placeInputPoints();
	placeOutputPoints();

	endPlace();
}

/**
 * Returns an input point
 */
point blockSchema::inputPoint(unsigned int i) const
{
	faustassert(placed());
	faustassert(i < inputs());
	return fInputPoint[i];
}

/**
 * Returns an output point
 */
point blockSchema::outputPoint(unsigned int i) const
{
	faustassert(placed());
	faustassert(i < outputs());
	return fOutputPoint[i];
}

/**
 * Computes the input points according to the position and the
 * orientation of the blockSchema
 */
void blockSchema::placeInputPoints()
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
 * orientation of the blockSchema
 */
void blockSchema::placeOutputPoints()
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
 * Draw the blockSchema on the device. This methos can only
 * be called after the blockSchema have been placed
 */
void blockSchema::draw(device& dev)
{
	faustassert(placed());

	drawRectangle(dev);
	drawText(dev);
    drawOrientationMark(dev);
    drawInputArrows(dev);
}

/**
 * Draw the colored rectangle with the optional link
 */
void blockSchema::drawRectangle(device& dev)
{
	dev.rect(	x() + dHorz,
				y() + dVert,
				width() - 2*dHorz,
				height() - 2*dVert,
				fColor.c_str(),
				fLink.c_str()
			);
}

/**
 * Draw the text centered on the box
 */
void blockSchema::drawText(device& dev)
{
	dev.text( 	x() + width()/2,
				y() + height()/2,
                fText.c_str(),
                fLink.c_str()
			);
}

/**
 * Draw the orientation mark, a small point that indicates
 * the first input (like integrated circuits)
 */
void blockSchema::drawOrientationMark(device& dev)
{
	double px, py;

	if (orientation() == kLeftRight) {
		px = x() + dHorz;
		py = y() + dVert;
	} else {
		px = x() + width() - dHorz;
		py = y() + height() - dVert;
	}

	dev.markSens( px, py, orientation() );
}

/**
 * Draw horizontal arrows from the input points to the
 * blockSchema rectangle
 */
void blockSchema::drawInputArrows(device& dev)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i=0; i<inputs(); i++) {
        point p = fInputPoint[i];
        dev.fleche(p.x+dx, p.y, 0, orientation());
    }
}

/**
 * Draw horizontal arrows from the input points to the
 * blockSchema rectangle
 */
void blockSchema::collectTraits(collector& c)
{
    collectInputWires(c);
    collectOutputWires(c);
}

/**
 * Draw horizontal arrows from the input points to the
 * blockSchema rectangle
 */
void blockSchema::collectInputWires(collector& c)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i=0; i<inputs(); i++) {
        point p = fInputPoint[i];
        c.addTrait(trait(point(p.x, p.y), point(p.x+dx, p.y)));     // in->out direction
        c.addInput(point(p.x+dx, p.y));
    }
}

/**
 * Draw horizontal line from the blockSchema rectangle to the
 * output points
 */
void blockSchema::collectOutputWires(collector& c)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i=0; i<outputs(); i++) {
        point p = fOutputPoint[i];
        c.addTrait(trait(point(p.x-dx, p.y), point(p.x, p.y)));     // in->out direction
        c.addOutput(point(p.x-dx, p.y));
    }
}


