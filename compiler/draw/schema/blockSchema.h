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

#ifndef __BLOCKSCHEMA__
#define __BLOCKSCHEMA__

#include "schema.h"
#include <vector>
#include <string>

/**
 * A simple rectangular box with a text and inputs and outputs.
 * The constructor is private in order to make sure
 * makeBlockSchema is used instead
 */
class blockSchema : public schema
{
  protected:
	const string	fText;			///< Text to be displayed
	const string	fColor;			///< color of the box
    const string	fLink;			///< option URL link

	// fields only defined after place() is called
	vector<point>	fInputPoint;	///< input connection points
	vector<point>	fOutputPoint;	///< output connection points


  public:
    friend schema*  makeBlockSchema (	unsigned int inputs,
                                        unsigned int outputs,
                                        const string& name,
                                        const string& color,
                                        const string& link);

	virtual void 	place(double x, double y, int orientation);
	virtual void 	draw(device& dev);
	virtual point	inputPoint(unsigned int i) const;
	virtual point 	outputPoint(unsigned int i) const;
    virtual void    collectTraits(collector& c);

  protected:
	blockSchema (	unsigned int inputs, unsigned int outputs,
					double width, double height,
  					const string& name, const string& color,
                    const string& link);

	void placeInputPoints();
	void placeOutputPoints();

  	void drawRectangle(device& dev);
	void drawText(device& dev);
	void drawOrientationMark(device& dev);
    void drawInputArrows(device& dev);
//    void drawOutputWires(device& dev);

    void collectInputWires(collector& c);
    void collectOutputWires(collector& c);

};

#endif


