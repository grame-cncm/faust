/* ------------------------------------------------------------
name: "bug-sampo-power"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	static int itbl0mydspSIG0[] = new int[128];
	int mydsp_faustpower2_i(int value) {
		return (value * value);
		
	}
	
	
	final class mydspSIG0 {
		
		int iRec0[] = new int[2];
		
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
			for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
				iRec0[l0] = 0;
				
			}
			
		}
		void fillmydspSIG0(int count, int[] output) {
			for (int i = 0; (i < count); i = (i + 1)) {
				iRec0[0] = (iRec0[1] + 1);
				output[i] = mydspSIG0_faustpower2_i(iRec0[0]);
				iRec0[1] = iRec0[0];
				
			}
			
		}
	};

	mydspSIG0 newmydspSIG0() {return new mydspSIG0(); }
	void deletemydspSIG0(mydspSIG0 dsp) {}
	
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("name", "bug-sampo-power");
	}

	int getNumInputs() {
		return 1;
		
	}
	int getNumOutputs() {
		return 1;
		
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
		sig0.fillmydspSIG0(128, itbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		
	}
	
	public void instanceResetUserInterface() {
		
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
		ui_interface.openVerticalBox("bug-sampo-power");
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		for (int i = 0; (i < count); i = (i + 1)) {
			output0[i] = (float)mydsp_faustpower2_i(itbl0mydspSIG0[(int)(127.0f * (float)java.lang.Math.abs(input0[i]))]);
			
		}
		
	}
	
};

