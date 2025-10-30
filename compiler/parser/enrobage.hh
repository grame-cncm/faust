/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
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
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>

void streamCopyLicense(std::istream& src, std::ostream& dst, const std::string& exceptiontag);
void streamCopyUntil(std::istream& src, std::ostream& dst, const std::string& until);
void streamCopyUntilEnd(std::istream& src, std::ostream& dst);

std::unique_ptr<std::ifstream> openArchStream(const char* filename);

FILE* fopenSearch(const char* filename, std::string& fullpath);

bool checkURL(const char* filename);

inline std::string fileBasename(const std::string& name)
{
    std::filesystem::path path(name);
    auto                  filename = path.filename();
    return (filename.empty()) ? name : filename.string();
}

inline std::string fileDirname(const std::string& name)
{
    std::filesystem::path path(name);
    auto                  parent = path.parent_path();
    return (parent.empty()) ? "." : parent.string();
}

std::string stripEnd(const std::string& name, const std::string& ext);

std::string makeOutputFile(const std::string& fname);
