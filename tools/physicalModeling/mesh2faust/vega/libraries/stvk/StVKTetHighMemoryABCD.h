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

#ifndef _STVKTETHIGHMEMORYABCD_H_
#define _STVKTETHIGHMEMORYABCD_H_

#include "StVKElementABCD.h"
#include "tetMesh.h"

/*
  Class "StVKTetHighMemoryABCD" stores (explicitly) the St.Venant-Kirchhoff 
  A,B,C,D coefficients for a tetrahedron (high-memory version).
  It enables fast coefficient access, but requires more memory than 
  the "StVKTetABCD" class. The class "StVKTetHighMemoryABCD" is practical 
  up to a few thousand tetrahedra, depending on the size of your memory. 
  In our simulations, we usually used "StVKTetABCD" for all the tet meshes.
*/

class StVKTetHighMemoryABCD : public StVKElementABCD
{
public:

  // computes the ABCD coefficients 
  StVKTetHighMemoryABCD(TetMesh * tetMesh);

  inline virtual Mat3d A(void * elementIterator, int i, int j) { return A_[*(int*)elementIterator][i][j]; }
  inline virtual double B(void * elementIterator, int i, int j) { return B_[*(int*)elementIterator][i][j]; }
  inline virtual Vec3d C(void * elementIterator, int i, int j, int k) { return C_[*(int*)elementIterator][i][j][k]; }
  inline virtual double D(void * elementIterator, int i, int j, int k, int l) { return D_[*(int*)elementIterator][i][j][k][l]; }

  virtual ~StVKTetHighMemoryABCD();

protected:
  Mat3d (*A_) [4][4];
  double (*B_) [4][4];
  Vec3d (*C_) [4][4][4];
  double (*D_) [4][4][4][4];

  void StVKSingleTetABCD(Vec3d vertices[4], Mat3d A[4][4], double B[4][4], Vec3d C[4][4][4], double D[4][4][4][4]);
};

#endif

