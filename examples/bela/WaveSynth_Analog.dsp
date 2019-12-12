import("stdfaust.lib");

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Simple demo of wavetable synthesis. A LFO modulate the interpolation between 4 tables.
// It's possible to add more tables step.
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// ANALOG IMPLEMENTATION:
//
// ANALOG_0	: Wave travelling
// ANALOG_1	: LFO Frequency
// ANALOG_2	: LFO Depth (wave travel modulation)
// ANALOG_3	: Release
//
// MIDI:
// CC 73 : Attack
// CC 76 : Decay
// CC 77 : Sustain
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// GENERAL
midigate = button("gate");
midifreq = nentry("freq[unit:Hz]", 440, 20, 20000, 1);
midigain = nentry("gain", 0.5, 0, 1, 0.01);

waveTravel = hslider("waveTravel[BELA: ANALOG_0]",0,0,1,0.01);

// pitchwheel
bend = ba.semi2ratio(hslider("bend [midi:pitchwheel]",0,-2,2,0.01));

gFreq = midifreq * bend;

// LFO
lfoDepth = hslider("lfoDepth[BELA: ANALOG_2]",0,0.,1,0.001):si.smoo;
lfoFreq = hslider("lfoFreq[BELA: ANALOG_1]",0.1,0.01,10,0.001):si.smoo;
moov = ((os.lf_trianglepos(lfoFreq) * lfoDepth) + waveTravel) : min(1) : max(0);

volA = hslider("A[midi:ctrl 73]",0.01,0.01,4,0.01);
volD = hslider("D[midi:ctrl 76]",0.6,0.01,8,0.01);
volS = hslider("S[midi:ctrl 77]",0.2,0,1,0.01);
volR = hslider("R[BELA: ANALOG_3]",0.8,0.01,8,0.01);
envelop = en.adsre(volA,volD,volS,volR,midigate);

// Out amplitude
vol = envelop * midigain;

WF(tablesize, rang) = abs((fmod((1+(float(ba.time)*rang)/float(tablesize)), 4.0))-2) -1.;

// 4 WF maxi with this version:
scanner(nb, position) = -(_,soustraction) : *(_,coef) : cos : max(0)
    with {
        coef = 3.14159 * ((nb-1)*0.5);
        soustraction = select2( position>0, 0, (position/(nb-1)) );
    };

wfosc(freq) = (rdtable(tablesize, wt1, faze)*(moov : scanner(4,0)))+(rdtable(tablesize, wt2, faze)*(moov : scanner(4,1)))
            + (rdtable(tablesize, wt3, faze)*(moov : scanner(4,2)))+(rdtable(tablesize, wt4, faze)*(moov : scanner(4,3)))
    with {
        tablesize = 1024;
        wt1 = WF(tablesize, 16);
        wt2 = WF(tablesize, 8);
        wt3 = WF(tablesize, 6);
        wt4 = WF(tablesize, 4);
        faze = int(os.phasor(tablesize,freq));
    };

process = wfosc(gFreq) * vol;

