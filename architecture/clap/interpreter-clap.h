//
// Created by Cucu on 04/07/2025.
//

#ifndef INTERPRETER_CLAP_H
#define INTERPRETER_CLAP_H

#include <faust/dsp/interpreter-dsp.h>
#include "interpreter-clap.h" // include wrapper
#include <faust/gui/APIUI.h> //backedn parameter list
#include <memory>
#include <string>
#include <vector>

// a wrapper class around libfaust's interpreter backend for CLAP
class InterpreterCLAP {
public:
    InterpreterCLAP();
    ~InterpreterCLAP();

    // load and compile a .dsp file at runtime
    bool loadFromFile(const std::string& filepath, int sampleRate);

    // audio processing
    void compute(int nframes, float** inputs, float** outputs);

    // parameter handling
    int getParamCount() const;
    float getParamValue(int index) const;
    void setParamValue(int index, float value);
    const std::string getParamLabel(int index) const;

    // i/o info
    int getNumInputs() const;
    int getNumOutputs() const;

    // parameter metadata
    float getParamMin(int idx) const;
    float getParamMax(int idx) const;
    float getParamInit(int idx) const;

private:
    interpreter_dsp_factory* fFactory = nullptr;
    std::unique_ptr<dsp> fDSP;
    std::unique_ptr<APIUI> fUI;

    int fSampleRate = 44100;
};

class InterpreterCLAPPlugin : public clap::helpers::Plugin {
    // ...
private:
    InterpreterCLAP fInterpreter;
};

#endif // INTERPRETER_CLAP_H