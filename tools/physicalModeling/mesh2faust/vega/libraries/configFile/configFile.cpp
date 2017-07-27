/*
  * Copyright (c) 2007, Carnegie Mellon University
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *     * Redistributions of source code must retain the above copyright
  *       notice, this list of conditions and the following disclaimer.
  *     * Redistributions in binary form must reproduce the above copyright
  *       notice, this list of conditions and the following disclaimer in the
  *       documentation and/or other materials provided with the distribution.
  *     * Neither the name of Carnegie Mellon University, nor the
  *       names of its contributors may be used to endorse or promote products
  *       derived from this software without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND ANY
  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY
  * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include "configFile.h"
using namespace std;

#define OPT_INT 0
#define OPT_BOOL 1
#define OPT_FLOAT 2
#define OPT_DOUBLE 3
#define OPT_VEC3D 4
#define OPT_CSTR 10
#define OPT_STRING 11
#define OPT_STRARR 20

ConfigFile::ConfigFile() : suppressWarnings_(0) 
{
  strcpy(stoppingString, "**EOF");
}

ConfigFile::~ConfigFile() {}

// finds a particular option name among all specified options
int ConfigFile::seekOption(const char * optionName)
{
  string upperOptionName = optionName;

  upperCase(&upperOptionName[0]);
  for(unsigned int i=0; i<optionNames.size(); i++)
  {
    if (upperOptionName == optionNames[i])
      return (int)i;
  }
  return -1;
}

void ConfigFile::printOptions() const
{
  for(unsigned int i=0; i<optionNames.size(); i++)
  {
    switch(optionTypes[i])
    {
      case OPT_INT:
        printf("%s: %d\n",optionNames[i].c_str(), *(int*)(destLocations[i]));
        break;

      case OPT_BOOL:
        printf("%s: %d\n",optionNames[i].c_str(), *(bool*)(destLocations[i]));
        break;

      case OPT_FLOAT:
        printf("%s: %G\n",optionNames[i].c_str(), *(float*)(destLocations[i]));
        break;

      case OPT_DOUBLE:
        printf("%s: %G\n",optionNames[i].c_str(), *(double*)(destLocations[i]));
        break;

      case OPT_VEC3D:
        printf("%s: %G, %G, %G\n", optionNames[i].c_str(), (*(Vec3d*)(destLocations[i]))[0], (*(Vec3d*)(destLocations[i]))[1], (*(Vec3d*)(destLocations[i]))[2]);
        break;

      case OPT_CSTR:
        printf("%s: %s\n",optionNames[i].c_str(), (char*)(destLocations[i]));
        break;

      case OPT_STRING:
	      printf("%s: %s\n",optionNames[i].c_str(), ((string*)(destLocations[i]))->c_str());
	       break;

      case OPT_STRARR:
        {
          vector<string> & vct = *(vector<string> *)(destLocations[i]);
          printf("%s: ", optionNames[i].c_str());
          for(size_t i = 0; i < vct.size(); i++) 
          {
            printf("%s", vct[i].c_str());
            if (i + 1 != vct.size())
              printf(", ");
          }
          printf("\n");
        }
        break;

      default:
        printf("Error: invalid type requested (1)\n");
    }
  }
}

// a generic routine to add a new option entry to the list of all options
template<class T>
int ConfigFile::addOptionHelper(const char * optionName, T * destLocation)
{
  if (seekOption(optionName) != -1)
  {
    if (!suppressWarnings_)
      printf("Warning: option %s already exists. Ignoring request to re-add it.\n",optionName);
    return 1;
  }
  std::string optionName_(optionName);

  // convert to uppercase
  for(unsigned int i=0; i< optionName_.size(); i++)
    optionName_[i] = toupper(optionName_[i]);

  optionNames.push_back(optionName_);
  destLocations.push_back((void*)destLocation);
  optionSet.push_back(false);
  return 0;
}

#define ADD_OPTION_METHOD(type, OPT_TYPE) \
  int ConfigFile::addOption(const char * optionName, type * destLocation) \
  { \
    int code; \
    if ((code = addOptionHelper(optionName, destLocation)) != 0) \
      return code; \
    optionTypes.push_back(OPT_TYPE); \
    return 0; \
  }

ADD_OPTION_METHOD(int, OPT_INT)

ADD_OPTION_METHOD(bool, OPT_BOOL)

ADD_OPTION_METHOD(float, OPT_FLOAT)

ADD_OPTION_METHOD(double, OPT_DOUBLE)

ADD_OPTION_METHOD(Vec3d, OPT_VEC3D)

ADD_OPTION_METHOD(char, OPT_CSTR)

ADD_OPTION_METHOD(string, OPT_STRING)

ADD_OPTION_METHOD(vector<std::string>, OPT_STRARR)

template<class T>
int ConfigFile::addOptionOptional(const char * optionName, T * destLocation, const T & defaultValue)
{
  int code = addOption(optionName,destLocation);
  *destLocation = defaultValue;
  optionSet[optionSet.size()-1] = true;
  return code;
}

int ConfigFile::addOptionOptional(const char * optionName, char * destLocation, const char * defaultValue)
{
  int code = addOption(optionName,destLocation);
  // must use memmove because strings may overlap
  memmove(destLocation, defaultValue, strlen(defaultValue) + 1);
  optionSet[optionSet.size()-1] = true;
  return code;
}

#define CHECK_FORMAT(cond, printStatement, error_no) \
  do \
  { \
    if (cond) \
    { \
      if (verbose) \
        printStatement; \
      return error_no; \
    } \
  } while(0)

#define CHECK_EMPTY_OPTION(cond) \
  CHECK_FORMAT(cond, printf("Error: empty option %d: %s\n", count, &line[0]), 2)

#define CHECK_DATA_WITHOUT_OPTION(cond) \
  CHECK_FORMAT(cond, printf("Error: dataline with no option %d: %s\n", count, &line[0]), 3)

#define CHECK_NO_DATALINE(cond) \
  CHECK_FORMAT(cond, printf("Error: No dataline for option %s\n", optionNames[optionIndex].c_str()), 4)

#define CHECK_EOF_REACHED(cond) \
  CHECK_FORMAT(cond, printf("Error: EOF reached without specifying option value.\n"), 5)

#define CHECK_INVALID_DATA(cond) \
  CHECK_FORMAT(cond, printf("Error: invalid dataline for option %s: %s.\n", optionNames[optionIndex].c_str(), line), 6)

#define CHECK_INVALID_BOOL(cond) \
  CHECK_FORMAT(cond, printf("Error: invalid boolean specification for option %s: %s.\n", optionNames[optionIndex].c_str(), line), 7)

#define CHECK_OPTION_SET \
  for(size_t i=0; i<optionNames.size(); i++) \
  { \
    if (!optionSet[i]) \
    { \
      if (verbose) \
        printf("Error: option %s didn't have an entry in the config file.\n",optionNames[i].c_str()); \
      return 1; \
    } \
  }

int ConfigFile::parseNumber(int type, const char * line, void * dest, int optionIndex, int verbose)
{
  if (type == OPT_INT)
    CHECK_INVALID_DATA(sscanf(line, "%d", (int*)dest) == 0);
  else if (type == OPT_FLOAT)
    CHECK_INVALID_DATA(sscanf(line, "%f", (float*)dest) == 0);
  else if (type == OPT_DOUBLE)
    CHECK_INVALID_DATA(sscanf(line, "%lf", (double*)dest) == 0);
  else if (type == OPT_BOOL)
  {
    if (strncmp(line,"true",4) == 0)
      *((bool *)dest) = true;
    else if (strncmp(line,"false",5) == 0)
      *((bool *)dest) = false;
    else 
    {
      int number = 0;
      CHECK_INVALID_BOOL(sscanf(line, "%d", &number) == 0);
      *((bool *)dest) = (number == 0 ? false : true);
    }
  }
  else if (type == OPT_VEC3D) 
  {
    istringstream ss(line);
    Vec3d vec(0.);
    ss >> vec[0];
    CHECK_INVALID_DATA(ss.fail());
    for(int i = 1; i < 3; i++) 
    {
      ss >> ws;
      int separator = ss.peek(); // peek next character
      CHECK_INVALID_DATA(separator == EOF);
      if (separator == ',')
      {
        char character = 0;
        ss >> character; // eat that separator
      }
      ss >> vec[i];
      CHECK_INVALID_DATA(ss.fail());
    }
    *((Vec3d*)dest) = vec;
  }
  return 0;
}

int ConfigFile::parseOptions(const Entries & entries, Entries * remainingEntries, int verbose) 
{
  for(size_t i = 0; i < entries.size(); i++) 
  {
    const Entry & entry = entries[i];
    const string & option = entry.option;
    const string & value = entry.value;

    int optionIndex = seekOption(option.c_str());
    //printf("Read entry: %s . Option index: %d .\n", &line[1], index);
    if (optionIndex == -1) 
    {  
      if (remainingEntries != NULL) 
        remainingEntries->push_back(entry);
      else if ((verbose) && (!suppressWarnings_))
        printf("Warning: unknown option on line %d: %s\n",entry.lineCount,option.c_str());
      continue;
    }

    int type = optionTypes[optionIndex];
    void * dest = destLocations[optionIndex];
    const char * line = value.c_str();

    CHECK_NO_DATALINE(type != OPT_STRARR && value.size() == 0);

    if (type == OPT_CSTR) 
    {
      size_t length = 0;
      if ((length = value.find('\n')) == value.npos)
        length = value.size();
      memcpy(dest, value.c_str(), length);
      ((char*)dest)[length] = '\0';
    }
    else if (type == OPT_STRING) 
    {
      size_t length = 0;
      if ((length = value.find('\n')) == value.npos)
        length = value.size();
      *((string *)dest) = value.substr(0, length);
    }
    else if (type == OPT_STRARR) 
    {
      if (value.size() > 0) 
      {
        size_t start = 0, pos = 0;
        while((pos = value.find('\n', start)) != value.npos) 
        {
          ((vector<string> *)dest)->push_back(value.substr(start, pos - start));
          start = pos+1;
        }
        ((vector<string> *)dest)->push_back(value.substr(start));
      }
    }
    else
    {
      int ret = 0;
      if ((ret = parseNumber(type, line ,dest, optionIndex, verbose)) != 0)
        return ret;
    }
    optionSet[optionIndex] = true;
  } // end for entries

  CHECK_OPTION_SET;
  return 0;
}

static char * stripc(char * s) 
{
  size_t start = 0;
  for(; s[start] != '\0' && isspace(s[start]); start++) ;
  if (s[start] == '\0')  // empty string
    return s+start;

  size_t end = strlen(s) - 1;
  for(; isspace(s[end]); end--) ;
  s[end+1] = '\0';
  return s+start;
}

int ConfigFile::parseOptions(FILE * fin, int verbose)
{
  int count = 0;
  char lineBuffer[4096];

  int optionIndex = -1;
  bool dataRead = false; // whether data entry has been read
  int type = 0;          // option type: INT, BOOL, ...
  void * dest = NULL;
  bool skipUnknownOption = false;
  while (fgets(lineBuffer,4096,fin) != NULL)
  {
    count++;
    const char * line = stripc(lineBuffer);
    
    // ignore blank lines and comments
    if ((line[0] == '#') || (line[0] == '\0'))
      continue;
    if (strcmp(line, stoppingString) == 0)
      break;

    if (line[0] == '*') // option line
    {
      CHECK_NO_DATALINE(optionIndex >= 0 && dataRead == false); // check no data for the last option
      CHECK_EMPTY_OPTION(line[1] == '\0'); // option line with empty option

      optionIndex = seekOption(&line[1]);
      dataRead = false; // reset dataRead because a new option is found
      skipUnknownOption = false;
      if (optionIndex == -1) // cannot find the option
      {
        if (verbose && (!suppressWarnings_))
          printf("Warning: unknown option on line %d: %s\n", count, &line[1]);
        skipUnknownOption = true;
        continue;
      }
      type = optionTypes[optionIndex];
      dest = destLocations[optionIndex];
      if (type == OPT_STRARR)
      {
        dataRead = true;       //for STRARR, 0 to multiple lines of string are allowed
        optionSet[optionIndex] = true;
      }
    }
    else // found data entry
    {
      if (skipUnknownOption)
        continue;
      CHECK_DATA_WITHOUT_OPTION(optionIndex == -1); // check data entry with no corresponding option

      if (type == OPT_CSTR)
        strcpy((char*)dest, line);
      else if (type == OPT_STRING)
        *((string *)dest) = line;
      else if (type == OPT_STRARR)
        ((vector<string> *)dest)->push_back(line);
      else
      {
        int ret = 0;
        if ((ret = parseNumber(type, line ,dest, optionIndex, verbose)) != 0)
          return ret;
      }
      optionSet[optionIndex] = true;
      dataRead = true;
    } // end if found data entry
  } // end while
  CHECK_EOF_REACHED(optionIndex >= 0 && dataRead == false);

  CHECK_OPTION_SET;
  return 0;
}

// parse a file and return its config entries
int ConfigFile::parse(const char * filename, Entries & entries, const char * stoppingString, int verbose)
{
  ifstream fin(filename, ios::binary);
  if (!fin)
  {
    printf("Error: could not open option file %s\n",filename);
    return 1;
  }
  return parse(fin, entries, stoppingString, verbose);
}

// parse a file and return its config entries
int ConfigFile::parse(std::istream & fin, Entries & entries, const char * stoppingString, int verbose)
{
  if (!fin)
    return 1;

  string line;
  int count = 0;
  // bool dataRead = false;
  Entry entry;
  while(!fin.eof()) 
  {
    line.clear();
    getline(fin, line);
    count++;

    strip(line); // remove blank characters at the beginning and end
    
    // ignore blank lines and comments
    if (line.size() == 0 || line[0] == '#')
      continue;
    if (strcmp(line.c_str(), stoppingString) == 0)
      break;

    // a new entry found
    if (line[0] == '*') 
    {
      // we only push an entry to entries when a new option has found
      // in this way we can handle option with multiple lines
      if (entry.option.size() > 0)
        entries.push_back(entry);

      entry.option.clear();
      entry.value.clear();

      entry.option = &line[1];
      entry.lineCount = count;
      CHECK_EMPTY_OPTION(entry.option.size() == 0);
    }
    else // add entry value. Append data to the end of existing data, separated by \n
    {
      // check if data entry with no corresponding option
      CHECK_DATA_WITHOUT_OPTION(entry.option.size() == 0);
      if (entry.value.size() > 0)
        entry.value.append("\n");
      entry.value.append(line);
    }
  } // end while (!fin.eof())
  if (entry.option.size() > 0) // if there is a remaining entry
    entries.push_back(entry);
  return 0;
}

int ConfigFile::parseOptions(const char * filename, int verbose)
{
  FILE * fin = fopen(filename,"r");
  if (!fin)
  {
    printf("Error: could not open option file %s\n",filename);
    return 1;
  }
  int code = parseOptions(fin, verbose);
  fclose(fin);
  return code;
}

int ConfigFile::parseOptions(std::istream & in, int verbose)
{
  vector<Entry> entries;
  if (parse(in, entries, stoppingString) != 0)
    return 1; 
  return parseOptions(entries, NULL, verbose);
}

void ConfigFile::strip(string & s) 
{
  if (s.size() == 0) 
    return;
  size_t start = 0;
  for(; start < s.size() && isspace(s[start]); start++) ;
  if (start == s.size()) 
  {
    s.clear();
    return;
  }
  size_t end = s.size() - 1;
  for(; isspace(s[end]); end--) ;
  assert(start <= end);
  s = s.substr(start, end - start + 1);
}

// convert string to uppercase
void ConfigFile::upperCase(char * s)
{
  for(size_t i=0; i<strlen(s); i++)
    s[i] = toupper(s[i]);
}

void ConfigFile::setStoppingString(const char * stoppingString_)
{
  if (strlen(stoppingString_) >= 31)
  {
    printf("Warning: proposed stopping string %s is too long. Stopping string not modifed.\n", stoppingString_);
    return;
  }
  strcpy(stoppingString, stoppingString_);
}

template int ConfigFile::addOptionOptional<bool>(const char * optionName, bool * destLocation, const bool & defaultValue);
template int ConfigFile::addOptionOptional<int>(const char * optionName, int * destLocation, const int & defaultValue);
template int ConfigFile::addOptionOptional<float>(const char * optionName, float * destLocation, const float & defaultValue);
template int ConfigFile::addOptionOptional<double>(const char * optionName, double * destLocation, const double & defaultValue);
template int ConfigFile::addOptionOptional<Vec3d>(const char * optionName, Vec3d * destLocation, const Vec3d & defaultValue);
template int ConfigFile::addOptionOptional<string>(const char * optionName, string * destLocation, const string & defaultValue);
template int ConfigFile::addOptionOptional<vector<string> >(const char * optionName, vector<string> * destLocation, const vector<string> & defaultValue);

