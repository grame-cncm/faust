/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#ifndef __interpreter_factory_base__
#define __interpreter_factory_base__

#include <string>
#include <ostream>

struct Meta;
class dsp_factory;
class dsp;

struct dsp_factory_base {
    
    virtual ~dsp_factory_base()
    {}
    
    virtual std::string getName() = 0;
    
    virtual std::string getSHAKey() = 0;
    virtual void setSHAKey(const std::string& sha_key) = 0;
    
    virtual std::string getDSPCode() = 0;
    virtual void setDSPCode(const std::string& code) = 0;
    
    virtual dsp* createDSPInstance(dsp_factory* factory) = 0;
    
    virtual void metadata(Meta* meta) = 0;
    
    virtual void write(std::ostream* out, bool small = false) = 0;
  
};

#endif
