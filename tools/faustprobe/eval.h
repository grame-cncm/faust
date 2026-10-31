/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// --eval EXPR: an expression evaluated in a file's scope, without a file
// written for it. The source is wrapped in environment{}, as poly-dsp.h does to
// reach 'effect', and the expressions are added inside it:
//
//     __faustprobe_env = environment{ <line 1 of the file>
//     <the rest of the file>
//     __faustprobe_eval0 =
//     EXPR0
//     ;
//     };
//     process = __faustprobe_env.__faustprobe_eval0;
//
// The file keeps its line numbers, the opener sharing its first line, and an
// expression is alone on its line, which explain() renames <eval k>.

#ifndef __faustprobe_eval__
#define __faustprobe_eval__

#include <string>
#include <vector>

// A file wrapped for the evaluation of some expressions.
class EvalProgram {
   public:
    // Wraps a file's text; refuses an empty expression.
    EvalProgram(const std::string& file, const std::vector<std::string>& exprs);

    // The expressions, flattened to a line and without their trailing semicolon.
    const std::vector<std::string>& exprs() const { return fExprs; }
    // The 1-based line of the wrapped source that holds expression k.
    size_t                          exprLine(size_t k) const;
    // The program that computes the expressions, their outputs side by side.
    std::string source() const;
    // The program whose outputs are the number of outputs of each expression.
    std::string aritySource() const;
    // One label per output of source(): the expression, with [j] when it has several.
    std::vector<std::string> labels(const std::vector<size_t>& arities, size_t outputs) const;
    // A compile error of the wrapped source, for the person who typed the expressions.
    std::string explain(const std::string& name, const std::string& error) const;
    // The expression standing for a member of the environment in a text.
    std::string renameMembers(std::string text) const;

   private:
    // The environment, up to and including its closing brace.
    std::string environment() const;
    std::vector<std::string> fExprs;  // as typed, on one line
    std::string              fFile;  // the file's text, without its trailing blank lines
};

#endif
