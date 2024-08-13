// All effects used by minimoog.dsp

import("pkg:faust/faust/stdfaust.lib@1.0.0");
import("layout2.lib");

process = _,_ : +
	: component("echo.dsp")
	: component("flanger.dsp")
	: component("chorus.dsp")
	: component("freeverb.dsp");
