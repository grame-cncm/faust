//##################################### phaser.dsp #######################################
// Phaser demo application.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

phaser2_group(x) = vgroup("PHASER2 [tooltip: Reference: 
	https://ccrma.stanford.edu/~jos/pasp/Flanging.html]", x);
meter_group(x) = phaser2_group(hgroup("[0]", x));
ctl_group(x)  = phaser2_group(hgroup("[1]", x));
nch_group(x)  = phaser2_group(hgroup("[2]", x));
lvl_group(x)  = phaser2_group(hgroup("[3]", x));

pbp = meter_group(checkbox("[0] Bypass  [tooltip: When this is checked, the phaser 
	has no effect]"));
invert = meter_group(checkbox("[1] Invert Internal Phaser Sum"));
vibr = meter_group(checkbox("[2] Vibrato Mode")); // In this mode you can hear any "Doppler"

// FIXME: This should be an amplitude-response display:
// flangeview = phaser2_amp_resp : meter_group(hspectrumview("[2] Phaser Amplitude Response", 0,1));
// phaser2_stereo_demo(x,y) = attach(x,flangeview),y : ...

phaser2_stereo_demo = *(level),*(level) :
	ef.phaser2_stereo(Notches,width,frqmin,fratio,frqmax,speed,mdepth,fb,invert);

Notches = 4; // Compile-time parameter: 2 is typical for analog phaser stomp-boxes

// FIXME: Add tooltips
speed  = ctl_group(hslider("[1] Speed [unit:Hz] [style:knob]", 0.5, 0, 10, 0.001));
depth  = ctl_group(hslider("[2] Notch Depth (Intensity) [style:knob]", 1, 0, 1, 0.001));
fb     = ctl_group(hslider("[3] Feedback Gain [style:knob]", 0, -0.999, 0.999, 0.001));

width  = nch_group(hslider("[1] Notch width [unit:Hz] [style:knob] [scale:log]", 
	1000, 10, 5000, 1));
frqmin = nch_group(hslider("[2] Min Notch1 Freq [unit:Hz] [style:knob] [scale:log]", 
	100, 20, 5000, 1));
frqmax = nch_group(hslider("[3] Max Notch1 Freq [unit:Hz] [style:knob] [scale:log]", 
	800, 20, 10000, 1)) : max(frqmin);
fratio = nch_group(hslider("[4] Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n) [style:knob]", 
	1.5, 1.1, 4, 0.001));

level  = lvl_group(hslider("Phaser Output Level [unit:dB]", 0, -60, 10, 0.1)) : 
	ba.db2linear;

mdepth = select2(vibr,depth,2); // Improve "ease of use"

process = ba.bypass2(pbp,phaser2_stereo_demo);