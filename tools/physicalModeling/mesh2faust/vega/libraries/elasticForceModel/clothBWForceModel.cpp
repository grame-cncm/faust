/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "forceModel" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC     *
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

#include "clothBWForceModel.h"

ClothBWForceModel::ClothBWForceModel(ClothBW * clothBW_): clothBW(clothBW_)
{ 
  r = 3 * clothBW->GetNumVertices(); 
}

ClothBWForceModel::~ClothBWForceModel()
{
}

double ClothBWForceModel::GetElasticEnergy(double * u)
{
  return clothBW->ComputeEnergy(u);
}

void ClothBWForceModel::GetInternalForce(double * u, double * internalForces)
{
  clothBW->ComputeForce(u, internalForces);
}

void ClothBWForceModel::GetTangentStiffnessMatrixTopology(SparseMatrix ** tangentStiffnessMatrix)
{
  clothBW->GenerateStiffnessMatrixTopology(tangentStiffnessMatrix);
}

void ClothBWForceModel::GetTangentStiffnessMatrix(double * u, SparseMatrix * tangentStiffnessMatrix)
{
  clothBW->ComputeStiffnessMatrix(u, tangentStiffnessMatrix);
} 

void ClothBWForceModel::GetForceAndMatrix (double * u, double * internalForces, SparseMatrix * tangentStiffnessMatrix)
{
  clothBW->ComputeForceAndMatrix(u, internalForces, tangentStiffnessMatrix);
}
