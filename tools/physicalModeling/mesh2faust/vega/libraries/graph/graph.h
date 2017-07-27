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

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <set>
#include <map>
#include "sparseMatrix.h"

/*
  A class to store a graph (nodes connected with edges).
*/

class Graph
{
public:

  Graph(); 
  Graph(const char * filename, int sortEdgeVertices=1); // load graph from file
  // each edge is given by two integers; length of "edges" should be 2xnumEdges
  Graph(int numVertices, int numEdges, int * edges, int sortEdgeVertices=1);
  Graph(const Graph & graph);
  Graph & operator=(const Graph & graph);
  ~Graph();

  void Save(const char * filename); // save graph to file

  int GetNumVertices();
  int GetNumEdges();

  int GetNumNeighbors(int vertex);
  int GetNeighbor(int vertex, int i);
  int IsNeighbor(int vtx1, int vtx2);

  int GetMinDegree();
  int GetMaxDegree();
  double GetAvgDegree();
  double GetStdevDegree();

  void ExpandNeighbors(); // connects every node to all the neighbors of every neighbor
  void PrintInfo();

  // if scaleRows == 1, each row will be scaled to sum to one
  void GetLaplacian(SparseMatrix ** L, int scaleRows=0);

  // returns the Cartesian graph product of "this" and graph2
  Graph * CartesianProduct(Graph & graph2);
  // return the index of vertex (vertex1, vertex2) in the cartesian product of "this" with another graph (which is not needed explicitly)
  int GetCartesianProductVertexIndex(int vertex1, int vertex2);
  // converts in the opposite direction
  void GetCartesianProductVertexIndexComponents(int productVertex, int * vertex1, int * vertex2);

  // clusters given vertices into connected components
  void Cluster(std::set<int> & vertices, std::vector<std::set<int> > & clusters);

  // computes the shortest distance from the given seed vertices (distance of zero) to all the graph vertices
  // input: seed vertices
  // output: distance to the set of seed vertices, for each mesh vertex
  void ShortestPath(std::set<int> & seedVertices, std::vector<int> & distances);

protected:
  int numVertices, numEdges; // num vertices, num edges
  std::set< std::pair<int, int> > edges;
  std::vector< std::map<int, int> > vertexNeighbors; // (index of neighbor, index)
  std::vector< std::vector<int> > vertexNeighborsVector;

  void BuildVertexNeighbors();
  void BuildVertexNeighborsVector();
};

inline int Graph::GetNumVertices()
{
  return numVertices;
}

inline int Graph::GetNumEdges()
{
  return numEdges;
}

inline int Graph::GetNumNeighbors(int vertex)
{
  return (int) vertexNeighborsVector[vertex].size();
}

inline int Graph::GetNeighbor(int vertex, int i)
{
  return vertexNeighborsVector[vertex][i];
}

#endif

