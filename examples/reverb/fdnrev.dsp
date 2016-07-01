//##################################### fdnrev.dsp #######################################
// A feedback delay network reverb.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS
// TODO: seems to be broken

import("stdfaust.lib");


//==================================== Static Parameters =================================
//========================================================================================

N = 16; // Feedback Delay Network (FDN) order
NB = 5; // Number of frequency bands / Number of (nearly) independent T60 controls
BBSO =3; // Butterworth band-split order

MAXDELAY = 8192; // sync w delays and prime_power_delays above
defdurs = (8.4,6.5,5.0,3.8,2.7); // NB default durations (sec)
deffreqs = (500,1000,2000,4000); // NB-1 default crossover frequencies (Hz)
deflens = (56.3,63.0); // 2 default min and max path lengths


//==================================== GUI Declaration ===================================
//========================================================================================

fdn_group(x)  = vgroup("FEEDBACK DELAY NETWORK (FDN) REVERBERATOR, ORDER 16
    [tooltip: See Faust's reverb.lib for documentation and references]", x);

freq_group(x)  = fdn_group(vgroup("[1] Band Crossover Frequencies", x));
t60_group(x)  = fdn_group(hgroup("[2] Band Decay Times (T60)", x));
path_group(x)  = fdn_group(vgroup("[3] Room Dimensions", x));
revin_group(x)  = fdn_group(hgroup("[4] Input Controls", x));
nonl_group(x) = revin_group(vgroup("[4] Nonlinearity",x));
quench_group(x) = revin_group(vgroup("[3] Reverb State",x));

nonl = nonl_group(hslider("[style:knob] [tooltip: nonlinear mode coupling]",
            0, -0.999, 0.999, 0.001));
loopgainmax = 1.0-0.5*quench_group(button("[1] Quench
	[tooltip: Hold down 'Quench' to clear the reverberator]"));

pathmin = path_group(hslider("[1] min acoustic ray length [unit:m] [scale:log]
    [tooltip: This length (in meters) determines the shortest delay-line used in the FDN 
    reverberator. Think of it as the shortest wall-to-wall separation in the room.]",
    46, 0.1, 63, 0.1));
pathmax = path_group(hslider("[2] max acoustic ray length [unit:m] [scale:log]
	[tooltip: This length (in meters) determines the longest delay-line used in the 
	FDN reverberator. Think of it as the largest wall-to-wall separation in the room.]",
    63, 0.1, 63, 0.1));

durvals(i) = t60_group(vslider("[%i] %i [unit:s] [scale:log][tooltip: T60 is the 60dB 
	decay-time in seconds. For concert halls, an overall reverberation time (T60) near 
	1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each 
	frequency band.  In real rooms, higher frequency bands generally decay faster due 
	to absorption and scattering.]",ba.take(i+1,defdurs), 0.1, 100, 0.1));
durs = par(i,NB,durvals(NB-1-i));

freqvals(i) = freq_group(hslider("[%i] Band %i upper edge in Hz [unit:Hz] [scale:log]
    [tooltip: Each delay-line signal is split into frequency-bands for separate 
    decay-time control in each band]",ba.take(i+1,deffreqs), 100, 10000, 1));
freqs = par(i,NB-1,freqvals(i));

delays = de.prime_power_delays(N,pathmin,pathmax);

gain = hslider("[3] Output Level (dB) [unit:dB][tooltip: Output scale factor]", 
	-40, -70, 20, 0.1) : ba.db2linear;
     // (can cause infinite loop:) with { db2linear(x) = pow(10, x/20.0); };


//============================================ DSP =======================================
//========================================================================================

process = dm.stereo_reverb_tester(revin_group)
          <: re.fdnrev0(MAXDELAY,delays,BBSO,freqs,durs,loopgainmax,nonl)
          :> *(gain),*(gain);
