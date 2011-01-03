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

#ifndef _RATEMAP_
#define _RATEMAP_

#include "tree.hh"

#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <boost/rational.hpp>

typedef boost::rational<long> rational;

/** dictionary, mapping rate sources (i.e. trees) to factors
 *
 *  a rate map is a vector in a multidimensional vector space. it is constructed from a
 *  number of Tree instances, which serve as an orthogonal basis.
 *
 *  properties: RateMaps are orthogonal, if they don't have a common base
 *              RateMaps are parallel, if one can be scaled to the other
 *
 * */
struct RateMap:
    map<Tree, rational>
{
    RateMap operator* (rational factor) const
    {
        RateMap ret;
        for (RateMap::const_iterator it = begin(); it != end(); ++it) {
            Tree n = it->first;
            rational rate = it->second;
            ret.insert(make_pair(n, rate * factor));
        }
        return ret;
    }

    rational length(void) const
    {
        rational ret = 0;
        for (RateMap::const_iterator it = begin(); it != end(); ++it)
            ret += it->second;
        return ret;
    }
};

void dump(RateMap const &);

/** two rate maps are orthogonal, if their constraints are independent */
bool orthogonal(RateMap const & lhs, RateMap const & rhs);

/** two rate maps are parallel, if their constraints only differ by a constant factor */
bool parallel(RateMap const & lhs, RateMap const & rhs);

/** two rate maps are compatible, if they have no conflicting entry */
bool compatible(RateMap const & lhs, RateMap const & rhs);

/** compute the factor to scale lhs to rhs. returns 0 if arguments are not parallel */
rational computeScaleFactor(RateMap const & lhs, RateMap const & rhs);

std::set<Tree> findCommonBases(RateMap const & lhs, RateMap const & rhs);

/** merge two rate maps
 *
 *  Throws, if rate maps are not compatible
 * */
RateMap merge(RateMap const & lhs, RateMap const & rhs);

/** unify two rate maps, rate maps can be unified, if common entries just differ by a certain factor.
 *
 *  Throws, if rate maps cannot be unified
 * */
RateMap unify(RateMap const & lhs, RateMap const & rhs);


/** merges rate maps in the range [begin, end[ */
template <typename Iterator>
static RateMap mergeRateMaps(Iterator begin, Iterator end)
{
    RateMap ret = *begin++;
    for (Iterator it = begin; it != end; ++it)
        ret = merge(ret, *it);
    return ret;
}



/** unifies rate maps in the range [begin, end[ */
template <typename Iterator>
static RateMap unifyRateMaps(Iterator begin, Iterator end)
{
    using namespace std;
    if (begin == end)
        return RateMap();

    RateMap ret = *begin++;

    for (Iterator it = begin; it != end; ++it) {
        RateMap const & currentRateMap = *it;

        set<Tree> commonBases = findCommonBases(currentRateMap, ret);

        rational factor = 0;
        for (set<Tree>::const_iterator baseIt = commonBases.begin(); baseIt != commonBases.end(); ++baseIt) {
            rational scaleInCurrent = currentRateMap.at(*baseIt);
            rational scaleInRet     = ret.at(*baseIt);
            rational newFactor = scaleInRet / scaleInCurrent;

            if (factor != 0 && factor != newFactor)
                throw logic_error("unable to unify rate maps");
            factor = newFactor;
        }

        if (commonBases.empty()) // FIXME: we should probably perform the unification incrementally
            factor = 1;

        RateMap scaled = currentRateMap * factor; // factors of the common basis match

        for (RateMap::const_iterator baseIt = scaled.begin(); baseIt != scaled.end(); ++baseIt) {
            Tree basis = baseIt->first;

            if (commonBases.find(basis) == commonBases.end())
                ret.insert(make_pair(basis, scaled.at(basis)));
            else
                assert(scaled.at(basis) == ret.at(basis));
        }
    }
    return ret;
}

#endif
