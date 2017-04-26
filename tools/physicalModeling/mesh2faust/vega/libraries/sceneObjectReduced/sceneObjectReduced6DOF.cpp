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

#include "sceneObjectReduced6DOF.h"

SceneObjectReduced6DOF::SceneObjectReduced6DOF(const char * filenameOBJ, ModalMatrix * modalMatrix): SceneObjectWithRestPosition(filenameOBJ), SceneObjectReduced(filenameOBJ, modalMatrix), SceneObject6DOF(filenameOBJ), qvel(NULL)
{
}

SceneObjectReduced6DOF::SceneObjectReduced6DOF(ObjMesh * objMesh, ModalMatrix * modalMatrix, bool deepCopy): SceneObjectWithRestPosition(objMesh, deepCopy), SceneObjectReduced(objMesh, modalMatrix, deepCopy), SceneObject6DOF(objMesh, deepCopy), qvel(NULL)
{
}

SceneObjectReduced6DOF::~SceneObjectReduced6DOF() 
{
  free(qvel);
}

void SceneObjectReduced6DOF::GetSingleVertexPosition(int vertex, double * x, double * y, double * z)
{
  double x0 = restPosition[3*vertex+0];
  double y0 = restPosition[3*vertex+1];
  double z0 = restPosition[3*vertex+2];

  modalMatrix->AddAssembleSingleVertex(vertex,q,&x0,&y0,&z0);

  // transform x0, y0, z0 via centerOfMass,R
  // x = centerOfMass + R * x0
  *x = R[0] * x0 + R[1] * y0 + R[2] * z0 + centerOfMass[0];
  *y = R[3] * x0 + R[4] * y0 + R[5] * z0 + centerOfMass[1];
  *z = R[6] * x0 + R[7] * y0 + R[8] * z0 + centerOfMass[2];
}

void SceneObjectReduced6DOF::GetSingleVertexVelocity(int vertex, double * objectVel, double * objectAngVel, double * velx, double * vely, double * velz)
{
  SceneObject6DOF::GetSingleVertexVelocity(vertex, objectVel, objectAngVel, velx, vely, velz);

  double localDefoVel[3];
  modalMatrix->AssembleSingleVertex(vertex,qvel,&localDefoVel[0], &localDefoVel[1], &localDefoVel[2]);
  *velx += R[0] * localDefoVel[0] + R[1] * localDefoVel[1] + R[2] * localDefoVel[2];
  *vely += R[3] * localDefoVel[0] + R[4] * localDefoVel[1] + R[5] * localDefoVel[2];
  *velz += R[6] * localDefoVel[0] + R[7] * localDefoVel[1] + R[8] * localDefoVel[2];
}

void SceneObjectReduced6DOF::Setqvel(double * qvel_)
{
  int r = modalMatrix->Getr();
  if (qvel == NULL)
    qvel = (double*) malloc (sizeof(double) * r);
  memcpy(qvel, qvel_, sizeof(double) * r);
}


