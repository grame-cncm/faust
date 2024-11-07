#include "SDF.hh"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "signals.hh"

Port::Port(std::string name, portType type, int rate) : name{name}, type{type}, execRate{rate}
{
}

void Port::setName(std::string name)
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

std::string Port::getName()
{
    return this->name;
}

std::string Port::getType()
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

Actor::Actor(std::string name, std::string type) : name{name}, type{type}
{
    // this->ports = nullptr;
}

void Actor::setName(std::string name)
{
    this->name = name;
}

void Actor::setType(std::string type)
{
    this->type = type;
}

void Actor::setDelayInputSigName(std::string inputSig)
{
    this->delayInputSigName = inputSig;
}

void Actor::setArg(std::string argActorName, int value)
{
    this->args.first  = argActorName;
    this->args.second = value;
}

void Actor::addInputSignalName(std::string name)
{
    this->inputSignals.push_back(name);
}

void Actor::addPort(Port newPort)
{
    this->ports.push_back(newPort);
}

void Actor::removePort(std::string portName)
{
    for (unsigned i = 0; i < this->ports.size(); i++) {
        if (this->ports[i].getName() == portName) {
            this->ports.erase(this->ports.begin() + i);
        }
    }
}

std::string Actor::getName()
{
    return this->name;
}

std::string Actor::getType()
{
    return this->type;
}

std::vector<Port> Actor::getPorts()
{
    return this->ports;
}

std::string Actor::getDelayInputSigName()
{
    return this->delayInputSigName;
}

std::pair<std::string, int> Actor::getArg()
{
    return this->args;
}

std::vector<std::string> Actor::getInputSignalNames()
{
    return this->inputSignals;
}

// replace old signal name with new signal name (order must be retained)
void Actor::replaceInputSignalName(std::string oldName, std::string newName)
{
    std::replace(this->inputSignals.begin(), this->inputSignals.end(), oldName, newName);
}

void Actor::writeToXML(std::ostream& fout)
{
    fout << "        <actor name='" << this->getName() << "' type='" << this->getType() << "'>"
         << std::endl;
    for (auto p : this->ports) {
        fout << "            <port type='" << p.getType() << "' name='" << p.getName() << "' rate='"
             << p.getRate() << "'/>" << std::endl;
    }
    fout << "        </actor>" << std::endl;
}

void Actor::writePropertiesToXML(std::ostream& fout)
{
    fout << "        <actorProperties actor='" << this->getName() << "'>" << std::endl;
    fout << "            <processor type='cluster_0' default='true'>" << std::endl;
    fout << "                <executionTime time='1' />" << std::endl;
    fout << "            </processor>" << std::endl;
    fout << "        </actorProperties>" << std::endl;
}

void Actor::printInfo()
{
    std::cout << "Actor name, type: " << this->getName() << ", " << this->getType() << std::endl;
    for (auto i : this->ports) {
        std::cout << "\tPort: " << i.getName() << std::endl;
    }
}

Channel::Channel(std::string name, std::string srcActor, std::string srcPort, std::string dstActor,
                 std::string dstPort, int size, int initialTokens)
    : name{name},
      srcActor{srcActor},
      srcPort{srcPort},
      dstActor{dstActor},
      dstPort{dstPort},
      size{size},
      initialTokens{initialTokens}
{
}

Channel::Channel(std::string name, std::string srcActor, std::string srcPort, std::string dstActor,
                 std::string dstPort)
    : name{name},
      srcActor{srcActor},
      srcPort{srcPort},
      dstActor{dstActor},
      dstPort{dstPort},
      size{1},
      initialTokens{0}
{
}

void Channel::setSrcActor(std::string srcActorName)
{
    this->srcActor = srcActorName;
}

void Channel::setDstActor(std::string dstActorName)
{
    this->dstActor = dstActorName;
}

void Channel::setSrcPort(std::string srcPortName)
{
    this->srcPort = srcPortName;
}

void Channel::setDstPort(std::string dstPortName)
{
    this->dstPort = dstPortName;
}

std::string Channel::getName()
{
    return this->name;
}

std::string Channel::getSrcActor()
{
    return this->srcActor;
}

std::string Channel::getDstActor()
{
    return this->dstActor;
}

std::string Channel::getSrcPort()
{
    return this->srcPort;
}

std::string Channel::getDstPort()
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

void Channel::writeToXML(std::ostream& fout)
{
    fout << "        <channel name='" << this->getName() << "' srcActor='" << this->getSrcActor()
         << "' srcPort='" << this->getSrcPort() << "' dstActor='" << this->getDstActor()
         << "' dstPort='" << this->getDstPort() << "' size='" << this->getSize()
         << "' initialTokens='" << this->getInitialTokens() << "'/>" << std::endl;
}

void Channel::printInfo()
{
    std::cout << "Channel name: " << this->getName() << std::endl;
    std::cout << "\tSource Port: " << this->getSrcPort() << std::endl;
    std::cout << "\tDest Port: " << this->getDstPort() << std::endl;
    std::cout << "\tSrcActor: " << this->getSrcActor() << std::endl;
    std::cout << "\tDstActor: " << this->getDstActor() << std::endl;
}
