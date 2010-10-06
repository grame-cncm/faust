
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __ICC
#define INLINE __forceinline
#else
#define INLINE inline
#endif

// Globals

#define THREAD_POOL_SIZE 16
#define JACK_SCHED_POLICY SCHED_FIFO

/* use 512KB stack per thread - the default is way too high to be feasible
 * with mlockall() on many systems */
#define THREAD_STACK 524288

typedef void* (ThreadHandler) (void* arg);

static int GetPID()
{
#ifdef WIN32
    return  _getpid();
#else
    return getpid();
#endif
}

#ifdef __APPLE__
#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#include <mach/thread_policy.h>
#include <mach/thread_act.h>

#endif

struct CopyThread {

    pthread_t fThread;
    sem_t* fSemaphore;
    char fName[128];

    #ifdef __APPLE__
    
    void CancelThread()
    {
        mach_port_t machThread = pthread_mach_thread_np(fThread);
        thread_terminate(machThread);
    }

    #endif

    #ifdef __linux__

    void CancelThread()
    {
        pthread_cancel(fThread);
        pthread_join(fThread, NULL);
    }

    #endif
    
    CopyThread()
    {
        sprintf(fName, "faust_sem_%d_%p", GetPID(), this);
        if ((fSemaphore = sem_open(fName, O_CREAT, 0777, 0)) == (sem_t*)SEM_FAILED) {
            std::cerr << "Allocate: can't check in named semaphore name = " <<fName << " " << strerror(errno) << std::endl;
            throw std::bad_alloc();
        }
    }
    
    ~CopyThread()
    {
        sem_unlink(fName);
        sem_close(fSemaphore);
    }
    
    void Wait()
    {
        while (sem_wait(fSemaphore) != 0) {}
    }
    
    void Signal()
    {
         sem_post(fSemaphore);
    }
 
    int Start(bool realtime, ThreadHandler fun, void* arg)
    {
        pthread_attr_t attributes;
        struct sched_param rt_param;
        pthread_attr_init(&attributes);
        
        int priority = 60; // TODO
        int res;
        
        /*
        if (realtime) {
            fRealTime = true;
        }else {
            fRealTime = getenv("OMP_REALTIME") ? strtol(getenv("OMP_REALTIME"), NULL, 10) : true;
        }
        */
                               
        if ((res = pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE))) {
            printf("Cannot request joinable thread creation for real-time thread res = %d err = %s\n", res, strerror(errno));
            return -1;
        }

        if ((res = pthread_attr_setscope(&attributes, PTHREAD_SCOPE_SYSTEM))) {
            printf("Cannot set scheduling scope for real-time thread res = %d err = %s\n", res, strerror(errno));
            return -1;
        }

        if (realtime) {
            
            if ((res = pthread_attr_setinheritsched(&attributes, PTHREAD_EXPLICIT_SCHED))) {
                printf("Cannot request explicit scheduling for RT thread res = %d err = %s\n", res, strerror(errno));
                return -1;
            }
        
            if ((res = pthread_attr_setschedpolicy(&attributes, JACK_SCHED_POLICY))) {
                printf("Cannot set RR scheduling class for RT thread res = %d err = %s\n", res, strerror(errno));
                return -1;
            }
            
            memset(&rt_param, 0, sizeof(rt_param));
            rt_param.sched_priority = priority;

            if ((res = pthread_attr_setschedparam(&attributes, &rt_param))) {
                printf("Cannot set scheduling priority for RT thread res = %d err = %s\n", res, strerror(errno));
                return -1;
            }

        } else {
            
            if ((res = pthread_attr_setinheritsched(&attributes, PTHREAD_INHERIT_SCHED))) {
                printf("Cannot request explicit scheduling for RT thread res = %d err = %s\n", res, strerror(errno));
                return -1;
            }
        }
     
        if ((res = pthread_attr_setstacksize(&attributes, THREAD_STACK))) {
            printf("Cannot set thread stack size res = %d err = %s\n", res, strerror(errno));
            return -1;
        }
        
        if ((res = pthread_create(&fThread, &attributes, fun, arg))) {
            printf("Cannot create thread res = %d err = %s\n", res, strerror(errno));
            return -1;
        }

        pthread_attr_destroy(&attributes);
        return 0;
    }

    void Stop()
    {
        CancelThread();
    }
    
};

char* load_program_source(const char *filename)
{
    struct stat statbuf;
    FILE* fh;
    char* source;

    fh = fopen(filename, "r");
    if (fh == 0)
        return 0;

    stat(filename, &statbuf);
    source = (char *) malloc(statbuf.st_size + 1);
    fread(source, statbuf.st_size, 1, fh);
    source[statbuf.st_size] = '\0';

    return source;
}

#ifdef __cplusplus
}
#endif
