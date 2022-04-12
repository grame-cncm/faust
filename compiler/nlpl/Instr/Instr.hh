#pragma once

#include <array>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include "Expr.hh"
#include "HashTuple.hh"
#include "Memory.hh"

namespace nlpl {
std::ostream& tab(std::ostream& fout, int n);

/**
 * @brief instructions are expressions written in memory
 *
 */

class Instruction;
using Instr = Instruction*;

class Instruction {
   public:
    virtual std::set<Instr> lift()                                     = 0;  // lift an instruction into a set of instructions
    virtual void            getDependencies(std::set<Dependency>& dep) = 0;  // dependencies needed by this instr.
    virtual void            getProvided(std::set<Mem>& prov)           = 0;  // what this instruction provides
    virtual void            getSubInstr(std::set<Instruction*>& expr)  = 0;
    virtual void            print(std::ostream& os, int indent)        = 0;
    virtual Instr           schedule()                                 = 0;  // Transform set of instr. into seq
    virtual Instr           optimize()                                 = 0;  // merge if and repeats
    virtual void            dispatch(std::map<Expr, Instr>& IMap, std::map<Expr, Instr>& RMap, std::set<Instr>& OMap) = 0;
};

// Printing an expression
inline std::ostream& operator<<(std::ostream& os, Instr instr)
{
    instr->print(os, 0);
    return os;
}
// Mem-write modes

enum WriteMode : int { kReplaceWrite = 0, kAddWrite = 1, kSubWrite = 2 };
inline const char* WriteModeOp(int m)
{
    std::array<const char*, 3> name{"=", "+=", "-="};
    return name.at(m);
}

// Instructions builders
Instr SyncMem(Mem mem, const std::set<Mem>& D);
Instr WriteMem(Mem mem, int mode, Expr expr);
Instr WriteVec(Mem mem, int mode, Expr idx, Expr exp);
Instr Block(const std::set<Instr>& I);
Instr Seq(const std::vector<Instr>& I);
Instr IfThenElse(Expr cond, Instr THEN, Instr ELSE);
Instr Repeat(Expr count, Instr body);

// classify dependencies in two sets, internal and external
void classifyDependencies(Instr i, std::set<Dependency>& internal, std::set<Dependency>& external);

// simplified API
inline Instr Write(Mem mem, Expr expr)
{
    return WriteMem(mem, kReplaceWrite, expr);
}
inline Instr Write(Mem mem, Expr idx, Expr expr)
{
    return WriteVec(mem, kReplaceWrite, idx, expr);
}

}  // namespace nlpl