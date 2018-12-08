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

#ifndef _FBC_EXECUTOR_H
#define _FBC_EXECUTOR_H

#include "faust/gui/CGlue.h"
#include "interpreter_bytecode.hh"

template <class T>
struct FBCExecutor {
    
    virtual void ExecuteBuildUserInterface(FIRUserInterfaceBlockInstruction<T>* block, UITemplate* glue) {};
    virtual void ExecuteBlock(FBCBlockInstruction<T>* block, bool compile = false) {};
    
    virtual void setIntValue(int offset, int value) {}
    virtual int getIntValue(int offset) { return -1; }
    
    virtual void setInput(int offset, T* buffer) {}
    virtual void setOutput(int offset, T* buffer) {}
    
};

#endif
