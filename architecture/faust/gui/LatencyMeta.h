/************************** BEGIN LatencyMeta.h ***************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __LatencyMeta__
#define __LatencyMeta__

#include <cstdlib>
#include <cstring>

#include "faust/gui/meta.h"

/**
 * The latency a DSP adds to the signal path, as declared in its global metadata,
 * for a plugin architecture to report it to the host:
 *
 * - declare latency_samples "<frames>"; (or latency_frames)
 * - declare latency_sec "<seconds>"; converted with the host sample rate
 *
 * The compiler cannot know it: only the author of a lookahead or a linear phase
 * filter knows how much of the delay is on purpose.
 */
struct LatencyMeta : public Meta {

    double fFrames = 0.;
    double fSeconds = 0.;
    bool fDouble = false;   // the DSP computes in double precision

    void declare(const char* key, const char* value)
    {
        if (!strcmp(key, "latency_frames") || !strcmp(key, "latency_samples")) {
            fFrames = std::atof(value);
        } else if (!strcmp(key, "latency_sec")) {
            fSeconds = std::atof(value);
        } else if (!strcmp(key, "compile_options")) {
            fDouble = strstr(value, "-double") != nullptr;
        }
    }

    bool isDeclared() const { return fFrames > 0. || fSeconds > 0.; }

    // The latency in frames at this sample rate, 0 when none is declared
    int getFrames(double sample_rate) const
    {
        if (fFrames > 0.) {
            return int(fFrames);
        } else if (fSeconds > 0.) {
            // As @(ba.sec2samp(<seconds>)) delays the signal: the product is computed
            // in the precision of the DSP, and its fraction dropped (0.071 s at 48 kHz
            // is 3408 frames in single precision, 3407 in double)
            return fDouble ? int(fSeconds * sample_rate) : int(float(fSeconds) * float(sample_rate));
        } else {
            return 0;
        }
    }
};

#endif
/**************************  END  LatencyMeta.h **************************/
