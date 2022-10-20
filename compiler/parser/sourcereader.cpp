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

/*
 sourcereader : Faust source file reader
 This component is in charge of mapping filenames to
 the list of Faust definitions they contain.
*/

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <sstream>

#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef EMCC
#include <emscripten.h>
#endif

#include "compatibility.hh"
#include "sourcereader.hh"
#include "sourcefetcher.hh"
#include "enrobage.hh"
#include "ppbox.hh"
#include "exception.hh"
#include "global.hh"
#include "Text.hh"

using namespace std;

/****************************************************************
 Parser variables
 *****************************************************************/

int yyparse();
int yylex_destroy(void);
void yyrestart(FILE* new_file);
struct yy_buffer_state* yy_scan_string(const char *yy_str); // In principle YY_BUFFER_STATE

int yyerr;
extern int yydebug;
extern FILE* yyin;
extern int yylineno;
extern const char* yyfilename;

/**
 * Checks an argument list for containing only
 * standard identifiers, no patterns and
 * is linear.
 * @param args the argument list to check
 * @return true if it contains only identifiers
 */

static bool standardArgList(Tree args)
{
	map<Tree,int> L;
	while (isList(args)) {
		if (!isBoxIdent(hd(args))) return false;
		if (++L[hd(args)] > 1) return false;
		args = tl(args);
	}
	return true;
}

static string printPatternError(Tree symbol, Tree lhs1, Tree rhs1, Tree lhs2, Tree rhs2)
{
    stringstream error;

    if (!symbol) {
        error << "ERROR : inconsistent number of parameters in pattern-matching rule: "
        << boxpp(reverse(lhs2)) << " => " << boxpp(rhs2) << ";"
        << " previous rule was: "
        << boxpp(reverse(lhs1)) << " => " << boxpp(rhs1) << ";"
        << endl;
    } else {
        error << "ERROR (file " << yyfilename << ":" << yylineno << ") : in the definition of " << boxpp(symbol) << endl
        << "Inconsistent number of parameters in pattern-matching rule: "
        << boxpp(reverse(lhs2)) << " => " << boxpp(rhs2) << ";"
        << " previous rule was: "
        << boxpp(reverse(lhs1)) << " => " << boxpp(rhs1) << ";"
        << endl;
    }

    return error.str();
}

static string printRedefinitionError(Tree symbol, list<Tree>& variants)
{
    stringstream error;

    error << "ERROR (file " << yyfilename << ":" << yylineno << ") : multiple definitions of symbol " << boxpp(symbol) << endl;
    for (const auto& p : variants) {
        Tree params = hd(p);
        Tree body = tl(p);
        if (isNil(params)) {
            error << boxpp(symbol) << " = " << boxpp(body) << ";" << endl;
        } else {
            error << boxpp(symbol) << boxpp(params) << " = " << boxpp(body) << ";" << endl;
        }
    }

    return error.str();
}

/**
 * Transforms a list of variants (arglist.body)
 * into an abstraction or a boxCase.
 * @param symbol name only used in case of error
 * @param variants list of variants (arglist.body)
 * @return the corresponding box expression
 */

static Tree makeDefinition(Tree symbol, list<Tree>& variants)
{
	if (variants.size() == 1) {
		Tree rhs = *(variants.begin());
		Tree args = hd(rhs);
		Tree body = tl(rhs);

		if (isNil(args)) {
			return body;
		} else if (standardArgList(args)) {
			return buildBoxAbstr(args, body);
		} else {
			return boxCase(cons(rhs,gGlobal->nil));
		}
	} else {
		Tree l = gGlobal->nil;
		Tree prev = *variants.begin();
		int npat = len(hd(prev));

        if (npat == 0) {
            throw faustexception(printRedefinitionError(symbol, variants));
        }

		for (const auto& p : variants) {
			Tree cur = p;
			if ((npat == 0) || (npat != len(hd(cur)))) {
                throw faustexception(printPatternError(symbol, hd(prev), tl(prev), hd(cur), tl(cur)));
			}
			prev = cur;
			l = cons(p,l);
		}
		return boxCase(l);
	}
}

// Add function metadata (using a boxMetadata construction) to a list of definitions
static Tree addFunctionMetadata(Tree ldef, FunMDSet& M)
{
    Tree lresult = gGlobal->nil; // the transformed list of definitions

    // for each definition def of ldef
    for (; !isNil(ldef); ldef = tl(ldef)) {
        Tree def = hd(ldef);
        Tree fname;
        if (isNil(def)) {
            // skip null definitions produced by declarations
        } else if (isImportFile(def, fname)) {
            lresult = cons(def, lresult);
        } else {
            Tree foo = hd(def);
            Tree exp = tl(def);
            for (const auto& m : M[foo]) {
                exp = boxMetadata(exp, m);
            }
            lresult = cons(cons(foo,exp), lresult);
        }
    }
    return lresult;
}

void SourceReader::checkName()
{
    if (gGlobal->gMasterDocument == yyfilename) {
        Tree name = tree("name");
        if (gGlobal->gMetaDataSet.find(name) == gGlobal->gMetaDataSet.end()) {
            gGlobal->gMetaDataSet[name].insert(tree(quote(stripEnd(basename((char*)yyfilename), ".dsp"))));
        }
        gGlobal->gMetaDataSet[tree("filename")].insert(tree(quote(basename((char*)yyfilename))));
    }
}

/**
 * Parse a single Faust source file, returns the list of
 * definitions it contains.
 *
 * @param fname the name of the file to parse
 * @return the list of definitions it contains
 */

inline bool isURL(const char* name) { return (strstr(name, "http://") != 0) || (strstr(name, "https://") != 0); }
inline bool isFILE(const char* name) { return strstr(name, "file://") != 0; }

Tree SourceReader::parseFile(const char* fname)
{
    yyerr = 0;
    yylineno = 1;
    yyfilename = fname;
 
    // We are requested to parse an URL file
    if (isURL(yyfilename)) {
        char* buffer = nullptr;
    #ifdef EMCC
        // Call JS code to load URL
        buffer = (char*)EM_ASM_INT({
            var dsp_code = "";
            try {
                var xmlhttp = new XMLHttpRequest();
                xmlhttp.open("GET", Module.UTF8ToString($0), false);
                xmlhttp.send();
                if (xmlhttp.status == 200) {
                    dsp_code = xmlhttp.responseText;
                }
            } catch(e) {
                console.log(e);
            }
            return allocate(intArrayFromString(dsp_code), 'i8', ALLOC_STACK);
        }, yyfilename);

        Tree res = nullptr;
        if (strlen(buffer) == 0) {
            stringstream error;
            error << "ERROR : unable to access URL '" << fname << "'" << endl;
            throw faustexception(error.str());
        } else {
            yy_scan_string(buffer);
            res = parseLocal(yyfilename);
        }
    #else
        // Otherwise use http URL fetch code
        if (http_fetch(yyfilename, &buffer) == -1) {
            stringstream error;
            error << "ERROR : unable to access URL '" << fname << "' : " << http_strerror() << endl;
            throw faustexception(error.str());
        }
        yy_scan_string(buffer);
        Tree res = parseLocal(yyfilename);
        // 'http_fetch' result must be deallocated
        free(buffer);
    #endif
        return res;

    } else {

        // Test for local url
        if (isFILE(yyfilename)) {
            yyfilename = &yyfilename[7]; // skip 'file://'
        }
        
        // Try to open local file
        string fullpath1;
        FILE* tmp_file = yyin = fopenSearch(yyfilename, fullpath1); // Keep file to properly close it
        if (yyin) {
            Tree res = parseLocal(fullpath1.c_str());
            fclose(tmp_file);
            return res;
        } else {
        #ifdef EMCC
            // Try to open with the complete URL
            Tree res = nullptr;
            for (size_t i = 0; i < gGlobal->gImportDirList.size(); i++) {
                if (isURL(gGlobal->gImportDirList[i].c_str())) {
                    // Keep the created filename in the global state, so that the 'yyfilename'
                    // global variable always points to a valid string
                    gGlobal->gImportFilename = gGlobal->gImportDirList[i] + fname;
                    if ((res = parseFile(gGlobal->gImportFilename.c_str()))) return res;
                }
            }
        #endif
            stringstream error;
            error << "ERROR : unable to open file " << yyfilename << endl;
            throw faustexception(error.str());
        }
    }
}

Tree SourceReader::parseString(const char* fname)
{
    yyerr = 0;
    yylineno = 1;
    yyfilename = fname;
    yy_scan_string(gGlobal->gInputString.c_str());

    // Clear global "inputstring" so that imported files will be correctly parsed with "parse"
    gGlobal->gInputString = "";
    return parseLocal(fname);
}

Tree SourceReader::parseLocal(const char* fname)
{
    int r = yyparse();
    stringstream error;

    if (r) {
        error << "ERROR : parse code = " << r << endl;
        throw faustexception(error.str());
    }
    if (yyerr > 0) {
        error << "ERROR : parse code = " << yyerr << endl;
        throw faustexception(error.str());
    }

    yylex_destroy();

    // We have parsed a valid file
    checkName();
    fFilePathnames.push_back(fname);
    return gGlobal->gResult;
}

/**
 * Check if a file as been read and is in the "cache"
 *
 * @param fname the name of the file to check
 * @return true if the file is in the cache
 */

bool SourceReader::cached(string fname)
{
	return fFileCache.find(fname) != fFileCache.end();
}

/**
 * Return the list of definitions file contains. Cache the result.
 *
 * @param fname the name of the file to check
 * @return the list of definitions it contains
 */

Tree SourceReader::getList(const char* fname)
{
	if (!cached(fname)) {
        // Previous metadata need to be cleared before parsing a file
        gGlobal->gFunMDSet.clear();
        Tree ldef = (gGlobal->gInputString != "") ? parseString(fname) : parseFile(fname);
        // Definitions with metadata have to be wrapped into a boxMetadata construction
        fFileCache[fname] = addFunctionMetadata(ldef, gGlobal->gFunMDSet);
	}
    return fFileCache[fname];
}

/**
 * Return a vector of pathnames representing the list
 * of all the source files that have been required
 * to evaluate process (those in fFileCache)
 */

vector<string> SourceReader::listSrcFiles()
{
    return fFilePathnames;
}

/**
 * Return a vector of pathnames representing the list
 * of all the source files that have been required
 * to evaluate process, without the DSP file itself
 */

vector<string> SourceReader::listLibraryFiles()
{
    vector<string> tmp = fFilePathnames;
    if (tmp.size() > 0) tmp.erase(tmp.begin());
    return tmp;
}

/**
 * Return the list of definitions where all imports have been expanded.
 *
 * @param ldef the list of definitions to expand
 * @return the expanded list of definitions
 */

Tree SourceReader::expandList(Tree ldef)
{
	set<string> visited;
	return expandRec(ldef, visited, gGlobal->nil);
}

Tree SourceReader::expandRec(Tree ldef, set<string>& visited, Tree lresult)
{
	for (;!isNil(ldef); ldef = tl(ldef)) {
		Tree d = hd(ldef);
		Tree fname;
		if (isNil(d)) {
			// skill null definitions produced by declarations
		} else if (isImportFile(d, fname)) {
			const char* f = tree2str(fname);
			if (visited.find(f) == visited.end()) {
				visited.insert(f);
				lresult = expandRec(getList(f), visited, lresult);
			}
		} else {
			lresult = cons(d, lresult);
		}
	}
	return lresult;
}

// =================
// Public functions
// =================

/**
 * Formats a list of raw definitions represented by triplets
 * <name, arglist, body> into abstractions or pattern
 * matching rules when appropriate.
 *
 * @param rldef list of raw definitions in reverse order
 * @return the list of formatted definitions
 */

Tree formatDefinitions(Tree rldef)
{
    map<Tree, list<Tree> > dic;
    map<Tree, list<Tree> >::iterator p;
    Tree ldef2 = gGlobal->nil;
    Tree file;

    // Collects the definitions in a dictionnary
    while (!isNil(rldef)) {
        Tree def = hd(rldef);
        rldef = tl(rldef);
        if (isImportFile(def, file)) {
            ldef2 = cons(def,ldef2);
        } else if (!isNil(def)) {
            //cout << " def : " << *def << endl;
            dic[hd(def)].push_front(tl(def));
        }
    }

    // Produces the definitions
    for (p = dic.begin(); p != dic.end(); p++) {
        ldef2 = cons(cons(p->first, makeDefinition(p->first, p->second)), ldef2);
    }

    return ldef2;
}

Tree checkRulelist(Tree lr)
{
    Tree lrules = lr;
    if (isNil(lrules)) {
        stringstream error;
        error << "ERROR (file " << yyfilename << ":" << yylineno << ") : a case expression can't be empty" << endl;
        throw faustexception(error.str());
    }
    // first pattern used as a reference
    Tree lhs1 = hd(hd(lrules));
    Tree rhs1 = tl(hd(lrules));
    int npat = len(lhs1);
    lrules = tl(lrules);
    while (!isNil(lrules)) {
        Tree lhs2 = hd(hd(lrules));
        Tree rhs2 = tl(hd(lrules));
        if (npat != len(lhs2)) {
            throw faustexception(printPatternError(nullptr, lhs1, rhs1, lhs2, rhs2));
        }
        lhs1 = lhs2;
        rhs1 = rhs2;
        lrules = tl(lrules);
    }
    return lr;
}

void declareMetadata(Tree key, Tree value)
{
    if (gGlobal->gMasterDocument == yyfilename) {
        // Inside master document, no prefix needed to declare metadata
        gGlobal->gMetaDataSet[key].insert(value);
    } else {
        string fkey(yyfilename);
        if (fkey != "") {
            fkey += "/";
        }
        fkey += tree2str(key);
        gGlobal->gMetaDataSet[tree(fkey.c_str())].insert(value);
    }
}

/*
fun -> (file*fun -> {key*value,...})

gGlobal->gFunMetaDataSet[fun].insert(file*fun*key*value);
gFunMetaDataSet = map<tree, tuple<Tree,Tree,Tree,Tree>>
*/

// Called by parser to create function's metadata
void declareDefinitionMetadata(Tree id, Tree key, Tree value)
{
    stringstream fullkeystream;
    fullkeystream << yyfilename << "/" << tree2str(id) << ":" << tree2str(key);
    string fullkey = fullkeystream.str();
    Tree md = cons(tree(fullkey), value);
    //cout << "Creation of a function metadata : " << *md << endl;
    gGlobal->gFunMDSet[boxIdent(tree2str(id))].insert(md);
}

void declareDoc(Tree t)
{
	gGlobal->gDocVector.push_back(t);
}
