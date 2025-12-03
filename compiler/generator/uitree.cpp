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

#include "uitree.hh"
#include <algorithm>
#include <sstream>
#include <vector>
#include "exception.hh"
#include "global.hh"

using namespace std;

static Tree makeSubFolderChain(Tree path, Tree elem);
static Tree putFolder(Tree folder, Tree item);
static Tree getFolder(Tree folder, Tree ilabel);
static Tree sortPropList(Tree pl);
static Tree sortFolderTree(Tree t);

static void error(const char* s, Tree t)
{
    fprintf(stderr, "ERROR : %s (%p)\n", s, (void*)t);
}

#define FAUST_ERROR(s, t)        \
    {                            \
        error(s, t);             \
        throw faustexception(s); \
    }

//------------------------------------------------------------------------------
// Property list
//------------------------------------------------------------------------------
//
// Property lists are represented as a simple association list:
//   pl = [ (key1 . val1), (key2 . val2), ... ]
// where each element of the list is itself a cons(key, val).
// The basic operations below do *not* keep the list sorted; insertion is O(1).
// The final UI tree is sorted once in UITree::prepareUserInterfaceTree().

/**
 * Look up a value in a property list.
 * This is a simple linear search with no ordering assumption.
 */
static bool findKey(Tree pl, Tree key, Tree& val)
{
    for (Tree l = pl; !isNil(l); l = tl(l)) {
        Tree kv = hd(l);
        if (left(kv) == key) {
            val = right(kv);
            return true;
        }
    }
    return false;
}

/**
 * Update (or insert) a key in a property list.
 * If the key already exists, its value is replaced.
 * Otherwise a new (key, val) pair is added at the head of the list.
 */
static Tree updateKey(Tree pl, Tree key, Tree val)
{
    if (isNil(pl)) {
        // Key does not exist yet: create a one-element list.
        return cons(cons(key, val), gGlobal->nil);
    }
    if (left(hd(pl)) == key) {
        // Replace existing value for this key.
        return cons(cons(key, val), tl(pl));
    }
    // Keep current head and update in the tail.
    return cons(hd(pl), updateKey(tl(pl), key, val));
}

/**
 * Remove the first occurrence of a key from a property list.
 */
static Tree removeKey(Tree pl, Tree key)
{
    if (isNil(pl)) {
        return gGlobal->nil;
    }
    if (left(hd(pl)) == key) {
        // Drop the first matching element.
        return tl(pl);
    }
    // Keep current head and continue in the tail.
    return cons(hd(pl), removeKey(tl(pl), key));
}

/**
 * Insert a (key, val) pair without trying to keep the list sorted.
 * This keeps insertion O(1); the cost of sorting is paid once later
 * in UITree::prepareUserInterfaceTree().
 *
 * This is particularly important when building large folders: instead of
 * an O(n^2) cost for n sequential insertions in a sorted list, we get O(n)
 * for construction plus O(n log n) for a single sort at the end.
 */
static Tree addKey(Tree pl, Tree key, Tree val)
{
    return cons(cons(key, val), pl);
}

//------------------------------------------------------------------------------
// Sorting helpers
//------------------------------------------------------------------------------

/**
 * Experimental ordering predicate: arrange keys in alphabetical order
 * based on their label.
 *
 * Keys can be either:
 *   - directly a label symbol, or
 *   - a pair (type . label), in which case we compare on the label.
 */
static bool isBefore(Tree k1, Tree k2)
{
    // Before comparing replace (type . label) by label.
    if (isList(k1)) {
        k1 = tl(k1);
    }
    if (isList(k2)) {
        k2 = tl(k2);
    }

    Sym s1, s2;
    if (!isSym(k1->node(), &s1)) {
        FAUST_ERROR("the node of the tree is not a symbol", k1);
    }
    if (!isSym(k2->node(), &s2)) {
        FAUST_ERROR("the node of the tree is not a symbol", k2);
    }

    return strcmp(name(s1), name(s2)) < 0;
}

/**
 * Sort a property list by key using the isBefore() ordering.
 * Complexity: O(n log n) for a folder with n entries.
 */
static Tree sortPropList(Tree pl)
{
    std::vector<Tree> items;

    // Copy list elements into a temporary vector.
    for (Tree l = pl; !isNil(l); l = tl(l)) {
        items.push_back(hd(l));  // (key . val)
    }

    std::sort(items.begin(), items.end(),
              [](Tree a, Tree b) { return isBefore(left(a), left(b)); });

    // Rebuild a list in the sorted order.
    Tree res = gGlobal->nil;
    for (auto it = items.rbegin(); it != items.rend(); ++it) {
        res = cons(*it, res);
    }
    return res;
}

/**
 * Recursively sort the content of all UI folders.
 *
 * This keeps the external behaviour (alphabetically ordered UI)
 * while avoiding the cost of maintaining a sorted property list
 * on every insertion.
 */
static Tree sortFolderTree(Tree t)
{
    Tree label, elements;
    if (isUiFolder(t, label, elements)) {
        // First sort the property list at this level.
        Tree sortedElems = sortPropList(elements);

        // Then recursively sort subfolders.
        Tree newElemsRev = gGlobal->nil;
        for (Tree l = sortedElems; !isNil(l); l = tl(l)) {
            Tree kv      = hd(l);
            Tree k       = left(kv);
            Tree v       = right(kv);
            Tree sortedV = sortFolderTree(v);
            newElemsRev  = cons(cons(k, sortedV), newElemsRev);
        }

        // Reverse to restore forward order.
        Tree newElems = reverse(newElemsRev);
        return uiFolder(label, newElems);
    }

    // Non-folder nodes are left untouched.
    return t;
}

//-----------------------------------------------------
// Management of the user interface tree construction
//-----------------------------------------------------

Tree uiFolder(Tree label, Tree elements)
{
    return tree(gGlobal->UIFOLDER, label, elements);
}
bool isUiFolder(Tree t)
{
    return isTree(t, gGlobal->UIFOLDER);
}
bool isUiFolder(Tree t, Tree& label, Tree& elements)
{
    return isTree(t, gGlobal->UIFOLDER, label, elements);
}

Tree uiWidget(Tree label, Tree varname, Tree sig)
{
    return tree(gGlobal->UIWIDGET, label, varname, sig);
}
bool isUiWidget(Tree t, Tree& label, Tree& varname, Tree& sig)
{
    return isTree(t, gGlobal->UIWIDGET, label, varname, sig);
}

// places an item in a folder. Eventually replaces the element with the same name.
Tree putFolder(Tree folder, Tree item)
{
    Tree label, content;

    if (!isUiFolder(folder, label, content)) {
        fprintf(stderr, "ERROR in addFolder : not a folder\n");
    }
    return uiFolder(label, updateKey(content, uiLabel(item), item));
}

// places an item in a folder. Without replacement
Tree addToFolder(Tree folder, Tree item)
{
    Tree label, content;

    if (!isUiFolder(folder, label, content)) {
        fprintf(stderr, "ERROR in addFolder : not a folder\n");
    }
    return uiFolder(label, addKey(content, uiLabel(item), item));
}

// get an item from a folder (or return NIL)
Tree getFolder(Tree folder, Tree ilabel)
{
    Tree flabel, content, item;
    if (!isUiFolder(folder, flabel, content)) {
        fprintf(stderr, "ERROR in getFolder : not a folder\n");
    }
    if (findKey(content, ilabel, item)) {
        return item;
    } else {
        return gGlobal->nil;
    }
}

// creates a string of folders corresponding to path and containing in fine elem
Tree makeSubFolderChain(Tree path, Tree elem)
{
    if (isNil(path)) {
        return elem;
    } else {
        return putFolder(uiFolder(hd(path), gGlobal->nil), makeSubFolderChain(tl(path), elem));
    }
}

Tree putSubFolder(Tree folder, Tree path, Tree item)
{
    if (isNil(path)) {
        // return putFolder(folder, item);
        return addToFolder(folder, item);
    } else {
        Tree subfolder = getFolder(folder, hd(path));
        if (isUiFolder(subfolder)) {
            return putFolder(folder, putSubFolder(subfolder, tl(path), item));
        } else {
            return putFolder(folder, makeSubFolderChain(path, item));
        }
    }
}

/*
 How folders work.
 Folder at 1 level : a folder contains a list of things identified by a name:
 Folder[(l1,d1)...(ln,dn)]
 where (lx,dx) is a thing dx identified by a name lx. We assume that the lx are all different.

 You can add a thing to a folder: Add(Folder, Thing) -> Folder

 If the folder already contains something with the same name, this thing is replaced by the new one.

 ADD (Folder[(l1,d1)...(ln,dn)], (lx,dx)) -> Folder[(l1,d1)...(lx,dx)...(ln,dn)]

 ADD (Folder[(l1,d1)...(lx,dx)...(ln,dn)], (lx,dx')) -> Folder[(l1,d1)...(lx,dx')...(ln,dn)]
 */

string checkNullLabel(Tree t, const string& label)
{
    return (label == "") ? string("0x00") : label;
}

string checkNullBargraphLabel(Tree t, const string& label, int direction)
{
    return (label == "") ? gGlobal->getFreshID((direction == 0) ? "hbargraph" : "vbargraph")
                         : label;
}

/**
 * Add a widget with a certain path to the user interface tree
 */
void UITree::addUIWidget(Tree path, Tree widget)
{
    fUIRoot = putSubFolder(fUIRoot, path, widget);
}

/**
 * Remove fake root folder if not needed (that is if the UI
 * is completely enclosed in one folder), then sort the full tree once.
 */
Tree UITree::prepareUserInterfaceTree()
{
    // Start from the current root.
    Tree root, elems;
    Tree ui = fUIRoot;

    // Remove fake root folder if not needed.
    if (isUiFolder(fUIRoot, root, elems) && isList(elems) && isNil(tl(elems))) {
        Tree folder = right(hd(elems));
        if (isUiFolder(folder)) {
            ui = folder;
        }
    }

    // Sort all folders by key labels. This keeps alphabetical ordering of the
    // UI while avoiding the O(n^2) cost of maintaining sorted property lists
    // during construction.
    return sortFolderTree(ui);
}
