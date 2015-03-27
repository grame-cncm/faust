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
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "dsp_aux.hh"
#include "libfaust.h"

using namespace std;

EXPORT string expandDSPFromFile(const string& filename, 
                                int argc, const char* argv[], 
                                string& sha_key,
                                string& error_msg)
{
    int argc1 = argc + 2;
    const char* argv1[32];
    
    argv1[0] = "faust";
    argv1[1] = filename.c_str();
    for (int i = 0; i < argc; i++) {
        argv1[i+2] = argv[i];
    }
        
	char error_msg_aux[512];
    char sha_key_aux[64];
    
	string res = expand_dsp(argc1, argv1, "", "", sha_key_aux, error_msg_aux);

	error_msg = error_msg_aux;
    sha_key = sha_key_aux;
    return res;
}

EXPORT string expandDSPFromString(const string& name_app, 
                                  const string& dsp_content, 
                                  int argc, const char* argv[], 
                                  string& sha_key,
                                  string& error_msg)
{
    int argc1 = argc + 1;
    const char* argv1[32];
    
    argv1[0] = "faust";
    for (int i = 0; i < argc; i++) {
        argv1[i+1] = argv[i];
    }
    
    char error_msg_aux[512];
    char sha_key_aux[64];
	const char* name = name_app.c_str();
	const char* content = dsp_content.c_str();
    string res = expand_dsp(argc1, argv1, name, content, sha_key_aux, error_msg_aux);

    error_msg = error_msg_aux;
    sha_key = sha_key_aux;
    return res;
}

EXPORT bool generateAuxFilesFromFile(const string& filename, int argc, const char* argv[], string& error_msg)
{
    int argc1 = argc + 2;
    const char* argv1[32];
    
    argv1[0] = "faust";
    argv1[1] = filename.c_str();
    for (int i = 0; i < argc; i++) {
        argv1[i+2] = argv[i];
    }
    
    char error_msg_aux[512];
    if (!compile_faust(argc1, argv1, "", "", error_msg_aux, false)) {
        return true;
    } else {
        error_msg = error_msg_aux;
        return false;
    }
}

EXPORT bool generateAuxFilesFromString(const string& name_app, const string& dsp_content, int argc, const char* argv[], string& error_msg)
{
    int argc1 = argc + 1;
    const char* argv1[32];
    
    argv1[0] = "faust";
    for (int i = 0; i < argc; i++) {
        argv1[i+1] = argv[i];
    }
 
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
    int argc1 = argc + 2;
    const char* argv1[32];
    
    argv1[0] = "faust";
    argv1[1] = filename;
    for (int i = 0; i < argc; i++) {
        argv1[i+2] = argv[i];
    }
    
    string str = expand_dsp(argc1, argv1, "", "", sha_key, error_msg);
    char* cstr = (char*)malloc(str.length() + 1);
    strcpy(cstr, str.c_str());
    return cstr;
}

EXPORT const char* expandCDSPFromString(const char* name_app, 
                                        const char* dsp_content, 
                                        int argc, const char* argv[], 
                                        char* sha_key,
                                        char* error_msg)
{
    int argc1 = argc + 1;
    const char* argv1[32];
    
    argv1[0] = "faust";
    for (int i = 0; i < argc; i++) {
        argv1[i+1] = argv[i];
    }
    
    string str = expand_dsp(argc1, argv1, name_app, dsp_content, sha_key, error_msg);
    char* cstr = (char*)malloc(str.length() + 1);
    strcpy(cstr, str.c_str());
    return cstr;
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
