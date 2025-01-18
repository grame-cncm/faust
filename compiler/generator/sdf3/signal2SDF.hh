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

class Signal2SDF : public TreeTraversal {
   protected:
    bool           fTraceFlag{false};  // trace transformations when true
    bool           fVisitGen{false};
    int            fIndent{0};  // current indentation during trace
    std::string    fMessage;    // trace message
    std::set<Tree> fVisited;    // avoid visiting a tree twice

    std::map<std::string, Actor>   actorList;
    std::map<std::string, Channel> chList;
    int                            chCount  = 0;
    int                            outCount = 0;
    std::vector<std::string>       delayActors;
    std::vector<std::string>       recActors;
    std::vector<std::string>       inputArgTrackedActors;

    void visit(Tree t) override;

   public:
    Signal2SDF() = default;
    void        self(Tree t) override;
    void        sigToSDF(Tree t, std::ostream& fout);
    std::string chAttr(Type t);
    void        mergeChannels(const std::string& ch1, const std::string& ch2);
    void bypassRec(const std::string& recActorName, std::vector<std::string>& inputSignalNames);
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
