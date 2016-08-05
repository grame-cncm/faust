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
#include <stdlib.h>

#include "faust/gui/console.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/FUI.h"
#include "faust/audio/channels.h"

static int gResult = 0;
static int gError = 0;

void compareFiles(std::istream* in1, std::istream* in2, float tolerance)
{
    std::string line1, line2, dummy;
    int input1, input2, output1, output2, count1, count2;
    
    // Read inputs
    {
        getline(*in1, line1);
        getline(*in2, line2);
        
        std::stringstream l1reader(line1);
        std::stringstream l2reader(line2);
        
        l1reader >> dummy; l1reader >> dummy;
        l2reader >> dummy; l2reader >> dummy;
        
        l1reader >> input1;
        l2reader >> input2;
        
        if (input1 != input2) {
            std::cerr << "input1 : " << input1 << "different from : " << input2 << std::endl;
            gResult = 1;
            exit(gResult);
        }
    }
        
    // Read outputs
    {
        getline(*in1, line1);
        getline(*in2, line2);
        
        std::stringstream l1reader(line1);
        std::stringstream l2reader(line2);
        
        l1reader >> dummy; l1reader >> dummy;
        l2reader >> dummy; l2reader >> dummy;
        
        l1reader >> output1;
        l2reader >> output2;
        
        if (output1 != output2) {
            std::cerr << "output1 : " << output1 << "different from : " << output2 << std::endl;
            gResult = 1;
            exit(gResult);
        }
    }
    
    // Read count
    {
        getline(*in1, line1);
        getline(*in2, line2);
        
        std::stringstream l1reader(line1);
        std::stringstream l2reader(line2);
        
        l1reader >> dummy; l1reader >> dummy;
        l2reader >> dummy; l2reader >> dummy;
        
        l1reader >> count1;
        l2reader >> count2;
        
        if (count1 != count2) {
            std::cerr << "count1 : " << count1 << "different from : " << count2 << std::endl;
            gResult = 1;
            exit(gResult);
        }
    }
    
    // Compare samples
    for (int i = 0; i < count1; i++) {
        double sample1, sample2;
        
        getline(*in1, line1);
        getline(*in2, line2);
        
        std::stringstream l1reader(line1);
        std::stringstream l2reader(line2);
        
        l1reader >> dummy; l1reader >> dummy;
        l2reader >> dummy; l2reader >> dummy;
        
        for (int j = 0; j < output1; j++) {
        
            l1reader >> sample1;
            l2reader >> sample2;
            double delta = fabs(sample1 - sample2);
            
            if (delta > tolerance) {
                std::cerr << "line : " << i << " output : " << j << " sample1 : " << sample1 << " different from sample2 : " << sample2 << " delta : " << delta << std::endl;
                gResult = 1;
                if (gError++ > 10) {
                    std::cerr << "Too much errors, stops..." << std::endl;
                    exit(gResult);
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    std::ifstream reader1(argv[1]);
    std::ifstream reader2(argv[2]);
    float tolerance = 2e-06;
    if (argc == 4) {
        tolerance = strtod(argv[3], NULL);
    }
    compareFiles(&reader1, &reader2, tolerance);
    exit(gResult);
}
