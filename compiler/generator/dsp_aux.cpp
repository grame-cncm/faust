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

#ifdef _WIN32
#include "compatibility.hh"
#else
#include <libgen.h>
#endif

#include "dsp_aux.hh"
#include "libfaust.h"
#include "TMutex.h"

extern TLockAble* gDSPFactoriesLock;

using namespace std;

static bool start_with(const string& str, const string& key)
{
    for (size_t i = 0; i < key.size(); i++) {
        if (str[i] != key[i]) return false;
    }
    return true;
}

EXPORT string expandDSPFromFile(const string& filename, 
                                int argc, const char* argv[], 
                                string& sha_key,
                                string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    return expandDSPFromString(base.substr(0, pos), path_to_content(filename), argc, argv, sha_key, error_msg);
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
    TLock lock(gDSPFactoriesLock);
    
    // Already expanded version ?
    if (start_with(dsp_content, COMPILATION_OPTIONS)) {
        if (extract_compilation_options(dsp_content) == reorganize_compilation_options(argc, argv)) {
            // Same compilation options as the ones kept in the expanded version
            sha_key = generateSHA1(dsp_content);
            return dsp_content;
        } else {
            // Otherwise add a new compilation options line, consider it as the new expanded code : generate SHA key and return it
            string new_dsp_content = COMPILATION_OPTIONS + reorganize_compilation_options(argc, argv) + ";\n" + dsp_content;
            sha_key = generateSHA1(new_dsp_content);
            return new_dsp_content;
        }
    } else {
        int argc1 = argc + 1;
        const char* argv1[32];
        
        argv1[0] = "faust";
        for (int i = 0; i < argc; i++) {
            argv1[i+1] = argv[i];
        }
        
        argv1[argc1] = 0;  // NULL terminated argv
        
        char error_msg_aux[512];
        char sha_key_aux[128];
        const char* name = name_app.c_str();
        const char* content = dsp_content.c_str();
        // 'expand_dsp' adds the normalized compilation options in the DSP code before computing the SHA key
        string res = expand_dsp(argc1, argv1, name, content, sha_key_aux, error_msg_aux);
        error_msg = error_msg_aux;
        sha_key = sha_key_aux;
        return res;
    }
}

EXPORT bool generateAuxFilesFromFile(const string& filename, int argc, const char* argv[], string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    return generateAuxFilesFromString(base.substr(0, pos), path_to_content(filename), argc, argv, error_msg);
}

EXPORT bool generateAuxFilesFromString(const string& name_app, const string& dsp_content, int argc, const char* argv[], string& error_msg)
{
    TLock lock(gDSPFactoriesLock);
    
    int argc1 = 1;
    const char* argv1[64];
    argv1[0] = "faust";
    
    // Filter arguments
    for (int i = 0; i < argc; i++) {
        if (!(strcmp(argv[i],"-vec") == 0 ||
            strcmp(argv[i],"-sch") == 0)) {
            argv1[argc1++] = argv[i];
        }
    }
    
    argv1[argc1] = 0;  // NULL terminated argv
  
    char error_msg_aux[512];
    if (!compile_faust(argc1, argv1, name_app.c_str(), dsp_content.c_str(), error_msg_aux, false)) {
        return true;
    } else {
        error_msg = error_msg_aux;
        return false;
    }
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
    strncpy(error_msg, error_msg_aux.c_str(), 256);
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
    strncpy(error_msg, error_msg_aux.c_str(), 256);
    return strdup(res.c_str());
}

EXPORT bool generateCAuxFilesFromFile(const char* filename, int argc, const char* argv[], char* error_msg)
{
    string error_msg_aux;
    bool res = generateAuxFilesFromFile(filename, argc, argv, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 256);
    return res;
}

EXPORT bool generateCAuxFilesFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg)
{
    string error_msg_aux;
    bool res = generateAuxFilesFromString(name_app, dsp_content, argc, argv, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 256);
    return res;
}
