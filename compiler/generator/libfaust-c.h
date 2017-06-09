/************************************************************************
 ************************************************************************
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 ************************************************************************
 ************************************************************************/

#ifndef LIBFAUST_C_H
#define LIBFAUST_C_H

#include <string>

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
