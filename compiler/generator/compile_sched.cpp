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

#include "compile_sched.hh"
#include "floats.hh"
#include "ppsig.hh"

void SchedulerCompiler::compileMultiSignal(Tree L)
{
    //contextor recursivness(0);
    L = prepare(L);     // optimize, share and annotate expression
    
    for (int i = 0; i < fClass->inputs(); i++) {
        fClass->addZone3(subst("$1* input$0 = &input[$0][fIndex];", T(i), xfloat()));
    }
    for (int i = 0; i < fClass->outputs(); i++) {
       fClass->addZone3(subst("$1* output$0 = &output[$0][fIndex];", T(i), xfloat()));
    }
                
    fClass->addSharedDecl("fullcount"); 
    fClass->addSharedDecl("input"); 
    fClass->addSharedDecl("output"); 
    
    for (int i = 0; isList(L); L = tl(L), i++) {
        Tree sig = hd(L);
        fClass->openLoop("count");
        fClass->addExecCode(Statement("", subst("output$0[i] = $2$1;", T(i), CS(sig), xcast())));
        fClass->closeLoop(sig);
    }
    
    // Build tasks list 
    fClass->buildTasksList();
    
    generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot), true);
 	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
    if (fDescription) {
        fDescription->ui(prepareUserInterfaceTree(fUIRoot));
    }
}

/**
 * Generate the code for a (short) delay line
 * @param k the c++ class where the delay line will be placed.
 * @param l the loop where the code will be placed.
 * @param tname the name of the C++ type (float or int)
 * @param dlname the name of the delay line (vector) to be used.
 * @param delay the maximum delay
 * @param cexp the content of the signal as a C++ expression 
 */
void SchedulerCompiler::vectorLoop(const string& tname, const string& vecname, const string& cexp, const string& ccs)
{  
    // -- declare the vector
    fClass->addSharedDecl(vecname);
    
    // -- variables moved as class fields...
    fClass->addDeclCode(subst("$0 \t$1[$2];", tname, vecname, T(gGlobal->gVecSize)));
    
    // -- compute the new samples
    fClass->addExecCode(Statement(ccs, subst("$0[i] = $1;", vecname, cexp)));
}

/**
 * Generate the code for a (short) delay line
 * @param k the c++ class where the delay line will be placed.
 * @param l the loop where the code will be placed.
 * @param tname the name of the C++ type (float or int)
 * @param dlname the name of the delay line (vector) to be used.
 * @param delay the maximum delay
 * @param cexp the content of the signal as a C++ expression 
 */
void SchedulerCompiler::dlineLoop(const string& tname, const string& dlname, int delay, const string& cexp, const string& ccs)
{
    if (delay < gGlobal->gMaxCopyDelay) {
        
        // Implementation of a copy based delayline
        
	    // create names for temporary and permanent storage  
	    string  buf = subst("$0_tmp", dlname); 			
        string  pmem= subst("$0_perm", dlname);
        
        // constraints delay size to be multiple of 4
        delay = (delay+3)&-4;
        
        // allocate permanent storage for delayed samples
        string  dsize   = T(delay);
        fClass->addDeclCode(subst("$0 \t$1[$2];", tname, pmem, dsize));
        
        // init permanent memory
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i]=0;", pmem, dsize));
        
        // compute method
        
        // -- declare a buffer and a "shifted" vector
        fClass->addSharedDecl(buf);
        
        // -- variables moved as class fields...
        fClass->addDeclCode(subst("$0 \t$1[$2+$3];", tname, buf, T(gGlobal->gVecSize), dsize));
        
        fClass->addFirstPrivateDecl(dlname);
        fClass->addZone2(subst("$0* \t$1 = &$2[$3];", tname, dlname, buf, dsize));
        
        // -- copy the stored samples to the delay line
        fClass->addPreCode(Statement(ccs, subst("for (int i=0; i<$2; i++) $0[i]=$1[i];", buf, pmem, dsize)));
        
        // -- compute the new samples
        fClass->addExecCode(Statement(ccs, subst("$0[i] = $1;", dlname, cexp)));
        
        // -- copy back to stored samples
        fClass->addPostCode(Statement(ccs, subst("for (int i=0; i<$2; i++) $0[i]=$1[count+i];", pmem, buf, dsize)));
        
    } else {
        
        // Implementation of a ring-buffer delayline
        
        // the size should be large enough and aligned on a power of two
        delay   = pow2limit(delay + gGlobal->gVecSize);
        string  dsize   = T(delay);
        string  mask    = T(delay-1);
        
        // create names for temporary and permanent storage  
        string  idx = subst("$0_idx", dlname);
        string  idx_save = subst("$0_idx_save", dlname);
        
        // allocate permanent storage for delayed samples
        fClass->addDeclCode(subst("$0 \t$1[$2];", tname, dlname, dsize));
        fClass->addDeclCode(subst("int \t$0;", idx));
        fClass->addDeclCode(subst("int \t$0;", idx_save));
        
        // init permanent memory
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i]=0;", dlname, dsize));
        fClass->addClearCode(subst("$0 = 0;", idx));
        fClass->addClearCode(subst("$0 = 0;", idx_save));
        
        // -- update index
        fClass->addPreCode(Statement(ccs, subst("$0 = ($0+$1)&$2;", idx, idx_save, mask)));
        
        // -- compute the new samples
        fClass->addExecCode(Statement(ccs, subst("$0[($2+i)&$3] = $1;", dlname, cexp, idx, mask)));
        
        // -- save index
        fClass->addPostCode(Statement(ccs, subst("$0 = count;", idx_save)));
    }
}
