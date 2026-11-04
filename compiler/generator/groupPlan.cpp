/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "groupPlan.hh"

#include <functional>
#include <ostream>

void GroupPlan::print(std::ostream& out) const
{
    std::function<void(int, int)> walk = [&](int id, int depth) {
        const GroupNode&   n = nodes[id];
        static const char* K[] = {"Feuille", "Boucle", "Insecable", "Adjacent", "Libre"};
        for (int i = 0; i < depth; i++) {
            out << "  ";
        }
        out << K[n.kind];
        if (n.kind == GroupNode::kLeaf) {
            out << " mat=" << n.mat;
        }
        if (n.kind == GroupNode::kAtomic) {
            out << " regime=" << n.regime << " (" << n.a << "," << n.b << ") poids=" << n.weight;
        }
        if (!n.children.empty()) {
            out << " [" << n.children.size() << "]";
        }
        out << "\n";
        for (int c : n.children) {
            walk(c, depth + 1);
        }
    };
    walk(0, 0);
}
