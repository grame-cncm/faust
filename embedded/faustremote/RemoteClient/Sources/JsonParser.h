#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

#include <map>
#include <vector>
#include <string>

using namespace std;

struct itemInfo{
    
    string type;
    string label;
    string address;
    string init;
    string min;
    string max;
    string step;
    map<string,string> meta;
    
};

// ------------------------- external API ------------------------------

bool parseJson(const char*& p, map<string,string>& metadatas, vector<itemInfo*>& uiItems);

#endif // SIMPLEPARSER_H
