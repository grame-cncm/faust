//UTILITIES.cpp

#include "utilities.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream> 
#include <fstream>

//Returns the content of a file passed in path
string pathToContent(const string& path)
{
    ifstream file(path.c_str(), std::ifstream::binary);
    
    file.seekg (0, file.end);
    int size = file.tellg();
    file.seekg (0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

//Verify if the word is a number
bool isStringInt(const char* word){
    
    bool returning = true;
    
    for (size_t i = 0; i < strlen(word); i++){
        if (!isdigit(word[i])){
            returning = false;
            break;
        }
    }
    return returning;
}

long lopt(char *argv[], const char *name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

const char* loptions(char *argv[], const char *name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

bool isopt(char *argv[], const char *name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

int lopt_Spe(int i, char *argv[], const char *name, char* path)
{
//	int	i;
//	for (i = 0; argv[i]; i++){
        if (!strcmp(argv[i], name)){
            strcpy(path, argv[i+1]);
        
            if (argv[i+2] && !strcmp(argv[i+2], "--n"))
                return atoi(argv[i+3]);
            else
                return 1;
        }
//    }	
    
    return 0;
}


