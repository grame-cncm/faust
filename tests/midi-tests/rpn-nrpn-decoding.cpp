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

// Check how midi_handler decodes RPN and NRPN messages (MidiNRPN):
// - the parameter number selected with CC 101/100 is reported, so an RPN 2
//   (coarse tuning) is not delivered as RPN 0 (pitch bend range);
// - NRPNs (CC 99/98) go to nrpn(), never to rpn();
// - CC 6 alone produces a value (LSB reset to 0), CC 38 then completes it;
// - the selection is kept across data entries, until the RPN null or CC 121;
// - each channel has its own selection;
// - CC 6/38 are ordinary controllers when no parameter is selected.

#include <iostream>
#include <sstream>
#include <string>

#include "faust/midi/midi.h"

struct Recorder : public midi {
    std::ostringstream fLog;

    void rpn(double, int channel, int ctrl, int value) override
    {
        fLog << "rpn(" << channel << "," << ctrl << "," << value << ") ";
    }
    void nrpn(double, int channel, int ctrl, int value) override
    {
        fLog << "nrpn(" << channel << "," << ctrl << "," << value << ") ";
    }
    void ctrlChange(double, int channel, int ctrl, int value) override
    {
        fLog << "cc(" << channel << "," << ctrl << "," << value << ") ";
    }
};

struct Test {
    midi_handler fHandler;
    Recorder     fRecorder;

    Test() { fHandler.addMidiIn(&fRecorder); }

    Test& cc(int ctrl, int value, int channel = 0)
    {
        fHandler.handleData2(0., midi::MIDI_CONTROL_CHANGE, channel, ctrl, value);
        return *this;
    }
};

static int gFailures = 0;

static void expect(const char* name, Test& test, const std::string& expected)
{
    std::string got = test.fRecorder.fLog.str();
    if (got != expected) {
        std::cerr << "FAIL: " << name << "\n  expected: " << expected << "\n  got:      " << got << "\n";
        gFailures++;
    }
}

int main()
{
    {
        Test t;
        t.cc(101, 0).cc(100, 0).cc(6, 2).cc(38, 0);
        expect("RPN 0 (pitch bend range)", t, "rpn(0,0,256) rpn(0,0,256) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 1).cc(6, 64).cc(38, 0);
        expect("RPN 1 (fine tuning)", t, "rpn(0,1,8192) rpn(0,1,8192) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 2).cc(6, 66).cc(38, 0);
        expect("RPN 2 (coarse tuning)", t, "rpn(0,2,8448) rpn(0,2,8448) ");
    }
    {
        Test t;
        t.cc(101, 1).cc(100, 3).cc(6, 5).cc(38, 7);
        expect("RPN 131, 14-bit value", t, "rpn(0,131,640) rpn(0,131,647) ");
    }
    {
        Test t;
        t.cc(99, 0).cc(98, 0).cc(6, 24).cc(38, 0);
        expect("NRPN 0 is not RPN 0", t, "nrpn(0,0,3072) nrpn(0,0,3072) ");
    }
    {
        Test t;
        t.cc(99, 2).cc(98, 5).cc(6, 1).cc(38, 2);
        expect("NRPN 261", t, "nrpn(0,261,128) nrpn(0,261,130) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 0).cc(6, 12);
        expect("data entry MSB only", t, "rpn(0,0,1536) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 0).cc(6, 12).cc(38, 50).cc(6, 3);
        expect("MSB resets the LSB", t, "rpn(0,0,1536) rpn(0,0,1586) rpn(0,0,384) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 0).cc(38, 50);
        expect("LSB before any MSB is ignored", t, "");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 0).cc(6, 2).cc(6, 5).cc(38, 1);
        expect("selection kept across data entries", t, "rpn(0,0,256) rpn(0,0,640) rpn(0,0,641) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 0).cc(6, 2).cc(101, 127).cc(100, 127).cc(6, 5).cc(38, 1);
        expect("RPN null deselects", t, "rpn(0,0,256) cc(0,6,5) cc(0,38,1) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 0).cc(121, 0).cc(6, 5);
        expect("Reset All Controllers deselects", t, "cc(0,121,0) cc(0,6,5) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(98, 0).cc(6, 5);
        expect("RPN MSB + NRPN LSB selects nothing", t, "cc(0,6,5) ");
    }
    {
        Test t;
        t.cc(101, 0).cc(100, 2).cc(6, 5, 1).cc(6, 70);
        expect("selection is per channel", t, "cc(1,6,5) rpn(0,2,8960) ");
    }
    {
        Test t;
        t.cc(6, 10).cc(38, 20).cc(7, 100);
        expect("CC 6/38 without selection", t, "cc(0,6,10) cc(0,38,20) cc(0,7,100) ");
    }

    if (gFailures == 0) {
        std::cout << "PASS rpn-nrpn-decoding\n";
        return 0;
    }
    return 1;
}
