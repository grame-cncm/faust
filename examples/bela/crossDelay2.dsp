import("stdfaust.lib");

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Stereo Delay with feedback and crossfeedback (L to R and R to L feedback).
// And pitch shifting on feedback.
// A pre-delay without feedback is added for a wider stereo effect.
//
// Designed to use the Analog Input for parameters controls.
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// ANALOG IN:
// ANALOG 0	: Pre-Delay L
// ANALOG 1	: Pre-Delay R
// ANALOG 2	: Delay L
// ANALOG 3	: Delay R
// ANALOG 4	: Cross feedback
// ANALOG 5	: Feedback
// ANALOG 6	: Pitchshifter L
// ANALOG 7	: Pitchshifter R
//
// Available by OSC : (see BELA console for precise adress)
// Feedback filter:
// crossLF : Crossfeedback Lowpass
// crossHF : Crossfeedback Highpass
// feedbLF : Feedback Lowpass
// feedbHF : Feedback Highpass
//
///////////////////////////////////////////////////////////////////////////////////////////////////

preDelL	= ba.sec2samp(hslider("preDelL[BELA: ANALOG_0]", 1,0,2,0.001)):si.smoo;
preDelR	= ba.sec2samp(hslider("preDelR[BELA: ANALOG_1]", 1,0,2,0.001)):si.smoo;
delL	= ba.sec2samp(hslider("delL[BELA: ANALOG_2]", 1,0,2,0.001)):si.smoo;
delR	= ba.sec2samp(hslider("delR[BELA: ANALOG_3]", 1,0,2,0.001)):si.smoo;

crossLF	= hslider("crossLF", 12000, 20, 20000, 0.001);
crossHF	= hslider("crossHF", 60, 20, 20000, 0.001);
feedbLF	= hslider("feedbLF", 12000, 20, 20000, 0.001);
feedbHF	= hslider("feedbHF", 60, 20, 20000, 0.001);

CrossFeedb = hslider("CrossFeedb[BELA: ANALOG_4]", 0.0, 0., 1, 0.001):si.smoo;
feedback = hslider("feedback[BELA: ANALOG_5]", 0.0, 0., 1, 0.001):si.smoo;

pitchL = hslider("shiftL[BELA: ANALOG_6]", 0,-12,12,0.001):si.smoo;
pitchR = hslider("shiftR[BELA: ANALOG_7]", 0,-12,12,0.001):si.smoo;

routeur(a,b,c,d) = ((a*CrossFeedb):fi.lowpass(2,crossLF):fi.highpass(2,crossHF))+((b*feedback):fi.lowpass(2,feedbLF):fi.highpass(2,feedbHF))+c,
					((b*CrossFeedb):fi.lowpass(2,crossLF):fi.highpass(2,crossHF))+((a*feedback):fi.lowpass(2,feedbLF):fi.highpass(2,feedbHF))+d;

process = (de.sdelay(65536, 512,preDelL),de.sdelay(65536, 512,preDelR)):(routeur : de.sdelay(65536, 512,delL), de.sdelay(65536, 512,delR))~(ef.transpose(512, 256, pitchL), ef.transpose(512, 256, pitchR));
