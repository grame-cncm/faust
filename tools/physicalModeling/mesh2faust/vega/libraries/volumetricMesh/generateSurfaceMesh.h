/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Yijing Li                                *
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
  Creates the surface mesh of the given volumetric mesh.
  Note: interior volumetric mesh vertices are kept in the surface mesh (as isolated vertices).
        So, the vertex set of the volumetric mesh is identical to the surface mesh vertex set,
        with the same order.
*/

#ifndef _GENERATESURFACEMESH_H_
#define _GENERATESURFACEMESH_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "volumetricMesh.h"
#include "objMesh.h"


class GenerateSurfaceMesh
{
public:
  // The output surface mesh is usually a triangle mesh, but can also be a quad mesh for cubic meshes.
  // The last argument specifies whether output mesh should be quads or triangles (in the case of cubic volumetric meshes).
  // All vertices of the volumetric mesh are included in the output surface mesh, even if they don't touch any surface triangle (e.g., vertices in the interior of the volumetric mesh).
  static ObjMesh * ComputeMesh(const VolumetricMesh * volumetricMesh, bool triangulateOutputMesh=false); 

  static ObjMesh * ComputeMesh(const VolumetricMesh * volumetricMesh, const ObjMesh * superMesh, bool triangulateOutputMesh=false); // computes the surface of the mesh, but only the part which is also the outer surface of the given super mesh (advanced routine)
};

#endif

