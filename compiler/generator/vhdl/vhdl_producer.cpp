#include "vhdl_producer.hh"
#include <algorithm>
#include <functional>

int Vertex::input_counter = 0;
int Vertex::output_counter = 0;

// Retiming values for each vertex
typedef std::vector<int> Retiming;

// Constants to make the creation of input/output vertices easier to follow
const bool INPUT = true;
const bool OUTPUT = false;

/**
 * Transforms a given tree-representation of a signal to an equivalent signal DAG representation.
 */
void VhdlProducer::visit(Tree signal)
{
    int vertex_id = _vertices.size();
    int     i;
    Tree    x, y;

    // Handle recursive signals
    if (isProj(signal, &i, x)) {
        // Projections are transformed in specific input and output vertices.
        // We also need to create two edges: one to the recursive output, and another
        // to the vertex originally using the projection.
        _visit_stack.push(VisitInfo::make_recursive(vertex_id));
        // This allows us to keep track of which recursive output node to link to in the subtree.
        _virtual_io_stack.push(vertex_id + 1);

        // Creating two vertices, an output and an input, that are linked.
        addVertex(Vertex(signal, OUTPUT));
        addVertex(Vertex(signal, INPUT));

        // Then visiting the projected value.
        self(x);

        _virtual_io_stack.pop();
        _visit_stack.pop();
    }
    // Recursive symbols are bypassed in the final graph.
    else if (isRec(signal, x, y)) {
        mapself(y);
    }
    // General case
    else {
        // Initialize a new vertex
        _visit_stack.push(VisitInfo(vertex_id));
        addVertex(Vertex(signal));

        // Then visit its children.
        SignalVisitor::visit(signal);

        // Finally, we create edges from the children to the current vertex.
        _visit_stack.pop();
        if (!_visit_stack.empty()) {
            VisitInfo last_visited = _visit_stack.top();
            int register_count = _vertices[last_visited.vertex_index].is_output() ? SAMPLE_RATE : 0;
            _edges[vertex_id].push_back(Edge(last_visited.vertex_index, register_count, _vertices[vertex_id].propagation_delay));

            if (last_visited.is_recursive) {
                _visit_stack.pop();
                _edges[vertex_id].push_back(Edge(_visit_stack.top().vertex_index, 0, _vertices[vertex_id].propagation_delay));
                _visit_stack.push(last_visited);
            }
        } else {
            // We're at a root node, which means it is an output. To make retiming possible,
            // we need to create an explicit output node with `MASTER_CLOCK_FREQUENCY / SAMPLE_RATE` registers.
            int output_id = _vertices.size();
            addVertex(Vertex(signal, OUTPUT));
            _edges[vertex_id].push_back(Edge(output_id, static_cast<int>(MASTER_CLOCK_FREQUENCY / SAMPLE_RATE), _vertices[vertex_id].propagation_delay));
        }
    }
}

void VhdlProducer::optimize()
{
    retiming();
}

void VhdlProducer::generate(std::ostream& out)
{
    auto container = VhdlCodeContainer(_name, _inputs_count, _outputs_count, cyclesPerSample(), {});

    instantiate_components(container);
    map_ports(container);

    // Output to file
    out << container;
}

/**
 * CODE GENERATION
 */
void VhdlProducer::instantiate_components(VhdlCodeContainer& container)
{
    // We generate a new component for each vertex
    for (auto vertex : _vertices) {
        container.register_component(vertex);
    }
}
void VhdlProducer::map_ports(VhdlCodeContainer& container)
{
    // Iterates over all edges to map ports accordingly
    for (auto it = _vertices.begin(); it != _vertices.end(); ++it) {
        auto vertex = *it;
        auto edges = _edges[it - _vertices.begin()];
        for (auto edge : edges) {
            container.connect(vertex, _vertices[edge.target], edge.register_count);
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

        max_incoming_weight[vertex] = std::make_optional(0);

        for (auto edge : transposed_graph[vertex]) {
            int w = incoming_weight(edge.target);
            if (w > max_incoming_weight[vertex].value()) {
                max_incoming_weight[vertex].value() = w;
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
    for (size_t u = 0; u < _vertices.size(); ++u) {
        for (Edge& edge : _edges[u]) {
            int max_pipeline_stages = max_incoming_weight[edge.target].value() - _vertices[edge.target].pipeline_stages;
            edge.register_count += max_pipeline_stages - _vertices[u].pipeline_stages;
        }
    }
}

/**
 * RETIMING
 */
void VhdlProducer::retiming()
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

std::vector<int> topologicalOrdering(size_t vertices, const std::vector<std::vector<Edge>>& edges) {
    std::vector<int> stack;

    std::vector<bool> visited = std::vector<bool>(vertices, false);

    std::function<void(int)> topologicalSort;
    topologicalSort = [&](int vertex) -> void {
      visited[vertex] = true;
      for (auto adjacent : edges[vertex]) {
          if (!visited[adjacent.target]) {
              topologicalSort(adjacent.target);
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

std::vector<int> VhdlProducer::maxIncomingPropagationDelays() {
    // We first remove edges with weight > 0
    std::vector<std::vector<Edge>> zero_edges;
    for (auto vertex_edges : _edges) {
        std::vector<Edge> filtered_edges;
        for (auto edge : vertex_edges) {
            if (edge.register_count == 0) {
                filtered_edges.push_back(edge);
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

    for (auto vertex : topological_order) {
        computePropagationDelay(vertex);
    }
    return propagation_delay;
}

void VhdlProducer::computeWeightDelayInformation()
{
    // TODO: Unnecessary as long as we do not take into account propagation delay
}

std::optional<Retiming> VhdlProducer::findRetiming(int target_clock_period)
{
    // Set current retiming to 0 for all nodes
    Retiming retiming = std::vector<int>(_vertices.size(), 0);
    auto saved_edges = _edges;

    // Repeat |V| - 1 times
    for (int i = 0; i < _vertices.size(); ++i) {
        applyRetiming(retiming);
        auto propagation_delays = maxIncomingPropagationDelays();
        for (size_t j = 0; j < _vertices.size(); ++j) {
            if (propagation_delays[j] > target_clock_period) {
                retiming[j] += 1;
            }
        }
    }

    // Finally, check the minimal clock period of G_r for the final retiming
    // If said clock period is greater than `target_clock_period`, no legal retiming
    // can satisfy the target clock period
    applyRetiming(retiming);
    auto propagation_delays = maxIncomingPropagationDelays();
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
        out << "\"" << std::hex << _vertices[i].node_hash << "_" << std::dec << i << "\" [label=<" << _vertices[i].signal->node() << "<BR /><FONT POINT-SIZE=\"10\">id: " << i << ", pipeline stages: " << _vertices[i].pipeline_stages << "</FONT>>, weight=\"" << _vertices[i].pipeline_stages << "\"];" << std::endl;
        for (auto edge : _edges[i]) {
            out << "\"" << std::hex << _vertices[i].node_hash << "_"  << std::dec << i << "\" -> \"" << std::hex << _vertices[edge.target].node_hash << std::dec << "_" << edge.target << "\" [label=\"" << edge.register_count << "\",weight=\"" << edge.register_count << "\"];" << std::endl;
        }
    }

    out << "}" << std::endl;
}

void VhdlProducer::parseCustomComponents(std::istream& input)
{
    std::string id_str;
    std::string implementation_file;
    std::string pipeline_stages_str;

    while (!input.eof()) {
        std::getline(input, id_str, ' ');
        std::getline(input, implementation_file, ' ');
        std::getline(input, pipeline_stages_str, ';');

        _vertices[std::stoi(id_str)].pipeline_stages = std::stoi(pipeline_stages_str);
    }
}

int VhdlProducer::cyclesPerSample() const
{
    std::vector<int> topological_order = topologicalOrdering(_vertices.size(), _edges);
    std::vector<std::vector<Edge>> transposed_graph = transposedGraph();

    // Then find the path with maximum weight to each vertex
    std::vector<int> incoming_weight = std::vector<int>(_vertices.size(), 0);
    std::function<int(int)> computeIncomingWeight;
    computeIncomingWeight = [&](int vertex_id) -> int {
      if (incoming_weight[vertex_id] != 0) {
          return incoming_weight[vertex_id];
      }


      std::vector<Edge> incoming_edges = transposed_graph[vertex_id];
      int max_incoming = 0;
      for (auto edge : incoming_edges) {
          if (_vertices[vertex_id].is_output()) {
              continue;
          }

          int incoming = computeIncomingWeight(edge.target) + edge.register_count;
          if (incoming > max_incoming) {
              max_incoming = incoming;
          }
      }

      incoming_weight[vertex_id] = _vertices[vertex_id].pipeline_stages + max_incoming;
      return incoming_weight[vertex_id];
    };

    int max_incoming_weight= 0;
    for (auto vertex : topological_order) {
        int incoming_weight = computeIncomingWeight(vertex);
        if (incoming_weight > max_incoming_weight) {
            max_incoming_weight= incoming_weight;
        }
    }

    return max_incoming_weight;
}
