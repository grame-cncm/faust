/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2023 INRIA
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

#pragma once
#include <string>

class DlCodeGen {
    std::string fDlType;
    std::string fDlName;
    int         fBlockSize;
    int         fDlMaxDelay;
    bool        fMono;

   public:
    DlCodeGen(const std::string& dlType, const std::string& dlName, int blockSize, int dlSize, bool mono)
        : fDlType(dlType), fDlName(dlName), fBlockSize(blockSize), fDlMaxDelay(dlSize), fMono(mono)
    {
    }
    virtual ~DlCodeGen() = default;

    virtual std::string globalDeclare() const;
    virtual std::string globalInit() const;
    virtual std::string localDeclare() const;
    virtual std::string pointerSetup() const;
    virtual std::string copyGlobalToLocal() const;
    virtual std::string copyLocalToGlobal() const;
    virtual std::string advance() const;
   
};
