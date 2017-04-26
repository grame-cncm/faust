/**
Converts a PPM source image into a byte array, for use in 
glui_bitmap_img_data.cpp.

*/
#include "ppm.h"

#include <cstdio>
#include <cstring>

int main( int argc, char *argv[] )
{
  int        i;
  unsigned char* img = 0;
  int        w, h;
  FILE      *output;
  char       basename[200];

  if ( argc != 2 && argc != 3 ) {
    fprintf( stderr, "USAGE: %s input.ppm [output.cpp]\n", argv[0] );
    return 1;
  }

  LoadPPM( argv[1], img, w, h );

  if ( img ) {
    strcpy( basename, argv[1] );
    basename[ strlen(basename)-4 ] = '\0';

    if (argc == 3) 
      output = fopen( argv[2], "w" );
    else
      output = stdout;
    if ( !output ) {
      fprintf( stderr, "ERROR: File '%s' could not be opened for writing\n",
	       argv[2] );
      return 1;
    }

    VFlip(img,w,h); /* Opengl bitmaps are specified bottom-to-top */

    fprintf( output, "\n\n");
    fprintf( output, "int %s[] = {", basename );
    fprintf( output, "    %d, %d,   /* width, height */\n", w, h);

    fprintf( output, "    " );  
    for( i=0; i<w * h; i++ ) {
      fprintf( output, "%3d,%3d,%3d,  ", 
	       img[i*3+0],
	       img[i*3+1],
	       img[i*3+2] );
      if ( (i%5) == 4 ) {
	fprintf( output, "\n    " );
      }
    }

    fprintf( output, "\n};\n" );
    fclose( output );
  }
  else {
    fprintf( stderr, "ERROR: Image '%s' invalid\n", argv[1] );
    return 1;
  }

  return 0;  
}


