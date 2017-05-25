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

#include "SPOOLESSolver.h"
#include "sparseSolverAvailability.h"

#ifdef SPOOLES_SOLVER_IS_AVAILABLE

// SPOOLES solver is available

extern "C" {
  #include "LinSol/Bridge.h"
}

SPOOLESSolver::SPOOLESSolver(const SparseMatrix * A, int verbose)
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

  Bridge * bridge = Bridge_new();
  Bridge_setMatrixParams(bridge, n, SPOOLES_REAL, SPOOLES_SYMMETRIC);
  Bridge_setMessageInfo(bridge, 1, msgFile);
  int rc = Bridge_setup(bridge, mtxA);
  if (rc != 1)
  {
    printf("Error: Bridge setup returned exit code %d.\n", rc);
    throw 1;
  }

  int permuteFlag = 1;
  int error;
  rc = Bridge_factor(bridge, mtxA, permuteFlag, &error);

  if (rc != 1)
  {
    printf("Error: matrix factorization failed. Bridge_factor exit code: %d. Error code: %d\n", rc, error);
    throw 1;
  }

  // construct dense SPOOLES matrix for rhs and x
  DenseMtx *mtx_rhs = DenseMtx_new();
  DenseMtx_init(mtx_rhs, SPOOLES_REAL, 0, 0, n, 1, 1, n);
  mtx_rhsPointer = (void*) mtx_rhs;

  DenseMtx *mtx_x = DenseMtx_new();
  DenseMtx_init(mtx_x, SPOOLES_REAL, 0, 0, n, 1, 1, n);
  mtx_xPointer = (void*) mtx_x;

  bridgePointer = (void*) bridge;
  APointer = (void*) mtxA;

  if (verbose >= 1)
    printf("Factorization completed.\n");
}

SPOOLESSolver::~SPOOLESSolver()
{
  Bridge_free((Bridge*) bridgePointer);
  InpMtx_free((InpMtx *) APointer);
  DenseMtx_free((DenseMtx *) mtx_rhsPointer);
  DenseMtx_free((DenseMtx *) mtx_xPointer);
  fclose(msgFile);
}

void SPOOLESSolver::DisabledSolverError() {}

int SPOOLESSolver::SolveLinearSystem(double * x, const double * rhs)
{
  Bridge * bridge = (Bridge*) bridgePointer;
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

  int permuteFlag = 1;
  int rc = Bridge_solve(bridge, permuteFlag, mtx_x, mtx_rhs);

  if (rc != 1)
  {
    printf("Error: linear system solve failed. Bridge_solve exit code: %d.\n", rc);
    return (rc == 0) ? 1 : rc;
  }

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

SPOOLESSolver::SPOOLESSolver(const SparseMatrix * A, int verbose)
{
  DisabledSolverError();
}

SPOOLESSolver::~SPOOLESSolver()
{
}

void SPOOLESSolver::DisabledSolverError()
{
  printf("Error: SPOOLES solver called, but it has not been installed/compiled/enabled. After installation, enable it in \"sparseSolverAvailability.h\".\n");
  throw 1;
}

int SPOOLESSolver::SolveLinearSystem(double * x, const double * rhs)
{
  DisabledSolverError();
  return 1;
}

#endif

