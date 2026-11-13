/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <algorithm>

#include "clockRegionSchema.h"
#include "exception.hh"

using namespace std;

const double clockRegionSchema::fTopMargin(30);
const double clockRegionSchema::fHorMargin(10);
const double clockRegionSchema::fBotMargin(10);
const double clockRegionSchema::fMinWidth(50);

schema* makeClockRegionSchema(schema* s, const string& name, const string& rate)
{
    return new clockRegionSchema(s, name, rate);
}

/**
 * A frame around the schema, with room above it for the keyword and the rate input.
 */
clockRegionSchema::clockRegionSchema(schema* s, const string& name, const string& rate)
    : schema(s->inputs() + 1, s->outputs(),
             max(max(fMinWidth, s->width() + 2 * fHorMargin), (4 + name.size()) * dLetter),
             s->height() + fTopMargin + fBotMargin),
      fSchema(s),
      fName(name),
      fRate(rate)
{
    for (unsigned int i = 0; i < inputs(); i++) {
        fInputPoint.push_back(point(0, 0));
    }
    for (unsigned int i = 0; i < outputs(); i++) {
        fOutputPoint.push_back(point(0, 0));
    }
}

/**
 * Define the graphic position of the schema. Computes the graphic
 * position of all the elements, in particular the inputs and outputs.
 * This method must be called before draw(), otherwise draw is not allowed
 */
void clockRegionSchema::place(double ox, double oy, int orientation)
{
    double hmargin = (width() - fSchema->width()) / 2;

    beginPlace(ox, oy, orientation);
    if (orientation == kLeftRight) {
        fSchema->place(ox + hmargin, oy + fTopMargin, orientation);

        // the rate input, above the inputs of the body
        fInputPoint[0] = point(ox + fHorMargin / 2, oy + 2 * fTopMargin / 3);
        for (unsigned int i = 1; i < inputs(); i++) {
            point p        = fSchema->inputPoint(i - 1);
            fInputPoint[i] = point(ox + fHorMargin / 2, p.y);
        }
        for (unsigned int i = 0; i < outputs(); i++) {
            point p         = fSchema->outputPoint(i);
            fOutputPoint[i] = point(ox + width() - fHorMargin / 2, p.y);
        }
    } else {
        fSchema->place(ox + hmargin, oy + fBotMargin, orientation);

        fInputPoint[0] = point(ox + width() - fHorMargin / 2, oy + height() - 2 * fTopMargin / 3);
        for (unsigned int i = 1; i < inputs(); i++) {
            point p        = fSchema->inputPoint(i - 1);
            fInputPoint[i] = point(ox + width() - fHorMargin / 2, p.y);
        }
        for (unsigned int i = 0; i < outputs(); i++) {
            point p         = fSchema->outputPoint(i);
            fOutputPoint[i] = point(ox + fHorMargin / 2, p.y);
        }
    }
    endPlace();
}

point clockRegionSchema::inputPoint(unsigned int i) const
{
    faustassert(placed());
    faustassert(i < inputs());
    return fInputPoint[i];
}

point clockRegionSchema::outputPoint(unsigned int i) const
{
    faustassert(placed());
    faustassert(i < outputs());
    return fOutputPoint[i];
}

/**
 * Draw the frame, the keyword and the rate input. This method can only
 * be called after the schema has been placed
 */
void clockRegionSchema::draw(device& dev)
{
    faustassert(placed());

    fSchema->draw(dev);

    // the coordinates of the frame
    double tw = (2 + fName.size()) * dLetter;
    double x0 = x() + fHorMargin / 2;             // left
    double y0 = y() + fHorMargin / 2;             // top
    double x1 = x() + width() - fHorMargin / 2;   // right
    double y1 = y() + height() - fHorMargin / 2;  // bottom

    dev.trait(x0, y0, x0, y1);
    dev.trait(x0, y1, x1, y1);
    dev.trait(x1, y1, x1, y0);
    dev.trait(x0, y0, x1, y0);

    // the orientation mark
    if (orientation() == kLeftRight) {
        dev.markSens(x0, y0, orientation());
    } else {
        dev.markSens(x1, y1, orientation());
    }

    // the arrow of the rate input
    point p = fInputPoint[0];
    dev.fleche(p.x, p.y, 0, orientation());

    // the keyword, centered, and the label of the rate input
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;
    if (orientation() == kLeftRight) {
        dev.label(x0 + (width() - tw) / 2, y0 + 5, fName.c_str());
        dev.label(p.x + 2, p.y, fRate.c_str());
    } else {
        dev.label(x0 + (width() - tw) / 2, y1 - 5, fName.c_str());
        dev.label(p.x - 16 - dx, p.y, fRate.c_str());
    }
}

/**
 * The wires from the frame to the inputs and outputs of the body. The rate input
 * stops at the frame.
 */
void clockRegionSchema::collectTraits(collector& c)
{
    faustassert(placed());

    fSchema->collectTraits(c);

    c.addInput(inputPoint(0));
    for (unsigned int i = 1; i < inputs(); i++) {
        point p = inputPoint(i);
        point q = fSchema->inputPoint(i - 1);
        c.addInput(q);
        c.addTrait(trait(p, q));  // in->out direction
    }
    for (unsigned int i = 0; i < outputs(); i++) {
        point q = fSchema->outputPoint(i);
        point p = outputPoint(i);
        c.addOutput(q);
        c.addTrait(trait(q, p));  // in->out direction
    }
}
