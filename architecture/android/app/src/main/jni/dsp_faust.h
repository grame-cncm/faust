/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2014 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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

bool init(int, int);
bool start(void);
void stop(void);
void destroy(void);
bool isRunning(void);
int keyOn(int, int);
int keyOff(int);
int pitchBend(int, float);
const char* getJSON(void);
int getParamsCount(void);
float getParam(const char*);
void setParam(const char*, float);
int setVoiceParam(const char*, int, float);
int setVoiceGain(int, float);
const char* getParamAddress(int);
void propagateAcc(int acc, float v);
void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax);
void propagateGyr(int acc, float v);
void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax);
float getCPULoad();
int getScreenColor();
