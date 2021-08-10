-- --------------------------------------------------------------------
-- "float_pkg" package contains functions for floating point math.
-- Please see the documentation for the floating point package.
-- This package should be compiled into "ieee_proposed" and used as follows:
-- use ieee.std_logic_1164.all;
-- use ieee.numeric_std.all;
-- use ieee_proposed.fixed_float_types.all;
-- use ieee_proposed.fixed_pkg.all;
-- use ieee_proposed.float_pkg.all;
--
--  This verison is designed to work with the VHDL-93 compilers.  Please
--  note the "%%%" comments.  These are where we diverge from the
--  VHDL-200X LRM.
--
-- --------------------------------------------------------------------
-- Version    : $Revision: 1.1 $
-- Date       : $Date: 2012/03/09 20:36:50 $
-- --------------------------------------------------------------------

use STD.TEXTIO.all;
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;
use work.fixed_float_types.all;
use work.fixed_pkg.all;
--use ieee.fixed_pkg.all;

package float_pkg is
-- generic (
  -- Defaults for sizing routines, when you do a "to_float" this will be
  -- the default size.  Example float32 would be 8 and 23 (8 downto -23)
  constant float_exponent_width : NATURAL    := 8;
  constant float_fraction_width : NATURAL    := 23;
  -- Rounding algorithm, "round_nearest" is default, other valid values
  -- are "round_zero" (truncation), "round_inf" (round up), and
  -- "round_neginf" (round down)
  constant float_round_style    : round_type := round_nearest;
  -- Denormal numbers (very small numbers near zero) true or false
  constant float_denormalize    : BOOLEAN    := true;
  -- Turns on NAN processing (invalid numbers and overflow) true of false
  constant float_check_error    : BOOLEAN    := true;
  -- Guard bits are added to the bottom of every operation for rounding.
  -- any natural number (including 0) are valid.
  constant float_guard_bits     : NATURAL    := 3;
  -- If TRUE, then turn off warnings on "X" propagation
  constant no_warning : BOOLEAN := (false
                                                 );

  -- Author David Bishop (dbishop@vhdl.org)

  -- Note that the size of the vector is not defined here, but in
  -- the package which calls this one.
  type UNRESOLVED_float is array (INTEGER range <>) of STD_ULOGIC;  -- main type
  subtype U_float is UNRESOLVED_float;

  subtype float is UNRESOLVED_float;
  -----------------------------------------------------------------------------
  -- Use the float type to define your own floating point numbers.
  -- There must be a negative index or the packages will error out.
  -- Minimum supported is "subtype float7 is float (3 downto -3);"
  -- "subtype float16 is float (6 downto -9);" is probably the smallest
  -- practical one to use.
  -----------------------------------------------------------------------------

  -- IEEE 754 single precision
  subtype UNRESOLVED_float32 is UNRESOLVED_float (8 downto -23);
  alias U_float32 is UNRESOLVED_float32;
  subtype float32 is float (8 downto -23);
  -----------------------------------------------------------------------------
  -- IEEE-754 single precision floating point.  This is a "float"
  -- in C, and a FLOAT in Fortran.  The exponent is 8 bits wide, and
  -- the fraction is 23 bits wide.  This format can hold roughly 7 decimal
  -- digits.  Infinity is 2**127 = 1.7E38 in this number system.
  -- The bit representation is as follows:
  -- 1 09876543 21098765432109876543210
  -- 8 76543210 12345678901234567890123
  -- 0 00000000 00000000000000000000000
  -- 8 7      0 -1                  -23
  -- +/-   exp.  fraction
  -----------------------------------------------------------------------------

  -- IEEE 754 double precision
  subtype UNRESOLVED_float64 is UNRESOLVED_float (11 downto -52);
  alias U_float64 is UNRESOLVED_float64;
  subtype float64 is float (11 downto -52);
  -----------------------------------------------------------------------------
  -- IEEE-754 double precision floating point.  This is a "double float"
  -- in C, and a FLOAT*8 in Fortran.  The exponent is 11 bits wide, and
  -- the fraction is 52 bits wide.  This format can hold roughly 15 decimal
  -- digits.  Infinity is 2**2047 in this number system.
  -- The bit representation is as follows:
  --  3 21098765432 1098765432109876543210987654321098765432109876543210
  --  1 09876543210 1234567890123456789012345678901234567890123456789012
  --  S EEEEEEEEEEE FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
  -- 11 10        0 -1                                               -52
  -- +/-  exponent    fraction
  -----------------------------------------------------------------------------

  -- IEEE 854 & C extended precision
  subtype UNRESOLVED_float128 is UNRESOLVED_float (15 downto -112);
  alias U_float128 is UNRESOLVED_float128;
  subtype float128 is float (15 downto -112);
  -----------------------------------------------------------------------------
  -- The 128 bit floating point number is "long double" in C (on
  -- some systems this is a 70 bit floating point number) and FLOAT*32
  -- in Fortran.  The exponent is 15 bits wide and the fraction is 112
  -- bits wide. This number can handle approximately 33 decimal digits.
  -- Infinity is 2**32,767 in this number system.
  -----------------------------------------------------------------------------

  -- purpose: Checks for a valid floating point number
  type valid_fpstate is (nan,           -- Signaling NaN (C FP_NAN)
                         quiet_nan,     -- Quiet NaN (C FP_NAN)
                         neg_inf,       -- Negative infinity (C FP_INFINITE)
                         neg_normal,    -- negative normalized nonzero
                         neg_denormal,  -- negative denormalized (FP_SUBNORMAL)
                         neg_zero,      -- -0 (C FP_ZERO)
                         pos_zero,      -- +0 (C FP_ZERO)
                         pos_denormal,  -- Positive denormalized (FP_SUBNORMAL)
                         pos_normal,    -- positive normalized nonzero
                         pos_inf,       -- positive infinity
                         isx);          -- at least one input is unknown

  -- This deferred constant will tell you if the package body is synthesizable
  -- or implemented as real numbers.
  constant fphdlsynth_or_real : BOOLEAN;  -- deferred constant

  -- Returns the class which X falls into
  function Classfp (
    x           : UNRESOLVED_float;              -- floating point input
    check_error : BOOLEAN := float_check_error)  -- check for errors
    return valid_fpstate;

  -- Arithmetic functions, these operators do not require parameters.
  function "abs" (arg : UNRESOLVED_float) return UNRESOLVED_float;
  function "-" (arg   : UNRESOLVED_float) return UNRESOLVED_float;

  -- These allows the base math functions to use the default values
  -- of their parameters.  Thus they do full IEEE floating point.

  function "+" (l, r   : UNRESOLVED_float) return UNRESOLVED_float;
  function "-" (l, r   : UNRESOLVED_float) return UNRESOLVED_float;
  function "*" (l, r   : UNRESOLVED_float) return UNRESOLVED_float;
  function "/" (l, r   : UNRESOLVED_float) return UNRESOLVED_float;
  function "rem" (l, r : UNRESOLVED_float) return UNRESOLVED_float;
  function "mod" (l, r : UNRESOLVED_float) return UNRESOLVED_float;

  -- Basic parameter list
  -- round_style - Selects the rounding algorithm to use
  -- guard - extra bits added to the end if the operation to add precision
  -- check_error - When "false" turns off NAN and overflow checks
  -- denormalize - When "false" turns off denormal number processing

  function add (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  function subtract (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  function multiply (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  function divide (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  function remainder (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  function modulo (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  -- reciprocal
  function reciprocal (
    arg                  : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  function dividebyp2 (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  -- Multiply accumulate  result = l*r + c
  function mac (
    l, r, c              : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  -- Square root (all 754 based implementations need this)
  function sqrt (
    arg                  : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;
    constant guard       : NATURAL    := float_guard_bits;
    constant check_error : BOOLEAN    := float_check_error;
    constant denormalize : BOOLEAN    := float_denormalize)
    return UNRESOLVED_float;

  function Is_Negative (arg : UNRESOLVED_float) return BOOLEAN;

  -----------------------------------------------------------------------------
  -- compare functions
  -- =, /=, >=, <=, <, >, maximum, minimum

  function eq (                               -- equal =
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN;

  function ne (                               -- not equal /=
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN;

  function lt (                               -- less than <
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN;

  function gt (                               -- greater than >
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN;

  function le (                               -- less than or equal to <=
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN;

  function ge (                               -- greater than or equal to >=
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN;

  -- Need to overload the default versions of these
  function "="  (l, r : UNRESOLVED_float) return BOOLEAN;
  function "/=" (l, r : UNRESOLVED_float) return BOOLEAN;
  function ">=" (l, r : UNRESOLVED_float) return BOOLEAN;
  function "<=" (l, r : UNRESOLVED_float) return BOOLEAN;
  function ">"  (l, r : UNRESOLVED_float) return BOOLEAN;
  function "<"  (l, r : UNRESOLVED_float) return BOOLEAN;

  function \?=\  (l, r : UNRESOLVED_float) return STD_ULOGIC;
  function \?/=\ (l, r : UNRESOLVED_float) return STD_ULOGIC;
  function \?>\  (l, r : UNRESOLVED_float) return STD_ULOGIC;
  function \?>=\ (l, r : UNRESOLVED_float) return STD_ULOGIC;
  function \?<\  (l, r : UNRESOLVED_float) return STD_ULOGIC;
  function \?<=\ (l, r : UNRESOLVED_float) return STD_ULOGIC;

  function std_match (l, r     : UNRESOLVED_float) return BOOLEAN;
  function find_rightmost (arg : UNRESOLVED_float; y : STD_ULOGIC)
    return INTEGER;
  function find_leftmost (arg : UNRESOLVED_float; y : STD_ULOGIC)
    return INTEGER;
  function maximum (l, r : UNRESOLVED_float) return UNRESOLVED_float;
  function minimum (l, r : UNRESOLVED_float) return UNRESOLVED_float;

  -- conversion functions
  -- Converts one floating point number into another.

  function resize (
    arg                     : UNRESOLVED_float;  -- Floating point input
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  function resize (
    arg                     : UNRESOLVED_float;  -- Floating point input
    size_res                : UNRESOLVED_float;
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  function to_float32 (
    arg                     : UNRESOLVED_float;
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float32;

  function to_float64 (
    arg                     : UNRESOLVED_float;
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float64;

  function to_float128 (
    arg                     : UNRESOLVED_float;
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float128;

  -- Converts an fp into an SLV (needed for synthesis)
  function to_slv (arg : UNRESOLVED_float) return STD_LOGIC_VECTOR;
  alias to_StdLogicVector is to_slv [UNRESOLVED_float return STD_LOGIC_VECTOR];
  alias to_Std_Logic_Vector is to_slv [UNRESOLVED_float return STD_LOGIC_VECTOR];

  -- Converts an fp into an std_ulogic_vector (sulv)
  function to_sulv (arg : UNRESOLVED_float) return STD_ULOGIC_VECTOR;
  alias to_StdULogicVector is to_sulv [UNRESOLVED_float return STD_ULOGIC_VECTOR];
  alias to_Std_ULogic_Vector is to_sulv [UNRESOLVED_float return STD_ULOGIC_VECTOR];

  -- std_ulogic_vector to float
  function to_float (
    arg                     : STD_ULOGIC_VECTOR;
    constant exponent_width : NATURAL := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- length of FP output fraction
    return UNRESOLVED_float;

  -- Integer to float
  function to_float (
    arg                     : INTEGER;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float;

  -- real to float
  function to_float (
    arg                     : REAL;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  -- unsigned to float
  function to_float (
    arg                     : UNSIGNED;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float;

  -- signed to float
  function to_float (
    arg                     : SIGNED;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float;

  -- unsigned fixed point to float
  function to_float (
    arg                     : UNRESOLVED_ufixed;  -- unsigned fixed point input
    constant exponent_width : NATURAL    := float_exponent_width;  -- width of exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- width of fraction
    constant round_style    : round_type := float_round_style;  -- rounding
    constant denormalize    : BOOLEAN    := float_denormalize)  -- use ieee extensions
    return UNRESOLVED_float;

  -- signed fixed point to float
  function to_float (
    arg                     : UNRESOLVED_sfixed;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style;  -- rounding
    constant denormalize    : BOOLEAN    := float_denormalize)  -- rounding option
    return UNRESOLVED_float;

  -- size_res functions
  -- Integer to float
  function to_float (
    arg                  : INTEGER;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float;

  -- real to float
  function to_float (
    arg                  : REAL;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style;  -- rounding option
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  -- unsigned to float
  function to_float (
    arg                  : UNSIGNED;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float;

  -- signed to float
  function to_float (
    arg                  : SIGNED;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float;

  -- sulv to float
  function to_float (
    arg      : STD_ULOGIC_VECTOR;
    size_res : UNRESOLVED_float)
    return UNRESOLVED_float;

  -- unsigned fixed point to float
  function to_float (
    arg                  : UNRESOLVED_ufixed;  -- unsigned fixed point input
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style;  -- rounding
    constant denormalize : BOOLEAN    := float_denormalize)  -- use ieee extensions
    return UNRESOLVED_float;

  -- signed fixed point to float
  function to_float (
    arg                  : UNRESOLVED_sfixed;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style;  -- rounding
    constant denormalize : BOOLEAN    := float_denormalize)  -- rounding option
    return UNRESOLVED_float;

  -- float to unsigned
  function to_unsigned (
    arg                  : UNRESOLVED_float;  -- floating point input
    constant size        : NATURAL;     -- length of output
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return UNSIGNED;

  -- float to signed
  function to_signed (
    arg                  : UNRESOLVED_float;  -- floating point input
    constant size        : NATURAL;     -- length of output
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return SIGNED;

  -- purpose: Converts a float to unsigned fixed point
  function to_ufixed (
    arg                     : UNRESOLVED_float;  -- fp input
    constant left_index     : INTEGER;  -- integer part
    constant right_index    : INTEGER;  -- fraction part
    constant overflow_style : fixed_overflow_style_type := fixed_overflow_style;  -- saturate
    constant round_style    : fixed_round_style_type    := fixed_round_style;  -- rounding
    constant check_error    : BOOLEAN                   := float_check_error;  -- check for errors
    constant denormalize    : BOOLEAN                   := float_denormalize)
    return UNRESOLVED_ufixed;

  -- float to signed fixed point
  function to_sfixed (
    arg                     : UNRESOLVED_float;  -- fp input
    constant left_index     : INTEGER;  -- integer part
    constant right_index    : INTEGER;  -- fraction part
    constant overflow_style : fixed_overflow_style_type := fixed_overflow_style;  -- saturate
    constant round_style    : fixed_round_style_type    := fixed_round_style;  -- rounding
    constant check_error    : BOOLEAN                   := float_check_error;  -- check for errors
    constant denormalize    : BOOLEAN                   := float_denormalize)
    return UNRESOLVED_sfixed;

  -- size_res versions
  -- float to unsigned
  function to_unsigned (
    arg                  : UNRESOLVED_float;  -- floating point input
    size_res             : UNSIGNED;
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return UNSIGNED;

  -- float to signed
  function to_signed (
    arg                  : UNRESOLVED_float;  -- floating point input
    size_res             : SIGNED;
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return SIGNED;

  -- purpose: Converts a float to unsigned fixed point
  function to_ufixed (
    arg                     : UNRESOLVED_float;  -- fp input
    size_res                : UNRESOLVED_ufixed;
    constant overflow_style : fixed_overflow_style_type := fixed_overflow_style;  -- saturate
    constant round_style    : fixed_round_style_type    := fixed_round_style;  -- rounding
    constant check_error    : BOOLEAN                   := float_check_error;  -- check for errors
    constant denormalize    : BOOLEAN                   := float_denormalize)
    return UNRESOLVED_ufixed;

  -- float to signed fixed point
  function to_sfixed (
    arg                     : UNRESOLVED_float;  -- fp input
    size_res                : UNRESOLVED_sfixed;
    constant overflow_style : fixed_overflow_style_type := fixed_overflow_style;  -- saturate
    constant round_style    : fixed_round_style_type    := fixed_round_style;  -- rounding
    constant check_error    : BOOLEAN                   := float_check_error;  -- check for errors
    constant denormalize    : BOOLEAN                   := float_denormalize)
    return UNRESOLVED_sfixed;

  -- float to real
  function to_real (
    arg                  : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return REAL;

  -- float to integer
  function to_integer (
    arg                  : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return INTEGER;

  -- For Verilog compatability
  function realtobits (arg : REAL) return STD_ULOGIC_VECTOR;
  function bitstoreal (arg : STD_ULOGIC_VECTOR) return REAL;

  -- Maps metalogical values
  function to_01 (
    arg  : UNRESOLVED_float;            -- floating point input
    XMAP : STD_LOGIC := '0')
    return UNRESOLVED_float;

  function Is_X (arg    : UNRESOLVED_float) return BOOLEAN;
  function to_X01 (arg  : UNRESOLVED_float) return UNRESOLVED_float;
  function to_X01Z (arg : UNRESOLVED_float) return UNRESOLVED_float;
  function to_UX01 (arg : UNRESOLVED_float) return UNRESOLVED_float;

  -- These two procedures were copied out of the body because they proved
  -- very useful for vendor specific algorithm development
  -- Break_number converts a floating point number into it's parts
  -- Exponent is biased by -1

  procedure break_number (
    arg         : in  UNRESOLVED_float;
    denormalize : in  BOOLEAN := float_denormalize;
    check_error : in  BOOLEAN := float_check_error;
    fract       : out UNSIGNED;
    expon       : out SIGNED;  -- NOTE:  Add 1 to get the real exponent!
    sign        : out STD_ULOGIC);

  procedure break_number (
    arg         : in  UNRESOLVED_float;
    denormalize : in  BOOLEAN := float_denormalize;
    check_error : in  BOOLEAN := float_check_error;
    fract       : out ufixed;           -- a number between 1.0 and 2.0
    expon       : out SIGNED;  -- NOTE:  Add 1 to get the real exponent!
    sign        : out STD_ULOGIC);

  -- Normalize takes a fraction and and exponent and converts them into
  -- a floating point number.  Does the shifting and the rounding.
  -- Exponent is assumed to be biased by -1

  function normalize (
    fract                   : UNSIGNED;           -- fraction, unnormalized
    expon                   : SIGNED;   -- exponent - 1, normalized
    sign                    : STD_ULOGIC;         -- sign bit
    sticky                  : STD_ULOGIC := '0';  -- Sticky bit (rounding)
    constant exponent_width : NATURAL    := float_exponent_width;  -- size of output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- size of output fraction
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant denormalize    : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant nguard         : NATURAL    := float_guard_bits)   -- guard bits
    return UNRESOLVED_float;

  -- Exponent is assumed to be biased by -1
  function normalize (
    fract                   : ufixed;   -- unsigned fixed point
    expon                   : SIGNED;   -- exponent - 1, normalized
    sign                    : STD_ULOGIC;         -- sign bit
    sticky                  : STD_ULOGIC := '0';  -- Sticky bit (rounding)
    constant exponent_width : NATURAL    := float_exponent_width;  -- size of output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- size of output fraction
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant denormalize    : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant nguard         : NATURAL    := float_guard_bits)   -- guard bits
    return UNRESOLVED_float;

  function normalize (
    fract                : UNSIGNED;    -- unsigned
    expon                : SIGNED;      -- exponent - 1, normalized
    sign                 : STD_ULOGIC;  -- sign bit
    sticky               : STD_ULOGIC := '0';  -- Sticky bit (rounding)
    size_res             : UNRESOLVED_float;   -- used for sizing only
    constant round_style : round_type := float_round_style;  -- rounding option
    constant denormalize : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant nguard      : NATURAL    := float_guard_bits)   -- guard bits
    return UNRESOLVED_float;

  -- Exponent is assumed to be biased by -1
  function normalize (
    fract                : ufixed;      -- unsigned fixed point
    expon                : SIGNED;      -- exponent - 1, normalized
    sign                 : STD_ULOGIC;  -- sign bit
    sticky               : STD_ULOGIC := '0';  -- Sticky bit (rounding)
    size_res             : UNRESOLVED_float;   -- used for sizing only
    constant round_style : round_type := float_round_style;  -- rounding option
    constant denormalize : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant nguard      : NATURAL    := float_guard_bits)   -- guard bits
    return UNRESOLVED_float;

  -- overloaded versions
  function "+"   (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float;
  function "+"   (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "+"   (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float;
  function "+"   (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "-"   (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float;
  function "-"   (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "-"   (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float;
  function "-"   (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "*"   (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float;
  function "*"   (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "*"   (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float;
  function "*"   (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "/"   (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float;
  function "/"   (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "/"   (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float;
  function "/"   (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "rem" (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float;
  function "rem" (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "rem" (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float;
  function "rem" (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "mod" (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float;
  function "mod" (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float;
  function "mod" (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float;
  function "mod" (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float;

  -- overloaded compare functions
  function "="   (l : UNRESOLVED_float; r : REAL) return BOOLEAN;
  function "/="  (l : UNRESOLVED_float; r : REAL) return BOOLEAN;
  function ">="  (l : UNRESOLVED_float; r : REAL) return BOOLEAN;
  function "<="  (l : UNRESOLVED_float; r : REAL) return BOOLEAN;
  function ">"   (l : UNRESOLVED_float; r : REAL) return BOOLEAN;
  function "<"   (l : UNRESOLVED_float; r : REAL) return BOOLEAN;
  function "="   (l : REAL; r : UNRESOLVED_float) return BOOLEAN;
  function "/="  (l : REAL; r : UNRESOLVED_float) return BOOLEAN;
  function ">="  (l : REAL; r : UNRESOLVED_float) return BOOLEAN;
  function "<="  (l : REAL; r : UNRESOLVED_float) return BOOLEAN;
  function ">"   (l : REAL; r : UNRESOLVED_float) return BOOLEAN;
  function "<"   (l : REAL; r : UNRESOLVED_float) return BOOLEAN;
  function "="   (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN;
  function "/="  (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN;
  function ">="  (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN;
  function "<="  (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN;
  function ">"   (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN;
  function "<"   (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN;
  function "="   (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN;
  function "/="  (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN;
  function ">="  (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN;
  function "<="  (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN;
  function ">"   (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN;
  function "<"   (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN;
  function \?=\  (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC;
  function \?/=\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC;
  function \?>\  (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC;
  function \?>=\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC;
  function \?<\  (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC;
  function \?<=\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC;
  function \?=\  (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?/=\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?>\  (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?>=\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?<\  (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?<=\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?=\  (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC;
  function \?/=\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC;
  function \?>\  (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC;
  function \?>=\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC;
  function \?<\  (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC;
  function \?<=\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC;
  function \?=\  (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?/=\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?>\  (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?>=\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?<\  (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC;
  function \?<=\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC;
  -- minimum and maximum overloads
  function maximum (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float;
  function minimum (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float;
  function maximum (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float;
  function minimum (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float;
  function maximum (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float;
  function minimum (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float;
  function maximum (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float;
  function minimum (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float;
----------------------------------------------------------------------------
  -- logical functions
  ----------------------------------------------------------------------------

  function "not"  (l    : UNRESOLVED_float) return UNRESOLVED_float;
  function "and"  (l, r : UNRESOLVED_float) return UNRESOLVED_float;
  function "or"   (l, r : UNRESOLVED_float) return UNRESOLVED_float;
  function "nand" (l, r : UNRESOLVED_float) return UNRESOLVED_float;
  function "nor"  (l, r : UNRESOLVED_float) return UNRESOLVED_float;
  function "xor"  (l, r : UNRESOLVED_float) return UNRESOLVED_float;
  function "xnor" (l, r : UNRESOLVED_float) return UNRESOLVED_float;
  -- Vector and std_ulogic functions, same as functions in numeric_std
  function "and" (l : STD_ULOGIC; r : UNRESOLVED_float)
    return UNRESOLVED_float;
  function "and" (l : UNRESOLVED_float; r : STD_ULOGIC)
    return UNRESOLVED_float;
  function "or" (l : STD_ULOGIC; r : UNRESOLVED_float)
    return UNRESOLVED_float;
  function "or" (l : UNRESOLVED_float; r : STD_ULOGIC)
    return UNRESOLVED_float;
  function "nand" (l : STD_ULOGIC; r : UNRESOLVED_float)
    return UNRESOLVED_float;
  function "nand" (l : UNRESOLVED_float; r : STD_ULOGIC)
    return UNRESOLVED_float;
  function "nor" (l : STD_ULOGIC; r : UNRESOLVED_float)
    return UNRESOLVED_float;
  function "nor" (l : UNRESOLVED_float; r : STD_ULOGIC)
    return UNRESOLVED_float;
  function "xor" (l : STD_ULOGIC; r : UNRESOLVED_float)
    return UNRESOLVED_float;
  function "xor" (l : UNRESOLVED_float; r : STD_ULOGIC)
    return UNRESOLVED_float;
  function "xnor" (l : STD_ULOGIC; r : UNRESOLVED_float)
    return UNRESOLVED_float;
  function "xnor" (l : UNRESOLVED_float; r : STD_ULOGIC)
    return UNRESOLVED_float;
  -- Reduction operators, same as numeric_std functions
  function and_reduce  (l : UNRESOLVED_float) return STD_ULOGIC;
  function nand_reduce (l : UNRESOLVED_float) return STD_ULOGIC;
  function or_reduce   (l : UNRESOLVED_float) return STD_ULOGIC;
  function nor_reduce  (l : UNRESOLVED_float) return STD_ULOGIC;
  function xor_reduce  (l : UNRESOLVED_float) return STD_ULOGIC;
  function xnor_reduce (l : UNRESOLVED_float) return STD_ULOGIC;

  -- Note: "sla", "sra", "sll", "slr", "rol" and "ror" not implemented.

  -----------------------------------------------------------------------------
  -- Recommended Functions from the IEEE 754 Appendix
  -----------------------------------------------------------------------------

  -- returns x with the sign of y.
  function Copysign (x, y : UNRESOLVED_float) return UNRESOLVED_float;

  -- Returns y * 2**n for integral values of N without computing 2**n
  function Scalb (
    y                    : UNRESOLVED_float;  -- floating point input
    N                    : INTEGER;     -- exponent to add    
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  -- Returns y * 2**n for integral values of N without computing 2**n
  function Scalb (
    y                    : UNRESOLVED_float;  -- floating point input
    N                    : SIGNED;      -- exponent to add    
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float;

  -- returns the unbiased exponent of x
  function Logb (x : UNRESOLVED_float) return INTEGER;
  function Logb (x : UNRESOLVED_float) return SIGNED;

  -- returns the next representable neighbor of x in the direction toward y
  function Nextafter (
    x, y                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN := float_denormalize)
    return UNRESOLVED_float;

  -- Returns TRUE if X is unordered with Y.
  function Unordered (x, y : UNRESOLVED_float) return BOOLEAN;
  function Finite (x       : UNRESOLVED_float) return BOOLEAN;
  function Isnan (x        : UNRESOLVED_float) return BOOLEAN;

  -- Function to return constants.
  function zerofp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float;
  function nanfp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float;
  function qnanfp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float;
  function pos_inffp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float;
  function neg_inffp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float;
  function neg_zerofp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float;
  -- size_res versions
  function zerofp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float;
  function nanfp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float;
  function qnanfp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float;
  function pos_inffp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float;
  function neg_inffp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float;
  function neg_zerofp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float;

  -- ===========================================================================
  -- string and textio Functions
  -- ===========================================================================
-- rtl_synthesis off
-- pragma synthesis_off
  -- writes S:EEEE:FFFFFFFF
  procedure WRITE (
    L         : inout LINE;              -- access type (pointer)
    VALUE     : in    UNRESOLVED_float;  -- value to write
    JUSTIFIED : in    SIDE  := right;    -- which side to justify text
    FIELD     : in    WIDTH := 0);       -- width of field

  -- Reads SEEEEFFFFFFFF, "." and ":" are ignored
  procedure READ (L : inout LINE; VALUE : out UNRESOLVED_float);
  procedure READ (L    : inout LINE; VALUE : out UNRESOLVED_float;
                  GOOD : out   BOOLEAN);

  alias BREAD is READ [LINE, UNRESOLVED_float, BOOLEAN];
  alias BREAD is READ [LINE, UNRESOLVED_float];
  alias BWRITE is WRITE [LINE, UNRESOLVED_float, SIDE, WIDTH];
  alias BINARY_READ is READ [LINE, UNRESOLVED_FLOAT, BOOLEAN];
  alias BINARY_READ is READ [LINE, UNRESOLVED_FLOAT];
  alias BINARY_WRITE is WRITE [LINE, UNRESOLVED_float, SIDE, WIDTH];

  procedure OWRITE (
    L         : inout LINE;              -- access type (pointer)
    VALUE     : in    UNRESOLVED_float;  -- value to write
    JUSTIFIED : in    SIDE  := right;    -- which side to justify text
    FIELD     : in    WIDTH := 0);       -- width of field

  -- Octal read with padding, no separators used
  procedure OREAD (L : inout LINE; VALUE : out UNRESOLVED_float);
  procedure OREAD (L    : inout LINE; VALUE : out UNRESOLVED_float;
                   GOOD : out   BOOLEAN);
  alias OCTAL_READ is OREAD [LINE, UNRESOLVED_FLOAT, BOOLEAN];
  alias OCTAL_READ is OREAD [LINE, UNRESOLVED_FLOAT];
  alias OCTAL_WRITE is OWRITE [LINE, UNRESOLVED_FLOAT, SIDE, WIDTH];

  -- Hex write with padding, no separators
  procedure HWRITE (
    L         : inout LINE;              -- access type (pointer)
    VALUE     : in    UNRESOLVED_float;  -- value to write
    JUSTIFIED : in    SIDE  := right;    -- which side to justify text
    FIELD     : in    WIDTH := 0);       -- width of field

  -- Hex read with padding, no separators used
  procedure HREAD (L : inout LINE; VALUE : out UNRESOLVED_float);
  procedure HREAD (L    : inout LINE; VALUE : out UNRESOLVED_float;
                   GOOD : out   BOOLEAN);
  alias HEX_READ is HREAD [LINE, UNRESOLVED_FLOAT, BOOLEAN];
  alias HEX_READ is HREAD [LINE, UNRESOLVED_FLOAT];
  alias HEX_WRITE is HWRITE [LINE, UNRESOLVED_FLOAT, SIDE, WIDTH];

  -- returns "S:EEEE:FFFFFFFF"
  function to_string (value : UNRESOLVED_float) return STRING;
  alias TO_BSTRING is TO_STRING [UNRESOLVED_FLOAT return STRING];
  alias TO_BINARY_STRING is TO_STRING [UNRESOLVED_FLOAT return STRING];

  -- Returns a HEX string, with padding
  function to_hstring (value : UNRESOLVED_float) return STRING;
  alias TO_HEX_STRING is TO_HSTRING [UNRESOLVED_FLOAT return STRING];

  -- Returns and octal string, with padding
  function to_ostring (value : UNRESOLVED_float) return STRING;
  alias TO_OCTAL_STRING is TO_OSTRING [UNRESOLVED_FLOAT return STRING];

  function from_string (
    bstring                 : STRING;   -- binary string
    constant exponent_width : NATURAL := float_exponent_width;
    constant fraction_width : NATURAL := float_fraction_width)
    return UNRESOLVED_float;
  alias from_bstring is from_string [STRING, NATURAL, NATURAL
                                     return UNRESOLVED_float];
  alias from_binary_string is from_string [STRING, NATURAL, NATURAL
                                           return UNRESOLVED_float];
  function from_ostring (
    ostring                 : STRING;   -- Octal string
    constant exponent_width : NATURAL := float_exponent_width;
    constant fraction_width : NATURAL := float_fraction_width)
    return UNRESOLVED_float;
  alias from_octal_string is from_ostring [STRING, NATURAL, NATURAL
                                           return UNRESOLVED_float];

  function from_hstring (
    hstring                 : STRING;   -- hex string
    constant exponent_width : NATURAL := float_exponent_width;
    constant fraction_width : NATURAL := float_fraction_width)
    return UNRESOLVED_float;
  alias from_hex_string is from_hstring [STRING, NATURAL, NATURAL
                                         return UNRESOLVED_float];

  function from_string (
    bstring  : STRING;                  -- binary string
    size_res : UNRESOLVED_float)        -- used for sizing only 
    return UNRESOLVED_float;
  alias from_bstring is from_string [STRING, UNRESOLVED_float
                                     return UNRESOLVED_float];
  alias from_binary_string is from_string [STRING, UNRESOLVED_float
                                           return UNRESOLVED_float];

  function from_ostring (
    ostring  : STRING;                  -- Octal string
    size_res : UNRESOLVED_float)        -- used for sizing only 
    return UNRESOLVED_float;
  alias from_octal_string is from_ostring [STRING, UNRESOLVED_float
                                           return UNRESOLVED_float];

  function from_hstring (
    hstring  : STRING;                  -- hex string
    size_res : UNRESOLVED_float)        -- used for sizing only 
    return UNRESOLVED_float;
  alias from_hex_string is from_hstring [STRING, UNRESOLVED_float
                                         return UNRESOLVED_float];
-- rtl_synthesis on
-- pragma synthesis_on
  -- IN VHDL-2006 std_logic_vector is a subtype of std_ulogic_vector, so these
  -- extra functions are needed for compatability.
  function to_float (
    arg                     : STD_LOGIC_VECTOR;
    constant exponent_width : NATURAL := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- length of FP output fraction
    return UNRESOLVED_float;

  function to_float (
    arg      : STD_LOGIC_VECTOR;
    size_res : UNRESOLVED_float)
    return UNRESOLVED_float;

  -- For Verilog compatability
  function realtobits (arg : REAL) return STD_LOGIC_VECTOR;
  function bitstoreal (arg : STD_LOGIC_VECTOR) return REAL;

end package float_pkg;
-------------------------------------------------------------------------------
-- Proposed package body for the VHDL-200x-FT float_pkg package
-- This version is optimized for Synthesis, and not for simulation.
-- Note that there are functional differences between the synthesis and
-- simulation packages bodies.  The Synthesis version is preferred.
-- This package body supplies a recommended implementation of these functions
-- Version    : $Revision: 1.1 $
-- Date       : $Date: 2012/03/09 20:36:50 $
--
--  Created for VHDL-200X par, David Bishop (dbishop@vhdl.org)
-------------------------------------------------------------------------------

package body float_pkg is

  -- Author David Bishop (dbishop@vhdl.org)
  -----------------------------------------------------------------------------
  -- type declarations
  -----------------------------------------------------------------------------

  -- This deferred constant will tell you if the package body is synthesizable
  -- or implemented as real numbers, set to "true" if synthesizable.
  constant fphdlsynth_or_real : BOOLEAN := true;  -- deferred constant

  -- types of boundary conditions
  type boundary_type is (normal, infinity, zero, denormal);

  -- null range array constant
  constant NAFP : UNRESOLVED_float (0 downto 1)  := (others => '0');
  constant NSLV : STD_ULOGIC_VECTOR (0 downto 1) := (others => '0');

  -- %%% Replicated functions
  -- These functions are replicated so that we don't need to reference the new
  -- 2006 package std.standard, std_logic_1164 and numeric_std.
  function maximum (
    l, r : INTEGER)                     -- inputs
    return INTEGER is
  begin  -- function max
    if l > r then return l;
    else return r;
    end if;
  end function maximum;

  function minimum (
    l, r : INTEGER)                     -- inputs
    return INTEGER is
  begin  -- function min
    if l > r then return r;
    else return l;
    end if;
  end function minimum;

  function or_reduce (arg : STD_ULOGIC_VECTOR)
    return STD_LOGIC is
    variable Upper, Lower : STD_ULOGIC;
    variable Half         : INTEGER;
    variable BUS_int      : STD_ULOGIC_VECTOR (arg'length - 1 downto 0);
    variable Result       : STD_ULOGIC;
  begin
    if (arg'length < 1) then            -- In the case of a NULL range
      Result := '0';
    else
      BUS_int := to_ux01 (arg);
      if (BUS_int'length = 1) then
        Result := BUS_int (BUS_int'left);
      elsif (BUS_int'length = 2) then
        Result := BUS_int (BUS_int'right) or BUS_int (BUS_int'left);
      else
        Half   := (BUS_int'length + 1) / 2 + BUS_int'right;
        Upper  := or_reduce (BUS_int (BUS_int'left downto Half));
        Lower  := or_reduce (BUS_int (Half - 1 downto BUS_int'right));
        Result := Upper or Lower;
      end if;
    end if;
    return Result;
  end function or_reduce;

  function or_reduce (arg : UNSIGNED)
    return STD_ULOGIC is
  begin
    return or_reduce (STD_ULOGIC_VECTOR (arg));
  end function or_reduce;

  function or_reduce (arg : SIGNED)
    return STD_ULOGIC is
  begin
    return or_reduce (STD_ULOGIC_VECTOR (arg));
  end function or_reduce;

  function or_reduce (arg : STD_LOGIC_VECTOR)
    return STD_ULOGIC is
  begin
    return or_reduce (STD_ULOGIC_VECTOR (arg));
  end function or_reduce;

  -- purpose: AND all of the bits in a vector together
  -- This is a copy of the proposed "and_reduce" from 1076.3
  function and_reduce (arg : STD_ULOGIC_VECTOR)
    return STD_LOGIC is
    variable Upper, Lower : STD_ULOGIC;
    variable Half         : INTEGER;
    variable BUS_int      : STD_ULOGIC_VECTOR (arg'length - 1 downto 0);
    variable Result       : STD_ULOGIC;
  begin
    if (arg'length < 1) then            -- In the case of a NULL range
      Result := '1';
    else
      BUS_int := to_ux01 (arg);
      if (BUS_int'length = 1) then
        Result := BUS_int (BUS_int'left);
      elsif (BUS_int'length = 2) then
        Result := BUS_int (BUS_int'right) and BUS_int (BUS_int'left);
      else
        Half   := (BUS_int'length + 1) / 2 + BUS_int'right;
        Upper  := and_reduce (BUS_int (BUS_int'left downto Half));
        Lower  := and_reduce (BUS_int (Half - 1 downto BUS_int'right));
        Result := Upper and Lower;
      end if;
    end if;
    return Result;
  end function and_reduce;

  function and_reduce (arg : UNSIGNED)
    return STD_ULOGIC is
  begin
    return and_reduce (STD_ULOGIC_VECTOR (arg));
  end function and_reduce;

  function and_reduce (arg : SIGNED)
    return STD_ULOGIC is
  begin
    return and_reduce (STD_ULOGIC_VECTOR (arg));
  end function and_reduce;

  function xor_reduce (arg : STD_ULOGIC_VECTOR) return STD_ULOGIC is
    variable Upper, Lower : STD_ULOGIC;
    variable Half         : INTEGER;
    variable BUS_int      : STD_ULOGIC_VECTOR (arg'length - 1 downto 0);
    variable Result       : STD_ULOGIC := '0';  -- In the case of a NULL range
  begin
    if (arg'length >= 1) then
      BUS_int := to_ux01 (arg);
      if (BUS_int'length = 1) then
        Result := BUS_int (BUS_int'left);
      elsif (BUS_int'length = 2) then
        Result := BUS_int(BUS_int'right) xor BUS_int(BUS_int'left);
      else
        Half   := (BUS_int'length + 1) / 2 + BUS_int'right;
        Upper  := xor_reduce (BUS_int (BUS_int'left downto Half));
        Lower  := xor_reduce (BUS_int (Half - 1 downto BUS_int'right));
        Result := Upper xor Lower;
      end if;
    end if;
    return Result;
  end function xor_reduce;

  function nand_reduce(arg : STD_ULOGIC_VECTOR) return STD_ULOGIC is
  begin
    return not and_reduce (arg);
  end function nand_reduce;

  function nor_reduce(arg : STD_ULOGIC_VECTOR) return STD_ULOGIC is
  begin
    return not or_reduce (arg);
  end function nor_reduce;

  function xnor_reduce(arg : STD_ULOGIC_VECTOR) return STD_ULOGIC is
  begin
    return not xor_reduce (arg);
  end function xnor_reduce;

  function find_leftmost (ARG : UNSIGNED; Y : STD_ULOGIC)
    return INTEGER is
  begin
    for INDEX in ARG'range loop
      if ARG(INDEX) = Y then
        return INDEX;
      end if;
    end loop;
    return -1;
  end function find_leftmost;

  -- Match table, copied form new std_logic_1164
  type stdlogic_table is array(STD_ULOGIC, STD_ULOGIC) of STD_ULOGIC;
  constant match_logic_table : stdlogic_table := (
    -----------------------------------------------------
    -- U    X    0    1    Z    W    L    H    -         |   |  
    -----------------------------------------------------
    ('U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', '1'),  -- | U |
    ('U', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '1'),  -- | X |
    ('U', 'X', '1', '0', 'X', 'X', '1', '0', '1'),  -- | 0 |
    ('U', 'X', '0', '1', 'X', 'X', '0', '1', '1'),  -- | 1 |
    ('U', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '1'),  -- | Z |
    ('U', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '1'),  -- | W |
    ('U', 'X', '1', '0', 'X', 'X', '1', '0', '1'),  -- | L |
    ('U', 'X', '0', '1', 'X', 'X', '0', '1', '1'),  -- | H |
    ('1', '1', '1', '1', '1', '1', '1', '1', '1')   -- | - |
    );


  -------------------------------------------------------------------
  -- ?= functions, Similar to "std_match", but returns "std_ulogic".
  -------------------------------------------------------------------
  -- %%% FUNCTION "?=" ( l, r : std_ulogic ) RETURN std_ulogic IS
  function \?=\ (l, r : STD_ULOGIC) return STD_ULOGIC is
  begin
    return match_logic_table (l, r);
  end function \?=\;
  -- %%% END FUNCTION "?=";

  -- %%% FUNCTION "?/=" ( l, r : std_ulogic ) RETURN std_ulogic is
  function \?/=\ (l, r : STD_ULOGIC) return STD_ULOGIC is
  begin
    return not match_logic_table (l, r);
  end function \?/=\;
  -- %%% END FUNCTION "?/=";

  function \?=\ (l, r : STD_ULOGIC_VECTOR) return STD_ULOGIC is
    alias lv        : STD_ULOGIC_VECTOR(1 to l'length) is l;
    alias rv        : STD_ULOGIC_VECTOR(1 to r'length) is r;
    variable result, result1 : STD_ULOGIC;
  begin
    -- Logically identical to an "=" operator.
    if ((l'length < 1) and (r'length < 1)) then
      -- VHDL-2008 LRM 9.2.3 Two NULL arrays of the same type are equal
      return '1';
    elsif lv'length /= rv'length then
      -- Two arrays of different lengths are false
      return '0';
    else
      result := '1';
      for i in lv'low to lv'high loop
        result1 := match_logic_table(lv(i), rv(i));
        result := result and result1;
      end loop;
      return result;
    end if;
  end function \?=\;

  function Is_X (s : UNSIGNED) return BOOLEAN is
  begin
    return Is_X (STD_LOGIC_VECTOR (s));
  end function Is_X;

  function Is_X (s : SIGNED) return BOOLEAN is
  begin
    return Is_X (STD_LOGIC_VECTOR (s));
  end function Is_X;
-- %%% END replicated functions

  -- Special version of "minimum" to do some boundary checking
  function mine (L, R : INTEGER)
    return INTEGER is
  begin  -- function minimum
    if (L = INTEGER'low or R = INTEGER'low) then
      report float_pkg'instance_name
        & " Unbounded number passed, was a literal used?"
        severity error;
      return 0;
    end if;
    return minimum (L, R);
  end function mine;

  -- Generates the base number for the exponent normalization offset.
  function gen_expon_base (
    constant exponent_width : NATURAL)
    return SIGNED is
    variable result : SIGNED (exponent_width-1 downto 0);
  begin
    result                    := (others => '1');
    result (exponent_width-1) := '0';
    return result;
  end function gen_expon_base;

  -- Integer version of the "log2" command (contributed by Peter Ashenden)
  function log2 (A : NATURAL) return NATURAL is
    variable quotient : NATURAL;
    variable result   : NATURAL := 0;
  begin
    quotient := A / 2;
    while quotient > 0 loop
      quotient := quotient / 2;
      result   := result + 1;
    end loop;
    return result;
  end function log2;

  -- Function similar to the ILOGB function in MATH_REAL
  function log2 (A : REAL) return INTEGER is
    variable Y : REAL;
    variable N : INTEGER := 0;
  begin
    if (A = 1.0 or A = 0.0) then
      return 0;
    end if;
    Y := A;
    if(A > 1.0) then
      while Y >= 2.0 loop
        Y := Y / 2.0;
        N := N + 1;
      end loop;
      return N;
    end if;
    -- O < Y < 1
    while Y < 1.0 loop
      Y := Y * 2.0;
      N := N - 1;
    end loop;
    return N;
  end function log2;

  -- purpose: Test the boundary conditions of a Real number
  procedure test_boundary (
    arg                     : in  REAL;     -- Input, converted to real
    constant fraction_width : in  NATURAL;  -- length of FP output fraction
    constant exponent_width : in  NATURAL;  -- length of FP exponent
    constant denormalize    : in  BOOLEAN := true;  -- Use IEEE extended FP
    variable btype          : out boundary_type;
    variable log2i          : out INTEGER
    ) is
    constant expon_base : SIGNED (exponent_width-1 downto 0) :=
      gen_expon_base(exponent_width);   -- exponent offset
    constant exp_min : SIGNED (12 downto 0) :=
      -(resize(expon_base, 13)) + 1;    -- Minimum normal exponent
    constant exp_ext_min : SIGNED (12 downto 0) :=
      exp_min - fraction_width;         -- Minimum for denormal exponent
    variable log2arg : INTEGER;         -- log2 of argument
  begin  -- function test_boundary
    -- Check to see if the exponent is big enough
    -- Note that the argument is always an absolute value at this point.
    log2arg := log2(arg);
    if arg = 0.0 then
      btype := zero;
    elsif exponent_width > 11 then      -- Exponent for Real is 11 (64 bit)
      btype := normal;
    else
      if log2arg < to_integer(exp_min) then
        if denormalize then
          if log2arg < to_integer(exp_ext_min) then
            btype := zero;
          else
            btype := denormal;
          end if;
        else
          if log2arg < to_integer(exp_min)-1 then
            btype := zero;
          else
            btype := normal;            -- Can still represent this number
          end if;
        end if;
      elsif exponent_width < 11 then
        if log2arg > to_integer(expon_base)+1 then
          btype := infinity;
        else
          btype := normal;
        end if;
      else
        btype := normal;
      end if;
    end if;
    log2i := log2arg;
  end procedure test_boundary;

  -- purpose: Rounds depending on the state of the "round_style"
  -- Logic taken from
  -- "What Every Computer Scientist Should Know About Floating Point Arithmetic"
  -- by David Goldberg (1991)
  function check_round (
    fract_in             : STD_ULOGIC;  -- input fraction
    sign                 : STD_ULOGIC;  -- sign bit
    remainder            : UNSIGNED;    -- remainder to round from
    sticky               : STD_ULOGIC := '0';      -- Sticky bit
    constant round_style : round_type)  -- rounding type
    return BOOLEAN is
    variable result     : BOOLEAN;
    variable or_reduced : STD_ULOGIC;
  begin  -- function check_round
    result := false;
    if (remainder'length > 0) then      -- if remainder in a null array
      or_reduced := or_reduce (remainder & sticky);
      rounding_case : case round_style is
        when round_nearest =>           -- Round Nearest, default mode
          if remainder(remainder'high) = '1' then  -- round
            if (remainder'length > 1) then
              if ((or_reduce (remainder(remainder'high-1
                                        downto remainder'low)) = '1'
                   or sticky = '1')
                  or fract_in = '1') then
                -- Make the bottom bit zero if possible if we are at 1/2
                result := true;
              end if;
            else
              result := (fract_in = '1' or sticky = '1');
            end if;
          end if;
        when round_inf =>               -- round up if positive, else truncate.
          if or_reduced = '1' and sign = '0' then
            result := true;
          end if;
        when round_neginf =>        -- round down if negative, else truncate.
          if or_reduced = '1' and sign = '1' then
            result := true;
          end if;
        when round_zero =>              -- round toward 0   Truncate
          null;
      end case rounding_case;
    end if;
    return result;
  end function check_round;

  -- purpose: Rounds depending on the state of the "round_style"
  -- unsigned version
  procedure fp_round (
    fract_in  : in  UNSIGNED;            -- input fraction
    expon_in  : in  SIGNED;              -- input exponent
    fract_out : out UNSIGNED;            -- output fraction
    expon_out : out SIGNED) is           -- output exponent
  begin  -- procedure fp_round
    if and_reduce (fract_in) = '1' then  -- Fraction is all "1"
      expon_out := expon_in + 1;
      fract_out := to_unsigned(0, fract_out'high+1);
    else
      expon_out := expon_in;
      fract_out := fract_in + 1;
    end if;
  end procedure fp_round;

  -- This version of break_number doesn't call "classfp"
  procedure break_number (              -- internal version
    arg         : in  UNRESOLVED_float;
    fptyp       : in  valid_fpstate;
    denormalize : in  BOOLEAN := true;
    fract       : out UNSIGNED;
    expon       : out SIGNED) is
    constant fraction_width : NATURAL := -arg'low;  -- length of FP output fraction
    constant exponent_width : NATURAL := arg'high;  -- length of FP output exponent
    constant expon_base     : SIGNED (exponent_width-1 downto 0) :=
      gen_expon_base(exponent_width);   -- exponent offset
    variable exp : SIGNED (expon'range);
  begin
    fract (fraction_width-1 downto 0) :=
      UNSIGNED (to_slv(arg(-1 downto -fraction_width)));
    breakcase : case fptyp is
      when pos_zero | neg_zero =>
        fract (fraction_width) := '0';
        exp                    := -expon_base;
      when pos_denormal | neg_denormal =>
        if denormalize then
          exp                    := -expon_base;
          fract (fraction_width) := '0';
        else
          exp                    := -expon_base - 1;
          fract (fraction_width) := '1';
        end if;
      when pos_normal | neg_normal | pos_inf | neg_inf =>
        fract (fraction_width) := '1';
        exp                    := SIGNED(arg(exponent_width-1 downto 0));
        exp (exponent_width-1) := not exp(exponent_width-1);
      when others =>
        assert NO_WARNING
          report float_pkg'instance_name
          & "BREAK_NUMBER: " &
          "Meta state detected in fp_break_number process"
          severity warning;
        -- complete the case, if a NAN goes in, a NAN comes out.
        exp                    := (others => '1');
        fract (fraction_width) := '1';
    end case breakcase;
    expon := exp;
  end procedure break_number;

  -- purpose: floating point to UNSIGNED
  -- Used by to_integer, to_unsigned, and to_signed functions
  procedure float_to_unsigned (
    arg                  : in  UNRESOLVED_float;    -- floating point input
    variable sign        : out STD_ULOGIC;          -- sign of output
    variable frac        : out UNSIGNED;            -- unsigned biased output
    constant denormalize : in  BOOLEAN;             -- turn on denormalization
    constant bias        : in  NATURAL;             -- bias for fixed point
    constant round_style : in  round_type) is       -- rounding method
    constant fraction_width : INTEGER := -mine(arg'low, arg'low);  -- length of FP output fraction
    constant exponent_width : INTEGER := arg'high;  -- length of FP output exponent
    variable fract          : UNSIGNED (frac'range);  -- internal version of frac
    variable isign          : STD_ULOGIC;           -- internal version of sign
    variable exp            : INTEGER;  -- Exponent
    variable expon          : SIGNED (exponent_width-1 downto 0);  -- Vectorized exp
    -- Base to divide fraction by
    variable frac_shift     : UNSIGNED (frac'high+3 downto 0);  -- Fraction shifted
    variable shift          : INTEGER;
    variable remainder      : UNSIGNED (2 downto 0);
    variable round          : STD_ULOGIC;           -- round BIT
  begin
    isign                   := to_x01(arg(arg'high));
    -- exponent /= '0', normal floating point
    expon                   := to_01(SIGNED(arg (exponent_width-1 downto 0)), 'X');
    expon(exponent_width-1) := not expon(exponent_width-1);
    exp                     := to_integer (expon);
    -- Figure out the fraction
    fract                   := (others => '0');     -- fill with zero
    fract (fract'high)      := '1';     -- Add the "1.0".
    shift                   := (fract'high-1) - exp;
    if fraction_width > fract'high then             -- Can only use size-2 bits
      fract (fract'high-1 downto 0) := UNSIGNED (to_slv (arg(-1 downto
                                                             -fract'high)));
    else                                -- can use all bits
      fract (fract'high-1 downto fract'high-fraction_width) :=
        UNSIGNED (to_slv (arg(-1 downto -fraction_width)));
    end if;
    frac_shift := fract & "000";
    if shift < 0 then                   -- Overflow
      fract := (others => '1');
    else
      frac_shift := shift_right (frac_shift, shift);
      fract      := frac_shift (frac_shift'high downto 3);
      remainder  := frac_shift (2 downto 0);
      -- round (round_zero will bypass this and truncate)
      case round_style is
        when round_nearest =>
          round := remainder(2) and
                   (fract (0) or (or_reduce (remainder (1 downto 0))));
        when round_inf =>
          round := remainder(2) and not isign;
        when round_neginf =>
          round := remainder(2) and isign;
        when others =>
          round := '0';
      end case;
      if round = '1' then
        fract := fract + 1;
      end if;
    end if;
    frac := fract;
    sign := isign;
  end procedure float_to_unsigned;

  -- purpose: returns a part of a vector, this function is here because
  -- or (fractr (to_integer(shiftx) downto 0));
  -- can't be synthesized in some synthesis tools.
  function smallfract (
    arg   : UNSIGNED;
    shift : NATURAL)
    return STD_ULOGIC is
    variable orx : STD_ULOGIC;
  begin
    orx := arg(shift);
    for i in arg'range loop
      if i < shift then
        orx := arg(i) or orx;
      end if;
    end loop;
    return orx;
  end function smallfract;
  ---------------------------------------------------------------------------
  -- Visible functions
  ---------------------------------------------------------------------------

  -- purpose: converts the negative index to a positive one
  -- negative indices are illegal in 1164 and 1076.3
  function to_sulv (
    arg : UNRESOLVED_float)             -- fp vector
    return STD_ULOGIC_VECTOR is
    variable result : STD_ULOGIC_VECTOR (arg'length-1 downto 0);
  begin  -- function to_std_ulogic_vector
    if arg'length < 1 then
      return NSLV;
    end if;
    result := STD_ULOGIC_VECTOR (arg);
    return result;
  end function to_sulv;

  -- Converts an fp into an SLV
  function to_slv (arg : UNRESOLVED_float) return STD_LOGIC_VECTOR is
  begin
    return to_stdlogicvector (to_sulv (arg));
  end function to_slv;

  -- purpose: normalizes a floating point number
  -- This version assumes an "unsigned" input with
  function normalize (
    fract                   : UNSIGNED;   -- fraction, unnormalized
    expon                   : SIGNED;   -- exponent, normalized by -1
    sign                    : STD_ULOGIC;         -- sign BIT
    sticky                  : STD_ULOGIC := '0';  -- Sticky bit (rounding)
    constant exponent_width : NATURAL    := float_exponent_width;  -- size of output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- size of output fraction
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant denormalize    : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant nguard         : NATURAL    := float_guard_bits)  -- guard bits
    return UNRESOLVED_float is
    variable sfract     : UNSIGNED (fract'high downto 0);  -- shifted fraction
    variable rfract     : UNSIGNED (fraction_width-1 downto 0);   -- fraction
    variable exp        : SIGNED (exponent_width+1 downto 0);  -- exponent
    variable rexp       : SIGNED (exponent_width+1 downto 0);  -- result exponent
    variable rexpon     : UNSIGNED (exponent_width-1 downto 0);   -- exponent
    variable result     : UNRESOLVED_float (exponent_width downto -fraction_width);  -- result
    variable shiftr     : INTEGER;      -- shift amount
    variable stickyx    : STD_ULOGIC;   -- version of sticky
    constant expon_base : SIGNED (exponent_width-1 downto 0) :=
      gen_expon_base(exponent_width);   -- exponent offset
    variable round, zerores, infres : BOOLEAN;
  begin  -- function normalize
    zerores := false;
    infres  := false;
    round   := false;
    shiftr  := find_leftmost (to_01(fract), '1')     -- Find the first "1"
               - fraction_width - nguard;  -- subtract the length we want
    exp := resize (expon, exp'length) + shiftr;
    if (or_reduce (fract) = '0') then   -- Zero
      zerores := true;
    elsif ((exp <= -resize(expon_base, exp'length)-1) and denormalize)
      or ((exp < -resize(expon_base, exp'length)-1) and not denormalize) then
      if (exp >= -resize(expon_base, exp'length)-fraction_width-1)
        and denormalize then
        exp    := -resize(expon_base, exp'length)-1;
        shiftr := -to_integer (expon + expon_base);  -- new shift
      else                              -- return zero
        zerores := true;
      end if;
    elsif (exp > expon_base-1) then     -- infinity
      infres := true;
    end if;
    if zerores then
      result := zerofp (fraction_width => fraction_width,
                        exponent_width => exponent_width);
    elsif infres then
      result := pos_inffp (fraction_width => fraction_width,
                           exponent_width => exponent_width);
    else
      sfract := fract srl shiftr;       -- shift
      if shiftr > 0 then
--        stickyx := sticky or (or_reduce(fract (shiftr-1 downto 0)));
        stickyx := sticky or smallfract (fract, shiftr-1);
      else
        stickyx := sticky;
      end if;
      if nguard > 0 then
        round := check_round (
          fract_in    => sfract (nguard),
          sign        => sign,
          remainder   => sfract(nguard-1 downto 0),
          sticky      => stickyx,
          round_style => round_style);
      end if;
      if round then
        fp_round(fract_in  => sfract (fraction_width-1+nguard downto nguard),
                 expon_in  => exp(rexp'range),
                 fract_out => rfract,
                 expon_out => rexp);
      else
        rfract := sfract (fraction_width-1+nguard downto nguard);
        rexp   := exp(rexp'range);
      end if;
      -- result
      rexpon := UNSIGNED (rexp(exponent_width-1 downto 0));
      rexpon (exponent_width-1)          := not rexpon(exponent_width-1);
      result (rexpon'range)              := UNRESOLVED_float(rexpon);
      result (-1 downto -fraction_width) := UNRESOLVED_float(rfract);
    end if;
    result (exponent_width) := sign;    -- sign BIT
    return result;
  end function normalize;

  -- purpose: normalizes a floating point number
  -- This version assumes a "ufixed" input
  function normalize (
    fract                   : ufixed;   -- unsigned fixed point
    expon                   : SIGNED;   -- exponent, normalized by -1
    sign                    : STD_ULOGIC;         -- sign bit
    sticky                  : STD_ULOGIC := '0';  -- Sticky bit (rounding)
    constant exponent_width : NATURAL    := float_exponent_width;  -- size of output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- size of output fraction
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant denormalize    : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant nguard         : NATURAL    := float_guard_bits)   -- guard bits
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable arguns : UNSIGNED (fract'high + fraction_width + nguard
                                downto 0) := (others => '0');
  begin  -- function normalize
    arguns (arguns'high downto maximum (arguns'high-fract'length+1, 0)) :=
      UNSIGNED (to_slv (fract));
    result := normalize (fract          => arguns,
                         expon          => expon,
                         sign           => sign,
                         sticky         => sticky,
                         fraction_width => fraction_width,
                         exponent_width => exponent_width,
                         round_style    => round_style,
                         denormalize    => denormalize,
                         nguard         => nguard);
    return result;
  end function normalize;

  -- purpose: normalizes a floating point number
  -- This version assumes a "ufixed" input with a "size_res" input
  function normalize (
    fract                : ufixed;      -- unsigned fixed point
    expon                : SIGNED;      -- exponent, normalized by -1
    sign                 : STD_ULOGIC;  -- sign bit
    sticky               : STD_ULOGIC := '0';  -- Sticky bit (rounding)
    size_res             : UNRESOLVED_float;   -- used for sizing only
    constant round_style : round_type := float_round_style;  -- rounding option
    constant denormalize : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant nguard      : NATURAL    := float_guard_bits)   -- guard bits
    return UNRESOLVED_float is
    constant fraction_width : NATURAL := -size_res'low;
    constant exponent_width : NATURAL := size_res'high;
    variable result         : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable arguns : UNSIGNED (fract'high + fraction_width + nguard
                                downto 0) := (others => '0');
  begin  -- function normalize
    arguns (arguns'high downto maximum (arguns'high-fract'length+1, 0)) :=
      UNSIGNED (to_slv (fract));
    result := normalize (fract          => arguns,
                         expon          => expon,
                         sign           => sign,
                         sticky         => sticky,
                         fraction_width => fraction_width,
                         exponent_width => exponent_width,
                         round_style    => round_style,
                         denormalize    => denormalize,
                         nguard         => nguard);
    return result;
  end function normalize;

  -- Regular "normalize" function with a "size_res" input.
  function normalize (
    fract                : UNSIGNED;    -- unsigned
    expon                : SIGNED;      -- exponent - 1, normalized
    sign                 : STD_ULOGIC;  -- sign bit
    sticky               : STD_ULOGIC := '0';  -- Sticky bit (rounding)
    size_res             : UNRESOLVED_float;   -- used for sizing only
    constant round_style : round_type := float_round_style;  -- rounding option
    constant denormalize : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant nguard      : NATURAL    := float_guard_bits)   -- guard bits
    return UNRESOLVED_float is
  begin
    return normalize (fract          => fract,
                      expon          => expon,
                      sign           => sign,
                      sticky         => sticky,
                      fraction_width => -size_res'low,
                      exponent_width => size_res'high,
                      round_style    => round_style,
                      denormalize    => denormalize,
                      nguard         => nguard);
  end function normalize;

  -- Returns the class which X falls into
  function Classfp (
    x           : UNRESOLVED_float;     -- floating point input
    check_error : BOOLEAN := float_check_error)   -- check for errors
    return valid_fpstate is
    constant fraction_width : INTEGER := -mine(x'low, x'low);  -- length of FP output fraction
    constant exponent_width : INTEGER := x'high;  -- length of FP output exponent
    variable arg            : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- classfp
    if (arg'length < 1 or fraction_width < 3 or exponent_width < 3
        or x'left < x'right) then
      report float_pkg'instance_name
        & "CLASSFP: " &
        "Floating point number detected with a bad range"
        severity error;
      return isx;
    end if;
    -- Check for "X".
    arg := to_01 (x, 'X');
    if (arg(0) = 'X') then
      return isx;                       -- If there is an X in the number
      -- Special cases, check for illegal number
    elsif check_error and
      (and_reduce (STD_ULOGIC_VECTOR (arg (exponent_width-1 downto 0)))
       = '1') then                      -- Exponent is all "1".
      if or_reduce (to_slv (arg (-1 downto -fraction_width)))
        /= '0' then  -- Fraction must be all "0" or this is not a number.
        if (arg(-1) = '1') then         -- From "W. Khan - IEEE standard
          return nan;            -- 754 binary FP Signaling nan (Not a number)
        else
          return quiet_nan;
        end if;
        -- Check for infinity
      elsif arg(exponent_width) = '0' then
        return pos_inf;                 -- Positive infinity
      else
        return neg_inf;                 -- Negative infinity
      end if;
      -- check for "0"
    elsif or_reduce (STD_LOGIC_VECTOR (arg (exponent_width-1 downto 0)))
      = '0' then                        -- Exponent is all "0"
      if or_reduce (to_slv (arg (-1 downto -fraction_width)))
        = '0' then                      -- Fraction is all "0"
        if arg(exponent_width) = '0' then
          return pos_zero;              -- Zero
        else
          return neg_zero;
        end if;
      else
        if arg(exponent_width) = '0' then
          return pos_denormal;          -- Denormal number (ieee extended fp)
        else
          return neg_denormal;
        end if;
      end if;
    else
      if arg(exponent_width) = '0' then
        return pos_normal;              -- Normal FP number
      else
        return neg_normal;
      end if;
    end if;
  end function Classfp;

  procedure break_number (
    arg         : in  UNRESOLVED_float;
    denormalize : in  BOOLEAN := float_denormalize;
    check_error : in  BOOLEAN := float_check_error;
    fract       : out UNSIGNED;
    expon       : out SIGNED;
    sign        : out STD_ULOGIC) is
    constant fraction_width : NATURAL := -mine(arg'low, arg'low);  -- length of FP output fraction
    variable fptyp          : valid_fpstate;
  begin
    fptyp := Classfp (arg, check_error);
    sign  := to_x01(arg(arg'high));
    break_number (
      arg         => arg,
      fptyp       => fptyp,
      denormalize => denormalize,
      fract       => fract,
      expon       => expon);
  end procedure break_number;
  
  procedure break_number (
    arg         : in  UNRESOLVED_float;
    denormalize : in  BOOLEAN := float_denormalize;
    check_error : in  BOOLEAN := float_check_error;
    fract       : out ufixed;           -- 1 downto -fraction_width
    expon       : out SIGNED;           -- exponent_width-1 downto 0
    sign        : out STD_ULOGIC) is
    constant fraction_width : NATURAL := -mine(arg'low, arg'low);  -- length of FP output fraction
    variable fptyp          : valid_fpstate;
    variable ufract         : UNSIGNED (fraction_width downto 0);  -- unsigned fraction
  begin
    fptyp := Classfp (arg, check_error);
    sign  := to_x01(arg(arg'high));
    break_number (
      arg         => arg,
      fptyp       => fptyp,
      denormalize => denormalize,
      fract       => ufract,
      expon       => expon);
    fract (0 downto -fraction_width) := ufixed (ufract);
  end procedure break_number;

  -- Arithmetic functions
  function "abs" (
    arg : UNRESOLVED_float)             -- floating point input
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (arg'range);  -- result
  begin
    if (arg'length > 0) then
      result            := to_01 (arg, 'X');
      result (arg'high) := '0';         -- set the sign bit to positive     
      return result;
    else
      return NAFP;
    end if;
  end function "abs";

  -- IEEE 754 "negative" function
  function "-" (
    arg : UNRESOLVED_float)                          -- floating point input
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (arg'range);  -- result
  begin
    if (arg'length > 0) then
      result            := to_01 (arg, 'X');
      result (arg'high) := not result (arg'high);    -- invert sign bit
      return result;
    else
      return NAFP;
    end if;
  end function "-";

  -- Addition, adds two floating point numbers
  function add (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width   : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    constant addguard         : NATURAL := guard;         -- add one guard bit
    variable lfptype, rfptype : valid_fpstate;
    variable fpresult         : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable fractl, fractr   : UNSIGNED (fraction_width+1+addguard downto 0);  -- fractions
    variable fractc, fracts   : UNSIGNED (fractl'range);  -- constant and shifted variables
    variable urfract, ulfract : UNSIGNED (fraction_width downto 0);
    variable ufract           : UNSIGNED (fraction_width+1+addguard downto 0);
    variable exponl, exponr   : SIGNED (exponent_width-1 downto 0);  -- exponents
    variable rexpon           : SIGNED (exponent_width downto 0);  -- result exponent
    variable shiftx           : SIGNED (exponent_width downto 0);  -- shift fractions
    variable sign             : STD_ULOGIC;   -- sign of the output
    variable leftright        : BOOLEAN;      -- left or right used
    variable lresize, rresize : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable sticky           : STD_ULOGIC;   -- Holds precision for rounding
  begin  -- addition
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      lfptype := isx;
    else
      lfptype := classfp (l, check_error);
      rfptype := classfp (r, check_error);
    end if;
    if (lfptype = isx or rfptype = isx) then
      fpresult := (others => 'X');
    elsif (lfptype = nan or lfptype = quiet_nan or
           rfptype = nan or rfptype = quiet_nan)
      -- Return quiet NAN, IEEE754-1985-7.1,1
      or (lfptype = pos_inf and rfptype = neg_inf)
      or (lfptype = neg_inf and rfptype = pos_inf) then
      -- Return quiet NAN, IEEE754-1985-7.1,2
      fpresult := qnanfp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    elsif (lfptype = pos_inf or rfptype = pos_inf) then   -- x + inf = inf
      fpresult := pos_inffp (fraction_width => fraction_width,
                             exponent_width => exponent_width);
    elsif (lfptype = neg_inf or rfptype = neg_inf) then   -- x - inf = -inf
      fpresult := neg_inffp (fraction_width => fraction_width,
                             exponent_width => exponent_width);
    elsif (lfptype = neg_zero and rfptype = neg_zero) then   -- -0 + -0 = -0
      fpresult := neg_zerofp (fraction_width => fraction_width,
                             exponent_width => exponent_width);
    else
      lresize := resize (arg            => to_x01(l),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      lfptype := classfp (lresize, false);    -- errors already checked
      rresize := resize (arg            => to_x01(r),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      rfptype := classfp (rresize, false);    -- errors already checked
      break_number (
        arg         => lresize,
        fptyp       => lfptype,
        denormalize => denormalize,
        fract       => ulfract,
        expon       => exponl);
      fractl := (others => '0');
      fractl (fraction_width+addguard downto addguard) := ulfract;
      break_number (
        arg         => rresize,
        fptyp       => rfptype,
        denormalize => denormalize,
        fract       => urfract,
        expon       => exponr);
      fractr := (others => '0');
      fractr (fraction_width+addguard downto addguard) := urfract;
      shiftx := (exponl(exponent_width-1) & exponl) - exponr;
      if shiftx < -fractl'high then
        rexpon    := exponr(exponent_width-1) & exponr;
        fractc    := fractr;
        fracts    := (others => '0');   -- add zero
        leftright := false;
        sticky    := or_reduce (fractl);
      elsif shiftx < 0 then
        shiftx    := - shiftx;
        fracts    := shift_right (fractl, to_integer(shiftx));
        fractc    := fractr;
        rexpon    := exponr(exponent_width-1) & exponr;
        leftright := false;
--        sticky    := or_reduce (fractl (to_integer(shiftx) downto 0));
        sticky    := smallfract (fractl, to_integer(shiftx));
      elsif shiftx = 0 then
        rexpon := exponl(exponent_width-1) & exponl;
        sticky := '0';
        if fractr > fractl then
          fractc    := fractr;
          fracts    := fractl;
          leftright := false;
        else
          fractc    := fractl;
          fracts    := fractr;
          leftright := true;
        end if;
      elsif shiftx > fractr'high then
        rexpon    := exponl(exponent_width-1) & exponl;
        fracts    := (others => '0');   -- add zero
        fractc    := fractl;
        leftright := true;
        sticky    := or_reduce (fractr);
      elsif shiftx > 0 then
        fracts    := shift_right (fractr, to_integer(shiftx));
        fractc    := fractl;
        rexpon    := exponl(exponent_width-1) & exponl;
        leftright := true;
--        sticky    := or_reduce (fractr (to_integer(shiftx) downto 0));
        sticky    := smallfract (fractr, to_integer(shiftx));
      end if;
      -- add
      fracts (0) := fracts (0) or sticky;     -- Or the sticky bit into the LSB
      if l(l'high) = r(r'high) then
        ufract := fractc + fracts;
        sign   := l(l'high);
      else                              -- signs are different
        ufract := fractc - fracts;      -- always positive result
        if leftright then               -- Figure out which sign to use
          sign := l(l'high);
        else
          sign := r(r'high);
        end if;
      end if;
      if or_reduce (ufract) = '0' then
        sign := '0';                    -- IEEE 854, 6.3, paragraph 2.
      end if;
        -- normalize
      fpresult := normalize (fract          => ufract,
                             expon          => rexpon,
                             sign           => sign,
                             sticky         => sticky,
                             fraction_width => fraction_width,
                             exponent_width => exponent_width,
                             round_style    => round_style,
                             denormalize    => denormalize,
                             nguard         => addguard);
    end if;
    return fpresult;
  end function add;

  -- Subtraction, Calls "add".
  function subtract (
    l, r                 : UNRESOLVED_float;     -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    variable negr : UNRESOLVED_float (r'range);  -- negative version of r
  begin
    negr := -r;
    return add (l           => l,
                r           => negr,
                round_style => round_style,
                guard       => guard,
                check_error => check_error,
                denormalize => denormalize);
  end function subtract;

  -- Floating point multiply
  function multiply (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width   : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    constant multguard        : NATURAL := guard;           -- guard bits
    variable lfptype, rfptype : valid_fpstate;
    variable fpresult         : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable fractl, fractr   : UNSIGNED (fraction_width downto 0);  -- fractions
    variable rfract           : UNSIGNED ((2*(fraction_width))+1 downto 0);  -- result fraction
    variable sfract           : UNSIGNED (fraction_width+1+multguard downto 0);  -- result fraction
    variable shifty           : INTEGER;      -- denormal shift
    variable exponl, exponr   : SIGNED (exponent_width-1 downto 0);  -- exponents
    variable rexpon           : SIGNED (exponent_width+1 downto 0);  -- result exponent
    variable fp_sign          : STD_ULOGIC;   -- sign of result
    variable lresize, rresize : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable sticky           : STD_ULOGIC;   -- Holds precision for rounding
  begin  -- multiply
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      lfptype := isx;
    else
      lfptype := classfp (l, check_error);
      rfptype := classfp (r, check_error);
    end if;
    if (lfptype = isx or rfptype = isx) then
      fpresult := (others => 'X');
    elsif ((lfptype = nan or lfptype = quiet_nan or
            rfptype = nan or rfptype = quiet_nan)) then
      -- Return quiet NAN, IEEE754-1985-7.1,1
      fpresult := qnanfp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    elsif (((lfptype = pos_inf or lfptype = neg_inf) and
            (rfptype = pos_zero or rfptype = neg_zero)) or
           ((rfptype = pos_inf or rfptype = neg_inf) and
            (lfptype = pos_zero or lfptype = neg_zero))) then    -- 0 * inf
      -- Return quiet NAN, IEEE754-1985-7.1,3
      fpresult := qnanfp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    elsif (lfptype = pos_inf or rfptype = pos_inf
           or lfptype = neg_inf or rfptype = neg_inf) then  -- x * inf = inf
      fpresult := pos_inffp (fraction_width => fraction_width,
                             exponent_width => exponent_width);
      -- figure out the sign
      fp_sign := l(l'high) xor r(r'high);     -- figure out the sign
      fpresult (exponent_width) := fp_sign;
    else
      fp_sign := l(l'high) xor r(r'high);     -- figure out the sign
      lresize := resize (arg            => to_x01(l),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      lfptype := classfp (lresize, false);    -- errors already checked
      rresize := resize (arg            => to_x01(r),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      rfptype := classfp (rresize, false);    -- errors already checked
      break_number (
        arg         => lresize,
        fptyp       => lfptype,
        denormalize => denormalize,
        fract       => fractl,
        expon       => exponl);
      break_number (
        arg         => rresize,
        fptyp       => rfptype,
        denormalize => denormalize,
        fract       => fractr,
        expon       => exponr);
      if (rfptype = pos_denormal or rfptype = neg_denormal) then
        shifty := fraction_width - find_leftmost(fractr, '1');
        fractr := shift_left (fractr, shifty);
      elsif (lfptype = pos_denormal or lfptype = neg_denormal) then
        shifty := fraction_width - find_leftmost(fractl, '1');
        fractl := shift_left (fractl, shifty);
      else
        shifty := 0;
        -- Note that a denormal number * a denormal number is always zero.
      end if;
      -- multiply
      -- add the exponents
      rexpon := resize (exponl, rexpon'length) + exponr - shifty + 1;
      rfract := fractl * fractr;        -- Multiply the fraction
      sfract := rfract (rfract'high downto
                        rfract'high - (fraction_width+1+multguard));
      sticky := or_reduce (rfract (rfract'high-(fraction_width+1+multguard)
                                   downto 0));
      -- normalize
      fpresult := normalize (fract          => sfract,
                             expon          => rexpon,
                             sign           => fp_sign,
                             sticky         => sticky,
                             fraction_width => fraction_width,
                             exponent_width => exponent_width,
                             round_style    => round_style,
                             denormalize    => denormalize,
                             nguard         => multguard);
    end if;
    return fpresult;
  end function multiply;

  function short_divide (
    lx, rx : UNSIGNED)
    return UNSIGNED is
    -- This is a special divider for the floating point routines.
    -- For a true unsigned divider, "stages" needs to = lx'high
    constant stages       : INTEGER := lx'high - rx'high;  -- number of stages
    variable partial      : UNSIGNED (lx'range);
    variable q            : UNSIGNED (stages downto 0);
    variable partial_argl : SIGNED (rx'high + 2 downto 0);
    variable partial_arg  : SIGNED (rx'high + 2 downto 0);
  begin
    partial := lx;
    for i in stages downto 0 loop
      partial_argl := resize ("0" & SIGNED (partial(lx'high downto i)),
                              partial_argl'length);
      partial_arg := partial_argl - SIGNED ("0" & rx);
      if (partial_arg (partial_arg'high) = '1') then       -- negative
        q(i) := '0';
      else
        q(i) := '1';
        partial (lx'high+i-stages downto lx'high+i-stages-rx'high) :=
          UNSIGNED (partial_arg(rx'range));
      end if;
    end loop;
    -- to make the output look like that of the unsigned IEEE divide.
    return resize (q, lx'length);
  end function short_divide;

  -- 1/X function.  Needed for algorithm development.
  function reciprocal (
    arg                  : UNRESOLVED_float;
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width : NATURAL := -mine(arg'low, arg'low);  -- length of FP output fraction
    constant exponent_width : NATURAL := arg'high;  -- length of FP output exponent
    constant divguard       : NATURAL := guard;     -- guard bits
    function onedivy (
      arg : UNSIGNED)
      return UNSIGNED is
      variable q   : UNSIGNED((2*arg'high)+1 downto 0);
      variable one : UNSIGNED (q'range);
    begin
      one           := (others => '0');
      one(one'high) := '1';
      q := short_divide (one, arg);     -- Unsigned divide
      return resize (q, arg'length+1);
    end function onedivy;
    variable fptype        : valid_fpstate;
    variable expon         : SIGNED (exponent_width-1 downto 0);   -- exponents
    variable denorm_offset : NATURAL range 0 to 2;
    variable fract         : UNSIGNED (fraction_width downto 0);
    variable fractg        : UNSIGNED (fraction_width+divguard downto 0);
    variable sfract        : UNSIGNED (fraction_width+1+divguard downto 0);  -- result fraction
    variable fpresult      : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- reciprocal
    fptype := classfp(arg, check_error);
    classcase : case fptype is
      when isx =>
        fpresult := (others => 'X');
      when nan | quiet_nan =>
        -- Return quiet NAN, IEEE754-1985-7.1,1
        fpresult := qnanfp (fraction_width => fraction_width,
                            exponent_width => exponent_width);
      when pos_inf | neg_inf =>         -- 1/inf, return 0
        fpresult := zerofp (fraction_width => fraction_width,
                            exponent_width => exponent_width);
      when neg_zero | pos_zero =>       -- 1/0
        report float_pkg'instance_name
          & "RECIPROCAL: Floating Point divide by zero"
          severity error;
        fpresult := pos_inffp (fraction_width => fraction_width,
                               exponent_width => exponent_width);
      when others =>
        if (fptype = pos_denormal or fptype = neg_denormal)
          and ((arg (-1) or arg(-2)) /= '1') then
          -- 1/denormal = infinity, with the exception of 2**-expon_base
          fpresult := pos_inffp (fraction_width => fraction_width,
                                 exponent_width => exponent_width);
          fpresult (exponent_width) := to_x01 (arg (exponent_width));
        else
          break_number (
            arg         => arg,
            fptyp       => fptype,
            denormalize => denormalize,
            fract       => fract,
            expon       => expon);
          fractg := (others => '0');
          if (fptype = pos_denormal or fptype = neg_denormal) then
            -- The reciprocal of a denormal number is typically zero,
            -- except for two special cases which are trapped here.
            if (to_x01(arg (-1)) = '1') then
              fractg (fractg'high downto divguard+1) :=
                fract (fract'high-1 downto 0);      -- Shift to not denormal
              denorm_offset := 1;       -- add 1 to exponent compensate
            else                        -- arg(-2) = '1'
              fractg (fractg'high downto divguard+2) :=
                fract (fract'high-2 downto 0);      -- Shift to not denormal
              denorm_offset := 2;       -- add 2 to exponent compensate
            end if;
          else
            fractg (fractg'high downto divguard) := fract;
            denorm_offset := 0;
          end if;
          expon  := - expon - 3 + denorm_offset;
          sfract := onedivy (fractg);
          -- normalize
          fpresult := normalize (fract          => sfract,
                                 expon          => expon,
                                 sign           => arg(exponent_width),
                                 sticky         => '1',
                                 fraction_width => fraction_width,
                                 exponent_width => exponent_width,
                                 round_style    => round_style,
                                 denormalize    => denormalize,
                                 nguard         => divguard);
        end if;
    end case classcase;
    return fpresult;
  end function reciprocal;

  -- floating point division
  function divide (
    l, r                 : UNRESOLVED_float;       -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width   : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    constant divguard         : NATURAL := guard;  -- division guard bits
    variable lfptype, rfptype : valid_fpstate;
    variable fpresult         : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable ulfract, urfract : UNSIGNED (fraction_width downto 0);
    variable fractl           : UNSIGNED ((2*(fraction_width+divguard)+1) downto 0);  -- left
    variable fractr           : UNSIGNED (fraction_width+divguard downto 0);  -- right
    variable rfract           : UNSIGNED (fractl'range);    -- result fraction
    variable sfract           : UNSIGNED (fraction_width+1+divguard downto 0);  -- result fraction
    variable exponl, exponr   : SIGNED (exponent_width-1 downto 0);  -- exponents
    variable rexpon           : SIGNED (exponent_width+1 downto 0);  -- result exponent
    variable fp_sign, sticky  : STD_ULOGIC;        -- sign of result
    variable shifty, shiftx   : INTEGER;           -- denormal number shift
    variable lresize, rresize : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- divide
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      lfptype := isx;
    else
      lfptype := classfp (l, check_error);
      rfptype := classfp (r, check_error);
    end if;
    classcase : case rfptype is
      when isx =>
        fpresult := (others => 'X');
      when nan | quiet_nan =>
        -- Return quiet NAN, IEEE754-1985-7.1,1
        fpresult := qnanfp (fraction_width => fraction_width,
                            exponent_width => exponent_width);
      when pos_inf | neg_inf =>
        if lfptype = pos_inf or lfptype = neg_inf  -- inf / inf
          or lfptype = quiet_nan or lfptype = nan then
          -- Return quiet NAN, IEEE754-1985-7.1,4
          fpresult := qnanfp (fraction_width => fraction_width,
                              exponent_width => exponent_width);
        else                            -- x / inf = 0
          fpresult := zerofp (fraction_width => fraction_width,
                              exponent_width => exponent_width);
          fp_sign := l(l'high) xor r(r'high);        -- sign
          fpresult (fpresult'high) := fp_sign;  -- sign
        end if;
      when pos_zero | neg_zero =>
        if lfptype = pos_zero or lfptype = neg_zero         -- 0 / 0
          or lfptype = quiet_nan or lfptype = nan then
          -- Return quiet NAN, IEEE754-1985-7.1,4
          fpresult := qnanfp (fraction_width => fraction_width,
                              exponent_width => exponent_width);
        else
          report float_pkg'instance_name
            & "DIVIDE: Floating Point divide by zero"
            severity error;
          -- Infinity, define in 754-1985-7.2
          fpresult := pos_inffp (fraction_width => fraction_width,
                                 exponent_width => exponent_width);
          fp_sign := l(l'high) xor r(r'high);        -- sign
          fpresult (fpresult'high) := fp_sign;  -- sign
        end if;
      when others =>
        classcase2 : case lfptype is
          when isx =>
            fpresult := (others => 'X');
          when nan | quiet_nan =>
            -- Return quiet NAN, IEEE754-1985-7.1,1
            fpresult := qnanfp (fraction_width => fraction_width,
                                exponent_width => exponent_width);
          when pos_inf | neg_inf =>     -- inf / x = inf
            fpresult := pos_inffp (fraction_width => fraction_width,
                                   exponent_width => exponent_width);
            fp_sign := l(l'high) xor r(r'high);        -- sign
            fpresult(exponent_width) := fp_sign;
          when pos_zero | neg_zero =>   -- 0 / X = 0
            fpresult := zerofp (fraction_width => fraction_width,
                                exponent_width => exponent_width);
            fp_sign := l(l'high) xor r(r'high);        -- sign
            fpresult(exponent_width) := fp_sign;
          when others =>
            fp_sign := l(l'high) xor r(r'high);        -- sign
            lresize := resize (arg            => to_x01(l),
                               exponent_width => exponent_width,
                               fraction_width => fraction_width,
                               denormalize_in => denormalize,
                               denormalize    => denormalize);
            lfptype := classfp (lresize, false);   -- errors already checked
            rresize := resize (arg            => to_x01(r),
                               exponent_width => exponent_width,
                               fraction_width => fraction_width,
                               denormalize_in => denormalize,
                               denormalize    => denormalize);
            rfptype := classfp (rresize, false);   -- errors already checked
            break_number (
              arg         => lresize,
              fptyp       => lfptype,
              denormalize => denormalize,
              fract       => ulfract,
              expon       => exponl);
            -- right side
            break_number (
              arg         => rresize,
              fptyp       => rfptype,
              denormalize => denormalize,
              fract       => urfract,
              expon       => exponr);
            -- Compute the exponent
            rexpon := resize (exponl, rexpon'length) - exponr - 2;
            if (rfptype = pos_denormal or rfptype = neg_denormal) then
              -- Do the shifting here not after.  That way we have a smaller
              -- shifter, and need a smaller divider, because the top
              -- bit in the divisor will always be a "1".
              shifty := fraction_width - find_leftmost(urfract, '1');
              urfract := shift_left (urfract, shifty);
              rexpon := rexpon + shifty;
            end if;
            fractr := (others => '0');
            fractr (fraction_width+divguard downto divguard) := urfract;
            if (lfptype = pos_denormal or lfptype = neg_denormal) then
              shiftx := fraction_width - find_leftmost(ulfract, '1');
              ulfract := shift_left (ulfract, shiftx);
              rexpon := rexpon - shiftx;
            end if;
            fractl  := (others => '0');
            fractl (fractl'high downto fractl'high-fraction_width) := ulfract;
            -- divide
            rfract := short_divide (fractl, fractr);        -- unsigned divide
            sfract := rfract (sfract'range);       -- lower bits
            sticky := '1';
            -- normalize
            fpresult := normalize (fract          => sfract,
                                   expon          => rexpon,
                                   sign           => fp_sign,
                                   sticky         => sticky,
                                   fraction_width => fraction_width,
                                   exponent_width => exponent_width,
                                   round_style    => round_style,
                                   denormalize    => denormalize,
                                   nguard         => divguard);
        end case classcase2;
    end case classcase;
    return fpresult;
  end function divide;

  -- division by a power of 2
  function dividebyp2 (
    l, r                 : UNRESOLVED_float;      -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width   : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lfptype, rfptype : valid_fpstate;
    variable fpresult         : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable ulfract, urfract : UNSIGNED (fraction_width downto 0);
    variable exponl, exponr   : SIGNED(exponent_width-1 downto 0);  -- exponents
    variable rexpon           : SIGNED(exponent_width downto 0);  -- result exponent
    variable fp_sign          : STD_ULOGIC;       -- sign of result
    variable lresize, rresize : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- divisionbyp2
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      lfptype := isx;
    else
      lfptype := classfp (l, check_error);
      rfptype := classfp (r, check_error);
    end if;
    classcase : case rfptype is
      when isx =>
        fpresult := (others => 'X');
      when nan | quiet_nan =>
        -- Return quiet NAN, IEEE754-1985-7.1,1
        fpresult := qnanfp (fraction_width => fraction_width,
                            exponent_width => exponent_width);
      when pos_inf | neg_inf =>
        if lfptype = pos_inf or lfptype = neg_inf then      -- inf / inf
          -- Return quiet NAN, IEEE754-1985-7.1,4
          fpresult := qnanfp (fraction_width => fraction_width,
                              exponent_width => exponent_width);
        else                            -- x / inf = 0
          fpresult := zerofp (fraction_width => fraction_width,
                              exponent_width => exponent_width);
          fp_sign := l(l'high) xor r(r'high);        -- sign
          fpresult (fpresult'high) := fp_sign;  -- sign
        end if;
      when pos_zero | neg_zero =>
        if lfptype = pos_zero or lfptype = neg_zero then    -- 0 / 0
          -- Return quiet NAN, IEEE754-1985-7.1,4
          fpresult := qnanfp (fraction_width => fraction_width,
                              exponent_width => exponent_width);
        else
          report float_pkg'instance_name
            & "DIVIDEBYP2: Floating Point divide by zero"
            severity error;
          -- Infinity, define in 754-1985-7.2
          fpresult := pos_inffp (fraction_width => fraction_width,
                                 exponent_width => exponent_width);
          fp_sign := l(l'high) xor r(r'high);        -- sign
          fpresult (fpresult'high) := fp_sign;  -- sign
        end if;
      when others =>
        classcase2 : case lfptype is
          when isx =>
            fpresult := (others => 'X');
          when nan | quiet_nan =>
            -- Return quiet NAN, IEEE754-1985-7.1,1
            fpresult := qnanfp (fraction_width => fraction_width,
                                exponent_width => exponent_width);
          when pos_inf | neg_inf =>     -- inf / x = inf
            fpresult := pos_inffp (fraction_width => fraction_width,
                                   exponent_width => exponent_width);
            fp_sign := l(l'high) xor r(r'high);        -- sign
            fpresult (exponent_width) := fp_sign;  -- sign
          when pos_zero | neg_zero =>   -- 0 / X = 0
            fpresult := zerofp (fraction_width => fraction_width,
                                exponent_width => exponent_width);
            fp_sign := l(l'high) xor r(r'high);        -- sign
            fpresult (exponent_width) := fp_sign;  -- sign
          when others =>
            fp_sign := l(l'high) xor r(r'high);        -- sign
            lresize := resize (arg            => to_x01(l),
                               exponent_width => exponent_width,
                               fraction_width => fraction_width,
                               denormalize_in => denormalize,
                               denormalize    => denormalize);
            lfptype := classfp (lresize, false);  -- errors already checked
            rresize := resize (arg            => to_x01(r),
                               exponent_width => exponent_width,
                               fraction_width => fraction_width,
                               denormalize_in => denormalize,
                               denormalize    => denormalize);
            rfptype := classfp (rresize, false);  -- errors already checked
            break_number (
              arg         => lresize,
              fptyp       => lfptype,
              denormalize => denormalize,
              fract       => ulfract,
              expon       => exponl);
            -- right side
            break_number (
              arg         => rresize,
              fptyp       => rfptype,
              denormalize => denormalize,
              fract       => urfract,
              expon       => exponr);
            assert (or_reduce (urfract (fraction_width-1 downto 0)) = '0')
              report float_pkg'instance_name
              & "DIVIDEBYP2: "
              & "Dividebyp2 called with a non power of two divisor"
              severity error;
            rexpon := (exponl(exponl'high)&exponl)
                      - (exponr(exponr'high)&exponr) - 1;
            -- normalize
            fpresult := normalize (fract          => ulfract,
                                   expon          => rexpon,
                                   sign           => fp_sign,
                                   sticky         => '1',
                                   fraction_width => fraction_width,
                                   exponent_width => exponent_width,
                                   round_style    => round_style,
                                   denormalize    => denormalize,
                                   nguard         => 0);
        end case classcase2;
    end case classcase;
    return fpresult;
  end function dividebyp2;

  -- Multiply accumulate  result = l*r + c
  function mac (
    l, r, c              : UNRESOLVED_float;      -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width : NATURAL :=
      -mine (mine(l'low, r'low), c'low);   -- length of FP output fraction
    constant exponent_width : NATURAL :=
      maximum (maximum(l'high, r'high), c'high);  -- length of FP output exponent
    variable lfptype, rfptype, cfptype : valid_fpstate;
    variable fpresult                  : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable fractl, fractr            : UNSIGNED (fraction_width downto 0);  -- fractions
    variable fractx                    : UNSIGNED (fraction_width+guard downto 0);
    variable fractc, fracts            : UNSIGNED (fraction_width+1+guard downto 0);
    variable rfract                    : UNSIGNED ((2*(fraction_width))+1 downto 0);  -- result fraction
    variable sfract, ufract            : UNSIGNED (fraction_width+1+guard downto 0);  -- result fraction
    variable exponl, exponr, exponc    : SIGNED (exponent_width-1 downto 0);  -- exponents
    variable rexpon, rexpon2           : SIGNED (exponent_width+1 downto 0);  -- result exponent
    variable shifty                    : INTEGER;      -- denormal shift
    variable shiftx                    : SIGNED (rexpon'range);  -- shift fractions
    variable fp_sign                   : STD_ULOGIC;  -- sign of result
    variable lresize, rresize          : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable cresize                   : UNRESOLVED_float (exponent_width downto -fraction_width - guard);
    variable leftright                 : BOOLEAN;     -- left or right used
    variable sticky                    : STD_ULOGIC;  -- Holds precision for rounding
  begin  -- multiply
    if (fraction_width = 0 or l'length < 7 or r'length < 7 or c'length < 7) then
      lfptype := isx;
    else
      lfptype := classfp (l, check_error);
      rfptype := classfp (r, check_error);
      cfptype := classfp (c, check_error);
    end if;
    if (lfptype = isx or rfptype = isx or cfptype = isx) then
      fpresult := (others => 'X');
    elsif (lfptype = nan or lfptype = quiet_nan or
           rfptype = nan or rfptype = quiet_nan or
           cfptype = nan or cfptype = quiet_nan) then
      -- Return quiet NAN, IEEE754-1985-7.1,1
      fpresult := qnanfp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    elsif (((lfptype = pos_inf or lfptype = neg_inf) and
            (rfptype = pos_zero or rfptype = neg_zero)) or
           ((rfptype = pos_inf or rfptype = neg_inf) and
            (lfptype = pos_zero or lfptype = neg_zero))) then  -- 0 * inf
      -- Return quiet NAN, IEEE754-1985-7.1,3
      fpresult := qnanfp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    elsif (lfptype = pos_inf or rfptype = pos_inf
           or lfptype = neg_inf or rfptype = neg_inf  -- x * inf = inf
           or cfptype = neg_inf or cfptype = pos_inf) then  -- x + inf = inf
      fpresult := pos_inffp (fraction_width => fraction_width,
                             exponent_width => exponent_width);
      -- figure out the sign
      fpresult (exponent_width) := l(l'high) xor r(r'high);
    else
      fp_sign := l(l'high) xor r(r'high);  -- figure out the sign
      lresize := resize (arg            => to_x01(l),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      lfptype := classfp (lresize, false);        -- errors already checked
      rresize := resize (arg            => to_x01(r),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      rfptype := classfp (rresize, false);        -- errors already checked
      cresize := resize (arg            => to_x01(c),
                         exponent_width => exponent_width,
                         fraction_width => -cresize'low,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      cfptype := classfp (cresize, false);        -- errors already checked
      break_number (
        arg         => lresize,
        fptyp       => lfptype,
        denormalize => denormalize,
        fract       => fractl,
        expon       => exponl);
      break_number (
        arg         => rresize,
        fptyp       => rfptype,
        denormalize => denormalize,
        fract       => fractr,
        expon       => exponr);
      break_number (
        arg         => cresize,
        fptyp       => cfptype,
        denormalize => denormalize,
        fract       => fractx,
        expon       => exponc);
      if (rfptype = pos_denormal or rfptype = neg_denormal) then
        shifty := fraction_width - find_leftmost(fractr, '1');
        fractr := shift_left (fractr, shifty);
      elsif (lfptype = pos_denormal or lfptype = neg_denormal) then
        shifty := fraction_width - find_leftmost(fractl, '1');
        fractl := shift_left (fractl, shifty);
      else
        shifty := 0;
        -- Note that a denormal number * a denormal number is always zero.
      end if;
      -- multiply
      rfract := fractl * fractr;        -- Multiply the fraction
      -- add the exponents
      rexpon := resize (exponl, rexpon'length) + exponr - shifty + 1;
      shiftx := rexpon - exponc;
      if shiftx < -fractl'high then
        rexpon2 := resize (exponc, rexpon2'length);
        fractc  := "0" & fractx;
        fracts  := (others => '0');
        sticky  := or_reduce (rfract);
      elsif shiftx < 0 then
        shiftx := - shiftx;
        fracts := shift_right (rfract (rfract'high downto rfract'high
                                       - fracts'length+1),
                               to_integer(shiftx));
        fractc    := "0" & fractx;
        rexpon2   := resize (exponc, rexpon2'length);
        leftright := false;
        sticky := or_reduce (rfract (to_integer(shiftx)+rfract'high
                                     - fracts'length downto 0));
      elsif shiftx = 0 then
        rexpon2 := resize (exponc, rexpon2'length);
        sticky  := or_reduce (rfract (rfract'high - fractc'length downto 0));
        if rfract (rfract'high downto rfract'high - fractc'length+1) > fractx
        then
          fractc := "0" & fractx;
          fracts := rfract (rfract'high downto rfract'high
                            - fracts'length+1);
          leftright := false;
        else
          fractc := rfract (rfract'high downto rfract'high
                            - fractc'length+1);
          fracts    := "0" & fractx;
          leftright := true;
        end if;
      elsif shiftx > fractx'high then
        rexpon2   := rexpon;
        fracts    := (others => '0');
        fractc    := rfract (rfract'high downto rfract'high - fractc'length+1);
        leftright := true;
        sticky := or_reduce (fractx & rfract (rfract'high - fractc'length
                                              downto 0));
      else                              -- fractx'high > shiftx > 0
        rexpon2   := rexpon;
        fracts    := "0" & shift_right (fractx, to_integer (shiftx));
        fractc    := rfract (rfract'high downto rfract'high - fractc'length+1);
        leftright := true;
        sticky := or_reduce (fractx (to_integer (shiftx) downto 0)
                             & rfract (rfract'high - fractc'length downto 0));
      end if;
      fracts (0) := fracts (0) or sticky;  -- Or the sticky bit into the LSB
      if fp_sign = to_X01(c(c'high)) then
        ufract  := fractc + fracts;
        fp_sign := fp_sign;
      else                              -- signs are different
        ufract := fractc - fracts;      -- always positive result
        if leftright then               -- Figure out which sign to use
          fp_sign := fp_sign;
        else
          fp_sign := c(c'high);
        end if;
      end if;
      -- normalize
      fpresult := normalize (fract          => ufract,
                             expon          => rexpon2,
                             sign           => fp_sign,
                             sticky         => sticky,
                             fraction_width => fraction_width,
                             exponent_width => exponent_width,
                             round_style    => round_style,
                             denormalize    => denormalize,
                             nguard         => guard);
    end if;
    return fpresult;
  end function mac;

  -- "rem" function
  function remainder (
    l, r                 : UNRESOLVED_float;       -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width   : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    constant divguard         : NATURAL := guard;  -- division guard bits
    variable lfptype, rfptype : valid_fpstate;
    variable fpresult         : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable ulfract, urfract : UNSIGNED (fraction_width downto 0);
    variable fractr, fractl   : UNSIGNED (fraction_width+divguard downto 0);  -- right
    variable rfract           : UNSIGNED (fractr'range);    -- result fraction
    variable sfract           : UNSIGNED (fraction_width+divguard downto 0);  -- result fraction
    variable exponl, exponr   : SIGNED (exponent_width-1 downto 0);  -- exponents
    variable rexpon           : SIGNED (exponent_width downto 0);  -- result exponent
    variable fp_sign          : STD_ULOGIC;        -- sign of result
    variable shifty           : INTEGER;           -- denormal number shift
    variable lresize, rresize : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- remainder
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      lfptype := isx;
    else
      lfptype := classfp (l, check_error);
      rfptype := classfp (r, check_error);
    end if;
    if (lfptype = isx or rfptype = isx) then
      fpresult := (others => 'X');
    elsif (lfptype = nan or lfptype = quiet_nan)
      or (rfptype = nan or rfptype = quiet_nan)
      -- Return quiet NAN, IEEE754-1985-7.1,1
      or (lfptype = pos_inf or lfptype = neg_inf)  -- inf rem x
      -- Return quiet NAN, IEEE754-1985-7.1,5
      or (rfptype = pos_zero or rfptype = neg_zero) then    -- x rem 0
      -- Return quiet NAN, IEEE754-1985-7.1,5
      fpresult := qnanfp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    elsif (rfptype = pos_inf or rfptype = neg_inf) then     -- x rem inf = 0
      fpresult := zerofp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    elsif (abs(l) < abs(r)) then
      fpresult := l;
    else
      fp_sign := to_X01(l(l'high));     -- sign
      lresize := resize (arg            => to_x01(l),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      lfptype := classfp (lresize, false);         -- errors already checked
      rresize := resize (arg            => to_x01(r),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      rfptype := classfp (rresize, false);         -- errors already checked
      fractl  := (others => '0');
      break_number (
        arg         => lresize,
        fptyp       => lfptype,
        denormalize => denormalize,
        fract       => ulfract,
        expon       => exponl);
      fractl (fraction_width+divguard downto divguard) := ulfract;
      -- right side
      fractr := (others => '0');
      break_number (
        arg         => rresize,
        fptyp       => rfptype,
        denormalize => denormalize,
        fract       => urfract,
        expon       => exponr);
      fractr (fraction_width+divguard downto divguard) := urfract;
      rexpon := (exponr(exponr'high)&exponr);
      shifty := to_integer(exponl - rexpon);
      if (shifty > 0) then
        fractr := shift_right (fractr, shifty);
        rexpon := rexpon + shifty;
      end if;
      if (fractr /= 0) then
        -- rem
        rfract := fractl rem fractr;    -- unsigned rem
        sfract := rfract (sfract'range);           -- lower bits
        -- normalize
        fpresult := normalize (fract          => sfract,
                               expon          => rexpon,
                               sign           => fp_sign,
                               fraction_width => fraction_width,
                               exponent_width => exponent_width,
                               round_style    => round_style,
                               denormalize    => denormalize,
                               nguard         => divguard);
      else
        -- If we shift "fractr" so far that it becomes zero, return zero.
        fpresult := zerofp (fraction_width => fraction_width,
                            exponent_width => exponent_width);
      end if;
    end if;
    return fpresult;
  end function remainder;

  -- "mod" function
  function modulo (
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant guard       : NATURAL    := float_guard_bits;  -- number of guard bits
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width   : NATURAL := - mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lfptype, rfptype : valid_fpstate;
    variable fpresult         : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable remres           : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- remainder
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      lfptype := isx;
    else
      lfptype := classfp (l, check_error);
      rfptype := classfp (r, check_error);
    end if;
    if (lfptype = isx or rfptype = isx) then
      fpresult := (others => 'X');
    elsif (lfptype = nan or lfptype = quiet_nan)
      or (rfptype = nan or rfptype = quiet_nan)
      -- Return quiet NAN, IEEE754-1985-7.1,1
      or (lfptype = pos_inf or lfptype = neg_inf)           -- inf rem x
      -- Return quiet NAN, IEEE754-1985-7.1,5
      or (rfptype = pos_zero or rfptype = neg_zero) then    -- x rem 0
      -- Return quiet NAN, IEEE754-1985-7.1,5
      fpresult := qnanfp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    elsif (rfptype = pos_inf or rfptype = neg_inf) then     -- x rem inf = 0
      fpresult := zerofp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
    else
      remres := remainder (l           => abs(l),
                           r           => abs(r),
                           round_style => round_style,
                           guard       => guard,
                           check_error => false,
                           denormalize => denormalize);
      -- MOD is the same as REM, but you do something different with
      -- negative values
      if (is_negative (l)) then
        remres := - remres;
      end if;
      if (is_negative (l) = is_negative (r) or remres = 0) then
        fpresult := remres;
      else
        fpresult := add (l           => remres,
                         r           => r,
                         round_style => round_style,
                         guard       => guard,
                         check_error => false,
                         denormalize => denormalize);        
      end if;
    end if;
    return fpresult;
  end function modulo;

  -- Square root of a floating point number.  Done using Newton's Iteration.
  function sqrt (
    arg                  : UNRESOLVED_float;        -- floating point input
    constant round_style : round_type := float_round_style;
    constant guard       : NATURAL    := float_guard_bits;
    constant check_error : BOOLEAN    := float_check_error;
    constant denormalize : BOOLEAN    := float_denormalize)
    return UNRESOLVED_float is
    constant fraction_width : NATURAL := guard-arg'low;  -- length of FP output fraction
    constant exponent_width : NATURAL := arg'high;  -- length of FP output exponent
    variable sign           : STD_ULOGIC;
    variable fpresult       : float (arg'range);
    variable fptype         : valid_fpstate;
    variable iexpon         : SIGNED(exponent_width-1 downto 0);  -- exponents
    variable expon          : SIGNED(exponent_width downto 0);    -- exponents
    variable ufact          : ufixed (0 downto arg'low);
    variable fact           : ufixed (2 downto -fraction_width);  -- fraction
    variable resb           : ufixed (fact'high+1 downto fact'low);
  begin  -- square root
    fptype := Classfp (arg, check_error);
    classcase : case fptype is
      when isx =>
        fpresult := (others => 'X');
      when nan | quiet_nan |
        -- Return quiet NAN, IEEE754-1985-7.1,1
        neg_normal | neg_denormal | neg_inf =>      -- sqrt (neg)
        -- Return quiet NAN, IEEE754-1985-7.1.6
        fpresult := qnanfp (fraction_width => fraction_width-guard,
                            exponent_width => exponent_width);
      when pos_inf =>                   -- Sqrt (inf), return infinity
        fpresult := pos_inffp (fraction_width => fraction_width-guard,
                               exponent_width => exponent_width);
      when pos_zero =>                  -- return 0
        fpresult := zerofp (fraction_width => fraction_width-guard,
                            exponent_width => exponent_width);
      when neg_zero =>                  -- IEEE754-1985-6.3 return -0
        fpresult := neg_zerofp (fraction_width => fraction_width-guard,
                                exponent_width => exponent_width);
      when others =>
        break_number (arg         => arg,
                      denormalize => denormalize,
                      check_error => false,
                      fract       => ufact,
                      expon       => iexpon,
                      sign        => sign);
        expon := resize (iexpon+1, expon'length);   -- get exponent
        fact  := resize (ufact, fact'high, fact'low);
        if (expon(0) = '1') then
          fact := fact sla 1;           -- * 2.0
        end if;
        expon := shift_right (expon, 1);            -- exponent/2
        -- Newton's iteration - root := (1 + arg) / 2
        resb  := (fact + 1) sra 1;
        for j in 0 to fraction_width/4 loop
          --   root := (root + (arg/root))/2
          resb := resize (arg            => (resb + (fact/resb)) sra 1,
                          left_index     => resb'high,
                          right_index    => resb'low,
                          round_style    => fixed_truncate,
                          overflow_style => fixed_wrap);
        end loop;
        fpresult := normalize (fract          => resb,
                               expon          => expon-1,
                               sign           => '0',
                               exponent_width => arg'high,
                               fraction_width => -arg'low,
                               round_style    => round_style,
                               denormalize    => denormalize,
                               nguard         => guard);
    end case classcase;
    return fpresult;
  end function sqrt;

  function Is_Negative (arg : UNRESOLVED_float) return BOOLEAN is
    -- Technically -0 should return "false", but I'm leaving that case out.
  begin
    return (to_x01(arg(arg'high)) = '1');
  end function Is_Negative;

  -- compare functions
  -- =, /=, >=, <=, <, >

  function eq (                         -- equal =
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN is
    variable lfptype, rfptype       : valid_fpstate;
    variable is_equal, is_unordered : BOOLEAN;
    constant fraction_width         : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width         : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lresize, rresize       : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- equal
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      return false;
    else
      lfptype := classfp (l, check_error);
      rfptype := classfp (r, check_error);
    end if;
    if (lfptype = neg_zero or lfptype = pos_zero) and
      (rfptype = neg_zero or rfptype = pos_zero) then
      is_equal := true;
    else
      lresize := resize (arg            => to_x01(l),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      rresize := resize (arg            => to_x01(r),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      is_equal := (to_slv(lresize) = to_slv(rresize));
    end if;
    if (check_error) then
      is_unordered := Unordered (x => l,
                                 y => r);
    else
      is_unordered := false;
    end if;
    return is_equal and not is_unordered;
  end function eq;

  function lt (                         -- less than <
    l, r                 : UNRESOLVED_float;         -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN is
    constant fraction_width             : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width             : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lfptype, rfptype           : valid_fpstate;
    variable expl, expr                 : UNSIGNED (exponent_width-1 downto 0);
    variable fractl, fractr             : UNSIGNED (fraction_width-1 downto 0);
    variable is_less_than, is_unordered : BOOLEAN;
    variable lresize, rresize           : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      is_less_than := false;
    else
      lresize := resize (arg            => to_x01(l),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      rresize := resize (arg            => to_x01(r),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      if to_x01(l(l'high)) = to_x01(r(r'high)) then  -- sign bits
        expl := UNSIGNED(lresize(exponent_width-1 downto 0));
        expr := UNSIGNED(rresize(exponent_width-1 downto 0));
        if expl = expr then
          fractl := UNSIGNED (to_slv(lresize(-1 downto -fraction_width)));
          fractr := UNSIGNED (to_slv(rresize(-1 downto -fraction_width)));
          if to_x01(l(l'high)) = '0' then            -- positive number
            is_less_than := (fractl < fractr);
          else
            is_less_than := (fractl > fractr);       -- negative
          end if;
        else
          if to_x01(l(l'high)) = '0' then            -- positive number
            is_less_than := (expl < expr);
          else
            is_less_than := (expl > expr);           -- negative
          end if;
        end if;
      else
        lfptype := classfp (l, check_error);
        rfptype := classfp (r, check_error);
        if (lfptype = neg_zero and rfptype = pos_zero) then
          is_less_than := false;        -- -0 < 0 returns false.
        else
          is_less_than := (to_x01(l(l'high)) > to_x01(r(r'high)));
        end if;
      end if;
    end if;
    if check_error then
      is_unordered := Unordered (x => l,
                                 y => r);
    else
      is_unordered := false;
    end if;
    return is_less_than and not is_unordered;
  end function lt;

  function gt (                         -- greater than >
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN is
    constant fraction_width   : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lfptype, rfptype : valid_fpstate;
    variable expl, expr       : UNSIGNED (exponent_width-1 downto 0);
    variable fractl, fractr   : UNSIGNED (fraction_width-1 downto 0);
    variable is_greater_than  : BOOLEAN;
    variable is_unordered     : BOOLEAN;
    variable lresize, rresize : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- greater_than
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      is_greater_than := false;
    else
      lresize := resize (arg            => to_x01(l),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      rresize := resize (arg            => to_x01(r),
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => denormalize,
                         denormalize    => denormalize);
      if to_x01(l(l'high)) = to_x01(r(r'high)) then              -- sign bits
        expl := UNSIGNED(lresize(exponent_width-1 downto 0));
        expr := UNSIGNED(rresize(exponent_width-1 downto 0));
        if expl = expr then
          fractl := UNSIGNED (to_slv(lresize(-1 downto -fraction_width)));
          fractr := UNSIGNED (to_slv(rresize(-1 downto -fraction_width)));
          if to_x01(l(l'high)) = '0' then     -- positive number
            is_greater_than := fractl > fractr;
          else
            is_greater_than := fractl < fractr;                  -- negative
          end if;
        else
          if to_x01(l(l'high)) = '0' then     -- positive number
            is_greater_than := expl > expr;
          else
            is_greater_than := expl < expr;   -- negative
          end if;
        end if;
      else
        lfptype := classfp (l, check_error);
        rfptype := classfp (r, check_error);
        if (lfptype = pos_zero and rfptype = neg_zero) then
          is_greater_than := false;     -- 0 > -0 returns false.
        else
          is_greater_than := to_x01(l(l'high)) < to_x01(r(r'high));
        end if;
      end if;
    end if;
    if check_error then
      is_unordered := Unordered (x => l,
                                 y => r);
    else
      is_unordered := false;
    end if;
    return is_greater_than and not is_unordered;
  end function gt;

  -- purpose: /= function
  function ne (                         -- not equal /=
    l, r                 : UNRESOLVED_float;
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN is
    variable is_equal, is_unordered : BOOLEAN;
  begin
    is_equal := eq (l           => l,
                    r           => r,
                    check_error => false,
                    denormalize => denormalize);
    if check_error then
      is_unordered := Unordered (x => l,
                                 y => r);
    else
      is_unordered := false;
    end if;
    return not (is_equal and not is_unordered);
  end function ne;

  function le (                               -- less than or equal to <=
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN is
    variable is_greater_than, is_unordered : BOOLEAN;
  begin
    is_greater_than := gt (l           => l,
                           r           => r,
                           check_error => false,
                           denormalize => denormalize);
    if check_error then
      is_unordered := Unordered (x => l,
                                 y => r);
    else
      is_unordered := false;
    end if;
    return not is_greater_than and not is_unordered;
  end function le;

  function ge (                               -- greater than or equal to >=
    l, r                 : UNRESOLVED_float;  -- floating point input
    constant check_error : BOOLEAN := float_check_error;
    constant denormalize : BOOLEAN := float_denormalize)
    return BOOLEAN is
    variable is_less_than, is_unordered : BOOLEAN;
  begin
    is_less_than := lt (l           => l,
                        r           => r,
                        check_error => false,
                        denormalize => denormalize);
    if check_error then
      is_unordered := Unordered (x => l,
                                 y => r);
    else
      is_unordered := false;
    end if;
    return not is_less_than and not is_unordered;
  end function ge;

  function \?=\ (L, R : UNRESOLVED_float) return STD_ULOGIC is
    constant fraction_width         : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width         : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lfptype, rfptype       : valid_fpstate;
    variable is_equal, is_unordered : STD_ULOGIC;
    variable lresize, rresize       : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- ?=
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      return 'X';
    else
      lfptype := classfp (l, float_check_error);
      rfptype := classfp (r, float_check_error);
    end if;
    if (lfptype = neg_zero or lfptype = pos_zero) and
      (rfptype = neg_zero or rfptype = pos_zero) then
      is_equal := '1';
    else
      lresize := resize (arg            => l,
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => float_denormalize,
                         denormalize    => float_denormalize);
      rresize := resize (arg            => r,
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => float_denormalize,
                         denormalize    => float_denormalize);
      is_equal := \?=\ (to_sulv(lresize), to_sulv(rresize));
    end if;
    if (float_check_error) then
      if (lfptype = nan or lfptype = quiet_nan or
          rfptype = nan or rfptype = quiet_nan) then
        is_unordered := '1';
      else
        is_unordered := '0';
      end if;
    else
      is_unordered := '0';
    end if;
    return is_equal and not is_unordered;
  end function \?=\;

  function \?/=\ (L, R : UNRESOLVED_float) return STD_ULOGIC is
    constant fraction_width         : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width         : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lfptype, rfptype       : valid_fpstate;
    variable is_equal, is_unordered : STD_ULOGIC;
    variable lresize, rresize       : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- ?/=
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      return 'X';
    else
      lfptype := classfp (l, float_check_error);
      rfptype := classfp (r, float_check_error);
    end if;
    if (lfptype = neg_zero or lfptype = pos_zero) and
      (rfptype = neg_zero or rfptype = pos_zero) then
      is_equal := '1';
    else
      lresize := resize (arg            => l,
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => float_denormalize,
                         denormalize    => float_denormalize);
      rresize := resize (arg            => r,
                         exponent_width => exponent_width,
                         fraction_width => fraction_width,
                         denormalize_in => float_denormalize,
                         denormalize    => float_denormalize);
      is_equal := \?=\ (to_sulv(lresize), to_sulv(rresize));
    end if;
    if (float_check_error) then
      if (lfptype = nan or lfptype = quiet_nan or
          rfptype = nan or rfptype = quiet_nan) then
        is_unordered := '1';
      else
        is_unordered := '0';
      end if;
    else
      is_unordered := '0';
    end if;
    return not (is_equal and not is_unordered);
  end function \?/=\;

  function \?>\ (L, R : UNRESOLVED_float) return STD_ULOGIC is
    constant fraction_width : NATURAL := -mine(l'low, r'low);
    variable founddash      : BOOLEAN := false;
  begin
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      return 'X';
    else
      for i in L'range loop
        if L(i) = '-' then
          founddash := true;
        end if;
      end loop;
      for i in R'range loop
        if R(i) = '-' then
          founddash := true;
        end if;
      end loop;
      if founddash then
        report float_pkg'instance_name
          & " ""?>"": '-' found in compare string"
          severity error;
        return 'X';
      elsif is_x(l) or is_x(r) then
        return 'X';
      elsif l > r then
        return '1';
      else
        return '0';
      end if;
    end if;
  end function \?>\;

  function \?>=\ (L, R : UNRESOLVED_float) return STD_ULOGIC is
    constant fraction_width : NATURAL := -mine(l'low, r'low);
    variable founddash      : BOOLEAN := false;
  begin
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      return 'X';
    else
      for i in L'range loop
        if L(i) = '-' then
          founddash := true;
        end if;
      end loop;
      for i in R'range loop
        if R(i) = '-' then
          founddash := true;
        end if;
      end loop;
      if founddash then
        report float_pkg'instance_name
          & " ""?>="": '-' found in compare string"
          severity error;
        return 'X';
      elsif is_x(l) or is_x(r) then
        return 'X';
      elsif l >= r then
        return '1';
      else
        return '0';
      end if;
    end if;
  end function \?>=\;

  function \?<\ (L, R : UNRESOLVED_float) return STD_ULOGIC is
    constant fraction_width : NATURAL := -mine(l'low, r'low);
    variable founddash      : BOOLEAN := false;
  begin
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      return 'X';
    else
      for i in L'range loop
        if L(i) = '-' then
          founddash := true;
        end if;
      end loop;
      for i in R'range loop
        if R(i) = '-' then
          founddash := true;
        end if;
      end loop;
      if founddash then
        report float_pkg'instance_name
          & " ""?<"": '-' found in compare string"
          severity error;
        return 'X';
      elsif is_x(l) or is_x(r) then
        return 'X';
      elsif l < r then
        return '1';
      else
        return '0';
      end if;
    end if;
  end function \?<\;

  function \?<=\ (L, R : UNRESOLVED_float) return STD_ULOGIC is
    constant fraction_width : NATURAL := -mine(l'low, r'low);
    variable founddash      : BOOLEAN := false;
  begin
    if (fraction_width = 0 or l'length < 7 or r'length < 7) then
      return 'X';
    else
      for i in L'range loop
        if L(i) = '-' then
          founddash := true;
        end if;
      end loop;
      for i in R'range loop
        if R(i) = '-' then
          founddash := true;
        end if;
      end loop;
      if founddash then
        report float_pkg'instance_name
          & " ""?<="": '-' found in compare string"
          severity error;
        return 'X';
      elsif is_x(l) or is_x(r) then
        return 'X';
      elsif l <= r then
        return '1';
      else
        return '0';
      end if;
    end if;
  end function \?<=\;

  function std_match (L, R : UNRESOLVED_float) return BOOLEAN is
  begin
    if (L'high = R'high and L'low = R'low) then
      return std_match(to_sulv(L), to_sulv(R));
    else
      report float_pkg'instance_name
        & "STD_MATCH: L'RANGE /= R'RANGE, returning FALSE"
        severity warning;
      return false;
    end if;
  end function std_match;

  function find_rightmost (arg : UNRESOLVED_float; y : STD_ULOGIC) return INTEGER is
  begin
    for_loop : for i in arg'reverse_range loop
      if \?=\ (arg(i), y) = '1' then
        return i;
      end if;
    end loop;
    return arg'high+1;                  -- return out of bounds 'high
  end function find_rightmost;

  function find_leftmost (arg : UNRESOLVED_float; y : STD_ULOGIC) return INTEGER is
  begin
    for_loop : for i in arg'range loop
      if \?=\ (arg(i), y) = '1' then
        return i;
      end if;
    end loop;
    return arg'low-1;                   -- return out of bounds 'low
  end function find_leftmost;

  -- These override the defaults for the compare operators.
  function "=" (l, r : UNRESOLVED_float) return BOOLEAN is
  begin
    return eq(l, r);
  end function "=";

  function "/=" (l, r : UNRESOLVED_float) return BOOLEAN is
  begin
    return ne(l, r);
  end function "/=";

  function ">=" (l, r : UNRESOLVED_float) return BOOLEAN is
  begin
    return ge(l, r);
  end function ">=";

  function "<=" (l, r : UNRESOLVED_float) return BOOLEAN is
  begin
    return le(l, r);
  end function "<=";

  function ">" (l, r : UNRESOLVED_float) return BOOLEAN is
  begin
    return gt(l, r);
  end function ">";

  function "<" (l, r : UNRESOLVED_float) return BOOLEAN is
  begin
    return lt(l, r);
  end function "<";

  -- purpose: maximum of two numbers (overrides default)
  function maximum (
    L, R : UNRESOLVED_float)
    return UNRESOLVED_float is
    constant fraction_width   : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lresize, rresize : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin
    if ((L'length < 1) or (R'length < 1)) then return NAFP;
    end if;
    lresize := resize (l, exponent_width, fraction_width);
    rresize := resize (r, exponent_width, fraction_width);
    if lresize > rresize then return lresize;
    else return rresize;
    end if;
  end function maximum;

  function minimum (
    L, R : UNRESOLVED_float)
    return UNRESOLVED_float is
    constant fraction_width   : NATURAL := -mine(l'low, r'low);  -- length of FP output fraction
    constant exponent_width   : NATURAL := maximum(l'high, r'high);  -- length of FP output exponent
    variable lresize, rresize : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin
    if ((L'length < 1) or (R'length < 1)) then return NAFP;
    end if;
    lresize := resize (l, exponent_width, fraction_width);
    rresize := resize (r, exponent_width, fraction_width);
    if lresize > rresize then return rresize;
    else return lresize;
    end if;
  end function minimum;

  -----------------------------------------------------------------------------
  -- conversion functions
  -----------------------------------------------------------------------------

  -- Converts a floating point number of one format into another format
  function resize (
    arg                     : UNRESOLVED_float;        -- Floating point input
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant in_fraction_width : NATURAL := -arg'low;  -- length of FP output fraction
    constant in_exponent_width : NATURAL := arg'high;  -- length of FP output exponent
    variable result            : UNRESOLVED_float (exponent_width downto -fraction_width);
                                        -- result value
    variable fptype            : valid_fpstate;
    variable expon_in          : SIGNED (in_exponent_width-1 downto 0);
    variable fract_in          : UNSIGNED (in_fraction_width downto 0);
    variable round             : BOOLEAN;
    variable expon_out         : SIGNED (exponent_width-1 downto 0);  -- output fract
    variable fract_out         : UNSIGNED (fraction_width downto 0);  -- output fract
    variable passguard         : NATURAL;
  begin
    fptype := classfp(arg, check_error);
    if ((fptype = pos_denormal or fptype = neg_denormal) and denormalize_in
        and (in_exponent_width < exponent_width
             or in_fraction_width < fraction_width))
      or in_exponent_width > exponent_width
      or in_fraction_width > fraction_width then
      -- size reduction
      classcase : case fptype is
        when isx =>
          result := (others => 'X');
        when nan | quiet_nan =>
          result := qnanfp (fraction_width => fraction_width,
                            exponent_width => exponent_width);
        when pos_inf =>
          result := pos_inffp (fraction_width => fraction_width,
                               exponent_width => exponent_width);
        when neg_inf =>
          result := neg_inffp (fraction_width => fraction_width,
                               exponent_width => exponent_width);
        when pos_zero | neg_zero =>
          result := zerofp (fraction_width => fraction_width,   -- hate -0
                            exponent_width => exponent_width);
        when others =>
          break_number (
            arg         => arg,
            fptyp       => fptype,
            denormalize => denormalize_in,
            fract       => fract_in,
            expon       => expon_in);
          if fraction_width > in_fraction_width and denormalize_in then
            -- You only get here if you have a denormal input
            fract_out := (others => '0');              -- pad with zeros
            fract_out (fraction_width downto
                       fraction_width - in_fraction_width) := fract_in;
            result := normalize (
              fract          => fract_out,
              expon          => expon_in,
              sign           => arg(arg'high),
              fraction_width => fraction_width,
              exponent_width => exponent_width,
              round_style    => round_style,
              denormalize    => denormalize,
              nguard         => 0);
          else
            result := normalize (
              fract          => fract_in,
              expon          => expon_in,
              sign           => arg(arg'high),
              fraction_width => fraction_width,
              exponent_width => exponent_width,
              round_style    => round_style,
              denormalize    => denormalize,
              nguard         => in_fraction_width - fraction_width);
          end if;
      end case classcase;
    else                                -- size increase or the same size
      if exponent_width > in_exponent_width then
        expon_in := SIGNED(arg (in_exponent_width-1 downto 0));
        if fptype = pos_zero or fptype = neg_zero then
          result (exponent_width-1 downto 0) := (others => '0');
        elsif expon_in = -1 then        -- inf or nan (shorts out check_error)
          result (exponent_width-1 downto 0) := (others => '1');
        else
          -- invert top BIT
          expon_in(expon_in'high)            := not expon_in(expon_in'high);
          expon_out := resize (expon_in, expon_out'length);  -- signed expand
          -- Flip it back.
          expon_out(expon_out'high)          := not expon_out(expon_out'high);
          result (exponent_width-1 downto 0) := UNRESOLVED_float(expon_out);
        end if;
        result (exponent_width) := arg (in_exponent_width);     -- sign
      else                              -- exponent_width = in_exponent_width
        result (exponent_width downto 0) := arg (in_exponent_width downto 0);
      end if;
      if fraction_width > in_fraction_width then
        result (-1 downto -fraction_width) := (others => '0');  -- zeros
        result (-1 downto -in_fraction_width) :=
          arg (-1 downto -in_fraction_width);
      else                              -- fraction_width = in_fraciton_width
        result (-1 downto -fraction_width) :=
          arg (-1 downto -in_fraction_width);
      end if;
    end if;
    return result;
  end function resize;

  function resize (
    arg                     : UNRESOLVED_float;  -- floating point input
    size_res                : UNRESOLVED_float;
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := resize (arg            => arg,
                        exponent_width => size_res'high,
                        fraction_width => -size_res'low,
                        round_style    => round_style,
                        check_error    => check_error,
                        denormalize_in => denormalize_in,
                        denormalize    => denormalize);
      return result;
    end if;
  end function resize;

  function to_float32 (
    arg                     : UNRESOLVED_float;
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float32 is
  begin
    return resize (arg            => arg,
                   exponent_width => float32'high,
                   fraction_width => -float32'low,
                   round_style    => round_style,
                   check_error    => check_error,
                   denormalize_in => denormalize_in,
                   denormalize    => denormalize);
  end function to_float32;

  function to_float64 (
    arg                     : UNRESOLVED_float;
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float64 is
  begin
    return resize (arg            => arg,
                   exponent_width => float64'high,
                   fraction_width => -float64'low,
                   round_style    => round_style,
                   check_error    => check_error,
                   denormalize_in => denormalize_in,
                   denormalize    => denormalize);
  end function to_float64;

  function to_float128 (
    arg                     : UNRESOLVED_float;
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant check_error    : BOOLEAN    := float_check_error;
    constant denormalize_in : BOOLEAN    := float_denormalize;  -- Use IEEE extended FP
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float128 is
  begin
    return resize (arg            => arg,
                   exponent_width => float128'high,
                   fraction_width => -float128'low,
                   round_style    => round_style,
                   check_error    => check_error,
                   denormalize_in => denormalize_in,
                   denormalize    => denormalize);
  end function to_float128;

  -- to_float (Real)
  -- typically not Synthesizable unless the input is a constant.
  function to_float (
    arg                     : REAL;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style;  -- rounding option
    constant denormalize    : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    variable result     : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable arg_real   : REAL;         -- Real version of argument
    variable validfp    : boundary_type;      -- Check for valid results
    variable exp        : INTEGER;      -- Integer version of exponent
    variable expon      : UNSIGNED (exponent_width - 1 downto 0);
                                        -- Unsigned version of exp.
    constant expon_base : SIGNED (exponent_width-1 downto 0) :=
      gen_expon_base(exponent_width);   -- exponent offset
    variable fract     : UNSIGNED (fraction_width-1 downto 0);
    variable frac      : REAL;          -- Real version of fraction
    constant roundfrac : REAL := 2.0 ** (-2 - fract'high);  -- used for rounding
    variable round     : BOOLEAN;       -- to round or not to round
  begin
    result   := (others => '0');
    arg_real := arg;
    if arg_real < 0.0 then
      result (exponent_width) := '1';
      arg_real                := - arg_real;  -- Make it positive.
    else
      result (exponent_width) := '0';
    end if;
    test_boundary (arg            => arg_real,
                   fraction_width => fraction_width,
                   exponent_width => exponent_width,
                   denormalize    => denormalize,
                   btype          => validfp,
                   log2i          => exp);
    if validfp = zero then
      return result;                    -- Result initialized to "0".
    elsif validfp = infinity then
      result (exponent_width - 1 downto 0) := (others => '1');  -- Exponent all "1"
                                        -- return infinity.
      return result;
    else
      if validfp = denormal then        -- Exponent will default to "0".
        expon := (others => '0');
        frac  := arg_real * (2.0 ** (to_integer(expon_base)-1));
      else                              -- Number less than 1. "normal" number
        expon := UNSIGNED (to_signed (exp-1, exponent_width));
        expon(exponent_width-1) := not expon(exponent_width-1);
        frac := (arg_real / 2.0 ** exp) - 1.0;  -- Number less than 1.
      end if;
      for i in 0 to fract'high loop
        if frac >= 2.0 ** (-1 - i) then
          fract (fract'high - i) := '1';
          frac := frac - 2.0 ** (-1 - i);
        else
          fract (fract'high - i) := '0';
        end if;
      end loop;
      round := false;
      case round_style is
        when round_nearest =>
          if frac > roundfrac or ((frac = roundfrac) and fract(0) = '1') then
            round := true;
          end if;
        when round_inf =>
          if frac /= 0.0 and result(exponent_width) = '0' then
            round := true;
          end if;
        when round_neginf =>
          if frac /= 0.0 and result(exponent_width) = '1' then
            round := true;
          end if;
        when others =>
          null;                         -- don't round
      end case;
      if (round) then
        if and_reduce (fract) = '1' then      -- fraction is all "1"
          expon := expon + 1;
          fract := (others => '0');
        else
          fract := fract + 1;
        end if;
      end if;
      result (exponent_width-1 downto 0) := UNRESOLVED_float(expon);
      result (-1 downto -fraction_width) := UNRESOLVED_float(fract);
      return result;
    end if;
  end function to_float;

  -- to_float (Integer)
  function to_float (
    arg                     : INTEGER;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float is
    variable result     : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable arg_int    : NATURAL;      -- Natural version of argument
    variable expon      : SIGNED (exponent_width-1 downto 0);
    variable exptmp     : SIGNED (exponent_width-1 downto 0);
    -- Unsigned version of exp.
    constant expon_base : SIGNED (exponent_width-1 downto 0) :=
      gen_expon_base(exponent_width);   -- exponent offset
    variable fract     : UNSIGNED (fraction_width-1 downto 0) := (others => '0');
    variable fracttmp  : UNSIGNED (fraction_width-1 downto 0);
    variable round     : BOOLEAN;
    variable shift     : NATURAL;
    variable shiftr    : NATURAL;
    variable roundfrac : NATURAL;       -- used in rounding
  begin
    if arg < 0 then
      result (exponent_width) := '1';
      arg_int                 := -arg;  -- Make it positive.
    else
      result (exponent_width) := '0';
      arg_int                 := arg;
    end if;
    if arg_int = 0 then
      result := zerofp (fraction_width => fraction_width,
                        exponent_width => exponent_width);
    else
      -- If the number is larger than we can represent in this number system
      -- we need to return infinity.
      shift := log2(arg_int);
      if shift > to_integer(expon_base) then
        -- worry about infinity
        if result (exponent_width) = '0' then
          result := pos_inffp (fraction_width => fraction_width,
                               exponent_width => exponent_width);
        else
          -- return negative infinity.
          result := neg_inffp (fraction_width => fraction_width,
                               exponent_width => exponent_width);
        end if;
      else                              -- Normal number (can't be denormal)
        -- Compute Exponent
        expon   := to_signed (shift-1, expon'length);  -- positive fraction.
        -- Compute Fraction
        arg_int := arg_int - 2**shift;  -- Subtract off the 1.0
        shiftr  := shift;
        for I in fract'high downto maximum (fract'high - shift + 1, 0) loop
          shiftr := shiftr - 1;
          if (arg_int >= 2**shiftr) then
            arg_int  := arg_int - 2**shiftr;
            fract(I) := '1';
          else
            fract(I) := '0';
          end if;
        end loop;
        -- Rounding routine
        round := false;
        if arg_int > 0 then
          roundfrac := 2**(shiftr-1);
          case round_style is
            when round_nearest =>
              if arg_int > roundfrac or
                ((arg_int = roundfrac) and fract(0) = '1') then
                round := true;
              end if;
            when round_inf =>
              if arg_int /= 0 and result (exponent_width) = '0' then
                round := true;
              end if;
            when round_neginf =>
              if arg_int /= 0 and result (exponent_width) = '1' then
                round := true;
              end if;
            when others =>
              null;
          end case;
        end if;
        if round then
          fp_round(fract_in  => fract,
                   expon_in  => expon,
                   fract_out => fracttmp,
                   expon_out => exptmp);
          fract := fracttmp;
          expon := exptmp;
        end if;
        -- Put the number together and return
        expon(exponent_width-1)            := not expon(exponent_width-1);
        result (exponent_width-1 downto 0) := UNRESOLVED_float(expon);
        result (-1 downto -fraction_width) := UNRESOLVED_float(fract);
      end if;
    end if;
    return result;
  end function to_float;

  -- to_float (unsigned)
  function to_float (
    arg                     : UNSIGNED;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float is
    variable result   : UNRESOLVED_float (exponent_width downto -fraction_width);
    constant ARG_LEFT : INTEGER := ARG'length-1;
    alias XARG        : UNSIGNED(ARG_LEFT downto 0) is ARG;
    variable sarg     : SIGNED (ARG_LEFT+1 downto 0);  -- signed version of arg
  begin
    if arg'length < 1 then
      return NAFP;
    end if;
    sarg (XARG'range) := SIGNED (XARG);
    sarg (sarg'high)  := '0';
    result := to_float (arg            => sarg,
                        exponent_width => exponent_width,
                        fraction_width => fraction_width,
                        round_style    => round_style);
    return result;
  end function to_float;

  -- to_float (signed)
  function to_float (
    arg                     : SIGNED;
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float is
    variable result     : UNRESOLVED_float (exponent_width downto -fraction_width);
    constant ARG_LEFT   : INTEGER := ARG'length-1;
    alias XARG          : SIGNED(ARG_LEFT downto 0) is ARG;
    variable arg_int    : UNSIGNED(xarg'range);  -- Real version of argument
    variable argb2      : UNSIGNED(xarg'high/2 downto 0);  -- log2 of input
    variable rexp       : SIGNED (exponent_width - 1 downto 0);
    variable exp        : SIGNED (exponent_width - 1 downto 0);
    -- signed version of exp.
    variable expon      : UNSIGNED (exponent_width - 1 downto 0);
    -- Unsigned version of exp.
    constant expon_base : SIGNED (exponent_width-1 downto 0) :=
      gen_expon_base(exponent_width);   -- exponent offset
    variable round  : BOOLEAN;
    variable fract  : UNSIGNED (fraction_width-1 downto 0);
    variable rfract : UNSIGNED (fraction_width-1 downto 0);
    variable sign   : STD_ULOGIC;         -- sign bit
  begin
    if arg'length < 1 then
      return NAFP;
    end if;
    if Is_X (xarg) then
      result := (others => 'X');
    elsif (xarg = 0) then
      result := zerofp (fraction_width => fraction_width,
                        exponent_width => exponent_width);
    else                                -- Normal number (can't be denormal)
      sign := to_X01(xarg (xarg'high));
      arg_int := UNSIGNED(abs (to_01(xarg)));
      -- Compute Exponent
      argb2 := to_unsigned(find_leftmost(arg_int, '1'), argb2'length);  -- Log2
      if argb2 > UNSIGNED(expon_base) then
        result := pos_inffp (fraction_width => fraction_width,
                             exponent_width => exponent_width);
        result (exponent_width) := sign;
      else
        exp     := SIGNED(resize(argb2, exp'length));
        arg_int := shift_left (arg_int, arg_int'high-to_integer(exp));
        if (arg_int'high > fraction_width) then
          fract := arg_int (arg_int'high-1 downto (arg_int'high-fraction_width));
          round := check_round (
            fract_in    => fract (0),
            sign        => sign,
            remainder   => arg_int((arg_int'high-fraction_width-1)
                                   downto 0),
            round_style => round_style);
          if round then
            fp_round(fract_in  => fract,
                     expon_in  => exp,
                     fract_out => rfract,
                     expon_out => rexp);
          else
            rfract := fract;
            rexp   := exp;
          end if;
        else
          rexp   := exp;
          rfract := (others => '0');
          rfract (fraction_width-1 downto fraction_width-1-(arg_int'high-1)) :=
            arg_int (arg_int'high-1 downto 0);
        end if;
        result (exponent_width) := sign;
        expon := UNSIGNED (rexp-1);
        expon(exponent_width-1)            := not expon(exponent_width-1);
        result (exponent_width-1 downto 0) := UNRESOLVED_float(expon);
        result (-1 downto -fraction_width) := UNRESOLVED_float(rfract);
      end if;
    end if;
    return result;
  end function to_float;

  -- std_logic_vector to float
  function to_float (
    arg                     : STD_ULOGIC_VECTOR;
    constant exponent_width : NATURAL := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- length of FP output fraction
    return UNRESOLVED_float is
    variable fpvar : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin
    if arg'length < 1 then
      return NAFP;
    end if;
    fpvar := UNRESOLVED_float(arg);
    return fpvar;
  end function to_float;

  -- purpose: converts a ufixed to a floating point
  function to_float (
    arg                     : UNRESOLVED_ufixed;  -- unsigned fixed point input
    constant exponent_width : NATURAL    := float_exponent_width;  -- width of exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- width of fraction
    constant round_style    : round_type := float_round_style;  -- rounding
    constant denormalize    : BOOLEAN    := float_denormalize)  -- use ieee extensions
    return UNRESOLVED_float is
    variable sarg   : sfixed (arg'high+1 downto arg'low);  -- Signed version of arg
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width);
  begin  -- function to_float
    if (arg'length < 1) then
      return NAFP;
    end if;
    sarg (arg'range) := sfixed (arg);
    sarg (sarg'high) := '0';
    result := to_float (arg            => sarg,
                        exponent_width => exponent_width,
                        fraction_width => fraction_width,
                        round_style    => round_style,
                        denormalize    => denormalize);
    return result;
  end function to_float;

  function to_float (
    arg                     : UNRESOLVED_sfixed;    -- signed fixed point
    constant exponent_width : NATURAL    := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL    := float_fraction_width;  -- length of FP output fraction
    constant round_style    : round_type := float_round_style;  -- rounding
    constant denormalize    : BOOLEAN    := float_denormalize)  -- rounding option
    return UNRESOLVED_float is
    constant integer_width     : INTEGER := arg'high;
    constant in_fraction_width : INTEGER := arg'low;
    variable xresult     : sfixed (integer_width downto in_fraction_width);
    variable result      : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable arg_int     : UNSIGNED(integer_width - in_fraction_width
                                    downto 0);  -- unsigned version of argument
    variable argx        : SIGNED (integer_width - in_fraction_width downto 0);
    variable exp, exptmp : SIGNED (exponent_width + 1 downto 0);
    variable expon       : UNSIGNED (exponent_width - 1 downto 0);
    -- Unsigned version of exp.
    constant expon_base  : SIGNED (exponent_width-1 downto 0) :=
      gen_expon_base(exponent_width);   -- exponent offset
    variable fract, fracttmp : UNSIGNED (fraction_width-1 downto 0) :=
      (others => '0');
    variable round : BOOLEAN := false;
  begin
    if (arg'length < 1) then
      return NAFP;
    end if;
    xresult := to_01(arg, 'X');
    argx    := SIGNED(to_slv(xresult));
    if (Is_X (arg)) then
      result := (others => 'X');
    elsif (argx = 0) then
      result := (others => '0');
    else
      result := (others => '0');        -- zero out the result
      if argx(argx'left) = '1' then     -- toss the sign bit
        result (exponent_width) := '1';     -- Negative number
        arg_int := UNSIGNED(to_x01(not STD_LOGIC_VECTOR (argx))) + 1; -- Make it positive with two's complement
      else
        result (exponent_width) := '0';
        arg_int := UNSIGNED(to_x01(STD_LOGIC_VECTOR (argx))); -- new line: direct conversion to unsigned
      end if;
      -- Compute Exponent
      exp     := to_signed(find_leftmost(arg_int, '1'), exp'length);  -- Log2
      if exp + in_fraction_width > expon_base then  -- return infinity
        result (-1 downto -fraction_width)  := (others => '0');
        result (exponent_width -1 downto 0) := (others => '1');
        return result;
      elsif (denormalize and
             (exp + in_fraction_width <= -resize(expon_base, exp'length))) then
        exp := -resize(expon_base, exp'length);
        -- shift by a constant
        arg_int := shift_left (arg_int,
                               (arg_int'high + to_integer(expon_base)
                                + in_fraction_width - 1));
        if (arg_int'high > fraction_width) then
          fract := arg_int (arg_int'high-1 downto (arg_int'high-fraction_width));
          round := check_round (
            fract_in    => arg_int(arg_int'high-fraction_width),
            sign        => result(result'high),
            remainder   => arg_int((arg_int'high-fraction_width-1)
                                   downto 0),
            round_style => round_style);
          if (round) then
            fp_round (fract_in => arg_int (arg_int'high-1 downto
                                           (arg_int'high-fraction_width)),
                      expon_in  => exp,
                      fract_out => fract,
                      expon_out => exptmp);
            exp := exptmp;
          end if;
        else
          fract (fraction_width-1 downto fraction_width-1-(arg_int'high-1)) :=
            arg_int (arg_int'high-1 downto 0);
        end if;
      else
        arg_int := shift_left (arg_int, arg_int'high-to_integer(exp));
        exp     := exp + in_fraction_width;
        if (arg_int'high > fraction_width) then
          fract := arg_int (arg_int'high-1 downto (arg_int'high-fraction_width));
          round := check_round (
            fract_in    => fract(0),
            sign        => result(result'high),
            remainder   => arg_int((arg_int'high-fraction_width-1)
                                   downto 0),
            round_style => round_style);
          if (round) then
            fp_round (fract_in  => fract,
                      expon_in  => exp,
                      fract_out => fracttmp,
                      expon_out => exptmp);
            fract := fracttmp;
            exp   := exptmp;
          end if;
        else
          fract (fraction_width-1 downto fraction_width-1-(arg_int'high-1)) :=
            arg_int (arg_int'high-1 downto 0);
        end if;
      end if;
      expon := UNSIGNED (resize(exp-1, exponent_width));
      expon(exponent_width-1)            := not expon(exponent_width-1);
      result (exponent_width-1 downto 0) := UNRESOLVED_float(expon);
      result (-1 downto -fraction_width) := UNRESOLVED_float(fract);
    end if;
    return result;
  end function to_float;

  -- size_res functions
  -- Integer to float
  function to_float (
    arg                  : INTEGER;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_float (arg            => arg,
                          exponent_width => size_res'high,
                          fraction_width => -size_res'low,
                          round_style    => round_style);
      return result;
    end if;
  end function to_float;

  -- real to float
  function to_float (
    arg                  : REAL;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style;  -- rounding option
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_float (arg            => arg,
                          exponent_width => size_res'high,
                          fraction_width => -size_res'low,
                          round_style    => round_style,
                          denormalize    => denormalize);
      return result;
    end if;
  end function to_float;

  -- unsigned to float
  function to_float (
    arg                  : UNSIGNED;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style)  -- rounding option
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_float (arg            => arg,
                          exponent_width => size_res'high,
                          fraction_width => -size_res'low,
                          round_style    => round_style);
      return result;
    end if;
  end function to_float;

  -- signed to float
  function to_float (
    arg                  : SIGNED;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style)  -- rounding
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_float (arg            => arg,
                          exponent_width => size_res'high,
                          fraction_width => -size_res'low,
                          round_style    => round_style);
      return result;
    end if;
  end function to_float;

  -- std_ulogic_vector to float
  function to_float (
    arg      : STD_ULOGIC_VECTOR;
    size_res : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_float (arg            => arg,
                          exponent_width => size_res'high,
                          fraction_width => -size_res'low);
      return result;
    end if;
  end function to_float;

  -- unsigned fixed point to float
  function to_float (
    arg                  : UNRESOLVED_ufixed;  -- unsigned fixed point input
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style;  -- rounding
    constant denormalize : BOOLEAN    := float_denormalize)  -- use ieee extensions
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_float (arg            => arg,
                          exponent_width => size_res'high,
                          fraction_width => -size_res'low,
                          round_style    => round_style,
                          denormalize    => denormalize);
      return result;
    end if;
  end function to_float;

  -- signed fixed point to float
  function to_float (
    arg                  : UNRESOLVED_sfixed;
    size_res             : UNRESOLVED_float;
    constant round_style : round_type := float_round_style;  -- rounding
    constant denormalize : BOOLEAN    := float_denormalize)  -- rounding option
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_float (arg            => arg,
                          exponent_width => size_res'high,
                          fraction_width => -size_res'low,
                          round_style    => round_style,
                          denormalize    => denormalize);
      return result;
    end if;
  end function to_float;

  -- to_integer (float)
  function to_integer (
    arg                  : UNRESOLVED_float;   -- floating point input
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return INTEGER is
    variable validfp : valid_fpstate;   -- Valid FP state
    variable frac    : UNSIGNED (-arg'low downto 0);         -- Fraction
    variable fract   : UNSIGNED (1-arg'low downto 0);        -- Fraction
    variable expon   : SIGNED (arg'high-1 downto 0);
    variable isign   : STD_ULOGIC;      -- internal version of sign
    variable round   : STD_ULOGIC;      -- is rounding needed?
    variable result  : INTEGER;
    variable base    : INTEGER;         -- Integer exponent
  begin
    validfp := classfp (arg, check_error);
    classcase : case validfp is
      when isx | nan | quiet_nan | pos_zero | neg_zero | pos_denormal | neg_denormal =>
        result := 0;                    -- return 0
      when pos_inf =>
        result := INTEGER'high;
      when neg_inf =>
        result := INTEGER'low;
      when others =>
        break_number (
          arg         => arg,
          fptyp       => validfp,
          denormalize => false,
          fract       => frac,
          expon       => expon);
        fract (fract'high)            := '0';  -- Add extra bit for 0.6 case
        fract (fract'high-1 downto 0) := frac;
        isign                         := to_x01 (arg (arg'high));
        base                          := to_integer (expon) + 1;
        if base < -1 then
          result := 0;
        elsif base >= frac'high then
          result := to_integer (fract) * 2**(base - frac'high);
        else                            -- We need to round
          if base = -1 then             -- trap for 0.6 case.
            result := 0;
          else
            result := to_integer (fract (frac'high downto frac'high-base));
          end if;
          -- rounding routine
          case round_style is
            when round_nearest =>
              if frac'high - base > 1 then
                round := fract (frac'high - base - 1) and
                         (fract (frac'high - base)
                          or (or_reduce (fract (frac'high - base - 2 downto 0))));
              else
                round := fract (frac'high - base - 1) and
                         fract (frac'high - base);
              end if;
            when round_inf =>
              round := fract(frac'high - base - 1) and not isign;
            when round_neginf =>
              round := fract(frac'high - base - 1) and isign;
            when others =>
              round := '0';
          end case;
          if round = '1' then
            result := result + 1;
          end if;
        end if;
        if isign = '1' then
          result := - result;
        end if;
    end case classcase;
    return result;
  end function to_integer;

  -- to_unsigned (float)
  function to_unsigned (
    arg                  : UNRESOLVED_float;  -- floating point input
    constant size        : NATURAL;     -- length of output
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return UNSIGNED is
    variable validfp : valid_fpstate;   -- Valid FP state
    variable frac    : UNSIGNED (size-1 downto 0);           -- Fraction
    variable sign    : STD_ULOGIC;      -- not used
  begin
    validfp := classfp (arg, check_error);
    classcase : case validfp is
      when isx | nan | quiet_nan =>
        frac := (others => 'X');
      when pos_zero | neg_inf | neg_zero | neg_normal | pos_denormal | neg_denormal =>
        frac := (others => '0');        -- return 0
      when pos_inf =>
        frac := (others => '1');
      when others =>
        float_to_unsigned (
          arg         => arg,
          frac        => frac,
          sign        => sign,
          denormalize => false,
          bias        => 0,
          round_style => round_style);
    end case classcase;
    return (frac);
  end function to_unsigned;

  -- to_signed (float)
  function to_signed (
    arg                  : UNRESOLVED_float;  -- floating point input
    constant size        : NATURAL;     -- length of output
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return SIGNED is
    variable sign    : STD_ULOGIC;      -- true if negative
    variable validfp : valid_fpstate;   -- Valid FP state
    variable frac    : UNSIGNED (size-1 downto 0);           -- Fraction
    variable result  : SIGNED (size-1 downto 0);
  begin
    validfp := classfp (arg, check_error);
    classcase : case validfp is
      when isx | nan | quiet_nan =>
        result := (others => 'X');
      when pos_zero | neg_zero | pos_denormal | neg_denormal =>
        result := (others => '0');      -- return 0
      when pos_inf =>
        result               := (others => '1');
        result (result'high) := '0';
      when neg_inf =>
        result               := (others => '0');
        result (result'high) := '1';
      when others =>
        float_to_unsigned (
          arg         => arg,
          sign        => sign,
          frac        => frac,
          denormalize => false,
          bias        => 0,
          round_style => round_style);
        result (size-1)          := '0';
        result (size-2 downto 0) := SIGNED(frac (size-2 downto 0));
        if sign = '1' then
          -- Because the most negative signed number is 1 less than the most
          -- positive signed number, we need this code.
          if frac(frac'high) = '1' then       -- return most negative number
            result               := (others => '0');
            result (result'high) := '1';
          else
            result := -result;
          end if;
        else
          if frac(frac'high) = '1' then       -- return most positive number
            result               := (others => '1');
            result (result'high) := '0';
          end if;
        end if;
    end case classcase;
    return result;
  end function to_signed;

  -- purpose: Converts a float to ufixed
  function to_ufixed (
    arg                     : UNRESOLVED_float;            -- fp input
    constant left_index     : INTEGER;  -- integer part
    constant right_index    : INTEGER;  -- fraction part
    constant overflow_style : fixed_overflow_style_type := fixed_overflow_style;  -- saturate
    constant round_style    : fixed_round_style_type    := fixed_round_style;  -- rounding
    constant check_error    : BOOLEAN                   := float_check_error;  -- check for errors
    constant denormalize    : BOOLEAN                   := float_denormalize)
    return UNRESOLVED_ufixed is
    constant fraction_width : INTEGER                    := -mine(arg'low, arg'low);  -- length of FP output fraction
    constant exponent_width : INTEGER                    := arg'high;  -- length of FP output exponent
    constant size           : INTEGER                    := left_index - right_index + 4;  -- unsigned size
    variable expon_base     : INTEGER;  -- exponent offset
    variable validfp        : valid_fpstate;               -- Valid FP state
    variable exp            : INTEGER;  -- Exponent
    variable expon          : UNSIGNED (exponent_width-1 downto 0);  -- Vectorized exponent
    -- Base to divide fraction by
    variable frac           : UNSIGNED (size-1 downto 0) := (others => '0');  -- Fraction
    variable frac_shift     : UNSIGNED (size-1 downto 0);  -- Fraction shifted
    variable shift          : INTEGER;
    variable result_big     : UNRESOLVED_ufixed (left_index downto right_index-3);
    variable result         : UNRESOLVED_ufixed (left_index downto right_index);  -- result
  begin  -- function to_ufixed
    validfp := classfp (arg, check_error);
    classcase : case validfp is
      when isx | nan | quiet_nan =>
        frac := (others => 'X');
      when pos_zero | neg_inf | neg_zero | neg_normal | neg_denormal =>
        frac := (others => '0');        -- return 0
      when pos_inf =>
        frac := (others => '1');        -- always saturate
      when others =>
        expon_base := 2**(exponent_width-1) -1;            -- exponent offset
        -- Figure out the fraction
        if (validfp = pos_denormal) and denormalize then
          exp              := -expon_base +1;
          frac (frac'high) := '0';      -- Remove the "1.0".
        else
          -- exponent /= '0', normal floating point
          expon                   := UNSIGNED(arg (exponent_width-1 downto 0));
          expon(exponent_width-1) := not expon(exponent_width-1);
          exp                     := to_integer (SIGNED(expon)) +1;
          frac (frac'high)        := '1';   -- Add the "1.0".
        end if;
        shift := (frac'high - 3 + right_index) - exp;
        if fraction_width > frac'high then  -- Can only use size-2 bits
          frac (frac'high-1 downto 0) := UNSIGNED (to_slv (arg(-1 downto
                                                               -frac'high)));
        else                            -- can use all bits
          frac (frac'high-1 downto frac'high-fraction_width) :=
            UNSIGNED (to_slv (arg(-1 downto -fraction_width)));
        end if;
        frac_shift := frac srl shift;
        if shift < 0 then               -- Overflow
          frac := (others => '1');
        else
          frac := frac_shift;
        end if;
    end case classcase;
    result_big := to_ufixed (
      arg         => STD_ULOGIC_VECTOR(frac),
      left_index  => left_index,
      right_index => (right_index-3));
    result := resize (arg            => result_big,
                      left_index     => left_index,
                      right_index    => right_index,
                      round_style    => round_style,
                      overflow_style => overflow_style);
    return result;
  end function to_ufixed;

  -- purpose: Converts a float to sfixed
  function to_sfixed (
    arg                     : UNRESOLVED_float;  -- fp input
    constant left_index     : INTEGER;  -- integer part
    constant right_index    : INTEGER;  -- fraction part
    constant overflow_style : fixed_overflow_style_type := fixed_overflow_style;  -- saturate
    constant round_style    : fixed_round_style_type    := fixed_round_style;  -- rounding
    constant check_error    : BOOLEAN                   := float_check_error;  -- check for errors
    constant denormalize    : BOOLEAN                   := float_denormalize)
    return UNRESOLVED_sfixed is
    constant fraction_width : INTEGER                    := -mine(arg'low, arg'low);  -- length of FP output fraction
    constant exponent_width : INTEGER                    := arg'high;  -- length of FP output exponent
    constant size           : INTEGER                    := left_index - right_index + 4;  -- unsigned size
    variable expon_base     : INTEGER;  -- exponent offset
    variable validfp        : valid_fpstate;     -- Valid FP state
    variable exp            : INTEGER;  -- Exponent
    variable sign           : BOOLEAN;  -- true if negative
    variable expon          : UNSIGNED (exponent_width-1 downto 0);  -- Vectorized exponent
    -- Base to divide fraction by
    variable frac           : UNSIGNED (size-2 downto 0) := (others => '0');  -- Fraction
    variable frac_shift     : UNSIGNED (size-2 downto 0);  -- Fraction shifted
    variable shift          : INTEGER;
    variable rsigned        : SIGNED (size-1 downto 0);  -- signed version of result
    variable result_big     : UNRESOLVED_sfixed (left_index downto right_index-3);
    variable result         : UNRESOLVED_sfixed (left_index downto right_index)
      := (others => '0');               -- result
  begin  -- function to_sfixed
    validfp := classfp (arg, check_error);
    classcase : case validfp is
      when isx | nan | quiet_nan =>
        result := (others => 'X');
      when pos_zero | neg_zero =>
        result := (others => '0');      -- return 0
      when neg_inf =>
        result (left_index) := '1';     -- return smallest negative number
      when pos_inf =>
        result              := (others => '1');  -- return largest number
        result (left_index) := '0';
      when others =>
        expon_base := 2**(exponent_width-1) -1;  -- exponent offset
        if arg(exponent_width) = '0' then
          sign := false;
        else
          sign := true;
        end if;
        -- Figure out the fraction
        if (validfp = pos_denormal or validfp = neg_denormal)
          and denormalize then
          exp              := -expon_base +1;
          frac (frac'high) := '0';      -- Add the "1.0".
        else
          -- exponent /= '0', normal floating point
          expon                   := UNSIGNED(arg (exponent_width-1 downto 0));
          expon(exponent_width-1) := not expon(exponent_width-1);
          exp                     := to_integer (SIGNED(expon)) +1;
          frac (frac'high)        := '1';        -- Add the "1.0".
        end if;
        shift := (frac'high - 3 + right_index) - exp;
        if fraction_width > frac'high then       -- Can only use size-2 bits
          frac (frac'high-1 downto 0) := UNSIGNED (to_slv (arg(-1 downto
                                                               -frac'high)));
        else                            -- can use all bits
          frac (frac'high-1 downto frac'high-fraction_width) :=
            UNSIGNED (to_slv (arg(-1 downto -fraction_width)));
        end if;
        frac_shift := frac srl shift;
        if shift < 0 then               -- Overflow
          frac := (others => '1');
        else
          frac := frac_shift;
        end if;
        if not sign then
          rsigned := SIGNED("0" & frac);
        else
          rsigned := -(SIGNED("0" & frac));
        end if;
        result_big := to_sfixed (
          arg         => STD_LOGIC_VECTOR(rsigned),
          left_index  => left_index,
          right_index => (right_index-3));
        result := resize (arg            => result_big,
                          left_index     => left_index,
                          right_index    => right_index,
                          round_style    => round_style,
                          overflow_style => overflow_style);
    end case classcase;
    return result;
  end function to_sfixed;

  -- size_res versions
  -- float to unsigned
  function to_unsigned (
    arg                  : UNRESOLVED_float;  -- floating point input
    size_res             : UNSIGNED;
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return UNSIGNED is
    variable result : UNSIGNED (size_res'range);
  begin
    if (SIZE_RES'length = 0) then
      return result;
    else
      result := to_unsigned (
        arg         => arg,
        size        => size_res'length,
        round_style => round_style,
        check_error => check_error);
      return result;
    end if;
  end function to_unsigned;

  -- float to signed
  function to_signed (
    arg                  : UNRESOLVED_float;  -- floating point input
    size_res             : SIGNED;
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error)  -- check for errors
    return SIGNED is
    variable result : SIGNED (size_res'range);
  begin
    if (SIZE_RES'length = 0) then
      return result;
    else
      result := to_signed (
        arg         => arg,
        size        => size_res'length,
        round_style => round_style,
        check_error => check_error);
      return result;
    end if;
  end function to_signed;

  -- purpose: Converts a float to unsigned fixed point
  function to_ufixed (
    arg                     : UNRESOLVED_float;  -- fp input
    size_res                : UNRESOLVED_ufixed;
    constant overflow_style : fixed_overflow_style_type := fixed_overflow_style;  -- saturate
    constant round_style    : fixed_round_style_type    := fixed_round_style;  -- rounding
    constant check_error    : BOOLEAN                   := float_check_error;  -- check for errors
    constant denormalize    : BOOLEAN                   := float_denormalize)
    return UNRESOLVED_ufixed is
    variable result : UNRESOLVED_ufixed (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_ufixed (
        arg            => arg,
        left_index     => size_res'high,
        right_index    => size_res'low,
        overflow_style => overflow_style,
        round_style    => round_style,
        check_error    => check_error,
        denormalize    => denormalize);
      return result;
    end if;
  end function to_ufixed;

  -- float to signed fixed point
  function to_sfixed (
    arg                     : UNRESOLVED_float;  -- fp input
    size_res                : UNRESOLVED_sfixed;
    constant overflow_style : fixed_overflow_style_type := fixed_overflow_style;  -- saturate
    constant round_style    : fixed_round_style_type    := fixed_round_style;  -- rounding
    constant check_error    : BOOLEAN                   := float_check_error;  -- check for errors
    constant denormalize    : BOOLEAN                   := float_denormalize)
    return UNRESOLVED_sfixed is
    variable result : UNRESOLVED_sfixed (size_res'left downto size_res'right);
  begin
    if (result'length < 1) then
      return result;
    else
      result := to_sfixed (
        arg            => arg,
        left_index     => size_res'high,
        right_index    => size_res'low,
        overflow_style => overflow_style,
        round_style    => round_style,
        check_error    => check_error,
        denormalize    => denormalize);
      return result;
    end if;
  end function to_sfixed;

  -- to_real (float)
  -- typically not Synthesizable unless the input is a constant.
  function to_real (
    arg                  : UNRESOLVED_float;        -- floating point input
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return REAL is
    constant fraction_width : INTEGER := -mine(arg'low, arg'low);  -- length of FP output fraction
    constant exponent_width : INTEGER := arg'high;  -- length of FP output exponent
    variable sign           : REAL;     -- Sign, + or - 1
    variable exp            : INTEGER;  -- Exponent
    variable expon_base     : INTEGER;  -- exponent offset
    variable frac           : REAL    := 0.0;       -- Fraction
    variable validfp        : valid_fpstate;        -- Valid FP state
    variable expon          : UNSIGNED (exponent_width - 1 downto 0)
      := (others => '1');               -- Vectorized exponent
  begin
    validfp := classfp (arg, check_error);
    classcase : case validfp is
      when isx | pos_zero | neg_zero | nan | quiet_nan =>
        return 0.0;
      when neg_inf =>
        return REAL'low;                -- Negative infinity.
      when pos_inf =>
        return REAL'high;               -- Positive infinity
      when others =>
        expon_base := 2**(exponent_width-1) -1;
        if to_X01(arg(exponent_width)) = '0' then
          sign := 1.0;
        else
          sign := -1.0;
        end if;
        -- Figure out the fraction
        for i in 0 to fraction_width-1 loop
          if to_X01(arg (-1 - i)) = '1' then
            frac := frac + (2.0 **(-1 - i));
          end if;
        end loop;  -- i
        if validfp = pos_normal or validfp = neg_normal or not denormalize then
          -- exponent /= '0', normal floating point
          expon                   := UNSIGNED(arg (exponent_width-1 downto 0));
          expon(exponent_width-1) := not expon(exponent_width-1);
          exp                     := to_integer (SIGNED(expon)) +1;
          sign                    := sign * (2.0 ** exp) * (1.0 + frac);
        else  -- exponent = '0', IEEE extended floating point
          exp  := 1 - expon_base;
          sign := sign * (2.0 ** exp) * frac;
        end if;
        return sign;
    end case classcase;
  end function to_real;

  -- For Verilog compatability
  function realtobits (arg : REAL) return STD_ULOGIC_VECTOR is
    variable result : float64;          -- 64 bit floating point
  begin
    result := to_float (arg => arg,
                        exponent_width => float64'high,
                        fraction_width => -float64'low);
    return to_sulv (result);
  end function realtobits;

  function bitstoreal (arg : STD_ULOGIC_VECTOR) return REAL is
    variable arg64 : float64;           -- arg converted to float
  begin
    arg64 := to_float (arg => arg,
                       exponent_width => float64'high,
                       fraction_width => -float64'low);
    return to_real (arg64);
  end function bitstoreal;

  -- purpose: Removes meta-logical values from FP string
  function to_01 (
    arg  : UNRESOLVED_float;            -- floating point input
    XMAP : STD_LOGIC := '0')
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (arg'range);
  begin  -- function to_01
    if (arg'length < 1) then
      assert NO_WARNING
        report float_pkg'instance_name
        & "TO_01: null detected, returning NULL"
        severity warning;
      return NAFP;
    end if;
    result := UNRESOLVED_float (STD_LOGIC_VECTOR(to_01(UNSIGNED(to_slv(arg)), XMAP)));
    return result;
  end function to_01;

  function Is_X
    (arg : UNRESOLVED_float)
    return BOOLEAN is
  begin
    return Is_X (to_slv(arg));
  end function Is_X;

  function to_X01 (arg : UNRESOLVED_float) return UNRESOLVED_float is
    variable result : UNRESOLVED_float (arg'range);
  begin
    if (arg'length < 1) then
      assert NO_WARNING
        report float_pkg'instance_name
        & "TO_X01: null detected, returning NULL"
        severity warning;
      return NAFP;
    else
      result := UNRESOLVED_float (to_X01(to_slv(arg)));
      return result;
    end if;
  end function to_X01;

  function to_X01Z (arg : UNRESOLVED_float) return UNRESOLVED_float is
    variable result : UNRESOLVED_float (arg'range);
  begin
    if (arg'length < 1) then
      assert NO_WARNING
        report float_pkg'instance_name
        & "TO_X01Z: null detected, returning NULL"
        severity warning;
      return NAFP;
    else
      result := UNRESOLVED_float (to_X01Z(to_slv(arg)));
      return result;
    end if;
  end function to_X01Z;

  function to_UX01 (arg : UNRESOLVED_float) return UNRESOLVED_float is
    variable result : UNRESOLVED_float (arg'range);
  begin
    if (arg'length < 1) then
      assert NO_WARNING
        report float_pkg'instance_name
        & "TO_UX01: null detected, returning NULL"
        severity warning;
      return NAFP;
    else
      result := UNRESOLVED_float (to_UX01(to_slv(arg)));
      return result;
    end if;
  end function to_UX01;

  -- These allows the base math functions to use the default values
  -- of their parameters.  Thus they do full IEEE floating point.
  function "+" (l, r : UNRESOLVED_float) return UNRESOLVED_float is
  begin
    return add (l, r);
  end function "+";

  function "-" (l, r : UNRESOLVED_float) return UNRESOLVED_float is
  begin
    return subtract (l, r);
  end function "-";

  function "*" (l, r : UNRESOLVED_float) return UNRESOLVED_float is
  begin
    return multiply (l, r);
  end function "*";

  function "/" (l, r : UNRESOLVED_float) return UNRESOLVED_float is
  begin
    return divide (l, r);
  end function "/";

  function "rem" (l, r : UNRESOLVED_float) return UNRESOLVED_float is
  begin
    return remainder (l, r);
  end function "rem";

  function "mod" (l, r : UNRESOLVED_float) return UNRESOLVED_float is
  begin
    return modulo (l, r);
  end function "mod";

  -- overloaded versions
  function "+" (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return add (l, r_float);
  end function "+";

  function "+" (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return add (l_float, r);
  end function "+";

  function "+" (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return add (l, r_float);
  end function "+";

  function "+" (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return add (l_float, r);
  end function "+";

  function "-" (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return subtract (l, r_float);
  end function "-";

  function "-" (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return subtract (l_float, r);
  end function "-";

  function "-" (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return subtract (l, r_float);
  end function "-";

  function "-" (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return subtract (l_float, r);
  end function "-";

  function "*" (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return multiply (l, r_float);
  end function "*";

  function "*" (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return multiply (l_float, r);
  end function "*";

  function "*" (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return multiply (l, r_float);
  end function "*";

  function "*" (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return multiply (l_float, r);
  end function "*";

  function "/" (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return divide (l, r_float);
  end function "/";

  function "/" (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return divide (l_float, r);
  end function "/";

  function "/" (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return divide (l, r_float);
  end function "/";

  function "/" (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return divide (l_float, r);
  end function "/";

  function "rem" (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return remainder (l, r_float);
  end function "rem";

  function "rem" (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return remainder (l_float, r);
  end function "rem";

  function "rem" (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return remainder (l, r_float);
  end function "rem";

  function "rem" (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return remainder (l_float, r);
  end function "rem";

  function "mod" (l : UNRESOLVED_float; r : REAL) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return modulo (l, r_float);
  end function "mod";

  function "mod" (l : REAL; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return modulo (l_float, r);
  end function "mod";

  function "mod" (l : UNRESOLVED_float; r : INTEGER) return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return modulo (l, r_float);
  end function "mod";

  function "mod" (l : INTEGER; r : UNRESOLVED_float) return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return modulo (l_float, r);
  end function "mod";

  function "=" (l : UNRESOLVED_float; r : REAL) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return eq (l, r_float);
  end function "=";

  function "/=" (l : UNRESOLVED_float; r : REAL) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return ne (l, r_float);
  end function "/=";

  function ">=" (l : UNRESOLVED_float; r : REAL) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return ge (l, r_float);
  end function ">=";

  function "<=" (l : UNRESOLVED_float; r : REAL) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return le (l, r_float);
  end function "<=";

  function ">" (l : UNRESOLVED_float; r : REAL) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return gt (l, r_float);
  end function ">";

  function "<" (l : UNRESOLVED_float; r : REAL) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return lt (l, r_float);
  end function "<";

  function "=" (l : REAL; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return eq (l_float, r);
  end function "=";

  function "/=" (l : REAL; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return ne (l_float, r);
  end function "/=";

  function ">=" (l : REAL; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return ge (l_float, r);
  end function ">=";

  function "<=" (l : REAL; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return le (l_float, r);
  end function "<=";

  function ">" (l : REAL; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return gt (l_float, r);
  end function ">";

  function "<" (l : REAL; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return lt (l_float, r);
  end function "<";

  function "=" (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return eq (l, r_float);
  end function "=";

  function "/=" (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return ne (l, r_float);
  end function "/=";

  function ">=" (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return ge (l, r_float);
  end function ">=";

  function "<=" (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return le (l, r_float);
  end function "<=";

  function ">" (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return gt (l, r_float);
  end function ">";

  function "<" (l : UNRESOLVED_float; r : INTEGER) return BOOLEAN is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return lt (l, r_float);
  end function "<";

  function "=" (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return eq (l_float, r);
  end function "=";

  function "/=" (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return ne (l_float, r);
  end function "/=";

  function ">=" (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return ge (l_float, r);
  end function ">=";

  function "<=" (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return le (l_float, r);
  end function "<=";

  function ">" (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return gt (l_float, r);
  end function ">";

  function "<" (l : INTEGER; r : UNRESOLVED_float) return BOOLEAN is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float(l, r'high, -r'low);
    return lt (l_float, r);
  end function "<";

  -- ?= overloads
  function \?=\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?=\ (l, r_float);
  end function \?=\;

  function \?/=\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?/=\ (l, r_float);
  end function \?/=\;

  function \?>\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?>\ (l, r_float);
  end function \?>\;

  function \?>=\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?>=\ (l, r_float);
  end function \?>=\;

  function \?<\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?<\ (l, r_float);
  end function \?<\;

  function \?<=\ (l : UNRESOLVED_float; r : REAL) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?<=\ (l, r_float);
  end function \?<=\;

  -- real and float
  function \?=\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?=\ (l_float, r);
  end function \?=\;

  function \?/=\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?/=\ (l_float, r);
  end function \?/=\;

  function \?>\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?>\ (l_float, r);
  end function \?>\;

  function \?>=\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?>=\ (l_float, r);
  end function \?>=\;

  function \?<\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?<\ (l_float, r);
  end function \?<\;

  function \?<=\ (l : REAL; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?<=\ (l_float, r);
  end function \?<=\;

  -- ?= overloads
  function \?=\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?=\ (l, r_float);
  end function \?=\;

  function \?/=\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?/=\ (l, r_float);
  end function \?/=\;

  function \?>\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?>\ (l, r_float);
  end function \?>\;

  function \?>=\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?>=\ (l, r_float);
  end function \?>=\;

  function \?<\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?<\ (l, r_float);
  end function \?<\;

  function \?<=\ (l : UNRESOLVED_float; r : INTEGER) return STD_ULOGIC is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return \?<=\ (l, r_float);
  end function \?<=\;

  -- integer and float
  function \?=\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?=\ (l_float, r);
  end function \?=\;

  function \?/=\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?/=\ (l_float, r);
  end function \?/=\;

  function \?>\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?>\ (l_float, r);
  end function \?>\;

  function \?>=\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?>=\ (l_float, r);
  end function \?>=\;

  function \?<\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?<\ (l_float, r);
  end function \?<\;

  function \?<=\ (l : INTEGER; r : UNRESOLVED_float) return STD_ULOGIC is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return \?<=\ (l_float, r);
  end function \?<=\;

  -- minimum and maximum overloads
  function minimum (l : UNRESOLVED_float; r : REAL)
    return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return minimum (l, r_float);
  end function minimum;

  function maximum (l : UNRESOLVED_float; r : REAL)
    return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return maximum (l, r_float);
  end function maximum;

  function minimum (l : REAL; r : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return minimum (l_float, r);
  end function minimum;

  function maximum (l : REAL; r : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return maximum (l_float, r);
  end function maximum;

  function minimum (l : UNRESOLVED_float; r : INTEGER)
    return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return minimum (l, r_float);
  end function minimum;

  function maximum (l : UNRESOLVED_float; r : INTEGER)
    return UNRESOLVED_float is
    variable r_float : UNRESOLVED_float (l'range);
  begin
    r_float := to_float (r, l'high, -l'low);
    return maximum (l, r_float);
  end function maximum;

  function minimum (l : INTEGER; r : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return minimum (l_float, r);
  end function minimum;

  function maximum (l : INTEGER; r : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable l_float : UNRESOLVED_float (r'range);
  begin
    l_float := to_float (l, r'high, -r'low);
    return maximum (l_float, r);
  end function maximum;

  ----------------------------------------------------------------------------
  -- logical functions
  ----------------------------------------------------------------------------
  function "not" (L : UNRESOLVED_float) return UNRESOLVED_float is
    variable RESULT : STD_ULOGIC_VECTOR(L'length-1 downto 0);  -- force downto
  begin
    RESULT := not to_sulv(L);
    return to_float (RESULT, L'high, -L'low);
  end function "not";

  function "and" (L, R : UNRESOLVED_float) return UNRESOLVED_float is
    variable RESULT : STD_ULOGIC_VECTOR(L'length-1 downto 0);  -- force downto
   begin
     if (L'high = R'high and L'low = R'low) then
      RESULT := to_sulv(L) and to_sulv(R);
    else
      assert NO_WARNING
        report float_pkg'instance_name
        & """and"": Range error L'RANGE /= R'RANGE"
        severity warning;
      RESULT := (others => 'X');
    end if;
    return to_float (RESULT, L'high, -L'low);
  end function "and";

  function "or" (L, R : UNRESOLVED_float) return UNRESOLVED_float is
    variable RESULT : STD_ULOGIC_VECTOR(L'length-1 downto 0);  -- force downto
  begin
     if (L'high = R'high and L'low = R'low) then
      RESULT := to_sulv(L) or to_sulv(R);
    else
      assert NO_WARNING
        report float_pkg'instance_name
        & """or"": Range error L'RANGE /= R'RANGE"
        severity warning;
      RESULT := (others => 'X');
    end if;
    return to_float (RESULT, L'high, -L'low);
  end function "or";

  function "nand" (L, R : UNRESOLVED_float) return UNRESOLVED_float is
    variable RESULT : STD_ULOGIC_VECTOR(L'length-1 downto 0);  -- force downto
  begin
     if (L'high = R'high and L'low = R'low) then
      RESULT := to_sulv(L) nand to_sulv(R);
    else
      assert NO_WARNING
        report float_pkg'instance_name
        & """nand"": Range error L'RANGE /= R'RANGE"
        severity warning;
      RESULT := (others => 'X');
    end if;
    return to_float (RESULT, L'high, -L'low);
  end function "nand";

  function "nor" (L, R : UNRESOLVED_float) return UNRESOLVED_float is
    variable RESULT : STD_ULOGIC_VECTOR(L'length-1 downto 0);  -- force downto
  begin
     if (L'high = R'high and L'low = R'low) then
      RESULT := to_sulv(L) nor to_sulv(R);
    else
      assert NO_WARNING
        report float_pkg'instance_name
        & """nor"": Range error L'RANGE /= R'RANGE"
        severity warning;
      RESULT := (others => 'X');
    end if;
    return to_float (RESULT, L'high, -L'low);
  end function "nor";

  function "xor" (L, R : UNRESOLVED_float) return UNRESOLVED_float is
    variable RESULT : STD_ULOGIC_VECTOR(L'length-1 downto 0);  -- force downto
  begin
     if (L'high = R'high and L'low = R'low) then
      RESULT := to_sulv(L) xor to_sulv(R);
    else
      assert NO_WARNING
        report float_pkg'instance_name
        & """xor"": Range error L'RANGE /= R'RANGE"
        severity warning;
      RESULT := (others => 'X');
    end if;
    return to_float (RESULT, L'high, -L'low);
  end function "xor";

  function "xnor" (L, R : UNRESOLVED_float) return UNRESOLVED_float is
    variable RESULT : STD_ULOGIC_VECTOR(L'length-1 downto 0);  -- force downto
  begin
     if (L'high = R'high and L'low = R'low) then
      RESULT := to_sulv(L) xnor to_sulv(R);
    else
      assert NO_WARNING
        report float_pkg'instance_name
        & """xnor"": Range error L'RANGE /= R'RANGE"
        severity warning;
      RESULT := (others => 'X');
    end if;
    return to_float (RESULT, L'high, -L'low);
  end function "xnor";

  -- Vector and std_ulogic functions, same as functions in numeric_std
  function "and" (L : STD_ULOGIC; R : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (R'range);
  begin
    for i in result'range loop
      result(i) := L and R(i);
    end loop;
    return result;
  end function "and";

  function "and" (L : UNRESOLVED_float; R : STD_ULOGIC)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (L'range);
  begin
    for i in result'range loop
      result(i) := L(i) and R;
    end loop;
    return result;
  end function "and";

  function "or" (L : STD_ULOGIC; R : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (R'range);
  begin
    for i in result'range loop
      result(i) := L or R(i);
    end loop;
    return result;
  end function "or";

  function "or" (L : UNRESOLVED_float; R : STD_ULOGIC)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (L'range);
  begin
    for i in result'range loop
      result(i) := L(i) or R;
    end loop;
    return result;
  end function "or";

  function "nand" (L : STD_ULOGIC; R : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (R'range);
  begin
    for i in result'range loop
      result(i) := L nand R(i);
    end loop;
    return result;
  end function "nand";

  function "nand" (L : UNRESOLVED_float; R : STD_ULOGIC)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (L'range);
  begin
    for i in result'range loop
      result(i) := L(i) nand R;
    end loop;
    return result;
  end function "nand";

  function "nor" (L : STD_ULOGIC; R : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (R'range);
  begin
    for i in result'range loop
      result(i) := L nor R(i);
    end loop;
    return result;
  end function "nor";

  function "nor" (L : UNRESOLVED_float; R : STD_ULOGIC)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (L'range);
  begin
    for i in result'range loop
      result(i) := L(i) nor R;
    end loop;
    return result;
  end function "nor";

  function "xor" (L : STD_ULOGIC; R : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (R'range);
  begin
    for i in result'range loop
      result(i) := L xor R(i);
    end loop;
    return result;
  end function "xor";

  function "xor" (L : UNRESOLVED_float; R : STD_ULOGIC)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (L'range);
  begin
    for i in result'range loop
      result(i) := L(i) xor R;
    end loop;
    return result;
  end function "xor";

  function "xnor" (L : STD_ULOGIC; R : UNRESOLVED_float)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (R'range);
  begin
    for i in result'range loop
      result(i) := L xnor R(i);
    end loop;
    return result;
  end function "xnor";

  function "xnor" (L : UNRESOLVED_float; R : STD_ULOGIC)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (L'range);
  begin
    for i in result'range loop
      result(i) := L(i) xnor R;
    end loop;
    return result;
  end function "xnor";

  -- Reduction operator_reduces, same as numeric_std functions

  function and_reduce (l : UNRESOLVED_float) return STD_ULOGIC is
  begin
    return and_reduce (to_sulv(l));
  end function and_reduce;

  function nand_reduce (l : UNRESOLVED_float) return STD_ULOGIC is
  begin
    return nand_reduce (to_sulv(l));
  end function nand_reduce;

  function or_reduce (l : UNRESOLVED_float) return STD_ULOGIC is
  begin
    return or_reduce (to_sulv(l));
  end function or_reduce;

  function nor_reduce (l : UNRESOLVED_float) return STD_ULOGIC is
  begin
    return nor_reduce (to_sulv(l));
  end function nor_reduce;

  function xor_reduce (l : UNRESOLVED_float) return STD_ULOGIC is
  begin
    return xor_reduce (to_sulv(l));
  end function xor_reduce;

  function xnor_reduce (l : UNRESOLVED_float) return STD_ULOGIC is
  begin
    return xnor_reduce (to_sulv(l));
  end function xnor_reduce;

  -----------------------------------------------------------------------------
  -- Recommended Functions from the IEEE 754 Appendix
  -----------------------------------------------------------------------------
  -- returns x with the sign of y.
  function Copysign (
    x, y : UNRESOLVED_float)            -- floating point input
    return UNRESOLVED_float is
  begin
    return y(y'high) & x (x'high-1 downto x'low);
  end function Copysign;

  -- Returns y * 2**n for integral values of N without computing 2**n
  function Scalb (
    y                    : UNRESOLVED_float;      -- floating point input
    N                    : INTEGER;     -- exponent to add    
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    constant fraction_width : NATURAL := -mine(y'low, y'low);  -- length of FP output fraction
    constant exponent_width : NATURAL := y'high;  -- length of FP output exponent
    variable arg, result    : UNRESOLVED_float (exponent_width downto -fraction_width);  -- internal argument
    variable expon          : SIGNED (exponent_width-1 downto 0);  -- Vectorized exp
    variable exp            : SIGNED (exponent_width downto 0);
    variable ufract         : UNSIGNED (fraction_width downto 0);
    constant expon_base     : SIGNED (exponent_width-1 downto 0)
      := gen_expon_base(exponent_width);          -- exponent offset
    variable fptype : valid_fpstate;
  begin
    -- This can be done by simply adding N to the exponent.
    arg    := to_01 (y, 'X');
    fptype := classfp(arg, check_error);
    classcase : case fptype is
      when isx =>
        result := (others => 'X');
      when nan | quiet_nan =>
        -- Return quiet NAN, IEEE754-1985-7.1,1
        result := qnanfp (fraction_width => fraction_width,
                          exponent_width => exponent_width);
      when others =>
        break_number (
          arg         => arg,
          fptyp       => fptype,
          denormalize => denormalize,
          fract       => ufract,
          expon       => expon);
        exp := resize (expon, exp'length) + N;
        result := normalize (
          fract          => ufract,
          expon          => exp,
          sign           => to_x01 (arg (arg'high)),
          fraction_width => fraction_width,
          exponent_width => exponent_width,
          round_style    => round_style,
          denormalize    => denormalize,
          nguard         => 0);
    end case classcase;
    return result;
  end function Scalb;

  -- Returns y * 2**n for integral values of N without computing 2**n
  function Scalb (
    y                    : UNRESOLVED_float;  -- floating point input
    N                    : SIGNED;      -- exponent to add    
    constant round_style : round_type := float_round_style;  -- rounding option
    constant check_error : BOOLEAN    := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN    := float_denormalize)  -- Use IEEE extended FP
    return UNRESOLVED_float is
    variable n_int : INTEGER;
  begin
    n_int := to_integer(N);
    return Scalb (y           => y,
                  N           => n_int,
                  round_style => round_style,
                  check_error => check_error,
                  denormalize => denormalize);
  end function Scalb;

  -- returns the unbiased exponent of x
  function Logb (
    x : UNRESOLVED_float)               -- floating point input
    return INTEGER is
    constant fraction_width : NATURAL := -mine (x'low, x'low);  -- length of FP output fraction
    constant exponent_width : NATURAL := x'high;  -- length of FP output exponent
    variable result         : INTEGER;  -- result
    variable arg            : UNRESOLVED_float (exponent_width downto -fraction_width);  -- internal argument
    variable expon          : SIGNED (exponent_width - 1 downto 0);
    variable fract          : UNSIGNED (fraction_width downto 0);
    constant expon_base     : INTEGER := 2**(exponent_width-1) -1;  -- exponent
                                        -- offset +1
    variable fptype         : valid_fpstate;
  begin
    -- Just return the exponent.
    arg    := to_01 (x, 'X');
    fptype := classfp(arg);
    classcase : case fptype is
      when isx | nan | quiet_nan =>
        -- Return quiet NAN, IEEE754-1985-7.1,1
        result := 0;
      when pos_denormal | neg_denormal =>
        fract (fraction_width) := '0';
        fract (fraction_width-1 downto 0) :=
          UNSIGNED (to_slv(arg(-1 downto -fraction_width)));
        result := find_leftmost (fract, '1')      -- Find the first "1"
                  - fraction_width;     -- subtract the length we want
        result := -expon_base + 1 + result;
      when others =>
        expon                   := SIGNED(arg (exponent_width - 1 downto 0));
        expon(exponent_width-1) := not expon(exponent_width-1);
        expon                   := expon + 1;
        result                  := to_integer (expon);
    end case classcase;
    return result;
  end function Logb;

  -- returns the unbiased exponent of x
  function Logb (
    x : UNRESOLVED_float)               -- floating point input
    return SIGNED is
    constant exponent_width : NATURAL := x'high;  -- length of FP output exponent
    variable result         : SIGNED (exponent_width - 1 downto 0);  -- result
  begin
    -- Just return the exponent.
    result := to_signed (Logb (x), exponent_width);
    return result;
  end function Logb;

  -- returns the next representable neighbor of x in the direction toward y
  function Nextafter (
    x, y                 : UNRESOLVED_float;      -- floating point input
    constant check_error : BOOLEAN := float_check_error;  -- check for errors
    constant denormalize : BOOLEAN := float_denormalize)
    return UNRESOLVED_float is
    constant fraction_width : NATURAL := -mine(x'low, x'low);  -- length of FP output fraction
    constant exponent_width : NATURAL := x'high;  -- length of FP output exponent
    function "=" (
      l, r : UNRESOLVED_float)          -- inputs
      return BOOLEAN is
    begin  -- function "="
      return eq (l           => l,
                 r           => r,
                 check_error => false);
    end function "=";
    function ">" (
      l, r : UNRESOLVED_float)          -- inputs
      return BOOLEAN is
    begin  -- function ">"
      return gt (l           => l,
                 r           => r,
                 check_error => false);
    end function ">";
    variable fract              : UNSIGNED (fraction_width-1 downto 0);
    variable expon              : UNSIGNED (exponent_width-1 downto 0);
    variable sign               : STD_ULOGIC;
    variable result             : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable validfpx, validfpy : valid_fpstate;  -- Valid FP state
  begin  -- fp_Nextafter
    -- If Y > X, add one to the fraction, otherwise subtract.
    validfpx := classfp (x, check_error);
    validfpy := classfp (y, check_error);
    if validfpx = isx or validfpy = isx then
      result := (others => 'X');
      return result;
    elsif (validfpx = nan or validfpy = nan) then
      return nanfp (fraction_width => fraction_width,
                    exponent_width => exponent_width);
    elsif (validfpx = quiet_nan or validfpy = quiet_nan) then
      return qnanfp (fraction_width => fraction_width,
                     exponent_width => exponent_width);
    elsif x = y then                    -- Return X
      return x;
    else
      fract := UNSIGNED (to_slv (x (-1 downto -fraction_width)));  -- Fraction
      expon := UNSIGNED (x (exponent_width - 1 downto 0));     -- exponent
      sign  := x(exponent_width);       -- sign bit
      if (y > x) then
        -- Increase the number given
        if validfpx = neg_inf then
          -- return most negative number
          expon     := (others => '1');
          expon (0) := '0';
          fract     := (others => '1');
        elsif validfpx = pos_zero or validfpx = neg_zero then
          -- return smallest denormal number
          sign     := '0';
          expon    := (others => '0');
          fract    := (others => '0');
          fract(0) := '1';
        elsif validfpx = pos_normal then
          if and_reduce (fract) = '1' then        -- fraction is all "1".
            if and_reduce (expon (exponent_width-1 downto 1)) = '1'
              and expon (0) = '0' then
                                        -- Exponent is one away from infinity.
              assert NO_WARNING
                report float_pkg'instance_name
                & "FP_NEXTAFTER: NextAfter overflow"
                severity warning;
              return pos_inffp (fraction_width => fraction_width,
                                exponent_width => exponent_width);
            else
              expon := expon + 1;
              fract := (others => '0');
            end if;
          else
            fract := fract + 1;
          end if;
        elsif validfpx = pos_denormal then
          if and_reduce (fract) = '1' then        -- fraction is all "1".
            -- return smallest possible normal number
            expon    := (others => '0');
            expon(0) := '1';
            fract    := (others => '0');
          else
            fract := fract + 1;
          end if;
        elsif validfpx = neg_normal then
          if or_reduce (fract) = '0' then         -- fraction is all "0".
            if or_reduce (expon (exponent_width-1 downto 1)) = '0' and
              expon (0) = '1' then      -- Smallest exponent
              -- return the largest negative denormal number
              expon := (others => '0');
              fract := (others => '1');
            else
              expon := expon - 1;
              fract := (others => '1');
            end if;
          else
            fract := fract - 1;
          end if;
        elsif validfpx = neg_denormal then
          if or_reduce (fract(fract'high downto 1)) = '0'
            and fract (0) = '1' then    -- Smallest possible fraction
            return zerofp (fraction_width => fraction_width,
                           exponent_width => exponent_width);
          else
            fract := fract - 1;
          end if;
        end if;
      else
        -- Decrease the number
        if validfpx = pos_inf then
          -- return most positive number
          expon     := (others => '1');
          expon (0) := '0';
          fract     := (others => '1');
        elsif validfpx = pos_zero
          or classfp (x) = neg_zero then
          -- return smallest negative denormal number
          sign     := '1';
          expon    := (others => '0');
          fract    := (others => '0');
          fract(0) := '1';
        elsif validfpx = neg_normal then
          if and_reduce (fract) = '1' then        -- fraction is all "1".
            if and_reduce (expon (exponent_width-1 downto 1)) = '1'
              and expon (0) = '0' then
                                        -- Exponent is one away from infinity.
              assert NO_WARNING
                report float_pkg'instance_name
                & "FP_NEXTAFTER: NextAfter overflow"
                severity warning;
              return neg_inffp (fraction_width => fraction_width,
                                exponent_width => exponent_width);
            else
              expon := expon + 1;       -- Fraction overflow
              fract := (others => '0');
            end if;
          else
            fract := fract + 1;
          end if;
        elsif validfpx = neg_denormal then
          if and_reduce (fract) = '1' then        -- fraction is all "1".
            -- return smallest possible normal number
            expon    := (others => '0');
            expon(0) := '1';
            fract    := (others => '0');
          else
            fract := fract + 1;
          end if;
        elsif validfpx = pos_normal then
          if or_reduce (fract) = '0' then         -- fraction is all "0".
            if or_reduce (expon (exponent_width-1 downto 1)) = '0' and
              expon (0) = '1' then      -- Smallest exponent
              -- return the largest positive denormal number
              expon := (others => '0');
              fract := (others => '1');
            else
              expon := expon - 1;
              fract := (others => '1');
            end if;
          else
            fract := fract - 1;
          end if;
        elsif validfpx = pos_denormal then
          if or_reduce (fract(fract'high downto 1)) = '0'
            and fract (0) = '1' then    -- Smallest possible fraction
            return zerofp (fraction_width => fraction_width,
                           exponent_width => exponent_width);
          else
            fract := fract - 1;
          end if;
        end if;
      end if;
      result (-1 downto -fraction_width)  := UNRESOLVED_float(fract);
      result (exponent_width -1 downto 0) := UNRESOLVED_float(expon);
      result (exponent_width)             := sign;
      return result;
    end if;
  end function Nextafter;

  -- Returns True if X is unordered with Y.
  function Unordered (
    x, y : UNRESOLVED_float)            -- floating point input
    return BOOLEAN is
    variable lfptype, rfptype : valid_fpstate;
  begin
    lfptype := classfp (x);
    rfptype := classfp (y);
    if (lfptype = nan or lfptype = quiet_nan or
        rfptype = nan or rfptype = quiet_nan or
        lfptype = isx or rfptype = isx) then
      return true;
    else
      return false;
    end if;
  end function Unordered;

  function Finite (
    x : UNRESOLVED_float)
    return BOOLEAN is
    variable fp_state : valid_fpstate;  -- fp state
  begin
    fp_state := Classfp (x);
    if (fp_state = pos_inf) or (fp_state = neg_inf) then
      return true;
    else
      return false;
    end if;
  end function Finite;

  function Isnan (
    x : UNRESOLVED_float)
    return BOOLEAN is
    variable fp_state : valid_fpstate;  -- fp state
  begin
    fp_state := Classfp (x);
    if (fp_state = nan) or (fp_state = quiet_nan) then
      return true;
    else
      return false;
    end if;
  end function Isnan;

  -- Function to return constants.
  function zerofp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float is
    constant result : UNRESOLVED_float (exponent_width downto -fraction_width) :=
      (others => '0');                                          -- zero
  begin
    return result;
  end function zerofp;

  function nanfp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width) :=
      (others => '0');                  -- zero
  begin
    result (exponent_width-1 downto 0) := (others => '1');
    -- Exponent all "1"
    result (-1) := '1';  -- MSB of Fraction "1"
    -- Note: From W. Khan "IEEE Standard 754 for Binary Floating Point"
    -- The difference between a signaling NAN and a quiet NAN is that
    -- the MSB of the Fraction is a "1" in a Signaling NAN, and is a
    -- "0" in a quiet NAN.
    return result;
  end function nanfp;

  function qnanfp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width) :=
      (others => '0');                  -- zero
  begin
    result (exponent_width-1 downto 0) := (others => '1');
    -- Exponent all "1"
    result (-fraction_width)           := '1';  -- LSB of Fraction "1"
    -- (Could have been any bit)
    return result;
  end function qnanfp;

  function pos_inffp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width) :=
      (others => '0');                  -- zero
  begin
    result (exponent_width-1 downto 0) := (others => '1');  -- Exponent all "1"
    return result;
  end function pos_inffp;

  function neg_inffp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width) :=
      (others => '0');                  -- zero
  begin
    result (exponent_width downto 0) := (others => '1');  -- top bits all "1"
    return result;
  end function neg_inffp;

  function neg_zerofp (
    constant exponent_width : NATURAL := float_exponent_width;  -- exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- fraction
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width) :=
      (others => '0');                                          -- zero
  begin
    result (exponent_width) := '1';
    return result;
  end function neg_zerofp;

  -- size_res versions
  function zerofp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float is
  begin
    return zerofp (
      exponent_width => size_res'high,
      fraction_width => -size_res'low);
  end function zerofp;

  function nanfp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float is
  begin
    return nanfp (
      exponent_width => size_res'high,
      fraction_width => -size_res'low);
  end function nanfp;

  function qnanfp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float is
  begin
    return qnanfp (
      exponent_width => size_res'high,
      fraction_width => -size_res'low);
  end function qnanfp;

  function pos_inffp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float is
  begin
    return pos_inffp (
      exponent_width => size_res'high,
      fraction_width => -size_res'low);
  end function pos_inffp;

  function neg_inffp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float is
  begin
    return neg_inffp (
      exponent_width => size_res'high,
      fraction_width => -size_res'low);
  end function neg_inffp;

  function neg_zerofp (
    size_res : UNRESOLVED_float)        -- variable is only use for sizing
    return UNRESOLVED_float is
  begin
    return neg_zerofp (
      exponent_width => size_res'high,
      fraction_width => -size_res'low);
  end function neg_zerofp;

-- rtl_synthesis off
-- pragma synthesis_off

  --%%% these functions are copied from std_logic_1164 (VHDL-200X edition)
  -- Textio functions
  -- purpose: writes float into a line (NOTE changed basetype)
  type MVL9plus is ('U', 'X', '0', '1', 'Z', 'W', 'L', 'H', '-', error);
  type char_indexed_by_MVL9 is array (STD_ULOGIC) of CHARACTER;
  type MVL9_indexed_by_char is array (CHARACTER) of STD_ULOGIC;
  type MVL9plus_indexed_by_char is array (CHARACTER) of MVL9plus;

  constant NBSP         : CHARACTER            := CHARACTER'val(160);  -- space character
  constant MVL9_to_char : char_indexed_by_MVL9 := "UX01ZWLH-";
  constant char_to_MVL9 : MVL9_indexed_by_char :=
    ('U' => 'U', 'X' => 'X', '0' => '0', '1' => '1', 'Z' => 'Z',
     'W' => 'W', 'L' => 'L', 'H' => 'H', '-' => '-', others => 'U');
  constant char_to_MVL9plus : MVL9plus_indexed_by_char :=
    ('U' => 'U', 'X' => 'X', '0' => '0', '1' => '1', 'Z' => 'Z',
     'W' => 'W', 'L' => 'L', 'H' => 'H', '-' => '-', others => error);
  constant NUS : STRING(2 to 1) := (others => ' ');

  -- purpose: Skips white space
  procedure skip_whitespace (
    L : inout LINE) is
    variable readOk : BOOLEAN;
    variable c      : CHARACTER;
  begin
    while L /= null and L.all'length /= 0 loop
      if (L.all(1) = ' ' or L.all(1) = NBSP or L.all(1) = HT) then
        read (l, c, readOk);
      else
        exit;
      end if;
    end loop;
  end procedure skip_whitespace;

-- %%% Replicated textio functions
  function to_ostring (value : STD_LOGIC_VECTOR) return STRING is
    constant ne     : INTEGER := (value'length+2)/3;
    variable pad    : STD_LOGIC_VECTOR(0 to (ne*3 - value'length) - 1);
    variable ivalue : STD_LOGIC_VECTOR(0 to ne*3 - 1);
    variable result : STRING(1 to ne);
    variable tri    : STD_LOGIC_VECTOR(0 to 2);
  begin
    if value'length < 1 then
      return NUS;
    else
      if value (value'left) = 'Z' then
        pad := (others => 'Z');
      else
        pad := (others => '0');
      end if;
      ivalue := pad & value;
      for i in 0 to ne-1 loop
        tri := To_X01Z(ivalue(3*i to 3*i+2));
        case tri is
          when o"0"   => result(i+1) := '0';
          when o"1"   => result(i+1) := '1';
          when o"2"   => result(i+1) := '2';
          when o"3"   => result(i+1) := '3';
          when o"4"   => result(i+1) := '4';
          when o"5"   => result(i+1) := '5';
          when o"6"   => result(i+1) := '6';
          when o"7"   => result(i+1) := '7';
          when "ZZZ"  => result(i+1) := 'Z';
          when others => result(i+1) := 'X';
        end case;
      end loop;
      return result;
    end if;
  end function to_ostring;
  -------------------------------------------------------------------   
  function to_hstring (value : STD_LOGIC_VECTOR) return STRING is
    constant ne     : INTEGER := (value'length+3)/4;
    variable pad    : STD_LOGIC_VECTOR(0 to (ne*4 - value'length) - 1);
    variable ivalue : STD_LOGIC_VECTOR(0 to ne*4 - 1);
    variable result : STRING(1 to ne);
    variable quad   : STD_LOGIC_VECTOR(0 to 3);
  begin
    if value'length < 1 then
      return NUS;
    else
      if value (value'left) = 'Z' then
        pad := (others => 'Z');
      else
        pad := (others => '0');
      end if;
      ivalue := pad & value;
      for i in 0 to ne-1 loop
        quad := To_X01Z(ivalue(4*i to 4*i+3));
        case quad is
          when x"0"   => result(i+1) := '0';
          when x"1"   => result(i+1) := '1';
          when x"2"   => result(i+1) := '2';
          when x"3"   => result(i+1) := '3';
          when x"4"   => result(i+1) := '4';
          when x"5"   => result(i+1) := '5';
          when x"6"   => result(i+1) := '6';
          when x"7"   => result(i+1) := '7';
          when x"8"   => result(i+1) := '8';
          when x"9"   => result(i+1) := '9';
          when x"A"   => result(i+1) := 'A';
          when x"B"   => result(i+1) := 'B';
          when x"C"   => result(i+1) := 'C';
          when x"D"   => result(i+1) := 'D';
          when x"E"   => result(i+1) := 'E';
          when x"F"   => result(i+1) := 'F';
          when "ZZZZ" => result(i+1) := 'Z';
          when others => result(i+1) := 'X';
        end case;
      end loop;
      return result;
    end if;
  end function to_hstring;
  procedure Char2TriBits (C           :     CHARACTER;
                          RESULT      : out STD_LOGIC_VECTOR(2 downto 0);
                          GOOD        : out BOOLEAN;
                          ISSUE_ERROR : in  BOOLEAN) is
  begin
    case c is
      when '0' => result := o"0"; good := true;
      when '1' => result := o"1"; good := true;
      when '2' => result := o"2"; good := true;
      when '3' => result := o"3"; good := true;
      when '4' => result := o"4"; good := true;
      when '5' => result := o"5"; good := true;
      when '6' => result := o"6"; good := true;
      when '7' => result := o"7"; good := true;
      when 'Z' => result := "ZZZ"; good := true;
      when 'X' => result := "XXX"; good := true;
      when others =>
        assert not ISSUE_ERROR
          report float_pkg'instance_name
          & "OREAD Error: Read a '" & c &
          "', expected an Octal character (0-7)."
          severity error;
        result := "UUU";
        good   := false;
    end case;
  end procedure Char2TriBits;

  procedure OREAD (L    : inout LINE; VALUE : out STD_LOGIC_VECTOR;
                   GOOD : out   BOOLEAN) is
    variable ok    : BOOLEAN;
    variable c     : CHARACTER;
    constant ne    : INTEGER := (VALUE'length+2)/3;
    constant pad   : INTEGER := ne*3 - VALUE'length;
    variable sv    : STD_LOGIC_VECTOR(0 to ne*3 - 1);
    variable i     : INTEGER;
    variable lastu : BOOLEAN := false;           -- last character was an "_"
  begin
    VALUE := (VALUE'range => 'U');               -- initialize to a "U"
    Skip_whitespace (L);
    if VALUE'length > 0 then
      read (l, c, ok);
      i := 0;
      while i < ne loop
        -- Bail out if there was a bad read
        if not ok then
          good := false;
          return;
        elsif c = '_' then
          if i = 0 then
            good := false;                       -- Begins with an "_"
            return;
          elsif lastu then
            good := false;                       -- "__" detected
            return;
          else
            lastu := true;
          end if;
        else
          Char2TriBits(c, sv(3*i to 3*i+2), ok, false);
          if not ok then
            good := false;
            return;
          end if;
          i := i + 1;
          lastu := false;
        end if;
        if i < ne then
          read(L, c, ok);
        end if;
      end loop;
      if or_reduce (sv (0 to pad-1)) = '1' then  -- %%% replace with "or"
        good := false;                           -- vector was truncated.
      else
        good  := true;
        VALUE := sv (pad to sv'high);
      end if;
    else
      good := true;                              -- read into a null array
    end if;
  end procedure OREAD;

  -- Hex Read and Write procedures for STD_ULOGIC_VECTOR.
  -- Modified from the original to be more forgiving.

  procedure Char2QuadBits (C           :     CHARACTER;
                           RESULT      : out STD_LOGIC_VECTOR(3 downto 0);
                           GOOD        : out BOOLEAN;
                           ISSUE_ERROR : in  BOOLEAN) is
  begin
    case c is
      when '0'       => result := x"0"; good := true;
      when '1'       => result := x"1"; good := true;
      when '2'       => result := x"2"; good := true;
      when '3'       => result := x"3"; good := true;
      when '4'       => result := x"4"; good := true;
      when '5'       => result := x"5"; good := true;
      when '6'       => result := x"6"; good := true;
      when '7'       => result := x"7"; good := true;
      when '8'       => result := x"8"; good := true;
      when '9'       => result := x"9"; good := true;
      when 'A' | 'a' => result := x"A"; good := true;
      when 'B' | 'b' => result := x"B"; good := true;
      when 'C' | 'c' => result := x"C"; good := true;
      when 'D' | 'd' => result := x"D"; good := true;
      when 'E' | 'e' => result := x"E"; good := true;
      when 'F' | 'f' => result := x"F"; good := true;
      when 'Z'       => result := "ZZZZ"; good := true;
      when 'X'       => result := "XXXX"; good := true;
      when others =>
        assert not ISSUE_ERROR
          report float_pkg'instance_name
          & "HREAD Error: Read a '" & c &
          "', expected a Hex character (0-F)."
          severity error;
        result := "UUUU";
        good   := false;
    end case;
  end procedure Char2QuadBits;

  procedure HREAD (L    : inout LINE; VALUE : out STD_LOGIC_VECTOR;
                   GOOD : out   BOOLEAN) is
    variable ok    : BOOLEAN;
    variable c     : CHARACTER;
    constant ne    : INTEGER := (VALUE'length+3)/4;
    constant pad   : INTEGER := ne*4 - VALUE'length;
    variable sv    : STD_LOGIC_VECTOR(0 to ne*4 - 1);
    variable i     : INTEGER;
    variable lastu : BOOLEAN := false;  -- last character was an "_"
  begin
    VALUE := (VALUE'range => 'U');      -- initialize to a "U"
    Skip_whitespace (L);
    if VALUE'length > 0 then
      read (l, c, ok);
      i := 0;
      while i < ne loop
        -- Bail out if there was a bad read
        if not ok then
          good := false;
          return;
        elsif c = '_' then
          if i = 0 then
            good := false;              -- Begins with an "_"
            return;
          elsif lastu then
            good := false;              -- "__" detected
            return;
          else
            lastu := true;
          end if;
        else
          Char2QuadBits(c, sv(4*i to 4*i+3), ok, false);
          if not ok then
            good := false;
            return;
          end if;
          i := i + 1;
          lastu := false;
        end if;
        if i < ne then
          read(L, c, ok);
        end if;
      end loop;
      if or_reduce (sv (0 to pad-1)) = '1' then  -- %%% replace with "or"
        good := false;                  -- vector was truncated.
      else
        good  := true;
        VALUE := sv (pad to sv'high);
      end if;
    else
      good := true;                     -- Null input string, skips whitespace
    end if;
  end procedure HREAD;

-- %%% END replicated textio functions

  -- purpose: Checks the punctuation in a line
  procedure check_punctuation (
    arg   : in  STRING;
    colon : out BOOLEAN;                -- There was a colon in the line
    dot   : out BOOLEAN;                -- There was a dot in the line
    good  : out BOOLEAN;                -- True if enough characters found
    chars : in INTEGER) is
    -- Examples.  Legal inputs are "0000000", "0000.000", "0:000:000"
    alias xarg            : STRING (1 to arg'length) is arg;  -- make it downto range
    variable icolon, idot : BOOLEAN;    -- internal
    variable j : INTEGER := 0;          -- charters read
  begin
    good   := false;
    icolon := false;
    idot   := false;
    for i in 1 to arg'length loop
      if xarg(i) = ' ' or xarg(i) = NBSP or xarg(i) = HT or j = chars then
        exit;
      elsif xarg(i) = ':' then
        icolon := true;
      elsif xarg(i) = '.' then
        idot := true;
      elsif xarg (i) /= '_' then
        j := j + 1;
      end if;
    end loop;
    if j = chars then
      good := true;                     -- There are enough charactes to read
    end if;
    colon := icolon;
    if idot and icolon then
      dot := false;
    else
      dot := idot;
    end if;
  end procedure check_punctuation;

  -- purpose: Searches a line for a ":" and replaces it with a ".".
  procedure fix_colon (
    arg   : inout STRING;
    chars : in integer) is
    alias xarg            : STRING (1 to arg'length) is arg;  -- make it downto range
    variable j : INTEGER := 0;          -- charters read
  begin
    for i in 1 to arg'length loop
      if xarg(i) = ' ' or xarg(i) = NBSP or xarg(i) = HT or j > chars then
        exit;
      elsif xarg(i) = ':' then
        xarg (i) := '.';
      elsif xarg (i) /= '_' then
        j := j + 1;
      end if;
    end loop;
  end procedure fix_colon;

  procedure WRITE (
    L         : inout LINE;              -- input line
    VALUE     : in    UNRESOLVED_float;  -- floating point input
    JUSTIFIED : in    SIDE  := right;
    FIELD     : in    WIDTH := 0) is
    variable s     : STRING(1 to value'high - value'low +3);
    variable sindx : INTEGER;
  begin  -- function write
    s(1)  := MVL9_to_char(STD_ULOGIC(VALUE(VALUE'high)));
    s(2)  := ':';
    sindx := 3;
    for i in VALUE'high-1 downto 0 loop
      s(sindx) := MVL9_to_char(STD_ULOGIC(VALUE(i)));
      sindx    := sindx + 1;
    end loop;
    s(sindx) := ':';
    sindx    := sindx + 1;
    for i in -1 downto VALUE'low loop
      s(sindx) := MVL9_to_char(STD_ULOGIC(VALUE(i)));
      sindx    := sindx + 1;
    end loop;
    WRITE (L, s, JUSTIFIED, FIELD);
  end procedure WRITE;

  procedure READ (L : inout LINE; VALUE : out UNRESOLVED_float) is
    -- Possible data:  0:0000:0000000
    --                 000000000000
    variable c      : CHARACTER;
    variable mv     : UNRESOLVED_float (VALUE'range);
    variable readOk : BOOLEAN;
    variable lastu  : BOOLEAN := false;         -- last character was an "_"
    variable i      : INTEGER;          -- index variable
  begin  -- READ
    VALUE := (VALUE'range => 'U');      -- initialize to a "U"
    Skip_whitespace (L);
    READ (l, c, readOk);
    if VALUE'length > 0 then
      i := value'high;
      readloop : loop
        if readOk = false then          -- Bail out if there was a bad read
          report float_pkg'instance_name
            & "READ(float): "
            & "Error end of file encountered."
            severity error;
          return;
        elsif c = ' ' or c = CR or c = HT then  -- reading done.
          if (i /= value'low) then
            report float_pkg'instance_name
              & "READ(float): "
              & "Warning: Value truncated."
              severity warning;
            return;
          end if;
        elsif c = '_' then
          if i = value'high then        -- Begins with an "_"
            report float_pkg'instance_name
              & "READ(float): "
              & "String begins with an ""_""" severity error;
            return;
          elsif lastu then              -- "__" detected
            report float_pkg'instance_name
              & "READ(float): "
              & "Two underscores detected in input string ""__"""
              severity error;
            return;
          else
            lastu := true;
          end if;
        elsif c = ':' or c = '.' then   -- separator, ignore
          if not (i = -1 or i = value'high-1) then
            report float_pkg'instance_name
              & "READ(float):  "
              & "Warning: Separator point does not match number format: '"
              & c & "' encountered at location " & INTEGER'image(i) & "."
              severity warning;
          end if;
          lastu := false;
        elsif (char_to_MVL9plus(c) = error) then
          report float_pkg'instance_name
            & "READ(float): "
            & "Error: Character '" & c & "' read, expected STD_ULOGIC literal."
            severity error;
          return;
        else
          mv (i) := char_to_MVL9(c);
          i := i - 1;
          if i < value'low then
            VALUE := mv;
            return;
          end if;
          lastu := false;
        end if;
        READ (l, c, readOk);
      end loop readloop;
    end if;
  end procedure READ;

  procedure READ (L : inout LINE; VALUE : out UNRESOLVED_float; GOOD : out BOOLEAN) is
    -- Possible data:  0:0000:0000000
    --                 000000000000
    variable c      : CHARACTER;
    variable mv     : UNRESOLVED_float (VALUE'range);
    variable lastu  : BOOLEAN := false;         -- last character was an "_"
    variable i      : INTEGER;          -- index variable
    variable readOk : BOOLEAN;
  begin  -- READ
    VALUE := (VALUE'range => 'U');      -- initialize to a "U"
    Skip_whitespace (L);
    READ (l, c, readOk);
    if VALUE'length > 0 then
      i := value'high;
      good := false;
      readloop : loop
        if readOk = false then          -- Bail out if there was a bad read
          return;
        elsif c = ' ' or c = CR or c = HT then  -- reading done
          return;
        elsif c = '_' then
          if i = 0 then                 -- Begins with an "_"
            return;
          elsif lastu then              -- "__" detected
            return;
          else
            lastu := true;
          end if;
        elsif c = ':' or c = '.' then   -- separator, ignore
          -- good := (i = -1 or i = value'high-1);
          lastu := false;
        elsif (char_to_MVL9plus(c) = error) then
          return;
        else
          mv (i) := char_to_MVL9(c);
          i := i - 1;
          if i < value'low then
            good  := true;
            VALUE := mv;
            return;
          end if;
          lastu := false;
        end if;
        READ (l, c, readOk);
      end loop readloop;
    else
      good := true;                     -- read into a null array
    end if;
  end procedure READ;

  procedure OWRITE (
    L         : inout LINE;              -- access type (pointer)
    VALUE     : in    UNRESOLVED_float;  -- value to write
    JUSTIFIED : in    SIDE  := right;    -- which side to justify text
    FIELD     : in    WIDTH := 0) is     -- width of field
  begin
    WRITE (L         => L,
           VALUE     => to_ostring(VALUE),
           JUSTIFIED => JUSTIFIED,
           FIELD     => FIELD);
  end procedure OWRITE;

  procedure OREAD (L : inout LINE; VALUE : out UNRESOLVED_float) is
    constant ne         : INTEGER := ((value'length+2)/3) * 3;   -- pad
    variable slv        : STD_LOGIC_VECTOR (ne-1 downto 0);      -- slv
    variable slvu       : ufixed (VALUE'range);  -- Unsigned fixed point
    variable c          : CHARACTER;
    variable ok         : BOOLEAN;
    variable nybble     : STD_LOGIC_VECTOR (2 downto 0);         -- 3 bits
    variable colon, dot : BOOLEAN;
  begin
    VALUE := (VALUE'range => 'U');      -- initialize to a "U"
    Skip_whitespace (L);
    if VALUE'length > 0 then
      check_punctuation (arg   => L.all,
                         colon => colon,
                         dot   => dot,
                         good  => ok,
                         chars => ne/3);
      if not ok then
        report float_pkg'instance_name & "OREAD: "
          & "short string encounted: " & L.all
          & " needs to have " & integer'image (ne/3)
          & " valid octal characters."
          severity error;
        return;
      elsif dot then
        OREAD (L, slvu, ok);            -- read it like a UFIXED number
        if not ok then
          report float_pkg'instance_name & "OREAD: "
            & "error encounted reading STRING " & L.all
            severity error;
          return;
        else
          VALUE := UNRESOLVED_float (slvu);
        end if;
      elsif colon then
        OREAD (L, nybble, ok);          -- read the sign bit
        if not ok then
          report float_pkg'instance_name & "OREAD: "
            & "End of string encountered"
            severity error;
          return;
        elsif nybble (2 downto 1) /= "00" then
          report float_pkg'instance_name & "OREAD: "
            & "Illegal sign bit STRING encounted "
            severity error;
          return;
        end if;
        read (l, c, ok);                -- read the colon
        fix_colon (L.all, ne/3);         -- replaces the colon with a ".".
        OREAD (L, slvu (slvu'high-1 downto slvu'low), ok);  -- read it like a UFIXED number
        if not ok then
          report float_pkg'instance_name & "OREAD: "
            & "error encounted reading STRING " & L.all
            severity error;
          return;
        else
          slvu (slvu'high) := nybble (0);
          VALUE := UNRESOLVED_float (slvu);
        end if;
      else
        OREAD (L, slv, ok);
        if not ok then
          report float_pkg'instance_name & "OREAD: "
            & "Error encounted during read"
            severity error;
          return;
        end if;
        if (or_reduce (slv(ne-1 downto VALUE'high-VALUE'low+1)) = '1') then
          report float_pkg'instance_name & "OREAD: "
            & "Vector truncated."
            severity error;
          return;
        end if;
        VALUE := to_float (slv(VALUE'high-VALUE'low downto 0),
                           VALUE'high, -VALUE'low);
      end if;
    end if;
  end procedure OREAD;

  procedure OREAD(L : inout LINE; VALUE : out UNRESOLVED_float; GOOD : out BOOLEAN) is
    constant ne         : INTEGER := ((value'length+2)/3) * 3;   -- pad
    variable slv        : STD_LOGIC_VECTOR (ne-1 downto 0);      -- slv
    variable slvu       : ufixed (VALUE'range);  -- Unsigned fixed point
    variable c          : CHARACTER;
    variable ok         : BOOLEAN;
    variable nybble     : STD_LOGIC_VECTOR (2 downto 0);         -- 3 bits
    variable colon, dot : BOOLEAN;
  begin
    VALUE := (VALUE'range => 'U');      -- initialize to a "U"
    GOOD  := false;
    Skip_whitespace (L);
    if VALUE'length > 0 then
      check_punctuation (arg   => L.all,
                         colon => colon,
                         dot   => dot,
                         good  => ok,
                         chars => ne/3);
      if not ok then
        return;
      elsif dot then
        OREAD (L, slvu, ok);            -- read it like a UFIXED number
        if not ok then
          return;
        else
          VALUE := UNRESOLVED_float (slvu);
        end if;
      elsif colon then
        OREAD (L, nybble, ok);          -- read the sign bit
        if not ok then
          return;
        elsif nybble (2 downto 1) /= "00" then
          return;
        end if;
        read (l, c, ok);                -- read the colon
        fix_colon (L.all, ne/3);         -- replaces the colon with a ".".
        OREAD (L, slvu (slvu'high-1 downto slvu'low), ok);  -- read it like a UFIXED number
        if not ok then
          return;
        else
          slvu (slvu'high) := nybble (0);
          VALUE := UNRESOLVED_float (slvu);
        end if;
      else
        OREAD (L, slv, ok);
        if not ok then
          return;
        end if;
        if (or_reduce (slv(ne-1 downto VALUE'high-VALUE'low+1)) = '1') then
          return;
        end if;
        VALUE := to_float (slv(VALUE'high-VALUE'low downto 0),
                           VALUE'high, -VALUE'low);
      end if;
      GOOD := true;
    end if;
  end procedure OREAD;

  procedure HWRITE (
    L         : inout LINE;              -- access type (pointer)
    VALUE     : in    UNRESOLVED_float;  -- value to write
    JUSTIFIED : in    SIDE  := right;    -- which side to justify text
    FIELD     : in    WIDTH := 0) is     -- width of field
  begin
    WRITE (L         => L,
           VALUE     => to_hstring(VALUE),
           JUSTIFIED => JUSTIFIED,
           FIELD     => FIELD);
  end procedure HWRITE;

  procedure HREAD (L : inout LINE; VALUE : out UNRESOLVED_float) is
    constant ne         : INTEGER := ((value'length+3)/4) * 4;   -- pad
    variable slv        : STD_LOGIC_VECTOR (ne-1 downto 0);      -- slv
    variable slvu       : ufixed (VALUE'range);  -- Unsigned fixed point
    variable c          : CHARACTER;
    variable ok         : BOOLEAN;
    variable nybble     : STD_LOGIC_VECTOR (3 downto 0);         -- 4 bits
    variable colon, dot : BOOLEAN;
  begin
    VALUE := (VALUE'range => 'U');      -- initialize to a "U"
    Skip_whitespace (L);
    if VALUE'length > 0 then
      check_punctuation (arg   => L.all,
                         colon => colon,
                         dot   => dot,
                         good  => ok,
                         chars => ne/4);
      if not ok then
        report float_pkg'instance_name & "HREAD: "
          & "short string encounted: " & L.all
          & " needs to have " & integer'image (ne/4)
          & " valid hex characters."
          severity error;
        return;
      elsif dot then
        HREAD (L, slvu, ok);            -- read it like a UFIXED number
        if not ok then
          report float_pkg'instance_name & "HREAD: "
            & "error encounted reading STRING " & L.all
            severity error;
          return;
        else
          VALUE := UNRESOLVED_float (slvu);
        end if;
      elsif colon then
        HREAD (L, nybble, ok);          -- read the sign bit
        if not ok then
          report float_pkg'instance_name & "HREAD: "
            & "End of string encountered"
            severity error;
          return;
        elsif nybble (3 downto 1) /= "000" then
          report float_pkg'instance_name & "HREAD: "
            & "Illegal sign bit STRING encounted "
            severity error;
          return;
        end if;
        read (l, c, ok);                -- read the colon
        fix_colon (L.all, ne/4);         -- replaces the colon with a ".".
        HREAD (L, slvu (slvu'high-1 downto slvu'low), ok);  -- read it like a UFIXED number
        if not ok then
          report float_pkg'instance_name & "HREAD: "
            & "error encounted reading STRING " & L.all
            severity error;
          return;
        else
          slvu (slvu'high) := nybble (0);
          VALUE := UNRESOLVED_float (slvu);
        end if;
      else
        HREAD (L, slv, ok);
        if not ok then
          report float_pkg'instance_name & "HREAD: "
            & "Error encounted during read"
            severity error;
          return;
        end if;
        if (or_reduce (slv(ne-1 downto VALUE'high-VALUE'low+1)) = '1') then
          report float_pkg'instance_name & "HREAD: "
            & "Vector truncated."
            severity error;
          return;
        end if;
        VALUE := to_float (slv(VALUE'high-VALUE'low downto 0),
                           VALUE'high, -VALUE'low);
      end if;
    end if;
  end procedure HREAD;

  procedure HREAD (L : inout LINE; VALUE : out UNRESOLVED_float; GOOD : out BOOLEAN) is
    constant ne         : INTEGER := ((value'length+3)/4) * 4;   -- pad
    variable slv        : STD_LOGIC_VECTOR (ne-1 downto 0);      -- slv
    variable slvu       : ufixed (VALUE'range);  -- Unsigned fixed point
    variable c          : CHARACTER;
    variable ok         : BOOLEAN;
    variable nybble     : STD_LOGIC_VECTOR (3 downto 0);         -- 4 bits
    variable colon, dot : BOOLEAN;
  begin
    VALUE := (VALUE'range => 'U');      -- initialize to a "U"
    GOOD  := false;
    Skip_whitespace (L);
    if VALUE'length > 0 then
      check_punctuation (arg   => L.all,
                         colon => colon,
                         dot   => dot,
                         good  => ok,
                         chars => ne/4);
      if not ok then
        return;
      elsif dot then
        HREAD (L, slvu, ok);            -- read it like a UFIXED number
        if not ok then
          return;
        else
          VALUE := UNRESOLVED_float (slvu);
        end if;
      elsif colon then
        HREAD (L, nybble, ok);          -- read the sign bit
        if not ok then
          return;
        elsif nybble (3 downto 1) /= "000" then
          return;
        end if;
        read (l, c, ok);                -- read the colon
        fix_colon (L.all, ne/4);         -- replaces the colon with a ".".
        HREAD (L, slvu (slvu'high-1 downto slvu'low), ok);  -- read it like a UFIXED number
        if not ok then
          return;
        else
          slvu (slvu'high) := nybble (0);
          VALUE := UNRESOLVED_float (slvu);
        end if;
      else
        HREAD (L, slv, ok);
        if not ok then
          return;
        end if;
        if (or_reduce (slv(ne-1 downto VALUE'high-VALUE'low+1)) = '1') then
          return;
        end if;
        VALUE := to_float (slv(VALUE'high-VALUE'low downto 0),
                           VALUE'high, -VALUE'low);
      end if;
      GOOD := true;
    end if;
  end procedure HREAD;

  function to_string (value : UNRESOLVED_float) return STRING is
    variable s     : STRING(1 to value'high - value'low +3);
    variable sindx : INTEGER;
  begin  -- function write
    s(1)  := MVL9_to_char(STD_ULOGIC(VALUE(VALUE'high)));
    s(2)  := ':';
    sindx := 3;
    for i in VALUE'high-1 downto 0 loop
      s(sindx) := MVL9_to_char(STD_ULOGIC(VALUE(i)));
      sindx    := sindx + 1;
    end loop;
    s(sindx) := ':';
    sindx    := sindx + 1;
    for i in -1 downto VALUE'low loop
      s(sindx) := MVL9_to_char(STD_ULOGIC(VALUE(i)));
      sindx    := sindx + 1;
    end loop;
    return s;
  end function to_string;

  function to_hstring (value : UNRESOLVED_float) return STRING is
    variable slv : STD_LOGIC_VECTOR (value'length-1 downto 0);
  begin
    floop : for i in slv'range loop
      slv(i) := to_X01Z (value(i + value'low));
    end loop floop;
    return to_hstring (slv);
  end function to_hstring;

  function to_ostring (value : UNRESOLVED_float) return STRING is
    variable slv : STD_LOGIC_VECTOR (value'length-1 downto 0);
  begin
    floop : for i in slv'range loop
      slv(i) := to_X01Z (value(i + value'low));
    end loop floop;
    return to_ostring (slv);
  end function to_ostring;

  function from_string (
    bstring                 : STRING;   -- binary string
    constant exponent_width : NATURAL := float_exponent_width;
    constant fraction_width : NATURAL := float_fraction_width)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable L      : LINE;
    variable good   : BOOLEAN;
  begin
    L := new STRING'(bstring);
    READ (L, result, good);
    deallocate (L);
    assert (good)
      report float_pkg'instance_name
      & "from_string: Bad string " & bstring
      severity error;
    return result;
  end function from_string;

  function from_ostring (
    ostring                 : STRING;   -- Octal string
    constant exponent_width : NATURAL := float_exponent_width;
    constant fraction_width : NATURAL := float_fraction_width)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable L      : LINE;
    variable good   : BOOLEAN;
  begin
    L := new STRING'(ostring);
    OREAD (L, result, good);
    deallocate (L);
    assert (good)
      report float_pkg'instance_name
      & "from_ostring: Bad string " & ostring
      severity error;
    return result;
  end function from_ostring;

  function from_hstring (
    hstring                 : STRING;   -- hex string
    constant exponent_width : NATURAL := float_exponent_width;
    constant fraction_width : NATURAL := float_fraction_width)
    return UNRESOLVED_float is
    variable result : UNRESOLVED_float (exponent_width downto -fraction_width);
    variable L      : LINE;
    variable good   : BOOLEAN;
  begin
    L := new STRING'(hstring);
    HREAD (L, result, good);
    deallocate (L);
    assert (good)
      report float_pkg'instance_name
      & "from_hstring: Bad string " & hstring
      severity error;
    return result;
  end function from_hstring;

  function from_string (
    bstring  : STRING;                  -- binary string
    size_res : UNRESOLVED_float)        -- used for sizing only 
    return UNRESOLVED_float is
  begin
    return from_string (bstring        => bstring,
                        exponent_width => size_res'high,
                        fraction_width => -size_res'low);
  end function from_string;

  function from_ostring (
    ostring  : STRING;                  -- Octal string
    size_res : UNRESOLVED_float)        -- used for sizing only 
    return UNRESOLVED_float is
  begin
    return from_ostring (ostring        => ostring,
                         exponent_width => size_res'high,
                         fraction_width => -size_res'low);
  end function from_ostring;

  function from_hstring (
    hstring  : STRING;                  -- hex string
    size_res : UNRESOLVED_float)        -- used for sizing only 
    return UNRESOLVED_float is
  begin
    return from_hstring (hstring        => hstring,
                         exponent_width => size_res'high,
                         fraction_width => -size_res'low);
  end function from_hstring;
-- rtl_synthesis on
-- pragma synthesis_on
  function to_float (
    arg                     : STD_LOGIC_VECTOR;
    constant exponent_width : NATURAL := float_exponent_width;  -- length of FP output exponent
    constant fraction_width : NATURAL := float_fraction_width)  -- length of FP output fraction
    return UNRESOLVED_float is
  begin
    return to_float (
      arg            => to_stdulogicvector (arg),
      exponent_width => exponent_width,
      fraction_width => fraction_width);
  end function to_float;

  function to_float (
    arg      : STD_LOGIC_VECTOR;
    size_res : UNRESOLVED_float)
    return UNRESOLVED_float is
  begin
    return to_float (
      arg      => to_stdulogicvector (arg),
      size_res => size_res);
  end function to_float;

  -- For Verilog compatability
  function realtobits (arg : REAL) return STD_LOGIC_VECTOR is
    variable result : float64;          -- 64 bit floating point
  begin
    result := to_float (arg => arg,
                        exponent_width => float64'high,
                        fraction_width => -float64'low);
    return to_slv (result);
  end function realtobits;

  function bitstoreal (arg : STD_LOGIC_VECTOR) return REAL is
    variable arg64 : float64;           -- arg converted to float
  begin
    arg64 := to_float (arg => arg,
                       exponent_width => float64'high,
                       fraction_width => -float64'low);
    return to_real (arg64);
  end function bitstoreal;

end package body float_pkg;
