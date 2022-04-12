#pragma once

#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include "HashTuple.hh"
#include "Memory.hh"

namespace nlpl {
// Expressions

class Expression {
   public:
    virtual void getDependencies(std::set<Dependency>& dep) = 0;
    virtual void getSubExpr(std::set<Expression*>& subexpr) = 0;
    virtual void print(std::ostream& os)                    = 0;
    virtual int  priority()                                 = 0;
};
using Expr = Expression*;

// Expression builders
Expr Integer(int i);
Expr Float(double f);
Expr ReadMem(Mem mem);
Expr ReadMem(Mem mem, int minDelay);
Expr ReadVec(Mem mem, Expr idx, int minDelay);
Expr UnaryOp(const std::string& op, int priority, Expr exp);
Expr BinaryOp(const std::string& op, int priority, Expr left, Expr right);
Expr Fun(const std::string& op, const std::vector<Expr>& args);

// Printing an expression
inline std::ostream& operator<<(std::ostream& os, Expr exp)
{
    exp->print(os);
    return os;
}

// C++ operator precedence (partial list)
enum Rank {
    kTop    = 0,
    kMul    = 5,
    kAdd    = 6,
    kShift  = 7,
    kOrder  = 9,
    kEq     = 10,
    kBitAnd = 11,
    kBitXOr = 12,
    kBitOr  = 13,
    kLogAnd = 14,
    kLogOr  = 15
};

// multiplicative: * / %
inline Expr Mul(Expr left, Expr right)
{
    return BinaryOp("*", Rank::kMul, left, right);
}

inline Expr Div(Expr left, Expr right)
{
    return BinaryOp("/", kMul, left, right);
}

inline Expr Mod(Expr left, Expr right)
{
    return BinaryOp("%", kMul, left, right);
}

// addition and substraction

inline Expr Add(Expr left, Expr right)
{
    return BinaryOp("+", kAdd, left, right);
}

inline Expr Sub(Expr left, Expr right)
{
    return BinaryOp("-", kAdd, left, right);
}

// Bitwise shift

inline Expr LeftShift(Expr left, Expr right)
{
    return BinaryOp("<<", kShift, left, right);
}

inline Expr RightShift(Expr left, Expr right)
{
    return BinaryOp(">>", kShift, left, right);
}

// Relational (order) operations

inline Expr Less(Expr left, Expr right)
{
    return BinaryOp("<", kOrder, left, right);
}

inline Expr LessEq(Expr left, Expr right)
{
    return BinaryOp("<=", kOrder, left, right);
}

inline Expr Greater(Expr left, Expr right)
{
    return BinaryOp(">", kOrder, left, right);
}

inline Expr GreaterEq(Expr left, Expr right)
{
    return BinaryOp(">=", kOrder, left, right);
}

// Equality operations

inline Expr Equal(Expr left, Expr right)
{
    return BinaryOp("==", kEq, left, right);
}

inline Expr Diff(Expr left, Expr right)
{
    return BinaryOp("!=", kEq, left, right);
}

// Others

inline Expr BitAnd(Expr left, Expr right)
{
    return BinaryOp("&", kBitAnd, left, right);
}

inline Expr BitXOr(Expr left, Expr right)
{
    return BinaryOp("^", kBitXOr, left, right);
}

inline Expr BitOr(Expr left, Expr right)
{
    return BinaryOp("|", kBitOr, left, right);
}

inline Expr LogAnd(Expr left, Expr right)
{
    return BinaryOp("&&", kLogAnd, left, right);
}

inline Expr LogOr(Expr left, Expr right)
{
    return BinaryOp("||", kLogOr, left, right);
}

}  // namespace nlpl