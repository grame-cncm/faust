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

#if !defined SVGDEV_H
#define SVGDEV_H

#include <iostream>
#include <fstream>

#include "device.h"

#ifdef EMCC
#define JSLINKSTATUS true
#else
#define JSLINKSTATUS false
#endif

class SVGDev : public device {
   private:
	std::ofstream fOutStream;
	bool fJSLink = JSLINKSTATUS;		// a flag to use js for links (i.e. function call) instead of xlink:href
	std::string fCurrentPath;			// the path of the current svg folder 
	std::string getJSLink(const char* link) const;

	inline std::ostream& outstream() 	{ return fOutStream; }
	
	std::string startlink(const char* link);
	void		endlink(const char* link);
	const char*	rectColor2Style(const std::string color) const;
	std::string	getStyle(const std::string& file) const;

   public:
    SVGDev(const char*, double, double);
    ~SVGDev();
    void rect(double x, double y, double l, double h, const char* color, const char* link);
    void triangle(double x, double y, double l, double h, const char* color, const char* link, bool leftright);
    void rond(double x, double y, double rayon);
    void carre(double x, double y, double cote);
    void fleche(double x, double y, double rotation, int sens);
    void trait(double x1, double y1, double x2, double y2);
    void dasharray(double x1, double y1, double x2, double y2);
    void text(double x, double y, const char* name, const char* link);
    void label(double x, double y, const char* name);
    void markSens(double x, double y, int sens);
    void Error(const char* message, const char* reason, int nb_error, double x, double y, double largeur);
};

#endif
