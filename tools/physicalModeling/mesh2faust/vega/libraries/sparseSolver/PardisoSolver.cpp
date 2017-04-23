/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sparseSolver" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC   *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Yijing Li, Hongyi Xu                     *
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PardisoSolver.h"
#include "sparseSolverAvailability.h"

#ifdef PARDISO_SOLVER_IS_AVAILABLE

// Pardiso solver is available

#ifdef __APPLE__
  #include "TargetConditionals.h"
#endif

#include "mkl.h"

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)
  #define PARDISO pardiso
//#else
//#define PARDISO pardiso
#endif

PardisoSolver::PardisoSolver(const SparseMatrix * A, int numThreads_, matrixType mtype_, reorderingType rtype_, int directIterative_, int verbose_): numThreads(numThreads_), mtype(mtype_), rtype(rtype_), directIterative(directIterative_), verbose(verbose_)
{
  mkl_set_num_threads(numThreads);

  n = A->Getn();

  if (verbose >= 1)
    printf("Converting matrix to Pardiso format...\n");

  int numEntries;
  int upperTriangleOnly;  
  if ((mtype == REAL_SPD) || (mtype == REAL_SYM_INDEFINITE))  // matrix is symmetric
  {
    numEntries = A->GetNumUpperTriangleEntries();
    upperTriangleOnly = 1;
  }
  else  
  {
    // structural symmetric or unsymmetric
    numEntries = A->GetNumEntries();
    upperTriangleOnly = 0;
  }
  a = (double*) malloc (sizeof(double) * numEntries);  
  ia = (int*) malloc (sizeof(int) * (A->GetNumRows() + 1));  
  ja = (int*) malloc (sizeof(int) * numEntries);  
  int oneIndexed = 1;
  A->GenerateCompressedRowMajorFormat(a, ia, ja, upperTriangleOnly, oneIndexed);

  if (verbose >= 2)
    printf("numEntries: %d\n", numEntries);

  // permute & do symbolic factorization

  nrhs = 1; // Number of right hand sides.
  maxfct = 1; // Maximum number of numerical factorizations.
  mnum = 1; // Which factorization to use.
  msglvl = verbose >= 1 ? verbose - 1 : 0; // Print statistical information to the output file
  error = 0; // Initialize error flag

  for (int i = 0; i < 64; i++) 
    iparm[i] = 0;

  iparm[0] = 1; // Do not use the solver default values (use custom values, provided below)
  iparm[1] = rtype; // matrix re-ordering algorithm
  iparm[2] = 0; // unused 

  // use iterative-direct algorithm if requested
  if (directIterative)
  {
    if (mtype == REAL_SPD)  
      iparm[3] = 62; // matrix is symmetric positive-definite; use CGS iteration for symmetric positive-definite matrices
    else
      iparm[3] = 61; // use CGS iteration
  }
  else
    iparm[3] = 0; 

  iparm[4] = 0; // No user fill-in reducing permutation
  iparm[5] = 0; // Write solution into x
  iparm[6] = 0; // Output: number of iterative refinement steps performed
  iparm[7] = 0; // Max numbers of iterative refinement steps (used during the solving stage). Value of 0 (default) means: The solver automatically performs two steps of iterative refinement when perturbed pivots are obtained during the numerical factorization.
  iparm[8] = 0; // Reserved. Must set to 0.

  // Pivoting perturbation; the values below are Pardiso's default values
  // Pivoting only applies to REAL_UNSYM and REAL_SYM_INDEFINITE
  if (mtype == REAL_UNSYM)
    iparm[9] = 13; // For non-symmetric matrices, perturb the pivot elements with 1E-13
  else 
    iparm[9] = 8; // Use 1.0E-8 for symmetric indefinite matrices
  
  // Scaling and matching. The following below are the Pardiso defaults.
  if (mtype == REAL_UNSYM)  // unsymmetric matrices
  {
    iparm[10] = 1; // enable scaling
    iparm[12] = 1; // enable matching
  }
  else
  {
    iparm[10] = 0; // disable scaling
    iparm[12] = 0; // disable matching
  }

  iparm[11] = 0; // Solve with transposed or conjugate transposed matrix A. Not in use here.

  iparm[13] = 0; // Output: Number of perturbed pivots
  iparm[14] = 0; // Output: Peak memory on symbolic factorization (in KB)
  iparm[15] = 0; // Output: Permanent memory on symbolic factorization (in KB)
  iparm[16] = 0; // Output: Size of factors/Peak memory on numerical factorization and solution (in KB)
  
  iparm[17] = -1; // Output: Report the number of non-zero elements in the factors.
  iparm[18] = 0; // Report number of floating point operations (in 10^6 floating point operations) that are necessary to factor the matrix A. Disabled.
  iparm[19] = 0; // Output: Report CG/CGS diagnostics.
  iparm[20] = 1; // Pivoting for symmetric indefinite matrices: Apply 1x1 and 2x2 Bunch-Kaufman pivoting during the factorization process.
  iparm[21] = 0; // Output: Inertia: number of positive eigenvalues.
  iparm[22] = 0; // Output: Inertia: number of negative eigenvalues.

  iparm[23] = 0; // Parallel factorization control. Use default.
  iparm[24] = 0; // Parallel forward/backward solve control. Intel MKL PARDISO uses a parallel algorithm for the solve step.

  // the other iparms (above 24) are left at 0

  /* -------------------------------------------------------------------- *\
     .. Initialize the internal solver memory pointer. This is only 
     necessary for the FIRST call of the PARDISO solver. 
  \* -------------------------------------------------------------------- */
  for (int i=0; i<64; i++) 
    pt[i] = 0;

  if (verbose >= 1)
    printf("Reordering and symbolically factorizing the matrix...\n");

  /* -------------------------------------------------------------------- *\
     .. Reordering and Symbolic Factorization. This step also allocates 
     all memory that is necessary for the factorization.
  \* -------------------------------------------------------------------- */
  phase = 11;
  PARDISO (pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase,
    &n, a, ia, ja, NULL, &nrhs,
    iparm, &msglvl, NULL, NULL, &error);

  if (error != 0)
  {
    printf("Error: Pardiso matrix re-ordering/symbolic factorization returned non-zero exit code %d.\n", error);
    throw error;
  }

  if (verbose >= 2)
  {
    printf("\nReordering and symbolic factorization completed...\n");
    printf("Number of nonzeros in factors = %d\n", iparm[17]);
    printf("Number of factorization MFLOPS = %d\n", iparm[18]);
  }
}

PardisoSolver::~PardisoSolver()
{
  phase = -1;
  PARDISO(pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase, &n, a, ia, ja, NULL, &nrhs, iparm, &msglvl, NULL, NULL, &error);

  if (error != 0)
    printf("Error: Pardiso Cholesky dealloacation returned non-zero exit code %d.\n", error);

  free(a);
  free(ia);
  free(ja);
}

void PardisoSolver::DisabledSolverError() {}

MKL_INT PardisoSolver::FactorMatrix(const SparseMatrix * A)
{
  if (directIterative)
    return 0;

  mkl_set_num_threads(numThreads);

  // compute the factorization
  if (verbose >= 1)
    printf("Factoring the %d x %d matrix (%d threads)...\n", n, n, numThreads);

  int upperTriangleOnly = 1;
  int oneIndexed = 1;

  if ((mtype == REAL_SPD) || (mtype == REAL_SYM_INDEFINITE))  // matrix is symmetric
    upperTriangleOnly = 1;    // symmetric matrix can only be represented by its upper triangle elements
  else  // structural symmetric or unsymmetric
    upperTriangleOnly = 0;    // unsymmetric matrix must store all its elements
  A->GenerateCompressedRowMajorFormat(a, NULL, NULL, upperTriangleOnly, oneIndexed);

  // factor 
  phase = 22;
  PARDISO(pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase, &n, a, ia, ja, NULL, &nrhs, iparm, &msglvl, NULL, NULL,  &error);

  if (error != 0)
    printf("Error: Pardiso Cholesky decomposition returned non-zero exit code %d.\n", error);

  if (verbose >= 1)
    printf("Factorization completed.\n");

  return error;
}

int PardisoSolver::SolveLinearSystem(double * x, const double * rhs)
{
  if (directIterative != 0)
  {
    printf("Error: direct-iterative flag was specified in the constructor (must use SolveLinearSystemDirectIterative routine).\n");
    return 101;
  }

  mkl_set_num_threads(numThreads); 

  if (verbose >= 2)
    printf("Solving linear system...(%d threads)\n", numThreads);

  phase = 33;
  PARDISO(pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase, &n, a, ia, ja, NULL, &nrhs, iparm, &msglvl, (double*)rhs, x, &error);

  if (error != 0)
    printf("Error: Pardiso solve returned non-zero exit code %d.\n", error);

  if (verbose >= 2)
    printf("Solve completed.\n"); 

  return (int)error;
}

MKL_INT PardisoSolver::ForwardSubstitution(double * y, const double * rhs)
{
  if (directIterative != 0)
  {
    printf("Error: direct-iterative flag was specified in the constructor (must use SolveLinearSystemDirectIterative routine).\n");
    return 101;
  }

  if (verbose >= 2)
    printf("Performing forward substitution...(%d threads)\n", numThreads);

  mkl_set_num_threads(numThreads); 

  int maxIterRefinementSteps = iparm[7];
  iparm[7] = 0;

  phase = 331;
  PARDISO(pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase, &n, a, ia, ja, NULL, &nrhs, iparm, &msglvl, (double*)rhs, y, &error);

  iparm[7] = maxIterRefinementSteps;

  if (error != 0)
    printf("Error: Pardiso solve returned non-zero exit code %d.\n", error);

  if (verbose >= 2)
    printf("Solve completed.\n"); 

  return error;
}

MKL_INT PardisoSolver::DiagonalSubstitution(double * v, const double * y)
{
  if (directIterative != 0)
  {
    printf("Error: direct-iterative flag was specified in the constructor (must use SolveLinearSystemDirectIterative routine).\n");
    return 101;
  }

  if (mtype == REAL_SPD)
  {
    printf("Error: diagonal substitution should not be used for positive-definite matrices.\n");
    return 102;
  }

  mkl_set_num_threads(numThreads); 

  if (verbose >= 2)
    printf("Performing forward substitution...(%d threads)\n", numThreads);

  int maxIterRefinementSteps = iparm[7];
  iparm[7] = 0;

  phase = 332;
  PARDISO(pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase, &n, a, ia, ja, NULL, &nrhs, iparm, &msglvl, (double*)y, v, &error);

  iparm[7] = maxIterRefinementSteps;

  if (error != 0)
    printf("Error: Pardiso solve returned non-zero exit code %d.\n", error);

  if (verbose >= 2)
    printf("Solve completed.\n"); 

  return error;
}

MKL_INT PardisoSolver::BackwardSubstitution(double * x, const double * y)
{
  if (directIterative != 0)
  {
    printf("Error: direct-iterative flag was specified in the constructor (must use SolveLinearSystemDirectIterative routine).\n");
    return 101;
  }

  mkl_set_num_threads(numThreads); 

  if (verbose >= 2)
    printf("Performing forward substitution...(%d threads)\n", numThreads);

  int maxIterRefinementSteps = iparm[7];
  iparm[7] = 0;

  phase = 333;
  PARDISO(pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase, &n, a, ia, ja, NULL, &nrhs, iparm, &msglvl, (double*)y, x, &error);

  iparm[7] = maxIterRefinementSteps;

  if (error != 0)
    printf("Error: Pardiso solve returned non-zero exit code %d.\n", error);

  if (verbose >= 2)
    printf("Solve completed.\n"); 

  return error;
}

MKL_INT PardisoSolver::SolveLinearSystemMultipleRHS(double * x, const double * rhs, int numRHS)
{
  if (directIterative != 0)
  {
    printf("Error: direct-iterative flag was specified in the constructor (must use SolveLinearSystemDirectIterative routine).\n");
    return 101;
  }

  if (verbose >= 2)
    printf("Solving linear system...(%d threads)\n", numThreads);

  mkl_set_num_threads(numThreads); 

  phase = 33;
  PARDISO(pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase, &n, a, ia, ja, NULL, &numRHS, iparm, &msglvl, (double*)rhs, x, &error);

  if (error != 0)
    printf("Error: Pardiso solve returned non-zero exit code %d.\n", error);

  if (verbose >= 2)
    printf("Solve completed.\n");

  return error;
}

MKL_INT PardisoSolver::SolveLinearSystemDirectIterative(const SparseMatrix * A, double * x, const double * rhs)
{
  if (directIterative != 1)
  {
    printf("Error: direct-iterative flag was not specified in the constructor.\n");
    return 102;
  }

  mkl_set_num_threads(numThreads); 

  if (verbose >= 2)
    printf("Solving linear system...(%d threads, direct-iterative)\n", numThreads);

  int upperTriangleOnly = 1;
  int oneIndexed = 1;
  A->GenerateCompressedRowMajorFormat(a, NULL, NULL, upperTriangleOnly, oneIndexed);

  phase = 23;
  PARDISO(pt, &maxfct, &mnum, (MKL_INT*)&mtype, &phase, &n, a, ia, ja, NULL, &nrhs, iparm, &msglvl, (double*)rhs, x, &error);

  if (error != 0)
    printf("Error: Pardiso solve returned non-zero exit code %d.\n", error);

  if (verbose >= 2)
    printf("Solve completed.\n"); 

  return error;
}

#else

// Pardiso Solver is not available

PardisoSolver::PardisoSolver(const SparseMatrix * A, int numThreads_, matrixType mtype_, reorderingType rtype_, int directIterative_, int verbose_): numThreads(numThreads_), mtype(mtype_), rtype(rtype_), directIterative(directIterative_), verbose(verbose_)
{
  DisabledSolverError();
}

PardisoSolver::~PardisoSolver()
{
}

void PardisoSolver::DisabledSolverError()
{
  printf("Error: Pardiso solver called, but it has not been installed/compiled/enabled. After installation, enable it in \"sparseSolverAvailability.h\".\n");
  throw 1;
}

MKL_INT PardisoSolver::FactorMatrix(const SparseMatrix * A)
{
  DisabledSolverError();
  return 1;
}

MKL_INT PardisoSolver::SolveLinearSystem(double * x, const double * rhs)
{
  DisabledSolverError();
  return 1;
}

MKL_INT PardisoSolver::SolveLinearSystemMultipleRHS(double * x, const double * rhs, int numRHS)
{
  DisabledSolverError();
  return 1;
}

MKL_INT PardisoSolver::SolveLinearSystemDirectIterative(const SparseMatrix * A, double * x, const double * rhs)
{
  DisabledSolverError();
  return 1;
}

#endif

