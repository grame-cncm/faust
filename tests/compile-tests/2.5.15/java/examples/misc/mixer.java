/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "mixer"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	float fConst0;
	float fVslider0;
	float fRec1[] = new float[2];
	float fEntry0;
	float fCheckbox0;
	float fVslider1;
	float fRec3[] = new float[2];
	float fRec2[] = new float[2];
	float fVbargraph0;
	float fEntry1;
	float fCheckbox1;
	float fVslider2;
	float fRec5[] = new float[2];
	float fRec4[] = new float[2];
	float fVbargraph1;
	float fEntry2;
	float fCheckbox2;
	float fVslider3;
	float fRec7[] = new float[2];
	float fRec6[] = new float[2];
	float fVbargraph2;
	float fEntry3;
	float fCheckbox3;
	float fVslider4;
	float fRec9[] = new float[2];
	float fRec8[] = new float[2];
	float fVbargraph3;
	float fEntry4;
	float fCheckbox4;
	float fVslider5;
	float fRec11[] = new float[2];
	float fRec10[] = new float[2];
	float fVbargraph4;
	float fEntry5;
	float fCheckbox5;
	float fVslider6;
	float fRec13[] = new float[2];
	float fRec12[] = new float[2];
	float fVbargraph5;
	float fEntry6;
	float fCheckbox6;
	float fVslider7;
	float fRec15[] = new float[2];
	float fRec14[] = new float[2];
	float fVbargraph6;
	float fEntry7;
	float fCheckbox7;
	float fVslider8;
	float fRec17[] = new float[2];
	float fRec16[] = new float[2];
	float fVbargraph7;
	float fRec0[] = new float[2];
	float fVbargraph8;
	float fRec18[] = new float[2];
	float fVbargraph9;
	
	public void metadata(Meta m) { 
		m.declare("../analysis/vumeter.dsp/author", "Grame");
		m.declare("../analysis/vumeter.dsp/copyright", "(c)GRAME 2006");
		m.declare("../analysis/vumeter.dsp/license", "BSD");
		m.declare("../analysis/vumeter.dsp/name", "vumeter");
		m.declare("../analysis/vumeter.dsp/version", "1.0");
		m.declare("../dynamic/volume.dsp/author", "Grame");
		m.declare("../dynamic/volume.dsp/copyright", "(c)GRAME 2006");
		m.declare("../dynamic/volume.dsp/license", "BSD");
		m.declare("../dynamic/volume.dsp/name", "volume");
		m.declare("../dynamic/volume.dsp/version", "1.0");
		m.declare("../spat/panpot.dsp/author", "Grame");
		m.declare("../spat/panpot.dsp/copyright", "(c)GRAME 2006");
		m.declare("../spat/panpot.dsp/license", "BSD");
		m.declare("../spat/panpot.dsp/name", "panpot");
		m.declare("../spat/panpot.dsp/version", "1.0");
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "mixer");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
	}

	int getNumInputs() {
		return 8;
		
	}
	int getNumOutputs() {
		return 2;
		
	}
	int getInputRate(int channel) {
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
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		fVslider0 = (float)0.0f;
		fEntry0 = (float)0.0f;
		fCheckbox0 = (float)0.0f;
		fVslider1 = (float)0.0f;
		fEntry1 = (float)0.0f;
		fCheckbox1 = (float)0.0f;
		fVslider2 = (float)0.0f;
		fEntry2 = (float)0.0f;
		fCheckbox2 = (float)0.0f;
		fVslider3 = (float)0.0f;
		fEntry3 = (float)0.0f;
		fCheckbox3 = (float)0.0f;
		fVslider4 = (float)0.0f;
		fEntry4 = (float)0.0f;
		fCheckbox4 = (float)0.0f;
		fVslider5 = (float)0.0f;
		fEntry5 = (float)0.0f;
		fCheckbox5 = (float)0.0f;
		fVslider6 = (float)0.0f;
		fEntry6 = (float)0.0f;
		fCheckbox6 = (float)0.0f;
		fVslider7 = (float)0.0f;
		fEntry7 = (float)0.0f;
		fCheckbox7 = (float)0.0f;
		fVslider8 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec3[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec7[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec9[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec11[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec13[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec12[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec15[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec14[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec17[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec16[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec0[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec18[l18] = 0.0f;
			
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
		ui_interface.openHorizontalBox("mixer");
		ui_interface.openVerticalBox("Ch 0");
		ui_interface.declare("fEntry0", "1", "");
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.addNumEntry("pan", new FaustVarAccess() {
				public String getId() { return "fEntry0"; }
				public void set(float val) { fEntry0 = val; }
				public float get() { return (float)fEntry0; }
			}
			, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider1", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.declare("fVbargraph0", "2", "");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee8351b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph0"; }
				public void set(float val) { fVbargraph0 = val; }
				public float get() { return (float)fVbargraph0; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 1");
		ui_interface.declare("fEntry1", "1", "");
		ui_interface.declare("fEntry1", "style", "knob");
		ui_interface.addNumEntry("pan", new FaustVarAccess() {
				public String getId() { return "fEntry1"; }
				public void set(float val) { fEntry1 = val; }
				public float get() { return (float)fEntry1; }
			}
			, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider2", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.declare("fVbargraph1", "2", "");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee83f2b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", new FaustVarAccess() {
				public String getId() { return "fCheckbox1"; }
				public void set(float val) { fCheckbox1 = val; }
				public float get() { return (float)fCheckbox1; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 2");
		ui_interface.declare("fEntry2", "1", "");
		ui_interface.declare("fEntry2", "style", "knob");
		ui_interface.addNumEntry("pan", new FaustVarAccess() {
				public String getId() { return "fEntry2"; }
				public void set(float val) { fEntry2 = val; }
				public float get() { return (float)fEntry2; }
			}
			, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider3", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.declare("fVbargraph2", "2", "");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee8497f0", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", new FaustVarAccess() {
				public String getId() { return "fCheckbox2"; }
				public void set(float val) { fCheckbox2 = val; }
				public float get() { return (float)fCheckbox2; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 3");
		ui_interface.declare("fEntry3", "1", "");
		ui_interface.declare("fEntry3", "style", "knob");
		ui_interface.addNumEntry("pan", new FaustVarAccess() {
				public String getId() { return "fEntry3"; }
				public void set(float val) { fEntry3 = val; }
				public float get() { return (float)fEntry3; }
			}
			, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider4", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider4"; }
				public void set(float val) { fVslider4 = val; }
				public float get() { return (float)fVslider4; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.declare("fVbargraph3", "2", "");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee853ff0", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", new FaustVarAccess() {
				public String getId() { return "fCheckbox3"; }
				public void set(float val) { fCheckbox3 = val; }
				public float get() { return (float)fCheckbox3; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 4");
		ui_interface.declare("fEntry4", "1", "");
		ui_interface.declare("fEntry4", "style", "knob");
		ui_interface.addNumEntry("pan", new FaustVarAccess() {
				public String getId() { return "fEntry4"; }
				public void set(float val) { fEntry4 = val; }
				public float get() { return (float)fEntry4; }
			}
			, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider5", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.declare("fVbargraph4", "2", "");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee85eab0", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", new FaustVarAccess() {
				public String getId() { return "fCheckbox4"; }
				public void set(float val) { fCheckbox4 = val; }
				public float get() { return (float)fCheckbox4; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 5");
		ui_interface.declare("fEntry5", "1", "");
		ui_interface.declare("fEntry5", "style", "knob");
		ui_interface.addNumEntry("pan", new FaustVarAccess() {
				public String getId() { return "fEntry5"; }
				public void set(float val) { fEntry5 = val; }
				public float get() { return (float)fEntry5; }
			}
			, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider6", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.declare("fVbargraph5", "2", "");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee869830", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", new FaustVarAccess() {
				public String getId() { return "fCheckbox5"; }
				public void set(float val) { fCheckbox5 = val; }
				public float get() { return (float)fCheckbox5; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 6");
		ui_interface.declare("fEntry6", "1", "");
		ui_interface.declare("fEntry6", "style", "knob");
		ui_interface.addNumEntry("pan", new FaustVarAccess() {
				public String getId() { return "fEntry6"; }
				public void set(float val) { fEntry6 = val; }
				public float get() { return (float)fEntry6; }
			}
			, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider7", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.declare("fVbargraph6", "2", "");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee874870", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", new FaustVarAccess() {
				public String getId() { return "fCheckbox6"; }
				public void set(float val) { fCheckbox6 = val; }
				public float get() { return (float)fCheckbox6; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 7");
		ui_interface.declare("fEntry7", "1", "");
		ui_interface.declare("fEntry7", "style", "knob");
		ui_interface.addNumEntry("pan", new FaustVarAccess() {
				public String getId() { return "fEntry7"; }
				public void set(float val) { fEntry7 = val; }
				public float get() { return (float)fEntry7; }
			}
			, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider8", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.declare("fVbargraph7", "2", "");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee87cad0", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", new FaustVarAccess() {
				public String getId() { return "fCheckbox7"; }
				public void set(float val) { fCheckbox7 = val; }
				public float get() { return (float)fCheckbox7; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("stereo out");
		ui_interface.openVerticalBox("L");
		ui_interface.declare("fVbargraph8", "2", "");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee8809b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph8"; }
				public void set(float val) { fVbargraph8 = val; }
				public float get() { return (float)fVbargraph8; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("R");
		ui_interface.declare("fVbargraph9", "2", "");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7f9bee889f50", new FaustVarAccess() {
				public String getId() { return "fVbargraph9"; }
				public void set(float val) { fVbargraph9 = val; }
				public float get() { return (float)fVbargraph9; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		ui_interface.declare("fVslider0", "1", "");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] input2 = inputs[2];
		float[] input3 = inputs[3];
		float[] input4 = inputs[4];
		float[] input5 = inputs[5];
		float[] input6 = inputs[6];
		float[] input7 = inputs[7];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0)));
		float fSlow1 = (0.00555555569f * (fEntry0 + -90.0f));
		float fSlow2 = (float)java.lang.Math.sqrt((0.0f - fSlow1));
		float fSlow3 = (1.0f - fCheckbox0);
		float fSlow4 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider1)));
		float fSlow5 = (0.00555555569f * (fEntry1 + -90.0f));
		float fSlow6 = (float)java.lang.Math.sqrt((0.0f - fSlow5));
		float fSlow7 = (1.0f - fCheckbox1);
		float fSlow8 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider2)));
		float fSlow9 = (0.00555555569f * (fEntry2 + -90.0f));
		float fSlow10 = (float)java.lang.Math.sqrt((0.0f - fSlow9));
		float fSlow11 = (1.0f - fCheckbox2);
		float fSlow12 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider3)));
		float fSlow13 = (0.00555555569f * (fEntry3 + -90.0f));
		float fSlow14 = (float)java.lang.Math.sqrt((0.0f - fSlow13));
		float fSlow15 = (1.0f - fCheckbox3);
		float fSlow16 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider4)));
		float fSlow17 = (0.00555555569f * (fEntry4 + -90.0f));
		float fSlow18 = (float)java.lang.Math.sqrt((0.0f - fSlow17));
		float fSlow19 = (1.0f - fCheckbox4);
		float fSlow20 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider5)));
		float fSlow21 = (0.00555555569f * (fEntry5 + -90.0f));
		float fSlow22 = (float)java.lang.Math.sqrt((0.0f - fSlow21));
		float fSlow23 = (1.0f - fCheckbox5);
		float fSlow24 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider6)));
		float fSlow25 = (0.00555555569f * (fEntry6 + -90.0f));
		float fSlow26 = (float)java.lang.Math.sqrt((0.0f - fSlow25));
		float fSlow27 = (1.0f - fCheckbox6);
		float fSlow28 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider7)));
		float fSlow29 = (0.00555555569f * (fEntry7 + -90.0f));
		float fSlow30 = (float)java.lang.Math.sqrt((0.0f - fSlow29));
		float fSlow31 = (1.0f - fCheckbox7);
		float fSlow32 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider8)));
		float fSlow33 = (float)java.lang.Math.sqrt((fSlow1 + 1.0f));
		float fSlow34 = (float)java.lang.Math.sqrt((fSlow5 + 1.0f));
		float fSlow35 = (float)java.lang.Math.sqrt((fSlow9 + 1.0f));
		float fSlow36 = (float)java.lang.Math.sqrt((fSlow13 + 1.0f));
		float fSlow37 = (float)java.lang.Math.sqrt((fSlow17 + 1.0f));
		float fSlow38 = (float)java.lang.Math.sqrt((fSlow21 + 1.0f));
		float fSlow39 = (float)java.lang.Math.sqrt((fSlow25 + 1.0f));
		float fSlow40 = (float)java.lang.Math.sqrt((fSlow29 + 1.0f));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow0 + (0.999000013f * fRec1[1]));
			fRec3[0] = (fSlow4 + (0.999000013f * fRec3[1]));
			float fTemp0 = (fSlow3 * (fRec3[0] * input0[i]));
			fRec2[0] = (float)java.lang.Math.max((fRec2[1] - fConst0), (float)java.lang.Math.abs(fTemp0));
			fVbargraph0 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec2[0])));
			fRec5[0] = (fSlow8 + (0.999000013f * fRec5[1]));
			float fTemp1 = (fSlow7 * (fRec5[0] * input1[i]));
			fRec4[0] = (float)java.lang.Math.max((fRec4[1] - fConst0), (float)java.lang.Math.abs(fTemp1));
			fVbargraph1 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec4[0])));
			fRec7[0] = (fSlow12 + (0.999000013f * fRec7[1]));
			float fTemp2 = (fSlow11 * (fRec7[0] * input2[i]));
			fRec6[0] = (float)java.lang.Math.max((fRec6[1] - fConst0), (float)java.lang.Math.abs(fTemp2));
			fVbargraph2 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec6[0])));
			fRec9[0] = (fSlow16 + (0.999000013f * fRec9[1]));
			float fTemp3 = (fSlow15 * (fRec9[0] * input3[i]));
			fRec8[0] = (float)java.lang.Math.max((fRec8[1] - fConst0), (float)java.lang.Math.abs(fTemp3));
			fVbargraph3 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec8[0])));
			fRec11[0] = (fSlow20 + (0.999000013f * fRec11[1]));
			float fTemp4 = (fSlow19 * (fRec11[0] * input4[i]));
			fRec10[0] = (float)java.lang.Math.max((fRec10[1] - fConst0), (float)java.lang.Math.abs(fTemp4));
			fVbargraph4 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec10[0])));
			fRec13[0] = (fSlow24 + (0.999000013f * fRec13[1]));
			float fTemp5 = (fSlow23 * (fRec13[0] * input5[i]));
			fRec12[0] = (float)java.lang.Math.max((fRec12[1] - fConst0), (float)java.lang.Math.abs(fTemp5));
			fVbargraph5 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec12[0])));
			fRec15[0] = (fSlow28 + (0.999000013f * fRec15[1]));
			float fTemp6 = (fSlow27 * (fRec15[0] * input6[i]));
			fRec14[0] = (float)java.lang.Math.max((fRec14[1] - fConst0), (float)java.lang.Math.abs(fTemp6));
			fVbargraph6 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec14[0])));
			fRec17[0] = (fSlow32 + (0.999000013f * fRec17[1]));
			float fTemp7 = (fSlow31 * (fRec17[0] * input7[i]));
			fRec16[0] = (float)java.lang.Math.max((fRec16[1] - fConst0), (float)java.lang.Math.abs(fTemp7));
			fVbargraph7 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec16[0])));
			float fTemp8 = (fRec1[0] * ((((((((fSlow2 * fTemp0) + (fSlow6 * fTemp1)) + (fSlow10 * fTemp2)) + (fSlow14 * fTemp3)) + (fSlow18 * fTemp4)) + (fSlow22 * fTemp5)) + (fSlow26 * fTemp6)) + (fSlow30 * fTemp7)));
			fRec0[0] = (float)java.lang.Math.max((fRec0[1] - fConst0), (float)java.lang.Math.abs(fTemp8));
			fVbargraph8 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec0[0])));
			output0[i] = fTemp8;
			float fTemp9 = (fRec1[0] * ((((((((fSlow33 * fTemp0) + (fSlow34 * fTemp1)) + (fSlow35 * fTemp2)) + (fSlow36 * fTemp3)) + (fSlow37 * fTemp4)) + (fSlow38 * fTemp5)) + (fSlow39 * fTemp6)) + (fSlow40 * fTemp7)));
			fRec18[0] = (float)java.lang.Math.max((fRec18[1] - fConst0), (float)java.lang.Math.abs(fTemp9));
			fVbargraph9 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec18[0])));
			output1[i] = fTemp9;
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec0[1] = fRec0[0];
			fRec18[1] = fRec18[0];
			
		}
		
	}
	
};

