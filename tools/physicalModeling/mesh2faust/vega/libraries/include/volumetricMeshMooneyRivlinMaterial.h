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

#ifndef _VOLUMETRICMESHMOONEYRIVLINMATERIAL_H_
#define _VOLUMETRICMESHMOONEYRIVLINMATERIAL_H_

#include "volumetricMesh.h"

// Mooney-Rivlin material

/*
   The implemented Mooney-Rivlin material model is described in:
   BONET J., WOOD R. D.: Nonlinear Continuum Mechanics
   for Finite Element Analysis, 2nd Ed. Cambridge University
   Press, 2008, page 170
*/

// note that this class only stores material properties
// the actual implementation of the Mooney-Rivlin material is in the isotropicHyperelasticFEM class

class VolumetricMesh::MooneyRivlinMaterial : public VolumetricMesh::Material
{
public:
  MooneyRivlinMaterial(std::string name, double density, double mu01, double mu10, double v1);
  MooneyRivlinMaterial(const MooneyRivlinMaterial & mooneyRivlinMaterial);
  virtual ~MooneyRivlinMaterial() {}
  virtual VolumetricMesh::Material * clone() const;
  virtual VolumetricMesh::Material::materialType getType();

  inline double getmu01() const; 
  inline double getmu10() const; 
  inline double getv1() const; 
  inline void setmu01(double mu01); 
  inline void setmu10(double mu10); 
  inline void setv1(double v1); 

protected:
  double mu01_, mu10_, v1_;
};

inline VolumetricMesh::MooneyRivlinMaterial::MooneyRivlinMaterial(std::string name, double density, double mu01, double mu10, double v1): VolumetricMesh::Material(name, density), mu01_(mu01), mu10_(mu10), v1_(v1) {}
inline VolumetricMesh::MooneyRivlinMaterial::MooneyRivlinMaterial(const MooneyRivlinMaterial & mooneyRivlinMaterial) : VolumetricMesh::Material(mooneyRivlinMaterial.getName(), mooneyRivlinMaterial.getDensity()),  mu01_(mooneyRivlinMaterial.getmu01()), mu10_(mooneyRivlinMaterial.getmu10()), v1_(mooneyRivlinMaterial.getv1()) {}
inline double VolumetricMesh::MooneyRivlinMaterial::getmu01() const { return mu01_; } 
inline double VolumetricMesh::MooneyRivlinMaterial::getmu10() const { return mu10_; } 
inline double VolumetricMesh::MooneyRivlinMaterial::getv1() const { return v1_; } 
inline void VolumetricMesh::MooneyRivlinMaterial::setmu01(double mu01) { mu01_ = mu01; }
inline void VolumetricMesh::MooneyRivlinMaterial::setmu10(double mu10) { mu10_ = mu10; }
inline void VolumetricMesh::MooneyRivlinMaterial::setv1(double v1) { v1_ = v1; }

// obtain pointer to MooneyRivlinMaterial (necessary inside classes that implement the Mooney-Rivlin material)
VolumetricMesh::MooneyRivlinMaterial * downcastMooneyRivlinMaterial(VolumetricMesh::Material * material); // performs a check via getType and returns NULL if material is not Mooney Rivlin

#endif

