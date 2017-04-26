/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "Large Modal Deformation Factory",                                    *
 * a pre-processing utility for model reduction of                       *
 * deformable objects undergoing large deformations.                     *
 *                                                                       *
 *  Copyright (C) 2007 CMU, 2009 MIT, 2016 USC                           *
 *                                                                       *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Hongyi Xu                                *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Fun Shing Sin, Daniel Schroeder,             *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
 *          Zumberge Research and Innovation Fund at USC                 *
 *                                                                       *
 * This utility is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This utility is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;
#include "ARPACKSolver.h"
#include "invMKSolver.h"
#include "invZTAZSolver.h"
#include "invZTAZMSolver.h"
#include "ZTAZMultiplicator.h"
#include "lapack-headers.h"

//#define SPOOLES
#define PARDISO

#define DSAUPD dsaupd_
#define DSEUPD dseupd_
#define INTEGER int

/* Note: 
  This code is now independent of ARPACK++ and calls ARPACK directly. It has been tested and works fine.

  Previously, it used ARPACK++, which, while convenient, required installing ARPACK++ (which required
  editing some of its headers files to bring it up to date wit today's C compilers), and
  only worked under Windows and Linux. Under Mac, it lead to strange errors inside ARPACK.
*/

// always keep this undefined
//#define USEARPACKPLUSPLUS

#ifdef USEARPACKPLUSPLUS
  #include "argsym.h"
#else
  extern "C"
  {
  void DSAUPD(INTEGER * IDO, char * BMAT, INTEGER * N, char * WHICH, INTEGER * NEV,
    double * TOL, double * RESID, INTEGER * NCV, double * V, INTEGER * LDV, INTEGER * IPARAM,
    INTEGER * IPNTR, double * WORKD, double * WORKL, INTEGER * LWORKL, INTEGER * INFO);

  // call DSAUPD 
  //c     ( IDO, BMAT, N, WHICH, NEV, TOL, RESID, NCV, V, LDV, IPARAM,
  //c       IPNTR, WORKD, WORKL, LWORKL, INFO )

  void DSEUPD(
    INTEGER * RVEC, char * HOWMNY, INTEGER * SELECT, double * D, double * Z, INTEGER * LDZ, double * SIGMA,
    char * BMAT, INTEGER * N, char * WHICH, INTEGER * NEV,
    double * TOL, double * RESID, INTEGER * NCV, double * V, INTEGER * LDV, INTEGER * IPARAM,
    INTEGER * IPNTR, double * WORKD, double * WORKL, INTEGER * LWORKL, INTEGER * INFO);

  //c  call DSEUPD  
  //c     ( RVEC, HOWMNY, SELECT, D, Z, LDZ, SIGMA, BMAT, N, WHICH, NEV, TOL,
  //c       RESID, NCV, V, LDV, IPARAM, IPNTR, WORKD, WORKL, LWORKL, INFO )
}
#endif

#ifdef SPOOLES
  #include "SPOOLESSolver.h"
  #include "SPOOLESSolverMT.h"
#endif

#ifdef PARDISO
  #include "PardisoSolver.h"
#endif

int ARPACKSolver::SolveGenEigReg(SparseMatrix * KInput, SparseMatrix * MInput, int numEigenvalues, double * eigenvalues, double * eigenvectors, const char * mode, int numLinearSolverThreads, int verbose)
{
  int np = KInput->Getn();
  if (np != MInput->Getn())
    return -1;

  if ((strcmp(mode, "SM") != 0) && (strcmp(mode, "LM") != 0))
    return -1;

  bool largestMagnitude = (strcmp(mode, "LM") == 0);
  SparseMatrix * K;
  SparseMatrix * M;
  if (largestMagnitude)
  {
    K = KInput;
    M = MInput;
  }
  else
  {
    // swap K and M to get the smallest eigenvalues
    K = MInput;
    M = KInput;
  }

  // solve Kx = lambda Mx with ARPACK
  // need multiplication with M^{-1} K and with M

  // create M^{-1} solver
  LinearSolver * invMSolver = NULL;
  #ifdef SPOOLES
    if (numLinearSolverThreads == 0)
    {
      if (verbose >= 1)
        printf("Linear solver: SPOOLES\n");
      invMSolver = new SPOOLESSolver(M, verbose);
    }
    else
    {
      if (verbose >= 1)
        printf("Linear solver: SPOOLES (%d threads).\n", numLinearSolverThreads);
      invMSolver = new SPOOLESSolverMT(M, numLinearSolverThreads, verbose);
    }
  #endif

  #ifdef PARDISO
    if (verbose >= 1)
      printf("Linear solver: PARDISO (%d threads).\n", (numLinearSolverThreads == 0) ? 1 : numLinearSolverThreads);

    int directIterative = 0;
    PardisoSolver * pardisoSolver = new PardisoSolver(M, numLinearSolverThreads, PardisoSolver::REAL_SYM_INDEFINITE,
      PardisoSolver::NESTED_DISSECTION, directIterative, verbose);
    pardisoSolver->FactorMatrix(M);
    invMSolver = pardisoSolver;
  #endif

  if (invMSolver == NULL)
  {
    printf("Error: no linear solver specified in SolveGenEigReg.\n");
    return 1;
  }

  // create M^{-1} K solver
  InvMKSolver invMKSolver(invMSolver, K);

  #ifdef USEARPACKPLUSPLUS
/*
    ARSymGenEig(int np, int nevp, ARFOP* objOPp,
              void (ARFOP::* MultOPxp)(ARFLOAT[], ARFLOAT[]), ARFB* objBp,
              void (ARFB::* MultBxp)(ARFLOAT[], ARFLOAT[]),
              char* whichp = "LM", int ncvp = 0, ARFLOAT tolp = 0.0,
              int maxitp = 0, ARFLOAT* residp = NULL, bool ishiftp = true);
*/
    ARSymGenEig<double, InvMKSolver, SparseMatrix> solver
      (np, numEigenvalues, 
       &invMKSolver, &InvMKSolver::ComputeInvMK,
       M, (void (SparseMatrix::*)(double*,double*)) &SparseMatrix::MultiplyVector, "LM");

    int nconv = solver.EigenValVectors(eigenvectors, eigenvalues);
  #else
    const int maxIter = 10000;

    // call ARPACK
    INTEGER IDO = 0;
    char BMAT = 'G';
    INTEGER N = np;
    char WHICH[3] = "LM"; 
    INTEGER NEV = numEigenvalues;
    double TOL = 0.0;
    double * RESID = (double*) malloc (sizeof(double) * N);
    INTEGER NCV = 3 * NEV;
    if (NCV > N)
      NCV = N;
    double * V = (double*) malloc (sizeof(double) * N * NCV);
    INTEGER LDV = N;
    INTEGER IPARAM[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    IPARAM[0] = 1; // no user-provided shifts
    IPARAM[2] = maxIter; 
    IPARAM[3] = 1;
    //IPARAM[4] = 0;
    IPARAM[6] = 2; // the mode (regular generalized eigenproblem)
    INTEGER IPNTR[11]; 
    double * WORKD = (double*) malloc (sizeof(double) * 3 * N);
    INTEGER LWORKL = 2 * (NCV*NCV + 8*NCV); // at least NCV**2 + 8*NCV; 
    double * WORKL = (double*) malloc (sizeof(double) * LWORKL);
    INTEGER INFO = 0;

    double * buffer = (double*) malloc (sizeof(double) * N);
  
    do
    {
      //printf("Entering dsaupd...\n"); fflush(NULL);
      DSAUPD(&IDO, &BMAT, &N, WHICH, &NEV, &TOL, RESID, &NCV, V, &LDV, IPARAM, IPNTR, WORKD, WORKL, &LWORKL, &INFO);
      if (INFO != 0)
      {
        printf("Error: DSAUPD returned non-zero exit code %d .\n", (int)INFO);
        delete(invMSolver);
        return -1;
      }

      //printf("IDO=%d\n", (int)IDO); fflush(NULL);
  
      switch(IDO)
      {
        case -1:
          invMKSolver.ComputeInvMK(&WORKD[IPNTR[0]-1], &WORKD[IPNTR[1]-1]);
        break;

        case 1:
          invMKSolver.ComputeInvMK(&WORKD[IPNTR[0]-1], &WORKD[IPNTR[1]-1]);
        break;

        case 2:
          M->MultiplyVector(&WORKD[IPNTR[0]-1], &WORKD[IPNTR[1]-1]);
        break;

        case 3:
          printf("Error: case IDO=3 should have never happened.\n");
          delete(invMSolver);
          return -1;
        break;

        case 99:
        break;

        default:
          printf("Error: unknown case.\n");
          delete(invMSolver);
          return -1;
        break;
      };
    }
    while (IDO != 99);

    // obtain the eigenvalues and eigenvectors
    INTEGER RVEC = 1;
    char HOWMNY = 'A'; // all eigenvectors
    INTEGER * SELECT = (INTEGER*) malloc (sizeof(INTEGER) * NCV);
    double * D = eigenvalues;
    double * Z = eigenvectors;
    INTEGER LDZ = N;
    double * SIGMA = NULL;
    DSEUPD(&RVEC, &HOWMNY, SELECT, D, Z, &LDZ, SIGMA,
      &BMAT, &N, WHICH, &NEV, &TOL, RESID, &NCV, V, &LDV, IPARAM, IPNTR, WORKD, WORKL, &LWORKL, &INFO);
  
    free(SELECT); 
    free(RESID);
    free(V);
    free(WORKD);
    free(WORKL);
    free(buffer);

    int nconv = IPARAM[4];
  #endif

  // normalize results
  for(int i=0; i<nconv; i++)
    MInput->NormalizeVector(&eigenvectors[np*i]);

  //solver.FindEigenvectors();
  //nconv = solver.ConvergedEigenvalues();

  if (!largestMagnitude)
  {
    for(int i=0; i<nconv; i++)
      eigenvalues[i] = 1.0 / eigenvalues[i];

    // reverse eigenvalues (and appropriate eigenvectors)
    for(int i=0; i< numEigenvalues / 2; i++)
    {
      // swap i and numEigenvalues-1-i
      double temp = eigenvalues[i];
      eigenvalues[i] = eigenvalues[numEigenvalues-1-i];
      eigenvalues[numEigenvalues-1-i] = temp;

      for(int j=0; j<np; j++)
      {
        temp = eigenvectors[np*i+j];
        eigenvectors[np*i+j] = eigenvectors[np*(numEigenvalues-1-i) + j];
        eigenvectors[np*(numEigenvalues-1-i) + j] = temp;
      }
    }
  }

  if (verbose >= 1)
  {
    #ifdef USEARPACKPLUSPLUS
      cout << "Dimension of the system            : " << np              << endl;
      cout << "Number of 'requested' eigenvalues  : " << solver.GetNev()  << endl;
      cout << "Number of 'converged' eigenvalues  : " << nconv          << endl;
      cout << "Number of Arnoldi vectors generated: " << solver.GetNcv()  << endl;
      cout << "Number of iterations taken         : " << solver.GetIter() << endl;
    #else
      cout << "Dimension of the system            : " << np              << endl;
      cout << "Number of 'requested' eigenvalues  : " << NEV << endl;
      cout << "Number of 'converged' eigenvalues  : " << nconv          << endl;
      cout << "Number of Arnoldi vectors generated: " << NCV << endl;
      cout << "Number of iterations taken         : " << IPARAM[2] << endl;
      cout << endl;
    #endif

    // Printing eigenvalues.

    cout << "Eigenvalues:" << endl;
    //for (int i=numEigenvalues-nconv; i<numEigenvalues; i++) 
    for (int i=0; i<nconv; i++) 
    {
      cout << "  lambda[" << (i+1) << "]: " << eigenvalues[i] << endl;
    }
    cout << endl;

    // Printing the residual norm || A*x - lambda*B*x ||
    // for the nconv accurately computed eigenvectors.

    double * Ax      = new double[np];
    double * Bx      = new double[np];
    double * ResNorm = new double[nconv];

    double infinityNormK = KInput->GetInfinityNorm();
    double infinityNormM = MInput->GetInfinityNorm();
    double infNorm = infinityNormK;
    if (infinityNormM > infNorm)
      infNorm = infinityNormM;

    for (int i=0; i<nconv; i++) 
    {
      KInput->MultiplyVector(&eigenvectors[np*i],Ax);
      MInput->MultiplyVector(&eigenvectors[np*i],Bx);
      for(int j=0; j<np; j++)
        Ax[j] = Ax[j] - eigenvalues[i] * Bx[j];
      //cblas_daxpy(np, -eigenvalues[i], Bx, 1, Ax, 1);
      ResNorm[i] = 0;
      for(int j=0; j<np; j++)
        ResNorm[i] += Ax[j] * Ax[j];
      ResNorm[i] = sqrt(ResNorm[i]) / fabs(eigenvalues[i]) / infNorm;
      //ResNorm[i] = cblas_dnrm2(np, Ax, 1) / fabs(eigenvalues[i]);
    }

/*
    for (int i=0; i<nconv; i++) 
    {
      cout << "||A*x(" << (i+1) << ") - lambda(" << (i+1);
      cout << ")*B*x(" << (i+1) << ")|| / |lambda| / max(||A||,||B||) = " << ResNorm[i] << endl;
    }
    cout << endl;
*/

    //printf("Cleaning up ARPACK workspace.\n");fflush(NULL);
    delete[] Ax;
    delete[] Bx;
    delete[] ResNorm;
  }

  delete(invMSolver);

  return nconv;
}

int ARPACKSolver::SolveGenEigShInv(SparseMatrix * K, SparseMatrix * M, int numEigenvalues, double * eigenvalues, double * eigenvectors, double sigma, int numLinearSolverThreads, int verbose)
{
  int np = K->Getn();
  if (np != M->Getn())
    return -1;

  // solve Kx = lambda Mx with ARPACK, shift-invert mode (mode number 3)
  // need multiplication with (K-sigma*M)^{-1}, (K-sigma*M)^{-1} M, and with M

  SparseMatrix * KsigmaM = K;
  if (sigma != 0)
  {
    // compute KsigmaM = K - sigma * M
    KsigmaM = new SparseMatrix(*K); 
    KsigmaM->BuildSubMatrixIndices(*M);
    KsigmaM->AddSubMatrix(-sigma, *M);
  }

  // create (K-sigma*M)^{-1} solver
  LinearSolver * invKSolver = NULL;

  #ifdef SPOOLES
    if (numLinearSolverThreads == 0)
    {
      if (verbose >= 1)
        printf("Linear solver: SPOOLES\n");
      invKSolver = new SPOOLESSolver(KsigmaM, verbose);
    }
    else
    {
      if (verbose >= 1)
        printf("Linear solver: SPOOLES (%d threads).\n", numLinearSolverThreads);
      invKSolver = new SPOOLESSolverMT(KsigmaM, numLinearSolverThreads, verbose);
    }
  #endif

  #ifdef PARDISO
    if (verbose >= 1)
      printf("Linear solver: PARDISO (%d threads).\n", (numLinearSolverThreads == 0) ? 1 : numLinearSolverThreads);
    int directIterative = 0;
    PardisoSolver * pardisoSolver = new PardisoSolver(KsigmaM, numLinearSolverThreads, PardisoSolver::REAL_SYM_INDEFINITE,
      PardisoSolver::NESTED_DISSECTION, directIterative, verbose);
    pardisoSolver->FactorMatrix(KsigmaM);
    invKSolver = pardisoSolver;
  #endif

  if (invKSolver == NULL)
  {
    printf("Error: no linear solver specified in SolveGenEigShInv.\n");
    return 1;
  }

  // create (K-sigma*M)^{-1}*M solver
  InvMKSolver invKMSolver(invKSolver, M);

  const int maxIter = 10000;

  // call ARPACK
  INTEGER IDO = 0;
  char BMAT = 'G';
  INTEGER N = np;
  char WHICH[3] = "LM"; 
  INTEGER NEV = numEigenvalues;
  double TOL = 0.0;
  double * RESID = (double*) malloc (sizeof(double) * N);
  INTEGER NCV = 3 * NEV;
  if (NCV > N)
    NCV = N;
  double * V = (double*) malloc (sizeof(double) * N * NCV);
  INTEGER LDV = N;
  INTEGER IPARAM[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  IPARAM[0] = 1; // no user-provided shifts
  IPARAM[2] = maxIter; 
  IPARAM[3] = 1;
  IPARAM[6] = 3; // the mode (shift-inverted generalized eigenproblem)
  INTEGER IPNTR[11]; 
  double * WORKD = (double*) malloc (sizeof(double) * 3 * N);
  INTEGER LWORKL = 2 * (NCV*NCV + 8*NCV); // at least NCV**2 + 8*NCV; 
  double * WORKL = (double*) malloc (sizeof(double) * LWORKL);
  INTEGER INFO = 0;

  double * buffer = (double*) malloc (sizeof(double) * N);
  
  if (verbose >= 1)
  {
    cout << "Dimension of the system            : " << np  << endl;
    cout << "Number of 'requested' eigenvalues  : " << NEV << endl;
    cout << "Entering the ARPACK eigenvalue routine..." << endl;
	fflush(NULL);
  }

  do
  {
    DSAUPD(&IDO, &BMAT, &N, WHICH, &NEV, &TOL, RESID, &NCV, V, &LDV, IPARAM, IPNTR, WORKD, WORKL, &LWORKL, &INFO);
    if (INFO != 0)
    {
      printf("Error: DSAUPD returned non-zero exit code %d .\n", (int)INFO);
      delete(invKSolver);
      return -1;
    }

    //printf("IDO=%d\n", (int)IDO); fflush(NULL);
    //c           ===> OP = (inv[K - sigma*M])*M  and  B = M. 
  
    switch(IDO)
    {
      case -1:
//c          IDO = -1: compute  Y = OP * X  where
//c                    IPNTR(1) is the pointer into WORKD for X,
//c                    IPNTR(2) is the pointer into WORKD for Y.
//c                    This is for the initialization phase to force the
//c                    starting vector into the range of OP.
        //printf("IDO = -1\n");
        invKMSolver.ComputeInvMK(&WORKD[IPNTR[0]-1], &WORKD[IPNTR[1]-1]);
      break;

      case 1:
//c          IDO =  1: compute  Y = (K - sigma*M)^-1 * Z
//c                    IPNTR(2) is the pointer into WORKD for Y,
//c                    IPNTR(3) is the pointer into WORKD for Z.
//c           (see dsdrv4.f example)
        //printf("IDO = 1\n");
        invKSolver->SolveLinearSystem(&WORKD[IPNTR[1]-1], &WORKD[IPNTR[2]-1]);
      break;

      case 2:
//c          IDO =  2: compute  Y = B * X  where
//c                    IPNTR(1) is the pointer into WORKD for X,
//c                    IPNTR(2) is the pointer into WORKD for Y.
        //printf("IDO = 2\n");
        M->MultiplyVector(&WORKD[IPNTR[0]-1], &WORKD[IPNTR[1]-1]);
      break;

      case 3:
        printf("Error: case IDO=3 should have never happened.\n");
        delete(invKSolver);
        return -1;
      break;

      case 99:
      break;

      default:
        printf("Error: unknown case.\n");
        delete(invKSolver);
        return -1;
      break;
    };
  }
  while (IDO != 99);

  // obtain the eigenvalues and eigenvectors
  INTEGER RVEC = 1;
  char HOWMNY = 'A'; // all eigenvectors
  INTEGER * SELECT = (INTEGER*) malloc (sizeof(INTEGER) * NCV);
  double * D = eigenvalues;
  double * Z = eigenvectors;
  INTEGER LDZ = N;
  double SIGMA = sigma;
  DSEUPD(&RVEC, &HOWMNY, SELECT, D, Z, &LDZ, &SIGMA,
    &BMAT, &N, WHICH, &NEV, &TOL, RESID, &NCV, V, &LDV, IPARAM, IPNTR, WORKD, WORKL, &LWORKL, &INFO);
  
  free(SELECT); 
  free(RESID);
  free(V);
  free(WORKD);
  free(WORKL);
  free(buffer);

  if (sigma != 0)
  {
    delete(KsigmaM);
  }

  int nconv = IPARAM[4];

  // normalize results
  for(int i=0; i<nconv; i++)
    M->NormalizeVector(&eigenvectors[np*i]);

  //solver.FindEigenvectors();
  //nconv = solver.ConvergedEigenvalues();

  if (verbose >= 1)
  {
    cout << "ARPACK solver is done." << endl;
    //cout << "Dimension of the system            : " << np              << endl;
    //cout << "Number of 'requested' eigenvalues  : " << NEV << endl;
    cout << "Number of 'converged' eigenvalues  : " << nconv          << endl;
    cout << "Number of Arnoldi vectors generated: " << NCV << endl;
    cout << "Number of iterations taken         : " << IPARAM[2] << endl;
    cout << endl;

    // Printing eigenvalues.

    cout << "Eigenvalues:" << endl;
    //for (int i=numEigenvalues-nconv; i<numEigenvalues; i++) 
    for (int i=0; i<nconv; i++) 
    {
      cout << "  lambda[" << (i+1) << "]: " << eigenvalues[i] << endl;
    }
    cout << endl;

    // Printing the residual norm || A*x - lambda*B*x ||
    // for the nconv accurately computed eigenvectors.

    double * Ax      = new double[np];
    double * Bx      = new double[np];
    double * ResNorm = new double[nconv];

    double infinityNormK = K->GetInfinityNorm();
    double infinityNormM = M->GetInfinityNorm();
    double infNorm = infinityNormK;
    if (infinityNormM > infNorm)
      infNorm = infinityNormM;

    for (int i=0; i<nconv; i++) 
    {
      K->MultiplyVector(&eigenvectors[np*i],Ax);
      M->MultiplyVector(&eigenvectors[np*i],Bx);
      for(int j=0; j<np; j++)
        Ax[j] = Ax[j] - eigenvalues[i] * Bx[j];
      //cblas_daxpy(np, -eigenvalues[i], Bx, 1, Ax, 1);
      ResNorm[i] = 0;
      for(int j=0; j<np; j++)
        ResNorm[i] += Ax[j] * Ax[j];
      ResNorm[i] = sqrt(ResNorm[i]) / fabs(eigenvalues[i]) / infNorm;
      //ResNorm[i] = cblas_dnrm2(np, Ax, 1) / fabs(eigenvalues[i]);
    }

/*
    for (int i=0; i<nconv; i++) 
    {
      cout << "||A*x(" << (i+1) << ") - lambda(" << (i+1);
      cout << ")*B*x(" << (i+1) << ")|| / |lambda| / max(||A||,||B||) = " << ResNorm[i] << endl;
    }
    cout << endl;
*/

    //printf("Cleaning up ARPACK workspace.\n");fflush(NULL);
    delete[] Ax;
    delete[] Bx;
    delete[] ResNorm;
  }

  delete(invKSolver);
  return nconv;
}

int ARPACKSolver::SolveGenEigShInv(SparseMatrix * K, SparseMatrix * M, SparseMatrix * C, int numEigenvalues, double * eigenvalues, double * eigenvectors, double sigma, double eps, int numLinearSolverThreads, int verbose)
{
  int np = K->Getn();
  if (np != M->Getn())
    return -1;

  // convert to dense matrix
  int numCons = C->Getn();
  double * dataC = (double*) malloc (sizeof(double) * np * numCons);
  C->MakeDenseMatrix(dataC, np);

  // do SVD on C
  Matrix<double> CM(numCons, np, dataC, false, false);
  Matrix<double> UM(numCons, numCons);
  Matrix<double> Sigma(numCons, 1);
  double * VT = (double*) malloc (sizeof(double) * np  * numCons);
  Matrix<double> VTM(numCons, np, VT, false, false); // same shape as CM

  CM.SVD(UM, Sigma, VTM);

  // regularize C
  double * sigmaValues = Sigma.GetData();
  int c = 0;
  for(c = 0; c < numCons; c++) // find the rank of matrix C (=c)
  {
    if (sigmaValues[c] < eps)
      break;
  }

  // VT, after only keeping rows 1..c
  double * newC = (double*) malloc (sizeof(double) * np * c);
  int counter = 0;
  for(int i = 0; i < np; i++)
  {
    double * pointer = &VT[numCons * i];
    for(int j = 0; j < c; j++)
    {
      newC[counter] = pointer[j];
      counter++;
    }
  }

  free(dataC);
  free(VT);

  // from now on, we just use newC
  SparseMatrixOutline * POutline = new SparseMatrixOutline(np); // for the permutation matrix
  double * bufferc = (double*) malloc(sizeof(double) * c);
  // indices[i] tells the position of column i after the permutation
  int * indices = (int*) calloc(np, sizeof(int));
  for(int i = 0; i < np; i++)
    indices[i] = i;

  // Gaussian elimination
  for(int i = 0; i < c; i++) // over all rows of newC
  {
    // find column with maximum absolute value in the current row
    double maxValue = 0.0;
    int column = i; // columns 1..i-1 are already zero, because of Gaussian elimination
    for(int j = i; j < np; j++)
    {
      if (fabs(newC[ELT(c, i, j)]) > maxValue)
      {
	maxValue = fabs(newC[ELT(c, i, j)]);
	column = j;
      }
    }
    // now, "column" contains the column with max absolute value

    // swap indices[column] and indices[i]
    int tmp = indices[column];
    indices[column] = indices[i];
    indices[i] = tmp;

    // swap columns i and "column"
    memcpy(bufferc, &newC[ELT(c, 0, column)], sizeof(double) * c);
    memcpy(&newC[ELT(c, 0, column)], &newC[ELT(c, 0, i)],  sizeof(double) * c);
    memcpy(&newC[ELT(c, 0, i)], bufferc,  sizeof(double) * c);

    double value = newC[ELT(c, i, i)];
    for(int j = i+1; j < c; j++)
    {
      double scale = newC[ELT(c, j, i)] / value;
      for(int l = i; l < np; l++)
	newC[ELT(c, j, l)] -= scale * newC[ELT(c, i, l)];
    }
  }

  for(int i = 0; i < np; i++)
    POutline->AddEntry(indices[i], i, 1.0);

  SparseMatrix * P = new SparseMatrix(POutline);
  delete(POutline);

  free(indices);
  free(bufferc);

  // form Cp and Cn
  double * Cp = &newC[0];
  double * Cn = &newC[c*c];

  // solve Kx = lambda Mx with ARPACK, shift-invert mode (mode number 3)
  // need multiplication with (K-sigma*M)^{-1}, (K-sigma*M)^{-1} M, and with M
  SparseMatrix * KsigmaM = K;
  if (sigma != 0)
  {
    // compute KsigmaM = K - sigma * M
    KsigmaM = new SparseMatrix(*K);
    KsigmaM->BuildSubMatrixIndices(*M);
    KsigmaM->AddSubMatrix(-sigma, *M);
  }

  int npc = np - c;
  Matrix<double> CnM (c, npc, Cn);
  Matrix<double> CpM (c, c, Cp);
  Matrix<double> invCpM = Inverse(CpM);

  // form the nullspace Z
  double * ZUpper = (double*) malloc (sizeof(double) * npc * c);
  Matrix<double> ZupperM(c, npc, ZUpper, false, false);
  ZupperM = invCpM * CnM;
  ZupperM *= -1;

  SparseMatrix * PKP = new SparseMatrix(KsigmaM->ConjugateMatrix(*P, 0, M->Getn()));

  //thresholded Z, used as the preconditioner
  SparseMatrixOutline * spZOutline = new SparseMatrixOutline(np);
  for(int i = 0; i < c; i++)
  {
    for(int j = 0; j < np-c; j++)
    {
      if (ZUpper[ELT(c, i, j)] > 1E-10)
	spZOutline->AddEntry(i, j, ZUpper[ELT(c, i, j)]);
    }
  }

  for(int i = c ; i < np; i++)
    spZOutline->AddEntry(i, i-c, 1.0);

  SparseMatrix * spZ = new SparseMatrix(spZOutline);
  delete(spZOutline);

  SparseMatrix * ZKZ = new SparseMatrix(PKP->ConjugateMatrix(*spZ, 0, npc));

  free(ZUpper);
  delete(PKP);
  delete(spZ);

  int directIterative = 0;
  PardisoSolver * pardisoSolver = new PardisoSolver(ZKZ, numLinearSolverThreads, PardisoSolver::REAL_SYM_INDEFINITE,
    PardisoSolver::NESTED_DISSECTION, directIterative, verbose);
  pardisoSolver->FactorMatrix(ZKZ);

  // create M* multiplicator
  ZTAZMultiplicator Mmult(M, P, &invCpM, &CnM);

  // create (M)^{-1} solver
  InvZTAZSolver invZTAZSolver(KsigmaM, pardisoSolver, P, &invCpM, &CnM);

  // create (M)^{-1}*K solver
  InvZTAZMSolver invZTAZMSolver(KsigmaM, M, pardisoSolver, P, &invCpM, &CnM);
  const int maxIter = 10000;

  // call ARPACK
  INTEGER IDO = 0;
  char BMAT = 'G';
  INTEGER N = npc;
  char WHICH[3] = "LM";
  INTEGER NEV = numEigenvalues;
  double TOL = 0.0;
  double * RESID = (double*) malloc (sizeof(double) * N);
  INTEGER NCV = 3 * NEV;
  if (NCV > N)
    NCV = N;
  double * V = (double*) malloc (sizeof(double) * N * NCV);
  INTEGER LDV = N;
  INTEGER IPARAM[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  IPARAM[0] = 1; // no user-provided shifts
  IPARAM[2] = maxIter;
  IPARAM[3] = 1;
  IPARAM[6] = 3; // the mode (shift-inverted generalized eigenproblem)
  INTEGER IPNTR[11];
  double * WORKD = (double*) malloc (sizeof(double) * 3 * N);
  INTEGER LWORKL = 2 * (NCV*NCV + 8*NCV); // at least NCV**2 + 8*NCV; 
  double * WORKL = (double*) malloc (sizeof(double) * LWORKL);
  INTEGER INFO = 0;

  double * buffer = (double*) malloc (sizeof(double) * N);

  if (verbose >= 1)
  {
    cout << "Dimension of the system            : " << npc  << endl;
    cout << "Number of 'requested' eigenvalues  : " << NEV << endl;
    cout << "Entering the ARPACK eigenvalue routine..." << endl;
    fflush(NULL);
  }

  do
  {
    DSAUPD(&IDO, &BMAT, &N, WHICH, &NEV, &TOL, RESID, &NCV, V, &LDV, IPARAM, IPNTR, WORKD, WORKL, &LWORKL, &INFO);
    if (INFO != 0)
    {
      printf("Error: DSAUPD returned non-zero exit code %d .\n", (int)INFO);
      delete(pardisoSolver);
      delete(P);
      free(newC);
      delete(ZKZ);
      return -1;
    }

    //printf("IDO=%d\n", (int)IDO); fflush(NULL);
    //c           ===> OP = (inv[K - sigma*M])*M  and  B = M. 

    switch(IDO)
    {
      case -1:
	//c          IDO = -1: compute  Y = OP * X  where
	//c                    IPNTR(1) is the pointer into WORKD for X,
	//c                    IPNTR(2) is the pointer into WORKD for Y.
	//c                    This is for the initialization phase to force the
	//c                    starting vector into the range of OP.
	//printf("IDO = -1\n");
	invZTAZMSolver.ComputeInvZTAZM(&WORKD[IPNTR[0]-1], &WORKD[IPNTR[1]-1]);
	break;

      case 1:
	//c          IDO =  1: compute  Y = (K - sigma*M)^-1 * Z
	//c                    IPNTR(2) is the pointer into WORKD for Y,
	//c                    IPNTR(3) is the pointer into WORKD for Z.
	//c           (see dsdrv4.f example)
	//printf("IDO = 1\n");
	invZTAZSolver.ComputeInvZTAZ(&WORKD[IPNTR[1]-1], &WORKD[IPNTR[2]-1]);
	break;

      case 2:
	//c          IDO =  2: compute  Y = B * X  where
	//c                    IPNTR(1) is the pointer into WORKD for X,
	//c                    IPNTR(2) is the pointer into WORKD for Y.
	//printf("IDO = 2\n");
	Mmult.Multiply(&WORKD[IPNTR[0]-1], &WORKD[IPNTR[1]-1]);
	break;

      case 3:
	printf("Error: case IDO=3 should have never happened.\n");
        delete(pardisoSolver);
        delete(P);
        free(newC);
        delete(ZKZ);
	return -1;
	break;

      case 99:
	break;

      default:
	printf("Error: unknown case.\n");
        delete(pardisoSolver);
        delete(P);
        free(newC);
        delete(ZKZ);
	return -1;
	break;
    };
  }
  while (IDO != 99);

  // obtain the eigenvalues and eigenvectors
  INTEGER RVEC = 1;
  char HOWMNY = 'A'; // all eigenvectors
  INTEGER * SELECT = (INTEGER*) malloc (sizeof(INTEGER) * NCV);
  double * D = eigenvalues;
  double * Z = eigenvectors;
  INTEGER LDZ = N;
  double SIGMA = sigma;
  DSEUPD(&RVEC, &HOWMNY, SELECT, D, Z, &LDZ, &SIGMA,
      &BMAT, &N, WHICH, &NEV, &TOL, RESID, &NCV, V, &LDV, IPARAM, IPNTR, WORKD, WORKL, &LWORKL, &INFO);

  free(SELECT);
  free(RESID);
  free(V);
  free(WORKD);
  free(WORKL);
  free(buffer);

  if (sigma != 0)
    delete(KsigmaM);

  int nconv = IPARAM[4];

  /*
     Multiply the constrained eigenvectors with Z: 
     Z = P [ -C_p^{-1} C_n  ]
           [  I             ]
   */

  double * buffer2 = (double*) malloc(sizeof(double) * np * nconv);
  for(int i = 0; i < nconv; i++)
  {
    Matrix<double> eM(npc, 1, &eigenvectors[npc*i], false, false);
    Matrix<double> bcM(c, 1, &buffer2[np*i], false, false);
    bcM = invCpM * (CnM * eM);
    bcM *= -1.0;
    for(int j = 0; j < npc; j++)
      buffer2[np*i+c+j] = eigenvectors[npc*i+j];
  }

  for(int i = 0; i < nconv; i++)
    P->MultiplyVector(&buffer2[np*i], &eigenvectors[np*i]);

  free(buffer2);

  // normalize results
  for(int i=0; i<nconv; i++)
    M->NormalizeVector(&eigenvectors[np*i]);
  //solver.FindEigenvectors();
  //nconv = solver.ConvergedEigenvalues();

  if (verbose >= 1)
  {
    cout << "ARPACK solver is done." << endl;
    //cout << "Dimension of the system            : " << np              << endl;
    //cout << "Number of 'requested' eigenvalues  : " << NEV << endl;
    cout << "Number of 'converged' eigenvalues  : " << nconv          << endl;
    cout << "Number of Arnoldi vectors generated: " << NCV << endl;
    cout << "Number of iterations taken         : " << IPARAM[2] << endl;
    cout << endl;

    // Printing eigenvalues.

    cout << "Eigenvalues:" << endl;
    for (int i=0; i<nconv; i++)
      cout << "  lambda[" << (i+1) << "]: " << eigenvalues[i] << endl;
    cout << endl;

    // Printing the residual norm || A*x - lambda*B*x ||
    // for the nconv accurately computed eigenvectors.

    double * Ax      = new double[np];
    double * Bx      = new double[np];
    double * ResNorm = new double[nconv];

    double infinityNormK = K->GetInfinityNorm();
    double infinityNormM = M->GetInfinityNorm();
    double infNorm = infinityNormK;
    if (infinityNormM > infNorm)
      infNorm = infinityNormM;

    for (int i=0; i<nconv; i++)
    {
      K->MultiplyVector(&eigenvectors[np*i],Ax);
      M->MultiplyVector(&eigenvectors[np*i],Bx);
      for(int j=0; j<np; j++)
	Ax[j] = Ax[j] - eigenvalues[i] * Bx[j];
      //cblas_daxpy(np, -eigenvalues[i], Bx, 1, Ax, 1);
      ResNorm[i] = 0;
      for(int j=0; j<np; j++)
	ResNorm[i] += Ax[j] * Ax[j];
      ResNorm[i] = sqrt(ResNorm[i]) / fabs(eigenvalues[i]) / infNorm;
      //ResNorm[i] = cblas_dnrm2(np, Ax, 1) / fabs(eigenvalues[i]);
    }
    /*
       for (int i=0; i<nconv; i++) 
       {
       cout << "||A*x(" << (i+1) << ") - lambda(" << (i+1);
       cout << ")*B*x(" << (i+1) << ")|| / |lambda| / max(||A||,||B||) = " << ResNorm[i] << endl;
       }
       cout << endl;
     */

    //printf("Cleaning up the ARPACK workspace.\n");fflush(NULL);
    delete[] Ax;
    delete[] Bx;
    delete[] ResNorm;
  }

  delete(pardisoSolver);
  delete(P);
  free(newC);
  delete(ZKZ);
  return nconv;
}

