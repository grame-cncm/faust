/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "objMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Christopher Twigg, Daniel Schroeder      *
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
  Loads/saves an obj file to binary format.
  Jernej Barbic, 2009
*/

#ifndef _OBJMESHBINARYLOADER_H_
#define _OBJMESHBINARYLOADER_H_

#include "objMesh.h"
#include <string>

class ObjMeshBinaryLoader
{
public:
  static int readFromBinaryFile(ObjMesh ** objMesh, const std::string & filename);
  static int writeToBinaryFile(ObjMesh * objMesh, const std::string & filename);

protected:
  static int readFromBinary(ObjMesh::Vertex ** vertex, std::ifstream * fin);
  static int readFromBinary(ObjMesh::Face ** face, std::ifstream * fin);
  static int readFromBinary(ObjMesh::Group ** group, std::ifstream * fin);
  static int readFromBinary(ObjMesh::Material ** material, std::ifstream * fin);
  static int writeToBinary(ObjMesh::Vertex * vertex, std::ofstream * fout);
  static int writeToBinary(ObjMesh::Face * face, std::ofstream * fout);
  static int writeToBinary(ObjMesh::Group * group, std::ofstream * fout);
  static int writeToBinary(ObjMesh::Material * material, std::ofstream * fout);

  static int readStringFromBinary(std::string & name, std::ifstream * fin);
  static int readVec3dFromBinary(Vec3d & vec, std::ifstream * fin);
  static int writeStringToBinary(const std::string name, std::ofstream * fout);
  static int writeVec3dToBinary(Vec3d & vec, std::ofstream * fout);
};

#endif

