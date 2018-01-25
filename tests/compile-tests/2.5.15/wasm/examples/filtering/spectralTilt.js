
/*
Code generated with Faust version 2.5.15
Compilation options: wast/wasm, -scal -ftz 0
*/

function getJSONmydsp() {
	return "{\"name\":\"spectralTilt\",\"version\":\"2.5.15\",\"options\":\"wast/wasm, -scal -ftz 0\",\"size\":\"60\",\"inputs\":\"1\",\"outputs\":\"1\",\"meta\":[{\"description\":\"Demonstrate the Spectral Tilt effect on test signals\"},{\"filters.lib/name\":\"Faust Filters Library\"},{\"filters.lib/version\":\"0.0\"},{\"maths.lib/author\":\"GRAME\"},{\"maths.lib/copyright\":\"GRAME\"},{\"maths.lib/license\":\"LGPL with exception\"},{\"maths.lib/name\":\"Faust Math Library\"},{\"maths.lib/version\":\"2.1\"},{\"name\":\"spectralTilt\"}],\"ui\":[{\"type\":\"vgroup\",\"label\":\"spectralTilt\",\"items\":[{\"type\":\"hslider\",\"label\":\"Slope of Spectral Tilt across Band\",\"address\":\"/spectralTilt/Slope_of_Spectral_Tilt_across_Band\",\"index\":\"20\",\"meta\":[{\"1\":\"\"}],\"init\":\"-0.5\",\"min\":\"-1\",\"max\":\"1\",\"step\":\"0.001\"},{\"type\":\"hslider\",\"label\":\"Band Start Frequency\",\"address\":\"/spectralTilt/Band_Start_Frequency\",\"index\":\"12\",\"meta\":[{\"2\":\"\"},{\"unit\":\"Hz\"}],\"init\":\"100\",\"min\":\"20\",\"max\":\"10000\",\"step\":\"1\"},{\"type\":\"hslider\",\"label\":\"Band Width\",\"address\":\"/spectralTilt/Band_Width\",\"index\":\"16\",\"meta\":[{\"3\":\"\"},{\"unit\":\"Hz\"}],\"init\":\"5000\",\"min\":\"100\",\"max\":\"10000\",\"step\":\"1\"}]}]}";
}
