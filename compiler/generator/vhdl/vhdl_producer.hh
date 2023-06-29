#pragma once

#include "vhdl_code_container.hh"
#include "signalVisitor.hh"
#include "global.hh"
#include "sigtyperules.hh"
#include <fstream>
#include <optional>

//-------------------------VhdlProducer---------------------------
// Transforms a signal into semantically equivalent VHDL code
//----------------------------------------------------------------------
typedef std::vector<int> Retiming;
// Target sample rate in kHz
const float SAMPLE_RATE = 44.1;
// Target clock frequency in kHz
const float MASTER_CLOCK_FREQUENCY = 667000;

struct Vertex {
    static int input_counter;
    static int output_counter;
    Tree signal;
    size_t node_hash;
    int nature;

    int propagation_delay = 1;
    int pipeline_stages = 0;

    bool recursive;

    Vertex(const Tree& signal)
        : signal(signal), node_hash(signal->hashkey()), nature(getCertifiedSigType(signal)->nature()), propagation_delay(1), pipeline_stages(0), recursive(false) {};

    Vertex(const Tree& signal, bool is_input): Vertex(signal) {
        int i;
        Tree group;
        if (!isProj(signal, &i, group)) {
            i = is_input ? input_counter++ : output_counter++;
        } else {
            recursive = true;
        }
        this->signal = is_input ? sigInput(i) : sigOutput(i, signal);
    }

    bool is_output() const
    {
        return signal->node() == gGlobal->SIGOUTPUT;
    }
    bool is_input() const {
        return signal->node() == gGlobal->SIGINPUT;
    }
    bool is_recursive() const {
        return recursive;
    }

    int get_nature() const {
        return nature;
    }
};
template<>
struct std::hash<Vertex> {
    std::size_t operator()(Vertex const& v) const noexcept
    {
        return v.node_hash;
    }
};

struct Edge {
    int target;
    int register_count;

    int critical_path_weight;
    int critical_path_delay;

    Edge(int target_id, int register_count, int origin_delay): target(target_id), register_count(register_count), critical_path_weight(register_count), critical_path_delay(-origin_delay) {}
};

struct VisitInfo {
    int vertex_index;
    bool is_recursive = false;

    static VisitInfo make_recursive(int vertex_index) {
        VisitInfo info(vertex_index);
        info.is_recursive = true;
        return info;
    }

    VisitInfo(int vertex_index): vertex_index(vertex_index) {}
};

class VhdlProducer : public SignalVisitor {
    std::vector<Vertex> _vertices;
    std::vector<std::vector<Edge>> _edges;
    std::stack<VisitInfo> _visit_stack;
    std::stack<int> _virtual_io_stack;

    std::string _name;
    int _inputs_count;
    int _outputs_count;

    /** Visits the signal tree recursively to transform it into a weighted graph */
    virtual void visit(Tree signal) override;

   public:
    VhdlProducer(Tree signal, const std::string& name, int numInputs, int numOutputs)
    : _name(name), _inputs_count(numInputs), _outputs_count(numOutputs)
    {
        // Convert the input signal to a weighted circuit graph
        visitRoot(signal);

        // Parse the components file to get pipeline stages information (optional)
        if (!gGlobal->gVHDLComponentsFile.empty()) {
            std::ifstream components_file(gGlobal->gVHDLComponentsFile);
            if (!components_file) {
                std::cerr << "Failed to read file: " << gGlobal->gVHDLComponentsFile << std::endl;
                faustassert(false);
            }
            parseCustomComponents(components_file);
            components_file.close();

            // We only need to normalize the graph if we're using user-defined components
            normalize();
        }
    }

    void addVertex(Vertex v)
    {
        _vertices.push_back(v);
        _edges.push_back({});
    }

    /** Optimizes the graph using all implemented optimization passes.
     * Currently implemented passes:
     * - retiming
     */
    void optimize();

    /** Generates the VHDL code corresponding to the graph representation */
    void generate(std::ostream& out);

    /** Exports the graph as a DOT language file */
    void exportGraph(std::ostream& out) const;

    /** Applies an optimal retiming to the circuit, minimizing the feasible clock period */
    void retiming();

   protected:
    /**
     * CODE GENERATION
     */
    void instantiate_components(VhdlCodeContainer& container);
    void map_ports(VhdlCodeContainer& container);

    /**
     * NORMALIZATION
     */
    /**
     * Normalizes the circuit, adding registers to compensate the eventual difference in
     * lag induces by pipelined operators
     */
    void normalize();

    /**
     * RETIMING
     */
    /** Computes the maximal propagation delay to access each vertex */
    std::vector<int> maxIncomingPropagationDelays();

    /** Computes the W and D matrices, with
     * W[i][j] = minimum weight (i.e registers count) from i to j -> critical path
     * D[i][j] = maximum propagation delay along the critical path from i to j
     */
     void computeWeightDelayInformation();

     /** Given a clock period c, returns a retiming of the circuit with clock period
      * less than c if it exists
      */
     std::optional<Retiming> findRetiming(int target_clock_period);

     /** Applies a given retiming to the circuit, assuming said retiming is legal */
     void applyRetiming(const Retiming& retiming);

    /**
     * HELPER FUNCTIONS
     */
    /** Computes the maximum number of cycles necessary to access a given vertex.
     * It is equivalent to the longest path along the graph, weighted by registers and pipeline stages.
     * This is useful to propagate signals like ap_start in the actual circuit along a series of registers.
     */
    int cyclesFromInput(int vertex) const;

    std::optional<int> searchNode(const size_t hash) const {
        for (size_t v = 0; v < _vertices.size(); ++v) {
            if (_vertices[v].node_hash == hash) {
                return std::optional<int>(v);
            }
        }

        return std::nullopt;
    }

    std::vector<int> incomingEdges(int vertex_id, const std::vector<std::vector<Edge>>& edges) const {
        std::vector<int> incoming;
        for (size_t v = 0; v < edges.size(); ++v) {
            for (auto edge : edges[v]) {
                if (edge.target == vertex_id) {
                    incoming.push_back(v);
                }
            }
        }
        return incoming;
    }

    std::vector<std::vector<Edge>> transposedGraph() const {
        std::vector<std::vector<Edge>> transposed = std::vector(_edges.size(), std::vector<Edge>());
        for (size_t v = 0; v < _edges.size(); ++v) {
            for (auto edge : _edges[v]) {
                transposed[edge.target].push_back(Edge(v, edge.register_count, edge.critical_path_delay));
            }
        }
        return transposed;
    }


    /** Parses a user-defined config file for operators
     * Such files are structured as follows:
     * <id> <implementation file> <pipeline stages>
     *  12    flopoco_fpadd.vhdl         4
     *
     * To find the id of a component/vertex, you can first run a pass using the --vhdl-trace option
     * and find the id on the resulting vhdl_graph.dot file.
     */
    void parseCustomComponents(std::istream& input);

    /** Overrides the TreeTraversal::self method to handle recursion */
    virtual void self(Tree t)
    {
        if (fTrace) traceEnter(t);
        fIndent++;
        if (!fVisited.count(t)) {
            fVisited[t] = 0;
            visit(t);
        } else {
            int vertex_id = _vertices.size();
            auto existing_id = searchNode(t->hashkey());
            // If the signal was already seen before and our subtree goes to a recursive output,
            // we add the corresponding recursive input to this node.
            if (existing_id.has_value() && !_virtual_io_stack.empty()) {
                vertex_id = _visit_stack.top().vertex_index;
                int virtual_input_id = _virtual_io_stack.top();
                _edges[virtual_input_id].push_back(Edge(vertex_id, 0, 0));
            }
        }

        // Keep visit counter
        fVisited[t]++;
        fIndent--;
        if (fTrace) traceExit(t);
    }
};