/*
* Copyright (c) 2015, University of Southern California
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of University of Southern California, nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY UNIVERSITY OF SOUTHERN CALIFORNIA 
* ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
* IN NO EVENT SHALL UNIVERSITY OF SOUTHERN CALIFORNIA BE 
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
  Multicore library.
  Code authors: Jernej Barbic, Yili Zhao, Bohan Wang
*/

#ifndef _MULTICORE_H_
#define _MULTICORE_H_

#include <queue>
#include <pthread.h>

#ifndef WIN32
  #include <semaphore.h>
#else
  #include <windows.h>
#endif

class Multicore
{
public:
  Multicore(int maxNumThreads, int persistentThreads=0); // valid thread numbers are 0 <= thread < maxNumThreads; if persistentThreads == 1, threads will be launched once in constructor, reused, and only turned off in the destructor
  ~Multicore();

  typedef void* (*threadTask) (void*);
  void SetThreadTask(int thread, threadTask task);
  void SetThreadTaskParameter(int thread, void * taskParameter);
  threadTask GetThreadTask(int thread) { return tasks[thread]; }
  void * GetThreadParameter(int thread) { return taskParameters[thread]; }

  // split an integer range [indexLo, indexHi) into "numThreads" buckets (each of which can then be assigned to a separate thread)
  // bucketLo and bucketHi must be pre-allocated arrays of integers of length "numThreads"
  static void SplitWorkLoad(int indexLo, int indexHi, int numThreads, int * bucketLo, int * bucketHi);

  // === API 1 : all threads launched at once, and wait for barrier at end ===
  void LaunchThreads(int threadLo, int threadHi); // launch threadLo <= thread < threadHi; this routine will block until all threads are done

  // === API 2 : launch threads individually ===
  void LaunchThread(int thread); 
  void WaitForAvailableThread(int * availableThread); // returns as soon as one thread is available, "availableThread" (output) will contain the available thread
  void WaitForCompletionOfAllThreads();

protected:
  int maxNumThreads;
  threadTask * tasks;
  void ** taskParameters;

  int persistentThreads;
  pthread_mutex_t persistentThreadMutex;
  int persistentThreadExitSignal;
  int persistentThreadLo;
  int * persistentThreadSignal;

  pthread_t * tid;
  static const int numAvailableThreadsSemaphoreIndex = 1;
  static const int numCompletedThreadsSemaphoreIndex = 2;
  int numCompletedThreads;
  int numAssignedThreads;

  typedef struct
  {
    int thread;
    Multicore * multicore;
  } Multicore_LaunchThreadHelperData;
  Multicore_LaunchThreadHelperData * helperData;

  friend void * Multicore_LaunchThreadHelper(void * data);
  friend void * Multicore_PersistentThreadWorker(void * data);

  pthread_mutex_t mutex;
  std::queue<int> availableThreads;
  std::queue<int> completedThreads;
  void ReportCompletedTask(int thread);

  #ifndef WIN32
    sem_t * numAvailableThreadsSemaphore;
    sem_t * numCompletedThreadsSemaphore;
    sem_t ** SelectSemaphore(int semaphoreIndex);
  #else
    HANDLE numAvailableThreadsSemaphore;
    HANDLE numCompletedThreadsSemaphore;
    HANDLE * SelectSemaphore(int semaphoreIndex);
    void ErrorExit(LPTSTR lpszFunction);
  #endif

  int InitSemaphore(int semaphoreIndex);
  int SemPost(int semaphoreIndex);
  int SemWait(int semaphoreIndex);
  int SemClose(int semaphoreIndex);
};

#endif

