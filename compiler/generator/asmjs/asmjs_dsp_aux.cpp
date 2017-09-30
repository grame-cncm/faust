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

#include "compatibility.hh"
#include "asmjs_dsp_aux.hh"
#include "Text.hh"

typedef class faust_smartptr<asmjs_dsp_factory> SDsp_factory;

dsp_factory_table<SDsp_factory> gAsmjsFactoryTable;

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
    
    dsp_factory_base* dsp_factory_aux = compileFaustFactory(argc1, argv1,
                                                             name_app.c_str(),
                                                             dsp_content.c_str(),
                                                             error_msg,
                                                             true);
    if (dsp_factory_aux) {
        asmjs_dsp_factory* factory = new asmjs_dsp_factory(dsp_factory_aux);
        gAsmjsFactoryTable.setFactory(factory);
        factory->setSHAKey(sha_key);
        factory->setDSPCode(expanded_dsp_content);
        return factory;
    } else {
        return NULL;
    }
}

EXPORT bool deleteAsmjsDSPFactory(asmjs_dsp_factory* factory)
{
    return (factory) ? gAsmjsFactoryTable.deleteDSPFactory(factory): false;
}

// C API

static const char* createAsmCDSPFactoryAux(asmjs_dsp_factory* factory, const string& error_msg_aux, char* error_msg)
{
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    if (factory) {
        stringstream dst;
        factory->write(&dst, false, false);
        return strdup(flatten(dst.str()).c_str());
        // And keep factory...
    } else {
        return NULL;
    }
}

EXPORT const char* createAsmCDSPFactoryFromFile(const char* filename, int argc, const char* argv[], char* error_msg)
{
    string error_msg_aux;
    asmjs_dsp_factory* factory = createAsmDSPFactoryFromFile(filename, argc, argv, error_msg_aux);
    return createAsmCDSPFactoryAux(factory, error_msg_aux, error_msg);
}

EXPORT const char* createAsmCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg)
{
    string error_msg_aux;
    asmjs_dsp_factory* factory = createAsmDSPFactoryFromString(name_app, dsp_content, argc, argv, error_msg_aux);
    return createAsmCDSPFactoryAux(factory, error_msg_aux, error_msg);
}


