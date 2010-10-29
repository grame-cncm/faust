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

#include "sigtyperules.hh"
#include "sigrateinference.hh"
#include "xtended.hh"
#include "prim2.hh"

#include "ratemap.hpp"

/** \file sigrateinference.cpp signal rate inference
 *
 *  the signal rate inference algorithm is split into 2 phases: propagation,
 *  and simplification.
 *
 *  rate source:
 *  a rate source is a signal, that has no constraints for its signal rate.
 *
 *  propagation:
 *  during propagation, all signals are annotated with a rate map, depending
 *  on their input signals. propagation is done recursively though projections
 *  to infer the rate of recursive signals.
 *
 *  simplification:
 *  in the simplification phase, the signals are annotated with a normalized
 *  rate, that is computed from their rate maps. the normalized rate is an
 *  integer factor for the base rate.
 *
 **********************************************************************/

/** trees have a rate, if they are computed at audio rate */
static bool hasRate(Tree sig)
{
    Type t = sig->getType();
    if (t->variability() < kSamp)
        return false;
    else
        return true;
}

typedef map<Tree, RateMap> signalRateMap;  /// signal -> rateEnv

static void dump(signalRateMap const & srm)
{
    for (signalRateMap::const_iterator it = srm.begin(); it != srm.end(); ++it)
    {
        dump(it->first);
        dump(it->second);
        cout << endl;
    }
}

static signalRateMap gProjMap;
static signalRateMap gRateMap;


static RateMap initRate(Tree sig)
{
    RateMap ret;
    ret.insert(make_pair(sig, 1));
    return ret;
}

static RateMap doInferRateDispatch(Tree sig);

/* infere rate and store in global rate map */
static RateMap doInferRate(Tree sig)
{
    RateMap ret = doInferRateDispatch(sig);
    if (gRateMap.find(sig) == gRateMap.end())
        gRateMap.insert(make_pair(sig, ret));
    else
        gRateMap[sig] = merge(gRateMap[sig], ret);
    return ret;
}

static RateMap propagateRate(Tree sig)
{
    if (hasRate(sig))
        return doInferRate(sig);
    else
        return initRate(sig);
}

static RateMap propagateRate(Tree s1, Tree s2)
{
    if (!hasRate(s1))
        return propagateRate(s2);
    if (!hasRate(s2))
        return propagateRate(s1);

    // both signals are at audio rate
    RateMap i1 = doInferRate(s1);
    RateMap i2 = doInferRate(s2);

    return merge(i1, i2);
}

static RateMap propagateRate(Tree s1, Tree s2, Tree s3)
{
    if (!hasRate(s1))
        return propagateRate(s2, s3);
    if (!hasRate(s2))
        return propagateRate(s1, s3);
    if (!hasRate(s3))
        return propagateRate(s1, s2);

    // all signals are at audio rate
    RateMap i[3] = {
        doInferRate(s1),
        doInferRate(s2),
        doInferRate(s3)
    };

    return mergeRateMaps(i, i+3);
}

static RateMap propagateRate(Tree s1, Tree s2, Tree s3, Tree s4)
{
    if (!hasRate(s1))
        return propagateRate(s2, s3, s4);
    if (!hasRate(s2))
        return propagateRate(s1, s3, s4);
    if (!hasRate(s3))
        return propagateRate(s1, s2, s4);
    if (!hasRate(s4))
        return propagateRate(s1, s2, s3);

    // all signals are at audio rate
    RateMap i[4] = {
        doInferRate(s1),
        doInferRate(s2),
        doInferRate(s3),
        doInferRate(s4),
    };

    return mergeRateMaps(i, i+4);
}


static RateMap infereXRate(Tree sig)
{
    vector<RateMap> data;

    for (int i = 0; i < sig->arity(); i++) {
        Tree branch = sig->branch(i);

        if (hasRate(branch))
            data.push_back(doInferRate(branch));
        else
            data.push_back(initRate(branch));
    }

    RateMap ret = mergeRateMaps(data.begin(), data.end());
    return ret;
}

static RateMap infereFFRate (Tree ff, Tree ls)
{
    if (ffarity(ff)==0) {
        return initRate(ff);
    } else {
        vector<RateMap> vid;
        while (isList(ls)) {
            vid.push_back(doInferRate(hd(ls)));
            ls = tl(ls);
        }
        return mergeRateMaps(vid.begin(), vid.end());
    }
}

static Tree projKey(int i, Tree sym)
{
    return cons(tree(Node(i)), sym);
}

static RateMap infereProjRate(int i, Tree sig)
{
    Tree sym = sig->branch(0);
    Tree proj = projKey(i, sym);

    /* the first time, we find a projection, we use it as signal source, and infer its type
     */
    if (gProjMap.find(proj) == gProjMap.end()) {
        RateMap env = initRate(proj);
        gProjMap[proj] = env;

        RateMap infered = doInferRate(sig);

        assert(compatible(infered, env));
        return infered;
    } else
        return gProjMap[proj];
}

static RateMap infereRecRate(Tree var, Tree body)
{
    int size = len(body);

    vector<RateMap> vret;

    /* we infer all recursions and verify the correctness against the initial assumption for the signal source
     */
    for (int i = 0; i != size; ++i) {
        Tree proj = projKey(i, var);
        Tree n = nth(body, i);
        RateMap last;

        for (;;) {
            RateMap inferred = doInferRate(n);

            if (!compatible(inferred, gProjMap[proj])) {
                printf("Error in rate propagation\n");
                exit(1);
            }
            if (inferred == last)
                break;

            last = inferred;
        }
        vret.push_back(last);
    }

    RateMap ret = unifyRateMaps(vret.begin(), vret.end());

    return ret;
}

static RateMap infereVectorize(Tree s1, Tree s2)
{
    RateMap i1 = doInferRate(s1);
    int n = tree2int(s2);

    RateMap ret = i1 * rational(1, n);
    return ret;
}

static RateMap infereSerialize(Tree s1, Tree s2)
{
    RateMap i1 = doInferRate(s1);
    Type t1 = getSigType(s1);
    FaustVectorType * vt1 = isVectorType(t1.pointee());
    assert(vt1);
    RateMap ret = i1 * vt1->size();
    return ret;
}


RateMap doInferRateDispatch(Tree sig)
{
    int         i;
    double      r;
    Tree        sel, s1, s2, s3, ff, id, ls, l, x, y, z, u, var, body, type, name, file;
    Tree        label, cur, min, max, step;

         if ( getUserData(sig) )                        return infereXRate(sig);
    else if (isSigInt(sig, &i))                         return initRate(sig);
    else if (isSigReal(sig, &r))                        return initRate(sig);
    else if (isSigInput(sig, &i)) {
        RateMap ret;
        Tree inputTree = tree(Node(i));
        ret.insert(make_pair(inputTree, 1));
        return ret;
    }
    else if (isSigDelay1(sig, s1))                      return propagateRate(s1);
    else if (isSigPrefix(sig, s1, s2))                  return propagateRate(s1);
    else if (isSigFixDelay(sig, s1, s2))                return propagateRate(s1, s2);
    else if (isSigBinOp(sig, &i, s1, s2))               return propagateRate(s1, s2);
    else if (isSigIntCast(sig, s1))                     return propagateRate(s1);
    else if (isSigFloatCast(sig, s1))                   return propagateRate(s1);
    else if (isSigFFun(sig, ff, ls))                    return infereFFRate(ff, ls);
    else if (isSigFConst(sig,type,name,file))           return initRate(sig);
    else if (isSigFVar(sig,type,name,file))             return initRate(sig);
    else if (isSigButton(sig))                          return initRate(sig);
    else if (isSigCheckbox(sig))                        return initRate(sig);
    else if (isSigVSlider(sig,label,cur,min,max,step))  return initRate(sig);
    else if (isSigHSlider(sig,label,cur,min,max,step))  return initRate(sig);
    else if (isSigNumEntry(sig,label,cur,min,max,step)) return initRate(sig);
    else if (isSigHBargraph(sig, l, x, y, s1))          return initRate(sig);
    else if (isSigVBargraph(sig, l, x, y, s1))          return initRate(sig);
    else if (isSigAttach(sig, s1, s2))                  return propagateRate(s1, s2);
    else if (isRec(sig, var, body))                     return infereRecRate(var, body);
    else if (isProj(sig, &i, s1))                       return infereProjRate(i, s1);
    else if (isSigTable(sig, id, s1, s2))               return propagateRate(s2, s3);
    else if (isSigWRTbl(sig, id, s1, s2, s3))           return propagateRate(s1, s2, s3);
    else if (isSigRDTbl(sig, s1, s2))                   return propagateRate(s2);
    else if (isSigGen(sig, s1))                         return propagateRate(s1);
    else if (isSigDocConstantTbl(sig, x, y) )           return RateMap();
    else if (isSigDocWriteTbl(sig,x,y,z,u) )            return RateMap();
    else if (isSigDocAccessTbl(sig, x, y) )             return RateMap();
    else if (isSigSelect2(sig,sel,s1,s2))               return propagateRate(sel, s1, s2);
    else if (isSigSelect3(sig,sel,s1,s2,s3))            return propagateRate(sel, s1, s2, s3);
    else if (isList(sig)) {
        vector<RateMap> v;
        while (isList(sig)) {
            v.push_back(doInferRate(hd(sig)));
            sig = tl(sig);
        }
        RateMap ret = unifyRateMaps(v.begin(), v.end());
        return ret;
    }
    else if (isSigVectorize(sig, s1, s2))               return infereVectorize(s1, s2);
    else if (isSigSerialize(sig, s1))                   return infereSerialize(s1, s2);
    else if (isSigConcat(sig, s1, s2))                  return propagateRate(s1, s2);
    else if (isSigVectorAt(sig, s1, s2))                return propagateRate(s1, s2);

    printf("internal error");
    exit(1);
}


typedef map<Tree, rational> simplifiedRateMap;

/** normalizes rate map
 *
 *  - computes the rates, relative to a fundamental rate
 *  - normalizes the rates relative to the smallest rate in the graph
 *
 * \returns dictionary, mapping every signal to a normalized rate
 */
static simplifiedRateMap normalizeRateMap(RateMap const & rateFactors)
{
    simplifiedRateMap ret;

    for (signalRateMap::const_iterator it1 = gRateMap.begin(); it1 != gRateMap.end(); ++it1) {
        Tree sig = it1->first;
        RateMap const & e = it1->second;

        vector<rational> results;

        for (RateMap::const_iterator it2 = e.begin(); it2 != e.end(); ++it2) {
            Tree base = it2->first;
            rational const & r = it2->second;
            RateMap::const_iterator found = rateFactors.find(base);
            if (found != rateFactors.end()) {
                rational const & factor = found->second;
                rational val = r / factor;
                results.push_back(val);
            } else {
                results.push_back(r);
            }
        }
        assert(results.size());
        for (vector<rational>::const_iterator it = results.begin(); it != results.end(); ++it)
            assert(*it == results.front());

        ret.insert(make_pair(sig, results.front()));
    }

    long denom = 1;
    for (simplifiedRateMap::iterator it = ret.begin(); it != ret.end(); ++it)
        denom = boost::lcm(denom, it->second.denominator());

    for (simplifiedRateMap::iterator it = ret.begin(); it != ret.end(); ++it) {
        it->second = it->second * denom;
        assert(it->second.denominator() == 1);
        dump(it->first);
        cout << it->second.numerator() << endl << endl;
    }

    return ret;
}


Tree ratePropertyKey = tree(symbol("RateProperty"));

static void annotateRate(simplifiedRateMap const & map)
{
    for (simplifiedRateMap::const_iterator it = map.begin(); it != map.end(); ++it) {
        Tree sig = it->first;
        rational const & rate = it->second;
        assert(rate.denominator() == 1);
        int numerator = rate.numerator();

        setProperty(sig, ratePropertyKey, tree(Node(numerator)));
    }
}

void inferRate(Tree sig)
{
    RateMap data = doInferRate(sig);

    simplifiedRateMap rates = normalizeRateMap(data);

    annotateRate(rates);
}
