/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "compatibility.hh"
#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "Text.hh"
#include "libfaust.h"
#include "libfaust-c.h"
#include "export.hh"

#ifdef WIN32
#pragma warning (disable: 4996)
#endif

using namespace std;

// Look for 'key' in 'options' and modify the parameter 'position' if found
static bool parseKey(vector<string> options, const string& key, int& position)
{
    for (size_t i = 0; i < options.size(); i++) {
        if (key == options[i]) {
            position = i;
            return true;
        }
    }
    
    return false;
}

/*
 *  Add 'key' if existing in 'options', otherwise add 'defaultKey' (if different from "")
 * return true if 'key' was added
*/
static bool addKeyIfExisting(vector<string>& options, vector<string>& newoptions, const string& key, const string& defaultKey, int& position)
{
    if (parseKey(options, key, position)) {
        newoptions.push_back(options[position]);
        options.erase(options.begin()+position);
        position--;
        return true;
    } else if (defaultKey != "") {
        newoptions.push_back(defaultKey);
    }
    
    return false;
}

// Add 'key' & it's associated value if existing in 'options', otherwise add 'defaultValue' (if different from "")
static void addKeyValueIfExisting(vector<string>& options, vector<string>& newoptions, const string& key, const string& defaultValue)
{
    int position = 0;
    
    if (addKeyIfExisting(options, newoptions, key, "", position)) {
        if (position+1 < int(options.size()) && options[position+1][0] != '-') {
            newoptions.push_back(options[position+1]);
            options.erase(options.begin()+position+1);
            position--;
        } else {
            newoptions.push_back(defaultValue);
        }
    }
}

/* 
 * Reorganizes the compilation options
 * Following the tree of compilation (Faust_Compilation_Options.pdf in distribution)
 */
static vector<string> reorganizeCompilationOptionsAux(vector<string>& options)
{
    bool vectorize = false;
    int position = 0;
    
    vector<string> newoptions;
    
    //------STEP 1 - Single or Double ?
    addKeyIfExisting(options, newoptions, "-double", "-single", position);
    
    //------STEP 2 - Options Leading to -vec inclusion
    if (addKeyIfExisting(options, newoptions, "-sch", "", position)) {
        vectorize = true;
    }
    
    if (addKeyIfExisting(options, newoptions, "-omp", "", position)){
        vectorize = true;
        addKeyIfExisting(options, newoptions, "-pl", "", position);
    }
    
    if (vectorize) {
        newoptions.push_back("-vec");
    }
    
    //------STEP3 - Add options depending on -vec/-scal option
    if (vectorize || addKeyIfExisting(options, newoptions, "-vec", "", position)) {
        addKeyIfExisting(options, newoptions, "-dfs", "", position);
        addKeyIfExisting(options, newoptions, "-vls", "", position);
        addKeyIfExisting(options, newoptions, "-fun", "", position);
        addKeyIfExisting(options, newoptions, "-g", "", position);
        addKeyValueIfExisting(options, newoptions, "-vs", "32");
        addKeyValueIfExisting(options, newoptions, "-lv", "0");
    } else {
        addKeyIfExisting(options, newoptions, "-scal", "-scal", position);
        addKeyIfExisting(options, newoptions, "-inpl", "", position);
    }
    
    addKeyValueIfExisting(options, newoptions, "-mcd", "16");
    addKeyValueIfExisting(options, newoptions, "-cn", "");
    addKeyValueIfExisting(options, newoptions, "-ftz", "0");
    
    //------STEP4 - Add other types of Faust options
    /*
     addKeyIfExisting(options, newoptions, "-tg", "", position);
     addKeyIfExisting(options, newoptions, "-sg", "", position);
     addKeyIfExisting(options, newoptions, "-ps", "", position);
     addKeyIfExisting(options, newoptions, "-svg", "", position);
     
     if (addKeyIfExisting(options, newoptions, "-mdoc", "", position)) {
     addKeyValueIfExisting(options, newoptions, "-mdlang", "");
     addKeyValueIfExisting(options, newoptions, "-stripdoc", "");
     }
     
     addKeyIfExisting(options, newoptions, "-sd", "", position);
     addKeyValueIfExisting(options, newoptions, "-f", "25");
     addKeyValueIfExisting(options, newoptions, "-mns", "40");
     addKeyIfExisting(options, newoptions, "-sn", "", position);
     addKeyIfExisting(options, newoptions, "-xml", "", position);
     addKeyIfExisting(options, newoptions, "-blur", "", position);
     addKeyIfExisting(options, newoptions, "-lb", "", position);
     addKeyIfExisting(options, newoptions, "-mb", "", position);
     addKeyIfExisting(options, newoptions, "-rb", "", position);
     addKeyIfExisting(options, newoptions, "-lt", "", position);
     addKeyValueIfExisting(options, newoptions, "-a", "");
     addKeyIfExisting(options, newoptions, "-i", "", position);
     addKeyValueIfExisting(options, newoptions, "-cn", "");
     addKeyValueIfExisting(options, newoptions, "-t", "120");
     addKeyIfExisting(options, newoptions, "-time", "", position);
     addKeyValueIfExisting(options, newoptions, "-o", "");
     addKeyValueIfExisting(options, newoptions, "-lang", "cpp");
     addKeyIfExisting(options, newoptions, "-flist", "", position);
     addKeyValueIfExisting(options, newoptions, "-l", "");
     addKeyValueIfExisting(options, newoptions, "-O", "");
     
     //-------Add Other Options that are possibily passed to the compiler (-I, -blabla, ...)
     while (options.size() != 0) {
        if (options[0] != "faust") newoptions.push_back(options[0]); // "faust" first argument
        options.erase(options.begin());
     }
     */
    
    return newoptions;
}

static std::string extractCompilationOptions(const std::string& dsp_content)
{
    size_t pos1 = dsp_content.find(COMPILATION_OPTIONS_KEY);
    
    if (pos1 != string::npos) {
        size_t pos2 = dsp_content.find_first_of('"', pos1 + 1);
        size_t pos3 = dsp_content.find_first_of('"', pos2 + 1);
        if (pos2 != string::npos && pos3 != string::npos) {
            return dsp_content.substr(pos2, (pos3 - pos2) + 1);
        }
    }
    
    return "";
}

string reorganizeCompilationOptions(int argc, const char* argv[])
{
    vector<string> res1;
    for (int i = 0; i < argc; i++) {
        res1.push_back(argv[i]);
    }
    
    vector<string> res2 = reorganizeCompilationOptionsAux(res1);
    
    string sep, res3;
    for (size_t i = 0; i < res2.size(); i++) {
        res3 = res3 + sep + res2[i];
        sep = " ";
    }
    
    return "\"" + res3 + "\"";
}

void* dsp_factory_imp::allocate(size_t size)
{
    if (fManager) {
        return fManager->allocate(size);
    } else {
        faustassert(false);
        return nullptr;
    }
}

void dsp_factory_imp::destroy(void* ptr)
{
    if (fManager) {
        fManager->destroy(ptr);
    } else {
        faustassert(false);
    }
}

// External libfaust API

EXPORT string expandDSPFromFile(const string& filename,
                                int argc, const char* argv[],
                                string& sha_key,
                                string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    return expandDSPFromString(base.substr(0, pos), pathToContent(filename), argc, argv, sha_key, error_msg);
}

/*
Same DSP code and same normalized compilation options will generate the same SHA key.
*/
EXPORT string expandDSPFromString(const string& name_app, 
                                  const string& dsp_content, 
                                  int argc, const char* argv[], 
                                  string& sha_key,
                                  string& error_msg)
{
    if (dsp_content == "") {
        error_msg = "Unable to read file";
        return "";
    // Already expanded version ?
    } else if (startWith(dsp_content, COMPILATION_OPTIONS)) {
        if (extractCompilationOptions(dsp_content) == reorganizeCompilationOptions(argc, argv)) {
            // Same compilation options as the ones kept in the expanded version
            sha_key = generateSHA1(dsp_content);
            return dsp_content;
        } else {
            // Otherwise add a new compilation options line, consider it as the new expanded code : generate SHA key and return it
            string new_dsp_content = COMPILATION_OPTIONS + reorganizeCompilationOptions(argc, argv) + ";\n" + dsp_content;
            sha_key = generateSHA1(new_dsp_content);
            return new_dsp_content;
        }
    } else {
        
        int argc1 = 0;
        const char* argv1[64];
        argv1[argc1++] = "faust";
        for (int i = 0; i < argc; i++) {
            argv1[argc1++] = argv[i];
        }
        argv1[argc1] = 0;  // NULL terminated argv
        
        // 'expandDsp' adds the normalized compilation options in the DSP code before computing the SHA key
        return expandDSP(argc1, argv1, name_app.c_str(), dsp_content.c_str(), sha_key, error_msg);
    }
}

EXPORT bool generateAuxFilesFromFile(const string& filename, int argc, const char* argv[], string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    return generateAuxFilesFromString(base.substr(0, pos), pathToContent(filename), argc, argv, error_msg);
}

EXPORT bool generateAuxFilesFromString(const string& name_app, const string& dsp_content, int argc, const char* argv[], string& error_msg)
{
    if (dsp_content == "") {
        error_msg = "Unable to read file";
        return false;
    } else {
    
        int argc1 = 0;
        const char* argv1[64];
        argv1[argc1++] = "faust";
        // Filter arguments
        for (int i = 0; i < argc; i++) {
            if (!(strcmp(argv[i], "-vec") == 0 || strcmp(argv[i], "-sch") == 0)) {
                argv1[argc1++] = argv[i];
            }
        }
        argv1[argc1] = 0;  // NULL terminated argv
        
        dsp_factory_base* factory = compileFaustFactory(argc1, argv1, name_app.c_str(), dsp_content.c_str(), error_msg, false);
        // Factory is no more needed
        delete factory;
        return (factory != NULL);
    }
}

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

static void sha1_transform(SHA1_CTX* ctx, uchar data[])
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

static void sha1_init(SHA1_CTX* ctx)
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

static void sha1_update(SHA1_CTX* ctx, uchar data[], uint len)
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

EXPORT string generateSHA1(const string& dsp_content)
{
    SHA1_CTX ctx;
    unsigned char obuf[20] = {0};
    
    // Hash one
    sha1_init(&ctx);
    sha1_update(&ctx, (unsigned char*)dsp_content.c_str(), dsp_content.size());
    sha1_final(&ctx, obuf);
    
    // convert SHA1 key into hexadecimal string
    string sha1key;
    for (int i = 0; i < 20; i++) {
        const char* H = "0123456789ABCDEF";
        char c1 = H[(obuf[i] >> 4)];
        char c2 = H[(obuf[i] & 15)];
        sha1key += c1;
        sha1key += c2;
    }
    
    return sha1key;
}

EXPORT const char* expandCDSPFromFile(const char* filename, 
                                    int argc, const char* argv[], 
                                    char* sha_key,
                                    char* error_msg)
{
    string sha_key_aux;
    string error_msg_aux;
    string res = expandDSPFromFile(filename, argc, argv, sha_key_aux, error_msg_aux);
    strncpy(sha_key, sha_key_aux.c_str(), 64);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return strdup(res.c_str());
}

EXPORT const char* expandCDSPFromString(const char* name_app, 
                                        const char* dsp_content, 
                                        int argc, const char* argv[], 
                                        char* sha_key,
                                        char* error_msg)
{
    string sha_key_aux;
    string error_msg_aux;
    string res = expandDSPFromString(name_app, dsp_content, argc, argv, sha_key_aux, error_msg_aux);
    strncpy(sha_key, sha_key_aux.c_str(), 64);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return strdup(res.c_str());
}

EXPORT bool generateCAuxFilesFromFile(const char* filename, int argc, const char* argv[], char* error_msg)
{
    string error_msg_aux;
    bool res = generateAuxFilesFromFile(filename, argc, argv, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return res;
}

EXPORT bool generateCAuxFilesFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg)
{
    string error_msg_aux;
    bool res = generateAuxFilesFromString(name_app, dsp_content, argc, argv, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return res;
}

EXPORT void generateCSHA1(const char* data, char* sha_key)
{
    strncpy(sha_key, generateSHA1(data).c_str(), 64);
}

EXPORT void freeCMemory(void* ptr)
{
    free(ptr);
}

