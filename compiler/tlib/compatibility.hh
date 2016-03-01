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
 
#define LLVM_BUILD (LLVM_31 || LLVM_32 || LLVM_33 || LLVM_34 || LLVM_35 || LLVM_36 || LLVM_37)

unsigned faust_alarm(unsigned seconds);

#ifdef _WIN32
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

struct timezone 
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};

#define alarm(x) 0
#ifndef __MINGW32__
// mingw has these in its headers.
#define strdup _strdup
#define snprintf _snprintf
#endif
extern "C" {
#if (_MSC_VER<=1700)
    double  rint(double nr);
#endif
int gettimeofday(struct timeval *tv, struct timezone *tz);
int chdir(const char* path);
int mkdir(const char* path, unsigned int attribute);
char* getcwd(char* str, int size);
int isatty(int file);
}
void getFaustPathname(char* str, unsigned int size);
void getFaustPathname(char* str, unsigned int size);
char* realpath(const char* path, char resolved_path[PATH_MAX]);
char* basename(const char* fullpath);

#ifdef  NDEBUG
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

#define S_IRWXG 0
#define S_IROTH 0
#define S_IXOTH 0
#define DIRSEP '\\'

#undef min
#undef max

#else

#include <unistd.h>
#define DIRSEP '/'
#define FAUST_PATH_MAX 1024

void getFaustPathname(char* str, unsigned int size);

#endif

#endif
