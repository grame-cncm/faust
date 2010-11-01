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
#include <boost/rational.hpp>

typedef boost::rational<long> rational;

/** dictionary, mapping rate sources (i.e. trees) to factors
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
};

void dump(RateMap const &);

/** two rate maps are compatible, if they have no conflicting entry */
bool compatible(RateMap const & lhs, RateMap const & rhs);

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
    RateMap ret = *begin++;
    for (Iterator it = begin; it != end; ++it)
        ret = unify(ret, *it);
    return ret;
}


#endif
