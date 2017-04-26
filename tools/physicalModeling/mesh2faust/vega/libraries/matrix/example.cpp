/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "matrix" library , Copyright (C) 2007 CMU, 2009 MIT                   *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/code                                      *
 * Research: Jernej Barbic, Doug L. James, Jovan Popovic                 *
 * Funding: NSF, Link Foundation, Singapore-MIT GAMBIT Game Lab          *
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

#include "matrix.h"

/*
  A simple example using the matrix class.
*/

int main()
{
  double Av[9] = {2.0, 1.0, 1.0,
                  1.0, 2.0, 1.0,
                  1.0, 1.0, 2.0, };

  Matrix<double> A(3, 3, Av);
  Matrix<double> B = 0.5 * Transpose(A) * A;
  printf("Matrix:\n");
  B.Print();
  char outputFilename[96] = "BMatrix";
  B.Save(outputFilename);

  Matrix<double> Q(3,3); // will hold eigenvectors
  Matrix<double> Lambda(3,1); // will hold eigenvalues
  B.SymmetricEigenDecomposition(Q, Lambda);

  printf("Eigenvalues:\n");
  Lambda.Print();

  return 0;
}

