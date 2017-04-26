#ifndef _CONFIGFILE_H_
#define _CONFIGFILE_H_

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

  Code author: Jernej Barbic
  CMU, 2005-2007
  Version 1.0

  A class to parse text configuration files. 
  See configFile-example.cpp and configFile-example.config for examples. 
  It is by far easier to look at the example first, than to proceed
  straight to reading the class interface.

  Supported types for option entries:
  int (integer)
  bool (boolean, true/false)
  float (single precision floating point)
  double (double precision floating point)
  char* (a C-style string)
  Vec3d (vector of three double values)
  string (std::string)
  vector<string> (0 to multiple lines of string)

  Configuration files are text files. The format for each option entry is:
  *<option name>
  <option value>

  Example:
  *temperature
  36.6

  *rainy
  # boolean option can accept both integer (0/1) or text (true/false) input
  false

  *color
  # Vec3d option can accept numbers separated by either comma "," or space " "
  #0.4, 0.8, 0.5
  0.4 0.8 0.5

  *street
  # string/char* option accepts one line of characters. Memory preallocation
  # is required for char* option
  Hoover

  *toDoList
  # vector<string> option can accept 0 to multiple lines of text
  wash car
  buy food
  repair chair

  Blank lines are ignored. 
  A line is a comment if it begins with a "#".
  The options can appear in arbitrary order. They need not follow the order
  in which they were created via addOption/addOptionOptional.

*/

#include <vector>
#include <string>
#include "vec3d.h"

class ConfigFile
{
public:
  ConfigFile();
  virtual ~ConfigFile();

  // === routines to define the valid option entries for your configuration file ===
  // each option entry is either mandatory, or optional (in which case you need to provide a default value)
  // option names are case IN-sensitive (i.e., upper/lower case does not matter)
  // "destLocation" will be overwritten with the value read from the configuration file when "parseOptions" is called (or default value will be used in case of optional option entries if a particular configuration file did not provide the entry)

  // routines to specify mandatory option entries
  // if "parseOptions" does not find a mandatory option in a particular configuration file, it will exit with a non-zero code
  int addOption(const char * optionName, int * destLocation);
  int addOption(const char * optionName, bool * destLocation);
  int addOption(const char * optionName, float * destLocation);
  int addOption(const char * optionName, double * destLocation);
  int addOption(const char * optionName, Vec3d * destLocation);
  int addOption(const char * optionName, char * destLocation); // for strings, you must pass a pointer to a pre-allocated string buffer (and not a pointer to a (char*) pointer)
  int addOption(const char * optionName, std::string * destLocation);
  int addOption(const char * optionName, std::vector<std::string> * destLocation); // allow arbitrary lines of strings

  // routines to specify option entries that are optional
  // if not specified in a particular config file, the value will default to the given default value
  template<class T>
  int addOptionOptional(const char * optionName, T * destLocation, const T & defaultValue);
  int addOptionOptional(const char * optionName, char * destLocation, const char * defaultValue);

  // === routines to parse config files ===
  // after you have specified your option entries with addOption and/or addOptionOptional, 
  // call "parseOptions" to open a particular configuration file and load the option values to their destination locations.
  int parseOptions(const char * filename, int verbose = 1); // returns 0 on success, and a non-zero value on failure
  int parseOptions(std::istream & in, int verbose = 1);     // makes it possible to parse from std::istream
  int parseOptions(FILE * fin, int verbose=1);              // makes it possible to parse from a file stream

  // after calling "parseOptions", you can print out the values of all options, to see the values that were read from the configuration file
  void printOptions() const;

  // === recursive parsing ===

  // following routines allow recursive parsing. first convert config file to a vector of entries (<option name>, <option value>)
  // then in each level, a ConfigFile object parses the entry vector, assigns the correct options that the object knows, 
  // and passes the unrecognized entries to the next level
  struct Entry 
  {
    std::string option;
    std::string value;
    int lineCount;
    Entry() : lineCount(-1) {}
  };
  typedef std::vector<Entry> Entries;

  // parse a file and return its config entries
  static int parse(const char * filename, Entries & entries, const char * stoppingString = "**EOF", int verbose = 1);
  static int parse(std::istream & in, Entries & entries, const char * stoppingString = "**EOF", int verbose = 1); // makes it possible to parse from a file stream
 
  // parse option from entries. If remainingEntries is provided, those entries that are not recognized are pushed into remainingEntries
  int parseOptions(const Entries & entries, Entries * remainingEntries = NULL, int verbose = 1);

  // === additional settings ===

  // (optional) set a stopping string (when it is encountered in a file, parsing will stop); default: **EOF
  // if the stopping string does not appear in a file, it will be parsed to the end
  void setStoppingString(const char * stoppingString);

  // you can disable printing out warnings (default: enabled)
  void suppressWarnings(int suppressWarnings_) { this->suppressWarnings_ = suppressWarnings_; }

protected:
  std::vector<std::string> optionNames;
  std::vector<int> optionTypes;
  std::vector<void*> destLocations;

  std::vector<bool> optionSet;
  
  int seekOption(const char * optionName); // returns -1 if not found

  template<class T>
  int addOptionHelper(const char * optionName, T * destLocation);

  int parseNumber(int type, const char * line, void * dest, int optionIndex, int verbose);

  static void strip(std::string & s);
  static void upperCase(char * s); // converts a string to upper case

  int suppressWarnings_;

  char stoppingString[32];
};

#endif

