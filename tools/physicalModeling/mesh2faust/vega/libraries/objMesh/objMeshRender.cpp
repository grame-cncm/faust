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
  #define isnan _isnan
#endif

#include "openGL-headers.h"
#include <string.h>
#include "objMeshRender.h"
#include "imageIO.h"
using namespace std;

// this file (in the imageIO library) defines what image file formats are supported
// note: PPM and uncompressed TGA are always supported
#include "imageFormats.h"

// Renders the obj mesh.
// Written by Daniel Schroeder and Jernej Barbic, 2011
// Transparency and anisotropic filtering added by Jernej Barbic, 2012

void ObjMeshRender::Texture::loadTextureImage(string fullPath, int * width, int * height, int * bpp, unsigned char ** texData)
{
  ImageIO imageIO;
  ImageIO::fileFormatType fileFormat;
  // automatically determines the file format type from the filename extension; see imageIO class
  ImageIO::errorType errorCode = imageIO.load(fullPath.c_str(), &fileFormat);
  if (errorCode != ImageIO::OK)
  {
    printf("Warning: unable to load texture %s.\n", fullPath.c_str());
    return;
  }

  *width = imageIO.getWidth();
  *height = imageIO.getHeight();
  *bpp = imageIO.getBytesPerPixel();
  *texData = (unsigned char*) malloc (sizeof(unsigned char) * *width * *height * *bpp);
  memcpy(*texData, imageIO.getPixels(), sizeof(unsigned char) * *width * *height * *bpp);
}

void ObjMeshRender::Texture::loadTexture(string fullPath, int textureMode_)
{
  this->fullPath = fullPath;

  printf("Loading texture %s.\n", fullPath.c_str());

  int width = 0;
  int height = 0;
  unsigned char * texData = NULL;
  loadTextureImage(fullPath, &width, &height, &bytesPerPixel, &texData);

  glEnable(GL_TEXTURE_2D);
  textureMode = textureMode_;
  texture.first = true;
  glGenTextures(1, &(texture.second));
  glBindTexture(GL_TEXTURE_2D, texture.second);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if((textureMode & OBJMESHRENDER_MIPMAPBIT) == OBJMESHRENDER_GL_USEMIPMAP) 
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  } 
  else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }

  if((textureMode & OBJMESHRENDER_LIGHTINGMODULATIONBIT) == OBJMESHRENDER_GL_REPLACE)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  else
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  if ((width * bytesPerPixel) % 4 != 0)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // set internal format (3 or 4 bytes)
  GLint internalFormat = GL_RGB;
  GLenum format = GL_RGB;
  if (bytesPerPixel == 4)
  {
    internalFormat = GL_RGBA;
    format = GL_RGBA;
  }

  if((textureMode & OBJMESHRENDER_MIPMAPBIT) == OBJMESHRENDER_GL_NOMIPMAP)
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, texData);
  else
  {
    char * versionString = (char*) glGetString(GL_VERSION);
    double version = 0.0;
    if (versionString != NULL)  // glGetString will return NULL in an invalid OpenGL context; this is to protect from a seg fault if versionString is NULL on the next line
      version = strtod(versionString, NULL); 
    if (version >= 3.0)
    {
      //unsigned char * texData1 = (unsigned char*) malloc (sizeof(unsigned char) * width * height * bytesPerPixel);
      //for(int i=0; i<width*height*bytesPerPixel; i++)
        //texData[i] = 128;

      //printf("OpenGL version: %G\n", version);
      //glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, texData);
      //glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, texData1);
      //glGenerateMipmap(GL_TEXTURE_2D);
      gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, width, height, format, GL_UNSIGNED_BYTE, texData);
    }
    else
      gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, width, height, format, GL_UNSIGNED_BYTE, texData);
  }

  // enable anisotropic filtering (if requested)
  // also, check whether extension string can be found
  if (((textureMode & OBJMESHRENDER_ANISOTROPICFILTERINGBIT) == OBJMESHRENDER_GL_USEANISOTROPICFILTERING) && (strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic")))
  {
    #define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
    #define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

    float maxAnisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

    #undef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
    #undef GL_TEXTURE_MAX_ANISOTROPY_EXT
  }

  glDisable(GL_TEXTURE_2D);
  free(texData);
}

void ObjMeshRender::Texture::flipImage(int width, int height, int bpp, unsigned char * image)
{
  unsigned char * rowBuffer = (unsigned char*) malloc (sizeof(unsigned char) * bpp * width);
  for(int row=0; row < height / 2; row++)
  {
    int otherRow = height - 1 - row;

    // swap row and otherRow

    unsigned char * rowPixels = &image[bpp * width * row];
    unsigned char * otherRowPixels = &image[bpp * width * otherRow];

    // copy row to rowBuffer
    for(int i=0; i<bpp * width; i++)
      rowBuffer[i] = rowPixels[i];

    // copy otherRow to row
    for(int i=0; i<bpp * width; i++)
      rowPixels[i] = otherRowPixels[i];

    // copy rowBuffer to otherRow
    for(int i=0; i<bpp * width; i++)
      otherRowPixels[i] = rowBuffer[i];
  }
  free(rowBuffer);
}

ObjMeshRender::ObjMeshRender(ObjMesh * mesh_) : mesh(mesh_) 
{
  alphaBlendingThreshold = OBJMESHRENDER_DEFAULT_ALPHA_BLENDING_THRESHOLD;
}

ObjMeshRender::~ObjMeshRender()
{
  for(int i=0; i<(int)textures.size(); i++)
  {
    if (ownTexture[i])
    {
      delete(textures[i]);
      ownTexture[i] = 0;
    }
  }
  textures.clear();
}

void ObjMeshRender::renderGroup(unsigned int groupIndex, int geometryMode, int renderMode)
{
  render(geometryMode, renderMode, groupIndex);
}

void ObjMeshRender::renderGroup(const char * groupName, int geometryMode, int renderMode)
{
  // get the group
  std::string name(groupName);
  unsigned int groupIndex = mesh->getGroupIndex(name);
  render(geometryMode, renderMode, groupIndex);
}

void ObjMeshRender::render(int geometryMode, int renderMode, int renderSingleGroup)
{
  if (renderMode & OBJMESHRENDER_TRANSPARENCY)
  {
    //printf("Two-pass render.\n");
    // two-pass render
    int modifiedRenderMode = ((unsigned int)renderMode) & (~OBJMESHRENDER_TRANSPARENCY); 

    glEnable(GL_LIGHTING);
  
    // pass 1
    glEnable(GL_ALPHA_TEST);
    // glAlphaFunc(GL_EQUAL, 1.0);
    glAlphaFunc(GL_GREATER, alphaBlendingThreshold);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    render(geometryMode, modifiedRenderMode, renderSingleGroup);

    glEnable(GL_LIGHTING);
    
    // pass 2
    glEnable(GL_ALPHA_TEST);
    //glAlphaFunc(GL_LESS, 1.0);
    glAlphaFunc(GL_LEQUAL, alphaBlendingThreshold);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    render(geometryMode, modifiedRenderMode, renderSingleGroup);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    
    return;
  }

  bool warnMissingNormals = false;
  bool warnMissingFaceNormals = false;
  bool warnMissingTextureCoordinates = false;
  bool warnMissingTextures = false;
  //bool warnUnimplementedFlat = false;

  GLboolean lightingInitiallyEnabled = false;
  glGetBooleanv(GL_LIGHTING, &lightingInitiallyEnabled);
  //printf("lighting initially enabled: %d\n", lightingInitiallyEnabled);

  // resolve conflicts in render mode settings and/or mesh data
  if((renderMode & OBJMESHRENDER_FLAT) && (renderMode & OBJMESHRENDER_SMOOTH))
  {
    printf("Requested both FLAT and SMOOTH rendering; SMOOTH used\n");
    renderMode &= ~OBJMESHRENDER_FLAT;
  }

  if((renderMode & OBJMESHRENDER_COLOR) && (renderMode & OBJMESHRENDER_MATERIAL))
  {
    printf("Requested both COLOR and MATERIAL rendering; MATERIAL used\n");
    renderMode &= ~OBJMESHRENDER_COLOR;
  }

  if(renderMode & OBJMESHRENDER_COLOR)
    glEnable(GL_COLOR_MATERIAL);
  else if(renderMode & OBJMESHRENDER_MATERIAL)
    glDisable(GL_COLOR_MATERIAL);

  if(renderMode & OBJMESHRENDER_CUSTOMCOLOR)
    glDisable(GL_LIGHTING);

  // render triangles
  if(geometryMode & OBJMESHRENDER_TRIANGLES)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(geometryMode & (OBJMESHRENDER_EDGES | OBJMESHRENDER_VERTICES))
    {
      //glEnable(GL_POLYGON_OFFSET_FILL);
      //glPolygonOffset(2.0, 2.0);
    }

    int faceCount = 0;
    for(unsigned int i=0; i < mesh->getNumGroups(); i++)
    {
      if ((renderSingleGroup >= 0) && ((int)i != renderSingleGroup))     
        continue;

      const ObjMesh::Group * groupHandle = mesh->getGroupHandle(i);
      // set material
      const ObjMesh::Material * materialHandle = mesh->getMaterialHandle(groupHandle->getMaterialIndex());
      //printf("Material: %d\n",group.materialIndex());
      Vec3d Ka = materialHandle->getKa();
      Vec3d Kd = materialHandle->getKd();
      Vec3d Ks = materialHandle->getKs();

      float shininess = materialHandle->getShininess();
      float alpha = materialHandle->getAlpha();
      float ambient[4] = { (float)Ka[0], (float)Ka[1], (float)Ka[2], alpha };
      float diffuse[4] = { (float)Kd[0], (float)Kd[1], (float)Kd[2], alpha };
      float specular[4] = { (float)Ks[0], (float)Ks[1], (float)Ks[2], alpha };
      if(renderMode & OBJMESHRENDER_MATERIAL)
      {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
      }
      else if(renderMode & OBJMESHRENDER_COLOR)
      {
        glColor3fv(diffuse);
      }

      if((renderMode & OBJMESHRENDER_TEXTURE) && materialHandle->hasTextureFilename())
      {
        if(groupHandle->getMaterialIndex() >= textures.size())
        {
          //textures are missing
          warnMissingTextures = true;
        }
        else if (!textures[groupHandle->getMaterialIndex()]->hasTexture())
          warnMissingTextures = true;
        else
        {
          Texture * textureHandle = textures[groupHandle->getMaterialIndex()];
          glBindTexture(GL_TEXTURE_2D, textureHandle->getTexture());
          glEnable(GL_TEXTURE_2D);
          if((textureHandle->getTextureMode() & OBJMESHRENDER_LIGHTINGMODULATIONBIT) == OBJMESHRENDER_GL_REPLACE)
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
          else
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
          glEnable(GL_TEXTURE_2D);
        }
      }
      else
      {
        glDisable(GL_TEXTURE_2D);
      }

      //printf("amb: %G %G %G\n", Ka[0], Ka[1], Ka[2]);
      //printf("dif: %G %G %G\n", Kd[0], Kd[1], Kd[2]);
      //printf("spe: %G %G %G\n", Ks[0], Ks[1], Ks[2]);

      for(unsigned int iFace = 0; iFace < groupHandle->getNumFaces(); iFace++)
      {
        const ObjMesh::Face * faceHandle = groupHandle->getFaceHandle(iFace);

        glBegin(GL_POLYGON);
        if(renderMode & OBJMESHRENDER_FLAT)
        {
          if(faceHandle->hasFaceNormal())
          {
            Vec3d fnormal = faceHandle->getFaceNormal();
            glNormal3d(fnormal[0],fnormal[1],fnormal[2]);
          }
          else
            warnMissingFaceNormals = true;
        }

        Vec3d faceColor(0,0,0);
        if(renderMode & OBJMESHRENDER_CUSTOMCOLORFACES)
        {
          if (customColorsFaces.size() == 0)
            faceColor = Vec3d(0,0,1);
          else
            faceColor = customColorsFaces[faceCount];
        }

        for(unsigned int iVertex = 0; iVertex < faceHandle->getNumVertices(); iVertex++)
        {
          const ObjMesh::Vertex * vertexHandle = faceHandle->getVertexHandle(iVertex);
          Vec3d v = mesh->getPosition(*vertexHandle);
          int vertexPositionIndex = vertexHandle->getPositionIndex();

          // set normal
          if(renderMode & OBJMESHRENDER_SMOOTH)
          {
            if(vertexHandle->hasNormalIndex())
            {
              Vec3d normal = mesh->getNormal(*vertexHandle);
              if ((!isnan(normal[0])) && (!isnan(normal[1])) && (!isnan(normal[2])))
                glNormal3d(normal[0], normal[1], normal[2]);
              else
                glNormal3d(0, 1, 0);
            }
            else
              warnMissingNormals = true;
          }

          // set texture coordinate
          if(renderMode & OBJMESHRENDER_TEXTURE)
          {
            if(vertexHandle->hasTextureCoordinateIndex())
            {
              Vec3d vtexture = mesh->getTextureCoordinate(*vertexHandle);
              glTexCoord2d(vtexture[0], vtexture[1]);
            }
            else
              warnMissingTextureCoordinates = true;
          }

          if(renderMode & OBJMESHRENDER_CUSTOMCOLOR)
          {
            if (customColors.size() == 0)
              glColor3f(0,0,1);
            else
              glColor3f(customColors[vertexPositionIndex][0], customColors[vertexPositionIndex][1], customColors[vertexPositionIndex][2]);
          }

          if(renderMode & OBJMESHRENDER_CUSTOMCOLORFACES)
            glColor3f(faceColor[0], faceColor[1], faceColor[2]);

          // set position
          glVertex3d(v[0],v[1],v[2]);
        }

        glEnd();

        faceCount++;
      }

      if((renderMode & OBJMESHRENDER_TEXTURE))
        glDisable(GL_TEXTURE_2D);
    }

    if(geometryMode & (OBJMESHRENDER_EDGES | OBJMESHRENDER_VERTICES))
    {
      //glDisable(GL_POLYGON_OFFSET_FILL);
    }
  }

  // render vertices 
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);

  if(geometryMode & OBJMESHRENDER_VERTICES)
  {
    if (renderSingleGroup < 0)
    {
      int numVertices = mesh->getNumVertices();

      for(int i = 0; i < numVertices; i++)
      {
        if(renderMode & OBJMESHRENDER_SELECTION)
          glLoadName(i);  
        glBegin(GL_POINTS);
        Vec3d pos = mesh->getPosition(i);
        glVertex3f(pos[0], pos[1], pos[2]);
        glEnd();
      }
    }
    else
    {
      const ObjMesh::Group * groupHandle = mesh->getGroupHandle(renderSingleGroup);
      for(unsigned int iFace = 0; iFace < groupHandle->getNumFaces(); ++iFace)
      {
        const ObjMesh::Face * faceHandle = groupHandle->getFaceHandle(iFace);
        if(geometryMode & OBJMESHRENDER_VERTICES)
        {
          glBegin(GL_POINTS);
          for(unsigned int iVertex = 0; iVertex < faceHandle->getNumVertices(); ++iVertex)
          {
            const ObjMesh::Vertex * vertexHandle = faceHandle->getVertexHandle(iVertex);
            Vec3d v = mesh->getPosition(*vertexHandle);
            glVertex3d(v[0], v[1], v[2]);
          }
          glEnd();
        }
      }
    }
  }

  // render edges 
  if (geometryMode & OBJMESHRENDER_EDGES)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    //glPolygonOffset(1.0, 1.0);
    glPolygonOffset(-1.0, -1.0);
    for(unsigned int i=0; i < mesh->getNumGroups(); i++)
    {
      if ((renderSingleGroup >= 0) && ((int)i != renderSingleGroup))
        continue;

      const ObjMesh::Group * groupHandle = mesh->getGroupHandle(i);
      for(unsigned int iFace = 0; iFace < groupHandle->getNumFaces(); ++iFace)
      {
        const ObjMesh::Face * faceHandle = groupHandle->getFaceHandle(iFace);
        if(geometryMode & OBJMESHRENDER_EDGES)
        {
          glBegin(GL_POLYGON);
          for(unsigned int iVertex = 0; iVertex < faceHandle->getNumVertices(); ++iVertex)
          {
            const ObjMesh::Vertex * vertexHandle = faceHandle->getVertexHandle(iVertex);
            Vec3d v = mesh->getPosition(*vertexHandle);
            glVertex3d(v[0], v[1], v[2]);
          }
          glEnd();
        }
      }
    }
    glDisable(GL_POLYGON_OFFSET_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  if (lightingInitiallyEnabled)
    glEnable(GL_LIGHTING);

  //print warnings
  if(warnMissingNormals)
    printf("Warning: used SMOOTH rendering with missing vertex normal(s).\n");
  if(warnMissingFaceNormals)
    printf("Warning: used FLAT rendering with missing face normal(s).\n");
  if(warnMissingTextureCoordinates)
    printf("Warning: used TEXTURE rendering with missing texture coordinate(s).\n");
  if(warnMissingTextures)
    printf("Warning: used TEXTURE rendering with un-setup texture(s).\n");
}

unsigned int ObjMeshRender::createDisplayList(int geometryMode, int renderMode)
{
  unsigned int list = glGenLists(1);
  glNewList(list, GL_COMPILE);
  render(geometryMode, renderMode);
  glEndList();
  return list;
}

void ObjMeshRender::renderSpecifiedVertices(int * specifiedVertices, int numSpecifiedVertices)
{
  glBegin(GL_POINTS);

  for(int i = 0; i < numSpecifiedVertices; i++)
  {
    renderVertex(specifiedVertices[i]);
  }

  glEnd();
}

void ObjMeshRender::renderVertex(int index)
{
  Vec3d pos = mesh->getPosition(index);
  glVertex3f(pos[0], pos[1], pos[2]);
}

void ObjMeshRender::renderGroupEdges(const char * groupName)
{
  //get the group
  string name(groupName);
  ObjMesh::Group group = mesh->getGroup(name);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_POLYGON_OFFSET_LINE);
  glPolygonOffset(1.0, 1.0);

  for( unsigned int iFace = 0; iFace < group.getNumFaces(); ++iFace )
  {
    ObjMesh::Face face = group.getFace(iFace);

    glBegin(GL_POLYGON);
    for( unsigned int iVertex = 0; iVertex < face.getNumVertices(); ++iVertex )
    {
      const ObjMesh::Vertex * vertexHandle = face.getVertexHandle(iVertex);
      Vec3d v = mesh->getPosition(*vertexHandle);
      glVertex3d(v[0], v[1], v[2]);
    }
    glEnd();
  }

  glDisable(GL_POLYGON_OFFSET_LINE);
}

int ObjMeshRender::numTextures()
{
  int numTextures = 0;
  int numMaterials = mesh->getNumMaterials();
  for(int i = 0; i < numMaterials; i++)
  {
    const ObjMesh::Material * material = mesh->getMaterialHandle(i);

    if(material->hasTextureFilename())
      numTextures++;
  }
  return numTextures;
}

void ObjMeshRender::loadTextures(int textureMode, std::vector<Texture*> * texturePool, int updatePool)
{
  //clear old
  for(int i=0; i<(int)textures.size(); i++)
  {
    if (ownTexture[i])
    {
      delete(textures[i]);
      ownTexture[i] = 0;
    }
  }
  textures.clear();

  int numMaterials = mesh->getNumMaterials();
  textures.resize(numMaterials);
  ownTexture.resize(numMaterials);

  const ObjMesh::Material * material;
  char path[4096];
  string objName = mesh->getFilename();
  mesh->dirname(objName.c_str(), path);
  string pathStr = string(path);

  for(int i = 0; i < numMaterials; i++)
  {
    material = mesh->getMaterialHandle(i);
    if(!material->hasTextureFilename())
    {
      ownTexture[i] = 0;
      continue;
    }

    string fullPath = pathStr + string("/") + material->getTextureFilename();

    int found = 0;
    if (texturePool != NULL)
    {
      // seek for this texture in the texture pool
      for(int j=0; j<(int)texturePool->size(); j++)
      {
        std::string poolFullPath = (*texturePool)[j]->getFullPath();
        if (fullPath == poolFullPath)
        {
          //printf("Texture %s discovered in the texture pool. Avoiding reload.\n", fullPath.c_str());
          textures[i] = (*texturePool)[j];
          ownTexture[i] = 0;
          found = 1;
          break;
        }
      }
    }

    if (!found)
    {
      textures[i] = new Texture();
      ownTexture[i] = 1;
      textures[i]->loadTexture(fullPath, textureMode);
      if (updatePool)
        texturePool->push_back(textures[i]);
    }
  }
}

ObjMeshRender::Texture * ObjMeshRender::getTextureHandle(int textureIndex)
{
  return textures[textureIndex];
}

ObjMeshRender::Texture::~Texture()
{
  if (texture.first) 
    glDeleteTextures(1, &(texture.second));
}

void ObjMeshRender::outputOpenGLRenderCode()
{
  for(unsigned int i=0; i < mesh->getNumGroups(); i++)
  {
    const ObjMesh::Group * groupHandle = mesh->getGroupHandle(i);

    // set material
    ObjMesh::Material material = mesh->getMaterial(groupHandle->getMaterialIndex());

    Vec3d Ka = material.getKa();
    Vec3d Kd = material.getKd();
    Vec3d Ks = material.getKs();
    float shininess = material.getShininess();

    printf("float ambient[4] = { %f, %f, %f, 1.0 };\n", Ka[0], Ka[1], Ka[2]);
    printf("float diffuse[4] = { %f, %f, %f, 1.0 };\n", Kd[0], Kd[1], Kd[2]);
    printf("float specular[4] = { %f, %f, %f, 1.0 };\n", Ks[0], Ks[1], Ks[2]);

    printf("glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);\n");
    printf("glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);\n");
    printf("glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);\n");
    printf("glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, %f);\n", shininess);

    for( unsigned int iFace = 0; iFace < groupHandle->getNumFaces(); ++iFace )
    {
      ObjMesh::Face face = groupHandle->getFace(iFace);

      printf("glBegin(GL_POLYGON);\n");

      for( unsigned int iVertex = 0; iVertex < face.getNumVertices(); ++iVertex )
      {
        const ObjMesh::Vertex * vertexHandle = face.getVertexHandle(iVertex);
        Vec3d v = mesh->getPosition(*vertexHandle);

        // set normal
        if( vertexHandle->hasNormalIndex() )
        {
          Vec3d normal = mesh->getNormal(*vertexHandle);
          printf("glNormal3d(%f,%f,%f);\n", normal[0], normal[1], normal[2]);
        }

        // set texture coordinate
        if(vertexHandle->hasTextureCoordinateIndex())
        {
          Vec3d textureCoordinate = mesh->getTextureCoordinate(*vertexHandle);
          printf("glTexCoord2d(%f,%f);\n", textureCoordinate[0], textureCoordinate[1]);
        }

        printf("glVertex3d(%f,%f,%f);\n", v[0],v[1],v[2]);
      }
      printf("glEnd();\n");
    }
  }
}

void ObjMeshRender::renderNormals(double normalLength)
{
  double diameter = mesh->getDiameter();

  glBegin(GL_LINES);

  for(unsigned int i=0; i < mesh->getNumGroups(); i++)
  {
    const ObjMesh::Group * groupHandle = mesh->getGroupHandle(i);
    for(unsigned int iFace = 0; iFace < groupHandle->getNumFaces(); ++iFace)
    {
      ObjMesh::Face face = groupHandle->getFace(iFace);

      for(unsigned int iVertex = 0; iVertex < face.getNumVertices(); ++iVertex)
      {
        const ObjMesh::Vertex * vertexHandle = face.getVertexHandle(iVertex);
        Vec3d v = mesh->getPosition(*vertexHandle);

        glVertex3d(v[0], v[1], v[2]);

        // compute endpoint
        Vec3d vnormalOffset;
        if(vertexHandle->hasNormalIndex())
          vnormalOffset = v + normalLength * diameter * mesh->getNormal(*vertexHandle);
        else
          vnormalOffset = v;

        glVertex3d(vnormalOffset[0], vnormalOffset[1], vnormalOffset[2]);
      }
    }
  }

  glEnd();
}

void ObjMeshRender::setCustomColors(const Vec3d & color)
{
  int numVertices = (int)mesh->getNumVertices();
  customColors.clear();
  for(int i=0; i<numVertices; i++)
    customColors.push_back(color);
}

void ObjMeshRender::setCustomColors(const vector<Vec3d> & colors)
{
  int numVertices = (int)mesh->getNumVertices();
  customColors.clear();
  for(int i=0; i<numVertices; i++)
    customColors.push_back(colors[i]);
}

void ObjMeshRender::setCustomColorsFaces(const Vec3d & color)
{
  int numFaces = (int)mesh->getNumFaces();
  customColorsFaces.clear();
  for(int i=0; i<numFaces; i++)
    customColorsFaces.push_back(color);
}

void ObjMeshRender::setCustomColorsFaces(const vector<Vec3d> & colors)
{
  int numFaces = (int)mesh->getNumFaces();
  customColorsFaces.clear();
  for(int i=0; i<numFaces; i++)
    customColorsFaces.push_back(colors[i]);
}

int ObjMeshRender::maxBytesPerPixelInTextures()
{
  int maxBytes = 0;

  int numMaterials = mesh->getNumMaterials();
  for(int i=0; i<numMaterials; i++)
  {
    const ObjMesh::Material * material = mesh->getMaterialHandle(i);
    if(!material->hasTextureFilename())
      continue;

    Texture * tex = getTextureHandle(i);
    int bpp = tex->getBytesPerPixel();
    if (bpp > maxBytes)
      maxBytes = bpp;
  }

  return maxBytes;
}

void ObjMeshRender::renderBoundaryEdges()
{

}

void ObjMeshRender::renderCreaseEdges(double thresholdAngle)
{

}

void ObjMeshRender::renderSilhouetteEdges(double cameraPos[3])
{

}

unsigned int ObjMeshRender::createBoundaryEdgesDisplayList()
{
  unsigned int list = glGenLists(1);
  glNewList(list, GL_COMPILE);
  renderBoundaryEdges();
  glEndList();
  return list;
}

unsigned int ObjMeshRender::createCreaseEdgesDisplayList(double thresholdAngle)
{
  unsigned int list = glGenLists(1);
  glNewList(list, GL_COMPILE);
  renderCreaseEdges(thresholdAngle);
  glEndList();
  return list;
}

unsigned int ObjMeshRender::createSilhouetteEdgesDisplayList(double cameraPos[3])
{
  unsigned int list = glGenLists(1);
  glNewList(list, GL_COMPILE);
  renderSilhouetteEdges(cameraPos);
  glEndList();
  return list;
}

