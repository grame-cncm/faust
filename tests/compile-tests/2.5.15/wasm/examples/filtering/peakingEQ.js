
/*
Code generated with Faust version 2.5.15
Compilation options: wast/wasm, -scal -ftz 0
*/

function getJSONmydsp() {
	return "{\"name\":\"peakingEQ\",\"version\":\"2.5.15\",\"options\":\"wast/wasm, -scal -ftz 0\",\"size\":\"32\",\"inputs\":\"1\",\"outputs\":\"1\",\"meta\":[{\"maths.lib/author\":\"GRAME\"},{\"maths.lib/copyright\":\"GRAME\"},{\"maths.lib/license\":\"LGPL with exception\"},{\"maths.lib/name\":\"Faust Math Library\"},{\"maths.lib/version\":\"2.1\"},{\"maxmsp.lib/author\":\"GRAME\"},{\"maxmsp.lib/copyright\":\"GRAME\"},{\"maxmsp.lib/license\":\"LGPL\"},{\"maxmsp.lib/name\":\"MaxMSP compatibility Library\"},{\"maxmsp.lib/version\":\"1.1\"},{\"name\":\"peakingEQ\"}],\"ui\":[{\"type\":\"vgroup\",\"label\":\"peakingEQ\",\"items\":[{\"type\":\"hslider\",\"label\":\"Freq\",\"address\":\"/peakingEQ/Freq\",\"index\":\"8\",\"init\":\"1000\",\"min\":\"100\",\"max\":\"10000\",\"step\":\"1\"},{\"type\":\"hslider\",\"label\":\"Gain\",\"address\":\"/peakingEQ/Gain\",\"index\":\"16\",\"meta\":[{\"unit\":\"dB\"}],\"init\":\"0\",\"min\":\"-10\",\"max\":\"10\",\"step\":\"0.1\"},{\"type\":\"hslider\",\"label\":\"Q\",\"address\":\"/peakingEQ/Q\",\"index\":\"12\",\"init\":\"1\",\"min\":\"0.01\",\"max\":\"100\",\"step\":\"0.01\"}]}]}";
}
