/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sparseMatrix" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC   *
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

/*
  Example for how to use the SparseMatrix class and the conjugate gradient solver.
  The CG solver is in the "sparseSolvers" folder.
  See also sparseMatrix.h and CGSolver.h.
*/

#include "sparseMatrix.h"
#include "CGSolver.h"

int main()
{
  /*
    To create and use a sparse matrix, follow the following simple procedure:

    1. Create a SparseMatrixOutline object, which specifies the locations of non-zero entries. Optionally, you can also set the values for the non-zero entries, or you can do that later. You can add the non-zero entries in arbitrary order. Duplicates are allowed and will internally be properly merged into a single entry.

    2. Initialize a SparseMatrix object by passing the SparseMatrixOutline object to it as a parameter. With the SparseMatrix object, you can no longer modify the locations of the non-zero entries (but can still modify the values for the non-zero entries). However, all data is stored in simple C arrays which can be traversed quickly. All the computational routines operate on the SparseMatrix object.

   3. You can now deallocate the SparseMatrixOutline object (call delete() on it) 

   4. Do whatever you want with the SparseMatrix object, e.g., sum several of them together, access/modify elements, solve a linear system using a CG solver (or Gauss-Seidel iterations), save it to a text file, etc.

  */

  /* 
     We will create the following 1000 x 1000 sparse matrix:

           [ 3 1         ]
           [ 1 3 1       ]
     A  =  [   1 3 1     ]
           [     1 3 1   ]
           [       ...   ]
           [         1 3 ]

  */

  // ****************************************
  // 1. Generate the "outline" of the matrix, 
  // i.e. locations of non-zero entries
  // ****************************************

  int n = 1000; // matrix dimension
  SparseMatrixOutline * outline = new SparseMatrixOutline(n); // n x n sparse matrix
  for(int row=0; row<n; row++)
  {
    // here we are also setting the values of non-zero entries (or we could also do that later with the SparseMatrix object)
    if (row - 1 >= 0)
      outline->AddEntry(row, row-1, 1.0); 
    outline->AddEntry(row, row, 3.0);
    if (row + 1 < n)
      outline->AddEntry(row, row+1, 1.0); 
  }

  // ****************************************
  // 2. Convert to a sparse matrix
  // ****************************************

  SparseMatrix A(outline);

  // ****************************************
  // 3. We no longer need the outline
  // ****************************************

  delete(outline); 

  // ****************************************
  // 4. Solve the linear system A * x = b,
  // where b = [ +1 -1 +1 -1 ... +1 -1 ] ^T
  // ****************************************

  double * b = (double*) calloc (n, sizeof(double)); // sets all entries to 0
  for(int i=0; i<n; i++)
  {
    if (i % 2 == 0)
      b[i] = 1;
    else
      b[i] = -1;
  }
 
  double * x = (double*) calloc (n, sizeof(double)); // sets all entries to 0; note: initial value of x is important as it is the initial guess to the CG solver

  // create the Jacobi-preconditioned CG solver:
  CGSolver solver(&A);
  double eps = 1E-9;
  int maxIter = 500;
  int verbose = 0; // set this to 1 to see printouts of iteration progress

  printf("Solving a %d x %d sparse linear system with %d non-zero elements...\n", A.Getn(), A.Getn(), A.GetNumEntries());
  int code = solver.SolveLinearSystemWithJacobiPreconditioner(x, b, eps, maxIter, verbose); // do the CG solve
  // note: because all the diagonal elements are equal for our matrix A, the Jacobi preconditioner does not accelerate convergence in this case (but generally will if the diagonal elements have varying magnitudes)

  // check the exit code for any errors, |code| is the number of CG iterations performed, and code sign is a 1-bit error flag
  if (code < 0)
    printf("Error: the Jacobi-preconditioned CG solver did not converge in %d iterations.\n", -code);
  else
    printf("The Jacobi-preconditioned CG solver converged in %d iterations.\n", code);

  // ******************************************
  // 5. Print the solution out, verify solution
  // ******************************************

  // the system has now been solved, print the solution out:
  printf("The CG solution:\n");
  for(int i=0; i<n; i++)
    printf("%f ", x[i]);
  printf("\n");

  // verify the solution:
  A.CheckLinearSystemSolution(x,b); 
  printf("\n");

  // ******************************************
  // 6. Solve again, this time using 
  // the Gauss-Seidel solver
  // ******************************************

  // now, let's solve the system again using Gauss-Seidel iteration:
  for(int i=0; i<n; i++)
    x[0] = 0.0;

  // do 100 Gauss-Seidel iterations
  int numGaussSeidelIterations = 100;
  for(int iter=0; iter<numGaussSeidelIterations; iter++)
    A.DoOneGaussSeidelIteration(x, b);
  
  printf("The Gauss-Seidel solution (%d iterations):\n", numGaussSeidelIterations);
  for(int i=0; i<n; i++)
    printf("%f ", x[i]);
  printf("\n");

  // verify the Gauss-Seidel solution:
  A.CheckLinearSystemSolution(x,b); 
  printf("\n");

  // deallocate
  free(x);
  free(b);

  return 0;
}

