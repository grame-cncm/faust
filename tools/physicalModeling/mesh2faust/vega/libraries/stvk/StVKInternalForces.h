/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "StVK" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC           *
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

#ifndef _STVKINTERNALFORCES_H_
#define _STVKINTERNALFORCES_H_

/*

Given a 3D volumetric mesh, and a vector of displacements of its vertices,
the classes StVKInternalForces, StVKStiffnessMatrix and StVKHessianTensor
compute internal elastic strain energy, internal forces, tangent stiffness
matrices, and the second derivative of internal forces (the Hessian), under
an isotropic geometrically nonlinear Finite Element Method (FEM) elastic model.
Large deformations are therefore supported ("geometric nonlinearities"). 
The strain-stress relationship is linear (the St. Venant-Kirchhoff model).
Material parameters (Young's modulus, Poisson ratio, mass density) can be set 
for each individual mesh element, and can therefore vary across the mesh.

Supported volumetric mesh types:
1. Tetrahedral meshes 
2. Meshes consisting of cubes, obtained by voxelizing a triangle geometry 
   (the cubes are a subset of a regular 3D grid; all cubes are axis-aligned and 
    of the same size)

Multi-threaded versions of the classes are also available ("MT" suffix). 
They use POSIX threads ("pthreads") - which are available under Unix, Mac OS X, 
and also Windows. The code is thread-safe. The computation of the following 
quantities is multi-threaded: internal forces, tangent stiffness matrix, 
strain energy. With large meshes, these routines achieve almost linear scaling 
(tested on a 8-core CPU).

We were able to run the code under Unix, Max OS X, and Windows.

This code was designed for interactive simulation, but can also be used offline. 
The routines were optimized for speed. Our multi-threaded implementation is 
interactive up to about several thousand tetrahedra.

The code also supports reduced FEM deformable models ([Barbic and James 2005], 
SIGGRAPH 2005). The corresponding classes use "Reduced" in their name. So, this 
code essentially gives two separate simulators: full simulations (no reduction), 
and reduced simulations.

With tet meshes, there is a choice between a low-memory implementation and a 
high-memory implementation. With a few thousand tetrahedra (depending on the 
size and availability of your memory), you can gain a small speedup (e.g. 1.5x) 
by using a high-memory version (see StVKTetHighMemoryABCD.h).

Note: all matrices are stored in the column-major order (same format as in LAPACK).

*/

#include "volumetricMesh.h"
#include "StVKElementABCD.h"

class StVKInternalForces
{
public:

  // before creating this class, you must first create the volumetric mesh, and the precomputed integrals
  // you can use the StVKElementABCDLoader.h header file to create the "precomputedABCDIntegrals"
  StVKInternalForces(VolumetricMesh * volumetricMesh, StVKElementABCD * precomputedABCDIntegrals, bool addGravity=false, double g=9.81);
  virtual ~StVKInternalForces();

  // both vertex displacements and internal forces refer to the vertices of the simulation mesh
  // they must be (pre-allocated) vectors of length 3 * numVertices
  // the internal forces are returned with the sign corresponding to f_int(x) on the left side of the equation M * x'' + f_int(x) = f_ext
  // i.e., the computed internal forces are negatives of the actual physical internal forces acting on the material
  virtual void ComputeForces(const double * vertexDisplacements, double * internalForces);

  // enables or disables the gravity (note: you can also set this in the constructor; use this routine to turn the gravity on/off during the simulation)
  void SetGravity(bool addGravity) { this->addGravity = addGravity; InitGravity(); } // if addGravity is enabled, ComputeForces will subtract the gravity force from the internal forces (note: subtraction, not addition, is used because the internal forces are returned with the sign as described in the f_int(x) comment above)

  virtual double ComputeEnergy(const double * vertexDisplacements); // get the nonlinear elastic strain energy

  inline VolumetricMesh * GetVolumetricMesh() { return volumetricMesh; }
  inline StVKElementABCD * GetPrecomputedIntegrals() { return precomputedIntegrals; }

  // === advanced routines below === 
  double ComputeEnergyContribution(const double * vertexDisplacements, int elementLow, int elementHigh, double * buffer = NULL); // compute the contribution to strain energy due to the specified elements; needs a buffer for internal calculations; you can pass NULL (and then an internal buffer will be used), or pass your own buffer (useful with multi-threading)
  void AddLinearTermsContribution(const double * vertexDisplacements, double * forces, int elementLow=-1, int elementHigh=-1);
  void AddQuadraticTermsContribution(const double * vertexDisplacements, double * forces, int elementLow=-1, int elementHigh=-1);
  void AddCubicTermsContribution(const double * vertexDisplacements, double * forces, int elementLow=-1, int elementHigh=-1);
  
protected:
  VolumetricMesh * volumetricMesh;
  StVKElementABCD * precomputedIntegrals;

  double * gravityForce;
  bool addGravity;
  double g;
  void InitGravity(); // aux function

  double * buffer;
  int numElementVertices;

  void ResetVector(double * vec); // aux function

  double * lambdaLame;
  double * muLame;
};

#endif

