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

static bool isControl(Tree i)
{
    Tree id, origin, exp;
    bool r = isSigControlWrite(i, id, origin, exp);
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
    digraph<digraph<Tree>> DG = graph2dag(R);
    vector<digraph<Tree>>  VG = serialize(DG);

    // 3) print each subgraph
    ofstream f;
    f.open(filename);

    f << "// CONTROL SCHEDULING " << endl;
    for (Tree i : serialize(L)) {
        f << i << ":\t" << ppsig(Dic[i]) << endl;
    }
    f << endl;

    f << "// SCALAR SCHEDULING " << endl;
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
