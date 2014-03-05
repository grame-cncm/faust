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
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>

#include "dsp_aux.hh"

using namespace std;

std::string expand_dsp(int argc, const char* argv[], const char* name, const char* input, char* error_msg);
int compile_faust(int argc, const char* argv[], const char* name, const char* input, char* error_msg, bool generate);

EXPORT std::string expandDSPFromFile(const std::string& filename, 
                                    int argc, const char* argv[], 
                                    std::string& error_msg)
{
    int argc1 = argc + 4;
    const char* argv1[32];
	  
    argv1[0] = "faust";
    argv1[1] = "-lang";
    argv1[2] = "llvm";
    argv1[3] = filename.c_str();
    for (int i = 0; i < argc; i++) {
        argv1[i+4] = argv[i];
    }
    
    char error_msg_aux[512];
    string res = expand_dsp(argc1, argv1, "", "", error_msg_aux);
    error_msg = error_msg_aux;
    return res;
}

EXPORT std::string expandDSPFromString(const std::string& name_app, 
                                    const std::string& dsp_content, 
                                    int argc, const char* argv[], 
                                    std::string& error_msg)
{
    int argc1 = argc + 3;
    const char* argv1[32];
	  
    argv1[0] = "faust";
    argv1[1] = "-lang";
    argv1[2] = "llvm";
    for (int i = 0; i < argc; i++) {
        argv1[i+3] = argv[i];
    }
    
    char error_msg_aux[512];
    string res = expand_dsp(argc1, argv1, name_app.c_str(), dsp_content.c_str(), error_msg_aux);
    error_msg = error_msg_aux;
    return res;
}

static bool CheckParameters(int argc, const char* argv[])
{
    for (int i = 0; i < argc; i++) {
        if ((strcmp(argv[i], "-tg") == 0
            || strcmp(argv[i], "-sg") == 0
            || strcmp(argv[i], "-ps") == 0
            || strcmp(argv[i], "-svg") == 0
            || strcmp(argv[i], "-mdoc") == 0
            || strcmp(argv[i], "-xml") == 0)) {
            return true;
        }
    }
    return false;
}

EXPORT bool generateAuxFilesFromFile(const std::string& filename, int argc, const char* argv[], std::string& error_msg)
{
    if (CheckParameters(argc, argv)) {
    
        int argc1 = argc + 4;
        const char* argv1[32];
          
        argv1[0] = "faust";
        argv1[1] = "-lang";
        argv1[2] = "llvm";
        argv1[3] = filename.c_str();
        for (int i = 0; i < argc; i++) {
            argv1[i+4] = argv[i];
        }
        
        char error_msg_aux[512];
        compile_faust(argc1, argv1, "", "", error_msg_aux, false);
        error_msg = error_msg_aux;
        return true;
    } else {
        return false;
    }
}

EXPORT bool generateAuxFilesFromString(const std::string& name_app, const std::string& dsp_content, int argc, const char* argv[], std::string& error_msg)
{
    if (CheckParameters(argc, argv)) {
    
        int argc1 = argc + 3;
        const char* argv1[32];
          
        argv1[0] = "faust";
        argv1[1] = "-lang";
        argv1[2] = "llvm";
        for (int i = 0; i < argc; i++) {
            argv1[i+3] = argv[i];
        }
     
        char error_msg_aux[512];
        compile_faust(argc1, argv1, name_app.c_str(), dsp_content.c_str(), error_msg_aux, false);
        error_msg = error_msg_aux;
        return true;
    } else {
        return false;
    }
}

EXPORT const char* expandCDSPFromFile(const char* filename, 
                                    int argc, const char* argv[], 
                                    char* error_msg)
{
    int argc1 = argc + 4;
    const char* argv1[32];
	  
    argv1[0] = "faust";
    argv1[1] = "-lang";
    argv1[2] = "llvm";
    argv1[3] = filename;
    for (int i = 0; i < argc; i++) {
        argv1[i+4] = argv[i];
    }
    
    string str = expand_dsp(argc1, argv1, "", "", error_msg);
    char* cstr = (char*)malloc(str.length() + 1);
    strcpy(cstr, str.c_str());
    return cstr;
}

EXPORT const char* expandCDSPFromString(const char* name_app, 
                                    const char* dsp_content, 
                                    int argc, const char* argv[], 
                                    char* error_msg)
{
    int argc1 = argc + 3;
    const char* argv1[32];
	  
    argv1[0] = "faust";
    argv1[1] = "-lang";
    argv1[2] = "llvm";
    for (int i = 0; i < argc; i++) {
        argv1[i+3] = argv[i];
    }
    
    string str = expand_dsp(argc1, argv1, name_app, dsp_content, error_msg);
    char* cstr = (char*)malloc(str.length() + 1);
    strcpy(cstr, str.c_str());
    return cstr;
}

EXPORT bool generateCAuxFilesFromFile(const char* filename, int argc, const char* argv[], char* error_msg)
{
    if (CheckParameters(argc, argv)) {
    
        int argc1 = argc + 4;
        const char* argv1[32];
          
        argv1[0] = "faust";
        argv1[1] = "-lang";
        argv1[2] = "llvm";
        argv1[3] = filename;
        for (int i = 0; i < argc; i++) {
            argv1[i+4] = argv[i];
        }
        
        compile_faust(argc1, argv1, "", "", error_msg, false);
        return true;
    } else {
        return false;
    }
}

EXPORT bool generateCAuxFilesFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg)
{
    if (CheckParameters(argc, argv)) {
    
        int argc1 = argc + 3;
        const char* argv1[32];
          
        argv1[0] = "faust";
        argv1[1] = "-lang";
        argv1[2] = "llvm";
        for (int i = 0; i < argc; i++) {
            argv1[i+3] = argv[i];
        }
     
        compile_faust(argc1, argv1, name_app, dsp_content, error_msg, false);
        return true;
    } else {
        return false;
    }
}
