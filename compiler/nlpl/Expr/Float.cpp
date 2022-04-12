#include <unordered_map>
#include <utility>

#include "Expr.hh"
namespace nlpl {
class FloatExpr : public Expression {
    double fFloat;

   public:
    explicit FloatExpr(double f) : fFloat(f) {}
    void getDependencies(std::set<Dependency>&) override {}
    void getSubExpr(std::set<Expression*>&) override {}
    void print(std::ostream& os) override { os << fFloat; }
    int  priority() override { return 0; }
};

Expr Float(double f)
{
    static std::unordered_map<double, Expr> gFloatHashtable;
    auto                                    p = gFloatHashtable.find(f);
    if (p != gFloatHashtable.end()) {
        return p->second;
    } else {
        Expr e = new FloatExpr(f);
        gFloatHashtable.insert({f, e});
        return e;
    }
}
}  // namespace nlpl