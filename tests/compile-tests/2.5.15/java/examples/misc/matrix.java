/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "matrix"
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
	float fVslider11;
	float fVslider12;
	float fVslider13;
	float fVslider14;
	float fVslider15;
	float fVslider16;
	float fVslider17;
	float fVslider18;
	float fVslider19;
	float fVslider20;
	float fVslider21;
	float fVslider22;
	float fVslider23;
	float fVslider24;
	float fVslider25;
	float fVslider26;
	float fVslider27;
	float fVslider28;
	float fVslider29;
	float fVslider30;
	float fVslider31;
	float fVslider32;
	float fVslider33;
	float fVslider34;
	float fVslider35;
	float fVslider36;
	float fVslider37;
	float fVslider38;
	float fVslider39;
	float fVslider40;
	float fVslider41;
	float fVslider42;
	float fVslider43;
	float fVslider44;
	float fVslider45;
	float fVslider46;
	float fVslider47;
	float fVslider48;
	float fVslider49;
	float fVslider50;
	float fVslider51;
	float fVslider52;
	float fVslider53;
	float fVslider54;
	float fVslider55;
	float fVslider56;
	float fVslider57;
	float fVslider58;
	float fVslider59;
	float fVslider60;
	float fVslider61;
	float fVslider62;
	float fVslider63;
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("license", "BSD");
		m.declare("name", "matrix");
		m.declare("version", "1.0");
	}

	int getNumInputs() {
		return 8;
		
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
		fVslider0 = (float)-10.0f;
		fVslider1 = (float)-10.0f;
		fVslider2 = (float)-10.0f;
		fVslider3 = (float)-10.0f;
		fVslider4 = (float)-10.0f;
		fVslider5 = (float)-10.0f;
		fVslider6 = (float)-10.0f;
		fVslider7 = (float)-10.0f;
		fVslider8 = (float)-10.0f;
		fVslider9 = (float)-10.0f;
		fVslider10 = (float)-10.0f;
		fVslider11 = (float)-10.0f;
		fVslider12 = (float)-10.0f;
		fVslider13 = (float)-10.0f;
		fVslider14 = (float)-10.0f;
		fVslider15 = (float)-10.0f;
		fVslider16 = (float)-10.0f;
		fVslider17 = (float)-10.0f;
		fVslider18 = (float)-10.0f;
		fVslider19 = (float)-10.0f;
		fVslider20 = (float)-10.0f;
		fVslider21 = (float)-10.0f;
		fVslider22 = (float)-10.0f;
		fVslider23 = (float)-10.0f;
		fVslider24 = (float)-10.0f;
		fVslider25 = (float)-10.0f;
		fVslider26 = (float)-10.0f;
		fVslider27 = (float)-10.0f;
		fVslider28 = (float)-10.0f;
		fVslider29 = (float)-10.0f;
		fVslider30 = (float)-10.0f;
		fVslider31 = (float)-10.0f;
		fVslider32 = (float)-10.0f;
		fVslider33 = (float)-10.0f;
		fVslider34 = (float)-10.0f;
		fVslider35 = (float)-10.0f;
		fVslider36 = (float)-10.0f;
		fVslider37 = (float)-10.0f;
		fVslider38 = (float)-10.0f;
		fVslider39 = (float)-10.0f;
		fVslider40 = (float)-10.0f;
		fVslider41 = (float)-10.0f;
		fVslider42 = (float)-10.0f;
		fVslider43 = (float)-10.0f;
		fVslider44 = (float)-10.0f;
		fVslider45 = (float)-10.0f;
		fVslider46 = (float)-10.0f;
		fVslider47 = (float)-10.0f;
		fVslider48 = (float)-10.0f;
		fVslider49 = (float)-10.0f;
		fVslider50 = (float)-10.0f;
		fVslider51 = (float)-10.0f;
		fVslider52 = (float)-10.0f;
		fVslider53 = (float)-10.0f;
		fVslider54 = (float)-10.0f;
		fVslider55 = (float)-10.0f;
		fVslider56 = (float)-10.0f;
		fVslider57 = (float)-10.0f;
		fVslider58 = (float)-10.0f;
		fVslider59 = (float)-10.0f;
		fVslider60 = (float)-10.0f;
		fVslider61 = (float)-10.0f;
		fVslider62 = (float)-10.0f;
		fVslider63 = (float)-10.0f;
		
	}
	
	public void instanceClear() {
		
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
		ui_interface.openTabBox("Matrix 8 x 8");
		ui_interface.openHorizontalBox("Output 0");
		ui_interface.addVerticalSlider("Input 0", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 1", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 2", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 3", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 4", new FaustVarAccess() {
				public String getId() { return "fVslider4"; }
				public void set(float val) { fVslider4 = val; }
				public float get() { return (float)fVslider4; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 5", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 6", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 7", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 1");
		ui_interface.addVerticalSlider("Input 0", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 1", new FaustVarAccess() {
				public String getId() { return "fVslider9"; }
				public void set(float val) { fVslider9 = val; }
				public float get() { return (float)fVslider9; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 2", new FaustVarAccess() {
				public String getId() { return "fVslider10"; }
				public void set(float val) { fVslider10 = val; }
				public float get() { return (float)fVslider10; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 3", new FaustVarAccess() {
				public String getId() { return "fVslider11"; }
				public void set(float val) { fVslider11 = val; }
				public float get() { return (float)fVslider11; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 4", new FaustVarAccess() {
				public String getId() { return "fVslider12"; }
				public void set(float val) { fVslider12 = val; }
				public float get() { return (float)fVslider12; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 5", new FaustVarAccess() {
				public String getId() { return "fVslider13"; }
				public void set(float val) { fVslider13 = val; }
				public float get() { return (float)fVslider13; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 6", new FaustVarAccess() {
				public String getId() { return "fVslider14"; }
				public void set(float val) { fVslider14 = val; }
				public float get() { return (float)fVslider14; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 7", new FaustVarAccess() {
				public String getId() { return "fVslider15"; }
				public void set(float val) { fVslider15 = val; }
				public float get() { return (float)fVslider15; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 2");
		ui_interface.addVerticalSlider("Input 0", new FaustVarAccess() {
				public String getId() { return "fVslider16"; }
				public void set(float val) { fVslider16 = val; }
				public float get() { return (float)fVslider16; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 1", new FaustVarAccess() {
				public String getId() { return "fVslider17"; }
				public void set(float val) { fVslider17 = val; }
				public float get() { return (float)fVslider17; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 2", new FaustVarAccess() {
				public String getId() { return "fVslider18"; }
				public void set(float val) { fVslider18 = val; }
				public float get() { return (float)fVslider18; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 3", new FaustVarAccess() {
				public String getId() { return "fVslider19"; }
				public void set(float val) { fVslider19 = val; }
				public float get() { return (float)fVslider19; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 4", new FaustVarAccess() {
				public String getId() { return "fVslider20"; }
				public void set(float val) { fVslider20 = val; }
				public float get() { return (float)fVslider20; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 5", new FaustVarAccess() {
				public String getId() { return "fVslider21"; }
				public void set(float val) { fVslider21 = val; }
				public float get() { return (float)fVslider21; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 6", new FaustVarAccess() {
				public String getId() { return "fVslider22"; }
				public void set(float val) { fVslider22 = val; }
				public float get() { return (float)fVslider22; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 7", new FaustVarAccess() {
				public String getId() { return "fVslider23"; }
				public void set(float val) { fVslider23 = val; }
				public float get() { return (float)fVslider23; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 3");
		ui_interface.addVerticalSlider("Input 0", new FaustVarAccess() {
				public String getId() { return "fVslider24"; }
				public void set(float val) { fVslider24 = val; }
				public float get() { return (float)fVslider24; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 1", new FaustVarAccess() {
				public String getId() { return "fVslider25"; }
				public void set(float val) { fVslider25 = val; }
				public float get() { return (float)fVslider25; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 2", new FaustVarAccess() {
				public String getId() { return "fVslider26"; }
				public void set(float val) { fVslider26 = val; }
				public float get() { return (float)fVslider26; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 3", new FaustVarAccess() {
				public String getId() { return "fVslider27"; }
				public void set(float val) { fVslider27 = val; }
				public float get() { return (float)fVslider27; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 4", new FaustVarAccess() {
				public String getId() { return "fVslider28"; }
				public void set(float val) { fVslider28 = val; }
				public float get() { return (float)fVslider28; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 5", new FaustVarAccess() {
				public String getId() { return "fVslider29"; }
				public void set(float val) { fVslider29 = val; }
				public float get() { return (float)fVslider29; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 6", new FaustVarAccess() {
				public String getId() { return "fVslider30"; }
				public void set(float val) { fVslider30 = val; }
				public float get() { return (float)fVslider30; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 7", new FaustVarAccess() {
				public String getId() { return "fVslider31"; }
				public void set(float val) { fVslider31 = val; }
				public float get() { return (float)fVslider31; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 4");
		ui_interface.addVerticalSlider("Input 0", new FaustVarAccess() {
				public String getId() { return "fVslider32"; }
				public void set(float val) { fVslider32 = val; }
				public float get() { return (float)fVslider32; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 1", new FaustVarAccess() {
				public String getId() { return "fVslider33"; }
				public void set(float val) { fVslider33 = val; }
				public float get() { return (float)fVslider33; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 2", new FaustVarAccess() {
				public String getId() { return "fVslider34"; }
				public void set(float val) { fVslider34 = val; }
				public float get() { return (float)fVslider34; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 3", new FaustVarAccess() {
				public String getId() { return "fVslider35"; }
				public void set(float val) { fVslider35 = val; }
				public float get() { return (float)fVslider35; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 4", new FaustVarAccess() {
				public String getId() { return "fVslider36"; }
				public void set(float val) { fVslider36 = val; }
				public float get() { return (float)fVslider36; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 5", new FaustVarAccess() {
				public String getId() { return "fVslider37"; }
				public void set(float val) { fVslider37 = val; }
				public float get() { return (float)fVslider37; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 6", new FaustVarAccess() {
				public String getId() { return "fVslider38"; }
				public void set(float val) { fVslider38 = val; }
				public float get() { return (float)fVslider38; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 7", new FaustVarAccess() {
				public String getId() { return "fVslider39"; }
				public void set(float val) { fVslider39 = val; }
				public float get() { return (float)fVslider39; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 5");
		ui_interface.addVerticalSlider("Input 0", new FaustVarAccess() {
				public String getId() { return "fVslider40"; }
				public void set(float val) { fVslider40 = val; }
				public float get() { return (float)fVslider40; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 1", new FaustVarAccess() {
				public String getId() { return "fVslider41"; }
				public void set(float val) { fVslider41 = val; }
				public float get() { return (float)fVslider41; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 2", new FaustVarAccess() {
				public String getId() { return "fVslider42"; }
				public void set(float val) { fVslider42 = val; }
				public float get() { return (float)fVslider42; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 3", new FaustVarAccess() {
				public String getId() { return "fVslider43"; }
				public void set(float val) { fVslider43 = val; }
				public float get() { return (float)fVslider43; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 4", new FaustVarAccess() {
				public String getId() { return "fVslider44"; }
				public void set(float val) { fVslider44 = val; }
				public float get() { return (float)fVslider44; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 5", new FaustVarAccess() {
				public String getId() { return "fVslider45"; }
				public void set(float val) { fVslider45 = val; }
				public float get() { return (float)fVslider45; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 6", new FaustVarAccess() {
				public String getId() { return "fVslider46"; }
				public void set(float val) { fVslider46 = val; }
				public float get() { return (float)fVslider46; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 7", new FaustVarAccess() {
				public String getId() { return "fVslider47"; }
				public void set(float val) { fVslider47 = val; }
				public float get() { return (float)fVslider47; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 6");
		ui_interface.addVerticalSlider("Input 0", new FaustVarAccess() {
				public String getId() { return "fVslider48"; }
				public void set(float val) { fVslider48 = val; }
				public float get() { return (float)fVslider48; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 1", new FaustVarAccess() {
				public String getId() { return "fVslider49"; }
				public void set(float val) { fVslider49 = val; }
				public float get() { return (float)fVslider49; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 2", new FaustVarAccess() {
				public String getId() { return "fVslider50"; }
				public void set(float val) { fVslider50 = val; }
				public float get() { return (float)fVslider50; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 3", new FaustVarAccess() {
				public String getId() { return "fVslider51"; }
				public void set(float val) { fVslider51 = val; }
				public float get() { return (float)fVslider51; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 4", new FaustVarAccess() {
				public String getId() { return "fVslider52"; }
				public void set(float val) { fVslider52 = val; }
				public float get() { return (float)fVslider52; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 5", new FaustVarAccess() {
				public String getId() { return "fVslider53"; }
				public void set(float val) { fVslider53 = val; }
				public float get() { return (float)fVslider53; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 6", new FaustVarAccess() {
				public String getId() { return "fVslider54"; }
				public void set(float val) { fVslider54 = val; }
				public float get() { return (float)fVslider54; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 7", new FaustVarAccess() {
				public String getId() { return "fVslider55"; }
				public void set(float val) { fVslider55 = val; }
				public float get() { return (float)fVslider55; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 7");
		ui_interface.addVerticalSlider("Input 0", new FaustVarAccess() {
				public String getId() { return "fVslider56"; }
				public void set(float val) { fVslider56 = val; }
				public float get() { return (float)fVslider56; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 1", new FaustVarAccess() {
				public String getId() { return "fVslider57"; }
				public void set(float val) { fVslider57 = val; }
				public float get() { return (float)fVslider57; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 2", new FaustVarAccess() {
				public String getId() { return "fVslider58"; }
				public void set(float val) { fVslider58 = val; }
				public float get() { return (float)fVslider58; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 3", new FaustVarAccess() {
				public String getId() { return "fVslider59"; }
				public void set(float val) { fVslider59 = val; }
				public float get() { return (float)fVslider59; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 4", new FaustVarAccess() {
				public String getId() { return "fVslider60"; }
				public void set(float val) { fVslider60 = val; }
				public float get() { return (float)fVslider60; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 5", new FaustVarAccess() {
				public String getId() { return "fVslider61"; }
				public void set(float val) { fVslider61 = val; }
				public float get() { return (float)fVslider61; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 6", new FaustVarAccess() {
				public String getId() { return "fVslider62"; }
				public void set(float val) { fVslider62 = val; }
				public float get() { return (float)fVslider62; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.addVerticalSlider("Input 7", new FaustVarAccess() {
				public String getId() { return "fVslider63"; }
				public void set(float val) { fVslider63 = val; }
				public float get() { return (float)fVslider63; }
			}
			, -10.0f, -96.0f, 4.0f, 0.100000001f);
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
		float[] output2 = outputs[2];
		float[] output3 = outputs[3];
		float[] output4 = outputs[4];
		float[] output5 = outputs[5];
		float[] output6 = outputs[6];
		float[] output7 = outputs[7];
		float fSlow0 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0));
		float fSlow1 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider1));
		float fSlow2 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider2));
		float fSlow3 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider3));
		float fSlow4 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider4));
		float fSlow5 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider5));
		float fSlow6 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider6));
		float fSlow7 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider7));
		float fSlow8 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider8));
		float fSlow9 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider9));
		float fSlow10 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider10));
		float fSlow11 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider11));
		float fSlow12 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider12));
		float fSlow13 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider13));
		float fSlow14 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider14));
		float fSlow15 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider15));
		float fSlow16 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider16));
		float fSlow17 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider17));
		float fSlow18 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider18));
		float fSlow19 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider19));
		float fSlow20 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider20));
		float fSlow21 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider21));
		float fSlow22 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider22));
		float fSlow23 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider23));
		float fSlow24 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider24));
		float fSlow25 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider25));
		float fSlow26 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider26));
		float fSlow27 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider27));
		float fSlow28 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider28));
		float fSlow29 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider29));
		float fSlow30 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider30));
		float fSlow31 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider31));
		float fSlow32 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider32));
		float fSlow33 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider33));
		float fSlow34 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider34));
		float fSlow35 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider35));
		float fSlow36 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider36));
		float fSlow37 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider37));
		float fSlow38 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider38));
		float fSlow39 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider39));
		float fSlow40 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider40));
		float fSlow41 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider41));
		float fSlow42 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider42));
		float fSlow43 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider43));
		float fSlow44 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider44));
		float fSlow45 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider45));
		float fSlow46 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider46));
		float fSlow47 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider47));
		float fSlow48 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider48));
		float fSlow49 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider49));
		float fSlow50 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider50));
		float fSlow51 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider51));
		float fSlow52 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider52));
		float fSlow53 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider53));
		float fSlow54 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider54));
		float fSlow55 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider55));
		float fSlow56 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider56));
		float fSlow57 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider57));
		float fSlow58 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider58));
		float fSlow59 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider59));
		float fSlow60 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider60));
		float fSlow61 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider61));
		float fSlow62 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider62));
		float fSlow63 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider63));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			float fTemp1 = input1[i];
			float fTemp2 = input2[i];
			float fTemp3 = input3[i];
			float fTemp4 = input4[i];
			float fTemp5 = input5[i];
			float fTemp6 = input6[i];
			float fTemp7 = input7[i];
			output0[i] = ((((((((fSlow0 * fTemp0) + (fSlow1 * fTemp1)) + (fSlow2 * fTemp2)) + (fSlow3 * fTemp3)) + (fSlow4 * fTemp4)) + (fSlow5 * fTemp5)) + (fSlow6 * fTemp6)) + (fSlow7 * fTemp7));
			output1[i] = ((((((((fSlow8 * fTemp0) + (fSlow9 * fTemp1)) + (fSlow10 * fTemp2)) + (fSlow11 * fTemp3)) + (fSlow12 * fTemp4)) + (fSlow13 * fTemp5)) + (fSlow14 * fTemp6)) + (fSlow15 * fTemp7));
			output2[i] = ((((((((fSlow16 * fTemp0) + (fSlow17 * fTemp1)) + (fSlow18 * fTemp2)) + (fSlow19 * fTemp3)) + (fSlow20 * fTemp4)) + (fSlow21 * fTemp5)) + (fSlow22 * fTemp6)) + (fSlow23 * fTemp7));
			output3[i] = ((((((((fSlow24 * fTemp0) + (fSlow25 * fTemp1)) + (fSlow26 * fTemp2)) + (fSlow27 * fTemp3)) + (fSlow28 * fTemp4)) + (fSlow29 * fTemp5)) + (fSlow30 * fTemp6)) + (fSlow31 * fTemp7));
			output4[i] = ((((((((fSlow32 * fTemp0) + (fSlow33 * fTemp1)) + (fSlow34 * fTemp2)) + (fSlow35 * fTemp3)) + (fSlow36 * fTemp4)) + (fSlow37 * fTemp5)) + (fSlow38 * fTemp6)) + (fSlow39 * fTemp7));
			output5[i] = ((((((((fSlow40 * fTemp0) + (fSlow41 * fTemp1)) + (fSlow42 * fTemp2)) + (fSlow43 * fTemp3)) + (fSlow44 * fTemp4)) + (fSlow45 * fTemp5)) + (fSlow46 * fTemp6)) + (fSlow47 * fTemp7));
			output6[i] = ((((((((fSlow48 * fTemp0) + (fSlow49 * fTemp1)) + (fSlow50 * fTemp2)) + (fSlow51 * fTemp3)) + (fSlow52 * fTemp4)) + (fSlow53 * fTemp5)) + (fSlow54 * fTemp6)) + (fSlow55 * fTemp7));
			output7[i] = ((((((((fSlow56 * fTemp0) + (fSlow57 * fTemp1)) + (fSlow58 * fTemp2)) + (fSlow59 * fTemp3)) + (fSlow60 * fTemp4)) + (fSlow61 * fTemp5)) + (fSlow62 * fTemp6)) + (fSlow63 * fTemp7));
			
		}
		
	}
	
};

