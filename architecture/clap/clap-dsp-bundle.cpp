//
// clap-dsp-bundle.cpp
//

#include "clap-dsp-bundle.h"

#include <fstream>
#include <sstream>

DspBundle::~DspBundle()
{
    // Order matters: the instance belongs to the factory.
    delete fDSP;
    if (fFactory) {
        deleteInterpreterDSPFactory(fFactory);
    }
}

DspBundle* DspBundle::fromFile(const std::string& path, int sampleRate, int slotCount,
                               const DspBundle* previous, std::string& error)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        error = "cannot open " + path;
        return nullptr;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    if (file.bad()) {
        error = "cannot read " + path;
        return nullptr;
    }

    DspBundle* bundle = fromString(path, buffer.str(), sampleRate, slotCount, previous, error);
    if (bundle) {
        bundle->fPath = path;
    }
    return bundle;
}

DspBundle* DspBundle::fromString(const std::string& name, const std::string& code, int sampleRate,
                                 int slotCount, const DspBundle* previous, std::string& error)
{
    DspBundle* bundle = new DspBundle();

    // The DSP directory goes on the import path, so that a program which
    // imports a sibling library still compiles when the host's working
    // directory is somewhere else entirely.
    std::string  directory;
    const size_t slash = name.find_last_of("/\\");
    if (slash != std::string::npos) {
        directory = name.substr(0, slash);
    }
    const char* argv[2] = {"-I", directory.c_str()};
    const int   argc    = directory.empty() ? 0 : 2;

    bundle->fFactory = createInterpreterDSPFactoryFromString(name, code, argc, argv, error);
    if (!bundle->fFactory) {
        delete bundle;
        return nullptr;
    }

    if (!bundle->finish(sampleRate, slotCount, previous, error)) {
        delete bundle;
        return nullptr;
    }
    bundle->fPath = name;
    return bundle;
}

bool DspBundle::finish(int sampleRate, int slotCount, const DspBundle* previous, std::string& error)
{
    fDSP = fFactory->createDSPInstance();
    if (!fDSP) {
        error = "cannot instantiate the compiled DSP";
        return false;
    }

    // buildUserInterface before init: init writes the default values into the
    // zones the UI is about to publish.
    fDSP->buildUserInterface(&fUI);
    fDSP->init(sampleRate);

    fNumInputs  = fDSP->getNumInputs();
    fNumOutputs = fDSP->getNumOutputs();

    // Carry values over by address, so that editing a DSP does not reset the
    // controls that survived the edit. Reading the previous bundle's zones can
    // race with the audio thread writing them; the result is at worst one
    // automation step stale, which is the right trade for not locking the
    // audio thread.
    const int count = fUI.getParamsCount();
    for (int i = 0; i < count; ++i) {
        FAUSTFLOAT value = fUI.getParamInit(i);
        if (previous) {
            const CLAPMapUI& old      = previous->getUI();
            const int        oldCount = old.getParamsCount();
            for (int j = 0; j < oldCount; ++j) {
                if (old.getParamAddress(j) == fUI.getParamAddress(i)) {
                    value = fUI.clampToRange(i, old.getParamValue(j));
                    break;
                }
            }
        }
        fUI.setParamValue(i, value);
    }

    buildSlotMapping(slotCount, previous);
    return true;
}

void DspBundle::buildSlotMapping(int slotCount, const DspBundle* previous)
{
    fSlotAddress.assign(slotCount, std::string());
    fSlotToParam.assign(slotCount, -1);

    const int         count = fUI.getParamsCount();
    std::vector<bool> assigned(count, false);

    // First pass: a slot that already existed keeps its address, so the host's
    // automation lane still points at the same control after the reload.
    if (previous) {
        const std::vector<std::string>& old = previous->getSlotAddresses();
        const int shared = int(old.size() < fSlotAddress.size() ? old.size() : fSlotAddress.size());
        for (int s = 0; s < shared; ++s) {
            if (old[s].empty()) {
                continue;
            }
            for (int j = 0; j < count; ++j) {
                if (!assigned[j] && fUI.getParamAddress(j) == old[s]) {
                    fSlotAddress[s] = old[s];
                    fSlotToParam[s] = j;
                    assigned[j]     = true;
                    break;
                }
            }
        }
    }

    // Second pass: whatever is left takes the first free slot.
    for (int j = 0; j < count; ++j) {
        if (assigned[j]) {
            continue;
        }
        bool placed = false;
        for (int s = 0; s < slotCount; ++s) {
            if (fSlotAddress[s].empty()) {
                fSlotAddress[s] = fUI.getParamAddress(j);
                fSlotToParam[s] = j;
                assigned[j]     = true;
                placed          = true;
                break;
            }
        }
        if (!placed) {
            fUnreachable.push_back(fUI.getParamAddress(j));
        }
    }
}
