/************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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
    License along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Boston, MA  02110-1301  USA
 ************************************************************************/

#pragma once

#include <optional>

#include "signals.hh"

/**
 * NEVER TRANSFORM A GENERATOR.
 *
 * A table's content is filled once, at initialisation. No per-sample
 * transformation has any business inside it : the optimisation buys nothing
 * at run time, and rebuilding the generator costs.
 *
 * What it costs is the identity of the table. A table IS its generator's
 * signal tree -- generateStaticTable memoises on that tree and on nothing
 * else, never on the size and never on the content. So a generator that comes
 * back from a pass as a different tree is a different table. When a family
 * freezes the sub-trees it reads from the outside, a generator reached both
 * from a frozen node and from a free one is rebuilt on one side only : two
 * trees, one meaning, and the compiler emits the table twice. Measured on
 * glassHarmonica, tunedBar and tibetanBowl under -fam -fir : two static
 * tables of 65536 floats whose contents are bit-identical.
 *
 * The rule is written here, once, and every signal-level rewrite cuts its
 * descent with it. Written pass by pass it rots : seven passes run under
 * -fir, and cutting two of them left the fork exactly where it was.
 *
 * The cut is a top-down guard : the generator node decides its whole subtree,
 * its children are never visited, and the bottom-up rule is not applied to
 * it. The generator therefore comes out of the pass as the very pointer it
 * went in as, which is what makes the two sides coincide again.
 */
inline std::optional<Tree> sigGenCut(Tree t)
{
    return isSigGen(t) ? std::optional<Tree>(t) : std::nullopt;
}
