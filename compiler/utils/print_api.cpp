/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ************************************************************************
 ************************************************************************/

#include <sstream>

#include "print_api.hh"
#include "global.hh"
#include "ppbox.hh"
#include "ppsig.hh"

using namespace std;

LIBFAUST_API string printSignal(Tree sig, bool shared, int max_size)
{
    // Clear print state
    gGlobal->clear();
    stringstream str;
    if (shared) {
        ppsigShared(sig, str, max_size);
    } else {
        str << ppsig(sig, max_size) << endl;
    }
    return str.str();
}

LIBFAUST_API string printBox(Tree box, bool shared, int max_size)
{
    // Clear print state
    gGlobal->clear();
    stringstream str;
    if (shared) {
        boxppShared(box, str);
    } else {
        str << mBox(box, max_size) << endl;
    }
    return str.str();
}
