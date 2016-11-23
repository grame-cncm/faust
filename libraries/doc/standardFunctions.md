# Standard Functions

Dozens of functions are implemented in the Faust libraries and many of them are very specialized and not useful to beginners or to people who only need to use Faust for basic applications. This section offers an index organized by categories of the "standard Faust functions" (basic filters, effects, synthesizers, etc.).

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

<script type="text/javascript">
(function() {
    $('div.table-begin').nextUntil('div.table-end', 'table').addClass('table table-bordered');
	})();
</script>
	
