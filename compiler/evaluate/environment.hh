#ifndef ENVIRONMENT_HH
#define ENVIRONMENT_HH


#include "tlib.hh"

Tree pushValueDef(Tree id, Tree def, Tree lenv);

bool searchIdDef(Tree id, Tree& def, Tree lenv);

Tree pushMultiClosureDefs(Tree ldefs, Tree visited, Tree lenv);

Tree copyEnvReplaceDefs(Tree anEnv, Tree ldefs, Tree visited, Tree curEnv);

#endif // ENVIRONMENT_HH
