/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#include <libgen.h>
#include <stdlib.h>
#include <iostream>
#include <list>

#include "faust/dsp/proxy-dsp.h"
#include "faust/dsp/timed-dsp.h"
#include "faust/gui/PathBuilder.h"
#include "faust/gui/FUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/faustqt.h"
#include "faust/misc.h"
#include "faust/audio/audio.h"

#ifdef IOS
#include "faust/gui/APIUI.h"
#include "faust/audio/coreaudio-ios-dsp.h"
#else
#include "faust/audio/coreaudio-dsp.h"
#endif

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

// Always include this file, otherwise -poly only mode does not compile....
#include "faust/gui/MidiUI.h"

#ifdef MIDICTRL
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
#endif

/**************************BEGIN USER SECTION **************************/

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/
<<includeIntrinsic>>

<<includeclass>>

#if defined(POLY) || defined(POLY2)
#include "faust/dsp/poly-dsp.h"
#include "faust/dsp/dsp-combiner.h"
#endif

#if defined(POLY2)
#include "effect.cpp"
#endif

dsp* DSP;

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

/******************************************************************************
*******************************************************************************

                                Sensors section

*******************************************************************************
*******************************************************************************/
#ifdef IOS
#include <QAccelerometer>
#include <QGyroscope>
#include <QAccelerometerReading>
#include <QGyroscopeReading>
#include <QTimer>

//------------------------------------------------------------------------
class Sensor
{
	private:
    
		QSensor* fSensor;
		int fType;
		QSensorReading* fReader;
		QSensor* create(int type) const;
	
	public:
		enum  { kSensorStart = 1, kAccelerometer = 1, kGyroscope, kSensorMax };

				 Sensor(int type) : fSensor(0), fType(type), fReader(0)
									{ fSensor = create (type); fSensor->connectToBackend(); }
		virtual ~Sensor()			{ if (available()) activate (false); delete fSensor; }

		int				isAccel() const		{ return fType == kAccelerometer; }
		int				isGyro () const		{ return fType == kGyroscope; }
		bool			available() const	{ return fSensor->isConnectedToBackend(); }
		bool			active() const		{ return fSensor->isActive(); }
		void			activate(bool state){ fSensor->setActive(state); fReader = fSensor->reading(); }
		int				count()				{ return fReader ? fReader->valueCount() : 0; }
		float			value(int i) const	{ return fReader->value(i).value<float>(); }
};

//------------------------------------------------------------------------
QSensor* Sensor::create (int type) const
{
	switch (type) {
		case kAccelerometer: return new QAccelerometer();
		case kGyroscope: return new QGyroscope();
		default:
			cerr << "unknown sensor type " << type << endl;
	}
	return 0;
}

//------------------------------------------------------------------------
class Sensors : public QObject
{
    private:
    
        APIUI* fUI;
        Sensor fAccel, fGyro;
        int fTimerID;
        
	public:
    
		typedef std::map<int, Sensor*> TSensors;
				 Sensors(APIUI* ui)
				 		: fUI(ui), fAccel(Sensor::kAccelerometer), fGyro(Sensor::kGyroscope), fTimerID(0) {}
		virtual ~Sensors()		{ killTimer(fTimerID); }
		void start();
        
	protected:
    
		void timerEvent(QTimerEvent*);
};

//------------------------------------------------------------------------
void Sensors::timerEvent(QTimerEvent*)
{
	if (fAccel.active()) {
        int count = fAccel.count();
        for (int i = 0; (i< count) && (i < 3); i++) {
        	fUI->propagateAcc(i, fAccel.value(i));
        }
	}
	if (fGyro.active()) {
        int count = fGyro.count();
        for (int i = 0; (i< count) && (i < 3); i++) {
        	fUI->propagateGyr(i, fGyro.value(i));
        }
	}
}

//------------------------------------------------------------------------
void Sensors::start() 
{
	bool activate = false;
	if (fAccel.available()) { fAccel.activate(true); activate = true; }
	if (fGyro.available()) 	{ fGyro.activate(true); activate = true; }
	if (activate) fTimerID = startTimer(10);
}
#endif

/******************************************************************************
*******************************************************************************

                                MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/

static bool hasMIDISync()
{
    JSONUI jsonui;
    mydsp tmp_dsp;
    tmp_dsp.buildUserInterface(&jsonui);
    std::string json = jsonui.JSON();
    
    return ((json.find("midi") != std::string::npos) &&
            ((json.find("start") != std::string::npos) ||
            (json.find("stop") != std::string::npos) ||
            (json.find("clock") != std::string::npos)));
}

#ifdef IOS
#define lopt(a,b,val)	val
#define coreaudio		iosaudio
#endif

int main(int argc, char *argv[])
{
	char name[256];
	char rcfilename[256];
	char* home = getenv("HOME");
#ifdef IOS
    APIUI apiui;
    Sensors sensors(&apiui);
#endif

	snprintf(name, 255, "%s", basename(argv[0]));
	snprintf(rcfilename, 255, "%s/.%src", home, name);
    
    long srate = (long)lopt(argv, "--frequency", -1);
    int fpb = lopt(argv, "--buffer", 512);
    
#ifdef POLY2
    mydsp tmp_dsp;
    int poly = lopt(argv, "--poly", 4);
    int group = lopt(argv, "--group", 1);

#if MIDICTRL
    if (hasMIDISync()) {
        DSP = new timed_dsp(new dsp_sequencer(new mydsp_poly(&tmp_dsp, poly, true, group), new effect()));
    } else {
        DSP = new dsp_sequencer(new mydsp_poly(&tmp_dsp, poly, true, group), new effect());
    }
#else
    DSP = new dsp_sequencer(new mydsp_poly(&tmp_dsp, poly, false, group), new effect());
#endif

#elif POLY
    mydsp tmp_dsp;
    int poly = lopt(argv, "--poly", 4);
    int group = lopt(argv, "--group", 1);

#if MIDICTRL
    if (hasMIDISync()) {
        DSP = new timed_dsp(new mydsp_poly(&tmp_dsp, poly, true, group));
    } else {
        DSP = new mydsp_poly(&tmp_dsp, poly, true, group);
    }
#else
    DSP = new mydsp_poly(&tmp_dsp, poly, false, group);
#endif

#elif MIDICTRL
    if (hasMIDISync()) {
        DSP = new timed_dsp(new mydsp());
    } else {
        DSP = new mydsp();
    }
#else
    DSP = new mydsp();
#endif
    
    if (DSP == 0) {
        std::cerr << "Unable to allocate Faust DSP object" << std::endl;
        exit(1);
    }
 
	QApplication myApp(argc, argv);
    
    QTGUI interface;
    FUI finterface;
    DSP->buildUserInterface(&interface);
    DSP->buildUserInterface(&finterface);
#ifdef IOS
    DSP->buildUserInterface(&apiui);
#endif

#ifdef MIDICTRL
    rt_midi midi_handler(name);
    MidiUI midiinterface(&midi_handler);
    DSP->buildUserInterface(&midiinterface);
    std::cout << "MIDI is on" << std::endl;
#endif

#ifdef HTTPCTRL
    httpdUI httpdinterface(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);
    std::cout << "HTTPD is on" << std::endl;
 #endif

#ifdef OSCCTRL
	OSCUI oscinterface(name, argc, argv);
    DSP->buildUserInterface(&oscinterface);
    std::cout << "OSC is on" << std::endl;
#endif

	coreaudio audio(srate, fpb);
	audio.init(name, DSP);
	finterface.recallState(rcfilename);
	audio.start();
#ifdef IOS
	sensors.start();
#endif
	
    printf("ins %d\n", audio.get_num_inputs());
    printf("outs %d\n", audio.get_num_outputs());

#ifdef HTTPCTRL
	httpdinterface.run();
#ifdef QRCODECTRL
    interface.displayQRCode(httpdinterface.getTCPPort());
#endif
#endif

#ifdef OSCCTRL
	oscinterface.run();
#endif
#ifdef MIDICTRL
	midiinterface.run();
#endif
	interface.run();

    myApp.setStyleSheet(interface.styleSheet());
    myApp.exec();
    interface.stop();
    
	audio.stop();
	finterface.saveState(rcfilename);

  	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/


