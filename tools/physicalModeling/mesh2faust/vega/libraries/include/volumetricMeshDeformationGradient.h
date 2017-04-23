/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC *
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
   Given a volumetric mesh and its deformations,
   computes the deformation gradient, and other related quantities.
*/

#ifndef _VOLUMETRICMESHDEFORMATIONGRADIENT_H_
#define _VOLUMETRICMESHDEFORMATIONGRADIENT_H_

#include "volumetricMesh.h"

class VolumetricMeshDeformationGradient
{
public:
  // computes the deformation gradient for the deformation given by the displacement vector u (length 3n, where n=#vertices), for the element with index "elementIndex"
  // F is a 3x3 matrix, stored row-major into a vector of length 9
  static void ComputeDeformationGradient(VolumetricMesh * mesh, double * u, int elementIndex, double * F);

  // computes the three principal stretches (singular values of F)
  // lambdas are returned in descending order
  // returns 0 on success, and non-zero on SVD failure
  static int ComputePrincipalStretches(double * F, double * lambda);

  // maximal stretch in the entire mesh
  static double ComputeMaximalStretch(VolumetricMesh * mesh, double * u);

protected:

};

#endif

