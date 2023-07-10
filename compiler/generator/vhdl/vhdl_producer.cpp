#include "vhdl_producer.hh"
#include <algorithm>
#include <functional>

int Vertex::input_counter = 0;
int Vertex::output_counter = 0;

// Retiming values for each vertex
typedef std::vector<int> Retiming;

void VhdlProducer::visit(Tree signal)
{
    int vertex_id = _vertices.size();
    auto existing_id = searchNode(signal->hashkey());
    // If the signal was already seen before and our subtree goes to a recursive output,
    // we add the corresponding recursive input to this node.
    if (existing_id.has_value() && !_virtual_io_stack.empty()) {
        vertex_id = _visit_stack.top().vertex_index;
        int virtual_input_id = _virtual_io_stack.top();
        _edges[virtual_input_id].push_back(Edge(vertex_id, 0, 0));
        return;
    }

    int     i;
    int64_t i64;
    double  r;
    Tree    size, gen, wi, ws, tbl, ri, c, sel, x, y, z, u, v, var, le, label, ff, largs, type, name, file, sf;

    // Handle recursive signals
    if (isProj(signal, &i, x)) {
        // Projections are transformed in specific input and output vertices.
        // We also need to create two edges: one to the recursive output, and another
        // to the vertex originally using the projection.
        _visit_stack.push(VisitInfo::make_recursive(vertex_id));
        // This allows us to keep track of which recursive output node to link to in the subtree.
        _virtual_io_stack.push(vertex_id + 1);

        // Creating two vertices, an output and an input, that are linked.
        _vertices.push_back(Vertex(signal, false));
        _vertices.push_back(Vertex(signal, true));
        _edges.push_back({});
        _edges.push_back({});

        // Then visiting the projected value.
        self(x);

        _virtual_io_stack.pop();
        _visit_stack.pop();
        return;
    } else if (isRec(signal, var, le)) {
        // Recursive symbols are bypassed in the final graph, so we return early.
        mapself(le);
        return;
    }

    // Initialize a new vertex
    _visit_stack.push(VisitInfo(vertex_id));
    _vertices.push_back(Vertex(signal));
    _edges.push_back({});

    // Then visit its children.
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
    // TODO: ignore those
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
    // TODO: Later
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
    // TODO: might want to ignore ?
    else if (isSigSoundfile(signal, label)) {
    } else if (isSigSoundfileLength(signal, sf, x)) {
        self(sf), self(x);
    } else if (isSigSoundfileRate(signal, sf, x)) {
        self(sf), self(x);
    } else if (isSigSoundfileBuffer(signal, sf, x, y, z)) {
        self(sf), self(x), self(y), self(z);
    }

    // Attach, Enable, Control
    // TODO: Later
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
        std::cerr << __FILE__ << ":" << __LINE__ << " ASSERT : unrecognized signal : " << *signal << std::endl;
    }

    // Finally, we create edges from the children to the current vertex.
    _visit_stack.pop();
    if (!_visit_stack.empty()) {
        VisitInfo last_visited = _visit_stack.top();
        int register_count = _vertices[last_visited.vertex_index].node.getSym() == gGlobal->SIGOUTPUT ? SAMPLE_RATE : 0;
        _edges[vertex_id].push_back(Edge(last_visited.vertex_index, register_count, _vertices[vertex_id].propagation_delay));

        if (last_visited.is_recursive) {
            _visit_stack.pop();
            _edges[vertex_id].push_back(Edge(_visit_stack.top().vertex_index, 0, _vertices[vertex_id].propagation_delay));
            _visit_stack.push(last_visited);
        }
    } else {
        // We're at a root node, which means it is an output. To make retiming possible,
        // we need to create an explicit output node with `SAMPLE_RATE` registers.
        int output_id = _vertices.size();
        _vertices.push_back(Vertex(signal, false));
        _edges.push_back({});
        _edges[vertex_id].push_back(Edge(output_id, SAMPLE_RATE, _vertices[vertex_id].propagation_delay));
    }
}


void VhdlProducer::optimize()
{
    // Normalization needs to be done before retiming to really be efficient
    normalize();
    retime();
}

void VhdlProducer::generate()
{
    declare_dependencies();
    instantiate_components();
    map_ports();

    // Output to file
}

/**
 * CODE GENERATION
 */
void VhdlProducer::declare_dependencies()
{
    *_code_container.dependencies()
        << "library ieee;" << std::endl
        << "use ieee.std_logic_1164.all;" << std::endl
        << "use ieee.numeric_std.all;" << std::endl
        << "use ieee.std_logic_arith.all;" << std::endl
        << "use ieee.std_logic_signed.all;" << std::endl
        << "use work.fixed_float_types.all;" << std::endl;

    // Include the right package for real numbers encoding
    if (usingFloatEncoding()) {
        *_code_container.dependencies() << "use work.float_pkg.all;" << std::endl;
    } else {
        *_code_container.dependencies() << "use work.fixed_pkg.all;" << std::endl;
    }
}
void VhdlProducer::generate_entities()
{

}
void VhdlProducer::instantiate_components()
{

}
void VhdlProducer::map_ports()
{
    for (auto it = _vertices.begin(); it != _vertices.end(); ++it) {
        auto vertex = *it;
        auto edges = _edges[it - _vertices.begin()];
        for (auto edge : edges) {
            // TODO:
            // <target_name_id>: <generic_target_entity_name>
            // port map (
            //  clk => clock,
            //  rst => ap_rst_n,
            //  <target_name_id_in> => <source_name_id_out>,
            //  ...
            _code_container.connect(vertex, _vertices[edge.target], edge.register_count);
        }
    }
}

/**
 * NORMALIZATION
 */
void VhdlProducer::normalize()
{
    // For each vertex `v`, we find the weight `w` of the longest incoming path.
    // The notion of weight is defined here as the sum of pipeline stages of vertices along the path.
    std::vector<std::optional<int>> max_incoming_weight = std::vector(_vertices.size(), std::optional<int>());
    auto transposed_graph = transposedGraph();

    std::function<int(int)> incoming_weight;
    incoming_weight = [&](int vertex) {
        if (max_incoming_weight[vertex].has_value()) {
            return max_incoming_weight[vertex].value();
        }

        for (auto edge : transposed_graph[vertex]) {
            int w = incoming_weight(edge.target);
            if (!max_incoming_weight[vertex].has_value() || w > max_incoming_weight[vertex].value()) {
                max_incoming_weight[vertex] = std::make_optional(w);
            }
        }
        max_incoming_weight[vertex] = std::make_optional(_vertices[vertex].pipeline_stages + max_incoming_weight[vertex].value_or(0));
        return max_incoming_weight[vertex].value();
    };

    for (int i = 0; i < _vertices.size(); ++i) {
        incoming_weight(i);
    }

    // Afterwards, for each vertex `u` such that there is an edge `u -> v`, we add `w - l(u)` registers
    // to `u -> v` to compensate for the lag.
    for (int u = 0; u < _vertices.size(); ++u) {
        int pipeline_stages = _vertices[u].pipeline_stages;
        for (auto edge : _edges[u]) {
            edge.register_count += max_incoming_weight[edge.target].value() - pipeline_stages;
        }
    }
}

/**
 * RETIMING
 */
void VhdlProducer::retime()
{
    // TODO: First compute W and D matrices to determine max_d
    // Note that this is not necessary as of now, since all operators have an equal
    // propagation delay. It will be necessary however if the notion of delay is ever used
    // in the future.
    int max_d = 2400;

    // Use binary search to find a legal retiming of minimal clock period
    int l = 0, r = max_d, m;
    Retiming best_retiming = std::vector<int>(_vertices.size(), 0);
    while (l <= r) {
        m = l + (r - l) / 2;

        // If a retiming of clock period <= m is possible, we keep searching in the lower
        // half if any lower value of m is also feasible
        // Otherwise, we search for the other half
        auto retiming = findRetiming(m);
        if (retiming.has_value()) {
            best_retiming = retiming.value();
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    applyRetiming(best_retiming);
}

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

std::vector<int> VhdlProducer::minFeasibleClockPeriod() {
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

    return propagation_delay;
}

void VhdlProducer::computeWeightDelayInformation()
{
    // This is done through the use of the Floyd-Warshall algorithm
    // for all-pairs shortest path
}

std::optional<Retiming> VhdlProducer::findRetiming(int target_clock_period)
{
    // Set current retime to 0 for all nodes
    Retiming retiming = std::vector<int>(_vertices.size(), 0);
    auto saved_edges = _edges;

    // Repeat |V| - 1 times
    for (int i = 0; i < _vertices.size(); ++i) {
        applyRetiming(retiming);
        auto propagation_delays = minFeasibleClockPeriod();
        for (int j = 0; j < _vertices.size(); ++j) {
            if (propagation_delays[j] > target_clock_period) {
                retiming[j] += 1;
            }
        }
    }

    // Finally, check the minimal clock period of G_r for the final retiming
    // If said clock period is greater than `target_clock_period`, no legal retiming
    // can satisfy the target clock period
    applyRetiming(retiming);
    auto propagation_delays = minFeasibleClockPeriod();
    _edges = saved_edges;

    int max_propagation_delay = *std::max_element(std::begin(propagation_delays), std::end(propagation_delays));
    if (max_propagation_delay > target_clock_period) {
        return std::nullopt;
    } else {
        return std::make_optional(retiming);
    }
}

void VhdlProducer::applyRetiming(const Retiming& retiming)
{
    for (int i = 0; i < _vertices.size(); ++i) {
        for (int j = 0; j < _edges[i].size(); ++j) {
            _edges[i][j].register_count += retiming[_edges[i][j].target] - retiming[i];
        }
    }
}

void VhdlProducer::exportGraph(std::ostream& out) const
{
    out << "digraph {" << std::endl;
    for (size_t i = 0; i < _vertices.size(); ++i) {
        out << "\"" << std::hex << _vertices[i].node_hash << "_" << std::dec << i << "\" [label=<" << _vertices[i].node << "<BR /><FONT POINT-SIZE=\"10\">hash: 0x" << std::hex << _vertices[i].node_hash << std::dec << ", pipeline stages: " << _vertices[i].pipeline_stages << "</FONT>>, weight=\"" << _vertices[i].pipeline_stages << "\"];" << std::endl;
        for (auto edge : _edges[i]) {
            out << "\"" << std::hex << _vertices[i].node_hash << "_"  << std::dec << i << "\" -> \"" << std::hex << _vertices[edge.target].node_hash << std::dec << "_" << edge.target << "\" [label=\"" << edge.register_count << "\",weight=\"" << edge.register_count << "\"];" << std::endl;
        }
    }

    out << "}" << std::endl;
}
