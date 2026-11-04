/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2011-2026 GRAME, Centre National de Creation Musicale
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

#ifndef INVERTERSCHEMA_H
#define INVERTERSCHEMA_H

#include "blockSchema.h"

/**
 * An inverter : a special symbol corresponding to '*(-1)'
 * to create more compact diagrams
 */
class inverterSchema : public blockSchema {
   public:
    friend schema* makeInverterSchema(const std::string& color);

    virtual void draw(device& dev);

   private:
    inverterSchema(const std::string& color);
};

#endif  // INVERTERSCHEMA_H
