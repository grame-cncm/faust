/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _JSON_INSTRUCTIONS_H
#define _JSON_INSTRUCTIONS_H

#include <string>
#include <set>

#include "faust/gui/JSONUI.h"
#include "instructions.hh"
#include "exception.hh"

using namespace std;

#ifdef WIN32
#pragma warning(disable : 4244)
#endif

/*
 FIR visitor to prepare the JSON representation.
*/

template <typename REAL>
struct JSONInstVisitor : public DispatchVisitor, public JSONUIReal<REAL> {
    map<string, string> fPathTable; // Table : field_name, complete path
    set<string> fControlPathSet;    // Set of already used control paths
 
    using DispatchVisitor::visit;
    
    const string& insertPath(set<string>& table, const string& path, bool check = true)
    {
        if (check && table.find(path) != table.end()) {
            throw faustexception("ERROR : path '" + path + "' is already used\n");
        } else {
            table.insert(path);
        }
        return path;
    }
  
    JSONInstVisitor(const std::string& name, const std::string& filename, int inputs, int outputs, int sr_index,
                    const std::string& sha_key, const std::string& dsp_code, const std::string& version,
                    const std::string& compile_options, const std::vector<std::string>& library_list,
                    const std::vector<std::string>& include_pathnames, int size,
                    const std::map<std::string, int>& path_table,
                    MemoryLayoutType memory_layout)
        : JSONUIReal<REAL>(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list,
                 include_pathnames, size, path_table, memory_layout)
    {
    }

    JSONInstVisitor(int inputs, int outputs) : JSONUIReal<REAL>(inputs, outputs) {}

    JSONInstVisitor() : JSONUIReal<REAL>() {}

    virtual ~JSONInstVisitor() {}
  
    virtual void visit(AddMetaDeclareInst* inst) { this->declare(NULL, inst->fKey.c_str(), inst->fValue.c_str()); }

    virtual void visit(OpenboxInst* inst)
    {
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                this->openVerticalBox(inst->fName.c_str());
                break;
            case OpenboxInst::kHorizontalBox:
                this->openHorizontalBox(inst->fName.c_str());
                break;
            case OpenboxInst::kTabBox:
                this->openTabBox(inst->fName.c_str());
                break;
        }
    }

    virtual void visit(CloseboxInst* inst) { this->closeBox(); }

    virtual void visit(AddButtonInst* inst)
    {
        switch (inst->fType) {
            case AddButtonInst::kDefaultButton:
                this->addButton(inst->fLabel.c_str(), nullptr);
                break;
            case AddButtonInst::kCheckButton:
                this->addCheckButton(inst->fLabel.c_str(), nullptr);
                break;
            default:
                faustassert(false);
                break;
        }
        faustassert(fPathTable.find(inst->fZone) == fPathTable.end());
        fPathTable[inst->fZone] = insertPath(fControlPathSet, this->buildPath(inst->fLabel));
    }

    virtual void visit(AddSliderInst* inst)
    {
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                this->addHorizontalSlider(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            case AddSliderInst::kVertical:
                this->addVerticalSlider(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            case AddSliderInst::kNumEntry:
                this->addNumEntry(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            default:
                faustassert(false);
                break;
        }
        faustassert(fPathTable.find(inst->fZone) == fPathTable.end());
        fPathTable[inst->fZone] = insertPath(fControlPathSet, this->buildPath(inst->fLabel));
    }

    virtual void visit(AddBargraphInst* inst)
    {
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                this->addHorizontalBargraph(inst->fLabel.c_str(), nullptr, inst->fMin, inst->fMax);
                break;
            case AddBargraphInst::kVertical:
                this->addVerticalBargraph(inst->fLabel.c_str(), nullptr, inst->fMin, inst->fMax);
                break;
            default:
                faustassert(false);
                break;
        }
        faustassert(fPathTable.find(inst->fZone) == fPathTable.end());
        fPathTable[inst->fZone] = insertPath(fControlPathSet, this->buildPath(inst->fLabel), false);
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        this->addSoundfile(inst->fLabel.c_str(), inst->fURL.c_str(), nullptr);
        faustassert(fPathTable.find(inst->fSFZone) == fPathTable.end());
        fPathTable[inst->fSFZone] = insertPath(fControlPathSet, this->buildPath(inst->fLabel));
    }

    void setInputs(int input) { this->fInputs = input; }
    void setOutputs(int output) { this->fOutputs = output; }
};

#endif
