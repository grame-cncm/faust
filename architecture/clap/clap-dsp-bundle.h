//
// clap-dsp-bundle.h
//
// One compiled Faust DSP and everything that belongs to it: the interpreter
// factory, the instance, the UI, and the CLAP slot mapping.
//
// The whole point of the type is its lifecycle. A bundle is built complete or
// not at all, and it is never mutated structurally once handed out. Reloading
// is therefore "build a second bundle, publish it, retire the first", never
// "tear the live one down and hope the replacement compiles". That is what
// makes a syntax error during live editing a no-op: the running DSP keeps
// playing because nothing touched it.
//
#ifndef CLAP_DSP_BUNDLE_H
#define CLAP_DSP_BUNDLE_H

#include <faust/dsp/interpreter-dsp.h>

#include <string>
#include <vector>

#include "clap-mapui.h"

class DspBundle {
   public:
    ~DspBundle();

    DspBundle(const DspBundle&)            = delete;
    DspBundle& operator=(const DspBundle&) = delete;

    // Compile, instantiate, build the UI, init at sampleRate, restore what can
    // be restored from `previous`, and lay out the slot table. Returns nullptr
    // with `error` set if any step fails; `previous` is only read.
    //
    // Callable from any thread except the audio thread: it compiles, allocates
    // and does file I/O.
    static DspBundle* fromFile(const std::string& path, int sampleRate, int slotCount,
                               const DspBundle* previous, std::string& error);

    static DspBundle* fromString(const std::string& name, const std::string& code, int sampleRate,
                                 int slotCount, const DspBundle* previous, std::string& error);

    dsp* getDSP() const { return fDSP; }

    // Not const: the audio thread writes parameter zones through it.
    CLAPMapUI& getUI() const { return const_cast<CLAPMapUI&>(fUI); }

    const std::string& getPath() const { return fPath; }
    int                getNumInputs() const { return fNumInputs; }
    int                getNumOutputs() const { return fNumOutputs; }
    int                getParamsCount() const { return fUI.getParamsCount(); }

    // Faust parameter index behind a CLAP slot, or -1 when the slot is unused.
    int slotToParam(uint32_t slot) const
    {
        return (slot < fSlotToParam.size()) ? fSlotToParam[slot] : -1;
    }

    // Addresses of the controls that did not fit in the available slots. Empty
    // in the normal case; reported rather than silently dropped, which is what
    // the fixed ceiling used to do.
    const std::vector<std::string>& getUnreachableParams() const { return fUnreachable; }

    // The slot table, so that the next reload can preserve slot identity.
    const std::vector<std::string>& getSlotAddresses() const { return fSlotAddress; }

   private:
    DspBundle() = default;

    // Shared tail of the two factory functions: everything after the
    // interpreter factory exists.
    bool finish(int sampleRate, int slotCount, const DspBundle* previous, std::string& error);

    // Slot s keeps its address across a reload when that address still exists,
    // so a host keeps its automation and its MIDI learn through an edit. Any
    // control without a slot goes into the first free one; what is left over is
    // recorded in fUnreachable.
    void buildSlotMapping(int slotCount, const DspBundle* previous);

    interpreter_dsp_factory* fFactory = nullptr;
    dsp*                     fDSP     = nullptr;
    CLAPMapUI                fUI;
    std::string              fPath;
    int                      fNumInputs  = 0;
    int                      fNumOutputs = 0;

    std::vector<std::string> fSlotAddress;  // "" means the slot is unused
    std::vector<int>         fSlotToParam;  // -1 means the slot is unused
    std::vector<std::string> fUnreachable;
};

#endif  // CLAP_DSP_BUNDLE_H
