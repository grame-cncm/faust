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
  Author: Jernej Barbic, 2003
  Generates a voxel representation of an offset surface
*/

#if defined(_WIN32) || defined(WIN32)
  #pragma warning(disable : 4996)
  #pragma warning(disable : 4267)
  #pragma warning(disable : 4244)
#endif
#include "objMeshOffsetVoxels.h"
#include "matrixIO.h"
#include "matrixMacros.h"
#include <fstream>
#include <iomanip>
#include <string.h>
using namespace std;

ObjMeshOffsetVoxels::ObjMeshOffsetVoxels( ObjMesh * objMesh_, int resolution_[3], int depth_, Vec3d bmin_, Vec3d bmax_ )
{
  objMesh = new ObjMesh(*objMesh_);
  init(resolution_, depth_, bmin_, bmax_);
}

ObjMeshOffsetVoxels::ObjMeshOffsetVoxels( ObjMesh * objMesh_, int resolution_[3], int depth_, double expansionFactor )
{
  objMesh = new ObjMesh(*objMesh_);

  // build mesh bounding box
  Vec3d bmin_, bmax_;
  objMesh->getCubicBoundingBox(expansionFactor, &bmin_, &bmax_);

  init(resolution_, depth_, bmin_, bmax_);
}

void ObjMeshOffsetVoxels::init(int resolution_[3], int depth_, Vec3d bmin_, Vec3d bmax_)
{
  resolution[0] = resolution_[0];
  resolution[1] = resolution_[1];
  resolution[2] = resolution_[2];
  depth = depth_;
  bmin = bmin_;
  bmax = bmax_;

  //cout << "Entering obj mesh voxelization routine..." << endl;
  //cout << "Resolution is " << resolution[0] << " x " << resolution[1] << " x " << resolution[2] << " ..." << endl;

  //cout << "Checking if mesh is triangular... ";
  if (!(objMesh->isTriangularMesh()))
  {
    //cout << "mesh was not triangular: triangulating... ";
    objMesh->triangulate();
    //cout << "done" << endl;
  }
  else
  {
    //cout << "yes" << endl;
  }

  side = bmax - bmin;
  inc[0] = side[0] / resolution[0];
  inc[1] = side[1] / resolution[1];
  inc[2] = side[2] / resolution[2];

  //cout << "Scene bounding box is: " << bmin << " " << bmax << endl;
  //cout << "Computing voxels intersecting the model..." << endl;

  // iterate over all triangles
  // for every triangle, find the voxel containing its center of mass
  // then, grow the voxels until they don't intersect the triangle any more

  voxels.clear(); // will contain voxels intersecting the triangles 

  // local search helpers:
  set<voxel> checkedVoxels; // used to mark what voxels have already been visited
  vector<voxel> scheduledVoxels; // contains voxels still to be processed
  for (unsigned int i=0; i<objMesh->getNumGroups(); i++)
  {
    const ObjMesh::Group * getGroupHandle = objMesh->getGroupHandle(i);
      
    for (unsigned int j=0; j<getGroupHandle->getNumFaces(); j++)
    {
      Vec3d p0 = objMesh->getPosition(getGroupHandle->getFace(j).getVertex(0).getPositionIndex());
      Vec3d p1 = objMesh->getPosition(getGroupHandle->getFace(j).getVertex(1).getPositionIndex());
      Vec3d p2 = objMesh->getPosition(getGroupHandle->getFace(j).getVertex(2).getPositionIndex());
      TriangleBasic triangle(p0,p1,p2);

      Vec3d center = 1.0 / 3 * (p0 + p1 + p2);
      Vec3d relCenter = center-bmin;

      // find voxel containing center
      int vi,vj,vk;
      vi = (int)(relCenter[0] / inc[0]);
      vj = (int)(relCenter[1] / inc[1]);
      vk = (int)(relCenter[2] / inc[2]);

      checkedVoxels.clear();
      checkedVoxels.insert(voxel(vi,vj,vk));

      scheduledVoxels.clear();
      scheduledVoxels.push_back(voxel(vi,vj,vk));

      // while there are still some scheduled voxels:
      //   take one
      //   check if intersecting the triangle
      //   if yes
      //     add voxel to voxels
      //     queue all neighbors that haven't been visited yet
     
      while (!scheduledVoxels.empty())
      {
        voxel v = scheduledVoxels.back();
        scheduledVoxels.pop_back();
     
        // make bounding box for voxel
        Vec3d bbmin = bmin + Vec3d(v.first * inc[0], v.second * inc[1], v.third * inc[2]);
        BoundingBox bbox(bbmin, bbmin + inc);

        if (triangle.doesIntersectBox(bbox)) // intersection test
        {
	  // add the voxel to the final list of hits
          voxels.insert(v);
          // queue all neighbors of v, and also put them into checkedVoxels
          // (but don't do anything if they have already been queued)
          voxel neighbor;
          #define PROCESS(ii,jj,kk)\
          neighbor = voxel(v.first+(ii),v.second+(jj),v.third+(kk));\
          if ((neighbor.first >= 0) && (neighbor.first <= resolution[0]) &&\
              (neighbor.second >= 0) && (neighbor.second <= resolution[1]) &&\
              (neighbor.third >= 0) && (neighbor.third <= resolution[2])) \
          {\
            if (checkedVoxels.find(neighbor) == checkedVoxels.end())\
            {\
              checkedVoxels.insert(neighbor);\
              scheduledVoxels.push_back(neighbor);\
            }\
          }
          for (int iii=-1; iii<=1; iii++)
            for (int jjj=-1; jjj<=1; jjj++)
              for (int kkk=-1; kkk<=1; kkk++)
              {
                if ((iii == 0) && (jjj ==0) && (kkk==0))
                  continue;
                PROCESS(iii,jjj,kkk)
              }
        }  
      }

      // now, voxels contains all voxels that intersect the given triangle (plus everything from previous triangles) 
    }
  }

  // now, voxels contains all voxels intersecting any triangle

  //cout << "Growing " << depth << " layers of voxels out of the original (squashing cubes) layer." << endl;

  // grow voxels several layers
  set<voxel> voxeli; // temporary buffer
  for (int i=0; i<depth; i++)
  {
    // expand all voxels in all directions
    // take everything out of voxels, expand one layer, and insert into voxeli
    voxeli.clear();

    voxel neighbor;

    #define PROCESSI(ii,jj,kk)\
      neighbor = voxel(vox->first+(ii),vox->second+(jj),vox->third+(kk));\
      if ((neighbor.first >= 0) && (neighbor.first <= resolution[0]) &&\
          (neighbor.second >= 0) && (neighbor.second <= resolution[1]) &&\
          (neighbor.third >= 0) && (neighbor.third <= resolution[2])) \
      {\
	voxeli.insert(neighbor);\
      }
    
    set<voxel>::iterator vox;

    for (vox = voxels.begin(); vox != voxels.end(); ++vox) // over all members of voxels
    {
      for (int iii=-1; iii<=1; iii++)
        for (int jjj=-1; jjj<=1; jjj++)
          for (int kkk=-1; kkk<=1; kkk++)
          {
            PROCESSI(iii,jjj,kkk)
          }
    }
    voxels = voxeli;
  }

  //cout << "Building unique list of faces..." << endl;
  // build unique list of faces

  buildUniqueListOfFaces(); 
}

void ObjMeshOffsetVoxels::emptyComponents(vector<Vec3d> & componentSeeds, vector<int> & componentSize, bool interiorOnly)
{
  componentSeeds.clear();
  componentSize.clear();

  set<voxel> voxelSet = voxels;

  for(int i=0; i<resolution[0]; i++)
    for(int j=0; j<resolution[1]; j++)
      for(int k=0; k<resolution[2]; k++)
      {
        if (voxelSet.find(voxel(i,j,k)) == voxelSet.end())
        {
          // new component detected
          size_t sizePrev = voxelSet.size();
          Vec3d seed(bmin[0] + inc[0] * ( i + 0.5 ),
                     bmin[1] + inc[1] * ( j + 0.5 ),
                     bmin[2] + inc[2] * ( k + 0.5 ));
          bool touchesBoundingBox = floodFillFromSet(seed, voxelSet);
          if (!(interiorOnly && touchesBoundingBox))
          {
            componentSize.push_back(voxelSet.size() - sizePrev);
            componentSeeds.push_back(seed);
          }
        }
      }
}

void ObjMeshOffsetVoxels::floodFill(Vec3d seed)
{
  //cout << "Flood-filling from seed: " << seed << endl;
  floodFillFromSet(seed, voxels);
  buildUniqueListOfFaces();
}

void ObjMeshOffsetVoxels::floodFill(vector<Vec3d> & seeds)
{
  for(unsigned int i=0; i<seeds.size(); i++)
  {
    //cout << "Flood-filling from seed: " << seeds[i] << endl;
    floodFillFromSet(seeds[i], voxels);
  }

  buildUniqueListOfFaces();
}

bool ObjMeshOffsetVoxels::floodFillFromSet(Vec3d seed, set<voxel> & voxelSet)
{
  bool touchesBoundingBox = false;

  // find voxel containing seed
  int vi,vj,vk;
  Vec3d relSeed = seed-bmin;
  vi = (int)(relSeed[0] / inc[0]);
  vj = (int)(relSeed[1] / inc[1]);
  vk = (int)(relSeed[2] / inc[2]);

  if ((vi < 0) || (vi >= resolution[0]) ||
     (vj < 0) || (vj >= resolution[1]) ||
     (vk < 0) || (vk >= resolution[2]))
  {
    printf("Warning: flood-filling seed is outside the bounding box. Performing no flood-fill.\n");
    return false;
  }
  

  voxel seedVoxel(vi,vj,vk);

  set<voxel> queue;
  queue.insert(seedVoxel);
  voxelSet.insert(seedVoxel);

  while (!queue.empty())
  {
    //cout << "." << flush;

    voxel vox = *(queue.begin());
    queue.erase(vox);

    voxel neighbor;
    
    //printf("vox: %d %d %d\n",vox.first,vox.second,vox.third);

    // process all 8 neighbors
    #define PROCESSNGH(ii,jj,kk)\
    neighbor = voxel(vox.first+(ii),vox.second+(jj),vox.third+(kk));\
    if ((neighbor.first >= 0) && (neighbor.first < resolution[0]) &&\
        (neighbor.second >= 0) && (neighbor.second < resolution[1]) &&\
        (neighbor.third >= 0) && (neighbor.third < resolution[2])) \
    {\
      if (voxelSet.find(neighbor) == voxelSet.end())\
      {\
        queue.insert(neighbor);\
        voxelSet.insert(neighbor);\
        if (!touchesBoundingBox)\
          if ((neighbor.first == 0)  || (neighbor.first == resolution[0] - 1) ||\
              (neighbor.second == 0) || (neighbor.second == resolution[1] - 1) ||\
              (neighbor.third == 0)  || (neighbor.third == resolution[2] - 1))\
                touchesBoundingBox = true;\
      }\
    }

    PROCESSNGH(1,0,0);
    PROCESSNGH(-1,0,0);
    PROCESSNGH(0,1,0);
    PROCESSNGH(0,-1,0);
    PROCESSNGH(0,0,1);
    PROCESSNGH(0,0,-1);
  }

  return touchesBoundingBox;
}

void ObjMeshOffsetVoxels::buildUniqueListOfFaces()
{
  surfaceFaces.clear();
  interiorFaces.clear();
  
  set<voxel>::iterator vox;
  for (vox = voxels.begin(); vox != voxels.end(); ++vox) // over all members of voxels
  {
    // for each face of vox:
    //   if already on the list of surface faces, erase it from there, and add it among interior faces
    //   else add it among surface faces
  
    //cout << "Voxel: " << vox->first << " " << vox->second << " " << vox->third << endl;
  
    gridPoint pmin(vox->first,vox->second,vox->third);
    gridPoint pmax(vox->first+1,vox->second+1,vox->third+1);

    gridPoint p0(pmin.first,pmin.second,pmin.third);
    gridPoint p1(pmax.first,pmin.second,pmin.third);
    gridPoint p2(pmax.first,pmax.second,pmin.third);
    gridPoint p3(pmin.first,pmax.second,pmin.third);
  
    gridPoint p4(pmin.first,pmin.second,pmax.third);
    gridPoint p5(pmax.first,pmin.second,pmax.third);
    gridPoint p6(pmax.first,pmax.second,pmax.third);
    gridPoint p7(pmin.first,pmax.second,pmax.third);
  
    TopologicalFace * face;
    
    #define PROCESS_FACE(q0,q1,q2,q3)\
    face = new TopologicalFace((q0),(q1),(q2),(q3));\
    if (surfaceFaces.find(*face) != surfaceFaces.end())\
    {\
      surfaceFaces.erase(*face);\
      interiorFaces.insert(*face);\
    }\
    else\
    {\
      surfaceFaces.insert(*face);\
    }\
    delete(face);

    PROCESS_FACE(p0,p3,p2,p1)
    PROCESS_FACE(p4,p5,p6,p7)
    PROCESS_FACE(p0,p1,p5,p4)
    PROCESS_FACE(p3,p7,p6,p2)
    PROCESS_FACE(p1,p2,p6,p5)
    PROCESS_FACE(p0,p4,p7,p3)
  }
}

void ObjMeshOffsetVoxels::render()
{
  set<voxel>::iterator vox;
  for (vox = voxels.begin(); vox != voxels.end(); ++vox) // over all members of voxels
     renderVoxel(*vox);
}

void ObjMeshOffsetVoxels::renderSurfaceFaces()
{
  set<TopologicalFace,FaceOrder>::iterator face;

  for (face = surfaceFaces.begin(); face != surfaceFaces.end(); ++face) // over all surface faces
    renderTopologicalFace(*face);
}



void ObjMeshOffsetVoxels::renderVoxel(voxel vox)
{
  // make bounding box for voxel
  Vec3d bbmin = bmin + Vec3d(vox.first*inc[0],vox.second*inc[1],vox.third*inc[2]);
  BoundingBox bbox(bbmin,bbmin+inc);
  bbox.render();
}

void ObjMeshOffsetVoxels::renderTopologicalFace(const TopologicalFace & face) const
{
  // make flat bounding box
  Vec3d bbmin = Vec3d(face.vertex(0).first*inc[0],face.vertex(0).second*inc[1],face.vertex(0).third*inc[2]);
  bbmin += bmin;
  Vec3d bbmax = Vec3d(face.vertex(2).first*inc[0],face.vertex(2).second*inc[1],face.vertex(2).third*inc[2]);
  bbmax += bmin;
  BoundingBox bbox(bbmin,bbmax);
  bbox.render();
}

ObjMesh * ObjMeshOffsetVoxels::surfaceOffsetMesh()
{
  ObjMesh * objMesh = new ObjMesh();

  // create a list of vertices
  set<gridPoint> vertices;

  set<TopologicalFace,FaceOrder>::iterator face; // insert all vertices
  for (face = surfaceFaces.begin(); face != surfaceFaces.end(); ++face) // over all surface faces
  {
    vertices.insert(face->vertex(0));
    vertices.insert(face->vertex(1));
    vertices.insert(face->vertex(2));
    vertices.insert(face->vertex(3));
  }

  // now, vertices contains all vertices with no duplications

  // create default group
  objMesh->addGroup("Default");    

  // add all vertices into a map, together with their corresponding position
  // also, add vertices to objMesh
  map<gridPoint,int> vertices2;
  set<gridPoint>:: iterator v;
  int position=0;
  for (v = vertices.begin(); v != vertices.end(); ++v)
  {
    vertices2.insert(pair<gridPoint,int>(*v,position));
    Vec3d pos = bmin + Vec3d(v->first*inc[0], v->second*inc[1], v->third*inc[2]);
    objMesh->addVertexPosition( pos );
    //cout << "Position " << position << ": " << pos << endl;
    position++;
  }

  // add all faces
  unsigned int index;
  for (face = surfaceFaces.begin(); face != surfaceFaces.end(); ++face) // over all surface faces
  {
    ObjMesh::Face newFace;
    for (int i=0; i<4; i++)
    {
      index = (vertices2.find(face->vertex(i)))->second;

      std::pair< bool, unsigned int > texPos(false,0); // no textures or normals assigned
      std::pair< bool, unsigned int > normal(false,0);

      newFace.addVertex( ObjMesh::Vertex( index, texPos, normal ) );

    }
    objMesh->addFaceToGroup(newFace,0);
  }

  return objMesh;
}

bool ObjMeshOffsetVoxels::FaceOrder::operator()(const TopologicalFace & x, const TopologicalFace & y) const
{

  // first, sort the vertices on each face (order of vertices is irrelevant when comparing if two faces are equal)
  TopologicalFace xSorted = x; xSorted.sortVertices();
  TopologicalFace ySorted = y; ySorted.sortVertices();

  for (int i=0; i<4; i++)
  {
    gridPoint x1 = xSorted.vertex(i);
    gridPoint y1 = ySorted.vertex(i);

    if (x1 < y1)
      return true;
    if (y1 < x1)
      return false;
  }

  return false;
}

ObjMeshOffsetVoxels::TopologicalFace::TopologicalFace(gridPoint p1, gridPoint p2, gridPoint p3, gridPoint p4)
{
  vertices_.push_back(p1); vertices_.push_back(p2); vertices_.push_back(p3); vertices_.push_back(p4);

  assert(vertices_.size() == 4);
}

void ObjMeshOffsetVoxels::TopologicalFace::sortVertices()
{
  sort(vertices_.begin(),vertices_.end());

  // sanity check
  unique(vertices_.begin(),vertices_.end());
  assert(vertices_.size() == 4);
}

void ObjMeshOffsetVoxels::generateCubicMesh(const string & filenameVeg, const string & filenameInterp, const string & filenameObj)
{
  cout << "Generating cubic mesh..." << endl;
  cout << "Writing mesh to " << filenameVeg << " ." << endl;

  // open file
  ofstream fout(filenameVeg.c_str());

  if (!fout)
  {
    cout << "Error: could not write to file " << filenameVeg << endl;
    return;
  }

  // create a list of vertices in all voxels
  set<gridPoint> vertices;
  // insert all voxel vertices
  set<voxel>::iterator aVoxel; 
  for (aVoxel = voxels.begin(); aVoxel != voxels.end(); ++aVoxel) // over all voxels
  {
    unsigned int i1,j1,k1;
    i1 = aVoxel->first;
    j1 = aVoxel->second;
    k1 = aVoxel->third;

    vertices.insert(gridPoint(i1,j1,k1));
    vertices.insert(gridPoint(i1+1,j1,k1));
    vertices.insert(gridPoint(i1+1,j1+1,k1));
    vertices.insert(gridPoint(i1,j1+1,k1));

    vertices.insert(gridPoint(i1,j1,k1+1));
    vertices.insert(gridPoint(i1+1,j1,k1+1));
    vertices.insert(gridPoint(i1+1,j1+1,k1+1));
    vertices.insert(gridPoint(i1,j1+1,k1+1));
  } 
  
  // now, vertices contains all voxel vertices with no duplications

  cout << "Num voxels: " << voxels.size() << " Num voxel vertices: " << vertices.size() << endl; 

  // open up the objMesh for the output surface mesh
  ObjMesh * objMesh = new ObjMesh();

  // create default group
  objMesh->addGroup("Default");
  
  // add all voxel vertices into a map, together with their corresponding index (i.e. serial number of a voxel vertex in the set order)
  map<gridPoint,int> vertices2;
  set<gridPoint>:: iterator v; // will run over all voxel vertices
  int position=0;

  fout << "*VERTICES" << endl;
  fout << (int)vertices.size() << " 3 0 0" << endl;

  for (v = vertices.begin(); v != vertices.end(); ++v)
  {
    vertices2.insert(pair<gridPoint,int>(*v,position));
    Vec3d pos = bmin + Vec3d(v->first*inc[0], v->second*inc[1], v->third*inc[2]);
    objMesh->addVertexPosition(pos);

    //cout << "Position " << position << ": " << pos << endl;
    position++;

    // write vertex to file
    fout << setprecision (16) << position << " " << pos[0] << " " << pos[1] << " " << pos[2] << endl;
  } 
  
  fout << endl;
  fout << "*ELEMENTS" << endl;
  fout << "CUBIC" << endl;
  fout << (int)voxels.size() << " 4 0" <<  endl;

  // print out all voxels
  unsigned int index;
  position = 0;
  for (aVoxel = voxels.begin(); aVoxel != voxels.end(); ++aVoxel) // over all voxels
  {
    fout << position+1;
    unsigned int i1,j1,k1;
    i1 = aVoxel->first;
    j1 = aVoxel->second;
    k1 = aVoxel->third;

    #define PROCESS_CORNER(di,dj,dk)\
    index = 1+(vertices2.find(gridPoint(i1+(di),j1+(dj),k1+(dk))))->second;\
    fout << " " << index;    

    PROCESS_CORNER(0,0,0);
    PROCESS_CORNER(1,0,0);
    PROCESS_CORNER(1,1,0);
    PROCESS_CORNER(0,1,0);
    PROCESS_CORNER(0,0,1);
    PROCESS_CORNER(1,0,1);
    PROCESS_CORNER(1,1,1);
    PROCESS_CORNER(0,1,1);

    fout << endl;

    position++;
  } 

  fout.close();

  // generate the barycentric masks

  cout << "Writing interpolation info to file " << filenameInterp << " ." << endl;

  // open file
  fout.open(filenameInterp.c_str());

  if (!fout)
  {
    cout << "Error: could not write to file " << filenameInterp << endl;
    return;
  }

  // for every vertex of the mesh, find what voxel it is in
  // then find indices of the vertices of that voxel
  // and compute the barycentric coordinates
  
  for (unsigned int i=0; i < objMesh->getNumVertices(); i++) // over all vertices of the mesh
  {
    Vec3d pos = objMesh->getPosition(i);
    unsigned int i1,j1,k1;
    
    Vec3d relPos = pos-bmin;

    // find voxel containing 'pos'
    i1 = (unsigned int)(relPos[0] / inc[0]);
    j1 = (unsigned int)(relPos[1] / inc[1]);
    k1 = (unsigned int)(relPos[2] / inc[2]);

    // compute barycentric coordinates
    Vec3d w = pos - (bmin + Vec3d(i1 * inc[0], j1 * inc[1], k1 * inc[2]));
    double alpha = w[0] / inc[0];     
    double beta = w[1] / inc[1];     
    double gamma = w[2] / inc[2];     

    unsigned int c000 = vertices2.find(gridPoint(i1+0,j1+0,k1+0))->second;
    unsigned int c100 = vertices2.find(gridPoint(i1+1,j1+0,k1+0))->second;
    unsigned int c110 = vertices2.find(gridPoint(i1+1,j1+1,k1+0))->second;
    unsigned int c010 = vertices2.find(gridPoint(i1+0,j1+1,k1+0))->second;

    unsigned int c001 = vertices2.find(gridPoint(i1+0,j1+0,k1+1))->second;
    unsigned int c101 = vertices2.find(gridPoint(i1+1,j1+0,k1+1))->second;
    unsigned int c111 = vertices2.find(gridPoint(i1+1,j1+1,k1+1))->second;
    unsigned int c011 = vertices2.find(gridPoint(i1+0,j1+1,k1+1))->second;

    double f000 = (1-alpha)*(1-beta)*(1-gamma);
    double f100 = (alpha)*(1-beta)*(1-gamma);
    double f110 = (alpha)*(beta)*(1-gamma);
    double f010 = (1-alpha)*(beta)*(1-gamma);

    double f001 = (1-alpha)*(1-beta)*(gamma);
    double f101 = (alpha)*(1-beta)*(gamma);
    double f111 = (alpha)*(beta)*(gamma);
    double f011 = (1-alpha)*(beta)*(gamma);

    fout << i << " ";

    fout << c000 << " " << f000 << " ";
    fout << c100 << " " << f100 << " ";
    fout << c110 << " " << f110 << " ";
    fout << c010 << " " << f010 << " ";

    fout << c001 << " " << f001 << " ";
    fout << c101 << " " << f101 << " ";
    fout << c111 << " " << f111 << " ";
    fout << c011 << " " << f011 << endl;
  }

  fout.close();

  // by now, surfaceFaces contains a unique list of all surface faces
  // add all faces to the surface obj mesh of the voxel mesh
  set<TopologicalFace,FaceOrder>::iterator face;
  for (face = surfaceFaces.begin(); face != surfaceFaces.end(); ++face) // all surface faces
  {
    int index[4];
    for (int i=0; i<4; i++)
      index[i] = (vertices2.find(face->vertex(i)))->second;
 
    std::pair< bool, unsigned int > texPos(false,0); // no textures 
    std::pair< bool, unsigned int > normal(false,0); // no normals

/*
    // triangulate the face into two triangles

    Face newFace1;
    newFace1.addVertex( Vertex( index[0], texPos, normal ) );
    newFace1.addVertex( Vertex( index[1], texPos, normal ) );
    newFace1.addVertex( Vertex( index[2], texPos, normal ) );

    Face newFace2;
    newFace2.addVertex( Vertex( index[2], texPos, normal ) );
    newFace2.addVertex( Vertex( index[3], texPos, normal ) );
    newFace2.addVertex( Vertex( index[0], texPos, normal ) );

    objMesh->addFaceToGroup(newFace1,0);
    objMesh->addFaceToGroup(newFace2,0);
*/

    // make one quad face

    ObjMesh::Face newFace;
    newFace.addVertex( ObjMesh::Vertex( index[0], texPos, normal ) );
    newFace.addVertex( ObjMesh::Vertex( index[1], texPos, normal ) );
    newFace.addVertex( ObjMesh::Vertex( index[2], texPos, normal ) );
    newFace.addVertex( ObjMesh::Vertex( index[3], texPos, normal ) );

    objMesh->addFaceToGroup(newFace,0);
  }

  // search if there already is "default" material; if there is not, add it
  objMesh->addDefaultMaterial();
  objMesh->computeBoundingBox();

  objMesh->save(filenameObj);

  delete(objMesh);
}

void ObjMeshOffsetVoxels::generateCubicMesh(int * numCubeVertices, double ** cubeVertices, int * numCubes, int ** cubes, int ** interpolationVertices, double ** interpolationWeights, ObjMesh ** surfaceMesh)
{
  //cout << "Generating cubic mesh..." << endl;

  // create a list of vertices in all voxels
  set<gridPoint> vertices;
  // insert all voxel vertices
  set<voxel>::iterator aVoxel; 
  for (aVoxel = voxels.begin(); aVoxel != voxels.end(); ++aVoxel) // over all voxels
  {
    unsigned int i1,j1,k1;
    i1 = aVoxel->first;
    j1 = aVoxel->second;
    k1 = aVoxel->third;

    vertices.insert(gridPoint(i1,j1,k1));
    vertices.insert(gridPoint(i1+1,j1,k1));
    vertices.insert(gridPoint(i1+1,j1+1,k1));
    vertices.insert(gridPoint(i1,j1+1,k1));

    vertices.insert(gridPoint(i1,j1,k1+1));
    vertices.insert(gridPoint(i1+1,j1,k1+1));
    vertices.insert(gridPoint(i1+1,j1+1,k1+1));
    vertices.insert(gridPoint(i1,j1+1,k1+1));
  } 

  // now, "vertices" contains all voxel vertices with no duplications
  //cout << "Num voxels: " << voxels.size() << " Num voxel vertices: " << vertices.size() << endl; 

  // creates an empty objMesh (for the output surface mesh)
  *surfaceMesh = new ObjMesh();

  // create default group
  (*surfaceMesh)->addGroup("Default");

  // add all voxel vertices into a map, together with their corresponding index (i.e. serial number of a voxel vertex in the set order)
  map<gridPoint,int> vertices2;
  set<gridPoint>:: iterator v; // will run over all voxel vertices

  int position=0;
  *numCubeVertices = vertices.size();
  *cubeVertices = (double*) malloc (sizeof(double) * 3 * vertices.size());
  for (v = vertices.begin(); v != vertices.end(); ++v)
  {
    vertices2.insert(pair<gridPoint,int>(*v,position));
    Vec3d pos = bmin + Vec3d(v->first*inc[0], v->second*inc[1], v->third*inc[2]);
    (*surfaceMesh)->addVertexPosition(pos);

    (*cubeVertices)[3*position+0] = pos[0];
    (*cubeVertices)[3*position+1] = pos[1];
    (*cubeVertices)[3*position+2] = pos[2];

    //cout << "Position " << position << ": " << pos << endl;
    position++;
  } 

  unsigned int index;
  position = 0;
  *numCubes = voxels.size();
  *cubes = (int*) malloc (sizeof(int) * voxels.size() * 8);
  for (aVoxel = voxels.begin(); aVoxel != voxels.end(); ++aVoxel) // over all voxels
  {
    unsigned int i1,j1,k1;
    i1 = aVoxel->first;
    j1 = aVoxel->second;
    k1 = aVoxel->third;

    #define PROCESS_CORNER_SHORT(di,dj,dk)\
    index = (vertices2.find(gridPoint(i1+(di),j1+(dj),k1+(dk))))->second;

    PROCESS_CORNER_SHORT(0,0,0); (*cubes)[8*position+0] = index;
    PROCESS_CORNER_SHORT(1,0,0); (*cubes)[8*position+1] = index;
    PROCESS_CORNER_SHORT(1,1,0); (*cubes)[8*position+2] = index;
    PROCESS_CORNER_SHORT(0,1,0); (*cubes)[8*position+3] = index;
    PROCESS_CORNER_SHORT(0,0,1); (*cubes)[8*position+4] = index;
    PROCESS_CORNER_SHORT(1,0,1); (*cubes)[8*position+5] = index;
    PROCESS_CORNER_SHORT(1,1,1); (*cubes)[8*position+6] = index;
    PROCESS_CORNER_SHORT(0,1,1); (*cubes)[8*position+7] = index;

    position++;
  } 

  // generate the barycentric masks

  // for every vertex of the mesh, find what voxel it is in
  // then, find indices of the vertices of that voxel
  // and compute the barycentric coordinates

  *interpolationVertices = (int*) malloc (sizeof(int) * 8 * objMesh->getNumVertices());
  *interpolationWeights = (double*) malloc (sizeof(double) * 8 * objMesh->getNumVertices());

  for (unsigned int i=0; i < objMesh->getNumVertices(); i++) // over all vertices of the mesh
  {
    Vec3d pos = objMesh->getPosition(i);
    unsigned int i1,j1,k1;

    Vec3d relPos = pos-bmin;

    // find voxel containing 'pos'
    i1 = (unsigned int)(relPos[0] / inc[0]);
    j1 = (unsigned int)(relPos[1] / inc[1]);
    k1 = (unsigned int)(relPos[2] / inc[2]);

    // compute barycentric coordinates
    Vec3d w = pos - (bmin + Vec3d(i1 * inc[0], j1 * inc[1], k1 * inc[2]));
    double alpha = w[0] / inc[0];     
    double beta = w[1] / inc[1];     
    double gamma = w[2] / inc[2];     

    unsigned int c000, c100, c110, c010, c001, c101, c111, c011;
    unsigned int * cArray[8] = { &c000, &c100, &c110, &c010, &c001, &c101, &c111, &c011 };
    int offset[8][3] = { {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}, {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1} };
    for(int j=0; j<8; j++)
    {
      map<gridPoint,int> :: iterator iter = vertices2.find(gridPoint(i1 + offset[j][0], j1 + offset[j][1], k1 + offset[j][2]));
      if (iter != vertices2.end())
        *(cArray[j]) = iter->second;
      else
        *(cArray[j]) = 0; // handle case where vertex is at the boundary of a voxel and round-off may move it to a non-existing voxel (barycentric coordinate is zero in this case)
    }

    //unsigned int c000 = vertices2.find(gridPoint(i1+0,j1+0,k1+0))->second;
    //unsigned int c100 = vertices2.find(gridPoint(i1+1,j1+0,k1+0))->second;
    //unsigned int c110 = vertices2.find(gridPoint(i1+1,j1+1,k1+0))->second;
    //unsigned int c010 = vertices2.find(gridPoint(i1+0,j1+1,k1+0))->second;

    //unsigned int c001 = vertices2.find(gridPoint(i1+0,j1+0,k1+1))->second;
    //unsigned int c101 = vertices2.find(gridPoint(i1+1,j1+0,k1+1))->second;
    //unsigned int c111 = vertices2.find(gridPoint(i1+1,j1+1,k1+1))->second;
    //unsigned int c011 = vertices2.find(gridPoint(i1+0,j1+1,k1+1))->second;

    double f000 = (1-alpha)*(1-beta)*(1-gamma);
    double f100 = (alpha)*(1-beta)*(1-gamma);
    double f110 = (alpha)*(beta)*(1-gamma);
    double f010 = (1-alpha)*(beta)*(1-gamma);

    double f001 = (1-alpha)*(1-beta)*(gamma);
    double f101 = (alpha)*(1-beta)*(gamma);
    double f111 = (alpha)*(beta)*(gamma);
    double f011 = (1-alpha)*(beta)*(gamma);

    (*interpolationVertices)[8*i+0] = c000;
    (*interpolationVertices)[8*i+1] = c100;
    (*interpolationVertices)[8*i+2] = c110;
    (*interpolationVertices)[8*i+3] = c010;
    (*interpolationVertices)[8*i+4] = c001;
    (*interpolationVertices)[8*i+5] = c101;
    (*interpolationVertices)[8*i+6] = c111;
    (*interpolationVertices)[8*i+7] = c011;

    (*interpolationWeights)[8*i+0] = f000;
    (*interpolationWeights)[8*i+1] = f100;
    (*interpolationWeights)[8*i+2] = f110;
    (*interpolationWeights)[8*i+3] = f010;
    (*interpolationWeights)[8*i+4] = f001;
    (*interpolationWeights)[8*i+5] = f101;
    (*interpolationWeights)[8*i+6] = f111;
    (*interpolationWeights)[8*i+7] = f011;
  }

  // by now, surfaceFaces contains a unique list of all surface faces
  // add all faces to the surface obj mesh of the voxel mesh
  set<TopologicalFace,FaceOrder>::iterator face;
  for (face = surfaceFaces.begin(); face != surfaceFaces.end(); ++face) // all surface faces
  {
    int index[4];
    for (int i=0; i<4; i++)
      index[i] = (vertices2.find(face->vertex(i)))->second;

    std::pair< bool, unsigned int > texPos(false,0); // no textures 
    std::pair< bool, unsigned int > normal(false,0); // no normals

    /*
    // triangulate the face into two triangles

    Face newFace1;
    newFace1.addVertex( Vertex( index[0], texPos, normal ) );
    newFace1.addVertex( Vertex( index[1], texPos, normal ) );
    newFace1.addVertex( Vertex( index[2], texPos, normal ) );

    Face newFace2;
    newFace2.addVertex( Vertex( index[2], texPos, normal ) );
    newFace2.addVertex( Vertex( index[3], texPos, normal ) );
    newFace2.addVertex( Vertex( index[0], texPos, normal ) );

    objMesh->addFaceToGroup(newFace1,0);
    objMesh->addFaceToGroup(newFace2,0);
     */

    // make one quad face

    ObjMesh::Face newFace;
    newFace.addVertex( ObjMesh::Vertex( index[0], texPos, normal ) );
    newFace.addVertex( ObjMesh::Vertex( index[1], texPos, normal ) );
    newFace.addVertex( ObjMesh::Vertex( index[2], texPos, normal ) );
    newFace.addVertex( ObjMesh::Vertex( index[3], texPos, normal ) );

    (*surfaceMesh)->addFaceToGroup(newFace,0);
  }

  // search if there already is "default" material; if there is not, add it
  (*surfaceMesh)->addDefaultMaterial();

  (*surfaceMesh)->computeBoundingBox();
}

void ObjMeshOffsetVoxels::generateInterpolationMasks(const string & filenameInterp, const string & inputObjMesh)
{
  cout << "Generating interpolation masks for the external file " << inputObjMesh << endl;

  // create a list of vertices in all voxels
  set<gridPoint> vertices;

  // insert all voxel vertices
  set<voxel>::iterator aVoxel; 
  for (aVoxel = voxels.begin(); aVoxel != voxels.end(); ++aVoxel) // over all voxels
  {
    unsigned int i1,j1,k1;
    i1 = aVoxel->first;
    j1 = aVoxel->second;
    k1 = aVoxel->third;

    vertices.insert(gridPoint(i1,j1,k1));
    vertices.insert(gridPoint(i1+1,j1,k1));
    vertices.insert(gridPoint(i1+1,j1+1,k1));
    vertices.insert(gridPoint(i1,j1+1,k1));

    vertices.insert(gridPoint(i1,j1,k1+1));
    vertices.insert(gridPoint(i1+1,j1,k1+1));
    vertices.insert(gridPoint(i1+1,j1+1,k1+1));
    vertices.insert(gridPoint(i1,j1+1,k1+1));
  } 
  
  // now, vertices contains all voxel vertices with no duplications

  // add all voxel vertices into a map, together with their corresponding index (i.e. serial number of a voxel vertex in the set order)
  map<gridPoint,int> vertices2;
  set<gridPoint>:: iterator v; // will run over all voxel vertices
  int position=0;
  for (v = vertices.begin(); v != vertices.end(); ++v)
  {
    vertices2.insert(pair<gridPoint,int>(*v,position));
    //Vec3d pos = bmin + Vec3d(v->first*inc[0], v->second*inc[1], v->third*inc[2]);
    //cout << "Position " << position << ": " << pos << endl;
    position++;
  } 
  
  // generate the barycentric masks

  cout << "Writing interpolation info to file " << filenameInterp << " ." << endl;

  // open file
  ofstream fout(filenameInterp.c_str());

  if (!fout)
  {
    cout << "Error: could not write to file " << filenameInterp << endl;
    return;
  }

  // for every vertex of the mesh, find what voxel it is in
  // then find indices of the vertices of that voxel
  // and compute the barycentric coordinates

  ObjMesh inputMesh(inputObjMesh);
  
  // will contain all voxels that contain at least one vertex of the external mesh
  set<voxel> visitedVoxels;

  cout << "Processing vertices of the external mesh file..." << endl;
  for (unsigned int i=0; i < inputMesh.getNumVertices(); i++) // over all vertices of the mesh
  {
    if (i % 100 == 0)
      cout << i << " " << flush;

    Vec3d pos = inputMesh.getPosition(i);
    unsigned int i1,j1,k1;
    
    Vec3d relPos = pos-bmin;

    // find voxel containing 'pos'
    i1 = (unsigned int)(relPos[0] / inc[0]);
    j1 = (unsigned int)(relPos[1] / inc[1]);
    k1 = (unsigned int)(relPos[2] / inc[2]);

    // store voxel so that we can later print out a list of visited voxels
    visitedVoxels.insert(voxel(i1,j1,k1));

    // compute barycentric coordinates
    Vec3d w = pos - (bmin + Vec3d(i1 * inc[0], j1 * inc[1], k1 * inc[2]));
    double alpha = w[0] / inc[0];     
    double beta = w[1] / inc[1];     
    double gamma = w[2] / inc[2];     

    map<gridPoint,int> :: iterator voxelVertexEntry;

    voxelVertexEntry = vertices2.find(gridPoint(i1+0,j1+0,k1+0));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 000" << endl;
      return; 
    }
    unsigned int c000 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+1,j1+0,k1+0));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 100" << endl;
      return; 
    }
    unsigned int c100 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+1,j1+1,k1+0));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 110" << endl;
      return; 
    }
    unsigned int c110 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+0,j1+1,k1+0));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 010" << endl;
      return; 
    }
    unsigned int c010 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+0,j1+0,k1+1));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 001" << endl;
      return; 
    }
    unsigned int c001 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+1,j1+0,k1+1));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 101" << endl;
      return; 
    }
    unsigned int c101 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+1,j1+1,k1+1));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 111" << endl;
      return; 
    }
    unsigned int c111 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+0,j1+1,k1+1));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 011" << endl;
      return; 
    }
    unsigned int c011 = voxelVertexEntry->second;

/*
    unsigned int c000 = vertices2.find(gridPoint(i1+0,j1+0,k1+0))->second;
    unsigned int c100 = vertices2.find(gridPoint(i1+1,j1+0,k1+0))->second;
    unsigned int c110 = vertices2.find(gridPoint(i1+1,j1+1,k1+0))->second;
    unsigned int c010 = vertices2.find(gridPoint(i1+0,j1+1,k1+0))->second;

    unsigned int c001 = vertices2.find(gridPoint(i1+0,j1+0,k1+1))->second;
    unsigned int c101 = vertices2.find(gridPoint(i1+1,j1+0,k1+1))->second;
    unsigned int c111 = vertices2.find(gridPoint(i1+1,j1+1,k1+1))->second;
    unsigned int c011 = vertices2.find(gridPoint(i1+0,j1+1,k1+1))->second;
*/
    double f000 = (1-alpha)*(1-beta)*(1-gamma);
    double f100 = (alpha)*(1-beta)*(1-gamma);
    double f110 = (alpha)*(beta)*(1-gamma);
    double f010 = (1-alpha)*(beta)*(1-gamma);

    double f001 = (1-alpha)*(1-beta)*(gamma);
    double f101 = (alpha)*(1-beta)*(gamma);
    double f111 = (alpha)*(beta)*(gamma);
    double f011 = (1-alpha)*(beta)*(gamma);

    fout << i << " ";

    fout << c000 << " " << f000 << " ";
    fout << c100 << " " << f100 << " ";
    fout << c110 << " " << f110 << " ";
    fout << c010 << " " << f010 << " ";

    fout << c001 << " " << f001 << " ";
    fout << c101 << " " << f101 << " ";
    fout << c111 << " " << f111 << " ";
    fout << c011 << " " << f011 << endl;
  }

  fout.close();

  // print out indices of all voxels that contain vertices of the external mesh
  int index=1;
  int lineCounter = 0;
  printf("\nVoxels that contain vertices of the given external mesh:\n");
  for (aVoxel = voxels.begin(); aVoxel != voxels.end(); ++aVoxel) // over all voxels
  {
    unsigned int i1,j1,k1;
    i1 = aVoxel->first;
    j1 = aVoxel->second;
    k1 = aVoxel->third;

    // seek for (i1,j1,k1) in the list of all voxels
    if (visitedVoxels.find(voxel(i1,j1,k1)) != visitedVoxels.end())
    {
      printf("%d,",index);
      lineCounter++;
    }

    if (lineCounter >= 8)
    {
      lineCounter = 0;
      printf("\n");
    }

    index++;
  }
  printf("\n");

  index=1;
  lineCounter = 0;
  printf("\nVoxels that DO NOT contain vertices of the given external mesh:\n");
  for (aVoxel = voxels.begin(); aVoxel != voxels.end(); ++aVoxel) // over all voxels
  {
    unsigned int i1,j1,k1;
    i1 = aVoxel->first;
    j1 = aVoxel->second;
    k1 = aVoxel->third;

    // seek for (i1,j1,k1) in the list of all voxels
    if (visitedVoxels.find(voxel(i1,j1,k1)) == visitedVoxels.end())
    {
      printf("%d,",index);
      lineCounter++;
    }

    if (lineCounter >= 8)
    {
      lineCounter = 0;
      printf("\n");
    }

    index++;
  }
  printf("\n");

  cout << endl << "Total voxels: " << voxels.size() << " Successful termination." << endl;
}

//  generates the normal correction matrix for the vertices from the external file 'inputObjMesh'
void ObjMeshOffsetVoxels::generateNormalCorrectionMatrix(const string filenameCorrectionMatrix, const string inputObjMesh, const string filenameVoxelModalMatrix, const string filenameNormals)
{
  cout << "Generating normal correction matrix  for the external file " << inputObjMesh << endl;

  // create a list of vertices in all voxels
  set<gridPoint> vertices;

  // insert all voxel vertices
  set<voxel>::iterator aVoxel; 
  for (aVoxel = voxels.begin(); aVoxel != voxels.end(); ++aVoxel) // over all voxels
  {
    unsigned int i1,j1,k1;
    i1 = aVoxel->first;
    j1 = aVoxel->second;
    k1 = aVoxel->third;

    vertices.insert(gridPoint(i1,j1,k1));
    vertices.insert(gridPoint(i1+1,j1,k1));
    vertices.insert(gridPoint(i1+1,j1+1,k1));
    vertices.insert(gridPoint(i1,j1+1,k1));

    vertices.insert(gridPoint(i1,j1,k1+1));
    vertices.insert(gridPoint(i1+1,j1,k1+1));
    vertices.insert(gridPoint(i1+1,j1+1,k1+1));
    vertices.insert(gridPoint(i1,j1+1,k1+1));
  } 
  
  // now, vertices contains all voxel vertices with no duplications

  // add all voxel vertices into a map, together with their corresponding index (i.e. serial number of a voxel vertex in the set order)
  map<gridPoint,int> vertices2;
  set<gridPoint>:: iterator v; // will run over all voxel vertices
  int position=0;
  for (v = vertices.begin(); v != vertices.end(); ++v)
  {
    vertices2.insert(pair<gridPoint,int>(*v,position));
    //Vec3d pos = bmin + Vec3d(v->first*inc[0], v->second*inc[1], v->third*inc[2]);
    //cout << "Position " << position << ": " << pos << endl;
    position++;
  } 
  
  // === load the voxel modal matrix
  cout << "Loading the voxel modal matrix " << filenameVoxelModalMatrix << " ." << endl;

  int nVoxel,r;
  double * voxelModalMatrix;
  ReadMatrixFromDisk_((char*)filenameVoxelModalMatrix.c_str(), &nVoxel, &r, &voxelModalMatrix);
  nVoxel /= 3;
  Assert_(nVoxel,vertices.size(),1);

  // === load normals

  FILE * fin;
  OpenFile_((char*)filenameNormals.c_str(),&fin,"r");

  int numNormals;
  if (fscanf(fin,"%d\n",&numNormals) < 1)
    printf("Warning: bad input file syntax. Unable to read the number of normals.\n");

  vector<Vec3d> normals;
  for(int i=0; i<numNormals; i++)
  {
    double nx,ny,nz;
    if (fscanf(fin,"%lf %lf %lf\n",&nx,&ny,&nz) < 3)
      printf("Warning: bad input file syntax. Unable to read normals.\n");
    normals.push_back(Vec3d(nx,ny,nz));
  }

  fclose(fin);

  // === generate the normal correction matrix

  cout << "Loading the external file " << inputObjMesh << " ." << endl;

  ObjMesh inputMesh(inputObjMesh);

  cout << "Generating the normal correction matrix..." << endl;

  int n = inputMesh.getNumVertices();

  Assert_(n, numNormals, 2);

  double * outputMatrix = (double*) malloc (sizeof(double) * 3 * n * r);

  // for every vertex of the mesh, find what voxel it is in
  // then find indices of the vertices of that voxel
  // and compute the barycentric coordinates
  // the assemble the normal matrix correction

  cout << "Processing vertices of the external mesh file..." << endl;
  for (unsigned int i=0; i < inputMesh.getNumVertices(); i++) // over all vertices of the mesh
  {
    if (i % 100 == 0)
      cout << i << " " << flush;

    Vec3d pos = inputMesh.getPosition(i);
    unsigned int i1,j1,k1;
    
    Vec3d relPos = pos-bmin;

    // find voxel containing 'pos'
    i1 = (unsigned int)(relPos[0] / inc[0]);
    j1 = (unsigned int)(relPos[1] / inc[1]);
    k1 = (unsigned int)(relPos[2] / inc[2]);

    // compute barycentric coordinates
    Vec3d w = pos - (bmin + Vec3d(i1 * inc[0], j1 * inc[1], k1 * inc[2]));
    double alpha = w[0] / inc[0];     
    double beta = w[1] / inc[1];     
    double gamma = w[2] / inc[2];     

    // locate voxel vertices
    map<gridPoint,int> :: iterator voxelVertexEntry;

    voxelVertexEntry = vertices2.find(gridPoint(i1+0,j1+0,k1+0));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 000" << endl;
      return; 
    }
    unsigned int c000 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+1,j1+0,k1+0));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 100" << endl;
      return; 
    }
    unsigned int c100 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+1,j1+1,k1+0));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 110" << endl;
      return; 
    }
    unsigned int c110 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+0,j1+1,k1+0));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 010" << endl;
      return; 
    }
    unsigned int c010 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+0,j1+0,k1+1));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 001" << endl;
      return; 
    }
    unsigned int c001 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+1,j1+0,k1+1));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 101" << endl;
      return; 
    }
    unsigned int c101 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+1,j1+1,k1+1));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 111" << endl;
      return; 
    }
    unsigned int c111 = voxelVertexEntry->second;

    voxelVertexEntry = vertices2.find(gridPoint(i1+0,j1+1,k1+1));
    if (voxelVertexEntry == vertices2.end())
    {
      cout << "Error: vertex " << i+1 << " at location " << pos << " doesn't have corner neighbor 011" << endl;
      return; 
    }
    unsigned int c011 = voxelVertexEntry->second;

/*
    unsigned int c000 = vertices2.find(gridPoint(i1+0,j1+0,k1+0))->second;
    unsigned int c100 = vertices2.find(gridPoint(i1+1,j1+0,k1+0))->second;
    unsigned int c110 = vertices2.find(gridPoint(i1+1,j1+1,k1+0))->second;
    unsigned int c010 = vertices2.find(gridPoint(i1+0,j1+1,k1+0))->second;

    unsigned int c001 = vertices2.find(gridPoint(i1+0,j1+0,k1+1))->second;
    unsigned int c101 = vertices2.find(gridPoint(i1+1,j1+0,k1+1))->second;
    unsigned int c111 = vertices2.find(gridPoint(i1+1,j1+1,k1+1))->second;
    unsigned int c011 = vertices2.find(gridPoint(i1+0,j1+1,k1+1))->second;
*/
/*
    double f000 = (1-alpha)*(1-beta)*(1-gamma);
    double f100 = (alpha)*(1-beta)*(1-gamma);
    double f110 = (alpha)*(beta)*(1-gamma);
    double f010 = (1-alpha)*(beta)*(1-gamma);

    double f001 = (1-alpha)*(1-beta)*(gamma);
    double f101 = (alpha)*(1-beta)*(gamma);
    double f111 = (alpha)*(beta)*(gamma);
    double f011 = (1-alpha)*(beta)*(gamma);
*/
    Vec3d gradf000(1.0 / inc[0] * -(1-beta)*(1-gamma), 1.0 / inc[1] * -(1-alpha)*(1-gamma), 1.0 / inc[2] * -(1-alpha)*(1-beta));
    Vec3d gradf100(1.0 / inc[0] * (1-beta)*(1-gamma), 1.0 / inc[1] * -alpha*(1-gamma), 1.0 / inc[2] * -alpha*(1-beta));
    Vec3d gradf110(1.0 / inc[0] * beta*(1-gamma), 1.0 / inc[1] * alpha*(1-gamma), 1.0 / inc[2] * -alpha*beta);
    Vec3d gradf010(1.0 / inc[0] * -beta*(1-gamma), 1.0 / inc[1] * (1-alpha)*(1-gamma), 1.0 / inc[2] * (1-alpha)*-beta);

    Vec3d gradf001(1.0 / inc[0] * -(1-beta)*gamma, 1.0 / inc[1] * -(1-alpha)*gamma, 1.0 / inc[2] * (1-alpha)*(1-beta));
    Vec3d gradf101(1.0 / inc[0] * (1-beta)*gamma, 1.0 / inc[1] * -alpha*gamma, 1.0 / inc[2] * alpha*(1-beta));
    Vec3d gradf111(1.0 / inc[0] * beta*gamma, 1.0 / inc[1] * alpha*gamma, 1.0 / inc[2] * alpha*beta);
    Vec3d gradf011(1.0 / inc[0] * -beta*gamma, 1.0 / inc[1] * (1-alpha)*gamma, 1.0 / inc[2] * (1-alpha)*beta);

    Vec3d normal = normals[i];

    for(int j=0; j<r; j++)
    {
      Vec3d u000(voxelModalMatrix[ELT(3*nVoxel,3*c000+0,j)],voxelModalMatrix[ELT(3*nVoxel,3*c000+1,j)],voxelModalMatrix[ELT(3*nVoxel,3*c000+2,j)]);
      Vec3d u100(voxelModalMatrix[ELT(3*nVoxel,3*c100+0,j)],voxelModalMatrix[ELT(3*nVoxel,3*c100+1,j)],voxelModalMatrix[ELT(3*nVoxel,3*c100+2,j)]);
      Vec3d u110(voxelModalMatrix[ELT(3*nVoxel,3*c110+0,j)],voxelModalMatrix[ELT(3*nVoxel,3*c110+1,j)],voxelModalMatrix[ELT(3*nVoxel,3*c110+2,j)]);
      Vec3d u010(voxelModalMatrix[ELT(3*nVoxel,3*c010+0,j)],voxelModalMatrix[ELT(3*nVoxel,3*c010+1,j)],voxelModalMatrix[ELT(3*nVoxel,3*c010+2,j)]);
      Vec3d u001(voxelModalMatrix[ELT(3*nVoxel,3*c001+0,j)],voxelModalMatrix[ELT(3*nVoxel,3*c001+1,j)],voxelModalMatrix[ELT(3*nVoxel,3*c001+2,j)]);
      Vec3d u101(voxelModalMatrix[ELT(3*nVoxel,3*c101+0,j)],voxelModalMatrix[ELT(3*nVoxel,3*c101+1,j)],voxelModalMatrix[ELT(3*nVoxel,3*c101+2,j)]);
      Vec3d u111(voxelModalMatrix[ELT(3*nVoxel,3*c111+0,j)],voxelModalMatrix[ELT(3*nVoxel,3*c111+1,j)],voxelModalMatrix[ELT(3*nVoxel,3*c111+2,j)]);
      Vec3d u011(voxelModalMatrix[ELT(3*nVoxel,3*c011+0,j)],voxelModalMatrix[ELT(3*nVoxel,3*c011+1,j)],voxelModalMatrix[ELT(3*nVoxel,3*c011+2,j)]);

      Vec3d coef(0,0,0);
      coef += dot(gradf000,normal) * u000;
      coef += dot(gradf100,normal) * u100;
      coef += dot(gradf110,normal) * u110;
      coef += dot(gradf010,normal) * u010;
      coef += dot(gradf001,normal) * u001;
      coef += dot(gradf101,normal) * u101;
      coef += dot(gradf111,normal) * u111;
      coef += dot(gradf011,normal) * u011;
      
      outputMatrix[ELT(3*n, 3*i+0, j)] = coef[0];
      outputMatrix[ELT(3*n, 3*i+1, j)] = coef[1];
      outputMatrix[ELT(3*n, 3*i+2, j)] = coef[2];
    }

  }

  cout << endl;

  WriteMatrixToDisk_((char*)filenameCorrectionMatrix.c_str(), 3*n, r, outputMatrix);
 
  free(outputMatrix);
  free(voxelModalMatrix);
}
