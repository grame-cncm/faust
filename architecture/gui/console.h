/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.


 ************************************************************************
 ************************************************************************/
#ifndef __faustconsole__
#define __faustconsole__

#include "GUI.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <string>
#include <map>
#include <iostream>

using namespace std;

/******************************************************************************
*******************************************************************************

								USER INTERFACE

*******************************************************************************
*******************************************************************************/

struct param {
	float* fZone; float fMin; float fMax;
	param(float* z, float a, float b) : fZone(z), fMin(a), fMax(b) {}
};

class CMDUI : public GUI
{
	int					fArgc;
	char**				fArgv;
	stack<string>		fPrefix;
	map<string, param>	fKeyParam;

	void addOption(const char* label, float* zone, float min, float max)
	{
		string fullname = fPrefix.top() + label;
		fKeyParam.insert(make_pair(fullname, param(zone, min, max)));
	}

	void openAnyBox(const char* label)
	{
		string prefix;

		if (label && label[0]) {
			prefix = fPrefix.top() + "-" + label;
		} else {
			prefix = fPrefix.top();
		}
		fPrefix.push(prefix);
	}

public:

	CMDUI(int argc, char *argv[]) : GUI(), fArgc(argc), fArgv(argv) { fPrefix.push("--"); }
	virtual ~CMDUI() {}

	virtual void openFrameBox(const char* label)		{ openAnyBox(label); }
	virtual void openTabBox(const char* label)          { openAnyBox(label); }
	virtual void openHorizontalBox(const char* label)	{ openAnyBox(label); }
	virtual void openVerticalBox(const char* label)     { openAnyBox(label); }
	virtual void closeBox()                             { fPrefix.pop(); }

	virtual void addButton(const char* label, float* zone) 		{};
	virtual void addToggleButton(const char* label, float* zone) 	{};
	virtual void addCheckButton(const char* label, float* zone) 	{};

	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
	{
		addOption(label,zone,min,max);
	}

	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
	{
		addOption(label,zone,min,max);
	}

	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
	{
		addOption(label,zone,min,max);
	}

	// -- passive widgets

	virtual void addNumDisplay(const char* label, float* zone, int precision) 						{}
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) 	{}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) 			{}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) 			{}

	virtual void show() {}
	virtual void run()
	{
		char c;
		printf("Type 'q' to quit\n");
		while ((c = getchar()) != 'q') {
			sleep(1);
		}
	}

	void print()
	{
		map<string, param>::iterator i;
		cout << fArgc << "\n";
		cout << fArgv[0] << " option list : ";
		for (i = fKeyParam.begin(); i != fKeyParam.end(); i++) {
			cout << "[ " << i->first << " " << i->second.fMin << ".." << i->second.fMax <<" ] ";
		}
	}

	void process_command()
	{
		map<string, param>::iterator p;
		for (int i = 1; i < fArgc; i++) {
			if (fArgv[i][0] == '-') {
				p = fKeyParam.find(fArgv[i]);
				if (p == fKeyParam.end()) {
					cout << fArgv[0] << " : unrecognized option " << fArgv[i] << "\n";
					print();
					exit(1);
				}
				char*	end;
				*(p->second.fZone) = float(strtod(fArgv[i+1], &end));
				i++;
			}
		}
	}

	void process_init()
	{
		map<string, param>::iterator p;
		for (int i = 1; i < fArgc; i++) {
			if (fArgv[i][0] == '-') {
				p = fKeyParam.find(fArgv[i]);
				if (p == fKeyParam.end()) {
					cout << fArgv[0] << " : unrecognized option " << fArgv[i] << "\n";
					exit(1);
				}
				char*	end;
				*(p->second.fZone) = float(strtod(fArgv[i+1], &end));
				i++;
			}
		}
	}
};

#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/
