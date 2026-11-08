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

// Checks that the index based accessors of MapUI designate the same control
// for the same index: getParamAddress, getParamAddress1, getParamShortname,
// getParamShortname1, getParamLabel, getParamLabel1 and getParamZone.
// The UI is built by hand, as buildUserInterface would do: controls are declared
// in an order that differs from the order of their paths, of their shortnames
// and of their labels, and one label is used in two groups.

#include <cstdio>
#include <cstring>
#include <map>
#include <string>

#include "faust/gui/MapUI.h"

static int gErrors = 0;

static void check(bool cond, int index, const char* what)
{
    if (!cond) {
        std::printf("FAIL index %d: %s\n", index, what);
        gErrors++;
    }
}

int main()
{
    FAUSTFLOAT zones[8] = {};
    std::map<FAUSTFLOAT*, std::string> labels;  // declared label of each zone
    MapUI ui;

    auto slider = [&](const char* label, int i) {
        labels[&zones[i]] = label;
        ui.addHorizontalSlider(label, &zones[i], 0, 0, 1, 0.1);
    };

    ui.openVerticalBox("X");
    ui.openHorizontalBox("Filter");
    slider("Frequency", 0);
    slider("Resonance", 1);
    ui.closeBox();
    ui.openHorizontalBox("Modulation");
    slider("CV offset", 2);
    slider("V-oct trim", 3);
    slider("Gain", 4);
    ui.closeBox();
    ui.openHorizontalBox("Signal");
    slider("Input level", 5);
    slider("Gain", 6);  // same label as in 'Modulation'
    ui.closeBox();
    ui.closeBox();

    int count = ui.getParamsCount();
    if (count != 7) {
        std::printf("FAIL getParamsCount: %d instead of 7\n", count);
        return 1;
    }

    for (int i = 0; i < count; i++) {
        FAUSTFLOAT* zone = ui.getParamZone(i);
        std::string address = ui.getParamAddress(i);
        std::string shortname = ui.getParamShortname(i);
        std::string label = ui.getParamLabel(i);
        std::printf("%d: %s -> %s, '%s'\n", i, address.c_str(), shortname.c_str(), label.c_str());

        check(zone != nullptr, i, "getParamZone(int) is null");
        check(ui.getParamZone(address) == zone, i, "getParamAddress does not designate getParamZone(int)");
        check(ui.getParamAddress1(i) && address == ui.getParamAddress1(i), i, "getParamAddress1 differs from getParamAddress");
        check(!shortname.empty() && ui.getParamZone(shortname) == zone, i, "getParamShortname does not designate getParamZone(int)");
        check(ui.getParamShortname1(i) && shortname == ui.getParamShortname1(i), i, "getParamShortname1 differs from getParamShortname");
        check(labels.count(zone) && label == labels[zone], i, "getParamLabel is not the label of getParamZone(int)");
        check(ui.getParamLabel1(i) && label == ui.getParamLabel1(i), i, "getParamLabel1 differs from getParamLabel");
    }

    // Out of range indexes
    check(ui.getParamAddress(count) == "" && ui.getParamAddress1(-1) == nullptr, count, "address out of range");
    check(ui.getParamShortname(count) == "" && ui.getParamShortname1(-1) == nullptr, count, "shortname out of range");
    check(ui.getParamLabel(count) == "" && ui.getParamLabel1(-1) == nullptr, count, "label out of range");
    check(ui.getParamZone(count) == nullptr, count, "zone out of range");

    std::printf("%s: %d controls, %d errors\n", (gErrors == 0) ? "PASS" : "FAIL", count, gErrors);
    return (gErrors == 0) ? 0 : 1;
}
