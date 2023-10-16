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

#ifndef _SIMPLIFY_
#define _SIMPLIFY_

/*
 * Simplify a signal.
 *
 * Note that the resulting tree will possibly contain incorrectly
 * promoted subtrees that have to be processed using castPromote.
 */
Tree simplify(Tree sig);

/**
 * Converts regular tables into doc tables in order to
 * facilitate the mathematical documentation generation
 */
Tree docTableConvertion(Tree sig);

#endif
