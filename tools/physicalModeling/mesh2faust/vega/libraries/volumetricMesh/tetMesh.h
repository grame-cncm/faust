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
  This class is a container for a tetrahedral volumetric 3D mesh. See 
  also volumetricMesh.h. The tetrahedra can take arbitrary shapes (not 
  limited to only a few shapes).
*/

#ifndef _TETMESH_H_
#define _TETMESH_H_

#include "volumetricMesh.h"

// see also volumetricMesh.h for a description of the routines

class TetMesh : public VolumetricMesh
{
public:
  // loads the mesh from a file 
  // ASCII: .veg text input format, see documentation and the provided examples
  // BINARY: .vegb binary input format
  TetMesh(const char * filename, fileFormatType fileFormat = ASCII, int verbose=1);

  // load from a stream
  // if memoryLoad is 0, binaryStream is FILE* (load from a file), otherwise, it is char* (load from a memory buffer)
  TetMesh(void * binaryStream, int memoryLoad = 0);

  // constructs a tet mesh from the given vertices and elements, 
  // with a single region and material ("E, nu" material)
  // "vertices" is double-precision array of length 3 x numVertices .
  // "elements" is an integer array of length 4 x numElements
  TetMesh(int numVertices, double * vertices,
         int numElements, int * elements,
         double E=1E6, double nu=0.45, double density=1000);

  // constructs a tet mesh from the given vertices and elements, 
  // with an arbitrary number of sets, regions and materials
  // "vertices" is double-precision array of length 3 x numVertices 
  // "elements" is an integer array of length 4 x numElements
  // "materials", "sets" and "regions" will be copied internally (deep copy), so you
  // can release them after calling this constructor
  TetMesh(int numVertices, double * vertices,
         int numElements, int * elements,
         int numMaterials, Material ** materials,
         int numSets, Set ** sets,
         int numRegions, Region ** regions);

  // loads a file of a "special" (not .veg) type
  // currently one such special format is supported:
  // specialFileType=0: 
  //   the ".ele" and ".node" format, used by TetGen, 
  //   "filename" is the basename, e.g., passing "mesh" will load the mesh from "mesh.ele" and "mesh.node" 
  // default material parameters will be used
  TetMesh(const char * filename, int specialFileType, int verbose); 

  // creates a mesh consisting of the specified element subset of the given TetMesh
  TetMesh(const TetMesh & mesh, int numElements, int * elements, std::map<int,int> * vertexMap = NULL);

  TetMesh(const TetMesh & tetMesh);
  virtual VolumetricMesh * clone();
  virtual ~TetMesh();

  virtual int saveToAscii(const char * filename) const;
  // saves the mesh to binary format
  // returns: 0 = success, non-zero = error
  // output: if bytesWritten is non-NULL, it will contain the number of bytes written 
  virtual int saveToBinary(const char * filename, unsigned int * bytesWritten = NULL) const;
  virtual int saveToBinary(FILE * binaryOutputStream, unsigned int * bytesWritten = NULL, bool countBytesOnly = false) const;

 // === misc queries ===

  static VolumetricMesh::elementType elementType() { return elementType_; }
  virtual VolumetricMesh::elementType getElementType() const { return elementType(); }

  static double getTetVolume(const Vec3d & a, const Vec3d & b, const Vec3d & c, const Vec3d & d);
  static double getTetDeterminant(const Vec3d & a, const Vec3d & b, const Vec3d & c, const Vec3d & d);

  virtual double getElementVolume(int el) const;
  virtual void getElementInertiaTensor(int el, Mat3d & inertiaTensor) const;
  virtual void computeElementMassMatrix(int element, double * massMatrix) const;

  virtual bool containsVertex(int element, Vec3d pos) const; // true if given element contain given position, false otherwise

  // edge queries
  virtual int getNumElementEdges() const;
  virtual void getElementEdges(int el, int * edgeBuffer) const;

 // === interpolation ===

  static void computeBarycentricWeights(const Vec3d vertexPos[4], const Vec3d & pos, double * weights);
  virtual void computeBarycentricWeights(int el, const Vec3d & pos, double * weights) const;
  void computeGradient(int element, const double * U, int numFields, double * grad) const; // for tet meshes, gradient is constant inside each tet, hence no need to specify position
  virtual void interpolateGradient(int element, const double * U, int numFields, Vec3d pos, double * grad) const; // conforms to the virtual function in the base class, "pos" does not affect the computation

  // === misc ===

  void orient(); // orients the tets (re-orders vertices within each tet), so that each tet has positive orientation: ((v1 - v0) x (v2 - v0)) dot (v3 - v0) >= 0

protected:
  static const VolumetricMesh::elementType elementType_;
  TetMesh(int numElementVertices): VolumetricMesh(numElementVertices) {}

  friend class VolumetricMeshExtensions;
};

#endif

