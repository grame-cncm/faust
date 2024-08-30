/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2009 GRAME, Centre National de Creation Musicale
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

/*****************************************************************************
 ******************************************************************************


                        The Documentator Language


 ******************************************************************************
 *****************************************************************************/

/**
 * @file doc.cpp
 * @author Karim Barkati and Yann Orlarey
 * @version 1.0
 * @date 2009
 * @brief Implementation of documentation trees support and printing.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <algorithm>
#include <functional>

#include <fstream>
#include <iostream>
#include <sstream>

#include <map>
#include <string>
#include <vector>

#include "compatibility.hh"
#include "doc.hh"
#include "doc_Text.hh"
#include "doc_autodoc.hh"
#include "doc_compile.hh"
#include "doc_lang.hh"
#include "doc_notice.hh"
#include "drawschema.hh"
#include "enrobage.hh"
#include "errormsg.hh"
#include "eval.hh"
#include "exception.hh"
#include "files.hh"
#include "global.hh"
#include "lateq.hh"
#include "names.hh"
#include "ppbox.hh"
#include "prim2.hh"
#include "propagate.hh"
#include "recursivness.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "sourcereader.hh"

#define MAXIDCHARS 10  ///< max numbers (characters) to represent ids (e.g. for directories).

using namespace std;

/*****************************************************************************
                        Globals and prototyping
 *****************************************************************************/

enum { langEN, langFR, langIT };

/* Printing functions */
static void printLatexHeader(istream& latexheader, const string& faustversion, ostream& docout);
static void printFaustListings(ostream& docout);
static void printFaustListing(string& path, ostream& docout);
static void printLatexFooter(ostream& docout);
static void printDocContent(const char* svgTopDir, const vector<Tree>& docVector,
                            const string& faustversion, ostream& docout);
static void printFaustdocStamp(const string& faustversion, ostream& docout);
static void printDocEqn(Lateq* ltq, ostream& docout);
static void printDocDgm(const Tree expr, const char* svgTopDir, ostream& docout, int i);
static void printDocMetadata(const Tree expr, ostream& docout);

/* Primary sub-functions for <equation> handling */
static void prepareDocEqns(const vector<Tree>& docBoxes,
                           vector<Lateq*>&     docCompiledEqnsVector);  ///< Caller function.
static void collectDocEqns(const vector<Tree>& docBoxes,
                           vector<Tree>&       eqBoxes);  ///< step 0. Feed a vector.
static void mapEvalDocEqn(const vector<Tree>& eqBoxes, const Tree& env,
                          vector<Tree>& evalEqBoxes);  ///< step 1. Evaluate boxes.
static void mapGetEqName(const vector<Tree>& evalEqBoxes,
                         vector<string>&     eqNames);  ///< step 2. Get boxes name.
static void calcEqnsNicknames(const vector<string>& eqNames,
                              vector<string>&       eqNicknames);  ///< step 3. Calculate nicknames.
static void mapPrepareEqSig(const vector<Tree>& evalEqBoxes, vector<int>& eqInputs,
                            vector<int>&  eqOutputs,
                            vector<Tree>& eqSigs);  ///< step 4&5. Propagate and prepare signals.
static void mapSetSigNickname(const vector<string>& eqNicknames, const vector<int>& eqInputs,
                              const vector<Tree>& eqSigs);  ///< step 6. Set signals nicknames.
static void collectEqSigs(const vector<Tree>& eqSigs,
                          Tree& superEqList);  ///< step 7. Collect all signals in a superlist.
static void annotateSuperList(DocCompiler* DC, Tree superEqList);  ///< step 8. Annotate superlist.
// static void	calcAndSetLtqNames( Tree superEqList );		///< step 9.
static void mapCompileDocEqnSigs(
    const vector<Tree>& eqSigs, const vector<int>& eqInputs, const vector<int>& eqOutputs,
    DocCompiler*    DC,
    vector<Lateq*>& docCompiledEqnsVector);  ///< step 10. Compile equations.

/* Secondary sub-functions for <equation> handling */
static string calcNumberedName(const char* base, int i);
static void   getBoxInputsAndOutputs(const Tree t, int& numInputs, int& numOutputs);
static string calcDocEqnInitial(const string s);

/* Notice related functions */
static void       initCompilationDate();
static struct tm* getCompilationDate();

/* Files functions */
static unique_ptr<ifstream> openArchFile(const string& filename);
static char*                legalFileName(const Tree t, int n, char* dst);
static void                 copyFaustSources(const char* projname, const vector<string>& pathnames);
vector<string>&             docCodeSlicer(const string& faustfile, vector<string>& codeSlices);
static void                 printdocCodeSlices(const string& code, ostream& docout);
static bool                 doesFileBeginWithCode(const string& faustfile);

/*****************************************************************************
                    Types of Documentation Elements
 *****************************************************************************/

Tree docTxt(const char* name)
{
    return tree(gGlobal->DOCTXT, tree(symbol(name)));
}
bool isDocTxt(Tree t)
{
    return t->node() == Node(gGlobal->DOCTXT);
}
bool isDocTxt(Tree t0, const char** str)
{
    Tree t1;
    Sym  s;
    if (isTree(t0, gGlobal->DOCTXT, t1) && isSym(t1->node(), &s)) {
        *str = name(s);
        return true;
    } else {
        return false;
    }
}

Tree docEqn(Tree x)
{
    return tree(gGlobal->DOCEQN, x);
}
bool isDocEqn(Tree t, Tree& x)
{
    return isTree(t, gGlobal->DOCEQN, x);
}

Tree docDgm(Tree x)
{
    return tree(gGlobal->DOCDGM, x);
}
bool isDocDgm(Tree t, Tree& x)
{
    return isTree(t, gGlobal->DOCDGM, x);
}

Tree docNtc()
{
    return tree(gGlobal->DOCNTC);
}
bool isDocNtc(Tree t)
{
    return isTree(t, gGlobal->DOCNTC);
}

Tree docLst()
{
    return tree(gGlobal->DOCLST);
}
bool isDocLst(Tree t)
{
    return isTree(t, gGlobal->DOCLST);
}

Tree docMtd(Tree x)
{
    return tree(gGlobal->DOCMTD, x);
}
bool isDocMtd(Tree t, Tree& x)
{
    return isTree(t, gGlobal->DOCMTD, x);
}

/*****************************************************************************
                Main Printing Function for the Documentation
 *****************************************************************************/

/**
 * @brief The entry point to generate Faust doc files.
 *
 * The entry point to generate the output LaTeX file, stored in the directory "<projname>-math/".
 * This file eventually references images for diagrams, generated in SVG subdirectories.
 * The device system was adapted from drawSchema's device system.
 *
 * @param[in]	projname		Basename of the new doc directory ("*-math").
 * @param[in]	docdev			The doc device; only ".tex" is supported for the moment.
 * @param[in]	faustversion	The current version of this Faust compiler.
 */
void printDoc(const char* projname, const char* docdev, const char* faustversion)
{
    gGlobal->gDocDevSuffix = docdev;

    /** File stuff : create doc directories and a tex file. */
    // cerr << "Documentator : printDoc : gGlobal->gFaustDirectory = '" << gGlobal->gFaustDirectory
    // << "'" << endl; cerr << "Documentator : printDoc : gGlobal->gFaustSuperDirectory = '" <<
    // gGlobal->gFaustSuperDirectory << "'" << endl;  cerr << "Documentator : printDoc :
    // gGlobal->gFaustSuperSuperDirectory = '" << gGlobal->gFaustSuperSuperDirectory << "'" << endl;
    // cerr << "Documentator : printDoc : gCurrentDir = '" << gCurrentDir << "'" << endl;

    makeDir(projname);  // create a top directory to store files

    string svgTopDir = subst("$0/svg", projname);
    makeDir(svgTopDir.c_str());  // create a directory to store svg-* subdirectories.

    string cppdir = subst("$0/cpp", projname);
    makeDir(cppdir.c_str());  // create a cpp directory.

    string pdfdir = subst("$0/pdf", projname);
    makeDir(pdfdir.c_str());  // create a pdf directory.

    /* Copy all Faust source files into an 'src' sub-directory. */
    vector<string> pathnames = gGlobal->gReader.listSrcFiles();
    copyFaustSources(projname, pathnames);

    string texdir = subst("$0/tex", projname);
    mkchDir(texdir.c_str());  // create a directory and move into.

    /** Create THE mathdoc tex file. */
    ofstream docout(subst("$0.$1", gGlobal->gDocName, docdev).c_str());
    choldDir();  // return to current directory

    /** Init and load translation file. */
    loadTranslationFile(gGlobal->gDocLang);

    /** Simulate a default doc if no <mdoc> tag detected. */
    if (gGlobal->gDocVector.empty()) {
        declareAutoDoc();
    }

    /** Printing stuff : in the '.tex' ouptut file, eventually including SVG files. */
    printFaustdocStamp(faustversion, docout);  ///< Faust version and compilation date (comment).
    unique_ptr<istream> latexheader = openArchFile(gGlobal->gLatexheaderfilename);
    printLatexHeader(*latexheader, faustversion,
                     docout);  ///< Static LaTeX header (packages and setup).
    printDocContent(svgTopDir.c_str(), gGlobal->gDocVector, faustversion,
                    docout);   ///< Generate math contents (main stuff!).
    printLatexFooter(docout);  ///< Static LaTeX footer.
}

/*****************************************************************************
            LaTeX basic printing functions of the Documentation
 *****************************************************************************/

/**
 * Print a static LaTeX header.
 *
 * @param[in]	latexheader		The file containing the static part of the LaTeX header.
 * @param[in]	faustversion	The current version of this Faust compiler.
 * @param[out]	docout			The LaTeX output file to print into.
 */
static void printLatexHeader(istream& latexheader, const string& faustversion, ostream& docout)
{
    string s;
    while (getline(latexheader, s)) {
        docout << s << endl;
    }

    /** Specific LaTeX macros for Faust */
    docout << "\\newcommand{\\faustfilename}{" << gGlobal->gMasterDocument << "}" << endl;
    docout << "\\newcommand{\\faustdocdir}{" << gGlobal->gMasterName << "-mdoc}" << endl;
    docout << "\\newcommand{\\faustprogname}{" << gGlobal->gMasterName << "}" << endl;
    docout << "\\newcommand{\\faustversion}{" << faustversion << "}" << endl;
    char datebuf[150];
    strftime(datebuf, 150, "%B %d, %Y", getCompilationDate());
    docout << "\\newcommand{\\faustdocdate}{" << datebuf << "}" << endl;

    docout << endl << "\\begin{document}" << endl;
}

/**
 * @Brief Print a metadata set.
 *
 * Each metadata is a set, in order to handle multiple items,
 * like multiple authors, even if most of metadatas have
 * unique items.
 *
 * @param[in]	expr		Parsed metadata keyname, as boxes tree.
 * @param[out]	docout		The output file to print into.
 */
static void printDocMetadata(const Tree expr, ostream& docout)
{
    if (gGlobal->gMetaDataSet.count(expr)) {
        string    sep  = "";
        set<Tree> mset = gGlobal->gMetaDataSet[expr];
        for (set<Tree>::iterator j = mset.begin(); j != mset.end(); j++) {
            docout << sep << unquote(tree2str(*j));
            sep = ", ";
        }
    }
}

/**
 * Print listings of each Faust code ".dsp" files,
 * calling the 'printFaustListing' function.
 *
 * @param[out]	docout		The LaTeX output file to print into.
 */
static void printFaustListings(ostream& docout)
{
    if (gGlobal->gLstDependenciesSwitch) {
        vector<string> pathnames = gGlobal->gReader.listSrcFiles();
        for (unsigned int i = 0; i < pathnames.size(); i++) {
            printFaustListing(pathnames[i], docout);
        }
    } else {
        printFaustListing(gGlobal->gMasterDocument, docout);
    }
}

/**
 * Print a listing of the Faust code, in a LaTeX "listing" environment.
 * Strip content of <mdoc> tags.
 *
 * @param[in]	faustfile	The source file containing the Faust code.
 * @param[out]	docout		The LaTeX output file to print into.
 */
static void printFaustListing(string& faustfile, ostream& docout)
{
    string   s;
    ifstream src;

    // cerr << "Documentator : printFaustListing : Opening file '" << faustfile << "'" << endl;
    src.open(faustfile.c_str(), ifstream::in);

    docout << endl << "\\bigskip\\bigskip" << endl;
    docout << "\\begin{lstlisting}[caption=\\texttt{" << fileBasename(faustfile.c_str()) << "}]"
           << endl;

    bool isInsideDoc = false;

    if (faustfile != "" && src.good()) {
        while (getline(src, s)) { /** We suppose there's only one <mdoc> tag per line. */
            size_t foundopendoc = s.find("<mdoc>");
            if (foundopendoc != string::npos && gGlobal->gStripDocSwitch) {
                isInsideDoc = true;
            }

            if (isInsideDoc == false) {
                docout << s << endl;
            }

            size_t foundclosedoc = s.find("</mdoc>");
            if (foundclosedoc != string::npos && gGlobal->gStripDocSwitch) {
                isInsideDoc = false;
            }
        }
    } else {
        stringstream error;
        error << "ERROR : can't open Faust source file " << faustfile << endl;
        throw faustexception(error.str());
    }

    docout << "\\end{lstlisting}" << endl << endl;
}

/**
 * Print the static LaTeX footer.
 *
 * @param[out]	docout		The LaTeX output file to print into.
 */
static void printLatexFooter(ostream& docout)
{
    docout << endl << "\\end{document}" << endl << endl;
}

/**
 * Print a "doc stamp" in the LaTeX document :
 * - the Faust version,
 * - the date of doc compilation,
 * - faust's web site URL.
 *
 * @param[in]	faustversion	The current version of this Faust compiler.
 * @param[out]	docout			The LaTeX output file to print into.
 */
static void printFaustdocStamp(const string& faustversion, ostream& docout)
{
    char datebuf[150];
    strftime(datebuf, 150, "%c", getCompilationDate());

    docout << "%% This documentation was generated with Faust version " << faustversion << endl;
    docout << "%% " << datebuf << endl;
    docout << "%% https://faust.grame.fr" << endl << endl;
}

/*****************************************************************************
            Main loop : launches prepare, evaluate, and print functions
 *****************************************************************************/

/**
 * @brief Main documentator loop.
 *
 * First loop on gGlobal->gGlobal->gDocVector, which contains the faust <mdoc> trees.
 * Second loop for each of these <mdoc> trees, which contain parsed input expressions of 3 types :
 * gGlobal->DOCEQN for <equation> tags, gGlobal->DOCDGM for <diagram> tags, and gGlobal->DOCTXT for
 *direct LaTeX text (no tag).
 * - gGlobal->DOCTXT expressions printing is trivial.
 * - gGlobal->DOCDGM expressions printing calls 'printDocDgm' to generate SVG files and print LaTeX
 *"figure" code.
 * - gGlobal->DOCEQN expressions printing calls 'printDocEqn' after an important preparing work
 *   has been done by 'prepareDocEqns'.
 *
 * @param[in]	projname		Basename of the new doc directory ("*-math").
 * @param[in]	docVector		Contains all <mdoc> parsed content (as boxes).
 * @param[in]	faustversion	The current version of this Faust compiler.
 * @param[out]	docout			The output file to print into.
 **/
static void printDocContent(const char* svgTopDir, const vector<Tree>& docVector,
                            const string& faustversion, ostream& docout)
{
    // cerr << endl << "Documentator : printdoccontent : " << docVector.size() << " <mdoc> tags
    // read." << endl;

    /** Equations need to be prepared (named and compiled) before printing. */
    vector<Lateq*> docCompiledEqnsVector;
    prepareDocEqns(docVector, docCompiledEqnsVector);  ///< Quite a lot of stuff there.
    vector<Lateq*>::iterator eqn_it = docCompiledEqnsVector.begin();

    int dgmIndex = 1;  ///< For diagram directories numbering.

    vector<string> docMasterCodeMap;
    docMasterCodeMap = docCodeSlicer(gGlobal->gMasterDocument, docMasterCodeMap);

    vector<Tree>::const_iterator   doc;
    vector<string>::const_iterator code;
    code = docMasterCodeMap.begin();

    if (doesFileBeginWithCode(gGlobal->gMasterDocument) && (!docMasterCodeMap.empty()) &&
        gGlobal->gLstDistributedSwitch) {
        printdocCodeSlices(*code, docout);
        code++;
    }

    /** First level printing loop, on docVector. */
    for (doc = docVector.begin(); doc < docVector.end(); doc++, code++) {
        Tree L = reverse(*doc);
        // cerr << "Entering into <mdoc> parsing..." << endl;

        /** Second level printing loop, on each <mdoc>. */
        while (isList(L)) {
            Tree expr;
            if (isDocEqn(hd(L), expr)) {  ///< After equations are well prepared and named.
                printDocEqn(*eqn_it++, docout);
            } else if (isDocDgm(hd(L), expr)) {
                printDocDgm(expr, svgTopDir, docout, dgmIndex++);
            } else if (isDocMtd(hd(L), expr)) {
                printDocMetadata(expr, docout);
            } else if (isDocTxt(hd(L))) {
                docout << *hd(L)->branch(0);  // Directly print registered doc text.
            } else if (isDocNtc(hd(L))) {
                printDocNotice(faustversion, docout);
            } else if (isDocLst(hd(L))) {
                printFaustListings(docout);
            } else {
                cerr << "ERROR : " << *hd(L) << " is not a valid documentation type." << endl;
            }
            L = tl(L);
        }
        // cerr << " ...end of <mdoc> parsing." << endl;

        if (code != docMasterCodeMap.end() && gGlobal->gLstDistributedSwitch) {
            printdocCodeSlices(*code, docout);
        }
    }
}

/*****************************************************************************
            Primary sub-functions for <equation> handling
 *****************************************************************************/

/**
 * @brief Caller function for all steps of doc equations preparation.
 *
 * Note : many of the functions called put their result into their last argument
 * in a "source / destination" manner,
 * the "destination" being declared before the function call.
 *
 * @param[in]	docBoxes				The <mdoc> boxes to collect and prepare.
 * @param[out]	docCompiledEqnsVector	The place to store compiled equations.
 */
static void prepareDocEqns(const vector<Tree>& docBoxes, vector<Lateq*>& docCompiledEqnsVector)
{
    vector<Tree> eqBoxes;
    collectDocEqns(docBoxes, eqBoxes);  ///< step 0. Feed a vector.

    if (!eqBoxes.empty()) {
        vector<Tree> evalEqBoxes;
        mapEvalDocEqn(eqBoxes, gGlobal->gExpandedDefList,
                      evalEqBoxes);  ///< step 1. Evaluate boxes.
        vector<string> eqNames;
        mapGetEqName(evalEqBoxes, eqNames);  ///< step 2. Get boxes name.
        vector<string> eqNicknames;
        calcEqnsNicknames(eqNames, eqNicknames);  ///< step 3. Calculate nicknames.

        vector<int>  eqInputs;
        vector<int>  eqOutputs;
        vector<Tree> eqSigs;
        mapPrepareEqSig(evalEqBoxes, eqInputs, eqOutputs,
                        eqSigs);  ///< step 4&5. Propagate and prepare signals.
        mapSetSigNickname(eqNicknames, eqInputs, eqSigs);  ///< step 6. Set signals nicknames.
        Tree superEqList;
        collectEqSigs(eqSigs, superEqList);  ///< step 7. Collect all signals in a superlist.

        DocCompiler* DC = new DocCompiler(0, 0);
        annotateSuperList(DC, superEqList);  ///< step 8. Annotate superEqList.
        // calcAndSetLtqNames( superEqList );										///< step 9.
        // (directly in 10.)
        mapCompileDocEqnSigs(eqSigs, eqInputs, eqOutputs, DC,
                             docCompiledEqnsVector);  ///< step 10. Compile every signal.
    }
}

/**
 * #0. Collect every <equation> found in all <mdoc> faust comments.
 *
 * @param[in]	docBoxes	The <mdoc> boxes to filter.
 * @param[out]	eqBoxes		The place to store only <equation> boxes.
 */
static void collectDocEqns(const vector<Tree>& docBoxes, vector<Tree>& eqBoxes)
{
    int nbdoceqn = 0;

    for (vector<Tree>::const_iterator doc = docBoxes.begin(); doc < docBoxes.end(); doc++) {
        Tree L = reverse(*doc);
        Tree expr;
        while (isList(L)) {
            if (isDocEqn(hd(L), expr)) {
                eqBoxes.push_back(expr);
                nbdoceqn++;
            }
            L = tl(L);
        }
    }
    // cerr << "Documentator : collectDocEqns : " << nbdoceqn << " <equation> tags found." << endl;
}

/**
 * #1. Evaluate every doc <equation> (evaluation replaces abstractions by symbolic boxes).
 *
 * @param[in]	eqBoxes		The boxes to evaluate.
 * @param[in]	env			The environment for the evaluation.
 * @param[out]	evalEqBoxes	The place to store evaluated equations boxes.
 */
static void mapEvalDocEqn(const vector<Tree>& eqBoxes, const Tree& env, vector<Tree>& evalEqBoxes)
{
    // cerr << "###\n# Documentator : mapEvalDocEqn" << endl;

    for (vector<Tree>::const_iterator eq = eqBoxes.begin(); eq < eqBoxes.end(); eq++) {
        evalEqBoxes.push_back(evaldocexpr(*eq, env));
    }
    // cerr << "Documentator : end of mapEvalDocEqn\n---" << endl;
}

/**
 * #2. Get name if exists, else create one, and store it.
 *
 * @param[in]	evalEqBoxes	Evaluated box trees, eventually containing an equation name.
 * @param[out]	eqNames		The place to store equations names.
 */
static void mapGetEqName(const vector<Tree>& evalEqBoxes, vector<string>& eqNames)
{
    // cerr << "###\n# Documentator : mapGetEqName" << endl;

    int i = 1;
    for (vector<Tree>::const_iterator eq = evalEqBoxes.begin(); eq < evalEqBoxes.end(); eq++, i++) {
        Tree   id;
        string s;
        int    n, m;
        getBoxType(*eq, &n, &m);  // eq name only for bd without inputs
        if (n == 0 && getDefNameProperty(*eq, id)) {
            s = tree2str(id);
        } else {
            s = calcNumberedName("doceqn-", i);
        }
        eqNames.push_back(s);
    }
    // cerr << "Documentator : end of mapGetEqName\n---" << endl;
}

/**
 * #3. Calculate a nickname for each equation and store it.
 *
 * @param[in]	eqNames		Equations names to parse.
 * @param[out]	eqNicknames	The place to store calculated nicknames.
 *
 * @todo Should check unicity : check whether several names share the same initial,
 * or else capture consonants for example.
 */
static void calcEqnsNicknames(const vector<string>& eqNames, vector<string>& eqNicknames)
{
    // cerr << "###\n# Documentator : calcEqnsNicknames" << endl;

    vector<string> v;

    for (vector<string>::const_iterator eq = eqNames.begin(); eq < eqNames.end(); eq++) {
        string init = calcDocEqnInitial(*eq);
        v.push_back(init);
        /** Check duplicates */
        //		for( vector<string>::iterator it = v.begin(); it < v.end()-1; ++it ) {
        //			if (init == *it) {
        //				//cerr << "!! Warning Documentator : calcEqnsNicknames : duplicates \"" <<
        // init << "\"" << endl;
        //			}
        //		}
        eqNicknames.push_back(init);
    }

    //	for( vector<string>::const_iterator eq = eqNames.begin(); eq < eqNames.end(); eq++ ) {
    //		int c = 0;
    //		c = count_if(eqNames.begin(), eqNames.end(), bind2nd(equal_to<string>(), *eq));
    //		if (c > 0) {
    //			cerr << "- Duplicate nickname !! " << *eq << endl;
    //		} else {
    //			cerr << "(no duplicate) " << *eq << endl;
    //		}
    //	}

    // cerr << "Documentator : end of calcEqnsNicknames\n---" << endl;
}

/**
 * #4&5. Propagate and prepare every doc <equation>.
 *
 * Call boxPropagateSig, deBruijn2Sym, simplify, and privatise.
 *
 * @param[in]	evalEqBoxes		Equations boxes to propagate as signals.
 * @param[out]	eqSigs			The place to store prepared signals.
 */
static void mapPrepareEqSig(const vector<Tree>& evalEqBoxes, vector<int>& eqInputs,
                            vector<int>& eqOutputs, vector<Tree>& eqSigs)
{
    // cerr << "###\n# Documentator : mapPrepareEqSig" << endl;

    for (vector<Tree>::const_iterator eq = evalEqBoxes.begin(); eq < evalEqBoxes.end(); eq++) {
        int numInputs, numOutputs;
        getBoxInputsAndOutputs(*eq, numInputs, numOutputs);
        // cerr << numInputs <<" ins and " << numOutputs <<" outs" << endl;
        eqInputs.push_back(numInputs);
        eqOutputs.push_back(numOutputs);

        Tree lsig1 = boxPropagateSig(gGlobal->nil, *eq, makeSigInputList(numInputs));
        // cerr << "output signals are : " << endl;  printSignal(lsig1, stderr);

        Tree lsig2 = deBruijn2Sym(lsig1);  ///< Convert debruijn recursion into symbolic recursion
        Tree lsig3 = simplify(lsig2);      ///< Simplify by executing every computable operation
        // Tree lsig4 = privatise(lsig3);		///< Un-share tables with multiple writers
        Tree lsig4 = docTableConvertion(
            lsig3);  ///< convert regular tables into special doctables
                     ///< (regular tables are difficult to translate to equations)
        eqSigs.push_back(lsig4);
    }
    // cerr << "Documentator : end of mapPrepareEqSig\n---" << endl;
}

/**
 * #6. Set signals nicknames.
 *
 * Do nothing for the moment !
 * @param[in]	eqNicknames		Contains previously calculated nicknames.
 * @param[out]	eqSigs			The signals to tag with a NICKNAMEPROPERTY.
 */
static void mapSetSigNickname(const vector<string>& eqNicknames, const vector<int>& eqInputs,
                              const vector<Tree>& eqSigs)
{
    // cerr << "###\n# Documentator : mapSetSigNickname" << endl;

    //	Do nothing for the moment...
    //	for( unsigned int i=0; i < eqSigs.size(); i++ ) {
    //		if (eqInputs[i] == 0) // Only "generators" should be finally named with user equation
    //(nick)name. 			setSigListNickName(eqSigs[i], eqNicknames[i]);
    //	}
    // cerr << "Documentator : end of mapSetSigNickname\n---" << endl;
}

/**
 * #7. Collect each prepared list of signals to construct a super list.
 *
 * @param[in]	eqSigs			Contains well-prepared and nicknamed signals.
 * @param[out]	superEqList		The root where to 'cons' signals all together.
 */
static void collectEqSigs(const vector<Tree>& eqSigs, Tree& superEqList)
{
    // cerr << "###\n# Documentator : collectEqSigs" << endl;

    superEqList = gGlobal->nil;

    for (vector<Tree>::const_iterator it = eqSigs.begin(); it < eqSigs.end(); ++it) {
        superEqList = cons(*it, superEqList);
    }
    // printSignal(superEqList, stdout, 0);

    // cerr << endl << "Documentator : end of collectEqSigs\n---" << endl;
}

/**
 * #8. Annotate superEqList (to find candidate signals to be named later).
 *
 * @param[in]	DC			The signals compiler.
 * @param[out]	superEqList	The super equations signal tree to annotate.
 */
static void annotateSuperList(DocCompiler* DC, Tree superEqList)
{
    DC->annotate(superEqList);
}

///**
// * #9. Calculated and set lateq (LaTeX equation) names.
// * Note : Transfered into mapCompileDocEqnSigs (DocCompiler::compileMultiSignal).
// */
// static void	calcAndSetLtqNames(Tree superEqList)
//{
//
//}

/**
 * #10. Name and compile prepared doc <equation> signals.
 *
 * @param[in]	eqSigs					Contains well-prepared and nicknamed signals.
 * @param[in]	DC						The signals compiler.
 * @param[out]	docCompiledEqnsVector	The place to store each compiled Lateq* object.
 */
static void mapCompileDocEqnSigs(const vector<Tree>& eqSigs, const vector<int>& eqInputs,
                                 const vector<int>& eqOutputs, DocCompiler* DC,
                                 vector<Lateq*>& docCompiledEqnsVector)
{
    // cerr << "###\n# Documentator : mapCompileDocEqnSigs" << endl;

    for (unsigned int i = 0; i < eqSigs.size(); i++) {
        // docCompiledEqnsVector.push_back( DC->compileMultiSignal(*it, 0) );
        docCompiledEqnsVector.push_back(
            DC->compileLateq(eqSigs[i], new Lateq(eqInputs[i], eqOutputs[i])));
    }

    // cerr << "Documentator : end of mapCompileDocEqnSigs\n---" << endl;
}

/*****************************************************************************
                Secondary sub-functions for <equation> handling
 *****************************************************************************/
/**
 * Calculate an appropriate nickname for equations,
 * from previous names.
 *
 * @param	The string to parse.
 * @return	Essentially returns the initial character,
 * except "Y" for "process", and "Z" for unnamed equations.
 */
static string calcDocEqnInitial(const string s)
{
    string nn;
    if (s == "process") {
        nn = "Y";
    } else if (s.substr(0, 6) == "doceqn") {
        nn = "Z";
    } else {
        nn += toupper(s[0]);
    }
    return nn;
}

/**
 * Just get the number of inputs and the number of outputs of a box.
 *
 * @param[in]	t			The box tree to get inputs and outputs from.
 * @param[out]	numInputs	The place to store the number of inputs.
 * @param[out]	numOutputs	The place to store the number of outputs.
 */
static void getBoxInputsAndOutputs(const Tree t, int& numInputs, int& numOutputs)
{
    if (!getBoxType(t, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR : during the evaluation of t : " << boxpp(t) << endl;
        throw faustexception(error.str());
    }
    // cerr << "Documentator : " << numInputs <<" inputs and " << numOutputs <<" outputs for box : "
    // << boxpp(t) << endl;
}

/**
 * Print doc equations, following the Lateq::println method.
 *
 * @param[in]	ltq		The object containing compiled LaTeX code of equations.
 * @param[out]	docout	The output file to print into.
 */
static void printDocEqn(Lateq* ltq, ostream& docout)
{
    ltq->println(docout);
    // cerr << "Documentator : printDocEqn : "; ltq->println(cerr); cerr << endl;
}

/*****************************************************************************
                    Sub-function for <diagram> handling
 *****************************************************************************/

/**
 * @brief Doc diagrams handling.
 *
 * Three steps :
 * 1. evaluate expression
 * 2. call svg drawing in the appropriate directory
 * 3. print latex figure code with the appropriate directory reference
 *
 * @param[in]	expr		Parsed input expression, as boxes tree.
 * @param[in]	svgTopDir	Basename of the new doc directory ("*-math/svg").
 * @param[out]	docout		The output file to print into.
 */
static void printDocDgm(const Tree expr, const char* svgTopDir, ostream& docout, int i)
{
    /** 1. Evaluate expression. */
    Tree docdgm = evaldocexpr(expr, gGlobal->gExpandedDefList);
    if (gGlobal->gErrorCount > 0) {
        stringstream error;
        error << "ERROR : total of " << gGlobal->gErrorCount
              << " errors during evaluation of : diagram docdgm = " << boxpp(docdgm) << ";\n";
        throw faustexception(error.str());
    }

    /**
     * 2. Draw the diagram after its evaluation, in SVG.
     * Warning : pdflatex can't directly include SVG files !
     */
    char dgmid[MAXIDCHARS + 1];
    snprintf(dgmid, sizeof(dgmid), "%02d", i);
    string thisdgmdir = subst("$0/svg-$1", svgTopDir, dgmid);
    // cerr << "Documentator : printDocDgm : drawSchema in '" << gCurrentDir << "/" << thisdgmdir <<
    // "'" << endl;

    drawSchema(docdgm, thisdgmdir.c_str(), "svg");

    /** 3. Print LaTeX figure code. */
    char         temp[1024];
    const string dgmfilename = legalFileName(docdgm, 1024, temp);
    // docout << "figure \\ref{figure" << i << "}";
    docout << "\\begin{figure}[ht!]" << endl;
    docout << "\t\\centering" << endl;
    docout << "\t\\includegraphics[width=\\textwidth]{" << subst("../svg/svg-$0/", dgmid)
           << dgmfilename << "}" << endl;
    docout << "\t\\caption{" << gGlobal->gDocMathStringMap["dgmcaption"] << " \\texttt{"
           << dgmfilename << "}}" << endl;
    docout << "\t\\label{figure" << i << "}" << endl;
    docout << "\\end{figure}" << endl << endl;

    /** 4. Warn about naming interferences (in the notice). */
    gGlobal->gDocNoticeFlagMap["nameconflicts"] = true;
    gGlobal->gDocNoticeFlagMap["svgdir"]        = true;
}

/*****************************************************************************
                            Other sub-functions
 *****************************************************************************/
/**
 * Slice faust code between "mdoc" sections.
 *
 * @param[in]	faustfile	Name of the input faust file to parse.
 * @param[in]	codeSlices	The place to store code "slices".
 */
vector<string>& docCodeSlicer(const string& faustfile, vector<string>& codeSlices)
{
    string   s;
    ifstream src;
    src.open(faustfile.c_str(), ifstream::in);
    string tmp = "";

    bool isInsideDoc = false;

    if (faustfile != "" && src.good()) {
        while (getline(src, s)) { /** Caution: we suppose there's only one <mdoc> tag per line! */
            size_t foundopendoc = s.find("<mdoc>");

            if (foundopendoc != string::npos) {
                if (isInsideDoc == false) { /** A change has come. ;) */
                    if (!tmp.empty()) {
                        codeSlices.push_back(tmp);
                    }
                    tmp = "";
                }
                isInsideDoc = true;
            }

            if (isInsideDoc == false) {
                tmp += s + '\n';
            }

            size_t foundclosedoc = s.find("</mdoc>");
            if (foundclosedoc != string::npos) {
                isInsideDoc = false;
            }
        }
    } else {
        stringstream error;
        error << "ERROR : can't open Faust source file " << faustfile << endl;
        throw faustexception(error.str());
    }
    return codeSlices;
}

/**
 * Print faust code inside a listing environment.
 *
 * @param[in]	code		Faust code as a string (may contain '\n' characters).
 * @param[out]	docout		The output file to print into.
 */
static void printdocCodeSlices(const string& code, ostream& docout)
{
    if (!code.empty()) {
        docout << endl
               << "\\begin{lstlisting}[numbers=none, frame=none, basicstyle=\\small\\ttfamily, "
                  "backgroundcolor=\\color{yobg}]"
               << endl;
        docout << code << endl;
        docout << "\\end{lstlisting}" << endl << endl;
    }
}

/**
 * Test whether a file does begin with some faust code or not.
 *
 * @param[in]	faustfile	Name of the input faust file to parse.
 */
static bool doesFileBeginWithCode(const string& faustfile)
{
    string   s;
    ifstream src;
    src.open(faustfile.c_str(), ifstream::in);

    if (faustfile != "" && src.good()) {
        getline(src, s);
        size_t foundopendoc = s.find("<mdoc>");
        if (int(foundopendoc) == 0) {
            return false;
        } else {
            return true;
        }
    } else {
        stringstream error;
        error << "ERROR : can't open Faust source file " << faustfile << endl;
        throw faustexception(error.str());
    }
}

/*
 * Open architecture file.
 */
static unique_ptr<ifstream> openArchFile(const string& filename)
{
    unique_ptr<ifstream> file;
    getCurrentDir();  // Save the current directory.
    // cerr << "Documentator : openArchFile : Opening input file  '" << filename << "'" << endl;
    if ((file = openArchStream(filename.c_str()))) {
        // cerr << "Documentator : openArchFile : Opening '" << filename << "'" << endl;
    } else {
        stringstream error;
        error << "ERROR : can't open architecture file " << filename << endl;
        throw faustexception(error.str());
    }
    choldDir();  // Return to current directory.
    return file;
}

/**
 * Transform the definition name property of tree <t> into a
 * legal file name.  The resulting file name is stored in
 * <dst> a table of at least <n> chars. Returns the <dst> pointer
 * for convenience.
 */
static char* legalFileName(const Tree t, int n, char* dst)
{
    Tree id;
    int  i = 0;
    if (getDefNameProperty(t, id)) {
        const char* src = tree2str(id);
        for (i = 0; isalnum(src[i]) && i < 16; i++) {
            dst[i] = src[i];
        }
    }
    dst[i] = 0;
    if (strcmp(dst, "process") != 0) {
        // if it is not process add the hex address to make the name unique
        snprintf(&dst[i], n - i, "-%p", (void*)t);
    }
    return dst;
}

/**
 * Simply concat a string with a number in a "%03d" format.
 * The number has MAXIDCHARS characters.
 **/
static string calcNumberedName(const char* base, int i)
{
    char nb[MAXIDCHARS + 1];
    snprintf(nb, sizeof(nb), "%03d", i);
    return subst("$0$1", base, nb);
}

/**
 * Copy all Faust source files into an 'src' subdirectory.
 *
 * @param[in]	projname		Basename of the new doc directory ("*-math").
 * @param[in]	pathnames		The paths list of the source files to copy.
 */
static void copyFaustSources(const char* projname, const vector<string>& pathnames)
{
    string srcdir = subst("$0/src", projname);
    // cerr << "Documentator : copyFaustSources : Creating directory '" << srcdir << "'" << endl;
    makeDir(srcdir.c_str());  // create a directory.

    for (unsigned int i = 0; i < pathnames.size(); i++) {
        ifstream src;
        ofstream dst;
        string   faustfile = pathnames[i];
        string   copy      = subst("$0/$1", srcdir, fileBasename(faustfile.c_str()));
        // cerr << "Documentator : copyFaustSources : Opening input file  '" << faustfile << "'" <<
        // endl; cerr << "Documentator : copyFaustSources : Opening output file '" << copy << "'" <<
        // endl;
        src.open(faustfile.c_str(), ifstream::in);
        dst.open(copy.c_str(), ofstream::out);
        string s;
        while (getline(src, s)) {
            dst << s << endl;
        }
    }
}

//------------------------ date managment -------------------------

static void initCompilationDate()
{
    time_t now;
    time(&now);
    gGlobal->gCompilationDate = *localtime(&now);
}

static struct tm* getCompilationDate()
{
    initCompilationDate();
    return &gGlobal->gCompilationDate;
}
