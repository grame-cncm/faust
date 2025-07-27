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
 ************************************************************************/

#include <stdbool.h>

#ifndef LIBFAUSTCOMMON_C_H
#define LIBFAUSTCOMMON_C_H

#include "faust/export.h"

/*!
 \addtogroup boxc C interface for the Box API.
 @{
 */

/**
 * Opaque types.
 */

#ifdef _MSC_VER
#define CTree_DEFINED
typedef void CTree;
#else
#define CTree_DEFINED
typedef struct {} CTree;
#endif

typedef CTree* Signal;
typedef CTree* Box;

enum SType { kSInt, kSReal };

enum SOperator { kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };

#ifdef __cplusplus
extern "C"
{
#endif
    
    /**
     * Print the box.
     *
     * @param box - the box to be printed
     * @param shared - whether the identical sub boxes are printed as identifiers
     * @param max_size - the maximum number of characters to be printed (possibly needed for big expressions in non shared mode)
     *
     * @return the printed box as a string (to be deleted by the caller using freeCMemory)
     */
    LIBFAUST_API char* CprintBox(Box box, bool shared, int max_size);
    
    /**
     * Print the signal.
     *
     * @param sig - the signal to be printed
     * @param shared - whether the identical sub signals are printed as identifiers
     * @param max_size - the maximum number of characters to be printed (possibly needed for big expressions in non shared mode)
     *
     * @return the printed signal as a string (to be deleted by the caller using freeCMemory)
     */
    LIBFAUST_API char* CprintSignal(Signal sig, bool shared, int max_size);
    
#ifdef __cplusplus
}
#endif

#endif

#ifndef LIBFAUSTBOX_C_H
#define LIBFAUSTBOX_C_H

#ifdef __cplusplus
extern "C"
{
#endif
    
    /**
     * Create global compilation context, has to be done first,
     * and paired with a call to destroyLibContext().
     */
    LIBFAUST_API void createLibContext();
    
    /**
     * Destroy global compilation context, has to be done last,
     * and paired with a call to createLibContext().
     * Note that the created DSP factory can be used outside
     * of the createLibContext/destroyLibContext scope.
     */
    LIBFAUST_API void destroyLibContext();

    /**
     * Check if a box is nil.
     *
     * @param b - the box
     *
     * @return true if the box is nil, otherwise false.
     */
    LIBFAUST_API bool CisNil(Box b);

    /**
     * Convert a box (such as the label of a UI) to a string.
     *
     * @param b - the box to convert
     *
     * @return a string representation of a box.
     */
    LIBFAUST_API const char* Ctree2str(Box b);

    /**
     * If t has a node of type int, return it. Otherwise error
     *
     * @param b - the box to convert
     *
     * @return the int value of the box.
     */
    LIBFAUST_API int Ctree2int(Box b);

    /**
     * Return the xtended type of a box.
     *
     * @param b - the box whose xtended type to return
     *
     * @return a pointer to xtended type if it exists, otherwise nullptr.
     */
    LIBFAUST_API void* CgetUserData(Box b);

    /**
     * Constant integer : for all t, x(t) = n.
     *
     * @param n - the integer
     *
     * @return the integer box.
     */
    
    LIBFAUST_API Box CboxInt(int n);
    
    /**
     * Constant real : for all t, x(t) = n.
     *
     * @param n - the float/double value (depends of -single or -double compilation parameter)
     *
     * @return the float/double box.
     */
    LIBFAUST_API Box CboxReal(double n);
    
    /**
     * The identity box, copy its input to its output.
     *
     * @return the identity box.
     */
    LIBFAUST_API Box CboxWire();
    
    /**
     * The cut box, to "stop"/terminate a signal.
     *
     * @return the cut box.
     */
    LIBFAUST_API Box CboxCut();
    
    /**
     * The sequential composition of two blocks (e.g., A:B) expects: outputs(A)=inputs(B)
     *
     * @return the seq box.
     */
    LIBFAUST_API Box CboxSeq(Box x, Box y);
    
    /**
     * The parallel composition of two blocks (e.g., A,B).
     * It places the two block-diagrams one on top of the other, without connections.
     *
     * @return the par box.
     */
    LIBFAUST_API Box CboxPar(Box x, Box y);
    
    LIBFAUST_API Box CboxPar3(Box x, Box y, Box z);
    
    LIBFAUST_API Box CboxPar4(Box a, Box b, Box c, Box d);
    
    LIBFAUST_API Box CboxPar5(Box a, Box b, Box c, Box d, Box e);
    
    /**
     * The split composition (e.g., A<:B) operator is used to distribute
     * the outputs of A to the inputs of B.
     *
     * For the operation to be valid, the number of inputs of B
     * must be a multiple of the number of outputs of A: outputs(A).k=inputs(B)
     *
     * @return the split box.
     */
    LIBFAUST_API Box CboxSplit(Box x, Box y);
    
    /**
     * The merge composition (e.g., A:>B) is the dual of the split composition.
     *
     * The number of outputs of A must be a multiple of the number of inputs of B: outputs(A)=k.inputs(B)
     *
     * @return the merge box.
     */
    LIBFAUST_API Box CboxMerge(Box x, Box y);
    
    /**
     * The recursive composition (e.g., A~B) is used to create cycles in the block-diagram
     * in order to express recursive computations.
     * It is the most complex operation in terms of connections: outputs(A)≥inputs(B) and inputs(A)≥outputs(B)
     *
     * @return the rec box.
     */
    LIBFAUST_API Box CboxRec(Box x, Box y);
    
    /**
     * The route primitive facilitates the routing of signals in Faust.
     * It has the following syntax: route(A,B,a,b,c,d,...) or route(A,B,(a,b),(c,d),...)
     *
     * @param n -  the number of input signals
     * @param m -  the number of output signals
     * @param r - the routing description, a 'par' expression of a,b / (a,b) input/output pairs
     
     * @return the route box.
     */
    LIBFAUST_API Box CboxRoute(Box n, Box m, Box r);
    
    /**
     * Create a delayed box.
     *
     * @return the delayed box.
     */
    LIBFAUST_API Box CboxDelay();
    
    /**
     * Create a delayed box.
     *
     * @param s - the box to be delayed
     * @param del - the delay box that doesn't have to be fixed but must be bounded and cannot be negative
     
     * @return the delayed box.
     */
    LIBFAUST_API Box CboxDelayAux(Box b, Box del);
    
    /**
     * Create a casted box.
     *
     * @return the casted box.
     */
    LIBFAUST_API Box CboxIntCast();
    
    /**
     * Create a casted box.
     *
     * @param s - the box to be casted in integer
     *
     * @return the casted box.
     */
    LIBFAUST_API Box CboxIntCastAux(Box b);
    
    /**
     * Create a casted box.
     *
     * @return the casted box.
     */
    LIBFAUST_API Box CboxFloatCast();
    
    /**
     * Create a casted box.
     *
     * @param s - the signal to be casted as float/double value (depends of -single or -double compilation parameter)
     *
     * @return the casted box.
     */
    LIBFAUST_API Box CboxFloatCastAux(Box b);
    
    /**
     * Create a read only table.
     *
     * @return the table box.
     */
    LIBFAUST_API Box CboxReadOnlyTable();
    
    /**
     * Create a read only table.
     *
     * @param n - the table size, a constant numerical expression (see [1])
     * @param init - the table content
     * @param ridx - the read index (an int between 0 and n-1)
     *
     * @return the table box.
     */
    LIBFAUST_API Box CboxReadOnlyTableAux(Box n, Box init, Box ridx);
    
    /**
     * Create a read/write table.
     *
     * @return the table box.
     */
    LIBFAUST_API Box CboxWriteReadTable();
    
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
    LIBFAUST_API Box CboxWriteReadTableAux(Box n, Box init, Box widx, Box wsig, Box ridx);
    
    /**
     * Create a waveform.
     *
     * @param wf - the content of the waveform as a vector of boxInt or boxDouble boxes
     *
     * @return the waveform box.
     */
    LIBFAUST_API Box CboxWaveform(Box* wf);
    
    /**
     * Create a soundfile block.
     *
     * @param label - of form "label[url:{'path1';'path2';'path3'}]" to describe a list of soundfiles
     * @param chan - the number of outputs channels, a constant numerical expression (see [1])
     *
     * @return the soundfile box.
     */
    LIBFAUST_API Box CboxSoundfile(const char* label, Box chan);
    
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
    Box CoxSoundfileAux(const char* label, Box chan, Box part, Box ridx);
    
    /**
     * Create a selector between two boxes.
     *
     * @return the selected box depending of the selector value at each time t.
     */
    LIBFAUST_API Box CboxSelect2();
    
    /**
     * Create a selector between two boxes.
     *
     * @param selector - when 0 at time t returns s1[t], otherwise returns s2[t]
     * @param s1 - first box to be selected
     * @param s2 - second box to be selected
     *
     * @return the selected box depending of the selector value at each time t.
     */
    LIBFAUST_API Box CboxSelect2Aux(Box selector, Box b1, Box b2);
    
    /**
     * Create a selector between three boxes.
     *
     * @return the selected box depending of the selector value at each time t.
     */
    LIBFAUST_API Box CboxSelect3();
    
    /**
     * Create a selector between three boxes.
     *
     * @param selector - when 0 at time t returns s1[t], when 1 at time t returns s2[t], otherwise returns s3[t]
     * @param s1 - first box to be selected
     * @param s2 - second box to be selected
     * @param s3 - third box to be selected
     *
     * @return the selected box depending of the selector value at each time t.
     */
    LIBFAUST_API Box CboxSelect3Aux(Box selector, Box b1, Box b2, Box b3);
    
    /**
     * Create a foreign function box.
     *
     * @param rtype - the foreign function return type of SType
     * @param names - the list of function names for single, double, quad, fixed-point
     * @param atypes - the list of arguments types
     * @param incfile - the include file where the foreign function is defined
     * @param libfile - the library file where the foreign function is defined
     *
     * @return the foreign function box.
     */
    LIBFAUST_API Box CboxFFun(enum SType rtype, const char** names, enum SType* atypes, const char* incfile, const char* libfile);

    /**
     * Create a foreign constant box.
     *
     * @param type - the foreign constant type of SType
     * @param name - the foreign constant name
     * @param incfile - the include file where the foreign constant is defined
     *
     * @return the foreign constant box.
     */
    LIBFAUST_API Box CboxFConst(enum SType type, const char* name, const char* incfile);
    
    /**
     * Create a foreign variable box.
     *
     * @param type - the foreign variable type of SType
     * @param name - the foreign variable name
     * @param incfile - the include file where the foreign variable is defined
     *
     * @return the foreign variable box.
     */
    LIBFAUST_API Box CboxFVar(enum SType type, const char* name, const char* incfile);
    
    /**
     * Generic binary mathematical functions.
     *
     * @param op - the operator in SOperator set
     *
     * @return the result box of op(x,y).
     */
    LIBFAUST_API Box CboxBinOp(SOperator op);
    
    LIBFAUST_API Box CboxBinOpAux(SOperator op, Box b1, Box b2);
    
    /**
     * Specific binary mathematical functions.
     *
     * @return the result box.
     */
    LIBFAUST_API Box CboxAdd();
    LIBFAUST_API Box CboxAddAux(Box b1, Box b2);
    LIBFAUST_API Box CboxSub();
    LIBFAUST_API Box CboxSubAux(Box b1, Box b2);
    LIBFAUST_API Box CboxMul();
    LIBFAUST_API Box CboxMulAux(Box b1, Box b2);
    LIBFAUST_API Box CboxDiv();
    LIBFAUST_API Box CboxDivAux(Box b1, Box b2);
    LIBFAUST_API Box CboxRem();
    LIBFAUST_API Box CboxRemAux(Box b1, Box b2);
    
    LIBFAUST_API Box CboxLeftShift();
    LIBFAUST_API Box CboxLeftShiftAux(Box b1, Box b2);
    LIBFAUST_API Box CboxLRightShift();
    LIBFAUST_API Box CboxLRightShiftAux(Box b1, Box b2);
    LIBFAUST_API Box CboxARightShift();
    LIBFAUST_API Box CboxARightShiftAux(Box b1, Box b2);
    
    LIBFAUST_API Box CboxGT();
    LIBFAUST_API Box CboxGTAux(Box b1, Box b2);
    LIBFAUST_API Box CboxLT();
    LIBFAUST_API Box CboxLTAux(Box b1, Box b2);
    LIBFAUST_API Box CboxGE();
    LIBFAUST_API Box CboxGEAux(Box b1, Box b2);
    LIBFAUST_API Box CboxLE();
    LIBFAUST_API Box CboxLEAux(Box b1, Box b2);
    LIBFAUST_API Box CboxEQ();
    LIBFAUST_API Box CboxEQAux(Box b1, Box b2);
    LIBFAUST_API Box CboxNE();
    LIBFAUST_API Box CboxNEAux(Box b1, Box b2);
    
    LIBFAUST_API Box CboxAND();
    LIBFAUST_API Box CboxANDAux(Box b1, Box b2);
    LIBFAUST_API Box CboxOR();
    LIBFAUST_API Box CboxORAux(Box b1, Box b2);
    LIBFAUST_API Box CboxXOR();
    LIBFAUST_API Box CboxXORAux(Box b1, Box b2);
    
    /**
     * Extended unary mathematical functions.
     */
    LIBFAUST_API Box CboxAbs();
    LIBFAUST_API Box CboxAbsAux(Box x);
    LIBFAUST_API Box CboxAcos();
    LIBFAUST_API Box CboxAcosAux(Box x);
    LIBFAUST_API Box CboxTan();
    LIBFAUST_API Box CboxTanAux(Box x);
    LIBFAUST_API Box CboxSqrt();
    LIBFAUST_API Box CboxSqrtAux(Box x);
    LIBFAUST_API Box CboxSin();
    LIBFAUST_API Box CboxSinAux(Box x);
    LIBFAUST_API Box CboxRint();
    LIBFAUST_API Box CboxRintAux(Box x);
    LIBFAUST_API Box CboxRound();
    LIBFAUST_API Box CboxRoundAux(Box x);
    LIBFAUST_API Box CboxLog();
    LIBFAUST_API Box CboxLogAux(Box x);
    LIBFAUST_API Box CboxLog10();
    LIBFAUST_API Box CboxLog10Aux(Box x);
    LIBFAUST_API Box CboxFloor();
    LIBFAUST_API Box CboxFloorAux(Box x);
    LIBFAUST_API Box CboxExp();
    LIBFAUST_API Box CboxExpAux(Box x);
    LIBFAUST_API Box CboxExp10();
    LIBFAUST_API Box CboxExp10Aux(Box x);
    LIBFAUST_API Box CboxCos();
    LIBFAUST_API Box CboxCosAux(Box x);
    LIBFAUST_API Box CboxCeil();
    LIBFAUST_API Box CboxCeilAux(Box x);
    LIBFAUST_API Box CboxAtan();
    LIBFAUST_API Box CboxAtanAux(Box x);
    LIBFAUST_API Box CboxAsin();
    LIBFAUST_API Box CboxAsinAux(Box x);
    
    /**
     * Extended binary mathematical functions.
     */
    LIBFAUST_API Box CboxRemainder();
    LIBFAUST_API Box CboxRemainderAux(Box b1, Box b2);
    LIBFAUST_API Box CboxPow();
    LIBFAUST_API Box CboxPowAux(Box b1, Box b2);
    LIBFAUST_API Box CboxMin();
    LIBFAUST_API Box CboxMinAux(Box b1, Box b2);
    LIBFAUST_API Box CboxMax();
    LIBFAUST_API Box CboxMaxAux(Box b1, Box b2);
    LIBFAUST_API Box CboxFmod();
    LIBFAUST_API Box CboxFmodAux(Box b1, Box b2);
    LIBFAUST_API Box CboxAtan2();
    LIBFAUST_API Box CboxAtan2Aux(Box b1, Box b2);
    
    /**
     * Create a button box.
     *
     * @param label - the label definition (see [2])
     *
     * @return the button box.
     */
    LIBFAUST_API Box CboxButton(const char* label);
    
    /**
     * Create a checkbox box.
     *
     * @param label - the label definition (see [2])
     *
     * @return the checkbox box.
     */
    LIBFAUST_API Box CboxCheckbox(const char* label);
    
    /**
     * Create a vertical slider box.
     *
     * @param label - the label definition (see [2])
     * @param init - the init box, a constant numerical expression (see [1])
     * @param min - the min box, a constant numerical expression (see [1])
     * @param max - the max box, a constant numerical expression (see [1])
     * @param step - the step box, a constant numerical expression (see [1])
     *
     * @return the vertical slider box.
     */
    LIBFAUST_API Box CboxVSlider(const char* label, Box init, Box min, Box max, Box step);
    
    /**
     * Create an horizontal slider box.
     *
     * @param label - the label definition (see [2])
     * @param init - the init box, a constant numerical expression (see [1])
     * @param min - the min box, a constant numerical expression (see [1])
     * @param max - the max box, a constant numerical expression (see [1])
     * @param step - the step box, a constant numerical expression (see [1])
     *
     * @return the horizontal slider box.
     */
    LIBFAUST_API Box CboxHSlider(const char* label, Box init, Box min, Box max, Box step);
    
    /**
     * Create a num entry box.
     *
     * @param label - the label definition (see [2])
     * @param init - the init box, a constant numerical expression (see [1])
     * @param min - the min box, a constant numerical expression (see [1])
     * @param max - the max box, a constant numerical expression (see [1])
     * @param step - the step box, a constant numerical expression (see [1])
     *
     * @return the num entry box.
     */
    LIBFAUST_API Box CboxNumEntry(const char* label, Box init, Box min, Box max, Box step);
    
    /**
     * Create a vertical bargraph box.
     *
     * @param label - the label definition (see [2])
     * @param min - the min box, a constant numerical expression (see [1])
     * @param max - the max box, a constant numerical expression (see [1])
     *
     * @return the vertical bargraph box.
     */
    LIBFAUST_API Box CboxVBargraph(const char* label, Box min, Box max);
    
    /**
     * Create a vertical bargraph box.
     *
     * @param label - the label definition (see [2])
     * @param min - the min box, a constant numerical expression (see [1])
     * @param max - the max box, a constant numerical expression (see [1])
     * @param x - the input box
     *
     * @return the vertical bargraph box.
     */
    LIBFAUST_API Box CboxVBargraphAux(const char* label, Box min, Box max, Box x);
    
    /**
     * Create an horizontal bargraph box.
     *
     * @param label - the label definition (see [2])
     * @param min - the min box, a constant numerical expression (see [1])
     * @param max - the max box, a constant numerical expression (see [1])
     *
     * @return the horizontal bargraph box.
     */
    LIBFAUST_API Box CboxHBargraph(const char* label, Box min, Box max);
    
    /**
     * Create a horizontal bargraph box.
     *
     * @param label - the label definition (see [2])
     * @param min - the min box, a constant numerical expression (see [1])
     * @param max - the max box, a constant numerical expression (see [1])
     * @param x - the input box
     *
     * @return the horizontal bargraph box.
     */
    LIBFAUST_API Box CboxHBargraphAux(const char* label, Box min, Box max, Box x);
    
    /**
     * Create a vertical group box.
     * @param label - the label definition (see [2])
     * @param group - the group to be added
     *
     * @return the vertical group box.
     */
    LIBFAUST_API Box CboxVGroup(const char* label, Box group);
    
    /**
     * Create a horizontal group box.
     * @param label - the label definition (see [2])
     * @param group - the group to be added
     *
     * @return the horizontal group box.
     */
    LIBFAUST_API Box CboxHGroup(const char* label, Box group);
    
    /**
     * Create a tab group box.
     * @param label - the label definition (see [2])
     * @param group - the group to be added
     *
     * @return the tab group box.
     */
    LIBFAUST_API Box CboxTGroup(const char* label, Box group);

    /**
     * Create an attach box.
     *
     * The attach primitive takes two input boxes and produces one output box
     * which is a copy of the first input. The role of attach is to force
     * its second input boxes to be compiled with the first one.
     *
     * @return the attach box.
     */
    LIBFAUST_API Box CboxAttach();
    
    /**
     * Create an attach box.
     *
     * The attach primitive takes two input box and produces one output box
     * which is a copy of the first input. The role of attach is to force
     * its second input box to be compiled with the first one.
     *
     * @param s1 - the first box
     * @param s2 - the second box
     *
     * @return the attach box.
     */
    LIBFAUST_API Box CboxAttachAux(Box b1, Box b2);

    LIBFAUST_API bool CisBoxAbstr(Box t, Box* x, Box* y);
    LIBFAUST_API bool CisBoxAccess(Box t, Box* exp, Box* id);
    LIBFAUST_API bool CisBoxAppl(Box t, Box* x, Box* y);
    LIBFAUST_API bool CisBoxButton(Box b, Box* lbl);
    LIBFAUST_API bool CisBoxCase(Box b, Box* rules);
    LIBFAUST_API bool CisBoxCheckbox(Box b, Box* lbl);
    LIBFAUST_API bool CisBoxComponent(Box b, Box* filename);
    LIBFAUST_API bool CisBoxCut(Box t);
    LIBFAUST_API bool CisBoxEnvironment(Box b);
    LIBFAUST_API bool CisBoxError(Box t);
    LIBFAUST_API bool CisBoxFConst(Box b, Box* type, Box* name, Box* file);
    LIBFAUST_API bool CisBoxFFun(Box b, Box* ff);
    LIBFAUST_API bool CisBoxFVar(Box b, Box* type, Box* name, Box* file);
    LIBFAUST_API bool CisBoxHBargraph(Box b, Box* lbl, Box* min, Box* max);
    LIBFAUST_API bool CisBoxHGroup(Box b, Box* lbl, Box* x);
    LIBFAUST_API bool CisBoxHSlider(Box b, Box* lbl, Box* cur, Box* min, Box* max, Box* step);
    LIBFAUST_API bool CisBoxIdent(Box t, const char** str);
    LIBFAUST_API bool CisBoxInputs(Box t, Box* x);
    LIBFAUST_API bool CisBoxInt(Box t, int* i);
    LIBFAUST_API bool CisBoxIPar(Box t, Box* x, Box* y, Box* z);
    LIBFAUST_API bool CisBoxIProd(Box t, Box* x, Box* y, Box* z);
    LIBFAUST_API bool CisBoxISeq(Box t, Box* x, Box* y, Box* z);
    LIBFAUST_API bool CisBoxISum(Box t, Box* x, Box* y, Box* z);
    LIBFAUST_API bool CisBoxLibrary(Box b, Box* filename);
    LIBFAUST_API bool CisBoxMerge(Box t, Box* x, Box* y);
    LIBFAUST_API bool CisBoxMetadata(Box b, Box* exp, Box* mdlist);
    LIBFAUST_API bool CisBoxNumEntry(Box b, Box* lbl, Box* cur, Box* min, Box* max, Box* step);
    LIBFAUST_API bool CisBoxOutputs(Box t, Box* x);
    LIBFAUST_API bool CisBoxPar(Box t, Box* x, Box* y);
    LIBFAUST_API bool CisBoxPatternMatcher(Box b);
    LIBFAUST_API bool CisBoxPatternVar(Box b, Box* id);
    LIBFAUST_API bool CisBoxPrim0(Box b);
    LIBFAUST_API bool CisBoxPrim1(Box b);
    LIBFAUST_API bool CisBoxPrim2(Box b);
    LIBFAUST_API bool CisBoxPrim3(Box b);
    LIBFAUST_API bool CisBoxPrim4(Box b);
    LIBFAUST_API bool CisBoxPrim5(Box b);
    LIBFAUST_API bool CisBoxReal(Box t, double* r);
    LIBFAUST_API bool CisBoxRec(Box t, Box* x, Box* y);
    LIBFAUST_API bool CisBoxRoute(Box b, Box* n, Box* m, Box* r);
    LIBFAUST_API bool CisBoxSeq(Box t, Box* x, Box* y);
    LIBFAUST_API bool CisBoxSlot(Box t, int* id);
    LIBFAUST_API bool CisBoxSoundfile(Box b, Box* label, Box* chan);
    LIBFAUST_API bool CisBoxSplit(Box t, Box* x, Box* y);
    LIBFAUST_API bool CisBoxSymbolic(Box t, Box* slot, Box* body);
    LIBFAUST_API bool CisBoxTGroup(Box b, Box* lbl, Box* x);
    LIBFAUST_API bool CisBoxVBargraph(Box b, Box* lbl, Box* min, Box* max);
    LIBFAUST_API bool CisBoxVGroup(Box b, Box* lbl, Box* x);
    LIBFAUST_API bool CisBoxVSlider(Box b, Box* lbl, Box* cur, Box* min, Box* max, Box* step);
    LIBFAUST_API bool CisBoxWaveform(Box b);
    LIBFAUST_API bool CisBoxWire(Box t);
    LIBFAUST_API bool CisBoxWithLocalDef(Box t, Box* body, Box* ldef);

    /**
     * Compile a DSP source code as a string in a flattened box
     *
     * @param name_app - the name of the Faust program
     * @param dsp_content - the Faust program as a string
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param inputs - the place to return the number of inputs of the resulting box
     * @param outputs - the place to return the number of outputs of the resulting box
     * @param error_msg - the error string to be filled
     *
     * @return a flattened box on success, otherwise a null pointer.
     */
    LIBFAUST_API Box CDSPToBoxes(const char* name_app, const char* dsp_content, int argc, const char* argv[], int* inputs, int* outputs, char* error_msg);
    
    /**
     * Return the number of inputs and outputs of a box
     *
     * @param box - the box we want to know the number of inputs and outputs
     * @param inputs - the place to return the number of inputs
     * @param outputs - the place to return the number of outputs
     *
     * @return true if type is defined, false if undefined.
     */
    LIBFAUST_API bool CgetBoxType(Box box, int* inputs, int* outputs);

    /**
     * Compile a box expression in a null terminated array of signals in normal form
     * (see CsimplifyToNormalForm in libfaust-signal-c.h)
     *
     * @param box - the box expression
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return a null terminated array of signals on success (to be deleted by the caller using freeCMemory), otherwise a nullptr.
     */
    LIBFAUST_API Signal* CboxesToSignals(Box box, char* error_msg);
    
    /**
     * Create source code in a target language from a box expression.
     *
     * @param name_app - the name of the Faust program
     * @param box - the box expression
     * @param lang - the target source code's language which can be one of "c",
     * "cpp", "cmajor", "codebox", "csharp", "dlang", "fir", "interp", "java", "jax",
     * "jsfx", "julia", "ocpp", "rust" or "wast"
     * (depending of which of the corresponding backends are compiled in libfaust)
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param error_msg - the error string to be filled
     *
     * @return a string of source code on success (to be deleted by the caller using freeCMemory) or a nullptr and setting error_msg on error.
     */
    LIBFAUST_API char* CcreateSourceFromBoxes(const char* name_app, Box box,
                                            const char* lang,
                                            int argc, const char* argv[],
                                            char* error_msg);
  
    /**
     * The free function to be used on memory returned CcreateSourceFromBoxes.
     *
     * This is MANDATORY on Windows when otherwise all nasty runtime version related crashes can occur.
     *
     * @param ptr - the pointer to be deleted.
     */
    LIBFAUST_API void freeCMemory(void* ptr);
    
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
