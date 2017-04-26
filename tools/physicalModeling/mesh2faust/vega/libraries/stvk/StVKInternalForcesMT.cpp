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
#include "StVKInternalForcesMT.h"

StVKInternalForcesMT::StVKInternalForcesMT(VolumetricMesh * volumetricMesh, StVKElementABCD * precomputedABCDIntegrals, bool addGravity_, double g_, int numThreads_): StVKInternalForces(volumetricMesh, precomputedABCDIntegrals, addGravity_, g_), numThreads(numThreads_) 
{
  internalForceBuffer = (double*) malloc (sizeof(double) * numThreads * 3 * volumetricMesh->getNumVertices());
  energyBuffer = (double*) malloc (sizeof(double) * numThreads);
  energyAuxBuffer = (double*) malloc (sizeof(double) * numThreads * 3 * volumetricMesh->getNumVertices());

  // split the workload
  int numElements = volumetricMesh->getNumElements();
  startElement = (int*) malloc (sizeof(int) * numThreads);
  endElement = (int*) malloc (sizeof(int) * numThreads);

  int remainder = numElements % numThreads;
  // the first 'remainder' nodes will process one element more
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
      
  printf("Total elements: %d \n",numElements);
  printf("Num threads: %d \n",numThreads);
  printf("Canonical job size: %d \n",jobSize);      
  printf("Num threads with job size augmented by one element: %d \n",remainder);
}

StVKInternalForcesMT::~StVKInternalForcesMT() 
{
  free(startElement);
  free(endElement);
  free(energyBuffer);
  free(energyAuxBuffer);
  free(internalForceBuffer);
}

int StVKInternalForcesMT::GetStartElement(int rank)
{
  return startElement[rank];
}

int StVKInternalForcesMT::GetEndElement(int rank)
{
  return endElement[rank];
}

struct StVKInternalForcesMT_threadArg
{
  StVKInternalForcesMT * stVKInternalForcesMT;
  const double * vertexDisplacements;
  double * targetBuffer;
  int rank;
  int computationTarget; // 0 = force, 1 = energy
  double * auxBuffer; // for energy computations
};

void * StVKInternalForcesMT_WorkerThread(void * arg)
{
  struct StVKInternalForcesMT_threadArg * threadArgp = (struct StVKInternalForcesMT_threadArg*) arg;
  StVKInternalForcesMT * stVKInternalForcesMT = threadArgp->stVKInternalForcesMT;
  const double * vertexDisplacements = threadArgp->vertexDisplacements;
  double * targetBuffer = threadArgp->targetBuffer;
  int rank = threadArgp->rank;
  int startElement = stVKInternalForcesMT->GetStartElement(rank);
  int endElement = stVKInternalForcesMT->GetEndElement(rank);

  if (threadArgp->computationTarget == 0)
  {
    stVKInternalForcesMT->AddLinearTermsContribution(vertexDisplacements, targetBuffer, startElement, endElement);
    stVKInternalForcesMT->AddQuadraticTermsContribution(vertexDisplacements, targetBuffer, startElement, endElement);
    stVKInternalForcesMT->AddCubicTermsContribution(vertexDisplacements, targetBuffer, startElement, endElement);
  }

  if (threadArgp->computationTarget == 1)
  {
    *targetBuffer = stVKInternalForcesMT->ComputeEnergyContribution(vertexDisplacements, startElement, endElement, threadArgp->auxBuffer);
  }

  return NULL;
}

void StVKInternalForcesMT::ComputeForces(const double * vertexDisplacements, double * internalForces)
{
  //PerformanceCounter forceCounter;
  Compute(0, vertexDisplacements, internalForces);

  //forceCounter.StopCounter();
  //printf("Internal forces: %G\n", forceCounter.GetElapsedTime());
}

double StVKInternalForcesMT::ComputeEnergy(const double * vertexDisplacements)
{
  double result;
  Compute(1, vertexDisplacements, &result);
  return result;
}

void StVKInternalForcesMT::Compute(int computationTarget, const double * vertexDisplacements, double * target)
{
  int numVertices3 = 3 * volumetricMesh->getNumVertices();
  struct StVKInternalForcesMT_threadArg * threadArgv = (struct StVKInternalForcesMT_threadArg*) malloc (sizeof(struct StVKInternalForcesMT_threadArg) * numThreads);

  pthread_t * tid = (pthread_t*) malloc (sizeof(pthread_t) * numThreads);

  for(int i=0; i<numThreads; i++)
  {
    threadArgv[i].stVKInternalForcesMT = this;
    threadArgv[i].vertexDisplacements = vertexDisplacements;
    if (computationTarget == 0)
      threadArgv[i].targetBuffer = &internalForceBuffer[i * numVertices3];
    if (computationTarget == 1)
    {
      threadArgv[i].targetBuffer = &energyBuffer[i];
      threadArgv[i].auxBuffer = &energyAuxBuffer[i * numVertices3];
    }
    threadArgv[i].rank = i;
    threadArgv[i].computationTarget = computationTarget;
  }
    
  if (computationTarget == 0)
    memset(internalForceBuffer, 0, sizeof(double) * numVertices3 * numThreads);
  if (computationTarget == 1)
    memset(energyBuffer, 0, sizeof(double) * numThreads);

  for(int i=0; i<numThreads; i++)
  {
    if (pthread_create(&tid[i], NULL, StVKInternalForcesMT_WorkerThread, &threadArgv[i]) != 0)
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

  // assemble
  if (computationTarget == 0)
  {
    memset(target, 0, sizeof(double) * numVertices3);
    for(int i=0; i<numThreads; i++)
    {
      double * source = &internalForceBuffer[i * numVertices3];
      for(int j=0; j<numVertices3; j++)
        target[j] += source[j];
    }

    if (addGravity)
    {
      int n = volumetricMesh->getNumVertices();
      for(int i=0; i<3*n; i++)
      {
        target[i] -= gravityForce[i];
      }
    }
  }

  if (computationTarget == 1)
  {
    *target = 0;
    for(int i=0; i<numThreads; i++)
      *target += energyBuffer[i];
  }
}

