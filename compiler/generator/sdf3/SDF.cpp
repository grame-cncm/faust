#include "SDF.hh"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "signals.hh"

using namespace std;

Port::Port(const string& name, portType type, int rate) : name{name}, type{type}, execRate{rate}
{
}

void Port::setName(const string& name)
{
    this->name = name;
}

void Port::setType(portType type)
{
    this->type = type;
}

void Port::setRate(int rate)
{
    this->execRate = rate;
}

string Port::getName()
{
    return this->name;
}

string Port::getType()
{
    if (this->type == portType::in) {
        return "in";
    } else if (this->type == portType::out) {
        return "out";
    } else {
        return "ERROR: invalid port type detected";
    }
}

int Port::getRate()
{
    return this->execRate;
}

Actor::Actor(const string& name, const string& type) : name{name}, type{type}
{
    // this->ports = nullptr;
}

void Actor::setName(const string& name)
{
    this->name = name;
}

void Actor::setType(const string& type)
{
    this->type = type;
}

void Actor::setDelayInputSigName(const string& inputSig)
{
    this->delayInputSigName = inputSig;
}

void Actor::setArg(const string& argActorName, int value)
{
    this->args.first  = argActorName;
    this->args.second = value;
}

void Actor::addInputSignalName(const string& name)
{
    this->inputSignals.push_back(name);
}

void Actor::addPort(Port newPort)
{
    this->ports.push_back(newPort);
}

void Actor::removePort(const string& portName)
{
    for (unsigned i = 0; i < this->ports.size(); i++) {
        if (this->ports[i].getName() == portName) {
            this->ports.erase(this->ports.begin() + i);
        }
    }
}

string Actor::getName()
{
    return this->name;
}

string Actor::getType()
{
    return this->type;
}

vector<Port> Actor::getPorts()
{
    return this->ports;
}

string Actor::getDelayInputSigName()
{
    return this->delayInputSigName;
}

pair<string, int> Actor::getArg()
{
    return this->args;
}

vector<string> Actor::getInputSignalNames()
{
    return this->inputSignals;
}

// replace old signal name with new signal name (order must be retained)
void Actor::replaceInputSignalName(const string& oldName, const string& newName)
{
    std::replace(this->inputSignals.begin(), this->inputSignals.end(), oldName, newName);
}

void Actor::writeToXML(ostream& fout)
{
    fout << "        <actor name='" << this->getName() << "' type='" << this->getType() << "'>"
         << endl;
    for (auto p : this->ports) {
        fout << "            <port type='" << p.getType() << "' name='" << p.getName() << "' rate='"
             << p.getRate() << "'/>" << endl;
    }
    fout << "        </actor>" << endl;
}

void Actor::writePropertiesToXML(ostream& fout)
{
    fout << "        <actorProperties actor='" << this->getName() << "'>" << endl;
    fout << "            <processor type='cluster_0' default='true'>" << endl;
    fout << "                <executionTime time='1' />" << endl;
    fout << "            </processor>" << endl;
    fout << "        </actorProperties>" << endl;
}

void Actor::printInfo()
{
    cout << "Actor name, type: " << this->getName() << ", " << this->getType() << endl;
    for (auto i : this->ports) {
        cout << "\tPort: " << i.getName() << endl;
    }
}

Channel::Channel(const string& name, const string& srcActor, const string& srcPort,
                 const string& dstActor, const string& dstPort, int size, int initialTokens)
    : name{name},
      srcActor{srcActor},
      dstActor{dstActor},
      srcPort{srcPort},
      dstPort{dstPort},
      size{size},
      initialTokens{initialTokens}
{
}

Channel::Channel(const string& name, const string& srcActor, const string& srcPort,
                 const string& dstActor, const string& dstPort)
    : name{name},
      srcActor{srcActor},
      dstActor{dstActor},
      srcPort{srcPort},
      dstPort{dstPort},
      size{1},
      initialTokens{0}
{
}

void Channel::setSrcActor(const string& srcActorName)
{
    this->srcActor = srcActorName;
}

void Channel::setDstActor(const string& dstActorName)
{
    this->dstActor = dstActorName;
}

void Channel::setSrcPort(const string& srcPortName)
{
    this->srcPort = srcPortName;
}

void Channel::setDstPort(const string& dstPortName)
{
    this->dstPort = dstPortName;
}

string Channel::getName()
{
    return this->name;
}

string Channel::getSrcActor()
{
    return this->srcActor;
}

string Channel::getDstActor()
{
    return this->dstActor;
}

string Channel::getSrcPort()
{
    return this->srcPort;
}

string Channel::getDstPort()
{
    return this->dstPort;
}

int Channel::getSize()
{
    return this->size;
}

int Channel::getInitialTokens()
{
    return this->initialTokens;
}

void Channel::setInitialTokens(int nTokens)
{
    this->initialTokens = nTokens;
}

void Channel::writeToXML(ostream& fout)
{
    fout << "        <channel name='" << this->getName() << "' srcActor='" << this->getSrcActor()
         << "' srcPort='" << this->getSrcPort() << "' dstActor='" << this->getDstActor()
         << "' dstPort='" << this->getDstPort() << "' size='" << this->getSize()
         << "' initialTokens='" << this->getInitialTokens() << "'/>" << endl;
}

void Channel::printInfo()
{
    cout << "Channel name: " << this->getName() << endl;
    cout << "\tSource Port: " << this->getSrcPort() << endl;
    cout << "\tDest Port: " << this->getDstPort() << endl;
    cout << "\tSrcActor: " << this->getSrcActor() << endl;
    cout << "\tDstActor: " << this->getDstActor() << endl;
}
