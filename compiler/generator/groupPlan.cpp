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
