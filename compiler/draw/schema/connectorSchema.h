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

#ifndef __connectorSchema__
#define __connectorSchema__


#include "schema.h"
#include <vector>
#include <string>

/**
 * A simple rectangular box with a text and inputs and outputs.
 * The constructor is private in order to make sure
 * makeconnectorSchema is used instead
 */
class connectorSchema : public schema
{
  protected:
    // fields only defined after place() is called
    vector<point>	fInputPoint;	///< input connection points
    vector<point>	fOutputPoint;	///< output connection points


  public:
    friend schema*  makeConnectorSchema ();

    virtual void 	place(double x, double y, int orientation);
    virtual void 	draw(device& dev);
    virtual point	inputPoint(unsigned int i) const;
    virtual point 	outputPoint(unsigned int i) const;
    virtual void    collectTraits(collector& c);

  protected:
    connectorSchema ();

    void placeInputPoints();
    void placeOutputPoints();
    void collectInputWires(collector& c);
    void collectOutputWires(collector& c);

};

#endif


