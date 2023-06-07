#pragma once

#include "signalVisitor.hh"
#include "vhdl_code_container.hh"
#include "global.hh"
#include <optional>

//-------------------------VhdlProducer---------------------------
// Transforms a signal into semantically equivalent VHDL code
//----------------------------------------------------------------------
typedef std::vector<int> Retiming;
const int SAMPLE_RATE = 24000;

class VhdlProducer : public SignalVisitor {
   private:
    struct Vertex {
        static int input_counter;
        static int output_counter;
        Node node;
        size_t node_hash;

        int propagation_delay = 1;

        Vertex(const Tree& signal)
            : node(signal->node()), node_hash(signal->hashkey()), propagation_delay(1) {};

        Vertex(const Tree& signal, bool is_input): node(signal->node()), node_hash(signal->hashkey()), propagation_delay(1) {
            int i;
            Tree group;
            if (!isProj(signal, &i, group)) {
                i = is_input ? input_counter++ : output_counter++;
            }
            node = is_input ? sigInput(i)->node() : sigOutput(i, signal)->node();
        }
    };

    struct Edge {
        int target;
        int register_count;

        int critical_path_weight;
        int critical_path_delay;

        Edge(int target_id, int register_count, int origin_delay): target(target_id), register_count(register_count), critical_path_weight(register_count), critical_path_delay(-origin_delay) {}
    };

    Tree _signal;
    std::vector<Vertex> _vertices;
    std::vector<std::vector<Edge>> _edges;
    std::stack<int> _visit_stack;
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
        for (int i = 0; i < _vertices.size(); ++i) {
            std::cout << i << ": " << _vertices[i].node << " (" << _vertices[i].node_hash << ')' << std::endl;

            for (auto e : _edges[i]) {
                std::cout << "\t" << e.target << ", " << e.register_count << " registers" << std::endl;
            }
        }
        std::cout <<  std::endl << "=============================" << std::endl << std::endl;

        // Step 2: Optimize the graph
        optimize();
        std::cout << "after optimization: " << std::endl;
        for (int i = 0; i < _vertices.size(); ++i) {
            std::cout << i << ": " << _vertices[i].node << " (" << _vertices[i].node_hash << ')' << std::endl;

            for (auto e : _edges[i]) {
                std::cout << "\t" << e.target << ", " << e.register_count << " registers" << std::endl;
            }
        }

        // Step 3: Generate VHDL code structure from the resulting graph
        generate();
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
        for (int v = 0; v < _vertices.size(); ++v) {
            if (_vertices[v].node_hash == hash) {
                return std::optional<int>(v);
            }
        }

        return std::nullopt;
    }

    std::vector<int> incomingEdges(int vertex_id, const std::vector<std::vector<int>>& edges) const {
        std::vector<int> incoming;
        for (int v = 0; v < edges.size(); ++v) {
            for (auto edge : edges[v]) {
                if (edge == vertex_id) {
                    incoming.push_back(v);
                }
            }
        }
        return incoming;
    }

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