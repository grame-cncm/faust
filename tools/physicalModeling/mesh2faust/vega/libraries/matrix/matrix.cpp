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

#include <math.h>
#include "matrix.h"
#include "matrixIO.h"
#include "matrixExp.h"

template<class real>
Matrix<real>::Matrix(const char * filename)
{
  if (ReadMatrixFromDisk(filename, &m, &n, &data) != 0)
  {
    printf("Error loading matrix from %s.\n", filename);
    throw 1;
  }
  freeDataInDestructor = true;
}

template<class real>
Matrix<real>::Matrix(int m_, int n_, const real * data_, 
                     bool makeInternalDataCopy, bool freeDataInDestructor_):
  m(m_), n(n_), freeDataInDestructor(freeDataInDestructor_)
{
  if (makeInternalDataCopy)
  {
    data = (real*) malloc (sizeof(real) * m * n);
    memcpy(data, data_, sizeof(real) * m * n);
  }
  else
    data = (real*)data_;
}

template<class real>
Matrix<real>::Matrix (int m_, int n_, bool freeDataInDestructor_):
  m(m_), n(n_), freeDataInDestructor(freeDataInDestructor_)
{
  data = (real*) calloc (m * n, sizeof(real));
}

template<class real>
Matrix<real>::Matrix (int m_, int n_, real constEntry, bool freeDataInDestructor_):
  m(m_), n(n_), freeDataInDestructor(freeDataInDestructor_)
{
  data = (real*) malloc (sizeof(real) * m * n);
  for(int i=0; i<m*n; i++)
    data[i] = constEntry;
}

template<class real>
Matrix<real>::Matrix(int m_, real diagonal,
         bool freeDataInDestructor_):
  m(m_), n(m_), freeDataInDestructor(freeDataInDestructor_)
{
  data = (real*) calloc (m*m, sizeof(real));
  for(int i=0; i<m; i++)
    data[ELT(m,i,i)] = diagonal;
}

template<class real>
Matrix<real>::Matrix (int m_, const Matrix & vec, bool freeDataInDestructor_):
  m(m_), n(m_), freeDataInDestructor(freeDataInDestructor_)
{
  if (m != vec.Getm())
    throw 101;
  if (vec.Getn() != 1)
    throw 102;
  data = (real*) calloc (m*m, sizeof(real));
  for(int i=0; i<m; i++)
    data[ELT(m,i,i)] = vec(i,0);
}

template<class real>
Matrix<real>::Matrix(int m_, const real * diagonal,
         bool freeDataInDestructor_):
  m(m_), n(m_), freeDataInDestructor(freeDataInDestructor_)
{
  data = (real*) calloc (m*m, sizeof(real));
  for(int i=0; i<m; i++)
    data[ELT(m,i,i)] = diagonal[i];
}

template<class real>
Matrix<real>::Matrix(const Matrix<real> & mtx2)
{
  m = mtx2.Getm();
  n = mtx2.Getn();
  data = (real*) malloc (sizeof(real) * m * n);
  memcpy(data, mtx2.GetData(), sizeof(real) * m * n);
  freeDataInDestructor = true;
}

template<class real>
Matrix<real>::~Matrix()
{
  if (freeDataInDestructor)
    free(data);
}

template<class real>
const Matrix<real> Matrix<real>::operator+ (const Matrix<real> & mtx2) const
{
  if ((m != mtx2.Getm()) || (n != mtx2.Getn()))
  {
    printf("Matrix size mismatch in Matrix::operator+ . m = %d, n = %d, mtx2.m = %d, mtx2.n = %d\n",
      m, n, mtx2.Getm(), mtx2.Getn());
    throw 1;
  }
  real * output = SumMatrices(m, n, data, mtx2.GetData(), (real*)NULL);
  return Matrix<real>(m,n,output,false);
}

template<class real>
const Matrix<real> Matrix<real>::operator- (const Matrix<real> & mtx2) const
{
  if ((m != mtx2.Getm()) || (n != mtx2.Getn()))
  {
    printf("Matrix size mismatch in Matrix::operator- . m = %d, n = %d, mtx2.m = %d, mtx2.n = %d\n",
      m, n, mtx2.Getm(), mtx2.Getn());
    throw 2;
  }
  real * output = SubtractMatrices(m, n, data, mtx2.GetData(), (real*)NULL);
  return Matrix<real>(m,n,output,false);
}

template<class real>
const Matrix<real> Matrix<real>::operator* (const Matrix<real> & mtx2) const
{
  if (n != mtx2.Getm())
  {
    printf("Matrix size mismatch in Matrix::operator* . m = %d, n = %d, mtx2.m = %d, mtx2.n = %d\n",
      m, n, mtx2.Getm(), mtx2.Getn());
    throw 3;
  }
  real * output = MultiplyMatrices(m, n, mtx2.Getn(), data, mtx2.GetData(), (real*)NULL);
  return Matrix<real>(m,mtx2.Getn(),output,false);
}

// output = trans(this) * mtx2  
template<class real>
const Matrix<real> Matrix<real>::MultiplyT(const Matrix & mtx2) const
{
  if (m != mtx2.Getm())
  {
    printf("Matrix size mismatch in Matrix::MultiplyT . m = %d, n = %d, mtx2.m = %d, mtx2.n = %d\n",
      m, n, mtx2.Getm(), mtx2.Getn());
    throw 31;
  }
  real * output = MultiplyMatricesT(n, m, mtx2.Getn(), data, mtx2.GetData(), (real*)NULL);
  return Matrix<real>(n,mtx2.Getn(),output,false);
}

template<class real>
Matrix<real> & Matrix<real>::operator= (const Matrix<real> & mtx2)
{
  if ((m != mtx2.Getm()) || (n != mtx2.Getn()))
  {
    printf("Matrix size mismatch in Matrix::operator= . m = %d, n = %d, mtx2.m = %d, mtx2.n = %d\n",
      m, n, mtx2.Getm(), mtx2.Getn());
    throw 4;
  }
 
  if (this == &mtx2) // self-assignment
    return (*this);

  memcpy(data, mtx2.GetData(), sizeof(real) * m * n);
  return (*this);
}

template<class real>
Matrix<real> & Matrix<real>::operator+= (const Matrix<real> & mtx2)
{
  if ((m != mtx2.Getm()) || (n != mtx2.Getn()))
  {
    printf("Matrix size mismatch in Matrix::operator+= . m = %d, n = %d, mtx2.m = %d, mtx2.n = %d\n",
      m, n, mtx2.Getm(), mtx2.Getn());
    throw 5;
  }
  // works fine even if self-assignment
  SumMatrices(m, n, data, mtx2.GetData(), data);
  return (*this);
}

template<class real>
Matrix<real> & Matrix<real>::operator-= (const Matrix<real> & mtx2)
{
  if ((m != mtx2.Getm()) || (n != mtx2.Getn()))
  {
    printf("Matrix size mismatch in Matrix::operator-= . m = %d, n = %d, mtx2.m = %d, mtx2.n = %d\n",
      m, n, mtx2.Getm(), mtx2.Getn());
    throw 6;
  }
  // works fine even if self-assignment
  SubtractMatrices(m, n, data, mtx2.GetData(), data);
  return (*this);
}

template<class real>
Matrix<real> & Matrix<real>::operator*= (const Matrix<real> & mtx2)
{
  if ((n != mtx2.Getm()) || (n != mtx2.Getn()))
  {
    printf("Matrix size mismatch in Matrix::operator*= . m = %d, n = %d, mtx2.m = %d, mtx2.n = %d\n",
      m, n, mtx2.Getm(), mtx2.Getn());
    throw 7;
  }
  // works fine even if self-assignment
  real * buffer = MultiplyMatrices(m, n, n, data, mtx2.GetData());
  memcpy(data, buffer, sizeof(real) * m * n);
  free(buffer);
  return (*this);
}

template<class real>
Matrix<real> & Matrix<real>::operator*= (const real alpha)
{
  int mn = m * n;
  for(int i=0; i<mn; i++)
    data[i] *= alpha;   
  return (*this);
}

template<class real>
real Matrix<real>::MaxAbsEntry() const
{
  real maxAbsEntry = 0.0;
  int mn = m * n;
  for(int i=0; i<mn; i++)
  {
    if (fabs(data[i]) > maxAbsEntry)
      maxAbsEntry = fabs(data[i]);
  }
  return maxAbsEntry;
}

template<class real>
Matrix<real> & Matrix<real>::InPlaceTranspose()
{
  InPlaceTransposeMatrix(m, n, data);
  // swap m,n
  int swap = m;
  m = n;
  n = swap;
  return (*this);
}

template<class real>
void Matrix<real>::Print(int numDigits) const
{
  char formatString[6];
  if (numDigits < 0)
    strcpy(formatString,"%G ");
  else
    sprintf(formatString,"%%.%df ", numDigits);    

  for(int i=0; i<m; i++)
  {
    for(int j=0; j<n; j++)
      printf(formatString, (*this)(i,j));
    printf("\n");
  }
}

template<class real>
void Matrix<real>::SymmetricEigenDecomposition(Matrix<real> & Q, Matrix<real> & Lambda)
{    
  if (m != n)
  {
    printf("Matrix size mismatch in Matrix::SymmetricEigenDecomposition . m = %d, n = %d\n", m, n);
    throw 12;
  }    

  real * QData = (real*) malloc(sizeof(real) * m * m);
  real * LambdaData = (real*) malloc(sizeof(real) * m);
  SymmetricMatrixEigenDecomposition(m, data, QData, LambdaData);
  Q = Matrix<real>(m,m,QData,false);
  Lambda = Matrix<real>(m,1,LambdaData,false);
}

template<class real>
void Matrix<real>::SVD(Matrix<real> & U, Matrix<real> & Sigma, Matrix<real> & VT)
{    
  real * UData = (real*) malloc(sizeof(real) * m * MIN(m,n));
  real * SigmaData = (real*) malloc(sizeof(real) * MIN(m,n));
  real * VTData = (real*) malloc(sizeof(real) * MIN(m,n) * n);
  MatrixSVD(m, n, data, UData, SigmaData, VTData);
  U = Matrix<real>(m, MIN(m,n), UData, false);
  Sigma = Matrix<real>(MIN(m,n), 1, SigmaData, false);
  VT = Matrix<real>(MIN(m,n), n, VTData, false);
}

template<class real>
int Matrix<real>::EigenDecomposition(Matrix<real> & EigenVectors, Matrix<real> & LambdaRe, Matrix<real> & LambdaIm)
{    
  if (m != n)
  {
    printf("Matrix size mismatch in Matrix::EigenDecomposition . m = %d, n = %d\n", m, n);
    throw 13;
  }    

  real * EigenVectorsData = (real*) malloc(sizeof(real) * m * m);
  real * LambdaReData = (real*) malloc(sizeof(real) * m);
  real * LambdaImData = (real*) malloc(sizeof(real) * m);
  int code = MatrixEigenDecomposition(m, data, 
    EigenVectorsData, LambdaReData, LambdaImData);

  EigenVectors = Matrix<real>(m,m,EigenVectorsData,false);
  LambdaRe = Matrix<real>(m,1,LambdaReData,false);
  LambdaIm = Matrix<real>(m,1,LambdaImData,false);

  return code;
}

template<class real>
int Matrix<real>::LUSolve(const Matrix<real> & x, const Matrix<real> & rhs)
{
  if ((Getm() != Getn()) || (Getm() != x.Getm()) || (x.Getm() != rhs.Getm()) || (x.Getn() != rhs.Getn()) )
  {    
    printf("Matrix size mismatch in Matrix::LUSolve .\n");
    throw 12;
  }
  
  int exitCode = 0;
  try
  {
    MatrixLUSolve(Getn(), rhs.Getn(), GetData(), x.GetData(), rhs.GetData());
  }
  catch(int exceptionCode)
  {
    exitCode = exceptionCode;
  }

  return exitCode;
}

#ifdef USE_EXPOKIT

template<class real>
void Matrix<real>::MExpv(real t, const Matrix<real> & v, Matrix<real> & w)
{
  if ((Getm() != Getn()) || (Getm() != v.Getm()) || (Getm() != w.Getm()) || (v.Getn() != 1) || (w.Getn() != 1))
  {
    printf("Matrix size mismatch in Matrix::MExpv .\n");
    throw 13;
  }

  MatrixExpv(Getm(), GetData(), t, v.GetData(), w.GetData());
}

#else

template<class real>
void Matrix<real>::MExpv(real t, const Matrix<real> & v, Matrix<real> & w)
{
  printf("Error: MExpv is not enabled.\n");
}

#endif



template<class real>
int Matrix<real>::Save(const char * filename) const
{
  if (WriteMatrixToDisk(filename, m, n, data) != 0)
  {
    printf("Error writing matrix to %s.\n", filename);
    return 1;
  }
  return 0;
}

template<class real>
void Matrix<real>::SetSubmatrix(int I, int J, const Matrix<real> & submatrix)
{
  int subm = submatrix.Getm();
  int subn = submatrix.Getn();
  real * subdata = submatrix.GetData();

  if ((I < 0) || (J < 0) || (I + subm > m) || (J + subn > n))
  {
    printf("Error: matrix index out of bounds.\n");
    throw 21;
  }

  for(int j=0; j<subn; j++)
    for(int i=0; i<subm; i++)
      data[ELT(m,I+i,J+j)] = subdata[ELT(subm,i,j)];
}

template<class real>
void Matrix<real>::RemoveColumns(int columnStart, int columnEnd)
{
  // write everything to the right of columnEnd to the left
  int stride = columnEnd - columnStart;
  for(int column=columnEnd; column<n; column++)
  {
    // write column to column-stride
    memcpy(&data[ELT(m, 0, column-stride)], &data[ELT(m, 0, column)], sizeof(double) * m);
  }

  // free the space
  data = (real*) realloc (data, sizeof(real) * m * (n - stride));
 
  n = n - stride;
}

template<class real>
void Matrix<real>::RemoveRows(int rowStart, int rowEnd)
{
  InPlaceTransposeMatrix(m, n, data);
  int mBuf = m;
  m = n;
  n = mBuf;
  RemoveColumns(rowStart, rowEnd);
  InPlaceTransposeMatrix(m, n, data);
  mBuf = m;
  m = n;
  n = mBuf;
}

template<class real>
void Matrix<real>::RemoveRowsColumns(int columnStart, int columnEnd)
{
  RemoveColumns(columnStart, columnEnd);
  RemoveRows(columnStart, columnEnd);
}

template<class real>
void Matrix<real>::AppendColumns(const Matrix<real> & columns)
{
  if (columns.Getm() != m)
  {
    printf("Error: mismatch in number of rows in AppendColumns.\n");
    throw 41;
  }

  data = (real*) realloc (data, sizeof(real) * (m * (n + columns.Getn())));
  memcpy(&data[ELT(m, 0, n)], columns.GetData(), sizeof(real) * m * columns.Getn());
  n += columns.Getn();
}

template<class real>
void Matrix<real>::AppendRows(const Matrix<real> & rows)
{
  if (rows.Getn() != n)
  {
    printf("Error: mismatch in number of columns in AppendRows.\n");
    throw 42;
  }

  InPlaceTransposeMatrix(m, n, data);
  int mBuf = m;
  m = n;
  n = mBuf;
  Matrix<real> rowsT = Transpose(rows);
  AppendColumns(rowsT);
  InPlaceTransposeMatrix(m, n, data);
  mBuf = m;
  m = n;
  n = mBuf;
}

template<class real>
void Matrix<real>::AppendRowsColumns(const Matrix<real> & bottomLeftBlock, const Matrix<real> & topRightBlock, const Matrix<real> & bottomRightBlock)
{
  if (topRightBlock.Getm() != m)
  {
    printf("Error: mismatch in AppendRowsColumns.\n");
    throw 43;
  }

  if (bottomLeftBlock.Getn() != n)
  {
    printf("Error: mismatch in AppendRowsColumns.\n");
    throw 44;
  }

  if (bottomRightBlock.Getm() != bottomLeftBlock.Getm())
  {
    printf("Error: mismatch in AppendRowsColumns.\n");
    throw 45;
  }

  if (bottomRightBlock.Getn() != topRightBlock.Getn())
  {
    printf("Error: mismatch in AppendRowsColumns.\n");
    throw 46;
  }

  AppendColumns(topRightBlock);
 
  Matrix<real> blockMatrix(bottomLeftBlock.Getm(), n);
  real * blockMatrixData = blockMatrix.GetData();
  memcpy(blockMatrixData, bottomLeftBlock.GetData(), sizeof(real) * (bottomLeftBlock.Getm() * bottomLeftBlock.Getn()));
  memcpy(&blockMatrixData[ELT(bottomLeftBlock.Getm(), 0, bottomLeftBlock.Getn())], bottomRightBlock.GetData(), sizeof(real) * (bottomRightBlock.Getm() * bottomRightBlock.Getn()));
  AppendRows(blockMatrix);
}

// === float ===
template Matrix<float>::Matrix(const char * filename);
template Matrix<float>::Matrix(int m, int n, const float * data,
                     bool makeInternalDataCopy, bool freeDataInDestructor);
template Matrix<float>::Matrix(int m, int n, bool freeDataInDestructor);
template Matrix<float>::Matrix(int m, int n, float constEntry, bool freeDataInDestructor);
template Matrix<float>::Matrix(int m, float diagonal, bool freeDataInDestructor);
template Matrix<float>::Matrix(int m, const float * diagonal, bool freeDataInDestructor);
template Matrix<float>::Matrix (int m, const Matrix<float> & vec, bool freeDataInDestructor);
template Matrix<float>::Matrix(const Matrix<float> & mtx2);
template Matrix<float>::~Matrix();
template const Matrix<float> Matrix<float>::operator+ (const Matrix<float> & mtx2) const;
template const Matrix<float> Matrix<float>::operator- (const Matrix<float> & mtx2) const;
template const Matrix<float> Matrix<float>::operator* (const Matrix<float> & mtx2) const;
template const Matrix<float> Matrix<float>::MultiplyT(const Matrix<float> & mtx2) const;
template Matrix<float> & Matrix<float>::operator= (const Matrix<float> & mtx2);
template Matrix<float> & Matrix<float>::operator+= (const Matrix<float> & mtx2);
template Matrix<float> & Matrix<float>::operator-= (const Matrix<float> & mtx2);
template Matrix<float> & Matrix<float>::operator*= (const Matrix<float> & mtx2);
template Matrix<float> & Matrix<float>::operator*= (const float alpha);
template float Matrix<float>::MaxAbsEntry() const;
template Matrix<float> & Matrix<float>::InPlaceTranspose();
template void Matrix<float>::SymmetricEigenDecomposition(Matrix<float> & Q, Matrix<float> & Lambda);
template void Matrix<float>::SVD(Matrix<float> & U, Matrix<float> & Sigma, Matrix<float> & VT);
template int Matrix<float>::EigenDecomposition(Matrix<float> & EigenVectors, Matrix<float> & LambdaRe, Matrix<float> & LambdaIm);
template int Matrix<float>::LUSolve(const Matrix<float> & x, const Matrix<float> & rhs);
#ifdef USE_EXPOKIT
  template void Matrix<float>::MExpv(float t, const Matrix<float> & v, Matrix<float> & w);
#endif
template void Matrix<float>::Print(int numDigits) const; 
template int Matrix<float>::Save(const char * filename) const;
template void Matrix<float>::SetSubmatrix(int I, int J, const Matrix<float> & submatrix);
template void Matrix<float>::RemoveColumns(int columnStart, int columnEnd);
template void Matrix<float>::RemoveRows(int rowStart, int rowEnd);
template void Matrix<float>::RemoveRowsColumns(int columnStart, int columnEnd);
template void Matrix<float>::AppendRows(const Matrix<float> & rows);
template void Matrix<float>::AppendColumns(const Matrix<float> & columns);
template void Matrix<float>::AppendRowsColumns(const Matrix<float> & bottomLeftBlock, const Matrix<float> & topRightBlock, const Matrix<float> & bottomRightBlock);

// === double ===
template Matrix<double>::Matrix(const char * filename);
template Matrix<double>::Matrix(int m, int n, const double * data,
                     bool makeInternalDataCopy, bool freeDataInDestructor);
template Matrix<double>::Matrix(int m, int n, bool freeDataInDestructor);
template Matrix<double>::Matrix(int m, int n, double constEntry, bool freeDataInDestructor);
template Matrix<double>::Matrix(int m, double diagonal, bool freeDataInDestructor);
template Matrix<double>::Matrix(int m, const double * diagonal, bool freeDataInDestructor);
template Matrix<double>::Matrix (int m, const Matrix<double> & vec, bool freeDataInDestructor);
template Matrix<double>::Matrix(const Matrix<double> & mtx2);
template Matrix<double>::~Matrix();
template const Matrix<double> Matrix<double>::operator+ (const Matrix<double> & mtx2) const;
template const Matrix<double> Matrix<double>::operator- (const Matrix<double> & mtx2) const;
template const Matrix<double> Matrix<double>::operator* (const Matrix<double> & mtx2) const;
template Matrix<double> & Matrix<double>::operator*= (const double alpha);
template const Matrix<double> Matrix<double>::MultiplyT(const Matrix<double> & mtx2) const;
template Matrix<double> & Matrix<double>::operator= (const Matrix<double> & mtx2);
template Matrix<double> & Matrix<double>::operator+= (const Matrix<double> & mtx2);
template Matrix<double> & Matrix<double>::operator-= (const Matrix<double> & mtx2);
template Matrix<double> & Matrix<double>::operator*= (const Matrix<double> & mtx2);
template double Matrix<double>::MaxAbsEntry() const;
template Matrix<double> & Matrix<double>::InPlaceTranspose();
template void Matrix<double>::SymmetricEigenDecomposition(Matrix<double> & Q, Matrix<double> & Lambda);
template void Matrix<double>::SVD(Matrix<double> & U, Matrix<double> & Sigma, Matrix<double> & VT);
template int Matrix<double>::EigenDecomposition(Matrix<double> & EigenVectors, Matrix<double> & LambdaRe, Matrix<double> & LambdaIm);
template int Matrix<double>::LUSolve(const Matrix<double> & x, const Matrix<double> & rhs);
#ifdef USE_EXPOKIT
  template void Matrix<double>::MExpv(double t, const Matrix<double> & v, Matrix<double> & w);
#endif
template void Matrix<double>::Print(int numDigits) const;
template int Matrix<double>::Save(const char * filename) const;
template void Matrix<double>::SetSubmatrix(int I, int J, const Matrix<double> & submatrix);
template void Matrix<double>::RemoveColumns(int columnStart, int columnEnd);
template void Matrix<double>::RemoveRows(int rowStart, int rowEnd);
template void Matrix<double>::RemoveRowsColumns(int columnStart, int columnEnd);
template void Matrix<double>::AppendRows(const Matrix<double> & rows);
template void Matrix<double>::AppendColumns(const Matrix<double> & columns);
template void Matrix<double>::AppendRowsColumns(const Matrix<double> & bottomLeftBlock, const Matrix<double> & topRightBlock, const Matrix<double> & bottomRightBlock);

