#include "statement.hh"


Statement::Statement(const string& condition, const string& code)
    : fHasCondition(true), fCondition(condition), fCode(code)
{}

bool Statement::hasCondition()
{
    return fHasCondition;
}

bool Statement::hasCondition(const string& cond)
{
    return fCondition==cond;
}

const string& Statement::condition()
{
    return fCondition;
}

const string& Statement::code()
{
    return fCode;
}
