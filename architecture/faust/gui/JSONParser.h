/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <map>
#include <vector>
#include <string>

struct itemInfo {
    std::string type;
    std::string label;
    std::string address;
    std::string init;
    std::string min;
    std::string max;
    std::string step;
    std::map<std::string,std::string> meta;
};

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Advance pointer p to the first non blank character
static void skipBlank(const char*& p)
{
    while (isspace(*p)) { p++; }
}

// Parse a quoted string "..." and store the result in s, reports an error if it fails
static bool parseString(const char*& p, std::string& s)
{
    std::string str;
    
    skipBlank(p);
    
    const char* saved = p;
    
    if (*p++ == '"') {
        while ((*p != 0) && (*p != '"')) {
            str += *p++;
        }
        if (*p++=='"') {
            s = str;
            return true;
        }
    }
    p = saved;
    return false;
}

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    std::cerr << "Parse error : " << errmsg << " here : " << p << std::endl;
    return true;
}

// Parse character x, but don't report error if fails
static bool tryChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

// Parse character x, reports an error if it fails
static bool parseChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
//
static bool parseMetaData(const char*& p, std::string& key, std::string& value, std::map<std::string,std::string>& metadatas)
{
    if (parseString(p, key)){
        if (key.compare("meta") == 0){
            if (parseChar(p, ':') && parseChar(p, '[') && parseChar(p, '{')) {
                do {
                    std::string key1;
                    std::string value1;
                    if (parseMetaData(p, key1, value1, metadatas)) {
                        metadatas[key1] = value1;
                    }
                } while (tryChar(p, ','));
                
                return parseChar(p, '}') && parseChar(p, ']');
            } else {
                return false;
            }
        } else {
           return parseChar(p, ':') && parseString(p, value);
        }
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
//
static bool parseUI(const char*& p, std::vector<itemInfo*>& uiItems, int& numItems)
{
    if (parseChar(p, '{')) {
        
        std::string label;
        std::string value;
        
        do {
            
            if (parseString(p, label)) {
                
                if (label.compare("type") == 0) {
                    
                    if (uiItems.size() != 0)
                        numItems++;
                    
                    if (parseChar(p, ':') && parseString(p, value)) {   
                        
                        itemInfo* item = new itemInfo;
                        item->type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label.compare("label") == 0) {
                    if (parseChar(p, ':') && parseString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->label = value;
                    }
                }
                
                else if (label.compare("address") == 0){
                    if (parseChar(p, ':') && parseString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->address = value;
                    }
                }
                
                else if (label.compare("meta") == 0) {
                    
                    std::string metaKey, metaValue;
                    if (parseChar(p, ':') && parseChar(p,'[')) {
                        
                        do { 
                            if (parseChar(p,'{') && parseString(p, metaKey) && parseChar(p, ':') && parseString(p, metaValue) && parseChar(p,'}')) {
                                itemInfo* item = uiItems[numItems];
                                item->meta[metaKey] = metaValue;
                            }
                            
                        } while (tryChar(p,','));
                        if (!parseChar(p,']'))
                            return false;
                    }
                }
                
                else if (label.compare("init") == 0) {
                    if (parseChar(p, ':') && parseString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->init = value;
                    }
                }
                
                else if (label.compare("min") == 0){
                    if (parseChar(p, ':') && parseString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->min = value;
                    }
                }
                
                else if (label.compare("max") == 0){
                    if (parseChar(p, ':') && parseString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->max = value;
                    }
                }
                
                else if (label.compare("step") == 0){
                    if (parseChar(p, ':') && parseString(p, value)){
                        itemInfo* item = uiItems[numItems];
                        item->step = value;
                    }
                }
                
                else if (label.compare("items") == 0) {
                    
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        
                        do { 
                            if (!parseUI(p, uiItems, numItems))
                                return false;
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo* item = new itemInfo;
                            item->type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                return false;
            }
            
        } while (tryChar(p, ','));
        
        return parseChar(p, '}');
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse full json record describing a json/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
// This function is used by targetsDescriptionReceived() the remote  DSP to decode the result of 
//
bool parseJson(const char*& p, std::map<std::string,std::string>& metadatas, std::vector<itemInfo*>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        
        if (parseMetaData(p, key, value, metadatas)) {
            metadatas[key] = value;
        } else {
            if (key.compare("ui") == 0) {
                int numItems = 0;
                parseChar(p,'[') && parseUI(p, uiItems, numItems);
            }
        }
    } while (tryChar(p,','));
    
    return parseChar(p, '}');
}

#endif // JSON_PARSER_H
