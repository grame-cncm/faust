/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
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

#ifndef _utilities_H
#define _utilities_H

#include <string>
#include <iostream>
#include <fstream> 

using namespace std;

inline std::string pathToContent(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

std::string searchIP();

bool isInt(const char* word);

long lopt(const char *argv[], const char* name, long def);

bool isopt(const char* argv[], const char* name);

bool isopt(int argc, const char *argv[], const char *name);

const char* loptions(const char* argv[], const char* name, const char* def);

const char* loptions(int argc, const char* argv[], const char* name, const char* def);

int lopt_spe(int i, const char* argv[], const char* name, char* path);

string nameWithoutSpaces(const string& name);

void printOptions(int argc, const char* argv[]);

#endif
