# Standard Functions

Dozens of functions are implemented in the Faust libraries and many of them are very specialized and not useful to beginners or to people who only need to use Faust for basic applications. This section offers an index organized by categories of the "standard Faust functions" (basic filters, effects, synthesizers, etc.). This index only contains functions without a user interface (UI). Faust functions with a built-in UI can be found in [`demos.lib`](#demos.lib).


## Analysis Tools

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Amplitude Follower](#amp_follower) | [`an.`](#analysis.lib)[`amp_follower`](#amp_follower) | Classic analog audio envelope follower
[Octave Analyzers](#mth_octave_analyzer) | [`an.`](#analysis.lib)[`mth_octave_analyzer[N]`](#mth_octave_analyzer) | Octave analyzers

<div class="table-end"></div>


## Basic Elements

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Beats](#beat) | [`ba.`](#basics.lib)[`beat`](#beat) | Pulses at a specific tempo
[Block](#block) | [`si.`](#signals.lib)[`block`](#block) | Terminate n signals
[Break Point Function](#bpf) | [`ba.`](#basics.lib)[`bpf`](#bpf) | Beak Point Function (BPF)
[Bus](#bus) | [`si.`](#signals.lib)[`bus`](#bus) | Bus of n signals
[Bypass (Mono)](#bypass1) | [`ba.`](#basics.lib)[`bypass1`](#bypass1) | Mono bypass
[Bypass (Stereo)](#bypass2) | [`ba.`](#basics.lib)[`bypass2`](#bypass2) | Stereo bypass
[Count Elements](#count) | [`ba.`](#basics.lib)[`count`](#count) | Count elements in a list
[Count Down](#countdown) | [`ba.`](#basics.lib)[`countdown`](#countdown) | Samples count down
[Count Up](#countup) | [`ba.`](#basics.lib)[`countup`](#countup) | Samples count up
[Delay (Integer)](#delay) | [`de.`](#delays.lib)[`delay`](#delay) | Integer delay
[Delay (Float)](#fdelay) | [`de.`](#delays.lib)[`fdelay`](#fdelay) | Fractional delay
[Down Sample](#downsample) | [`ba.`](#basics.lib)[`downSample`](#downsample) | Down sample a signal
[Impulsify](#impulsify) | [`ba.`](#basics.lib)[`impulsify`](#impulsify) | Turns a signal into an impulse
[Sample and Hold](#sandh) | [`ba.`](#basics.lib)[`sAndH`](#sandh) | Sample and hold
[Signal Crossing](#cross) | [`ro.`](#routes.lib)[`cross`](#cross) | Cross n signals
[Smoother (Default)](#smoo) | [`si.`](#signals.lib)[`smoo`](#smoo) | Exponential smoothing
[Smoother](#smooth) | [`si.`](#signals.lib)[`smooth`](#smooth) | Exponential smoothing with controllable pole
[Take Element](#take) | [`ba.`](#basics.lib)[`take`](#take) | Take en element from a list
[Time](#time) | [`ba.`](#basics.lib)[`time`](#time) | A simple timer

<div class="table-end"></div>


## Conversion

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[dB to Linear](#db2linear) | [`ba.`](#basics.lib)[`db2linear`](#db2linear) | Converts dB to linear values
[Linear to dB](#linear2db) | [`ba.`](#basics.lib)[`linear2db`](#linear2db) | Converts linear values to dB
[MIDI Key to Hz](#midikey2hz) | [`ba.`](#basics.lib)[`midikey2hz`](#midikey2hz) | Converts a MIDI key number into a frequency
[Hz to MIDI Key](#hz2midikey) | [`ba.`](#basics.lib)[`hz2midikey`](#hz2midikey) | Converts a frequency into MIDI key number
[Pole to T60](#pole2tau) | [`ba.`](#basics.lib)[`pole2tau`](#pole2tau) | Converts a pole into a time constant (t60)
[Samples to Seconds](#samp2sec) | [`ba.`](#basics.lib)[`samp2sec`](#samp2sec) | Converts samples to seconds
[Seconds to Samples](#sec2samp) | [`ba.`](#basics.lib)[`sec2samp`](#sec2samp) | Converts seconds to samples
[T60 to Pole](#tau2pole) | [`ba.`](#basics.lib)[`tau2pole`](#tau2pole) | Converts a time constant (t60) into a pole

<div class="table-end"></div>


## Effects

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Auto Wah](#autowah) | [`ve.`](#vaeffects.lib)[`autowah`](#autowah) | Auto-Wah effect
[Compressor](#compressor_mono) | [`co.`](#compressors.lib)[`compressor_mono`](#compressor_mono) | Dynamic range compressor
[Distortion](#cubicnl) | [`ef.`](#misceffects.lib)[`cubicnl`](#cubicnl) | Cubic nonlinearity distortion
[Crybaby](#crybaby) | [`ve.`](#vaeffects.lib)[`crybaby`](#crybaby) | Crybaby wah pedal
[Echo](#echo) | [`ef.`](#misceffects.lib)[`echo`](#echo) | Simple echo
[Flanger](#flanger_stereo) | [`pf.`](#phaflangers.lib)[`flanger_stereo`](#flanger_stereo) | Flanging effect
[Gate](#gate_mono) | [`ef.`](#misceffects.lib)[`gate_mono`](#gate_mono) | Mono signal gate
[Limiter](#limiter_1176_R4_mono) | [`co.`](#compressors.lib)[`limiter_1176_R4_mono`](#limiter_1176_R4_mono) | Limiter
[Phaser](#phaser2_stereo) | [`pf.`](#phaflangers.lib)[`phaser2_stereo`](#phaser2_stereo) | Phaser effect
[Reverb (FDN)](#fdnrev0) | [`re.`](#reverbs.lib)[`fdnrev0`](#fdnrev0) | Feedback delay network reverberator
[Reverb (Freeverb)](#mono_freeverb) | [`re.`](#reverbs.lib)[`mono_freeverb`](#mono_freeverb) | Most "famous" Schroeder reverberator
[Reverb (Simple)](#jcrev) | [`re.`](#reverbs.lib)[`jcrev`](#jcrev) | Simple Schroeder reverberator
[Reverb (Zita)](#zita_rev1_stereo) | [`re.`](#reverbs.lib)[`zita_rev1_stereo`](#zita_rev1_stereo) | High quality FDN reverberator
[Panner](#panner) | [`sp.`](#spats.lib)[`panner`](#panner) | Linear stereo panner
[Pitch Shift](#transpose) | [`ef.`](#misceffects.lib)[`transpose`](#transpose) | Simple pitch shifter
[Panner](#spat) | [`sp.`](#spats.lib)[`spat`](#spat) | N outputs spatializer
[Speaker Simulator](#speakerbp) | [`ef.`](#misceffects.lib)[`speakerbp`](#speakerbp) | Simple speaker simulator
[Stereo Width](#stereo_width) | [`ef.`](#misceffects.lib)[`stereo_width`](#stereo_width) | Stereo width effect
[Vocoder](#vocoder) | [`ve.`](#vaeffects.lib)[`vocoder`](#vocoder) | Simple vocoder
[Wah](#wah4) | [`ve.`](#vaeffects.lib)[`wah4`](#wah4) | Wah effect

<div class="table-end"></div>


## Envelope Generators

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[ADSR](#asr) | [`en.`](#envelopes.lib)[`adsr`](#adsr) | Attack/Decay/Sustain/Release envelope generator
[AR](#ar) | [`en.`](#envelopes.lib)[`ar`](#ar) | Attack/Release envelope generator
[ASR](#asr) | [`en.`](#envelopes.lib)[`asr`](#asr) | Attack/Sustain/Release envelope generator
[Exponential](#smoothEvelope) | [`en.`](#envelopes.lib)[`smoothEnvelope`](#smoothEnvelope) | Exponential envelope generator

<div class="table-end"></div>


## Filters

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Bandpass (Butterworth)](#bandpass) | [`fi.`](#filters.lib)[`bandpass`](#bandpass) | Generic butterworth bandpass
[Bandpass (Resonant)](#resonbp) | [`fi.`](#filters.lib)[`resonbp`](#resonbp) | Virtual analog resonant bandpass
[Bandstop (Butterworth)](#bandstop) | [`fi.`](#filters.lib)[`bandstop`](#bandstop) | Generic butterworth bandstop
[Biquad](#tf2) | [`fi.`](#filters.lib)[`tf2`](#tf2) | "Standard" biquad filter
[Comb (Allpass)](#allpass_fcomb) | [`fi.`](#filters.lib)[`allpass_fcomb`](#allpass_fcomb) | Schroeder allpass comb filter
[Comb (Feedback)](#fb_fcomb) | [`fi.`](#filters.lib)[`fb_fcomb`](#fb_fcomb) | Feedback comb filter
[Comb (Feedforward)](#ff_fcomb) | [`fi.`](#filters.lib)[`ff_fcomb`](#ff_fcomb) | Feed-forward comb filter.
[DC Blocker](#dcblocker) | [`fi.`](#filters.lib)[`dcblocker`](#dcblocker) | Default dc blocker
[Filterbank](#filterbank) | [`fi.`](#filters.lib)[`filterbank`](#filterbank) | Generic filter bank
[FIR (Arbitrary Order)](#fir) | [`fi.`](#filters.lib)[`fir`](#fir) | Nth-order FIR filter
[High Shelf](#high_shelf) | [`fi.`](#filters.lib)[`high_shelf`](#high_shelf) | High shelf
[Highpass (Butterworth)](#highpass) | [`fi.`](#filters.lib)[`highpass`](#highpass) | Nth-order Butterworth highpass
[Highpass (Resonant)](#resonhp) | [`fi.`](#filters.lib)[`resonhp`](#resonhp) | Virtual analog resonant highpass
[IIR (Arbitrary Order)](#iir) | [`fi.`](#filters.lib)[`iir`](#iir) | Nth-order IIR filter
[Level Filter](#levelfilter) | [`fi.`](#filters.lib)[`levelfilter`](#levelfilter) | Dynamic level lowpass
[Low Shelf](#low_shelf) | [`fi.`](#filters.lib)[`low_shelf`](#low_shelf) | Low shelf
[Lowpass (Butterworth)](#lowpass) | [`fi.`](#filters.lib)[`lowpass`](#lowpass) | Nth-order Butterworth lowpass
[Lowpass (Resonant)](#resonlp) | [`fi.`](#filters.lib)[`resonlp`](#resonlp) | Virtual analog resonant lowpass
[Notch Filter](#notchw) | [`fi.`](#filters.lib)[`notchw`](#notchw) | Simple notch filter
[Peak Equalizer](#peak_eq) | [`fi.`](#filters.lib)[`peak_eq`](#peak_eq) | Peaking equalizer section

<div class="table-end"></div>


## Oscillators/Sound Generators

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Impulse](#impulse) | [`os.`](#oscillators.lib)[`impulse`](#impulse) | Generate an impulse on start-up
[Impulse Train](#imptrain) | [`os.`](#oscillators.lib)[`imptrain`](#imptrain) | Band-limited impulse train
[Phasor](#phasor) | [`os.`](#oscillators.lib)[`phasor`](#phasor) | Simple phasor
[Pink Noise](#pink_noise) | [`no.`](#noises.lib)[`pink_noise`](#pink_noise) | Pink noise generator
[Pulse Train](#pulsetrain) | [`os.`](#oscillators.lib)[`pulsetrain`](#pulsetrain) | Band-limited pulse train
[Pulse Train (Low Frequency)](#lf_imptrain) | [`os.`](#oscillators.lib)[`lf_imptrain`](#lf_imptrain) | Low-frequency pulse train
[Sawtooth](#sawtooth) | [`os.`](#oscillators.lib)[`sawtooth`](#sawtooth) | Band-limited sawtooth wave
[Sawtooth (Low Frequency)](#lf_saw) | [`os.`](#oscillators.lib)[`lf_saw`](#lf_saw) | Low-frequency sawtooth wave
[Sine (Filter-Based)](#osc) | [`os.`](#oscillators.lib)[`osc`](#osc) | Sine oscillator (filter-based)
[Sine (Table-Based)](#oscsin) | [`os.`](#oscillators.lib)[`oscsin`](#oscsin) | Sine oscillator (table-based)
[Square](#square) | [`os.`](#oscillators.lib)[`square`](#square) | Band-limited square wave
[Square (Low Frequency)](#lf_squarewave) | [`os.`](#oscillators.lib)[`lf_squarewave`](#lf_squarewave) | Low-frequency square wave
[Triangle](#triangle) | [`os.`](#oscillators.lib)[`triangle`](#triangle) | Band-limited triangle wave
[Triangle (Low Frequency)](#lf_triangle) | [`os.`](#oscillators.lib)[`lf_triangle`](#lf_triangle) | Low-frequency triangle wave
[White Noise](#noise) | [`no.`](#noises.lib)[`noise`](#noise) | White noise generator

<div class="table-end"></div>


## Synths

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Additive Drum](#additivedrum) | [`sy.`](#synths.lib)[`additiveDrum`](#additivedrum) | Additive synthesis drum
[Bandpassed Sawtooth](#dubdub) | [`sy.`](#synths.lib)[`dubDub`](#dubdub) | Sawtooth through resonant bandpass
[Comb String](#combstring) | [`sy.`](#synths.lib)[`combString`](#combstring) | String model based on a comb filter
[FM](#fm) | [`sy.`](#synths.lib)[`fm`](#fm) | Frequency modulation synthesizer
[Lowpassed Sawtooth](#sawtrombone) | [`sy.`](#synths.lib)[`sawTrombone`](#sawtrombone) | "Trombone" based on a filtered sawtooth
[Popping Filter](#popfilterperc) | [`sy.`](#synths.lib)[`popFilterPerc`](#popfilterperc) | Popping filter percussion instrument

<div class="table-end"></div>


<!--
TODO: potentially say something about demos.lib and demo functions here. Also, not sure what to do with math.lib.
-->

<script type="text/javascript">
(function() {
    $('div.table-begin').nextUntil('div.table-end', 'table').addClass('table table-bordered');
	})();
</script>
