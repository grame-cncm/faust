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

#include "faust/gui/JSONUI.h"
#include "instructions.hh"

using namespace std;

#ifdef WIN32
#pragma warning(disable : 4244)
#endif

/*
 FIR visitor to prepare the JSON representation.
*/

struct JSONInstVisitor : public DispatchVisitor, public JSONUI {
    map<string, string> fPathTable;  // Table : field_name, complete path

    using DispatchVisitor::visit;

    JSONInstVisitor(const std::string& name, const std::string& filename, int inputs, int outputs, int sr_index,
                    const std::string& sha_key, const std::string& dsp_code, const std::string& version,
                    const std::string& compile_options, const std::vector<std::string>& library_list,
                    const std::vector<std::string>& include_pathnames, const std::string& size,
                    const std::map<std::string, int>& path_table)
        : JSONUI(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list,
                 include_pathnames, size, path_table)
    {
    }

    JSONInstVisitor(int inputs, int outputs) : JSONUI(inputs, outputs) {}

    JSONInstVisitor() : JSONUI() {}

    virtual ~JSONInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst) { declare(NULL, inst->fKey.c_str(), inst->fValue.c_str()); }

    virtual void visit(OpenboxInst* inst)
    {
        switch (inst->fOrient) {
            case 0:
                openVerticalBox(inst->fName.c_str());
                break;
            case 1:
                openHorizontalBox(inst->fName.c_str());
                break;
            case 2:
                openTabBox(inst->fName.c_str());
                break;
            default:
                faustassert(false);
                break;
        }
    }

    virtual void visit(CloseboxInst* inst) { closeBox(); }

    virtual void visit(AddButtonInst* inst)
    {
        if (inst->fType == AddButtonInst::kDefaultButton) {
            addButton(inst->fLabel.c_str(), nullptr);
        } else {
            addCheckButton(inst->fLabel.c_str(), nullptr);
        }

        fPathTable[inst->fZone] = buildPath(inst->fLabel);
    }

    virtual void visit(AddSliderInst* inst)
    {
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                addHorizontalSlider(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            case AddSliderInst::kVertical:
                addVerticalSlider(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            case AddSliderInst::kNumEntry:
                addNumEntry(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            default:
                faustassert(false);
                break;
        }

        fPathTable[inst->fZone] = buildPath(inst->fLabel);
    }

    virtual void visit(AddBargraphInst* inst)
    {
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                addHorizontalBargraph(inst->fLabel.c_str(), nullptr, inst->fMin, inst->fMax);
                break;
            case AddBargraphInst::kVertical:
                addVerticalBargraph(inst->fLabel.c_str(), nullptr, inst->fMin, inst->fMax);
                break;
            default:
                faustassert(false);
                break;
        }

        fPathTable[inst->fZone] = buildPath(inst->fLabel);
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        addSoundfile(inst->fLabel.c_str(), inst->fURL.c_str(), nullptr);
        fPathTable[inst->fSFZone] = buildPath(inst->fLabel);
    }

    void setInputs(int input) { fInputs = input; }
    void setOutputs(int output) { fOutputs = output; }
};

#endif
