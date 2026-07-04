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

/** \file tlib-error.hh
 * Error reporting for tlib.
 *
 * The library never terminates the process on its own: every internal error
 * goes through a single, replaceable handler. The default handler throws
 * std::runtime_error, so a standalone user gets standard C++ exceptions with
 * no setup. A host application (e.g. the Faust compiler) can install its own
 * handler to throw its own exception type instead; since such a type usually
 * derives from std::runtime_error, existing catch sites keep working.
 */

#ifndef __TLIB_ERROR__
#define __TLIB_ERROR__

#include <string>

#include "export.hh"

namespace tlib {

/// A handler receives the error message and MUST NOT return (throw or abort).
using ErrorHandler = void (*)(const std::string& msg);

/// Install a custom error handler; nullptr restores the default
/// (throw std::runtime_error). Returns the previously installed handler.
TLIB_API ErrorHandler setErrorHandler(ErrorHandler h);

/// Report an internal error through the installed handler. If the handler
/// wrongly returns, std::abort() is called.
[[noreturn]] TLIB_API void error(const std::string& msg);

/// Report a failed assertion (used by the TLIB_ASSERT macro).
[[noreturn]] TLIB_API void assertFailed(const char* file, int line);

}  // namespace tlib

#define TLIB_ASSERT(cond) ((cond) ? (void)0 : tlib::assertFailed(__FILE__, __LINE__))

#endif
