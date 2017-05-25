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
#include "sceneObjectReduced.h"

SceneObjectReduced::SceneObjectReduced(const char * filenameOBJ, ModalMatrix * modalMatrix): SceneObjectWithRestPosition(filenameOBJ), SceneObjectDeformable(filenameOBJ) 
{
  Construct(modalMatrix);
}

SceneObjectReduced::SceneObjectReduced(ObjMesh * objMesh, ModalMatrix * modalMatrix, bool deepCopy): SceneObjectWithRestPosition(objMesh, deepCopy), SceneObjectDeformable(objMesh, deepCopy) 
{
  Construct(modalMatrix);
}

void SceneObjectReduced::Construct(ModalMatrix * modalMatrix)
{
  this->modalMatrix = modalMatrix;
  r = modalMatrix->Getr();
  q = (double*) calloc (r,sizeof(double));
}

SceneObjectReduced::~SceneObjectReduced()
{
  free(q);
}

void SceneObjectReduced::SetZeroq()
{
  memset(q, 0, sizeof(double) * r);
}

void SceneObjectReduced::Scaleq(double scale)
{
  for(int i=0; i<r; i++)
    q[i] *= scale;
}

