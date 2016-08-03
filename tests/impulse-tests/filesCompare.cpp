#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <string>
#include <map>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <cfenv>
#include <cmath>
#include <cfloat>

#include "faust/gui/console.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/FUI.h"
#include "faust/audio/channels.h"


void compareFiles(std::istream* in1, std::istream* in2)
{
    std::string line1, line2, dummy;
    
    getline(*in1, line1);
    getline(*in2, line2);
    
    getline(*in1, line1);
    getline(*in2, line2);

    getline(*in1, line1);
    getline(*in2, line2);
    
    //std::cout << "line1 " << line1 << std::endl;
    //std::cout << "line2 " << line2 << std::endl;
  
    std::stringstream l1reader(line1);
    std::stringstream l2reader(line2);
    
    l1reader >> dummy; l1reader >> dummy;
    l2reader >> dummy; l2reader >> dummy;
    
    int cout1, cout2;
    
    l1reader >> cout1;
    l2reader >> cout2;
    
    //std::cout << "cout1 " << cout1 << std::endl;
    //std::cout << "cout2 " << cout2 << std::endl;
    
    if (cout1 != cout2) {
        std::cerr << "cout1 : " << cout1 << "different from : " << cout2 << std::endl;
        exit(1);
    }
    
    for (int i = 0; i < cout1; i++) {
        double sample1, sample2;
        
        getline(*in1, line1);
        getline(*in2, line2);
        
        std::stringstream l1reader(line1);
        std::stringstream l2reader(line2);
        
        l1reader >> dummy; l1reader >> dummy;
        l2reader >> dummy; l2reader >> dummy;
        
        l1reader >> sample1;
        l2reader >> sample2;
        
        if (fabs(sample1 - sample2) > 2e-06) {
            std::cerr << "line : " << i << " sample1 : " << sample1 << " different from sample2 : " << sample2 << std::endl;
            exit(1);
        }
    }
}

int main(int argc, char* argv[])
{
    std::ifstream reader1(argv[1]);
    std::ifstream reader2(argv[2]);
    compareFiles(&reader1, &reader2);
    exit(0);
}
