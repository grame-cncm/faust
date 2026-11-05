/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

// Check that midi_handler reports the RPN number selected with CC 101/100.
// Only RPN 0 is the pitch bend range: an RPN 2 (coarse tuning) must not be
// delivered as RPN 0, or MidiUI changes the pitch wheel range.

#include <iostream>

#include "faust/midi/midi.h"

struct RpnRecorder : public midi {
    int fCount = 0;
    int fCtrl  = -1;
    int fValue = -1;

    void rpn(double, int, int ctrl, int value) override
    {
        fCount++;
        fCtrl  = ctrl;
        fValue = value;
    }
};

static bool check(int msb, int lsb, int data_msb, int data_lsb)
{
    midi_handler handler;
    RpnRecorder  recorder;
    handler.addMidiIn(&recorder);
    handler.handleData2(0., midi::MIDI_CONTROL_CHANGE, 0, 101, msb);
    handler.handleData2(0., midi::MIDI_CONTROL_CHANGE, 0, 100, lsb);
    handler.handleData2(0., midi::MIDI_CONTROL_CHANGE, 0, 6, data_msb);
    handler.handleData2(0., midi::MIDI_CONTROL_CHANGE, 0, 38, data_lsb);
    int ctrl  = (msb << 7) | lsb;
    int value = (data_msb << 7) | data_lsb;
    if (recorder.fCount != 1 || recorder.fCtrl != ctrl || recorder.fValue != value) {
        std::cerr << "FAIL: RPN " << ctrl << " = " << value << " reported " << recorder.fCount
                  << " time(s) as RPN " << recorder.fCtrl << " = " << recorder.fValue << "\n";
        return false;
    }
    return true;
}

int main()
{
    bool ok = check(0, 0, 2, 0)    // pitch bend range: 2 semitones
              & check(0, 1, 64, 0)  // fine tuning
              & check(0, 2, 66, 0)  // coarse tuning
              & check(1, 3, 5, 7);
    if (ok) std::cout << "PASS rpn-number\n";
    return ok ? 0 : 1;
}
