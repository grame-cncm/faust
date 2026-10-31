/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "eval.h"

#include <algorithm>
#include <cctype>

#include "text.h"

static const std::string kOpener = "__faustprobe_env = environment{ ";
static const std::string kMember = "__faustprobe_eval";

EvalProgram::EvalProgram(const std::string& file, const std::vector<std::string>& exprs)
{
    if (exprs.empty()) {
        throw Failure("--eval needs an expression");
    }
    for (std::string expr : exprs) {
        // one line per expression: its diagnostics are located on it
        std::replace(expr.begin(), expr.end(), '\n', ' ');
        std::replace(expr.begin(), expr.end(), '\r', ' ');
        expr = trim(expr);
        while (!expr.empty() && expr.back() == ';') {
            expr.pop_back();
        }
        expr = trim(expr);
        if (expr.empty()) {
            throw Failure("--eval was given an empty expression");
        }
        fExprs.push_back(expr);
    }
    fFile = file;
    while (!fFile.empty() && isspace(static_cast<unsigned char>(fFile.back()))) {
        fFile.pop_back();
    }
}

size_t EvalProgram::exprLine(size_t k) const
{
    // the file, then three lines per expression: name, expression, ';'
    size_t lines = fFile.empty() ? 1 : split(fFile, '\n').size();
    return lines + 3 * k + 2;
}

std::string EvalProgram::environment() const
{
    std::string source = kOpener + fFile + "\n";
    for (size_t k = 0; k < fExprs.size(); k++) {
        source += kMember + str(k) + " =\n" + fExprs[k] + "\n;\n";
    }
    return source + "};\n";
}

std::string EvalProgram::source() const
{
    std::vector<std::string> members;
    for (size_t k = 0; k < fExprs.size(); k++) {
        members.push_back("__faustprobe_env." + kMember + str(k));
    }
    return environment() + "process = " + join(members, ", ") + ";\n";
}

std::string EvalProgram::aritySource() const
{
    std::vector<std::string> members;
    for (size_t k = 0; k < fExprs.size(); k++) {
        members.push_back("outputs(__faustprobe_env." + kMember + str(k) + ")");
    }
    return environment() + "process = " + join(members, ", ") + ";\n";
}

std::vector<std::string> EvalProgram::labels(const std::vector<size_t>& arities, size_t outputs) const
{
    size_t                   total = 0;
    std::vector<std::string> shown;
    for (size_t arity : arities) {
        total += arity;
        shown.push_back(str(arity));
    }
    if (arities.size() != fExprs.size() || total != outputs) {
        throw Failure("--eval: the expressions have [" + join(shown, ", ") + "] outputs and the program " +
                      str(outputs));
    }
    std::vector<std::string> labels;
    for (size_t k = 0; k < fExprs.size(); k++) {
        for (size_t j = 0; j < arities[k]; j++) {
            labels.push_back(arities[k] == 1 ? fExprs[k] : fExprs[k] + "[" + str(j) + "]");
        }
    }
    return labels;
}

// The symbol of an 'undefined symbol : NAME' diagnostic.
static std::string undefinedSymbol(const std::string& error)
{
    const std::string marker = "undefined symbol : ";
    size_t            at     = error.find(marker);
    if (at == std::string::npos) {
        return "";
    }
    size_t from = at + marker.size(), to = from;
    while (to < error.size() && !isspace(static_cast<unsigned char>(error[to]))) {
        to++;
    }
    return error.substr(from, to - from);
}

// Whether 'expr' uses the identifier 'symbol'.
static bool usesIdentifier(const std::string& expr, const std::string& symbol)
{
    auto wordChar = [](char c) { return isalnum(static_cast<unsigned char>(c)) || c == '_'; };
    for (size_t at = expr.find(symbol); at != std::string::npos; at = expr.find(symbol, at + 1)) {
        bool startsWord = at == 0 || !wordChar(expr[at - 1]);
        bool endsWord   = at + symbol.size() == expr.size() || !wordChar(expr[at + symbol.size()]);
        if (startsWord && endsWord) {
            return true;
        }
    }
    return false;
}

// A location of libfaust reads 'NAME:LINE : ERROR : ...'. On the lines of
// expression k it becomes '<eval k>:1', with a note saying which expression
// that is; a location in the file is already right.
std::string EvalProgram::explain(const std::string& name, const std::string& error) const
{
    std::string              text = error;
    std::vector<std::string> notes;
    std::vector<bool>        located(fExprs.size(), false);
    for (size_t k = 0; k < fExprs.size(); k++) {
        size_t line = exprLine(k);
        // the expression's own line; then its terminator, where a parser
        // reports what the expression left open
        std::string onExpr       = name + ":" + str(line) + " :";
        std::string onTerminator = name + ":" + str(line + 1) + " :";
        located[k]               = text.find(onExpr) != std::string::npos || text.find(onTerminator) != std::string::npos;
        std::string here         = "<eval " + str(k) + ">:1 :";
        text                     = replaceAll(replaceAll(text, onTerminator, here), onExpr, here);
        if (located[k]) {
            notes.push_back("  = note: <eval " + str(k) + "> is `--eval '" + fExprs[k] + "'`, line " + str(line) +
                            " of the source as wrapped");
        }
    }
    std::string symbol = undefinedSymbol(error);
    if (!symbol.empty()) {
        for (size_t k = 0; k < fExprs.size(); k++) {
            if (!located[k] && usesIdentifier(fExprs[k], symbol)) {
                notes.push_back("  = note: `" + symbol + "` is used by <eval " + str(k) + ">, `--eval '" + fExprs[k] +
                                "'`: an expression sees the file's top-level definitions, not those local to a "
                                "`with` block");
            }
        }
    }
    if (text.find("__faustprobe_env") != std::string::npos) {
        notes.push_back("  = note: `" + trim(kOpener) +
                        "...` and `process = ...` are the wrapper `--eval` puts around the file");
    }
    return notes.empty() ? text : trim(text) + "\n" + join(notes, "\n");
}

std::string EvalProgram::renameMembers(std::string text) const
{
    for (size_t k = fExprs.size(); k-- > 0;) {
        text = replaceAll(text, "__faustprobe_env." + kMember + str(k), fExprs[k]);
        text = replaceAll(text, kMember + str(k), fExprs[k]);
    }
    return text;
}
