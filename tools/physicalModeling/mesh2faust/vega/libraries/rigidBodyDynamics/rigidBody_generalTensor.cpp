/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "rigidBodyDynamics" library , Copyright (C) 2007 CMU                  *
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

#include "rigidBody_generalTensor.h"
#include "matrixMultiplyMacros.h"

RigidBody_GeneralTensor::RigidBody_GeneralTensor(double mass, double inertiaTensorAtRest[9]):
  RigidBody(mass,inertiaTensorAtRest[0],inertiaTensorAtRest[4],inertiaTensorAtRest[8])
{ 
  SetInertiaTensor(inertiaTensorAtRest);
}

void RigidBody_GeneralTensor::SetInertiaTensor(double inertiaTensorAtRest[9], int updateAngularVelocity)
{
  memcpy(this->inertiaTensorAtRest, inertiaTensorAtRest, sizeof(double) * 9);

  // compute inverse inertia tensor at rest
  Invert3x3Matrix(this->inertiaTensorAtRest, inverseInertiaTensorAtRest);

  inverseInertiaTensorAtRestX = inverseInertiaTensorAtRest[0];
  inverseInertiaTensorAtRestY = inverseInertiaTensorAtRest[4];
  inverseInertiaTensorAtRestZ = inverseInertiaTensorAtRest[8];

  // change the angular velocity accordingly
  if (updateAngularVelocity)
    ComputeAngularVelocity();
}

// computes the inertia tensor, using the current rotation matrix 
// inertia tensor at rest is assumed general (i.e. not necessary diagonal)
// 120 flops
void RigidBody_GeneralTensor::ComputeInertiaTensor(double inertiaTensor[9])
{
  //inertiaTensor = R * inertiaTensorAtRest * R^T
  
  inertiaTensor[0] = 
      R[0] * (inertiaTensorAtRest[0] * R[0] + inertiaTensorAtRest[1] * R[1] + inertiaTensorAtRest[2] * R[2]) + 
      R[1] * (inertiaTensorAtRest[1] * R[0] + inertiaTensorAtRest[4] * R[1] + inertiaTensorAtRest[5] * R[2]) + 
      R[2] * (inertiaTensorAtRest[2] * R[0] + inertiaTensorAtRest[5] * R[1] + inertiaTensorAtRest[8] * R[2]);

  inertiaTensor[1] = 
      R[0] * (inertiaTensorAtRest[0] * R[3] + inertiaTensorAtRest[1] * R[4] + inertiaTensorAtRest[2] * R[5]) +
      R[1] * (inertiaTensorAtRest[1] * R[3] + inertiaTensorAtRest[4] * R[4] + inertiaTensorAtRest[5] * R[5]) +
      R[2] * (inertiaTensorAtRest[2] * R[3] + inertiaTensorAtRest[5] * R[4] + inertiaTensorAtRest[8] * R[5]);

  inertiaTensor[2] = 
      R[0] * (inertiaTensorAtRest[0] * R[6] + inertiaTensorAtRest[1] * R[7] + inertiaTensorAtRest[2] * R[8]) +
      R[1] * (inertiaTensorAtRest[1] * R[6] + inertiaTensorAtRest[4] * R[7] + inertiaTensorAtRest[5] * R[8]) +
      R[2] * (inertiaTensorAtRest[2] * R[6] + inertiaTensorAtRest[5] * R[7] + inertiaTensorAtRest[8] * R[8]);

  inertiaTensor[4] = 
      R[3] * (inertiaTensorAtRest[0] * R[3] + inertiaTensorAtRest[1] * R[4] + inertiaTensorAtRest[2] * R[5]) + 
      R[4] * (inertiaTensorAtRest[1] * R[3] + inertiaTensorAtRest[4] * R[4] + inertiaTensorAtRest[5] * R[5]) + 
      R[5] * (inertiaTensorAtRest[2] * R[3] + inertiaTensorAtRest[5] * R[4] + inertiaTensorAtRest[8] * R[5]);

  inertiaTensor[5] = 
      R[3] * (inertiaTensorAtRest[0] * R[6] + inertiaTensorAtRest[1] * R[7] + inertiaTensorAtRest[2] * R[8]) +
      R[4] * (inertiaTensorAtRest[1] * R[6] + inertiaTensorAtRest[4] * R[7] + inertiaTensorAtRest[5] * R[8]) +
      R[5] * (inertiaTensorAtRest[2] * R[6] + inertiaTensorAtRest[5] * R[7] + inertiaTensorAtRest[8] * R[8]);

  inertiaTensor[8] = 
      R[6] * (inertiaTensorAtRest[0] * R[6] + inertiaTensorAtRest[1] * R[7] + inertiaTensorAtRest[2] * R[8]) + 
      R[7] * (inertiaTensorAtRest[1] * R[6] + inertiaTensorAtRest[4] * R[7] + inertiaTensorAtRest[5] * R[8]) + 
      R[8] * (inertiaTensorAtRest[2] * R[6] + inertiaTensorAtRest[5] * R[7] + inertiaTensorAtRest[8] * R[8]);

  // inertia tensor is symmetric
  inertiaTensor[3] = inertiaTensor[1];
  inertiaTensor[6] = inertiaTensor[2];
  inertiaTensor[7] = inertiaTensor[5];
}

// computes the angular velocity from the angular momentum
// using the current rotation matrix
// inertia tensor at rest is dense
// 45 flops
// w = R * I^{body}^{-1} * R^T * L
void RigidBody_GeneralTensor::ComputeAngularVelocity()
{
  double temp0, temp1, temp2;
  // temp = R^T * L 
  temp0 = R[0] * angularMomentumX + R[3] * angularMomentumY + R[6] * angularMomentumZ;
  temp1 = R[1] * angularMomentumX + R[4] * angularMomentumY + R[7] * angularMomentumZ;
  temp2 = R[2] * angularMomentumX + R[5] * angularMomentumY + R[8] * angularMomentumZ;

  // temp' = I^{body}^{-1} * temp 
  double temp3, temp4, temp5;
  temp3 = inverseInertiaTensorAtRest[0] * temp0 + inverseInertiaTensorAtRest[1] * temp1 + inverseInertiaTensorAtRest[2] * temp2;
  temp4 = inverseInertiaTensorAtRest[3] * temp0 + inverseInertiaTensorAtRest[4] * temp1 + inverseInertiaTensorAtRest[5] * temp2;
  temp5 = inverseInertiaTensorAtRest[6] * temp0 + inverseInertiaTensorAtRest[7] * temp1 + inverseInertiaTensorAtRest[8] * temp2;

  // angularVelocity = R * temp
  angularVelocityX = R[0] * temp3 + R[1] * temp4 + R[2] * temp5;
  angularVelocityY = R[3] * temp3 + R[4] * temp4 + R[5] * temp5;
  angularVelocityZ = R[6] * temp3 + R[7] * temp4 + R[8] * temp5;
}

void RigidBody_GeneralTensor::GetInverseInertiaTensor(double * inverseInertiaTensor)
{
  //inverseInertiaTensor = R * inverseInertiaTensorAtRest * R^T
  //double helperMatrix[9];
  //MATRIX_MULTIPLY3X3ABT(inverseInertiaTensorAtRest, R, helperMatrix);
  //MATRIX_MULTIPLY3X3(R, helperMatrix, inverseInertiaTensor);
  inverseInertiaTensor[0] = 
    R[0] * (inverseInertiaTensorAtRest[0] * R[0] + inverseInertiaTensorAtRest[1] * R[1] + inverseInertiaTensorAtRest[2] * R[2]) + 
    R[1] * (inverseInertiaTensorAtRest[1] * R[0] + inverseInertiaTensorAtRest[4] * R[1] + inverseInertiaTensorAtRest[5] * R[2]) + 
    R[2] * (inverseInertiaTensorAtRest[2] * R[0] + inverseInertiaTensorAtRest[5] * R[1] + inverseInertiaTensorAtRest[8] * R[2]);

  inverseInertiaTensor[1] = 
    R[0] * (inverseInertiaTensorAtRest[0] * R[3] + inverseInertiaTensorAtRest[1] * R[4] + inverseInertiaTensorAtRest[2] * R[5]) +
    R[1] * (inverseInertiaTensorAtRest[1] * R[3] + inverseInertiaTensorAtRest[4] * R[4] + inverseInertiaTensorAtRest[5] * R[5]) +
    R[2] * (inverseInertiaTensorAtRest[2] * R[3] + inverseInertiaTensorAtRest[5] * R[4] + inverseInertiaTensorAtRest[8] * R[5]);

  inverseInertiaTensor[2] = 
    R[0] * (inverseInertiaTensorAtRest[0] * R[6] + inverseInertiaTensorAtRest[1] * R[7] + inverseInertiaTensorAtRest[2] * R[8]) +
    R[1] * (inverseInertiaTensorAtRest[1] * R[6] + inverseInertiaTensorAtRest[4] * R[7] + inverseInertiaTensorAtRest[5] * R[8]) +
    R[2] * (inverseInertiaTensorAtRest[2] * R[6] + inverseInertiaTensorAtRest[5] * R[7] + inverseInertiaTensorAtRest[8] * R[8]);

  inverseInertiaTensor[4] = 
    R[3] * (inverseInertiaTensorAtRest[0] * R[3] + inverseInertiaTensorAtRest[1] * R[4] + inverseInertiaTensorAtRest[2] * R[5]) + 
    R[4] * (inverseInertiaTensorAtRest[1] * R[3] + inverseInertiaTensorAtRest[4] * R[4] + inverseInertiaTensorAtRest[5] * R[5]) + 
    R[5] * (inverseInertiaTensorAtRest[2] * R[3] + inverseInertiaTensorAtRest[5] * R[4] + inverseInertiaTensorAtRest[8] * R[5]);

  inverseInertiaTensor[5] = 
    R[3] * (inverseInertiaTensorAtRest[0] * R[6] + inverseInertiaTensorAtRest[1] * R[7] + inverseInertiaTensorAtRest[2] * R[8]) +
    R[4] * (inverseInertiaTensorAtRest[1] * R[6] + inverseInertiaTensorAtRest[4] * R[7] + inverseInertiaTensorAtRest[5] * R[8]) +
    R[5] * (inverseInertiaTensorAtRest[2] * R[6] + inverseInertiaTensorAtRest[5] * R[7] + inverseInertiaTensorAtRest[8] * R[8]);

  inverseInertiaTensor[8] = 
    R[6] * (inverseInertiaTensorAtRest[0] * R[6] + inverseInertiaTensorAtRest[1] * R[7] + inverseInertiaTensorAtRest[2] * R[8]) + 
    R[7] * (inverseInertiaTensorAtRest[1] * R[6] + inverseInertiaTensorAtRest[4] * R[7] + inverseInertiaTensorAtRest[5] * R[8]) + 
    R[8] * (inverseInertiaTensorAtRest[2] * R[6] + inverseInertiaTensorAtRest[5] * R[7] + inverseInertiaTensorAtRest[8] * R[8]);

  // inverse inertia tensor is symmetric
  inverseInertiaTensor[3] = inverseInertiaTensor[1];
  inverseInertiaTensor[6] = inverseInertiaTensor[2];
  inverseInertiaTensor[7] = inverseInertiaTensor[5];
}

void RigidBody_GeneralTensor::GetInverseInertiaTensorAtRest(double * inverseInertiaTensorAtRest_)
{
  MATRIX_SET3X3(inverseInertiaTensorAtRest_, inverseInertiaTensorAtRest);
}

