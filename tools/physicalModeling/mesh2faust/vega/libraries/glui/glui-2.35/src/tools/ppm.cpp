//------------------------------------------------------------------------------
// File : ppm.cpp
//------------------------------------------------------------------------------

//============================================================================
// ppm.cpp : Portable Pixel Map image format module
//============================================================================

#include <cstdio>
#include <cassert>
#include <cstring>

#define PPM_VERBOSE 0


void VFlip(unsigned char * Pix, int width, int height, int chan)
{
	int lsize = width * chan;
	unsigned char *tbuf = new unsigned char[lsize];
	assert(tbuf);

  if (height == 0) 
    return;

	for(int y=0; y<height/2; y++)
	{
		memcpy(tbuf, &Pix[y*lsize], lsize);
		memcpy(&Pix[y*lsize], &Pix[(height-y-1)*lsize], lsize);
		memcpy(&Pix[(height-y-1)*lsize], tbuf, lsize);
	}
	delete [] tbuf;
}


//----------------------------------------------------------------------------
// READS AN IMAGE IN FROM A PPM FILE. RETURNS THE COLOR RGB ARRAY AND DIMENSIONS
// PERFORMS AUTO-ALLOCATION OF Color ARRAY IF SET TO NULL BEFORE CALLING; OTHERWISE
// ASSUMES THAT COLOR HAS BEEN PRE-ALLOCED.
//----------------------------------------------------------------------------
void LoadPPM(const char *FileName, unsigned char* &Color, int &Width, int &Height)
{
  FILE* fp = fopen(FileName, "rb");
  if (fp==NULL) 
    { printf("PPM ERROR (ReadPPM) : unable to open %s!\n",FileName);
      Color=NULL; Width=0; Height=0; return; }
  int c,s;
  do{ do { s=fgetc(fp); } while (s!='\n'); } while ((c=fgetc(fp))=='#');
  ungetc(c,fp);
  fscanf(fp, "%d %d\n255\n", &Width, &Height);
#if PPM_VERBOSE
  printf("Reading %dx%d Texture [%s]. . .\n", Width, Height, FileName);
#endif
  int NumComponents = Width*Height*3;
  if (Color==NULL) Color = new unsigned char[NumComponents];
  fread(Color,NumComponents,1,fp);
  fclose(fp);
}

//----------------------------------------------------------------------------
// Writes an unsigned byte RGB color array out to a PPM file.
//----------------------------------------------------------------------------
void WritePPM(const char *FileName, unsigned char* Color, int Width, int Height)
{
  FILE* fp = fopen(FileName, "wb");
  if (fp==NULL) { printf("PPM ERROR (WritePPM) : unable to open %s!\n",FileName); return; }
  fprintf(fp, "P6\n%d %d\n255\n", Width, Height);
  fwrite(Color,1,Width*Height*3,fp);
  fclose(fp);
}
