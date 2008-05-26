#include "delayline.hh"
#include "Text.hh"

extern int gVecSize;
extern int gMaxCopyDelay;


static int pow2limit(int x)
{
    int n = 2;
    while (n < x) { n = 2*n; }
    return n;
}

/**
 * Generate the code for a (short) delay line
 * @param k the c++ class where the delay line will be placed.
 * @param l the loop where the code will be placed.
 * @param tname the name of the C++ type (float or int)
 * @param dlname the name of the delay line (vector) to be used.
 * @param delay the maximun delay
 * @param cexp the content of the signal as a C++ expression 
 */
void  vectorLoop (Klass* k, const string& tname, const string& vecname, const string& cexp) 
{  
    // -- declare the vector
    //k->addSlowCode(subst("$0 \t$1[$2];", tname, vecname, T(gVecSize)));
    //k->addLocalDecl(tname, subst("$0[$1]", vecname, T(gVecSize)));
    k->addLocalVecDecl(tname, vecname, gVecSize);
        
    // -- compute the new samples
    k->addExecCode(subst("$0[i] = $1;", vecname, cexp));
}


/**
 * Generate the code for a (short) delay line
 * @param k the c++ class where the delay line will be placed.
 * @param l the loop where the code will be placed.
 * @param tname the name of the C++ type (float or int)
 * @param dlname the name of the delay line (vector) to be used.
 * @param delay the maximun delay
 * @param cexp the content of the signal as a C++ expression 
 */
void  dlineLoop (Klass* k, const string& tname, const string& dlname, int delay, const string& cexp) 
{
    if (delay < gMaxCopyDelay) {

        // Implementation of a copy based delayline

	    // create names for temporary and permanent storage  
	    string  buf = subst("$0_tmp", dlname); 			
        string  pmem= subst("$0_perm", dlname);
        
        // constraints delay size to be multiple of 4
        delay = (delay+3)&-4;
            
        // allocate permanent storage for delayed samples
        string  dsize   = T(delay);
        k->addDeclCode(subst("$0 \t$1[$2];", tname, pmem, dsize));
            
        // init permanent memory
        k->addInitCode(subst("for (int i=0; i<$1; i++) $0[i]=0;", pmem, dsize)); 
            
        // compute method
            
        // -- declare a buffer and a "shifted" vector
        //k->addSlowCode(subst("static $0 \t$1[$2+$3];", tname, buf, T(gVecSize), dsize));
        //k->addSlowCode(subst("static $0* \t$1 = &$2[$3];", tname, dlname, buf, dsize));
        
		//k->addLocalDecl(tname, subst("$0[$1+$2]", buf, T(gVecSize), dsize));
        k->addLocalVecDecl(tname, buf, gVecSize+delay);

        ////////k->addLocalDecl(subst("$0*",tname), dlname, subst("&$0[$1]", buf, dsize));
        k->addLocalCommonDecl(subst("$0*",tname), dlname,  subst("&$0[$1]", buf, dsize));
    
        // -- copy the stored samples to the delay line
        k->addSlowExecCode(subst("for (int i=0; i<$2; i++) $0[i]=$1[i];", buf, pmem, dsize));
                    
        // -- compute the new samples
        k->addExecCode(subst("$0[i] = $1;", dlname, cexp));
            
        // -- copy back to stored samples
        k->addEndCode(subst("for (int i=0; i<$2; i++) $0[i]=$1[count+i];", pmem, buf, dsize));

    } else {

        // Implementation of a ring-buffer delayline

        // the size should be large enough and aligned on a power of two
        delay   = pow2limit(delay + gVecSize);
        string  dsize   = T(delay);
        string  mask    = T(delay-1);

        // create names for temporary and permanent storage  
        string  idx = subst("$0_idx", dlname);          
            
        // allocate permanent storage for delayed samples
        k->addDeclCode(subst("$0 \t$1[$2];", tname, dlname, dsize));
        k->addDeclCode(subst("int \t$0;", idx));
            
        // init permanent memory
        k->addInitCode(subst("for (int i=0; i<$1; i++) $0[i]=0;", dlname, dsize)); 
        k->addInitCode(subst("$0 = 0;", idx)); 
                    
        // -- compute the new samples
        k->addExecCode(subst("$0[($2+i)&$3] = $1;", dlname, cexp, idx, mask));
            
        // -- update index
        k->addEndCode(subst("$0 = ($0+count)&$1;", idx, mask));


    }
}
