#include "loopDetector.hh"
#include "ppbox.hh"
 
void loopDetector::listPossibleCycles (vector<int>& v)
{
	//cerr << "list possible cycles" << endl;
	Tree t = get(0);
	for (int i=1; i<=(fBuffersize/2); i++) {
		if (t == get(i)) { 
			//cout << "possible cycle at " << i << endl;
			v.push_back(i); 
		}
	}
}
 
bool loopDetector::detect (Tree t)
{
	//cerr << "detect " << t << endl;
	fPhase++;
	fBuffer[fPhase%fBuffersize] = t;
	if ((fPhase%fCheckperiod) == 0) {
		// list possible cycles
		vector<int> vc;
		listPossibleCycles(vc);
	
		// check each possible cycle
		//for (int i = vc.size(); i > 0;) {
		for (unsigned int i = 0; i < vc.size(); i++) {
			//i--;
			if (isCycle(vc[i])) {
                cerr 	<< "ERROR : after "
                        << fPhase
                        << " evaluation steps, the compiler has detected an endless evaluation cycle of "
						<< vc[i]  
                        << " steps"
                        << endl;
				exit(1);
				return true;
			}
		}		
	}
	return false;
}


bool loopDetector::isCycle(int period)
{
	//cerr << "check cycle " << period << endl;
	int n = fBuffersize/period; // number of periods
	for (int i=0; i<period; i++) {
		Tree x = get(i);
		for (int p=1; p<n; p++) {
			if (x != get(i+p*period)) return false;
		}
	}
	return true;
}
