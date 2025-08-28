//
// Created by Facundo Franchino on 04/07/2025.

// header for interpreter wrapper
#ifndef INTERPRETER_CLAP_H
#define INTERPRETER_CLAP_H

#include <faust/dsp/interpreter-dsp.h>
#include "clap-mapui.h"  // use the shared CLAPMapUI
#include <memory>
#include <string>

class InterpreterCLAP {
public:
    InterpreterCLAP();
    ~InterpreterCLAP();

    bool loadFromFile(const std::string& filepath, int sampleRate);
    bool loadFromString(const std::string& name, const std::string& dspCode, int sampleRate);

    void compute(int nframes, float** inputs, float** outputs);

    int getParamCount() const;
    float getParamValue(int index) const;
    void setParamValue(int index, float value);
    std::string getParamLabel(int index) const;

    int getNumInputs() const;
    int getNumOutputs() const;

    float getParamMin(int idx) const;
    float getParamMax(int idx) const;
    float getParamInit(int idx) const;

    dsp* getDSP() { return fDSP; }
    CLAPMapUI* getUI() { return fUI.get(); }

private:
    interpreter_dsp_factory* fFactory = nullptr;
    dsp* fDSP = nullptr;
    std::unique_ptr<CLAPMapUI> fUI;  // use CLAPMapUI instead of MapUI

    int fSampleRate = 44100;
};

#endif