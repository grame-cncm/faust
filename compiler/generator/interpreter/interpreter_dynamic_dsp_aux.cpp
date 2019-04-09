/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>

#include "Text.hh"
#include "interpreter_dynamic_dsp_aux.hh"
#include "libfaust.h"

using namespace std;

EXPORT interpreter_dsp_factory* createInterpreterDSPFactoryFromFile(const string& filename, int argc,
                                                                    const char* argv[], string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos  = filename.find(".dsp");

    if (pos != string::npos) {
        return createInterpreterDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv,
                                                     error_msg);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)\n";
        return nullptr;
    }
}

EXPORT interpreter_dsp_factory* createInterpreterDSPFactoryFromString(const string& name_app, const string& dsp_content,
                                                                      int argc, const char* argv[], string& error_msg)
{
    TLock lock(dsp_factory_imp::gDSPFactoriesLock);
    string expanded_dsp_content, sha_key;

    if ((expanded_dsp_content = expandDSPFromString(name_app, dsp_content, argc, argv, sha_key, error_msg)) == "") {
        return nullptr;
    } else {
        int         argc1 = 0;
        const char* argv1[32];

        argv1[argc1++] = "faust";
        argv1[argc1++] = "-lang";
        argv1[argc1++] = "interp";
        argv1[argc1++] = "-o";
        argv1[argc1++] = "string";

        for (int i = 0; i < argc; i++) {
            argv1[argc1++] = argv[i];
        }
        argv1[argc1] = 0;  // NULL terminated argv

        dsp_factory_table<SDsp_factory>::factory_iterator it;
        interpreter_dsp_factory*                          factory = 0;

        if (gInterpreterFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            dsp_factory_base* dsp_factory_aux =
                compileFaustFactory(argc1, argv1, name_app.c_str(), dsp_content.c_str(), error_msg, true);
            if (dsp_factory_aux) {
                dsp_factory_aux->setName(name_app);
                factory = new interpreter_dsp_factory(dsp_factory_aux);
                gInterpreterFactoryTable.setFactory(factory);
                factory->setSHAKey(sha_key);
                factory->setDSPCode(expanded_dsp_content);
                return factory;
            } else {
                return nullptr;
            }
        }
    }
}
