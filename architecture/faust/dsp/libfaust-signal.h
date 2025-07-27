/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 **************************************************************************/

#include <string>
#include <vector>
#include <ostream>
#include <limits>

#ifndef LIBFAUSTCOMMON_H
#define LIBFAUSTCOMMON_H

#include "faust/export.h"

/*!
 \addtogroup signalcpp C++ interface for the Signal API.
 @{
 */

/**
 * Opaque types.
 */
class LIBFAUST_API CTree;
typedef std::vector<CTree*> tvec;

typedef CTree* Signal;
typedef CTree* Box;
typedef CTree* Tree;

typedef Tree (*prim0)();
typedef Tree (*prim1)(Tree x);
typedef Tree (*prim2)(Tree x, Tree y);
typedef Tree (*prim3)(Tree x, Tree y, Tree z);
typedef Tree (*prim4)(Tree w, Tree x, Tree y, Tree z);
typedef Tree (*prim5)(Tree v, Tree w, Tree x, Tree y, Tree z);

LIBFAUST_API const char* prim0name(prim0);
LIBFAUST_API const char* prim1name(prim1);
LIBFAUST_API const char* prim2name(prim2);
LIBFAUST_API const char* prim3name(prim3);
LIBFAUST_API const char* prim4name(prim4);
LIBFAUST_API const char* prim5name(prim5);

/**
 *  Return the name parameter of a foreign function.
 *
 * @param  s - the signal
 * @return the name
 */
LIBFAUST_API const char* ffname(Signal s);

/**
 *  Return the arity of a foreign function.
 *
 * @param  s - the signal
 * @return the name
 */
LIBFAUST_API int ffarity(Signal s);

enum SType { kSInt, kSReal };

typedef std::vector<SType> svec;

typedef std::vector<std::string> nvec;

enum SOperator { kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };

/**
 * Base class for factories.
 */
struct LIBFAUST_API dsp_factory_base {
    
    virtual ~dsp_factory_base() {}
    
    virtual void write(std::ostream* /*out*/, bool /*binary*/ = false, bool /*compact*/ = false) {}
};

/**
 * Print the box.
 *
 * @param box - the box to be printed
 * @param shared - whether the identical sub boxes are printed as identifiers
 * @param max_size - the maximum number of characters to be printed (possibly needed for big expressions in non shared mode)
 *
 * @return the printed box as a string
 */
LIBFAUST_API std::string printBox(Box box, bool shared, int max_size);

/**
 * Print the signal.
 *
 * @param sig - the signal to be printed
 * @param shared - whether the identical sub signals are printed as identifiers
 * @param max_size - the maximum number of characters to be printed (possibly needed for big expressions in non shared mode)
 *
 * @return the printed signal as a string
 */
LIBFAUST_API std::string printSignal(Signal sig, bool shared, int max_size);

#endif

#ifndef LIBFAUSTSIGNAL_H
#define LIBFAUSTSIGNAL_H

// To be used with getSigInterval/setSigInterval
// see: https://stackoverflow.com/questions/27442885/syntax-error-with-stdnumeric-limitsmax
struct Interval {
    double fLo = std::numeric_limits<double>::lowest();    //< minimal value
    double fHi = (std::numeric_limits<double>::max)();     //< maximal value
    int    fLSB = -24;                                     //< lsb in bits
    
    // To be used to set a full interval
    Interval(double lo, double hi, int lsb):fLo(lo), fHi(hi), fLSB(lsb)
    {}
    
    // To be used to only set the LSB, with fLo and fHi taking default values
    Interval(int lsb):fLSB(lsb)
    {}
};

inline static std::ostream& operator<<(std::ostream& dst, const Interval& it)
{
    dst << "Interval [" << it.fLo << ", " << it.fHi << ", " << it.fLSB << "]";
    return dst;
}

/**
 * Create global compilation context, has to be done first,
 * and paired with a call to destroyLibContext().
 */
extern "C" LIBFAUST_API void createLibContext();

/**
 * Destroy global compilation context, has to be done last,
 * and paired with a call to createLibContext().
 * Note that the created DSP factory can be used outside
 * of the createLibContext/destroyLibContext scope.
 */
extern "C" LIBFAUST_API void destroyLibContext();

/**
 * Get the signal interval.
 * 
 * @param s - the signal
 * 
 * @return the signal interval
 */
LIBFAUST_API Interval getSigInterval(Signal s);

/**
 * Set the signal interval.
 * 
 * @param s - the signal
 * @param inter - the signal interval
 */
LIBFAUST_API void setSigInterval(Signal s, Interval& inter);

/**
 * Check if a signal is nil.
 *
 * @param s - the signal
 *
 * @return true if the signal is nil, otherwise false.
 */
LIBFAUST_API bool isNil(Signal s);

/**
 * Convert a signal (such as the label of a UI) to a string.
 *
 * @param s - the signal to convert
 *
 * @return a string representation of a signal.
 */
LIBFAUST_API const char* tree2str(Signal s);

/**
 * Return the xtended type of a signal.
 *
 * @param s - the signal whose xtended type to return
 *
 * @return a pointer to xtended type if it exists, otherwise nullptr.
 */
LIBFAUST_API void* getUserData(Signal s);

/**
 * Return the arity of the xtended signal.
 *
 * @param s - the xtended signal
 *
 * @return the arity of the xtended signal.
 */
LIBFAUST_API unsigned int xtendedArity(Signal s);

/**
 * Return the name of the xtended signal.
 *
 * @param s - the xtended signal
 *
 * @return the name of the xtended signal.
 */
LIBFAUST_API const char* xtendedName(Signal s);

/**
 * Constant integer : for all t, x(t) = n.
 *
 * @param n - the integer
 *
 * @return the integer signal.
 */
LIBFAUST_API Signal sigInt(int n);

/**
 * Constant real : for all t, x(t) = n.
 *
 * @param n - the float/double value (depends of -single or -double compilation parameter)
 *
 * @return the float/double signal.
 */
LIBFAUST_API Signal sigReal(double n);

/**
 * Create an input.
 *
 * @param idx - the input index
 *
 * @return the input signal.
 */
LIBFAUST_API Signal sigInput(int idx);

/**
 * Create a delayed signal.
 *
 * @param s - the signal to be delayed
 * @param del - the delay signal that doesn't have to be fixed but must be bounded and cannot be negative
 *
 * @return the delayed signal.
 */
LIBFAUST_API Signal sigDelay(Signal s, Signal del);

/**
 * Create a one sample delayed signal.
 *
 * @param s - the signal to be delayed
 *
 * @return the delayed signal.
 */
LIBFAUST_API Signal sigDelay1(Signal s);

/**
 * Create a casted signal.
 *
 * @param s - the signal to be casted in integer
 *
 * @return the casted signal.
 */
LIBFAUST_API Signal sigIntCast(Signal s);

/**
 * Create a casted signal.
 *
 * @param s - the signal to be casted as float/double value (depends of -single or -double compilation parameter)
 *
 * @return the casted signal.
 */
LIBFAUST_API Signal sigFloatCast(Signal s);

/**
 * Create a read only table.
 *
 * @param n - the table size, a constant numerical expression (see [1])
 * @param init - the table content
 * @param ridx - the read index (an int between 0 and n-1)
 *
 * @return the table signal.
 */
LIBFAUST_API Signal sigReadOnlyTable(Signal n, Signal init, Signal ridx);

/**
 * Create a read/write table.
 *
 * @param n - the table size, a constant numerical expression (see [1])
 * @param init - the table content
 * @param widx - the write index (an integer between 0 and n-1)
 * @param wsig - the input of the table
 * @param ridx - the read index (an integer between 0 and n-1)
 *
 * @return the table signal.
 */
LIBFAUST_API Signal sigWriteReadTable(Signal n, Signal init, Signal widx, Signal wsig, Signal ridx);

/**
 * Create a waveform.
 *
 * @param wf - the content of the waveform as a vector of sigInt or sigDouble signals
 *
 * @return the waveform signal.
 */
LIBFAUST_API Signal sigWaveform(const tvec& wf);
// Use: sigInt(wf.size()); to generate the waveform size signal

/**
 * Create a soundfile block.
 *
 * @param label - of form "label[url:{'path1';'path2';'path3'}]" to describe a list of soundfiles
 *
 * @return the soundfile block.
 */
LIBFAUST_API Signal sigSoundfile(const std::string& label);

/**
 * Create the length signal of a given soundfile in frames.
 *
 * @param sf - the soundfile
 * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
 *
 * @return the soundfile length signal.
 */
LIBFAUST_API Signal sigSoundfileLength(Signal sf, Signal part);

/**
 * Create the rate signal of a given soundfile in Hz.
 *
 * @param sf - the soundfile
 * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
 *
 * @return the soundfile rate signal.
 */
LIBFAUST_API Signal sigSoundfileRate(Signal sf, Signal part);

/**
 * Create the buffer signal of a given soundfile.
 *
 * @param sf - the soundfile
 * @param chan - an integer to select a given channel, a constant numerical expression (see [1])
 * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
 * @param ridx - the read index (an integer between 0 and the selected sound length)
 *
 * @return the soundfile buffer signal.
 */
LIBFAUST_API Signal sigSoundfileBuffer(Signal sf, Signal chan, Signal part, Signal ridx);

/**
 * Create a selector between two signals.
 *
 * @param selector - when 0 at time t returns s1[t], otherwise returns s2[t]
 * (selector is automatically wrapped with sigIntCast)
 * @param s1 - first signal to be selected
 * @param s2 - second signal to be selected
 *
 * @return the selected signal depending of the selector value at each time t.
 */
LIBFAUST_API Signal sigSelect2(Signal selector, Signal s1, Signal s2);

/**
 * Create a selector between three signals.
 *
 * @param selector - when 0 at time t returns s1[t], when 1 at time t returns s2[t], otherwise returns s3[t]
 * (selector is automatically wrapped with sigIntCast)
 * @param s1 - first signal to be selected
 * @param s2 - second signal to be selected
 * @param s3 - third signal to be selected
 *
 * @return the selected signal depending of the selector value at each time t.
 */
LIBFAUST_API Signal sigSelect3(Signal selector, Signal s1, Signal s2, Signal s3);

/**
 * Create a foreign function signal.
 *
 * @param rtype - the foreign function return type of SType
 * @param names - the list of function names for single, double, quad, fixed-point
 * @param atypes - the list of arguments types
 * @param incfile - the include file where the foreign function is defined
 * @param libfile - the library file where the foreign function is defined
 * @param largs - the list of args
 *
 * @return the foreign function signal.
 */
LIBFAUST_API Signal sigFFun(SType rtype, nvec names, svec atypes, const std::string& incfile, const std::string& libfile, tvec largs);

/**
 * Create a foreign constant signal.
 *
 * @param type - the foreign constant type of SType
 * @param name - the foreign constant name
 * @param incfile - the include file where the foreign constant is defined
 *
 * @return the foreign constant signal.
 */
LIBFAUST_API Signal sigFConst(SType type, const std::string& name, const std::string& incfile);

/**
 * Create a foreign variable signal.
 *
 * @param type - the foreign variable type of SType
 * @param name - the foreign variable name
 * @param incfile - the include file where the foreign variable is defined
 *
 * @return the foreign variable signal.
 */
LIBFAUST_API Signal sigFVar(SType type, const std::string& name, const std::string& incfile);

/**
 * Generic binary mathematical functions.
 *
 * @param op - the operator in SOperator set
 * @param x - first signal
 * @param y - second signal
 *
 * @return the result signal of op(x,y).
 */
LIBFAUST_API Signal sigBinOp(SOperator op, Signal x, Signal y);

/**
 * Specific binary mathematical functions.
 *
 * @param x - first signal
 * @param y - second signal
 *
 * @return the result signal of fun(x,y).
 */
LIBFAUST_API Signal sigAdd(Signal x, Signal y);
LIBFAUST_API Signal sigSub(Signal x, Signal y);
LIBFAUST_API Signal sigMul(Signal x, Signal y);
LIBFAUST_API Signal sigDiv(Signal x, Signal y);
LIBFAUST_API Signal sigRem(Signal x, Signal y);

LIBFAUST_API Signal sigLeftShift(Signal x, Signal y);
LIBFAUST_API Signal sigLRightShift(Signal x, Signal y);
LIBFAUST_API Signal sigARightShift(Signal x, Signal y);

LIBFAUST_API Signal sigGT(Signal x, Signal y);
LIBFAUST_API Signal sigLT(Signal x, Signal y);
LIBFAUST_API Signal sigGE(Signal x, Signal y);
LIBFAUST_API Signal sigLE(Signal x, Signal y);
LIBFAUST_API Signal sigEQ(Signal x, Signal y);
LIBFAUST_API Signal sigNE(Signal x, Signal y);

LIBFAUST_API Signal sigAND(Signal x, Signal y);
LIBFAUST_API Signal sigOR(Signal x, Signal y);
LIBFAUST_API Signal sigXOR(Signal x, Signal y);

/**
 * Extended unary mathematical functions.
 */
LIBFAUST_API Signal sigAbs(Signal x);
LIBFAUST_API Signal sigAcos(Signal x);
LIBFAUST_API Signal sigTan(Signal x);
LIBFAUST_API Signal sigSqrt(Signal x);
LIBFAUST_API Signal sigSin(Signal x);
LIBFAUST_API Signal sigRint(Signal x);
LIBFAUST_API Signal sigLog(Signal x);
LIBFAUST_API Signal sigLog10(Signal x);
LIBFAUST_API Signal sigFloor(Signal x);
LIBFAUST_API Signal sigExp(Signal x);
LIBFAUST_API Signal sigExp10(Signal x);
LIBFAUST_API Signal sigCos(Signal x);
LIBFAUST_API Signal sigCeil(Signal x);
LIBFAUST_API Signal sigAtan(Signal x);
LIBFAUST_API Signal sigAsin(Signal x);

/**
 * Extended binary mathematical functions.
 */
LIBFAUST_API Signal sigRemainder(Signal x, Signal y);
LIBFAUST_API Signal sigPow(Signal x, Signal y);
LIBFAUST_API Signal sigMin(Signal x, Signal y);
LIBFAUST_API Signal sigMax(Signal x, Signal y);
LIBFAUST_API Signal sigFmod(Signal x, Signal y);
LIBFAUST_API Signal sigAtan2(Signal x, Signal y);

/**
 * Create a recursive signal inside the sigRecursion expression.
 *
 * @return the recursive signal.
 */
LIBFAUST_API Signal sigSelf();

/**
 * Create a recursive signal. Use sigSelf() to refer to the
 * recursive signal inside the sigRecursion expression.
 *
 * @param s - the signal to recurse on.
 *
 * @return the signal with a recursion.
 */
LIBFAUST_API Signal sigRecursion(Signal s);

/**
 * Create a recursive signal inside the sigRecursionN expression.
 *
 * @param id - the recursive signal index (starting from 0, up to the number of outputs signals in the recursive block)
 *
 * @return the recursive signal.
 */
LIBFAUST_API Signal sigSelfN(int id);

/**
 * Create a recursive block of signals. Use sigSelfN() to refer to the
 * recursive signal inside the sigRecursionN expression.
 *
 * @param rf - the list of signals to recurse on.
 *
 * @return the list of signals with recursions.
 */
LIBFAUST_API tvec sigRecursionN(const tvec& rf);

/**
 * Create a button signal.
 *
 * @param label - the label definition (see [2])
 *
 * @return the button signal.
 */
LIBFAUST_API Signal sigButton(const std::string& label);

/**
 * Create a checkbox signal.
 *
 * @param label - the label definition (see [2])
 *
 * @return the checkbox signal.
 */
LIBFAUST_API Signal sigCheckbox(const std::string& label);

/**
 * Create a vertical slider signal.
 *
 * @param label - the label definition (see [2])
 * @param init - the init signal, a constant numerical expression (see [1])
 * @param min - the min signal, a constant numerical expression (see [1])
 * @param max - the max signal, a constant numerical expression (see [1])
 * @param step - the step signal, a constant numerical expression (see [1])
 *
 * @return the vertical slider signal.
 */
LIBFAUST_API Signal sigVSlider(const std::string& label, Signal init, Signal min, Signal max, Signal step);

/**
 * Create an horizontal slider signal.
 *
 * @param label - the label definition (see [2])
 * @param init - the init signal, a constant numerical expression (see [1])
 * @param min - the min signal, a constant numerical expression (see [1])
 * @param max - the max signal, a constant numerical expression (see [1])
 * @param step - the step signal, a constant numerical expression (see [1])
 *
 * @return the horizontal slider signal.
 */
LIBFAUST_API Signal sigHSlider(const std::string& label, Signal init, Signal min, Signal max, Signal step);

/**
 * Create a num entry signal.
 *
 * @param label - the label definition (see [2])
 * @param init - the init signal, a constant numerical expression (see [1])
 * @param min - the min signal, a constant numerical expression (see [1])
 * @param max - the max signal, a constant numerical expression (see [1])
 * @param step - the step signal, a constant numerical expression (see [1])
 *
 * @return the num entry signal.
 */
LIBFAUST_API Signal sigNumEntry(const std::string& label, Signal init, Signal min, Signal max, Signal step);

/**
 * Create a vertical bargraph signal.
 *
 * @param label - the label definition (see [2])
 * @param min - the min signal, a constant numerical expression (see [1])
 * @param max - the max signal, a constant numerical expression (see [1])
 * @param s - the input signal
 *
 * @return the vertical bargraph signal.
 */
LIBFAUST_API Signal sigVBargraph(const std::string& label, Signal min, Signal max, Signal s);

/**
 * Create an horizontal bargraph signal.
 *
 * @param label - the label definition (see [2])
 * @param min - the min signal, a constant numerical expression (see [1])
 * @param max - the max signal, a constant numerical expression (see [1])
 * @param s - the input signal
 *
 * @return the horizontal bargraph signal.
 */
LIBFAUST_API Signal sigHBargraph(const std::string& label, Signal min, Signal max, Signal s);

/**
 * Create an attach signal.
 *
 * The attach primitive takes two input signals and produces one output signal
 * which is a copy of the first input. The role of attach is to force
 * its second input signal to be compiled with the first one.
 *
 * @param s1 - the first signal
 * @param s2 - the second signal
 *
 * @return the attach signal.
 */
LIBFAUST_API Signal sigAttach(Signal s1, Signal s2);

/**
 * Test each signal and fill additional signal specific parameters.
 *
 * @return true and fill the specific parameters if the signal is of a given type, false otherwise
 */
LIBFAUST_API bool isSigInt(Signal t, int* i);
LIBFAUST_API bool isSigReal(Signal t, double* r);
LIBFAUST_API bool isSigInput(Signal t, int* i);
LIBFAUST_API bool isSigOutput(Signal t, int* i, Signal& t0);
LIBFAUST_API bool isSigDelay1(Signal t, Signal& t0);
LIBFAUST_API bool isSigDelay(Signal t, Signal& t0, Signal& t1);
LIBFAUST_API bool isSigPrefix(Signal t, Signal& t0, Signal& t1);
LIBFAUST_API bool isSigRDTbl(Signal s, Signal& t, Signal& i);
LIBFAUST_API bool isSigWRTbl(Signal u, Signal& id, Signal& t, Signal& i, Signal& s);
LIBFAUST_API bool isSigGen(Signal t, Signal& x);
LIBFAUST_API bool isSigDocConstantTbl(Signal t, Signal& n, Signal& sig);
LIBFAUST_API bool isSigDocWriteTbl(Signal t, Signal& n, Signal& sig, Signal& widx, Signal& wsig);
LIBFAUST_API bool isSigDocAccessTbl(Signal t, Signal& tbl, Signal& ridx);
LIBFAUST_API bool isSigSelect2(Signal t, Signal& selector, Signal& s1, Signal& s2);
LIBFAUST_API bool isSigAssertBounds(Signal t, Signal& s1, Signal& s2, Signal& s3);
LIBFAUST_API bool isSigHighest(Signal t, Signal& s);
LIBFAUST_API bool isSigLowest(Signal t, Signal& s);

LIBFAUST_API bool isSigBinOp(Signal s, int* op, Signal& x, Signal& y);
LIBFAUST_API bool isSigFFun(Signal s, Signal& ff, Signal& largs);
LIBFAUST_API bool isSigFConst(Signal s, Signal& type, Signal& name, Signal& file);
LIBFAUST_API bool isSigFVar(Signal s, Signal& type, Signal& name, Signal& file);

LIBFAUST_API bool isProj(Signal s, int* i, Signal& rgroup);
LIBFAUST_API bool isRec(Signal s, Signal& var, Signal& body);

LIBFAUST_API bool isSigIntCast(Signal s, Signal& x);
LIBFAUST_API bool isSigFloatCast(Signal s, Signal& x);

LIBFAUST_API bool isSigButton(Signal s, Signal& lbl);
LIBFAUST_API bool isSigCheckbox(Signal s, Signal& lbl);

LIBFAUST_API bool isSigWaveform(Signal s);

LIBFAUST_API bool isSigHSlider(Signal s, Signal& lbl, Signal& init, Signal& min, Signal& max, Signal& step);
LIBFAUST_API bool isSigVSlider(Signal s, Signal& lbl, Signal& init, Signal& min, Signal& max, Signal& step);
LIBFAUST_API bool isSigNumEntry(Signal s, Signal& lbl, Signal& init, Signal& min, Signal& max, Signal& step);

LIBFAUST_API bool isSigHBargraph(Signal s, Signal& lbl, Signal& min, Signal& max, Signal& x);
LIBFAUST_API bool isSigVBargraph(Signal s, Signal& lbl, Signal& min, Signal& max, Signal& x);

LIBFAUST_API bool isSigAttach(Signal s, Signal& s0, Signal& s1);

LIBFAUST_API bool isSigEnable(Signal s, Signal& s0, Signal& s1);
LIBFAUST_API bool isSigControl(Signal s, Signal& s0, Signal& s1);

LIBFAUST_API bool isSigSoundfile(Signal s, Signal& label);
LIBFAUST_API bool isSigSoundfileLength(Signal s, Signal& sf, Signal& part);
LIBFAUST_API bool isSigSoundfileRate(Signal s, Signal& sf, Signal& part);
LIBFAUST_API bool isSigSoundfileBuffer(Signal s, Signal& sf, Signal& chan, Signal& part, Signal& ridx);

/**
 *  Simplify a signal to its normal form, where:
 *  - all possible optimisations, simplications, and compile time computations have been done
 *  - the mathematical functions (primitives and binary functions), delay, select2, soundfile primitive...
 *  are properly typed (arguments and result)
 *  - signal cast are properly done when needed
 *
 * @param sig - the signal to be processed
 *
 * @return the signal in normal form.
 */
LIBFAUST_API Signal simplifyToNormalForm(Signal s);

/**
 *  Simplify a signal list to its normal form, where:
 *  - all possible optimisations, simplications, and compile time computations have been done
 *  - the mathematical functions (primitives and binary functions), delay, select2, soundfile primitive...
 *  are properly typed (arguments and result)
 *  - signal cast are properly done when needed
 *
 * @param siglist - the signal list to be processed
 *
 * @return the signal vector in normal form.
 */
LIBFAUST_API tvec simplifyToNormalForm2(tvec siglist);

/**
 * Create source code in a target language from a vector of output signals.
 *
 * @param name_app - the name of the Faust program
 * @param osigs - the vector of output signals (that will internally be converted in normal form,
 * see simplifyToNormalForm)
 * @param lang - the target source code's language which can be one of "c",
 * "cpp", "cmajor", "codebox", "csharp", "dlang", "fir", "interp", "java", "jax",
 * "jsfx", "julia", "ocpp", "rust" or "wast"
 * (depending of which of the corresponding backends are compiled in libfaust)
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return a string of source code on success, setting error_msg on error.
 */
LIBFAUST_API std::string createSourceFromSignals(const std::string& name_app, tvec osigs,
                                                 const std::string& lang,
                                                 int argc, const char* argv[],
                                                 std::string& error_msg);

/*
 [1] Constant numerical expression : see https://faustdoc.grame.fr/manual/syntax/#constant-numerical-expressions
 [2] Label definition : https://faustdoc.grame.fr/manual/syntax/#variable-parts-of-a-label
 */

/*!
 @}
 */

#endif
