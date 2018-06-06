#ifndef FAST_POW2
#define FAST_POW2

// Copied from fastexp.h
// See that file for copyright info.

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <cassert>

//#ifdef __cplusplus
//#define cast_uint32_t static_cast<uint32_t>
//#else
#define cast_uint32_t (uint32_t)
//#endif

//#define DEBUG_FASTPOW2

#ifdef DEBUG_FASTPOW2
static int counter = 0;
#endif

static inline float
fastpow2 (float p)
{
  //static_assert(sizeof(float)==4,"float not 32 bits!");
  if (p == 0) {
    return 1.0;
  }
  float offset = (p < 0) ? 1.0f : 0.0f;
  float clipp = (p < -126) ? -126.0f : p;
  int w = clipp;
  float z = clipp - w + offset;
  union { uint32_t i; float f; } v = { cast_uint32_t ( (1 << 23) * (clipp + 121.2740575f + 27.7280233f / (4.84252568f - z) - 1.49012907f * z) ) };

#ifdef DEBUG_FASTPOW2
    if (counter++ >= 1024) {
        printf("fastpow2: 2 ^ %f = %f ~ %f\n", p, powf(2.0,p), v.f);
        counter = 0;
    };
#endif

 return v.f;
}

// NOT SUFFICIENTLY ACCURATE - USE fastpow2 above.
// This one causes very noticeable overdamping of high-frequency notes
static inline float
fasterpow2 (float p)
{
  //static_assert(sizeof(float)==4,"float not 32 bits!");
  fprintf(stderr,"*** fasterpow2 is NOT SUFFICIENTLY ACCURATE - use fastpow2 (below) instead\n");
  exit(1);
  float clipp = (p < -126) ? -126.0f : p;
  union { uint32_t i; float f; } v = { cast_uint32_t ( (1 << 23) * (clipp + 126.94269504f) ) };

#ifdef DEBUG_FASTPOW2
    if (counter++ >= 1024) {
        printf("fasterpow2: 2 ^ %f = %f ~ %f\n", p, powf(2.0,p), v.f);
        counter = 0;
    };
#endif

  return v.f;
}

#endif
