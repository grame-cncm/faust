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

#include <vector>

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
    string currentSymbol;            // Holds the current symbol being builded

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
                frontier = true;  // abck to frontier mode for next symbol
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
        Sym  s;
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

/**
 * @brief Normalize a group label with type prefix against current path.
 * This function properly handles relative path components (.., .) in group labels.
 * 
 * @param groupType 0=vertical, 1=horizontal, 2=tab
 * @param label The group label (may contain relative path components like "../name")
 * @param currentPath The current path context (bottom-up list)
 * @return The normalized path to use for contents of this group
 */
Tree normalizeGroupPath(int groupType, Tree label, Tree currentPath)
{
    // Safety check
    if (!label) {
        return cons(cons(tree(groupType), tree("")), currentPath);
    }
    
    // Convert the label tree to a string
    Sym s;
    if (!isSym(label->node(), &s)) {
        // If it's not a symbol, treat it as pre-parsed
        return cons(cons(tree(groupType), label), currentPath);
    }
    
    // Get the label string
    const char* labelStr = name(s);
    if (!labelStr || labelStr[0] == 0) {
        // Empty label
        return cons(cons(tree(groupType), tree("")), currentPath);
    }
    
    // Parse the label to extract path components
    Tree parsedPath = label2path(labelStr);
    
    if (!parsedPath || isNil(parsedPath)) {
        // Empty parsed path, shouldn't happen but be safe
        return cons(cons(tree(groupType), label), currentPath);
    }
    
    // If the parsed path is just a single name (no / separators), 
    // encode it with the group type and add to current path
    if (isNil(tl(parsedPath))) {
        Tree name = hd(parsedPath);
        // Check if it's a special path component
        if (isPathRoot(name) || isPathParent(name) || isPathCurrent(name)) {
            // Just apply the path operation
            return concatPath(parsedPath, currentPath);
        } else {
            // It's a simple name, encode it with group type
            return cons(cons(tree(groupType), name), currentPath);
        }
    }
    
    // The parsed path has multiple components: [elem1, elem2, ..., finalName]
    // We need to split off the final name and apply the rest (prefix) to currentPath.
    // Strategy: Build a list of all elements except the last, then process them.
    
    // Collect all elements except the last into a vector for easier processing
    std::vector<Tree> elements;
    Tree temp = parsedPath;
    while (!isNil(temp)) {
        elements.push_back(hd(temp));
        temp = tl(temp);
    }
    
    if (elements.empty()) {
        // Should not happen, but be safe
        return cons(cons(tree(groupType), label), currentPath);
    }
    
    // The last element is the final name
    Tree finalName = elements.back();
    
    // Build the prefix path (all elements except the last) in correct order
    Tree pathPrefix = gGlobal->nil;
    for (size_t i = 0; i + 1 < elements.size(); i++) {
        pathPrefix = cons(elements[i], pathPrefix);
    }
    
    // Reverse pathPrefix to get correct top-down order
    Tree reversedPrefix = gGlobal->nil;
    while (!isNil(pathPrefix)) {
        reversedPrefix = cons(hd(pathPrefix), reversedPrefix);
        pathPrefix = tl(pathPrefix);
    }
    
    // Apply the prefix to current path (this handles .. and .)
    // concatPath resolves relative path elements (.., .) against the current path
    Tree adjustedPath = concatPath(reversedPrefix, currentPath);
    
    // Check if adjustedPath is a bare path marker (not a list)
    // This happens when ".." tries to go beyond the root of an empty path.
    // In this case, concatPath returns a single pathParent marker.
    // We wrap it in a list to maintain the path structure invariant.
    if (adjustedPath && !isNil(adjustedPath) && !isList(adjustedPath)) {
        // adjustedPath is a single marker (like pathParent), wrap it in a list
        adjustedPath = cons(adjustedPath, gGlobal->nil);
    }
    
    // Now add the final name with group type encoding
    if (isPathRoot(finalName) || isPathParent(finalName) || isPathCurrent(finalName)) {
        // This shouldn't normally happen (path ending in .. or .), but handle it
        return concatPath(cons(finalName, gGlobal->nil), adjustedPath);
    } else {
        // Encode the final name with the group type
        return cons(cons(tree(groupType), finalName), adjustedPath);
    }
}
