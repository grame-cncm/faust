# Standard Functions

Dozens of functions are implemented in the Faust libraries and many of them are very specialized and not useful to beginners or to people who only need to use Faust for basic applications. This section offers an index organized by categories of the "standard Faust functions" (basic filters, effects, synthesizers, etc.).


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
[Beats](#beat) | [`ba.`](#basic.lib)[`beat`](#beat) | Pulses at a specific tempo
[Block](#block) | [`si.`](#signal.lib)[`block`](#block) | Terminate n signals
[Break Point Function](#bpf) | [`ba.`](#basic.lib)[`bpf`](#bpf) | Beak Point Function (BPF)
[Bus](#bus) | [`si.`](#signal.lib)[`bus`](#bus) | Bus of n signals
[Bypass (Mono)](#bypass1) | [`ba.`](#basic.lib)[`bypass1`](#bypass1) | Mono bypass
[Bypass (Stereo)](#bypass2) | [`ba.`](#basic.lib)[`bypass2`](#bypass2) | Stereo bypass
[Count Elements](#count) | [`ba.`](#basic.lib)[`count`](#count) | Count elements in a list
[Count Down](#countdown) | [`ba.`](#basic.lib)[`countdown`](#countdown) | Samples count down
[Count Up](#countup) | [`ba.`](#basic.lib)[`countup`](#countup) | Samples count up
[Delay (Integer)](#delay) | [`de.`](#delay.lib)[`delay`](#delay) | Integer delay
[Delay (Float)](#fdelay) | [`de.`](#delay.lib)[`fdelay`](#fdelay) | Fractional delay
[Impulsify](#impulsify) | [`ba.`](#basic.lib)[`impulsify`](#impulsify) | Turns a signal into an impulse
[Sample and Hold](#sandh) | [`ba.`](#basic.lib)[`sAndH`](#sandh) | Sample and hold
[Signal Crossing](#cross) | [`ro.`](#route.lib)[`cross`](#cross) | Cross n signals
[Smoother (Default)](#smoo) | [`si.`](#signal.lib)[`smoo`](#smoo) | Exponential smoothing
[Smoother](#smooth) | [`si.`](#signal.lib)[`smooth`](#smooth) | Exponential smoothing with controllable pole
[Take Element](#take) | [`ba.`](#basic.lib)[`take`](#take) | Take en element from a list
[Time](#time) | [`ba.`](#basic.lib)[`time`](#time) | A simple timer

<div class="table-end"></div>


## Conversion

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[dB to Linear](#db2linear) | [`ba.`](#basic.lib)[`db2linear`](#db2linear) | Converts dB to linear values
[Linear to dB](#linear2db) | [`ba.`](#basic.lib)[`linear2db`](#linear2db) | Converts linear values to dB
[MIDI Key to Hz](#midikey2hz) | [`ba.`](#basic.lib)[`midikey2hz`](#midikey2hz) | Converts a MIDI key number into a frequency
[Pole to T60](#pole2tau) | [`ba.`](#basic.lib)[`pole2tau`](#pole2tau) | Converts a pole into a time constant (t60)
[Samples to Seconds](#samp2sec) | [`ba.`](#basic.lib)[`samp2sec`](#samp2sec) | Converts samples to seconds
[Seconds to Samples](#sec2samp) | [`ba.`](#basic.lib)[`sec2samp`](#sec2samp) | Converts seconds to samples
[T60 to Pole](#tau2pole) | [`ba.`](#basic.lib)[`tau2pole`](#tau2pole) | Converts a time constant (t60) into a pole

<div class="table-end"></div>


## Effects

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Auto Wah](#autowah) | [`ve.`](#vaeffect.lib)[`autowah`](#autowah) | Auto-Wah effect
[Compressor](#compressor_mono) | [`co.`](#compressor.lib)[`compressor_mono`](#compressor_mono) | Dynamic range compressor
[Distortion](#cubicnl) | [`ef.`](#misceffect.lib)[`cubicnl`](#cubicnl) | Cubic nonlinearity distortion
[Crybaby](#crybaby) | [`ve.`](#vaeffect.lib)[`crybaby`](#crybaby) | Crybaby wah pedal
[Echo](#echo) | [`ef.`](#misceffect.lib)[`echo`](#echo) | Simple echo
[Flanger](#flanger_mono) | [`pf.`](#phafla.lib)[`flanger_mono`](#flanger_mono) | Flanging effect
[Gate](#gate_mono) | [`ef.`](#misceffect.lib)[`gate_mono`](#gate_mono) | Mono signal gate
[Limiter](#limiter_1176_R4_mono) | [`co.`](#compressor.lib)[`limiter_1176_R4_mono`](#limiter_1176_R4_mono) | Limiter
[Phaser](#phaser2_mono) | [`pf.`](#phafla.lib)[`phaser2_mono`](#phaser2_mono) | Phaser effect
[Pitch Shift](#transpose) | [`ef.`](#misceffect.lib)[`transpose`](#transpose) | Simple pitch shifter
[Speaker Simulator](#speakerbp) | [`ef.`](#misceffect.lib)[`speakerbp`](#speakerbp) | Simple speaker simulator
[Stereo Width](#stereo_width) | [`ef.`](#misceffect.lib)[`stereo_width`](#stereo_width) | Stereo width effect
[Vocoder](#vocoder) | [`ve.`](#vaeffect.lib)[`vocoder`](#vocoder) | Simple vocoder
[Wah](#wah4) | [`ve.`](#vaeffect.lib)[`wah4`](#wah4) | Wah effect

<div class="table-end"></div>


## Envelope Generators

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[ADSR](#asr) | [`en.`](#envelope.lib)[`adsr`](#adsr) | Attack/Decay/Sustain/Release envelope generator
[AR](#ar) | [`en.`](#envelope.lib)[`ar`](#ar) | Attack/Release envelope generator
[ASR](#asr) | [`en.`](#envelope.lib)[`asr`](#asr) | Attack/Sustain/Release envelope generator
[Exponential](#smoothEvelope) | [`en.`](#envelope.lib)[`smoothEnvelope`](#smoothEnvelope) | Exponential envelope generator

<div class="table-end"></div>


## Filters

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Bandpass (Butterworth)](#bandpass) | [`fi.`](#filter.lib)[`bandpass`](#bandpass) | Generic butterworth bandpass
[Bandpass (Resonant)](#resonbp) | [`fi.`](#filter.lib)[`resonbp`](#resonbp) | Virtual analog resonant bandpass
[Bandstop (Butterworth)](#bandstop) | [`fi.`](#filter.lib)[`bandstop`](#bandstop) | Generic butterworth bandstop
[Biquad](#tf2) | [`fi.`](#filter.lib)[`tf2`](#tf2) | "Standard" biquad filter
[Comb (Allpass)](#allpass_fcomb) | [`fi.`](#filter.lib)[`allpass_fcomb`](#allpass_fcomb) | Schroeder allpass comb filter
[Comb (Feedback)](#fb_fcomb) | [`fi.`](#filter.lib)[`fb_fcomb`](#fb_fcomb) | Feedback comb filter
[Comb (Feedforward)](#ff_fcomb) | [`fi.`](#filter.lib)[`ff_fcomb`](#ff_fcomb) | Feed-forward comb filter.
[DC Blocker](#dcblocker) | [`fi.`](#filter.lib)[`dcblocker`](#dcblocker) | Default dc blocker
[Filterbank](#filterbank) | [`fi.`](#filter.lib)[`filterbank`](#filterbank) | Generic filter bank
[FIR (Arbitrary Order)](#fir) | [`fi.`](#filter.lib)[`fir`](#fir) | Nth-order FIR filter
[High Shelf](#high_shelf) | [`fi.`](#filter.lib)[`high_shelf`](#high_shelf) | High shelf
[Highpass (Butterworth)](#highpass) | [`fi.`](#filter.lib)[`highpass`](#highpass) | Nth-order Butterworth highpass
[Highpass (Resonant)](#resonhp) | [`fi.`](#filter.lib)[`resonhp`](#resonhp) | Virtual analog resonant highpass
[IIR (Arbitrary Order)](#iir) | [`fi.`](#filter.lib)[`iir`](#iir) | Nth-order IIR filter
[Level Filter](#levelfilter) | [`fi.`](#filter.lib)[`levelfilter`](#levelfilter) | Dynamic level lowpass
[Low Shelf](#low_shelf) | [`fi.`](#filter.lib)[`low_shelf`](#low_shelf) | Low shelf
[Lowpass (Butterworth)](#lowpass) | [`fi.`](#filter.lib)[`lowpass`](#lowpass) | Nth-order Butterworth lowpass
[Lowpass (Resonant)](#resonlp) | [`fi.`](#filter.lib)[`resonlp`](#resonlp) | Virtual analog resonant lowpass
[Notch Filter](#notchw) | [`fi.`](#filter.lib)[`notchw`](#notchw) | Simple notch filter
[Peak Equalizer](#peak_eq) | [`fi.`](#filter.lib)[`peak_eq`](#peak_eq) | Peaking equalizer section

<div class="table-end"></div>


## Oscillators/Sound Generators

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Impulse](#impulse) | [`os.`](#miscoscillator.lib)[`impulse`](#impulse) | Generate an impulse on start-up
[Impulse Train](#imptrain) | [`os.`](#miscoscillator.lib)[`imptrain`](#imptrain) | Band-limited impulse train
[Phasor](#phasor) | [`os.`](#miscoscillator.lib)[`phasor`](#phasor) | Simple phasor
[Pink Noise](#pink_noise) | [`no.`](#noise.lib)[`pink_noise`](#pink_noise) | Pink noise generator
[Pulse Train](#pulsetrain) | [`os.`](#miscoscillator.lib)[`pulsetrain`](#pulsetrain) | Band-limited pulse train
[Pulse Train (Low Frequency)](#lf_imptrain) | [`os.`](#miscoscillator.lib)[`lf_imptrain`](#lf_imptrain) | Low-frequency pulse train
[Sawtooth](#sawtooth) | [`os.`](#miscoscillator.lib)[`sawtooth`](#sawtooth) | Band-limited sawtooth wave
[Sawtooth (Low Frequency)](#lf_saw) | [`os.`](#miscoscillator.lib)[`lf_saw`](#lf_saw) | Low-frequency sawtooth wave
[Sine (Filter-Based)](#osc) | [`os.`](#miscoscillator.lib)[`osc`](#osc) | Sine oscillator (filter-based)
[Sine (Table-Based)](#oscsin) | [`os.`](#miscoscillator.lib)[`oscsin`](#oscsin) | Sine oscillator (table-based)
[Square](#square) | [`os.`](#miscoscillator.lib)[`square`](#square) | Band-limited square wave
[Square (Low Frequency)](#lf_squarewave) | [`os.`](#miscoscillator.lib)[`lf_squarewave`](#lf_squarewave) | Low-frequency square wave
[Triangle](#triangle) | [`os.`](#miscoscillator.lib)[`triangle`](#triangle) | Band-limited triangle wave
[Triangle (Low Frequency)](#lf_triangle) | [`os.`](#miscoscillator.lib)[`lf_triangle`](#lf_triangle) | Low-frequency triangle wave
[White Noise](#noise) | [`no.`](#noise.lib)[`noise`](#noise) | White noise generator

<div class="table-end"></div>


## Synths

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Additive Drum](#additivedrum) | [`sy.`](#synth.lib)[`additiveDrum`](#additivedrum) | Additive synthesis drum
[Bandpassed Sawtooth](#dubdub) | [`sy.`](#synth.lib)[`dubDub`](#dubdub) | Sawtooth through resonant bandpass
[Comb String](#combstring) | [`sy.`](#synth.lib)[`combString`](#combstring) | String model based on a comb filter
[FM](#fm) | [`sy.`](#synth.lib)[`fm`](#fm) | Frequency modulation synthesizer
[Lowpassed Sawtooth](#sawtrombone) | [`sy.`](#synth.lib)[`sawTrombone`](#sawtrombone) | "Trombone" based on a filtered sawtooth
[Popping Filter](#popfilterperc) | [`sy.`](#synth.lib)[`popFilterPerc`](#popfilterperc) | Popping filter percussion instrument

<div class="table-end"></div>


<!--
TODO: potentially say something about demo.lib and demo functions here. Also, not sure what to do with math.lib.
-->

<script type="text/javascript">
(function() {
    $('div.table-begin').nextUntil('div.table-end', 'table').addClass('table table-bordered');
	})();
</script>
	
