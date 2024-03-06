class lp_filter3
{
public:
	void setSampleRate(float sampleRate);
	void reset();
	void process(float *x, float *y_out_, int nSamples);

	float getcutoff();
	void setcutoff(float value);
	float getvol();
	void setvol(float value);

private:

	
	float Rr_6 = 0.0f;
	float lp_filter3_extra_1 = 0.0f;
	float Rr_11 = 0.0f;
	float lp_filter3_extra_3 = 0.0f;
	float Rr_16 = 0.0f;
	float lp_filter3_extra_5 = 0.0f;
	float _delayed_6 = 0.0f;
	float _delayed_7 = 0.0f;
	float _delayed_8 = 0.0f;
	float cutoff = 0.0f;
	float vol = 0.0f;

	
	float cutoff_z1;
	char cutoff_CHANGED;
	
	float vol_z1;
	char vol_CHANGED;
	

	float fs;
	char firstRun;

};
