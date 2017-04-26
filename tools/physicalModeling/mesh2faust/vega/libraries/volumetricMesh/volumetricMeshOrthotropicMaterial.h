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

/*
  Stores an orthotropic material.
*/

#ifndef _VOLUMETRICMESHORTHOTROPICMATERIAL_H_
#define _VOLUMETRICMESHORTHOTROPICMATERIAL_H_

#include "volumetricMesh.h"

// stores an orthotropic material
class VolumetricMesh::OrthotropicMaterial : public VolumetricMesh::Material
{
public:
  OrthotropicMaterial(std::string name, double density, double E1, double E2, double E3, double nu12, double nu23, double nu31, double G12, double G23, double G31, double * R);
  OrthotropicMaterial(const OrthotropicMaterial & orthotropicMaterial);
  virtual ~OrthotropicMaterial() {}
  virtual VolumetricMesh::Material * clone() const;
  virtual VolumetricMesh::Material::materialType getType();

  // Es, Nus and Gs are all given in the local coordinate system specified by R
  inline double getE1() const; // Young's modulus in the x-direction  
  inline double getE2() const; // Young's modulus in the y-direction  
  inline double getE3() const; // Young's modulus in the z-direction  
  inline double getNu12() const; // Poisson's ratio when pulling in x-direction, contraction in y
  inline double getNu23() const; // Poisson's ratio when pulling in y-direction, contraction in z
  inline double getNu31() const; // Poisson's ratio when pulling in z-direction, contraction in x
  inline double getG12() const; // shear modulus in xy
  inline double getG23() const; // shear modulus in yz
  inline double getG31() const; // shear modulus in zx
  void getR(double * R) const; // rotation (3x3 matrix) of the local coordinate system, in row-major order

  inline void setE1(double E1); 
  inline void setE2(double E2); 
  inline void setE3(double E3); 
  inline void setNu12(double nu12); 
  inline void setNu23(double nu23); 
  inline void setNu31(double nu31); 
  inline void setG12(double G12); 
  inline void setG23(double G23); 
  inline void setG31(double G31); 
  void setR(double * R); 

protected:
  double E1_, E2_, E3_, nu12_, nu23_, nu31_, G12_, G23_, G31_; 
  double R_[9];
};

inline double VolumetricMesh::OrthotropicMaterial::getE1() const { return E1_; } 
inline double VolumetricMesh::OrthotropicMaterial::getE2() const { return E2_; } 
inline double VolumetricMesh::OrthotropicMaterial::getE3() const { return E3_; } 
inline double VolumetricMesh::OrthotropicMaterial::getNu12() const { return nu12_; } 
inline double VolumetricMesh::OrthotropicMaterial::getNu23() const { return nu23_; } 
inline double VolumetricMesh::OrthotropicMaterial::getNu31() const { return nu31_; } 
inline double VolumetricMesh::OrthotropicMaterial::getG12() const { return G12_; } 
inline double VolumetricMesh::OrthotropicMaterial::getG23() const { return G23_; } 
inline double VolumetricMesh::OrthotropicMaterial::getG31() const { return G31_; } 

inline void VolumetricMesh::OrthotropicMaterial::setE1(double E1) { E1_ = E1; }
inline void VolumetricMesh::OrthotropicMaterial::setE2(double E2) { E2_ = E2; }
inline void VolumetricMesh::OrthotropicMaterial::setE3(double E3) { E3_ = E3; }
inline void VolumetricMesh::OrthotropicMaterial::setNu12(double nu12) { nu12_ = nu12; }
inline void VolumetricMesh::OrthotropicMaterial::setNu23(double nu23) { nu23_ = nu23; }
inline void VolumetricMesh::OrthotropicMaterial::setNu31(double nu31) { nu31_ = nu31; }
inline void VolumetricMesh::OrthotropicMaterial::setG12(double G12) { G12_ = G12; }
inline void VolumetricMesh::OrthotropicMaterial::setG23(double G23) { G23_ = G23; }
inline void VolumetricMesh::OrthotropicMaterial::setG31(double G31) { G31_ = G31; }

// obtain pointer to OrthotropicMaterial (necessary inside classes that assume ENu material)
VolumetricMesh::OrthotropicMaterial * downcastOrthotropicMaterial(VolumetricMesh::Material * material); // performs a check via getType and returns NULL if material is not Orthotropic

#endif

