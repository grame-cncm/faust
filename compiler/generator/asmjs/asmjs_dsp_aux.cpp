/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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
#include <iostream>
#include <fstream>
#include <sstream>
#include <libgen.h>

#include "compatibility.hh"
#include "asmjs_dsp_aux.hh"
#include "libfaust.h"
#include "Text.hh"


typedef class faust_smartptr<asmjs_dsp_factory> SDsp_factory;

dsp_factory_table<SDsp_factory> gAsmjsFactoryTable;

#ifdef LOADER
string pathToContent(const string& path)
{
    ifstream file(path.c_str(), ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}
#endif

// C++ API

EXPORT asmjs_dsp_factory* createAsmDSPFactoryFromFile(const string& filename,
                                                    int argc, const char* argv[],
                                                    string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createAsmDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, error_msg);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return NULL;
    }
}

EXPORT asmjs_dsp_factory* createAsmDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc, const char* argv[], string& error_msg)
{
    string expanded_dsp_content = "";
    string sha_key = "";
    
    // Deactivated for now since expandDSPFromString use thread based call of compiler ...
    /*
    if ((expanded_dsp_content = expandDSPFromString(name_app, dsp_content, argc, argv, sha_key, error_msg)) == "") {
        return NULL;
    } else
    */
    
    {
        int argc1 = 0;
        const char* argv1[64];
        
        argv1[argc1++] = "faust";
        argv1[argc1++] = "-lang";
        argv1[argc1++] = "ajs";
        argv1[argc1++] = "-o";
        argv1[argc1++] = "string";
        
        for (int i = 0; i < argc; i++) {
            argv1[argc1++] = argv[i];
        }
        
        argv1[argc1] = 0;  // NULL terminated argv
        
        dsp_factory_table<SDsp_factory>::factory_iterator it;
        asmjs_dsp_factory* factory = 0;
        
        if (gAsmjsFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            dsp_factory_base* dsp_factory_aux = compile_faust_factory(argc1, argv1,
                                                                     name_app.c_str(),
                                                                     dsp_content.c_str(),
                                                                     error_msg);
            if (!dsp_factory_aux) { return NULL; }
            factory = new asmjs_dsp_factory(dsp_factory_aux);
            gAsmjsFactoryTable.setFactory(factory);
            factory->setSHAKey(sha_key);
            factory->setDSPCode(expanded_dsp_content);
            return factory;
        }
    }
}

EXPORT bool deleteAsmjsDSPFactory(asmjs_dsp_factory* factory)
{
    return (factory) ? gAsmjsFactoryTable.deleteDSPFactory(factory): false;
}

// C API

EXPORT const char* createAsmCDSPFactoryFromFile(const char* filename, int argc, const char* argv[], char* error_msg)
{
    string error_msg_aux;
    asmjs_dsp_factory* factory = createAsmDSPFactoryFromFile(filename, argc, argv, error_msg_aux);
    if (factory) {
        stringstream dst;
        factory->write(&dst, false, false);
        strncpy(error_msg, error_msg_aux.c_str(), 4096);
        return strdup(flatten(dst.str()).c_str());
        // And keep factory...
    } else {
        strncpy(error_msg, "libfaust.js fatal error...\n", 4096);
        return NULL;
    }
}

EXPORT const char* createAsmCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg)
{
    string error_msg_aux;
    asmjs_dsp_factory* factory = createAsmDSPFactoryFromString(name_app, dsp_content, argc, argv, error_msg_aux);
    if (factory) {
        stringstream dst;
        factory->write(&dst, false, false);
        strncpy(error_msg, error_msg_aux.c_str(), 4096);
        return strdup(flatten(dst.str()).c_str());
        // And keep factory...
    } else {
        strncpy(error_msg, "libfaust.js fatal error...\n", 4096);
        return NULL;
    }
}

EXPORT const char* getCLibFaustVersion() { return FAUSTVERSION; }

EXPORT void freeCDSP(void* ptr)
{
    free(ptr);
}

