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


/*
 sourcereader : Faust source file reader
 
 This component is in charge of mapping filenames to 
 the list of faust definitions they contain.
 
 */
#include <iostream>
#include <map>
#include <list>
#include <string>
#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef EMCC 
#include <emscripten.h>
#endif

#include "sourcereader.hh"
#include "sourcefetcher.hh"
#include "enrobage.hh"
#include "ppbox.hh"
#include "exception.hh"
#include "global.hh"

using namespace std;

int yylex_destroy(void);
void yyrestart(FILE *new_file);

/****************************************************************
 Parser variables
 *****************************************************************/

int yyparse();
struct yy_buffer_state* yy_scan_string (const char *yy_str); // In principle YY_BUFFER_STATE

extern int 		yyerr;
extern int 		yydebug;
extern FILE*	yyin;
extern int		yylineno;
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
	map<Tree,int>	L;
	while (isList(args)) {
		if (!isBoxIdent(hd(args))) return false;
		if (++L[hd(args)] > 1) return false;
		args = tl(args);
	}
	return true;
}

static string printPatternError(Tree lhs1, Tree rhs1, Tree lhs2, Tree rhs2)
{
    stringstream error;
	error 	<< "ERROR : inconsistent number of parameters in pattern-matching rule: "
    << boxpp(reverse(lhs2)) << " => " << boxpp(rhs2) << ";"
    << " previous rule was: " 
    << boxpp(reverse(lhs1)) << " => " << boxpp(rhs1) << ";"
    << endl;
    
    return error.str();
}

Tree checkRulelist (Tree lr)
{
	Tree lrules = lr;
	if (isNil(lrules)) { 
        throw faustexception("ERROR : a case expression can't be empty\n");
    }
	// first pattern used as a reference
	Tree lhs1 = hd(hd(lrules));
	Tree rhs1 = tl(hd(lrules));
	int npat = len(lhs1); 
	lrules = tl(lrules);
	while (! isNil(lrules)) {
		Tree lhs2 = hd(hd(lrules));
		Tree rhs2 = tl(hd(lrules));
		if (npat != len(lhs2)) {
            throw faustexception(printPatternError(lhs1,rhs1,lhs2,rhs2));
		}
		
		lhs1 = lhs2;
		rhs1 = rhs2;
		lrules = tl(lrules);
	}	
	return lr;
}

/**
 * Transforms a list of variants (arglist.body) 
 * into an abstraction or a boxCase.
 * @param variants list of variants (arglist.body)
 * @return the corresponding box expression 
 */
static Tree makeDefinition(list<Tree>& variants)
{
	if (variants.size() == 1) {
		Tree rhs = *(variants.begin());
		Tree args= hd(rhs);
		Tree body= tl(rhs);
		
		if (isNil(args)) {
			return body;
		} else if (standardArgList(args)) {
			return buildBoxAbstr(args, body);
		} else {
			return boxCase(cons(rhs,gGlobal->nil));
		}
	} else {
		list<Tree>::iterator p;
		Tree	l = gGlobal->nil;
		Tree	prev = *variants.begin();
		int 	npat = len(hd(prev));
		for (p=variants.begin(); p!=variants.end(); p++) {
			Tree cur = *p;
			if (npat != len(hd(cur))) {
                throw faustexception(printPatternError(hd(prev), tl(prev), hd(cur), tl(cur)));
			}
			prev = cur;
			l = cons(*p,l);
		}
		return boxCase(l);
	}
}

/**
 * Formats a list of raw definitions represented by triplets
 * <name,arglist,body> into abstractions or pattern 
 * matching rules when appropriate.
 * 
 * @param rldef list of raw definitions in reverse order
 * @return the list of formatted definitions
 */
Tree formatDefinitions(Tree rldef)
{
	map<Tree,list<Tree> > dic;
	map<Tree,list<Tree> >::iterator p;
	Tree ldef2 = gGlobal->nil;
	Tree file;
	
	//cout << "Format definitions " << *rldef << endl;
	// collects the definitions in a dictionnary
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
	
	// produce the definitions
	
	for (p=dic.begin(); p!=dic.end(); p++) {
		ldef2 = cons (cons(p->first, makeDefinition(p->second)), ldef2);
	}
	
	//cout << "list of definitions : " << *ldef2 << endl;
	return ldef2;
}

/**
 * Parse a single faust source file. returns the list of
 * definitions it contains.
 * 
 * @param fname the name of the file to parse
 * @return the list of definitions it contains
 */
Tree SourceReader::parsefile(string fname)
{
    yyerr = 0;
    yylineno = 1;
    yyfilename = fname.c_str();
    string fullpath;
 
    // We are requested to parse an URL file
    if (strstr(yyfilename,"http://") != 0) {
        char* buffer = 0;
    #ifdef EMCC
        // Call JS code to load URL
        buffer = (char*)EM_ASM_INT({
            var xmlhttp = new XMLHttpRequest();
            var dsp_code = "";
            xmlhttp.open("GET", Module.Pointer_stringify($0), false);
            xmlhttp.send();
            if (xmlhttp.status == 200) {
                dsp_code = xmlhttp.responseText;
            } 
            return allocate(intArrayFromString(dsp_code), 'i8', ALLOC_STACK);
        }, yyfilename);
        
        Tree res = 0;
        if (strlen(buffer) == 0) {
            stringstream error;
            error << "ERROR : unable to access URL '" << fname << "' : " << endl;
            throw faustexception(error.str());
        } else {
            yy_scan_string(buffer);
            res = parse(yyfilename);
        }
    #else
        // Otherwise use http URL fetch code
        if (http_fetch(yyfilename, &buffer) == -1) {
            stringstream error;
            error << "ERROR : unable to access URL '" << fname << "' : " << http_strerror() << endl;
            throw faustexception(error.str());
        }
        yy_scan_string(buffer);
        Tree res = parse(yyfilename);
        // 'http_fetch' result must be deallocated
        free(buffer);
    #endif
        return res;

    } else {
        
        // Test for local url
		if (strstr(yyfilename,"file://") != 0) {
			yyfilename  = &yyfilename[7]; // skip 'file://'
		}
        
    #ifdef EMCC
        // Try to open with the complete URL
        Tree res = 0;
        for (list<string>::iterator i = gGlobal->gImportDirList.begin(); i != gGlobal->gImportDirList.end(); i++) {
            string url = *i + fname;
            if ((res = parsefile(url))) return res;
        }
        stringstream error;
        error << "ERROR : unable to open file " << yyfilename << endl;
        throw faustexception(error.str());
    #else
        string fullpath;
        FILE* tmp_file = yyin = fopensearch(yyfilename, fullpath); // Keep file to properly close it
        if (yyin == NULL) {
            stringstream error;
            error << "ERROR : unable to open file " << yyfilename << endl;
            throw faustexception(error.str());
        }
        Tree res = parse(fullpath);
        fclose(tmp_file);
        return res;
    #endif
    }
}

Tree SourceReader::parsestring(string fname) 
{
    yyerr = 0;
    yylineno = 1;
    yyfilename = fname.c_str();
    
    yy_scan_string(gGlobal->gInputString);
    // Clear global "inputstring" so that imported files will be correctly parsed with "parse"
    gGlobal->gInputString = NULL;
    return parse(fname);
}

Tree SourceReader::parse(string fname) 
{
    int r = yyparse();
    stringstream error;
    
 	if (r) { 
        error << "Parse error : code = " << r << endl;
        throw faustexception(error.str());
	}
	if (yyerr > 0) {
        error << "ERROR : parse, code = " << yyerr << endl;
        throw faustexception(error.str());
	}
    
    yylex_destroy();
    
	// we have parsed a valid file
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

Tree SourceReader::getlist(string fname)
{
	if (!cached(fname)) {
        if (gGlobal->gInputString) {
            fFileCache[fname] = parsestring(fname);
        } else {
            fFileCache[fname] = parsefile(fname);
        }
	}
    if (fFileCache[fname] == 0) {
        throw faustexception("getlist");
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
    //	vector<string> 						srcfiles;
    
    //	for (map<string, Tree>::const_iterator p = fFileCache.begin(); p != fFileCache.end(); p++) {
    //		srcfiles.push_back(p->first);
    //	}
    
    //	return srcfiles;	
	return fFilePathnames;
}

/**
 * Return the list of definitions where all imports have been expanded.
 * 
 * @param ldef the list of definitions to expand
 * @return the expanded list of definitions
 */

Tree SourceReader::expandlist(Tree ldef)
{
	set<string> visited;
	return expandrec(ldef, visited, gGlobal->nil);	
}

Tree SourceReader::expandrec(Tree ldef, set<string>& visited, Tree lresult)
{
	for (;!isNil(ldef); ldef = tl(ldef)) {
		Tree d = hd(ldef); 
		Tree fname;
		if (isNil(d)) {
			// skill null definitions produced by declarations
		} else if (isImportFile(d,fname)) {
			string f = tree2str(fname);
			//cerr << "import(" << f << ")" << endl;
			
			//string f = tree2str(fname);
			if (visited.find(f) == visited.end()) {
				visited.insert(f);
				//Tree l = getlist(f);
				lresult = expandrec(getlist(f), visited, lresult);
			}
			
		} else {
			lresult = cons(d, lresult);
		}
	}
	return lresult;
}

void declareMetadata(Tree key, Tree value)
{
    if (gGlobal->gMasterDocument == yyfilename) {
        // inside master document, no prefix needed to declare metadata
        gGlobal->gMetaDataSet[key].insert(value);
    } else {
        string fkey(yyfilename);
        if (fkey != "") {
            fkey += "/";
        }
        fkey += tree2str(key);
        gGlobal->gMetaDataSet[tree(fkey.c_str())].insert(value);
    }
    //cout << "Master " << gGlobal->gMasterDocument  << ", file " << yyfilename <<  " : declare " << *key << "," << *value << endl;
}

void declareDoc(Tree t)
{
	//gGlobal->gLatexDocSwitch = true;
	gGlobal->gDocVector.push_back(t);
}
