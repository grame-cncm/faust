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
 
#include <sstream>
#include "uitree.hh"
#include "exception.hh"
#include "global.hh"

static Tree makeSubFolderChain(Tree path, Tree elem);
static Tree putFolder(Tree folder, Tree item);
static Tree getFolder (Tree folder, Tree ilabel);

static void error(const char * s, Tree t)
{
	fprintf(stderr, "ERROR : %s (%p)\n", s, (void*)t);
}

#define FAUST_ERROR(s,t) { error(s,t); throw faustexception(s); }

//------------------------------------------------------------------------------
// Property list
//------------------------------------------------------------------------------

#if 0
// version normale, qui marche, mais qui ne range pas en ordre alphabetique
static bool findKey (Tree pl, Tree key, Tree& val)
{
	if (isNil(pl)) 				return false;
	if (left(hd(pl)) == key) 	{ val= right(hd(pl)); return true; }
	/*  left(hd(pl)) != key	*/	return findKey (tl(pl), key, val); 
}

static Tree updateKey (Tree pl, Tree key, Tree val)
{
	if (isNil(pl)) 				return cons ( cons(key,val), gGlobal->nil );
	if (left(hd(pl)) == key) 	return cons ( cons(key,val), tl(pl) );
	/*  left(hd(pl)) != key	*/	return cons ( hd(pl), updateKey( tl(pl), key, val ));
}

static Tree removeKey (Tree pl, Tree key)
{
	if (isNil(pl)) 				return gGlobal->nil;
	if (left(hd(pl)) == key) 	return tl(pl);
	/*  left(hd(pl)) != key	*/	return cons (hd(pl), removeKey(tl(pl), key));
}

#else

// verion experimentale qui range en ordre alphabetique

static bool isBefore(Tree k1, Tree k2) 
{ 
	// before comparing replace (type . label) by label
	if (isList(k1)) { k1 = tl(k1); }
	if (isList(k2)) { k2 = tl(k2); }
	
	//fprintf(stderr, "isBefore("); print(k1, stderr); fprintf(stderr,", "); print(k2, stderr); fprintf(stderr,")\n"); 
	Sym s1, s2;
	if (!isSym(k1->node(), &s1)) {
		FAUST_ERROR("the node of the tree is not a symbol", k1);
	}
	if (!isSym(k2->node(), &s2)) {
		FAUST_ERROR("the node of the tree is not a symbol", k2);
	}
	
	//fprintf (stderr, "strcmp(\"%s\", \"%s\") = %d\n", name(s1), name(s2), strcmp(name(s1), name(s2)));
	return strcmp(name(s1), name(s2)) < 0;
}

static bool findKey (Tree pl, Tree key, Tree& val)
{
	if (isNil(pl)) 					return false;
	if (left(hd(pl)) == key) 		{ val = right(hd(pl)); return true; }
	if (isBefore(left(hd(pl)),key))	return findKey (tl(pl), key, val); 
	return false;
}

static Tree updateKey (Tree pl, Tree key, Tree val)
{
    if (isNil(pl))                  return cons ( cons(key,val), gGlobal->nil );
    if (left(hd(pl)) == key)        return cons ( cons(key,val), tl(pl) );
    if (isBefore(left(hd(pl)),key)) return cons ( hd(pl), updateKey( tl(pl), key, val ));
    return cons(cons(key,val), pl);
}

/**
 * Like updateKey but allow multiple items with same key
 */
static Tree addKey (Tree pl, Tree key, Tree val)
{
    if (isNil(pl))                  return cons ( cons(key,val), gGlobal->nil );
    if (isBefore(key, left(hd(pl)))) return cons(cons(key,val), pl);
    return cons ( hd(pl), addKey( tl(pl), key, val ));
}

#if 0
static Tree removeKey (Tree pl, Tree key)
{
	if (isNil(pl)) 					return gGlobal->nil;
	if (left(hd(pl)) == key) 		return tl(pl);
	if (isBefore(left(hd(pl)),key))	return cons (hd(pl), removeKey(tl(pl), key));
	return pl;
}
#endif
#endif

//------------------------------------------------------------------------------
// gestion de la construction de l'arbre d'interface utilisateur
//------------------------------------------------------------------------------

Tree  	uiFolder(Tree label, Tree elements)				{ return tree(gGlobal->UIFOLDER, label, elements); 		}
bool  	isUiFolder(Tree t)								{ return isTree(t, gGlobal->UIFOLDER); 					}
bool  	isUiFolder(Tree t, Tree& label, Tree& elements)	{ return isTree(t, gGlobal->UIFOLDER, label, elements); 	}

Tree 	uiWidget(Tree label, Tree varname, Tree sig) 					{ return tree(gGlobal->UIWIDGET, label, varname, sig); }
bool 	isUiWidget(Tree t, Tree& label, Tree& varname, Tree& sig)		{ return isTree(t, gGlobal->UIWIDGET, label, varname, sig); }

// place un item dans un folder. Remplace eventuellement l'élément de même nom.
Tree putFolder(Tree folder, Tree item)
{
    Tree    label, content;
    
    if ( ! isUiFolder(folder, label, content)) { fprintf(stderr, "ERROR in addFolder : not a folder\n"); }
    return uiFolder(label, updateKey(content, uiLabel(item), item));
}

// place un item dans un folder. Sans Remplacement
Tree addToFolder(Tree folder, Tree item)
{
    Tree    label, content;
    
    if ( ! isUiFolder(folder, label, content)) { fprintf(stderr, "ERROR in addFolder : not a folder\n"); }
    return uiFolder(label, addKey(content, uiLabel(item), item));
}

// get an item from a folder (or return NIL)
Tree getFolder (Tree folder, Tree ilabel)
{
	Tree	flabel, content, item;
	if (!isUiFolder(folder, flabel, content)) 	{ fprintf(stderr, "ERROR in getFolder : not a folder\n"); }
	if (findKey(content, ilabel, item)) {
		return item;
	} else {
		return gGlobal->nil;
	}
}
	
// crée une chaine de dossiers correspondant à path et contenant in fine elem
Tree makeSubFolderChain(Tree path, Tree elem)
{
	if (isNil(path)) {
		return elem;
	} else {
		return putFolder(uiFolder(hd(path), gGlobal->nil), makeSubFolderChain(tl(path),elem));
	}
} 
	
Tree putSubFolder(Tree folder, Tree path, Tree item) 
{
	if (isNil(path)) {
        //return putFolder(folder, item);
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
Fonctionnement des dossiers. 
Dossier a 1 niveau : Un dossier contient une liste de choses reperees par un nom :
	Dossier[(l1,d1)...(ln,dn)] 
ou (lx,dx) est une chose dx reperee par un nom lx. On suppose les lx tous differents

On peut ajouter une chose a un dossier : Ajouter(Dossier, Chose) -> Dossier

Si le dossier contient deja qq chose de meme nom, cette chose est remplacee par la nouvelle.

AJOUTER (Dossier[(l1,d1)...(ln,dn)], (lx,dx)) -> Dossier[(l1,d1)...(lx,dx)...(ln,dn)]

AJOUTER (Dossier[(l1,d1)...(lx,dx)...(ln,dn)], (lx,dx')) -> Dossier[(l1,d1)...(lx,dx')...(ln,dn)]
*/


// Handle empty labels in a consistent way
string ptrToHex(Tree ptr)
{
    stringstream res; res << hex << ptr; return res.str();
}

string checkNullLabel(Tree t, const string& label, bool bargraph)
{
    return (label == "") ? (bargraph ? ptrToHex(t) : string("0x00")) : label;
}
