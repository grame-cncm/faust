#include <functional>
#include <iostream>
#include <set>
#include <sstream>

#include "global.hh"
#include "instructionInputs.hh"
#include "ppsig.hh"
#include "symbol.hh"

using namespace std;

/**
 * @brief Compute the dependency graph of a signal
 *
 */
class CollectInputs : public SignalVisitor {
    set<Tree> fInputs;  // Its graph of dependencies

   public:
    explicit CollectInputs(Tree sig)
    {
        Tree id, tid, origin, content, init, idx, exp, time, clklist;
        int  i, nature, dmax, dmin, tblsize;
        // Analyzed signals are supposed to be only "instructions": DelayLines, Shared, Controls or Outputs.
        // It is an error otherwise
        if (isSigInstructionDelayLineWrite(sig, id, origin, &nature, &dmax, content)) {
            self(content);
        } else if (isSigInstructionSharedWrite(sig, id, origin, &nature, content)) {
            self(content);
        } else if (isSigInstructionVectorWrite(sig, id, origin, &nature, content)) {
            self(content);
        } else if (isSigInstructionShortDLineWrite(sig, id, origin, &nature, content)) {
            self(content);
        } else if (isSigInstructionControlWrite(sig, id, origin, &nature, content)) {
            self(content);
        } else if (isSigInstructionBargraphWrite(sig, id, origin, &nature, content)) {
            self(content);
        } else if (isSigInstructionTableWrite(sig, id, origin, &nature, &tblsize, init, idx, exp)) {
            self(init);
            self(idx);
            self(exp);
        } else if (isSigInstructionTableAccessWrite(sig, id, origin, &nature, &dmin, tid, idx)) {
            self(idx);
        } else if (isSigOutput(sig, &i, content)) {
            self(content);
        } else if (isSigInstructionTimeWrite(sig)) {
            // NOTHING (but have to check)

        }

        // new instruction2 cases

        else if (isSigInstruction2DelayWrite(sig, clklist, id, &nature, time, content)) {
            self(clklist);
            self(time);
            self(content);
        } else if (isSigInstruction2IncWrite(sig, clklist, id, &nature)) {
            self(clklist);
        } else if (isSigInstruction2MemWrite(sig, clklist, id, &nature, exp)) {
            self(clklist);
            self(exp);
        }

        else {
            std::cerr << "ERROR, not an instruction1: " << ppsig(sig) << endl;
            faustassert(false);
        }
    }

    const set<Tree>& inputs() const { return fInputs; }

   protected:
    void visit(Tree t) override
    {
        Tree id, origin, dl, time, delay;
        int  nature, dmax, dmin;

        // the dependencies are DelayLines, shared expressions or Control signals
        if (isSigInstructionDelayLineRead(t, id, origin, &nature, &dmax, &dmin, dl) ||
            isSigInstructionTableRead(t, id, origin, &nature, &dmin, dl)) {
            fInputs.insert(t);
            self(dl);
        } else if (isSigInstructionSharedRead(t, id, origin, &nature)) {
            fInputs.insert(t);
        } else if (isSigInstructionVectorRead(t, id, origin, &nature)) {
            fInputs.insert(t);
        } else if (isSigInstructionShortDLineRead(t, id, origin, &nature, &dmin)) {
            fInputs.insert(t);
        } else if (isSigInstructionTimeRead(t)) {
            fInputs.insert(t);
        } else if (isSigInstructionControlRead(t, id, origin, &nature)) {
            fInputs.insert(t);
        } else if (isSigInstructionBargraphRead(t, id, origin, &nature)) {
            fInputs.insert(t);
        }

        // new sig instruction2

        else if (isSigInstruction2DelayRead(t, id, &nature, time, delay)) {
            fInputs.insert(id);
            self(time);
            self(delay);
        } else if (isSigInstruction2MemRead(t, id, &nature)) {
            fInputs.insert(id);
        }

        else {
            SignalVisitor::visit(t);
        }
    }
};

set<Tree> instructionInputs(Tree instr)
{
    CollectInputs D(instr);

    return D.inputs();
}
