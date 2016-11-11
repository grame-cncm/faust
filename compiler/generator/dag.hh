/************************************************************************
 ************************************************************************
 FAUST compiler
	Copyright (C) 2016-2017 GRAME, Centre National de Creation Musicale
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

/*****************************************************************************
 A DAG OF SIGNALS
	HISTORY
	13/10/16 : first version
 *****************************************************************************/


#ifndef _DAG_
#define _DAG_

#include "signals.hh"
#include <set>
#include <iostream>

class dag
{
protected:
	set<Tree>				fVertices;	// all vertices of the DAG
	set<Tree>				fEntries;	// entry points subset of vertices
	set<pair<Tree, Tree> >	fEdges;		// all edges between vertices

public:
    dag();											// creates an empty dag
	dag(const dag& a, const dag& b);				// union of two dags
	dag(Tree n, const dag& a, bool recursive);		// new dependecy dag

	void add(const dag& d);		// add the content of a dag to this one
	ostream& print (ostream& fout) const;
    ~dag();
};


inline ostream& operator<<(ostream& dst, const dag& g)
{
	return g.print(dst);
}

#endif
