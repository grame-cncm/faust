/************************************************************************
 ************************************************************************
 FAUST Architecture File for audio engine
 Copyright (C) 2014 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2014-2016 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------

 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.

 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

class FaustPolyEngine;

class DspFaust
{
public:
    DspFaust(int,int);
	~DspFaust();

    bool start();
    void stop();
    bool isRunning();

    int keyOn(int, int);
    int keyOff(int);
    void propagateMidi(int, double, int, int, int, int);

    const char* getJSON();

    int getParamsCount();

    void setParamValue(const char*, float);
    float getParamValue(const char*);

    void setVoiceParamValue(const char*, int, float);
    float getVoiceParamValue(const char*, int);

    const char* getParamAddress(int);

    void propagateAcc(int, float);
    void setAccConverter(int, int, int, float, float, float);

    void propagateGyr(int, float);
    void setGyrConverter(int, int, int, float, float, float);

    float getCPULoad();
    int getScreenColor();
private:
	FaustPolyEngine *fPolyEngine;
};
