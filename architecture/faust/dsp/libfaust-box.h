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

#include <string>
#include <vector>
#include <ostream>

#ifndef LIBFAUSTCOMMON_H
#define LIBFAUSTCOMMON_H

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

#ifndef LIBFAUSTBOX_H
#define LIBFAUSTBOX_H

/**
 * Indicates the identifier (if any) the expression was a definition of.
 *
 * @param b the expression
 * @param id reference to the identifier
 *
 * @return true if the expression b was a definition of id
 **/
LIBFAUST_API bool getDefNameProperty(Box b, Box& id);

/**
 * Extract the name from a label.
 *
 * @param full_label the label to be analyzed
 *
 * @return the extracted name
 **/
LIBFAUST_API std::string extractName(Box full_label);

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
 * Check if a box is nil.
 *
 * @param b - the box
 *
 * @return true if the box is nil, otherwise false.
 */
LIBFAUST_API bool isNil(Box b);

/**
 * Convert a box (such as the label of a UI) to a string.
 *
 * @param b - the box to convert
 *
 * @return a string representation of a box.
 */
LIBFAUST_API const char* tree2str(Box b);

/**
 * If t has a node of type int, return it. Otherwise error
 *
 * @param b - the box to convert
 *
 * @return the int value of the box.
 */
LIBFAUST_API int tree2int(Box b);

/**
 * Return the xtended type of a box.
 *
 * @param b - the box whose xtended type to return
 *
 * @return a pointer to xtended type if it exists, otherwise nullptr.
 */
LIBFAUST_API void* getUserData(Box b);

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
LIBFAUST_API Box boxDelay(Box b, Box del);

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
LIBFAUST_API Box boxIntCast(Box b);

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
LIBFAUST_API Box boxFloatCast(Box b);

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
LIBFAUST_API Box boxSelect2(Box selector, Box b1, Box b2);

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
 * @param s3 - third box to be selected
 *
 * @return the selected box depending of the selector value at each time t.
 */
LIBFAUST_API Box boxSelect3(Box selector, Box b1, Box b2, Box b3);

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
LIBFAUST_API Box boxFFun(SType rtype, nvec names, svec atypes, const std::string& incfile, const std::string& libfile);

/**
 * Create a foreign constant box.
 *
 * @param type - the foreign constant type of SType
 * @param name - the foreign constant name
 * @param incfile - the include file where the foreign constant is defined
 *
 * @return the foreign constant box.
 */
LIBFAUST_API Box boxFConst(SType type, const std::string& name, const std::string& incfile);

/**
 * Create a foreign variable box.
 *
 * @param type - the foreign variable type of SType
 * @param name - the foreign variable name
 * @param incfile - the include file where the foreign variable is defined
 *
 * @return the foreign variable box.
 */
LIBFAUST_API Box boxFVar(SType type, const std::string& name, const std::string& incfile);

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
LIBFAUST_API Box boxRound();
LIBFAUST_API Box boxRound(Box x);
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
 * @return the horizontal bargraph box.
 */
LIBFAUST_API Box boxHBargraph(const std::string& label, Box min, Box max, Box x);

/**
 * Create a vertical group box.
 * @param label - the label definition (see [2])
 * @param group - the group to be added
 *
 * @return the vertical group box.
 */
LIBFAUST_API Box boxVGroup(const std::string& label, Box group);

/**
 * Create a horizontal group box.
 * @param label - the label definition (see [2])
 * @param group - the group to be added
 *
 * @return the horizontal group box.
 */
LIBFAUST_API Box boxHGroup(const std::string& label, Box group);

/**
 * Create a tab group box.
 * @param label - the label definition (see [2])
 * @param group - the group to be added
 *
 * @return the tab group box.
 */
LIBFAUST_API Box boxTGroup(const std::string& label, Box group);

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
 * its second input box to be compiled with the first one.
 *
 * @param s1 - the first box
 * @param s2 - the second box
 *
 * @return the attach box.
 */
LIBFAUST_API Box boxAttach(Box b1, Box b2);

LIBFAUST_API Box boxPrim2(prim2 foo);

/**
 * Test each box and fill additional boxe specific parameters.
 *
 * @return true and fill the specific parameters if the box is of a given type, false otherwise
 */
LIBFAUST_API bool isBoxAbstr(Box t);
LIBFAUST_API bool isBoxAbstr(Box t, Box& x, Box& y);
LIBFAUST_API bool isBoxAccess(Box t, Box& exp, Box& id);
LIBFAUST_API bool isBoxAppl(Box t);
LIBFAUST_API bool isBoxAppl(Box t, Box& x, Box& y);
LIBFAUST_API bool isBoxButton(Box b);
LIBFAUST_API bool isBoxButton(Box b, Box& lbl);
LIBFAUST_API bool isBoxCase(Box b);
LIBFAUST_API bool isBoxCase(Box b, Box& rules);
LIBFAUST_API bool isBoxCheckbox(Box b);
LIBFAUST_API bool isBoxCheckbox(Box b, Box& lbl);
LIBFAUST_API bool isBoxComponent(Box b, Box& filename);
LIBFAUST_API bool isBoxCut(Box t);
LIBFAUST_API bool isBoxEnvironment(Box b);
LIBFAUST_API bool isBoxError(Box t);
LIBFAUST_API bool isBoxFConst(Box b);
LIBFAUST_API bool isBoxFConst(Box b, Box& type, Box& name, Box& file);
LIBFAUST_API bool isBoxFFun(Box b);
LIBFAUST_API bool isBoxFFun(Box b, Box& ff);
LIBFAUST_API bool isBoxFVar(Box b);
LIBFAUST_API bool isBoxFVar(Box b, Box& type, Box& name, Box& file);
LIBFAUST_API bool isBoxHBargraph(Box b);
LIBFAUST_API bool isBoxHBargraph(Box b, Box& lbl, Box& min, Box& max);
LIBFAUST_API bool isBoxHGroup(Box b);
LIBFAUST_API bool isBoxHGroup(Box b, Box& lbl, Box& x);
LIBFAUST_API bool isBoxHSlider(Box b);
LIBFAUST_API bool isBoxHSlider(Box b, Box& lbl, Box& cur, Box& min, Box& max, Box& step);
LIBFAUST_API bool isBoxIdent(Box t);
LIBFAUST_API bool isBoxIdent(Box t, const char** str);
LIBFAUST_API bool isBoxInputs(Box t, Box& x);
LIBFAUST_API bool isBoxInt(Box t);
LIBFAUST_API bool isBoxInt(Box t, int* i);
LIBFAUST_API bool isBoxIPar(Box t, Box& x, Box& y, Box& z);
LIBFAUST_API bool isBoxIProd(Box t, Box& x, Box& y, Box& z);
LIBFAUST_API bool isBoxISeq(Box t, Box& x, Box& y, Box& z);
LIBFAUST_API bool isBoxISum(Box t, Box& x, Box& y, Box& z);
LIBFAUST_API bool isBoxLibrary(Box b, Box& filename);
LIBFAUST_API bool isBoxMerge(Box t, Box& x, Box& y);
LIBFAUST_API bool isBoxMetadata(Box b, Box& exp, Box& mdlist);
LIBFAUST_API bool isBoxNumEntry(Box b);
LIBFAUST_API bool isBoxNumEntry(Box b, Box& lbl, Box& cur, Box& min, Box& max, Box& step);
LIBFAUST_API bool isBoxOutputs(Box t, Box& x);
LIBFAUST_API bool isBoxPar(Box t, Box& x, Box& y);
LIBFAUST_API bool isBoxPrim0(Box b);
LIBFAUST_API bool isBoxPrim1(Box b);
LIBFAUST_API bool isBoxPrim2(Box b);
LIBFAUST_API bool isBoxPrim3(Box b);
LIBFAUST_API bool isBoxPrim4(Box b);
LIBFAUST_API bool isBoxPrim5(Box b);
LIBFAUST_API bool isBoxPrim0(Box b, prim0* p);
LIBFAUST_API bool isBoxPrim1(Box b, prim1* p);
LIBFAUST_API bool isBoxPrim2(Box b, prim2* p);
LIBFAUST_API bool isBoxPrim3(Box b, prim3* p);
LIBFAUST_API bool isBoxPrim4(Box b, prim4* p);
LIBFAUST_API bool isBoxPrim5(Box b, prim5* p);
LIBFAUST_API bool isBoxReal(Box t);
LIBFAUST_API bool isBoxReal(Box t, double* r);
LIBFAUST_API bool isBoxRec(Box t, Box& x, Box& y);
LIBFAUST_API bool isBoxRoute(Box b, Box& n, Box& m, Box& r);
LIBFAUST_API bool isBoxSeq(Box t, Box& x, Box& y);
LIBFAUST_API bool isBoxSlot(Box t);
LIBFAUST_API bool isBoxSlot(Box t, int* id);
LIBFAUST_API bool isBoxSoundfile(Box b);
LIBFAUST_API bool isBoxSoundfile(Box b, Box& label, Box& chan);
LIBFAUST_API bool isBoxSplit(Box t, Box& x, Box& y);
LIBFAUST_API bool isBoxSymbolic(Box t);
LIBFAUST_API bool isBoxSymbolic(Box t, Box& slot, Box& body);
LIBFAUST_API bool isBoxTGroup(Box b);
LIBFAUST_API bool isBoxTGroup(Box b, Box& lbl, Box& x);
LIBFAUST_API bool isBoxVBargraph(Box b);
LIBFAUST_API bool isBoxVBargraph(Box b, Box& lbl, Box& min, Box& max);
LIBFAUST_API bool isBoxVGroup(Box b);
LIBFAUST_API bool isBoxVGroup(Box b, Box& lbl, Box& x);
LIBFAUST_API bool isBoxVSlider(Box b);
LIBFAUST_API bool isBoxVSlider(Box b, Box& lbl, Box& cur, Box& min, Box& max, Box& step);
LIBFAUST_API bool isBoxWaveform(Box b);
LIBFAUST_API bool isBoxWire(Box t);
LIBFAUST_API bool isBoxWithLocalDef(Box t, Box& body, Box& ldef);

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
LIBFAUST_API Box DSPToBoxes(const std::string& name_app, const std::string& dsp_content, int argc, const char* argv[], int* inputs, int* outputs, std::string& error_msg);

/**
 * Return the number of inputs and outputs of a box
 *
 * @param box - the box we want to know the number of inputs and outputs
 * @param inputs - the place to return the number of inputs
 * @param outputs - the place to return the number of outputs
 *
 * @return true if type is defined, false if undefined.
 */
LIBFAUST_API bool getBoxType(Box box, int* inputs, int* outputs);

/**
 * Compile a box expression in a list of signals in normal form
 * (see simplifyToNormalForm in libfaust-signal.h)
 *
 * @param box - the box expression
 * @param error_msg - the error string to be filled
 *
 * @return a list of signals in normal form on success, otherwise an empty list.
 */
LIBFAUST_API tvec boxesToSignals(Box box, std::string& error_msg);

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
 * @return a string of source code on success, setting error_msg on error.
 */
LIBFAUST_API std::string createSourceFromBoxes(const std::string& name_app, Box box,
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
