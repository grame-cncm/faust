/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "spat"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fHslider0;
	float fHslider1;
	float fRec0[] = new float[2];
	float fRec1[] = new float[2];
	float fRec2[] = new float[2];
	float fRec3[] = new float[2];
	float fRec4[] = new float[2];
	float fRec5[] = new float[2];
	float fRec6[] = new float[2];
	float fRec7[] = new float[2];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("license", "BSD");
		m.declare("name", "spat");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("spats.lib/name", "Faust Spatialization Library");
		m.declare("spats.lib/version", "0.0");
		m.declare("version", "1.0");
	}

	int getNumInputs() {
		return 1;
		
	}
	int getNumOutputs() {
		return 8;
		
	}
	int getInputRate(int channel) {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
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
		ui_interface.openVerticalBox("Spatializer 1x8");
		ui_interface.addHorizontalSlider("angle", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("distance", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float[] output2 = outputs[2];
		float[] output3 = outputs[3];
		float[] output4 = outputs[4];
		float[] output5 = outputs[5];
		float[] output6 = outputs[6];
		float[] output7 = outputs[7];
		float fSlow0 = fHslider0;
		float fSlow1 = (fSlow0 + 1.0f);
		float fSlow2 = fHslider1;
		float fSlow3 = (4.99999987e-05f * (fSlow1 * (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, (1.0f - (8.0f * (fSlow0 * (float)java.lang.Math.abs(((float)java.lang.Math.IEEEremainder((fSlow2 + 1.5f), 1.0f) + -0.5f)))))))));
		float fSlow4 = (4.99999987e-05f * (fSlow1 * (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, (1.0f - (8.0f * (fSlow0 * (float)java.lang.Math.abs(((float)java.lang.Math.IEEEremainder((fSlow2 + 1.375f), 1.0f) + -0.5f)))))))));
		float fSlow5 = (4.99999987e-05f * (fSlow1 * (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, (1.0f - (8.0f * (fSlow0 * (float)java.lang.Math.abs(((float)java.lang.Math.IEEEremainder((fSlow2 + 1.25f), 1.0f) + -0.5f)))))))));
		float fSlow6 = (4.99999987e-05f * (fSlow1 * (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, (1.0f - (8.0f * (fSlow0 * (float)java.lang.Math.abs(((float)java.lang.Math.IEEEremainder((fSlow2 + 1.125f), 1.0f) + -0.5f)))))))));
		float fSlow7 = (4.99999987e-05f * (fSlow1 * (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, (1.0f - (8.0f * (fSlow0 * (float)java.lang.Math.abs(((float)java.lang.Math.IEEEremainder((fSlow2 + 1.0f), 1.0f) + -0.5f)))))))));
		float fSlow8 = (4.99999987e-05f * (fSlow1 * (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, (1.0f - (8.0f * (fSlow0 * (float)java.lang.Math.abs(((float)java.lang.Math.IEEEremainder((fSlow2 + 0.875f), 1.0f) + -0.5f)))))))));
		float fSlow9 = (4.99999987e-05f * (fSlow1 * (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, (1.0f - (8.0f * (fSlow0 * (float)java.lang.Math.abs(((float)java.lang.Math.IEEEremainder((fSlow2 + 0.75f), 1.0f) + -0.5f)))))))));
		float fSlow10 = (4.99999987e-05f * (fSlow1 * (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, (1.0f - (8.0f * (fSlow0 * (float)java.lang.Math.abs(((float)java.lang.Math.IEEEremainder((fSlow2 + 0.625f), 1.0f) + -0.5f)))))))));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fRec0[0] = (fSlow3 + (0.999899983f * fRec0[1]));
			output0[i] = (fTemp0 * fRec0[0]);
			fRec1[0] = (fSlow4 + (0.999899983f * fRec1[1]));
			output1[i] = (fTemp0 * fRec1[0]);
			fRec2[0] = (fSlow5 + (0.999899983f * fRec2[1]));
			output2[i] = (fTemp0 * fRec2[0]);
			fRec3[0] = (fSlow6 + (0.999899983f * fRec3[1]));
			output3[i] = (fTemp0 * fRec3[0]);
			fRec4[0] = (fSlow7 + (0.999899983f * fRec4[1]));
			output4[i] = (fTemp0 * fRec4[0]);
			fRec5[0] = (fSlow8 + (0.999899983f * fRec5[1]));
			output5[i] = (fTemp0 * fRec5[0]);
			fRec6[0] = (fSlow9 + (0.999899983f * fRec6[1]));
			output6[i] = (fTemp0 * fRec6[0]);
			fRec7[0] = (fSlow10 + (0.999899983f * fRec7[1]));
			output7[i] = (fTemp0 * fRec7[0]);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}
	
};

