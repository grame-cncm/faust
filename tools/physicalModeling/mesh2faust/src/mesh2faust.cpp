#include "mesh2faust.h"

// Vega
#include "StVKElementABCDLoader.h"
#include "StVKStiffnessMatrix.h"
#include "generateMassMatrix.h"
#include "tetMesh.h"
#include "tetMesher.h"

// Spectra
#include <Spectra/MatOp/SparseSymMatProd.h>
#include <Spectra/MatOp/SymShiftInvert.h>
#include <Spectra/SymGEigsShiftSolver.h>

#include <sstream>

using namespace std;

m2f::Response m2f::mesh2faust(TetMesh *volumetricMesh, MaterialProperties material, CommonArguments args) {
    if (args.debugMode) cout << "Creating and computing mass matrix\n";

    SparseMatrix *massMatrix;
    GenerateMassMatrix::computeMassMatrix(volumetricMesh, &massMatrix, true);

    if (args.debugMode) cout << "Creating and computing stiffness matrix\n";

    StVKElementABCD *precomputedIntegrals = StVKElementABCDLoader::load(volumetricMesh);
    StVKInternalForces internalForces{volumetricMesh, precomputedIntegrals};
    SparseMatrix *stiffnessMatrix;
    StVKStiffnessMatrix stiffnessMatrixClass{&internalForces};
    stiffnessMatrixClass.GetStiffnessMatrixTopology(&stiffnessMatrix);

    const uint vertexDim = 3;
    const int numVertices = volumetricMesh->getNumVertices();
    double *zero = (double *)calloc(numVertices * vertexDim, sizeof(double));
    stiffnessMatrixClass.ComputeStiffnessMatrix(zero, stiffnessMatrix);

    free(zero);
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

    const int n = stiffnessMatrix->Getn();
    Eigen::SparseMatrix<double> K(n, n), M(n, n);
    K.setFromTriplets(K_triplets.begin(), K_triplets.end());
    M.setFromTriplets(M_triplets.begin(), M_triplets.end());

    delete massMatrix;
    massMatrix = nullptr;
    delete stiffnessMatrix;
    stiffnessMatrix = nullptr;

    auto model = mesh2modal(M, K, numVertices, vertexDim, material, args);
    return modal2faust(std::move(model), {args.modelName, args.freqControl});
}

m2f::ModalModel m2f::mesh2modal(
    const Eigen::SparseMatrix<double> &M,
    const Eigen::SparseMatrix<double> &K,
    int numVertices, int vertexDim,
    MaterialProperties material,
    CommonArguments args
) {
    const int femNModes = std::min(args.femNModes, numVertices * vertexDim - 1);

    /** Compute mass/stiffness eigenvalues and eigenvectors **/
    if (args.debugMode) {
        cout << "\nStarting the eigen solver.\n";
        cout << femNModes << " modes will be computed for FEM analysis.\n\n";
    }

    using OpType = Spectra::SymShiftInvert<double, Eigen::Sparse, Eigen::Sparse>;
    using BOpType = Spectra::SparseSymMatProd<double>;

    const int convergenceRatio = min(max(2 * femNModes + 1, 20), numVertices * vertexDim);
    const double sigma = pow(2 * M_PI * args.modesMinFreq, 2);
    OpType op(K, M);
    BOpType Bop(M);
    Spectra::SymGEigsShiftSolver<OpType, BOpType, Spectra::GEigsMode::ShiftInvert> eigs(op, Bop, femNModes, convergenceRatio, sigma);
    eigs.init();
    eigs.compute(Spectra::SortRule::LargestMagn, 1000, 1e-10, Spectra::SortRule::SmallestAlge);
    if (eigs.info() != Spectra::CompInfo::Successful) {
        if (args.debugMode) cout << "Could not compute eigenvalues.\n";
        return {};
    }

    const auto eigenvalues = eigs.eigenvalues();
    const auto eigenvectors = eigs.eigenvectors();

    /** Compute modes frequencies/gains/T60s **/
    if (args.debugMode) cout << "Computing modes ...\n\n";

    std::vector<float> modeFreqs(femNModes), modeT60s(femNModes);
    int lowestModeIndex = 0, highestModeIndex = 0;
    for (int mode = 0; mode < femNModes; ++mode) {
        if (eigenvalues[mode] > 1) { // Ignore very small eigenvalues
            // See Eqs. 1-12 in https://www.cs.cornell.edu/~djames/papers/DyRT.pdf for a derivation of the following.
            auto &v = eigenvectors.col(mode);
            double omega_i = sqrt(eigenvalues[mode]); // Undamped natural frequency, in rad/s
            // With good eigenvalue estimates, this should be near-equivalent:
            // double Mv = v.transpose() * M * v, Kv = v.transpose() * K * v, omega_i = sqrt(Kv / Mv);
            double xi_i = 0.5 * (material.alpha / omega_i + material.beta * omega_i); // Damping ratio
            double omega_i_hz = omega_i / (2 * M_PI);
            modeFreqs[mode] = omega_i_hz * sqrt(1 - xi_i * xi_i); // Damped natural frequency
            // T60 is the time for the mode's amplitude to decay by 60 dB.
            // 20 * log10(1000) = 60 dB -> After T60 time, the amplitude is 1/1000th of its initial value.
            // A change of basis gets us to the ln(1000) factor.
            // See https://ccrma.stanford.edu/~jos/st/Audio_Decay_Time_T60.html
            static const double LN_1000 = std::log(1000);
            modeT60s[mode] = LN_1000 / (xi_i * omega_i_hz); // Damping is based on the _undamped_ natural frequency.
        } else {
            modeFreqs[mode] = modeT60s[mode] = 0.0;
        }
        if (modeFreqs[mode] < args.modesMinFreq) ++lowestModeIndex;
        if (modeFreqs[mode] < args.modesMaxFreq) ++highestModeIndex;
    }

    // Adjust modes to include only the requested range.
    const int nModes = std::min(std::min(args.targetNModes, femNModes), highestModeIndex - lowestModeIndex);
    modeFreqs.erase(modeFreqs.begin(), modeFreqs.begin() + lowestModeIndex);
    modeFreqs.resize(nModes);
    modeT60s.erase(modeT60s.begin(), modeT60s.begin() + lowestModeIndex);
    modeT60s.resize(nModes);

    if (!args.exPos.empty()) args.nExPos = args.exPos.size();
    else if (args.nExPos == -1) args.nExPos = numVertices;
    args.nExPos = std::min(args.nExPos, numVertices);

    std::vector<std::vector<float>> gains(args.nExPos); // Mode gains by [exitation position][mode]
    for (int exPos = 0; exPos < args.nExPos; ++exPos) { // For each excitation position
        // If exPos was provided, retrieve data. Otherwise, distribute excitation positions linearly.
        int evIndex = vertexDim * (exPos < args.exPos.size() ? args.exPos[exPos] : exPos * numVertices / args.nExPos);
        gains[exPos] = std::vector<float>(nModes);
        float maxGain = 0;
        for (int mode = 0; mode < nModes; ++mode) {
            float gain = 0;
            for (int vi = 0; vi < vertexDim; ++vi) gain += pow(eigenvectors(evIndex + vi, mode + lowestModeIndex), 2);

            gains[exPos][mode] = sqrt(gain);
            if (gains[exPos][mode] > maxGain) maxGain = gains[exPos][mode];
        }
        for (float &gain : gains[exPos]) gain /= maxGain;
    }

    return {std::move(modeFreqs), std::move(modeT60s), std::move(gains)};
}

m2f::Response m2f::mesh2faust(const char *objFileName, MaterialProperties material, CommonArguments args) {
    // Load mesh file.
    if (args.debugMode) cout << "Loading the mesh file...\n";
    ObjMesh objMesh{objFileName};

    // Generate 3D volumetric mesh from obj mesh.
    if (args.debugMode) {
        cout << "\nGenerating a 3D mesh with the following material properties:"
             << "\n\tYoung's modulus: " << material.youngModulus
             << "\n\tPoisson's ratio: " << material.poissonRatio
             << "\n\tDensity: " << material.density
             << "\n\tRayleigh damping alpha: " << material.alpha
             << "\n\tRayleigh damping beta: " << material.beta
             << "\n\n";
    }

    // TODO: no way to prevent printing here (yet)
    TetMesh *volumetricMesh = TetMesher().compute(&objMesh);
    volumetricMesh->setSingleMaterial(material.youngModulus, material.poissonRatio, material.density);

    auto response = mesh2faust(volumetricMesh, material, args);

    delete volumetricMesh;
    volumetricMesh = nullptr;

    return response;
}

m2f::Response m2f::modal2faust(const ModalModel &model, DspGenArguments args) {
    const auto &freqs = model.modeFreqs;
    const auto &gains = model.modeGains;
    const auto &t60s = model.modeT60s;
    const auto nModes = freqs.size();
    const auto nExPos = gains.size();

    stringstream dsp;
    dsp << "import(\"stdfaust.lib\");\n\n"
        << args.modelName << "(" << (args.freqControl ? "freq," : "")
        << "exPos,t60Scale) = _ <: "
           "par(mode,nModes,pm.modeFilter(modeFreqs(mode),modesT60s(mode),"
           "modesGains(int(exPos),mode))) :> /(nModes)\n"
        << "with{\n"
        << "nModes = " << nModes << ";\n";
    if (nExPos > 1) dsp << "nExPos = " << nExPos << ";\n";

    if (args.freqControl) {
        dsp << "modeFreqRatios(n) = ba.take(n+1,(";
        for (int mode = 0; mode < nModes; ++mode) {
            dsp << freqs[mode] / freqs.front();
            if (mode < nModes - 1) dsp << ",";
        }
        dsp << "));\n"
                  << "modeFreqs(mode) = freq*modeFreqRatios(mode);\n";
    } else {
        dsp << "modeFreqs(n) = ba.take(n+1,(";
        for (int mode = 0; mode < nModes; ++mode) {
            dsp << freqs[mode];
            if (mode < nModes - 1) dsp << ",";
        }
        dsp << "));\n";
    }

    dsp << "modesGains(p,n) = waveform{";
    for (int exPos = 0; exPos < gains.size(); ++exPos) {
        for (int mode = 0; mode < gains[exPos].size(); ++mode) {
            dsp << gains[exPos][mode];
            if (mode < nModes - 1) dsp << ",";
        }
        if (exPos < gains.size() - 1) dsp << ",";
    }
    dsp << "},int(p*nModes+n) : rdtable" << (args.freqControl ? " : select2(modeFreqs(n)<(ma.SR/2-1),0)" : "") << ";\n";

    dsp << "modesT60s(n) = t60Scale * ba.take(n+1,(";
    for (int mode = 0; mode < nModes; ++mode) {
        dsp << t60s[mode];
        if (mode < nModes - 1) dsp << ",";
    }
    dsp << "));\n";
    dsp << "};\n";

    return {dsp.str(), std::move(model)};
}
