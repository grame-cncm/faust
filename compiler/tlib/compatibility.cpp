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
 
#include "compatibility.hh"
#include "math.h"

#if defined(__MINGW32__) || defined (_WIN32)
	// Simulate some Unix fonctions on Windows

#if !defined(INT) & !defined(FLOAT)
#include <windows.h>
#else
#include <io.h>
#endif

	#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
	  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
	#else
	  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
	#endif

	int gettimeofday(struct timeval *tv, struct timezone *tz)
	{
	  FILETIME ft;
	  unsigned __int64 tmpres = 0;
	  static int tzflag;

	  if (NULL != tv)
	  {
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS; 
		tmpres /= 10;  /*convert into microseconds*/
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	  }

	  if (NULL != tz)
	  {
		if (!tzflag)
		{
		  _tzset();
		  tzflag++;
		}
		tz->tz_minuteswest = _timezone / 60;
		tz->tz_dsttime = _daylight;
	  }
	  return 0;
	}
	int		isatty(int file){ return 0; }

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


