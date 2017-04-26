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

// Renders the obj mesh.
// Written by Daniel Schroeder and Jernej Barbic, 2011

#ifndef _OBJMESHRENDER_H_
#define _OBJMESHRENDER_H_

#include <vector>
#include <assert.h>
#include "objMesh.h"

//flags for ObjMeshRender: 
//geometry mode
#define OBJMESHRENDER_TRIANGLES (1 << 0)
#define OBJMESHRENDER_EDGES (1 << 1)
#define OBJMESHRENDER_VERTICES (1 << 2)

//rendering mode
#define OBJMESHRENDER_NONE                (0)            /* render with only vertices */
#define OBJMESHRENDER_FLAT                (1 << 0)       /* render with facet normals */
#define OBJMESHRENDER_SMOOTH              (1 << 1)       /* render with vertex normals */
#define OBJMESHRENDER_TEXTURE             (1 << 2)       /* render with texture coords */
#define OBJMESHRENDER_COLOR               (1 << 3)       /* render with color materials */
#define OBJMESHRENDER_MATERIAL            (1 << 4)       /* render with materials */
#define OBJMESHRENDER_SELECTION           (1 << 5)       /* render with OpenGL selection (only applies to vertices, otherwise ignored) */
#define OBJMESHRENDER_CUSTOMCOLOR         (1 << 6)       /* render with custom vertex colors */
#define OBJMESHRENDER_TRANSPARENCY        (1 << 7)       /* render in two passes, to handle transparencies */
#define OBJMESHRENDER_CUSTOMCOLORFACES    (1 << 8)       /* render with custom face colors */

//texture mode: replace vs modulate
#define OBJMESHRENDER_LIGHTINGMODULATIONBIT 1
#define OBJMESHRENDER_GL_REPLACE 0
#define OBJMESHRENDER_GL_MODULATE 1

//texture mode: mipmapping
#define OBJMESHRENDER_MIPMAPBIT 2
#define OBJMESHRENDER_GL_NOMIPMAP 0
#define OBJMESHRENDER_GL_USEMIPMAP 2

//texture mode: anisotropic filtering
#define OBJMESHRENDER_ANISOTROPICFILTERINGBIT 4
#define OBJMESHRENDER_GL_NOANISOTROPICFILTERING 0
#define OBJMESHRENDER_GL_USEANISOTROPICFILTERING 4

//default alpha blending threshold for 2-pass rendering (for transparent textures)
#define OBJMESHRENDER_DEFAULT_ALPHA_BLENDING_THRESHOLD 0.5f

class ObjMeshRender
{
public:

  class Texture
  {
  public:
    Texture() : fullPath(std::string("__none")), texture(std::make_pair(false, 0)), textureMode(OBJMESHRENDER_GL_NOMIPMAP | OBJMESHRENDER_GL_MODULATE), bytesPerPixel(3) {}
    virtual ~Texture();

    static void loadTextureImage(std::string fullPath, int * width, int * height, int * bpp, unsigned char ** texData);

    void loadTexture(std::string fullPath, int textureMode); // also sets up OpenGl

    bool hasTexture() { return texture.first; }
    unsigned int getTexture() { assert( texture.first ); return texture.second; }

    std::string getFullPath() { return fullPath; }
    int getTextureMode() { return textureMode; }
    int getBytesPerPixel() { return bytesPerPixel; }

  protected:
    std::string fullPath;
    std::pair< bool, unsigned int > texture; // OpenGL texture ID
    int textureMode;
    int bytesPerPixel;

    static void flipImage(int width, int height, int bpp, unsigned char * image);
  };

  ObjMeshRender(ObjMesh * mesh);
  ~ObjMeshRender();

  void render(int geometryMode, int renderMode, int renderSingleGroup=-1);
  unsigned int createDisplayList(int geometryMode, int renderMode);

  // set custom colors, for OBJMESHRENDER_CUSTOMCOLOR mode
  void setCustomColors(const Vec3d & color); // constant color for each mesh vertex
  void setCustomColors(const std::vector<Vec3d> & colors); // specific color for every mesh vertex

  // set custom colors, for OBJMESHRENDER_CUSTOMCOLORFACES mode
  void setCustomColorsFaces(const Vec3d & color); // constant color for each mesh face
  void setCustomColorsFaces(const std::vector<Vec3d> & colors); // specific color for every mesh face

  void renderSpecifiedVertices(int * specifiedVertices, int numSpecifiedVertices);
  void renderVertex(int index);

  // the more specific rendering versions 
  void renderGroup(unsigned int groupIndex, int geometryMode, int renderMode);
  void renderGroup(const char * groupName, int geometryMode, int renderMode);
  void renderGroupEdges(const char * groupName);

  // render boundary edges
  void renderBoundaryEdges(); // does not use the display list
  unsigned int createBoundaryEdgesDisplayList();

  // render crease edges
  void renderCreaseEdges(double thresholdAngle=90.0); // does not use the display list 
  unsigned int createCreaseEdgesDisplayList(double thresholdAngle=90.0);

  // render silhouette edges
  void renderSilhouetteEdges(double cameraPos[3]); // does not use the display list 
  unsigned int createSilhouetteEdgesDisplayList(double cameraPos[3]);

  int numTextures();
  int maxBytesPerPixelInTextures();
  Texture * getTextureHandle(int textureIndex);
  void loadTextures(int textureMode, std::vector<Texture*> * texturePool=NULL, int updatePool=0);

  void renderNormals(double normalLength);

  // outputs OpenGL code to render faces
  void outputOpenGLRenderCode();

  // get/set alpha blending value, for OBJMESHRENDER_TRANSPARENCY mode
  double getAlphaBlendingThreshold() const { return alphaBlendingThreshold; }
  void setAlphaBlendingThreshold(double threshold) { alphaBlendingThreshold = threshold; }

protected:
  ObjMesh * mesh;
  std::vector<Vec3d> customColors;
  std::vector<Vec3d> customColorsFaces;
  std::vector< Texture* > textures;
  std::vector<int> ownTexture;
  double alphaBlendingThreshold;
};

#endif

