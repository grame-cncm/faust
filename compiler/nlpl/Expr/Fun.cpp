#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Expr.hh"

namespace nlpl {

class FunExpr : public Expression {
    std::string       fOpName;
    std::vector<Expr> fArgs;

   public:
    explicit FunExpr(std::string op, std::vector<Expr>  args) : fOpName(std::move(op)), fArgs(std::move(args)) {}

    void getDependencies(std::set<Dependency>& dep) override
    {
        for (Expr a : fArgs) a->getDependencies(dep);
    }

    void getSubExpr(std::set<Expression*>& subexpr) override
    {
        for (Expr a : fArgs) subexpr.insert(a);
    }

    void print(std::ostream& os) override
    {
        os << ' ' << fOpName << '(';
        std::string sep = "";
        for (Expr a : fArgs) {
            os << sep;
            a->print(os);
            sep = ", ";
        }
        os << ')';
    }

    int priority() override { return 1000; }
};

Expr Fun(const std::string& op, const std::vector<Expr>& args)
{
    static std::unordered_map<std::tuple<std::string, std::vector<Expr>>, Expr> gFunExprHash;
    std::tuple<std::string, std::vector<Expr>>                                  key(op, args);

    auto p = gFunExprHash.find(key);
    if (p != gFunExprHash.end()) {
        return p->second;
    } else {
        Expr e = new FunExpr(op, args);
        gFunExprHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl