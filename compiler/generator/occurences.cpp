#include <assert.h>
#include <stdlib.h>
#include "recursivness.hh"
#include "occurences.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include <iostream>

using namespace std;

/**
 * Extended Variability with recursiveness indication
 */
static int xVariability (int v, int r)
{
	//cerr << "xVariability (" << v << ", " <<  r << ")" << endl;
	//assert (v < 3);				// kKonst=0, kBlock=1, kSamp=2
	//assert(r==0 | v==2);
	if (r>1) r=1;
	return min(3, v + r);
}

//-------------------------------------------------
//	Occurences methods
//-------------------------------------------------

Occurences::Occurences(int v, int r) : fXVariability(xVariability(v,r)) {
	for (int i=0; i<4; i++) fOccurences[i]=0;
	fMultiOcc = false;
	fMaxDelay = 0;
	fOutDelayOcc = false;
}

Occurences* Occurences::incOccurences(int v, int r, int d) {
	int ctxt = xVariability(v,r);
	//assert (ctxt >= fXVariability);
	fOccurences[ctxt] += 1;
	fMultiOcc = fMultiOcc | (ctxt > fXVariability) | (fOccurences[ctxt] > 1);
	if (d == 0) {
		//cerr << "Occurence outside a delay " << endl;
		fOutDelayOcc = true;
	}
	if (d > fMaxDelay) {
		//cerr << "Max delay : " << fMaxDelay << " <- " << d << endl;
		fMaxDelay = d;
	}
	return this;
}

bool Occurences::hasMultiOccurences()	const	{ return fMultiOcc; }

bool Occurences::hasOutDelayOccurences() const	{ return fOutDelayOcc; }

int Occurences::getMaxDelay() const
{
	return fMaxDelay;
}

//--------------------------------------------------
//	Mark and retrieve occurences of subtrees of root
//--------------------------------------------------

void OccMarkup::mark(Tree root)
{
	fRootTree = root;
	fPropKey = tree(unique("OCCURENCES"));

	if (isList(root)) {
		while (isList(root)) {
			//incOcc(kSamp, 1, hd(root));
			incOcc(nil, kSamp, 0, 0, hd(root));
			root = tl(root);
		}
		//cerr << "END OF LIST IS " << *root << endl;
	} else {
		//incOcc(kSamp, 1, root);
		incOcc(nil, kSamp, 0, 0, root);
	}
}

Occurences* OccMarkup::retrieve(Tree t)
{
	Occurences* p = getOcc(t);
	if (p == 0) {
		//cerr << "No Occurences info attached to : " << *t << endl;
		//exit(1);
	}
	return p;
}

//------------------------------------------------------------------------------
// Increment the occurences of t within context v,r,d and proceed recursively
//------------------------------------------------------------------------------

void OccMarkup::incOcc(Tree env, int v, int r, int d, Tree t)
{
	// Check if we have already visited this tree
	Occurences* occ = getOcc(t);

	if (occ==0) {
		// 1) We build initial occurence information
		Type	ty = getCertifiedSigType(t);
		int v0 = ty->variability();
		int r0 = getRecursivness(t);

		occ = new Occurences(v0,r0);
		setOcc(t, occ);

		// We mark the subtrees of t
        Tree c, x, y, z;
		if (isSigFixDelay(t,x,y)) {
			Type g2 = getCertifiedSigType(y);
			int d2 = checkDelayInterval(g2);
			assert(d2>=0);
			incOcc(env, v0, r0, d2, x);
			incOcc(env, v0, r0, 0, y);
        } else if (isSigPrefix(t,y,x)) {
            incOcc(env, v0, r0, 1, x);
            incOcc(env, v0, r0, 0, y);
        } else if (isSigSelect3(t,c,y,x,z)) {
            // make a special case for select3 implemented with real if
            // because the c expression will be used twice in the C++
            // translation
			incOcc(env, v0, r0, 0, c);
			incOcc(env, v0, r0, 0, c);
            incOcc(env, v0, r0, 0, x);
            incOcc(env, v0, r0, 0, y);
            incOcc(env, v0, r0, 0, z);
        } else {
			vector<Tree> br;
			int n = getSubSignals(t, br);
			if (n>0 && ! isSigGen(t)) {
				for (int i=0; i<n; i++) incOcc(env, v0, r0, 0, br[i]);
			}
		}
	}

	occ->incOccurences(v,r,d);

}



Occurences* OccMarkup::getOcc(Tree t)
{
	Tree p = t->getProperty(fPropKey);
	if (p) {
		return (Occurences*) tree2ptr(p);
	} else {
		return 0;
	}
}


void OccMarkup::setOcc(Tree t, Occurences* occ)
{
	t->setProperty(fPropKey, tree(occ));
}



/**
 * return the position of a signal in the current recursive environment
 * @param env the current recursive environment of the signal
 * @param t signal we want to know the position
 * @return the position in the recursive environment
 */
static int position (Tree env, Tree t, int p)
{
	if (isNil(env)) return 0;	// was not in the environment
	if (hd(env) == t) return p;
	else return position (tl(env), t, p+1);
}
