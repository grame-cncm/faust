//------------------------------------------------------------------------------
// File : ppm.hpp
//------------------------------------------------------------------------------
//============================================================================
// ppm.hpp : Portable Pixel Map image format module
//============================================================================

void LoadPPM(const char *FileName, unsigned char* &Color, int &Width, int &Height);
void WritePPM(const char *FileName, unsigned char* Color, int Width, int Height);
void VFlip(unsigned char * Pix, int width, int height, int chan=3);
