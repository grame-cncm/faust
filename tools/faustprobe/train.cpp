/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "train.h"

#include <algorithm>
#include <cmath>
#include <limits>

// The names printed and written to JSON.
const char* boundName(Bound bound)
{
    return bound == Bound::Lower ? "lower" : "upper";
}

// Likewise for a scheme.
const char* fdSchemeName(FdScheme scheme)
{
    switch (scheme) {
        case FdScheme::Central:
            return "central";
        case FdScheme::Forward:
            return "forward";
        default:
            return "backward";
    }
}

// The swept controls at the best point, as --set assignments.
Assignments TrainGrid::bestAssignments() const
{
    Assignments assignments;
    for (size_t k = 0; k < paths.size(); k++) {
        assignments.push_back(std::make_pair(paths[k], points[best].first[k]));
    }
    return assignments;
}

// A trained control: its exact path, its range, its starting value.
struct Param {
    std::string path;
    double      min, max, init;
};

// The control a query names, a bargraph included.
static const Control& resolved(const Probe& probe, const std::string& query)
{
    std::vector<std::string> candidates;
    const Control*           control = probe.controls().resolve(query, &candidates);
    if (control != nullptr) {
        return *control;
    }
    if (candidates.empty()) {
        throw Failure("no control matching `" + query + "`");
    }
    throw Failure("`" + query + "` is ambiguous, matches: " + join(candidates, ", "));
}

// The trained controls, from their widgets' initial values or from what
// 'sets' gives them, clamped to their range.
static std::vector<Param> resolveParams(const Probe& probe, const std::vector<std::string>& queries,
                                        const Assignments& sets)
{
    if (queries.empty()) {
        throw Failure("--train needs at least one control");
    }
    std::vector<Param> params;
    for (const std::string& query : queries) {
        const Control& control = resolved(probe, query);
        if (control.kind == ControlKind::Bargraph) {
            throw Failure("`" + control.path + "` is a bargraph, not a control to train");
        }
        params.push_back({control.path, control.min, control.max, control.init});
    }
    for (const auto& set : sets) {
        const std::string path = resolved(probe, set.first).path;
        for (Param& param : params) {
            if (param.path == path) {
                // the value the check reports as applied, which is what the
                // command line says of it
                try {
                    param.init = probe.controls().checkWrite(set.first, set.second).applied;
                } catch (const Failure&) {
                    param.init = set.second;
                }
            }
        }
    }
    return params;
}

// The --set values; the trained controls are rewritten by the caller just after.
static void applySets(Probe& probe, const Assignments& sets)
{
    for (const auto& set : sets) {
        probe.set(set.first, set.second);
    }
}

// The lanes must exist: reading past the outputs would be silent.
static void checkLanes(const Probe& probe, const TrainSpec& spec)
{
    size_t needed = spec.firstGradLane + spec.params.size();
    if (spec.lossLane >= probe.outputs() || needed > probe.outputs()) {
        throw Failure("the program has " + str(probe.outputs()) + " outputs: the loss lane " + str(spec.lossLane) +
                      " and the gradient lanes " + str(spec.firstGradLane) + ".." + str(needed - 1) +
                      " do not fit");
    }
}

// The excitation of frames start .. start + frames.
static Channels inputBlock(const InputMode& input, size_t channels, size_t start, size_t frames, double sampleRate)
{
    Channels block(channels, std::vector<double>(frames));
    for (size_t ch = 0; ch < channels; ch++) {
        for (size_t i = 0; i < frames; i++) {
            block[ch][i] = input.sample(ch, start + i, sampleRate);
        }
    }
    return block;
}

// The sum of each output over the block: the reverse sweep of a block makes that the
// gradient of the block's loss.
static std::vector<double> laneSums(const Channels& outs)
{
    std::vector<double> sums;
    for (const std::vector<double>& lane : outs) {
        double sum = 0.0;
        for (double value : lane) {
            sum += value;
        }
        sums.push_back(sum);
    }
    return sums;
}

// Per block: the controls are written, the block computed, the lanes averaged, and the
// optimizer steps the controls, clamped to their range. Adam has its bias correction.
Trained train(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec,
              const std::function<void(const TrainStep&)>& onStep)
{
    if (spec.block == 0 || spec.blocks == 0) {
        throw Failure("--train needs a block size and a number of blocks");
    }
    const double kB1 = 0.9, kB2 = 0.999, kEps = 1e-8;  // Kingma & Ba 2015

    Probe              probe(factory, sampleRate);
    std::vector<Param> params = resolveParams(probe, spec.params, spec.sets);
    checkLanes(probe, spec);

    Trained trained;
    for (const Param& param : params) {
        trained.paths.push_back(param.path);
        trained.values.push_back(param.init);
        trained.ranges.push_back(std::make_pair(param.min, param.max));
    }
    std::vector<double>& values = trained.values;
    std::vector<double>  m(params.size(), 0.0), v(params.size(), 0.0);
    trained.minLoss     = std::numeric_limits<double>::infinity();
    trained.valuesAtMin = values;
    trained.bounds.assign(params.size(), BoundStats());
    BlockTimer timer(sampleRate);
    double     n = double(spec.block);

    for (size_t iteration = 1; iteration <= spec.blocks; iteration++) {
        if (spec.resetPerBlock) {
            // controls back to their defaults and the state cleared; the --set
            // controls and the trained ones are rewritten just below
            probe.reset();
        }
        applySets(probe, spec.sets);
        for (size_t k = 0; k < params.size(); k++) {
            probe.setExact(params[k].path, values[k]);
        }
        size_t   start = spec.resetPerBlock ? 0 : (iteration - 1) * spec.block;
        Channels x     = inputBlock(spec.input, probe.inputs(), start, spec.block, sampleRate);

        uint64_t started = nowNanos();
        Channels outs    = probe.computeRaw(x, spec.block);
        // a position in what was computed, whatever the excitation replays
        timer.record((iteration - 1) * spec.block, spec.block, secondsSince(started));

        std::vector<double> sums = laneSums(outs);
        double              loss = sums[spec.lossLane] / n;
        if (!std::isfinite(loss)) {
            std::vector<std::string> then;
            for (size_t k = 0; k < params.size(); k++) {
                then.push_back(params[k].path + "=" + plainNumber(values[k]));
            }
            throw Failure("the loss is not finite at block " + str(iteration) +
                          "\n  controls of that block: " + join(then, " "));
        }
        if (iteration == 1) {
            trained.firstLoss = loss;
        }
        trained.lastLoss = loss;
        if (loss < trained.minLoss) {
            // the controls this block ran with, not those its step leads to
            trained.minLoss      = loss;
            trained.minLossBlock = iteration;
            trained.valuesAtMin  = values;
        }
        std::vector<double> grads;
        for (size_t k = 0; k < params.size(); k++) {
            double g = sums[spec.firstGradLane + k] / n;
            grads.push_back(g);
            double step;
            if (spec.optimizer == OptimizerKind::Sgd) {
                step = spec.lr * g;
            } else {
                m[k]        = kB1 * m[k] + (1.0 - kB1) * g;
                v[k]        = kB2 * v[k] + (1.0 - kB2) * g * g;
                double mHat = m[k] / (1.0 - __builtin_powi(kB1, static_cast<int>(iteration)));
                double vHat = v[k] / (1.0 - __builtin_powi(kB2, static_cast<int>(iteration)));
                step        = spec.lr * mHat / (sqrt(vHat) + kEps);
            }
            values[k] = std::min(std::max(values[k] - step, params[k].min), params[k].max);
            // on a bound after the step: the descent is stopped in that direction
            BoundStats& bound = trained.bounds[k];
            if (values[k] <= params[k].min) {
                bound.onLower++;
                bound.endsOn = Bound::Lower;
            } else if (values[k] >= params[k].max) {
                bound.onUpper++;
                bound.endsOn = Bound::Upper;
            } else {
                bound.endsOn = Bound::None;
            }
        }
        TrainStep step;
        step.block  = iteration;
        step.loss   = loss;
        step.grads  = grads;
        step.params = values;
        onStep(step);
    }
    trained.timing = timer.finish();
    return trained;
}

// Every point from a cleared instance: --set, the trained controls at their start,
// the swept ones at the point. The best is the lowest finite loss, the first on a tie.
TrainGrid trainGrid(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec,
                    const std::vector<std::pair<std::string, std::vector<double>>>& axes)
{
    if (spec.block == 0) {
        throw Failure("--sweep with --train needs a block size");
    }
    Probe              probe(factory, sampleRate);
    std::vector<Param> params = resolveParams(probe, spec.params, spec.sets);
    checkLanes(probe, spec);
    // the trained control each axis drives
    std::vector<size_t> driven;
    for (const auto& axis : axes) {
        const std::string path  = resolved(probe, axis.first).path;
        size_t            index = params.size();
        for (size_t k = 0; k < params.size(); k++) {
            if (params[k].path == path) {
                index = k;
            }
        }
        if (index == params.size()) {
            throw Failure("--sweep `" + axis.first + "`: with --train, a swept control must be a trained one (" +
                          path + " is not); --set gives any other control a fixed value");
        }
        if (axis.second.empty()) {
            throw Failure("--sweep `" + axis.first + "` has no value");
        }
        if (std::find(driven.begin(), driven.end(), index) != driven.end()) {
            throw Failure("--sweep names `" + path + "` twice");
        }
        driven.push_back(index);
    }
    Channels x     = inputBlock(spec.input, probe.inputs(), 0, spec.block, sampleRate);
    size_t   total = 1;
    for (const auto& axis : axes) {
        total *= axis.second.size();
    }
    TrainGrid grid;
    for (size_t flat = 0; flat < total; flat++) {
        // the last axis varies fastest, as in a render sweep
        size_t              rest = flat;
        std::vector<double> at(axes.size(), 0.0);
        for (size_t axis = axes.size(); axis-- > 0;) {
            at[axis] = axes[axis].second[rest % axes[axis].second.size()];
            rest /= axes[axis].second.size();
        }
        probe.reset();
        applySets(probe, spec.sets);
        for (size_t k = 0; k < params.size(); k++) {
            double value = params[k].init;
            for (size_t axis = 0; axis < driven.size(); axis++) {
                if (driven[axis] == k) {
                    value = at[axis];
                }
            }
            probe.setExact(params[k].path, value);
        }
        std::vector<double> sums = laneSums(probe.computeRaw(x, spec.block));
        grid.points.push_back(std::make_pair(at, sums[spec.lossLane] / double(spec.block)));
    }
    bool found = false;
    for (size_t index = 0; index < grid.points.size(); index++) {
        double loss = grid.points[index].second;
        if (std::isfinite(loss) && (!found || loss < grid.points[grid.best].second)) {
            grid.best = index;
            found     = true;
        }
    }
    if (!found) {
        throw Failure("the loss is finite at no point of the grid");
    }
    for (size_t k : driven) {
        grid.paths.push_back(params[k].path);
    }
    return grid;
}

// The scheme whose points x, x +- h, x +- 2h stay in [min, max]: central when
// x +- h does, else one-sided, away from the bound.
static bool schemeWithin(double x, double h, double min, double max, FdScheme& scheme)
{
    if (x - h >= min && x + h <= max) {
        scheme = FdScheme::Central;
    } else if (x + 2.0 * h <= max) {
        scheme = FdScheme::Forward;
    } else if (x - 2.0 * h >= min) {
        scheme = FdScheme::Backward;
    } else {
        return false;
    }
    return true;
}

// Differences of the summed loss lane at steps h and h/2, extrapolated to a zero step
// (Richardson): a plain central difference is off by the third derivative times h^2/6,
// which does not shrink with the gradient and is all that is left at the end of a
// descent. A control is never set outside its range.
std::vector<FdCheck> fdCheck(const std::shared_ptr<Factory>& factory, int sampleRate, const TrainSpec& spec, double h,
                             const std::vector<double>* at)
{
    if (spec.block == 0) {
        throw Failure("--fd-check needs a block size");
    }
    std::vector<Param> params;
    size_t             inputs;
    {
        Probe probe(factory, sampleRate);
        checkLanes(probe, spec);
        params = resolveParams(probe, spec.params, spec.sets);
        inputs = probe.inputs();
    }
    Channels x = inputBlock(spec.input, inputs, 0, spec.block, sampleRate);
    // every evaluation on a fresh instance, so that the state is the same each time
    auto evaluate = [&](const std::vector<double>& values) {
        Probe probe(factory, sampleRate);
        applySets(probe, spec.sets);
        for (size_t k = 0; k < params.size(); k++) {
            probe.setExact(params[k].path, values[k]);
        }
        return laneSums(probe.computeRaw(x, spec.block));
    };
    std::vector<double> init;
    if (at != nullptr) {
        if (at->size() != params.size()) {
            throw Failure("--fd-check: " + str(at->size()) + " values for " + str(params.size()) +
                          " trained controls");
        }
        init = *at;
    } else {
        for (const Param& param : params) {
            init.push_back(param.init);
        }
    }
    std::vector<double>  base = evaluate(init);
    std::vector<FdCheck> checks;
    for (size_t k = 0; k < params.size(); k++) {
        const Param& param = params[k];
        FdScheme     scheme;
        if (!schemeWithin(init[k], h, param.min, param.max, scheme)) {
            throw Failure("--fd-check: " + param.path + " = " + plainNumber(init[k]) +
                          " has no finite difference of step " + plainNumber(h) + " inside its range [" +
                          plainNumber(param.min) + ", " + plainNumber(param.max) + "]: give a smaller --fd-step");
        }
        // the loss lane with control k moved by 'offset'
        auto lossAt = [&](double offset) {
            std::vector<double> values = init;
            values[k] += offset;
            return evaluate(values)[spec.lossLane];
        };
        double atX        = base[spec.lossLane];
        auto   difference = [&](double step) {
            switch (scheme) {
                case FdScheme::Central: {
                    double plus  = lossAt(step);
                    double minus = lossAt(-step);
                    return (plus - minus) / (2.0 * step);
                }
                case FdScheme::Forward: {
                    double one = lossAt(step);
                    double two = lossAt(2.0 * step);
                    return (-3.0 * atX + 4.0 * one - two) / (2.0 * step);
                }
                default: {
                    double one = lossAt(-step);
                    double two = lossAt(-2.0 * step);
                    return (3.0 * atX - 4.0 * one + two) / (2.0 * step);
                }
            }
        };
        FdCheck check;
        check.path          = param.path;
        check.scheme        = scheme;
        check.fdPlain       = difference(h);
        check.fd            = (4.0 * difference(h / 2.0) - check.fdPlain) / 3.0;
        check.rad           = base[spec.firstGradLane + k];
        check.relativeError = fabs(check.rad - check.fd) / std::max(fabs(check.fd), 1.0);
        checks.push_back(check);
    }
    return checks;
}
