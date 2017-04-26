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

#include "isotropicHyperelasticFEMForceModel.h"

IsotropicHyperelasticFEMForceModel::IsotropicHyperelasticFEMForceModel(IsotropicHyperelasticFEM * isotropicHyperelasticFEM_): isotropicHyperelasticFEM(isotropicHyperelasticFEM_)
{
  r = 3 * isotropicHyperelasticFEM->GetTetMesh()->getNumVertices();
}

IsotropicHyperelasticFEMForceModel::~IsotropicHyperelasticFEMForceModel() {}

double IsotropicHyperelasticFEMForceModel::GetElasticEnergy(double * u)
{
  return isotropicHyperelasticFEM->ComputeEnergy(u);
}

void IsotropicHyperelasticFEMForceModel::GetInternalForce(double * u, double * internalForces)
{
  isotropicHyperelasticFEM->ComputeForces(u, internalForces);
}

void IsotropicHyperelasticFEMForceModel::GetTangentStiffnessMatrixTopology(SparseMatrix ** tangentStiffnessMatrix)
{
  isotropicHyperelasticFEM->GetStiffnessMatrixTopology(tangentStiffnessMatrix);
}

void IsotropicHyperelasticFEMForceModel::GetTangentStiffnessMatrix(double * u, SparseMatrix * tangentStiffnessMatrix)
{
  isotropicHyperelasticFEM->GetTangentStiffnessMatrix(u, tangentStiffnessMatrix);
} 

void IsotropicHyperelasticFEMForceModel::GetForceAndMatrix(double * u, double * internalForces, SparseMatrix * tangentStiffnessMatrix)
{
  isotropicHyperelasticFEM->GetForceAndTangentStiffnessMatrix(u, internalForces, tangentStiffnessMatrix);
}

