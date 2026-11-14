/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

/**
 * @file drawstep.hh
 * Steppable SVG diagrams (-sst <n>).
 *
 * While drawSchema builds the schema of a box, it also propagates signals
 * through it, with the compiler's own propagate(): every schema it builds is
 * recorded with the signals on its inputs and outputs. Once the file is
 * placed, these signals are attached to the wires (traits) and to value labels
 * at the outputs of the blocks, of the recursion delays, and of the diagram.
 * The values of these signals for samples 0 to n-1 are computed by the
 * compiler's SignalRenderer, with the test signal given by -ssi on
 * the inputs of process, and embedded in the SVG with a small player script.
 *
 * Inspired by faust-stepper (Pierre Cochard, https://github.com/pchdev/ujm-dsp),
 * a standalone web page that steps a Faust subset sample by sample; no code is
 * taken from it.
 */

#ifndef _DRAWSTEP_
#define _DRAWSTEP_

#include <string>

#include "signals.hh"

class schema;
class SVGDev;
struct collector;

// Signals of a box being drawn
struct StepContext {
    Tree    fSlotEnv;  // slot environment, as in propagate()
    Tree    fPath;     // user interface path, as in propagate()
    Tree    fRecs;     // enclosing de Bruijn recursive groups, innermost first (a list)
    siglist fIns;      // input signals of the box (open terms inside a recursion)
};

enum StepKind {
    kStepWiring,   // no value label (composition, cable, cut, decoration...)
    kStepBlock,    // a value label on each output
    kStepControl,  // a user interface element : a block, listed among the default table columns
    kStepLiteral,  // a number : its value is its label
    kStepIO        // value labels on the inputs and outputs of the whole file
};

// Space (in SVG units) above the diagram for the stepping controls, smallest width, margin
const double kStepTopBand  = 22;
const double kStepMinWidth = 190;
const double kStepMargin   = 50;

// Output signals of box t in context ctx (the compiler's propagate())
siglist stepOutputs(Tree t, const StepContext& ctx);

// Recording of the schemas of the file being generated
void stepBeginFile();
void stepRecord(schema* s, const StepContext& ctx, const siglist& outs, StepKind kind,
                const std::string& name);
// The delays of a recursion : the inputs of its second (feedback) diagram
void stepRecordDelays(schema* rec, const siglist& delayed, Tree recs);

// A file of the drawing, placed, with its traits collected : prepared now (signals of the
// wires, value labels), written by stepWriteFiles with the wires carrying their signals,
// the value labels, the values and the player
void stepDeferFile(const std::string& path, schema* top, collector* traits);
// Computes the values of all the deferred files in one batch, then writes them
void stepWriteFiles();

// -ssc : parses the control changes and checks that each names a control of process
void stepCheckControls(Tree process);

// The input signals of process for -sst : the outputs of the test signal box
// (0 inputs, 1 or n outputs), cast to float, as many as process has inputs
siglist stepInputSignals(Tree inputBox, int numInputs);

#endif
