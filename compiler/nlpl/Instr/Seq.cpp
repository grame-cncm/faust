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
namespace nlpl {
class SeqInstr : public Instruction {
    std::vector<Instr> fInstructions;

   public:
    explicit SeqInstr(std::vector<Instr> I) : fInstructions(std::move(I)) {}

    std::set<Instr> lift() override { return {this}; }  // TODO(orlarey)

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
        if (indent < 1) indent = 1;
        tab(os, indent - 1) << "{";
        for (auto i : fInstructions) {
            i->print(os, indent);
        }
        tab(os, indent - 1) << "}";
    }

    Instruction* schedule() override
    {
        std::vector<Instr> V;
        for (Instr i : fInstructions) {
            V.push_back(i->schedule());
        }
        return Seq(V);
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

Instr Seq(const std::vector<Instr>& I)
{
    static std::unordered_map<std::vector<Instr>, Instr> gSeqHash;
    auto                                                 p = gSeqHash.find(I);
    if (p != gSeqHash.end()) {
        return p->second;
    } else {
        Instr e = new SeqInstr(I);
        gSeqHash.insert({I, e});
        return e;
    }
}
}  // namespace nlpl