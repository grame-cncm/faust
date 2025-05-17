/************************** BEGIN PathBuilder.cpp **************************
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
 ************************************************************************/

#include "PathBuilder.h"
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iostream> //for debugging

#include "faust/export.h"

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

void PathBuilder::addFullPathNew(const std::string& label,const std::string& varname) { fFullPathsNew.push_back({buildPath(label),varname}); }

// Assuming shortnames have been built, return the shortname from a label
std::string PathBuilder::buildShortnameNew(const std::string& varname)
        {
            return (hasShortname()) ? fVarname2Short[varname] : "";
        }

void PathBuilder::computeShortNamesNew()
        {
            std::vector<std::string>           uniquePathsNew;  // all full paths transformed but made unique with a prefix
            std::map<std::string, std::string> unique2varname;  // all full paths transformed but made unique with a prefix

            std::vector<std::string>           uniquePaths;  // all full paths transformed but made unique with a prefix
            std::map<std::string, std::string> unique2full;  // all full paths transformed but made unique with a prefix
            char num_buffer[16];
            int pnum = 0;

            std::cerr << "fFullPaths len:"<< fFullPaths.size() << std::endl;
            std::cerr << "fFullPathsNew len:"<< fFullPathsNew.size() << std::endl;
            for (const auto& t : fFullPathsNew) {
                std::string s;
                std::string varname; 
                std::tie(s,varname) = t;
                std::cerr << "fFullPathsNew s:"<< s << std::endl;
                std::cerr << "fFullPathsNew varname:"<< varname << std::endl;
                snprintf(num_buffer, 16, "%d", pnum++);
                std::string u = "/P" + std::string(num_buffer) + str2ID(remove0x00(s));
                uniquePathsNew.push_back(u);
                unique2varname[u] = varname;  // remember the varname associated to a unique path
            }

            pnum = 0;
            for (const auto& s : fFullPaths) {
                // std::string s;
                // std::string varname; 
                // std::tie(s,varname) = t;
                // std::cerr << "s:"<< s << std::endl;
                // std::cerr << "v:"<< varname << std::endl;

                // Using snprintf since Teensy does not have the std::to_string function
                snprintf(num_buffer, 16, "%d", pnum++);
                std::string u = "/P" + std::string(num_buffer) + str2ID(remove0x00(s));
                uniquePaths.push_back(u);
                unique2full[u] = s;  // remember the full path associated to a unique path
                std::cerr << "uniquePath u:"<< u << std::endl;
                std::cerr << "fullPath s:"<< s << std::endl;
            }
        
            std::map<std::string, int> uniquePath2level;                // map path to level
            for (const auto& s : uniquePaths) uniquePath2level[s] = 1;   // we init all levels to 1
            bool have_collisions = true;
        
            while (have_collisions) {
                // compute collision list
                std::set<std::string>              collisionSet;
                std::map<std::string, std::string> short2full;
                have_collisions = false;
                for (const auto& it : uniquePath2level) {
                    std::string u = it.first;
                    int n = it.second;
                    std::string shortName = cut(u, n);
                    auto p = short2full.find(shortName);
                    if (p == short2full.end()) {
                        // no collision
                        short2full[shortName] = u;
                    } else {
                        // we have a collision, add the two paths to the collision set
                        have_collisions = true;
                        collisionSet.insert(u);
                        collisionSet.insert(p->second);
                    }
                }
                for (const auto& s : collisionSet) uniquePath2level[s]++;  // increase level of colliding path
            }
        
            for (const auto& it : uniquePath2level) {
                std::string u = it.first;
                int n = it.second;
                std::string shortName = replaceCharList(cut(u, n), {'/'}, '_');
                std::cerr << "u:" << u << std::endl;
                std::cerr << "n:" << n  << std::endl;
                std::cerr << "cut(u, n):" << cut(u, n)  << std::endl;
                std::cerr << "shortName:" << shortName << std::endl;
                fFull2Short[unique2full[u]] = shortName;
                fVarname2Short[unique2varname[u]] = shortName;
                // fFull2Short[varname] = shortName;
            }
        }


