-- --------------------------------------------------------------------
-- "fixed_float_types" package contains types used in the fixed and floating
-- point packages..
-- Please see the documentation for the floating point package.
-- This package should be compiled into "ieee_proposed" and used as follows:
--
--  This verison is designed to work with the VHDL-93 compilers.  Please
--  note the "%%%" comments.  These are where we diverge from the
--  VHDL-200X LRM.
--
-- --------------------------------------------------------------------
-- Version    : $Revision: 1.2 $
-- Date       : $Date: 2011/03/24 07:44:24 $
-- --------------------------------------------------------------------

package fixed_float_types is

  -- Types used for generics of fixed_generic_pkg
  
  type fixed_round_style_type is (fixed_round, fixed_truncate);
  
  type fixed_overflow_style_type is (fixed_saturate, fixed_wrap);

  -- Type used for generics of float_generic_pkg

  -- These are the same as the C FE_TONEAREST, FE_UPWARD, FE_DOWNWARD,
  -- and FE_TOWARDZERO floating point rounding macros.

  type round_type is (round_nearest,    -- Default, nearest LSB '0'
                      round_inf,        -- Round toward positive infinity
                      round_neginf,     -- Round toward negative infinity
                      round_zero);      -- Round toward zero (truncate)

end package fixed_float_types;

