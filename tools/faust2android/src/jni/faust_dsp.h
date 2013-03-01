/*
TODO header needed
*/

struct Para {
			int cnt;
			int cntLay;
			int *typeLay;
			int *labelLayPos;
			const char *labelLay;
			int *type;
			int *layoutEl;
			float *zone;
			int *labelPos;
			const char *label;
			float *init;
			float *min;
			float *max;
			float *step;
		} ;

class faust{
public:
	Para initFaust(void);
	void startAudio(void);
	void processDSP(void);
	void setParam(float*);
	void stopAudio(void);
};

