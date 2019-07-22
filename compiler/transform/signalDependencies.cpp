#include <functional>
#include <iostream>
#include <sstream>

#include "ppsig.hh"
#include "signalDependencies.hh"
#include "symbol.hh"

//-------------------------SignalDependencies---------------------------
// Compute the dependency graph (delay lines and controls) of a signal
//----------------------------------------------------------------------

class SignalDependencies : public SignalVisitor {
    Tree          fRoot;   // the ID of the signal we analyze
    digraph<Tree> fGraph;  // Its graph of dependencies

   public:
    SignalDependencies(Tree sig)
    {
        Tree id, origin, content;
        int  dmax, i;
        // Analyzed signals are supposed to be "instructions": DelayLines, Controls or Outputs.
        // It is an error otherwise
        if (isSigDelayLineWrite(sig, id, origin, &dmax, content)) {
            fRoot = id;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigSharedWrite(sig, id, origin, content)) {
            fRoot = id;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigControlWrite(sig, id, origin, content)) {
            fRoot = id;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigOutput(sig, &i, content)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(content);
        } else {
            std::cerr << "**** BIG ERROR ***" << endl;
        }
    }
    const digraph<Tree>& graph() const
    {
        std::cerr << "The dependency-graph of " << fRoot << "@" << ppsig(fRoot) << " is " << fGraph << std::endl;
        return fGraph;
    }

   protected:
    virtual void visit(Tree t)
    {
        Tree id, origin, dl;
        int  dmin;

        // the dependencies are DelayLines or Control signals
        if (isSigDelayLineRead(t, id, origin, &dmin, dl)) {
            fGraph.add(fRoot, id, dmin);
            self(dl);
        } else if (isSigSharedRead(t, id, origin)) {
            fGraph.add(fRoot, id);
        } else if (isSigControlRead(t, id, origin)) {
            fGraph.add(fRoot, id);
        } else {
            SignalVisitor::visit(t);
        }
    }
};

//================================================================

void Dictionnary::add(Tree sig)
{
    Tree id, origin, content;
    int  dmax, i;
    // Analyzed signals are supposed to be DelayLines, Controls or Outputs
    if (isSigDelayLineWrite(sig, id, origin, &dmax, content) || isSigSharedWrite(sig, id, origin, content) ||
        isSigControlWrite(sig, id, origin, content)) {
        // cerr << "Dictionnary::add " << id << "@" << *id << " := " << *sig << endl;
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
    // D.trace(true, "compute dependencies");
    // cerr << "Dependencies of " << ppsig(sig) << " are " << D.graph() << endl;
    return D.graph();
}

// replace ;= by \n, max columns 40
static string format(const string& s)
{
    if (s.size() < 20) {
        return s;
    } else {
        string r;
        int    state = 0;
        int    count = 1;
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
                r += ":=\\n";
                state = 2;
                count = 1;
            } else if (state == 2) {
                r += c;
                if (++count % 40 == 0) r += "\\n";
            }
        }
        return r;
    }
}

ostream& dotfile2(ostream& file, Dictionnary& dict, const digraph<Tree>& g)
{
    file << "digraph mygraph { \n\t node [shape=box]" << endl;
    for (Tree n : g.nodes()) {
        stringstream sn, src;
        // cerr << "dict[" << *n << "] = " << *dict[n] << endl;
        src << ppsig(dict[n]);
        sn << '"' << format(src.str()) << '"';
        bool hascnx = false;
        for (const auto& c : g.connections(n)) {
            stringstream sm, dst;
            dst << ppsig(dict[c.first]);
            sm << '"' << format(dst.str()) << '"';
            hascnx = true;
            if (c.second == 0) {
                file << "\t" << sn.str() << "->" << sm.str() << ";" << endl;
            } else {
                file << "\t" << sn.str() << "->" << sm.str() << " [label=\"" << c.second << "\"];" << endl;
            }
        }
        if (!hascnx) {
            file << "\t" << sn.str() << ";" << endl;
        }
    }

    return file << "}" << endl;
}
