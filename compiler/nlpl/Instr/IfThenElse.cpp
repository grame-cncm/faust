#include <tuple>
#include <unordered_map>
#include <utility>

#include <cassert>

#include <string>
#include <vector>

#include "Expr.hh"
#include "Instr.hh"

namespace nlpl
{
class IfThenElseInstr : public Instruction
{
    Expr  fCond;
    Instr fThen;
    Instr fElse;

   public:
    explicit IfThenElseInstr(Expr cond, Instr THEN, Instr ELSE) : fCond(cond), fThen(THEN), fElse(ELSE) {}

    // accessors
    Expr  cond() const { return fCond; }
    Instr theninstr() const { return fThen; }
    Instr elseinstr() const { return fElse; }

    std::set<Instr> lift() override { return {this}; }

    void getDependencies(std::set<Dependency>& dep) override
    {
        fCond->getDependencies(dep);
        fThen->getDependencies(dep);
        fElse->getDependencies(dep);
    }
    void getProvided(std::set<Memory>& prov) override
    {
        fThen->getProvided(prov);
        fElse->getProvided(prov);
    }
    void getSubInstr(std::set<Instruction*>& I) override
    {
        I.insert(fThen);
        I.insert(fElse);
    }
    void print(std::ostream& os, int indent) override
    {
        tab(os, indent) << "if (" << fCond << ")";
        fThen->print(os, indent + 1);
        tab(os, indent) << "else";
        fElse->print(os, indent + 1);
    }

    Instruction* schedule() override { return IfThenElse(fCond, fThen->schedule(), fElse->schedule()); }
    Instruction* optimize() override { return IfThenElse(fCond, fThen->optimize(), fElse->optimize()); }

    void dispatch(std::map<Expr, Instr>& IMap, std::map<Expr, Instr>&, std::set<Instr>&) override
    {
        auto p = IMap.find(fCond);
        if (p == IMap.end()) {
            // First IF for this condition
            IMap.insert({fCond, this});
        } else {
            // we already have an If with this condition
            if (auto r = dynamic_cast<IfThenElseInstr*>(p->second)) {
                // merge the two then and the two else branches
                std::set<Instr> T, E;
                for (Instr i : fThen->lift()) T.insert(i);
                for (Instr i : r->theninstr()->lift()) T.insert(i);
                for (Instr i : fElse->lift()) E.insert(i);
                for (Instr i : r->elseinstr()->lift()) E.insert(i);
                // Create the new IF
                Instr m = IfThenElse(fCond, Block(T), Block(E));
                IMap.insert({fCond, m});
            }
        }
    }
};

Instr IfThenElse(Expr cond, Instr THEN, Instr ELSE)
{
    static std::unordered_map<std::tuple<Expr, Instr, Instr>, Instr> gIfThenElseHash;
    std::tuple<Expr, Instr, Instr>                                   key(cond, THEN, ELSE);
    auto                                                             p = gIfThenElseHash.find(key);
    if (p != gIfThenElseHash.end()) {
        return p->second;
    } else {
        Instr e = new IfThenElseInstr(cond, THEN, ELSE);
        gIfThenElseHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl