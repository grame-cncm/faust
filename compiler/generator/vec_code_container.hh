/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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
 ************************************************************************
 ************************************************************************/

#ifndef _VEC_CODE_CONTAINER_H
#define _VEC_CODE_CONTAINER_H

#include "code_container.hh"

/*
 Base class code -vec code generation.
 */
class VectorCodeContainer : public virtual CodeContainer {
   private:
    void moveStack2Struct();

    // Code generated with -lv 0 option
    BlockInst* generateDAGLoopVariant0(const std::string& counter);
    
    // Code generated with -lv 1 option
    BlockInst* generateDAGLoopVariant1(const std::string& counter);

    void generateLocalInputs(BlockInst* loop_code, const std::string& index) override;
    void generateLocalOutputs(BlockInst* loop_code, const std::string& index) override;

    void       processFIR(void) override;
    BlockInst* flattenFIR(void) override;

   protected:
    BlockInst* fDAGBlock;

   public:
    VectorCodeContainer(int numInputs, int numOutputs)
    {
        initialize(numInputs, numOutputs);
        fDAGBlock = InstBuilder::genBlockInst();
    }
};

#endif
