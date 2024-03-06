class lowshelffilter
{
public:
	void setSampleRate(float sampleRate);
	void reset();
	void process(float *x, float *y_out_, int nSamples);

	float getgain();
	void setgain(float value);

private:

	
	float lowshelffilter_extra_0 = 0.0f;
	float lowshelffilter_extra_1 = 0.0f;
	float a = 0.0f;
	float _delayed_3 = 0.0f;
	float _delayed_4 = 0.0f;
	float gain = 0.0f;

	
	float gain_z1;
	char gain_CHANGED;
	

	float fs;
	char firstRun;

};
