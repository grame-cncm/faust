//#include "../bench/lmbench.h"






/* link with  */
/* link with : "" */
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <pthread.h> 
#include <sys/wait.h>
#include <list>




inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }



// g++ -Wall -O3 -lm -lpthread -lasound `gtk-config --cflags --libs` test.cpp -o test

// Generic min and max (didn't found any better way using templates)
// assuming int < long < float < double
//-------------------------------------------------------------------

inline int 		max (int a, int b) 			{ return (a>b) ? a : b; }

inline long 	max (long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (int a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (long a, int b) 		{ return (a>b) ? a : b; }

inline float 	max (float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max (long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max (double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max (long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max (float a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (double a, float b) 	{ return (a>b) ? a : b; }


inline int 		min (int a, int b) 			{ return (a<b) ? a : b; }

inline long 	min (long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (int a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (long a, int b) 		{ return (a<b) ? a : b; }

inline float 	min (float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min (long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min (double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min (long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min (float a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (double a, float b) 	{ return (a<b) ? a : b; }
		
template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }




bool setRealtimePriority ()
{
    struct passwd *         pw;
    int                     err;
    uid_t                   uid;
    struct sched_param      param;

    uid = getuid ();
    pw = getpwnam ("root");
    setuid (pw->pw_uid);
    param.sched_priority = 50; /* 0 to 99  */
    err = sched_setscheduler(0, SCHED_RR, &param);
    setuid (uid);
    return (err != -1);
}


/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/



<<includeIntrinsic>>



/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
	bool	fStopped;
public:
		
	UI() : fStopped(false) {}
	virtual ~UI() {}
	
	virtual void addButton(char* label, float* zone) = 0;
	virtual void addToggleButton(char* label, float* zone) = 0;
	virtual void addCheckButton(char* label, float* zone) = 0;
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;
	
	virtual void openFrameBox(char* label) = 0;
	virtual void openTabBox(char* label) = 0;
	virtual void openHorizontalBox(char* label) = 0;
	virtual void openVerticalBox(char* label) = 0;
	virtual void closeBox() = 0;
	
	virtual void run() = 0;
	
	void stop()	{ fStopped = true; }
	bool stopped() 	{ return fStopped; }
};




/******************************************************************************
*******************************************************************************

								DSP

*******************************************************************************
*******************************************************************************/



//----------------------------------------------------------------
//  dÂŽéfinition du processeur de signal
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		
		
<<includeclass>>

mydsp	DSP;



/******************************************************************************
*******************************************************************************

								Bench utility

*******************************************************************************
*******************************************************************************/


/*
 * a timing utilities library
 *
 * Requires 64bit integers to work.
 *
 * %W% %@%
 *
 * Copyright (c) 2000 Carl Staelin.
 * Copyright (c) 1994-1998 Larry McVoy.
 * Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
#define	 _LIB /* bench.h needs this */

//#include "bench.h"
/*
 * $Id: bench.cpp,v 1.1 2004/04/27 15:20:08 orlarey Exp $
 */
#ifndef _BENCH_H
#define _BENCH_H

#ifdef WIN32
#include <windows.h>
typedef unsigned char bool_t;
#endif

#include	<assert.h>
#include        <ctype.h>
#include        <stdio.h>
#ifndef WIN32
#include        <unistd.h>
#endif
#include        <stdlib.h>
#include        <fcntl.h>
#include        <signal.h>
#include        <errno.h>
#ifndef WIN32
#include        <strings.h>
#endif
#include        <sys/types.h>
#ifndef WIN32
#include        <sys/mman.h>
#endif
#include        <sys/stat.h>
#ifndef WIN32
#include        <sys/wait.h>
#include	<time.h>
#include        <sys/time.h>
#include        <sys/socket.h>
#include        <sys/un.h>
#include        <sys/resource.h>
#define PORTMAP
#include	<rpc/rpc.h>
#endif
#include	<rpc/types.h>

#ifndef HAVE_uint
typedef unsigned int uint;
#endif

#ifndef HAVE_uint64
#ifdef HAVE_uint64_t
typedef uint64_t uint64;
#else /* HAVE_uint64_t */
typedef unsigned long long uint64;
#endif /* HAVE_uint64_t */
#endif /* HAVE_uint64 */

#ifndef HAVE_int64
#ifdef HAVE_int64_t
typedef int64_t int64;
#else /* HAVE_int64_t */
typedef long long int64;
#endif /* HAVE_int64_t */
#endif /* HAVE_int64 */

#define NO_PORTMAPPER

//#include	"stats.h"
//#include	"timing.h"
/*
 * $Id: bench.cpp,v 1.1 2004/04/27 15:20:08 orlarey Exp $
 */
#ifndef _TIMING_H
#define _TIMING_H

char	*p64(uint64 big);
char	*p64sz(uint64 big);
double	Delta(void);
double	Now(void);
void	adjust(int usec);
void	bandwidth(uint64 bytes, uint64 times, int verbose);
uint64	bytes(char *s);
void	context(uint64 xfers);
uint64	delta(void);
int	get_enough(int);
uint64	get_n(void);
void	kb(uint64 bytes);
double	l_overhead(void);
char	last(char *s);
void	latency(uint64 xfers, uint64 size);
void	mb(uint64 bytes);
void	micro(char *s, uint64 n);
void	micromb(uint64 mb, uint64 n);
void	milli(char *s, uint64 n);
void	morefds(void);
void	nano(char *s, uint64 n);
uint64	now(void);
void	ptime(uint64 n);
void	rusage(void);
void	save_n(uint64);
void	settime(uint64 usecs);
void	start(struct timeval *tv);
uint64	stop(struct timeval *begin, struct timeval *end);
uint64	t_overhead(void);
double	timespent(void);
void	timing(FILE *out);
uint64	tvdelta(struct timeval *, struct timeval *);
void	tvsub(struct timeval *tdiff, struct timeval *t1, struct timeval *t0);
void	use_int(int result);
void	use_pointer(void *result);
uint64	usecs_spent(void);
void	touch(char *buf, int size);
int*	permutation(int max, int scale);
int	cp(char* src, char* dst, mode_t mode);
long	bread(void* src, long count);

#if defined(hpux) || defined(__hpux)
int	getpagesize();
#endif

#endif /* _TIMING_H */

#ifndef _STATS_H
#define _STATS_H

//#include "bench.h"
//#include "timing.h"

//#define ABS(x)	((x) < 0 ? -(x) : (x))

int	int_compare(const void *a, const void *b);
int	uint64_compare(const void *a, const void *b);
int	double_compare(const void *a, const void *b);

typedef	int (*int_stat)(int *values, int size);
typedef	uint64 (*uint64_stat)(uint64 *values, int size);
typedef	double (*double_stat)(double *values, int size);

int	int_median(int *values, int size);
uint64	uint64_median(uint64 *values, int size);
double	double_median(double *values, int size);

int	int_mean(int *values, int size);
uint64	uint64_mean(uint64 *values, int size);
double	double_mean(double *values, int size);

int	int_min(int *values, int size);
uint64	uint64_min(uint64 *values, int size);
double	double_min(double *values, int size);

int	int_max(int *values, int size);
uint64	uint64_max(uint64 *values, int size);
double	double_max(double *values, int size);

double	int_variance(int *values, int size);
double	uint64_variance(uint64 *values, int size);
double	double_variance(double *values, int size);

double	int_moment(int moment, int *values, int size);
double	uint64_moment(int moment, uint64 *values, int size);
double	double_moment(int moment, double *values, int size);

double	int_stderr(int *values, int size);
double	uint64_stderr(uint64 *values, int size);
double	double_stderr(double *values, int size);

double	int_skew(int *values, int size);
double	uint64_skew(uint64 *values, int size);
double	double_skew(double *values, int size);

double	int_kurtosis(int *values, int size);
double	uint64_kurtosis(uint64 *values, int size);
double	double_kurtosis(double *values, int size);

double	int_bootstrap_stderr(int *values, int size, int_stat f);
double	uint64_bootstrap_stderr(uint64 *values, int size, uint64_stat f);
double	double_bootstrap_stderr(double *values, int size, double_stat f);

void	regression(double *x, double *y, double *sig, int n,
		   double *a, double *b, double *sig_a, double *sig_b, 
		   double *chi2);

#endif /* _STATS_H */


//#include	"lib_debug.h"
//#include	"lib_tcp.h"
//#include	"lib_udp.h"
//#include	"lib_unix.h"


#ifdef	DEBUG
#	define		debug(x) fprintf x
#else
#	define		debug(x)
#endif
#ifdef	NO_PORTMAPPER
#define	TCP_SELECT	-31233
#define	TCP_XACT	-31234
#define	TCP_CONTROL	-31235
#define	TCP_DATA	-31236
#define	TCP_CONNECT	-31237
#define UDP_XACT	-31238
#define UDP_DATA	-31239
#else
#define	TCP_SELECT	(u_long)404038	/* XXX - unregistered */
#define	TCP_XACT	(u_long)404039	/* XXX - unregistered */
#define	TCP_CONTROL	(u_long)404040	/* XXX - unregistered */
#define	TCP_DATA	(u_long)404041	/* XXX - unregistered */
#define	TCP_CONNECT	(u_long)404042	/* XXX - unregistered */
#define	UDP_XACT 	(u_long)404032	/* XXX - unregistered */
#define	UDP_DATA 	(u_long)404033	/* XXX - unregistered */
#define	VERS		(u_long)1
#endif

#define	UNIX_CONTROL	"/tmp/lmbench.ctl"
#define	UNIX_DATA	"/tmp/lmbench.data"
#define	UNIX_LAT	"/tmp/lmbench.lat"

/*
 * socket send/recv buffer optimizations
 */
#define	SOCKOPT_READ	0x0001
#define	SOCKOPT_WRITE	0x0002
#define	SOCKOPT_RDWR	0x0003
#define	SOCKOPT_PID	0x0004
#define	SOCKOPT_REUSE	0x0008
#define	SOCKOPT_NONE	0

#ifndef SOCKBUF
#define	SOCKBUF		(1024*1024)
#endif

#ifndef	XFERSIZE
#define	XFERSIZE	(64*1024)	/* all bandwidth I/O should use this */
#endif

#if defined(SYS5) || defined(WIN32)
#define	bzero(b, len)	memset(b, 0, len)
#define	bcopy(s, d, l)	memcpy(d, s, l)
#define	rindex(s, c)	strrchr(s, c)
#endif
#define	gettime		usecs_spent
#define	streq		!strcmp
#define	ulong		unsigned long

#ifndef HAVE_DRAND48
#ifdef HAVE_RAND
#define srand48		srand
#define drand48()	((double)rand() / (double)RAND_MAX)
#elif defined(USE_RANDOM)
#define srand48		srandom
#define drand48()	((double)random() / (double)RAND_MAX)
#endif /* HAVE_RAND */
#endif /* HAVE_DRAND48 */

#ifdef WIN32
#include <process.h>
#define getpid _getpid
int	gettimeofday(struct timeval *tv, struct timezone *tz);
#endif

#define	SMALLEST_LINE	32		/* smallest cache line size */
#define	TIME_OPEN2CLOSE

#define	GO_AWAY	signal(SIGALRM, exit); alarm(60 * 60);
#define	REAL_SHORT	   50000
#define	SHORT	 	 1000000
#define	MEDIUM	 	 2000000
#define	LONGER		 7500000	/* for networking data transfers */
#define	ENOUGH		REAL_SHORT

#define	TRIES		11

typedef struct {
	uint64 u;
	uint64 n;
} value_t;

typedef struct {
	int	N;
	value_t	v[TRIES];
} result_t;
int	sizeof_result(int N);
void    insertinit(result_t *r);
void    insertsort(uint64, uint64, result_t *);
void	save_median();
void	save_minimum();
void	set_results(result_t *r);
result_t* get_results();


#define	BENCHO(loop_body, overhead_body, enough) { 			\
	int 		__i, __N;					\
	double 		__oh;						\
	result_t 	__overhead, __r;				\
	insertinit(&__overhead); insertinit(&__r);			\
	__N = (enough == 0 || get_enough(enough) <= 100000) ? TRIES : 1;\
	if (enough < LONGER) {loop_body;} /* warm the cache */		\
	for (__i = 0; __i < __N; ++__i) {				\
		BENCH1(overhead_body, enough);				\
		if (gettime() > 0)					\
			insertsort(gettime(), get_n(), &__overhead);	\
		BENCH1(loop_body, enough);				\
		if (gettime() > 0)					\
			insertsort(gettime(), get_n(), &__r);		\
	}								\
	for (__i = 0; __i < __r.N; ++__i) {				\
		__oh = __overhead.v[__i].u / (double)__overhead.v[__i].n; \
		if (__r.v[__i].u > (uint64)((double)__r.v[__i].n * __oh)) \
			__r.v[__i].u -= (uint64)((double)__r.v[__i].n * __oh);	\
		else							\
			__r.v[__i].u = 0;				\
	}								\
	*(get_results()) = __r;						\
}

#define	BENCH(loop_body, enough) { 					\
	long		__i, __N;					\
	result_t 	__r;						\
	insertinit(&__r);						\
	__N = (enough == 0 || get_enough(enough) <= 100000) ? TRIES : 1;\
	if (enough < LONGER) {loop_body;} /* warm the cache */		\
	for (__i = 0; __i < __N; ++__i) {				\
		BENCH1(loop_body, enough);				\
		if (gettime() > 0)					\
			insertsort(gettime(), get_n(), &__r);		\
	}								\
	*(get_results()) = __r;						\
}

#define	BENCH1(loop_body, enough) { 					\
	double		__usecs;					\
	BENCH_INNER(loop_body, enough);  				\
	__usecs = gettime();						\
	__usecs -= t_overhead() + get_n() * l_overhead();		\
	settime(__usecs >= 0. ? (uint64)__usecs : 0);			\
}
	
#define	BENCH_INNER(loop_body, enough) { 				\
	static iter_t	__iterations = 1;				\
	int		__enough = get_enough(enough);			\
	iter_t		__n;						\
	double		__result = 0.;					\
									\
	while(__result < 0.95 * __enough) {				\
		start(0);						\
		for (__n = __iterations; __n > 0; __n--) {		\
			loop_body;					\
		}							\
		__result = stop(0,0);					\
		if (__result < 0.99 * __enough 				\
		    || __result > 1.2 * __enough) {			\
			if (__result > 150.) {				\
				double	tmp = __iterations / __result;	\
				tmp *= 1.1 * __enough;			\
				__iterations = (iter_t)(tmp + 1);	\
			} else {					\
				if (__iterations > (iter_t)1<<27) {	\
					__result = 0.;			\
					break;				\
				}					\
				__iterations <<= 3;			\
			}						\
		}							\
	} /* while */							\
	save_n((uint64)__iterations); settime((uint64)__result);	\
}

/* getopt stuff */
#define getopt	mygetopt
#define optind	myoptind
#define optarg	myoptarg
#define	opterr	myopterr
#define	optopt	myoptopt
extern	int	optind;
extern	int	opterr;
extern	int	optopt;
extern	char	*optarg;
int	getopt(int ac, char **av, char *opts);

typedef u_long iter_t;
typedef void (*bench_f)(iter_t iterations, void* cookie);
typedef void (*support_f)(void* cookie);

extern void benchmp(support_f initialize, 
		    bench_f benchmark,
		    support_f cleanup,
		    int enough, 
		    int parallel,
		    int warmup,
		    int repetitions,
		    void* cookie
	);

/* 
 * These are used by weird benchmarks which cannot return, such as page
 * protection fault handling.  See lat_sig.c for sample usage.
 */
extern void* benchmp_getstate();
extern iter_t benchmp_interval(void* _state);

/*
 * Which child process is this?
 * Returns a number in the range [0, ..., N-1], where N is the
 * total number of children (parallelism)
 */
extern int benchmp_childid();

//#include	"lib_mem.h"
#ifndef LMBENCH_MEM_H
#define LMBENCH_MEM_H


#define MAX_MEM_PARALLELISM 16
#define MEM_BENCHMARK_DECL(N) \
	void mem_benchmark_##N(iter_t iterations, void* cookie);

#define REPEAT_0(m)	m(0)
#define REPEAT_1(m)	REPEAT_0(m) m(1)
#define REPEAT_2(m)	REPEAT_1(m) m(2)
#define REPEAT_3(m)	REPEAT_2(m) m(3)
#define REPEAT_4(m)	REPEAT_3(m) m(4)
#define REPEAT_5(m)	REPEAT_4(m) m(5)
#define REPEAT_6(m)	REPEAT_5(m) m(6)
#define REPEAT_7(m)	REPEAT_6(m) m(7)
#define REPEAT_8(m)	REPEAT_7(m) m(8)
#define REPEAT_9(m)	REPEAT_8(m) m(9)
#define REPEAT_10(m)	REPEAT_9(m) m(10)
#define REPEAT_11(m)	REPEAT_10(m) m(11)
#define REPEAT_12(m)	REPEAT_11(m) m(12)
#define REPEAT_13(m)	REPEAT_12(m) m(13)
#define REPEAT_14(m)	REPEAT_13(m) m(14)
#define REPEAT_15(m)	REPEAT_14(m) m(15)

struct mem_state {
	char*	addr;	/* raw pointer returned by malloc */
	char*	base;	/* page-aligned pointer */
	char*	p[MAX_MEM_PARALLELISM];
	int	initialized;
	int	width;
	size_t	len;
	size_t	maxlen;
	size_t	line;
	size_t	pagesize;
	size_t	nlines;
	size_t	npages;
	size_t	nwords;
	size_t*	pages;
	size_t*	lines;
	size_t*	words;
};

void mem_initialize(void* cookie);
void line_initialize(void* cookie);
void tlb_initialize(void* cookie);
void mem_cleanup(void* cookie);
void tlb_cleanup(void* cookie);

REPEAT_15(MEM_BENCHMARK_DECL)
extern bench_f mem_benchmarks[];

size_t	line_find(size_t l, int warmup, int repetitions, struct mem_state* state);
double	line_test(size_t l, int warmup, int repetitions, struct mem_state* state);
double	par_mem(size_t l, int warmup, int repetitions, struct mem_state* state);

#endif /* LMBENCH_MEM_H */


/*
 * Generated from msg.x which is included here:

	program XACT_PROG {
	    version XACT_VERS {
		char
		RPC_XACT(char) = 1;
    	} = 1;
	} = 3970;

 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#define XACT_PROG ((u_long)404040)
#define XACT_VERS ((u_long)1)
#define RPC_XACT ((u_long)1)
#define RPC_EXIT ((u_long)2)
extern char *rpc_xact_1();
extern char *client_rpc_xact_1();

#endif /* _BENCH_H */




/* #define _DEBUG */

#define	nz(x)	((x) == 0 ? 1 : (x))

/*
 * I know you think these should be 2^10 and 2^20, but people are quoting
 * disk sizes in powers of 10, and bandwidths are all power of ten.
 * Deal with it.
 */
#define	MB	(1000*1000.0)
#define	KB	(1000.0)

static struct timeval 	start_tv, stop_tv;
FILE			*ftiming;
static volatile uint64	use_result_dummy;
static		uint64	iterations;
static		void	init_timing(void);

#if defined(hpux) || defined(__hpux)
#include <sys/mman.h>
#endif

#ifdef	RUSAGE
#include <sys/resource.h>
#define	SECS(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
#define	mine(f)		(int)(ru_stop.f - ru_start.f)

static struct rusage ru_start, ru_stop;

void
rusage(void)
{
	double  sys, user, idle;
	double  per;

	sys = SECS(ru_stop.ru_stime) - SECS(ru_start.ru_stime);
	user = SECS(ru_stop.ru_utime) - SECS(ru_start.ru_utime);
	idle = timespent() - (sys + user);
	per = idle / timespent() * 100;
	if (!ftiming) ftiming = stderr;
	fprintf(ftiming, "real=%.2f sys=%.2f user=%.2f idle=%.2f stall=%.0f%% ",
	    timespent(), sys, user, idle, per);
	fprintf(ftiming, "rd=%d wr=%d min=%d maj=%d ctx=%d\n",
	    mine(ru_inblock), mine(ru_oublock),
	    mine(ru_minflt), mine(ru_majflt),
	    mine(ru_nvcsw) + mine(ru_nivcsw));
}

#endif	/* RUSAGE */

void
lmbench_usage(int argc, char *argv[], char* usage)
{
	fprintf(stderr,"Usage: %s %s", argv[0], usage);
	exit(-1);
}

static int	benchmp_sigterm_received;
static int	benchmp_sigchld_received;
static pid_t	benchmp_sigalrm_pid;
static int	benchmp_sigalrm_timeout;
void (*benchmp_sigterm_handler)(int);
void (*benchmp_sigchld_handler)(int);
void (*benchmp_sigalrm_handler)(int);

void
benchmp_sigterm(int signo)
{
	benchmp_sigterm_received = 1;
}

void
benchmp_sigchld(int signo)
{
	signal(SIGCHLD, SIG_IGN);
	benchmp_sigchld_received = 1;
#ifdef _DEBUG
	fprintf(stderr, "benchmp_sigchld handler\n");
#endif
}

void
benchmp_sigalrm(int signo)
{
	signal(SIGALRM, SIG_IGN);
	kill(benchmp_sigalrm_pid, SIGTERM);
	/* 
	 * Since we already waited a full timeout period for the child
	 * to die, we only need to wait a little longer for subsequent
	 * children to die.
	 */
	benchmp_sigalrm_timeout = 1;
}

void 
benchmp_child(support_f initialize, 
	      bench_f benchmark,
	      support_f cleanup,
	      int childid,
	      int response, 
	      int start_signal, 
	      int result_signal, 
	      int exit_signal,
	      int parallel, 
	      iter_t iterations,
	      int repetitions,
	      int enough,
	      void* cookie
	      );
void
benchmp_parent(int response, 
	       int start_signal, 
	       int result_signal, 
	       int exit_signal, 
	       pid_t* pids,
	       int parallel, 
	       iter_t iterations,
	       int warmup,
	       int repetitions,
	       int enough
	       );

int
sizeof_result(int repetitions);

void 
benchmp(support_f initialize, 
	bench_f benchmark,
	support_f cleanup,
	int enough, 
	int parallel,
	int warmup,
	int repetitions,
	void* cookie)
{
	iter_t		iterations = 1;
	double		result = 0.;
	double		usecs;
	long		i, j;
	pid_t		pid;
	pid_t		*pids = NULL;
	int		response[2];
	int		start_signal[2];
	int		result_signal[2];
	int		exit_signal[2];
	int		need_warmup;
	fd_set		fds;
	struct timeval	timeout;

#ifdef _DEBUG
	fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): entering\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie);
#endif
	enough = get_enough(enough);

	/* initialize results */
	settime(0);
	save_n(1);

	if (parallel > 1) {
		/* Compute the baseline performance */
		benchmp(initialize, benchmark, cleanup, 
			enough, 1, warmup, repetitions, cookie);

		/* if we can't even do a single job, then give up */
		if (gettime() == 0)
			return;

		/* calculate iterations for 1sec runtime */
		iterations = get_n();
		if (enough < SHORT) {
			double tmp = (double)SHORT * (double)get_n();
			tmp /= (double)gettime();
			iterations = (iter_t)tmp + 1;
		}
		settime(0);
		save_n(1);
	}

	/* Create the necessary pipes for control */
	if (pipe(response) < 0
	    || pipe(start_signal) < 0
	    || pipe(result_signal) < 0
	    || pipe(exit_signal) < 0) {
#ifdef _DEBUG
		fprintf(stderr, "BENCHMP: Could not create control pipes\n");
#endif /* _DEBUG */
		return;
	}

	/* fork the necessary children */
	benchmp_sigchld_received = 0;
	benchmp_sigterm_received = 0;
	benchmp_sigterm_handler = signal(SIGTERM, benchmp_sigterm);
	benchmp_sigterm_handler = signal(SIGCHLD, benchmp_sigchld);
	pids = (pid_t*)malloc(parallel * sizeof(pid_t));
	if (!pids) return;
	bzero((void*)pids, parallel * sizeof(pid_t));

	for (i = 0; i < parallel; ++i) {
		if (benchmp_sigterm_received)
			goto error_exit;
#ifdef _DEBUG
		fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): creating child %d\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie, i);
#endif
		switch(pids[i] = fork()) {
		case -1:
			/* could not open enough children! */
#ifdef _DEBUG
			fprintf(stderr, "BENCHMP: fork() failed!\n");
#endif /* _DEBUG */
			goto error_exit;
		case 0:
			/* If child */
			close(response[0]);
			close(start_signal[1]);
			close(result_signal[1]);
			close(exit_signal[1]);
			benchmp_child(initialize, 
				      benchmark, 
				      cleanup, 
				      i,
				      response[1], 
				      start_signal[0], 
				      result_signal[0], 
				      exit_signal[0],
				      enough,
				      iterations,
				      parallel,
				      repetitions,
				      cookie
				);
			exit(0);
		default:
			break;
		}
	}
	close(response[1]);
	close(start_signal[0]);
	close(result_signal[0]);
	close(exit_signal[0]);
	benchmp_parent(response[0], 
		       start_signal[1], 
		       result_signal[1], 
		       exit_signal[1],
		       pids,
		       parallel, 
		       iterations,
		       warmup,
		       repetitions,
		       enough
		);
	goto cleanup_exit;

error_exit:
	/* give the children a chance to clean up gracefully */
	signal(SIGCHLD, SIG_IGN);
	while (--i >= 0) {
		kill(pids[i], SIGTERM);
	}

cleanup_exit:
	/* 
	 * Clean up and kill all children
	 *
	 * NOTE: the children themselves SHOULD exit, and
	 *   Killing them could prevent them from
	 *   cleanup up subprocesses, etc... So, we only
	 *   want to kill child processes when it appears
	 *   that they will not die of their own accord.
	 *   We wait twice the timing interval plus two seconds
	 *   for children to die.  If they haven't died by 
	 *   that time, then we start killing them.
	 */
	benchmp_sigalrm_timeout = (int)((2 * enough)/1000000) + 2;
	if (benchmp_sigalrm_timeout < 5)
		benchmp_sigalrm_timeout = 5;
	signal(SIGCHLD, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	while (i-- > 0) {
		/* wait timeout seconds for child to die, then kill it */
		benchmp_sigalrm_pid = pids[i];
		signal(SIGALRM, benchmp_sigalrm);
		alarm(benchmp_sigalrm_timeout); 

		waitpid(pids[i], NULL, 0);

		alarm(0);
		signal(SIGALRM, SIG_IGN);
	}

	if (pids) free(pids);
#ifdef _DEBUG
	fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): exiting\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie);
#endif
}

void
benchmp_parent(	int response, 
		int start_signal, 
		int result_signal, 
		int exit_signal,
		pid_t* pids,
		int parallel, 
	        iter_t iterations,
		int warmup,
		int repetitions,
		int enough
		)
{
	int		i,j,k,l;
	int		bytes_read;
	result_t*	results = NULL;
	result_t*	merged_results = NULL;
	char*		signals = NULL;
	unsigned char*	buf;
	fd_set		fds_read, fds_error;
	struct timeval	timeout;

	if (benchmp_sigchld_received || benchmp_sigterm_received) {
#ifdef _DEBUG
		fprintf(stderr, "benchmp_parent: entering, benchmp_sigchld_received=%d\n", benchmp_sigchld_received);
#endif
		goto error_exit;
	}

	results = (result_t*)malloc(sizeof_result(repetitions));
	merged_results = (result_t*)malloc(sizeof_result(parallel * repetitions));
	signals = (char*)malloc(parallel * sizeof(char));
	if (!results || !merged_results || !signals) return;

	/* Collect 'ready' signals */
	for (i = 0; i < parallel * sizeof(char); i += bytes_read) {
		bytes_read = 0;
		FD_ZERO(&fds_read);
		FD_ZERO(&fds_error);
		FD_SET(response, &fds_read);
		FD_SET(response, &fds_error);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		select(response+1, &fds_read, NULL, &fds_error, &timeout);
		if (benchmp_sigchld_received 
		    || benchmp_sigterm_received
		    || FD_ISSET(response, &fds_error)) 
		{
#ifdef _DEBUG
			fprintf(stderr, "benchmp_parent: ready, benchmp_sigchld_received=%d\n", benchmp_sigchld_received);
#endif
			goto error_exit;
		}
		if (!FD_ISSET(response, &fds_read)) {
			continue;
		}

		bytes_read = read(response, signals, parallel * sizeof(char) - i);
		if (bytes_read < 0) {
#ifdef _DEBUG
			fprintf(stderr, "benchmp_parent: ready, bytes_read=%d, %s\n", bytes_read, strerror(errno));
#endif
			goto error_exit;
		}
	}

	/* let the children run for warmup microseconds */
	if (warmup > 0) {
		struct timeval delay;
		delay.tv_sec = warmup / 100000;
		delay.tv_usec = warmup % 100000;

		select(0, NULL, NULL, NULL, &delay);
	}

	/* send 'start' signal */
	write(start_signal, signals, parallel * sizeof(char));

	/* Collect 'done' signals */
	for (i = 0; i < parallel * sizeof(char); i += bytes_read) {
		bytes_read = 0;
		FD_ZERO(&fds_read);
		FD_ZERO(&fds_error);
		FD_SET(response, &fds_read);
		FD_SET(response, &fds_error);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		select(response+1, &fds_read, NULL, &fds_error, &timeout);
		if (benchmp_sigchld_received 
		    || benchmp_sigterm_received
		    || FD_ISSET(response, &fds_error)) 
		{
#ifdef _DEBUG
			fprintf(stderr, "benchmp_parent: done, benchmp_child_died=%d\n", benchmp_sigchld_received);
#endif
			goto error_exit;
		}
		if (!FD_ISSET(response, &fds_read)) {
			continue;
		}

		bytes_read = read(response, signals, parallel * sizeof(char) - i);
		if (bytes_read < 0) {
#ifdef _DEBUG
			fprintf(stderr, "benchmp_parent: done, bytes_read=%d, %s\n", bytes_read, strerror(errno));
#endif
			goto error_exit;
		}
	}

	/* collect results */
	insertinit(merged_results);
	for (i = 0; i < parallel; ++i) {
		int n = sizeof_result(repetitions);
		buf = (unsigned char*)results;

		FD_ZERO(&fds_read);
		FD_ZERO(&fds_error);

		/* tell one child to report its results */
		write(result_signal, buf, sizeof(char));

		for (; n > 0; n -= bytes_read, buf += bytes_read) {
			bytes_read = 0;
			FD_SET(response, &fds_read);
			FD_SET(response, &fds_error);

			timeout.tv_sec = 1;
			timeout.tv_usec = 0;
			select(response+1, &fds_read, NULL, &fds_error, &timeout);
			if (benchmp_sigchld_received 
			    || benchmp_sigterm_received
			    || FD_ISSET(response, &fds_error)) 
			{
#ifdef _DEBUG
				fprintf(stderr, "benchmp_parent: results, benchmp_sigchld_received=%d\n", benchmp_sigchld_received);
#endif
				goto error_exit;
			}
			if (!FD_ISSET(response, &fds_read)) {
				continue;
			}

			bytes_read = read(response, buf, n);
			if (bytes_read < 0) {
#ifdef _DEBUG
				fprintf(stderr, "benchmp_parent: results, bytes_read=%d, %s\n", bytes_read, strerror(errno));
#endif
				goto error_exit;
			}
		}
		for (j = 0; j < results->N; ++j) {
			insertsort(results->v[j].u, 
				   results->v[j].n, merged_results);
		}
	}

	/* we allow children to die now, without it causing an error */
	signal(SIGCHLD, SIG_IGN);
	
	/* send 'exit' signals */
	write(exit_signal, results, parallel * sizeof(char));

	/* Compute median time; iterations is constant! */
	set_results(merged_results);

	goto cleanup_exit;
error_exit:
#ifdef _DEBUG
	fprintf(stderr, "benchmp_parent: error_exit!\n");
#endif
	signal(SIGCHLD, SIG_IGN);
	for (i = 0; i < parallel; ++i) {
		kill(pids[i], SIGTERM);
	}
	free(merged_results);
cleanup_exit:
	close(response);
	close(start_signal);
	close(result_signal);
	close(exit_signal);

	if (results) free(results);
	if (signals) free(signals);
}


typedef enum { warmup, timing_interval, cooldown } benchmp_state;

typedef struct {
	benchmp_state	state;
	support_f	initialize;
	bench_f		benchmark;
	support_f	cleanup;
	int		childid;
	int		response;
	int		start_signal;
	int		result_signal;
	int		exit_signal;
	int		enough;
        iter_t		iterations;
	int		parallel;
        int		repetitions;
	void*		cookie;
	int		iterations_batch;
	int		need_warmup;
	long		i;
	int		r_size;
	result_t*	r;
} benchmp_child_state;

static benchmp_child_state _benchmp_child_state;

int
benchmp_childid()
{
	return _benchmp_child_state.childid;
}

void
benchmp_child_sigterm(int signo)
{
	signal(SIGTERM, SIG_IGN);
	if (_benchmp_child_state.cleanup)
		(*_benchmp_child_state.cleanup)(&_benchmp_child_state);
	exit(0);
}

void*
benchmp_getstate()
{
	return ((void*)&_benchmp_child_state);
}

void 
benchmp_child(support_f initialize, 
		bench_f benchmark,
		support_f cleanup,
		int childid,
		int response, 
		int start_signal, 
		int result_signal, 
		int exit_signal,
		int enough,
	        iter_t iterations,
		int parallel, 
	        int repetitions,
		void* cookie
		)
{
	iter_t		iterations_batch = (parallel > 1) ? get_n() : 1;
	double		result = 0.;
	double		usecs;
	long		i = 0;
	int		need_warmup;
	fd_set		fds;
	struct timeval	timeout;

	_benchmp_child_state.state = warmup;
	_benchmp_child_state.initialize = initialize;
	_benchmp_child_state.benchmark = benchmark;
	_benchmp_child_state.cleanup = cleanup;
	_benchmp_child_state.childid = childid;
	_benchmp_child_state.response = response;
	_benchmp_child_state.start_signal = start_signal;
	_benchmp_child_state.result_signal = result_signal;
	_benchmp_child_state.exit_signal = exit_signal;
	_benchmp_child_state.enough = enough;
	_benchmp_child_state.iterations = iterations;
	_benchmp_child_state.iterations_batch = iterations_batch;
	_benchmp_child_state.parallel = parallel;
	_benchmp_child_state.repetitions = repetitions;
	_benchmp_child_state.cookie = cookie;
	_benchmp_child_state.need_warmup = 1;
	_benchmp_child_state.i = 0;
	_benchmp_child_state.r_size = sizeof_result(repetitions);
	_benchmp_child_state.r = (result_t*)malloc(_benchmp_child_state.r_size);

	if (!_benchmp_child_state.r) return;
	insertinit(_benchmp_child_state.r);
	set_results(_benchmp_child_state.r);

	need_warmup = 1;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	signal(SIGCHLD, benchmp_sigchld_handler);

	if (initialize)
		(*initialize)(cookie);
	
	if (benchmp_sigterm_handler != SIG_DFL) {
		signal(SIGTERM, benchmp_sigterm_handler);
	} else {
		signal(SIGTERM, benchmp_child_sigterm);
	}
	if (benchmp_sigterm_received)
		benchmp_child_sigterm(SIGTERM);

	/* start experiments, collecting results */
	insertinit(_benchmp_child_state.r);

	start(0);
	while (1) {
		(*benchmark)(benchmp_interval(&_benchmp_child_state), cookie);
	}
}

iter_t
benchmp_interval(void* _state)
{
	char		c;
	iter_t		iterations;
	double		result;
	fd_set		fds;
	struct timeval	timeout;
	benchmp_child_state* state = (benchmp_child_state*)_state;

	result = stop(0,0);
	save_n(state->iterations);
	result -= t_overhead() + get_n() * l_overhead();
	settime(result >= 0. ? (uint64)result : 0.);

	/* if the parent died, then give up */
	if (getppid() == 1 && state->cleanup) {
		(*state->cleanup)(state->cookie);
		exit(0);
	}

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	FD_ZERO(&fds);

	switch (state->state) {
	case warmup:
		iterations = state->iterations_batch;
		if (state->need_warmup) {
			state->need_warmup = 0;
			/* send 'ready' */
			write(state->response, &c, sizeof(char));
		}
		FD_SET(state->start_signal, &fds);
		select(state->start_signal+1, &fds, NULL,
		       NULL, &timeout);
		if (FD_ISSET(state->start_signal, &fds)) {
			state->state = timing_interval;
			read(state->start_signal, &c, sizeof(char));
			iterations = state->iterations;
		}
		break;
	case timing_interval:
		iterations = state->iterations;
		if (state->parallel > 1 || result > 0.95 * state->enough) {
			insertsort(gettime(), get_n(), get_results());
			state->i++;
			/* we completed all the experiments, return results */
			if (state->i >= state->repetitions) {
				state->state = cooldown;
			}
		}
		if (state->parallel == 1 
		    && (result < 0.99 * state->enough || result > 1.2 * state->enough)) {
			if (result > 150.) {
				double tmp = iterations / result;
				tmp *= 1.1 * state->enough;
				iterations = (iter_t)(tmp + 1);
			} else {
				iterations <<= 3;
				if (iterations > 1<<27
				    || result < 0. && iterations > 1<<20) {
					state->state = cooldown;
				}
			}
		}
		if (state->state != cooldown) {
			state->iterations = iterations;
		} else {
			/* send 'done' */
			write(state->response, (void*)&c, sizeof(char));
			iterations = state->iterations_batch;
		}
		break;
	case cooldown:
		iterations = state->iterations_batch;
		FD_SET(state->result_signal, &fds);
		select(state->result_signal+1, &fds, NULL, NULL, &timeout);
		if (FD_ISSET(state->result_signal, &fds)) {
			/* 
			 * At this point all children have stopped their
			 * measurement loops, so we can block waiting for
			 * the parent to tell us to send our results back.
			 * From this point on, we will do no more "work".
			 */
			read(state->result_signal, (void*)&c, sizeof(char));
			write(state->response, (void*)get_results(), state->r_size);
			if (state->cleanup)
				(*state->cleanup)(state->cookie);

			/* Now wait for signal to exit */
			read(state->exit_signal, (void*)&c, sizeof(char));
			exit(0);
		}
	};
	start(0);
	return (iterations);
}


/*
 * Redirect output someplace else.
 */
void
timing(FILE *out)
{
	ftiming = out;
}

/*
 * Start timing now.
 */
void
start(struct timeval *tv)
{
	if (tv == NULL) {
		tv = &start_tv;
	}
#ifdef	RUSAGE
	getrusage(RUSAGE_SELF, &ru_start);
#endif
	(void) gettimeofday(tv, (struct timezone *) 0);
}

/*
 * Stop timing and return real time in microseconds.
 */
uint64
stop(struct timeval *begin, struct timeval *end)
{
	if (end == NULL) {
		end = &stop_tv;
	}
	(void) gettimeofday(end, (struct timezone *) 0);
#ifdef	RUSAGE
	getrusage(RUSAGE_SELF, &ru_stop);
#endif

	if (begin == NULL) {
		begin = &start_tv;
	}
	return (tvdelta(begin, end));
}

uint64
now(void)
{
	struct timeval t;
	uint64	m;

	(void) gettimeofday(&t, (struct timezone *) 0);
	m = t.tv_sec;
	m *= 1000000;
	m += t.tv_usec;
	return (m);
}

double
Now(void)
{
	struct timeval t;

	(void) gettimeofday(&t, (struct timezone *) 0);
	return (t.tv_sec * 1000000.0 + t.tv_usec);
}

uint64
delta(void)
{
	static struct timeval last;
	struct timeval t;
	struct timeval diff;
	uint64	m;

	(void) gettimeofday(&t, (struct timezone *) 0);
	if (last.tv_usec) {
		tvsub(&diff, &t, &last);
		last = t;
		m = diff.tv_sec;
		m *= 1000000;
		m += diff.tv_usec;
		return (m);
	} else {
		last = t;
		return (0);
	}
}

double
Delta(void)
{
	struct timeval t;
	struct timeval diff;

	(void) gettimeofday(&t, (struct timezone *) 0);
	tvsub(&diff, &t, &start_tv);
	return (diff.tv_sec + diff.tv_usec / 1000000.0);
}

void
save_n(uint64 n)
{
	iterations = n;
}

uint64
get_n(void)
{
	return (iterations);
}

/*
 * Make the time spend be usecs.
 */
void
settime(uint64 usecs)
{
	bzero((void*)&start_tv, sizeof(start_tv));
	stop_tv.tv_sec = usecs / 1000000;
	stop_tv.tv_usec = usecs % 1000000;
}

void
bandwidth(uint64 bytes, uint64 times, int verbose)
{
	struct timeval tdiff;
	double  mb, secs;

	tvsub(&tdiff, &stop_tv, &start_tv);
	secs = tdiff.tv_sec;
	secs *= 1000000;
	secs += tdiff.tv_usec;
	secs /= 1000000;
	secs /= times;
	mb = bytes / MB;
	if (!ftiming) ftiming = stderr;
	if (verbose) {
		(void) fprintf(ftiming,
		    "%.4f MB in %.4f secs, %.4f MB/sec\n",
		    mb, secs, mb/secs);
	} else {
		if (mb < 1) {
			(void) fprintf(ftiming, "%.6f ", mb);
		} else {
			(void) fprintf(ftiming, "%.2f ", mb);
		}
		if (mb / secs < 1) {
			(void) fprintf(ftiming, "%.6f\n", mb/secs);
		} else {
			(void) fprintf(ftiming, "%.2f\n", mb/secs);
		}
	}
}

void
kb(uint64 bytes)
{
	struct timeval td;
	double  s, bs;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	bs = bytes / nz(s);
	if (s == 0.0) return;
	if (!ftiming) ftiming = stderr;
	(void) fprintf(ftiming, "%.0f KB/sec\n", bs / KB);
}

void
mb(uint64 bytes)
{
	struct timeval td;
	double  s, bs;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	bs = bytes / nz(s);
	if (s == 0.0) return;
	if (!ftiming) ftiming = stderr;
	(void) fprintf(ftiming, "%.2f MB/sec\n", bs / MB);
}

void
latency(uint64 xfers, uint64 size)
{
	struct timeval td;
	double  s;

	if (!ftiming) ftiming = stderr;
	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	if (s == 0.0) return;
	if (xfers > 1) {
		fprintf(ftiming, "%d %dKB xfers in %.2f secs, ",
		    (int) xfers, (int) (size / KB), s);
	} else {
		fprintf(ftiming, "%.1fKB in ", size / KB);
	}
	if ((s * 1000 / xfers) > 100) {
		fprintf(ftiming, "%.0f millisec%s, ",
		    s * 1000 / xfers, xfers > 1 ? "/xfer" : "s");
	} else {
		fprintf(ftiming, "%.4f millisec%s, ",
		    s * 1000 / xfers, xfers > 1 ? "/xfer" : "s");
	}
	if (((xfers * size) / (MB * s)) > 1) {
		fprintf(ftiming, "%.2f MB/sec\n", (xfers * size) / (MB * s));
	} else {
		fprintf(ftiming, "%.2f KB/sec\n", (xfers * size) / (KB * s));
	}
}

void
context(uint64 xfers)
{
	struct timeval td;
	double  s;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	if (s == 0.0) return;
	if (!ftiming) ftiming = stderr;
	fprintf(ftiming,
	    "%d context switches in %.2f secs, %.0f microsec/switch\n",
	    (int)xfers, s, s * 1000000 / xfers);
}

void
nano(char *s, uint64 n)
{
	struct timeval td;
	double  micro;

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
	micro *= 1000;
	if (micro == 0.0) return;
	if (!ftiming) ftiming = stderr;
	fprintf(ftiming, "%s: %.2f nanoseconds\n", s, micro / n);
}

void
micro(char *s, uint64 n)
{
	struct timeval td;
	double	micro;

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
	micro /= n;
	if (micro == 0.0) return;
	//if (!ftiming) ftiming = stderr;
        ftiming = stderr;
	fprintf(ftiming, "%s: %.4f microseconds\n", s, micro);
	/*
#if 0
	if (micro >= 100) {
		fprintf(ftiming, "%s: %.1f microseconds\n", s, micro);
	} else if (micro >= 10) {
		fprintf(ftiming, "%s: %.3f microseconds\n", s, micro);
	} else {
		fprintf(ftiming, "%s: %.4f microseconds\n", s, micro);
	}
#endif
	*/
}

void
micromb(uint64 sz, uint64 n)
{
	struct timeval td;
	double	mb, micro;

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
	micro /= n;
	mb = sz;
	mb /= MB;
	if (micro == 0.0) return;
	//if (!ftiming) ftiming = stderr;
        ftiming = stderr;
	if (micro >= 10) {
		fprintf(ftiming, "%.6f %.0f\n", mb, micro);
	} else {
		fprintf(ftiming, "%.6f %.3f\n", mb, micro);
	}
}

void
milli(char *s, uint64 n)
{
	struct timeval td;
	uint64 milli;

	tvsub(&td, &stop_tv, &start_tv);
	milli = td.tv_sec * 1000 + td.tv_usec / 1000;
	milli /= n;
	if (milli == 0.0) return;
	//if (!ftiming) ftiming = stderr;
	ftiming = stderr;
        fprintf(ftiming, "%s: %d milliseconds\n", s, (int)milli);
}

void
ptime(uint64 n)
{
	struct timeval td;
	double  s;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	if (s == 0.0) return;
	if (!ftiming) ftiming = stderr;
	fprintf(ftiming,
	    "%d in %.2f secs, %.0f microseconds each\n",
	    (int)n, s, s * 1000000 / n);
}

uint64
tvdelta(struct timeval *start, struct timeval *stop)
{
	struct timeval td;
	uint64	usecs;

	tvsub(&td, stop, start);
	usecs = td.tv_sec;
	usecs *= 1000000;
	usecs += td.tv_usec;
	return (usecs);
}

void
tvsub(struct timeval * tdiff, struct timeval * t1, struct timeval * t0)
{
	tdiff->tv_sec = t1->tv_sec - t0->tv_sec;
	tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
	if (tdiff->tv_usec < 0 && tdiff->tv_sec > 0) {
		tdiff->tv_sec--;
		tdiff->tv_usec += 1000000;
		assert(tdiff->tv_usec >= 0);
	}

	/* time shouldn't go backwards!!! */
	if (tdiff->tv_usec < 0 || t1->tv_sec < t0->tv_sec) {
		tdiff->tv_sec = 0;
		tdiff->tv_usec = 0;
	}
}

uint64
gettime(void)
{
	return (tvdelta(&start_tv, &stop_tv));
}

double
timespent(void)
{
	struct timeval td;

	tvsub(&td, &stop_tv, &start_tv);
	return (td.tv_sec + td.tv_usec / 1000000.0);
}

static	char	p64buf[10][20];
static	int	n;

char	*
p64(uint64 big)
{
	char	*s = p64buf[n++];

	if (n == 10) n = 0;
#ifdef  linux
	{
        int     *a = (int*)&big;

        if (a[1]) {
                sprintf(s, "0x%x%08x", a[1], a[0]);
        } else {
                sprintf(s, "0x%x", a[0]);
        }
	}
#endif
#ifdef	__sgi
        sprintf(s, "0x%llx", big);
#endif
	return (s);
}

char	*
p64sz(uint64 big)
{
	double	d = big;
	char	*tags = " KMGTPE";
	int	t = 0;
	char	*s = p64buf[n++];

	if (n == 10) n = 0;
	while (d > 512) t++, d /= 1024;
	if (d == 0) {
		return ("0");
	}
	if (d < 100) {
		sprintf(s, "%.4f%c", d, tags[t]);
	} else {
		sprintf(s, "%.2f%c", d, tags[t]);
	}
	return (s);
}

char
last(char *s)
{
	while (*s++)
		;
	return (s[-2]);
}

uint64
bytes(char *s)
{
	uint64	n;

	if (sscanf(s, "%llu", &n) < 1)
		return (0);

	if ((last(s) == 'k') || (last(s) == 'K'))
		n *= 1024;
	if ((last(s) == 'm') || (last(s) == 'M'))
		n *= (1024 * 1024);
	return (n);
}

void
use_int(int result) { use_result_dummy += result; }

void
use_pointer(void *result) { use_result_dummy += (int)result; }

int
sizeof_result(int repetitions)
{
	if (repetitions <= TRIES)
		return (sizeof(result_t));
	return (sizeof(result_t) + (repetitions - TRIES) * sizeof(value_t));
}

void
insertinit(result_t *r)
{
	int	i;

	r->N = 0;
}

/* biggest to smallest */
void
insertsort(uint64 u, uint64 n, result_t *r)
{
	int	i, j;

	if (u == 0) return;

	for (i = 0; i < r->N; ++i) {
		if (u/(double)n > r->v[i].u/(double)r->v[i].n) {
			for (j = r->N; j > i; --j) {
				r->v[j] = r->v[j - 1];
			}
			break;
		}
	}
	r->v[i].u = u;
	r->v[i].n = n;
	r->N++;
}

static result_t  _results;
static result_t* results = &_results;

result_t*
get_results()
{
	return (results);
}

void
set_results(result_t *r)
{
	results = r;
	save_median();
}

void
save_minimum()
{
	if (results->N == 0) {
		save_n(1);
		settime(0);
	} else {
		save_n(results->v[results->N - 1].n);
		settime(results->v[results->N - 1].u);
	}
}

void
save_median()
{
	int	i = results->N / 2;
	uint64	u, n;

	if (results->N == 0) {
		n = 1;
		u = 0;
	} else if (results->N % 2) {
		n = results->v[i].n;
		u = results->v[i].u;
	} else {
		n = (results->v[i].n + results->v[i-1].n) / 2;
		u = (results->v[i].u + results->v[i-1].u) / 2;
	}
#ifdef _DEBUG
	fprintf(stderr, "save_median: N=%d, n=%lu, u=%lu\n", results->N, (unsigned long)n, (unsigned long)u);
#endif /* _DEBUG */
	save_n(n); settime(u);
}

/*
 * The inner loop tracks bench.h but uses a different results array.
 */
static long *
one_op(register long *p)
{
	BENCH_INNER(p = (long *)*p;, 0);
	return (p);
}

static long *
two_op(register long *p)
{
	BENCH_INNER(p = (long *)*p; p = (long*)*p;, 0);
	return (p);
}

static long	*p = (long *)&p;
static long	*q = (long *)&q;

double
l_overhead(void)
{
	int	i;
	uint64	N_save, u_save;
	static	double overhead;
	static	int initialized = 0;
	result_t one, two, *r_save;

	init_timing();
	if (initialized) return (overhead);

	initialized = 1;
	if (getenv("LOOP_O")) {
		overhead = atof(getenv("LOOP_O"));
	} else {
		r_save = get_results(); N_save = get_n(); u_save = gettime(); 
		insertinit(&one);
		insertinit(&two);
		for (i = 0; i < TRIES; ++i) {
			use_pointer((void*)one_op(p));
			if (gettime() > t_overhead())
				insertsort(gettime() - t_overhead(), get_n(), &one);
			use_pointer((void *)two_op(p));
			if (gettime() > t_overhead())
				insertsort(gettime() - t_overhead(), get_n(), &two);
		}
		/*
		 * u1 = (n1 * (overhead + work))
		 * u2 = (n2 * (overhead + 2 * work))
		 * ==> overhead = 2. * u1 / n1 - u2 / n2
		 */
		set_results(&one); 
		save_minimum();
		overhead = 2. * gettime() / (double)get_n();
		
		set_results(&two); 
		save_minimum();
		overhead -= gettime() / (double)get_n();
		
		if (overhead < 0.) overhead = 0.;	/* Gag */

		set_results(r_save); save_n(N_save); settime(u_save); 
	}
	return (overhead);
}

/*
 * Figure out the timing overhead.  This has to track bench.h
 */
uint64
t_overhead(void)
{
	uint64		N_save, u_save;
	static int	initialized = 0;
	static uint64	overhead = 0;
	struct timeval	tv;
	result_t	*r_save;

	init_timing();
	if (initialized) return (overhead);

	initialized = 1;
	if (getenv("TIMING_O")) {
		overhead = atof(getenv("TIMING_O"));
	} else if (get_enough(0) <= 50000) {
		/* it is not in the noise, so compute it */
		int		i;
		result_t	r;

		r_save = get_results(); N_save = get_n(); u_save = gettime(); 
		insertinit(&r);
		for (i = 0; i < TRIES; ++i) {
			BENCH_INNER(gettimeofday(&tv, 0), 0);
			insertsort(gettime(), get_n(), &r);
		}
		set_results(&r);
		save_minimum();
		overhead = gettime() / get_n();

		set_results(r_save); save_n(N_save); settime(u_save); 
	}
	return (overhead);
}

/*
 * Figure out how long to run it.
 * If enough == 0, then they want us to figure it out.
 * If enough is !0 then return it unless we think it is too short.
 */
static	int	long_enough;
static	int	compute_enough();

int
get_enough(int e)
{
	init_timing();
	return (long_enough > e ? long_enough : e);
}


static void
init_timing(void)
{
	static	int done = 0;

	if (done) return;
	done = 1;
	long_enough = compute_enough();
	t_overhead();
	l_overhead();
}

typedef long TYPE;

static TYPE **
enough_duration(register long N, register TYPE ** p)
{
#define	ENOUGH_DURATION_TEN(one)	one one one one one one one one one one
	while (N-- > 0) {
		ENOUGH_DURATION_TEN(p = (TYPE **) *p;);
	}
	return (p);
}

static uint64
duration(long N)
{
	uint64	usecs;
	TYPE   *x = (TYPE *)&x;
	TYPE  **p = (TYPE **)&x;

	start(0);
	p = enough_duration(N, p);
	usecs = stop(0, 0);
	use_pointer((void *)p);
	return (usecs);
}

/*
 * find the minimum time that work "N" takes in "tries" tests
 */
static uint64
time_N(iter_t N)
{
	int     i;
	uint64	usecs;
	result_t r, *r_save;

	r_save = get_results();
	insertinit(&r);
	for (i = 1; i < TRIES; ++i) {
		usecs = duration(N);
		insertsort(usecs, N, &r);
	}
	set_results(&r);
	save_minimum();
	usecs = gettime();
	set_results(r_save);
	return (usecs);
}

/*
 * return the amount of work needed to run "enough" microseconds
 */
static long
find_N(int enough)
{
	int		tries;
	static iter_t	N = 10000;
	static uint64	usecs = 0;

	if (!usecs) usecs = time_N(N);

	for (tries = 0; tries < 10; ++tries) {
		if (0.98 * enough < usecs && usecs < 1.02 * enough)
			return (N);
		if (usecs < 1000)
			N *= 10;
		else {
			double  n = N;

			n /= usecs;
			n *= enough;
			N = n + 1;
		}
		usecs = time_N(N);
	}
	return (-1);
}

/*
 * We want to verify that small modifications proportionally affect the runtime
 */
static double test_points[] = {1.015, 1.02, 1.035};
static int
test_time(int enough)
{
	int     i;
	iter_t	N;
	uint64	usecs, expected, baseline, diff;

	if ((N = find_N(enough)) <= 0)
		return (0);

	baseline = time_N(N);

	for (i = 0; i < sizeof(test_points) / sizeof(double); ++i) {
		usecs = time_N((int)((double) N * test_points[i]));
		expected = (uint64)((double)baseline * test_points[i]);
		diff = expected > usecs ? expected - usecs : usecs - expected;
		if (diff / (double)expected > 0.0025)
			return (0);
	}
	return (1);
}


/*
 * We want to find the smallest timing interval that has accurate timing
 */
static int     possibilities[] = { 5000, 10000, 50000, 100000 };
static int
compute_enough()
{
	int     i;

	if (getenv("ENOUGH")) {
		return (atoi(getenv("ENOUGH")));
	}
	for (i = 0; i < sizeof(possibilities) / sizeof(int); ++i) {
		if (test_time(possibilities[i]))
			return (possibilities[i]);
	}

	/* 
	 * if we can't find a timing interval that is sufficient, 
	 * then use SHORT as a default.
	 */
	return (SHORT);
}

/*
 * This stuff isn't really lib_timing, but ...
 */
void
morefds(void)
{
#ifdef	RLIMIT_NOFILE
	struct	rlimit r;

	getrlimit(RLIMIT_NOFILE, &r);
	r.rlim_cur = r.rlim_max;
	setrlimit(RLIMIT_NOFILE, &r);
#endif
}

/* analogous to bzero, bcopy, etc., except that it just reads
 * data into the processor
 */
long
bread(void* buf, long nbytes)
{
	long sum = 0;
	register long *p, *next;
	register char *end;

	p = (long*)buf;
	end = (char*)buf + nbytes;
	for (next = p + 128; (void*)next <= (void*)end; p = next, next += 128) {
		sum +=
			p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+
			p[8]+p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+
			p[15]+p[16]+p[17]+p[18]+p[19]+p[20]+p[21]+
			p[22]+p[23]+p[24]+p[25]+p[26]+p[27]+p[28]+
			p[29]+p[30]+p[31]+p[32]+p[33]+p[34]+p[35]+
			p[36]+p[37]+p[38]+p[39]+p[40]+p[41]+p[42]+
			p[43]+p[44]+p[45]+p[46]+p[47]+p[48]+p[49]+
			p[50]+p[51]+p[52]+p[53]+p[54]+p[55]+p[56]+
			p[57]+p[58]+p[59]+p[60]+p[61]+p[62]+p[63]+
			p[64]+p[65]+p[66]+p[67]+p[68]+p[69]+p[70]+
			p[71]+p[72]+p[73]+p[74]+p[75]+p[76]+p[77]+
			p[78]+p[79]+p[80]+p[81]+p[82]+p[83]+p[84]+
			p[85]+p[86]+p[87]+p[88]+p[89]+p[90]+p[91]+
			p[92]+p[93]+p[94]+p[95]+p[96]+p[97]+p[98]+
			p[99]+p[100]+p[101]+p[102]+p[103]+p[104]+
			p[105]+p[106]+p[107]+p[108]+p[109]+p[110]+
			p[111]+p[112]+p[113]+p[114]+p[115]+p[116]+
			p[117]+p[118]+p[119]+p[120]+p[121]+p[122]+
			p[123]+p[124]+p[125]+p[126]+p[127];
	}
	for (next = p + 16; (void*)next <= (void*)end; p = next, next += 16) {
		sum +=
			p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+
			p[8]+p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+
			p[15];
	}
	for (next = p + 1; (void*)next <= (void*)end; p = next, next++) {
		sum += *p;
	}
	return sum;
}

void
touch(char *buf, int nbytes)
{
	static	int psize;

	if (!psize) {
		psize = getpagesize();
	}
	while (nbytes > 0) {
		*buf = 1;
		buf += psize;
		nbytes -= psize;
	}
}

int*
permutation(int max, int scale)
{
	int	i, v;
	static unsigned int r = 0;
	int*	result = (int*)malloc(max * sizeof(int));

	if (result == NULL) return NULL;

	for (i = 0; i < max; ++i) {
		result[i] = i * scale;
	}

	if (r == 0)
		r = (getpid()<<6) ^ getppid() ^ rand() ^ (rand()<<10);

	/* randomize the sequence */
	for (i = max - 1; i > 0; --i) {
		r = (r << 1) ^ rand();
		v = result[r % (i + 1)];
		result[r % (i + 1)] = result[i];
		result[i] = v;
	}

#ifdef _DEBUG
	fprintf(stderr, "permutation(%d): {", max);
	for (i = 0; i < max; ++i) {
	  fprintf(stderr, "%d", result[i]);
	  if (i < max - 1) 
	    fprintf(stderr, ",");
	}
	fprintf(stderr, "}\n");
	fflush(stderr);
#endif /* _DEBUG */

	return (result);
}

int
cp(char* src, char* dst, mode_t mode)
{
	int sfd, dfd;
	char buf[8192];
	ssize_t size;

	if ((sfd = open(src, O_RDONLY)) < 0) {
		return -1;
	}
	if ((dfd = open(dst, O_CREAT|O_TRUNC|O_RDWR, mode)) < 0) {
		return -1;
	}
	while ((size = read(sfd, buf, 8192)) > 0) {
		if (write(dfd, buf, size) < size) return -1;
	}
	fsync(dfd);
	close(sfd);
	close(dfd);
}

#if defined(hpux) || defined(__hpux)
int
getpagesize()
{
	return (sysconf(_SC_PAGE_SIZE));
}
#endif

#ifdef WIN32
int
getpagesize()
{
	SYSTEM_INFO s;

	GetSystemInfo(&s);
	return ((int)s.dwPageSize);
}

LARGE_INTEGER
getFILETIMEoffset()
{
	SYSTEMTIME s;
	FILETIME f;
	LARGE_INTEGER t;

	s.wYear = 1970;
	s.wMonth = 1;
	s.wDay = 1;
	s.wHour = 0;
	s.wMinute = 0;
	s.wSecond = 0;
	s.wMilliseconds = 0;
	SystemTimeToFileTime(&s, &f);
	t.QuadPart = f.dwHighDateTime;
	t.QuadPart <<= 32;
	t.QuadPart |= f.dwLowDateTime;
	return (t);
}

int
gettimeofday(struct timeval *tv, struct timezone *tz)
{
	LARGE_INTEGER			t;
	FILETIME			f;
	double					microseconds;
	static LARGE_INTEGER	offset;
	static double			frequencyToMicroseconds;
	static int				initialized = 0;
	static BOOL				usePerformanceCounter = 0;

	if (!initialized) {
		LARGE_INTEGER performanceFrequency;
		initialized = 1;
		usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
		if (usePerformanceCounter) {
			QueryPerformanceCounter(&offset);
			frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
		} else {
			offset = getFILETIMEoffset();
			frequencyToMicroseconds = 10.;
		}
	}
	if (usePerformanceCounter) QueryPerformanceCounter(&t);
	else {
		GetSystemTimeAsFileTime(&f);
		t.QuadPart = f.dwHighDateTime;
		t.QuadPart <<= 32;
		t.QuadPart |= f.dwLowDateTime;
	}

	t.QuadPart -= offset.QuadPart;
	microseconds = (double)t.QuadPart / frequencyToMicroseconds;
	t.QuadPart = microseconds;
	tv->tv_sec = t.QuadPart / 1000000;
	tv->tv_usec = t.QuadPart % 1000000;
	return (0);
}
#endif





#define BSIZE 1024

int		numInChan;
int		numOutChan;

float* 	inChannel[256];
float* 	outChannel[256];

void benchmark_computation(iter_t repeat, void* cookie)
{
  int sizebloc =  *(int*)cookie;

  for(int j=0; j<repeat*BSIZE/sizebloc; j++) DSP.compute(sizebloc,inChannel,outChannel);
}

void bench(long buffer, long repeat)
{
  // allocation des canaux audios pour le dsp
  numInChan = DSP.getNumInputs();
  numOutChan = DSP.getNumOutputs();
	
  assert (numInChan < 256);
  assert (numOutChan < 256);
   
  for (int i = 0; i < numInChan; i++) inChannel[i] = (float*) aligned_calloc (BSIZE, sizeof(float));
  for (int i = 0; i < numOutChan; i++) outChannel[i] = (float*) aligned_calloc (BSIZE, sizeof(float));


  benchmp(NULL,benchmark_computation,NULL,0,1,0,repeat,&buffer);

  milli("Elapsed time milliseconds: ", get_n());
  micro("Elapsed time microseconds: ", get_n());
  nano("Elapsed time nanoseconds: ", get_n());
}



//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

// lopt : Scan Command Line long int Arguments

long lopt (int argc, char *argv[], char* longname, char* shortname, long def)
{
	for (int i=2; i<argc; i++)
		if ( strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0 )
			return atoi(argv[i]);
	return def;
}	


int main(int argc, char *argv[] )
{
  bool rt = setRealtimePriority();
  printf(rt?"RealTime Set\n":"RealTime Not Set\n"); 


  bench(lopt(argc,argv,"--buffer","-b",128),lopt(argc,argv,"--repeat","-r",100));



  return 0;
}





