
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

#include <mach/thread_policy.h>
#include <mach/thread_act.h>

#define THREAD_SET_PRIORITY         0
#define THREAD_SCHEDULED_PRIORITY   1

static UInt32 GetThreadPriority(pthread_t thread, int inWhichPriority);

// returns the thread's priority as it was last set by the API
static UInt32 GetThreadSetPriority(pthread_t thread)
{
    return GetThreadPriority(thread, THREAD_SET_PRIORITY);
}

// returns the thread's priority as it was last scheduled by the Kernel
static UInt32 GetThreadScheduledPriority(pthread_t thread)
{
    return GetThreadPriority(thread, THREAD_SCHEDULED_PRIORITY);
}

static int SetThreadToPriority(pthread_t thread, UInt32 inPriority, Boolean inIsFixed, UInt64 period, UInt64 computation, UInt64 constraint)
{
    if (inPriority == 96) {
        // REAL-TIME / TIME-CONSTRAINT THREAD
        thread_time_constraint_policy_data_t theTCPolicy;
        theTCPolicy.period = period;
        theTCPolicy.computation = computation;
        theTCPolicy.constraint = constraint;
        theTCPolicy.preemptible = true;
        kern_return_t res = thread_policy_set(pthread_mach_thread_np(thread), THREAD_TIME_CONSTRAINT_POLICY, (thread_policy_t)&theTCPolicy, THREAD_TIME_CONSTRAINT_POLICY_COUNT);
        return (res == KERN_SUCCESS) ? 0 : -1;
    } else {
        // OTHER THREADS
        thread_extended_policy_data_t theFixedPolicy;
        thread_precedence_policy_data_t thePrecedencePolicy;
        SInt32 relativePriority;
        
        // [1] SET FIXED / NOT FIXED
        theFixedPolicy.timeshare = !inIsFixed;
        thread_policy_set(pthread_mach_thread_np(thread), THREAD_EXTENDED_POLICY, (thread_policy_t)&theFixedPolicy, THREAD_EXTENDED_POLICY_COUNT);
        
        // [2] SET PRECEDENCE
        // N.B.: We expect that if thread A created thread B, and the program wishes to change
        // the priority of thread B, then the call to change the priority of thread B must be
        // made by thread A.
        // This assumption allows us to use pthread_self() to correctly calculate the priority
        // of the feeder thread (since precedency policy's importance is relative to the
        // spawning thread's priority.)
        relativePriority = inPriority - GetThreadSetPriority(pthread_self());
        
        thePrecedencePolicy.importance = relativePriority;
        kern_return_t res = thread_policy_set(pthread_mach_thread_np(thread), THREAD_PRECEDENCE_POLICY, (thread_policy_t)&thePrecedencePolicy, THREAD_PRECEDENCE_POLICY_COUNT);
        return (res == KERN_SUCCESS) ? 0 : -1;
    }
}

static UInt32 GetThreadPriority(pthread_t thread, int inWhichPriority)
{
    thread_basic_info_data_t threadInfo;
    policy_info_data_t thePolicyInfo;
    unsigned int count;
    
    // get basic info
    count = THREAD_BASIC_INFO_COUNT;
    thread_info(pthread_mach_thread_np(thread), THREAD_BASIC_INFO, (thread_info_t)&threadInfo, &count);
    
    switch (threadInfo.policy) {
        case POLICY_TIMESHARE:
            count = POLICY_TIMESHARE_INFO_COUNT;
            thread_info(pthread_mach_thread_np(thread), THREAD_SCHED_TIMESHARE_INFO, (thread_info_t)&(thePolicyInfo.ts), &count);
            if (inWhichPriority == THREAD_SCHEDULED_PRIORITY) {
                return thePolicyInfo.ts.cur_priority;
            } else {
                return thePolicyInfo.ts.base_priority;
            }
            break;
            
        case POLICY_FIFO:
            count = POLICY_FIFO_INFO_COUNT;
            thread_info(pthread_mach_thread_np(thread), THREAD_SCHED_FIFO_INFO, (thread_info_t)&(thePolicyInfo.fifo), &count);
            if ((thePolicyInfo.fifo.depressed) && (inWhichPriority == THREAD_SCHEDULED_PRIORITY)) {
                return thePolicyInfo.fifo.depress_priority;
            }
            return thePolicyInfo.fifo.base_priority;
            break;
            
        case POLICY_RR:
            count = POLICY_RR_INFO_COUNT;
            thread_info(pthread_mach_thread_np(thread), THREAD_SCHED_RR_INFO, (thread_info_t)&(thePolicyInfo.rr), &count);
            if ((thePolicyInfo.rr.depressed) && (inWhichPriority == THREAD_SCHEDULED_PRIORITY)) {
                return thePolicyInfo.rr.depress_priority;
            }
            return thePolicyInfo.rr.base_priority;
            break;
    }
    
    return 0;
}

static int GetParams(pthread_t thread, UInt64* period, UInt64* computation, UInt64* constraint)
{
    thread_time_constraint_policy_data_t theTCPolicy;
    mach_msg_type_number_t count = THREAD_TIME_CONSTRAINT_POLICY_COUNT;
    boolean_t get_default = false;
    
    kern_return_t res = thread_policy_get(pthread_mach_thread_np(thread),
                                          THREAD_TIME_CONSTRAINT_POLICY,
                                          (thread_policy_t)&theTCPolicy,
                                          &count,
                                          &get_default);
    if (res == KERN_SUCCESS) {
        *period = theTCPolicy.period;
        *computation = theTCPolicy.computation;
        *constraint = theTCPolicy.constraint;
        return 0;
    } else {
        return -1;
    }
}

static UInt64 period = 0;
static UInt64 computation = 0;
static UInt64 constraint = 0;

INLINE void GetRealTime()
{
    if (period == 0) {
        GetParams(pthread_self(), &period, &computation, &constraint);
    }
}

INLINE void SetRealTime()
{
    SetThreadToPriority(pthread_self(), 96, true, period, computation, constraint);
}

#endif

struct RunThread {

    pthread_t fThread;
    sem_t* fSemaphore;
    char fName[128];
    bool fRealTime;

    #ifdef __APPLE__
    
    void Cancel()
    {
        mach_port_t machThread = pthread_mach_thread_np(fThread);
        thread_terminate(machThread);
    }
    
    void Join()
    {
        sem_post(fSemaphore);
        pthread_join(fThread, NULL);
    }


    #endif

    #ifdef __linux__

    void Cancel()
    {
        pthread_cancel(fThread);
        pthread_join(fThread, NULL);
    }
    
    void Join()
    {
        sem_post(fSemaphore);
        pthread_join(fThread, NULL);
    }

    #endif
    
    RunThread()
    {
        sprintf(fName, "faust_sem_%d_%p", GetPID(), this);
        if ((fSemaphore = sem_open(fName, O_CREAT, 0777, 0)) == (sem_t*)SEM_FAILED) {
            std::cerr << "Allocate: can't check in named semaphore name = " <<fName << " " << strerror(errno) << std::endl;
            throw std::bad_alloc();
        }
    }
    
    ~RunThread()
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
        
        int priority = 70; // TODO
        int res;
        
        if (realtime) {
            fRealTime = true;
        }else {
            fRealTime = getenv("OMP_REALTIME") ? strtol(getenv("OMP_REALTIME"), NULL, 10) : true;
        }
                               
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
        Cancel();
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
