class EQregaliaStereo
{
public:
	void setSampleRate(float sampleRate);
	void reset();
	void process(float *xL, float *xR, float *yL_out_, float *yR_out_, int nSamples);

	float getlow();
	void setlow(float value);
	float gethigh();
	void sethigh(float value);
	float getpeak();
	void setpeak(float value);

private:

	
	float EQregaliaStereo_extra_1 = 0.0f;
	float EQregaliaStereo_extra_3 = 0.0f;
	float EQregaliaStereo_extra_5 = 0.0f;
	float EQregaliaStereo_extra_6 = 0.0f;
	float a_3 = 0.0f;
	float EQregaliaStereo_extra_8 = 0.0f;
	float a_5 = 0.0f;
	float EQregaliaStereo_extra_10 = 0.0f;
	float a_7 = 0.0f;
	float EQregaliaStereo_extra_15 = 0.0f;
	float EQregaliaStereo_extra_16 = 0.0f;
	float EQregaliaStereo_extra_18 = 0.0f;
	float EQregaliaStereo_extra_20 = 0.0f;
	float EQregaliaStereo_extra_22 = 0.0f;
	float EQregaliaStereo_extra_23 = 0.0f;
	float a_10 = 0.0f;
	float EQregaliaStereo_extra_25 = 0.0f;
	float a_12 = 0.0f;
	float EQregaliaStereo_extra_27 = 0.0f;
	float a_14 = 0.0f;
	float EQregaliaStereo_extra_32 = 0.0f;
	float EQregaliaStereo_extra_33 = 0.0f;
	float _delayed_34 = 0.0f;
	float _delayed_35 = 0.0f;
	float _delayed_36 = 0.0f;
	float _delayed_37 = 0.0f;
	float _delayed_38 = 0.0f;
	float _delayed_39 = 0.0f;
	float _delayed_40 = 0.0f;
	float _delayed_41 = 0.0f;
	float _delayed_42 = 0.0f;
	float _delayed_43 = 0.0f;
	float _delayed_44 = 0.0f;
	float _delayed_45 = 0.0f;
	float _delayed_46 = 0.0f;
	float _delayed_47 = 0.0f;
	float _delayed_48 = 0.0f;
	float _delayed_49 = 0.0f;
	float _delayed_50 = 0.0f;
	float _delayed_51 = 0.0f;
	float _delayed_52 = 0.0f;
	float _delayed_53 = 0.0f;
	float low = 1.0f;
	float high = 0.0f;
	float peak = 0.0f;

	
	float low_z1;
	char low_CHANGED;
	
	float high_z1;
	char high_CHANGED;
	
	float peak_z1;
	char peak_CHANGED;
	

	float fs;
	char firstRun;

};
