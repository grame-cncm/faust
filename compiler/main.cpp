/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
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
#include "global.hh"
#include "export.hh"
#include "exception.hh"
#include "compatibility.hh"

// Standalone compiler uses the real 'alarm' function
unsigned faust_alarm(unsigned seconds)
{
    return alarm(seconds);
}

int main(int argc, const char* argv[])
{
    gGlobal = NULL;

    try {
        global::allocate();
        compile_faust_internal(argc, argv, 0, 0, true);
    } catch (faustexception& e) {
        if (e.Message().size() > 0) {
            e.PrintMessage();
            exit(1);
        }
    }

    global::destroy();
    return 0;
}
