#pragma once

#include "vhdl_code_container.hh"
#include "signalVisitor.hh"
#include "global.hh"
#include <fstream>
#include <optional>

//-------------------------VhdlProducer---------------------------
// Transforms a signal into semantically equivalent VHDL code
//----------------------------------------------------------------------
typedef std::vector<int> Retiming;
const int SAMPLE_RATE = 2400;

struct Vertex {
    static int input_counter;
    static int output_counter;
    Node node;
    size_t node_hash;

    int propagation_delay = 1;
    int pipeline_stages = 0;

    Vertex(const Tree& signal)
        : node(signal->node()), node_hash(signal->hashkey()), propagation_delay(1), pipeline_stages(0) {};

    Vertex(const Tree& signal, bool is_input): node(signal->node()), node_hash(signal->hashkey()), propagation_delay(1) {
        int i;
        Tree group;
        if (!isProj(signal, &i, group)) {
            i = is_input ? input_counter++ : output_counter++;
        }
        node = is_input ? sigInput(i)->node() : sigOutput(i, signal)->node();
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
    Tree _signal;
    std::vector<Vertex> _vertices;
    std::vector<std::vector<Edge>> _edges;
    std::stack<VisitInfo> _visit_stack;
    std::stack<int> _virtual_io_stack;

    VhdlCodeContainer _code_container;

    /** Visits the signal tree recursively to transform it into a weighted graph */
    virtual void visit(Tree signal) override;

   public:
    VhdlProducer(Tree signal, const std::string& name, int numInputs, int numOutputs, std::ostream& out)
    : _signal(signal), _code_container(out)
    {
        // Step 1: Convert the input signal to a weighted circuit graph
        visitRoot(_signal);
        std::cout << "transformation to graph: " << std::endl;
        for (size_t i = 0; i < _vertices.size(); ++i) {
            std::cout << i << ": " << _vertices[i].node << " (0x" << std::hex << _vertices[i].node_hash << std::dec << ')' << std::endl;

            for (auto e : _edges[i]) {
                std::cout << "\t" << e.target << ", " << e.register_count << " registers" << std::endl;
            }
        }
        std::cout <<  std::endl << "=============================" << std::endl << std::endl;

        // Step 2: Optimize the graph
        optimize();
        std::cout << "after optimization: " << std::endl;
        for (size_t i = 0; i < _vertices.size(); ++i) {
            std::cout << i << ": " << _vertices[i].node << " (0x" << std::hex << _vertices[i].node_hash << std::dec << ')' << std::endl;

            for (auto e : _edges[i]) {
                std::cout << "\t" << e.target << ", " << e.register_count << " registers" << std::endl;
            }
        }

        // Step 2.5: Export the graph using the DOT language (optional)
        if (gGlobal->gVHDLTrace) {
            std::ofstream dot_output;
            dot_output.open("vhdl_graph.dot");
            exportGraph(dot_output);
            dot_output.close();
        }

        // TODO Step 3: Generate VHDL code structure from the resulting graph
        // generate();

        // Step 4: Output the generated VHDL to a file
        //out << _code_container;
    }

   protected:
    /** Optimizes the graph using implemented optimization passes
     * Currently implemented passes:
     * - retiming
     */
    void optimize();


    /** Generates the VHDL code corresponding to the graph representation */
    void generate();

    /**
     * CODE GENERATION
     */
    void declare_dependencies();
    void generate_entities();
    void instantiate_components();
    void map_ports();

    /** Generates a generic VHDL binary operator for the given type */
    void generic_binop_entity(int op, int kind);

    /** Generates an entity that can be polled for a wave signal */
    void generate_waveform_entity();

    /** Generates a delay entity */
    void generate_delay_entity();

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
    /** Retimes the circuit, minimizing the feasible clock period */
    void retime();

    /** Computes the minimal feasible clock period of the current circuit */
    std::vector<int> minFeasibleClockPeriod();

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

    /** HELPER FUNCTIONS */
    std::optional<int> searchNode(const size_t hash) const {
        for (size_t v = 0; v < _vertices.size(); ++v) {
            if (_vertices[v].node_hash == hash) {
                return std::optional<int>(v);
            }
        }

        return std::nullopt;
    }

    std::vector<int> incomingEdges(int vertex_id, const std::vector<std::vector<int>>& edges) const {
        std::vector<int> incoming;
        for (size_t v = 0; v < edges.size(); ++v) {
            for (auto edge : edges[v]) {
                if (edge == vertex_id) {
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

    /** Checks whether reals should encoded using fixed or floating point arithmetic */
    bool usingFloatEncoding() const { return gGlobal->gVHDLFloatEncoding; }

    /** Exports the graph as a DOT language file */
    void exportGraph(std::ostream& out) const;

    void self(Tree t)
    {
        if (fTrace) traceEnter(t);
        fIndent++;
        if (!fVisited.count(t)) {
            fVisited[t] = 0;
        }
        visit(t);
        // Keep visit counter
        fVisited[t]++;
        fIndent--;
        if (fTrace) traceExit(t);
    }
};