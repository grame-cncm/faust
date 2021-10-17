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

/**
 * Opaque types.
 */

#ifdef _MSC_VER
typedef void CTree;
#else
typedef struct {} CTree;
#endif

typedef CTree* Box;
typedef CTree* Signal;

enum SType { kSInt, kSReal };

enum SOperator { kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };

#endif

#ifndef LIBFAUSTBOX_C_H
#define LIBFAUSTBOX_C_H

#include <string>
#include <vector>

#ifdef __cplusplus
extern "C"
{
#endif
    
    
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
     * @return the integer box.
     */
    
    Box CboxInt(int n);
    
    /**
     * Constant real : for all t, x(t) = n.
     *
     * @param n - the float/double value (depends of -single or -double compilation parameter)
     *
     * @return the float/double box.
     */
    Box CboxReal(double n);
    
    /**
     * The identity box, copy its input to its output.
     *
     * @return the identity box.
     */
    Box CboxWire();
    
    /**
     * The cut box, to "stop"/terminate a signal.
     *
     * @return the cut box.
     */
    Box CboxCut();
    
    /**
     * The sequential composition of two blocks (e.g., A:B) expects: outputs(A)=inputs(B)
     *
     * @return the seq box.
     */
    Box CboxSeq(Box x, Box y);
    
    /**
     * The parallel composition of two blocks (e.g., A,B).
     * It places the two block-diagrams one on top of the other, without connections.
     *
     * @return the par box.
     */
    Box CboxPar(Box x, Box y);
    
    Box CboxPar3(Box x, Box y, Box z)
    {
        return CboxPar(x, CboxPar(y, z));
    }
    
    Box CboxPar4(Box a, Box b, Box c, Box d)
    {
        return CboxPar(a, CboxPar3(b, c, d));
    }
    
    Box boxPar5(Box a, Box b, Box c, Box d, Box e)
    {
        return CboxPar(a, CboxPar4(b, c, d, e));
    }
    
    /**
     * The split composition (e.g., A<:B) operator is used to distribute
     * the outputs of A to the inputs of B.
     *
     * For the operation to be valid, the number of inputs of B
     * must be a multiple of the number of outputs of A: outputs(A).k=inputs(B)
     *
     * @return the split box.
     */
    Box CboxSplit(Box x, Box y);
    
    /**
     * The merge composition (e.g., A:>B) is the dual of the split composition.
     *
     * The number of outputs of A must be a multiple of the number of inputs of B: outputs(A)=k.inputs(B)
     *
     * @return the merge box.
     */
    Box CboxMerge(Box x, Box y);
    
    /**
     * The recursive composition (e.g., A~B) is used to create cycles in the block-diagram
     * in order to express recursive computations.
     * It is the most complex operation in terms of connections: outputs(A)≥inputs(B) and inputs(A)≥outputs(B)
     *
     * @return the rec box.
     */
    Box CboxRec(Box x, Box y);
    
    /**
     * The route primitive facilitates the routing of signals in Faust.
     * It has the following syntax: route(A,B,a,b,c,d,...) or route(A,B,(a,b),(c,d),...)
     *
     * @param n -  the number of input signals
     * @param m -  the number of output signals
     * @param r - the routing description, a 'par' expression of a,b / (a,b) input/output pairs
     
     * @return the route box.
     */
    Box CboxRoute(Box n, Box m, Box r);
    
    /**
     * Create a delayed box.
     *
     * @return the delayed box.
     */
    Box CboxDelay();
    
    /**
     * Create a delayed box.
     *
     * @param s - the box to be delayed
     * @param del - the delay box that doesn't have to be fixed but must be bounded and cannot be negative
     
     * @return the delayed box.
     */
    Box CboxDelayAux(Box s, Box del)
    {
        return CboxSeq(CboxPar(s, del), CboxDelay());
    }
    
    /**
     * Create a casted box.
     *
     * @return the casted box.
     */
    Box CboxIntCast();
    
    /**
     * Create a casted box.
     *
     * @param s - the box to be casted in integer
     *
     * @return the casted box.
     */
    
    Box CboxIntCastAux(Box s)
    {
        return CboxSeq(s, CboxIntCast());
    }
    
    /**
     * Create a casted box.
     *
     * @return the casted box.
     */
    Box CboxFloatCast();
    
    /**
     * Create a casted box.
     *
     * @param s - the signal to be casted as float/double value (depends of -single or -double compilation parameter)
     *
     * @return the casted box.
     */
    Box CboxFloatCastAux(Box s)
    {
        return CboxSeq(s, CboxFloatCast());
    }
    
    /**
     * Create a read only table.
     *
     * @return the table box.
     */
    Box CboxReadOnlyTable();
    
    /**
     * Create a read only table.
     *
     * @param n - the table size, a constant numerical expression (see [1])
     * @param init - the table content
     * @param ridx - the read index (an int between 0 and n-1)
     *
     * @return the table box.
     */
    Box CboxReadOnlyTableAux(Box n, Box init, Box ridx)
    {
        return CboxSeq(CboxPar3(n, init, ridx), CboxReadOnlyTable());
    }
    
    /**
     * Create a read/write table.
     *
     * @return the table box.
     */
    Box CboxWriteReadTable();
    
    /**
     * Create a read/write table.
     *
     * @param n - the table size, a constant numerical expression (see [1])
     * @param init - the table content
     * @param widx - the write index (an integer between 0 and n-1)
     * @param wsig - the input of the table
     * @param ridx - the read index (an integer between 0 and n-1)
     *
     * @return the table box.
     */
    Box CboxWriteReadTableAux(Box n, Box init, Box widx, Box wsig, Box ridx)
    {
        return CboxSeq(boxPar5(n, init, widx, wsig, ridx), CboxWriteReadTable());
    }
    
    /**
     * Create a waveform.
     *
     * @param wf - the content of the waveform as a vector of boxInt or boxDouble boxes
     *
     * @return the waveform box.
     */
    Box CboxWaveform(Box* wf);
    
    /**
     * Create a soundfile block.
     *
     * @param label - of form "label[url:{'path1';'path2';'path3'}]" to describe a list of soundfiles
     * @param chan - the number of outputs channels, a constant numerical expression (see [1])
     *
     * @return the soundfile box.
     */
    Box CboxSoundfile(const char* label, Box chan);
    
    /**
     * Create a soundfile block.
     *
     * @param label - of form "label[url:{'path1';'path2';'path3'}]" to describe a list of soundfiles
     * @param chan - the number of outputs channels, a constant numerical expression (see [1])
     * @param part - in the [0..255] range to select a given sound number, a constant numerical expression (see [1])
     * @param ridx - the read index (an integer between 0 and the selected sound length)
     *
     * @return the soundfile box.
     */
    Box CoxSoundfileAux(const char* label, Box chan, Box part, Box ridx)
    {
        return CboxSeq(CboxPar(part, ridx), CboxSoundfile(label, chan));
    }
    
    /**
     * Create a selector between two boxes.
     *
     * @return the selected box depending of the selector value at each time t.
     */
    Box CboxSelect2();
    
    /**
     * Create a selector between two boxes.
     *
     * @param selector - when 0 at time t returns s1[t], otherwise returns s2[t]
     * @param s1 - first box to be selected
     * @param s2 - second box to be selected
     *
     * @return the selected box depending of the selector value at each time t.
     */
    Box CboxSelect2Aux(Box selector, Box s1, Box s2)
    {
        return CboxSeq(CboxPar3(selector, s1, s2), CboxSelect2());
    }
    
    /**
     * Create a selector between three boxes.
     *
     * @return the selected box depending of the selector value at each time t.
     */
    Box CboxSelect3();
    
    /**
     * Create a selector between three boxes.
     *
     * @param selector - when 0 at time t returns s1[t], when 1 at time t returns s2[t], otherwise returns s3[t]
     * @param s1 - first box to be selected
     * @param s2 - second box to be selected
     * @param s3 - third signal to be selected
     *
     * @return the selected box depending of the selector value at each time t.
     */
    Box CboxSelect3Aux(Box selector, Box s1, Box s2, Box s3)
    {
        return CboxSeq(CboxPar4(selector, s1, s2, s3), CboxSelect3());
    }
    
    /**
     * Create a foreign constant box.
     *
     * @param type - the foreign constant type of SType
     * @param name - the foreign constant name
     * @param file - the include file where the foreign constant is defined
     *
     * @return the foreign constant box.
     */
    Box CboxFConst(SType type, const char* name, const char* file);
    
    /**
     * Create a foreign variable box.
     *
     * @param type - the foreign variable type of SType
     * @param name - the foreign variable name
     * @param file - the include file where the foreign variable is defined
     *
     * @return the foreign variable box.
     */
    Box CboxFVar(SType type, const char* name, const char* file);
    
    /**
     * Generic binary mathematical functions.
     *
     * @param op - the operator in SOperator set
     *
     * @return the result box of op(x,y).
     */
    Box CboxBinOp(SOperator op);
    
    Box CboxBinOpAux(SOperator op, Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxBinOp(op));
    }
    
    /**
     * Specific binary mathematical functions.
     *
     * @return the result box.
     */
    Box CboxAdd();
    Box CboxAddAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxAdd());
    }
    Box CboxSub();
    Box CboxSubAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxSub());
    }
    Box CboxMul();
    Box CboxMulAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxMul());
    }
    Box CboxDiv();
    Box CboxDivAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxDiv());
    }
    Box CboxRem();
    Box CboxRemAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxRem());
    }
    
    Box CboxLeftShift();
    Box CboxLeftShiftAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxLeftShift());
    }
    Box CboxLRightShift();
    Box CboxLRightShiftAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxLRightShift());
    }
    Box CboxARightShift();
    Box CboxARightShiftAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxARightShift());
    }
    
    Box CboxGT();
    Box CboxGTAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxGT());
    }
    Box CboxLT();
    Box CboxLTAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxLT());
    }
    Box CboxGE();
    Box CboxGEAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxGE());
    }
    Box CboxLE();
    Box CboxLEAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxLE());
    }
    Box CboxEQ();
    Box CboxEQAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxEQ());
    }
    Box CboxNE();
    Box CboxNEAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxNE());
    }
    
    Box CboxAND();
    Box CboxANDAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxAND());
    }
    Box CboxOR();
    Box CboxORAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxOR());
    }
    Box CboxXOR();
    Box CboxXORAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxXOR());
    }
    
    /**
     * Extended unary mathematical functions.
     */
    
    Box CboxAbs();
    Box CboxAbsAux(Box x)
    {
        return CboxSeq(x, CboxAbs());
    }
    Box CboxAcos();
    Box CboxAcosAux(Box x)
    {
        return CboxSeq(x, CboxAcos());
    }
    Box CboxTan();
    Box CboxTanAux(Box x)
    {
        return CboxSeq(x, CboxTan());
    }
    Box CboxSqrt();
    Box CboxSqrtAux(Box x)
    {
        return CboxSeq(x, CboxSqrt());
    }
    Box CboxSin();
    Box CboxSinAux(Box x)
    {
        return CboxSeq(x, CboxSin());
    }
    Box CboxRint();
    Box CboxRintAux(Box x)
    {
        return CboxSeq(x, CboxRint());
    }
    Box CboxLog();
    Box CboxLogAux(Box x)
    {
        return CboxSeq(x, CboxLog());
    }
    Box CboxLog10();
    Box CboxLog10Aux(Box x)
    {
        return CboxSeq(x, CboxLog10());
    }
    Box CboxFloor();
    Box CboxFloorAux(Box x)
    {
        return CboxSeq(x, CboxFloor());
    }
    Box CboxExp();
    Box CboxExpAux(Box x)
    {
        return CboxSeq(x, CboxExp());
    }
    Box CboxExp10();
    Box CboxExp10Aux(Box x)
    {
        return CboxSeq(x, CboxExp10());
    }
    Box CboxCos();
    Box CboxCosAux(Box x)
    {
        return CboxSeq(x, CboxCos());
    }
    Box CboxCeil();
    Box CboxCeilAux(Box x)
    {
        return CboxSeq(x, CboxCeil());
    }
    Box CboxAtan();
    Box CboxAtanAux(Box x)
    {
        return CboxSeq(x, CboxAtan());
    }
    Box CboxAsin();
    Box CboxAsinAux(Box x)
    {
        return CboxSeq(x, CboxAsin());
    }
    
    /**
     * Extended binary mathematical functions.
     */
    
    Box CboxRemainder();
    Box CboxRemainderAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxRemainder());
    }
    Box CboxPow();
    Box CboxPowAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxPow());
    }
    Box CboxMin();
    Box CboxMinAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxMin());
    }
    Box CboxMax();
    Box CboxMaxAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxMax());
    }
    Box CboxFmod();
    Box CboxFmodAux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxFmod());
    }
    Box CboxAtan2();
    Box CboxAtan2Aux(Box b1, Box b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxAtan2());
    }
    
    /**
     * Create a button box.
     *
     * @param label - the label definition (see [2])
     *
     * @return the button box.
     */
    Box CboxButton(const char* label);
    
    /**
     * Create a checkbox box.
     *
     * @param label - the label definition (see [2])
     *
     * @return the checkbox box.
     */
    Box CboxCheckbox(const char* label);
    
    /**
     * Create a vertical slider box.
     *
     * @param label - the label definition (see [2])
     * @param init - the init box, a constant numerical expression (see [1])
     * @param min - the max box, a constant numerical expression (see [1])
     * @param max - the min box, a constant numerical expression (see [1])
     * @param step - the step box, a constant numerical expression (see [1])
     *
     * @return the vertical slider box.
     */
    Box CboxVSlider(const char* label, Box init, Box min, Box max, Box step);
    
    /**
     * Create an horizontal slider box.
     *
     * @param label - the label definition (see [2])
     * @param init - the init box, a constant numerical expression (see [1])
     * @param min - the max box, a constant numerical expression (see [1])
     * @param max - the min box, a constant numerical expression (see [1])
     * @param step - the step box, a constant numerical expression (see [1])
     *
     * @return the horizontal slider box.
     */
    Box CboxHSlider(const char* label, Box init, Box min, Box max, Box step);
    
    /**
     * Create a num entry box.
     *
     * @param label - the label definition (see [2])
     * @param init - the init box, a constant numerical expression (see [1])
     * @param min - the max box, a constant numerical expression (see [1])
     * @param max - the min box, a constant numerical expression (see [1])
     * @param step - the step box, a constant numerical expression (see [1])
     *
     * @return the num entry box.
     */
    Box CboxNumEntry(const char* label, Box init, Box min, Box max, Box step);
    
    /**
     * Create a vertical bargraph box.
     *
     * @param label - the label definition (see [2])
     * @param min - the max box, a constant numerical expression (see [1])
     * @param max - the min box, a constant numerical expression (see [1])
     *
     * @return the vertical bargraph box.
     */
    Box CboxVBargraph(const char* label, Box min, Box max);
    
    /**
     * Create a vertical bargraph box.
     *
     * @param label - the label definition (see [2])
     * @param min - the max box, a constant numerical expression (see [1])
     * @param max - the min box, a constant numerical expression (see [1])
     * @param s - the input box
     *
     * @return the vertical bargraph box.
     */
    Box CboxVBargraphAux(const char* label, Box min, Box max, Box x)
    {
        return CboxSeq(x, CboxVBargraph(label, min, max));
    }
    
    /**
     * Create an horizontal bargraph box.
     *
     * @param label - the label definition (see [2])
     * @param min - the max box, a constant numerical expression (see [1])
     * @param max - the min box, a constant numerical expression (see [1])
     *
     * @return the horizontal bargraph box.
     */
    Box CboxHBargraph(const char* label, Box min, Box max);
    
    /**
     * Create a horizontal bargraph box.
     *
     * @param label - the label definition (see [2])
     * @param min - the max box, a constant numerical expression (see [1])
     * @param max - the min box, a constant numerical expression (see [1])
     * @param s - the input box
     *
     * @return the vertical horizontal box.
     */
    Box CboxHBargraphAux(const char* label, Box min, Box max, Box x)
    {
        return CboxSeq(x, CboxHBargraph(label, min, max));
    }
    /**
     * Create an attach box.
     *
     * The attach primitive takes two input boxes and produces one output box
     * which is a copy of the first input. The role of attach is to force
     * its second input boxes to be compiled with the first one.
     *
     * @return the attach box.
     */
    Box CboxAttach();
    
    /**
     * Create an attach box.
     *
     * The attach primitive takes two input box and produces one output box
     * which is a copy of the first input. The role of attach is to force
     * its second input signal to be compiled with the first one.
     *
     * @param s1 - the first box
     * @param s2 - the second box
     *
     * @return the attach signal.
     */
    Box CboxAttachAux(Box s1, Box s2)
    {
        return CboxSeq(CboxPar(s1, s2), CboxAttach());
    }
    
    /**
     * Compile a box expression in a null terminated array of signals.
     *
     * @param box - the box expression
     * @param error_msg - the error string to be filled
     *
     * @return a null terminated array of signals on success (to be deleted by the caller using freeCMemory), otherwise a nullptr.
     */
    Signal* CboxesToSignals(Box box, char* error_msg);
    
    /*
     [1] Constant numerical expression : see https://faustdoc.grame.fr/manual/syntax/#constant-numerical-expressions
     [2] Label definition : https://faustdoc.grame.fr/manual/syntax/#variable-parts-of-a-label
     */
    
#ifdef __cplusplus
}
#endif

#endif


