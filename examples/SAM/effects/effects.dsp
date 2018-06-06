// All effects used by minimoog.dsp

import("stdfaust.lib");
import("layout2.dsp");

process = _,_ : +
	: component("echo.dsp")
	: component("flanger.dsp")
	: component("chorus.dsp")
	: component("freeverb.dsp");
