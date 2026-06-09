	.build_version macos, 26, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_inspect_compute
	.p2align	2
_inspect_compute:
	stp	d15, d14, [sp, #-160]!
	stp	d13, d12, [sp, #16]
	stp	d11, d10, [sp, #32]
	stp	d9, d8, [sp, #48]
	stp	x28, x27, [sp, #64]
	stp	x26, x25, [sp, #80]
	stp	x24, x23, [sp, #96]
	stp	x22, x21, [sp, #112]
	stp	x20, x19, [sp, #128]
	stp	x29, x30, [sp, #144]
	sub	sp, sp, #352
	mov	x19, x2
	mov	x20, x1
	mov	x21, x0
	add	x22, x0, #264
	mov	w8, #99
	add	x23, sp, #344
	mov	x9, #-7378697629483820647
	movk	x9, #39322
	movk	x9, #49065, lsl #48
	str	x9, [sp, #48]
LBB0_1:
	mov	x24, x8
	str	x20, [sp, #344]
	; InlineAsm Start
	; InlineAsm End
	str	x19, [sp, #344]
	; InlineAsm Start
	; InlineAsm End
	ldr	x25, [x20]
	ldr	x26, [x19]
	ldr	s0, [x21, #16]
	fcvt	d0, s0
	ldr	d11, [x21, #8]
	fmul	d0, d11, d0
	bl	_tan
	mov.16b	v8, v0
	ldp	s1, s0, [x21, #20]
	fcvt	d9, s0
	str	d9, [sp, #40]
	fcvt	d0, s1
	ldr	d13, [sp, #48]
	fmul	d1, d0, d13
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d9
	stp	d8, d0, [sp, #24]
	fadd	d0, d8, d0
	fmov	d12, #1.00000000
	fmadd	d0, d8, d0, d12
	fdiv	d2, d12, d0
	fmov	d0, #-1.00000000
	fmadd	d0, d8, d8, d0
	fadd	d0, d0, d0
	stp	d0, d2, [sp, #328]
	ldr	s0, [x21, #28]
	fcvt	d0, s0
	fmul	d0, d11, d0
	bl	_tan
	mov.16b	v8, v0
	ldp	s1, s0, [x21, #32]
	fcvt	d9, s0
	str	d9, [sp, #56]
	fcvt	d0, s1
	fmul	d1, d0, d13
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d9
	str	d0, [sp, #64]
	mov.16b	v1, v8
	str	d8, [sp, #16]
	fadd	d0, d8, d0
	fmadd	d0, d8, d0, d12
	fdiv	d2, d12, d0
	fmov	d8, #-1.00000000
	fmadd	d0, d1, d1, d8
	fadd	d0, d0, d0
	stp	d0, d2, [sp, #312]
	ldr	s0, [x21, #40]
	fcvt	d0, s0
	fmul	d0, d11, d0
	bl	_tan
	mov.16b	v9, v0
	ldp	s1, s0, [x21, #44]
	fcvt	d10, s0
	str	d10, [sp, #80]
	fcvt	d0, s1
	fmul	d1, d0, d13
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d10
	str	d0, [sp, #88]
	str	d9, [sp, #72]
	fadd	d0, d9, d0
	fmadd	d0, d9, d0, d12
	fdiv	d2, d12, d0
	fmadd	d0, d9, d9, d8
	fmov	d8, #-1.00000000
	fadd	d0, d0, d0
	stp	d0, d2, [sp, #296]
	ldr	s0, [x21, #52]
	fcvt	d0, s0
	fmul	d0, d11, d0
	bl	_tan
	mov.16b	v9, v0
	ldp	s1, s0, [x21, #56]
	fcvt	d10, s0
	str	d10, [sp, #104]
	fcvt	d0, s1
	fmul	d1, d0, d13
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d10
	str	d0, [sp, #112]
	str	d9, [sp, #96]
	fadd	d0, d9, d0
	fmadd	d0, d9, d0, d12
	fdiv	d14, d12, d0
	fmadd	d0, d9, d9, d8
	fadd	d0, d0, d0
	str	d0, [sp, #288]
	ldr	s0, [x21, #64]
	fcvt	d0, s0
	fmul	d0, d11, d0
	mov.16b	v10, v11
	bl	_tan
	mov.16b	v9, v0
	ldp	s1, s0, [x21, #68]
	fcvt	d11, s0
	str	d11, [sp, #128]
	fcvt	d0, s1
	mov.16b	v8, v13
	fmul	d1, d0, d13
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d11
	str	d0, [sp, #136]
	str	d9, [sp, #120]
	fadd	d0, d9, d0
	fmadd	d0, d9, d0, d12
	fdiv	d13, d12, d0
	fmov	d0, #-1.00000000
	fmadd	d0, d9, d9, d0
	fadd	d0, d0, d0
	str	d0, [sp, #280]
	ldr	s0, [x21, #76]
	fcvt	d0, s0
	fmul	d0, d10, d0
	bl	_tan
	mov.16b	v11, v0
	ldp	s1, s0, [x21, #80]
	fcvt	d15, s0
	str	d15, [sp, #152]
	fcvt	d0, s1
	fmul	d1, d0, d8
	mov.16b	v9, v8
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d15
	str	d0, [sp, #160]
	str	d11, [sp, #144]
	fadd	d0, d11, d0
	fmadd	d0, d11, d0, d12
	fdiv	d15, d12, d0
	fmov	d0, #-1.00000000
	fmadd	d0, d11, d11, d0
	fadd	d0, d0, d0
	str	d0, [sp, #272]
	ldr	s0, [x21, #88]
	fcvt	d0, s0
	fmul	d0, d10, d0
	str	d10, [sp, #240]
	bl	_tan
	mov.16b	v8, v0
	ldp	s1, s0, [x21, #92]
	fcvt	d11, s0
	str	d11, [sp, #176]
	fcvt	d0, s1
	fmul	d1, d0, d9
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d11
	str	d0, [sp, #184]
	mov.16b	v1, v8
	str	d8, [sp, #168]
	fadd	d0, d8, d0
	fmadd	d0, d8, d0, d12
	fdiv	d8, d12, d0
	fmov	d0, #-1.00000000
	fmadd	d0, d1, d1, d0
	fadd	d0, d0, d0
	str	d0, [sp, #264]
	ldr	s0, [x21, #100]
	fcvt	d0, s0
	fmul	d0, d10, d0
	bl	_tan
	mov.16b	v10, v0
	ldp	s1, s0, [x21, #104]
	fcvt	d9, s0
	str	d9, [sp, #200]
	fcvt	d0, s1
	ldr	d11, [sp, #48]
	fmul	d1, d0, d11
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d9
	str	d0, [sp, #208]
	str	d10, [sp, #192]
	fadd	d0, d10, d0
	fmadd	d0, d10, d0, d12
	fdiv	d9, d12, d0
	fmov	d0, #-1.00000000
	fmadd	d0, d10, d10, d0
	fadd	d0, d0, d0
	str	d0, [sp, #256]
	ldr	s0, [x21, #112]
	fcvt	d0, s0
	ldr	d1, [sp, #240]
	fmul	d0, d1, d0
	bl	_tan
	str	d0, [sp, #216]
	ldp	s1, s0, [x21, #116]
	fcvt	d10, s0
	str	d10, [sp, #224]
	fcvt	d0, s1
	fmul	d1, d0, d11
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	fdiv	d0, d0, d10
	str	d0, [sp, #232]
	ldr	d1, [sp, #216]
	fadd	d0, d1, d0
	fmadd	d0, d1, d0, d12
	fdiv	d11, d12, d0
	fmov	d0, #-1.00000000
	fmadd	d0, d1, d1, d0
	fadd	d0, d0, d0
	str	d0, [sp, #248]
	ldr	s0, [x21, #124]
	fcvt	d0, s0
	ldr	d1, [sp, #240]
	fmul	d0, d1, d0
	bl	_tan
	str	d0, [sp, #8]
	ldp	s1, s0, [x21, #128]
	fcvt	d10, s0
	fcvt	d0, s1
	ldr	d1, [sp, #48]
	fmul	d1, d0, d1
	fmov	d0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]"
	mov	x8, #0
	fdiv	d0, d0, d10
	ldr	d16, [sp, #8]
	fadd	d1, d16, d0
	fmadd	d7, d16, d1, d12
	fsub	d0, d16, d0
	fmadd	d1, d16, d0, d12
	fdiv	d5, d12, d10
	ldr	d2, [sp, #216]
	ldr	d0, [sp, #232]
	fsub	d0, d2, d0
	fmadd	d0, d2, d0, d12
	stp	d0, d1, [sp, #232]
	ldr	d0, [sp, #224]
	fdiv	d0, d12, d0
	fadd	d1, d2, d0
	fmadd	d1, d2, d1, d12
	fsub	d0, d0, d2
	fmsub	d0, d2, d0, d12
	stp	d0, d1, [sp, #216]
	ldr	d2, [sp, #192]
	ldr	d0, [sp, #208]
	fsub	d0, d2, d0
	fmadd	d3, d2, d0, d12
	ldr	d0, [sp, #200]
	fdiv	d0, d12, d0
	fadd	d1, d2, d0
	fmadd	d1, d2, d1, d12
	stp	d1, d3, [sp, #200]
	fsub	d0, d0, d2
	fmsub	d1, d2, d0, d12
	ldr	d2, [sp, #168]
	ldr	d0, [sp, #184]
	fsub	d0, d2, d0
	fmadd	d0, d2, d0, d12
	stp	d0, d1, [sp, #184]
	ldr	d0, [sp, #176]
	fdiv	d0, d12, d0
	fadd	d1, d2, d0
	fmadd	d1, d2, d1, d12
	fsub	d0, d0, d2
	fmsub	d0, d2, d0, d12
	stp	d0, d1, [sp, #168]
	ldr	d2, [sp, #144]
	ldr	d0, [sp, #160]
	fsub	d0, d2, d0
	fmadd	d3, d2, d0, d12
	ldr	d0, [sp, #152]
	fdiv	d0, d12, d0
	fadd	d1, d2, d0
	fmadd	d1, d2, d1, d12
	stp	d1, d3, [sp, #152]
	fsub	d0, d0, d2
	fmsub	d1, d2, d0, d12
	ldr	d2, [sp, #120]
	ldr	d0, [sp, #136]
	fsub	d0, d2, d0
	fmadd	d0, d2, d0, d12
	stp	d0, d1, [sp, #136]
	ldr	d0, [sp, #128]
	fdiv	d0, d12, d0
	fadd	d1, d2, d0
	fmadd	d1, d2, d1, d12
	fsub	d0, d0, d2
	fmsub	d0, d2, d0, d12
	stp	d0, d1, [sp, #120]
	ldr	d2, [sp, #96]
	ldr	d0, [sp, #112]
	fsub	d0, d2, d0
	fmadd	d3, d2, d0, d12
	ldr	d0, [sp, #104]
	fdiv	d0, d12, d0
	fadd	d1, d2, d0
	fmadd	d1, d2, d1, d12
	stp	d1, d3, [sp, #104]
	fsub	d0, d0, d2
	fmsub	d1, d2, d0, d12
	ldr	d2, [sp, #72]
	ldr	d0, [sp, #88]
	fsub	d0, d2, d0
	fmadd	d0, d2, d0, d12
	stp	d0, d1, [sp, #88]
	ldr	d0, [sp, #80]
	fdiv	d0, d12, d0
	fadd	d1, d2, d0
	fmadd	d1, d2, d1, d12
	fsub	d0, d0, d2
	fmsub	d0, d2, d0, d12
	stp	d0, d1, [sp, #72]
	ldp	d2, d4, [sp, #16]
	ldr	d0, [sp, #64]
	fsub	d0, d2, d0
	fmadd	d3, d2, d0, d12
	ldr	d0, [sp, #56]
	fdiv	d0, d12, d0
	fadd	d1, d2, d0
	fmadd	d1, d2, d1, d12
	stp	d1, d3, [sp, #56]
	fsub	d0, d0, d2
	fmsub	d0, d2, d0, d12
	ldp	d1, d2, [sp, #32]
	fsub	d1, d4, d1
	fmadd	d1, d4, d1, d12
	fdiv	d3, d12, d2
	fadd	d2, d4, d3
	fmadd	d2, d4, d2, d12
	fsub	d3, d3, d4
	fmsub	d3, d4, d3, d12
	fadd	d4, d16, d5
	fmadd	d4, d16, d4, d12
	fsub	d5, d5, d16
	fmsub	d5, d16, d5, d12
	fmov	d6, #-1.00000000
	fmadd	d6, d16, d16, d6
	fadd	d6, d6, d6
	fdiv	d7, d12, d7
	ldp	d29, d24, [x21, #144]
	ldp	d12, d10, [x21, #168]
	ldp	d28, d21, [x21, #192]
	ldp	d27, d20, [x21, #216]
	ldp	d25, d19, [x21, #240]
	ldp	d23, d18, [x21, #264]
	ldp	d22, d17, [x21, #288]
	ldp	d26, d16, [x21, #312]
LBB0_2:
	ldr	s30, [x25, x8]
	fmul	d29, d6, d29
	fcvt	d30, s30
	ldr	d31, [sp, #240]
	fmadd	d31, d31, d24, d29
	fmsub	d30, d7, d31, d30
	str	d30, [x21, #136]
	fmadd	d29, d4, d30, d29
	ldr	d30, [sp, #248]
	fmul	d30, d30, d12
	fmadd	d24, d5, d24, d29
	ldr	d29, [sp, #232]
	fmadd	d29, d29, d10, d30
	fmul	d29, d11, d29
	fnmsub	d24, d7, d24, d29
	str	d24, [x21, #160]
	ldr	d29, [sp, #256]
	fmul	d28, d29, d28
	ldp	d29, d31, [sp, #216]
	fmadd	d24, d31, d24, d30
	fmadd	d24, d29, d10, d24
	ldr	d29, [sp, #208]
	fmadd	d29, d29, d21, d28
	fmul	d29, d9, d29
	fnmsub	d24, d11, d24, d29
	str	d24, [x21, #184]
	ldr	d29, [sp, #264]
	fmul	d27, d29, d27
	ldr	d29, [sp, #200]
	fmadd	d24, d29, d24, d28
	ldr	d28, [sp, #192]
	fmadd	d21, d28, d21, d24
	ldr	d24, [sp, #184]
	fmadd	d24, d24, d20, d27
	fmul	d24, d8, d24
	fnmsub	d21, d9, d21, d24
	str	d21, [x21, #208]
	ldr	d24, [sp, #272]
	fmul	d24, d24, d25
	ldp	d25, d28, [sp, #168]
	fmadd	d21, d28, d21, d27
	fmadd	d20, d25, d20, d21
	ldr	d21, [sp, #160]
	fmadd	d21, d21, d19, d24
	fmul	d21, d15, d21
	fnmsub	d20, d8, d20, d21
	str	d20, [x21, #232]
	ldr	d21, [sp, #280]
	fmul	d21, d21, d23
	ldp	d23, d25, [sp, #144]
	fmadd	d20, d25, d20, d24
	fmadd	d19, d23, d19, d20
	ldr	d20, [sp, #136]
	fmadd	d20, d20, d18, d21
	fmul	d20, d13, d20
	fnmsub	d19, d15, d19, d20
	str	d19, [x21, #256]
	ldr	d20, [sp, #288]
	fmul	d20, d20, d22
	ldr	d22, [sp, #128]
	fmadd	d19, d22, d19, d21
	ldr	d21, [sp, #120]
	fmadd	d18, d21, d18, d19
	ldp	d21, d19, [sp, #104]
	fmadd	d19, d19, d17, d20
	fmul	d19, d14, d19
	fnmsub	d18, d13, d18, d19
	str	d18, [x21, #280]
	ldp	d19, d23, [sp, #296]
	fmul	d19, d19, d26
	fmadd	d18, d21, d18, d20
	ldr	d20, [sp, #96]
	fmadd	d17, d20, d17, d18
	ldr	d18, [sp, #88]
	fmadd	d18, d18, d16, d19
	fmul	d18, d23, d18
	fnmsub	d17, d14, d17, d18
	str	d17, [x21, #304]
	ldp	d18, d20, [x21, #336]
	ldp	d21, d22, [sp, #312]
	fmul	d18, d21, d18
	ldr	d21, [sp, #80]
	fmadd	d17, d21, d17, d19
	ldr	d19, [sp, #72]
	fmadd	d16, d19, d16, d17
	ldr	d17, [sp, #64]
	fmadd	d17, d17, d20, d18
	fmul	d17, d22, d17
	fnmsub	d16, d23, d16, d17
	str	d16, [x21, #328]
	ldp	d17, d19, [x21, #360]
	ldr	d21, [sp, #328]
	fmul	d17, d21, d17
	ldr	d21, [sp, #56]
	fmadd	d16, d21, d16, d18
	fmadd	d16, d0, d20, d16
	fmadd	d18, d1, d19, d17
	ldr	d20, [sp, #336]
	fmul	d18, d20, d18
	fnmsub	d16, d22, d16, d18
	str	d16, [x21, #352]
	fmadd	d16, d2, d16, d17
	fmadd	d16, d3, d19, d16
	fmul	d16, d20, d16
	fcvt	s16, d16
	str	s16, [x26, x8]
	ldr	d24, [x21, #144]
	ldur	q29, [x21, #136]
	str	q29, [x21, #144]
	ldr	d10, [x21, #168]
	ldr	q12, [x21, #160]
	stur	q12, [x21, #168]
	ldr	d21, [x21, #192]
	ldur	q28, [x21, #184]
	str	q28, [x21, #192]
	ldr	d20, [x21, #216]
	ldr	q27, [x21, #208]
	stur	q27, [x21, #216]
	ldr	d19, [x21, #240]
	ldur	q25, [x21, #232]
	str	q25, [x21, #240]
	ldr	d18, [x21, #264]
	ldr	q23, [x21, #256]
	str	q23, [x22]
	ldr	d17, [x21, #288]
	ldr	q22, [x22, #16]
	str	q22, [x21, #288]
	ldr	d16, [x21, #312]
	ldr	q26, [x22, #64]
	str	q26, [x21, #336]
	ldr	q26, [x21, #352]
	str	q26, [x22, #96]
	ldr	q26, [x21, #304]
	str	q26, [x22, #48]
	add	x8, x8, #4
	cmp	x8, #2048
	b.ne	LBB0_2
	;MEMBARRIER
	sub	w8, w24, #1
	cbnz	w24, LBB0_1
	add	sp, sp, #352
	ldp	x29, x30, [sp, #144]
	ldp	x20, x19, [sp, #128]
	ldp	x22, x21, [sp, #112]
	ldp	x24, x23, [sp, #96]
	ldp	x26, x25, [sp, #80]
	ldp	x28, x27, [sp, #64]
	ldp	d9, d8, [sp, #48]
	ldp	d11, d10, [sp, #32]
	ldp	d13, d12, [sp, #16]
	ldp	d15, d14, [sp], #160
	ret

	.p2align	2
_main_closure_0:
	.cfi_startproc
	b	_KGEN_CompilerRT_AsyncRT_GetOrCreateCPUDevice
	.cfi_endproc

	.p2align	2
_main_closure_1:
	.cfi_startproc
	b	_KGEN_CompilerRT_AsyncRT_ReleaseCPUDevice
	.cfi_endproc

	.section	__TEXT,__literal16,16byte_literals
	.p2align	4, 0x0
lCPI3_0:
	.long	0x461c4000
	.long	0x00000000
	.long	0x42480000
	.long	0x460ca000
lCPI3_1:
	.long	0x00000000
	.long	0x42480000
	.long	0x45fa0000
	.long	0x00000000
lCPI3_2:
	.long	0x42480000
	.long	0x45dac000
	.long	0x00000000
	.long	0x42480000
lCPI3_3:
	.long	0x45bb8000
	.long	0x00000000
	.long	0x42480000
	.long	0x459c4000
lCPI3_4:
	.long	0x00000000
	.long	0x42480000
	.long	0x457a0000
	.long	0x00000000
lCPI3_5:
	.long	0x42480000
	.long	0x453b8000
	.long	0x00000000
	.long	0x42480000
lCPI3_6:
	.long	0x44fa0000
	.long	0x00000000
	.long	0x42480000
	.long	0x447a0000
lCPI3_7:
	.quad	37
	.quad	2305843009213693952
lCPI3_8:
	.quad	1
	.quad	2305843009213693952
lCPI3_9:
	.quad	2
	.quad	2305843009213693952
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	2
_main:
	.cfi_startproc
	sub	sp, sp, #160
	stp	x20, x19, [sp, #128]
	stp	x29, x30, [sp, #144]
	.cfi_def_cfa_offset 160
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x1
	mov	x20, x0
	bl	_KGEN_CompilerRT_AsyncRT_GetCurrentCPUDevice
	cbnz	x0, LBB3_2
Lloh0:
	adrp	x0, _static_string_a61c3395ab9379d9@PAGE
Lloh1:
	add	x0, x0, _static_string_a61c3395ab9379d9@PAGEOFF
Lloh2:
	adrp	x2, _main_closure_0@GOTPAGE
Lloh3:
	ldr	x2, [x2, _main_closure_0@GOTPAGEOFF]
Lloh4:
	adrp	x3, _main_closure_1@GOTPAGE
Lloh5:
	ldr	x3, [x3, _main_closure_1@GOTPAGEOFF]
	mov	w1, #7
	bl	_KGEN_CompilerRT_GetOrCreateGlobal
LBB3_2:
	mov	x0, x20
	mov	x1, x19
	bl	_KGEN_CompilerRT_SetArgV
	bl	_KGEN_CompilerRT_PrintStackTraceOnFault
	mov	w0, #8
	mov	w1, #376
	bl	_KGEN_CompilerRT_AlignedAlloc
	cbz	x0, LBB3_7
	mov	x19, x0
	mov	x8, #130841883705344
	movk	x8, #1, lsl #48
	mov	x9, #41260
	movk	x9, #52999, lsl #16
	movk	x9, #10307, lsl #32
	movk	x9, #16129, lsl #48
	stp	x8, x9, [x0]
Lloh6:
	adrp	x8, lCPI3_0@PAGE
Lloh7:
	ldr	q0, [x8, lCPI3_0@PAGEOFF]
Lloh8:
	adrp	x8, lCPI3_1@PAGE
Lloh9:
	ldr	q1, [x8, lCPI3_1@PAGEOFF]
	stp	q0, q1, [x0, #16]
Lloh10:
	adrp	x8, lCPI3_2@PAGE
Lloh11:
	ldr	q0, [x8, lCPI3_2@PAGEOFF]
Lloh12:
	adrp	x8, lCPI3_3@PAGE
Lloh13:
	ldr	q1, [x8, lCPI3_3@PAGEOFF]
	stp	q0, q1, [x0, #48]
Lloh14:
	adrp	x8, lCPI3_4@PAGE
Lloh15:
	ldr	q0, [x8, lCPI3_4@PAGEOFF]
Lloh16:
	adrp	x8, lCPI3_5@PAGE
Lloh17:
	ldr	q1, [x8, lCPI3_5@PAGEOFF]
	stp	q0, q1, [x0, #80]
Lloh18:
	adrp	x8, lCPI3_6@PAGE
Lloh19:
	ldr	q0, [x8, lCPI3_6@PAGEOFF]
	str	q0, [x0, #112]
	mov	x8, #4776067404826411008
	str	x8, [x0, #128]
	movi.2d	v0, #0000000000000000
	stur	q0, [x0, #152]
	stur	q0, [x0, #168]
	stur	q0, [x0, #184]
	stur	q0, [x0, #200]
	stur	q0, [x0, #216]
	stur	q0, [x0, #232]
	stur	q0, [x0, #248]
	mov	x8, x0
	str	q0, [x8, #136]!
	stp	q0, q0, [x8, #128]
	stp	q0, q0, [x8, #160]
	stp	q0, q0, [x8, #192]
	str	q0, [x8, #224]
	mov	w0, #16
	mov	w1, #4112
	bl	_KGEN_CompilerRT_AlignedAlloc
	cbz	x0, LBB3_7
	mov	x8, #0
	add	x9, x0, #16
LBB3_5:
	str	x9, [x0, x8]
	add	x9, x9, #2048
	add	x8, x8, #8
	cmp	x8, #16
	b.ne	LBB3_5
	mov	x20, x0
	add	x0, x0, #16
	mov	w1, #4096
	bl	_bzero
	add	x2, x20, #4
	mov	x0, x19
	mov	x1, x20
	bl	_inspect_compute
	mov	x0, x20
	bl	_KGEN_CompilerRT_AlignedFree
	mov	x0, x19
	bl	_KGEN_CompilerRT_AlignedFree
	bl	_KGEN_CompilerRT_DestroyGlobals
	mov	w0, #0
	ldp	x29, x30, [sp, #144]
	ldp	x20, x19, [sp, #128]
	add	sp, sp, #160
	ret
LBB3_7:
Lloh20:
	adrp	x8, _static_string_09e773a88105e290@PAGE
Lloh21:
	add	x9, x8, _static_string_09e773a88105e290@PAGEOFF
Lloh22:
	adrp	x8, lCPI3_7@PAGE
Lloh23:
	ldr	q0, [x8, lCPI3_7@PAGEOFF]
	stur	q0, [sp, #64]
Lloh24:
	adrp	x8, _static_string_a8d4ace0dc8d360e@PAGE
Lloh25:
	add	x8, x8, _static_string_a8d4ace0dc8d360e@PAGEOFF
	str	x8, [sp, #80]
Lloh26:
	adrp	x8, lCPI3_8@PAGE
Lloh27:
	ldr	q0, [x8, lCPI3_8@PAGEOFF]
	stur	q0, [sp, #88]
Lloh28:
	adrp	x8, _static_string_7f1562353e292282@PAGE
Lloh29:
	add	x8, x8, _static_string_7f1562353e292282@PAGEOFF
	str	x8, [sp, #104]
Lloh30:
	adrp	x8, lCPI3_9@PAGE
Lloh31:
	ldr	q0, [x8, lCPI3_9@PAGEOFF]
	stur	q0, [sp, #112]
	mov	w8, #1
	stp	x8, x9, [sp, #48]
	strb	w8, [sp, #40]
	str	x8, [sp, #32]
Lloh32:
	adrp	x8, _static_string_bbe01a6a523daf15@PAGE
Lloh33:
	add	x8, x8, _static_string_bbe01a6a523daf15@PAGEOFF
	stp	xzr, x8, [sp, #16]
Lloh34:
	adrp	x8, _static_string_c44bdff4074eecdb@PAGE
Lloh35:
	add	x8, x8, _static_string_c44bdff4074eecdb@PAGEOFF
	add	x9, sp, #56
Lloh36:
	adrp	x0, _static_string_31203c1a2bdb78cc@PAGE
Lloh37:
	add	x0, x0, _static_string_31203c1a2bdb78cc@PAGEOFF
Lloh38:
	adrp	x5, _static_string_e076905c259bf94f@PAGE
Lloh39:
	add	x5, x5, _static_string_e076905c259bf94f@PAGEOFF
	add	x2, sp, #80
	add	x7, sp, #104
	stp	x9, x8, [sp]
	mov	w1, #6
	mov	w3, #233
	mov	w4, #14
	mov	w6, #54
	bl	"_std::io::io::print[KGENParamList[::Writable],*::Writable,LITImmutOrigin,::Origin[::Bool(False), $2]](*$0,sep:::StringSlice[::Bool(False), StaticConstantOrigin, *?],end:::StringSlice[::Bool(False), StaticConstantOrigin, *?],flush:::Bool,file:::FileDescriptor$),Ts.values`=[[typevalue<#kgen.instref<\"std::collections::string::string_slice::StringSlice,mut=false,origin._mlir_origin`={  },origin={  }\">>, struct<(pointer<none>, index)>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>], [typevalue<#kgen.instref<\"std::reflection::location::SourceLocation\">>, struct<(index, index, struct<(pointer<none>, index)>)>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>]]"
	ldrb	w8, [sp, #127]
	tbz	w8, #6, LBB3_10
	ldr	x8, [sp, #104]
	sub	x0, x8, #8
	mov	x8, #-1
	ldaddal	x8, x8, [x0]
	cmp	x8, #1
	b.ne	LBB3_10
	dmb	ishld
	bl	_KGEN_CompilerRT_AlignedFree
LBB3_10:
	ldrb	w8, [sp, #103]
	tbz	w8, #6, LBB3_13
	ldr	x8, [sp, #80]
	sub	x0, x8, #8
	mov	x8, #-1
	ldaddal	x8, x8, [x0]
	cmp	x8, #1
	b.ne	LBB3_13
	dmb	ishld
	bl	_KGEN_CompilerRT_AlignedFree
LBB3_13:
	brk	#0x1
	.loh AdrpLdrGot	Lloh4, Lloh5
	.loh AdrpLdrGot	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpLdr	Lloh18, Lloh19
	.loh AdrpAdrp	Lloh16, Lloh18
	.loh AdrpLdr	Lloh16, Lloh17
	.loh AdrpAdrp	Lloh14, Lloh16
	.loh AdrpLdr	Lloh14, Lloh15
	.loh AdrpAdrp	Lloh12, Lloh14
	.loh AdrpLdr	Lloh12, Lloh13
	.loh AdrpAdrp	Lloh10, Lloh12
	.loh AdrpLdr	Lloh10, Lloh11
	.loh AdrpAdrp	Lloh8, Lloh10
	.loh AdrpLdr	Lloh8, Lloh9
	.loh AdrpAdrp	Lloh6, Lloh8
	.loh AdrpLdr	Lloh6, Lloh7
	.loh AdrpAdd	Lloh38, Lloh39
	.loh AdrpAdd	Lloh36, Lloh37
	.loh AdrpAdd	Lloh34, Lloh35
	.loh AdrpAdd	Lloh32, Lloh33
	.loh AdrpLdr	Lloh30, Lloh31
	.loh AdrpAdd	Lloh28, Lloh29
	.loh AdrpAdrp	Lloh26, Lloh28
	.loh AdrpLdr	Lloh26, Lloh27
	.loh AdrpAdd	Lloh24, Lloh25
	.loh AdrpAdrp	Lloh22, Lloh24
	.loh AdrpLdr	Lloh22, Lloh23
	.loh AdrpAdrp	Lloh20, Lloh22
	.loh AdrpAdd	Lloh20, Lloh21
	.cfi_endproc

	.p2align	2
"_std::builtin::simd::SIMD::write_to[::Writer](::SIMD[$0, $1],$2&),dtype=si64,size=1,writer.T`2x=[typevalue<#kgen.instref<\"std::format::_utils::_WriteBufferStack,origin._mlir_origin`={  },origin={  },W=[typevalue<#kgen.instref<\\1B\\22std::io::file_descriptor::FileDescriptor\\22>>, index],stack_buffer_bytes=4096\">>, struct<(struct<(array<4096, scalar<ui8>>) memoryOnly>, index, pointer<index>) memoryOnly>]":
	.cfi_startproc
	sub	sp, sp, #144
	stp	x24, x23, [sp, #80]
	stp	x22, x21, [sp, #96]
	stp	x20, x19, [sp, #112]
	stp	x29, x30, [sp, #128]
	.cfi_def_cfa_offset 144
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	mov	x19, x1
	mov	x20, x0
	tbnz	x0, #63, LBB4_3
	ldr	x2, [x19, #4096]
	cmp	x2, #1, lsl #12
	b.le	LBB4_9
	ldr	x8, [x19, #4104]
	ldr	x0, [x8]
	mov	x1, x19
	bl	_write
	mov	x2, #0
	str	xzr, [x19, #4096]
	cbnz	x20, LBB4_10
	b	LBB4_23
LBB4_3:
	ldr	x2, [x19, #4096]
	add	x8, x2, #1
	cmp	x8, #1, lsl #12
	b.le	LBB4_5
	ldr	x8, [x19, #4104]
	ldr	x0, [x8]
	mov	x1, x19
	bl	_write
	mov	x2, #0
	str	xzr, [x19, #4096]
LBB4_5:
	mov	w8, #45
	strb	w8, [x19, x2]
	ldr	x8, [x19, #4096]
	add	x2, x8, #1
	str	x2, [x19, #4096]
	cmp	x2, #1, lsl #12
	b.le	LBB4_7
	ldr	x8, [x19, #4104]
	ldr	x0, [x8]
	mov	x1, x19
	bl	_write
	mov	x2, #0
	str	xzr, [x19, #4096]
LBB4_7:
	strb	wzr, [sp, #79]
	mov	w8, #63
	mov	x9, #-7378697629483820647
	mov	x10, #-10
	add	x11, sp, #15
Lloh40:
	adrp	x12, _static_string_978d8d34847e5196@PAGE
Lloh41:
	add	x12, x12, _static_string_978d8d34847e5196@PAGEOFF
LBB4_8:
	smulh	x13, x20, x9
	asr	x14, x13, #2
	add	x13, x14, x13, lsr #63
	mul	x14, x13, x10
	cmn	x20, #1
	cset	w15, gt
	subs	x14, x20, x14
	cset	w16, ne
	ands	w15, w15, w16
	csel	x16, x10, xzr, ne
	adds	x14, x14, x16
	cneg	x14, x14, mi
	ldrb	w14, [x12, x14]
	strb	w14, [x11, x8]
	sub	x8, x8, #1
	subs	x20, x15, x13
	b.ne	LBB4_8
	b	LBB4_12
LBB4_9:
	cbz	x20, LBB4_21
LBB4_10:
	strb	wzr, [sp, #79]
	mov	w8, #63
	mov	x9, #-3689348814741910324
	movk	x9, #52429
	mov	x10, #-10
	add	x11, sp, #15
Lloh42:
	adrp	x12, _static_string_978d8d34847e5196@PAGE
Lloh43:
	add	x12, x12, _static_string_978d8d34847e5196@PAGEOFF
LBB4_11:
	mov	x13, x20
	umulh	x14, x20, x9
	lsr	x20, x14, #3
	madd	x14, x20, x10, x12
	ldrb	w14, [x14, x13]
	strb	w14, [x11, x8]
	sub	x8, x8, #1
	cmp	x13, #10
	b.hs	LBB4_11
LBB4_12:
	add	x9, x8, #1
	add	x10, x8, #66
	bic	x10, x10, x10, asr #63
	cmp	x9, #65
	mov	w11, #65
	csinc	x8, x11, x8, ge
	cmp	x9, #0
	csel	x23, x10, x8, mi
	add	x8, sp, #15
	add	x21, x8, x23
	mov	w8, #64
	sub	x20, x8, x23
	cmp	x20, #1, lsl #12
	b.le	LBB4_14
	ldr	x8, [x19, #4104]
	ldr	x0, [x8]
	mov	x1, x19
	bl	_write
	str	xzr, [x19, #4096]
	ldr	x8, [x19, #4104]
	ldr	x0, [x8]
	mov	x1, x21
	mov	x2, x20
	bl	_write
	ldp	x29, x30, [sp, #128]
	ldp	x20, x19, [sp, #112]
	ldp	x22, x21, [sp, #96]
	ldp	x24, x23, [sp, #80]
	add	sp, sp, #144
	ret
LBB4_14:
	add	x8, x20, x2
	cmp	x8, #1, lsl #12
	b.le	LBB4_16
	ldr	x8, [x19, #4104]
	ldr	x0, [x8]
	mov	x1, x19
	bl	_write
	mov	x2, #0
	str	xzr, [x19, #4096]
LBB4_16:
	cmp	x23, #64
	b.ne	LBB4_18
LBB4_17:
	ldr	x8, [x19, #4096]
	add	x8, x8, x20
	b	LBB4_24
LBB4_18:
	add	x22, x19, x2
	cmp	x20, #4
	b.gt	LBB4_25
	mov	w8, #63
	sub	x8, x8, x23
	ldrb	w9, [x21]
	strb	w9, [x22]
	ldrb	w9, [sp, #78]
	strb	w9, [x22, x8]
	cmp	x20, #3
	b.lt	LBB4_17
	mov	w8, #62
	sub	x8, x8, x23
	ldrb	w9, [x21, #1]
	strb	w9, [x22, #1]
	ldrb	w9, [sp, #77]
	strb	w9, [x22, x8]
	b	LBB4_17
LBB4_21:
	cmp	x2, #1, lsl #12
	b.ne	LBB4_23
	ldr	x8, [x19, #4104]
	ldr	x0, [x8]
	mov	x1, x19
	bl	_write
	mov	x2, #0
	str	xzr, [x19, #4096]
LBB4_23:
	mov	w8, #48
	strb	w8, [x19, x2]
	ldr	x8, [x19, #4096]
	add	x8, x8, #1
LBB4_24:
	str	x8, [x19, #4096]
	ldp	x29, x30, [sp, #128]
	ldp	x20, x19, [sp, #112]
	ldp	x22, x21, [sp, #96]
	ldp	x24, x23, [sp, #80]
	add	sp, sp, #144
	ret
LBB4_25:
	cmp	x20, #16
	b.gt	LBB4_28
	add	x8, x22, x20
	cmp	x20, #8
	b.lt	LBB4_32
	ldr	x9, [x21]
	str	x9, [x22]
	ldur	x9, [sp, #71]
	stur	x9, [x8, #-8]
	b	LBB4_17
LBB4_28:
	ands	x23, x20, #0x7fffffffffffffe0
	b.eq	LBB4_30
	mov	x0, x22
	mov	x1, x21
	mov	x2, x23
	bl	_memcpy
LBB4_30:
	cmp	x23, x20
	b.eq	LBB4_17
	add	x0, x22, x23
	add	x1, x21, x23
	and	x2, x20, #0x1f
	bl	_memcpy
	b	LBB4_17
LBB4_32:
	ldr	w9, [x21]
	str	w9, [x22]
	ldur	w9, [sp, #75]
	stur	w9, [x8, #-4]
	b	LBB4_17
	.loh AdrpAdd	Lloh40, Lloh41
	.loh AdrpAdd	Lloh42, Lloh43
	.cfi_endproc

	.p2align	2
"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false":
	.cfi_startproc
	stp	x24, x23, [sp, #-64]!
	stp	x22, x21, [sp, #16]
	stp	x20, x19, [sp, #32]
	stp	x29, x30, [sp, #48]
	.cfi_def_cfa_offset 64
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	mov	x19, x2
	mov	x21, x1
	mov	x20, x0
	cmp	x2, #1, lsl #12
	b.le	LBB5_2
	ldr	x8, [x20, #4104]
	ldr	x2, [x20, #4096]
	ldr	x0, [x8]
	mov	x1, x20
	bl	_write
	str	xzr, [x20, #4096]
	ldr	x8, [x20, #4104]
	ldr	x0, [x8]
	mov	x1, x21
	mov	x2, x19
	ldp	x29, x30, [sp, #48]
	ldp	x20, x19, [sp, #32]
	ldp	x22, x21, [sp, #16]
	ldp	x24, x23, [sp], #64
	b	_write
LBB5_2:
	ldr	x2, [x20, #4096]
	add	x8, x2, x19
	cmp	x8, #1, lsl #12
	b.le	LBB5_4
	ldr	x8, [x20, #4104]
	ldr	x0, [x8]
	mov	x1, x20
	bl	_write
	mov	x2, #0
	str	xzr, [x20, #4096]
LBB5_4:
	cbz	x19, LBB5_16
	add	x8, x20, x2
	cmp	x19, #4
	b.gt	LBB5_8
	sub	x9, x19, #1
	ldrb	w10, [x21]
	strb	w10, [x8]
	ldrb	w10, [x21, x9]
	strb	w10, [x8, x9]
	cmp	x19, #3
	b.lt	LBB5_16
	sub	x9, x19, #2
	ldrb	w10, [x21, #1]
	strb	w10, [x8, #1]
	ldrb	w10, [x21, x9]
	strb	w10, [x8, x9]
	b	LBB5_16
LBB5_8:
	cmp	x19, #16
	b.gt	LBB5_11
	add	x9, x8, x19
	add	x10, x21, x19
	cmp	x19, #8
	b.lt	LBB5_15
	ldr	x11, [x21]
	str	x11, [x8]
	ldur	x8, [x10, #-8]
	stur	x8, [x9, #-8]
	b	LBB5_16
LBB5_11:
	ands	x22, x19, #0x7fffffffffffffe0
	b.eq	LBB5_13
	add	x0, x20, x2
	mov	x23, x2
	and	x2, x19, #0x7fffffffffffffe0
	mov	x1, x21
	bl	_memcpy
	mov	x2, x23
LBB5_13:
	cmp	x22, x19
	b.eq	LBB5_16
	add	x8, x20, x2
	add	x0, x8, x22
	add	x1, x21, x22
	and	x2, x19, #0x1f
	bl	_memcpy
	b	LBB5_16
LBB5_15:
	ldr	w11, [x21]
	str	w11, [x8]
	ldur	w8, [x10, #-4]
	stur	w8, [x9, #-4]
LBB5_16:
	ldr	x8, [x20, #4096]
	add	x8, x8, x19
	str	x8, [x20, #4096]
	ldp	x29, x30, [sp, #48]
	ldp	x20, x19, [sp, #32]
	ldp	x22, x21, [sp, #16]
	ldp	x24, x23, [sp], #64
	ret
	.cfi_endproc

	.p2align	2
"_std::io::io::_flush(::FileDescriptor)":
	.cfi_startproc
	stp	x20, x19, [sp, #-32]!
	stp	x29, x30, [sp, #16]
	.cfi_def_cfa_offset 32
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	bl	_dup
Lloh44:
	adrp	x1, _static_string_0d78baac08237ddb@PAGE
Lloh45:
	add	x1, x1, _static_string_0d78baac08237ddb@PAGEOFF
	bl	_fdopen
	mov	x19, x0
	bl	_fflush
	mov	x0, x19
	ldp	x29, x30, [sp, #16]
	ldp	x20, x19, [sp], #32
	b	_fclose
	.loh AdrpAdd	Lloh44, Lloh45
	.cfi_endproc

	.p2align	2
"_std::io::io::print[KGENParamList[::Writable],*::Writable,LITImmutOrigin,::Origin[::Bool(False), $2]](*$0,sep:::StringSlice[::Bool(False), StaticConstantOrigin, *?],end:::StringSlice[::Bool(False), StaticConstantOrigin, *?],flush:::Bool,file:::FileDescriptor$),Ts.values`=[[typevalue<#kgen.instref<\"std::collections::string::string_slice::StringSlice,mut=false,origin._mlir_origin`={  },origin={  }\">>, struct<(pointer<none>, index)>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>], [typevalue<#kgen.instref<\"std::reflection::location::SourceLocation\">>, struct<(index, index, struct<(pointer<none>, index)>)>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>]]":
	.cfi_startproc
	stp	x28, x27, [sp, #-96]!
	stp	x26, x25, [sp, #16]
	stp	x24, x23, [sp, #32]
	stp	x22, x21, [sp, #48]
	stp	x20, x19, [sp, #64]
	stp	x29, x30, [sp, #80]
	sub	sp, sp, #1, lsl #12
	sub	sp, sp, #64
	.cfi_def_cfa_offset 4256
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	.cfi_offset w25, -72
	.cfi_offset w26, -80
	.cfi_offset w27, -88
	.cfi_offset w28, -96
	mov	x22, x7
	mov	x27, x6
	mov	x28, x5
	mov	x25, x4
	mov	x26, x3
	mov	x19, x2
	mov	x2, x1
	mov	x1, x0
	ldr	x9, [sp, #4288]
	ldr	x8, [sp, #4280]
	stp	x8, x9, [sp, #16]
	ldr	x23, [sp, #4272]
	add	x8, sp, #201
	ldrb	w8, [x8, #4095]
	str	w8, [sp, #36]
	ldr	x24, [sp, #4264]
	ldr	x21, [sp, #4256]
	ldr	x8, [sp, #4304]
	str	x8, [sp, #40]
	str	xzr, [sp, #4144]
	add	x8, sp, #40
	str	x8, [sp, #4152]
	add	x0, sp, #48
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	add	x0, sp, #48
	mov	x1, x24
	mov	x2, x23
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	ldr	x8, [x19, #16]
	tbnz	x8, #63, LBB7_2
	ldp	x19, x2, [x19]
	b	LBB7_3
LBB7_2:
	ubfx	x2, x8, #56, #5
LBB7_3:
	add	x20, sp, #48
	add	x0, sp, #48
	mov	x1, x19
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	add	x0, sp, #48
	mov	x1, x24
	mov	x2, x23
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	add	x0, sp, #48
	mov	x1, x28
	mov	x2, x27
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	ldr	x2, [sp, #4144]
	add	x8, x2, #1
	cmp	x8, #1, lsl #12
	b.le	LBB7_5
	ldr	x8, [sp, #4152]
	ldr	x0, [x8]
	add	x1, sp, #48
	bl	_write
	mov	x2, #0
	str	xzr, [sp, #4144]
LBB7_5:
	mov	w19, #58
	strb	w19, [x20, x2]
	ldr	x8, [sp, #4144]
	add	x8, x8, #1
	str	x8, [sp, #4144]
	add	x1, sp, #48
	mov	x0, x26
	bl	"_std::builtin::simd::SIMD::write_to[::Writer](::SIMD[$0, $1],$2&),dtype=si64,size=1,writer.T`2x=[typevalue<#kgen.instref<\"std::format::_utils::_WriteBufferStack,origin._mlir_origin`={  },origin={  },W=[typevalue<#kgen.instref<\\1B\\22std::io::file_descriptor::FileDescriptor\\22>>, index],stack_buffer_bytes=4096\">>, struct<(struct<(array<4096, scalar<ui8>>) memoryOnly>, index, pointer<index>) memoryOnly>]"
	ldr	x2, [sp, #4144]
	add	x8, x2, #1
	cmp	x8, #1, lsl #12
	b.le	LBB7_7
	ldr	x8, [sp, #4152]
	ldr	x0, [x8]
	add	x1, sp, #48
	bl	_write
	mov	x2, #0
	str	xzr, [sp, #4144]
LBB7_7:
	add	x8, sp, #48
	strb	w19, [x8, x2]
	ldr	x8, [sp, #4144]
	add	x8, x8, #1
	str	x8, [sp, #4144]
	add	x1, sp, #48
	mov	x0, x25
	bl	"_std::builtin::simd::SIMD::write_to[::Writer](::SIMD[$0, $1],$2&),dtype=si64,size=1,writer.T`2x=[typevalue<#kgen.instref<\"std::format::_utils::_WriteBufferStack,origin._mlir_origin`={  },origin={  },W=[typevalue<#kgen.instref<\\1B\\22std::io::file_descriptor::FileDescriptor\\22>>, index],stack_buffer_bytes=4096\">>, struct<(struct<(array<4096, scalar<ui8>>) memoryOnly>, index, pointer<index>) memoryOnly>]"
	add	x0, sp, #48
	mov	x1, x24
	mov	x2, x23
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	ldr	x8, [x22, #16]
	tbnz	x8, #63, LBB7_9
	ldp	x22, x2, [x22]
	b	LBB7_10
LBB7_9:
	ubfx	x2, x8, #56, #5
LBB7_10:
	add	x0, sp, #48
	mov	x1, x22
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	add	x0, sp, #48
	mov	x1, x24
	mov	x2, x23
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	ldr	x8, [x21, #16]
	tbnz	x8, #63, LBB7_12
	ldp	x21, x2, [x21]
	b	LBB7_13
LBB7_12:
	ubfx	x2, x8, #56, #5
LBB7_13:
	add	x0, sp, #48
	mov	x1, x21
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	add	x0, sp, #48
	ldp	x1, x2, [sp, #16]
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=false"
	ldr	x8, [sp, #4152]
	ldr	x2, [sp, #4144]
	ldr	x0, [x8]
	add	x1, sp, #48
	bl	_write
	ldr	w8, [sp, #36]
	tbz	w8, #0, LBB7_15
	ldr	x0, [sp, #40]
	add	sp, sp, #1, lsl #12
	add	sp, sp, #64
	ldp	x29, x30, [sp, #80]
	ldp	x20, x19, [sp, #64]
	ldp	x22, x21, [sp, #48]
	ldp	x24, x23, [sp, #32]
	ldp	x26, x25, [sp, #16]
	ldp	x28, x27, [sp], #96
	b	"_std::io::io::_flush(::FileDescriptor)"
LBB7_15:
	add	sp, sp, #1, lsl #12
	add	sp, sp, #64
	ldp	x29, x30, [sp, #80]
	ldp	x20, x19, [sp, #64]
	ldp	x22, x21, [sp, #48]
	ldp	x24, x23, [sp, #32]
	ldp	x26, x25, [sp, #16]
	ldp	x28, x27, [sp], #96
	ret
	.cfi_endproc

	.p2align	6
"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f64,size=1\">>, scalar<f64>]":
	fmov	x8, d0
	mov	x9, #4602678819172646912
	bfxil	x9, x8, #0, #52
	fmov	d3, x9
	mov	x9, #15309
	movk	x9, #26239, lsl #16
	movk	x9, #41118, lsl #32
	movk	x9, #16358, lsl #48
	fmov	d2, x9
	mov	x9, #-9223372036854775808
	fmov	d4, x9
	.p2align	6, , 4
	fcmp	d3, d2
	fcsel	d4, d3, d4, lt
	mov	x9, #-1022
	mov	x10, #-1023
	csel	x9, x10, x9, lt
	fmov	d2, #1.00000000
	fcmp	d1, d2
	b.pl	LBB8_5
	fcmp	d1, #0.0
	b.pl	LBB8_6
	fneg	d5, d1
	movi.2d	v6, #0000000000000000
	fmov	d7, #-1.00000000
	fmov	x10, d5
	mov	w11, #1075
	subs	x11, x11, x10, lsr #52
	mov	x12, #-1
	lsl	x11, x12, x11
	mov	x12, #9223372036854775807
	csel	x11, x11, x12, hi
	and	x10, x11, x10
	fmov	d5, x10
	.p2align	6, , 4
	fcmp	d1, d7
	fcsel	d5, d6, d5, gt
	fneg	d5, d5
	fcmp	d5, d1
	b.eq	LBB8_8
	b	LBB8_12
LBB8_5:
	fmov	x10, d1
	ubfx	x11, x10, #52, #11
	mov	w12, #1075
	subs	x11, x12, x11
	mov	x12, #-1
	lsl	x11, x12, x11
	csinv	x11, x11, xzr, hi
	and	x10, x11, x10
	fmov	d5, x10
	fcmp	d5, d1
	b.eq	LBB8_8
	b	LBB8_12
LBB8_6:
	b.ne	LBB8_11
	mov.16b	v5, v1
	fcmp	d5, d1
	b.ne	LBB8_12
LBB8_8:
	fcvtzs	w8, d5
	cmp	w8, #0
	cneg	w9, w8, mi
	fmov	d1, #1.00000000
	cmp	w9, #1
	b.lt	LBB8_10
LBB8_9:
	fmul	d3, d0, d2
	tst	w9, #0x1
	fcsel	d2, d2, d3, eq
	fmul	d0, d0, d0
	lsr	w9, w9, #1
	cbnz	w9, LBB8_9
LBB8_10:
	fdiv	d0, d1, d2
	cmp	w8, #0
	fcsel	d0, d0, d2, mi
	ret
LBB8_11:
	movi.2d	v5, #0000000000000000
	fcmp	d5, d1
	b.eq	LBB8_8
LBB8_12:
	fadd	d0, d4, d3
	fmov	d3, #-1.00000000
	mov	x10, #35659
	movk	x10, #2835, lsl #16
	movk	x10, #31287, lsl #32
	movk	x10, #49085, lsl #48
	mov	x11, #9306
	movk	x11, #25157, lsl #16
	movk	x11, #1079, lsl #32
	movk	x11, #16306, lsl #48
	fadd	d0, d0, d3
	fmov	d3, x10
	fmov	d4, x11
	mov	x10, #36504
	movk	x10, #19721, lsl #16
	movk	x10, #58531, lsl #32
	movk	x10, #16317, lsl #48
	fmadd	d3, d0, d4, d3
	fmov	d4, x10
	mov	x10, #60716
	movk	x10, #56179, lsl #16
	movk	x10, #52137, lsl #32
	movk	x10, #49087, lsl #48
	fmadd	d3, d3, d0, d4
	fmov	d4, x10
	mov	x10, #13113
	movk	x10, #54477, lsl #16
	movk	x10, #15671, lsl #32
	movk	x10, #16322, lsl #48
	fmadd	d3, d3, d0, d4
	fmov	d4, x10
	mov	x10, #35515
	movk	x10, #1227, lsl #16
	movk	x10, #21962, lsl #32
	movk	x10, #49093, lsl #48
	fmadd	d3, d3, d0, d4
	fmov	d4, x10
	mov	x10, #48702
	movk	x10, #36623, lsl #16
	movk	x10, #39381, lsl #32
	movk	x10, #16329, lsl #48
	fmadd	d3, d3, d0, d4
	fmov	d4, x10
	mov	x10, #-54509
	movk	x10, #32512, lsl #16
	movk	x10, #49103, lsl #48
	fmadd	d3, d3, d0, d4
	fmov	d4, x10
	mov	x10, #52630
	movk	x10, #15909, lsl #16
	movk	x10, #21845, lsl #32
	movk	x10, #16341, lsl #48
	fmadd	d3, d3, d0, d4
	fmov	d4, x10
	fmul	d5, d0, d0
	fmadd	d3, d3, d0, d4
	fmul	d4, d0, d5
	fmul	d3, d4, d3
	fmov	d4, #-0.50000000
	fmadd	d3, d5, d4, d3
	add	x8, x9, x8, lsr #52
	mov	x9, #14831
	movk	x9, #65274, lsl #16
	movk	x9, #11842, lsl #32
	movk	x9, #16358, lsl #48
	fadd	d0, d0, d3
	scvtf	d3, x8
	fmov	d4, x9
	fmadd	d0, d3, d4, d0
	mov	x8, #8913
	movk	x8, #63963, lsl #16
	movk	x8, #11134, lsl #32
	movk	x8, #16518, lsl #48
	fmul	d0, d1, d0
	fmov	d1, x8
	mov	x8, #22293
	movk	x8, #13978, lsl #16
	movk	x8, #11133, lsl #32
	movk	x8, #49286, lsl #48
	fminnm	d0, d0, d1
	fmov	d1, x8
	mov	x8, #33534
	movk	x8, #25899, lsl #16
	movk	x8, #5447, lsl #32
	movk	x8, #16375, lsl #48
	fmaxnm	d0, d0, d1
	fmov	d1, x8
	fmov	d3, #0.50000000
	fmadd	d1, d0, d1, d3
	mov	x8, #12288
	movk	x8, #65274, lsl #16
	movk	x8, #11842, lsl #32
	movk	x8, #49126, lsl #48
	frintm	d4, d1
	fmov	d5, x8
	mov	x8, #17636
	movk	x8, #26613, lsl #16
	movk	x8, #58949, lsl #32
	movk	x8, #15962, lsl #48
	mov	x9, #55448
	movk	x9, #61432, lsl #16
	movk	x9, #61144, lsl #32
	movk	x9, #15905, lsl #48
	fmadd	d4, d4, d5, d0
	fmov	d5, x8
	fmov	d6, x9
	mov	x8, #40796
	movk	x8, #46968, lsl #16
	movk	x8, #32335, lsl #32
	movk	x8, #16018, lsl #48
	fmadd	d5, d4, d6, d5
	fmov	d6, x8
	mov	x8, #50996
	movk	x8, #42326, lsl #16
	movk	x8, #7651, lsl #32
	movk	x8, #16071, lsl #48
	fmadd	d5, d5, d4, d6
	fmov	d6, x8
	mov	x8, #40986
	movk	x8, #6657, lsl #16
	movk	x8, #416, lsl #32
	movk	x8, #16122, lsl #48
	fmadd	d5, d5, d4, d6
	fmov	d6, x8
	mov	x8, #40986
	movk	x8, #6657, lsl #16
	movk	x8, #416, lsl #32
	movk	x8, #16170, lsl #48
	fmadd	d5, d5, d4, d6
	fmov	d6, x8
	mov	x8, #27671
	movk	x8, #5825, lsl #16
	movk	x8, #49516, lsl #32
	movk	x8, #16214, lsl #48
	fmadd	d5, d5, d4, d6
	fmov	d6, x8
	mov	x8, #1229782938247303441
	movk	x8, #16257, lsl #48
	fmadd	d5, d5, d4, d6
	fmov	d6, x8
	mov	x8, #6148914691236517205
	movk	x8, #16293, lsl #48
	fmadd	d5, d5, d4, d6
	fmov	d6, x8
	mov	x8, #6148914691236517205
	movk	x8, #16325, lsl #48
	fmadd	d5, d5, d4, d6
	fmov	d6, x8
	fmadd	d5, d5, d4, d6
	fcvtms	x8, d1
	mov	x9, #4607182418800017408
	fmadd	d1, d5, d4, d3
	add	x8, x9, x8, lsl #52
	fmadd	d1, d1, d4, d2
	fmov	d3, x8
	fmadd	d1, d1, d4, d2
	fmul	d1, d1, d3
	fmaxnm	d0, d1, d0
	ret

	.section	__TEXT,__const
	.p2align	4, 0x0
_static_string_e076905c259bf94f:
	.asciz	"oss/modular/mojo/stdlib/std/memory/unsafe_pointer.mojo"

	.p2align	4, 0x0
_static_string_c44bdff4074eecdb:
	.space	1

	.p2align	4, 0x0
_static_string_7f1562353e292282:
	.asciz	": "

	.p2align	4, 0x0
_static_string_a8d4ace0dc8d360e:
	.asciz	" "

	.p2align	4, 0x0
_static_string_31203c1a2bdb78cc:
	.asciz	"ABORT:"

	.p2align	4, 0x0
_static_string_bbe01a6a523daf15:
	.asciz	"\n"

	.p2align	4, 0x0
_static_string_09e773a88105e290:
	.asciz	"alloc failed: returned a null pointer"

	.p2align	4, 0x0
_static_string_a61c3395ab9379d9:
	.asciz	"Runtime"

	.p2align	4, 0x0
_static_string_978d8d34847e5196:
	.asciz	"0123456789abcdefghijklmnopqrstuvwxyz"

	.p2align	4, 0x0
_static_string_0d78baac08237ddb:
	.asciz	"a"

.subsections_via_symbols
