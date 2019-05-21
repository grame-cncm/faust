#include "signalDependencies.hh"

void SignalDependencies::visit(Tree t)
{
    Tree id, dl;
    int  dmin;

    if (isSigDelayLineRead(t, id, &dmin, dl)) {
        auto p = fDependencies.find(id);
        if (p != fDependencies.end()) {
            // the dependency already exists, we take the minimum
            p->second = std::min(p->second, dmin);
        } else {
            fDependencies[id] = dmin;
        }
        self(dl);
    } else {
        SignalVisitor::visit(t);
    }
}

ostream& SignalDependencies::print(ostream& dst) const
{
    string sep = "";
    dst << "SignalDependencies {";
    for (auto p : fDependencies) {
        dst << sep << p.first << "[" << p.second << "]";
        sep = ", ";
    }
    dst << "}" << std::endl;
    return dst;
}
