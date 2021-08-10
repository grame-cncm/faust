#include <unordered_map>
#include <utility>

#include "Expr.hh"
#include "Memory.hh"
namespace nlpl
{
class ReadMemExpr : public Expression
{
    Mem fMem;
    int fMinDelay;

   public:
    explicit ReadMemExpr(Mem mem, int minDelay) : fMem(mem), fMinDelay(minDelay) {}
    void getDependencies(std::set<Dependency>& dep) override { dep.insert({fMem, fMinDelay}); }
    void getSubExpr(std::set<Expression*>&) override {}
    void print(std::ostream& os) override { os << fMem->fName; }
    int  priority() override { return -1; }
};

Expr ReadMem(Mem mem, int minDelay)
{
    static std::unordered_map<std::tuple<Mem, int>, Expr> gReadMemExprHash;
    std::tuple<Mem, int>                                  key(mem, minDelay);

    auto p = gReadMemExprHash.find(key);
    if (p != gReadMemExprHash.end()) {
        return p->second;
    } else {
        Expr e = new ReadMemExpr(mem, minDelay);
        gReadMemExprHash.insert({key, e});
        return e;
    }
}

Expr ReadMem(Mem mem)
{
    return ReadMem(mem, 0);
}

}  // namespace nlpl