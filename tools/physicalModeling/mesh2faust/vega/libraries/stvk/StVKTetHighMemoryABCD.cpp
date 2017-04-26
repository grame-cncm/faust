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

#include "StVKTetHighMemoryABCD.h"

//#define CONTIGUOUSBLOCK

StVKTetHighMemoryABCD::StVKTetHighMemoryABCD(TetMesh * tetMesh)
{
  int numElements = tetMesh->getNumElements();

  // allocate contiguous buffer for coefficients
  int totalCoefficientSize = (sizeof(Mat3d [4][4]) +
    sizeof(double [4][4]) +
    sizeof(Vec3d [4][4][4]) +
    sizeof(double [4][4][4][4]) ) * numElements;

  #ifdef CONTIGUOUSBLOCK
    unsigned char * block = (unsigned char*) malloc (sizeof(unsigned char) * totalCoefficientSize);
    A_ = (Mat3d (*) [4][4]) &block[0];
    B_ = (double (*) [4][4]) &block[sizeof(Mat3d [4][4]) * numElements];
    C_ = (Vec3d (*) [4][4][4]) &block[(sizeof(Mat3d [4][4]) + sizeof(double [4][4])) * numElements];
    D_ = (double (*) [4][4][4][4]) &block[(sizeof(Mat3d [4][4]) + sizeof(double [4][4]) + sizeof(Vec3d [4][4][4])) * numElements];
  #else
    A_ = (Mat3d (*) [4][4]) malloc (sizeof(Mat3d [4][4]) * numElements);
    B_ = (double (*) [4][4]) malloc (sizeof(double [4][4]) * numElements);
    C_ = (Vec3d (*) [4][4][4]) malloc (sizeof(Vec3d [4][4][4]) * numElements);
    D_ = (double (*) [4][4][4][4]) malloc (sizeof(double [4][4][4][4]) * numElements);
  #endif

  for(int el=0; el<numElements; el++)
  {
    Vec3d vertices[4];
    for(int i=0; i<4; i++)
      vertices[i] = tetMesh->getVertex(el, i);
    StVKSingleTetABCD(vertices, A_[el], B_[el], C_[el], D_[el]);
  }

  printf("Total tet ABCD coefficient size: %G Mb.\n", 
   1.0 * totalCoefficientSize / 1024 / 1024);
}

StVKTetHighMemoryABCD::~StVKTetHighMemoryABCD()
{
  #ifdef CONTIGUOUSBLOCK
    free((unsigned char*)A_);
  #else
    free(A_);
    free(B_);
    free(C_);
    free(D_);
  #endif
}

void StVKTetHighMemoryABCD::StVKSingleTetABCD(Vec3d vtx[4], Mat3d A[4][4], double B[4][4], Vec3d C[4][4][4], double D[4][4][4][4])
{
  double det = TetMesh::getTetDeterminant(vtx[0], vtx[1], vtx[2], vtx[3]);
  double volume = fabs(det / 6);

  Vec3d Phig[4];
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
        Phig[i][j] = 1.0 * sign * dot(Vec3d(1,1,1), cross(columns[0],columns[1])) / det;
        countI++;
      }
    }

  // A
  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++)
      A[i][j] = volume * tensorProduct(Phig[i], Phig[j]);

  // B
  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++)
      B[i][j] = volume * dot(Phig[i], Phig[j]);    

  // C
  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++)
      for (int k=0; k<4; k++)
        C[i][j][k] = volume * dot(Phig[j], Phig[k]) * Phig[i];

  // D
  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++)
      for (int k=0; k<4; k++)
        for (int l=0; l<4; l++)
          D[i][j][k][l] = volume * dot(Phig[i],Phig[j]) * dot(Phig[k],Phig[l]);
}

