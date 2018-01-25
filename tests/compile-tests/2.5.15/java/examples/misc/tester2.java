/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2014"
license: "BSD"
name: "tester2"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	static float ftbl0mydspSIG0[] = new float[65537];
	
	
	final class mydspSIG0 {
		
		int iRec2[] = new int[2];
		
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
			for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
				iRec2[l2] = 0;
				
			}
			
		}
		void fillmydspSIG0(int count, float[] output) {
			for (int i = 0; (i < count); i = (i + 1)) {
				iRec2[0] = (iRec2[1] + 1);
				output[i] = (float)java.lang.Math.sin((9.58738019e-05f * (float)(iRec2[0] + -1)));
				iRec2[1] = iRec2[0];
				
			}
			
		}
	};

	mydspSIG0 newmydspSIG0() {return new mydspSIG0(); }
	void deletemydspSIG0(mydspSIG0 dsp) {}
	
	float fHslider0;
	float fRec0[] = new float[2];
	float fHslider1;
	float fRec1[] = new float[2];
	float fHslider2;
	int fSamplingFreq;
	float fConst0;
	float fHslider3;
	float fRec3[] = new float[2];
	int iRec5[] = new int[3];
	float fRec4[] = new float[3];
	float fRec6[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2014");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "tester2");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		return 2;
		
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
			case 1: {
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
		fHslider0 = (float)-96.0f;
		fHslider1 = (float)0.0f;
		fHslider2 = (float)0.0f;
		fHslider3 = (float)440.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			iRec5[l4] = 0;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
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
		ui_interface.openVerticalBox("Stereo Audio Tester");
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "unit", "Hz");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 440.0f, 40.0f, 20000.0f, 1.0f);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("volume", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, -96.0f, -96.0f, 0.0f, 1.0f);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.declare("fHslider2", "style", "menu{'white noise':0;'pink noise':1;'sine':2}");
		ui_interface.addHorizontalSlider("signal", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface.declare("fHslider1", "4", "");
		ui_interface.declare("fHslider1", "style", "radio{'none':0;'left':1;'right':2;'both':3}");
		ui_interface.addHorizontalSlider("channel", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 3.0f, 1.0f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider0)));
		int iSlow1 = (int)fHslider1;
		int iSlow2 = ((iSlow1 & 1) != 0);
		int iSlow3 = (int)fHslider2;
		int iSlow4 = (iSlow3 == 0);
		int iSlow5 = (iSlow3 == 1);
		float fSlow6 = (fConst0 * fHslider3);
		int iSlow7 = ((iSlow1 & 2) != 0);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fRec1[0] = (((fRec1[1] < (float)iSlow2))?(float)java.lang.Math.min((fRec1[1] + 0.000226757373f), (float)iSlow2):(float)java.lang.Math.max((fRec1[1] + -0.000226757373f), (float)iSlow2));
			fRec3[0] = (fSlow6 + (fRec3[1] - (float)java.lang.Math.floor((fSlow6 + fRec3[1]))));
			float fTemp0 = (65536.0f * fRec3[0]);
			int iTemp1 = (int)fTemp0;
			iRec5[0] = ((1103515245 * iRec5[1]) + 12345);
			fRec4[0] = (((6.90678287e-12f * (float)iRec5[2]) + ((1.80116081f * fRec4[1]) + (2.30852802e-11f * (float)iRec5[0]))) - ((0.802577376f * fRec4[2]) + (2.93626512e-11f * (float)iRec5[1])));
			float fTemp2 = (((iSlow4==0)?true:false)?(4.65661287e-10f * (float)iRec5[0]):(((iSlow5==0)?true:false)?fRec4[0]:(ftbl0mydspSIG0[iTemp1] + ((fTemp0 - (float)java.lang.Math.floor(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1])))));
			output0[i] = ((fRec0[0] * fRec1[0]) * fTemp2);
			fRec6[0] = (((fRec6[1] < (float)iSlow7))?(float)java.lang.Math.min((fRec6[1] + 0.000226757373f), (float)iSlow7):(float)java.lang.Math.max((fRec6[1] + -0.000226757373f), (float)iSlow7));
			output1[i] = ((fRec0[0] * fRec6[0]) * fTemp2);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			iRec5[2] = iRec5[1];
			iRec5[1] = iRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			
		}
		
	}
	
};

