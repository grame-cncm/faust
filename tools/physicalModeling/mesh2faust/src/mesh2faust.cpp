#include "mesh2faust.h"

// Vega
#include "StVKElementABCDLoader.h"
#include "StVKStiffnessMatrix.h"
#include "generateMassMatrix.h"
#include "tetMesher.h"

// Spectra
#include <Spectra/SymGEigsShiftSolver.h>
#include <Spectra/MatOp/SymShiftInvert.h>
#include <Spectra/MatOp/SparseSymMatProd.h>

#include <sstream>

using namespace std;

string m2f::mesh2faust(TetMesh *volumetricMesh, CommonArguments args) {
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

string m2f::mesh2faust(
    const Eigen::SparseMatrix<double> &M,
    const Eigen::SparseMatrix<double> &K,
    int numVertices,
    int vertexDim,
    CommonArguments args
) {
    int femNModes = std::min(args.femNModes, numVertices * vertexDim - 1);
    int targetNModes = std::min(args.targetNModes, femNModes);

    if (args.debugMode) {
        cout << "\nStarting the eigen solver\n";
        cout << femNModes << " modes will be computed for the FEM analysis\n\n";
    }

    using OpType = Spectra::SymShiftInvert<double, Eigen::Sparse, Eigen::Sparse>;
    using BOpType = Spectra::SparseSymMatProd<double>;

    OpType op(K, M);
    BOpType Bop(M);
    int convergenceRatio = min(max(2*femNModes+1, 20), numVertices * vertexDim);
    double sigma = -1.0;
    Spectra::SymGEigsShiftSolver<OpType, BOpType, Spectra::GEigsMode::ShiftInvert>
        eigs(op, Bop, femNModes, convergenceRatio, sigma);
    eigs.init();
    eigs.compute(Spectra::SortRule::LargestMagn);

    string dsp = ""; // Faust DSP code to return. Populated below if successful.

    if (eigs.info() == Spectra::CompInfo::Successful) {
        Eigen::VectorXd eigenValues = eigs.eigenvalues();
        Eigen::MatrixXd eigenVectors = eigs.eigenvectors();

        /////////////////////////////////////
        // COMPUTE MODE FREQS
        /////////////////////////////////////
 
        if (args.debugMode) cout << "Computing modes frequencies\n\n";

        float modesFreqs[femNModes];
        int lowestModeIndex = 0;
        int highestModeIndex = 0;
        for (int i = 0; i < femNModes; i++) {
            double eigenValue = eigenValues[femNModes - 1 - i]; // Eigenvalues are ordered largest-first.
            modesFreqs[i] = eigenValue <= 0 ? 0.0 : sqrt((float)eigenValue) / (2 * M_PI);
            if (modesFreqs[i] < args.modesMinFreq) {
                lowestModeIndex++;
            }
            if (modesFreqs[i] < args.modesMaxFreq &&
                (highestModeIndex - lowestModeIndex) < targetNModes &&
                highestModeIndex < numVertices) {
                highestModeIndex++;
            }
        }
 
        // Adjust number of target modes to modes range.
        int modesRange = highestModeIndex - lowestModeIndex;
        if (modesRange < targetNModes) targetNModes = modesRange;
 
        // Diplay mode frequencies.
        if (args.showFreqs) {
            cout << "Mode frequencies between " << args.modesMinFreq << "Hz and " << args.modesMaxFreq << "Hz:\n";
            for (int i = 0; i < targetNModes; i++) {
                cout << modesFreqs[i + lowestModeIndex] << "\n";
            }
            cout << "\n";
        }
 
        /////////////////////////////////////
        // COMPUTE GAINS
        /////////////////////////////////////
 
        if (args.debugMode) {
            cout << "Computing modes gains for modes between " << args.modesMinFreq
                << "Hz and " << args.modesMaxFreq << "Hz\n\n";
        }
        if (args.exPos.size() > 0) {
            // If exPos list specified, retrieve number of ex positions.
            args.nExPos = args.exPos.size();
        } else if (args.nExPos == -1) {
            // If nExPos and exPos not specified, use max number of excitation positions.
            args.nExPos = numVertices;
        }
        args.nExPos = std::min(args.nExPos, numVertices); // Limit nExPos to number of vertices.

        int exPosStep = numVertices / args.nExPos; // Number of vertices to skip between each exPos.

        /////////////////////////////////////
        // GENERATE FAUST DSP
        /////////////////////////////////////

        // TODO: say something about the model that will be generated (parameters available, etc.)

        stringstream dspStream;
        dspStream << "import(\"stdfaust.lib\");\n\n";
        if (args.freqControl) {
            dspStream << args.modelName
                << "(freq,exPos,t60,t60DecayRatio,t60DecaySlope) = _ <: "
                "par(i,nModes,pm.modeFilter(modesFreqs(i),modesT60s(i),"
                "modesGains(int(exPos),i))) :> /(nModes)\n";
        } else {
            dspStream << args.modelName
                << "(exPos,t60,t60DecayRatio,t60DecaySlope) = _ <: "
                "par(i,nModes,pm.modeFilter(modesFreqs(i),modesT60s(i),"
                "modesGains(int(exPos),i))) :> /(nModes)\n";
        }
        dspStream << "with{\n";
        dspStream << "nModes = " << targetNModes << ";\n";
        if (args.nExPos > 1) dspStream << "nExPos = " << args.nExPos << ";\n";

        if (args.freqControl) {
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
        float unnormalizedGains[targetNModes]; // Used to store gains for each exitation position.
        for (int i = 0; i < args.nExPos; i++) { // i = excitation position
            float maxGain = 0; // for normalization
            for (int j = 0; j < targetNModes; j++) { // j = current mode
                // If exPos was defined, then retrieve data. Otherwise, choose linear ex pos.
                int evIndex = j + lowestModeIndex;
                evIndex = femNModes - 1 - evIndex; // Eigenvectors are ordered largest-first.
                int evValueIndex = vertexDim * (i < args.exPos.size() ? args.exPos[i] : (i * exPosStep));
                float unnormalizedGain = 0;
                for (int k = 0; k < vertexDim; k++) {
                    // Eigen is column-major by default.
                    unnormalizedGain += pow(eigenVectors(evValueIndex + k, evIndex), 2);
                }
                unnormalizedGains[j] = sqrt(unnormalizedGain);
                if (unnormalizedGains[j] > maxGain) maxGain = unnormalizedGains[j];
            }
            for (int j = 0; j < targetNModes; j++) {
                dspStream << unnormalizedGains[j] / maxGain;
                if (j < (targetNModes - 1)) dspStream << ",";
            }
            if (i < (args.nExPos - 1)) dspStream << ",";
        }
        if (args.freqControl) {
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

    return dsp;
}

string m2f::mesh2faust(const char *objectFileName, MaterialProperties materialProperties, CommonArguments args)
{
    /////////////////////////////////////
    // RETRIEVE MODEL
    /////////////////////////////////////

    // Load mesh file.
    if (args.debugMode) cout << "Loading the mesh file\n";
    ObjMesh *objMesh = new ObjMesh(objectFileName);
 
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

    string dsp = mesh2faust(volumetricMesh, args);

    delete volumetricMesh;
    volumetricMesh = nullptr;
    delete objMesh;
    objMesh = nullptr;

    return dsp;
}
