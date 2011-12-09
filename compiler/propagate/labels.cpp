#include "labels.hh"
#include "compatibility.hh"

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
        return cons(tree(""), nil);

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
        return cons(tree(label),nil);
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
		assert(isNil(relpath));
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
		assert (isSym(label->node(),&s));
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

