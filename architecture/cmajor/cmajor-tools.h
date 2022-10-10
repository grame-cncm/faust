/************************** BEGIN cmajor-tools.h *************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __cmajortools_dsp__
#define __cmajortools_dsp__

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <map>
#include <algorithm>

#include "faust/dsp/libfaust.h"

/**
 * Faust/Cmajor hybrid file parser
 */
class faust_cmajor_parser  {
    
    private:
        
        std::map <std::string, std::string> extractFaustBlocks(std::istream& in, std::stringstream& res_file)
        {
            std::string line;
            std::stringstream faust_block;
            bool is_faust_block = false;
            int brackets = 0;
            std::map <std::string, std::string> faust_blocks;     // name, code
            std::map <std::string, std::string>::iterator cur_faust_block;
            
            while (getline(in, line)) {
                
                std::stringstream line_reader(line);
                std::string token1, token2, token3;
                
                line_reader >> token1;
                line_reader >> token2;
                line_reader >> token3;
                
                if (is_faust_block) {
                    // End of block
                    if ((token1 == "}") && (--brackets == 0)) {
                        is_faust_block = false;
                        cur_faust_block->second = faust_block.str();
                        faust_block.str("");
                        // Start of block (or could be on the previous line)
                    } else if (token1 == "{") {
                        brackets++;
                        continue;
                    } else {
                        faust_block << line << "\n";
                    }
                    continue;
                } else {
                    is_faust_block = (token1 == "faust" && token2 != "");
                    if (is_faust_block) {
                        if (token3 == "{") brackets++;
                        faust_blocks[token2] = "";
                        cur_faust_block = faust_blocks.find(token2);
                    }
                }
                
                // Keep the lines of Cmajor file
                if (!is_faust_block) res_file << line << std::endl;
            }
            
            return faust_blocks;
        }
    
        std::string generateCmajorBlock(const std::string& name, const std::string& code, int argc, const char* argv[])
        {
            int argc1 = 0;
            const char* argv1[64];
            argv1[argc1++] = "-lang";
            //argv1[argc1++] = "cmajor";
            argv1[argc1++] = "cmajor-hybrid";
            argv1[argc1++] = "-cn";
            argv1[argc1++] = name.c_str();
            argv1[argc1++] = "-o";
            argv1[argc1++] = "/var/tmp/exp.cmajor";
            for (int i = 0; i < argc; i++) {
                argv1[argc1++] = argv[i];
            }
            argv1[argc1] = nullptr;  // NULL terminated argv
            
            std::string error_msg;
            bool res = generateAuxFilesFromString(name, code, argc1, argv1, error_msg);
            
            if (res) {
                std::ifstream cmajor_file("/var/tmp/exp.cmajor");
                std::string cmajor_string((std::istreambuf_iterator<char>(cmajor_file)), std::istreambuf_iterator<char>());
                return cmajor_string;
            } else {
                std::cerr << "ERROR : generateAuxFilesFromFile " << error_msg;
                return "";
            }
        }

    public:
    
        faust_cmajor_parser()
        {}
    
        ~faust_cmajor_parser()
        {}
 
        bool parseCmajorFile(const std::string& input, const std::string& output, int argc, const char* argv[])
        {
            std::ifstream reader(input.c_str());
            if (reader.is_open()) {
                
                // Open Cmajor output file
                std::ofstream output_file(output);
          
                // Extract the Faust blocks and returns the input file without them
                std::stringstream cmajor_file;
                std::map<std::string, std::string> faust_blocks = extractFaustBlocks(reader, cmajor_file);
                
                // Write all Faust blocks translated to Cmajor
                for (const auto& it : faust_blocks) {
                    std::string block = generateCmajorBlock(it.first, it.second, argc, argv);
                    if (block == "") return false;
                    output_file << block;
                }
                
                // Write the Cmajor part
                output_file << cmajor_file.str();
                output_file.close();
                
                return true;
            } else {
                return false;
            }
        }
    
        bool generateCmajorFile(const std::string& input, const std::string& output, int argc, const char* argv[])
        {
            int argc1 = 0;
            const char* argv1[64];
            argv1[argc1++] = "-lang";
            argv1[argc1++] = "cmajor";
            argv1[argc1++] = "-o";
            argv1[argc1++] = output.c_str();
            for (int i = 0; i < argc; i++) {
                argv1[argc1++] = argv[i];
            }
            argv1[argc1] = nullptr;  // NULL terminated argv
            
            std::string error_msg;
            bool res = generateAuxFilesFromFile(input, argc1, argv1, error_msg);
            if (!res) {
                std::cerr << "ERROR : generateAuxFilesFromFile " << error_msg;
            }
            return res;
        }
    
        void createCmajorPatch(const std::string& cmajor_file)
        {
            // Generate "cmajorpatch" file
            std::string cmajorpatch_file = cmajor_file + "patch";
            std::ofstream patch_file(cmajorpatch_file);
            patch_file << "{" << std::endl;
                patch_file << "\t\"CmajorVersion\": 1," << std::endl;
                patch_file << "\t\"ID\": \"grame.cmajor.hybrid\"," << std::endl;
                patch_file << "\t\"version\": \"1.0\"," << std::endl;
                patch_file << "\t\"name\": \"hybrid\"," << std::endl;
                patch_file << "\t\"description\": \"Cmajor example\"," << std::endl;
                patch_file << "\t\"category\": \"synth\"," << std::endl;
                patch_file << "\t\"manufacturer\": \"GRAME\"," << std::endl;
                patch_file << "\t\"website\": \"https://faust.grame.fr\"," << std::endl;
                patch_file << "\t\"isInstrument\": true," << std::endl;
                patch_file << "\t\"source\": "; patch_file << "\"" << cmajor_file << "\"" << std::endl;
            patch_file << "}";
            patch_file.close();
        }
   
};

#endif
/************************** END cmajor-dsp.h **************************/
