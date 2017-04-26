/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "matrix" library , Copyright (C) 2007 CMU, 2009 MIT                   *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/code                                      *
 * Research: Jernej Barbic, Doug L. James, Jovan Popovic                 *
 * Funding: NSF, Link Foundation, Singapore-MIT GAMBIT Game Lab          *
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

#ifndef _MATRIX_SVD_H_
#define _MATRIX_SVD_H_

/*
  Compute the first few principal components (the dominant column space) 
  of a data matrix, via singular value decomposition (SVD).
  Requires BLAS and LAPACK.

  See also matrixIO.h.
*/

#include "matrixIO.h"

// specifies how to discard statistically insignificant components
typedef struct
{
  // epsilonBased: all singular values smaller than "epsilon" times largest singular value are discarded
  // numberOfModesBased: retain the first "rDesired" components
  enum {epsilonBased, numberOfModesBased} tresholdingType;
  int rDesired;
  double epsilon;
} ThresholdingSpecification;

// computes the dominant column space of a matrix A 
// matrix A is m x n and is stored column-major
// contents of A are destroyed
// on output, the first r columns of A contain the dominant column space
// returns code:
//   0: success
//  -1: input matrix is NULL
//  -2: memory allocation problem
// > 0: SVD failed, returns the dgesvd exit code 
// if "weights" (m-vector) are given, PCA will be weighted by the weights (mass-PCA)
int MatrixPCA(ThresholdingSpecification * thresholdingSpecification,
              int m, int n, double * A, int * r, double * weights=NULL);

#endif

