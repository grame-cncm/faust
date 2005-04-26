/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/
 
 
 
#include "compile_vect.hh"


#include "compile.hh"
#include "compile_scal.hh"
#include "sigtype.hh"

#include <stdio.h>
#include <iostream>
#include <sstream>

#include "sigprint.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "privatise.hh"
#include "prim2.hh"


static Klass* signal2klass (const string& name, Tree sig)
{
	Type t = getSigType(sig, NULLENV);
	if (t->nature() == kInt) {

		ScalarCompiler C( new SigIntGenKlass(name) );
		C.compileSingleSignal(sig);
		return C.getClass();

	} else {

		ScalarCompiler C( new SigFloatGenKlass(name) );
		C.compileSingleSignal(sig);
		return C.getClass();

	}		
}


/*****************************************************************************
		getFreshID
*****************************************************************************/

//map<string, int>	VectorCompiler::fIDCounters;

string VectorCompiler::getFreshID ( const char* prefix)
{
  char c[64];

  if (fIDCounters.find(prefix) == fIDCounters.end()) {
    fIDCounters[prefix]=0;
  }

  int n = fIDCounters[prefix];

  fIDCounters[prefix] = n+1;

  snprintf(c, 63, "%s%d", prefix, n);

  return string(c);
}



/*****************************************************************************
						makeCompileKey
*****************************************************************************/

Tree VectorCompiler::makeCompileKey(Tree t, int unroll)
{
  char 	name[256];
  snprintf(name, 256, "%d COMPILED IN %p : ", unroll, (CTree*)t);
  return tree(unique(name));
}


/*****************************************************************************
						    prepare
*****************************************************************************/

Tree VectorCompiler::prepare(Tree L0)
{
  Tree L3 = Compiler::prepare(L0);

  sharingAnalysis(L3);			// annotate L3 with sharing count

  fCompileScalKey[0] = makeCompileKey(L3,0);
  fCompileScalKey[1] = makeCompileKey(L3,1);
  fCompileScalKey[2] = makeCompileKey(L3,2);
  fCompileScalKey[3] = makeCompileKey(L3,3);
  fCompileScalarVecKey[0] = makeCompileKey(L3,0);
  fCompileScalarVecKey[1] = makeCompileKey(L3,1);
  fCompileScalarVecKey[2] = makeCompileKey(L3,2);
  fCompileScalarVecKey[3] = makeCompileKey(L3,3);
  fCompileVecKey = makeCompileKey(L3,0);

  fIDKey = tree(unique("IDKEY"));

  return L3;
}


/*****************************************************************************
						    compileMultiSignal
*****************************************************************************/

void VectorCompiler::compileMultiSignal (Tree L)
{	
  L = prepare(L);		// optimize and annotate expression
  for (int i = 0; i < fClass->inputs(); i++) {
    fClass->addSlowCode(subst("float* input$0 __attribute__ ((aligned(16))); input$0 = input[$0];", T(i)));    
  }
  for (int i = 0; i < fClass->outputs(); i++) {
    fClass->addSlowCode(subst("float* output$0 __attribute__ ((aligned(16))); output$0 = output[$0]; vec_float vec_output$0;", T(i)));    
  }
  for (int i = 0; isList(L); L = tl(L), i++) {
    Tree sig = hd(L);

    Type t = getSigType(sig, NULLENV);

    if(t->boolean()==kBool) fClass->addExecCode(subst("vec_output$0 = bool2float($1);", T(i), CS(NULLENV,sig,kVect)));
    else if(t->nature()==kInt) fClass->addExecCode(subst("vec_output$0 = int2float($1);", T(i), CS(NULLENV,sig,kVect)));
    else fClass->addExecCode(subst("vec_output$0 = $1;", T(i), CS(NULLENV,sig,kVect)));
 
    fClass->addExecCode(subst("store_a_vec(&output$0[i], vec_output$0);",T(i)));
  }
  generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
}


/*****************************************************************************
						    compileSingleSignal
*****************************************************************************/

void VectorCompiler::compileSingleSignal (Tree sig)
{	
  sig = prepare(sig);		// optimize and annotate expression

  fClass->addSlowCode("float* input _attribute__ ((aligned(16))); input = input[0];");
  
  fClass->addSlowCode("float* output __attribute__ ((aligned(16))); output = output[0]; vec_float vec_output;");
  

  Type t = getSigType(sig, NULLENV);

  if(t->boolean()==kBool) fClass->addExecCode(subst("vec_output = bool2float($0);", CS(NULLENV,sig,kVect)));
  else if(t->nature()==kInt) fClass->addExecCode(subst("vec_output = int2float($0);", CS(NULLENV,sig,kVect)));
  else fClass->addExecCode(subst("vec_output = $0;", CS(NULLENV,sig,kVect)));

  fClass->addExecCode("store_a_vec(&output[i], vec_output);");


  generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
}

/*****************************************************************************
							 CS : compile a signal
*****************************************************************************/
/**
 * Compile a signal
 * @param env the type environment (enclosing recursions).
 * @param sig the signal expression to compile.
 * @param context the type of the enclosing expression ( vector, scalar produced as vector or true scalar )
 * @return the C code translation of sig as a string
 */

string	VectorCompiler::CS (Tree env, Tree sig, int context)
{
  // Changement ÂŽà faire:
  // quel que soit le contexte dans lequel on cherche ÂŽà compiler, il faut vÂŽérifier si le signal a dÂŽéjÂŽà ÂŽétÂŽé
  // compilÂŽé dans n'importe quel contexte, dans ce cas il doit avoir une variable de cache,
  // sinon on compile


  Tree prop;

  Type t = getSigType(sig,env);
  int type = t->vectorability();
  int varia = t->variability();


  // node already compiled for the current context
  if((context==kVect)&&(getProperty(sig,fCompileVecKey,prop))) return tree2str(prop); // vector code
  else if((context==kScal)&&(getProperty(sig,fCompileScalarVecKey[loop_unroll],prop))) return tree2str(prop); // scalar code emulated with vectors
  else if((context==kTrueScal)&&(getProperty(sig,fCompileScalKey[loop_unroll],prop))) return tree2str(prop); // true scalar code
  // node already compiled in an another context
  else if((varia==kSamp)&&(context==kScal)&&(getProperty(sig,fCompileVecKey,prop))) { // node already compiled as a vector and used as a scalar
   
    string temp;
    if(shcount(fSharingKeyScal,sig)>1) {

      temp = generateCacheCode(env,sig,subst("VEC2SCALVEC0($0)",tree2str(prop)),kScal);
      setProperty(sig,fCompileScalarVecKey[0],tree(temp));
      setProperty(sig,fCompileScalarVecKey[1],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC1($0)",tree2str(prop)),kScal)));
      setProperty(sig,fCompileScalarVecKey[2],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC2($0)",tree2str(prop)),kScal)));
      setProperty(sig,fCompileScalarVecKey[3],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC3($0)",tree2str(prop)),kScal)));

    } else {

      temp = subst("VEC2SCALVEC0($0)",tree2str(prop));
      setProperty(sig,fCompileScalarVecKey[0],tree(temp));
      setProperty(sig,fCompileScalarVecKey[1],tree(subst("VEC2SCALVEC1($0)",tree2str(prop))));
      setProperty(sig,fCompileScalarVecKey[2],tree(subst("VEC2SCALVEC2($0)",tree2str(prop))));
      setProperty(sig,fCompileScalarVecKey[3],tree(subst("VEC2SCALVEC3($0)",tree2str(prop))));

    }
   	      
    return temp;

  } else if((varia==kSamp)&&(context==kTrueScal)&&(getProperty(sig,fCompileVecKey,prop))) { // node already compiled as a vector and used as a true scalar

    string vname = getFreshID("vec_tempScal");
    if (t->nature() == kInt) fClass->addExecCode(subst("__vec_int $0; $0.v = $1;", vname, tree2str(prop)));
    else fClass->addExecCode(subst("__vec_float $0; $0.v = $1;", vname, tree2str(prop)));

    string temp;
    if(shcount(fSharingKeyTrueScal,sig)>1) {

      temp = generateCacheCode(env,sig,subst("$0.s[0]",vname),kTrueScal);
      setProperty(sig,fCompileScalKey[0],tree(temp));
      setProperty(sig,fCompileScalKey[1],tree(generateCacheCode(env,sig,subst("$0.s[1]",vname),kTrueScal)));
      setProperty(sig,fCompileScalKey[2],tree(generateCacheCode(env,sig,subst("$0.s[2]",vname),kTrueScal)));
      setProperty(sig,fCompileScalKey[3],tree(generateCacheCode(env,sig,subst("$0.s[3]",vname),kTrueScal)));

    } else {
   
      temp = subst("$0.s[0]",vname);
      setProperty(sig,fCompileScalKey[0],tree(temp));
      setProperty(sig,fCompileScalKey[1],tree(subst("$0.s[1]",vname)));
      setProperty(sig,fCompileScalKey[2],tree(subst("$0.s[2]",vname)));
      setProperty(sig,fCompileScalKey[3],tree(subst("$0.s[3]",vname)));

    }
		
    return temp; 


  // node not yet compiled
  } else {

    string code;    
    int i;
    Tree id,z,x,y,ff,largs,label,le;
    
    


    if(context==kVect) {


      if(varia==kSamp) {
	
	code = generateVec(env,sig); // whatever the type


	if(shcount(fSharingKeyVec,sig)>1) code = generateCacheCode(env,sig,code,kVect);
	else if((shcount(fSharingKeyScal,sig)>=1)&&(!getProperty(sig,fCompileScalarVecKey[loop_unroll],prop))) code = generateCacheCode(env,sig,code,kVect);
	//else if((shcount(fSharingKeyTrueScal,sig)>=1)&&(!getProperty(sig,fCompileScalKey[loop_unroll],prop))) code = generateCacheCode(env,sig,code,kVect);


      } else {
	
	code = generateCacheCode(env,sig,CS(env,sig,kTrueScal),kVect);
	setProperty(sig,fCompileVecKey,tree(code));
	setProperty(sig,fCompileScalarVecKey[0],tree(code));
	setProperty(sig,fCompileScalarVecKey[1],tree(code));
	setProperty(sig,fCompileScalarVecKey[2],tree(code));
	setProperty(sig,fCompileScalarVecKey[3],tree(code));
	
      }	

      setProperty(sig,fCompileVecKey,tree(code));




     
    } else if(context==kScal) {


      if(varia==kSamp) {

	if(type==kVect) {
 
	  if(isSigInput(sig,&i)&&(shcount(fSharingKeyVec,sig)==1)&&(shcount(fSharingKeyScal,sig)==1)) {

	    code = generateScalarVec(env,sig); 

	    if(shcount(fSharingKeyScal,sig)>1) code = generateCacheCode(env,sig,code,kScal);	
	    setProperty(sig,fCompileScalarVecKey[loop_unroll],tree(code));

	  } else if(isProj(sig,&i,x)&&isRec(x,label,le)) {

	    if(heuristiqueRec(env,sig,&code)) {
	      
	      string temp = generateCacheCode(env,sig,subst("VEC2SCALVEC0($0)",code),kScal);
	      setProperty(sig,fCompileScalarVecKey[0],tree(temp));
	      setProperty(sig,fCompileScalarVecKey[1],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC1($0)",code),kScal)));
	      setProperty(sig,fCompileScalarVecKey[2],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC2($0)",code),kScal)));
	      setProperty(sig,fCompileScalarVecKey[3],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC3($0)",code),kScal)));
	      setProperty(sig,fCompileVecKey,tree(subst("$0",code)));
	      
	      code = temp;

	    } else {

	      code = generateScalarVec(env,sig);
	      setProperty(sig,fCompileScalarVecKey[loop_unroll],tree(code));
	    }


	  } else {

	    //code = subst("VEC2SCALVEC$0($1)",T(loop_unroll),CS(env,sig,kVect));
	    //setProperty(sig,fCompileScalarVecKey[loop_unroll],tree(code));   

	    string tempVec = CS(env,sig,kVect);
	    string temp = generateCacheCode(env,sig,subst("VEC2SCALVEC0($0)",tempVec),kScal);
	    setProperty(sig,fCompileScalarVecKey[0],tree(temp));
	    setProperty(sig,fCompileScalarVecKey[1],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC1($0)",tempVec),kScal)));
	    setProperty(sig,fCompileScalarVecKey[2],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC2($0)",tempVec),kScal)));
	    setProperty(sig,fCompileScalarVecKey[3],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC3($0)",tempVec),kScal)));
	    
	    code = temp;
	  }

	// type = kScal
	} else {
	  code = generateScalarVec(env,sig);

	  if(shcount(fSharingKeyScal,sig)>1) code = generateCacheCode(env,sig,code,kScal);	
	  setProperty(sig,fCompileScalarVecKey[loop_unroll],tree(code));

	}


	//if(shcount(fSharingKeyScal,sig)>1) code = generateCacheCode(env,sig,code,kScal);
	//setProperty(sig,fCompileScalarVecKey[loop_unroll],tree(code));

      } else {

	code = generateCacheCode(env,sig,CS(env,sig,kTrueScal),kVect); // kVect parce que vecteur constant
	setProperty(sig,fCompileVecKey,tree(code));
	setProperty(sig,fCompileScalarVecKey[0],tree(code));
	setProperty(sig,fCompileScalarVecKey[1],tree(code));
	setProperty(sig,fCompileScalarVecKey[2],tree(code));
	setProperty(sig,fCompileScalarVecKey[3],tree(code));	
      }


      //setProperty(sig,fCompileScalarVecKey[loop_unroll],tree(code));





    } else if(context==kTrueScal) {


      if(varia==kSamp) {

	if(type==kVect) {

	  if(isSigInput(sig,&i)||isSigGen(sig,x)||isSigTable(sig,id,x,y)||isSigWRTbl(sig,id,x,y,z)||isSigRDTbl(sig,x,y)||isSigFFun(sig,ff,largs)) { // don't need VEC2SCAL
	    
	    code = generateScal(env,sig);
	  
	  } else if(isProj(sig,&i,x)&&isRec(x,label,le)) { 
		
		code = CS(env,sig,kVect);

		string vname = getFreshID("vec_tempScal");
		if (t->nature() == kInt) fClass->addExecCode(subst("__vec_int $0; $0.v = $1;", vname, code));
		else fClass->addExecCode(subst("__vec_float $0; $0.v = $1;", vname, code));

		setProperty(sig,fCompileScalKey[0],tree(subst("$0.s[0]",vname)));
		setProperty(sig,fCompileScalKey[1],tree(subst("$0.s[1]",vname)));
		setProperty(sig,fCompileScalKey[2],tree(subst("$0.s[2]",vname)));
		setProperty(sig,fCompileScalKey[3],tree(subst("$0.s[3]",vname)));

		code = subst("$0.s[0]",vname);

	  } else {

	    string temp = CS(env,sig,kVect);
  
	    string vname = getFreshID("vec_tempScal");
	    if (t->nature() == kInt) fClass->addExecCode(subst("__vec_int $0; $0.v = $1;", vname, temp));
	    else fClass->addExecCode(subst("__vec_float $0; $0.v = $1;", vname, temp));
	    
	    setProperty(sig,fCompileScalKey[0],tree(subst("$0.s[0]",vname)));
	    setProperty(sig,fCompileScalKey[1],tree(subst("$0.s[1]",vname)));
	    setProperty(sig,fCompileScalKey[2],tree(subst("$0.s[2]",vname)));
	    setProperty(sig,fCompileScalKey[3],tree(subst("$0.s[3]",vname)));

	    code = subst("$0.s[0]",vname);

	  }


	} else { // type = kScal
 
	  if(isSigInput(sig,&i)||isSigGen(sig,x)||isSigTable(sig,id,x,y)||isSigWRTbl(sig,id,x,y,z)||isSigRDTbl(sig,x,y)||isSigFFun(sig,ff,largs)) { // don't need VEC2SCAL
	    
	    code = generateScal(env,sig);
	  
	  } else {

	    code = subst("VEC2SCAL0($0)",CS(env,sig,kScal));

	  }
	}

	if(shcount(fSharingKeyTrueScal,sig)>1) code = generateCacheCode(env,sig,code,kTrueScal);


	if((!isSigGen(sig,x))&&(!isSigTable(sig,id,x,y))) setProperty(sig,fCompileScalKey[loop_unroll],tree(code));
	else {
	  setProperty(sig,fCompileScalKey[0],tree(code));
	  setProperty(sig,fCompileScalKey[1],tree(code));
	  setProperty(sig,fCompileScalKey[2],tree(code));
	  setProperty(sig,fCompileScalKey[3],tree(code));
	}


      } else {

	code = generateScal(env,sig);
	
	if(shcount(fSharingKeyTrueScal,sig)>1) code = generateCacheCode(env,sig,code,kTrueScal);

	setProperty(sig,fCompileScalKey[0],tree(code));
	setProperty(sig,fCompileScalKey[1],tree(code));
	setProperty(sig,fCompileScalKey[2],tree(code));
	setProperty(sig,fCompileScalKey[3],tree(code));
	
      }  
    }
    

    return code;
  }

}



/*****************************************************************************
					   SCALAR-VECTOR INTERFACE
*****************************************************************************/


string VectorCompiler::generateVec(Tree env,Tree sig)
{
	int i;
	float r;
	Tree c,x,y,ff,largs,label,le,type,name,file;

	if(isSigInt(sig,&i))                    		return generateCacheCode(env,sig,T(i),kVect);
	else if(isSigReal(sig,&r))              		return generateCacheCode(env,sig,T(r),kVect);
	else if(isSigInput(sig,&i)) 	          		return generateInput(env,sig,T(i),kVect);
	else if(isSigFConst(sig,type,name,file) )		{ addIncludeFile(tree2str(file));	return generateCacheCode(env,sig,tree2str(name),kVect); 	}
	else if(isSigBinOp(sig,&i,x,y))         		return generateBinOp(env,sig,i,x,y,kVect);
	else if(isSigDelay1(sig,x)) 		  			return generateDelay1(env,sig,x,kVect);
	else if(isSigSelect2(sig,c,x,y))        		return generateSelect2(env,sig,c,x,y,kVect);
	else if(isSigIntCast(sig,x)) 		  			return generateIntCast(env,sig,x,kVect);
	else if(isSigFloatCast(sig,x)) 	  				return generateFloatCast(env,sig,x,kVect);
	else if(isProj(sig,&i,x)&&isRec(x,label,le)) { // si proj dans generateVec, c'est forcement proj d'un rec ( et pas d'un ref )

    string code;
    if(heuristiqueRec(env,sig,&code)) {

      setProperty(sig,fCompileScalarVecKey[0],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC0($0)",code),kScal)));
      setProperty(sig,fCompileScalarVecKey[1],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC1($0)",code),kScal)));
      setProperty(sig,fCompileScalarVecKey[2],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC2($0)",code),kScal)));
      setProperty(sig,fCompileScalarVecKey[3],tree(generateCacheCode(env,sig,subst("VEC2SCALVEC3($0)",code),kScal)));

      return code;

    } else {

      string ID;

      loop_unroll = 0; ID = CS(env,x,kScal); rec_var_map[ID] = 0;
      string Scal0 = generateRecProj(env,sig,ID,i); setProperty(sig,fCompileScalarVecKey[0],tree(Scal0));   
      loop_unroll = 1; ID = CS(env,x,kScal); rec_var_map[ID] = 1;
      string Scal1 = generateRecProj(env,sig,ID,i); setProperty(sig,fCompileScalarVecKey[1],tree(Scal1));
      loop_unroll = 2; ID = CS(env,x,kScal); rec_var_map[ID] = 2;
      string Scal2 = generateRecProj(env,sig,ID,i); setProperty(sig,fCompileScalarVecKey[2],tree(Scal2));
      loop_unroll = 3; ID = CS(env,x,kScal); rec_var_map[ID] = 3;
      string Scal3 = generateRecProj(env,sig,ID,i); setProperty(sig,fCompileScalarVecKey[3],tree(Scal3));
      loop_unroll = 0;

      return subst("SCAL2VEC($0,$1,$2,$3)",Scal0,Scal1,Scal2,Scal3);      
    }


  } else if(isSigFFun(sig,ff,largs)) {


      loop_unroll = 0; string Scal0 = CS(env,sig,kTrueScal);
      loop_unroll = 1; string Scal1 = CS(env,sig,kTrueScal);
      loop_unroll = 2; string Scal2 = CS(env,sig,kTrueScal);
      loop_unroll = 3; string Scal3 = CS(env,sig,kTrueScal);
      loop_unroll = 0;

      return subst("SCAL2VEC($0,$1,$2,$3)",Scal0,Scal1,Scal2,Scal3);


  } else if(isSigRDTbl(sig,x,y)) {


      loop_unroll = 0; string Scal0 = generateCacheCode(env,sig,subst("load_scal(&$0)",CS(env,sig,kTrueScal)),kScal); setProperty(sig,fCompileScalarVecKey[0],tree(Scal0)); 
      loop_unroll = 1; string Scal1 = generateCacheCode(env,sig,subst("load_scal(&$0)",CS(env,sig,kTrueScal)),kScal); setProperty(sig,fCompileScalarVecKey[1],tree(Scal1)); 
      loop_unroll = 2; string Scal2 = generateCacheCode(env,sig,subst("load_scal(&$0)",CS(env,sig,kTrueScal)),kScal); setProperty(sig,fCompileScalarVecKey[2],tree(Scal2)); 
      loop_unroll = 3; string Scal3 = generateCacheCode(env,sig,subst("load_scal(&$0)",CS(env,sig,kTrueScal)),kScal); setProperty(sig,fCompileScalarVecKey[3],tree(Scal3)); 
      loop_unroll = 0;

      return subst("SCAL2VEC($0,$1,$2,$3)",Scal0,Scal1,Scal2,Scal3);


  }


  return "Error generateVec";
}


string VectorCompiler::generateScalarVec(Tree env,Tree sig)
{
  int i;
  Tree c,x,y,label,le,ff,largs;

  if(isSigInput(sig,&i)) 	          		return generateInput(env,sig,T(i),kScal);
  else if(isSigBinOp(sig,&i,x,y))         	return generateBinOp(env,sig,i,x,y,kScal);
  else if(isSigDelay1(sig,x)) 		  		return generateDelay1(env,sig,x,kScal);
  else if(isSigSelect2(sig,c,x,y))        	return generateSelect2(env,sig,c,x,y,kScal);
  else if(isSigIntCast(sig,x)) 		  		return generateIntCast(env,sig,x,kScal);
  else if(isSigFloatCast(sig,x)) 	  		return generateFloatCast(env,sig,x,kScal);
  else if(isRef(sig,label))               	return generateRecRef(env,sig,label);
  else if(isRec(sig,label,le))            	return generateRecGroup(env,sig,label,le);
  else if(isProj(sig,&i,x)&&isRef(x,label)) {   

    string ID = CS(env,x,kScal);
    if(loop_unroll==0) rec_var_map[ID]=3;
    else rec_var_map[ID]=loop_unroll-1;
    return generateRecProj(env,sig,ID,i);
   
 
  } else if(isProj(sig,&i,x)&&isRec(x,label,le)) {

    string ID = CS(env,x,kScal);
    rec_var_map[ID] = loop_unroll;
    return generateRecProj(env,sig,ID,i);

  
  } else if(isSigFFun(sig,ff,largs)) {

    string Scal = generateCacheCode(env,sig,CS(env,sig,kTrueScal),kTrueScal);
    return subst("load_scal(&$0)", Scal);

  } else if(isSigRDTbl(sig,x,y))            return subst("load_scal(&$0)",CS(env,sig,kTrueScal));


  return "Error generateScalarVec";
}


string VectorCompiler::generateScal(Tree env,Tree sig)
{
	int i;
	float r;
	Tree ff,largs,id,label,c,x,y,z,type,name,file;

	if(isSigInt(sig,&i))                      	return T(i); 
	else if(isSigReal(sig,&r))                	return T(r);
	else if(isSigFConst(sig,type,name,file) )	{ addIncludeFile(tree2str(file));	return tree2str(name); 	}
	else if(isSigVSlider(sig,label,c,x,y,z))  	return generateVSlider(env,sig,label,c,x,y,z);
	else if(isSigHSlider(sig,label,c,x,y,z))  	return generateHSlider(env,sig,label,c,x,y,z);
	else if(isSigButton(sig,label)) 	    	return generateButton(env,sig,label);
	else if(isSigCheckbox(sig,label)) 	    	return generateCheckbox(env,sig,label);
	else if(isSigNumEntry(sig,label,c,x,y,z)) 	return generateNumEntry(env,sig,label,c,x,y,z);
	else if(isSigInput(sig,&i)) 	            return generateInput(env,sig,T(i),kTrueScal);
	else if(isSigBinOp(sig,&i,x,y))           	return generateBinOp(env,sig,i,x,y,kTrueScal);
	else if(isSigDelay1(sig,x)) 		    	return generateDelay1(env,sig,x,kTrueScal);
	else if(isSigSelect2(sig,c,x,y))          	return generateSelect2(env,sig,c,x,y,kTrueScal);
	else if(isSigIntCast(sig,x)) 		    	return generateIntCast(env,sig,x,kTrueScal);
	else if(isSigFloatCast(sig,x)) 	    		return generateFloatCast(env,sig,x,kTrueScal);
	else if(isSigFFun(sig,ff,largs))	    	return generateFFun(env,sig,ff,largs);
	else if(isSigGen(sig,x)) 		    		return generateSigGen(env,sig,x);
	else if(isSigTable(sig,id,x,y)) 	    	return generateTable(env,sig,x,y);
	else if(isSigWRTbl(sig,id,x,y,z))         	return generateWRTbl(env,sig,x,y,z);
	else if(isSigRDTbl(sig,x,y)) 	            return generateRDTbl(env,sig,x,y);


	return "Error generateScal";
}


/*****************************************************************************
							   CACHE CODE
*****************************************************************************/

string VectorCompiler::generateCacheCode(Tree env, Tree sig, const string& exp, int context)
{
  string ctype,vname;
  int i; float r;
  Tree x,y,z,label,le,id;

  Type t = getSigType(sig,env);

  if((!isSigGen(sig,x))&&(!isSigTable(sig,id,x,y))&&(!isSigWRTbl(sig,id,x,y,z))&&(!isSigDelay1(sig,x))) {

  switch(t->variability())
    {

    case kKonst :

      vname = getFreshID("vec_data");

      // seul variables qu'on autorise dans de le DeclCode et InitCode sont variables mÂŽémoires
      // qui doivent persister d'un appel ÂŽà l'autre ( variables rÂŽécursives, mem, table lecture/ecriture,
      // variables de l'interface graphique ) et les tables constantes ( table en lecture seule,
      // trop longue ÂŽà initialiser )
      // dorÂŽénavant toutes les constantes numÂŽériques sont dÂŽéclarer dans SlowCode

      /*
      if((context==kVect)||(context==kScal)) {
    
	if(t->nature() == kInt) {
	  fClass->addDeclCode(subst("vec_int \t$0;", vname));
	  fClass->addInitCode(subst("$0 = set_vec($1);", vname, exp));
	} else {
	  fClass->addDeclCode(subst("vec_float \t$0;", vname));
	  fClass->addInitCode(subst("$0 = set_vec($1);", vname, exp));
	}

      } else {

	if((!isSigInt(sig,&i))&&(!isSigReal(sig,&r))) {

	  vname = getFreshID("temp");
	  if (t->nature() == kInt) {
	    fClass->addDeclCode(subst("int \t$0;", vname));
	    fClass->addInitCode(subst("$0 = $1;", vname, exp));
	  } else {
	    fClass->addExecCode(subst("float \t$0;", vname));
	    fClass->addInitCode(subst("$0 = $1;", vname, exp));
	  }

	} else vname = exp;

      }
      */

      if((context==kVect)||(context==kScal)) {
    
	if(t->nature() == kInt) fClass->addSlowCode(subst("const vec_int $0 = set_vec($1);", vname, exp));
	else fClass->addSlowCode(subst("const vec_float $0 = set_vec($1);", vname, exp));       

      } else {

	// impossible

	if((!isSigInt(sig,&i))&&(!isSigReal(sig,&r))) {

	  vname = getFreshID("temp");
	  if (t->nature() == kInt) {
	    fClass->addDeclCode(subst("int \t$0;", vname));
	    fClass->addInitCode(subst("$0 = $1;", vname, exp));
	  } else {
	    fClass->addExecCode(subst("float \t$0;", vname));
	    fClass->addInitCode(subst("$0 = $1;", vname, exp));
	  }

	} else vname = exp;

      }

      break;
	

    case kBlock :

      if((context==kVect)||(context==kScal)) {

	vname = getFreshID("vec_block");
	if (t->nature() == kInt) fClass->addSlowCode(subst("vec_int $0 = set_vec($1);", vname, exp));
	else fClass->addSlowCode(subst("vec_float $0 = set_vec($1);", vname, exp));

      } else {

	vname = getFreshID("block");
	if (t->nature() == kInt) fClass->addSlowCode(subst("int $0 = $1;", vname, exp));
	else fClass->addSlowCode(subst("float $0 = $1;", vname, exp));

      }
      
      break;




    case kSamp :
	
      if(context==kVect) {

	    vname = getFreshID("vec_temp");
	    if (t->nature() == kInt) fClass->addExecCode(subst("vec_int $0 = $1;", vname, exp));
	    else fClass->addExecCode(subst("vec_float $0 = $1;", vname, exp));	  	  	  

      } else if(context==kScal) {
	
	if( isProj(sig,&i,x) || isRec(sig,label,le) || isRef(sig,label) ) {

	  vname = exp;

	} else {

	  vname = getFreshID("vec_temp");

	  if (t->nature() == kInt) fClass->addExecCode(subst("vec_int $0 = $1;", vname, exp));
	  else fClass->addExecCode(subst("vec_float $0 = $1;", vname, exp));

	}

      } else {

	vname = getFreshID("temp");

	if (t->nature() == kInt) fClass->addExecCode(subst("int $0 = $1;", vname, exp));
	else fClass->addExecCode(subst("float $0 = $1;", vname, exp));
	

      }

      break;



    default:
      fprintf(stderr,"Error in generateCacheCode: variability of signal undefined: %s\n",exp.c_str());
      return exp;
    }


  } else vname = exp;

  return vname;
}


/*****************************************************************************
							   INPUTS - OUTPUTS
*****************************************************************************/

string  VectorCompiler::generateInput (Tree env, Tree sig, const string& idx, int context)
{
  string temp;

  if(context==kVect) {
    if((shcount(fSharingKeyVec,sig)>1)||(shcount(fSharingKeyScal,sig)>=1)||(shcount(fSharingKeyTrueScal,sig)>=1)) temp = subst("load_a_vec(&input$0[i])",idx);
    else temp = subst("*(vec_float*)&input$0[i]",idx);
  } else if(context==kScal) temp = subst("load_scal(&input$0[i+$1])",idx,T(loop_unroll));
  else temp = subst("input$0[i+$1]",idx,T(loop_unroll));

  return temp;
}



string VectorCompiler::generateOutput(Tree env, Tree sig, const string& idx, Tree x, int context)
{
  string dst,arg;

  if(context==kVect) {
    dst = subst("vec_output$0", idx);
    arg = generateVec(env,x);
  } else {
    dst = subst("output$0[i+$1]", idx, T(loop_unroll));
    arg = generateScalarVec(env,x);
  }

  if(context==kVect) fClass->addExecCode(subst("$0 = $1;", dst, arg));
  else fClass->addExecCode(subst("store_scal(&$0,$1);", dst, arg));
  return dst;
}









/*****************************************************************************
							   BINARY OPERATION
*****************************************************************************/


// EVENTUELLEMENT ENLEVER CE DYNAMIQUE CASTING ET LE REPORTER DANS LES INTRINSEQUES ( CHAQUE OPERATION POUVANT ACCEPTER TOUT LES TYPES 
// D'ARGUMENTS ET FAIRE CONVERSIONS DANS LES INTRINSEQUES SI BESOIN EST )

bool VectorCompiler::DynamicCasting(Tree env, int nature_sig, int nature_arg1, int nature_arg2, Tree arg1, Tree arg2, string* cast_arg1, string* cast_arg2)
{
  int i;

  if(nature_arg1==kBool) {

    if(nature_arg2==kBool) {

      // bool op bool : check type of the operation
      if(nature_sig==kBool) {

	// OK
	*cast_arg1 = CS(env,arg1,kVect);
	*cast_arg2 = CS(env,arg2,kVect);

      } else if(nature_sig==kInt) {

	// result of the operation is used as an integer: cast arg1 and arg2
	*cast_arg1 = subst("bool2int($0)",CS(env,arg1,kVect));
	*cast_arg2 = subst("bool2int($0)",CS(env,arg2,kVect));

      } else if(nature_sig==kReal) {

	// result of the operation is used as a float: cast arg1 and arg2
	*cast_arg1 = subst("bool2float($0)",CS(env,arg1,kVect));
	*cast_arg2 = subst("bool2float($0)",CS(env,arg2,kVect));

      } else return false;


    } else if(nature_arg2==kInt) {

      // bool op int : cast arg1
      *cast_arg1 = subst("bool2int($0)",CS(env,arg1,kVect));
      *cast_arg2 = CS(env,arg2,kVect);

    } else if(nature_arg2==kReal) {

      // bool op float : cast arg1
      *cast_arg1 = subst("bool2float($0)",CS(env,arg1,kVect));
      *cast_arg2 = CS(env,arg2,kVect);

    } else return false;



  } else if(nature_arg1==kInt) {

    if(nature_arg2==kBool) {

      // int op bool : cast arg2
      *cast_arg1 = CS(env,arg1,kVect);
      *cast_arg2 = subst("bool2int($0)",CS(env,arg2,kVect));

    } else if(nature_arg2==kInt) {

      // int op int : OK
      *cast_arg1 = CS(env,arg1,kVect);
      *cast_arg2 = CS(env,arg2,kVect);

    } else if(nature_arg2==kReal) {

      // int op float : cast arg1
      if(isSigInt(arg1,&i)) { // arg1 is constant and should not be casted dynamically
	  string vname = getFreshID("vec_data");
	  fClass->addDeclCode(subst("vec_float \t$0;", vname));
	  fClass->addInitCode(subst("$0 = set_vec($1);", vname, T(float(i))));
	  *cast_arg1 = vname;
      } else *cast_arg1 = subst("int2float($0)",CS(env,arg1,kVect));
      *cast_arg2 = CS(env,arg2,kVect);

    } else return false;



  } else if(nature_arg1==kReal) {

    if(nature_arg2==kBool) {

      // float op bool : cast arg2
      *cast_arg1 = CS(env,arg1,kVect);
      *cast_arg2 = subst("bool2float($0)",CS(env,arg2,kVect));

    } else if(nature_arg2==kInt) {

      // float op int : cast arg2
      *cast_arg1 = CS(env,arg1,kVect);
      if(isSigInt(arg2,&i)) { // arg2 is constant and should not be casted dynamically
	string vname = getFreshID("vec_data");
	fClass->addDeclCode(subst("vec_float \t$0;", vname));
	fClass->addInitCode(subst("$0 = set_vec($1);", vname, T(float(i))));
	*cast_arg2 = vname;
      } else *cast_arg2 = subst("int2float($0)",CS(env,arg2,kVect));

    } else if(nature_arg2==kReal) {

      // float op float : OK
      *cast_arg1 = CS(env,arg1,kVect);
      *cast_arg2 = CS(env,arg2,kVect);

    } else return false;

  } else return false;

  return true;
}

// check for trinary operations of type:  a*b + c , a*(1/b) + c
// if the multiplication ( in such trinary operations ) is shared, two classic binary operations are produced
bool VectorCompiler::TrinaryOperationAccVec(Tree env,Tree arg1,Tree arg2,string* result)
{
  int i; float r;
  Tree w,x,y,z;
  string tri_op,tri_arg1,tri_arg2,tri_arg3;

  Type targ1 = getSigType(arg1,env);
  Type targ2 = getSigType(arg2,env);

  if(isSigBinOp(arg1, &i, x, y)&&(i==2)&&(shcount(fSharingKeyVec,arg1)==1)&&(shcount(fSharingKeyScal,arg1)==0)&&(shcount(fSharingKeyTrueScal,arg1)==0)&&(targ1->variability()==kSamp)) { // x*y + arg2 and multiplication not shared and multiplication's variability==kSamp

    //Type tx = getSigType(x,env);
    //Type ty = getSigType(y,env);
    

    if(isSigBinOp(x,&i,w,z)&&(i==3)&&((isSigReal(w,&r)&&(r==1.0))||(isSigInt(w,&i)&&(i==1)))) { //  (1/z)*y + arg2

      //Type tz = getSigType(z,env);

      tri_op = string("divadd_vec");

      tri_arg1 = CS(env,y,kVect);
      tri_arg2 = CS(env,z,kVect);
      tri_arg3 = CS(env,arg2,kVect);

      // type opÂŽération
      //if(sig->nature==kReal) {      
	
	// tri_arg1
	//if(ty->boolean()==kBool) tri_arg1 = subst("bool2float($0)",CS(env,y,kVect));
	//else if(ty->nature()==kInt) tri_arg1 = subst("int2float($0)",CS(env,y,kVect));
	//else tri_arg1 = CS(env,y,kVect);

	// tri_arg2
	//if(tz->boolean()==kBool) tri_arg2 = subst("bool2float($0)",CS(env,z,kVect));
	//else if(tz->nature()==kInt) tri_arg2 = subst("int2float($0)",CS(env,z,kVect));
	//else tri_arg2 = CS(env,z,kVect);

	// tri_arg3
	//if(targ2->boolean()==kBool) tri_arg3 = subst("bool2float($0)",CS(env,arg2,kVect));
	//else if(targ2->nature()==kInt) tri_arg3 = subst("int2float($0)",CS(env,arg2,kVect));
	//else tri_arg3 = CS(env,arg2,kVect);

	//} else {
	
	// tri_arg1
	//if(ty->boolean()==kBool) tri_arg1 = subst("bool2int($0)",CS(env,y,kVect));
	//else if(ty->nature()==kReal) tri_arg1 = subst("float2int($0)",CS(env,y,kVect));
	//else tri_arg1 = CS(env,y,kVect);

	// tri_arg2
	//if(tz->boolean()==kBool) tri_arg2 = subst("bool2int($0)",CS(env,z,kVect));
	//else if(tz->nature()==kReal) tri_arg2 = subst("float2int($0)",CS(env,z,kVect));
	//else tri_arg2 = CS(env,z,kVect);

	// tri_arg3
	//if(targ2->boolean()==kBool) tri_arg3 = subst("bool2int($0)",CS(env,arg2,kVect));
	//else if(targ2->nature()==kReal) tri_arg3 = subst("float2int($0)",CS(env,arg2,kVect));
	//else tri_arg3 = CS(env,arg2,kVect);

      //}



    } else if(isSigBinOp(y,&i,w,z)&&(i==3)&&((isSigReal(w,&r)&&(r==1.0))||(isSigInt(w,&i)&&(i==1)))) { // x*(1/z) + arg2

      tri_op = string("divadd_vec");

      tri_arg1 = CS(env,x,kVect);
      tri_arg2 = CS(env,z,kVect);
      tri_arg3 = CS(env,arg2,kVect);


    } else { // x*y +arg2

      tri_op = string("madd_vec");

      tri_arg1 = CS(env,x,kVect);
      tri_arg2 = CS(env,y,kVect);
      tri_arg3 = CS(env,arg2,kVect);

    }

  } else if(isSigBinOp(arg2, &i, x, y)&&(i==2)&&(shcount(fSharingKeyVec,arg2)==1)&&(shcount(fSharingKeyScal,arg2)==0)&&(shcount(fSharingKeyTrueScal,arg2)==0)&&(targ2->variability()==kSamp)) { // arg1 + x*y and multiplication not shared and multiplication's variability==kSamp

    if(isSigBinOp(x,&i,w,z)&&(i==3)&&((isSigReal(w,&r)&&(r==1.0))||(isSigInt(w,&i)&&(i==1)))) { //  arg1 + (1/z)*y

      tri_op = string("divadd_vec");

      tri_arg1 = CS(env,y,kVect);
      tri_arg2 = CS(env,z,kVect);
      tri_arg3 = CS(env,arg1,kVect);
 
    } else if(isSigBinOp(y,&i,w,z)&&(i==3)&&((isSigReal(w,&r)&&(r==1.0))||(isSigInt(w,&i)&&(i==1)))) { // arg1 + x*(1/z)

      tri_op = string("divadd_vec");
      
      tri_arg1 = CS(env,x,kVect);
      tri_arg2 = CS(env,z,kVect);
      tri_arg3 = CS(env,arg1,kVect);

    } else { // arg1 + x*y

      tri_op = string("madd_vec");

      tri_arg1 = CS(env,x,kVect);
      tri_arg2 = CS(env,y,kVect);
      tri_arg3 = CS(env,arg1,kVect);
    }

  } else return false;


  *result = subst("$0($1,$2,$3)",tri_op,tri_arg1,tri_arg2,tri_arg3);

  return true;
}

bool VectorCompiler::TrinaryOperationAccScal(Tree env,Tree arg1,Tree arg2,string* result)
{
  int i; float r;
  Tree w,x,y,z;
  string tri_op,tri_arg1,tri_arg2,tri_arg3;

  Type targ1 = getSigType(arg1,env);
  Type targ2 = getSigType(arg2,env);

 

  if(isSigBinOp(arg1, &i, x, y)&&(i==2)&&(shcount(fSharingKeyVec,arg1)==0)&&(shcount(fSharingKeyScal,arg1)==1)&&(shcount(fSharingKeyTrueScal,arg1)==1)&&(targ1->variability()==kSamp)) { // x*y + arg2 and multiplication not shared and multiplication's variability==kSamp

    //Type tx = getSigType(x,env);
    //Type ty = getSigType(y,env);


    if(targ1->vectorability()==kScal) {
    

      if(isSigBinOp(x,&i,w,z)&&(i==3)&&((isSigReal(w,&r)&&(r==1.0))||(isSigInt(w,&i)&&(i==1)))) { //  (1/z)*y + arg2
	
	//Type tz = getSigType(z,env);

	tri_op = string("divadd_scal");

	tri_arg1 = CS(env,y,kScal);
	tri_arg2 = CS(env,z,kScal);
	tri_arg3 = CS(env,arg2,kScal);


      } else if(isSigBinOp(y,&i,w,z)&&(i==3)&&((isSigReal(w,&r)&&(r==1.0))||(isSigInt(w,&i)&&(i==1)))) { // x*(1/z) + arg2

	tri_op = string("divadd_scal");

	tri_arg1 = CS(env,x,kScal);
	tri_arg2 = CS(env,z,kScal);
	tri_arg3 = CS(env,arg2,kScal);


      } else { // x*y +arg2

	tri_op = string("madd_scal");
	
	tri_arg1 = CS(env,x,kScal);
	tri_arg2 = CS(env,y,kScal);
	tri_arg3 = CS(env,arg2,kScal);

      }

    } else return false;


  } else if(isSigBinOp(arg2, &i, x, y)&&(i==2)&&(shcount(fSharingKeyVec,arg2)==0)&&(shcount(fSharingKeyScal,arg2)==1)&&(shcount(fSharingKeyTrueScal,arg2)==1)&&(targ2->variability()==kSamp)) { // arg1 + x*y and multiplication not shared and multiplication's variability==kSamp

    if(targ2->vectorability()==kScal) {

      if(isSigBinOp(x,&i,w,z)&&(i==3)&&((isSigReal(w,&r)&&(r==1.0))||(isSigInt(w,&i)&&(i==1)))) { //  arg1 + (1/z)*y

	tri_op = string("divadd_scal");

	tri_arg1 = CS(env,y,kScal);
	tri_arg2 = CS(env,z,kScal);
	tri_arg3 = CS(env,arg1,kScal);
 
      } else if(isSigBinOp(y,&i,w,z)&&(i==3)&&((isSigReal(w,&r)&&(r==1.0))||(isSigInt(w,&i)&&(i==1)))) { // arg1 + x*(1/z)

	tri_op = string("divadd_scal");
      
	tri_arg1 = CS(env,x,kScal);
	tri_arg2 = CS(env,z,kScal);
	tri_arg3 = CS(env,arg1,kScal);

      } else { // arg1 + x*y

	tri_op = string("madd_scal");

	tri_arg1 = CS(env,x,kScal);
	tri_arg2 = CS(env,y,kScal);
	tri_arg3 = CS(env,arg1,kScal);
      }

    } else return false;

  } else return false;


  *result = subst("$0($1,$2,$3)",tri_op,tri_arg1,tri_arg2,tri_arg3);

  return true;
}





string VectorCompiler::generateBinOp (Tree env,Tree sig, int opcode, Tree arg1, Tree arg2, int context)
{
  Type t = getSigType(sig,env);
  Type targ1 = getSigType(arg1,env);
  Type targ2 = getSigType(arg2,env);

  if(t->variability()<kSamp) { // operation produced in slow-code: scalar production

    return subst("($0 $1 $2)", CS(env,arg1,kTrueScal), gBinOpTable[opcode]->fName, CS(env,arg2,kTrueScal));

  } else if(context==kVect) { // vector operation

    string tri_op;
    // check for trinary operations of type:  a*b + c , a*(1/b) + c
    if((opcode==0)&&TrinaryOperationAccVec(env,arg1,arg2,&tri_op)) {

      return tri_op;

    // standard binary operation
    } else {

      //  string arg1_cast,arg2_cast;
      //  if(!DynamicCasting(env,t->nature(),targ1->nature(),targ2->nature(),arg1,arg2,&arg1_cast,&arg2_cast)) //fprintf(stderr,"Error: in dynamic casting\n");
      
      //  return subst("$0($1,$2)", gBinOpTable[opcode]->fNameVec, arg1_cast,arg2_cast);

      return subst("$0($1,$2)", gBinOpTable[opcode]->fNameVec, CS(env,arg1,kVect), CS(env,arg2,kVect));

    }

    //return subst("$0($1,$2)", gBinOpTable[opcode]->fNameVec, CS(env,arg1,kVect), CS(env,arg2,kVect));


  } else if(context==kScal) { // scalar operation

    string tri_op;
    // check for trinary operations of type:  a*b + c , a*(1/b) + c
    if((opcode==0)&&TrinaryOperationAccScal(env,arg1,arg2,&tri_op)) {

      return tri_op;

    // standard binary operation
    } else {

      return subst("$0($1,$2)", gBinOpTable[opcode]->fNameScal, CS(env,arg1,kScal), CS(env,arg2,kScal));

    }

  } else //fprintf(stderr,"BinOp True Scal\n");

  return "Error in generateBinOp";
}



/*****************************************************************************
							   1-SAMPLE DELAY
*****************************************************************************/

string VectorCompiler::generateDelay1 (Tree env, Tree sig, Tree arg, int context)
{ 
  string vname,tname,ctype,zero;

  Type t = getSigType(sig,env);
  Type targ = getSigType(arg,env);

  //if(targ->variability()<kSamp) return CS(env,arg,kTrueScal,kTrueScal);
  //else {
    
    if(t->nature()==kInt) {
      if(loop_unroll==0) {
		vname = getFreshID("vec_imem");
		tname = getFreshID("vec_ipre");
		ctype = "vec_int";
		zero = "set_vec(0)";    
      } else {
		Tree prop; getProperty(sig,fCompileScalarVecKey[0],prop);
		tname = tree2str(prop);
		vname = subst("vec_imem$0", tname.substr(8,tname.size()+1));
      }
    } else {
      if(loop_unroll==0) {
		vname = getFreshID("vec_fmem");
		tname = getFreshID("vec_fpre");
		ctype = "vec_float";
		zero = "set_vec(0.0)";
      } else {
		Tree prop; getProperty(sig,fCompileScalarVecKey[0],prop);
		tname = tree2str(prop);
		vname = subst("vec_fmem$0", tname.substr(8,tname.size()+1));
      }
    }
    //}



  if(context==kVect) { // vector context
      
    int sharingVec = shcount(fSharingKeyVec, sig);
    int sharingScal = shcount(fSharingKeyScal, sig) ;
    int sharingTrueScal = shcount(fSharingKeyTrueScal, sig);
    string arg_vec = CS(env,arg,kVect);
      
    if(loop_unroll==0) {
      
      fClass->addDeclCode(subst("$0 \t$1;", ctype, vname));
      fClass->addInitCode(subst("$0 = $1;", vname, zero));

      Tree x; int i;
      if((sharingVec>1)||(sharingScal>=1)||(sharingTrueScal>=1)||isSigDelay1(sig,x)||isProj(sig,&i,x)) { // cas particulier: la compilation d'arg donne une variable tampon qu'on peut utiliser directement	  
	fClass->addExecCode(subst("$0 $1 = mem1_vec($2,$3);", ctype, tname, arg_vec, vname));
	fClass->addExecCode(subst("$0 = $1;", vname, arg_vec));
      } else { // sinon on doit creer une variable temporaire
	string name_temp,type_temp;

	if (t->nature() == kInt) {
	  name_temp = getFreshID("vec_idata");
	  type_temp = "vec_int";	   
	} else {
	  name_temp = getFreshID("vec_fdata");
	  type_temp = "vec_float";
	}

	fClass->addExecCode(subst("$0 $1 = $2;",type_temp,name_temp,arg_vec));
	fClass->addExecCode(subst("$0 $1 = mem1_vec($2,$3);", ctype, tname, name_temp, vname));
	fClass->addExecCode(subst("$0 = $1;", vname, name_temp));
      }

    } else {
	
      fprintf(stderr,"ERROR GENERATE DELAY: VECTOR CONTEXT LOOP_UNROLL!=0\n");

    }

  } else { // scalar context
    
    string arg_scal = CS(env,arg,kScal);

    if(loop_unroll==0) {
      fClass->addDeclCode(subst("$0 \t$1;", ctype, vname));
      fClass->addInitCode(subst("$0 = $1;", vname, zero));
      
      //fClass->addExecScalCode(subst("$0 $1 = $2;", ctype, tname, vname),0);
      fClass->addExecCode(subst("$0 $1 = $2;", ctype, tname, vname));
	
    //} else fClass->addExecScalCode(subst("$0 = $1;", tname, vname),loop_unroll);
    } else fClass->addExecCode(subst("$0 = $1;", tname, vname));

    //fClass->addExecScalCode(subst("$0 = $1;", vname, arg_scal),loop_unroll);
    fClass->addExecCode(subst("$0 = $1;", vname, arg_scal));

  }

  return tname;
}


/*****************************************************************************
							   Selector
*****************************************************************************/

string VectorCompiler::generateSelect2(Tree env, Tree sig, Tree selector, Tree s1, Tree s2, int context)
{
  string ctype,temp0,temp1,selidx;

  Type t = getSigType(sig,env);
  Type ts1 = getSigType(s1,env);
  Type ts2 = getSigType(s2,env);
  Type tsel = getSigType(selector,env);

  // type of the selector
  if(t->nature() == kInt) ctype = "int";
  else ctype = "float";

  if(context==kVect) {
    if(loop_unroll==0) {

      temp0 = getFreshID("tmpSelvec0");
      temp1 = getFreshID("tmpSelvec1");
      selidx = getFreshID("idxSelvec");

      if(t->nature()==ts1->nature()) fClass->addExecCode(subst("vec_$0 $1 = $2;",ctype,temp0,CS(env,s1,kVect)));
      else fClass->addExecCode(subst("vec_$0 $1 = int2float($2);",ctype,temp0,CS(env,s1,kVect)));

      if(t->nature()==ts2->nature()) fClass->addExecCode(subst("vec_$0 $1 = $2;",ctype,temp1,CS(env,s2,kVect)));
      else fClass->addExecCode(subst("vec_$0 $1 = int2float($2);",ctype,temp1,CS(env,s2,kVect)));

      if((tsel->boolean()==kBool)&&(tsel->variability()==kSamp )) {

	if((t->nature()==kInt)&&(tsel->nature()==kInt)) fClass->addExecCode(subst("vec_int $0 = $1;",selidx,CS(env,selector,kVect)));
	else if((t->nature()==kReal)&&(tsel->nature()==kReal)) fClass->addExecCode(subst("vec_float $0 = $1;",selidx,CS(env,selector,kVect)));
	else if((t->nature()==kReal)&&(tsel->nature()==kInt)) fClass->addExecCode(subst("vec_float $0 = boolint2boolfloat($1);",selidx,CS(env,selector,kVect)));
	else fClass->addExecCode(subst("vec_int $0 = boolfloat2boolint($1);",selidx,CS(env,selector,kVect)));

      } else {

	if((t->nature()==kInt)&&(tsel->nature()==kInt)) fClass->addExecCode(subst("vec_int $0 = gt_vec($1, set_vec(0) );",selidx,CS(env,selector,kVect)));
	else if((t->nature()==kReal)&&(tsel->nature()==kReal)) fClass->addExecCode(subst("vec_float $0 = gt_vec($1, set_vec(0) );",selidx,CS(env,selector,kVect)));
	else if((t->nature()==kReal)&&(tsel->nature()==kInt)) fClass->addExecCode(subst("vec_float $0 = gt_vec(int2float($1), set_vec(0.0) );",selidx,CS(env,selector,kVect)));
	else fClass->addExecCode(subst("vec_int $0 = gt_vec(float2int($1), set_vec(0) );",selidx,CS(env,selector,kVect)));
      }
      
      return subst("select_vec($0,$1,$2)",selidx,temp0,temp1);
      

    } else return "Error Select2: vectorability kVect but loop_unrool!=0";

  } else if(context==kScal) {

    temp0 = subst("tmpSel0$0",T(loop_unroll)); temp0 = getFreshID(temp0.c_str());
    temp1 = subst("tmpSel1$0",T(loop_unroll)); temp1 = getFreshID(temp1.c_str());
    selidx = subst("idxSel$0",T(loop_unroll)); selidx = getFreshID(selidx.c_str());

    //if(t->nature()==ts1->nature()) fClass->addExecScalCode(subst("vec_$0 $1 = $2;",ctype,temp0,CS(env,s1,kScal)),loop_unroll);
    //else fClass->addExecScalCode(subst("vec_$0 $1 = int2float($2);",ctype,temp0,CS(env,s1,kScal)),loop_unroll);
    if(t->nature()==ts1->nature()) fClass->addExecCode(subst("vec_$0 $1 = $2;",ctype,temp0,CS(env,s1,kScal)));
    else fClass->addExecCode(subst("vec_$0 $1 = int2float($2);",ctype,temp0,CS(env,s1,kScal)));

    //if(t->nature()==ts2->nature()) fClass->addExecScalCode(subst("vec_$0 $1 = $2;",ctype,temp1,CS(env,s2,kScal)),loop_unroll);
    //else fClass->addExecScalCode(subst("vec_$0 $1 = int2float($2);",ctype,temp1,CS(env,s2,kScal)),loop_unroll);
    if(t->nature()==ts2->nature()) fClass->addExecCode(subst("vec_$0 $1 = $2;",ctype,temp1,CS(env,s2,kScal)));
    else fClass->addExecCode(subst("vec_$0 $1 = int2float($2);",ctype,temp1,CS(env,s2,kScal)));

    if((tsel->boolean()==kBool)&&(tsel->variability()==kSamp)) {
      
      if((t->nature()==kInt)&&(tsel->nature()==kInt)) fClass->addExecCode(subst("vec_int $0 = $1;",selidx,CS(env,selector,kScal)));
      else if((t->nature()==kReal)&&(tsel->nature()==kReal)) fClass->addExecCode(subst("vec_float $0 = $1;",selidx,CS(env,selector,kScal)));
      else if((t->nature()==kReal)&&(tsel->nature()==kInt)) fClass->addExecCode(subst("vec_float $0 = boolint2boolfloat($1);",selidx,CS(env,selector,kScal)));
      else fClass->addExecCode(subst("vec_int $0 = boolfloat2boolint($1);",selidx,CS(env,selector,kScal)));

    } else {

      if((t->nature()==kInt)&&(tsel->nature()==kInt)) fClass->addExecCode(subst("vec_int $0 = gt_scal($1, set_vec(0));",selidx,CS(env,selector,kScal)));
      else if((t->nature()==kReal)&&(tsel->nature()==kReal)) fClass->addExecCode(subst("vec_float $0 = gt_scal($1,set_vec(0.0));",selidx,CS(env,selector,kScal)));
      else if((t->nature()==kReal)&&(tsel->nature()==kInt)) fClass->addExecCode(subst("vec_float $0 = gt_scal(int2float($1),set_vec(0.0));",selidx,CS(env,selector,kScal)));
      else fClass->addExecCode(subst("vec_int $0 = gt_scal(float2int($1), set_vec(0));",selidx,CS(env,selector,kScal)));
    }

      
    return subst("select_scal($0,$1,$2)",selidx,temp0,temp1);
    //return subst("or_scal(and_not_scal($0,$1),and_scal($0,$2))",selidx,temp0,temp1);

  } else {

    return "Error: Select2 for true Scal not implemented yet";
  }

  return "Error generateSelect2";

  // RESTE LE CAS D'UN SELECTEUR A VARIABILITY < kSAMP -> SELECT SCALAIRE ( VRAI SCALAIRE )
}

/*****************************************************************************
							   Primitive Operations
*****************************************************************************/

string VectorCompiler::generateFFun  (Tree env, Tree sig, Tree ff, Tree largs)
{
  addIncludeFile(ffincfile(ff));
  addLibrary(fflibfile(ff));

  switch (ffarity(ff))
    {
    case 0 : return subst("$0()", ffname(ff));
    case 1 : return subst("$0($1)", ffname(ff), CS(env,nth(largs,0),kTrueScal));
    case 2 : return subst("$0($1, $2)", ffname(ff), CS(env,nth(largs,0),kTrueScal), CS(env,nth(largs,1),kTrueScal));
    case 3 : return subst("$0($1, $2, $3)", ffname(ff), CS(env,nth(largs,0),kTrueScal), CS(env,nth(largs,1),kTrueScal), CS(env,nth(largs,2),kTrueScal));
    default : //fprintf(stderr, "error inside generateFFun");
      exit(1);
    }
  return "Arity Error in FFun";
}



/*****************************************************************************
							   	    CASTING
*****************************************************************************/

string  VectorCompiler::generateIntCast   	(Tree env, Tree sig, Tree x, int context)
{ 
  Type t = getSigType(sig,env);

  if(t->variability()<kSamp) return subst("int($0)",CS(env,x,kTrueScal));
  else if(context==kVect) return subst("float2int($0)", CS(env,x,kVect));
  else return subst("float2int($0)", CS(env,x,kScal));
}

string  VectorCompiler::generateFloatCast 	(Tree env, Tree sig, Tree x, int context)
{
  Type t = getSigType(sig,env);

  if(t->variability()<kSamp) return subst("float($0)",CS(env,x,kTrueScal));
  else if(context==kVect) return subst("int2float($0)", CS(env,x,kVect));
  else return subst("int2float($0)", CS(env,x,kScal)); 
}


/*****************************************************************************
							user interface elements
*****************************************************************************/

string  VectorCompiler::generateButton 		(Tree env, Tree sig, Tree path)
{
  static string varname;

  if(!loop_unroll) {

    Tree prop;
    if(getProperty(sig,fCompileScalKey[0],prop)) varname = tree2str(prop);
    else {
      varname = getFreshID("fbutton");
      fClass->addDeclCode(subst("float \t$0;", varname));
      fClass->addInitCode(subst("$0 = 0.0;", varname));
      addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
    }

    return varname;
  }

  return "Error in generateButton";
}

string  VectorCompiler::generateCheckbox 	(Tree env, Tree sig, Tree path)
{
  static string varname;

  if(!loop_unroll) {

    Tree prop;
    if(getProperty(sig,fCompileScalKey[0],prop)) varname = tree2str(prop);
    else {
      varname = getFreshID("fcheckbox");
      fClass->addDeclCode(subst("float \t$0;", varname));
      fClass->addInitCode(subst("$0 = 0.0;", varname));
      addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
    }

    return varname;
  }

  return "Error in generateCheckbox";
}

string  VectorCompiler::generateVSlider 	(Tree env, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
  static string varname;

  if(loop_unroll==0) {

    Tree prop;
    if(getProperty(sig,fCompileScalKey[0],prop)) varname = tree2str(prop);
    else {
      varname = getFreshID("fslider");
      fClass->addDeclCode(subst("float \t$0;", varname));
      fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
      addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
    }

    return varname;
  }

  return "Error in generateVSlider";
}

string  VectorCompiler::generateHSlider	 	(Tree env, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
  static string varname;

  if(loop_unroll==0) {

    Tree prop;
    if(getProperty(sig,fCompileScalKey[0],prop)) varname = tree2str(prop);
    else {
      varname = getFreshID("fslider");
      fClass->addDeclCode(subst("float \t$0;", varname));
      fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
      addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
    }

    return varname;
  }

  return "Error in generateHSlider";
}


string  VectorCompiler::generateNumEntry 	(Tree env, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
  static string varname;

  if(loop_unroll==0) {

    Tree prop;
    if(getProperty(sig,fCompileScalKey[0],prop)) varname = tree2str(prop);
    else { 
      varname = getFreshID("fentry");
      fClass->addDeclCode(subst("float \t$0;", varname));
      fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
      addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
    }

    return varname;
  }

  return "Error in generateNumEntry";
}



/*****************************************************************************
							   	    TABLES
*****************************************************************************/


/*----------------------------------------------------------------------------
						sigGen : initial table content
----------------------------------------------------------------------------*/

string  VectorCompiler::generateSigGen(Tree env, Tree sig, Tree content)
{
  string klassname = getFreshID("SIG");
  string signame = getFreshID("sig");

  if(!loop_unroll) {
    fClass->addSubKlass(signal2klass(klassname, content));
    fClass->addInitCode(subst("$0 $1;", klassname, signame));
  }

  return signame;
}

/*----------------------------------------------------------------------------
						sigTable : table declaration
----------------------------------------------------------------------------*/

string  VectorCompiler::generateTable (Tree env, Tree sig, Tree tsize, Tree content)
{
  string        generator(CS(env,content,kTrueScal));
  string	ctype;
  int 		size;
  static string vname;

  if (!isSigInt(tsize, &size)) {
    //fprintf(stderr, "error generate table: size should be an integer\n");
    exit(1);
  }


  // definition du nom et du type de la table
  Type t = getSigType(sig,env);

  if (t->nature() == kInt) { vname = getFreshID("itbl"); ctype = "int"; }
  else { vname = getFreshID("ftbl"); ctype = "float"; }
  

  // declaration de la table
  fClass->addDeclCode(subst("$0 \t$1[$2] __attribute__ ((aligned(16)));", ctype, vname, T(size)));

  // initialisation du generateur de contenu
  fClass->addInitCode(subst("$0.init(samplingFreq);", generator));

  // remplissage de la table
  fClass->addInitCode(subst("$0.fill($1,$2);", generator, T(size), vname));

 

  // on retourne le nom de la table
  return vname;
}

/*----------------------------------------------------------------------------
						sigWRTable : table assignement
----------------------------------------------------------------------------*/

string  VectorCompiler::generateWRTbl (Tree env, Tree sig, Tree tbl, Tree idx, Tree data )
{
  string tblName = CS(env,tbl,kTrueScal);
  //fClass->addExecScalCode(subst("store_scal(&$0[$1],$2);", tblName, CS(env,idx,kTrueScal), CS(env,data,kScal)),loop_unroll);
  fClass->addExecCode(subst("store_scal(&$0[$1],$2);", tblName, CS(env,idx,kTrueScal), CS(env,data,kScal)));
  return tblName;
}

/*----------------------------------------------------------------------------
						sigRDTable : table access
----------------------------------------------------------------------------*/

string  VectorCompiler::generateRDTbl (Tree env, Tree sig, Tree tbl, Tree idx )
{
  return subst("$1[$0]", CS(env,idx,kTrueScal), CS(env,tbl,kTrueScal));
}



//string  VectorCompiler::generateRDOnlyTbl(Tree sig, Tree tbl, Tree idx)
//{
// return subst("$0[$1]", CS(tbl,kTrueScal,kTrueScal), CS(idx,kTrueScal,kTrueScal));
//}


/*****************************************************************************
							   RECURSIONS
*****************************************************************************/

// dÂŽÃ©tecte les rÂŽÃ©cursions typiques du type: R = ( m + R ) & n; 
// et les remplace par un code vectorisÂŽÃ©
bool VectorCompiler::heuristiqueRec(Tree env, Tree sig, string* result)
{
  int i,j,n,m;
  Tree prop,ProjRec,ProjRef,label,le,LeftAnd,RightAnd,LeftPlus,RightPlus; //v,w,x,y,z,label,le;

  //fprintf(stderr,"\n\nHEURISTIQUE\n\n");

  //int sh = shcount(fSharingKey,sig);
  ////fprintf(stderr,"HEURISTIQUE: SHARING: %d\n", sh);

  if(getProperty(sig,fCompileVecKey,prop)) { *result = tree2str(prop); return true; }
  else if ( !isProj(sig, &i, ProjRec) ) { /*fprintf(stderr,"HEURISTIQUE FALSE: pas proj\n");*/ return false; }                    // proj
  else if ( !isRec(ProjRec, label, le) ) { /*fprintf(stderr,"HEURISTIQUE FALSE: pas rec\n");*/ return false; }              // rec
  else if ( len(le)!=1 ) { /*fprintf(stderr,"HEURISTIQUE FALSE: pas len(le)==1\n");*/ return false; }
  else if ( !(isSigBinOp(nth(le,0), &i, LeftAnd, RightAnd)&&(shcount(fSharingKeyScal, nth(le,0))==1)&&(shcount(fSharingKeyVec, nth(le,0))==0)&&(shcount(fSharingKeyTrueScal, nth(le,0))==1) ) ) { /*fprintf(stderr,"HEURISTIQUE FALSE: pas sigbinop, pas sharing key =1 \n");*/ return false; }   //  &
  else if ( i!=13  ) { /*fprintf(stderr,"HEURISTIQUE FALSE: pas &\n");*/ return false; } // &
  else if ( isSigInt(LeftAnd,&n) ) {                                // n
      
    if( isSigBinOp(RightAnd,&i,LeftPlus,RightPlus) && (i==0) && (shcount(fSharingKeyVec,RightAnd)==0) &&(shcount(fSharingKeyScal,RightAnd)==1)&&(shcount(fSharingKeyTrueScal,RightAnd)==1) ) {           // +

      if ( isSigInt(LeftPlus,&m) ) {                                 // m

	if( isProj(RightPlus,&j,ProjRef) && isRef(ProjRef,label) && (j==0) ) {                                // OK: R = n & ( m + R )

	  int sh = shcount(fSharingKeyVec,LeftPlus);
	  if(sh>1) setProperty(LeftPlus,fSharingKeyVec,tree(sh-1)); // on ne peut plus partager aussi facilement m parce qu'on produit 4*m

	} else { /*fprintf(stderr,"HEURISTIQUE FALSE: pas ref\n");*/ return false; }

      } else if ( isSigInt(RightPlus,&m) ) {                          // m

	if( isProj(LeftPlus,&j,ProjRef) && isRef(ProjRef,label) && (j==0) ) {                                // OK: R = n & ( R + m )

	  int sh = shcount(fSharingKeyVec,RightPlus);
	  if(sh>1) setProperty(RightPlus,fSharingKeyVec,tree(sh-1)); // on ne peut plus partager aussi facilement m parce qu'on produit 4*m

	} else { /*printf(stderr,"HEURISTIQUE FALSE: pas ref\n");*/ return false; }

      } else { /*fprintf(stderr,"HEURISTIQUE FALSE: pas int\n");*/ return false; }

    } else { /*fprintf(stderr,"HEURISTIQUE FALSE: pas sigbinop pas +- pas sharing==1\n");*/ return false; }

  } else if ( isSigInt(RightAnd,&n) ) {                              // n

    if( isSigBinOp(LeftAnd,&i,LeftPlus,RightPlus) && (i==0) && (shcount(fSharingKeyVec,LeftAnd)==0) &&(shcount(fSharingKeyScal,LeftAnd)==1)&&(shcount(fSharingKeyTrueScal,LeftAnd)==1)) {           // +

      if ( isSigInt(LeftPlus,&m) ) {                                 // m

	if( isProj(RightPlus,&j,ProjRef) && isRef(ProjRef,label) && (j==0) ) {                                // OK: R = n & ( m +- R )

  	  int sh = shcount(fSharingKeyVec,LeftPlus);
	  if(sh>1) setProperty(LeftPlus,fSharingKeyVec,tree(sh-1)); // on ne peut plus partager aussi facilement m parce qu'on produit 4*m

	} else { /*fprintf(stderr,"HEURISTIQUE FALSE: pas ref\n");*/ return false; }

      } else if ( isSigInt(RightPlus,&m) ) {                          // m

	if( isProj(LeftPlus,&j,ProjRef) && isRef(ProjRef,label) && (j==0) ) {                                // OK: R = n & ( R +- m )

	  int sh = shcount(fSharingKeyVec,RightPlus);
	  if(sh>1) setProperty(RightPlus,fSharingKeyVec,tree(sh-1)); // on ne peut plus partager aussi facilement m parce qu'on produit 4*m

	} else { /*fprintf(stderr,"HEURISTIQUE FALSE: pas ref\n");*/ return false; }

      } else { /*fprintf(stderr,"HEURISTIQUE FALSE: pas int\n");*/ return false; }

    } else { /*fprintf(stderr,"HEURISTIQUE FALSE: pas sigbinop pas +- pas sharing==1\n");*/ return false; }

  } else { /*fprintf(stderr,"HEURISTIQUE FALSE: pas int\n");*/ return false; }


  //fprintf(stderr,"\n\nHEURISTIQUE TRUE\n\n");


  string ID = getFreshID("vec_R");
  fClass->addDeclCode(subst("vec_int \t$0;",ID));
  int init3 = 0;
  int init2 = n;
  int init1 = n-m;
  int init0 = n-2*m;
  fClass->addInitCode(subst("$0 = set_vec($1,$2,$3,$4);" , ID,T(init0),T(init1),T(init2),T(init3)));
  

  string Inc = getFreshID("vec_data");
  fClass->addDeclCode(subst("vec_int \t$0;",Inc));
  int IntInc = 4*m;
  fClass->addInitCode(subst("$0 = set_vec($1);", Inc, T(IntInc)));


  string And;
  if(n==IntInc) {
    And = Inc;
    if(isSigInt(LeftAnd,&n)) {
      setProperty(LeftAnd,fCompileVecKey,tree(And));
      setProperty(LeftAnd,fCompileScalarVecKey[0],tree(And));
      setProperty(LeftAnd,fCompileScalarVecKey[1],tree(And));
      setProperty(LeftAnd,fCompileScalarVecKey[2],tree(And));
      setProperty(LeftAnd,fCompileScalarVecKey[3],tree(And));
    } else {
      setProperty(RightAnd,fCompileVecKey,tree(And));
      setProperty(RightAnd,fCompileScalarVecKey[0],tree(And));
      setProperty(RightAnd,fCompileScalarVecKey[1],tree(And));
      setProperty(RightAnd,fCompileScalarVecKey[2],tree(And));
      setProperty(RightAnd,fCompileScalarVecKey[3],tree(And));
    }
  } else {
    if(isSigInt(LeftAnd,&n)&&getProperty(LeftAnd,fCompileVecKey,prop)) And = tree2str(prop);
    else if(getProperty(RightAnd,fCompileVecKey,prop)) And = tree2str(prop);
    else {
      And = getFreshID("vec_data");
      fClass->addDeclCode(subst("vec_int \t$0;",And));
      fClass->addInitCode(subst("$0 = set_vec($1);", And, T(n)));
      if(isSigInt(LeftAnd,&n)) {
	setProperty(LeftAnd,fCompileVecKey,tree(And));
	setProperty(LeftAnd,fCompileScalarVecKey[0],tree(And));
	setProperty(LeftAnd,fCompileScalarVecKey[1],tree(And));
	setProperty(LeftAnd,fCompileScalarVecKey[2],tree(And));
	setProperty(LeftAnd,fCompileScalarVecKey[3],tree(And));
      } else {
	setProperty(RightAnd,fCompileVecKey,tree(And));
	setProperty(RightAnd,fCompileScalarVecKey[0],tree(And));
	setProperty(RightAnd,fCompileScalarVecKey[1],tree(And));
	setProperty(RightAnd,fCompileScalarVecKey[2],tree(And));
	setProperty(RightAnd,fCompileScalarVecKey[3],tree(And));
      }
    }
  }

  fClass->addExecCode(subst("$0 = and_vec(add_vec($0,$1),$2);", ID, Inc, And));

  *result = subst("$0",ID);

  return true;
}


/*---------------------------------------------------------------------------
							fonctions auxilliaires
----------------------------------------------------------------------------*/

// Genere le nom d'une variable recursive permanente
static string makeRecVarPermName_vect(const string& groupID, int i) 
{
  return subst("$0_$1", groupID, T(i));
}

// Genere le nom d'une variable recursive temporaire
static string makeRecVarTempName_vect(const string& groupID, int i) 
{ 
  return subst("$0temp$1", groupID, T(i));
}

// Donne le nom du type C correspondant ÂŽà la nature d'un signal
static string cType (Type t) 
{ 
	return (t->nature() == kInt) ? "int" : "float";
}

// Donne le nom zero correspondant ÂŽà la nature d'un signal
static string cZero (Type t) 
{ 
	return (t->nature() == kInt) ? "0" : "0.0";
}

// Clef de proprietÂŽé associant un nom au label d'un groupe recursif
Tree RECNAMEPROP = tree(symbol("sigRecNameProp"));


/*--------------------------------------------------------------------------
							   Fonctions de gÂŽÃ©nÂŽÃ©ration
----------------------------------------------------------------------------*/


string  VectorCompiler::generateRecGroup (Tree env, Tree sig, Tree label, Tree le)
{
  Type 	t 	= getSigType(sig, env);
  // prepare the environments for the subtermes
  Tree	tEnv2	= addEnv(label,t,env);

  int n = len(le);

  // get the name of the recursive variable
  string ID; Tree tID;
  if(getProperty(sig,fIDKey,tID)) ID = tree2str(tID);
  else {
    ID = getFreshID("vec_R");
    setProperty(sig,fIDKey,tree(ID));
  }

  setProperty(label, RECNAMEPROP, tree(ID.c_str()));


  if(n==1) { // single recursive signal

    Tree e = nth(le, 0);
    Type te = getSigType(e, tEnv2);

    

    // declaration and initialisation of the recursive variable
    string vperm = subst("$0_$1", makeRecVarPermName_vect(ID, 0),T(loop_unroll));

   
    if(loop_unroll==3) {

      if(te->nature()==kInt) {
	fClass->addDeclCode(subst("vec_int \t$0;",vperm));
	fClass->addInitCode(subst("$0 = set_vec(0);", vperm)); 
      } else {
	fClass->addDeclCode(subst("vec_float \t$0;", vperm));
	fClass->addInitCode(subst("$0 = set_vec(0.0);", vperm)); 
      }

      //fClass->addExecScalCode(subst("\t$0 = $1;", vperm, CS(tEnv2,e,kScal)),loop_unroll);
      fClass->addExecCode(subst("\t$0 = $1;", vperm, CS(tEnv2,e,kScal)));

    } else {

      //if(te->nature()==kInt) fClass->addExecScalCode(subst("vec_int $0 = $1;", vperm, CS(tEnv2,e,kScal)),loop_unroll);
      //else fClass->addExecScalCode(subst("vec_float $0 = $1;", vperm, CS(tEnv2,e,kScal)),loop_unroll); 
      if(te->nature()==kInt) fClass->addExecCode(subst("vec_int $0 = $1;", vperm, CS(tEnv2,e,kScal)));
      else fClass->addExecCode(subst("vec_float $0 = $1;", vperm, CS(tEnv2,e,kScal))); 

    }
    
    
    /*
    string vperm = makeRecVarPermName_vect(ID, 0);

    if(loop_unroll==0) {  

      if(te->nature()==kInt) {
	fClass->addDeclCode(subst("vec_int \t$0;",vperm));
	fClass->addInitCode(subst("$0 = set_vec(0);", vperm)); 
      } else {
	fClass->addDeclCode(subst("vec_float \t$0;", vperm));
	fClass->addInitCode(subst("$0 = set_vec(0.0);", vperm)); 
      }
    }

    fClass->addExecCode(subst("\t$0 = REC$1($2);", vperm, T(loop_unroll), CS(tEnv2,e,kScal)));
    */

  } else { // group of mutually recursive signals

    for (int i=0; i<n; i++) {
      Tree e = nth(le, i);
      Type te = getSigType(e, tEnv2);

      
      
      string vperm = subst("$0_$1",makeRecVarPermName_vect(ID, i),T(loop_unroll));
      string vtemp = subst("$0_$1",makeRecVarTempName_vect(ID, i),T(loop_unroll));



      if(loop_unroll==3) {

	if(te->nature()==kInt) {
	  fClass->addDeclCode(subst("vec_int \t$0;", vperm));
	  fClass->addInitCode(subst("$0 = set_vec(0);", vperm)); 
	} else {
	  fClass->addDeclCode(subst("vec_float \t$0;", vperm));
	  fClass->addInitCode(subst("$0 = set_vec(0.0);", vperm));
	}
      }

      //fClass->addExecScalCode(subst("vec_$0 $1 = $2;", cType(te), vtemp, CS(tEnv2,e,kScal)),loop_unroll);
      fClass->addExecCode(subst("vec_$0 $1 = $2;", cType(te), vtemp, CS(tEnv2,e,kScal)));
      
      /*
      string vperm = makeRecVarPermName_vect(ID, i);
      string vtemp = makeRecVarTempName_vect(ID, i);

      if(loop_unroll==0) {

	if(te->nature()==kInt) {
	  fClass->addDeclCode(subst("vec_int \t$0;", vperm));
	  fClass->addInitCode(subst("$0 = set_vec(0);", vperm)); 
	} else {
	  fClass->addDeclCode(subst("vec_float \t$0;", vperm));
	  fClass->addInitCode(subst("$0 = set_vec(0.0);", vperm));
	}
      }

      fClass->addExecCode(subst("vec_$0 $1_$2 = REC$2($3);", cType(te), vtemp, T(loop_unroll), CS(tEnv2,e,kScal)));
      */
    }

    for (int i=0; i<n; i++) {

      Tree e = nth(le, 0);
      Type te = getSigType(e, tEnv2);
      
      //if(loop_unroll==3) fClass->addExecScalCode(subst("\t$0_$1 = $2_$1;", makeRecVarPermName_vect(ID, i), T(loop_unroll), makeRecVarTempName_vect(ID, i)),loop_unroll);
      if(loop_unroll==3) fClass->addExecCode(subst("\t$0_$1 = $2_$1;", makeRecVarPermName_vect(ID, i), T(loop_unroll), makeRecVarTempName_vect(ID, i)));      
      else {
	
	//if(te->nature()==kInt) fClass->addExecScalCode(subst("vec_int $0_$1 = $2_$1;", makeRecVarPermName_vect(ID, i), T(loop_unroll), makeRecVarTempName_vect(ID, i)),loop_unroll);
	//else fClass->addExecScalCode(subst("vec_float $0_$1 = $2_$1;", makeRecVarPermName_vect(ID, i), T(loop_unroll), makeRecVarTempName_vect(ID, i)),loop_unroll);
	if(te->nature()==kInt) fClass->addExecCode(subst("vec_int $0_$1 = $2_$1;", makeRecVarPermName_vect(ID, i), T(loop_unroll), makeRecVarTempName_vect(ID, i)));
	else fClass->addExecCode(subst("vec_float $0_$1 = $2_$1;", makeRecVarPermName_vect(ID, i), T(loop_unroll), makeRecVarTempName_vect(ID, i)));
      }
      

      //fClass->addExecCode(subst("\t$0 = $1_$2;", makeRecVarPermName_vect(ID, i), makeRecVarTempName_vect(ID, i), T(loop_unroll)));  
    }

  }


  return ID;
}


// Projection : selection du iÂŽÃ¨me signal d'un groupe recursif
string  VectorCompiler::generateRecProj (Tree env, Tree sig, const string& ID, int i)
{  
  return subst("$0_$1",makeRecVarPermName_vect(ID, i),T(rec_var_map[ID]));
  //return makeRecVarPermName_vect(ID, i);
}


// Variable : rÂŽÃ©fÂŽÃ©rence au iÂŽÃ¨me signal d'un groupe recursif englobant
string  VectorCompiler::generateRecRef (Tree env, Tree sig, Tree label)
{
  Tree t;

  if (getProperty(label, RECNAMEPROP, t)) {
    return name(t->node().getSym());
  } else {
    //fprintf(stderr, "error generate ref\n");
    exit(1);
  }
  return "error in Compiler::generateRecRef";
}

