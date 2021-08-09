#include <unordered_map>
#include <utility>

#include "Expr.hh"
#include "Memory.hh"
namespace nlpl {
class ReadMemExpr : public Expression {
    Memory fMem;
    int    fMinDelay;

   public:
    explicit ReadMemExpr(Memory mem, int minDelay) : fMem(mem), fMinDelay(minDelay) {}
    void getDependencies(std::set<Dependency>& dep) override { dep.insert({fMem, fMinDelay}); }
    void getSubExpr(std::set<Expression*>&) override {}
    void print(std::ostream& os) override { os << fMem->name(); }
    int  priority() override { return -1; }
};

Expr ReadMem(Memory mem, int minDelay)
{
    static std::unordered_map<std::tuple<Memory, int>, Expr> gReadMemExprHash;
    std::tuple<Memory, int>                                  key(mem, minDelay);

    auto p = gReadMemExprHash.find(key);
    if (p != gReadMemExprHash.end()) {
        return p->second;
    } else {
        Expr e = new ReadMemExpr(mem, minDelay);
        gReadMemExprHash.insert({key, e});
        return e;
    }
}

Expr ReadMem(Memory mem)
{
    return ReadMem(mem, 0);
}

}  // namespace nlpl