#ifndef __SOURCEREADER__
#define __SOURCEREADER__

#include "boxes.hh"
#include <string>
#include <set>
#include <vector>

using namespace std;

Tree formatDefinitions(Tree rldef);
Tree checkRulelist (Tree lrules);
void declareMetadata(Tree key, Tree value);
void declareDoc(Tree t);

class SourceReader 
{
	map<string, Tree>	fFileCache;
	vector<string>		fFilePathnames;
	Tree parse(const char* fname);
	Tree expandrec(Tree ldef, set<string>& visited, Tree lresult);
	bool cached(string fname);
	
public:
	Tree getlist(const char* fname);
	Tree expandlist(Tree ldef);
	vector<string>	listSrcFiles();
};


#endif 
