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

#ifndef _OBJMESHORIENTABLE_H_
#define _OBJMESHORIENTABLE_H_

#include "objMesh.h"

/*
  Generates a half-edge datastructure, assuming tha the given obj mesh is orientable.
  Author: Jernej Barbic, 2004
*/

class ObjMeshOrientable
{
public:
  // generates the half-edge datastructure
  // if generateHalfEdges flag is 1 (default), it also generates the half edges (otherwise class is not fully initialized)
  // if numOrientationFlips is not NULL, returns the number of edges that were flipped to orient the surface coherently
  // if the mesh is non-orientable, throws an exception
  ObjMeshOrientable(const std::string & filename, int generateHalfEdges=1, int * numOrientationFlips = NULL, int verbose=0);

  ObjMeshOrientable(ObjMesh * objMesh, int generateHalfEdges=1, int * numOrientationFlips = NULL, int verbose=0);

  ~ObjMeshOrientable();

  // makes an empty structure
  ObjMeshOrientable() {}

  class HalfEdge
  {
    public:
      explicit HalfEdge(const unsigned int & position_g, const unsigned int& startVertex_g, const unsigned int& endVertex_g, const unsigned int& startV_g, const unsigned int& endV_g, const unsigned int groupID_g, const unsigned int& face_g, const int opposite_g, const unsigned int next_g // value of -1 denotes boundary edge const unsigned int next_g
)
      :	position_(position_g), startVertex_(startVertex_g), endVertex_(endVertex_g), 
        startV_(startV_g), endV_(endV_g),
        groupID_(groupID_g),face_(face_g),
        opposite_(opposite_g), next_(next_g) {}

        // accessors for getting global edge position
        unsigned int position() { return position_;}

        // accessors for starting and ending vertices of the edge (global indexing)
        unsigned int startVertex() { return startVertex_; }
        unsigned int endVertex() { return endVertex_; }

        // accessors for starting and ending vertices of the edge (local indexing on the local face)
        unsigned int startV() { return startV_; }
        unsigned int endV() { return endV_; }

        // accessors for the face on the left of the edge
        unsigned int groupID() { return groupID_; }
        unsigned int face() { return face_; }

        // accessors for opposite and next edges
        int opposite() { return opposite_; }
        unsigned int next() { return next_; }

        // mutator for opposite and next edges
        void setOpposite(int opposite_g) { opposite_ = opposite_g; }
        void setNext(unsigned int next_g) { next_ = next_g; }

        // is this edge a boundary edge
        bool isBoundary() { return (opposite_ == -1);}

        void flipOrientation(); // flips orientation of the edge (careful, structure not coherent any more now)

        bool operator== (HalfEdge & halfEdge2) { return (position_ == halfEdge2.position_);} 
        bool operator!= (HalfEdge & halfEdge2) { return (position_ != halfEdge2.position_);} 
 

    protected:
        unsigned int position_; // the global position of the half-edge in the data structure
        unsigned int startVertex_, endVertex_; // global vertex indices
        unsigned int startV_, endV_; // local vertex indices, on the face
        unsigned int groupID_;
        unsigned int face_;
        int opposite_;
        unsigned int next_;
  };
        
protected:
  ObjMesh * objMesh;
  void Init(int generateHalfEdges, int * numOrientationFlips, int verbose);

  std::vector< HalfEdge > halfEdges_;
  std::vector< int > boundaryEdges_;
  unsigned int connectedComponents; // the total number of connected components of the mesh

  bool hasBoundary_; // does the surface have boundary

  std::vector<int> edgesAtVertices_; // for every vertex, contains one half-edge emanating out of it
  std::vector<std::vector<int> > edgesAtFaces_; // for every face, contains one half-edge on this face

  void determineIfSurfaceHasBoundary();

public:
  size_t numHalfEdges() { return halfEdges_.size(); }
  HalfEdge & halfEdge(unsigned int i) { return halfEdges_[i]; }

  // this function is mostly called internally, but can sometimes also be called from the outside
  // returns the number of edges that were flipped to orient the surface coherently
  // (which will be zero if the input mesh already is oriented coherently)
  // if the data structure cannot be generated (non-manifold geometry), returns -1
  int GenerateHalfEdgeDataStructure(int verbose=0); // generates the whole datastructure, assuming the base objMesh class has been initialized

  void CopyHalfEdgeTopologyFrom(ObjMeshOrientable * source); // makes the half-edge topological info equal to that of source

  // returns the opposite halfedge to the given half-edge
  // this function will fail for boundary edges, should always check first with isBoundary()
  HalfEdge & edgeOpposite(HalfEdge & halfedge) { return halfEdges_[halfedge.opposite()]; } 

  // returns the next halfedge to the given half-edge
  HalfEdge & edgeNext(HalfEdge & halfedge) { return halfEdges_[halfedge.next()]; } 

  // returns the previous halfedge to the given half-edge
  // does so by looping around the face (pointers to previous edges are not explicitly stored), so this is slower than edgeNext
  HalfEdge & edgePrevious(HalfEdge & halfedge);

  // loops around the vertex (vertex is defined as the ending position of the halfedge)
  // consists of taking the next edge, then taking the opposite edge
  // if boundary edge encountered, can't take the opposite edge; it this case flag=1 is returned and the edge returned is the boundary edge pointing away from the vertex
  // if taking the opposite edge is possible, the returned edge points into the vertex and flag is set to 0
  // this is effectively looping in the clockwise (negative) orientation
  HalfEdge & loopVertex(HalfEdge & halfedge, int & flag); 

  // returns the the group that contains the given half-edge
  ObjMesh::Group edgeGroup(HalfEdge & halfedge) { return *(objMesh->getGroupHandle(halfedge.groupID())); } 

  // returns the face to the left of the given half-edge
  ObjMesh::Face edgeFace(HalfEdge & halfedge) 
  { const ObjMesh::Group * getGroupHandle = objMesh->getGroupHandle(halfedge.groupID());
    return getGroupHandle->getFace(halfedge.face()); }

  // returns the starting vertex of the given half-edge
  ObjMesh::Vertex edgeStartVertex (HalfEdge & halfedge) 
  { const ObjMesh::Group * getGroupHandle = objMesh->getGroupHandle(halfedge.groupID());
    return (getGroupHandle->getFace(halfedge.face())).getVertex(halfedge.startV()); }

  // returns the ending vertex of the given half-edge
  ObjMesh::Vertex edgeEndVertex (HalfEdge & halfedge) 
  { const ObjMesh::Group * getGroupHandle = objMesh->getGroupHandle(halfedge.groupID());
    return (getGroupHandle->getFace(halfedge.face())).getVertex(halfedge.endV()); }

  unsigned int numConnectedComponents() { return connectedComponents;}

  bool isIsolatedVertex(unsigned int vertex) { return (edgesAtVertices_[vertex] == -1); } // returns true if vertex is isolated
  bool isBoundaryVertex(unsigned int vertex) { return halfEdges_[edgesAtVertices_[vertex]].isBoundary(); } // returns true if vertex is a mesh boundary vertex

  void PrintHalfEdges(); // prints the half-edges out

  ObjMesh * GenerateOrientedMesh(); // generates oriented mesh (same mesh as the input ObjMesh, but oriented consistently)

  // returns some halfedge emanating out of a given vertex (returns always the same edge)
  // in case vertex is a boundary vertex, it will return the edge such that there is no clockwise edge to the given edge around the given vertex
  // this function will fail for isolated vertices; should always check first with isIsolatedVertex()
  HalfEdge & edgeAtVertex( unsigned int vertex ) { return halfEdges_[edgesAtVertices_[vertex]]; }

  // returns some halfedge on the given face (returns always the same edge)
  HalfEdge & edgeAtFace( unsigned int groupID, unsigned int faceID ) { return halfEdges_[edgesAtFaces_[groupID][faceID]]; }

  // returns true if surface has boundary and false if it is closed
  bool hasBoundary() { return hasBoundary_;}

  size_t numBoundaryEdges() { return boundaryEdges_.size(); }
  int boundaryEdge(int i) { return boundaryEdges_[i]; }

  int internalAllocation;
};

#endif

