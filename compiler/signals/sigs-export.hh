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

#ifndef __SIGS_EXPORT__
#define __SIGS_EXPORT__

// Symbol visibility macro. Empty for a static library (the default build).
// A host application that embeds the signal library in a shared library can
// redefine it from its build system, e.g. :
//     -DSIGS_EXPORT_HEADER='"faust/export.h"' -DSIGS_API=LIBFAUST_API
// SIGS_EXPORT_HEADER is included first so the macro SIGS_API expands to can
// be defined (dllexport/dllimport on Windows, visibility("default") elsewhere).
#ifdef SIGS_EXPORT_HEADER
#include SIGS_EXPORT_HEADER
#endif
#ifndef SIGS_API
#define SIGS_API
#endif

#endif
