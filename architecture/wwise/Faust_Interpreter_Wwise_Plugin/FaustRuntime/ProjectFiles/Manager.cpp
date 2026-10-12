#include "Manager.h"
#include "entry_code.h"
#include "PluginUtils/plugin_utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <filesystem>

#define UNTITLED_FILENAME "Untitled"
#define PROJECT_FILES_SUBDIR "ProjectFiles"
#define DEFAULT_CODE_FILENAME "default_entry_code"

ProjectFilesManager::ProjectFilesManager(std::string& exportPath)
    : projectFilesDir(exportPath+'/'+ std::string(PROJECT_FILES_SUBDIR))
    , untitled_filename(std::string(UNTITLED_FILENAME))
{
    scanProjectFileDir();
}

std::vector<std::string> ProjectFilesManager::getProjectFiles() const { 
    std::vector<std::string> filenames; // without extension
    for (const std::string& pf : project_files)
    {
        filenames.push_back(pf);
    }
    return filenames; 
}

bool ProjectFilesManager::load(const std::string& filename, std::wstring& dspCode)
{

    if (project_files.find(filename) == project_files.end())
    {
        // return default
        std::string code = std::string(default_entry_code);
        dspCode = PluginUtils::string2wstring(code);
        return false;
    }
    
    std::string current_file_path = getFilePath(filename);
    
    bool fileLoaded = PluginUtils::load_utf16_file(current_file_path, dspCode);
    
    return fileLoaded;
}


bool ProjectFilesManager::create(std::string& filename)
{
    filename = untitled_filename + std::to_string(getNextUntitledNumber());

    std::string filepath = getFilePath(filename);
    if (std::filesystem::exists(filepath))
    {
        std::cerr << "File already exists: " << filepath << "\n";
        return false;
    }

    if (!writeFile(filename, PluginUtils::string2wstring(std::string(default_entry_code))))
        return false;

    project_files.insert(filename);
    return true;
}

bool ProjectFilesManager::writeFile(const std::string& filename, const std::wstring& contents) const
{   
    const std::string filepath = getFilePath(filename);
    return PluginUtils::store_utf16_file(filepath,contents);
}

bool ProjectFilesManager::rename(const std::string& oldName, const std::string& newName)
{
    // remove untitled number from registry
    if (!removeUntitledNumber(oldName)){
        std::cout << "Entry "<<oldName << " is not "<<untitled_filename<<std::endl;
    }

    // update project_files
    if (project_files.find(oldName) != project_files.end())
    {
        project_files.erase(oldName);
        project_files.insert(newName);
    }

    // rename the actual file on disk
    try {
        std::filesystem::path old_file = std::filesystem::path(getFilePath(oldName));
        std::filesystem::path new_file = std::filesystem::path(getFilePath(newName));

        std::cout << "Renaming "<<oldName<<" to "<<newName<<std::endl;

        // rename file on disk
        std::filesystem::rename(old_file, new_file);

        std::cout << "Renamed "<<oldName<<" to "<<newName<<" successfully."<<std::endl;
        
        return true;
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Renaming "<<oldName<<" to "<<newName<<" failed: " << e.what() << '\n';
        return false;
    }
}

bool ProjectFilesManager::remove(const std::string& name)
{
    if (!project_files.empty())
    {
        // remove untitled number from registry
        if (!removeUntitledNumber(name)){
            std::cout << "Entry "<<name << " is not "<<untitled_filename<<std::endl;
        }

        // remove from set
        if (project_files.find(name) != project_files.end())
        {
            project_files.erase(name);
        }
    
        // remove the file
        try{
            std::string filepath = getFilePath(name);        
            std::filesystem::path file_path(filepath);
        
            std::cout<<"Removing the file "<<filepath<<"."<<std::endl;

            if (!std::filesystem::exists(file_path))
            {
                std::cerr<<"Can't remove file."<<filepath<<" does not exist"<<std::endl;
                return false;
            }

            std::filesystem::remove(file_path);

            std::cout<<"File "<<filepath<<" removed successfully."<<std::endl;
            return true;
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Remove failed: " << e.what() << '\n';
            return false;
        }
    }
    return false;
}

bool ProjectFilesManager::pfNameUnique(const std::string& name){
    return (project_files.find(name) == project_files.end());
}

void ProjectFilesManager::scanProjectFileDir()
{
    // only the first time , when the dir is not yet created.
    if (!std::filesystem::exists(projectFilesDir))
    {
        std::filesystem::create_directories(projectFilesDir);
    }

    for (auto& entry : std::filesystem::directory_iterator(projectFilesDir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".dsp")
        {
            std::string filename = entry.path().stem().string();
            project_files.insert(filename);
            updateUntitledSet(filename);
        }
    }

    // create a default file if there are not any others yet
    if (project_files.empty())
    {
        std::string filename = std::string(DEFAULT_CODE_FILENAME);
        writeFile(
            filename,
            PluginUtils::string2wstring(std::string(default_entry_code))
        );
        project_files.insert(filename);
    }
}

void ProjectFilesManager::updateUntitledSet(const std::string& filename)
{
    // if filename starts with untitled_filename
    if (filename.rfind(untitled_filename, 0) == 0)
    {
        std::string numberPart = filename.substr(untitled_filename.size()); // the numeric part
        size_t dotPos = numberPart.find('.');
        numberPart = numberPart.substr(0, dotPos);
        usedUntitledNumbers.insert(std::stoi(numberPart));
    }
}

size_t ProjectFilesManager::getNextUntitledNumber()
{
    size_t i = 1;
    if (!usedUntitledNumbers.empty())
    {
        int maxValue = *usedUntitledNumbers.rbegin(); // get the max value of the set
        while (i<=(maxValue+1))                     // iterate until reaching the max number
        {
            if (usedUntitledNumbers.find(i) == usedUntitledNumbers.end())
            {
                // first unused number
                usedUntitledNumbers.insert(i);
                break; 
            }
            ++i;
        }
    }
    usedUntitledNumbers.insert(i);
    return i;
}

bool ProjectFilesManager::removeUntitledNumber(const std::string& filename)
{
    // if filename starts with `Untitled`
    if (filename.rfind(untitled_filename, 0) == 0)
    {
        std::string numberPart = filename.substr(untitled_filename.size());
        usedUntitledNumbers.erase(std::stoi(numberPart));
        return true;
    }
    return false;
}

std::string ProjectFilesManager::getFilePath(const std::string& filename) const
{
    return projectFilesDir + '/'+ filename + ".dsp";
}
