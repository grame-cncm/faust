#include "signal2SDF.hh"
#include <cassert>
#include <cstdlib>
#include <map>
#include "Text.hh"
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signalVisitor.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"

using namespace std;

/**
 * Draw a list of signals as a synchronous dataflow graph using
 * SDF3-compatible XML format
 */
void Signal2SDF::sigToSDF(Tree L, ostream& fout)
{
    const string graphName = gGlobal->gMasterName;  // name of .dsp file
    set<Tree>    alreadyDrawn;
    while (!isNil(L)) {
        self(hd(L));
        // recLog(hd(L), alreadyDrawn);
        // add output node (and related ports/channels) to relevant lists
        string outName("OUTPUT_" + std::to_string(outCount));
        actorList.insert(pair<string, Actor>(outName, Actor(outName, outName)));
        stringstream srcActor;
        srcActor << hd(L);
        string chName("channel_" + std::to_string(chCount) + chAttr(getCertifiedSigType(hd(L))));
        string srcPortName("in_" + chName);
        string dstPortName("out_" + chName);
        actorList.at(srcActor.str()).addPort(Port(srcPortName, portType::out, 1));
        actorList.at(outName).addPort(Port(dstPortName, portType::in, 1));
        chList.insert(pair<string, Channel>(
            chName, Channel(chName, srcActor.str(), srcPortName, outName, dstPortName, 1, 0)));
        chCount++;
        outCount++;
        L = tl(L);
    }

    // Write graph information to XML
    fout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
         << "<sdf3 type=\"sdf\" version=\"1.0\"\n"
         << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
         << "    xsi:noNamespaceSchemaLocation=\"http://www.es.ele.tue.nl/sdf3/xsd/sdf3-csdf.xsd\">"
         << endl;
    fout << "<applicationGraph name='" << graphName << "'>" << endl;
    fout << "    <sdf name='" << graphName << "' type='" << graphName << "'>" << endl;
    // Bypass REC actors for SDF
    for (auto& r : recActors) {
        vector<string> inputActorNames = actorList.at(r).getInputSignalNames();
        bypassRec(r, inputActorNames);
        // remove bypassed channels
        for (auto& i : inputActorNames) {
            string channelToRemove = channelNameFromActors(i, r);
            actorList.at(i).removePort(chList.at(channelToRemove).getSrcPort());
            chList.erase(chList.find(channelToRemove));
            updateArguments(r, i);
        }
        // remove recursive actor
        actorList.erase(actorList.find(r));
    }
    // update names of binop actors to reflect order of input arguments
    for (auto& b : inputArgTrackedActors) {
        string newName = actorList.at(b).getName();
        for (auto& arg : actorList.at(b).getInputSignalNames()) {
            newName += "_" + arg;
        }
        actorList.at(b).setName(newName);
        for (auto& c : chList) {  // update actor name in channel list
            if (c.second.getSrcActor() == b) {
                chList.at(c.first).setSrcActor(newName);
            } else if (c.second.getDstActor() == b) {
                chList.at(c.first).setDstActor(newName);
            }
        }
    }
    // Write graph information (actor/channel names, ports)
    for (auto& a : actorList) {
        // add self loops
        string srcPortName("in_R" + a.first);
        string dstPortName("out_R" + a.first);
        a.second.addPort(Port(srcPortName, portType::out, 1));
        a.second.addPort(Port(dstPortName, portType::in, 1));
        string chName("channel_" + a.first);
        chList.insert(
            pair<string, Channel>(chName, Channel(chName, a.second.getName(), srcPortName,
                                                  a.second.getName(), dstPortName, 1, 1)));
        a.second.writeToXML(fout);
    }
    for (auto& c : chList) {
        c.second.writeToXML(fout);
    }
    fout << "    </sdf>\n" << endl;
    fout << "    <sdfProperties>" << endl;
    // Write actor properties
    for (auto& a : actorList) {
        a.second.writePropertiesToXML(fout);
    }
    fout << "    </sdfProperties>" << endl;
    fout << "</applicationGraph>" << endl;
    fout << "</sdf3>" << endl;
}

/**
 * translate signal binary operations into strings
 */
static const char* binopname[] = {"add",      "diff",        "prod",     "div", "mod", "l_shift",
                                  "r_shift",  "greaterthan", "lessthan", "geq", "leq", "equal",
                                  "notequal", "AND",         "OR",       "XOR"};

/**
 * traverse tree and perform various actions depending
 * on the type of signal detected
 */
void Signal2SDF::visit(Tree sig)
{
    int          i;
    double       r;
    vector<Tree> subsig;
    Tree         c, sel, x, y, z, u, v, var, le, label, id, ff, largs, type, name, file, sf;

    xtended* p = (xtended*)getUserData(sig);
    if (isList(sig)) {
        do {
            self(hd(sig));
            sig = tl(sig);
        } while (isList(sig));
    } else if (p) {
        if (p == gGlobal->gPowPrim) {  // a very roundabout way to identify power operators since
                                       // they're categorized under xtended types
            if (isSigPow(sig, &i, x, y)) {
                logPowActor(sig, x, y, "pow");
            }
        } else if (p == gGlobal->gFloorPrim) {
            if (isTree(sig, "floor", x)) {
                logCastActor(sig, x, "floor");
            }
        } else if (p == gGlobal->gMaxPrim) {
            if (isTree(sig, "max", x, y)) {
                logBinopActor(sig, x, y, "max");
            }
        } else if (p == gGlobal->gMinPrim) {
            if (isTree(sig, "min", x, y)) {
                logBinopActor(sig, x, y, "min");
            }
        } else if (p == gGlobal->gSqrtPrim) {
            if (isTree(sig, "sqrt", x)) {
                logCastActor(sig, x, "sqrt");
            }
        } else {
            logActor(sig, p->name());
        }
        for (Tree b : sig->branches()) {
            self(b);
        }
        return;
    } else if (isSigInt(sig, &i)) {
        logActor(sig, std::to_string(i));
        return;
    } else if (isSigReal(sig, &r)) {
        logActor(sig, std::to_string(r));
        return;
    } else if (isSigWaveform(sig)) {
        logActor(sig, "waveform");
        return;
    } else if (isSigInput(sig, &i)) {
        logActor(sig, "INPUT_" + std::to_string(i));
        return;
    } else if (isSigOutput(sig, &i, x)) {
        logActor(sig, "OUTPUT_" + std::to_string(i));
        self(x);
        return;
    } else if (isSigDelay1(sig, x)) {
        logActor(sig, "mem");
        self(x);
        return;
    } else if (isSigDelay(sig, x, y)) {
        logActor(sig, "delay");
        self(x);
        self(y);
        return;
    } else if (isSigPrefix(sig, x, y)) {
        logActor(sig, "prefix");
        self(x);
        self(y);
        return;
    } else if (isSigBinOp(sig, &i, x, y)) {
        logBinopActor(sig, x, y, binopname[i]);
        self(x);
        self(y);
        return;
    }

    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
        mapself(largs);
        return;
    } else if (isSigFConst(sig, type, name, file)) {
        logActor(sig, tree2str(name));
        return;
    } else if (isSigFVar(sig, type, name, file)) {
        return;
    }

    // Tables
    // else if (isSigTable(sig, id, x, y)) { // TODO wait for new implementation
    //     std::stringstream fout;
    //     fout << "table: " << id;
    //     logActor(sig, fout.str());
    //     self(x);
    //     self(y);
    //     return;
    // }
    else if (isSigWRTbl(sig, id, x, y, z)) {
        stringstream fout;
        fout << "write: " << id;
        logActor(sig, fout.str());
        self(x);
        self(y);
        self(z);
        return;
    } else if (isSigRDTbl(sig, x, y)) {
        logActor(sig, "read");
        self(x);
        self(y);
        return;
    }

    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        self(x);
        self(y);
        self(u);
        self(v);
        return;
    } else if (isSigDocAccessTbl(sig, x, y)) {
        self(x);
        self(y);
        return;
    }

    // Select2 (and Select3 expressed with Select2)
    else if (isSigSelect2(sig, sel, x, y)) {
        logActor(sig, "select2");
        self(sel);
        self(x);
        self(y);
        return;
    }

    // Table sigGen
    else if (isSigGen(sig, x)) {
        if (fVisitGen) {
            logActor(sig, "generator");
            self(x);
            return;
        } else {
            return;
        }
    }

    // recursive signals
    else if (isProj(sig, &i, x)) {
        logActor(sig, "Proj");
        self(x);
        return;
    } else if (isRec(sig, var, le)) {
        stringstream fout;
        fout << "REC " << *var;
        logRecActor(sig, le, fout.str());
        self(le);
        return;
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        logCastActor(sig, x, "float2int");
        self(x);
        return;
    } else if (isSigFloatCast(sig, x)) {
        logCastActor(sig, x, "int2float");
        self(x);
        return;
    }

    // UI
    else if (isSigButton(sig, label)) {
        logActor(sig, "button");
        return;
    } else if (isSigCheckbox(sig, label)) {
        logActor(sig, "checkbox");
        return;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        logActor(sig, "vslider");
        // self(c), self(x), self(y), self(z);
        return;
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        logActor(sig, "hslider");
        // self(c), self(x), self(y), self(z);
        return;
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        logActor(sig, "nentry");
        self(c), self(x), self(y), self(z);
        return;
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        logActor(sig, "vbargraph");
        self(x), self(y), self(z);
        return;
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        logActor(sig, "hbargraph");
        self(x), self(y), self(z);
        return;
    }

    // Soundfile length, rate, buffer
    else if (isSigSoundfile(sig, label)) {
        return;
    } else if (isSigSoundfileLength(sig, sf, x)) {
        self(sf), self(x);
        return;
    } else if (isSigSoundfileRate(sig, sf, x)) {
        self(sf), self(x);
        return;
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        self(sf), self(x), self(y), self(z);
        return;
    }

    // Attach, Enable, Control
    else if (isSigAttach(sig, x, y)) {
        logActor(sig, "attach");
        self(x), self(y);
        return;
    } else if (isSigEnable(sig, x, y)) {
        self(x), self(y);
        return;
    } else if (isSigControl(sig, x, y)) {
        self(x), self(y);
        return;
    }

    else if (isNil(sig)) {
        // now nil can appear in table write instructions
        return;
    } else {
        stringstream error;
        error << __FILE__ << ":" << __LINE__ << " ERROR : unrecognized signal : " << *sig << endl;
        throw faustexception(error.str());
    }
}

void Signal2SDF::self(Tree t)
{
    if (!fVisited.count(t)) {
        fVisited.insert(t);
        visit(t);
    }
}

/**
 * Return string of signal type
 */
string Signal2SDF::chAttr(Type t)
{
    string s;

    // nature
    switch (t->nature()) {
        case kInt:
            s += "_int";
            break;
        case kReal:
            s += "_real";
            break;
        default:
            s += "_nomatch";
            break;
    }

    // vectorability
    if (t->vectorability() == kVect && t->variability() == kSamp) {
        s += "_vect";
    }

    return s;
}

/**
 * Combine two channels in channel list
 */
void Signal2SDF::mergeChannels(const string& ch1, const string& ch2)
{
    chList.at(ch1).setDstActor(chList.at(ch2).getDstActor());
    chList.at(ch1).setDstPort(chList.at(ch2).getDstPort());
    // retain ch1 in list
    chList.erase(chList.find(ch2));
}

/**
 * Modify a channel to bypass the given REC actor
 */
void Signal2SDF::bypassRec(const string& recActorName, vector<string>& inputSignalNames)
{
    vector<Port> outputPorts;
    for (auto& p : actorList.at(recActorName).getPorts()) {
        if (p.getType() == "out") {
            outputPorts.push_back(p);
        }
    }
    assert(
        outputPorts.size() ==
        inputSignalNames.size());  // rec signals must have matching input and output signal numbers
    // randomly assign inputs to outputs TODO figure out actual mapping of this
    for (size_t i = 0; i < outputPorts.size(); i++) {
        string channelToMod = channelNameFromPort(outputPorts[i]);
        actorList.at(inputSignalNames[i]).addPort(outputPorts[i]);
        chList.at(channelToMod)
            .setSrcActor(
                inputSignalNames[i]);  // connect output channel of REC to one of its input actors
        chList.at(channelToMod).setInitialTokens(1);
    }
}

/**
 * Identify channel name based on an input or output port
 */
string Signal2SDF::channelNameFromPort(Port port)
{
    for (auto& c : chList) {
        if (port.getType() == "in") {
            if (port.getName() == c.second.getDstPort()) {
                return c.second.getName();
            }
        } else if (port.getType() == "out") {
            if (port.getName() == c.second.getSrcPort()) {
                return c.second.getName();
            }
        }
    }
    return "ERROR: no matching channel";
}

/**
 * Identify name of channel between two actors
 */
string Signal2SDF::channelNameFromActors(const string& srcActor, const string& dstActor)
{
    for (auto& c : chList) {
        if (c.second.getSrcActor() == srcActor && c.second.getDstActor() == dstActor) {
            return c.second.getName();
        }
    }
    return "ERROR no matching channel";
}

/**
 * Update argument actor names of operators if they have changed
 */
void Signal2SDF::updateArguments(const string& oldArg, const string& newArg)
{
    for (auto& op : inputArgTrackedActors) {
        vector<string> argNames = (actorList.at(op)).getInputSignalNames();
        for (auto& arg : argNames) {
            if (oldArg == arg) {
                (actorList.at(op)).replaceInputSignalName(oldArg, newArg);
            }
        }
    }
}

/**
 * Add output channels from sig to channel list, along with the corresponding
 * ports on the source and destination actors
 */
void Signal2SDF::addChannel(Tree sig)
{
    vector<Tree> subsig;
    int          n = getSubSignals(sig, subsig);
    if (n > 0) {
        if (n == 1 && isList(subsig[0])) {
            Tree id, body;
            faustassert(isRec(sig, id, body));
            Tree L = subsig[0];
            subsig.clear();
            n = 0;
            do {
                subsig.push_back(hd(L));
                L = tl(L);
                n += 1;
            } while (isList(L));
        }

        for (int i = 0; i < n; i++) {
            self(subsig[i]);
            // log channels and corresponding ports for the connected actors
            string       chName("channel_" + std::to_string(chCount) +
                                chAttr(getCertifiedSigType(subsig[i])));
            stringstream srcActor;
            stringstream dstActor;
            srcActor << subsig[i];
            dstActor << sig;
            string srcPortName("in_" + chName);
            string dstPortName("out_" + chName);
            actorList.at(srcActor.str()).addPort(Port(srcPortName, portType::out, 1));
            actorList.at(dstActor.str()).addPort(Port(dstPortName, portType::in, 1));
            chList.insert(pair<string, Channel>(
                chName,
                Channel(chName, srcActor.str(), srcPortName, dstActor.str(), dstPortName, 1, 0)));
            Tree tId, tB;
            if (isRec(sig, tId,
                      tB)) {  // NOTE workaround to track missing input signals for rec actors
                vector<string> recInputs = actorList.at(dstActor.str()).getInputSignalNames();
                if (std::find(recInputs.begin(), recInputs.end(), srcActor.str()) ==
                    recInputs.end()) {
                    actorList.at(dstActor.str()).addInputSignalName(srcActor.str());
                }
            }
            chCount++;
        }
    }
}

/**
 * Add the actor associated with sig to the actor list
 */
void Signal2SDF::logActor(Tree sig, const string& type)
{
    stringstream actorName;  // get unique actor names from signal
    actorName << sig;
    actorList.insert(pair<string, Actor>(actorName.str(), Actor(actorName.str(), type)));
    addChannel(sig);
}

/**
 * Add the actor associated with sig to the actor list
 */
void Signal2SDF::logDelayActor(Tree sig, Tree x, Tree y, const string& type)
{
    stringstream actorName;
    stringstream arg1Name;
    stringstream arg2Name;
    int          i;
    actorName << sig;
    arg1Name << x;
    arg2Name << y;
    actorList.insert(pair<string, Actor>(actorName.str(), Actor(actorName.str(), type)));
    // NOTE assume here that fixed delays will only have Int argument, might need to expand to
    // include Real values
    if (isSigInt(y, &i)) {  // fixed delay: track delay length to model later
        delayActors.push_back(actorName.str());
        actorList.at(actorName.str()).setDelayInputSigName(arg1Name.str());
        actorList.at(actorName.str()).setArg(arg2Name.str(), i);
    } else {  // variable delay: leave alone; will resolve later
        actorList.at(actorName.str()).addInputSignalName(arg1Name.str());
        actorList.at(actorName.str()).addInputSignalName(arg2Name.str());
    }
    addChannel(sig);
}

/**
 * Add the recursive actor associated with sig to the actor list
 * and recursive actor list
 */
void Signal2SDF::logRecActor(Tree sig, Tree le, const string& type)
{
    stringstream actorName;
    stringstream inputSigName;
    actorName << sig;
    inputSigName << hd(le);
    actorList.insert(pair<string, Actor>(actorName.str(), Actor(actorName.str(), type)));
    recActors.push_back(actorName.str());
    actorList.at(actorName.str()).addInputSignalName(inputSigName.str());
    addChannel(sig);
}

/**
 * Add the binary actor associated with sig to the actor list
 * and track the orger of execution
 */
void Signal2SDF::logBinopActor(Tree sig, Tree x, Tree y, const string& type)
{
    stringstream actorName;
    stringstream arg1Name;
    stringstream arg2Name;
    actorName << sig;
    arg1Name << x;
    arg2Name << y;
    actorList.insert(pair<string, Actor>(actorName.str(), Actor(actorName.str(), type)));
    // track order of arguments for binary operators
    inputArgTrackedActors.push_back(actorName.str());
    actorList.at(actorName.str()).addInputSignalName(arg1Name.str());
    actorList.at(actorName.str()).addInputSignalName(arg2Name.str());
    addChannel(sig);
}

/**
 * Replace UI component with a constant component of equal to its initial value
 */
void Signal2SDF::logUIActor(Tree sig, Tree init)
{
    int    i;
    double r;
    if (isSigInt(init, &i)) {
        logActor(sig, std::to_string(i));
    } else if (isSigReal(init, &r)) {
        logActor(sig, std::to_string(r));
    } else {
        stringstream error;
        error << __FILE__ << ":" << __LINE__
              << " ERROR : init value for UI component not found : " << *sig << endl;
        throw faustexception(error.str());
    }
}

/**
 * Add the power actor associated with sig to the actor list
 * and track the orger of execution - note that it denotes y^x
 */
void Signal2SDF::logPowActor(Tree sig, Tree x, Tree y, const string& type)
{
    stringstream actorName;
    stringstream arg1Name;
    stringstream arg2Name;
    actorName << sig;
    arg1Name << x;
    arg2Name << y;
    actorList.insert(pair<string, Actor>(actorName.str(), Actor(actorName.str(), type)));
    // track order of arguments for binary operators
    inputArgTrackedActors.push_back(actorName.str());
    actorList.at(actorName.str()).addInputSignalName(arg1Name.str());
    actorList.at(actorName.str()).addInputSignalName(arg2Name.str());
    addChannel(sig);
}

/**
 * Add the actor associated with sig to the actor list
 */
void Signal2SDF::logCastActor(Tree sig, Tree x, const string& type)
{
    stringstream actorName;  // get unique actor names from signal
    stringstream argName;
    actorName << sig;
    argName << x;
    actorList.insert(pair<string, Actor>(actorName.str(), Actor(actorName.str(), type)));
    inputArgTrackedActors.push_back(actorName.str());
    actorList.at(actorName.str()).addInputSignalName(argName.str());
    addChannel(sig);
}

/**
 * Check if a signal is a power operator and assign its branches to args x and y
 */
bool Signal2SDF::isSigPow(Tree sig, int* i, Tree& x, Tree& y)
{
    return isTree(sig, "pow", x, y);
}
