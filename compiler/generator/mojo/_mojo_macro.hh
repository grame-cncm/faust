/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

// compiler/generator/mojo/_mojo_macro.hh

#ifndef _MOJO_MACRO_HH
#define _MOJO_MACRO_HH

#ifndef mj_debug_msg
    #define mj_debug_msg(out, ...) \
         out << "\n======== DEBUG - " << __VA_ARGS__ << " =========\n"
#endif

#ifndef mj_error_msg
    #define mj_error_msg(out, ...) \
        out << "\n======== ERROR - " << __VA_ARGS__ << " =========\n"
#endif

#ifndef mj_debug_fir
    #define mj_debug_fir(out, inst, msg)      \
        mj_debug_msg(out, "FIR DUMP - " msg); \
        dump2FIR(inst, out, false);           \
        out << "\n"
#endif

#ifndef mj_unused
    #define mj_unused(x) ((void)(x))
#endif

#ifndef mj_noimpl
    #define mj_noimpl(out, msg) \
        mj_error_msg(out, msg " is not implemented");
#endif

#ifndef mj_noimpl1
    #define mj_noimpl1(out, msg, x) \
        mj_unused(x); mj_noimpl(out, msg)
#endif

#ifndef mj_noimpl2
    #define mj_noimpl2(out, msg, x, y) \
        mj_unused(x); mj_unused(y); mj_noimpl(out, msg)
#endif

#ifndef mj_noimpl3
    #define mj_noimpl3(out, msg, x, y, z) \
        mj_unused(x); mj_unused(y); mj_unused(z); mj_noimpl(out, msg)
#endif

#ifndef mj_noimpl4
    #define mj_noimpl4(out, msg, x, y, z, w) \
        mj_unused(x); mj_unused(y); mj_unused(z); mj_unused(w); mj_noimpl(out, msg)
#endif

#ifndef mj_noimpl5
    #define mj_noimpl5(out, msg, x, y, z, w, v) \
        mj_unused(x); mj_unused(y); mj_unused(z); mj_unused(w); mj_unused(v); mj_noimpl(out, msg)
#endif

#ifndef mj_noimpl6
    #define mj_noimpl6(out, msg, x, y, z, w, v, u) \
        mj_unused(x); mj_unused(y); mj_unused(z); mj_unused(w); mj_unused(v); mj_unused(u); mj_noimpl(out, msg)
#endif

#ifndef dycast
    #define dycast(T, x) dynamic_cast<T>(x)
#endif
#ifndef recast
    #define recast(T, x) reinterpret_cast<T>(x)
#endif

#endif  // _MOJO_MACRO_HH
