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

#include "matrixMacros.h"
#include "matrixBLAS.h"
#include <math.h>

template<class real>
real * SumMatrices(int m, int n, real * mtx1, real * mtx2, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  int mn = m * n;
  for(int i=0; i<mn; i++)
    target[i] = mtx1[i] + mtx2[i];

  return target;
}

template<class real>
real * SubtractMatrices(int m, int n, real * mtx1, real * mtx2, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  int mn = m * n;
  for(int i=0; i<mn; i++)
    target[i] = mtx1[i] - mtx2[i];

  return target;
}

template<class real>
real * MultiplyMatrices(int m, int p, int n, real * mtx1, real * mtx2, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
    {
      real entry = 0;
      for(int k=0; k<p; k++)
        entry += mtx1[ELT(m,i,k)] * mtx2[ELT(p, k, j)];
      target[ELT(m, i, j)] = entry;
    }

  return target;
}

template<class real>
real * MultiplyMatricesT(int m, int p, int n, real * mtx1, real * mtx2, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
    {
      real entry = 0;
      for(int k=0; k<p; k++)
        entry += mtx1[ELT(p, k, i)] * mtx2[ELT(p, k, j)];
      target[ELT(m, i, j)] = entry;
    }

  return target;
}

template<class real>
real * ScalarMultiplyMatrix(int m, int n, real alpha, real * mtx, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  int mn = m * n;
  for(int i=0; i<mn; i++)
    target[i] = alpha * mtx[i];

  return target;
}

// computes Euclidean norm of a vector
template <class real>
real VectorNorm(int m, real * vec)
{
  double norm = 0;
  for(int i=0; i<m; i++)
    norm += vec[i] * vec[i];
  return (sqrt(norm));
}

