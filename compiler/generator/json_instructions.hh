/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _JSON_INSTRUCTIONS_H
#define _JSON_INSTRUCTIONS_H

#include <string>
#include <sstream>
#include <set>

#include "faust/gui/JSONUI.h"
#include "instructions.hh"
#include "exception.hh"

#ifdef WIN32
#pragma warning(disable : 4244)
#endif

/*
 FIR visitor to prepare the JSON representation.
*/

template <typename REAL>
struct JSONInstVisitor : public DispatchVisitor, public JSONUIReal<REAL> {
    std::map<std::string, std::string> fPathTable;  // Table : field_name, complete path
    std::set<std::string> fInputsPathSet;           // Set of already used inputs control paths
    std::set<std::string> fOuputsPathSet;           // Set of already used outputs control paths
 
    using DispatchVisitor::visit;
    
    const std::string& insertInputsPath(const std::string& path)
    {
        // Two input control cannot have a same path (ERROR)
        if (fInputsPathSet.find(path) != fInputsPathSet.end()) {
            throw faustexception("ERROR : path '" + path + "' is already used\n");
        }
        // An input control and a bargraph cannot have the same path (ERROR)
        if (fOuputsPathSet.find(path) != fOuputsPathSet.end()) {
            throw faustexception("ERROR : path '" + path + "' is already used for a bargraph\n");
        }
        fInputsPathSet.insert(path);
        return path;
    }
    
    const std::string& insertOutputsPath(const std::string& path)
    {
        // An input control and a bargraph cannot have the same path (ERROR)
        if (fInputsPathSet.find(path) != fInputsPathSet.end()) {
            throw faustexception("ERROR : path '" + path + "' is already used for a input control\n");
        }
        // Two bargraph can have the same path (WARNING)
        if (fOuputsPathSet.find(path) != fOuputsPathSet.end()) {
            std::stringstream error;
            error << "WARNING : bargraph path '" + path + "' is already used";
            gWarningMessages.push_back(error.str());
        }
        fOuputsPathSet.insert(path);
        return path;
    }
  
    JSONInstVisitor(const std::string& name, const std::string& filename, int inputs, int outputs, int sr_index,
                    const std::string& sha_key, const std::string& dsp_code, const std::string& version,
                    const std::string& compile_options, const std::vector<std::string>& library_list,
                    const std::vector<std::string>& include_pathnames, int size,
                    const PathTableType& path_table,
                    MemoryLayoutType memory_layout,
                    InstComplexity inst_comp = {})
        : JSONUIReal<REAL>(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list,
                 include_pathnames, size, path_table, memory_layout, inst_comp)
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
        fPathTable[inst->fZone] = insertInputsPath(this->buildPath(inst->fLabel));
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
        fPathTable[inst->fZone] = insertInputsPath(this->buildPath(inst->fLabel));
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
        fPathTable[inst->fZone] = insertOutputsPath(this->buildPath(inst->fLabel));
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        this->addSoundfile(inst->fLabel.c_str(), inst->fURL.c_str(), nullptr);
        faustassert(fPathTable.find(inst->fSFZone) == fPathTable.end());
        fPathTable[inst->fSFZone] = insertInputsPath(this->buildPath(inst->fLabel));
    }

    void setInputs(int input) { this->fInputs = input; }
    void setOutputs(int output) { this->fOutputs = output; }
};

/*
 FIR visitor used with PathBuilder to prepare the path <==> shotnames map
 */

struct ShortnameInstVisitor : public DispatchVisitor, public PathBuilder {

    virtual void visit(OpenboxInst* inst) override
    {
        pushLabel(inst->fName);
    }
    
    virtual void visit(CloseboxInst* inst) override
    {
        if (popLabel()) {
            // Shortnames can be computed when all fullnames are known
            computeShortNames();
        }
    }
    
    virtual void visit(AddButtonInst* inst) override
    {
        addFullPath(inst->fLabel);
    }
    
    virtual void visit(AddSliderInst* inst) override
    {
        addFullPath(inst->fLabel);
    }
    
    virtual void visit(AddBargraphInst* inst) override
    {
        addFullPath(inst->fLabel);
    }
};

#endif
