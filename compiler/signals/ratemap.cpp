/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2010 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "ratemap.hpp"

void dump(RateMap const & rm)
{
    for (RateMap::const_iterator it = rm.begin(); it != rm.end(); ++it)
        cout << *(it->first) << '\t' << it->second << endl;
}

bool compatible(RateMap const & lhs, RateMap const & rhs)
{
    typedef RateMap::const_iterator ci;
    for (ci it = lhs.begin(); it != lhs.end(); ++it) {
        Tree key = it->first;
        ci key_in_rhs = rhs.find(key);
        if (key_in_rhs != rhs.end()) {
            if (it->second != key_in_rhs->second)
                return false;
        }
    }
    return true;
}

static RateMap doMerge(RateMap const & lhs, RateMap const & rhs)
{
    RateMap ret(lhs);

    for (RateMap::const_iterator it = rhs.begin(); it != rhs.end(); ++it)
        ret.insert(*it);
    return ret;
}

RateMap merge(RateMap const & lhs, RateMap const & rhs)
{
    if (lhs.empty())
        return rhs;
    if (rhs.empty())
        return lhs;

    if (!compatible(lhs, rhs))
        throw runtime_error("Error in rate propagation");

    return doMerge(lhs, rhs);
}

RateMap unify(RateMap const & lhs, RateMap const & rhs)
{
    rational factor = 0;

    /* two rate maps can be unified, if their elements just differ by a constant factor */
    typedef RateMap::const_iterator ci;
    for (ci it = lhs.begin(); it != lhs.end(); ++it) {
        Tree key = it->first;
        ci key_in_rhs = rhs.find(key);
        if (key_in_rhs != rhs.end()) {
            rational ration = it->second / key_in_rhs->second;
            if (factor == 0)
                factor = ration;
            else if (ration != factor)
                throw runtime_error("conflict for unifying rate maps");
        }
    }

    RateMap scaled_rhs = factor ? rhs * factor : rhs;
    RateMap ret = doMerge(scaled_rhs, lhs);
    return ret;
}

