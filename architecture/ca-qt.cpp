/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN ca-qt.cpp ****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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
#include <string>
#include <list>

#include "faust/dsp/proxy-dsp.h"
#include "faust/dsp/timed-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/FUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/PresetUI.h"
#include "faust/gui/QTUI.h"
#include "faust/audio/audio.h"
#include "faust/misc.h"

#ifdef IOS
#include "faust/gui/APIUI.h"
#include "faust/audio/coreaudio-ios-dsp.h"
#else
#include "faust/audio/coreaudio-dsp.h"
#endif

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
static void osc_compute_callback(void* arg)
{
    static_cast<OSCUI*>(arg)->endBundle();
}
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

// Always include this file, otherwise -nvoices only mode does not compile....
#include "faust/gui/MidiUI.h"

#ifdef MIDICTRL
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
#endif

#define stringify_literal(x) #x
#define stringify_expanded(x) stringify_literal(x)

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

#include "faust/dsp/poly-dsp.h"

#ifdef POLY2
#include "faust/dsp/dsp-combiner.h"
#include "effect.h"
#endif

using namespace std;

dsp* DSP;

list<GUI*> GUI::fGuiList;
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
        enum { kSensorStart = 1, kAccelerometer = 1, kGyroscope, kSensorMax };
        
        Sensor(int type) : fSensor(0), fType(type), fReader(0)
        { fSensor = create (type); fSensor->connectToBackend(); }
        virtual ~Sensor() { if (available()) activate (false); delete fSensor; }
        
        int isAccel() const { return fType == kAccelerometer; }
        int isGyro () const { return fType == kGyroscope; }
        bool available() const { return fSensor->isConnectedToBackend(); }
        bool active() const { return fSensor->isActive(); }
        void activate(bool state){ fSensor->setActive(state); fReader = fSensor->reading(); }
        int count() { return fReader ? fReader->valueCount() : 0; }
        float value(int i) const { return fReader->value(i).value<float>(); }
};

//------------------------------------------------------------------------
QSensor* Sensor::create(int type) const
{
    switch (type) {
        case kAccelerometer: return new QAccelerometer();
        case kGyroscope: return new QGyroscope();
        default: cerr << "unknown sensor type " << type << endl;
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
        
        typedef map<int, Sensor*> TSensors;
        Sensors(APIUI* ui)
        : fUI(ui), fAccel(Sensor::kAccelerometer), fGyro(Sensor::kGyroscope), fTimerID(0) {}
        virtual ~Sensors() { killTimer(fTimerID); }
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
    if (fGyro.available()) { fGyro.activate(true); activate = true; }
    if (activate) fTimerID = startTimer(10);
}
#endif

/******************************************************************************
 *******************************************************************************
 
 MAIN PLAY THREAD
 
 *******************************************************************************
 *******************************************************************************/

#ifdef IOS
#define lopt(a,b,val)	val
#define coreaudio		iosaudio
#endif

int main(int argc, char* argv[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    bool midi_sync = false;
    int nvoices = 0;
    bool control = true;
    
    if (isopt(argv, "-help") || isopt(argv, "-h")) {
        cout << argv[0] << " [--frequency <val>] [--buffer <val>] [--nvoices <val>] [--control <0/1>] [--group <0/1>] [--virtual-midi <0/1>]\n";
        exit(1);
    }
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
    
#ifdef IOS
    APIUI apiui;
    Sensors sensors(&apiui);
#endif
    
    snprintf(name, 256, "%s", basename(argv[0]));
    snprintf(rcfilename, 256, "%s/.%src", home, name);
     
    long srate = (long)lopt(argv, "--frequency", -1);
    int fpb = lopt(argv, "--buffer", 512);
    bool is_virtual = lopt(argv, "--virtual-midi", false);
    
#ifdef POLY2
    nvoices = lopt(argv, "--nvoices", nvoices);
    control = lopt(argv, "--control", control);
    int group = lopt(argv, "--group", 1);
    
    cout << "Started with " << nvoices << " voices\n";
    DSP = new mydsp_poly(new mydsp(), nvoices, control, group);
    
#if MIDICTRL
    if (midi_sync) {
        DSP = new timed_dsp(new dsp_sequencer(DSP, new effect()));
    } else {
        DSP = new dsp_sequencer(DSP, new effect());
    }
#else
    DSP = new dsp_sequencer(DSP, new effect());
#endif
    
#else
    nvoices = lopt(argv, "--nvoices", nvoices);
    control = lopt(argv, "--control", control);
    int group = lopt(argv, "--group", 1);
    
    if (nvoices > 0) {
        cout << "Started with " << nvoices << " voices\n";
        DSP = new mydsp_poly(new mydsp(), nvoices, control, group);
        
#if MIDICTRL
        if (midi_sync) {
            DSP = new timed_dsp(DSP);
        }
#endif
        
    } else {
#if MIDICTRL
        if (midi_sync) {
            DSP = new timed_dsp(new mydsp());
        } else {
            DSP = new mydsp();
        }
#else
        // We possibly have a file...
        /*
         try {
            DSP = new dsp_sequencer(new sound_player(stringify_expanded(SOUND_FILE)), new mydsp());
         } catch (...) {
            DSP = new mydsp();
         }
         */
        DSP = new mydsp();
#endif
    }
    
#endif
    
    if (!DSP) {
        cerr << "Unable to allocate Faust DSP object" << endl;
        exit(1);
    }
    
    QApplication myApp(argc, argv);
    
    QTGUI* interface = new QTGUI();
    FUI finterface;
    
#ifdef PRESETUI
    PresetUI pinterface(interface, string(PRESETDIR) + string(name) + ((nvoices > 0) ? "_poly" : ""));
    DSP->buildUserInterface(&pinterface);
#else
    DSP->buildUserInterface(interface);
    DSP->buildUserInterface(&finterface);
#endif
    
#ifdef IOS
    DSP->buildUserInterface(&apiui);
#endif
    
#ifdef MIDICTRL
    rt_midi midi_handler(name, is_virtual);
    MidiUI midiinterface(&midi_handler);
    DSP->buildUserInterface(&midiinterface);
    cout << "MIDI is on" << endl;
#endif
    
#ifdef HTTPCTRL
    httpdUI httpdinterface(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);
    cout << "HTTPD is on" << endl;
#endif
    
    coreaudio audio(srate, fpb);
    if (!audio.init(name, DSP)) {
        cerr << "Unable to init audio" << endl;
        exit(1);
    }
   
// After audio init to get SR
#ifdef SOUNDFILE
    // Use bundle path
    SoundUI soundinterface(SoundUI::getBinaryPath() + "/Contents/Resources/", audio.getSampleRate());
    DSP->buildUserInterface(&soundinterface);
#endif
    
#ifdef IOS
    sensors.start();
#endif
    
#ifdef OSCCTRL
    OSCUI oscinterface(name, argc, argv);
    DSP->buildUserInterface(&oscinterface);
    cout << "OSC is on" << endl;
    audio.addControlCallback(osc_compute_callback, &oscinterface);
#endif
    
    if (!audio.start()) {
        cerr << "Unable to start audio" << endl;
        exit(1);
    }
    
    cout << "ins " << audio.getNumInputs() << endl;
    cout << "outs " << audio.getNumOutputs() << endl;
    
#ifdef HTTPCTRL
    httpdinterface.run();
#ifdef QRCODECTRL
    interface->displayQRCode(httpdinterface.getTCPPort());
#endif
#endif
    
#ifdef OSCCTRL
    oscinterface.run();
#endif
    
#ifdef MIDICTRL
    if (!midiinterface.run()) {
        cerr << "MidiUI run error " << endl;
    }
#endif
    
    // After the allocation of controllers
    finterface.recallState(rcfilename);
 
    interface->run();
    
    myApp.setStyleSheet(interface->styleSheet());
    myApp.exec();
    
#ifdef MIDICTRL
    midiinterface.stop();
#endif
    interface->stop();
    
    audio.stop();
    finterface.saveState(rcfilename);
    
    delete DSP;
    
    return 0;
}

/******************** END ca-qt.cpp ****************/

