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

#ifndef __DESCRIPTION__
#define __DESCRIPTION__

//------------------------------------
// generation of an xml description
//------------------------------------

#include <string>
#include <list>
#include <set>
#include <map>
#include <string>
#include "signals.hh"
#include "smartpointer.hh"
#include "tlib.hh"
#include "uitree.hh"
#include "garbageable.hh"

using namespace std;

void extractMetadata(const string& fulllabel, string& label, map<string, set<string> >& metadata);
string extractName(Tree fulllabel);

class Description : public virtual Garbageable
{
	string 			fName;
	string 			fAuthor;
	string 			fCopyright;
	string 			fLicense;
	string 			fVersion;

	string			fClassName;
	int				fInputs;
	int				fOutputs;
	int				fWidgetID;
	int				fActiveWidgetCount;
	int				fPassiveWidgetCount;
	list<string>	fActiveLines;
	list<string>	fPassiveLines;
	list<string>	fLayoutLines;
	list<int>		fLayoutTabs;
	

  public:
  
	Description():	/*fName("Unknow"), 
					fAuthor("Unknow"), 
					fCopyright("Unknow"),
					fLicense("Unknow"), 
					fVersion("Unknow"),*/
					
					fInputs(0),
					fOutputs(0),
					fWidgetID(0),
					fActiveWidgetCount(0),
					fPassiveWidgetCount(0)
					{}
					
	Description*	name(const string& s) 			{ fName = s; 	return this; }
	Description*	author(const string& s) 		{ fAuthor = s; 	return this; }
	Description*	copyright(const string& s) 		{ fCopyright = s; return this; }
	Description*	license(const string& s) 		{ fLicense = s; return this; }
	Description*	version(const string& s) 		{ fVersion = s; return this; }
	
	Description*	className(const string& s)		{ fClassName = s; return this; }
	Description*	inputs(int n) 					{ fInputs = n; 	return this; }
	Description*	outputs(int n) 					{ fOutputs = n; return this; }
	
	void			ui(Tree t);
	void 			print(int n, ostream& fout);
	
		
  private:
  
	void 			addGroup(int level, Tree t);
	int 			addWidget(Tree label, Tree varname, Tree sig);
	
  	void 			tab (int n, ostream& fout);
	void			addActiveLine(const string& l) 	{ fActiveLines.push_back(l);}
	void			addPassiveLine(const string& l) { fPassiveLines.push_back(l);}
	void			addLayoutLine(int n, const string& l) 	{ fLayoutTabs.push_back(n); fLayoutLines.push_back(l);}
	
};

#endif
