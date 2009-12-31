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


#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cstdlib>

#include "doc_metadatas.hh"
#include "doc.hh"


extern SourceReader		gReader;

map<string, string>		gDocMetadatasStringMap;
set<string>				gDocMetadatasKeySet;

static void				initDocMetadatasKeySet();




/*****************************************************************************
						Public functions
 *****************************************************************************/


/** 
 * Dispatch initialization of metadatas container.
 */
void initDocMetadatas() 
{
	initDocMetadatasKeySet();
}



/*****************************************************************************
							Static functions
 *****************************************************************************/


/** 
 * Initialize gDocMetadatasKeySet, a set containing all the keywords.
 */
static void initDocMetadatasKeySet() {
	
	gDocMetadatasKeySet.insert("name");
	gDocMetadatasKeySet.insert("author");
	gDocMetadatasKeySet.insert("copyright");
	gDocMetadatasKeySet.insert("license");
	gDocMetadatasKeySet.insert("version");
}


///** 
// * Simple trace function.
// */
//static void printDocMetadatasStringMapContent() {
//	bool trace = false;
//	if(trace) {
//		cout << "gDocMetadatasStringMap.size() = " << gDocMetadatasStringMap.size() << endl;
//		map<string,string>::iterator it;
//		int i = 1;
//		for(it = gDocMetadatasStringMap.begin(); it!=gDocMetadatasStringMap.end(); ++it)
//			cout << i++ << ".\tgDocNoticeStringMap[" << it->first << "] \t= '" << it->second << "'" << endl;
//	}
//}

