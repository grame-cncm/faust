#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "DependenciesGraph.hh"

/**
 * @brief Result of auditing a hierarchical dependency graph.
 *
 * Contains validation status and lists of errors and warnings found during the audit.
 */
struct AuditResult {
    bool                     valid;     ///< True if the graph passes all checks
    std::vector<std::string> errors;    ///< List of errors found
    std::vector<std::string> warnings;  ///< List of warnings found
};

/**
 * @brief Audits a hierarchical dependency graph for consistency.
 *
 * This function checks various properties of the Hgraph:
 * - Each signal appears in at most one graph (main, controls, or subgraph)
 * - Control signals are properly classified
 * - Signals with subgraphs satisfy needSubGraph()
 *
 * @param hg The hierarchical graph to audit.
 * @return An AuditResult containing validation status and any errors/warnings.
 */
AuditResult auditHgraph(const Hgraph& hg);
