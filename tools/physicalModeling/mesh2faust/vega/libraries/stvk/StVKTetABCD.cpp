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

#include "StVKTetABCD.h"

StVKTetABCD::StVKTetABCD(TetMesh * tetMesh)
{
  int numElements = tetMesh->getNumElements();
  int totalCoefficientSize = (sizeof(elementData) * numElements);

  elementsData = (elementData*) malloc (sizeof(elementData) * numElements);

  for(int el=0; el<numElements; el++)
  {
    Vec3d vertices[4];
    for(int i=0; i<4; i++)
      vertices[i] = tetMesh->getVertex(el, i);
    StVKSingleTetABCD(vertices, &elementsData[el]);
  }

  printf("Total tet ABCD coefficient size: %G Mb.\n", 
   1.0 * totalCoefficientSize / 1024 / 1024);
}

StVKTetABCD::~StVKTetABCD()
{
  free(elementsData);
}

void StVKTetABCD::StVKSingleTetABCD(Vec3d vtx[4], elementData * target)
{
  double det = TetMesh::getTetDeterminant(vtx[0], vtx[1], vtx[2], vtx[3]);
  target->volume = fabs(det / 6);

  for(int i=0; i<4; i++)
    for(int j=0; j<3; j++)
    {
      Vec3d columns[2];
      int countI = 0;
      for(int ii=0; ii<4; ii++)
      {
        if (ii == i)
          continue;
        int countJ = 0;
        for(int jj=0; jj<3; jj++)
        {
          if (jj == j)
            continue;

          columns[countJ][countI] = vtx[ii][jj];
          countJ++;
        }
        int sign = (((i + j) % 2) == 0) ? -1 : 1;
        target->Phig[i][j] = 1.0 * sign * dot(Vec3d(1,1,1), cross(columns[0],columns[1])) / det;
        countI++;
      }
    }
}

void StVKTetABCD::AllocateElementIterator(void ** elementIterator)
{
  ElementCache * cache = new ElementCache();
  *elementIterator = cache;
}

void StVKTetABCD::ReleaseElementIterator(void * elementIterator)
{
  ElementCache * cache = (ElementCache *) elementIterator;
  delete(cache);
}

void StVKTetABCD::PrepareElement(int el, void * elementIterator)
{
  ElementCache * cache = (ElementCache *) elementIterator;
  cache->elementPointer = &elementsData[el];
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      (cache->dots)[i][j] = dot(cache->elementPointer->Phig[i], cache->elementPointer->Phig[j]);
}

Mat3d StVKTetABCD::A(void * elementIterator, int i, int j)
{
  ElementCache * cache = (ElementCache *) elementIterator;
  return cache->elementPointer->volume * tensorProduct(cache->elementPointer->Phig[i], cache->elementPointer->Phig[j]);
}

double StVKTetABCD::B(void * elementIterator, int i, int j)
{
  ElementCache * cache = (ElementCache *) elementIterator;
  return cache->elementPointer->volume * cache->dots[i][j];
}

Vec3d StVKTetABCD::C(void * elementIterator, int i, int j, int k)
{
  ElementCache * cache = (ElementCache *) elementIterator;
  return cache->elementPointer->volume * cache->dots[j][k] * cache->elementPointer->Phig[i];
}

double StVKTetABCD::D(void * elementIterator, int i, int j, int k, int l)
{
  ElementCache * cache = (ElementCache *) elementIterator;
  return cache->elementPointer->volume * cache->dots[i][j] * cache->dots[k][l]; 
}

