#include <tuple>
#include <unordered_map>
#include <utility>

#include <string>
#include <vector>

#include "Expr.hh"
#include "Instr.hh"
namespace nlpl {
class WriteVecInstr : public Instruction {
    Mem  fMem;
    int  fMode;
    Expr fIndex;
    Expr fExpr;

   public:
    explicit WriteVecInstr(Mem mem, int mode, Expr idx, Expr expr) : fMem(mem), fMode(mode), fIndex(idx), fExpr(expr) {}

    std::set<Instr> lift() override { return {this}; }
    void            getDependencies(std::set<Dependency>& dep) override { fExpr->getDependencies(dep); }
    void            getProvided(std::set<Mem>& prov) override { prov.insert(fMem); }
    void            getSubInstr(std::set<Instruction*>&) override {}
    void            print(std::ostream& os, int indent) override
    {
        tab(os, indent) << fMem << '[' << fIndex << ']' << ' ' << WriteModeOp(fMode) << ' ' << fExpr << ';';
    }
    Instruction* schedule() override { return this; }
    Instruction* optimize() override { return this; }
    void         dispatch(std::map<Expr, Instr>&, std::map<Expr, Instr>&, std::set<Instr>& OMap) override { OMap.insert(this); }
};

Instr WriteVec(Mem mem, int mode, Expr idx, Expr expr)
{
    static std::unordered_map<std::tuple<Mem, int, Expr, Expr>, Instr> gWriteVecHash;
    std::tuple<Mem, int, Expr, Expr>                                   key(mem, mode, idx, expr);
    auto                                                               p = gWriteVecHash.find(key);
    if (p != gWriteVecHash.end()) {
        return p->second;
    } else {
        Instr e = new WriteVecInstr(mem, mode, idx, expr);
        gWriteVecHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl