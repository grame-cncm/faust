/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2024 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright Jaime Koh (https://github.com/jkmingwen) and GRAME
 ************************************************************************
 ************************************************************************/

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include "signals.hh"

enum portType { in, out };

class Port {
   public:
    Port(const std::string&, portType, int);
    void        setName(const std::string&);
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
    Actor(const std::string&, const std::string&);
    void              setName(const std::string&);
    void              setType(const std::string&);
    void              addPort(Port);
    void              removePort(const std::string&);
    void              setDelayInputSigName(const std::string&);
    void              setArg(const std::string&, int);
    void              addInputSignalName(const std::string&);
    void              addParameter(const std::string& paramName, const std::string& paramVal);
    std::string       getName();
    std::string       getType();
    std::vector<Port> getPorts();
    std::string       getDelayInputSigName();
    std::pair<std::string, int>        getArg();
    std::vector<std::string>           getInputSignalNames();
    std::map<std::string, std::string> getParams();
    void replaceInputSignalName(const std::string& oldName, const std::string& newName);
    void writeToXML(std::ostream& fout);
    void writePropertiesToXML(std::ostream& fout);
    void printInfo();  // for debugging

   private:
    std::string       name;  // unique identifier for actor
    std::string       type;  // describes what the actor does
    std::vector<Port> ports;
    std::string delayInputSigName;  // track input signals for delay operator in order to bypass it
                                    // in SDF representation
    std::pair<std::string, int> args;
    std::vector<std::string> inputSignals;  // track list of input signals for rec operator in order
                                            // to bypass it in SDF representation
    std::map<std::string, std::string>
        params;  // track parameters for given actor (i.e. init, min, max)
};

class Channel {
   public:
    Channel(const std::string& name, const std::string& srcActor, const std::string& srcPort,
            const std::string& dstActor, const std::string& dstPort, int size, int initialTokens);
    Channel(const std::string& name, const std::string& srcActor, const std::string& srcPort,
            const std::string& dstActor, const std::string& dstPort);
    void        setSrcActor(const std::string&);
    void        setDstActor(const std::string&);
    void        setSrcPort(const std::string&);
    void        setDstPort(const std::string&);
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
