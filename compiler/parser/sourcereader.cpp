/*
	sourcereader : Faust source file reader
	
	This component is in charge of mapping filenames to 
	the list of faust definitions they contain.
	
*/
#include <iostream>
#include <map>
#include <list>


#include "sourcereader.hh"
#include "enrobage.hh"
#include "ppbox.hh"

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


static void printPatternError(Tree lhs1, Tree rhs1, Tree lhs2, Tree rhs2)
{
	cerr 	<< "ERROR : inconsistent number of parameters in pattern-matching rule: "
			<< boxpp(reverse(lhs2)) << " => " << boxpp(rhs2) << ";"
			<< " previous rule was: " 
			<< boxpp(reverse(lhs1)) << " => " << boxpp(rhs1) << ";"
			<< endl;
}

Tree checkRulelist (Tree lr)
{
	Tree lrules = lr;
	if (isNil(lrules)) { cerr << "ERROR : a case expression can't be empty" << endl; exit(1); }
	// first pattern used as a reference
	Tree lhs1 = hd(hd(lrules));
	Tree rhs1 = tl(hd(lrules));
	int npat = len(lhs1); 
	lrules = tl(lrules);
	while (! isNil(lrules)) {
		Tree lhs2 = hd(hd(lrules));
		Tree rhs2 = tl(hd(lrules));
		if (npat != len(lhs2)) {
			printPatternError(lhs1,rhs1,lhs2,rhs2);
			exit(1);
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
			return boxCase(cons(rhs,nil));
		}
	} else {
		list<Tree>::iterator p;
		Tree	l = nil;
		Tree	prev = *variants.begin();
		int 	npat = len(hd(prev));
		for (p=variants.begin(); p!=variants.end(); p++) {
			Tree cur = *p;
			if (npat != len(hd(cur))) {
				printPatternError(hd(prev), tl(prev), hd(cur), tl(cur));
				exit(1);
			}
			prev = cur;
			l = cons(*p,l);
		}
		return boxCase(l);
	}
}



/**
 * Formats a list of raw definitions represented by triplets
 * <name,arglit,body> into abstractions or pattern 
 * matching rules when appropriate.
 * 
 * @param rldef list of raw definitions in reverse order
 * @return the list of formatted definitions
 */
Tree formatDefinitions(Tree rldef)
{
	map<Tree,list<Tree> > dic;
	map<Tree,list<Tree> >::iterator p;
	Tree ldef2 = nil;
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
    if (fFileCache[fname] == 0) exit(1);
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
				
			
