// Created from flange.dsp 2015/06/21

import("pkg:faust/faust/stdfaust.lib@1.0.0");

flanger_mono(dmax,curdel,depth,fb,invert,lfoshape)
  = _ <: _, (-:de.fdelay(dmax,curdel)) ~ *(fb) : _,
  *(select2(invert,depth,0-depth))
  : + : *(1/(1+depth));           // ideal for dc and reinforced sinusoids (in-phase summed signals)


process = ba.bypass1(fbp,flanger_mono_gui);

   // Kill the groups to save vertical space:
   meter_group(x) = flsg(x);
   ctl_group(x)  = flkg(x);
   del_group(x)  = flkg(x);
   lvl_group(x)  = flkf(x);

   flangeview = lfo(freq);

   flanger_mono_gui = attach(flangeview) : flanger_mono(dmax,curdel,depth,fb,invert,lfoshape);

   sinlfo(freq) = (1 + os.oscrs(freq))/2;
   trilfo(freq) = 1.0-abs(os.saw1(freq));
   lfo(f) = (lfoshape * trilfo(f)) + ((1-lfoshape) * sinlfo(f));

   dmax = 2048;
   odflange = 44; // ~1 ms at 44.1 kHz = min delay
   dflange  = ((dmax-1)-odflange)*del_group(vslider("[1] Delay [midi:ctrl 50][style:knob]", 0.22, 0, 1, 1));
   freq     = ctl_group(vslider("[1] Rate [midi:ctrl 2] [unit:Hz] [style:knob]", 0.5, 0, 10, 0.01)) : si.smooth(ba.tau2pole(freqT60/6.91));

   freqT60  = 0.15661;
   depth    = ctl_group(vslider("[3] Depth [midi:ctrl 3] [style:knob]", .75, 0, 1, 0.001)) : si.smooth(ba.tau2pole(depthT60/6.91));

   depthT60 = 0.15661;
   fb       = ctl_group(vslider("[5] Feedback [midi:ctrl 4] [style:knob]", 0, -0.995, 0.99, 0.001)) : si.smooth(ba.tau2pole(fbT60/6.91));

   fbT60    = 0.15661;
   lfoshape = ctl_group(vslider("[7] Waveshape [midi:ctrl 54] [style:knob]", 0, 0, 1, 0.001));
   curdel   = odflange+dflange*lfo(freq);

   fbp = 1-int(flsg(vslider("[0] Enable [midi:ctrl 105][style:knob]",0,0,1,1)));

   invert = flsg(vslider("[1] Invert [midi:ctrl 49][style:knob]",0,0,1,1):int);

// This layout loosely follows the MiniMoog-V
// Arturia-only features are labeled
// Original versions also added where different

// Need vrocker and hrocker toggle switches in Faust!
// Need orange and blue color choices
//   Orange => Connect modulation sources to their destinations
//    Blue  => Turn audio sources On and Off
// - and later -
//   White  => Turn performance features On and Off
//   Black  => Select between modulation sources
//   Julius Smith for Analog Devices 3/1/2017

vrocker(x) = checkbox("%%x [style:vrocker]");
hrocker(x) = checkbox("%%x [style:hrocker]");
vrockerblue(x) = checkbox("%x  [style:vrocker] [color:blue]");
vrockerblue(x) = checkbox("%x [style:vrocker] [color:blue]");
 // USAGE: vrockerorange("[0] ModulationEnable");

hrockerblue(x) = checkbox("%%x [style:hrocker] [color:blue]");
vrockerred(x) = checkbox("%%x [style:vrocker] [color:red]");
hrockerred(x) = checkbox("%%x [style:hrocker] [color:red]");

declare designer "Robert A. Moog";

mmg(x) = hgroup("",x); // Minimoog + Effects
  synthg(x) = mmg(vgroup("[0] Minimoog",x));
  fxg(x) = mmg(hgroup("[1] Effects",x));
  mg(x) = synthg(hgroup("[0]",x));
    cg(x) = mg(vgroup("[0] Controllers",x)); // Formerly named "Modules" but "Minimoog" group-title is enough
      vg(x) = cg(hgroup("[0] Master Volume", x));
      dg(x) = cg(hgroup("[1] Oscillator Tuning & Switching", x));
        // Tune knob = master tune
        dsg(x) = dg(vgroup("[1] Switches", x));
	  // Oscillator Modulation HrockerRed => apply Modulation Mix output to osc1&2 pitches
	  // [MOVED here from osc3 group] Osc 3 Control VrockerRed => use osc3 as LFO instead of osc3
      gmmg(x) = cg(hgroup("[2] Glide and ModMix", x));
        // Glide knob [0:10] = portamento speed
        // Modulation Mix knob [0:10] (between Osc3 and Noise) = mix of noise and osc3 modulating osc1&2 pitch and/or VCF freq
    og(x) = mg(vgroup("[1] Oscillator Bank", x));
      osc1(x) = og(hgroup("[1] Oscillator 1", x));
        // UNUSED Control switch (for alignment) - Could put Oscillator Modulation switch there
        // Range rotary switch: LO (slow pulses or rhythm), 32', 16', 8', 4', 2'
        // Frequency <something> switch: LED to right
        // Waveform rotary switch: tri, impulse/bent-triangle, saw, pulseWide, pulseMed, pulseNarrow
      osc2(x) = og(hgroup("[2] Oscillator 2", x));
        // UNUSED (originall) or Osc 2 Control VrockerRed
        // Range rotary switch: LO, 32', 16', 8', 4', 2'
        // Detuning knob: -7 to 7 [NO SWITCH]
        // Waveform rotary switch: tri, impulse(?), saw, pulseWide, pulseMed, pulseNarrow
      osc3(x) = og(hgroup("[3] Oscillator 3", x));
        // Osc 3 Control VrockerRed => use osc3 as LFO instead of osc3
        // Range rotary switch: LO, 32', 16', 8', 4', 2'
        // Detuning knob: -7 to 7 [NO SWITCH]
        // Waveform rotary switch: tri, impulse(?), saw, pulseWide, pulseMed, pulseNarrow
    mixg(x) = mg(vgroup("[2] Mixer", x));
      // Each row 5 slots to maintain alignment and include red rockers joining VCF area:
      mr1(x) = mixg(hgroup("[0] Osc1", x)); // mixer row 1 =
      // Osc1 Volume and Osc1 HrockerBlue & _ & _ & Filter Modulation HrockerRed
      // Filter Modulation => Modulation Mix output to VCF freq
      mr2(x) = mixg(hgroup("[1] Ext In, KeyCtl", x)); // row 2 = Ext In HrockerBlue and Vol and Overload LED and Keyboard Ctl HrockerRed 1
      mr3(x) = mixg(hgroup("[2] Osc2", x)); // = Osc2 Volume and Osc2 HrockerBlue and Keyboard Ctl HrockerRed 2
      // Keyboard Control Modulation 1&2 => 0, 1/3, 2/3, all of Keyboard Control Signal ("gate?") applied to VCF freq
      mr4(x) = mixg(hgroup("[3] Noise", x)); // = Noise HrockerBlue and Volume and Noise Type VrockerBlue
        mr4cbg(x) = mr4(vgroup("[1]", x)); // = Noise Off and White/Pink selection
	// two rockers
      mr5(x) = mixg(hgroup("[4] Osc3", x)); //  Osc3 Volume and Osc3 HrockerBlue
    modg(x) = mg(vgroup("[3] Modifiers", x));
      vcfg(x) = modg(vgroup("[0] Filter", x));
        vcf1(x) = vcfg(hgroup("[0] [tooltip:freq, Q, ContourScale]", x));
	  vcf1cbg(x) = vcf1(vgroup("[0] [tooltip:two checkboxes]", x));
          // Filter Modulation switch
          // VCF Off switch
        // Corner Frequency knob
        // Filter Emphasis knob
        // Amount of Contour knob
        vcf2(x) = vcfg(hgroup("[1] Filter Contour [tooltip:AttFilt, DecFilt, Sustain Level for Filter Contour]", x));
        // Attack Time knob
        // Decay Time knob
        // Sustain Level knob
      ng(x) = modg(hgroup("[1] Loudness Contour", x));
        // Attack Time knob
        // Decay Time knob
        // Sustain Level knob
    echog(x) = fxg(hgroup("[4] Echo",x));
      ekg(x) = echog(vgroup("[0] Knobs",x));
      esg(x) = echog(vgroup("[1] Switches",x));
    flg(x) = fxg(hgroup("[5] Flanger",x));
      flkg(x) = flg(vgroup("[0] Knobs",x));
      flsg(x) = flg(vgroup("[1] Switches",x));
    chg(x) = fxg(hgroup("[6] Chorus",x));
      ckg(x) = chg(vgroup("[0] Knobs",x));
      csg(x) = chg(vgroup("[1] Switches",x));
    rg(x) = fxg(hgroup("[7] Reverb",x));
      rkg(x) = rg(vgroup("[0] Knobs",x));
      rsg(x) = rg(vgroup("[1] Switches",x));
    outg(x) = fxg(vgroup("[8] Output", x));
      volg(x) = outg(hgroup("[0] Volume Main Output", x));
        // Volume knob [0-10]
	// Unison switch (Arturia) or Output connect/disconnect switch (original)
	//   When set, all voices are stacked and instrument is in mono mode
      tunerg(x) = outg(hgroup("[1] A-440 Switch", x));
      vdtpolyg(x) = outg(hgroup("[2] Voice Detune / Poly", x));
        // Voice Detune knob [0-10] (Arturia) or
	// Polyphonic switch [red LED below] (Arturia)
	//   When set, instrument is in polyphonic mode with one oscillator per key
    clipg(x) = fxg(vgroup("[9] Soft Clip", x));
	// Soft Clipping switch [red LED above]
  kg(x) = synthg(hgroup("[1] Keyboard Group", x)); // Keyboard was 3 1/2 octaves
    ws(x) = kg(vgroup("[0] Wheels and Switches", x));
      s1g(x) = ws(hgroup("[0] Jacks and Rockers", x));
        jg(x) = s1g(vgroup("[0] MiniJacks",x));
        gdlg(x) = s1g(vgroup("[1] Glide/Decay/Legato Enables",x)); // Arturia
	// Glide Hrocker (see original Button version below)
	// Decay Hrocker (see original Button version below) => Sets Release (R) of ADSR to either 0 or Decay (R)
	// Legato Hrocker (not in original)
      s2g(x) = ws(hgroup("[1] [tooltip:Wheels+]", x));
        bg(x) = s2g(vgroup("[0] [tooltip:Bend Enable and Range]", x));
        wg(x) = s2g(hgroup("[1] [tooltip:Bend and Mod Wheels]", x));
	// Using Glide/Decay/Legato enables above following Arturia:
	//   dg(x) = s2g(hgroup("[2] Glide and Decay momentary pushbuttons", x));
	//   Glide Button injects portamento as set by Glide knob
	//   Decay Button uses decay of Loudness Contour (else 0)
    keys(x) = kg(hgroup("[1] [tooltip:Keys]", x));
      gg(x) = keys(hgroup("[0] [tooltip: Gates]",x));
      // leave slot 1 open for sustain (below)
