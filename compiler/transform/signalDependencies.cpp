#include "signalDependencies.hh"

SignalDependencies::SignalDependencies(Tree root) : fVisitGen(false), fRoot(root)
{
    Tree id, content;
    int  dmax, i;

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

void SignalDependencies::visit(Tree t)
{
    Tree id, dl;
    int  dmin;

    if (isSigDelayLineRead(t, id, &dmin, dl)) {
        fGraph.add(fRoot, id, dmin);
        auto p = fDependencies.find(id);
        if (p != fDependencies.end()) {
            // the dependency already exists, we take the minimum
            p->second = std::min(p->second, dmin);
        } else {
            fDependencies[id] = dmin;
        }
        self(dl);
    } else if (isSigControlRead(t, id)) {
        fGraph.add(fRoot, id);
        fDependencies[id] = 0;
    } else {
        SignalVisitor::visit(t);
    }
}

ostream& SignalDependencies::print(ostream& dst) const
{
    string sep = "";
    dst << "Signal " << fRoot << " Depends on {";
    for (auto p : fDependencies) {
        dst << sep << p.first << "[" << p.second << "]";
        sep = ", ";
    }
    dst << "}" << std::endl;
    dst << "DIGRAPH: " << fGraph << endl;
    return dst;
}

const digraph<Tree>& SignalDependencies::graph() const
{
    return fGraph;
}