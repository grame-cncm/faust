#include "DependenciesPrinting.hh"
#include "DependenciesUtils.hh"
#include "ppsig.hh"

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
        printSigWithStepRefs(os, sig, stepNumbers);
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
void printSigWithStepRefs(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers)
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
            std::cerr << "WARNING: signal " << ppsig(sig) << " as already number "
                      << stepNumbers.at(sig) << " while we want to assign number " << step
                      << std::endl;
            // faustassert(false);  // we dont want to continue !
        }
        // Assign the current step number to the signal
        stepNumbers[sig] = step++;
    }
    return step;
}