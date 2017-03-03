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
 * @file colorize.cpp
 * Uses colors to analyze dependencies among sub expressions
 */

#include "colorize.h"
#include "signals.hh"
#include "global.hh"

using namespace std; 

// static funvtions needed to implement splitDependance

static int allocateColor(Tree exp);							///< allocate a new unique color for exp
static void colorize(Tree exp, int color);					///< add color information to exp and all its subtrees
static void uncolorize(Tree exp);							///< remove color information
static void listMultiColoredExp(Tree exp, set<Tree>& lst);	///< list multicolored subexpressions of exp

/**
 * Analyze a set of expressions to discover its dependencies that is subexpressions
 * common to at least two of these expressions
 * @param exps set of expressions to analyze
 * @param post resulting set of post expressions
 * @param pre resulting set of pre expressions
 */
void splitDependance(const set<Tree>& exps, set<Tree>& post, set<Tree>& pre)
{
 	set<Tree>::const_iterator e;
 	for (e= exps.begin(); e != exps.end(); e++) {
 		colorize(*e, allocateColor(*e));
 	}
 	
 	pre.clear();
 	for (e = exps.begin(); e != exps.end(); e++) {
 		listMultiColoredExp(*e, pre);
 	}
 	
 	post.clear();
 	set_difference(exps.begin(), exps.end(), pre.begin(), pre.end(), inserter(post, post.begin()));
 	
 	for (e = exps.begin(); e != exps.end(); e++) {
 		uncolorize(*e);
 	}
}

//------------------------------------------- IMPLEMENTATION  (level 1)-----------------------------------------------------

static void addColor(Tree exp, int color);					///< a color to the colors of exp
static bool hasColor(Tree exp, int color);					///< true if exp is already colored with color
static int colorsCount(Tree exp);							///< returns the number of colors of exp
static void clearColors(Tree exp);							///< remove the color property of exp

/**
 * Allocate a unique color (an integer) for an expression.
 * by converting its address into an integer
 */
int allocateColor(Tree exp)
{
//	return int(exp); 
	int& color = gGlobal->gColorMap[exp];
	if (!color) {
		color = gGlobal->gNextFreeColor++;
    }
	return color;
}

/**
 * Add a color to all the expression tree
 */
void colorize(Tree exp, int color)
{
	if (! hasColor(exp, color)) {
		addColor(exp, color);
		vector<Tree> v;
		int n = getSubSignals(exp, v, false);
		for (int i=0; i<n; i++) colorize(v[i], color);
	}	
}

/**
 * Remove the colors of an expression tree
 */
void uncolorize(Tree exp)
{
	if (colorsCount(exp) > 0) {
		clearColors(exp);
		vector<Tree> v;
		int n = getSubSignals(exp, v, false);
		for (int i=0; i<n; i++) uncolorize(v[i]);
	}	
}

/**
 * Make a set of the multicolored sub-expressions
 */
void listMultiColoredExp(Tree exp, set<Tree>& lst)
{
	faustassert(colorsCount(exp) > 0);
	if (colorsCount(exp) > 1) {
		// we have found a multicolored expression
		lst.insert(exp);
	} else {
		// it is a monocolored expression
		// we search its subexpressions
		vector<Tree> v;
		int n = getSubSignals(exp, v, false);
		for (int i=0; i<n; i++) {
			listMultiColoredExp(v[i], lst);
		}
	}	
}

//------------------------------------------- IMPLEMENTATION  (level 2)-----------------------------------------------------

/**
 * set the color-set property of sig
 * @param sig the signal we want to type
 * @param t the type of the signal
 */
void setColorProperty(Tree sig, set<int>* colorset)
{
	setProperty(sig, gGlobal->COLORPROPERTY, tree((void*)colorset));
}

/**
 * retrieve the color-set property of sig
 * @param sig the signal we want to know the color-set property
 */
set<int>* getColorProperty(Tree sig)
{
	Tree tt;
	if (!getProperty(sig, gGlobal->COLORPROPERTY, tt)) {
		return 0;
	} else {
		return (set<int>*)tree2ptr(tt);
	}
}

/**
 * Add a color to the colorset of exp. Create an empty
 * coloset if needed.
 * @param sig the signal we want to color
 * @param color the color used
 */
void addColor(Tree exp, int color)
{
	set<int>* cset = getColorProperty(exp);
	if (cset == 0) {
		cset = new set<int>();
		setColorProperty(exp, cset);
	}
	cset->insert(color);
}

/**
 * Test if exp as color in its colorset
 * @param sig the signal we want to test
 * @param color the color to test
 * @return true if color is member of the colorset of sig
 */
bool hasColor(Tree exp, int color)
{
	set<int>* cset = getColorProperty(exp);
	if (cset==0) {
		return false;
	} else {
		return cset->find(color) != cset->end();
	}
}

/**
 * Count the number of colors of exp
 * @param exp the expression we want to count the colors
 * @return the number of elements in the color set or 0
 */
static int colorsCount(Tree exp)
{
	set<int>* cset = getColorProperty(exp);
	if (cset==0) {
		return 0;
	} else {
		return (int)cset->size();
	}
}

/**
 * Count the number of colors of exp
 * @param exp the expression we want to count the colors
 * @return the number of elements in the color set or 0
 */
static void clearColors(Tree exp)
{
	set<int>* cset = getColorProperty(exp);
	if (cset != 0) {
		cset->clear();
	}
}


