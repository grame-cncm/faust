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

 /**
 * @file drawschema.cpp
 * Implement block-diagram schema generation in svg or postscript format.
 * The result is a folder containing one or more schema files in svg or
 * ps format. Complex block-diagrams are automatically splitted.
 */

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#include <ostream>
#include <sstream>
#include <set>
#include <utility>
#include <map>
#include <stack>
#include <string>

#include "boxes.hh"
#include "ppbox.hh"
#include "prim2.hh"
#include "global.hh"

#include <vector>
#include "devLib.h"
#include "ppbox.hh"
#include "xtended.hh"
#include "occurrences.hh"
#include "boxcomplexity.hh"

#include "schema.h"
#include "drawschema.hh"
#include "compatibility.hh"
#include "names.hh"
#include "description.hh"
#include "property.hh"
#include "exception.hh"
#include "files.hh"

#if 0
#define linkcolor "#b3d1dc"
#define normalcolor "#ffeaa2"
#define uicolor "#F1CFA1"
#define slotcolor "#ffffd7"
#define numcolor "#ffffff"
#endif

#if 0
#define linkcolor "#F57900" 
#define normalcolor "#4B71A1"
#define uicolor "#47945E"
#define slotcolor "#EDD400"
#define numcolor "#4B71A1"
#endif

#if 0
#define linkcolor "#47945E" 
#define normalcolor "#4B71A1"
#define uicolor "#f44800"
#define slotcolor "#EDD400"
#define numcolor "#f44800"
#endif

#if 0
#define linkcolor "#47945E" 
#define normalcolor "#4B71A1"
#define uicolor "#816647"
#define slotcolor "#EDD400"
#define numcolor "#f44800"
#endif

#if 0
#define linkcolor "#003366" 
#define normalcolor "#4B71A1"
#define uicolor "#816647"
#define slotcolor "#EDD400"
#define numcolor "#f44800"
#endif

#if 0
#define linkcolor "#003366" 
#define normalcolor "#4B71A1"
#define uicolor "#477881"
#define slotcolor "#816647"
#define numcolor "#f44800"
#endif


#if 1
#define linkcolor "#003366" 
#define normalcolor "#4B71A1"
#define uicolor "#477881"
#define slotcolor "#47945E"
#define numcolor "#f44800"
#define invcolor "#ffffff"
#endif

using namespace std;

// prototypes of internal functions
static void 	writeSchemaFile(Tree bd);
static schema* 	generateDiagramSchema (Tree bd);
static schema* 	generateInsideSchema(Tree t);
static void 	scheduleDrawing(Tree t);
static bool 	pendingDrawing(Tree& t);
static schema* 	generateAbstractionSchema(schema* x, Tree t);
static schema* 	generateOutputSlotSchema(Tree a);
static schema* 	generateInputSlotSchema(Tree a);
static schema* 	generateBargraphSchema(Tree t);
static schema* 	generateUserInterfaceSchema(Tree t);
static schema* 	generateSoundfileSchema(Tree t);
static char* 	legalFileName(Tree t, int n, char* dst);

static schema*  addSchemaInputs(int ins, schema* x);
static schema*  addSchemaOutputs(int outs, schema* x);

/**
 *The entry point to generate from a block diagram as a set of
 *svg files stored in the directory "<projname>-svg/" or
 *"<projname>-ps/" depending of <dev>.
 */
void drawSchema(Tree bd, const char* projname, const char* dev)
{
	gGlobal->gDevSuffix 	= dev;
	gGlobal->gFoldingFlag 	= boxComplexity(bd) > gGlobal->gFoldThreshold;
   
	mkchdir(projname); 			// create a directory to store files

	scheduleDrawing(bd);		// schedule the initial drawing

	Tree t; while (pendingDrawing(t)) {
		writeSchemaFile(t);		// generate all the pending drawing
	}

	cholddir();					// return to current directory
}


/************************************************************************
 ************************************************************************
							IMPLEMENTATION
 ************************************************************************
 ************************************************************************/


//------------------- to schedule and retreive drawing ------------------

/**
 * Schedule a makeBlockSchema diagram to be drawn.
 */
static void scheduleDrawing(Tree t)
{
	if (gGlobal->gDrawnExp.find(t) == gGlobal->gDrawnExp.end()) {
		gGlobal->gDrawnExp.insert(t);
		gGlobal->gBackLink.insert(make_pair(t,gGlobal->gSchemaFileName));	// remember the enclosing filename
		gGlobal->gPendingExp.push(t);
	}
}

/**
 * Retrieve next block diagram that must be drawn
 */
static bool pendingDrawing(Tree& t)
{
	if (gGlobal->gPendingExp.empty()) return false;
	t = gGlobal->gPendingExp.top();
	gGlobal->gPendingExp.pop();
	return true;
}

//------------------------ dealing with files -------------------------

/**
 * Write a top level diagram. A top level diagram
 * is decorated with its definition name property
 * and is drawn in an individual file
 */
static void writeSchemaFile(Tree bd)
{
	Tree			id;
	schema* 		ts;
    int             ins, outs;

	char 			temp[1024];

	gGlobal->gOccurrences = new Occurrences(bd);
    getBoxType(bd, &ins, &outs);

	bool hasname = getDefNameProperty(bd, id); 

	//faustassert(hasname);
	if (!hasname) {
		// create an arbitrary name 
		id = tree(Node(unique("diagram_")));
	}

	// generate legal file name for the schema
    stringstream s1; s1 << legalFileName(bd, 1024, temp) << "." << gGlobal->gDevSuffix;
    string res1 = s1.str();
    gGlobal->gSchemaFileName = res1;

	// generate the label of the schema
	stringstream s2; s2 << tree2str(id);
	string link = gGlobal->gBackLink[bd];
    ts = makeTopSchema(addSchemaOutputs(outs, addSchemaInputs(ins, generateInsideSchema(bd))), 20, s2.str(), link);
	// draw to the device defined by gDevSuffix
    if (strcmp(gGlobal->gDevSuffix, "svg") == 0) {
        SVGDev dev(res1.c_str(), ts->width(), ts->height());
        ts->place(0,0, kLeftRight);
        ts->draw(dev);
        {
            collector c;
            ts->collectTraits(c);
            c.draw(dev);
        }
    } else {
        PSDev dev(res1.c_str(), ts->width(), ts->height());
        ts->place(0,0, kLeftRight);
        ts->draw(dev);
        {
            collector c;
            ts->collectTraits(c);
            c.draw(dev);
        }
    }
}

/**
 * Transform the definition name property of tree <t> into a
 * legal file name.  The resulting file name is stored in
 * <dst> a table of at least <n> chars. Returns the <dst> pointer
 * for convenience.
 */
static char* legalFileName(Tree t, int n, char* dst)
{
	Tree	id;
	int 	i=0;
	if (getDefNameProperty(t, id)) {
		const char* 	src = tree2str(id);
		for (i=0; isalnum(src[i]) && i<16; i++) {
			dst[i] = src[i];
		}
	}
	dst[i] = 0;
	if (strcmp(dst, "process") != 0) { 
		// if it is not process add the hex address to make the name unique
		snprintf(&dst[i], n-i, "-%p", (void*)t);
	}
	return dst;
}


//------------------------ generating the schema -------------------------


/**
 * isInverter(t) returns true if t == '*(-1)'. This test is used
 * to simplify diagram by using a special symbol for inverters.
 */
Tree gInverter[6];

static bool isInverter(Tree t)
{
    // init gInverted table. For some reason doesn't work if done outside
    if (gInverter[0] == 0) {
        gInverter[0] = boxSeq(boxPar(boxWire(), boxInt(-1)),boxPrim2(sigMul));
        gInverter[1] = boxSeq(boxPar(boxInt(-1), boxWire()),boxPrim2(sigMul));
        gInverter[2] = boxSeq(boxPar(boxWire(), boxReal(-1.0)),boxPrim2(sigMul));
        gInverter[3] = boxSeq(boxPar(boxReal(-1.0), boxWire()),boxPrim2(sigMul));
        gInverter[4] = boxSeq(boxPar(boxInt(0), boxWire()),boxPrim2(sigSub));
        gInverter[5] = boxSeq(boxPar(boxReal(0.0), boxWire()),boxPrim2(sigSub));
    };

    //cerr << "isInverter " << t << '$' << boxpp(t) << endl;
    for (int i=0; i<6; i++) {
        if (t == gInverter[i]) return true;
    }
    return false;
}


/**
 * Compute the Pure Routing property, that is expressions
 * only made of cut, wires and slots. No labels will be
 * dispayed for pure routing expressions.
 */

static bool isPureRouting(Tree t)
{
    bool    r;
    int     ID;
    Tree    x,y;

    if (gGlobal->gPureRoutingProperty->get(t,r)) {
        return r;
    } else if (    isBoxCut(t)
                || isBoxWire(t)
                || isInverter(t)
                || isBoxSlot(t, &ID)
                || (isBoxPar(t,x,y) && isPureRouting(x) && isPureRouting(y))
                || (isBoxSeq(t,x,y) && isPureRouting(x) && isPureRouting(y))
                || (isBoxSplit(t,x,y) && isPureRouting(x) && isPureRouting(y))
                || (isBoxMerge(t,x,y) && isPureRouting(x) && isPureRouting(y))
              ) {
        gGlobal->gPureRoutingProperty->set(t,true);
        return true;
    } else {
        gGlobal->gPureRoutingProperty->set(t,false);
        return false;
    }
}


/**
 * Generate an appropriate schema according to
 * the type of block diagram. When folding is requiered,
 * instead of going down block-diagrams with a name,
 * schedule them for an individual file.
 */
static schema* generateDiagramSchema(Tree t)
{
	Tree	id;
	int		ins, outs;

	//cerr << t << " generateDiagramSchema " << boxpp(t)<< endl;

	if (getDefNameProperty(t, id)) {
		stringstream 	s; s << tree2str(id);
		//cerr << t << "\tNAMED : " << s.str() << endl;
	}

	if (gGlobal->gFoldingFlag && /*(gOccurrences->getCount(t) > 0) &&*/
			(boxComplexity(t) > 2) && getDefNameProperty(t, id)) {
		char 	temp[1024];
		getBoxType(t, &ins, &outs);
		stringstream s, l;
		s << tree2str(id);
		l << legalFileName(t,1024,temp) << "." << gGlobal->gDevSuffix;
		scheduleDrawing(t);
		return makeBlockSchema(ins, outs, s.str(), linkcolor, l.str());

    } else  if (getDefNameProperty(t, id) && ! isPureRouting(t)) {
		// named case : not a slot, with a name
		// draw a line around the object with its name
		stringstream 	s; s << tree2str(id);
		return makeDecorateSchema(generateInsideSchema(t), 10, s.str());

	} else {
		// normal case
		return generateInsideSchema(t);
	}
}



/**
 * Generate the inside schema of a block diagram
 * according to its type
 */
static schema* generateInsideSchema(Tree t)
{
	Tree a, b, ff, l, type,name,file;
	int		i;
	double	r;
	prim0	p0;
	prim1	p1;
	prim2	p2;
	prim3	p3;
	prim4	p4;
	prim5	p5;


	xtended* xt = (xtended*)getUserData(t);

	if (xt)							{ return makeBlockSchema(xt->arity(), 1, xt->name(), normalcolor, ""); }

    else if (isInverter(t))         { return makeInverterSchema(invcolor); }

	else if (isBoxInt(t, &i))		{ stringstream 	s; s << i; return makeBlockSchema(0, 1, s.str(), numcolor, "" ); }
	else if (isBoxReal(t, &r)) 		{ stringstream 	s; s << r; return makeBlockSchema(0, 1, s.str(), numcolor, "" ); }
	else if (isBoxWaveform(t))      { return makeBlockSchema(0, 2, "waveform{...}", normalcolor, ""); }
    else if (isBoxWire(t)) 			{ return makeCableSchema(); }
	else if (isBoxCut(t)) 			{ return makeCutSchema();  }

	else if (isBoxPrim0(t, &p0)) 	{ return makeBlockSchema(0, 1, prim0name(p0), normalcolor, ""); }
	else if (isBoxPrim1(t, &p1)) 	{ return makeBlockSchema(1, 1, prim1name(p1), normalcolor, ""); }
	else if (isBoxPrim2(t, &p2)) 	{ return makeBlockSchema(2, 1, prim2name(p2), normalcolor, ""); }
	else if (isBoxPrim3(t, &p3)) 	{ return makeBlockSchema(3, 1, prim3name(p3), normalcolor, ""); }
	else if (isBoxPrim4(t, &p4)) 	{ return makeBlockSchema(4, 1, prim4name(p4), normalcolor, ""); }
	else if (isBoxPrim5(t, &p5)) 	{ return makeBlockSchema(5, 1, prim5name(p5), normalcolor, ""); }

	else if (isBoxFFun(t, ff)) 					{ return makeBlockSchema(ffarity(ff), 1, ffname(ff), normalcolor, ""); }
    else if (isBoxFConst(t, type,name,file))    { return makeBlockSchema(0, 1, tree2str(name), normalcolor, ""); }
    else if (isBoxFVar (t, type, name,file))    { return makeBlockSchema(0, 1, tree2str(name), normalcolor, ""); }

	else if (isBoxButton(t)) 		{ return generateUserInterfaceSchema(t); }
	else if (isBoxCheckbox(t)) 		{ return generateUserInterfaceSchema(t); }
	else if (isBoxVSlider(t)) 		{ return generateUserInterfaceSchema(t); }
	else if (isBoxHSlider(t)) 		{ return generateUserInterfaceSchema(t); }
	else if (isBoxNumEntry(t)) 		{ return generateUserInterfaceSchema(t); }
	else if (isBoxVBargraph(t))		{ return generateBargraphSchema(t); }
	else if (isBoxHBargraph(t))		{ return generateBargraphSchema(t); }
	else if (isBoxSoundfile(t))		{ return generateSoundfileSchema(t); }

	// don't draw group rectangle when labels are empty (ie "")
    else if (isBoxVGroup(t,l,a))	{ 	stringstream s; s << "vgroup(" << extractName(l) << ")";
										schema* r = generateDiagramSchema(a);
									  	return makeDecorateSchema(r, 10, s.str()); }
    else if (isBoxHGroup(t,l,a))	{ 	stringstream s; s << "hgroup(" << extractName(l) << ")";
										schema* r = generateDiagramSchema(a);
									  	return makeDecorateSchema(r, 10, s.str()); }
    else if (isBoxTGroup(t,l,a))	{ 	stringstream s; s << "tgroup(" << extractName(l) << ")";
										schema* r = generateDiagramSchema(a);
									  	return makeDecorateSchema(r, 10, s.str()); }

	else if (isBoxSeq(t, a, b)) 	{ return makeSeqSchema(generateDiagramSchema(a), generateDiagramSchema(b)); }
	else if (isBoxPar(t, a, b)) 	{ return makeParSchema(generateDiagramSchema(a), generateDiagramSchema(b)); }
	else if (isBoxSplit(t, a, b)) 	{ return makeSplitSchema(generateDiagramSchema(a), generateDiagramSchema(b)); }
	else if (isBoxMerge(t, a, b)) 	{ return makeMergeSchema(generateDiagramSchema(a), generateDiagramSchema(b)); }
	else if (isBoxRec(t, a, b)) 	{ return makeRecSchema(generateDiagramSchema(a), generateDiagramSchema(b)); }

	else if (isBoxSlot(t, &i))		{ return generateOutputSlotSchema(t); }
	else if (isBoxSymbolic(t,a,b))	{
		Tree 	id;
		if (getDefNameProperty(t, id)) {
			return generateAbstractionSchema(generateInputSlotSchema(a), b);
		} else {
			return makeDecorateSchema(generateAbstractionSchema(generateInputSlotSchema(a), b), 10, "Abstraction");
		}
	} else {
        stringstream error;
        error << "Internal Error, box expression not recognized : ";
        t->print(error);
        error << endl;
        throw faustexception(error.str());
	}
}

/**
 * Convert User interface element into a textual representation
 */
static void UserInterfaceDescription(Tree box, string& d)
{
    Tree    t1, label, cur, min, max, step, chan;
    stringstream 	fout;
    // user interface
         if (isBoxButton(box, label))	fout << "button(" << extractName(label) << ')';
    else if (isBoxCheckbox(box, label))	fout << "checkbox(" << extractName(label) << ')';
    else if (isBoxVSlider(box, label, cur, min, max, step)) 	{
        fout << "vslider("
             << extractName(label) << ", "
             << boxpp(cur) << ", "
             << boxpp(min) << ", "
             << boxpp(max) << ", "
             << boxpp(step)<< ')';
    }
    else if (isBoxHSlider(box, label, cur, min, max, step)) 	{
        fout << "hslider("
             << extractName(label) << ", "
             << boxpp(cur) << ", "
             << boxpp(min) << ", "
             << boxpp(max) << ", "
             << boxpp(step)<< ')';
    }
    else if (isBoxVGroup(box, label, t1)) {
        fout << "vgroup(" << extractName(label) << ", " << boxpp(t1, 0) << ')';
    }
    else if (isBoxHGroup(box, label, t1)) {
        fout << "hgroup(" << extractName(label) << ", " << boxpp(t1, 0) << ')';
    }
    else if (isBoxTGroup(box, label, t1)) {
        fout << "tgroup(" << extractName(label) << ", " << boxpp(t1, 0) << ')';
    }
    else if (isBoxHBargraph(box, label, min, max)) 	{
        fout << "hbargraph("
             << extractName(label) << ", "
             << boxpp(min) << ", "
             << boxpp(max) << ')';
    }
    else if (isBoxVBargraph(box, label, min, max)) 	{
        fout << "vbargraph("
             << extractName(label) << ", "
             << boxpp(min) << ", "
             << boxpp(max) << ')';
    }
    else if (isBoxNumEntry(box, label, cur, min, max, step)) 	{
        fout << "nentry("
             << extractName(label) << ", "
             << boxpp(cur) << ", "
             << boxpp(min) << ", "
             << boxpp(max) << ", "
             << boxpp(step)<< ')';
    }
    else if (isBoxSoundfile(box, label, chan)) 	{
        fout << "soundfile("
             << extractName(label) << ", "
             << boxpp(chan) << ')';
    }
    else {
        throw faustexception("INTERNAL ERROR : unknown user interface element\n");
    }
    d = fout.str();
}


/**
 * Generate a 0->1 block schema for a user interface element
 */
static schema* 	generateUserInterfaceSchema(Tree t)
{
    string s; UserInterfaceDescription(t,s);
    return makeBlockSchema(0, 1, s, uicolor, "");
}


/**
 * Generate a 1->1 block schema for a user interface bargraph
 */
static schema* generateBargraphSchema(Tree t)
{
    string s; UserInterfaceDescription(t,s);
    return makeBlockSchema(1, 1, s, uicolor, "");
}

/**
 * Generate a 1->c+2 block schema for soundfile("toto",c) 
 */
static schema* generateSoundfileSchema(Tree t)
{
    Tree    label, chan;
    if (isBoxSoundfile(t, label, chan)) {
        int n = tree2int(chan);
        string s; UserInterfaceDescription(t,s);
        return makeBlockSchema(1, 2+n, s, uicolor, "");
    } else {
        throw faustexception("Internal error\n");
    }
}



/**
 * Generate a 1->0 block schema for an input slot
 */
static schema* generateInputSlotSchema(Tree a)
{
	Tree id; faustassert(getDefNameProperty(a, id));
	stringstream s; s << tree2str(id);
	return makeBlockSchema(1, 0, s.str(), slotcolor, "");
}



/**
 * Generate a 0->1 block schema for an output slot
 */
static schema* generateOutputSlotSchema(Tree a)
{
	Tree id; faustassert(getDefNameProperty(a, id));
	stringstream s; s << tree2str(id);
	return makeBlockSchema(0, 1, s.str(), slotcolor, "");
}



/**
 * Generate an abstraction schema by placing in sequence
 * the input slots and the body
 */
static schema* generateAbstractionSchema(schema* x, Tree t)
{
	Tree 	a,b;

	while (isBoxSymbolic(t,a,b)) {
		x = makeParSchema(x, generateInputSlotSchema(a));
		t = b;
	}
	return makeSeqSchema(x, generateDiagramSchema(t));
}

static schema* addSchemaInputs(int ins, schema* x)
{
    if (ins==0) {
        return x;
    } else {
        schema* y = 0;
        do {
            schema* z = makeConnectorSchema();
            if (y != 0) {
                y = makeParSchema(y,z);
            } else {
                y = z;
            }
        } while (--ins);
        return makeSeqSchema(y,x);
    }
}


static schema* addSchemaOutputs(int outs, schema* x)
{
    if (outs==0) {
        return x;
    } else {
        schema* y = 0;
        do {
            schema* z = makeConnectorSchema();
            if (y != 0) {
                y = makeParSchema(y,z);
            } else {
                y = z;
            }
        } while (--outs);
        return makeSeqSchema(x,y);
    }
}
