
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

// Globals

#define THREAD_SIZE 32
#define QUEUE_SIZE 4096

#define WORK_STEALING_INDEX 0
#define LAST_TASK_INDEX 1

#ifdef __ICC
#define INLINE __forceinline
#else
#define INLINE inline
#endif

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

#ifdef __linux__

// handle 32/64 bits int size issues
#ifdef __x86_64__
#define UInt32	unsigned int
#define UInt64	unsigned long int
#else
#define UInt32	unsigned int
#define UInt64	unsigned long long int
#endif

#endif

#ifdef __APPLE__
#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#include <libkern/OSAtomic.h>
#endif

class DSPThreadPool;

extern DSPThreadPool* gThreadPool;
extern int gClientCount;
extern UInt64 gMaxStealing;
    
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
#ifdef __APPLE__
    return __sync_bool_compare_and_swap((int*)addr, value, newvalue);
#else
    register char ret;
    __asm__ __volatile__ ("# CAS \n\t"
						  LOCK "cmpxchg %2, (%1) \n\t"
						  "sete %0               \n\t"
						  : "=a" (ret)
						  : "c" (addr), "d" (newvalue), "a" (value)
                          : "memory");
    return ret;
#endif
}

static INLINE int atomic_xadd(volatile int* atomic, int val) 
{ 
#ifdef __APPLE__
    // Returns new value
    return __sync_add_and_fetch(atomic, val);
#else
    register int ret;
    __asm__ __volatile__ ("# atomic_xadd \n\t"
                          LOCK "xaddl %0,%1 \n\t"
                          : "=r" (ret), "=m" (*atomic) 
                          : "0" (val), "m" (*atomic));
    return ret;
#endif
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
        }
        scounter;
        int fValue;
    }info;
    
	INLINE AtomicCounter()
	{
        info.fValue = 0;
    }
     
 	INLINE  AtomicCounter& operator=(AtomicCounter& obj)
    {
        info.fValue = obj.info.fValue;
        return *this;
    }
    
	INLINE  AtomicCounter& operator=(volatile AtomicCounter& obj)
	{
        info.fValue = obj.info.fValue;
        return *this;
    }
    
};

int get_max_cpu()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

static int GetPID()
{
#ifdef WIN32
    return  _getpid();
#else
    return getpid();
#endif
}

#define Value(e) (e).info.fValue

#define Head(e) (e).info.scounter.fHead
#define IncHead(e) (e).info.scounter.fHead++
#define DecHead(e) (e).info.scounter.fHead--

#define Tail(e) (e).info.scounter.fTail
#define IncTail(e) (e).info.scounter.fTail++
#define DecTail(e) (e).info.scounter.fTail--

#define MASTER_THREAD 0

#define MAX_STEAL_DUR 50                    // in usec
#define DEFAULT_CLOCKSPERSEC 2500000000     // in cycles (2,5 Ghz)
#define THREAD_POOL_SIZE 16
#define JACK_SCHED_POLICY SCHED_FIFO

/* use 512KB stack per thread - the default is way too high to be feasible
 * with mlockall() on many systems */
#define THREAD_STACK 524288

#ifdef __APPLE__

#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
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

#ifdef __cplusplus
extern "C"
{
#endif

void getRealTime()
{
    if (period == 0) {
        GetParams(pthread_self(), &period, &computation, &constraint);
    }
}

#ifdef __cplusplus
}
#endif

static void setRealTime()
{
    SetThreadToPriority(pthread_self(), 96, true, period, computation, constraint);
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

#endif

#ifdef __linux__

static int faust_sched_policy = -1;
static struct sched_param faust_rt_param; 

#ifdef __cplusplus
extern "C"
{
#endif

void getRealTime()
{
    if (faust_sched_policy == -1) {
        memset(&faust_rt_param, 0, sizeof(faust_rt_param));
    	pthread_getschedparam(pthread_self(), &faust_sched_policy, &faust_rt_param);
    }
}

#ifdef __cplusplus
}
#endif

static void setRealTime()
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

#endif

#define KDSPMESURE 50

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

#if defined(LLVM_31) || defined(LLVM_30) || defined(LLVM_29)
    typedef void (* computeThreadExternalFun) (void* dsp, int cur_thread);
    extern computeThreadExternalFun gComputeThreadExternal;
#else
    void computeThreadExternal(void* dsp, int num_thread);
#endif

class Runnable {
    
    private:
        
        UInt64 fTiming[KDSPMESURE];
        UInt64 fStart;
        UInt64 fStop;
        int fCounter;
        float fOldMean;
        int fOldfDynamicNumThreads;
        bool fDynAdapt;
        
        virtual void computeThread(int cur_thread) = 0;
    
    public :
    
        Runnable():fCounter(0), fOldMean(1000000000.f), fOldfDynamicNumThreads(1)
        {
            memset(fTiming, 0, sizeof(long long int ) * KDSPMESURE);
            fDynAdapt = getenv("OMP_DYN_THREAD") ? strtol(getenv("OMP_DYN_THREAD"), NULL, 10) : false;
        }
        
        INLINE float ComputeMean()
        {
            float mean = 0;
            for (int i = 0; i < KDSPMESURE; i++) {
                mean += float(fTiming[i]);
            }
            mean /= float(KDSPMESURE);
            return mean;
        }
        
        INLINE void StartMeasure()
        {
            if (fDynAdapt) {
                fStart = DSP_rdtsc();
            }
        }
         
        INLINE void StopMeasure(int staticthreadnum, int& dynthreadnum)
        {
            if (!fDynAdapt) {
                return;
            }
            
            fStop = DSP_rdtsc();
            fCounter = (fCounter + 1) % KDSPMESURE;
            if (fCounter == 0) {
                float mean = ComputeMean();
                if (fabs(mean - fOldMean) > 5000) {
                    if (mean > fOldMean) { // Worse...
                        //printf("Worse %f %f\n", mean, fOldMean);
                        if (fOldfDynamicNumThreads > dynthreadnum) {
                            fOldfDynamicNumThreads = dynthreadnum;
                            dynthreadnum += 1;
                        } else {
                            fOldfDynamicNumThreads = dynthreadnum;
                            dynthreadnum -= 1;
                        }
                     } else { // Better...
                        //printf("Better %f %f\n", mean, fOldMean);
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
                    //printf("dynthreadnum %d\n", dynthreadnum);
                }
            }
            fTiming[fCounter] = fStop - fStart; 
        }
};

class TaskQueue 
{
    private:
    
        int fTaskList[QUEUE_SIZE];
        volatile AtomicCounter fCounter;
        UInt64 fStealingStart;
     
    public:
  
        INLINE TaskQueue(int cur_thread)
        {
            for (int i = 0; i < QUEUE_SIZE; i++) {
                fTaskList[i] = -1;
            }
            fStealingStart = 0;
        }
         
        INLINE void InitOne()
        {
            for (int i = 0; i < QUEUE_SIZE; i++) {
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
            // Takes first timetamp
            if (fStealingStart == 0) {
                fStealingStart = DSP_rdtsc();
            } else if ((DSP_rdtsc() - fStealingStart) > gMaxStealing) {
                Yield();
            }
		}

		INLINE void ResetStealingDur()
		{
            fStealingStart = 0;
		}
        
        static INLINE int GetNextTask(void* taskqueuelist, int thread, int num_threads)
        {
            int tasknum;
            TaskQueue** task_queue_list = static_cast<TaskQueue**>(taskqueuelist);
            
            for (int i = 0; i < num_threads; i++) {
                if ((i != thread) && task_queue_list[i] && (tasknum = task_queue_list[i]->PopTail()) != WORK_STEALING_INDEX) {
                #ifdef __linux__
                    //if (thread != MASTER_THREAD)
                        task_queue_list[thread]->ResetStealingDur();
                #endif
                    return tasknum;    // Task is found
                }
            }
            NOP();
        #ifdef __linux__
			//if (thread != MASTER_THREAD)
                task_queue_list[thread]->MeasureStealingDur();
        #endif
            return WORK_STEALING_INDEX;    // Otherwise will try "workstealing" again next cycle...
        }
        
        INLINE void InitTaskList(int task_list_size, int* task_list, int thread_num, int cur_thread, int& tasknum)
        {
            int task_slice = task_list_size / thread_num;
            int task_slice_rest = task_list_size % thread_num;

            if (task_slice == 0) {
                // Each thread directly executes one task
                tasknum = task_list[cur_thread];
                // Thread 0 takes remaining ready tasks 
                if (cur_thread == 0) { 
                    for (int index = 0; index < task_slice_rest - thread_num; index++) {
                        PushHead(task_list[task_slice_rest + index]);
                    }
                }
            } else {
                // Each thread takes a part of ready tasks
                int index;
                for (index = 0; index < task_slice - 1; index++) {
                    PushHead(task_list[cur_thread * task_slice + index]);
                }
                // Each thread directly executes one task 
                tasknum = task_list[cur_thread * task_slice + index];
                // Thread 0 takes remaining ready tasks 
                if (cur_thread == 0) {
                    for (index = 0; index < task_slice_rest; index++) {
                        PushHead(task_list[thread_num * task_slice + index]);
                    }
                }
            }
        }
        
        static INLINE void InitAll(void* taskqueuelist, int num_threads)
        {
            TaskQueue** task_queue_list = static_cast<TaskQueue**>(taskqueuelist);
            for (int i = 0; i < num_threads; i++) {
                task_queue_list[i]->InitOne();
            }
        }
     
};

class TaskGraph 
{
    private:
    
        volatile int fTaskList[QUEUE_SIZE];
        
    public:
    
        TaskGraph()
        {
            for (int i = 0; i < QUEUE_SIZE; i++) {
                fTaskList[i] = 0;
            } 
        }

        INLINE void InitTask(int task, int val)
        {
            fTaskList[task] = val;
        }
        
        void Display()
        {
            for (int i = 0; i < QUEUE_SIZE; i++) {
                printf("Task = %d activation = %d\n", i, fTaskList[i]);
            } 
        }
          
        INLINE void ActivateOutputTask(TaskQueue& queue, int task, int& tasknum)
        {
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                if (tasknum == WORK_STEALING_INDEX) {
                    tasknum = task;
                } else {
                    queue.PushHead(task);
                }
            }    
        }
        
        INLINE void ActivateOutputTask(TaskQueue* queue, int task, int* tasknum)
        {
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                if (*tasknum == WORK_STEALING_INDEX) {
                    *tasknum = task;
                } else {
                    queue->PushHead(task);
                }
            }    
        }
         
        INLINE void ActivateOutputTask(TaskQueue& queue, int task)
        {
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                queue.PushHead(task);
            }
        }
        
        INLINE void ActivateOutputTask(TaskQueue* queue, int task)
        {
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                queue->PushHead(task);
            }
        }
        
        INLINE void ActivateOneOutputTask(TaskQueue& queue, int task, int& tasknum)
        {
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                tasknum = task;
            } else {
                tasknum = queue.PopHead(); 
            }
        }
        
        INLINE void ActivateOneOutputTask(TaskQueue* queue, int task, int* tasknum)
        {
            if (DEC_ATOMIC(&fTaskList[task]) == 0) {
                *tasknum = task;
            } else {
                *tasknum = queue->PopHead(); 
            }
        }
        
        INLINE void GetReadyTask(TaskQueue& queue, int& tasknum)
        {
            if (tasknum == WORK_STEALING_INDEX) {
                tasknum = queue.PopHead();
            }
        }
        
        INLINE void GetReadyTask(TaskQueue* queue, int* tasknum)
        {
            if (*tasknum == WORK_STEALING_INDEX) {
                *tasknum = queue->PopHead();
            }
        }
 
};

class DSPThread {

    private:
    
        pthread_t fThread;
        void* fDSP;
        sem_t* fSemaphore;
        char fName[128];
        bool fRealTime;
        int fNumThread;
        
        static void* ThreadHandler(void* arg)
        {
            DSPThread* thread = static_cast<DSPThread*>(arg);
            
            AVOIDDENORMALS;
            
            // One "dummy" cycle to setup thread
            if (thread->fRealTime) {
                thread->Run();
                setRealTime();
            }
                      
            while (true) {
                thread->Run();
            }
            
            return NULL;
        }
    
    public: 
    
        DSPThread(int num_thread, void* dsp)
        {
            fNumThread = num_thread;
            fDSP = dsp;
            fRealTime = false;
            
            sprintf(fName, "faust_sem_%d_%p", GetPID(), this);
            
            if ((fSemaphore = sem_open(fName, O_CREAT, 0777, 0)) == (sem_t*)SEM_FAILED) {
                printf("Allocate: can't check in named semaphore name = %s err = %s", fName, strerror(errno));
            }
        }

        virtual ~DSPThread()
        {
            sem_unlink(fName);
            sem_close(fSemaphore);
        }
        
        void Run()
        {
            while (sem_wait(fSemaphore) != 0) {}
        #if defined(LLVM_31) || defined(LLVM_30) || defined(LLVM_29)
            gComputeThreadExternal(fDSP, fNumThread + 1);
        #else
            computeThreadExternal(fDSP, fNumThread + 1);
        #endif
        }
                
        void Signal()
        {
            sem_post(fSemaphore);
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

            pthread_attr_destroy(&attributes);
            return 0;
        }
        
        void Stop()
        {
            CancelThread(fThread);
        }

};

class DSPThreadPool {
    
    private:
    
        DSPThread* fThreadPool[THREAD_POOL_SIZE];
        int fThreadCount; 
      
    public:
        
        DSPThreadPool()
        {
            for (int i = 0; i < THREAD_POOL_SIZE; i++) {
                fThreadPool[i] = NULL;
            }
            fThreadCount = 0;
        }

        ~DSPThreadPool()
        {
            StopAll();
            
            for (int i = 0; i < fThreadCount; i++) {
                delete(fThreadPool[i]);
                fThreadPool[i] = NULL;
            }
            
            fThreadCount = 0;
         }

        void StartAll(int num_thread, bool realtime, void* dsp)
        {
            if (fThreadCount == 0) {  // Protection for multiple call...  (like LADSPA plug-ins in Ardour)
                for (int i = 0; i < num_thread; i++) {
                    fThreadPool[i] = new DSPThread(i, dsp);
                    fThreadPool[i]->Start(realtime);
                    fThreadCount++;
                }
            }
        }

        void StopAll()
        {
            for (int i = 0; i < fThreadCount; i++) {
                fThreadPool[i]->Stop();
            }
        }

        void SignalAll(int num_thread)
        {
            for (int i = 0; i < num_thread; i++) {  // Important : use local num here...
                fThreadPool[i]->Signal();
            }
        }

        static DSPThreadPool* Init()
        {
            if (gClientCount++ == 0 && !gThreadPool) {
                gThreadPool = new DSPThreadPool();
            }
            return gThreadPool;
        }

        static void Destroy()
        {
            if (--gClientCount == 0 && gThreadPool) {
                delete gThreadPool;
                gThreadPool = NULL;
            }
        }
    
};

#ifndef PLUG_IN

// Globals
DSPThreadPool* gThreadPool = 0;
int gClientCount = 0;

int clock_per_microsec = (getenv("CLOCKSPERSEC") 
                ? strtoll(getenv("CLOCKSPERSEC"), NULL, 10) 
                : DEFAULT_CLOCKSPERSEC) / 1000000;
                
UInt64  gMaxStealing = getenv("OMP_STEALING_DUR") 
                ? strtoll(getenv("OMP_STEALING_DUR"), NULL, 10) * clock_per_microsec 
                : MAX_STEAL_DUR * clock_per_microsec;

#endif

#ifdef __cplusplus
extern "C"
{
#endif

// Thread pool 

void* createThreadPool()
{
    return (void*)new DSPThreadPool();
}
void deleteThreadPool(void* pool)
{
    delete (DSPThreadPool*)pool;
}

void startAll(void* pool, int num_threads, void* dsp)
{
    ((DSPThreadPool*)pool)->StartAll(num_threads, true, dsp);
}

void stopAll(void* pool)
{
    ((DSPThreadPool*)pool)->StopAll();
}

void signalAll(void* pool, int num_threads)
{
    ((DSPThreadPool*)pool)->SignalAll(num_threads);
}

// Task queue 

void initAllTaskQueue(void* task_queue_list, int num_threads)
{
    TaskQueue::InitAll(task_queue_list, num_threads);
}

void* createTaskQueue(int cur_thread)
{
    return (void*)new TaskQueue(cur_thread);
}

void deleteTaskQueue(void* queue)
{
    delete (TaskQueue*)queue;
}

void initOneTaskQueue(void* queue)
{
    ((TaskQueue*)queue)->InitOne();
}

void pushHead(void* queue, int task)
{
    ((TaskQueue*)queue)->PushHead(task);
}

int popHead(void* queue)
{
    return ((TaskQueue*)queue)->PopHead();
}

int popTail(void* queue)
{
    return ((TaskQueue*)queue)->PopTail();
}

int getNextTask(void* task_queue_list, int cur_thread, int dynamic_threads)
{
    return TaskQueue::GetNextTask(task_queue_list, cur_thread, dynamic_threads);
}

// Task graph 

void* createTaskGraph()
{
    return (void*)new TaskGraph();
}

void deleteTaskGraph(void* graph)
{
    delete (TaskGraph*)graph;
}

void initTask(void* graph, int task, int count)
{
    ((TaskGraph*)graph)->InitTask(task, count);
}

void activateOutputTask1(void* graph, void* queue, int task, int* tasknum)
{
    ((TaskGraph*)graph)->ActivateOutputTask((TaskQueue*)queue, task, tasknum);
}

void activateOutputTask2(void* graph, void* queue, int task)
{
    ((TaskGraph*)graph)->ActivateOutputTask((TaskQueue*)queue, task);
}

void activateOneOutputTask(void* graph, void* queue, int task, int* tasknum)
{
    ((TaskGraph*)graph)->ActivateOneOutputTask((TaskQueue*)queue, task, tasknum);
}

void getReadyTask(void* graph, void* queue, int* tasknum)
{
    ((TaskGraph*)graph)->GetReadyTask((TaskQueue*)queue, tasknum);
}

int getStaticThreadsNum()
{
    return get_max_cpu();
}
int getDynamicThreadsNum()
{
    return getenv("OMP_NUM_THREADS") ? atoi(getenv("OMP_NUM_THREADS")) : get_max_cpu();
}

#ifdef __cplusplus
}
#endif
