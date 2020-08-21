/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include "exception.hh"
#include "ondemandSchema.h"

using namespace std;

const double ondemandSchema::fTopMargin(30);     // gap between the top and the top of the inside schema
const double ondemandSchema::fHorMargin(10);     // left and right gap
const double ondemandSchema::fBotMargin(10);     // gap between the bottom and the bottom of the inside schema
const string ondemandSchema::fText("ondemand");  // Test to display, tipically "ondemand"

/**
 * Returns an enlarged schema, but only if really needed
 * that is if the required width is greater that the schema width.
 */
schema* makeOndemandSchema(schema* s)
{
    return new ondemandSchema(s);
}

/**
 * Put additional space left and right of a schema so that the result has
 * a certain width. The wires are prolonged accordingly.
 */
ondemandSchema::ondemandSchema(schema* s)
    : schema(s->inputs() + 1, s->outputs(), s->width() + 2 * fHorMargin, s->height() + fTopMargin + fBotMargin),
      fSchema(s)
{
    for (unsigned int i = 0; i < inputs(); i++) fInputPoint.push_back(point(0, 0));
    for (unsigned int i = 0; i < outputs(); i++) fOutputPoint.push_back(point(0, 0));
}

/**
 * Define the graphic position of the schema. Computes the graphic
 * position of all the elements, in particular the inputs and outputs.
 * This method must be called before draw(), otherwise draw is not allowed
 */
void ondemandSchema::place(double ox, double oy, int orientation)
{
    if (orientation == kLeftRight) {
        beginPlace(ox, oy, orientation);

        fSchema->place(ox + fHorMargin, oy + fTopMargin, orientation);

        double m = fHorMargin;
        if (orientation == kRightLeft) {
            m = -m;
        }

        fInputPoint[0] = point(ox + fHorMargin / 2, oy + 2 * fTopMargin / 3);  // this is the clock entry
        for (unsigned int i = 1; i < inputs(); i++) {
            point p        = fSchema->inputPoint(i - 1);
            fInputPoint[i] = point(ox + fHorMargin / 2, p.y);
        }

        for (unsigned int i = 0; i < outputs(); i++) {
            point p         = fSchema->outputPoint(i);
            fOutputPoint[i] = point(p.x + m, p.y);
        }

        endPlace();

    } else {
        beginPlace(ox, oy, orientation);

        fSchema->place(ox + width() - fHorMargin - fSchema->width(), oy + height() - fTopMargin - fSchema->height(),
                       orientation);

        double m = fHorMargin;
        if (orientation == kRightLeft) {
            m = -m;
        }

        fInputPoint[0] = point(ox + width() - fHorMargin / 2, oy + height() - 2 * fTopMargin / 3);
        for (unsigned int i = 1; i < inputs(); i++) {
            point p        = fSchema->inputPoint(i - 1);
            fInputPoint[i] = point(ox + width() - fHorMargin / 2, p.y);
        }
        for (unsigned int i = 0; i < outputs(); i++) {
            point p         = fSchema->outputPoint(i);
            fOutputPoint[i] = point(p.x + m, p.y);
        }

        endPlace();
    }
}

/**
 * Returns an input point
 */
point ondemandSchema::inputPoint(unsigned int i) const
{
    faustassert(placed());
    faustassert(i < inputs());
    return fInputPoint[i];
}

/**
 * Returns an output point
 */
point ondemandSchema::outputPoint(unsigned int i) const
{
    faustassert(placed());
    faustassert(i < outputs());
    return fOutputPoint[i];
}

/**
 * Draw the enlarged schema. This methods can only
 * be called after the block have been placed
 */
void ondemandSchema::draw(device& dev)
{
    faustassert(placed());

    fSchema->draw(dev);

    // define the coordinates of the frame
    double tw = (2 + fText.size()) * dLetter;
    double x0 = x() + fHorMargin / 2;             // left
    double y0 = y() + fHorMargin / 2;             // top
    double x1 = x() + width() - fHorMargin / 2;   // right
    double y1 = y() + height() - fHorMargin / 2;  // bottom
    // double tl = x0 + 2*dWire;					// left of text zone
    double tl = x() + fHorMargin;  // left of text zone
    // double tr = min(tl + tw, x1);  // right of text zone

    // draw the surronding frame
    dev.trait(x0, y0, x0, y1);  // left line
    dev.trait(x0, y1, x1, y1);  // bottom line
    dev.trait(x1, y1, x1, y0);  // right line
    dev.trait(x0, y0, x1, y0);  // top segment

    // draw orientation mark
    if (orientation() == kLeftRight) {
        dev.markSens(x0, y0, orientation());
    } else {
        dev.markSens(x1, y1, orientation());
    }

    // draw clock arrow
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;
    // for (unsigned int i = 0; i < inputs(); i++) {
    point p = fInputPoint[0];
    dev.fleche(p.x, p.y, 0, orientation());
    //}

    // draw the ondemand label
    // dev.label(tl, y0, fText.c_str());  //
    // draw text
    if (orientation() == kLeftRight) {
        dev.label(x0 + (width() - tw) / 2, y0 + 5, "ondemand");
    } else {
        dev.label(x0 + (width() - tw) / 2, y1 - 5, "ondemand");
    }

    // draw clock label
    point p0 = fInputPoint[0];
    // dev.label(p0.x - 32 - dx, p0.y, "CLOCK");  //
    if (orientation() == kLeftRight) {
        dev.label(p0.x + 2, p0.y, "clock");  //
    } else {
        dev.label(p0.x - 22 - dx, p0.y, "clock");  //
    }
}

/**
 * Draw the enlarged schema. This methos can only
 * be called after the block have been placed
 */
void ondemandSchema::collectTraits(collector& c)
{
    faustassert(placed());

    fSchema->collectTraits(c);

    c.addInput(inputPoint(0));
    // draw enlarge input wires
    for (unsigned int i = 1; i < inputs(); i++) {
        point p = inputPoint(i);
        point q = fSchema->inputPoint(i - 1);
        c.addInput(q);
        c.addTrait(trait(p, q));  // in->out direction
    }

    // draw enlarge output wires
    for (unsigned int i = 0; i < outputs(); i++) {
        point q = fSchema->outputPoint(i);
        point p = outputPoint(i);
        c.addOutput(q);
        c.addTrait(trait(q, p));  // in->out direction
    }
}
