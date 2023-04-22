/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2023 GRAME, Centre National de Creation Musicale
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

#include "tlib.hh"

//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of sig
//------------------------------------------------------------------------------

int getSharingCount(Tree sig, Tree key);

//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of sig
//------------------------------------------------------------------------------

void sharingAnalysis(Tree t, Tree& key);
