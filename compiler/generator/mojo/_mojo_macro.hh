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

#ifndef _MOJO_MACRO_HH
#define _MOJO_MACRO_HH

#ifndef mj_debug_msg
    #define mj_debug_msg(...) \
        *fOut << "\n\n-------- DEBUG: " << __VA_ARGS__ << " --------\n\n"
#endif

#ifndef mj_error_msg
    #define mj_error_msg(...) \
        *fOut << "\n\n-------- ERROR: " << __VA_ARGS__ << " --------\n\n"
#endif

#ifndef mj_debug_fir
    #define mj_debug_fir(inst, msg) \
        mj_debug_msg(msg);          \
        dump2FIR(inst, *fOut);      \
        *fOut << wbanner() << "\n"
#endif

#ifndef mj_unused
    #define mj_unused(x) ((void)(x))
#endif

#ifndef mj_noimpl0
    #define mj_noimpl0(msg) \
        *fOut << msg
#endif

#ifndef mj_noimpl1
    #define mj_noimpl1(x, msg)      \
        mj_unused(x);               \
        mj_error_msg(msg)
#endif

#ifndef mj_noimpl2
    #define mj_noimpl2(x, y, msg) \
        mj_unused(x);             \
        mj_unused(y);             \
        mj_error_msg(msg)
#endif

#ifndef mj_noimpl3
    #define mj_noimpl3(x, y, z, msg) \
        mj_unused(x);                \
        mj_unused(y);                \
        mj_unused(z);                \
        mj_error_msg(msg)
#endif

#ifndef dycast
    #define dycast(T, x) dynamic_cast<T>(x)
#endif
#ifndef stcast
    #define stcast(T, x) static_cast<T>(x)
#endif
#ifndef recast
    #define recast(T, x) reinterpret_cast<T>(x)
#endif
#ifndef cast
    #define cast(T, x) ((T) (x))
#endif

#endif  // _MOJO_MACRO_HH
