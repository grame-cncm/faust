#include <functional>
#include <iostream>
#include <set>
#include <sstream>

#include "global.hh"
#include "ppsig.hh"
#include "signalDependencies.hh"
#include "symbol.hh"

#include "arrow.hh"
#include "digraph.hh"
#include "digraphop.hh"
#include "schedule.hh"
#include "stdprinting.hh"

using namespace std;

#if 0
class XYTableDependencies : public SignalVisitor {
   protected:
    set<Tree> fTables;
    void      visit(Tree t) override
    {
        Tree id, origin, dl;
        int  nature, dmin;

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
#endif

/**
 * @brief Compute the dependency graph of a signal
 *
 */
class SignalDependencies : public SignalVisitor {
    Tree                    fRoot;   // the ID of the signal we analyze
    digraph<Tree, multidep> fGraph;  // Its graph of dependencies

   public:
    SignalDependencies(Tree sig)
    {
        Tree id, tid, origin, content, init, idx, exp;
        int  i, nature, dmax, dmin, tblsize;
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
        } else if (isSigInstructionTableAccessWrite(sig, id, origin, &nature, &dmin, tid, idx)) {
            fRoot   = sig;
            Tree tw = getIDInstruction(tid);
            fGraph.add(fRoot, tw, mdep(/*std::string("8-") + */ tree2str(tid), dmin));
            self(idx);
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
    const digraph<Tree, multidep>& graph() const
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
            fGraph.add(fRoot, getIDInstruction(id), mdep(/*std::string("1-") + */ tree2str(id), dmin));
            self(dl);
        } else if (isSigInstructionTableRead(t, id, origin, &nature, &dmin, dl)) {
            fGraph.add(fRoot, getIDInstruction(id), mdep(/*std::string("2-") + */ tree2str(id), dmin));
            self(dl);
        } else if (isSigInstructionSharedRead(t, id, origin, &nature)) {
            fGraph.add(fRoot, getIDInstruction(id), mdep(/*std::string("3-") + */ tree2str(id), 0));
        } else if (isSigInstructionVectorRead(t, id, origin, &nature)) {
            fGraph.add(fRoot, getIDInstruction(id), mdep(/*std::string("4-") + */ tree2str(id), 0));
        } else if (isSigInstructionShortDLineRead(t, id, origin, &nature, &dmin)) {
            fGraph.add(fRoot, getIDInstruction(id), mdep(/*std::string("5-") + */ tree2str(id), dmin));
        } else if (isSigInstructionTimeRead(t)) {
            fGraph.add(fRoot, sigInstructionTimeWrite(), mdep("time", 0));  // TODO : a verifier (YO)
        } else if (isSigInstructionControlRead(t, id, origin, &nature)) {
            fGraph.add(fRoot, getIDInstruction(id), mdep(/*std::string("6-") + */ tree2str(id), 0));
        } else if (isSigInstructionBargraphRead(t, id, origin, &nature)) {
            fGraph.add(fRoot, getIDInstruction(id), mdep(/*std::string("7-") + */ tree2str(id), 0));
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

digraph<Tree, multidep> dependencyGraph(Tree sig)
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

ostream& dotfile2(ostream& file, const digraph<Tree, multidep>& g)
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
            hascnx        = true;
            std::string l = arrow_traits<multidep>::label(c.second);
            file << "\t" << sn.str() << "->" << sm.str() << " [label=\"" << l << "\"];" << endl;
        }
        if (!hascnx) {
            file << "\t" << sn.str() << ";" << endl;
        }
    }

    return file << "}" << endl;
}

static std::ostream& serialcontent(std::ostream& file, const digraph<Tree, multidep>& g)
{
    std::string       sep = "";
    std::vector<Tree> V   = serialize(cut(g, 1));

    for (Tree i : V) {
        file << ppsig(i) << "\n";
    }
    return file;
}

ostream& dotfile3(ostream& file, const digraph<digraph<Tree, multidep>, multidep>& g)
{
    cerr << "\n\nDOTFILE3 of graph " << g << "\n" << endl;

    file << "digraph mygraph { \n\t node [shape=box]" << endl;
    for (const auto& n : g.nodes()) {
        stringstream sn, src;
        cerr << "Handling node: " << n << endl;
        // cerr << "dict[" << *n << "] = " << *dict[n] << endl;
        serialcontent(std::cerr, n);
        serialcontent(src, n);
        sn << '"' << src.str() << '"';
        bool hascnx = false;
        for (const auto& c : g.connections(n)) {
            stringstream sm, dst;
            // cerr << "dotfile2: transcribing " << c << endl;
            serialcontent(dst, c.first);
            sm << '"' << dst.str() << '"';
            hascnx        = true;
            std::string l = arrow_traits<multidep>::label(c.second);
            file << "\t" << sn.str() << "->" << sm.str() << " [label=\"" << l << "\"];" << endl;
        }
        if (!hascnx) {
            file << "\t" << sn.str() << endl;
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

/**
 * @brief Compute the memory dependencies of a vector of instructions
 *
 */
class MemoryDependencies : public SignalVisitor {
    std::vector<std::pair<std::string, std::string>> MD;

   public:
    void analyze(Tree sig)
    {
        Tree id, tid, origin, content, init, idx, exp;
        int  i, nature, dmax, dmin, tblsize;
        // Analyzed signals are supposed to be "instructions": DelayLines, Shared, Controls or Outputs.
        // It is an error otherwise
        if (isSigInstructionDelayLineWrite(sig, id, origin, &nature, &dmax, content)) {
            self(content);
            MD.push_back(std::make_pair("write1", tree2str(id)));
        } else if (isSigInstructionSharedWrite(sig, id, origin, &nature, content)) {
            self(content);
            // MD.push_back(std::make_pair("write2", tree2str(id)));
        } else if (isSigInstructionVectorWrite(sig, id, origin, &nature, content)) {
            self(content);
            MD.push_back(std::make_pair("write3", tree2str(id)));
        } else if (isSigInstructionShortDLineWrite(sig, id, origin, &nature, content)) {
            self(content);
            MD.push_back(std::make_pair("write4", tree2str(id)));
        } else if (isSigInstructionControlWrite(sig, id, origin, &nature, content)) {
            self(content);
            MD.push_back(std::make_pair("write5", tree2str(id)));
        } else if (isSigInstructionBargraphWrite(sig, id, origin, &nature, content)) {
            self(content);
            MD.push_back(std::make_pair("write6", tree2str(id)));
        } else if (isSigInstructionTableWrite(sig, id, origin, &nature, &tblsize, init, idx, exp)) {
            self(idx);
            self(exp);
            MD.push_back(std::make_pair("write7", tree2str(id)));
        } else if (isSigInstructionTableAccessWrite(sig, id, origin, &nature, &dmin, tid, idx)) {
            self(idx);
            MD.push_back(std::make_pair("read0", tree2str(tid)));
        } else if (isSigOutput(sig, &i, content)) {
            self(content);
        } else if (isSigInstructionTimeWrite(sig)) {
        } else {
            std::cerr << "ERROR, not an instruction: " << ppsig(sig) << endl;
            faustassert(false);
        }
    }
    const std::vector<std::pair<std::string, std::string>>& getAnalysis() const
    {
        // std::cerr << "The dependency-graph of " << fRoot << "@" << ppsig(fRoot) << " is " << fGraph << std::endl;
        return MD;
    }

   protected:
    void visit(Tree t) override
    {
        Tree id, origin, dl;
        int  nature, dmax, dmin;

        // the dependencies are DelayLines, shared expressions or Control signals
        if (isSigInstructionDelayLineRead(t, id, origin, &nature, &dmax, &dmin, dl)) {
            self(dl);
            MD.push_back(std::make_pair("read1", tree2str(id)));
        } else if (isSigInstructionTableRead(t, id, origin, &nature, &dmin, dl)) {
            self(dl);
            MD.push_back(std::make_pair("read2", tree2str(id)));
        } else if (isSigInstructionSharedRead(t, id, origin, &nature)) {
            // MD.push_back(std::make_pair("read3", tree2str(id)));
        } else if (isSigInstructionVectorRead(t, id, origin, &nature)) {
            MD.push_back(std::make_pair("read4", tree2str(id)));
        } else if (isSigInstructionShortDLineRead(t, id, origin, &nature, &dmin)) {
            MD.push_back(std::make_pair("read5", tree2str(id)));
        } else if (isSigInstructionTimeRead(t)) {
        } else if (isSigInstructionControlRead(t, id, origin, &nature)) {
        } else if (isSigInstructionBargraphRead(t, id, origin, &nature)) {
        } else {
            SignalVisitor::visit(t);
        }
    }
};

//================================================================
// memoryDependencies(const std::vector<Tree>& I) : Compute the
// memory dependecies, a list of memory access
//================================================================

std::vector<std::pair<std::string, std::string>> memoryDependencies(const std::vector<Tree>& I)
{
    MemoryDependencies M;
    for (auto i : I) {
        M.analyze(i);
    }
    return M.getAnalysis();
}
