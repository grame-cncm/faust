#include <cassert>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Expr.hh"
#include "Instr.hh"
namespace nlpl
{
class RepeatInstr : public Instruction
{
    Expr  fCount;
    Instr fBody;

   public:
    explicit RepeatInstr(Expr count, Instr body) : fCount(count), fBody(body) {}

    Expr  count() const { return fCount; }
    Instr body() const { return fBody; }

    std::set<Instr> lift() override { return {this}; }

    void getDependencies(std::set<Dependency>& dep) override
    {
        fCount->getDependencies(dep);
        fBody->getDependencies(dep);
    }
    void getProvided(std::set<Memory>& prov) override { fBody->getProvided(prov); }
    void getSubInstr(std::set<Instruction*>& I) override { I.insert(fBody); }
    void print(std::ostream& os, int indent) override
    {
        tab(os, indent) << "for (int i = 0; i < " << fCount << "; i++)";
        fBody->print(os, indent + 1);
    }

    Instruction* schedule() override { return Repeat(fCount, fBody->schedule()); }
    Instruction* optimize() override { return Repeat(fCount, fBody->optimize()); }

    /**
     * @brief Add this instruction into RMap with a merge if needed
     *
     * @param RMap
     */
    void dispatch(std::map<Expr, Instr>&, std::map<Expr, Instr>& RMap, std::set<Instr>&) override
    {
        auto p = RMap.find(fCount);
        if (p == RMap.end()) {
            // First repeat of this fCount
            RMap.insert({fCount, this});
        } else {
            // we already have a repeat with this fCount
            if (auto r = dynamic_cast<RepeatInstr*>(p->second)) {
                std::set<Instr> B;
                for (Instr i : fBody->lift()) B.insert(i);
                for (Instr i : r->body()->lift()) B.insert(i);
                // Create the new Repeat
                Instr m = Repeat(fCount, Block(B));
                RMap.insert({fCount, m});
            }
        }
    }
};

Instr Repeat(Expr count, Instr body)
{
    static std::unordered_map<std::tuple<Expr, Instr>, Instr> gRepeatHash;
    std::tuple<Expr, Instr>                                   key(count, body);
    auto                                                      p = gRepeatHash.find(key);
    if (p != gRepeatHash.end()) {
        return p->second;
    } else {
        Instr e = new RepeatInstr(count, body);
        gRepeatHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl