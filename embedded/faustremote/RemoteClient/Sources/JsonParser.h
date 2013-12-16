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

bool parseJson(const char*& p, map<string,string>& metadatas, vector<itemInfo*>& uiItems);

// ------------------------- implementation ------------------------------
bool parseMetaData (const char*& p, string& key, string& value, map<string,string>& metadatas);
bool parseUI (const char*& p, vector<itemInfo*>& uiItems, int& numItems);

void skipBlank(const char*& p);
bool parseError(const char*& p, const char* errmsg );
bool tryChar(const char*& p, char x);
bool parseChar(const char*& p, char x);
bool parseString(const char*& p, string& s);

#endif // SIMPLEPARSER_H
