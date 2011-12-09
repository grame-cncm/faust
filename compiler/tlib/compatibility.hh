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


#if defined (WIN32)

#include <windows.h>

#ifdef WIN32
	#undef min
	#undef max
#endif

bool	chdir(const char* path);
int		mkdir(const char* path, unsigned int attribute);
char*	getcwd(char* str, unsigned int size);
int		isatty(int file);
void	getFaustPathname(char* str, unsigned int size);
void	getFaustPathname(char* str, unsigned int size);

#include <assert.h>
#ifdef  NDEBUG
#undef assert
#define assert(_Expression) do { bool bTest = (_Expression) != 0; } while (0)
#endif

#define snprintf _snprintf
//#define rintf(x) floor((x)+(((x) < 0 ) ? -0.5f :0.5f))
#define FAUST_PATH_MAX 1024

#if !defined(__MINGW32__)
	double	remainder(double numerator, double denominator);
	#define S_IRWXU 0
#endif

#define S_IRWXG 0
#define S_IROTH 0
#define S_IXOTH 0
#define DIRSEP '\\'

#else

#include <unistd.h>
#define DIRSEP '/'
#define FAUST_PATH_MAX 1024

void getFaustPathname(char* str, unsigned int size);

#endif

#endif
