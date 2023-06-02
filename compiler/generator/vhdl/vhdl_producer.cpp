#include "vhdl_producer.hh"
#include <algorithm>
#include <functional>


void VhdlProducer::visit(Tree signal)
{
    // If the signal was already seen before, we must be in a recursive block
    int vertex_id = _vertices.size();
    auto existing_id = searchNode(signal->hashkey());
    if (existing_id.has_value() && !_virtual_io_stack.empty()) {
        vertex_id = _visit_stack.top();
        int virtual_input_id = _virtual_io_stack.top();
        _edges[virtual_input_id].push_back(Edge(vertex_id, 0, 0));
        return;
    }

    signal->setVisited();

    int     i;
    int64_t i64;
    double  r;
    Tree    size, gen, wi, ws, tbl, ri, c, sel, x, y, z, u, v, var, le, label, ff, largs, type, name, file, sf;

    // Handle recursive signals
    if (isProj(signal, &i, x)) {
        // Projections are transformed in specific input and output nodes, and
        // need to create two edges at once
        _visit_stack.push(-vertex_id);
        _virtual_io_stack.push(vertex_id + 1);
        _vertices.push_back(Vertex(signal, true));
        _vertices.push_back(Vertex(signal, false));
        _edges.push_back({});
        _edges.push_back({});
        self(x);
        _virtual_io_stack.pop();
        _visit_stack.pop();
        return;
    } else if (isRec(signal, var, le)) {
        // Recursive symbols are bypassed in the final graph
        mapself(le);
        return;
    }

    // Initialize a new vertex
    _visit_stack.push(vertex_id);
    _vertices.push_back(Vertex(signal));
    _edges.push_back({});

    // Then deal with propagation and edge creation

    if (getUserData(signal)) {
        for (Tree b : signal->branches()) {
            self(b);
        }
    } else if (isSigInt(signal, &i)) {
    } else if (isSigInt64(signal, &i64)) {
    } else if (isSigReal(signal, &r)) {
    } else if (isSigWaveform(signal)) {
    } else if (isSigInput(signal, &i)) {
    } else if (isSigOutput(signal, &i, x)) {
        self(x);
    } else if (isSigDelay1(signal, x)) {
        self(x);
    } else if (isSigDelay(signal, x, y)) {
        self(x);
        self(y);
    } else if (isSigPrefix(signal, x, y)) {
        self(x);
        self(y);
    } else if (isSigBinOp(signal, &i, x, y)) {
        self(x);
        self(y);
    }

    // Foreign functions
    else if (isSigFFun(signal, ff, largs)) {
        mapself(largs);
    } else if (isSigFConst(signal, type, name, file)) {
    } else if (isSigFVar(signal, type, name, file)) {
    }

    // Tables
    else if (isSigWRTbl(signal, size, gen, wi, ws)) {
        self(size);
        self(gen);
        if (wi != gGlobal->nil) {
            // rwtable
            self(wi);
            self(ws);
        }
    } else if (isSigRDTbl(signal, tbl, ri)) {
        self(tbl);
        self(ri);
    }

    // Doc
    else if (isSigDocConstantTbl(signal, x, y)) {
        self(x);
        self(y);
    } else if (isSigDocWriteTbl(signal, x, y, u, v)) {
        self(x);
        self(y);
        self(u);
        self(v);
    } else if (isSigDocAccessTbl(signal, x, y)) {
        self(x);
        self(y);
    }

    // Select2 (and Select3 expressed with Select2)
    else if (isSigSelect2(signal, sel, x, y)) {
        self(sel);
        self(x);
        self(y);
    }

    // Table sigGen
    else if (isSigGen(signal, x)) {
        if (fVisitGen) {
            self(x);
        } else {
        }
    }

    // Int, Bit and Float Cast
    else if (isSigIntCast(signal, x)) {
        self(x);
    } else if (isSigBitCast(signal, x)) {
        self(x);
    } else if (isSigFloatCast(signal, x)) {
        self(x);
    }

    // UI
    else if (isSigButton(signal, label)) {
    } else if (isSigCheckbox(signal, label)) {
    } else if (isSigVSlider(signal, label, c, x, y, z)) {
        self(c), self(x), self(y), self(z);
    } else if (isSigHSlider(signal, label, c, x, y, z)) {
        self(c), self(x), self(y), self(z);
    } else if (isSigNumEntry(signal, label, c, x, y, z)) {
        self(c), self(x), self(y), self(z);
    } else if (isSigVBargraph(signal, label, x, y, z)) {
        self(x), self(y), self(z);
    } else if (isSigHBargraph(signal, label, x, y, z)) {
        self(x), self(y), self(z);
    }

    // Soundfile length, rate, buffer
    else if (isSigSoundfile(signal, label)) {
    } else if (isSigSoundfileLength(signal, sf, x)) {
        self(sf), self(x);
    } else if (isSigSoundfileRate(signal, sf, x)) {
        self(sf), self(x);
    } else if (isSigSoundfileBuffer(signal, sf, x, y, z)) {
        self(sf), self(x), self(y), self(z);
    }

    // Attach, Enable, Control
    else if (isSigAttach(signal, x, y)) {
        self(x), self(y);
    } else if (isSigEnable(signal, x, y)) {
        self(x), self(y);
    } else if (isSigControl(signal, x, y)) {
        self(x), self(y);
    }

    else if (isNil(signal)) {
        // now nil can appear in table write instructions
    } else {
        //cerr << __FILE__ << ":" << __LINE__ << " ASSERT : unrecognized signal : " << *sig << endl;
    }


    _visit_stack.pop();
    if (!_visit_stack.empty()) {
        auto last_visited = _visit_stack.top();
        _edges[vertex_id].push_back(Edge(abs(last_visited), 0, _vertices[vertex_id].propagation_delay));
        // Recursive virtual nodes
        if (last_visited < 0) {
            _visit_stack.pop();
            _edges[vertex_id].push_back(Edge(_visit_stack.top(), 0, _vertices[vertex_id].propagation_delay));
            _visit_stack.push(last_visited);
        }
    }
}


void VhdlProducer::optimize()
{

}

void VhdlProducer::generate()
{
    // TODO
}

/**
 * RETIMING
 */

std::vector<int> topologicalOrdering(int vertices, const std::vector<std::vector<int>>& edges) {
    std::vector<int> stack;

    std::vector<bool> visited = std::vector<bool>(vertices, false);

    std::function<void(int)> topologicalSort;
    topologicalSort = [&](int vertex) -> void {
      visited[vertex] = true;
      for (auto adjacent : edges[vertex]) {
          if (!visited[adjacent]) {
              topologicalSort(adjacent);
          }
      }

      stack.push_back(vertex);
    };

    for (int vertex = 0; vertex < vertices; ++vertex) {
        if (!visited[vertex]) {
            topologicalSort(vertex);
        }
    }

    return stack;
}

int VhdlProducer::minFeasibleClockPeriod() {
    // We first remove edges with weight > 0
    std::vector<std::vector<int>> zero_edges;
    for (auto vertex_edges : _edges) {
        std::vector<int> filtered_edges;
        for (auto edge : vertex_edges) {
            if (edge.register_count == 0) {
                filtered_edges.push_back(edge.target);
            }
        }

        zero_edges.push_back(filtered_edges);
    }

    // We then sort the remaining ones topologically, and search for the
    std::vector<int> topological_order = topologicalOrdering(_vertices.size(), zero_edges);

    // Then find the maximum propagation delay for a critical path
    std::vector<int> propagation_delay = std::vector<int>(_vertices.size(), 0);
    std::function<int(int)> computePropagationDelay;
    computePropagationDelay = [&](int vertex_id) -> int {
      if (propagation_delay[vertex_id] != 0) {
          return propagation_delay[vertex_id];
      }

      std::vector<int> incoming_edges = incomingEdges(vertex_id, zero_edges);
      int max_incoming = 0;
      for (auto incoming_vertex : incoming_edges) {
          int delay = computePropagationDelay(incoming_vertex);
          if (delay > max_incoming) {
              max_incoming = delay;
          }
      }

      propagation_delay[vertex_id] = _vertices[vertex_id].propagation_delay + max_incoming;
      return propagation_delay[vertex_id];
    };

    int max_propagation_delay = 0;
    for (auto vertex : topological_order) {
        int propagation_delay = computePropagationDelay(vertex);
        if (propagation_delay > max_propagation_delay) {
            max_propagation_delay = propagation_delay;
        }
    }

    return max_propagation_delay;
}

void VhdlProducer::computeWeightDelayInformation()
{

}
