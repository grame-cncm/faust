class lp_filter
{
public:
	void setSampleRate(float sampleRate);
	void reset();
	void process(float *x, float *y_out_, int nSamples);

	float getcutoff();
	void setcutoff(float value);

private:

	
	float Rr_5 = 0.0f;
	float lp_filter_extra_1 = 0.0f;
	float _delayed_2 = 0.0f;
	float cutoff = 0.0f;

	
	float cutoff_z1;
	char cutoff_CHANGED;
	

	float fs;
	char firstRun;

};
