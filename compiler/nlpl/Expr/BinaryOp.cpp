#include <tuple>
#include <unordered_map>
#include <utility>

#include "Expr.hh"

namespace nlpl {
class BinaryExpr : public Expression {
    std::string fOpName;
    int         fPriority;
    Expr        fLeft;
    Expr        fRight;

   public:
    explicit BinaryExpr(std::string op, int priority, Expr left, Expr right)
        : fOpName(std::move(op)), fPriority(priority), fLeft(left), fRight(right)
    {
    }

    void getDependencies(std::set<Dependency>& dep) override
    {
        fLeft->getDependencies(dep);
        fRight->getDependencies(dep);
    }

    void getSubExpr(std::set<Expression*>& subexpr) override
    {
        subexpr.insert(fLeft);
        subexpr.insert(fRight);
    }

    void print(std::ostream& os) override
    {
        if (fLeft->priority() > fPriority) {
            os << '(' << fLeft << ')';
        } else {
            os << fLeft;
        }
        os << ' ' << fOpName << ' ';
        if (fRight->priority() > fPriority) {
            os << '(' << fRight << ')';
        } else {
            os << fRight;
        }
    }

    int priority() override { return fPriority; }
};

Expr BinaryOp(const std::string& op, int priority, Expr left, Expr right)
{
    static std::unordered_map<std::tuple<std::string, int, Expr, Expr>, Expr> gBinaryExprHash;

    std::tuple<std::string, int, Expr, Expr> key(op, priority, left, right);

    auto p = gBinaryExprHash.find(key);
    if (p != gBinaryExprHash.end()) {
        return p->second;
    } else {
        Expr e = new BinaryExpr(op, priority, left, right);
        gBinaryExprHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl