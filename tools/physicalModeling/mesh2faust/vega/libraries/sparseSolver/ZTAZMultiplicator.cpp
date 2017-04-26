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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ZTAZMultiplicator.h"
#include "performanceCounter.h"

ZTAZMultiplicator::ZTAZMultiplicator(SparseMatrix * A_, SparseMatrix * P_, Matrix<double> * invCp_, Matrix<double> * Cn_): A(A_), P(P_), invCp(invCp_), Cn(Cn_)
{
  buffer1 = (double*) malloc (sizeof(double) * A->Getn());
  buffer2 = (double*) malloc (sizeof(double) * A->Getn());
  invCpCn = new Matrix<double>((*invCp) * (*Cn));
  invCpCnT = new Matrix<double>(Transpose(*invCpCn));
}

ZTAZMultiplicator::~ZTAZMultiplicator()
{
  free(buffer1);
  free(buffer2);
  delete(invCpCn);
  delete(invCpCnT);
}

/*
  computes x |--> Z^T A Z x

  Z = P [ -C_p^{-1} C_n  ]
        [   I            ]
*/
void ZTAZMultiplicator::Multiply(const double * x, double * output)
{
  int n3 = A->Getn();
  int c = Cn->Getm(); // number of rows in Cn
  Matrix<double> xM(n3 - c, 1, x, false, false); // dimension of x must be n3 - c
  Matrix<double> buff_c(c, 1, buffer1, false, false);
  buff_c = *invCpCn * xM;
  buff_c *= -1.0; // first c rows of buffer1 are now set
  memcpy(&buffer1[c], x, sizeof(double) * (n3-c)); // multiplication with identity

  P->MultiplyVector(buffer1, buffer2);
  A->MultiplyVector(buffer2, buffer1);
  P->TransposeMultiplyVector(buffer1, n3, buffer2);

  Matrix<double> buff2_c(c, 1, buffer2, false, false);
  Matrix<double> outputM(n3-c, 1, output, false, false); // size of output is n3 - c
  outputM = *invCpCnT * buff2_c;
  outputM *= -1.0;
  for(int i = 0; i < n3-c; i++)
    output[i] += buffer2[i+c];
}

