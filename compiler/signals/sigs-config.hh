/************************************************************************
 ************************************************************************
    FAUST signal library
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

/** \file sigs-config.hh
 * Host configuration hooks of the signal library.
 *
 * The library delegates to the host application the few services whose exact
 * behaviour depends on the host (here the textual formatting of real numbers,
 * which in the Faust compiler follows the -single/-double/-quad and target
 * language options). Every hook has an autonomous default so a standalone
 * user gets a working library with no setup.
 */

#ifndef __SIGS_CONFIG__
#define __SIGS_CONFIG__

#include <string>

#include "sigs-export.hh"

namespace sigs {

/// Interns the signal constructors AND registers them in the Signal
/// signature (sigOpcode.hh), so each carries a dense opcode. The Faust
/// compiler calls this from global.cpp instead of interning the SIG*
/// symbols by hand; it fills the sigs::g.SIG* members.
SIGS_API void initSignalSymbols();

/// Standalone initialization of the whole signal library state (symbols,
/// property keys, type singletons, session state, option defaults). The
/// Faust compiler does NOT call it (global.cpp performs the same writes in
/// its own order); standalone hosts call it after tlib::init(), once per
/// session.
SIGS_API void init();

/// Formats a real number when pretty-printing signals (ppsig).
using RealPrinter = std::string (*)(double);

/// Install a custom real printer; nullptr restores the default (shortest
/// round-trip "%g" form, with a trailing ".0" when needed). Returns the
/// previously installed printer.
SIGS_API RealPrinter setRealPrinter(RealPrinter p);

/// Format a real number through the installed printer.
SIGS_API std::string printReal(double n);

}  // namespace sigs

#endif
