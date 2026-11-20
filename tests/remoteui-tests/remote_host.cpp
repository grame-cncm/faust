/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

// A test architecture for RemoteUI: no audio device, the DSP is computed by
// a thread of its own (64 frames a millisecond or so), so that bargraphs
// move; RemoteUI is started with the command line's -remote options. It runs
// until its standard input closes, then says goodbye to the phones.
//
//     faust -a tests/remoteui-tests/remote_host.cpp -I architecture foo.dsp -o foo.cpp
//     c++ -std=c++17 -O1 -I architecture foo.cpp -o foo -lpthread
//     ./foo -remote ws://127.0.0.1:8444 -remote-room r -remote-token t
//
// With -poly <n>, the DSP is polyphonic and the phones' MIDI plays it.
//
// Used by the conformance test of faustwasm (test/cli/remote-native.test.mjs).

#include <stdio.h>
#include <string.h>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>

#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/GUI.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/gui/RemoteUI.h"

<<includeIntrinsic>>

<<includeclass>>

// The statics of GUI, which poly-dsp.h uses
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char* argv[])
{
    int voices = 0;
    for (int i = 1; i + 1 < argc; i++) {
        if (strcmp(argv[i], "-poly") == 0) voices = atoi(argv[i + 1]);
    }
    mydsp_poly* poly = nullptr;
    ::dsp* DSP = nullptr;
    if (voices > 0) {
        poly = new mydsp_poly(new mydsp(), voices, true, true);
        DSP = poly;
    } else {
        DSP = new mydsp();
    }
    DSP->init(48000);

    RemoteUI remote("remote_host", DSP, argc, argv);
    DSP->buildUserInterface(&remote);
    if (poly) {
        remote.setMidiFunction([poly](const std::vector<int>& data) {
            int type = data[0] & 0xF0;
            int channel = data[0] & 0x0F;
            if (type == 0x90 && data[2] > 0) poly->keyOn(channel, data[1], data[2]);
            else if (type == 0x80 || type == 0x90) poly->keyOff(channel, data[1], data[2]);
            else if (type == 0xB0) poly->ctrlChange(channel, data[1], data[2]);
        });
        remote.setVoiceCounter([poly]() { return poly->getNumActiveVoices(); });
    }
    if (!remote.run()) {
        fprintf(stderr, "usage: %s -remote ws://127.0.0.1:<host-port> [-remote-room r] [-remote-token t] [-poly n]\n", argv[0]);
        return 1;
    }

    std::atomic<bool> running(true);
    std::thread audio([&]() {
        const int frames = 64;
        std::vector<std::vector<FAUSTFLOAT> > ins(DSP->getNumInputs(), std::vector<FAUSTFLOAT>(frames, 0));
        std::vector<std::vector<FAUSTFLOAT> > outs(DSP->getNumOutputs(), std::vector<FAUSTFLOAT>(frames, 0));
        std::vector<FAUSTFLOAT*> in, out;
        for (auto& b : ins) in.push_back(b.data());
        for (auto& b : outs) out.push_back(b.data());
        while (running) {
            DSP->compute(frames, in.data(), out.data());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    while (getchar() != EOF) {}
    running = false;
    audio.join();
    remote.stop();
    delete DSP;
    return 0;
}
