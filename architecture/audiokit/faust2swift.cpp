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

#include "faust/gui/JSONUIDecoder.h"
#include "faust/gui/DecoratorUI.h"

using namespace std;

static string pathToContent(const string& path)
{
    ifstream file(path.c_str(), ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size]  = 0;
    string result = buffer;
    file.close();
    delete[] buffer;
    return result;
}

struct SwiftFilePrinter : public GenericUI
{
    ofstream& fOutFile;
    string fKlassName;
    string fUnit;
    stringstream fInit1;
    stringstream fInit2;
    
    SwiftFilePrinter(const string& class_name, ofstream& out_file):fKlassName(class_name), fOutFile(out_file)
    {
        fInit1 << "public init(_ input: Node";
    }
    
    void printHeader()
    {
        fOutFile << "// Copyright AudioKit. All Rights Reserved. Revision History at http://github.com/AudioKit/AudioKit/" << endl;
        fOutFile << "import AVFoundation" << endl;
        fOutFile << "import CAudioKit" << endl;
        fOutFile << endl;
        fOutFile << "/// Faust node." << endl;
        fOutFile << "public class Faust" << fKlassName << ": Node, AudioUnitContainer, Toggleable {" << endl;
        fOutFile << endl;
        fOutFile << "\t" << "/// Unique four-letter identifier \"dclp\"" << endl;
        fOutFile << "\t" << "public static let ComponentDescription = AudioComponentDescription(effect: \"dclp\")" << endl;
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
        fOutFile << "\t" << "// MARK: - Initialization" << endl;
        fOutFile << "\t" << fInit1.str() << ")" << endl;
        fOutFile << "\t{" << endl;
        fOutFile << fInit2.str();
        fOutFile << "\t}" << endl;
        fOutFile << "}" << endl;
    }
    
    string printUnit()
    {
        if (fUnit == "Hz") {
            return ".hertz";
        } else if (fUnit == "dB") {
            return ".decibels";
        } else {
            return "";
        }
    }
    
    void printButton(const char* label)
    {
        
    }
    void printParam(const char* label, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT init)
    {
        fOutFile << "\t" << "// " << label << endl;
        fOutFile << "\t" << "public static let" << label << "Def = NodeParameterDef(identifier: \"" << label << "\", ";
        fOutFile << "name: \"" << label << "\", ";
        fOutFile << "address: akGetParameterAddress(\"" << fKlassName << "_" << label << "\"), ";
        fOutFile << "range: " << min << " ... " << max << ", ";
        string unit = printUnit();
        if (unit.size() > 0) fOutFile << "unit: " << unit << ", ";
        fOutFile << "flags: .default)";
        fOutFile << endl << endl;
        fOutFile << "\t" << "@Parameter public var " << label << ": AUValue" << endl << endl;
        
        // Complete fInit1
        fInit1 << ", " << label << ": AUValue = " << init;
        
        // Complete fInit2
        fInit2 << "\t\t" << "self." << label << " = " << label << endl;
        
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

int main(int argc, char* argv[])
{
    // Load JSON file and decode it
    string JSON = pathToContent(argv[1]);
    JSONUIDecoder decoded_ui(JSON);

    // Genarate swift file
    string file_name = decoded_ui.fFileName;
    file_name.erase(file_name.end() - 4, file_name.end());
    
    ofstream out_file("Faust" + file_name + ".swift");
    SwiftFilePrinter printer(file_name, out_file);
    printer.printHeader();
    decoded_ui.buildUserInterface(&printer);
    printer.printFooter();
    
    return 0;
}


