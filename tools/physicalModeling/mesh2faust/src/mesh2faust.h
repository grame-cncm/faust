#pragma once

#include <string>
#include <vector>

#include "tetMesh.h"
#include <Eigen/SparseCore>

namespace m2f {

// Defaults to aluminum.
struct MaterialProperties {
    double youngModulus{70E9};
    double poissonRatio{0.35};
    double density{2700};
};

struct CommonArguments {
    std::string modelName = "modalModel"; // name for the generated model
    bool freqControl = false;    // Freq control activated
    float modesMinFreq = 20;     // Lowest mode freq
    float modesMaxFreq = 10000;  // Highest mode freq
    int targetNModes = 20;       // Number of synthesized modes
    int femNModes = 100;         // Number of modes to be computed with Finite Element Analysis (FEA)
    std::vector<int> exPos = {}; // Specific excitation positions
    int nExPos = -1;             // Number of excitation positions (default is max)
    bool showFreqs = false;      // Display computed frequencies
    bool debugMode = false;      // Verbose printing
};

// The response type of all mesh2faust functions.
// todo introduce an intermediate function to return just mode freqs and gains in its own struct
// (and anything else needed) then a function to turn this into dsp code.
struct Response {
    std::string modelDsp; // Faust DSP code defining the model function, with the provided `modelName`
    std::vector<float> modeFreqs; // Mode frequencies
    std::vector<std::vector<float>> modeGains; // Mode gains by [exitation position][mode]
};

// The main library function.
// The `mesh2faust` command line tool wraps this function.
Response mesh2faust(
    const char *objectFileName = "", // .obj file name
    MaterialProperties materialProperties = {}, // Material properties of the mesh, for FEA
    CommonArguments args = {}
);

// This version takes a pre-loaded tetraheral mesh.
// Material properties are assumed to already be baked into the mesh.
Response mesh2faust(TetMesh *volumetricMesh, CommonArguments args = {});

Response mesh2faust(
    const Eigen::SparseMatrix<double> &M, // Mass matrix
    const Eigen::SparseMatrix<double> &K, // Stiffness matrix
    int numVertices,
    int vertexDim = 3,
    CommonArguments arg = {}
);

} // namespace mesh2faust
