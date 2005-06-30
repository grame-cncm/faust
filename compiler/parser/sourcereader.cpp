/*
	sourcereader : Faust source file reader
	
	This component is in charge of mapping filenames to 
	the list of faust definitions they contain.
	
*/
#include <iostream>

#include "sourcereader.hh"
#include "enrobage.hh"
using namespace std;

/****************************************************************
 						Parser variables
*****************************************************************/


int yyparse();

extern int 		yyerr;
extern int 		yydebug;
extern FILE*	yyin;
extern int		yylineno;
extern const char * yyfilename;

extern Tree 	gResult;
extern Tree 	gResult2;

 
/**
 * Parse a single faust source file. returns the list of
 * definitions it contains.
 * 
 * @param fname the name of the file to parse
 * @return the list of definitions it contains
 */

Tree SourceReader::parse(string fname)
{
	yyerr = 0;
	
	yyfilename = fname.c_str();
	yyin = fopensearch(yyfilename);
	if (yyin == NULL) {
		fprintf(stderr, "ERROR : Unable to open file  %s \n", yyfilename); 
		exit(1);
	}
	
	yylineno = 1;
	int r = yyparse();
	if (r) { 
		fprintf(stderr, "Parse error : code = %d \n", r); 
	}
	if (yyerr > 0) {
		//fprintf(stderr, "Erreur de parsing 2, count = %d \n", yyerr); 
		exit(1);
	}

	return gResult;
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
		fFileCache[fname] = parse(fname);
	}
	return fFileCache[fname];
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
	return expandrec(ldef, visited, nil);	
}

Tree SourceReader::expandrec(Tree ldef, set<string>& visited, Tree lresult)
{
	for (;!isNil(ldef); ldef = tl(ldef)) {
		Tree d = hd(ldef); 
		Tree fname;
		
		if (isImportFile(d,fname)) {
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
				
			
