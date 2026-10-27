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

/*****************************************************************************
******************************************************************************
                            FAUST SIGNAL COMPILER
                        Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Compile a list of FAUST signals into a C++ class.

 History :
 ---------
    2002-02-08 : First version

******************************************************************************
*****************************************************************************/

#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include "compile.hh"
#include <vector>
#include <unordered_set>
#include "ppsig.hh"
#include "sigattributes.hh"
#include "exception.hh"
#include "sigs-state.hh"
#include "floats.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "timing.hh"
#include "rewrite.hh"
#include "prim2.hh"
#include "sigtypesolver.hh"
#include "sigPromotion.hh"

using namespace std;

/*****************************************************************************
******************************************************************************

                                    API

******************************************************************************
*****************************************************************************/

/*****************************************************************************
******************************************************************************

                          GENERAL COMPILER METHODS

******************************************************************************
*****************************************************************************/

std::string nameDelayType(DelayType dt)
{
    static std::string delayTypeName[] = {"kNotADelay",     "kZeroDelay",      "kMonoDelay",
                                          "kSingleDelay",   "kCopyDelay",      "kDenseDelay",
                                          "kMaskRingDelay", "kSelectRingDelay"};
    return delayTypeName[int(dt)];
}

/*****************************************************************************
                               constructor
*****************************************************************************/

string certifiedDuration(double samples)
{
    auto seconds = [](double s) {
        std::stringstream d;
        if (s >= 10) {
            d << std::llround(s);
        } else {
            d << std::setprecision(2) << s;
        }
        return d.str();
    };
    return seconds(samples / 48000.0) + " seconds at 48000 Hz (" + seconds(samples / 192000.0) +
           " seconds at 192000 Hz)";
}

void checkLightTypes(Tree L)
{
    if (getenv("FAUST_CHECK_LIGHT_TYPES") == nullptr) {
        return;
    }
    const ExactSolvers        exact(L);
    std::unordered_set<Tree> seen;
    std::vector<Tree>        work{L};
    int                      signals = 0, differ = 0;
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) continue;
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body) work.push_back(body);
            continue;
        }
        for (int i = 0; i < t->arity(); i++) work.push_back(t->branch(i));
        ::Type ty = getSigType(t);
        if (!ty) continue;
        signals++;
        const bool same = ty->nature() == exact.nature(t) && ty->variability() == exact.variability(t) &&
                          ty->computability() == exact.computability(t) &&
                          ty->vectorability() == exact.vectorability(t) && ty->boolean() == exact.booleanity(t);
        if (!same) {
            if (differ < 10) {
                cerr << "light type differs : " << ty->nature() << "/" << exact.nature(t) << " "
                     << ty->variability() << "/" << exact.variability(t) << " " << ty->computability() << "/"
                     << exact.computability(t) << " " << ty->vectorability() << "/" << exact.vectorability(t)
                     << " " << ty->boolean() << "/" << exact.booleanity(t) << " : " << ppsig(t, 10) << endl;
            }
            differ++;
        }
    }
    cerr << "light types : " << signals << " signals, " << differ << " differ" << endl;
}

static const char* kCertifiedWarning = "WARNING : this program is certified for ";
static const char* kFastMathWarning =
    "WARNING : -fm computes mathematical functions by approximations that the interval "
    "analysis does not bound : the certification of this program does not cover them\n";
static const char* kNoRangeUIWarning =
    "WARNING : -norui leaves the controls as the host writes them, while the certification "
    "assumes the sliders and numerical entries within their declared range and the buttons "
    "and checkboxes at 0 or 1 : other values are not covered\n";

bool isCertificationWarning(const std::string& warning)
{
    // the waivers of -nocert end with the name of the option
    return warning.rfind(kCertifiedWarning, 0) == 0 || warning == kFastMathWarning ||
           warning == kNoRangeUIWarning || warning.find("(-nocert)") != std::string::npos;
}

void checkCertificates()
{
    const double seconds = gGlobal->gMinCertifiedSeconds;
    for (const auto& [reason, samples] : sigs::g.gCertifiedSamples) {
        if (samples < seconds * 48000.0 && !gGlobal->gNoCert) {
            std::stringstream error;
            error << "ERROR : this program is certified for only " << certifiedDuration(samples) << " ("
                  << reason << ") : at least " << seconds << " seconds at 48000 Hz are required (-mcs)"
                  << endl
                  << kIntervalRefusalHint;
            throw faustexception(error.str());
        }
    }
    // a program bounded only for a limited time says for how long
    for (const auto& [reason, samples] : sigs::g.gCertifiedSamples) {
        std::stringstream warning;
        warning << kCertifiedWarning << certifiedDuration(samples) << " (" << reason << ")" << endl;
        gWarningMessages.push_back(warning.str());
    }
    // -nocert : what was accepted although the analysis did not prove it
    for (const auto& waiver : sigs::g.gCertificationWaivers) {
        gWarningMessages.push_back(waiver);
    }
    // -fm replaces mathematical functions by approximations that the intervals do not bound
    if (gGlobal->gFastMathLib != "") {
        gWarningMessages.push_back(kFastMathWarning);
    }
    // -norui : the controls are not brought within the values the typing assumes
    if (!gGlobal->gRangeUI) {
        gWarningMessages.push_back(kNoRangeUIWarning);
    }
}

// The certified type of a signal, when it has one
static SimpleType* certifiedSimpleType(Tree t)
{
    ::Type ty = getSigType(t);
    return ty ? isSimpleType(ty.pointee()) : nullptr;
}

// The operands of t as the analysis reads them : a projection reads its definition
static std::vector<Tree> analysisOperands(Tree t)
{
    std::vector<Tree> ops;
    int               i, op;
    Tree              g, var, body, x, y;
    if (isProj(t, &i, g) && isRec(g, var, body) && body != nullptr && isList(body)) {
        ops.push_back(nth(body, i));
        return ops;
    }
    if (isSigBinOp(t, &op, x, y)) {
        return {x, y};
    }
    for (int k = 0; k < t->arity(); k++) {
        ops.push_back(t->branch(k));
    }
    return ops;
}

// A signal as a refusal prints it : ppsig stops at a position of its stream, so each one
// is printed in a stream of its own
static std::string showSignal(Tree t)
{
    std::stringstream s;
    s << ppsig(t, MAX_ERROR_SIZE);
    return s.str();
}

// An interval as a refusal prints it
static std::string showInterval(const interval& i)
{
    std::stringstream s;
    // an integer exactly, a real with the digits of the precision of the program
    auto bound = [](double b) {
        std::stringstream d;
        if (std::isfinite(b) && b == std::trunc(b) && std::fabs(b) < 0x1p53) {
            d << std::llround(b);
        } else {
            d << std::setprecision(gGlobal->gFloatSize == 1 ? 8 : 16) << b;
        }
        return d.str();
    };
    if (i.isEmpty()) {
        s << "no valid value";
    } else {
        s << "[" << bound(i.lo()) << ", " << bound(i.hi()) << "]";
    }
    if (!i.isEmpty() && i.mayBeInvalid()) {
        s << ", possibly invalid";
    }
    if (i.moves()) {
        s << ", a bound holding over the analysis horizon only";
    }
    return s.str();
}

// The program the certified typing bounded, from checkValidity to the -wall report, which
// runs after the generation of the code
static Tree gCertifiedRoots = nullptr;

void checkValidity(Tree roots)
{
    gCertifiedRoots = roots;
    std::unordered_set<Tree> seen;
    std::vector<Tree>        work{roots};
    std::vector<Tree>        certain;  // the signals without a valid value, as found
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) continue;
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body) work.push_back(body);
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            work.push_back(t->branch(k));
        }
        SimpleType* st = certifiedSimpleType(t);
        if (!st) continue;
        const interval it = st->getInterval();
        if (it.isEmpty() && it.mayBeInvalid()) {
            certain.push_back(t);
        }
        int  op;
        Tree x, y;
        if (st->nature() == kInt && isSigBinOp(t, &op, x, y) && op == kRem) {
            SimpleType* sx = certifiedSimpleType(x);
            SimpleType* sy = certifiedSimpleType(y);
            if (!sx || !sy) continue;
            // the defined form of the normal form (sigPromotion.cpp) replaces a divisor 0 by 1 :
            // the divisor it guards decides, 0 excepted
            Tree guarded;
            bool guards0 = isGuardedDivisor(y, guarded);
            if (guards0) {
                if (SimpleType* sg = certifiedSimpleType(guarded)) sy = sg;
            }
            const interval ix      = sx->getInterval();
            const interval iy      = sy->getInterval();
            const bool     zero    = mayBeInteger(iy, 0) && !guards0;
            const bool     extreme = mayBeInteger(ix, double(INT32_MIN)) && mayBeInteger(iy, -1);
            if (zero || extreme) {
                std::stringstream error;
                error << "ERROR : an integer remainder may stop the execution, "
                      << (zero ? "its divisor may be 0" : "it may compute -2147483648 % -1") << " : "
                      << showSignal(t) << endl
                      << "        dividend " << showSignal(x) << " in " << showInterval(ix)
                      << endl
                      << "        divisor " << showSignal(y) << " in " << showInterval(iy)
                      << endl
                      << kIntervalRefusalHint;
                throw faustexception(error.str());
            }
        }
    }
    // the source of a certain invalidity : a signal without a valid value whose operands
    // all have one, or the first one found when they all belong to a loop
    std::unordered_set<Tree> invalid(certain.begin(), certain.end());
    for (size_t n = 0; n < certain.size(); n++) {
        Tree t      = certain[n];
        bool source = true;
        for (Tree c : analysisOperands(t)) {
            if (invalid.count(c)) {
                source = false;
            }
        }
        if (!source && n + 1 < certain.size()) continue;
        if (!source) t = certain.front();
        std::stringstream error;
        error << "ERROR : a signal has no valid value, it is always NaN or an undefined operation : "
              << showSignal(t) << endl;
        for (Tree c : analysisOperands(t)) {
            if (SimpleType* sc = certifiedSimpleType(c)) {
                error << "        operand " << showSignal(c) << " in "
                      << showInterval(sc->getInterval()) << endl;
            }
        }
        error << kIntervalRefusalHint;
        throw faustexception(error.str());
    }
}

void reportNumericCertificate()
{
    Tree roots      = gCertifiedRoots;
    gCertifiedRoots = nullptr;
    if (!gAllWarning || roots == nullptr) return;
    std::stringstream report;
    try {
        // the hypothesis on the audio inputs, written as a bound in a copy of the program ;
        // the copy renames its recursive groups, the compiled program keeps its definitions
        std::unordered_map<Tree, Tree> memo;
        auto bound = [](Tree t) -> Tree {
            int i;
            if (isSigInput(t, &i)) {
                Tree hi = sigMin(sigReal(1.0), t);
                return sigMax(sigReal(-1.0), hi);
            }
            return t;
        };
        Tree                           H = treeRewriteMemo(roots, bound, memo);
        std::unordered_map<Tree, Tree> original;  // a signal of the copy, printed as written
        for (const auto& [o, h] : memo) {
            original[h] = o;
        }
        std::unordered_set<Tree> inputs;  // a bounded audio input : a hypothesis, not a signal to report
        for (const auto& [o, h] : memo) {
            int n;
            if (isSigInput(o, &n)) inputs.insert(h);
        }
        auto shown = [&](Tree h) {
            auto it = original.find(h);
            return showSignal(it != original.end() ? it->second : h);
        };

        TypeSolver solver(H);
        auto       bad = [&](Tree t, bool& invalid, bool& infinite) {
            if (!solver.isSignal(t)) return false;
            const interval i = solver.interval(t);
            invalid          = i.mayBeInvalid();
            infinite = !invalid && solver.type(t)->nature() == kReal && !i.isEmpty() &&
                       (std::isinf(i.lo()) || std::isinf(i.hi()));
            return invalid || infinite;
        };
        auto operands = [&](Tree t) {
            std::stringstream s;
            const char*       sep = "";
            for (Tree c : analysisOperands(t)) {
                if (solver.isSignal(c)) {
                    s << sep << showInterval(solver.interval(c));
                    sep = ", ";
                }
            }
            return s.str();
        };

        std::set<Tree>           outputs;
        std::unordered_set<Tree> seen;
        std::vector<Tree>        work;
        for (Tree l = H; isList(l); l = tl(l)) {
            outputs.insert(hd(l));
        }
        work.push_back(H);
        std::vector<std::string> sources, foreign, lines;
        std::vector<Tree>        carriers;  // the bad signals whose operands are bad too
        int  invalids = 0, infinites = 0;
        bool output = false, bargraph = false;
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) continue;
            Tree var, body, ff, largs;
            if (isRec(t, var, body)) {
                if (body) work.push_back(body);
                continue;
            }
            if (inputs.count(t)) continue;
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
            bool invalid, infinite;
            const bool wrong = bad(t, invalid, infinite);
            if (wrong) {
                (invalid ? invalids : infinites)++;
                output   = output || outputs.count(t);
                bargraph = bargraph || isSigHBargraph(t) || isSigVBargraph(t);
            }
            // a foreign function is not certified, whatever its interval
            if (isSigFFun(t, ff, largs)) {
                foreign.push_back("foreign function " + std::string(ffname(ff)) + ", whose domain is unknown : " +
                                  shown(t));
                continue;
            }
            if (!wrong) continue;
            // a source : no operand invalid, and for an infinity no operand infinite ; an
            // audio input is a hypothesis, not a source
            int  n;
            bool source = !isSigInput(t, &n);
            for (Tree c : analysisOperands(t)) {
                bool ci, cf;
                if (bad(c, ci, cf) && (ci || !invalid)) source = false;
            }
            Tree rx, ry, guarded;
            int  rop;
            if (source && isSigBinOp(t, &rop, rx, ry) && rop == kRem && isGuardedDivisor(ry, guarded)) {
                // the defined form of an integer remainder : the divisor it guards
                sources.push_back("an integer remainder whose divisor may be 0, where it gives 0 : " + shown(rx) +
                                  " % " + shown(guarded) + " ; divisor in " + showInterval(solver.interval(guarded)));
            } else if (source && (isSigIIR(t) || isSigIRM(t))) {
                // a revealed recursion : the coefficients are its operands
                sources.push_back("a recursion the analysis does not prove contracting : " + shown(t) +
                                  " ; operands in " + operands(t));
            } else if (source) {
                sources.push_back(std::string(invalid ? "may be NaN or undefined" : "may be infinite") + " : " +
                                  shown(t) + " ; operands in " + operands(t));
            } else {
                carriers.push_back(t);
            }
        }
        lines = sources;
        if (sources.empty() && !carriers.empty()) {
            // a recursion without a source outside it : its first recursive signal, and the
            // factor, the coefficient or the weight that the analysis could not bound, a
            // valid operand that is neither a constant nor an audio input
            Tree rec = nullptr, factor = nullptr;
            for (Tree t : carriers) {
                int  i;
                Tree g;
                if (rec == nullptr && isProj(t, &i, g)) rec = t;
                for (Tree c : analysisOperands(t)) {
                    bool   ci, cf;
                    int    iv;
                    double rv;
                    if (factor == nullptr && solver.isSignal(c) && !inputs.count(c) && !bad(c, ci, cf) &&
                        !isSigInt(c, &iv) && !isSigReal(c, &rv)) {
                        factor = c;
                    }
                }
            }
            std::string line =
                "a recursion the analysis does not prove contracting : " + shown(rec ? rec : carriers.front());
            if (factor) line += " ; operand " + shown(factor) + " in " + showInterval(solver.interval(factor));
            lines.push_back(line);
        }
        lines.insert(lines.end(), foreign.begin(), foreign.end());
        if (lines.empty() && invalids + infinites == 0) return;
        report << "WARNING : this program is not certified free of NaN and infinity, under the "
                  "assumptions of the certificate (audio inputs within [-1, 1], controls within "
                  "their ranges) :"
               << endl;
        for (size_t k = 0; k < lines.size() && k < 3; k++) {
            report << "        " << lines[k] << endl;
        }
        report << "        " << invalids << (invalids == 1 ? " signal" : " signals") << " may be NaN or undefined, "
               << infinites << " may be infinite" << (output ? " ; an output is concerned" : "")
               << (bargraph ? " ; a bargraph is concerned" : "")
               << ((output || bargraph) ? "" : " ; no output nor bargraph is concerned") << endl;
    } catch (faustexception& e) {
        report << "WARNING : the numeric certificate could not be checked : " << e.what();
    }
    gWarningMessages.push_back(report.str());
}

void dumpEquations(Tree L)
{
    try {
        typeAnnotation(L, false);
    } catch (faustexception&) {
    }
    ppsigEquations(L, cout);
    throw faustexception("Dump normal form finished...\n");
}

Compiler::Compiler(const string& name, const string& super, int numInputs, int numOutputs, bool vec)
    : fClass(new Klass(name, super, numInputs, numOutputs, vec)),
      fNeedToDeleteClass(true),
      fUIRoot(uiFolder(cons(tree(0), tree("")))),
      fDescription(0),
      fJSON(numInputs, numOutputs)
{
    fClass->addIncludeFile("<math.h>");
}

Compiler::Compiler(Klass* k)
    : fClass(k),
      fNeedToDeleteClass(false),
      fUIRoot(uiFolder(cons(tree(0), tree("")))),
      fDescription(0),
      fJSON(k->inputs(), k->outputs())
{
}

Compiler::~Compiler()
{
    if (fNeedToDeleteClass) {
        delete fClass;
    }
}

/*****************************************************************************
                            user interface elements
*****************************************************************************/

//================================= some string processing utilities
//=================================

/**
 * Removes enclosing whitespaces : '  toto  ' -> 'toto'
 */
static string wdel(const string& s)
{
    size_t i = 0;
    size_t j = s.size();
    while (i < j && s[i] == ' ') {
        i++;
    }
    while (j > i && s[j - 1] == ' ') {
        j--;
    }
    return s.substr(i, j - i);
}

//================================= BUILD USER INTERFACE METHOD =================================

void Compiler::generateMetaData()
{
    // Add global metadata
    for (map<Tree, set<Tree, treeorder>, comp_str>::iterator i = gGlobal->gMetaDataSet.begin();
         i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            stringstream str1, str2;
            str1 << *(i->first);
            str2 << **(i->second.begin());
            string res1 = str1.str();
            string res2 = unquote(str2.str());
            fJSON.declare(res1.c_str(), res2.c_str());
        } else {
            for (set<Tree, treeorder>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    stringstream str1, str2;
                    str1 << *(i->first);
                    str2 << **j;
                    string res1 = str1.str();
                    string res2 = unquote(str2.str());
                    fJSON.declare(res1.c_str(), res2.c_str());
                } else {
                    stringstream str2;
                    str2 << **j;
                    string res2 = unquote(str2.str());
                    fJSON.declare("contributor", res2.c_str());
                }
            }
        }
    }
}

/**
 * Generate buildUserInterface C++ lines of code corresponding
 * to user interface element t
 */
void Compiler::generateUserInterfaceTree(Tree t, bool root)
{
    Tree label, elements, varname, sig;

    if (isUiFolder(t, label, elements)) {
        const int orient = tree2int(left(label));
        // Empty labels will be renamed with a 0xABCD (address) kind of name that is ignored and not
        // displayed by UI architectures
        const char* str   = tree2str(right(label));
        const char* model = nullptr;

        // extract metadata from group label str resulting in a simplifiedLabel
        // and metadata declarations for fictive zone at address 0
        string                   simplifiedLabel;
        map<string, set<string>> metadata;
        extractMetadata(str, simplifiedLabel, metadata);

        // add metadata if any
        for (map<string, set<string>>::iterator i = metadata.begin(); i != metadata.end(); i++) {
            const string&      key    = i->first;
            const set<string>& values = i->second;
            for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
                fClass->addUICode(
                    subst("ui_interface->declare($0, \"$1\", \"$2\");", "0", wdel(key), wdel(*j)));
                fJSON.declare(NULL, wdel(key).c_str(), wdel(*j).c_str());
            }
        }

        // At root level and if label is empty, use the name kept in "metadata" (either the one
        // coded in 'declare name "XXX";' line, or the filename)
        string group = (root && (simplifiedLabel == ""))
                           ? unquote(tree2str(*(gGlobal->gMetaDataSet[tree("name")].begin())))
                           : checkNullLabel(t, simplifiedLabel);
        switch (orient) {
            case 0:
                model = "ui_interface->openVerticalBox(\"$0\");";
                fJSON.openVerticalBox(group.c_str());
                break;
            case 1:
                model = "ui_interface->openHorizontalBox(\"$0\");";
                fJSON.openHorizontalBox(group.c_str());
                break;
            case 2:
                model = "ui_interface->openTabBox(\"$0\");";
                fJSON.openTabBox(group.c_str());
                break;
            default:
                cerr << "ASSERT : user interface generation 1\n";
                faustassert(false);
                break;
        }

        fClass->addUICode(subst(model, group));
        generateUserInterfaceElements(elements);
        fClass->addUICode("ui_interface->closeBox();");
        fJSON.closeBox();

    } else if (isUiWidget(t, label, varname, sig)) {
        generateWidgetCode(label, varname, sig);
    } else {
        cerr << "ASSERT : user interface generation 2\n";
        faustassert(false);
    }
}

/**
 * Iterate generateUserInterfaceTree on a list of user interface elements
 */
void Compiler::generateUserInterfaceElements(Tree elements)
{
    while (!isNil(elements)) {
        generateUserInterfaceTree(right(hd(elements)));
        elements = tl(elements);
    }
}

/////////////////////////////////////////////////

/**
 * Generate buildUserInterface C++ lines of code corresponding
 * to user interface widget t
 */
void Compiler::generateWidgetCode(Tree fulllabel, Tree varname, Tree sig)
{
    Tree                     path, c, x, y, z;
    map<string, set<string>> metadata;
    string                   label, url;

    extractMetadata(tree2str(fulllabel), label, metadata);

    // Extract "url" metadata to be given as parameter to 'addSoundfile' function
    if (isSigSoundfile(sig, path)) {
        for (map<string, set<string>>::iterator i = metadata.begin(); i != metadata.end(); i++) {
            string      key    = i->first;
            set<string> values = i->second;
            for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
                if (key == "url") {
                    url = prepareURL(*j);
                }
            }
        }
    } else {
        // Add metadata if any
        for (map<string, set<string>>::iterator i = metadata.begin(); i != metadata.end(); i++) {
            const string&      key    = i->first;
            const set<string>& values = i->second;
            for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
                fClass->addUICode(subst("ui_interface->declare(&$0, \"$1\", \"$2\");",
                                        tree2str(varname), wdel(key), wdel(*j)));
                fJSON.declare(NULL, wdel(key).c_str(), wdel(*j).c_str());
            }
        }
    }

    if (isSigButton(sig, path)) {
        fClass->incUIActiveCount();
        fClass->addUICode(subst("ui_interface->addButton(\"$0\", &$1);",
                                checkNullLabel(varname, label), tree2str(varname)));
        fJSON.addButton(checkNullLabel(varname, label).c_str(), NULL);

    } else if (isSigCheckbox(sig, path)) {
        fClass->incUIActiveCount();
        fClass->addUICode(subst("ui_interface->addCheckButton(\"$0\", &$1);",
                                checkNullLabel(varname, label), tree2str(varname)));
        fJSON.addCheckButton(checkNullLabel(varname, label).c_str(), NULL);

    } else if (isSigVSlider(sig, path, c, x, y, z)) {
        fClass->incUIActiveCount();
        fClass->addUICode(subst("ui_interface->addVerticalSlider(\"$0\", &$1, $2, $3, $4, $5);",
                                checkNullLabel(varname, label), tree2str(varname),
                                T(tree2double(c)), T(tree2double(x)), T(tree2double(y)),
                                T(tree2double(z))));
        fJSON.addVerticalSlider(checkNullLabel(varname, label).c_str(), NULL, (float)tree2double(c),
                                (float)tree2double(x), (float)tree2double(y),
                                (float)tree2double(z));

    } else if (isSigHSlider(sig, path, c, x, y, z)) {
        fClass->incUIActiveCount();
        fClass->addUICode(subst("ui_interface->addHorizontalSlider(\"$0\", &$1, $2, $3, $4, $5);",
                                checkNullLabel(varname, label), tree2str(varname),
                                T(tree2double(c)), T(tree2double(x)), T(tree2double(y)),
                                T(tree2double(z))));
        fJSON.addHorizontalSlider(checkNullLabel(varname, label).c_str(), NULL,
                                  (float)tree2double(c), (float)tree2double(x),
                                  (float)tree2double(y), (float)tree2double(z));

    } else if (isSigNumEntry(sig, path, c, x, y, z)) {
        fClass->incUIActiveCount();
        fClass->addUICode(subst("ui_interface->addNumEntry(\"$0\", &$1, $2, $3, $4, $5);",
                                checkNullLabel(varname, label), tree2str(varname),
                                T(tree2double(c)), T(tree2double(x)), T(tree2double(y)),
                                T(tree2double(z))));
        fJSON.addNumEntry(checkNullLabel(varname, label).c_str(), NULL, (float)tree2double(c),
                          (float)tree2double(x), (float)tree2double(y), (float)tree2double(z));

    } else if (isSigVBargraph(sig, path, x, y, z)) {
        fClass->incUIPassiveCount();
        fClass->addUICode(subst("ui_interface->addVerticalBargraph(\"$0\", &$1, $2, $3);",
                                checkNullBargraphLabel(varname, label, 1), tree2str(varname),
                                T(tree2double(x)), T(tree2double(y))));
        fJSON.addVerticalBargraph(checkNullLabel(varname, label).c_str(), NULL,
                                  (float)tree2double(x), (float)tree2double(y));

    } else if (isSigHBargraph(sig, path, x, y, z)) {
        fClass->incUIPassiveCount();
        fClass->addUICode(subst("ui_interface->addHorizontalBargraph(\"$0\", &$1, $2, $3);",
                                checkNullBargraphLabel(varname, label, 0), tree2str(varname),
                                T(tree2double(x)), T(tree2double(y))));
        fJSON.addHorizontalBargraph(checkNullLabel(varname, label).c_str(), NULL,
                                    (float)tree2double(x), (float)tree2double(y));

    } else if (isSigSoundfile(sig, path)) {
        fClass->incUIActiveCount();
        fClass->addUICode(subst(
            "ui_interface->addSoundfile(\"$0\", \"$1\", &$2);", checkNullLabel(varname, label),
            ((url == "") ? prepareURL(label).c_str() : url.c_str()), tree2str(varname)));
        fJSON.addSoundfile(checkNullLabel(varname, label).c_str(),
                           ((url == "") ? prepareURL(label).c_str() : url.c_str()), NULL);
    } else {
        cerr << "ASSERT : generating widget code 3\n";
        faustassert(false);
    }
}

//==================================== USER INTERFACE MACROS ==================================

/**
 * Generate user interface macros corresponding
 * to user interface element t
 */
void Compiler::generateMacroInterfaceTree(const string& pathname, Tree t)
{
    Tree label, elements, varname, sig;

    if (isUiFolder(t, label, elements)) {
        string pathname2 = pathname;
        string str       = tree2str(right(label));
        if (str.length() > 0) {
            pathname2 += str + "/";
        }
        generateMacroInterfaceElements(pathname2, elements);
    } else if (isUiWidget(t, label, varname, sig)) {
        generateWidgetMacro(pathname, label, varname, sig);
    } else {
        cerr << "ASSERT : user interface macro generation 2\n";
        faustassert(false);
    }
}

/**
 * Iterate generateMacroInterfaceTree on a list of user interface elements
 */
void Compiler::generateMacroInterfaceElements(const string& pathname, Tree elements)
{
    while (!isNil(elements)) {
        generateMacroInterfaceTree(pathname, right(hd(elements)));
        elements = tl(elements);
    }
}

/**
 * Generate user interface macros corresponding
 * to a user interface widget
 */
void Compiler::generateWidgetMacro(const string& pathname, Tree fulllabel, Tree varname, Tree sig)
{
    Tree                     path, c, x, y, z;
    string                   label;
    map<string, set<string>> metadata;

    extractMetadata(tree2str(fulllabel), label, metadata);
    string pathlabel = pathname + label;

    if (isSigButton(sig, path)) {
        fClass->addUIMacro(subst("FAUST_ADDBUTTON(\"$0\", $1);", pathlabel, tree2str(varname)));

    } else if (isSigCheckbox(sig, path)) {
        fClass->addUIMacro(subst("FAUST_ADDCHECKBOX(\"$0\", $1);", pathlabel, tree2str(varname)));

    } else if (isSigVSlider(sig, path, c, x, y, z)) {
        fClass->addUIMacro(subst("FAUST_ADDVERTICALSLIDER(\"$0\", $1, $2, $3, $4, $5);", pathlabel,
                                 tree2str(varname), T(tree2double(c)), T(tree2double(x)),
                                 T(tree2double(y)), T(tree2double(z))));

    } else if (isSigHSlider(sig, path, c, x, y, z)) {
        fClass->addUIMacro(subst("FAUST_ADDHORIZONTALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
                                 pathlabel, tree2str(varname), T(tree2double(c)), T(tree2double(x)),
                                 T(tree2double(y)), T(tree2double(z))));

    } else if (isSigNumEntry(sig, path, c, x, y, z)) {
        fClass->addUIMacro(subst("FAUST_ADDNUMENTRY(\"$0\", $1, $2, $3, $4, $5);", pathlabel,
                                 tree2str(varname), T(tree2double(c)), T(tree2double(x)),
                                 T(tree2double(y)), T(tree2double(z))));

    } else if (isSigVBargraph(sig, path, x, y, z)) {
        fClass->addUIMacro(subst("FAUST_ADDVERTICALBARGRAPH(\"$0\", $1, $2, $3);", pathlabel,
                                 tree2str(varname), T(tree2double(x)), T(tree2double(y))));

    } else if (isSigHBargraph(sig, path, x, y, z)) {
        fClass->addUIMacro(subst("FAUST_ADDHORIZONTALBARGRAPH(\"$0\", $1, $2, $3);", pathlabel,
                                 tree2str(varname), T(tree2double(x)), T(tree2double(y))));

    } else if (isSigSoundfile(sig, path)) {
        fClass->addUIMacro(subst("FAUST_ADDSOUNDFILE(\"$0\", $1);", pathlabel, tree2str(varname)));

    } else {
        cerr << "ASSERT in generating widget macro\n";
        faustassert(false);
    }
}
