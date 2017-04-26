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

#if defined(_WIN32) || defined(WIN32)
  #pragma warning(disable : 4996)
  #pragma warning(disable : 4267)
  #pragma warning(disable : 4244)
#endif

#include <vector>
#include <queue>
#include <string>
#include <string.h>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
#include "objMeshBinaryLoader.h"

//#define VERBOSE

int ObjMeshBinaryLoader::readStringFromBinary(std::string & name, std::ifstream * fin)
{
  #ifdef VERBOSE
    printf("readString\n");
  #endif

  int strl;
  fin->read((char*)&strl, sizeof(int));
  char * nameBuffer = (char*) malloc (strl);
  fin->read(nameBuffer,strl);
  name = string(nameBuffer);

  return 0;
}

int ObjMeshBinaryLoader::readVec3dFromBinary(Vec3d & vec, std::ifstream * fin)
{
  #ifdef VERBOSE
    printf("readVec3d\n");
  #endif

  double x,y,z;
  fin->read((char*)&x, sizeof(double));
  fin->read((char*)&y, sizeof(double));
  fin->read((char*)&z, sizeof(double));
  vec = Vec3d(x,y,z);

  return 0;
}

int ObjMeshBinaryLoader::writeStringToBinary(const std::string name, std::ofstream * fout)
{
  char * nameBuffer = (char*)name.c_str();
  int strl = strlen(nameBuffer) + 1;
  fout->write((char*)&strl, sizeof(int));
  fout->write(nameBuffer,strl);

  return 0;
}

int ObjMeshBinaryLoader::writeVec3dToBinary(Vec3d & vec, std::ofstream * fout)
{
  double x = vec[0];
  double y = vec[1];
  double z = vec[2];

  fout->write((char*)&x, sizeof(double));
  fout->write((char*)&y, sizeof(double));
  fout->write((char*)&z, sizeof(double));

  return 0;
}

int ObjMeshBinaryLoader::readFromBinaryFile(ObjMesh ** objMesh, const std::string & filename)
{
  *objMesh = new ObjMesh();

  ifstream fin(filename.c_str(),ios::binary);

  unsigned int numMaterials;
  fin.read((char*)&numMaterials, sizeof(unsigned int));
  for(unsigned int i=0; i<numMaterials; i++)
  {
    ObjMesh::Material * material;
    readFromBinary(&material, &fin);
    (*objMesh)->addMaterial(*material);
  }

  unsigned int numGroups;
  fin.read((char*)&numGroups, sizeof(unsigned int));
  for(unsigned int i=0; i<numGroups; i++)
  {
    ObjMesh::Group * group;
    readFromBinary(&group, &fin);
    (*objMesh)->addGroup(*group);
  }

  unsigned int numVertexPositions;
  fin.read((char*)&numVertexPositions, sizeof(unsigned int));
  for(unsigned int i=0; i<numVertexPositions; i++)
  {
    Vec3d pos;
    readVec3dFromBinary(pos, &fin);
    (*objMesh)->addVertexPosition(pos);
  }

  unsigned int numTextureCoords;
  fin.read((char*)&numTextureCoords, sizeof(unsigned int));
  for(unsigned int i=0; i<numTextureCoords; i++)
  {
    Vec3d uv;
    readVec3dFromBinary(uv, &fin);
    (*objMesh)->addTextureCoordinate(uv);
  }

  unsigned int numNormals;
  fin.read((char*)&numNormals, sizeof(unsigned int));
  for(unsigned int i=0; i<numNormals; i++)
  {
    Vec3d normal;
    readVec3dFromBinary(normal, &fin);
    (*objMesh)->addVertexNormal(normal);
  }

  fin.close();

  return 0;
}

int ObjMeshBinaryLoader::writeToBinaryFile(ObjMesh * objMesh, const std::string & filename)
{
  ofstream fout(filename.c_str(),ios::binary);

  unsigned int numMaterials = objMesh->getNumMaterials();
  fout.write((char*)&numMaterials, sizeof(unsigned int));
  for(unsigned int i=0; i<numMaterials; i++)
    writeToBinary((ObjMesh::Material*)objMesh->getMaterialHandle(i), &fout);

  unsigned int numGroups = objMesh->getNumGroups();
  fout.write((char*)&numGroups, sizeof(unsigned int));
  for(unsigned int i=0; i<numGroups; i++)
    writeToBinary((ObjMesh::Group*)objMesh->getGroupHandle(i), &fout);

  unsigned int numVertexPositions = objMesh->getNumVertices();
  fout.write((char*)&numVertexPositions, sizeof(unsigned int));
  for(unsigned int i=0; i<numVertexPositions; i++)
  {  
    Vec3d pos = objMesh->getPosition(i);
    writeVec3dToBinary(pos, &fout);
  }

  unsigned int numTextureCoords = objMesh->getNumTextureCoordinates();
  fout.write((char*)&numTextureCoords, sizeof(unsigned int));
  for(unsigned int i=0; i<numTextureCoords; i++)
  {
    Vec3d texCoord = objMesh->getTextureCoordinate(i);
    writeVec3dToBinary(texCoord, &fout);
  }

  unsigned int numNormals = objMesh->getNumNormals();
  fout.write((char*)&numNormals, sizeof(unsigned int));
  for(unsigned int i=0; i<numNormals; i++)
  {
    Vec3d normal = objMesh->getNormal(i);
    writeVec3dToBinary(normal, &fout);
  }

  fout.close();

  return 0;
}

int ObjMeshBinaryLoader::readFromBinary(ObjMesh::Vertex ** vertex, std::ifstream * fin)
{
  #ifdef VERBOSE
    printf("readVertex\n");
  #endif

  unsigned int position;
  fin->read((char*)&position, sizeof(unsigned int));

  bool textureBool;
  int textureInt;
  fin->read((char*)&textureBool, sizeof(bool));
  fin->read((char*)&textureInt, sizeof(int));
  std::pair<bool, unsigned int> texture(textureBool,textureInt);

  bool normalBool;
  int normalInt;
  fin->read((char*)&normalBool, sizeof(bool));
  fin->read((char*)&normalInt, sizeof(int));
  std::pair<bool, unsigned int> normal(normalBool, normalInt);

  *vertex = new ObjMesh::Vertex(position, texture, normal);

  return 0;
}

int ObjMeshBinaryLoader::writeToBinary(ObjMesh::Vertex * vertex, std::ofstream * fout)
{
  unsigned int position = vertex->getPositionIndex();
  fout->write((char*)&position, sizeof(unsigned int));

  bool textureBool = (vertex->getTextureIndexPair()).first;
  int textureInt = (vertex->getTextureIndexPair()).second;
  fout->write((char*)&textureBool, sizeof(bool));
  fout->write((char*)&textureInt, sizeof(int));

  bool normalBool = (vertex->getNormalIndexPair()).first;
  int normalInt = (vertex->getNormalIndexPair()).second;
  fout->write((char*)&normalBool, sizeof(bool));
  fout->write((char*)&normalInt, sizeof(int));

  return 0;
}

int ObjMeshBinaryLoader::readFromBinary(ObjMesh::Face ** face, std::ifstream * fin)
{
  #ifdef VERBOSE
    printf("readFace\n");
  #endif

  unsigned int numVertices;
  fin->read((char*)&numVertices, sizeof(unsigned int));

  *face = new ObjMesh::Face();

  for(unsigned int i=0; i<numVertices; i++)
  {
    ObjMesh::Vertex * vertex;
    readFromBinary(&vertex, fin);  
    (*face)->addVertex(*vertex);
  }

  return 0;
}

int ObjMeshBinaryLoader::writeToBinary(ObjMesh::Face * face, std::ofstream * fout)
{
  unsigned int numVertices = face->getNumVertices();
  fout->write((char*)&numVertices, sizeof(unsigned int));

  for(unsigned int i=0; i<numVertices; i++)
    writeToBinary((ObjMesh::Face*)face->getVertexHandle(i), fout);

  return 0;
}

int ObjMeshBinaryLoader::readFromBinary(ObjMesh::Group ** group, std::ifstream * fin)
{
  #ifdef VERBOSE
    printf("readGroup\n");
  #endif

  string name;
  readStringFromBinary(name, fin);

  unsigned int materialIndex;
  fin->read((char*)&materialIndex, sizeof(unsigned int));

  *group = new ObjMesh::Group(name, materialIndex);

  unsigned int numFaces;
  fin->read((char*)&numFaces, sizeof(unsigned int));

  for(unsigned int i=0; i<numFaces; i++)
  {
    ObjMesh::Face * face;
    readFromBinary(&face, fin);  
    (*group)->addFace(*face);
  }

  return 0;
}


int ObjMeshBinaryLoader::writeToBinary(ObjMesh::Group * group, std::ofstream * fout)
{
  writeStringToBinary(group->getName(), fout);

  unsigned int materialIndex = group->getMaterialIndex();
  fout->write((char*)&materialIndex, sizeof(unsigned int));

  unsigned int numFaces = group->getNumFaces();
  fout->write((char*)&numFaces, sizeof(unsigned int));

  for(unsigned int i=0; i<numFaces; i++)
    writeToBinary((ObjMesh::Face*)group->getFaceHandle(i), fout);

  return 0;
}

int ObjMeshBinaryLoader::readFromBinary(ObjMesh::Material ** material, std::ifstream * fin)
{
  #ifdef VERBOSE
    printf("readMaterial\n");
  #endif

  string name;
  readStringFromBinary(name, fin);
  
  #ifdef VERBOSE
    cout << name << endl;
  #endif

  double shininess;
  fin->read((char*)&shininess, sizeof(double));

  Vec3d Ka, Kd, Ks;
  readVec3dFromBinary(Ka, fin);
  readVec3dFromBinary(Kd, fin);
  readVec3dFromBinary(Ks, fin);

  *material = new ObjMesh::Material(name, Ka, Kd, Ks, shininess);

  #ifdef VERBOSE
    printf("done readMaterial\n");
  #endif

  return 0;
}

int ObjMeshBinaryLoader::writeToBinary(ObjMesh::Material * material, std::ofstream * fout)
{
  writeStringToBinary(material->getName(), fout);

  double shininess = material->getShininess();
  fout->write((char*)&shininess, sizeof(double));

  Vec3d Ka = material->getKa();
  writeVec3dToBinary(Ka, fout);
  Vec3d Kd = material->getKd();
  writeVec3dToBinary(Kd, fout);
  Vec3d Ks = material->getKs();
  writeVec3dToBinary(Ks, fout);

  return 0;
}

