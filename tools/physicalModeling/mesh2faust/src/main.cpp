#include "mesh2faust.h"

#include <iostream>
#include <fstream>

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
    const char *objectFileName = "";
    std::string modelName = "modalModel";
    m2f::MaterialProperties materialProperties{};
    bool freqControl = false;
    float modesMinFreq = 20, modesMaxFreq = 10000;
    int targetNModes = 20, femNModes = 100;
    std::vector<int> exPos;
    int nExPos = -1;
    bool debugMode = false, showFreqs = false;
 
    /////////////////////////////////////
    // PARSE ARGUMENTS
    /////////////////////////////////////
    int currentArg = 0;
    if (argc > 1) {
        while (currentArg <= (argc - 1)) {
            if (strcmp(argv[currentArg], "--infile") == 0) {
                currentArg++;
                objectFileName = argv[currentArg];
                if (strcmp(objectFileName, "") == 0) {
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
                        double value = strtod(argv[currentArg], NULL);
                        if (i == 0) materialProperties.youngModulus = value;
                        else if (i == 1) materialProperties.poissonRatio = value;
                        else if (i == 2) materialProperties.density = value;
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
                modelName = argv[currentArg];
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

    string dsp = m2f::mesh2faust(
        objectFileName,
        materialProperties,
        {
            modelName,
            freqControl,
            modesMinFreq,
            modesMaxFreq,
            targetNModes,
            femNModes,
            exPos,
            nExPos,
            showFreqs,
            debugMode
        }
    );

    string faustFileName = modelName + ".lib";
    ofstream faustFile(faustFileName.c_str());
    faustFile << dsp;
    faustFile.close();

    return 0;
}
