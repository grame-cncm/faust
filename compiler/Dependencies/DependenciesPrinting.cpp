#include "DependenciesPrinting.hh"
#include "DependenciesUtils.hh"
#include "binop.hh"
#include "occurrences.hh"
#include "ppsig.hh"
#include "signals.hh"

/**
 * @brief Prints the clock of a signal to the output stream.
 *
 * If the clock is nil, it prints "sample". Otherwise, it prints the clock itself.
 *
 * @param os The output stream to print to.
 * @param clk The clock to print.
 */
void printClock(std::ostream& os, Tree clk)
{
    if (clk == gGlobal->nil) {
        os << "sample";
    } else {
        os << clk;
    }
}

/**
 * @brief Prints the hierarchical schedule of signals.
 *
 * This function prints the schedule of signals, including constant and control signals,
 * and audio signals. It uses a map of step numbers to reference signals in the schedule.
 *
 * @param hs The hierarchical schedule to print.
 */
void printHsched(const Hsched& hs)
{
    std::map<Tree, int> stepNumbers = numberSchedule(hs);
    std::cerr << "Hierarchical schedule of signals" << std::endl;
    std::cerr << "Constant and Control Signals:" << std::endl;
    recPrinting(std::cerr, hs.sigsched, stepNumbers, hs.controls, 1);
    std::cerr << "Audio Signals" << std::endl;
    recPrinting(std::cerr, hs.sigsched, stepNumbers, hs.sigsched.at(hs.outSigList), 1);
}

/**
 * @brief Prints the hierarchical schedule of signals with max delay information.
 *
 * This function prints the schedule of signals, including constant and control signals,
 * and audio signals, with maximum delay information for each signal.
 *
 * @param hs The hierarchical schedule to print.
 * @param maxDelays Map of signals to their maximum delays.
 */
void printHschedWithDelays(const Hsched& hs, OccMarkup* OM)
{
    std::map<Tree, int> stepNumbers = numberSchedule(hs);
    std::cerr << "Hierarchical schedule of signals" << std::endl;
    std::cerr << "Constant and Control Signals:" << std::endl;
    recPrintingWithDelays(std::cerr, hs.sigsched, stepNumbers, OM, hs.controls, 1);
    std::cerr << "Audio Signals" << std::endl;
    recPrintingWithDelays(std::cerr, hs.sigsched, stepNumbers, OM, hs.sigsched.at(hs.outSigList),
                          1);
}

/**
 * @brief Recursively prints the schedule of signals with indentation and delay information.
 *
 * @param os The output stream to print to.
 * @param sigSchedules A map of signals to their schedules.
 * @param stepNumbers A map of signals to their step numbers.
 * @param maxDelays Map of signals to their maximum delays.
 * @param schedule The schedule to print.
 * @param indent The indentation level.
 */
void recPrintingWithDelays(std::ostream& os, const std::map<Tree, schedule<Tree>>& sigSchedules,
                           const std::map<Tree, int>& stepNumbers, OccMarkup* OM,
                           const schedule<Tree>& schedule, int indent)
{
    for (Tree sig : schedule.elements()) {
        if (Tree clk; needSubGraph(sig, clk)) {
            // if a signal has a subschedule we first number its dependencies
            recPrintingWithDelays(os, sigSchedules, stepNumbers, OM, sigSchedules.at(sig),
                                  indent + 1);
        }
        for (int i = 0; i < indent; i++) {
            os << '\t';
        }
        os << "%" << stepNumbers.at(sig) << " : ";
        printSigWithStepRefs(os, sig, stepNumbers, OM);
        os << std::endl;
    }
}

/**
 * @brief Recursively prints the schedule of signals with indentation.
 *
 * This function recursively prints the schedule of signals, including subschedules, with
 * proper indentation for readability. It uses a map of step numbers to reference signals.
 *
 * @param os The output stream to print to.
 * @param sigSchedules A map of signals to their schedules.
 * @param stepNumbers A map of signals to their step numbers.
 * @param schedule The schedule to print.
 * @param indent The indentation level.
 */
void recPrinting(std::ostream& os, const std::map<Tree, schedule<Tree>>& sigSchedules,
                 const std::map<Tree, int>& stepNumbers, const schedule<Tree>& schedule, int indent)
{
    for (Tree sig : schedule.elements()) {
        if (Tree clk; needSubGraph(sig, clk)) {
            // if a signal has a subschedule we first number its dependencies
            recPrinting(os, sigSchedules, stepNumbers, sigSchedules.at(sig), indent + 1);
        }
        for (int i = 0; i < indent; i++) {
            os << '\t';
        }
        os << "%" << stepNumbers.at(sig) << " : ";
        printSigWithStepRefs(os, sig, stepNumbers, nullptr);
        os << std::endl;
    }
}

/**
 * @brief Prints a signal with step references to the output stream.
 *
 * This function prints a signal to the output stream, including its node and branches.
 * It handles special cases for input signals, projections, IIR filters, and sigclocked signals.
 * It uses a map of step numbers to reference signals in the output.
 *
 * @param os The output stream to print to.
 * @param sig The signal to print.
 * @param stepNumbers A map of signals to their step numbers.
 */
void printSigWithStepRefs(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers,
                          OccMarkup* OM)
{
    Tree W, var, body;
    Type ty = getCertifiedSigType(sig);

    // Special case: input signal (e.g., Input(0))
    if (int i; isSigInput(sig, &i)) {
        os << "Input(" << i << ")" << "\t// " << *ty;
        return;
    }

    // Special case: projection from a group of recursive definitions
    if (int i; isProj(sig, &i, W)) {
        faustassert(isRec(W, var, body));
        os << "letrec " << *var << '(' << i << ") = ";
        printStepRefs(os, nth(body, i), stepNumbers);
        os << "\t// " << *ty;
        return;
    }

    // Handle IIR
    if (tvec v; isSigIIR(sig, v)) {
        os << sig->node();
        char sep = '(';
        for (unsigned int i = 0; i < v.size(); i++) {
            os << sep;
            printStepRefs(os, v[i], stepNumbers);
            sep = ',';
        }
        os << ") \t// " << *ty;
        return;
    }

    // special case: sigclocked signals, don't print the content of the clock environment
    if (Tree clk, s; isSigClocked(sig, clk, s)) {
        os << "sigClocked(";
        printClock(os, clk);
        os << ',';
        printStepRefs(os, s, stepNumbers);
        os << ')' << "\t// " << *ty;

        // Add max delay information if available
        if (OM) {
            if (Occurrences* occ = OM->retrieve(sig)) {
                os << " max delay: " << occ->getMaxDelay();
            } else {
                os << " NO OCC !";
            }
        }

        return;
    }

    // special case for OD/US/DS signals
    if (Tree clockedClk; needSubGraph(sig, clockedClk)) {
        Tree clkenv, clk;
        faustassert(isSigClocked(clockedClk, clkenv, clk));
        os << sig->node() << '(' << clkenv << ',';
        printStepRefs(os, clk, stepNumbers);
        // Only print branches after nil marker
        bool afternil = false;
        for (Tree s : sig->branches()) {
            if (afternil) {
                os << ',';
                printStepRefs(os, s, stepNumbers);
            } else if (s == gGlobal->nil) {
                afternil = true;
            }
        }
        os << ')';
        return;
    }

    // general case
    os << sig->node();
    tvec B = sig->branches();

    if (B.size() > 0) {
        char sep = '(';
        for (Tree s : B) {
            os << sep;
            printStepRefs(os, s, stepNumbers);
            sep = ',';
        }
        os << ')';
    }
    os << "\t// " << *ty;

    // Add max delay information if available
    if (OM) {
        if (Occurrences* occ = OM->retrieve(sig)) {
            os << " max delay: " << occ->getMaxDelay();
        } else {
            os << " NO OCC !";
        }
    }
    os << std::endl;
}

/**
 * @brief Prints a step reference to the output stream.
 *
 * If the signal has a step number, it prints the step number with a '%' prefix.
 * Otherwise, it prints the signal itself.
 *
 * @param os The output stream to print to.
 * @param sig The signal to print.
 * @param stepNumbers A map of signals to their step numbers.
 */
void printStepRefs(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers)
{
    if (stepNumbers.find(sig) != stepNumbers.end()) {
        os << '%' << stepNumbers.at(sig);
    } else {
        os << *sig;
    }
}

/**
 * @brief Generates a map of signals to their step numbers for scheduling.
 *
 * This function generates a map of signals to their step numbers, which is used for
 * scheduling the signals. It first numbers the control and constant signals, and then
 * recursively numbers the remaining signals based on their dependencies.
 *
 * @param hs The hierarchical schedule to number.
 * @return A map of signals to their step numbers.
 */
std::map<Tree, int> numberSchedule(const Hsched& hs)
{
    int                 step = 0;
    std::map<Tree, int> signumbers;

    // Control and constant signals has to be numbered first
    for (Tree sig : hs.controls.elements()) {
        signumbers[sig] = step++;
    }
    step = recNumbering(hs.sigsched, signumbers, hs.sigsched.at(hs.outSigList), step);

    return signumbers;
}

/**
 * @brief Recursively numbers the signals in a schedule.
 *
 * This function recursively numbers the signals in a schedule, including subschedules, based
 * on their dependencies. It uses a map of signals to their step numbers to keep track of
 * the numbering.
 *
 * @param sigSchedules A map of signals to their schedules.
 * @param stepNumbers A map of signals to their step numbers.
 * @param schedule The schedule to number.
 * @param step The starting step number.
 * @return The updated step number after numbering the signals in the schedule.
 */
int recNumbering(const std::map<Tree, schedule<Tree>>& sigSchedules,
                 std::map<Tree, int>& stepNumbers, const schedule<Tree>& schedule, int step)
{
    for (Tree sig : schedule.elements()) {
        if (Tree clk; needSubGraph(sig, clk)) {
            // if a signal has a subschedule we first number its dependencies
            step = recNumbering(sigSchedules, stepNumbers, sigSchedules.at(sig), step);
        }
        if (stepNumbers.find(sig) != stepNumbers.end()) {
            std::cerr << "WARNING: signal " << sig << " as already number " << stepNumbers.at(sig)
                      << " while we want to assign number " << step << std::endl;
            // faustassert(false);  // we dont want to continue !
        }
        // Assign the current step number to the signal
        stepNumbers[sig] = step++;
    }
    return step;
}

/**
 * @brief Generates a DOT graph representation of the hierarchical schedule.
 *
 * This function creates a complete DOT graph showing the signal dependencies
 * with separate clusters for constants/controls and audio signals.
 *
 * @param hs The hierarchical schedule to convert to DOT format.
 * @param os The output stream to write the DOT graph to.
 */
void printHschedDOT(const Hsched& hs, std::ostream& os)
{
    std::map<Tree, int> stepNumbers = numberSchedule(hs);

    os << "digraph signal_schedule {" << std::endl;
    os << "  rankdir=TB;" << std::endl;
    os << "  node [fontname=\"Arial\"];" << std::endl;
    os << "  edge [fontname=\"Arial\"];" << std::endl;
    os << std::endl;

    // Generate constants and controls cluster
    os << "  subgraph cluster_constants {" << std::endl;
    os << "    label=\"Constant and Control Signals\";" << std::endl;
    os << "    style=filled;" << std::endl;
    os << "    fillcolor=lightblue;" << std::endl;
    os << "    fontsize=14;" << std::endl;

    for (Tree sig : hs.controls.elements()) {
        printSigDOTNode(os, sig, stepNumbers);
    }
    os << "  }" << std::endl;
    os << std::endl;

    // Generate audio signals cluster
    os << "  subgraph cluster_audio {" << std::endl;
    os << "    label=\"Audio Signals\";" << std::endl;
    os << "    style=filled;" << std::endl;
    os << "    fillcolor=lightgreen;" << std::endl;
    os << "    fontsize=14;" << std::endl;

    recDOTPrinting(os, hs.sigsched, stepNumbers, hs.sigsched.at(hs.outSigList), "audio");
    os << "  }" << std::endl;
    os << std::endl;

    // Generate all edges
    os << "  // Dependencies" << std::endl;
    for (Tree sig : hs.controls.elements()) {
        printSigDOTEdges(os, sig, stepNumbers);
    }

    for (Tree sig : hs.sigsched.at(hs.outSigList).elements()) {
        Tree clk;
        if (needSubGraph(sig, clk)) {
            for (Tree subsig : hs.sigsched.at(sig).elements()) {
                printSigDOTEdges(os, subsig, stepNumbers);
            }
        }
        printSigDOTEdges(os, sig, stepNumbers);
    }

    os << "}" << std::endl;
}

/**
 * @brief Recursively generates DOT nodes for the schedule.
 *
 * @param os The output stream to write to.
 * @param sigSchedules A map of signals to their schedules.
 * @param stepNumbers A map of signals to their step numbers.
 * @param schedule The schedule to convert.
 * @param subgraphName Name for the subgraph (cluster).
 */
void recDOTPrinting(std::ostream& os, const std::map<Tree, schedule<Tree>>& sigSchedules,
                    const std::map<Tree, int>& stepNumbers, const schedule<Tree>& schedule,
                    const std::string& subgraphName)
{
    for (Tree sig : schedule.elements()) {
        if (Tree clk; needSubGraph(sig, clk)) {
            recDOTPrinting(os, sigSchedules, stepNumbers, sigSchedules.at(sig), subgraphName);
        }
        printSigDOTNode(os, sig, stepNumbers);
    }
}

/**
 * @brief Generates a DOT node representation for a signal.
 *
 * @param os The output stream to write to.
 * @param sig The signal to convert.
 * @param stepNumbers A map of signals to their step numbers.
 */
void printSigDOTNode(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers)
{
    int stepNum = stepNumbers.at(sig);
    os << "    node" << stepNum << " [label=<" << "<font color=\"gray\">" << stepNum << ":</font> ";

    // Get signal description without step references
    Tree W, var, body;

    // Special case: input signal
    if (int i; isSigInput(sig, &i)) {
        os << "Input(" << i << ")";
    }
    // Special case: projection from recursive definitions
    else if (int i; isProj(sig, &i, W)) {
        faustassert(isRec(W, var, body));
        os << "letrec " << *var << '(' << i << ")";
    }
    // Special case: sigclocked signals
    else if (Tree clk, s; isSigClocked(sig, clk, s)) {
        os << "sigClocked(";
        if (clk == gGlobal->nil) {
            os << "sample";
        } else {
            os << clk;
        }
        os << ",...)";
    }
    // Special case: binary operations with symbolic operators
    else {
        int  op;
        Tree x, y;
        if (isSigBinOp(sig, &op, x, y)) {
            // Map operation codes to symbols
            const char* opSymbol = "?";
            switch (op) {
                case kAdd:
                    opSymbol = "+";
                    break;
                case kSub:
                    opSymbol = "-";
                    break;
                case kMul:
                    opSymbol = "*";
                    break;
                case kDiv:
                    opSymbol = "/";
                    break;
                case kRem:
                    opSymbol = "%";
                    break;
                case kLsh:
                    opSymbol = "&lt;&lt;";
                    break;
                case kARsh:
                    opSymbol = "&gt;&gt;";
                    break;
                case kLRsh:
                    opSymbol = "&gt;&gt;&gt;";
                    break;
                case kGT:
                    opSymbol = "&gt;";
                    break;
                case kLT:
                    opSymbol = "&lt;";
                    break;
                case kGE:
                    opSymbol = "&gt;=";
                    break;
                case kLE:
                    opSymbol = "&lt;=";
                    break;
                case kEQ:
                    opSymbol = "==";
                    break;
                case kNE:
                    opSymbol = "!=";
                    break;
                case kAND:
                    opSymbol = "&";
                    break;
                case kOR:
                    opSymbol = "|";
                    break;
                case kXOR:
                    opSymbol = "^";
                    break;
                default:
                    opSymbol = "?";
                    break;
            }

            os << opSymbol << "(";
            bool first           = true;
            bool hasNonConstants = false;

            // Display constants for both operands
            tvec operands = {x, y};
            for (Tree operand : operands) {
                int    intVal;
                double realVal;
                if (isSigInt(operand, &intVal)) {
                    if (!first) {
                        os << ", ";
                    }
                    os << intVal;
                    first = false;
                } else if (isSigReal(operand, &realVal)) {
                    if (!first) {
                        os << ", ";
                    }
                    os << realVal;
                    first = false;
                } else {
                    hasNonConstants = true;
                }
            }

            // Add "..." if there are non-constant operands
            if (hasNonConstants) {
                if (!first) {
                    os << ", ";
                }
                os << "...";
            }

            os << ")";
        } else {
            // General case with constants in label
            os << sig->node();

            tvec branches = sig->branches();
            if (branches.size() > 0) {
                os << "(";
                bool first           = true;
                bool hasNonConstants = false;

                // First pass: display all constants
                for (Tree branch : branches) {
                    int    intVal;
                    double realVal;
                    if (isSigInt(branch, &intVal)) {
                        if (!first) {
                            os << ", ";
                        }
                        os << intVal;
                        first = false;
                    } else if (isSigReal(branch, &realVal)) {
                        if (!first) {
                            os << ", ";
                        }
                        os << realVal;
                        first = false;
                    } else {
                        hasNonConstants = true;
                    }
                }

                // Add "..." if there are non-constant operands
                if (hasNonConstants) {
                    if (!first) {
                        os << ", ";
                    }
                    os << "...";
                }

                os << ")";
            }
        }
    }

    os << ">";

    // Set node style based on signal type
    if (int i; isSigInput(sig, &i)) {
        os << " shape=ellipse fillcolor=yellow style=filled";
    } else if (Tree clk, s; isSigClocked(sig, clk, s)) {
        os << " shape=box fillcolor=orange style=filled";
    } else {
        os << " shape=ellipse fillcolor=white style=filled";
    }

    os << "];" << std::endl;
}

/**
 * @brief Generates DOT edges for signal dependencies.
 *
 * @param os The output stream to write to.
 * @param sig The signal to process.
 * @param stepNumbers A map of signals to their step numbers.
 */
void printSigDOTEdges(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers)
{
    int stepNum = stepNumbers.at(sig);

    // Process all dependencies
    Tree W, var, body;

    // Special case: projection from recursive definitions
    if (int i; isProj(sig, &i, W)) {
        faustassert(isRec(W, var, body));
        Tree dep = nth(body, i);
        if (stepNumbers.find(dep) != stepNumbers.end()) {
            os << "  node" << stepNum << " -> node" << stepNumbers.at(dep) << ";" << std::endl;
        }
        return;
    }

    // Handle IIR
    if (tvec v; isSigIIR(sig, v)) {
        for (Tree dep : v) {
            if (stepNumbers.find(dep) != stepNumbers.end()) {
                os << "  node" << stepNumbers.at(dep) << " -> node" << stepNum << ";" << std::endl;
            }
        }
        return;
    }

    // Special case: sigclocked signals
    if (Tree clk, s; isSigClocked(sig, clk, s)) {
        if (stepNumbers.find(s) != stepNumbers.end()) {
            os << "  node" << stepNum << " -> node" << stepNumbers.at(s) << ";" << std::endl;
        }
        return;
    }

    // Special case for OD/US/DS signals
    if (Tree clockedClk; needSubGraph(sig, clockedClk)) {
        Tree clkenv, clk;
        faustassert(isSigClocked(clockedClk, clkenv, clk));
        if (stepNumbers.find(clk) != stepNumbers.end()) {
            os << "  node" << stepNum << " -> node" << stepNumbers.at(clk) << ";" << std::endl;
        }

        bool afternil = false;
        for (Tree s : sig->branches()) {
            if (afternil && stepNumbers.find(s) != stepNumbers.end()) {
                os << "  node" << stepNum << " -> node" << stepNumbers.at(s) << ";" << std::endl;
            } else if (s == gGlobal->nil) {
                afternil = true;
            }
        }
        return;
    }

    // General case: only create edges to non-constant operands
    for (Tree dep : sig->branches()) {
        int    intVal;
        double realVal;
        // Only create edge if it's not a constant
        if (!isSigInt(dep, &intVal) && !isSigReal(dep, &realVal)) {
            if (stepNumbers.find(dep) != stepNumbers.end()) {
                os << "  node" << stepNum << " -> node" << stepNumbers.at(dep) << ";" << std::endl;
            }
        }
    }
}