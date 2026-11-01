#ifndef PROJECT_FILES_MANAGER_H
#define PROJECT_FILES_MANAGER_H

#include <string>
#include <vector>
#include <set>

class ProjectFilesManager
{
public:
    /* Constructor */
    ProjectFilesManager(std::string&);

    /* Returns a list of DSP filenames (without the .dsp extension) stored on the disk at a specific location. */
    std::vector<std::string> getProjectFiles() const;

    /* Function used to load the contents of a dsp file. */
    bool load(const std::string&, std::wstring&);

    /* Function used to create a new dsp file.*/
    bool create(std::string&);

    /* Function used to store a dsp file on disk.*/
    bool writeFile(const std::string&, const std::wstring& contents) const;

    /* Function used to rename a dsp file.*/
    bool rename(const std::string&, const std::string&);

    /* Function used to remove a dsp file.*/
    bool remove(const std::string&);

    /* Returns true if the argument does not exist on the registry of the existing filenames.*/
    bool pfNameUnique(const std::string&);

private:

    std::string projectFilesDir;
    std::set<std::string> project_files;
    std::set<size_t> usedUntitledNumbers;
    std::string untitled_filename;    

    void scanProjectFileDir();
    void updateUntitledSet(const std::string&);
    size_t getNextUntitledNumber();
    bool removeUntitledNumber(const std::string&);
    std::string getFilePath(const std::string&) const;
};

#endif
