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

#ifndef _GENERATEINTERPOLATIONMATRIX_H_
#define _GENERATEINTERPOLATIONMATRIX_H_

#include "sparseMatrix.h"

// creates the sparse matrix A that interpolates a quantity from volumetric 
// mesh vertices to an embedded triangle mesh:
// y = A * x
// y ... triangle mesh quantity
// x ... volumetric mesh quantity

class GenerateInterpolationMatrix
{
public:
  // If numSourceLocations is >= 0, matrix A will be right-padded with 
  // appropriate zero columns. Typically, numSourceLocations should be the 
  // number of volumetric mesh vertices.
  // numTargetLocations, numElementVertices, vertices, weights, can be 
  // generated using the interpolation capabilities of the VolumetricMesh class
  static void generate(int numTargetLocations, int numElementVertices, const int * vertices, const double * weights, SparseMatrix ** A, int numSourceLocations=-1); 
};

#endif

