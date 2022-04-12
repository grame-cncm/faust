#include <unordered_map>
#include <utility>

#include "Expr.hh"
namespace nlpl {
class IntExpr : public Expression {
    int fInt;

   public:
    explicit IntExpr(int i) : fInt(i) {}
    void getDependencies(std::set<Dependency>&) override {}
    void getSubExpr(std::set<Expression*>&) override {}
    void print(std::ostream& os) override { os << fInt; }
    int  priority() override { return 0; }
};

Expr Integer(int i)
{
    static std::unordered_map<int, Expr> gIntegerHashtable;
    auto                                 p = gIntegerHashtable.find(i);
    if (p != gIntegerHashtable.end()) {
        return p->second;
    } else {
        Expr e = new IntExpr(i);
        gIntegerHashtable.insert({i, e});
        return e;
    }
}
}  // namespace nlpl