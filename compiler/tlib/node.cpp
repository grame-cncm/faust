#include "node.hh"
#include "math.h"

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

//-----------------------------------------------------------------------------
// sameMagnitude(a,b) : true if the two nodes a and b represent numbers of same
//  absolute value. Int promoted to double if needed.
//

bool sameMagnitude(const Node& a, const Node& b)
{
    if (a.type() == kDoubleNode) {
        if (b.type() == kDoubleNode) {
            return fabs(a.getDouble()) == fabs(b.getDouble());
        } else if (b.type() == kIntNode) {
            return fabs(a.getDouble()) == fabs(double(b.getInt()));
        } else {
            return false;
        }
    } else if (a.type() == kIntNode) {
        if (b.type() == kDoubleNode) {
            return fabs(double(a.getInt())) == fabs(b.getDouble());
        } else if (b.type() == kIntNode) {
            return abs(a.getInt()) == abs(b.getInt());
        } else {
            return false;
        }
    } else {
        return false;
    }
}