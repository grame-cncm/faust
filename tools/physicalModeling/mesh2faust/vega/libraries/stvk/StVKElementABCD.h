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

#ifndef _STVKELEMENTABCD_H_
#define _STVKELEMENTABCD_H_

#include "minivector.h"

/*
  This abstract class serves as storage space for the St.Venant-Kirchhoff A,B,C,D coefficients for a mesh element. 
  See also StVKInternalForces.h .
*/

class StVKElementABCD
{
public:

  // the iterator can be different types in the derived implementation classes
  virtual Mat3d A(void * elementIterator, int i, int j) = 0;
  virtual double B(void * elementIterator, int i, int j) = 0;
  virtual Vec3d C(void * elementIterator, int i, int j, int k) = 0;
  virtual double D(void * elementIterator, int i, int j, int k, int l) = 0;

  virtual ~StVKElementABCD() {};

  virtual void AllocateElementIterator(void ** elementIterator);
  virtual void ReleaseElementIterator(void * elementIterator);
  virtual void PrepareElement(int el, void * elementIterator); // must call each time before accessing an element

protected:
};

#endif

