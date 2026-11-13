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

#ifndef __CLOCKREGIONSCHEMA__
#define __CLOCKREGIONSCHEMA__

#include <string>
#include <vector>

#include "schema.h"

/**
 * The frame of a clock region : ondemand, upsampling or downsampling. It has one input
 * more than the schema it encloses, the rate of the derived clock, drawn first. The
 * constructor is private : use makeClockRegionSchema.
 */

class clockRegionSchema : public schema {
    static const double fTopMargin;  // gap between the top and the top of the inside schema
    static const double fHorMargin;  // left and right gap
    static const double fBotMargin;  // gap between the bottom and the bottom of the inside schema
    static const double fMinWidth;   // minimal width of a region

    schema*            fSchema;       // the schema inside the region
    std::string        fName;         // the keyword, displayed on the frame
    std::string        fRate;         // the label of the rate input
    std::vector<point> fInputPoint;   // input points
    std::vector<point> fOutputPoint;  // output points

   public:
    friend schema* makeClockRegionSchema(schema* s, const std::string& name, const std::string& rate);

    virtual void  place(double ox, double oy, int orientation);
    virtual void  draw(device& dev);
    virtual point inputPoint(unsigned int i) const;
    virtual point outputPoint(unsigned int i) const;
    virtual void  collectTraits(collector& c);

   private:
    clockRegionSchema(schema* s, const std::string& name, const std::string& rate);
};

#endif
