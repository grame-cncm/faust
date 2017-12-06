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

#ifndef __COMPATIBILITY__
#define __COMPATIBILITY__

unsigned faust_alarm(unsigned seconds);

#if defined(__MINGW32__) || (defined(_MSC_VER) && _MSC_VER >= 1900)
#define faust_mkdir(path, attribute) mkdir(path)
#elif !defined(WIN32)
#define faust_mkdir(path, attribute) mkdir(path, attribute)
#endif

#if defined(_WIN32)
#include <windows.h>
#include <time.h>
#include <assert.h>

#ifdef __MINGW32__
// mingw has PATH_MAX defined in limits.h. Make sure that it's included.
#include <limits.h>
#else
#define PATH_MAX 512
#endif
#define YY_NO_UNISTD_H 1

#define GCC_VERSION (__GNUC__ * 10000                 \
                     + __GNUC_MINOR__ * 100           \
                     + __GNUC_PATCHLEVEL__)

#if GCC_VERSION < 40700
struct timezone
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};
#endif

#define alarm(x) 0

#if !defined(__MINGW32__) && (_MSC_VER < 1900)
// mingw & VS2015 have these in its headers.
#define strdup _strdup
#define snprintf _snprintf
#endif

extern "C" {
#if (_MSC_VER<=1700)
    double  rint(double nr);
#endif

    int gettimeofday(struct timeval *tv, struct timezone *tz);
    int chdir(const char* path);
    #if _MSC_VER
      #undef small
      int mkdir(const char* path);
    #endif
    char* getcwd(char* str, int size);
#ifndef WIN32
	int isatty(int file);
#endif
}

void getFaustPathname(char* str, unsigned int size);
void getFaustPathname(char* str, unsigned int size);
char* realpath(const char* path, char resolved_path[PATH_MAX]);
char* basename(const char* fullpath);

#ifdef NDEBUG
#undef assert
#define assert(_Expression) do { bool bTest = (_Expression) != 0; } while (0)
#endif

//#define rintf(x) floor((x)+(((x) < 0 ) ? -0.5f :0.5f))
#define FAUST_PATH_MAX 1024

#if !defined(__MINGW32__)
#if (_MSC_VER<=1700)
	double	remainder(double numerator, double denominator);
	double rint(double nr);
#endif
	/* missing on Windows : see http://bugs.mysql.com/bug.php?id=15936 */
	#define S_IRWXU 0
#endif

#if !defined(__MINGW32__) || GCC_VERSION < 40903
#define S_IRWXG 0
#define S_IROTH 0
#define S_IXOTH 0
#define DIRSEP '\\'
#endif

#undef min
#undef max

#else

#include <unistd.h>
#include <libgen.h>

#define DIRSEP '/'
#define FAUST_PATH_MAX 1024

void getFaustPathname(char* str, unsigned int size);

#endif // _WIN32
#endif
