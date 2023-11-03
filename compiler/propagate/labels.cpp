/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    Copyright (C) 2023-2023 INRIA
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

#include "labels.hh"
#include "compatibility.hh"
#include "description.hh"
#include "global.hh"

using namespace std;

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
 */

static Tree pathRoot()
{
    return tree(gGlobal->PATHROOT);
}
static bool isPathRoot(Tree t)
{
    return isTree(t, gGlobal->PATHROOT);
}

static Tree pathParent()
{
    return tree(gGlobal->PATHPARENT);
}
static bool isPathParent(Tree t)
{
    return isTree(t, gGlobal->PATHPARENT);
}

static Tree pathCurrent()
{
    return tree(gGlobal->PATHCURRENT);
}
static bool isPathCurrent(Tree t)
{
    return isTree(t, gGlobal->PATHCURRENT);
}

/**
 * analyze name for "H:name" | "V:name" etc
 */

static Tree encodeName(char g, const string& name)
{
    switch (g) {
        case 'v':
        case 'V':
            return cons(tree(0), tree(name));

        case 'h':
        case 'H':
            return cons(tree(1), tree(name));

        case 't':
        case 'T':
            return cons(tree(2), tree(name));

        default:
            return cons(tree(0), tree(name));
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
        char   g = label[0];
        string s;
        int    i = 2;
        while ((label[i] != 0) && (label[i] != '/')) {
            s.push_back(label[i]);
            i++;
        }
        if (label[i] == '/') i++;
        return cons(encodeName(g, s), label2path(&label[i]));

    } else {
        return cons(tree(label), gGlobal->nil);
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
                // cerr << "abspath : " << *abspath << endl;
                return concatPath(tl(relpath), hd(relpath));
            } else {
                return concatPath(tl(relpath), tl(abspath));
            }
        } else if (isPathCurrent(head)) {
            return concatPath(tl(relpath), abspath);
        } else {
            return concatPath(tl(relpath), cons(head, abspath));
        }
    } else {
        faustassert(isNil(relpath));
        return abspath;
    }
}

static Tree normalizeLabel(Tree label, Tree path)
{
    // we suppose label = "../label" or "name/label" or "name"
    // cout << "Normalize Label " << *label << " with path " << *path << endl;
    if (isList(label)) {
        return cons(label, path);
    } else {
        Sym  s      = 0;
        bool is_sym = isSym(label->node(), &s);
        faustassert(is_sym);
        return concatPath(label2path(name(s)), path);
    }
}

// Normalize a path. For example, assuming i=3, "h:bidule/foo%i"
// is transformed into: cons[foo3,cons[cons[1,bidule],nil]]
// Where 0 indicates v, 1 indicates h, and 2 indicates t.
// Metadata are not removed !
Tree normalizePath(Tree path)
{
    // cout << "Normalize Path [[" << *path << "]]" << endl;
    Tree npath;
    if (isNil(path)) {
        npath = path;
    } else {
        npath = normalizeLabel(hd(path), normalizePath(tl(path)));
    }
    // cout << "              -> [[" << *npath << "]]" << endl;
    return npath;
}

// SuperNormalize a path by removing vht indications.
// For example, assuming i=3, "h:bidule/foo%i"
// is transformed into: cons[foo3,cons[bidule,nil]]
// Where 0 indicates v, 1 indicates h, and 2 indicates t.
// Metadata are not removed !
Tree superNormalizePath(Tree path)
{
    Tree npath = normalizePath(path);
    Tree spath;

    // std::cout << "SuperNormalize Path [[" << *path << "]]" << endl;
    if (isNil(npath)) {
        spath = npath;
    } else {
        Tree head = hd(npath);
        if (isList(head)) {
            std::string fulllabel = tree2str(tl(head));
            std::string label     = removeMetadata(fulllabel);
            spath                 = cons(tree(label), superNormalizePath(tl(npath)));
        } else {
            std::string fulllabel = tree2str(head);
            std::string label     = removeMetadata(fulllabel);
            spath                 = cons(tree(label), superNormalizePath(tl(npath)));
        }
    }
    // std::cout << "SuperNormalizePath " << *path << " -> " << *spath << std::endl;
    return spath;
}

/**
 * @brief Test if a label path is part of a group.
 * @param gpath the group path
 * @param lpath the label path
 * @param rpath the remaining path if there is a match
 * @return true if the label path is part of the group path
 */
bool matchGroup(Tree gpath, Tree lpath, Tree& rpath)
{
    if (gpath == lpath) {
        rpath = gGlobal->nil;
        return true;
    } else if (isList(lpath)) {
        Tree head = hd(lpath);
        Tree tail = tl(lpath);
        Tree rest;
        if (matchGroup(gpath, tail, rest)) {
            rpath = cons(head, rest);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}