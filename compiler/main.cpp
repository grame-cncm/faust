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

#include "global.hh"
#include "exception.hh"

#ifdef __cplusplus
extern "C" int compile_faust_internal(int argc, char* argv[], const char* library_path, const char* draw_path, const char* name, const char* input);
#endif

int main(int argc, char* argv[])
{
    int res = 0;
    gGlobal = NULL;
   
    try {
        global::allocate();
        
        // Add time-out argument
        int argc1 = argc + 2;
        char* argv1[argc1];
        int i;
        for (i = 0; i < argc; i++) {
            argv1[i] = argv[i];
        }
        argv1[i++] = "-t";
        argv1[i++] = "120";

        res = compile_faust_internal(argc1, argv1, "", "", 0, 0);
    } catch (faustexception& e) {
        e.PrintMessage();
    }
    
    global::destroy();
    return res;
}
