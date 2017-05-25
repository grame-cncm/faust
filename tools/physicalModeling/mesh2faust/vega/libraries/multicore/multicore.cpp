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

#include <stdio.h>
#include <stdlib.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <fcntl.h>
#if defined(_WIN32) || defined(WIN32)
  #include <windows.h>
  #include <strsafe.h>
  #include <process.h>
  #pragma warning(disable : 4995)
#else
  #include <unistd.h> 
#endif
#include "multicore.h"
using namespace std;

void * Multicore_PersistentThreadWorker(void * data)
{
  Multicore::Multicore_LaunchThreadHelperData * mdata = (Multicore::Multicore_LaunchThreadHelperData*) data;
  int thread = mdata->thread;
  
  while (1)
  {
    if (mdata->multicore->persistentThreadSignal[thread] == 1)
    {
      int threadLo = mdata->multicore->persistentThreadLo;
      mdata->multicore->tasks[threadLo + thread](mdata->multicore->taskParameters[threadLo + thread]);
      //printf("Job %d completed.\n", thread);

      pthread_mutex_lock(&mdata->multicore->persistentThreadMutex);
      mdata->multicore->persistentThreadSignal[thread] = 2;
      pthread_mutex_unlock(&mdata->multicore->persistentThreadMutex);
    }

    if (mdata->multicore->persistentThreadExitSignal != 0)
      break;
  }

  //mdata->multicore->persistentThreadExitSignal = 2;
  printf("persistent worker exited.\n");

  return NULL;
}

Multicore::Multicore(int maxNumThreads_, int persistentThreads_): maxNumThreads(maxNumThreads_), persistentThreads(persistentThreads_)
{
  tasks = (threadTask*) malloc (sizeof(threadTask) * maxNumThreads);
  taskParameters = (void**) malloc (sizeof(void*) * maxNumThreads);
  tid = (pthread_t*) malloc (sizeof(pthread_t) * maxNumThreads);
  helperData = (Multicore_LaunchThreadHelperData*) malloc (sizeof(Multicore_LaunchThreadHelperData) * maxNumThreads);

  if (InitSemaphore(numAvailableThreadsSemaphoreIndex) == -1)
  {
    printf("Error: failed to initialize semaphore.\n");
    throw 1;
  }

  if (InitSemaphore(numAvailableThreadsSemaphoreIndex) == -1)
  {
    printf("Error: failed to initialize semaphore.\n");
    throw 1;
  }

  // initialize the pool of available resources
  for(int i=0; i<maxNumThreads; i++)
  {
    availableThreads.push(i);
    SemPost(numAvailableThreadsSemaphoreIndex);
  }

  //for(int i=0; i<maxNumThreads; i++)
  //{
    //sem_wait(numAvailableThreadsSemaphore);
  //}

  //int val1 = sem_post(numAvailableThreadsSemaphore);
  //int val2 = sem_wait(numAvailableThreadsSemaphore);
  //int val3 = sem_wait(numAvailableThreadsSemaphore);
  //printf("%d %d %d\n", val1, val2, val3);
  //exit(1);

  numCompletedThreads = 0;
  numAssignedThreads = 0;

  if (pthread_mutex_init(&mutex, NULL) != 0)
  {
    printf("Error: pthread_mutex_init failed.\n");
    throw 1;
  }

  if (persistentThreads)
  {
    if (pthread_mutex_init(&persistentThreadMutex, NULL) != 0)
    {
      printf("Error: pthread_mutex_init failed.\n");
      throw 1;
    }
    persistentThreadExitSignal = 0;
    persistentThreadSignal = (int*) calloc (maxNumThreads, sizeof(int));
    for(int i=0; i<maxNumThreads; i++)
    {
      helperData[i].thread = i;
      helperData[i].multicore = this;
      if (pthread_create(&tid[i], NULL, Multicore_PersistentThreadWorker, &helperData[i]) != 0)
      {
        printf("Error: unable to launch persistent thread %d.\n", i);
        throw 2;
      }
    }
  }
}

Multicore::~Multicore()
{
  if (persistentThreads)
  {
    persistentThreadExitSignal = 1;
    //while (persistentThreadExitSignal == 1)
    //{
      //printf("waiting for persistentThreadExitSignal to flip to 2.\n");
    //}
    //free(persistentThreadSignal);

    int code;
    if ((code = pthread_mutex_destroy(&persistentThreadMutex)) != 0) 
    {
      //printf("Warning: pthread_mutex_destroy failed.\n");
      //char errorMessage[80];
      //strerror_r(code, errorMessage, sizeof(errorMessage));
      //printf("%s\n", errorMessage);
    }
  }

  SemClose(numAvailableThreadsSemaphoreIndex);
  SemClose(numCompletedThreadsSemaphoreIndex);

  int code;
  if ((code = pthread_mutex_destroy(&mutex)) != 0) 
  {
    //printf("Warning: pthread_mutex_destroy failed.\n");
    //char errorMessage[80];
    //strerror_r(code, errorMessage, sizeof(errorMessage));
    //printf("%s\n", errorMessage);
  }
  
  free(helperData);
  free(tid);
  free(taskParameters);
  free(tasks);

  // must stop any persistent threads
  // (unimplemented)
}

void Multicore::SetThreadTask(int thread, threadTask task)
{
  tasks[thread] = task;
}

void Multicore::SetThreadTaskParameter(int thread, void * taskParameter)
{
  taskParameters[thread] = taskParameter;
}

void Multicore::LaunchThreads(int threadLo, int threadHi)
{
  int numThreads = threadHi - threadLo;
  if ((threadLo < 0) || (threadHi > maxNumThreads))
  {
    printf("Error: incorrect threading range specification.\n");
    return;
  }

  if (numThreads == 0)
    return;

  if (persistentThreads)
  {
    persistentThreadLo = threadLo + 1;

    pthread_mutex_lock(&persistentThreadMutex);
    for(int i=0; i<numThreads-1; i++)
      persistentThreadSignal[i] = 1;
    pthread_mutex_unlock(&persistentThreadMutex);

    tasks[threadLo](taskParameters[threadLo]);

    for(int i=0; i<numThreads-1; i++)
    {
      while (1)
      {
        //printf("waiting on %d...\n", i);
        int exitCode = 0;
        pthread_mutex_lock(&persistentThreadMutex);
        if (persistentThreadSignal[i] == 2)
          exitCode = 1;
        pthread_mutex_unlock(&persistentThreadMutex);
        if (exitCode)
          break;
      } 
    }
    //printf("waiting done...\n");

    pthread_mutex_lock(&persistentThreadMutex);
    for(int i=0; i<numThreads-1; i++)
      persistentThreadSignal[i] = 0;
    pthread_mutex_unlock(&persistentThreadMutex);
  }
  else
  {
    for(int i=0; i<numThreads; i++)
    {
      if (pthread_create(&tid[i], NULL, tasks[threadLo+i], taskParameters[threadLo+i]) != 0)
      {
        printf("Error: unable to launch thread %d.\n", threadLo + i);
        return;
      }
    }

    for(int i=0; i<numThreads; i++)
    {
      if (pthread_join(tid[i], NULL) != 0)
      {
        printf("Error: unable to join thread %d.\n", threadLo + i);
        return;
      }
    }
  }
}

void * Multicore_LaunchThreadHelper(void * data)
{
  Multicore::Multicore_LaunchThreadHelperData * mdata = (Multicore::Multicore_LaunchThreadHelperData*) data;
  int thread = mdata->thread;
  void * result = mdata->multicore->GetThreadTask(thread)(mdata->multicore->GetThreadParameter(thread));

  mdata->multicore->ReportCompletedTask(thread);

  return result;
}

void Multicore::ReportCompletedTask(int thread)
{
  pthread_mutex_lock(&mutex);
  availableThreads.push(thread);
  pthread_mutex_unlock(&mutex);

  SemPost(numAvailableThreadsSemaphoreIndex);
  SemPost(numCompletedThreadsSemaphoreIndex);
}

void Multicore::LaunchThread(int thread) 
{
  pthread_mutex_lock(&mutex);
  numAssignedThreads++;
  pthread_mutex_unlock(&mutex);

  helperData[thread].thread = thread;
  helperData[thread].multicore = this;

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  if (pthread_create(&tid[thread], &attr, Multicore_LaunchThreadHelper, &helperData[thread]) != 0)
  {
    printf("Error: unable to launch thread %d.\n", thread);
    return;
  }

  //pthread_detach(tid[thread]);
}

void Multicore::WaitForAvailableThread(int * availableThread)
{
  SemWait(numAvailableThreadsSemaphoreIndex);

  pthread_mutex_lock(&mutex);

  //printf("Inside WaitForAvailableThread.. #availableThreads: %d\n", (int)availableThreads.size());

  if (availableThreads.size() == 0)
  {
    printf("Error: empty queue inside the critical section.\n");
    return;
  }

  *availableThread = availableThreads.front();
  availableThreads.pop();

  pthread_mutex_unlock(&mutex);
}

void Multicore::WaitForCompletionOfAllThreads()
{
  while (1)
  {
    pthread_mutex_lock(&mutex);
    if (numCompletedThreads >= numAssignedThreads)
    {
      pthread_mutex_unlock(&mutex);
      break;
    }
    pthread_mutex_unlock(&mutex);
    SemWait(numCompletedThreadsSemaphoreIndex);
    numCompletedThreads++;
  }

  numCompletedThreads = 0;
  numAssignedThreads = 0;
}

void Multicore::SplitWorkLoad(int indexLo, int indexHi, int numThreads, int * bucketLo, int * bucketHi)
{
  int n = indexHi - indexLo;

  int remainder = n % numThreads;
  // the first 'remainder' nodes will process one element more
  int jobSize = n / numThreads;

  for(int rank=0; rank < numThreads; rank++)
  {
    if (rank < remainder)
    {
      bucketLo[rank] = rank * (jobSize+1);
      bucketHi[rank] = (rank+1) * (jobSize+1);
    } 
    else
    {
      bucketLo[rank] = remainder * (jobSize+1) + (rank-remainder) * jobSize;
      bucketHi[rank] = remainder * (jobSize+1) + ((rank-remainder)+1) * jobSize;
    }
  }

  for(int rank=0; rank < numThreads; rank++)
  {
    bucketLo[rank] += indexLo;
    bucketHi[rank] += indexLo;
  }
}

#ifndef WIN32
// non-windows code
sem_t ** Multicore::SelectSemaphore(int semaphoreIndex)
{
  sem_t ** targetSemaphore = NULL;
  switch(semaphoreIndex)
  {
    case numAvailableThreadsSemaphoreIndex:
      targetSemaphore = &numAvailableThreadsSemaphore;
    break;

    case numCompletedThreadsSemaphoreIndex:
      targetSemaphore = &numCompletedThreadsSemaphore;
    break;

    default:
      printf("Error: invalid semaphore index %d.\n", semaphoreIndex);
    break;
  }

  return targetSemaphore;
}
#else
HANDLE * Multicore::SelectSemaphore(int semaphoreIndex)
{
  HANDLE * targetSemaphore = NULL;
  switch(semaphoreIndex)
  {
  case numAvailableThreadsSemaphoreIndex:
    targetSemaphore = &numAvailableThreadsSemaphore;
    break;

  case numCompletedThreadsSemaphoreIndex:
    targetSemaphore = &numCompletedThreadsSemaphore;
    break;

  default:
    printf("Error: invalid semaphore index %d.\n", semaphoreIndex);
    break;
  }

  return targetSemaphore;
}
#endif

int Multicore::InitSemaphore(int semaphoreIndex)
{
#ifndef WIN32

  // non-windows code
  char semaphoreName[60];
  pid_t processID = getpid();
  sprintf(semaphoreName, "/multicoreSem%d_%d", semaphoreIndex, processID);

  if (sem_unlink(semaphoreName) != 0)
  {
    //printf("Error: cannot unlink %s.\n", semaphoreName);
    //exit(1);
  }

  sem_t ** targetSemaphore = SelectSemaphore(semaphoreIndex); 

  #define FILE_MODE (S_IRWXU | S_IRWXG | S_IRWXO)
    *targetSemaphore = sem_open(semaphoreName, O_CREAT | O_EXCL, FILE_MODE, 0);
  #undef FILE_MODE

  if (*targetSemaphore == SEM_FAILED)
  {
    printf("Error: sem_init (%s) failed.\n", semaphoreName);
    return -1;  // FAILED
  }

  return 0; // SUCCEEDED
#else
  // windows code
  char semaphoreName[60];
  int  processID = _getpid();
  sprintf_s(semaphoreName, "/multicoreSem%d_%d", semaphoreIndex, processID);

  // create semaphore 
  HANDLE * targetSemaphore = SelectSemaphore(semaphoreIndex);
  // try to open it first
  *targetSemaphore = OpenSemaphoreA(SEMAPHORE_MODIFY_STATE | SYNCHRONIZE, false, semaphoreName);

  // The commented sentence allows the semaphore to be inherited by the child process. 
  // HOWEVER, the semaphore MUST be specified as "inheritable" when it is created.
  //*targetSemaphore = OpenSemaphoreA(SEMAPHORE_MODIFY_STATE | SYNCHRONIZE, true, semaphoreName);  

  // if it cannot be opened, try to create a new one
  if (*targetSemaphore == NULL)
  {
    // Initialize a security descriptor.  
    /*PSECURITY_DESCRIPTOR pSD = NULL;
    pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH); 
    if (pSD == NULL)
    {
      printf("Error in allocating PSECURITY_DESCRIPTOR.\n");
      exit(0);
    } 
    SECURITY_ATTRIBUTES sa;
    // Initialize a security attributes structure.
    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = pSD;
    sa.bInheritHandle = true;  // the semaphore could be inherited by the child process
    *targetSemaphore = CreateSemaphoreA(sa, 0, maxNumThreads, semaphoreName);  */

    switch(semaphoreIndex)
    {
      case numAvailableThreadsSemaphoreIndex:
        *targetSemaphore = CreateSemaphoreA(NULL, 0, maxNumThreads, semaphoreName); 
      break;

      case numCompletedThreadsSemaphoreIndex:
        *targetSemaphore = CreateSemaphoreA(NULL, 0, INT_MAX, semaphoreName); 
      break;
    }

    // In the above function call, the 1st parameter indicates that this semaphore CANNOT be inherited by its child process.
    // If you want it to be inherited, please use the commented piece of code.
  }

  // If it cannot be opened or created, the function returns a "Failed" signal.
  if (*targetSemaphore == NULL)
  {
    printf("Error: sem_init (%s) failed.\n", semaphoreName);
    ErrorExit(TEXT("sem_init"));
    return -1; // FAILED
  }
  return 0; // SUCCEEDED

#endif
}

int Multicore::SemPost(int semaphoreIndex)
{
#ifndef WIN32

  // non-windows code
  sem_t ** targetSemaphore = SelectSemaphore(semaphoreIndex);      
  if (sem_post(*targetSemaphore) != 0)
  {
    printf("Error: sem post %d failed.\n", semaphoreIndex);
    return 1;
  }
  return 0;

#else

  // windows code
  HANDLE * targetSemaphore = SelectSemaphore(semaphoreIndex); 
  if (!ReleaseSemaphore(*targetSemaphore, 1, NULL))
  {
    printf("Error: sem_post %d failed.\n", semaphoreIndex);
    ErrorExit(TEXT("sem_post"));
    return 1;
  }
  return 0;

#endif
}

int Multicore::SemWait(int semaphoreIndex)
{
#ifndef WIN32

  // non-windows code
  sem_t ** targetSemaphore = SelectSemaphore(semaphoreIndex);      
  if (sem_wait(*targetSemaphore) != 0)
  {
    printf("Error: sem wait %d failed.\n", semaphoreIndex);
    return 1;
  }
  return 0;

#else

  // windows code
  HANDLE * targetSemaphore = SelectSemaphore(semaphoreIndex);
  if (WaitForSingleObject(*targetSemaphore, INFINITE) == WAIT_FAILED)
  {
    printf("Error: sem_wait %d failed.\n", semaphoreIndex);
    ErrorExit(TEXT("sem_wait"));
    return 1;
  }
  return 0;

#endif
}

int Multicore::SemClose(int semaphoreIndex)
{
#ifndef WIN32

  // non-windows code
  sem_t ** targetSemaphore = SelectSemaphore(semaphoreIndex);      
  if (sem_close(*targetSemaphore) != 0)
  {
    printf("Error: sem close %d failed.\n", semaphoreIndex);
    return 1;
  }
  return 0;

#else

  // windows code
  HANDLE * targetSemaphore = SelectSemaphore(semaphoreIndex);
  if (!CloseHandle(*targetSemaphore))
  {
    printf("Error: sem_close %d failed.\n", semaphoreIndex);
    ErrorExit(TEXT("sem_close"));
    return 1;
  }
  return 0;
#endif
}

#ifdef WIN32
void Multicore::ErrorExit(LPTSTR lpszFunction) 
{ 
  // Retrieve the system error message for the last-error code

  LPVOID lpMsgBuf;
  LPVOID lpDisplayBuf;
  DWORD dw = GetLastError(); 

  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    dw,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR) &lpMsgBuf,
    0, NULL );

  // Display the error message and exit the process

  lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
    (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
  StringCchPrintf((LPTSTR)lpDisplayBuf, 
    LocalSize(lpDisplayBuf) / sizeof(TCHAR),
    TEXT("%s failed with error %d: %s"), 
    lpszFunction, dw, lpMsgBuf); 
  MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

  LocalFree(lpMsgBuf);
  LocalFree(lpDisplayBuf);
  ExitProcess(dw); 
}
#endif

