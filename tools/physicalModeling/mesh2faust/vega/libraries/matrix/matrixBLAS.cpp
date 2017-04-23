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

#define BLAS

#ifdef BLAS
  #include "matrixBLASOptimized.cpp"
#else
  #include "matrixBLASVanilla.cpp"
#endif

#include "vegalong.h"

// transposes the matrix (without making a separate copy)
template <class real>
void InPlaceTransposeMatrix(int m, int n, real * mtx)
{ 
  real buffer;
  #define SWAP_ELT(i,j)\
    buffer = mtx[i];\
    mtx[i] = mtx[j];\
    mtx[j] = buffer;

  vegalong M = m;
  vegalong N = n;
  vegalong MN = M*N;
  
  for(vegalong i=0; i< MN; i++)
  {
    vegalong current = i;
    do
    {
      // evaluate permutation on 'current'
      vegalong k = current / N;
      vegalong l = current % N;
  
      current = M * l + k;
    } 
    while(current < i);

    if (current>i)
    {
      SWAP_ELT(i,current);
      //printf("Swap: %d %d .\n",i,current);
    }
  }
}

template float * MultiplyMatrices<float>(int m, int p, int n, float * mtx1, float * mtx2, float * output);
template double * MultiplyMatrices<double>(int m, int p, int n, double * mtx1, double * mtx2, double * output);

template float * MultiplyMatricesT<float>(int m, int p, int n, float * mtx1, float * mtx2, float * output);
template double * MultiplyMatricesT<double>(int m, int p, int n, double * mtx1, double * mtx2, double * output);

template float * SumMatrices<float>(int m, int n, float * mtx1, float * mtx2, float * output);
template double * SumMatrices<double>(int m, int n, double * mtx1, double * mtx2, double * output);

template float * SubtractMatrices<float>(int m, int n, float * mtx1, float * mtx2, float * output);
template double * SubtractMatrices<double>(int m, int n, double * mtx1, double * mtx2, double * output);

template float * ScalarMultiplyMatrix<float>(int m, int n, float alpha, float * mtx, float * output);
template double * ScalarMultiplyMatrix<double>(int m, int n, double alpha, double * mtx, double * output);

template void InPlaceTransposeMatrix<double>(int m, int n, double * U);
template void InPlaceTransposeMatrix<float>(int m, int n, float * U);

template double VectorNorm<double>(int m, double * vec);
template float VectorNorm<float>(int m, float * vec);
