#include <iostream>
#include <set>
#include <vector>
#include "ppsig.hh"
#include "sigDependenciesGraph.hh"
#include "signalVisitor.hh"
#include "signals.hh"
#include "sigtyperules.hh"

#undef TRACE

static void printsignal(std::ostream& file, std::set<Tree>& visited, int depth, Tree sig)
{
    if (sig->arity() == 0) {
        file << sig->node();
        return;
    }
    if (depth <= 0 || visited.count(sig)) {
        file << '$' << sig;
        return;
    }
    visited.insert(sig);
    int p;
    if (Tree rgroup; isProj(sig, &p, rgroup)) {
        Tree id, body;
        faustassert(isRec(rgroup, id, body));
        file << '$' << sig << ':' << "proj(" << p << " of recgroup " << *rgroup << " = ";
        printsignal(file, visited, depth - 1, body);
        file << ") ";
        return;
    }
    file << '$' << sig << ':' << sig->node();
    if (sig->arity() > 0) {
        file << " [";
        for (int i = 0; i < sig->arity(); i++) {
            if (i > 0) {
                file << ", ";
            }
            printsignal(file, visited, depth - 1, sig->branch(i));
        }
        file << "]";
    }
}

/**
 * @brief A class for validating signal trees.
 *
 * This class extends `SignalVisitor` to traverse and validate signal trees.
 * It ensures that each signal has a valid type and tracks the visitation count.
 */
class SignalValidator : public SignalVisitor {
   private:
    std::vector<Tree> fStack;  ///< Stack to keep track of visited signals
   public:
    SignalValidator() : SignalVisitor()
    {
        fTrace   = false;
        fMessage = "SignalValidator";
    }

   protected:
    void visit(Tree t) override;
};

/**
 * @brief
 */
void SignalValidator::visit(Tree sig)
{
    Type ty = getSigType(sig);
    if (!ty) {
        std::set<Tree> visited;
        std::cerr << "No type for: ";
        printsignal(std::cerr, visited, 1, sig);
        std::cerr << "\n";

        // Afficher jusqu'à 5 niveaux d'ascendants avec leurs types
        int levels = std::min(5, (int)fStack.size());
        for (int i = 0; i < levels; i++) {
            Tree ancestor     = fStack[fStack.size() - 1 - i];
            Type ancestorType = getSigType(ancestor);
            std::cerr << "Ancestor level " << (i + 1) << ": ";
            printsignal(std::cerr, visited, 2, ancestor);
            if (ancestorType) {
                std::cerr << " (type: " << ancestorType << ")";
            }
            std::cerr << "\n";
        }
        std::cerr << "\n";
        return;
    }
    fStack.push_back(sig);
    SignalVisitor::visit(sig);
    fStack.pop_back();
}

// External API functions

void validateSignal(Tree sig)
{
    SignalValidator validator;
    validator.self(sig);
}

void validateSignalList(Tree L)
{
    SignalValidator validator;
    validator.bypassRecGroup(true);
    validator.mapself(L);
}