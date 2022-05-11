/***************************************************************************
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
 ***************************************************************************/

#ifndef LIBFAUSTCOMMON_H
#define LIBFAUSTCOMMON_H

#include <string>
#include <vector>

#include "faust/export.h"

/*!
 \addtogroup boxcpp C++ interface for the Box API.
 @{
 */

/**
 * Opaque types.
 */
class LIBFAUST_API CTree;
typedef std::vector<CTree*> tvec;

enum SType { kSInt, kSReal };

enum SOperator { kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };

/**
 * Base class for factories.
 */
struct LIBFAUST_API dsp_factory_base {
    
    virtual ~dsp_factory_base() {}
    
    virtual void write(std::ostream* out, bool binary = false, bool compact = false) {}
};

#endif

#ifndef LIBFAUSTBOX_H
#define LIBFAUSTBOX_H

/**
 * Opaque types.
 */
typedef CTree* Box;

/**
 * Create global compilation context, has to be done first.
 */
extern "C" LIBFAUST_API void createLibContext();

/**
 * Destroy global compilation context, has to be done last.
 */
extern "C" LIBFAUST_API void destroyLibContext();

/**
 * Constant integer : for all t, x(t) = n.
 *
 * @param n - the integer
 *
 * @return the integer box.
 */

LIBFAUST_API Box boxInt(int n);

/**
 * Constant real : for all t, x(t) = n.
 *
 * @param n - the float/double value (depends of -single or -double compilation parameter)
 *
 * @return the float/double box.
 */
LIBFAUST_API Box boxReal(double n);

/**
 * The identity box, copy its input to its output.
 *
 * @return the identity box.
 */
LIBFAUST_API Box boxWire();

/**
* The cut box, to "stop"/terminate a signal.
*
* @return the cut box.
*/
LIBFAUST_API Box boxCut();

/**
 * The sequential composition of two blocks (e.g., A:B) expects: outputs(A)=inputs(B)
 *
 * @return the seq box.
 */
LIBFAUST_API Box boxSeq(Box x, Box y);

/**
 * The parallel composition of two blocks (e.g., A,B).
 * It places the two block-diagrams one on top of the other, without connections.
 *
 * @return the par box.
 */
LIBFAUST_API Box boxPar(Box x, Box y);

LIBFAUST_API Box boxPar3(Box x, Box y, Box z);

LIBFAUST_API Box boxPar4(Box a, Box b, Box c, Box d);

LIBFAUST_API Box boxPar5(Box a, Box b, Box c, Box d, Box e);

/**
 * The split composition (e.g., A<:B) operator is used to distribute
 * the outputs of A to the inputs of B.
 *
 * For the operation to be valid, the number of inputs of B
 * must be a multiple of the number of outputs of A: outputs(A).k=inputs(B)
 *
 * @return the split box.
 */
LIBFAUST_API Box boxSplit(Box x, Box y);

/**
 * The merge composition (e.g., A:>B) is the dual of the split composition.
 *
 * The number of outputs of A must be a multiple of the number of inputs of B: outputs(A)=k.inputs(B)
 *
 * @return the merge box.
 */
LIBFAUST_API Box boxMerge(Box x, Box y);

/**
 * The recursive composition (e.g., A~B) is used to create cycles in the block-diagram
 * in order to express recursive computations.
 * It is the most complex operation in terms of connections: outputs(A)≥inputs(B) and inputs(A)≥outputs(B)
 *
 * @return the rec box.
 */
LIBFAUST_API Box boxRec(Box x, Box y);

/**
 * The route primitive facilitates the routing of signals in Faust.
 * It has the following syntax: route(A,B,a,b,c,d,...) or route(A,B,(a,b),(c,d),...)
 *
 * @param n -  the number of input signals
 * @param m -  the number of output signals
 * @param r - the routing description, a 'par' expression of a,b / (a,b) input/output pairs

 * @return the route box.
 */
LIBFAUST_API Box boxRoute(Box n, Box m, Box r);

/**
 * Create a delayed box.
 *
 * @return the delayed box.
 */
LIBFAUST_API Box boxDelay();

/**
 * Create a delayed box.
 *
 * @param s - the box to be delayed
 * @param del - the delay box that doesn't have to be fixed but must be bounded and cannot be negative

 * @return the delayed box.
 */
LIBFAUST_API Box boxDelay(Box s, Box del);

/**
 * Create a casted box.
 *
 * @return the casted box.
 */
LIBFAUST_API Box boxIntCast();

/**
 * Create a casted box.
 *
 * @param s - the box to be casted in integer
 *
 * @return the casted box.
 */
LIBFAUST_API Box boxIntCast(Box s);

/**
 * Create a casted box.
 *
 * @return the casted box.
 */
LIBFAUST_API Box boxFloatCast();

/**
 * Create a casted box.
 *
 * @param s - the signal to be casted as float/double value (depends of -single or -double compilation parameter)
 *
 * @return the casted box.
 */
LIBFAUST_API Box boxFloatCast(Box s);

/**
 * Create a read only table.
 *
 * @return the table box.
 */
LIBFAUST_API Box boxReadOnlyTable();

/**
 * Create a read only table.
 *
 * @param n - the table size, a constant numerical expression (see [1])
 * @param init - the table content
 * @param ridx - the read index (an int between 0 and n-1)
 *
 * @return the table box.
 */
LIBFAUST_API Box boxReadOnlyTable(Box n, Box init, Box ridx);

/**
 * Create a read/write table.
 *
 * @return the table box.
 */
LIBFAUST_API Box boxWriteReadTable();

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
LIBFAUST_API Box boxWriteReadTable(Box n, Box init, Box widx, Box wsig, Box ridx);

/**
 * Create a waveform.
 *
 * @param wf - the content of the waveform as a vector of boxInt or boxDouble boxes
 *
 * @return the waveform box.
 */
LIBFAUST_API Box boxWaveform(const tvec& wf);

/**
 * Create a soundfile block.
 *
 * @param label - of form "label[url:{'path1';'path2';'path3'}]" to describe a list of soundfiles
 * @param chan - the number of outputs channels, a constant numerical expression (see [1])
 *
 * @return the soundfile box.
 */
LIBFAUST_API Box boxSoundfile(const std::string& label, Box chan);

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
LIBFAUST_API Box boxSoundfile(const std::string& label, Box chan, Box part, Box ridx);

/**
 * Create a selector between two boxes.
 *
 * @return the selected box depending of the selector value at each time t.
 */
LIBFAUST_API Box boxSelect2();

/**
 * Create a selector between two boxes.
 *
 * @param selector - when 0 at time t returns s1[t], otherwise returns s2[t]
 * @param s1 - first box to be selected
 * @param s2 - second box to be selected
 *
 * @return the selected box depending of the selector value at each time t.
 */
LIBFAUST_API Box boxSelect2(Box selector, Box s1, Box s2);

/**
 * Create a selector between three boxes.
 *
 * @return the selected box depending of the selector value at each time t.
 */
LIBFAUST_API Box boxSelect3();

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
LIBFAUST_API Box boxSelect3(Box selector, Box s1, Box s2, Box s3);

/**
 * Create a foreign constant box.
 *
 * @param type - the foreign constant type of SType
 * @param name - the foreign constant name
 * @param file - the include file where the foreign constant is defined
 *
 * @return the foreign constant box.
 */
LIBFAUST_API Box boxFConst(SType type, const std::string& name, const std::string& file);

/**
 * Create a foreign variable box.
 *
 * @param type - the foreign variable type of SType
 * @param name - the foreign variable name
 * @param file - the include file where the foreign variable is defined
 *
 * @return the foreign variable box.
 */
LIBFAUST_API Box boxFVar(SType type, const std::string& name, const std::string& file);

/**
 * Generic binary mathematical functions.
 *
 * @param op - the operator in SOperator set
 *
 * @return the result box of op(x,y).
 */
LIBFAUST_API Box boxBinOp(SOperator op);

LIBFAUST_API Box boxBinOp(SOperator op, Box b1, Box b2);

/**
 * Specific binary mathematical functions.
 *
 * @return the result box.
 */
LIBFAUST_API Box boxAdd();
LIBFAUST_API Box boxAdd(Box b1, Box b2);
LIBFAUST_API Box boxSub();
LIBFAUST_API Box boxSub(Box b1, Box b2);
LIBFAUST_API Box boxMul();
LIBFAUST_API Box boxMul(Box b1, Box b2);
LIBFAUST_API Box boxDiv();
LIBFAUST_API Box boxDiv(Box b1, Box b2);
LIBFAUST_API Box boxRem();
LIBFAUST_API Box boxRem(Box b1, Box b2);

LIBFAUST_API Box boxLeftShift();
LIBFAUST_API Box boxLeftShift(Box b1, Box b2);
LIBFAUST_API Box boxLRightShift();
LIBFAUST_API Box boxLRightShift(Box b1, Box b2);
LIBFAUST_API Box boxARightShift();
LIBFAUST_API Box boxARightShift(Box b1, Box b2);

LIBFAUST_API Box boxGT();
LIBFAUST_API Box boxGT(Box b1, Box b2);
LIBFAUST_API Box boxLT();
LIBFAUST_API Box boxLT(Box b1, Box b2);
LIBFAUST_API Box boxGE();
LIBFAUST_API Box boxGE(Box b1, Box b2);
LIBFAUST_API Box boxLE();
LIBFAUST_API Box boxLE(Box b1, Box b2);
LIBFAUST_API Box boxEQ();
LIBFAUST_API Box boxEQ(Box b1, Box b2);
LIBFAUST_API Box boxNE();
LIBFAUST_API Box boxNE(Box b1, Box b2);

LIBFAUST_API Box boxAND();
LIBFAUST_API Box boxAND(Box b1, Box b2);
LIBFAUST_API Box boxOR();
LIBFAUST_API Box boxOR(Box b1, Box b2);
LIBFAUST_API Box boxXOR();
LIBFAUST_API Box boxXOR(Box b1, Box b2);

/**
 * Extended unary mathematical functions.
 */

LIBFAUST_API Box boxAbs();
LIBFAUST_API Box boxAbs(Box x);
LIBFAUST_API Box boxAcos();
LIBFAUST_API Box boxAcos(Box x);
LIBFAUST_API Box boxTan();
LIBFAUST_API Box boxTan(Box x);
LIBFAUST_API Box boxSqrt();
LIBFAUST_API Box boxSqrt(Box x);
LIBFAUST_API Box boxSin();
LIBFAUST_API Box boxSin(Box x);
LIBFAUST_API Box boxRint();
LIBFAUST_API Box boxRint(Box x);
LIBFAUST_API Box boxLog();
LIBFAUST_API Box boxLog(Box x);
LIBFAUST_API Box boxLog10();
LIBFAUST_API Box boxLog10(Box x);
LIBFAUST_API Box boxFloor();
LIBFAUST_API Box boxFloor(Box x);
LIBFAUST_API Box boxExp();
LIBFAUST_API Box boxExp(Box x);
LIBFAUST_API Box boxExp10();
LIBFAUST_API Box boxExp10(Box x);
LIBFAUST_API Box boxCos();
LIBFAUST_API Box boxCos(Box x);
LIBFAUST_API Box boxCeil();
LIBFAUST_API Box boxCeil(Box x);
LIBFAUST_API Box boxAtan();
LIBFAUST_API Box boxAtan(Box x);
LIBFAUST_API Box boxAsin();
LIBFAUST_API Box boxAsin(Box x);

/**
 * Extended binary mathematical functions.
 */

LIBFAUST_API Box boxRemainder();
LIBFAUST_API Box boxRemainder(Box b1, Box b2);
LIBFAUST_API Box boxPow();
LIBFAUST_API Box boxPow(Box b1, Box b2);
LIBFAUST_API Box boxMin();
LIBFAUST_API Box boxMin(Box b1, Box b2);
LIBFAUST_API Box boxMax();
LIBFAUST_API Box boxMax(Box b1, Box b2);
LIBFAUST_API Box boxFmod();
LIBFAUST_API Box boxFmod(Box b1, Box b2);
LIBFAUST_API Box boxAtan2();
LIBFAUST_API Box boxAtan2(Box b1, Box b2);

/**
 * Create a button box.
 *
 * @param label - the label definition (see [2])
 *
 * @return the button box.
 */
LIBFAUST_API Box boxButton(const std::string& label);

/**
 * Create a checkbox box.
 *
 * @param label - the label definition (see [2])
 *
 * @return the checkbox box.
 */
LIBFAUST_API Box boxCheckbox(const std::string& label);

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
LIBFAUST_API Box boxVSlider(const std::string& label, Box init, Box min, Box max, Box step);

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
LIBFAUST_API Box boxHSlider(const std::string& label, Box init, Box min, Box max, Box step);

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
LIBFAUST_API Box boxNumEntry(const std::string& label, Box init, Box min, Box max, Box step);

/**
 * Create a vertical bargraph box.
 *
 * @param label - the label definition (see [2])
 * @param min - the min box, a constant numerical expression (see [1])
 * @param max - the max box, a constant numerical expression (see [1])
 *
 * @return the vertical bargraph box.
 */
LIBFAUST_API Box boxVBargraph(const std::string& label, Box min, Box max);

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
LIBFAUST_API Box boxVBargraph(const std::string& label, Box min, Box max, Box x);

/**
 * Create an horizontal bargraph box.
 *
 * @param label - the label definition (see [2])
 * @param min - the min box, a constant numerical expression (see [1])
 * @param max - the max box, a constant numerical expression (see [1])
 *
 * @return the horizontal bargraph box.
 */
LIBFAUST_API Box boxHBargraph(const std::string& label, Box min, Box max);

/**
 * Create a horizontal bargraph box.
 *
 * @param label - the label definition (see [2])
 * @param min - the min box, a constant numerical expression (see [1])
 * @param max - the max box, a constant numerical expression (see [1])
 * @param x - the input box
 *
 * @return the vertical horizontal box.
 */
LIBFAUST_API Box boxHBargraph(const std::string& label, Box min, Box max, Box x);

/**
 * Create an attach box.
 *
 * The attach primitive takes two input boxes and produces one output box
 * which is a copy of the first input. The role of attach is to force
 * its second input boxes to be compiled with the first one.
 *
 * @return the attach box.
 */
LIBFAUST_API Box boxAttach();

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
LIBFAUST_API Box boxAttach(Box s1, Box s2);

/**
 * Compile a box expression in a list of signals.
 *
 * @param box - the box expression
 * @param error_msg - the error string to be filled
 *
 * @return a list of signals on success, otherwise an empty list.
 */
LIBFAUST_API tvec boxesToSignals(Box box, std::string& error_msg);

/**
 * Create a C++ Faust DSP factory from a box expression.
 *
 * @param name_app - the name of the Faust program
 * @param box - the box expression
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */
LIBFAUST_API  dsp_factory_base* createCPPDSPFactoryFromBoxes(const std::string& name_app, Box box,
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
