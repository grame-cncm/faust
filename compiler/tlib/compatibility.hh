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
 

#ifndef     __COMPATIBILITY__
#define     __COMPATIBILITY__

void getFaustPathname(char* str, unsigned int size);

#if defined( __MINGW32__)

#include <windows.h>
#define snprintf _snprintf
//#define rintf(x) floor((x)+(((x) < 0 ) ? -0.5f :0.5f))
//#define FAUST_PATH_MAX 1024
#define getcwd(buffer,len) GetCurrentDirectory(len,buffer)
#define chdir(path) (!SetCurrentDirectory(path))
#define mkdir(path,attribute) CreateDirectory(path,NULL)
//#define S_IRWXU 0
#define S_IRWXG 0
#define S_IROTH 0
#define S_IXOTH 0
#define DIRSEP '\\'

#elif defined (WIN32)

#include <windows.h>
#define snprintf _snprintf
#define rintf(x) floor((x)+(((x) < 0 ) ? -0.5f :0.5f))
#define FAUST_PATH_MAX 1024
#define getcwd(buffer,len) GetCurrentDirectory(len,buffer)
#define chdir(path) (!SetCurrentDirectory(path))
#define mkdir(path,attribute) CreateDirectory(path,NULL)
#define S_IRWXU 0
#define S_IRWXG 0
#define S_IROTH 0
#define S_IXOTH 0
#define DIRSEP '\\'

#else

#include <unistd.h>
#define DIRSEP '/'
#define FAUST_PATH_MAX 1024

#endif

#endif
