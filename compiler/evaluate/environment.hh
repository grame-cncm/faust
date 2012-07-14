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

#ifndef ENVIRONMENT_HH
#define ENVIRONMENT_HH

#include "tlib.hh"

Tree pushValueDef(Tree id, Tree def, Tree lenv);

bool searchIdDef(Tree id, Tree& def, Tree lenv);

Tree pushMultiClosureDefs(Tree ldefs, Tree visited, Tree lenv);

Tree copyEnvReplaceDefs(Tree anEnv, Tree ldefs, Tree visited, Tree curEnv);

bool isEnvBarrier(Tree t);

Tree pushEnvBarrier(Tree lenv);

#endif // ENVIRONMENT_HH
