/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 *  Copyright (C) 2007 CMU, 2009 MIT, 2016 USC                           *
 *                                                                       *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Hongyi Xu, Jernej Barbic                                *
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

#include "invZTAZSolver.h"
#include "performanceCounter.h"

InvZTAZSolver::InvZTAZSolver(SparseMatrix * A, PardisoSolver * ZTAZPardisoSolver_, SparseMatrix * P, Matrix<double> * invCp, Matrix<double> * Cn):ZTAZPardisoSolver(ZTAZPardisoSolver_)
{
  int n3 = A->Getn();
  int c = Cn->Getm(); // number of rows in Cn

  zTAZMultiplicator = new ZTAZMultiplicator(A, P, invCp, Cn);
  cgSolver = new CGSolver(n3 - c, InvZTAZSolver::Multiplicator, (void*)zTAZMultiplicator);
}

void InvZTAZSolver::Multiplicator(const void * data, const double * x, double * Ax)
{
  ZTAZMultiplicator * zTAZMultiplicator = (ZTAZMultiplicator*)data;
  zTAZMultiplicator->Multiply(x, Ax);
}

InvZTAZSolver::~InvZTAZSolver()
{
  delete(zTAZMultiplicator);
  delete(cgSolver);
}

void InvZTAZSolver::ComputeInvZTAZ(double * x, double * output)
{
  //cgSolver->SolveLinearSystem(x, output);
  ZTAZPardisoSolver->SolveLinearSystem(x, output);

  cgSolver->SolveLinearSystemWithPreconditioner(ZTAZPardisoSolver, x, output, 1E-3, 200, 0);
 // cgSolver->SolveLinearSystemWithoutPreconditioner(x, output, 1E-3, 200, 0);
}

