#ifndef PLUGIN_CONFIG_H
#define PLUGIN_CONFIG_H

#define STORAGE_DIRNAME "_faust"
#define DEFAULT_NAME_APP "Faust Interpreter Plugin"

#define PREVIEW_WINDOW_WIDTH 640
#define PREVIEW_WINDOW_HEIGHT 480

#include <string>

struct PluginConfiguration {
    
    std::string name_app {std::string(DEFAULT_NAME_APP)};
    
    struct Paths {
        std::string wwiseRoot;
        std::string exportPath;
        std::string faust_includedir;
        std::string faust_dspdir;
        std::string archfile;  
        std::string config = "Debug"; 
    }path;
    
    std::string plugin_type;
    std::string plugin_name;
    std::string author;
    std::string description;
    int num_inputs = 0;
    int num_outputs = 0;

    int sampleRate=0;
    int bufferSize=0;
    int speakersAvail=0;
    int maxSpeakersAvail=0;

    struct PreviewWindow {
        int width = int(PREVIEW_WINDOW_WIDTH);
        int height = int (PREVIEW_WINDOW_HEIGHT);
    }preview;

    void reset()
    {
        name_app=std::string(DEFAULT_NAME_APP); 
        plugin_type="";
        plugin_name="";
        author="";
        description="";
        num_inputs = 0;
        num_outputs = 0;
        sampleRate=0;
        speakersAvail = (maxSpeakersAvail != 0) ? maxSpeakersAvail : 0;
    }
};

#endif