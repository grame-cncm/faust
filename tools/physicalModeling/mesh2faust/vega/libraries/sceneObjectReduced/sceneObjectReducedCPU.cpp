/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sceneObject" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC    *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Daniel Schroeder                         *
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "sceneObjectReducedCPU.h"

SceneObjectReducedCPU::SceneObjectReducedCPU(const char * filenameOBJ, ModalMatrix * modalMatrix): SceneObjectWithRestPosition(filenameOBJ), SceneObjectReduced(filenameOBJ, modalMatrix) 
{
  Construct(modalMatrix);
}

SceneObjectReducedCPU::SceneObjectReducedCPU(ObjMesh * objMesh, ModalMatrix * modalMatrix, bool deepCopy): SceneObjectWithRestPosition(objMesh, deepCopy), SceneObjectReduced(objMesh, modalMatrix, deepCopy) 
{
  Construct(modalMatrix);
}

void SceneObjectReducedCPU::Construct(ModalMatrix * modalMatrix)
{
  if (n != modalMatrix->Getn())
  {
    printf("Error (SceneObjectReducedCPU): modal matrix size (%d) doesn't match the number of "
           "obj file vertices (%d).\n", modalMatrix->Getn(), n);
    exit(1);
  }

  u = (double*) calloc (3*n,sizeof(double));
}

void SceneObjectReducedCPU::Setq(double * q)
{
  memcpy(this->q,q,sizeof(double)*r);
}

void SceneObjectReducedCPU::Getq(double * q)
{
  memcpy(q,this->q,sizeof(double)*r);
}

void SceneObjectReducedCPU::Getu(double * u)
{
  memcpy(u, this->u, sizeof(double) * 3 * n);
}

void SceneObjectReducedCPU::Compute_uUq()
{
  modalMatrix->AssembleVector(q,u);
  SetVertexDeformations(u);
}

int SceneObjectReducedCPU::GetClosestVertex(Vec3d & queryPos, double * distance, double * auxVertexBuffer)
{
  return SceneObject::GetClosestVertex(queryPos, distance,  auxVertexBuffer);
}

