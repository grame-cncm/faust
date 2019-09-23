#include "scalarScheduling.hh"
#include <fstream>
#include <ostream>
#include "digraph.hh"
#include "digraphop.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigIdentity.hh"
#include "signalDependencies.hh"
#include "sigtyperules.hh"

using namespace std;

/**
 * @brief Check if an instruction can be computed at init time
 *
 * @param i the instruction to test
 * @return true if a control instruction of variability kKonst
 * @return false otherwise
 */
static bool isInit(Tree i)
{
    Tree id, origin, exp;
    int  nat;
    bool r = isSigInstructionControlWrite(i, id, origin, &nat, exp);

    if (r) {
        Type t = getCertifiedSigType(origin);
        cerr << "-> " << *t << " -> " << ppsig(i) << endl;
        if (t->variability() == kKonst) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Check if a control instruction
 *
 * @param i the instruction to test
 * @return true if it is a control instruction
 * @return false otherwise
 */
static bool isControl(Tree i)
{
    Tree id, origin, exp;
    int  nat;
    bool r = isSigInstructionControlWrite(i, id, origin, &nat, exp);

    if (r) {
        Type t = getCertifiedSigType(origin);
        cerr << "-> " << *t << " -> " << ppsig(i) << endl;
    }
    return r;
}

/**
 * @brief generates a text file from a set of instructions
 *
 * @param "filename.txt" the name of the file
 * @param instr the set of instructions
 */
void scalarScheduling(const string& filename, set<Tree> I)
{
    digraph<Tree> G;  // the signal graph
    Dictionnary   Dic;

    // 1) build the graph
    for (auto i : I) {
        G.add(dependencyGraph(i));
        Dic.add(i);
    }

    // split in two graphs
    digraph<Tree> T;  // the subgraph of control instructions (temporary)
    digraph<Tree> K;  // the subgraph of init-time instructions
    digraph<Tree> B;  // the subgraph of block-time instructions
    digraph<Tree> E;  // the subgraph at sample-time instructions

    splitgraph<Tree>(G, [&Dic](Tree id) { return isControl(Dic[id]); }, T, E);
    splitgraph<Tree>(T, [&Dic](Tree id) { return isInit(Dic[id]); }, K, B);

    // 3) print each subgraph
    ofstream f;
    f.open(filename);

    f << "// INIT SCHEDULING " << endl;
    for (Tree i : serialize(K)) {
        f << i << ":\t" << ppsig(Dic[i]) << endl;
    }
    f << endl;

    f << "// CONTROL SCHEDULING " << endl;
    for (Tree i : serialize(B)) {
        f << i << ":\t" << ppsig(Dic[i]) << endl;
    }
    f << endl;

    f << "// SCALAR SCHEDULING " << endl;
    digraph<digraph<Tree>> DG = graph2dag(E);
    vector<digraph<Tree>>  VG = serialize(DG);

    for (digraph<Tree> g : VG) {
        f << "\n// " << g << "\n" << endl;

        vector<Tree> v = serialize(cut(g, 1));
        for (Tree i : v) {
            f << i << ":\t" << ppsig(Dic[i]) << endl;
        }
    }

    f.close();
}

/**
 * @brief generates a parallel scheduling from a set of instructions
 *
 * @param "filename.txt" the name of the file
 * @param I the set of instructions
 */
void parallelScheduling(const string& filename, set<Tree> I)
{
    digraph<Tree> G;
    Dictionnary   Dic;

    // 1) build the graph
    for (auto i : I) {
        G.add(dependencyGraph(i));
        Dic.add(i);
    }

    // split in two graphs
    digraph<Tree> L;  // the control graph
    digraph<Tree> R;  // the signal graph

    splitgraph<Tree>(G, [&Dic](Tree id) { return isControl(Dic[id]); }, L, R);

    // 2) create a vector of subgraphs
    digraph<digraph<Tree>>        DG = graph2dag(R);
    vector<vector<digraph<Tree>>> PG = parallelize(DG);

    // 3) print each subgraph
    ofstream f;
    f.open(filename);

    f << "// CONTROL SCHEDULING " << endl;
    for (Tree i : serialize(L)) {
        f << i << ":\t" << ppsig(Dic[i]) << endl;
    }
    f << endl;

    f << "// PARALLEL SCHEDULING " << endl;
    for (vector<digraph<Tree>> p : PG) {
        f << "\n// BEGIN PARALLEL TASKS" << endl;
        for (digraph<Tree> g : p) {
            f << "\n// begin task: " << g << endl;
            vector<Tree> v = serialize(cut(g, 1));
            for (Tree i : v) {
                f << i << ":\t" << ppsig(Dic[i]) << endl;
            }
            f << "// end   task" << endl;
        }
        f << "\n// END PARALLEL TASKS\n" << endl;
    }

    f.close();
}
