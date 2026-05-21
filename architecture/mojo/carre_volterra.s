	.build_version macos, 26, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_inspect_compute
	.p2align	2
_inspect_compute:

	.cfi_startproc
	stp	d11, d10, [sp, #-128]!
	stp	d9, d8, [sp, #16]
	stp	x28, x27, [sp, #32]
	stp	x26, x25, [sp, #48]
	stp	x24, x23, [sp, #64]
	stp	x22, x21, [sp, #80]
	stp	x20, x19, [sp, #96]
	stp	x29, x30, [sp, #112]
	sub	sp, sp, #1, lsl #12
	sub	sp, sp, #1520
	.cfi_def_cfa_offset 5744
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
	stp	x1, x2, [sp, #32]
	mov	x26, x0
	add	x8, x0, #16, lsl #12
	add	x0, x8, #240
	mov	w8, #33000
	add	x9, x26, x8
	add	x10, x26, #232
	mov	w8, #33008
	add	x11, x26, x8
	add	x8, x26, #16, lsl #12
	add	x8, x8, #248
	str	x8, [sp, #192]
	add	x8, x26, #16, lsl #12
	add	x8, x8, #280
	str	x8, [sp, #184]
	add	x8, x26, #16, lsl #12
	add	x8, x8, #312
	str	x8, [sp, #176]
	add	x8, x26, #16, lsl #12
	add	x8, x8, #376
	str	x8, [sp, #168]
	add	x8, x26, #16, lsl #12
	add	x16, x8, #408
	add	x8, x26, #16, lsl #12
	add	x17, x8, #344
	add	x8, x26, #16, lsl #12
	add	x3, x8, #440
	add	x8, x26, #16, lsl #12
	add	x4, x8, #472
	add	x8, sp, #224
	add	x6, x8, #32
	add	x8, sp, #512
	add	x19, x8, #32
	add	x12, sp, #800
	add	x8, x12, #16
	str	x8, [sp, #120]
	add	x8, sp, #1200
	add	x8, x8, #32
	str	x8, [sp, #112]
	add	x8, sp, #1744
	add	x8, x8, #32
	str	x8, [sp, #104]
	add	x8, sp, #2544
	add	x27, x8, #32
	add	x8, sp, #2832
	add	x30, x8, #32
	add	x13, sp, #3120
	mov	x8, #47479
	movk	x8, #24011, lsl #16
	movk	x8, #29422, lsl #32
	movk	x8, #16439, lsl #48
	fmov	d0, x8
	mov	x8, #277076930199552
	movk	x8, #16543, lsl #48
	fmov	d1, x8
	mov	x8, #6148914691236517205
	movk	x8, #16341, lsl #48
	fmov	d2, x8
	add	x1, x13, #32
	fmov	d3, #1.00000000
	movi.2d	v4, #0000000000000000
	fmov	d5, #-1.00000000
	add	x13, sp, #3408
	add	x8, x13, #32
	add	x14, sp, #3952
	add	x5, x14, #32
	add	x14, sp, #1, lsl #12
	add	x14, x14, #400
	add	x15, x14, #32
	str	x15, [sp, #96]
	add	x15, sp, #1, lsl #12
	add	x15, x15, #944
	add	x2, x15, #32
	str	x2, [sp, #216]
	add	x2, sp, #1, lsl #12
	add	x2, x2, #1232
	add	x22, x2, #32
	add	x12, x12, #12
	str	x12, [sp, #88]
	add	x12, x14, #256
	str	x12, [sp, #80]
	add	x14, x13, #256
	add	x12, x15, #256
	stp	x12, x14, [sp, #64]
	add	x12, x2, #256
	str	x12, [sp, #56]
	mov	w14, #99
	mov	x21, #-4294967296
	mov	x23, #4294967296
	add	x2, sp, #944
	add	x28, sp, #1488
	add	x24, sp, #2288
	add	x20, sp, #3696
	add	x12, sp, #1, lsl #12
	add	x12, x12, #144
	add	x13, sp, #1, lsl #12
	add	x13, x13, #688
	str	x26, [sp, #128]
	stp	x9, x0, [sp, #16]
LBB0_1:
	str	xzr, [sp, #208]
	str	w14, [sp, #52]
	mov	x25, x9
	ldr	x9, [sp, #32]
	str	x9, [sp, #5328]
	add	x14, sp, #1, lsl #12
	add	x14, x14, #1232
	; InlineAsm Start
	; InlineAsm End
	ldr	x9, [sp, #40]
	str	x9, [sp, #5328]
	; InlineAsm Start
	; InlineAsm End
	ldr	x9, [x9]
	str	x9, [sp, #152]
	ldp	d16, d7, [x26, #24]
	fmaxnm	d29, d7, d0
	fmul	d6, d16, d29
	ldr	d17, [x26, #72]
	fadd	d7, d7, d17
	fmaxnm	d23, d7, d0
	fmul	d7, d16, d23
	ldp	d20, d19, [x26, #112]
	fmul	d16, d19, d20
	fadd	d17, d16, d3
	fdiv	d17, d3, d17
	ldp	d18, d30, [x26, #128]
	fmul	d19, d19, d18
	fmul	d19, d20, d19
	fdiv	d20, d3, d29
	fdiv	d21, d3, d23
	ldr	d24, [x26, #224]
	fdiv	d22, d24, d23
	fminnm	d22, d22, d1
	fmaxnm	d26, d22, d4
	fcvtzs	w14, d26
	scvtf	d27, w14
	fsub	d22, d26, d27
	fdiv	d24, d24, d29
	fminnm	d24, d24, d1
	fmaxnm	d25, d24, d4
	fcvtzs	w15, d25
	scvtf	d28, w15
	fdiv	d23, d30, d23
	fsub	d24, d3, d25
	fadd	d24, d24, d28
	fsub	d25, d25, d28
	fsub	d26, d3, d26
	fadd	d26, d26, d27
	ldr	d27, [x0, #264]
	fmul	d27, d27, d2
	ldr	d28, [x26, #136]
	ldp	w9, w7, [x25]
	str	w9, [sp, #204]
	mov	x9, x0
	ldr	w0, [x0]
	ldr	w9, [x9, #4]
	str	w9, [sp, #200]
	neg	w9, w14
	str	w9, [sp, #148]
	mvn	w9, w15
	str	w9, [sp, #144]
	neg	w9, w15
	str	w9, [sp, #140]
	mvn	w9, w14
	str	w9, [sp, #136]
	fdiv	d29, d30, d29
LBB0_2:
	mov	x14, #0
	ldur	q30, [x26, #40]
	ldur	q31, [x26, #56]
	stp	q30, q31, [sp, #224]
LBB0_3:
	lsl	x15, x14, #32
	add	x25, x15, x21
	asr	x25, x25, #29
	ldr	d30, [x6, x25]
	fadd	d31, d6, d30
	frintm	d31, d31
	fsub	d30, d30, d31
	fadd	d30, d6, d30
	str	d30, [x6, x14, lsl #3]
	add	x14, x15, x23
	asr	x14, x14, #32
	cmp	x14, #32
	b.lt	LBB0_3
	mov	x14, #0
	add	x9, sp, #224
	ldp	q30, q31, [x9, #256]
	stur	q30, [x26, #40]
	stur	q31, [x26, #56]
	ldp	q30, q31, [x26, #80]
	stp	q30, q31, [sp, #512]
LBB0_5:
	lsl	x15, x14, #32
	add	x25, x15, x21
	asr	x25, x25, #29
	ldr	d30, [x19, x25]
	fadd	d31, d7, d30
	frintm	d31, d31
	fsub	d30, d30, d31
	fadd	d30, d7, d30
	str	d30, [x19, x14, lsl #3]
	add	x14, x15, x23
	asr	x14, x14, #32
	cmp	x14, #32
	b.lt	LBB0_5
	mov	x14, #0
	add	x9, sp, #512
	ldp	q30, q31, [x9, #256]
	stp	q30, q31, [x26, #80]
	ldur	q30, [x26, #144]
	str	q30, [sp, #800]
	ldr	x9, [sp, #120]
	mov	w15, #1
LBB0_7:
	str	w15, [x9, x14, lsl #2]
	add	w14, w14, #1
	sxtw	x14, w14
	cmp	x14, #32
	b.lt	LBB0_7
	mov	x14, #0
	add	x9, sp, #800
	ldur	q30, [x9, #128]
	stur	q30, [x26, #144]
	ldp	q30, q31, [x26, #160]
	str	q30, [sp, #1200]
	str	q31, [sp, #1216]
	ldr	x9, [sp, #112]
LBB0_9:
	ldr	d30, [x6, x14, lsl #3]
	fadd	d30, d30, d30
	fadd	d30, d30, d5
	mov	w15, #2
	fmov	d31, #1.00000000
LBB0_10:
	fmul	d8, d31, d30
	tst	w15, #0x1
	fcsel	d31, d31, d8, eq
	fmul	d30, d30, d30
	lsr	w15, w15, #1
	cbnz	w15, LBB0_10
	str	d31, [x9, x14, lsl #3]
	add	w14, w14, #1
	sxtw	x14, w14
	cmp	x14, #32
	b.lt	LBB0_9
	mov	x14, #0
	add	x15, sp, #1200
	ldp	q30, q31, [x15, #256]
	add	x25, sp, #1200
	stp	q30, q31, [x26, #160]
	ldp	q30, q31, [x26, #192]
	str	q30, [sp, #1744]
	str	q31, [sp, #1760]
	ldr	x9, [sp, #104]
LBB0_13:
	ldr	d30, [x19, x14, lsl #3]
	fadd	d30, d30, d30
	fadd	d30, d30, d5
	mov	w15, #2
	fmov	d31, #1.00000000
LBB0_14:
	fmul	d8, d31, d30
	tst	w15, #0x1
	fcsel	d31, d31, d8, eq
	fmul	d30, d30, d30
	lsr	w15, w15, #1
	cbnz	w15, LBB0_14
	str	d31, [x9, x14, lsl #3]
	add	w14, w14, #1
	sxtw	x14, w14
	cmp	x14, #32
	b.lt	LBB0_13
	mov	x14, #0
	add	x15, sp, #1744
	ldp	q30, q31, [x15, #256]
	add	x9, sp, #1744
	stp	q30, q31, [x26, #192]
	ldr	x15, [sp, #88]
LBB0_17:
	ldr	s30, [x15, x14, lsl #2]
	sshll.2d	v30, v30, #0
	scvtf	d30, d30
	str	d30, [x2, x14, lsl #3]
	add	x14, x14, #1
	cmp	x14, #32
	b.ne	LBB0_17
	add	x14, sp, #1488
	add	x15, x25, #32
	mov	w25, #32
LBB0_19:
	ldp	d31, d30, [x15, #-8]
	fsub	d30, d30, d31
	str	d30, [x14], #8
	add	x15, x15, #8
	subs	x25, x25, #1
	b.ne	LBB0_19
	add	x14, sp, #2032
	add	x15, x9, #32
	mov	w25, #32
LBB0_21:
	ldp	d31, d30, [x15, #-8]
	fsub	d30, d30, d31
	str	d30, [x14], #8
	add	x15, x15, #8
	subs	x25, x25, #1
	b.ne	LBB0_21
	mov	x14, #0
	ldr	w9, [sp, #204]
	add	w15, w7, w9
	and	w9, w15, #0xfff
	str	w9, [sp, #164]
	add	x9, sp, #2032
LBB0_23:
	and	w25, w15, #0xfff
	ldr	d30, [x2, x14]
	ldr	d31, [x9, x14]
	fmul	d30, d30, d31
	fmul	d30, d23, d30
	str	d30, [x10, w25, uxtw #3]
	add	x14, x14, #8
	add	w15, w15, #1
	cmp	x14, #256
	b.ne	LBB0_23
	mov	x14, #0
	ldr	w9, [sp, #200]
	add	w15, w9, w0
	and	w9, w15, #0xfff
	str	w9, [sp, #160]
LBB0_25:
	and	w25, w15, #0xfff
	ldr	d30, [x2, x14]
	ldr	d31, [x28, x14]
	fmul	d30, d30, d31
	fmul	d30, d29, d30
	str	d30, [x11, w25, uxtw #3]
	add	x14, x14, #8
	add	w15, w15, #1
	cmp	x14, #256
	b.ne	LBB0_25
	mov	x25, #0
	ldr	w9, [sp, #148]
	ldp	w28, w26, [sp, #200]
	add	w14, w9, w26
	add	w15, w14, w7
	ldr	w9, [sp, #144]
	add	w14, w9, w0
	add	w14, w14, w28
	ldr	w9, [sp, #140]
	add	w0, w9, w0
	add	w0, w0, w28
	ldr	w9, [sp, #136]
	add	w26, w9, w26
	add	w26, w26, w7
	add	x7, sp, #1488
	add	x28, sp, #2032
LBB0_27:
	ldr	d30, [x7, x25, lsl #3]
	ldr	d31, [x28, x25, lsl #3]
	fmul	d31, d21, d31
	fmadd	d30, d20, d30, d31
	ldr	d31, [x2, x25, lsl #3]
	add	w9, w26, w25
	and	w9, w9, #0xfff
	ldr	d8, [x10, w9, uxtw #3]
	add	w9, w0, w25
	and	w9, w9, #0xfff
	ldr	d9, [x11, w9, uxtw #3]
	fmul	d30, d31, d30
	add	w9, w14, w25
	and	w9, w9, #0xfff
	ldr	d31, [x11, w9, uxtw #3]
	fmul	d31, d25, d31
	fmadd	d31, d24, d9, d31
	add	w9, w15, w25
	and	w9, w9, #0xfff
	ldr	d9, [x10, w9, uxtw #3]
	fmadd	d31, d26, d9, d31
	fmadd	d31, d22, d8, d31
	fnmsub	d30, d28, d30, d31
	str	d30, [x24, x25, lsl #3]
	add	x25, x25, #1
	cmp	x25, #32
	b.ne	LBB0_27
	mov	x15, #0
	ldr	x9, [sp, #192]
	ldp	q31, q30, [x9]
	str	q30, [sp, #2560]
	str	q31, [sp, #2544]
	ldr	x9, [sp, #208]
	ldr	x14, [sp, #152]
	add	x14, x14, x9, lsl #3
	ldr	d30, [sp, #2568]
LBB0_29:
	ldr	d31, [x24, x15]
	fmadd	d30, d19, d31, d30
	fmul	d30, d17, d30
	str	d30, [x27, x15]
	add	x15, x15, #8
	cmp	x15, #256
	b.ne	LBB0_29
	mov	x15, #0
	add	x9, sp, #2544
	ldp	q30, q31, [x9, #256]
	ldr	x9, [sp, #192]
	stp	q30, q31, [x9]
	ldr	x9, [sp, #184]
	ldp	q30, q31, [x9]
	str	q30, [sp, #2832]
	str	q31, [sp, #2848]
	ldr	x26, [sp, #128]
	add	x28, sp, #1488
LBB0_31:
	lsl	x9, x15, #32
	add	x0, x9, x21
	asr	x0, x0, #29
	ldr	d30, [x27, x15, lsl #3]
	ldr	d31, [x30, x0]
	fmadd	d30, d16, d30, d31
	fmul	d30, d17, d30
	str	d30, [x30, x15, lsl #3]
	add	x9, x9, x23
	asr	x15, x9, #32
	cmp	x15, #32
	b.lt	LBB0_31
	mov	x15, #0
	add	x9, sp, #2832
	ldp	q30, q31, [x9, #256]
	ldr	x9, [sp, #184]
	stp	q30, q31, [x9]
LBB0_33:
	ldr	d30, [x27, x15, lsl #3]
	mov	w0, #3
	fmov	d31, #1.00000000
LBB0_34:
	fmul	d8, d31, d30
	tst	w0, #0x1
	fcsel	d31, d31, d8, eq
	fmul	d30, d30, d30
	lsr	w0, w0, #1
	cbnz	w0, LBB0_34
	str	d31, [x20, x15, lsl #3]
	add	x15, x15, #1
	cmp	x15, #32
	b.ne	LBB0_33
	mov	x15, #0
	ldr	x9, [sp, #176]
	ldp	q30, q31, [x9]
	str	q30, [sp, #3120]
	str	q31, [sp, #3136]
LBB0_37:
	lsl	x9, x15, #32
	add	x0, x9, x21
	asr	x0, x0, #29
	ldr	d30, [x30, x15, lsl #3]
	ldr	d31, [x1, x0]
	fmadd	d30, d16, d30, d31
	fmul	d30, d17, d30
	str	d30, [x1, x15, lsl #3]
	add	x9, x9, x23
	asr	x15, x9, #32
	cmp	x15, #32
	b.lt	LBB0_37
	mov	x15, #0
	add	x9, sp, #3120
	ldp	q30, q31, [x9, #256]
	ldr	x9, [sp, #176]
	stp	q30, q31, [x9]
	ldr	x9, [sp, #168]
	ldp	q30, q31, [x9]
	str	q30, [sp, #3952]
	str	q31, [sp, #3968]
LBB0_39:
	lsl	x9, x15, #3
	and	x0, x9, #0x7fffffff8
	sub	x0, x0, #8
	ldr	d30, [x24, x9]
	fmul	d30, d18, d30
	mov	w25, #3
	fmov	d31, #1.00000000
LBB0_40:
	fmul	d8, d31, d30
	tst	w25, #0x1
	fcsel	d31, d31, d8, eq
	fmul	d30, d30, d30
	lsr	w25, w25, #1
	cbnz	w25, LBB0_40
	ldr	d30, [x20, x15, lsl #3]
	fsub	d30, d31, d30
	ldr	d31, [x5, x0]
	fmadd	d30, d16, d30, d31
	fmul	d30, d17, d30
	str	d30, [x5, x15, lsl #3]
	cmp	x15, #31
	add	x15, x15, #1
	b.ne	LBB0_39
	mov	x15, #0
	add	x9, sp, #3952
	ldp	q30, q31, [x9, #256]
	ldr	x9, [sp, #168]
	stp	q30, q31, [x9]
	add	x9, sp, #3408
	ldr	x25, [sp, #96]
LBB0_43:
	ldr	d30, [x30, x15, lsl #3]
	mov	w0, #3
	fmov	d31, #1.00000000
LBB0_44:
	fmul	d8, d31, d30
	tst	w0, #0x1
	fcsel	d31, d31, d8, eq
	fmul	d30, d30, d30
	lsr	w0, w0, #1
	cbnz	w0, LBB0_44
	str	d31, [x12, x15, lsl #3]
	add	x15, x15, #1
	cmp	x15, #32
	b.ne	LBB0_43
	mov	x15, #0
	add	x0, sp, #1, lsl #12
	add	x0, x0, #400
LBB0_47:
	ldr	d30, [x16, x15]
	str	d30, [x0, x15]
	add	x15, x15, #8
	cmp	x15, #32
	b.ne	LBB0_47
	mov	x15, #0
	ldr	d30, [sp, #4520]
LBB0_49:
	ldr	d31, [x5, x15]
	ldr	d8, [x20, x15]
	fadd	d31, d31, d8
	ldr	d8, [x12, x15]
	fsub	d31, d31, d8
	fmadd	d30, d16, d31, d30
	fmul	d30, d17, d30
	str	d30, [x25, x15]
	add	x15, x15, #8
	cmp	x15, #256
	b.ne	LBB0_49
	mov	x15, #0
	ldr	x0, [sp, #80]
LBB0_51:
	ldr	d30, [x0, x15]
	str	d30, [x16, x15]
	add	x15, x15, #8
	cmp	x15, #32
	b.ne	LBB0_51
	mov	x15, #0
LBB0_53:
	ldr	d30, [x1, x15, lsl #3]
	mov	w0, #3
	fmov	d31, #1.00000000
LBB0_54:
	fmul	d8, d31, d30
	tst	w0, #0x1
	fcsel	d31, d31, d8, eq
	fmul	d30, d30, d30
	lsr	w0, w0, #1
	cbnz	w0, LBB0_54
	str	d31, [x13, x15, lsl #3]
	add	x15, x15, #1
	cmp	x15, #32
	b.ne	LBB0_53
	mov	x15, #0
LBB0_57:
	ldr	d30, [x17, x15]
	str	d30, [x9, x15]
	add	x15, x15, #8
	cmp	x15, #32
	b.ne	LBB0_57
	mov	x15, #0
LBB0_59:
	lsl	x9, x15, #32
	add	x0, x9, x21
	asr	x0, x0, #29
	ldr	d30, [x1, x15, lsl #3]
	ldr	d31, [x8, x0]
	fmadd	d30, d16, d30, d31
	fmul	d30, d17, d30
	str	d30, [x8, x15, lsl #3]
	add	x9, x9, x23
	asr	x15, x9, #32
	cmp	x15, #32
	b.lt	LBB0_59
	mov	x15, #0
	ldr	x9, [sp, #72]
LBB0_61:
	ldr	d30, [x9, x15]
	str	d30, [x17, x15]
	add	x15, x15, #8
	cmp	x15, #32
	b.ne	LBB0_61
	mov	x15, #0
	add	x9, sp, #1, lsl #12
	add	x9, x9, #944
LBB0_63:
	ldr	d30, [x3, x15]
	str	d30, [x9, x15]
	add	x15, x15, #8
	cmp	x15, #32
	b.ne	LBB0_63
	mov	x15, #0
	ldr	d30, [sp, #5064]
	ldr	x9, [sp, #216]
LBB0_65:
	ldr	d31, [x25, x15]
	ldr	d8, [x12, x15]
	fadd	d31, d31, d8
	ldr	d8, [x13, x15]
	fsub	d31, d31, d8
	fmadd	d30, d16, d31, d30
	fmul	d30, d17, d30
	str	d30, [x9, x15]
	add	x15, x15, #8
	cmp	x15, #256
	b.ne	LBB0_65
	mov	x15, #0
	ldr	x9, [sp, #64]
LBB0_67:
	ldr	d30, [x9, x15]
	str	d30, [x3, x15]
	add	x15, x15, #8
	cmp	x15, #32
	b.ne	LBB0_67
	mov	x15, #0
	add	x9, sp, #1, lsl #12
	add	x9, x9, #1232
LBB0_69:
	ldr	d30, [x4, x15]
	str	d30, [x9, x15]
	add	x15, x15, #8
	cmp	x15, #32
	b.ne	LBB0_69
	mov	x15, #0
LBB0_71:
	lsl	x9, x15, #3
	and	x0, x9, #0x7fffffff8
	sub	x0, x0, #8
	ldr	x7, [sp, #216]
	ldr	d30, [x7, x9]
	ldr	d31, [x13, x9]
	ldr	d8, [x8, x9]
	mov	w25, #3
	fmov	d9, #1.00000000
LBB0_72:
	fmul	d10, d9, d8
	tst	w25, #0x1
	fcsel	d9, d9, d10, eq
	fmul	d8, d8, d8
	lsr	w25, w25, #1
	cbnz	w25, LBB0_72
	fadd	d30, d30, d31
	fsub	d30, d30, d9
	ldr	d31, [x22, x0]
	fmadd	d30, d16, d30, d31
	fmul	d30, d17, d30
	str	d30, [x22, x15, lsl #3]
	cmp	x15, #31
	add	x15, x15, #1
	b.ne	LBB0_71
	mov	x15, #0
	ldr	x9, [sp, #56]
LBB0_75:
	ldr	d30, [x9, x15]
	str	d30, [x4, x15]
	add	x15, x15, #8
	cmp	x15, #32
	b.ne	LBB0_75
	mov	x15, #0
LBB0_77:
	ldr	d30, [x22, x15, lsl #3]
	ldr	d31, [x8, x15, lsl #3]
	fmsub	d30, d27, d30, d31
	str	d30, [x14, x15, lsl #3]
	add	w9, w15, #1
	sxtw	x15, w9
	cmp	x15, #32
	b.lt	LBB0_77
	mov	w9, #32
	ldp	w15, w14, [sp, #160]
	mov	x0, x15
	mov	w7, #32
	stp	w9, w14, [sp, #200]
	ldr	x9, [sp, #208]
	cmp	x9, #449
	add	x9, x9, #32
	str	x9, [sp, #208]
	b.lo	LBB0_2
	ldp	x9, x0, [sp, #16]
	str	w14, [x9]
	mov	w14, #32
	str	w14, [x9, #4]
	stp	w15, w14, [x0]
	;MEMBARRIER
	ldr	w15, [sp, #52]
	sub	w14, w15, #1
	cbnz	w15, LBB0_1
	add	sp, sp, #1, lsl #12
	add	sp, sp, #1520
	ldp	x29, x30, [sp, #112]
	ldp	x20, x19, [sp, #96]
	ldp	x22, x21, [sp, #80]
	ldp	x24, x23, [sp, #64]
	ldp	x26, x25, [sp, #48]
	ldp	x28, x27, [sp, #32]
	ldp	d9, d8, [sp, #16]
	ldp	d11, d10, [sp], #128
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
	.quad	0x40f7700000000000
	.quad	0x3ee5d867c3ece2a5
lCPI3_1:
	.quad	0x3f112843cf07a12c
	.quad	0x4085e00000000000
lCPI3_2:
	.quad	0x3fe0000000000000
	.quad	0x40d7700000000000
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
	mov	w1, #512
	movk	w1, #1, lsl #16
	bl	_KGEN_CompilerRT_AlignedAlloc
	cbz	x0, LBB3_5
	mov	x19, x0
	str	xzr, [x0]
	mov	w8, #30464
	movk	w8, #1, lsl #16
	str	w8, [x0, #8]
Lloh6:
	adrp	x8, lCPI3_0@PAGE
Lloh7:
	ldr	q0, [x8, lCPI3_0@PAGEOFF]
	str	q0, [x0, #16]
	mov	x8, #123145302310912
	movk	x8, #16615, lsl #48
	str	x8, [x0, #224]
	mov	x8, #140737488355328
	movk	x8, #16507, lsl #48
	str	x8, [x0, #32]
	mov	x8, #4611686018427387904
	str	x8, [x0, #72]
Lloh8:
	adrp	x8, lCPI3_1@PAGE
Lloh9:
	ldr	q0, [x8, lCPI3_1@PAGEOFF]
Lloh10:
	adrp	x8, lCPI3_2@PAGE
Lloh11:
	ldr	q1, [x8, lCPI3_2@PAGEOFF]
	stp	q0, q1, [x0, #112]
	movi.2d	v0, #0000000000000000
	stur	q0, [x0, #40]
	stur	q0, [x0, #56]
	stp	q0, q0, [x0, #80]
	stp	q0, q0, [x0, #144]
	stp	q0, q0, [x0, #176]
	str	q0, [x0, #208]
	add	x0, x0, #232
	mov	w1, #280
	movk	w1, #1, lsl #16
	bl	_bzero
	mov	w0, #16
	mov	w1, #4112
	bl	_KGEN_CompilerRT_AlignedAlloc
	cbz	x0, LBB3_5
	add	x8, x0, #8
	str	x8, [x0]
	mov	x20, x0
	mov	x0, x8
	mov	w1, #4096
	bl	_bzero
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
