/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sparseSolver" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC   *
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

#include "SPOOLESSolverMT.h"
#include "SPOOLESSolver.h"
#include "sparseSolverAvailability.h"

#ifdef SPOOLES_SOLVER_IS_AVAILABLE

// SPOOLES solver is available

extern "C" {
  #include "LinSol/BridgeMT.h"
}

SPOOLESSolverMT::SPOOLESSolverMT(const SparseMatrix * A, int numThreads, int verbose)
{
  n = A->Getn();
  this->verbose = verbose;

  msgFile = fopen("SPOOLES.message","w");

  // prepare SPOOLES input matrix
  if (verbose >= 1)
    printf("Converting matrix to SPOOLES format...\n");

  InpMtx * mtxA = InpMtx_new();
  InpMtx_init(mtxA, INPMTX_BY_ROWS, SPOOLES_REAL, A->GetNumEntries(), n);

  for(int row=0; row<n; row++)
  {
    int rowLength = A->GetRowLength(row);

    for(int j=0; j< rowLength; j++)
    {
      if (A->GetColumnIndex(row,j) >= row)
        InpMtx_inputRealEntry(mtxA, row, A->GetColumnIndex(row, j), A->GetEntry(row, j) );
    }
  }

  InpMtx_changeStorageMode(mtxA, INPMTX_BY_VECTORS);
  //InpMtx_writeForHumanEye(mtxA, msgFile);

  // compute the factorization
  if (verbose >= 1)
    printf("Factoring the %d x %d matrix...\n",n,n);

  BridgeMT * bridgeMT = BridgeMT_new();
  BridgeMT_setMatrixParams(bridgeMT, n, SPOOLES_REAL, SPOOLES_SYMMETRIC);
  BridgeMT_setMessageInfo(bridgeMT, 1, msgFile);
  int rc = BridgeMT_setup(bridgeMT, mtxA);
  if (rc != 1)
  {
    printf("Error: BridgeMT setup returned exit code %d.\n", rc);
    throw 1;
  }

  int type = 1; // real entries
  int nfront, nfind, nfent;
  double nfactorops;
  rc = BridgeMT_factorStats(bridgeMT, type, SPOOLES_SYMMETRIC, &nfront,
                            &nfind, &nfent, &nsolveops, &nfactorops);
  if ( rc != 1 ) 
  {
    printf("Error: BridgeMT_factorStats returned exit code %d.\n", rc);
    throw 1;
  }

  fprintf(msgFile,
        "\n\n factor matrix statistics"
        "\n %d fronts, %d indices, %d entries"
        "\n %d solve operations, %12.4e factor operations",
        nfront, nfind, nfent, nsolveops, nfactorops) ;
  fflush(msgFile) ;


  // setup the parallel factorization

  rc = BridgeMT_factorSetup(bridgeMT, numThreads, 0, 0.0) ;
  fprintf(msgFile, "\n\n ----- PARALLEL FACTOR SETUP -----\n") ;
  fprintf(msgFile,
        "\n    CPU %8.3f : time to setup parallel factorization",
        bridgeMT->cpus[5]) ;
  fprintf(msgFile, "\n total factor operations = %.0f",
           DV_sum(bridgeMT->cumopsDV)) ;
  fprintf(msgFile,
           "\n upper bound on speedup due to load balance = %.2f",
           DV_sum(bridgeMT->cumopsDV)/DV_max(bridgeMT->cumopsDV)) ;
  fprintf(msgFile, "\n operations distributions over threads") ;
  DV_writeForHumanEye(bridgeMT->cumopsDV, msgFile) ;
  fflush(msgFile) ;

  // factor the matrix
  int permuteflag  = 1 ;
  int error;
  rc = BridgeMT_factor(bridgeMT, mtxA, permuteflag, &error);
  if ( rc == 1 ) 
  {
    fprintf(msgFile, "\n\n factorization completed successfully\n") ;
  } 
  else 
  {
    printf("Error: factorization returned exit code %d (error %d).\n", rc, error);
    throw 1;
  }

  fprintf(msgFile, "\n\n ----- FACTORIZATION -----\n") ;
  fprintf(msgFile,
        "\n    CPU %8.3f : time to permute original matrix"
        "\n    CPU %8.3f : time to initialize factor matrix"
        "\n    CPU %8.3f : time to compute factorization"
        "\n    CPU %8.3f : time to post-process factorization"
        "\n CPU %8.3f : total factorization time\n",
        bridgeMT->cpus[6],
        bridgeMT->cpus[7],
        bridgeMT->cpus[8],
        bridgeMT->cpus[9],
        bridgeMT->cpus[10]) ;
  fprintf(msgFile, "\n\n factorization statistics"
        "\n %d pivots, %d pivot tests, %d delayed vertices"
        "\n %d entries in D, %d entries in L, %d entries in U",
        bridgeMT->stats[0], bridgeMT->stats[1], bridgeMT->stats[2],
        bridgeMT->stats[3], bridgeMT->stats[4], bridgeMT->stats[5]) ;
  fprintf(msgFile,
        "\n\n factorization: raw mflops %8.3f, overall mflops %8.3f",
        1.e-6*nfactorops/bridgeMT->cpus[8],
        1.e-6*nfactorops/bridgeMT->cpus[10]) ;
  fflush(msgFile) ;

  // construct dense SPOOLES matrix for rhs and x
  DenseMtx *mtx_rhs = DenseMtx_new();
  DenseMtx_init(mtx_rhs, SPOOLES_REAL, 0, 0, n, 1, 1, n);
  mtx_rhsPointer = (void*) mtx_rhs;

  DenseMtx *mtx_x = DenseMtx_new();
  DenseMtx_init(mtx_x, SPOOLES_REAL, 0, 0, n, 1, 1, n);
  mtx_xPointer = (void*) mtx_x;

  bridgeMTPointer = (void*) bridgeMT;
  APointer = (void*) mtxA;

  if (verbose >= 1)
    printf("Factorization completed.\n");
}

SPOOLESSolverMT::~SPOOLESSolverMT()
{
  BridgeMT_free((BridgeMT*) bridgeMTPointer);
  InpMtx_free((InpMtx *) APointer);
  DenseMtx_free((DenseMtx *) mtx_rhsPointer);
  DenseMtx_free((DenseMtx *) mtx_xPointer);
  fclose(msgFile);
}

void SPOOLESSolverMT::DisabledSolverError() {}

int SPOOLESSolverMT::SolveLinearSystem(double * x, const double * rhs)
{
  BridgeMT * bridgeMT = (BridgeMT*) bridgeMTPointer;
  DenseMtx * mtx_rhs = (DenseMtx*) mtx_rhsPointer;
  DenseMtx * mtx_x = (DenseMtx*) mtx_xPointer;

  // set mtx_rhs
  DenseMtx_zero(mtx_rhs);
  for(int i=0; i < n; i++)
    DenseMtx_setRealEntry(mtx_rhs, i, 0, rhs[i]);

  /*
    FILE * fout = fopen("bla.txt","w");
    DenseMtx_writeForHumanEye(mtx_rhs, fout);
    fclose(fout);
  */

  // zero the solution
  DenseMtx_zero(mtx_x);
  
  // solve
  if (verbose >= 2)
    printf("Solving the linear system...\n");

  // setup the solve
  int rc = BridgeMT_solveSetup(bridgeMT) ;
  fprintf(msgFile, "\n\n ----- PARALLEL SOLVE SETUP -----\n") ;
  fprintf(msgFile,
          "\n    CPU %8.3f : time to setup parallel solve",
          bridgeMT->cpus[11]) ;

  // solve the system
  int permuteflag = 1;
  rc = BridgeMT_solve(bridgeMT, permuteflag, mtx_x, mtx_rhs) ;
  if (rc != 1)
  {
    printf("Error: linear system solve failed. BridgeMT_solve exit code: %d.\n", rc);
    return (rc == 0) ? 1 : rc;
  }

  fprintf(msgFile, "\n\n ----- SOLVE -----\n") ;
  fprintf(msgFile,
          "\n    CPU %8.3f : time to permute rhs into new ordering"
          "\n    CPU %8.3f : time to solve linear system"
          "\n    CPU %8.3f : time to permute solution into old ordering"
          "\n CPU %8.3f : total solve time\n",
          bridgeMT->cpus[12], bridgeMT->cpus[13],
          bridgeMT->cpus[14], bridgeMT->cpus[15]) ;
  fprintf(msgFile,
          "\n\n solve: raw mflops %8.3f, overall mflops %8.3f",
          1.e-6*nsolveops/bridgeMT->cpus[13],
          1.e-6*nsolveops/bridgeMT->cpus[15]) ;
  fflush(msgFile) ;

  if (verbose >= 2)
    printf("Solve completed.\n"); 

  // store result
  for(int i=0; i < n; i++)
    DenseMtx_realEntry(mtx_x, i, 0, &x[i]);

  /*
    fout = fopen("ble.txt","w");
    DenseMtx_writeForHumanEye(mtx_x, fout);
    fclose(fout);
  */

  return 0;
}

#else

// SPOOLES Solver is not available

SPOOLESSolverMT::SPOOLESSolverMT(const SparseMatrix * A, int numThreads, int verbose)
{
  DisabledSolverError();
}

SPOOLESSolverMT::~SPOOLESSolverMT()
{
}

void SPOOLESSolverMT::DisabledSolverError()
{
  printf("Error: SPOOLES solver called, but it has not been installed/compiled/enabled. After installation, enable it in \"sparseSolverAvailability.h\".\n");
  throw 1;
}

int SPOOLESSolverMT::SolveLinearSystem(double * x, const double * rhs)
{
  DisabledSolverError();
  return 1;
}

#endif

