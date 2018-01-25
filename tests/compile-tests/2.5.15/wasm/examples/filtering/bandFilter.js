
/*
Code generated with Faust version 2.5.15
Compilation options: wast/wasm, -scal -ftz 0
*/

function getJSONmydsp() {
	return "{\"name\":\"bandFilter\",\"version\":\"2.5.15\",\"options\":\"wast/wasm, -scal -ftz 0\",\"size\":\"32\",\"inputs\":\"1\",\"outputs\":\"1\",\"meta\":[{\"author\":\"Grame\"},{\"basics.lib/name\":\"Faust Basic Element Library\"},{\"basics.lib/version\":\"0.0\"},{\"copyright\":\"(c)GRAME 2006\"},{\"filters.lib/name\":\"Faust Filters Library\"},{\"filters.lib/version\":\"0.0\"},{\"license\":\"BSD\"},{\"maths.lib/author\":\"GRAME\"},{\"maths.lib/copyright\":\"GRAME\"},{\"maths.lib/license\":\"LGPL with exception\"},{\"maths.lib/name\":\"Faust Math Library\"},{\"maths.lib/version\":\"2.1\"},{\"name\":\"bandFilter\"},{\"version\":\"1.0\"}],\"ui\":[{\"type\":\"vgroup\",\"label\":\"Bandfilter\",\"items\":[{\"type\":\"nentry\",\"label\":\"Q factor\",\"address\":\"/Bandfilter/Q_factor\",\"index\":\"16\",\"meta\":[{\"style\":\"knob\"}],\"init\":\"50\",\"min\":\"0.1\",\"max\":\"100\",\"step\":\"0.1\"},{\"type\":\"nentry\",\"label\":\"freq\",\"address\":\"/Bandfilter/freq\",\"index\":\"8\",\"meta\":[{\"style\":\"knob\"},{\"unit\":\"Hz\"}],\"init\":\"1000\",\"min\":\"20\",\"max\":\"20000\",\"step\":\"1\"},{\"type\":\"vslider\",\"label\":\"gain\",\"address\":\"/Bandfilter/gain\",\"index\":\"12\",\"meta\":[{\"unit\":\"dB\"}],\"init\":\"0\",\"min\":\"-50\",\"max\":\"50\",\"step\":\"0.1\"}]}]}";
}
