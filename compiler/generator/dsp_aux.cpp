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
#include "export.hh"

#ifdef WIN32
#pragma warning (disable: 4996)
#endif

using namespace std;

// Look for 'key' in 'options' and modify the parameter 'position' if found
static bool parseKey(vector<string> options, const string& key, int& position)
{
    for (int i = 0; i < int(options.size()); i++) {
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

// External C++ libfaust API

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

// External C libfaust API

#ifdef __cplusplus
extern "C" {
#endif
    
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

#ifdef __cplusplus
}
#endif
