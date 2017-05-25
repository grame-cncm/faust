#ifndef _OBJMESHGRAPH_H_
#define _OBJMESHGRAPH_H_

/*
   Jernej Barbic, CMU, MIT, USC, 2007-2012

   A graph where the nodes are obj mesh vertices, edges and faces.
   Two nodes are connected if they are adjacent in the mesh.

   There is also a static function, "GenerateVertexGraph", which computes a graph where the nodes
   are obj mesh vertices, and two nodes are connected if they are adjacent in the mesh.
*/

#include "triple.h"
#include "graph.h"
#include "objMesh.h"

class ObjMeshGraph : public Graph
{
public:
  ObjMeshGraph(ObjMesh * objMesh); // will be triangulated if necessary

  int GetVertexID(int meshVertex);
  int GetEdgeID(int meshEdge);
  int GetFaceID(int meshFace);
   
  //void meshID(int graphVertex, int & siteType, int & siteID);
  // converts graph vertex to the integer indices of the particular site
  // sitetpye: 0 = vtx, 1 = edge, 2 = face
  void meshID(int graphVertex, int & siteType, int meshVtxData[3]);

  // converts distance-field style (face, siteIndex) pair to the graph vertex ID
  // siteIndex:
  //  0: vertex0
  //  1: vertex1
  //  2: vertex2
  //  3: edge among 01
  //  4: edge among 12
  //  5: edge among 20
  //  6: the face itself
  int graphID(int faceID, int siteIndex);

  // Creates a graph where the nodes are obj mesh vertices. Two nodes are connected if they are adjacent in the mesh.
  // Face clique:
  // 0: connect every vertex to the next and previous vertex along the face perimeter (but not to other vertices of that face)
  // 1: connect every vertex to all other face vertices
  static Graph * GenerateVertexGraph(const ObjMesh * objMesh, int faceClique=0);

protected:
  int nObj, eObj, fObj;
  std::vector<std::pair<int, int> > meshEdgesVector; // maps each integer identifier to the corresponding edge 
  std::vector<triple<int, int, int> > meshFaceVerticesVector; // for every mesh triangle, gives indices of its vertices
  std::vector<triple<int, int, int> > meshFaceEdgesVector; // for every mesh triangle, gives indices of its edges
  ObjMesh * objMesh;
};

inline int ObjMeshGraph::GetVertexID(int vertex)
{
  return vertex;
}

inline int ObjMeshGraph::GetEdgeID(int edge)
{
  return nObj + edge;
}

inline int ObjMeshGraph::GetFaceID(int face)
{
  return nObj + eObj + face;
}

#endif

