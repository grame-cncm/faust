#pragma once

#include "sigs-export.hh"

// The standalone session of the signal library : init() builds what a
// compilation needs (the signal symbols, the property keys, the defaults of
// the options, a fresh type solver). The compiler does not call it -- its
// global.cpp performs the same steps in its own order -- ; standalone hosts
// and the tests call it after tlib::init(), once per session.
namespace sigs {
/// Standalone initialization of the whole signal library state (symbols,
/// property keys, type singletons, session state, option defaults). The
/// Faust compiler does NOT call it (global.cpp performs the same writes in
/// its own order); standalone hosts call it after tlib::init(), once per
/// session.
SIGS_API void init();
}  // namespace sigs
