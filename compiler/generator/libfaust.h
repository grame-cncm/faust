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

EXPORT std::string generateSHA1(const std::string& dsp_content);

#endif
