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

#ifndef _VOLUMETRICMESH_H_
#define _VOLUMETRICMESH_H_

/*
  This abstract class can store a generic volumetric 3D mesh. 
  It stores the mesh geometric information (elements and vertices), 
  and also the material parameters of each individual mesh element 
  (Young's modulus, Poisson ratio, mass density). This is done by 
  organizing elements with the same material parameters into a "region".
  The class supports several geometric queries and interpolation to 
  an embedded triangle mesh ("Free-Form Deformation").  It also 
  supports exporting the mesh to an .ele or .node format (the format 
  used by the Stellar and TetGen mesh generation packages).  Derived classes 
  are the TetMesh (general tetrahedral meshes), and CubicMesh 
  (axis-aligned cubic "voxel" meshes). See description in tetMesh.h and cubicMesh.h.

  All quantities are 0-indexed, except the input mesh files where the 
  elements and vertices are 1-indexed (same as in TetGen and Stellar).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <set>
#include <string>
#include <map>
#include "minivector.h"

class VolumetricMesh
{
public:

  // Note: This class is abstract and cannot be instantiated; use the constructors in the derived classes (TetMesh, CubicMesh) to initialize a mesh, or use the load routine in volumetricMeshLoader.h

  // copy constructor, destructor
  VolumetricMesh(const VolumetricMesh & volumetricMesh);
  virtual VolumetricMesh * clone() = 0;
  virtual ~VolumetricMesh();

  // nested classes to store sets, materials and regions (declared later)
  class Set; 
  class Material; 
  class Region;

  // === save/export ===

  // saves the mesh to a text file (.veg file format, see examples and documentation)
  virtual int saveToAscii(const char * filename) const = 0; 
  virtual int save(const char * filename) const; // for backward compatibility (just calls saveToAscii)

  // saves the mesh to binary format
  // returns: 0 = success, non-zero = error
  // output: if bytesWritten is non-NULL, it will contain the number of bytes written 
  virtual int saveToBinary(const char * filename, unsigned int * bytesWritten = NULL) const = 0;
  // if countBytesOnly = true, user can pass NULL to binaryOutputStream
  virtual int saveToBinary(FILE * binaryOutputStream, unsigned int * bytesWritten = NULL, bool countBytesOnly = false) const = 0;

  // exports the mesh geometry to an .ele and .node file (TetGen and Stellar format)
  // if includeRegions=1, an extra column is added to output, identifying the region of each element
  int exportToEle(const char * baseFilename, int includeRegions=0) const;
  // exports the mesh geometry to memory arrays (say, for external usage)
  // all parameters are output parameters
  // vertices and elements will be allocated inside the routine
  void exportMeshGeometry(int * numVertices, double ** vertices, int * numElements = NULL, int * numElementVertices = NULL, int ** elements = NULL) const;

  // === vertex and element access ===

  typedef enum { INVALID, TET, CUBIC } elementType;
  typedef enum { ASCII, BINARY, NUM_FILE_FORMATS } fileFormatType; // ASCII is the text .veg format, BINARY is the binary .vegb format
  // opens the file and returns the element type of the volumetric mesh in the file; returns INVALID if no type information found
  static elementType getElementType(const char * filename, fileFormatType fileFormat = ASCII); 
  virtual elementType getElementType() const = 0; // calls the derived class to identify itself
  // advanced usage: returns the element type of the volumetric mesh from a BINARY stream (does not modify fin)
  //static elementType getElementType(FILE * fin);
  static elementType getElementType(void * fin, int memoryLoad = 0);

  inline int getNumVertices() const { return numVertices; }
  inline Vec3d & getVertex(int i) { return vertices[i]; }
  inline const Vec3d & getVertex(int i) const { return vertices[i]; }
  inline Vec3d & getVertex(int element, int vertex) { return vertices[elements[element][vertex]]; }
  inline const Vec3d & getVertex(int element, int vertex) const { return vertices[elements[element][vertex]]; }
  inline int getVertexIndex(int element, int vertex) const { return elements[element][vertex]; }
  inline const int * getVertexIndices(int element) const { return elements[element]; }
  inline Vec3d * getVertices() { return vertices; } // advanced, internal datastructure
  inline const Vec3d * getVertices() const { return vertices; }
  inline int getNumElements() const { return numElements; }
  inline int getNumElementVertices() const { return numElementVertices; } 
  void renumberVertices(const std::vector<int> & permutation); // renumbers the vertices using the provided permutation
  inline void setVertex(int i, const Vec3d & pos) { vertices[i] = pos; } // set the position of a vertex

  // === materials access === 

  inline int getNumMaterials() const { return numMaterials; }
  inline const Material * getMaterial(int i) const { return materials[i]; }
  inline const Material * getElementMaterial(int el) const { return materials[elementMaterial[el]]; }
  static void getDefaultMaterial(double * E, double * nu, double * density);

  inline int getNumSets() const { return numSets; }
  inline const Set * getSet(int i) const { return sets[i]; }

  inline int getNumRegions() const { return numRegions; }
  inline const Region * getRegion(int i) const { return regions[i]; }

  // === materials editing ===
  inline Material * getMaterial(int i) { return materials[i]; }
  inline Material * getElementMaterial(int el) { return materials[elementMaterial[el]]; }
  void setMaterial(int i, const Material * material); // sets i-th material to "material"
  void setSingleMaterial(double E, double nu, double density); // erases all materials and creates a single material for the entire mesh
  void addMaterial(const Material * material, const Set & newSet, bool removeEmptySets, bool removeEmptyMaterials);

  // mass density of an element
  double getElementDensity(int el) const { return materials[elementMaterial[el]]->getDensity(); }
  // computes the mass matrix of a single element
  // note: to compute the mass matrix for the entire mesh, use generateMassMatrix.h
  virtual void computeElementMassMatrix(int element, double * massMatrix) const = 0; // massMatrix is numElementVertices_ x numElementVertices_

  // === geometric queries and transformations ===

  Vec3d getElementCenter(int el) const;

  // center of mass and inertia tensor
  double getVolume() const;
  virtual double getElementVolume(int el) const = 0;
  void getVertexVolumes(double * vertexVolumes) const; // compute the volume "belonging" to each vertex
  virtual void getElementInertiaTensor(int el, Mat3d & inertiaTensor) const = 0; // returns the inertia tensor of a single element, around its center of mass, with unit density
  double getMass() const; // compute the total mass of the mesh, using the mass density material information
  void getInertiaParameters(double & mass, Vec3d & centerOfMass, Mat3d & inertiaTensor) const ; // mass, center of mass and inertia tensor for the entire mesh

  // centroid is the geometric center of all vertices; radius is the tightest fitting sphere centered at the centroid
  void getMeshGeometricParameters(Vec3d & centroid, double * radius) const;

  // mesh 1-neighborhood queries
  void getVerticesInElements(std::vector<int> & elements, std::vector<int> & vertices) const;
  void getElementsTouchingVertices(std::vector<int> & vertices, std::vector<int> & elements) const;
  void getVertexNeighborhood(std::vector<int> & vertices, std::vector<int> & neighborhood) const;

  // proximity queries
  int getClosestElement(Vec3d pos) const; // finds the closest element to the given position (using linear scan); distance to a element is defined as distance to its center
  int getClosestVertex(Vec3d pos) const; // finds the closest vertex to the given position (using linear scan)
  int getContainingElement(Vec3d pos) const; // finds the element that containts the given position (using linear scan); if such element does not exist, -1 is returned
  virtual bool containsVertex(int element, Vec3d pos)  const = 0; // true if given element contain given position, false otherwise

  // computes the gravity vector (different forces on different mesh vertices due to potentially varying mass densities)
  // gravityForce must be a pre-allocated vector of length 3xnumVertices()
  void computeGravity(double * gravityForce, double g=9.81, bool addForce=false) const;

  // edge queries
  virtual int getNumElementEdges() const = 0;
  virtual void getElementEdges(int el, int * edgeBuffer) const = 0; // edgeBuffer must be pre-allocated, of size 2 x numElementEdges()

  // (permanently) applies the deformation to the vertices of the mesh
  void applyDeformation(double * u);
  void applyLinearTransformation(double * pos, double * R); // transforms every vertex as X |--> pos + R * X (R must be given row-major)

  // === submesh creation ===

  // (permanently) set this mesh to its submesh containing the specified elements (i.e., delete the mesh elements not on the given list of elements)
  // if vertexMap is non-null, it also returns a renaming datastructure: vertexMap[big mesh vertex] is the vertex index in the subset mesh
  void setToSubsetMesh(std::set<int> & subsetElements, int removeIsolatedVertices=1, std::map<int,int> * vertexMap = NULL);

  // === interpolation ===

  // the interpolant is a triple (numTargetLocations, vertices, weights)
  // Generates interpolation weights to transfer quantities from volumetric mesh to (embedded) surface meshes.
  // Input is a list of 3D target locations where the interpolant will be computed,
  // e.g., those could be vertices of a triangle mesh embedded into the volumetric mesh.
  // Each location is a 3-vector, i.e., 3 consecutive double-precision values.
  // If zeroThreshold is set positive, than for any target location that is 
  //   more than zeroThreshold away from the closest element, 
  //   all weights will be set to zero; this is useful, e.g. to 
  //   fix locations far away from your mesh.
  // Output: vertices and weights arrays
  // vertices: gives a list of integer indices of the vertices of the element
  //   closest to the target location (numElementVertices entries per target location, one for each element vertex)
  //   note: if target location is inside a voxel, that voxel will be chosen as closest
  // weights: a list of numElementVertices_ weights, as per the numElementVertices_ vertices of each element (weights sum to 1)
  // If zeroThreshold >= 0, then the points that are further than zeroThreshold away from any volumetric mesh vertex, are assigned weights of 0.
  // If elements is not NULL, the closest elements for each target location will be returned in the integer list "*elements" (allocated inside the function)
  // If elements is not NULL, the function will allocate an integer array *elements, and return the closest element to each target location in it.
  // Returns the number of target points that do not lie inside any element.
  int generateInterpolationWeights(int numTargetLocations, const double * targetLocations, int ** vertices, double ** weights, double zeroThreshold = -1.0, int ** elements = NULL, int verbose=0) const; // this is the "master" function, meant to be typically used to create the interpolant

  // interpolates 3D vector data from vertices of the 
  //   volumetric mesh (data given in u) to the target locations (output goes into uTarget)
  //   e.g., use this to interpolate deformation from the volumetric mesh to a triangle mesh
  static void interpolate(const double * u, double * uTarget, int numTargetLocations, int numElementVertices, const int * vertices, const double * weights);

  // the following are less often used, more specialized functions
  // same as "generateInterpolationWeights" above, except here the elements that contain the target locations are assumed to be known, and are provided in array "elements"; returns 0 on success, 1 otherwise
  int generateInterpolationWeights(int numTargetLocations, const double * targetLocations, int * elements, int ** vertices, double ** weights, double zeroThreshold = -1.0, int verbose=0) const; 
  // generates the integer list "elements" of the elements that contain given vertices; if closestElementIfOutside==1, then vertices outside of the mesh are assigned the closest element, otherwise -1 is assigned; returns the number of target locations outside of the mesh
  int generateContainingElements(int numTargetLocations, const double * targetLocations, int ** elements, int useClosestElementIfOutside=1, int verbose=0) const; 
  static int getNumInterpolationElementVertices(const char * filename); // looks at the first line of "filename" to determine "numElementVertices" for this particular interpolant
  static int loadInterpolationWeights(const char * filename, int numTargetLocations, int numElementVertices, int ** vertices, double ** weights); // ASCII version; returns 0 on success
  static int saveInterpolationWeights(const char * filename, int numTargetLocations, int numElementVertices, const int * vertices, const double * weights); // ASCII version
  static int loadInterpolationWeightsBinary(const char * filename, int * numTargetLocations, int * numElementVertices, int ** vertices, double ** weights); // binary version; returns 0 on success
  static int saveInterpolationWeightsBinary(const char * filename, int numTargetLocations, int numElementVertices, const int * vertices, const double * weights); // binary version
  static int loadInterpolationWeightsBinary(FILE * fin, int * numTargetLocations, int * numElementVertices, int ** vertices, double ** weights); // binary version; returns 0 on success
  static int saveInterpolationWeightsBinary(FILE * fout, int numTargetLocations, int numElementVertices, const int * vertices, const double * weights); // binary version

  // computes barycentric weights of the given position with respect to the given element
  virtual void computeBarycentricWeights(int element, const Vec3d & pos, double * weights) const = 0;

  // computes the gradient of a 3D vector field (specified at the volumetric mesh vertices), at the location "pos"
  // "numFields" fields can be interpolated simultaneously; each is given as one column of the U matrix
  // U is a 3numVertices x numFields matrix; stored column-major
  // output: grad is 9 x numFields matrix, stored column-major; each column gives the gradient (3x3 matrix), stored row-major format
  // return: 0 if pos inside the mesh, 1 otherwise
  int interpolateGradient(const double * U, int numFields, Vec3d pos, double * grad) const;
  // in this version, the element containing the "pos" must be known, and prescribed directly
  virtual void interpolateGradient(int element, const double * U, int numFields, Vec3d pos, double * grad) const = 0;

  // === material-related nested classes ===

  // a set of integers, with a name (used for example, to store elements that share the same material properties)
  class Set
  {
  public:

    Set(const std::string & name);
    Set(const Set & set);
    Set(const std::string & name, const std::set<int> & elements);

    inline std::string getName() const;
    inline int getNumElements() const;
    inline void getElements(std::set<int> & elements) const;
    inline const std::set<int> & getElements() const;
    inline bool isMember(int element) const;

    inline std::set<int> & getElements();
    inline void insert(int element);
    inline void clear();

  protected:
    std::string name;
    std::set<int> elements;
  };

  // stores a material (abstract class)
  class Material
  {
  public:
    Material(const std::string name, double density);
    Material(const Material & material);
    virtual ~Material() {};
    virtual Material * clone() const = 0;

    inline std::string getName() const; // material name
    inline double getDensity() const; // density
    inline void setName(const std::string name);
    inline void setDensity(double density);

    // ENU = any isotropic material parameterized by E (Young's modulus), nu (Poisson's ratio)
    // ORTHOTROPIC = orthotropic anisotropic material
    // MOONEYRIVLIN = Mooney-Rivlin material
    typedef enum { INVALID, ENU, ORTHOTROPIC, MOONEYRIVLIN } materialType;
    virtual materialType getType() = 0;

    typedef enum { ENU_DENSITY, ENU_E, ENU_NU, ENU_NUM_PROPERTIES } enuMaterialProperties;
    typedef enum { ORTHOTROPIC_DENSITY, ORTHOTROPIC_E1, ORTHOTROPIC_E2, ORTHOTROPIC_E3, ORTHOTROPIC_NU12, ORTHOTROPIC_NU23, ORTHOTROPIC_NU31, ORTHOTROPIC_G12, ORTHOTROPIC_G23, ORTHOTROPIC_G31, ORTHOTROPIC_NUM_PROPERTIES } orthotropicMaterialProperties;
    typedef enum { MOONEYRIVLIN_DENSITY, MOONEYRIVLIN_MU01, MOONEYRIVLIN_MU10, MOONEYRIVLIN_V1, MOONEYRIVLIN_NUM_PROPERTIES } mooneyrivlinMaterialProperties;

  protected:
    std::string name;
    double density;
  };

  // material with E (Young's modulus), nu (Poisson's ratio) (defined in volumetricMeshENuMaterial.h)
  class ENuMaterial;
  // Mooney-Rivlin material (defined in volumetricMeshMooneyRivlinMaterial.h)
  class MooneyRivlinMaterial;
  // Orthotropic material (defined in volumetricMeshOrthotropicMaterial.h)
  class OrthotropicMaterial;

  // a volumetric mesh region, i.e., a set of elements sharing the same material
  class Region
  {
  public:
    Region(int materialIndex, int setIndex);
    inline int getMaterialIndex() const;
    inline int getSetIndex() const;
    inline void setMaterialIndex(int index);
    inline void setSetIndex(int index);

  protected:
    int setIndex, materialIndex;
  };

  static double E_default;
  static double nu_default;
  static double density_default;

protected:
  int numVertices;
  Vec3d * vertices;

  int numElementVertices;
  int numElements;
  int ** elements;

  int numMaterials;
  int numSets;
  int numRegions;
  Material ** materials;
  Set ** sets; 
  Region ** regions;
  int * elementMaterial;  // material index of each element

  // parses the mesh, and returns the mesh element type
  VolumetricMesh(const char * filename, fileFormatType fileFormat, int numElementVertices, elementType * elementType_, int verbose);
  // if memoryLoad is 0, binaryInputStream is FILE* (load from a file, via a stream), otherwise, it is char* (load from a memory buffer)
  VolumetricMesh(void * binaryInputStream, int numElementVertices, elementType * elementType_, int memoryLoad = 0);
  VolumetricMesh(int numElementVertices_) { numElementVertices = numElementVertices_; }
  void propagateRegionsToElements();
  void loadFromBinaryGeneric(void * binaryInputStream, elementType * elementType_, int memoryLoad);

  // constructs a mesh from the given vertices and elements, 
  // with a single region and material ("E, nu" material)
  // "vertices" is double-precision array of length 3 x numVertices 
  // "elements" is an integer array of length numElements x numElementVertices
  VolumetricMesh(int numVertices, double * vertices, 
         int numElements, int numElementVertices, int * elements,
         double E=E_default, double nu=nu_default, double density=density_default); 

  // constructs a mesh from the given vertices and elements, 
  // with an arbitrary number of sets, regions and materials
  // "vertices" is double-precision array of length 3 x numVertices 
  // "elements" is an integer array of length numElements x numElementVertices
  // "materials", "sets" and "regions" will be copied internally (deep copy), so they
  // can be released after calling this constructor
  VolumetricMesh(int numVertices, double * vertices, 
         int numElements, int numElementVertices, int * elements,
         int numMaterials, Material ** materials,
         int numSets, Set ** sets,
         int numRegions, Region ** regions);

  // creates a submesh consisting of the specified elements of the given mesh
  // if vertexMap is non-null, it also returns a renaming datastructure: vertexMap[big mesh vertex] is the vertex index in the subset mesh
  VolumetricMesh(const VolumetricMesh & mesh, int numElements, int * elements, std::map<int,int> * vertexMap = NULL); 

  int saveToAscii(const char * filename, elementType elementType_) const;
  int saveToBinary(const char * filename, unsigned int * bytesWritten, elementType elementType_) const;
  int saveToBinary(FILE * binaryOutputStream, unsigned int * bytesWritten, elementType elementType_, bool countBytesOnly = false) const;

  void loadFromAscii(const char * filename, elementType * elementType_, int verbose = 0);
  void loadFromBinary(const char * filename, elementType * elementType_);
  void loadFromBinary(FILE * binaryInputStream, elementType * elementType_);
  void loadFromMemory(unsigned char * binaryInputStream, elementType * elementType_);
  void assignMaterialsToElements(int verbose);

  static elementType getElementTypeASCII(const char * filename); 
  static elementType getElementTypeBinary(const char * filename);

  elementType temp; // auxiliary

  friend class VolumetricMeshExtensions;
  friend class VolumetricMeshLoader;

  static unsigned int readFromFile(void * buf, unsigned int elementSize, unsigned int numElements, void * fin);
  static unsigned int readFromMemory(void * buf, unsigned int elementSize, unsigned int numElements, void * memoryLocation);
};

inline VolumetricMesh::Set::Set(const std::string & name_) { name = name_; }
inline VolumetricMesh::Set::Set(const Set & set) { elements = set.elements; name = set.getName(); }
inline VolumetricMesh::Set::Set(const std::string & name_, const std::set<int> & elements_) : name(name_), elements(elements_) {}
inline std::string VolumetricMesh::Set::getName() const { return name; }
inline int VolumetricMesh::Set::getNumElements() const { return (int)(this->elements.size()); }
inline void VolumetricMesh::Set::getElements(std::set<int> & elements) const { elements = this->elements; }
inline const std::set<int> & VolumetricMesh::Set::getElements() const { return elements; }
inline std::set<int> & VolumetricMesh::Set::getElements() { return elements; }
inline bool VolumetricMesh::Set::isMember(int element) const {return (elements.find(element) != elements.end());}
inline void VolumetricMesh::Set::insert(int element) { elements.insert(element); }
inline void VolumetricMesh::Set::clear() { elements.clear(); }

inline VolumetricMesh::Material::Material(const std::string name_, double density_): density(density_) { name = name_; }
inline VolumetricMesh::Material::Material(const Material & material) : density(material.getDensity()) { name = material.getName(); }
inline std::string VolumetricMesh::Material::getName() const { return name; }  // material name
inline double VolumetricMesh::Material::getDensity() const { return density; } // density
inline void VolumetricMesh::Material::setName(const std::string name_) { name = name_; }
inline void VolumetricMesh::Material::setDensity(double density_) { density = density_; }

inline VolumetricMesh::Region::Region(int materialIndex_, int setIndex_): setIndex(setIndex_), materialIndex(materialIndex_) {}
inline int VolumetricMesh::Region::getMaterialIndex() const { return materialIndex; }
inline int VolumetricMesh::Region::getSetIndex() const { return setIndex; }
inline void VolumetricMesh::Region::setMaterialIndex(int index) { materialIndex = index; }
inline void VolumetricMesh::Region::setSetIndex(int index) { setIndex = index; }

#endif

