#ifndef faust_teensy_h_
#define faust_teensy_h_

#include <string>
#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

class dsp;
class MapUI;

class AudioFaust : public AudioStream
{
public:
	AudioFaust();
	~AudioFaust();
	virtual void update(void);
	void setParamValue(const std::string& path, float value);
private:
	float** fInChannel;
	float** fOutChannel;
	MapUI* UI;
	dsp* fDSP;
};

#endif
