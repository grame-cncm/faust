/************************************************************************
    FAUST Architecture File
    Copyright (C) 2010-2012 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

// For AVOIDDENORMALS
#include "faust/dsp/dsp.h"

#ifdef __cplusplus
extern "C" {
#endif

// Globals

static int GetPID()
{
#ifdef WIN32
    return _getpid();
#else
    return getpid();
#endif
}

#define WORK_STEALING_INDEX 0
#define LAST_TASK_INDEX 1

#define MASTER_THREAD 0
#define MAX_STEAL_DUR 50                        // in usec
#define DEFAULT_CLOCKS_PER_SEC 2500000000       // in cycles (2,5 Ghz)
#define JACK_SCHED_POLICY SCHED_FIFO
#define KDSPMESURE 50

#define MEAN_TRESHOLD 0.1f   // in percentage

#ifdef __ICC
    #define INLINE __forceinline
#else
    #define INLINE inline
#endif

#ifdef __linux__

// handle 32/64 bits int size issues
#ifdef __x86_64__
#define UInt32 unsigned int
#define UInt64 unsigned long int
#else
#define UInt32 unsigned int
#define UInt64 unsigned long long int
#endif

#endif

#ifdef __APPLE__
    #include <mach/mach.h>
#elif defined(_WIN32)
    #include <windows.h>
#else
    #include <semaphore.h>
    #include <errno.h>
#endif

/*
  Copyright (C) 2012 Paul Davis
  Author: David Robillard

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
static int GetPID()
{
#ifdef WIN32
    return _getpid();
#else
    return getpid();
#endif
}

  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/**
   Unnamed (process local) counting semaphore.

   The civilized person's synchronisation primitive. A counting semaphore is
   an integer which is always non-negative, so, an attempted decrement (or
   "wait") will block if the value is 0, until another thread does an increment
   (or "post").

   At least on Lignux, the main advantage of this is that it is fast and the
   only safe way to reliably signal from a real-time audio thread. The
   counting semantics also complement ringbuffers of events nicely.
*/

class Semaphore
{
    public:
        /**
           Create a new semaphore.
           Chances are you want 1 wait() per 1 post(), an initial value of 0.
        */
        inline Semaphore(unsigned initial);

        inline ~Semaphore();

        /** Post/Increment/Signal */
        inline void post();

        /** Wait/Decrement.  Returns false on error. */
        inline bool wait();

        /** Attempt Wait/Decrement.  Returns true iff a decrement occurred. */
        inline bool try_wait();

    private:
    #if defined(__APPLE__)
        semaphore_t _sem;  // sem_t is a worthless broken mess on OSX
    #elif defined(_WIN32)
        HANDLE _sem;  // types are overrated anyway
    #else
        char fName[128];
        sem_t* _sem;
    #endif
};

#ifdef __APPLE__

inline Semaphore::Semaphore(unsigned initial)
{
	if (semaphore_create(mach_task_self(), &_sem, SYNC_POLICY_FIFO, initial)) {
		throw -1;
	}
}

inline Semaphore::~Semaphore()
{
	semaphore_destroy(mach_task_self(), _sem);
}

inline void Semaphore::post()
{
	semaphore_signal(_sem);
}

inline bool Semaphore::wait()
{
	if (semaphore_wait(_sem) != KERN_SUCCESS) {
		return false;
	}
	return true;
}

inline bool Semaphore::try_wait()
{
	const mach_timespec_t zero = { 0, 0 };
	return semaphore_timedwait(_sem, zero) == KERN_SUCCESS;
}

#elif defined(_WIN32)

inline Semaphore::Semaphore(unsigned initial)
{
	if (!(_sem = CreateSemaphore(NULL, initial, LONG_MAX, NULL))) {
		throw -1;
	}
}

inline Semaphore::~Semaphore()
{
	CloseHandle(_sem);
}

inline void Semaphore::post()
{
	ReleaseSemaphore(_sem, 1, NULL);
}

inline bool Semaphore::wait()
{
	if (WaitForSingleObject(_sem, INFINITE) != WAIT_OBJECT_0) {
		return false;
	}
	return true;
}

inline bool Semaphore::try_wait()
{
	return WaitForSingleObject(_sem, 0) == WAIT_OBJECT_0;
}

#else  /* !defined(__APPLE__) && !defined(_WIN32) */

Semaphore::Semaphore(unsigned initial)
{
    sprintf(fName, "faust_sem_%d_%p", GetPID(), this);
    if ((_sem = sem_open(fName, O_CREAT, 0777, 0)) == (sem_t*)SEM_FAILED) {
        printf("Allocate: can't check in named semaphore name = %s err = %s", fName, strerror(errno));
        throw -1;
    }
}

inline Semaphore::~Semaphore()
{
    sem_unlink(fName);
    sem_close(_sem);
}

inline void Semaphore::post()
{
     sem_post(_sem);
}

inline bool Semaphore::wait()
{
    while (sem_wait(_sem)) {
        if (errno != EINTR) {
            return false;  // We are all doomed
        }
        // Otherwise, interrupted (rare/weird), so try again.
    }

	return true;
}

inline bool Semaphore::try_wait()
{
     return (sem_trywait(_sem) == 0);
}

#endif

#ifdef __APPLE__
//#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#include <MacTypes.h>
#include <libkern/OSAtomic.h>
#endif

static void Yield();

/**
 * Returns the number of clock cycles elapsed since the last reset
 * of the processor
 */
static INLINE UInt64 DSP_rdtsc(void)
{
	union {
		UInt32 i32[2];
		UInt64 i64;
	} count;
	
	__asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
    return count.i64;
}

#if defined(__i386__) || defined(__x86_64__)

#define LOCK "lock ; "

static INLINE void NOP(void)
{
    /*
    #ifndef __APPLE__
	__asm__ __volatile__("nop \n\t");
    #endif
    */
}

static INLINE char CAS1(volatile void* addr, volatile int value, int newvalue)
{
    return __sync_bool_compare_and_swap((int*)addr, value, newvalue);
}

static INLINE int atomic_xadd(volatile int* atomic, int val) 
{ 
     return __sync_add_and_fetch(atomic, val);
} 

#endif

/*
static INLINE int INC_ATOMIC(volatile int* val)
{
    int actual;
    do {
        actual = *val;
    } while (!CAS1(val, actual, actual + 1));
    return actual;
}

static INLINE int DEC_ATOMIC(volatile int* val)
{
    int actual;
    do {
        actual = *val;
    } while (!CAS1(val, actual, actual - 1));
    return actual;
}
*/

static INLINE int INC_ATOMIC(volatile int* val)
{
    return atomic_xadd(val, 1);
}
 
static INLINE int DEC_ATOMIC(volatile int* val)
{
    return atomic_xadd(val, -1);
}
 
// To be used in lock-free queue
struct AtomicCounter 
{
    union {
        struct {
            short fHead;	
            short fTail;	
        } scounter;
        int fValue;
    } info;
    
    INLINE AtomicCounter()
	{
        info.fValue = 0;
    }
      
 	INLINE AtomicCounter& operator=(AtomicCounter& obj)
    {
        info.fValue = obj.info.fValue;
        return *this;
    }
    
	INLINE AtomicCounter& operator=(volatile AtomicCounter& obj)
	{
        info.fValue = obj.info.fValue;
        return *this;
    }
    
};

/* use 512KB stack per thread - the default is way too high to be feasible
 * with mlockall() on many systems */
#define THREAD_STACK 524288

#ifdef __APPLE__

#include <mach/thread_policy.h>
#include <mach/thread_act.h>
#include <mach/mach_time.h>

#define THREAD_SET_PRIORITY         0
#define THREAD_SCHEDULED_PRIORITY   1

static void get_affinity(pthread_t thread)
{
    thread_affinity_policy theTCPolicy;
    mach_msg_type_number_t count = THREAD_AFFINITY_POLICY_COUNT;
    boolean_t get_default = false;
    kern_return_t res = thread_policy_get(pthread_mach_thread_np(thread), THREAD_AFFINITY_POLICY, (thread_policy_t)&theTCPolicy, &count, &get_default);
    if (res == KERN_SUCCESS) {
        //printf("get_affinity = %d\n", theTCPolicy.affinity_tag);
    }
}

static void set_affinity(pthread_t thread, int tag)
{
    thread_affinity_policy theTCPolicy;
    theTCPolicy.affinity_tag = tag;
    kern_return_t res = thread_policy_set(pthread_mach_thread_np(thread), THREAD_AFFINITY_POLICY, (thread_policy_t)&theTCPolicy, THREAD_AFFINITY_POLICY_COUNT);
    if (res == KERN_SUCCESS) {
        //printf("set_affinity = %d\n", theTCPolicy.affinity_tag);
    }
}

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


static double gTimeRatio = 0;
static UInt64 gPeriod = 0;
static UInt64 gComputation = 0;
static UInt64 gConstraint = 0;

/* This should only be called ONCE per process. */
static void InitTime()
{
	mach_timebase_info_data_t info;
	mach_timebase_info(&info);
	gTimeRatio = ((double)info.numer / (double)info.denom) / 1000;
}

UInt64 GetMicroSeconds(void)
{
    return UInt64(mach_absolute_time() * gTimeRatio);
}

void GetRealTime()
{
    if (gPeriod == 0) {
        InitTime();
        GetParams(pthread_self(), &gPeriod, &gComputation, &gConstraint);
    }
}

static void SetRealTime()
{
    SetThreadToPriority(pthread_self(), 96, true, gPeriod, gComputation, gConstraint);
}

static void CancelThread(pthread_t fThread)
{
    mach_port_t machThread = pthread_mach_thread_np(fThread);
    thread_terminate(machThread);
}

static void Yield()
{
    //sched_yield();
}

int get_max_cpu()
{
    int physical_count = 0;
    size_t size = sizeof(physical_count);
    sysctlbyname("hw.physicalcpu", &physical_count, &size, NULL, 0);
    int logical_count = 0;
    sysctlbyname("hw.logicalcpu", &logical_count, &size, NULL, 0);
    return physical_count;
}

#endif

#ifdef __linux__

static int faust_sched_policy = -1;
static struct sched_param faust_rt_param; 

void GetRealTime()
{
    if (faust_sched_policy == -1) {
        memset(&faust_rt_param, 0, sizeof(faust_rt_param));
    	pthread_getschedparam(pthread_self(), &faust_sched_policy, &faust_rt_param);
    }
}

static void SetRealTime()
{
	faust_rt_param.sched_priority--;
    pthread_setschedparam(pthread_self(), faust_sched_policy, &faust_rt_param);
}

static void CancelThread(pthread_t fThread)
{
    pthread_cancel(fThread);
    pthread_join(fThread, NULL);
}

static void Yield()
{
    pthread_yield();
}

// TODO
static UInt64 GetMicroSeconds(void)
{	
    return 0;
}

static void get_affinity(pthread_t thread) {}
static void set_affinity(pthread_t thread, int tag) {}

int get_max_cpu()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

#endif

static INLINE int Range(int min, int max, int val)
{
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    } else {
        return val;
    }
}

#if defined(LLVM_50) || defined(LLVM_40) || defined(LLVM_39) || defined(LLVM_38) || defined(LLVM_37) || defined(LLVM_36) || defined(LLVM_35) || defined(LLVM_34)
    extern "C" void computeThreadExternal(void* dsp, int num_thread) __attribute__((weak_import));
#else
    void computeThreadExternal(void* dsp, int num_thread);
#endif

class DynThreadAdapter {
    
    private:
        
        UInt64 fTiming[KDSPMESURE];
        UInt64 fStart;
        UInt64 fStop;
        int fCounter;
        float fOldMean;
        int fOldfDynamicNumThreads;
        bool fDynAdapt;
        
        INLINE float ComputeMean()
        {
            float mean = 0;
            for (int i = 0; i < KDSPMESURE; i++) {
                mean += float(fTiming[i]);
            }
            mean /= float(KDSPMESURE);
            return mean;
        }
    
    public :
    
        DynThreadAdapter():fCounter(0), fOldMean(1000000000.f), fOldfDynamicNumThreads(1)
        {
            memset(fTiming, 0, sizeof(long long int ) * KDSPMESURE);
            fDynAdapt = getenv("OMP_DYN_THREAD") ? strtol(getenv("OMP_DYN_THREAD"), NULL, 10) : false;
        }
        
        INLINE void StartMeasure()
        {
            if (fDynAdapt) {
                //fStart = DSP_rdtsc();
                fStart = GetMicroSeconds();
            }
        }
         
        INLINE void StopMeasure(int staticthreadnum, int& dynthreadnum)
        {
            if (!fDynAdapt) {
                return;
            }
            
            //fStop = DSP_rdtsc();
            fStop = GetMicroSeconds();
            fCounter = (fCounter + 1) % KDSPMESURE;
            if (fCounter == 0) {
                float mean = ComputeMean();
                // Recompute dynthreadnum is timing différence is sufficient...
                //printf("mean = %f fOldMean = %f\n", mean, fOldMean);
                if (fabs(mean - fOldMean) / fOldMean > MEAN_TRESHOLD) {
                    if (mean > fOldMean) { // Worse...
                        if (fOldfDynamicNumThreads > dynthreadnum) {
                            fOldfDynamicNumThreads = dynthreadnum;
                            dynthreadnum += 1;
                        } else {
                            fOldfDynamicNumThreads = dynthreadnum;
                            dynthreadnum -= 1;
                        }
                     } else { // Better...
                        if (fOldfDynamicNumThreads > dynthreadnum) {
                            fOldfDynamicNumThreads = dynthreadnum;
                            dynthreadnum -= 1;
                        } else {
                            fOldfDynamicNumThreads = dynthreadnum;
                            dynthreadnum += 1;
                        }
                    }
                    fOldMean = mean;
                    dynthreadnum = Range(1, staticthreadnum, dynthreadnum);
                    //printf("dynthreadnum = %d\n", dynthreadnum);
                }
            }
            // And keep computation time
            fTiming[fCounter] = fStop - fStart; 
        }
};

#define Value(e) (e).info.fValue

#define Head(e) (e).info.scounter.fHead
#define IncHead(e) (e).info.scounter.fHead++
#define DecHead(e) (e).info.scounter.fHead--

#define Tail(e) (e).info.scounter.fTail
#define IncTail(e) (e).info.scounter.fTail++
#define DecTail(e) (e).info.scounter.fTail--

class TaskQueue 
{
    private:
    
        int* fTaskList;
        int fTaskQueueSize;
        volatile AtomicCounter fCounter;
        
        UInt64 fStealingStart;
        UInt64 fMaxStealing;
     
    public:
  
        INLINE TaskQueue()
        {}
        
        INLINE void Init(int task_queue_size)
        {
            fTaskQueueSize = task_queue_size;
            fTaskList = new int[fTaskQueueSize];
            for (int i = 0; i < fTaskQueueSize; i++) {
                fTaskList[i] = -1;
            }
            fStealingStart = 0;
             
            int clock_per_microsec = (getenv("CLOCKSPERSEC") 
                ? strtoll(getenv("CLOCKSPERSEC"), NULL, 10) 
                : DEFAULT_CLOCKS_PER_SEC) / 1000000;
                
            fMaxStealing = getenv("OMP_STEALING_DUR") 
                ? strtoll(getenv("OMP_STEALING_DUR"), NULL, 10) * clock_per_microsec 
                : MAX_STEAL_DUR * clock_per_microsec;
        }
        
        INLINE ~TaskQueue()
        {
            delete[] fTaskList;
        }
         
        INLINE void InitOne()
        {
            for (int i = 0; i < fTaskQueueSize; i++) {
                fTaskList[i] = -1;
            }
            fCounter.info.fValue = 0;
            fStealingStart = 0;
        }
        
        INLINE void PushHead(int item)
        {
            fTaskList[Head(fCounter)] = item;
            IncHead(fCounter);
        }
        
        INLINE int PopHead()
        {
            AtomicCounter old_val;
            AtomicCounter new_val;
            
            do {
                old_val = fCounter;
                new_val = old_val;
                if (Head(old_val) == Tail(old_val)) {
                    return WORK_STEALING_INDEX;
                } else {
                    DecHead(new_val);
                }
            } while (!CAS1(&fCounter, Value(old_val), Value(new_val)));
            
            return fTaskList[Head(old_val) - 1];
        }
        
        INLINE int PopTail()
        {   
            AtomicCounter old_val;
            AtomicCounter new_val;

            do {
                old_val = fCounter;
                new_val = old_val;
                if (Head(old_val) == Tail(old_val)) {
                    return WORK_STEALING_INDEX;
                } else {
                    IncTail(new_val);
                }
            } while (!CAS1(&fCounter, Value(old_val), Value(new_val)));

            return fTaskList[Tail(old_val)];
        }

		INLINE void MeasureStealingDur()
		{
            // Takes first timestamp
            if (fStealingStart == 0) {
                fStealingStart = DSP_rdtsc();
            } else if ((DSP_rdtsc() - fStealingStart) > fMaxStealing) {
                Yield();
            }
		}

		INLINE void ResetStealingDur()
		{
            fStealingStart = 0;
		}
           
        static INLINE int GetNextTask(TaskQueue* task_queue_list, int cur_thread, int num_threads)
        {
            int tasknum;
            for (int i = 0; i < num_threads; i++) {
                if ((tasknum = task_queue_list[i].PopTail()) != WORK_STEALING_INDEX) {
                #ifdef __linux__
                    //if (cur_thread != MASTER_THREAD)
                        task_queue_list[cur_thread].ResetStealingDur();
                #endif
                    return tasknum;    // Task is found
                }
            }
            //NOP();
        #ifdef __linux__
			//if (cur_thread != MASTER_THREAD)
                task_queue_list[cur_thread].MeasureStealingDur();
        #endif
            return WORK_STEALING_INDEX;    // Otherwise will try "workstealing" again next cycle...
        }
         
        INLINE void InitTaskList(int task_list_size, int* task_list, int thread_num, int cur_thread)
        {
            int task_slice = task_list_size / thread_num;
            int task_slice_rest = task_list_size % thread_num;
            
            // cur_thread takes it's slice of tasks
            for (int index = 0; index < task_slice; index++) {
                PushHead(task_list[cur_thread * task_slice + index]);
            }
            
            // Thread 0 takes remaining ready tasks 
            if (cur_thread == 0) {
                for (int index = 0; index < task_slice_rest; index++) {
                    PushHead(task_list[thread_num * task_slice + index]);
                }
            }
        }
        
        static INLINE void InitAll(TaskQueue* task_queue_list, int num_threads)
        {
            for (int i = 0; i < num_threads; i++) {
                task_queue_list[i].InitOne();
            }
        }
     
};

class TaskGraph 
{
    private:
    
        volatile int* fTaskList;
        int fTaskQueueSize;
        
    public:
    
        TaskGraph(int task_queue_size)
        {
            fTaskQueueSize = task_queue_size;
            fTaskList = new int[fTaskQueueSize];
            for (int i = 0; i < fTaskQueueSize; i++) {
                fTaskList[i] = 0;
            } 
        }
        
        INLINE ~TaskGraph()
        {
            delete[] fTaskList;
        }

        INLINE void InitTask(int task, int val)
        {
            fTaskList[task] = val;
        }
        
        void Display()
        {
            for (int i = 0; i < fTaskQueueSize; i++) {
                printf("Task = %d activation = %d\n", i, fTaskList[i]);
            } 
        }
          
        INLINE void ActivateOutputTask(TaskQueue& queue, int task, int* tasknum)
        {
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                if (*tasknum == WORK_STEALING_INDEX) {
                    *tasknum = task;
                } else {
                    queue.PushHead(task);
                }
            }    
        }
          
        INLINE void ActivateOutputTask(TaskQueue& queue, int task)
        {   
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                queue.PushHead(task);
            }
        }
         
        INLINE void ActivateOneOutputTask(TaskQueue& queue, int task, int* tasknum)
        {   
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                *tasknum = task;
            } else {
                *tasknum = queue.PopHead(); 
            }
        }
        
        INLINE void GetReadyTask(TaskQueue& queue, int* tasknum)
        {
            if (*tasknum == WORK_STEALING_INDEX) {
                *tasknum = queue.PopHead();
            }
        }
        
};

class DSPThread;

class DSPThreadPool {
    
    private:
    
        DSPThread** fThreadPool;
        int fThreadCount; 
        volatile int fCurThreadCount;
      
    public:
        
        DSPThreadPool(int thread_pool_size);
        ~DSPThreadPool();
    
        void StartAll(int num_thread, bool realtime, void* dsp);
       
        void StopAll();
      
        void SignalAll(int num_thread);
        
        void SignalOne()
        {
            DEC_ATOMIC(&fCurThreadCount);
        }

        bool IsFinished()
        {
            return (fCurThreadCount == 0);
        }

};

class DSPThread {

    private:
    
        pthread_t fThread;
        DSPThreadPool* fThreadPool;
        Semaphore fSemaphore;
        bool fRealTime;
        int fNumThread;
        void* fDSP;
        
        static void* ThreadHandler(void* arg)
        {
            DSPThread* thread = static_cast<DSPThread*>(arg);
            
            AVOIDDENORMALS;
            get_affinity(thread->fThread);

            // One "dummy" cycle to setup thread
            if (thread->fRealTime) {
                thread->Run();
                SetRealTime();
            }
                      
            while (true) {
                thread->Run();
            }
            
            return NULL;
        }
    
    public: 
    
        DSPThread(int num_thread, DSPThreadPool* pool, void* dsp)
            :fThreadPool(pool), fSemaphore(0), fRealTime(false), fNumThread(num_thread), fDSP(dsp) 
        {}

        virtual ~DSPThread()
        {}
        
        void Run()
        {
            fSemaphore.wait();
            computeThreadExternal(fDSP, fNumThread + 1);
            //fThreadPool->SignalOne();
        }
                
        void Signal()
        {
            fSemaphore.post();
        }
        
        int Start(bool realtime)
        {
            pthread_attr_t attributes;
            struct sched_param rt_param;
            pthread_attr_init(&attributes);
            
            int priority = 60; // TODO
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
            
            if ((res = pthread_create(&fThread, &attributes, ThreadHandler, this))) {
                printf("Cannot create thread res = %d err = %s\n", res, strerror(errno));
                return -1;
            }
            
            // Set affinity
            set_affinity(fThread, fNumThread + 1);

            pthread_attr_destroy(&attributes);
            return 0;
        }
        
        void Stop()
        {
            CancelThread(fThread);
        }

};

DSPThreadPool::DSPThreadPool(int thread_pool_size)
{
    fThreadPool = new DSPThread*[thread_pool_size];
    for (int i = 0; i < thread_pool_size; i++) {
        fThreadPool[i] = NULL;
    }
    fThreadCount = 0;
    fCurThreadCount = 0;
}

DSPThreadPool::~DSPThreadPool()
{
    StopAll();
    
    for (int i = 0; i < fThreadCount; i++) {
        delete(fThreadPool[i]);
        fThreadPool[i] = NULL;
    }
    
    fThreadCount = 0;
    delete[] fThreadPool;
}

void DSPThreadPool::StartAll(int num_thread, bool realtime, void* dsp)
{
    if (fThreadCount == 0) {  // Protection for multiple call...  (like LADSPA plug-ins in Ardour)
        for (int i = 0; i < num_thread; i++) {
            fThreadPool[i] = new DSPThread(i, this, dsp);
            fThreadPool[i]->Start(realtime);
            fThreadCount++;
        }
    }
}

void DSPThreadPool::StopAll()
{
    for (int i = 0; i < fThreadCount; i++) {
        fThreadPool[i]->Stop();
    }
}

void DSPThreadPool::SignalAll(int num_thread)
{
    fCurThreadCount = num_thread;
     
    for (int i = 0; i < num_thread; i++) {  // Important : use local num here...
        fThreadPool[i]->Signal();
    }
}

/*
    Public C++ interface
*/

class WorkStealingScheduler {

    private:
    
        DSPThreadPool* fThreadPool;
        TaskQueue* fTaskQueueList;
        TaskGraph* fTaskGraph;
        
        DynThreadAdapter fDynThreadAdapter;
        
        int fDynamicNumThreads;
        int fStaticNumThreads;
        
        int* fReadyTaskList;
        int fReadyTaskListSize;
        int fReadyTaskListIndex;
    
    public:
    
        WorkStealingScheduler(int task_queue_size, int init_task_list_size)
        {
            fStaticNumThreads = get_max_cpu();
            fDynamicNumThreads = getenv("OMP_NUM_THREADS") ? atoi(getenv("OMP_NUM_THREADS")) : fStaticNumThreads;
            
            fThreadPool = new DSPThreadPool(fStaticNumThreads);
            fTaskGraph = new TaskGraph(task_queue_size);
            fTaskQueueList = new TaskQueue[fStaticNumThreads];
            for (int i = 0; i < fStaticNumThreads; i++) {
                fTaskQueueList[i].Init(task_queue_size);
            }
            
            fReadyTaskListSize = init_task_list_size;
            fReadyTaskList = new int[fReadyTaskListSize];
            fReadyTaskListIndex = 0;
        }
        
        ~WorkStealingScheduler()
        {
            delete fThreadPool;
            delete fTaskGraph;
            delete[] fTaskQueueList;
            delete[] fReadyTaskList;
        }
        
        void AddReadyTask(int task_num)
        {
            fReadyTaskList[fReadyTaskListIndex++] = task_num;
        }
        
        void StartAll(void* dsp)
        {
            fThreadPool->StartAll(fStaticNumThreads - 1, true, dsp);
        }
        
        void StopAll()
        {
            fThreadPool->StopAll();
        }
          
        void SignalAll()
        {
            GetRealTime();
            fDynThreadAdapter.StartMeasure();
            fThreadPool->SignalAll(fDynamicNumThreads - 1);
        }
        
        void SyncAll()
        {
            //while (!fThreadPool->IsFinished()) {}
            fDynThreadAdapter.StopMeasure(fStaticNumThreads, fDynamicNumThreads);
        }
        
        void PushHead(int cur_thread, int task_num)
        {
            fTaskQueueList[cur_thread].PushHead(task_num);
        }
          
        int GetNextTask(int cur_thread)
        {
            return TaskQueue::GetNextTask(fTaskQueueList, cur_thread, fDynamicNumThreads);
        }
        
        void InitTask(int task_num, int count)
        {
            fTaskGraph->InitTask(task_num, count);
        }
        
        void ActivateOutputTask(int cur_thread, int task, int* task_num)
        {
            fTaskGraph->ActivateOutputTask(fTaskQueueList[cur_thread], task, task_num);
        }
        
        void ActivateOutputTask(int cur_thread, int task)
        {
            fTaskGraph->ActivateOutputTask(fTaskQueueList[cur_thread], task);
        }
        
        void ActivateOneOutputTask(int cur_thread, int task, int* task_num)
        {
            fTaskGraph->ActivateOneOutputTask(fTaskQueueList[cur_thread], task, task_num);
        }
                
        void GetReadyTask(int cur_thread, int* task_num)
        {
            fTaskGraph->GetReadyTask(fTaskQueueList[cur_thread], task_num);
        }
        
        void InitTaskList(int cur_thread)
        {
            TaskQueue::InitAll(fTaskQueueList, fDynamicNumThreads);
            if (cur_thread == -1) {
                // Dispatch on all WSQ
                for (int i = 0; i < fDynamicNumThreads; i++) {
                    fTaskQueueList[i].InitTaskList(fReadyTaskListSize, fReadyTaskList, fDynamicNumThreads, i);
                }
            } else {
                // Otherwise push all ready tasks in cur_thread WSQ
                for (int i = 0; i < fReadyTaskListSize; i++) {
                    fTaskQueueList[cur_thread].PushHead(fReadyTaskList[i]);
                }
            }
        }

};

/*
C scheduler interface
*/
    
#ifdef _WIN32
#define EXPORT __declspec(dllexport) __attribute__((always_inline))
#else
#define EXPORT inline __attribute__ ((visibility("default"))) __attribute__((always_inline))
#endif

EXPORT void* createScheduler(int task_queue_size, int init_task_list_size)
{
    return new WorkStealingScheduler(task_queue_size, init_task_list_size);
}

EXPORT void deleteScheduler(void* scheduler)
{   
    delete(static_cast<WorkStealingScheduler*>(scheduler));
}

EXPORT void startAll(void* scheduler, void* dsp)
{
    static_cast<WorkStealingScheduler*>(scheduler)->StartAll(dsp);
}

EXPORT void stopAll(void* scheduler)
{
    static_cast<WorkStealingScheduler*>(scheduler)->StopAll();
}

EXPORT void signalAll(void* scheduler)
{
    static_cast<WorkStealingScheduler*>(scheduler)->SignalAll();
}

EXPORT void syncAll(void* scheduler)
{
    static_cast<WorkStealingScheduler*>(scheduler)->SyncAll();
}

EXPORT void pushHead(void* scheduler, int cur_thread, int task_num)
{
    static_cast<WorkStealingScheduler*>(scheduler)->PushHead(cur_thread, task_num);
}

EXPORT int getNextTask(void* scheduler, int cur_thread)
{
    return static_cast<WorkStealingScheduler*>(scheduler)->GetNextTask(cur_thread);
}

EXPORT void initTask(void* scheduler, int task_num, int count)
{
    static_cast<WorkStealingScheduler*>(scheduler)->InitTask(task_num, count);
}

EXPORT void activateOutputTask1(void* scheduler, int cur_thread, int task, int* task_num)
{
    static_cast<WorkStealingScheduler*>(scheduler)->ActivateOutputTask(cur_thread, task, task_num);
}

EXPORT void activateOutputTask2(void* scheduler, int cur_thread, int task)
{
    static_cast<WorkStealingScheduler*>(scheduler)->ActivateOutputTask(cur_thread, task);
}

EXPORT void activateOneOutputTask(void* scheduler, int cur_thread, int task, int* task_num)
{
    static_cast<WorkStealingScheduler*>(scheduler)->ActivateOneOutputTask(cur_thread, task, task_num);
}
        
EXPORT void getReadyTask(void* scheduler, int cur_thread, int* task_num)
{
    static_cast<WorkStealingScheduler*>(scheduler)->GetReadyTask(cur_thread, task_num);
}

EXPORT void initTaskList(void* scheduler, int cur_thread)
{
    static_cast<WorkStealingScheduler*>(scheduler)->InitTaskList(cur_thread);
}

EXPORT void addReadyTask(void* scheduler, int task_num)
{
    static_cast<WorkStealingScheduler*>(scheduler)->AddReadyTask(task_num);
}

#ifdef __cplusplus
}
#endif
