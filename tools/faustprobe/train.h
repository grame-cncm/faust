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

struct TrainSpec {
    std::vector<std::string> params;  // exact paths or unique suffixes, in the order of their lanes
    size_t        lossLane      = 0;
    size_t        firstGradLane = 1;
    OptimizerKind optimizer     = OptimizerKind::Adam;
    double        lr            = 0.01;
    size_t        block         = 64;
    size_t        blocks        = 100;
    InputMode     input;
    bool          resetPerBlock = false;
    Assignments   sets;
};

struct TrainStep {
    size_t              block = 0;  // 1-based
    double              loss  = 0.0;
    std::vector<double> grads;
    std::vector<double> params;
};

enum class Bound { None, Lower, Upper };
const char* boundName(Bound bound);

struct BoundStats {
    size_t onLower = 0;
    size_t onUpper = 0;
    Bound  endsOn  = Bound::None;
};

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

struct TrainGrid {
    std::vector<std::string>                          paths;
    std::vector<std::pair<std::vector<double>, double>> points;  // the swept values, and the loss there
    size_t                                            best = 0;
    Assignments                                       bestAssignments() const;
};

enum class FdScheme { Central, Forward, Backward };
const char* fdSchemeName(FdScheme scheme);

struct FdCheck {
    std::string path;
    double      rad           = 0.0;  // the gradient lane summed over the block
    double      fd            = 0.0;  // differences at h and h/2, extrapolated to a zero step
    double      fdPlain       = 0.0;  // the plain difference at h
    double      relativeError = 0.0;  // |rad - fd| / max(|fd|, 1)
    FdScheme    scheme        = FdScheme::Central;
};

Trained train(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec,
              const std::function<void(const TrainStep&)>& onStep);
TrainGrid trainGrid(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec,
                    const std::vector<std::pair<std::string, std::vector<double>>>& axes);
// At 'at', one value per trained control, or at the starting values when null.
std::vector<FdCheck> fdCheck(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec,
                             double h, const std::vector<double>* at);

#endif
