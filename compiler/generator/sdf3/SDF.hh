#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include "signals.hh"

enum portType { in, out };

class Port {
   public:
    Port(std::string, portType, int);
    void        setName(std::string);
    void        setType(portType);
    void        setRate(int);
    std::string getName();
    std::string getType();
    int         getRate();

   private:
    std::string name;
    portType    type;
    int         execRate;
};

class Actor {
   public:
    Actor(std::string, std::string);
    void                        setName(std::string);
    void                        setType(std::string);
    void                        addPort(Port);
    void                        removePort(std::string);
    void                        setDelayInputSigName(std::string);
    void                        setArg(std::string, int);
    void                        addInputSignalName(std::string);
    std::string                 getName();
    std::string                 getType();
    std::vector<Port>           getPorts();
    std::string                 getDelayInputSigName();
    std::pair<std::string, int> getArg();
    std::vector<std::string>    getInputSignalNames();
    void                        replaceInputSignalName(std::string oldName, std::string newName);
    void                        writeToXML(std::ostream& fout);
    void                        writePropertiesToXML(std::ostream& fout);
    void                        printInfo();  // for debugging

   private:
    std::string       name;  // unique identifier for actor
    std::string       type;  // describes what the actor does
    std::vector<Port> ports;
    std::string delayInputSigName;  // track input signals for delay operator in order to bypass it
                                    // in SDF representation
    std::pair<std::string, int> args;
    std::vector<std::string> inputSignals;  // track list of input signals for rec operator in order
                                            // to bypass it in SDF representation
};

class Channel {
   public:
    Channel(std::string name, std::string srcActor, std::string srcPort, std::string dstActor,
            std::string dstPort, int size, int initialTokens);
    Channel(std::string name, std::string srcActor, std::string srcPort, std::string dstActor,
            std::string dstPort);
    void        setSrcActor(std::string);
    void        setDstActor(std::string);
    void        setSrcPort(std::string);
    void        setDstPort(std::string);
    std::string getName();
    std::string getSrcActor();
    std::string getDstActor();
    std::string getSrcPort();
    std::string getDstPort();
    int         getSize();
    int         getInitialTokens();
    void        setInitialTokens(int);
    void        writeToXML(std::ostream& fout);
    void        printInfo();

   private:
    std::string name;
    std::string srcActor;
    std::string dstActor;
    std::string srcPort;
    std::string dstPort;
    int         size;
    int         initialTokens;
};
