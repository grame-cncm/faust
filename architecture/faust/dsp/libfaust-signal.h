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

#ifndef LIBFAUSTCOMMON_H
#define LIBFAUSTCOMMON_H

/*!
 \addtogroup signalcpp C++ interface for the Signal API.
 @{
 */

/**
 * Opaque types.
 */
class CTree;
typedef std::vector<CTree*> tvec;

enum SType { kSInt, kSReal };

enum SOperator { kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };

/**
 * Base class for factories.
 */
struct dsp_factory_base {
    
    virtual ~dsp_factory_base() {}
    
    virtual void write(std::ostream* out, bool binary = false, bool compact = false) {}
};

#endif

#ifndef LIBFAUSTSIGNAL_H
#define LIBFAUSTSIGNAL_H

/**
 * Opaque types.
 */
typedef CTree* Signal;

/**
 * Create global compilation context, has to be done first.
 */
extern "C" void createLibContext();

/**
 * Destroy global compilation context, has to be done last.
 */
extern "C" void destroyLibContext();

/**
 * Constant integer : for all t, x(t) = n.
 *
 * @param n - the integer
 *
 * @return the integer signal.
 */
Signal sigInt(int n);

/**
 * Constant real : for all t, x(t) = n.
 *
 * @param n - the float/double value (depends of -single or -double compilation parameter)
 *
 * @return the float/double signal.
 */
Signal sigReal(double n);

/**
 * Create an input.
 *
 * @param idx - the input index
 *
 * @return the input signal.
 */
Signal sigInput(int idx);

/**
 * Create a delayed signal.
 *
 * @param s - the signal to be delayed
 * @param del - the delay signal that doesn't have to be fixed but must be bounded and cannot be negative
 *
 * @return the delayed signal.
 */
Signal sigDelay(Signal s, Signal del);

/**
 * Create a casted signal.
 *
 * @param s - the signal to be casted in integer
 *
 * @return the casted signal.
 */
Signal sigIntCast(Signal s);

/**
 * Create a casted signal.
 *
 * @param s - the signal to be casted as float/double value (depends of -single or -double compilation parameter)
 *
 * @return the casted signal.
 */
Signal sigFloatCast(Signal s);

/**
 * Create a read only table.
 *
 * @param n - the table size, a constant numerical expression (see [1])
 * @param init - the table content
 * @param ridx - the read index (an int between 0 and n-1)
 *
 * @return the table signal.
 */
Signal sigReadOnlyTable(Signal n, Signal init, Signal ridx);

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
Signal sigWriteReadTable(Signal n, Signal init, Signal widx, Signal wsig, Signal ridx);

/**
 * Create a waveform.
 *
 * @param wf - the content of the waveform as a vector of sigInt or sigDouble signals
 *
 * @return the waveform signal.
 */
Signal sigWaveform(const tvec& wf);
// Use: sigInt(wf.size()); to generate the waveform size signal

/**
 * Create a soundfile block.
 *
 * @param label - of form "label[url:{'path1';'path2';'path3'}]" to describe a list of soundfiles
 *
 * @return the soundfile block.
 */
Signal sigSoundfile(const std::string& label);

/**
 * Create the length signal of a given soundfile in frames.
 *
 * @param sf - the soundfile
 * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
 *
 * @return the soundfile length signal.
 */
Signal sigSoundfileLength(Signal sf, Signal part);

/**
 * Create the rate signal of a given soundfile in Hz.
 *
 * @param sf - the soundfile
 * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
 *
 * @return the soundfile rate signal.
 */
Signal sigSoundfileRate(Signal sf, Signal part);

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
Signal sigSoundfileBuffer(Signal sf, Signal chan, Signal part, Signal ridx);

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
Signal sigSelect2(Signal selector, Signal s1, Signal s2);

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
Signal sigSelect3(Signal selector, Signal s1, Signal s2, Signal s3);

/**
 * Create a foreign constant signal.
 *
 * @param type - the foreign constant type of SType
 * @param name - the foreign constant name
 * @param file - the include file where the foreign constant is defined
 *
 * @return the foreign constant signal.
 */
Signal sigFConst(SType type, const std::string& name, const std::string& file);

/**
 * Create a foreign variable signal.
 *
 * @param type - the foreign variable type of SType
 * @param name - the foreign variable name
 * @param file - the include file where the foreign variable is defined
 *
 * @return the foreign variable signal.
 */
Signal sigFVar(SType type, const std::string& name, const std::string& file);

/**
 * Generic binary mathematical functions.
 *
 * @param op - the operator in SOperator set
 * @param x - first signal
 * @param y - second signal
 *
 * @return the result signal of op(x,y).
 */
Signal sigBinOp(SOperator op, Signal x, Signal y);

/**
 * Specific binary mathematical functions.
 *
 * @param x - first signal
 * @param y - second signal
 *
 * @return the result signal of fun(x,y).
 */
Signal sigAdd(Signal x, Signal y);
Signal sigSub(Signal x, Signal y);
Signal sigMul(Signal x, Signal y);
Signal sigDiv(Signal x, Signal y);
Signal sigRem(Signal x, Signal y);

Signal sigLeftShift(Signal x, Signal y);
Signal sigLRightShift(Signal x, Signal y);
Signal sigARightShift(Signal x, Signal y);

Signal sigGT(Signal x, Signal y);
Signal sigLT(Signal x, Signal y);
Signal sigGE(Signal x, Signal y);
Signal sigLE(Signal x, Signal y);
Signal sigEQ(Signal x, Signal y);
Signal sigNE(Signal x, Signal y);

Signal sigAND(Signal x, Signal y);
Signal sigOR(Signal x, Signal y);
Signal sigXOR(Signal x, Signal y);

/**
 * Extended unary mathematical functions.
 */
Signal sigAbs(Signal x);
Signal sigAcos(Signal x);
Signal sigTan(Signal x);
Signal sigSqrt(Signal x);
Signal sigSin(Signal x);
Signal sigRint(Signal x);
Signal sigLog(Signal x);
Signal sigLog10(Signal x);
Signal sigFloor(Signal x);
Signal sigExp(Signal x);
Signal sigExp10(Signal x);
Signal sigCos(Signal x);
Signal sigCeil(Signal x);
Signal sigAtan(Signal x);
Signal sigAsin(Signal x);

/**
 * Extended binary mathematical functions.
 */
Signal sigRemainder(Signal x, Signal y);
Signal sigPow(Signal x, Signal y);
Signal sigMin(Signal x, Signal y);
Signal sigMax(Signal x, Signal y);
Signal sigFmod(Signal x, Signal y);
Signal sigAtan2(Signal x, Signal y);

/**
 * Create a recursive signal inside the sigRecursion expression.
 *
 * @return the recursive signal.
 */
Signal sigSelf();

/**
 * Create a recursive signal. Use sigSelf() to refer to the
 * recursive signal inside the sigRecursion expression.
 *
 * @param s - the signal to recurse on.
 *
 * @return the signal with a recursion.
 */
Signal sigRecursion(Signal s);

/**
 * Create a button signal.
 *
 * @param label - the label definition (see [2])
 *
 * @return the button signal.
 */
Signal sigButton(const std::string& label);

/**
 * Create a checkbox signal.
 *
 * @param label - the label definition (see [2])
 *
 * @return the checkbox signal.
 */
Signal sigCheckbox(const std::string& label);

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
Signal sigVSlider(const std::string& label, Signal init, Signal min, Signal max, Signal step);

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
Signal sigHSlider(const std::string& label, Signal init, Signal min, Signal max, Signal step);

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
Signal sigNumEntry(const std::string& label, Signal init, Signal min, Signal max, Signal step);

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
Signal sigVBargraph(const std::string& label, Signal min, Signal max, Signal s);

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
Signal sigHBargraph(const std::string& label, Signal min, Signal max, Signal s);

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
Signal sigAttach(Signal s1, Signal s2);

/**
 * Create a C++ Faust DSP factory from a vector of output signals.
 *
 * @param name_app - the name of the Faust program
 * @param signals_vec - the vector of output signals
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */
dsp_factory_base* createCPPDSPFactoryFromSignals(const std::string& name_app, tvec signals_vec,
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
