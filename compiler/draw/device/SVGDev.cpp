/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

// SVGDev.cpp

#include "SVGDev.h"
#include "exception.hh"
#include "global.hh"

#include <stdio.h>
#include <fstream>
#include <sstream>

#ifdef EMCC
#include <filesystem>
namespace fs = std::__fs::filesystem;
#endif

using namespace std;

static string xmlcode(const char* name)
{
    stringstream out;
    // SUBSTITUTION DES CARACTeRES INTERDITS EN XML
    while (*name) {
		char c = *name++;
		switch (c) {
            case '<':
                out << "&lt;";
                break;
            case '>':
                out << "&gt;";
                break;
            case '\'':
                out << "&apos;";
                break;
            case '"':
                out << "&quot;";
                break;
            case '&':
                out << "&amp;";
                break;
            default:
				out << c;
		}
    }
    return out.str();
}


SVGDev::SVGDev(const char* ficName, double largeur, double hauteur)
{
#ifdef EMCC
	fCurrentPath = fs::current_path();		// filesystem not supported by Visual Studio 15
#endif
    double gScale = 0.5;
    fOutStream = new ofstream (ficName);
    if (fOutStream->fail()) {
        stringstream error;
        error << "ERROR : impossible to create or open " << ficName << endl;
        throw faustexception(error.str());
    }

    // representation file:
    outstream() << "<?xml version=\"1.0\"?>" << endl;
	// + DTD ...
    // viewBox:
    const char* svgref = "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"";
    
    if (gGlobal->gScaledSVG) {
        outstream() << svgref << " viewBox=\"0 0 " << largeur << " " << hauteur << "\" width=\"100%%\" height=\"100%%\" version=\"1.1\">" << endl;
    } else {
        outstream() << svgref << " viewBox=\"0 0 " << largeur << " " << hauteur
					<< "\" width=\"" << largeur * gScale << "mm\" height=\"" << hauteur * gScale << "mm\" version=\"1.1\">" << endl;
    }

    if (gGlobal->gShadowBlur) {
        outstream() <<
				"<defs>\n"
                "   <filter id=\"filter\" filterRes=\"18\" x=\"0\" y=\"0\">\n"
                "     <feGaussianBlur in=\"SourceGraphic\" stdDeviation=\"1.55\" result=\"blur\"/>\n"
                "     <feOffset in=\"blur\" dx=\"3\" dy=\"3\"/>\n"
                "   </filter>\n"
                "</defs>" << endl;
    }
    outstream() << getStyle(gGlobal->gStyleFile.c_str()) << endl;
}

SVGDev::~SVGDev()
{
    outstream() << "</svg>" << endl;
    delete fOutStream;
}

static string toJSName(const char* path) {
	string name;
	while (*path) {
		char c = *path++;
		if (c!='-' && c!='/') name += c;
	}
	return name;
}

string SVGDev::getJSLink(const char* link) const
{
	string path = fCurrentPath + "/" + xmlcode(link);
	stringstream jslink;
	jslink << " onclick=\"" << toJSName(fCurrentPath.c_str()) << "('" << path << "')\"";
    return jslink.str();
}


std::string	SVGDev::getStyle (const string& styleFile) const
{
	string defaultStyle =
			"<style>\n"
			" .arrow {stroke:black; stroke-width:0.25; fill:none}\n"
			" .line  {stroke:black; stroke-linecap:round; stroke-width:0.25;}\n"
			" .dashline {stroke:black; stroke-linecap:round; stroke-width:0.25; stroke-dasharray:3,3;}\n"
			" .text  {font-family:Arial; font-size:7px; text-anchor:middle; fill:#FFFFFF;}\n"
			" .label {font-family:Arial; font-size:7px;}\n"
			" .error {stroke-width:0.3; fill:red; text-anchor:middle;}\n"
			" .reason{stroke-width:0.3; fill:none; text-anchor:middle;}\n"
			" .carre {stroke:black; stroke-width:0.5; fill:none;}\n"
			" .shadow{stroke:none; fill:#aaaaaa; filter:url(#filter);}\n"
			" .rect  {stroke:none;}\n"
			" .border {stroke:none; fill:#cccccc;}\n"
			" .linkbox {stroke:none; fill:#003366;}\n"
			" .normalbox {stroke:none; fill:#4B71A1;}\n"
			" .uibox {stroke:none; fill:#477881;}\n"
			" .slotbox {stroke:none; fill:#47945E;}\n"
			" .numcolorbox {stroke:none; fill:#f44800;}\n"
			" .invcolorbox {stroke:none; fill:#ffffff;}\n"
			" .link:hover { cursor:pointer;}\n"
			"</style>";

	if (styleFile.size()) {
		ifstream file (styleFile);
		if (file.is_open()) {
		    file.seekg (0, file.end);
			int length = int(file.tellg());
			file.seekg (0, file.beg);
			char * buffer = new char [length+1];
			file.read (buffer,length);
			buffer[length] = 0;
			string style(buffer);
			delete[] buffer;
			if (file.gcount() != length)
				cerr << "failed to read style file '" << styleFile << "'" << endl;
			else return style;
		}
		else cerr << "cannot open style file '" << styleFile << "'" << endl;
	}
	return defaultStyle;
}


const char*	SVGDev::rectColor2Style	(const string color) const
{
	if (color == "#003366") return "linkbox";
	if (color == "#4B71A1") return "normalbox";
	if (color == "#477881") return "uibox";
	if (color == "#47945E") return "slotbox";
	if (color == "#f44800") return "numcolorbox";
	if (color == "#ffffff") return "invcolorbox";
	return "rect";
}


string SVGDev::startlink (const char* link)
{
    if (link != 0 && link[0] != 0) {
		if (fJSLink)
			return getJSLink(link);
        else
			outstream() << "<a xlink:href=\"" << xmlcode(link) << "\">" << endl;
    }
    return "";
}

void SVGDev::endlink (const char* link)
{
	if (link != 0 && link[0] != 0 && !fJSLink) outstream() << "</a>" << endl;
}

void SVGDev::rect(double x, double y, double l, double h, const char* color, const char* link)
{
	string jslink = startlink(link);
    string rclass = (gGlobal->gShadowBlur) ? "shadow" : "border";
    string style = rectColor2Style(color);
    string lclass = (fJSLink) ? style + " link" : style;
	outstream() << "<rect x=\"" << x+1 << "\" y=\"" << y+1
				<< "\" width=\"" << l << "\" height=\"" << h
				<< "\" rx=\"0.1\" ry=\"0.1\" class=\"" << rclass << "\"/>" << endl;

    // draw the rectangle
	outstream() << "<rect x=\"" << x << "\" y=\"" << y
				<< "\" width=\"" << l << "\" height=\"" << h
				<< "\" rx=\"0\" ry=\"0\""
				<< " class=\"" << lclass << "\" " << jslink << "/>" << endl;
//				<< " style=\"fill:" << color << "\" class=\"" << lclass << "\" " << jslink << "/>" << endl;
	endlink(link);
}

//<polygon fill="lightsteelblue" stroke="midnightblue" stroke-width="5"
//    points="350,180 380,180 380,160 410,160 410,180 440,180 440,140 470,140 470,180
//    500,180 500,120 530,120 530,180" />

void SVGDev::triangle(double x, double y, double l, double h, const char* color, const char* link, bool leftright)
{
	string jslink = startlink(link);
    // draw triangle+circle
    float r = 1.5;  // circle radius
    float x0, x1, x2;
    if (leftright) {
        x0 = (float)x;
        x1 = (float)(x + l - 2 * r);
        x2 = (float)(x + l - r);
    } else {
        x0 = (float)(x + l);
        x1 = (float)(x + 2 * r);
        x2 = (float)(x + r);
    }
    string lclass = (fJSLink) ? " class=\"link\" " : " ";
    outstream() << "<polygon fill=\"" << color << "\" stroke=\"black\" stroke-width=\".25\""
				<< " points=\"" << x0 << "," << y << "," << x1 << "," << (y + h / 2.0f) << "," << x0 << "," << (y+h)
				<< lclass << jslink << "\"/>" << endl;
    outstream() << "<circle  fill=\"" << color << "\" stroke=\"black\" stroke-width=\".25\""
				<< " cx=\"" << x2 << "\" cy=\"" << (y + h / 2.0f) << "\" r=\"" << r << "\"/>" << lclass << jslink << endl;
	endlink(link);
}

void SVGDev::rond(double x, double y, double rayon)
{
    outstream() << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << rayon << "\"/>" << endl;
}

void SVGDev::fleche(double x, double y, double rotation, int sens)
{
    double dx = (sens == 1) ? 3 : -3;
    double dy = 1;
	outstream() << "<path d=\"M" << x-dx << " " << y-dy << " L" << x << " " << y << " L" << x-dx << " " << y+dy << "\" class=\"arrow\" />" << endl;
}

void SVGDev::carre(double x, double y, double cote)
{
    outstream() << "<rect x=\"" << (x - 0.5 * cote) << "\" y=\"" << (y - cote)
				<< "\" width=\"" << cote << "\" height=\"" << cote << "\" class=\"carre\"/>" << endl;
}

void SVGDev::trait(double x1, double y1, double x2, double y2)
{
    outstream() << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" class=\"line\"/>" << endl;
}

void SVGDev::dasharray(double x1, double y1, double x2, double y2)
{
    outstream() << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" class=\"dashline\"/>" << endl;
}

void SVGDev::text(double x, double y, const char* name, const char* link)
{
	string jslink = startlink(link);
	string tclass = (fJSLink) ? "text link" : "text";
	outstream() << "<text x=\"" << x << "\" y=\"" << y+2 << "\" class=\"" << tclass << "\" " << jslink << ">" << xmlcode(name) << "</text>" << endl;
	endlink(link);
}

void SVGDev::label(double x, double y, const char* name)
{
    outstream() << "<text x=\"" << x << "\" y=\"" << y+2 << "\" class=\"label\">" << xmlcode(name) << "</text>" << endl;
}

void SVGDev::markSens(double x, double y, int sens)
{
    int offset = (sens == 1) ? 2 : -2;
    outstream() << "<circle cx=\"" << x + offset << "\" cy=\"" << y + offset << "\" r=\"1\"/>" << endl;
}

void SVGDev::Error(const char* message, const char* reason, int nb_error, double x, double y, double largeur)
{
    outstream() << "<text x=\"" << x << "\" y=\"" << y-7 << "\"  textLength=\"" << largeur
				<< "\" lengthAdjust=\"spacingAndGlyphs\" class=\"error\">" << nb_error << " : " << message << "</text>" << endl;
    outstream() << "<text x=\"" << x << "\" y=\"" << y+7 << "\"  textLength=\"" << largeur
				<< "\" lengthAdjust=\"spacingAndGlyphs\" class=\"reason\"> " << reason << "</text>" << endl;
}
