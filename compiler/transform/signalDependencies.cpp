#include <functional>
#include <iostream>
#include <sstream>

#include "ppsig.hh"
#include "signalDependencies.hh"

//-------------------------SignalDependencies---------------------------
// Compute the dependency graph (delay lines and controls) of a signal
//----------------------------------------------------------------------

class SignalDependencies : public SignalVisitor {
    Tree          fRoot;   // the ID of the signal we analyze
    digraph<Tree> fGraph;  // Its graph of dependencies

   public:
    SignalDependencies(Tree root)
    {
        Tree id, content;
        int  dmax, i;
        // Analyzed signals are supposed to be DelayLines, Controls or Outputs
        if (isSigDelayLineWrite(root, id, &dmax, content) || isSigControlWrite(root, id, content)) {
            fRoot = id;
            self(content);
        } else if (isSigOutput(root, &i, content)) {
            fRoot = root;  // sigInt(i);
            self(content);
        } else {
            std::cerr << "**** BIG ERROR ***" << endl;
        }
    }
    const digraph<Tree>& graph() const { return fGraph; }

   protected:
    virtual void visit(Tree t)
    {
        Tree id, dl;
        int  dmin;

        // the dependencies are DelayLines or Control signals
        if (isSigDelayLineRead(t, id, &dmin, dl)) {
            fGraph.add(fRoot, id, dmin);
            self(dl);
        } else if (isSigControlRead(t, id)) {
            fGraph.add(fRoot, id);
        } else {
            SignalVisitor::visit(t);
        }
    }
};

//================================================================

void Dictionnary::add(Tree sig)
{
    Tree id, content;
    int  dmax, i;
    // Analyzed signals are supposed to be DelayLines, Controls or Outputs
    if (isSigDelayLineWrite(sig, id, &dmax, content) || isSigControlWrite(sig, id, content)) {
        fDefinitions[id] = sig;
    } else if (isSigOutput(sig, &i, content)) {
        fDefinitions[sig] = sig;
    } else {
        std::cerr << "**** BIG ERROR ***" << endl;
    }
}

Tree Dictionnary::operator[](Tree id)
{
    return fDefinitions[id];
}

//================================================================
// signalDependencies(sig) : Compute the dependencies of a signal
// of type: sigDelayLineWrite() | sigControlWrite() | sigOutput()
// returns the dependency graph
//================================================================

digraph<Tree> dependencyGraph(Tree sig)
{
    SignalDependencies D(sig);
    return D.graph();
}

// replace ;= by \n
static string format(const string& s)
{
    string r;
    int    state = 0;
    for (char c : s) {
        if ((state == 0) & (c != ':')) {
            r += c;
        } else if ((state == 0) & (c == ':')) {
            state = 1;
        } else if ((state == 1) & (c != '=')) {
            r += ':';
            r += c;
            state = 0;
        } else if ((state == 1) & (c == '=')) {
            r += "\\n";
            state = 0;
        }
    }
    return r;
}

ostream& dotfile2(ostream& file, Dictionnary& dict, const digraph<Tree>& g)
{
    file << "digraph mygraph { \n\t node [shape=box]" << endl;
    for (Tree n : g.nodes()) {
        stringstream sn;
        sn << '"' << ppsig(dict[n]) << '"';
        bool hascnx = false;
        for (const auto& c : g.connections(n)) {
            stringstream sm;
            sm << '"' << ppsig(dict[c.first]) << '"';
            hascnx = true;
            if (c.second == 0) {
                file << "\t" << format(sn.str()) << "->" << format(sm.str()) << ";" << endl;
            } else {
                file << "\t" << format(sn.str()) << "->" << format(sm.str()) << " [label=\"" << c.second << "\"];"
                     << endl;
            }
        }
        if (!hascnx) {
            file << "\t" << format(sn.str()) << ";" << endl;
        }
    }

    return file << "}" << endl;
}
