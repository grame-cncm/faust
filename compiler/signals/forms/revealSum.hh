#pragma once

#include "signals.hh"

#include <unordered_map>

// throughShared : gather through the shared sub-sums (only when lowerSums follows).
// origins, when given, receives for every rebuilt node the node it came from (a
// revealed n-ary sum : the top of the binary chain it flattened ; a rebuilt group :
// the original group, recorded through its projections ; any node above them : its
// original), so that a plan made on the revealed tree can be carried out on the
// original one (the family form : LES-AUTOMATES).
// consumed, when given, receives for every revealed sum the original binary
// sums it absorbed below its origin (the chain flattened into it), so that a
// plan carried out on the original tree can skip them with the sum.
Tree revealSum(Tree L, bool throughShared = false, std::unordered_map<Tree, Tree>* origins = nullptr,
               std::unordered_map<Tree, std::vector<Tree>>* consumed = nullptr);
