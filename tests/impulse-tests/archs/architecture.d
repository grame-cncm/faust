import std.stdio;
import std.format;
import std.conv;
import std.string;
import std.algorithm : max, min, map;
import core.stdc.stdio : snprintf;
import core.stdc.stdlib;
import core.stdc.string : memset, strlen;
import core.stdc.math : isinf;
import dplug.core.vec;
import dplug.core.map;
import dplug.core.nogc;
import core.stdc.stdint : uintptr_t;

alias FAUSTFLOAT = double;

class Meta {
nothrow:
@nogc:
    void declare(string name, string value) {}
}

class UI {
nothrow:
@nogc:
    void declare(string id, string key, string value){ }
    void declare(int id, string key, string value){ }
    void declare(FAUSTFLOAT* id, string key, string value){ }

    // -- layout groups

    void openTabBox(string label){ }
    void openHorizontalBox(string label){ }
    void openVerticalBox(string label){ }
    void closeBox(){ }

    // -- active widgets

    void addButton(string label, FAUSTFLOAT* val){ }
    void addCheckButton(string label, FAUSTFLOAT* val){ }
    void addVerticalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step){ }
    void addHorizontalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step){ }
    void addNumEntry(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step){ }

    // -- passive display widgets

    void addHorizontalBargraph(string label, FAUSTFLOAT* val, FAUSTFLOAT min, FAUSTFLOAT max){ }
    void addVerticalBargraph(string label, FAUSTFLOAT* val, FAUSTFLOAT min, FAUSTFLOAT max){ }
}

interface dsp {
nothrow:
@nogc:
public:
    void metadata(Meta* m);
    int getNumInputs();
    int getNumOutputs();
    void buildUserInterface(UI* uiInterface);
    int getSampleRate();
    void instanceInit(int sample_rate);
    void instanceResetUserInterface();
    void compute(int count, FAUSTFLOAT*[] inputs, FAUSTFLOAT*[] outputs);
    void initialize(int sample_rate);
}

enum int kFrames = 64;

//----------------------------------------------------------------------------
// FUI
//----------------------------------------------------------------------------
class FUI : UI
{
nothrow:
@nogc:

    protected:

        Vec!string fControlsLevel;
        Vec!(FAUSTFLOAT*) fButtons;

        // add an element by relating its full name and memory zone
        void addElement(string label, FAUSTFLOAT* zone, bool button = false)
        {
            if (button) {
                fButtons.pushBack(zone);
            }
        }

    
    public:

        this() 
        { 
            fControlsLevel = makeVec!string();
            fButtons = makeVec!(FAUSTFLOAT*)();
        }
        ~this() {}

        void setButtons(bool state)
        {
            for (size_t i = 0; i < fButtons.length(); i++) {
                *fButtons[i] = state;
            }
        }
    
        void pushLabel(string label) { fControlsLevel.pushBack(label); }
        void popLabel() nothrow @nogc { if(fControlsLevel.length() > 0) fControlsLevel.popBack(); }

        // -- widget's layouts (just keep track of group labels)

        override void openTabBox(string label) { pushLabel(label); }
        override void openHorizontalBox(string label) { pushLabel(label); }
        override void openVerticalBox(string label) { pushLabel(label); }
        override void closeBox() nothrow @nogc { popLabel(); }

        // -- active widgets (just add an element)

        override void addButton(string label, FAUSTFLOAT* zone) { addElement(label, zone, true); }
        override void addCheckButton(string label, FAUSTFLOAT* zone) { addElement(label, zone); }
        override void addVerticalSlider(string label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT)
                                                                    { addElement(label, zone); }
        override void addHorizontalSlider(string label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT)
                                                                    { addElement(label, zone); }
        override void addNumEntry(string label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT)
                                                                    { addElement(label, zone); }

        // -- passive widgets (are ignored)

        override void addHorizontalBargraph(string label, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) {}
        override void addVerticalBargraph(string label, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) {}
    
        // -- soundfiles
        // override void addSoundfile(string label, string filename, Soundfile** sf_zone) {}

        // -- metadata are not used

        override void declare(FAUSTFLOAT*, string, string) {}
}

//----------------------------------------------------------------------------
// DSP control UI
//----------------------------------------------------------------------------

class CheckControlUI : UI
{
nothrow:
@nogc:
    Map!(FAUSTFLOAT*, FAUSTFLOAT) fControlZone;
   
    override void addButton(string label, FAUSTFLOAT* zone)
    {
        addItem(zone, FAUSTFLOAT(0));
    }
    override void addCheckButton(string label, FAUSTFLOAT* zone)
    {
        addItem(zone, FAUSTFLOAT(0));
    }
    override void addVerticalSlider(string label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    override void addHorizontalSlider(string label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    override void addNumEntry(string label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    
    void addItem(FAUSTFLOAT* zone, FAUSTFLOAT init)
    {
        fControlZone[zone] = init;
    }
   
    bool checkDefaults()
    {
        foreach(kv; fControlZone.byKeyValue())
        {
            if(*(kv.key) != kv.value) return false;
        }
        return true;
    }
    
    void initRandom()
    {
        foreach(kv; fControlZone.byKeyValue())
        {
            kv.value = 0.123456789;
        }
    }
}

static void printHeader(ref string irFile, mydsp DSP, int nbsamples)
{
    // Print general informations
    irFile ~= format!"number_of_inputs  : %3d\n"(DSP.getNumInputs());
    irFile ~= format!"number_of_outputs : %3d\n"(DSP.getNumOutputs());
    irFile ~= format!"number_of_frames  : %6d\n"(nbsamples);
}

static FAUSTFLOAT normalize(FAUSTFLOAT f)
{
    if (std.math.isNaN(f)) {
        stderr.writeln("ERROR : isnan\n");
        throw new Exception("ERROR : isnan\n");
    } else if (isinf(f)) {
        stderr.writeln("ERROR : isinf\n");
        throw new Exception("ERROR : isinf\n");
    }
    return (fabs(f) < FAUSTFLOAT(0.000001) ? FAUSTFLOAT(0.0) : f);
}

class real_channels(T)
{
    private:
        
        int fNumFrames;
        int fNumChannels;
        T*[] fBuffers;
        T*[] fSliceBuffers;
        
    public:
        
        this(int nframes, int nchannels)
        {
            fBuffers = new T*[nchannels];
            fSliceBuffers = new T*[nchannels];
            fNumFrames = nframes;
            fNumChannels = nchannels;
            
            // allocate audio channels
            for (int chan = 0; chan < fNumChannels; chan++) {
                fBuffers[chan] = cast(T*)new FAUSTFLOAT[fNumFrames];
            }
            
            zero();
        }
        
        void zero()
        {
            // clear audio channels
            for (int chan = 0; chan < fNumChannels; chan++) {
                memset(fBuffers[chan], 0, T.sizeof * fNumFrames);
            }
        }
        
        void impulse()
        {
            // set first sample to 1 for all channels
            for (int chan = 0; chan < fNumChannels; chan++) {
                fBuffers[chan][0] = FAUSTFLOAT(1.0);
                for (int frame = 1; frame < fNumFrames; frame++) {
                    fBuffers[chan][frame] = T(0.0);
                }
            }
        }
        
        void display()
        {
            for (int chan = 0; chan < fNumChannels; chan++) {
                for (int frame = 0; frame < fNumFrames; frame++) {
                    writeln("chan = " ~ to!string(chan) ~ " frame = " ~ to!string(frame) ~ " value = " ~ to!string(fBuffers[chan][frame]) ~ "\n");
                }
            }
        }

        // GC handles free the buffers in this case, nothing to do here
        ~this()
        {
        }
        
        T*[] buffers() { return fBuffers; }
        
        T*[] buffers(int index)
        {
            assert(index < fNumFrames);
            for (int chan = 0; chan < fNumChannels; chan++) {
                fSliceBuffers[chan] = &fBuffers[chan][index];
            }
            return fSliceBuffers;
        }
    
}

class channels : real_channels!FAUSTFLOAT {

    public:
    
        this(int nframes, int nchannels) { super(nframes, nchannels); }
}

// To be used in static context
static void runDSP(ref string irFile, mydsp DSP, ref const string file, ref int linenum, int nbsamples, bool inpl = false, bool random = false)
{
    FUI finterface = new FUI();
    DSP.buildUserInterface(cast(UI*)&finterface);
    
    // // Soundfile
    // TestMemoryReader memory_reader;
    // SoundUI sound_ui = new SoundUI("", -1, &memory_reader);
    // DSP.buildUserInterface(&sound_ui);
    
    // Get control and then 'initRandom'
    CheckControlUI controlui = new CheckControlUI();
    DSP.buildUserInterface(cast(UI*)&controlui);
    controlui.initRandom();
    
    // // MIDI control
    // midi_handler handler;
    // MidiUI midi_ui = new MidiUI(&handler);
    // DSP.buildUserInterface(&midi_ui);
    
    // Init signal processor and the user interface values
    DSP.initialize(44100);
    
    // Check getSampleRate
    if (DSP.getSampleRate() != 44100) {
        stderr.writeln("ERROR runDSP in getSampleRate : " ~ to!string(DSP.getSampleRate()) ~ "\n");
    }
    
    // Check default after 'init'
    if (!controlui.checkDefaults()) {
        stderr.writeln("ERROR runDSP in checkDefaults after 'init'\n");
    }
    
    // Check default after 'instanceResetUserInterface'
    controlui.initRandom();
    DSP.instanceResetUserInterface();
    if (!controlui.checkDefaults()) {
        stderr.writeln("ERROR runDSP in checkDefaults after 'instanceResetUserInterface'\n");
    }
    
    // Check default after 'instanceInit'
    controlui.initRandom();
    DSP.instanceInit(44100);
    if (!controlui.checkDefaults()) {
        stderr.writeln("ERROR runDSP in checkDefaults after 'instanceInit'\n");
    }
    
    // To test that instanceInit properly init a cloned DSP
    DSP = DSP.clone();
    DSP.instanceInit(44100);
    
    // Init UIs on cloned DSP
    DSP.buildUserInterface(cast(UI*)&finterface);
    // DSP.buildUserInterface(cast(UI)&sound_ui);
    // DSP.buildUserInterface(cast(UI)&midi_ui);
    
    int nins = DSP.getNumInputs();
    int nouts = DSP.getNumOutputs();
    
    channels ichan = new channels(kFrames, ((inpl) ? max(nins, nouts) : nins));
    channels ochan = (inpl) ? ichan : new channels(kFrames, nouts);
    
    int run = 0;
    
    // // Test MIDI control
    // for (int i = 0; i < 127; i++) {
    //     handler.handleData2(0, MidiStatus.MIDI_CONTROL_CHANGE, 0, i, 100);
    //     handler.handleData2(0, MidiStatus.MIDI_POLY_AFTERTOUCH, 0, i, 75);
    //     handler.handleData2(0, MidiStatus.MIDI_NOTE_ON, 0, i, 75);
    //     handler.handleData2(0, MidiStatus.MIDI_NOTE_OFF, 0, i, 75);
    //     handler.handleData2(0, MidiStatus.MIDI_PITCH_BEND, 0, i, 4000);
    // }
    // handler.handleData1(0, MidiStatus.MIDI_PROGRAM_CHANGE, 0, 10);
    // handler.handleData1(0, MidiStatus.MIDI_AFTERTOUCH, 0, 10);
    
    // GUI::updateAllGuis();
    
    // print audio frames
    int i;
    try {
        while (nbsamples > 0) {
            if (run == 0) {
                ichan.impulse();
                finterface.setButtons(true);
            }
            if (run >= 1) {
                ichan.zero();
                finterface.setButtons(false);
            }
            int nFrames = min(kFrames, nbsamples);
            
            if (random) {
                int randval = rand();
                int n1 = randval % nFrames;
                int n2 = nFrames - n1;
                DSP.compute(n1, ichan.buffers(), ochan.buffers());
                DSP.compute(n2, ichan.buffers(n1), ochan.buffers(n1));
            } else {
                DSP.compute(nFrames, ichan.buffers(), ochan.buffers());
            }
           
            run++;
            // Print samples
            for (int j = 0; j < nFrames; j++) {
                irFile ~= format!"%6d : "(linenum++);
                for (int c = 0; c < nouts; c++) {
                    FAUSTFLOAT f = normalize(ochan.buffers()[c][j]);
                    irFile ~= format!" %8.6f"(f);
                }
                irFile ~= "\n";
            }
            nbsamples -= nFrames;
        }
    } catch (Exception ex) {
        stderr.writeln("ERROR in '" ~ file ~ "' at line : " ~ to!string(i) ~ "\n");
    }
    
    ichan.destroy();
    if (ochan != ichan) ochan.destroy();
    DSP.destroy();
}


void main(string[] args)
{
    if(args.length < 2)
    {
        stderr.writeln("Error: no argument provided for IR file path");
        return;
    }

    string irFilePath = args[1];
    // string irFilePath = "/home/reker/.test/test.ir";
    string fileText = "";
    File irFile = File(irFilePath, "w+");
    scope(exit) 
    { 
        irFile.write(fileText); 
        irFile.close();
    }
    
    int linenum = 0;
    int nbsamples = 60_000;
    
    // print general informations
    printHeader(fileText, new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(fileText, new mydsp(), args[0], linenum, nbsamples/4);
    runDSP(fileText, new mydsp(), args[0], linenum, nbsamples/4, false, true);
    // runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    // runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
}

<<includeIntrinsic>>

<<includeclass>>
