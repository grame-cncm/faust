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

#ifndef LIBFAUSTSIGNAL_H
#define LIBFAUSTSIGNAL_H

#include <string>
#include <vector>

#include "faust/dsp/dsp.h"

/*****************************************************************************
 Signal language
 *****************************************************************************/

// Opaque types
class CTree;
typedef CTree* Signal;
typedef std::vector<Signal> tvec;

// Constant signals : for all t, x(t)=n
Signal sigInt(int n);
Signal sigReal(double n);

// Inputs
Signal sigInput(int i);

// Delay
Signal sigFixDelay(Signal t0, Signal t1);

// Int and Double casting
Signal sigIntCast(Signal t);
Signal sigFloatCast(Signal t);

// Tables
Signal sigRDTbl(Signal t, Signal i);
Signal sigWRTbl(Signal id, Signal t, Signal i, Signal s);
Signal sigTable(Signal id, Signal n, Signal sig);
Signal sigGen(Signal content);

Signal sigWriteReadTable(Signal n, Signal init, Signal widx, Signal wsig, Signal ridx);
Signal sigReadOnlyTable(Signal n, Signal init, Signal ridx);

// Waveforms
Signal sigWaveform(const tvec& wf);
// Use: sigInt(tvec.size()); to generate the waveform size signal

// Soundfiles
Signal sigSoundfile(const std::string& label);
Signal sigSoundfileLength(Signal sf, Signal part);
Signal sigSoundfileRate(Signal sf, Signal part);
Signal sigSoundfileBuffer(Signal sf, Signal chan, Signal part, Signal ridx);

// Selectors
Signal sigSelect2(Signal selector, Signal s1, Signal s2);
Signal sigSelect3(Signal selector, Signal s1, Signal s2, Signal s3);

// Foreign functions
Signal sigFFun(Signal ff, tvec largs);

enum SType { kSInt, kSReal };

// Foreign constants
Signal sigFConst(SType type, const std::string& name, const std::string& file);

// Foreign variables
Signal sigFVar(SType type, const std::string& name, const std::string& file);

// Math functions

// Generic version
enum SOperator { kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };
Signal sigBinOp(SOperator op, Signal x, Signal y);

// Specific versions
Signal sigAdd(Signal x, Signal y);
Signal sigSub(Signal x, Signal y);
Signal sigMul(Signal x, Signal y);
Signal sigDiv(Signal x, Signal y);
Signal sigRem(Signal x, Signal y);

Signal sigLeftShift(Signal x, Signal y);
Signal sigRightShift(Signal x, Signal y);

Signal sigGT(Signal x, Signal y);
Signal sigLT(Signal x, Signal y);
Signal sigGE(Signal x, Signal y);
Signal sigLE(Signal x, Signal y);
Signal sigEQ(Signal x, Signal y);
Signal sigNE(Signal x, Signal y);

Signal sigAND(Signal x, Signal y);
Signal sigOR(Signal x, Signal y);
Signal sigXOR(Signal x, Signal y);

// Extended math functions
Signal sigAbs(Signal x);
Signal sigAcos(Signal x);
Signal sigTan(Signal x);
Signal sigSqrt(Signal x);
Signal sigSin(Signal x);
Signal sigRint(Signal x);
Signal sigRemainder(Signal x, Signal y);
Signal sigPow(Signal x, Signal y);
Signal sigMin(Signal x, Signal y);
Signal sigMax(Signal x, Signal y);
Signal sigLog(Signal x);
Signal sigLog10(Signal x);
Signal sigFmod(Signal x, Signal y);
Signal sigFloor(Signal x);
Signal sigExp(Signal x);
Signal sigExp10(Signal x);
Signal sigCos(Signal x);
Signal sigCeil(Signal x);
Signal sigAtan(Signal x);
Signal sigAtan2(Signal x, Signal y);
Signal sigAsin(Signal x);

// For recursive signals: sigSelf() has to be used in the sigRecursion(...) expression
Signal sigSelf();
Signal sigRecursion(Signal s);

/*****************************************************************************
 User Interface Elements
 *****************************************************************************/

Signal sigButton(const std::string& label);
Signal sigCheckbox(const std::string& label);
Signal sigVSlider(const std::string& label, Signal cur, Signal min, Signal max, Signal step);
Signal sigHSlider(const std::string& label, Signal cur, Signal min, Signal max, Signal step);
Signal sigNumEntry(const std::string& label, Signal cur, Signal min, Signal max, Signal step);

// Output elements
Signal sigVBargraph(const std::string& label, Signal min, Signal max, Signal x);
Signal sigHBargraph(const std::string& label, Signal min, Signal max, Signal x);
Signal sigAttach(Signal x, Signal y);

/**********************
 // Helpers functions
 **********************/

// Reproduce the 'SR' definition in platform.lib: SR = min(192000.0, max(1.0, fconstant(int fSamplingFreq, <dummy.h>)));
inline Signal getSampleRate()
{
    return sigMin(sigReal(192000.0), sigMax(sigReal(1.0), sigFConst(SType::kSInt, "fSamplingFreq", "<dummy.h>")));
}

// Reproduce the 'BS' definition in platform.lib: BS = fvariable(int count, <dummy.h>);
inline Signal getBufferSize()
{
    return sigFVar(SType::kSInt, "count", "<dummy.h>");
}

/*******************************
 // Base class for factories
 ********************************/

struct dsp_factory_base {
    
    virtual ~dsp_factory_base() {}
    
    virtual std::string getName()                        = 0;
    virtual void        setName(const std::string& name) = 0;
    
    virtual std::string getSHAKey()                           = 0;
    virtual void        setSHAKey(const std::string& sha_key) = 0;
    
    virtual std::string getDSPCode()                        = 0;
    virtual void        setDSPCode(const std::string& code) = 0;
    
    virtual std::string getCompileOptions() = 0;
    
    virtual dsp* createDSPInstance(dsp_factory* factory) = 0;
    
    virtual void                setMemoryManager(dsp_memory_manager* manager) = 0;
    virtual dsp_memory_manager* getMemoryManager()                            = 0;
    
    virtual void* allocate(size_t size) = 0;
    virtual void  destroy(void* ptr)    = 0;
    
    virtual void metadata(Meta* meta) = 0;
    
    virtual void write(std::ostream* out, bool binary = false, bool compact = false) = 0;
    
    virtual void writeHelper(std::ostream* out, bool binary = false, bool compact = false) {}  // Helper functions
    
    virtual std::string getBinaryCode() = 0;
    
};

// Create global compilation context
void createLibContext();

// Destroy global compilation context
void destroyLibContext();

/**
 * Create a Faust DSP factory from a vector of output signals.
 *
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param name - the DSP name
 * @param signals - the vector of output signals
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */
dsp_factory_base* compileDSPSignalFactory(int argc, const char* argv[],
                                        const std::string& name,
                                        tvec signals,
                                        std::string& error_msg);

#endif
