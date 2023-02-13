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

#include "files.hh"
#include "compatibility.hh"
#include "exception.hh"
#include "global.hh"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <errno.h>
#include <iostream>
#include <sstream>

using namespace std;

/**
 *Switch back to the previously stored current directory
 */

void choldDir()
{
    if (chdir(gGlobal->gCurrentDir.c_str()) == 0) {
        return;
    } else {
        stringstream error;
        error << "ERROR : choldDir : " << strerror(errno) << std::endl;
        throw faustexception(error.str());
    }
}

/**
 * Create a new directory in the current one to store the diagrams.
 * The current directory is saved to be later restored.
 */

void mkchDir(const string& dirname)
{
    getCurrentDir();
    if (gGlobal->gCurrentDir != "") {
        int status = faust_mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (status == 0 || errno == EEXIST) {
            if (chdir(dirname.c_str()) == 0) {
                return;
            }
        }
    }

    stringstream error;
    error << "ERROR : mkchDir : " << strerror(errno) << std::endl;
    throw faustexception(error.str());
}

void makeDir(const string& dirname)
{
    getCurrentDir();
    if (gGlobal->gCurrentDir != "") {
        int status = faust_mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (status == 0 || errno == EEXIST) {
            return;
        }
    }

    stringstream error;
    error << "ERROR : makeDir : " << strerror(errno) << std::endl;
    throw faustexception(error.str());
}

void getCurrentDir()
{
    char  buffer[FAUST_PATH_MAX];
    char* current_dir    = getcwd(buffer, FAUST_PATH_MAX);
    gGlobal->gCurrentDir = (current_dir) ? current_dir : "";
}


