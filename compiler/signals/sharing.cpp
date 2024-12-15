// /************************************************************************
//  ************************************************************************
//     FAUST compiler
//     Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
//     ---------------------------------------------------------------------
//     This program is free software; you can redistribute it and/or modify
//     it under the terms of the GNU Lesser General Public License as published by
//     the Free Software Foundation; either version 2.1 of the License, or
//     (at your option) any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Lesser General Public License for more details.

//     You should have received a copy of the GNU Lesser General Public License
//     along with this program; if not, write to the Free Software
//     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//  ************************************************************************
//  ************************************************************************/

// /*****************************************************************************
// ******************************************************************************
//                             FAUST SIGNAL COMPILER
//                         Y. Orlarey, (c) Grame 2002
// ------------------------------------------------------------------------------
//  History :
//  ---------
//     2002-02-08 : First version

// ******************************************************************************
// *****************************************************************************/

// #include <stdio.h>

// #include "sharing.hh"
// #include "sigtyperules.hh"

// using namespace std;

// /*****************************************************************************
// ******************************************************************************

//                                 SHARING ANALYSIS

// ******************************************************************************
// *****************************************************************************/

// static void setSharingCount(Tree sig, Tree key, int count)
// {
//     setProperty(sig, key, tree(count));
// }

// //------------------------------------------------------------------------------
// // Create a specific property key for the sharing count of subtrees of t
// //------------------------------------------------------------------------------

// // the test here is that sharing is not counted in regard to not attached trees that switch rate
// static void sharingAnnotation(int vctxt, Tree sig, Tree key, bool notattach)
// {
//     int count = getSharingCount(sig, key);
//     if (count > 0) {
//         cerr << endl << sig->node() << " " << "second is attach: "<< (sig->node() == gGlobal->SIGATTACH) << " s: "<< sig->node().type() << endl ;
//         // it is not our first visit
//         setSharingCount(sig, key, count + 1);

//     } else {
//         // it is our first visit,
//         int v = getCertifiedSigType(sig)->variability();

//         // check "time sharing" cases
//         if (v < vctxt && !notattach) {
//             cerr << endl << "v < vctxt:" << sig->node() <<endl;
//             setSharingCount(sig, key,
//                             2);  // time sharing occurence : slower expression in faster context
//         } else {
//             cerr << endl << "v >= vctxt:" << sig->node() <<endl;
//             setSharingCount(sig, key, 1);  // regular occurence
//         }

//         // Annotate the sub signals
//         tvec subsig;
//         //remove this for checking if occurrences can be always used
//         bool dropsecond = false;//(sig->node() == gGlobal->SIGATTACH);
//         int  n = getSubSignals(sig, subsig);
//         if (n > 0 && !isSigGen(sig)) {
//             for (int i = 0; i < n; i++) {
//                 if (dropsecond && i==1){
//                     sharingAnnotation(v, subsig[i], key,true);
//                 } else {
//                     sharingAnnotation(v, subsig[i], key,notattach);
//                 }
//             }
//         }
//     }
// }

// //------------------------------------------------------------------------------
// // Get the sharing count of sig
// //------------------------------------------------------------------------------

// int getSharingCount(Tree sig, Tree key)
// {
//     Tree c;
//     if (getProperty(sig, key, c)) {
//         cerr << endl << "is attach: "<< (sig->node() == gGlobal->SIGATTACH) << " s: "<< c->node().getInt() << endl ;
//         return c->node().getInt();
//     } else {
//         return 0;
//     }
// }

// //------------------------------------------------------------------------------
// // Create a specific property key for the sharing count of subtrees of sig
// //------------------------------------------------------------------------------

// void sharingAnalysis(Tree sig, Tree& key)
// {
//     key = shprkey(sig);

//     if (isList(sig)) {
//         while (isList(sig)) {
//             cerr << endl << "while:" << hd(sig)->node() <<endl;
//             sharingAnnotation(kSamp, hd(sig), key,false);
//             sig = tl(sig);
//         }
//     } else {
//         cerr << endl << "else:" << hd(sig)->node() <<endl;
//         sharingAnnotation(kSamp, sig, key,false);
//     }
// }
