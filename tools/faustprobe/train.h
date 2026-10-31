/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// A gradient-descent driver over a probe: the host of a program whose loss and
// gradient lanes leave the graph. Per block the lanes are averaged and the
// optimizer steps the controls, kept in their range. A program that outputs a
// loss and its gradients is what the driver needs, however they were computed.

#ifndef __faustprobe_train__
#define __faustprobe_train__

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "engine.h"

enum class OptimizerKind { Adam, Sgd };

// What to train and how.
struct TrainSpec {
    std::vector<std::string> params;  // exact paths or unique suffixes, in the order of their lanes
    size_t        lossLane      = 0;  // output of the per-sample loss
    size_t        firstGradLane = 1;  // output of the first control's gradient; the others follow
    OptimizerKind optimizer     = OptimizerKind::Adam;  // the update rule
    double        lr            = 0.01;  // learning rate
    size_t        block         = 64;  // frames per step
    size_t        blocks        = 100;  // number of steps
    InputMode     input;  // position-addressed, so the blocks are contiguous
    bool          resetPerBlock = false;  // every block replays the same response from silence
    Assignments   sets;  // --set: a starting point, or a value fixed after every reset
};

// One step, reported as it happens.
struct TrainStep {
    size_t              block = 0;  // 1-based
    double              loss  = 0.0;  // the block's mean loss
    std::vector<double> grads;  // its mean gradients
    std::vector<double> params;  // the controls after the step
};

// Which end of its range a control sits on.
enum class Bound { None, Lower, Upper };
const char* boundName(Bound bound);

// How often keeping a control in its range held it on a bound.
struct BoundStats {
    size_t onLower = 0;
    size_t onUpper = 0;
    Bound  endsOn  = Bound::None;
};

// The outcome of a descent. The last loss is not the best one when the descent left a
// minimum: the lowest, its block and its controls are kept.
struct Trained {
    std::vector<std::string>               paths;
    std::vector<double>                    values;
    std::vector<std::pair<double, double>> ranges;
    std::vector<BoundStats>                bounds;
    double                                 firstLoss = 0.0;
    double                                 lastLoss  = 0.0;
    double                                 minLoss   = 0.0;
    size_t                                 minLossBlock = 0;
    std::vector<double>                    valuesAtMin;
    Timing                                 timing;
};

// The loss of one block over a grid of starting points.
struct TrainGrid {
    std::vector<std::string>                          paths;
    std::vector<std::pair<std::vector<double>, double>> points;  // the swept values, and the loss there
    size_t                                            best = 0;
    Assignments                                       bestAssignments() const;
};

// Where a finite difference takes its points: around the value, or on one side of it
// near a bound of the range.
enum class FdScheme { Central, Forward, Backward };
const char* fdSchemeName(FdScheme scheme);

// One gradient lane against finite differences, on one block.
struct FdCheck {
    std::string path;
    double      rad           = 0.0;  // the gradient lane summed over the block
    double      fd            = 0.0;  // differences at h and h/2, extrapolated to a zero step
    double      fdPlain       = 0.0;  // the plain difference at h
    double      relativeError = 0.0;  // |rad - fd| / max(|fd|, 1)
    FdScheme    scheme        = FdScheme::Central;
};

// The descent, on one instance kept running.
Trained train(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec,
              const std::function<void(const TrainStep&)>& onStep);
// The loss of the first block at every point of the axes, which must name trained controls.
TrainGrid trainGrid(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec,
                    const std::vector<std::pair<std::string, std::vector<double>>>& axes);
// At 'at', one value per trained control, or at the starting values when null.
std::vector<FdCheck> fdCheck(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec,
                             double h, const std::vector<double>* at);

#endif
