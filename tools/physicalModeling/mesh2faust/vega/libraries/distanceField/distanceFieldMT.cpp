/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Hongyi Xu, Yijing Li                     *
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
  Multithreaded computation of the distance field.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include <pthread.h>

#include "distanceFieldMT.h"


DistanceFieldMT::DistanceFieldMT(int numThreads_) : DistanceField(), numThreads(numThreads_) 
{
}

DistanceFieldMT::DistanceFieldMT(int resolutionX_, int resolutionY_, int resolutionZ_, int numThreads_): DistanceField(resolutionX_, resolutionY_, resolutionZ_), numThreads(numThreads_)
{
}

void DistanceFieldMT::Setup()
{
  // split the workload
  startSlice = (int*) malloc (sizeof(int) * numThreads);
  endSlice = (int*) malloc (sizeof(int) * numThreads);

  int totalSlices = (zMax - zMin + 1);

  int remainder = totalSlices % numThreads;
  // the first 'remainder' nodes will process one element more
  int jobSize = totalSlices / numThreads;

  for(int rank=0; rank < numThreads; rank++)
  {
    if (rank < remainder)
    {
      startSlice[rank] = zMin + rank * (jobSize+1);
      endSlice[rank] = zMin + (rank+1) * (jobSize+1);
    }
    else
    {
      startSlice[rank] = zMin + remainder * (jobSize+1) + (rank-remainder) * jobSize;
      endSlice[rank] = zMin + remainder * (jobSize+1) + ((rank-remainder)+1) * jobSize;
    }
  }

  printf("Total slices: %d \n", totalSlices);
  printf("Num threads: %d \n", numThreads);
  printf("Canonical job size: %d \n", jobSize);
  printf("Num threads with job size augmented by one element: %d \n", remainder);
}

DistanceFieldMT::~DistanceFieldMT()
{
}

int DistanceFieldMT::GetStartSlice(int rank)
{
  return startSlice[rank];
}

int DistanceFieldMT::GetEndSlice(int rank)
{
  return endSlice[rank];
}

// the routines for signed and unsigned distance field computation
#define COMPUTE_SIGNED_FIELD
  #define COMPUTE_FLOOD_FIELD
    #include "computeFieldMT.cpp"
  #undef COMPUTE_FLOOD_FIELD
    #include "computeFieldMT.cpp"
#undef COMPUTE_SIGNED_FIELD
  #include "computeFieldMT.cpp"

