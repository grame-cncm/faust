# Standard Functions

Dozens of functions are implemented in the Faust libraries and many of them are very specialized and not useful to beginners or to people who only need to use Faust for basic applications. This section offers an index organized by categories of the "standard Faust functions" (basic filters, effects, synthesizers, etc.). This index only contains functions without a user interface (UI). Faust functions with a built-in UI can be found in [`demos.lib`](#demos.lib).


## Analysis Tools

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Amplitude Follower](#an.amp_follower) | [`an.`](#analysis.lib)[`amp_follower`](#an.amp_follower) | Classic analog audio envelope follower
[Octave Analyzers](#an.mth_octave_analyzer) | [`an.`](#analysis.lib)[`mth_octave_analyzer[N]`](#an.mth_octave_analyzer) | Octave analyzers

<div class="table-end"></div>


## Basic Elements

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Beats](#ba.beat) | [`ba.`](#basics.lib)[`beat`](#ba.beat) | Pulses at a specific tempo
[Block](#si.block) | [`si.`](#signals.lib)[`block`](#si.block) | Terminate n signals
[Break Point Function](#ba.bpf) | [`ba.`](#basics.lib)[`bpf`](#ba.bpf) | Beak Point Function (BPF)
[Bus](#si.bus) | [`si.`](#signals.lib)[`bus`](#si.bus) | Bus of n signals
[Bypass (Mono)](#ba.bypass1) | [`ba.`](#basics.lib)[`bypass1`](#ba.bypass1) | Mono bypass
[Bypass (Stereo)](#ba.bypass2) | [`ba.`](#basics.lib)[`bypass2`](#ba.bypass2) | Stereo bypass
[Count Elements](#ba.count) | [`ba.`](#basics.lib)[`count`](#ba.count) | Count elements in a list
[Count Down](#ba.countdown) | [`ba.`](#basics.lib)[`countdown`](#ba.countdown) | Samples count down
[Count Up](#ba.countup) | [`ba.`](#basics.lib)[`countup`](#ba.countup) | Samples count up
[Delay (Integer)](#de.delay) | [`de.`](#delays.lib)[`delay`](#de.delay) | Integer delay
[Delay (Float)](#de.fdelay) | [`de.`](#delays.lib)[`fdelay`](#de.fdelay) | Fractional delay
[Down Sample](#ba.downsample) | [`ba.`](#basics.lib)[`downSample`](#ba.downsample) | Down sample a signal
[Impulsify](#ba.impulsify) | [`ba.`](#basics.lib)[`impulsify`](#ba.impulsify) | Turns a signal into an impulse
[Sample and Hold](#ba.sandh) | [`ba.`](#basics.lib)[`sAndH`](#ba.sandh) | Sample and hold
[Signal Crossing](#ro.cross) | [`ro.`](#routes.lib)[`cross`](#ro.cross) | Cross n signals
[Smoother (Default)](#si.smoo) | [`si.`](#signals.lib)[`smoo`](#si.smoo) | Exponential smoothing
[Smoother](#si.smooth) | [`si.`](#signals.lib)[`smooth`](#si.smooth) | Exponential smoothing with controllable pole
[Take Element](#ba.take) | [`ba.`](#basics.lib)[`take`](#ba.take) | Take en element from a list
[Time](#ba.time) | [`ba.`](#basics.lib)[`time`](#ba.time) | A simple timer

<div class="table-end"></div>


## Conversion

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[dB to Linear](#ba.db2linear) | [`ba.`](#basics.lib)[`db2linear`](#ba.db2linear) | Converts dB to linear values
[Linear to dB](#ba.linear2db) | [`ba.`](#basics.lib)[`linear2db`](#ba.linear2db) | Converts linear values to dB
[MIDI Key to Hz](#ba.midikey2hz) | [`ba.`](#basics.lib)[`midikey2hz`](#ba.midikey2hz) | Converts a MIDI key number into a frequency
[Hz to MIDI Key](#ba.hz2midikey) | [`ba.`](#basics.lib)[`hz2midikey`](#ba.hz2midikey) | Converts a frequency into MIDI key number
[Pole to T60](#ba.pole2tau) | [`ba.`](#basics.lib)[`pole2tau`](#ba.pole2tau) | Converts a pole into a time constant (t60)
[Samples to Seconds](#ba.samp2sec) | [`ba.`](#basics.lib)[`samp2sec`](#ba.samp2sec) | Converts samples to seconds
[Seconds to Samples](#ba.sec2samp) | [`ba.`](#basics.lib)[`sec2samp`](#ba.sec2samp) | Converts seconds to samples
[T60 to Pole](#ba.tau2pole) | [`ba.`](#basics.lib)[`tau2pole`](#ba.tau2pole) | Converts a time constant (t60) into a pole

<div class="table-end"></div>


## Effects

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Auto Wah](#ve.autowah) | [`ve.`](#vaeffects.lib)[`autowah`](#ve.autowah) | Auto-Wah effect
[Compressor](#co.compressor_mono) | [`co.`](#compressors.lib)[`compressor_mono`](#co.compressor_mono) | Dynamic range compressor
[Distortion](#ef.cubicnl) | [`ef.`](#misceffects.lib)[`cubicnl`](#ef.cubicnl) | Cubic nonlinearity distortion
[Crybaby](#ve.crybaby) | [`ve.`](#vaeffects.lib)[`crybaby`](#ve.crybaby) | Crybaby wah pedal
[Echo](#ef.echo) | [`ef.`](#misceffects.lib)[`echo`](#ef.echo) | Simple echo
[Flanger](#pf.flanger_stereo) | [`pf.`](#phaflangers.lib)[`flanger_stereo`](#pf.flanger_stereo) | Flanging effect
[Gate](#ef.gate_mono) | [`ef.`](#misceffects.lib)[`gate_mono`](#ef.gate_mono) | Mono signal gate
[Limiter](#co.limiter_1176_R4_mono) | [`co.`](#compressors.lib)[`limiter_1176_R4_mono`](#co.limiter_1176_R4_mono) | Limiter
[Phaser](#pf.phaser2_stereo) | [`pf.`](#phaflangers.lib)[`phaser2_stereo`](#pf.phaser2_stereo) | Phaser effect
[Reverb (FDN)](#re.fdnrev0) | [`re.`](#reverbs.lib)[`fdnrev0`](#re.fdnrev0) | Feedback delay network reverberator
[Reverb (Freeverb)](#re.mono_freeverb) | [`re.`](#reverbs.lib)[`mono_freeverb`](#re.mono_freeverb) | Most "famous" Schroeder reverberator
[Reverb (Simple)](#re.jcrev) | [`re.`](#reverbs.lib)[`jcrev`](#re.jcrev) | Simple Schroeder reverberator
[Reverb (Zita)](#re.zita_rev1_stereo) | [`re.`](#reverbs.lib)[`zita_rev1_stereo`](#re.zita_rev1_stereo) | High quality FDN reverberator
[Panner](#sp.panner) | [`sp.`](#spats.lib)[`panner`](#sp.panner) | Linear stereo panner
[Pitch Shift](#ef.transpose) | [`ef.`](#misceffects.lib)[`transpose`](#ef.transpose) | Simple pitch shifter
[Panner](#sp.spat) | [`sp.`](#spats.lib)[`spat`](#sp.spat) | N outputs spatializer
[Speaker Simulator](#ef.speakerbp) | [`ef.`](#misceffects.lib)[`speakerbp`](#ef.speakerbp) | Simple speaker simulator
[Stereo Width](#ef.stereo_width) | [`ef.`](#misceffects.lib)[`stereo_width`](#ef.stereo_width) | Stereo width effect
[Vocoder](#ve.vocoder) | [`ve.`](#vaeffects.lib)[`vocoder`](#ve.vocoder) | Simple vocoder
[Wah](#ve.wah4) | [`ve.`](#vaeffects.lib)[`wah4`](#ve.wah4) | Wah effect

<div class="table-end"></div>


## Envelope Generators

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[ADSR](#en.asr) | [`en.`](#envelopes.lib)[`adsr`](#en.adsr) | Attack/Decay/Sustain/Release envelope generator
[AR](#en.ar) | [`en.`](#envelopes.lib)[`ar`](#en.ar) | Attack/Release envelope generator
[ASR](#en.asr) | [`en.`](#envelopes.lib)[`asr`](#en.asr) | Attack/Sustain/Release envelope generator
[Exponential](#en.smoothEvelope) | [`en.`](#envelopes.lib)[`smoothEnvelope`](#en.smoothEnvelope) | Exponential envelope generator

<div class="table-end"></div>


## Filters

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Bandpass (Butterworth)](#fi.bandpass) | [`fi.`](#filters.lib)[`bandpass`](#fi.bandpass) | Generic butterworth bandpass
[Bandpass (Resonant)](#fi.resonbp) | [`fi.`](#filters.lib)[`resonbp`](#fi.resonbp) | Virtual analog resonant bandpass
[Bandstop (Butterworth)](#fi.bandstop) | [`fi.`](#filters.lib)[`bandstop`](#fi.bandstop) | Generic butterworth bandstop
[Biquad](#fi.tf2) | [`fi.`](#filters.lib)[`tf2`](#fi.tf2) | "Standard" biquad filter
[Comb (Allpass)](#fi.allpass_fcomb) | [`fi.`](#filters.lib)[`allpass_fcomb`](#fi.allpass_fcomb) | Schroeder allpass comb filter
[Comb (Feedback)](#fi.fb_fcomb) | [`fi.`](#filters.lib)[`fb_fcomb`](#fi.fb_fcomb) | Feedback comb filter
[Comb (Feedforward)](#fi.ff_fcomb) | [`fi.`](#filters.lib)[`ff_fcomb`](#fi.ff_fcomb) | Feed-forward comb filter.
[DC Blocker](#fi.dcblocker) | [`fi.`](#filters.lib)[`dcblocker`](#fi.dcblocker) | Default dc blocker
[Filterbank](#fi.filterbank) | [`fi.`](#filters.lib)[`filterbank`](#fi.filterbank) | Generic filter bank
[FIR (Arbitrary Order)](#fi.fir) | [`fi.`](#filters.lib)[`fir`](#fi.fir) | Nth-order FIR filter
[High Shelf](#fi.high_shelf) | [`fi.`](#filters.lib)[`high_shelf`](#fi.high_shelf) | High shelf
[Highpass (Butterworth)](#fi.highpass) | [`fi.`](#filters.lib)[`highpass`](#fi.highpass) | Nth-order Butterworth highpass
[Highpass (Resonant)](#fi.resonhp) | [`fi.`](#filters.lib)[`resonhp`](#fi.resonhp) | Virtual analog resonant highpass
[IIR (Arbitrary Order)](#fi.iir) | [`fi.`](#filters.lib)[`iir`](#fi.iir) | Nth-order IIR filter
[Level Filter](#fi.levelfilter) | [`fi.`](#filters.lib)[`levelfilter`](#fi.levelfilter) | Dynamic level lowpass
[Low Shelf](#fi.low_shelf) | [`fi.`](#filters.lib)[`low_shelf`](#fi.low_shelf) | Low shelf
[Lowpass (Butterworth)](#fi.lowpass) | [`fi.`](#filters.lib)[`lowpass`](#fi.lowpass) | Nth-order Butterworth lowpass
[Lowpass (Resonant)](#fi.resonlp) | [`fi.`](#filters.lib)[`resonlp`](#fi.resonlp) | Virtual analog resonant lowpass
[Notch Filter](#fi.notchw) | [`fi.`](#filters.lib)[`notchw`](#fi.notchw) | Simple notch filter
[Peak Equalizer](#fi.peak_eq) | [`fi.`](#filters.lib)[`peak_eq`](#fi.peak_eq) | Peaking equalizer section

<div class="table-end"></div>


## Oscillators/Sound Generators

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Impulse](#os.impulse) | [`os.`](#oscillators.lib)[`impulse`](#os.impulse) | Generate an impulse on start-up
[Impulse Train](#os.imptrain) | [`os.`](#oscillators.lib)[`imptrain`](#os.imptrain) | Band-limited impulse train
[Phasor](#os.phasor) | [`os.`](#oscillators.lib)[`phasor`](#os.phasor) | Simple phasor
[Pink Noise](#no.pink_noise) | [`no.`](#noises.lib)[`pink_noise`](#no.pink_noise) | Pink noise generator
[Pulse Train](#os.pulsetrain) | [`os.`](#oscillators.lib)[`pulsetrain`](#os.pulsetrain) | Band-limited pulse train
[Pulse Train (Low Frequency)](#os.lf_imptrain) | [`os.`](#oscillators.lib)[`lf_imptrain`](#os.lf_imptrain) | Low-frequency pulse train
[Sawtooth](#os.sawtooth) | [`os.`](#oscillators.lib)[`sawtooth`](#os.sawtooth) | Band-limited sawtooth wave
[Sawtooth (Low Frequency)](#os.lf_saw) | [`os.`](#oscillators.lib)[`lf_saw`](#os.lf_saw) | Low-frequency sawtooth wave
[Sine (Filter-Based)](#os.osc) | [`os.`](#oscillators.lib)[`osc`](#os.osc) | Sine oscillator (filter-based)
[Sine (Table-Based)](#os.oscsin) | [`os.`](#oscillators.lib)[`oscsin`](#os.oscsin) | Sine oscillator (table-based)
[Square](#os.square) | [`os.`](#oscillators.lib)[`square`](#os.square) | Band-limited square wave
[Square (Low Frequency)](#os.lf_squarewave) | [`os.`](#oscillators.lib)[`lf_squarewave`](#os.lf_squarewave) | Low-frequency square wave
[Triangle](#os.triangle) | [`os.`](#oscillators.lib)[`triangle`](#os.triangle) | Band-limited triangle wave
[Triangle (Low Frequency)](#os.lf_triangle) | [`os.`](#oscillators.lib)[`lf_triangle`](#os.lf_triangle) | Low-frequency triangle wave
[White Noise](#no.noise) | [`no.`](#noises.lib)[`noise`](#no.noise) | White noise generator

<div class="table-end"></div>


## Synths

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Additive Drum](#sy.additivedrum) | [`sy.`](#synths.lib)[`additiveDrum`](#sy.additivedrum) | Additive synthesis drum
[Bandpassed Sawtooth](#sy.dubdub) | [`sy.`](#synths.lib)[`dubDub`](#sy.dubdub) | Sawtooth through resonant bandpass
[Comb String](#sy.combstring) | [`sy.`](#synths.lib)[`combString`](#sy.combstring) | String model based on a comb filter
[FM](#sy.fm) | [`sy.`](#synths.lib)[`fm`](#sy.fm) | Frequency modulation synthesizer
[Lowpassed Sawtooth](#sy.sawtrombone) | [`sy.`](#synths.lib)[`sawTrombone`](#sy.sawtrombone) | "Trombone" based on a filtered sawtooth
[Popping Filter](#sy.popfilterperc) | [`sy.`](#synths.lib)[`popFilterPerc`](#sy.popfilterperc) | Popping filter percussion instrument

<div class="table-end"></div>


<!--
TODO: potentially say something about demos.lib and demo functions here. Also, not sure what to do with math.lib.
-->

<script type="text/javascript">
(function() {
    $('div.table-begin').nextUntil('div.table-end', 'table').addClass('table table-bordered');
	})();
</script>
