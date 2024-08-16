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

#ifndef __SOURCEREADER__
#define __SOURCEREADER__

#include "boxes.hh"
#include <string>
#include <set>
#include <vector>

#include "PackageManager.hh"

Tree formatDefinitions(Tree rldef);
Tree checkRulelist (Tree lrules);
void declareMetadata(Tree key, Tree value);
void declareDefinitionMetadata(Tree id, Tree key, Tree value);
void declareDoc(Tree t);

/**
 * Helper class used for additional DSP of library files needed in the parsing process.
*/
class SourceReader 
{
    
    private:
    
        std::map<std::string, Tree> fFileCache;
        std::vector<std::string> fFilePathnames;
        std::vector<std::string> pPackageLists;
        PackageManager pm; 

        Tree parseLocal(const char* fname);
        Tree expandRec(Tree ldef, std::set<std::string>& visited, Tree lresult);
        bool cached(std::string fname);
        Tree parseFile(const char* fname);
        Tree parseString(const char* fname);
        void checkName();
        void checkDependency();
        
    public:
    
        void init()
        {
            fFileCache.clear();
            fFilePathnames.clear();
        }
        Tree getList(const char* fname);
        Tree expandList(Tree ldef);
        std::vector<std::string> listSrcFiles();
        std::vector<std::string> listLibraryFiles();
        std::vector<std::string> listPackages();

};

#endif 
