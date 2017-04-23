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

/*
  Wrapper to matrix LAPACK routines.
  See also matrix.h.
*/

#ifndef _MATRIX_LAPACK_H_
#define _MATRIX_LAPACK_H_

#include <stdlib.h>

template<class real>
real * InverseMatrix(int m, real * mtx, real * output = NULL);

template<class real>
real * PseudoInverseMatrix(int m, int n, real * mtx, real singularValueThreshold = 1e-6, int * rank = NULL, real * output = NULL);

template<class real>
real * MatrixLeastSquareSolve(int m, int n, int nRhs, real * mtx, real * b, real rcond, int * rank = NULL, real * output = NULL);

template<class real>
void MatrixLUSolve(int n, int nRhs, real * mtx, real * x, real * b);

// mtx * x = lambda * x
template<class real>
void SymmetricMatrixEigenDecomposition(int m, real * mtx, real * Q, real * Lambda);

// mtx * x = lambda * mtx2 * x
// Warning: mtx2 will be modified after this function call.
template<class real>
void SymmetricMatrixGeneralEigenDecomposition(int m, real * mtx, real * mtx2, real * Q, real * Lambda);

// mtx * x = lambda * x
template<class real> 
int MatrixEigenDecomposition(int m, real * mtx, real * EigenVectors, real * LambdaRe, real * LambdaIm);

// U is m x MIN(m,n)
// Sigma is a MIN(m,n) vector
// VT is MIN(m,n) x n
template<class real> 
void MatrixSVD(int m, int n, real * mtx, real * U, real * Sigma, real * VT);

#endif

