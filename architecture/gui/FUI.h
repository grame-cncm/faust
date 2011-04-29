#ifndef FAUST_FUI_H
#define FAUST_FUI_H

#include "UI.h"

#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>

#include <iostream>
#include <fstream>

using namespace std;

#if 1

/*******************************************************************************
 * FUI : used to save and recall the state of the user interface
 * This class provides essentially two new methods saveState() and recallState()
 * used to save on file and recall from file the state of the user interface.
 * The file is human readble and editable
 ******************************************************************************/

class FUI  : public UI
{
	stack<string>		fGroupStack;
	vector<string>		fNameList;
	map<string, float*>	fName2Zone;

 protected:

 	// labels are normalized by replacing white spaces by underscores and by
 	// removing parenthesis
	string normalizeLabel(const char* label)
	{
		string 	s;
		char 	c;

		while ((c=*label++)) {
			if (isspace(c)) 				{ s += '_'; }
			//else if ((c == '(') | (c == ')') ) 	{ }
			else 							{ s += c; }
		}
		return s;
	}

	// add an element by relating its full name and memory zone
	virtual void addElement (const char* label, float* zone)
	{
		string fullname (fGroupStack.top() + '/' + normalizeLabel(label));
		fNameList.push_back(fullname);
		fName2Zone[fullname] = zone;
	}

	// keep track of full group names in a stack
	virtual void pushGroupLabel(const char* label)
	{
		if (fGroupStack.empty()) {
			fGroupStack.push(normalizeLabel(label));
		} else {
			fGroupStack.push(fGroupStack.top() + '/' + normalizeLabel(label));
		}
	}

	virtual void popGroupLabel()
	{
		fGroupStack.pop();
	};

 public:

	FUI() 			{}
	virtual ~FUI() 	{}

	// -- Save and recall methods

	// save the zones values and full names
	virtual void saveState(const char* filename)
	{
		ofstream f(filename);

		for (unsigned int i=0; i<fNameList.size(); i++) {
			string	n = fNameList[i];
			float*	z = fName2Zone[n];
			f << *z << ' ' << n << endl;
		}

		f << endl;
		f.close();
	}

	// recall the zones values and full names
	virtual void recallState(const char* filename)
	{
		ifstream f(filename);
		float	v;
		string	n;

		while (f.good()) {
			f >> v >> n;
			if (fName2Zone.count(n)>0) {
				*(fName2Zone[n]) = v;
			} else {
				cerr << "recallState : parameter not found : " << n << " with value : " << v << endl;
			}
		}
		f.close();
	}


    // -- widget's layouts (just keep track of group labels)

    virtual void openFrameBox(const char* label) 		{ pushGroupLabel(label); }
    virtual void openTabBox(const char* label) 			{ pushGroupLabel(label); }
    virtual void openHorizontalBox(const char* label) 	{ pushGroupLabel(label); }
    virtual void openVerticalBox(const char* label)  	{ pushGroupLabel(label); }
    virtual void closeBox() 							{ popGroupLabel(); };

    // -- active widgets (just add an element)

    virtual void addButton(const char* label, float* zone) 			{ addElement(label, zone); }
    virtual void addToggleButton(const char* label, float* zone) 	{ addElement(label, zone); }
    virtual void addCheckButton(const char* label, float* zone) 	{ addElement(label, zone); }
    virtual void addVerticalSlider(const char* label, float* zone, float , float , float , float )
    																{ addElement(label, zone); }
    virtual void addHorizontalSlider(const char* label, float* zone, float , float , float , float )
    																{ addElement(label, zone); }
    virtual void addNumEntry(const char* label, float* zone, float , float , float , float )
    																{ addElement(label, zone); }

    // -- passive widgets (are ignored)

    virtual void addNumDisplay(const char* , float* , int ) {};
    virtual void addTextDisplay(const char* , float* , const char*[], float , float ) {};
    virtual void addHorizontalBargraph(const char* , float* , float , float ) {};
    virtual void addVerticalBargraph(const char* , float* , float , float ) {};

	// -- metadata are not used

    virtual void declare(float* , const char* , const char* ) {}
};
#endif

#endif

