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

#ifndef _STVKTETABCD_H_
#define _STVKTETABCD_H_

#include "StVKElementABCD.h"
#include "tetMesh.h"

/*
  This class stores the St.Venant-Kirchhoff A,B,C,D coefficients for a tetrahedral element.
  This is the low-memory version (the version that we use most often).
  See also StVKInternalForces.h .
*/

class StVKTetABCD : public StVKElementABCD
{
public:

  // computes the ABCD coefficients 
  StVKTetABCD(TetMesh * tetMesh);

  virtual Mat3d A(void * elementIterator, int i, int j);
  virtual double B(void * elementIterator, int i, int j);
  virtual Vec3d C(void * elementIterator, int i, int j, int k);
  virtual double D(void * elementIterator, int i, int j, int k, int l);

  typedef struct
  {
    double volume;
    Vec3d Phig[4]; // gradient of a basis function
  } elementData;

  typedef struct
  {
    elementData * elementPointer;
    double dots[4][4];
  } ElementCache;

  void AllocateElementIterator(void ** elementIterator);
  void ReleaseElementIterator(void * elementIterator);
  void PrepareElement(int el, void * elementIterator); // must call each time before accessing an element

  virtual ~StVKTetABCD();

protected:

  elementData * elementsData;

  // creates the elementData structure for a tet
  void StVKSingleTetABCD(Vec3d vertices[4], elementData * target);
};

#endif

