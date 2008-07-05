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
 

int isatty(int file) {return 0;}


#if defined( __MINGW32__) || defined (WIN32)
#include <windows.h>

    void getFaustPathname(char* str, unsigned int size)
    {
        GetModuleFileName(NULL, str, size);
    }

#else // Linux

    #include <stdlib.h>
    #include <string.h>
    void getFaustPathname(char* str, unsigned int size)
    {
		char* path = getenv("_");
		if (path) {
        	strncpy(str, path, size);
		} else {
			// prevent the case of _ undefined
			strncpy(str, "/usr/local/bin/faust", size);
		} 
    }

#endif


