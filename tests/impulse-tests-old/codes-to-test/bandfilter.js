
/*
Code generated with Faust version 2.5.15
Compilation options: wast-i, -double -ftz 0
*/

function getJSONmydsp() {
	return "{\"name\":\"bandfilter\",\"version\":\"2.5.15\",\"options\":\"wast-i, -double -ftz 0\",\"size\":\"64\",\"inputs\":\"1\",\"outputs\":\"1\",\"meta\":[{\"author\":\"Grame\"},{\"copyright\":\"(c)GRAME 2006\"},{\"license\":\"BSD\"},{\"math.lib/author\":\"GRAME\"},{\"math.lib/copyright\":\"GRAME\"},{\"math.lib/deprecated\":\"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\"},{\"math.lib/license\":\"LGPL with exception\"},{\"math.lib/name\":\"Math Library\"},{\"math.lib/version\":\"1.0\"},{\"music.lib/author\":\"GRAME\"},{\"music.lib/copyright\":\"GRAME\"},{\"music.lib/license\":\"LGPL with exception\"},{\"music.lib/name\":\"Music Library\"},{\"music.lib/version\":\"1.0\"},{\"name\":\"bandfilter\"},{\"version\":\"1.0\"}],\"ui\":[{\"type\":\"vgroup\",\"label\":\"Bandfilter\",\"items\":[{\"type\":\"nentry\",\"label\":\"Q factor\",\"address\":\"/Bandfilter/Q_factor\",\"index\":\"32\",\"meta\":[{\"style\":\"knob\"}],\"init\":\"50\",\"min\":\"0.1\",\"max\":\"100\",\"step\":\"0.1\"},{\"type\":\"nentry\",\"label\":\"freq\",\"address\":\"/Bandfilter/freq\",\"index\":\"16\",\"meta\":[{\"style\":\"knob\"},{\"unit\":\"Hz\"}],\"init\":\"1000\",\"min\":\"20\",\"max\":\"20000\",\"step\":\"1\"},{\"type\":\"vslider\",\"label\":\"gain\",\"address\":\"/Bandfilter/gain\",\"index\":\"24\",\"meta\":[{\"unit\":\"dB\"}],\"init\":\"0\",\"min\":\"-50\",\"max\":\"50\",\"step\":\"0.1\"}]}]}";
}
