#include <array>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Expr.hh"
#include "Instr.hh"
#include "Memory.hh"

namespace nlpl
{
class SyncMemInstr : public Instruction
{
    Memory           fMem;
    std::set<Memory> fDep;

   public:
    explicit SyncMemInstr(Memory mem, std::set<Memory> D) : fMem(mem), fDep(std::move(D)) {}

    std::set<Instr> lift() override { return {this}; }
    void            getDependencies(std::set<Dependency>& dep) override
    {
        for (auto m : fDep) {
            dep.insert({m, 0});
        }
    }
    void getProvided(std::set<Memory>& prov) override { prov.insert(fMem); }
    void getSubInstr(std::set<Instruction*>&) override {}
    void print(std::ostream& os, int indent) override
    {
        tab(os, indent) << fMem << " sync";
        for (auto m : fDep) {
            os << ' ' << m;
        }
        os << ';';
    }

    Instruction* schedule() override { return this; }
    Instruction* optimize() override { return this; }
    void dispatch(std::map<Expr, Instr>&, std::map<Expr, Instr>&, std::set<Instr>& OMap) override { OMap.insert(this); }
};

Instr SyncMem(Memory mem, const std::set<Memory>& D)
{
    static std::unordered_map<std::tuple<Memory, std::set<Memory>>, Instr> gSyncMemHash;
    std::tuple<Memory, std::set<Memory>>                                   key(mem, D);
    auto                                                                   p = gSyncMemHash.find(key);
    if (p != gSyncMemHash.end()) {
        return p->second;
    } else {
        Instr e = new SyncMemInstr(mem, D);
        gSyncMemHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl