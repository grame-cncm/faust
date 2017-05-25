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

#ifndef _RIGIDBODY_GENERAL_TENSOR_H_
#define _RIGIDBODY_GENERAL_TENSOR_H_

/*
  Classes 'RigidBody' and 'RigidBody_GeneralTensor' 
  implement 6-DOF rigid dynamics of a single rigid body, as presented in:
   
  David Baraff:
  "An Introduction to Physically Based Modeling:
   Rigid Body Simulation I: Unconstrained Rigid Body Dynamics"
  (SIGGRAPH 97 Course Notes)
  http://www.cs.cmu.edu/~baraff/pbm/pbm.html

  See rigidBody.h for more detailed usage.
*/

#include "rigidBody.h"

class RigidBody_GeneralTensor : public RigidBody
{
public:

  // inertia tensor at rest should be the world-coordinate-system inertia tensor 
  //   when position=(0,0,0), and rotation=identity
  // constructor will set position and rotation to zero/identity
  RigidBody_GeneralTensor(double mass, double inertiaTensorAtRest[9]);

  // modify the body inertia tensor (i.e., tensor in the frame of reference of the object)
  // if updateAngularVelocity is set, angular velocity will be updated so that angular momentum stays constant
  void SetInertiaTensor(double inertiaTensorAtRest[9], int updateAngularVelocity=0);

  void GetInverseInertiaTensor(double * inverseInertiaTensor);
  void GetInverseInertiaTensorAtRest(double * inverseInertiaTensorAtRest);
protected:

  // computes the inertia tensor (given the current rotation matrix); dense inertia tensor at rest
  virtual void ComputeInertiaTensor(double inertiaTensor[9]);

  // computes the angular velocity from the angular momentum
  // via equation w = (R * I_body^{-1} * R^T) L
  // using the current rotation matrix 
  virtual void ComputeAngularVelocity();
  
  // inertia tensor are with respect to the world coordinate system
  double inertiaTensorAtRest[9]; // the inertia tensor when position=(0,0,0) and R=I
  double inverseInertiaTensorAtRest[9]; 

};

#endif

