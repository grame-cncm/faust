/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Hongyi Xu                                *
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

#include <string.h>
#include "matrixMacros.h"
#include "generateGradientMatrix.h"

void GenerateGradientMatrix::GenerateElementMatrixEntries(const TetMesh * tetMesh, int element, double * m)
{
  // grad is constant inside a tet
  Vec3d vtx[4];
  for(int i=0; i<4; i++)
    vtx[i] = tetMesh->getVertex(element,i);

  // form M =
  // [b - a]
  // [c - a]
  // [d - a]

  Mat3d M(vtx[1] - vtx[0], vtx[2] - vtx[0], vtx[3] - vtx[0]);
  Mat3d MInvT = trans(inv(M));
  //printf("MInvT=\n");
  //MInvT.print();

  for(int vtx=0; vtx<3; vtx++)
//    for(int dof=0; dof<3; dof++)
      for(int j=0; j<3; j++)
        m[3 * (vtx + 1) + j] = MInvT[vtx][j];
        //G[ELT(9, 3 * dof + j, vtx + 1)] = MInvT[vtx][j];

  //for(int dof=0; dof<3; dof++)
    for(int j=0; j<3; j++)
    {
      double entry = 0.0;
      for(int k=0; k<3; k++)
        entry -= MInvT[k][j];
      //G[ELT(9, 3 * dof + j, 0)] = entry;
      m[j] = entry;
    }
}

void GenerateGradientMatrix::GenerateElementMatrix(const TetMesh * tetMesh, int element, double * G)
{
  double m[12];
  GenerateElementMatrixEntries(tetMesh, element, m);

  // G is 9 x 12:
  //        [ m0       m1       m2       m3       ]
  //  G =   [    m0       m1       m2       m3    ]
  //        [       m0       m1       m2       m3 ]
  //
  // where mi are 3-vectors

  memset(G, 0, sizeof(double) * 9 * 12);

  for(int vtx=0; vtx<4; vtx++)
    for(int dof=0; dof<3; dof++)
      for(int j=0; j<3; j++)
        G[ELT(9, 3 * dof + j, 3 * vtx + dof)] = m[3 * vtx + j]; 
}

void GenerateGradientMatrix::Generate(const TetMesh * tetMesh, SparseMatrix ** G, SparseMatrix ** GTG, double * GTGElementWeights)
{
  // matrix is 9 #tets x 3 #vertices

  SparseMatrixOutline outline(9*tetMesh->getNumElements());
  SparseMatrixOutline outlineGTG(3*tetMesh->getNumVertices());

  for(int element=0; element<tetMesh->getNumElements(); element++)
  {
    if (element % 100 == 0)
    {
      printf("%d ", element);
      fflush(NULL);
    }

    double m[12];
    GenerateElementMatrixEntries(tetMesh, element, m);

    //double dFduPacked[36]; // 9 x 12, only diagonal 3x1 blocks are non-zero
    //GenerateElementMatrix(tetMesh, element, dFduPacked);

    //// write dFduPacked in place
    // write m in place
    for(int vtx=0; vtx<4; vtx++)
      for(int dof=0; dof<3; dof++)
        for(int j=0; j<3; j++)
        {
          int row = 9 * element + 3 * dof + j;
          int column = 3 * tetMesh->getVertexIndex(element, vtx) + dof;
          //double entry = dFduPacked[ELT(9, 3 * dof + j, vtx)];
          double entry = m[3 * vtx + j];
          outline.AddEntry(row, column, entry);
        }

    if (GTG != NULL)
    {
      double factor = 1.0;
      if (GTGElementWeights != NULL)
        factor = GTGElementWeights[element] * GTGElementWeights[element];

      for(int vtxA=0; vtxA<4; vtxA++)
        for(int vtxB=0; vtxB<4; vtxB++)
          for(int i=0; i<3; i++)
          {
            int row = 3 * tetMesh->getVertexIndex(element, vtxA) + i;
            int column = 3 * tetMesh->getVertexIndex(element, vtxB) + i;
            double entry = 0.0;
            for(int k=0; k<3; k++)
              //entry += dFduPacked[ELT(9, 3 * i + k, vtxA)] * dFduPacked[ELT(9, 3 * i + k, vtxB)];
              entry += m[3 * vtxA + k] * m[3 * vtxB + k];  
            entry *= factor;
            outlineGTG.AddEntry(row, column, entry);
          }
    }
  }

  *G = new SparseMatrix(&outline);

  if (GTG != NULL)
    *GTG = new SparseMatrix(&outlineGTG);
}

/*
    // old version
    for(int vtx=0; vtx<3; vtx++)
    {
      for(int dof=0; dof<3; dof++)
      {
        for(int j=0; j<3; j++)
        {
          int row = 9*element + 3*dof + j;
          int column = 3*tetMesh->getVertexIndex(element, vtx+1) + dof;
          outline.AddEntry(row, column, MInvT[vtx][j]);
        }
      }
    }

    for(int dof=0; dof<3; dof++)
    {
      for(int j=0; j<3; j++)
      {
        int row = 9*element + 3*dof + j;
        int column = 3*tetMesh->getVertexIndex(element, 0) + dof;
        double entry = 0.0;
        for(int k=0; k<3; k++)
          entry -= MInvT[k][j];
        outline.AddEntry(row, column, entry);
      }
    }
*/

void GenerateGradientMatrix::GenerateForScalarField(const TetMesh * tetMesh, SparseMatrix ** GTG, double * GTGElementWeights)
{
  SparseMatrixOutline outlineGTG(tetMesh->getNumVertices());

  for(int element=0; element<tetMesh->getNumElements(); element++)
  {
    if (element % 100 == 0)
    {
      printf("%d ", element);
      fflush(NULL);
    }

    double m[12];
    GenerateElementMatrixEntries(tetMesh, element, m);

    if (GTG != NULL)
    {
      double factor = 1.0;
      if (GTGElementWeights != NULL)
        factor = GTGElementWeights[element] * GTGElementWeights[element];

      for(int vtxA=0; vtxA<4; vtxA++)
        for(int vtxB=0; vtxB<4; vtxB++)
          {
            int row = tetMesh->getVertexIndex(element, vtxA);
            int column = tetMesh->getVertexIndex(element, vtxB);
            double entry = 0.0;
            for(int k=0; k<3; k++)
              //entry += dFduPacked[ELT(9, 3 * i + k, vtxA)] * dFduPacked[ELT(9, 3 * i + k, vtxB)];
              entry += m[3 * vtxA + k] * m[3 * vtxB + k];
            entry *= factor;
            outlineGTG.AddEntry(row, column, entry);
          }
    }
  }

  if (GTG != NULL)
    *GTG = new SparseMatrix(&outlineGTG);
}

