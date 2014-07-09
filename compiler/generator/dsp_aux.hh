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
 
#ifndef DSP_AUX_H
#define DSP_AUX_H

#include <string>
#include "export.hh"

// Public C++ interface without LLVM

EXPORT std::string expandDSPFromFile(const std::string& filename, 
                                    int argc, const char* argv[], 
                                    std::string& sha_key,
                                    std::string& error_msg);

EXPORT std::string expandDSPFromString(const std::string& name_app, 
                                        const std::string& dsp_content, 
                                        int argc, const char* argv[], 
                                        std::string& sha_key,
                                        std::string& error_msg);

EXPORT bool generateAuxFilesFromFile(const std::string& filename, int argc, const char* argv[], std::string& error_msg);

EXPORT bool generateAuxFilesFromString(const std::string& name_app, const std::string& dsp_content, int argc, const char* argv[], std::string& error_msg);

#ifdef __cplusplus
extern "C" {
#endif
    
// Public C interface without LLVM

EXPORT const char* expandCDSPFromFile(const char* filename, 
                                    int argc, const char* argv[], 
                                    char* sha_key,
                                    char* error_msg);

EXPORT const char* expandCDSPFromString(const char* name_app, 
                                    const char* dsp_content, 
                                    int argc, const char* argv[], 
                                    char* sha_key,
                                    char* error_msg);

EXPORT bool generateCAuxFilesFromFile(const char* filename, int argc, const char* argv[], char* error_msg);

EXPORT bool generateCAuxFilesFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg);

#ifdef __cplusplus
}
#endif

#endif
