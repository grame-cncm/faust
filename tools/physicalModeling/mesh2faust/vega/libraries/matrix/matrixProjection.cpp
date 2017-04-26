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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CBLAS
#ifdef CBLAS
  #include "lapack-headers.h"
#endif

#include "matrixIO.h"
#include "matrixMacros.h"
#include "matrixProjection.h"

#ifdef CBLAS
// if-then-else template choosing
template<bool C>
class _cblas_xgemv {};

template<>
class _cblas_xgemv<true> {
public:
    inline static void f (const  CBLAS_ORDER order,
                 const  CBLAS_TRANSPOSE trans, const int m, const int n,
                 const float alpha, const float * a, const int lda,
                 const float * x, const int incx, float beta,
                 float * y, const int incy)
     { cblas_sgemv(order, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);}
};

template<>
class _cblas_xgemv<false> {
public:
    inline static void f (const  CBLAS_ORDER order,
                 const  CBLAS_TRANSPOSE trans, const int m, const int n,
                 const double alpha, const double * a, const int lda,
                 const double * x, const int incx, double beta,
                 double * y, const int incy)
     { cblas_dgemv(order, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);}
};
#endif

// construct vector f, using the equation f = U q
// matrix U is of size n x r, and is given in the column-major order
// vector q is of length r
// vector f is of length n
template <class real>
void SynthesizeVector(int n_inp, int r_inp, real * U_inp, real * q_inp, real * f_inp)
{
#ifdef CBLAS
  CBLAS_ORDER     order= CblasColMajor;
  CBLAS_TRANSPOSE trans= CblasNoTrans;
  int m = n_inp;
  int n = r_inp;
  real alpha = 1;
  real * a = U_inp;
  int lda = m;
  real * x = q_inp;
  int incx = 1;
  real beta = 0;
  real * y = f_inp; // holds the result
  int incy = 1;

  _cblas_xgemv<sizeof(real)==sizeof(float)>::f(order, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
#else
  int i,j;
  for (i=0; i<n_inp; i++) // over all rows, i.e. all coordinates
  {
    f_inp[i] = 0;
    for (j=0; j<r_inp; j++) // over all modes
      f_inp[i] += U_inp[ELT(n_inp,i,j)] * q_inp[j];
  }
#endif
}

// construct sparse vector f, using the equation f = U q
// matrix U is of size n x r, and is given in the column-major order
// vector q is of length r
// the coordinates of the vector f of interest are specified in the array i_buffer
// k is the total number of requested coordinates
// result is written into vector f. Length of result is k <= n
template <class real>
void SynthesizeSparseVector(int n, int r, real * U, real * q, real * f, int * i_buffer, int k)
{
  int i,j;
  for (i=0; i<k; i++) // over all non-zero rows
  {
    f[i] = 0;
    for (j=0; j<r; j++) // over all modes
      f[i] += U[ELT(n,i_buffer[i],j)] * q[j];
  }
}


// project vector f onto basis, given by U, using the equation q = U^T f
// matrix U is of size n x r
template <class real>
void ProjectVector(int n_inp, int r_inp, real * U_inp, real * q_inp, real * f_inp)
{
  // has to make inner product of vector f will all the columns of U
  // i.e. multiply U^T * f = q
#ifdef CBLAS
  CBLAS_ORDER     order= CblasColMajor;
  CBLAS_TRANSPOSE trans= CblasTrans;
  int m = n_inp;
  int n = r_inp;
  real alpha = 1;
  real * a = U_inp;
  int lda = m;
  real * x = f_inp;
  int incx = 1;
  real beta = 0;
  real * y = q_inp; // will hold the result
  int incy = 1;

  _cblas_xgemv<sizeof(real)==sizeof(float)>::f(order, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
#else
  int i,j;
  for (j=0; j<r_inp; j++) // over all columns of U
  {
    // dot product of column j of U with vector f
    q_inp[j] = 0;
    for (i=0; i<n_inp; i++)
      q_inp[j] += U_inp[ELT(n_inp,i,j)] * f_inp[i];
  }
#endif
}

// project sparse vector f onto basis, given by U, using the equation q = U^T f
// matrix U is of size n x r
// number of non-zero components of f is given by k
// non-zero components of vector f are given by f_buffer and i_buffer, where i_buffer[j] specifies the position, 
// and f_buffer[j] specifies the force component at i_buffer[j]
template <class real>
void ProjectSparseVector(int n, int r, real * U, real * q, real * f_buffer, int * i_buffer, int k)
{
  // has to make inner product of vector f will all the columns of U
  int i,j;
  for (j=0; j<r; j++) // over all columns of U
  {
    // dot product of column j of U with vector f
    q[j] = 0;
    for (i=0; i<k; i++)
      q[j] += U[ELT(n,i_buffer[i],j)] * f_buffer[i];
  }

}

template void SynthesizeVector<double>(int n, int r, double * U, double * q, double * f);
template void SynthesizeVector<float>(int n, int r, float * U, float * q, float * f);

template void SynthesizeSparseVector<double>(int n, int r, double * U, double * q, double * f, int * i_buffer, int k);
template void SynthesizeSparseVector<float>(int n, int r, float * U, float * q, float * f, int * i_buffer, int k);

template void ProjectVector<double>(int n, int r, double * U, double * q, double * f);
template void ProjectVector<float>(int n, int r, float * U, float * q, float * f);

template void ProjectSparseVector<double>(int n, int r, double * U, double * q, double * f_buffer, int * i_buffer, int k);
template void ProjectSparseVector<float>(int n, int r, float * U, float * q, float * f_buffer, int * i_buffer, int k);

