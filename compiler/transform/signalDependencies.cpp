#include <functional>
#include <iostream>
#include <set>
#include <sstream>

#include "global.hh"
#include "ppsig.hh"
#include "signalDependencies.hh"
#include "symbol.hh"

using namespace std;

class XYTableDependencies : public SignalVisitor {
   protected:
    set<Tree> fTables;
    void      visit(Tree t) override
    {
        Tree id, origin, dl;
        int  nature, dmax, dmin;

        // the dependencies are DelayLines, shared expressions or Control signals
        if (isSigInstructionTableRead(t, id, origin, &nature, &dmin, dl)) {
            fTables.insert(getIDInstruction(id));
            self(dl);
        } else {
            SignalVisitor::visit(t);
        }
    }

   public:
    XYTableDependencies() {}
    const set<Tree>& tables() const
    {
        // std::cerr << "The dependency-graph of " << fRoot << "@" << ppsig(fRoot) << " is " << fGraph << std::endl;
        return fTables;
    }
};

set<Tree> listTableDependencies(Tree t)
{
    XYTableDependencies D;
    D.self(t);
    return D.tables();
}
/**
 * @brief Compute the dependency graph of a signal
 *
 */
class SignalDependencies : public SignalVisitor {
    Tree          fRoot;   // the ID of the signal we analyze
    digraph<Tree> fGraph;  // Its graph of dependencies

   public:
    SignalDependencies(Tree sig)
    {
        Tree id, origin, content, init, idx, exp;
        int  i, nature, dmax, tblsize;
        // Analyzed signals are supposed to be "instructions": DelayLines, Shared, Controls or Outputs.
        // It is an error otherwise
        if (isSigInstructionDelayLineWrite(sig, id, origin, &nature, &dmax, content)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigInstructionSharedWrite(sig, id, origin, &nature, content)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigInstructionVectorWrite(sig, id, origin, &nature, content)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigInstructionShortDLineWrite(sig, id, origin, &nature, content)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigInstructionControlWrite(sig, id, origin, &nature, content)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigInstructionBargraphWrite(sig, id, origin, &nature, content)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigInstructionTableWrite(sig, id, origin, &nature, &tblsize, init, idx, exp)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(init);
            self(idx);
            self(exp);
        } else if (isSigOutput(sig, &i, content)) {
            fRoot = sig;
            fGraph.add(fRoot);
            self(content);
        } else if (isSigInstructionTimeWrite(sig)) {
            fRoot = sig;
            fGraph.add(fRoot);
        } else {
            std::cerr << "ERROR, not an instruction: " << ppsig(sig) << endl;
            faustassert(false);
        }
    }
    const digraph<Tree>& graph() const
    {
        // std::cerr << "The dependency-graph of " << fRoot << "@" << ppsig(fRoot) << " is " << fGraph << std::endl;
        return fGraph;
    }

   protected:
    void visit(Tree t) override
    {
        Tree id, origin, dl;
        int  nature, dmax, dmin;

        // the dependencies are DelayLines, shared expressions or Control signals
        if (isSigInstructionDelayLineRead(t, id, origin, &nature, &dmax, &dmin, dl)) {
            fGraph.add(fRoot, getIDInstruction(id), dmin);
            self(dl);
        } else if (isSigInstructionTableRead(t, id, origin, &nature, &dmin, dl)) {
            fGraph.add(fRoot, getIDInstruction(id), dmin);
            self(dl);
        } else if (isSigInstructionSharedRead(t, id, origin, &nature)) {
            fGraph.add(fRoot, getIDInstruction(id));
        } else if (isSigInstructionVectorRead(t, id, origin, &nature)) {
            fGraph.add(fRoot, getIDInstruction(id));
        } else if (isSigInstructionShortDLineRead(t, id, origin, &nature, &dmin)) {
            fGraph.add(fRoot, getIDInstruction(id), dmin);
        } else if (isSigInstructionTimeRead(t)) {
            fGraph.add(fRoot, sigInstructionTimeWrite(), 0);  // TODO : a verifier (YO)
        } else if (isSigInstructionControlRead(t, id, origin, &nature)) {
            fGraph.add(fRoot, getIDInstruction(id));
        } else if (isSigInstructionBargraphRead(t, id, origin, &nature)) {
            fGraph.add(fRoot, getIDInstruction(id));
        } else {
            SignalVisitor::visit(t);
        }
    }
};

//================================================================
// signalDependencies(sig) : Compute the dependencies of a signal
// of type: sigInstructionDelayLineWrite() | sigInstructionControlWrite() | sigOutput()
// returns the dependency graph
//================================================================

digraph<Tree> dependencyGraph(Tree sig)
{
    SignalDependencies D(sig);
    D.trace(gGlobal->gDebugSwitch, "SignalDependencies");
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

ostream& dotfile2(ostream& file, const digraph<Tree>& g)
{
    // cerr << "\n\nDOT2FILE of graph " << g << "\n" << endl;

    file << "digraph mygraph { \n\t node [shape=box]" << endl;
    for (Tree n : g.nodes()) {
        stringstream sn, src;
        // cerr << "Handling node: " << n << "@" << ppsig(n) << endl;
        // cerr << "dict[" << *n << "] = " << *dict[n] << endl;
        src << ppsig(n);
        sn << '"' << format(src.str()) << '"';
        bool hascnx = false;
        for (const auto& c : g.connections(n)) {
            stringstream sm, dst;
            // cerr << "dotfile2: transcribing " << c << endl;
            dst << ppsig(c.first);
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

/**
 * @brief associates a unique ID to a signal
 *
 * @param prefix the prefix of the ID
 * @param sig the signal that will be associated to the id
 * @return Tree always the same unique ID
 */
Tree uniqueID(const char* prefix, Tree sig)
{
    Tree ID;
    Tree key = tree(symbol(prefix));
    if (getProperty(sig, key, ID)) {
        return ID;
    } else {
        ID = tree(unique(prefix));
        setProperty(sig, key, ID);
        return ID;
    }
}
