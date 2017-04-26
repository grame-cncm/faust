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

#include "float.h"
#include <vector>
#include <set>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
using namespace std;
#include "objMeshOrientable.h"

/*
  Generates a half edge datastructure, assuming tha the given obj mesh is orientable.
  Author: Jernej Barbic, 2004
*/

void ObjMeshOrientable::HalfEdge::flipOrientation()
{
  int buffer = startVertex_;
  startVertex_ = endVertex_;
  endVertex_ = buffer;
}

ObjMeshOrientable::~ObjMeshOrientable()
{
  if (internalAllocation)
    delete(objMesh);
}

ObjMeshOrientable::ObjMeshOrientable(const std::string & filename, int generateHalfEdges, int * numOrientationFlips_, int verbose)
{
  internalAllocation = 1;
  objMesh = new ObjMesh(filename, ObjMesh::ASCII, verbose);
  Init(generateHalfEdges, numOrientationFlips_, verbose);
}

ObjMeshOrientable::ObjMeshOrientable(ObjMesh * objMesh, int generateHalfEdges, int * numOrientationFlips_, int verbose)
{
  internalAllocation = 0;
  this->objMesh = objMesh;
  Init(generateHalfEdges, numOrientationFlips_, verbose);
}

void ObjMeshOrientable::Init(int generateHalfEdges, int * numOrientationFlips_, int verbose)
{
  if (generateHalfEdges)
  {
    // TODO: culprit
    int numOrientationFlips = GenerateHalfEdgeDataStructure(verbose);

    if (numOrientationFlips_ != NULL)
      *numOrientationFlips_ = numOrientationFlips;

    if (numOrientationFlips < 0)
      throw 1;
  }
}

void ObjMeshOrientable::PrintHalfEdges()
{
  for (unsigned int i=0; i<halfEdges_.size(); i++)
  {
    cout << "Half edge "<< i << " :" << endl;
    cout << "  Opposite edge: " << halfEdges_[i].opposite() << endl;
    cout << "  Next edge: " << halfEdges_[i].next() << endl;
    cout << "  Group: " << halfEdges_[i].groupID() << endl;
    cout << "  Face: " << halfEdges_[i].face() << endl;
    cout << "  Start vertex: " << halfEdges_[i].startVertex() << endl;
    cout << "  End vertex: " << halfEdges_[i].endVertex() << endl;
    cout << "  Start vertex (local): " << halfEdges_[i].startV() << endl;
    cout << "  End vertex (local): " << halfEdges_[i].endV() << endl;
    cout << "  Is boundary: " << halfEdges_[i].isBoundary() << endl;
  }
}

// returns the number of edges flipped
int ObjMeshOrientable::GenerateHalfEdgeDataStructure(int verbose)
{
  if (verbose)
    std::cout << "Building the half edge data structure..." << std::endl;

  // Step 1: iterate over all faces
  // for each face, add all the edges onto the list of half-edges

  if (verbose)
    std::cout << "Step 1: Generating the list of half edges..." << std::endl;

  //typedef std::vector<ObjMesh::Group> SGroup;

  int coutCounter = 0;

  for(unsigned int i = 0; i < objMesh->getNumGroups(); i++ )
  {
    const ObjMesh::Group * currentGroup = objMesh->getGroupHandle(i);

    if (verbose)
    {
      std::cout << "  Processing obj group '" << currentGroup->getName() << std::endl;
      std::cout << "  Iterating through group faces..." << std::endl;
    }

    for( unsigned int iFace = 0; iFace < currentGroup->getNumFaces(); ++iFace )
    {
      ObjMesh::Face face = currentGroup->getFace(iFace); // get face whose number is iFace

      if (coutCounter < 100)
      {
        if (verbose)
          std::cout << face.getNumVertices() ;
        coutCounter++;
      }
      if (coutCounter == 100)
      {
        if (verbose)
          cout << "...[and more]";
        coutCounter++;
      }

      unsigned int edgesSoFar = halfEdges_.size();

      for ( unsigned int iVertex = 0; iVertex < face.getNumVertices(); ++iVertex )
      {
        // create a half edge for each edge, store -1 for half-edge adjacent edge for now
        // index vertices starting from 0
        int nextEdge = edgesSoFar + ((iVertex + 1) % face.getNumVertices());
        HalfEdge halfEdge(edgesSoFar + iVertex, face.getVertex(iVertex).getPositionIndex(), face.getVertex((iVertex + 1) % face.getNumVertices()).getPositionIndex(), iVertex, (iVertex + 1) % face.getNumVertices(), i, iFace, -1, nextEdge);

        halfEdges_.push_back(halfEdge);
      }
    }
    if (verbose)
      std::cout << std::endl;
  }

/*
  for (unsigned int i=0; i<halfEdges_.size(); i++)
  {
    cout << "Half edge "<< i << " :" << endl;
    cout << "  Opposite edge: " << halfEdges_[i].opposite() << endl;
    cout << "  Next edge: " << halfEdges_[i].next() << endl;
    cout << "  Group: " << halfEdges_[i].groupID() << endl;
    cout << "  Face: " << halfEdges_[i].face() << endl;
    cout << "  Start vertex: " << halfEdges_[i].startVertex() << endl;
    cout << "  End vertex: " << halfEdges_[i].endVertex() << endl;
    cout << "  Start vertex (local): " << halfEdges_[i].startV() << endl;
    cout << "  End vertex (local): " << halfEdges_[i].endV() << endl;
    cout << "  Is boundary: " << halfEdges_[i].isBoundary() << endl;
  }
*/

  // Step 2: build correspondence among half-dges
  // for each half-edge, search for the opposite half-edge, if it exists

  if (verbose)
  {
    std::cout << "Step 2: Building correspondence among half-edges..." << std::endl;
    std::cout << "Boundary edges: ";
  }

  // insert all edges into a binary tree

  typedef std::multimap<std::pair< unsigned int, unsigned int > , unsigned int> BinaryTree;
  BinaryTree edges;

  for (unsigned int i=0; i < halfEdges_.size(); i++)
  {
    int vertex1 = halfEdges_[i].startVertex();
    int vertex2 = halfEdges_[i].endVertex();

    if (vertex1 == vertex2)
    {
      if (verbose)
      {
        std::cout << "Error: encountered a degenerated edge with equal starting and ending vertex." << std::endl;
        std::cout << "  Group:" << halfEdges_[i].groupID() << "  Face #: " << halfEdges_[i].face() << "Vertex ID: " << vertex1 << std::endl;
      }
      return -1;
    }

    if (vertex1 > vertex2) // swap
    {
      int buffer = vertex1;
      vertex1 = vertex2;
      vertex2 = buffer;
    }

    std::pair<unsigned int, unsigned int> vertices(vertex1,vertex2);
    edges.insert(std::make_pair(vertices,i));
  }

  // retrieve one by one and build correspondence
  for (unsigned int i=0; i < halfEdges_.size(); i++)
  {
    int vertex1 = halfEdges_[i].startVertex();
    int vertex2 = halfEdges_[i].endVertex();

    if (vertex1 > vertex2) // swap
    {
      int buffer = vertex1;
      vertex1 = vertex2;
      vertex2 = buffer;
    }

    std::pair<unsigned int, unsigned int> vertices(vertex1,vertex2);

    // search for the edge

    int hits = 0;
    int candidates = 0;
    BinaryTree::iterator pos;
    for (pos = edges.lower_bound(vertices); pos != edges.upper_bound(vertices); ++pos)
    {
      candidates++;
      // check if we found ourselves
      if (pos->second != i)
      {
        // not ourselves
        halfEdges_[i].setOpposite(pos->second);
        hits++;
      }
    }

    if (candidates >= 3)
    {
      if (verbose)
        std::cout << "Error: encountered an edge that appears in more than two triangles. Geometry is non-manifold. Exiting." << std::endl;
      int faceNum = halfEdges_[i].face();
      if (verbose)
      {
        std::cout << "  Group:" << halfEdges_[i].groupID() << std::endl << "  Face #: " << faceNum << std::endl;
        std::cout << "  Edge: " << vertex1 << " " << vertex2 << std::endl;
        std::cout << "  Vertices: " << objMesh->getPosition(vertex1) << " " << objMesh->getPosition(vertex2) << std::endl;
      }
      return -1;
    }

    if (hits == 0) // boundary edge
    {
      //std::cout << "B";
      if (verbose)
        std::cout << "B(" << vertex1 << "," << vertex2 << ") ";
      boundaryEdges_.push_back(i);
    }
  }

  if (verbose)
    std::cout << " total: " << boundaryEdges_.size() << std::endl;

/*
  for (unsigned int i=0; i<halfEdges_.size(); i++)
  {
    cout << "Half edge "<< i << " :" << endl;
    cout << "  Opposite edge: " << halfEdges_[i].opposite() << endl;
    cout << "  Next edge: " << halfEdges_[i].next() << endl;
    cout << "  Group: " << halfEdges_[i].groupID() << endl;
    cout << "  Face: " << halfEdges_[i].face() << endl;
    cout << "  Start vertex: " << halfEdges_[i].startVertex() << endl;
    cout << "  End vertex: " << halfEdges_[i].endVertex() << endl;
    cout << "  Start vertex (local): " << halfEdges_[i].startV() << endl;
    cout << "  End vertex (local): " << halfEdges_[i].endV() << endl;
    cout << "  Is boundary: " << halfEdges_[i].isBoundary() << endl;
  }
*/
  // now, each half-edge knows its mirror edge, but orientations of faces might be inconsistent

  // orient all half-edges consistently
  if (verbose)
    std::cout << "Step 3: Attempting to orient the faces coherently..." << std::endl;

  // generate marks for all the edges
  std::vector<int> marks(halfEdges_.size(), 0);

  // initialize queue
  std::set<int> queue;

  connectedComponents = 0;
  int numOrientationFlips = 0;

  while(1) // breakable
  {
    // find the first un-marked edge and queue it
    unsigned int unmarkedEdge;
    for (unmarkedEdge = 0; unmarkedEdge < halfEdges_.size(); unmarkedEdge++)
    {
      if (marks[unmarkedEdge] == 0)
        break; // found an unmarked edge
    }

    if (unmarkedEdge == halfEdges_.size()) // no unmarked edge was found
    {
      break; // out of while; we are done
    }
    else
    {
      if (verbose)
        cout << "Found a new connected component. Seed half-edge is: " << unmarkedEdge << endl;
      connectedComponents++;
      queue.insert(unmarkedEdge);

      while(queue.size() > 0)
      {
        int edge = *(queue.begin());
        queue.erase(queue.begin());

        //std::cout << "Retrieved edge from queue: " << edge << " Queue size: " << queue.size() << std::endl;
        //cout << "The edge is boundary: " << halfEdges_[edge].isBoundary() << endl;

        //std::cout << "Marking all the edges on this face: ";
        // first, mark all the edges on this face as visited
        int loop = edge;
        do
        {
          marks[loop] = 1;
          //std::cout << loop << " ";
          loop = halfEdges_[loop].next();
        }
        while (loop != edge);
        //std::cout << std::endl;

        // check if edge is consistent with the opposite edge orientation
        // careful: edge might be on the boundary
        // find a non-boundary edge on the same face (if it exists)
        //std::cout << "Seeking for a non-boundary edge on this face...";
        loop = edge;
        int exitFlag = 0;

        while ((halfEdges_[loop].isBoundary()) && (exitFlag == 0))
        {
          //cout << loop << " ";
          loop = halfEdges_[loop].next();
          if (loop == edge) // all edges are boundary
            exitFlag = 1;
        }

        if (exitFlag == 1) // all edges are boundary; this is an isolated face
        {
          if (verbose)
            cout << "Encountered an isolated face." << endl;
          //cout << "none found." << endl;
          continue; // no need to queue anything or flip anything, this was an isolated face
          // also, this case can only happen during the first iteration of the while loop, which will also be the last one
        }

        edge = loop; // now, edge is a non-boundary halfedge

        //std::cout << "found non-boundary edge: " << edge << std::endl;
        //std::cout << "opposite edge is: " << halfEdges_[edge].opposite() << std::endl;

        bool orientationFlipNecessary = (marks[halfEdges_[edge].opposite()] == 1) && (halfEdges_[edge].startVertex() == (edgeOpposite(halfEdges_[edge])).startVertex());

        //std::cout << "Orientation flip necessary for this face: " << orientationFlipNecessary << std::endl;

        if (orientationFlipNecessary)
        {
          // flip all edges along this face
          //cout << "Orientation flip" << endl;
          numOrientationFlips++;
          loop = edge;
          int cache = 0;
          do
          {
            int nextO = halfEdges_[loop].next();
            halfEdges_[loop].setNext(cache);
            cache = loop;
            halfEdges_[loop].flipOrientation(); // flip orientation
            loop = nextO;
          }
          while (loop != edge);
          halfEdges_[loop].setNext(cache);

          int groupID = halfEdges_[loop].groupID();
          int faceID = halfEdges_[loop].face();

          ObjMesh::Group * currentGroup = (ObjMesh::Group*) objMesh->getGroupHandle(groupID);

          if (verbose)
            currentGroup->getFace(faceID).printVertices();

          currentGroup->reverseFace(faceID);

          if (verbose)
            currentGroup->getFace(faceID).printVertices();
        }

        // check if new orientation is consistent eveywhere along the face
        // if not, surface is not orientable
        // at the same time, queue the opposite edges if they are not marked already
        loop = edge;
        do
        {
          if (!halfEdges_[loop].isBoundary()) // skip boundary edges
          {
            // if opposite unmarked, queue the opposite edge
            if (marks[halfEdges_[loop].opposite()] == 0)
            {
              queue.insert(halfEdges_[loop].opposite());
              //marks[halfEdges_[loop].opposite()] = 1; // JNB, 2008
              //std::cout << "visiting edge: " << loop << " pushing opposite: " << halfEdges_[loop].opposite() << std::endl;
            }
            else
            {
              // opposite edge is marked as already visited
              // if orientation consistent, do nothing
              // if orientation not consistent, surface is not orientable

              bool orientationConsistent = (halfEdges_[loop].startVertex() == (edgeOpposite(halfEdges_[loop])).endVertex());

              //std::cout << "visiting edge: " << loop << " opposite marked " << std::endl;

              if (!orientationConsistent)
              {
                if (verbose)
                  std::cout << "Error: surface is non-orientable. Offending edge: [" << halfEdges_[loop].startVertex() << "," << halfEdges_[loop].endVertex() << "]" << std::endl;
                return -1;
              }
            }
          }
          loop = halfEdges_[loop].next();
        }
        while (loop != edge);

      }
    }
  } // end of while

  if (verbose)
    printf("Consistent orientation generated. Performed %d orientation flips.\n", numOrientationFlips);

  //PrintHalfEdges();

  // step 4: for every vertex, find a half-edge emanating out of it
  if (verbose)
  {
    std::cout << "Step 4: For every vertex, caching a half-edge emanating out of it..." << std::endl;
    std::cout << "        For every face, caching a half-edge on it..." << std::endl;
  }

  for (unsigned int i=0; i< objMesh->getNumVertices(); i++)
    edgesAtVertices_.push_back(-1); // value of -1 corresponds to no edge (i.e. isolated vertex)

  for (unsigned int i=0; i < halfEdges_.size(); i++)
  {
    //cout << i << " " << halfEdges_[i].startVertex() << " " << halfEdges_[i].endVertex() << endl;
    edgesAtVertices_[halfEdges_[i].endVertex()] = i;
  }

  // if vertex is on the boundary, rotate the edge until it is an incoming boundary edge
  // rotate edge until it is either on the boundary, or we come around to the same edge
  int numIsolatedVertices = 0;
  for (unsigned int i=0; i < objMesh->getNumVertices(); i++)
  {
    if (isIsolatedVertex(i))
    {
      numIsolatedVertices++;
      continue;
    }
    HalfEdge * loop = &edgeAtVertex(i);
    HalfEdge * start = loop;
    do
    {
      if (loop->isBoundary())
      {
        // set the edge to the current edge
        edgesAtVertices_[i] = loop->position();
        break;
      }
      loop = &edgePrevious(edgeOpposite(*loop));
    }
    while (*loop != *start);
    // if we came around, no need to change edgeAtVertices[i]
  }

  if (numIsolatedVertices > 0)
    if (verbose)
      printf("Warning: mesh has %d isolated vertices.\n", numIsolatedVertices);

  // build the cache for faces, first reset to -1
  for (unsigned int i=0; i < objMesh->getNumGroups(); i++)
  {
    const ObjMesh::Group * currentGroup = objMesh->getGroupHandle(i);
    std::vector<int> dataForThisGroup;
    dataForThisGroup.clear();
    for (unsigned int j=0; j < currentGroup->getNumFaces(); j++)
    {
      dataForThisGroup.push_back(-1);
    }
    edgesAtFaces_.push_back(dataForThisGroup);
  }
  for (unsigned int i=0; i < halfEdges_.size(); i++)
    edgesAtFaces_[halfEdges_[i].groupID()][halfEdges_[i].face()] = i;

  // sanity check: none of the face entries should be -1
  for (unsigned int i=0; i < objMesh->getNumGroups(); i++)
  {
    const ObjMesh::Group * currentGroup = objMesh->getGroupHandle(i);
    for (unsigned int j=0; j < currentGroup->getNumFaces(); j++)
      if (edgesAtFaces_[i][j] == -1)
      {
        if (verbose)
          cout << "Warning: face on group " << i << "(" << currentGroup->getName() << "), position " << j << " has no edges." << endl;
      }
  }

  determineIfSurfaceHasBoundary();

  // testing: previous edge capability
  /*
  cout << "Testing previous edge capability..." << endl;
  for (unsigned int i=0; i < halfEdges_.size(); i++)
  {
    cout << i << ": " << edgePrevious(halfEdges_[i]).position() << endl;
  }

  // testing: print out associated edges for every vertex
  for (unsigned int i=0; i < vertexPositions_.size(); i++)
  {
    cout << "Halfedge into vertex " << i << ": " << edgeAtVertex(i).position() << endl;
  }

  // testing: print out associated edges for every face
  for (unsigned int i=0; i < groups_.size(); i++)
    for (unsigned int j=0; j < groups_[i].getNumFaces(); j++)
    {
      cout << "Halfedge on face " << i << " " << j << ": " << edgeAtFace(i,j).position() << endl;
    }

  // testing: loop around every vertex
  for (unsigned int i=0; i < vertexPositions_.size(); i++)
  {
    cout << "Looping around vertex " << i << ":";
    int flag = 0;
    HalfEdge * start = &edgeAtVertex(i);
    HalfEdge * loop = start;
    do
    {
      cout << loop->position() << " ";

      if (flag != 0) // boundary edge, exit the loop
      {
        cout << " B";
        break;
      }
      loop = &loopVertex(*loop,flag);
    }
    while (loop->position() != start->position());

    cout << endl;
  }
  */

  if (verbose)
  {
    std::cout << "Half-edge datastructure constructed successfully." << std::endl;
    std::cout << "Statistics: " << std::endl;
    std::cout << "  Half-edges: " << halfEdges_.size() << std::endl;
    std::cout << "  Boundary half-edges: " << boundaryEdges_.size() << std::endl;
    std::cout << "  Connected components: " << connectedComponents << std::endl;
  }

  return numOrientationFlips;
}

// returns the previous halfedge to the given half-edge
// does so by looping around the face (pointers to previous edges are not explicitly stored), so this is slower than edgeNext
ObjMeshOrientable::HalfEdge & ObjMeshOrientable::edgePrevious ( HalfEdge & halfedge )
{
  HalfEdge * loop = &halfedge;
  while (edgeNext(*loop) != halfedge)
    loop = &(edgeNext(*loop));

  HalfEdge & prevEdge = *loop;

  return prevEdge;
}

// loops around the vertex (vertex is defined as the ending position of the halfedge)
// consists of taking the next edge, then taking the opposite edge
// if boundary edge encountered, can't take the opposite edge; it this case flag=1 is returned
//     and the edge returned is the boundary edge pointing away from the vertex
// if taking the opposite edge is possible, the returned edge points into the vertex and flag is set to 0
ObjMeshOrientable::HalfEdge & ObjMeshOrientable::loopVertex(HalfEdge & halfedge, int & flag)
{
  HalfEdge * loop = &halfedge;
  loop = &(edgeNext(*loop));

  if (loop->isBoundary())
  {
    flag = 1;
    // return boundary edge pointing away from the vertex (there is no corresponding edge pointing into the vertex)
    HalfEdge & result = *loop;
    return result;
  }
  else
  {
    flag = 0;
    loop = &(edgeOpposite(*loop));
    // return edge pointing into the vertex
    HalfEdge & result = *loop;
    return result;
  }
}

void ObjMeshOrientable::determineIfSurfaceHasBoundary()
{
  for (unsigned int i=0; i < halfEdges_.size(); i++)
  {
    if (halfEdges_[i].isBoundary())
    {
      hasBoundary_ = true;
      return;
    }
  }

  hasBoundary_ = false;
}

void ObjMeshOrientable::CopyHalfEdgeTopologyFrom(ObjMeshOrientable * source) // makes the half-edge topological info equal to that of source
{

  halfEdges_ = source->halfEdges_;
  boundaryEdges_ = source->boundaryEdges_;
  connectedComponents = source->connectedComponents;
  edgesAtVertices_ = source->edgesAtVertices_;
  edgesAtFaces_ = source->edgesAtFaces_;
  hasBoundary_ = source->hasBoundary_;
}

ObjMesh * ObjMeshOrientable::GenerateOrientedMesh()
{
  ObjMesh * outputObjMesh = new ObjMesh(*objMesh);

  for(unsigned int i=0; i < outputObjMesh->getNumGroups(); i++) // over all groups
  {
    ObjMesh::Group * groupHandle = (ObjMesh::Group*) outputObjMesh->getGroupHandle(i);
    for (unsigned int j=0; j < groupHandle->getNumFaces(); j++) // over all faces
    {
      const ObjMesh::Face * face = groupHandle->getFaceHandle(j);
      if (face->getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than 3 vertices.\n");
        continue;
      }

      HalfEdge edge = edgeAtFace(i, j);

      // loop until edge is first edge
      unsigned int startPosition = face->getVertex(0).getPositionIndex();
      while (edgeStartVertex(edge).getPositionIndex() != startPosition)
        edge = edgeNext(edge);

      // reverse the face if not correctly oriented
      if (edgeEndVertex(edge).getPositionIndex() != face->getVertex(1).getPositionIndex())
        groupHandle->reverseFace(j);
    }
  }

  return outputObjMesh;
}
