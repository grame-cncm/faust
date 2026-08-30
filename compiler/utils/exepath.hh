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

#ifndef __EXEPATH__
#define __EXEPATH__

#include <string>

#ifdef EMCC
class exepath {
   public:
    static std::string get(const std::string& name) { return ""; }
    static std::string dirup(const std::string& path);
};

#else

class exepath {
    // recursively removes expressions like /a_name/.. from a path
    static std::string stripPath(const std::string& path);

    // resolves symbolic links (not implemented on Windows/MSVC
    static std::string resolvelink(const std::string& path);

#ifndef WIN32
    static std::string relative2absolute(const std::string& path);
#endif

   public:
    // gives the current exe path
    // name is the executable name as given by argv[0]
    // on output: the path to the current app, terminated with a path separator
    // note that symbolic links are resolved on unix like systems
    static std::string get(const std::string& name);

    // removes the last /xxxx part
    static std::string dirup(const std::string& path);
};
#endif

#endif
