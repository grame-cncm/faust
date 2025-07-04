//
// Created by Cucu on 04/07/2025.
//

#include "interpreter-clap.h"
#include <iostream>


InterpreterCLAPPlugin::InterpreterCLAPPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
: clap::helpers::Plugin(desc, host), fFactory(nullptr), fDSP(nullptr) {}

InterpreterCLAPPlugin::~InterpreterCLAPPlugin() {
    if (fDSP) delete fDSP;
    if (fFactory) deleteInterpreterDSPFactory(fFactory);
}


bool InterpreterCLAPPlugin::init() noexcept {
    std::string error_msg;
    const char* dsp_code = "process = no.noise;"; //minimal Faust DSP code
    fFactory = createInterpreterDSPFactoryFromString("interpreter_plugin", dsp_code, 0, nullptr, error_msg);
    if (!fFactory) {
        std::cerr << "failed to create interpreter DSP factory: " << error_msg << "\n";
        return false;
    }
    fDSP = fFactory->createDSPInstance();
    if (!fDSP) {
        std::cerr << "failed to create interpreter DSP instance\n";
        return false;
    }
    fDSP->init(44100); //init with default sample rate
    return true;
}