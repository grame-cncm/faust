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

#include <set>
using namespace std;
#include "generateMeshGraph.h"

Graph * GenerateMeshGraph::Generate(const VolumetricMesh * volumetricMesh)
{
  // Generate springs:
  typedef pair<int,int> edge;
  #define SORTED(i,j) ( (i) <= (j) ? make_pair((i),(j)) : make_pair((j),(i)) )

  // first, all tensile springs (quad edges)
  set<edge> edgeSet;
  int numElementEdges = volumetricMesh->getNumElementEdges();
  int * edgeBuffer = (int*) malloc (sizeof(int) * 2 * numElementEdges);
  for(int el=0; el<volumetricMesh->getNumElements(); el++)
  {
    volumetricMesh->getElementEdges(el, edgeBuffer);  

    for(int j=0; j<numElementEdges; j++)
      edgeSet.insert(SORTED(edgeBuffer[2*j+0], edgeBuffer[2*j+1]));
  }

  free(edgeBuffer);

  int numEdges = edgeSet.size();
  int * edges = (int*) malloc (sizeof(int) * 2 * numEdges);

  int count = 0;
  for(set<edge> :: iterator iter = edgeSet.begin(); iter != edgeSet.end(); iter++)
  {
    edges[2*count+0] = iter->first;
    edges[2*count+1] = iter->second;
    count++;
  }

  //for(int i=0; i<numEdges; i++)
    //printf("%d %d\n", edges[2*i+0], edges[2*i+1]);
  //printf("Num edges: %d\n", numEdges);

  Graph * graph  = new Graph(volumetricMesh->getNumVertices(), numEdges, edges);

  free(edges);

  return graph;
}

