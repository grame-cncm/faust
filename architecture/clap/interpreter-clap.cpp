//
// Created by Cucu on 04/07/2025.
//

#include "interpreter-clap.h"
#include <iostream>

// starting w no parameters, no midi, no ui, just handles one input and one output mono channels for now

// plugin constructor, it calls the base clap plugin constructor with the descriptor and host
// initialises the pointers fDSP, fFactory to nullptr to start clean
InterpreterCLAPPlugin::InterpreterCLAPPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
: clap::helpers::Plugin(desc, host), fFactory(nullptr), fDSP(nullptr) {}


// the faust API function deleteInterpreterDSPFactory releases the compiled DSP factory and reduces its reference count
// using this in order to prevent memory leakage
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