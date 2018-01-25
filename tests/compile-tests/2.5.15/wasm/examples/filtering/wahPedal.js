
/*
Code generated with Faust version 2.5.15
Compilation options: wast/wasm, -scal -ftz 0
*/

function getJSONmydsp() {
	return "{\"name\":\"wahPedal\",\"version\":\"2.5.15\",\"options\":\"wast/wasm, -scal -ftz 0\",\"size\":\"64\",\"inputs\":\"1\",\"outputs\":\"1\",\"meta\":[{\"basics.lib/name\":\"Faust Basic Element Library\"},{\"basics.lib/version\":\"0.0\"},{\"description\":\"Demonstrate the Fourth-Order Wah pedal (similar to the Moog VCF)\"},{\"filters.lib/name\":\"Faust Filters Library\"},{\"filters.lib/version\":\"0.0\"},{\"maths.lib/author\":\"GRAME\"},{\"maths.lib/copyright\":\"GRAME\"},{\"maths.lib/license\":\"LGPL with exception\"},{\"maths.lib/name\":\"Faust Math Library\"},{\"maths.lib/version\":\"2.1\"},{\"name\":\"wahPedal\"},{\"signals.lib/name\":\"Faust Signal Routing Library\"},{\"signals.lib/version\":\"0.0\"},{\"vaeffects.lib/name\":\"Faust Virtual Analog Filter Effect Library\"},{\"vaeffects.lib/version\":\"0.0\"}],\"ui\":[{\"type\":\"hgroup\",\"label\":\"WAH4\",\"meta\":[{\"tooltip\":\"Fourth-order wah effect made using moog_vcf\"}],\"items\":[{\"type\":\"checkbox\",\"label\":\"Bypass\",\"address\":\"/WAH4/Bypass\",\"index\":\"0\",\"meta\":[{\"0\":\"\"},{\"tooltip\":\"When this is checked, the wah pedal has   no effect\"}]},{\"type\":\"hslider\",\"label\":\"Resonance Frequency\",\"address\":\"/WAH4/Resonance_Frequency\",\"index\":\"12\",\"meta\":[{\"1\":\"\"},{\"scale\":\"log\"},{\"tooltip\":\"wah resonance   frequency in Hz\"}],\"init\":\"200\",\"min\":\"100\",\"max\":\"2000\",\"step\":\"1\"}]}]}";
}
