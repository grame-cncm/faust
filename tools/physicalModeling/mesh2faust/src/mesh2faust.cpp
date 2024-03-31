#include "mesh2faust.h"

// Vega
#include "StVKElementABCDLoader.h"
#include "StVKStiffnessMatrix.h"
#include "generateMassMatrix.h"
#include "tetMesher.h"

// Spectra
#include <Spectra/MatOp/SparseSymMatProd.h>
#include <Spectra/MatOp/SymShiftInvert.h>
#include <Spectra/SymGEigsShiftSolver.h>

#include <sstream>

using namespace std;

m2f::Response m2f::mesh2faust(TetMesh *volumetricMesh, CommonArguments args) {
    // Compute mass matrix.
    if (args.debugMode) cout << "Creating and computing mass matrix\n";
    SparseMatrix *massMatrix;
    GenerateMassMatrix::computeMassMatrix(volumetricMesh, &massMatrix, true);

    // computing stiffness matrix
    if (args.debugMode) cout << "Creating and computing stiffness matrix\n";
    StVKElementABCD *precomputedIntegrals = StVKElementABCDLoader::load(volumetricMesh);
    StVKInternalForces *internalForces = new StVKInternalForces(volumetricMesh, precomputedIntegrals);
    SparseMatrix *stiffnessMatrix;
    StVKStiffnessMatrix *stiffnessMatrixClass = new StVKStiffnessMatrix(internalForces);
    stiffnessMatrixClass->GetStiffnessMatrixTopology(&stiffnessMatrix);

    uint vertexDim = 3;
    int numVertices = volumetricMesh->getNumVertices();
    double *zero = (double *)calloc(numVertices * vertexDim, sizeof(double));
    stiffnessMatrixClass->ComputeStiffnessMatrix(zero, stiffnessMatrix);

    free(zero);
    delete stiffnessMatrixClass;
    stiffnessMatrixClass = nullptr;
    delete internalForces;
    internalForces = nullptr;
    delete precomputedIntegrals;
    precomputedIntegrals = nullptr;

    // Copy Vega sparse matrices to Eigen matrices.
    // _Note: Eigen is column-major by default._
    vector<Eigen::Triplet<double>> K_triplets, M_triplets;
    for (int i = 0; i < stiffnessMatrix->GetNumRows(); ++i) {
        for (int j = 0; j < stiffnessMatrix->GetRowLength(i); ++j) {
            K_triplets.push_back({i, stiffnessMatrix->GetColumnIndex(i, j), stiffnessMatrix->GetEntry(i, j)});
        }
    }
    for (int i = 0; i < massMatrix->GetNumRows(); ++i) {
        for (int j = 0; j < massMatrix->GetRowLength(i); ++j) {
            M_triplets.push_back({i, massMatrix->GetColumnIndex(i, j), massMatrix->GetEntry(i, j)});
        }
    }

    int n = stiffnessMatrix->Getn();
    Eigen::SparseMatrix<double> K(n, n), M(n, n);
    K.setFromTriplets(K_triplets.begin(), K_triplets.end());
    M.setFromTriplets(M_triplets.begin(), M_triplets.end());

    delete massMatrix;
    massMatrix = nullptr;
    delete stiffnessMatrix;
    stiffnessMatrix = nullptr;

    return mesh2faust(M, K, numVertices, vertexDim, args);
}

m2f::Response m2f::mesh2faust(
    const Eigen::SparseMatrix<double> &M,
    const Eigen::SparseMatrix<double> &K,
    int numVertices,
    int vertexDim,
    CommonArguments args
) {
    int femNModes = std::min(args.femNModes, numVertices * vertexDim - 1);
    if (args.debugMode) {
        cout << "\nStarting the eigen solver\n";
        cout << femNModes << " modes will be computed for the FEM analysis\n\n";
    }

    using OpType = Spectra::SymShiftInvert<double, Eigen::Sparse, Eigen::Sparse>;
    using BOpType = Spectra::SparseSymMatProd<double>;

    OpType op(K, M);
    BOpType Bop(M);
    int convergenceRatio = min(max(2 * femNModes + 1, 20), numVertices * vertexDim);
    double sigma = -1.0;
    Spectra::SymGEigsShiftSolver<OpType, BOpType, Spectra::GEigsMode::ShiftInvert> eigs(op, Bop, femNModes, convergenceRatio, sigma);
    eigs.init();
    eigs.compute(Spectra::SortRule::LargestMagn, 1000, 1e-10, Spectra::SortRule::SmallestAlge);
    if (eigs.info() != Spectra::CompInfo::Successful) {
        if (args.debugMode) cout << "Could not compute eigenvalues.\n";
        return {};
    }

    Eigen::VectorXd eigenValues = eigs.eigenvalues();
    Eigen::MatrixXd eigenVectors = eigs.eigenvectors();

    /** Compute modes frequencies **/
    if (args.debugMode) cout << "Computing modes frequencies\n\n";

    std::vector<float> modeFreqs(femNModes); // Start with all modes and filter later.
    int lowestModeIndex = 0, highestModeIndex = 0;
    int targetNModes = std::min(args.targetNModes, femNModes);
    for (int mode = 0; mode < eigenValues.size(); ++mode) {
        modeFreqs[mode] = eigenValues[mode] <= 0 ? 0.0 : sqrt(float(eigenValues[mode])) / (2 * M_PI);
        if (modeFreqs[mode] < args.modesMinFreq) ++lowestModeIndex;
        if (modeFreqs[mode] < args.modesMaxFreq) ++highestModeIndex;
    }

    // Adjust modes to include only the requested range.
    modeFreqs.erase(modeFreqs.begin(), modeFreqs.begin() + lowestModeIndex);
    int nModes = std::min(targetNModes, highestModeIndex - lowestModeIndex);
    modeFreqs.resize(nModes);

    if (args.showFreqs) {
        cout << "Mode frequencies:\n";
        for (float modeFreq : modeFreqs) cout << modeFreq << "\n";
        cout << "\n";
    }

    /** Compute modes gains **/
    if (args.debugMode) cout << "Computing modes gains\n\n";

    if (!args.exPos.empty()) args.nExPos = args.exPos.size();
    else if (args.nExPos == -1) args.nExPos = numVertices;
    args.nExPos = std::min(args.nExPos, numVertices);

    std::vector<std::vector<float>> gains(args.nExPos); // Mode gains by [exitation position][mode]
    for (int exPos = 0; exPos < args.nExPos; ++exPos) { // For each excitation position
        gains[exPos] = std::vector<float>(nModes);
        float maxGain = 0;
        for (int mode = 0; mode < nModes; ++mode) {
            // If exPos was provided, retrieve data. Otherwise, distribute excitation positions linearly.
            float gain = 0;
            int evValueIndex = vertexDim * (exPos < args.exPos.size() ? args.exPos[exPos] : exPos * numVertices / args.nExPos);
            int evIndex = mode + lowestModeIndex;
            for (int vi = 0; vi < vertexDim; ++vi) gain += pow(eigenVectors(evValueIndex + vi, evIndex), 2);

            gains[exPos][mode] = sqrt(gain);
            if (gains[exPos][mode] > maxGain) maxGain = gains[exPos][mode];
        }
        for (float &gain : gains[exPos]) gain /= maxGain;
    }

    /////////////////////////////////////
    // GENERATE FAUST DSP
    /////////////////////////////////////

    stringstream dspStream;
    dspStream << "import(\"stdfaust.lib\");\n\n"
              << args.modelName << "(" << (args.freqControl ? "freq," : "")
              << "exPos,t60,t60DecayRatio,t60DecaySlope) = _ <: "
                 "par(mode,nModes,pm.modeFilter(modeFreqs(mode),modesT60s(mode),"
                 "modesGains(int(exPos),mode))) :> /(nModes)\n"
              << "with{\n"
              << "nModes = " << nModes << ";\n";
    if (args.nExPos > 1) dspStream << "nExPos = " << args.nExPos << ";\n";

    if (args.freqControl) {
        dspStream << "modeFreqRatios(n) = ba.take(n+1,(";
        for (int mode = 0; mode < nModes; ++mode) {
            dspStream << modeFreqs[mode] / modeFreqs.front();
            if (mode < nModes - 1) dspStream << ",";
        }
        dspStream << "));\n"
                  << "modeFreqs(mode) = freq*modeFreqRatios(mode);\n";
    } else {
        dspStream << "modeFreqs(n) = ba.take(n+1,(";
        for (int mode = 0; mode < nModes; ++mode) {
            dspStream << modeFreqs[mode];
            if (mode < nModes - 1) dspStream << ",";
        }
        dspStream << "));\n";
    }

    dspStream << "modesGains(p,n) = waveform{";
    for (int exPos = 0; exPos < gains.size(); ++exPos) {
        for (int mode = 0; mode < gains[exPos].size(); ++mode) {
            dspStream << gains[exPos][mode];
            if (mode < nModes - 1) dspStream << ",";
        }
        if (exPos < gains.size() - 1) dspStream << ",";
    }

    dspStream << "},int(p*nModes+n) : rdtable"
              << (args.freqControl ? " : select2(modeFreqs(n)<(ma.SR/2-1),0)" : "") << ";\n"
              << "modesT60s(mode) = t60*pow(1-("
              << (args.freqControl ? "modeFreqRatios(mode)" : "modeFreqs(mode)") << "/"
              << (args.freqControl ? (modeFreqs.back() / modeFreqs.front()) : modeFreqs.back())
              << ")*t60DecayRatio,t60DecaySlope);\n};\n";

    return {dspStream.str(), std::move(modeFreqs), std::move(gains)};
}

m2f::Response m2f::mesh2faust(const char *objectFileName, MaterialProperties materialProperties, CommonArguments args) {
    /////////////////////////////////////
    // RETRIEVE MODEL
    /////////////////////////////////////

    // Load mesh file.
    if (args.debugMode) cout << "Loading the mesh file\n";
    auto *objMesh = new ObjMesh(objectFileName);

    // Generate 3D volumetric mesh from obj mesh.
    if (args.debugMode) {
        cout << "\nGenerating a 3D mesh with the following properties\n";
        cout << "Young's modulus: " << materialProperties.youngModulus << "\n";
        cout << "Poisson's ratio: " << materialProperties.poissonRatio << "\n";
        cout << "Density: " << materialProperties.density << "\n";
    }

    // TODO: no way to prevent printing here (yet)
    TetMesh *volumetricMesh = TetMesher().compute(objMesh);
    // Set mesh material properties.
    volumetricMesh->setSingleMaterial(materialProperties.youngModulus, materialProperties.poissonRatio, materialProperties.density);

    auto response = mesh2faust(volumetricMesh, args);

    delete volumetricMesh;
    volumetricMesh = nullptr;
    delete objMesh;
    objMesh = nullptr;

    return response;
}
