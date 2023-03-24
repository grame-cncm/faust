#include "StVKElementABCDLoader.h"
#include "StVKStiffnessMatrix.h"
#include "generateMassMatrix.h"
#include "tetMesher.h"
#include <fstream>
#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <Spectra/SymGEigsShiftSolver.h>
#include <Spectra/MatOp/SymShiftInvert.h>
#include <Spectra/MatOp/SparseSymMatProd.h>

using namespace std;

void printHelp()
{
    cout << "MESH2FAUST: FAUST PHYSICAL MODEL GENERATOR\n\n";
    cout << "mesh2faust is an open-source modal physical model generator "
        "for the Faust programming language. mesh2faust takes a volumetric mesh of "
        "a 3D object as its main argument, carries out a finite element analysis, "
        "and generates the corresponding Faust modal physical model. A wide range "
        "of parameters can be configured to fine-tune the analysis as well as the "
        "behavior of the generated object.\n";
    cout << "Additional resources: https://github.com/grame-cncm/faust/blob/master-dev/tools/physicalModeling/mesh2faust/README.md\n\n";
    cout << "USAGE:\n\n";
    cout << "mesh2faust --infile 3dObject.obj\n";
    cout << "Where 3dObject.obj is a volumetric mesh file\n\n";
    cout << "OPTIONS:\n\n";
    cout << "--help: prints this help\n";
    cout << "--debug: verboses the output of mesh2faust\n";
    cout << "--showfreqs: prints the list of frequencies of the calculated modes\n";
    cout << "--infile: specifies the path to the volumetric mesh "
        "file. Dimensions of the mesh should be in meters. E.g.: --infile file.obj\n";
    cout << "--freqcontrol: adds frequency control to the generated "
        "model by adding a freq parameter to it\n";
    cout << "--name: specifies the name of the generated model "
        "(no spaces or special characters). E.g.: --name modelName\n";
    cout << "--minmode: specifies the minimum frequency of the "
        "lowest mode. E.g.: --minmode 30\n";
    cout << "--maxmode: specifies the maximum frequency of the "
        "highest mode. E.g.: --maxmode 9000\n";
    cout << "--lmexpos: specifies the maximum number of excitation "
        "positions in the model. E.g.: --lmexpos 10\n";
    cout << "--expos: specifies excitation positions as a list "
        "of vertex IDs. E.g.: --expos 89 63 45\n";
    cout << "--nfemmodes: specifies the number of modes to be computed "
        "for the finite element analysis. E.g.: --nfemmodes 300\n";
    cout << "--nsynthmodes: specifies the max number of modes to be added "
        "to the physical model and synthesized. E.g.: --nsynthmodes 50\n";
}

int main(int argc, char **argv)
{
    const char *modelFileName = "";        // .obj file name
    std::string objectName = "modalModel"; // generated object name
    // Young's modulus, Poisson's ratio and density - default: aluminum
    double materialProperties[3] = {70E9, 0.35, 2700}; 
    std::vector<int> exPos;
    bool debugMode = false;     // debug mode activated
    bool showFreqs = false;     // hide or show frequencies in the selected range
    bool freqControl = false;   // freq control activated
    float modesMinFreq = 20;    // lowest mode freq
    float modesMaxFreq = 10000; // highest mode freq
    int targetNModes = 20;      // number of synthesized modes
    int femNModes = 100;        // number of synthesized modes
    int nExPos = -1;            // number of excitation positions (default is max)
 
    /////////////////////////////////////
    // PARSE ARGUMENTS
    /////////////////////////////////////
    int currentArg = 0;
    if (argc > 1) {
        while (currentArg <= (argc - 1)) {
            if (strcmp(argv[currentArg], "--infile") == 0) {
                currentArg++;
                modelFileName = argv[currentArg];
                if (strcmp(modelFileName, "") == 0) {
                    cout << "No .obj file provided!\n";
                    return 0;
                }
            } else if (strcmp(argv[currentArg], "--material") == 0) {
                currentArg++;
                for (int i = 0; i < 3; i++) {
                    if (currentArg > (argc - 1)) {
                        cout << "Not enough parameter properties!\n";
                        return 0;
                    }
                    if (strtod(argv[currentArg], NULL) != 0) {
                        materialProperties[i] = strtod(argv[currentArg], NULL);
                    } else {
                        cout << "Wrong material parameter: " << argv[currentArg] << "\n";
                        return 0;
                    }
                    if (i < 2)
                    currentArg++;
                }
            } else if (strcmp(argv[currentArg], "--expos") == 0) {
                currentArg++;
                while (strtod(argv[currentArg], NULL) != 0) {
                    exPos.push_back(strtod(argv[currentArg], NULL));
                    currentArg++;
                }
                currentArg--;
            } else if (strcmp(argv[currentArg], "--debug") == 0) {
                debugMode = true;
            } else if (strcmp(argv[currentArg], "--help") == 0) {
                printHelp();
            } else if (strcmp(argv[currentArg], "--showfreqs") == 0) {
                showFreqs = true;
            } else if (strcmp(argv[currentArg], "--freqcontrol") == 0) {
                freqControl = true;
            } else if (strcmp(argv[currentArg], "--name") == 0) {
                currentArg++;
                if (currentArg > (argc - 1)) {
                    cout << "--name: expecting an argument\n";
                    return 0;
                }
                objectName = argv[currentArg];
            } else if (strcmp(argv[currentArg], "--minmode") == 0) {
                currentArg++;
                if (currentArg > (argc - 1)) {
                    cout << "--minmode: expecting an argument\n";
                    return 0;
                }
                if (strtod(argv[currentArg], NULL) != 0) {
                    modesMinFreq = strtof(argv[currentArg], NULL);
                } else {
                    cout << "Min mode is not a float\n";
                    return 0;
                }
            } else if (strcmp(argv[currentArg], "--maxmode") == 0) {
                currentArg++;
                if (currentArg > (argc - 1)) {
                    cout << "--maxmode: expecting an argument\n";
                    return 0;
                }
                if (strtod(argv[currentArg], NULL) != 0) {
                    modesMaxFreq = strtof(argv[currentArg], NULL);
                } else {
                    cout << "Max mode is not a float\n";
                    return 0;
                }
            } else if (strcmp(argv[currentArg], "--lmexpos") == 0) {
                currentArg++;
                if (currentArg > (argc - 1)) {
                    cout << "--lmexpos: expecting an argument\n";
                    return 0;
                }
                if (strtod(argv[currentArg], NULL) != 0) {
                    nExPos = strtod(argv[currentArg], NULL);
                } else {
                    cout << "Excitation position limit is not an int\n";
                    return 0;
                }
            } else if (strcmp(argv[currentArg], "--nsynthmodes") == 0) {
                currentArg++;
                if (currentArg > (argc - 1)) {
                    cout << "--nsynthmodes: expecting an argument\n";
                    return 0;
                }
                if (strtod(argv[currentArg], NULL) != 0) {
                    targetNModes = strtod(argv[currentArg], NULL);
                } else {
                    cout << "Number of synthesized modes is not an int\n";
                    return 0;
                }
            } else if (strcmp(argv[currentArg], "--nfemmodes") == 0) {
                currentArg++;
                if (currentArg > (argc - 1)) {
                    cout << "--nfemmodes: expecting an argument\n";
                    return 0;
                }
                if (strtod(argv[currentArg], NULL) != 0) {
                    femNModes = strtod(argv[currentArg], NULL);
                } else {
                    cout << "Number of FEM modes is not an int\n";
                    return 0;
                }
            }
            currentArg++;
        }
    } else {
        cout << "Missing arguments!\n\n";
        printHelp();
        return 0;
    }
 
    /////////////////////////////////////
    // RETRIEVE MODEL
    /////////////////////////////////////

    // Load mesh file.
    if (debugMode) {
        cout << "Loading the mesh file\n";
    }
    ObjMesh *objMesh = new ObjMesh(modelFileName);
 
    // Generate 3D volumetric mesh from 2D mesh.
    if (debugMode) {
        cout << "\nGenerating a 3D mesh with the following properties\n";
        cout << "Young's modulus: " << materialProperties[0] << "\n";
        cout << "Poisson's ratio: " << materialProperties[1] << "\n";
        cout << "Density: " << materialProperties[2] << "\n";
    }
    // TODO: no way to prevent printing here (yet)
    TetMesh *volumetricMesh = TetMesher().compute(objMesh);
    // Set mesh material properties.
    volumetricMesh->setSingleMaterial(materialProperties[0], materialProperties[1], materialProperties[2]);
 
    // Compute mass matrix.
    if (debugMode) {
        cout << "Creating and computing mass matrix\n";
    }
    SparseMatrix *massMatrix;
    GenerateMassMatrix::computeMassMatrix(volumetricMesh, &massMatrix, true);

    // computing stiffness matrix
    if (debugMode) {
        cout << "Creating and computing stiffness matrix\n";
    }
    StVKElementABCD *precomputedIntegrals = StVKElementABCDLoader::load(volumetricMesh);
    StVKInternalForces *internalForces = new StVKInternalForces(volumetricMesh, precomputedIntegrals);
    SparseMatrix *stiffnessMatrix;
    StVKStiffnessMatrix *stiffnessMatrixClass = new StVKStiffnessMatrix(internalForces);
    stiffnessMatrixClass->GetStiffnessMatrixTopology(&stiffnessMatrix);
    double *zero = (double *)calloc(3 * volumetricMesh->getNumVertices(), sizeof(double));
    stiffnessMatrixClass->ComputeStiffnessMatrix(zero, stiffnessMatrix);

    // Copy Vega sparse matrices to Eigen matrices.
    std::vector<Eigen::Triplet<double>> K_triplets, M_triplets;
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

    if (eigs.info() == Spectra::CompInfo::Successful) { // if analysis was successful...
        Eigen::VectorXd eigenValues = eigs.eigenvalues();
        Eigen::MatrixXd eigenVectors = eigs.eigenvectors();

        /////////////////////////////////////
        // COMPUTE MODE FREQS
        /////////////////////////////////////
 
        if (debugMode) {
            cout << "Computing modes frequencies\n\n";
        }
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
        // GENERATE FAUST FILE
        /////////////////////////////////////
        
        // TODO: say something about the model that will be generated (parameters available, etc.)
 
        std::string faustFileName;
        faustFileName.append(objectName).append(".lib");
        std::ofstream faustFile(faustFileName.c_str());
        faustFile << "import(\"stdfaust.lib\");\n\n";
        if (freqControl) {
            faustFile << objectName
                << "(freq,exPos,t60,t60DecayRatio,t60DecaySlope) = _ <: "
                "par(i,nModes,pm.modeFilter(modesFreqs(i),modesT60s(i),"
                "modesGains(int(exPos),i))) :> /(nModes)\n";
        } else {
            faustFile << objectName
                << "(exPos,t60,t60DecayRatio,t60DecaySlope) = _ <: "
                "par(i,nModes,pm.modeFilter(modesFreqs(i),modesT60s(i),"
                "modesGains(int(exPos),i))) :> /(nModes)\n";
        }
        faustFile << "with{\n";
        faustFile << "nModes = " << targetNModes << ";\n";
        if (nExPos > 1) faustFile << "nExPos = " << nExPos << ";\n";
 
        if (freqControl) {
            faustFile << "modesFreqRatios(n) = ba.take(n+1,(";
            for (int i = 0; i < targetNModes; i++) {
                faustFile << modesFreqs[lowestModeIndex + i] / modesFreqs[lowestModeIndex];
                if (i < (targetNModes - 1)) faustFile << ",";
            }
            faustFile << "));\n";
            faustFile << "modesFreqs(i) = freq*modesFreqRatios(i);\n";
        } else {
            faustFile << "modesFreqs(n) = ba.take(n+1,(";
            for (int i = 0; i < targetNModes; i++) {
                faustFile << modesFreqs[lowestModeIndex + i];
                if (i < (targetNModes - 1)) faustFile << ",";
            }
            faustFile << "));\n";
        }
        faustFile << "modesGains(p,n) = waveform{";
        for (int i = 0; i < nExPos; i++) {
            for (int j = 0; j < targetNModes; j++) {
                faustFile << modesGains[i][j];
                if (j < (targetNModes - 1)) faustFile << ",";
            }
            if (i < (nExPos - 1)) faustFile << ",";
        }
        if (freqControl) {
            faustFile << "},int(p*nModes+n) : rdtable : select2(modesFreqs(n)<(ma.SR/2-1),0);\n"
                << "modesT60s(i) = t60*pow(1-(modesFreqRatios(i)/"
                << modesFreqs[highestModeIndex] / modesFreqs[lowestModeIndex]
                << ")*t60DecayRatio,t60DecaySlope);\n";
        } else {
            faustFile << "},int(p*nModes+n) : rdtable;\n"
                << "modesT60s(i) = t60*pow(1-(modesFreqs(i)/"
                << modesFreqs[highestModeIndex]
                << ")*t60DecayRatio,t60DecaySlope);\n";
        }
        faustFile << "};\n";
        faustFile.close();
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
    delete volumetricMesh;
    volumetricMesh = nullptr;
    delete objMesh;
    objMesh = nullptr;
 
    return 0;
}
