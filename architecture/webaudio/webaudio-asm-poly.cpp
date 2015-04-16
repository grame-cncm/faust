/*
 faust2webaudio
 
 Primarily written by Myles Borins
 During the Spring 2013 offering of Music 420b with Julius Smith
 A bit during the Summer of 2013 with the help of Joshua Kit Clayton
 And finally a sprint during the late fall of 2013 to get everything working
 A Special thanks to Yann Orlarey and Stéphane Letz
 
 faust2webaudio is distributed under the terms the MIT or GPL2 Licenses.
 Choose the license that best suits your project. The text of the MIT and GPL
 licenses are at the root directory.
 
 Additional code : GRAME 2014

*/

// Adapted From https://gist.github.com/camupod/5640386
// compile using "C" linkage to avoid name obfuscation

#include <emscripten.h>
#include <vector>
#include <map>
#include <string>
#include <math.h>

#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/audio/dsp.h"

// "mydsp" part will be replaced by the actual '-cn' parameter

// Usage : faust -i -uim -a webaudio/webaudio-asm-poly.cpp -cn karplus karplus.dsp -o karplus.cpp

inline int max(unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int max(int a, int b)	{ return (a>b) ? a : b; }

inline long max(long a, long b) { return (a>b) ? a : b; }
inline long max(int a, long b) 	{ return (a>b) ? a : b; }
inline long max(long a, int b) 	{ return (a>b) ? a : b; }

inline float max(float a, float b) { return (a>b) ? a : b; }
inline float max(int a, float b) 	{ return (a>b) ? a : b; }
inline float max(float a, int b) 	{ return (a>b) ? a : b; }
inline float max(long a, float b) 	{ return (a>b) ? a : b; }
inline float max(float a, long b) 	{ return (a>b) ? a : b; }

inline double max(double a, double b) 	{ return (a>b) ? a : b; }
inline double max(int a, double b)      { return (a>b) ? a : b; }
inline double max(double a, int b)      { return (a>b) ? a : b; }
inline double max(long a, double b) 	{ return (a>b) ? a : b; }
inline double max(double a, long b) 	{ return (a>b) ? a : b; }
inline double max(float a, double b) 	{ return (a>b) ? a : b; }
inline double max(double a, float b) 	{ return (a>b) ? a : b; }

inline int	min(int a, int b)	{ return (a<b) ? a : b; }

inline long min(long a, long b) { return (a<b) ? a : b; }
inline long min(int a, long b) 	{ return (a<b) ? a : b; }
inline long min(long a, int b) 	{ return (a<b) ? a : b; }

inline float min(float a, float b) { return (a<b) ? a : b; }
inline float min(int a, float b) 	{ return (a<b) ? a : b; }
inline float min(float a, int b) 	{ return (a<b) ? a : b; }
inline float min(long a, float b) 	{ return (a<b) ? a : b; }
inline float min(float a, long b) 	{ return (a<b) ? a : b; }

inline double min(double a, double b) 	{ return (a<b) ? a : b; }
inline double min(int a, double b)      { return (a<b) ? a : b; }
inline double min(double a, int b)      { return (a<b) ? a : b; }
inline double min(long a, double b) 	{ return (a<b) ? a : b; }
inline double min(double a, long b) 	{ return (a<b) ? a : b; }
inline double min(float a, double b) 	{ return (a<b) ? a : b; }
inline double min(double a, float b) 	{ return (a<b) ? a : b; }

<<includeIntrinsic>>

<<includeclass>>

#include "faust/dsp/poly-dsp.h"

