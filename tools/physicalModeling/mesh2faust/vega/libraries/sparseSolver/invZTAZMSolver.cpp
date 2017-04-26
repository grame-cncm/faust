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

#include "invZTAZMSolver.h"

InvZTAZMSolver::InvZTAZMSolver(SparseMatrix * A, SparseMatrix * M, PardisoSolver * ZTAZPardisoSolver, SparseMatrix * P, Matrix<double> * invCp, Matrix<double> * Cn)
{
  zTMZMultiplicator = new ZTAZMultiplicator(M, P, invCp, Cn);
  invZTAZSolver = new InvZTAZSolver(A, ZTAZPardisoSolver, P, invCp, Cn);

  int n3 = A->Getn();
  int c = Cn->Getm(); // number of rows in Cn
  dim = n3 - c;
  buffer = (double*) malloc (sizeof(double) * dim);
}

InvZTAZMSolver::~InvZTAZMSolver()
{
  delete(zTMZMultiplicator);
  delete(invZTAZSolver);
  free(buffer);
}

// output <-- (Z^T A Z)^{-1} (Z^T M Z) x
// x <-- (Z^T M Z) x
void InvZTAZMSolver::ComputeInvZTAZM(double * x, double * output)
{
  zTMZMultiplicator->Multiply(x, buffer);
  memcpy(x, buffer, sizeof(double) * dim);
  invZTAZSolver->ComputeInvZTAZ(output, buffer);
}

