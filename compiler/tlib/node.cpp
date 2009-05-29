#include "node.hh"

ostream& Node::print (ostream& fout) const 					///< print a node on a stream
{
	switch (fType) {
		case kIntNode : 	return fout << fData.i;
		case kDoubleNode : 	return fout << fData.f;
		case kSymNode : 	return fout << *(fData.s);
		case kPointerNode : return fout << "ptr:" << fData.p;
		default : 			return fout << "badnode";
	}
			
//	return fout;
}

