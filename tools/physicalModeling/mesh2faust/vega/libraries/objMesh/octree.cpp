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

//  An octree storing triangles. Can be intersected with a sphere or a line segment.
//  Jernej Barbic, CMU

#include "openGL-headers.h"
#include <iostream>
#include "octree.h"
using namespace std;

template<class TriangleClass>
Octree<TriangleClass>::Octree(int maxDepth_, int depth_): maxDepth(maxDepth_), depth(depth_) 
{
  for(int i=0; i<8; i++)
    childrenNodes[i] = NULL;
}

template<class TriangleClass>
bool Octree<TriangleClass>::build(std::vector<TriangleClass> & triangleList, int maxNumTriangles)
{
  BoundingBox parentCube(triangleList);
  parentCube.expand(1.05);
  return build(triangleList,parentCube,maxNumTriangles);
}

template<class TriangleClass>
int Octree<TriangleClass>::buildPrintInfo = 0;

template<class TriangleClass>
int Octree<TriangleClass>::numMaxDepthExceededCases = 0;

template<class TriangleClass>
int Octree<TriangleClass>::numMaxTriInDepthExceededCases = 0;

template<class TriangleClass>
bool Octree<TriangleClass>::build(std::vector<TriangleClass> & triangleList, BoundingBox & parentCube, int maxNumTriangles)
{
  // set the bounding box
  boundingBox = parentCube;

  // total number of triangles 
  int numTriangles = (int)triangleList.size();

  // if there are fewer triangles than the threshold value, or if max depth has been reached, this node becomes a leaf which stores the triangles
  // max depth checking is necessary, since otherwise vertices with high valence will always be contained in some box, and that box will be split forever
  if ((numTriangles <= maxNumTriangles) || (depth >= maxDepth))
  {
    // cout << "L" << numTriangles << " " << depth << " " << endl;
    for(int i=0; i<numTriangles; i++)
      triangles.push_back(triangleList[i]);

    if ((depth >= maxDepth) && (numTriangles >= maxNumTriangles))
    {
      if (buildPrintInfo == 2)
        printf("Warning: cube max depth (%d) reached with more triangles per cell (%d) than requested (%d)\n",maxDepth,numTriangles,maxNumTriangles);

      if (buildPrintInfo == 1)
      {
        numMaxDepthExceededCases++;

        if (numMaxDepthExceededCases <= 5)
          printf("Warning: cube max depth (%d) reached with more triangles per cell (%d) than requested (%d)\n",maxDepth,numTriangles,maxNumTriangles);

        if (numMaxDepthExceededCases == 5)
        {
          printf("(suppressing further max depth warning messages)\n");
        }

        if (numTriangles > numMaxTriInDepthExceededCases)
          numMaxTriInDepthExceededCases = numTriangles;
      }
    }

    return true;
  }

  //cout << "N" << numTriangles << " ";

  // create the child cubes;
  BoundingBox childCubeBoxes[8];
  createChildCubes(childCubeBoxes);

  std::vector<TriangleClass> childTriangles[8];

  // for each child, generate a list of triangles that intersect the child bounding box
  for(int i=0; i<numTriangles; i++)
    for(int j=0; j<8; j++)
      if (triangleList[i].doesIntersectBox(childCubeBoxes[j]))
        childTriangles[j].push_back(triangleList[i]);

  // for (int i=0; i<8; i++)
  //   cout << "S" << i << ":" << childTriangles[i].size() << " ";
  // cout << endl;

  // for any child with intersecting triangles, create and recursively build the subtree
  for(int i=0; i<8; i++)
  {
    if (childTriangles[i].size() > 0)
    {
      childrenNodes[i] = new Octree<TriangleClass>(maxDepth,depth+1);

      if(childrenNodes[i] == NULL)
        return false;

      if(!childrenNodes[i]->build(childTriangles[i], childCubeBoxes[i], maxNumTriangles))
        return false;
    }
    else
      childrenNodes[i] = NULL;
  }

  //cout << "C ";
  return true;
}

template<class TriangleClass>
int Octree<TriangleClass>::getDepth()
{
  if(triangles.size() > 0)
    return 0; // leaf
  else
  {
    int maxChildDepth=0;
    for(int i=0; i<8; i++)
    {
      if(childrenNodes[i] != NULL)
      {
        int childDepth = childrenNodes[i]->getDepth();
        if (childDepth > maxChildDepth)
          maxChildDepth = childDepth;
      }
    }
    return maxChildDepth + 1;
  }
}

template<class TriangleClass>
void Octree<TriangleClass>::buildCollisionList(std::vector<TriangleClass*> & triangleList, const SimpleSphere & simpleSphere)
{
  // if the bounding box does not intersect the sphere, there can be no collision
  if(!simpleSphere.doesBoundingBoxIntersect(boundingBox))
    return;

  // if this node is a leaf, add its triangles to the potential collision list, otherwise recurse
  if(triangles.size() > 0)
  {
    int tsize = (int)triangles.size();
    for(int i=0; i<tsize; i++)
      triangleList.push_back(&(triangles[i]));
  }
  else
  {
    for(int i=0; i<8; i++)
      if(childrenNodes[i] != NULL)
        childrenNodes[i]->buildCollisionList(triangleList, simpleSphere);
  }

  return;
}

template<class TriangleClass>
void Octree<TriangleClass>::buildCollisionList(std::vector<TriangleClass*> & triangleList,  const Vec3d & segmentStartPoint, const Vec3d & segmentEndPoint, vector<Vec3d> * intersectionList)
{
  // if the bounding box does not intersect the line segment, there can be no collision
  Vec3d intersectionPoint;
  if(!boundingBox.lineSegmentIntersection(segmentStartPoint, segmentEndPoint, &intersectionPoint))
    return;

  // if this node is a leaf, add its triangles to the potential collision list, otherwise recurse
  if(triangles.size() > 0)
  {
    int tsize = (int)triangles.size();
    for(int i=0; i<tsize; i++)
    {
      Vec3d intersectionPoint;
      int collisionStatus = triangles[i].lineSegmentIntersection(segmentStartPoint, segmentEndPoint, &intersectionPoint);
      if (collisionStatus == 1) 
      {
        triangleList.push_back(&(triangles[i]));
        if(intersectionList) 
          intersectionList->push_back(intersectionPoint);
      }
    }
  }
  else
  {
    for(int i=0; i<8; i++)
      if(childrenNodes[i] != NULL)
        childrenNodes[i]->buildCollisionList(triangleList, segmentStartPoint, segmentEndPoint, intersectionList);
  }
}

template<class TriangleClass>
void Octree<TriangleClass>::render()
{
  for(int i=0; i<8; i++)
    if(childrenNodes[i] != NULL)
      childrenNodes[i]->render();

  // render only leaf nodes that are not empty
  if(triangles.size() > 0)
    boundingBox.render();
}

template<class TriangleClass>
void Octree<TriangleClass>::render(int level)
{
  for(int i=0; i<8; i++)
    if(childrenNodes[i] != NULL)
      childrenNodes[i]->render(level);

  // render only non-empty leaf nodes at the requested depth
  if ((triangles.size() > 0) && (level == depth)) 
    boundingBox.render();
}

template<class TriangleClass>
void Octree<TriangleClass>::render(int level, int boxIndex)
{
  renderCounter = 0;
  renderHelper(level,boxIndex);
}

template<class TriangleClass>
int Octree<TriangleClass>::renderCounter; 

template<class TriangleClass>
int Octree<TriangleClass>::printRenderInfo = 0;

template<class TriangleClass>
void Octree<TriangleClass>::renderHelper(int level, int boxIndex)
{
  unsigned int  j;
  for(int i=0; i<8; i++)
    if(childrenNodes[i] != NULL)
      childrenNodes[i]->renderHelper(level,boxIndex);

  // render only non-empty leaf nodes at the requested depth
  if ((triangles.size() > 0) && (level == depth))
  {
    if (renderCounter == boxIndex)
    {
      glColor3f(0,1,0);
      boundingBox.render();
      glColor3f(1,0,0);
      for(j=0; j<triangles.size(); j++)
        triangles[j].render();
      glColor3f(0,0,0);
      for(j=0; j<triangles.size(); j++)
        triangles[j].renderEdges();
      if (printRenderInfo == 1)
      {
        boundingBox.print();
        printf("Num triangles: %d.\n", (int)triangles.size());
        printRenderInfo = 0;
      }
    }
    renderCounter++;
  }
}

template<class TriangleClass>
void Octree<TriangleClass>::deallocate()
{
  for(int i=0; i<8; i++)
  {
    if(childrenNodes[i] != NULL)
    {
      childrenNodes[i]->deallocate();

      delete(childrenNodes[i]);
      childrenNodes[i] = NULL;
    }
  }

  triangles.clear();
}

template<class TriangleClass>
void Octree<TriangleClass>::createChildCubes(BoundingBox * childCubeBoxes)
{
  Vec3d center = boundingBox.center();

  // top left & near
  childCubeBoxes[0].setbmin(boundingBox.bmin()[0], center[1], boundingBox.bmin()[2]);
  childCubeBoxes[0].setbmax(center[0], boundingBox.bmax()[1], center[2]);

  // top right & near
  childCubeBoxes[1].setbmin(center[0], center[1], boundingBox.bmin()[2]);
  childCubeBoxes[1].setbmax(boundingBox.bmax()[0], boundingBox.bmax()[1], center[2]);

  // bottom left & near
  childCubeBoxes[2].setbmin(boundingBox.bmin()[0], boundingBox.bmin()[1], boundingBox.bmin()[2]);
  childCubeBoxes[2].setbmax(center[0], center[1], center[2]);

  // bottom right & near
  childCubeBoxes[3].setbmin(center[0], boundingBox.bmin()[1], boundingBox.bmin()[2]);
  childCubeBoxes[3].setbmax(boundingBox.bmax()[0], center[1], center[2]);

  // top left & far
  childCubeBoxes[4].setbmin(boundingBox.bmin()[0], center[1], center[2]);
  childCubeBoxes[4].setbmax(center[0], boundingBox.bmax()[1], boundingBox.bmax()[2]);

  // top right & far
  childCubeBoxes[5].setbmin(center[0], center[1], center[2]);
  childCubeBoxes[5].setbmax(boundingBox.bmax()[0], boundingBox.bmax()[1], boundingBox.bmax()[2]);

  // bottom left & far
  childCubeBoxes[6].setbmin(boundingBox.bmin()[0], boundingBox.bmin()[1], center[2]);
  childCubeBoxes[6].setbmax(center[0], center[1], boundingBox.bmax()[2]);

  // bottom right & far
  childCubeBoxes[7].setbmin(center[0], boundingBox.bmin()[1], center[2]);
  childCubeBoxes[7].setbmax(boundingBox.bmax()[0], center[1], boundingBox.bmax()[2]);

  // sanity check
  for (int i=0; i<7; i++)
    childCubeBoxes[i].verifyBox();
}

template Octree<TriangleBasic>::Octree(int maxDepth_g, int depth_g);
template bool Octree<TriangleBasic>::build(std::vector<TriangleBasic> &triangleList, BoundingBox &parentCube, int maxNumTriangles);
template bool Octree<TriangleBasic>::build(std::vector<TriangleBasic> &triangleList, int maxNumTriangles);
template void Octree<TriangleBasic>::setBuildPrintInfo(int info); 
template void Octree<TriangleBasic>::getBuildInfo(int * numMaxDepthExceededCases, int * numMaxTriInDepthExceededCases);
template int Octree<TriangleBasic>::getDepth();
template void Octree<TriangleBasic>::buildCollisionList(std::vector<TriangleBasic*> &triangleList, const SimpleSphere &simpleSphere);
template void Octree<TriangleBasic>::buildCollisionList(std::vector<TriangleBasic*> &triangleList, const Vec3d & segmentStartPoint, const Vec3d & segmentEndPoint, vector<Vec3d> * intersectionList);
template void Octree<TriangleBasic>::render();
template void Octree<TriangleBasic>::render(int level);
template void Octree<TriangleBasic>::render(int level, int boxIndex);
template void Octree<TriangleBasic>::renderHelper(int level, int boxIndex);

template void Octree<TriangleBasic>::deallocate();
template void Octree<TriangleBasic>::createChildCubes(BoundingBox * childCubeBoxes);

template Octree<TriangleWithCollisionInfo>::Octree(int maxDepth_g, int depth_g);
template bool Octree<TriangleWithCollisionInfo>::build(std::vector<TriangleWithCollisionInfo> &triangleList, BoundingBox &parentCube, int maxNumTriangles);
template bool Octree<TriangleWithCollisionInfo>::build(std::vector<TriangleWithCollisionInfo> &triangleList, int maxNumTriangles);
template void Octree<TriangleWithCollisionInfo>::setBuildPrintInfo(int info); 
template void Octree<TriangleWithCollisionInfo>::getBuildInfo(int * numMaxDepthExceededCases, int * numMaxTriInDepthExceededCases);
template void Octree<TriangleWithCollisionInfo>::buildCollisionList(std::vector<TriangleWithCollisionInfo*> &triangleList, const SimpleSphere &simpleSphere);
template void Octree<TriangleWithCollisionInfo>::buildCollisionList(std::vector<TriangleWithCollisionInfo*> &triangleList, const Vec3d & segmentStartPoint, const Vec3d & segmentEndPoint, std::vector<Vec3d> * intersectionList);
template int Octree<TriangleWithCollisionInfo>::getDepth();
template void Octree<TriangleWithCollisionInfo>::render();
template void Octree<TriangleWithCollisionInfo>::render(int level);
template void Octree<TriangleWithCollisionInfo>::render(int level, int boxIndex);
template void Octree<TriangleWithCollisionInfo>::renderHelper(int level, int boxIndex);
template void Octree<TriangleWithCollisionInfo>::deallocate();
template void Octree<TriangleWithCollisionInfo>::createChildCubes(BoundingBox * childCubeBoxes);

template Octree<TriangleWithCollisionInfoAndPseudoNormals>::Octree(int maxDepth_g, int depth_g);
template bool Octree<TriangleWithCollisionInfoAndPseudoNormals>::build(std::vector<TriangleWithCollisionInfoAndPseudoNormals> &triangleList, BoundingBox &parentCube, int maxNumTriangles);
template bool Octree<TriangleWithCollisionInfoAndPseudoNormals>::build(std::vector<TriangleWithCollisionInfoAndPseudoNormals> &triangleList, int maxNumTriangles);
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::setBuildPrintInfo(int info); 
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::getBuildInfo(int * numMaxDepthExceededCases, int * numMaxTriInDepthExceededCases);
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::buildCollisionList(std::vector<TriangleWithCollisionInfoAndPseudoNormals*> &triangleList, const SimpleSphere &simpleSphere);
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::buildCollisionList(std::vector<TriangleWithCollisionInfoAndPseudoNormals*> &triangleList, const Vec3d & segmentStartPoint, const Vec3d & segmentEndPoint, vector<Vec3d> * intersectionList);
template int Octree<TriangleWithCollisionInfoAndPseudoNormals>::getDepth();
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::render();
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::render(int level);
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::render(int level, int boxIndex);
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::renderHelper(int level, int boxIndex);
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::deallocate();
template void Octree<TriangleWithCollisionInfoAndPseudoNormals>::createChildCubes(BoundingBox * childCubeBoxes);

