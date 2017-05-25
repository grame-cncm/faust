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

/*
  Cloth model from [Baraff Witkin 1998] 
*/

#ifndef _CLOTHBWFORCEMODEL_H_
#define _CLOTHBWFORCEMODEL_H_

#include "clothBW.h"
#include "forceModel.h"

class ClothBWForceModel : public virtual ForceModel
{
public:
  ClothBWForceModel(ClothBW * clothBW);
  virtual ~ClothBWForceModel();
  
  virtual double GetElasticEnergy(double * u);
  virtual void GetInternalForce(double * u, double * internalForces);
  virtual void GetTangentStiffnessMatrixTopology(SparseMatrix ** tangentStiffnessMatrix);
  virtual void GetTangentStiffnessMatrix(double * u, SparseMatrix * tangentStiffnessMatrix); 
  virtual void GetForceAndMatrix (double * u, double * internalForces, SparseMatrix * tangentStiffnessMatrix);
protected:
  ClothBW * clothBW;
};

#endif

