#include <signals.hh>
#include <property.hh>

/**
 * Extract the sub signals of a signal expression, that is not
 * necesseraly all the subtrees.
 * @param sig the signals
 * @param vsigs a reference to the vector where the subsignals will be placed
 * @return the number of subsignals
 */

int	getSubSignals (Tree sig, vector<Tree>& vsigs, bool visitgen)
{
	vsigs.clear();

	int 	i;
	double	r;
    Tree 	c, sel, x, y, z, u, v, var, le, label, id, ff, largs, type, name, file;

		 if ( getUserData(sig) ) 					{ for (int i=0; i<sig->arity(); i++) { vsigs.push_back(sig->branch(i)); }
													  return sig->arity(); }
	else if ( isSigInt(sig, &i) ) 					{ return 0; }
	else if ( isSigReal(sig, &r) ) 					{ return 0; }
    else if ( isSigWaveform(sig))                   { vsigs = sig->branches(); return vsigs.size(); }

    //else if ( isSigWaveform(sig) )                  { return 0; }

	else if ( isSigInput(sig, &i) ) 				{ return 0; 			}
	else if ( isSigOutput(sig, &i, x) ) 			{ vsigs.push_back(x); return 1;	}

	else if ( isSigDelay1(sig, x) ) 				{ vsigs.push_back(x); return 1;	}

	else if ( isSigFixDelay(sig, x, y) ) 			{ vsigs.push_back(x); vsigs.push_back(y); return 2;	}
    else if ( isSigPrefix(sig, x, y) )              { vsigs.push_back(x); vsigs.push_back(y); return 2;	}
	else if ( isSigIota(sig, x) ) 					{ vsigs.push_back(x); return 1; }

	else if ( isSigBinOp(sig, &i, x, y) )			{ vsigs.push_back(x); vsigs.push_back(y); return 2; }
	else if ( isSigFFun(sig, ff, largs) )			{ int n = 0; while (!isNil(largs)) { vsigs.push_back(hd(largs)); largs = tl(largs); n++; } return n; }
    else if ( isSigFConst(sig, type, name, file) )  { return 0; }
    else if ( isSigFVar(sig, type, name, file) )    { return 0; }

	else if ( isSigTable(sig, id, x, y) ) 			{ vsigs.push_back(x); vsigs.push_back(y); return 2;	}
	else if ( isSigWRTbl(sig, id, x, y, z) )		{ vsigs.push_back(x); vsigs.push_back(y); vsigs.push_back(z); return 3;	}
	else if ( isSigRDTbl(sig, x, y) ) 				{ vsigs.push_back(x); vsigs.push_back(y); return 2;	}

    else if ( isSigDocConstantTbl(sig, x, y) )      { vsigs.push_back(x); vsigs.push_back(y); return 2;	}
    else if ( isSigDocWriteTbl(sig, x, y, u, v) )	{ vsigs.push_back(x); vsigs.push_back(y); vsigs.push_back(u); vsigs.push_back(v); return 4;	}
    else if ( isSigDocAccessTbl(sig, x, y) )        { vsigs.push_back(x); vsigs.push_back(y); return 2;	}


	else if ( isSigSelect2(sig, sel, x, y) ) 		{ vsigs.push_back(sel); vsigs.push_back(x); vsigs.push_back(y); return 3; }
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ vsigs.push_back(sel); vsigs.push_back(x); vsigs.push_back(y); vsigs.push_back(z); return 4; }

	else if ( isSigGen(sig, x) ) 					{ if (visitgen) { vsigs.push_back(x); return 1;} else { return 0; } }

    else if ( isProj(sig, &i, x) )                  { vsigs.push_back(x); return 1;	}
    else if ( isRec(sig, var, le) )                 { vsigs.push_back(le); return 1; }

	else if ( isSigIntCast(sig, x) ) 				{ vsigs.push_back(x); return 1; }
	else if ( isSigFloatCast(sig, x) ) 				{ vsigs.push_back(x); return 1; }

	else if ( isSigButton(sig, label) ) 			{ return 0; }
	else if ( isSigCheckbox(sig, label) ) 			{ return 0; }
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ return 0; }
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ return 0; }
    else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ return 0; }

	else if ( isSigVBargraph(sig, label,x,y,z) )	{ vsigs.push_back(z); return 1;	}
	else if ( isSigHBargraph(sig, label,x,y,z) )	{ vsigs.push_back(z); return 1;	}

	else if ( isSigSoundfileLength(sig,label) )		{ return 0;	}
	else if ( isSigSoundfileRate(sig,label) )		{ return 0;	}
	else if ( isSigSoundfileChannel(sig,label,x,y) ){ vsigs.push_back(x); vsigs.push_back(y); return 2;	}
	
	else if ( isSigAttach(sig, x, y) )				{ vsigs.push_back(x); vsigs.push_back(y); return 2;	}
    else if ( isList(sig) )                         { vsigs.push_back(hd(sig)); vsigs.push_back(tl(sig));  return 2; }
    else if ( isNil(sig) )                          { return 0; }

	else {
        cerr << "ERROR, getSubSignals unrecognized signal : " << *sig << endl;
		exit(1);
	}
	return 0;
}
