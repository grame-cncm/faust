//UTILITIES.cpp

#include "utilities.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

//Returns the content of a file passed in path
string pathToContent(string path){
    
    QFile file(path.c_str());
    string Content;
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //        printf("impossible to open content\n");
        Content = "";
        //        return Content;
    }
    while (!file.atEnd()) {
        //        printf("Content read\n");
        QByteArray line = file.readLine();
        Content += line.data();
    }
    
    //    printf("CONTENT = %s\n", Content.c_str());
    return Content;
}

//Verify if the word is a number
bool isStringInt(const char* word){
    
    bool returning = true;
    
    for(size_t i=0; i<strlen(word); i++){
        if(!isdigit(word[i])){
            returning = false;
            break;
        }
    }
    return returning;
}

long lopt(int argc, char *argv[], const char *name, long def)
{
	int	i;
	for (i = 0; i<argc; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

const char* loptions(int argc, char *argv[], const char *name, const char* def)
{
	int	i;
	for (i = 0; i<argc; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}


