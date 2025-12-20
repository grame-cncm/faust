#include <map>
#include <set>
#include <vector>

#include "signals.hh"

/**
 * @brief Clock Environment Inference Engine
 *
 * This class implements a fixed-point algorithm to infer the clock environment
 * for each signal in a signal list. The clock environment represents the nested
 * clock domain hierarchy in which a signal is computed.
 *
 * The algorithm:
 * 1. Collects all recursive groups in the signal graph
 * 2. Computes a fixed-point hypothesis H : Group → ClkEnv
 * 3. Infers the clock environment for each signal using H
 * 4. Annotates each signal with its computed clock environment
 *
 * See ClockEnvironmentInferenceRulesV2.md for the formal inference rules.
 */
class ClkEnvInference {
   private:
    std::map<Tree, Tree> mapping;  ///< Maps signals to their inferred clock environments

   public:
    /**
     * @brief Infer and annotate clock environments for all signals in the list
     *
     * This method computes the clock environment for each signal in sigList using
     * a fixed-point algorithm, then annotates each signal Tree node with the
     * CLKENVPROPERTY property containing its clock environment.
     *
     * @param sigList List of signals to process (Tree list structure)
     */
    void annotate(Tree sigList);

    /**
     * @brief Get the clock environment property of a signal
     *
     * Retrieves the clock environment that was previously computed and annotated
     * on the signal by ClkEnvInference::annotate(). This is a static method that
     * can be called without a ClkEnvInference instance.
     *
     * @param sig The signal whose clock environment to retrieve
     * @return Tree The clock environment of the signal
     * @throws faustassert Triggers an assertion if the signal has no associated clock environment
     */
    static Tree getClkEnv(Tree sig);

    /**
     * @brief Test that each OD/US/DS signal has a unique clock environment
     *
     * This test function verifies the invariant that different OD/US/DS signals
     * should never share the same clock environment. If duplicates are found,
     * it indicates a bug in clock environment creation (likely due to de Bruijn
     * notation issues).
     *
     * @param hg The hierarchical graph containing the subgraphs to test
     * @return true if all clkEnv are unique, false if duplicates are detected
     */
    static bool testClkEnvUniqueness(const struct Hgraph& hg);
};

bool isAncestorClkEnv(Tree c1, Tree c2);
