#ifndef PLUGIN_UTILS_H
#define PLUGIN_UTILS_H

#include <string>

namespace PluginUtils{

    /*
        Converts the plugin name to a valid format accepted by Wwise.
        Adjustments include:
            - Prefixing with "Dsp_" if name starts with a number or is invalid
            - Replacing spaces with underscores
            - Capitalizing the first character
    */
    std::string ensure_valid_plugin_name(const std::string& name);

    /* Function to move a file from source to dest. */
    bool moveFile(const std::string&, const std::string&);

    /* Function that creates a new unique directory named with a timestamp. 
     * This dir will be created within the directory of the string that is passed as an argument. */
    std::string createTempDir(const std::string&);

    /* Convert a wide string to string and vice versa. */
    std::string wstring2string(const std::wstring);
    std::wstring string2wstring(const std::string);

    /* Function that iterates over the last lines of the output.log file, and returns the plugin configuration printed on those lines. */
    std::string parsePluginConfiguration(const std::string&, const int numLines = 7);

    /* Writes a buffer to a UTF-16 encoded text file. */
    bool store_utf16_file(const std::string& path, const std::wstring& buffer);
    /* Loads a buffer from a UTF-16 encoded text file. */
    bool load_utf16_file(const std::string& path, std::wstring& buffer);

    /* Runs a script with administrative rights. Here it is used to build plugins using faust2wwise. */
    bool runElevatedScript(const std::wstring& exe,const std::wstring& args);
    /* Creates(/Generates) a script and stores it on disk on the fly. */
    void createBatScript(const std::string& scriptPath);

}

#endif
