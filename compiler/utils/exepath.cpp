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

#include <array>
#include <cstdio>
#include <memory>
#include <regex>
#include <sstream>
#include <string>

#ifdef WIN32
#include <windows.h>
#define kPSEP '\\'
#else
#include <libgen.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#define kPSEP '/'
#endif

#include "exepath.hh"

using namespace std;

//-----------------------------------------------------------------
// removes the exe name from a path (similar to dirname)
string exepath::dirup(const string& path)
{
    if (path.empty()) return path;
    size_t len = path.length();
    size_t pos = path.rfind(kPSEP, len - 2);
    if (pos == string::npos) return "";
    string out = path.substr(0, pos);
    return out == "." ? "" : out;
}

#ifndef EMCC
//-----------------------------------------------------------------
// recursively removes expressions like /a_name/.. from a path
string exepath::stripPath(const string& path)
{
    regex e("/[^/]*/\\.\\.");  // matches sequence like /path/..
    string stripped = regex_replace(path, e, string(""));
    return (stripped == path) ? path : stripPath(stripped);
}

#ifdef WIN32
//-----------------------------------------------------------------
string exepath::resolvelink(const string& path)
{
    return path;
}
#else

//-----------------------------------------------------------------
string exepath::resolvelink(const string& path)
{
    char    buff[FILENAME_MAX + 1];
    ssize_t n = readlink(path.c_str(), buff, FILENAME_MAX);
    if (n > 0) {
        buff[n]       = 0;
        bool relative = (buff[0] != '/');
        if (relative) {  // this is a relative link
            string tmp = dirup(path);
            return (tmp[0] == '/') ? stripPath(tmp + "/" + buff) : relative2absolute(buff);
        }
        return buff;
    }
    return "";
}

#endif

#ifdef WIN32
//-----------------------------------------------------------------
string exepath::get(const string& name)
{
    char  buff[1024];
    DWORD n = GetModuleFileNameA(NULL, buff, 1024);
    return n ? dirup(buff) : "";
}

#else
//-----------------------------------------------------------------
// exec any command and get the result from a pipe
static std::string exec(const string& cmd)
{
    std::array<char, FILENAME_MAX> buffer;
    std::string                    result;
    std::shared_ptr<FILE>          pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) return "";
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), FILENAME_MAX, pipe.get()) != nullptr) result += buffer.data();
    }
    return result;
}

static string GetCurrentWorkingDir()
{
    char buff[FILENAME_MAX];
    return GetCurrentDir(buff, FILENAME_MAX) ? buff : "";
}

//-----------------------------------------------------------------
string exepath::relative2absolute(const string& path)
{
    if (path[0] == kPSEP) return path;

    string pwd = GetCurrentWorkingDir();
    // the next line removes the form "./"
    string tmp = (path[1] == kPSEP) ? path.substr(2) : path;
    return stripPath(pwd + kPSEP + tmp);
}

//-----------------------------------------------------------------
string exepath::get(const string& argv0)
{
#ifdef WIN32
    if (argv0[1] == ':') {  // with msys, argv[0] is the full path name
        string path = dirup(argv0);
        return (path.back() != kPSEP) ? path + kPSEP : path;
    }
#endif
    string which;
    if ((argv0[0] == '.') || (argv0.find('/') != string::npos)) {
        // app call is relative to the current location
        which = relative2absolute(argv0);
    } else {
        stringstream cmd;
        cmd << "which " << argv0;
        which = exec(cmd.str());
        if (which.empty()) return "";
        if (which.back() == '\n') which.pop_back();
    }
    string target = resolvelink(which);
    if (!target.empty()) {
        which = target;
    }

    string path = dirup(which);
    return (path.back() != kPSEP) ? path + kPSEP : path;
}
#endif

#endif
