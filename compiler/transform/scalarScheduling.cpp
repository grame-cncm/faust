#include "scalarScheduling.hh"
#include <fstream>
#include <ostream>
#include "digraph.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigIdentity.hh"
#include "signalDependencies.hh"
#include "sigtyperules.hh"

using namespace std;

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

    // 2) create a vector of subgraphs
    digraph<digraph<Tree>> DG = graph2dag(G);
    vector<digraph<Tree>>  VG = serialize(DG);

    // 3) print each subgraph
    ofstream f;
    f.open(filename);

    f << "// SCALAR SCHEDULING " << endl;
    for (digraph<Tree> g : VG) {
        f << "\n// " << g << endl;

        vector<Tree> v = serialize(cut(g, 1));
        for (Tree i : v) {
            f << ppsig(Dic[i]) << endl;
        }
    }

    f.close();
}
