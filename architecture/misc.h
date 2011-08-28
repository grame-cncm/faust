
#ifndef __misc__
#define __misc__

#include <map>
#include <string.h>

// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};

struct Meta
{
    virtual void declare (const char* key, const char* value) = 0;
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

inline int		lsr (int x, int n)		{ return int(((unsigned int)x) >> n); }
inline int 		int2pow2 (int x)		{ int r=0; while ((1<<r)<x) r++; return r; }

long lopt(char *argv[], const char *name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

char* lopts(char *argv[], const char *name, char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}
#endif

