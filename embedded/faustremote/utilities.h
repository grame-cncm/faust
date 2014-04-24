#ifndef _utilities_H
#define _utilities_H

#include <string>

using namespace std;

string pathToContent(const string& path);

bool isInt(const char* word);

long lopt(char *argv[], const char *name, long def);

bool isopt(char *argv[], const char *name);

const char* loptions(char *argv[], const char *name, const char* def);

int lopt_Spe(int i, char *argv[], const char *name, char* path);

#endif
