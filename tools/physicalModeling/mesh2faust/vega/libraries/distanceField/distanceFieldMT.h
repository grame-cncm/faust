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

#ifndef _DISTANCEFIELDMT_H_
#define _DISTANCEFIELDMT_H_

//#define USE_MULTICORE_LIBRARY

#include "distanceField.h"

class DistanceFieldMT : public DistanceField
{
public:

  DistanceFieldMT(int numThreads);
  virtual ~DistanceFieldMT();

  DistanceFieldMT(int resolutionX, int resolutionY, int resolutionZ, int numThreads);

  // advanced function (tells what range of Z-slices is assigned to each thread)
  int GetStartSlice(int rank);
  int GetEndSlice(int rank);

protected:
  virtual int ZigZagSigned(void * objMeshOctree, void * meshGraph);
  virtual int ZigZagUnsigned(void * objMeshOctree, void * meshGraph);
  virtual int ZigZagFloodFillSigned(void * objMeshOctree, void * meshGraph);

  void Setup();

  int numThreads;
  int * startSlice;
  int * endSlice;
};

#endif

