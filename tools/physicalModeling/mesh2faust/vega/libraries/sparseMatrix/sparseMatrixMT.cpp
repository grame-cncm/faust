/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sparseMatrixMT" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC *
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <set>
#include <algorithm>
#include "sparseMatrixMT.h"
using namespace std;

// for faster computation, enable the -fopenmp -DUSE_OPENMP macro line in the Makefile-header file (see also documentation)

#ifdef USE_OPENMP
  #include <omp.h>
#endif

void SparseMatrixMT::MultiplyVector(const SparseMatrix * A, const double * input, double * result, int numThreads)
{
  int ** indices = A->GetColumnIndices();
  double ** entries = A->GetEntries();
  int * rowLengths = A->GetRowLengths();
  int n = A->GetNumRows();
  if (numThreads < 0)
  #ifdef USE_OPENMP
    numThreads = omp_get_num_threads();
  #else
    numThreads = 0;
  #endif

  #ifdef USE_OPENMP
    #pragma omp parallel for num_threads(numThreads)
  #endif
  for(int i=0; i<n; i++)
  {
    result[i] = 0;
    for(int j=0; j < rowLengths[i]; j++)
    {
      result[i] += input[indices[i][j]] * entries[i][j];
    }
  }
}


