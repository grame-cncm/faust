import("stdfaust.lib");

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Additive synthesizer, must be used with OSC message to program sound.
// It as 8 harmonics. Each have it's own volume envelop.
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// OSC messages (see BELA console for precise adress)
// For each harmonics (%rang indicate harmonic number, starting at 0) :
// vol%rang	: General Volume (vol0 control the volume of the fundamental)
// A%rang : Attack
// D%rang : Decay
// S%rang : Sustain
// R%rang : Release
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// GENERAL
midigate = button("gate");
midifreq = nentry("freq[unit:Hz]", 440, 20, 20000, 1);
midigain = nentry("gain", 0.5, 0, 10, 0.01);

// pitchwheel
bend = ba.semi2ratio(hslider("bend [midi:pitchwheel]",0,-2,2,0.01));

gFreq = midifreq * bend;

partiel(rang) = os.oscrs(gFreq*(rang+1))*volume
    with {
        // UI
        vol	= hslider("vol%rang", 1, 0, 1, 0.001);
     
        a = 0.01 * hslider("A%rang", 1, 0, 400, 0.001);
        d = 0.01 * hslider("D%rang", 1, 0, 400, 0.001);
        s = hslider("S%rang", 1, 0, 1, 0.001);
        r = 0.01 * hslider("R%rang", 1, 0, 800, 0.001);

        volume = ((en.adsr(a,d,s,r,midigate))*vol) : max(0) : min(1);
    };

process = par(i, 8, partiel(i)) :> /(8);
