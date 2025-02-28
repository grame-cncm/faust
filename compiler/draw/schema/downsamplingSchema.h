/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2025 GRAME, Centre National de Creation Musicale
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

#ifndef __DSSCHEMA__
#define __DSSCHEMA__

#include <string>
#include <vector>
#include "schema.h"

/**
 * downsampling box wrapper. The constructor is private because one
 * should use the makeDownsamplingSchema function instead.
 */

class downsamplingSchema : public schema {
    static const double fTopMargin;  // gap between the top and the top of the inside schema
    static const double fHorMargin;  // left and right gap
    static const double fBotMargin;  // gap between the bottom and the bottom of the inside schema
    static const double fMinWidth;   // gap between the bottom and the bottom of the inside schema

    static const std::string fText;         // Test to display, tipically "downsampling"
    schema*                  fSchema;       // the schema inside the on-demand box
    std::vector<point>       fInputPoint;   // input points
    std::vector<point>       fOutputPoint;  // output points

   public:
    friend schema* makeDownsamplingSchema(schema* s1);

    virtual void  place(double ox, double oy, int orientation);
    virtual void  draw(device& dev);
    virtual point inputPoint(unsigned int i) const;
    virtual point outputPoint(unsigned int i) const;
    virtual void  collectTraits(collector& c);

   private:
    downsamplingSchema(schema* s1);
    void drawInternalWires(device& dev);
    void collectInternalWires(collector& c);
};

schema* makeDownsamplingSchema(schema* s);

#endif
