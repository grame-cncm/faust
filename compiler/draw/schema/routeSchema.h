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

#ifndef __ROUTESCHEMA__
#define __ROUTESCHEMA__

#include <string>
#include <vector>
#include "schema.h"

using namespace std;

/**
 * A simple rectangular box with a text and inputs and outputs.
 * The constructor is private in order to make sure
 * makeBlockSchema is used instead
 */
class routeSchema : public schema {
   protected:
    const string           fText;    ///< Text to be displayed
    const string           fColor;   ///< color of the box
    const string           fLink;    ///< option URL link
    const std::vector<int> fRoutes;  ///< route description: s1,d2,s2,d2,...

    // fields only defined after place() is called
    vector<point> fInputPoint;   ///< input connection points
    vector<point> fOutputPoint;  ///< output connection points

   public:
    friend schema* makeRouteSchema(unsigned int n, unsigned int m, const std::vector<int>& routes);
    // friend schema* makeRoutingSchema(unsigned int inputs, unsigned int outputs, const vector<int>& route);
    virtual void  place(double x, double y, int orientation);
    virtual void  draw(device& dev);
    virtual point inputPoint(unsigned int i) const;
    virtual point outputPoint(unsigned int i) const;
    virtual void  collectTraits(collector& c);

   protected:
    routeSchema(unsigned int inputs, unsigned int outputs, double width, double height, const std::vector<int>& routes);

    void placeInputPoints();
    void placeOutputPoints();

    void drawRectangle(device& dev);
    void drawText(device& dev);
    void drawOrientationMark(device& dev);
    void drawInputArrows(device& dev);
    //    void drawOutputWires(device& dev);

    void collectInputWires(collector& c);
    void collectOutputWires(collector& c);

    bool isValidRoute(int src, int dst) const;
};

#endif
