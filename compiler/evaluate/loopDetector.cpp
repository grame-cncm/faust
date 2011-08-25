#include "loopDetector.hh"
#include "ppbox.hh"

bool loopDetector::detect(Tree t)
{
    fPhase++;
    int w = fPhase%fBuffersize;
    fBuffer[w] = t;
    if ((fPhase%fCheckperiod) == 0) {
        // time to check for a cycle
        for (int i=1; i<fBuffersize; i++) {
            int r = w-i; if (r < 0) { r += fBuffersize; }
            assert(r>=0);
            assert(r<fBuffersize);
            assert(r != w);
            if (fBuffer[r] == t) {
                cerr 	<< "ERROR : after "
                        << fPhase
                        << " evaluation steps, the compiler has detected an endless evaluation cycle of "
                        << i
                        << " steps"
                        << endl;
                exit(1);
            }
        }
    }
    return false;
}
