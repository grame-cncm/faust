/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC *
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

#include "generateTetMeshFromCubicMesh.h"

TetMesh * GenerateTetMeshFromCubicMesh::Generate(CubicMesh * cubicMesh, double E, double nu, double density)
{
  int numVertices;
  double * vertices;
  int numCubicElements;
  int numElementVertices;
  int * cubicElements;

  cubicMesh->exportMeshGeometry(&numVertices, &vertices, &numCubicElements, &numElementVertices, &cubicElements);

  int numTetElements = 6 * numCubicElements;
  int * tetElements = (int*) malloc (sizeof(int) * 4 * numTetElements);

  int tetSubdivision[6][4] = {
    { 0, 1, 3, 4 },
    { 1, 3, 4, 5 },
    { 3, 4, 5, 7 },
    { 1, 2, 3, 5 },
    { 2, 5, 6, 7 },
    { 2, 3, 5, 7 }
   };

  for(int i=0; i<numCubicElements; i++)
  {
    int * cubicElement = &cubicElements[8*i];
    for(int tet=0; tet<6; tet++)
    {
      int tetIndex = 6*i+tet;
      for(int vtx=0; vtx<4; vtx++)
      {
        int localVertexIndex = tetSubdivision[tet][vtx];
        tetElements[4*tetIndex+vtx] = cubicElement[localVertexIndex];
      }
    }
  }

  TetMesh * tetMesh = new TetMesh(numVertices, vertices, numTetElements, tetElements, E, nu, density);

  free(tetElements);
  free(cubicElements);
  free(vertices);

  return tetMesh;
}

