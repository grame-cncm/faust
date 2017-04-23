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

/*
  Computes the tangent stiffness matrix of a StVK elastic deformable object.
  The tangent stiffness matrix depends on the deformable configuration.
  As a special case, the routine can compute the stiffness matrix in the rest configuration.
  See also StVKInternalForces.h .
*/

#ifndef _STVKSTIFFNESSMATRIX_H_
#define _STVKSTIFFNESSMATRIX_H_

#include "sparseMatrix.h"
#include "StVKInternalForces.h"

class StVKStiffnessMatrix
{
public:

  // initializes the computation of the tangent stiffness matrix
  StVKStiffnessMatrix(StVKInternalForces *  stVKInternalForces);
  virtual ~StVKStiffnessMatrix();

  // generates a zero matrix with the same pattern of non-zero entries as the tangent stiffness matrix
  // note: sparsity pattern does not depend on the deformable configuration
  void GetStiffnessMatrixTopology(SparseMatrix ** stiffnessMatrixTopology); 

  // evaluates the tangent stiffness matrix in the given deformation configuration
  // "vertexDisplacements" is an array of vertex deformations, of length 3*n, where n is the total number of mesh vertices
  virtual void ComputeStiffnessMatrix(const double * vertexDisplacements, SparseMatrix * sparseMatrix);

  inline void ResetStiffnessMatrix(SparseMatrix * sparseMatrix) {sparseMatrix->ResetToZero();}

  inline VolumetricMesh * GetVolumetricMesh() { return volumetricMesh; }
  inline StVKElementABCD * GetPrecomputedIntegrals() { return precomputedIntegrals; }

  // === the routines below are meant for advanced usage ===

  // auxiliary functions, these will add the contributions into 'forces'
  void AddLinearTermsContribution(const double * vertexDisplacements, SparseMatrix * sparseMatrix, int elementLow=-1, int elementHigh=-1);
  void AddQuadraticTermsContribution(const double * vertexDisplacements,SparseMatrix * sparseMatrix, int elementLow=-1, int elementHigh=-1);
  void AddCubicTermsContribution(const double * vertexDisplacements, SparseMatrix * sparseMatrix, int elementLow=-1, int elementHigh=-1);

  void GetMatrixAccelerationIndices(int *** row__, int *** column__) { *row__ = row_; *column__ = column_;}

protected:

  int numElementVertices;

  // acceleration indices
  int ** row_;
  int ** column_;

  VolumetricMesh * volumetricMesh;
  StVKInternalForces * stVKInternalForces;
  StVKElementABCD * precomputedIntegrals;

  double * lambdaLame;
  double * muLame;

  // adds a 3x3 block matrix corresponding to a derivative of force on vertex c wrt to vertex a
  // c is 0..7
  // a is 0..7
  inline void AddMatrix3x3Block(int c, int a, int element, Mat3d & matrix, SparseMatrix * sparseMatrix);
};

inline void StVKStiffnessMatrix::AddMatrix3x3Block(int c, int a, int element, Mat3d & matrix, SparseMatrix * sparseMatrix)
{
  int * row = row_[element];
  int * column = column_[element];

  for(int k=0; k<3; k++)
    for(int l=0; l<3; l++)
      sparseMatrix->AddEntry(3*row[c]+k, 3*column[numElementVertices*c+a]+l, matrix[k][l]);
}

#endif

