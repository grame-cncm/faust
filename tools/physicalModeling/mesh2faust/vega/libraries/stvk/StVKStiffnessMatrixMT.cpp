/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "StVK" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Fun Shing Sin, Daniel Schroeder,             *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
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

#include <pthread.h>
#include "StVKStiffnessMatrixMT.h"

StVKStiffnessMatrixMT::StVKStiffnessMatrixMT(StVKInternalForces *  stVKInternalForces, int numThreads_): StVKStiffnessMatrix(stVKInternalForces), numThreads(numThreads_) 
{
  SparseMatrix * stiffnessMatrixSkeleton;
  GetStiffnessMatrixTopology(&stiffnessMatrixSkeleton);

  // generate skeleton matrices
  sparseMatrixBuffer = (SparseMatrix**) malloc (sizeof(SparseMatrix*) * numThreads);
  for(int i=0; i<numThreads; i++)
    sparseMatrixBuffer[i] = new SparseMatrix(*stiffnessMatrixSkeleton);

  // split the workload
  int numElements = volumetricMesh->getNumElements();
  startElement = (int*) malloc (sizeof(int) * numThreads);
  endElement = (int*) malloc (sizeof(int) * numThreads);

  int remainder = numElements % numThreads;
  // the first 'remainder' nodes will process one elements more
  int jobSize = numElements / numThreads;

  for(int rank=0; rank < numThreads; rank++)
  {
    if (rank < remainder)
    {
      startElement[rank] = rank * (jobSize+1);
      endElement[rank] = (rank+1) * (jobSize+1);
    }
    else
    {
      startElement[rank] = remainder * (jobSize+1) + (rank-remainder) * jobSize;
      endElement[rank] = remainder * (jobSize+1) + ((rank-remainder)+1) * jobSize;
    }
  }

  delete(stiffnessMatrixSkeleton);

  printf("Total elements: %d \n",numElements);
  printf("Num threads: %d \n",numThreads);
  printf("Canonical job size: %d \n",jobSize);
  printf("Num threads with job size augmented by one elements: %d \n",remainder);
}

StVKStiffnessMatrixMT::~StVKStiffnessMatrixMT() 
{
  free(startElement);
  free(endElement);
  for(int i=0; i<numThreads; i++)
    delete(sparseMatrixBuffer[i]);
  free(sparseMatrixBuffer);
}

int StVKStiffnessMatrixMT::GetStartElement(int rank)
{
  return startElement[rank];
}

int StVKStiffnessMatrixMT::GetEndElement(int rank)
{
  return endElement[rank];
}

struct StVKStiffnessMatrixMT_threadArg
{
  StVKStiffnessMatrixMT * stVKStiffnessMatrixMT;
  const double * vertexDisplacements;
  SparseMatrix * targetBuffer;
  int rank;
};

void * StVKStiffnessMatrixMT_WorkerThread(void * arg)
{
  struct StVKStiffnessMatrixMT_threadArg * threadArgp = (struct StVKStiffnessMatrixMT_threadArg*) arg;
  StVKStiffnessMatrixMT * stVKStiffnessMatrixMT = threadArgp->stVKStiffnessMatrixMT;
  const double * vertexDisplacements = threadArgp->vertexDisplacements;
  SparseMatrix * targetBuffer = threadArgp->targetBuffer;
  int rank = threadArgp->rank;
  int startElement = stVKStiffnessMatrixMT->GetStartElement(rank);
  int endElement = stVKStiffnessMatrixMT->GetEndElement(rank);

  stVKStiffnessMatrixMT->AddLinearTermsContribution(vertexDisplacements, targetBuffer, startElement, endElement);
  stVKStiffnessMatrixMT->AddQuadraticTermsContribution(vertexDisplacements, targetBuffer, startElement, endElement);
  stVKStiffnessMatrixMT->AddCubicTermsContribution(vertexDisplacements, targetBuffer, startElement, endElement);

  return NULL;
}

void StVKStiffnessMatrixMT::ComputeStiffnessMatrix(const double * vertexDisplacements, SparseMatrix * sparseMatrix)
{
  //PerformanceCounter stiffnessCounter;
  // launch the threads
  struct StVKStiffnessMatrixMT_threadArg * threadArgv = (struct StVKStiffnessMatrixMT_threadArg*) malloc (sizeof(struct StVKStiffnessMatrixMT_threadArg) * numThreads);

  pthread_t * tid = (pthread_t*) malloc (sizeof(pthread_t) * numThreads);

  for(int i=0; i<numThreads; i++)
  {
    threadArgv[i].stVKStiffnessMatrixMT = this;
    threadArgv[i].vertexDisplacements = vertexDisplacements;
    threadArgv[i].targetBuffer = sparseMatrixBuffer[i];
    threadArgv[i].rank = i;
    sparseMatrixBuffer[i]->ResetToZero();
  }

  for(int i=0; i<numThreads; i++)
  {
    if (pthread_create(&tid[i], NULL, StVKStiffnessMatrixMT_WorkerThread, &threadArgv[i]) != 0)
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
      exit(1);
    }
  }

  free(threadArgv);
  free(tid);

  // assemble results
  sparseMatrix->ResetToZero();
  for(int i=0; i<numThreads; i++)
    *sparseMatrix += *(sparseMatrixBuffer[i]);

  //stiffnessCounter.StopCounter();
  //printf("Stiffness matrix: %G\n", stiffnessCounter.GetElapsedTime());
}

