//---------------------------------------------------------
// Volume control in dB with MIDI control (CC-1, modWheel)
//---------------------------------------------------------

import("stdfaust.lib");

gain		=  vslider("Volume[midi:ctrl 2] [tooltip CC-1]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo;

process		= _,_: *(gain), *(gain);
