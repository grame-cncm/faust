#include "plugin_utils.h"
#include <cctype>
#include <filesystem>
#include <iostream>
#include <deque>

// for the createTempDir
#include <chrono>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <locale>
#include <codecvt>


// for file utils
#include <vector>
#include <cstdio>


namespace PluginUtils
{

    std::string ensure_valid_plugin_name(const std::string& name) {
        std::string valid = name;

        // replace spaces with underscores
        for (auto& c : valid) {
            if (c == ' ') {
                c = '_';
            }
        }

        // ff empty or first char not alphabetic or '_' --> prepend "Dsp_"
        if (valid.empty() || !(std::isalpha(valid[0]) || valid[0] == '_')) {
            valid = "Dsp_" + valid;
        }

        // capitalize first char
        if (!valid.empty()) {
            valid[0] = static_cast<char>(std::toupper(valid[0]));
        }

        return valid;
    }


    bool moveFile(const std::string& sourcePath, const std::string& destPath)
    {
        try {
            std::filesystem::path src(sourcePath);
            std::filesystem::path dst(destPath);

            if (!std::filesystem::exists(src)) {
                std::cerr << "Source file does not exist: " << src << '\n';
                return false;
            }

            std::filesystem::copy_file(src, dst, std::filesystem::copy_options::overwrite_existing);
            std::filesystem::remove(src); // Delete original
            return true;
        } 
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << '\n';
            return false;
        }
    }

    // TODO: discard timestamp and use the plugin name for the new directory.
    std::string createTempDir(const std::string& exportPath)
    {
        std::ostringstream timestamp;
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        timestamp << std::put_time(std::localtime(&now_time_t), "%Y%m%d_%H%M%S");

        std::filesystem::path tempDirectory = std::filesystem::path( exportPath + "/" + timestamp.str());

        try {
            std::filesystem::create_directories(tempDirectory);
            // std::filesystem::remove(tempDirectory);          //TODO : uncomment later
        } catch (const std::filesystem::filesystem_error& e) {
            // handle failure to create directory
            return false;
        }
        return tempDirectory.string();
    }   
    
    std::string wstring2string(const std::wstring wstr)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }

    std::wstring string2wstring(const std::string str)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(str);   
    }


    std::string parsePluginConfiguration(const std::string& filepath, int numLines)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            return {};
        }

        std::deque<std::string> buffer;
        std::string line;
        while (std::getline(file, line)) {
            buffer.push_back(line);
            if (buffer.size() > static_cast<size_t>(numLines))
                buffer.pop_front();
        }

        buffer.pop_front();// discard last line;

        std::ostringstream out;
        for (const auto& l : buffer)
            out << l << '\n';

        return out.str();
    }

    bool load_utf16_file(const std::string& path, std::wstring& buffer)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file) return false;

        // Read raw bytes
        std::vector<char> bytes(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        // Must be even-sized (UTF-16)
        if (bytes.size() % 2 != 0)
            return false;

        buffer.resize(bytes.size() / 2);
        memcpy(buffer.data(), bytes.data(), bytes.size());

        return true;
    }

    bool store_utf16_file(const std::string& path, const std::wstring& buffer)
    {
        std::ofstream file(path, std::ios::binary | std::ios::trunc);
        if (!file) return false;

        file.write(
            reinterpret_cast<const char*>(buffer.data()),
            buffer.size() * sizeof(wchar_t)
        );

        return true;
    }

    #include <windows.h>
    #include <shellapi.h>
    bool runElevatedScript(const std::wstring& exe,const std::wstring& args)
    {
        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.fMask = SEE_MASK_NOCLOSEPROCESS;
        sei.lpVerb = L"runas";        // elevation
        sei.lpFile = exe.c_str();
        sei.lpParameters = args.c_str();
        sei.nShow = SW_SHOWNORMAL;

        if (!ShellExecuteExW(&sei))
            return false;

        // wait to finish
        WaitForSingleObject(sei.hProcess, INFINITE);
        DWORD exitCode = 0;
        GetExitCodeProcess(sei.hProcess, &exitCode);
        CloseHandle(sei.hProcess);

        return exitCode == 0;
    }


    void createBatScript(const std::string& scriptPath)
    {
        if (!std::filesystem::exists(scriptPath))
        {
            std::ofstream out(scriptPath);
            out <<
            R"(@echo off
REM Parameters
set "TempDir=%1"
set "PluginName=%2"
set "UseDouble=%3"
set "IsOutOfPlace=%4"

echo Building plugin in elevated mode...
cd /d "%TempDir%"

REM Convert boolean flag into faust argument
set "DP_FLAG="
if "%UseDouble%"=="1" (
    set "DP_FLAG=-double"
)

REM Out-of-place flag (empty if not enabled)
set "OP_FLAG="
if "%IsOutOfPlace%"=="1" (
    set "OP_FLAG=--out-of-place"
)

faust2wwise "%PluginName%.dsp" %DP_FLAG% %OP_FLAG% > output.log 2>&1
exit /b %ERRORLEVEL%
            )";
            out.close();
        }
    }
}