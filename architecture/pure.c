/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2009-2011 Albert Graef <Dr.Graef@t-online.de>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 2.1 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA.
 ************************************************************************
 ************************************************************************/

/* Pure C architecture for Faust. This provides essentially the same interface
   as the C++ architecture in pure.cpp, but is supposed to be used with Pure's
   native Faust interface. In particular, this architecture enables you to use
   faust2 to compile a Faust dsp to a C module (faust -lang c -a pure.c) which
   can then be compiled to LLVM bitcode using an LLVM-capable C compiler such
   as clang, llvm-gcc, or gcc with the dragonegg plugin. The resulting bitcode
   module can then be loaded with Pure's built-in Faust bitcode linker. Please
   check the Pure manual at http://purelang.bitbucket.org for details. */

#include <stdlib.h>
#include <math.h>

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

/* Define FAUSTFLOAT so that audio buffers and control values are always
   represented as double pointers. */

#define FAUSTFLOAT double

//----------------------------------------------------------------------------
//  Abstract user interface
//----------------------------------------------------------------------------

// -- layout groups

typedef void (* openTabBoxFun) (void* interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* interface, const char* label);
typedef void (* openVerticalBoxFun) (void* interface, const char* label);
typedef void (*closeBoxFun) (void* interface);

// -- active widgets

typedef void (* addButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive display widgets

typedef void (* addHorizontalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

typedef void (* declareFun) (void* interface, FAUSTFLOAT* zone, const char* key, const char* value);

typedef struct {
  void* uiInterface;
  openTabBoxFun openTabBox;
  openHorizontalBoxFun openHorizontalBox;
  openVerticalBoxFun openVerticalBox;
  closeBoxFun closeBox;
  addButtonFun addButton;
  addCheckButtonFun addCheckButton;
  addVerticalSliderFun addVerticalSlider;
  addHorizontalSliderFun addHorizontalSlider;
  addNumEntryFun addNumEntry;
  addHorizontalBargraphFun addHorizontalBargraph;
  addVerticalBargraphFun addVerticalBargraph;
  declareFun declare;
} UIGlue;

typedef void (* metaDeclareFun) (void*, const char* key, const char* value);

typedef struct {
  void *metaInterface;
  metaDeclareFun declare;
} MetaGlue;

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>
