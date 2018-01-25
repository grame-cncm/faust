/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2009"
license: "BSD"
name: "osci"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	static float ftbl0mydspSIG0[] = new float[65537];
	
	
	final class mydspSIG0 {
		
		int iRec1[] = new int[2];
		
		int getNumInputsmydspSIG0() {
			return 0;
			
		}
		int getNumOutputsmydspSIG0() {
			return 1;
			
		}
		int getInputRatemydspSIG0(int channel) {
			int rate;
			switch (channel) {
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		int getOutputRatemydspSIG0(int channel) {
			int rate;
			switch (channel) {
				case 0: {
					rate = 0;
					break;
				}
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		
		void instanceInitmydspSIG0(int samplingFreq) {
			for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
				iRec1[l1] = 0;
				
			}
			
		}
		void fillmydspSIG0(int count, float[] output) {
			for (int i = 0; (i < count); i = (i + 1)) {
				iRec1[0] = (iRec1[1] + 1);
				output[i] = (float)java.lang.Math.sin((9.58738019e-05f * (float)(iRec1[0] + -1)));
				iRec1[1] = iRec1[0];
				
			}
			
		}
	};

	mydspSIG0 newmydspSIG0() {return new mydspSIG0(); }
	void deletemydspSIG0(mydspSIG0 dsp) {}
	
	float fHslider0;
	float fRec0[] = new float[2];
	int fSamplingFreq;
	float fConst0;
	float fHslider1;
	float fRec2[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2009");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "osci");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
	}

	int getNumInputs() {
		return 0;
		
	}
	int getNumOutputs() {
		return 1;
		
	}
	int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	public void classInit(int samplingFreq) {
		mydspSIG0 sig0 = newmydspSIG0();
		sig0.instanceInitmydspSIG0(samplingFreq);
		sig0.fillmydspSIG0(65537, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.0f;
		fHslider1 = (float)1000.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		
	}
	
	public void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	public void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	public void buildUserInterface(UI ui_interface) {
		ui_interface.openVerticalBox("Oscillator");
		ui_interface.declare("fHslider1", "unit", "Hz");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 1000.0f, 20.0f, 24000.0f, 1.0f);
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("volume", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, -96.0f, 0.0f, 0.100000001f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float fSlow0 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider0)));
		float fSlow1 = (fConst0 * fHslider1);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fRec2[0] = (fSlow1 + (fRec2[1] - (float)java.lang.Math.floor((fSlow1 + fRec2[1]))));
			float fTemp0 = (65536.0f * fRec2[0]);
			int iTemp1 = (int)fTemp0;
			output0[i] = (fRec0[0] * (ftbl0mydspSIG0[iTemp1] + ((fTemp0 - (float)java.lang.Math.floor(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1]))));
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			
		}
		
	}
	
};

