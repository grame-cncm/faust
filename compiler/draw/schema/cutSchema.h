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

#ifndef __CUTSCHEMA__
#define __CUTSCHEMA__

#include "schema.h"

/**
 * Terminate a cable (cut box)
 */
class cutSchema : public schema {
    point fPoint;

   public:
    friend schema* makeCutSchema();
    virtual void   place(double x, double y, int orientation);
    virtual void   draw(device& dev);
    virtual point  inputPoint(unsigned int i) const;
    virtual point  outputPoint(unsigned int i) const;
    virtual void   collectTraits(collector& c);

   private:
    cutSchema();
};

#endif
