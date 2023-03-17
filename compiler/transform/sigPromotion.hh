/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef __SIGPROMOTION__
#define __SIGPROMOTION__

#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "sigIdentity.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"
#include "ppsig.hh"

/*
 Print the type of a signal.
 To be used on a type annotated signal.
 */
class SignalTypePrinter final : public SignalVisitor {
    
    private:
        std::vector<std::string> fPrinted;
        void visit(Tree sig) override;
        
    public:
        SignalTypePrinter(Tree L);

};

/*
 Check a signal:
 - for correct extended typing
 - for correct SigBinOp args typing
 - for proper SigIntCast and SigFloatCast use
 - for correct range in sliders (min < max and default in [min...max] range)
 - for use on control/enable (not available in -vec mode)
 - for proper simplication of sigLowest/sigHigest

 To be used on a type annotated signal.
*/
class SignalChecker final : public SignalVisitor {
    
    private:
        void visit(Tree sig) override;
    
        void isRange(Tree sig, Tree init_aux, Tree min_aux, Tree max_aux);
  
    public:
        SignalChecker(Tree L)
        {
            // Check that the root tree is properly type annotated
            getCertifiedSigType(L);
            visitRoot(L);
        }
};

//-------------------------SignalPromotion------------------------------
// Adds explicit int or float cast when needed. This is needed prior
// to any optimisations to avoid to scramble int and float expressions.
// To be used on a type annotated signal.
//----------------------------------------------------------------------
class SignalPromotion final : public SignalIdentity {
    
    private:
        Tree transformation(Tree sig);
        
        // Cast a sig to t1 if t1 != t2
        Tree smartCast(Type t1, Type t2, Tree sig);
        Tree smartCast(int t1, int t2, Tree sig);
        // Cast a sig to t
        Tree cast(Type t, Tree sig);
        Tree cast(int t, Tree sig);
        // Adds an intCast only if needed
        Tree smartIntCast(Type t, Tree sig);
        // Adds a floatCast only if needed
        Tree smartFloatCast(Type t, Tree sig);
    
    public:
        SignalPromotion()
        {
            // Go inside tables
            fVisitGen = true;
        }

};

//--------------------SignalBool2IntPromotion------------------
// Cast bool binary operations (comparison operations) to int.
//-------------------------------------------------------------
class SignalBool2IntPromotion final : public SignalIdentity {
    
    private:
        Tree transformation(Tree sig);

    public:
        SignalBool2IntPromotion()
        {
            // Go inside tables
            fVisitGen = true;
        }

};

//--------------------SignalFXPromotion------------------
// Special math function casting mode in -fx generation.
//-------------------------------------------------------------
class SignalFXPromotion final : public SignalIdentity {
    
    private:
        Tree transformation(Tree sig);
        
    public:
        SignalFXPromotion()
        {
            // Go inside tables
            fVisitGen = true;
        }
    
};

//-------------SignalIntCastPromotion---------------
// Float to integer conversion, checking the range.
//--------------------------------------------------
class SignalIntCastPromotion final : public SignalIdentity {
    
    private:
        Tree transformation(Tree sig);
        
    public:
        SignalIntCastPromotion()
        {
            // Go inside tables
            fVisitGen = true;
        }
    
};

//-------------------------SignalTablePromotion----------------------
// Generate safe access to rdtable/rwtable (wdx/rdx in [0..size-1]).
//-------------------------------------------------------------------
class SignalTablePromotion final : public SignalIdentity {
    
    private:
        Tree transformation(Tree sig);
    
        // Safe version of rtable/rwtable access
        Tree safeSigRDTbl(Tree sig, Tree tbl, Tree size, Tree ri);
        Tree safeSigWRTbl(Tree sig, Tree size, Tree gen, Tree wi, Tree ws);
    
    public:
        SignalTablePromotion()
        {
            // Go inside tables
            fVisitGen = true;
        }
    
};

//-------------------------SignalUIPromotion--------------------
// Generate safe access to range UI items (sliders and nentry).
//--------------------------------------------------------------
class SignalUIPromotion final : public SignalIdentity {
    
    private:
        Tree transformation(Tree sig);
            
    public:
        SignalUIPromotion()
        {
            // Go inside tables
            fVisitGen = true;
        }
    
};

//-------------------------SignalUIFreezePromotion---------------------------
// Freeze range UI items (sliders and nentry) to their init value. Everything
// that depends of sliders and nentry will be computed at compile time.
//---------------------------------------------------------------------------
class SignalUIFreezePromotion final : public SignalIdentity {
    
    private:
        Tree transformation(Tree sig);
        
    public:
        SignalUIFreezePromotion()
        {
            // Go inside tables
            fVisitGen = true;
        }
    
};

//-------------SignalFTZPromotion---------------
// The wrapping code allows to flush to zero denormalized number.
// This option should be used only when it is not available on the CPU.
//--------------------------------------------------
class SignalFTZPromotion final : public SignalIdentity {
    
    private:
    
        Tree selfRec(Tree t);
          
    public:
        SignalFTZPromotion()
        {
            // Go inside tables
            fVisitGen = true;
        }
    
};

// Public API
Tree signalPromote(Tree sig, bool trace = false);
Tree signalBool2IntPromote(Tree sig);
Tree signalFXPromote(Tree sig);
Tree signalTablePromote(Tree sig);
Tree signalIntCastPromote(Tree sig);
Tree signalUIPromote(Tree sig);
Tree signalUIFreezePromote(Tree sig);
Tree signalFTZPromote(Tree sig);
#endif
