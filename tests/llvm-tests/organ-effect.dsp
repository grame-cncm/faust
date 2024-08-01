import("stdfaust.lib");

timbre(f) = os.osc(f)*0.5 + os.osc(f*2)*0.25 + os.osc(f*3)*0.125;

process = timbre(hslider("freq", 440, 20, 10000, 1))
	* hslider("gain", 0.5, 0, 1, 0.01)
	* (button("gate") : en.adsr(0.1,0.1,0.98,1.5));
    
    effect = dm.zita_light;