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

#include "StVKElementABCDLoader.h"
#include "StVKCubeABCD.h"
#include "StVKTetABCD.h"
#include "StVKTetHighMemoryABCD.h"
#include "cubicMesh.h"
#include "tetMesh.h"

StVKElementABCD * StVKElementABCDLoader::load(VolumetricMesh * volumetricMesh, unsigned int loadingFlag)
{
  if (volumetricMesh == NULL)
  {
    printf("Error: volumetric mesh is NULL.\n");
    return NULL;
  }

  VolumetricMesh::elementType elementType_ = volumetricMesh->getElementType();
  StVKElementABCD * stVKElementABCD = NULL;
/*
  if (elementType_ == CubicMesh::elementType())
  {
    //printf("Loading cubic mesh integrals...\n");
    CubicMesh * cubeMesh = (CubicMesh*) volumetricMesh;
    stVKElementABCD = new StVKCubeABCD(cubeMesh->getCubeSize()); 
  }
*/
  if (elementType_ == TetMesh::elementType())
  {
    //printf("Loading tet mesh integrals...\n");
    TetMesh * tetMesh = (TetMesh*) volumetricMesh;
    if ((loadingFlag & 1) == 0)
    {
      //printf("Using the low-memory coefficient version.\n");
      stVKElementABCD = new StVKTetABCD(tetMesh); 
    }
    else
    {
      //printf("Using the high-memory coefficient version.\n");
      stVKElementABCD = new StVKTetHighMemoryABCD(tetMesh); 
    }
  }

  if (stVKElementABCD == NULL)
  {
    printf("Error in StVKElementABCDLoader: invalid mesh type.\n");
    exit(1);
  }

  return stVKElementABCD;
}

