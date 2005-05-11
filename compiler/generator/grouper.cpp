#include <stdio.h>
#include <assert.h>
#include "signals.hh"
#include "sigprint.hh"
#include "sigorderrules.hh"
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include "grouper.hh"

using namespace std;


Tree STRUCTURE = tree(symbol("sigStructure"));

static Tree structure2(Tree sig);
static Tree structure1(Tree sig);
static Tree structure0 (Tree sig);

/** 
 * The structure of a tree is this tree without 
 * its subtrees at a certain level
 */

Tree structure (Tree sig)
{
	Tree p = sig->getProperty(STRUCTURE);
	
	if (p == 0) {
		p = structure2(sig);
		sig->setProperty(STRUCTURE, p);
	}
	
	return p;
}



/*----------------implementation------------------*/

static Tree structure2(Tree sig)
{
	Tree	x,y;
	
	if (isSigAdd(sig, x, y)) {
		return sigAdd(structure1(x), structure1(y));
		
	} else if (isSigSub(sig, x, y)) {
		return sigSub(structure1(x), structure1(y));
		
	} else if (isSigMul(sig, x, y)) {
		return sigMul(structure1(x), structure1(y));
		
	} else if (isSigDiv(sig, x, y)) {
		return sigDiv(structure1(x), structure1(y));
		
	} else {
		return structure0(sig);
	}
	
}

static Tree structure1(Tree sig)
{
	Tree	x,y;
	
	if (isSigAdd(sig, x, y)) {
		return sigAdd(structure0(x), structure0(y));
		
	} else if (isSigSub(sig, x, y)) {
		return sigSub(structure0(x), structure0(y));
		
	} else if (isSigMul(sig, x, y)) {
		return sigMul(structure0(x), structure0(y));
		
	} else if (isSigDiv(sig, x, y)) {
		return sigDiv(structure0(x), structure0(y));
		
	} else {
		return structure0(sig);
	}
	
}


static Tree structure0 (Tree sig)
{
	return tree(0);
}


/**
 * Vector instruction
 */

//inline ostream& operator << (ostream& s, const grouper& g) { return g.print(s); }
	
ostream& 	simd::print (ostream& fout) const
{
	fout << gBinOpTable[fOpcode]->fName << ':' << fArgs.size() << " (";
	for (unsigned int i = 0; i < fArgs.size(); i++) {
		printSignal(structure(fArgs[i]), stderr); 
		fout << " --  ";
	}
	fout << ")";
	return fout;
}

ostream& 	grouper::print (ostream& fout) const
{
	for (unsigned int g=0; g<fGroups.size(); g++) {
		const simd& s = fGroups[g];
		
		fout << g << ':' << gBinOpTable[s.fOpcode]->fName << ':' << s.fArgs.size() << " [[";
		
		for (unsigned int i = 0; i < s.fArgs.size(); i++) {
			Tree t = s.fArgs[i]; 
			int p, g1=-1, g2=-1;
				
			hasGroupProperty(t->branch(1), &g1, &p);
			hasGroupProperty(t->branch(2), &g2, &p);
			
			printSignal(structure(t), stderr);
			 
			fout << " <" << g1 << ':' << g2 << ">  ";
		}
		
		fout << "]]" << endl;
	}
	return fout;
}

bool grouper::hasGroupProperty(Tree sig) const
{
	return sig->getProperty(fKey) != 0;
}
	

bool grouper::hasGroupProperty(Tree sig, int* gnum, int* pos) const 
{
	Tree p = sig->getProperty(fKey);
	if (p) {
		*gnum = tree2int(hd(p));
		*pos = tree2int(tl(p));
		return true;
	} else {
		return false;
	}
}
	

void grouper::setGroupProperty(Tree sig, int gnum, int pos) const
{
	sig->setProperty(fKey, cons(tree(gnum),tree(pos)));
}
	

// nouvelle façon de faire

int	grouper::searchGroup(int opcode)
{
	int n = fGroups.size();
	
	// search and return a group of same opcode and not in the blacklist
	for (int g=0; g<n; g++) {
		if (fGroups[g].fOpcode == opcode && ! fBlackList.member(g)) {
			return g;
		}
	}
	
	// no suitable group found for this opcode, add a new one
	fGroups.push_back(simd(opcode));
	return n;
}


void grouper::visitBinOp (Tree sig, int opcode, Tree x, Tree y)
{
	if (!hasGroupProperty(sig)) {
		
		if (fVectorOpcodes.find(opcode) == fVectorOpcodes.end() || getSigOrder(sig) < 3) {
			// not a vectorisable instruction or not in the audio loop
			setGroupProperty(sig, -1, -1);
			visit(x);
			visit(y);
			
		} else  {
			// is a vectorizable instruction
			int group 	= searchGroup(opcode);
			int	pos 	= fGroups[group].append(sig);
			
			setGroupProperty(sig, group, pos);
			
			// increase blacklist
			fBlackList.push(group);
			visit(x);
			visit(y);
			fBlackList.pop();
			
		}
	}
}
