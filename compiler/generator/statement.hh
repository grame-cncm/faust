#ifndef STATEMENT_H
#define STATEMENT_H

// implements a code statement with an optional condition

namespace std{}
using namespace std;

#include <string>

class Statement
{
    const bool   fHasCondition;
    const string fCondition;
    const string fCode;
public:
    Statement(const string& condition, const string& code);

    bool hasCondition();
    bool hasCondition(const string& cond);
    const string& condition();
    const string& code();
};

#endif // STATEMENT_H
