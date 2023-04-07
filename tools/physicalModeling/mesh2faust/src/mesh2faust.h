#pragma once

#include <string>
#include <vector>

namespace m2f {

// Defaults to aluminum.
struct MaterialProperties {
    double youngModulus{70E9};
    double poissonRatio{0.35};
    double density{2700};
};

// Returns the generated Faust code as a string.
std::string mesh2faust(
    const char *modelFileName = "",        // .obj file name
    std::string objectName = "modalModel", // generated object name
    MaterialProperties materialProperties = {}, // default to aluminum
    bool freqControl = false,    // freq control activated
    float modesMinFreq = 20,     // lowest mode freq
    float modesMaxFreq = 10000,  // highest mode freq
    int targetNModes = 20,       // number of synthesized modes
    int femNModes = 100,         // number of modes to be computed for the finite element analysis
    std::vector<int> exPos = {}, // specific excitation positions
    int nExPos = -1,             // number of excitation positions (default is max)
    bool showFreqs = false,      // hide or show frequencies in the selected range
    bool debugMode = false       // debug mode activated
);

} // namespace mesh2faust
