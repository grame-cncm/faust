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

/*
  This class is a multi-threaded version of the class "StVKStiffnessMatrix".
  It uses POSIX threads ("pthreads") as the threading API.
  Each thread assembles the stiffness matrix with respect to a subset of all the mesh elements. 
  At the end, the individual results are added into a global stiffness matrix.

  See also StVKStiffnessMatrix.h .
*/

#ifndef _STVKSTIFFNESSMATRIXMT_H_
#define _STVKSTIFFNESSMATRIXMT_H_

#include "StVKStiffnessMatrix.h"

class StVKStiffnessMatrixMT : public StVKStiffnessMatrix
{
public:
  // multicore version of StVKStiffnessMatrix
  StVKStiffnessMatrixMT(StVKInternalForces *  stVKInternalForces, int numThreads);
  virtual ~StVKStiffnessMatrixMT();

  // evaluates the stiffness matrix in the given deformation configuration
  virtual void ComputeStiffnessMatrix(const double * vertexDisplacements, SparseMatrix * sparseMatrix);

  int GetStartElement(int rank);
  int GetEndElement(int rank);

protected:
  int numThreads;
  int * startElement, * endElement;
  SparseMatrix ** sparseMatrixBuffer;
};

#endif

