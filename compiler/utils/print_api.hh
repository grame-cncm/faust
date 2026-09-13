/************************************************************************
 ************************************************************************
    FAUST compiler
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
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ************************************************************************
 ************************************************************************/

#pragma once

#include <string>

#include "faust/export.h"
#include "tlib.hh"

// The two printers of the public API (libfaust, the documentator, the
// generators) : a signal or a box as a string, shared subexpressions named
// or not, bounded in size. They reset the compiler's print state first, which
// is why they live in the compiler and not in the signal library.

LIBFAUST_API std::string printSignal(Tree sig, bool shared, int max_size);
LIBFAUST_API std::string printBox(Tree box, bool shared, int max_size);
