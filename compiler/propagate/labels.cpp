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

#include "labels.hh"
#include "compatibility.hh"
#include "global.hh"

//=========================== PATHNAME ===============================

/**
 * Grammar for labels with pathnames
 *-----------------------------------
 * <label> = <name> | <path> <name>
 * <name> = [^/]+             
 * <path> = <apath> | <rpath>
 * <apath> = '/' | '/' <rpath>
 * <rpath> = (<gname> '/')+
 * <gname> = ".." | "." | <gtype> <name>
 * <gtype> = "h:" | "H:" | "v:" | V:" | "t:" | "T:"
 *
 */

Tree pathRoot()						{ return tree(gGlobal->PATHROOT); }
bool isPathRoot(Tree t)				{ return isTree(t, gGlobal->PATHROOT); }

Tree pathParent()					{ return tree(gGlobal->PATHPARENT); }
bool isPathParent(Tree t)			{ return isTree(t, gGlobal->PATHPARENT); }

Tree pathCurrent()					{ return tree(gGlobal->PATHCURRENT); }
bool isPathCurrent(Tree t)			{ return isTree(t, gGlobal->PATHCURRENT); }


/**
 * analyze name for "H:name" | "V:name" etc
 */

static Tree encodeName(char g, const string& name)
{
    switch (g) {
        case 'v':
        case 'V': return cons(tree(0), tree(name));

        case 'h':
        case 'H': return cons(tree(1), tree(name));

        case 't':
        case 'T': return cons(tree(2), tree(name));

        default : return cons(tree(0), tree(name));
    }
}


/**
 * Analyzes a label and converts it as a path
 */

static Tree label2path(const char* label)
{
    if (label[0] == 0) {
        return cons(tree(""), gGlobal->nil);

    } else if (label[0] == '/') {
        return cons(pathRoot(), label2path(&label[1]));

    } else if ((label[0] == '.') && (label[1] == '/')) {
        return label2path(&label[2]);

    } else if ((label[0] == '.') && (label[1] == '.') && (label[2] == '/')) {
        return cons(pathParent(), label2path(&label[3]));

    } else if (label[1] == ':') {
        char    g = label[0];
        string  s;
        int     i = 2;
        while ((label[i] != 0) && (label[i] != '/')) {
            s.push_back(label[i]);
            i++;
        }
        if (label[i] == '/') i++;
        return cons(encodeName(g,s), label2path(&label[i]));

    } else {
        return cons(tree(label),gGlobal->nil);
    }
}


/**
 * Concatenate the relative path to the absolute path
 * Note that the relpath is top-down while the abspath 
 * is bottom-up
 */
 
static Tree concatPath(Tree relpath, Tree abspath)
{
	if (isList(relpath)) {
		Tree head = hd(relpath);
		if (isPathRoot(head)) {
			return concatPath(tl(relpath), gGlobal->nil);
		} else if (isPathParent(head)) {
			if (!isList(abspath)) { 
				//cerr << "abspath : " << *abspath << endl; 
				return concatPath(tl(relpath), hd(relpath));
			} else {
				return concatPath(tl(relpath), tl(abspath));
			}
		} else if (isPathCurrent(head)) {
			return concatPath(tl(relpath), abspath);
		} else {
			return concatPath(tl(relpath), cons(head,abspath));
		}
	} else {
		faustassert(isNil(relpath));
		return abspath;
	}
}


static Tree normalizeLabel(Tree label, Tree path)
{
	// we suppose label = "../label" ou "name/label" ou "name"	
	//cout << "Normalize Label " << *label << " with path " << *path << endl;
	if (isList(label)) {
		return cons(label, path);
	} else {
        Sym s;
        bool is_sym = isSym(label->node(),&s);
        faustassert(is_sym);
        return concatPath(label2path(name(s)),path);
	}
}

Tree normalizePath(Tree path)
{
    //cout << "Normalize Path [[" << *path << "]]" << endl;
	Tree npath;
    if (isNil(path)) {
        npath = path;
    } else {
        npath = normalizeLabel(hd(path), normalizePath(tl(path)));
    }
    //cout << "              -> [[" << *npath << "]]" << endl;
	return npath;
}

