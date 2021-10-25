/************************************************************************
 ************************************************************************
 Copyright (C) 2021 GRAME, Centre National de Creation Musicale
 
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
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 ************************************************************************
 ************************************************************************/

#ifndef LIBFAUSTCOMMON_C_H
#define LIBFAUSTCOMMON_C_H

/*!
 \addtogroup signalc C interface for the Signal API.
 @{
 */


/**
 * Opaque types.
 */

#ifdef _MSC_VER
typedef void CTree;
#else
typedef struct {} CTree;
#endif

typedef CTree* Signal;
typedef CTree* Box;

enum SType { kSInt, kSReal };

enum SOperator { kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };

#endif

#ifndef LIBFAUSTSIGNAL_C_H
#define LIBFAUSTSIGNAL_C_H

#ifdef __cplusplus
extern "C"
{
#endif
    
    /**
     * Create global compilation context, has to be done first.
     */
    void createLibContext();
    
    /**
     * Destroy global compilation context, has to be done last.
     */
    void destroyLibContext();
    
    /**
     * Constant integer : for all t, x(t) = n.
     *
     * @param n - the integer
     *
     * @return the integer value.
     */
    Signal CsigInt(int n);
    
    /**
     * Constant real : for all t, x(t) = n.
     *
     * @param n - the float/double value (depends of -single or -double compilation parameter)
     *
     * @return the float/double signal.
     */
    Signal CsigReal(double n);
    
    /**
     * Create an input.
     *
     * @param idx - the input index
     *
     * @return the input signal.
     */
    Signal CsigInput(int idx);
    
    /**
     * Create a delayed signal.
     *
     * @param s - the signal to be delayed
     * @param del - the delay signal that doesn't have to be fixed but must be bounded and cannot be negative
     *
     * @return the delayed signal.
     */
    Signal CsigDelay(Signal s, Signal del);
    
    /**
     * Create a casted signal.
     *
     * @param s - the signal to be casted in integer
     *
     * @return the casted signal.
     */
    Signal CsigIntCast(Signal s);
    
    /**
     * Create a casted signal.
     *
     * @param s - the signal to be casted as float/double value (depends of -single or -double compilation parameter)
     *
     * @return the casted signal.
     */
    Signal CsigFloatCast(Signal s);
    
    /**
     * Create a read only table.
     *
     * @param n - the table size, a constant numerical expression (see [1])
     * @param init - the table content
     * @param ridx - the read index (an int between 0 and n-1)
     *
     * @return the table signal.
     */
    Signal CsigReadOnlyTable(Signal n, Signal init, Signal ridx);
    
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
    Signal CsigWriteReadTable(Signal n, Signal init, Signal widx, Signal wsig, Signal ridx);
    
    /**
     * Create a waveform.
     *
     * @param wf - the content of the waveform as a null terminated array of CsigInt or CsigDouble signals
     *
     * @return the waveform signal.
     */
    Signal CsigWaveform(Signal* wf);
    // Use: CsigInt(size of wf); to generate the waveform size signal
    
    /**
     * Create a soundfile block.
     *
     * @param label - of form "label[url:{'path1';'path2';'path3'}]" to describe a list of soundfiles
     *
     * @return the soundfile block.
     */
    Signal CsigSoundfile(const char* label);
    
    /**
     * Create the length signal of a given soundfile in frames.
     *
     * @param sf - the soundfile
     * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
     *
     * @return the length signal.
     */
    Signal CsigSoundfileLength(Signal sf, Signal part);
    
    /**
     * Create the rate signal of a given soundfile in Hz.
     *
     * @param sf - the soundfile
     * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
     *
     * @return the rate signal.
     */
    Signal CsigSoundfileRate(Signal sf, Signal part);
    
    /**
     * Create the buffer signal of a given soundfile.
     *
     * @param sf - the soundfile
     * @param chan - an integer to select a given channel, a constant numerical expression (see [1])
     * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
     * @param ridx - the read index (an integer between 0 and the selected sound length)
     *
     * @return the buffer signal.
     */
    Signal CsigSoundfileBuffer(Signal sf, Signal chan, Signal part, Signal ridx);
    
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
    Signal CsigSelect2(Signal selector, Signal s1, Signal s2);
    
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
    Signal CsigSelect3(Signal selector, Signal s1, Signal s2, Signal s3);
      
    /**
     * Create a foreign constant signal.
     *
     * @param type - the foreign constant type of SType
     * @param name - the foreign constant name
     * @param file - the include file where the foreign constant is defined
     *
     * @return the foreign constant signal.
     */
    Signal CsigFConst(enum SType type, const char* name, const char* file);
    
    /**
     * Create a foreign variable signal.
     *
     * @param type - the foreign variable type of SType
     * @param name - the foreign variable name
     * @param file - the include file where the foreign variable is defined
     *
     * @return the foreign variable signal.
     */
    Signal CsigFVar(enum SType type, const char* name, const char* file);
    
    /**
     * Generic binary mathematical functions.
     *
     * @param op - the operator in SOperator set
     * @param x - first signal
     * @param y - second signal
     *
     * @return the result signal of op(x,y).
     */
    Signal CsigBinOp(enum SOperator op, Signal x, Signal y);
    
    /**
     * Specific binary mathematical functions.
     *
     * @param x - first signal
     * @param y - second signal
     *
     * @return the result signal of fun(x,y).
     */
    Signal CsigAdd(Signal x, Signal y);
    Signal CsigSub(Signal x, Signal y);
    Signal CsigMul(Signal x, Signal y);
    Signal CsigDiv(Signal x, Signal y);
    Signal CsigRem(Signal x, Signal y);
    
    Signal CsigLeftShift(Signal x, Signal y);
    Signal CsigLRightShift(Signal x, Signal y);
    Signal CsigARightShift(Signal x, Signal y);
    
    Signal CsigGT(Signal x, Signal y);
    Signal CsigLT(Signal x, Signal y);
    Signal CsigGE(Signal x, Signal y);
    Signal CsigLE(Signal x, Signal y);
    Signal CsigEQ(Signal x, Signal y);
    Signal CsigNE(Signal x, Signal y);
    
    Signal CsigAND(Signal x, Signal y);
    Signal CsigOR(Signal x, Signal y);
    Signal CsigXOR(Signal x, Signal y);
    
    /**
     * Extended unary mathematical functions.
     */
    Signal CsigAbs(Signal x);
    Signal CsigAcos(Signal x);
    Signal CsigTan(Signal x);
    Signal CsigSqrt(Signal x);
    Signal CsigSin(Signal x);
    Signal CsigRint(Signal x);
    Signal CsigLog(Signal x);
    Signal CsigLog10(Signal x);
    Signal CsigFloor(Signal x);
    Signal CsigExp(Signal x);
    Signal CsigExp10(Signal x);
    Signal CsigCos(Signal x);
    Signal CsigCeil(Signal x);
    Signal CsigAtan(Signal x);
    Signal CsigAsin(Signal x);
    
    /**
     * Extended binary mathematical functions.
     */
    Signal CsigRemainder(Signal x, Signal y);
    Signal CsigPow(Signal x, Signal y);
    Signal CsigMin(Signal x, Signal y);
    Signal CsigMax(Signal x, Signal y);
    Signal CsigFmod(Signal x, Signal y);
    Signal CsigAtan2(Signal x, Signal y);
    
    /**
     * Create a recursive signal inside the sigRecursion expression.
     *
     * @return the recursive signal.
     */
    Signal CsigSelf();
    
    /**
     * Create a recursive signal. Use sigSelf() to refer to the
     * recursive signal inside the sigRecursion expression.
     *
     * @param s - the signal to recurse on.
     *
     * @return the signal with a recursion.
     */
    Signal CsigRecursion(Signal s);
    
    /**
     * Create a button signal.
     *
     * @param label - the label definition (see [2])
     *
     * @return the button signal.
     */
    Signal CsigButton(const char* label);
    
    /**
     * Create a checkbox signal.
     *
     * @param label - the label definition (see [2])
     *
     * @return the checkbox signal.
     */
    Signal CsigCheckbox(const char* label);
    
    /**
     * Create a vertical slider signal.
     *
     * @param label - the label definition (see [2])
     * @param init - the init signal, a constant numerical expression (see [1])
     * @param min - the max signal, a constant numerical expression (see [1])
     * @param max - the min signal, a constant numerical expression (see [1])
     * @param step - the step signal, a constant numerical expression (see [1])
     *
     * @return the vertical slider signal.
     */
    Signal CsigVSlider(const char* label, Signal init, Signal min, Signal max, Signal step);
    
    /**
     * Create an horizontal slider signal.
     *
     * @param label - the label definition (see [2])
     * @param init - the init signal, a constant numerical expression (see [1])
     * @param min - the max signal, a constant numerical expression (see [1])
     * @param max - the min signal, a constant numerical expression (see [1])
     * @param step - the step signal, a constant numerical expression (see [1])
     *
     * @return the horizontal slider signal.
     */
    Signal CsigHSlider(const char* label, Signal init, Signal min, Signal max, Signal step);
    
    /**
     * Create a num entry signal.
     *
     * @param label - the label definition (see [2])
     * @param init - the init signal, a constant numerical expression (see [1])
     * @param min - the max signal, a constant numerical expression (see [1])
     * @param max - the min signal, a constant numerical expression (see [1])
     * @param step - the step signal, a constant numerical expression (see [1])
     *
     * @return the num entry signal.
     */
    Signal CsigNumEntry(const char* label, Signal init, Signal min, Signal max, Signal step);
    
    /**
     * Create a vertical bargraph signal.
     *
     * @param label - the label definition (see [2])
     * @param min - the max signal, a constant numerical expression (see [1])
     * @param max - the min signal, a constant numerical expression (see [1])
     * @param s - the input signal
     *
     * @return the vertical bargraph signal.
     */
    Signal CsigVBargraph(const char* label, Signal min, Signal max, Signal s);
    
    /**
     * Create an horizontal bargraph signal.
     *
     * @param label - the label definition (see [2])
     * @param min - the max signal, a constant numerical expression (see [1])
     * @param max - the min signal, a constant numerical expression (see [1])
     * @param s - the input signal
     *
     * @return the horizontal bargraph signal.
     */
    Signal CsigHBargraph(const char* label, Signal min, Signal max, Signal s);
    
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
    Signal CsigAttach(Signal s1, Signal s2);
    
    /*
     [1] Constant numerical expression : see https://faustdoc.grame.fr/manual/syntax/#constant-numerical-expressions
     [2] Label definition : https://faustdoc.grame.fr/manual/syntax/#variable-parts-of-a-label
     */
    
#ifdef __cplusplus
}
#endif

/*!
 @}
 */

#endif
