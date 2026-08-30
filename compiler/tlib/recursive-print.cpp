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

#include "recursive-print.hh"

#include <cstddef>
#include <ostream>
#include <vector>

namespace {

struct Definition {
    Tree fVar;
    Tree fBody;
};

struct PrintContext {
    int                     fDepth = 0;
    std::vector<Definition> fDefinitions;

    bool contains(Tree var) const
    {
        for (const Definition& definition : fDefinitions) {
            if (definition.fVar == var) {
                return true;
            }
        }
        return false;
    }
};

thread_local PrintContext gPrintContext;

}  // namespace

RecursivePrintSession::RecursivePrintSession() : fRoot(gPrintContext.fDepth++ == 0)
{
    if (fRoot) {
        gPrintContext.fDefinitions.clear();
    }
}

RecursivePrintSession::~RecursivePrintSession()
{
    --gPrintContext.fDepth;
}

std::ostream& RecursivePrintSession::reference(std::ostream& out, Tree var, Tree body)
{
    if (body && !gPrintContext.contains(var)) {
        gPrintContext.fDefinitions.push_back({var, body});
    }
    return out << *var;
}

void RecursivePrintSession::finish(std::ostream& out,
                                   const DefinitionPrinter& printDefinition) const
{
    if (!fRoot || gPrintContext.fDefinitions.empty()) {
        return;
    }

    out << "\nwith {\n";
    // Printing a body can discover additional, nested definitions.
    for (std::size_t i = 0; i < gPrintContext.fDefinitions.size(); ++i) {
        const Definition definition = gPrintContext.fDefinitions[i];
        out << "  " << *definition.fVar << " := ";
        printDefinition(out, definition.fVar, definition.fBody);
        out << "\n";
    }
    out << "}";
}
