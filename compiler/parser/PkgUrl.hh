#pragma once

#include <string>

class PkgUrl
{
private:
    std::string version;
    std::string author;
    std::string libName;

    void parse(std::string);
public:
  
    PkgUrl(std::string);

    std::string getVersion() const;
    std::string getAuthor() const;
    std::string getLibraryName() const;
    std::string getPath() const;

    static bool isPKgUrl(std::string);
};