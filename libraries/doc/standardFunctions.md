# Standard Functions

Dozens of functions are implemented in the Faust libraries and many of them are very specialized and not useful to beginners or to people who only need to use Faust for basic applications. This section offers an index organized by categories of the "standard Faust functions" (basic filters, effects, synthesizers, etc.).

## Oscillators/Sound Generators

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[White Noise](#noise) | [`no.`](#noise.lib)[`noise`](#noise) | White noise generator.
[Sine](#osc) | [`os.`](#miscoscillator.lib)[`osc`](#osc) | Sine wave oscillator (filter based).

<div class="table-end"></div>

## Filters

<div class="table-begin"></div>

Function Type | Function Name | Description
--- | --- | ---
[Comb](#ff_fcomb) | [`fi.`](#filter.lib)[`ff_fcomb`](#ff_fcomb) | Feed-forward comb filter.
[Feedback Comb](#fb_fcomb) | [`fi.`](#filter.lib)[`fb_fcomb`](#fb_fcomb) | Feedback comb filter.
[Butterworth Lowpass](#lowpass) | [`fi.`](#filter.lib)[`lowpass`](#lowpass) | Nth-order Butterworth lowpass filter.
[Butterworth Highpass](#highpass) | [`fi.`](#filter.lib)[`highpass`](#highpass) | Nth-order Butterworth highpass filter.

<div class="table-end"></div>

<script type="text/javascript">
(function() {
    $('div.table-begin').nextUntil('div.table-end', 'table').addClass('table table-bordered');
	})();
</script>
	
