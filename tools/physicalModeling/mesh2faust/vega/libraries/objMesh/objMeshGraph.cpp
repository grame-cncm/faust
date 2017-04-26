#include <map>
#include "objMeshGraph.h"
using namespace std;

ObjMeshGraph::ObjMeshGraph(ObjMesh * objMesh_): objMesh(objMesh_)
{
  if (!(objMesh->isTriangularMesh()))
  {
    printf("Mesh was not triangular. Triangulating..."); fflush(NULL);
    objMesh->triangulate();
    printf(" done\n");
  }

  std::map<std::pair<int, int>, int > meshEdges; // unstructured list of edges, with an integer identifier for each edge

  // create mesh edges
  printf("Building mesh graph edges...\n");
  for(unsigned int i = 0; i < objMesh->getNumGroups(); i++ )
  {
    const ObjMesh::Group * currentGroup = objMesh->getGroupHandle(i);

    std::cout << "  Processing obj group '" << currentGroup->getName() << std::endl;
    std::cout << "  Iterating through group faces..." << std::endl;

    for( unsigned int iFace = 0; iFace < currentGroup->getNumFaces(); ++iFace )
    {
      const ObjMesh::Face face = currentGroup->getFace(iFace); // get face whose number is iFace

      // add to vector of mesh faces
      triple<int,int,int> faceV;
      faceV.first = face.getVertex(0).getPositionIndex();
      faceV.second = face.getVertex(1).getPositionIndex();
      faceV.third = face.getVertex(2).getPositionIndex();
      meshFaceVerticesVector.push_back(faceV);

      // vertexCount() will always be 3
      for ( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
      {
        int vtxA = face.getVertex(iVertex).getPositionIndex();
        int vtxB = face.getVertex((iVertex + 1) % face.getNumVertices()).getPositionIndex();
 
        // ensure that vtxA <= vtxB
        if (vtxA >= vtxB)
        {
          int buffer = vtxA;
          vtxA = vtxB;
          vtxB = buffer;
        }
 
        meshEdges.insert(make_pair(make_pair(vtxA, vtxB), 0));
      }
    }
  }

  // create vector of mesh edges
  for(map<pair<int,int>, int > :: iterator iter = meshEdges.begin();
      iter != meshEdges.end(); iter++)
  {
    meshEdgesVector.push_back(iter->first);
  }

  nObj = objMesh->getNumVertices();
  eObj = meshEdges.size();
  fObj = objMesh->getNumFaces();

  numVertices = nObj + eObj + fObj;

  // add edge indices to the mesh edge datastructure
  int numMeshEdges = 0;
  for(map<pair<int,int>, int> :: iterator iter = meshEdges.begin();
      iter != meshEdges.end(); iter++)
  {
    iter->second = numMeshEdges;
    numMeshEdges++; 
  }

  // build graph adjacency
  int faceIndex = 0;
  printf("Building mesh graph adjacency...\n");
  for(unsigned int i = 0; i < objMesh->getNumGroups(); i++ )
  {
    const ObjMesh::Group * currentGroup = objMesh->getGroupHandle(i);

    std::cout << "  Processing obj group '" << currentGroup->getName() << std::endl;
    std::cout << "  Iterating through group faces..." << std::endl;

    for( unsigned int iFace = 0; iFace < currentGroup->getNumFaces(); ++iFace )
    {
      const ObjMesh::Face face = currentGroup->getFace(iFace); // get face whose number is iFace

      // every vtx is adjacent to its face
      for ( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
      {
        int vtx = face.getVertex(iVertex).getPositionIndex();
        edges.insert(make_pair(GetVertexID(vtx), GetFaceID(faceIndex)));
      }

      // every edge is adjacent to its face
      int edgeIDs[3];
      for ( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
      {
        int vtxA = face.getVertex(iVertex).getPositionIndex();
        int vtxB = face.getVertex((iVertex + 1) % face.getNumVertices()).getPositionIndex();

        // ensure vtxA <= vtxB
        if (vtxA >= vtxB)
        {
          int buffer = vtxA;
          vtxA = vtxB;
          vtxB = buffer;
        }

        map<pair<int, int>, int > :: iterator iter = meshEdges.find(make_pair(vtxA, vtxB));
        if (iter == meshEdges.end())
        {
          printf("Sanity check error: vtxA=%d vtxB=%d.\n",vtxA,vtxB);
          exit(1);
        }
        int edgeID = iter->second;
        edgeIDs[iVertex] = edgeID;
        edges.insert(make_pair(GetEdgeID(edgeID), GetFaceID(faceIndex)));
      }

      meshFaceEdgesVector.push_back(triple<int,int,int> (edgeIDs[0], edgeIDs[1], edgeIDs[2]));

      faceIndex++;
    }
  }

  // every edge is adjacent to its vertices
  for(map<pair<int,int>, int > :: iterator iter = meshEdges.begin();
      iter != meshEdges.end(); iter++)
  {
    edges.insert(make_pair(GetVertexID(iter->first.first), GetEdgeID(iter->second)));
    edges.insert(make_pair(GetVertexID(iter->first.second), GetEdgeID(iter->second)));
  }

  numEdges = edges.size();

  printf("Graph generated.\n");
  printf("Mesh vertices: %d\n", nObj); 
  printf("Mesh edges: %d\n", eObj); 
  printf("Mesh faces: %d\n", fObj); 

  BuildVertexNeighbors();
}

void ObjMeshGraph::meshID(int graphVertex, int & siteType, int meshVtxData[3])
{
  if (graphVertex < nObj)
  {
    siteType = 0;
    meshVtxData[0] = graphVertex;
  }
  else
  if (graphVertex < nObj + eObj)
  {
    siteType = 1;
    int edgeID = graphVertex - nObj;
    pair<int,int> edge = meshEdgesVector[edgeID];
    meshVtxData[0] = edge.first;
    meshVtxData[1] = edge.second;
  }
  else
  {
    siteType = 2;
    int faceID = graphVertex - nObj - eObj;
    triple<int,int,int> face = meshFaceVerticesVector[faceID];
    meshVtxData[0] = face.first;
    meshVtxData[1] = face.second;
    meshVtxData[2] = face.third;
  }
}

int ObjMeshGraph::graphID(int faceID, int siteIndex)
{
  //  0: vertex0
  //  1: vertex1
  //  2: vertex2
  //  3: edge among 01
  //  4: edge among 12
  //  5: edge among 20
  //  6: the face itself

  int graphVertex = 0;
  switch(siteIndex)
  {
    case 0:
      graphVertex = meshFaceVerticesVector[faceID].first;
    break;

    case 1:
      graphVertex = meshFaceVerticesVector[faceID].second;
    break;

    case 2:
      graphVertex = meshFaceVerticesVector[faceID].third;
    break;

    case 3:
      graphVertex = nObj + meshFaceEdgesVector[faceID].first;
    break;

    case 4:
      graphVertex = nObj + meshFaceEdgesVector[faceID].second;
    break;

    case 5:
      graphVertex = nObj + meshFaceEdgesVector[faceID].third;
    break;

    case 6:
      graphVertex = nObj + eObj + faceID;
    break;
  }

  if (graphVertex > numVertices)
  {
    printf("Error: incorrect graph vertex (%d). faceID=%d site:%d\n", 
      graphVertex, faceID, siteIndex);
  }

  return graphVertex;
}

Graph * ObjMeshGraph::GenerateVertexGraph(const ObjMesh * objMesh, int faceClique)
{
  // Generate springs:
  typedef pair<int,int> edge;
  set<edge> edgeSet;
  #define SORTED(i,j) ( (i) <= (j) ? make_pair((i),(j)) : make_pair((j),(i)) )

  for(unsigned int i=0; i < objMesh->getNumGroups(); i++) // over all groups
  {
    const ObjMesh::Group * group = objMesh->getGroupHandle(i);
    for (unsigned int j=0; j < group->getNumFaces(); j++) // over all faces
    {
      const ObjMesh::Face * face = group->getFaceHandle(j);
      if (face->getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than 3 vertices.\n");
        continue;
      }

      unsigned int faceDegree = face->getNumVertices();

      // get the vertices
      vector<ObjMesh::Vertex> vertices;
      for(unsigned int k=0; k<faceDegree; k++)
        vertices.push_back(face->getVertex(k));

      // create edges
      if (faceClique)
      {
        for(unsigned int k=0; k<faceDegree; k++)
          for(unsigned int l=k+1; l<faceDegree; l++)
            edgeSet.insert(SORTED(vertices[k].getPositionIndex(), vertices[l].getPositionIndex()));
      }
      else
        for(unsigned int k=0; k<faceDegree; k++)
          edgeSet.insert(SORTED(vertices[k].getPositionIndex(), vertices[(k+1) % faceDegree].getPositionIndex()));
    }
  }

  int numEdges = edgeSet.size();
  int * edges = (int*) malloc (sizeof(int) * 2 * numEdges);
  int count = 0;
  for(set<edge> :: iterator iter = edgeSet.begin(); iter != edgeSet.end(); iter++)
  {
    edges[2*count+0] = iter->first;
    edges[2*count+1] = iter->second;
    count++;
  }

  Graph * graph  = new Graph(objMesh->getNumVertices(), numEdges, edges);

  free(edges);

  return graph;

  #undef SORTED
}

