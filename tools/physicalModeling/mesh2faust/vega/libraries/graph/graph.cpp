/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "graph" library , Copyright (C) 2016 USC                              *
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

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrixIO.h"
#include "graph.h"
using namespace std;

Graph::Graph() 
{ 
  numVertices = 0; 
  numEdges = 0; 
}

Graph::Graph(const Graph & graph) 
{
  (*this) = graph;
}

Graph & Graph::operator=(const Graph & graph) 
{
  numVertices = graph.numVertices;
  numEdges = graph.numEdges;
  edges = graph.edges;
  vertexNeighbors = graph.vertexNeighbors;
  vertexNeighborsVector = graph.vertexNeighborsVector;
  return *this;
}

Graph::~Graph()
{
}

Graph::Graph(int numVertices_, int numEdges_, int * edges_, int sortEdgeVertices): numVertices(numVertices_), numEdges(numEdges_)
{
  //printf("num vertices: %d\n", numVertices);
  for(int i=0; i<numEdges; i++)
  {
    //printf("Edge: %d %d\n", edges_[2*i+0], edges_[2*i+1]);
    if (sortEdgeVertices)
    {
      // keep the two indices in each edge sorted
      if (edges_[2*i+0] < edges_[2*i+1])
        edges.insert(make_pair(edges_[2*i+0], edges_[2*i+1])); 
      else
        edges.insert(make_pair(edges_[2*i+1], edges_[2*i+0])); 
    }
    else
      edges.insert(make_pair(edges_[2*i+0], edges_[2*i+1])); 
  }

  BuildVertexNeighbors();
}

Graph::Graph(const char * filename, int sortEdgeVertices)
{
  FILE * fin;
  OpenFile_(filename, &fin, "r");
  int code = fscanf(fin, "%d %d\n", &numVertices, &numEdges);
  if (code != 2)
    throw 1;

  //printf("num vertices: %d\n", numVertices);
  for(int i=0; i<numEdges; i++)
  {
    int vtxA, vtxB;
    int code = fscanf(fin, "%d %d\n", &vtxA, &vtxB);
    if (code != 2)
      throw 2;

    //printf("Edge: %d %d\n", vtxA, vtxB);
    // keep the two indices in each edge sorted
    if (sortEdgeVertices)
    {
      if (vtxA < vtxB)
        edges.insert(make_pair(vtxA, vtxB));
      else
        edges.insert(make_pair(vtxB, vtxA));
    }
    else
      edges.insert(make_pair(vtxA, vtxB));
  }

  fclose(fin);

  BuildVertexNeighbors();
}

void Graph::Save(const char * filename)
{
  FILE * fout;
  OpenFile_(filename, &fout, "w");
  fprintf(fout, "%d %d\n", numVertices, numEdges);

  for(set<pair<int, int> > :: iterator iter = edges.begin(); iter != edges.end(); iter++)
  {
    int vtxA = iter->first;
    int vtxB = iter->second;
    fprintf(fout, "%d %d\n", vtxA, vtxB);
  }

  fclose(fout);
}

void Graph::BuildVertexNeighbors()
{
  vertexNeighbors.clear();

  //printf("Building vertex neighbors.\n");
  for(int i=0; i<numVertices; i++)
    vertexNeighbors.push_back(map<int, int>());

  for(set<pair<int,int> > :: iterator iter = edges.begin(); iter != edges.end(); iter++)
  {
    vertexNeighbors[iter->first].insert(make_pair(iter->second,0)); 
    vertexNeighbors[iter->second].insert(make_pair(iter->first,0)); 
  }

  // number the neighbors
  for(int i=0; i<numVertices; i++)
  {
    int count = 0;
    for(map<int,int> :: iterator iter = vertexNeighbors[i].begin(); iter != vertexNeighbors[i].end(); iter++)
    {
      iter->second = count;
      count++;
    }
  }

  BuildVertexNeighborsVector();
}

void Graph::BuildVertexNeighborsVector()
{
  vertexNeighborsVector.clear();

  // create a copy of the data (in a vector), so that can access ith element fast
  for(int i=0; i<numVertices; i++)
  {
    vertexNeighborsVector.push_back(vector<int>());
    for(map<int,int> :: iterator iter = vertexNeighbors[i].begin(); iter != vertexNeighbors[i].end(); iter++)
      vertexNeighborsVector[i].push_back(iter->first);
  }
}

int Graph::GetMaxDegree()
{
  int maxDegree = 0;
  for(int vtx=0; vtx<numVertices; vtx++)
    if ((int)vertexNeighbors[vtx].size() > maxDegree)
      maxDegree = vertexNeighbors[vtx].size();
  return maxDegree;
}

int Graph::GetMinDegree()
{
  int minDegree = INT_MAX;
  for(int vtx=0; vtx<numVertices; vtx++)
    if ((int)vertexNeighbors[vtx].size() < minDegree)
      minDegree = vertexNeighbors[vtx].size();
  return minDegree;
}

double Graph::GetAvgDegree()
{
  double avgDegree = 0;
  for(int vtx=0; vtx<numVertices; vtx++)
    avgDegree += vertexNeighbors[vtx].size();
  return avgDegree / numVertices;
}

double Graph::GetStdevDegree()
{
  double avgDegree_ = GetAvgDegree();
  double std = 0;
  for(int vtx=0; vtx<numVertices; vtx++)
    std += (vertexNeighbors[vtx].size() - avgDegree_) * (vertexNeighbors[vtx].size() - avgDegree_);
  return sqrt(std / numVertices);
}

int Graph::IsNeighbor(int vtx1, int vtx2)
{
  map<int,int> :: iterator iter = vertexNeighbors[vtx1].find(vtx2);
  if (iter == vertexNeighbors[vtx1].end())
    return 0;
  else
    return iter->second + 1;
}

void Graph::ExpandNeighbors()
{
  // over all edges:
  // insert neigbors of every vtx into the edges

  set<pair<int, int> > expandedEdges = edges;

  for(set<pair<int, int> > :: iterator iter = edges.begin(); iter != edges.end(); iter++)
  {
    int vtxA = iter->first; 
    int vtxB = iter->second; 

    // connect all neighbors of A to B
    for(map<int,int> :: iterator mapIter = vertexNeighbors[vtxA].begin(); mapIter != vertexNeighbors[vtxA].end(); mapIter++)
    {
      if (vtxB < mapIter->first)
        expandedEdges.insert(make_pair(vtxB, mapIter->first)); 
    }

    // connect all neigbhors of B to A
    for(map<int,int> :: iterator mapIter = vertexNeighbors[vtxB].begin(); mapIter != vertexNeighbors[vtxB].end(); mapIter++)
      if (vtxA < mapIter->first)
        expandedEdges.insert(make_pair(vtxA, mapIter->first)); 
  }
 
  edges = expandedEdges;
  numEdges = edges.size();
  BuildVertexNeighbors();
}

void Graph::PrintInfo()
{
  printf("Graph vertices: %d\n", numVertices);
  printf("Graph edges: %d\n", numEdges);
  printf("Graph min degree: %d\n", GetMinDegree());
  printf("Graph max degree: %d\n", GetMaxDegree());
  printf("Graph avg degree: %G\n", GetAvgDegree());
  printf("Graph degree stdev: %G\n", GetStdevDegree());
}

void Graph::GetLaplacian(SparseMatrix ** L, int scaleRows)
{
  SparseMatrixOutline outline(3*numVertices);
  for(int i=0; i<numVertices; i++)
  {
    int numNeighbors = (int)vertexNeighborsVector[i].size();
    if (numNeighbors == 0)
      continue;

    for(int k=0; k<3; k++)
      outline.AddEntry(3 * i + k, 3 * i + k, (scaleRows != 0) ? 1.0 : numNeighbors);

    double weight;
    if (scaleRows != 0)
      weight = -1.0 / numNeighbors;
    else
      weight = -1.0;

    for(int j=0; j<numNeighbors; j++)
      for(int k=0; k<3; k++)
        outline.AddEntry(3 * i + k, 3 * vertexNeighborsVector[i][j] + k, weight);
  }

  *L = new SparseMatrix(&outline);
}

Graph * Graph::CartesianProduct(Graph & graph2)
{
  int numProductVertices = numVertices * graph2.numVertices;
  int numProductEdges = numEdges * graph2.numVertices + numVertices * graph2.numEdges;
  int * productEdges = (int*) malloc (sizeof(int) * 2 * numProductEdges);
 
  printf("Num space-time graph vertices: %d\n", numProductVertices);
  printf("Num space-time graph edges: %d\n", numProductEdges);

  int edge = 0;
  for(int j=0; j<graph2.numVertices; j++)
  {
    for(int i=0; i<numVertices; i++)
    {
      // connect every vertex of graph1 to its neighbors
      //std::vector< std::vector<int> > vertexNeighborsVector;
      for(int k=0; k<(int)vertexNeighborsVector[i].size(); k++)
      {  
        if (i > vertexNeighborsVector[i][k])
        {
          productEdges[2*edge+0] = GetCartesianProductVertexIndex(i, j);
          productEdges[2*edge+1] = GetCartesianProductVertexIndex(vertexNeighborsVector[i][k], j);
          edge++;
        }
      }
      // connect every vertex of graph2 to its neighbors
      for(int k=0; k<(int)(graph2.vertexNeighborsVector[j].size()); k++)
      {  
        if (j > graph2.vertexNeighborsVector[j][k])
        {
          productEdges[2*edge+0] = GetCartesianProductVertexIndex(i, j);
          productEdges[2*edge+1] = GetCartesianProductVertexIndex(i, graph2.vertexNeighborsVector[j][k]);
          edge++;
        }
      }
    }
  }

  Graph * graph = new Graph(numProductVertices, numProductEdges, productEdges);
  free(productEdges);
  return graph;
}

// cluster given vertices into connected components
void Graph::Cluster(std::set<int> & vertices, vector<set<int> > & clusters)
{
  clusters.clear();
  for(set<int> :: iterator iter = vertices.begin(); iter != vertices.end(); iter++)
  {
    int vtx = *iter;
    int found = -1;
    for(int i=0; i<(int)clusters.size(); i++)
    {
      if (clusters[i].find(vtx) != clusters[i].end())
      {
        found = i;
        break;
      }
      for(set<int> :: iterator iter2 = clusters[i].begin(); iter2 != clusters[i].end(); iter2++)
      {
        if (IsNeighbor(vtx, *iter2))
        {
          found = i;
          break;
        }
      }
    }

    if (found == -1)
    {
     set<int> newCluster;
     newCluster.insert(vtx);
     clusters.push_back(newCluster);
    }
    else
    {
      clusters[found].insert(vtx);
    }
  }
}

int Graph::GetCartesianProductVertexIndex(int vertex1, int vertex2)
{
  return vertex2 * numVertices + vertex1;
}

void Graph::GetCartesianProductVertexIndexComponents(int productVertex, int * vertex1, int * vertex2)
{
  *vertex2 = productVertex / numVertices;
  *vertex1 = productVertex % numVertices;
}

void Graph::ShortestPath(std::set<int> & seedVertices, std::vector<int> & distances)
{
  distances.clear();
  distances.resize(numVertices);
  
  for(set<int> :: iterator iter = seedVertices.begin(); iter != seedVertices.end(); iter++)
    distances[*iter] = 0;

  set<int> visitedVertices = seedVertices;

  int distance = 0;
  set<int> oldFront, front;
  oldFront = seedVertices;
  while ((int)visitedVertices.size() != numVertices)
  {
    distance++;

    // create the front
    front.clear();
    for(set<int> :: iterator iter = oldFront.begin(); iter != oldFront.end(); iter++)
    {
      int node = *iter;
      for(int i=0; i < (int)vertexNeighborsVector[node].size(); i++)
      {
        int neighbor = vertexNeighborsVector[node][i];
        if (visitedVertices.find(neighbor) == visitedVertices.end())
          front.insert(neighbor);
      }
    }

    // write distance to front
    for(set<int> :: iterator iter = front.begin(); iter != front.end(); iter++)
    {
      int node = *iter;
      visitedVertices.insert(node);
      distances[node] = distance;
    }

    oldFront = front; 
  }
}

