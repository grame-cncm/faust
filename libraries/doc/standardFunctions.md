# Standard Functions

Dozens of functions are implemented in the Faust libraries and many of them are very specialized and not useful to beginners or to people who only need to use Faust for basic applications. This section offers an index organized by categories of the "standard Faust functions" (basic filters, effects, synthesizers, etc.).

## Oscillators/Sound Generators

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[White Noise](#noise) | [`no.`](#noise.lib)[`noise`](#noise) | White noise generator
[Pink Noise](#pink_noise) | [`no.`](#noise.lib)[`pink_noise`](#pink_noise) | Pink noise generator
[Phasor](#phasor) | [`os.`](#miscoscillator.lib)[`phasor`](#phasor) | Simple phasor
[Sine (Table-Based)](#oscsin) | [`os.`](#miscoscillator.lib)[`oscsin`](#oscsin) | Sine wave oscillator (table-based)
[Sine (Filter-Based)](#osc) | [`os.`](#miscoscillator.lib)[`osc`](#osc) | Sine wave oscillator (filter-based)
[LF Pulse Train](#lf_imptrain) | [`os.`](#miscoscillator.lib)[`lf_imptrain`](#lf_imptrain) | Low-frequency impulse train
[LF Square Wave](#lf_squarewave) | [`os.`](#miscoscillator.lib)[`lf_squarewave`](#lf_squarewave) | Low-frequency square wave
[LF Triangle Wave](#lf_triangle) | [`os.`](#miscoscillator.lib)[`lf_triangle`](#lf_triangle) | Low-frequency triangle wave
[LF Sawtooth Wave](#lf_saw) | [`os.`](#miscoscillator.lib)[`lf_saw`](#lf_saw) | Low-frequency sawtooth wave
[Sawtooth Wave](#sawtooth) | [`os.`](#miscoscillator.lib)[`sawtooth`](#sawtooth) | Alias-free sawtooth wave

<div class="table-end"></div>

## Filters

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[DC Blocker](#dcblocker) | [`fi.`](#filter.lib)[`dcblocker`](#dcblocker) | Default dc blocker
[Comb](#ff_fcomb) | [`fi.`](#filter.lib)[`ff_fcomb`](#ff_fcomb) | Feed-forward comb filter.
[Feedback Comb](#fb_fcomb) | [`fi.`](#filter.lib)[`fb_fcomb`](#fb_fcomb) | Feedback comb filter
[Allpass Comb](#allpass_fcomb) | [`fi.`](#filter.lib)[`allpass_fcomb`](#allpass_fcomb) | Schroeder allpass comb filter
[Arbitrary Order IIR](#iir) | [`fi.`](#filter.lib)[`iir`](#iir) | Nth-order IIR filter
[Arbitrary Order FIR](#fir) | [`fi.`](#filter.lib)[`fir`](#fir) | Nth-order FIR filter
[Biquad](#tf2) | [`fi.`](#filter.lib)[`tf2`](#tf2) | "Standard" biquad filter
[Notch Filter](#notchw) | [`fi.`](#filter.lib)[`notchw`](#notchw) | Simple notch filter
[Resonant Lowpass](#resonlp) | [`fi.`](#filter.lib)[`resonlp`](#resonlp) | Virtual analog resonant lowpass
[Resonant Highpass](#resonhp) | [`fi.`](#filter.lib)[`resonhp`](#resonhp) | Virtual analog resonant highpass
[Resonant Bandpass](#resonbp) | [`fi.`](#filter.lib)[`resonbp`](#resonbp) | Virtual analog resonant bandpass
[Butterworth Bandpass](#bandpass) | [`fi.`](#filter.lib)[`bandpass`](#bandpass) | Generic butterworth bandpass
[Butterworth Bandstop](#bandstop) | [`fi.`](#filter.lib)[`bandstop`](#bandstop) | Generic butterworth bandstop
[Butterworth Lowpass](#lowpass) | [`fi.`](#filter.lib)[`lowpass`](#lowpass) | Nth-order Butterworth lowpass
[Butterworth Highpass](#highpass) | [`fi.`](#filter.lib)[`highpass`](#highpass) | Nth-order Butterworth highpass
[Low Shelf](#low_shelf) | [`fi.`](#filter.lib)[`low_shelf`](#low_shelf) | Low shelf
[High Shelf](#high_shelf) | [`fi.`](#filter.lib)[`high_shelf`](#high_shelf) | High shelf
[Peak Equalizer](#peak_eq) | [`fi.`](#filter.lib)[`peak_eq`](#peak_eq) | Peaking equalizer section
[Level Filter](#levelfilter) | [`fi.`](#filter.lib)[`levelfilter`](#levelfilter) | Dynamic level lowpass
[Filterbank](#filterbank) | [`fi.`](#filter.lib)[`filterbank`](#filterbank) | Generic filter bank


<div class="table-end"></div>

<script type="text/javascript">
(function() {
    $('div.table-begin').nextUntil('div.table-end', 'table').addClass('table table-bordered');
	})();
</script>
	
