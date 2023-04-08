#include "mesh2faust.h"

#include "StVKElementABCDLoader.h"
#include "StVKStiffnessMatrix.h"
#include "generateMassMatrix.h"
#include "tetMesher.h"
#include <sstream>
#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <Spectra/SymGEigsShiftSolver.h>
#include <Spectra/MatOp/SymShiftInvert.h>
#include <Spectra/MatOp/SparseSymMatProd.h>

using namespace std;

string m2f::mesh2faust(
    TetMesh *volumetricMesh,
    string objectName,
    bool freqControl,
    float modesMinFreq,
    float modesMaxFreq,
    int targetNModes,
    int femNModes,
    vector<int> exPos,
    int nExPos,
    bool showFreqs,
    bool debugMode
) {
    // Compute mass matrix.
    if (debugMode) cout << "Creating and computing mass matrix\n";
    SparseMatrix *massMatrix;
    GenerateMassMatrix::computeMassMatrix(volumetricMesh, &massMatrix, true);

    // computing stiffness matrix
    if (debugMode) cout << "Creating and computing stiffness matrix\n";
    StVKElementABCD *precomputedIntegrals = StVKElementABCDLoader::load(volumetricMesh);
    StVKInternalForces *internalForces = new StVKInternalForces(volumetricMesh, precomputedIntegrals);
    SparseMatrix *stiffnessMatrix;
    StVKStiffnessMatrix *stiffnessMatrixClass = new StVKStiffnessMatrix(internalForces);
    stiffnessMatrixClass->GetStiffnessMatrixTopology(&stiffnessMatrix);
    double *zero = (double *)calloc(3 * volumetricMesh->getNumVertices(), sizeof(double));
    stiffnessMatrixClass->ComputeStiffnessMatrix(zero, stiffnessMatrix);

    // Copy Vega sparse matrices to Eigen matrices.
    vector<Eigen::Triplet<double>> K_triplets, M_triplets;
    for (int i = 0; i < stiffnessMatrix->GetNumRows(); i++) {
        for (int j = 0; j < stiffnessMatrix->GetRowLength(i); j++) {
            K_triplets.push_back({i, stiffnessMatrix->GetColumnIndex(i, j), stiffnessMatrix->GetEntry(i, j)});
        }
    }
    for (int i = 0; i < massMatrix->GetNumRows(); i++) {
        for (int j = 0; j < massMatrix->GetRowLength(i); j++) {
            M_triplets.push_back({i, massMatrix->GetColumnIndex(i, j), massMatrix->GetEntry(i, j)});
        }
    }

    /////////////////////////////////////
    // EIGEN ANALYSIS
    /////////////////////////////////////

    if (debugMode) {
        cout << "\nStarting the eigen solver\n";
        cout << femNModes << " modes will be computed for the FEM analysis\n\n";
    }

    int n = stiffnessMatrix->Getn();
    double sigma = -1.0;

    Eigen::SparseMatrix<double> K(n, n), M(n, n);
    K.setFromTriplets(K_triplets.begin(), K_triplets.end());
    M.setFromTriplets(M_triplets.begin(), M_triplets.end());

    using OpType = Spectra::SymShiftInvert<double, Eigen::Sparse, Eigen::Sparse>;
    using BOpType = Spectra::SparseSymMatProd<double>;
    OpType op(K, M);
    BOpType Bop(M);
    int convergence_ratio = max(2*femNModes+1, 20);
    Spectra::SymGEigsShiftSolver<OpType, BOpType, Spectra::GEigsMode::ShiftInvert>
        eigs(op, Bop, femNModes, convergence_ratio, sigma);
    eigs.init();
    eigs.compute(Spectra::SortRule::LargestMagn);

    string dsp = ""; // Faust DSP code to return. Populated below.

    if (eigs.info() == Spectra::CompInfo::Successful) { // if analysis was successful...
        Eigen::VectorXd eigenValues = eigs.eigenvalues();
        Eigen::MatrixXd eigenVectors = eigs.eigenvectors();

        /////////////////////////////////////
        // COMPUTE MODE FREQS
        /////////////////////////////////////
 
        if (debugMode) cout << "Computing modes frequencies\n\n";
        float modesFreqs[femNModes]; // modes freqs
        int lowestModeIndex = 0;
        int highestModeIndex = 0;
        for (int i = 0; i < femNModes; i++) {
            double eigenValue = eigenValues[femNModes - 1 - i]; // Eigenvalues are ordered largest-first.
            modesFreqs[i] = eigenValue <= 0 ? 0.0 : sqrt((float)eigenValue) / (2 * M_PI);
            if (modesFreqs[i] < modesMinFreq) {
                lowestModeIndex++;
            }
            if (modesFreqs[i] < modesMaxFreq &&
                (highestModeIndex - lowestModeIndex) < targetNModes &&
                highestModeIndex < volumetricMesh->getNumVertices()) {
                highestModeIndex++;
            }
        }
 
        // Adjust number of target modes to modes range.
        int modesRange = highestModeIndex - lowestModeIndex;
        if (modesRange < targetNModes) targetNModes = modesRange;
 
        // Diplay mode frequencies.
        if (showFreqs) {
            cout << "Mode frequencies between " << modesMinFreq << "Hz and " << modesMaxFreq << "Hz:\n";
            for (int i = 0; i < targetNModes; i++) {
                cout << modesFreqs[i + lowestModeIndex] << "\n";
            }
            cout << "\n";
        }
 
        /////////////////////////////////////
        // COMPUTE GAINS
        /////////////////////////////////////
 
        if (debugMode) {
            cout << "Computing modes gains for modes between " << modesMinFreq
                << "Hz and " << modesMaxFreq << "Hz\n\n";
        }
        if (exPos.size() > 0) {
            // If exPos specified, then retrieve number of ex positions.if (exPos.size() > 0) {
            nExPos = exPos.size();
        }
        if (nExPos == -1 || nExPos > volumetricMesh->getNumVertices()) {
            // If nExPos not specified, then max number of exPos.
            nExPos = volumetricMesh->getNumVertices();
        }
        int exPosStep = volumetricMesh->getNumVertices() / nExPos; // to skip excitation positions
        float modesGains[nExPos][targetNModes]; // modes gains matrix
        for (int i = 0; i < nExPos; i++) { // i = excitation position
            float maxGain = 0; // for normalization
            for (int j = 0; j < targetNModes; j++) { // j = current mode
                // If exPos was defined, then retrieve data. Otherwise, choose linear ex pos.
                int evIndex = j + lowestModeIndex;
                evIndex = femNModes - 1 - evIndex; // Eigenvectors are ordered largest-first.
                int evValueIndex = 3 * (exPos.size() > 0 ? exPos[i] : (i * exPosStep));
                // Eigen is column-major by default.
                modesGains[i][j] = sqrt(pow(eigenVectors(evValueIndex, evIndex), 2) +
                                        pow(eigenVectors(evValueIndex + 1, evIndex), 2) +
                                        pow(eigenVectors(evValueIndex + 2, evIndex), 2));
                if (modesGains[i][j] > maxGain) maxGain = modesGains[i][j]; // Save max gain for normalization.
            }
            // Normalize gains for current position.
            for (int j = 0; j < targetNModes; j++) {
                modesGains[i][j] /= maxGain;
            }
        }

        /////////////////////////////////////
        // GENERATE FAUST DSP
        /////////////////////////////////////

        // TODO: say something about the model that will be generated (parameters available, etc.)

        stringstream dspStream;
        dspStream << "import(\"stdfaust.lib\");\n\n";
        if (freqControl) {
            dspStream << objectName
                << "(freq,exPos,t60,t60DecayRatio,t60DecaySlope) = _ <: "
                "par(i,nModes,pm.modeFilter(modesFreqs(i),modesT60s(i),"
                "modesGains(int(exPos),i))) :> /(nModes)\n";
        } else {
            dspStream << objectName
                << "(exPos,t60,t60DecayRatio,t60DecaySlope) = _ <: "
                "par(i,nModes,pm.modeFilter(modesFreqs(i),modesT60s(i),"
                "modesGains(int(exPos),i))) :> /(nModes)\n";
        }
        dspStream << "with{\n";
        dspStream << "nModes = " << targetNModes << ";\n";
        if (nExPos > 1) dspStream << "nExPos = " << nExPos << ";\n";

        if (freqControl) {
            dspStream << "modesFreqRatios(n) = ba.take(n+1,(";
            for (int i = 0; i < targetNModes; i++) {
                dspStream << modesFreqs[lowestModeIndex + i] / modesFreqs[lowestModeIndex];
                if (i < (targetNModes - 1)) dspStream << ",";
            }
            dspStream << "));\n";
            dspStream << "modesFreqs(i) = freq*modesFreqRatios(i);\n";
        } else {
            dspStream << "modesFreqs(n) = ba.take(n+1,(";
            for (int i = 0; i < targetNModes; i++) {
                dspStream << modesFreqs[lowestModeIndex + i];
                if (i < (targetNModes - 1)) dspStream << ",";
            }
            dspStream << "));\n";
        }
        dspStream << "modesGains(p,n) = waveform{";
        for (int i = 0; i < nExPos; i++) {
            for (int j = 0; j < targetNModes; j++) {
                dspStream << modesGains[i][j];
                if (j < (targetNModes - 1)) dspStream << ",";
            }
            if (i < (nExPos - 1)) dspStream << ",";
        }
        if (freqControl) {
            dspStream << "},int(p*nModes+n) : rdtable : select2(modesFreqs(n)<(ma.SR/2-1),0);\n"
                << "modesT60s(i) = t60*pow(1-(modesFreqRatios(i)/"
                << modesFreqs[highestModeIndex] / modesFreqs[lowestModeIndex]
                << ")*t60DecayRatio,t60DecaySlope);\n";
        } else {
            dspStream << "},int(p*nModes+n) : rdtable;\n"
                << "modesT60s(i) = t60*pow(1-(modesFreqs(i)/"
                << modesFreqs[highestModeIndex]
                << ")*t60DecayRatio,t60DecaySlope);\n";
        }
        dspStream << "};\n";

        dsp = dspStream.str();
    }

    // cleaning
    free(zero);
    delete stiffnessMatrixClass;
    stiffnessMatrixClass = nullptr;
    delete stiffnessMatrix;
    stiffnessMatrix = nullptr;
    delete internalForces;
    internalForces = nullptr;
    delete precomputedIntegrals;
    precomputedIntegrals = nullptr;
    delete massMatrix;
    massMatrix = nullptr;

    return dsp;
}

string m2f::mesh2faust(
    const char *modelFileName,
    string objectName,
    m2f::MaterialProperties materialProperties,
    bool freqControl,
    float modesMinFreq, float modesMaxFreq,
    int targetNModes, int femNModes,
    vector<int> exPos,
    int nExPos,
    bool showFreqs, bool debugMode
)
{
    /////////////////////////////////////
    // RETRIEVE MODEL
    /////////////////////////////////////

    // Load mesh file.
    if (debugMode) cout << "Loading the mesh file\n";
    ObjMesh *objMesh = new ObjMesh(modelFileName);
 
    // Generate 3D volumetric mesh from 2D mesh.
    if (debugMode) {
        cout << "\nGenerating a 3D mesh with the following properties\n";
        cout << "Young's modulus: " << materialProperties.youngModulus << "\n";
        cout << "Poisson's ratio: " << materialProperties.poissonRatio << "\n";
        cout << "Density: " << materialProperties.density << "\n";
    }
    // TODO: no way to prevent printing here (yet)
    TetMesh *volumetricMesh = TetMesher().compute(objMesh);
    // Set mesh material properties.
    volumetricMesh->setSingleMaterial(materialProperties.youngModulus, materialProperties.poissonRatio, materialProperties.density);

    string dsp = mesh2faust(volumetricMesh, objectName, freqControl, modesMinFreq, modesMaxFreq,
        targetNModes, femNModes, exPos, nExPos, showFreqs, debugMode);

    delete volumetricMesh;
    volumetricMesh = nullptr;
    delete objMesh;
    objMesh = nullptr;

    return dsp;
}
