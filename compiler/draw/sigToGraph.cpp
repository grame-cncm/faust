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

#include <stdio.h>

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "interval.hh"
#include "exception.hh"
#include "sigToGraph.hh"
#include "signals.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "xtended.hh"

using namespace std;

static void   recdraw(Tree sig, set<Tree>& drawn, ostream& fout);
static string nodeattr(Type t);
static string edgeattr(Type t);
static string sigLabel(Tree sig);

/**
 * Draw a list of signals as a directed graph using graphviz's dot language
 */
void sigToGraph(Tree L, ostream& fout)
{
    set<Tree> alreadyDrawn;

    fout << "strict digraph loopgraph {\n"
         << "    rankdir=LR; node [fontsize=10];" << endl;
    int out = 0;
    while (isList(L)) {
        recdraw(hd(L), alreadyDrawn, fout);

        fout << "OUTPUT_" << out << "[color=\"red2\" style=\"filled\" fillcolor=\"pink\"];" << endl;
        fout << 'S' << hd(L) << " -> "
             << "OUTPUT_" << out++ << "[" << edgeattr(getCertifiedSigType(hd(L))) << "];" << endl;
        L = tl(L);
    }

    fout << "}" << endl;
}

/******************************* IMPLEMENTATION ***********************************/

/**
 * Draw recursively a signal
 */
static void recdraw(Tree sig, set<Tree>& drawn, ostream& fout)
{
    // cerr << ++gGlobal->TABBER << "ENTER REC DRAW OF " << sig << "$" << *sig << endl;
    tvec subsig;
    int  n;

    if (drawn.count(sig) == 0) {
        drawn.insert(sig);
        if (isList(sig)) {
            do {
                recdraw(hd(sig), drawn, fout);
                sig = tl(sig);
            } while (isList(sig));
        } else {
            // draw the node
            fout << 'S' << sig << "[label=\"" << sigLabel(sig) << "\"" << nodeattr(getCertifiedSigType(sig)) << "];"
                 << endl;

            // draw the subsignals
            n = getSubSignals(sig, subsig);
            if (n > 0) {
                if (n == 1 && isList(subsig[0])) {
                    Tree id, body;
                    faustassert(isRec(sig, id, body));
                    if (!isRec(sig, id, body)) {
                    }
                    // special recursion case, recreate a vector of subsignals instead of the
                    // list provided by getSubSignal
                    Tree L = subsig[0];
                    subsig.clear();
                    n = 0;
                    do {
                        subsig.push_back(hd(L));
                        L = tl(L);
                        n += 1;
                    } while (isList(L));
                }

                for (int i = 0; i < n; i++) {
                    recdraw(subsig[i], drawn, fout);
                    fout << 'S' << subsig[i] << " -> " << 'S' << sig << "[" << edgeattr(getCertifiedSigType(subsig[i]))
                         << "];" << endl;
                }
            }
        }
    }
    // cerr << --gGlobal->TABBER << "EXIT REC DRAW OF " << sig << endl;
}

string commonAttr(Type t)
{
    string sout;
    // nature
    if (t->nature() == kInt) {
        sout += " color=\"blue\"";
    } else {
        sout += " color=\"red\"";
    }
    // vectorability
    if (t->vectorability() == kVect && t->variability() == kSamp) {
        sout += " style=\"bold\"";
    }
    return sout;
}

/**
 * Convert a signal type into edge attributes
 */

static string edgeattr(Type t)
{
    string sout(commonAttr(t));
    sout += " label =\"";
    sout += t->getInterval().to_string();
    sout += ", ";
    sout += t->getRes().toString();
    sout += "\"";
    return sout;
}

/**
 * Convert a signal type into node attributes
 */
static string nodeattr(Type t)
{
    string sout(commonAttr(t));

    // variability
    if (t->variability() == kKonst) {
        sout += " shape=\"box\"";
    } else if (t->variability() == kBlock) {
        sout += " shape=\"hexagon\"";
    } else if (t->variability() == kSamp) {
        sout += " shape=\"ellipse\"";
    }
    return sout;
}

/**
 * translate signal binary operations into strings
 */
static const char* binopname[] = {"+", "-", "*", "/", "%", "<<", ">>", ">", "<", ">=", "<=", "==", "!=", "&", "|", "^"};

/**
 * return the label of a signal as a string
 */
static string sigLabel(Tree sig)
{
    int    i;
    double r;
    Tree   size, gen, wi, ws, tbl, ri, x, y, z, c, type, name, file, ff, largs, le, sel, var, label;

    xtended* p = (xtended*)getUserData(sig);

    stringstream fout;

    if (p) {
        fout << p->name();
    } else if (isSigInt(sig, &i)) {
        fout << i;
    } else if (isSigReal(sig, &r)) {
        fout << r;
    } else if (isSigWaveform(sig)) {
        fout << "waveform";
    }

    else if (isSigInput(sig, &i)) {
        fout << "INPUT_" << i;
    }
    // else if ( isSigOutput(sig, &i, x) )             { fout << "OUTPUT_" << i; }

    else if (isSigDelay1(sig, x)) {
        fout << "mem";
    } else if (isSigDelay(sig, x, y)) {
        fout << "@";
    } else if (isSigPrefix(sig, x, y)) {
        fout << "prefix";
    } else if (isSigBinOp(sig, &i, x, y)) {
        fout << binopname[i];
    } else if (isSigFFun(sig, ff, largs)) {
        fout << "ffunction:" << *ff;
    } else if (isSigFConst(sig, type, name, file)) {
        fout << *name;
    } else if (isSigFVar(sig, type, name, file)) {
        fout << *name;
    }

    else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        fout << "write:" << sig;
    } else if (isSigRDTbl(sig, tbl, ri)) {
        fout << "read";
    }

    else if (isSigSelect2(sig, sel, x, y)) {
        fout << "select2";
    }

    else if (isSigGen(sig, x)) {
        fout << "generator";
    }

    else if (isProj(sig, &i, x)) {
        fout << "Proj" << i;
    } else if (isRec(sig, var, le)) {
        fout << "REC " << *var;
    }

    else if (isSigIntCast(sig, x)) {
        fout << "int";
    } else if (isSigBitCast(sig, x)) {
        fout << "bit";
    } else if (isSigFloatCast(sig, x)) {
        fout << "float";
    }
#if 0
    else if ( isSigButton(sig, label) ) 			{ fout << "button \"" << *label << '"'; }
    else if ( isSigCheckbox(sig, label) ) 			{ fout << "checkbox \"" << *label << '"'; }
    else if ( isSigVSlider(sig, label,c,x,y,z) )	{ fout << "vslider \"" << *label << '"';  }
    else if ( isSigHSlider(sig, label,c,x,y,z) )	{ fout << "hslider \"" << *label << '"';  }
    else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ fout << "nentry \"" << *label << '"';  }
    
    else if ( isSigVBargraph(sig, label,x,y,z) )	{ fout << "vbargraph \"" << *label << '"'; 	}
    else if ( isSigHBargraph(sig, label,x,y,z) )	{ fout << "hbargraph \"" << *label << '"'; 	}
#else
    else if (isSigButton(sig, label)) {
        fout << "button";
    } else if (isSigCheckbox(sig, label)) {
        fout << "checkbox";
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        fout << "vslider";
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        fout << "hslider";
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        fout << "nentry";
    }

    else if (isSigVBargraph(sig, label, x, y, z)) {
        fout << "vbargraph";
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        fout << "hbargraph";
    }
#endif
    else if (isSigAttach(sig, x, y)) {
        fout << "attach";
    }

    else if (isSigAssertBounds(sig, x, y, z)) {
        fout << "assertbounds";
    }

    else if (isSigLowest(sig, x)) {
        fout << "lowest";
    }

    else if (isSigHighest(sig, x)) {
        fout << "highest";
    }

    else {
        stringstream error;
        error << "ERROR : sigToGraph.cpp, unrecognized signal : " << *sig << endl;
        throw faustexception(error.str());
    }

    return fout.str();
}
