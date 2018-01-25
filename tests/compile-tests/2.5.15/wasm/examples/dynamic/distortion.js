
/*
Code generated with Faust version 2.5.15
Compilation options: wast/wasm, -scal -ftz 0
*/

function getJSONmydsp() {
	return "{\"name\":\"distortion\",\"version\":\"2.5.15\",\"options\":\"wast/wasm, -scal -ftz 0\",\"size\":\"48\",\"inputs\":\"1\",\"outputs\":\"1\",\"meta\":[{\"author\":\"JOS, revised by RM\"},{\"basics.lib/name\":\"Faust Basic Element Library\"},{\"basics.lib/version\":\"0.0\"},{\"description\":\"Distortion demo application.\"},{\"filters.lib/name\":\"Faust Filters Library\"},{\"filters.lib/version\":\"0.0\"},{\"misceffects.lib/name\":\"Faust Math Library\"},{\"misceffects.lib/version\":\"2.0\"},{\"name\":\"distortion\"},{\"signals.lib/name\":\"Faust Signal Routing Library\"},{\"signals.lib/version\":\"0.0\"},{\"version\":\"0.0\"}],\"ui\":[{\"type\":\"vgroup\",\"label\":\"CUBIC NONLINEARITY cubicnl\",\"meta\":[{\"tooltip\":\"Reference:   https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html\"}],\"items\":[{\"type\":\"checkbox\",\"label\":\"Bypass\",\"address\":\"/CUBIC_NONLINEARITY_cubicnl/Bypass\",\"index\":\"0\",\"meta\":[{\"0\":\"\"},{\"tooltip\":\"When this is checked, the   nonlinearity has no effect\"}]},{\"type\":\"hslider\",\"label\":\"Drive\",\"address\":\"/CUBIC_NONLINEARITY_cubicnl/Drive\",\"index\":\"4\",\"meta\":[{\"1\":\"\"},{\"tooltip\":\"Amount of distortion\"}],\"init\":\"0\",\"min\":\"0\",\"max\":\"1\",\"step\":\"0.01\"},{\"type\":\"hslider\",\"label\":\"Offset\",\"address\":\"/CUBIC_NONLINEARITY_cubicnl/Offset\",\"index\":\"16\",\"meta\":[{\"2\":\"\"},{\"tooltip\":\"Brings in even harmonics\"}],\"init\":\"0\",\"min\":\"0\",\"max\":\"1\",\"step\":\"0.01\"}]}]}";
}
