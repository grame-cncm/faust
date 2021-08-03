#include <unordered_map>
#include <utility>

#include "Expr.hh"
#include "Memory.hh"
namespace nlpl {
class ReadMemExpr : public Expression {
    Memory fMem;

   public:
    explicit ReadMemExpr(Memory mem) : fMem(mem) {}
    void getDependencies(std::set<Dependency>& dep) override { dep.insert({fMem, 0}); }
    void getSubExpr(std::set<Expression*>&) override {}
    void print(std::ostream& os) override { os << fMem->name(); }
    int  priority() override { return -1; }
};

Expr ReadMem(Memory mem)
{
    static std::unordered_map<Memory, Expr> gHash;
    auto                                    p = gHash.find(mem);
    if (p != gHash.end()) {
        return p->second;
    } else {
        Expr e = new ReadMemExpr(mem);
        gHash.insert({mem, e});
        return e;
    }
}
}  // namespace nlpl