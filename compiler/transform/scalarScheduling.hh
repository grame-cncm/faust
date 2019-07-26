/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#ifndef __SCALARSCHEDULING__
#define __SCALARSCHEDULING__

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "signals.hh"

using namespace std;

/**
 * @brief generates a scalar scheduling from a set of instructions
 *
 * @param "filename.txt" the name of the file
 * @param I the set of instructions
 */
void scalarScheduling(const string& filename, set<Tree> I);

/**
 * @brief generates a parallel scheduling from a set of instructions
 *
 * @param "filename.txt" the name of the file
 * @param I the set of instructions
 */
void parallelScheduling(const string& filename, set<Tree> I);

#endif
