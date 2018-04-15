/************************************************************************
 ************************************************************************
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 ************************************************************************
 ************************************************************************/

#ifndef LIBFAUST_C_H
#define LIBFAUST_C_H

#include <string.h>

#ifdef _WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
// Code by: B-Con (http://b-con.us)
// Released under the GNU GPL
// MD5 Hash Digest implementation (little endian byte order)

// Signed variables are for wimps
#define uchar unsigned char
#define uint unsigned int

// DBL_INT_ADD treats two unsigned ints a and b as one 64-bit integer and adds c to it
#define ROTLEFT(a,b) ((a << b) | (a >> (32-b)))
#define DBL_INT_ADD(a,b,c) if (a > 0xffffffff - c) ++b; a += c;

typedef struct {
    uchar data[64];
    uint datalen;
    uint bitlen[2];
    uint state[5];
    uint k[4];
} SHA1_CTX;

inline void sha1_transform(SHA1_CTX* ctx, uchar data[])
{
    uint a,b,c,d,e,i,j,t,m[80];
    
    for (i = 0,j = 0; i < 16; ++i, j += 4) {
        m[i] = (data[j] << 24) + (data[j+1] << 16) + (data[j+2] << 8) + (data[j+3]);
    }
    for ( ; i < 80; ++i) {
        m[i] = (m[i-3] ^ m[i-8] ^ m[i-14] ^ m[i-16]);
        m[i] = (m[i] << 1) | (m[i] >> 31);
    }
    
    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    
    for (i=0; i < 20; ++i) {
        t = ROTLEFT(a,5) + ((b & c) ^ (~b & d)) + e + ctx->k[0] + m[i];
        e = d;
        d = c;
        c = ROTLEFT(b,30);
        b = a;
        a = t;
    }
    for ( ; i < 40; ++i) {
        t = ROTLEFT(a,5) + (b ^ c ^ d) + e + ctx->k[1] + m[i];
        e = d;
        d = c;
        c = ROTLEFT(b,30);
        b = a;
        a = t;
    }
    for ( ; i < 60; ++i) {
        t = ROTLEFT(a,5) + ((b & c) ^ (b & d) ^ (c & d))  + e + ctx->k[2] + m[i];
        e = d;
        d = c;
        c = ROTLEFT(b,30);
        b = a;
        a = t;
    }
    for ( ; i < 80; ++i) {
        t = ROTLEFT(a,5) + (b ^ c ^ d) + e + ctx->k[3] + m[i];
        e = d;
        d = c;
        c = ROTLEFT(b,30);
        b = a;
        a = t;
    }
    
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
}

inline void sha1_init(SHA1_CTX* ctx)
{
    ctx->datalen = 0;
    ctx->bitlen[0] = 0;
    ctx->bitlen[1] = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xc3d2e1f0;
    ctx->k[0] = 0x5a827999;
    ctx->k[1] = 0x6ed9eba1;
    ctx->k[2] = 0x8f1bbcdc;
    ctx->k[3] = 0xca62c1d6;
}

inline void sha1_update(SHA1_CTX* ctx, uchar data[], uint len)
{
    uint i;
    
    for (i = 0; i < len; ++i) {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == 64) {
            sha1_transform(ctx, ctx->data);
            DBL_INT_ADD(ctx->bitlen[0], ctx->bitlen[1], 512);
            ctx->datalen = 0;
        }
    }
}

static void sha1_final(SHA1_CTX *ctx, uchar hash[])
{
    uint i;
    
    i = ctx->datalen;
    
    // Pad whatever data is left in the buffer.
    if (ctx->datalen < 56) {
        ctx->data[i++] = 0x80;
        while (i < 56) {
            ctx->data[i++] = 0x00;
        }
    } else {
        ctx->data[i++] = 0x80;
        while (i < 64) {
            ctx->data[i++] = 0x00;
        }
        sha1_transform(ctx, ctx->data);
        memset(ctx->data,0,56);
    }
    
    // Append to the padding the total message's length in bits and transform.
    DBL_INT_ADD(ctx->bitlen[0], ctx->bitlen[1], 8 * ctx->datalen);
    ctx->data[63] = ctx->bitlen[0];
    ctx->data[62] = ctx->bitlen[0] >> 8;
    ctx->data[61] = ctx->bitlen[0] >> 16;
    ctx->data[60] = ctx->bitlen[0] >> 24;
    ctx->data[59] = ctx->bitlen[1];
    ctx->data[58] = ctx->bitlen[1] >> 8;
    ctx->data[57] = ctx->bitlen[1] >> 16;
    ctx->data[56] = ctx->bitlen[1] >> 24;
    sha1_transform(ctx,ctx->data);
    
    // Since this implementation uses little endian byte ordering and MD uses big endian,
    // reverse all the bytes when copying the final state to the output hash.
    for (i = 0; i < 4; ++i) {
        hash[i]    = (ctx->state[0] >> (24-i*8)) & 0x000000ff;
        hash[i+4]  = (ctx->state[1] >> (24-i*8)) & 0x000000ff;
        hash[i+8]  = (ctx->state[2] >> (24-i*8)) & 0x000000ff;
        hash[i+12] = (ctx->state[3] >> (24-i*8)) & 0x000000ff;
        hash[i+16] = (ctx->state[4] >> (24-i*8)) & 0x000000ff;
    }
}
    
/**
 * Compute a SHA1 key from a string
 *
 * @param data - the string to be converted in SHA1 key
 * @param key - a 64 characters buffer to be filled with the computed key
 *
 */
LIBEXPORT inline void generateCSHA1(const char* data, char* sha_key)
{
    SHA1_CTX ctx;
    unsigned char obuf[20] = {0};
    
    // Hash one
    sha1_init(&ctx);
    sha1_update(&ctx, (unsigned char*)data, strlen(data));
    sha1_final(&ctx, obuf);
    
    // convert SHA1 key into hexadecimal string
    for (int i = 0; i < 20; i++) {
        const char* H = "0123456789ABCDEF";
        char c1 = H[(obuf[i] >> 4)];
        char c2 = H[(obuf[i] & 15)];
        sha_key += c1;
        sha_key += c2;
    }
}

/**
 * Expand a DSP source code into a self-contained DSP where all library import have been inlined starting from a filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param sha_key - a SHA key to be filled by for the resulting DSP
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 *
 * @return the expanded DSP or a NULL string in case of failure (to be deleted by the caller using freeCMemory)
 */
LIBEXPORT const char* expandCDSPFromFile(const char* filename, 
                                    int argc, const char* argv[],
                                    char* sha_key,
                                    char* error_msg);

/**
 * Expand a DSP source code into a self-contained DSP where all library import have been inlined starting from a string.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param sha_key - a SHA key to be filled by for the resulting DSP
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 *
 * @return the expanded DSP or a NULL string in case of failure (to be deleted by the caller using freeCMemory)
 */
LIBEXPORT const char* expandCDSPFromString(const char* name_app,
                                        const char* dsp_content,
                                        int argc, const char* argv[], 
                                        char* sha_key,
                                        char* error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 *
 * @return the expanded DSP or a empty string in case of failure
 */
LIBEXPORT bool generateCAuxFilesFromFile(const char* filename, int argc, const char* argv[], char* error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a string.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 *
 * @return the expanded DSP or a empty string in case of failure
 */
LIBEXPORT bool generateCAuxFilesFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg);
    
/**
 * The free function to be used on memory returned by getCDSPMachineTarget, getCName, getCSHAKey,
 * getCDSPCode, getCLibraryList, getAllCDSPFactories, writeCDSPFactoryToBitcode,
 * writeCDSPFactoryToIR, writeCDSPFactoryToMachine,expandCDSPFromString and expandCDSPFromFile.
 *
 * This is MANDATORY on Windows when otherwise all nasty runtime version related crashes can occur.
 *
 * @param ptr - the pointer to be deleted.
 */    
LIBEXPORT void freeCMemory(void* ptr);
    
#ifdef __cplusplus
}
#endif

#endif
