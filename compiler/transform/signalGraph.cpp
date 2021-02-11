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

/************************************************************************
 ************************************************************************
 * Split a list of signals into a set of instruction
 *
 *  USAGE : set<Tree> I = splitSignalsToInstr(fConditionProperty, L);
 *
 ************************************************************************
 ************************************************************************/

#include "signalGraph.hh"

#include <fstream>
#include <ostream>

#include "global.hh"
#include "instructionInputs.hh"
#include "old_occurences.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigIdentity.hh"
#include "signalDependencies.hh"
#include "sigtyperules.hh"

using namespace std;

/**
 * @brief generates a dotfile graph of a set of instructions
 *
 * @param "filename.dot" the name of the file
 * @param instr the set of instructions
 */
void signalGraph(const string& filename, const set<Tree>& I)
{
    // cerr << "\n\nBEGIN build Dependency Graph: " << filename << endl;

    digraph<Tree, multidep> G;
    // Dictionnary   Dic;

    for (auto i : I) {
        G.add(dependencyGraph(i));
        // Dic.add(i);
    }

    ofstream f;
    f.open(filename);
    // cerr << "\n\nCreate dotfile: " << filename << endl;

    // dotfile2(f, Dic, G);
    dotfile2(f, G);
    f.close();
    // cerr << "END build Dependency Graph: " << filename << "\n\n" << endl;
}

/**
 * @brief generates a dotfile graph of a set of instructions in vector mode
 *
 * @param "filename.dot" the name of the file
 * @param instr the set of instructions
 */
void signalVectorGraph(const string& filename, const set<Tree>& I)
{
    // cerr << "\n\nBEGIN build Dependency Graph: " << filename << endl;

    digraph<Tree, multidep> G;

    for (auto i : I) {
        G.add(dependencyGraph(i));
    }

    digraph<digraph<Tree, multidep>, multidep> VG = graph2dag(G);
    ofstream                                   f;
    f.open(filename);
    // cerr << "\n\nCreate dotfile: " << filename << endl;

    // dotfile2(f, Dic, G);
    dotfile3(f, VG);
    f.close();
    // cerr << "END build Dependency Graph: " << filename << "\n\n" << endl;
}
