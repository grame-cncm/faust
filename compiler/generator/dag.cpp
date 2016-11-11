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


#include "dag.hh"
#include "ppsig.hh"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;


// Public methods

// creates an empty dag
dag::dag() {}

// creates a dag by merging two dags
dag::dag(const dag& A, const dag& B)
{
	add(A);
	add(B);
}

// creates a dag by combining a node and a dependency dag
dag::dag(Tree n, const dag& D, bool recursive)
{
	// vertices = n + vertices(D)
	fVertices.insert(n);
	fVertices.insert(D.fVertices.begin(), D.fVertices.end());

	// edges = {(n,ei)} + edges(D) [+ {(n,)}] if recursive
	fEdges.insert(D.fEdges.begin(), D.fEdges.end());
	for (auto e: D.fEntries) {
		fEdges.insert(pair<Tree,Tree>(n,e));
	}
	if (recursive) fEdges.insert(pair<Tree,Tree>(n,n));

	// entries = {n}
	fEntries.insert(n);

}

dag::~dag() {}

// implementation

void dag::add(const dag& D)
{
	fVertices.insert(D.fVertices.begin(), D.fVertices.end());
	fEntries.insert(D.fEntries.begin(), D.fEntries.end());
	fEdges.insert(D.fEdges.begin(), D.fEdges.end());
}

/**
 
 strict digraph loopgraph {
 rankdir=LR; node [fontsize=10];
 S0x7ffd6a40f8e0[label="@" color="blue" shape="ellipse"];
 S0x7ffd6a40f850[label="Proj0" color="blue" shape="ellipse"];
 S0x7ffd6a40f610[label="REC W0" color="blue" style="bold" shape="ellipse"];
 S0x7ffd6a40f120[label="@" color="blue" style="bold" shape="ellipse"];
 S0x7ffd6a407930[label="1" color="blue" shape="box"];
 S0x7ffd6a407930 -> S0x7ffd6a40f120[ color="blue"];
 S0x7ffd6a407930 -> S0x7ffd6a40f120[ color="blue"];
 S0x7ffd6a40f120 -> S0x7ffd6a40f610[ color="blue" style="bold"];
 S0x7ffd6a40f610 -> S0x7ffd6a40f850[ color="blue" style="bold"];
 S0x7ffd6a40f850 -> S0x7ffd6a40f8e0[ color="blue"];
 S0x7ffd6a407690[label="0" color="blue" shape="box"];
 S0x7ffd6a407690 -> S0x7ffd6a40f8e0[ color="blue"];
 OUTPUT_0[color="red2" style="filled" fillcolor="pink"];
 S0x7ffd6a40f8e0 -> OUTPUT_0[ color="blue"];
 }


 **/

ostream& dag::print (ostream& fout) const
{
	fout << "strict digraph loopgraph {" << endl;
	fout << "node [fontsize=9, shape=box];" << endl;

	// print all vertices first
	for (auto n: fVertices) {
		fout << "V" << n << "[label=\"" << ppsig(n) << "\"];" << endl;
	}

	for (auto n: fVertices) {
		for (auto m: fVertices) {
			if (fEdges.count(make_pair(n,m))>0) {
				fout << "V" << n << " -> " << "V" << m << ";" << endl;
			}
		}
	}

	fout << "}" << endl;
	return fout;
}
