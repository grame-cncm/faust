class lp_filter2
{
public:
	void setSampleRate(float sampleRate);
	void reset();
	void process(float *x, float *y_out_, int nSamples);

	float getcutoff();
	void setcutoff(float value);

private:

	
	float Rr_7 = 0.0f;
	float lp_filter2_extra_1 = 0.0f;
	float Rr_8 = 0.0f;
	float Gr_8 = 0.0f;
	float dl_8 = 0.0f;
	float lp_filter2_extra_2 = 0.0f;
	float dr_8 = 0.0f;
	float lp_filter2_extra_3 = 0.0f;
	float _delayed_4 = 0.0f;
	float lp_filter2_extra_5 = 0.0f;
	float _delayed_6 = 0.0f;
	float cutoff = 0.0f;

	
	float cutoff_z1;
	char cutoff_CHANGED;
	

	float fs;
	char firstRun;

};
