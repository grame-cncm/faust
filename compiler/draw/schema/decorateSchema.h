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

#ifndef __DECORATESCHEMA__
#define __DECORATESCHEMA__


#include "schema.h"

/**
 * A decorateSchema is a schema surrounded by a dashed rectangle with a
 * label on the top left. The rectangle is placed at half the margin
 * parameter
 */

class decorateSchema : public schema
{
	schema*			fSchema;
	double			fMargin;
	string			fText;
	vector<point>	fInputPoint;
	vector<point>	fOutputPoint;

  public:
    friend schema*  makeDecorateSchema (schema* s1, double margin, const string& text);

	virtual void 	place(double ox, double oy, int orientation);
	virtual void 	draw(device& dev);
    virtual point	inputPoint(unsigned int i)	const;
	virtual point 	outputPoint(unsigned int i)	const;
    virtual void    collectTraits(collector& c);

  private:
	decorateSchema (schema* s1, double margin, const string& text);
};

#endif


