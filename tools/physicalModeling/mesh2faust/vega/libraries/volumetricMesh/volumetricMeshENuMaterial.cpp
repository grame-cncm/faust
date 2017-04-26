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

#include "volumetricMeshENuMaterial.h"

VolumetricMesh::Material::materialType VolumetricMesh::ENuMaterial::getType() 
{ 
  return VolumetricMesh::Material::ENU; 
}

VolumetricMesh::Material * VolumetricMesh::ENuMaterial::clone() const
{ 
  return new VolumetricMesh::ENuMaterial(*this); 
}

// performs a check via getType and returns NULL if material is not ENU
VolumetricMesh::ENuMaterial * downcastENuMaterial(VolumetricMesh::Material * material)
{
  if (material->getType() != VolumetricMesh::Material::ENU)
    return NULL;

  return (VolumetricMesh::ENuMaterial*) material;
}

