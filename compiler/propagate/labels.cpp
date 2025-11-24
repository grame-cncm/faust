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

/**
 * Root path marker ('/').
 * @return root marker tree node
 */
static Tree pathRoot()
{
    return tree(gGlobal->PATHROOT);
}
/**
 * Check if a node is the root path marker.
 * @param t candidate node
 * @return true if t equals PATHROOT
 */
static bool isPathRoot(Tree t)
{
    return isTree(t, gGlobal->PATHROOT);
}

/**
 * Parent path marker ("..").
 * @return parent marker tree node
 */
static Tree pathParent()
{
    return tree(gGlobal->PATHPARENT);
}
/**
 * Check if a node is the parent path marker.
 * @param t candidate node
 * @return true if t equals PATHPARENT
 */
static bool isPathParent(Tree t)
{
    return isTree(t, gGlobal->PATHPARENT);
}

/**
 * Current path marker (".").
 * @return current marker tree node
 */
static Tree pathCurrent()
{
    return tree(gGlobal->PATHCURRENT);
}
/**
 * Check if a node is the current path marker.
 * @param t candidate node
 * @return true if t equals PATHCURRENT
 */
static bool isPathCurrent(Tree t)
{
    return isTree(t, gGlobal->PATHCURRENT);
}

/**
 * Encode a label with its group code ("H:name", "V:name", "T:name").
 * @param g group code character ('v','h','t' and upper-case variants)
 * @param name label string without group prefix
 * @return cons(group code, label)
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
 * Analyze a label string and convert it to a top-down path.
 * Handles '/', '.', '..' and group prefixes (v:/h:/t:).
 * @param label C string representation of the label
 * @return path as a list of tree nodes (top-down)
 */
Tree label2path(const char* label)
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
        if (label[i] == '/') {
            i++;
        }
        return cons(encodeName(g, s), label2path(&label[i]));

    } else {
        return cons(tree(label), gGlobal->nil);
    }
}

/**
 * @brief Converts a widget modulation target string into a reversed path.
 *
 * The target string is parsed according to the following grammar:
 * <target> ::= [<sep>] <symbol> {<sep> <symbol>} [<sep>]
 * <sep> ::= "/" {<sep>}
 *
 * Example: "group1/group2/name" -> cons("name", cons("group2", cons("group1", nil)))
 *
 * @param target The target string to convert.
 * @return Tree The reversed path representation of the target.
 */
Tree target2path(const std::string& target)
{
    bool   frontier = true;          // Indicates if we are at the start of a new symbol
    Tree   path     = gGlobal->nil;  // The resulting path (constructed in reverse order)
    string currentSymbol;            // Holds the current symbol being built

    for (char c : target) {
        if (frontier) {
            if (c != '/') {
                currentSymbol = c;      // start a new symbol
                frontier      = false;  // end frontier mode
            }
        } else {
            if (c != '/') {
                currentSymbol += c;  // Continue building the current symbol
            } else {
                path     = cons(tree(currentSymbol), path);  // add current symbol to the path
                frontier = true;  // back to frontier mode for next symbol
            }
        }
    }

    // Add the last symbol to the path if it wasn't followed by a separator
    if (!frontier) {
        path = cons(tree(currentSymbol), path);
    }

    return path;
}

/**
 * Concatenate a top-down relative path with a bottom-up absolute path.
 * Handles '/', '..' and '.' navigation markers and clamps ".." at the root.
 * @param relpath relative path (top-down)
 * @param abspath absolute path (bottom-up)
 * @return combined absolute path (bottom-up)
 */
static Tree concatPath(Tree relpath, Tree abspath)
{
    if (isList(relpath)) {
        Tree head = hd(relpath);
        if (isPathRoot(head)) {
            return concatPath(tl(relpath), gGlobal->nil);
        } else if (isPathParent(head)) {
            if (isList(abspath)) {
                return concatPath(tl(relpath), tl(abspath));
            }
            // Already at root: drop the parent and keep going
            return concatPath(tl(relpath), gGlobal->nil);
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

/**
 * Extract a group code from a tree node. Only integer nodes are accepted.
 * @param codeTree node containing the code
 * @param code resulting integer code
 * @return true if codeTree holds an int code (0,1,2 expected)
 */
static bool getGroupCode(Tree codeTree, int& code)
{
    return isInt(codeTree->node(), &code);
}

/**
 * Detect a group label of the form (code,label) and extract components.
 * @param label candidate label tree
 * @param gcode group code (0=v,1=h,2=t) output
 * @param glabel inner label output
 * @return true if label matches the group pattern
 */
static bool isGroupLabel(Tree label, Tree& gcode, Tree& glabel)
{
    if (isList(label)) {
        Tree tail = tl(label);
        int  code;
        if (getGroupCode(hd(label), code) && (0 <= code) && (code <= 2)) {
            if (isList(tail) && isNil(tl(tail))) {
                gcode  = hd(label);
                glabel = hd(tail);
                return true;
            } else if (!isNil(tail)) {
                // Common case: label is a pair (gcode, glabel)
                gcode  = hd(label);
                glabel = tail;
                return true;
            }
        } else {
            faustassert(false && "Invalid group code in UI label");
        }
    }
    return false;
}

/**
 * Attach the group code to every element of a relative path, leaving
 * navigation markers (/ .. .) untouched.
 * @param relpath relative path (top-down)
 * @param gcode group code to attach (0=v,1=h,2=t)
 * @return relative path with group code applied
 */
static Tree addGroupCode(Tree relpath, Tree gcode)
{
    if (isList(relpath)) {
        Tree head = hd(relpath);
        if (isPathRoot(head) || isPathParent(head) || isPathCurrent(head)) {
            return cons(head, addGroupCode(tl(relpath), gcode));
        } else if (isList(head)) {
            return cons(head, addGroupCode(tl(relpath), gcode));
        } else {
            return cons(cons(gcode, head), addGroupCode(tl(relpath), gcode));
        }
    } else {
        faustassert(isNil(relpath));
        return gGlobal->nil;
    }
}

/**
 * Normalize a single label component against the current path.
 * - Plain symbols are converted through label2path then concatenated.
 * - Group labels propagate their navigation markers and apply the group code
 *   to each path element.
 * @param label label tree to normalize
 * @param path current absolute path (bottom-up)
 * @return new absolute path including the label
 */
static Tree normalizeLabel(Tree label, Tree path)
{
    // we suppose label = "../label" or "name/label" or "name"
    // cout << "Normalize Label " << *label << " with path " << *path << endl;
    if (isList(label)) {
        Tree gcode, glabel;
        if (isGroupLabel(label, gcode, glabel)) {
            Sym  s;
            bool is_sym = isSym(glabel->node(), &s);
            faustassert(is_sym);
            // Apply path modifiers (/, .., .) contained in the group label on the current path
            return concatPath(addGroupCode(label2path(name(s)), gcode), path);
        }
        return cons(label, path);
    } else {
        Sym  s;
        bool is_sym = isSym(label->node(), &s);
        faustassert(is_sym);
        return concatPath(label2path(name(s)), path);
    }
}

/**
 * Normalize a full path.
 * Example: "h:bidule/foo%i" -> cons[foo3, cons[cons[1,bidule], nil]]
 * (0=v, 1=h, 2=t). Metadata are preserved.
 * @param path path to normalize
 * @return normalized path
 */
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

/**
 * Normalize a path, drop group codes, and remove widget metadata.
 * Example: "h:bidule/foo%i" -> cons[foo3, cons[bidule, nil]].
 * The calls to removeMetadata() ensure label decorations like [unit:Hz] are discarded here.
 * @param path path to normalize
 * @return normalized path without group codes and metadata
 */
Tree superNormalizePath(Tree path)
{
    Tree npath = normalizePath(path);
    Tree spath;

    // std::cerr << "SuperNormalize Path [[" << *path << "]]" << endl;
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
    // std::cerr << "matchGroup " << *gpath << " " << *lpath << std::endl;
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
