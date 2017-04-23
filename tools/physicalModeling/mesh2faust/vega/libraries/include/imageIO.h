/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "imageIO" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Yili Zhao, Jernej Barbic                                 *
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

/*
  Load/save PPM, PNG, JPEG, TIFF, TGA image formats.

  PPM and TGA are built-in (no external dependencies).
  PNG depends on libpng, JPEG depends on jpeglib and TIFF depends on libtiff.

  In order to enable PNG, JPEG or TIFF, uncomment the corresponding line in imageFormats.h, and link against the external library.
*/

#ifndef _IMAGEIO_H_
#define _IMAGEIO_H_

class ImageIO
{
public:

  ImageIO();

  // makeInternalCopy:
  // 0: do not copy pixels internally (shallow copy)
  // 1: copy pixels internally (deep copy)
  ImageIO(unsigned int width, unsigned int height, unsigned int bytesPerPixel, unsigned char * pixels, int makeInternalCopy=1);
  ~ImageIO();

  inline unsigned int getWidth() { return width; }
  inline unsigned int getHeight() { return height; }
  inline unsigned int getBytesPerPixel() { return bytesPerPixel; }
  inline unsigned char * getPixels() { return pixels; }
  inline unsigned char getPixel(int x, int y, int channel) { return pixels[(y * width + x) * bytesPerPixel + channel]; }

  // error codes
  typedef enum { OK, INVALID_FILE_FORMAT, IO_ERROR, MEMORY_ERROR, OTHER_ERROR } errorType;

  // generic loader, infers the file format automatically from the filename extension
  // input: filename
  // output: fileFormat
  typedef enum { FORMAT_PPM, FORMAT_TGA, FORMAT_JPEG, FORMAT_TIFF, FORMAT_PNG, FORMAT_NONE } fileFormatType;
  errorType load(const char * filename, fileFormatType * fileFormat);
  errorType save(const char * filename, fileFormatType fileFormat);

  // loaders specific to each file format

  // no external dependency
  errorType loadPPM(const char * filename);
  errorType savePPM(const char * filename);

  // uncompressed TGA only
  // no external dependency
  errorType loadTGA(const char * filename);
  errorType saveTGA(const char * filename); 

  // using jpeglib
  errorType loadJPEG(const char * filename);
  errorType saveJPEG(const char * filename);
  errorType saveJPEGWithGivenQuality(const char * filename, int quality = 95);

  // using libtiff
  errorType loadTIFF(const char * filename);
  errorType saveTIFF(const char * filename);

  // using libpng
  errorType loadPNG(const char * filename);
  errorType savePNG(const char * filename);

  // flips the image vertically
  void flipVertically(); 

protected:
  unsigned int width, height;
  unsigned int bytesPerPixel;
  unsigned char * pixels;
  int ownPixels;

  errorType loadNONE(const char * filename);
  errorType saveNONE(const char * filename);
};

#endif

