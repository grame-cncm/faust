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
  The "Matrix" class implements a matrix: a 2D array of real values,
  together with the commonly defined algebraic operations.
  The matrix can be rectangular (they need not be necessarily square). 
  The matrix is stored in the column-major order (same as in LAPACK).
  Storage is dense (see the "sparseMatrix" library for sparse matrices).
  The class suports common algebraic operations (addition, multiplication, 
  transposition, etc.), including operator overloading, so you can
  write expressions like: A += 0.25 * (B + A) * C;
  It is possible to load/save the matrix from/to a file, using 
  a special well-documented binary format (see matrixIO.h).
  The class can also perform more complex matrix operations such
  as computing the SVD decomposition, solving linear systems (via LU decomposition),
  finding eigenvalues and eigenvectors, solving least square systems, and
  computing matrix inverses and pseudoinverses.
  The code uses BLAS routines to perform matrix addition and multiplication,
  and LAPACK for SVD, LU, eigenanalysis, least square systems, inverses and pseudoinverses.
  
  The code can use the expokit package (http://www.maths.uq.edu.au/expokit/) to compute matrix exponentials. The wrapper to expokit is implemented ("MExpv" and "MExp" routines), but it is disabled by default to avoid linking problems when not using expokit. See the comment at the MExpv routine below for how to enable the exp functionality. Also note that the MExp and MExpv routines only work in double precision. This is because expokit supports double precision matrix exponentials (DGPADM), but does not currently include a single-precision routine SGPADM.

*/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrixMacros.h"
#include "matrixBLAS.h"
#include "matrixLAPACK.h"

// uncomment the following to use the MExpv and MExp routines:
//#define USE_EXPOKIT

#ifdef USE_EXPOKIT
  #include "matrixExp.h"
#endif

template<class real>
class Matrix
{
public:
  // load matrix from a file (see matrixIO.h for the binary file format)
  Matrix(const char * filename); 

  // create a m x n matrix; "data" must an array of length m*n, giving the matrix entries in column-major order
  // if "makeInternalDataCopy" is true (default), the class will internally make a copy of the data; otherwise, it will only direct its internal pointer to the user-provided array data
  // if "freeDataInDestructor" is true (default), the class will free the data array in the destructor; if "makeInternalDataCopy" is false, you will typically want to set "freeDataInDestructor" to false too
  Matrix(int m, int n, const real * data, 
         bool makeInternalDataCopy = true, bool freeDataInDestructor = true);
  // create a m x n matrix of all zeros
  Matrix (int m, int n, bool freeDataInDestructor = true);
  // create a m x n matrix of constant entries
  Matrix (int m, int n, real constEntry, bool freeDataInDestructor = true);
  // create a m x m diagonal matrix with all the diagonal entries equaling "diagonal"
  Matrix (int m, real diagonal, bool freeDataInDestructor = true);
  // create a m x m diagonal matrix with the diagonal entries specified by the array diagonal (of length m)
  Matrix (int m, const real * diagonal, bool freeDataInDestructor = true);
  // create a m x m diagonal matrix with the diagonal entries specified by the m x 1 matrix "vec"
  Matrix (int m, const Matrix & vec, bool freeDataInDestructor = true); 
  Matrix(const Matrix & mtx2);
  ~Matrix();

  inline int Getm() const { return m; }
  inline int Getn() const { return n; }
  inline real * GetData() const { return data; }

  const Matrix operator+ (const Matrix & mtx2) const;
  const Matrix operator- (const Matrix & mtx2) const;
  const Matrix operator* (const Matrix & mtx2) const;
  Matrix & operator= (const Matrix & mtx2);
  Matrix & operator+= (const Matrix & mtx2);
  Matrix & operator-= (const Matrix & mtx2);
  Matrix & operator*= (const Matrix & mtx2);
  Matrix & operator*= (const real alpha);
  inline const real & operator() (int row, int columns) const;
  inline real & operator() (int row, int columns);

  // output = trans(this) * mtx2
  const Matrix MultiplyT (const Matrix & mtx2) const;

  // transpose the matrix in place, i.e., without creating an intermediate copy buffer (useful with large matrices where the copy might otherwise not fit into memory)
  Matrix & InPlaceTranspose();

  // sets the submatrix, defined by its upper-left corner at (i,j) and the dimensions of "submatrix", to entries from the matrix "submatrix"
  void SetSubmatrix(int i, int j, const Matrix<real> & submatrix);

  void RemoveRows(int rowStart, int rowEnd);
  void RemoveColumns(int columnStart, int columnEnd);
  void RemoveRowsColumns(int columnStart, int columnEnd);
  void AppendRows(const Matrix<real> & rows);
  void AppendColumns(const Matrix<real> & columns);
  void AppendRowsColumns(const Matrix<real> & bottomLeftBlock, const Matrix<real> & topRightBlock, const Matrix<real> & bottomRightBlock);

  real MaxAbsEntry() const;

  void Print(int numDigits=-1) const; // if numDigits=-1: use %G flag
  int Save(const char * filename) const; // returns 0 on success, 1 on failure

  // factor <this matrix> = Q * Lambda * Q^T
  // matrix must be symmetric (no checks performed)
  // Lambda will be returned as a n x 1 vector, in ascending order
  void SymmetricEigenDecomposition(Matrix<real> & Q, Matrix<real> & Lambda);

  // computes SVD of matrix
  // this matrix = U * diag(Sigma) * VT
  // note: Sigma is returned as a MIN(m,n) x 1 vector
  // U must be a m x MIN(m,n) matrix
  // VT must be a  MIN(m,n) x n matrix
  void SVD(Matrix<real> & U, Matrix<real> & Sigma, Matrix<real> & VT);

  // compute eigenvalues and eigenvectors of a general matrix
  // eigenvectors are returned in the n x n matrix EigenVectors
  // eigenvalues are (in general) complex and are returned in n x 1 vectors LambdaRe and LambdaIm
  // return value: 0 on success, xGEEV INFO on failure (a general matrix is not always diagonalizable)
  int EigenDecomposition(Matrix<real> & EigenVectors, Matrix<real> & LambdaRe, Matrix<real> & LambdaIm);

  // solves linear system (via LU):
  // (this matrix) * x = rhs
  int LUSolve(const Matrix<real> & x, const Matrix<real> & rhs);

  // scalar-matrix multiplication
  // example: A = 0.37 * B;
  inline friend const Matrix<real> operator* (real alpha, const Matrix<real> & mtx2)
  {
    real * output = ScalarMultiplyMatrix(mtx2.Getm(), mtx2.Getn(), alpha,mtx2.GetData());
    return Matrix<real>(mtx2.Getm(),mtx2.Getn(),output,false);
  }

  // compute the Frobenius inner product of two matrices (sum of products of all pairwise entries)
  // example: double product = FrobeniusInnerProduct(A, B);
  inline friend real FrobeniusInnerProduct(const Matrix<real> & mtx1, const Matrix<real> & mtx2)
  {
    if ((mtx1.Getm() != mtx2.Getm()) || (mtx1.Getn() != mtx2.Getn()))
    {    
      printf("Matrix size mismatch in Matrix::FrobeniusInnerProduct.\n");
      throw 10;
    }
    real product = 0.0;
    int mn = mtx1.Getm() * mtx1.Getn();
    for(int i=0; i<mn; i++)
      product += mtx1.data[i] * mtx2.data[i];
    return product;
  }
  
  // transpose the matrix
  // example: A = Transpose(B);
  inline friend const Matrix<real> Transpose(const Matrix<real> & mtx2)
  {
    real * buffer = (real*) malloc (sizeof(real) * mtx2.Getm() * mtx2.Getn());
    memcpy(buffer, mtx2.GetData(), sizeof(real) * mtx2.Getm() * mtx2.Getn());
    InPlaceTransposeMatrix(mtx2.Getm(), mtx2.Getn(), buffer);
    return Matrix<real>(mtx2.Getn(), mtx2.Getm(), buffer, false);
  }

  // compute matrix inverse
  // example: A = Inverse(B);
  inline friend const Matrix<real> Inverse(const Matrix<real> & mtx2)
  {
    if (mtx2.Getm() != mtx2.Getn())
    {    
      printf("Matrix size mismatch in Matrix::Inverse . mtx2.m = %d, mtx2.n = %d\n",      mtx2.Getm(), mtx2.Getn());
      throw 11;
    }
    real * buffer = InverseMatrix(mtx2.Getm(), mtx2.GetData());
    return Matrix<real>(mtx2.Getm(), mtx2.Getm(), buffer, false);
  }

  // compute matrix pseudoinverse
  // example: A = PseudoInverse(B);
  inline friend const Matrix<real> PseudoInverse(const Matrix<real> & mtx2, real singularValueThreshold, int * rank)
  {
    real * buffer = PseudoInverseMatrix(mtx2.Getm(), mtx2.Getn(),
      mtx2.GetData(), singularValueThreshold, rank);
    return Matrix<real>(mtx2.Getn(), mtx2.Getm(), buffer, false);
  }

  // solve the least square system: mtx * output = rhs
  // rcond is the condition number beyond which matrix singular values are considered singular (see also LAPACK)
  // rank is a pointer to a single integer, giving the non-singular rank of the matrix, based on rcond
  // example:  A * X = B
  // int rank;
  // X = LeastSquareSolve(A, B, 1e-12, &rank);
  inline friend const Matrix<real> LeastSquareSolve(const Matrix<real> & mtx, const Matrix<real> & rhs, real rcond, int * rank)
  {
    if (mtx.Getm() != rhs.Getm())
    {    
      printf("Matrix size mismatch in Matrix::LeastSquareSolve . mtx.m = %d, rhs.m = %d\n", mtx.Getm(), rhs.Getm());
      throw 12;
    }
    real * buffer = MatrixLeastSquareSolve(mtx.Getm(), mtx.Getn(), rhs.Getn(), 
      mtx.GetData(), rhs.GetData(), rcond, rank);
    return Matrix<real>(mtx.Getn(), rhs.Getn(), buffer, false);
  }  

  // === matrix exponential routines ===

  // In order to use these routines, you must enable the USE_EXPOKIT definition in the header of matrix.h (disabled by default to avoid linker problems when expokit is not used), and link your code against the expokit library:
  // http://www.maths.uq.edu.au/expokit/
  // The expokit routines compute the matrix exponential of a general matrix in
  // full, using the irreducible rational Pade approximation to the 
  // exponential function exp(x) = r(x) = (+/-)( I + 2*(q(x)/p(x)) ),
  // combined with scaling-and-squaring.

  // computes w = exp((this matrix)*t)v, where v and w are vectors, and t is a scalar
  // "this matrix" must be a square matrix (denote the dimensions by m x m)
  // v and w are m x 1 vectors
  // note: this routine uses the same algorithm as MExp below: it explicitly constructs exp((this matrix)*t), and then multiplies by v
  void MExpv(real t, const Matrix<real> & v, Matrix<real> & w);

  // computes A = exp(t*mtx), where A and mtx are square matrices, and t is a scalar
  // code is a pointer to an integer where the xgpasm expokit routine exit code will be stored (you can pass NULL to discard this code); normal termination is code 0
  inline friend const Matrix<real> MExp(real t, const Matrix<real> & mtx, int * code = NULL)
  {
    #ifdef USE_EXPOKIT
      if (mtx.Getm() != mtx.Getn())
      {    
        printf("Matrix size mismatch in Matrix::MExp . mtx.m = %d, mtx.n = %d\n", mtx.Getm(), mtx.Getn());
        throw 13;
      }

      real * buffer = (real*) malloc (sizeof(real) * mtx.Getm() * mtx.Getm());
      int codei = MatrixExp(mtx.Getm(), mtx.GetData(), t, buffer);
      if (code != NULL)
        *code = codei;
      return Matrix<real>(mtx.Getm(), mtx.Getm(), buffer, false);
    #else
      printf("Error: MExp is not enabled.\n");
      return Matrix<real>();
    #endif
  }

protected:
  int m, n;
  real * data;
  bool freeDataInDestructor;
};

template<class real>
inline const real & Matrix<real>::operator() (int row, int column) const
{
  return data[ELT(m,row,column)];
}

template<class real>
inline real & Matrix<real>::operator() (int row, int column) 
{
  return data[ELT(m,row,column)];
}

#endif

