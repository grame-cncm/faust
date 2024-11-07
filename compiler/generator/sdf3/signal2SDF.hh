#include <cstdlib>
#include "SDF.hh"
#include "property.hh"
#include "sigtyperules.hh"
#include "tree.hh"
#include "treeTraversal.hh"
#include "xtended.hh"

//-------------------------Signal2SDF-------------------------------
// Compile signal expresssions into SDF representations in XML
//------------------------------------------------------------------

using namespace std;

class Signal2SDF : public TreeTraversal {
   protected:
    bool           fTraceFlag{false};  // trace transformations when true
    bool           fVisitGen{false};
    int            fIndent{0};  // current indentation during trace
    std::string    fMessage;    // trace message
    std::set<Tree> fVisited;    // avoid visiting a tree twice

    map<std::string, Actor>   actorList;
    map<std::string, Channel> chList;
    int                       chCount  = 0;
    int                       outCount = 0;
    vector<std::string>       delayActors;
    vector<std::string>       recActors;
    vector<std::string>       inputArgTrackedActors;

    void visit(Tree t) override;

   public:
    Signal2SDF() = default;
    void        self(Tree t) override;
    void        sigToSDF(Tree t, std::ostream& fout);
    std::string chAttr(Type t);
    void        mergeChannels(const std::string& ch1, const std::string& ch2);
    void        bypassRec(const std::string& recActorName, vector<std::string>& inputSignalNames);
    std::string channelNameFromPort(Port port);
    std::string channelNameFromActors(const std::string& srcActor, const std::string& dstActor);
    void        updateArguments(const std::string& oldArg, const std::string& newArg);
    void        addChannel(Tree sig);
    void        logActor(Tree sig, const std::string& type);
    void        logDelayActor(Tree sig, Tree x, Tree y, const std::string& type);
    void        logRecActor(Tree sig, Tree le, const std::string& type);
    void        logBinopActor(Tree sig, Tree x, Tree y, const std::string& type);
    void        logUIActor(Tree sig, Tree init);
    void        logPowActor(Tree sig, Tree x, Tree y, const std::string& type);
    void        logCastActor(Tree sig, Tree x, const std::string& type);
    bool        isSigPow(Tree sig, int* i, Tree& x, Tree& y);
};
