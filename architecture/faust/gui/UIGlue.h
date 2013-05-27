/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/

#ifndef FAUST_UIGLUE_H
#define FAUST_UIGLUE_H

#include "faust/gui/CUI.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * UI glue code
 ******************************************************************************/

void openTabBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openTabBox(label);
}

void openHorizontalBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openHorizontalBox(label);
}

void openVerticalBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openVerticalBox(label);
}

void closeBoxGlue(void* cpp_interface)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->closeBox();
}

void addButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addButton(label, zone);
}

void addCheckButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addCheckButton(label, zone);
}

void addVerticalSliderGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addVerticalSlider(label, zone, init, min, max, step);
}

void addHorizontalSliderGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addHorizontalSlider(label, zone, init, min, max, step);
}

void addNumEntryGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addNumEntry(label, zone, init, min, max, step);
}

void addHorizontalBargraphGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addHorizontalBargraph(label, zone, min, max);
}

void addVerticalBargraphGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addVerticalBargraph(label, zone, min, max);
}

void declareGlue(void* cpp_interface, FAUSTFLOAT* zone, const char* key, const char* value)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->declare(zone, key, value);
}

void buildUIGlue(UIGlue* glue, UI* interface)
{
    glue->uiInterface = interface;
    glue->openTabBox = openTabBoxGlue;
    glue->openHorizontalBox = openHorizontalBoxGlue;
    glue->openVerticalBox = openVerticalBoxGlue;
    glue->closeBox = closeBoxGlue;
    glue->addButton = addButtonGlue;
    glue->addCheckButton = addCheckButtonGlue;
    glue->addVerticalSlider = addVerticalSliderGlue;
    glue->addHorizontalSlider = addHorizontalSliderGlue;
    glue->addNumEntry = addNumEntryGlue;
    glue->addHorizontalBargraph = addHorizontalBargraphGlue;
    glue->addVerticalBargraph = addVerticalBargraphGlue;
    glue->declare = declareGlue;
}

/*******************************************************************************
 * Meta glue code
 ******************************************************************************/

void declareMetaGlue(void* cpp_interface, const char* key, const char* value)
{
    Meta* interface = static_cast<Meta*>(cpp_interface);
    interface->declare(key, value);
}

void buildMetaGlue(MetaGlue* glue, Meta* meta)
{
    glue->mInterface = meta;
    glue->declare = declareMetaGlue;
}

#ifdef __cplusplus
}
#endif

#endif
