/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
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

/*
  Computes the first largest or smallest eigenvalues and eigenvectors of
  a large sparse matrix, using the ARPACK library:
  http://www.caam.rice.edu/software/ARPACK/

  There is also a routine to compute constrained modes, as published in:

  Hongyi Xu and Jernej Barbic: Pose-Space Subspace Dynamics, 
  ACM Transactions on Graphics 35(4) (SIGGRAPH 2016), Anaheim, CA, USA
*/

#ifndef _ARPACKSOLVER_H_
#define _ARPACKSOLVER_H_

#include "sparseMatrix.h"

class ARPACKSolver
{
public:
 
  // Perform eigensolve:
  // K * x = lambda * M * x
  // Returns the number of converged eigenvalues.
  // Assumes that both K and M are symmetric, and that M > 0.
  // Both matrices are given using the entire matrix (not just the lower/upper triangle).
  // Mode is either "LM" or "SM" (with SM, must also have K > 0).
  // Uses mode 2 of ARPACK (regular generalized eigenvalue problem).
  int SolveGenEigReg(SparseMatrix * K, SparseMatrix * M, int numEigenvalues, double * eigenvalues, double * eigenvectors, const char * mode = "LM", int numLinearSolverThreads=0, int verbose=1);

  // Perform eigensolve:
  // K * x = lambda * M * x.
  // Solves for the smallest (in absolute sense) eigenvalues.
  // Returns the number of converged eigenvalues.
  // Assumes that both K and M are symmetric, and that M >= 0.
  // K can be singular.
  // Uses mode 3 of ARPACK (shift-inverted generalized eigenvalue problem).
  // "sigma" is the amount of shift. This is needed when K is singular.
  int SolveGenEigShInv(SparseMatrix * K, SparseMatrix * M, int numEigenvalues, double * eigenvalues, double * eigenvectors, double sigma=0.0, int numLinearSolverThreads=0, int verbose=1);

  // Perform constrained eigensolve:
  // K * x = lambda * M * x, subject to C x = 0.
  // Solves for the smallest (in absolute sense) eigenvalues,
  // subject to the constraint C x = 0.
  // Returns the number of converged eigenvalues.
  // Assumes that both K and M are symmetric, and that M >= 0.
  // K can be singular.
  // Uses mode 3 of ARPACK (shift-inverted generalized eigenvalue problem).
  // "sigma" is the amount of shift. This is needed when K is singular.
  // Matrix C can be singular; "eps" is a threshold for regularizing the matrix C.
  int SolveGenEigShInv(SparseMatrix * K, SparseMatrix * M, SparseMatrix * C, int numEigenvalues, double * eigenvalues, double * eigenvectors, double sigma=0.0, double eps=1e-6, int numLinearSolverThreads=0, int verbose=1);

protected:
};

#endif

