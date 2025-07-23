/************************************************************************
 ************************************************************************
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

 ************************************************************************
 ************************************************************************/

#ifndef LIBFAUST_H
#define LIBFAUST_H

#include <string.h>
#include <string>

#include "faust/export.h"

/*!
 \addtogroup libfaustcpp C++ interface for the tools API.
 @{
 */

/**
 * Generate SHA1 key from a string.
 *
 * @param data - the string to be converted in SHA1 key
 *
 * @return the SHA key.
 */
LIBFAUST_API std::string generateSHA1(const std::string& data);

/**
 * Expand a DSP source code into a self-contained DSP where all library import have been inlined
 * starting from a filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered
 * (-svg, ...) --> use generateAuxFilesXX)
 * @param sha_key - a SHA key to be filled by for the resulting DSP
 * @param error_msg - the error string to be filled
 *
 * @return the expanded DSP or an empty string in case of failure.
 */
LIBFAUST_API std::string expandDSPFromFile(const std::string& filename, int argc,
                                           const char* argv[], std::string& sha_key,
                                           std::string& error_msg);

/**
 * Expand a DSP source code into a self-contained DSP where all library import have been inlined
 * starting from a string.
 *
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered
 * (-svg, ...) --> use generateAuxFilesXX)
 * @param sha_key - a SHA key to be filled by for the resulting DSP
 * @param error_msg - the error string to be filled
 *
 * @return the expanded DSP or a empty string in case of failure.
 */
LIBFAUST_API std::string expandDSPFromString(const std::string& name_app,
                                             const std::string& dsp_content, int argc,
                                             const char* argv[], std::string& sha_key,
                                             std::string& error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return true if success or false and an error message in case of failure.
 */
LIBFAUST_API bool generateAuxFilesFromFile(const std::string& filename, int argc,
                                           const char* argv[], std::string& error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return the result as a string or a empty string in case of failure.
 */
LIBFAUST_API std::string generateAuxFilesFromFile2(const std::string& filename, int argc,
                                                   const char* argv[], std::string& error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a string.
 *
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return true if success or false and an error message in case of failure.
 */
LIBFAUST_API bool generateAuxFilesFromString(const std::string& name_app,
                                             const std::string& dsp_content, int argc,
                                             const char* argv[], std::string& error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a string.
 *
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return the result as a string or a empty string in case of failure.
 */
LIBFAUST_API std::string generateAuxFilesFromString2(const std::string& name_app,
                                                     const std::string& dsp_content, int argc,
                                                     const char* argv[], std::string& error_msg);

/*!
 @}
 */

#endif
