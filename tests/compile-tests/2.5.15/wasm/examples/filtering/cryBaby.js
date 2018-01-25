
/*
Code generated with Faust version 2.5.15
Compilation options: wast/wasm, -scal -ftz 0
*/

function getJSONmydsp() {
	return "{\"name\":\"cryBaby\",\"version\":\"2.5.15\",\"options\":\"wast/wasm, -scal -ftz 0\",\"size\":\"60\",\"inputs\":\"1\",\"outputs\":\"1\",\"meta\":[{\"basics.lib/name\":\"Faust Basic Element Library\"},{\"basics.lib/version\":\"0.0\"},{\"description\":\"Application demonstrating the CryBaby wah pedal emulation\"},{\"filters.lib/name\":\"Faust Filters Library\"},{\"filters.lib/version\":\"0.0\"},{\"maths.lib/author\":\"GRAME\"},{\"maths.lib/copyright\":\"GRAME\"},{\"maths.lib/license\":\"LGPL with exception\"},{\"maths.lib/name\":\"Faust Math Library\"},{\"maths.lib/version\":\"2.1\"},{\"name\":\"cryBaby\"},{\"signals.lib/name\":\"Faust Signal Routing Library\"},{\"signals.lib/version\":\"0.0\"},{\"vaeffects.lib/name\":\"Faust Virtual Analog Filter Effect Library\"},{\"vaeffects.lib/version\":\"0.0\"}],\"ui\":[{\"type\":\"hgroup\",\"label\":\"CRYBABY\",\"meta\":[{\"tooltip\":\"Reference:   https://ccrma.stanford.edu/~jos/pasp/vegf.html\"}],\"items\":[{\"type\":\"checkbox\",\"label\":\"Bypass\",\"address\":\"/CRYBABY/Bypass\",\"index\":\"0\",\"meta\":[{\"0\":\"\"},{\"tooltip\":\"When this is checked, the wah   pedal has no effect\"}]},{\"type\":\"hslider\",\"label\":\"Wah parameter\",\"address\":\"/CRYBABY/Wah_parameter\",\"index\":\"4\",\"meta\":[{\"1\":\"\"},{\"tooltip\":\"wah pedal angle between   0 (rocked back) and 1 (rocked forward)\"}],\"init\":\"0.8\",\"min\":\"0\",\"max\":\"1\",\"step\":\"0.01\"}]}]}";
}
