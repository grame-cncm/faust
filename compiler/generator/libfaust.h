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

#include <string>

/**
 * Expand a DSP source code into a self-contained DSP where all library import have been inlined starting from a filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param sha_key - a SHA key to be filled by for the resulting DSP
 * @param error_msg - the error string to be filled
 *
 * @return the expanded DSP or an empty string in case of failure
 */
std::string expandDSPFromFile(const std::string& filename,
                            int argc, const char* argv[],
                            std::string& sha_key,
                            std::string& error_msg);

/**
 * Expand a DSP source code into a self-contained DSP where all library import have been inlined starting from a string.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param sha_key - a SHA key to be filled by for the resulting DSP
 * @param error_msg - the error string to be filled
 *
 * @return the expanded DSP or a empty string in case of failure
 */
std::string expandDSPFromString(const std::string& name_app,
                                const std::string& dsp_content,
                                int argc, const char* argv[], 
                                std::string& sha_key,
                                std::string& error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a filename.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return the expanded DSP or an empty string in case of failure
 */
bool generateAuxFilesFromFile(const std::string& filename, int argc, const char* argv[], std::string& error_msg);

/**
 * Generate additional file (other backends, SVG, XML, JSON...) starting from a string.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return the expanded DSP or a empty string in case of failure
 */
bool generateAuxFilesFromString(const std::string& name_app, const std::string& dsp_content, int argc, const char* argv[], std::string& error_msg);

/**
 * Generate SHA key from a DSP as a string
 *
 * @param dsp_content - the DSP string
 *
 * @return the SHA key
 */
std::string generateSHA1(const std::string& dsp_content);

/**
 * The free function to be used on memory returned by getCDSPMachineTarget, getCName, getCSHAKey,
 * getCDSPCode, getCLibraryList, getAllCDSPFactories, writeCDSPFactoryToBitcode,
 * writeCDSPFactoryToIR, writeCDSPFactoryToMachine,expandCDSPFromString and expandCDSPFromFile.
 *
 * This is MANDATORY on Windows when otherwise all nasty runtime version related crashes can occur.
 *
 * @param ptr - the pointer to be deleted.
 */
extern "C" void freeCMemory(void* ptr);

#endif
