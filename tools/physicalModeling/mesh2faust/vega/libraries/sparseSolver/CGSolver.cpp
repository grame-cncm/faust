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

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "CGSolver.h"

CGSolver::CGSolver(SparseMatrix * A_): A(A_) 
{
  numRows = A->GetNumRows();
  InitBuffers();
  multiplicator = CGSolver::DefaultMultiplicator;
  multiplicatorData = (void*)A;
  invDiagonal = NULL;
}

CGSolver::CGSolver(int numRows_, blackBoxProductType callBackFunction_, void * data_, double * diagonal): numRows(numRows_), multiplicator(callBackFunction_), multiplicatorData(data_), A(NULL)
{
  InitBuffers();
  invDiagonal = (double*) malloc (sizeof(double) * numRows);
  if (diagonal == NULL)
  {
    for(int i=0; i<numRows; i++)
      invDiagonal[i] = 1.0;
  }
  else
  {
    for(int i=0; i<numRows; i++)
      invDiagonal[i] = 1.0 / diagonal[i];
  }
}

CGSolver::~CGSolver()
{
  free(r);
  free(d);
  free(q);
  free(invDiagonal);
}

void CGSolver::DefaultMultiplicator(const void * data, const double * x, double * Ax)
{
  SparseMatrix * A = (SparseMatrix*)data;
  A->MultiplyVector(x, Ax);
}

void CGSolver::InitBuffers()
{
  r = (double*) malloc (sizeof(double) * numRows);
  d = (double*) malloc (sizeof(double) * numRows);
  q = (double*) malloc (sizeof(double) * numRows);
}

// implements the virtual method from LinearSolver by calling "SolveLinearSystem" with default parameters
int CGSolver::SolveLinearSystem(double * x, const double * b) 
{
  return SolveLinearSystemWithJacobiPreconditioner(x, b, 1E-6, 1000, 0);
}

int CGSolver::SolveLinearSystemWithoutPreconditioner(double * x, const double * b, double eps, int maxIterations, int verbose)
{
  int iteration=1;
  multiplicator(multiplicatorData, x, r); //A->MultiplyVector(x,r);
  for (int i=0; i<numRows; i++)
  {
    r[i] = b[i] - r[i];
    d[i] = r[i];
  }

  double residualNorm2 = ComputeDotProduct(r, r);
  double initialResidualNorm2 = residualNorm2;

  while ((residualNorm2 > eps * eps * initialResidualNorm2) && (iteration <= maxIterations))
  {
    if (verbose)
      printf("CG iteration %d: current L2 error vs initial error=%G\n", iteration, sqrt(residualNorm2 / initialResidualNorm2));

    multiplicator(multiplicatorData, d, q); //A->MultiplyVector(d,q); // q = A * d
    double dDotq = ComputeDotProduct(d, q);
    double alpha = residualNorm2 / dDotq;
    //printf("residualNorm2=%G dDotq=%G alpha=%G\n", residualNorm2, dDotq, alpha);

    for(int i=0; i<numRows; i++)
      x[i] += alpha * d[i];

    if (iteration % 30 == 0)
    {
      // periodically compute the exact residual (Shewchuk, page 8)
      multiplicator(multiplicatorData, x, r); //A->MultiplyVector(x,r);
      for (int i=0; i<numRows; i++)
        r[i] = b[i] - r[i];
    }
    else
    {
      for (int i=0; i<numRows; i++)
        r[i] = r[i] - alpha * q[i];
    }

    double oldResidualNorm2 = residualNorm2;
    residualNorm2 = ComputeDotProduct(r, r);
    double beta = residualNorm2 / oldResidualNorm2;

    for (int i=0; i<numRows; i++)
      d[i] = r[i] + beta * d[i];

    iteration++;
  }

  return (iteration-1) * ((residualNorm2 > eps * eps * initialResidualNorm2) ? -1 : 1);
}

int CGSolver::SolveLinearSystemWithPreconditioner(LinearSolver * preconditioner, double * x, const double * b, double eps, int maxIterations, int verbose)
{
  int iteration=1;
  multiplicator(multiplicatorData, x, r); //A->MultiplyVector(x,r);
  for (int i=0; i<numRows; i++)
    r[i] = b[i] - r[i];
  preconditioner->SolveLinearSystem(d, r); // d = M^{-1} * r

  // residualNorm2 = < M^{-1} * r, r >
  double residualNorm2 = ComputeDotProduct(d, r);
  double initialResidualNorm2 = residualNorm2;

  while ((residualNorm2 > eps * eps * initialResidualNorm2) && (iteration <= maxIterations))
  {
    if (verbose)
      printf("CG iteration %d: current M^{-1}-L2 error vs initial error=%G\n", iteration, sqrt(residualNorm2 / initialResidualNorm2));

    multiplicator(multiplicatorData, d, q); //A->MultiplyVector(d,q); // q = A * d
    double dDotq = ComputeDotProduct(d, q);
    double alpha = residualNorm2 / dDotq;

    for(int i=0; i<numRows; i++)
      x[i] += alpha * d[i];

    if (iteration % 30 == 0)
    {
      // periodically compute the exact residual (Shewchuk, page 8)
      multiplicator(multiplicatorData, x, r); //A->MultiplyVector(x,r);
      for (int i=0; i<numRows; i++)
	r[i] = b[i] - r[i];
    }
    else
    {
      for (int i=0; i<numRows; i++)
	r[i] = r[i] - alpha * q[i];
    }

    double oldResidualNorm2 = residualNorm2;

    preconditioner->SolveLinearSystem(q, r); // q = M^{-1} * r
    // residualNorm2 = < M^{-1} * r, r >
    residualNorm2 = ComputeDotProduct(q, r);
    double beta = residualNorm2 / oldResidualNorm2;

    for (int i=0; i<numRows; i++)
      d[i] = q[i] + beta * d[i];

    iteration++;
  }

  if (residualNorm2 < 0)
  {
    printf("Warning: residualNorm2=%G is negative. Input matrix might not be SPD. Solution could be incorrect.\n", residualNorm2);
  }

  return (iteration-1) * ((residualNorm2 > eps * eps * initialResidualNorm2) ? -1 : 1);
}

int CGSolver::SolveLinearSystemWithJacobiPreconditioner(double * x, const double * b, double eps, int maxIterations, int verbose)
{
  if (invDiagonal == NULL)
  {
    // This code will only execute when the class was constructed via the "SparseMatrix * A_" constructor (and only once).
    // In the "blackBoxProductType callBackFunction_" constructor, invDiagonal would have already been set to non-NULL.

    // extract diagonal entries
    A->BuildDiagonalIndices(); // note: if indices are already built, this call will do nothing (you can therefore also call BuildDiagonalIndices() once and for all before calling SolveLinearSystemWithJacobiPreconditioner); in any case, BuildDiagonalIndices() is fast (a single linear traversal of all matrix elements)

    invDiagonal = (double*) malloc (sizeof(double) * numRows);
    A->GetDiagonal(invDiagonal);
    for(int i=0; i<numRows; i++)
      invDiagonal[i] = 1.0 / invDiagonal[i]; // potential division by zero here (uncommon in practice)
  }

  int iteration=1;
  multiplicator(multiplicatorData, x, r); //A->MultiplyVector(x,r);
  for (int i=0; i<numRows; i++)
  {
    r[i] = b[i] - r[i];
    d[i] = invDiagonal[i] * r[i];
  }

  double residualNorm2 = ComputeTriDotProduct(r, r, invDiagonal);
  double initialResidualNorm2 = residualNorm2;

  while ((residualNorm2 > eps * eps * initialResidualNorm2) && (iteration <= maxIterations))
  {
    if (verbose)
      printf("CG iteration %d: current M^{-1}-L2 error vs initial error=%G\n", iteration, sqrt(residualNorm2 / initialResidualNorm2));

    multiplicator(multiplicatorData, d, q); //A->MultiplyVector(d,q); // q = A * d
    double dDotq = ComputeDotProduct(d, q);
    double alpha = residualNorm2 / dDotq;

    for(int i=0; i<numRows; i++)
      x[i] += alpha * d[i];

    if (iteration % 30 == 0)
    {
      // periodically compute the exact residual (Shewchuk, page 8)
      multiplicator(multiplicatorData, x, r); //A->MultiplyVector(x,r);
      for (int i=0; i<numRows; i++)
        r[i] = b[i] - r[i];
    }
    else
    {
      for (int i=0; i<numRows; i++)
        r[i] = r[i] - alpha * q[i];
    }

    double oldResidualNorm2 = residualNorm2;
    residualNorm2 = ComputeTriDotProduct(r, r, invDiagonal);
    double beta = residualNorm2 / oldResidualNorm2;

    for (int i=0; i<numRows; i++)
      d[i] = invDiagonal[i] * r[i] + beta * d[i];

    iteration++;
  }

  if (residualNorm2 < 0)
  {
    printf("Warning: residualNorm2=%G is negative. Input matrix might not be SPD. Solution could be incorrect.\n", residualNorm2);
  }

  return (iteration-1) * ((residualNorm2 > eps * eps * initialResidualNorm2) ? -1 : 1);
}

double CGSolver::ComputeDotProduct(double * v1, double * v2)
{
  double result = 0;
  for(int i=0; i<numRows; i++)
    result += v1[i] * v2[i];

  return result;
}

double CGSolver::ComputeTriDotProduct(double * x, double * y, double * z)
{
  double result = 0;
  for(int i=0; i<numRows; i++)
    result += x[i] * y[i] * z[i];

  return result;
}

