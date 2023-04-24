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
    bool freqControl = false;    // freq control activated
    float modesMinFreq = 20;     // lowest mode freq
    float modesMaxFreq = 10000;  // highest mode freq
    int targetNModes = 20;       // number of synthesized modes
    int femNModes = 100;         // number of modes to be computed for the finite element analysis
    std::vector<int> exPos = {}; // specific excitation positions
    int nExPos = -1;             // number of excitation positions (default is max)
    bool showFreqs = false;      // display computed frequencies
    bool debugMode = false;      // for verbose printing
};

// The main library function.
// The `mesh2faust` command line tool wraps this function.
// Returns the generated Faust code as a string.
std::string mesh2faust(
    const char *objectFileName = "", // .obj file name
    MaterialProperties materialProperties = {}, // material properties to set on the generated volumetric mesh
    CommonArguments args = {}
);

// This version takes a pre-loaded tetraheral mesh.
// Material properties are assumed to already be baked into the mesh.
std::string mesh2faust(TetMesh *volumetricMesh, CommonArguments args = {});

std::string mesh2faust(
    const Eigen::SparseMatrix<double> &M, // Mass matrix
    const Eigen::SparseMatrix<double> &K, // Stiffness matrix
    int numVertices,
    int vertexDim = 3,
    CommonArguments arg = {}
);

} // namespace mesh2faust
