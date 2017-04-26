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

#ifndef _SPOOLESSOLVERMT_H_
#define _SPOOLESSOLVERMT_H_

/*

Solves A * x = rhs, where A is sparse, usually large, and symmetric.
Uses a multi-threaded approach to perform the solve.

The solution is obtained using the the SPOOLES library (which is free software).
The solution method is direct (not iterative). As such, convergence
is often very robust, and there is no need to tune convergence parameters,
unlike, say, in the Conjugate gradient method.
Memory requirements are minimized by re-ordering the matrix before applying
Cholesky decomposition.
However, for very large systems (e.g. 200,000 x 200,000 matrices on a 
2Gb machine), the Cholesky decomposition might run out of memory.

*/

#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"
#include "linearSolver.h"

class SPOOLESSolverMT : public LinearSolver
{
public:

  // this constructor will re-order A (in an internal copy), and then perform complete Cholesky factorization (via SPOOLES)
  // A is not modified
  SPOOLESSolverMT(const SparseMatrix * A, int numThreads, int verbose=0);
  virtual ~SPOOLESSolverMT();

  // solve: A * x = rhs, using SPOOLES
  // uses the Cholesky factors obtained in the constructor
  // rhs is not modified
  virtual int SolveLinearSystem(double * x, const double * rhs);

protected:
  int n;
  void * bridgeMTPointer;
  void * mtx_xPointer;
  void * mtx_rhsPointer;
  void * APointer;
  FILE * msgFile;
  int verbose;
  int nsolveops;

  static void DisabledSolverError();
};

#endif

