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
 
#include "node.hh"
#include "math.h"
#include <stdlib.h>

ostream& Node::print (ostream& fout) const 					///< print a node on a stream
{
	switch (fType) {
		case kIntNode : 	return fout << fData.i;
		case kDoubleNode : 	return fout << fData.f;
		case kSymNode : 	return fout << *(fData.s);
		case kPointerNode : return fout << "ptr:" << fData.p;
		default : 			return fout << "badnode";
	}
}

//-----------------------------------------------------------------------------
// sameMagnitude(a,b) : true if the two nodes a and b represent numbers of same
//  absolute value. Int promoted to double if needed.
//

bool sameMagnitude(const Node& a, const Node& b)
{
    if (a.type() == kDoubleNode) {
        if (b.type() == kDoubleNode) {
            return fabs(a.getDouble()) == fabs(b.getDouble());
        } else if (b.type() == kIntNode) {
            return fabs(a.getDouble()) == fabs(double(b.getInt()));
        } else {
            return false;
        }
    } else if (a.type() == kIntNode) {
        if (b.type() == kDoubleNode) {
            return fabs(double(a.getInt())) == fabs(b.getDouble());
        } else if (b.type() == kIntNode) {
            return abs(a.getInt()) == abs(b.getInt());
        } else {
            return false;
        }
    } else {
        return false;
    }
}
