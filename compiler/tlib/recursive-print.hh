/************************************************************************
 ************************************************************************
    TLIB : tree library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#ifndef __RECURSIVE_PRINT_HH__
#define __RECURSIVE_PRINT_HH__

#include <functional>
#include <iosfwd>

#include "export.hh"
#include "tree.hh"

/**
 * Collects symbolic recursive definitions during a customized tree print.
 *
 * Nested sessions cooperate within one thread: only the outermost session
 * emits the collected definitions. Different threads have independent state.
 * The node-specific printer remains entirely under the caller's control.
 */
class TLIB_API RecursivePrintSession {
   public:
    using DefinitionPrinter = std::function<void(std::ostream&, Tree, Tree)>;

    RecursivePrintSession();
    ~RecursivePrintSession();

    RecursivePrintSession(const RecursivePrintSession&)            = delete;
    RecursivePrintSession& operator=(const RecursivePrintSession&) = delete;

    /// Print a recursive variable and remember its definition once.
    static std::ostream& reference(std::ostream& out, Tree var, Tree body);

    /// Emit all definitions collected by the outermost printing session.
    /// Definitions discovered while printing another definition are included.
    void finish(std::ostream& out, const DefinitionPrinter& printDefinition) const;

   private:
    bool fRoot;
};

#endif
