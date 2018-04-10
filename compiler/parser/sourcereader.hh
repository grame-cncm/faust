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
void declareDefinitionMetadata(Tree id, Tree key, Tree value);
void declareDoc(Tree t);

class SourceReader 
{
    
    private:
    
        map<string, Tree> fFileCache;
        vector<string> fFilePathnames;
    
        Tree parseLocal(const char* fname);
        Tree expandRec(Tree ldef, set<string>& visited, Tree lresult);
        bool cached(string fname);
        Tree parseFile(const char* fname);
        Tree parseString(const char* fname);
        void checkName();
        
    public:
    
        Tree getList(const char* fname);
        Tree expandList(Tree ldef);
        vector<string> listSrcFiles();

};

#endif 
