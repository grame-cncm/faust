#include "sigs-session.hh"

#include "sigs-config.hh"
#include "sigs-state.hh"
#include "signals.hh"
#include "sigtypesolver.hh"

namespace sigs {

/**
 * Standalone initialization of the signal library state: signal symbols,
 * property keys, type singletons, session state and option defaults. NOT
 * called by the Faust compiler, which performs the same writes itself in
 * global.cpp (in its own, order-sensitive sequence); intended for standalone
 * hosts and tests. Requires tlib::init() first, and can be called again
 * between two sessions.
 */
void init()
{
    typeSolverReset();  // solving sessions reference trees of the previous session
    // Signal constructors (interned and registered in the Signal signature)
    initSignalSymbols();

    // Foreign function head and type constructors (ordinary symbols)
    g.FFUN       = symbol("ForeignFunction");
    g.SIMPLETYPE = symbol("SimpleType");

    // Property keys
    g.RECURSIVNESS = tree(symbol("RecursivnessProp"));
    g.DOCTABLES    = tree(symbol("DocTablesProp"));
    g.NULLENV      = tree(symbol("NullRenameEnv"));
    g.NORMALFORM   = tree(symbol("NormalForm"));
    // State of the normal form and of the recursive-dependency analysis
    g.gSimplifiedMemo.clear();
    g.gDependencies.clear();
    g.gWarningMessages.clear();
    g.gStartTiming = nullptr;
    g.gEndTiming   = nullptr;
    // Option defaults of the normal form and the transformations (same values as global.cpp)
    g.gLocalCausalityCheck = false;
    g.gFTZMode             = 0;
    g.gCheckIntRange       = false;
    g.gCheckTable          = true;
    g.gEtaHarvest          = false;
    g.gEtaIterations       = 1;
    g.gEtaRegroup          = false;
    g.gFreezeUI            = false;
    g.gRangeUI             = false;
    g.gMathExceptions      = false;
    g.gVectorSwitch        = false;
    g.gAllWarning          = false;
    g.gSigNoNorm           = false;

    // Session state
    g.TABBER = Tabber(1);
    g.gSignalTable.clear();
    g.gSignalTrace.clear();
    g.gSignalCounter   = 0;
    g.gAllocationCount = 0;
    g.gSymListProp     = new property<Tree>();
    g.gMemoizedTypes   = new property<AudioType*>();

    // Option defaults (same values as global.cpp)
    g.gCausality      = false;
    g.gFloatSize      = 1;

    // Extended primitive registry: empty in standalone mode (the concrete
    // primitives carry code generation and live in the compiler)
    g.gAbsPrim        = nullptr;
    g.gAcosPrim       = nullptr;
    g.gAsinPrim       = nullptr;
    g.gAtan2Prim      = nullptr;
    g.gAtanPrim       = nullptr;
    g.gCeilPrim       = nullptr;
    g.gCosPrim        = nullptr;
    g.gExp10Prim      = nullptr;
    g.gExpPrim        = nullptr;
    g.gFloorPrim      = nullptr;
    g.gFmodPrim       = nullptr;
    g.gLog10Prim      = nullptr;
    g.gLogPrim        = nullptr;
    g.gMaxPrim        = nullptr;
    g.gMinPrim        = nullptr;
    g.gPowPrim        = nullptr;
    g.gRemainderPrim  = nullptr;
    g.gRintPrim       = nullptr;
    g.gSinPrim        = nullptr;
    g.gSqrtPrim       = nullptr;
    g.gTanPrim        = nullptr;

    // Type singletons (require the interval algebra and gMemoizedTypes above)
}

/**
 * Default real printer: shortest "%g" form that round-trips to the same
 * double, with a trailing ".0" added when the result would read as an int.
 */
static std::string defaultRealPrinter(double n)
{
    char c[64];
    for (int p = 1; p <= 32; p++) {
        snprintf(c, sizeof(c), "%.*g", p, n);
        if (strtod(c, nullptr) == n) {
            break;
        }
    }
    if (strcspn(c, ".e") == strlen(c)) {
        strncat(c, ".0", sizeof(c) - strlen(c) - 1);
    }
    return std::string(c);
}

static RealPrinter gRealPrinter = defaultRealPrinter;

RealPrinter setRealPrinter(RealPrinter p)
{
    RealPrinter old = gRealPrinter;
    gRealPrinter    = (p != nullptr) ? p : defaultRealPrinter;
    return old;
}

std::string printReal(double n)
{
    return gRealPrinter(n);
}

}  // namespace sigs
