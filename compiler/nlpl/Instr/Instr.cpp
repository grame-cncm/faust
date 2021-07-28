#include "Instr.hh"
namespace nlpl
{
/**
 * @brief classify dependencies in two sets, internal and external
 *
 * @param i instruction
 * @param internal set of self-provided internal dependencies
 * @param external set of non-provided external dependencies
 *
 */

void classifyDependencies(Instr i, std::set<Dependency>& internal, std::set<Dependency>& external)
{
    std::set<Dependency> D;
    std::set<Memory>     P;

    i->getDependencies(D);
    i->getProvided(P);

    for (const auto& d : D) {
        if (P.find(d.first) != P.end()) {
            internal.insert(d);  // found in Provided ==> internal dependency
        } else {
            external.insert(d);  // not found in Provided ==> external dependency
        }
    }
}

std::ostream& tab(std::ostream& fout, int n)
{
    fout << '\n';
    if (n > 0) {
        while (n--) fout << "    ";
    }
    return fout;
}
}  // namespace nlpl