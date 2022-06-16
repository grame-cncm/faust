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

#ifndef interpreter_dynamic_dsp_aux_h
#define interpreter_dynamic_dsp_aux_h

#include "interpreter_dsp_aux.hh"

LIBFAUST_API interpreter_dsp_factory* createInterpreterDSPFactoryFromFile(const std::string& filename, int argc,
                                                                          const char* argv[], std::string& error_msg);

LIBFAUST_API interpreter_dsp_factory* createInterpreterDSPFactoryFromString(const std::string& name_app,
                                                                            const std::string& dsp_content, int argc,
                                                                            const char* argv[], std::string& error_msg);

LIBFAUST_API interpreter_dsp_factory* createInterpreterDSPFactoryFromSignals(const std::string& name_app, tvec signals,
                                                                             int argc, const char* argv[],
                                                                             std::string& error_msg);

LIBFAUST_API interpreter_dsp_factory* createInterpreterDSPFactoryFromBoxes(const std::string& name_app, Tree box,
                                                                           int argc, const char* argv[],
                                                                           std::string& error_msg);

#ifdef __cplusplus
extern "C" {
#endif

// Public C interface

LIBFAUST_API interpreter_dsp_factory* createCInterpreterDSPFactoryFromFile(const char* filename, int argc,
                                                                        const char* argv[], char* error_msg);

LIBFAUST_API interpreter_dsp_factory* createCInterpreterDSPFactoryFromString(const char* name_app,
                                                                         const char* dsp_content, int argc,
                                                                         const char* argv[], char* error_msg);

LIBFAUST_API interpreter_dsp_factory* createCInterpreterDSPFactoryFromSignals(const char* name_app, Signal* signals,
                                                                          int argc, const char* argv[],
                                                                          char* error_msg);

LIBFAUST_API interpreter_dsp_factory* createCInterpreterDSPFactoryFromBoxes(const char* name_app, Tree box,
                                                                         int argc, const char* argv[],
                                                                         char* error_msg);

#ifdef __cplusplus
}
#endif

#endif
