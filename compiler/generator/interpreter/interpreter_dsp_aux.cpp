/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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
 
#include "interpreter_dsp_aux.h"
#include <string>

EXPORT interpreter_dsp_factory* getDSPInterpreterFactoryFromSHAKey(const std::string& sha_key)
{}

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromFile(const std::string& filename, 
                                                                  int argc, const char* argv[], 
                                                                  const std::string& target, 
                                                                  std::string& error_msg, int opt_level)
{
    error_msg = "Not implemented";
    return NULL;
}

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromString(const std::string& name_app, const std::string& dsp_content, 
                                                                    int argc, const char* argv[], 
                                                                    const std::string& target, 
                                                                    std::string& error_msg, int opt_level)
{
    return NULL;
}   

EXPORT bool deleteDSPInterpreterFactory(interpreter_dsp_factory* factory)
{
    return false;
}

EXPORT std::vector<std::string> getDSPInterpreterFactoryLibraryList(interpreter_dsp_factory* factory)
{
    
}

EXPORT std::vector<std::string> getAllDSPInterpreterFactories()
{}

EXPORT void deleteAllDSPInterpreterFactories()
{}

EXPORT interpreter_dsp* createDSPInterpreterInstance(interpreter_dsp_factory* factory)
{
    return NULL;
}

EXPORT void deleteDSPInterpreterInstance(interpreter_dsp* dsp)
{}

