#pragma once

#include <string>
#include <vector>

#include <Eigen/SparseCore>

class TetMesh;

namespace m2f {

// Defaults to steel.
struct MaterialProperties {
    double youngModulus{2E11};
    double poissonRatio{0.29};
    double density{7850};
    double alpha{5}, beta{3E-8}; // Rayleigh damping coefficients
};

struct CommonArguments {
    std::string modelName = "modalModel"; // Name for the model function
    bool freqControl = false;    // Freq control activated
    float modesMinFreq = 20;     // Lowest mode freq
    float modesMaxFreq = 10000;  // Highest mode freq
    int targetNModes = 20;       // Number of synthesized modes
    int femNModes = 100;         // Number of modes to be computed with Finite Element Analysis (FEA)
    std::vector<int> exPos = {}; // Specific excitation positions
    int nExPos = -1;             // Number of excitation positions (default is max)
    bool debugMode = false;      // Verbose printing
};

struct ModalModel {
    std::vector<float> modeFreqs; // Mode frequencies
    std::vector<float> modeT60s; // Mode T60 decay times
    std::vector<std::vector<float>> modeGains; // Mode gains by [exitation position][mode]
};

// The response type of all mesh2faust functions.
struct Response {
    std::string modelDsp; // Faust DSP code defining the model function, with the provided `modelName`
    ModalModel model; // Model data
};

// The main library function.
// The `mesh2faust` command line tool wraps this function.
Response mesh2faust(const char *objFileName = "", MaterialProperties material = {}, CommonArguments args = {});

// This version takes a pre-loaded tetraheral mesh.
// Material properties are assumed to already be baked into the mesh, but we still need the Rayleigh damping coefficients.
Response mesh2faust(TetMesh *volumetricMesh, MaterialProperties material = {}, CommonArguments args = {});

ModalModel mesh2modal(
    const Eigen::SparseMatrix<double> &M, // Mass matrix
    const Eigen::SparseMatrix<double> &K, // Stiffness matrix
    int numVertices,
    int vertexDim = 3,
    MaterialProperties material = {},
    CommonArguments args = {}
);

// Subset of `CommonArguments` required for the DSP code generation phase
struct DspGenArguments {
    std::string modelName = "modalModel"; // Name for the generated model
    bool freqControl = false; // Freq control activated
};

// Generate DSP code from a `ModalModel`.
Response modal2faust(const ModalModel &, DspGenArguments args = {});

} // namespace mesh2faust
