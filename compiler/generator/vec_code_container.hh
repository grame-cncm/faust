/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#ifndef _VEC_CODE_CONTAINER_H
#define _VEC_CODE_CONTAINER_H

#include "code_container.hh"

class VectorCodeContainer : public virtual CodeContainer {

    private:

        void moveStack2Struct();
        
        BlockInst* generateDAGLoopVariant0(const string& counter);
        BlockInst* generateDAGLoopVariant1(const string& counter);
        
        void processFIR(void);
        BlockInst* flattenFIR(void);

    protected:

        BlockInst* fDAGBlock;

    public:

        VectorCodeContainer(int numInputs, int numOutputs)
        {
            initializeCodeContainer(numInputs, numOutputs);
            fFullCount = "count";
        }

};

#endif
