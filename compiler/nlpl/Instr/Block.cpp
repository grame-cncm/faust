#include <array>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Expr.hh"
#include "Instr.hh"
#include "arrow.hh"
#include "digraph.hh"
#include "digraphop.hh"
#include "schedule.hh"
#include "stdprinting.hh"
namespace nlpl
{
static const std::vector<Instr> scheduleInstructions(const std::set<Instr>& I)
{
    std::unordered_map<Mem, Instr> providedBy;  // Collect everything provided by I
    digraph<Instr, multidep>       G;           // The dependency graph
    for (Instr i : I) {
        G.add(i);
        std::set<Mem> M;
        i->getProvided(M);
        for (Mem m : M) {
            providedBy[m] = i;
        }
    }
    for (Instr i : I) {
        std::set<Dependency> D;
        i->getDependencies(D);
        for (const Dependency& d : D) {
            auto p = providedBy.find(d.first);
            if ((d.second == 0) && (p != providedBy.end())) {
                // Only consider immediate local dependencies
                Instr src = p->second;
                G.add(i, src, mdep(d.first->fName, d.second));
            }
        }
    }
    schedule<Instr> S = dfschedule(G);
    return S.elements();
}

class BlockInstr : public Instruction
{
    std::set<Instr> fInstructions;

   public:
    explicit BlockInstr(std::set<Instr> I) : fInstructions(std::move(I)) {}

    std::set<Instr> lift() override { return fInstructions; }

    void getDependencies(std::set<Dependency>& dep) override
    {
        for (auto i : fInstructions) i->getDependencies(dep);
    }
    void getProvided(std::set<Mem>& prov) override
    {
        for (auto i : fInstructions) i->getProvided(prov);
    }
    void getSubInstr(std::set<Instruction*>& subs) override
    {
        for (auto i : fInstructions) subs.insert(i);
    }
    void print(std::ostream& os, int indent) override
    {
        if (indent < 1) {
            indent = 1;  // special case when printing a block with an indent of 0 (outside an if or a repeat)
        }
        tab(os, indent - 1) << "{";
        for (auto i : fInstructions) {
            i->print(os, indent);
        }
        tab(os, indent - 1) << "}";
    }
    Instr schedule() override
    {
        std::set<Instr> I;
        for (Instr i : fInstructions) {
            I.insert(i->schedule());
        }
        return Seq(scheduleInstructions(I));
    }

    /**
     * @brief We optimize a set of instructions by grouping IF and Repeats. Blocks are flattened
     *
     * @return Instr
     */
    Instr optimize() override
    {
        // combine if with same condition and repeat with same count
        std::map<Expr, Instr> IMap;  // If then else grouped by condition
        std::map<Expr, Instr> RMap;  // Repeat grouped by repeat expression
        std::set<Instr>       OMap;  // Other instructions

        this->dispatch(IMap, RMap, OMap);

        std::set<Instr> R;
        for (auto m : IMap) {
            R.insert(m.second);
        }
        for (auto m : RMap) {
            R.insert(m.second);
        }
        for (auto i : OMap) {
            R.insert(i);
        }
        return Block(R);
    }

    void dispatch(std::map<Expr, Instr>& IMap, std::map<Expr, Instr>& RMap, std::set<Instr>& OMap) override
    {
        for (Instr i : fInstructions) {
            i->dispatch(IMap, RMap, OMap);
        }
    }
};

Instr Block(const std::set<Instr>& I)
{
    static std::unordered_map<std::set<Instr>, Instr> gBlockHash;
    auto                                              p = gBlockHash.find(I);
    if (p != gBlockHash.end()) {
        return p->second;
    } else {
        Instr e = new BlockInstr(I);
        gBlockHash.insert({I, e});
        return e;
    }
}
}  // namespace nlpl