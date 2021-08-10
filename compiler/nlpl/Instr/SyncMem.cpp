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
    Mem           fMem;
    std::set<Mem> fDep;

   public:
    explicit SyncMemInstr(Mem mem, std::set<Mem> D) : fMem(mem), fDep(std::move(D)) {}

    std::set<Instr> lift() override { return {this}; }
    void            getDependencies(std::set<Dependency>& dep) override
    {
        for (auto m : fDep) {
            dep.insert({m, 0});
        }
    }
    void getProvided(std::set<Mem>& prov) override { prov.insert(fMem); }
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

Instr SyncMem(Mem mem, const std::set<Mem>& D)
{
    static std::unordered_map<std::tuple<Mem, std::set<Mem>>, Instr> gSyncMemHash;
    std::tuple<Mem, std::set<Mem>>                                   key(mem, D);
    auto                                                             p = gSyncMemHash.find(key);
    if (p != gSyncMemHash.end()) {
        return p->second;
    } else {
        Instr e = new SyncMemInstr(mem, D);
        gSyncMemHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl