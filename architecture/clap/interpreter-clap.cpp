//
// Created by Cucu on 04/07/2025.
//

#include "interpreter-clap.h"
#include <faust/dsp/interpreter-dsp.h>
#include <faust/gui/APIUI.h> //backend parameter list
#include <fstream>
#include <sstream>
#include <iostream>

InterpreterCLAP::InterpreterCLAP() : fFactory(nullptr), fDSP(nullptr) {}

InterpreterCLAP::~InterpreterCLAP() {
    if (fFactory) deleteInterpreterDSPFactory(fFactory);
}

bool InterpreterCLAP::loadFromFile(const std::string& path, int sampleRate) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open DSP file: " << path << "\n";
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();

    std::string error_msg;
    fFactory = createInterpreterDSPFactoryFromString(
        path.c_str(), code, 0, nullptr, error_msg
    );

    if (!fFactory) {
        std::cerr << "DSP factory creation failed: " << error_msg << "\n";
        return false;
    }

    fDSP = fFactory->createDSPInstance();
    if (!fDSP) {
        std::cerr << "DSP instance creation failed\n";
        return false;
    }

    fUI = std::make_unique<APIUI>();
    fDSP->buildUserInterface(fUI.get());
    fDSP->init(sampleRate);

    return true;
}

int InterpreterCLAP::getNumInputs() const {
    return fDSP ? fDSP->getNumInputs() : 0;
}

int InterpreterCLAP::getNumOutputs() const {
    return fDSP ? fDSP->getNumOutputs() : 0;
}

int InterpreterCLAP::getParamCount() const {
    return fUI ? fUI->getParamsCount() : 0;
}

void InterpreterCLAP::setParamValue(int idx, float val) {
    if (fUI) fUI->setParamValue(idx, val);
}

std::string InterpreterCLAP::getParamLabel(int idx) const {
    return fUI ? fUI->getParamLabel(idx) : "";
}

float InterpreterCLAP::getParamValue(int idx) const {
    return fUI ? fUI->getParamValue(idx) : 0.f;
}

float InterpreterCLAP::getParamMin(int idx) const {
    return fUI ? fUI->getParamMin(idx) : 0.f;
}

float InterpreterCLAP::getParamMax(int idx) const {
    return fUI ? fUI->getParamMax(idx) : 1.f;
}

float InterpreterCLAP::getParamInit(int idx) const {
    return fUI ? fUI->getParamInit(idx) : 0.f;
}

void InterpreterCLAP::compute(int frames, float** inputs, float** outputs) {
    if (fDSP) fDSP->compute(frames, inputs, outputs);
}