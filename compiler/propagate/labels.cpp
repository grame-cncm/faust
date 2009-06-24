#include "labels.hh"

//=========================== PATHNAME ===============================

/**
 * Grammar for labels with pathnames
 *-----------------------------------
 * label = name | dir name
 * name = [^/]+ | ".." | "." (need to take into account also properties)
 * dir = adir | rdir
 * adir = '/' | '/' rdir
 * rdir = (name '/')+
 *
 */

Sym PATHROOT = symbol ("/");
Tree pathRoot()						{ return tree(PATHROOT); }
bool isPathRoot(Tree t)				{ return isTree(t, PATHROOT); }

Sym PATHPARENT = symbol ("..");
Tree pathParent()					{ return tree(PATHPARENT); }
bool isPathParent(Tree t)			{ return isTree(t, PATHPARENT); }

Sym PATHCURRENT = symbol (".");
Tree pathCurrent()					{ return tree(PATHCURRENT); }
bool isPathCurrent(Tree t)			{ return isTree(t, PATHCURRENT); }



/**
 * analyze name for "H:name" | "V:name" etc
 */
 
static Tree encodeName(const string& name)
{
	if (name.size()>2) {
		if (name[1] == ':') {
			switch (name[0]) {
				case 'v': 
				case 'V': return cons(tree(0), tree(name.substr(2)));
				
				case 'h': 
				case 'H': return cons(tree(1), tree(name.substr(2)));
				
				case 't': 
				case 'T': return cons(tree(2), tree(name.substr(2)));
				
				default : return tree(name);
			}
		} else {
			return tree(name);
		}
	} else {
		return tree(name);
	}
}
				

/**
 * Analyzes a label and converts it as a path
 */
 
static Tree label2path(const char* label)
{
	cout << "label2path of " << label << endl;
	int i = 0;
	if (label[i] == 0) return nil;
	if (label[i] == '/') return cons(pathRoot(), label2path(&label[i+1]));
	else {
		string name;
		while ((label[i] != 0) && (label[i] != '/')) {
			name.push_back(label[i]);
			i++;
		}
		if (label[i] == '/') i++;
		return cons(encodeName(name), label2path(&label[i]));
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
			return concatPath(tl(relpath), nil);
		} else if (isPathParent(head)) {
			assert (isList(abspath));
			return concatPath(tl(relpath), tl(abspath));
		} else if (isPathCurrent(head)) {
			return concatPath(tl(relpath), abspath);
		} else {
			return concatPath(tl(relpath), cons(head,abspath));
		}
	} else {
		assert(isNil(relpath));
		return abspath;
	}
}


static Tree normalizeLabel(Tree label, Tree path)
{
	// we suppose label = "../label" ou "name/label" ou "name"	
	//cout << "Normalize Label " << *label << endl;
	if (isList(label)) {
		return cons(label, path);
	} else {
		Sym s;
		assert (isSym(label->node(),&s));
		return concatPath(label2path(name(s)),path);
	}
}

Tree normalizePath(Tree path)
{
	//cout << "Normalize Path : " << *path << endl;
	Tree npath;
	if (isNil(path)) npath = path;
	else npath = normalizeLabel(hd(path), normalizePath(tl(path)));	
	//cout << "              -> " << *npath << endl;
	return npath;
}

