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

#ifndef __CABLESCHEMA__
#define __CABLESCHEMA__


#include "schema.h"

/**
 * Simple cables (identity box) in parallel. The width of a cable
 * is null. Therefore input and output connection points are the
 * same. The constructor is private to enforce the use of
 * makeCableSchema.
 */
class cableSchema : public schema
{
	vector<point>	fPoint;

  public:
    friend schema*  makeCableSchema (unsigned int n);

	virtual void 	place(double x, double y, int orientation);
	virtual void 	draw(device& dev);
	virtual point	inputPoint(unsigned int i)	const;
	virtual point 	outputPoint(unsigned int i)	const;
    virtual void    collectTraits(collector& c);
  private:
  	 cableSchema (unsigned int n);

};

#endif


