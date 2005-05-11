#ifndef _GROUPER_
#define _GROUPER_

#include <set>
#include <stack>

#include "sigvisitor.hh"


Tree structure (Tree sig);

struct simd 
{
	int 			fOpcode;
	vector<Tree>	fArgs;
	
	simd (int opcode) : fOpcode(opcode) {}
	
	int	append(Tree sig)	{
		fArgs.push_back(sig);
		return fArgs.size()-1;
	}
	ostream& 	print (ostream& fout) const; 
};	



struct TBlackList
{
	stack<int>		fStack;
	set<int>		fSet;
	
	void push(int g) 	{ fSet.insert(g); fStack.push(g); 			}	///< add element to the black list
	void pop()			{ fSet.erase(fStack.top()); fStack.pop(); 	}	///< remove the last added member
	bool member(int g)	{ return fSet.find(g) != fSet.end();		}	///< is member of the black list
};
	

struct grouper : fullvisitor
{
	Tree			fKey;
	vector<simd>	fGroups;
	TBlackList		fBlackList;
	set<int>		fVectorOpcodes;
	
	grouper() : fKey(tree(Node(this))) 
	{ 
		fVectorOpcodes.insert(kAdd);
		fVectorOpcodes.insert(kMul);
		fVectorOpcodes.insert(kSub);
		fVectorOpcodes.insert(kDiv);
	}
	
	bool hasGroupProperty(Tree sig) const;
	bool hasGroupProperty(Tree sig, int* gnum, int* pos) const;
	void setGroupProperty(Tree sig, int gnum, int pos) const;
	int	searchGroup(int opcode);
	
	ostream& 	print (ostream& fout) const; 
	
	// nouvelle facon de faire
	
	virtual void visitBinOp		(Tree sig, int opcode, Tree s1, Tree s2);


};
inline ostream& operator << (ostream& s, const simd& t) { return t.print(s); }
inline ostream& operator << (ostream& s, const grouper& t) { return t.print(s); }

#endif
