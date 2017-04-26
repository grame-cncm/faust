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

#include "rigidBody.h"

RigidBody::RigidBody(double mass, double inertiaTensorAtRestX, double inertiaTensorAtRestY, double inertiaTensorAtRestZ)
{
  this->mass=mass;
  this->inertiaTensorAtRestX = inertiaTensorAtRestX;
  this->inertiaTensorAtRestY = inertiaTensorAtRestY;
  this->inertiaTensorAtRestZ = inertiaTensorAtRestZ;

  inverseInertiaTensorAtRestX = 1.0 / inertiaTensorAtRestX;
  inverseInertiaTensorAtRestY = 1.0 / inertiaTensorAtRestY;
  inverseInertiaTensorAtRestZ = 1.0 / inertiaTensorAtRestZ;

  linearDampingCoef = 0.0;
  rotationalDampingCoef = 0.0;

  ResetBodyToRest();
  ResetExternalForce();
  ResetExternalTorque();
}


// performs one step of Euler integration
void RigidBody::EulerStep(double timestep) 
{
  // 3dof part
  positionX += timestep * velocityX;
  positionY += timestep * velocityY;
  positionZ += timestep * velocityZ;

  velocityX += timestep * (externalForceX - linearDampingCoef * velocityX) / mass;
  velocityY += timestep * (externalForceY - linearDampingCoef * velocityY) / mass;
  velocityZ += timestep * (externalForceZ - linearDampingCoef * velocityZ) / mass;

  // 6dof part
  // update the quaternion rotation
  q = q + (0.5 * timestep) * Quaternion<double>(0,angularVelocityX,angularVelocityY,angularVelocityZ) * q;
  // re-normalize the quaternion
  q.Normalize();

  // update angularMomentum
  angularMomentumX += timestep * (externalTorqueX - rotationalDampingCoef * angularVelocityX);
  angularMomentumY += timestep * (externalTorqueY - rotationalDampingCoef * angularVelocityY);
  angularMomentumZ += timestep * (externalTorqueZ - rotationalDampingCoef * angularVelocityZ);

  // reconstruct the rotation matrix
  q.Quaternion2Matrix(R);
    
  // reconstruct angular velocity
  ComputeAngularVelocity();
}

// performs one step of Euler integration, Symplectic version
void RigidBody::EulerStepSymplectic(double timestep)
{
  // 3dof part
  velocityX += timestep * (externalForceX - linearDampingCoef * velocityX) / mass;
  velocityY += timestep * (externalForceY - linearDampingCoef * velocityY) / mass;
  velocityZ += timestep * (externalForceZ - linearDampingCoef * velocityZ) / mass;

  positionX += timestep * velocityX;
  positionY += timestep * velocityY;
  positionZ += timestep * velocityZ;

  // 6dof part
  // update angularMomentum
  angularMomentumX += timestep * (externalTorqueX - rotationalDampingCoef * angularVelocityX);
  angularMomentumY += timestep * (externalTorqueY - rotationalDampingCoef * angularVelocityY);
  angularMomentumZ += timestep * (externalTorqueZ - rotationalDampingCoef * angularVelocityZ);

  // reconstruct angular velocity
  ComputeAngularVelocity();

  // update the quaternion rotation
  q = q + (0.5 * timestep) * Quaternion<double>(0,angularVelocityX,angularVelocityY,angularVelocityZ) * q;
  // re-normalize the quaternion
  q.Normalize();
  // reconstruct the rotation matrix
  q.Quaternion2Matrix(R);
}

// computes the inertia tensor, using the current rotation matrix 
// assumes diagonal inertia tensor at rest
// 48 flops
void RigidBody::ComputeInertiaTensor(double inertiaTensor[9])
{
  //inertiaTensor = R * diag(inertiaTensorAtRestX, inertiaTensorAtRestY, inertiaTensorAtRestZ) * R^T
  
  inertiaTensor[0] = R[0] * inertiaTensorAtRestX * R[0] + R[1] * inertiaTensorAtRestY * R[1] + R[2] * inertiaTensorAtRestZ * R[2];
  inertiaTensor[1] = R[3] * inertiaTensorAtRestX * R[0] + R[4] * inertiaTensorAtRestY * R[1] + R[5] * inertiaTensorAtRestZ * R[2];
  inertiaTensor[2] = R[6] * inertiaTensorAtRestX * R[0] + R[7] * inertiaTensorAtRestY * R[1] + R[8] * inertiaTensorAtRestZ * R[2];

  inertiaTensor[4] = R[3] * inertiaTensorAtRestX * R[3] + R[4] * inertiaTensorAtRestY * R[4] + R[5] * inertiaTensorAtRestZ * R[5];
  inertiaTensor[5] = R[6] * inertiaTensorAtRestX * R[3] + R[7] * inertiaTensorAtRestY * R[4] + R[8] * inertiaTensorAtRestZ * R[5];

  inertiaTensor[8] = R[6] * inertiaTensorAtRestX * R[6] + R[7] * inertiaTensorAtRestY * R[7] + R[8] * inertiaTensorAtRestZ * R[8];

  // symmetric
  inertiaTensor[3] = inertiaTensor[1];
  inertiaTensor[6] = inertiaTensor[2];
  inertiaTensor[7] = inertiaTensor[5];
}

// computes the angular velocity from the angular momentum
// using the current rotation matrix 
// inertia tensor at rest is diagonal
// 33 flops
// w = R * I^{body}^{-1} * R^T * L
void RigidBody::ComputeAngularVelocity()
{
  double temp0, temp1, temp2;
 
  // temp = R^T * L 
  temp0 = R[0] * angularMomentumX + R[3] * angularMomentumY + R[6] * angularMomentumZ;
  temp1 = R[1] * angularMomentumX + R[4] * angularMomentumY + R[7] * angularMomentumZ;
  temp2 = R[2] * angularMomentumX + R[5] * angularMomentumY + R[8] * angularMomentumZ;

  // temp = I^{body}^{-1} * temp = diag(invIBodyX, invIBodyY, invIBodyZ) * temp;
  temp0 = inverseInertiaTensorAtRestX * temp0;
  temp1 = inverseInertiaTensorAtRestY * temp1;
  temp2 = inverseInertiaTensorAtRestZ * temp2;

  // angularVelocity = R * temp
  angularVelocityX = R[0] * temp0 + R[1] * temp1 + R[2] * temp2;
  angularVelocityY = R[3] * temp0 + R[4] * temp1 + R[5] * temp2;
  angularVelocityZ = R[6] * temp0 + R[7] * temp1 + R[8] * temp2;
}

// inverts a 3x3 matrix
void RigidBody::Invert3x3Matrix(double * A, double * AInv)
{
  // det(A)
  double invDeterminant = 1.0 / 
           (-A[2] * A[4] * A[6] + 
             A[1] * A[5] * A[6] + 
             A[2] * A[3] * A[7] - 
	     A[0] * A[5] * A[7] - 
	     A[1] * A[3] * A[8] + 
	     A[0] * A[4] * A[8]);

  AInv[0] = invDeterminant * (-A[5] * A[7] + A[4] * A[8]);
  AInv[1] = invDeterminant * (A[2] * A[7] - A[1] * A[8]);
  AInv[2] = invDeterminant * (-A[2] * A[4] + A[1] * A[5]);
  AInv[3] = invDeterminant * (A[5] * A[6] - A[3] * A[8]);
  AInv[4] = invDeterminant * (-A[2] * A[6] + A[0] * A[8]);
  AInv[5] = invDeterminant * (A[2] * A[3] - A[0] * A[5]);
  AInv[6] = invDeterminant * (-A[4] * A[6] + A[3] * A[7]);
  AInv[7] = invDeterminant * (A[1] * A[6] - A[0] * A[7]);
  AInv[8] = invDeterminant * (-A[1] * A[3] + A[0] * A[4]);
}

void RigidBody::SetToAnotherBody(RigidBody & anotherBody)
{
  positionX = anotherBody.positionX;  
  positionY = anotherBody.positionY;  
  positionZ = anotherBody.positionZ;  

  velocityX = anotherBody.velocityX;  
  velocityY = anotherBody.velocityY;  
  velocityZ = anotherBody.velocityZ;  

  angularVelocityX = anotherBody.angularVelocityX;  
  angularVelocityY = anotherBody.angularVelocityY;  
  angularVelocityZ = anotherBody.angularVelocityZ;  

  angularMomentumX = anotherBody.angularMomentumX;  
  angularMomentumY = anotherBody.angularMomentumY;  
  angularMomentumZ = anotherBody.angularMomentumZ;  
 
  for(int i=0; i<9; i++)
    R[i] = (anotherBody.R)[i];

  q = anotherBody.q;
}

void RigidBody::TransformToLocal(double * globalVector, double * localVector)
{
  // global = R * local + pos
  double temp[3] = { globalVector[0] - positionX, globalVector[1] - positionY, globalVector[2] - positionZ };

  localVector[0] = R[0] * temp[0] + R[3] * temp[1] + R[6] * temp[2];
  localVector[1] = R[1] * temp[0] + R[4] * temp[1] + R[7] * temp[2];
  localVector[2] = R[2] * temp[0] + R[5] * temp[1] + R[8] * temp[2];
}

void RigidBody::TransformToGlobal(double * localVector, double * globalVector)
{
  globalVector[0] = positionX + R[0] * localVector[0] + R[1] * localVector[1] + R[2] * localVector[2];
  globalVector[1] = positionY + R[3] * localVector[0] + R[4] * localVector[1] + R[5] * localVector[2];
  globalVector[2] = positionZ + R[6] * localVector[0] + R[7] * localVector[1] + R[8] * localVector[2];
}

void RigidBody::SetLinearDamping(double linearDampingCoef)
{
  this->linearDampingCoef = linearDampingCoef;
}

void RigidBody::SetRotationalDamping(double rotationalDampingCoef)
{
  this->rotationalDampingCoef = rotationalDampingCoef;
}

