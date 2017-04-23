/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "objMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Christopher Twigg, Daniel Schroeder,     *
 *               Yili Zhao, Yijing Li                                    *
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
#include <float.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <assert.h>
#include "macros.h"
#include "objMesh-disjointSet.h"
#include "objMesh.h"
using namespace std;

// for faster parallel loading of multimesh binary files, enable the -fopenmp -DUSE_OPENMP macro line in the Makefile-header file (see also documentation)

#ifdef USE_OPENMP
  #include <omp.h>
#endif

ObjMesh::ObjMesh(const std::string & filename_, fileFormatType fileFormat, int verbose) : filename(filename_)
{
  switch (fileFormat)
  {
    case ASCII:
    {
      std::string filenameString(filename_);
      loadFromAscii(filenameString, verbose);
    }
    break;

    case BINARY:
      loadFromBinary(filename_, verbose);
    break;

    default:
      printf("Error in ObjMesh::ObjMesh: File format %d is unknown.\n", fileFormat);
      throw 1;
    break;
  }

  computeBoundingBox();

  // statistics
  if (verbose)
  {
    std::cout << "Parsed obj file '" << filename << "'; statistics:" << std::endl;
    std::cout << "   " << groups.size() << " groups," << std::endl;
    std::cout << "   " << getNumFaces() << " faces," << std::endl;
    std::cout << "   " << vertexPositions.size() << " vertices," << std::endl;
    std::cout << "   " << normals.size() << " normals, " << std::endl;
    std::cout << "   " << textureCoordinates.size() << " texture coordinates, " << std::endl;
  }
}

ObjMesh::ObjMesh(void * binaryInputStream, streamType stream, int verbose)
{
  filename = string("");
  loadFromBinary(binaryInputStream, stream, verbose);
  computeBoundingBox();
}

ObjMesh::ObjMesh(int numVertices, const double * vertices, int numTriangles, const int * triangles)
{
  filename = string("");

  for(int i=0; i<numVertices; i++)
    addVertexPosition(Vec3d(vertices[3*i+0], vertices[3*i+1], vertices[3*i+2]));

  unsigned int materialIndex = 0;
  addMaterial(string("default"), Vec3d(1,1,1), Vec3d(1,1,1), Vec3d(1,1,1), 0);
  groups.push_back(Group("defaultGroup", materialIndex));
  for(int i=0; i<numTriangles; i++)
  {
    Face face;
    face.addVertex(Vertex(triangles[3*i+0]));
    face.addVertex(Vertex(triangles[3*i+1]));
    face.addVertex(Vertex(triangles[3*i+2]));
    addFaceToGroup(face, 0);
  }

  computeBoundingBox();
}

ObjMesh::ObjMesh(int numVertices, const double * vertices, int numFaces, const int* faceVertexCounts, const int * faces)
{
  filename = string("");

  for(int i = 0; i < numVertices; i++)
    addVertexPosition(Vec3d(vertices[3*i+0], vertices[3*i+1], vertices[3*i+2]));

  unsigned int materialIndex = 0;
  addMaterial(string("default"), Vec3d(1,1,1), Vec3d(1,1,1), Vec3d(1,1,1), 0);
  groups.push_back(Group("defaultGroup", materialIndex));
  for(int i = 0, k = 0; i < numFaces; i++)
  {
    Face face;
    int faceVertexCount = faceVertexCounts[i];
    for(int j = 0; j < faceVertexCount; j++)
    {
      face.addVertex(Vertex(faces[k]));
      k++;
    }

    addFaceToGroup(face, 0);
  }

  computeBoundingBox();
}


ObjMesh::ObjMesh(const ObjMesh & objMesh_)
{ 
  // copy materials 
  unsigned int numObjMaterials = objMesh_.getNumMaterials();
  for (unsigned int materialIndex=0; materialIndex < numObjMaterials; materialIndex++)
  {
    std::string materialName = objMesh_.getMaterial(materialIndex).getName();
    Vec3d Ka = objMesh_.getMaterial(materialIndex).getKa();
    Vec3d Kd = objMesh_.getMaterial(materialIndex).getKd();
    Vec3d Ks = objMesh_.getMaterial(materialIndex).getKs();
    double shininess = objMesh_.getMaterial(materialIndex).getShininess();

    // add a new material
    addMaterial(materialName, Ka, Kd, Ks, shininess);

    if (objMesh_.getMaterial(materialIndex).hasTextureFilename())
    {
      std::string textureFilename = objMesh_.getMaterial(materialIndex).getTextureFilename();
      materials[materialIndex].setTextureFilename(textureFilename);
    }
  }  // for materialIndex

  // copy vertices
  unsigned int numVertices = objMesh_.getNumVertices();
  for(unsigned int vertexIndex=0; vertexIndex < numVertices; vertexIndex++)
    vertexPositions.push_back(objMesh_.vertexPositions[vertexIndex]);

  // copy texture coordinates
  unsigned int numTexCoordinates = objMesh_.getNumTextureCoordinates();
  for(unsigned int textureCoordinateIndex=0; textureCoordinateIndex < numTexCoordinates; textureCoordinateIndex++)
    textureCoordinates.push_back(objMesh_.textureCoordinates[textureCoordinateIndex]);

  // copy normals
  unsigned int numNormals = objMesh_.getNumNormals();
  for(unsigned int normalIndex=0; normalIndex < numNormals; normalIndex++)
    normals.push_back(objMesh_.normals[normalIndex]);

  // copy groups
  unsigned int numGroups = objMesh_.getNumGroups();
  for(unsigned int groupIndex=0; groupIndex < numGroups; groupIndex++)
  {
    // group name and material index
    std::string groupName = objMesh_.groups[groupIndex].getName();
    unsigned int materialIndex = objMesh_.groups[groupIndex].getMaterialIndex();
    groups.push_back(Group(groupName, materialIndex));

    // copy faces of current group
    unsigned int numFaces = objMesh_.groups[groupIndex].getNumFaces();
    for (unsigned int faceIndex=0; faceIndex < numFaces; faceIndex++)
    {
      const Face * objMeshFace = objMesh_.groups[groupIndex].getFaceHandle(faceIndex);
      unsigned int numFaceVertices = objMeshFace->getNumVertices();
      Face currentFace;
      for (unsigned int vertexIndex=0; vertexIndex < numFaceVertices; vertexIndex++)
        currentFace.addVertex(objMeshFace->getVertex(vertexIndex));

      groups[groupIndex].addFace(currentFace);
    }
  }  // for groupIndex
  
  // copy filename
  filename = objMesh_.filename;

  computeBoundingBox();
}

int ObjMesh::loadFromAscii(const string & filename, int verbose)
{
  unsigned int numFaces = 0;

  const int maxline = 4096;
  std::ifstream ifs(filename.c_str());
  char line[maxline];

  unsigned int currentGroup=0;
  unsigned int ignoreCounter=0;

  unsigned int currentMaterialIndex = 0;

  // Note: the default material will be added when encountered in the obj file, or at the end if necessary. One cannot simply add it here at the beginning because a material read from the .mtl file could also be called "default".

  if (verbose)
    std::cout << "Parsing .obj file '" << filename << "'." << std::endl;

  if (!ifs)
  {
    std::string message = "Could not open .obj file '";
    message.append(filename);
    message.append( "'" );
    throw ObjMeshException( message );
  }

  int lineNum = 0;
  int numGroupFaces = 0;
  int groupCloneIndex = 0;
  std::string groupSourceName;

  while(ifs)
  {
    lineNum++;
    ifs.getline(line, maxline);
    if (strlen(line) > 0)
    {
      // if ending in '\\', the next line should be concatenated to the current line
      int lastCharPos = (int)strlen(line)-1;
      while(line[lastCharPos] == '\\') 
      {
        line[lastCharPos] = ' ';  // first turn '\' to ' '
        char nextline[maxline];
        ifs.getline(nextline, maxline);
        strcat(line, nextline);
        lastCharPos = (int)strlen(line)-1;
      }
    }

    std::string lineString(line);
    // trim white space ahead
    lineString.erase(lineString.begin(), std::find_if(lineString.begin(), lineString.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    // trim white space in the end  
    lineString.erase(std::find_if(lineString.rbegin(), lineString.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), lineString.end());


    memset(line, 0, maxline);
    strcpy(line, lineString.c_str());

    convertWhitespaceToSingleBlanks(line);

    char command = line[0];

    if (strncmp(line,"v ",2) == 0) // vertex
    {
      //std::cout << "v " ;
      Vec3d pos;
      double x,y,z;
      if (sscanf(line, "v %lf %lf %lf\n", &x, &y, &z) < 3)
      {
        throw ObjMeshException("Invalid vertex", filename, lineNum);
      }
      pos = Vec3d(x,y,z);
      vertexPositions.push_back( pos );
    }
    else if (strncmp(line, "vn ", 3) == 0)
    {
      //std::cout << "vn " ;
      Vec3d normal;
      double x,y,z;
      if (sscanf(line,"vn %lf %lf %lf\n", &x, &y, &z) < 3)
      {
        throw ObjMeshException("Invalid normal", filename, lineNum);
      }
      normal = Vec3d(x,y,z);
      normals.push_back(normal);
    }
    else if (strncmp(line, "vt ", 3) == 0 )
    {
      //std::cout << "vt " ;
      Vec3d tex(0.0);
      double x,y;
      if (sscanf(line, "vt %lf %lf\n", &x, &y) < 2)
      {
        throw ObjMeshException("Invalid texture coordinate", filename, lineNum);
      }
      tex = Vec3d(x,y,0);
      textureCoordinates.push_back(tex);
    }
    else if (strncmp(line, "g ", 2) == 0)
    {
      // remove last newline
      if (strlen(line) > 0)
      {
        if (line[strlen(line)-1] == '\n')
          line[strlen(line)-1] = 0;
      }

      // remove last carriage return
      if (strlen(line) > 0)
      {
        if (line[strlen(line)-1] == '\r')
          line[strlen(line)-1] = 0;
      }

      std::string name;
      if (strlen(line) < 2)
      {
        if (verbose)
          cout << "Warning:  Empty group name encountered: " << filename << " " << lineNum << endl;
        name = string("");
      }
      else
        name = string(&line[2]);

      //printf("Detected group: %s\n", &line[2]);

      // check if this group already exists
      bool groupFound = false;
      unsigned int counter = 0;
      for(std::vector< Group >::const_iterator itr = groups.begin(); itr != groups.end(); itr++)
      {
        if (itr->getName() == name)
        {
          currentGroup = counter;
          groupFound = true;
          break;
        }
        counter++;
      }
      if (!groupFound)
      {
        groups.push_back(Group(name, currentMaterialIndex));
        currentGroup = groups.size() - 1;
        numGroupFaces = 0;
        groupCloneIndex = 0;
        groupSourceName = name;
      }
    }
    else if ((strncmp(line, "f ", 2) == 0) || (strncmp(line, "fo ", 3) == 0))
    {
      char * faceLine = &line[2];
      if (strncmp(line, "fo", 2) == 0)
        faceLine = &line[3];

      //std::cout << "f " ;
      if (groups.empty())
      {
        groups.push_back(Group("default"));
        currentGroup = 0;
      }

      Face face;

      // the faceLine string now looks like the following:
      //   vertex1 vertex2 ... vertexn
      // where vertexi is v/t/n, v//n, v/t, or v

      char * curPos = faceLine;
      while( *curPos != '\0' )
      {
        // seek for next whitespace or eof
        char * tokenEnd = curPos;
        while ((*tokenEnd != ' ') && (*tokenEnd != '\0'))
          tokenEnd++;

        bool whiteSpace = false;
        if (*tokenEnd == ' ')
        {
          *tokenEnd = '\0';
          whiteSpace = true;
        }

        int pos;
        int nor;
        int tex;
        std::pair< bool, unsigned int > texPos;
        std::pair< bool, unsigned int > normal;

        // now, parse curPos
        if (strstr(curPos,"//") != NULL) 
        {
          if (sscanf(curPos, "%d//%d", &pos, &nor) < 2)
          {
            throw ObjMeshException( "Invalid face", filename, lineNum);
          }

          // v//n
          if (pos < 0)
            pos = (int)vertexPositions.size() + pos + 1;
          if (nor < 0)
            nor = (int)normals.size() + nor + 1;

          texPos = make_pair(false, 0);
          normal = make_pair(true, (unsigned int)nor);
        }
        else 
        {
          if (sscanf(curPos, "%d/%d/%d", &pos, &tex, &nor) != 3)
          {
            if (strstr(curPos, "/") != NULL)
            {
              if (sscanf(curPos, "%d/%d", &pos, &tex) == 2)
              {
                // v/t
                if (pos < 0)
                  pos = (int)vertexPositions.size() + pos + 1;
                if (tex < 0)
                  tex = (int)textureCoordinates.size() + tex + 1;

                texPos = make_pair(true, (unsigned int)tex);
                normal = make_pair(false, 0);
              }
              else
              {
                throw ObjMeshException("Invalid face", filename, lineNum);
              }
            }
            else
            { 
              if (sscanf(curPos, "%d", &pos) == 1)
              {
                // v
                if (pos < 0)
                  pos = (int)vertexPositions.size() + pos + 1;

                texPos = make_pair(false, 0);
                normal = make_pair(false, 0);
              }
              else
              {
                throw ObjMeshException("Invalid face", filename, lineNum);
              }
            }
          }
          else
          { 
            // v/t/n
            if (pos < 0)
              pos = (int)vertexPositions.size() + pos + 1;
            if (tex < 0)
              tex = (int)textureCoordinates.size() + tex + 1;
            if (nor < 0)
              nor = (int)normals.size() + nor + 1;

            texPos = make_pair(true, (unsigned int)tex);
            normal = make_pair(true, (unsigned int)nor);
          }
        }

        // sanity check
        if ((pos < 1) || (pos > (int)vertexPositions.size()))
        {
          printf("Error: vertex %d is out of bounds.\n", pos);
          throw 51;
        }

        if (texPos.first && ((tex < 1) || (tex > (int)textureCoordinates.size())))
        {
          printf("Error: texture %d is out of bounds.\n", tex);
          throw 53;
        }

        if (normal.first && ((nor < 1) || (nor > (int)normals.size())))
        {
          printf("Error: normal %d is out of bounds.\n", nor);
          throw 52;
        }

        // decrease indices to make them 0-indexed
        pos--;
        if (texPos.first)
          texPos.second--;
        if (normal.first)
          normal.second--;

        face.addVertex(Vertex((unsigned int)pos, texPos, normal));

        if (whiteSpace)
        {
          *tokenEnd = ' ';
          curPos = tokenEnd + 1; 
        }
        else
          curPos = tokenEnd;
      }

      numFaces++;
      groups[currentGroup].addFace(face);
      numGroupFaces++;
    }
    else if ((strncmp(line, "#", 1) == 0 ) || (strncmp(line, "\0", 1) == 0))
    { 
      // ignore comment lines and empty lines
    }
    else if (strncmp(line, "usemtl", 6) == 0)
    {
      // switch to a new material
      if (numGroupFaces > 0)
      {
        // usemtl without a "g" statement; must create a new group
        // first, create unique name
        char newNameC[4096];
        sprintf(newNameC, "%s.%d", groupSourceName.c_str(), groupCloneIndex);
        //printf("Splitting group...\n");
        //printf("New name=%s\n", newNameC);
        std::string newName(newNameC);
        groups.push_back(Group(newName, currentMaterialIndex));
        currentGroup = groups.size()-1;
        numGroupFaces = 0;
        groupCloneIndex++;
      }

      materialSearch:
      bool materialFound = false;
      unsigned int counter = 0;
      char * materialName = &line[7];
      for(std::vector< Material >::const_iterator itr = materials.begin(); itr != materials.end(); itr++)
      {
        if (itr->getName() == string(materialName))
        {
          currentMaterialIndex = counter;

          // update current group
          if (groups.empty())
          {
            groups.push_back(Group("default"));
            currentGroup = 0;
          }

          groups[currentGroup].setMaterialIndex(currentMaterialIndex);
          materialFound = true;
          break;
        }
        counter++;
      }

      if (!materialFound)
      {
        if (strcmp(materialName, "default") == 0)
        {
          addDefaultMaterial();
          goto materialSearch;
        }

        char msg[4096];
        sprintf(msg, "Obj mesh material %s does not exist.\n", materialName);
        throw ObjMeshException(msg);
      }
    }
    else if (strncmp(line, "mtllib", 6) == 0)
    {
      char mtlFilename[4096];
      strcpy(mtlFilename, filename.c_str());
      parseMaterials(mtlFilename, &line[7], verbose);
    }
    else if ((strncmp(line, "s ", 2) == 0 ) || (strncmp(line, "o ", 2) == 0))
    {
      // ignore lines beginning with s and o
      //std::cout << command << " ";
      if (ignoreCounter < 5)
      {
        if (verbose)
          std::cout << "Warning: ignoring '" << command << "' line" << std::endl;
        ignoreCounter++;
      }
      if (ignoreCounter == 5)
      {
        if (verbose)
          std::cout << "(suppressing further output of ignored lines)" << std::endl;
        ignoreCounter++;
      }
    }
    else
    {
      //std::cout << "invalid ";
      std::ostringstream msg;
      msg << "Invalid line in .obj file '" << filename << "': " << line;
      throw ObjMeshException(msg.str(), filename, lineNum);
    }
  }

  // add the "default" material if it doesn't already exist
  addDefaultMaterial();

  return 0;
}

void ObjMesh::addDefaultMaterial()
{
  // search if there already is the "default" material
  bool addDefaultMaterial = true;
  unsigned int numObjMaterials = getNumMaterials();
  for (unsigned int materialIndex=0; materialIndex<numObjMaterials; materialIndex++)
  {
    std::string materialNameString = materials[materialIndex].getName();
    char * materialName = (char *)(materialNameString.c_str());

    if(strcmp(materialName, "default") == 0)
    {
      addDefaultMaterial = false;
      break;
    }
  }

  if (addDefaultMaterial)
  {
    addMaterial(string("default"), Vec3d(0.2,0.2,0.2), Vec3d(0.6,0.6,0.6), Vec3d(0.0,0.0,0.0), 65);
  }
}

std::vector<std::string> ObjMesh::getGroupNames() const
{
  std::vector<std::string> result;
  result.reserve(groups.size());
  for(std::vector<Group>::const_iterator groupItr = groups.begin(); groupItr != groups.end(); groupItr++)
    result.push_back(groupItr->getName());

  return result;
}

ObjMesh::Group ObjMesh::getGroup(const std::string name) const
{
  for(std::vector<Group>::const_iterator itr = groups.begin(); itr != groups.end(); itr++)
  {
    if (itr->getName() == name)
      return *itr;
  }

  std::ostringstream oss;
  oss << "Invalid group name: '" << name << "'.";
  throw ObjMeshException(oss.str());
}

void ObjMesh::printInfo() const
{
  typedef std::vector<std::string> SVec;
  SVec groupNames1 = getGroupNames();
  for(SVec::const_iterator nameItr = groupNames1.begin(); nameItr != groupNames1.end(); nameItr++)
  {
    std::cout << "Found obj group '" << *nameItr << std::endl;
    ObjMesh::Group group1 = getGroup(*nameItr); // retrieve group named *nameItr, and store it into "group"
    std::cout << "Iterating through group faces..." << std::endl;
    for( unsigned int iFace = 0; iFace < group1.getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = group1.getFace(iFace); // get face number iFace
      if (face.getNumVertices() == 3)
        std::cout << "  found triangle ";
      else if (face.getNumVertices() == 4)
        std::cout << "  found quadrilateral ";
      else
        std::cout << "  found " << face.getNumVertices() << "-gon ";

      // Since the vertex positions are unique within the files, we can
      // use these to cross-index the polygons.
      for( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
      {
        if ( iVertex != 0 )
          std::cout << " -> ";
        std::cout << face.getVertex(iVertex).getPositionIndex(); // print out integer indices of the vertices
      }
      std::cout << std::endl;

      // Now we will retrieve positions, normals, and texture coordinates of the
      // files by indexing into the global vertex namespace.
      for( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
      {
        ObjMesh::Vertex vertex = face.getVertex(iVertex);
        std::cout << "    vertex " << iVertex << "; " << std::endl;
        std::cout << "      position = " << getPosition(vertex.getPositionIndex()) << ";" << std::endl;
        if (vertex.hasNormalIndex())
          std::cout << "      normal = " << getNormal(vertex.getNormalIndex()) << ";" << std::endl;
        if (vertex.hasTextureCoordinateIndex())
          std::cout << "      texture coordinate = " << getTextureCoordinate(vertex.getTextureCoordinateIndex()) << ";" << std::endl;
      }
    }
  }
}

bool ObjMesh::isTriangularMesh() const
{
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      if (groups[i].getFace(j).getNumVertices() != 3)
        return false;
    }
  return true;
}

bool ObjMesh::isQuadrilateralMesh() const
{
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      if (groups[i].getFace(j).getNumVertices() != 4)
        return false;
    }
  return true;
}

unsigned int ObjMesh::computeMaxFaceDegree() const
{
  unsigned int maxDegree = 0;
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      if (face->getNumVertices() > maxDegree)
        maxDegree = face->getNumVertices();
    }

  return maxDegree;
}

void ObjMesh::triangulate()
{
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      Face * face = (Face*) groups[i].getFaceHandle(j);
      if (face->getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than 3 vertices.\n");
      }
  
      unsigned int faceDegree = face->getNumVertices();

      if (faceDegree > 3)
      {
        // triangulate the face

        // get the vertices:
        vector<Vertex> vertices;
        for(unsigned int k=0; k<face->getNumVertices(); k++)
          vertices.push_back(face->getVertex(k));
        
        Face newFace;
        newFace.addVertex(vertices[0]);
        newFace.addVertex(vertices[1]);
        newFace.addVertex(vertices[2]);

        // overwrite old face
        *face = newFace;

        for(unsigned int k=2; k<faceDegree-1; k++)
        {
          // tesselate the remainder of the old face
          Face newFace;
          newFace.addVertex(vertices[0]);
          newFace.addVertex(vertices[k]);
          newFace.addVertex(vertices[k+1]);
          groups[i].addFace(newFace);
        }
      }
    }
}

void ObjMesh::computeBoundingBox()
{
  bmin = Vec3d(DBL_MAX, DBL_MAX, DBL_MAX);
  bmax = Vec3d(-DBL_MAX, -DBL_MAX, -DBL_MAX);

  for(unsigned int i=0; i < vertexPositions.size(); i++) // over all vertices
  {
    Vec3d p = vertexPositions[i]; 

    if (p[0] < bmin[0])
      bmin[0] = p[0];
    if (p[0] > bmax[0])
      bmax[0] = p[0];

    if (p[1] < bmin[1])
      bmin[1] = p[1];
    if (p[1] > bmax[1])
      bmax[1] = p[1];

    if (p[2] < bmin[2])
      bmin[2] = p[2];
    if (p[2] > bmax[2])
      bmax[2] = p[2];
  }

  center = 0.5 * (bmin + bmax);
  cubeHalf = 0.5 * (bmax - bmin);
  diameter = len(bmax - bmin);
}

void ObjMesh::getBoundingBox(double expansionRatio, Vec3d * bmin_, Vec3d * bmax_) const
{
  *bmin_ = center - expansionRatio * cubeHalf;
  *bmax_ = center + expansionRatio * cubeHalf;
}

void ObjMesh::getCubicBoundingBox(double expansionRatio, Vec3d * bmin_, Vec3d * bmax_) const
{
  double maxHalf = cubeHalf[0];

  if (cubeHalf[1] > maxHalf)
    maxHalf = cubeHalf[1];

  if (cubeHalf[2] > maxHalf)
    maxHalf = cubeHalf[2];

  Vec3d cubeHalfCube = Vec3d(maxHalf, maxHalf, maxHalf);

  *bmin_ = center - expansionRatio * cubeHalfCube;
  *bmax_ = center + expansionRatio * cubeHalfCube;
}

double ObjMesh::getDiameter() const
{
  return diameter;
}

int ObjMesh::saveObjMeshesToBinary(const std::string & filename, int numObjMeshes, ObjMesh ** objMeshes, int * saveObjMeshesFlag, int outputMaterials, int verbose)
{
  FILE * output = fopen(filename.c_str(), "wb");
  if (output == NULL)
  {
    printf("Error in ObjMesh::saveToBinary: cannot open %s to write.\n", filename.c_str());
    return 1;
  }

  unsigned int * bytesWritten = (unsigned int*) calloc (numObjMeshes, sizeof(unsigned int));

  // count the number of bytes written to the file for every obj mesh
  for(int i=0; i<numObjMeshes; i++)
  {
    if (saveObjMeshesFlag[i] == 0)
      continue;

    bool countBytesOnly = true;
    objMeshes[i]->saveToBinary(NULL, outputMaterials, &bytesWritten[i], countBytesOnly);
  }

  if (verbose)
  {
    printf("number of bytes for each obj mesh: \n");
    for(int i=0; i<numObjMeshes; i++)
      printf("%u, ", bytesWritten[i]);
    printf("\n");
  }

  // write the header to the file
  fwrite(&numObjMeshes, sizeof(int), 1, output);
  fwrite(bytesWritten, sizeof(unsigned int), numObjMeshes, output);

  // write the obj meshes to the file
  for(int i=0; i<numObjMeshes; i++)
  {
    if (saveObjMeshesFlag[i] == 0)
      continue;

    bool countBytesOnly = false;
    objMeshes[i]->saveToBinary(output, outputMaterials, &bytesWritten[i], countBytesOnly, verbose);
  }

  free(bytesWritten);
  fclose(output);

  return 0;
}

int ObjMesh::saveToBinary(const std::string & filename_, int outputMaterials, int verbose) const
{
  FILE * fout = fopen(filename_.c_str(), "wb");
  if (fout == NULL)
  {
    printf("Error in ObjMesh::saveToBinary: cannot open file %s to write.\n", filename_.c_str());
  }
  bool countBytesOnly = false;
  int code = saveToBinary(fout, outputMaterials, NULL, countBytesOnly, verbose);
  fclose(fout);
  return code;
}

// return:
// 0 = succeeded
// 1 = failed
int ObjMesh::saveToBinary(FILE * binaryOutputStream, int outputMaterials, unsigned int * bytesWritten, bool countBytesOnly, int verbose) const
{
  // first pass: count the total number of bytes to be written to the file
  // second pass: do the actual writing 
  enum {COUNT_BYTES, WRITE_TO_DISK, NUM_PASSES};
  int totalPasses = NUM_PASSES;
  if (countBytesOnly)
    totalPasses = WRITE_TO_DISK;

  unsigned int totalBytes = 0;
  for(int pass = 0; pass < totalPasses; pass++)
  {
    unsigned int bytes = 0;
    unsigned int items;

    // the header will be the number of bytes (including the totalbytes itself)
    items = 1;
    if (pass == WRITE_TO_DISK)
      items = fwrite(&totalBytes, sizeof(unsigned int), 1, binaryOutputStream);
    if (items != 1)
      return 1;
    bytes += items * sizeof(unsigned int);

    // save the flag that determines whether to output materials or not
    items = 1;
    if (pass == WRITE_TO_DISK)
      items = fwrite(&outputMaterials, sizeof(int), 1, binaryOutputStream);
    if (items != 1)
      return 1;
    bytes += items * sizeof(int);

    // save materials, if necessary
    if (outputMaterials)
    {
      unsigned int numObjMaterials = getNumMaterials();

      // save the number of materials
      items = 1;
      if (pass == WRITE_TO_DISK)
        items = fwrite(&numObjMaterials, sizeof(unsigned int), 1, binaryOutputStream);
      if (items != 1)
        return 1;
      bytes += items * sizeof(unsigned int);

      // save the material names
      for (unsigned int materialIndex=0; materialIndex < numObjMaterials; materialIndex++)
      {
        std::string materialNameString = materials[materialIndex].getName();
        char * materialName = (char *)(materialNameString.c_str());
        unsigned int strLength = strlen(materialName);
        items = 1;
        if (pass == WRITE_TO_DISK)
          items = fwrite(&strLength, sizeof(unsigned int), 1, binaryOutputStream);
        if (items != 1)
          return 1;
        bytes += items * sizeof(unsigned int);

        items = strLength;
        if (pass == WRITE_TO_DISK)
          items = fwrite(materialName, sizeof(char), strLength, binaryOutputStream);
        if (items != strLength)
          return 1;
        bytes += items * sizeof(char);
      }

      // Ka, Kd, Ks, each of which has 3 doubles, plus Ns, a double
      // So there are 10 doubles for every material
      enum {KA_0, KA_1, KA_3, KD_0, KD_1, KD_2, KS_0, KS_1, KS_2, NS, NUM_MATERIAL_PROPERTIES};
      double * materialProperties = (double *) malloc(sizeof(double) * NUM_MATERIAL_PROPERTIES * numObjMaterials);

      std::vector<unsigned int> materialHasTextureImageKd;

      for (unsigned int materialIndex=0; materialIndex < numObjMaterials; materialIndex++)
      {
        unsigned int offset = materialIndex * NUM_MATERIAL_PROPERTIES;

        Vec3d Ka = materials[materialIndex].getKa();
        Ka.convertToArray(&materialProperties[offset]);

        Vec3d Kd = materials[materialIndex].getKd();
        Kd.convertToArray(&materialProperties[offset + 3]);

        Vec3d Ks = materials[materialIndex].getKs();
        Ks.convertToArray(&materialProperties[offset + 6]);

        materialProperties[offset + 9] = materials[materialIndex].getShininess() * 1000.0 / 128.0;

        if (materials[materialIndex].hasTextureFilename())
          materialHasTextureImageKd.push_back(materialIndex);
      }  // for materialIndex

      // save the material properties
      items = NUM_MATERIAL_PROPERTIES * numObjMaterials;
      if (pass == WRITE_TO_DISK)
        items = fwrite(materialProperties, sizeof(double), NUM_MATERIAL_PROPERTIES * numObjMaterials, binaryOutputStream);
      if (items !=  NUM_MATERIAL_PROPERTIES * numObjMaterials)
        return 1;
      bytes += items * sizeof(double);

      free(materialProperties);

      // save the number of materials which have map_Kd texture images
      unsigned int vectorSize = materialHasTextureImageKd.size();
      items = 1;
      if (pass == WRITE_TO_DISK)
        items = fwrite(&vectorSize, sizeof(unsigned int), 1, binaryOutputStream);
      if (items != 1)
        return 1;
      bytes += items * sizeof(unsigned int);

      for(unsigned int materialIndex=0; materialIndex < vectorSize; materialIndex++)
      {
        // save the material ID
        unsigned int materialID = materialHasTextureImageKd[materialIndex];
        items = 1;
        if (pass == WRITE_TO_DISK)
          items = fwrite(&materialID, sizeof(unsigned int), 1, binaryOutputStream);
        if (items != 1)
          return 1;
        bytes += items * sizeof(unsigned int);

        // save the material image
        std::string textureFilenameString = materials[materialID].getTextureFilename();
        char * textureFilename = (char *)(textureFilenameString.c_str());
        unsigned int strLength = strlen(textureFilename);
        items = 1;
        if (pass == WRITE_TO_DISK)
          items = fwrite(&strLength, sizeof(unsigned int), 1, binaryOutputStream);
        if (items != 1)
          return 1;
        bytes += items * sizeof(unsigned int);

        items = strLength;
        if (pass == WRITE_TO_DISK)
          items = fwrite(textureFilename, sizeof(char), strLength, binaryOutputStream);
        if (items != strLength)
          return 1;
        bytes += items * sizeof(char);
      }  // for materialIndex
    }  // if outputMaterials

    // save the number of vertices
    unsigned int numVertices = vertexPositions.size();
    items = 1;
    if (pass == WRITE_TO_DISK)
      items = fwrite(&numVertices, sizeof(unsigned int), 1, binaryOutputStream);
    if (items != 1)
      return 1;
    bytes += items * sizeof(unsigned int);

    // save vertices
    for (unsigned int vertexIndex=0; vertexIndex < numVertices; vertexIndex++)
    {
      Vec3d pos = getPosition(vertexIndex);
      double temp[3];
      pos.convertToArray(temp);

      items = 3;
      if (pass == WRITE_TO_DISK)
        items = fwrite(temp, sizeof(double), 3, binaryOutputStream);
      if (items != 3)
        return 1;
      bytes += items * sizeof(double);
    }

    // save the number of texture coordinates
    unsigned int numTexCoordinates = textureCoordinates.size();
    items = 1;
    if (pass == WRITE_TO_DISK)
      items = fwrite(&numTexCoordinates, sizeof(unsigned int), 1, binaryOutputStream);
    if (items != 1)
      return 1;
    bytes += items * sizeof(unsigned int);

    // save texture coordinates
    for (unsigned int texCoordinateIndex=0; texCoordinateIndex < numTexCoordinates; texCoordinateIndex++)
    {
      Vec3d texCoord_ = getTextureCoordinate(texCoordinateIndex);
      double temp[3];
      texCoord_.convertToArray(temp);

      items = 3;
      if (pass == WRITE_TO_DISK)
        items = fwrite(temp, sizeof(double), 3, binaryOutputStream);
      if (items != 3)
        return 1;
      bytes += items * sizeof(double);
    }

    // save the number of normals
    unsigned int numNormals = normals.size();
    items = 1;
    if (pass == WRITE_TO_DISK)
      items = fwrite(&numNormals, sizeof(unsigned int), 1, binaryOutputStream);
    if (items != 1)
      return 1;
    bytes += items * sizeof(unsigned int);

    // save normals
    for (unsigned int normalIndex=0; normalIndex < numNormals; normalIndex++)
    {
      Vec3d normal_ = getNormal(normalIndex);
      double temp[3];
      normal_.convertToArray(temp);
      items = 3;
      if (pass == WRITE_TO_DISK)
        items = fwrite(temp, sizeof(double), 3, binaryOutputStream);
      if (items != 3)
        return 1;
      bytes += items * sizeof(double);
    }

    // save the number of groups
    unsigned int numGroups = groups.size();
    items = 1;
    if (pass == WRITE_TO_DISK)
      items = fwrite(&numGroups, sizeof(unsigned int), 1, binaryOutputStream);
    if (items != 1)
      return 1;
    bytes += items * sizeof(unsigned int);

    // save groups and faces
    for(unsigned int groupIndex=0; groupIndex < groups.size(); groupIndex++)
    {
      // save group name 
      std::string groupNameString = groups[groupIndex].getName();
      char * groupNameStr = (char *)(groupNameString.c_str());
      unsigned int strLength = strlen(groupNameStr);
      items = 1;
      if (pass == WRITE_TO_DISK)
        items = fwrite(&strLength, sizeof(unsigned int), 1, binaryOutputStream);
      if (items != 1)
        return 1;
      bytes += items * sizeof(unsigned int);


      items = strLength;
      if (pass == WRITE_TO_DISK)
        items = fwrite(groupNameStr, sizeof(char), strLength, binaryOutputStream);
      if (items != strLength)
        return 1;
      bytes += items * sizeof(char);

      // save the material index of the current group
      if (outputMaterials)
      {
        unsigned int materialIndex = groups[groupIndex].getMaterialIndex();
        items = 1;
        if (pass == WRITE_TO_DISK)
          items = fwrite(&materialIndex, sizeof(unsigned int), 1, binaryOutputStream);
        if (items != 1)
          return 1;
        bytes += items * sizeof(unsigned int);
      }

      // save the number of faces of the current group
      unsigned int numFaces = groups[groupIndex].getNumFaces();
      items = 1;
      if (pass == WRITE_TO_DISK)
        items = fwrite(&numFaces, sizeof(unsigned int), 1, binaryOutputStream);
      if (items != 1)
        return 1;
      bytes += items * sizeof(unsigned int);

      // save the number of vertices of each face in current group
      unsigned int totalFaceVertices = 0;
      unsigned int * numFaceVerticesArray = (unsigned int *) malloc (sizeof(unsigned int) * numFaces);
      for (unsigned int faceIndex=0; faceIndex < numFaces; faceIndex++)
      {
        Face face = groups[groupIndex].getFace(faceIndex); // get face whose number is faceIndex
        numFaceVerticesArray[faceIndex] = face.getNumVertices();
        totalFaceVertices += numFaceVerticesArray[faceIndex];
      }
      items = numFaces;
      if (pass == WRITE_TO_DISK)
        items = fwrite(numFaceVerticesArray, sizeof(unsigned int), numFaces, binaryOutputStream);
      if (items != numFaces)
        return 1;
      bytes += items * sizeof(unsigned int);
      free(numFaceVerticesArray);

      unsigned int * verticesArray = (unsigned int *) malloc (sizeof(unsigned int) * totalFaceVertices);
      // because the output is 1-indexed, we can use 0 to represent "no such property"
      unsigned int * textureCoordinateIndexArray = (unsigned *) malloc (sizeof(unsigned int) * totalFaceVertices);
      unsigned int * normalIndexArray = (unsigned *) malloc (sizeof(unsigned int) * totalFaceVertices);
      memset(textureCoordinateIndexArray, 0, sizeof(unsigned int) * totalFaceVertices);
      memset(normalIndexArray, 0, sizeof(unsigned int) * totalFaceVertices);
      unsigned int vertexCount = 0;
      for (unsigned int faceIndex=0; faceIndex < numFaces; faceIndex++)
      {
        Face face = groups[groupIndex].getFace(faceIndex); // get the face whose number is faceIndex
        unsigned int numFaceVertices = face.getNumVertices();

        // current face
        for (unsigned int vertexIndex=0; vertexIndex < numFaceVertices; vertexIndex++)
        {
          Vertex vertex = face.getVertex(vertexIndex);
          verticesArray[vertexCount] = vertex.getPositionIndex() + 1; // 1-indexed

          if (vertex.hasTextureCoordinateIndex())
            textureCoordinateIndexArray[vertexCount] = vertex.getTextureCoordinateIndex() + 1; // 1-indexed

          if (vertex.hasNormalIndex())
            normalIndexArray[vertexCount] = vertex.getNormalIndex() + 1; // 1-indexed

          vertexCount++;
        }  // for vertexIndex
      }  // for faceIndex

      // save the vertices of each face
      items = totalFaceVertices;
      if (pass == WRITE_TO_DISK)
        items = fwrite(verticesArray, sizeof(unsigned int), totalFaceVertices, binaryOutputStream);
      if (items != totalFaceVertices)
        return 1;
      bytes += items * sizeof(unsigned int);

      items = totalFaceVertices;
      if (pass == WRITE_TO_DISK)
        items = fwrite(textureCoordinateIndexArray, sizeof(unsigned int), totalFaceVertices, binaryOutputStream);
      if (items != totalFaceVertices)
        return 1;
      bytes += items * sizeof(unsigned int);

      items = totalFaceVertices;
      if (pass == WRITE_TO_DISK)
        items = fwrite(normalIndexArray, sizeof(unsigned int), totalFaceVertices, binaryOutputStream);
      if (items != totalFaceVertices)
        return 1;
      bytes += items * sizeof(unsigned int);

      free(verticesArray);
      free(textureCoordinateIndexArray);
      free(normalIndexArray);

    }  // for groupIndex

    if (pass == COUNT_BYTES)
      totalBytes = bytes;
  } // for pass

  if (bytesWritten != NULL)
    *bytesWritten = totalBytes;
  else
    if (countBytesOnly)
    {
      printf("Warning in ObjMesh::saveToBinary: 'bytesWritten' is set to NULL while 'countBytesOnly' is set true.\n");
      return 2;
    }
  
  return 0;
}

void ObjMesh::save(const string & filename, int outputMaterials, fileFormatType fileFormat, int verbose) const
{
  switch(fileFormat)
  {
    case ASCII:
      saveToAscii(filename, outputMaterials, verbose);
      break;
    
    case BINARY:
        saveToBinary(filename, outputMaterials, verbose);
      break;

    default:
      printf("Error in ObjMesh::save: file format is unknown.\n");
      break;
  }
}

void ObjMesh::saveToAscii(const string & filename, int outputMaterials, int verbose) const
{
  string materialFilename;
  string materialFilenameLocal;

  if (outputMaterials && (getNumMaterials() == 0))
    outputMaterials = 0;

  if (outputMaterials)
  {
    materialFilename = filename + ".mtl";
    // remove directory part from materialFilename
    char * materialFilenameTempC = (char*)materialFilename.c_str();
    char * beginString = materialFilenameTempC;
    // seek for last '/'
    for(unsigned int i=0; i< strlen(materialFilenameTempC); i++)
      if ((materialFilenameTempC[i] == '/') || (materialFilenameTempC[i] == '\\'))
        beginString = &materialFilenameTempC[i+1];

    materialFilenameLocal = string(beginString);
  }

  if (verbose >= 1)
  {
    cout << "Writing obj to file " << filename << " ." << endl;
    if (outputMaterials)
      cout << "Writing materials to " << materialFilename << " ." << endl;
    else
      cout << "No material output." << endl;
  }

  // open file
  ofstream fout(filename.c_str());

  if (!fout)
  {
    cout << "Error: could not write to file " << filename << endl;
    return;
  }

  // count total number of triangles
  int numTriangles = 0;
  for(unsigned int i = 0; i < groups.size(); i++ )
    numTriangles += groups[i].getNumFaces();

  fout << "# Generated by the ObjMesh class" << endl;
  fout << "# Number of vertices: " << vertexPositions.size() << endl;
  fout << "# Number of texture coordinates: " << textureCoordinates.size() << endl;
  fout << "# Number of normals: " << normals.size() << endl;
  fout << "# Number of faces: " << numTriangles << endl;
  fout << "# Number of groups: " << groups.size() << endl;

  if (outputMaterials)
    fout << endl << "mtllib " << materialFilenameLocal << endl << endl;

  // vertices...
  for (unsigned int i=0; i < vertexPositions.size(); i++)
  {
    Vec3d pos = getPosition(i);
    fout << "v " << pos[0] << " " << pos[1] << " " << pos[2] << endl; 
  }

  // texture coordinates...
  for (unsigned int i=0; i < textureCoordinates.size(); i++)
  {
    Vec3d texCoord_ = getTextureCoordinate(i);
    fout << "vt " << texCoord_[0] << " " << texCoord_[1] << endl; 
  }

  // normals...
  for (unsigned int i=0; i < normals.size(); i++)
  {
    Vec3d normal_ = getNormal(i);
    fout << "vn " << normal_[0] << " " << normal_[1] << " " << normal_[2] << endl; 
  }

  // groups and faces...
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    fout << "g " << groups[i].getName() << endl;
    if (outputMaterials)
      fout << "usemtl " << materials[groups[i].getMaterialIndex()].getName() << endl;

    for( unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      Face face = groups[i].getFace(iFace); // get face whose number is iFace

      fout << "f";   

      if (face.getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for ( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
      {
        Vertex vertex = face.getVertex(iVertex);
        fout << " " << int(vertex.getPositionIndex() + 1);

        if (vertex.hasTextureCoordinateIndex() || vertex.hasNormalIndex())
        {
          fout << "/";

          if (vertex.hasTextureCoordinateIndex())
            fout << int(vertex.getTextureCoordinateIndex() + 1);
    
          if (vertex.hasNormalIndex())
          {
            fout << "/";
    
            if (vertex.hasNormalIndex())
              fout << int(vertex.getNormalIndex() + 1);
          }
        }
      }

      fout << endl;
    }
  }

  fout.close(); 

  if (outputMaterials)
  {
    ofstream fout(materialFilename.c_str());

    if (!fout)
    {
      cout << "Error: could not write to file " << materialFilename << endl;
      return;
    }

    for(unsigned int i=0; i< getNumMaterials(); i++)
    {
      fout << "newmtl " << materials[i].getName() << endl;
      fout << "illum 4" << endl;

      Vec3d Ka = materials[i].getKa();
      Vec3d Kd = materials[i].getKd();
      Vec3d Ks = materials[i].getKs();
      double shininess = materials[i].getShininess() * 1000.0 / 128.0;

      fout << "Ka " << Ka[0] << " " << Ka[1] << " " << Ka[2] << endl;
      fout << "Kd " << Kd[0] << " " << Kd[1] << " " << Kd[2] << endl;
      fout << "Ks " << Ks[0] << " " << Ks[1] << " " << Ks[2] << endl;
      fout << "Ns " << shininess << endl;
      if (materials[i].hasTextureFilename())
      {
        std::string textureFilename = materials[i].getTextureFilename();
        fout << "map_Kd " << textureFilename << endl;
      }
      fout << endl;
    }

    fout.close();
  }
}

void ObjMesh::saveToAbq(const string & filename) const
{
  cout << "Writing obj to abq file " << filename << " ." << endl;

  if (computeMaxFaceDegree() > 4)
  {
    cout << "Error: mesh has faces with more than 4 vertices." << endl;
    return;
  } 

  vector<double> surfaceAreas ;
  computeSurfaceAreaPerGroup(surfaceAreas);
  for(unsigned int i=0; i<surfaceAreas.size(); i++)
  {
    printf("Surface area of group %d: %G\n",i,surfaceAreas[i]);
  }

  // open file
  FILE * fout = fopen(filename.c_str(),"w");

  if (!fout)
  {
    cout << "Error: could not write to file " << filename << endl;
    return;
  }

  // vertices...
  fprintf(fout, "*NODE\n");
  for (unsigned int i=0; i < vertexPositions.size(); i++)
  {
    Vec3d pos = getPosition(i);
    fprintf(fout,"   %d,   %.15f,   %.15f,   %.15f\n",i+1,pos[0],pos[1],pos[2]);
  }

  // groups and faces...
  int faceCount=0;
  vector<int> startIndex; // for generation of element sets
  vector<int> endIndex;
  vector<std::string> groupNames;
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    printf("Num faces in group %d: %d\n",i+1,(int)(groups[i].getNumFaces()));
 
    if (groups[i].getNumFaces() == 0)
      continue;

    startIndex.push_back(faceCount+1);
    groupNames.push_back(groups[i].getName());

    // two passes: triangles and quads
    for(unsigned int numFaceVertices=3; numFaceVertices<=4; numFaceVertices++)
    {
      bool firstElement = true;
      for( unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
      {
        Face face = groups[i].getFace(iFace); // get face whose number is iFace

        if (face.getNumVertices() != numFaceVertices)
          continue;

        if (firstElement)
        {
          fprintf(fout,"*ELEMENT, TYPE=S%d\n",numFaceVertices);
          firstElement = false;
        }

        faceCount++;
        fprintf(fout,"%d   ",faceCount);

        for ( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
        {
          Vertex vertex = face.getVertex(iVertex);
          fprintf(fout,",%d",vertex.getPositionIndex() + 1);
        }
                                                                                                                                                             
        fprintf(fout,"\n");
      }
    }

    endIndex.push_back(faceCount);
  }
  
  for(unsigned int i=0; i<startIndex.size(); i++)
  {
    fprintf(fout,"*ELSET,ELSET=%s,GENERATE\n",groupNames[i].c_str());
    fprintf(fout,"  %d,%d\n",startIndex[i],endIndex[i]);
  }

  fprintf(fout,"*ELSET,ELSET=EALL,GENERATE\n");
  fprintf(fout,"  1,%d\n",faceCount);

  fclose(fout);
}

void ObjMesh::saveToStl(const string & filename) const
{
  cout << "Writing obj to STL file " << filename << " ." << endl;

  // open file
  ofstream fout(filename.c_str());

  if (!fout)
  {
    cout << "Error: could not write to file " << filename << endl;
    return;
  }

  // check if mesh is triangular
  if (!isTriangularMesh())
  {
    cout << "Error: input mesh is not triangular. " << endl;
    return;
  }

  // count total number of triangles
  int numTriangles = 0;
  for(unsigned int i = 0; i < groups.size(); i++ )
    numTriangles += groups[i].getNumFaces();

  fout << "# Generated automatically by the ObjMesh class" << endl;
  fout << "# Number of vertices: " << vertexPositions.size() << endl;
  fout << "# Number of faces: " << numTriangles << endl;


  fout << "solid" << endl;

  // groups and faces...
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for( unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      fout << "  facet normal ";

      // get the face data
      Vertex v0 = face.getVertex(0);
      Vertex v1 = face.getVertex(1);
      Vertex v2 = face.getVertex(2);

      Vec3d p0 = getPosition(v0);
      Vec3d p1 = getPosition(v1);
      Vec3d p2 = getPosition(v2);

      // compute the face normal
      Vec3d normal = norm(cross(p1-p0,p2-p0));

      fout << normal[0] << " " << normal[1] << " " << normal[2] << endl;

      fout << "    outer loop" << endl;

      fout << "      vertex " << p0[0] << " " << p0[1] << " " << p0[2] << endl;
      fout << "      vertex " << p1[0] << " " << p1[1] << " " << p1[2] << endl;
      fout << "      vertex " << p2[0] << " " << p2[1] << " " << p2[2] << endl;

      fout << "    endloop" << endl;
      fout << "  endfacet" << endl;

    }
  }

  fout << "endsolid" << endl;

  fout.close();
}

void ObjMesh::saveToSmesh(const std::string & filename) const
{
  cout << "Writing obj to smesh file " << filename << " ." << endl;

  // open file
  ofstream fout(filename.c_str());

  if (!fout)
  {
    cout << "Error: could not write to file " << filename << endl;
    return;
  }

  fout << getNumVertices() << " 3 0 0" << endl;

  // write out vertices
  for(unsigned int i=0; i< getNumVertices(); i++)
  {
    Vec3d p = getPosition(i);
    fout << i+1 << " " << p[0] << " " << p[1] << " " << p[2] << endl;
  }

  // count total number of faces
  int numFaces = 0;
  for(unsigned int i = 0; i < groups.size(); i++ )
    numFaces += groups[i].getNumFaces();

  fout << endl;
  fout << numFaces << " 0" << endl;

  // groups and faces...
  for(unsigned int i = 0; i < groups.size(); i++ )
    for( unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      Face face = groups[i].getFace(iFace); // get face whose number is iFace
      fout << face.getNumVertices();
      for(unsigned int j=0; j<face.getNumVertices(); j++)
      {
        // get the face data
        Vertex v = face.getVertex(j);
        fout << " " << v.getPositionIndex() + 1;
      }
      fout << endl;
    }

  fout << endl;
  fout << "0" << endl;
  fout << "0" << endl;
  fout.close();
}

ObjMesh * ObjMesh::splitIntoConnectedComponents(int withinGroupsOnly, int verbose) const
{
  // withinGroupsOnly:
  // 0: off (global split; may fuse texture coordinates)
  // 1: intersect global connected components with groups
  // 2: break each group into connected components, regardless of the rest of the mesh

  vector<DisjointSet*> dset;
  if (withinGroupsOnly == 2)
  {
    for(unsigned int i=0; i < groups.size(); i++) // over all groups
    {
      DisjointSet * groupDisjointSet = new DisjointSet(getNumVertices());
      groupDisjointSet->MakeSet();
      dset.push_back(groupDisjointSet);
    }
  }
  else
  {
    DisjointSet * globalDisjointSet = new DisjointSet(getNumVertices());
    globalDisjointSet->MakeSet();
    for(unsigned int i=0; i < groups.size(); i++) // over all groups
      dset.push_back(globalDisjointSet);
  }

  // build vertex connections
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
  {
    // if (verbose == 0)
    // {
    //   printf("%d ", i);
    //   fflush(NULL);
    // }

    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      if (verbose)
      {
        if (j % 100 == 1)
          printf("Processing group %d / %d, face %d / %d.\n", i, (int)groups.size(), j, (int)groups[i].getNumFaces()); 
      }
      const Face * face = groups[i].getFaceHandle(j);
      int faceDegree = (int)face->getNumVertices();
      for(int vtx=0; vtx<faceDegree-1; vtx++)
      {
        int vertex = face->getVertex(vtx).getPositionIndex();
        int vertexNext = face->getVertex(vtx+1).getPositionIndex();
        dset[i]->UnionSet(vertex, vertexNext);
      }
    }
  }
  // if (verbose == 0)
  //   printf("\n");

  // determine group for every face
  int numOutputGroups = 0;
  vector<map<int, int> *> representatives;
  if (withinGroupsOnly == 2)
  {
    for(unsigned int i=0; i < groups.size(); i++) // over all groups
    {
      map<int, int> * groupMap = new map<int,int>();
      representatives.push_back(groupMap);
    }
  }
  else
  {
    map<int, int> * globalMap = new map<int,int>();
    for(unsigned int i=0; i < groups.size(); i++) // over all groups
      representatives.push_back(globalMap);
  }

  vector<vector<int> > faceGroup;
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
  {
    // if (verbose == 0)
    // {
    //   printf("%d ", i);
    //   fflush(NULL);
    // }

    faceGroup.push_back(vector<int>());
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      if (verbose)
      {
        if (j % 100 == 1)
          printf("Processing group %d / %d, face %d / %d.\n", i, (int)groups.size(), j, (int)groups[i].getNumFaces()); 
      }
      const Face * face = groups[i].getFaceHandle(j);
      int rep = dset[i]->FindSet(face->getVertex(0).getPositionIndex());

      map<int,int> :: iterator iter = representatives[i]->find(rep);
      int groupID;
      if (iter == representatives[i]->end())
      {
        groupID = numOutputGroups;
        representatives[i]->insert(make_pair(rep, numOutputGroups));
        numOutputGroups++;
      }
      else
        groupID = iter->second;

      faceGroup[i].push_back(groupID);
    }
  }

  // if (verbose == 0)
  //   printf("\n");

  // build output mesh
  ObjMesh * output = new ObjMesh();

  // output vertices
  for(unsigned int i=0; i<getNumVertices(); i++)
    output->addVertexPosition(getPosition(i));

  // output normals
  for(unsigned int i=0; i<getNumNormals(); i++)
    output->addVertexNormal(getNormal(i));

  // output texture coordinates
  for(unsigned int i=0; i<getNumTextureCoordinates(); i++)
    output->addTextureCoordinate(getTextureCoordinate(i));

  // output materials
  for(unsigned int i=0; i<getNumMaterials(); i++)
    output->addMaterial(getMaterial(i));

  // create output groups, taking into account potential splitting in case: withinGroupsOnly == 1
  int groupCount = 0;
  map <pair<int, int>, int> outputGroup;
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
  {
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      int groupID = faceGroup[i][j];
      if (withinGroupsOnly == 1)
      {
        if (outputGroup.find(make_pair(i, groupID)) == outputGroup.end())
        {
          outputGroup.insert(make_pair(make_pair(i, groupID), groupCount));
          groupCount++;
        }
      }
      else
      {
        outputGroup.insert(make_pair(make_pair(i, groupID), groupID));
      }
    }
  }

  if (withinGroupsOnly == 1)
    numOutputGroups = groupCount;

  // create groups
  for(int i=0; i<numOutputGroups; i++)
  {
    char s[96];
    sprintf(s, "group%05d", i);
    output->addGroup(string(s));
  }

  // add faces to groups
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
  {
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      int connectedGroupID = faceGroup[i][j];

      map<pair<int,int>, int> :: iterator iter = outputGroup.find(make_pair(i, connectedGroupID));
      if (iter == outputGroup.end())
      {
        printf("Error: encountered unhandled (input group, connected group) case.\n");
      }
      int groupID = iter->second;

      output->addFaceToGroup(*face, groupID);

      // set the material for this group
      Group * outputGroupHandle = (Group*) output->getGroupHandle(groupID);
      outputGroupHandle->setMaterialIndex(groups[i].getMaterialIndex());
    }
  }

  output->computeBoundingBox();

  // de-allocate
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
  {
    delete(representatives[i]);
    representatives[i] = NULL;
    delete(dset[i]);
    dset[i] = NULL;

    if (withinGroupsOnly != 2)
      break;
  }

  return output;
}

ObjMesh * ObjMesh::clone(const std::vector<std::pair<int, int> > & groupsAndFaces, int removeIsolatedVertices) const
{
  ObjMesh * output = new ObjMesh();
  output->materials = materials;
  output->vertexPositions = vertexPositions;
  output->textureCoordinates = textureCoordinates;
  output->normals = normals;

  for(int i=0; i<(int)getNumGroups(); i++)
  {
    Group group(groups[i].getName(), groups[i].getMaterialIndex());
    output->addGroup(group);
  }

  for(std::vector<std::pair<int, int> > :: const_iterator iter = groupsAndFaces.begin(); iter != groupsAndFaces.end(); iter++)
    output->groups[iter->first].addFace(groups[iter->first].getFace(iter->second));

  if (removeIsolatedVertices)
    output->removeIsolatedVertices();

  return output;
}

// extracts the given group
ObjMesh * ObjMesh::extractGroup(unsigned int groupID, int keepOnlyUsedNormals, int keepOnlyUsedTextureCoordinates) const
{
  map<int,int> oldToNewVertices;
  map<int,int> newToOldVertices;

  map<int,int> oldToNewNormals;
  map<int,int> newToOldNormals;

  map<int,int> oldToNewTextureCoordinates;
  map<int,int> newToOldTextureCoordinates;

  int numGroupVertices = 0;
  int numGroupNormals = 0;
  int numGroupTextureCoordinates = 0;

  // establish new vertices, normals and texture coordinates
  for (unsigned int j=0; j < groups[groupID].getNumFaces(); j++) // over all faces
  {
    const Face * face = groups[groupID].getFaceHandle(j);
    int faceDegree = (int)face->getNumVertices();
    for(int vtx=0; vtx<faceDegree; vtx++)
    {
      int vertex = face->getVertex(vtx).getPositionIndex();
      if (oldToNewVertices.find(vertex) == oldToNewVertices.end())
      {
        oldToNewVertices.insert(make_pair(vertex, numGroupVertices));
        newToOldVertices.insert(make_pair(numGroupVertices, vertex));
        numGroupVertices++;
      }

      if (face->getVertex(vtx).hasNormalIndex())
      {
        int normalIndex = face->getVertex(vtx).getNormalIndex();
        if (oldToNewNormals.find(normalIndex) == oldToNewNormals.end())
        {
          oldToNewNormals.insert(make_pair(normalIndex, numGroupNormals));
          newToOldNormals.insert(make_pair(numGroupNormals, normalIndex));
          numGroupNormals++;
        }
      }

      if (face->getVertex(vtx).hasTextureCoordinateIndex())
      {
        int textureCoordinateIndex = face->getVertex(vtx).getTextureCoordinateIndex();
        if (oldToNewTextureCoordinates.find(textureCoordinateIndex) == oldToNewTextureCoordinates.end())
        {
          oldToNewTextureCoordinates.insert(make_pair(textureCoordinateIndex, numGroupTextureCoordinates));
          newToOldTextureCoordinates.insert(make_pair(numGroupTextureCoordinates, textureCoordinateIndex));
          numGroupTextureCoordinates++;
        }
      }
    }
  }

  ObjMesh * output = new ObjMesh();

  // output vertices
  for(int i=0; i<numGroupVertices; i++)
    output->addVertexPosition(getPosition(newToOldVertices[i]));

  // output normals
  if (keepOnlyUsedNormals)
  {
    for(int i=0; i<numGroupNormals; i++)
      output->addVertexNormal(getNormal(newToOldNormals[i]));
  }
  else
  {
    for(unsigned int i=0; i<getNumNormals(); i++)
      output->addVertexNormal(getNormal(i));
  }

  // output texture coordinates
  if (keepOnlyUsedTextureCoordinates)
  {
    for(int i=0; i<numGroupTextureCoordinates; i++)
      output->addTextureCoordinate(getTextureCoordinate(newToOldTextureCoordinates[i]));
  }
  else
  {
    for(unsigned int i=0; i<getNumTextureCoordinates(); i++)
      output->addTextureCoordinate(getTextureCoordinate(i));
  }

  // output materials
  for(unsigned int i=0; i<getNumMaterials(); i++)
    output->addMaterial(getMaterial(i));

  // add a single group
  char s[4096];
  //sprintf(s, "group%05d", groupID);
  sprintf(s, "%s", groups[groupID].getName().c_str());
  output->addGroup(s);

  // set material for the extracted group
  //unsigned int newGroupIndex = output->groups.size() - 1;
  //if (newGroupIndex < 0)
  //{
  //  printf("Error: failed to add a new group to the mesh.\n");
  //  exit(0);
  //}
  if (output->groups.size() == 0)
  {
    printf("Error: failed to add a new group to the mesh.\n");
    exit(0);
  }
  unsigned int newGroupIndex = output->groups.size() - 1;

  output->groups[newGroupIndex].setMaterialIndex(groups[groupID].getMaterialIndex());

  // add faces to the group
  for (unsigned int j=0; j < groups[groupID].getNumFaces(); j++) // over all faces
  {
    const Face * face = groups[groupID].getFaceHandle(j);
    Face newFace;
    int faceDegree = (int)face->getNumVertices();
    for(int vtx=0; vtx<faceDegree; vtx++)
    {
      int oldVertexIndex = face->getVertex(vtx).getPositionIndex();
      int newVertexIndex = oldToNewVertices[oldVertexIndex];
      Vertex newVertex = face->getVertex(vtx);
      newVertex.setPositionIndex(newVertexIndex);

      if (newVertex.hasNormalIndex() && keepOnlyUsedNormals)
      { 
        int oldNormalIndex = face->getVertex(vtx).getNormalIndex();
        int newNormalIndex = oldToNewNormals[oldNormalIndex];
        newVertex.setNormalIndex(newNormalIndex);
      }

      if (newVertex.hasTextureCoordinateIndex() && keepOnlyUsedTextureCoordinates)
      {
        int oldTextureCoordinateIndex = face->getVertex(vtx).getTextureCoordinateIndex();
        int newTextureCoordinateIndex = oldToNewTextureCoordinates[oldTextureCoordinateIndex];
        newVertex.setTextureCoordinateIndex(newTextureCoordinateIndex);
      }

      newFace.addVertex(newVertex);      
    }
    output->addFaceToGroup(newFace, 0);
  }

  output->computeBoundingBox();
  return output;
}

double ObjMesh::computeTriangleSurfaceArea(Vec3d & p0, Vec3d & p1, Vec3d & p2)
{
  return 0.5 * (len(cross(p1-p0, p2-p0)));
}

void ObjMesh::computeCentroids(std::vector<Vec3d> & centroids) const
{
  interpolateToCentroids(vertexPositions, centroids);
}
                                                                                                                                                             
void ObjMesh::interpolateToCentroids(const std::vector<double> & nodalData, std::vector<double> & centroidData) const
{
  int faceIndex = 0;
  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      double data = 0;
      for (unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++)
      {
        unsigned int index = face.getVertex(iVertex).getPositionIndex();
        data += nodalData[index];
      }

      data /= face.getNumVertices();
      centroidData[faceIndex] = data;

      faceIndex++;
    }
  }
}

void ObjMesh::interpolateToCentroids(const std::vector<Vec3d> & nodalData, std::vector<Vec3d> & centroidData) const
{
  int faceIndex = 0;
  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++)
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      Vec3d data(0,0,0);
      for (unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++)
      {
        unsigned int index = face.getVertex(iVertex).getPositionIndex();
        data += nodalData[index];
      }

      data /= face.getNumVertices();
      centroidData[faceIndex] = data;

      faceIndex++;
    }
  }
}

void ObjMesh::computeSurfaceAreaPerVertex()
{
  for (unsigned int i=0; i < getNumVertices(); i++)
    surfaceAreaPerVertex.push_back(0);

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++)
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++)
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      double faceSurfaceArea = computeFaceSurfaceArea(face);

      for (unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++)
      {
        unsigned int index = face.getVertex(iVertex).getPositionIndex();
        surfaceAreaPerVertex[index] += faceSurfaceArea / face.getNumVertices(); // each vertex owns an equal share of the face
      }
    }
  }
}

void ObjMesh::scaleUniformly(const Vec3d & center, double factor)
{
  for (unsigned int i=0; i < vertexPositions.size(); i++) // over all vertices
    vertexPositions[i] = center + factor * (vertexPositions[i] - center);

  computeBoundingBox();
}

void ObjMesh::transformRigidly(const Vec3d & translation, const Mat3d & rotation)
{
  for (unsigned int i=0; i < vertexPositions.size(); i++) // over all vertices
  {
    Vec3d rotatedPosition = rotation * vertexPositions[i];
    vertexPositions[i] = rotatedPosition + translation;
  }

  for (unsigned int i=0; i < normals.size(); i++) // over all normals
  {
    Vec3d rotatedNormal = rotation * normals[i];
    normals[i] = rotatedNormal;
  }

  computeBoundingBox();
}

void ObjMesh::deform(double * u)
{
  for (unsigned int i=0; i < vertexPositions.size(); i++) // over all vertices
    vertexPositions[i] += Vec3d(&u[3*i]);
  
  computeBoundingBox();
}

double ObjMesh::computeVolume() const
{
  double volume = 0;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      for (unsigned int iVertex = 0; iVertex < face.getNumVertices() - 2; iVertex++)
      {
        // base vertex
        Vec3d v0 = getPosition(face.getVertex(0));
        Vec3d v1 = getPosition(face.getVertex(iVertex+1));
        Vec3d v2 = getPosition(face.getVertex(iVertex+2));

        Vec3d normal = cross(v1-v0, v2-v0);
        Vec3d center = 1.0 / 3 * (v0 + v1 + v2);

        volume += dot(normal, center);
      }
    }
  }
  
  volume /= 6.0;
  
  return volume;
}

Vec3d ObjMesh::computeCenterOfMass_Vertices() const
{
  Vec3d center(0,0,0);
  for (unsigned int i=0; i < vertexPositions.size(); i++) // over all vertices
    center += vertexPositions[i];
  center /= vertexPositions.size();
  return center;
}

Vec3d ObjMesh::computeCenterOfMass_Triangles(const vector<double> & groupDensities) const
{
  Vec3d centerOfMass = 0.0;
  double totalMass=0.0;
  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    double density = groupDensities[i];
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      double area = computeFaceSurfaceArea(face);
      double mass = density * area;
      totalMass += mass;
      Vec3d centroid = computeFaceCentroid(face);       
      centerOfMass += mass * centroid;
    }
  }
  centerOfMass /= totalMass;
  return centerOfMass;
}

void ObjMesh::computeInertiaTensor_Triangles(double IT[6]) const
{
  double surfaceMassDensity = 1.0;
  vector<double> groupDensities;
  for(unsigned int i=0; i<groups.size(); i++)
    groupDensities.push_back(surfaceMassDensity);
  computeInertiaTensor_Triangles(groupDensities, IT);
}

void ObjMesh::computeInertiaTensor_Triangles(double mass, double IT[6]) const
{
  double surface = computeSurfaceArea();
  double surfaceMassDensity = mass / surface;
  vector<double> groupDensities;
  for(unsigned int i=0; i<groups.size(); i++)
    groupDensities.push_back(surfaceMassDensity);
  computeInertiaTensor_Triangles(groupDensities, IT);
}

double ObjMesh::computeMass(const vector<double> & groupDensities) const
{
  double totalMass = 0.0;
  // over all faces
  for(unsigned int i=0; i < groups.size(); i++)
  {
    double density = groupDensities[i];
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than three vertices.\n");
        continue;
      }

      double area = computeFaceSurfaceArea(face);
      double mass = density * area;
      totalMass += mass;
    }
  }
  
  return totalMass;
}

void ObjMesh::computeInertiaTensor_Triangles(const vector<double> & groupDensities, double IT[6]) const
{
  Vec3d centerOfMass = 0.0;
  memset(IT, 0, sizeof(double) * 6);
  double totalMass=0.0;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++)
  {
    double density = groupDensities[i];
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++)
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than three vertices.\n");
        continue;
      }

      double area = computeFaceSurfaceArea(face);
      double mass = density * area;
      totalMass += mass;
      Vec3d centroid = computeFaceCentroid(face);       
      centerOfMass += mass * centroid;

      Vec3d v0 = getPosition(face.getVertex(0)); 
      for (unsigned int iVertex = 1; iVertex < face.getNumVertices()-1; iVertex++ )
      {
        Vec3d v1 = getPosition(face.getVertex(iVertex));
        Vec3d v2 = getPosition(face.getVertex(iVertex + 1));
        double ITTriangle[6];
        computeSpecificInertiaTensor(v0, v1, v2, ITTriangle);

        double triangleArea = 0.5 * len(cross(v1-v0, v2-v0));
        for(int j=0; j<6; j++)
          IT[j] += triangleArea * density * ITTriangle[j];
      }
    }
  }
  
  centerOfMass /= totalMass;

  // IT is now the center around the origin  
  // transfer tensor to the center of mass
  double a = centerOfMass[0];
  double b = centerOfMass[1];
  double c = centerOfMass[2];

  double correction[6] = 
       { b*b + c*c, -a*b, -a*c,
               a*a + c*c, -b*c,
                     a*a + b*b };
                                                                                                                                                             
  for(int i=0; i<6; i++)
    IT[i] -= totalMass * correction[i];

}

Vec3d ObjMesh::computeCenterOfMass_Triangles() const
{
  Vec3d centerOfMass = 0.0;

  double totalArea=0.0;
  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      double area = computeFaceSurfaceArea(face);
      totalArea += area;
      Vec3d centroid = computeFaceCentroid(face);       
      centerOfMass += area * centroid;
    }
  }
  
  centerOfMass /= totalArea;
  
  return centerOfMass;
}

void ObjMesh::computeFaceSurfaceAreas(vector<double> & surfaceAreas) const
{
  int faceIndex = 0;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace
      surfaceAreas[faceIndex] = computeFaceSurfaceArea(face);
      faceIndex++;
    }
  }
}

double ObjMesh::computeSurfaceArea() const
{
  double area = 0;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace
      area += computeFaceSurfaceArea(face);
    }
  }
  
  return area;
}

void ObjMesh::computeSurfaceAreaPerGroup(vector<double> & surfaceAreas) const
{
  surfaceAreas.clear();

  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    double area = 0;
    // over all faces
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace
      area += computeFaceSurfaceArea(face);
    }

    surfaceAreas.push_back(area);
  }

}

void ObjMesh::computeMassPerVertex(const vector<double> & groupSurfaceMassDensity, vector<double> & masses) const
{
  masses.clear();
  for(unsigned int i=0; i<getNumVertices(); i++)
    masses.push_back(0.0);

  for(unsigned int i = 0; i < groups.size(); i++)
  {
    // over all faces
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++)
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace
      double faceSurfaceArea = computeFaceSurfaceArea(face);
      for ( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
        masses[face.getVertex(iVertex).getPositionIndex()] += groupSurfaceMassDensity[i] * faceSurfaceArea / face.getNumVertices();
    }
  }
}

// warning: normal is computed using the first three face vertices (assumes planar face)
Vec3d ObjMesh::computeFaceNormal(const Face & face) const
{
  // the three vertices
  Vec3d pos0 = getPosition(face.getVertex(0));
  Vec3d pos1 = getPosition(face.getVertex(1));
  Vec3d pos2 = getPosition(face.getVertex(2));
  Vec3d normal = norm(cross(pos1 - pos0, pos2 - pos0));

  if (isNaN(normal[0]) || isNaN(normal[1]) || isNaN(normal[2]))
  {
    //degenerate geometry; return an arbitrary normal
    normal = Vec3d(1.0, 0.0, 0.0);
  }

  return normal;
}

void ObjMesh::buildFaceNormals()
{
  for(unsigned int i = 0; i < groups.size(); i++)
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++)
    {
      ObjMesh::Face * faceHandle = (Face*) groups[i].getFaceHandle(iFace); // get face whose number is iFace

      if (faceHandle->getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      Vec3d normal = computeFaceNormal(*faceHandle);
      faceHandle->setFaceNormal(normal);
    }
  }
}

void ObjMesh::setNormalsToFaceNormals()
{
  // over all faces
  normals.clear();
  for(unsigned int i=0; i < groups.size(); i++)
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++)
    {
      const ObjMesh::Face * faceHandle = groups[i].getFaceHandle(iFace); // get face whose number is iFace

      if (faceHandle->getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      if (faceHandle->hasFaceNormal())
        addVertexNormal(faceHandle->getFaceNormal());
      else
        addVertexNormal(computeFaceNormal(*faceHandle));

      // over all vertices of the face
      for (unsigned k=0; k<faceHandle->getNumVertices(); k++)
      {
        Vertex * vertex = (Vertex*) faceHandle->getVertexHandle(k);
        vertex->setNormalIndex(getNumNormals() - 1);
      }
    }
  }
}

void ObjMesh::setNormalsToAverageFaceNormals()
{
  vector<Vec3d> normalBuffer(getNumVertices(),Vec3d(0,0,0));
  vector<unsigned int> normalCount(getNumVertices(),0);

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      // the three vertices
      unsigned int index0 = face.getVertex(0).getPositionIndex();
      unsigned int index1 = face.getVertex(1).getPositionIndex();
      unsigned int index2 = face.getVertex(2).getPositionIndex();

      Vec3d pos0 = getPosition(index0);
      Vec3d pos1 = getPosition(index1);
      Vec3d pos2 = getPosition(index2);

      Vec3d normal = norm(cross(pos1-pos0,pos2-pos0));
      // this works even for non-triangle meshes

      normalBuffer[index0] += normal;
      normalBuffer[index1] += normal;
      normalBuffer[index2] += normal;

      normalCount[index0]++;
      normalCount[index1]++;
      normalCount[index2]++;

    }
  }

  bool errorMessageSeen=false;
  // normalize the normals
  for (unsigned int i=0; i < getNumVertices(); i++)
  {
    if (normalCount[i] == 0)
    {
      if (!errorMessageSeen)
        cout << "Warning: encountered a vertex not belonging to any triangle (suppressing further warnings)" << endl;
      errorMessageSeen = true;
      normalBuffer[i] = Vec3d(1,0,0); // assign some bogus normal
    }
    else
      normalBuffer[i] = norm(normalBuffer[i]);
  }

  // register new normals with the objMesh data structure
  normals.clear();
  for (unsigned int i=0; i < getNumVertices(); i++)
    addVertexNormal(normalBuffer[i]);     

  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    Group * group = &(groups[i]);
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      const Face * face = group->getFaceHandle(iFace);

      if (face->getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for (unsigned k=0; k<face->getNumVertices(); k++)
      {
        Vertex * vertex = (Vertex*) face->getVertexHandle(k);
        vertex->setNormalIndex(vertex->getPositionIndex());
      }
    }
  }
}

unsigned int ObjMesh::getClosestVertex(const Vec3d & queryPos, double * distance) const
{
  double closestDist2 = DBL_MAX;
  double candidateDist2;
  unsigned int indexClosest = 0;
  for(unsigned int i=0; i< getNumVertices(); i++)
  {
    Vec3d relPos = getPosition(i) - queryPos;
    if ((candidateDist2 = dot(relPos,relPos)) < closestDist2)
    {
      closestDist2 = candidateDist2;
      indexClosest = i;
    } 
  }

  if (distance != NULL)
    *distance = sqrt(closestDist2);
  return indexClosest;
}

double ObjMesh::computeMinEdgeLength() const
{
  double minLength = -1;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
	cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for (unsigned k=0; k<face.getNumVertices(); k++)
      {
        Vec3d pos0 = getPosition(face.getVertex(k));
        Vec3d pos1 = getPosition(face.getVertex((k+1) % face.getNumVertices()));
        double length = len(pos1-pos0);

        if (minLength < 0) // only the first time
          minLength = length;
        else if (length < minLength)
          minLength = length;
      }
    }
  }
  
  return minLength;

}

double ObjMesh::computeAverageEdgeLength() const
{
  double totalLength = 0.0;
  int numEdges = 0;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
	cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for (unsigned k=0; k<face.getNumVertices(); k++)
      {
        Vec3d pos0 = getPosition(face.getVertex(k));
        Vec3d pos1 = getPosition(face.getVertex((k+1) % face.getNumVertices()));
        double length = len(pos1-pos0);
        totalLength += length;
        numEdges++;
      }
    }
  }
  
  return totalLength/numEdges;
}

double ObjMesh::computeMedianEdgeLength() const
{
  vector<double> lengths;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
	cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for (unsigned k=0; k<face.getNumVertices(); k++)
      {
        Vec3d pos0 = getPosition(face.getVertex(k));
        Vec3d pos1 = getPosition(face.getVertex((k+1) % face.getNumVertices()));
        double length = len(pos1-pos0);
        lengths.push_back(length);
      }
    }
  }
  
  sort(lengths.begin(), lengths.end());

  return lengths[lengths.size() / 2];
}

double ObjMesh::computeMaxEdgeLength() const
{
  double maxLength = 0;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
	cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for (unsigned k=0; k<face.getNumVertices(); k++)
      {
        Vec3d pos0 = getPosition(face.getVertex(k));
        Vec3d pos1 = getPosition(face.getVertex((k+1) % face.getNumVertices()));
        double length = len(pos1-pos0);
        if (length > maxLength)
          maxLength = length;
      }
    }
  }
  
  return maxLength;
}

double ObjMesh::computeMinEdgeLength(int * vtxa, int * vtxb) const
{
  *vtxa = *vtxb = -1;

  double minLength = -1;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
	cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for (unsigned k=0; k<face.getNumVertices(); k++)
      {
        Vec3d pos0 = getPosition(face.getVertex(k));
        Vec3d pos1 = getPosition(face.getVertex((k+1) % face.getNumVertices()));

        double length = len(pos1-pos0);

        if (minLength < 0) // only the first time
          minLength = length;
        else if (length < minLength)
          minLength = length;
        
        *vtxa = face.getVertex(k).getPositionIndex();
        *vtxb = face.getVertex((k+1) % face.getNumVertices()).getPositionIndex();
      }
    }
  }
  
  return minLength;
}

double ObjMesh::computeMaxEdgeLength(int * vtxa, int * vtxb) const
{
  *vtxa = *vtxb = -1;

  double maxLength = 0;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      if (face.getNumVertices() < 3)
	cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for (unsigned k=0; k<face.getNumVertices(); k++)
      {
        Vec3d pos0 = getPosition(face.getVertex(k));
        Vec3d pos1 = getPosition(face.getVertex((k+1) % face.getNumVertices()));
        double length = len(pos1-pos0);

        if (length > maxLength)
          maxLength = length;

        *vtxa = face.getVertex(k).getPositionIndex();
        *vtxb = face.getVertex((k+1) % face.getNumVertices()).getPositionIndex();
      }
    }
  }
  
  return maxLength;
}

unsigned int ObjMesh::getNumFaces() const
{
  unsigned int counter = 0;
  for (unsigned int i=0; i < groups.size(); i++)
    counter += groups[i].getNumFaces();    

  return counter;
}  

void ObjMesh::setNormalsToPseudoNormals()
{
  // nuke any previous normals
  normals.clear();

  // registers pseudonormals as the new normals
  for(unsigned int i=0; i < getNumVertices(); i++)
  {
    normals.push_back(pseudoNormals[i]);
  }

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      const ObjMesh::Face * face = groups[i].getFaceHandle(iFace); // get face whose number is iFace

      // over all vertices of the face
      for (unsigned k=0; k<face->getNumVertices(); k++)
      {
        Vertex * vertex = (Vertex*) face->getVertexHandle(k);
        vertex->setNormalIndex(vertex->getPositionIndex());
      }
    }
  }
}

void ObjMesh::buildVertexNormals(double angle)
{
  if (vertexFaceNeighbors.size() == 0)
  {
    printf("Error: buildVertexNormals() failed because vertex face neighbors were not built prior to calling buildVertexNormals(). Call \"buildVertexFaceNeighbors\".\n");
    return;
  }

  double cosang = cos(angle * M_PI / 180.0);

  normals.clear();
  int averageIndex = 0;

  for(unsigned int i = 0; i < getNumVertices(); i++)
  {
    if (vertexFaceNeighbors[i].size() == 0)
    {
      //silly lonely vertex
      continue;
    }
    const Face * firstFace = getGroupHandle(vertexFaceNeighbors[i].begin()->getGroupIndex())->getFaceHandle(vertexFaceNeighbors[i].begin()->getFaceIndex());
    if (!firstFace->hasFaceNormal())
    {
      printf("Warning: face normals not computed\n");
      return;
    }
    Vec3d firstNorm = firstFace->getFaceNormal();

    Vec3d average = Vec3d(0.0);
    bool averagedAnything = false;

    //find which faces contribute
    for(std::list<VertexFaceNeighbor>::iterator iter = vertexFaceNeighbors[i].begin(); iter != vertexFaceNeighbors[i].end(); iter++)
    {
      //get angle
      const Face * currentFace = getGroupHandle(iter->getGroupIndex())->getFaceHandle(iter->getFaceIndex());
      if (!currentFace->hasFaceNormal())
      {
        printf("Warning: face normals not computed\n");
        return;
      }
      //dot product
      if (dot(firstNorm, currentFace->getFaceNormal()) > cosang)
      {
        //is good, so contribute to average
        average += currentFace->getFaceNormal();
        iter->setAveraged(true);
        averagedAnything = true;
      }
      else
        iter->setAveraged(false);
    }

    if (averagedAnything)
    {
      normals.push_back(norm(average));
      averageIndex = normals.size() - 1;
    }

    //determine consequences for associated vertices in each face
    for(std::list<VertexFaceNeighbor>::iterator iter = vertexFaceNeighbors[i].begin(); iter != vertexFaceNeighbors[i].end(); iter++)
    {
      const Face * currentFace = getGroupHandle(iter->getGroupIndex())->getFaceHandle(iter->getFaceIndex());
      if (iter->getAveraged())
      {
        //use average for normal
        Vertex * vertex = (Vertex*) currentFace->getVertexHandle(iter->getFaceVertexIndex());
        vertex->setNormalIndex(averageIndex);
      }
      else
      {
        //use face normal for normal
        normals.push_back(currentFace->getFaceNormal());
        Vertex * vertex = (Vertex*) currentFace->getVertexHandle(iter->getFaceVertexIndex());
        vertex->setNormalIndex(normals.size() - 1);
      }
    }
  }
}

void ObjMesh::buildVertexNormalsFancy(double angle)
{
  if (vertexFaceNeighbors.size() == 0)
  {
    printf("Error: buildVertexNormalsFancy() failed because vertex face neighbors were not built prior to calling buildVertexNormalsFancy(). Call \"buildVertexFaceNeighbors\".\n");
    return;
  }

  double cosang = cos(angle * M_PI / 180.0);

  normals.clear();

  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      const ObjMesh::Face * faceHandle = groups[i].getFaceHandle(iFace); // get face whose number is iFace

      if (faceHandle->getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      if (!faceHandle->hasFaceNormal())
        printf("Warning: face has no face normal\n");

      Vec3d faceNorm = faceHandle->getFaceNormal();

      for(unsigned int j = 0; j < faceHandle->getNumVertices(); j++)
      {
        //process the neighbors of this vertex
        int vertexIndex = faceHandle->getVertexHandle(j)->getPositionIndex();
        Vec3d newNorm(0.0);
        bool averagedAnything = false;

        for(std::list<VertexFaceNeighbor>::iterator iter = vertexFaceNeighbors[vertexIndex].begin(); iter != vertexFaceNeighbors[vertexIndex].end(); iter++)
        {
          const Face * neighborFaceHandle = getGroupHandle(iter->getGroupIndex())->getFaceHandle(iter->getFaceIndex());
          if (!neighborFaceHandle->hasFaceNormal())
            printf("Warning: face has no face normal\n");

          if (dot(faceNorm, neighborFaceHandle->getFaceNormal()) > cosang)
          {
            newNorm += neighborFaceHandle->getFaceNormal();
            averagedAnything = true;
          }
        }
        if (!averagedAnything)
        {
          printf("error in mesh neighbor structure\n");
          newNorm = Vec3d(1.0);
        }
        normals.push_back(norm(newNorm));
        Vertex * vertex = (Vertex*) faceHandle->getVertexHandle(j);
        vertex->setNormalIndex(normals.size() - 1);
      }
    }
  }
}

void ObjMesh::setMaterialAlpha(double alpha)
{
  for(unsigned int i = 0; i < materials.size(); i++)
    materials[i].setAlpha(alpha);
}

void ObjMesh::setSingleMaterial(const Material & material)
{
  materials.clear();
  materials.push_back(material);
  for(int groupNo=0; groupNo<(int)groups.size(); groupNo++)
    groups[groupNo].setMaterialIndex(0);
}

void ObjMesh::computePseudoNormals()
{
  vector<int> vertexDegree(getNumVertices());
  for(unsigned int i=0; i<getNumVertices(); i++)
    pseudoNormals.push_back(0.0);

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace

      // over all vertices
      for (unsigned k=0; k<face.getNumVertices(); k++)
      {
        // compute angle at that vertex in radians
        Vec3d pos = getPosition(face.getVertex(k));
        Vec3d posNext, posPrev;
        if (k != face.getNumVertices() - 1)
          posNext = getPosition(face.getVertex(k + 1));
        else
          posNext = getPosition(face.getVertex(0));

        if (k != 0)
          posPrev = getPosition(face.getVertex(k - 1));
        else
          posPrev = getPosition(face.getVertex(face.getNumVertices() - 1));

        double lenNext = len(posNext-pos);
        double lenPrev = len(posPrev-pos);

        double angle = acos(dot(posNext-pos,posPrev-pos)/lenNext/lenPrev);
        Vec3d normal = norm(cross(posNext-pos, posPrev-pos));

        if (isNaN(normal[0]) || isNaN(normal[1]) || isNaN(normal[2]))
        {
          cout << "Error (when computing vertex pseudonormals): NaN encountered (face with zero surface area)." << endl;
          cout << "Group: " << i << " Face: " << iFace << " " << endl;
          normal[0] = 0; normal[1] = 0; normal[2] = 0;
          //cout << "  vtx0: " << index0 << " vtx1: " << index1 << " vtx2: " << index2 << endl;
          //cout << "  "  << p0 << endl;
          //cout << "  "  << p1 << endl;
          //cout << "  "  << p2 << endl;
          //cout << "Feature: " << normali << endl;
        }
        else
        {
          if ((lenNext == 0) || (lenPrev == 0) || isNaN(angle))
          {
            cout << "Warning (when computing vertex pseudonormals): encountered zero-length edge" << endl;
            cout << "  lenNext: " << lenNext << " lenPrev: " << lenPrev << " angle: " << angle << endl;
          }
          else  
          {
            pseudoNormals[face.getVertex(k).getPositionIndex()] += angle * normal;
            vertexDegree[face.getVertex(k).getPositionIndex()]++;
          }
        }
      }
    }
  }

  for(unsigned int i=0; i<getNumVertices(); i++)
  {
    if (vertexDegree[i] != 0)
    {
      Vec3d pseudoNormalRaw = pseudoNormals[i];
      pseudoNormals[i] = norm(pseudoNormalRaw);
      if (isNaN(pseudoNormals[i][0]) || isNaN(pseudoNormals[i][1]) || isNaN(pseudoNormals[i][2]))
      {
        cout << "Error (when computing vertex pseudonormals): NaN encountered." << endl;
        cout << "Vertex: " << i << " pseudoNormal=" << pseudoNormals[i][0] << " " << pseudoNormals[i][1] << " " << pseudoNormals[i][2] << endl;
        cout << "  Pseudonormal before normalization=";
        printf("%G %G %G\n", pseudoNormalRaw[0], pseudoNormalRaw[1], pseudoNormalRaw[2]); 
        cout << "  Vertex degree=" << vertexDegree[i] << endl;
        pseudoNormals[i] = 0.0;
      }
    }
    else
      pseudoNormals[i] = 0.0;
  }
}

void ObjMesh::computeEdgePseudoNormals()
{
  edgePseudoNormals.clear();

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace
      Vec3d pos0 = getPosition(face.getVertex(0));
      Vec3d pos1 = getPosition(face.getVertex(1));
      Vec3d pos2 = getPosition(face.getVertex(2));
      Vec3d normal = norm(cross(pos1-pos0, pos2-pos0));

      if (isNaN(normal[0]) || isNaN(normal[1]) || isNaN(normal[2]))
      {
        cout << "Error: nan encountered (face with zero surface area)." << endl;
        cout << "Group: " << i << " Face: " << iFace << " " << endl;
        exit(1);
      }

      // over all edges at the face
      for (unsigned k=0; k<face.getNumVertices(); k++)
      {

        unsigned int startVertex = face.getVertex(k).getPositionIndex();
        unsigned int endVertex = face.getVertex( (k+1) % face.getNumVertices()).getPositionIndex();

        pair<unsigned int, unsigned int> edge;
        if (startVertex < endVertex)
        {
          edge.first = startVertex;
          edge.second = endVertex;
        }
        else
        {
          edge.first = endVertex;
          edge.second = startVertex;
        }

        map< pair<unsigned int, unsigned int>, Vec3d > :: iterator iter = edgePseudoNormals.find(edge);
        
        if (iter == edgePseudoNormals.end())
        {
          edgePseudoNormals.insert(make_pair(edge,normal));
        }
        else
        {
          iter->second += normal;
        }
      }
    }
  }

  // normalize normals
  map< pair<unsigned int, unsigned int>, Vec3d > :: iterator iter;
  for(iter = edgePseudoNormals.begin(); iter != edgePseudoNormals.end(); ++iter)
  {
    Vec3d normal = norm(iter->second);
    if (isNaN(normal[0]) || isNaN(normal[1]) || isNaN(normal[2]))
    {
      cout << "Warning (while computing edge pseudonormals): NaN encountered (face with zero surface area)." << endl;
      normal[0] = 1; normal[1] = 0; normal[2] = 0;
    }
    iter->second = normal;
  }
}

int ObjMesh::removeZeroAreaFaces(int verbose)
{
  int numZeroAreaFaces = 0;

  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      if ((verbose == 1) && (iFace % 100 == 0))
      {
        printf("Processing face %d in group %d...\n", iFace, i);
        fflush(NULL);
      }      

      ObjMesh::Face face = groups[i].getFace(iFace); // get face whose number is iFace
      Vec3d pos0 = getPosition(face.getVertex(0));
      Vec3d pos1 = getPosition(face.getVertex(1));
      Vec3d pos2 = getPosition(face.getVertex(2));
      Vec3d normal = norm(cross(pos1-pos0, pos2-pos0));

      bool identicalVertex = false;
      for(unsigned int jj=0; jj< face.getNumVertices(); jj++)
        for(unsigned int kk=jj+1; kk< face.getNumVertices(); kk++)
        {
          if (face.getVertex(jj).getPositionIndex() == face.getVertex(kk).getPositionIndex())
            identicalVertex = true;
        }

      if (isNaN(normal[0]) || isNaN(normal[1]) || isNaN(normal[2]) || identicalVertex)
      {
        groups[i].removeFace(iFace);
        iFace--;
        numZeroAreaFaces++;
      }
    }
  }

  return numZeroAreaFaces;
}

int ObjMesh::removeHangingFaces()
{
  map< pair<unsigned int,unsigned int>, vector<pair<unsigned int, unsigned int> > > facesAdjacentToEdge;

  // build facesAdjacentToEdge
  // over all faces
  for(unsigned int iGroup = 0; iGroup < groups.size(); iGroup++ )
  {
    for(unsigned int iFace = 0; iFace < groups[iGroup].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[iGroup].getFace(iFace); // get face whose number is iFace
      for(unsigned int j=0; j<face.getNumVertices(); j++) // over all vertices of this face
      {
        unsigned int vtxIndexA = face.getVertex(j).getPositionIndex();
        unsigned int vtxIndexB = face.getVertex((j + 1) % face.getNumVertices()).getPositionIndex();
        if (vtxIndexA > vtxIndexB)
          std::swap(vtxIndexA, vtxIndexB);

        std::pair<unsigned int, unsigned int> myPair(vtxIndexA, vtxIndexB);
        if (facesAdjacentToEdge.find(myPair) == facesAdjacentToEdge.end())
          facesAdjacentToEdge.insert(make_pair(myPair, vector<pair<unsigned int, unsigned int> >())); 
        facesAdjacentToEdge[myPair].push_back(make_pair(iGroup, iFace));
      }
    }
  }

  set<pair<unsigned int, unsigned int> > eraseList;

  // check the map for edges with more than two neighbors
  for(map< pair<unsigned int,unsigned int>, vector<pair<unsigned int, unsigned int> > > :: iterator iter = facesAdjacentToEdge.begin(); iter != facesAdjacentToEdge.end(); iter++)
  {
    if ((iter->second).size() > 2)
    {
      // edge has more than two neighboring faces

      // check all adjacent faces, to see if any of them has an edge that has no other neighbor
      for(unsigned int i=0; i<(iter->second).size(); i++)
      {
        unsigned int iGroup = (iter->second)[i].first;
        unsigned int iFace = (iter->second)[i].second;

        ObjMesh::Face face = groups[iGroup].getFace(iFace); // get face whose number is iFace
        for(unsigned int j=0; j<face.getNumVertices(); j++) // over all vertices
        {
          unsigned int vtxIndexA = face.getVertex(j).getPositionIndex();
          unsigned int vtxIndexB = face.getVertex((j + 1) % face.getNumVertices()).getPositionIndex();
          if (vtxIndexA > vtxIndexB)
            std::swap(vtxIndexA, vtxIndexB);

          std::pair<unsigned int, unsigned int> myPair(vtxIndexA, vtxIndexB);
          if (facesAdjacentToEdge[myPair].size() == 1)
          {
            // found an edge with only one neighboring face (this face)
            // erase the face
            eraseList.insert((iter->second)[i]);
            break;
          }
        }
      }
    }
  }

  // erase faces whose all three edges are not shared by any other face
  // over all faces
  for(unsigned int iGroup = 0; iGroup < groups.size(); iGroup++ )
  {
    for(unsigned int iFace = 0; iFace < groups[iGroup].getNumFaces(); iFace++ )
    {
      int eraseFace = 1;
      ObjMesh::Face face = groups[iGroup].getFace(iFace); // get face whose number is iFace
      for(unsigned int j=0; j<face.getNumVertices(); j++) // over all vertices of this face
      {
        unsigned int vtxIndexA = face.getVertex(j).getPositionIndex();
        unsigned int vtxIndexB = face.getVertex((j + 1) % face.getNumVertices()).getPositionIndex();
        if (vtxIndexA > vtxIndexB)
          std::swap(vtxIndexA, vtxIndexB);

        std::pair<unsigned int, unsigned int> myPair(vtxIndexA, vtxIndexB);
        if (facesAdjacentToEdge[myPair].size() > 1)
        {
          eraseFace = 0;
          break;
        }
      }

      if (eraseFace)
        eraseList.insert(make_pair(iGroup, iFace));
    }
  }

  //printf("Erase list size is: %d\n", (int)eraseList.size());

  // erase the scheduled faces
  // must iterate from the back to front, to have correct indexing
  for(set<pair<unsigned int, unsigned int> > :: reverse_iterator iter = eraseList.rbegin(); iter != eraseList.rend(); iter++)
  {
    unsigned int iGroup = iter->first;
    unsigned int iFace = iter->second;
    Group * groupHandle = (Group*) getGroupHandle(iGroup);
    groupHandle->removeFace(iFace);
  }

  return (int) eraseList.size();
}

int ObjMesh::removeNonManifoldEdges()
{
  map< pair<unsigned int,unsigned int>, vector<pair<unsigned int, unsigned int> > > facesAdjacentToEdge;

  // build facesAdjacentToEdge
  // over all faces
  for(unsigned int iGroup = 0; iGroup < groups.size(); iGroup++ )
  {
    for(unsigned int iFace = 0; iFace < groups[iGroup].getNumFaces(); iFace++ )
    {
      ObjMesh::Face face = groups[iGroup].getFace(iFace); // get face whose number is iFace
      for(unsigned int j=0; j<face.getNumVertices(); j++) // over all vertices of this face
      {
        unsigned int vtxIndexA = face.getVertex(j).getPositionIndex();
        unsigned int vtxIndexB = face.getVertex((j + 1) % face.getNumVertices()).getPositionIndex();
        if (vtxIndexA > vtxIndexB)
          std::swap(vtxIndexA, vtxIndexB);

        std::pair<unsigned int, unsigned int> myPair(vtxIndexA, vtxIndexB);
        if (facesAdjacentToEdge.find(myPair) == facesAdjacentToEdge.end())
          facesAdjacentToEdge.insert(make_pair(myPair, vector<pair<unsigned int, unsigned int> >())); 
        facesAdjacentToEdge[myPair].push_back(make_pair(iGroup, iFace));
      }
    }
  }

  vector<pair<unsigned int, unsigned int> > eraseList;

  // check the map for edges with more than two neighbors
  for(map<pair<unsigned int,unsigned int>, vector<pair<unsigned int, unsigned int> > > :: iterator iter = facesAdjacentToEdge.begin(); iter != facesAdjacentToEdge.end(); iter++)
  {
    if ((iter->second).size() > 2)
      eraseList.push_back(iter->first);
  }

  sort(eraseList.begin(), eraseList.end());
  //printf("Erase list size: %d\n", eraseList.size());

  int removedEdges = 0;

  for(unsigned int i=0; i<eraseList.size(); i++)
  {
    if (eraseList[i].first == eraseList[i].second)
      continue;

    //printf("Removing edge: %d to %d.\n", eraseList[i].first, eraseList[i].second);

    int removeIsolatedVertices_ = 0;
    collapseEdge(eraseList[i].first, eraseList[i].second, removeIsolatedVertices_);
    removedEdges++;

    // renumber all future pairs
    for(unsigned int j=i+1; j<eraseList.size(); j++)
    {
      if (eraseList[j].first == eraseList[i].second)
        eraseList[j].first = eraseList[i].first;
      if (eraseList[j].second == eraseList[i].second)
        eraseList[j].second = eraseList[i].first;

      if (eraseList[j].first > eraseList[j].second)
        std::swap(eraseList[j].first, eraseList[j].second);
    }
  }

  removeIsolatedVertices();

  return removedEdges;
}

void ObjMesh::collapseEdge(unsigned int vertexA, unsigned int vertexB, int removeIsolatedVertices_)
{
  if (vertexA > vertexB)
    std::swap(vertexA, vertexB);

  // over all faces
  for(unsigned int iGroup = 0; iGroup < groups.size(); iGroup++)
  {
    Group * group = (Group*) getGroupHandle(iGroup);
    vector<unsigned int> eraseList;
    for(unsigned int iFace = 0; iFace < groups[iGroup].getNumFaces(); iFace++)
    {
      int eraseFace = 0;
      Face * face = (Face*) group->getFaceHandle(iFace); // get face whose number is iFace
      for(unsigned int j=0; j<face->getNumVertices(); j++) // over all vertices of this face
      {
        unsigned int vtxIndex = face->getVertex(j).getPositionIndex();
        if (vtxIndex == vertexB)
        {
          Vertex * vertex = (Vertex*) face->getVertexHandle(j);
          vertex->setPositionIndex(vertexA);
        }
      }

      // remove consecutive vertices
      for(unsigned int j=0; j<face->getNumVertices(); j++) // over all vertices of this face
      {
        unsigned int vtxIndexA = face->getVertex(j).getPositionIndex();
        unsigned int vtxIndexB = face->getVertex((j + 1) % face->getNumVertices()).getPositionIndex();
        if (vtxIndexA == vtxIndexB)
        {
          if (face->getNumVertices() <= 3)
            eraseFace = 1;
          else
            face->removeVertex(j);
          break;
        }
      }

      if (eraseFace)
        eraseList.push_back(iFace);
    }

    for(int i=(int)eraseList.size()-1; i>=0; i--)
    {
      //printf("Erasing face %d\n", eraseList[i]);
      group->removeFace(eraseList[i]);
    }
  }

  if (removeIsolatedVertices_)
    removeIsolatedVertices();
}

// returns 1 on success, 0 otherwise
int ObjMesh::getEdgePseudoNormal(unsigned int i, unsigned int j, Vec3d * pseudoNormal) const
{ 
  pair<unsigned int,unsigned int> edge;

  if (i < j)
  {
    edge.first = i;
    edge.second = j;
  }
  else
  {
    edge.first = j;
    edge.second = i;
  }

  map< pair<unsigned int, unsigned int> , Vec3d > :: const_iterator iter = edgePseudoNormals.find(edge);

  if (iter != edgePseudoNormals.end())
  {
    *pseudoNormal = iter->second;
    return 0;
  }

  return 1;
}

double ObjMesh::computeFaceSurfaceArea(const Face & face) const
{ 
  double faceSurfaceArea = 0;

  // base vertex
  Vec3d basePos = getPosition(face.getVertex(0));
                                                                                                                                                             
  for ( unsigned int iVertex = 1; iVertex < face.getNumVertices()-1; iVertex++ )
  {
     Vec3d pos1 = getPosition(face.getVertex(iVertex));
     Vec3d pos2 = getPosition(face.getVertex(iVertex + 1));
     faceSurfaceArea += fabs(computeTriangleSurfaceArea(basePos, pos1, pos2));
  }

  return faceSurfaceArea;
}

Vec3d ObjMesh::computeFaceCentroid(const Face & face) const
{ 
  Vec3d centroid = 0.0;
  for ( unsigned int iVertex = 0; iVertex < face.getNumVertices(); iVertex++ )
     centroid += getPosition(face.getVertex(iVertex));
  centroid /= face.getNumVertices();

  return centroid;
}

void ObjMesh::computeSpecificInertiaTensor(Vec3d & v0, Vec3d & v1, Vec3d & v2, double t[6]) const
{

  t[0] = (v0[1]*v0[1] + v0[2]*v0[2] + v1[1]*v1[1] + v1[2]*v1[2] + 
    v1[1]*v2[1] + v2[1]*v2[1] + v0[1]*(v1[1] + v2[1]) + 
    v1[2]*v2[2] + v2[2]*v2[2] + v0[2]*(v1[2] + v2[2]))/6; 

  t[1] = (-2*v1[0]*v1[1] - v1[1]*v2[0] - v0[1]*(v1[0] + v2[0])
     - v1[0]*v2[1] - 2*v2[0]*v2[1] - 
     v0[0]*(2*v0[1] + v1[1] + v2[1]))/12; 

  t[2] = (-2*v1[0]*v1[2] - v1[2]*v2[0] - v0[2]*(v1[0] + v2[0]) - 
    v1[0]*v2[2] - 2*v2[0]*v2[2] - 
    v0[0]*(2*v0[2] + v1[2] + v2[2]))/12; 

  t[3] =  (v0[0]*v0[0] + v0[2]*v0[2] + v1[0]*v1[0] + v1[2]*v1[2] + 
    v1[0]*v2[0] + v2[0]*v2[0] + v0[0]*(v1[0] + v2[0]) + 
    v1[2]*v2[2] + v2[2]*v2[2] + v0[2]*(v1[2] + v2[2]))/6; 

  t[4] = (-2*v1[1]*v1[2] - v1[2]*v2[1] - 
    v0[2]*(v1[1] + v2[1]) - v1[1]*v2[2] - 2*v2[1]*v2[2] - 
    v0[1]*(2*v0[2] + v1[2] + v2[2]))/12; 

  t[5] = (v0[0]*v0[0] + v0[1]*v0[1] + v1[0]*v1[0] + v1[1]*v1[1] + 
    v1[0]*v2[0] + v2[0]*v2[0] + v0[0]*(v1[0] + v2[0]) + 
    v1[1]*v2[1] + v2[1]*v2[1] + v0[1]*(v1[1] + v2[1]))/6;
}

void ObjMesh::dirname(const char * path, char * result)
{
  // seek for last '/' or '\'
  const char * ch = path;
  int lastPos = -1;
  int pos=0;

  while (*ch != 0)
  {
    if (*ch == '\\')
	  lastPos = pos;

    if (*ch == '/')
	  lastPos = pos;

	ch++;
	pos++;
  }

  if (lastPos != -1)
  {
    memcpy(result,path,sizeof(char)*lastPos);
    result[lastPos] = 0;
  }
  else
  {
	result[0] = '.';
	result[1] = 0;
  }
}

void ObjMesh::parseMaterials(const std::string & objMeshFilename, const std::string & materialFilename, int verbose)
{
  FILE * file;
  //char buf[128];
  //unsigned int numMaterials;
  
  char objMeshFilenameCopy[4096];
  strcpy(objMeshFilenameCopy, objMeshFilename.c_str());

  char dir[4096];
  dirname(objMeshFilenameCopy,dir);
  char filename[4096];
  strcpy(filename, dir);
  strcat(filename, "/");
  strcat(filename, materialFilename.c_str());

  file = fopen(filename, "r");
  if (!file) 
  {
    fprintf(stderr, " parseMaterials() failed: can't open material file %s.\n", filename);
    std::string message = "Failed to open material file '";
    message.append(filename);
    message.append("'");
    throw ObjMeshException(message);
  }
  
  double Ka[3];
  double Kd[3];
  double Ks[3];
  double shininess;
  string matName;
  string textureFile = string();

  // now, read in the data 
  char buf[4096];
  unsigned int numMaterials = 0;
  while(fscanf(file, "%s", buf) != EOF) 
  {
    switch(buf[0]) 
    {
      case '#':
        // comment 
        // ignore the rest of line
        fgets_(buf, sizeof(buf), file);
      break;

      case 'n':               
        // newmtl
        if (numMaterials >= 1) // flush previous material
          addMaterial(matName, Vec3d(Ka[0], Ka[1], Ka[2]), Vec3d(Kd[0], Kd[1], Kd[2]), Vec3d(Ks[0], Ks[1], Ks[2]), shininess, textureFile);

        // reset to default
        Ka[0] = 0.1; Ka[1] = 0.1; Ka[2] = 0.1;
        Kd[0] = 0.5; Kd[1] = 0.5; Kd[2] = 0.5;
        Ks[0] = 0.0; Ks[1] = 0.0; Ks[2] = 0.0;
        shininess = 65;
        textureFile = string();

        fgets_(buf, sizeof(buf), file);
        sscanf(buf, "%s %s", buf, buf);
        numMaterials++;
        matName = string(buf);
      break;

      case 'N':
        if (buf[1] == 's')
        {
          if (fscanf(file, "%lf", &shininess) < 1)
            printf("Warning: incorect mtl file syntax. Unable to read shininess.\n");
          // wavefront shininess is from [0, 1000], so scale for OpenGL 
          shininess *= 128.0 / 1000.0;
        }
        else
          fgets_(buf, sizeof(buf), file); // ignore the rest of the line
      break;

      case 'K':
        switch(buf[1]) 
        {
          case 'd':
            if (fscanf(file, "%lf %lf %lf", &Kd[0], &Kd[1], &Kd[2]) < 3)
              printf("Warning: incorect mtl file syntax. Unable to read Kd.\n");
          break;

          case 's':
            if (fscanf(file, "%lf %lf %lf", &Ks[0], &Ks[1], &Ks[2]) < 3)
              printf("Warning: incorect mtl file syntax. Unable to read Ks.\n");
           break;

          case 'a':
            if (fscanf(file, "%lf %lf %lf", &Ka[0], &Ka[1], &Ka[2]) < 3)
              printf("Warning: incorect mtl file syntax. Unable to read Ka.\n");
          break;

          default:
            // ignore the rest of the line
            fgets_(buf, sizeof(buf), file);
          break;
        }
      break;

      case 'm':
        if (strcmp(buf, "map_Kd") == 0)
        {
          fgets_(buf, sizeof(buf), file);
          sscanf(buf, "%s %s", buf, buf);
          textureFile = string(buf);
          if (verbose)
            printf("Noticed texture %s.\n", textureFile.c_str());
        }
      break;

      default:
        // ignore the rest of the line
        fgets_(buf, sizeof(buf), file);
      break;
    }
  }

  if (numMaterials >= 1) // flush last material
    addMaterial(matName, Vec3d(Ka[0], Ka[1], Ka[2]), Vec3d(Kd[0], Kd[1], Kd[2]), Vec3d(Ks[0], Ks[1], Ks[2]), shininess, textureFile);

  fclose(file);
}

void ObjMesh::initSurfaceSampling()
{
  if (!isTriangularMesh())
  {
    throw ObjMeshException("Error in init surface sampling: surface not triangular.");
  }

  double totalSurfaceArea = computeSurfaceArea();
  double area = 0;
  
  // over all faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      surfaceSamplingAreas.push_back(make_pair(area, groups[i].getFaceHandle(iFace)));
      ObjMesh::Face face = groups[i].getFace(iFace); 
      area += computeFaceSurfaceArea(face) / totalSurfaceArea;
    }
  }

}

Vec3d ObjMesh::getSurfaceSamplePosition(double sample) const
{
  unsigned int facePosition;
  for(facePosition=0; facePosition< surfaceSamplingAreas.size()-1; facePosition++)
  {
    if ((surfaceSamplingAreas[facePosition].first <= sample) && 
        (surfaceSamplingAreas[facePosition+1].first > sample))
      break;
  }

  // facePosition now contains the index of the face to sample from
  const Face * face = surfaceSamplingAreas[facePosition].second;

  // sample at random on the face
  double alpha, beta;
  do
  {
    alpha = 1.0 * rand() / RAND_MAX;
    beta = 1.0 * rand() / RAND_MAX;
  }  
  while (alpha + beta > 1);

  double gamma = 1 - alpha - beta;

  Vec3d v0 = getPosition(face->getVertex(0)); 
  Vec3d v1 = getPosition(face->getVertex(1)); 
  Vec3d v2 = getPosition(face->getVertex(2)); 

  Vec3d sampledPos = alpha * v0 + beta * v1 + gamma * v2;
  return sampledPos;
}

void ObjMesh::getMeshRadius(const Vec3d & centroid, double * radius) const
{
  double radiusSquared = 0.0;
  for(std::vector<Vec3d>::const_iterator iter = vertexPositions.begin(); iter != vertexPositions.end(); iter++)
  {
    double newSquared = len2(*iter - centroid);
    if (newSquared > radiusSquared)
      radiusSquared = newSquared;
  }
  *radius = sqrt(radiusSquared);
}

void ObjMesh::getMeshGeometricParameters(Vec3d * centroid, double * radius) const
{
  //find the centroid
  *centroid = Vec3d(0, 0, 0);
  for(std::vector<Vec3d>::const_iterator iter = vertexPositions.begin(); iter != vertexPositions.end(); iter++)
    *centroid += *iter;
  *centroid /= getNumVertices();

  // find the radius
  getMeshRadius(*centroid, radius);
}

void ObjMesh::buildVertexFaceNeighbors()
{
  vertexFaceNeighbors.clear();
  for(unsigned int i=0; i<getNumVertices(); i++)
    vertexFaceNeighbors.push_back(std::list<VertexFaceNeighbor>());

  //go through each of the faces
  for(unsigned int i = 0; i < groups.size(); i++ )
  {
    for(unsigned int iFace = 0; iFace < groups[i].getNumFaces(); iFace++ )
    {
      const ObjMesh::Face * faceHandle = groups[i].getFaceHandle(iFace); // get face whose number is iFace

      if (faceHandle->getNumVertices() < 3)
        cout << "Warning: encountered a face (group=" << i << ",face=" << iFace << ") with fewer than 3 vertices." << endl;

      for(unsigned int j = 0; j < faceHandle->getNumVertices(); j++)
      {
        const ObjMesh::Vertex * vertexHandle = faceHandle->getVertexHandle(j);
        vertexFaceNeighbors[vertexHandle->getPositionIndex()].push_back(ObjMesh::VertexFaceNeighbor(i, iFace, j));
      }
    }
  }
}

void ObjMesh::clearVertexFaceNeighbors()
{
  vertexFaceNeighbors.clear();
}

void ObjMesh::Group::removeFace(unsigned int i)
{
  faces.erase(faces.begin() + i);
}

ObjMeshException::ObjMeshException(const std::string & reason)
{
  std::ostringstream oss;
  oss << "Error:  " << reason;
  std::cout << std::endl << oss.str() << std::endl;
}

ObjMeshException::ObjMeshException(const std::string & reason, const std::string & filename, unsigned int line)
{
  std::ostringstream oss;
  oss << "Error in file '" << filename << "', line " << line << ": " << reason;
  std::cout << std::endl << oss.str() << std::endl;
}

bool ObjMesh::Material::operator==(const Material & mat2) const
{
  if (len(Ka - mat2.Ka) > 1e-7)
    return false;

  if (len(Kd - mat2.Kd) > 1e-7)
    return false;

  if (len(Ks - mat2.Ks) > 1e-7)
    return false;

  if (fabs(shininess - mat2.shininess) > 1e-7)
    return false;
   
  return true;
}

int ObjMesh::removeDuplicatedMaterials()
{
  unsigned int numMaterials = getNumMaterials();
  vector<int> reNumberVector(numMaterials);  

  vector<Material> newMaterials;

  // detected duplicated materials
  for(unsigned int i=0; i<numMaterials; i++)
  {
    bool newMaterial = true; 
    for(unsigned int j=0; j<newMaterials.size(); j++)
    {
      if (newMaterials[j] == materials[i])
      {
        newMaterial = false;
        reNumberVector[i] = j;
        break;
      }
    }

    if (newMaterial)
    {
      newMaterials.push_back(materials[i]);
      reNumberVector[i] = newMaterials.size() - 1;
    }
  } 

  materials = newMaterials;

  // correct the groups
  for(unsigned int i=0; i<getNumGroups(); i++)
    groups[i].setMaterialIndex(reNumberVector[groups[i].getMaterialIndex()]);

  return materials.size();
}

void ObjMesh::exportGeometry(int * numVertices, double ** vertices, int * numTriangles , int ** triangles, int * numGroups, int ** triangleGroups) const
{
  // set vertices
  if (numVertices != NULL) 
    *numVertices = vertexPositions.size();
  if (vertices != NULL)
  {
    *vertices = (double*) malloc (sizeof(double) * 3 * vertexPositions.size());
    for(size_t i=0; i< vertexPositions.size(); i++)
    {
      Vec3d vtx = getPosition(i);
      (*vertices)[3*i+0] = vtx[0];
      (*vertices)[3*i+1] = vtx[1];
      (*vertices)[3*i+2] = vtx[2];
    }
  }

  if (numGroups != NULL)
    *numGroups = getNumGroups();

  if (numTriangles == NULL && triangles == NULL && triangleGroups == NULL)
    return;

  // count #triangles 
  int nt = 0;
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      if (face->getNumVertices() < 3)
        continue;
      nt += face->getNumVertices() - 2;
    }

  if(numTriangles != NULL)
    *numTriangles = nt;
  if (triangles == NULL && triangleGroups == NULL)
    return;

  // set triangles
  if(triangles != NULL)
    *triangles = (int*) malloc (sizeof(int) * 3 * nt);
  
  // set triangle groups while setting triangle positions (easy addition)
  if (triangleGroups != NULL)
    *triangleGroups = (int*) calloc (nt, sizeof(int)); // set all groups to 0 just in case

  for(unsigned int i=0, tri=0; i < groups.size(); i++) // over all groups
  {
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      if (face->getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than 3 vertices.\n");
        continue;
      }

      unsigned int faceDegree = face->getNumVertices();

      // triangulate the face

      // get the vertices:
      vector<Vertex> vertices;
      for(unsigned int k=0; k<face->getNumVertices(); k++)
        vertices.push_back(face->getVertex(k));
      
      // set triangle vertex positions
      if(triangles != NULL)
      {
        (*triangles)[3*tri+0] = vertices[0].getPositionIndex();
        (*triangles)[3*tri+1] = vertices[1].getPositionIndex();
        (*triangles)[3*tri+2] = vertices[2].getPositionIndex();
      }
      
      // set triangle group
      if (triangleGroups != NULL)
        (*triangleGroups)[tri] = i;
      
      // increment triangle counter
      tri++;

      for(unsigned int k=2; k<faceDegree-1; k++)
      {
        if(triangles != NULL)
        {
          (*triangles)[3*tri+0] = vertices[0].getPositionIndex();
          (*triangles)[3*tri+1] = vertices[k].getPositionIndex();
          (*triangles)[3*tri+2] = vertices[k+1].getPositionIndex();
        }
        
        // set triangle group
        if (triangleGroups != NULL)
          (*triangleGroups)[tri] = i;
        
        // increment triangle counter
        tri++;
      }
    }
  }
  //printf("Exported %d vertices and %d triangles.\n", vertexPositions.size(), nt);
}

void ObjMesh::exportFaceGeometry(int * numVertices, double ** vertices, int * numFaces, int ** faceCardinality, int ** faces, int * numGroups, int ** faceGroups) const
{
  // set vertices
  if (numVertices != NULL) 
    *numVertices = vertexPositions.size();
  if (vertices != NULL)
  {
    *vertices = (double*) malloc (sizeof(double) * 3 * *numVertices);
    for(int i=0; i< *numVertices; i++)
    {
      Vec3d vtx = getPosition(i);
      (*vertices)[3*i+0] = vtx[0];
      (*vertices)[3*i+1] = vtx[1];
      (*vertices)[3*i+2] = vtx[2];
    }
  }

  if(numGroups != NULL)
    *numGroups = getNumGroups();

  if (numFaces == NULL && faceCardinality == NULL && faces == NULL && faceGroups == NULL)
    return;

  // set faces
  int nf = 0, totalCardinality = 0;
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      if (face->getNumVertices() < 3)
        continue;
      nf++;
      totalCardinality += face->getNumVertices();
    }

  if(numFaces != NULL)
    (*numFaces) = nf;
  if (faceCardinality == NULL && faces == NULL && faceGroups == NULL)
    return;

  if(faceCardinality != NULL)
    *faceCardinality = (int*) malloc (sizeof(int) * nf);

  if(faces != NULL)
    *faces = (int*) malloc (sizeof(int) * totalCardinality);

  if(faceGroups != NULL)
    *faceGroups = (int*) calloc (*numFaces, sizeof(int));

  int faceCounter = 0;
  int tc = 0;
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      if (face->getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than 3 vertices.\n");
        continue;
      }

      int faceDegree = (int)face->getNumVertices();
      if(faceCardinality != NULL)
        (*faceCardinality)[faceCounter] = faceDegree;
      if(faceGroups != NULL)
        (*faceGroups)[faceCounter] = i;
      if(faces != NULL)
        for(unsigned int k=0; k<face->getNumVertices(); k++)
          (*faces)[tc + k] = face->getVertex(k).getPositionIndex();
        
      faceCounter++;
      tc += faceDegree;
    }
  //printf("Exported %d vertices and %d faces. Average number of vertices: %G\n", *numVertices, *numFaces, 1.0 * totalCardinality / (*numFaces));
}

void ObjMesh::exportUVGeometry(int * numUVVertices, double ** UVvertices, int * numUVTriangles, int ** UVTriangles) const // exports the geometry in the texture coordinate space
{
  // count num UV triangles
  *numUVTriangles = 0;
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      if (face->getNumVertices() < 3)
        continue;
      *numUVTriangles += face->getNumVertices() - 2;
    }

  *numUVVertices = 3 * *numUVTriangles;
  *UVvertices = (double*) malloc (sizeof(double) * 3 * *numUVVertices);
  *UVTriangles = (int*) malloc (sizeof(int) * 3 * *numUVTriangles);

  int tri = 0;
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
  {
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      if (face->getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than 3 vertices.\n");
        continue;
      }

      // get the vertices:
      vector<Vertex> vertices;
      for(unsigned int k=0; k<face->getNumVertices(); k++)
        vertices.push_back(face->getVertex(k));

      // triangulate the face
      for(int i=0; i<(int) face->getNumVertices()-2; i++)
      {
        Vec3d uv0 = getTextureCoordinate(vertices[0].getTextureCoordinateIndex());;
        Vec3d uv1 = getTextureCoordinate(vertices[i+1].getTextureCoordinateIndex());;
        Vec3d uv2 = getTextureCoordinate(vertices[i+2].getTextureCoordinateIndex());;
        (*UVvertices)[9*tri+0] = uv0[0];
        (*UVvertices)[9*tri+1] = uv0[1];
        (*UVvertices)[9*tri+2] = uv0[2];
        (*UVvertices)[9*tri+3] = uv1[0];
        (*UVvertices)[9*tri+4] = uv1[1];
        (*UVvertices)[9*tri+5] = uv1[2];
        (*UVvertices)[9*tri+6] = uv2[0];
        (*UVvertices)[9*tri+7] = uv2[1];
        (*UVvertices)[9*tri+8] = uv2[2];

        (*UVTriangles)[3*tri+0] = 3*tri+0;
        (*UVTriangles)[3*tri+1] = 3*tri+1;
        (*UVTriangles)[3*tri+2] = 3*tri+2;

        // increment triangle counter
        tri++;
      }
    }
  }
}

// allows one to query the vertex indices of each triangle
// order of triangles is same as in "exportGeometry": for every group, traverse all faces, and tesselate each face into triangles 
void ObjMesh::initTriangleLookup()
{
  int numVertices;
  double * vertices;
  int numTriangles;
  int * trianglesV;
  exportGeometry(&numVertices, &vertices, &numTriangles , &trianglesV);

  triangles.clear();
  for(int i=0; i<3*numTriangles; i++)
    triangles.push_back(trianglesV[i]);

  free(trianglesV);
  free(vertices);
}

void ObjMesh::clearTriangleLookup()
{
  triangles.clear();
}

void ObjMesh::getTriangle(int triangleIndex, int * vtxA, int * vtxB, int * vtxC) // must call "initTriangleLookup" first
{
  *vtxA = triangles[3*triangleIndex+0];
  *vtxB = triangles[3*triangleIndex+1];
  *vtxC = triangles[3*triangleIndex+2];
}

void ObjMesh::renumberVertices(const vector<int> & permutation)
{
  unsigned int numVertices = getNumVertices();

  // renumber vertices
  if (permutation.size() != numVertices)
  {
    printf("Error: permutation size mismatch.\n");
  }

  vector<Vec3d> vertexPositionsBuffer(numVertices);
  for(unsigned int i=0; i < numVertices; i++)
    vertexPositionsBuffer[permutation[i]] = vertexPositions[i];
  
  vertexPositions = vertexPositionsBuffer;
 
  // renumber faces
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      if (face->getNumVertices() < 3)
      {
        printf("Warning: encountered a face with fewer than 3 vertices.\n");
        continue;
      }

      for(unsigned int k=0; k<face->getNumVertices(); k++)
      {
        Vertex * vtx = (Vertex*) face->getVertexHandle(k);
        vtx->setPositionIndex(permutation[vtx->getPositionIndex()]);
      }       
    }
}

int ObjMesh::computeNumIsolatedVertices() const
{
  vector<int> counter(getNumVertices(), 0);

  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      for(unsigned int k=0; k<face->getNumVertices(); k++)
        counter[face->getVertex(k).getPositionIndex()]++;
    }

  int numIsolatedVertices = 0;
  for(unsigned int i=0; i<getNumVertices(); i++)
    if (counter[i] == 0)
      numIsolatedVertices++;

  return numIsolatedVertices;
}

int ObjMesh::removeIsolatedVertices()
{
  vector<int> counter(getNumVertices(), 0);

  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      for(unsigned int k=0; k<face->getNumVertices(); k++)
        counter[face->getVertex(k).getPositionIndex()]++;
    }

  map<int,int> oldToNew;
  map<int,int> newToOld;

  int numConnectedVertices = 0;
  for(unsigned int i=0; i<getNumVertices(); i++)
  {
    if (counter[i] != 0)
    {
      oldToNew.insert(make_pair(i, numConnectedVertices));
      newToOld.insert(make_pair(numConnectedVertices, i));
      numConnectedVertices++;
    }
  }

  int numOriginalVertices = getNumVertices();
  int numIsolatedVertices = numOriginalVertices - numConnectedVertices;

  // relink vertices, remove old vertices
  for(int i=0; i<numConnectedVertices; i++)
    vertexPositions[i] = vertexPositions[newToOld[i]];

  for(int i=numConnectedVertices; i<numOriginalVertices; i++)
    vertexPositions.pop_back();

  // renumber vertices inside faces
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      for(unsigned int k=0; k<face->getNumVertices(); k++)
      {
        Vertex * vertex = (Vertex*) face->getVertexHandle(k);
        int oldPositionIndex = vertex->getPositionIndex();
        vertex->setPositionIndex(oldToNew[oldPositionIndex]);
      }
    }
 
  return numIsolatedVertices;
}

int ObjMesh::removeIsolatedNormals()
{
  vector<int> counter(getNumNormals(), 0);

  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      for(unsigned int k=0; k<face->getNumVertices(); k++)
      {
        if (face->getVertex(k).hasNormalIndex())
          counter[face->getVertex(k).getNormalIndex()]++;
      }
    }

  map<int,int> oldToNew;
  map<int,int> newToOld;

  int numConnectedNormals = 0;
  for(unsigned int i=0; i<getNumNormals(); i++)
  {
    if (counter[i] != 0)
    {
      oldToNew.insert(make_pair(i, numConnectedNormals));
      newToOld.insert(make_pair(numConnectedNormals, i));
      numConnectedNormals++;
    }
  }

  int numOriginalNormals = getNumNormals();
  int numIsolatedNormals = numOriginalNormals - numConnectedNormals;

  // relink normals, remove old normals
  for(int i=0; i<numConnectedNormals; i++)
    normals[i] = normals[newToOld[i]];

  for(int i=numConnectedNormals; i<numOriginalNormals; i++)
    normals.pop_back();

  // renumber normals inside faces
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      for(unsigned int k=0; k<face->getNumVertices(); k++)
      {
        Vertex * vertex = (Vertex*) face->getVertexHandle(k);
        if (vertex->hasNormalIndex())
        {
          int oldNormalIndex = vertex->getNormalIndex();
          vertex->setNormalIndex(oldToNew[oldNormalIndex]);
        }
      }
    }
 
  return numIsolatedNormals;
}

int ObjMesh::removeIsolatedTextureCoordinates()
{
  vector<int> counter(getNumTextureCoordinates(), 0);

  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      for(unsigned int k=0; k<face->getNumVertices(); k++)
      {
        if (face->getVertex(k).hasTextureCoordinateIndex())
          counter[face->getVertex(k).getTextureCoordinateIndex()]++;
      }
    }

  map<int,int> oldToNew;
  map<int,int> newToOld;

  int numConnectedTextureCoordinates = 0;
  for(unsigned int i=0; i<getNumTextureCoordinates(); i++)
  {
    if (counter[i] != 0)
    {
      oldToNew.insert(make_pair(i, numConnectedTextureCoordinates));
      newToOld.insert(make_pair(numConnectedTextureCoordinates, i));
      numConnectedTextureCoordinates++;
    }
  }

  int numOriginalTextureCoordinates = getNumTextureCoordinates();
  int numIsolatedTextureCoordinates = numOriginalTextureCoordinates - numConnectedTextureCoordinates;

  // relink textureCoordinates, remove old textureCoordinates
  for(int i=0; i<numConnectedTextureCoordinates; i++)
    textureCoordinates[i] = textureCoordinates[newToOld[i]];

  for(int i=numConnectedTextureCoordinates; i<numOriginalTextureCoordinates; i++)
    textureCoordinates.pop_back();

  // renumber textureCoordinates inside faces
  for(unsigned int i=0; i < groups.size(); i++) // over all groups
    for (unsigned int j=0; j < groups[i].getNumFaces(); j++) // over all faces
    {
      const Face * face = groups[i].getFaceHandle(j);
      for(unsigned int k=0; k<face->getNumVertices(); k++)
      {
        Vertex * vertex = (Vertex*) face->getVertexHandle(k);
        if (vertex->hasTextureCoordinateIndex())
        {
          int oldTextureCoordinateIndex = vertex->getTextureCoordinateIndex();
          vertex->setTextureCoordinateIndex(oldToNew[oldTextureCoordinateIndex]);
        }
      }
    }
 
  return numIsolatedTextureCoordinates;
}

void ObjMesh::mergeGroups(const vector<int> & groupIndicesIn)
{
  if (groupIndicesIn.size() < 1)
    return;

  // sort group indices
  vector<int> groupIndices(groupIndicesIn);
  sort(groupIndices.begin(), groupIndices.end());

  // the groups will be copied into the group with the smallest index
  Group * groupDest = (Group*) getGroupHandle(*(groupIndices.begin())); 

  int count = 0;
  for(vector<int> :: reverse_iterator iter = groupIndices.rbegin(); iter != groupIndices.rend(); iter++)
  {
    if (count != (int)groupIndices.size() - 1) // no need to process the last group (with smallest index)
    {
      int groupIndex = *iter;
      Group * groupSource = (Group*) getGroupHandle(groupIndex);
      for(int i=0; i<(int)groupSource->getNumFaces(); i++)
        groupDest->addFace(groupSource->getFace(i));
      //printf("Removing group %d. Num groups = %d\n", groupIndex, (int)groups.size());
      groups[groupIndex] = groups.back();
      groups.pop_back();
    }
    count++;
  }
}

void ObjMesh::removeEmptyGroups()
{
  for(vector<Group> :: iterator iter = groups.begin(); iter != groups.end(); iter++)
  {
    if (iter->getNumFaces() == 0)
    {
      *iter = groups.back();
      groups.pop_back();
    }
  }
}

void ObjMesh::appendMesh(ObjMesh * mesh)
{
  // add vertices
  int numVerticesCurrent = getNumVertices();
  for(unsigned int i=0; i<mesh->getNumVertices(); i++)
    addVertexPosition(mesh->getPosition(i));

  // add normals
  int numNormalsCurrent = getNumNormals();
  for(unsigned int i=0; i<mesh->getNumNormals(); i++)
    addVertexNormal(mesh->getNormal(i));

  // add texture coordinates
  int numTextureCoordinatesCurrent = getNumTextureCoordinates();
  for(unsigned int i=0; i<mesh->getNumTextureCoordinates(); i++)
    addTextureCoordinate(mesh->getTextureCoordinate(i));

  // add materials
  int numMaterialsCurrent = getNumMaterials();
  for(unsigned int i=0; i<mesh->getNumMaterials(); i++)
    addMaterial(mesh->getMaterial(i));

  for(unsigned int i=0; i<mesh->getNumGroups(); i++)
  {
    const ObjMesh::Group * group = mesh->getGroupHandle(i);
    addGroup(group->getName());
    unsigned int newGroupID = getNumGroups() - 1;
    ObjMesh::Group * newGroup = (ObjMesh::Group*) getGroupHandle(newGroupID);
    newGroup->setMaterialIndex(numMaterialsCurrent + group->getMaterialIndex());

    // over all faces in the group of the current obj file
    for(unsigned int j=0; j<group->getNumFaces(); j++)
    {
      const ObjMesh::Face * face = group->getFaceHandle(j);
      for(unsigned int k=0; k<face->getNumVertices(); k++)
      {
        ObjMesh::Vertex * vertex = (ObjMesh::Vertex*) face->getVertexHandle(k);
        vertex->setPositionIndex(vertex->getPositionIndex() + numVerticesCurrent);
        if (vertex->hasNormalIndex())
          vertex->setNormalIndex(vertex->getNormalIndex() + numNormalsCurrent);
        if (vertex->hasTextureCoordinateIndex())
          vertex->setTextureCoordinateIndex(vertex->getTextureCoordinateIndex() + numTextureCoordinatesCurrent);
      }
      addFaceToGroup(*face,newGroupID);
    }
  }
}

// removes all whitespace characters from string s
void ObjMesh::removeWhitespace(char * s)
{
  char * p = s;
  while (*p != 0)
  {
    // erase empty space
    while (*p == ' ') 
    {
      char * q = p;
      while (*q != 0) // move characters to the left, by one character
      {
        *q = *(q+1);
        q++;
      }
    }
    p++;
  }
}

// shrinks all whitespace to a single space character; also removes any whitespace before end of string
void ObjMesh::convertWhitespaceToSingleBlanks(char * s)
{
  char * p = s;
  while (*p != 0)
  {
    // erase consecutive empty space characters, or end-of-string spaces
    while ((*p == ' ') && ((*(p+1) == 0) || (*(p+1) == ' '))) 
    {
      char * q = p;
      while (*q != 0) // move characters to the left, by one character
      {
        *q = *(q+1);
        q++;
      }
    }
    p++;
  }
}

void ObjMesh::fgets_(char * s, int n, FILE * stream)
{
  char * result = fgets(s, n, stream);
  if (result == NULL)
    printf("Warning: bad input file syntax. fgets_ returned NULL.\n");
  return;
}

unsigned int ObjMesh::getGroupIndex(const std::string name) const
{
  int count = 0;
  for(std::vector<Group>::const_iterator itr = groups.begin(); itr != groups.end(); itr++)
  {
    if (itr->getName() == name)
      return count;
    count++;
  }

  std::ostringstream oss;
  oss << "Invalid group name: '" << name << "'.";
  throw ObjMeshException(oss.str());

  return 0;
}

unsigned int ObjMesh::getMaterialIndex(const std::string name) const
{
  int count = 0;
  for(std::vector<Material>::const_iterator itr = materials.begin(); itr != materials.end(); itr++)
  {
    if (itr->getName() == name)
      return count;
    count++;
  }

  std::ostringstream oss;
  oss << "Invalid material name: '" << name << "'.";
  throw ObjMeshException(oss.str());

  return 0;
}

void ObjMesh::removeGroup(const int groupIndex)
{
  if ((groupIndex >= (int) groups.size()) || (groupIndex < 0))
  {
    printf("Warning: cannot remove group %d. Invalid group number.\n", groupIndex);
    return;
  }
  groups[groupIndex] = groups[groups.size() - 1];
  groups.pop_back();
  computeBoundingBox();
}
 
void ObjMesh::removeGroup(const std::string name)
{
  int groupIndex = getGroupIndex(name);
  removeGroup(groupIndex);
}

void ObjMesh::removeAllGroups()
{
  groups.clear();
  computeBoundingBox();
}

// 0 = no group uses a material that references a texture image, 1 = otherwise
int ObjMesh::usesTextureMapping()
{
  int result = 0;
  for(std::vector<Group>::const_iterator itr = groups.begin(); itr != groups.end(); itr++)
  {
    const Material * material = getMaterialHandle(itr->getMaterialIndex());
    result = result | ((int)material->hasTextureFilename());
  }
  return result;
}

int ObjMesh::loadObjMeshesFromBinary(const std::string & binaryFilename, int * numObjMeshes, ObjMesh *** objMeshes, int verbose)
{
  FILE * fin = fopen(binaryFilename.c_str(), "rb");
  if (fin == NULL)
  {
    if (verbose)
      printf("Error in ObjMesh::loadObjMeshesFromBinary: cannot open %s to load.\n", binaryFilename.c_str());
    return 1;
  }

  int code = loadObjMeshesFromBinary(fin, numObjMeshes, objMeshes, verbose);

  for(int objMeshIndex = 0; objMeshIndex < *numObjMeshes; objMeshIndex++)
    if ((*objMeshes)[objMeshIndex])
      (*objMeshes)[objMeshIndex]->filename = binaryFilename;

  return code;
}

int ObjMesh::loadObjMeshesFromBinary(FILE * fin, int * numObjMeshes, ObjMesh *** objMeshes, int verbose)
{
  // read the number of obj meshes
  unsigned int items = fread(numObjMeshes, sizeof(int), 1, fin);
  if (items != 1)
    return 1;

  int numMeshes = *numObjMeshes;

  if (verbose)
    printf("number of obj meshes to be read from binary: %d\n", numMeshes);

  // read how many bytes are stored for every obj mesh
  unsigned int * bytesWritten = (unsigned int *) calloc (numMeshes, sizeof(unsigned int));
  items = fread(bytesWritten, sizeof(unsigned int), numMeshes, fin);
  if ((int)items != numMeshes)
    return 1;

  if (verbose)
  {
    printf("number of bytes for each obj mesh: \n");
    for(int i=0; i<numMeshes; i++)
      printf("%u, ", bytesWritten[i]);
    printf("\n");
  }

  // compute the total bytes
  unsigned int totalBytes = 0;
  for(int i=0; i<numMeshes; i++)
    totalBytes += bytesWritten[i];

  // allocate memory for obj meshes
  (*objMeshes) = (ObjMesh **) malloc (sizeof(ObjMesh *) * numMeshes);
  for (int i=0; i<numMeshes; i++)
    (*objMeshes)[i] = NULL;

  // read entire block from the memory
  unsigned char * memory = (unsigned char *) malloc (sizeof(unsigned char) * totalBytes);
  items = fread(memory, sizeof(unsigned char), totalBytes, fin);

  if (verbose)
    printf("total bytes excluding header: %u\n", totalBytes);

  // compute the offset for every obj mesh
  unsigned int * offset = (unsigned int *) calloc (numMeshes, sizeof(unsigned int));
  for(int i=1; i<numMeshes; i++)
    offset[i] = offset[i-1] + bytesWritten[i-1];

  // load every obj mesh from memory
  #ifdef USE_OPENMP
    #pragma omp parallel for
  #endif
  for(int i=0; i<numMeshes; i++)
  {
    if (bytesWritten[i] != 0)
    {
      unsigned char * location = memory + offset[i];
      streamType stream = MEMORY_STREAM;
      int verbose = 0;
      (*objMeshes)[i] = new ObjMesh((void *)location, stream, verbose);
    }
  }

  free(bytesWritten);
  free(memory);
  free(offset);

  return 0;
}

int ObjMesh::loadFromBinary(const std::string & filename_, int verbose)
{
  filename = filename_;
  FILE * binaryInputStream = fopen(filename_.c_str(), "rb");
  if (binaryInputStream == NULL)
  {
    printf("Error in ObjMesh::loadFromBinary: cannot load obj from binary file %s.\n", filename_.c_str());
    return 1;
  }

  if (verbose)
    std::cout << "Parsing .obj file '" << filename << "'." << std::endl;

  streamType stream = FILE_STREAM;
  int code = loadFromBinary(binaryInputStream, stream, verbose);
  fclose(binaryInputStream);

  // statistics
  if (code == 0 && verbose)
  {
    std::cout << "Parsed obj file '" << filename << "'; statistics:" << std::endl;
    std::cout << "   " << groups.size() << " groups," << std::endl;
    std::cout << "   " << getNumFaces() << " faces," << std::endl;
    std::cout << "   " << vertexPositions.size() << " vertices," << std::endl;
    std::cout << "   " << normals.size() << " normals, " << std::endl;
    std::cout << "   " << textureCoordinates.size() << " texture coordinates, " << std::endl;
  }
  return code;
}

int ObjMesh::loadFromBinary(void * binaryInputStream_, streamType stream, int verbose)
{
  unsigned int (*genericRead)(void *, unsigned int, unsigned int, void *);
  void * binaryInputStream;
  if (stream == MEMORY_STREAM)
  {
    genericRead = &ObjMesh::readFromMemory;
    binaryInputStream = &binaryInputStream_; // a wrapper for input stream
  }
  else
  {
    genericRead = &ObjMesh::readFromFile;
    binaryInputStream = binaryInputStream_;
  }

  const unsigned int defaultMaterialIndex = 0;
  Vec3d defaultKa(0.2,0.2,0.2);
  Vec3d defaultKd(0.6,0.6,0.6);
  Vec3d defaultKs(0.0,0.0,0.0);
  double defaultShininess = 65.0;

  unsigned int totalBytes;
  unsigned int items = genericRead(&totalBytes, sizeof(unsigned int), 1, binaryInputStream);
  if (items != 1)
  {
    if (verbose)
      printf("Error in ObjMesh::loadFromBinary: cannot read the number of total bytes.\n");
    return 1;
  }

  // important: subtract the bytes used to save totalBytes
  totalBytes -= sizeof(unsigned int);

  vector<unsigned char> objMeshBuffer;
  unsigned char * objMeshBufferPtr = NULL;
  if (stream == FILE_STREAM)
  {
    try 
    {
      objMeshBuffer.resize(totalBytes);
    }
    catch (std::bad_alloc const &) 
    {
      printf("Error in ObjMesh::loadFromBinary: cannot allocate buffer to read entire obj mesh.\n");
      return 1;
    }
    objMeshBufferPtr = &objMeshBuffer[0];

    items = genericRead(objMeshBufferPtr, sizeof(unsigned char), totalBytes, binaryInputStream);
    if (items != totalBytes)
    {
      if (verbose)
        printf("Error in ObjMesh::loadFromBinary: cannot read from the binary file.\n");
      return 1;
    }
  }
  else
    objMeshBufferPtr = (unsigned char *) binaryInputStream_; // use current input stream directly, NOT the binaryInputStream wrapper

  void * binaryInputBuffer = &objMeshBufferPtr;

  // read whether the mesh has materials or not 
  int hasMaterials = 0;
  readFromMemory(&hasMaterials, sizeof(int), 1, binaryInputBuffer);
  if (!hasMaterials)
  {
    // add default material
    addMaterial(string("default"), defaultKa, defaultKd, defaultKs, defaultShininess);
  }

  vector<double> doubleVec;
  if (hasMaterials)
  {
    // number of materials
    unsigned int numObjMaterials;
    readFromMemory(&numObjMaterials, sizeof(unsigned int), 1, binaryInputBuffer);
    if (numObjMaterials == 0)
    {
      // add default materials
      addMaterial(string("default"), defaultKa, defaultKd, defaultKs, defaultShininess);
    }

    // name of the materials
    for (unsigned int materialIndex=0; materialIndex < numObjMaterials; materialIndex++)
    {
      // the length of current material name
      unsigned int strLength;
      readFromMemory(&strLength, sizeof(unsigned int), 1, binaryInputBuffer);

      // material name
      char * materialName = (char *) malloc (sizeof(char) * (strLength + 1));
      readFromMemory(materialName, sizeof(char), strLength, binaryInputBuffer);
      materialName[strLength] = '\0';

      // add a new material
      addMaterial(materialName, defaultKa, defaultKd, defaultKs, defaultShininess);
    }

    // material properties
    // Ka, Kd, Ks, each of which has 3 doubles, plus Ns, a double
    // So there are 10 doubles for every material
    const int numDoubles = 10;
    doubleVec.resize(numDoubles * numObjMaterials);
    readFromMemory(&doubleVec[0], sizeof(double), numDoubles * numObjMaterials, binaryInputBuffer);
    for (unsigned int materialIndex=0; materialIndex < numObjMaterials; materialIndex++)
    {
      unsigned int offset = materialIndex * numDoubles;
      Vec3d Ka(&doubleVec[offset]);
      Vec3d Kd(&doubleVec[offset+3]);
      Vec3d Ks(&doubleVec[offset+6]);
      double shininess = doubleVec[offset+9] * 128.0 / 1000.0;
      materials[materialIndex].setKa(Ka);
      materials[materialIndex].setKd(Kd);
      materials[materialIndex].setKs(Ks);
      materials[materialIndex].setShininess(shininess);
    }

    // number of materials which have map_Kd images
    unsigned int numMaterialsHasKdImages;
    readFromMemory(&numMaterialsHasKdImages, sizeof(unsigned int), 1, binaryInputBuffer);
    for (unsigned int materialIndex=0; materialIndex < numMaterialsHasKdImages; materialIndex++)
    {
      // the material ID
      unsigned int materialID;
      readFromMemory(&materialID, sizeof(unsigned int), 1, binaryInputBuffer);

      // material image
      unsigned int strLength;
      readFromMemory(&strLength, sizeof(unsigned int), 1, binaryInputBuffer);
      char textureFilename[4096];
      readFromMemory(textureFilename, sizeof(char), strLength, binaryInputBuffer);
      textureFilename[strLength] = '\0';

      // set the image
      materials[materialID].setTextureFilename(textureFilename);
    }  // for materialIndex
  }  // if (hasMaterials)

  // the number of vertices
  unsigned int numVertices;
  readFromMemory(&numVertices, sizeof(unsigned int), 1, binaryInputBuffer);

  // vertices
  doubleVec.resize(numVertices * 3);
  readFromMemory(&doubleVec[0], sizeof(double), numVertices * 3, binaryInputBuffer);
  for(unsigned int vertexIndex=0; vertexIndex < numVertices; vertexIndex++)
  {
    unsigned int offset = vertexIndex * 3;
    Vec3d pos(doubleVec[offset], doubleVec[offset+1], doubleVec[offset+2]);
    vertexPositions.push_back(pos);
  }

  // the number of texture coordinates
  unsigned int numTexCoordinates;
  readFromMemory(&numTexCoordinates, sizeof(unsigned int), 1, binaryInputBuffer);

  // texture coordinates
  if (numTexCoordinates > 0)
  {
    doubleVec.resize(numTexCoordinates * 3);
    readFromMemory(&doubleVec[0], sizeof(double), numTexCoordinates * 3, binaryInputBuffer);
    for(unsigned int textureCoordinateIndex=0; textureCoordinateIndex < numTexCoordinates; textureCoordinateIndex++)
    {
      unsigned int offset = textureCoordinateIndex * 3;
      Vec3d tex(doubleVec[offset], doubleVec[offset+1], doubleVec[offset+2]);
      textureCoordinates.push_back(tex);
    }
  }

  // the number of normals
  unsigned int numNormals;
  readFromMemory(&numNormals, sizeof(unsigned int), 1, binaryInputBuffer);

  // normals
  if (numNormals > 0)
  {
    doubleVec.resize(numNormals * 3);
    readFromMemory(&doubleVec[0], sizeof(double), numNormals * 3, binaryInputBuffer);
    for(unsigned int normalIndex=0; normalIndex < numNormals; normalIndex++)
    {
      unsigned int offset = normalIndex * 3;
      Vec3d normal(doubleVec[offset], doubleVec[offset+1], doubleVec[offset+2]);
      normals.push_back(normal);
    }
  }

  // the number of groups
  unsigned int numGroups;
  readFromMemory(&numGroups, sizeof(unsigned int), 1, binaryInputBuffer);

  // groups and faces
  for(unsigned int groupIndex=0; groupIndex < numGroups; groupIndex++)
  {
    // group name
    unsigned int strLength;
    readFromMemory(&strLength, sizeof(unsigned int), 1, binaryInputBuffer);
    char groupName[4096];
    readFromMemory(groupName, sizeof(char), strLength, binaryInputBuffer);
    groupName[strLength] = '\0';

    // group material index
    if (hasMaterials)
    {
      // material index
      unsigned int materialIndex;
      readFromMemory(&materialIndex, sizeof(unsigned int), 1, binaryInputBuffer);
      groups.push_back(Group(groupName, materialIndex));
    }
    else
    {
      // use default material
      groups.push_back(Group(groupName, defaultMaterialIndex));
    }

    // the number of faces of the current group
    unsigned int numFaces;
    readFromMemory(&numFaces, sizeof(unsigned int), 1, binaryInputBuffer);

    // the number of vertices in every face
    unsigned int * numFaceVerticesArray = (unsigned int *) malloc (sizeof(unsigned int) * numFaces);
    readFromMemory(numFaceVerticesArray, sizeof(unsigned int), numFaces, binaryInputBuffer);

    unsigned int totalFaceVertices = 0;
    for (unsigned int faceIndex=0; faceIndex < numFaces; faceIndex++)
      totalFaceVertices += numFaceVerticesArray[faceIndex];

    // vertex indices of every face in the current group
    unsigned int * vertexArray = (unsigned int *) malloc (sizeof(unsigned int) * totalFaceVertices);
    readFromMemory(vertexArray, sizeof(unsigned int), totalFaceVertices, binaryInputBuffer);

    // texture coordinate indices of every face in the current group
    unsigned int * texCoordinateArray = (unsigned int *) malloc (sizeof(unsigned int) * totalFaceVertices);
    readFromMemory(texCoordinateArray, sizeof(unsigned int), totalFaceVertices, binaryInputBuffer);

    // normal indices of every face in the current group
    unsigned int * normalArray = (unsigned int *) malloc (sizeof(unsigned int) * totalFaceVertices);
    readFromMemory(normalArray, sizeof(unsigned int), totalFaceVertices, binaryInputBuffer);

    unsigned int vertexCount = 0;
    for (unsigned int faceIndex=0; faceIndex < numFaces; faceIndex++)
    {
      Face currentFace;
      for (unsigned int vertexIndex=0; vertexIndex < numFaceVerticesArray[faceIndex]; vertexIndex++)
      {
        unsigned int pos = vertexArray[vertexCount] - 1; // 0-indexed
        std::pair< bool, unsigned int > texPos;
        std::pair< bool, unsigned int > normal;

        if (texCoordinateArray[vertexCount] == 0)  // no texture coordinate index
        {
          texPos.first = false;
          texPos.second = 0;  
        }
        else
        {
          texPos.first = true;
          texPos.second = texCoordinateArray[vertexCount] - 1; 
        }

        if (normalArray[vertexCount] == 0)  // no normal index
        {
          normal.first = false;
          normal.second = 0;  
        }
        else
        {
          normal.first = true;
          normal.second = normalArray[vertexCount] - 1;
        }
        currentFace.addVertex(Vertex(pos, texPos, normal));

        vertexCount++;
      }  // for vertexIndex (current face)

      groups[groupIndex].addFace(currentFace);
    }

    free(numFaceVerticesArray);
    free(vertexArray);
    free(texCoordinateArray);
    free(normalArray);
  }  // for groupIndex

  // search if there is a "default" material, if not, add it
  addDefaultMaterial();

  return 0;
}

unsigned int ObjMesh::readFromMemory(void * buf, unsigned int elementSize, unsigned int numElements, void * memoryLocation_)
{
  unsigned char * memoryLocation = (unsigned char *)(*(void **)(memoryLocation_));
  unsigned int numBytes = elementSize * numElements;
  memcpy(buf, memoryLocation, numBytes);
  (*(void **)(memoryLocation_)) = (void *)((unsigned char *)(*(void **)(memoryLocation_)) + numBytes);
  return numElements;
}

unsigned int ObjMesh::readFromFile(void * buf, unsigned int elementSize, unsigned int numElements, void * fin)
{
  return fread(buf, elementSize, numElements, (FILE*)fin);
}

