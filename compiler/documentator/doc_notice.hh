/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#ifndef _DOCNOTICE_
#define _DOCNOTICE_

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

using namespace std;

/** 
 * gDocNoticeFlagMap is public to let others 
 * turn to "true" flags that one want to print. 
 */
extern map<string, bool> gDocNoticeFlagMap;

void initDocNotice();
void printDocNotice(const string& faustversion, ostream& docout);

#endif
