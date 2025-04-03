/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
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
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef LIBFAUST_C_H
#define LIBFAUST_C_H

#include <string.h>
#include <stdbool.h>

#include "faust/export.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compute a SHA1 key from a string.
 *
 * @param data - the string to be converted in SHA1 key
 * @param sha_key - a 64 characters buffer to be filled with the computed key
 *
 */
LIBFAUST_API void generateCSHA1(const char* data, char* sha_key);

/**
 * Expand a DSP source code into a self-contained DSP where all library import have been inlined starting from a
 * filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use
 * generateCAuxFilesXX)
 * @param sha_key - a SHA key to be filled by for the resulting DSP
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 *
 * @return the expanded DSP or a NULL string in case of failure (to be deleted by the caller using freeCMemory)
 */
LIBFAUST_API const char* expandCDSPFromFile(const char* filename, int argc, const char* argv[], char* sha_key,
                                            char* error_msg);

/**
 * Expand a DSP source code into a self-contained DSP where all library import have been inlined starting from a string.
 *
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use
 * generateCAuxFilesXX)
 * @param sha_key - a SHA key to be filled by for the resulting DSP
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 *
 * @return the expanded DSP or a NULL string in case of failure (to be deleted by the caller using freeCMemory)
 */
LIBFAUST_API const char* expandCDSPFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[],
                                           char* sha_key, char* error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 *
 * @return the expanded DSP or a empty string in case of failure
 */
LIBFAUST_API bool generateCAuxFilesFromFile(const char* filename, int argc, const char* argv[], char* error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a string.
 *
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 *
 * @return the true if success or false and an error message in case of failure
 */
LIBFAUST_API bool generateCAuxFilesFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[],
                                           char* error_msg);

/**
 * The free function to be used on memory returned expandCDSPFromString and expandCDSPFromFile.
 *
 * This is MANDATORY on Windows when otherwise all nasty runtime version related crashes can occur.
 *
 * @param ptr - the pointer to be deleted.
 */
LIBFAUST_API void freeCMemory(void* ptr);

#ifdef __cplusplus
}
#endif

#endif
