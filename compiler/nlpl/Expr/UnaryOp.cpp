#include <tuple>
#include <unordered_map>
#include <utility>

#include "Expr.hh"
namespace nlpl {
class UnaryExpr : public Expression {
    std::string fOpName;
    int         fPriority;
    Expr        fExp;

   public:
    explicit UnaryExpr(std::string op, int priority, Expr exp) : fOpName(std::move(op)), fPriority(priority), fExp(exp) {}
    void getDependencies(std::set<Dependency>& dep) override { fExp->getDependencies(dep); }
    void getSubExpr(std::set<Expression*>& subexpr) override { subexpr.insert(fExp); }

    int  priority() override { return fPriority; }
    void print(std::ostream& os) override { os << fOpName << fExp; }
};

Expr UnaryOp(const std::string& op, int priority, Expr exp)
{
    static std::unordered_map<std::tuple<std::string, int, Expr>, Expr> gUnaryExprHash;
    std::tuple<std::string, int, Expr>                                  key(op, priority, exp);

    auto p = gUnaryExprHash.find(key);
    if (p != gUnaryExprHash.end()) {
        return p->second;
    } else {
        Expr e = new UnaryExpr(op, priority, exp);
        gUnaryExprHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl