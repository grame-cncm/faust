/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "Large Modal Deformation Factory",                                    *
 * a pre-processing utility for model reduction of                       *
 * deformable objects undergoing large deformations.                     *
 *                                                                       *
 *  Copyright (C) 2007 CMU, 2009 MIT, 2016 USC                           *
 *                                                                       *
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

#include <string.h>
#include "matrixMacros.h"
#include "minivector.h"
#include "computeStiffnessMatrixNullspace.h"

void ComputeStiffnessMatrixNullspace::ComputeNullspace(int n, const double * vertexPos, double * basis, int includeRotationalNullspace, int generateOrthogonalBasis)
{
  int basisSize = (includeRotationalNullspace ? 6 : 3);

  memset(basis, 0, sizeof(double) * 3 * n * basisSize);

  // translational part
  for(int i=0; i<n; i++)
    for(int j=0; j<3; j++)
      basis[ELT(3*n, 3*i+j, j)] = 1.0;

  // rotational part
  if (includeRotationalNullspace)
  {
    for(int i=0; i<n; i++)
    {
      Vec3d p(vertexPos[3*i+0], vertexPos[3*i+1], vertexPos[3*i+2]);
      Vec3d e0(1,0,0);
      Vec3d e1(0,1,0);
      Vec3d e2(0,0,1);
      Vec3d r0 = cross(e0, p);
      Vec3d r1 = cross(e1, p);
      Vec3d r2 = cross(e2, p);
      for(int j=0; j<3; j++)
      {
        basis[ELT(3*n, 3*i+j, 3)] = r0[j];
        basis[ELT(3*n, 3*i+j, 4)] = r1[j];
        basis[ELT(3*n, 3*i+j, 5)] = r2[j];
      }
    }
  }

  if (generateOrthogonalBasis)
  {
    // normalize translational vectors
    for(int v=0; v<3; v++)
    {
      double norm2 = 0.0;
      for(int i=0; i<3*n; i++)
        norm2 += basis[ELT(3*n, i, v)] * basis[ELT(3*n, i, v)];
      double invNorm = 1.0 / sqrt(norm2);
      for(int i=0; i<3*n; i++)
        basis[ELT(3*n, i, v)] *= invNorm; 
    }
    
    // ortho-normalize rotational vectors
    if (includeRotationalNullspace)
    {
      for(int v=0; v<3; v++)
      {
        for(int j=0; j<3+v; j++)
        {
          double dotp = 0.0;
          for(int i=0; i<3*n; i++)
            dotp += basis[ELT(3*n, i, j)] * basis[ELT(3*n, i, 3+v)];
          for(int i=0; i<3*n; i++)
            basis[ELT(3*n, i, 3+v)] -= dotp * basis[ELT(3*n, i, j)];
  
          double norm2 = 0.0;
          for(int i=0; i<3*n; i++)
            norm2 += basis[ELT(3*n, i, 3+v)] * basis[ELT(3*n, i, 3+v)];
          double invNorm = 1.0 / sqrt(norm2);
          for(int i=0; i<3*n; i++)
            basis[ELT(3*n, i, 3+v)] *= invNorm; 
        }
      }
    }
  }
}

void ComputeStiffnessMatrixNullspace::RemoveNullspaceComponent(int n, int nullspaceDimension, const double * nullspaceOrthonormalBasis, double * x)
{
  for(int i=0; i<nullspaceDimension; i++)
  {
    double dotp=0.0;
    for(int j=0; j<3*n; j++)
      dotp += x[j] * nullspaceOrthonormalBasis[ELT(3*n, j, i)];
    for(int j=0; j<3*n; j++)
      x[j] -= dotp * nullspaceOrthonormalBasis[ELT(3*n, j, i)];
  }
}

