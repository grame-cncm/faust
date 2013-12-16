#ifndef _utilities_H
#define _utilities_H

#include <string>

#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif

using namespace std;

string pathToContent(string path);

bool isStringInt(const char* word);

long lopt(char *argv[], const char *name, long def);

const char* loptions(char *argv[], const char *name, const char* def);

int lopt_Spe(int i, char *argv[], const char *name, char* path);

#endif