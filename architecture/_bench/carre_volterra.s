	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 26, 0	sdk_version 26, 0
	.section	__TEXT,__literal16,16byte_literals
	.p2align	4, 0x0                          ; -- Begin function main
lCPI0_0:
	.quad	0x40f7700000000000              ; double 96000
	.quad	0x3ee5d867c3ece2a5              ; double 1.0416666666666666E-5
lCPI0_2:
	.quad	0                               ; 0x0
	.quad	1                               ; 0x1
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3, 0x0
lCPI0_1:
	.long	0x442f0000                      ; float 700
	.long	0x3f000000                      ; float 0.5
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64
	stp	x22, x21, [sp, #16]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #32]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	mov	w0, #504                        ; =0x1f8
	movk	w0, #1, lsl #16
	bl	__Znwm
	mov	x19, x0
Lloh0:
	adrp	x8, __ZTV5mydsp@GOTPAGE
Lloh1:
	ldr	x8, [x8, __ZTV5mydsp@GOTPAGEOFF]
	add	x8, x8, #16
	str	x8, [x0]
	mov	w8, #30464                      ; =0x7700
	movk	w8, #1, lsl #16
	str	w8, [x0, #8]
Lloh2:
	adrp	x8, lCPI0_0@PAGE
Lloh3:
	ldr	q0, [x8, lCPI0_0@PAGEOFF]
	str	q0, [x0, #16]
	mov	x8, #41260                      ; =0xa12c
	movk	x8, #52999, lsl #16
	movk	x8, #10307, lsl #32
	movk	x8, #16145, lsl #48
	str	x8, [x0, #112]
	mov	x8, #123145302310912            ; =0x700000000000
	movk	x8, #16599, lsl #48
	str	x8, [x0, #128]
	mov	x8, #123145302310912            ; =0x700000000000
	movk	x8, #16615, lsl #48
	str	x8, [x0, #216]
	mov	w8, #1138491392                 ; =0x43dc0000
	str	w8, [x0, #32]
	mov	w8, #1073741824                 ; =0x40000000
	str	w8, [x0, #72]
Lloh4:
	adrp	x8, lCPI0_1@PAGE
Lloh5:
	ldr	d0, [x8, lCPI0_1@PAGEOFF]
	str	d0, [x0, #120]
	mov	w8, #496                        ; =0x1f0
	movk	w8, #1, lsl #16
	str	wzr, [x0, x8]
	bl	__ZN5mydsp13instanceClearEv
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
	mov	x0, x19
	blr	x8
	mov	x20, x0
	ldr	x8, [x19]
	ldr	x8, [x8, #24]
	mov	x0, x19
	blr	x8
	orr	w8, w0, w20
	tbnz	w8, #31, LBB0_11
; %bb.1:
	add	w22, w0, w20
	add	w8, w22, w22, lsl #6
	lsl	w8, w8, #3
	sxtw	x1, w8
	mov	w0, #8                          ; =0x8
	bl	_aligned_alloc
	cbz	x0, LBB0_12
; %bb.2:
	mov	x21, x0
	sxtw	x8, w22
	sbfiz	x9, x22, #3, #32
	add	x0, x0, x9
	cmp	w22, #1
	b.lt	LBB0_10
; %bb.3:
	cmp	w22, #8
	b.hs	LBB0_5
; %bb.4:
	mov	x10, #0                         ; =0x0
	b	LBB0_8
LBB0_5:
	and	x10, x8, #0x7ffffff8
Lloh6:
	adrp	x11, lCPI0_2@PAGE
Lloh7:
	ldr	q0, [x11, lCPI0_2@PAGEOFF]
	add	x11, x21, #32
	mov	w12, #1024                      ; =0x400
	dup.2d	v1, x12
	mov	w12, #2048                      ; =0x800
	dup.2d	v2, x12
	mov	w12, #3072                      ; =0xc00
	dup.2d	v3, x12
	dup.2d	v4, x0
	mov	w12, #8                         ; =0x8
	dup.2d	v5, x12
	mov	x12, x10
LBB0_6:                                 ; =>This Inner Loop Header: Depth=1
	shl.2d	v6, v0, #9
	add.2d	v6, v4, v6
	add.2d	v7, v6, v1
	add.2d	v16, v6, v2
	add.2d	v17, v6, v3
	stp	q6, q7, [x11, #-32]
	stp	q16, q17, [x11], #64
	add.2d	v0, v0, v5
	subs	x12, x12, #8
	b.ne	LBB0_6
; %bb.7:
	cmp	x10, x8
	b.eq	LBB0_10
LBB0_8:
	sub	x11, x8, x10
	add	x12, x21, x10, lsl #3
	add	x9, x9, x10, lsl #9
	add	x9, x21, x9
LBB0_9:                                 ; =>This Inner Loop Header: Depth=1
	str	x9, [x12], #8
	add	x9, x9, #512
	subs	x11, x11, #1
	b.ne	LBB0_9
LBB0_10:
	lsl	x1, x8, #9
	bl	_bzero
	add	x2, x21, w20, sxtw #3
	mov	x0, x19
	mov	x1, x21
	bl	__Z15inspect_computeR5mydspPPfS2_
	mov	x0, x21
	bl	_free
	ldr	x8, [x19]
	ldr	x8, [x8, #8]
	mov	x0, x19
	blr	x8
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #32]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
LBB0_11:
	mov	w19, #2                         ; =0x2
	str	x19, [sp]
Lloh8:
	adrp	x0, l_.str@PAGE
Lloh9:
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	mov	x0, x19
	bl	_exit
LBB0_12:
	mov	w19, #1                         ; =0x1
	str	x19, [sp]
Lloh10:
	adrp	x0, l_.str@PAGE
Lloh11:
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	mov	x0, x19
	bl	_exit
	.loh AdrpLdr	Lloh4, Lloh5
	.loh AdrpLdr	Lloh2, Lloh3
	.loh AdrpLdrGot	Lloh0, Lloh1
	.loh AdrpLdr	Lloh6, Lloh7
	.loh AdrpAdd	Lloh8, Lloh9
	.loh AdrpAdd	Lloh10, Lloh11
	.cfi_endproc
                                        ; -- End function
	.globl	__Z15inspect_computeR5mydspPPfS2_ ; -- Begin function _Z15inspect_computeR5mydspPPfS2_
	.p2align	2
__Z15inspect_computeR5mydspPPfS2_:      ; @_Z15inspect_computeR5mydspPPfS2_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #80
	stp	x24, x23, [sp, #16]             ; 16-byte Folded Spill
	stp	x22, x21, [sp, #32]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #48]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	mov	x19, x2
	mov	x20, x1
	mov	x21, x0
	mov	w22, #16960                     ; =0x4240
	movk	w22, #15, lsl #16
	add	x23, sp, #8
	mov	x24, sp
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	str	x20, [sp, #8]
	; InlineAsm Start
	; InlineAsm End
	str	x19, [sp]
	; InlineAsm Start
	; InlineAsm End
	ldr	x8, [x21]
	ldr	x8, [x8, #120]
	mov	x0, x21
	mov	w1, #128                        ; =0x80
	mov	x2, x20
	mov	x3, x19
	blr	x8
	; InlineAsm Start
	; InlineAsm End
	subs	w22, w22, #1
	b.ne	LBB1_1
; %bb.2:
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #48]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #32]             ; 16-byte Folded Reload
	ldp	x24, x23, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydspD1Ev                  ; -- Begin function _ZN5mydspD1Ev
	.weak_def_can_be_hidden	__ZN5mydspD1Ev
	.p2align	2
__ZN5mydspD1Ev:                         ; @_ZN5mydspD1Ev
	.cfi_startproc
; %bb.0:
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydspD0Ev                  ; -- Begin function _ZN5mydspD0Ev
	.weak_def_can_be_hidden	__ZN5mydspD0Ev
	.p2align	2
__ZN5mydspD0Ev:                         ; @_ZN5mydspD0Ev
	.cfi_startproc
; %bb.0:
	b	__ZdlPv
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp12getNumInputsEv      ; -- Begin function _ZN5mydsp12getNumInputsEv
	.weak_def_can_be_hidden	__ZN5mydsp12getNumInputsEv
	.p2align	2
__ZN5mydsp12getNumInputsEv:             ; @_ZN5mydsp12getNumInputsEv
	.cfi_startproc
; %bb.0:
	mov	w0, #0                          ; =0x0
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp13getNumOutputsEv     ; -- Begin function _ZN5mydsp13getNumOutputsEv
	.weak_def_can_be_hidden	__ZN5mydsp13getNumOutputsEv
	.p2align	2
__ZN5mydsp13getNumOutputsEv:            ; @_ZN5mydsp13getNumOutputsEv
	.cfi_startproc
; %bb.0:
	mov	w0, #1                          ; =0x1
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp18buildUserInterfaceEP2UI ; -- Begin function _ZN5mydsp18buildUserInterfaceEP2UI
	.weak_def_can_be_hidden	__ZN5mydsp18buildUserInterfaceEP2UI
	.p2align	2
__ZN5mydsp18buildUserInterfaceEP2UI:    ; @_ZN5mydsp18buildUserInterfaceEP2UI
	.cfi_startproc
; %bb.0:
	stp	x20, x19, [sp, #-32]!           ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x1
	mov	x20, x0
	ldr	x8, [x1]
	ldr	x8, [x8, #32]
Lloh12:
	adrp	x1, l_.str.1@PAGE
Lloh13:
	add	x1, x1, l_.str.1@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #56]
Lloh14:
	adrp	x1, l_.str.2@PAGE
Lloh15:
	add	x1, x1, l_.str.2@PAGEOFF
	add	x9, x20, #16, lsl #12           ; =65536
	add	x2, x9, #496
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #72]
Lloh16:
	adrp	x1, l_.str.3@PAGE
Lloh17:
	add	x1, x1, l_.str.3@PAGEOFF
	mov	w9, #52429                      ; =0xcccd
	movk	w9, #15820, lsl #16
	fmov	s3, w9
	add	x2, x20, #72
	fmov	s0, #2.00000000
	movi	d1, #0000000000000000
	fmov	s2, #6.00000000
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #72]
Lloh18:
	adrp	x1, l_.str.4@PAGE
Lloh19:
	add	x1, x1, l_.str.4@PAGEOFF
	mov	w9, #1138491392                 ; =0x43dc0000
	fmov	s0, w9
	mov	w9, #1174011904                 ; =0x45fa0000
	fmov	s2, w9
	add	x2, x20, #32
	fmov	s1, #20.00000000
	fmov	s3, #1.00000000
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #112]
Lloh20:
	adrp	x2, l_.str.5@PAGE
Lloh21:
	add	x2, x2, l_.str.5@PAGEOFF
Lloh22:
	adrp	x3, l_.str.6@PAGE
Lloh23:
	add	x3, x3, l_.str.6@PAGEOFF
	add	x1, x20, #120
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #72]
Lloh24:
	adrp	x1, l_.str.7@PAGE
Lloh25:
	add	x1, x1, l_.str.7@PAGEOFF
	mov	w9, #1143930880                 ; =0x442f0000
	fmov	s0, w9
	mov	w9, #16384                      ; =0x4000
	movk	w9, #18076, lsl #16
	fmov	s2, w9
	add	x2, x20, #120
	fmov	s1, #1.00000000
	fmov	s3, #1.00000000
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #72]
Lloh26:
	adrp	x1, l_.str.8@PAGE
Lloh27:
	add	x1, x1, l_.str.8@PAGEOFF
	mov	w9, #55050                      ; =0xd70a
	movk	w9, #15395, lsl #16
	fmov	s3, w9
	add	x2, x20, #124
	fmov	s0, #0.50000000
	movi	d1, #0000000000000000
	fmov	s2, #1.00000000
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x1, [x8, #40]
	mov	x0, x19
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp], #32             ; 16-byte Folded Reload
	br	x1
	.loh AdrpAdd	Lloh26, Lloh27
	.loh AdrpAdd	Lloh24, Lloh25
	.loh AdrpAdd	Lloh22, Lloh23
	.loh AdrpAdd	Lloh20, Lloh21
	.loh AdrpAdd	Lloh18, Lloh19
	.loh AdrpAdd	Lloh16, Lloh17
	.loh AdrpAdd	Lloh14, Lloh15
	.loh AdrpAdd	Lloh12, Lloh13
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp13getSampleRateEv     ; -- Begin function _ZN5mydsp13getSampleRateEv
	.weak_def_can_be_hidden	__ZN5mydsp13getSampleRateEv
	.p2align	2
__ZN5mydsp13getSampleRateEv:            ; @_ZN5mydsp13getSampleRateEv
	.cfi_startproc
; %bb.0:
	ldr	w0, [x0, #8]
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp4initEi               ; -- Begin function _ZN5mydsp4initEi
	.weak_def_can_be_hidden	__ZN5mydsp4initEi
	.p2align	2
__ZN5mydsp4initEi:                      ; @_ZN5mydsp4initEi
	.cfi_startproc
; %bb.0:
	ldr	x8, [x0]
	ldr	x2, [x8, #56]
	br	x2
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp12instanceInitEi      ; -- Begin function _ZN5mydsp12instanceInitEi
	.weak_def_can_be_hidden	__ZN5mydsp12instanceInitEi
	.p2align	2
__ZN5mydsp12instanceInitEi:             ; @_ZN5mydsp12instanceInitEi
	.cfi_startproc
; %bb.0:
	stp	x20, x19, [sp, #-32]!           ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x0
	ldr	x8, [x0]
	ldr	x8, [x8, #64]
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #72]
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x1, [x8, #80]
	mov	x0, x19
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp], #32             ; 16-byte Folded Reload
	br	x1
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp17instanceConstantsEi ; -- Begin function _ZN5mydsp17instanceConstantsEi
	.weak_def_can_be_hidden	__ZN5mydsp17instanceConstantsEi
	.p2align	2
__ZN5mydsp17instanceConstantsEi:        ; @_ZN5mydsp17instanceConstantsEi
	.cfi_startproc
; %bb.0:
	cmp	w1, #1
	csinc	w8, w1, wzr, gt
	ucvtf	d0, w8
	str	w1, [x0, #8]
	mov	x8, #123145302310912            ; =0x700000000000
	movk	x8, #16647, lsl #48
	fmov	d1, x8
	fminnm	d0, d0, d1
	fmov	d1, #1.00000000
	fdiv	d1, d1, d0
	stp	d0, d1, [x0, #16]
	mov	x8, #11544                      ; =0x2d18
	movk	x8, #21572, lsl #16
	movk	x8, #8699, lsl #32
	movk	x8, #16409, lsl #48
	fmov	d1, x8
	fdiv	d1, d1, d0
	str	d1, [x0, #112]
	fmov	d1, #0.25000000
	fmul	d1, d0, d1
	str	d1, [x0, #128]
	fmov	d1, #0.50000000
	fmul	d0, d0, d1
	str	d0, [x0, #216]
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3, 0x0                          ; -- Begin function _ZN5mydsp26instanceResetUserInterfaceEv
lCPI11_0:
	.long	0x442f0000                      ; float 700
	.long	0x3f000000                      ; float 0.5
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZN5mydsp26instanceResetUserInterfaceEv
	.weak_def_can_be_hidden	__ZN5mydsp26instanceResetUserInterfaceEv
	.p2align	2
__ZN5mydsp26instanceResetUserInterfaceEv: ; @_ZN5mydsp26instanceResetUserInterfaceEv
	.cfi_startproc
; %bb.0:
	mov	w8, #1138491392                 ; =0x43dc0000
	str	w8, [x0, #32]
	mov	w8, #1073741824                 ; =0x40000000
	str	w8, [x0, #72]
Lloh28:
	adrp	x8, lCPI11_0@PAGE
Lloh29:
	ldr	d0, [x8, lCPI11_0@PAGEOFF]
	str	d0, [x0, #120]
	mov	w8, #496                        ; =0x1f0
	movk	w8, #1, lsl #16
	str	wzr, [x0, x8]
	ret
	.loh AdrpLdr	Lloh28, Lloh29
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp13instanceClearEv     ; -- Begin function _ZN5mydsp13instanceClearEv
	.weak_def_can_be_hidden	__ZN5mydsp13instanceClearEv
	.p2align	2
__ZN5mydsp13instanceClearEv:            ; @_ZN5mydsp13instanceClearEv
	.cfi_startproc
; %bb.0:
	mov	x8, x0
	movi.2d	v0, #0000000000000000
	stur	q0, [x0, #56]
	stur	q0, [x0, #40]
	stp	q0, q0, [x0, #80]
	stur	q0, [x0, #136]
	stur	q0, [x0, #152]
	stur	q0, [x0, #168]
	stur	q0, [x0, #184]
	add	x0, x0, #224
	stur	q0, [x8, #200]
	mov	w1, #272                        ; =0x110
	movk	w1, #1, lsl #16
	b	_bzero
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp5cloneEv              ; -- Begin function _ZN5mydsp5cloneEv
	.weak_def_can_be_hidden	__ZN5mydsp5cloneEv
	.p2align	2
__ZN5mydsp5cloneEv:                     ; @_ZN5mydsp5cloneEv
	.cfi_startproc
; %bb.0:
	stp	x20, x19, [sp, #-32]!           ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x0
	mov	w0, #504                        ; =0x1f8
	movk	w0, #1, lsl #16
	bl	__Znwm
	mov	x20, x0
Lloh30:
	adrp	x8, __ZTV5mydsp@GOTPAGE
Lloh31:
	ldr	x8, [x8, __ZTV5mydsp@GOTPAGEOFF]
	add	x8, x8, #16
	str	x8, [x0], #8
	add	x1, x19, #8
	mov	w2, #492                        ; =0x1ec
	movk	w2, #1, lsl #16
	bl	_memcpy
	mov	x0, x20
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp], #32             ; 16-byte Folded Reload
	ret
	.loh AdrpLdrGot	Lloh30, Lloh31
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp8metadataEP4Meta      ; -- Begin function _ZN5mydsp8metadataEP4Meta
	.weak_def_can_be_hidden	__ZN5mydsp8metadataEP4Meta
	.p2align	2
__ZN5mydsp8metadataEP4Meta:             ; @_ZN5mydsp8metadataEP4Meta
	.cfi_startproc
; %bb.0:
	stp	x26, x25, [sp, #-80]!           ; 16-byte Folded Spill
	stp	x24, x23, [sp, #16]             ; 16-byte Folded Spill
	stp	x22, x21, [sp, #32]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #48]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
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
	mov	x19, x1
	ldr	x8, [x1]
	ldr	x8, [x8, #16]
Lloh32:
	adrp	x1, l_.str.9@PAGE
Lloh33:
	add	x1, x1, l_.str.9@PAGEOFF
Lloh34:
	adrp	x2, l_.str.10@PAGE
Lloh35:
	add	x2, x2, l_.str.10@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh36:
	adrp	x1, l_.str.11@PAGE
Lloh37:
	add	x1, x1, l_.str.11@PAGEOFF
Lloh38:
	adrp	x20, l_.str.12@PAGE
Lloh39:
	add	x20, x20, l_.str.12@PAGEOFF
	mov	x0, x19
	mov	x2, x20
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh40:
	adrp	x1, l_.str.13@PAGE
Lloh41:
	add	x1, x1, l_.str.13@PAGEOFF
Lloh42:
	adrp	x21, l_.str.14@PAGE
Lloh43:
	add	x21, x21, l_.str.14@PAGEOFF
	mov	x0, x19
	mov	x2, x21
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh44:
	adrp	x1, l_.str.15@PAGE
Lloh45:
	add	x1, x1, l_.str.15@PAGEOFF
Lloh46:
	adrp	x22, l_.str.16@PAGE
Lloh47:
	add	x22, x22, l_.str.16@PAGEOFF
	mov	x0, x19
	mov	x2, x22
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh48:
	adrp	x1, l_.str.17@PAGE
Lloh49:
	add	x1, x1, l_.str.17@PAGEOFF
Lloh50:
	adrp	x2, l_.str.18@PAGE
Lloh51:
	add	x2, x2, l_.str.18@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh52:
	adrp	x1, l_.str.19@PAGE
Lloh53:
	add	x1, x1, l_.str.19@PAGEOFF
Lloh54:
	adrp	x2, l_.str.20@PAGE
Lloh55:
	add	x2, x2, l_.str.20@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh56:
	adrp	x1, l_.str.21@PAGE
Lloh57:
	add	x1, x1, l_.str.21@PAGEOFF
Lloh58:
	adrp	x2, l_.str.22@PAGE
Lloh59:
	add	x2, x2, l_.str.22@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh60:
	adrp	x1, l_.str.23@PAGE
Lloh61:
	add	x1, x1, l_.str.23@PAGEOFF
Lloh62:
	adrp	x2, l_.str.24@PAGE
Lloh63:
	add	x2, x2, l_.str.24@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh64:
	adrp	x1, l_.str.25@PAGE
Lloh65:
	add	x1, x1, l_.str.25@PAGEOFF
Lloh66:
	adrp	x24, l_.str.26@PAGE
Lloh67:
	add	x24, x24, l_.str.26@PAGEOFF
	mov	x0, x19
	mov	x2, x24
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh68:
	adrp	x1, l_.str.27@PAGE
Lloh69:
	add	x1, x1, l_.str.27@PAGEOFF
Lloh70:
	adrp	x23, l_.str.28@PAGE
Lloh71:
	add	x23, x23, l_.str.28@PAGEOFF
	mov	x0, x19
	mov	x2, x23
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh72:
	adrp	x1, l_.str.29@PAGE
Lloh73:
	add	x1, x1, l_.str.29@PAGEOFF
Lloh74:
	adrp	x2, l_.str.30@PAGE
Lloh75:
	add	x2, x2, l_.str.30@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh76:
	adrp	x1, l_.str.31@PAGE
Lloh77:
	add	x1, x1, l_.str.31@PAGEOFF
Lloh78:
	adrp	x2, l_.str.32@PAGE
Lloh79:
	add	x2, x2, l_.str.32@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh80:
	adrp	x1, l_.str.33@PAGE
Lloh81:
	add	x1, x1, l_.str.33@PAGEOFF
Lloh82:
	adrp	x2, l_.str.34@PAGE
Lloh83:
	add	x2, x2, l_.str.34@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh84:
	adrp	x1, l_.str.35@PAGE
Lloh85:
	add	x1, x1, l_.str.35@PAGEOFF
	mov	x0, x19
	mov	x2, x20
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh86:
	adrp	x1, l_.str.36@PAGE
Lloh87:
	add	x1, x1, l_.str.36@PAGEOFF
	mov	x0, x19
	mov	x2, x21
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh88:
	adrp	x1, l_.str.37@PAGE
Lloh89:
	add	x1, x1, l_.str.37@PAGEOFF
	mov	x0, x19
	mov	x2, x22
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh90:
	adrp	x1, l_.str.38@PAGE
Lloh91:
	add	x1, x1, l_.str.38@PAGEOFF
	mov	x0, x19
	mov	x2, x23
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh92:
	adrp	x1, l_.str.39@PAGE
Lloh93:
	add	x1, x1, l_.str.39@PAGEOFF
Lloh94:
	adrp	x2, l_.str.40@PAGE
Lloh95:
	add	x2, x2, l_.str.40@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh96:
	adrp	x1, l_.str.41@PAGE
Lloh97:
	add	x1, x1, l_.str.41@PAGEOFF
Lloh98:
	adrp	x2, l_.str.42@PAGE
Lloh99:
	add	x2, x2, l_.str.42@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh100:
	adrp	x1, l_.str.43@PAGE
Lloh101:
	add	x1, x1, l_.str.43@PAGEOFF
Lloh102:
	adrp	x2, l_.str.44@PAGE
Lloh103:
	add	x2, x2, l_.str.44@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh104:
	adrp	x1, l_.str.45@PAGE
Lloh105:
	add	x1, x1, l_.str.45@PAGEOFF
Lloh106:
	adrp	x25, l_.str.46@PAGE
Lloh107:
	add	x25, x25, l_.str.46@PAGEOFF
	mov	x0, x19
	mov	x2, x25
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh108:
	adrp	x1, l_.str.47@PAGE
Lloh109:
	add	x1, x1, l_.str.47@PAGEOFF
	mov	x0, x19
	mov	x2, x25
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh110:
	adrp	x1, l_.str.48@PAGE
Lloh111:
	add	x1, x1, l_.str.48@PAGEOFF
	mov	x0, x19
	mov	x2, x22
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh112:
	adrp	x1, l_.str.49@PAGE
Lloh113:
	add	x1, x1, l_.str.49@PAGEOFF
Lloh114:
	adrp	x26, l_.str.50@PAGE
Lloh115:
	add	x26, x26, l_.str.50@PAGEOFF
	mov	x0, x19
	mov	x2, x26
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh116:
	adrp	x1, l_.str.51@PAGE
Lloh117:
	add	x1, x1, l_.str.51@PAGEOFF
Lloh118:
	adrp	x2, l_.str.52@PAGE
Lloh119:
	add	x2, x2, l_.str.52@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh120:
	adrp	x1, l_.str.53@PAGE
Lloh121:
	add	x1, x1, l_.str.53@PAGEOFF
	mov	x0, x19
	mov	x2, x24
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh122:
	adrp	x1, l_.str.54@PAGE
Lloh123:
	add	x1, x1, l_.str.54@PAGEOFF
	mov	x0, x19
	mov	x2, x25
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh124:
	adrp	x1, l_.str.55@PAGE
Lloh125:
	add	x1, x1, l_.str.55@PAGEOFF
	mov	x0, x19
	mov	x2, x25
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh126:
	adrp	x1, l_.str.56@PAGE
Lloh127:
	add	x1, x1, l_.str.56@PAGEOFF
	mov	x0, x19
	mov	x2, x22
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh128:
	adrp	x1, l_.str.57@PAGE
Lloh129:
	add	x1, x1, l_.str.57@PAGEOFF
	mov	x0, x19
	mov	x2, x26
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh130:
	adrp	x1, l_.str.58@PAGE
Lloh131:
	add	x1, x1, l_.str.58@PAGEOFF
Lloh132:
	adrp	x2, l_.str.59@PAGE
Lloh133:
	add	x2, x2, l_.str.59@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh134:
	adrp	x1, l_.str.60@PAGE
Lloh135:
	add	x1, x1, l_.str.60@PAGEOFF
	mov	x0, x19
	mov	x2, x24
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh136:
	adrp	x1, l_.str.61@PAGE
Lloh137:
	add	x1, x1, l_.str.61@PAGEOFF
Lloh138:
	adrp	x2, l_.str.1@PAGE
Lloh139:
	add	x2, x2, l_.str.1@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh140:
	adrp	x1, l_.str.62@PAGE
Lloh141:
	add	x1, x1, l_.str.62@PAGEOFF
	mov	x0, x19
	mov	x2, x20
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh142:
	adrp	x1, l_.str.63@PAGE
Lloh143:
	add	x1, x1, l_.str.63@PAGEOFF
	mov	x0, x19
	mov	x2, x21
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh144:
	adrp	x1, l_.str.64@PAGE
Lloh145:
	add	x1, x1, l_.str.64@PAGEOFF
	mov	x0, x19
	mov	x2, x22
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh146:
	adrp	x1, l_.str.65@PAGE
Lloh147:
	add	x1, x1, l_.str.65@PAGEOFF
	mov	x0, x19
	mov	x2, x23
	blr	x8
	ldr	x8, [x19]
	ldr	x8, [x8, #16]
Lloh148:
	adrp	x1, l_.str.66@PAGE
Lloh149:
	add	x1, x1, l_.str.66@PAGEOFF
Lloh150:
	adrp	x2, l_.str.67@PAGE
Lloh151:
	add	x2, x2, l_.str.67@PAGEOFF
	mov	x0, x19
	blr	x8
	ldr	x8, [x19]
Lloh152:
	adrp	x1, l_.str.68@PAGE
Lloh153:
	add	x1, x1, l_.str.68@PAGEOFF
	ldr	x3, [x8, #16]
Lloh154:
	adrp	x2, l_.str.69@PAGE
Lloh155:
	add	x2, x2, l_.str.69@PAGEOFF
	mov	x0, x19
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #48]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #32]             ; 16-byte Folded Reload
	ldp	x24, x23, [sp, #16]             ; 16-byte Folded Reload
	ldp	x26, x25, [sp], #80             ; 16-byte Folded Reload
	br	x3
	.loh AdrpAdd	Lloh154, Lloh155
	.loh AdrpAdd	Lloh152, Lloh153
	.loh AdrpAdd	Lloh150, Lloh151
	.loh AdrpAdd	Lloh148, Lloh149
	.loh AdrpAdd	Lloh146, Lloh147
	.loh AdrpAdd	Lloh144, Lloh145
	.loh AdrpAdd	Lloh142, Lloh143
	.loh AdrpAdd	Lloh140, Lloh141
	.loh AdrpAdd	Lloh138, Lloh139
	.loh AdrpAdd	Lloh136, Lloh137
	.loh AdrpAdd	Lloh134, Lloh135
	.loh AdrpAdd	Lloh132, Lloh133
	.loh AdrpAdd	Lloh130, Lloh131
	.loh AdrpAdd	Lloh128, Lloh129
	.loh AdrpAdd	Lloh126, Lloh127
	.loh AdrpAdd	Lloh124, Lloh125
	.loh AdrpAdd	Lloh122, Lloh123
	.loh AdrpAdd	Lloh120, Lloh121
	.loh AdrpAdd	Lloh118, Lloh119
	.loh AdrpAdd	Lloh116, Lloh117
	.loh AdrpAdd	Lloh114, Lloh115
	.loh AdrpAdd	Lloh112, Lloh113
	.loh AdrpAdd	Lloh110, Lloh111
	.loh AdrpAdd	Lloh108, Lloh109
	.loh AdrpAdd	Lloh106, Lloh107
	.loh AdrpAdd	Lloh104, Lloh105
	.loh AdrpAdd	Lloh102, Lloh103
	.loh AdrpAdd	Lloh100, Lloh101
	.loh AdrpAdd	Lloh98, Lloh99
	.loh AdrpAdd	Lloh96, Lloh97
	.loh AdrpAdd	Lloh94, Lloh95
	.loh AdrpAdd	Lloh92, Lloh93
	.loh AdrpAdd	Lloh90, Lloh91
	.loh AdrpAdd	Lloh88, Lloh89
	.loh AdrpAdd	Lloh86, Lloh87
	.loh AdrpAdd	Lloh84, Lloh85
	.loh AdrpAdd	Lloh82, Lloh83
	.loh AdrpAdd	Lloh80, Lloh81
	.loh AdrpAdd	Lloh78, Lloh79
	.loh AdrpAdd	Lloh76, Lloh77
	.loh AdrpAdd	Lloh74, Lloh75
	.loh AdrpAdd	Lloh72, Lloh73
	.loh AdrpAdd	Lloh70, Lloh71
	.loh AdrpAdd	Lloh68, Lloh69
	.loh AdrpAdd	Lloh66, Lloh67
	.loh AdrpAdd	Lloh64, Lloh65
	.loh AdrpAdd	Lloh62, Lloh63
	.loh AdrpAdd	Lloh60, Lloh61
	.loh AdrpAdd	Lloh58, Lloh59
	.loh AdrpAdd	Lloh56, Lloh57
	.loh AdrpAdd	Lloh54, Lloh55
	.loh AdrpAdd	Lloh52, Lloh53
	.loh AdrpAdd	Lloh50, Lloh51
	.loh AdrpAdd	Lloh48, Lloh49
	.loh AdrpAdd	Lloh46, Lloh47
	.loh AdrpAdd	Lloh44, Lloh45
	.loh AdrpAdd	Lloh42, Lloh43
	.loh AdrpAdd	Lloh40, Lloh41
	.loh AdrpAdd	Lloh38, Lloh39
	.loh AdrpAdd	Lloh36, Lloh37
	.loh AdrpAdd	Lloh34, Lloh35
	.loh AdrpAdd	Lloh32, Lloh33
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN3dsp7controlEv              ; -- Begin function _ZN3dsp7controlEv
	.weak_def_can_be_hidden	__ZN3dsp7controlEv
	.p2align	2
__ZN3dsp7controlEv:                     ; @_ZN3dsp7controlEv
	.cfi_startproc
; %bb.0:
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN3dsp5frameEPfS0_            ; -- Begin function _ZN3dsp5frameEPfS0_
	.weak_def_can_be_hidden	__ZN3dsp5frameEPfS0_
	.p2align	2
__ZN3dsp5frameEPfS0_:                   ; @_ZN3dsp5frameEPfS0_
	.cfi_startproc
; %bb.0:
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN5mydsp7computeEiPPfS1_      ; -- Begin function _ZN5mydsp7computeEiPPfS1_
	.weak_def_can_be_hidden	__ZN5mydsp7computeEiPPfS1_
	.p2align	2
__ZN5mydsp7computeEiPPfS1_:             ; @_ZN5mydsp7computeEiPPfS1_
	.cfi_startproc
; %bb.0:
	stp	d15, d14, [sp, #-160]!          ; 16-byte Folded Spill
	stp	d13, d12, [sp, #16]             ; 16-byte Folded Spill
	stp	d11, d10, [sp, #32]             ; 16-byte Folded Spill
	stp	d9, d8, [sp, #48]               ; 16-byte Folded Spill
	stp	x28, x27, [sp, #64]             ; 16-byte Folded Spill
	stp	x26, x25, [sp, #80]             ; 16-byte Folded Spill
	stp	x24, x23, [sp, #96]             ; 16-byte Folded Spill
	stp	x22, x21, [sp, #112]            ; 16-byte Folded Spill
	stp	x20, x19, [sp, #128]            ; 16-byte Folded Spill
	stp	x29, x30, [sp, #144]            ; 16-byte Folded Spill
	add	x29, sp, #144
	mov	w9, #5952                       ; =0x1740
Lloh156:
	adrp	x16, ___chkstk_darwin@GOTPAGE
Lloh157:
	ldr	x16, [x16, ___chkstk_darwin@GOTPAGEOFF]
	blr	x16
	sub	sp, sp, #1, lsl #12             ; =4096
	sub	sp, sp, #1856
	.cfi_def_cfa w29, 16
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
	.cfi_offset b8, -104
	.cfi_offset b9, -112
	.cfi_offset b10, -120
	.cfi_offset b11, -128
	.cfi_offset b12, -136
	.cfi_offset b13, -144
	.cfi_offset b14, -152
	.cfi_offset b15, -160
	mov	x19, x0
	add	x15, sp, #1, lsl #12            ; =4096
	add	x15, x15, #1104
	add	x9, sp, #3024
Lloh158:
	adrp	x8, ___stack_chk_guard@GOTPAGE
Lloh159:
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
Lloh160:
	ldr	x8, [x8]
	stur	x8, [x29, #-168]
	add	x8, x0, #16, lsl #12            ; =65536
	add	x30, x8, #232
	mov	w8, #32992                      ; =0x80e0
	add	x8, x0, x8
	str	x8, [sp, #424]                  ; 8-byte Folded Spill
	ldr	x8, [x3]
	str	x8, [sp, #312]                  ; 8-byte Folded Spill
	ldr	s0, [x0, #32]
	fcvt	d0, s0
	mov	x8, #47479                      ; =0xb977
	movk	x8, #24011, lsl #16
	movk	x8, #29422, lsl #32
	movk	x8, #16439, lsl #48
	fmov	d1, x8
	fcmp	d0, d1
	fcsel	d2, d1, d0, mi
	fabs	d3, d0
	fcsel	d3, d1, d3, mi
	fmov	d4, #20.00000000
	fmaxnm	d3, d3, d4
	ldr	d5, [x0, #24]
	fmul	d14, d5, d3
	ldr	s6, [x0, #72]
	fcvt	d6, s6
	fadd	d0, d0, d6
	fcmp	d0, d1
	fcsel	d6, d1, d0, mi
	fabs	d0, d0
	fcsel	d0, d1, d0, mi
	fmaxnm	d0, d0, d4
	fmul	d23, d5, d0
	ldp	s1, s4, [x0, #120]
	fcvt	d1, s1
	ldr	d5, [x0, #112]
	fmul	d8, d5, d1
	fmov	d7, #1.00000000
	fadd	d16, d8, d7
	fdiv	d9, d7, d16
	fcvt	d13, s4
	fmul	d4, d5, d13
	fmul	d11, d4, d1
	fdiv	d18, d7, d3
	ldr	d1, [x0, #216]
	fdiv	d4, d1, d6
	mov	x8, #277076930199552            ; =0xfc0000000000
	movk	x8, #16543, lsl #48
	fmov	d5, x8
	fminnm	d4, d4, d5
	movi	d6, #0000000000000000
	fmaxnm	d4, d4, d6
	fcvtzs	w7, d4
	scvtf	d16, w7
	fdiv	d19, d7, d0
	fsub	d20, d4, d16
	ldr	d17, [x0, #128]
	fdiv	d0, d17, d0
	str	q0, [sp, #352]                  ; 16-byte Folded Spill
	fdiv	d0, d1, d2
	fminnm	d0, d0, d5
	fmaxnm	d0, d0, d6
	fcvtzs	w21, d0
	scvtf	d1, w21
	fsub	d2, d7, d0
	fadd	d21, d2, d1
	fdiv	d2, d17, d3
	str	q2, [sp, #368]                  ; 16-byte Folded Spill
	fsub	d17, d0, d1
	fsub	d0, d7, d4
	fadd	d22, d0, d16
	add	x8, sp, #2448
	add	x24, x8, #32
	add	x8, sp, #1904
	add	x28, x8, #32
	add	x8, sp, #816
	add	x25, x8, #32
	add	x8, sp, #528
	add	x26, x8, #32
	ldr	s0, [x30, #264]
	fcvt	d0, s0
	mov	x8, #6148914691236517205        ; =0x5555555555555555
	movk	x8, #16341, lsl #48
	fmov	d1, x8
	fmul	d10, d0, d1
	fmov.2d	v1, #2.00000000
	fmov.2d	v0, #-1.00000000
	stp	q0, q1, [sp, #320]              ; 32-byte Folded Spill
	subs	w8, w1, #32
	str	x8, [sp, #296]                  ; 8-byte Folded Spill
	stp	q20, q18, [sp, #128]            ; 32-byte Folded Spill
	stp	q21, q19, [sp, #384]            ; 32-byte Folded Spill
	stp	q22, q17, [sp, #96]             ; 32-byte Folded Spill
	b.ge	LBB17_2
; %bb.1:
	mov	w27, #0                         ; =0x0
	subs	w20, w1, w27
	b.gt	LBB17_17
	b	LBB17_160
LBB17_2:
	str	w1, [sp, #12]                   ; 4-byte Folded Spill
	str	d11, [sp, #304]                 ; 8-byte Folded Spill
	mov	x27, #0                         ; =0x0
	add	x20, x19, #224
	mov	w8, #33000                      ; =0x80e8
	add	x22, x19, x8
	add	x8, x19, #16, lsl #12           ; =65536
	add	x10, x8, #240
	add	x8, x19, #16, lsl #12           ; =65536
	add	x8, x8, #272
	stp	x8, x10, [sp, #248]             ; 16-byte Folded Spill
	add	x8, x19, #16, lsl #12           ; =65536
	add	x8, x8, #304
	str	x8, [sp, #240]                  ; 8-byte Folded Spill
	add	x8, x19, #16, lsl #12           ; =65536
	add	x14, x8, #368
	add	x8, x19, #16, lsl #12           ; =65536
	add	x10, x8, #400
	add	x8, x19, #16, lsl #12           ; =65536
	add	x8, x8, #336
	stp	x8, x10, [sp, #216]             ; 16-byte Folded Spill
	add	x8, x19, #16, lsl #12           ; =65536
	add	x8, x8, #432
	str	x8, [sp, #208]                  ; 8-byte Folded Spill
	add	x8, x19, #16, lsl #12           ; =65536
	add	x10, x8, #464
	str	d10, [sp, #16]                  ; 8-byte Folded Spill
	fneg	d0, d10
	dup.2d	v2, v18[0]
	dup.2d	v1, v20[0]
	stp	q1, q2, [sp, #64]               ; 32-byte Folded Spill
	dup.2d	v2, v17[0]
	add	x8, x9, #264
	stp	x8, x10, [sp, #192]             ; 16-byte Folded Spill
	dup.2d	v1, v22[0]
	stp	q1, q2, [sp, #32]               ; 32-byte Folded Spill
	dup.2d	v0, v0[0]
	str	q0, [sp, #176]                  ; 16-byte Folded Spill
	neg	w8, w21
	str	w8, [sp, #172]                  ; 4-byte Folded Spill
	neg	w8, w7
	str	w8, [sp, #168]                  ; 4-byte Folded Spill
	mvn	w8, w21
	str	w8, [sp, #28]                   ; 4-byte Folded Spill
	mvn	w8, w7
	str	w8, [sp, #24]                   ; 4-byte Folded Spill
	add	x23, sp, #3600
	str	d13, [sp, #288]                 ; 8-byte Folded Spill
	stp	x24, x26, [sp, #272]            ; 16-byte Folded Spill
	str	d23, [sp, #264]                 ; 8-byte Folded Spill
	str	x14, [sp, #232]                 ; 8-byte Folded Spill
LBB17_3:                                ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB17_8 Depth 2
                                        ;     Child Loop BB17_10 Depth 2
                                        ;     Child Loop BB17_12 Depth 2
                                        ;     Child Loop BB17_14 Depth 2
	str	x27, [sp, #520]                 ; 8-byte Folded Spill
	ldur	q0, [x19, #56]
	ldur	q1, [x19, #40]
	str	q0, [sp, #5648]
	str	q1, [sp, #5632]
	ldr	d0, [sp, #5656]
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d0, d0, d1
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5664]
	str	d1, [sp, #5672]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5680]
	str	d1, [sp, #5688]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5696]
	str	d1, [sp, #5704]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5712]
	str	d1, [sp, #5720]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5728]
	str	d1, [sp, #5736]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5744]
	str	d1, [sp, #5752]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5760]
	str	d1, [sp, #5768]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5776]
	str	d1, [sp, #5784]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5792]
	str	d1, [sp, #5800]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5808]
	str	d1, [sp, #5816]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5824]
	str	d1, [sp, #5832]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5840]
	str	d1, [sp, #5848]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5856]
	str	d1, [sp, #5864]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5872]
	str	d1, [sp, #5880]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5888]
	str	d1, [sp, #5896]
	fadd	d0, d14, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d14, d0
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d14, d1
	str	d0, [sp, #5904]
	str	d1, [sp, #5912]
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1536
	ldp	q0, q1, [x8, #256]
	stur	q0, [x19, #40]
	stur	q1, [x19, #56]
	ldp	q1, q0, [x19, #80]
	str	q0, [sp, #5360]
	str	q1, [sp, #5344]
	ldr	d0, [sp, #5368]
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d0, d0, d1
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5376]
	str	d1, [sp, #5384]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5392]
	str	d1, [sp, #5400]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5408]
	str	d1, [sp, #5416]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5424]
	str	d1, [sp, #5432]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5440]
	str	d1, [sp, #5448]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5456]
	str	d1, [sp, #5464]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5472]
	str	d1, [sp, #5480]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5488]
	str	d1, [sp, #5496]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5504]
	str	d1, [sp, #5512]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5520]
	str	d1, [sp, #5528]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5536]
	str	d1, [sp, #5544]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5552]
	str	d1, [sp, #5560]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5568]
	str	d1, [sp, #5576]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5584]
	str	d1, [sp, #5592]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5600]
	str	d1, [sp, #5608]
	fadd	d0, d23, d1
	frintm	d0, d0
	fsub	d0, d1, d0
	fadd	d0, d23, d0
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d1, d0, d1
	fadd	d1, d23, d1
	str	d0, [sp, #5616]
	str	d1, [sp, #5624]
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1248
	ldp	q0, q1, [x8, #256]
	stp	q0, q1, [x19, #80]
	ldur	q0, [x19, #136]
	str	q0, [sp, #5200]
	add	x24, sp, #1, lsl #12            ; =4096
	add	x24, x24, #1104
	add	x0, x24, #16
Lloh161:
	adrp	x1, l_.memset_pattern.70@PAGE
Lloh162:
	add	x1, x1, l_.memset_pattern.70@PAGEOFF
	mov	w2, #128                        ; =0x80
	mov	x27, x30
	mov	x26, x19
	mov	x19, x21
	mov	x21, x7
	bl	_memset_pattern16
	mov	x7, x21
	mov	x21, x19
	mov	x19, x26
	mov	x30, x27
	ldur	q0, [x26, #152]
	ldur	q1, [x26, #168]
	str	q0, [sp, #4656]
	str	q1, [sp, #4672]
	ldp	q4, q3, [sp, #320]              ; 32-byte Folded Reload
	mov.16b	v0, v4
	ldr	q1, [sp, #5664]
	ldr	q2, [sp, #5680]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4688]
	str	q1, [sp, #4704]
	mov.16b	v0, v4
	ldr	q1, [sp, #5696]
	ldr	q2, [sp, #5712]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4720]
	str	q1, [sp, #4736]
	mov.16b	v0, v4
	ldr	q1, [sp, #5728]
	ldr	q2, [sp, #5744]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4752]
	str	q1, [sp, #4768]
	mov.16b	v0, v4
	ldr	q1, [sp, #5760]
	ldr	q2, [sp, #5776]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4784]
	str	q1, [sp, #4800]
	mov.16b	v0, v4
	ldr	q1, [sp, #5792]
	ldr	q2, [sp, #5808]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4816]
	str	q1, [sp, #4832]
	mov.16b	v0, v4
	ldr	q1, [sp, #5824]
	ldr	q2, [sp, #5840]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4848]
	str	q1, [sp, #4864]
	mov.16b	v0, v4
	ldr	q1, [sp, #5856]
	ldr	q2, [sp, #5872]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4880]
	str	q1, [sp, #4896]
	mov.16b	v0, v4
	ldr	q1, [sp, #5888]
	ldr	q2, [sp, #5904]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4912]
	str	q1, [sp, #4928]
	ldur	q0, [x26, #200]
	ldur	q1, [x26, #184]
	str	q1, [sp, #496]                  ; 16-byte Folded Spill
	str	q0, [sp, #4128]
	mov.16b	v0, v4
	ldr	q1, [sp, #5376]
	ldr	q2, [sp, #5392]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4144]
	str	q1, [sp, #4160]
	mov.16b	v0, v4
	ldr	q1, [sp, #5408]
	ldr	q2, [sp, #5424]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4176]
	str	q1, [sp, #4192]
	mov.16b	v0, v4
	ldr	q1, [sp, #5440]
	ldr	q2, [sp, #5456]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4208]
	str	q1, [sp, #4224]
	mov.16b	v0, v4
	ldr	q1, [sp, #5472]
	ldr	q2, [sp, #5488]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4240]
	str	q1, [sp, #4256]
	mov.16b	v0, v4
	ldr	q1, [sp, #5504]
	ldr	q2, [sp, #5520]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4272]
	str	q1, [sp, #4288]
	mov.16b	v0, v4
	ldr	q1, [sp, #5536]
	ldr	q2, [sp, #5552]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4304]
	str	q1, [sp, #4320]
	mov.16b	v0, v4
	ldr	q1, [sp, #5568]
	ldr	q2, [sp, #5584]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4336]
	str	q1, [sp, #4352]
	mov.16b	v0, v4
	ldr	q1, [sp, #5600]
	ldr	q2, [sp, #5616]
	fmla.2d	v0, v3, v1
	fmul.2d	v0, v0, v0
	mov.16b	v1, v4
	fmla.2d	v1, v3, v2
	fmul.2d	v1, v1, v1
	str	q0, [sp, #4368]
	str	q1, [sp, #4384]
	ldur	d0, [x24, #12]
	sshll.2d	v0, v0, #0
	scvtf.2d	v0, v0
	ldur	d1, [x24, #20]
	sshll.2d	v1, v1, #0
	scvtf.2d	v1, v1
	str	q0, [sp, #4944]
	str	q1, [sp, #4960]
	ldur	d0, [x24, #28]
	sshll.2d	v0, v0, #0
	scvtf.2d	v0, v0
	ldur	d1, [x24, #36]
	sshll.2d	v1, v1, #0
	scvtf.2d	v1, v1
	str	q0, [sp, #4976]
	str	q1, [sp, #4992]
	ldur	d0, [x24, #44]
	sshll.2d	v0, v0, #0
	scvtf.2d	v0, v0
	ldur	d1, [x24, #52]
	sshll.2d	v1, v1, #0
	scvtf.2d	v1, v1
	str	q0, [sp, #5008]
	str	q1, [sp, #5024]
	ldur	d0, [x24, #60]
	sshll.2d	v0, v0, #0
	scvtf.2d	v0, v0
	ldur	d1, [x24, #68]
	sshll.2d	v1, v1, #0
	scvtf.2d	v1, v1
	str	q0, [sp, #5040]
	str	q1, [sp, #5056]
	ldur	d0, [x24, #76]
	sshll.2d	v0, v0, #0
	scvtf.2d	v0, v0
	ldur	d1, [x24, #84]
	sshll.2d	v1, v1, #0
	scvtf.2d	v1, v1
	str	q0, [sp, #5072]
	str	q1, [sp, #5088]
	ldur	d0, [x24, #92]
	sshll.2d	v0, v0, #0
	scvtf.2d	v0, v0
	ldur	d1, [x24, #100]
	sshll.2d	v1, v1, #0
	scvtf.2d	v1, v1
	str	q0, [sp, #5104]
	str	q1, [sp, #5120]
	ldur	d0, [x24, #108]
	sshll.2d	v0, v0, #0
	scvtf.2d	v0, v0
	ldur	d1, [x24, #116]
	sshll.2d	v1, v1, #0
	scvtf.2d	v1, v1
	str	q0, [sp, #5136]
	str	q1, [sp, #5152]
	ldur	d0, [x24, #124]
	sshll.2d	v0, v0, #0
	scvtf.2d	v0, v0
	ldur	d1, [x24, #132]
	sshll.2d	v1, v1, #0
	scvtf.2d	v1, v1
	str	q0, [sp, #5168]
	str	q1, [sp, #5184]
	ldr	d0, [sp, #4680]
	ldr	q1, [sp, #4704]
	ldr	q2, [sp, #4688]
	ext.16b	v3, v2, v1, #8
	zip1.2d	v0, v0, v2
	fsub.2d	v0, v2, v0
	fsub.2d	v2, v1, v3
	str	q2, [sp, #4416]
	str	q0, [sp, #4400]
	ldr	q0, [sp, #4736]
	ldr	q2, [sp, #4720]
	dup.2d	v1, v1[1]
	ext.16b	v3, v2, v0, #8
	zip1.2d	v1, v1, v2
	fsub.2d	v1, v2, v1
	fsub.2d	v2, v0, v3
	str	q2, [sp, #4448]
	str	q1, [sp, #4432]
	ldr	q1, [sp, #4768]
	ldr	q2, [sp, #4752]
	dup.2d	v0, v0[1]
	ext.16b	v3, v2, v1, #8
	zip1.2d	v0, v0, v2
	fsub.2d	v0, v2, v0
	fsub.2d	v2, v1, v3
	str	q2, [sp, #4480]
	str	q0, [sp, #4464]
	ldr	q0, [sp, #4800]
	ldr	q2, [sp, #4784]
	dup.2d	v1, v1[1]
	ext.16b	v3, v2, v0, #8
	zip1.2d	v1, v1, v2
	fsub.2d	v1, v2, v1
	fsub.2d	v2, v0, v3
	str	q2, [sp, #4512]
	str	q1, [sp, #4496]
	ldr	q1, [sp, #4832]
	ldr	q2, [sp, #4816]
	dup.2d	v0, v0[1]
	ext.16b	v3, v2, v1, #8
	zip1.2d	v0, v0, v2
	fsub.2d	v0, v2, v0
	fsub.2d	v2, v1, v3
	str	q2, [sp, #4544]
	str	q0, [sp, #4528]
	ldr	q0, [sp, #4864]
	ldr	q2, [sp, #4848]
	dup.2d	v1, v1[1]
	ext.16b	v3, v2, v0, #8
	zip1.2d	v1, v1, v2
	fsub.2d	v1, v2, v1
	fsub.2d	v2, v0, v3
	str	q2, [sp, #4576]
	str	q1, [sp, #4560]
	ldr	q1, [sp, #4896]
	ldr	q2, [sp, #4880]
	dup.2d	v0, v0[1]
	ext.16b	v3, v2, v1, #8
	zip1.2d	v0, v0, v2
	fsub.2d	v0, v2, v0
	fsub.2d	v2, v1, v3
	str	q2, [sp, #4608]
	str	q0, [sp, #4592]
	mov	d0, v1[1]
	ldr	d1, [sp, #4912]
	ldr	d2, [sp, #4920]
	fsub	d0, d1, d0
	fsub	d1, d2, d1
	str	d0, [sp, #4624]
	str	d1, [sp, #4632]
	ldr	q0, [sp, #4928]
	zip1.2d	v1, v2, v0
	fsub.2d	v0, v0, v1
	str	q0, [sp, #4640]
	ldr	d0, [sp, #4136]
	ldr	q1, [sp, #4160]
	ldr	q2, [sp, #4144]
	ext.16b	v3, v2, v1, #8
	zip1.2d	v0, v0, v2
	fsub.2d	v0, v2, v0
	fsub.2d	v2, v1, v3
	str	q2, [sp, #3872]
	str	q0, [sp, #3856]
	ldr	q0, [sp, #4192]
	ldr	q2, [sp, #4176]
	dup.2d	v1, v1[1]
	ext.16b	v3, v2, v0, #8
	zip1.2d	v1, v1, v2
	fsub.2d	v1, v2, v1
	fsub.2d	v2, v0, v3
	str	q2, [sp, #3904]
	str	q1, [sp, #3888]
	ldr	q1, [sp, #4224]
	ldr	q2, [sp, #4208]
	dup.2d	v0, v0[1]
	ext.16b	v3, v2, v1, #8
	zip1.2d	v0, v0, v2
	fsub.2d	v0, v2, v0
	fsub.2d	v2, v1, v3
	str	q2, [sp, #3936]
	str	q0, [sp, #3920]
	ldr	q0, [sp, #4256]
	ldr	q2, [sp, #4240]
	dup.2d	v1, v1[1]
	ext.16b	v3, v2, v0, #8
	zip1.2d	v1, v1, v2
	fsub.2d	v1, v2, v1
	fsub.2d	v2, v0, v3
	str	q2, [sp, #3968]
	str	q1, [sp, #3952]
	ldr	q1, [sp, #4288]
	ldr	q2, [sp, #4272]
	dup.2d	v0, v0[1]
	ext.16b	v3, v2, v1, #8
	zip1.2d	v0, v0, v2
	fsub.2d	v0, v2, v0
	fsub.2d	v2, v1, v3
	str	q2, [sp, #4000]
	str	q0, [sp, #3984]
	ldr	q0, [sp, #4320]
	ldr	q2, [sp, #4304]
	dup.2d	v1, v1[1]
	ext.16b	v3, v2, v0, #8
	zip1.2d	v1, v1, v2
	fsub.2d	v1, v2, v1
	fsub.2d	v2, v0, v3
	str	q2, [sp, #4032]
	str	q1, [sp, #4016]
	ldr	q1, [sp, #4352]
	ldr	q2, [sp, #4336]
	dup.2d	v0, v0[1]
	ext.16b	v3, v2, v1, #8
	zip1.2d	v0, v0, v2
	fsub.2d	v0, v2, v0
	fsub.2d	v2, v1, v3
	str	q2, [sp, #4064]
	str	q0, [sp, #4048]
	mov	d0, v1[1]
	ldr	d1, [sp, #4368]
	ldr	d2, [sp, #4376]
	fsub	d0, d1, d0
	fsub	d1, d2, d1
	str	d0, [sp, #4080]
	str	d1, [sp, #4088]
	ldr	q0, [sp, #4384]
	zip1.2d	v1, v2, v0
	fsub.2d	v0, v0, v1
	str	q0, [sp, #4096]
	ldr	x14, [sp, #424]                 ; 8-byte Folded Reload
	ldp	w8, w9, [x14]
	add	w8, w9, w8
	sub	w10, w7, w8
	and	w9, w8, #0xfff
	ldr	d0, [sp, #4944]
	ldr	d3, [sp, #4944]
	ldr	q15, [sp, #352]                 ; 16-byte Folded Reload
	fmul	d0, d15, d0
	ldr	d1, [sp, #3856]
	ldr	d2, [sp, #3864]
	fmul	d0, d0, d1
	str	d0, [x20, w9, uxtw #3]
	ldr	d0, [sp, #4952]
	ldr	d1, [sp, #4952]
	stp	d3, d1, [sp, #480]              ; 16-byte Folded Spill
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #1
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #4960]
	ldr	d3, [sp, #4960]
	fmul	d0, d15, d0
	ldr	d1, [sp, #3872]
	ldr	d2, [sp, #3880]
	fmul	d0, d0, d1
	add	w11, w8, #2
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #4968]
	ldr	d1, [sp, #4968]
	stp	d1, d3, [sp, #464]              ; 16-byte Folded Spill
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #3
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #4976]
	ldr	d3, [sp, #4976]
	fmul	d0, d15, d0
	ldr	d1, [sp, #3888]
	ldr	d2, [sp, #3896]
	fmul	d0, d0, d1
	add	w11, w8, #4
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #4984]
	ldr	d1, [sp, #4984]
	stp	d1, d3, [sp, #448]              ; 16-byte Folded Spill
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #5
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #4992]
	ldr	d3, [sp, #4992]
	fmul	d0, d15, d0
	ldr	d1, [sp, #3904]
	ldr	d2, [sp, #3912]
	fmul	d0, d0, d1
	add	w11, w8, #6
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5000]
	ldr	d1, [sp, #5000]
	stp	d1, d3, [sp, #432]              ; 16-byte Folded Spill
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #7
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5008]
	ldr	d17, [sp, #5008]
	fmul	d0, d15, d0
	ldr	d1, [sp, #3920]
	ldr	d2, [sp, #3928]
	fmul	d0, d0, d1
	add	w11, w8, #8
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5016]
	ldr	d18, [sp, #5016]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #9
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5024]
	ldr	d19, [sp, #5024]
	fmul	d0, d15, d0
	ldr	d1, [sp, #3936]
	ldr	d2, [sp, #3944]
	fmul	d0, d0, d1
	add	w11, w8, #10
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5032]
	ldr	d20, [sp, #5032]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #11
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5040]
	ldr	d21, [sp, #5040]
	fmul	d0, d15, d0
	ldr	d1, [sp, #3952]
	ldr	d2, [sp, #3960]
	fmul	d0, d0, d1
	add	w11, w8, #12
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5048]
	ldr	d22, [sp, #5048]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #13
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5056]
	ldr	d23, [sp, #5056]
	fmul	d0, d15, d0
	ldr	d1, [sp, #3968]
	ldr	d2, [sp, #3976]
	fmul	d0, d0, d1
	add	w11, w8, #14
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5064]
	ldr	d24, [sp, #5064]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #15
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5072]
	ldr	d25, [sp, #5072]
	fmul	d0, d15, d0
	ldr	d1, [sp, #3984]
	ldr	d2, [sp, #3992]
	fmul	d0, d0, d1
	add	w11, w8, #16
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5080]
	ldr	d26, [sp, #5080]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #17
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5088]
	ldr	d27, [sp, #5088]
	fmul	d0, d15, d0
	ldr	d1, [sp, #4000]
	ldr	d2, [sp, #4008]
	fmul	d0, d0, d1
	add	w11, w8, #18
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5096]
	ldr	d28, [sp, #5096]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #19
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5104]
	ldr	d29, [sp, #5104]
	fmul	d0, d15, d0
	ldr	d1, [sp, #4016]
	ldr	d2, [sp, #4024]
	fmul	d0, d0, d1
	add	w11, w8, #20
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5112]
	ldr	d30, [sp, #5112]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #21
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5120]
	ldr	d31, [sp, #5120]
	fmul	d0, d15, d0
	ldr	d1, [sp, #4032]
	ldr	d2, [sp, #4040]
	fmul	d0, d0, d1
	add	w11, w8, #22
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5128]
	ldr	d16, [sp, #5128]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #23
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5136]
	ldr	d10, [sp, #5136]
	fmul	d0, d15, d0
	ldr	d1, [sp, #4048]
	ldr	d2, [sp, #4056]
	fmul	d0, d0, d1
	add	w11, w8, #24
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5144]
	ldr	d7, [sp, #5144]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #25
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5152]
	ldr	d11, [sp, #5152]
	fmul	d0, d15, d0
	ldr	d1, [sp, #4064]
	ldr	d2, [sp, #4072]
	fmul	d0, d0, d1
	add	w11, w8, #26
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5160]
	ldr	d12, [sp, #5160]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #27
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5168]
	ldr	d6, [sp, #5168]
	fmul	d0, d15, d0
	ldr	d1, [sp, #4080]
	ldr	d2, [sp, #4088]
	fmul	d0, d0, d1
	add	w11, w8, #28
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5176]
	ldr	d5, [sp, #5176]
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w11, w8, #29
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d0, [sp, #5184]
	ldr	d4, [sp, #5184]
	fmul	d0, d15, d0
	ldr	d2, [sp, #4096]
	ldr	d1, [sp, #4104]
	fmul	d0, d0, d2
	add	w11, w8, #30
	and	w11, w11, #0xfff
	str	d0, [x20, w11, uxtw #3]
	ldr	d2, [sp, #5192]
	ldr	d3, [sp, #5192]
	fmul	d2, d15, d2
	fmul	d1, d2, d1
	add	w11, w8, #31
	and	w11, w11, #0xfff
	str	d1, [x20, w11, uxtw #3]
	ldr	q15, [sp, #368]                 ; 16-byte Folded Reload
	ldr	d0, [sp, #480]                  ; 8-byte Folded Reload
	fmul	d1, d15, d0
	ldr	d2, [sp, #4400]
	ldr	d0, [sp, #4408]
	fmul	d1, d1, d2
	ldp	w11, w12, [x27]
	add	w12, w12, w11
	and	w11, w12, #0xfff
	str	d1, [x22, w11, uxtw #3]
	ldr	d1, [sp, #488]                  ; 8-byte Folded Reload
	fmul	d1, d15, d1
	fmul	d0, d1, d0
	add	w13, w12, #1
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	ldr	d0, [sp, #472]                  ; 8-byte Folded Reload
	fmul	d0, d15, d0
	ldr	d1, [sp, #4416]
	ldr	d2, [sp, #4424]
	fmul	d0, d0, d1
	add	w13, w12, #2
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	ldr	d0, [sp, #464]                  ; 8-byte Folded Reload
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w13, w12, #3
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	ldr	d0, [sp, #456]                  ; 8-byte Folded Reload
	fmul	d0, d15, d0
	ldr	d1, [sp, #4432]
	ldr	d2, [sp, #4440]
	fmul	d0, d0, d1
	add	w13, w12, #4
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	ldr	d0, [sp, #448]                  ; 8-byte Folded Reload
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w13, w12, #5
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	ldr	d0, [sp, #440]                  ; 8-byte Folded Reload
	fmul	d0, d15, d0
	ldr	d1, [sp, #4448]
	ldr	d2, [sp, #4456]
	fmul	d0, d0, d1
	add	w13, w12, #6
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	ldr	d0, [sp, #432]                  ; 8-byte Folded Reload
	fmul	d0, d15, d0
	fmul	d0, d0, d2
	add	w13, w12, #7
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d17
	ldr	d1, [sp, #4464]
	ldr	d2, [sp, #4472]
	fmul	d0, d0, d1
	add	w13, w12, #8
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d18
	fmul	d0, d0, d2
	add	w13, w12, #9
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d19
	ldr	d1, [sp, #4480]
	ldr	d2, [sp, #4488]
	fmul	d0, d0, d1
	add	w13, w12, #10
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d20
	fmul	d0, d0, d2
	add	w13, w12, #11
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d21
	ldr	d1, [sp, #4496]
	ldr	d2, [sp, #4504]
	fmul	d0, d0, d1
	add	w13, w12, #12
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d22
	fmul	d0, d0, d2
	add	w13, w12, #13
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d23
	ldr	d1, [sp, #4512]
	ldr	d2, [sp, #4520]
	fmul	d0, d0, d1
	add	w13, w12, #14
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d24
	fmul	d0, d0, d2
	add	w13, w12, #15
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d25
	ldr	d1, [sp, #4528]
	ldr	d2, [sp, #4536]
	fmul	d0, d0, d1
	add	w13, w12, #16
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d26
	fmul	d0, d0, d2
	add	w13, w12, #17
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d27
	ldr	d1, [sp, #4544]
	ldr	d2, [sp, #4552]
	fmul	d0, d0, d1
	add	w13, w12, #18
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d28
	fmul	d0, d0, d2
	add	w13, w12, #19
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d29
	ldr	d1, [sp, #4560]
	ldr	d2, [sp, #4568]
	fmul	d0, d0, d1
	add	w13, w12, #20
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d30
	fmul	d0, d0, d2
	add	w13, w12, #21
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d31
	ldr	d1, [sp, #4576]
	ldr	d2, [sp, #4584]
	fmul	d0, d0, d1
	add	w13, w12, #22
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d16
	fmul	d0, d0, d2
	add	w13, w12, #23
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d10
	ldr	d1, [sp, #4592]
	ldr	d2, [sp, #4600]
	fmul	d0, d0, d1
	add	w13, w12, #24
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d7
	fmul	d0, d0, d2
	add	w13, w12, #25
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d11
	ldr	d1, [sp, #4608]
	ldr	d2, [sp, #4616]
	fmul	d0, d0, d1
	add	w13, w12, #26
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d12
	fmul	d0, d0, d2
	add	w13, w12, #27
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d6
	ldr	d1, [sp, #4624]
	ldr	d2, [sp, #4632]
	fmul	d0, d0, d1
	add	w13, w12, #28
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d5
	fmul	d0, d0, d2
	add	w13, w12, #29
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d4
	ldr	d1, [sp, #4640]
	ldr	d2, [sp, #4648]
	fmul	d0, d0, d1
	add	w13, w12, #30
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	fmul	d0, d15, d3
	fmul	d0, d0, d2
	add	w13, w12, #31
	and	w13, w13, #0xfff
	str	d0, [x22, w13, uxtw #3]
	add	x15, sp, #1, lsl #12            ; =4096
	add	x15, x15, #1104
	ldur	q0, [x24, #128]
	stur	q0, [x26, #136]
	add	x13, sp, #1, lsl #12            ; =4096
	add	x13, x13, #560
	ldp	q0, q1, [x13, #256]
	stur	q0, [x26, #152]
	stur	q1, [x26, #168]
	ldr	q0, [sp, #496]                  ; 16-byte Folded Reload
	str	q0, [sp, #4112]
	add	x13, sp, #1, lsl #12            ; =4096
	add	x13, x13, #16
	ldp	q0, q1, [x13, #256]
	stur	q1, [x26, #200]
	stur	q0, [x26, #184]
	mov	w13, #32                        ; =0x20
	stp	w9, w13, [x14]
	stp	w11, w13, [x27]
	and	w10, w10, #0xfff
	ldr	d0, [x26, #128]
	cmp	w10, #31
	b.lo	LBB17_9
; %bb.4:                                ;   in Loop: Header=BB17_3 Depth=1
	sub	w10, w12, w21
	and	w10, w10, #0xfff
	cmp	w10, #4064
	b.hi	LBB17_9
; %bb.5:                                ;   in Loop: Header=BB17_3 Depth=1
	sub	w10, w21, w12
	and	w10, w10, #0xfff
	cmp	w10, #31
	b.lo	LBB17_9
; %bb.6:                                ;   in Loop: Header=BB17_3 Depth=1
	sub	w8, w8, w7
	and	w8, w8, #0xfff
	cmp	w8, #4065
	b.hs	LBB17_9
; %bb.7:                                ;   in Loop: Header=BB17_3 Depth=1
	mov	x8, #0                          ; =0x0
	ldr	w10, [sp, #172]                 ; 4-byte Folded Reload
	add	w10, w10, w11
	ldr	w11, [sp, #168]                 ; 4-byte Folded Reload
	add	w9, w11, w9
	ldr	d5, [sp, #304]                  ; 8-byte Folded Reload
	ldp	q7, q6, [sp, #384]              ; 32-byte Folded Reload
	ldr	x14, [sp, #232]                 ; 8-byte Folded Reload
	ldp	q17, q16, [sp, #64]             ; 32-byte Folded Reload
	ldp	q19, q18, [sp, #32]             ; 32-byte Folded Reload
	add	x12, sp, #1, lsl #12            ; =4096
	add	x12, x12, #848
	add	x13, sp, #1, lsl #12            ; =4096
	add	x13, x13, #304
	add	x16, sp, #3856
LBB17_8:                                ;   Parent Loop BB17_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	q1, [x12, x8]
	fmul.2d	v1, v1, v0[0]
	ldr	q2, [x13, x8]
	ldr	q3, [x16, x8]
	fmul.2d	v3, v3, v6[0]
	fmla.2d	v3, v2, v16
	sub	w11, w9, #1
	and	w11, w11, #0xfff
	ubfiz	x11, x11, #3, #32
	ldr	q2, [x20, x11]
	and	w11, w10, #0xfff
	ubfiz	x11, x11, #3, #32
	ldr	q4, [x22, x11]
	fmul.2d	v4, v4, v7[0]
	fmla.2d	v4, v2, v17
	sub	w11, w10, #1
	and	w11, w11, #0xfff
	ubfiz	x11, x11, #3, #32
	ldr	q2, [x22, x11]
	fmla.2d	v4, v2, v18
	and	w11, w9, #0xfff
	ubfiz	x11, x11, #3, #32
	ldr	q2, [x20, x11]
	fmla.2d	v4, v2, v19
	fneg.2d	v2, v4
	fmla.2d	v2, v3, v1
	str	q2, [x23, x8]
	add	w10, w10, #2
	add	w9, w9, #2
	add	x8, x8, #16
	cmp	x8, #256
	b.ne	LBB17_8
	b	LBB17_11
LBB17_9:                                ;   in Loop: Header=BB17_3 Depth=1
	mov	x8, #0                          ; =0x0
	ldp	w13, w10, [sp, #168]            ; 8-byte Folded Reload
	add	w10, w10, w11
	ldp	w12, w14, [sp, #24]             ; 8-byte Folded Reload
	add	w11, w14, w11
	add	w12, w12, w9
	add	w9, w13, w9
	ldr	d5, [sp, #304]                  ; 8-byte Folded Reload
	ldp	q16, q6, [sp, #128]             ; 32-byte Folded Reload
	ldp	q17, q7, [sp, #384]             ; 32-byte Folded Reload
	ldp	q19, q18, [sp, #96]             ; 32-byte Folded Reload
	ldr	x14, [sp, #232]                 ; 8-byte Folded Reload
	add	x16, sp, #1, lsl #12            ; =4096
	add	x16, x16, #848
	add	x17, sp, #1, lsl #12            ; =4096
	add	x17, x17, #304
	add	x0, sp, #3856
LBB17_10:                               ;   Parent Loop BB17_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	d1, [x16, x8, lsl #3]
	ldr	d2, [x17, x8, lsl #3]
	ldr	d3, [x0, x8, lsl #3]
	fmul	d3, d7, d3
	fmadd	d2, d6, d2, d3
	add	w13, w12, w8
	and	w13, w13, #0xfff
	ldr	d3, [x20, w13, uxtw #3]
	add	w13, w10, w8
	and	w13, w13, #0xfff
	ldr	d4, [x22, w13, uxtw #3]
	fmul	d4, d17, d4
	fmadd	d3, d16, d3, d4
	add	w13, w11, w8
	and	w13, w13, #0xfff
	ldr	d4, [x22, w13, uxtw #3]
	fmul	d1, d0, d1
	fmadd	d3, d18, d4, d3
	add	w13, w9, w8
	and	w13, w13, #0xfff
	ldr	d4, [x20, w13, uxtw #3]
	fmadd	d3, d19, d4, d3
	fnmsub	d1, d1, d2, d3
	str	d1, [x23, x8, lsl #3]
	add	x8, x8, #1
	cmp	x8, #32
	b.ne	LBB17_10
LBB17_11:                               ;   in Loop: Header=BB17_3 Depth=1
	mov	x8, #0                          ; =0x0
	ldr	x10, [sp, #256]                 ; 8-byte Folded Reload
	ldp	q1, q0, [x10]
	str	q0, [sp, #3328]
	str	q1, [sp, #3312]
	ldr	d0, [sp, #3336]
	ldr	d1, [sp, #3600]
	ldr	d2, [sp, #3608]
	fmadd	d0, d5, d1, d0
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3344]
	str	d1, [sp, #3352]
	ldr	d0, [sp, #3616]
	ldr	d2, [sp, #3624]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3360]
	str	d1, [sp, #3368]
	ldr	d0, [sp, #3632]
	ldr	d2, [sp, #3640]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3376]
	str	d1, [sp, #3384]
	ldr	d0, [sp, #3648]
	ldr	d2, [sp, #3656]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3392]
	str	d1, [sp, #3400]
	ldr	d0, [sp, #3664]
	ldr	d2, [sp, #3672]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3408]
	str	d1, [sp, #3416]
	ldr	d0, [sp, #3680]
	ldr	d2, [sp, #3688]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3424]
	str	d1, [sp, #3432]
	ldr	d0, [sp, #3696]
	ldr	d2, [sp, #3704]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3440]
	str	d1, [sp, #3448]
	ldr	d0, [sp, #3712]
	ldr	d2, [sp, #3720]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3456]
	str	d1, [sp, #3464]
	ldr	d0, [sp, #3728]
	ldr	d2, [sp, #3736]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3472]
	str	d1, [sp, #3480]
	ldr	d0, [sp, #3744]
	ldr	d2, [sp, #3752]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3488]
	str	d1, [sp, #3496]
	ldr	d0, [sp, #3760]
	ldr	d2, [sp, #3768]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3504]
	str	d1, [sp, #3512]
	ldr	d0, [sp, #3776]
	ldr	d2, [sp, #3784]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3520]
	str	d1, [sp, #3528]
	ldr	d0, [sp, #3792]
	ldr	d2, [sp, #3800]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3536]
	str	d1, [sp, #3544]
	ldr	d0, [sp, #3808]
	ldr	d2, [sp, #3816]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3552]
	str	d1, [sp, #3560]
	ldr	d0, [sp, #3824]
	ldr	d2, [sp, #3832]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3568]
	str	d1, [sp, #3576]
	ldr	d0, [sp, #3840]
	ldr	d2, [sp, #3848]
	fmadd	d0, d5, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d5, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3584]
	str	d1, [sp, #3592]
	add	x9, sp, #3312
	ldp	q0, q1, [x9, #256]
	stp	q0, q1, [x10]
	ldr	x10, [sp, #248]                 ; 8-byte Folded Reload
	ldp	q0, q1, [x10]
	str	q1, [sp, #3040]
	str	q0, [sp, #3024]
	ldr	d0, [sp, #3048]
	ldr	d1, [sp, #3344]
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	ldr	d1, [sp, #3352]
	ldr	d2, [sp, #3360]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3056]
	str	d1, [sp, #3064]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3368]
	ldr	d2, [sp, #3376]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3072]
	str	d1, [sp, #3080]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3384]
	ldr	d2, [sp, #3392]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3088]
	str	d1, [sp, #3096]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3400]
	ldr	d2, [sp, #3408]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3104]
	str	d1, [sp, #3112]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3416]
	ldr	d2, [sp, #3424]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3120]
	str	d1, [sp, #3128]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3432]
	ldr	d2, [sp, #3440]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3136]
	str	d1, [sp, #3144]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3448]
	ldr	d2, [sp, #3456]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3152]
	str	d1, [sp, #3160]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3464]
	ldr	d2, [sp, #3472]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3168]
	str	d1, [sp, #3176]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3480]
	ldr	d2, [sp, #3488]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3184]
	str	d1, [sp, #3192]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3496]
	ldr	d2, [sp, #3504]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3200]
	str	d1, [sp, #3208]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3512]
	ldr	d2, [sp, #3520]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3216]
	str	d1, [sp, #3224]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3528]
	ldr	d2, [sp, #3536]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3232]
	str	d1, [sp, #3240]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3544]
	ldr	d2, [sp, #3552]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3248]
	str	d1, [sp, #3256]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3560]
	ldr	d2, [sp, #3568]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3264]
	str	d1, [sp, #3272]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3576]
	ldr	d2, [sp, #3584]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3280]
	str	d1, [sp, #3288]
	fmadd	d0, d8, d2, d1
	fmul	d0, d9, d0
	ldr	d1, [sp, #3592]
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #3296]
	str	d1, [sp, #3304]
	add	x9, sp, #3024
	ldp	q0, q1, [x9, #256]
	stp	q0, q1, [x10]
	ldr	q0, [sp, #3344]
	fmul.2d	v1, v0, v0
	fmul.2d	v0, v0, v1
	ldr	q1, [sp, #3360]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	str	q0, [sp, #2192]
	str	q1, [sp, #2208]
	ldr	q0, [sp, #3376]
	fmul.2d	v1, v0, v0
	fmul.2d	v0, v0, v1
	ldr	q1, [sp, #3392]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	str	q0, [sp, #2224]
	str	q1, [sp, #2240]
	ldr	q0, [sp, #3408]
	fmul.2d	v1, v0, v0
	fmul.2d	v0, v0, v1
	ldr	q1, [sp, #3424]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	str	q0, [sp, #2256]
	str	q1, [sp, #2272]
	ldr	q0, [sp, #3440]
	fmul.2d	v1, v0, v0
	fmul.2d	v0, v0, v1
	ldr	q1, [sp, #3456]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	str	q0, [sp, #2288]
	str	q1, [sp, #2304]
	ldr	q0, [sp, #3472]
	fmul.2d	v1, v0, v0
	fmul.2d	v0, v0, v1
	ldr	q1, [sp, #3488]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	str	q0, [sp, #2320]
	str	q1, [sp, #2336]
	ldr	q0, [sp, #3504]
	fmul.2d	v1, v0, v0
	fmul.2d	v0, v0, v1
	ldr	q1, [sp, #3520]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	str	q0, [sp, #2352]
	str	q1, [sp, #2368]
	ldr	q0, [sp, #3536]
	fmul.2d	v1, v0, v0
	fmul.2d	v0, v0, v1
	ldr	q1, [sp, #3552]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	str	q0, [sp, #2384]
	str	q1, [sp, #2400]
	ldr	q0, [sp, #3568]
	fmul.2d	v1, v0, v0
	fmul.2d	v0, v0, v1
	ldr	q1, [sp, #3584]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	str	q0, [sp, #2416]
	str	q1, [sp, #2432]
	ldr	x11, [sp, #240]                 ; 8-byte Folded Reload
	ldp	q0, q1, [x11]
	str	q1, [sp, #2752]
	str	q0, [sp, #2736]
	ldr	d0, [sp, #2760]
	ldr	d1, [sp, #3056]
	ldr	d2, [sp, #3064]
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	fmadd	d1, d8, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #2768]
	str	d1, [sp, #2776]
	ldr	d0, [sp, #3072]
	ldr	d2, [sp, #3080]
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d8, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #2784]
	str	d1, [sp, #2792]
	ldr	d0, [sp, #3088]
	ldr	d2, [sp, #3096]
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d8, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #2800]
	str	d1, [sp, #2808]
	ldr	d0, [sp, #3104]
	ldr	d2, [sp, #3112]
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d8, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #2816]
	str	d1, [sp, #2824]
	ldr	d0, [sp, #3120]
	ldr	d2, [sp, #3128]
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d8, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #2832]
	str	d1, [sp, #2840]
	ldr	d0, [sp, #3136]
	ldr	d2, [sp, #3144]
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d8, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #2848]
	str	d1, [sp, #2856]
	ldr	d0, [sp, #3152]
	ldr	d2, [sp, #3160]
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d8, d2, d0
	fmul	d1, d9, d1
	str	d0, [sp, #2864]
	str	d1, [sp, #2872]
	ldr	d0, [sp, #3168]
	ldr	d2, [sp, #3176]
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fmadd	d1, d8, d2, d0
	fmul	d2, d9, d1
	str	d0, [sp, #2880]
	str	d2, [sp, #2888]
	ldr	q0, [sp, #3184]
	ldr	q1, [sp, #3200]
	fmadd	d2, d8, d0, d2
	fmul	d2, d9, d2
	str	d2, [sp, #2896]
	fmla.d	d2, d8, v0[1]
	fmul	d2, d9, d2
	fmadd	d3, d8, d1, d2
	fmul	d3, d9, d3
	str	d2, [sp, #2904]
	str	d3, [sp, #2912]
	fmla.d	d3, d8, v1[1]
	fmul	d3, d9, d3
	ldr	d2, [sp, #3216]
	ldr	d4, [sp, #3224]
	fmadd	d5, d8, d2, d3
	fmul	d5, d9, d5
	str	d3, [sp, #2920]
	str	d5, [sp, #2928]
	fmadd	d3, d8, d4, d5
	fmul	d3, d9, d3
	ldr	d4, [sp, #3232]
	ldr	d5, [sp, #3240]
	fmadd	d4, d8, d4, d3
	fmul	d4, d9, d4
	str	d3, [sp, #2936]
	str	d4, [sp, #2944]
	fmadd	d3, d8, d5, d4
	fmul	d3, d9, d3
	ldr	d4, [sp, #3248]
	ldr	d5, [sp, #3256]
	fmadd	d4, d8, d4, d3
	fmul	d4, d9, d4
	str	d3, [sp, #2952]
	str	d4, [sp, #2960]
	fmadd	d3, d8, d5, d4
	fmul	d3, d9, d3
	ldr	d4, [sp, #3264]
	ldr	d5, [sp, #3272]
	fmadd	d4, d8, d4, d3
	fmul	d4, d9, d4
	str	d3, [sp, #2968]
	str	d4, [sp, #2976]
	fmadd	d3, d8, d5, d4
	fmul	d3, d9, d3
	ldr	d4, [sp, #3280]
	ldr	d5, [sp, #3288]
	fmadd	d4, d8, d4, d3
	fmul	d4, d9, d4
	str	d3, [sp, #2984]
	str	d4, [sp, #2992]
	fmadd	d3, d8, d5, d4
	fmul	d3, d9, d3
	ldr	d4, [sp, #3296]
	ldr	d5, [sp, #3304]
	fmadd	d4, d8, d4, d3
	fmul	d4, d9, d4
	str	d3, [sp, #3000]
	str	d4, [sp, #3008]
	fmadd	d3, d8, d5, d4
	fmul	d3, d9, d3
	str	d3, [sp, #3016]
	add	x10, sp, #2736
	ldp	q3, q4, [x10, #256]
	stp	q3, q4, [x11]
	ldp	q3, q4, [x14]
	str	q4, [sp, #1920]
	str	q3, [sp, #1904]
	ldr	d3, [sp, #1928]
	ldr	x27, [sp, #520]                 ; 8-byte Folded Reload
	ldp	x24, x26, [sp, #272]            ; 16-byte Folded Reload
	add	x10, sp, #2192
LBB17_12:                               ;   Parent Loop BB17_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	d4, [x23, x8]
	fmul	d4, d4, d13
	fmul	d5, d4, d4
	fmul	d4, d4, d5
	ldr	d5, [x10, x8]
	fsub	d4, d4, d5
	fmadd	d3, d8, d4, d3
	fmul	d3, d9, d3
	str	d3, [x28, x8]
	add	x8, x8, #8
	cmp	x8, #256
	b.ne	LBB17_12
; %bb.13:                               ;   in Loop: Header=BB17_3 Depth=1
	mov	x8, #0                          ; =0x0
	add	x10, sp, #1904
	ldp	q3, q4, [x10, #256]
	stp	q3, q4, [x14]
	ldr	q3, [sp, #3056]
	ldr	q4, [sp, #3072]
	fmul.2d	v5, v3, v3
	fmul.2d	v3, v3, v5
	fmul.2d	v5, v4, v4
	fmul.2d	v4, v4, v5
	str	q3, [sp, #1648]
	str	q4, [sp, #1664]
	ldr	q3, [sp, #3088]
	ldr	q4, [sp, #3104]
	fmul.2d	v5, v3, v3
	fmul.2d	v3, v3, v5
	fmul.2d	v5, v4, v4
	fmul.2d	v4, v4, v5
	str	q3, [sp, #1680]
	str	q4, [sp, #1696]
	ldr	q3, [sp, #3120]
	ldr	q4, [sp, #3136]
	fmul.2d	v5, v3, v3
	fmul.2d	v3, v3, v5
	fmul.2d	v5, v4, v4
	fmul.2d	v4, v4, v5
	str	q3, [sp, #1712]
	str	q4, [sp, #1728]
	ldr	q3, [sp, #3152]
	ldr	q4, [sp, #3168]
	fmul.2d	v5, v3, v3
	fmul.2d	v3, v3, v5
	fmul.2d	v5, v4, v4
	fmul.2d	v4, v4, v5
	str	q3, [sp, #1744]
	str	q4, [sp, #1760]
	fmul.2d	v3, v0, v0
	fmul.2d	v0, v0, v3
	fmul.2d	v3, v1, v1
	fmul.2d	v1, v1, v3
	str	q0, [sp, #1776]
	str	q1, [sp, #1792]
	fmul	d0, d2, d2
	fmul	d0, d2, d0
	ldur	q1, [x9, #200]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	add	x10, sp, #1648
	stur	q1, [x10, #168]
	ldur	q1, [x9, #216]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	stur	q1, [x10, #184]
	ldur	q1, [x9, #232]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	stur	q1, [x10, #200]
	ldur	q1, [x9, #248]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	stur	q1, [x10, #216]
	ldr	x9, [sp, #192]                  ; 8-byte Folded Reload
	ldr	q1, [x9]
	fmul.2d	v2, v1, v1
	fmul.2d	v1, v1, v2
	stur	q1, [x10, #232]
	ldr	d1, [sp, #3304]
	fmul	d2, d1, d1
	fmul	d1, d1, d2
	str	d0, [sp, #1808]
	str	d1, [sp, #1896]
	ldr	x10, [sp, #224]                 ; 8-byte Folded Reload
	ldp	q0, q1, [x10]
	str	q1, [sp, #1376]
	str	q0, [sp, #1360]
	ldr	d1, [sp, #1384]
	ldr	d3, [sp, #1936]
	ldr	d0, [sp, #1944]
	ldr	d4, [sp, #2192]
	ldr	d2, [sp, #2200]
	fadd	d3, d3, d4
	ldr	d4, [sp, #1648]
	ldr	d5, [sp, #1648]
	fsub	d3, d3, d4
	fmadd	d1, d8, d3, d1
	fmul	d1, d9, d1
	fadd	d0, d0, d2
	ldr	d2, [sp, #1656]
	ldr	d3, [sp, #1656]
	stp	d3, d5, [sp, #488]              ; 16-byte Folded Spill
	fsub	d0, d0, d2
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	str	d1, [sp, #1392]
	str	d0, [sp, #1400]
	ldr	d1, [sp, #1952]
	ldr	d2, [sp, #1960]
	ldr	d3, [sp, #2208]
	ldr	d4, [sp, #2216]
	fadd	d1, d1, d3
	ldr	d3, [sp, #1664]
	ldr	d5, [sp, #1664]
	fsub	d1, d1, d3
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1672]
	ldr	d3, [sp, #1672]
	stp	d3, d5, [sp, #472]              ; 16-byte Folded Spill
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1408]
	str	d1, [sp, #1416]
	ldr	d0, [sp, #1968]
	ldr	d2, [sp, #1976]
	ldr	d3, [sp, #2224]
	ldr	d4, [sp, #2232]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1680]
	ldr	d5, [sp, #1680]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1688]
	ldr	d3, [sp, #1688]
	stp	d3, d5, [sp, #456]              ; 16-byte Folded Spill
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1424]
	str	d1, [sp, #1432]
	ldr	d0, [sp, #1984]
	ldr	d2, [sp, #1992]
	ldr	d3, [sp, #2240]
	ldr	d4, [sp, #2248]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1696]
	ldr	d5, [sp, #1696]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1704]
	ldr	d3, [sp, #1704]
	stp	d3, d5, [sp, #440]              ; 16-byte Folded Spill
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1440]
	str	d1, [sp, #1448]
	ldr	d0, [sp, #2000]
	ldr	d2, [sp, #2008]
	ldr	d3, [sp, #2256]
	ldr	d4, [sp, #2264]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1712]
	ldr	d5, [sp, #1712]
	str	d5, [sp, #432]                  ; 8-byte Folded Spill
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1720]
	ldr	d17, [sp, #1720]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1456]
	str	d1, [sp, #1464]
	ldr	d0, [sp, #2016]
	ldr	d2, [sp, #2024]
	ldr	d3, [sp, #2272]
	ldr	d4, [sp, #2280]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1728]
	ldr	d18, [sp, #1728]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1736]
	ldr	d19, [sp, #1736]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1472]
	str	d1, [sp, #1480]
	ldr	d0, [sp, #2032]
	ldr	d2, [sp, #2040]
	ldr	d3, [sp, #2288]
	ldr	d4, [sp, #2296]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1744]
	ldr	d20, [sp, #1744]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1752]
	ldr	d21, [sp, #1752]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1488]
	str	d1, [sp, #1496]
	ldr	d0, [sp, #2048]
	ldr	d2, [sp, #2056]
	ldr	d3, [sp, #2304]
	ldr	d4, [sp, #2312]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1760]
	ldr	d22, [sp, #1760]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1768]
	ldr	d23, [sp, #1768]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1504]
	str	d1, [sp, #1512]
	ldr	d0, [sp, #2064]
	ldr	d2, [sp, #2072]
	ldr	d3, [sp, #2320]
	ldr	d4, [sp, #2328]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1776]
	ldr	d24, [sp, #1776]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1784]
	ldr	d25, [sp, #1784]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1520]
	str	d1, [sp, #1528]
	ldr	d0, [sp, #2080]
	ldr	d2, [sp, #2088]
	ldr	d3, [sp, #2336]
	ldr	d4, [sp, #2344]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1792]
	ldr	d26, [sp, #1792]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1800]
	ldr	d27, [sp, #1800]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1536]
	str	d1, [sp, #1544]
	ldr	d0, [sp, #2096]
	ldr	d2, [sp, #2104]
	ldr	d3, [sp, #2352]
	ldr	d4, [sp, #2360]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1808]
	ldr	d28, [sp, #1808]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1816]
	ldr	d29, [sp, #1816]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1552]
	str	d1, [sp, #1560]
	ldr	d0, [sp, #2112]
	ldr	d2, [sp, #2120]
	ldr	d3, [sp, #2368]
	ldr	d4, [sp, #2376]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1824]
	ldr	d30, [sp, #1824]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1832]
	ldr	d31, [sp, #1832]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1568]
	str	d1, [sp, #1576]
	ldr	d0, [sp, #2128]
	ldr	d2, [sp, #2136]
	ldr	d3, [sp, #2384]
	ldr	d4, [sp, #2392]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1840]
	ldr	d16, [sp, #1840]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fmul	d0, d9, d0
	fadd	d1, d2, d4
	ldr	d2, [sp, #1848]
	ldr	d7, [sp, #1848]
	fsub	d1, d1, d2
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1584]
	str	d1, [sp, #1592]
	ldr	d0, [sp, #2144]
	ldr	d2, [sp, #2152]
	ldr	d3, [sp, #2400]
	ldr	d4, [sp, #2408]
	fadd	d0, d0, d3
	ldr	d3, [sp, #1856]
	ldr	d6, [sp, #1856]
	fsub	d0, d0, d3
	fmadd	d0, d8, d0, d1
	fadd	d1, d2, d4
	ldr	d2, [sp, #1864]
	ldr	d5, [sp, #1864]
	fsub	d1, d1, d2
	ldr	d2, [sp, #2160]
	ldr	d11, [sp, #2168]
	ldr	d3, [sp, #2416]
	ldr	d12, [sp, #2424]
	fadd	d2, d2, d3
	ldr	d13, [sp, #1872]
	ldr	d4, [sp, #1872]
	fsub	d2, d2, d13
	fmul	d0, d9, d0
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1600]
	str	d1, [sp, #1608]
	fmadd	d0, d8, d2, d1
	fadd	d1, d11, d12
	ldr	d11, [sp, #1880]
	ldr	d3, [sp, #1880]
	fsub	d11, d1, d11
	ldr	d1, [sp, #2176]
	ldr	d12, [sp, #2184]
	ldr	d13, [sp, #2432]
	ldr	d10, [sp, #2440]
	fadd	d13, d1, d13
	ldr	d15, [sp, #1888]
	ldr	d2, [sp, #1888]
	fsub	d13, d13, d15
	fmul	d0, d9, d0
	fmadd	d11, d8, d11, d0
	fmul	d11, d9, d11
	str	d0, [sp, #1616]
	str	d11, [sp, #1624]
	fmadd	d11, d8, d13, d11
	fadd	d10, d12, d10
	ldr	d12, [sp, #1896]
	ldr	d1, [sp, #1896]
	fsub	d10, d10, d12
	fmul	d11, d9, d11
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	str	d11, [sp, #1632]
	str	d10, [sp, #1640]
	add	x9, sp, #1360
	ldp	q10, q11, [x9, #256]
	stp	q10, q11, [x10]
	ldr	q10, [sp, #2768]
	fmul.2d	v11, v10, v10
	fmul.2d	v10, v10, v11
	ldr	q11, [sp, #2784]
	fmul.2d	v12, v11, v11
	fmul.2d	v11, v11, v12
	str	q10, [sp, #1104]
	str	q11, [sp, #1120]
	ldr	q10, [sp, #2800]
	fmul.2d	v11, v10, v10
	fmul.2d	v10, v10, v11
	ldr	q11, [sp, #2816]
	fmul.2d	v12, v11, v11
	fmul.2d	v11, v11, v12
	str	q10, [sp, #1136]
	str	q11, [sp, #1152]
	ldr	q10, [sp, #2832]
	fmul.2d	v11, v10, v10
	fmul.2d	v10, v10, v11
	ldr	q11, [sp, #2848]
	fmul.2d	v12, v11, v11
	fmul.2d	v11, v11, v12
	str	q10, [sp, #1168]
	str	q11, [sp, #1184]
	ldr	q10, [sp, #2864]
	fmul.2d	v11, v10, v10
	fmul.2d	v10, v10, v11
	ldr	q11, [sp, #2880]
	fmul.2d	v12, v11, v11
	fmul.2d	v11, v11, v12
	str	q10, [sp, #1200]
	str	q11, [sp, #1216]
	ldr	q10, [sp, #2896]
	fmul.2d	v11, v10, v10
	fmul.2d	v10, v10, v11
	ldr	q11, [sp, #2912]
	fmul.2d	v12, v11, v11
	fmul.2d	v11, v11, v12
	str	q10, [sp, #1232]
	str	q11, [sp, #1248]
	ldr	q10, [sp, #2928]
	fmul.2d	v11, v10, v10
	fmul.2d	v10, v10, v11
	ldr	q11, [sp, #2944]
	fmul.2d	v12, v11, v11
	fmul.2d	v11, v11, v12
	str	q10, [sp, #1264]
	str	q11, [sp, #1280]
	ldr	q10, [sp, #2960]
	fmul.2d	v11, v10, v10
	fmul.2d	v10, v10, v11
	ldr	q11, [sp, #2976]
	fmul.2d	v12, v11, v11
	fmul.2d	v11, v11, v12
	str	q10, [sp, #1296]
	str	q11, [sp, #1312]
	ldr	q10, [sp, #2992]
	fmul.2d	v11, v10, v10
	fmul.2d	v10, v10, v11
	ldr	q11, [sp, #3008]
	fmul.2d	v12, v11, v11
	fmul.2d	v11, v11, v12
	str	q10, [sp, #1328]
	str	q11, [sp, #1344]
	ldr	x10, [sp, #216]                 ; 8-byte Folded Reload
	ldp	q10, q11, [x10]
	str	q11, [sp, #2464]
	str	q10, [sp, #2448]
	ldr	d10, [sp, #2472]
	ldr	d11, [sp, #2768]
	ldr	d12, [sp, #2776]
	fmadd	d10, d8, d11, d10
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2480]
	str	d11, [sp, #2488]
	ldr	d10, [sp, #2784]
	ldr	d12, [sp, #2792]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2496]
	str	d11, [sp, #2504]
	ldr	d10, [sp, #2800]
	ldr	d12, [sp, #2808]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2512]
	str	d11, [sp, #2520]
	ldr	d10, [sp, #2816]
	ldr	d12, [sp, #2824]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2528]
	str	d11, [sp, #2536]
	ldr	d10, [sp, #2832]
	ldr	d12, [sp, #2840]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2544]
	str	d11, [sp, #2552]
	ldr	d10, [sp, #2848]
	ldr	d12, [sp, #2856]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2560]
	str	d11, [sp, #2568]
	ldr	d10, [sp, #2864]
	ldr	d12, [sp, #2872]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2576]
	str	d11, [sp, #2584]
	ldr	d10, [sp, #2880]
	ldr	d12, [sp, #2888]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2592]
	str	d11, [sp, #2600]
	ldr	d10, [sp, #2896]
	ldr	d12, [sp, #2904]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2608]
	str	d11, [sp, #2616]
	ldr	d10, [sp, #2912]
	ldr	d12, [sp, #2920]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2624]
	str	d11, [sp, #2632]
	ldr	d10, [sp, #2928]
	ldr	d12, [sp, #2936]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2640]
	str	d11, [sp, #2648]
	ldr	d10, [sp, #2944]
	ldr	d12, [sp, #2952]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2656]
	str	d11, [sp, #2664]
	ldr	d10, [sp, #2960]
	ldr	d12, [sp, #2968]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2672]
	str	d11, [sp, #2680]
	ldr	d10, [sp, #2976]
	ldr	d12, [sp, #2984]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2688]
	str	d11, [sp, #2696]
	ldr	d10, [sp, #2992]
	ldr	d12, [sp, #3000]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2704]
	str	d11, [sp, #2712]
	ldr	d10, [sp, #3008]
	ldr	d12, [sp, #3016]
	fmadd	d10, d8, d10, d11
	fmul	d10, d9, d10
	fmadd	d11, d8, d12, d10
	fmul	d11, d9, d11
	str	d10, [sp, #2720]
	str	d11, [sp, #2728]
	add	x9, sp, #2448
	ldp	q10, q11, [x9, #256]
	stp	q10, q11, [x10]
	ldr	x10, [sp, #208]                 ; 8-byte Folded Reload
	ldp	q10, q11, [x10]
	stp	q10, q11, [sp, #816]
	ldr	d10, [sp, #1392]
	ldr	d11, [sp, #1400]
	ldr	d0, [sp, #496]                  ; 8-byte Folded Reload
	fadd	d10, d10, d0
	ldr	d12, [sp, #1104]
	ldr	d13, [sp, #1112]
	fsub	d10, d10, d12
	ldr	d12, [sp, #840]
	fmadd	d10, d8, d10, d12
	ldr	d0, [sp, #488]                  ; 8-byte Folded Reload
	fadd	d11, d11, d0
	fsub	d11, d11, d13
	ldr	d12, [sp, #1408]
	ldr	d13, [sp, #1416]
	ldr	d0, [sp, #480]                  ; 8-byte Folded Reload
	fadd	d12, d12, d0
	ldr	d15, [sp, #1120]
	ldr	d0, [sp, #1128]
	fsub	d12, d12, d15
	fmul	d10, d9, d10
	fmadd	d11, d8, d11, d10
	fmul	d11, d9, d11
	str	d10, [sp, #848]
	str	d11, [sp, #856]
	fmadd	d10, d8, d12, d11
	ldr	d11, [sp, #472]                 ; 8-byte Folded Reload
	fadd	d11, d13, d11
	fsub	d0, d11, d0
	ldr	d11, [sp, #1424]
	ldr	d12, [sp, #1432]
	ldr	d13, [sp, #464]                 ; 8-byte Folded Reload
	fadd	d11, d11, d13
	ldr	d13, [sp, #1136]
	ldr	d15, [sp, #1144]
	fsub	d11, d11, d13
	fmul	d10, d9, d10
	fmadd	d0, d8, d0, d10
	fmul	d0, d9, d0
	str	d10, [sp, #864]
	str	d0, [sp, #872]
	fmadd	d0, d8, d11, d0
	ldp	d13, d10, [sp, #448]            ; 16-byte Folded Reload
	fadd	d10, d12, d10
	fsub	d10, d10, d15
	ldr	d11, [sp, #1440]
	ldr	d12, [sp, #1448]
	fadd	d11, d11, d13
	ldr	d13, [sp, #1152]
	ldr	d15, [sp, #1160]
	fsub	d11, d11, d13
	fmul	d0, d9, d0
	fmadd	d10, d8, d10, d0
	fmul	d10, d9, d10
	str	d0, [sp, #880]
	str	d10, [sp, #888]
	fmadd	d0, d8, d11, d10
	ldp	d13, d10, [sp, #432]            ; 16-byte Folded Reload
	fadd	d10, d12, d10
	fsub	d10, d10, d15
	ldr	d11, [sp, #1456]
	ldr	d12, [sp, #1464]
	fadd	d11, d11, d13
	ldr	d13, [sp, #1168]
	ldr	d15, [sp, #1176]
	fsub	d11, d11, d13
	fmul	d0, d9, d0
	fmadd	d10, d8, d10, d0
	fmul	d10, d9, d10
	str	d0, [sp, #896]
	str	d10, [sp, #904]
	fmadd	d0, d8, d11, d10
	fadd	d17, d12, d17
	fsub	d17, d17, d15
	ldr	d10, [sp, #1472]
	ldr	d11, [sp, #1480]
	fadd	d18, d10, d18
	ldr	d10, [sp, #1184]
	ldr	d12, [sp, #1192]
	fsub	d18, d18, d10
	fmul	d0, d9, d0
	fmadd	d17, d8, d17, d0
	fmul	d17, d9, d17
	str	d0, [sp, #912]
	str	d17, [sp, #920]
	fmadd	d0, d8, d18, d17
	fadd	d17, d11, d19
	fsub	d17, d17, d12
	ldr	d18, [sp, #1488]
	ldr	d19, [sp, #1496]
	fadd	d18, d18, d20
	ldr	d20, [sp, #1200]
	ldr	d10, [sp, #1208]
	fsub	d18, d18, d20
	fmul	d0, d9, d0
	fmadd	d17, d8, d17, d0
	fmul	d17, d9, d17
	str	d0, [sp, #928]
	str	d17, [sp, #936]
	fmadd	d0, d8, d18, d17
	fadd	d17, d19, d21
	fsub	d17, d17, d10
	ldr	d18, [sp, #1504]
	ldr	d19, [sp, #1512]
	fadd	d18, d18, d22
	ldr	d20, [sp, #1216]
	ldr	d21, [sp, #1224]
	fsub	d18, d18, d20
	fmul	d0, d9, d0
	fmadd	d17, d8, d17, d0
	fmul	d17, d9, d17
	str	d0, [sp, #944]
	str	d17, [sp, #952]
	fmadd	d0, d8, d18, d17
	fadd	d17, d19, d23
	fsub	d17, d17, d21
	ldr	d18, [sp, #1520]
	ldr	d19, [sp, #1528]
	fadd	d18, d18, d24
	ldr	d20, [sp, #1232]
	ldr	d21, [sp, #1240]
	fsub	d18, d18, d20
	fmul	d0, d9, d0
	fmadd	d17, d8, d17, d0
	fmul	d17, d9, d17
	str	d0, [sp, #960]
	str	d17, [sp, #968]
	fmadd	d0, d8, d18, d17
	fadd	d17, d19, d25
	fsub	d17, d17, d21
	ldr	d18, [sp, #1536]
	ldr	d19, [sp, #1544]
	fadd	d18, d18, d26
	ldr	d20, [sp, #1248]
	ldr	d21, [sp, #1256]
	fsub	d18, d18, d20
	fmul	d0, d9, d0
	fmadd	d17, d8, d17, d0
	fmul	d17, d9, d17
	str	d0, [sp, #976]
	str	d17, [sp, #984]
	fmadd	d0, d8, d18, d17
	fadd	d17, d19, d27
	fsub	d17, d17, d21
	ldr	d18, [sp, #1552]
	ldr	d19, [sp, #1560]
	fadd	d18, d18, d28
	ldr	d20, [sp, #1264]
	ldr	d21, [sp, #1272]
	fsub	d18, d18, d20
	fmul	d0, d9, d0
	fmadd	d17, d8, d17, d0
	fmul	d17, d9, d17
	str	d0, [sp, #992]
	str	d17, [sp, #1000]
	fmadd	d0, d8, d18, d17
	fadd	d17, d19, d29
	fsub	d17, d17, d21
	ldr	d18, [sp, #1568]
	ldr	d19, [sp, #1576]
	fadd	d18, d18, d30
	ldr	d20, [sp, #1280]
	ldr	d21, [sp, #1288]
	fsub	d18, d18, d20
	fmul	d0, d9, d0
	fmadd	d17, d8, d17, d0
	fmul	d17, d9, d17
	str	d0, [sp, #1008]
	str	d17, [sp, #1016]
	fmadd	d0, d8, d18, d17
	fadd	d17, d19, d31
	fsub	d17, d17, d21
	ldr	d18, [sp, #1584]
	ldr	d19, [sp, #1592]
	fadd	d16, d18, d16
	ldr	d18, [sp, #1296]
	ldr	d20, [sp, #1304]
	fsub	d16, d16, d18
	fmul	d0, d9, d0
	fmadd	d17, d8, d17, d0
	fmul	d17, d9, d17
	str	d0, [sp, #1024]
	str	d17, [sp, #1032]
	fmadd	d0, d8, d16, d17
	fadd	d7, d19, d7
	fsub	d7, d7, d20
	ldr	d16, [sp, #1600]
	ldr	d17, [sp, #1608]
	fadd	d6, d16, d6
	ldr	d16, [sp, #1312]
	ldr	d18, [sp, #1320]
	fsub	d6, d6, d16
	fmul	d0, d9, d0
	fmadd	d7, d8, d7, d0
	fmul	d7, d9, d7
	str	d0, [sp, #1040]
	str	d7, [sp, #1048]
	fmadd	d0, d8, d6, d7
	fadd	d5, d17, d5
	fsub	d5, d5, d18
	ldr	d6, [sp, #1616]
	ldr	d7, [sp, #1624]
	fadd	d4, d6, d4
	ldr	d6, [sp, #1328]
	ldr	d16, [sp, #1336]
	fsub	d4, d4, d6
	fmul	d0, d9, d0
	fmadd	d5, d8, d5, d0
	fmul	d5, d9, d5
	str	d0, [sp, #1056]
	str	d5, [sp, #1064]
	fmadd	d0, d8, d4, d5
	fadd	d3, d7, d3
	fsub	d3, d3, d16
	ldr	d4, [sp, #1632]
	ldr	d5, [sp, #1640]
	fadd	d2, d4, d2
	ldr	d4, [sp, #1344]
	ldr	d6, [sp, #1352]
	fsub	d2, d2, d4
	fmul	d0, d9, d0
	fmadd	d3, d8, d3, d0
	fmul	d3, d9, d3
	str	d0, [sp, #1072]
	str	d3, [sp, #1080]
	fmadd	d0, d8, d2, d3
	fmul	d0, d9, d0
	fadd	d1, d5, d1
	fsub	d1, d1, d6
	fmadd	d1, d8, d1, d0
	fmul	d1, d9, d1
	str	d0, [sp, #1088]
	str	d1, [sp, #1096]
	add	x9, sp, #816
	ldp	q0, q1, [x9, #256]
	stp	q0, q1, [x10]
	ldr	x10, [sp, #200]                 ; 8-byte Folded Reload
	ldp	q0, q1, [x10]
	stp	q0, q1, [sp, #528]
	ldr	d0, [sp, #552]
	add	x9, sp, #1104
LBB17_14:                               ;   Parent Loop BB17_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	d1, [x25, x8]
	ldr	d2, [x9, x8]
	fadd	d1, d1, d2
	ldr	d2, [x24, x8]
	fmul	d3, d2, d2
	fmul	d2, d2, d3
	fsub	d1, d1, d2
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	str	d0, [x26, x8]
	add	x8, x8, #8
	cmp	x8, #256
	b.ne	LBB17_14
; %bb.15:                               ;   in Loop: Header=BB17_3 Depth=1
	add	x8, sp, #528
	ldp	q0, q1, [x8, #256]
	stp	q0, q1, [x10]
	ldr	x8, [sp, #312]                  ; 8-byte Folded Reload
	add	x8, x8, x27, lsl #2
	ldr	q0, [sp, #2480]
	ldr	q1, [sp, #2496]
	ldp	q2, q3, [sp, #560]
	ldr	q5, [sp, #176]                  ; 16-byte Folded Reload
	fmla.2d	v1, v3, v5
	fmla.2d	v0, v2, v5
	fcvtn	v0.2s, v0.2d
	fcvtn2	v0.4s, v1.2d
	ldr	q1, [sp, #2512]
	ldr	q2, [sp, #2528]
	ldp	q3, q4, [sp, #592]
	fmla.2d	v2, v4, v5
	fmla.2d	v1, v3, v5
	fcvtn	v1.2s, v1.2d
	fcvtn2	v1.4s, v2.2d
	stp	q0, q1, [x8]
	ldr	q0, [sp, #2544]
	ldr	q1, [sp, #2560]
	ldp	q2, q3, [sp, #624]
	fmla.2d	v1, v3, v5
	fmla.2d	v0, v2, v5
	fcvtn	v0.2s, v0.2d
	fcvtn2	v0.4s, v1.2d
	ldr	q1, [sp, #2576]
	ldr	q2, [sp, #2592]
	ldp	q3, q4, [sp, #656]
	fmla.2d	v2, v4, v5
	fmla.2d	v1, v3, v5
	fcvtn	v1.2s, v1.2d
	fcvtn2	v1.4s, v2.2d
	stp	q0, q1, [x8, #32]
	ldr	q0, [sp, #2608]
	ldr	q1, [sp, #2624]
	ldp	q2, q3, [sp, #688]
	fmla.2d	v1, v3, v5
	fmla.2d	v0, v2, v5
	fcvtn	v0.2s, v0.2d
	fcvtn2	v0.4s, v1.2d
	ldr	q1, [sp, #2640]
	ldr	q2, [sp, #2656]
	ldp	q3, q4, [sp, #720]
	fmla.2d	v2, v4, v5
	fmla.2d	v1, v3, v5
	fcvtn	v1.2s, v1.2d
	fcvtn2	v1.4s, v2.2d
	stp	q0, q1, [x8, #64]
	ldr	q0, [sp, #2672]
	ldr	q1, [sp, #2688]
	ldp	q2, q3, [sp, #752]
	fmla.2d	v1, v3, v5
	fmla.2d	v0, v2, v5
	fcvtn	v0.2s, v0.2d
	fcvtn2	v0.4s, v1.2d
	ldr	q1, [sp, #2704]
	ldr	q2, [sp, #2720]
	ldp	q3, q4, [sp, #784]
	fmla.2d	v2, v4, v5
	fmla.2d	v1, v3, v5
	fcvtn	v1.2s, v1.2d
	fcvtn2	v1.4s, v2.2d
	add	x27, x27, #32
	stp	q0, q1, [x8, #96]
	ldr	x8, [sp, #296]                  ; 8-byte Folded Reload
	cmp	x27, x8
	ldr	d13, [sp, #288]                 ; 8-byte Folded Reload
	ldr	d23, [sp, #264]                 ; 8-byte Folded Reload
	b.ls	LBB17_3
; %bb.16:
	ldr	d10, [sp, #16]                  ; 8-byte Folded Reload
	ldr	d11, [sp, #304]                 ; 8-byte Folded Reload
	ldp	q20, q18, [sp, #128]            ; 32-byte Folded Reload
	ldp	q21, q19, [sp, #384]            ; 32-byte Folded Reload
	ldp	q22, q17, [sp, #96]             ; 32-byte Folded Reload
	ldr	w1, [sp, #12]                   ; 4-byte Folded Reload
	subs	w20, w1, w27
	b.le	LBB17_160
LBB17_17:
	ldur	q0, [x19, #40]
	ldur	q1, [x19, #56]
	str	q0, [sp, #5632]
	str	q1, [sp, #5648]
	cmp	w20, #1
	b.lt	LBB17_20
; %bb.18:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1536
	add	x8, x8, #32
	ldr	d0, [sp, #5656]
	mov	x9, x20
LBB17_19:                               ; =>This Inner Loop Header: Depth=1
	fadd	d1, d14, d0
	frintm	d1, d1
	fsub	d0, d0, d1
	fadd	d0, d14, d0
	str	d0, [x8], #8
	subs	x9, x9, #1
	b.ne	LBB17_19
LBB17_20:
	sbfiz	x8, x20, #3, #32
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1536
	ldr	q0, [x9, x8]
	sxtw	x3, w20
	stur	q0, [x19, #40]
	add	x8, x3, #2
	lsl	x23, x8, #3
	ldr	q0, [x9, x23]
	stur	q0, [x19, #56]
	ldp	q0, q1, [x19, #80]
	str	q0, [sp, #5344]
	str	q1, [sp, #5360]
	cmp	w20, #0
	b.le	LBB17_23
; %bb.21:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1248
	add	x8, x8, #32
	ldr	d0, [sp, #5368]
	mov	x9, x20
LBB17_22:                               ; =>This Inner Loop Header: Depth=1
	fadd	d1, d23, d0
	frintm	d1, d1
	fsub	d0, d0, d1
	fadd	d0, d23, d0
	str	d0, [x8], #8
	subs	x9, x9, #1
	b.ne	LBB17_22
LBB17_23:
	lsl	x22, x3, #3
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1248
	ldr	q0, [x8, x22]
	ldr	q1, [x8, x23]
	stp	q0, q1, [x19, #80]
	ldur	q0, [x19, #136]
	str	q0, [sp, #5200]
	cmp	w20, #0
	b.le	LBB17_25
; %bb.24:
	mvn	w8, w27
	add	w8, w8, w1
	ubfiz	x8, x8, #2, #32
Lloh163:
	adrp	x1, l_.memset_pattern.70@PAGE
Lloh164:
	add	x1, x1, l_.memset_pattern.70@PAGEOFF
	add	x0, x15, #16
	add	x2, x8, #4
	str	x22, [sp, #520]                 ; 8-byte Folded Spill
	mov	x22, x27
	mov	x27, x30
	stp	x23, x20, [sp, #488]            ; 16-byte Folded Spill
	mov	x23, x21
	mov	x21, x7
	mov	x20, x3
	bl	_memset_pattern16
	mov	x3, x20
	mov	x7, x21
	mov	x21, x23
	ldp	x23, x20, [sp, #488]            ; 16-byte Folded Reload
	ldp	q22, q17, [sp, #96]             ; 32-byte Folded Reload
	ldp	q21, q19, [sp, #384]            ; 32-byte Folded Reload
	ldp	q20, q18, [sp, #128]            ; 32-byte Folded Reload
	mov	x30, x27
	mov	x27, x22
	ldr	x22, [sp, #520]                 ; 8-byte Folded Reload
LBB17_25:
	lsl	x8, x3, #2
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1104
	ldr	q0, [x9, x8]
	stur	q0, [x19, #136]
	ldur	q0, [x19, #152]
	ldur	q1, [x19, #168]
	str	q0, [sp, #4656]
	str	q1, [sp, #4672]
	cmp	w20, #1
	ldp	q23, q16, [sp, #352]            ; 32-byte Folded Reload
	ldp	q6, q5, [sp, #320]              ; 32-byte Folded Reload
	b.lt	LBB17_33
; %bb.26:
	cmp	w20, #7
	b.hi	LBB17_28
; %bb.27:
	mov	x8, #0                          ; =0x0
	b	LBB17_31
LBB17_28:
	and	x8, x20, #0x7ffffff8
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #560
	add	x9, x9, #80
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #1536
	add	x10, x10, #48
	mov	x11, x8
LBB17_29:                               ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x10, #-16]
	ldp	q2, q3, [x10, #16]
	mov.16b	v4, v6
	fmla.2d	v4, v5, v0
	mov.16b	v0, v6
	fmla.2d	v0, v5, v1
	mov.16b	v1, v6
	fmla.2d	v1, v5, v2
	mov.16b	v2, v6
	fmla.2d	v2, v5, v3
	fmul.2d	v3, v4, v4
	fmul.2d	v0, v0, v0
	fmul.2d	v1, v1, v1
	stp	q3, q0, [x9, #-48]
	fmul.2d	v0, v2, v2
	stp	q1, q0, [x9, #-16]
	add	x9, x9, #64
	add	x10, x10, #64
	subs	x11, x11, #8
	b.ne	LBB17_29
; %bb.30:
	cmp	x8, x20
	b.eq	LBB17_33
LBB17_31:
	lsl	x9, x8, #3
	add	x10, x9, #32
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #560
	add	x9, x9, x10
	add	x11, sp, #1, lsl #12            ; =4096
	add	x11, x11, #1536
	add	x10, x11, x10
	sub	x8, x20, x8
	fmov	d0, #-1.00000000
	fmov	d1, #2.00000000
LBB17_32:                               ; =>This Inner Loop Header: Depth=1
	ldr	d2, [x10], #8
	fmadd	d2, d2, d1, d0
	fmul	d2, d2, d2
	str	d2, [x9], #8
	subs	x8, x8, #1
	b.ne	LBB17_32
LBB17_33:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #560
	ldr	q0, [x8, x22]
	stur	q0, [x19, #152]
	ldr	q0, [x8, x23]
	stur	q0, [x19, #168]
	ldur	q0, [x19, #184]
	ldur	q1, [x19, #200]
	str	q0, [sp, #4112]
	str	q1, [sp, #4128]
	cmp	w20, #0
	b.le	LBB17_41
; %bb.34:
	cmp	w20, #7
	b.hi	LBB17_36
; %bb.35:
	mov	x8, #0                          ; =0x0
	b	LBB17_39
LBB17_36:
	and	x8, x20, #0x7ffffff8
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #16
	add	x9, x9, #80
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #1248
	add	x10, x10, #48
	mov	x11, x8
LBB17_37:                               ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x10, #-16]
	ldp	q2, q3, [x10, #16]
	mov.16b	v4, v6
	fmla.2d	v4, v5, v0
	mov.16b	v0, v6
	fmla.2d	v0, v5, v1
	mov.16b	v1, v6
	fmla.2d	v1, v5, v2
	mov.16b	v2, v6
	fmla.2d	v2, v5, v3
	fmul.2d	v3, v4, v4
	fmul.2d	v0, v0, v0
	fmul.2d	v1, v1, v1
	stp	q3, q0, [x9, #-48]
	fmul.2d	v0, v2, v2
	stp	q1, q0, [x9, #-16]
	add	x9, x9, #64
	add	x10, x10, #64
	subs	x11, x11, #8
	b.ne	LBB17_37
; %bb.38:
	cmp	x8, x20
	b.eq	LBB17_41
LBB17_39:
	lsl	x9, x8, #3
	add	x10, x9, #32
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #16
	add	x9, x9, x10
	add	x11, sp, #1, lsl #12            ; =4096
	add	x11, x11, #1248
	add	x10, x11, x10
	sub	x8, x20, x8
	fmov	d0, #-1.00000000
	fmov	d1, #2.00000000
LBB17_40:                               ; =>This Inner Loop Header: Depth=1
	ldr	d2, [x10], #8
	fmadd	d2, d2, d1, d0
	fmul	d2, d2, d2
	str	d2, [x9], #8
	subs	x8, x8, #1
	b.ne	LBB17_40
LBB17_41:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #16
	ldr	q0, [x8, x22]
	stur	q0, [x19, #184]
	ldr	q0, [x8, x23]
	stur	q0, [x19, #200]
	cmp	w20, #0
	b.le	LBB17_69
; %bb.42:
	cmp	w20, #4
	b.hs	LBB17_44
; %bb.43:
	mov	x8, #0                          ; =0x0
	b	LBB17_53
LBB17_44:
	cmp	w20, #16
	b.hs	LBB17_46
; %bb.45:
	mov	x8, #0                          ; =0x0
	b	LBB17_50
LBB17_46:
	and	x8, x20, #0x7ffffff0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1104
	add	x9, x9, #44
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #848
	add	x10, x10, #64
	mov	x11, x8
LBB17_47:                               ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x9, #-32]
	sshll.2d	v2, v0, #0
	ldp	q3, q4, [x9], #64
	scvtf.2d	v2, v2
	sshll2.2d	v0, v0, #0
	scvtf.2d	v0, v0
	sshll.2d	v5, v1, #0
	scvtf.2d	v5, v5
	sshll2.2d	v1, v1, #0
	scvtf.2d	v1, v1
	sshll.2d	v6, v3, #0
	scvtf.2d	v6, v6
	sshll2.2d	v3, v3, #0
	scvtf.2d	v3, v3
	sshll.2d	v7, v4, #0
	scvtf.2d	v7, v7
	stp	q2, q0, [x10, #-64]
	sshll2.2d	v0, v4, #0
	stp	q5, q1, [x10, #-32]
	stp	q6, q3, [x10]
	scvtf.2d	v0, v0
	stp	q7, q0, [x10, #32]
	add	x10, x10, #128
	subs	x11, x11, #16
	b.ne	LBB17_47
; %bb.48:
	cmp	x8, x20
	b.eq	LBB17_55
; %bb.49:
	tst	x20, #0xc
	b.eq	LBB17_53
LBB17_50:
	mov	x11, x8
	and	x8, x20, #0x7ffffffc
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1104
	add	x9, x9, x11, lsl #2
	add	x9, x9, #12
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #848
	add	x10, x10, x11, lsl #3
	sub	x11, x11, x8
LBB17_51:                               ; =>This Inner Loop Header: Depth=1
	ldr	q0, [x9], #16
	sshll.2d	v1, v0, #0
	scvtf.2d	v1, v1
	sshll2.2d	v0, v0, #0
	scvtf.2d	v0, v0
	stp	q1, q0, [x10], #32
	adds	x11, x11, #4
	b.ne	LBB17_51
; %bb.52:
	cmp	x8, x20
	b.eq	LBB17_55
LBB17_53:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #848
	add	x9, x9, x8, lsl #3
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #1104
	add	x10, x10, x8, lsl #2
	add	x10, x10, #12
	sub	x8, x20, x8
LBB17_54:                               ; =>This Inner Loop Header: Depth=1
	ldr	w11, [x10], #4
	scvtf	d0, w11
	str	d0, [x9], #8
	subs	x8, x8, #1
	b.ne	LBB17_54
LBB17_55:
	cmp	w20, #7
	b.hi	LBB17_57
; %bb.56:
	mov	x8, #0                          ; =0x0
	b	LBB17_60
LBB17_57:
	and	x8, x20, #0x7ffffff8
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #304
	add	x9, x9, #32
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #560
	add	x10, x10, #40
	mov	x11, x8
LBB17_58:                               ; =>This Inner Loop Header: Depth=1
	ldur	q0, [x10, #-8]
	ldur	q1, [x10, #8]
	ldur	q2, [x10, #24]
	ldur	q3, [x10, #40]
	ldp	q4, q5, [x10, #-16]
	ldp	q6, q7, [x10, #16]
	fsub.2d	v0, v0, v4
	fsub.2d	v1, v1, v5
	fsub.2d	v2, v2, v6
	fsub.2d	v3, v3, v7
	stp	q0, q1, [x9, #-32]
	stp	q2, q3, [x9], #64
	add	x10, x10, #64
	subs	x11, x11, #8
	b.ne	LBB17_58
; %bb.59:
	cmp	x8, x20
	b.eq	LBB17_62
LBB17_60:
	lsl	x10, x8, #3
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #304
	add	x9, x9, x10
	add	x11, sp, #1, lsl #12            ; =4096
	add	x11, x11, #560
	add	x10, x10, x11
	add	x10, x10, #32
	sub	x8, x20, x8
LBB17_61:                               ; =>This Inner Loop Header: Depth=1
	ldp	d1, d0, [x10, #-8]
	fsub	d0, d0, d1
	str	d0, [x9], #8
	add	x10, x10, #8
	subs	x8, x8, #1
	b.ne	LBB17_61
LBB17_62:
	cmp	w20, #7
	b.hi	LBB17_64
; %bb.63:
	mov	x8, #0                          ; =0x0
	b	LBB17_67
LBB17_64:
	and	x8, x20, #0x7ffffff8
	add	x9, sp, #3856
	add	x9, x9, #32
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #16
	add	x10, x10, #40
	mov	x11, x8
LBB17_65:                               ; =>This Inner Loop Header: Depth=1
	ldur	q0, [x10, #-8]
	ldur	q1, [x10, #8]
	ldur	q2, [x10, #24]
	ldur	q3, [x10, #40]
	ldp	q4, q5, [x10, #-16]
	ldp	q6, q7, [x10, #16]
	fsub.2d	v0, v0, v4
	fsub.2d	v1, v1, v5
	fsub.2d	v2, v2, v6
	fsub.2d	v3, v3, v7
	stp	q0, q1, [x9, #-32]
	stp	q2, q3, [x9], #64
	add	x10, x10, #64
	subs	x11, x11, #8
	b.ne	LBB17_65
; %bb.66:
	cmp	x8, x20
	b.eq	LBB17_69
LBB17_67:
	lsl	x10, x8, #3
	add	x9, sp, #3856
	add	x9, x9, x10
	add	x11, sp, #1, lsl #12            ; =4096
	add	x11, x11, #16
	add	x10, x10, x11
	add	x10, x10, #32
	sub	x8, x20, x8
LBB17_68:                               ; =>This Inner Loop Header: Depth=1
	ldp	d1, d0, [x10, #-8]
	fsub	d0, d0, d1
	str	d0, [x9], #8
	add	x10, x10, #8
	subs	x8, x8, #1
	b.ne	LBB17_68
LBB17_69:
	add	x8, sp, #3312
	add	x10, x8, #32
	add	x8, x3, #3
	ldr	x9, [sp, #424]                  ; 8-byte Folded Reload
	ldp	w12, w13, [x9]
	add	w14, w13, w12
	and	w11, w14, #0xfff
	str	w11, [x9]
	cmp	w20, #1
	b.lt	LBB17_74
; %bb.70:
	add	x9, x19, #224
	cmp	w20, #7
	b.hi	LBB17_82
; %bb.71:
	mov	x15, #0                         ; =0x0
LBB17_72:
	add	w12, w13, w12
	add	w12, w12, w15
	lsl	x16, x15, #3
	add	x13, sp, #3856
	add	x13, x13, x16
	add	x17, sp, #1, lsl #12            ; =4096
	add	x17, x17, #848
	add	x16, x17, x16
	sub	x15, x20, x15
LBB17_73:                               ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x16], #8
	fmul	d0, d23, d0
	ldr	d1, [x13], #8
	fmul	d0, d0, d1
	and	w17, w12, #0xfff
	str	d0, [x9, w17, uxtw #3]
	add	w12, w12, #1
	subs	x15, x15, #1
	b.ne	LBB17_73
LBB17_74:
	add	x9, sp, #2736
	add	x9, x9, #32
	add	x12, x3, #1
	ldr	x13, [sp, #424]                 ; 8-byte Folded Reload
	str	w20, [x13, #4]
	ldp	w16, w17, [x30]
	add	w0, w17, w16
	and	w15, w0, #0xfff
	str	w15, [x30]
	cmp	w20, #0
	b.le	LBB17_81
; %bb.75:
	str	x3, [sp, #496]                  ; 8-byte Folded Spill
	mov	w13, #33000                     ; =0x80e8
	add	x13, x19, x13
	cmp	w20, #7
	b.hi	LBB17_87
; %bb.76:
	mov	x1, #0                          ; =0x0
LBB17_77:
	add	w16, w17, w16
	add	w16, w16, w1
	lsl	x2, x1, #3
	add	x17, sp, #1, lsl #12            ; =4096
	add	x17, x17, #304
	add	x17, x17, x2
	add	x3, sp, #1, lsl #12             ; =4096
	add	x3, x3, #848
	add	x2, x3, x2
	sub	x1, x20, x1
LBB17_78:                               ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x2], #8
	fmul	d0, d16, d0
	ldr	d1, [x17], #8
	fmul	d0, d0, d1
	and	w3, w16, #0xfff
	str	d0, [x13, w3, uxtw #3]
	add	w16, w16, #1
	subs	x1, x1, #1
	b.ne	LBB17_78
LBB17_79:
	str	w20, [x30, #4]
	ldr	d0, [x19, #128]
	add	x16, x19, #224
	cmp	w20, #7
	b.hi	LBB17_92
; %bb.80:
	mov	x17, #0                         ; =0x0
	b	LBB17_100
LBB17_81:
	str	w20, [x30, #4]
	ldur	q0, [x30, #8]
	ldur	q1, [x30, #24]
	str	q0, [sp, #3312]
	str	q1, [sp, #3328]
	b	LBB17_104
LBB17_82:
	mov	x15, #0                         ; =0x0
	sub	x16, x20, #1
	and	w17, w16, #0xfff
	mov	w0, #4095                       ; =0xfff
	bic	w0, w0, w14
	cmp	w0, w17
	b.lo	LBB17_72
; %bb.83:
	cmp	x16, #4095
	b.hi	LBB17_72
; %bb.84:
	and	x15, x20, #0x1ff8
	add	x16, sp, #3856
	add	x16, x16, #32
	add	x17, sp, #1, lsl #12            ; =4096
	add	x17, x17, #848
	add	x17, x17, #32
	mov	x0, x15
	mov	x1, x14
LBB17_85:                               ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x17, #-32]
	ldp	q2, q3, [x17], #64
	fmul.2d	v0, v0, v23[0]
	fmul.2d	v1, v1, v23[0]
	fmul.2d	v2, v2, v23[0]
	fmul.2d	v3, v3, v23[0]
	ldp	q4, q5, [x16, #-32]
	ldp	q6, q7, [x16], #64
	fmul.2d	v0, v0, v4
	fmul.2d	v1, v1, v5
	fmul.2d	v2, v2, v6
	fmul.2d	v3, v3, v7
	and	w2, w1, #0xfff
	add	x2, x9, w2, uxtw #3
	stp	q0, q1, [x2]
	stp	q2, q3, [x2, #32]
	add	w1, w1, #8
	subs	x0, x0, #8
	b.ne	LBB17_85
; %bb.86:
	cmp	x15, x20
	b.ne	LBB17_72
	b	LBB17_74
LBB17_87:
	mov	x1, #0                          ; =0x0
	sub	x2, x20, #1
	and	w3, w2, #0xfff
	mov	w4, #4095                       ; =0xfff
	bic	w4, w4, w0
	cmp	w4, w3
	b.lo	LBB17_77
; %bb.88:
	cmp	x2, #4095
	b.hi	LBB17_77
; %bb.89:
	and	x1, x20, #0x1ff8
	add	x2, sp, #1, lsl #12             ; =4096
	add	x2, x2, #304
	add	x2, x2, #32
	add	x3, sp, #1, lsl #12             ; =4096
	add	x3, x3, #848
	add	x3, x3, #32
	mov	x4, x1
	mov	x5, x0
LBB17_90:                               ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x3, #-32]
	ldp	q2, q3, [x3], #64
	fmul.2d	v0, v0, v16[0]
	fmul.2d	v1, v1, v16[0]
	fmul.2d	v2, v2, v16[0]
	fmul.2d	v3, v3, v16[0]
	ldp	q4, q5, [x2, #-32]
	ldp	q6, q7, [x2], #64
	fmul.2d	v0, v0, v4
	fmul.2d	v1, v1, v5
	fmul.2d	v2, v2, v6
	fmul.2d	v3, v3, v7
	and	w6, w5, #0xfff
	add	x6, x13, w6, uxtw #3
	stp	q0, q1, [x6]
	stp	q2, q3, [x6, #32]
	add	w5, w5, #8
	subs	x4, x4, #8
	b.ne	LBB17_90
; %bb.91:
	cmp	x1, x20
	b.ne	LBB17_77
	b	LBB17_79
LBB17_92:
	mov	x17, #0                         ; =0x0
	sub	x1, x20, #1
	and	w2, w1, #0xfff
	mvn	w3, w14
	add	w3, w3, w7
	and	w3, w3, #0xfff
	cmp	w3, w2
	b.lo	LBB17_100
; %bb.93:
	sub	w3, w21, w0
	and	w3, w3, #0xfff
	cmp	w3, w2
	b.lo	LBB17_100
; %bb.94:
	sub	w2, w7, w14
	and	w14, w1, #0xfff
	and	w2, w2, #0xfff
	cmp	w2, w14
	b.lo	LBB17_100
; %bb.95:
	eor	w0, w0, #0xfff
	add	w0, w0, w21
	and	w0, w0, #0xfff
	cmp	w0, w14
	b.lo	LBB17_100
; %bb.96:
	cmp	x1, #4095
	b.hi	LBB17_100
; %bb.97:
	str	x22, [sp, #520]                 ; 8-byte Folded Spill
	mov	x14, #0                         ; =0x0
	and	x17, x20, #0x1ffe
	dup.2d	v1, v18[0]
	dup.2d	v2, v20[0]
	dup.2d	v3, v17[0]
	sub	w0, w15, w21
	sub	w1, w0, #1
	mov	x22, x7
	sub	w2, w11, w7
	sub	w3, w2, #1
	dup.2d	v4, v22[0]
	add	x4, sp, #1, lsl #12             ; =4096
	add	x4, x4, #848
	add	x5, sp, #1, lsl #12             ; =4096
	add	x5, x5, #304
	add	x6, sp, #3856
	add	x7, sp, #3600
LBB17_98:                               ; =>This Inner Loop Header: Depth=1
	ldr	q5, [x4], #16
	ldr	q6, [x5], #16
	ldr	q7, [x6], #16
	add	w19, w3, w14
	and	w19, w19, #0xfff
	fmul.2d	v7, v7, v19[0]
	ubfiz	x19, x19, #3, #32
	ldr	q16, [x16, x19]
	add	w19, w0, w14
	and	w19, w19, #0xfff
	fmla.2d	v7, v6, v1
	ubfiz	x19, x19, #3, #32
	ldr	q6, [x13, x19]
	fmul.2d	v6, v6, v21[0]
	add	w19, w1, w14
	fmla.2d	v6, v16, v2
	and	w19, w19, #0xfff
	ubfiz	x19, x19, #3, #32
	ldr	q16, [x13, x19]
	add	w19, w2, w14
	fmla.2d	v6, v16, v3
	and	w19, w19, #0xfff
	ubfiz	x19, x19, #3, #32
	ldr	q16, [x16, x19]
	fmla.2d	v6, v16, v4
	fmul.2d	v5, v5, v0[0]
	fneg.2d	v6, v6
	fmla.2d	v6, v7, v5
	str	q6, [x7], #16
	add	x14, x14, #2
	cmp	x17, x14
	b.ne	LBB17_98
; %bb.99:
	cmp	x17, x20
	mov	x7, x22
	ldr	x22, [sp, #520]                 ; 8-byte Folded Reload
	b.eq	LBB17_102
LBB17_100:
	mov	x14, #0                         ; =0x0
	add	w15, w15, w17
	sub	w15, w15, w21
	sub	w0, w15, #1
	add	w11, w11, w17
	sub	w11, w11, w7
	lsl	x4, x17, #3
	add	x1, sp, #3600
	add	x1, x1, x4
	add	x2, sp, #3856
	add	x2, x2, x4
	add	x3, sp, #1, lsl #12             ; =4096
	add	x3, x3, #304
	add	x3, x3, x4
	add	x5, sp, #1, lsl #12             ; =4096
	add	x5, x5, #848
	add	x4, x5, x4
	sub	w5, w11, #1
	sub	x17, x20, x17
LBB17_101:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x4, x14, lsl #3]
	ldr	d2, [x3, x14, lsl #3]
	ldr	d3, [x2, x14, lsl #3]
	fmul	d3, d19, d3
	fmadd	d2, d18, d2, d3
	add	w6, w5, w14
	and	w6, w6, #0xfff
	ldr	d3, [x16, w6, uxtw #3]
	add	w6, w15, w14
	and	w6, w6, #0xfff
	ldr	d4, [x13, w6, uxtw #3]
	fmul	d4, d21, d4
	fmadd	d3, d20, d3, d4
	add	w6, w0, w14
	and	w6, w6, #0xfff
	ldr	d4, [x13, w6, uxtw #3]
	fmul	d1, d0, d1
	fmadd	d3, d17, d4, d3
	add	w6, w11, w14
	and	w6, w6, #0xfff
	ldr	d4, [x16, w6, uxtw #3]
	fmadd	d3, d22, d4, d3
	fnmsub	d1, d1, d2, d3
	str	d1, [x1, x14, lsl #3]
	add	x14, x14, #1
	cmp	x17, x14
	b.ne	LBB17_101
LBB17_102:
	ldur	q0, [x30, #24]
	ldur	q1, [x30, #8]
	str	q0, [sp, #3328]
	str	q1, [sp, #3312]
	add	x11, sp, #3600
	ldr	d0, [sp, #3336]
	mov	x13, x20
	mov	x14, x10
	ldr	x3, [sp, #496]                  ; 8-byte Folded Reload
LBB17_103:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x11], #8
	fmadd	d0, d11, d1, d0
	fmul	d0, d9, d0
	str	d0, [x14], #8
	subs	x13, x13, #1
	b.ne	LBB17_103
LBB17_104:
	add	x11, sp, #1360
	add	x11, x11, #32
	add	x13, sp, #3312
	ldr	d0, [x13, x3, lsl #3]
	str	d0, [x30, #8]
	lsl	x12, x12, #3
	ldr	q0, [x13, x12]
	str	q0, [x30, #16]
	ldr	d0, [x13, x8, lsl #3]
	str	d0, [x30, #32]
	ldur	q0, [x30, #40]
	ldur	q1, [x30, #56]
	str	q0, [sp, #3024]
	str	q1, [sp, #3040]
	cmp	w20, #0
	b.le	LBB17_110
; %bb.105:
	add	x13, sp, #3024
	add	x13, x13, #32
	ldr	d0, [sp, #3048]
	mov	x14, x20
	mov	x15, x13
LBB17_106:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x10], #8
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	str	d0, [x15], #8
	subs	x14, x14, #1
	b.ne	LBB17_106
; %bb.107:
	add	x10, sp, #3024
	ldr	q0, [x10, x22]
	stur	q0, [x30, #40]
	ldr	q0, [x10, x23]
	stur	q0, [x30, #56]
	cmp	w20, #0
	b.le	LBB17_111
; %bb.108:
	cmp	w20, #7
	b.hi	LBB17_112
; %bb.109:
	mov	x10, #0                         ; =0x0
	b	LBB17_115
LBB17_110:
	add	x10, sp, #3024
	ldr	q0, [x10, x22]
	stur	q0, [x30, #40]
	ldr	q0, [x10, x23]
	stur	q0, [x30, #56]
LBB17_111:
	ldur	q0, [x30, #72]
	ldur	q1, [x30, #88]
	str	q0, [sp, #2736]
	str	q1, [sp, #2752]
	b	LBB17_119
LBB17_112:
	and	x10, x20, #0x7ffffff8
	add	x14, sp, #2192
	add	x14, x14, #32
	add	x15, sp, #3312
	add	x15, x15, #48
	mov	x16, x10
LBB17_113:                              ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x15, #-16]
	ldp	q2, q3, [x15, #16]
	fmul.2d	v4, v0, v0
	fmul.2d	v5, v1, v1
	fmul.2d	v6, v2, v2
	fmul.2d	v7, v3, v3
	fmul.2d	v0, v0, v4
	fmul.2d	v1, v1, v5
	fmul.2d	v2, v2, v6
	stp	q0, q1, [x14, #-32]
	fmul.2d	v0, v3, v7
	stp	q2, q0, [x14], #64
	add	x15, x15, #64
	subs	x16, x16, #8
	b.ne	LBB17_113
; %bb.114:
	cmp	x10, x20
	b.eq	LBB17_117
LBB17_115:
	lsl	x15, x10, #3
	add	x14, sp, #2192
	add	x14, x14, x15
	add	x16, sp, #3312
	add	x15, x15, x16
	add	x15, x15, #32
	sub	x10, x20, x10
LBB17_116:                              ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x15], #8
	fmul	d1, d0, d0
	fmul	d0, d0, d1
	str	d0, [x14], #8
	subs	x10, x10, #1
	b.ne	LBB17_116
LBB17_117:
	ldur	q0, [x30, #88]
	ldur	q1, [x30, #72]
	str	q0, [sp, #2752]
	str	q1, [sp, #2736]
	ldr	d0, [sp, #2760]
	mov	x10, x20
	mov	x14, x9
LBB17_118:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x13], #8
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	str	d0, [x14], #8
	subs	x10, x10, #1
	b.ne	LBB17_118
LBB17_119:
	add	x10, sp, #2736
	ldr	d0, [x10, x3, lsl #3]
	str	d0, [x30, #72]
	ldr	q0, [x10, x12]
	str	q0, [x30, #80]
	ldr	d0, [x10, x8, lsl #3]
	str	d0, [x30, #96]
	ldur	q0, [x30, #136]
	ldur	q1, [x30, #152]
	str	q0, [sp, #1904]
	str	q1, [sp, #1920]
	cmp	w20, #0
	b.le	LBB17_125
; %bb.120:
	add	x10, sp, #3600
	add	x13, sp, #2192
	ldr	d0, [sp, #1928]
	mov	x14, x20
	mov	x15, x28
LBB17_121:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x10], #8
	fmul	d1, d1, d13
	fmul	d2, d1, d1
	fmul	d1, d1, d2
	ldr	d2, [x13], #8
	fsub	d1, d1, d2
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	str	d0, [x15], #8
	subs	x14, x14, #1
	b.ne	LBB17_121
; %bb.122:
	add	x10, sp, #1904
	ldr	q0, [x10, x22]
	stur	q0, [x30, #136]
	ldr	q0, [x10, x23]
	stur	q0, [x30, #152]
	cmp	w20, #0
	b.le	LBB17_126
; %bb.123:
	cmp	w20, #7
	b.hi	LBB17_127
; %bb.124:
	mov	x10, #0                         ; =0x0
	b	LBB17_130
LBB17_125:
	add	x10, sp, #1904
	ldr	q0, [x10, x22]
	stur	q0, [x30, #136]
	ldr	q0, [x10, x23]
	stur	q0, [x30, #152]
LBB17_126:
	ldur	q0, [x30, #168]
	ldur	q1, [x30, #184]
	str	q0, [sp, #1360]
	str	q1, [sp, #1376]
	b	LBB17_134
LBB17_127:
	and	x10, x20, #0x7ffffff8
	add	x13, sp, #1648
	add	x13, x13, #32
	add	x14, sp, #3024
	add	x14, x14, #48
	mov	x15, x10
LBB17_128:                              ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x14, #-16]
	ldp	q2, q3, [x14, #16]
	fmul.2d	v4, v0, v0
	fmul.2d	v5, v1, v1
	fmul.2d	v6, v2, v2
	fmul.2d	v7, v3, v3
	fmul.2d	v0, v0, v4
	fmul.2d	v1, v1, v5
	fmul.2d	v2, v2, v6
	stp	q0, q1, [x13, #-32]
	fmul.2d	v0, v3, v7
	stp	q2, q0, [x13], #64
	add	x14, x14, #64
	subs	x15, x15, #8
	b.ne	LBB17_128
; %bb.129:
	cmp	x10, x20
	b.eq	LBB17_132
LBB17_130:
	lsl	x14, x10, #3
	add	x13, sp, #1648
	add	x13, x13, x14
	add	x15, sp, #3024
	add	x14, x14, x15
	add	x14, x14, #32
	sub	x10, x20, x10
LBB17_131:                              ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x14], #8
	fmul	d1, d0, d0
	fmul	d0, d0, d1
	str	d0, [x13], #8
	subs	x10, x10, #1
	b.ne	LBB17_131
LBB17_132:
	ldur	q0, [x30, #184]
	ldur	q1, [x30, #168]
	str	q0, [sp, #1376]
	str	q1, [sp, #1360]
	add	x10, sp, #2192
	add	x13, sp, #1648
	ldr	d0, [sp, #1384]
	mov	x14, x20
	mov	x15, x11
LBB17_133:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x28], #8
	ldr	d2, [x10], #8
	fadd	d1, d1, d2
	ldr	d2, [x13], #8
	fsub	d1, d1, d2
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	str	d0, [x15], #8
	subs	x14, x14, #1
	b.ne	LBB17_133
LBB17_134:
	add	x10, sp, #1360
	ldr	d0, [x10, x3, lsl #3]
	ldr	q1, [x10, x12]
	str	d0, [x30, #168]
	str	q1, [x30, #176]
	ldr	d0, [x10, x8, lsl #3]
	str	d0, [x30, #192]
	cmp	w20, #0
	b.le	LBB17_137
; %bb.135:
	cmp	w20, #7
	b.hi	LBB17_138
; %bb.136:
	mov	x10, #0                         ; =0x0
	b	LBB17_141
LBB17_137:
	ldur	q0, [x30, #104]
	ldur	q1, [x30, #120]
	str	q0, [sp, #2448]
	str	q1, [sp, #2464]
	b	LBB17_145
LBB17_138:
	and	x10, x20, #0x7ffffff8
	add	x13, sp, #1104
	add	x13, x13, #32
	add	x14, sp, #2736
	add	x14, x14, #48
	mov	x15, x10
LBB17_139:                              ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x14, #-16]
	ldp	q2, q3, [x14, #16]
	fmul.2d	v4, v0, v0
	fmul.2d	v5, v1, v1
	fmul.2d	v6, v2, v2
	fmul.2d	v7, v3, v3
	fmul.2d	v0, v0, v4
	fmul.2d	v1, v1, v5
	fmul.2d	v2, v2, v6
	stp	q0, q1, [x13, #-32]
	fmul.2d	v0, v3, v7
	stp	q2, q0, [x13], #64
	add	x14, x14, #64
	subs	x15, x15, #8
	b.ne	LBB17_139
; %bb.140:
	cmp	x10, x20
	b.eq	LBB17_143
LBB17_141:
	lsl	x14, x10, #3
	add	x13, sp, #1104
	add	x13, x13, x14
	add	x15, sp, #2736
	add	x14, x14, x15
	add	x14, x14, #32
	sub	x10, x20, x10
LBB17_142:                              ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x14], #8
	fmul	d1, d0, d0
	fmul	d0, d0, d1
	str	d0, [x13], #8
	subs	x10, x10, #1
	b.ne	LBB17_142
LBB17_143:
	ldur	q0, [x30, #120]
	ldur	q1, [x30, #104]
	str	q0, [sp, #2464]
	str	q1, [sp, #2448]
	ldr	d0, [sp, #2472]
	mov	x10, x20
	mov	x13, x24
LBB17_144:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x9], #8
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	str	d0, [x13], #8
	subs	x10, x10, #1
	b.ne	LBB17_144
LBB17_145:
	add	x9, sp, #2448
	ldr	d0, [x9, x3, lsl #3]
	str	d0, [x30, #104]
	ldr	q0, [x9, x12]
	str	q0, [x30, #112]
	ldr	d0, [x9, x8, lsl #3]
	str	d0, [x30, #128]
	ldur	q0, [x30, #200]
	ldur	q1, [x30, #216]
	stp	q0, q1, [sp, #816]
	cmp	w20, #0
	b.le	LBB17_148
; %bb.146:
	add	x8, sp, #1648
	add	x9, sp, #1104
	ldr	d0, [sp, #840]
	mov	x10, x20
	mov	x12, x25
LBB17_147:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x11], #8
	ldr	d2, [x8], #8
	fadd	d1, d1, d2
	ldr	d2, [x9], #8
	fsub	d1, d1, d2
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	str	d0, [x12], #8
	subs	x10, x10, #1
	b.ne	LBB17_147
LBB17_148:
	add	x8, sp, #816
	ldr	q0, [x8, x22]
	stur	q0, [x30, #200]
	ldr	q0, [x8, x23]
	stur	q0, [x30, #216]
	ldur	q0, [x30, #232]
	ldur	q1, [x30, #248]
	stp	q0, q1, [sp, #528]
	cmp	w20, #0
	b.le	LBB17_154
; %bb.149:
	mov	w8, w27
	add	x9, sp, #1104
	ldr	d0, [sp, #552]
	mov	x10, x20
LBB17_150:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x25], #8
	ldr	d2, [x9], #8
	fadd	d1, d1, d2
	ldr	d2, [x24], #8
	fmul	d3, d2, d2
	fmul	d2, d2, d3
	fsub	d1, d1, d2
	fmadd	d0, d8, d1, d0
	fmul	d0, d9, d0
	str	d0, [x26], #8
	subs	x10, x10, #1
	b.ne	LBB17_150
; %bb.151:
	add	x9, sp, #528
	ldr	q0, [x9, x22]
	stur	q0, [x30, #232]
	ldr	q0, [x9, x23]
	stur	q0, [x30, #248]
	cmp	w20, #0
	b.le	LBB17_160
; %bb.152:
	fneg	d0, d10
	cmp	w20, #8
	b.hs	LBB17_155
; %bb.153:
	mov	x9, #0                          ; =0x0
	b	LBB17_158
LBB17_154:
	add	x8, sp, #528
	ldr	q0, [x8, x22]
	stur	q0, [x30, #232]
	ldr	q0, [x8, x23]
	stur	q0, [x30, #248]
	b	LBB17_160
LBB17_155:
	and	x9, x20, #0x7ffffff8
	dup.2d	v1, v0[0]
	ldr	x10, [sp, #312]                 ; 8-byte Folded Reload
	add	x10, x10, x8, lsl #2
	add	x10, x10, #16
	add	x11, sp, #2448
	add	x11, x11, #48
	add	x12, sp, #528
	add	x12, x12, #80
	mov	x13, x9
LBB17_156:                              ; =>This Inner Loop Header: Depth=1
	ldp	q2, q3, [x11, #-16]
	ldp	q4, q5, [x11, #16]
	ldp	q6, q7, [x12, #-48]
	ldp	q16, q17, [x12, #-16]
	fmla.2d	v2, v6, v1
	fmla.2d	v3, v7, v1
	fmla.2d	v4, v16, v1
	fmla.2d	v5, v17, v1
	fcvtn	v2.2s, v2.2d
	fcvtn	v3.2s, v3.2d
	fcvtn	v4.2s, v4.2d
	fcvtn	v5.2s, v5.2d
	stp	d2, d3, [x10, #-16]
	stp	d4, d5, [x10], #32
	add	x11, x11, #64
	add	x12, x12, #64
	subs	x13, x13, #8
	b.ne	LBB17_156
; %bb.157:
	cmp	x9, x20
	b.eq	LBB17_160
LBB17_158:
	lsl	x10, x9, #2
	add	x8, x10, x8, lsl #2
	ldr	x10, [sp, #312]                 ; 8-byte Folded Reload
	add	x8, x10, x8
	lsl	x10, x9, #3
	add	x11, x10, #32
	add	x10, sp, #528
	add	x10, x10, x11
	add	x12, sp, #2448
	add	x11, x12, x11
	sub	x9, x20, x9
LBB17_159:                              ; =>This Inner Loop Header: Depth=1
	ldr	d1, [x11], #8
	ldr	d2, [x10], #8
	fmadd	d1, d0, d2, d1
	fcvt	s1, d1
	str	s1, [x8], #4
	subs	x9, x9, #1
	b.ne	LBB17_159
LBB17_160:
	ldur	x8, [x29, #-168]
Lloh165:
	adrp	x9, ___stack_chk_guard@GOTPAGE
Lloh166:
	ldr	x9, [x9, ___stack_chk_guard@GOTPAGEOFF]
Lloh167:
	ldr	x9, [x9]
	cmp	x9, x8
	b.ne	LBB17_162
; %bb.161:
	add	sp, sp, #1, lsl #12             ; =4096
	add	sp, sp, #1856
	ldp	x29, x30, [sp, #144]            ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #128]            ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #112]            ; 16-byte Folded Reload
	ldp	x24, x23, [sp, #96]             ; 16-byte Folded Reload
	ldp	x26, x25, [sp, #80]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp, #64]             ; 16-byte Folded Reload
	ldp	d9, d8, [sp, #48]               ; 16-byte Folded Reload
	ldp	d11, d10, [sp, #32]             ; 16-byte Folded Reload
	ldp	d13, d12, [sp, #16]             ; 16-byte Folded Reload
	ldp	d15, d14, [sp], #160            ; 16-byte Folded Reload
	ret
LBB17_162:
	bl	___stack_chk_fail
	.loh AdrpLdrGotLdr	Lloh158, Lloh159, Lloh160
	.loh AdrpAdd	Lloh161, Lloh162
	.loh AdrpAdd	Lloh163, Lloh164
	.loh AdrpLdrGotLdr	Lloh165, Lloh166, Lloh167
	.loh AdrpLdrGot	Lloh156, Lloh157
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN3dsp7computeEdiPPfS1_       ; -- Begin function _ZN3dsp7computeEdiPPfS1_
	.weak_def_can_be_hidden	__ZN3dsp7computeEdiPPfS1_
	.p2align	2
__ZN3dsp7computeEdiPPfS1_:              ; @_ZN3dsp7computeEdiPPfS1_
	.cfi_startproc
; %bb.0:
	ldr	x8, [x0]
	ldr	x4, [x8, #120]
	br	x4
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Critical allocation error: %d\n"

	.section	__DATA,__const
	.globl	__ZTV5mydsp                     ; @_ZTV5mydsp
	.weak_def_can_be_hidden	__ZTV5mydsp
	.p2align	3, 0x0
__ZTV5mydsp:
	.quad	0
	.quad	__ZTI5mydsp
	.quad	__ZN5mydspD1Ev
	.quad	__ZN5mydspD0Ev
	.quad	__ZN5mydsp12getNumInputsEv
	.quad	__ZN5mydsp13getNumOutputsEv
	.quad	__ZN5mydsp18buildUserInterfaceEP2UI
	.quad	__ZN5mydsp13getSampleRateEv
	.quad	__ZN5mydsp4initEi
	.quad	__ZN5mydsp12instanceInitEi
	.quad	__ZN5mydsp17instanceConstantsEi
	.quad	__ZN5mydsp26instanceResetUserInterfaceEv
	.quad	__ZN5mydsp13instanceClearEv
	.quad	__ZN5mydsp5cloneEv
	.quad	__ZN5mydsp8metadataEP4Meta
	.quad	__ZN3dsp7controlEv
	.quad	__ZN3dsp5frameEPfS0_
	.quad	__ZN5mydsp7computeEiPPfS1_
	.quad	__ZN3dsp7computeEdiPPfS1_

	.private_extern	__ZTS5mydsp             ; @_ZTS5mydsp
	.section	__TEXT,__const
	.globl	__ZTS5mydsp
	.weak_definition	__ZTS5mydsp
__ZTS5mydsp:
	.asciz	"5mydsp"

	.private_extern	__ZTS3dsp               ; @_ZTS3dsp
	.globl	__ZTS3dsp
	.weak_definition	__ZTS3dsp
__ZTS3dsp:
	.asciz	"3dsp"

	.private_extern	__ZTI3dsp               ; @_ZTI3dsp
	.section	__DATA,__const
	.globl	__ZTI3dsp
	.weak_definition	__ZTI3dsp
	.p2align	3, 0x0
__ZTI3dsp:
	.quad	__ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	__ZTS3dsp-9223372036854775808

	.private_extern	__ZTI5mydsp             ; @_ZTI5mydsp
	.globl	__ZTI5mydsp
	.weak_definition	__ZTI5mydsp
	.p2align	3, 0x0
__ZTI5mydsp:
	.quad	__ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	__ZTS5mydsp-9223372036854775808
	.quad	__ZTI3dsp

	.section	__TEXT,__cstring,cstring_literals
l_.str.1:                               ; @.str.1
	.asciz	"carre_volterra"

l_.str.2:                               ; @.str.2
	.asciz	"NL"

l_.str.3:                               ; @.str.3
	.asciz	"delta"

l_.str.4:                               ; @.str.4
	.asciz	"freq carre"

l_.str.5:                               ; @.str.5
	.asciz	"unit"

l_.str.6:                               ; @.str.6
	.asciz	"Hz"

l_.str.7:                               ; @.str.7
	.asciz	"freq"

l_.str.8:                               ; @.str.8
	.asciz	"level"

l_.str.9:                               ; @.str.9
	.asciz	"compile_options"

l_.str.10:                              ; @.str.10
	.asciz	"-a arch/cpp/inspect.cpp -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32"

l_.str.11:                              ; @.str.11
	.asciz	"effect.lib/author"

l_.str.12:                              ; @.str.12
	.asciz	"Julius O. Smith (jos at ccrma.stanford.edu)"

l_.str.13:                              ; @.str.13
	.asciz	"effect.lib/copyright"

l_.str.14:                              ; @.str.14
	.asciz	"Julius O. Smith III"

l_.str.15:                              ; @.str.15
	.asciz	"effect.lib/deprecated"

l_.str.16:                              ; @.str.16
	.asciz	"This library is deprecated and is not maintained anymore. It will be removed in August 2017."

l_.str.17:                              ; @.str.17
	.asciz	"effect.lib/exciter_author"

l_.str.18:                              ; @.str.18
	.asciz	"Priyanka Shekar (pshekar@ccrma.stanford.edu)"

l_.str.19:                              ; @.str.19
	.asciz	"effect.lib/exciter_copyright"

l_.str.20:                              ; @.str.20
	.asciz	"Copyright (c) 2013 Priyanka Shekar"

l_.str.21:                              ; @.str.21
	.asciz	"effect.lib/exciter_license"

l_.str.22:                              ; @.str.22
	.asciz	"MIT License (MIT)"

l_.str.23:                              ; @.str.23
	.asciz	"effect.lib/exciter_name"

l_.str.24:                              ; @.str.24
	.asciz	"Harmonic Exciter"

l_.str.25:                              ; @.str.25
	.asciz	"effect.lib/exciter_version"

l_.str.26:                              ; @.str.26
	.asciz	"1.0"

l_.str.27:                              ; @.str.27
	.asciz	"effect.lib/license"

l_.str.28:                              ; @.str.28
	.asciz	"STK-4.3"

l_.str.29:                              ; @.str.29
	.asciz	"effect.lib/name"

l_.str.30:                              ; @.str.30
	.asciz	"Faust Audio Effect Library"

l_.str.31:                              ; @.str.31
	.asciz	"effect.lib/version"

l_.str.32:                              ; @.str.32
	.asciz	"1.33"

l_.str.33:                              ; @.str.33
	.asciz	"filename"

l_.str.34:                              ; @.str.34
	.asciz	"carre_volterra.dsp"

l_.str.35:                              ; @.str.35
	.asciz	"filter.lib/author"

l_.str.36:                              ; @.str.36
	.asciz	"filter.lib/copyright"

l_.str.37:                              ; @.str.37
	.asciz	"filter.lib/deprecated"

l_.str.38:                              ; @.str.38
	.asciz	"filter.lib/license"

l_.str.39:                              ; @.str.39
	.asciz	"filter.lib/name"

l_.str.40:                              ; @.str.40
	.asciz	"Faust Filter Library"

l_.str.41:                              ; @.str.41
	.asciz	"filter.lib/reference"

l_.str.42:                              ; @.str.42
	.asciz	"https://ccrma.stanford.edu/~jos/filters/"

l_.str.43:                              ; @.str.43
	.asciz	"filter.lib/version"

l_.str.44:                              ; @.str.44
	.asciz	"1.29"

l_.str.45:                              ; @.str.45
	.asciz	"math.lib/author"

l_.str.46:                              ; @.str.46
	.asciz	"GRAME"

l_.str.47:                              ; @.str.47
	.asciz	"math.lib/copyright"

l_.str.48:                              ; @.str.48
	.asciz	"math.lib/deprecated"

l_.str.49:                              ; @.str.49
	.asciz	"math.lib/license"

l_.str.50:                              ; @.str.50
	.asciz	"LGPL with exception"

l_.str.51:                              ; @.str.51
	.asciz	"math.lib/name"

l_.str.52:                              ; @.str.52
	.asciz	"Math Library"

l_.str.53:                              ; @.str.53
	.asciz	"math.lib/version"

l_.str.54:                              ; @.str.54
	.asciz	"music.lib/author"

l_.str.55:                              ; @.str.55
	.asciz	"music.lib/copyright"

l_.str.56:                              ; @.str.56
	.asciz	"music.lib/deprecated"

l_.str.57:                              ; @.str.57
	.asciz	"music.lib/license"

l_.str.58:                              ; @.str.58
	.asciz	"music.lib/name"

l_.str.59:                              ; @.str.59
	.asciz	"Music Library"

l_.str.60:                              ; @.str.60
	.asciz	"music.lib/version"

l_.str.61:                              ; @.str.61
	.asciz	"name"

l_.str.62:                              ; @.str.62
	.asciz	"oscillator.lib/author"

l_.str.63:                              ; @.str.63
	.asciz	"oscillator.lib/copyright"

l_.str.64:                              ; @.str.64
	.asciz	"oscillator.lib/deprecated"

l_.str.65:                              ; @.str.65
	.asciz	"oscillator.lib/license"

l_.str.66:                              ; @.str.66
	.asciz	"oscillator.lib/name"

l_.str.67:                              ; @.str.67
	.asciz	"Faust Oscillator Library"

l_.str.68:                              ; @.str.68
	.asciz	"oscillator.lib/version"

l_.str.69:                              ; @.str.69
	.asciz	"1.11"

	.section	__TEXT,__literal16,16byte_literals
	.p2align	4, 0x0                          ; @.memset_pattern.70
l_.memset_pattern.70:
	.long	1                               ; 0x1
	.long	1                               ; 0x1
	.long	1                               ; 0x1
	.long	1                               ; 0x1

	.no_dead_strip	__Z15inspect_computeR5mydspPPfS2_
.subsections_via_symbols
