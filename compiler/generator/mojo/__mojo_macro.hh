/*                                                                             *
*   SPDX-FileCopyrightText: 2026 GRAME, Centre National de Creation Musicale   *
*   SPDX-License-Identifier: LGPL-2.1-or-later                                 *
*                                                                             */

/** @file compiler/generator/mojo/__mojo_macro.hh **/

#ifndef _MOJO_MACRO_HH
#define _MOJO_MACRO_HH

#include "__mojo_hal.hh"

#define mj_debug_msg(out, ...) out << "\n======== DEBUG -- " << __VA_ARGS__ << " =========\n"
#define mj_error_msg(out, ...) out << "\n======== ERROR -- " << __VA_ARGS__ << " =========\n"
#define mj_panic_msg(out, ...) out << "\n======== PANIC -- " << __VA_ARGS__ << " =========\n"

#define mj_debug_fir(out, inst, msg)      \
    mj_debug_msg(out, "FIR DUMP - " msg); \
    dump2FIR(inst, out, false);           \
    out << "\n"

#define mj_panic(cond, ...)                   \
    if (!(cond)) {                            \
        mj_panic_msg(std::cerr, __VA_ARGS__); \
        faustassert(cond);                    \
        mj_unreachable();                     \
    }

#define mj_unused(x) ((void)(x))
#define mj_noimpl(out, msg) mj_error_msg(out, msg " is not implemented");
#define mj_noimpl1(out, msg, x) \
    mj_unused(x); mj_noimpl(out, msg)
#define mj_noimpl2(out, msg, x, y) \
    mj_unused(x); mj_unused(y); mj_noimpl(out, msg)
#define mj_noimpl3(out, msg, x, y, z) \
    mj_unused(x); mj_unused(y); mj_unused(z); mj_noimpl(out, msg)
#define mj_noimpl4(out, msg, x, y, z, w) \
    mj_unused(x); mj_unused(y); mj_unused(z); mj_unused(w); mj_noimpl(out, msg)
#define mj_noimpl5(out, msg, x, y, z, w, v) \
    mj_unused(x); mj_unused(y); mj_unused(z); mj_unused(w); mj_unused(v); mj_noimpl(out, msg)
#define mj_noimpl6(out, msg, x, y, z, w, v, u) \
    mj_unused(x); mj_unused(y); mj_unused(z); mj_unused(w); mj_unused(v); mj_unused(u); mj_noimpl(out, msg)

#define dycast(T, x) dynamic_cast<T>(x)
#define recast(T, x) reinterpret_cast<T>(x)

#define mj_simd_emit_check() if (not gSIMDEmit) return MojoInstVisitor::visit(inst);

#define mj_simd_emit_set(b)    b32 simd_emit_saved = gSIMDEmit; gSIMDEmit = b
#define mj_simd_emit_restore() gSIMDEmit = simd_emit_saved

#define mj_simd_high_set(b)    b32 simd_high_saved = gSIMDHigh; gSIMDHigh = b
#define mj_simd_high_restore() gSIMDHigh = simd_high_saved

#define mj_simd_emit_accept(_inst_) \
    mj_simd_emit_set(true); _inst_->accept(this); mj_simd_emit_restore()
#define mj_scalar_accept(_inst_) \
    mj_simd_emit_set(false); _inst_->accept(this); mj_simd_emit_restore()
#define mj_simd_high_accept(_inst_) \
    mj_simd_high_set(true); _inst_->accept(this); mj_simd_high_restore()

#define mj_scalar_visit(_inst_) mj_simd_emit_set(false); MojoInstVisitor::visit(_inst_); mj_simd_emit_restore()

#define mj_gpu_emit_check() if (not fKernel) return BaseVisitor::visit(inst); 

#endif  // _MOJO_MACRO_HH
