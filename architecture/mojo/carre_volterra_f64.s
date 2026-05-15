	.build_version macos, 26, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_inspect_compute
	.p2align	2

_inspect_compute:
	.cfi_startproc
	sub	sp, sp, #112
	stp	d15, d14, [sp, #48]
	stp	d13, d12, [sp, #64]
	stp	d11, d10, [sp, #80]
	stp	d9, d8, [sp, #96]
	.cfi_def_cfa_offset 112
	.cfi_offset b8, -8
	.cfi_offset b9, -16
	.cfi_offset b10, -24
	.cfi_offset b11, -32
	.cfi_offset b12, -40
	.cfi_offset b13, -48
	.cfi_offset b14, -56
	.cfi_offset b15, -64
	mov	x9, #0
	add	x8, x0, #16, lsl #12
	add	x10, x0, #168
	mov	w11, #32936
	add	x11, x0, x11
	str	x1, [sp, #40]
	add	x12, sp, #40
	; InlineAsm Start
	; InlineAsm End
	str	x2, [sp, #40]
	; InlineAsm Start
	; InlineAsm End
	ldr	x12, [x2]
	ldp	d4, d2, [x0, #24]
	fmul	d0, d2, d4
	fmov	d19, #1.00000000
	fadd	d1, d0, d19
	fdiv	d1, d19, d1
	ldp	d3, d11, [x0, #48]
	fmul	d2, d2, d3
	fmul	d2, d4, d2
	stp	d2, d3, [sp, #24]
	mov	x13, #47479
	movk	x13, #24011, lsl #16
	movk	x13, #29422, lsl #32
	movk	x13, #16439, lsl #48
	fmov	d2, x13
	ldp	d4, d5, [x0, #64]
	fmaxnm	d10, d4, d2
	fdiv	d3, d19, d10
	str	d3, [sp, #16]
	fmul	d6, d5, d10
	ldp	d13, d7, [x0, #104]
	fadd	d4, d4, d7
	fmaxnm	d2, d4, d2
	fdiv	d3, d19, d2
	str	d3, [sp, #8]
	fmul	d16, d5, d2
	ldp	d14, d4, [x0, #144]
	fdiv	d5, d4, d2
	mov	x13, #277076930199552
	movk	x13, #16543, lsl #48
	fmov	d20, x13
	fminnm	d5, d5, d20
	movi.2d	v21, #0000000000000000
	fmaxnm	d5, d5, d21
	fcvtzs	w13, d5
	scvtf	d22, w13
	fsub	d17, d5, d22
	fdiv	d18, d11, d2
	fdiv	d2, d4, d10
	fminnm	d2, d2, d20
	fmaxnm	d2, d2, d21
	fcvtzs	w14, d2
	mvn	w15, w13
	scvtf	d4, w14
	fsub	d20, d19, d2
	fadd	d23, d20, d4
	fsub	d25, d2, d4
	mvn	w16, w14
	fsub	d2, d19, d5
	fadd	d27, d2, d22
	mov	x17, #6148914691236517205
	movk	x17, #16341, lsl #48
	fmov	d2, x17
	ldp	d5, d4, [x8, #224]
	fmul	d8, d4, d2
	ldr	d31, [x0, #88]
	ldr	d30, [x0, #128]
	ldr	w17, [x0, #160]
	ldr	d29, [x8, #176]
	ldr	d28, [x8, #192]
	ldr	d26, [x8, #208]
	ldr	d24, [x8, #248]
	ldr	d22, [x8, #264]
	ldr	d21, [x8, #280]
	ldr	d20, [x8, #296]
	ldr	s2, [x0, #44]
	sshll.2d	v2, v2, #0
	scvtf	d15, d2
	mov	w1, #1
	fmov	d9, #-1.00000000
	mov.16b	v7, v11
	fdiv	d10, d11, d10
LBB0_1:
	fadd	d2, d6, d31
	frintm	d2, d2
	fsub	d2, d31, d2
	fadd	d31, d6, d2
	fadd	d2, d31, d31
	fadd	d2, d2, d9
	mov	w2, #2
	fmov	d11, #1.00000000
LBB0_2:
	fmul	d4, d11, d2
	tst	w2, #0x1
	fcsel	d11, d11, d4, eq
	fmul	d2, d2, d2
	lsr	w2, w2, #1
	cbnz	w2, LBB0_2
	fadd	d2, d16, d30
	frintm	d2, d2
	fsub	d2, d30, d2
	fadd	d30, d16, d2
	fadd	d2, d30, d30
	fadd	d2, d2, d9
	mov	w2, #2
	fmov	d12, #1.00000000
LBB0_4:
	fmul	d4, d12, d2
	tst	w2, #0x1
	fcsel	d12, d12, d4, eq
	fmul	d2, d2, d2
	lsr	w2, w2, #1
	cbnz	w2, LBB0_4
	fsub	d2, d11, d13
	fsub	d4, d12, d14
	fmul	d19, d15, d4
	fmul	d19, d18, d19
	and	w2, w17, #0xfff
	str	d19, [x10, w2, uxtw #3]
	fmul	d19, d15, d2
	fmul	d19, d10, d19
	str	d19, [x11, w2, uxtw #3]
	ldr	d3, [sp, #8]
	fmul	d4, d3, d4
	ldr	d3, [sp, #16]
	fmadd	d2, d3, d2, d4
	fmul	d2, d15, d2
	add	w2, w17, w15
	and	w2, w2, #0xfff
	ldr	d4, [x10, w2, uxtw #3]
	sub	w2, w17, w14
	and	w2, w2, #0xfff
	ldr	d19, [x11, w2, uxtw #3]
	add	w2, w17, w16
	and	w2, w2, #0xfff
	ldr	d13, [x11, w2, uxtw #3]
	fmul	d13, d25, d13
	fmadd	d19, d23, d19, d13
	sub	w2, w17, w13
	and	w2, w2, #0xfff
	ldr	d13, [x10, w2, uxtw #3]
	fmadd	d19, d27, d13, d19
	fmadd	d4, d17, d4, d19
	fnmsub	d2, d2, d7, d4
	ldr	d3, [sp, #24]
	fmadd	d4, d3, d2, d29
	fmul	d29, d1, d4
	mov	w2, #3
	fmov	d13, #1.00000000
	mov.16b	v4, v29
LBB0_6:
	fmul	d19, d13, d4
	tst	w2, #0x1
	fcsel	d13, d13, d19, eq
	fmul	d4, d4, d4
	lsr	w2, w2, #1
	cbnz	w2, LBB0_6
	ldr	d3, [sp, #32]
	fmul	d2, d3, d2
	mov	w2, #3
	fmov	d14, #1.00000000
LBB0_8:
	fmul	d4, d14, d2
	tst	w2, #0x1
	fcsel	d14, d14, d4, eq
	fmul	d2, d2, d2
	lsr	w2, w2, #1
	cbnz	w2, LBB0_8
	fmadd	d2, d0, d29, d28
	fmul	d28, d1, d2
	mov	w2, #3
	fmov	d15, #1.00000000
	mov.16b	v2, v28
LBB0_10:
	fmul	d4, d15, d2
	tst	w2, #0x1
	fcsel	d15, d15, d4, eq
	fmul	d2, d2, d2
	lsr	w2, w2, #1
	cbnz	w2, LBB0_10
	fmadd	d2, d0, d28, d26
	fmul	d26, d1, d2
	mov	w2, #3
	fmov	d2, #1.00000000
	mov.16b	v4, v26
LBB0_12:
	fmul	d19, d2, d4
	tst	w2, #0x1
	fcsel	d2, d2, d19, eq
	fmul	d4, d4, d4
	lsr	w2, w2, #1
	cbnz	w2, LBB0_12
	fmadd	d4, d0, d26, d5
	fmul	d5, d1, d4
	mov	w2, #3
	fmov	d4, #1.00000000
	mov.16b	v19, v5
LBB0_14:
	fmul	d3, d4, d19
	tst	w2, #0x1
	fcsel	d4, d4, d3, eq
	fmul	d19, d19, d19
	lsr	w2, w2, #1
	cbnz	w2, LBB0_14
	fsub	d3, d14, d13
	fmadd	d3, d0, d3, d24
	fmul	d24, d1, d3
	fadd	d3, d13, d24
	fsub	d3, d3, d15
	fmadd	d3, d0, d3, d22
	fmul	d22, d1, d3
	fadd	d3, d15, d22
	fsub	d3, d3, d2
	fmadd	d3, d0, d3, d21
	fmul	d21, d1, d3
	fadd	d2, d2, d21
	fsub	d2, d2, d4
	fmadd	d2, d0, d2, d20
	fmul	d20, d1, d2
	fmsub	d2, d8, d20, d5
	str	d2, [x12, x9, lsl #3]
	add	w17, w17, #1
	add	x9, x9, #1
	fmov	d15, #1.00000000
	mov.16b	v14, v12
	mov.16b	v13, v11
	cmp	x1, #64
	add	x1, x1, #1
	b.ne	LBB0_1
	movi.2s	v0, #1
	str	d0, [x0, #40]
	stp	d31, d31, [x0, #80]
	stp	d11, d11, [x0, #96]
	stp	d30, d30, [x0, #120]
	stp	d12, d12, [x0, #136]
	str	w17, [x0, #160]
	stp	d29, d29, [x8, #168]
	stp	d28, d28, [x8, #184]
	stp	d26, d26, [x8, #200]
	stp	d5, d5, [x8, #216]
	stp	d24, d24, [x8, #240]
	stp	d22, d22, [x8, #256]
	stp	d21, d21, [x8, #272]
	stp	d20, d20, [x8, #288]
	;MEMBARRIER
	ldp	d9, d8, [sp, #96]
	ldp	d11, d10, [sp, #80]
	ldp	d13, d12, [sp, #64]
	ldp	d15, d14, [sp, #48]
	add	sp, sp, #112
	ret
	.cfi_endproc

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
	.quad	0x40e7700000000000
	.quad	0x3f212843cf07a12c
lCPI3_1:
	.quad	0x3fe0000000000000
	.quad	0x40c7700000000000
lCPI3_2:
	.quad	0x407b800000000000
	.quad	0x3ef5d867c3ece2a5
lCPI3_3:
	.quad	37
	.quad	2305843009213693952
lCPI3_4:
	.quad	1
	.quad	2305843009213693952
lCPI3_5:
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
	mov	w1, #304
	movk	w1, #1, lsl #16
	bl	_KGEN_CompilerRT_AlignedAlloc
	cbz	x0, LBB3_5
	mov	x19, x0
	str	xzr, [x0]
	mov	w8, #48000
	str	w8, [x0, #8]
Lloh6:
	adrp	x8, lCPI3_0@PAGE
Lloh7:
	ldr	q0, [x8, lCPI3_0@PAGEOFF]
	str	q0, [x0, #16]
	mov	x8, #123145302310912
	movk	x8, #16599, lsl #48
	str	x8, [x0, #152]
Lloh8:
	adrp	x8, lCPI3_1@PAGE
Lloh9:
	ldr	q0, [x8, lCPI3_1@PAGEOFF]
Lloh10:
	adrp	x8, lCPI3_2@PAGE
Lloh11:
	ldr	q1, [x8, lCPI3_2@PAGEOFF]
	mov	x8, #4611686018427387904
	str	x8, [x0, #112]
	mov	x8, #246290604621824
	movk	x8, #16517, lsl #48
	stp	q0, q1, [x0, #48]
	stp	x8, xzr, [x0, #32]
	str	wzr, [x0, #160]
	movi.2d	v0, #0000000000000000
	stp	q0, q0, [x0, #80]
	stur	q0, [x0, #120]
	stur	q0, [x0, #136]
	add	x0, x0, #168
	mov	w1, #136
	movk	w1, #1, lsl #16
	bl	_bzero
	mov	w0, #16
	mov	w1, #528
	bl	_KGEN_CompilerRT_AlignedAlloc
	cbz	x0, LBB3_5
	mov	x8, x0
	movi.2d	v0, #0000000000000000
	str	q0, [x8, #8]!
	str	x8, [x0]
	stur	q0, [x0, #24]
	stur	q0, [x0, #40]
	stur	q0, [x0, #56]
	stur	q0, [x0, #72]
	stur	q0, [x0, #88]
	stur	q0, [x0, #104]
	stur	q0, [x0, #120]
	stur	q0, [x0, #136]
	stur	q0, [x0, #152]
	stur	q0, [x0, #168]
	stur	q0, [x0, #184]
	stur	q0, [x0, #200]
	stur	q0, [x0, #216]
	stur	q0, [x0, #232]
	stur	q0, [x0, #248]
	stp	q0, q0, [x8, #256]
	stp	q0, q0, [x8, #288]
	stp	q0, q0, [x8, #320]
	stp	q0, q0, [x8, #352]
	stp	q0, q0, [x8, #384]
	stp	q0, q0, [x8, #416]
	stp	q0, q0, [x8, #448]
	stp	q0, q0, [x8, #480]
	mov	x20, x0
	mov	x0, x19
	mov	x1, x20
	mov	x2, x20
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
LBB3_5:
Lloh12:
	adrp	x8, _static_string_09e773a88105e290@PAGE
Lloh13:
	add	x9, x8, _static_string_09e773a88105e290@PAGEOFF
Lloh14:
	adrp	x8, lCPI3_3@PAGE
Lloh15:
	ldr	q0, [x8, lCPI3_3@PAGEOFF]
	stur	q0, [sp, #64]
Lloh16:
	adrp	x8, _static_string_a8d4ace0dc8d360e@PAGE
Lloh17:
	add	x8, x8, _static_string_a8d4ace0dc8d360e@PAGEOFF
	str	x8, [sp, #80]
Lloh18:
	adrp	x8, lCPI3_4@PAGE
Lloh19:
	ldr	q0, [x8, lCPI3_4@PAGEOFF]
	stur	q0, [sp, #88]
Lloh20:
	adrp	x8, _static_string_7f1562353e292282@PAGE
Lloh21:
	add	x8, x8, _static_string_7f1562353e292282@PAGEOFF
	str	x8, [sp, #104]
Lloh22:
	adrp	x8, lCPI3_5@PAGE
Lloh23:
	ldr	q0, [x8, lCPI3_5@PAGEOFF]
	stur	q0, [sp, #112]
	mov	w8, #1
	stp	x8, x9, [sp, #48]
	strb	w8, [sp, #40]
	str	x8, [sp, #32]
Lloh24:
	adrp	x8, _static_string_bbe01a6a523daf15@PAGE
Lloh25:
	add	x8, x8, _static_string_bbe01a6a523daf15@PAGEOFF
	stp	xzr, x8, [sp, #16]
Lloh26:
	adrp	x8, _static_string_c44bdff4074eecdb@PAGE
Lloh27:
	add	x8, x8, _static_string_c44bdff4074eecdb@PAGEOFF
	add	x9, sp, #56
Lloh28:
	adrp	x0, _static_string_31203c1a2bdb78cc@PAGE
Lloh29:
	add	x0, x0, _static_string_31203c1a2bdb78cc@PAGEOFF
Lloh30:
	adrp	x5, _static_string_e076905c259bf94f@PAGE
Lloh31:
	add	x5, x5, _static_string_e076905c259bf94f@PAGEOFF
	add	x2, sp, #80
	add	x7, sp, #104
	stp	x9, x8, [sp]
	mov	w1, #6
	mov	w3, #232
	mov	w4, #14
	mov	w6, #54
	bl	"_std::io::io::print[KGENParamList[::Writable],*::Writable,LITImmutOrigin,::Origin[::Bool(False), $2]](*$0,sep:::StringSlice[::Bool(False), StaticConstantOrigin, *?],end:::StringSlice[::Bool(False), StaticConstantOrigin, *?],flush:::Bool,file:::FileDescriptor$),Ts.values`=[[typevalue<#kgen.instref<\"std::collections::string::string_slice::StringSlice,mut=0,origin._mlir_origin`={  },origin={  }\">>, struct<(pointer<none>, index)>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>], [typevalue<#kgen.instref<\"std::reflection::location::SourceLocation\">>, struct<(index, index, struct<(pointer<none>, index)>)>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>]]"
	ldrb	w8, [sp, #103]
	tbz	w8, #6, LBB3_8
	ldr	x8, [sp, #80]
	sub	x0, x8, #8
	mov	x8, #-1
	ldaddal	x8, x8, [x0]
	cmp	x8, #1
	b.ne	LBB3_8
	dmb	ishld
	bl	_KGEN_CompilerRT_AlignedFree
LBB3_8:
	ldrb	w8, [sp, #127]
	tbz	w8, #6, LBB3_11
	ldr	x8, [sp, #104]
	sub	x0, x8, #8
	mov	x8, #-1
	ldaddal	x8, x8, [x0]
	cmp	x8, #1
	b.ne	LBB3_11
	dmb	ishld
	bl	_KGEN_CompilerRT_AlignedFree
LBB3_11:
	brk	#0x1
	.loh AdrpLdrGot	Lloh4, Lloh5
	.loh AdrpLdrGot	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpLdr	Lloh10, Lloh11
	.loh AdrpAdrp	Lloh8, Lloh10
	.loh AdrpLdr	Lloh8, Lloh9
	.loh AdrpLdr	Lloh6, Lloh7
	.loh AdrpAdd	Lloh30, Lloh31
	.loh AdrpAdd	Lloh28, Lloh29
	.loh AdrpAdd	Lloh26, Lloh27
	.loh AdrpAdd	Lloh24, Lloh25
	.loh AdrpLdr	Lloh22, Lloh23
	.loh AdrpAdd	Lloh20, Lloh21
	.loh AdrpAdrp	Lloh18, Lloh20
	.loh AdrpLdr	Lloh18, Lloh19
	.loh AdrpAdd	Lloh16, Lloh17
	.loh AdrpAdrp	Lloh14, Lloh16
	.loh AdrpLdr	Lloh14, Lloh15
	.loh AdrpAdrp	Lloh12, Lloh14
	.loh AdrpAdd	Lloh12, Lloh13
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
Lloh32:
	adrp	x12, _static_string_978d8d34847e5196@PAGE
Lloh33:
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
Lloh34:
	adrp	x12, _static_string_978d8d34847e5196@PAGE
Lloh35:
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
	.loh AdrpAdd	Lloh32, Lloh33
	.loh AdrpAdd	Lloh34, Lloh35
	.cfi_endproc

	.p2align	2
"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0":
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
Lloh36:
	adrp	x1, _static_string_0d78baac08237ddb@PAGE
Lloh37:
	add	x1, x1, _static_string_0d78baac08237ddb@PAGEOFF
	bl	_fdopen
	mov	x19, x0
	bl	_fflush
	mov	x0, x19
	ldp	x29, x30, [sp, #16]
	ldp	x20, x19, [sp], #32
	b	_fclose
	.loh AdrpAdd	Lloh36, Lloh37
	.cfi_endproc

	.p2align	2
"_std::io::io::print[KGENParamList[::Writable],*::Writable,LITImmutOrigin,::Origin[::Bool(False), $2]](*$0,sep:::StringSlice[::Bool(False), StaticConstantOrigin, *?],end:::StringSlice[::Bool(False), StaticConstantOrigin, *?],flush:::Bool,file:::FileDescriptor$),Ts.values`=[[typevalue<#kgen.instref<\"std::collections::string::string_slice::StringSlice,mut=0,origin._mlir_origin`={  },origin={  }\">>, struct<(pointer<none>, index)>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>], [typevalue<#kgen.instref<\"std::reflection::location::SourceLocation\">>, struct<(index, index, struct<(pointer<none>, index)>)>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>], [typevalue<#kgen.instref<\"std::collections::string::string::String\">>, struct<(pointer<none>, index, index) memoryOnly>]]":
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
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
	add	x0, sp, #48
	mov	x1, x24
	mov	x2, x23
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
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
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
	add	x0, sp, #48
	mov	x1, x24
	mov	x2, x23
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
	add	x0, sp, #48
	mov	x1, x28
	mov	x2, x27
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
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
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
	ldr	x8, [x22, #16]
	tbnz	x8, #63, LBB7_9
	ldp	x22, x2, [x22]
	b	LBB7_10
LBB7_9:
	ubfx	x2, x8, #56, #5
LBB7_10:
	add	x0, sp, #48
	mov	x1, x22
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
	add	x0, sp, #48
	mov	x1, x24
	mov	x2, x23
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
	ldr	x8, [x21, #16]
	tbnz	x8, #63, LBB7_12
	ldp	x21, x2, [x21]
	b	LBB7_13
LBB7_12:
	ubfx	x2, x8, #56, #5
LBB7_13:
	add	x0, sp, #48
	mov	x1, x21
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
	add	x0, sp, #48
	ldp	x1, x2, [sp, #16]
	bl	"_std::format::_utils::_WriteBufferStack::write_string[::Bool,LITOrigin[$4._mlir_value],::Origin[$4, $5]](::_WriteBufferStack[$0, $1, $2, $3]&,::StringSlice[$4, $5, $6]),W=[typevalue<#kgen.instref<\"std::io::file_descriptor::FileDescriptor\">>, index],stack_buffer_bytes=4096,string.mut`2x1=0"
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

	.section	__TEXT,__const
	.p2align	4, 0x0
_static_string_e076905c259bf94f:
	.asciz	"oss/modular/mojo/stdlib/std/memory/unsafe_pointer.mojo"

	.p2align	4, 0x0
_static_string_bbe01a6a523daf15:
	.asciz	"\n"

	.p2align	4, 0x0
_static_string_31203c1a2bdb78cc:
	.asciz	"ABORT:"

	.p2align	4, 0x0
_static_string_a8d4ace0dc8d360e:
	.asciz	" "

	.p2align	4, 0x0
_static_string_7f1562353e292282:
	.asciz	": "

	.p2align	4, 0x0
_static_string_c44bdff4074eecdb:
	.space	1

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
