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
 

#if defined( __MINGW32__) || defined (WIN32)
	// Simulate some Unix fonctions on Windows

	#include <windows.h>
	#include "math.h"

#if defined(_MBCS) || __MINGW32__
	bool chdir(const char* path)
	{
		return !SetCurrentDirectory(path);
	}

	int mkdir(const char* path, unsigned int attribute)
	{
		return CreateDirectory(path,NULL);
	}

	char* getcwd(char* str, unsigned int size)
	{
		GetCurrentDirectory(size, str);
		return str;
	}
	void getFaustPathname(char* str, unsigned int size)
	{
		GetModuleFileName(NULL, str, size);
	}
#else
	bool chdir(const char* path)
	{
		wchar_t	wstr[2048];
		mbstowcs(wstr,path,2048);
		return !SetCurrentDirectory(wstr);
	}

	int mkdir(const char* path, unsigned int attribute)
	{
		wchar_t	wstr[2048];
		mbstowcs(wstr,path,2048);
		return CreateDirectory(wstr,NULL);
	}

	char* getcwd(char* str, unsigned int size)
	{
		wchar_t	wstr[2048];
		GetCurrentDirectory(2048, wstr);
		wcstombs(str,wstr,size);
		return str;
	}

	void getFaustPathname(char* str, unsigned int size)
	{
		wchar_t	wstr[2048];
		GetModuleFileName(NULL, wstr, 2048);
		wcstombs(str,wstr,size);
	}

#endif

	int isatty(int file)
	{
		return 0;
	}

#if !defined(__MINGW32__)

	typedef union
	{
		double value;
		struct
		{
			unsigned int lsw;
			unsigned int msw;
		} parts;
	} ieee_double_shape_type;


#define EXTRACT_WORDS(ix0,ix1,d)				\
	do {								\
	ieee_double_shape_type ew_u;					\
	ew_u.value = (d);						\
	(ix0) = ew_u.parts.msw;					\
	(ix1) = ew_u.parts.lsw;					\
	} while (0)

	/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)					\
	do {								\
	ieee_double_shape_type gh_u;					\
	gh_u.value = (d);						\
	(i) = gh_u.parts.msw;						\
	} while (0)

	/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)					\
	do {								\
	ieee_double_shape_type gl_u;					\
	gl_u.value = (d);						\
	(i) = gl_u.parts.lsw;						\
	} while (0)

#define SET_HIGH_WORD(d,v)					\
	do {								\
	ieee_double_shape_type sh_u;					\
	sh_u.value = (d);						\
	sh_u.parts.msw = (v);						\
	(d) = sh_u.value;						\
	} while (0)

	double remainder(double x, double p)
	{
		int hx,hp;
		unsigned int sx,lx,lp;
		double p_half;

		EXTRACT_WORDS(hx,lx,x);
		EXTRACT_WORDS(hp,lp,p);
		sx = hx&0x80000000;
		hp &= 0x7fffffff;
		hx &= 0x7fffffff;

		/* purge off exception values */
		if((hp|lp)==0) return (x*p)/(x*p); 	/* p = 0 */
		if((hx>=0x7ff00000)||			/* x not finite */
			((hp>=0x7ff00000)&&			/* p is NaN */
			(((hp-0x7ff00000)|lp)!=0)))
			return (x*p)/(x*p);


		static const double zero = 0.0;
		if (hp<=0x7fdfffff) x = fmod(x,p+p);	/* now x < 2p */
		if (((hx-hp)|(lx-lp))==0) return zero*x;
		x  = fabs(x);
		p  = fabs(p);
		if (hp<0x00200000) {
			if(x+x>p) {
				x-=p;
				if(x+x>=p) x -= p;
			}
		} else {
			p_half = 0.5*p;
			if(x>p_half) {
				x-=p;
				if(x>=p_half) x -= p;
			}
		}
		GET_HIGH_WORD(hx,x);
		SET_HIGH_WORD(x,hx^sx);
		return x;
	}
#endif

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


