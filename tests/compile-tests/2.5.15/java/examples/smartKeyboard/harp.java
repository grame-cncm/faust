/* ------------------------------------------------------------
name: "harp"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	float fConst0;
	float fVec0[] = new float[2];
	float fHslider0;
	float fConst1;
	float fHslider1;
	int iRec2[] = new int[2];
	float fButton0;
	float fVec1[] = new float[2];
	float fConst2;
	float fRec3[] = new float[2];
	float fConst3;
	int IOTA;
	float fVec2[] = new float[2048];
	float fRec0[] = new float[2];
	float fRec1[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'8',  'Keyboard 0 - Number of Keys':'16',  'Keyboard 1 - Number of Keys':'16',  'Keyboard 2 - Number of Keys':'16',  'Keyboard 3 - Number of Keys':'16',  'Keyboard 4 - Number of Keys':'16',  'Keyboard 5 - Number of Keys':'16',  'Keyboard 6 - Number of Keys':'16',  'Keyboard 7 - Number of Keys':'16',  'Keyboard 0 - Lowest Key':'40',  'Keyboard 1 - Lowest Key':'45',  'Keyboard 2 - Lowest Key':'50',  'Keyboard 3 - Lowest Key':'55',  'Keyboard 4 - Lowest Key':'60',  'Keyboard 5 - Lowest Key':'65',  'Keyboard 6 - Lowest Key':'70',  'Keyboard 7 - Lowest Key':'75',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "harp");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("synths.lib/name", "Faust Synthesizer Library");
		m.declare("synths.lib/version", "0.0");
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
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq));
		fConst1 = (1000.0f / fConst0);
		fConst2 = (0.00200000009f * fConst0);
		fConst3 = (0.00100000005f * fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)400.0f;
		fHslider1 = (float)2.0f;
		fButton0 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec2[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		IOTA = 0;
		for (int l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			fVec2[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec0[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec1[l6] = 0.0f;
			
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
		ui_interface.openVerticalBox("harp");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 400.0f, 50.0f, 2000.0f, 0.00999999978f);
		ui_interface.addButton("gate", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("res", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 2.0f, 0.100000001f, 4.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float fSlow0 = (fConst0 / fHslider0);
		float fSlow1 = (fSlow0 + -1.0f);
		float fSlow2 = (float)java.lang.Math.floor(fSlow1);
		float fSlow3 = (fSlow2 + (2.0f - fSlow0));
		float fSlow4 = (float)java.lang.Math.exp((0.0f - (fConst1 / fHslider1)));
		float fSlow5 = fButton0;
		int iSlow6 = (int)fSlow1;
		int iSlow7 = java.lang.Math.min(1025, java.lang.Math.max(0, iSlow6));
		float fSlow8 = (fSlow0 + (-1.0f - fSlow2));
		int iSlow9 = java.lang.Math.min(1025, java.lang.Math.max(0, (iSlow6 + 1)));
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fConst0;
			iRec2[0] = ((1103515245 * iRec2[1]) + 12345);
			fVec1[0] = fSlow5;
			fRec3[0] = (((((fSlow5 - fVec1[1]) > 0.0f) > 0))?0.0f:(float)java.lang.Math.min(fConst2, ((fRec3[1] + (0.00200000009f * (fConst0 - fVec0[1]))) + 1.0f)));
			int iTemp0 = (fRec3[0] < fConst3);
			float fTemp1 = ((fSlow4 * fRec0[1]) + (4.65661287e-10f * ((float)iRec2[0] * (((iTemp0==0)?true:false)?(((fRec3[0] < 0.0f))?0.0f:(((iTemp0==0)?true:false)?(fConst1 * fRec3[0]):1.0f)):(((fRec3[0] < fConst2))?((fConst1 * (0.0f - (fRec3[0] - fConst3))) + 1.0f):0.0f)))));
			fVec2[(IOTA & 2047)] = fTemp1;
			fRec0[0] = ((fSlow3 * fVec2[((IOTA - iSlow7) & 2047)]) + (fSlow8 * fVec2[((IOTA - iSlow9) & 2047)]));
			fRec1[0] = fTemp1;
			output0[i] = fRec1[1];
			fVec0[1] = fVec0[0];
			iRec2[1] = iRec2[0];
			fVec1[1] = fVec1[0];
			fRec3[1] = fRec3[0];
			IOTA = (IOTA + 1);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			
		}
		
	}
	
};

