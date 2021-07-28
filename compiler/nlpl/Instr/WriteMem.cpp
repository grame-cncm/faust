#include <array>
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
class WriteMemInstr : public Instruction
{
    Memory fMem;
    int    fMode;
    Expr   fExpr;

   public:
    explicit WriteMemInstr(Memory mem, int mode, Expr expr) : fMem(mem), fMode(mode), fExpr(expr) {}

    std::set<Instr> lift() override { return {this}; }
    void            getDependencies(std::set<Dependency>& dep) override { fExpr->getDependencies(dep); }
    void            getProvided(std::set<Memory>& prov) override { prov.insert(fMem); }
    void            getSubInstr(std::set<Instruction*>&) override {}
    void            print(std::ostream& os, int indent) override
    {
        tab(os, indent) << fMem << ' ' << WriteModeOp(fMode) << ' ' << fExpr << ';';
    }

    Instruction* schedule() override { return this; }
    Instruction* optimize() override { return this; }
    void dispatch(std::map<Expr, Instr>&, std::map<Expr, Instr>&, std::set<Instr>& OMap) override { OMap.insert(this); }
};

Instr WriteMem(Memory mem, int mode, Expr expr)
{
    static std::unordered_map<std::tuple<Memory, int, Expr>, Instr> gWriteMemHash;
    std::tuple<Memory, int, Expr>                                   key(mem, mode, expr);
    auto                                                            p = gWriteMemHash.find(key);
    if (p != gWriteMemHash.end()) {
        return p->second;
    } else {
        Instr e = new WriteMemInstr(mem, mode, expr);
        gWriteMemHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl