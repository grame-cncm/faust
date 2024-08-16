#include "PkgUrl.hh"
#include <regex>
#include "../errors/exception.hh"

PkgUrl::PkgUrl(std::string url)
{
    parse(url);
}

void PkgUrl::parse(std::string url)
{

    using namespace std::regex_constants; 

    std::regex pattern("^pkg:faust(?:/([_a-zA-Z]\\w*))?/([_a-zA-Z]\\w*.lib)@((?:\\d+)(?:\\.(?:\\d+)(?:\\.(?:\\d+))?)?)$", icase | ECMAScript); 

    std::smatch locater_parts;
    
    if(!std::regex_search(url,locater_parts,pattern))
        throw faustexception("Package URL Not Is Valid");

    this->author = locater_parts[1].str();
    this->libName = locater_parts[2].str();
    this->version = locater_parts[3].str();
}

std::string PkgUrl::getAuthor() const{
    return this->author;
}


bool PkgUrl::isPKgUrl(std::string url)
{
    using namespace std::regex_constants; 

    std::regex pattern("^pkg:faust(?:/([_a-zA-Z]\\w*))?/([_a-zA-Z]\\w*.lib)@((?:\\d+)(?:\\.(?:\\d+)(?:\\.(?:\\d+))?)?)$", icase | ECMAScript); 

    return std::regex_search(url,pattern);
}




std::string PkgUrl::getLibraryName() const{
    return this->libName;
}


std::string PkgUrl::getVersion() const {
    return this->version;
}

std::string PkgUrl::getPath() const {

    std::string path = "";

    if(!author.empty()){
        path += author + "/";
    }

    path += libName + "/";
    path += version + "/";
    path += libName;

    return path;
}