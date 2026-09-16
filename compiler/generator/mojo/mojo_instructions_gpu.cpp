/*                                                                             *
*   SPDX-FileCopyrightText: 2026 GRAME, Centre National de Creation Musicale   *
*   SPDX-License-Identifier: LGPL-2.1-or-later                                 *
*                                                                             */

/** @file compiler/generator/mojo/mojo_instructions_gpu.cpp **/

#include "mojo_instructions.hh"

inline namespace mojo {

MojoGpuInstVisitor::MojoGpuInstVisitor(
    OStream* out, String const& name, Work const& work, Views const& views, s32 tab
) : MojoInstVisitor(out, name, tab), fWork(work), fViews(views)
{}

bool MojoGpuInstVisitor::isChannel(String const& name)
{
    // NOTE:(Ari) use explicit size, prefer ssize if possible, but use usize if needed
    // auto pos = name.find_first_of("0123456789");
    usize pos = name.find_first_of("0123456789");
    if (pos == String::npos) {
        return false;
    }
    String prefix = name.substr(0, pos);
    if (prefix != "input" && prefix != "output") {
        return false;
    }
    usize end = name.find_first_not_of("0123456789", pos);
    return end == String::npos || name.substr(end) == "_ptr";
}

void MojoGpuInstVisitor::visit(NamedAddress* inst)
{
    auto loop = fLoops.find(inst->fName);
    if (loop != fLoops.end()) {
        *fOut << loop->second;
        return;
    }
    if (inst->fName == "vsize") {
        *fOut << "count";
        return;
    }
    if (inst->fName == "vindex") {
        *fOut << "offset";
        return;
    }
    if (inst->isStruct() || inst->isStaticStruct()) {
        *fOut << "dsp[].";
    } else if (fWork.count(inst->fName)) {
        *fOut << "work[].";
    }
    *fOut << snakeCase(inst->fName);
}

void MojoGpuInstVisitor::visit(DeclareVarInst* inst)
{
    if (isChannel(inst->getName()) || fViews.count(inst->getName())) {
        return;
    }
    if (!fWork.count(inst->getName())) {
        if (!inst->fValue && !dynamic_cast<ArrayTyped*>(inst->fType)) {
            *fOut << "var " << snakeCase(inst->getName()) << ": "
                  << fTypeManager->generateType(inst->fType) << wnextl(fTab);
        } else {
            MojoInstVisitor::visit(inst);
        }
        return;
    }
    if (inst->fValue) {
        inst->fAddress->accept(this);
        *fOut << " = ";
        bool address = dynamic_cast<LoadVarAddressInst*>(inst->fValue);
        if (address) {
            *fOut << "Ptr(to=";
        }
        inst->fValue->accept(this);
        if (address) {
            *fOut << ")";
        }
        *fOut << wnextl(fTab);
    }
}

void MojoGpuInstVisitor::visit(IndexedAddress* inst)
{
    if (isChannel(inst->getName())) {
        inst->fAddress->accept(this);
        *fOut << "[unsafe_offset=";
        inst->getIndex()->accept(this);
        *fOut << "]";
    } else {
        MojoInstVisitor::visit(inst);
    }
}

void MojoGpuInstVisitor::visit(FloatNumInst* inst)
{   *fOut << "F32(" << checkFloat(inst->fNum) << ")";   }

void MojoGpuInstVisitor::visit(DoubleNumInst* inst)
{   *fOut << "F64(" << checkDouble(inst->fNum) << ")";   }

void MojoGpuInstVisitor::visit(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    auto* init = dynamic_cast<DeclareVarInst*>(inst->fInit);
    if (!init || !init->fValue) {
        throw faustexception("ERROR : unsupported GPU loop initializer.\n");
    }
    String name  = init->getName();
    String saved = fLoops.count(name) ? fLoops.at(name) : "";
    String local = snakeCase(name) + "_" + std::to_string(fLoopId++);
    // Evaluate the initializer before introducing the new binding.
    *fOut << "var " << local << " = ";
    init->fValue->accept(this);
    *fOut << wnextl(fTab);
    fLoops[name] = local;
    *fOut << "while ";
    inst->fEnd->accept(this);
    fTab += 1;
    *fOut << ":" << wnextl(fTab);
    inst->fCode->accept(this);
    inst->fIncrement->accept(this);
    fTab -= 1;
    *fOut << wrewind(fOut);
    if (saved.empty()) {
        fLoops.erase(name);
    } else {
        fLoops[name] = saved;
    }
}

void MojoGpuInstVisitor::visit(FunCallInst* inst)
{
    if (!gMathLibTable.count(inst->fName)) {
        throw faustexception(
            "ERROR : Mojo GPU has no device implementation for '" + inst->fName + "'.\n"
        );
    }
    MojoInstVisitor::visit(inst);
}

}  // namespace mojo
