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
#include <fstream>
#include <ostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <cfenv>
#include <cmath>
#include <cfloat>
#include <stdlib.h>

static int gResult = 0;
static int gError = 0;

using namespace std;

static bool isopt(char* argv[], const char* name)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
    return false;
}

// responses compared so far : the test file may hold several in sequence,
// and its end after at least one complete response is the normal end
static int gResponses = 0;

// an end of file where a line was due : the file is empty or truncated, and
// the comparison must FAIL rather than stop (a truncated response passed
// silently before, and so did an empty one)
static bool truncated(istream* in, const char* which, const char* where)
{
    if (in->rdstate() & ifstream::eofbit) {
        cerr << which << " file ends in the " << where << (gResponses ? " of a further response" : "") << endl;
        gResult = 1;
        exit(gResult);
    }
    return false;
}

static bool compareFiles(istream* in1, istream* in2, double tolerance, bool is_part)
{
    string line1, line2, dummy;
    int input1, input2, output1, output2, count1, count2;
    
    // Read inputs
    {
        getline(*in1, line1);
        getline(*in2, line2);
        
        if ((in1->rdstate() & ifstream::eofbit)) {
            if (gResponses == 0) {
                cerr << "test file is empty" << endl;
                gResult = 1;
                exit(gResult);
            }
            return false;  // the normal end of the test file
        }
        
        if ((in2->rdstate() & ifstream::eofbit)) {
            cerr << "reference file is empty" << endl;
            gResult = 1;
            exit(gResult);
        }
        
        stringstream l1reader(line1);
        stringstream l2reader(line2);
        
        // Ignore "number_of_inputs" and ":" tokens
        l1reader >> dummy; l1reader >> dummy;
        l2reader >> dummy; l2reader >> dummy;
        
        l1reader >> input1;
        l2reader >> input2;
        
        if (input1 != input2) {
            cerr << "input1 : " << input1 << " different from input2 : " << input2 << endl;
            gResult = 1;
            exit(gResult);
        }
    }
        
    // Read outputs
    {
        getline(*in1, line1);
        getline(*in2, line2);
        truncated(in1, "test", "header");
        truncated(in2, "reference", "header");
        
        stringstream l1reader(line1);
        stringstream l2reader(line2);
        
        // Ignore "number_of_outputs" and ":" tokens
        l1reader >> dummy; l1reader >> dummy;
        l2reader >> dummy; l2reader >> dummy;
        
        l1reader >> output1;
        l2reader >> output2;
        
        if (output1 != output2) {
            cerr << "output1 : " << output1 << " different from output2 : " << output2 << endl;
            gResult = 1;
            exit(gResult);
        }
    }
    
    // Read count
    {
        getline(*in1, line1);
        getline(*in2, line2);
        truncated(in1, "test", "header");
        truncated(in2, "reference", "header");
        
        stringstream l1reader(line1);
        stringstream l2reader(line2);
        
        // Ignore "line_num" and ":" tokens
        l1reader >> dummy; l1reader >> dummy;
        l2reader >> dummy; l2reader >> dummy;
        
        l1reader >> count1;
        l2reader >> count2;
        
        if ((count1 != count2) && !is_part) {
            cerr << "count1 : " << count1 << " different from count2 : " << count2 << endl;
            gResult = 1;
            exit(gResult);
        }
    }
    
    // Compare samples
    for (int i = 0; i < count1; i++) {
        
        getline(*in1, line1);
        getline(*in2, line2);
        truncated(in1, "test", "samples");
        truncated(in2, "reference", "samples");
        
        stringstream l1reader(line1);
        stringstream l2reader(line2);
      
        // Keep line_num and ignore ":" tokens
        string line_num1, line_num2;
        l1reader >> line_num1; l1reader >> dummy;
        l2reader >> line_num2; l2reader >> dummy;
        
        double sample1, sample2;
        
        for (int j = 0; j < output1; j++) {
        
            l1reader >> sample1;
            l2reader >> sample2;
            double delta = fabs(sample1 - sample2);
            
            if (delta > tolerance) {
                
                cerr << "Line : " << line_num1 << " output : " << j << " sample1 : " << sample1 << " different from sample2 : " << sample2 << " delta : " << delta << endl;
                gResult = 1;
                if (gError++ > 10) {
                    cerr << "Too much errors, stops..." << endl;
                    exit(gResult);
                }
            }
        }
    }
    gResponses++;
    return true;
}

int main(int argc, char* argv[])
{
    double tolerance = 2e-06;
    if (argc == 4) {
        double param = strtod(argv[3], NULL);
        // -1 value used to take default value
        tolerance = (param > 0) ? param : tolerance;
    }
    
    // Possibly only compare a subpart of the reference file, starting from the beginning
    bool is_part = isopt(argv, "-part");
    
    // Test files may have several consecutive impulse responses, test all of them in sequence with the same reference
    ifstream test(argv[1]);
    bool compare = false;
    do {
        ifstream reference(argv[2]);
        compare = compareFiles(&test, &reference, tolerance, is_part);
    } while (compare);
    
    exit(gResult);
}
