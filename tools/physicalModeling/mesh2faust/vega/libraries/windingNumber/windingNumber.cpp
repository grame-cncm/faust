/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "windingNumber" library , Copyright (C) 2016 USC                      *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Yijing Li                                                *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Funding: National Science Foundation                                  *
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

#include "windingNumber.h"
#include "macros.h"

double WindingNumber::computeWindingNumber(ObjMesh * objMesh, const Vec3d & p) 
{
  assert(objMesh->isTriangularMesh());
  double w = 0;
  //  double maxO = -DBL_MAX;
  //  double minO = DBL_MAX;

  for(size_t i = 0; i < objMesh->getNumGroups(); i++) 
  {
    const ObjMesh::Group* group = objMesh->getGroupHandle(i);
    for(size_t j = 0; j < group->getNumFaces(); j++) 
    {
      const ObjMesh::Face* face = group->getFaceHandle(j);
      assert(face->getNumVertices() == 3);
      Vec3d vtx[3];

      for(int k = 0; k < 3; k++) 
      {
        const ObjMesh::Vertex* v = face->getVertexHandle(k);
        //unsigned int posInd = v->getPositionIndex();
        vtx[k] = objMesh->getPosition(*v);
      }

      Vec3d a = vtx[0] - p;
      Vec3d b = vtx[1] - p;
      Vec3d c = vtx[2] - p;
      double la = len(a), lb = len(b), lc = len(c);
      Mat3d mat(a,b,c);
      double omega = 2*atan2(det(mat), (la * lb * lc + dot(a,b) * lc + dot(b,c) * la + dot(c,a) * lb));
//      if(omega > maxO) maxO = omega;
//      if(omega < minO) minO = omega;
      w += omega;
    }
  }

  w /= 4 * M_PI;
  //PRINT(maxO / (4*M_PI));
  //PRINT(minO / (4*M_PI));
  return w;
}

