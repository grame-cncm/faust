/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "StVK" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC           *
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

#include "StVKCubeABCD.h"
#include "cubicMeshIntegrals.cpp"

StVKCubeABCD::StVKCubeABCD(double cubeSize)
{
  double * rawIntegrals = cubicMeshIntegrals;

  int i,j,k,l;

  // A
  for (i=0; i<8; i++)
    for (j=0; j<8; j++)
      for (k=0; k<3; k++)
        for (l=0; l<3; l++)
        {
          A_[i][j][k][l] = cubeSize * *rawIntegrals;
          rawIntegrals++;
        }

  // B
  for (i=0; i<8; i++)
    for (j=0; j<8; j++)
    {
      B_[i][j] = cubeSize * *rawIntegrals;
      rawIntegrals++;
    }

  // C
  for (i=0; i<8; i++)
    for (j=0; j<8; j++)
      for (k=0; k<8; k++)
        for (l=0; l<3; l++)
        {
          C_[i][j][k][l] = *rawIntegrals;
          rawIntegrals++;
        }

  // D
  for (i=0; i<8; i++)
    for (j=0; j<8; j++)
      for (k=0; k<8; k++)
        for (l=0; l<8; l++)
        {
          D_[i][j][k][l] = 1.0 / cubeSize * *rawIntegrals;
          rawIntegrals++;
        }
}

