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


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "signals.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "privatise.hh"

#include "compile_scal.hh"
#include "compile_vect.hh"
#include "propagate.hh"
#include "errormsg.hh"
#include "ppbox.hh"
#include "enrobage.hh"
#include "eval.hh"
#include "description.hh"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "sourcereader.hh"


// construction des representations graphiques

#include "schema.h"
#include "drawschema.hh"


using namespace std ;


/****************************************************************
 						Parser variables
*****************************************************************/


int yyparse();

int 			yyerr;
extern int 		yydebug;
extern FILE*	yyin;
Tree 			gResult;
Tree 			gResult2;

SourceReader	gReader;

list<string>	gNameProperty;
list<string>	gAuthorProperty;
list<string>	gCopyrightProperty;
list<string>	gVersionProperty;
list<string>	gLicenseProperty;


/****************************************************************
 				Command line tools and arguments
*****************************************************************/

//-- command line arguments

bool			gHelpSwitch 	= false;
bool			gVersionSwitch 	= false;
bool			gDetailsSwitch 	= false;
bool            gVectorSwitch 	= false;
bool            gDrawPSSwitch 	= false;
bool            gDrawSVGSwitch 	= false;
bool            gPrintXMLSwitch = false;
int            	gBalancedSwitch = 1;
int            	gFoldThreshold 	= 25;
int            	gMaxNameSize 	= 40;

string			gArchFile;
string			gOutputFile;
list<string>	gInputFiles;


//-- command line tools

static bool isCmd(char* cmd, char* kw1)
{
	return 	(strcmp(cmd, kw1) == 0);
}

static bool isCmd(char* cmd, char* kw1, char* kw2)
{
	return 	(strcmp(cmd, kw1) == 0) || (strcmp(cmd, kw2) == 0);
}

bool process_cmdline(int argc, char* argv[])
{
	int	i=1; int err=0;

	while (i<argc) {

		if        (isCmd(argv[i], "-h", "--help")) {
			gHelpSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-v", "--version")) {
			gVersionSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-d", "--details")) {
			gDetailsSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-a", "--architecture")) {
			gArchFile = argv[i+1];
			i += 2;

		} else if (isCmd(argv[i], "-o")) {
			gOutputFile = argv[i+1];
			i += 2;

		} else if (isCmd(argv[i], "-vec", "--vectorize")) {
			gVectorSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-ps", "--postscript")) {
			gDrawPSSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-xml", "--xml")) {
			gPrintXMLSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-svg", "--svg")) {
			gDrawSVGSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-f", "--fold")) {
			gFoldThreshold = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-mns", "--max-name-size")) {
			gMaxNameSize = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-lb", "--left-balanced")) {
			gBalancedSwitch = 0;
			i += 1;

		} else if (isCmd(argv[i], "-mb", "--mid-balanced")) {
			gBalancedSwitch = 1;
			i += 1;

		} else if (isCmd(argv[i], "-rb", "--right-balanced")) {
			gBalancedSwitch = 2;
			i += 1;

		} else if (argv[i][0] != '-') {
			if (check_file(argv[i])) {
				gInputFiles.push_back(argv[i]);
			}
			i++;

		} else {
			cerr << "faust: unrecognized option \"" << argv[i] <<"\"" << endl;
			i++;
			err++;
		}
	}

	return err == 0;
}



/****************************************************************
 					 Help and Version information
*****************************************************************/



void printversion()
{
	cout << "FAUST, DSP to C++ compiler, Version 0.9.7\n";
	cout << "Copyright (C) 2002-2006, GRAME - Centre National de Creation Musicale. All rights reserved. \n\n";
}


void printhelp()
{
	printversion();
	cout << "usage: faust [options] file1 [file2 ...]\n";
	cout << "\twhere options represent zero or more compiler options \n\tand fileN represents a faust source file (.dsp extension).\n";

	cout << "\noptions :\n";
	cout << "---------\n";

	cout << "-h \t\tprint this --help message\n";
	cout << "-v \t\tprint compiler --version information\n";
	cout << "-d \t\tprint compilation --details\n";
	cout << "-ps \t\tprint block-diagram --postscript file\n";
	cout << "-svg \t\tprint block-diagram --svg file\n";
	cout << "-f \t\t--fold threshold during block-diagram generation\n";
	cout << "-mns \t\t--max-name-size threshold during block-diagram generation\n";
	cout << "-xml \t\tgenerate an --xml description file\n";
	cout << "-lb \t\tgenerate --left-balanced expressions\n";
	cout << "-mb \t\tgenerate --mid-balanced expressions (default)\n";
	cout << "-rb \t\tgenerate --right-balanced expressions\n";
	cout << "-a <file> \tC++ wrapper file\n";
	cout << "-o <file> \tC++ output file\n";


	cout << "\nexample :\n";
	cout << "---------\n";

	cout << "faust -a jack-gtk.cpp -o myfx.cpp myfx.dsp\n";
}





/****************************************************************
 					 			MAIN
*****************************************************************/




int main (int argc, char* argv[])
{

	/****************************************************************
	 1 - process command line
	*****************************************************************/

	process_cmdline(argc, argv);

	if (gHelpSwitch) 		{ printhelp(); exit(0); }
	if (gVersionSwitch) 	{ printversion(); exit(0); }


	/****************************************************************
	 2 - parse source files
	*****************************************************************/

	list<string>::iterator s;
	gResult2 = nil;
	yyerr = 0;
	string masterFilename = "unknow";

	for (s = gInputFiles.begin(); s != gInputFiles.end(); s++) {
		if (s == gInputFiles.begin()) masterFilename = *s;
		gResult2 = cons(importFile(tree(s->c_str())), gResult2);
	}
	if (yyerr > 0) {
		//fprintf(stderr, "Erreur de parsing 2, count = %d \n", yyerr);
		exit(1);
	}


	/****************************************************************
	 3 - evaluate 'process' definition
	*****************************************************************/

	Tree process = evalprocess(gReader.expandlist(gResult2));
	if (gErrorCount > 0) {
		cerr << "Total of " << gErrorCount << " errors during evaluation of : process = " << boxpp(process) << ";\n";
		exit(1);
	}


	if (gDetailsSwitch) { cerr << "process = " << boxpp(process) << ";\n"; }

	if (gDrawPSSwitch) 	{ drawSchema( process, subst("$0-ps",  masterFilename).c_str(), "ps" ); }
	if (gDrawSVGSwitch) { drawSchema( process, subst("$0-svg", masterFilename).c_str(), "svg" ); }


	int numInputs, numOutputs;
	getBoxType(process, &numInputs, &numOutputs);

	if (gDetailsSwitch) { cerr <<"process has " <<numInputs <<" inputs, and " <<numOutputs <<" outputs" <<endl; }


	/****************************************************************
	 4 - compute output signals of 'process'
	*****************************************************************/

	Tree lsignals = boxPropagateSig(nil, process , makeSigInputList(numInputs) );
	if (gDetailsSwitch) { cerr << "output signals are : " << endl;  printSignal(lsignals, stderr); }


	/****************************************************************
	 5 - translate output signals into C++ code
	*****************************************************************/

	Compiler* C;
	if (gVectorSwitch) 	C = new VectorCompiler("mydsp", "dsp", numInputs, numOutputs);
	else 				C = new ScalarCompiler("mydsp", "dsp", numInputs, numOutputs);

	if (gPrintXMLSwitch) C->setDescription(new Description());

	C->compileMultiSignal(lsignals);


	/****************************************************************
	 6 - generate XML description (if required)
	*****************************************************************/

	//cerr << "gPrintXMLSwitch " << gPrintXMLSwitch << endl;

	if (gPrintXMLSwitch) {
		//cerr << "masterfilename " << masterFilename << endl;
		Description* 	D = C->getDescription(); assert(D);
		ostream* 		xout = new ofstream(subst("$0.xml", masterFilename).c_str());

		if(gNameProperty.size()) 		D->name(*gNameProperty.begin());
		if(gAuthorProperty.size()) 		D->author(*gAuthorProperty.begin());
		if(gCopyrightProperty.size()) 	D->copyright(*gCopyrightProperty.begin());
		if(gLicenseProperty.size()) 	D->license(*gLicenseProperty.begin());
		if(gVersionProperty.size()) 	D->version(*gVersionProperty.begin());

		D->inputs(C->getClass()->inputs());
		D->outputs(C->getClass()->outputs());

		D->print(0, *xout);
	}


	/****************************************************************
	 7 - generate output file
	*****************************************************************/

	ostream* dst;
	istream* enrobage;
	istream* intrinsic;

	if (gOutputFile != "") {
		dst = new ofstream(gOutputFile.c_str());
	} else {
		dst = &cout;
	}


	if (gArchFile != "") {
		if ( (enrobage = open_arch_stream(gArchFile.c_str())) ) {

			C->getClass()->printLibrary(*dst);
			C->getClass()->printIncludeFile(*dst);

			streamCopyUntil(*enrobage, *dst, "<<includeIntrinsic>>");
			if ( gVectorSwitch && (intrinsic = open_arch_stream("intrinsic.hh")) ) {
				streamCopyUntilEnd(*intrinsic, *dst);
			}

			streamCopyUntil(*enrobage, *dst, "<<includeclass>>");
			C->getClass()->println(0,*dst);
			streamCopyUntilEnd(*enrobage, *dst);
		} else {
			cerr << "ERROR : can't open architecture file " << gArchFile << endl;
			return 1;
		}
	} else {
		C->getClass()->printLibrary(*dst);
		C->getClass()->printIncludeFile(*dst);
		C->getClass()->println(0,*dst);
	}

	return 0;
}
