/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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
#include <iostream>

#include "exception.hh"
#include "global.hh"
#include "routeSchema.h"

using namespace std;

/**
 * Build n x m cable routing
 */

schema* makeRouteSchema(unsigned int inputs, unsigned int outputs, const std::vector<int>& routes)
{
    // determine the optimal size of the box
    double minimal = 3 * dWire;
    double h       = 2 * dVert + max(minimal, max(inputs, outputs) * dWire);
    double w       = 2 * dHorz + max(minimal, h * 0.75);

    return new routeSchema(inputs, outputs, w, h, routes);
}

/**
 * Build a simple colored routeSchema with a certain number of
 * inputs and outputs, a text to be displayed, and an optional link.
 * The length of the text as well as the number of inputs and outputs
 * are used to compute the size of the routeSchema
 */
routeSchema::routeSchema(unsigned int inputs, unsigned int outputs, double width, double height,
                         const std::vector<int>& routes)

    : schema(inputs, outputs, width, height), fText(""), fColor("#EEEEAA"), fLink(""), fRoutes(routes)
{
    for (unsigned int i = 0; i < inputs; i++) fInputPoint.push_back(point(0, 0));
    for (unsigned int i = 0; i < outputs; i++) fOutputPoint.push_back(point(0, 0));
}

/**
 * Define the graphic position of the routeSchema. Computes the graphic
 * position of all the elements, in particular the inputs and outputs.
 * This method must be called before draw(), otherwise draw is not allowed
 */
void routeSchema::place(double x, double y, int orientation)
{
    beginPlace(x, y, orientation);

    placeInputPoints();
    placeOutputPoints();

    endPlace();
}

/**
 * Returns an input point
 */
point routeSchema::inputPoint(unsigned int i) const
{
    faustassert(placed());
    faustassert(i < inputs());
    return fInputPoint[i];
}

/**
 * Returns an output point
 */
point routeSchema::outputPoint(unsigned int i) const
{
    faustassert(placed());
    faustassert(i < outputs());
    return fOutputPoint[i];
}

/**
 * Computes the input points according to the position and the
 * orientation of the routeSchema
 */
void routeSchema::placeInputPoints()
{
    int N = inputs();

    if (orientation() == kLeftRight) {
        double px = x();
        double py = y() + (height() - dWire * (N - 1)) / 2;

        for (int i = 0; i < N; i++) {
            fInputPoint[i] = point(px, py + i * dWire);
        }

    } else {
        double px = x() + width();
        double py = y() + height() - (height() - dWire * (N - 1)) / 2;

        for (int i = 0; i < N; i++) {
            fInputPoint[i] = point(px, py - i * dWire);
        }
    }
}

/**
 * Computes the output points according to the position and the
 * orientation of the routeSchema
 */
void routeSchema::placeOutputPoints()
{
    int N = outputs();

    if (orientation() == kLeftRight) {
        double px = x() + width();
        double py = y() + (height() - dWire * (N - 1)) / 2;

        for (int i = 0; i < N; i++) {
            fOutputPoint[i] = point(px, py + i * dWire);
        }

    } else {
        double px = x();
        double py = y() + height() - (height() - dWire * (N - 1)) / 2;

        for (int i = 0; i < N; i++) {
            fOutputPoint[i] = point(px, py - i * dWire);
        }
    }
}

/**
 * Draw the routeSchema on the device. This method can only
 * be called after the routeSchema have been placed
 */
void routeSchema::draw(device& dev)
{
    faustassert(placed());

    if (gGlobal->gDrawRouteFrame) {
        drawRectangle(dev);
        // drawText(dev);
        drawOrientationMark(dev);
        drawInputArrows(dev);
    }
}

/**
 * Draw the colored rectangle with the optional link
 */
void routeSchema::drawRectangle(device& dev)
{
    dev.rect(x() + dHorz, y() + dVert, width() - 2 * dHorz, height() - 2 * dVert, fColor.c_str(), fLink.c_str());
}

/**
 * Draw the text centered on the box
 */
void routeSchema::drawText(device& dev)
{
    dev.text(x() + width() / 2, y() + height() / 2, fText.c_str(), fLink.c_str());
}

/**
 * Draw the orientation mark, a small point that indicates
 * the first input (like integrated circuits)
 */
void routeSchema::drawOrientationMark(device& dev)
{
    double px, py;

    if (orientation() == kLeftRight) {
        px = x() + dHorz;
        py = y() + dVert;
    } else {
        px = x() + width() - dHorz;
        py = y() + height() - dVert;
    }

    dev.markSens(px, py, orientation());
}

/**
 * Draw horizontal arrows from the input points to the
 * routeSchema rectangle
 */
void routeSchema::drawInputArrows(device& dev)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i = 0; i < inputs(); i++) {
        point p = fInputPoint[i];
        dev.fleche(p.x + dx, p.y, 0, orientation());
    }
}

/**
 * Draw horizontal arrows from the input points to the
 * routeSchema rectangle
 */
bool routeSchema::isValidRoute(int src, int dst) const
{
    return (src > 0) && (src <= (int)inputs()) && (dst > 0) && (dst <= (int)outputs());
}

void routeSchema::collectTraits(collector& c)
{
    collectInputWires(c);
    collectOutputWires(c);
    // additional routing traits
    for (unsigned int i = 0; i < fRoutes.size() - 1; i += 2) {
        if (isValidRoute(fRoutes[i], fRoutes[i + 1])) {
            int   src = fRoutes[i] - 1;
            int   dst = fRoutes[i + 1] - 1;
            point p1  = fInputPoint[src];
            point p2  = fOutputPoint[dst];
            // cerr << "add traits: " << p1.x << 'x' << p1.y << " -> " << p2.x << "x" << p2.y << endl;
            double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;
            c.addTrait(trait(point(p1.x + dx, p1.y), point(p2.x - dx, p2.y)));
        }
    }
}

/**
 * Draw horizontal arrows from the input points to the
 * routeSchema rectangle
 */
void routeSchema::collectInputWires(collector& c)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i = 0; i < inputs(); i++) {
        point p = fInputPoint[i];
        c.addTrait(trait(point(p.x, p.y), point(p.x + dx, p.y)));  // in->out direction
        c.addInput(point(p.x + dx, p.y));
    }
}

/**
 * Draw horizontal line from the routeSchema rectangle to the
 * output points
 */
void routeSchema::collectOutputWires(collector& c)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i = 0; i < outputs(); i++) {
        point p = fOutputPoint[i];
        c.addTrait(trait(point(p.x - dx, p.y), point(p.x, p.y)));  // in->out direction
        c.addOutput(point(p.x - dx, p.y));
    }
}

#if 0
/**
 * Build n x m cable routing
 */
routeSchema::routeSchema(unsigned int n, unsigned int m, const std::vector<int>& routes)
    : schema(n, m, max(n, m) * dWire, max(n, m) * dWire)
{
    fRoutes = routes;
    for (unsigned int i = 0; i < n; i++) fInputPoints.push_back(point(0, 0));
    for (unsigned int i = 0; i < m; i++) fOutputPoints.push_back(point(0, 0));
}

/**
 * Place the communication points vertically spaced by dWire
 */
void routeSchema::place(double ox, double oy, int orientation)
{
    // std::cerr << "\nENTER route place of " << this << " at " << ox << 'x' << oy << endl;
    double diy = (height() - inputs() * dWire + dWire) / 2.0;
    double doy = (height() - outputs() * dWire + dWire) / 2.0;

    beginPlace(ox, oy, orientation);
    if (orientation == kLeftRight) {
        // std::cerr << "orientation == kLeftRight" << endl;
        for (unsigned int i = 0; i < inputs(); i++) {
            fInputPoints[i] = point(ox, oy + diy + i * dWire);
            // std::cerr << "input point :" << fInputPoints[i].x << 'x' << fInputPoints[i].y << endl;
        }
        for (unsigned int i = 0; i < outputs(); i++) {
            fOutputPoints[i] = point(ox + width(), oy + doy + i * dWire);
            // std::cerr << "output point: " << fInputPoints[i].x << 'x' << fInputPoints[i].y << endl;
        }
    } else {
        // std::cerr << "orientation == kRightLeft" << endl;
        for (unsigned int i = 0; i < outputs(); i++) {
            fOutputPoints[i] = point(ox, oy + height() - doy - i * dWire);
            // std::cerr << "output point: " << fInputPoints[i].x << 'x' << fInputPoints[i].y << endl;
        }
        for (unsigned int i = 0; i < inputs(); i++) {
            fInputPoints[i] = point(ox + width(), oy + height() - diy - i * dWire);
            // std::cerr << "input point :" << fInputPoints[i].x << 'x' << fInputPoints[i].y << endl;
        }
    }
    endPlace();
    // std::cerr << "EXIT route place " << ox << 'x' << oy << "\n" << endl;
}

/**
 * Nothing to draw. Actual drawing will take place when the wires
 * are enlargered
 */
void routeSchema::draw(device& dev)
{
}

/**
 * Nothing to collect. Actual collect will take place when the wires
 * are enlargered
 */
void routeSchema::collectTraits(collector& c)
{
    faustassert(placed());

    // draw the connections between them
    // std::cerr << "fRoutes.size() = " << fRoutes.size() << endl;
    if (fRoutes.size() >= 2) {
        unsigned int m = fRoutes.size() - 1;
        for (unsigned int i = 0; i < m; i += 2) {
            unsigned int src = fRoutes[i];
            unsigned int dst = fRoutes[i + 1];
            if ((src > 0) && (src <= inputs()) && (dst > 0) && (dst <= outputs())) {
                c.addTrait(trait(point(fInputPoints[src].x, fInputPoints[src].y),
                                 point(fOutputPoints[dst].x, fOutputPoints[dst].y)));

                // c.addInput(fInputPoints[src]);
                // c.addOutput(fOutputPoints[dst]);
            }
        }
    }
}

/**
 *input and output points are the same as the width is 0
 */
point routeSchema::inputPoint(unsigned int i) const
{
    faustassert(i < inputs());
    return fInputPoints[i];
}

/**
 *input and output points are the same as the width is 0
 */
point routeSchema::outputPoint(unsigned int i) const
{
    faustassert(i < outputs());
    return fOutputPoints[i];
}

#endif
