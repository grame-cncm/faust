/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sparseSolver" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC   *
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
  Helper class for the ARPACK solver.
*/

#ifndef _INVZTAZSOLVER_H_
#define _INVZTAZSOLVER_H_

#include "ZTAZMultiplicator.h"
#include "CGSolver.h"
#include "PardisoSolver.h"
/*
  Given a vector rhs, compute (Z^T A Z)^{-1} rhs
  Z = P [ -C_p^{-1} C_n  ]
        [   I            ]
*/
class InvZTAZSolver
{
public:
  InvZTAZSolver(SparseMatrix * A, PardisoSolver * ZTAZPardisoSolver, SparseMatrix * P, Matrix<double> * invCp, Matrix<double> * Cn);
  virtual ~InvZTAZSolver();

  // Solve for: (Z^T A Z) x = rhs
  //   x = (Z^T A Z)^{-1} rhs
  // rhs is not modified
  void ComputeInvZTAZ(double * x, double * rhs);

protected:
  PardisoSolver * ZTAZPardisoSolver;
  CGSolver * cgSolver;
  ZTAZMultiplicator * zTAZMultiplicator;

  static void Multiplicator(const void * data, const double * x, double * Ax);

};

#endif

