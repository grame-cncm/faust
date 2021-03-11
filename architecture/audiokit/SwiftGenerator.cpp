/************************************************************************
 FAUST Architecture File
 Copyright (C) 2021 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************/

#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/misc.h"

using namespace std;

<<includeIntrinsic>>
<<includeclass>>

struct SwiftFilePrinter : public GenericUI
{
    ofstream& fOutFile;
    string fKlassName;
    string fDSPName;
    string fUniqueCode;
    string fUnit;
    stringstream fInit1;
    stringstream fInit2;
    vector<string> fInit3;
    
    SwiftFilePrinter(const string& class_name, ofstream& out_file):fKlassName("Faust" + class_name), fDSPName(class_name), fOutFile(out_file)
    {
        fInit1 << "public init(_ input: Node? = nil";
        // this may need to be unique per node
        fUniqueCode = "Fdsp";
    }
    
    void printHeader()
    {
        fOutFile << "// Copyright AudioKit. All Rights Reserved. Revision History at http://github.com/AudioKit/AudioKit/" << endl;
        fOutFile << "import AVFoundation" << endl;
        fOutFile << "import CAudioKit" << endl;
        fOutFile << "import AudioKit" << endl;
        fOutFile << endl;
        fOutFile << "/// Faust node" << endl;
        fOutFile << "public class " << fKlassName << ": Node, AudioUnitContainer, Toggleable {" << endl;
        fOutFile << endl;
        fOutFile << "\t" << "/// Unique four-letter identifier. If using multiple Faust generated nodes, make this unique for each" << endl;
        fOutFile << "\t" << "public static let ComponentDescription = AudioComponentDescription(instrument: \"" << fUniqueCode << "\")" << endl;
        fOutFile << endl;
        fOutFile << "\t" << "/// Internal type of audio unit for this node" << endl;
        fOutFile << "\t" << "public typealias AudioUnitType = InternalAU" << endl;
        fOutFile << endl;
        fOutFile << "\t" << "public private(set) var internalAU: AudioUnitType?" << endl;
        fOutFile << endl;
        fOutFile << "\t" << "// MARK: - Parameters" << endl;
        fOutFile << endl;
    }
    
    void printFooter()
    {

        fOutFile << "\t" << "// MARK: - Audio Unit" << endl;
        fOutFile << "\tpublic class InternalAU: AudioUnitBase {" << endl;
        fOutFile << "\t\t" << "/// Get an array of the parameter definitions" << endl;
        fOutFile << "\t\t" << "/// - Returns: Array of parameter definitions" << endl;
        fOutFile << "\t\t" << "public override func getParameterDefs() -> [NodeParameterDef] {" << endl;
        fOutFile << "\t\t\t" << "[";
        for (int i = 0; i < fInit3.size(); i++) {
            fOutFile << fInit3[i];
            if (i < fInit3.size() - 1) fOutFile << ",\n\t\t\t";
        }
        fOutFile << "]" << endl;
        fOutFile << "\t\t}" << endl;
        
        fOutFile << "\t\t/// Create the DSP Refence for this node" << endl;
        fOutFile << "\t\t/// - Returns: DSP Reference" << endl;
        fOutFile << "\t\tpublic override func createDSP() -> DSPRef { akCreateDSP(\"" << fKlassName << "\") }" << endl;
        fOutFile << "\t}" << endl << endl;
        
        fOutFile << "\t" << "// MARK: - Initialization" << endl;
        fOutFile << "\t" << fInit1.str() << ") {" << endl;
        fOutFile << "\t\t" << "super.init(avAudioNode: input?.avAudioUnitOrNode ?? AVAudioNode())" << endl;
        fOutFile << "\t\t" << "instantiateAudioUnit { avAudioUnit in" << endl;
        fOutFile << "\t\t\t" << "self.avAudioUnit = avAudioUnit" << endl;
        fOutFile << "\t\t\t" << "self.avAudioNode = avAudioUnit" << endl;
        fOutFile << "\t\t\t" << "guard let audioUnit = avAudioUnit.auAudioUnit as? AudioUnitType else { fatalError(\"Couldn't create audio unit\") }" << endl;
        fOutFile << "\t\t\t" << "self.internalAU = audioUnit" << endl;
        fOutFile << "\t\t\t" << "self.stop()" << endl;
        fOutFile << fInit2.str();
        fOutFile << "\t\t}" << endl;
        fOutFile << "\t}" << endl;
        
        fOutFile << "}" << endl << endl;
    }
    
    string printUnit()
    {
        if (fUnit == "Hz") {
            return ".hertz";
        } else if (fUnit == "dB") {
            return ".decibels";
        } else {
            return ".customUnit";
        }
    }
    
    void printButton(const char* label_aux)
    {
        string label = label_aux;
        std::replace(label.begin(), label.end(), ' ', '_');
    }
    
    void printParam(const char* label_aux, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT init)
    {
        string label = label_aux;
        std::replace(label.begin(), label.end(), ' ', '_');

        fOutFile << "\t" << "// " << label << endl;
        fOutFile << "\t" << "public static var let" << label << "Def = NodeParameterDef(identifier: \"" << label << "\", ";
        fInit3.push_back(fKlassName + ".let" + string(label) + "Def");
        fOutFile << "name: \"" << label << "\", ";
        fOutFile << "address: akGetParameterAddress(\"" << fDSPName << "_" << label << "\"), ";
        fOutFile << "range: " << min << " ... " << max << ", ";
        fOutFile << "unit: " << printUnit() << ", ";
        fOutFile << "flags: .default)";
        fOutFile << endl << endl;
        fOutFile << "\t" << "@Parameter public var " << label << ": AUValue" << endl << endl;
        
        // Complete fInit1
        fInit1 << ", " << label << ": AUValue = " << init;
        
        // Complete fInit2
        fInit2 << "\t\t\t" << "self." << label << " = " << label << endl;
        
        // Reset unit metadata
        fUnit = "";
    }
   
    // -- active widgets
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        printButton(label);
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        printButton(label);
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        printParam(label, min, max, init);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        printParam(label, min, max, init);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        printParam(label, min, max, init);
    }
    
    // -- passive widgets
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        if (strcmp(key, "unit") == 0) {
            fUnit = val;
        }
    }
    
};

struct Meta1 : Meta
{
    string fFileName;
    void declare(const char* key, const char* value)
    {
        if (strcmp("filename", key) == 0) {
            fFileName = value;
        }
    }
};

int main(int argc, char* argv[])
{
    mydsp dsp;
    
    Meta1 meta1;
    dsp.metadata(&meta1);
   
    // Generate the swift output file
    string file_name = meta1.fFileName;
    file_name.erase(file_name.end() - 4, file_name.end());
    
    ofstream out_file("Faust" + file_name + ".swift");
    SwiftFilePrinter printer(file_name, out_file);
    printer.printHeader();
    dsp.buildUserInterface(&printer);
    printer.printFooter();
    
    return 0;
}
