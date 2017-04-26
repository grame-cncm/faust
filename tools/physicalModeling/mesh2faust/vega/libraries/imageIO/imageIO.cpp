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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(WIN32)
  #pragma warning(disable : 4996)
#endif

#include "imageFormats.h"

#ifdef ENABLE_TIFF
  #include <tiffio.h>
#endif

#ifdef ENABLE_JPEG
extern "C"
{
  #include <jpeglib.h> 
}
#endif

#ifdef ENABLE_PNG
extern "C"
{
  #include <png.h> 
}
#endif

#include "imageIO.h"
#include "vegalong.h"

#define BITS_PER_CHANNEL_8 8
#define BITS_PER_CHANNEL_16 16
#define IMAGE_IO_RGB 3
#define IMAGE_IO_RGB_ALPHA 4
#define IMAGE_IO_HORIZONTAL_DIFFERENCING 2
#define IMAGE_IO_UNCOMPRESSED_RGB 2

ImageIO::ImageIO()
{
  width = 0;
  height = 0;
  bytesPerPixel = 0;
  pixels = NULL;
  ownPixels = 0;
}

ImageIO::ImageIO(unsigned int width_, unsigned int height_, unsigned int bytesPerPixel_, unsigned char * pixels_, int makeInternalCopy) :
  width(width_), height(height_), bytesPerPixel(bytesPerPixel_)
{
  if (makeInternalCopy == 0)
  {
    pixels = pixels_;
    ownPixels = 0;
  }
  else
  {
    pixels = (unsigned char*) malloc (sizeof(unsigned char) * width * height * bytesPerPixel);
    memcpy(pixels, pixels_, sizeof(unsigned char) * width * height * bytesPerPixel);
    ownPixels = 1;
  }
}

ImageIO::~ImageIO() 
{ 
  if (ownPixels)
    free(pixels); 
}

ImageIO::errorType ImageIO::loadPPM(const char * filename)
{
  FILE * file = fopen(filename, "rb");
  if(!file)
    return IO_ERROR;

  char buf[4096];
  char * result = fgets(buf, 4096, file);
  result = result + 1; // to avoid a compiler warning
  if(strncmp(buf, "P6", 2))
  {
    printf("Error in loadPPM: File is not a raw RGB ppm.\n");
    fclose(file);
    return INVALID_FILE_FORMAT;
  }

  // read image width and height
  int i = 0;
  int maxval;
  while(i < 3)
  {
    char * dummy = fgets(buf, 4096, file);
    dummy = dummy + 1; // to suppress compiler warning
    if(buf[0] == '#') // ignore comments
      continue;
    if(i == 0)
      i += sscanf(buf, "%d %d %d", &width, &height, &maxval);
    else if (i == 1)
      i += sscanf(buf, "%d %d", &height, &maxval);
    else if (i == 2)
      i += sscanf(buf, "%d", &maxval);
  }

  bytesPerPixel = 3;

  // read the pixels
  if(ownPixels)
    free(pixels);
  pixels = (unsigned char*) malloc (sizeof(unsigned char) * 3 * width * height);
  ownPixels = 1;
  if(fread(pixels, sizeof(unsigned char), 3 * width * height, file) < 3 * width * height)
  {
    printf("Error in loadPPM: Error reading ppm image from %s.\n", filename);
    fclose(file);
    return IO_ERROR;
  }

  fclose(file);

  flipVertically();

  return OK;
}

ImageIO::errorType ImageIO::savePPM(const char * filename)
{
  FILE * file = fopen(filename, "wb");
  if(!file)
    return IO_ERROR;

  unsigned char * pixelsNoAlphaChannel = NULL;
  if (bytesPerPixel == 4) // special case, alpha channel byte will be dropped
  {
    printf("Warning in savePPM: Alpha channel has been dropped when the image is saved in PPM format.\n");
    pixelsNoAlphaChannel = (unsigned char *) malloc (sizeof(unsigned char) * width * height * 3);
    for(unsigned int pixelIndex = 0; pixelIndex < width * height; pixelIndex++)
      memcpy(&pixelsNoAlphaChannel[pixelIndex*3], &pixels[pixelIndex*4], sizeof(unsigned char) * 3);
  }
  else
    pixelsNoAlphaChannel = pixels;

  fprintf(file, "P6 %d %d 255\n", width, height);

  for (int row = height - 1; row >= 0; row--)
  {
    unsigned int pos = row * width * 3;
    if (fwrite(&pixelsNoAlphaChannel[pos], sizeof(unsigned char), 3 * width, file) != 3 * width)
    {
      printf("Error in savePPM: Error while saving ppm image to %s.\n", filename);
      if (bytesPerPixel == 4)
        free(pixelsNoAlphaChannel);
      fclose(file);
      return IO_ERROR;
    }
  }

  fclose(file);

  if (bytesPerPixel == 4)
    free(pixelsNoAlphaChannel);

  return OK;
}

ImageIO::errorType ImageIO::loadTGA(const char * filename)
{
  FILE * file = fopen(filename, "rb");
  if (!file)
  {
    printf("Error in loadTGA: Cannot open file %s.\n", filename);
    return IO_ERROR;
  }

  unsigned char type[4];
  if (fread (&type, sizeof (char), 3, file) < 3)
  {
    printf("Error in loadTGA: Error reading tga image from %s.\n", filename);
    fclose(file);
    return IO_ERROR;
  }

  if (fseek (file, 12, SEEK_SET) != 0)
  {
    printf("Error in loadTGA: Error reading tga image from %s.\n", filename);
    fclose(file);
    return IO_ERROR;
  }

  unsigned char info[6];
  if ( fread (&info, sizeof (char), 6, file) < 6 )
  {
    printf("Error in loadTGA: Error reading tga image from %s.\n", filename);
    fclose(file);
    return IO_ERROR;
  }

  // image type is either 2 (color) or 3 (grayscale)
  if ((type[1] != 0) || ((type[2] != 2) && (type[2] != 3)))
  {
    fclose(file);
    printf("Error in loadTGA: Invalid file type.\n");
    printf("type[1]=%d type[2]=%d\n", type[1], type[2]);
    return INVALID_FILE_FORMAT;
  }

  width = info[0] + 256 * info[1];
  height = info[2] + 256 * info[3];
  bytesPerPixel = info[4] / 8;

  if ((bytesPerPixel != 3) && (bytesPerPixel != 4))
  {
    fclose(file);
    printf("Error in loadTGA: Invalid number of bytes per pixel: %d.\n", bytesPerPixel);
    return INVALID_FILE_FORMAT;
  }

  vegalong imageSize = width * height * bytesPerPixel;

  // allocate memory for image data
  if(ownPixels)
    free(pixels);
  pixels = (unsigned char*) malloc (sizeof(unsigned char) * imageSize);
  ownPixels = 1;

  // read image data
  if ( (int)fread(pixels, sizeof(unsigned char), imageSize, file) < imageSize)
  {
    printf("Error in loadTGA: Error reading tga image from %s.\n", filename);
    fclose(file);
    return IO_ERROR;
  }

  // The order of the color in tga is BGR(A) not RGB(A), so 
  for(unsigned int pixelIndex = 0; pixelIndex < width * height; pixelIndex++)
  {
    unsigned int offset = pixelIndex * bytesPerPixel;
    unsigned char temp;
    enum{R, G, B, A};
    temp = pixels[offset + R];
    pixels[offset + R] = pixels[offset + B];
    pixels[offset + B] = temp;
  } 

  // close file
  fclose(file);

  return OK;
}

ImageIO::errorType ImageIO::saveTGA(const char * filename)
{
  // This routine writes the result as a uncompressed TGA file
  FILE *file = fopen(filename, "wb");
  if (!file)
  {
    printf("Error in saveTGA: Cannot open file %s.\n", filename);
    return IO_ERROR;
  }

  // we write the header in little endian manner, 
  // namely, information is stored with the low order byte followed by the high order byte.

  unsigned char buf;
  #define WRITECHAR(ch)\
    buf = (ch);\
    fwrite(&buf, sizeof(unsigned char), 1, file);

  WRITECHAR(0);       // id length, length of a string located after the header, 0 = no string
  WRITECHAR(0);       // color map type
  WRITECHAR(IMAGE_IO_UNCOMPRESSED_RGB);      // data type code

  WRITECHAR(0); 
  WRITECHAR(0);       // short integer, color map origin (little endian)

  WRITECHAR(0); 
  WRITECHAR(0);       // short integer, color map length (little endian)

  WRITECHAR(0);       // color map depth

  WRITECHAR(0); 
  WRITECHAR(0);       // short integer, x origin (little endian)

  WRITECHAR(0); 
  WRITECHAR(0);       // short integer, y origin (little endian)

  WRITECHAR(width % 256);
  WRITECHAR((width / 256) % 256);     // image width (little endian)
  WRITECHAR(height % 256);  
  WRITECHAR((height / 256) % 256);    // image height (little endian)

  switch (bytesPerPixel)
  {
  case IMAGE_IO_RGB_ALPHA:
    WRITECHAR(32);                       // 32 bit bitmap
  	break;

  case IMAGE_IO_RGB:
    WRITECHAR(24);                       // 24 bit map
    break;

  default:
    printf("Error in saveTGA: cannot handle the case where bytes per pixel is neither 3 nor 4.\n");
    fclose(file);
    return IO_ERROR;
    break;
  }

  WRITECHAR(0);                          // image descriptor
  
  unsigned char * pixelBuf = (unsigned char*) malloc (sizeof(unsigned char) * width * height * bytesPerPixel);
  if (pixelBuf == NULL)
  {
    printf("Error in saveTGA: cannot allocate memory for pixel buffer.\n");
    fclose(file);
    return IO_ERROR;
  }
  memcpy(pixelBuf, pixels, sizeof(unsigned char) * width * height * bytesPerPixel);
  
  // The order of the color is BGR(A) not RGB(A)
  for(unsigned int pixelIndex = 0; pixelIndex < width * height; pixelIndex++)
  {
    unsigned int offset = pixelIndex * bytesPerPixel;
    unsigned char temp;
    enum{R, G, B, A};
    temp = pixelBuf[offset + R];
    pixelBuf[offset + R] = pixelBuf[offset + B];
    pixelBuf[offset + B] = temp;
  }  

  fwrite(pixelBuf, sizeof(unsigned char), width * height * bytesPerPixel, file);

  free(pixelBuf);
  fclose(file);
  return OK;

  #undef WRITECHAR
}

ImageIO::errorType ImageIO::loadJPEG(const char * filename)
{
#ifdef ENABLE_JPEG
  FILE * file = fopen(filename, "rb");
  if(!file)
    return IO_ERROR;

  struct jpeg_decompress_struct jpgPicture;
  
  struct jpeg_error_mgr jpgErrorMessage;

  jpgPicture.err = jpeg_std_error(&jpgErrorMessage);
  j_decompress_ptr jpgPicturePtr = (j_decompress_ptr)(&jpgPicture);
  
  jpeg_create_decompress(jpgPicturePtr);  // Init
  jpeg_stdio_src(jpgPicturePtr, file);  // setup image source

  // read information of the image
  jpeg_read_header(jpgPicturePtr, TRUE);
  
  jpeg_start_decompress(jpgPicturePtr);
  
  width = jpgPicturePtr->image_width;
  height = jpgPicturePtr->image_height;

  // Careful: the bytesPerPixel information is not available in the jpeg header.
  // It is only available after calling jpeg_start_decompress().
  bytesPerPixel = jpgPicturePtr->output_components;

  if(ownPixels)
    free(pixels);
  pixels = (unsigned char *) malloc(sizeof(unsigned char) * width * height * bytesPerPixel);
  ownPixels = 1;
//  printf("Width = %d; Height = %d, bytesPerPixel = %d\n", width, height, bytesPerPixel);
//  fflush(NULL);

  JSAMPROW rowPtr[1];
  for(int row= jpgPicturePtr->output_height - 1; jpgPicturePtr->output_scanline < jpgPicturePtr->output_height; row--)
  {
    rowPtr[0] = (JSAMPROW) &pixels[row * width * bytesPerPixel];
    JDIMENSION maxNumLines = 1;
    if (jpeg_read_scanlines(jpgPicturePtr, (JSAMPARRAY)rowPtr, maxNumLines) != maxNumLines)
    {
      printf("Error in loadJPEG: Error reading jpg image from %s.\n", filename);
      jpeg_destroy_decompress(jpgPicturePtr);
      fclose(file);
      return IO_ERROR;
    }
  }

  jpeg_finish_decompress(jpgPicturePtr);
  
  jpeg_destroy_decompress(jpgPicturePtr);

  fclose(file);
  return OK;

#else
  return INVALID_FILE_FORMAT;
#endif
}

ImageIO::errorType ImageIO::saveJPEG(const char * filename)
{
  return saveJPEGWithGivenQuality(filename, 95);
}

ImageIO::errorType ImageIO::saveJPEGWithGivenQuality(const char * filename, int quality)
{
#ifdef ENABLE_JPEG

  FILE * file = fopen(filename, "wb");
  if(!file)
    return IO_ERROR;

  struct jpeg_compress_struct jpgPicture;
  struct jpeg_error_mgr jpgErrorMessage;

  jpgPicture.err = jpeg_std_error(&jpgErrorMessage);
  jpeg_create_compress(&jpgPicture);   // Init
  jpeg_stdio_dest(&jpgPicture, file);  // setup image destination

  unsigned char * pixelsNoAlphaChannel = NULL;
  if (bytesPerPixel == 4) // special case, alpha channel byte will be dropped
  {
    printf("Warning in saveJPEG: Alpha channel has been dropped when the image is saved in JPEG format.\n");
    pixelsNoAlphaChannel = (unsigned char *) malloc (sizeof(unsigned char) * width * height * 3);
    for(unsigned int pixelIndex = 0; pixelIndex < width * height; pixelIndex++)
      memcpy(&pixelsNoAlphaChannel[pixelIndex*3], &pixels[pixelIndex*4], sizeof(unsigned char) * 3);
  }
  else
    pixelsNoAlphaChannel = pixels;

  jpgPicture.image_width = width; 
  jpgPicture.image_height = height;
  jpgPicture.input_components = 3;		
  jpgPicture.in_color_space = JCS_RGB; 	// color space of the image

  jpeg_set_defaults(&jpgPicture);
  jpeg_set_quality(&jpgPicture, quality, TRUE);
  jpeg_start_compress(&jpgPicture, TRUE);

  JSAMPROW rowPtr[1];
  unsigned int numBytesPerRow = width * 3;
  for(int row = jpgPicture.image_height - 1; jpgPicture.next_scanline < jpgPicture.image_height; row--)
  {
    rowPtr[0] = &pixelsNoAlphaChannel[row * numBytesPerRow];
    JDIMENSION maxNumLines = 1;
    if (jpeg_write_scanlines(&jpgPicture, rowPtr, maxNumLines) != maxNumLines)
    {
      printf("Error in saveJPEG: Error while saving jpg image to %s.\n", filename);
      jpeg_destroy_compress(&jpgPicture);
      if(bytesPerPixel == 4)
        free(pixelsNoAlphaChannel);
      fclose(file);
      return IO_ERROR;
    }
  }

  jpeg_finish_compress(&jpgPicture);
  
  jpeg_destroy_compress(&jpgPicture);

  fclose(file);

  if(bytesPerPixel == 4)
    free(pixelsNoAlphaChannel);
  return OK;
#else
  return INVALID_FILE_FORMAT;
#endif
}

ImageIO::errorType ImageIO::loadTIFF(const char * filename)
{
#ifdef ENABLE_TIFF
  TIFF * tiff = TIFFOpen(filename, "r");
  if (!tiff)
    return IO_ERROR;

  // read the dimensions
  uint32 tiff_width, tiff_height;
  uint16 tiff_samplesPerPixel;
  uint16 tiff_bits;
  TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &tiff_width);
  TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &tiff_height);
  TIFFGetField(tiff, TIFFTAG_SAMPLESPERPIXEL, &tiff_samplesPerPixel);
  TIFFGetField(tiff, TIFFTAG_BITSPERSAMPLE, &tiff_bits);

  //printf("tiff_width: %d tiff_height: %d tiff_samplesPerPixel: %d tiff_bits: %d\n", tiff_width, tiff_height, tiff_samplesPerPixel, tiff_bits);

  if ((tiff_samplesPerPixel != IMAGE_IO_RGB) && (tiff_samplesPerPixel != IMAGE_IO_RGB_ALPHA))
  {
    printf("Error in loadTIFF: Sorry, cannot handle %d-channel images.\n", tiff_samplesPerPixel);
    TIFFClose(tiff);
    return OTHER_ERROR;
  }

  if (tiff_bits != BITS_PER_CHANNEL_8)
  {
    printf("Error in loadTIFF: Sorry, cannot handle %d-bit images.\n", tiff_bits);
    TIFFClose(tiff);
    return OTHER_ERROR;
  }

  width = tiff_width;
  height = tiff_height;
  bytesPerPixel = tiff_samplesPerPixel;

  uint32 * tiff_pixels = (uint32*) _TIFFmalloc(tiff_width * tiff_height * sizeof(uint32));
  if (!tiff_pixels)
  {
    TIFFClose(tiff);
    return MEMORY_ERROR;
  }

  printf("Loading TIFF image from file %s: resolution: %d x %d, %d-bit.\n", filename, width, height, 8 * bytesPerPixel);
 
  int stopOnError = 1;
  if (!TIFFReadRGBAImage(tiff, tiff_width, tiff_height, tiff_pixels, stopOnError))
  { 
    _TIFFfree(tiff_pixels);
    TIFFClose(tiff);
    printf("Error in loadTIFF: Unknown error when calling TIFFReadRGBAImage.\n");
    return IO_ERROR;
  }

  if(ownPixels)
    free(pixels);
  pixels = (unsigned char*) malloc (sizeof(unsigned char) * width * height * bytesPerPixel);
  ownPixels = 1;

  // write tiff_pixels into the pixels array
  int counter = 0;
  for(unsigned int row=0; row < height; row++)
  {
    for(unsigned int column=0; column < width; column++)
    {
      // read the uint32 pixel
      uint32 tiff_pixel = tiff_pixels[row * tiff_width + column];

      // write R,G,B,A in place into pixels
      pixels[counter] = TIFFGetR(tiff_pixel);
      counter++;

      if (bytesPerPixel < 3) 
        continue;

      pixels[counter] = TIFFGetG(tiff_pixel);
      counter++;
      pixels[counter] = TIFFGetB(tiff_pixel);
      counter++;

      if (bytesPerPixel < 4) 
        continue;

      // alpha channel
      pixels[counter] = TIFFGetA(tiff_pixel);
      counter++;
    }
  }

  _TIFFfree(tiff_pixels);
  TIFFClose(tiff);

  return OK;

#else
  return INVALID_FILE_FORMAT;
#endif
}

ImageIO::errorType ImageIO::saveTIFF(const char * filename)
{
#ifdef ENABLE_TIFF

  TIFF *tif;

  tif = TIFFOpen(filename, "w");
  if( !tif )
  {
    printf("Error in saveTIFF: Cannot open file %s.\n", filename);
    return IO_ERROR;
  }

  TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, bytesPerPixel);
  TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
  TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, BITS_PER_CHANNEL_8);
  TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  if (bytesPerPixel < IMAGE_IO_RGB)
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
  else
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
  TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_LZW);
  TIFFSetField(tif, TIFFTAG_PREDICTOR, IMAGE_IO_HORIZONTAL_DIFFERENCING);

  tsize_t bytesPerRow = bytesPerPixel * width;    
  
  if (TIFFScanlineSize(tif) != bytesPerRow)
  {
    printf("Error in saveTIFF: the scanline size mismatches the length in memory of one row of pixels in the image.\n");
    TIFFClose(tif);
    return IO_ERROR;
  }
  
  unsigned char * imageBuf = (unsigned char *)_TIFFmalloc(TIFFScanlineSize(tif));
  if (imageBuf == NULL)
  {
    printf("Error in saveTIFF: cannot allocate memory for the storage of a row of pixels.\n");
    TIFFClose(tif);
    return IO_ERROR;
  }

  // Set the strip size of the file to be the size of one row of pixels
  TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif, (uint32)bytesPerRow));

  for (unsigned int row = 0; row < height; row++)
  {
    memcpy(imageBuf, &pixels[(height - row - 1) * bytesPerRow], sizeof(unsigned char) * bytesPerRow); 
    if (TIFFWriteScanline(tif, imageBuf, row, 0) < 0)  // an error occurred while writing the image
    {
      printf("Error in saveTIFF: Error while saving TIFF image to %s.\n", filename);
      _TIFFfree(imageBuf);
      TIFFClose(tif);
      return IO_ERROR;
    }
  }

  _TIFFfree(imageBuf);
  TIFFClose(tif);

  return OK;
#else
  return INVALID_FILE_FORMAT;
#endif
}

ImageIO::errorType ImageIO::loadPNG(const char * filename)
{
#ifdef ENABLE_PNG
  FILE *file = fopen(filename, "rb");
  if (!file)
  {
    printf("Error in loadPNG: Cannot open file %s.\n", filename);
    return IO_ERROR;
  }

  // read the header of the image file
  const unsigned int pngHeaderBytes = 8;
  png_byte pngHeader[pngHeaderBytes];
  if (fread(pngHeader, 1, pngHeaderBytes, file) != pngHeaderBytes)
  {
    printf("Error in loadPNG: cannot read the header of the png file.\n");
    fclose(file);
    return (INVALID_FILE_FORMAT);
  };

  int pngFlag = !png_sig_cmp(pngHeader, 0, pngHeaderBytes);
  if (!pngFlag)
  {
    printf("Error in loadPNG: %s is not a png file.\n", filename);
    fclose(file);
    return (INVALID_FILE_FORMAT);
  }

  // initialize png_struct and png_info
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
  {
    printf("Error in loadPNG: Creating the internal structure failed.\n");
    fclose(file);
    return (IO_ERROR);
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_read_struct(&png_ptr,
      (png_infopp)NULL, (png_infopp)NULL);
    printf("Error in loadPNG: Creating the information structure failed.\n");
    fclose(file);
    return (IO_ERROR);
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    fclose(file);
    printf("Error in loadPNG: cannot setup the error handling.\n");
    return (IO_ERROR);
  }

  png_init_io(png_ptr, file);
  png_set_sig_bytes(png_ptr, pngHeaderBytes);

  png_read_info(png_ptr, info_ptr); 

  int color_type;
  int bit_depth;

  png_get_IHDR(png_ptr, info_ptr, (png_uint_32*)(&width), (png_uint_32*)(&height), &bit_depth, &color_type, NULL, NULL, NULL);

  // !!ATTETNION!! The following transformations are designed in the order that they should occur.
  // DO NOT change the sequence!!

  bool setBackgroundNeeded = false;

  switch (color_type)
  {
  case PNG_COLOR_TYPE_PALETTE:
    png_set_palette_to_rgb(png_ptr);  // change palette to RGB
    setBackgroundNeeded = true;
  	break;

  case PNG_COLOR_TYPE_GRAY:
    if (bit_depth < BITS_PER_CHANNEL_8)  // transforms grayscale images of less than 8 to 8 bits.
    {
      png_set_expand_gray_1_2_4_to_8(png_ptr);
      setBackgroundNeeded = true;
    }
    break; 
  }

  // adds a full alpha channel if there is transparency information in a tRNS chunk
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png_ptr);
  
  // The image has 16 bits per channel for every pixel. Strip the pixels down to 8 bits.
  if (bit_depth == BITS_PER_CHANNEL_16)
    png_set_strip_16(png_ptr);

  // PNG files pack pixels of bit depths 1,2, and 4 into bytes.
  // The following code expands to 1 pixel per byte without changing the value of the pixels
  if (bit_depth < BITS_PER_CHANNEL_8)
    png_set_packing(png_ptr);

  // convert a grayscale image to be represented as RGB
  if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
  {
    png_set_gray_to_rgb(png_ptr);
    setBackgroundNeeded = true;
  }

  // set background color if needed
  if (setBackgroundNeeded)
  {
    png_color_16 myBackground = {0, 0, 0, 0, 0};
    png_color_16 * imageBackground;

    if (png_get_bKGD(png_ptr, info_ptr, &imageBackground))
      png_set_background(png_ptr, imageBackground, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
    else
      png_set_background(png_ptr, &myBackground, PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
  }

 
//  PNG files store 16 bit pixels in net work byte order (big-endian)
//  The following code may be needed on PC as to change the storage to the little-endian.

//	if (bit_depth == 16)
//		png_set_swap(png_ptr);

  // After setting the transformations, update the png_info structure to reflect any transformations you have requested
  png_read_update_info(png_ptr, info_ptr);

  // get color type again. It may be changed if any transformation is applied ?? 
  color_type = png_get_color_type(png_ptr, info_ptr);
  switch (color_type)
  {
  case PNG_COLOR_TYPE_RGB:
    bytesPerPixel = IMAGE_IO_RGB;
  	break;
  case PNG_COLOR_TYPE_RGB_ALPHA:
    bytesPerPixel = IMAGE_IO_RGB_ALPHA;
    break;
  default:
    printf("Error in loadPNG: image transformation failed.\n");
    fclose(file);
    return (IO_ERROR);
    break;
  }

  // sanity check here
  if (png_get_rowbytes(png_ptr, info_ptr) != bytesPerPixel * width)
  {
    printf("Error in loadPNG: the number of bytes per row, which is %lu, does not match bytesPerPixel * width, which is %d.\n", png_get_rowbytes(png_ptr, info_ptr), bytesPerPixel * width);  
    fclose(file);
    return (IO_ERROR);
  }

  unsigned int bytesPerRow = bytesPerPixel * width;
  if(ownPixels)
    free(pixels);
  pixels = (unsigned char *) malloc (sizeof(unsigned char) * bytesPerRow * height);
  ownPixels = 1;

  png_bytep * row_pointers = (png_bytep*) malloc (sizeof(png_bytep) * height);
  for(unsigned int row = 0; row < height; row++)
    row_pointers[row] = (png_byte*)(&pixels[(height - row - 1) * bytesPerRow]);

  png_read_image(png_ptr, row_pointers);

  png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
  free(row_pointers);

  fclose(file);
  return OK;

#else
  return INVALID_FILE_FORMAT;
#endif
}

ImageIO::errorType ImageIO::savePNG(const char * filename)
{
#ifdef ENABLE_PNG
  FILE *file = fopen(filename, "wb");
  if (!file)
  {
    printf("Error in savePNG: Cannot open file %s.\n", filename);
    return IO_ERROR;
  }

  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
  {
    printf("Error in savePNG: Creating the internal structure failed.\n");
    fclose(file);
    return (IO_ERROR);
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  
  if (!info_ptr)
  {
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    printf("Error in savePNG: Creating the information structure failed.\n");
    fclose(file);
    return (IO_ERROR);
  }
  
  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(file);
    printf("Error in savePNG: cannot setup the error handling.\n");
    return (IO_ERROR);
  }

  // setup the output
  png_init_io(png_ptr, file);

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(file);
    printf("Error in savePNG: cannot write the png header.\n");
    return (IO_ERROR);
  }

  int bit_depth = BITS_PER_CHANNEL_8; // currently we only support 8 bits per channel
  int color_type;

  switch(bytesPerPixel)
  {
  case IMAGE_IO_RGB:
    color_type = PNG_COLOR_TYPE_RGB;
  	break;
  case IMAGE_IO_RGB_ALPHA:
    color_type = PNG_COLOR_TYPE_RGB_ALPHA;
    break;
  default:
    png_destroy_write_struct(&png_ptr, &info_ptr);
    printf("Error in savePNG: cannot handle bytesPerPixel that is not 3 or 4.\n");
    return OTHER_ERROR;
    break;
  }
    
  png_set_IHDR(png_ptr, info_ptr, (png_uint_32)width, (png_uint_32)height,
    bit_depth, color_type, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(file);
    printf("Error in savePNG: cannot write the png file.\n");
    return (IO_ERROR);
  }
  unsigned int bytesPerRow = bytesPerPixel * width;
  png_bytep * row_pointers = (png_bytep*) malloc (sizeof(png_bytep) * height);
  for(unsigned int row = 0; row < height; row++)
    row_pointers[row] = (png_byte*)(&pixels[(height - row - 1) * bytesPerRow]);

  png_write_image(png_ptr, row_pointers);

  free(row_pointers);

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(file);
    printf("Error in savePNG: unknown error occurred during end of file.\n");
    return (IO_ERROR);
  }

  png_write_end(png_ptr, NULL);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(file);
  
  return OK;

#else
  return INVALID_FILE_FORMAT;
#endif
}

ImageIO::errorType ImageIO::loadNONE(const char * filename)
{
  printf("Error: ImageIO load: unknown file format.\n");
  return INVALID_FILE_FORMAT;
}

ImageIO::errorType ImageIO::saveNONE(const char * filename)
{
  printf("Error: ImageIO save: unknown file format.\n");
  return INVALID_FILE_FORMAT;
}

ImageIO::errorType ImageIO::load(const char * filename, fileFormatType * fileFormat)
{
  // determine the file format
  *fileFormat = FORMAT_NONE;
  
  const char * extension = filename + strlen(filename) - 3;

  if ((strcmp(extension, "ppm") == 0) || (strcmp(extension, "PPM") == 0))
    *fileFormat = FORMAT_PPM;

  if ((strcmp(extension, "tga") == 0) || (strcmp(extension, "TGA") == 0))
    *fileFormat = FORMAT_TGA;

  #ifdef ENABLE_JPEG
  if ((strcmp(extension, "jpg") == 0) || (strcmp(extension, "JPEG") == 0))
    *fileFormat = FORMAT_JPEG;
  #endif

  #ifdef ENABLE_TIFF
  if ((strcmp(extension, "tif") == 0) || (strcmp(extension, "TIF") == 0))
    *fileFormat = FORMAT_TIFF;
  #endif

  #ifdef ENABLE_PNG
  if ((strcmp(extension, "png") == 0) || (strcmp(extension, "PNG") == 0))
    *fileFormat = FORMAT_PNG;
  #endif

  typedef errorType (ImageIO::*loadRoutineType) (const char*);
  loadRoutineType loadRoutine [] = { &ImageIO::loadPPM, &ImageIO::loadTGA, &ImageIO::loadJPEG, &ImageIO::loadTIFF, &ImageIO::loadPNG, &ImageIO::loadNONE };
  errorType errorCode = (this->*loadRoutine[*fileFormat])(filename);

  return errorCode;
}

ImageIO::errorType ImageIO::save(const char * filename, fileFormatType fileFormat)
{
  typedef errorType (ImageIO::*saveRoutineType) (const char*);
  saveRoutineType saveRoutine [] = { &ImageIO::savePPM, &ImageIO::saveTGA, &ImageIO::saveJPEG, &ImageIO::saveTIFF, &ImageIO::savePNG, &ImageIO::saveNONE };
  errorType errorCode = (this->*saveRoutine[fileFormat])(filename);

  return errorCode;
}

void ImageIO::flipVertically()
{
  unsigned char * rowBuffer = (unsigned char*) malloc (sizeof(unsigned char) * bytesPerPixel * width);

  for(unsigned int row=0; row < height / 2; row++)
  {
    int otherRow = height - 1 - row;

    // swap row and otherRow

    unsigned char * rowPixels = &pixels[bytesPerPixel * width * row];
    unsigned char * otherRowPixels = &pixels[bytesPerPixel * width * otherRow];

    // copy row to rowBuffer
    for(unsigned int i=0; i<bytesPerPixel * width; i++)
      rowBuffer[i] = rowPixels[i];

    // copy otherRow to row
    for(unsigned int i=0; i<bytesPerPixel * width; i++)
      rowPixels[i] = otherRowPixels[i];

    // copy rowBuffer to otherRow
    for(unsigned int i=0; i<bytesPerPixel * width; i++)
      otherRowPixels[i] = rowBuffer[i];
  }
  free(rowBuffer);
}

