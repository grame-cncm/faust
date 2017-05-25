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

#ifndef _PARDISOSOLVER_H_
#define _PARDISOSOLVER_H_

/*
  Solves A * x = rhs, where A is a sparse matrix. The following matrix types are supported:
    structurally symmetric matrix
    symmetric positive-definite matrix
    symmetric indefinite matrix
    unsymmetric matrix
  The solution is obtained using the Pardiso library from Intel MKL, using multi-threading.
  Three steps are performed: 
    1. matrix re-ordering and symbolic factorization (in the constructor)
    2. numerical matrix factorization (FactorMatrix)
    3. the actual linear system solve (SolveLinearSystem)
  The solution method is direct (not iterative), unless one uses the direct-iterative mode. 
  As such, convergence is robust, and there is no need to tune convergence parameters, unlike, say, in the conjugate gradient method.
  Memory requirements are minimized by re-ordering the matrix before applying the matrix decomposition.
  However, for very large systems (e.g. matrices of size 200,000 x 200,000, on a machine with 2 GB RAM), 
  the matrix decomposition might run out of memory.
*/

#include "linearSolver.h"
#include "sparseMatrix.h"

#define MKL_INT int

class PardisoSolver : public LinearSolver
{
public:
  // The constructor computes the permutation to re-order A, and performs symbolic factorization.
  // Only the topology of A matters for the constructor. A is not modified.
  // Note: after calling the constructor, you must call "FactorMatrix" to perform numerical factorization.
  //  "mtype" gives the matrix type:
  //  = 1   structurally symmetric matrix
  //  = 2   symmetric positive-definite matrix
  //  = -2  symmetric indefinite matrix
  //  = 11  unsymmetric matrix
  typedef enum { REAL_STRUCTURAL_SYM = 1, REAL_SPD = 2, REAL_SYM_INDEFINITE = -2, REAL_UNSYM = 11 } matrixType;
  // Matrix re-ordering is specified as follows:
  // = 0   minimum degree ordering
  // = 2   nested dissection algorithm from the METIS package
  // = 3   parallel (OpenMP) version of nested dissection; it can decrease the computation time on multi-core computers, especially when the constructor takes a long time
  typedef enum { MINIMUM_DEGREE_ORDERING = 0, NESTED_DISSECTION = 2, PARALLEL_NESTED_DISSECTION = 3 } reorderingType;
  // must have: numThreads >= 1
  // "directIterative" specifies whether a direct-iterative procedure is used (see Intel MKL's documentation)
  PardisoSolver(const SparseMatrix * A, int numThreads = 1, matrixType mtype = REAL_SYM_INDEFINITE, reorderingType rtype = NESTED_DISSECTION, int directIterative = 0, int verbose = 0);

  virtual ~PardisoSolver();

  // set the number of threads to use
  // must have: numThreads >= 1
  void SetNumThreads(int numThreads) { this->numThreads = numThreads; }

  // Perform the numerical matrix factorization (Cholesky for symmetric matrices, LU for other matrices).
  // This step is **mandatory** (constructor does not perform it).
  // You must factor the matrix at least once; and every time the entries of the matrix A change.
  // If the topology of A changes, you must call the constructor again.
  // A is not modified.
  MKL_INT FactorMatrix(const SparseMatrix * A); 

  // solve: A * x = rhs, using the previously computed matrix factorization
  // rhs is not modified
  virtual int SolveLinearSystem(double * x, const double * rhs);

  // solve multiple right-hand sides
  MKL_INT SolveLinearSystemMultipleRHS(double * x, const double * rhs, int numRHS);

  // solve: A * x = rhs, using the direct-iterative solver
  MKL_INT SolveLinearSystemDirectIterative(const SparseMatrix * A, double * x, const double * rhs);

  /*
    Advanced routines exposing the substeps of the solve.
    For REAL_SYM_INDEFINITE, SolveLinearSystem is equivalent to: ForwardSubstitution + DiagonalSubstitution + BackwardSubstitution
    For REAL_SPD, SolveLinearSystem is equivalent to: ForwardSubstitution + BackwardSubstitution (DiagonalSubstitution is not used)
  */
  MKL_INT ForwardSubstitution(double * y, const double * rhs); // L y = rhs
  MKL_INT DiagonalSubstitution(double * v, const double * y);  // D v = y
  MKL_INT BackwardSubstitution(double * x, const double * v);  // L^T x = v

protected:
  int n;
  double * a;
  int * ia, * ja;
  void *pt[64];
  MKL_INT iparm[64];

  int numThreads;
  matrixType mtype;
  reorderingType rtype;
  int directIterative;
  int verbose;
  MKL_INT nrhs; 
  MKL_INT maxfct, mnum, phase, error, msglvl;

  static void DisabledSolverError();
};

#endif

