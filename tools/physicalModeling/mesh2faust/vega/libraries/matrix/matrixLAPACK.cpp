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
#include <math.h>
#include "lapack-headers.h"
#include "matrixMacros.h"
#include "matrixLAPACK.h"
#include "matrixBLAS.h"

#ifdef __APPLE__
  #define DGETRF dgetrf_
  #define DGETRI dgetri_
  #define SGETRF sgetrf_
  #define SGETRI sgetri_
  #define DGESVD dgesvd_
  #define SGESVD sgesvd_
  #define DGELSY dgelsy_
  #define SGELSY sgelsy_
  #define DGESV dgesv_
  #define SGESV sgesv_
  #define DSYEV dsyev_
  #define SSYEV ssyev_
  #define DSYGV dsygv_
  #define SSYGV ssygv_
  #define SGEEV sgeev_
  #define DGEEV dgeev_
  #define DGPADM dgpadm_
  #define SGPADM sgpadm_
  #define INTEGER __CLPK_integer
#else
  #define DGETRF dgetrf
  #define DGETRI dgetri
  #define SGETRF sgetrf
  #define SGETRI sgetri
  #define DGESVD dgesvd
  #define SGESVD sgesvd
  #define DGELSY dgelsy
  #define SGELSY sgelsy
  #define DGESV dgesv
  #define SGESV sgesv
  #define DSYEV dsyev
  #define SSYEV ssyev
  #define DSYGV dsygv
  #define SSYGV ssygv
  #define SGEEV sgeev
  #define DGEEV dgeev
  #define DGPADM dgpadm_
  #define SGPADM sgpadm_
  #define INTEGER int
#endif

template<bool C>
class _xinverse {};

template<>
class _xinverse<true> {
public:
    inline static INTEGER f( INTEGER m, float * A, 
                          INTEGER * IPIV, float * WORK, 
                          INTEGER LWORK)
    {
      INTEGER M = m;
      INTEGER N = m;
      INTEGER LDA = m;
      INTEGER INFO;
      SGETRF (&M, &N, A, &LDA, IPIV, &INFO);

      if (INFO != 0)
      {
        printf("Warning: LAPACK routine SGETRF returned non-zero exit status %d.\n",(int)INFO);
      } 

      //SUBROUTINE SGETRI( N, A, LDA, IPIV, WORK, LWORK, INFO );
      SGETRI(&M, A, &LDA, IPIV, WORK, &LWORK, &INFO);

      if (INFO != 0)
      {
        printf("Warning: LAPACK routine SGETRI returned non-zero exit status %d.\n",(int)INFO);
      } 

      return INFO;
    }
};

template<>
class _xinverse<false> {
public:
    inline static INTEGER f( INTEGER m, double * A, 
                          INTEGER * IPIV, double * WORK, 
                          INTEGER LWORK)
    {
      INTEGER M = m;
      INTEGER N = m;
      INTEGER LDA = m;
      INTEGER INFO;
      DGETRF (&M, &N, A, &LDA, IPIV, &INFO);

      if (INFO != 0)
      {
        printf("Warning: LAPACK routine DGETRF returned non-zero exit status %d.\n",(int)INFO);
      } 

      //SUBROUTINE DGETRI( N, A, LDA, IPIV, WORK, LWORK, INFO );
      DGETRI(&M, A, &LDA, IPIV, WORK, &LWORK, &INFO);

      if (INFO != 0)
      {
        printf("Warning: LAPACK routine DGETRI returned non-zero exit status %d.\n",(int)INFO);
      } 

      return INFO;
    }
};

template<class real>
real * InverseMatrix(int m, real * mtx, real * output)
{
  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * m * m);

  memcpy(target, mtx, sizeof(real) * m * m);
  
  real * A = target;
  INTEGER * IPIV = (INTEGER*) malloc(sizeof(INTEGER) * m);

  INTEGER NB = 32; // optimal block size; could also call ilaenv
  INTEGER LWORK = m * NB;
  real * WORK = (real*) malloc (sizeof(real) * LWORK);

  _xinverse<sizeof(float)==sizeof(real)>::f(m, A, IPIV, WORK, LWORK);

  free(WORK);
  free(IPIV);

  return target;
}


template<bool C>
class _xgesvd {};

template<>
class _xgesvd<true> {
public:
    //SUBROUTINE SGESVD( JOBU, JOBVT, M, N, A, LDA, S, U, LDU, VT, LDVT, WORK, LWORK, INFO )

    inline static void f( char * jobu, char * jobvt, INTEGER * m, INTEGER * n,
                          float * A, INTEGER * LDA, float * S, float * U,
                          INTEGER * LDU, float * VT, INTEGER * LDVT, 
                          float * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      SGESVD(jobu, jobvt, m, n, A, LDA, S, U, LDU, VT, LDVT, WORK, LWORK, INFO);
    }
};

template<>
class _xgesvd<false> {
public:
    inline static void f( char * jobu, char * jobvt, INTEGER * m, INTEGER * n,
                          double * A, INTEGER * LDA, double * S, double * U,
                          INTEGER * LDU, double * VT, INTEGER * LDVT, 
                          double * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      DGESVD(jobu, jobvt, m, n, A, LDA, S, U, LDU, VT, LDVT, WORK, LWORK, INFO);
    }
};

template<class real>
real * PseudoInverseMatrix(int m, int n, real * mtx, real singularValueThreshold, int * rank_, real * output)
{
  real * A = (real*) malloc (sizeof(real) * m * n);
  memcpy(A, mtx, sizeof(real) * m * n);

  bool transpose = (m > n);
  if (transpose)
  {
    // swap m,n
    InPlaceTransposeMatrix(m,n, A);
    int buffer = m;
    m = n;
    n = buffer;
  }

  // now, we always have m <= n

  char jobu  = 'O';//overwrites A with U (left singular vectors)
  char jobvt = 'S';//all rows returned in VT

  int ldA = m;
  int ldU = m;

  INTEGER NB = 32; // optimal block size; could also call ilaenv
  int lwork = NB*MAX(3*MIN( m, n)+MAX(m,n), 5*MIN(m,n)-4);

  real * work = (real*) malloc (sizeof(real) * lwork);
  if (!work)
  {
    printf("Error: failed to allocate workspace.\n");
    throw 1;
  }

  //printf("Workspace size is: %G Mb .\n",1.0 * lwork * sizeof(int) / 1024 / 1024);

  // allocate array for singular vectors
  real * S = (real *) malloc (sizeof(real) * MIN(m,n));
  if (!S)
  {
    printf("Error: failed to allocate singular vectors.\n");
    free(work);
    throw 2;
  }

  // allocate array for VT
  int ldVT = MIN(m,n);
  real * VT = (real *) malloc (sizeof(real) * ldVT * n);
  if (!VT)
  {
    printf("Error: failed to allocate VT.\n");
    free(S);
    free(work);
    throw 3;
  }

  INTEGER M = m;
  INTEGER N = n;
  INTEGER LDA = ldA;
  INTEGER LDU = ldU;
  INTEGER LDVT = ldVT;
  INTEGER LWORK = lwork;
  INTEGER INFO;

  //printf("Calling LAPACK dgesvd routine...\n");fflush(NULL);

  //SUBROUTINE SGESVD( JOBU, JOBVT, M, N, A, LDA, S, U, LDU, VT, LDVT, WORK, LWORK, INFO )

  _xgesvd<sizeof(real)==sizeof(float)>::f 
                 (&jobu, &jobvt, &M, &N, A, &LDA,
                  S, NULL, &LDU, VT,
                  &LDVT, work, &LWORK, &INFO);

  if (INFO != 0)
  {
    int code = INFO;
    printf("Error: SVD solver returned non-zero exit code: %d.\n", code);
    free(VT);
    free(S);
    free(work);
    throw 4;
  }

  free(work);

  //printf ("Singular values:\n");fflush(NULL);
  //for (int i=0; i< MIN(m,n); i++)
   // printf("%f ",S[i]);
  //printf ("\n");

  // discard small singular values
  int rank = MIN(m,n);
  for(int i=0; i< MIN(m,n); i++)
  {
    if (S[i] / S[0] < singularValueThreshold)
    {
      rank = i;
      break;
    }
  }

  for(int i=0; i< rank; i++)
    S[i] = ((real)1.0) / S[i];

  for(int i=rank; i< MIN(m,n); i++)
    S[i] = 0.0;

  real * U = A;
  memset(&U[ELT(m,0,rank)], 0, sizeof(real) * m * (n-rank));
  InPlaceTransposeMatrix(m, m, U);
  real * UT = U;
  // UT is now m x m

  InPlaceTransposeMatrix(m,n,VT);
  real * V = VT;
  // V is now n x m

  // multiply A^{\dagger} = V * Sigma^{-1} * U^T
  for(int j=0; j<m; j++) // over all columns
    for(int i=0; i<n; i++) // over all rows
      V[ELT(n, i, j)] *= S[j];

  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * n * m);

  // V * UT
  // (n x m) * (m x m)
  // output is n x m
  MultiplyMatrices(n, m, m, V, UT, target);

  if (transpose)
    InPlaceTransposeMatrix(n, m, target);

  free(A);
  free(S);
  free(VT);

  if (rank_ != NULL)
    *rank_ = rank;

  return target;
}

template<bool C>
class _xgelsy {};

//SUBROUTINE DGELSY( M, N, NRHS, A, LDA, B, LDB, JPVT, RCOND, RANK,
//                   WORK, LWORK, INFO )

template<>
class _xgelsy<true> {
public:

    inline static void f( INTEGER * M, INTEGER * N, INTEGER * NRHS, 
                          float * A, INTEGER * LDA,
                          float * B, INTEGER * LDB, 
                          INTEGER * JPVT, float * RCOND, INTEGER * RANK,
                          float * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      SGELSY( M, N, NRHS, A, LDA, B, LDB, JPVT, RCOND, RANK,
              WORK, LWORK, INFO );
    }
};

template<>
class _xgelsy<false> {
public:

    inline static void f( INTEGER * M, INTEGER * N, INTEGER * NRHS, 
                          double * A, INTEGER * LDA,
                          double * B, INTEGER * LDB, 
                          INTEGER * JPVT, double * RCOND, INTEGER * RANK,
                          double * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      DGELSY( M, N, NRHS, A, LDA, B, LDB, JPVT, RCOND, RANK,
              WORK, LWORK, INFO );
    }
};

template<class real>
real * MatrixLeastSquareSolve(int m, int n, int nRhs, real * mtx, real * b, real rcond, int * rank_, real * output)
{
  real * A = (real*) malloc (sizeof(real) * m * n);
  if (!A)
  {
    printf("Error: failed to allocate A.\n");
    throw 1;
  }
  memcpy(A, mtx, sizeof(real) * m * n);

  INTEGER M = m;
  INTEGER N = n;
  INTEGER NRHS = nRhs;
  INTEGER LDA = m;

  INTEGER LDB = MAX(M,N);
  real * B = (real*) calloc (LDB * nRhs, sizeof(real));
  if (!B)
  {
    printf("Error: failed to allocate B.\n");
    free(A);
    throw 2;
  }
  for(int i=0; i < nRhs; i++)
    memcpy(&B[ELT(LDB,0,i)], &b[ELT(m,0,i)], sizeof(real) * m);

  INTEGER * JPVT = (INTEGER*) malloc (sizeof(INTEGER) * N);
  if (!JPVT)
  {
    printf("Error: failed to allocate JPVT.\n");
    free(B);
    free(A);
    throw 3;
  }
 
  INTEGER RANK;
  real RCOND = rcond;

  INTEGER NB = 32; // optimal block size; could also call ilaenv
  INTEGER LWORK = MAX( M*N+2*N+NB*(N+1), 2*M*N+NB*NRHS );

  real * WORK = (real*) malloc (sizeof(real) * LWORK);
  if (!WORK)
  {
    printf("Error: failed to allocate workspace.\n");
    free(JPVT);
    free(B);
    free(A);
    throw 4;
  }

  //printf("Workspace size is: %G Mb .\n",1.0 * LWORK * sizeof(int) / 1024 / 1024);

  INTEGER INFO;

  //printf("M=%d N=%d NRHS=%d LDA=%d LDB=%d\n", (int)M, (int)N, (int)NRHS, (int)LDA, (int)LDB);
  _xgelsy<sizeof(real)==sizeof(float)>::f 
                 (&M, &N, &NRHS, A, &LDA, B, &LDB, 
                  JPVT, &RCOND, &RANK,
                  WORK, &LWORK, &INFO );

  if (INFO != 0)
  {
    int code = INFO;
    printf("Error: xGELSY solver returned non-zero exit code: %d.\n", code);
    free(WORK);
    free(JPVT);
    free(B);
    free(A);
    throw 5;
  }

  free(JPVT);
  free(WORK);
  free(A);

  real * target = output;
  if (target == NULL)
    target = (real*) malloc (sizeof(real) * n * nRhs);

  for(int i=0; i < nRhs; i++)
    memcpy(&target[ELT(n,0,i)], &B[ELT(LDB,0,i)], sizeof(real) * n);

  free(B);

  if (rank_ != NULL)
    *rank_ = RANK;

  return target;
}

template<bool C>
class _xgesv {};


//DGESV( N, NRHS, A, LDA, IPIV, B, LDB, INFO )

template<>
class _xgesv<true> {
public:

    inline static void f( INTEGER * N, INTEGER * NRHS,
                          float * A, INTEGER * LDA,
                          INTEGER * IPIV,
                          float * B, INTEGER * LDB, 
                          INTEGER * INFO)
    {
      SGESV(N, NRHS, A, LDA, IPIV, B, LDB, INFO );
    }
};

template<>
class _xgesv<false> {
public:
    inline static void f( INTEGER * N, INTEGER * NRHS,
                          double * A, INTEGER * LDA,
                          INTEGER * IPIV,
                          double * B, INTEGER * LDB, 
                          INTEGER * INFO)
    {
      DGESV(N, NRHS, A, LDA, IPIV, B, LDB, INFO );
    }
};

template<class real>
void MatrixLUSolve(int n, int nRhs, real * mtx, real * x, real * b)
{
  real * A = (real*) malloc (sizeof(real) * n * n);
  if (!A)
  {
    printf("Error: failed to allocate A.\n");
    throw 1;
  }
  memcpy(A, mtx, sizeof(real) * n * n);

  INTEGER N = n;
  INTEGER NRHS = nRhs;
  INTEGER LDA = n;

  memcpy(x, b, sizeof(real) * n * nRhs);
  real * B = x;

  INTEGER * IPIV = (INTEGER*) malloc (sizeof(INTEGER) * N);
  if (!IPIV)
  {
    printf("Error: failed to allocate IPIV.\n");
    free(A);
    throw 3;
  }
 
  INTEGER LDB = n;
  INTEGER INFO;

  _xgesv<sizeof(real)==sizeof(float)>::f 
                 (&N, &NRHS, A, &LDA, IPIV, B, &LDB, &INFO);

  if (INFO != 0)
  {
    int code = INFO;
    printf("Error: xGESV solver returned non-zero exit code: %d.\n", code);
    free(IPIV);
    free(A);
    throw 4;
  }

  free(IPIV);
  free(A);
}

template<bool C>
class _xsyev {};

//SUBROUTINE DSYEV( JOBZ, UPLO, N, A, LDA, W, WORK, LWORK, INFO )
template<>
class _xsyev<true> {
public:

    inline static void f( char * JOBZ, char * UPLO, INTEGER * N,
                          float * A, INTEGER * LDA, float * W, 
                          float * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      SSYEV( JOBZ, UPLO, N, A, LDA, W, WORK, LWORK, INFO );
    }
};


template<>
class _xsyev<false> {
public:

    inline static void f( char * JOBZ, char * UPLO, INTEGER * N,
                          double * A, INTEGER * LDA, double * W, 
                          double * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      DSYEV( JOBZ, UPLO, N, A, LDA, W, WORK, LWORK, INFO );
    }
};

template<class real>
void SymmetricMatrixEigenDecomposition(int m, real * mtx, real * Q, real * Lambda)
{
  char JOBZ = 'V';
  char UPLO = 'U';
  INTEGER N = m;

  memcpy(Q, mtx, sizeof(real) * m * m);

  real * A = Q;

  INTEGER LDA = m;
  real * W = Lambda;

  INTEGER NB = 32;
  INTEGER LWORK = (NB+2)*N;

  real * WORK = (real*) malloc (sizeof(real) * LWORK);
  
  INTEGER INFO;

  _xsyev<sizeof(real)==sizeof(float)>::f(&JOBZ, &UPLO, &N, A, &LDA, W, WORK, &LWORK, &INFO); 

  if (INFO != 0)
  {
    int code = INFO;
    printf("Error: xSYEV solver returned non-zero exit code: %d.\n", code); fflush(NULL);
    free(WORK);
    throw 1;
  }

  free(WORK);
}

template<bool C>
class _xsygv {};

//SUBROUTINE  DSYGV( ITYPE, JOBZ, UPLO, N, A, LDA, B, LDB, W, WORK, LWORK, INFO )

template<>
class _xsygv<true> {
public:

    inline static void f( INTEGER * ITYPE, char * JOBZ, char * UPLO, INTEGER * N,
                          float * A, INTEGER * LDA, float * B, INTEGER * LDB, 
                          float * W, float * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      SSYGV( ITYPE, JOBZ, UPLO, N, A, LDA, B, LDB, W, WORK, LWORK, INFO );
    }
};


template<>
class _xsygv<false> {
public:

    inline static void f( INTEGER * ITYPE, char * JOBZ, char * UPLO, INTEGER * N,
                          double * A, INTEGER * LDA, double * B, INTEGER * LDB, 
                          double * W, double * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      DSYGV( ITYPE, JOBZ, UPLO, N, A, LDA, B, LDB, W, WORK, LWORK, INFO );
    }
};

template<class real>
void SymmetricMatrixGeneralEigenDecomposition(int m, real * mtx, real * mtx2, real * Q, real * Lambda)
{
  int ITYPE = 1;
  char JOBZ = 'V';
  char UPLO = 'U';
  int LWORK = 2 * (3 * m - 1);
  real * WORK = (real*) malloc (sizeof(real) * LWORK);
  int INFO;

  memcpy(Q, mtx, sizeof(real) * m * m);
  real * A = Q;
  real * B = mtx2;

  _xsygv<sizeof(real)==sizeof(float)>::f( &ITYPE, &JOBZ, &UPLO, &m, A, &m, B, &m, Lambda, WORK, &LWORK, &INFO );

  if (INFO != 0)
  {
    int code = INFO;
    printf("Error: xSYGV solver returned non-zero exit code: %d.\n", code); fflush(NULL);
    free(WORK);
    throw 1;
  }

  free(WORK);
}

template<bool C>
class _xgeev {};

//SUBROUTINE DGEEV( JOBVL, JOBVR, N, A, LDA, WR, WI, VL, LDVL, VR,
//                    LDVR, WORK, LWORK, INFO )

template<>
class _xgeev<true> {
public:

    inline static void f( char * JOBVL, char * JOBVR, INTEGER * N,
                          float * A, INTEGER * LDA, float * WR, float * WI,  
                          float * VL, INTEGER * LDVL, float * VR, INTEGER * LDVR,
                          float * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      SGEEV( JOBVL, JOBVR, N, A, LDA, WR, WI, VL, LDVL, VR,
                    LDVR, WORK, LWORK, INFO );
    }
};


template<>
class _xgeev<false> {
public:
    inline static void f( char * JOBVL, char * JOBVR, INTEGER * N,
                          double * A, INTEGER * LDA, double * WR, double * WI,  
                          double * VL, INTEGER * LDVL, double * VR, INTEGER * LDVR,
                          double * WORK, INTEGER * LWORK, INTEGER * INFO)
    {
      DGEEV( JOBVL, JOBVR, N, A, LDA, WR, WI, VL, LDVL, VR,
                    LDVR, WORK, LWORK, INFO );
    }
};

template<class real>
int MatrixEigenDecomposition(int m, real * mtx, real * EigenVectors, real * LambdaRe, real * LambdaIm)
{
  char JOBVL = 'N';
  char JOBVR = 'V';
  INTEGER N = m;

  real * A = (real*) malloc (sizeof(real) * m * m);
  memcpy(A, mtx, sizeof(real) * m * m);
  INTEGER LDA = m;

  real * WR = LambdaRe;
  real * WI = LambdaIm;

  real * VL = NULL;
  INTEGER LDVL = m;

  real * VR = EigenVectors;
  INTEGER LDVR = m;

  INTEGER LWORK = 16*N;

  real * WORK = (real*) malloc (sizeof(real) * LWORK);
  
  INTEGER INFO;

  _xgeev<sizeof(real)==sizeof(float)>::f(&JOBVL, &JOBVR, &N,
     A, &LDA, WR, WI, VL, &LDVL, VR, &LDVR, WORK, &LWORK, &INFO); 

  if (INFO != 0)
  {
    int code = INFO;
    printf("Warning: xGEEV solver returned non-zero exit code: %d.\n", code);
  }

  free(WORK);
  return INFO;
}

template<class real>
void MatrixSVD(int m, int n, real * mtx, real * U, real * Sigma, real * VT)
{
  real * A = (real*) malloc (sizeof(real) * m * n);
  memcpy(A, mtx, sizeof(real) * m * n);

  // must deal with transpose since Intel MKL sometimes crashes on thin matrices
  bool transpose = (m > n);
  if (transpose)
  {
    InPlaceTransposeMatrix(m, n, A);

    // swap arguments
    int buffer = m;
    m = n;
    n = buffer;

    real * bufferr = U;
    U = VT;
    VT = bufferr;
  }

  // now, we always have m <= n

  char jobu  = 'S'; //left singular vectors returned in U
  char jobvt = 'S'; //right singular vectors returned in VT

  INTEGER NB = 32; // optimal block size; could also call ilaenv
  int lwork = NB*MAX(3*MIN( m, n)+MAX(m,n), 5*MIN(m,n)-4);

  real * work = (real*) malloc (sizeof(real) * lwork);
  if (!work)
  {
    printf("Error: failed to allocate workspace.\n");
    throw 1;
  }

  //printf("Workspace size is: %G Mb .\n",1.0 * lwork * sizeof(int) / 1024 / 1024);

  INTEGER M = m;
  INTEGER N = n;
  INTEGER LDA = m;
  INTEGER LDU = m;
  INTEGER LDVT = MIN(m,n);
  INTEGER LWORK = lwork;
  INTEGER INFO;

  //printf("Calling LAPACK dgesvd routine...\n");fflush(NULL);

  //SUBROUTINE SGESVD( JOBU, JOBVT, M, N, A, LDA, S, U, LDU, VT, LDVT, WORK, LWORK, INFO )

  _xgesvd<sizeof(real)==sizeof(float)>::f 
                 (&jobu, &jobvt, &M, &N, A, &LDA,
                  Sigma, U, &LDU, VT,
                  &LDVT, work, &LWORK, &INFO);

  if (INFO != 0)
  {
    int code = INFO;
    printf("Error: SVD solver returned non-zero exit code: %d.\n", code);
    free(work);
    free(A);
    throw 2;
  }

  free(work);
  free(A);

  if (transpose)
  {
    InPlaceTransposeMatrix(m, MIN(m,n), U);
    InPlaceTransposeMatrix(MIN(m,n), n, VT);
  }
}

template float * InverseMatrix(int m, float * mtx, float * output);
template double * InverseMatrix(int m, double * mtx, double * output);
template float * PseudoInverseMatrix(int m, int n, float * mtx, float singularValueThreshold, int * rank, float * output);
template double * PseudoInverseMatrix(int m, int n, double * mtx, double singularValueThreshold, int * rank, double * output);
template float * MatrixLeastSquareSolve(int m, int n, int nRhs, float * mtx, float * b, float rcond, int * rank, float * output);
template double * MatrixLeastSquareSolve(int m, int n, int nRhs, double * mtx, double * b, double rcond, int * rank, double * output);
template void SymmetricMatrixEigenDecomposition(int m, float * mtx, float * Q, float * Lambda);
template void SymmetricMatrixEigenDecomposition(int m, double * mtx, double * Q, double * Lambda);
template void SymmetricMatrixGeneralEigenDecomposition(int m, float * mtx, float * mtx2, float * Q, float * Lambda);
template void SymmetricMatrixGeneralEigenDecomposition(int m, double * mtx, double * mtx2, double * Q, double * Lambda);
template int MatrixEigenDecomposition(int m, float * mtx, float * EigenVectors, float * LambdaRe, float * LambdaIm);
template int MatrixEigenDecomposition(int m, double * mtx, double * EigenVectors, double * LambdaRe, double * LambdaIm);
template void MatrixSVD(int m, int n, float * mtx, float * U, float * Sigma, float * VT);
template void MatrixSVD(int m, int n, double * mtx, double * U, double * Sigma, double * VT);
template void MatrixLUSolve(int n, int nRhs, float * mtx, float * x, float * b);
template void MatrixLUSolve(int n, int nRhs, double * mtx, double * x, double * b);

