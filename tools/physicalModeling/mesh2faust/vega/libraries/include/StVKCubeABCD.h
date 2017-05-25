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

#ifndef _STVKCUBEABCD_H_
#define _STVKCUBEABCD_H_

#include "StVKElementABCD.h"

/*
  This classes stores the St.Venant-Kirchhoff A,B,C,D coefficients for a cube element.
  See also StVKInternalForces.h .
*/

class StVKCubeABCD : public StVKElementABCD
{
public:

  // computes the ABCD coefficients 
  StVKCubeABCD(double cubeSize); // the size of the cube is cubeSize x cubeSize x cubeSize

  inline virtual Mat3d A(void * elementIterator, int i, int j) { return A_[i][j]; }
  inline virtual double B(void * elementIterator, int i, int j) { return B_[i][j]; }
  inline virtual Vec3d C(void * elementIterator, int i, int j, int k) { return C_[i][j][k]; }
  inline virtual double D(void * elementIterator, int i, int j, int k, int l) { return D_[i][j][k][l]; }

  virtual ~StVKCubeABCD() {}

protected:
  Mat3d A_[8][8];
  double B_[8][8];
  Vec3d C_[8][8][8];
  double D_[8][8][8][8];
};

#endif

