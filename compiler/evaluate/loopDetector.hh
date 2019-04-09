
/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef __LOOPDETECTOR__
#define __LOOPDETECTOR__

/**
 * \file loopDetector.hh
 *
 * Detect evaluation loops
 *
 **/

#include "boxes.hh"
#include "sourcereader.hh"

class loopDetector : public virtual Garbageable {
   private:
    const int    fBuffersize;
    const int    fCheckperiod;
    vector<Tree> fBuffer;
    int          fPhase;

   public:
    loopDetector(int buffersize, int checkperiod)
        : fBuffersize(buffersize), fCheckperiod(checkperiod), fBuffer(buffersize), fPhase(0)
    {
    }

    bool detect(Tree t);
};

#define MAX_STACK_SIZE 524288 * 128
#define STACK_FRAME 65536 * 4

class stackOverflowDetector {
   private:
    long fMaxStackSize;

    bool  fFirstCall;
    void* fFirstStackAddress;

   public:
    stackOverflowDetector(long size) : fMaxStackSize(size), fFirstCall(true), fFirstStackAddress(nullptr) {}

    void detect();
};

#endif
