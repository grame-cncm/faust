/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Hongyi Xu, Doug L. James                     *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Zumberge Research and Innovation Fund at USC                 *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

/*
  Multithreaded computation of the distance field. Main computational routines.
*/

#ifdef COMPUTE_SIGNED_FIELD
  #ifdef COMPUTE_FLOOD_FIELD
    #define COMPUTEFIELDMT_CLASSNAME DistanceFieldMT
    #define COMPUTEFIELDMT_STRUCTNAME DistanceFieldMT_signed_flood_struct
    #define COMPUTEFIELDMT_WORKERTHREADNAME DistanceFieldMT_signed_flood_WorkerThread
    #define ZIGZAGROUTINE DistanceField::ZigZagFloodFillSigned
  #else
    #ifdef COMPUTE_CLOSEST_POINT
      #define COMPUTEFIELDMT_CLASSNAME ClosestPointFieldMT
      #define COMPUTEFIELDMT_STRUCTNAME ClosestPointFieldMT_signed_struct
      #define COMPUTEFIELDMT_WORKERTHREADNAME ClosestPointFieldMT_signed_WorkerThread
      #define ZIGZAGROUTINE ClosestPointField::ZigZagSigned
    #else
      #define COMPUTEFIELDMT_CLASSNAME DistanceFieldMT
      #define COMPUTEFIELDMT_STRUCTNAME DistanceFieldMT_signed_struct
      #define COMPUTEFIELDMT_WORKERTHREADNAME DistanceFieldMT_signed_WorkerThread
      #define ZIGZAGROUTINE DistanceField::ZigZagSigned
    #endif
  #endif
#else
  #ifdef COMPUTE_CLOSEST_POINT
    #define COMPUTEFIELDMT_CLASSNAME ClosestPointFieldMT
    #define COMPUTEFIELDMT_STRUCTNAME ClosestPointFieldMT_unsigned_struct
    #define COMPUTEFIELDMT_WORKERTHREADNAME ClosestPointFieldMT_unsigned_WorkerThread
    #define ZIGZAGROUTINE ClosestPointField::ZigZagUnsigned
  #else
    #define COMPUTEFIELDMT_CLASSNAME DistanceFieldMT
    #define COMPUTEFIELDMT_STRUCTNAME DistanceFieldMT_unsigned_struct
    #define COMPUTEFIELDMT_WORKERTHREADNAME DistanceFieldFieldMT_unsigned_WorkerThread
    #define ZIGZAGROUTINE DistanceField::ZigZagUnsigned
  #endif
#endif

//#define USE_MULTICORE_LIBRARY
#ifdef USE_MULTICORE_LIBRARY
  #include "multicore.h"
#endif

struct COMPUTEFIELDMT_STRUCTNAME
{
  COMPUTEFIELDMT_CLASSNAME * object;
  void * objMeshOctree;
  void * meshGraph;
  int rank;
  int startSlice;
  int endSlice;
};

void * COMPUTEFIELDMT_WORKERTHREADNAME(void * arg)
{  
  struct COMPUTEFIELDMT_STRUCTNAME * threadArgp = (struct COMPUTEFIELDMT_STRUCTNAME*) arg;
  COMPUTEFIELDMT_CLASSNAME * object = threadArgp->object;
  void * objMeshOctree = threadArgp->objMeshOctree;
  void * meshGraph = threadArgp->meshGraph;
  int rank = threadArgp->rank;  
  //int startSlice = object->GetStartSlice(rank);
  //int endSlice = object->GetEndSlice(rank);
  int startSlice = threadArgp->startSlice;
  int endSlice = threadArgp->endSlice;
  //printf("rank: %d startSlice: %d endSlice: %d\n", rank, startSlice, endSlice);

  int asterisk=0;
  if (rank == 0)
    asterisk = 1;

  object->ZIGZAGROUTINE(objMeshOctree, meshGraph, startSlice, endSlice-1, asterisk);

  return NULL;
}

#ifdef COMPUTE_SIGNED_FIELD
  #ifdef COMPUTE_CLOSEST_POINT
    int ClosestPointFieldMT::ZigZagSigned(void * objMeshOctree_, void * meshGraph_)
  #else
    #ifdef COMPUTE_FLOOD_FIELD
      int DistanceFieldMT::ZigZagFloodFillSigned(void * objMeshOctree_, void * meshGraph_)
    #else
      int DistanceFieldMT::ZigZagSigned(void * objMeshOctree_, void * meshGraph_)
    #endif
  #endif
#else
  #ifdef COMPUTE_CLOSEST_POINT
    int ClosestPointFieldMT::ZigZagUnsigned(void * objMeshOctree_, void * meshGraph_)
  #else
    int DistanceFieldMT::ZigZagUnsigned(void * objMeshOctree_, void * meshGraph_)
  #endif
#endif
{
  Setup();

  struct COMPUTEFIELDMT_STRUCTNAME * threadArgv = (struct COMPUTEFIELDMT_STRUCTNAME*) malloc (sizeof(struct COMPUTEFIELDMT_STRUCTNAME) * numThreads);

  for(int i=0; i<numThreads; i++)
  {
    threadArgv[i].object = this;
    threadArgv[i].objMeshOctree = objMeshOctree_;
    threadArgv[i].meshGraph = meshGraph_;
    threadArgv[i].rank = i;
    threadArgv[i].startSlice = GetStartSlice(i);
    threadArgv[i].endSlice = GetEndSlice(i);
  }
   
  #ifdef USE_MULTICORE_LIBRARY 
    Multicore * multicore = new Multicore(numThreads);
    for(int i=0; i<numThreads; i++)
    {
      multicore->SetThreadTask(i, COMPUTEFIELDMT_WORKERTHREADNAME);    
      multicore->SetThreadTaskParameter(i, &threadArgv[i]);
    }

    //assigns equal z-range to every thread (weakness: can be non-even computational load)
    //multicore->LaunchThreads(0, numThreads);

    int zSlice = zMin;
    while (zSlice <= zMax)
    {
      int availableThread;
      multicore->WaitForAvailableThread(&availableThread);
      threadArgv[availableThread].startSlice = zSlice;
      threadArgv[availableThread].endSlice = zSlice + 1;
      multicore->LaunchThread(availableThread);
      zSlice++;
    }

    multicore->WaitForCompletionOfAllThreads();

    delete(multicore);
  #else
    printf("Launching %d threads...\n", numThreads);
    pthread_t * tid = (pthread_t*) malloc (sizeof(pthread_t) * numThreads);
    for(int i=0; i<numThreads; i++)
    {
      if (pthread_create(&tid[i], NULL, COMPUTEFIELDMT_WORKERTHREADNAME, &threadArgv[i]) != 0)
      {
        printf("Error: unable to launch thread %d.\n", i);
        exit(1);
      }
    }
  
    for(int i=0; i<numThreads; i++)
    {
      if (pthread_join(tid[i], NULL) != 0)
      {
        printf("Error: unable to join thread %d.\n", i);
        free(threadArgv);
        free(tid);
        free(startSlice);
        free(endSlice);
        return 1;
      }
    }
    free(tid);
  #endif

  free(threadArgv);
  free(startSlice);
  free(endSlice);

  return 0;
}

#undef ZIGZAGROUTINE
#undef COMPUTEFIELDMT_CLASSNAME
#undef COMPUTEFIELDMT_STRUCTNAME
#undef COMPUTEFIELDMT_WORKERTHREADNAME

