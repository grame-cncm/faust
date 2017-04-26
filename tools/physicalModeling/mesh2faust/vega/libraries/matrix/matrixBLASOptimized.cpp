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
#include "lapack-headers.h"

//void cblas_scopy(const int N, const float *X, const int incX, float *Y, const int incY); 
template<bool C>
class _xcopy {};

template<>
class _xcopy<true> 
{
public:
    inline static void f(const int N, float * X, const int incX, float * Y, const int incY)
    {
      cblas_scopy(N,X,incX,Y,incY);
    }
};

template<>
class _xcopy<false> 
{
public:
    inline static void f(const int N, double * X, const int incX, double * Y, const int incY)
    {
      cblas_dcopy(N,X,incX,Y,incY);
    }
};

//void cblas_saxpy(const int N, const float alpha, const float *X, const int incX, float *Y, const int incY);
template<bool C>
class _xaxpy {};

template<>
class _xaxpy<true> 
{
public:
    inline static void f(const int N, float alpha, const float * X, const int incX, float * Y, const int incY)
    {
      cblas_saxpy(N,alpha,X,incX,Y,incY);
    }
};

template<>
class _xaxpy<false> 
{
public:
    inline static void f(const int N, double alpha, const double * X, const int incX, double * Y, const int incY)
    {
      cblas_daxpy(N,alpha,X,incX,Y,incY);
    }
};

//void cblas_sscal(const int N, const float alpha, float *X, const int incX); 
template<bool C>
class _xscal {};

template<>
class _xscal<true> 
{
public:
    inline static void f(const int N, const float alpha, float * X, const int incX)
    {
      cblas_sscal(N,alpha,X,incX);
    }
};

template<>
class _xscal<false> 
{
public:
    inline static void f(const int N, const double alpha, double * X, const int incX)
    {
      cblas_dscal(N,alpha,X,incX);
    }
};

//void cblas_snrm2(const int N, float * X, const int incX); 
template<bool C>
class _xnrm2 {};

template<>
class _xnrm2<true> 
{
public:
    inline static float f(const int N, const float * X, const int incX)
    {
      return cblas_snrm2(N,X,incX);
    }
};

template<>
class _xnrm2<false> 
{
public:
    inline static double f(const int N, const double * X, const int incX)
    {
      return cblas_dnrm2(N,X,incX);
    }
};

//void cblas_sgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_TRANSPOSE TransB, const int M, const int N, const int K, const float alpha, const float *A, const int lda, const float *B, const int ldb, const float beta, float *C, const int ldc);
template<bool C>
class _xgemm {};

template<>
class _xgemm<true> 
{
public:
    inline static void f(const CBLAS_ORDER Order, const CBLAS_TRANSPOSE TransA, const CBLAS_TRANSPOSE TransB, const int M, const int N, const int K, const float alpha, const float *A, const int lda, const float *B, const int ldb, const float beta, float *C, const int ldc)
    {
      cblas_sgemm(Order, TransA, TransB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
    }
};

template<>
class _xgemm<false> 
{
public:
    inline static void f(const CBLAS_ORDER Order, const CBLAS_TRANSPOSE TransA, const CBLAS_TRANSPOSE TransB, const int M, const int N, const int K, const double alpha, const double *A, const int lda, const double *B, const int ldb, const double beta, double *C, const int ldc)
    {
      cblas_dgemm(Order, TransA, TransB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
    }
};

template<class real>
real * SumMatrices(int m, int n, real * mtx1, real * mtx2, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  _xcopy<sizeof(real)==sizeof(float)>::f(m*n, mtx1, 1, target, 1);   
  _xaxpy<sizeof(real)==sizeof(float)>::f(m*n, 1.0, mtx2, 1, target, 1);   

/*
  for(int i=0; i<m*n; i++)
    target[i] = mtx1[i] + mtx2[i];
*/
  return target;
}

template<class real>
real * SubtractMatrices(int m, int n, real * mtx1, real * mtx2, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  _xcopy<sizeof(real)==sizeof(float)>::f(m*n, mtx1, 1, target, 1);   
  _xaxpy<sizeof(real)==sizeof(float)>::f(m*n, -1.0, mtx2, 1, target, 1);   

/*
  for(int i=0; i<m*n; i++)
    target[i] = mtx1[i] - mtx2[i];
*/
  return target;
}

template<class real>
real * MultiplyMatrices(int m, int p, int n, real * mtx1, real * mtx2, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  _xgemm<sizeof(real)==sizeof(float)>::f(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, p, 1.0, mtx1, m, mtx2, p, 0.0, target, m);

/*
  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
    {
      real entry = 0;
      for(int k=0; k<p; k++)
        entry += mtx1[ELT(m,i,k)] * mtx2[ELT(p, k, j)];
      target[ELT(m, i, j)] = entry;
    }
*/
  return target;
}

template<class real>
real * MultiplyMatricesT(int m, int p, int n, real * mtx1, real * mtx2, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * n * m);

  _xgemm<sizeof(real)==sizeof(float)>::f(CblasColMajor, CblasTrans, CblasNoTrans, m, n, p, 1.0, mtx1, p, mtx2, p, 0.0, target, m);

/*
  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
    {
      real entry = 0;
      for(int k=0; k<p; k++)
        entry += mtx1[ELT(p, k, i)] * mtx2[ELT(p, k, j)];
      target[ELT(m, i, j)] = entry;
    }
*/
  return target;
}

template<class real>
real * ScalarMultiplyMatrix(int m, int n, real alpha, real * mtx, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * n);

  _xcopy<sizeof(real)==sizeof(float)>::f(m*n, mtx, 1, target, 1);   
  _xscal<sizeof(real)==sizeof(float)>::f(m*n, alpha, target, 1);
  
/*
  for(int i=0; i<m*n; i++)
    target[i] = alpha * mtx[i];
*/

  return target;
}

// computes Euclidean norm of a vector
template <class real>
real VectorNorm(int m, real * vec)
{
  return _xnrm2<sizeof(real)==sizeof(float)>::f(m, vec, 1);
}

