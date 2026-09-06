/*
 * Copyright (c) 2026, Yann Orlarey
 * SPDX-License-Identifier: Apache-2.0
 */

//
//  HierarchyDot.hh
//  DirectedGraph
//
//  Graphviz renderings of a hierarchy (HIERARCHY-SPEC.md). Graphviz has the
//  notion the structure needs : a cluster draws its nodes in a box, and
//  clusters nest. A laminar family of parts draws as is -- one cluster per
//  group, nesting by inclusion, the effective label as the cluster's title,
//  the boundary edges crossing the boxes, the delays as edge labels.
//
//  Two views, because the graphs are large :
//    hierarchyDot : every node inside its nested clusters, the recursive own
//                   components in dotted clusters -- the view that debugs
//                   one grouping ;
//    quotientDot  : one node per vertex of the quotient of a chosen group,
//                   a child as a box, an own component as an ellipse, the
//                   merged edges with their united delays -- the view of
//                   the execution structure, readable on big programs.
//

#pragma once

#include <functional>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <variant>
#include <vector>

#include "Hierarchy.hh"

namespace hierarchydot {

// a dot identifier : letters, digits and underscores, quoted otherwise
inline std::string quoted(const std::string& s)
{
    std::string r = "\"";
    for (char c : s) {
        if (c == '"' || c == '\\') {
            r += '\\';
        }
        r += c;
    }
    return r + "\"";
}

inline std::string delays(const std::set<int>& d)
{
    std::string r;
    for (int x : d) {
        if (!r.empty()) {
            r += ",";
        }
        r += std::to_string(x);
    }
    return r;
}

}  // namespace hierarchydot

// The full view. nodeId names a node for dot (unique, no quotes needed if
// it is an identifier ; it is quoted anyway) ; nodeLabel is what the box
// shows ; labelText turns a label into the cluster's title (unused when the
// hierarchy has no label type of interest : pass a function returning "").
template <typename N, typename L>
void hierarchyDot(std::ostream& out, const hierarchy<N, L>& h,
                  const std::function<std::string(const N&)>& nodeId,
                  const std::function<std::string(const N&)>& nodeLabel,
                  const std::function<std::string(const L&)>& labelText, const std::string& name = "hierarchy")
{
    using H     = hierarchy<N, L>;
    using Group = typename H::Group;
    using namespace hierarchydot;

    out << "digraph " << quoted(name) << " {\n";
    out << "  rankdir=LR;\n  node [shape=box, fontname=\"Helvetica\"];\n  compound=true;\n";

    // clusters, one per group, nested by inclusion ; a counter names them
    int                                    counter = 0;
    std::function<void(const Group&, int)> cluster = [&](const Group& g, int depth) {
        std::string ind(2 * (depth + 1), ' ');
        bool        isRoot = (g == h.root());
        if (!isRoot) {
            out << ind << "subgraph cluster_" << counter++ << " {\n";
            std::string title = "group of " + std::to_string(g.size());
            if (auto l = h.label(g)) {
                std::string t = labelText(*l);
                if (!t.empty()) {
                    title = t;
                }
            }
            out << ind << "  label=" << quoted(title) << ";\n" << ind << "  style=rounded;\n";
        }
        std::string inner = isRoot ? ind : ind + "  ";
        // the recursive own components, dotted
        auto q = h.quotient(g);
        for (const auto& v : q.nodes()) {
            if (const auto* own = std::get_if<typename H::Own>(&v)) {
                if (own->nodes.size() > 1) {
                    out << inner << "subgraph cluster_" << counter++ << " {\n"
                        << inner << "  style=dotted;\n" << inner << "  label=\"recurrence\";\n";
                    for (const N& n : own->nodes) {
                        out << inner << "  " << quoted(nodeId(n)) << " [label=" << quoted(nodeLabel(n)) << "];\n";
                    }
                    out << inner << "}\n";
                } else {
                    const N& n = *own->nodes.begin();
                    out << inner << quoted(nodeId(n)) << " [label=" << quoted(nodeLabel(n)) << "];\n";
                }
            }
        }
        for (const Group& c : h.children(g)) {
            cluster(c, isRoot ? depth : depth + 1);
        }
        if (!isRoot) {
            out << ind << "}\n";
        }
    };
    cluster(h.root(), 0);

    // the edges, every one, with their delays
    for (const N& u : h.root()) {
        for (const auto& dst : h.graph().destinations(u)) {
            out << "  " << quoted(nodeId(u)) << " -> " << quoted(nodeId(dst.first));
            std::string d = delays(dst.second);
            if (d != "0") {
                out << " [label=" << quoted(d) << "]";
            }
            out << ";\n";
        }
    }
    out << "}\n";
}

// The quotient view of one group : a child as a box titled by its label or
// its size, an own component as an ellipse listing its nodes.
template <typename N, typename L>
void quotientDot(std::ostream& out, const hierarchy<N, L>& h, const typename hierarchy<N, L>::Group& a,
                 const std::function<std::string(const N&)>& nodeLabel,
                 const std::function<std::string(const L&)>& labelText, const std::string& name = "quotient")
{
    using H      = hierarchy<N, L>;
    using Vertex = typename H::Vertex;
    using namespace hierarchydot;

    auto q = h.quotient(a);
    std::map<Vertex, std::string> id;
    int                           counter = 0;
    out << "digraph " << quoted(name) << " {\n  rankdir=LR;\n  node [fontname=\"Helvetica\"];\n";
    for (const auto& v : q.nodes()) {
        std::string vid = "v" + std::to_string(counter++);
        id[v]           = vid;
        if (const auto* c = std::get_if<typename H::Child>(&v)) {
            std::string title = "group of " + std::to_string(c->group.size());
            if (auto l = h.label(c->group)) {
                std::string t = labelText(*l);
                if (!t.empty()) {
                    title = t;
                }
            }
            out << "  " << vid << " [shape=box, style=rounded, label=" << quoted(title) << "];\n";
        } else {
            const auto& o = std::get<typename H::Own>(v);
            std::string text;
            for (const N& n : o.nodes) {
                if (!text.empty()) {
                    text += "\\n";
                }
                text += nodeLabel(n);
            }
            out << "  " << vid << " [shape=" << (o.nodes.size() > 1 ? "doubleoctagon" : "ellipse")
                << ", label=" << quoted(text) << "];\n";
        }
    }
    for (const auto& v : q.nodes()) {
        for (const auto& dst : q.destinations(v)) {
            out << "  " << id[v] << " -> " << id[dst.first];
            std::string d = delays(dst.second);
            if (d != "0") {
                out << " [label=" << quoted(d) << "]";
            }
            out << ";\n";
        }
    }
    out << "}\n";
}
