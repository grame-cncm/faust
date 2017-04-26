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

#include "volumetricMeshOrthotropicMaterial.h"

VolumetricMesh::OrthotropicMaterial::OrthotropicMaterial(std::string name, double density, double E1, double E2, double E3, double nu12, double nu23, double nu31, double G12, double G23, double G31, double * R): VolumetricMesh::Material(name, density), E1_(E1), E2_(E2), E3_(E3), nu12_(nu12), nu23_(nu23), nu31_(nu31), G12_(G12), G23_(G23), G31_(G31)
{
  memcpy(R_, R, sizeof(double) * 9);
}

VolumetricMesh::OrthotropicMaterial::OrthotropicMaterial(const OrthotropicMaterial & orthotropicMaterial) : VolumetricMesh::Material(orthotropicMaterial.getName(), orthotropicMaterial.getDensity()),  
  E1_(orthotropicMaterial.getE1()), 
  E2_(orthotropicMaterial.getE2()), 
  E3_(orthotropicMaterial.getE3()), 
  nu12_(orthotropicMaterial.getNu12()), 
  nu23_(orthotropicMaterial.getNu23()), 
  nu31_(orthotropicMaterial.getNu31()), 
  G12_(orthotropicMaterial.getG12()),
  G23_(orthotropicMaterial.getG23()), 
  G31_(orthotropicMaterial.getG31()) 
{
  orthotropicMaterial.getR(R_); 
}

VolumetricMesh::Material::materialType VolumetricMesh::OrthotropicMaterial::getType() 
{ 
  return VolumetricMesh::Material::ORTHOTROPIC; 
}

VolumetricMesh::Material * VolumetricMesh::OrthotropicMaterial::clone() const
{ 
  return new VolumetricMesh::OrthotropicMaterial(*this); 
}

// performs a check via getType and returns NULL if material is not ORTHOTROPIC
VolumetricMesh::OrthotropicMaterial * downcastOrthotropicMaterial(VolumetricMesh::Material * material)
{
  if (material->getType() != VolumetricMesh::Material::ORTHOTROPIC)
    return NULL;

  return (VolumetricMesh::OrthotropicMaterial*) material;
}

void VolumetricMesh::OrthotropicMaterial::setR(double * R) 
{
  memcpy(R_, R, sizeof(double) * 9);
}

void VolumetricMesh::OrthotropicMaterial::getR(double * R) const
{
  memcpy(R, R_, sizeof(double) * 9);
}

