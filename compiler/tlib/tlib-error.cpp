/************************************************************************
 ************************************************************************
    TLIB : tree library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#include "tlib-error.hh"

#include <cstdlib>
#include <sstream>
#include <stdexcept>

namespace tlib {

static void defaultErrorHandler(const std::string& msg)
{
    throw std::runtime_error(msg);
}

static ErrorHandler gErrorHandler = defaultErrorHandler;

ErrorHandler setErrorHandler(ErrorHandler h)
{
    ErrorHandler previous = gErrorHandler;
    gErrorHandler         = h ? h : defaultErrorHandler;
    return previous;
}

void error(const std::string& msg)
{
    gErrorHandler(msg);
    // The handler's contract is to never return; enforce it.
    std::abort();
}

void assertFailed(const char* file, int line)
{
    std::stringstream msg;
    msg << "ASSERT : failed assertion at " << file << ":" << line << "\n";
    error(msg.str());
}

}  // namespace tlib
