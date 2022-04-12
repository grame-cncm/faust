#include <tuple>
#include <unordered_map>
#include <utility>

#include "Expr.hh"
namespace nlpl {
class ReadVecExpr : public Expression {
    Mem  fMem;
    Expr fIndex;
    int  fMinDelay;

   public:
    explicit ReadVecExpr(Mem mem, Expr idx, int minDelay) : fMem(mem), fIndex(idx), fMinDelay(minDelay) {}

    void getDependencies(std::set<Dependency>& dep) override
    {
        dep.insert({fMem, fMinDelay});
        fIndex->getDependencies(dep);
    }

    void getSubExpr(std::set<Expression*>& subexpr) override { subexpr.insert(fIndex); }

    void print(std::ostream& os) override { os << fMem->fName << '[' << fIndex << ']'; }

    int priority() override { return 0; }
};

Expr ReadVec(Mem mem, Expr idx, int minDelay)
{
    static std::unordered_map<std::tuple<Mem, Expr, int>, Expr> gReadVecExprHash;
    std::tuple<Mem, Expr, int>                                  key(mem, idx, minDelay);

    auto p = gReadVecExprHash.find(key);
    if (p != gReadVecExprHash.end()) {
        return p->second;
    } else {
        Expr e = new ReadVecExpr(mem, idx, minDelay);
        gReadVecExprHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl