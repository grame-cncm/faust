#ifndef __SOURCEREADER__
#define __SOURCEREADER__

#include "boxes.hh"
#include <string>
#include <set>

using namespace std;

Tree formatDefinitions(Tree rldef);
Tree checkRulelist (Tree lrules);
void declareMetadata(Tree key, Tree value);

class SourceReader 
{
	map<string, Tree>	fFileCache;
	Tree parse(string fname);
	Tree expandrec(Tree ldef, set<string>& visited, Tree lresult);
	
public:
	bool cached(string fname);
	Tree getlist(string fname);
	Tree expandlist(Tree ldef);
};


#endif 
