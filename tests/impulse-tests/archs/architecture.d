import std.stdio;
import std.format;
import std.conv;
import core.stdc.stdio : snprintf;
import core.stdc.stdlib;
import core.stdc.string : memset;


/*******************************************************************
 * MemoryReader Implementation
 *******************************************************************/
enum int SOUND_CHAN   = 2;
enum int SOUND_LENGTH = 4096;
enum int SOUND_SR     = 44100;

class MemoryReader : SoundfileReader {
    
    this()
    {}
    
    /**
     * Check the availability of a sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     *
     * @return true if the sound resource is available, false otherwise.
     */
    override bool checkFile(ref const string path_name) { return true; }
    
    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    override void getParamsFile(ref const string path_name, ref int channels, ref int length)
    {
        channels = SOUND_CHAN;
        length = SOUND_LENGTH;
    }
    
    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    override void readFile(Soundfile soundfile, ref const string path_name, int part, ref int offset, int max_chan)
    {
        soundfile.fLength[part] = SOUND_LENGTH;
        soundfile.fSR[part] = SOUND_SR;
        soundfile.fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        for (int sample = 0; sample < SOUND_LENGTH; sample++) {
            for (int chan = 0; chan < SOUND_CHAN; chan++) {
                soundfile.fBuffers[chan][offset + sample] = 0.0f;
            }
        }
        
        // Update offset
        offset += SOUND_LENGTH;
    }
    
}

/*******************************************************************
 * SOUND FILE Implementation
 ******************************************************************/
enum int BUFFER_SIZE = 16384;
enum int SAMPLE_RATE = 44100;
enum int MAX_CHAN = 64;
enum int MAX_SOUNDFILE_PARTS = 256;

/*
 The soundfile structure to be used by the DSP code. Soundfile has a MAX_SOUNDFILE_PARTS parts 
 (even a single soundfile or an empty soundfile). 
 fLength, fOffset and fSR fields are filled accordingly by repeating
 the actual parts if needed.
 
 It has to be 'packed' to that the LLVM backend can correctly access it.

 Index computation:
    - p is the current part number [0..MAX_SOUNDFILE_PARTS-1] (must be proved by the type system)
    - i is the current position in the part. It will be constrained between [0..length]
    - idx(p,i) = fOffset[p] + max(0, min(i, fLength[p]));
*/

class Soundfile {
    FAUSTFLOAT** fBuffers;
    int* fLength;   // length of each part
    int* fSR;       // sample rate of each part
    int* fOffset;   // offset of each part in the global buffer
    int fChannels;  // max number of channels of all concatenated files

    this()
    {
        fBuffers  = null;
        fChannels = -1;
        fLength   = cast(int*)new int[MAX_SOUNDFILE_PARTS];
        fSR       = cast(int*)new int[MAX_SOUNDFILE_PARTS];
        fOffset   = cast(int*)new int[MAX_SOUNDFILE_PARTS];
    }

    ~this()
    {
        // Free the real channels only
        for (int chan = 0; chan < fChannels; chan++) {
            delete fBuffers[chan];
        }
        delete fBuffers;
        delete fLength;
        delete fSR;
        delete fOffset;
    }

}

/*
 The generic soundfile reader.
 */

class SoundfileReader {
    
   protected:
    
    int fDriverSR;
    
    void emptyFile(Soundfile soundfile, int part, ref int offset)
    {
        soundfile.fLength[part] = BUFFER_SIZE;
        soundfile.fSR[part] = SAMPLE_RATE;
        soundfile.fOffset[part] = offset;
        // Update offset
        offset += soundfile.fLength[part];
    }

    Soundfile createSoundfile(int cur_chan, int length, int max_chan)
    {
        Soundfile soundfile = new Soundfile();
        soundfile.fBuffers = cast(FAUSTFLOAT**)new FAUSTFLOAT*[max_chan];
        
        for (int chan = 0; chan < cur_chan; chan++) {
            soundfile.fBuffers[chan] = cast(FAUSTFLOAT*)new FAUSTFLOAT[length];
            memset(soundfile.fBuffers[chan], 0, FAUSTFLOAT.sizeof * length);
        }
        
        soundfile.fChannels = cur_chan;
        return soundfile;
    }

    void getBuffersOffset(Soundfile soundfile, FAUSTFLOAT** buffers, int offset)
    {
        for (int chan = 0; chan < soundfile.fChannels; chan++) {
            buffers[chan] = &soundfile.fBuffers[chan][offset];
        }
    }
    
    // Check if a soundfile exists and return its real path_name
    string checkFile(ref const Vec!string sound_directories, ref const string file_name)
    {
        if (checkFile(file_name)) {
            return file_name;
        } else {
            for (size_t i = 0; i < sound_directories.length(); i++) {
                string path_name = sound_directories[i] + "/" + file_name;
                if (checkFile(path_name)) { return path_name; }
            }
            return "";
        }
    }
    
    bool isResampling(int sample_rate) { return (fDriverSR > 0 && fDriverSR != sample_rate); }
 
    // To be implemented by subclasses

    /**
     * Check the availability of a sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     *
     * @return true if the sound resource is available, false otherwise.
     */
    bool checkFile(ref const string path_name) { return false; }
    
    /**
     * Check the availability of a sound resource.
     *
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     *
     * @return true if the sound resource is available, false otherwise.
     */

    bool checkFile(char* buffer, size_t size) { return true; }

    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    void getParamsFile(ref const string path_name, ref int channels, ref int length) {};
    
    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    void getParamsFile(char* buffer, size_t size, ref int channels, ref int length) {}

    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param soundfile - the soundfile to be filled
     * @param path_name - the name of the file, or sound resource identified this way
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    void readFile(Soundfile soundfile, ref const string path_name, int part, ref int offset, int max_chan) {};
    
    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param soundfile - the soundfile to be filled
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    void readFile(Soundfile soundfile, char* buffer, size_t size, int part, ref int offset, int max_chan) {}

  public:
    
    ~this() {}
    
    void setSampleRate(int sample_rate) { fDriverSR = sample_rate; }
   
    Soundfile createSoundfile(ref const Vec!string path_name_list, int max_chan)
    {
        try {
            int cur_chan = 1; // At least one buffer
            int total_length = 0;
            
            // Compute total length and channels max of all files
            for (int i = 0; i < cast(int)(path_name_list.length()); i++) {
                int chan, length;
                if (path_name_list[i] == "__empty_sound__") {
                    length = BUFFER_SIZE;
                    chan = 1;
                } else {
                    getParamsFile(path_name_list[i], chan, length);
                }
                cur_chan = max(cur_chan, chan);
                total_length += length;
            }
           
            // Complete with empty parts
            total_length += (MAX_SOUNDFILE_PARTS - cast(int)path_name_list.length()) * BUFFER_SIZE;
            
            // Create the soundfile
            Soundfile soundfile = createSoundfile(cur_chan, total_length, max_chan);
            
            // Init offset
            int offset = 0;
            
            // Read all files
            for (int i = 0; i < cast(int)(path_name_list.length()); i++) {
                if (path_name_list[i] == "__empty_sound__") {
                    emptyFile(soundfile, i, offset);
                } else {
                    readFile(soundfile, path_name_list[i], i, offset, max_chan);
                }
            }
            
            // Complete with empty parts
            for (int i = cast(int)(path_name_list.length()); i < MAX_SOUNDFILE_PARTS; i++) {
                emptyFile(soundfile, i, offset);
            }
            
            // Share the same buffers for all other channels so that we have max_chan channels available
            for (int chan = cur_chan; chan < max_chan; chan++) {
                soundfile.fBuffers[chan] = soundfile.fBuffers[chan % cur_chan];
            }
            
            return soundfile;
            
        } catch (Exception ex) {
            return null;
        }
    }

    // Check if all soundfiles exist and return their real path_name
    Vec!string checkFiles(ref const Vec!string sound_directories,
                                        ref const Vec!string file_name_list)
    {
        Vec!string path_name_list;
        for (size_t i = 0; i < file_name_list.length(); i++) {
            string path_name = checkFile(sound_directories, file_name_list[i]);
            // If 'path_name' is not found, it is replaced by an empty sound (= silence)
            path_name_list.push_back((path_name == "") ? "__empty_sound__" : path_name);
        }
        return path_name_list;
    }

}

import std.algorithm : max, min;

// static const MemoryReader gReader = new MemoryReader();

// // To be used by DSP code if no SoundUI is used
// Vec!string path_name_list;
// Soundfile defaultsound = gReader.createSoundfile(path_name_list, MAX_CHAN);

class UI {
nothrow:
@nogc:
    void declare(string id, string key, string value) {}
    void declare(int id, string key, string value) {}
    void declare(FAUSTFLOAT* id, string key, string value) {}

    // -- layout groups

    void openTabBox(string label) {}
    void openHorizontalBox(string label) {}
    void openVerticalBox(string label) {}
    void closeBox() {}

    // -- active widgets

    void addButton(string label, FAUSTFLOAT* val) {}
    void addCheckButton(string label, FAUSTFLOAT* val) {}
    void addVerticalSlider(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}
    void addHorizontalSlider(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}
    void addNumEntry(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}

    // -- passive display widgets

    void addHorizontalBargraph(string label, FAUSTFLOAT* val, float min, float max) {}
    void addVerticalBargraph(string label, FAUSTFLOAT* val, float min, float max) {}

}

class SoundUI : UI
{
		
    private:
    
        Vec!string fSoundfileDir;             // The soundfile directories
        Map!(string, Soundfile) fSoundfileMap;    // Map to share loaded soundfiles
        SoundfileReader* fSoundReader;

     public:
    
        /**
         * Create a soundfile loader which will typically use a concrete SoundfileReader like LibsndfileReader or JuceReader to load soundfiles.
         *
         * @param sound_directory - the base directory to look for files, which paths will be relative to this one
         * @param sample_rate - the audio driver SR which may be different from the file SR, to possibly resample files
         * @param reader - an alternative soundfile reader
         *
         * @return the soundfile loader.
         */
        this(ref const string sound_directory, int sample_rate = -1, SoundfileReader* reader = null)
        {
            fSoundfileDir.push_back(sound_directory);
            fSoundReader = (reader) ? reader : &gReader;
            fSoundReader.setSampleRate(sample_rate);
        }
    
        /**
         * Create a soundfile loader which will typically use a concrete SoundfileReader like LibsndfileReader or JuceReader to load soundfiles.
         *
         * @param sound_directories - a vector of base directories to look for files, which paths will be relative to these ones
         * @param sample_rate - the audio driver SR which may be different from the file SR, to possibly resample files
         * @param reader - an alternative soundfile reader
         *
         * @return the soundfile loader.
         */
        this(ref const Vec!string sound_directories, int sample_rate = -1, SoundfileReader* reader = null)
            // :fSoundfileDir(sound_directories)
        {
            fSoundReader = reader;
            fSoundReader.setSampleRate(sample_rate);
        }
    
        ~this()
        {   
            // Delete all soundfiles
            foreach (it; fSoundfileMap) {
                delete it.second;
            }
        }

        // -- soundfiles
        void addSoundfile(const char* label, const char* url, Soundfile* sf_zone)
        {
            const char* saved_url = url; // 'url' is consumed by parseMenuList2
            Vec!string file_name_list;
            
            bool menu = parseMenuList2(url, file_name_list, true);
            // If not a list, we have as single file
            if (!menu) { file_name_list.pushBack(saved_url); }
            
            // Parse the possible list
            if (fSoundfileMap.find(saved_url) == fSoundfileMap.end()) {
                // Check all files and get their complete path
                Vec!string path_name_list = fSoundReader.checkFiles(fSoundfileDir, file_name_list);
                // Read them and create the Soundfile
                Soundfile sound_file = fSoundReader.createSoundfile(path_name_list, MAX_CHAN);
                if (sound_file) {
                    fSoundfileMap[saved_url] = sound_file;
                } else {
                    // If failure, use 'defaultsound'
                    cerr ~ "addSoundfile : soundfile for " ~ saved_url ~ " cannot be created !\n";
                    *sf_zone = defaultsound;
                    return;
                }
            }
            
            // Get the soundfile
            *sf_zone = fSoundfileMap[saved_url];
        }
    
        /**
         * An OS dependant function to get the path of the running executable or plugin.
         * This will typically be used when creating a SoundUI soundfile loader, like new SoundUI(SoundUI::getBinaryPath());
         *
         * @return the running executable or plugin path.
         */
        static string getBinaryPath()
        {
            string bundle_path_str;
            return bundle_path_str;
        }
    
        /**
         * An OS dependant function to get the path of the running executable or plugin.
         * This will typically be used when creating a SoundUI soundfile loader, like new SoundUI(SoundUI::getBinaryPathFrom());
         *
         * @param path - entry point to start getting the path of the running executable or plugin.
         *
         * @return the running executable or plugin path.
         */
        static string getBinaryPathFrom(ref const string path)
        {
            string bundle_path_str;
            return bundle_path_str;
        }
}

enum int kFrames = 64;

// std::list<GUI*> GUI::fGuiList;
// ztimedmap GUI::gTimedZoneMap;

//----------------------------------------------------------------------------
// Test MemoryReader
//----------------------------------------------------------------------------

class TestMemoryReader : MemoryReader {
    
    override bool checkFile(ref const string path_name)
    {
        return true;
    }
    
    override void getParamsFile(ref const string path_name, ref int channels, ref int length)
    {
        channels = SOUND_CHAN;
        length = SOUND_LENGTH;
    }
    
    override void readFile(Soundfile soundfile, ref const string path_name, int part, ref int offset, int max_chan)
    {
        soundfile.fLength[part] = SOUND_LENGTH;
        soundfile.fSR[part] = SOUND_SR;
        soundfile.fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        for (int sample = 0; sample < SOUND_LENGTH; sample++)
        {
            for (int chan = 0; chan < SOUND_CHAN; chan++)
            {
                soundfile.fBuffers[chan][offset + sample] = sin(part + (2 * M_PI * float(sample)/SOUND_LENGTH));
            }
        }

        // Update offset
        offset += SOUND_LENGTH;
    }
    
}

//----------------------------------------------------------------------------
// DSP control UI
//----------------------------------------------------------------------------

class CheckControlUI : UI
{
    
    Map!(FAUSTFLOAT*, FAUSTFLOAT) fControlZone;
   
    void addButton(const char* label, FAUSTFLOAT* zone)
    {
        addItem(zone, FAUSTFLOAT(0));
    }
    void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        addItem(zone, FAUSTFLOAT(0));
    }
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    
    void addItem(FAUSTFLOAT* zone, FAUSTFLOAT init)
    {
        fControlZone[zone] = init;
    }
   
    bool checkDefaults()
    {
        foreach (it; fControlZone) {
            if (*it.first != it.second) return false;
        }
        return true;
    }
    
    void initRandom()
    {
        foreach (it; fControlZone) {
            *it.first = 0.123456789;
        }
    }
}

//----------------------------------------------------------------------------
// Test memory manager
//----------------------------------------------------------------------------

// class malloc_memory_manager : dsp_memory_manager {
    
//     void* allocate(size_t size)
//     {
//         void* res = malloc(size);
//         memset(res, 0, size);
//         return res;
//     }
 
//     void destroy(void* ptr)
//     {
//         free(ptr);
//     }
    
// }

class dsp {
nothrow:
@nogc:
public:
    int fSamplingFreq;
}

static void printHeader(dsp* DSP, int nbsamples)
{
    // Print general informations
    printf("number_of_inputs  : %3d\n", DSP.getNumInputs());
    printf("number_of_outputs : %3d\n", DSP.getNumOutputs());
    printf("number_of_frames  : %6d\n", nbsamples);
}

static FAUSTFLOAT normalize(FAUSTFLOAT f)
{
    if (std.math.isNaN(f)) {
        cerr ~ "ERROR : isnan\n";
        throw -1;
    } else if (std.math.isInf(f)) {
        cerr ~ "ERROR : isinf\n";
        throw -1;
    }
    return (fabs(f) < FAUSTFLOAT(0.000001) ? FAUSTFLOAT(0.0) : f);
}

// To be used in static context
static void runPolyDSP(dsp* dsp, ref int linenum, int nbsamples, int num_voices = 4)
{
    mydsp_poly* DSP = new mydsp_poly(dsp, num_voices, true, false);
    
    // Soundfile
    TestMemoryReader memory_reader;
    SoundUI sound_ui = new SoundUI("", -1, &memory_reader);
    DSP.setGroup(false);
    DSP.buildUserInterface(&sound_ui);
    DSP.setGroup(true);
  
    // Get control and then 'initRandom'
    CheckControlUI controlui;
    DSP.buildUserInterface(&controlui);
    controlui.initRandom();
    
    // init signal processor and the user interface values:
    DSP.init(44100);
    
    // Check getSampleRate
    if (DSP.getSampleRate() != 44100) {
        cerr ~ "ERROR runPolyDSP in getSampleRate : " ~ DSP.getSampleRate() ~ "\n";
    }
    
    // Check default after 'init'
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runPolyDSP in checkDefaults after 'init'\n" ;
    }
    
    // Check default after 'instanceResetUserInterface'
    controlui.initRandom();
    DSP.instanceResetUserInterface();
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runPolyDSP in checkDefaults after 'instanceResetUserInterface'\n";
    }
    
    // Check default after 'instanceInit'
    controlui.initRandom();
    DSP.instanceInit(44100);
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runPolyDSP in checkDefaults after 'instanceInit'\n";
    }
    
    // Init again
    DSP.init(44100);
    
    int nins = DSP.getNumInputs();
    channels ichan(kFrames, nins);
    
    int nouts = DSP.getNumOutputs();
    channels ochan(kFrames, nouts);
    
    // Test polyphony
    for (int i = 0; i < num_voices; i++) {
        DSP.keyOn(0, 60 + i*2, 100);
    }
    
    // Compute audio frames
    while (nbsamples > 0) {
        int nFrames = min(kFrames, nbsamples);
        DSP.compute(nFrames, ichan.buffers(), ochan.buffers());
        // Print samples
        for (int i = 0; i < nFrames; i++) {
            printf("%6d : ", linenum++);
            for (int c = 0; c < nouts; c++) {
                FAUSTFLOAT f = normalize(ochan.buffers()[c][i]);
                printf(" %8.6f", f);
            }
            printf("\n");
        }
        nbsamples -= nFrames;
    }
    
    delete DSP;
}

// To be used in static context
static void runDSP(dsp* DSP, ref const string file, ref int linenum, int nbsamples, bool inpl = false, bool random = false)
{
    char[256] rcfilename;
    string filename = file;
    filename = filename.substr(0, filename.find ('.'));
    snprintf(rcfilename, 255, "%src", filename.c_str());
    
    FUI finterface;
    DSP.buildUserInterface(&finterface);
    
    // Soundfile
    TestMemoryReader memory_reader;
    SoundUI sound_ui = new SoundUI("", -1, &memory_reader);
    DSP.buildUserInterface(&sound_ui);
    
    // Get control and then 'initRandom'
    CheckControlUI controlui;
    DSP.buildUserInterface(&controlui);
    controlui.initRandom();
    
    // MIDI control
    midi_handler handler;
    MidiUI midi_ui = new MidiUI(&handler);
    DSP.buildUserInterface(&midi_ui);
    
    // Init signal processor and the user interface values
    DSP.init(44100);
    
    // Check getSampleRate
    if (DSP.getSampleRate() != 44100) {
        cerr ~ "ERROR runDSP in getSampleRate : " ~ DSP.getSampleRate() ~ '\n';
    }
    
    // Check default after 'init'
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runDSP in checkDefaults after 'init'\n";
    }
    
    // Check default after 'instanceResetUserInterface'
    controlui.initRandom();
    DSP.instanceResetUserInterface();
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runDSP in checkDefaults after 'instanceResetUserInterface'\n";
    }
    
    // Check default after 'instanceInit'
    controlui.initRandom();
    DSP.instanceInit(44100);
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runDSP in checkDefaults after 'instanceInit'\n";
    }
    
    // To test that instanceInit properly init a cloned DSP
    DSP = DSP.clone();
    DSP.instanceInit(44100);
    
    // Init UIs on cloned DSP
    DSP.buildUserInterface(&finterface);
    DSP.buildUserInterface(&sound_ui);
    DSP.buildUserInterface(&midi_ui);
    
    int nins = DSP.getNumInputs();
    int nouts = DSP.getNumOutputs();
    
    channels* ichan = new channels(kFrames, ((inpl) ? max(nins, nouts) : nins));
    channels* ochan = (inpl) ? ichan : new channels(kFrames, nouts);
    
    int run = 0;
    
    // recall saved state
    finterface.recallState(rcfilename);
    
    // Test MIDI control
    for (int i = 0; i < 127; i++) {
        handler.handleData2(0, MidiStatus.MIDI_CONTROL_CHANGE, 0, i, 100);
        handler.handleData2(0, MidiStatus.MIDI_POLY_AFTERTOUCH, 0, i, 75);
        handler.handleData2(0, MidiStatus.MIDI_NOTE_ON, 0, i, 75);
        handler.handleData2(0, MidiStatus.MIDI_NOTE_OFF, 0, i, 75);
        handler.handleData2(0, MidiStatus.MIDI_PITCH_BEND, 0, i, 4000);
    }
    handler.handleData1(0, MidiStatus.MIDI_PROGRAM_CHANGE, 0, 10);
    handler.handleData1(0, MidiStatus.MIDI_AFTERTOUCH, 0, 10);
    
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
            for (int i = 0; i < nFrames; i++) {
                printf("%6d : ", linenum++);
                for (int c = 0; c < nouts; c++) {
                    FAUSTFLOAT f = normalize(ochan.buffers()[c][i]);
                    printf(" %8.6f", f);
                }
                printf("\n");
            }
            nbsamples -= nFrames;
        }
    } catch (Exception e) {
        cerr ~ "ERROR in '" ~ file ~ "' at line : " ~ i ~ "\n";
    }
    
    delete ichan;
    if (ochan != ichan) delete ochan;
    delete DSP;
}

class Meta {
nothrow:
@nogc:
    void declare(string name, string value) {}
}

// <<includeIntrinsic>>

// <<includeclass>>

// class Meta {
// nothrow:
// @nogc:
//     void declare(string name, string value) {}
// }

// class UI {
// nothrow:
// @nogc:
//     void declare(string id, string key, string value) {}
//     void declare(int id, string key, string value) {}
//     void declare(FAUSTFLOAT* id, string key, string value) {}

//     // -- layout groups

//     void openTabBox(string label) {}
//     void openHorizontalBox(string label) {}
//     void openVerticalBox(string label) {}
//     void closeBox() {}

//     // -- active widgets

//     void addButton(string label, FAUSTFLOAT* val) {}
//     void addCheckButton(string label, FAUSTFLOAT* val) {}
//     void addVerticalSlider(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}
//     void addHorizontalSlider(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}
//     void addNumEntry(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}

//     // -- passive display widgets

//     void addHorizontalBargraph(string label, FAUSTFLOAT* val, float min, float max) {}
//     void addVerticalBargraph(string label, FAUSTFLOAT* val, float min, float max) {}

// }

// class UIButton : UI
// {
//     this(FAUSTFLOAT state)
//     {
//         _state = state;
//     }
//     override void addButton(string label, FAUSTFLOAT* val) {
//         *val = _state;
//     }

// private:
//     FAUSTFLOAT _state;
// }

// class dsp {
// nothrow:
// @nogc:
// public:
//     int fSamplingFreq;
// }

// void printHeader(ref string file, mydsp dspObj, int numFrames)
// {
    
//     file ~= "number_of_inputs  :   " ~ to!string(dspObj.getNumInputs()) ~ "\n";
//     file ~= "number_of_outputs :   " ~ to!string(dspObj.getNumOutputs()) ~ "\n";
//     file ~= "number_of_frames  :  " ~ to!string(numFrames) ~ "\n";
// }

// void printSampleOutput(ref string file, int n, double[] outputValues)
// {
//     double customRound(double num, int precision)
//     {
//         immutable int trunc = cast(int)round(num * pow(10, precision));
//         return cast(double)trunc / pow(10, precision);
//     }

//     string s = format!"%6d :  "(n);
//     for(int i = 0; i < outputValues.length; ++i)
//     {
//         s ~= format!"%1.6f"(customRound(outputValues[i], 6));
//         if(i + 1 < outputValues.length)
//         {
//             s ~= " ";
//         }
//     }
//     file ~= s ~ '\n';
// }

// void main(string[] args)
// {
//     if(args.length < 2)
//     {
//         writeln("Error: no argument provided for IR file path");
//         return;
//     }

//     string irFilePath = args[1];
//     string fileText = "";
//     File irFile = File(irFilePath, "w+");
//     scope(exit) 
//     { 
//         irFile.write(fileText); 
//         irFile.close();
//     }
    
//     immutable int sampleRate = 44_100;
//     immutable int numFrames = 60_000;
//     immutable int blockSize = numFrames / 4;

//     mydsp dspObj = new mydsp();
//     dspObj.init(sampleRate);

//     printHeader(fileText, dspObj, numFrames);
//     runDSP(fileText, dspObj, numFrames / 4, sampleRate, blockSize);
// }

// void runDSP(ref string file, mydsp dspObj, int numFrames, int sampleRate, int blockSize)
// {
//     long bufferSize = long.max;

//     int numInputs = dspObj.getNumInputs();
//     int numOutputs = dspObj.getNumOutputs();
//     double*[] inputBuffers;
//     double*[] outputBuffers;

//     foreach(chan; 0..numInputs)
//     {
//         double* buffer = cast(double*)malloc(double.sizeof * numFrames);
//         for(int n = 0; n < numFrames; ++n)
//         {
//             buffer[n] = 0;
//         }
//         inputBuffers ~= buffer;
//     }

//     foreach(chan; 0..numOutputs)
//     {
//         double* buffer = cast(double*)malloc(double.sizeof * numFrames);
//         for(int n = 0; n < numFrames; ++n)
//         {
//             buffer[n] =  0.0f;
//         }
//         outputBuffers ~= buffer;
//     }

//     int cycle = 0;
//     int numFramesWritten = 0;
//     while(numFramesWritten < numFrames)
//     {
//         bufferSize = numFrames - numFramesWritten;
//         foreach(chan; 0..numInputs)
//         {
//             foreach(j; 0..bufferSize)
//             {
//                 inputBuffers[chan][j] = (numFramesWritten == 0 && j == 0) ? 1.0f : 0.0f;
//             }
//         }

//         if (cycle == 0)
//         {
//             UIButton buttonOn = new UIButton(1.0f);
//             dspObj.buildUserInterface(cast(UI*)&buttonOn);
//         }
//         else
//         {
//             UIButton buttonOff = new UIButton(0.0f);
//             dspObj.buildUserInterface(cast(UI*)&buttonOff);
//         }

//         dspObj.compute(cast(int)bufferSize, inputBuffers, outputBuffers);

//         for(int index = 0; index < bufferSize; ++index)
//         {
//             double[] outputValues = [];
//             foreach(chan; 0..numOutputs)
//             {
//                 outputValues ~= outputBuffers[chan][index];
//             }
//             printSampleOutput(file, cast(int)index, outputValues);
//             numFramesWritten++;
//         }

//         cycle++;
//     }


//     // scope(exit)
//     // {
//     //     foreach(chan; 0..numOutputs)
//     //     {
//     //         for(int index = 0; index < numFrames; ++index)
//     //         {
//     //             double sample = outputBuffers[chan][index];
//     //             printSampleOutput(file, cast(int)index, sample);
//     //         }
//     //     }
//     // }

//     // dspObj.compute(numFrames, inputBuffers, outputBuffers);
// }

// To be used in static context
static void runDSP(dsp* DSP, ref const string file, ref int linenum, int nbsamples, bool inpl = false, bool random = false)
{
    char[256] rcfilename;
    string filename = file;
    filename = filename.substr(0, filename.find ('.'));
    snprintf(rcfilename, 255, "%src", filename.c_str());
    
    FUI finterface;
    DSP.buildUserInterface(&finterface);
    
    // Soundfile
    TestMemoryReader memory_reader;
    SoundUI sound_ui = new SoundUI("", -1, &memory_reader);
    DSP.buildUserInterface(&sound_ui);
    
    // Get control and then 'initRandom'
    CheckControlUI controlui;
    DSP.buildUserInterface(&controlui);
    controlui.initRandom();
    
    // MIDI control
    midi_handler handler;
    MidiUI midi_ui = new MidiUI(&handler);
    DSP.buildUserInterface(&midi_ui);
    
    // Init signal processor and the user interface values
    DSP.init(44100);
    
    // Check getSampleRate
    if (DSP.getSampleRate() != 44100) {
        cerr ~ "ERROR runDSP in getSampleRate : " ~ DSP.getSampleRate() ~ "\n";
    }
    
    // Check default after 'init'
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runDSP in checkDefaults after 'init'\n";
    }
    
    // Check default after 'instanceResetUserInterface'
    controlui.initRandom();
    DSP.instanceResetUserInterface();
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runDSP in checkDefaults after 'instanceResetUserInterface'\n";
    }
    
    // Check default after 'instanceInit'
    controlui.initRandom();
    DSP.instanceInit(44100);
    if (!controlui.checkDefaults()) {
        cerr ~ "ERROR runDSP in checkDefaults after 'instanceInit'\n";
    }
    
    // To test that instanceInit properly init a cloned DSP
    DSP = DSP.clone();
    DSP.instanceInit(44100);
    
    // Init UIs on cloned DSP
    DSP.buildUserInterface(&finterface);
    DSP.buildUserInterface(&sound_ui);
    DSP.buildUserInterface(&midi_ui);
    
    int nins = DSP.getNumInputs();
    int nouts = DSP.getNumOutputs();
    
    channels* ichan = new channels(kFrames, ((inpl) ? max(nins, nouts) : nins));
    channels* ochan = (inpl) ? ichan : new channels(kFrames, nouts);
    
    int run = 0;
    
    // recall saved state
    finterface.recallState(rcfilename);
    
    // Test MIDI control
    for (int i = 0; i < 127; i++) {
        handler.handleData2(0, MidiStatus.MIDI_CONTROL_CHANGE, 0, i, 100);
        handler.handleData2(0, MidiStatus.MIDI_POLY_AFTERTOUCH, 0, i, 75);
        handler.handleData2(0, MidiStatus.MIDI_NOTE_ON, 0, i, 75);
        handler.handleData2(0, MidiStatus.MIDI_NOTE_OFF, 0, i, 75);
        handler.handleData2(0, MidiStatus.MIDI_PITCH_BEND, 0, i, 4000);
    }
    handler.handleData1(0, MidiStatus.MIDI_PROGRAM_CHANGE, 0, 10);
    handler.handleData1(0, MidiStatus.MIDI_AFTERTOUCH, 0, 10);
    
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
            for (int i = 0; i < nFrames; i++) {
                printf("%6d : ", linenum++);
                for (int c = 0; c < nouts; c++) {
                    FAUSTFLOAT f = normalize(ochan.buffers()[c][i]);
                    printf(" %8.6f", f);
                }
                printf("\n");
            }
            nbsamples -= nFrames;
        }
    } catch (Exception ex) {
        cerr ~ "ERROR in '" ~ file ~ "' at line : " ~ i ~ "\n";
    }
    
    delete ichan;
    if (ochan != ichan) delete ochan;
    delete DSP;
}

<<includeIntrinsic>>

<<includeclass>>

void main(string[] args)
{
    int linenum = 0;
    int nbsamples = 60_000;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new mydsp(), args[0], linenum, nbsamples/4);
    runDSP(new mydsp(), args[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
    
    return 0;
}
