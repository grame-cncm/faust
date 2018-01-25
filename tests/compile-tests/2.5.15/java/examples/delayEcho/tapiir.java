/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "tapiir"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fVslider0;
	float fVslider1;
	float fVslider2;
	float fVslider3;
	float fVslider4;
	float fVslider5;
	float fVslider6;
	float fVslider7;
	float fVslider8;
	float fVslider9;
	float fVslider10;
	int IOTA;
	float fVec0[] = new float[1048576];
	int fSamplingFreq;
	float fConst0;
	float fVslider11;
	float fRec0[] = new float[2];
	float fVslider12;
	float fVslider13;
	float fVslider14;
	float fVslider15;
	float fVslider16;
	float fVslider17;
	float fVslider18;
	float fVslider19;
	float fVslider20;
	float fVec1[] = new float[1048576];
	float fVslider21;
	float fRec1[] = new float[2];
	float fVslider22;
	float fVslider23;
	float fVslider24;
	float fVslider25;
	float fVslider26;
	float fVslider27;
	float fVslider28;
	float fVslider29;
	float fVslider30;
	float fVec2[] = new float[1048576];
	float fVslider31;
	float fRec2[] = new float[2];
	float fVslider32;
	float fVslider33;
	float fVslider34;
	float fVslider35;
	float fVslider36;
	float fVslider37;
	float fVslider38;
	float fVslider39;
	float fVslider40;
	float fVec3[] = new float[1048576];
	float fVslider41;
	float fRec3[] = new float[2];
	float fVslider42;
	float fVslider43;
	float fVslider44;
	float fVslider45;
	float fVslider46;
	float fVslider47;
	float fVslider48;
	float fVslider49;
	float fVslider50;
	float fVec4[] = new float[1048576];
	float fVslider51;
	float fRec4[] = new float[2];
	float fVslider52;
	float fVslider53;
	float fVslider54;
	float fVslider55;
	float fVslider56;
	float fVslider57;
	float fVslider58;
	float fVslider59;
	float fVslider60;
	float fVec5[] = new float[1048576];
	float fVslider61;
	float fRec5[] = new float[2];
	float fVslider62;
	float fVslider63;
	float fVslider64;
	float fVslider65;
	float fVslider66;
	float fVslider67;
	float fVslider68;
	float fVslider69;
	float fVslider70;
	float fVslider71;
	float fVslider72;
	float fVslider73;
	float fVslider74;
	float fVslider75;
	float fVslider76;
	float fVslider77;
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "tapiir");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
	}

	int getNumInputs() {
		return 2;
		
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
		fConst0 = (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq));
		
	}
	
	public void instanceResetUserInterface() {
		fVslider0 = (float)1.0f;
		fVslider1 = (float)0.0f;
		fVslider2 = (float)1.0f;
		fVslider3 = (float)0.0f;
		fVslider4 = (float)0.0f;
		fVslider5 = (float)0.0f;
		fVslider6 = (float)0.0f;
		fVslider7 = (float)0.0f;
		fVslider8 = (float)0.0f;
		fVslider9 = (float)1.0f;
		fVslider10 = (float)1.0f;
		fVslider11 = (float)0.0f;
		fVslider12 = (float)1.0f;
		fVslider13 = (float)0.0f;
		fVslider14 = (float)0.0f;
		fVslider15 = (float)0.0f;
		fVslider16 = (float)0.0f;
		fVslider17 = (float)0.0f;
		fVslider18 = (float)0.0f;
		fVslider19 = (float)1.0f;
		fVslider20 = (float)1.0f;
		fVslider21 = (float)0.0f;
		fVslider22 = (float)1.0f;
		fVslider23 = (float)0.0f;
		fVslider24 = (float)0.0f;
		fVslider25 = (float)0.0f;
		fVslider26 = (float)0.0f;
		fVslider27 = (float)0.0f;
		fVslider28 = (float)0.0f;
		fVslider29 = (float)1.0f;
		fVslider30 = (float)1.0f;
		fVslider31 = (float)0.0f;
		fVslider32 = (float)1.0f;
		fVslider33 = (float)0.0f;
		fVslider34 = (float)0.0f;
		fVslider35 = (float)0.0f;
		fVslider36 = (float)0.0f;
		fVslider37 = (float)0.0f;
		fVslider38 = (float)0.0f;
		fVslider39 = (float)1.0f;
		fVslider40 = (float)1.0f;
		fVslider41 = (float)0.0f;
		fVslider42 = (float)1.0f;
		fVslider43 = (float)0.0f;
		fVslider44 = (float)0.0f;
		fVslider45 = (float)0.0f;
		fVslider46 = (float)0.0f;
		fVslider47 = (float)0.0f;
		fVslider48 = (float)0.0f;
		fVslider49 = (float)1.0f;
		fVslider50 = (float)1.0f;
		fVslider51 = (float)0.0f;
		fVslider52 = (float)1.0f;
		fVslider53 = (float)0.0f;
		fVslider54 = (float)0.0f;
		fVslider55 = (float)0.0f;
		fVslider56 = (float)0.0f;
		fVslider57 = (float)0.0f;
		fVslider58 = (float)0.0f;
		fVslider59 = (float)1.0f;
		fVslider60 = (float)1.0f;
		fVslider61 = (float)0.0f;
		fVslider62 = (float)0.0f;
		fVslider63 = (float)0.0f;
		fVslider64 = (float)0.0f;
		fVslider65 = (float)0.0f;
		fVslider66 = (float)0.0f;
		fVslider67 = (float)1.0f;
		fVslider68 = (float)1.0f;
		fVslider69 = (float)1.0f;
		fVslider70 = (float)0.0f;
		fVslider71 = (float)0.0f;
		fVslider72 = (float)0.0f;
		fVslider73 = (float)0.0f;
		fVslider74 = (float)0.0f;
		fVslider75 = (float)0.0f;
		fVslider76 = (float)1.0f;
		fVslider77 = (float)1.0f;
		
	}
	
	public void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 1048576); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 1048576); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 1048576); l4 = (l4 + 1)) {
			fVec2[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 1048576); l6 = (l6 + 1)) {
			fVec3[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec3[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 1048576); l8 = (l8 + 1)) {
			fVec4[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec4[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 1048576); l10 = (l10 + 1)) {
			fVec5[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec5[l11] = 0.0f;
			
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
		ui_interface.openVerticalBox("Tapiir");
		ui_interface.openTabBox("0x00");
		ui_interface.openHorizontalBox("Tap 0");
		ui_interface.addVerticalSlider("delay (sec)", new FaustVarAccess() {
				public String getId() { return "fVslider11"; }
				public void set(float val) { fVslider11 = val; }
				public float get() { return (float)fVslider11; }
			}
			, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 0", new FaustVarAccess() {
				public String getId() { return "fVslider9"; }
				public void set(float val) { fVslider9 = val; }
				public float get() { return (float)fVslider9; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 1", new FaustVarAccess() {
				public String getId() { return "fVslider10"; }
				public void set(float val) { fVslider10 = val; }
				public float get() { return (float)fVslider10; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 0", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 1", new FaustVarAccess() {
				public String getId() { return "fVslider4"; }
				public void set(float val) { fVslider4 = val; }
				public float get() { return (float)fVslider4; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 2", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 3", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 4", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 5", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 1");
		ui_interface.addVerticalSlider("delay (sec)", new FaustVarAccess() {
				public String getId() { return "fVslider21"; }
				public void set(float val) { fVslider21 = val; }
				public float get() { return (float)fVslider21; }
			}
			, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider12"; }
				public void set(float val) { fVslider12 = val; }
				public float get() { return (float)fVslider12; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 0", new FaustVarAccess() {
				public String getId() { return "fVslider19"; }
				public void set(float val) { fVslider19 = val; }
				public float get() { return (float)fVslider19; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 1", new FaustVarAccess() {
				public String getId() { return "fVslider20"; }
				public void set(float val) { fVslider20 = val; }
				public float get() { return (float)fVslider20; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 0", new FaustVarAccess() {
				public String getId() { return "fVslider13"; }
				public void set(float val) { fVslider13 = val; }
				public float get() { return (float)fVslider13; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 1", new FaustVarAccess() {
				public String getId() { return "fVslider14"; }
				public void set(float val) { fVslider14 = val; }
				public float get() { return (float)fVslider14; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 2", new FaustVarAccess() {
				public String getId() { return "fVslider15"; }
				public void set(float val) { fVslider15 = val; }
				public float get() { return (float)fVslider15; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 3", new FaustVarAccess() {
				public String getId() { return "fVslider16"; }
				public void set(float val) { fVslider16 = val; }
				public float get() { return (float)fVslider16; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 4", new FaustVarAccess() {
				public String getId() { return "fVslider17"; }
				public void set(float val) { fVslider17 = val; }
				public float get() { return (float)fVslider17; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 5", new FaustVarAccess() {
				public String getId() { return "fVslider18"; }
				public void set(float val) { fVslider18 = val; }
				public float get() { return (float)fVslider18; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 2");
		ui_interface.addVerticalSlider("delay (sec)", new FaustVarAccess() {
				public String getId() { return "fVslider31"; }
				public void set(float val) { fVslider31 = val; }
				public float get() { return (float)fVslider31; }
			}
			, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider22"; }
				public void set(float val) { fVslider22 = val; }
				public float get() { return (float)fVslider22; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 0", new FaustVarAccess() {
				public String getId() { return "fVslider29"; }
				public void set(float val) { fVslider29 = val; }
				public float get() { return (float)fVslider29; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 1", new FaustVarAccess() {
				public String getId() { return "fVslider30"; }
				public void set(float val) { fVslider30 = val; }
				public float get() { return (float)fVslider30; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 0", new FaustVarAccess() {
				public String getId() { return "fVslider23"; }
				public void set(float val) { fVslider23 = val; }
				public float get() { return (float)fVslider23; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 1", new FaustVarAccess() {
				public String getId() { return "fVslider24"; }
				public void set(float val) { fVslider24 = val; }
				public float get() { return (float)fVslider24; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 2", new FaustVarAccess() {
				public String getId() { return "fVslider25"; }
				public void set(float val) { fVslider25 = val; }
				public float get() { return (float)fVslider25; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 3", new FaustVarAccess() {
				public String getId() { return "fVslider26"; }
				public void set(float val) { fVslider26 = val; }
				public float get() { return (float)fVslider26; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 4", new FaustVarAccess() {
				public String getId() { return "fVslider27"; }
				public void set(float val) { fVslider27 = val; }
				public float get() { return (float)fVslider27; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 5", new FaustVarAccess() {
				public String getId() { return "fVslider28"; }
				public void set(float val) { fVslider28 = val; }
				public float get() { return (float)fVslider28; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 3");
		ui_interface.addVerticalSlider("delay (sec)", new FaustVarAccess() {
				public String getId() { return "fVslider41"; }
				public void set(float val) { fVslider41 = val; }
				public float get() { return (float)fVslider41; }
			}
			, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider32"; }
				public void set(float val) { fVslider32 = val; }
				public float get() { return (float)fVslider32; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 0", new FaustVarAccess() {
				public String getId() { return "fVslider39"; }
				public void set(float val) { fVslider39 = val; }
				public float get() { return (float)fVslider39; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 1", new FaustVarAccess() {
				public String getId() { return "fVslider40"; }
				public void set(float val) { fVslider40 = val; }
				public float get() { return (float)fVslider40; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 0", new FaustVarAccess() {
				public String getId() { return "fVslider33"; }
				public void set(float val) { fVslider33 = val; }
				public float get() { return (float)fVslider33; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 1", new FaustVarAccess() {
				public String getId() { return "fVslider34"; }
				public void set(float val) { fVslider34 = val; }
				public float get() { return (float)fVslider34; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 2", new FaustVarAccess() {
				public String getId() { return "fVslider35"; }
				public void set(float val) { fVslider35 = val; }
				public float get() { return (float)fVslider35; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 3", new FaustVarAccess() {
				public String getId() { return "fVslider36"; }
				public void set(float val) { fVslider36 = val; }
				public float get() { return (float)fVslider36; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 4", new FaustVarAccess() {
				public String getId() { return "fVslider37"; }
				public void set(float val) { fVslider37 = val; }
				public float get() { return (float)fVslider37; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 5", new FaustVarAccess() {
				public String getId() { return "fVslider38"; }
				public void set(float val) { fVslider38 = val; }
				public float get() { return (float)fVslider38; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 4");
		ui_interface.addVerticalSlider("delay (sec)", new FaustVarAccess() {
				public String getId() { return "fVslider51"; }
				public void set(float val) { fVslider51 = val; }
				public float get() { return (float)fVslider51; }
			}
			, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider42"; }
				public void set(float val) { fVslider42 = val; }
				public float get() { return (float)fVslider42; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 0", new FaustVarAccess() {
				public String getId() { return "fVslider49"; }
				public void set(float val) { fVslider49 = val; }
				public float get() { return (float)fVslider49; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 1", new FaustVarAccess() {
				public String getId() { return "fVslider50"; }
				public void set(float val) { fVslider50 = val; }
				public float get() { return (float)fVslider50; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 0", new FaustVarAccess() {
				public String getId() { return "fVslider43"; }
				public void set(float val) { fVslider43 = val; }
				public float get() { return (float)fVslider43; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 1", new FaustVarAccess() {
				public String getId() { return "fVslider44"; }
				public void set(float val) { fVslider44 = val; }
				public float get() { return (float)fVslider44; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 2", new FaustVarAccess() {
				public String getId() { return "fVslider45"; }
				public void set(float val) { fVslider45 = val; }
				public float get() { return (float)fVslider45; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 3", new FaustVarAccess() {
				public String getId() { return "fVslider46"; }
				public void set(float val) { fVslider46 = val; }
				public float get() { return (float)fVslider46; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 4", new FaustVarAccess() {
				public String getId() { return "fVslider47"; }
				public void set(float val) { fVslider47 = val; }
				public float get() { return (float)fVslider47; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 5", new FaustVarAccess() {
				public String getId() { return "fVslider48"; }
				public void set(float val) { fVslider48 = val; }
				public float get() { return (float)fVslider48; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 5");
		ui_interface.addVerticalSlider("delay (sec)", new FaustVarAccess() {
				public String getId() { return "fVslider61"; }
				public void set(float val) { fVslider61 = val; }
				public float get() { return (float)fVslider61; }
			}
			, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider52"; }
				public void set(float val) { fVslider52 = val; }
				public float get() { return (float)fVslider52; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 0", new FaustVarAccess() {
				public String getId() { return "fVslider59"; }
				public void set(float val) { fVslider59 = val; }
				public float get() { return (float)fVslider59; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 1", new FaustVarAccess() {
				public String getId() { return "fVslider60"; }
				public void set(float val) { fVslider60 = val; }
				public float get() { return (float)fVslider60; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 0", new FaustVarAccess() {
				public String getId() { return "fVslider53"; }
				public void set(float val) { fVslider53 = val; }
				public float get() { return (float)fVslider53; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 1", new FaustVarAccess() {
				public String getId() { return "fVslider54"; }
				public void set(float val) { fVslider54 = val; }
				public float get() { return (float)fVslider54; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 2", new FaustVarAccess() {
				public String getId() { return "fVslider55"; }
				public void set(float val) { fVslider55 = val; }
				public float get() { return (float)fVslider55; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 3", new FaustVarAccess() {
				public String getId() { return "fVslider56"; }
				public void set(float val) { fVslider56 = val; }
				public float get() { return (float)fVslider56; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 4", new FaustVarAccess() {
				public String getId() { return "fVslider57"; }
				public void set(float val) { fVslider57 = val; }
				public float get() { return (float)fVslider57; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 5", new FaustVarAccess() {
				public String getId() { return "fVslider58"; }
				public void set(float val) { fVslider58 = val; }
				public float get() { return (float)fVslider58; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.openVerticalBox("outputs");
		ui_interface.openHorizontalBox("output 0");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 0", new FaustVarAccess() {
				public String getId() { return "fVslider67"; }
				public void set(float val) { fVslider67 = val; }
				public float get() { return (float)fVslider67; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 1", new FaustVarAccess() {
				public String getId() { return "fVslider68"; }
				public void set(float val) { fVslider68 = val; }
				public float get() { return (float)fVslider68; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 0", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 1", new FaustVarAccess() {
				public String getId() { return "fVslider62"; }
				public void set(float val) { fVslider62 = val; }
				public float get() { return (float)fVslider62; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 2", new FaustVarAccess() {
				public String getId() { return "fVslider63"; }
				public void set(float val) { fVslider63 = val; }
				public float get() { return (float)fVslider63; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 3", new FaustVarAccess() {
				public String getId() { return "fVslider64"; }
				public void set(float val) { fVslider64 = val; }
				public float get() { return (float)fVslider64; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 4", new FaustVarAccess() {
				public String getId() { return "fVslider65"; }
				public void set(float val) { fVslider65 = val; }
				public float get() { return (float)fVslider65; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 5", new FaustVarAccess() {
				public String getId() { return "fVslider66"; }
				public void set(float val) { fVslider66 = val; }
				public float get() { return (float)fVslider66; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("output 1");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider69"; }
				public void set(float val) { fVslider69 = val; }
				public float get() { return (float)fVslider69; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 0", new FaustVarAccess() {
				public String getId() { return "fVslider76"; }
				public void set(float val) { fVslider76 = val; }
				public float get() { return (float)fVslider76; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("input 1", new FaustVarAccess() {
				public String getId() { return "fVslider77"; }
				public void set(float val) { fVslider77 = val; }
				public float get() { return (float)fVslider77; }
			}
			, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 0", new FaustVarAccess() {
				public String getId() { return "fVslider70"; }
				public void set(float val) { fVslider70 = val; }
				public float get() { return (float)fVslider70; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 1", new FaustVarAccess() {
				public String getId() { return "fVslider71"; }
				public void set(float val) { fVslider71 = val; }
				public float get() { return (float)fVslider71; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 2", new FaustVarAccess() {
				public String getId() { return "fVslider72"; }
				public void set(float val) { fVslider72 = val; }
				public float get() { return (float)fVslider72; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 3", new FaustVarAccess() {
				public String getId() { return "fVslider73"; }
				public void set(float val) { fVslider73 = val; }
				public float get() { return (float)fVslider73; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 4", new FaustVarAccess() {
				public String getId() { return "fVslider74"; }
				public void set(float val) { fVslider74 = val; }
				public float get() { return (float)fVslider74; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addVerticalSlider("tap 5", new FaustVarAccess() {
				public String getId() { return "fVslider75"; }
				public void set(float val) { fVslider75 = val; }
				public float get() { return (float)fVslider75; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fVslider0;
		float fSlow1 = fVslider1;
		float fSlow2 = fVslider2;
		float fSlow3 = fVslider3;
		float fSlow4 = fVslider4;
		float fSlow5 = fVslider5;
		float fSlow6 = fVslider6;
		float fSlow7 = fVslider7;
		float fSlow8 = fVslider8;
		float fSlow9 = fVslider9;
		float fSlow10 = fVslider10;
		int iSlow11 = (int)(float)java.lang.Math.min(524288.0f, (float)java.lang.Math.max(0.0f, (fConst0 * fVslider11)));
		float fSlow12 = fVslider12;
		float fSlow13 = fVslider13;
		float fSlow14 = fVslider14;
		float fSlow15 = fVslider15;
		float fSlow16 = fVslider16;
		float fSlow17 = fVslider17;
		float fSlow18 = fVslider18;
		float fSlow19 = fVslider19;
		float fSlow20 = fVslider20;
		int iSlow21 = (int)(float)java.lang.Math.min(524288.0f, (float)java.lang.Math.max(0.0f, (fConst0 * fVslider21)));
		float fSlow22 = fVslider22;
		float fSlow23 = fVslider23;
		float fSlow24 = fVslider24;
		float fSlow25 = fVslider25;
		float fSlow26 = fVslider26;
		float fSlow27 = fVslider27;
		float fSlow28 = fVslider28;
		float fSlow29 = fVslider29;
		float fSlow30 = fVslider30;
		int iSlow31 = (int)(float)java.lang.Math.min(524288.0f, (float)java.lang.Math.max(0.0f, (fConst0 * fVslider31)));
		float fSlow32 = fVslider32;
		float fSlow33 = fVslider33;
		float fSlow34 = fVslider34;
		float fSlow35 = fVslider35;
		float fSlow36 = fVslider36;
		float fSlow37 = fVslider37;
		float fSlow38 = fVslider38;
		float fSlow39 = fVslider39;
		float fSlow40 = fVslider40;
		int iSlow41 = (int)(float)java.lang.Math.min(524288.0f, (float)java.lang.Math.max(0.0f, (fConst0 * fVslider41)));
		float fSlow42 = fVslider42;
		float fSlow43 = fVslider43;
		float fSlow44 = fVslider44;
		float fSlow45 = fVslider45;
		float fSlow46 = fVslider46;
		float fSlow47 = fVslider47;
		float fSlow48 = fVslider48;
		float fSlow49 = fVslider49;
		float fSlow50 = fVslider50;
		int iSlow51 = (int)(float)java.lang.Math.min(524288.0f, (float)java.lang.Math.max(0.0f, (fConst0 * fVslider51)));
		float fSlow52 = fVslider52;
		float fSlow53 = fVslider53;
		float fSlow54 = fVslider54;
		float fSlow55 = fVslider55;
		float fSlow56 = fVslider56;
		float fSlow57 = fVslider57;
		float fSlow58 = fVslider58;
		float fSlow59 = fVslider59;
		float fSlow60 = fVslider60;
		int iSlow61 = (int)(float)java.lang.Math.min(524288.0f, (float)java.lang.Math.max(0.0f, (fConst0 * fVslider61)));
		float fSlow62 = fVslider62;
		float fSlow63 = fVslider63;
		float fSlow64 = fVslider64;
		float fSlow65 = fVslider65;
		float fSlow66 = fVslider66;
		float fSlow67 = fVslider67;
		float fSlow68 = fVslider68;
		float fSlow69 = fVslider69;
		float fSlow70 = fVslider70;
		float fSlow71 = fVslider71;
		float fSlow72 = fVslider72;
		float fSlow73 = fVslider73;
		float fSlow74 = fVslider74;
		float fSlow75 = fVslider75;
		float fSlow76 = fVslider76;
		float fSlow77 = fVslider77;
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			float fTemp1 = input1[i];
			fVec0[(IOTA & 1048575)] = (fSlow2 * ((((((((fSlow3 * fRec0[1]) + (fSlow4 * fRec1[1])) + (fSlow5 * fRec2[1])) + (fSlow6 * fRec3[1])) + (fSlow7 * fRec4[1])) + (fSlow8 * fRec5[1])) + (fSlow9 * fTemp0)) + (fSlow10 * fTemp1)));
			fRec0[0] = fVec0[((IOTA - iSlow11) & 1048575)];
			fVec1[(IOTA & 1048575)] = (fSlow12 * ((((((((fSlow13 * fRec0[1]) + (fSlow14 * fRec1[1])) + (fSlow15 * fRec2[1])) + (fSlow16 * fRec3[1])) + (fSlow17 * fRec4[1])) + (fSlow18 * fRec5[1])) + (fSlow19 * fTemp0)) + (fSlow20 * fTemp1)));
			fRec1[0] = fVec1[((IOTA - iSlow21) & 1048575)];
			fVec2[(IOTA & 1048575)] = (fSlow22 * ((((((((fSlow23 * fRec0[1]) + (fSlow24 * fRec1[1])) + (fSlow25 * fRec2[1])) + (fSlow26 * fRec3[1])) + (fSlow27 * fRec4[1])) + (fSlow28 * fRec5[1])) + (fSlow29 * fTemp0)) + (fSlow30 * fTemp1)));
			fRec2[0] = fVec2[((IOTA - iSlow31) & 1048575)];
			fVec3[(IOTA & 1048575)] = (fSlow32 * ((((((((fSlow33 * fRec0[1]) + (fSlow34 * fRec1[1])) + (fSlow35 * fRec2[1])) + (fSlow36 * fRec3[1])) + (fSlow37 * fRec4[1])) + (fSlow38 * fRec5[1])) + (fSlow39 * fTemp0)) + (fSlow40 * fTemp1)));
			fRec3[0] = fVec3[((IOTA - iSlow41) & 1048575)];
			fVec4[(IOTA & 1048575)] = (fSlow42 * ((((((((fSlow43 * fRec0[1]) + (fSlow44 * fRec1[1])) + (fSlow45 * fRec2[1])) + (fSlow46 * fRec3[1])) + (fSlow47 * fRec4[1])) + (fSlow48 * fRec5[1])) + (fSlow49 * fTemp0)) + (fSlow50 * fTemp1)));
			fRec4[0] = fVec4[((IOTA - iSlow51) & 1048575)];
			fVec5[(IOTA & 1048575)] = (fSlow52 * ((((((((fSlow53 * fRec0[1]) + (fSlow54 * fRec1[1])) + (fSlow55 * fRec2[1])) + (fSlow56 * fRec3[1])) + (fSlow57 * fRec4[1])) + (fSlow58 * fRec5[1])) + (fSlow59 * fTemp0)) + (fSlow60 * fTemp1)));
			fRec5[0] = fVec5[((IOTA - iSlow61) & 1048575)];
			output0[i] = (fSlow0 * ((((((((fSlow1 * fRec0[0]) + (fSlow62 * fRec1[0])) + (fSlow63 * fRec2[0])) + (fSlow64 * fRec3[0])) + (fSlow65 * fRec4[0])) + (fSlow66 * fRec5[0])) + (fSlow67 * fTemp0)) + (fSlow68 * fTemp1)));
			output1[i] = (fSlow69 * ((((((((fSlow70 * fRec0[0]) + (fSlow71 * fRec1[0])) + (fSlow72 * fRec2[0])) + (fSlow73 * fRec3[0])) + (fSlow74 * fRec4[0])) + (fSlow75 * fRec5[0])) + (fSlow76 * fTemp0)) + (fSlow77 * fTemp1)));
			IOTA = (IOTA + 1);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			
		}
		
	}
	
};

