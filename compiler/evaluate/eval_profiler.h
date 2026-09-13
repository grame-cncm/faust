/************************************************************************
 ************************************************************************
    FAUST compiler - Evaluation profiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#ifndef __EVAL_PROFILER_H__
#define __EVAL_PROFILER_H__

#include <chrono>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <stack>

/**
 * Simple profiler to measure time spent in eval.cpp functions
 * Handles recursive calls correctly by using a stack of timers
 */
class EvalProfiler {
private:
    struct FunctionStats {
        std::string name;
        long long total_time_ns;  // Total time in nanoseconds
        long long call_count;
        long long self_time_ns;   // Time excluding child calls

        FunctionStats() : total_time_ns(0), call_count(0), self_time_ns(0) {}
    };

    struct CallFrame {
        std::string function_name;
        std::chrono::high_resolution_clock::time_point start_time;
        long long child_time_ns;  // Time spent in child calls

        CallFrame(const std::string& name)
            : function_name(name)
            , start_time(std::chrono::high_resolution_clock::now())
            , child_time_ns(0) {}
    };

    std::map<std::string, FunctionStats> stats;
    std::stack<CallFrame> call_stack;
    bool enabled;

public:
    static EvalProfiler& instance() {
        static EvalProfiler profiler;
        return profiler;
    }

    EvalProfiler() : enabled(false) {}

    void enable() { enabled = true; }
    void disable() { enabled = false; }
    bool is_enabled() const { return enabled; }

    void start(const std::string& function_name) {
        if (!enabled) return;

        call_stack.push(CallFrame(function_name));
        stats[function_name].call_count++;
    }

    void stop(const std::string& function_name) {
        if (!enabled) return;

        if (call_stack.empty()) {
            return;  // Should never happen but be safe
        }

        CallFrame frame = call_stack.top();
        call_stack.pop();

        // Calculate elapsed time
        auto end_time = std::chrono::high_resolution_clock::now();
        long long total_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
            end_time - frame.start_time).count();

        // Self time = total time - time spent in children
        long long self_duration = total_duration - frame.child_time_ns;

        // Update stats
        stats[function_name].total_time_ns += total_duration;
        stats[function_name].self_time_ns += self_duration;

        // Add this call's total duration to parent's child time
        if (!call_stack.empty()) {
            call_stack.top().child_time_ns += total_duration;
        }
    }

    void reset() {
        stats.clear();
        while (!call_stack.empty()) {
            call_stack.pop();
        }
    }

    void print_report(std::ostream& out = std::cerr) {
        if (stats.empty()) {
            out << "No profiling data collected." << std::endl;
            return;
        }

        // Convert to vector for sorting
        std::vector<std::pair<std::string, FunctionStats>> sorted_stats(stats.begin(), stats.end());

        // Sort by total time (descending)
        std::sort(sorted_stats.begin(), sorted_stats.end(),
                  [](const std::pair<std::string, FunctionStats>& a,
                     const std::pair<std::string, FunctionStats>& b) {
                      return a.second.total_time_ns > b.second.total_time_ns;
                  });

        out << "\n========== EVAL.CPP PROFILING REPORT ==========\n\n";

        // Calculate total time (use the first function's total time, usually evalprocess)
        long long total_time = 0;
        for (const auto& stat : sorted_stats) {
            total_time = std::max(total_time, stat.second.total_time_ns);
        }

        out << std::fixed << std::setprecision(3);
        out << std::left;
        out << std::setw(35) << "Function"
            << std::setw(15) << "Calls"
            << std::setw(18) << "Total Time (ms)"
            << std::setw(18) << "Self Time (ms)"
            << std::setw(15) << "Avg (μs)"
            << std::setw(10) << "% Total"
            << "\n";
        out << std::string(115, '-') << "\n";

        for (const auto& entry : sorted_stats) {
            const auto& name = entry.first;
            const auto& stat = entry.second;

            double total_ms = stat.total_time_ns / 1000000.0;
            double self_ms = stat.self_time_ns / 1000000.0;
            double avg_us = (stat.call_count > 0)
                ? (stat.total_time_ns / 1000.0) / stat.call_count
                : 0.0;
            double percent = (total_time > 0)
                ? (stat.total_time_ns * 100.0) / total_time
                : 0.0;

            out << std::setw(35) << name
                << std::setw(15) << stat.call_count
                << std::setw(18) << total_ms
                << std::setw(18) << self_ms
                << std::setw(15) << avg_us
                << std::setw(10) << percent
                << "\n";
        }

        out << std::string(115, '-') << "\n";
        out << "Total profiled time: " << (total_time / 1000000.0) << " ms\n";
        out << "\n===============================================\n\n";
    }
};

/**
 * RAII helper class for automatic timing
 */
class ScopedTimer {
private:
    std::string function_name;
    bool active;

public:
    ScopedTimer(const std::string& name) : function_name(name) {
        active = EvalProfiler::instance().is_enabled();
        if (active) {
            EvalProfiler::instance().start(function_name);
        }
    }

    ~ScopedTimer() {
        if (active) {
            EvalProfiler::instance().stop(function_name);
        }
    }
};

// Macro for easy instrumentation
#define PROFILE_FUNCTION() ScopedTimer __timer__(__FUNCTION__)
#define PROFILE_SCOPE(name) ScopedTimer __timer__##__LINE__(name)

#endif  // __EVAL_PROFILER_H__
