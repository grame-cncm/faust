#include "environment.hh"
#include "errormsg.hh"
#include "boxes.hh"
#include "ppbox.hh"
#include "names.hh"


//-----------------------new environment management----------------------------
//
// The environement is made of layers. Each layer contains a set of definitions
// stored as properties of the layer. Each definition can refers to other
// definitions of the same layer or of subsequent layers. Recursive
// definitions are not allowed. Multiple defintions of the same symbol
// in a layer is allowed but generate a warning when the definition is
// different
//-----------------------------------------------------------------------------



/**
 * Push a new (unique) empty layer (where multiple definitions can be stored)
 * on top of an existing environment.
 * @param lenv the old environment
 * @return the new environment
*/
static Tree pushNewLayer(Tree lenv)
{
    return tree(unique("ENV_LAYER"), lenv);
}



/**
 * Push a new environment barrier on top of an existing environment so
 * that searchIdDef (used by the pattern matcher) will not look after
 * the barrier. This barrier will not any influence on regular environment
 * lookup.
 * @param lenv the old environment
 * @return the new environment
*/
Sym BARRIER = symbol ("BARRIER");

Tree pushEnvBarrier(Tree lenv)
{
    return tree(BARRIER, lenv);
}


/**
 * Test if the environment is a barrier (or nil) so
 * that searchIdDef will know where to stop when searching
 * an environment.
 * @param lenv the environment to test
 * @return true is barrier reached
*/
bool isEnvBarrier(Tree lenv)
{
    return isNil(lenv) || (lenv->node() == Node(BARRIER));
}


/**
 * Add a definition (as a property) to the current top level layer. Check
 * and warn for multiple definitions.
 * @param id the symbol id to be defined
 * @param def the definition to be binded to the symbol id
 * @param lenv the environment where to add this new definition
*/
static void addLayerDef(Tree id, Tree def, Tree lenv)
{
    // check for multiple definitions of a symbol in the same layer
    Tree olddef;
    if (getProperty(lenv, id, olddef)) {
        if (def == olddef) {
            evalwarning(getDefFileProp(id), getDefLineProp(id), "equivalent re-definitions of", id);
        } else {
            fprintf(stderr, "%s:%d: ERROR: redefinition of symbols are not allowed : ", getDefFileProp(id), getDefLineProp(id));
            print(id,stderr);
            fprintf(stderr, " is already defined in file \"%s\" line %d \n", getDefFileProp(id), getDefLineProp(id));
            gErrorCount++;
        }
    }
    setProperty(lenv, id, def);
}


/**
 * Push a new layer and add a single definition.
 * @param id the symbol id to be defined
 * @param def the definition to be binded to the symbol id
 * @param lenv the environment where to push the layer and add the definition
 * @return the new environment
 */
Tree pushValueDef(Tree id, Tree def, Tree lenv)
{
    Tree lenv2 = pushNewLayer(lenv);
    addLayerDef(id, def, lenv2);
    return lenv2;
}


/**
 * Push a new layer with multiple definitions creating the appropriate closures
 * @param ldefs list of pairs (symbol id x definition) to be binded to the symbol id
 * @param visited set of visited symbols (used for recursive definition detection)
 * @param lenv the environment where to push the layer and add all the definitions
 * @return the new environment
*/
Tree pushMultiClosureDefs(Tree ldefs, Tree visited, Tree lenv)
{
    Tree lenv2 = pushNewLayer(lenv);
    while (!isNil(ldefs)) {
        Tree def = hd(ldefs);
        Tree id = hd(def);
        Tree rhs= tl(def);
        Tree cl = closure(tl(def),nil,visited,lenv2);
        stringstream s; s << boxpp(id);
        if (!isBoxCase(rhs)) setDefNameProperty(cl,s.str());
        addLayerDef( id, cl, lenv2 );
        ldefs = tl(ldefs);
    }
    return lenv2;
}


/**
 * Search the environment (until first barrier) for
 * the definition of a symbol ID and return it. Used by the
 * pattern matcher.
 * @param id the symbol ID to search
 * @param def where to store the definition if any
 * @param lenv the environment
 * @return true if a definition was found
 */
bool searchIdDef(Tree id, Tree& def, Tree lenv)
{
    // search the environment until a definition is found
    // or a barrier (or nil) is reached

    while (!isEnvBarrier(lenv) && !getProperty(lenv, id, def)) {
        lenv = lenv->branch(0);
    }
    return !isEnvBarrier(lenv);
}

/**
 * Replace closure that point to oldEnv with closure on newEnv
 */
static void updateClosures(vector<Tree>& clos, Tree oldEnv, Tree newEnv)
{
	for (unsigned int i=0; i < clos.size(); i++) {
        Tree exp, genv, visited, lenv;
        if (isClosure(clos[i], exp, genv, visited, lenv)) {
            if (lenv == oldEnv) {
                clos[i] = closure(exp, genv, visited, newEnv);
            }
        }
    }
}

/**
 * Create a new environment by copying an existing one and replacing some definitions
 * @param xenv existing environment we will copy
 * @param ldefs list of pairs (symbol id x definition) that will replace old definitions
 * @param visited set of visited symbols (used for recursive definition detection)
 * @param lenv the current environment to evaluate the definitions
 * @return the new environment
*/
Tree copyEnvReplaceDefs(Tree anEnv, Tree ldefs, Tree visited, Tree curEnv)
{
    vector<Tree>    ids, clos;
    Tree            copyEnv;

    anEnv->exportProperties(ids, clos);             // get the definitions of the environment
    copyEnv = pushNewLayer(anEnv->branch(0));       // create new environment with same stack
    updateClosures(clos, anEnv, copyEnv);           // update the closures replacing oldEnv with newEnv

	for (unsigned int i=0; i < clos.size(); i++) {           // transfers the updated definitions to the new environment
        setProperty(copyEnv, ids[i], clos[i]);
    }

    while (!isNil(ldefs)) {                         // replace the old definitions with the new ones
        Tree def = hd(ldefs);
        Tree id = hd(def);
        Tree rhs= tl(def);
        Tree cl = closure(rhs,nil,visited,curEnv);
        stringstream s; s << boxpp(id);
        if (!isBoxCase(rhs)) setDefNameProperty(cl,s.str());
        setProperty(copyEnv, id, cl);
        ldefs = tl(ldefs);
    }
    return copyEnv;
}


