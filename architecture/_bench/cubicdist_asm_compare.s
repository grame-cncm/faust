;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; CPP:

__ZN5mydsp7computeEiPPdS1_:             ; @_ZN5mydsp7computeEiPPdS1_
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
	mov	w9, #21504                      ; =0x5400
Lloh276:
	adrp	x16, ___chkstk_darwin@GOTPAGE
Lloh277:
	ldr	x16, [x16, ___chkstk_darwin@GOTPAGEOFF]
	blr	x16
	sub	sp, sp, #5, lsl #12             ; =20480
	sub	sp, sp, #1024
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
	str	w1, [sp, #12]                   ; 4-byte Folded Spill
	mov	x19, x0
Lloh278:
	adrp	x8, ___stack_chk_guard@GOTPAGE
Lloh279:
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
Lloh280:
	ldr	x8, [x8]
	stur	x8, [x29, #-168]
	ldp	x10, x8, [x3]
	stp	x10, x8, [sp, #344]             ; 16-byte Folded Spill
	ldr	d8, [x0, #8]
	mov	w20, #4719                      ; =0x126f
	movk	w20, #14979, lsl #16
	ldr	d0, [x0, #32]
	fcvt	s0, d0
	mov	w8, #52429                      ; =0xcccd
	movk	w8, #15692, lsl #16
	fmov	s1, w8
	fmul	s0, s0, s1
	bl	___exp10f
	fmov	s10, s0
	ldr	d0, [x19, #56]
	fcvt	s0, d0
	movi	d1, #0000000000000000
	str	s1, [sp, #892]                  ; 4-byte Folded Spill
	fcmp	s0, #0.0
	movi	d13, #0000000000000000
	b.le	LBB17_2
; %bb.1:
	ldr	s1, [x19, #72]
	fneg	s1, s1
	fdiv	s0, s1, s0
	bl	_expf
	fmov	s13, s0
LBB17_2:
	fcvt	s9, d8
	fmov	s8, w20
	add	x20, sp, #5, lsl #12            ; =20480
	add	x20, x20, #848
	ldr	d0, [x19, #80]
	fcvt	s0, d0
	mov	w8, #-1035730944                ; =0xc2440000
	fmov	s1, w8
	fadd	s0, s0, s1
	mov	w8, #43691                      ; =0xaaab
	movk	w8, #15786, lsl #16
	fmov	s1, w8
	fmul	s0, s0, s1
	bl	_exp2f
	mov	w8, #1138491392                 ; =0x43dc0000
	fmov	s1, w8
	fmul	s12, s0, s1
	fmov	s11, #1.00000000
	str	s13, [sp, #820]                 ; 4-byte Folded Spill
	fsub	s14, s11, s13
	add	x22, sp, #5, lsl #12            ; =20480
	add	x22, x22, #32
	add	x21, sp, #4, lsl #12            ; =16384
	add	x21, x21, #3840
	ldr	d0, [x19, #160]
	fcvt	s13, d0
	mov	w8, #4719                       ; =0x126f
	movk	w8, #14979, lsl #16
	fmov	s15, w8
	add	x23, sp, #4, lsl #12            ; =16384
	add	x23, x23, #3696
	ldr	d0, [x19, #184]
	fcvt	s0, d0
	fcvtzs	w15, s0
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2880
	add	x8, x8, #16
	str	x8, [sp, #488]                  ; 8-byte Folded Spill
	add	x25, sp, #4, lsl #12            ; =16384
	add	x25, x25, #2736
	add	x26, sp, #4, lsl #12            ; =16384
	add	x26, x26, #2592
	ldr	d0, [x19, #352]
	fcvt	s0, d0
	fmul	s1, s0, s15
	fcmp	s1, #0.0
	str	w15, [sp, #3336]                ; 4-byte Folded Spill
	b.le	LBB17_4
; %bb.3:
	ldr	s1, [x19, #360]
	fneg	s1, s1
	fdiv	s0, s1, s0
	bl	_expf
	ldr	w15, [sp, #3336]                ; 4-byte Folded Reload
	str	s0, [sp, #892]                  ; 4-byte Folded Spill
LBB17_4:
	add	x28, sp, #4, lsl #12            ; =16384
	add	x28, x28, #3152
	add	x8, x20, #16
	str	x8, [sp, #3352]                 ; 8-byte Folded Spill
	fmul	s9, s9, s8
	add	x16, x22, #16
	fmul	s10, s10, s8
	add	x17, x21, #16
	add	x8, x23, #16
	str	x8, [sp, #3344]                 ; 8-byte Folded Spill
	fmul	s2, s14, s12
	add	x8, x25, #16
	str	x8, [sp, #3200]                 ; 8-byte Folded Spill
	add	x8, x26, #16
	str	x8, [sp, #784]                  ; 8-byte Folded Spill
	fmul	s8, s13, s15
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2304
	ldr	s12, [sp, #892]                 ; 4-byte Folded Reload
	fsub	s13, s11, s12
	add	x8, x8, #16
	str	x8, [sp, #600]                  ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2160
	add	x8, x8, #16
	str	x8, [sp, #456]                  ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2016
	add	x8, x8, #16
	str	x8, [sp, #360]                  ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1744
	add	x13, x8, #16
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1600
	add	x8, x8, #16
	str	x8, [sp, #3296]                 ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1456
	add	x8, x8, #16
	str	x8, [sp, #800]                  ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1168
	add	x8, x8, #16
	str	x8, [sp, #672]                  ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1024
	add	x25, x8, #16
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #880
	add	x8, x8, #16
	str	x8, [sp, #368]                  ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #608
	add	x8, x8, #16
	str	x8, [sp, #744]                  ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #464
	ldr	d0, [x19, #3952]
	fcvt	s0, d0
	str	s0, [sp, #340]                  ; 4-byte Folded Spill
	fmov.4s	v0, #1.00000000
	str	q0, [sp, #320]                  ; 16-byte Folded Spill
	add	x8, x8, #16
	str	x8, [sp, #3280]                 ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #320
	add	x8, x8, #16
	str	x8, [sp, #3264]                 ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #32
	add	x8, x8, #16
	str	x8, [sp, #872]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3984
	add	x8, x8, #16
	str	x8, [sp, #608]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3840
	add	x20, x8, #16
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3568
	add	x8, x8, #16
	str	x8, [sp, #712]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3424
	add	x23, x8, #16
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3280
	add	x8, x8, #16
	str	x8, [sp, #3328]                 ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2992
	add	x8, x8, #16
	str	x8, [sp, #680]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2848
	add	x12, x8, #16
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2704
	add	x8, x8, #16
	str	x8, [sp, #376]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2432
	add	x8, x8, #16
	str	x8, [sp, #720]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2288
	add	x8, x8, #16
	str	x8, [sp, #3288]                 ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2144
	add	x8, x8, #16
	str	x8, [sp, #3272]                 ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1856
	add	x0, x8, #16
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1712
	add	x8, x8, #16
	str	x8, [sp, #624]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1568
	add	x8, x8, #16
	str	x8, [sp, #384]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1296
	add	x11, x8, #16
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1152
	add	x8, x8, #16
	str	x8, [sp, #3208]                 ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1008
	add	x8, x8, #16
	str	x8, [sp, #792]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #720
	add	x8, x8, #16
	str	x8, [sp, #688]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #576
	add	x10, x8, #16
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #432
	add	x8, x8, #16
	str	x8, [sp, #392]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #160
	add	x8, x8, #16
	str	x8, [sp, #752]                  ; 8-byte Folded Spill
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #16
	add	x8, x8, #16
	str	x8, [sp, #3304]                 ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3968
	add	x8, x8, #16
	str	x8, [sp, #808]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3680
	add	x30, x8, #16
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3536
	add	x27, x8, #16
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3392
	add	x8, x8, #16
	str	x8, [sp, #400]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3120
	add	x9, x8, #16
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2976
	add	x8, x8, #16
	str	x8, [sp, #3216]                 ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2832
	add	x21, x8, #16
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2544
	add	x22, x8, #16
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2400
	add	x8, x8, #16
	str	x8, [sp, #464]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2256
	add	x8, x8, #16
	str	x8, [sp, #408]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1984
	add	x8, x8, #16
	str	x8, [sp, #768]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1840
	add	x8, x8, #16
	str	x8, [sp, #3224]                 ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1696
	add	x14, x8, #16
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1408
	add	x7, x8, #16
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1264
	add	x8, x8, #16
	str	x8, [sp, #648]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1120
	add	x8, x8, #16
	str	x8, [sp, #416]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #848
	add	x8, x8, #16
	str	x8, [sp, #904]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #704
	add	x8, x8, #16
	str	x8, [sp, #3232]                 ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #560
	add	x8, x8, #16
	str	x8, [sp, #528]                  ; 8-byte Folded Spill
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #272
	add	x6, x8, #16
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #128
	add	x8, x8, #16
	str	x8, [sp, #472]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #4080
	add	x8, x8, #16
	str	x8, [sp, #424]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #3808
	add	x8, x8, #16
	str	x8, [sp, #776]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #3664
	add	x8, x8, #16
	str	x8, [sp, #3240]                 ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #3520
	add	x26, x8, #16
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #3232
	add	x5, x8, #16
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #3088
	add	x8, x8, #16
	str	x8, [sp, #656]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2944
	add	x8, x8, #16
	str	x8, [sp, #432]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2672
	add	x8, x8, #16
	str	x8, [sp, #880]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2528
	add	x8, x8, #16
	str	x8, [sp, #3248]                 ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2384
	add	x1, x8, #16
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2096
	add	x4, x8, #16
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1952
	add	x8, x8, #16
	str	x8, [sp, #480]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1808
	add	x8, x8, #16
	str	x8, [sp, #440]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1536
	add	x8, x8, #16
	str	x8, [sp, #496]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1392
	add	x8, x8, #16
	str	x8, [sp, #3312]                 ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1248
	add	x24, x8, #16
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #960
	add	x8, x8, #16
	str	x8, [sp, #896]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #816
	add	x8, x8, #16
	str	x8, [sp, #664]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #672
	add	x8, x8, #16
	str	x8, [sp, #448]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #400
	add	x8, x8, #16
	str	x8, [sp, #504]                  ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #256
	add	x8, x8, #16
	str	x8, [sp, #3256]                 ; 8-byte Folded Spill
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #112
	add	x3, x8, #16
	add	x8, sp, #3920
	add	x8, x8, #16
	str	x8, [sp, #512]                  ; 8-byte Folded Spill
	add	x8, sp, #3776
	add	x8, x8, #16
	str	x8, [sp, #3320]                 ; 8-byte Folded Spill
	add	x8, sp, #3632
	add	x2, x8, #16
	ldr	w8, [sp, #12]                   ; 4-byte Folded Reload
	subs	w8, w8, #32
	str	x8, [sp, #304]                  ; 8-byte Folded Spill
	str	x2, [sp, #568]                  ; 8-byte Folded Spill
	str	x3, [sp, #560]                  ; 8-byte Folded Spill
	str	x24, [sp, #552]                 ; 8-byte Folded Spill
	str	x1, [sp, #544]                  ; 8-byte Folded Spill
	str	x26, [sp, #536]                 ; 8-byte Folded Spill
	str	x10, [sp, #632]                 ; 8-byte Folded Spill
	str	x12, [sp, #616]                 ; 8-byte Folded Spill
	str	x16, [sp, #704]                 ; 8-byte Folded Spill
	str	x17, [sp, #696]                 ; 8-byte Folded Spill
	str	x14, [sp, #520]                 ; 8-byte Folded Spill
	str	x21, [sp, #584]                 ; 8-byte Folded Spill
	str	x23, [sp, #576]                 ; 8-byte Folded Spill
	str	x9, [sp, #760]                  ; 8-byte Folded Spill
	str	x11, [sp, #736]                 ; 8-byte Folded Spill
	str	x13, [sp, #728]                 ; 8-byte Folded Spill
	str	x4, [sp, #864]                  ; 8-byte Folded Spill
	str	x5, [sp, #856]                  ; 8-byte Folded Spill
	str	x6, [sp, #848]                  ; 8-byte Folded Spill
	str	x7, [sp, #840]                  ; 8-byte Folded Spill
	str	x22, [sp, #832]                 ; 8-byte Folded Spill
	str	x27, [sp, #640]                 ; 8-byte Folded Spill
	str	x30, [sp, #824]                 ; 8-byte Folded Spill
	b.ge	LBB17_6
; %bb.5:
	mov	w10, #0                         ; =0x0
	ldr	s1, [sp, #820]                  ; 4-byte Folded Reload
	ldr	w8, [sp, #12]                   ; 4-byte Folded Reload
	subs	w1, w8, w10
	ldr	x26, [sp, #872]                 ; 8-byte Folded Reload
	b.gt	LBB17_157
	b	LBB17_776
LBB17_6:
	str	x0, [sp, #592]                  ; 8-byte Folded Spill
	str	s13, [sp, #316]                 ; 4-byte Folded Spill
	mov	x10, #0                         ; =0x0
	cmp	w15, #0
	cset	w8, eq
	add	x11, x19, #404
	add	x9, x19, #444
	str	x9, [sp, #3168]                 ; 8-byte Folded Spill
	add	x9, x19, #668
	stp	x9, x11, [sp, #264]             ; 16-byte Folded Spill
	add	x9, x19, #708
	str	x9, [sp, #3152]                 ; 8-byte Folded Spill
	add	x9, x19, #744
	str	x9, [sp, #3144]                 ; 8-byte Folded Spill
	add	x11, x19, #932
	add	x9, x19, #972
	str	x9, [sp, #3136]                 ; 8-byte Folded Spill
	add	x9, x19, #1196
	stp	x9, x11, [sp, #248]             ; 16-byte Folded Spill
	add	x9, x19, #1236
	str	x9, [sp, #3128]                 ; 8-byte Folded Spill
	add	x9, x19, #1272
	str	x9, [sp, #3120]                 ; 8-byte Folded Spill
	add	x11, x19, #1460
	add	x9, x19, #1500
	str	x9, [sp, #3112]                 ; 8-byte Folded Spill
	add	x9, x19, #1536
	str	x9, [sp, #3104]                 ; 8-byte Folded Spill
	add	x9, x19, #1724
	stp	x9, x11, [sp, #232]             ; 16-byte Folded Spill
	add	x9, x19, #1764
	str	x9, [sp, #3096]                 ; 8-byte Folded Spill
	add	x9, x19, #1800
	str	x9, [sp, #3088]                 ; 8-byte Folded Spill
	add	x11, x19, #1988
	add	x9, x19, #2028
	str	x9, [sp, #3080]                 ; 8-byte Folded Spill
	add	x9, x19, #2064
	str	x9, [sp, #3072]                 ; 8-byte Folded Spill
	add	x9, x19, #2252
	stp	x9, x11, [sp, #216]             ; 16-byte Folded Spill
	add	x9, x19, #2292
	str	x9, [sp, #3064]                 ; 8-byte Folded Spill
	add	x9, x19, #2328
	str	x9, [sp, #3056]                 ; 8-byte Folded Spill
	add	x11, x19, #2516
	add	x9, x19, #2556
	str	x9, [sp, #3048]                 ; 8-byte Folded Spill
	add	x9, x19, #2592
	str	x9, [sp, #3040]                 ; 8-byte Folded Spill
	add	x9, x19, #2780
	stp	x9, x11, [sp, #200]             ; 16-byte Folded Spill
	add	x9, x19, #2820
	str	x9, [sp, #3032]                 ; 8-byte Folded Spill
	add	x9, x19, #2856
	str	x9, [sp, #3024]                 ; 8-byte Folded Spill
	add	x9, x19, #3044
	str	x9, [sp, #192]                  ; 8-byte Folded Spill
	dup.4h	v0, w8
	mov	w8, #48759                      ; =0xbe77
	movk	w8, #16255, lsl #16
	str	w8, [sp, #188]                  ; 4-byte Folded Spill
	fmov	s12, #-1.00000000
	ushll.4s	v0, v0, #0
	shl.4s	v0, v0, #31
	cmlt.4s	v0, v0, #0
	str	q0, [sp, #160]                  ; 16-byte Folded Spill
	add	x8, x19, #3084
	str	x8, [sp, #3016]                 ; 8-byte Folded Spill
	add	x8, x19, #3120
	str	x8, [sp, #3008]                 ; 8-byte Folded Spill
	add	x9, x19, #3308
	add	x8, x19, #3348
	str	x8, [sp, #3000]                 ; 8-byte Folded Spill
	add	x8, x19, #3384
	str	x8, [sp, #2992]                 ; 8-byte Folded Spill
	add	x8, x19, #3572
	stp	x8, x9, [sp, #144]              ; 16-byte Folded Spill
	add	x8, x19, #3612
	str	x8, [sp, #2984]                 ; 8-byte Folded Spill
	add	x8, x19, #3648
	str	x8, [sp, #2976]                 ; 8-byte Folded Spill
	add	x8, x19, #532
	str	x8, [sp, #2968]                 ; 8-byte Folded Spill
	add	x8, x19, #796
	str	x8, [sp, #2960]                 ; 8-byte Folded Spill
	add	x8, x19, #1060
	str	x8, [sp, #2952]                 ; 8-byte Folded Spill
	add	x8, x19, #1324
	str	x8, [sp, #2944]                 ; 8-byte Folded Spill
	add	x9, x19, #1588
	add	x8, x19, #1852
	stp	x8, x9, [sp, #128]              ; 16-byte Folded Spill
	add	x9, x19, #2116
	add	x8, x19, #2380
	stp	x8, x9, [sp, #104]              ; 16-byte Folded Spill
	add	x9, x19, #2644
	add	x8, x19, #2908
	stp	x8, x9, [sp, #88]               ; 16-byte Folded Spill
	add	x9, x19, #3172
	add	x8, x19, #3436
	stp	x8, x9, [sp, #72]               ; 16-byte Folded Spill
	add	x9, x19, #3700
	add	x8, x19, #3836
	stp	x8, x9, [sp, #56]               ; 16-byte Folded Spill
	add	x22, x19, #292
	add	x24, x19, #572
	add	x26, x19, #836
	add	x27, x19, #1100
	add	x8, x19, #1364
	str	x8, [sp, #2936]                 ; 8-byte Folded Spill
	add	x8, x19, #1628
	str	x8, [sp, #2928]                 ; 8-byte Folded Spill
	add	x8, x19, #1892
	str	x8, [sp, #2920]                 ; 8-byte Folded Spill
	add	x8, x19, #2156
	str	x8, [sp, #2912]                 ; 8-byte Folded Spill
	add	x8, x19, #2420
	str	x8, [sp, #2904]                 ; 8-byte Folded Spill
	add	x8, x19, #2684
	str	x8, [sp, #2896]                 ; 8-byte Folded Spill
	add	x8, x19, #2948
	str	x8, [sp, #2888]                 ; 8-byte Folded Spill
	add	x8, x19, #3212
	str	x8, [sp, #2880]                 ; 8-byte Folded Spill
	add	x8, x19, #3476
	str	x8, [sp, #2872]                 ; 8-byte Folded Spill
	add	x8, x19, #3740
	str	x8, [sp, #2864]                 ; 8-byte Folded Spill
	add	x8, x19, #3876
	str	x8, [sp, #2856]                 ; 8-byte Folded Spill
	add	x8, x19, #332
	str	x8, [sp, #2848]                 ; 8-byte Folded Spill
	add	x8, x19, #612
	str	x8, [sp, #2840]                 ; 8-byte Folded Spill
	add	x8, x19, #876
	str	x8, [sp, #2832]                 ; 8-byte Folded Spill
	add	x8, x19, #1140
	str	x8, [sp, #2824]                 ; 8-byte Folded Spill
	add	x8, x19, #1404
	str	x8, [sp, #2816]                 ; 8-byte Folded Spill
	add	x8, x19, #1668
	str	x8, [sp, #2808]                 ; 8-byte Folded Spill
	add	x8, x19, #1932
	str	x8, [sp, #2800]                 ; 8-byte Folded Spill
	add	x8, x19, #2196
	str	x8, [sp, #2792]                 ; 8-byte Folded Spill
	add	x8, x19, #2460
	str	x8, [sp, #2784]                 ; 8-byte Folded Spill
	add	x8, x19, #2724
	str	x8, [sp, #2776]                 ; 8-byte Folded Spill
	add	x8, x19, #2988
	str	x8, [sp, #2768]                 ; 8-byte Folded Spill
	add	x8, x19, #3252
	str	x8, [sp, #2760]                 ; 8-byte Folded Spill
	add	x8, x19, #3516
	str	x8, [sp, #2752]                 ; 8-byte Folded Spill
	add	x8, x19, #3780
	str	x8, [sp, #2744]                 ; 8-byte Folded Spill
	add	x8, x19, #3912
	str	x8, [sp, #2736]                 ; 8-byte Folded Spill
	add	x8, x19, #376
	str	x8, [sp, #2728]                 ; 8-byte Folded Spill
	add	x8, x19, #904
	str	x8, [sp, #2720]                 ; 8-byte Folded Spill
	add	x8, x19, #1168
	str	x8, [sp, #2712]                 ; 8-byte Folded Spill
	add	x8, x19, #1432
	str	x8, [sp, #2704]                 ; 8-byte Folded Spill
	add	x8, x19, #1696
	str	x8, [sp, #2696]                 ; 8-byte Folded Spill
	add	x8, x19, #1960
	str	x8, [sp, #2688]                 ; 8-byte Folded Spill
	add	x8, x19, #2224
	str	x8, [sp, #2680]                 ; 8-byte Folded Spill
	add	x8, x19, #2488
	str	x8, [sp, #2672]                 ; 8-byte Folded Spill
	add	x8, x19, #2752
	str	x8, [sp, #2664]                 ; 8-byte Folded Spill
	add	x8, x19, #3016
	str	x8, [sp, #2656]                 ; 8-byte Folded Spill
	add	x8, x19, #3280
	str	x8, [sp, #2648]                 ; 8-byte Folded Spill
	add	x8, x19, #3544
	str	x8, [sp, #2640]                 ; 8-byte Folded Spill
	add	x8, x19, #3808
	str	x8, [sp, #2632]                 ; 8-byte Folded Spill
	add	x8, x19, #3936
	str	x8, [sp, #2624]                 ; 8-byte Folded Spill
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3984
	add	x8, x8, #12
	stp	x8, x27, [sp, #16]              ; 16-byte Folded Spill
	ldr	s1, [sp, #820]                  ; 4-byte Folded Reload
	str	x25, [sp, #296]                 ; 8-byte Folded Spill
	str	s8, [sp, #292]                  ; 4-byte Folded Spill
	str	s9, [sp, #288]                  ; 4-byte Folded Spill
	str	s10, [sp, #284]                 ; 4-byte Folded Spill
	str	s2, [sp, #280]                  ; 4-byte Folded Spill
	str	x20, [sp, #120]                 ; 8-byte Folded Spill
	stp	x24, x22, [sp, #40]             ; 16-byte Folded Spill
	str	x26, [sp, #32]                  ; 8-byte Folded Spill
LBB17_7:                                ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB17_8 Depth 2
                                        ;     Child Loop BB17_11 Depth 2
                                        ;     Child Loop BB17_14 Depth 2
                                        ;     Child Loop BB17_16 Depth 2
                                        ;     Child Loop BB17_18 Depth 2
                                        ;     Child Loop BB17_20 Depth 2
                                        ;     Child Loop BB17_22 Depth 2
                                        ;     Child Loop BB17_24 Depth 2
                                        ;     Child Loop BB17_26 Depth 2
                                        ;     Child Loop BB17_28 Depth 2
                                        ;     Child Loop BB17_30 Depth 2
                                        ;     Child Loop BB17_32 Depth 2
                                        ;     Child Loop BB17_34 Depth 2
                                        ;     Child Loop BB17_36 Depth 2
                                        ;     Child Loop BB17_38 Depth 2
                                        ;     Child Loop BB17_40 Depth 2
                                        ;     Child Loop BB17_42 Depth 2
                                        ;     Child Loop BB17_44 Depth 2
                                        ;     Child Loop BB17_46 Depth 2
                                        ;     Child Loop BB17_48 Depth 2
                                        ;     Child Loop BB17_50 Depth 2
                                        ;     Child Loop BB17_52 Depth 2
                                        ;     Child Loop BB17_54 Depth 2
                                        ;     Child Loop BB17_56 Depth 2
                                        ;     Child Loop BB17_58 Depth 2
                                        ;     Child Loop BB17_60 Depth 2
                                        ;     Child Loop BB17_62 Depth 2
                                        ;     Child Loop BB17_64 Depth 2
                                        ;     Child Loop BB17_66 Depth 2
                                        ;     Child Loop BB17_68 Depth 2
                                        ;     Child Loop BB17_70 Depth 2
                                        ;     Child Loop BB17_72 Depth 2
                                        ;     Child Loop BB17_74 Depth 2
                                        ;     Child Loop BB17_76 Depth 2
                                        ;     Child Loop BB17_78 Depth 2
                                        ;     Child Loop BB17_80 Depth 2
                                        ;     Child Loop BB17_82 Depth 2
                                        ;     Child Loop BB17_84 Depth 2
                                        ;     Child Loop BB17_86 Depth 2
                                        ;     Child Loop BB17_88 Depth 2
                                        ;     Child Loop BB17_90 Depth 2
                                        ;     Child Loop BB17_92 Depth 2
                                        ;     Child Loop BB17_94 Depth 2
                                        ;     Child Loop BB17_96 Depth 2
                                        ;     Child Loop BB17_98 Depth 2
                                        ;     Child Loop BB17_100 Depth 2
                                        ;     Child Loop BB17_102 Depth 2
                                        ;     Child Loop BB17_104 Depth 2
                                        ;     Child Loop BB17_106 Depth 2
                                        ;     Child Loop BB17_108 Depth 2
                                        ;     Child Loop BB17_110 Depth 2
                                        ;     Child Loop BB17_112 Depth 2
                                        ;     Child Loop BB17_114 Depth 2
                                        ;     Child Loop BB17_116 Depth 2
                                        ;     Child Loop BB17_118 Depth 2
                                        ;     Child Loop BB17_120 Depth 2
                                        ;     Child Loop BB17_122 Depth 2
                                        ;     Child Loop BB17_124 Depth 2
                                        ;     Child Loop BB17_126 Depth 2
                                        ;     Child Loop BB17_128 Depth 2
                                        ;     Child Loop BB17_130 Depth 2
                                        ;     Child Loop BB17_132 Depth 2
                                        ;     Child Loop BB17_134 Depth 2
                                        ;     Child Loop BB17_136 Depth 2
                                        ;     Child Loop BB17_138 Depth 2
                                        ;     Child Loop BB17_140 Depth 2
                                        ;     Child Loop BB17_142 Depth 2
                                        ;     Child Loop BB17_144 Depth 2
                                        ;     Child Loop BB17_146 Depth 2
                                        ;     Child Loop BB17_148 Depth 2
                                        ;     Child Loop BB17_150 Depth 2
                                        ;     Child Loop BB17_152 Depth 2
                                        ;     Child Loop BB17_154 Depth 2
	ldur	q0, [x19, #88]
	str	q0, [sp, #21040]
	ldr	s0, [x28, #1516]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1520]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1524]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1528]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1532]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1536]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1540]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1544]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1548]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1552]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1556]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1560]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1564]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1568]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1572]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1576]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1580]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1584]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1588]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1592]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1596]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1600]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1604]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1608]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1612]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1616]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1620]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1624]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1628]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1632]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1636]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1640]
	fmadd	s0, s0, s1, s2
	str	s0, [x28, #1644]
	add	x8, sp, #5, lsl #12             ; =20480
	add	x8, x8, #560
	ldur	q0, [x8, #128]
	stur	q0, [x19, #88]
	ldr	s0, [x19, #104]
	ldr	q1, [sp, #21056]
	ldr	q2, [sp, #21072]
	fmul.4s	v1, v1, v0[0]
	fmul.4s	v2, v2, v0[0]
	str	q1, [sp, #20912]
	str	q2, [sp, #20928]
	ldr	q1, [sp, #21088]
	ldr	q2, [sp, #21104]
	fmul.4s	v1, v1, v0[0]
	fmul.4s	v2, v2, v0[0]
	str	q1, [sp, #20944]
	str	q2, [sp, #20960]
	ldr	q1, [sp, #21120]
	ldr	q2, [sp, #21136]
	fmul.4s	v1, v1, v0[0]
	fmul.4s	v2, v2, v0[0]
	str	q1, [sp, #20976]
	str	q2, [sp, #20992]
	ldr	q1, [sp, #21152]
	ldr	q2, [sp, #21168]
	fmul.4s	v1, v1, v0[0]
	fmul.4s	v0, v2, v0[0]
	ldr	x8, [sp, #344]                  ; 8-byte Folded Reload
	str	x10, [sp, #3192]                ; 8-byte Folded Spill
	add	x8, x8, x10, lsl #3
	str	x8, [sp, #2616]                 ; 8-byte Folded Spill
	str	q1, [sp, #21008]
	str	q0, [sp, #21024]
	ldr	s0, [x28, #1376]
	bl	_sinf
	str	s0, [x28, #1248]
	ldr	s0, [x28, #1380]
	bl	_sinf
	str	s0, [x28, #1252]
	ldr	s0, [x28, #1384]
	bl	_sinf
	str	s0, [x28, #1256]
	ldr	s0, [x28, #1388]
	bl	_sinf
	str	s0, [x28, #1260]
	ldr	s0, [x28, #1392]
	bl	_sinf
	str	s0, [x28, #1264]
	ldr	s0, [x28, #1396]
	bl	_sinf
	str	s0, [x28, #1268]
	ldr	s0, [x28, #1400]
	bl	_sinf
	str	s0, [x28, #1272]
	ldr	s0, [x28, #1404]
	bl	_sinf
	str	s0, [x28, #1276]
	ldr	s0, [x28, #1408]
	bl	_sinf
	str	s0, [x28, #1280]
	ldr	s0, [x28, #1412]
	bl	_sinf
	str	s0, [x28, #1284]
	ldr	s0, [x28, #1416]
	bl	_sinf
	str	s0, [x28, #1288]
	ldr	s0, [x28, #1420]
	bl	_sinf
	str	s0, [x28, #1292]
	ldr	s0, [x28, #1424]
	bl	_sinf
	str	s0, [x28, #1296]
	ldr	s0, [x28, #1428]
	bl	_sinf
	str	s0, [x28, #1300]
	ldr	s0, [x28, #1432]
	bl	_sinf
	str	s0, [x28, #1304]
	ldr	s0, [x28, #1436]
	bl	_sinf
	str	s0, [x28, #1308]
	ldr	s0, [x28, #1440]
	bl	_sinf
	str	s0, [x28, #1312]
	ldr	s0, [x28, #1444]
	bl	_sinf
	str	s0, [x28, #1316]
	ldr	s0, [x28, #1448]
	bl	_sinf
	str	s0, [x28, #1320]
	ldr	s0, [x28, #1452]
	bl	_sinf
	str	s0, [x28, #1324]
	ldr	s0, [x28, #1456]
	bl	_sinf
	str	s0, [x28, #1328]
	ldr	s0, [x28, #1460]
	bl	_sinf
	str	s0, [x28, #1332]
	ldr	s0, [x28, #1464]
	bl	_sinf
	str	s0, [x28, #1336]
	ldr	s0, [x28, #1468]
	bl	_sinf
	str	s0, [x28, #1340]
	ldr	s0, [x28, #1472]
	bl	_sinf
	str	s0, [x28, #1344]
	ldr	s0, [x28, #1476]
	bl	_sinf
	str	s0, [x28, #1348]
	ldr	s0, [x28, #1480]
	bl	_sinf
	str	s0, [x28, #1352]
	ldr	s0, [x28, #1484]
	bl	_sinf
	str	s0, [x28, #1356]
	ldr	s0, [x28, #1488]
	bl	_sinf
	str	s0, [x28, #1360]
	ldr	s0, [x28, #1492]
	bl	_sinf
	str	s0, [x28, #1364]
	ldr	s0, [x28, #1496]
	bl	_sinf
	str	s0, [x28, #1368]
	ldr	s0, [x28, #1500]
	bl	_sinf
	str	s0, [x28, #1372]
	ldr	s0, [x28, #1376]
	bl	_cosf
	str	s0, [x28, #1120]
	ldr	s0, [x28, #1380]
	bl	_cosf
	str	s0, [x28, #1124]
	ldr	s0, [x28, #1384]
	bl	_cosf
	str	s0, [x28, #1128]
	ldr	s0, [x28, #1388]
	bl	_cosf
	str	s0, [x28, #1132]
	ldr	s0, [x28, #1392]
	bl	_cosf
	str	s0, [x28, #1136]
	ldr	s0, [x28, #1396]
	bl	_cosf
	str	s0, [x28, #1140]
	ldr	s0, [x28, #1400]
	bl	_cosf
	str	s0, [x28, #1144]
	ldr	s0, [x28, #1404]
	bl	_cosf
	str	s0, [x28, #1148]
	ldr	s0, [x28, #1408]
	bl	_cosf
	str	s0, [x28, #1152]
	ldr	s0, [x28, #1412]
	bl	_cosf
	str	s0, [x28, #1156]
	ldr	s0, [x28, #1416]
	bl	_cosf
	str	s0, [x28, #1160]
	ldr	s0, [x28, #1420]
	bl	_cosf
	str	s0, [x28, #1164]
	ldr	s0, [x28, #1424]
	bl	_cosf
	str	s0, [x28, #1168]
	ldr	s0, [x28, #1428]
	bl	_cosf
	str	s0, [x28, #1172]
	ldr	s0, [x28, #1432]
	bl	_cosf
	str	s0, [x28, #1176]
	ldr	s0, [x28, #1436]
	bl	_cosf
	str	s0, [x28, #1180]
	ldr	s0, [x28, #1440]
	bl	_cosf
	str	s0, [x28, #1184]
	ldr	s0, [x28, #1444]
	bl	_cosf
	str	s0, [x28, #1188]
	ldr	s0, [x28, #1448]
	bl	_cosf
	str	s0, [x28, #1192]
	ldr	s0, [x28, #1452]
	bl	_cosf
	str	s0, [x28, #1196]
	ldr	s0, [x28, #1456]
	bl	_cosf
	str	s0, [x28, #1200]
	ldr	s0, [x28, #1460]
	bl	_cosf
	str	s0, [x28, #1204]
	ldr	s0, [x28, #1464]
	bl	_cosf
	str	s0, [x28, #1208]
	ldr	s0, [x28, #1468]
	bl	_cosf
	str	s0, [x28, #1212]
	ldr	s0, [x28, #1472]
	bl	_cosf
	str	s0, [x28, #1216]
	ldr	s0, [x28, #1476]
	bl	_cosf
	str	s0, [x28, #1220]
	ldr	s0, [x28, #1480]
	bl	_cosf
	str	s0, [x28, #1224]
	ldr	s0, [x28, #1484]
	bl	_cosf
	str	s0, [x28, #1228]
	ldr	s0, [x28, #1488]
	bl	_cosf
	str	s0, [x28, #1232]
	ldr	s0, [x28, #1492]
	bl	_cosf
	str	s0, [x28, #1236]
	ldr	s0, [x28, #1496]
	bl	_cosf
	str	s0, [x28, #1240]
	ldr	s0, [x28, #1500]
	bl	_cosf
	str	s0, [x28, #1244]
	ldur	q0, [x19, #124]
	str	q0, [sp, #20368]
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3984
	add	x0, x8, #16
Lloh281:
	adrp	x1, l_.memset_pattern.127@PAGE
Lloh282:
	add	x1, x1, l_.memset_pattern.127@PAGEOFF
	mov	w2, #128                        ; =0x80
	bl	_memset_pattern16
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3984
	ldur	q0, [x9, #128]
	stur	q0, [x19, #124]
	ldur	q0, [x19, #40]
	str	q0, [sp, #21184]
	ldr	s0, [x28, #1660]
	ldr	s1, [sp, #188]                  ; 4-byte Folded Reload
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1664]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1668]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1672]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1676]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1680]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1684]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1688]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1692]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1696]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1700]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1704]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1708]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1712]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1716]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1720]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1724]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1728]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1732]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1736]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1740]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1744]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1748]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1752]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1756]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1760]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1764]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1768]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1772]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1776]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1780]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1784]
	fmadd	s0, s0, s1, s10
	str	s0, [x28, #1788]
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #704
	ldur	q0, [x9, #128]
	stur	q0, [x19, #40]
	ldur	q0, [x19, #108]
	str	q0, [sp, #20512]
	ldur	q0, [x19, #140]
	str	q0, [sp, #20224]
	ldr	s0, [x28, #700]
	ldr	s1, [x28, #988]
	ldr	x10, [sp, #704]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #696]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #16]                  ; 8-byte Folded Reload
	add	x13, sp, #5, lsl #12            ; =20480
	add	x13, x13, #304
	add	x14, sp, #5, lsl #12            ; =20480
	add	x14, x14, #176
	mov	w15, #1                         ; =0x1
LBB17_8:                                ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	s2, [x13, x8]
	ldr	s3, [x14, x8]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	str	s4, [x10, x8]
	ldr	w9, [x12, x8]
	sub	w9, w15, w9
	scvtf	s5, w9
	fmadd	s0, s0, s3, s5
	fmsub	s0, s2, s1, s0
	str	s0, [x11, x8]
	add	x8, x8, #4
	fmov	s1, s4
	cmp	x8, #128
	b.ne	LBB17_8
; %bb.9:                                ;   in Loop: Header=BB17_7 Depth=1
	mov	x23, #0                         ; =0x0
	add	x8, sp, #5, lsl #12             ; =20480
	add	x8, x8, #32
	ldur	q0, [x8, #128]
	stur	q0, [x19, #108]
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3840
	ldur	q0, [x8, #128]
	stur	q0, [x19, #140]
	ldur	q0, [x19, #16]
	str	q0, [sp, #21328]
	ldr	s1, [x28, #1804]
	mov	w8, #48759                      ; =0xbe77
	movk	w8, #16255, lsl #16
	fmov	s0, w8
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1808]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1812]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1816]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1820]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1824]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1828]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1832]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1836]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1840]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1844]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1848]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1852]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1856]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1860]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1864]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1868]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1872]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1876]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1880]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1884]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1888]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1892]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1896]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1900]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1904]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1908]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1912]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1916]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1920]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1924]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1928]
	fmadd	s1, s1, s0, s9
	str	s1, [x28, #1932]
	add	x8, sp, #5, lsl #12             ; =20480
	add	x8, x8, #848
	ldur	q1, [x8, #128]
	stur	q1, [x19, #16]
	ldur	q1, [x19, #168]
	str	q1, [sp, #20080]
	ldr	s1, [x28, #556]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #560]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #564]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #568]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #572]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #576]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #580]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #584]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #588]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #592]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #596]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #600]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #604]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #608]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #612]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #616]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #620]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #624]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #628]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #632]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #636]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #640]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #644]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #648]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #652]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #656]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #660]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #664]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #668]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #672]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #676]
	fmadd	s1, s1, s0, s8
	str	s1, [x28, #680]
	fmadd	s0, s1, s0, s8
	str	s0, [x28, #684]
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3696
	ldur	q0, [x8, #128]
	stur	q0, [x19, #168]
	ldr	q0, [sp, #21200]
	ldr	q1, [sp, #21216]
	ldr	q2, [sp, #20528]
	ldr	q3, [sp, #20544]
	fmul.4s	v0, v0, v2
	fmul.4s	v1, v1, v3
	str	q0, [sp, #19952]
	str	q1, [sp, #19968]
	ldr	q0, [sp, #21232]
	ldr	q1, [sp, #21248]
	ldr	q2, [sp, #20560]
	ldr	q3, [sp, #20576]
	fmul.4s	v0, v0, v2
	fmul.4s	v1, v1, v3
	str	q0, [sp, #19984]
	str	q1, [sp, #20000]
	ldr	q0, [sp, #21264]
	ldr	q1, [sp, #21280]
	ldr	q2, [sp, #20592]
	ldr	q3, [sp, #20608]
	fmul.4s	v0, v0, v2
	fmul.4s	v1, v1, v3
	str	q0, [sp, #20016]
	str	q1, [sp, #20032]
	ldr	q0, [sp, #21296]
	ldr	q1, [sp, #21312]
	ldr	q2, [sp, #20624]
	ldr	q3, [sp, #20640]
	fmul.4s	v0, v0, v2
	fmul.4s	v1, v1, v3
	str	q0, [sp, #20048]
	str	q1, [sp, #20064]
	b	LBB17_11
LBB17_10:                               ;   in Loop: Header=BB17_11 Depth=2
	ldr	x8, [sp, #3344]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x23]
	fadd	s0, s0, s0
	bl	___exp10f
	fmadd	s0, s9, s0, s8
	fminnm	s0, s0, s11
	fmaxnm	s0, s0, s12
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3440
	str	s0, [x8, x23]
	add	x23, x23, #4
	cmp	x23, #128
	b.eq	LBB17_13
LBB17_11:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x8, [sp, #3352]                 ; 8-byte Folded Reload
	ldr	s8, [x8, x23]
	movi	d9, #0000000000000000
	ldr	w8, [sp, #3336]                 ; 4-byte Folded Reload
	cbnz	w8, LBB17_10
; %bb.12:                               ;   in Loop: Header=BB17_11 Depth=2
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3568
	ldr	s9, [x8, x23]
	b	LBB17_10
LBB17_13:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	ldr	q1, [sp, #19824]
	ldr	q2, [sp, #19840]
	fmul.4s	v3, v1, v1
	mov	w9, #43691                      ; =0xaaab
	movk	w9, #48810, lsl #16
	dup.4s	v0, w9
	ldr	q7, [sp, #320]                  ; 16-byte Folded Reload
	mov.16b	v4, v7
	fmla.4s	v4, v0, v3
	fmul.4s	v1, v1, v4
	ldp	q3, q4, [x19, #192]
	str	q3, [sp, #19680]
	str	q1, [sp, #19696]
	fmul.4s	v1, v2, v2
	mov.16b	v3, v7
	fmla.4s	v3, v0, v1
	fmul.4s	v1, v2, v3
	ldr	q2, [sp, #19856]
	ldr	q3, [sp, #19872]
	fmul.4s	v5, v2, v2
	mov.16b	v6, v7
	fmla.4s	v6, v0, v5
	fmul.4s	v2, v2, v6
	str	q1, [sp, #19712]
	str	q2, [sp, #19728]
	fmul.4s	v1, v3, v3
	mov.16b	v2, v7
	fmla.4s	v2, v0, v1
	fmul.4s	v1, v3, v2
	ldr	q2, [sp, #19888]
	ldr	q3, [sp, #19904]
	fmul.4s	v5, v2, v2
	mov.16b	v6, v7
	fmla.4s	v6, v0, v5
	fmul.4s	v2, v2, v6
	str	q1, [sp, #19744]
	str	q2, [sp, #19760]
	fmul.4s	v1, v3, v3
	mov.16b	v2, v7
	fmla.4s	v2, v0, v1
	fmul.4s	v1, v3, v2
	ldr	q2, [sp, #19920]
	ldr	q3, [sp, #19936]
	fmul.4s	v5, v2, v2
	mov.16b	v6, v7
	fmla.4s	v6, v0, v5
	fmul.4s	v2, v2, v6
	str	q1, [sp, #19776]
	str	q2, [sp, #19792]
	fmul.4s	v1, v3, v3
	mov.16b	v2, v7
	fmla.4s	v2, v0, v1
	fmul.4s	v0, v3, v2
	str	q0, [sp, #19808]
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3296
	ldur	q0, [x9, #128]
	str	q4, [sp, #19536]
	add	x9, sp, #3168
	ldr	s2, [x9, #16380]
	mov	w9, #47186                      ; =0xb852
	movk	w9, #16254, lsl #16
	fmov	s1, w9
	ldp	s4, s3, [x28, #156]
	fmadd	s2, s2, s1, s3
	fsub	s2, s2, s4
	ldp	s4, s5, [x28, #164]
	fmadd	s6, s2, s1, s4
	fsub	s3, s6, s3
	add	x9, sp, #3172
	str	s2, [x9, #16380]
	add	x9, sp, #3176
	str	s3, [x9, #16380]
	fmadd	s2, s3, s1, s5
	fsub	s2, s2, s4
	ldp	s3, s4, [x28, #172]
	fmadd	s6, s2, s1, s3
	fsub	s5, s6, s5
	add	x9, sp, #3180
	str	s2, [x9, #16380]
	add	x9, sp, #3184
	str	s5, [x9, #16380]
	fmadd	s2, s5, s1, s4
	fsub	s2, s2, s3
	ldp	s3, s5, [x28, #180]
	fmadd	s6, s2, s1, s3
	fsub	s4, s6, s4
	add	x9, sp, #3188
	str	s2, [x9, #16380]
	add	x9, sp, #3192
	str	s4, [x9, #16380]
	fmadd	s2, s4, s1, s5
	fsub	s2, s2, s3
	ldp	s3, s4, [x28, #188]
	fmadd	s6, s2, s1, s3
	fsub	s5, s6, s5
	add	x9, sp, #3196
	str	s2, [x9, #16380]
	add	x9, sp, #3200
	str	s5, [x9, #16380]
	fmadd	s2, s5, s1, s4
	fsub	s2, s2, s3
	ldp	s3, s5, [x28, #196]
	fmadd	s6, s2, s1, s3
	fsub	s4, s6, s4
	add	x9, sp, #3204
	str	s2, [x9, #16380]
	add	x9, sp, #3208
	str	s4, [x9, #16380]
	fmadd	s2, s4, s1, s5
	fsub	s2, s2, s3
	ldp	s3, s4, [x28, #204]
	fmadd	s6, s2, s1, s3
	fsub	s5, s6, s5
	add	x9, sp, #3212
	str	s2, [x9, #16380]
	add	x9, sp, #3216
	str	s5, [x9, #16380]
	fmadd	s2, s5, s1, s4
	fsub	s2, s2, s3
	ldp	s3, s5, [x28, #212]
	fmadd	s6, s2, s1, s3
	fsub	s4, s6, s4
	add	x9, sp, #3220
	str	s2, [x9, #16380]
	add	x9, sp, #3224
	str	s4, [x9, #16380]
	fmadd	s2, s4, s1, s5
	fsub	s2, s2, s3
	ldp	s3, s4, [x28, #220]
	fmadd	s6, s2, s1, s3
	fsub	s5, s6, s5
	add	x9, sp, #3228
	str	s2, [x9, #16380]
	add	x9, sp, #3232
	str	s5, [x9, #16380]
	fmadd	s2, s5, s1, s4
	fsub	s2, s2, s3
	ldp	s3, s5, [x28, #228]
	fmadd	s6, s2, s1, s3
	fsub	s4, s6, s4
	stp	s2, s4, [x28, #80]
	fmadd	s2, s4, s1, s5
	fsub	s2, s2, s3
	ldp	s3, s4, [x28, #236]
	fmadd	s6, s2, s1, s3
	fsub	s5, s6, s5
	stp	s2, s5, [x28, #88]
	fmadd	s2, s5, s1, s4
	fsub	s2, s2, s3
	ldp	s3, s5, [x28, #244]
	fmadd	s6, s2, s1, s3
	fsub	s4, s6, s4
	stp	s2, s4, [x28, #96]
	fmadd	s2, s4, s1, s5
	fsub	s2, s2, s3
	ldp	s3, s4, [x28, #252]
	fmadd	s6, s2, s1, s3
	fsub	s5, s6, s5
	stp	s2, s5, [x28, #104]
	fmadd	s2, s5, s1, s4
	fsub	s2, s2, s3
	ldr	s3, [x28, #260]
	fmadd	s5, s2, s1, s3
	fsub	s4, s5, s4
	stp	s2, s4, [x28, #112]
	ldr	s2, [x28, #264]
	fmadd	s4, s4, s1, s2
	fsub	s3, s4, s3
	ldr	s4, [x28, #268]
	fmadd	s5, s3, s1, s4
	fsub	s2, s5, s2
	stp	s3, s2, [x28, #120]
	ldr	s3, [x28, #272]
	fmadd	s2, s2, s1, s3
	fsub	s2, s2, s4
	ldr	s4, [x28, #276]
	fmadd	s5, s2, s1, s4
	fsub	s3, s5, s3
	stp	s2, s3, [x28, #128]
	ldr	s2, [x28, #280]
	fmadd	s3, s3, s1, s2
	fsub	s3, s3, s4
	ldr	s4, [x28, #284]
	fmadd	s1, s3, s1, s4
	fsub	s1, s1, s2
	stp	s3, s1, [x28, #136]
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3152
	ldur	q1, [x9, #128]
	stp	q0, q1, [x19, #192]
	ldr	q0, [sp, #19552]
	ldr	q1, [sp, #19568]
	ldr	q2, [sp, #19952]
	ldr	q3, [sp, #19968]
	ldr	q4, [sp, #160]                  ; 16-byte Folded Reload
	bif.16b	v0, v2, v4
	bif.16b	v1, v3, v4
	str	q0, [sp, #19408]
	str	q1, [sp, #19424]
	ldr	q0, [sp, #19584]
	ldr	q1, [sp, #19600]
	ldr	q2, [sp, #19984]
	ldr	q3, [sp, #20000]
	bif.16b	v0, v2, v4
	bif.16b	v1, v3, v4
	str	q0, [sp, #19440]
	str	q1, [sp, #19456]
	ldr	q0, [sp, #19616]
	ldr	q1, [sp, #19632]
	ldr	q2, [sp, #20016]
	ldr	q3, [sp, #20032]
	bif.16b	v0, v2, v4
	bif.16b	v1, v3, v4
	str	q0, [sp, #19472]
	str	q1, [sp, #19488]
	ldr	q0, [sp, #19648]
	ldr	q1, [sp, #19664]
	ldr	q2, [sp, #20048]
	ldr	q3, [sp, #20064]
	bif.16b	v0, v2, v4
	bif.16b	v1, v3, v4
	str	q0, [sp, #19504]
	str	q1, [sp, #19520]
	ldr	x10, [sp, #272]                 ; 8-byte Folded Reload
	ldr	q0, [x10]
	str	q0, [sp, #18688]
	ldr	s0, [x19, #392]
	ldr	s1, [x19, #396]
	ldr	s2, [x19, #400]
	add	x9, sp, #2316
	ldr	s3, [x9, #16380]
	add	x9, sp, #2320
	ldr	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3028
	ldr	s5, [x9, #16380]
	add	x9, sp, #3032
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2324
	str	s3, [x9, #16380]
	add	x9, sp, #2328
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3036
	ldr	s5, [x9, #16380]
	add	x9, sp, #3040
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2332
	str	s3, [x9, #16380]
	add	x9, sp, #2336
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3044
	ldr	s5, [x9, #16380]
	add	x9, sp, #3048
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2340
	str	s3, [x9, #16380]
	add	x9, sp, #2344
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3052
	ldr	s5, [x9, #16380]
	add	x9, sp, #3056
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2348
	str	s3, [x9, #16380]
	add	x9, sp, #2352
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3060
	ldr	s5, [x9, #16380]
	add	x9, sp, #3064
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2356
	str	s3, [x9, #16380]
	add	x9, sp, #2360
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3068
	ldr	s5, [x9, #16380]
	add	x9, sp, #3072
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2364
	str	s3, [x9, #16380]
	add	x9, sp, #2368
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3076
	ldr	s5, [x9, #16380]
	add	x9, sp, #3080
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2372
	str	s3, [x9, #16380]
	add	x9, sp, #2376
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3084
	ldr	s5, [x9, #16380]
	add	x9, sp, #3088
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2380
	str	s3, [x9, #16380]
	add	x9, sp, #2384
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3092
	ldr	s5, [x9, #16380]
	add	x9, sp, #3096
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2388
	str	s3, [x9, #16380]
	add	x9, sp, #2392
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3100
	ldr	s5, [x9, #16380]
	add	x9, sp, #3104
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2396
	str	s3, [x9, #16380]
	add	x9, sp, #2400
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3108
	ldr	s5, [x9, #16380]
	add	x9, sp, #3112
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2404
	str	s3, [x9, #16380]
	add	x9, sp, #2408
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3116
	ldr	s5, [x9, #16380]
	add	x9, sp, #3120
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2412
	str	s3, [x9, #16380]
	add	x9, sp, #2416
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3124
	ldr	s5, [x9, #16380]
	add	x9, sp, #3128
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2420
	str	s3, [x9, #16380]
	add	x9, sp, #2424
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3132
	ldr	s5, [x9, #16380]
	add	x9, sp, #3136
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2428
	str	s3, [x9, #16380]
	add	x9, sp, #2432
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3140
	ldr	s5, [x9, #16380]
	add	x9, sp, #3144
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #2436
	str	s3, [x9, #16380]
	add	x9, sp, #2440
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #3148
	ldr	s5, [x9, #16380]
	add	x9, sp, #3152
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	add	x9, sp, #2444
	str	s3, [x9, #16380]
	add	x9, sp, #2448
	str	s0, [x9, #16380]
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #2304
	ldur	q0, [x9, #128]
	str	q0, [x10]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #18544]
	ldr	s0, [x19, #392]
	ldr	s3, [x19, #424]
	ldr	s4, [x19, #428]
	ldr	s1, [x19, #432]
	ldr	s5, [x19, #436]
	ldr	s6, [x19, #440]
	fneg	s7, s1
	add	x9, sp, #2320
	ldr	s17, [x9, #16380]
	add	x9, sp, #2172
	ldr	s16, [x9, #16380]
	add	x9, sp, #2176
	ldr	s2, [x9, #16380]
	ldr	x9, [sp, #600]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x10, [sp, #456]                 ; 8-byte Folded Reload
LBB17_14:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x10, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_14
; %bb.15:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #2160
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	q0, [x19, #480]
	str	q0, [sp, #18400]
	ldr	s5, [x19, #460]
	ldr	s6, [x19, #464]
	ldr	s0, [x19, #468]
	ldr	s7, [x19, #472]
	ldr	s16, [x19, #476]
	fneg	s17, s0
	add	x9, sp, #2028
	ldr	s3, [x9, #16380]
	add	x9, sp, #2032
	ldr	s4, [x9, #16380]
	mov	x9, x10
	fmov	s19, s4
	fmov	s18, s3
	ldr	x12, [sp, #560]                 ; 8-byte Folded Reload
	ldr	x13, [sp, #552]                 ; 8-byte Folded Reload
	ldr	x15, [sp, #544]                 ; 8-byte Folded Reload
	ldr	x17, [sp, #536]                 ; 8-byte Folded Reload
	ldr	x1, [sp, #528]                  ; 8-byte Folded Reload
	ldr	x5, [sp, #808]                  ; 8-byte Folded Reload
	ldr	x6, [sp, #800]                  ; 8-byte Folded Reload
	ldr	x7, [sp, #792]                  ; 8-byte Folded Reload
	ldr	x30, [sp, #784]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #3328]                ; 8-byte Folded Reload
	ldr	x14, [sp, #3320]                ; 8-byte Folded Reload
	ldr	x16, [sp, #3312]                ; 8-byte Folded Reload
	ldr	x0, [sp, #3240]                 ; 8-byte Folded Reload
	ldr	x2, [sp, #3224]                 ; 8-byte Folded Reload
	ldr	x3, [sp, #3304]                 ; 8-byte Folded Reload
	ldr	x4, [sp, #3296]                 ; 8-byte Folded Reload
	ldr	x23, [sp, #664]                 ; 8-byte Folded Reload
	ldr	x21, [sp, #360]                 ; 8-byte Folded Reload
LBB17_16:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_16
; %bb.17:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #2016
	ldur	q1, [x9, #128]
	str	q1, [x19, #480]
	ldr	s1, [x19, #496]
	ldr	s2, [x19, #500]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #18416]
	ldr	q7, [sp, #18432]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #18272]
	str	q4, [sp, #18288]
	ldr	q3, [sp, #18448]
	ldr	q4, [sp, #18464]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #18304]
	str	q3, [sp, #18320]
	ldr	q3, [sp, #18480]
	ldr	q5, [sp, #18496]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #18336]
	str	q3, [sp, #18352]
	ldr	q3, [sp, #18512]
	ldr	q4, [sp, #18528]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #18368]
	str	q0, [sp, #18384]
	ldr	x21, [sp, #264]                 ; 8-byte Folded Reload
	ldr	q0, [x21]
	str	q0, [sp, #17552]
	ldr	s0, [x19, #656]
	ldr	s1, [x19, #660]
	ldr	s2, [x19, #664]
	add	x9, sp, #1180
	ldr	s3, [x9, #16380]
	add	x9, sp, #1184
	ldr	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1892
	ldr	s5, [x9, #16380]
	add	x9, sp, #1896
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1188
	str	s3, [x9, #16380]
	add	x9, sp, #1192
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1900
	ldr	s5, [x9, #16380]
	add	x9, sp, #1904
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1196
	str	s3, [x9, #16380]
	add	x9, sp, #1200
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1908
	ldr	s5, [x9, #16380]
	add	x9, sp, #1912
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1204
	str	s3, [x9, #16380]
	add	x9, sp, #1208
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1916
	ldr	s5, [x9, #16380]
	add	x9, sp, #1920
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1212
	str	s3, [x9, #16380]
	add	x9, sp, #1216
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1924
	ldr	s5, [x9, #16380]
	add	x9, sp, #1928
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1220
	str	s3, [x9, #16380]
	add	x9, sp, #1224
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1932
	ldr	s5, [x9, #16380]
	add	x9, sp, #1936
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1228
	str	s3, [x9, #16380]
	add	x9, sp, #1232
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1940
	ldr	s5, [x9, #16380]
	add	x9, sp, #1944
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1236
	str	s3, [x9, #16380]
	add	x9, sp, #1240
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1948
	ldr	s5, [x9, #16380]
	add	x9, sp, #1952
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1244
	str	s3, [x9, #16380]
	add	x9, sp, #1248
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1956
	ldr	s5, [x9, #16380]
	add	x9, sp, #1960
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1252
	str	s3, [x9, #16380]
	add	x9, sp, #1256
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1964
	ldr	s5, [x9, #16380]
	add	x9, sp, #1968
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1260
	str	s3, [x9, #16380]
	add	x9, sp, #1264
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1972
	ldr	s5, [x9, #16380]
	add	x9, sp, #1976
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1268
	str	s3, [x9, #16380]
	add	x9, sp, #1272
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1980
	ldr	s5, [x9, #16380]
	add	x9, sp, #1984
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1276
	str	s3, [x9, #16380]
	add	x9, sp, #1280
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1988
	ldr	s5, [x9, #16380]
	add	x9, sp, #1992
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1284
	str	s3, [x9, #16380]
	add	x9, sp, #1288
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #1996
	ldr	s5, [x9, #16380]
	add	x9, sp, #2000
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1292
	str	s3, [x9, #16380]
	add	x9, sp, #1296
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #2004
	ldr	s5, [x9, #16380]
	add	x9, sp, #2008
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #1300
	str	s3, [x9, #16380]
	add	x9, sp, #1304
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #2012
	ldr	s5, [x9, #16380]
	add	x9, sp, #2016
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	add	x9, sp, #1308
	str	s3, [x9, #16380]
	add	x9, sp, #1312
	str	s0, [x9, #16380]
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #1168
	ldur	q0, [x9, #128]
	str	q0, [x21]
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #17408]
	ldr	s0, [x19, #656]
	ldr	s3, [x19, #688]
	ldr	s4, [x19, #692]
	ldr	s1, [x19, #696]
	ldr	s5, [x19, #700]
	ldr	s6, [x19, #704]
	fneg	s7, s1
	add	x9, sp, #1184
	ldr	s17, [x9, #16380]
	add	x9, sp, #1036
	ldr	s16, [x9, #16380]
	add	x9, sp, #1040
	ldr	s2, [x9, #16380]
	ldr	x9, [sp, #672]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x21, [sp, #648]                 ; 8-byte Folded Reload
	ldr	x10, [sp, #632]                 ; 8-byte Folded Reload
LBB17_18:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x25, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_18
; %bb.19:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x9, x25
	mov	x25, x20
	mov	x8, #0                          ; =0x0
	add	x20, sp, #4, lsl #12            ; =16384
	add	x20, x20, #1024
	ldur	q0, [x20, #128]
	ldr	x20, [sp, #3152]                ; 8-byte Folded Reload
	str	q0, [x20]
	ldr	x20, [sp, #3144]                ; 8-byte Folded Reload
	ldr	q0, [x20]
	str	q0, [sp, #17264]
	ldr	s5, [x19, #724]
	ldr	s6, [x19, #728]
	ldr	s0, [x19, #732]
	ldr	s7, [x19, #736]
	ldr	s16, [x19, #740]
	fneg	s17, s0
	add	x20, sp, #892
	ldr	s3, [x20, #16380]
	add	x20, sp, #896
	ldr	s4, [x20, #16380]
	fmov	s19, s4
	fmov	s18, s3
	ldr	x20, [sp, #368]                 ; 8-byte Folded Reload
LBB17_20:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x20, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_20
; %bb.21:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #880
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #760]
	ldr	s2, [x19, #764]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #17280]
	ldr	q7, [sp, #17296]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #17136]
	str	q4, [sp, #17152]
	ldr	q3, [sp, #17312]
	ldr	q4, [sp, #17328]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #17168]
	str	q3, [sp, #17184]
	ldr	q3, [sp, #17344]
	ldr	q5, [sp, #17360]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #17200]
	str	q3, [sp, #17216]
	ldr	q3, [sp, #17376]
	ldr	q4, [sp, #17392]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #17232]
	str	q0, [sp, #17248]
	ldr	x20, [sp, #256]                 ; 8-byte Folded Reload
	ldr	q0, [x20]
	str	q0, [sp, #16416]
	ldr	s0, [x19, #920]
	ldr	s1, [x19, #924]
	ldr	s2, [x19, #928]
	add	x9, sp, #44
	ldr	s3, [x9, #16380]
	add	x9, sp, #48
	ldr	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #756
	ldr	s5, [x9, #16380]
	add	x9, sp, #760
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #52
	str	s3, [x9, #16380]
	add	x9, sp, #56
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #764
	ldr	s5, [x9, #16380]
	add	x9, sp, #768
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #60
	str	s3, [x9, #16380]
	add	x9, sp, #64
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #772
	ldr	s5, [x9, #16380]
	add	x9, sp, #776
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #68
	str	s3, [x9, #16380]
	add	x9, sp, #72
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #780
	ldr	s5, [x9, #16380]
	add	x9, sp, #784
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #76
	str	s3, [x9, #16380]
	add	x9, sp, #80
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #788
	ldr	s5, [x9, #16380]
	add	x9, sp, #792
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #84
	str	s3, [x9, #16380]
	add	x9, sp, #88
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #796
	ldr	s5, [x9, #16380]
	add	x9, sp, #800
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #92
	str	s3, [x9, #16380]
	add	x9, sp, #96
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #804
	ldr	s5, [x9, #16380]
	add	x9, sp, #808
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #100
	str	s3, [x9, #16380]
	add	x9, sp, #104
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #812
	ldr	s5, [x9, #16380]
	add	x9, sp, #816
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #108
	str	s3, [x9, #16380]
	add	x9, sp, #112
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #820
	ldr	s5, [x9, #16380]
	add	x9, sp, #824
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #116
	str	s3, [x9, #16380]
	add	x9, sp, #120
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #828
	ldr	s5, [x9, #16380]
	add	x9, sp, #832
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #124
	str	s3, [x9, #16380]
	add	x9, sp, #128
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #836
	ldr	s5, [x9, #16380]
	add	x9, sp, #840
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #132
	str	s3, [x9, #16380]
	add	x9, sp, #136
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #844
	ldr	s5, [x9, #16380]
	add	x9, sp, #848
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #140
	str	s3, [x9, #16380]
	add	x9, sp, #144
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #852
	ldr	s5, [x9, #16380]
	add	x9, sp, #856
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #148
	str	s3, [x9, #16380]
	add	x9, sp, #152
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #860
	ldr	s5, [x9, #16380]
	add	x9, sp, #864
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #156
	str	s3, [x9, #16380]
	add	x9, sp, #160
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #868
	ldr	s5, [x9, #16380]
	add	x9, sp, #872
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	add	x9, sp, #164
	str	s3, [x9, #16380]
	add	x9, sp, #168
	str	s4, [x9, #16380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	add	x9, sp, #876
	ldr	s5, [x9, #16380]
	add	x9, sp, #880
	ldr	s6, [x9, #16380]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	add	x9, sp, #172
	str	s3, [x9, #16380]
	add	x9, sp, #176
	str	s0, [x9, #16380]
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #32
	ldur	q0, [x9, #128]
	str	q0, [x20]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #16272]
	ldr	s0, [x19, #920]
	ldr	s3, [x19, #952]
	ldr	s4, [x19, #956]
	ldr	s1, [x19, #960]
	ldr	s5, [x19, #964]
	ldr	s6, [x19, #968]
	fneg	s7, s1
	add	x9, sp, #48
	ldr	s17, [x9, #16380]
	ldr	s16, [sp, #16280]
	ldr	s2, [sp, #16284]
	ldr	x9, [sp, #872]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x20, [sp, #608]                 ; 8-byte Folded Reload
LBB17_22:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x20, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_22
; %bb.23:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3984
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	q0, [x19, #1008]
	str	q0, [sp, #16128]
	ldr	s5, [x19, #988]
	ldr	s6, [x19, #992]
	ldr	s0, [x19, #996]
	ldr	s7, [x19, #1000]
	ldr	s16, [x19, #1004]
	fneg	s17, s0
	ldr	s3, [sp, #16136]
	ldr	s4, [sp, #16140]
	mov	x9, x20
	fmov	s19, s4
	fmov	s18, s3
	mov	x20, x25
LBB17_24:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x20, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_24
; %bb.25:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3840
	ldur	q1, [x9, #128]
	str	q1, [x19, #1008]
	ldr	s1, [x19, #1024]
	ldr	s2, [x19, #1028]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #16144]
	ldr	q7, [sp, #16160]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #16000]
	str	q4, [sp, #16016]
	ldr	q3, [sp, #16176]
	ldr	q4, [sp, #16192]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #16032]
	str	q3, [sp, #16048]
	ldr	q3, [sp, #16208]
	ldr	q5, [sp, #16224]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #16064]
	str	q3, [sp, #16080]
	ldr	q3, [sp, #16240]
	ldr	q4, [sp, #16256]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #16096]
	str	q0, [sp, #16112]
	ldr	x25, [sp, #248]                 ; 8-byte Folded Reload
	ldr	q0, [x25]
	str	q0, [sp, #15280]
	ldr	s0, [x19, #1184]
	ldr	s1, [x19, #1188]
	ldr	s2, [x19, #1192]
	ldr	s3, [sp, #15288]
	ldr	s4, [sp, #15292]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16000]
	ldr	s6, [sp, #16004]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15296]
	str	s4, [sp, #15300]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16008]
	ldr	s6, [sp, #16012]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15304]
	str	s4, [sp, #15308]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16016]
	ldr	s6, [sp, #16020]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15312]
	str	s4, [sp, #15316]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16024]
	ldr	s6, [sp, #16028]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15320]
	str	s4, [sp, #15324]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16032]
	ldr	s6, [sp, #16036]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15328]
	str	s4, [sp, #15332]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16040]
	ldr	s6, [sp, #16044]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15336]
	str	s4, [sp, #15340]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16048]
	ldr	s6, [sp, #16052]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15344]
	str	s4, [sp, #15348]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16056]
	ldr	s6, [sp, #16060]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15352]
	str	s4, [sp, #15356]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16064]
	ldr	s6, [sp, #16068]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15360]
	str	s4, [sp, #15364]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16072]
	ldr	s6, [sp, #16076]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15368]
	str	s4, [sp, #15372]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16080]
	ldr	s6, [sp, #16084]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15376]
	str	s4, [sp, #15380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16088]
	ldr	s6, [sp, #16092]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15384]
	str	s4, [sp, #15388]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16096]
	ldr	s6, [sp, #16100]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15392]
	str	s4, [sp, #15396]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16104]
	ldr	s6, [sp, #16108]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15400]
	str	s4, [sp, #15404]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16112]
	ldr	s6, [sp, #16116]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #15408]
	str	s4, [sp, #15412]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #16120]
	ldr	s6, [sp, #16124]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #15416]
	str	s0, [sp, #15420]
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2992
	ldur	q0, [x9, #128]
	str	q0, [x25]
	ldr	x9, [sp, #3128]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #15136]
	ldr	s0, [x19, #1184]
	ldr	s3, [x19, #1216]
	ldr	s4, [x19, #1220]
	ldr	s1, [x19, #1224]
	ldr	s5, [x19, #1228]
	ldr	s6, [x19, #1232]
	fneg	s7, s1
	ldr	s17, [sp, #15292]
	ldr	s16, [sp, #15144]
	ldr	s2, [sp, #15148]
	ldr	x9, [sp, #680]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x26, [sp, #616]                 ; 8-byte Folded Reload
LBB17_26:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x26, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_26
; %bb.27:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2848
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3128]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #3120]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #14992]
	ldr	s5, [x19, #1252]
	ldr	s6, [x19, #1256]
	ldr	s0, [x19, #1260]
	ldr	s7, [x19, #1264]
	ldr	s16, [x19, #1268]
	fneg	s17, s0
	ldr	s3, [sp, #15000]
	ldr	s4, [sp, #15004]
	mov	x9, x26
	fmov	s19, s4
	fmov	s18, s3
	ldr	x26, [sp, #376]                 ; 8-byte Folded Reload
LBB17_28:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x26, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_28
; %bb.29:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2704
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3120]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #1288]
	ldr	s2, [x19, #1292]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #15008]
	ldr	q7, [sp, #15024]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #14864]
	str	q4, [sp, #14880]
	ldr	q3, [sp, #15040]
	ldr	q4, [sp, #15056]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #14896]
	str	q3, [sp, #14912]
	ldr	q3, [sp, #15072]
	ldr	q5, [sp, #15088]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #14928]
	str	q3, [sp, #14944]
	ldr	q3, [sp, #15104]
	ldr	q4, [sp, #15120]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #14960]
	str	q0, [sp, #14976]
	ldr	x26, [sp, #240]                 ; 8-byte Folded Reload
	ldr	q0, [x26]
	str	q0, [sp, #14144]
	ldr	s0, [x19, #1448]
	ldr	s1, [x19, #1452]
	ldr	s2, [x19, #1456]
	ldr	s3, [sp, #14152]
	ldr	s4, [sp, #14156]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14864]
	ldr	s6, [sp, #14868]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14160]
	str	s4, [sp, #14164]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14872]
	ldr	s6, [sp, #14876]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14168]
	str	s4, [sp, #14172]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14880]
	ldr	s6, [sp, #14884]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14176]
	str	s4, [sp, #14180]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14888]
	ldr	s6, [sp, #14892]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14184]
	str	s4, [sp, #14188]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14896]
	ldr	s6, [sp, #14900]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14192]
	str	s4, [sp, #14196]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14904]
	ldr	s6, [sp, #14908]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14200]
	str	s4, [sp, #14204]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14912]
	ldr	s6, [sp, #14916]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14208]
	str	s4, [sp, #14212]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14920]
	ldr	s6, [sp, #14924]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14216]
	str	s4, [sp, #14220]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14928]
	ldr	s6, [sp, #14932]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14224]
	str	s4, [sp, #14228]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14936]
	ldr	s6, [sp, #14940]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14232]
	str	s4, [sp, #14236]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14944]
	ldr	s6, [sp, #14948]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14240]
	str	s4, [sp, #14244]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14952]
	ldr	s6, [sp, #14956]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14248]
	str	s4, [sp, #14252]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14960]
	ldr	s6, [sp, #14964]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14256]
	str	s4, [sp, #14260]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14968]
	ldr	s6, [sp, #14972]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14264]
	str	s4, [sp, #14268]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14976]
	ldr	s6, [sp, #14980]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #14272]
	str	s4, [sp, #14276]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #14984]
	ldr	s6, [sp, #14988]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #14280]
	str	s0, [sp, #14284]
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1856
	ldur	q0, [x9, #128]
	str	q0, [x26]
	ldr	x9, [sp, #3112]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #14000]
	ldr	s0, [x19, #1448]
	ldr	s3, [x19, #1480]
	ldr	s4, [x19, #1484]
	ldr	s1, [x19, #1488]
	ldr	s5, [x19, #1492]
	ldr	s6, [x19, #1496]
	fneg	s7, s1
	ldr	s17, [sp, #14156]
	ldr	s16, [sp, #14008]
	ldr	s2, [sp, #14012]
	ldr	x9, [sp, #592]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x26, [sp, #624]                 ; 8-byte Folded Reload
LBB17_30:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x26, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_30
; %bb.31:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1712
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3112]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #3104]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #13856]
	ldr	s5, [x19, #1516]
	ldr	s6, [x19, #1520]
	ldr	s0, [x19, #1524]
	ldr	s7, [x19, #1528]
	ldr	s16, [x19, #1532]
	fneg	s17, s0
	ldr	s3, [sp, #13864]
	ldr	s4, [sp, #13868]
	mov	x9, x26
	fmov	s19, s4
	fmov	s18, s3
	ldr	x26, [sp, #384]                 ; 8-byte Folded Reload
LBB17_32:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x26, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_32
; %bb.33:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1568
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3104]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #1552]
	ldr	s2, [x19, #1556]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #13872]
	ldr	q7, [sp, #13888]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #13728]
	str	q4, [sp, #13744]
	ldr	q3, [sp, #13904]
	ldr	q4, [sp, #13920]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #13760]
	str	q3, [sp, #13776]
	ldr	q3, [sp, #13936]
	ldr	q5, [sp, #13952]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #13792]
	str	q3, [sp, #13808]
	ldr	q3, [sp, #13968]
	ldr	q4, [sp, #13984]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #13824]
	str	q0, [sp, #13840]
	ldr	x26, [sp, #232]                 ; 8-byte Folded Reload
	ldr	q0, [x26]
	str	q0, [sp, #13008]
	ldr	s0, [x19, #1712]
	ldr	s1, [x19, #1716]
	ldr	s2, [x19, #1720]
	ldr	s3, [sp, #13016]
	ldr	s4, [sp, #13020]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13728]
	ldr	s6, [sp, #13732]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13024]
	str	s4, [sp, #13028]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13736]
	ldr	s6, [sp, #13740]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13032]
	str	s4, [sp, #13036]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13744]
	ldr	s6, [sp, #13748]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13040]
	str	s4, [sp, #13044]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13752]
	ldr	s6, [sp, #13756]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13048]
	str	s4, [sp, #13052]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13760]
	ldr	s6, [sp, #13764]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13056]
	str	s4, [sp, #13060]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13768]
	ldr	s6, [sp, #13772]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13064]
	str	s4, [sp, #13068]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13776]
	ldr	s6, [sp, #13780]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13072]
	str	s4, [sp, #13076]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13784]
	ldr	s6, [sp, #13788]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13080]
	str	s4, [sp, #13084]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13792]
	ldr	s6, [sp, #13796]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13088]
	str	s4, [sp, #13092]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13800]
	ldr	s6, [sp, #13804]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13096]
	str	s4, [sp, #13100]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13808]
	ldr	s6, [sp, #13812]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13104]
	str	s4, [sp, #13108]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13816]
	ldr	s6, [sp, #13820]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13112]
	str	s4, [sp, #13116]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13824]
	ldr	s6, [sp, #13828]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13120]
	str	s4, [sp, #13124]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13832]
	ldr	s6, [sp, #13836]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13128]
	str	s4, [sp, #13132]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13840]
	ldr	s6, [sp, #13844]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #13136]
	str	s4, [sp, #13140]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #13848]
	ldr	s6, [sp, #13852]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #13144]
	str	s0, [sp, #13148]
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #720
	ldur	q0, [x9, #128]
	str	q0, [x26]
	ldr	x9, [sp, #3096]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #12864]
	ldr	s0, [x19, #1712]
	ldr	s3, [x19, #1744]
	ldr	s4, [x19, #1748]
	ldr	s1, [x19, #1752]
	ldr	s5, [x19, #1756]
	ldr	s6, [x19, #1760]
	fneg	s7, s1
	ldr	s17, [sp, #13020]
	ldr	s16, [sp, #12872]
	ldr	s2, [sp, #12876]
	ldr	x9, [sp, #688]                  ; 8-byte Folded Reload
	fmov	s18, s2
LBB17_34:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x10, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_34
; %bb.35:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #576
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3096]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #3088]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #12720]
	ldr	s5, [x19, #1780]
	ldr	s6, [x19, #1784]
	ldr	s0, [x19, #1788]
	ldr	s7, [x19, #1792]
	ldr	s16, [x19, #1796]
	fneg	s17, s0
	ldr	s3, [sp, #12728]
	ldr	s4, [sp, #12732]
	mov	x9, x10
	fmov	s19, s4
	fmov	s18, s3
	ldr	x27, [sp, #392]                 ; 8-byte Folded Reload
LBB17_36:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x27, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_36
; %bb.37:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #432
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3088]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #1816]
	ldr	s2, [x19, #1820]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #12736]
	ldr	q7, [sp, #12752]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #12592]
	str	q4, [sp, #12608]
	ldr	q3, [sp, #12768]
	ldr	q4, [sp, #12784]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #12624]
	str	q3, [sp, #12640]
	ldr	q3, [sp, #12800]
	ldr	q5, [sp, #12816]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #12656]
	str	q3, [sp, #12672]
	ldr	q3, [sp, #12832]
	ldr	q4, [sp, #12848]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #12688]
	str	q0, [sp, #12704]
	ldr	x26, [sp, #224]                 ; 8-byte Folded Reload
	ldr	q0, [x26]
	str	q0, [sp, #11872]
	ldr	s0, [x19, #1976]
	ldr	s1, [x19, #1980]
	ldr	s2, [x19, #1984]
	ldr	s3, [sp, #11880]
	ldr	s4, [sp, #11884]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12592]
	ldr	s6, [sp, #12596]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11888]
	str	s4, [sp, #11892]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12600]
	ldr	s6, [sp, #12604]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11896]
	str	s4, [sp, #11900]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12608]
	ldr	s6, [sp, #12612]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11904]
	str	s4, [sp, #11908]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12616]
	ldr	s6, [sp, #12620]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11912]
	str	s4, [sp, #11916]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12624]
	ldr	s6, [sp, #12628]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11920]
	str	s4, [sp, #11924]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12632]
	ldr	s6, [sp, #12636]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11928]
	str	s4, [sp, #11932]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12640]
	ldr	s6, [sp, #12644]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11936]
	str	s4, [sp, #11940]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12648]
	ldr	s6, [sp, #12652]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11944]
	str	s4, [sp, #11948]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12656]
	ldr	s6, [sp, #12660]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11952]
	str	s4, [sp, #11956]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12664]
	ldr	s6, [sp, #12668]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11960]
	str	s4, [sp, #11964]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12672]
	ldr	s6, [sp, #12676]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11968]
	str	s4, [sp, #11972]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12680]
	ldr	s6, [sp, #12684]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11976]
	str	s4, [sp, #11980]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12688]
	ldr	s6, [sp, #12692]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11984]
	str	s4, [sp, #11988]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12696]
	ldr	s6, [sp, #12700]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #11992]
	str	s4, [sp, #11996]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12704]
	ldr	s6, [sp, #12708]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #12000]
	str	s4, [sp, #12004]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #12712]
	ldr	s6, [sp, #12716]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #12008]
	str	s0, [sp, #12012]
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3680
	ldur	q0, [x9, #128]
	str	q0, [x26]
	ldr	x9, [sp, #3080]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #11728]
	ldr	s0, [x19, #1976]
	ldr	s3, [x19, #2008]
	ldr	s4, [x19, #2012]
	ldr	s1, [x19, #2016]
	ldr	s5, [x19, #2020]
	ldr	s6, [x19, #2024]
	fneg	s7, s1
	ldr	s17, [sp, #11884]
	ldr	s16, [sp, #11736]
	ldr	s2, [sp, #11740]
	ldr	x9, [sp, #824]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x10, [sp, #640]                 ; 8-byte Folded Reload
LBB17_38:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x10, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_38
; %bb.39:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x9, x10
	mov	x8, #0                          ; =0x0
	add	x26, sp, #2, lsl #12            ; =8192
	add	x26, x26, #3536
	ldur	q0, [x26, #128]
	ldr	x26, [sp, #3080]                ; 8-byte Folded Reload
	str	q0, [x26]
	ldr	x26, [sp, #3072]                ; 8-byte Folded Reload
	ldr	q0, [x26]
	str	q0, [sp, #11584]
	ldr	s5, [x19, #2044]
	ldr	s6, [x19, #2048]
	ldr	s0, [x19, #2052]
	ldr	s7, [x19, #2056]
	ldr	s16, [x19, #2060]
	fneg	s17, s0
	ldr	s3, [sp, #11592]
	ldr	s4, [sp, #11596]
	fmov	s19, s4
	fmov	s18, s3
	ldp	x26, x24, [sp, #400]            ; 16-byte Folded Reload
LBB17_40:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x26, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_40
; %bb.41:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3392
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3072]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #2080]
	ldr	s2, [x19, #2084]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #11600]
	ldr	q7, [sp, #11616]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #11456]
	str	q4, [sp, #11472]
	ldr	q3, [sp, #11632]
	ldr	q4, [sp, #11648]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #11488]
	str	q3, [sp, #11504]
	ldr	q3, [sp, #11664]
	ldr	q5, [sp, #11680]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #11520]
	str	q3, [sp, #11536]
	ldr	q3, [sp, #11696]
	ldr	q4, [sp, #11712]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #11552]
	str	q0, [sp, #11568]
	ldr	x26, [sp, #216]                 ; 8-byte Folded Reload
	ldr	q0, [x26]
	str	q0, [sp, #10736]
	ldr	s0, [x19, #2240]
	ldr	s1, [x19, #2244]
	ldr	s2, [x19, #2248]
	ldr	s3, [sp, #10744]
	ldr	s4, [sp, #10748]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11456]
	ldr	s6, [sp, #11460]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10752]
	str	s4, [sp, #10756]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11464]
	ldr	s6, [sp, #11468]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10760]
	str	s4, [sp, #10764]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11472]
	ldr	s6, [sp, #11476]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10768]
	str	s4, [sp, #10772]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11480]
	ldr	s6, [sp, #11484]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10776]
	str	s4, [sp, #10780]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11488]
	ldr	s6, [sp, #11492]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10784]
	str	s4, [sp, #10788]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11496]
	ldr	s6, [sp, #11500]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10792]
	str	s4, [sp, #10796]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11504]
	ldr	s6, [sp, #11508]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10800]
	str	s4, [sp, #10804]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11512]
	ldr	s6, [sp, #11516]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10808]
	str	s4, [sp, #10812]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11520]
	ldr	s6, [sp, #11524]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10816]
	str	s4, [sp, #10820]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11528]
	ldr	s6, [sp, #11532]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10824]
	str	s4, [sp, #10828]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11536]
	ldr	s6, [sp, #11540]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10832]
	str	s4, [sp, #10836]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11544]
	ldr	s6, [sp, #11548]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10840]
	str	s4, [sp, #10844]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11552]
	ldr	s6, [sp, #11556]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10848]
	str	s4, [sp, #10852]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11560]
	ldr	s6, [sp, #11564]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10856]
	str	s4, [sp, #10860]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11568]
	ldr	s6, [sp, #11572]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #10864]
	str	s4, [sp, #10868]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #11576]
	ldr	s6, [sp, #11580]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #10872]
	str	s0, [sp, #10876]
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2544
	ldur	q0, [x9, #128]
	str	q0, [x26]
	ldr	x9, [sp, #3064]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #10592]
	ldr	s0, [x19, #2240]
	ldr	s3, [x19, #2272]
	ldr	s4, [x19, #2276]
	ldr	s1, [x19, #2280]
	ldr	s5, [x19, #2284]
	ldr	s6, [x19, #2288]
	fneg	s7, s1
	ldr	s17, [sp, #10748]
	ldr	s16, [sp, #10600]
	ldr	s2, [sp, #10604]
	ldr	x9, [sp, #832]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x26, [sp, #464]                 ; 8-byte Folded Reload
	ldr	x10, [sp, #656]                 ; 8-byte Folded Reload
LBB17_42:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x26, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_42
; %bb.43:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2400
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3064]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #3056]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #10448]
	ldr	s5, [x19, #2308]
	ldr	s6, [x19, #2312]
	ldr	s0, [x19, #2316]
	ldr	s7, [x19, #2320]
	ldr	s16, [x19, #2324]
	fneg	s17, s0
	ldr	s3, [sp, #10456]
	ldr	s4, [sp, #10460]
	fmov	s19, s4
	fmov	s18, s3
LBB17_44:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x26]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x26, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x24, x8]
	add	x26, x26, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_44
; %bb.45:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2256
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3056]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #2344]
	ldr	s2, [x19, #2348]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #10464]
	ldr	q7, [sp, #10480]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #10320]
	str	q4, [sp, #10336]
	ldr	q3, [sp, #10496]
	ldr	q4, [sp, #10512]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #10352]
	str	q3, [sp, #10368]
	ldr	q3, [sp, #10528]
	ldr	q5, [sp, #10544]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #10384]
	str	q3, [sp, #10400]
	ldr	q3, [sp, #10560]
	ldr	q4, [sp, #10576]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #10416]
	str	q0, [sp, #10432]
	ldr	x24, [sp, #208]                 ; 8-byte Folded Reload
	ldr	q0, [x24]
	str	q0, [sp, #9600]
	ldr	s0, [x19, #2504]
	ldr	s1, [x19, #2508]
	ldr	s2, [x19, #2512]
	ldr	s3, [sp, #9608]
	ldr	s4, [sp, #9612]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10320]
	ldr	s6, [sp, #10324]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9616]
	str	s4, [sp, #9620]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10328]
	ldr	s6, [sp, #10332]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9624]
	str	s4, [sp, #9628]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10336]
	ldr	s6, [sp, #10340]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9632]
	str	s4, [sp, #9636]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10344]
	ldr	s6, [sp, #10348]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9640]
	str	s4, [sp, #9644]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10352]
	ldr	s6, [sp, #10356]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9648]
	str	s4, [sp, #9652]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10360]
	ldr	s6, [sp, #10364]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9656]
	str	s4, [sp, #9660]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10368]
	ldr	s6, [sp, #10372]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9664]
	str	s4, [sp, #9668]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10376]
	ldr	s6, [sp, #10380]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9672]
	str	s4, [sp, #9676]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10384]
	ldr	s6, [sp, #10388]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9680]
	str	s4, [sp, #9684]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10392]
	ldr	s6, [sp, #10396]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9688]
	str	s4, [sp, #9692]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10400]
	ldr	s6, [sp, #10404]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9696]
	str	s4, [sp, #9700]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10408]
	ldr	s6, [sp, #10412]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9704]
	str	s4, [sp, #9708]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10416]
	ldr	s6, [sp, #10420]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9712]
	str	s4, [sp, #9716]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10424]
	ldr	s6, [sp, #10428]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9720]
	str	s4, [sp, #9724]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10432]
	ldr	s6, [sp, #10436]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #9728]
	str	s4, [sp, #9732]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #10440]
	ldr	s6, [sp, #10444]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #9736]
	str	s0, [sp, #9740]
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1408
	ldur	q0, [x9, #128]
	str	q0, [x24]
	ldr	x9, [sp, #3048]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #9456]
	ldr	s0, [x19, #2504]
	ldr	s3, [x19, #2536]
	ldr	s4, [x19, #2540]
	ldr	s1, [x19, #2544]
	ldr	s5, [x19, #2548]
	ldr	s6, [x19, #2552]
	fneg	s7, s1
	ldr	s17, [sp, #9612]
	ldr	s16, [sp, #9464]
	ldr	s2, [sp, #9468]
	ldr	x9, [sp, #840]                  ; 8-byte Folded Reload
	fmov	s18, s2
LBB17_46:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_46
; %bb.47:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1264
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3048]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #3040]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #9312]
	ldr	s5, [x19, #2572]
	ldr	s6, [x19, #2576]
	ldr	s0, [x19, #2580]
	ldr	s7, [x19, #2584]
	ldr	s16, [x19, #2588]
	fneg	s17, s0
	ldr	s3, [sp, #9320]
	ldr	s4, [sp, #9324]
	mov	x9, x21
	fmov	s19, s4
	fmov	s18, s3
	ldr	x21, [sp, #416]                 ; 8-byte Folded Reload
LBB17_48:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_48
; %bb.49:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1120
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3040]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #2608]
	ldr	s2, [x19, #2612]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #9328]
	ldr	q7, [sp, #9344]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #9184]
	str	q4, [sp, #9200]
	ldr	q3, [sp, #9360]
	ldr	q4, [sp, #9376]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #9216]
	str	q3, [sp, #9232]
	ldr	q3, [sp, #9392]
	ldr	q5, [sp, #9408]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #9248]
	str	q3, [sp, #9264]
	ldr	q3, [sp, #9424]
	ldr	q4, [sp, #9440]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #9280]
	str	q0, [sp, #9296]
	ldr	x21, [sp, #200]                 ; 8-byte Folded Reload
	ldr	q0, [x21]
	str	q0, [sp, #8464]
	ldr	s0, [x19, #2768]
	ldr	s1, [x19, #2772]
	ldr	s2, [x19, #2776]
	ldr	s3, [sp, #8472]
	ldr	s4, [sp, #8476]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9184]
	ldr	s6, [sp, #9188]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8480]
	str	s4, [sp, #8484]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9192]
	ldr	s6, [sp, #9196]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8488]
	str	s4, [sp, #8492]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9200]
	ldr	s6, [sp, #9204]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8496]
	str	s4, [sp, #8500]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9208]
	ldr	s6, [sp, #9212]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8504]
	str	s4, [sp, #8508]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9216]
	ldr	s6, [sp, #9220]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8512]
	str	s4, [sp, #8516]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9224]
	ldr	s6, [sp, #9228]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8520]
	str	s4, [sp, #8524]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9232]
	ldr	s6, [sp, #9236]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8528]
	str	s4, [sp, #8532]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9240]
	ldr	s6, [sp, #9244]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8536]
	str	s4, [sp, #8540]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9248]
	ldr	s6, [sp, #9252]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8544]
	str	s4, [sp, #8548]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9256]
	ldr	s6, [sp, #9260]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8552]
	str	s4, [sp, #8556]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9264]
	ldr	s6, [sp, #9268]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8560]
	str	s4, [sp, #8564]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9272]
	ldr	s6, [sp, #9276]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8568]
	str	s4, [sp, #8572]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9280]
	ldr	s6, [sp, #9284]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8576]
	str	s4, [sp, #8580]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9288]
	ldr	s6, [sp, #9292]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8584]
	str	s4, [sp, #8588]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9296]
	ldr	s6, [sp, #9300]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #8592]
	str	s4, [sp, #8596]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #9304]
	ldr	s6, [sp, #9308]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #8600]
	str	s0, [sp, #8604]
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #272
	ldur	q0, [x9, #128]
	str	q0, [x21]
	ldr	x9, [sp, #3032]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #8320]
	ldr	s0, [x19, #2768]
	ldr	s3, [x19, #2800]
	ldr	s4, [x19, #2804]
	ldr	s1, [x19, #2808]
	ldr	s5, [x19, #2812]
	ldr	s6, [x19, #2816]
	fneg	s7, s1
	ldr	s17, [sp, #8476]
	ldr	s16, [sp, #8328]
	ldr	s2, [sp, #8332]
	ldr	x9, [sp, #848]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x21, [sp, #472]                 ; 8-byte Folded Reload
LBB17_50:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_50
; %bb.51:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #128
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3032]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #3024]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #8176]
	ldr	s5, [x19, #2836]
	ldr	s6, [x19, #2840]
	ldr	s0, [x19, #2844]
	ldr	s7, [x19, #2848]
	ldr	s16, [x19, #2852]
	fneg	s17, s0
	ldr	s3, [sp, #8184]
	ldr	s4, [sp, #8188]
	mov	x9, x21
	fmov	s19, s4
	fmov	s18, s3
	ldr	x21, [sp, #424]                 ; 8-byte Folded Reload
LBB17_52:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_52
; %bb.53:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #4080
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3024]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #2872]
	ldr	s2, [x19, #2876]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #8192]
	ldr	q7, [sp, #8208]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #8048]
	str	q4, [sp, #8064]
	ldr	q3, [sp, #8224]
	ldr	q4, [sp, #8240]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #8080]
	str	q3, [sp, #8096]
	ldr	q3, [sp, #8256]
	ldr	q5, [sp, #8272]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #8112]
	str	q3, [sp, #8128]
	ldr	q3, [sp, #8288]
	ldr	q4, [sp, #8304]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #8144]
	str	q0, [sp, #8160]
	ldr	x21, [sp, #192]                 ; 8-byte Folded Reload
	ldr	q0, [x21]
	str	q0, [sp, #7328]
	ldr	s0, [x19, #3032]
	ldr	s1, [x19, #3036]
	ldr	s2, [x19, #3040]
	ldr	s3, [sp, #7336]
	ldr	s4, [sp, #7340]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8048]
	ldr	s6, [sp, #8052]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7344]
	str	s4, [sp, #7348]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8056]
	ldr	s6, [sp, #8060]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7352]
	str	s4, [sp, #7356]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8064]
	ldr	s6, [sp, #8068]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7360]
	str	s4, [sp, #7364]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8072]
	ldr	s6, [sp, #8076]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7368]
	str	s4, [sp, #7372]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8080]
	ldr	s6, [sp, #8084]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7376]
	str	s4, [sp, #7380]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8088]
	ldr	s6, [sp, #8092]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7384]
	str	s4, [sp, #7388]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8096]
	ldr	s6, [sp, #8100]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7392]
	str	s4, [sp, #7396]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8104]
	ldr	s6, [sp, #8108]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7400]
	str	s4, [sp, #7404]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8112]
	ldr	s6, [sp, #8116]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7408]
	str	s4, [sp, #7412]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8120]
	ldr	s6, [sp, #8124]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7416]
	str	s4, [sp, #7420]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8128]
	ldr	s6, [sp, #8132]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7424]
	str	s4, [sp, #7428]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8136]
	ldr	s6, [sp, #8140]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7432]
	str	s4, [sp, #7436]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8144]
	ldr	s6, [sp, #8148]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7440]
	str	s4, [sp, #7444]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8152]
	ldr	s6, [sp, #8156]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7448]
	str	s4, [sp, #7452]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8160]
	ldr	s6, [sp, #8164]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #7456]
	str	s4, [sp, #7460]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #8168]
	ldr	s6, [sp, #8172]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #7464]
	str	s0, [sp, #7468]
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3232
	ldur	q0, [x9, #128]
	str	q0, [x21]
	ldr	x9, [sp, #3016]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #7184]
	ldr	s0, [x19, #3032]
	ldr	s3, [x19, #3064]
	ldr	s4, [x19, #3068]
	ldr	s1, [x19, #3072]
	ldr	s5, [x19, #3076]
	ldr	s6, [x19, #3080]
	fneg	s7, s1
	ldr	s17, [sp, #7340]
	ldr	s16, [sp, #7192]
	ldr	s2, [sp, #7196]
	ldr	x9, [sp, #856]                  ; 8-byte Folded Reload
	fmov	s18, s2
LBB17_54:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x10, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_54
; %bb.55:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x9, x10
	mov	x8, #0                          ; =0x0
	add	x21, sp, #1, lsl #12            ; =4096
	add	x21, x21, #3088
	ldur	q0, [x21, #128]
	ldr	x21, [sp, #3016]                ; 8-byte Folded Reload
	str	q0, [x21]
	ldr	x21, [sp, #3008]                ; 8-byte Folded Reload
	ldr	q0, [x21]
	str	q0, [sp, #7040]
	ldr	s5, [x19, #3100]
	ldr	s6, [x19, #3104]
	ldr	s0, [x19, #3108]
	ldr	s7, [x19, #3112]
	ldr	s16, [x19, #3116]
	fneg	s17, s0
	ldr	s3, [sp, #7048]
	ldr	s4, [sp, #7052]
	fmov	s19, s4
	fmov	s18, s3
	ldr	x21, [sp, #432]                 ; 8-byte Folded Reload
LBB17_56:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_56
; %bb.57:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2944
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #3008]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #3136]
	ldr	s2, [x19, #3140]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #7056]
	ldr	q7, [sp, #7072]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #6912]
	str	q4, [sp, #6928]
	ldr	q3, [sp, #7088]
	ldr	q4, [sp, #7104]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #6944]
	str	q3, [sp, #6960]
	ldr	q3, [sp, #7120]
	ldr	q5, [sp, #7136]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #6976]
	str	q3, [sp, #6992]
	ldr	q3, [sp, #7152]
	ldr	q4, [sp, #7168]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #7008]
	str	q0, [sp, #7024]
	ldr	x21, [sp, #152]                 ; 8-byte Folded Reload
	ldr	q0, [x21]
	str	q0, [sp, #6192]
	ldr	s0, [x19, #3296]
	ldr	s1, [x19, #3300]
	ldr	s2, [x19, #3304]
	ldr	s3, [sp, #6200]
	ldr	s4, [sp, #6204]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6912]
	ldr	s6, [sp, #6916]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6208]
	str	s4, [sp, #6212]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6920]
	ldr	s6, [sp, #6924]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6216]
	str	s4, [sp, #6220]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6928]
	ldr	s6, [sp, #6932]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6224]
	str	s4, [sp, #6228]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6936]
	ldr	s6, [sp, #6940]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6232]
	str	s4, [sp, #6236]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6944]
	ldr	s6, [sp, #6948]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6240]
	str	s4, [sp, #6244]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6952]
	ldr	s6, [sp, #6956]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6248]
	str	s4, [sp, #6252]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6960]
	ldr	s6, [sp, #6964]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6256]
	str	s4, [sp, #6260]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6968]
	ldr	s6, [sp, #6972]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6264]
	str	s4, [sp, #6268]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6976]
	ldr	s6, [sp, #6980]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6272]
	str	s4, [sp, #6276]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6984]
	ldr	s6, [sp, #6988]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6280]
	str	s4, [sp, #6284]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #6992]
	ldr	s6, [sp, #6996]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6288]
	str	s4, [sp, #6292]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #7000]
	ldr	s6, [sp, #7004]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6296]
	str	s4, [sp, #6300]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #7008]
	ldr	s6, [sp, #7012]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6304]
	str	s4, [sp, #6308]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #7016]
	ldr	s6, [sp, #7020]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6312]
	str	s4, [sp, #6316]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #7024]
	ldr	s6, [sp, #7028]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #6320]
	str	s4, [sp, #6324]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #7032]
	ldr	s6, [sp, #7036]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #6328]
	str	s0, [sp, #6332]
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2096
	ldur	q0, [x9, #128]
	str	q0, [x21]
	ldr	x9, [sp, #3000]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #6048]
	ldr	s0, [x19, #3296]
	ldr	s3, [x19, #3328]
	ldr	s4, [x19, #3332]
	ldr	s1, [x19, #3336]
	ldr	s5, [x19, #3340]
	ldr	s6, [x19, #3344]
	fneg	s7, s1
	ldr	s17, [sp, #6204]
	ldr	s16, [sp, #6056]
	ldr	s2, [sp, #6060]
	ldr	x9, [sp, #864]                  ; 8-byte Folded Reload
	fmov	s18, s2
	ldr	x21, [sp, #480]                 ; 8-byte Folded Reload
LBB17_58:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s3, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s3, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_58
; %bb.59:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1952
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #3000]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2992]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #5904]
	ldr	s5, [x19, #3364]
	ldr	s6, [x19, #3368]
	ldr	s0, [x19, #3372]
	ldr	s7, [x19, #3376]
	ldr	s16, [x19, #3380]
	fneg	s17, s0
	ldr	s3, [sp, #5912]
	ldr	s4, [sp, #5916]
	mov	x9, x21
	fmov	s19, s4
	fmov	s18, s3
	ldr	x21, [sp, #440]                 ; 8-byte Folded Reload
LBB17_60:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s2, s6, s2
	ldr	s20, [x9]
	fmadd	s2, s5, s20, s2
	ldur	s21, [x9, #-8]
	fmadd	s2, s5, s21, s2
	fmul	s21, s16, s19
	fmadd	s18, s7, s18, s21
	fmul	s21, s18, s17
	fmov	s18, s19
	fmadd	s19, s1, s2, s21
	str	s19, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s2, s20
	cmp	x8, #128
	b.ne	LBB17_60
; %bb.61:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1808
	ldur	q1, [x9, #128]
	ldr	x9, [sp, #2992]                 ; 8-byte Folded Reload
	str	q1, [x9]
	ldr	s1, [x19, #3400]
	ldr	s2, [x19, #3404]
	ext.16b	v5, v4, v4, #4
	ldr	q6, [sp, #5920]
	ldr	q7, [sp, #5936]
	ext.16b	v5, v5, v6, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v6, v1[0]
	mov.s	v3[1], v4[0]
	mov.d	v3[1], v6[0]
	fmla.4s	v5, v3, v1[0]
	fmul.4s	v3, v5, v0[0]
	ext.16b	v4, v6, v7, #12
	fmul.4s	v4, v4, v2[0]
	fmla.4s	v4, v7, v1[0]
	ext.16b	v5, v6, v7, #8
	fmla.4s	v4, v5, v1[0]
	fmul.4s	v4, v4, v0[0]
	str	q3, [sp, #5776]
	str	q4, [sp, #5792]
	ldr	q3, [sp, #5952]
	ldr	q4, [sp, #5968]
	ext.16b	v5, v7, v3, #12
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v3, v1[0]
	ext.16b	v6, v7, v3, #8
	fmla.4s	v5, v6, v1[0]
	fmul.4s	v5, v5, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q5, [sp, #5808]
	str	q3, [sp, #5824]
	ldr	q3, [sp, #5984]
	ldr	q5, [sp, #6000]
	ext.16b	v6, v4, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v4, v4, v3, #8
	fmla.4s	v6, v4, v1[0]
	fmul.4s	v4, v6, v0[0]
	ext.16b	v6, v3, v5, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v5, v1[0]
	ext.16b	v3, v3, v5, #8
	fmla.4s	v6, v3, v1[0]
	fmul.4s	v3, v6, v0[0]
	str	q4, [sp, #5840]
	str	q3, [sp, #5856]
	ldr	q3, [sp, #6016]
	ldr	q4, [sp, #6032]
	ext.16b	v6, v5, v3, #12
	fmul.4s	v6, v6, v2[0]
	fmla.4s	v6, v3, v1[0]
	ext.16b	v5, v5, v3, #8
	fmla.4s	v6, v5, v1[0]
	fmul.4s	v5, v6, v0[0]
	ext.16b	v6, v3, v4, #12
	fmul.4s	v2, v6, v2[0]
	fmla.4s	v2, v4, v1[0]
	ext.16b	v3, v3, v4, #8
	fmla.4s	v2, v3, v1[0]
	fmul.4s	v0, v2, v0[0]
	str	q5, [sp, #5872]
	str	q0, [sp, #5888]
	ldr	x21, [sp, #144]                 ; 8-byte Folded Reload
	ldr	q0, [x21]
	str	q0, [sp, #5056]
	ldr	s0, [x19, #3560]
	ldr	s1, [x19, #3564]
	ldr	s2, [x19, #3568]
	ldr	s3, [sp, #5064]
	ldr	s4, [sp, #5068]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5776]
	ldr	s6, [sp, #5780]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5072]
	str	s4, [sp, #5076]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5784]
	ldr	s6, [sp, #5788]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5080]
	str	s4, [sp, #5084]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5792]
	ldr	s6, [sp, #5796]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5088]
	str	s4, [sp, #5092]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5800]
	ldr	s6, [sp, #5804]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5096]
	str	s4, [sp, #5100]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5808]
	ldr	s6, [sp, #5812]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5104]
	str	s4, [sp, #5108]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5816]
	ldr	s6, [sp, #5820]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5112]
	str	s4, [sp, #5116]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5824]
	ldr	s6, [sp, #5828]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5120]
	str	s4, [sp, #5124]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5832]
	ldr	s6, [sp, #5836]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5128]
	str	s4, [sp, #5132]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5840]
	ldr	s6, [sp, #5844]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5136]
	str	s4, [sp, #5140]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5848]
	ldr	s6, [sp, #5852]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5144]
	str	s4, [sp, #5148]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5856]
	ldr	s6, [sp, #5860]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5152]
	str	s4, [sp, #5156]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5864]
	ldr	s6, [sp, #5868]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5160]
	str	s4, [sp, #5164]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5872]
	ldr	s6, [sp, #5876]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5168]
	str	s4, [sp, #5172]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5880]
	ldr	s6, [sp, #5884]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5176]
	str	s4, [sp, #5180]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5888]
	ldr	s6, [sp, #5892]
	fmsub	s3, s0, s3, s5
	fmul	s5, s2, s3
	fmadd	s4, s1, s4, s5
	fmsub	s4, s0, s4, s6
	str	s3, [sp, #5184]
	str	s4, [sp, #5188]
	fmul	s5, s2, s4
	fmadd	s3, s1, s3, s5
	ldr	s5, [sp, #5896]
	ldr	s6, [sp, #5900]
	fmsub	s3, s0, s3, s5
	fmul	s2, s2, s3
	fmadd	s1, s1, s4, s2
	fmsub	s0, s0, s1, s6
	str	s3, [sp, #5192]
	str	s0, [sp, #5196]
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #960
	ldur	q0, [x9, #128]
	str	q0, [x21]
	ldr	x9, [sp, #2984]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #4912]
	ldr	s0, [x19, #3560]
	ldr	s1, [x19, #3592]
	ldr	s4, [x19, #3596]
	ldr	s2, [x19, #3600]
	ldr	s5, [x19, #3604]
	ldr	s6, [x19, #3608]
	fneg	s7, s2
	ldr	s17, [sp, #5068]
	ldr	s16, [sp, #4920]
	ldr	s3, [sp, #4924]
	ldr	x9, [sp, #896]                  ; 8-byte Folded Reload
	fmov	s18, s3
LBB17_62:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s17, s4, s17
	ldr	s19, [x9]
	fmadd	s17, s1, s19, s17
	ldur	s20, [x9, #-8]
	fmadd	s17, s1, s20, s17
	fmul	s20, s6, s18
	fmadd	s16, s5, s16, s20
	fmul	s20, s16, s7
	fmov	s16, s18
	fmadd	s18, s0, s17, s20
	str	s18, [x23, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s17, s19
	cmp	x8, #128
	b.ne	LBB17_62
; %bb.63:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #816
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2984]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2976]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #4768]
	ldr	s4, [x19, #3628]
	ldr	s5, [x19, #3632]
	ldr	s0, [x19, #3636]
	ldr	s6, [x19, #3640]
	ldr	s7, [x19, #3644]
	str	q0, [sp, #2592]                 ; 16-byte Folded Spill
	fneg	s16, s0
	ldr	s1, [sp, #4776]
	ldr	s0, [sp, #4780]
	mov	x9, x23
	fmov	s18, s0
	fmov	s17, s1
	ldr	x23, [sp, #448]                 ; 8-byte Folded Reload
LBB17_64:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s5, s3
	ldr	s19, [x9]
	fmadd	s3, s4, s19, s3
	ldur	s20, [x9, #-8]
	fmadd	s3, s4, s20, s3
	fmul	s20, s7, s18
	fmadd	s17, s6, s17, s20
	fmul	s20, s17, s16
	fmov	s17, s18
	fmadd	s18, s2, s3, s20
	str	s18, [x23, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s3, s19
	cmp	x8, #128
	b.ne	LBB17_64
; %bb.65:                               ;   in Loop: Header=BB17_7 Depth=1
	ldr	s2, [x19, #3664]
	mov	x8, #0                          ; =0x0
	ldr	s3, [x19, #3668]
	ext.16b	v4, v0, v0, #4
	ldr	q5, [sp, #4784]
	ldr	q6, [sp, #4800]
	ext.16b	v4, v4, v5, #12
	fmul.4s	v26, v4, v3[0]
	mov.s	v1[1], v0[0]
	mov.d	v1[1], v5[0]
	fmla.4s	v26, v5, v2[0]
	fmla.4s	v26, v1, v2[0]
	ext.16b	v0, v5, v6, #12
	fmul.4s	v25, v0, v3[0]
	fmla.4s	v25, v6, v2[0]
	ext.16b	v0, v5, v6, #8
	fmla.4s	v25, v0, v2[0]
	ldr	q0, [sp, #4816]
	ldr	q1, [sp, #4832]
	ext.16b	v4, v6, v0, #12
	fmul.4s	v24, v4, v3[0]
	fmla.4s	v24, v0, v2[0]
	ext.16b	v4, v6, v0, #8
	fmla.4s	v24, v4, v2[0]
	ext.16b	v4, v0, v1, #12
	fmul.4s	v23, v4, v3[0]
	fmla.4s	v23, v1, v2[0]
	ext.16b	v0, v0, v1, #8
	fmla.4s	v23, v0, v2[0]
	ldr	q0, [sp, #4848]
	ldr	q19, [sp, #4864]
	ext.16b	v4, v1, v0, #12
	fmul.4s	v18, v4, v3[0]
	fmla.4s	v18, v0, v2[0]
	ext.16b	v1, v1, v0, #8
	fmla.4s	v18, v1, v2[0]
	ext.16b	v1, v0, v19, #12
	fmul.4s	v17, v1, v3[0]
	fmla.4s	v17, v19, v2[0]
	ext.16b	v0, v0, v19, #8
	fmla.4s	v17, v0, v2[0]
	ldr	q0, [sp, #4880]
	ldr	q1, [sp, #4896]
	ext.16b	v4, v19, v0, #12
	fmul.4s	v16, v4, v3[0]
	fmla.4s	v16, v0, v2[0]
	ext.16b	v19, v19, v0, #8
	fmla.4s	v16, v19, v2[0]
	ext.16b	v19, v0, v1, #12
	fmul.4s	v7, v19, v3[0]
	fmla.4s	v7, v1, v2[0]
	ext.16b	v0, v0, v1, #8
	fmla.4s	v7, v0, v2[0]
	ldur	q0, [x19, #252]
	str	q0, [sp, #19264]
	ldp	s2, s0, [x19, #232]
	ldr	s1, [x19, #248]
	add	x9, sp, #2892
	ldr	s19, [x9, #16380]
	add	x9, sp, #2896
	ldr	s20, [x9, #16380]
	fmul	s21, s1, s20
	fmadd	s19, s0, s19, s21
	add	x9, sp, #3028
	ldr	s21, [x9, #16380]
	add	x9, sp, #3032
	ldr	s22, [x9, #16380]
	fmsub	s3, s2, s19, s21
	str	s3, [sp, #1688]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s20, s19
	fmsub	s4, s2, s19, s22
	str	s4, [sp, #1684]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3036
	ldr	s20, [x9, #16380]
	add	x9, sp, #3040
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1680]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1676]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3044
	ldr	s20, [x9, #16380]
	add	x9, sp, #3048
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1672]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1668]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3052
	ldr	s20, [x9, #16380]
	add	x9, sp, #3056
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1664]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1660]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3060
	ldr	s20, [x9, #16380]
	add	x9, sp, #3064
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1656]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1652]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3068
	ldr	s20, [x9, #16380]
	add	x9, sp, #3072
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1648]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1644]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3076
	ldr	s20, [x9, #16380]
	add	x9, sp, #3080
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1640]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1636]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3084
	ldr	s20, [x9, #16380]
	add	x9, sp, #3088
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1632]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1628]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3092
	ldr	s20, [x9, #16380]
	add	x9, sp, #3096
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1624]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1620]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3100
	ldr	s20, [x9, #16380]
	add	x9, sp, #3104
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1616]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1612]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3108
	ldr	s20, [x9, #16380]
	add	x9, sp, #3112
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1608]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1604]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3116
	ldr	s20, [x9, #16380]
	add	x9, sp, #3120
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1600]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1596]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3124
	ldr	s20, [x9, #16380]
	add	x9, sp, #3128
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1592]                 ; 4-byte Folded Spill
	fmul	s19, s1, s3
	fmadd	s19, s0, s4, s19
	fmsub	s4, s2, s19, s21
	str	s4, [sp, #1588]                 ; 4-byte Folded Spill
	fmul	s19, s1, s4
	fmadd	s19, s0, s3, s19
	add	x9, sp, #3132
	ldr	s20, [x9, #16380]
	add	x9, sp, #3136
	ldr	s21, [x9, #16380]
	fmsub	s15, s2, s19, s20
	fmul	s19, s1, s15
	fmadd	s19, s0, s4, s19
	fmsub	s14, s2, s19, s21
	fmul	s19, s1, s14
	fmadd	s19, s0, s15, s19
	add	x9, sp, #3140
	ldr	s20, [x9, #16380]
	add	x9, sp, #3144
	ldr	s21, [x9, #16380]
	fmsub	s13, s2, s19, s20
	fmul	s19, s1, s13
	fmadd	s19, s0, s14, s19
	fmsub	s12, s2, s19, s21
	fmul	s19, s1, s12
	fmadd	s19, s0, s13, s19
	add	x9, sp, #3148
	ldr	s20, [x9, #16380]
	add	x9, sp, #3152
	ldr	s21, [x9, #16380]
	fmsub	s3, s2, s19, s20
	str	s3, [sp, #1584]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s12, s1
	fmsub	s0, s2, s0, s21
	str	s0, [sp, #1580]                 ; 4-byte Folded Spill
	ldr	x9, [sp, #2968]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #18128]
	ldr	s2, [x19, #516]
	ldr	s1, [x19, #528]
	add	x9, sp, #1756
	ldr	s0, [x9, #16380]
	add	x9, sp, #1760
	ldr	s19, [x9, #16380]
	fmul	s20, s1, s19
	fmadd	s20, s2, s0, s20
	ldr	s0, [x19, #512]
	add	x9, sp, #1892
	ldr	s21, [x9, #16380]
	add	x9, sp, #1896
	ldr	s22, [x9, #16380]
	fmsub	s11, s0, s20, s21
	fmul	s20, s1, s11
	fmadd	s19, s2, s19, s20
	fmsub	s10, s0, s19, s22
	fmul	s19, s1, s10
	fmadd	s19, s2, s11, s19
	add	x9, sp, #1900
	ldr	s20, [x9, #16380]
	add	x9, sp, #1904
	ldr	s21, [x9, #16380]
	fmsub	s9, s0, s19, s20
	fmul	s19, s1, s9
	fmadd	s19, s2, s10, s19
	fmsub	s8, s0, s19, s21
	fmul	s19, s1, s8
	fmadd	s19, s2, s9, s19
	add	x9, sp, #1908
	ldr	s20, [x9, #16380]
	add	x9, sp, #1912
	ldr	s21, [x9, #16380]
	fmsub	s31, s0, s19, s20
	fmul	s19, s1, s31
	fmadd	s19, s2, s8, s19
	fmsub	s30, s0, s19, s21
	fmul	s19, s1, s30
	fmadd	s19, s2, s31, s19
	add	x9, sp, #1916
	ldr	s20, [x9, #16380]
	add	x9, sp, #1920
	ldr	s21, [x9, #16380]
	fmsub	s29, s0, s19, s20
	fmul	s19, s1, s29
	fmadd	s19, s2, s30, s19
	fmsub	s28, s0, s19, s21
	fmul	s19, s1, s28
	fmadd	s19, s2, s29, s19
	add	x9, sp, #1924
	ldr	s20, [x9, #16380]
	add	x9, sp, #1928
	ldr	s21, [x9, #16380]
	fmsub	s27, s0, s19, s20
	fmul	s19, s1, s27
	fmadd	s19, s2, s28, s19
	fmsub	s22, s0, s19, s21
	fmul	s19, s1, s22
	fmadd	s19, s2, s27, s19
	add	x9, sp, #1932
	ldr	s20, [x9, #16380]
	add	x9, sp, #1936
	ldr	s3, [x9, #16380]
	fmsub	s21, s0, s19, s20
	fmul	s19, s1, s21
	fmadd	s19, s2, s22, s19
	fmsub	s20, s0, s19, s3
	fmul	s3, s1, s20
	fmadd	s3, s2, s21, s3
	add	x9, sp, #1940
	ldr	s19, [x9, #16380]
	add	x9, sp, #1944
	ldr	s4, [x9, #16380]
	fmsub	s19, s0, s3, s19
	fmul	s3, s1, s19
	fmadd	s3, s2, s20, s3
	fmsub	s6, s0, s3, s4
	str	s6, [sp, #2588]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s19, s3
	add	x9, sp, #1948
	ldr	s4, [x9, #16380]
	add	x9, sp, #1952
	ldr	s5, [x9, #16380]
	fmsub	s4, s0, s3, s4
	str	s4, [sp, #2576]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s2, s6, s3
	fmsub	s6, s0, s3, s5
	str	s6, [sp, #2572]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s4, s3
	add	x9, sp, #1956
	ldr	s4, [x9, #16380]
	add	x9, sp, #1960
	ldr	s5, [x9, #16380]
	fmsub	s4, s0, s3, s4
	str	s4, [sp, #2560]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s2, s6, s3
	fmsub	s6, s0, s3, s5
	str	s6, [sp, #2556]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s4, s3
	add	x9, sp, #1964
	ldr	s4, [x9, #16380]
	add	x9, sp, #1968
	ldr	s5, [x9, #16380]
	fmsub	s4, s0, s3, s4
	str	s4, [sp, #2544]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s2, s6, s3
	fmsub	s6, s0, s3, s5
	str	s6, [sp, #2536]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s4, s3
	add	x9, sp, #1972
	ldr	s4, [x9, #16380]
	add	x9, sp, #1976
	ldr	s5, [x9, #16380]
	fmsub	s4, s0, s3, s4
	str	s4, [sp, #2532]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s2, s6, s3
	fmsub	s6, s0, s3, s5
	str	s6, [sp, #2520]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s4, s3
	add	x9, sp, #1980
	ldr	s4, [x9, #16380]
	add	x9, sp, #1984
	ldr	s5, [x9, #16380]
	fmsub	s4, s0, s3, s4
	str	s4, [sp, #2516]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s2, s6, s3
	fmsub	s6, s0, s3, s5
	str	s6, [sp, #2504]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s4, s3
	add	x9, sp, #1988
	ldr	s4, [x9, #16380]
	add	x9, sp, #1992
	ldr	s5, [x9, #16380]
	fmsub	s4, s0, s3, s4
	str	s4, [sp, #2500]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s2, s6, s3
	fmsub	s6, s0, s3, s5
	str	s6, [sp, #2488]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s4, s3
	add	x9, sp, #1996
	ldr	s4, [x9, #16380]
	add	x9, sp, #2000
	ldr	s5, [x9, #16380]
	fmsub	s4, s0, s3, s4
	str	s4, [sp, #2480]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s2, s6, s3
	fmsub	s6, s0, s3, s5
	str	s6, [sp, #2476]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s4, s3
	add	x9, sp, #2004
	ldr	s4, [x9, #16380]
	add	x9, sp, #2008
	ldr	s5, [x9, #16380]
	fmsub	s4, s0, s3, s4
	str	s4, [sp, #2472]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s2, s6, s3
	fmsub	s6, s0, s3, s5
	str	s6, [sp, #2460]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s4, s3
	add	x9, sp, #2012
	ldr	s4, [x9, #16380]
	add	x9, sp, #2016
	ldr	s5, [x9, #16380]
	fmsub	s3, s0, s3, s4
	str	s3, [sp, #2468]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s1, s2, s6, s1
	fmsub	s0, s0, s1, s5
	str	s0, [sp, #2464]                 ; 4-byte Folded Spill
	ldr	x9, [sp, #2960]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #16992]
	ldr	s0, [x19, #780]
	ldr	s1, [x19, #792]
	add	x9, sp, #620
	ldr	s2, [x9, #16380]
	add	x9, sp, #624
	ldr	s3, [x9, #16380]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #776]
	add	x9, sp, #756
	ldr	s5, [x9, #16380]
	add	x9, sp, #760
	ldr	s6, [x9, #16380]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #2456]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #2452]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	add	x9, sp, #764
	ldr	s4, [x9, #16380]
	add	x9, sp, #768
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2448]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2444]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #772
	ldr	s4, [x9, #16380]
	add	x9, sp, #776
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2440]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2436]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #780
	ldr	s4, [x9, #16380]
	add	x9, sp, #784
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2432]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2428]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #788
	ldr	s4, [x9, #16380]
	add	x9, sp, #792
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2424]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2420]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #796
	ldr	s4, [x9, #16380]
	add	x9, sp, #800
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2416]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2412]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #804
	ldr	s4, [x9, #16380]
	add	x9, sp, #808
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2408]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2404]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #812
	ldr	s4, [x9, #16380]
	add	x9, sp, #816
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2400]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2396]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #820
	ldr	s4, [x9, #16380]
	add	x9, sp, #824
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2392]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2388]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #828
	ldr	s4, [x9, #16380]
	add	x9, sp, #832
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2384]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2380]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #836
	ldr	s4, [x9, #16380]
	add	x9, sp, #840
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2376]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2372]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #844
	ldr	s4, [x9, #16380]
	add	x9, sp, #848
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2368]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2364]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #852
	ldr	s4, [x9, #16380]
	add	x9, sp, #856
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2360]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2356]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #860
	ldr	s4, [x9, #16380]
	add	x9, sp, #864
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2352]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2348]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #868
	ldr	s4, [x9, #16380]
	add	x9, sp, #872
	ldr	s5, [x9, #16380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2344]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2332]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	add	x9, sp, #876
	ldr	s4, [x9, #16380]
	add	x9, sp, #880
	ldr	s5, [x9, #16380]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #2340]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #2336]                 ; 4-byte Folded Spill
	ldr	x9, [sp, #2952]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #15856]
	ldr	s0, [x19, #1044]
	ldr	s1, [x19, #1056]
	ldr	s2, [sp, #15864]
	ldr	s3, [sp, #15868]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #1040]
	ldr	s5, [sp, #16000]
	ldr	s6, [sp, #16004]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #2328]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #2324]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #16008]
	ldr	s5, [sp, #16012]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2320]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2316]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16016]
	ldr	s5, [sp, #16020]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2312]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2308]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16024]
	ldr	s5, [sp, #16028]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2304]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2300]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16032]
	ldr	s5, [sp, #16036]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2296]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2292]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16040]
	ldr	s5, [sp, #16044]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2288]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2284]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16048]
	ldr	s5, [sp, #16052]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2280]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2276]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16056]
	ldr	s5, [sp, #16060]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2272]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2268]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16064]
	ldr	s5, [sp, #16068]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2264]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2260]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16072]
	ldr	s5, [sp, #16076]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2256]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2252]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16080]
	ldr	s5, [sp, #16084]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2248]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2244]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16088]
	ldr	s5, [sp, #16092]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2240]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2236]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16096]
	ldr	s5, [sp, #16100]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2232]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2228]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16104]
	ldr	s5, [sp, #16108]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2224]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2220]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16112]
	ldr	s5, [sp, #16116]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2216]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2204]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #16120]
	ldr	s5, [sp, #16124]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #2212]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #2208]                 ; 4-byte Folded Spill
	ldr	x9, [sp, #2944]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #14720]
	ldr	s0, [x19, #1308]
	ldr	s1, [x19, #1320]
	ldr	s2, [sp, #14728]
	ldr	s3, [sp, #14732]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #1304]
	ldr	s5, [sp, #14864]
	ldr	s6, [sp, #14868]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #2200]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #2196]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #14872]
	ldr	s5, [sp, #14876]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2192]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2188]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14880]
	ldr	s5, [sp, #14884]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2184]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2180]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14888]
	ldr	s5, [sp, #14892]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2176]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2172]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14896]
	ldr	s5, [sp, #14900]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2168]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2164]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14904]
	ldr	s5, [sp, #14908]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2160]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2156]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14912]
	ldr	s5, [sp, #14916]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2152]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2148]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14920]
	ldr	s5, [sp, #14924]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2144]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2140]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14928]
	ldr	s5, [sp, #14932]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2136]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2132]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14936]
	ldr	s5, [sp, #14940]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2128]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2124]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14944]
	ldr	s5, [sp, #14948]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2120]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2116]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14952]
	ldr	s5, [sp, #14956]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2112]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2108]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14960]
	ldr	s5, [sp, #14964]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2104]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2100]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14968]
	ldr	s5, [sp, #14972]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2096]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2092]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14976]
	ldr	s5, [sp, #14980]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2088]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2076]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #14984]
	ldr	s5, [sp, #14988]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #2084]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #2080]                 ; 4-byte Folded Spill
	ldr	x23, [sp, #136]                 ; 8-byte Folded Reload
	ldr	q0, [x23]
	str	q0, [sp, #13584]
	ldr	s0, [x19, #1572]
	ldr	s1, [x19, #1584]
	ldr	s2, [sp, #13592]
	ldr	s3, [sp, #13596]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #1568]
	ldr	s5, [sp, #13728]
	ldr	s6, [sp, #13732]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #2072]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #2068]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #13736]
	ldr	s5, [sp, #13740]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2064]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2060]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13744]
	ldr	s5, [sp, #13748]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2056]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2052]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13752]
	ldr	s5, [sp, #13756]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2048]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2044]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13760]
	ldr	s5, [sp, #13764]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2040]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2036]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13768]
	ldr	s5, [sp, #13772]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2032]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2028]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13776]
	ldr	s5, [sp, #13780]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2024]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2020]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13784]
	ldr	s5, [sp, #13788]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2016]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2012]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13792]
	ldr	s5, [sp, #13796]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2008]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #2004]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13800]
	ldr	s5, [sp, #13804]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #2000]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1996]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13808]
	ldr	s5, [sp, #13812]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1992]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1988]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13816]
	ldr	s5, [sp, #13820]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1984]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1980]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13824]
	ldr	s5, [sp, #13828]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1976]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1972]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13832]
	ldr	s5, [sp, #13836]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1968]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1964]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13840]
	ldr	s5, [sp, #13844]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1960]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1948]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #13848]
	ldr	s5, [sp, #13852]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #1956]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #1952]                 ; 4-byte Folded Spill
	ldr	x20, [sp, #128]                 ; 8-byte Folded Reload
	ldr	q0, [x20]
	str	q0, [sp, #12448]
	ldr	s0, [x19, #1836]
	ldr	s1, [x19, #1848]
	ldr	s2, [sp, #12456]
	ldr	s3, [sp, #12460]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #1832]
	ldr	s5, [sp, #12592]
	ldr	s6, [sp, #12596]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #1944]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #1940]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #12600]
	ldr	s5, [sp, #12604]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1936]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1932]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12608]
	ldr	s5, [sp, #12612]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1928]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1924]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12616]
	ldr	s5, [sp, #12620]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1920]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1916]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12624]
	ldr	s5, [sp, #12628]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1912]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1908]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12632]
	ldr	s5, [sp, #12636]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1904]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1900]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12640]
	ldr	s5, [sp, #12644]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1896]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1892]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12648]
	ldr	s5, [sp, #12652]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1888]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1884]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12656]
	ldr	s5, [sp, #12660]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1880]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1876]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12664]
	ldr	s5, [sp, #12668]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1872]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1868]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12672]
	ldr	s5, [sp, #12676]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1864]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1860]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12680]
	ldr	s5, [sp, #12684]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1856]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1852]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12688]
	ldr	s5, [sp, #12692]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1848]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1844]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12696]
	ldr	s5, [sp, #12700]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1840]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1836]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12704]
	ldr	s5, [sp, #12708]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1832]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1820]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #12712]
	ldr	s5, [sp, #12716]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #1828]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #1824]                 ; 4-byte Folded Spill
	ldr	x25, [sp, #112]                 ; 8-byte Folded Reload
	ldr	q0, [x25]
	str	q0, [sp, #11312]
	ldr	s0, [x19, #2100]
	ldr	s1, [x19, #2112]
	ldr	s2, [sp, #11320]
	ldr	s3, [sp, #11324]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #2096]
	ldr	s5, [sp, #11456]
	ldr	s6, [sp, #11460]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #1816]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #1812]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #11464]
	ldr	s5, [sp, #11468]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1808]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1804]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11472]
	ldr	s5, [sp, #11476]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1800]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1796]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11480]
	ldr	s5, [sp, #11484]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1792]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1788]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11488]
	ldr	s5, [sp, #11492]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1784]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1780]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11496]
	ldr	s5, [sp, #11500]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1776]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1772]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11504]
	ldr	s5, [sp, #11508]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1768]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1764]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11512]
	ldr	s5, [sp, #11516]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1760]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1756]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11520]
	ldr	s5, [sp, #11524]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1752]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1748]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11528]
	ldr	s5, [sp, #11532]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1744]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1740]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11536]
	ldr	s5, [sp, #11540]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1736]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1732]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11544]
	ldr	s5, [sp, #11548]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1728]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1724]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11552]
	ldr	s5, [sp, #11556]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1720]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1716]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11560]
	ldr	s5, [sp, #11564]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1712]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1708]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11568]
	ldr	s5, [sp, #11572]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1704]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1692]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #11576]
	ldr	s5, [sp, #11580]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #1700]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #1696]                 ; 4-byte Folded Spill
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #672
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2976]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	q2, [sp, #2592]                 ; 16-byte Folded Reload
	fmul.4s	v0, v26, v2[0]
	fmul.4s	v1, v25, v2[0]
	str	q0, [sp, #4640]
	str	q1, [sp, #4656]
	fmul.4s	v0, v24, v2[0]
	fmul.4s	v1, v23, v2[0]
	str	q0, [sp, #4672]
	str	q1, [sp, #4688]
	fmul.4s	v0, v18, v2[0]
	fmul.4s	v1, v17, v2[0]
	str	q0, [sp, #4704]
	str	q1, [sp, #4720]
	fmul.4s	v0, v16, v2[0]
	fmul.4s	v1, v7, v2[0]
	str	q0, [sp, #4736]
	str	q1, [sp, #4752]
	ldr	s0, [sp, #1688]                 ; 4-byte Folded Reload
	add	x9, sp, #2900
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1684]                 ; 4-byte Folded Reload
	add	x9, sp, #2904
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1680]                 ; 4-byte Folded Reload
	add	x9, sp, #2908
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1676]                 ; 4-byte Folded Reload
	add	x9, sp, #2912
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1672]                 ; 4-byte Folded Reload
	add	x9, sp, #2916
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1668]                 ; 4-byte Folded Reload
	add	x9, sp, #2920
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1664]                 ; 4-byte Folded Reload
	add	x9, sp, #2924
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1660]                 ; 4-byte Folded Reload
	add	x9, sp, #2928
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1656]                 ; 4-byte Folded Reload
	add	x9, sp, #2932
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1652]                 ; 4-byte Folded Reload
	add	x9, sp, #2936
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1648]                 ; 4-byte Folded Reload
	add	x9, sp, #2940
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1644]                 ; 4-byte Folded Reload
	add	x9, sp, #2944
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1640]                 ; 4-byte Folded Reload
	add	x9, sp, #2948
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1636]                 ; 4-byte Folded Reload
	add	x9, sp, #2952
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1632]                 ; 4-byte Folded Reload
	add	x9, sp, #2956
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1628]                 ; 4-byte Folded Reload
	add	x9, sp, #2960
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1624]                 ; 4-byte Folded Reload
	add	x9, sp, #2964
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1620]                 ; 4-byte Folded Reload
	add	x9, sp, #2968
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1616]                 ; 4-byte Folded Reload
	add	x9, sp, #2972
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1612]                 ; 4-byte Folded Reload
	add	x9, sp, #2976
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1608]                 ; 4-byte Folded Reload
	add	x9, sp, #2980
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1604]                 ; 4-byte Folded Reload
	add	x9, sp, #2984
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1600]                 ; 4-byte Folded Reload
	add	x9, sp, #2988
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1596]                 ; 4-byte Folded Reload
	add	x9, sp, #2992
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1592]                 ; 4-byte Folded Reload
	add	x9, sp, #2996
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1588]                 ; 4-byte Folded Reload
	add	x9, sp, #3000
	str	s0, [x9, #16380]
	add	x9, sp, #3004
	str	s15, [x9, #16380]
	add	x9, sp, #3008
	str	s14, [x9, #16380]
	add	x9, sp, #3012
	str	s13, [x9, #16380]
	add	x9, sp, #3016
	str	s12, [x9, #16380]
	ldr	s0, [sp, #1584]                 ; 4-byte Folded Reload
	add	x9, sp, #3020
	str	s0, [x9, #16380]
	ldr	s0, [sp, #1580]                 ; 4-byte Folded Reload
	add	x9, sp, #3024
	str	s0, [x9, #16380]
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #2880
	ldur	q0, [x9, #128]
	stur	q0, [x19, #252]
	add	x9, sp, #1764
	str	s11, [x9, #16380]
	add	x9, sp, #1768
	str	s10, [x9, #16380]
	add	x9, sp, #1772
	str	s9, [x9, #16380]
	add	x9, sp, #1776
	str	s8, [x9, #16380]
	add	x9, sp, #1780
	str	s31, [x9, #16380]
	add	x9, sp, #1784
	str	s30, [x9, #16380]
	add	x9, sp, #1788
	str	s29, [x9, #16380]
	add	x9, sp, #1792
	str	s28, [x9, #16380]
	add	x9, sp, #1796
	str	s27, [x9, #16380]
	add	x9, sp, #1800
	str	s22, [x9, #16380]
	add	x9, sp, #1804
	str	s21, [x9, #16380]
	add	x9, sp, #1808
	str	s20, [x9, #16380]
	add	x9, sp, #1812
	str	s19, [x9, #16380]
	ldr	x21, [sp, #104]                 ; 8-byte Folded Reload
	ldr	q0, [x21]
	str	q0, [sp, #10176]
	ldr	s0, [x19, #2364]
	ldr	s1, [x19, #2376]
	ldr	s2, [sp, #10184]
	ldr	s3, [sp, #10188]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #2360]
	ldr	s5, [sp, #10320]
	ldr	s6, [sp, #10324]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #2592]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #1688]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #10328]
	ldr	s5, [sp, #10332]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1684]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1680]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10336]
	ldr	s5, [sp, #10340]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1676]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1672]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10344]
	ldr	s5, [sp, #10348]
	fmsub	s7, s2, s3, s4
	str	s7, [sp, #1668]                 ; 4-byte Folded Spill
	fmul	s3, s1, s7
	fmadd	s3, s0, s6, s3
	fmsub	s3, s2, s3, s5
	str	s3, [sp, #10220]
	fmul	s4, s1, s3
	fmadd	s4, s0, s7, s4
	ldr	s5, [sp, #10352]
	ldr	s6, [sp, #10356]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #1664]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #1660]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #10360]
	ldr	s5, [sp, #10364]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1656]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1652]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10368]
	ldr	s5, [sp, #10372]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1648]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1644]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10376]
	ldr	s5, [sp, #10380]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1640]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1636]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10384]
	ldr	s5, [sp, #10388]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1632]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1628]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10392]
	ldr	s5, [sp, #10396]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1624]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1620]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10400]
	ldr	s5, [sp, #10404]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1616]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1612]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10408]
	ldr	s5, [sp, #10412]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1608]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1604]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10416]
	ldr	s5, [sp, #10420]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1600]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1596]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10424]
	ldr	s5, [sp, #10428]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1592]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1588]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10432]
	ldr	s5, [sp, #10436]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1584]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1572]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #10440]
	ldr	s5, [sp, #10444]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #1580]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #1576]                 ; 4-byte Folded Spill
	ldr	x24, [sp, #96]                  ; 8-byte Folded Reload
	ldr	q0, [x24]
	str	q0, [sp, #9040]
	ldr	s0, [x19, #2628]
	ldr	s1, [x19, #2640]
	ldr	s2, [sp, #9048]
	ldr	s3, [sp, #9052]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #2624]
	ldr	s5, [sp, #9184]
	ldr	s6, [sp, #9188]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #1568]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #1564]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #9192]
	ldr	s5, [sp, #9196]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1560]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1556]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9200]
	ldr	s5, [sp, #9204]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1552]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1548]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9208]
	ldr	s5, [sp, #9212]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1544]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1540]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9216]
	ldr	s5, [sp, #9220]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1536]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1532]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9224]
	ldr	s5, [sp, #9228]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1528]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1524]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9232]
	ldr	s5, [sp, #9236]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1520]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1516]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9240]
	ldr	s5, [sp, #9244]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1512]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1508]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9248]
	ldr	s5, [sp, #9252]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1504]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1500]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9256]
	ldr	s5, [sp, #9260]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1496]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1492]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9264]
	ldr	s5, [sp, #9268]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1488]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1484]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9272]
	ldr	s5, [sp, #9276]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1480]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1476]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9280]
	ldr	s5, [sp, #9284]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1472]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1468]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9288]
	ldr	s5, [sp, #9292]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1464]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1460]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9296]
	ldr	s5, [sp, #9300]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1456]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1444]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #9304]
	ldr	s5, [sp, #9308]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #1452]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #1448]                 ; 4-byte Folded Spill
	ldr	x22, [sp, #88]                  ; 8-byte Folded Reload
	ldr	q0, [x22]
	str	q0, [sp, #7904]
	ldr	s0, [x19, #2892]
	ldr	s1, [x19, #2904]
	ldr	s2, [sp, #7912]
	ldr	s3, [sp, #7916]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #2888]
	ldr	s5, [sp, #8048]
	ldr	s6, [sp, #8052]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #1440]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #1436]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #8056]
	ldr	s5, [sp, #8060]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1432]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1428]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8064]
	ldr	s5, [sp, #8068]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1424]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1420]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8072]
	ldr	s5, [sp, #8076]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1416]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1412]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8080]
	ldr	s5, [sp, #8084]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1408]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1404]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8088]
	ldr	s5, [sp, #8092]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1400]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1396]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8096]
	ldr	s5, [sp, #8100]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1392]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1388]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8104]
	ldr	s5, [sp, #8108]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1384]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1380]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8112]
	ldr	s5, [sp, #8116]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1376]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1372]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8120]
	ldr	s5, [sp, #8124]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1368]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1364]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8128]
	ldr	s5, [sp, #8132]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1360]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1356]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8136]
	ldr	s5, [sp, #8140]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1352]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1348]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8144]
	ldr	s5, [sp, #8148]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1344]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1340]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8152]
	ldr	s5, [sp, #8156]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1336]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1332]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8160]
	ldr	s5, [sp, #8164]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1320]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1316]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #8168]
	ldr	s5, [sp, #8172]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #1328]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #1324]                 ; 4-byte Folded Spill
	ldr	x27, [sp, #80]                  ; 8-byte Folded Reload
	ldr	q0, [x27]
	str	q0, [sp, #6768]
	ldr	s0, [x19, #3156]
	ldr	s1, [x19, #3168]
	ldr	s2, [sp, #6776]
	ldr	s3, [sp, #6780]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #3152]
	ldr	s5, [sp, #6912]
	ldr	s6, [sp, #6916]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #1312]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #1308]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #6920]
	ldr	s5, [sp, #6924]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1304]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1300]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6928]
	ldr	s5, [sp, #6932]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1296]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1292]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6936]
	ldr	s5, [sp, #6940]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1288]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1284]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6944]
	ldr	s5, [sp, #6948]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1280]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1276]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6952]
	ldr	s5, [sp, #6956]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1272]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1268]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6960]
	ldr	s5, [sp, #6964]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1264]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1260]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6968]
	ldr	s5, [sp, #6972]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1256]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1252]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6976]
	ldr	s5, [sp, #6980]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1248]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1244]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6984]
	ldr	s5, [sp, #6988]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1240]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1236]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #6992]
	ldr	s5, [sp, #6996]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1232]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1228]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #7000]
	ldr	s5, [sp, #7004]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1224]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1220]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #7008]
	ldr	s5, [sp, #7012]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1216]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1212]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #7016]
	ldr	s5, [sp, #7020]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1208]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1204]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #7024]
	ldr	s5, [sp, #7028]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1200]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1188]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #7032]
	ldr	s5, [sp, #7036]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #1196]                 ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #1192]                 ; 4-byte Folded Spill
	ldr	x26, [sp, #72]                  ; 8-byte Folded Reload
	ldr	q0, [x26]
	str	q0, [sp, #5632]
	ldr	s0, [x19, #3420]
	ldr	s1, [x19, #3432]
	ldr	s2, [sp, #5640]
	ldr	s3, [sp, #5644]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	ldr	s2, [x19, #3416]
	ldr	s5, [sp, #5776]
	ldr	s6, [sp, #5780]
	fmsub	s5, s2, s4, s5
	str	s5, [sp, #1184]                 ; 4-byte Folded Spill
	fmul	s4, s1, s5
	fmadd	s3, s0, s3, s4
	fmsub	s6, s2, s3, s6
	str	s6, [sp, #1180]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s5, s3
	ldr	s4, [sp, #5784]
	ldr	s5, [sp, #5788]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1176]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1172]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5792]
	ldr	s5, [sp, #5796]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1168]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1164]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5800]
	ldr	s5, [sp, #5804]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1160]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1156]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5808]
	ldr	s5, [sp, #5812]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1152]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1148]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5816]
	ldr	s5, [sp, #5820]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1144]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1140]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5824]
	ldr	s5, [sp, #5828]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1136]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1132]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5832]
	ldr	s5, [sp, #5836]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1128]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1124]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5840]
	ldr	s5, [sp, #5844]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1120]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1112]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5848]
	ldr	s5, [sp, #5852]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1104]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1080]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5856]
	ldr	s5, [sp, #5860]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1068]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1048]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5864]
	ldr	s5, [sp, #5868]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1036]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1012]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5872]
	ldr	s5, [sp, #5876]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #1024]                 ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #1000]                 ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5880]
	ldr	s5, [sp, #5884]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #988]                  ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #972]                  ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5888]
	ldr	s5, [sp, #5892]
	fmsub	s4, s2, s3, s4
	str	s4, [sp, #940]                  ; 4-byte Folded Spill
	fmul	s3, s1, s4
	fmadd	s3, s0, s6, s3
	fmsub	s6, s2, s3, s5
	str	s6, [sp, #932]                  ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s0, s4, s3
	ldr	s4, [sp, #5896]
	ldr	s5, [sp, #5900]
	fmsub	s3, s2, s3, s4
	str	s3, [sp, #936]                  ; 4-byte Folded Spill
	fmul	s1, s1, s3
	fmadd	s0, s0, s6, s1
	fmsub	s0, s2, s0, s5
	str	s0, [sp, #948]                  ; 4-byte Folded Spill
	ldr	x10, [sp, #64]                  ; 8-byte Folded Reload
	ldr	q0, [x10]
	str	q0, [sp, #4496]
	ldr	s2, [x19, #3684]
	ldr	s1, [x19, #3696]
	ldr	s0, [sp, #4504]
	ldr	s3, [sp, #4508]
	fmul	s4, s1, s3
	fmadd	s4, s2, s0, s4
	ldr	s0, [x19, #3680]
	ldr	s5, [sp, #4640]
	ldr	s6, [sp, #4640]
	str	s6, [sp, #1116]                 ; 4-byte Folded Spill
	fmsub	s6, s0, s4, s5
	str	s6, [sp, #928]                  ; 4-byte Folded Spill
	fmul	s4, s1, s6
	fmadd	s3, s2, s3, s4
	ldr	s4, [sp, #4644]
	ldr	s5, [sp, #4644]
	str	s5, [sp, #1108]                 ; 4-byte Folded Spill
	fmsub	s7, s0, s3, s4
	str	s7, [sp, #924]                  ; 4-byte Folded Spill
	fmul	s3, s1, s7
	fmadd	s3, s2, s6, s3
	ldr	s4, [sp, #4648]
	ldr	s5, [sp, #4648]
	str	s5, [sp, #1100]                 ; 4-byte Folded Spill
	fmsub	s6, s0, s3, s4
	str	s6, [sp, #920]                  ; 4-byte Folded Spill
	fmul	s3, s1, s6
	fmadd	s3, s2, s7, s3
	ldr	s4, [sp, #4652]
	ldr	s5, [sp, #4652]
	str	s5, [sp, #1096]                 ; 4-byte Folded Spill
	fmsub	s7, s0, s3, s4
	str	s7, [sp, #916]                  ; 4-byte Folded Spill
	fmul	s3, s1, s7
	fmadd	s3, s2, s6, s3
	ldr	s4, [sp, #4656]
	ldr	s5, [sp, #4656]
	str	s5, [sp, #1092]                 ; 4-byte Folded Spill
	fmsub	s14, s0, s3, s4
	fmul	s3, s1, s14
	fmadd	s3, s2, s7, s3
	ldr	s4, [sp, #4660]
	ldr	s5, [sp, #4660]
	str	s5, [sp, #1088]                 ; 4-byte Folded Spill
	fmsub	s13, s0, s3, s4
	fmul	s3, s1, s13
	fmadd	s3, s2, s14, s3
	ldr	s4, [sp, #4664]
	ldr	s5, [sp, #4664]
	str	s5, [sp, #1084]                 ; 4-byte Folded Spill
	fmsub	s12, s0, s3, s4
	fmul	s3, s1, s12
	fmadd	s3, s2, s13, s3
	ldr	s4, [sp, #4668]
	ldr	s5, [sp, #4668]
	str	s5, [sp, #1076]                 ; 4-byte Folded Spill
	fmsub	s11, s0, s3, s4
	fmul	s3, s1, s11
	fmadd	s3, s2, s12, s3
	ldr	s4, [sp, #4672]
	ldr	s5, [sp, #4672]
	str	s5, [sp, #1072]                 ; 4-byte Folded Spill
	fmsub	s10, s0, s3, s4
	fmul	s3, s1, s10
	fmadd	s3, s2, s11, s3
	ldr	s4, [sp, #4676]
	ldr	s5, [sp, #4676]
	str	s5, [sp, #1064]                 ; 4-byte Folded Spill
	fmsub	s9, s0, s3, s4
	fmul	s3, s1, s9
	fmadd	s3, s2, s10, s3
	ldr	s4, [sp, #4680]
	ldr	s5, [sp, #4680]
	str	s5, [sp, #1060]                 ; 4-byte Folded Spill
	fmsub	s8, s0, s3, s4
	fmul	s3, s1, s8
	fmadd	s3, s2, s9, s3
	ldr	s4, [sp, #4684]
	ldr	s5, [sp, #4684]
	str	s5, [sp, #1056]                 ; 4-byte Folded Spill
	fmsub	s31, s0, s3, s4
	fmul	s3, s1, s31
	fmadd	s3, s2, s8, s3
	ldr	s4, [sp, #4688]
	ldr	s5, [sp, #4688]
	str	s5, [sp, #1052]                 ; 4-byte Folded Spill
	fmsub	s30, s0, s3, s4
	fmul	s3, s1, s30
	fmadd	s3, s2, s31, s3
	ldr	s4, [sp, #4692]
	ldr	s5, [sp, #4692]
	str	s5, [sp, #1044]                 ; 4-byte Folded Spill
	fmsub	s29, s0, s3, s4
	fmul	s3, s1, s29
	fmadd	s3, s2, s30, s3
	ldr	s4, [sp, #4696]
	ldr	s5, [sp, #4696]
	str	s5, [sp, #1040]                 ; 4-byte Folded Spill
	fmsub	s28, s0, s3, s4
	fmul	s3, s1, s28
	fmadd	s3, s2, s29, s3
	ldr	s4, [sp, #4700]
	ldr	s5, [sp, #4700]
	str	s5, [sp, #1032]                 ; 4-byte Folded Spill
	fmsub	s27, s0, s3, s4
	fmul	s3, s1, s27
	fmadd	s3, s2, s28, s3
	ldr	s4, [sp, #4704]
	ldr	s5, [sp, #4704]
	str	s5, [sp, #1028]                 ; 4-byte Folded Spill
	fmsub	s26, s0, s3, s4
	fmul	s3, s1, s26
	fmadd	s3, s2, s27, s3
	ldr	s4, [sp, #4708]
	ldr	s5, [sp, #4708]
	str	s5, [sp, #1020]                 ; 4-byte Folded Spill
	fmsub	s25, s0, s3, s4
	fmul	s3, s1, s25
	fmadd	s3, s2, s26, s3
	ldr	s4, [sp, #4712]
	ldr	s5, [sp, #4712]
	str	s5, [sp, #1016]                 ; 4-byte Folded Spill
	fmsub	s24, s0, s3, s4
	fmul	s3, s1, s24
	fmadd	s3, s2, s25, s3
	ldr	s4, [sp, #4716]
	ldr	s5, [sp, #4716]
	str	s5, [sp, #1008]                 ; 4-byte Folded Spill
	fmsub	s23, s0, s3, s4
	fmul	s3, s1, s23
	fmadd	s3, s2, s24, s3
	ldr	s4, [sp, #4720]
	ldr	s5, [sp, #4720]
	str	s5, [sp, #1004]                 ; 4-byte Folded Spill
	fmsub	s21, s0, s3, s4
	fmul	s3, s1, s21
	fmadd	s3, s2, s23, s3
	ldr	s4, [sp, #4724]
	ldr	s5, [sp, #4724]
	str	s5, [sp, #996]                  ; 4-byte Folded Spill
	fmsub	s22, s0, s3, s4
	fmul	s3, s1, s22
	fmadd	s3, s2, s21, s3
	ldr	s4, [sp, #4728]
	ldr	s5, [sp, #4728]
	str	s5, [sp, #992]                  ; 4-byte Folded Spill
	fmsub	s20, s0, s3, s4
	fmul	s3, s1, s20
	fmadd	s3, s2, s22, s3
	ldr	s4, [sp, #4732]
	ldr	s5, [sp, #4732]
	str	s5, [sp, #984]                  ; 4-byte Folded Spill
	fmsub	s19, s0, s3, s4
	fmul	s3, s1, s19
	fmadd	s3, s2, s20, s3
	ldr	s4, [sp, #4736]
	ldr	s5, [sp, #4736]
	str	s5, [sp, #980]                  ; 4-byte Folded Spill
	fmsub	s18, s0, s3, s4
	fmul	s3, s1, s18
	fmadd	s3, s2, s19, s3
	ldr	s4, [sp, #4740]
	ldr	s5, [sp, #4740]
	str	s5, [sp, #976]                  ; 4-byte Folded Spill
	fmsub	s17, s0, s3, s4
	fmul	s3, s1, s17
	fmadd	s3, s2, s18, s3
	ldr	s4, [sp, #4744]
	ldr	s5, [sp, #4744]
	str	s5, [sp, #968]                  ; 4-byte Folded Spill
	fmsub	s16, s0, s3, s4
	fmul	s3, s1, s16
	fmadd	s3, s2, s17, s3
	ldr	s4, [sp, #4748]
	ldr	s5, [sp, #4748]
	str	s5, [sp, #960]                  ; 4-byte Folded Spill
	fmsub	s7, s0, s3, s4
	fmul	s3, s1, s7
	fmadd	s3, s2, s16, s3
	ldr	s4, [sp, #4752]
	ldr	s5, [sp, #4752]
	str	s5, [sp, #956]                  ; 4-byte Folded Spill
	fmsub	s6, s0, s3, s4
	fmul	s3, s1, s6
	fmadd	s4, s2, s7, s3
	ldr	s3, [sp, #4756]
	ldr	s5, [sp, #4756]
	str	s5, [sp, #952]                  ; 4-byte Folded Spill
	fmsub	s5, s0, s4, s3
	fmul	s4, s1, s5
	fmadd	s4, s2, s6, s4
	ldr	s3, [sp, #4760]
	ldr	s15, [sp, #4760]
	str	s15, [sp, #944]                 ; 4-byte Folded Spill
	fmsub	s4, s0, s4, s3
	fmul	s1, s1, s4
	fmadd	s1, s2, s5, s1
	ldr	s2, [sp, #4764]
	ldr	s3, [sp, #4764]
	str	s3, [sp, #964]                  ; 4-byte Folded Spill
	fmsub	s15, s0, s1, s2
	ldr	s0, [sp, #2588]                 ; 4-byte Folded Reload
	add	x9, sp, #1816
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2576]                 ; 4-byte Folded Reload
	add	x9, sp, #1820
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2572]                 ; 4-byte Folded Reload
	add	x9, sp, #1824
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2560]                 ; 4-byte Folded Reload
	add	x9, sp, #1828
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2556]                 ; 4-byte Folded Reload
	add	x9, sp, #1832
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2544]                 ; 4-byte Folded Reload
	add	x9, sp, #1836
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2536]                 ; 4-byte Folded Reload
	add	x9, sp, #1840
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2532]                 ; 4-byte Folded Reload
	add	x9, sp, #1844
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2520]                 ; 4-byte Folded Reload
	add	x9, sp, #1848
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2516]                 ; 4-byte Folded Reload
	add	x9, sp, #1852
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2504]                 ; 4-byte Folded Reload
	add	x9, sp, #1856
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2500]                 ; 4-byte Folded Reload
	add	x9, sp, #1860
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2488]                 ; 4-byte Folded Reload
	add	x9, sp, #1864
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2480]                 ; 4-byte Folded Reload
	add	x9, sp, #1868
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2476]                 ; 4-byte Folded Reload
	add	x9, sp, #1872
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2472]                 ; 4-byte Folded Reload
	add	x9, sp, #1876
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2460]                 ; 4-byte Folded Reload
	add	x9, sp, #1880
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2468]                 ; 4-byte Folded Reload
	add	x9, sp, #1884
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2464]                 ; 4-byte Folded Reload
	add	x9, sp, #1888
	str	s0, [x9, #16380]
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #1744
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2968]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	s0, [sp, #2456]                 ; 4-byte Folded Reload
	add	x9, sp, #628
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2452]                 ; 4-byte Folded Reload
	add	x9, sp, #632
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2448]                 ; 4-byte Folded Reload
	add	x9, sp, #636
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2444]                 ; 4-byte Folded Reload
	add	x9, sp, #640
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2440]                 ; 4-byte Folded Reload
	add	x9, sp, #644
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2436]                 ; 4-byte Folded Reload
	add	x9, sp, #648
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2432]                 ; 4-byte Folded Reload
	add	x9, sp, #652
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2428]                 ; 4-byte Folded Reload
	add	x9, sp, #656
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2424]                 ; 4-byte Folded Reload
	add	x9, sp, #660
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2420]                 ; 4-byte Folded Reload
	add	x9, sp, #664
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2416]                 ; 4-byte Folded Reload
	add	x9, sp, #668
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2412]                 ; 4-byte Folded Reload
	add	x9, sp, #672
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2408]                 ; 4-byte Folded Reload
	add	x9, sp, #676
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2404]                 ; 4-byte Folded Reload
	add	x9, sp, #680
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2400]                 ; 4-byte Folded Reload
	add	x9, sp, #684
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2396]                 ; 4-byte Folded Reload
	add	x9, sp, #688
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2392]                 ; 4-byte Folded Reload
	add	x9, sp, #692
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2388]                 ; 4-byte Folded Reload
	add	x9, sp, #696
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2384]                 ; 4-byte Folded Reload
	add	x9, sp, #700
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2380]                 ; 4-byte Folded Reload
	add	x9, sp, #704
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2376]                 ; 4-byte Folded Reload
	add	x9, sp, #708
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2372]                 ; 4-byte Folded Reload
	add	x9, sp, #712
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2368]                 ; 4-byte Folded Reload
	add	x9, sp, #716
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2364]                 ; 4-byte Folded Reload
	add	x9, sp, #720
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2360]                 ; 4-byte Folded Reload
	add	x9, sp, #724
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2356]                 ; 4-byte Folded Reload
	add	x9, sp, #728
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2352]                 ; 4-byte Folded Reload
	add	x9, sp, #732
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2348]                 ; 4-byte Folded Reload
	add	x9, sp, #736
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2344]                 ; 4-byte Folded Reload
	add	x9, sp, #740
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2332]                 ; 4-byte Folded Reload
	add	x9, sp, #744
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2340]                 ; 4-byte Folded Reload
	add	x9, sp, #748
	str	s0, [x9, #16380]
	ldr	s0, [sp, #2336]                 ; 4-byte Folded Reload
	add	x9, sp, #752
	str	s0, [x9, #16380]
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #608
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2960]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	s0, [sp, #2328]                 ; 4-byte Folded Reload
	str	s0, [sp, #15872]
	ldr	s0, [sp, #2324]                 ; 4-byte Folded Reload
	str	s0, [sp, #15876]
	ldr	s0, [sp, #2320]                 ; 4-byte Folded Reload
	str	s0, [sp, #15880]
	ldr	s0, [sp, #2316]                 ; 4-byte Folded Reload
	str	s0, [sp, #15884]
	ldr	s0, [sp, #2312]                 ; 4-byte Folded Reload
	str	s0, [sp, #15888]
	ldr	s0, [sp, #2308]                 ; 4-byte Folded Reload
	str	s0, [sp, #15892]
	ldr	s0, [sp, #2304]                 ; 4-byte Folded Reload
	str	s0, [sp, #15896]
	ldr	s0, [sp, #2300]                 ; 4-byte Folded Reload
	str	s0, [sp, #15900]
	ldr	s0, [sp, #2296]                 ; 4-byte Folded Reload
	str	s0, [sp, #15904]
	ldr	s0, [sp, #2292]                 ; 4-byte Folded Reload
	str	s0, [sp, #15908]
	ldr	s0, [sp, #2288]                 ; 4-byte Folded Reload
	str	s0, [sp, #15912]
	ldr	s0, [sp, #2284]                 ; 4-byte Folded Reload
	str	s0, [sp, #15916]
	ldr	s0, [sp, #2280]                 ; 4-byte Folded Reload
	str	s0, [sp, #15920]
	ldr	s0, [sp, #2276]                 ; 4-byte Folded Reload
	str	s0, [sp, #15924]
	ldr	s0, [sp, #2272]                 ; 4-byte Folded Reload
	str	s0, [sp, #15928]
	ldr	s0, [sp, #2268]                 ; 4-byte Folded Reload
	str	s0, [sp, #15932]
	ldr	s0, [sp, #2264]                 ; 4-byte Folded Reload
	str	s0, [sp, #15936]
	ldr	s0, [sp, #2260]                 ; 4-byte Folded Reload
	str	s0, [sp, #15940]
	ldr	s0, [sp, #2256]                 ; 4-byte Folded Reload
	str	s0, [sp, #15944]
	ldr	s0, [sp, #2252]                 ; 4-byte Folded Reload
	str	s0, [sp, #15948]
	ldr	s0, [sp, #2248]                 ; 4-byte Folded Reload
	str	s0, [sp, #15952]
	ldr	s0, [sp, #2244]                 ; 4-byte Folded Reload
	str	s0, [sp, #15956]
	ldr	s0, [sp, #2240]                 ; 4-byte Folded Reload
	str	s0, [sp, #15960]
	ldr	s0, [sp, #2236]                 ; 4-byte Folded Reload
	str	s0, [sp, #15964]
	ldr	s0, [sp, #2232]                 ; 4-byte Folded Reload
	str	s0, [sp, #15968]
	ldr	s0, [sp, #2228]                 ; 4-byte Folded Reload
	str	s0, [sp, #15972]
	ldr	s0, [sp, #2224]                 ; 4-byte Folded Reload
	str	s0, [sp, #15976]
	ldr	s0, [sp, #2220]                 ; 4-byte Folded Reload
	str	s0, [sp, #15980]
	ldr	s0, [sp, #2216]                 ; 4-byte Folded Reload
	str	s0, [sp, #15984]
	ldr	s0, [sp, #2204]                 ; 4-byte Folded Reload
	str	s0, [sp, #15988]
	ldr	s0, [sp, #2212]                 ; 4-byte Folded Reload
	str	s0, [sp, #15992]
	ldr	s0, [sp, #2208]                 ; 4-byte Folded Reload
	str	s0, [sp, #15996]
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3568
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2952]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	s0, [sp, #2200]                 ; 4-byte Folded Reload
	str	s0, [sp, #14736]
	ldr	s0, [sp, #2196]                 ; 4-byte Folded Reload
	str	s0, [sp, #14740]
	ldr	s0, [sp, #2192]                 ; 4-byte Folded Reload
	str	s0, [sp, #14744]
	ldr	s0, [sp, #2188]                 ; 4-byte Folded Reload
	str	s0, [sp, #14748]
	ldr	s0, [sp, #2184]                 ; 4-byte Folded Reload
	str	s0, [sp, #14752]
	ldr	s0, [sp, #2180]                 ; 4-byte Folded Reload
	str	s0, [sp, #14756]
	ldr	s0, [sp, #2176]                 ; 4-byte Folded Reload
	str	s0, [sp, #14760]
	ldr	s0, [sp, #2172]                 ; 4-byte Folded Reload
	str	s0, [sp, #14764]
	ldr	s0, [sp, #2168]                 ; 4-byte Folded Reload
	str	s0, [sp, #14768]
	ldr	s0, [sp, #2164]                 ; 4-byte Folded Reload
	str	s0, [sp, #14772]
	ldr	s0, [sp, #2160]                 ; 4-byte Folded Reload
	str	s0, [sp, #14776]
	ldr	s0, [sp, #2156]                 ; 4-byte Folded Reload
	str	s0, [sp, #14780]
	ldr	s0, [sp, #2152]                 ; 4-byte Folded Reload
	str	s0, [sp, #14784]
	ldr	s0, [sp, #2148]                 ; 4-byte Folded Reload
	str	s0, [sp, #14788]
	ldr	s0, [sp, #2144]                 ; 4-byte Folded Reload
	str	s0, [sp, #14792]
	ldr	s0, [sp, #2140]                 ; 4-byte Folded Reload
	str	s0, [sp, #14796]
	ldr	s0, [sp, #2136]                 ; 4-byte Folded Reload
	str	s0, [sp, #14800]
	ldr	s0, [sp, #2132]                 ; 4-byte Folded Reload
	str	s0, [sp, #14804]
	ldr	s0, [sp, #2128]                 ; 4-byte Folded Reload
	str	s0, [sp, #14808]
	ldr	s0, [sp, #2124]                 ; 4-byte Folded Reload
	str	s0, [sp, #14812]
	ldr	s0, [sp, #2120]                 ; 4-byte Folded Reload
	str	s0, [sp, #14816]
	ldr	s0, [sp, #2116]                 ; 4-byte Folded Reload
	str	s0, [sp, #14820]
	ldr	s0, [sp, #2112]                 ; 4-byte Folded Reload
	str	s0, [sp, #14824]
	ldr	s0, [sp, #2108]                 ; 4-byte Folded Reload
	str	s0, [sp, #14828]
	ldr	s0, [sp, #2104]                 ; 4-byte Folded Reload
	str	s0, [sp, #14832]
	ldr	s0, [sp, #2100]                 ; 4-byte Folded Reload
	str	s0, [sp, #14836]
	ldr	s0, [sp, #2096]                 ; 4-byte Folded Reload
	str	s0, [sp, #14840]
	ldr	s0, [sp, #2092]                 ; 4-byte Folded Reload
	str	s0, [sp, #14844]
	ldr	s0, [sp, #2088]                 ; 4-byte Folded Reload
	str	s0, [sp, #14848]
	ldr	s0, [sp, #2076]                 ; 4-byte Folded Reload
	str	s0, [sp, #14852]
	ldr	s0, [sp, #2084]                 ; 4-byte Folded Reload
	str	s0, [sp, #14856]
	ldr	s0, [sp, #2080]                 ; 4-byte Folded Reload
	str	s0, [sp, #14860]
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2432
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2944]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	s0, [sp, #2072]                 ; 4-byte Folded Reload
	str	s0, [sp, #13600]
	ldr	s0, [sp, #2068]                 ; 4-byte Folded Reload
	str	s0, [sp, #13604]
	ldr	s0, [sp, #2064]                 ; 4-byte Folded Reload
	str	s0, [sp, #13608]
	ldr	s0, [sp, #2060]                 ; 4-byte Folded Reload
	str	s0, [sp, #13612]
	ldr	s0, [sp, #2056]                 ; 4-byte Folded Reload
	str	s0, [sp, #13616]
	ldr	s0, [sp, #2052]                 ; 4-byte Folded Reload
	str	s0, [sp, #13620]
	ldr	s0, [sp, #2048]                 ; 4-byte Folded Reload
	str	s0, [sp, #13624]
	ldr	s0, [sp, #2044]                 ; 4-byte Folded Reload
	str	s0, [sp, #13628]
	ldr	s0, [sp, #2040]                 ; 4-byte Folded Reload
	str	s0, [sp, #13632]
	ldr	s0, [sp, #2036]                 ; 4-byte Folded Reload
	str	s0, [sp, #13636]
	ldr	s0, [sp, #2032]                 ; 4-byte Folded Reload
	str	s0, [sp, #13640]
	ldr	s0, [sp, #2028]                 ; 4-byte Folded Reload
	str	s0, [sp, #13644]
	ldr	s0, [sp, #2024]                 ; 4-byte Folded Reload
	str	s0, [sp, #13648]
	ldr	s0, [sp, #2020]                 ; 4-byte Folded Reload
	str	s0, [sp, #13652]
	ldr	s0, [sp, #2016]                 ; 4-byte Folded Reload
	str	s0, [sp, #13656]
	ldr	s0, [sp, #2012]                 ; 4-byte Folded Reload
	str	s0, [sp, #13660]
	ldr	s0, [sp, #2008]                 ; 4-byte Folded Reload
	str	s0, [sp, #13664]
	ldr	s0, [sp, #2004]                 ; 4-byte Folded Reload
	str	s0, [sp, #13668]
	ldr	s0, [sp, #2000]                 ; 4-byte Folded Reload
	str	s0, [sp, #13672]
	ldr	s0, [sp, #1996]                 ; 4-byte Folded Reload
	str	s0, [sp, #13676]
	ldr	s0, [sp, #1992]                 ; 4-byte Folded Reload
	str	s0, [sp, #13680]
	ldr	s0, [sp, #1988]                 ; 4-byte Folded Reload
	str	s0, [sp, #13684]
	ldr	s0, [sp, #1984]                 ; 4-byte Folded Reload
	str	s0, [sp, #13688]
	ldr	s0, [sp, #1980]                 ; 4-byte Folded Reload
	str	s0, [sp, #13692]
	ldr	s0, [sp, #1976]                 ; 4-byte Folded Reload
	str	s0, [sp, #13696]
	ldr	s0, [sp, #1972]                 ; 4-byte Folded Reload
	str	s0, [sp, #13700]
	ldr	s0, [sp, #1968]                 ; 4-byte Folded Reload
	str	s0, [sp, #13704]
	ldr	s0, [sp, #1964]                 ; 4-byte Folded Reload
	str	s0, [sp, #13708]
	ldr	s0, [sp, #1960]                 ; 4-byte Folded Reload
	str	s0, [sp, #13712]
	ldr	s0, [sp, #1948]                 ; 4-byte Folded Reload
	str	s0, [sp, #13716]
	ldr	s0, [sp, #1956]                 ; 4-byte Folded Reload
	str	s0, [sp, #13720]
	ldr	s0, [sp, #1952]                 ; 4-byte Folded Reload
	str	s0, [sp, #13724]
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1296
	ldur	q0, [x9, #128]
	str	q0, [x23]
	ldr	s0, [sp, #1944]                 ; 4-byte Folded Reload
	str	s0, [sp, #12464]
	ldr	s0, [sp, #1940]                 ; 4-byte Folded Reload
	str	s0, [sp, #12468]
	ldr	s0, [sp, #1936]                 ; 4-byte Folded Reload
	str	s0, [sp, #12472]
	ldr	s0, [sp, #1932]                 ; 4-byte Folded Reload
	str	s0, [sp, #12476]
	ldr	s0, [sp, #1928]                 ; 4-byte Folded Reload
	str	s0, [sp, #12480]
	ldr	s0, [sp, #1924]                 ; 4-byte Folded Reload
	str	s0, [sp, #12484]
	ldr	s0, [sp, #1920]                 ; 4-byte Folded Reload
	str	s0, [sp, #12488]
	ldr	s0, [sp, #1916]                 ; 4-byte Folded Reload
	str	s0, [sp, #12492]
	ldr	s0, [sp, #1912]                 ; 4-byte Folded Reload
	str	s0, [sp, #12496]
	ldr	s0, [sp, #1908]                 ; 4-byte Folded Reload
	str	s0, [sp, #12500]
	ldr	s0, [sp, #1904]                 ; 4-byte Folded Reload
	str	s0, [sp, #12504]
	ldr	s0, [sp, #1900]                 ; 4-byte Folded Reload
	str	s0, [sp, #12508]
	ldr	s0, [sp, #1896]                 ; 4-byte Folded Reload
	str	s0, [sp, #12512]
	ldr	s0, [sp, #1892]                 ; 4-byte Folded Reload
	str	s0, [sp, #12516]
	ldr	s0, [sp, #1888]                 ; 4-byte Folded Reload
	str	s0, [sp, #12520]
	ldr	s0, [sp, #1884]                 ; 4-byte Folded Reload
	str	s0, [sp, #12524]
	ldr	s0, [sp, #1880]                 ; 4-byte Folded Reload
	str	s0, [sp, #12528]
	ldr	s0, [sp, #1876]                 ; 4-byte Folded Reload
	str	s0, [sp, #12532]
	ldr	s0, [sp, #1872]                 ; 4-byte Folded Reload
	str	s0, [sp, #12536]
	ldr	s0, [sp, #1868]                 ; 4-byte Folded Reload
	str	s0, [sp, #12540]
	ldr	s0, [sp, #1864]                 ; 4-byte Folded Reload
	str	s0, [sp, #12544]
	ldr	s0, [sp, #1860]                 ; 4-byte Folded Reload
	str	s0, [sp, #12548]
	ldr	s0, [sp, #1856]                 ; 4-byte Folded Reload
	str	s0, [sp, #12552]
	ldr	s0, [sp, #1852]                 ; 4-byte Folded Reload
	str	s0, [sp, #12556]
	ldr	s0, [sp, #1848]                 ; 4-byte Folded Reload
	str	s0, [sp, #12560]
	ldr	s0, [sp, #1844]                 ; 4-byte Folded Reload
	str	s0, [sp, #12564]
	ldr	s0, [sp, #1840]                 ; 4-byte Folded Reload
	str	s0, [sp, #12568]
	ldr	s0, [sp, #1836]                 ; 4-byte Folded Reload
	str	s0, [sp, #12572]
	ldr	s0, [sp, #1832]                 ; 4-byte Folded Reload
	str	s0, [sp, #12576]
	ldr	s0, [sp, #1820]                 ; 4-byte Folded Reload
	str	s0, [sp, #12580]
	ldr	s0, [sp, #1828]                 ; 4-byte Folded Reload
	str	s0, [sp, #12584]
	ldr	s0, [sp, #1824]                 ; 4-byte Folded Reload
	str	s0, [sp, #12588]
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #160
	ldur	q0, [x9, #128]
	str	q0, [x20]
	ldr	s0, [sp, #1816]                 ; 4-byte Folded Reload
	str	s0, [sp, #11328]
	ldr	s0, [sp, #1812]                 ; 4-byte Folded Reload
	str	s0, [sp, #11332]
	ldr	s0, [sp, #1808]                 ; 4-byte Folded Reload
	str	s0, [sp, #11336]
	ldr	s0, [sp, #1804]                 ; 4-byte Folded Reload
	str	s0, [sp, #11340]
	ldr	s0, [sp, #1800]                 ; 4-byte Folded Reload
	str	s0, [sp, #11344]
	ldr	s0, [sp, #1796]                 ; 4-byte Folded Reload
	str	s0, [sp, #11348]
	ldr	s0, [sp, #1792]                 ; 4-byte Folded Reload
	str	s0, [sp, #11352]
	ldr	s0, [sp, #1788]                 ; 4-byte Folded Reload
	str	s0, [sp, #11356]
	ldr	s0, [sp, #1784]                 ; 4-byte Folded Reload
	str	s0, [sp, #11360]
	ldr	s0, [sp, #1780]                 ; 4-byte Folded Reload
	str	s0, [sp, #11364]
	ldr	s0, [sp, #1776]                 ; 4-byte Folded Reload
	str	s0, [sp, #11368]
	ldr	s0, [sp, #1772]                 ; 4-byte Folded Reload
	str	s0, [sp, #11372]
	ldr	s0, [sp, #1768]                 ; 4-byte Folded Reload
	str	s0, [sp, #11376]
	ldr	s0, [sp, #1764]                 ; 4-byte Folded Reload
	str	s0, [sp, #11380]
	ldr	s0, [sp, #1760]                 ; 4-byte Folded Reload
	str	s0, [sp, #11384]
	ldr	s0, [sp, #1756]                 ; 4-byte Folded Reload
	str	s0, [sp, #11388]
	ldr	s0, [sp, #1752]                 ; 4-byte Folded Reload
	str	s0, [sp, #11392]
	ldr	s0, [sp, #1748]                 ; 4-byte Folded Reload
	str	s0, [sp, #11396]
	ldr	s0, [sp, #1744]                 ; 4-byte Folded Reload
	str	s0, [sp, #11400]
	ldr	s0, [sp, #1740]                 ; 4-byte Folded Reload
	str	s0, [sp, #11404]
	ldr	s0, [sp, #1736]                 ; 4-byte Folded Reload
	str	s0, [sp, #11408]
	ldr	s0, [sp, #1732]                 ; 4-byte Folded Reload
	str	s0, [sp, #11412]
	ldr	s0, [sp, #1728]                 ; 4-byte Folded Reload
	str	s0, [sp, #11416]
	ldr	s0, [sp, #1724]                 ; 4-byte Folded Reload
	str	s0, [sp, #11420]
	ldr	s0, [sp, #1720]                 ; 4-byte Folded Reload
	str	s0, [sp, #11424]
	ldr	s0, [sp, #1716]                 ; 4-byte Folded Reload
	str	s0, [sp, #11428]
	ldr	s0, [sp, #1712]                 ; 4-byte Folded Reload
	str	s0, [sp, #11432]
	ldr	s0, [sp, #1708]                 ; 4-byte Folded Reload
	str	s0, [sp, #11436]
	ldr	s0, [sp, #1704]                 ; 4-byte Folded Reload
	str	s0, [sp, #11440]
	ldr	s0, [sp, #1692]                 ; 4-byte Folded Reload
	str	s0, [sp, #11444]
	ldr	s0, [sp, #1700]                 ; 4-byte Folded Reload
	str	s0, [sp, #11448]
	ldr	s0, [sp, #1696]                 ; 4-byte Folded Reload
	str	s0, [sp, #11452]
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3120
	ldur	q0, [x9, #128]
	str	q0, [x25]
	ldr	s0, [sp, #2592]                 ; 4-byte Folded Reload
	str	s0, [sp, #10192]
	ldr	s0, [sp, #1688]                 ; 4-byte Folded Reload
	str	s0, [sp, #10196]
	ldr	s0, [sp, #1684]                 ; 4-byte Folded Reload
	str	s0, [sp, #10200]
	ldr	s0, [sp, #1680]                 ; 4-byte Folded Reload
	str	s0, [sp, #10204]
	ldr	s0, [sp, #1676]                 ; 4-byte Folded Reload
	str	s0, [sp, #10208]
	ldr	s0, [sp, #1672]                 ; 4-byte Folded Reload
	str	s0, [sp, #10212]
	ldr	s0, [sp, #1668]                 ; 4-byte Folded Reload
	str	s0, [sp, #10216]
	ldr	s0, [sp, #1664]                 ; 4-byte Folded Reload
	str	s0, [sp, #10224]
	ldr	s0, [sp, #1660]                 ; 4-byte Folded Reload
	str	s0, [sp, #10228]
	ldr	s0, [sp, #1656]                 ; 4-byte Folded Reload
	str	s0, [sp, #10232]
	ldr	s0, [sp, #1652]                 ; 4-byte Folded Reload
	str	s0, [sp, #10236]
	ldr	s0, [sp, #1648]                 ; 4-byte Folded Reload
	str	s0, [sp, #10240]
	ldr	s0, [sp, #1644]                 ; 4-byte Folded Reload
	str	s0, [sp, #10244]
	ldr	s0, [sp, #1640]                 ; 4-byte Folded Reload
	str	s0, [sp, #10248]
	ldr	s0, [sp, #1636]                 ; 4-byte Folded Reload
	str	s0, [sp, #10252]
	ldr	s0, [sp, #1632]                 ; 4-byte Folded Reload
	str	s0, [sp, #10256]
	ldr	s0, [sp, #1628]                 ; 4-byte Folded Reload
	str	s0, [sp, #10260]
	ldr	s0, [sp, #1624]                 ; 4-byte Folded Reload
	str	s0, [sp, #10264]
	ldr	s0, [sp, #1620]                 ; 4-byte Folded Reload
	str	s0, [sp, #10268]
	ldr	s0, [sp, #1616]                 ; 4-byte Folded Reload
	str	s0, [sp, #10272]
	ldr	s0, [sp, #1612]                 ; 4-byte Folded Reload
	str	s0, [sp, #10276]
	ldr	s0, [sp, #1608]                 ; 4-byte Folded Reload
	str	s0, [sp, #10280]
	ldr	s0, [sp, #1604]                 ; 4-byte Folded Reload
	str	s0, [sp, #10284]
	ldr	s0, [sp, #1600]                 ; 4-byte Folded Reload
	str	s0, [sp, #10288]
	ldr	s0, [sp, #1596]                 ; 4-byte Folded Reload
	str	s0, [sp, #10292]
	ldr	s0, [sp, #1592]                 ; 4-byte Folded Reload
	str	s0, [sp, #10296]
	ldr	s0, [sp, #1588]                 ; 4-byte Folded Reload
	str	s0, [sp, #10300]
	ldr	s0, [sp, #1584]                 ; 4-byte Folded Reload
	str	s0, [sp, #10304]
	ldr	s0, [sp, #1572]                 ; 4-byte Folded Reload
	str	s0, [sp, #10308]
	ldr	s0, [sp, #1580]                 ; 4-byte Folded Reload
	str	s0, [sp, #10312]
	ldr	s0, [sp, #1576]                 ; 4-byte Folded Reload
	str	s0, [sp, #10316]
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1984
	ldur	q0, [x9, #128]
	str	q0, [x21]
	ldr	s0, [sp, #1568]                 ; 4-byte Folded Reload
	str	s0, [sp, #9056]
	ldr	s0, [sp, #1564]                 ; 4-byte Folded Reload
	str	s0, [sp, #9060]
	ldr	s0, [sp, #1560]                 ; 4-byte Folded Reload
	str	s0, [sp, #9064]
	ldr	s0, [sp, #1556]                 ; 4-byte Folded Reload
	str	s0, [sp, #9068]
	ldr	s0, [sp, #1552]                 ; 4-byte Folded Reload
	str	s0, [sp, #9072]
	ldr	s0, [sp, #1548]                 ; 4-byte Folded Reload
	str	s0, [sp, #9076]
	ldr	s0, [sp, #1544]                 ; 4-byte Folded Reload
	str	s0, [sp, #9080]
	ldr	s0, [sp, #1540]                 ; 4-byte Folded Reload
	str	s0, [sp, #9084]
	ldr	s0, [sp, #1536]                 ; 4-byte Folded Reload
	str	s0, [sp, #9088]
	ldr	s0, [sp, #1532]                 ; 4-byte Folded Reload
	str	s0, [sp, #9092]
	ldr	s0, [sp, #1528]                 ; 4-byte Folded Reload
	str	s0, [sp, #9096]
	ldr	s0, [sp, #1524]                 ; 4-byte Folded Reload
	str	s0, [sp, #9100]
	ldr	s0, [sp, #1520]                 ; 4-byte Folded Reload
	str	s0, [sp, #9104]
	ldr	s0, [sp, #1516]                 ; 4-byte Folded Reload
	str	s0, [sp, #9108]
	ldr	s0, [sp, #1512]                 ; 4-byte Folded Reload
	str	s0, [sp, #9112]
	ldr	s0, [sp, #1508]                 ; 4-byte Folded Reload
	str	s0, [sp, #9116]
	ldr	s0, [sp, #1504]                 ; 4-byte Folded Reload
	str	s0, [sp, #9120]
	ldr	s0, [sp, #1500]                 ; 4-byte Folded Reload
	str	s0, [sp, #9124]
	ldr	s0, [sp, #1496]                 ; 4-byte Folded Reload
	str	s0, [sp, #9128]
	ldr	s0, [sp, #1492]                 ; 4-byte Folded Reload
	str	s0, [sp, #9132]
	ldr	s0, [sp, #1488]                 ; 4-byte Folded Reload
	str	s0, [sp, #9136]
	ldr	s0, [sp, #1484]                 ; 4-byte Folded Reload
	str	s0, [sp, #9140]
	ldr	s0, [sp, #1480]                 ; 4-byte Folded Reload
	str	s0, [sp, #9144]
	ldr	s0, [sp, #1476]                 ; 4-byte Folded Reload
	str	s0, [sp, #9148]
	ldr	s0, [sp, #1472]                 ; 4-byte Folded Reload
	str	s0, [sp, #9152]
	ldr	s0, [sp, #1468]                 ; 4-byte Folded Reload
	str	s0, [sp, #9156]
	ldr	s0, [sp, #1464]                 ; 4-byte Folded Reload
	str	s0, [sp, #9160]
	ldr	s0, [sp, #1460]                 ; 4-byte Folded Reload
	str	s0, [sp, #9164]
	ldr	s0, [sp, #1456]                 ; 4-byte Folded Reload
	str	s0, [sp, #9168]
	ldr	s0, [sp, #1444]                 ; 4-byte Folded Reload
	str	s0, [sp, #9172]
	ldr	s0, [sp, #1452]                 ; 4-byte Folded Reload
	str	s0, [sp, #9176]
	ldr	s0, [sp, #1448]                 ; 4-byte Folded Reload
	str	s0, [sp, #9180]
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #848
	ldur	q0, [x9, #128]
	str	q0, [x24]
	ldr	s0, [sp, #1440]                 ; 4-byte Folded Reload
	str	s0, [sp, #7920]
	ldr	s0, [sp, #1436]                 ; 4-byte Folded Reload
	str	s0, [sp, #7924]
	ldr	s0, [sp, #1432]                 ; 4-byte Folded Reload
	str	s0, [sp, #7928]
	ldr	s0, [sp, #1428]                 ; 4-byte Folded Reload
	str	s0, [sp, #7932]
	ldr	s0, [sp, #1424]                 ; 4-byte Folded Reload
	str	s0, [sp, #7936]
	ldr	s0, [sp, #1420]                 ; 4-byte Folded Reload
	str	s0, [sp, #7940]
	ldr	s0, [sp, #1416]                 ; 4-byte Folded Reload
	str	s0, [sp, #7944]
	ldr	s0, [sp, #1412]                 ; 4-byte Folded Reload
	str	s0, [sp, #7948]
	ldr	s0, [sp, #1408]                 ; 4-byte Folded Reload
	str	s0, [sp, #7952]
	ldr	s0, [sp, #1404]                 ; 4-byte Folded Reload
	str	s0, [sp, #7956]
	ldr	s0, [sp, #1400]                 ; 4-byte Folded Reload
	str	s0, [sp, #7960]
	ldr	s0, [sp, #1396]                 ; 4-byte Folded Reload
	str	s0, [sp, #7964]
	ldr	s0, [sp, #1392]                 ; 4-byte Folded Reload
	str	s0, [sp, #7968]
	ldr	s0, [sp, #1388]                 ; 4-byte Folded Reload
	str	s0, [sp, #7972]
	ldr	s0, [sp, #1384]                 ; 4-byte Folded Reload
	str	s0, [sp, #7976]
	ldr	s0, [sp, #1380]                 ; 4-byte Folded Reload
	str	s0, [sp, #7980]
	ldr	s0, [sp, #1376]                 ; 4-byte Folded Reload
	str	s0, [sp, #7984]
	ldr	s0, [sp, #1372]                 ; 4-byte Folded Reload
	str	s0, [sp, #7988]
	ldr	s0, [sp, #1368]                 ; 4-byte Folded Reload
	str	s0, [sp, #7992]
	ldr	s0, [sp, #1364]                 ; 4-byte Folded Reload
	str	s0, [sp, #7996]
	ldr	s0, [sp, #1320]                 ; 4-byte Folded Reload
	str	s0, [sp, #8032]
	ldr	s0, [sp, #1316]                 ; 4-byte Folded Reload
	str	s0, [sp, #8036]
	ldr	s0, [sp, #1360]                 ; 4-byte Folded Reload
	str	s0, [sp, #8000]
	ldr	s0, [sp, #1356]                 ; 4-byte Folded Reload
	str	s0, [sp, #8004]
	ldr	s0, [sp, #1352]                 ; 4-byte Folded Reload
	str	s0, [sp, #8008]
	ldr	s0, [sp, #1348]                 ; 4-byte Folded Reload
	str	s0, [sp, #8012]
	ldr	s0, [sp, #1344]                 ; 4-byte Folded Reload
	str	s0, [sp, #8016]
	ldr	s0, [sp, #1340]                 ; 4-byte Folded Reload
	str	s0, [sp, #8020]
	ldr	s0, [sp, #1336]                 ; 4-byte Folded Reload
	str	s0, [sp, #8024]
	ldr	s0, [sp, #1332]                 ; 4-byte Folded Reload
	str	s0, [sp, #8028]
	ldr	s0, [sp, #1328]                 ; 4-byte Folded Reload
	str	s0, [sp, #8040]
	ldr	s0, [sp, #1324]                 ; 4-byte Folded Reload
	str	s0, [sp, #8044]
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3808
	ldur	q0, [x9, #128]
	str	q0, [x22]
	ldr	s0, [sp, #1312]                 ; 4-byte Folded Reload
	str	s0, [sp, #6784]
	ldr	s0, [sp, #1308]                 ; 4-byte Folded Reload
	str	s0, [sp, #6788]
	ldr	s0, [sp, #1304]                 ; 4-byte Folded Reload
	str	s0, [sp, #6792]
	ldr	s0, [sp, #1300]                 ; 4-byte Folded Reload
	str	s0, [sp, #6796]
	ldr	s0, [sp, #1296]                 ; 4-byte Folded Reload
	str	s0, [sp, #6800]
	ldr	s0, [sp, #1292]                 ; 4-byte Folded Reload
	str	s0, [sp, #6804]
	ldr	s0, [sp, #1288]                 ; 4-byte Folded Reload
	str	s0, [sp, #6808]
	ldr	s0, [sp, #1284]                 ; 4-byte Folded Reload
	str	s0, [sp, #6812]
	ldr	s0, [sp, #1280]                 ; 4-byte Folded Reload
	str	s0, [sp, #6816]
	ldr	s0, [sp, #1276]                 ; 4-byte Folded Reload
	str	s0, [sp, #6820]
	ldr	s0, [sp, #1272]                 ; 4-byte Folded Reload
	str	s0, [sp, #6824]
	ldr	s0, [sp, #1268]                 ; 4-byte Folded Reload
	str	s0, [sp, #6828]
	ldr	s0, [sp, #1264]                 ; 4-byte Folded Reload
	str	s0, [sp, #6832]
	ldr	s0, [sp, #1260]                 ; 4-byte Folded Reload
	str	s0, [sp, #6836]
	ldr	s0, [sp, #1256]                 ; 4-byte Folded Reload
	str	s0, [sp, #6840]
	ldr	s0, [sp, #1252]                 ; 4-byte Folded Reload
	str	s0, [sp, #6844]
	ldr	s0, [sp, #1248]                 ; 4-byte Folded Reload
	str	s0, [sp, #6848]
	ldr	s0, [sp, #1244]                 ; 4-byte Folded Reload
	str	s0, [sp, #6852]
	ldr	s0, [sp, #1240]                 ; 4-byte Folded Reload
	str	s0, [sp, #6856]
	ldr	s0, [sp, #1236]                 ; 4-byte Folded Reload
	str	s0, [sp, #6860]
	ldr	s0, [sp, #1232]                 ; 4-byte Folded Reload
	str	s0, [sp, #6864]
	ldr	s0, [sp, #1228]                 ; 4-byte Folded Reload
	str	s0, [sp, #6868]
	ldr	s0, [sp, #1224]                 ; 4-byte Folded Reload
	str	s0, [sp, #6872]
	ldr	s0, [sp, #1220]                 ; 4-byte Folded Reload
	str	s0, [sp, #6876]
	ldr	s0, [sp, #1216]                 ; 4-byte Folded Reload
	str	s0, [sp, #6880]
	ldr	s0, [sp, #1212]                 ; 4-byte Folded Reload
	str	s0, [sp, #6884]
	ldr	s0, [sp, #1208]                 ; 4-byte Folded Reload
	str	s0, [sp, #6888]
	ldr	s0, [sp, #1204]                 ; 4-byte Folded Reload
	str	s0, [sp, #6892]
	ldr	s0, [sp, #1200]                 ; 4-byte Folded Reload
	str	s0, [sp, #6896]
	ldr	s0, [sp, #1188]                 ; 4-byte Folded Reload
	str	s0, [sp, #6900]
	ldr	s0, [sp, #1196]                 ; 4-byte Folded Reload
	str	s0, [sp, #6904]
	ldr	s0, [sp, #1192]                 ; 4-byte Folded Reload
	str	s0, [sp, #6908]
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2672
	ldur	q0, [x9, #128]
	str	q0, [x27]
	ldr	s0, [sp, #1184]                 ; 4-byte Folded Reload
	str	s0, [sp, #5648]
	ldr	s0, [sp, #1180]                 ; 4-byte Folded Reload
	str	s0, [sp, #5652]
	ldr	s0, [sp, #1176]                 ; 4-byte Folded Reload
	str	s0, [sp, #5656]
	ldr	s0, [sp, #1172]                 ; 4-byte Folded Reload
	str	s0, [sp, #5660]
	ldr	s0, [sp, #1168]                 ; 4-byte Folded Reload
	str	s0, [sp, #5664]
	ldr	s0, [sp, #1164]                 ; 4-byte Folded Reload
	str	s0, [sp, #5668]
	ldr	s0, [sp, #1160]                 ; 4-byte Folded Reload
	str	s0, [sp, #5672]
	ldr	s0, [sp, #1156]                 ; 4-byte Folded Reload
	str	s0, [sp, #5676]
	ldr	s0, [sp, #1152]                 ; 4-byte Folded Reload
	str	s0, [sp, #5680]
	ldr	s0, [sp, #1148]                 ; 4-byte Folded Reload
	str	s0, [sp, #5684]
	ldr	s0, [sp, #1144]                 ; 4-byte Folded Reload
	str	s0, [sp, #5688]
	ldr	s0, [sp, #1140]                 ; 4-byte Folded Reload
	str	s0, [sp, #5692]
	ldr	s0, [sp, #1136]                 ; 4-byte Folded Reload
	str	s0, [sp, #5696]
	ldr	s0, [sp, #1132]                 ; 4-byte Folded Reload
	str	s0, [sp, #5700]
	ldr	s0, [sp, #1128]                 ; 4-byte Folded Reload
	str	s0, [sp, #5704]
	ldr	s0, [sp, #1124]                 ; 4-byte Folded Reload
	str	s0, [sp, #5708]
	ldr	s0, [sp, #1120]                 ; 4-byte Folded Reload
	str	s0, [sp, #5712]
	ldr	s0, [sp, #1112]                 ; 4-byte Folded Reload
	str	s0, [sp, #5716]
	ldr	s0, [sp, #1104]                 ; 4-byte Folded Reload
	str	s0, [sp, #5720]
	ldr	s0, [sp, #1080]                 ; 4-byte Folded Reload
	str	s0, [sp, #5724]
	ldr	s0, [sp, #1068]                 ; 4-byte Folded Reload
	str	s0, [sp, #5728]
	ldr	s0, [sp, #1048]                 ; 4-byte Folded Reload
	str	s0, [sp, #5732]
	ldr	s0, [sp, #1036]                 ; 4-byte Folded Reload
	str	s0, [sp, #5736]
	ldr	s0, [sp, #1012]                 ; 4-byte Folded Reload
	str	s0, [sp, #5740]
	ldr	s0, [sp, #940]                  ; 4-byte Folded Reload
	str	s0, [sp, #5760]
	ldr	s0, [sp, #932]                  ; 4-byte Folded Reload
	str	s0, [sp, #5764]
	ldr	s0, [sp, #936]                  ; 4-byte Folded Reload
	str	s0, [sp, #5768]
	ldr	s0, [sp, #1024]                 ; 4-byte Folded Reload
	str	s0, [sp, #5744]
	ldr	s0, [sp, #1000]                 ; 4-byte Folded Reload
	str	s0, [sp, #5748]
	ldr	s0, [sp, #988]                  ; 4-byte Folded Reload
	str	s0, [sp, #5752]
	ldr	s0, [sp, #972]                  ; 4-byte Folded Reload
	str	s0, [sp, #5756]
	ldr	s0, [sp, #948]                  ; 4-byte Folded Reload
	str	s0, [sp, #5772]
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1536
	ldur	q0, [x9, #128]
	str	q0, [x26]
	ldr	s0, [sp, #928]                  ; 4-byte Folded Reload
	str	s0, [sp, #4512]
	ldr	s0, [sp, #924]                  ; 4-byte Folded Reload
	str	s0, [sp, #4516]
	ldr	s0, [sp, #920]                  ; 4-byte Folded Reload
	str	s0, [sp, #4520]
	ldr	s0, [sp, #916]                  ; 4-byte Folded Reload
	str	s0, [sp, #4524]
	str	s14, [sp, #4528]
	str	s13, [sp, #4532]
	str	s12, [sp, #4536]
	str	s11, [sp, #4540]
	str	s10, [sp, #4544]
	str	s9, [sp, #4548]
	str	s8, [sp, #4552]
	str	s31, [sp, #4556]
	str	s30, [sp, #4560]
	str	s29, [sp, #4564]
	str	s28, [sp, #4568]
	str	s27, [sp, #4572]
	str	s26, [sp, #4576]
	str	s25, [sp, #4580]
	str	s24, [sp, #4584]
	str	s23, [sp, #4588]
	str	s6, [sp, #4624]
	str	s5, [sp, #4628]
	ldr	x20, [sp, #56]                  ; 8-byte Folded Reload
	ldr	q0, [x20]
	str	q0, [sp, #3920]
	str	s21, [sp, #4592]
	ldr	s1, [x19, #3824]
	ldr	s2, [x19, #3828]
	ldr	s0, [x19, #3832]
	ldr	s3, [sp, #3928]
	str	s22, [sp, #4596]
	str	s20, [sp, #4600]
	str	s19, [sp, #4604]
	str	s18, [sp, #4608]
	str	s17, [sp, #4612]
	str	s16, [sp, #4616]
	str	s7, [sp, #4620]
	str	s4, [sp, #4632]
	str	s15, [sp, #4636]
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #400
	ldur	q4, [x9, #128]
	str	q4, [x10]
	ldr	s4, [sp, #3932]
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1116]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s4, s2, s4, s5
	ldr	s5, [sp, #1108]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s4, s5
	fmul	s5, s0, s4
	fmadd	s5, s2, s3, s5
	ldr	s6, [sp, #1100]                 ; 4-byte Folded Reload
	fmsub	s5, s1, s5, s6
	str	s3, [sp, #3936]
	str	s4, [sp, #3940]
	fmul	s3, s0, s5
	fmadd	s3, s2, s4, s3
	ldr	s4, [sp, #1096]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s4
	fmul	s4, s0, s3
	fmadd	s4, s2, s5, s4
	ldr	s6, [sp, #1092]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s4, s6
	str	s5, [sp, #3944]
	str	s3, [sp, #3948]
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1088]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s5, s2, s4, s5
	str	s4, [sp, #3952]
	str	s3, [sp, #3956]
	ldr	s4, [sp, #1084]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s5, s4
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1076]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s5, s2, s4, s5
	str	s4, [sp, #3960]
	str	s3, [sp, #3964]
	ldr	s4, [sp, #1072]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s5, s4
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1064]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s5, s2, s4, s5
	str	s4, [sp, #3968]
	str	s3, [sp, #3972]
	ldr	s4, [sp, #1060]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s5, s4
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1056]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s5, s2, s4, s5
	str	s4, [sp, #3976]
	str	s3, [sp, #3980]
	ldr	s4, [sp, #1052]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s5, s4
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1044]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s5, s2, s4, s5
	str	s4, [sp, #3984]
	str	s3, [sp, #3988]
	ldr	s4, [sp, #1040]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s5, s4
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1032]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s5, s2, s4, s5
	str	s4, [sp, #3992]
	str	s3, [sp, #3996]
	ldr	s4, [sp, #1028]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s5, s4
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1020]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s5, s2, s4, s5
	str	s4, [sp, #4000]
	str	s3, [sp, #4004]
	ldr	s4, [sp, #1016]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s5, s4
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #1008]                 ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	fmul	s5, s0, s3
	fmadd	s5, s2, s4, s5
	str	s4, [sp, #4008]
	str	s3, [sp, #4012]
	ldr	s4, [sp, #1004]                 ; 4-byte Folded Reload
	fmsub	s4, s1, s5, s4
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #996]                  ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	str	s4, [sp, #4016]
	str	s3, [sp, #4020]
	fmul	s5, s0, s3
	fmadd	s4, s2, s4, s5
	ldr	s5, [sp, #992]                  ; 4-byte Folded Reload
	fmsub	s4, s1, s4, s5
	fmul	s5, s0, s4
	fmadd	s3, s2, s3, s5
	ldr	s5, [sp, #984]                  ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s5
	str	s4, [sp, #4024]
	str	s3, [sp, #4028]
	fmul	s5, s0, s3
	fmadd	s4, s2, s4, s5
	ldr	s5, [sp, #980]                  ; 4-byte Folded Reload
	fmsub	s16, s1, s4, s5
	fmul	s4, s0, s16
	fmadd	s3, s2, s3, s4
	ldr	s4, [sp, #976]                  ; 4-byte Folded Reload
	fmsub	s17, s1, s3, s4
	fmul	s3, s0, s17
	fmadd	s3, s2, s16, s3
	ldr	s4, [sp, #968]                  ; 4-byte Folded Reload
	fmsub	s18, s1, s3, s4
	fmul	s3, s0, s18
	fmadd	s3, s2, s17, s3
	ldr	s4, [sp, #960]                  ; 4-byte Folded Reload
	fmsub	s19, s1, s3, s4
	fmul	s3, s0, s19
	fmadd	s3, s2, s18, s3
	ldr	s4, [sp, #956]                  ; 4-byte Folded Reload
	fmsub	s3, s1, s3, s4
	fmul	s4, s0, s3
	fmadd	s4, s2, s19, s4
	ldr	s5, [sp, #952]                  ; 4-byte Folded Reload
	fmsub	s20, s1, s4, s5
	str	s3, [sp, #4048]
	fmul	s4, s0, s20
	fmadd	s3, s2, s3, s4
	ldr	s4, [sp, #944]                  ; 4-byte Folded Reload
	fmsub	s21, s1, s3, s4
	fmul	s5, s0, s21
	ldr	x22, [sp, #48]                  ; 8-byte Folded Reload
	ldr	q0, [x22]
	str	q0, [sp, #19120]
	ldr	s0, [x19, #280]
	ldr	s3, [x19, #288]
	fmov	s29, s0
	fneg	s4, s0
	add	x9, sp, #2896
	ldr	s7, [x9, #16380]
	add	x9, sp, #2748
	ldr	s0, [x9, #16380]
	fmadd	s6, s2, s20, s5
	ldr	s2, [x19, #232]
	ldr	s5, [x19, #272]
	ldr	s22, [sp, #964]                 ; 4-byte Folded Reload
	fmsub	s22, s1, s6, s22
	ldr	s1, [x19, #276]
	ldr	s6, [x19, #284]
	str	s16, [sp, #4032]
	str	s17, [sp, #4036]
	str	s18, [sp, #4040]
	str	s19, [sp, #4044]
	str	s20, [sp, #4052]
	str	s21, [sp, #4056]
	str	s22, [sp, #4060]
	add	x9, sp, #3920
	ldur	q16, [x9, #128]
	str	q16, [x20]
	add	x9, sp, #2752
	ldr	s23, [x9, #16380]
	ldr	x9, [sp, #488]                  ; 8-byte Folded Reload
	fmov	s16, s23
	ldr	x23, [sp, #3200]                ; 8-byte Folded Reload
LBB17_66:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s1, s7
	ldr	s17, [x9]
	fmadd	s7, s5, s17, s7
	ldur	s18, [x9, #-8]
	fmadd	s7, s5, s18, s7
	fmul	s18, s3, s16
	fmadd	s0, s6, s0, s18
	fmul	s18, s0, s4
	fmov	s0, s16
	fmadd	s16, s2, s7, s18
	str	s16, [x23, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s7, s17
	cmp	x8, #128
	b.ne	LBB17_66
; %bb.67:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #2736
	ldur	q0, [x9, #128]
	str	q0, [x22]
	ldp	x26, x24, [sp, #32]             ; 16-byte Folded Reload
	ldr	q0, [x24]
	str	q0, [sp, #17984]
	ldr	s2, [x19, #512]
	ldr	s3, [x19, #552]
	ldr	s4, [x19, #556]
	ldr	s5, [x19, #560]
	ldr	s0, [x19, #564]
	ldr	s1, [x19, #568]
	str	s5, [sp, #2592]                 ; 4-byte Folded Spill
	fneg	s5, s5
	add	x9, sp, #1760
	ldr	s7, [x9, #16380]
	add	x9, sp, #1612
	ldr	s6, [x9, #16380]
	add	x9, sp, #1616
	ldr	s24, [x9, #16380]
	ldr	x9, [sp, #728]                  ; 8-byte Folded Reload
	fmov	s16, s24
	ldr	x27, [sp, #24]                  ; 8-byte Folded Reload
	add	x10, sp, #3488
LBB17_68:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s4, s7
	ldr	s17, [x9]
	fmadd	s7, s3, s17, s7
	ldur	s18, [x9, #-8]
	fmadd	s7, s3, s18, s7
	fmul	s18, s1, s16
	fmadd	s6, s0, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s2, s7, s18
	str	s16, [x4, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s7, s17
	cmp	x8, #128
	b.ne	LBB17_68
; %bb.69:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #1600
	ldur	q0, [x9, #128]
	str	q0, [x24]
	ldr	q0, [x26]
	str	q0, [sp, #16848]
	ldr	s3, [x19, #776]
	ldr	s4, [x19, #816]
	ldr	s5, [x19, #820]
	ldr	s2, [x19, #824]
	ldr	s0, [x19, #828]
	ldr	s1, [x19, #832]
	str	s2, [sp, #2588]                 ; 4-byte Folded Spill
	fneg	s2, s2
	add	x9, sp, #624
	ldr	s7, [x9, #16380]
	add	x9, sp, #476
	ldr	s6, [x9, #16380]
	add	x9, sp, #480
	ldr	s25, [x9, #16380]
	ldr	x9, [sp, #744]                  ; 8-byte Folded Reload
	fmov	s16, s25
	ldr	x23, [sp, #576]                 ; 8-byte Folded Reload
	ldr	x4, [sp, #3280]                 ; 8-byte Folded Reload
	ldr	x20, [sp, #120]                 ; 8-byte Folded Reload
	ldr	x25, [sp, #296]                 ; 8-byte Folded Reload
	ldr	x21, [sp, #584]                 ; 8-byte Folded Reload
LBB17_70:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s5, s7
	ldr	s17, [x9]
	fmadd	s7, s4, s17, s7
	ldur	s18, [x9, #-8]
	fmadd	s7, s4, s18, s7
	fmul	s18, s1, s16
	fmadd	s6, s0, s6, s18
	fmul	s18, s6, s2
	fmov	s6, s16
	fmadd	s16, s3, s7, s18
	str	s16, [x4, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s7, s17
	cmp	x8, #128
	b.ne	LBB17_70
; %bb.71:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #464
	ldur	q0, [x9, #128]
	str	q0, [x26]
	ldr	q0, [x27]
	str	q0, [sp, #15712]
	ldr	s4, [x19, #1040]
	ldr	s5, [x19, #1080]
	ldr	s6, [x19, #1084]
	ldr	s2, [x19, #1088]
	ldr	s0, [x19, #1092]
	ldr	s1, [x19, #1096]
	str	s2, [sp, #2576]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s7, [sp, #15868]
	ldr	s3, [sp, #15720]
	ldr	s26, [sp, #15724]
	ldr	x9, [sp, #712]                  ; 8-byte Folded Reload
	fmov	s16, s26
	ldr	x4, [sp, #3288]                 ; 8-byte Folded Reload
LBB17_72:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s6, s7
	ldr	s17, [x9]
	fmadd	s7, s5, s17, s7
	ldur	s18, [x9, #-8]
	fmadd	s7, s5, s18, s7
	fmul	s18, s1, s16
	fmadd	s3, s0, s3, s18
	fmul	s18, s3, s2
	fmov	s3, s16
	fmadd	s16, s4, s7, s18
	str	s16, [x23, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s7, s17
	cmp	x8, #128
	b.ne	LBB17_72
; %bb.73:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3424
	ldur	q0, [x9, #128]
	str	q0, [x27]
	ldr	x9, [sp, #2936]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #14576]
	ldr	s5, [x19, #1304]
	ldr	s6, [x19, #1344]
	ldr	s7, [x19, #1348]
	ldr	s2, [x19, #1352]
	ldr	s0, [x19, #1356]
	ldr	s1, [x19, #1360]
	str	s2, [sp, #2572]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #14732]
	ldr	s3, [sp, #14584]
	ldr	s27, [sp, #14588]
	ldr	x9, [sp, #720]                  ; 8-byte Folded Reload
	fmov	s16, s27
LBB17_74:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s7, s4
	ldr	s17, [x9]
	fmadd	s4, s6, s17, s4
	ldur	s18, [x9, #-8]
	fmadd	s4, s6, s18, s4
	fmul	s18, s1, s16
	fmadd	s3, s0, s3, s18
	fmul	s18, s3, s2
	fmov	s3, s16
	fmadd	s16, s5, s4, s18
	str	s16, [x4, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s17
	cmp	x8, #128
	b.ne	LBB17_74
; %bb.75:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2288
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2936]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2928]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #13440]
	ldr	s6, [x19, #1568]
	ldr	s7, [x19, #1608]
	ldr	s16, [x19, #1612]
	ldr	s2, [x19, #1616]
	ldr	s0, [x19, #1620]
	ldr	s1, [x19, #1624]
	str	s2, [sp, #2560]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #13596]
	ldr	s3, [sp, #13448]
	ldr	s28, [sp, #13452]
	ldr	x9, [sp, #736]                  ; 8-byte Folded Reload
	fmov	s5, s28
	ldr	x4, [sp, #3208]                 ; 8-byte Folded Reload
LBB17_76:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s16, s4
	ldr	s17, [x9]
	fmadd	s4, s7, s17, s4
	ldur	s18, [x9, #-8]
	fmadd	s4, s7, s18, s4
	fmul	s18, s1, s5
	fmadd	s3, s0, s3, s18
	fmul	s18, s3, s2
	fmov	s3, s5
	fmadd	s5, s6, s4, s18
	str	s5, [x4, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s17
	cmp	x8, #128
	b.ne	LBB17_76
; %bb.77:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1152
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2928]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2920]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #12304]
	ldr	s7, [x19, #1832]
	ldr	s16, [x19, #1872]
	ldr	s17, [x19, #1876]
	ldr	s2, [x19, #1880]
	ldr	s0, [x19, #1884]
	ldr	s1, [x19, #1888]
	str	s2, [sp, #2556]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #12460]
	ldr	s3, [sp, #12312]
	ldr	s30, [sp, #12316]
	ldr	x9, [sp, #752]                  ; 8-byte Folded Reload
	fmov	s5, s30
LBB17_78:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s17, s4
	ldr	s6, [x9]
	fmadd	s4, s16, s6, s4
	ldur	s18, [x9, #-8]
	fmadd	s4, s16, s18, s4
	fmul	s18, s1, s5
	fmadd	s3, s0, s3, s18
	fmul	s18, s3, s2
	fmov	s3, s5
	fmadd	s5, s7, s4, s18
	str	s5, [x3, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s6
	cmp	x8, #128
	b.ne	LBB17_78
; %bb.79:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #16
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2920]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2912]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #11168]
	ldr	s16, [x19, #2096]
	ldr	s17, [x19, #2136]
	ldr	s18, [x19, #2140]
	ldr	s2, [x19, #2144]
	ldr	s0, [x19, #2148]
	ldr	s1, [x19, #2152]
	str	s2, [sp, #2544]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #11324]
	ldr	s3, [sp, #11176]
	ldr	s31, [sp, #11180]
	ldr	x9, [sp, #760]                  ; 8-byte Folded Reload
	fmov	s5, s31
	ldr	x3, [sp, #3216]                 ; 8-byte Folded Reload
	ldr	x4, [sp, #3296]                 ; 8-byte Folded Reload
LBB17_80:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s18, s4
	ldr	s6, [x9]
	fmadd	s4, s17, s6, s4
	ldur	s7, [x9, #-8]
	fmadd	s4, s17, s7, s4
	fmul	s7, s1, s5
	fmadd	s3, s0, s3, s7
	fmul	s7, s3, s2
	fmov	s3, s5
	fmadd	s5, s16, s4, s7
	str	s5, [x3, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s6
	cmp	x8, #128
	b.ne	LBB17_80
; %bb.81:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2976
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2912]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2904]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #10032]
	ldr	s17, [x19, #2360]
	ldr	s18, [x19, #2400]
	ldr	s19, [x19, #2404]
	ldr	s2, [x19, #2408]
	ldr	s0, [x19, #2412]
	ldr	s1, [x19, #2416]
	str	s2, [sp, #2536]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #10188]
	ldr	s3, [sp, #10040]
	ldr	s8, [sp, #10044]
	ldr	x9, [sp, #768]                  ; 8-byte Folded Reload
	fmov	s5, s8
LBB17_82:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s19, s4
	ldr	s6, [x9]
	fmadd	s4, s18, s6, s4
	ldur	s7, [x9, #-8]
	fmadd	s4, s18, s7, s4
	fmul	s7, s1, s5
	fmadd	s3, s0, s3, s7
	fmul	s7, s3, s2
	fmov	s3, s5
	fmadd	s5, s17, s4, s7
	str	s5, [x2, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s6
	cmp	x8, #128
	b.ne	LBB17_82
; %bb.83:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1840
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2904]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2896]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #8896]
	ldr	s18, [x19, #2624]
	ldr	s19, [x19, #2664]
	ldr	s20, [x19, #2668]
	ldr	s2, [x19, #2672]
	ldr	s0, [x19, #2676]
	ldr	s1, [x19, #2680]
	str	s2, [sp, #2532]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #9052]
	ldr	s3, [sp, #8904]
	ldr	s9, [sp, #8908]
	ldr	x9, [sp, #904]                  ; 8-byte Folded Reload
	fmov	s5, s9
	ldr	x2, [sp, #3232]                 ; 8-byte Folded Reload
	ldr	x3, [sp, #3304]                 ; 8-byte Folded Reload
LBB17_84:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s20, s4
	ldr	s6, [x9]
	fmadd	s4, s19, s6, s4
	ldur	s7, [x9, #-8]
	fmadd	s4, s19, s7, s4
	fmul	s7, s1, s5
	fmadd	s3, s0, s3, s7
	fmul	s7, s3, s2
	fmov	s3, s5
	fmadd	s5, s18, s4, s7
	str	s5, [x2, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s6
	cmp	x8, #128
	b.ne	LBB17_84
; %bb.85:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #704
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2896]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2888]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #7760]
	ldr	s19, [x19, #2888]
	ldr	s20, [x19, #2928]
	ldr	s21, [x19, #2932]
	ldr	s2, [x19, #2936]
	ldr	s0, [x19, #2940]
	ldr	s1, [x19, #2944]
	str	s2, [sp, #2520]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #7916]
	ldr	s3, [sp, #7768]
	ldr	s10, [sp, #7772]
	ldr	x9, [sp, #776]                  ; 8-byte Folded Reload
	fmov	s5, s10
	fmov	s17, s29
LBB17_86:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s21, s4
	ldr	s6, [x9]
	fmadd	s4, s20, s6, s4
	ldur	s7, [x9, #-8]
	fmadd	s4, s20, s7, s4
	fmul	s7, s1, s5
	fmadd	s3, s0, s3, s7
	fmul	s7, s3, s2
	fmov	s3, s5
	fmadd	s5, s19, s4, s7
	str	s5, [x0, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s6
	cmp	x8, #128
	b.ne	LBB17_86
; %bb.87:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3664
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2888]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2880]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #6624]
	ldr	s20, [x19, #3152]
	ldr	s21, [x19, #3192]
	ldr	s22, [x19, #3196]
	ldr	s2, [x19, #3200]
	ldr	s0, [x19, #3204]
	ldr	s1, [x19, #3208]
	str	s2, [sp, #2516]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #6780]
	ldr	s3, [sp, #6632]
	ldr	s11, [sp, #6636]
	ldr	x9, [sp, #880]                  ; 8-byte Folded Reload
	fmov	s5, s11
	ldr	x0, [sp, #3248]                 ; 8-byte Folded Reload
	ldr	x2, [sp, #3224]                 ; 8-byte Folded Reload
LBB17_88:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s22, s4
	ldr	s6, [x9]
	fmadd	s4, s21, s6, s4
	ldur	s7, [x9, #-8]
	fmadd	s4, s21, s7, s4
	fmul	s7, s1, s5
	fmadd	s3, s0, s3, s7
	fmul	s7, s3, s2
	fmov	s3, s5
	fmadd	s5, s20, s4, s7
	str	s5, [x0, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s6
	cmp	x8, #128
	b.ne	LBB17_88
; %bb.89:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2528
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2880]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2872]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #5488]
	ldr	s21, [x19, #3416]
	ldr	s22, [x19, #3456]
	ldr	s29, [x19, #3460]
	ldr	s2, [x19, #3464]
	ldr	s0, [x19, #3468]
	ldr	s1, [x19, #3472]
	str	s2, [sp, #2504]                 ; 4-byte Folded Spill
	fneg	s2, s2
	ldr	s4, [sp, #5644]
	ldr	s3, [sp, #5496]
	ldr	s12, [sp, #5500]
	ldr	x9, [sp, #496]                  ; 8-byte Folded Reload
	fmov	s5, s12
LBB17_90:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s29, s4
	ldr	s6, [x9]
	fmadd	s4, s22, s6, s4
	ldur	s7, [x9, #-8]
	fmadd	s4, s22, s7, s4
	fmul	s7, s1, s5
	fmadd	s3, s0, s3, s7
	fmul	s7, s3, s2
	fmov	s3, s5
	fmadd	s5, s21, s4, s7
	str	s5, [x16, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s6
	cmp	x8, #128
	b.ne	LBB17_90
; %bb.91:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1392
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2872]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2864]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #4352]
	ldr	s22, [x19, #3680]
	ldr	s29, [x19, #3720]
	ldr	s14, [x19, #3724]
	ldr	s2, [x19, #3728]
	ldr	s0, [x19, #3732]
	ldr	s1, [x19, #3736]
	fmov	s19, s2
	fneg	s2, s2
	ldr	s4, [sp, #4508]
	ldr	s3, [sp, #4360]
	ldr	s13, [sp, #4364]
	ldr	x9, [sp, #504]                  ; 8-byte Folded Reload
	fmov	s5, s13
	ldr	x16, [sp, #3256]                ; 8-byte Folded Reload
	ldr	x0, [sp, #3240]                 ; 8-byte Folded Reload
LBB17_92:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s14, s4
	ldr	s6, [x9]
	fmadd	s4, s29, s6, s4
	ldur	s7, [x9, #-8]
	fmadd	s4, s29, s7, s4
	fmul	s7, s1, s5
	fmadd	s3, s0, s3, s7
	fmul	s7, s3, s2
	fmov	s3, s5
	fmadd	s5, s22, s4, s7
	str	s5, [x16, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s4, s6
	cmp	x8, #128
	b.ne	LBB17_92
; %bb.93:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #256
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2864]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2856]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #3776]
	ldr	s29, [x19, #3824]
	ldr	s15, [x19, #3856]
	ldr	s0, [x19, #3860]
	ldr	s18, [x19, #3864]
	ldr	s1, [x19, #3868]
	ldr	s2, [x19, #3872]
	fneg	s3, s18
	ldr	s5, [sp, #3932]
	ldr	s4, [sp, #3784]
	ldr	s14, [sp, #3788]
	ldr	x9, [sp, #512]                  ; 8-byte Folded Reload
	fmov	s6, s14
LBB17_94:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s5, s0, s5
	ldr	s7, [x9]
	fmadd	s5, s15, s7, s5
	ldur	s16, [x9, #-8]
	fmadd	s5, s15, s16, s5
	fmul	s16, s2, s6
	fmadd	s4, s1, s4, s16
	fmul	s16, s4, s3
	fmov	s4, s6
	fmadd	s6, s29, s5, s16
	str	s6, [x14, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	fmov	s5, s7
	cmp	x8, #128
	b.ne	LBB17_94
; %bb.95:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3776
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2856]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2848]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #18976]
	ldr	s0, [x19, #312]
	ldr	s1, [x19, #316]
	ldr	s4, [x19, #320]
	ldr	s2, [x19, #324]
	ldr	s3, [x19, #328]
	str	s4, [sp, #2500]                 ; 4-byte Folded Spill
	fneg	s4, s4
	add	x9, sp, #2604
	ldr	s5, [x9, #16380]
	add	x9, sp, #2608
	ldr	s15, [x9, #16380]
	ldr	x9, [sp, #3200]                 ; 8-byte Folded Reload
	fmov	s6, s15
	ldr	x16, [sp, #3312]                ; 8-byte Folded Reload
LBB17_96:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s1, s23
	ldr	s23, [x9]
	fmadd	s7, s0, s23, s7
	ldur	s16, [x9, #-8]
	fmadd	s7, s0, s16, s7
	fmul	s16, s3, s6
	fmadd	s5, s2, s5, s16
	fmul	s16, s5, s4
	fmov	s5, s6
	fmadd	s6, s17, s7, s16
	str	s6, [x30, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_96
; %bb.97:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #2592
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2848]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2840]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #17840]
	ldr	s1, [x19, #592]
	ldr	s2, [x19, #596]
	ldr	s4, [x19, #600]
	ldr	s3, [x19, #604]
	ldr	s0, [x19, #608]
	str	s4, [sp, #2488]                 ; 4-byte Folded Spill
	fneg	s4, s4
	add	x9, sp, #1468
	ldr	s5, [x9, #16380]
	add	x9, sp, #1472
	ldr	s23, [x9, #16380]
	mov	x9, x4
	fmov	s6, s23
	ldr	s17, [sp, #2592]                ; 4-byte Folded Reload
LBB17_98:                               ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s2, s24
	ldr	s24, [x9]
	fmadd	s7, s1, s24, s7
	ldur	s16, [x9, #-8]
	fmadd	s7, s1, s16, s7
	fmul	s16, s0, s6
	fmadd	s5, s3, s5, s16
	fmul	s16, s5, s4
	fmov	s5, s6
	fmadd	s6, s17, s7, s16
	str	s6, [x6, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_98
; %bb.99:                               ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #1456
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2840]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2832]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #16704]
	ldr	s2, [x19, #856]
	ldr	s3, [x19, #860]
	ldr	s1, [x19, #864]
	ldr	s4, [x19, #868]
	ldr	s0, [x19, #872]
	str	s1, [sp, #2480]                 ; 4-byte Folded Spill
	fneg	s1, s1
	add	x9, sp, #332
	ldr	s5, [x9, #16380]
	add	x9, sp, #336
	ldr	s24, [x9, #16380]
	ldr	x9, [sp, #3280]                 ; 8-byte Folded Reload
	fmov	s6, s24
	ldr	x14, [sp, #3264]                ; 8-byte Folded Reload
	ldr	x4, [sp, #3288]                 ; 8-byte Folded Reload
	ldr	s17, [sp, #2588]                ; 4-byte Folded Reload
LBB17_100:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s3, s25
	ldr	s25, [x9]
	fmadd	s7, s2, s25, s7
	ldur	s16, [x9, #-8]
	fmadd	s7, s2, s16, s7
	fmul	s16, s0, s6
	fmadd	s5, s4, s5, s16
	fmul	s16, s5, s1
	fmov	s5, s6
	fmadd	s6, s17, s7, s16
	str	s6, [x14, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_100
; %bb.101:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #320
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2832]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2824]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #15568]
	ldr	s3, [x19, #1120]
	ldr	s4, [x19, #1124]
	ldr	s1, [x19, #1128]
	ldr	s5, [x19, #1132]
	ldr	s0, [x19, #1136]
	str	s1, [sp, #2588]                 ; 4-byte Folded Spill
	fneg	s1, s1
	ldr	s2, [sp, #15576]
	ldr	s25, [sp, #15580]
	mov	x9, x23
	fmov	s6, s25
	ldr	s17, [sp, #2576]                ; 4-byte Folded Reload
LBB17_102:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s4, s26
	ldr	s26, [x9]
	fmadd	s7, s3, s26, s7
	ldur	s16, [x9, #-8]
	fmadd	s7, s3, s16, s7
	fmul	s16, s0, s6
	fmadd	s2, s5, s2, s16
	fmul	s16, s2, s1
	fmov	s2, s6
	fmadd	s6, s17, s7, s16
	str	s6, [x11, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_102
; %bb.103:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3280
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2824]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2816]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #14432]
	ldr	s4, [x19, #1384]
	ldr	s5, [x19, #1388]
	ldr	s1, [x19, #1392]
	ldr	s6, [x19, #1396]
	ldr	s0, [x19, #1400]
	str	s1, [sp, #2576]                 ; 4-byte Folded Spill
	fneg	s1, s1
	ldr	s2, [sp, #14440]
	ldr	s26, [sp, #14444]
	mov	x9, x4
	fmov	s3, s26
	ldr	x11, [sp, #3272]                ; 8-byte Folded Reload
	ldr	x14, [sp, #3320]                ; 8-byte Folded Reload
	ldr	s17, [sp, #2572]                ; 4-byte Folded Reload
LBB17_104:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s7, s5, s27
	ldr	s27, [x9]
	fmadd	s7, s4, s27, s7
	ldur	s16, [x9, #-8]
	fmadd	s7, s4, s16, s7
	fmul	s16, s0, s3
	fmadd	s2, s6, s2, s16
	fmul	s16, s2, s1
	fmov	s2, s3
	fmadd	s3, s17, s7, s16
	str	s3, [x11, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_104
; %bb.105:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2144
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2816]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2808]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #13296]
	ldr	s5, [x19, #1648]
	ldr	s6, [x19, #1652]
	ldr	s1, [x19, #1656]
	ldr	s7, [x19, #1660]
	ldr	s0, [x19, #1664]
	str	s1, [sp, #2572]                 ; 4-byte Folded Spill
	fneg	s1, s1
	ldr	s2, [sp, #13304]
	ldr	s27, [sp, #13308]
	ldr	x9, [sp, #3208]                 ; 8-byte Folded Reload
	fmov	s3, s27
	ldr	s17, [sp, #2560]                ; 4-byte Folded Reload
LBB17_106:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s6, s28
	ldr	s28, [x9]
	fmadd	s4, s5, s28, s4
	ldur	s16, [x9, #-8]
	fmadd	s4, s5, s16, s4
	fmul	s16, s0, s3
	fmadd	s2, s7, s2, s16
	fmul	s16, s2, s1
	fmov	s2, s3
	fmadd	s3, s17, s4, s16
	str	s3, [x7, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_106
; %bb.107:                              ;   in Loop: Header=BB17_7 Depth=1
	str	s18, [sp, #2592]                ; 4-byte Folded Spill
	mov	x8, #0                          ; =0x0
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1008
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2808]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2800]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #12160]
	ldr	s6, [x19, #1912]
	ldr	s7, [x19, #1916]
	ldr	s1, [x19, #1920]
	ldr	s16, [x19, #1924]
	ldr	s0, [x19, #1928]
	str	s1, [sp, #2560]                 ; 4-byte Folded Spill
	fneg	s1, s1
	ldr	s2, [sp, #12168]
	ldr	s28, [sp, #12172]
	mov	x9, x3
	fmov	s3, s28
	ldr	s5, [sp, #2556]                 ; 4-byte Folded Reload
LBB17_108:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s7, s30
	ldr	s30, [x9]
	fmadd	s4, s6, s30, s4
	ldur	s17, [x9, #-8]
	fmadd	s4, s6, s17, s4
	fmul	s17, s0, s3
	fmadd	s2, s16, s2, s17
	fmul	s17, s2, s1
	fmov	s2, s3
	fmadd	s3, s5, s4, s17
	str	s3, [x5, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_108
; %bb.109:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3968
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2800]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2792]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #11024]
	ldr	s7, [x19, #2176]
	ldr	s16, [x19, #2180]
	ldr	s1, [x19, #2184]
	ldr	s17, [x19, #2188]
	ldr	s0, [x19, #2192]
	str	s1, [sp, #2556]                 ; 4-byte Folded Spill
	fneg	s1, s1
	ldr	s2, [sp, #11032]
	ldr	s30, [sp, #11036]
	ldr	x9, [sp, #3216]                 ; 8-byte Folded Reload
	fmov	s3, s30
	ldr	x3, [sp, #520]                  ; 8-byte Folded Reload
	ldr	s5, [sp, #2544]                 ; 4-byte Folded Reload
LBB17_110:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s16, s31
	ldr	s31, [x9]
	fmadd	s4, s7, s31, s4
	ldur	s18, [x9, #-8]
	fmadd	s4, s7, s18, s4
	fmul	s18, s0, s3
	fmadd	s2, s17, s2, s18
	fmul	s18, s2, s1
	fmov	s2, s3
	fmadd	s3, s5, s4, s18
	str	s3, [x21, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_110
; %bb.111:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2832
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2792]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2784]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #9888]
	ldr	s16, [x19, #2440]
	ldr	s17, [x19, #2444]
	ldr	s7, [x19, #2448]
	ldr	s18, [x19, #2452]
	ldr	s0, [x19, #2456]
	fneg	s1, s7
	ldr	s2, [sp, #9896]
	ldr	s31, [sp, #9900]
	mov	x9, x2
	fmov	s3, s31
	ldr	s5, [sp, #2536]                 ; 4-byte Folded Reload
	fmov	s6, s19
LBB17_112:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s17, s8
	ldr	s8, [x9]
	fmadd	s4, s16, s8, s4
	ldur	s19, [x9, #-8]
	fmadd	s4, s16, s19, s4
	fmul	s19, s0, s3
	fmadd	s2, s18, s2, s19
	fmul	s19, s2, s1
	fmov	s2, s3
	fmadd	s3, s5, s4, s19
	str	s3, [x3, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_112
; %bb.113:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1696
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2784]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2776]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #8752]
	ldr	s17, [x19, #2704]
	ldr	s18, [x19, #2708]
	ldr	s16, [x19, #2712]
	ldr	s19, [x19, #2716]
	ldr	s0, [x19, #2720]
	fneg	s1, s16
	ldr	s2, [sp, #8760]
	ldr	s8, [sp, #8764]
	ldr	x9, [sp, #3232]                 ; 8-byte Folded Reload
	fmov	s3, s8
	add	x2, sp, #2, lsl #12             ; =8192
	add	x2, x2, #1552
	ldr	s5, [sp, #2532]                 ; 4-byte Folded Reload
LBB17_114:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s18, s9
	ldr	s9, [x9]
	fmadd	s4, s17, s9, s4
	ldur	s20, [x9, #-8]
	fmadd	s4, s17, s20, s4
	fmul	s20, s0, s3
	fmadd	s2, s19, s2, s20
	fmul	s20, s2, s1
	fmov	s2, s3
	fmadd	s3, s5, s4, s20
	str	s3, [x1, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_114
; %bb.115:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #560
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2776]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2768]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #7616]
	ldr	s18, [x19, #2968]
	ldr	s19, [x19, #2972]
	ldr	s17, [x19, #2976]
	ldr	s20, [x19, #2980]
	ldr	s0, [x19, #2984]
	fneg	s1, s17
	ldr	s2, [sp, #7624]
	ldr	s9, [sp, #7628]
	mov	x9, x0
	fmov	s3, s9
	ldr	s5, [sp, #2520]                 ; 4-byte Folded Reload
LBB17_116:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s19, s10
	ldr	s10, [x9]
	fmadd	s4, s18, s10, s4
	ldur	s21, [x9, #-8]
	fmadd	s4, s18, s21, s4
	fmul	s21, s0, s3
	fmadd	s2, s20, s2, s21
	fmul	s21, s2, s1
	fmov	s2, s3
	fmadd	s3, s5, s4, s21
	str	s3, [x17, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_116
; %bb.117:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3520
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2768]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2760]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #6480]
	ldr	s19, [x19, #3232]
	ldr	s20, [x19, #3236]
	ldr	s18, [x19, #3240]
	ldr	s21, [x19, #3244]
	ldr	s0, [x19, #3248]
	fneg	s1, s18
	ldr	s2, [sp, #6488]
	ldr	s10, [sp, #6492]
	ldr	x9, [sp, #3248]                 ; 8-byte Folded Reload
	fmov	s3, s10
	add	x0, sp, #2, lsl #12             ; =8192
	add	x0, x0, #416
	ldr	s5, [sp, #2516]                 ; 4-byte Folded Reload
LBB17_118:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s20, s11
	ldr	s11, [x9]
	fmadd	s4, s19, s11, s4
	ldur	s22, [x9, #-8]
	fmadd	s4, s19, s22, s4
	fmul	s22, s0, s3
	fmadd	s2, s21, s2, s22
	fmul	s22, s2, s1
	fmov	s2, s3
	fmadd	s3, s5, s4, s22
	str	s3, [x15, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_118
; %bb.119:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2384
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2760]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2752]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #5344]
	ldr	s20, [x19, #3496]
	ldr	s21, [x19, #3500]
	ldr	s19, [x19, #3504]
	ldr	s22, [x19, #3508]
	ldr	s0, [x19, #3512]
	fneg	s1, s19
	ldr	s2, [sp, #5352]
	ldr	s11, [sp, #5356]
	mov	x9, x16
	fmov	s3, s11
	ldr	s5, [sp, #2504]                 ; 4-byte Folded Reload
LBB17_120:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s21, s12
	ldr	s12, [x9]
	fmadd	s4, s20, s12, s4
	ldur	s29, [x9, #-8]
	fmadd	s4, s20, s29, s4
	fmul	s29, s0, s3
	fmadd	s2, s22, s2, s29
	fmul	s29, s2, s1
	fmov	s2, s3
	fmadd	s3, s5, s4, s29
	str	s3, [x13, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_120
; %bb.121:                              ;   in Loop: Header=BB17_7 Depth=1
	str	s7, [sp, #2544]                 ; 4-byte Folded Spill
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1248
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2752]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2744]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #4208]
	ldr	s21, [x19, #3760]
	ldr	s22, [x19, #3764]
	ldr	s20, [x19, #3768]
	ldr	s29, [x19, #3772]
	ldr	s0, [x19, #3776]
	fneg	s1, s20
	ldr	s2, [sp, #4216]
	ldr	s12, [sp, #4220]
	ldr	x9, [sp, #3256]                 ; 8-byte Folded Reload
	fmov	s3, s12
	ldr	x16, [sp, #568]                 ; 8-byte Folded Reload
LBB17_122:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s4, s22, s13
	ldr	s13, [x9]
	fmadd	s4, s21, s13, s4
	ldur	s5, [x9, #-8]
	fmadd	s4, s21, s5, s4
	fmul	s5, s0, s3
	fmadd	s2, s29, s2, s5
	fmul	s5, s2, s1
	fmov	s2, s3
	fmadd	s3, s6, s4, s5
	str	s3, [x12, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_122
; %bb.123:                              ;   in Loop: Header=BB17_7 Depth=1
	mov	x8, #0                          ; =0x0
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #112
	ldur	q0, [x9, #128]
	ldr	x9, [sp, #2744]                 ; 8-byte Folded Reload
	str	q0, [x9]
	ldr	x9, [sp, #2736]                 ; 8-byte Folded Reload
	ldr	q0, [x9]
	str	q0, [sp, #3632]
	ldr	s22, [x19, #3892]
	ldr	s29, [x19, #3896]
	ldr	s21, [x19, #3900]
	ldr	s0, [x19, #3904]
	ldr	s1, [x19, #3908]
	fneg	s2, s21
	ldr	s3, [sp, #3640]
	ldr	s4, [sp, #3644]
	mov	x9, x14
	fmov	s13, s4
	ldr	s7, [sp, #2592]                 ; 4-byte Folded Reload
LBB17_124:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s5, s29, s14
	ldr	s14, [x9]
	fmadd	s5, s22, s14, s5
	ldur	s6, [x9, #-8]
	fmadd	s5, s22, s6, s5
	fmul	s6, s1, s13
	fmadd	s3, s0, s3, s6
	fmul	s6, s3, s2
	fmov	s3, s13
	fmadd	s13, s7, s5, s6
	str	s13, [x16, x8]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB17_124
; %bb.125:                              ;   in Loop: Header=BB17_7 Depth=1
	add	x8, sp, #3632
	ldur	q0, [x8, #128]
	ldr	x8, [sp, #2736]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2728]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #18832]
	ldr	s0, [x19, #368]
	ldr	s1, [x19, #372]
	add	x8, sp, #2464
	ldr	s2, [x8, #16380]
	mov	x8, x30
	mov	w9, #16                         ; =0x10
	ldr	s6, [sp, #892]                  ; 4-byte Folded Reload
	ldr	s22, [sp, #316]                 ; 4-byte Folded Reload
	add	x11, sp, #4, lsl #12            ; =16384
	add	x11, x11, #2448
	ldr	s7, [sp, #2500]                 ; 4-byte Folded Reload
LBB17_126:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s15
	ldr	s15, [x8]
	fmadd	s3, s0, s15, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s2, s6, s3
	str	s2, [x11, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_126
; %bb.127:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x11, #128]
	ldr	x8, [sp, #2728]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	q0, [x19, #640]
	str	q0, [sp, #17696]
	ldr	s0, [x19, #632]
	ldr	s1, [x19, #636]
	add	x8, sp, #1328
	ldr	s2, [x8, #16380]
	mov	x8, x6
	mov	w9, #16                         ; =0x10
	add	x11, sp, #4, lsl #12            ; =16384
	add	x11, x11, #1312
	add	x14, sp, #3, lsl #12            ; =12288
	add	x14, x14, #3136
	add	x30, sp, #4, lsl #12            ; =16384
	add	x30, x30, #176
	ldr	s7, [sp, #2488]                 ; 4-byte Folded Reload
LBB17_128:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s23
	ldr	s23, [x8]
	fmadd	s3, s0, s23, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x11, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_128
; %bb.129:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x11, #128]
	str	q0, [x19, #640]
	ldr	x8, [sp, #2720]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #16560]
	ldr	s0, [x19, #896]
	ldr	s1, [x19, #900]
	add	x8, sp, #192
	ldr	s2, [x8, #16380]
	ldr	x8, [sp, #3264]                 ; 8-byte Folded Reload
	mov	w9, #16                         ; =0x10
	add	x11, sp, #3, lsl #12            ; =12288
	add	x11, x11, #864
	add	x6, sp, #3, lsl #12             ; =12288
	add	x6, x6, #2000
	ldr	s7, [sp, #2480]                 ; 4-byte Folded Reload
LBB17_130:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s24
	ldr	s24, [x8]
	fmadd	s3, s0, s24, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x30, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_130
; %bb.131:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x30, #128]
	ldr	x8, [sp, #2720]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2712]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #15424]
	ldr	s0, [x19, #1160]
	ldr	s1, [x19, #1164]
	ldr	s2, [sp, #15436]
	ldr	x8, [sp, #3328]                 ; 8-byte Folded Reload
	mov	w9, #16                         ; =0x10
	ldr	s7, [sp, #2588]                 ; 4-byte Folded Reload
LBB17_132:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s25
	ldr	s25, [x8]
	fmadd	s3, s0, s25, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x14, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_132
; %bb.133:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x14, #128]
	ldr	x8, [sp, #2712]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2704]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #14288]
	ldr	s0, [x19, #1424]
	ldr	s1, [x19, #1428]
	ldr	s2, [sp, #14300]
	ldr	x8, [sp, #3272]                 ; 8-byte Folded Reload
	mov	w9, #16                         ; =0x10
	ldr	s7, [sp, #2576]                 ; 4-byte Folded Reload
LBB17_134:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s26
	ldr	s26, [x8]
	fmadd	s3, s0, s26, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x6, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_134
; %bb.135:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x6, #128]
	ldr	x8, [sp, #2704]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2696]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #13152]
	ldr	s0, [x19, #1688]
	ldr	s1, [x19, #1692]
	ldr	s2, [sp, #13164]
	mov	x8, x7
	mov	w9, #16                         ; =0x10
	add	x14, sp, #1, lsl #12            ; =4096
	add	x14, x14, #2240
	ldr	s7, [sp, #2572]                 ; 4-byte Folded Reload
LBB17_136:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s27
	ldr	s27, [x8]
	fmadd	s3, s0, s27, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x11, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_136
; %bb.137:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x11, #128]
	ldr	x8, [sp, #2696]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2688]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #12016]
	ldr	s0, [x19, #1952]
	ldr	s1, [x19, #1956]
	ldr	s2, [sp, #12028]
	mov	x8, x5
	mov	w9, #16                         ; =0x10
	add	x5, sp, #2, lsl #12             ; =8192
	add	x5, x5, #3824
	ldr	s7, [sp, #2560]                 ; 4-byte Folded Reload
LBB17_138:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s28
	ldr	s28, [x8]
	fmadd	s3, s0, s28, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x5, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_138
; %bb.139:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x5, #128]
	ldr	x8, [sp, #2688]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2680]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #10880]
	ldr	s0, [x19, #2216]
	ldr	s1, [x19, #2220]
	ldr	s2, [sp, #10892]
	mov	x8, x21
	mov	w9, #16                         ; =0x10
	add	x5, sp, #2, lsl #12             ; =8192
	add	x5, x5, #2688
	add	x11, sp, #4064
	ldr	s7, [sp, #2556]                 ; 4-byte Folded Reload
LBB17_140:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s30
	ldr	s30, [x8]
	fmadd	s3, s0, s30, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x5, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_140
; %bb.141:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x5, #128]
	ldr	x8, [sp, #2680]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2672]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #9744]
	ldr	s0, [x19, #2480]
	ldr	s1, [x19, #2484]
	ldr	s2, [sp, #9756]
	mov	x8, x3
	mov	w9, #16                         ; =0x10
	ldr	s7, [sp, #2544]                 ; 4-byte Folded Reload
LBB17_142:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s31
	ldr	s31, [x8]
	fmadd	s3, s0, s31, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s7, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x2, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_142
; %bb.143:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x2, #128]
	ldr	x8, [sp, #2672]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2664]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #8608]
	ldr	s0, [x19, #2744]
	ldr	s1, [x19, #2748]
	ldr	s2, [sp, #8620]
	mov	x8, x1
	mov	w9, #16                         ; =0x10
LBB17_144:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s8
	ldr	s8, [x8]
	fmadd	s3, s0, s8, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s16, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x0, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_144
; %bb.145:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x0, #128]
	ldr	x8, [sp, #2664]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2656]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #7472]
	ldr	s0, [x19, #3008]
	ldr	s1, [x19, #3012]
	ldr	s2, [sp, #7484]
	mov	x8, x17
	mov	w9, #16                         ; =0x10
	add	x17, sp, #1, lsl #12            ; =4096
	add	x17, x17, #3376
LBB17_146:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s9
	ldr	s9, [x8]
	fmadd	s3, s0, s9, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s17, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x17, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_146
; %bb.147:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x17, #128]
	ldr	x8, [sp, #2656]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2648]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #6336]
	ldr	s0, [x19, #3272]
	ldr	s1, [x19, #3276]
	ldr	s2, [sp, #6348]
	mov	x8, x15
	mov	w9, #16                         ; =0x10
LBB17_148:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s10
	ldr	s10, [x8]
	fmadd	s3, s0, s10, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s18, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x14, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_148
; %bb.149:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x14, #128]
	ldr	x8, [sp, #2648]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2640]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #5200]
	ldr	s0, [x19, #3536]
	ldr	s1, [x19, #3540]
	ldr	s2, [sp, #5212]
	mov	x8, x13
	mov	w9, #16                         ; =0x10
	add	x13, sp, #1, lsl #12            ; =4096
	add	x13, x13, #1104
LBB17_150:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s11
	ldr	s11, [x8]
	fmadd	s3, s0, s11, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s19, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x13, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_150
; %bb.151:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x13, #128]
	ldr	x8, [sp, #2640]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2632]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #4064]
	ldr	s0, [x19, #3800]
	ldr	s1, [x19, #3804]
	ldr	s2, [sp, #4076]
	mov	x8, x12
	mov	w9, #16                         ; =0x10
LBB17_152:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s12
	ldr	s12, [x8]
	fmadd	s3, s0, s12, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s20, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x11, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_152
; %bb.153:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x11, #128]
	ldr	x8, [sp, #2632]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	x8, [sp, #2624]                 ; 8-byte Folded Reload
	ldr	q0, [x8]
	str	q0, [sp, #3488]
	ldr	s0, [x19, #3928]
	ldr	s1, [x19, #3932]
	ldr	s2, [sp, #3500]
	mov	x8, x16
	mov	w9, #16                         ; =0x10
LBB17_154:                              ;   Parent Loop BB17_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	fmul	s3, s1, s4
	ldr	s4, [x8]
	fmadd	s3, s0, s4, s3
	ldur	s5, [x8, #-8]
	fmadd	s3, s0, s5, s3
	fmul	s3, s21, s3
	fabs	s3, s3
	fmul	s3, s22, s3
	fmadd	s2, s6, s2, s3
	str	s2, [x10, x9]
	add	x9, x9, #4
	add	x8, x8, #4
	cmp	x9, #144
	b.ne	LBB17_154
; %bb.155:                              ;   in Loop: Header=BB17_7 Depth=1
	ldur	q0, [x10, #128]
	ldr	x8, [sp, #2624]                 ; 8-byte Folded Reload
	str	q0, [x8]
	ldr	q0, [sp, #19472]
	ldr	q1, [sp, #19488]
	str	q0, [sp, #3424]
	str	q1, [sp, #3440]
	ldr	q0, [sp, #19504]
	ldr	q1, [sp, #19520]
	str	q0, [sp, #3456]
	str	q1, [sp, #3472]
	ldr	q0, [sp, #19408]
	ldr	q1, [sp, #19424]
	str	q0, [sp, #3360]
	str	q1, [sp, #3376]
	ldr	q0, [sp, #19440]
	ldr	q1, [sp, #19456]
	str	q0, [sp, #3392]
	str	q1, [sp, #3408]
	ldr	s0, [sp, #3628]
	str	s0, [sp, #2592]                 ; 4-byte Folded Spill
	ldr	s0, [sp, #4204]
	str	s0, [sp, #2588]                 ; 4-byte Folded Spill
	ldr	s0, [sp, #5340]
	str	s0, [sp, #2572]                 ; 4-byte Folded Spill
	ldr	s0, [sp, #6476]
	str	s0, [sp, #2556]                 ; 4-byte Folded Spill
	ldr	s0, [sp, #7612]
	str	s0, [sp, #2532]                 ; 4-byte Folded Spill
	ldr	s0, [sp, #8748]
	str	s0, [sp, #2516]                 ; 4-byte Folded Spill
	ldr	s0, [sp, #9884]
	str	s0, [sp, #2500]                 ; 4-byte Folded Spill
	ldr	s0, [sp, #11020]
	str	s0, [sp, #2480]                 ; 4-byte Folded Spill
	ldr	s11, [sp, #12156]
	ldr	s12, [sp, #13292]
	ldr	s13, [sp, #14428]
	ldr	s14, [sp, #15564]
	add	x8, sp, #320
	ldr	s8, [x8, #16380]
	add	x8, sp, #1456
	ldr	s15, [x8, #16380]
	add	x8, sp, #2592
	ldr	s0, [x8, #16380]
	bl	_log10f
	ldr	s10, [sp, #340]                 ; 4-byte Folded Reload
	fmov	s9, #20.00000000
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	str	d0, [sp, #2576]                 ; 8-byte Folded Spill
	fmov	s0, s15
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	str	d0, [sp, #2560]                 ; 8-byte Folded Spill
	fmov	s0, s8
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	str	d0, [sp, #2544]                 ; 8-byte Folded Spill
	fmov	s0, s14
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	str	d0, [sp, #2536]                 ; 8-byte Folded Spill
	fmov	s0, s13
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	str	d0, [sp, #2520]                 ; 8-byte Folded Spill
	fmov	s0, s12
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	str	d0, [sp, #2504]                 ; 8-byte Folded Spill
	fmov	s0, s11
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	str	d0, [sp, #2488]                 ; 8-byte Folded Spill
	ldr	s0, [sp, #2480]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	str	d0, [sp, #2480]                 ; 8-byte Folded Spill
	ldr	s0, [sp, #2500]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d11, s0
	ldr	s0, [sp, #2516]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d15, s0
	ldr	s0, [sp, #2532]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d8, s0
	ldr	s0, [sp, #2556]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d14, s0
	ldr	s0, [sp, #2572]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d13, s0
	ldr	s0, [sp, #2588]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s9, s10
	fcvt	d12, s0
	ldr	s0, [sp, #2592]                 ; 4-byte Folded Reload
	bl	_log10f
	ldr	d1, [sp, #2576]                 ; 8-byte Folded Reload
	str	d1, [x19, #3960]
	fmadd	s0, s0, s9, s10
	fcvt	d0, s0
	ldr	d1, [sp, #2560]                 ; 8-byte Folded Reload
	str	d1, [x19, #3968]
	ldr	d1, [sp, #2544]                 ; 8-byte Folded Reload
	str	d1, [x19, #3976]
	ldr	d1, [sp, #2536]                 ; 8-byte Folded Reload
	str	d1, [x19, #3984]
	ldr	d1, [sp, #2520]                 ; 8-byte Folded Reload
	str	d1, [x19, #3992]
	ldr	d1, [sp, #2504]                 ; 8-byte Folded Reload
	str	d1, [x19, #4000]
	ldr	d1, [sp, #2488]                 ; 8-byte Folded Reload
	str	d1, [x19, #4008]
	ldr	d1, [sp, #2480]                 ; 8-byte Folded Reload
	str	d1, [x19, #4016]
	str	d11, [x19, #4024]
	str	d15, [x19, #4032]
	str	d8, [x19, #4040]
	str	d14, [x19, #4048]
	str	d13, [x19, #4056]
	str	d12, [x19, #4064]
	str	d0, [x19, #4072]
	ldr	d1, [sp, #3360]
	ldr	d0, [sp, #3360]
	fcvtl	v2.2d, v1.2s
	ldr	d3, [sp, #3368]
	ldr	d1, [sp, #3368]
	fcvtl	v3.2d, v3.2s
	ldr	x8, [sp, #2616]                 ; 8-byte Folded Reload
	stp	q2, q3, [x8]
	ldr	d3, [sp, #3376]
	ldr	d2, [sp, #3376]
	fcvtl	v4.2d, v3.2s
	ldr	d5, [sp, #3384]
	ldr	d3, [sp, #3384]
	fcvtl	v5.2d, v5.2s
	stp	q4, q5, [x8, #32]
	ldr	d5, [sp, #3392]
	ldr	d4, [sp, #3392]
	fcvtl	v6.2d, v5.2s
	ldr	d7, [sp, #3400]
	ldr	d5, [sp, #3400]
	fcvtl	v7.2d, v7.2s
	stp	q6, q7, [x8, #64]
	ldr	d7, [sp, #3408]
	ldr	d6, [sp, #3408]
	fcvtl	v16.2d, v7.2s
	ldr	d17, [sp, #3416]
	ldr	d7, [sp, #3416]
	fcvtl	v17.2d, v17.2s
	stp	q16, q17, [x8, #96]
	ldr	d16, [sp, #3424]
	ldr	d17, [sp, #3424]
	fcvtl	v16.2d, v16.2s
	ldr	d18, [sp, #3432]
	ldr	d19, [sp, #3432]
	fcvtl	v18.2d, v18.2s
	stp	q16, q18, [x8, #128]
	ldr	d16, [sp, #3440]
	ldr	d18, [sp, #3440]
	fcvtl	v16.2d, v16.2s
	ldr	d20, [sp, #3448]
	ldr	d21, [sp, #3448]
	fcvtl	v20.2d, v20.2s
	stp	q16, q20, [x8, #160]
	ldr	d16, [sp, #3456]
	ldr	d20, [sp, #3456]
	fcvtl	v16.2d, v16.2s
	ldr	d22, [sp, #3464]
	ldr	d23, [sp, #3464]
	fcvtl	v22.2d, v22.2s
	stp	q16, q22, [x8, #192]
	ldr	d16, [sp, #3472]
	ldr	d22, [sp, #3472]
	fcvtl	v16.2d, v16.2s
	ldr	d24, [sp, #3480]
	ldr	d25, [sp, #3480]
	fcvtl	v24.2d, v24.2s
	stp	q16, q24, [x8, #224]
	ldr	x10, [sp, #3192]                ; 8-byte Folded Reload
	ldr	x8, [sp, #352]                  ; 8-byte Folded Reload
	add	x8, x8, x10, lsl #3
	fcvtl	v0.2d, v0.2s
	fcvtl	v1.2d, v1.2s
	stp	q0, q1, [x8]
	fcvtl	v0.2d, v2.2s
	fcvtl	v1.2d, v3.2s
	stp	q0, q1, [x8, #32]
	fcvtl	v0.2d, v4.2s
	fcvtl	v1.2d, v5.2s
	stp	q0, q1, [x8, #64]
	fcvtl	v0.2d, v6.2s
	fcvtl	v1.2d, v7.2s
	stp	q0, q1, [x8, #96]
	fcvtl	v0.2d, v17.2s
	fcvtl	v1.2d, v19.2s
	stp	q0, q1, [x8, #128]
	fcvtl	v0.2d, v18.2s
	fcvtl	v1.2d, v21.2s
	stp	q0, q1, [x8, #160]
	fcvtl	v0.2d, v20.2s
	fcvtl	v1.2d, v23.2s
	stp	q0, q1, [x8, #192]
	fcvtl	v0.2d, v22.2s
	fcvtl	v1.2d, v25.2s
	add	x10, x10, #32
	stp	q0, q1, [x8, #224]
	ldr	x8, [sp, #304]                  ; 8-byte Folded Reload
	cmp	x10, x8
	ldr	s8, [sp, #292]                  ; 4-byte Folded Reload
	ldr	s9, [sp, #288]                  ; 4-byte Folded Reload
	ldr	s10, [sp, #284]                 ; 4-byte Folded Reload
	ldr	s1, [sp, #820]                  ; 4-byte Folded Reload
	ldr	s2, [sp, #280]                  ; 4-byte Folded Reload
	fmov	s11, #1.00000000
	fmov	s12, #-1.00000000
	b.ls	LBB17_7
; %bb.156:
	ldr	s12, [sp, #892]                 ; 4-byte Folded Reload
	ldr	s13, [sp, #316]                 ; 4-byte Folded Reload
	ldr	x4, [sp, #864]                  ; 8-byte Folded Reload
	ldr	x5, [sp, #856]                  ; 8-byte Folded Reload
	ldr	x6, [sp, #848]                  ; 8-byte Folded Reload
	ldr	x7, [sp, #840]                  ; 8-byte Folded Reload
	ldr	x22, [sp, #832]                 ; 8-byte Folded Reload
	ldr	x30, [sp, #824]                 ; 8-byte Folded Reload
	ldr	x0, [sp, #592]                  ; 8-byte Folded Reload
	ldr	w15, [sp, #3336]                ; 4-byte Folded Reload
	ldr	x16, [sp, #704]                 ; 8-byte Folded Reload
	ldr	x17, [sp, #696]                 ; 8-byte Folded Reload
	ldr	w8, [sp, #12]                   ; 4-byte Folded Reload
	subs	w1, w8, w10
	ldr	x26, [sp, #872]                 ; 8-byte Folded Reload
	b.le	LBB17_776
LBB17_157:
	ldur	q0, [x19, #88]
	str	q0, [sp, #21040]
	cmp	w1, #1
	b.lt	LBB17_160
; %bb.158:
	add	x8, sp, #5, lsl #12             ; =20480
	add	x8, x8, #560
	add	x8, x8, #16
	ldr	s0, [x28, #1516]
	mov	x9, x1
LBB17_159:                              ; =>This Inner Loop Header: Depth=1
	fmadd	s0, s0, s1, s2
	str	s0, [x8], #4
	subs	x9, x9, #1
	b.ne	LBB17_159
LBB17_160:
	sxtw	x9, w1
	sbfiz	x8, x1, #2, #32
	add	x12, x9, #1
	str	x9, [sp, #3144]                 ; 8-byte Folded Spill
	add	x9, x9, #3
	str	x9, [sp, #3136]                 ; 8-byte Folded Spill
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #560
	ldr	q0, [x9, x8]
	stur	q0, [x19, #88]
	cmp	w1, #0
	str	x1, [sp, #3120]                 ; 8-byte Folded Spill
	str	x10, [sp, #3192]                ; 8-byte Folded Spill
	b.le	LBB17_163
; %bb.161:
	ldr	s0, [x19, #104]
	cmp	w1, #4
	str	x12, [sp, #3128]                ; 8-byte Folded Spill
	b.hs	LBB17_164
; %bb.162:
	mov	x8, #0                          ; =0x0
	b	LBB17_173
LBB17_163:
	ldur	q0, [x19, #124]
	str	q0, [sp, #20368]
	b	LBB17_190
LBB17_164:
	cmp	w1, #16
	b.hs	LBB17_166
; %bb.165:
	mov	x8, #0                          ; =0x0
	b	LBB17_170
LBB17_166:
	and	x8, x1, #0x7ffffff0
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #432
	add	x9, x9, #32
	add	x10, sp, #5, lsl #12            ; =20480
	add	x10, x10, #560
	add	x10, x10, #32
	mov	x11, x8
LBB17_167:                              ; =>This Inner Loop Header: Depth=1
	ldp	q1, q2, [x10, #-16]
	ldp	q3, q4, [x10, #16]
	fmul.4s	v1, v1, v0[0]
	fmul.4s	v2, v2, v0[0]
	fmul.4s	v3, v3, v0[0]
	fmul.4s	v4, v4, v0[0]
	stp	q1, q2, [x9, #-32]
	stp	q3, q4, [x9], #64
	add	x10, x10, #64
	subs	x11, x11, #16
	b.ne	LBB17_167
; %bb.168:
	cmp	x8, x1
	b.eq	LBB17_175
; %bb.169:
	tst	x1, #0xc
	b.eq	LBB17_173
LBB17_170:
	mov	x11, x8
	and	x8, x1, #0x7ffffffc
	lsl	x10, x11, #2
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #560
	add	x9, x10, x9
	add	x9, x9, #16
	add	x12, sp, #5, lsl #12            ; =20480
	add	x12, x12, #432
	add	x10, x12, x10
	sub	x11, x11, x8
LBB17_171:                              ; =>This Inner Loop Header: Depth=1
	ldr	q1, [x9], #16
	fmul.4s	v1, v1, v0[0]
	str	q1, [x10], #16
	adds	x11, x11, #4
	b.ne	LBB17_171
; %bb.172:
	cmp	x8, x1
	b.eq	LBB17_175
LBB17_173:
	lsl	x10, x8, #2
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #432
	add	x9, x9, x10
	add	x11, sp, #5, lsl #12            ; =20480
	add	x11, x11, #560
	add	x10, x10, x11
	add	x10, x10, #16
	sub	x8, x1, x8
LBB17_174:                              ; =>This Inner Loop Header: Depth=1
	ldr	s1, [x10], #4
	fmul	s1, s0, s1
	str	s1, [x9], #4
	subs	x8, x8, #1
	b.ne	LBB17_174
LBB17_175:
	mov	x26, x0
	cmp	w1, #1
	b.ne	LBB17_177
; %bb.176:
	mov	x24, #0                         ; =0x0
	b	LBB17_180
LBB17_177:
	and	x21, x1, #0x7ffffffe
	add	x22, sp, #5, lsl #12            ; =20480
	add	x22, x22, #432
	add	x23, sp, #5, lsl #12            ; =20480
	add	x23, x23, #304
	mov	x24, x21
LBB17_178:                              ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x22], #8
	str	q0, [sp, #3152]                 ; 16-byte Folded Spill
	mov	s0, v0[1]
	bl	_sinf
                                        ; kill: def $s0 killed $s0 def $q0
	str	q0, [sp, #3168]                 ; 16-byte Folded Spill
	ldr	q0, [sp, #3152]                 ; 16-byte Folded Reload
                                        ; kill: def $s0 killed $s0 killed $q0
	bl	_sinf
                                        ; kill: def $s0 killed $s0 def $q0
	ldr	q1, [sp, #3168]                 ; 16-byte Folded Reload
	mov.s	v0[1], v1[0]
	str	d0, [x23], #8
	subs	x21, x21, #2
	b.ne	LBB17_178
; %bb.179:
	ldr	x8, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	x24, x8
	b.eq	LBB17_182
LBB17_180:
	lsl	x8, x24, #2
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #304
	add	x21, x9, x8
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #432
	add	x22, x9, x8
	ldr	x8, [sp, #3120]                 ; 8-byte Folded Reload
	sub	x23, x8, x24
LBB17_181:                              ; =>This Inner Loop Header: Depth=1
	ldr	s0, [x22], #4
	bl	_sinf
	str	s0, [x21], #4
	subs	x23, x23, #1
	b.ne	LBB17_181
LBB17_182:
	ldr	x8, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	w8, #1
	b.ne	LBB17_184
; %bb.183:
	mov	x24, #0                         ; =0x0
	b	LBB17_187
LBB17_184:
	and	x24, x8, #0x7ffffffe
	add	x22, sp, #5, lsl #12            ; =20480
	add	x22, x22, #432
	add	x23, sp, #5, lsl #12            ; =20480
	add	x23, x23, #176
	mov	x21, x24
LBB17_185:                              ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x22], #8
	str	q0, [sp, #3152]                 ; 16-byte Folded Spill
	mov	s0, v0[1]
	bl	_cosf
                                        ; kill: def $s0 killed $s0 def $q0
	str	q0, [sp, #3168]                 ; 16-byte Folded Spill
	ldr	q0, [sp, #3152]                 ; 16-byte Folded Reload
                                        ; kill: def $s0 killed $s0 killed $q0
	bl	_cosf
                                        ; kill: def $s0 killed $s0 def $q0
	ldr	q1, [sp, #3168]                 ; 16-byte Folded Reload
	mov.s	v0[1], v1[0]
	str	d0, [x23], #8
	subs	x21, x21, #2
	b.ne	LBB17_185
; %bb.186:
	ldr	x8, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	x24, x8
	b.eq	LBB17_189
LBB17_187:
	lsl	x8, x24, #2
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #176
	add	x21, x9, x8
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #432
	add	x22, x9, x8
	ldr	x8, [sp, #3120]                 ; 8-byte Folded Reload
	sub	x23, x8, x24
LBB17_188:                              ; =>This Inner Loop Header: Depth=1
	ldr	s0, [x22], #4
	bl	_cosf
	str	s0, [x21], #4
	subs	x23, x23, #1
	b.ne	LBB17_188
LBB17_189:
	ldur	q0, [x19, #124]
	str	q0, [sp, #20368]
	ldr	x8, [sp, #3192]                 ; 8-byte Folded Reload
	mvn	w8, w8
	ldr	w9, [sp, #12]                   ; 4-byte Folded Reload
	add	w8, w8, w9
	ubfiz	x8, x8, #2, #32
Lloh283:
	adrp	x1, l_.memset_pattern.127@PAGE
Lloh284:
	add	x1, x1, l_.memset_pattern.127@PAGEOFF
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3984
	add	x0, x9, #16
	add	x2, x8, #4
	bl	_memset_pattern16
	ldr	x21, [sp, #584]                 ; 8-byte Folded Reload
	ldr	x23, [sp, #576]                 ; 8-byte Folded Reload
	ldr	x4, [sp, #864]                  ; 8-byte Folded Reload
	ldr	x5, [sp, #856]                  ; 8-byte Folded Reload
	ldr	x6, [sp, #848]                  ; 8-byte Folded Reload
	ldr	x7, [sp, #840]                  ; 8-byte Folded Reload
	ldr	x22, [sp, #832]                 ; 8-byte Folded Reload
	ldr	x30, [sp, #824]                 ; 8-byte Folded Reload
	mov	x0, x26
	ldr	x26, [sp, #872]                 ; 8-byte Folded Reload
	ldr	w15, [sp, #3336]                ; 4-byte Folded Reload
	ldr	x16, [sp, #704]                 ; 8-byte Folded Reload
	ldr	x17, [sp, #696]                 ; 8-byte Folded Reload
	ldr	x1, [sp, #3120]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #3128]                ; 8-byte Folded Reload
LBB17_190:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3984
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	w9, [x8, x9, lsl #2]
	str	w9, [x19, #124]
	lsl	x9, x12, #2
	str	x9, [sp, #3168]                 ; 8-byte Folded Spill
	ldr	d0, [x8, x9]
	str	d0, [x19, #128]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	w8, [x8, x9, lsl #2]
	str	w8, [x19, #136]
	ldur	q0, [x19, #40]
	str	q0, [sp, #21184]
	cmp	w1, #1
	b.lt	LBB17_193
; %bb.191:
	add	x8, sp, #5, lsl #12             ; =20480
	add	x8, x8, #704
	add	x8, x8, #16
	ldr	s0, [x28, #1660]
	mov	w9, #48759                      ; =0xbe77
	movk	w9, #16255, lsl #16
	fmov	s1, w9
	mov	x9, x1
LBB17_192:                              ; =>This Inner Loop Header: Depth=1
	fmadd	s0, s0, s1, s10
	str	s0, [x8], #4
	subs	x9, x9, #1
	b.ne	LBB17_192
LBB17_193:
	ldr	x8, [sp, #3144]                 ; 8-byte Folded Reload
	lsl	x9, x8, #2
	add	x8, sp, #5, lsl #12             ; =20480
	add	x8, x8, #704
	str	x9, [sp, #3152]                 ; 8-byte Folded Spill
	ldr	q0, [x8, x9]
	stur	q0, [x19, #40]
	ldur	q0, [x19, #108]
	str	q0, [sp, #20512]
	ldur	q0, [x19, #140]
	str	q0, [sp, #20224]
	cmp	w1, #0
	b.le	LBB17_196
; %bb.194:
	ldr	s0, [x28, #700]
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3984
	orr	x8, x8, #0xc
	ldr	s1, [x28, #988]
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #176
	add	x10, sp, #5, lsl #12            ; =20480
	add	x10, x10, #304
	mov	w11, #1                         ; =0x1
	mov	x12, x1
LBB17_195:                              ; =>This Inner Loop Header: Depth=1
	ldr	s2, [x10], #4
	ldr	s3, [x9], #4
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	str	s4, [x16], #4
	ldr	w13, [x8], #4
	sub	w13, w11, w13
	scvtf	s5, w13
	fmadd	s0, s0, s3, s5
	fmsub	s0, s2, s1, s0
	str	s0, [x17], #4
	fmov	s1, s4
	subs	x12, x12, #1
	b.ne	LBB17_195
LBB17_196:
	add	x8, sp, #5, lsl #12             ; =20480
	add	x8, x8, #32
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x8, x9]
	stur	q0, [x19, #108]
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3840
	ldr	q0, [x8, x9]
	stur	q0, [x19, #140]
	ldr	q0, [x19, #16]
	str	q0, [sp, #21328]
	cmp	w1, #0
	b.le	LBB17_199
; %bb.197:
	ldr	s0, [x28, #1804]
	mov	w8, #48759                      ; =0xbe77
	movk	w8, #16255, lsl #16
	fmov	s1, w8
	mov	x8, x1
	ldr	x9, [sp, #3352]                 ; 8-byte Folded Reload
LBB17_198:                              ; =>This Inner Loop Header: Depth=1
	fmadd	s0, s0, s1, s9
	str	s0, [x9], #4
	subs	x8, x8, #1
	b.ne	LBB17_198
LBB17_199:
	add	x8, x19, #292
	str	x8, [sp, #3128]                 ; 8-byte Folded Spill
	add	x8, sp, #5, lsl #12             ; =20480
	add	x8, x8, #848
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x8, x9]
	str	q0, [x19, #16]
	ldur	q0, [x19, #168]
	str	q0, [sp, #20080]
	cmp	w1, #0
	ldr	x24, [sp, #488]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
	b.le	LBB17_205
; %bb.200:
	ldr	s0, [x28, #556]
	mov	w8, #48759                      ; =0xbe77
	movk	w8, #16255, lsl #16
	fmov	s1, w8
	mov	x8, x1
	ldr	x9, [sp, #3344]                 ; 8-byte Folded Reload
LBB17_201:                              ; =>This Inner Loop Header: Depth=1
	fmadd	s0, s0, s1, s8
	str	s0, [x9], #4
	subs	x8, x8, #1
	b.ne	LBB17_201
; %bb.202:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3696
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x8, x9]
	stur	q0, [x19, #168]
	cmp	w1, #0
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	b.le	LBB17_206
; %bb.203:
	cmp	w1, #4
	b.hs	LBB17_207
; %bb.204:
	mov	x8, #0                          ; =0x0
	b	LBB17_216
LBB17_205:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3696
	ldr	q0, [x8, x9]
	stur	q0, [x19, #168]
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
LBB17_206:
	ldr	q0, [x19, #192]
	str	q0, [sp, #19680]
	b	LBB17_235
LBB17_207:
	cmp	w1, #16
	b.hs	LBB17_209
; %bb.208:
	mov	x8, #0                          ; =0x0
	b	LBB17_213
LBB17_209:
	and	x8, x1, #0x7ffffff0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3568
	add	x9, x9, #32
	add	x10, sp, #5, lsl #12            ; =20480
	add	x10, x10, #704
	add	x10, x10, #32
	add	x11, sp, #5, lsl #12            ; =20480
	add	x11, x11, #32
	add	x11, x11, #64
	mov	x12, x8
LBB17_210:                              ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x10, #-16]
	ldp	q2, q3, [x10, #16]
	ldp	q4, q5, [x11, #-48]
	ldp	q6, q7, [x11, #-16]
	fmul.4s	v0, v0, v4
	fmul.4s	v1, v1, v5
	fmul.4s	v2, v2, v6
	fmul.4s	v3, v3, v7
	stp	q0, q1, [x9, #-32]
	stp	q2, q3, [x9], #64
	add	x10, x10, #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_210
; %bb.211:
	cmp	x8, x1
	b.eq	LBB17_218
; %bb.212:
	tst	x1, #0xc
	b.eq	LBB17_216
LBB17_213:
	mov	x12, x8
	and	x8, x1, #0x7ffffffc
	lsl	x11, x12, #2
	add	x10, x11, #16
	add	x9, sp, #5, lsl #12             ; =20480
	add	x9, x9, #704
	add	x9, x9, x10
	add	x13, sp, #5, lsl #12            ; =20480
	add	x13, x13, #32
	add	x10, x13, x10
	add	x13, sp, #4, lsl #12            ; =16384
	add	x13, x13, #3568
	add	x11, x13, x11
	sub	x12, x12, x8
LBB17_214:                              ; =>This Inner Loop Header: Depth=1
	ldr	q0, [x9], #16
	ldr	q1, [x10], #16
	fmul.4s	v0, v0, v1
	str	q0, [x11], #16
	adds	x12, x12, #4
	b.ne	LBB17_214
; %bb.215:
	cmp	x8, x1
	b.eq	LBB17_218
LBB17_216:
	lsl	x10, x8, #2
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3568
	add	x9, x9, x10
	add	x11, x10, #16
	add	x10, sp, #5, lsl #12            ; =20480
	add	x10, x10, #32
	add	x10, x10, x11
	add	x12, sp, #5, lsl #12            ; =20480
	add	x12, x12, #704
	add	x11, x12, x11
	sub	x8, x1, x8
LBB17_217:                              ; =>This Inner Loop Header: Depth=1
	ldr	s0, [x11], #4
	ldr	s1, [x10], #4
	fmul	s0, s0, s1
	str	s0, [x9], #4
	subs	x8, x8, #1
	b.ne	LBB17_217
LBB17_218:
	str	x0, [sp, #592]                  ; 8-byte Folded Spill
	add	x23, sp, #4, lsl #12            ; =16384
	add	x23, x23, #3568
	add	x27, sp, #4, lsl #12            ; =16384
	add	x27, x27, #3440
	fmov	s8, #1.00000000
	fmov	s9, #-1.00000000
	mov	x22, x1
	b	LBB17_220
LBB17_219:                              ;   in Loop: Header=BB17_220 Depth=1
	ldr	x26, [sp, #3352]                ; 8-byte Folded Reload
	ldr	s11, [x26], #4
	ldr	x8, [sp, #3344]                 ; 8-byte Folded Reload
	ldr	s0, [x8], #4
	str	x8, [sp, #3344]                 ; 8-byte Folded Spill
	fadd	s0, s0, s0
	bl	___exp10f
	fmadd	s0, s10, s0, s11
	fminnm	s0, s0, s8
	fmaxnm	s0, s0, s9
	str	s0, [x27], #4
	add	x23, x23, #4
	str	x26, [sp, #3352]                ; 8-byte Folded Spill
	subs	x22, x22, #1
	ldr	w15, [sp, #3336]                ; 4-byte Folded Reload
	b.eq	LBB17_222
LBB17_220:                              ; =>This Inner Loop Header: Depth=1
	movi	d10, #0000000000000000
	cbnz	w15, LBB17_219
; %bb.221:                              ;   in Loop: Header=BB17_220 Depth=1
	ldr	s10, [x23]
	b	LBB17_219
LBB17_222:
	ldr	q0, [x19, #192]
	str	q0, [sp, #19680]
	ldr	x1, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	w1, #4
	b.hs	LBB17_224
; %bb.223:
	mov	x8, #0                          ; =0x0
	ldr	x21, [sp, #584]                 ; 8-byte Folded Reload
	ldr	x23, [sp, #576]                 ; 8-byte Folded Reload
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x4, [sp, #864]                  ; 8-byte Folded Reload
	ldr	x5, [sp, #856]                  ; 8-byte Folded Reload
	ldr	x6, [sp, #848]                  ; 8-byte Folded Reload
	ldr	x7, [sp, #840]                  ; 8-byte Folded Reload
	ldr	x22, [sp, #832]                 ; 8-byte Folded Reload
	ldr	x30, [sp, #824]                 ; 8-byte Folded Reload
	ldr	x0, [sp, #592]                  ; 8-byte Folded Reload
	ldr	x26, [sp, #872]                 ; 8-byte Folded Reload
	b	LBB17_233
LBB17_224:
	cmp	w1, #16
	ldr	x23, [sp, #576]                 ; 8-byte Folded Reload
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x4, [sp, #864]                  ; 8-byte Folded Reload
	ldr	x5, [sp, #856]                  ; 8-byte Folded Reload
	ldr	x6, [sp, #848]                  ; 8-byte Folded Reload
	ldr	x7, [sp, #840]                  ; 8-byte Folded Reload
	ldr	x22, [sp, #832]                 ; 8-byte Folded Reload
	ldr	x30, [sp, #824]                 ; 8-byte Folded Reload
	ldr	x0, [sp, #592]                  ; 8-byte Folded Reload
	b.hs	LBB17_226
; %bb.225:
	mov	x8, #0                          ; =0x0
	ldr	x21, [sp, #584]                 ; 8-byte Folded Reload
	ldr	x26, [sp, #872]                 ; 8-byte Folded Reload
	ldr	q18, [sp, #320]                 ; 16-byte Folded Reload
	b	LBB17_230
LBB17_226:
	and	x8, x1, #0x7ffffff0
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3296
	add	x9, x9, #64
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #3440
	add	x10, x10, #32
	mov	w11, #43691                     ; =0xaaab
	movk	w11, #48810, lsl #16
	dup.4s	v0, w11
	mov	x11, x8
	ldr	x21, [sp, #584]                 ; 8-byte Folded Reload
	ldr	x26, [sp, #872]                 ; 8-byte Folded Reload
	ldr	q18, [sp, #320]                 ; 16-byte Folded Reload
LBB17_227:                              ; =>This Inner Loop Header: Depth=1
	ldp	q1, q2, [x10, #-32]
	ldp	q3, q4, [x10], #64
	fmul.4s	v5, v1, v1
	fmul.4s	v6, v2, v2
	fmul.4s	v7, v3, v3
	fmul.4s	v16, v4, v4
	mov.16b	v17, v18
	fmla.4s	v17, v0, v5
	mov.16b	v5, v18
	fmla.4s	v5, v0, v6
	mov.16b	v6, v18
	fmla.4s	v6, v0, v7
	mov.16b	v7, v18
	fmla.4s	v7, v0, v16
	fmul.4s	v1, v1, v17
	fmul.4s	v2, v2, v5
	fmul.4s	v3, v3, v6
	stp	q1, q2, [x9, #-48]
	fmul.4s	v1, v4, v7
	stp	q3, q1, [x9, #-16]
	add	x9, x9, #64
	subs	x11, x11, #16
	b.ne	LBB17_227
; %bb.228:
	cmp	x8, x1
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
	b.eq	LBB17_235
; %bb.229:
	tst	x1, #0xc
	b.eq	LBB17_233
LBB17_230:
	mov	x11, x8
	and	x8, x1, #0x7ffffffc
	lsl	x10, x11, #2
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3440
	add	x9, x9, x10
	add	x12, sp, #4, lsl #12            ; =16384
	add	x12, x12, #3296
	add	x10, x10, x12
	add	x10, x10, #16
	sub	x11, x11, x8
	mov	w12, #43691                     ; =0xaaab
	movk	w12, #48810, lsl #16
	dup.4s	v0, w12
LBB17_231:                              ; =>This Inner Loop Header: Depth=1
	ldr	q1, [x9], #16
	fmul.4s	v2, v1, v1
	mov.16b	v3, v18
	fmla.4s	v3, v0, v2
	fmul.4s	v1, v1, v3
	str	q1, [x10], #16
	adds	x11, x11, #4
	b.ne	LBB17_231
; %bb.232:
	cmp	x8, x1
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
	b.eq	LBB17_235
LBB17_233:
	lsl	x10, x8, #2
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3296
	add	x9, x10, x9
	add	x9, x9, #16
	add	x11, sp, #4, lsl #12            ; =16384
	add	x11, x11, #3440
	add	x10, x11, x10
	sub	x8, x1, x8
	mov	w11, #43691                     ; =0xaaab
	movk	w11, #48810, lsl #16
	fmov	s0, w11
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
	fmov	s1, #1.00000000
LBB17_234:                              ; =>This Inner Loop Header: Depth=1
	ldr	s2, [x10], #4
	fmul	s3, s2, s2
	fmadd	s3, s3, s0, s1
	fmul	s2, s2, s3
	str	s2, [x9], #4
	subs	x8, x8, #1
	b.ne	LBB17_234
LBB17_235:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3296
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #192]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	stur	d0, [x19, #196]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #204]
	ldr	q0, [x19, #208]
	str	q0, [sp, #19536]
	add	x8, sp, #4, lsl #12             ; =16384
	cmp	w1, #0
	b.le	LBB17_241
; %bb.236:
	add	x8, x8, #3296
	add	x8, x8, #16
	add	x9, x28, #16
	add	x10, sp, #3168
	ldr	s0, [x10, #16380]
	ldr	s2, [x28, #156]
	mov	w10, #47186                     ; =0xb852
	movk	w10, #16254, lsl #16
	fmov	s1, w10
	mov	x10, x1
	ldr	x14, [sp, #600]                 ; 8-byte Folded Reload
LBB17_237:                              ; =>This Inner Loop Header: Depth=1
	ldr	s3, [x8], #4
	fmadd	s0, s0, s1, s3
	fsub	s0, s0, s2
	str	s0, [x9], #4
	fmov	s2, s3
	subs	x10, x10, #1
	b.ne	LBB17_237
; %bb.238:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3152
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x8, x9]
	stur	q0, [x19, #208]
	cmp	w1, #0
	ldp	x28, x27, [sp, #496]            ; 16-byte Folded Reload
	b.le	LBB17_242
; %bb.239:
	cmp	w1, #3
	b.hi	LBB17_243
; %bb.240:
	mov	x16, #0                         ; =0x0
	b	LBB17_246
LBB17_241:
	add	x8, x8, #3152
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x8, x9]
	stur	q0, [x19, #208]
	ldp	x28, x27, [sp, #496]            ; 16-byte Folded Reload
	ldr	x14, [sp, #600]                 ; 8-byte Folded Reload
LBB17_242:
	add	x8, x19, #404
	ldr	q0, [x8]
	str	q0, [sp, #18688]
	b	LBB17_250
LBB17_243:
	str	x0, [sp, #592]                  ; 8-byte Folded Spill
	mov	x9, #0                          ; =0x0
	and	x13, x1, #0x7ffffffc
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #3568
	add	x11, sp, #4, lsl #12            ; =16384
	add	x11, x11, #3152
	add	x12, sp, #4, lsl #12            ; =16384
	add	x12, x12, #3024
	mov	x26, x13
	mov	x8, x15
LBB17_244:                              ; =>This Inner Loop Header: Depth=1
	add	x14, x10, x9
	add	x15, x14, #4
	add	x16, x14, #8
	add	x17, x14, #12
	add	x0, x11, x9
	add	x1, x0, #16
	add	x2, x0, #20
	add	x3, x0, #24
	add	x0, x0, #28
	cmp	w8, #0
	csel	x14, x1, x14, eq
	csel	x15, x2, x15, eq
	csel	x16, x3, x16, eq
	csel	x17, x0, x17, eq
	ldr	s0, [x14]
	ldr	s1, [x15]
	ldr	s2, [x16]
	ldr	s3, [x17]
	add	x14, x12, x9
	stp	s0, s1, [x14]
	stp	s2, s3, [x14, #8]
	add	x9, x9, #16
	subs	x13, x13, #4
	b.ne	LBB17_244
; %bb.245:
	ldr	x1, [sp, #3120]                 ; 8-byte Folded Reload
	mov	x16, x26
	cmp	x26, x1
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	ldr	x0, [sp, #592]                  ; 8-byte Folded Reload
	ldr	x26, [sp, #872]                 ; 8-byte Folded Reload
	ldr	x14, [sp, #600]                 ; 8-byte Folded Reload
	mov	x15, x8
	b.eq	LBB17_248
LBB17_246:
	lsl	x11, x16, #2
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3568
	add	x9, x9, x11
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #3152
	add	x10, x11, x10
	add	x10, x10, #16
	add	x12, sp, #4, lsl #12            ; =16384
	add	x12, x12, #3024
	add	x11, x12, x11
	sub	x8, x1, x16
LBB17_247:                              ; =>This Inner Loop Header: Depth=1
	cmp	w15, #0
	csel	x12, x10, x9, eq
	ldr	s0, [x12]
	str	s0, [x11], #4
	add	x9, x9, #4
	add	x10, x10, #4
	subs	x8, x8, #1
	b.ne	LBB17_247
LBB17_248:
	add	x8, x19, #404
	ldr	q0, [x8]
	str	q0, [sp, #18688]
	ldr	s2, [x19, #392]
	ldr	s0, [x19, #396]
	ldr	s1, [x19, #400]
	fneg	s2, s2
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #3024
	add	x9, sp, #2320
	ldr	s3, [x9, #16380]
	mov	x9, x1
	mov	x10, x14
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_249:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x8], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x9, x9, #1
	b.ne	LBB17_249
LBB17_250:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2304
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #404]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	str	d0, [x19, #408]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #416]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	ldur	q0, [x8, #152]
	str	q0, [sp, #18544]
	cmp	w1, #0
	ldr	x10, [sp, #456]                 ; 8-byte Folded Reload
	b.le	LBB17_253
; %bb.251:
	ldr	s0, [x19, #392]
	ldr	s1, [x19, #424]
	ldr	s2, [x19, #428]
	ldr	s5, [x19, #432]
	ldr	s3, [x19, #436]
	ldr	s4, [x19, #440]
	fneg	s5, s5
	add	x8, sp, #2320
	ldr	s7, [x8, #16380]
	add	x8, sp, #2172
	ldr	s6, [x8, #16380]
	add	x8, sp, #2176
	ldr	s16, [x8, #16380]
	mov	x8, x1
	mov	x9, x10
LBB17_252:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x14]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x14, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x14, x14, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_252
LBB17_253:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2160
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x8, x9]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	stur	q0, [x8, #152]
	ldr	q0, [x19, #480]
	str	q0, [sp, #18400]
	cmp	w1, #0
	b.le	LBB17_259
; %bb.254:
	ldr	s0, [x19, #432]
	ldr	s1, [x19, #460]
	ldr	s2, [x19, #464]
	ldr	s5, [x19, #468]
	ldr	s3, [x19, #472]
	ldr	s4, [x19, #476]
	fneg	s5, s5
	add	x8, sp, #2176
	ldr	s7, [x8, #16380]
	add	x8, sp, #2028
	ldr	s6, [x8, #16380]
	add	x8, sp, #2032
	ldr	s16, [x8, #16380]
	mov	x8, x1
	ldr	x9, [sp, #360]                  ; 8-byte Folded Reload
LBB17_255:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_255
; %bb.256:
	mov	x14, x25
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2016
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x8, x9]
	str	q0, [x19, #480]
	cmp	w1, #0
	b.le	LBB17_260
; %bb.257:
	ldr	s0, [x19, #468]
	ldr	s1, [x19, #496]
	mov	x8, x1
	ldr	s2, [x19, #500]
	cmp	w1, #4
	ldr	x25, [sp, #3200]                ; 8-byte Folded Reload
	b.hs	LBB17_261
; %bb.258:
	mov	x9, #0                          ; =0x0
	b	LBB17_270
LBB17_259:
	mov	x14, x25
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2016
	ldr	q0, [x8, x9]
	str	q0, [x19, #480]
LBB17_260:
	add	x8, x19, #668
	ldr	q0, [x8]
	str	q0, [sp, #17552]
	ldr	x25, [sp, #3200]                ; 8-byte Folded Reload
	b	LBB17_274
LBB17_261:
	cmp	w1, #16
	b.hs	LBB17_263
; %bb.262:
	mov	x9, #0                          ; =0x0
	b	LBB17_267
LBB17_263:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #1888
	add	x10, x10, #32
	add	x11, sp, #4, lsl #12            ; =16384
	add	x11, x11, #2016
	add	x11, x11, #32
	mov	x12, x9
LBB17_264:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_264
; %bb.265:
	cmp	x9, x8
	b.eq	LBB17_272
; %bb.266:
	tst	x8, #0xc
	b.eq	LBB17_270
LBB17_267:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #2016
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #4, lsl #12            ; =16384
	add	x13, x13, #1888
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_268:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_268
; %bb.269:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_272
LBB17_270:
	lsl	x11, x9, #2
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #1888
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #4, lsl #12            ; =16384
	add	x12, x12, #2016
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_271:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_271
LBB17_272:
	add	x9, x19, #668
	ldr	q0, [x9]
	str	q0, [sp, #17552]
	ldr	s2, [x19, #656]
	ldr	s0, [x19, #660]
	ldr	s1, [x19, #664]
	fneg	s2, s2
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #1888
	add	x10, sp, #1184
	ldr	s3, [x10, #16380]
	ldr	x10, [sp, #672]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_273:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_273
LBB17_274:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1168
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #668]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	str	d0, [x19, #672]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #680]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	ldr	q0, [x8, #416]
	str	q0, [sp, #17408]
	cmp	w1, #0
	ldr	x10, [sp, #672]                 ; 8-byte Folded Reload
	b.le	LBB17_277
; %bb.275:
	ldr	s0, [x19, #656]
	ldr	s1, [x19, #688]
	ldr	s2, [x19, #692]
	ldr	s5, [x19, #696]
	ldr	s3, [x19, #700]
	ldr	s4, [x19, #704]
	fneg	s5, s5
	add	x8, sp, #1184
	ldr	s7, [x8, #16380]
	add	x8, sp, #1036
	ldr	s6, [x8, #16380]
	add	x8, sp, #1040
	ldr	s16, [x8, #16380]
	mov	x8, x1
	mov	x9, x14
LBB17_276:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_276
LBB17_277:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1024
	ldr	x10, [sp, #3152]                ; 8-byte Folded Reload
	ldr	q0, [x8, x10]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	str	q0, [x8, #416]
	add	x8, x8, #452
	ldr	q0, [x8]
	str	q0, [sp, #17264]
	cmp	w1, #0
	b.le	LBB17_283
; %bb.278:
	ldr	s0, [x19, #696]
	ldr	s1, [x19, #724]
	ldr	s2, [x19, #728]
	ldr	s5, [x19, #732]
	ldr	s3, [x19, #736]
	ldr	s4, [x19, #740]
	fneg	s5, s5
	add	x9, sp, #1040
	ldr	s7, [x9, #16380]
	add	x9, sp, #892
	ldr	s6, [x9, #16380]
	add	x9, sp, #896
	ldr	s16, [x9, #16380]
	mov	x9, x1
	ldr	x10, [sp, #368]                 ; 8-byte Folded Reload
LBB17_279:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x14]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x14, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x14, x14, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_279
; %bb.280:
	mov	x2, x20
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #880
	ldr	x10, [sp, #3152]                ; 8-byte Folded Reload
	ldr	q0, [x9, x10]
	str	q0, [x8]
	ldr	x8, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	w8, #0
	b.le	LBB17_284
; %bb.281:
	ldr	s0, [x19, #732]
	ldr	s1, [x19, #760]
	ldr	x9, [sp, #3120]                 ; 8-byte Folded Reload
	mov	x8, x9
	ldr	s2, [x19, #764]
	cmp	w9, #4
	ldr	x14, [sp, #3272]                ; 8-byte Folded Reload
	ldr	x15, [sp, #3264]                ; 8-byte Folded Reload
	ldr	x16, [sp, #3256]                ; 8-byte Folded Reload
	ldr	x17, [sp, #3248]                ; 8-byte Folded Reload
	ldr	x1, [sp, #3232]                 ; 8-byte Folded Reload
	ldr	x3, [sp, #3216]                 ; 8-byte Folded Reload
	ldr	x20, [sp, #3208]                ; 8-byte Folded Reload
	b.hs	LBB17_285
; %bb.282:
	mov	x9, #0                          ; =0x0
	b	LBB17_294
LBB17_283:
	mov	x2, x20
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #880
	ldr	q0, [x9, x10]
	str	q0, [x8]
LBB17_284:
	add	x8, x19, #932
	ldr	q0, [x8]
	str	q0, [sp, #16416]
	ldr	x14, [sp, #3272]                ; 8-byte Folded Reload
	ldr	x15, [sp, #3264]                ; 8-byte Folded Reload
	ldr	x16, [sp, #3256]                ; 8-byte Folded Reload
	ldr	x17, [sp, #3248]                ; 8-byte Folded Reload
	ldr	x1, [sp, #3232]                 ; 8-byte Folded Reload
	ldr	x3, [sp, #3216]                 ; 8-byte Folded Reload
	ldr	x20, [sp, #3208]                ; 8-byte Folded Reload
	b	LBB17_298
LBB17_285:
	cmp	w9, #16
	b.hs	LBB17_287
; %bb.286:
	mov	x9, #0                          ; =0x0
	b	LBB17_291
LBB17_287:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #752
	add	x10, x10, #32
	add	x11, sp, #4, lsl #12            ; =16384
	add	x11, x11, #880
	add	x11, x11, #32
	mov	x12, x9
LBB17_288:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_288
; %bb.289:
	cmp	x9, x8
	b.eq	LBB17_296
; %bb.290:
	tst	x8, #0xc
	b.eq	LBB17_294
LBB17_291:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #880
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #4, lsl #12            ; =16384
	add	x13, x13, #752
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_292:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_292
; %bb.293:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_296
LBB17_294:
	lsl	x11, x9, #2
	add	x10, sp, #4, lsl #12            ; =16384
	add	x10, x10, #752
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #4, lsl #12            ; =16384
	add	x12, x12, #880
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_295:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_295
LBB17_296:
	add	x9, x19, #932
	ldr	q0, [x9]
	str	q0, [sp, #16416]
	ldr	s2, [x19, #920]
	ldr	s0, [x19, #924]
	ldr	s1, [x19, #928]
	fneg	s2, s2
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #752
	add	x10, sp, #48
	ldr	s3, [x10, #16380]
	mov	x10, x26
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_297:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_297
LBB17_298:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #32
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #932]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s1, [x8, x9, lsl #2]
	str	d0, [x19, #936]
	str	s1, [x19, #944]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	add	x8, x8, #680
	ldr	q0, [x8]
	str	q0, [sp, #16272]
	ldr	x9, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	w9, #0
	b.le	LBB17_301
; %bb.299:
	ldr	s0, [x19, #920]
	ldr	s1, [x19, #952]
	ldr	s2, [x19, #956]
	ldr	s5, [x19, #960]
	ldr	s3, [x19, #964]
	ldr	s4, [x19, #968]
	fneg	s5, s5
	add	x9, sp, #48
	ldr	s7, [x9, #16380]
	ldr	s6, [sp, #16280]
	ldr	s16, [sp, #16284]
	ldr	x9, [sp, #3120]                 ; 8-byte Folded Reload
	ldr	x10, [sp, #608]                 ; 8-byte Folded Reload
LBB17_300:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x26]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x26, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x26, x26, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_300
LBB17_301:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3984
	ldr	x10, [sp, #3152]                ; 8-byte Folded Reload
	ldr	q0, [x9, x10]
	str	q0, [x8]
	ldr	q0, [x19, #1008]
	str	q0, [sp, #16128]
	ldr	x9, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	w9, #0
	b.le	LBB17_307
; %bb.302:
	ldr	s0, [x19, #960]
	ldr	s1, [x19, #988]
	ldr	s2, [x19, #992]
	ldr	s5, [x19, #996]
	ldr	s3, [x19, #1000]
	ldr	s4, [x19, #1004]
	fneg	s5, s5
	ldr	s7, [sp, #16284]
	ldr	s6, [sp, #16136]
	ldr	s16, [sp, #16140]
	mov	x8, x9
	ldr	x9, [sp, #608]                  ; 8-byte Folded Reload
LBB17_303:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x9]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x9, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x2], #4
	add	x9, x9, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_303
; %bb.304:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3840
	ldr	x9, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x8, x9]
	str	q0, [x19, #1008]
	ldr	x2, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	w2, #0
	b.le	LBB17_308
; %bb.305:
	ldr	s0, [x19, #996]
	ldr	s1, [x19, #1024]
	mov	x8, x2
	ldr	s2, [x19, #1028]
	cmp	w2, #4
	ldr	x26, [sp, #512]                 ; 8-byte Folded Reload
	b.hs	LBB17_309
; %bb.306:
	mov	x9, #0                          ; =0x0
	b	LBB17_318
LBB17_307:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3840
	ldr	q0, [x8, x10]
	str	q0, [x19, #1008]
	mov	x2, x9
LBB17_308:
	add	x8, x19, #1196
	ldr	q0, [x8]
	str	q0, [sp, #15280]
	ldr	x26, [sp, #512]                 ; 8-byte Folded Reload
	b	LBB17_322
LBB17_309:
	cmp	w2, #16
	b.hs	LBB17_311
; %bb.310:
	mov	x9, #0                          ; =0x0
	b	LBB17_315
LBB17_311:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #3712
	add	x10, x10, #32
	add	x11, sp, #3, lsl #12            ; =12288
	add	x11, x11, #3840
	add	x11, x11, #32
	mov	x12, x9
LBB17_312:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_312
; %bb.313:
	cmp	x9, x8
	b.eq	LBB17_320
; %bb.314:
	tst	x8, #0xc
	b.eq	LBB17_318
LBB17_315:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #3840
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #3, lsl #12            ; =12288
	add	x13, x13, #3712
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_316:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_316
; %bb.317:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_320
LBB17_318:
	lsl	x11, x9, #2
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #3712
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #3, lsl #12            ; =12288
	add	x12, x12, #3840
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_319:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_319
LBB17_320:
	add	x9, x19, #1196
	ldr	q0, [x9]
	str	q0, [sp, #15280]
	ldr	s2, [x19, #1184]
	ldr	s0, [x19, #1188]
	ldr	s1, [x19, #1192]
	fneg	s2, s2
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3712
	ldr	s3, [sp, #15292]
	ldr	x10, [sp, #680]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_321:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_321
LBB17_322:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2992
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #1196]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	str	d0, [x19, #1200]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #1208]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	ldr	q0, [x8, #944]
	str	q0, [sp, #15136]
	cmp	w2, #0
	ldr	x10, [sp, #680]                 ; 8-byte Folded Reload
	b.le	LBB17_325
; %bb.323:
	ldr	s0, [x19, #1184]
	ldr	s1, [x19, #1216]
	ldr	s2, [x19, #1220]
	ldr	s5, [x19, #1224]
	ldr	s3, [x19, #1228]
	ldr	s4, [x19, #1232]
	fneg	s5, s5
	ldr	s7, [sp, #15292]
	ldr	s6, [sp, #15144]
	ldr	s16, [sp, #15148]
	mov	x8, x2
	ldr	x9, [sp, #616]                  ; 8-byte Folded Reload
LBB17_324:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_324
LBB17_325:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2848
	ldr	x10, [sp, #3152]                ; 8-byte Folded Reload
	ldr	q0, [x8, x10]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	str	q0, [x8, #944]
	add	x8, x8, #980
	ldr	q0, [x8]
	str	q0, [sp, #14992]
	cmp	w2, #0
	b.le	LBB17_331
; %bb.326:
	ldr	s0, [x19, #1224]
	ldr	s1, [x19, #1252]
	ldr	s2, [x19, #1256]
	ldr	s5, [x19, #1260]
	ldr	s3, [x19, #1264]
	ldr	s4, [x19, #1268]
	fneg	s5, s5
	ldr	s7, [sp, #15148]
	ldr	s6, [sp, #15000]
	ldr	s16, [sp, #15004]
	mov	x9, x2
	ldr	x10, [sp, #616]                 ; 8-byte Folded Reload
	ldr	x2, [sp, #376]                  ; 8-byte Folded Reload
LBB17_327:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x2], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_327
; %bb.328:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2704
	ldr	x10, [sp, #3152]                ; 8-byte Folded Reload
	ldr	q0, [x9, x10]
	str	q0, [x8]
	ldr	x2, [sp, #3120]                 ; 8-byte Folded Reload
	cmp	w2, #0
	b.le	LBB17_332
; %bb.329:
	ldr	s0, [x19, #1260]
	ldr	s1, [x19, #1288]
	mov	x8, x2
	ldr	s2, [x19, #1292]
	cmp	w2, #4
	b.hs	LBB17_333
; %bb.330:
	mov	x9, #0                          ; =0x0
	b	LBB17_342
LBB17_331:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2704
	ldr	q0, [x9, x10]
	str	q0, [x8]
LBB17_332:
	add	x8, x19, #1460
	ldr	q0, [x8]
	str	q0, [sp, #14144]
	b	LBB17_346
LBB17_333:
	cmp	w2, #16
	b.hs	LBB17_335
; %bb.334:
	mov	x9, #0                          ; =0x0
	b	LBB17_339
LBB17_335:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #2576
	add	x10, x10, #32
	add	x11, sp, #3, lsl #12            ; =12288
	add	x11, x11, #2704
	add	x11, x11, #32
	mov	x12, x9
LBB17_336:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_336
; %bb.337:
	cmp	x9, x8
	b.eq	LBB17_344
; %bb.338:
	tst	x8, #0xc
	b.eq	LBB17_342
LBB17_339:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #2704
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #3, lsl #12            ; =12288
	add	x13, x13, #2576
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_340:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_340
; %bb.341:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_344
LBB17_342:
	lsl	x11, x9, #2
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #2576
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #3, lsl #12            ; =12288
	add	x12, x12, #2704
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_343:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_343
LBB17_344:
	add	x9, x19, #1460
	ldr	q0, [x9]
	str	q0, [sp, #14144]
	ldr	s2, [x19, #1448]
	ldr	s0, [x19, #1452]
	ldr	s1, [x19, #1456]
	fneg	s2, s2
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2576
	ldr	s3, [sp, #14156]
	mov	x10, x0
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_345:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_345
LBB17_346:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1856
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #1460]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s1, [x8, x9, lsl #2]
	str	d0, [x19, #1464]
	str	s1, [x19, #1472]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	add	x8, x8, #1208
	ldr	q0, [x8]
	str	q0, [sp, #14000]
	cmp	w2, #0
	b.le	LBB17_349
; %bb.347:
	ldr	s0, [x19, #1448]
	ldr	s1, [x19, #1480]
	ldr	s2, [x19, #1484]
	ldr	s5, [x19, #1488]
	ldr	s3, [x19, #1492]
	ldr	s4, [x19, #1496]
	fneg	s5, s5
	ldr	s7, [sp, #14156]
	ldr	s6, [sp, #14008]
	ldr	s16, [sp, #14012]
	mov	x9, x2
	ldr	x10, [sp, #624]                 ; 8-byte Folded Reload
LBB17_348:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x0]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x0, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x0, x0, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_348
LBB17_349:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1712
	ldr	x0, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x9, x0]
	str	q0, [x8]
	add	x8, x19, #1536
	ldr	q0, [x19, #1536]
	str	q0, [sp, #13856]
	cmp	w2, #0
	b.le	LBB17_355
; %bb.350:
	ldr	s0, [x19, #1488]
	ldr	s1, [x19, #1516]
	ldr	s2, [x19, #1520]
	ldr	s5, [x19, #1524]
	ldr	s3, [x19, #1528]
	ldr	s4, [x19, #1532]
	fneg	s5, s5
	ldr	s7, [sp, #14012]
	ldr	s6, [sp, #13864]
	ldr	s16, [sp, #13868]
	mov	x9, x2
	ldr	x10, [sp, #624]                 ; 8-byte Folded Reload
	ldr	x0, [sp, #384]                  ; 8-byte Folded Reload
LBB17_351:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x0], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_351
; %bb.352:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1568
	ldr	x0, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_356
; %bb.353:
	ldr	s0, [x19, #1524]
	ldr	s1, [x19, #1552]
	mov	x8, x2
	ldr	s2, [x19, #1556]
	cmp	w2, #4
	b.hs	LBB17_357
; %bb.354:
	mov	x9, #0                          ; =0x0
	b	LBB17_366
LBB17_355:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1568
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_356:
	add	x8, x19, #1724
	ldr	q0, [x8]
	str	q0, [sp, #13008]
	b	LBB17_370
LBB17_357:
	cmp	w2, #16
	b.hs	LBB17_359
; %bb.358:
	mov	x9, #0                          ; =0x0
	b	LBB17_363
LBB17_359:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #1440
	add	x10, x10, #32
	add	x11, sp, #3, lsl #12            ; =12288
	add	x11, x11, #1568
	add	x11, x11, #32
	mov	x12, x9
LBB17_360:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_360
; %bb.361:
	cmp	x9, x8
	b.eq	LBB17_368
; %bb.362:
	tst	x8, #0xc
	b.eq	LBB17_366
LBB17_363:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #1568
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #3, lsl #12            ; =12288
	add	x13, x13, #1440
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_364:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_364
; %bb.365:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_368
LBB17_366:
	lsl	x11, x9, #2
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #1440
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #3, lsl #12            ; =12288
	add	x12, x12, #1568
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_367:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_367
LBB17_368:
	add	x9, x19, #1724
	ldr	q0, [x9]
	str	q0, [sp, #13008]
	ldr	s2, [x19, #1712]
	ldr	s0, [x19, #1716]
	ldr	s1, [x19, #1720]
	fneg	s2, s2
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1440
	ldr	s3, [sp, #13020]
	ldr	x10, [sp, #688]                 ; 8-byte Folded Reload
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_369:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_369
LBB17_370:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #720
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #1724]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	str	d0, [x19, #1728]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #1736]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	ldr	q0, [x8, #1472]
	str	q0, [sp, #12864]
	cmp	w2, #0
	ldr	x10, [sp, #688]                 ; 8-byte Folded Reload
	b.le	LBB17_373
; %bb.371:
	ldr	s0, [x19, #1712]
	ldr	s1, [x19, #1744]
	ldr	s2, [x19, #1748]
	ldr	s5, [x19, #1752]
	ldr	s3, [x19, #1756]
	ldr	s4, [x19, #1760]
	fneg	s5, s5
	ldr	s7, [sp, #13020]
	ldr	s6, [sp, #12872]
	ldr	s16, [sp, #12876]
	mov	x8, x2
	ldr	x9, [sp, #632]                  ; 8-byte Folded Reload
LBB17_372:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_372
LBB17_373:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #576
	ldr	q0, [x8, x0]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	str	q0, [x8, #1472]
	add	x8, x8, #1508
	ldr	q0, [x8]
	str	q0, [sp, #12720]
	cmp	w2, #0
	b.le	LBB17_379
; %bb.374:
	ldr	s0, [x19, #1752]
	ldr	s1, [x19, #1780]
	ldr	s2, [x19, #1784]
	ldr	s5, [x19, #1788]
	ldr	s3, [x19, #1792]
	ldr	s4, [x19, #1796]
	fneg	s5, s5
	ldr	s7, [sp, #12876]
	ldr	s6, [sp, #12728]
	ldr	s16, [sp, #12732]
	mov	x9, x2
	ldr	x10, [sp, #632]                 ; 8-byte Folded Reload
	ldr	x0, [sp, #392]                  ; 8-byte Folded Reload
LBB17_375:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x0], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_375
; %bb.376:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #432
	ldr	x0, [sp, #3152]                 ; 8-byte Folded Reload
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_380
; %bb.377:
	ldr	s0, [x19, #1788]
	ldr	s1, [x19, #1816]
	mov	x8, x2
	ldr	s2, [x19, #1820]
	cmp	w2, #4
	b.hs	LBB17_381
; %bb.378:
	mov	x9, #0                          ; =0x0
	b	LBB17_390
LBB17_379:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #432
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_380:
	add	x8, x19, #1988
	ldr	q0, [x8]
	str	q0, [sp, #11872]
	b	LBB17_394
LBB17_381:
	cmp	w2, #16
	b.hs	LBB17_383
; %bb.382:
	mov	x9, #0                          ; =0x0
	b	LBB17_387
LBB17_383:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #304
	add	x10, x10, #32
	add	x11, sp, #3, lsl #12            ; =12288
	add	x11, x11, #432
	add	x11, x11, #32
	mov	x12, x9
LBB17_384:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_384
; %bb.385:
	cmp	x9, x8
	b.eq	LBB17_392
; %bb.386:
	tst	x8, #0xc
	b.eq	LBB17_390
LBB17_387:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #432
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #3, lsl #12            ; =12288
	add	x13, x13, #304
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_388:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_388
; %bb.389:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_392
LBB17_390:
	lsl	x11, x9, #2
	add	x10, sp, #3, lsl #12            ; =12288
	add	x10, x10, #304
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #3, lsl #12            ; =12288
	add	x12, x12, #432
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_391:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_391
LBB17_392:
	add	x9, x19, #1988
	ldr	q0, [x9]
	str	q0, [sp, #11872]
	ldr	s2, [x19, #1976]
	ldr	s0, [x19, #1980]
	ldr	s1, [x19, #1984]
	fneg	s2, s2
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #304
	ldr	s3, [sp, #11884]
	mov	x10, x30
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_393:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_393
LBB17_394:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3680
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #1988]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s1, [x8, x9, lsl #2]
	str	d0, [x19, #1992]
	str	s1, [x19, #2000]
	ldr	x8, [sp, #3128]                 ; 8-byte Folded Reload
	add	x8, x8, #1736
	ldr	q0, [x8]
	str	q0, [sp, #11728]
	cmp	w2, #0
	b.le	LBB17_397
; %bb.395:
	ldr	s0, [x19, #1976]
	ldr	s1, [x19, #2008]
	ldr	s2, [x19, #2012]
	ldr	s5, [x19, #2016]
	ldr	s3, [x19, #2020]
	ldr	s4, [x19, #2024]
	fneg	s5, s5
	ldr	s7, [sp, #11884]
	ldr	s6, [sp, #11736]
	ldr	s16, [sp, #11740]
	mov	x9, x2
	ldr	x10, [sp, #640]                 ; 8-byte Folded Reload
LBB17_396:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x30]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x30, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x30, x30, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_396
LBB17_397:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3536
	ldr	q0, [x9, x0]
	str	q0, [x8]
	add	x8, x19, #2064
	ldr	q0, [x19, #2064]
	str	q0, [sp, #11584]
	cmp	w2, #0
	b.le	LBB17_403
; %bb.398:
	ldr	s0, [x19, #2016]
	ldr	s1, [x19, #2044]
	ldr	s2, [x19, #2048]
	ldr	s5, [x19, #2052]
	ldr	s3, [x19, #2056]
	ldr	s4, [x19, #2060]
	fneg	s5, s5
	ldr	s7, [sp, #11740]
	ldr	s6, [sp, #11592]
	ldr	s16, [sp, #11596]
	mov	x9, x2
	ldr	x10, [sp, #640]                 ; 8-byte Folded Reload
	ldr	x30, [sp, #400]                 ; 8-byte Folded Reload
LBB17_399:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x30], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_399
; %bb.400:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3392
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_404
; %bb.401:
	ldr	s0, [x19, #2052]
	ldr	s1, [x19, #2080]
	mov	x8, x2
	ldr	s2, [x19, #2084]
	cmp	w2, #4
	ldr	x30, [sp, #3128]                ; 8-byte Folded Reload
	b.hs	LBB17_405
; %bb.402:
	mov	x9, #0                          ; =0x0
	b	LBB17_414
LBB17_403:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3392
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_404:
	add	x8, x19, #2252
	ldr	q0, [x8]
	str	q0, [sp, #10736]
	ldr	x30, [sp, #3128]                ; 8-byte Folded Reload
	b	LBB17_418
LBB17_405:
	cmp	w2, #16
	b.hs	LBB17_407
; %bb.406:
	mov	x9, #0                          ; =0x0
	b	LBB17_411
LBB17_407:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #3264
	add	x10, x10, #32
	add	x11, sp, #2, lsl #12            ; =8192
	add	x11, x11, #3392
	add	x11, x11, #32
	mov	x12, x9
LBB17_408:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_408
; %bb.409:
	cmp	x9, x8
	b.eq	LBB17_416
; %bb.410:
	tst	x8, #0xc
	b.eq	LBB17_414
LBB17_411:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #3392
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #2, lsl #12            ; =8192
	add	x13, x13, #3264
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_412:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_412
; %bb.413:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_416
LBB17_414:
	lsl	x11, x9, #2
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #3264
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #2, lsl #12            ; =8192
	add	x12, x12, #3392
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_415:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_415
LBB17_416:
	add	x9, x19, #2252
	ldr	q0, [x9]
	str	q0, [sp, #10736]
	ldr	s2, [x19, #2240]
	ldr	s0, [x19, #2244]
	ldr	s1, [x19, #2248]
	fneg	s2, s2
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3264
	ldr	s3, [sp, #10748]
	mov	x10, x22
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_417:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_417
LBB17_418:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2544
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #2252]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	str	d0, [x19, #2256]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #2264]
	ldr	q0, [x30, #2000]
	str	q0, [sp, #10592]
	cmp	w2, #0
	ldr	x10, [sp, #464]                 ; 8-byte Folded Reload
	b.le	LBB17_421
; %bb.419:
	ldr	s0, [x19, #2240]
	ldr	s1, [x19, #2272]
	ldr	s2, [x19, #2276]
	ldr	s5, [x19, #2280]
	ldr	s3, [x19, #2284]
	ldr	s4, [x19, #2288]
	fneg	s5, s5
	ldr	s7, [sp, #10748]
	ldr	s6, [sp, #10600]
	ldr	s16, [sp, #10604]
	mov	x8, x2
	mov	x9, x10
LBB17_420:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x22]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x22, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x22, x22, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_420
LBB17_421:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2400
	ldr	q0, [x8, x0]
	str	q0, [x30, #2000]
	add	x8, x30, #2036
	ldr	q0, [x8]
	str	q0, [sp, #10448]
	cmp	w2, #0
	b.le	LBB17_427
; %bb.422:
	ldr	s0, [x19, #2280]
	ldr	s1, [x19, #2308]
	ldr	s2, [x19, #2312]
	ldr	s5, [x19, #2316]
	ldr	s3, [x19, #2320]
	ldr	s4, [x19, #2324]
	fneg	s5, s5
	ldr	s7, [sp, #10604]
	ldr	s6, [sp, #10456]
	ldr	s16, [sp, #10460]
	mov	x9, x2
	ldr	x22, [sp, #408]                 ; 8-byte Folded Reload
LBB17_423:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x22], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_423
; %bb.424:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2256
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_428
; %bb.425:
	ldr	s0, [x19, #2316]
	ldr	s1, [x19, #2344]
	mov	x8, x2
	ldr	s2, [x19, #2348]
	cmp	w2, #4
	ldr	x22, [sp, #3224]                ; 8-byte Folded Reload
	b.hs	LBB17_429
; %bb.426:
	mov	x9, #0                          ; =0x0
	b	LBB17_438
LBB17_427:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2256
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_428:
	add	x8, x19, #2516
	ldr	q0, [x8]
	str	q0, [sp, #9600]
	ldr	x22, [sp, #3224]                ; 8-byte Folded Reload
	b	LBB17_442
LBB17_429:
	cmp	w2, #16
	b.hs	LBB17_431
; %bb.430:
	mov	x9, #0                          ; =0x0
	b	LBB17_435
LBB17_431:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #2128
	add	x10, x10, #32
	add	x11, sp, #2, lsl #12            ; =8192
	add	x11, x11, #2256
	add	x11, x11, #32
	mov	x12, x9
LBB17_432:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_432
; %bb.433:
	cmp	x9, x8
	b.eq	LBB17_440
; %bb.434:
	tst	x8, #0xc
	b.eq	LBB17_438
LBB17_435:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #2256
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #2, lsl #12            ; =8192
	add	x13, x13, #2128
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_436:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_436
; %bb.437:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_440
LBB17_438:
	lsl	x11, x9, #2
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #2128
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #2, lsl #12            ; =8192
	add	x12, x12, #2256
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_439:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_439
LBB17_440:
	add	x9, x19, #2516
	ldr	q0, [x9]
	str	q0, [sp, #9600]
	ldr	s2, [x19, #2504]
	ldr	s0, [x19, #2508]
	ldr	s1, [x19, #2512]
	fneg	s2, s2
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2128
	ldr	s3, [sp, #9612]
	mov	x10, x7
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_441:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_441
LBB17_442:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1408
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #2516]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s1, [x8, x9, lsl #2]
	str	d0, [x19, #2520]
	str	s1, [x19, #2528]
	add	x8, x30, #2264
	ldr	q0, [x8]
	str	q0, [sp, #9456]
	cmp	w2, #0
	b.le	LBB17_445
; %bb.443:
	ldr	s0, [x19, #2504]
	ldr	s1, [x19, #2536]
	ldr	s2, [x19, #2540]
	ldr	s5, [x19, #2544]
	ldr	s3, [x19, #2548]
	ldr	s4, [x19, #2552]
	fneg	s5, s5
	ldr	s7, [sp, #9612]
	ldr	s6, [sp, #9464]
	ldr	s16, [sp, #9468]
	mov	x9, x2
	ldr	x10, [sp, #648]                 ; 8-byte Folded Reload
LBB17_444:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x7]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x7, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x7, x7, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_444
LBB17_445:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1264
	ldr	q0, [x9, x0]
	str	q0, [x8]
	add	x8, x19, #2592
	ldr	q0, [x19, #2592]
	str	q0, [sp, #9312]
	cmp	w2, #0
	b.le	LBB17_451
; %bb.446:
	ldr	s0, [x19, #2544]
	ldr	s1, [x19, #2572]
	ldr	s2, [x19, #2576]
	ldr	s5, [x19, #2580]
	ldr	s3, [x19, #2584]
	ldr	s4, [x19, #2588]
	fneg	s5, s5
	ldr	s7, [sp, #9468]
	ldr	s6, [sp, #9320]
	ldr	s16, [sp, #9324]
	mov	x9, x2
	ldr	x10, [sp, #648]                 ; 8-byte Folded Reload
	ldr	x7, [sp, #416]                  ; 8-byte Folded Reload
LBB17_447:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x7], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_447
; %bb.448:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1120
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_452
; %bb.449:
	ldr	s0, [x19, #2580]
	ldr	s1, [x19, #2608]
	mov	x8, x2
	ldr	s2, [x19, #2612]
	cmp	w2, #4
	ldr	x7, [sp, #3240]                 ; 8-byte Folded Reload
	b.hs	LBB17_453
; %bb.450:
	mov	x9, #0                          ; =0x0
	b	LBB17_462
LBB17_451:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1120
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_452:
	add	x8, x19, #2780
	ldr	q0, [x8]
	str	q0, [sp, #8464]
	ldr	x7, [sp, #3240]                 ; 8-byte Folded Reload
	b	LBB17_466
LBB17_453:
	cmp	w2, #16
	b.hs	LBB17_455
; %bb.454:
	mov	x9, #0                          ; =0x0
	b	LBB17_459
LBB17_455:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #992
	add	x10, x10, #32
	add	x11, sp, #2, lsl #12            ; =8192
	add	x11, x11, #1120
	add	x11, x11, #32
	mov	x12, x9
LBB17_456:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_456
; %bb.457:
	cmp	x9, x8
	b.eq	LBB17_464
; %bb.458:
	tst	x8, #0xc
	b.eq	LBB17_462
LBB17_459:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #1120
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #2, lsl #12            ; =8192
	add	x13, x13, #992
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_460:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_460
; %bb.461:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_464
LBB17_462:
	lsl	x11, x9, #2
	add	x10, sp, #2, lsl #12            ; =8192
	add	x10, x10, #992
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #2, lsl #12            ; =8192
	add	x12, x12, #1120
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_463:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_463
LBB17_464:
	add	x9, x19, #2780
	ldr	q0, [x9]
	str	q0, [sp, #8464]
	ldr	s2, [x19, #2768]
	ldr	s0, [x19, #2772]
	ldr	s1, [x19, #2776]
	fneg	s2, s2
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #992
	ldr	s3, [sp, #8476]
	mov	x10, x6
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_465:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_465
LBB17_466:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #272
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #2780]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	str	d0, [x19, #2784]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #2792]
	ldr	q0, [x30, #2528]
	str	q0, [sp, #8320]
	cmp	w2, #0
	ldr	x10, [sp, #472]                 ; 8-byte Folded Reload
	b.le	LBB17_469
; %bb.467:
	ldr	s0, [x19, #2768]
	ldr	s1, [x19, #2800]
	ldr	s2, [x19, #2804]
	ldr	s5, [x19, #2808]
	ldr	s3, [x19, #2812]
	ldr	s4, [x19, #2816]
	fneg	s5, s5
	ldr	s7, [sp, #8476]
	ldr	s6, [sp, #8328]
	ldr	s16, [sp, #8332]
	mov	x8, x2
	mov	x9, x10
LBB17_468:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x6]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x6, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x6, x6, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_468
LBB17_469:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #128
	ldr	q0, [x8, x0]
	str	q0, [x30, #2528]
	add	x8, x30, #2564
	ldr	q0, [x8]
	str	q0, [sp, #8176]
	cmp	w2, #0
	b.le	LBB17_475
; %bb.470:
	ldr	s0, [x19, #2808]
	ldr	s1, [x19, #2836]
	ldr	s2, [x19, #2840]
	ldr	s5, [x19, #2844]
	ldr	s3, [x19, #2848]
	ldr	s4, [x19, #2852]
	fneg	s5, s5
	ldr	s7, [sp, #8332]
	ldr	s6, [sp, #8184]
	ldr	s16, [sp, #8188]
	mov	x9, x2
	ldr	x6, [sp, #424]                  ; 8-byte Folded Reload
LBB17_471:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x6], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_471
; %bb.472:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #4080
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_476
; %bb.473:
	ldr	s0, [x19, #2844]
	ldr	s1, [x19, #2872]
	mov	x8, x2
	ldr	s2, [x19, #2876]
	cmp	w2, #4
	ldr	x6, [sp, #528]                  ; 8-byte Folded Reload
	b.hs	LBB17_477
; %bb.474:
	mov	x9, #0                          ; =0x0
	b	LBB17_486
LBB17_475:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #4080
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_476:
	add	x8, x19, #3044
	ldr	q0, [x8]
	str	q0, [sp, #7328]
	ldr	x6, [sp, #528]                  ; 8-byte Folded Reload
	b	LBB17_490
LBB17_477:
	cmp	w2, #16
	b.hs	LBB17_479
; %bb.478:
	mov	x9, #0                          ; =0x0
	b	LBB17_483
LBB17_479:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #3952
	add	x10, x10, #32
	add	x11, sp, #1, lsl #12            ; =4096
	add	x11, x11, #4080
	add	x11, x11, #32
	mov	x12, x9
LBB17_480:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_480
; %bb.481:
	cmp	x9, x8
	b.eq	LBB17_488
; %bb.482:
	tst	x8, #0xc
	b.eq	LBB17_486
LBB17_483:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #4080
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #1, lsl #12            ; =4096
	add	x13, x13, #3952
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_484:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_484
; %bb.485:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_488
LBB17_486:
	lsl	x11, x9, #2
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #3952
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #1, lsl #12            ; =4096
	add	x12, x12, #4080
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_487:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_487
LBB17_488:
	add	x9, x19, #3044
	ldr	q0, [x9]
	str	q0, [sp, #7328]
	ldr	s2, [x19, #3032]
	ldr	s0, [x19, #3036]
	ldr	s1, [x19, #3040]
	fneg	s2, s2
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3952
	ldr	s3, [sp, #7340]
	mov	x10, x5
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_489:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_489
LBB17_490:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #3232
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #3044]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s1, [x8, x9, lsl #2]
	str	d0, [x19, #3048]
	str	s1, [x19, #3056]
	add	x8, x30, #2792
	ldr	q0, [x8]
	str	q0, [sp, #7184]
	cmp	w2, #0
	b.le	LBB17_493
; %bb.491:
	ldr	s0, [x19, #3032]
	ldr	s1, [x19, #3064]
	ldr	s2, [x19, #3068]
	ldr	s5, [x19, #3072]
	ldr	s3, [x19, #3076]
	ldr	s4, [x19, #3080]
	fneg	s5, s5
	ldr	s7, [sp, #7340]
	ldr	s6, [sp, #7192]
	ldr	s16, [sp, #7196]
	mov	x9, x2
	ldr	x10, [sp, #656]                 ; 8-byte Folded Reload
LBB17_492:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x5]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x5, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x5, x5, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_492
LBB17_493:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3088
	ldr	q0, [x9, x0]
	str	q0, [x8]
	add	x8, x19, #3120
	ldr	q0, [x19, #3120]
	str	q0, [sp, #7040]
	cmp	w2, #0
	b.le	LBB17_499
; %bb.494:
	ldr	s0, [x19, #3072]
	ldr	s1, [x19, #3100]
	ldr	s2, [x19, #3104]
	ldr	s5, [x19, #3108]
	ldr	s3, [x19, #3112]
	ldr	s4, [x19, #3116]
	fneg	s5, s5
	ldr	s7, [sp, #7196]
	ldr	s6, [sp, #7048]
	ldr	s16, [sp, #7052]
	mov	x9, x2
	ldr	x10, [sp, #656]                 ; 8-byte Folded Reload
	ldr	x5, [sp, #432]                  ; 8-byte Folded Reload
LBB17_495:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x5], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_495
; %bb.496:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2944
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_500
; %bb.497:
	ldr	s0, [x19, #3108]
	ldr	s1, [x19, #3136]
	mov	x8, x2
	ldr	s2, [x19, #3140]
	cmp	w2, #4
	b.hs	LBB17_501
; %bb.498:
	mov	x9, #0                          ; =0x0
	b	LBB17_510
LBB17_499:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2944
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_500:
	add	x8, x19, #3308
	ldr	q0, [x8]
	str	q0, [sp, #6192]
	b	LBB17_514
LBB17_501:
	cmp	w2, #16
	b.hs	LBB17_503
; %bb.502:
	mov	x9, #0                          ; =0x0
	b	LBB17_507
LBB17_503:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #2816
	add	x10, x10, #32
	add	x11, sp, #1, lsl #12            ; =4096
	add	x11, x11, #2944
	add	x11, x11, #32
	mov	x12, x9
LBB17_504:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_504
; %bb.505:
	cmp	x9, x8
	b.eq	LBB17_512
; %bb.506:
	tst	x8, #0xc
	b.eq	LBB17_510
LBB17_507:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #2944
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #1, lsl #12            ; =4096
	add	x13, x13, #2816
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_508:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_508
; %bb.509:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_512
LBB17_510:
	lsl	x11, x9, #2
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #2816
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #1, lsl #12            ; =4096
	add	x12, x12, #2944
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_511:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_511
LBB17_512:
	add	x9, x19, #3308
	ldr	q0, [x9]
	str	q0, [sp, #6192]
	ldr	s2, [x19, #3296]
	ldr	s0, [x19, #3300]
	ldr	s1, [x19, #3304]
	fneg	s2, s2
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2816
	ldr	s3, [sp, #6204]
	mov	x10, x4
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
LBB17_513:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_513
LBB17_514:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2096
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #3308]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	str	d0, [x19, #3312]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #3320]
	ldr	q0, [x30, #3056]
	str	q0, [sp, #6048]
	cmp	w2, #0
	ldr	x10, [sp, #480]                 ; 8-byte Folded Reload
	b.le	LBB17_517
; %bb.515:
	ldr	s0, [x19, #3296]
	ldr	s1, [x19, #3328]
	ldr	s2, [x19, #3332]
	ldr	s5, [x19, #3336]
	ldr	s3, [x19, #3340]
	ldr	s4, [x19, #3344]
	fneg	s5, s5
	ldr	s7, [sp, #6204]
	ldr	s6, [sp, #6056]
	ldr	s16, [sp, #6060]
	mov	x8, x2
	mov	x9, x10
LBB17_516:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x4]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x4, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x4, x4, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_516
LBB17_517:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1952
	ldr	q0, [x8, x0]
	str	q0, [x30, #3056]
	add	x8, x30, #3092
	ldr	q0, [x8]
	str	q0, [sp, #5904]
	cmp	w2, #0
	b.le	LBB17_523
; %bb.518:
	ldr	s0, [x19, #3336]
	ldr	s1, [x19, #3364]
	ldr	s2, [x19, #3368]
	ldr	s5, [x19, #3372]
	ldr	s3, [x19, #3376]
	ldr	s4, [x19, #3380]
	fneg	s5, s5
	ldr	s7, [sp, #6060]
	ldr	s6, [sp, #5912]
	ldr	s16, [sp, #5916]
	mov	x9, x2
	ldr	x4, [sp, #440]                  ; 8-byte Folded Reload
LBB17_519:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x4], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_519
; %bb.520:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1808
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_524
; %bb.521:
	ldr	s0, [x19, #3372]
	ldr	s1, [x19, #3400]
	mov	x8, x2
	ldr	s2, [x19, #3404]
	cmp	w2, #4
	b.hs	LBB17_525
; %bb.522:
	mov	x9, #0                          ; =0x0
	b	LBB17_534
LBB17_523:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1808
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_524:
	add	x8, x19, #3572
	ldr	q0, [x8]
	str	q0, [sp, #5056]
	b	LBB17_538
LBB17_525:
	cmp	w2, #16
	b.hs	LBB17_527
; %bb.526:
	mov	x9, #0                          ; =0x0
	b	LBB17_531
LBB17_527:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #1680
	add	x10, x10, #32
	add	x11, sp, #1, lsl #12            ; =4096
	add	x11, x11, #1808
	add	x11, x11, #32
	mov	x12, x9
LBB17_528:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_528
; %bb.529:
	cmp	x9, x8
	b.eq	LBB17_536
; %bb.530:
	tst	x8, #0xc
	b.eq	LBB17_534
LBB17_531:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #1808
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #1, lsl #12            ; =4096
	add	x13, x13, #1680
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_532:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_532
; %bb.533:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_536
LBB17_534:
	lsl	x11, x9, #2
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #1680
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #1, lsl #12            ; =4096
	add	x12, x12, #1808
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_535:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_535
LBB17_536:
	add	x9, x19, #3572
	ldr	q0, [x9]
	str	q0, [sp, #5056]
	ldr	s2, [x19, #3560]
	ldr	s0, [x19, #3564]
	ldr	s1, [x19, #3568]
	fneg	s2, s2
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1680
	ldr	s3, [sp, #5068]
	ldr	x11, [sp, #896]                 ; 8-byte Folded Reload
	mov	x10, x11
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
LBB17_537:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_537
LBB17_538:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #960
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #3572]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s1, [x8, x9, lsl #2]
	str	d0, [x19, #3576]
	str	s1, [x19, #3584]
	add	x8, x30, #3320
	ldr	q0, [x8]
	str	q0, [sp, #4912]
	cmp	w2, #0
	b.le	LBB17_541
; %bb.539:
	ldr	s0, [x19, #3560]
	ldr	s1, [x19, #3592]
	ldr	s2, [x19, #3596]
	ldr	s5, [x19, #3600]
	ldr	s3, [x19, #3604]
	ldr	s4, [x19, #3608]
	fneg	s5, s5
	ldr	s7, [sp, #5068]
	ldr	s6, [sp, #4920]
	ldr	s16, [sp, #4924]
	mov	x9, x2
	ldr	x10, [sp, #664]                 ; 8-byte Folded Reload
LBB17_540:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x11]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x11, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x11, x11, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_540
LBB17_541:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #816
	ldr	q0, [x9, x0]
	str	q0, [x8]
	add	x8, x19, #3648
	ldr	q0, [x19, #3648]
	str	q0, [sp, #4768]
	cmp	w2, #0
	b.le	LBB17_547
; %bb.542:
	ldr	s0, [x19, #3600]
	ldr	s1, [x19, #3628]
	ldr	s2, [x19, #3632]
	ldr	s5, [x19, #3636]
	ldr	s3, [x19, #3640]
	ldr	s4, [x19, #3644]
	fneg	s5, s5
	ldr	s7, [sp, #4924]
	ldr	s6, [sp, #4776]
	ldr	s16, [sp, #4780]
	mov	x9, x2
	ldr	x10, [sp, #664]                 ; 8-byte Folded Reload
	ldr	x11, [sp, #448]                 ; 8-byte Folded Reload
LBB17_543:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x11], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_543
; %bb.544:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #672
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_548
; %bb.545:
	ldr	s0, [x19, #3636]
	ldr	s1, [x19, #3664]
	mov	x8, x2
	ldr	s2, [x19, #3668]
	cmp	w2, #4
	b.hs	LBB17_549
; %bb.546:
	mov	x9, #0                          ; =0x0
	b	LBB17_558
LBB17_547:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #672
	ldr	q0, [x9, x0]
	str	q0, [x8]
LBB17_548:
	ldur	q0, [x19, #252]
	str	q0, [sp, #19264]
	b	LBB17_562
LBB17_549:
	cmp	w2, #16
	b.hs	LBB17_551
; %bb.550:
	mov	x9, #0                          ; =0x0
	b	LBB17_555
LBB17_551:
	dup.4s	v3, v1[0]
	and	x9, x8, #0x7ffffff0
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #544
	add	x10, x10, #32
	add	x11, sp, #1, lsl #12            ; =4096
	add	x11, x11, #672
	add	x11, x11, #32
	mov	x12, x9
LBB17_552:                              ; =>This Inner Loop Header: Depth=1
	ldp	q4, q5, [x11, #-16]
	ldp	q6, q7, [x11, #16]
	ldur	q16, [x11, #-20]
	ldur	q17, [x11, #-4]
	ldur	q18, [x11, #12]
	ldur	q19, [x11, #28]
	fmul.4s	v16, v16, v2[0]
	fmul.4s	v17, v17, v2[0]
	fmul.4s	v18, v18, v2[0]
	fmul.4s	v19, v19, v2[0]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	ldur	q4, [x11, #-24]
	ldur	q5, [x11, #-8]
	ldur	q6, [x11, #8]
	ldur	q7, [x11, #24]
	fmla.4s	v16, v4, v3
	fmla.4s	v17, v5, v3
	fmla.4s	v18, v6, v3
	fmla.4s	v19, v7, v3
	fmul.4s	v4, v16, v0[0]
	fmul.4s	v5, v17, v0[0]
	fmul.4s	v6, v18, v0[0]
	fmul.4s	v7, v19, v0[0]
	stp	q4, q5, [x10, #-32]
	stp	q6, q7, [x10], #64
	add	x11, x11, #64
	subs	x12, x12, #16
	b.ne	LBB17_552
; %bb.553:
	cmp	x9, x8
	b.eq	LBB17_560
; %bb.554:
	tst	x8, #0xc
	b.eq	LBB17_558
LBB17_555:
	mov	x12, x9
	and	x9, x8, #0x7ffffffc
	dup.4s	v3, v1[0]
	lsl	x11, x12, #2
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #672
	add	x10, x11, x10
	add	x10, x10, #16
	add	x13, sp, #1, lsl #12            ; =4096
	add	x13, x13, #544
	add	x11, x13, x11
	sub	x12, x12, x9
LBB17_556:                              ; =>This Inner Loop Header: Depth=1
	ldr	q4, [x10]
	ldur	q5, [x10, #-4]
	fmul.4s	v5, v5, v2[0]
	fmla.4s	v5, v4, v3
	ldur	q4, [x10, #-8]
	fmla.4s	v5, v4, v3
	fmul.4s	v4, v5, v0[0]
	str	q4, [x11], #16
	add	x10, x10, #16
	adds	x12, x12, #4
	b.ne	LBB17_556
; %bb.557:
	cmp	x9, x8
	ldr	x13, [sp, #880]                 ; 8-byte Folded Reload
	b.eq	LBB17_560
LBB17_558:
	lsl	x11, x9, #2
	add	x10, sp, #1, lsl #12            ; =4096
	add	x10, x10, #544
	add	x10, x10, x11
	sub	x9, x8, x9
	add	x12, sp, #1, lsl #12            ; =4096
	add	x12, x12, #672
	add	x11, x11, x12
	add	x11, x11, #16
LBB17_559:                              ; =>This Inner Loop Header: Depth=1
	ldp	s4, s3, [x11, #-4]
	ldur	s5, [x11, #-8]
	fmul	s4, s2, s4
	fmadd	s3, s1, s3, s4
	fmadd	s3, s1, s5, s3
	fmul	s3, s0, s3
	str	s3, [x10], #4
	add	x11, x11, #4
	subs	x9, x9, #1
	b.ne	LBB17_559
LBB17_560:
	ldur	q0, [x19, #252]
	str	q0, [sp, #19264]
	ldp	s2, s0, [x19, #232]
	ldr	s1, [x19, #248]
	fneg	s2, s2
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #3024
	add	x10, sp, #2896
	ldr	s3, [x10, #16380]
	mov	x10, x24
	ldr	x12, [sp, #904]                 ; 8-byte Folded Reload
LBB17_561:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x8, x8, #1
	b.ne	LBB17_561
LBB17_562:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2880
	ldr	x9, [sp, #3144]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #252]
	ldr	x9, [sp, #3168]                 ; 8-byte Folded Reload
	ldr	d0, [x8, x9]
	str	d0, [x19, #256]
	ldr	x9, [sp, #3136]                 ; 8-byte Folded Reload
	ldr	s0, [x8, x9, lsl #2]
	str	s0, [x19, #264]
	ldr	q0, [x30, #240]
	str	q0, [sp, #18128]
	cmp	w2, #0
	b.le	LBB17_565
; %bb.563:
	ldr	s2, [x19, #512]
	ldr	s0, [x19, #516]
	ldr	s1, [x19, #528]
	fneg	s2, s2
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1888
	add	x9, sp, #1760
	ldr	s3, [x9, #16380]
	mov	x9, x2
	ldr	x10, [sp, #728]                 ; 8-byte Folded Reload
LBB17_564:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x8], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x9, x9, #1
	b.ne	LBB17_564
LBB17_565:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1744
	ldr	q0, [x8, x0]
	str	q0, [x30, #240]
	add	x8, x30, #504
	ldr	q0, [x8]
	str	q0, [sp, #16992]
	cmp	w2, #0
	b.le	LBB17_568
; %bb.566:
	ldr	s2, [x19, #776]
	ldr	s0, [x19, #780]
	ldr	s1, [x19, #792]
	fneg	s2, s2
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #752
	add	x10, sp, #624
	ldr	s3, [x10, #16380]
	mov	x10, x2
	ldr	x11, [sp, #744]                 ; 8-byte Folded Reload
LBB17_567:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x11, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x11], #4
	subs	x10, x10, #1
	b.ne	LBB17_567
LBB17_568:
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #608
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #768]
	str	q0, [sp, #15856]
	cmp	w2, #0
	b.le	LBB17_571
; %bb.569:
	ldr	s2, [x19, #1040]
	ldr	s0, [x19, #1044]
	ldr	s1, [x19, #1056]
	fneg	s2, s2
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3712
	ldr	s3, [sp, #15868]
	mov	x9, x2
	ldr	x10, [sp, #712]                 ; 8-byte Folded Reload
LBB17_570:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x8], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x9, x9, #1
	b.ne	LBB17_570
LBB17_571:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3568
	ldr	q0, [x8, x0]
	str	q0, [x30, #768]
	add	x8, x30, #1032
	ldr	q0, [x8]
	str	q0, [sp, #14720]
	cmp	w2, #0
	b.le	LBB17_574
; %bb.572:
	ldr	s2, [x19, #1304]
	ldr	s0, [x19, #1308]
	ldr	s1, [x19, #1320]
	fneg	s2, s2
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2576
	ldr	s3, [sp, #14732]
	mov	x10, x2
	ldr	x11, [sp, #720]                 ; 8-byte Folded Reload
LBB17_573:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x11, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x11], #4
	subs	x10, x10, #1
	b.ne	LBB17_573
LBB17_574:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2432
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #1296]
	str	q0, [sp, #13584]
	cmp	w2, #0
	b.le	LBB17_577
; %bb.575:
	ldr	s2, [x19, #1568]
	ldr	s0, [x19, #1572]
	ldr	s1, [x19, #1584]
	fneg	s2, s2
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1440
	ldr	s3, [sp, #13596]
	mov	x9, x2
	ldr	x10, [sp, #736]                 ; 8-byte Folded Reload
LBB17_576:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x8], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x9, x9, #1
	b.ne	LBB17_576
LBB17_577:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1296
	ldr	q0, [x8, x0]
	str	q0, [x30, #1296]
	add	x8, x30, #1560
	ldr	q0, [x8]
	str	q0, [sp, #12448]
	cmp	w2, #0
	b.le	LBB17_580
; %bb.578:
	ldr	s2, [x19, #1832]
	ldr	s0, [x19, #1836]
	ldr	s1, [x19, #1848]
	fneg	s2, s2
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #304
	ldr	s3, [sp, #12460]
	mov	x10, x2
	ldr	x11, [sp, #752]                 ; 8-byte Folded Reload
LBB17_579:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x11, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x11], #4
	subs	x10, x10, #1
	b.ne	LBB17_579
LBB17_580:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #160
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #1824]
	str	q0, [sp, #11312]
	cmp	w2, #0
	b.le	LBB17_583
; %bb.581:
	ldr	s2, [x19, #2096]
	ldr	s0, [x19, #2100]
	ldr	s1, [x19, #2112]
	fneg	s2, s2
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3264
	ldr	s3, [sp, #11324]
	mov	x9, x2
	ldr	x10, [sp, #760]                 ; 8-byte Folded Reload
LBB17_582:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x8], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x9, x9, #1
	b.ne	LBB17_582
LBB17_583:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3120
	ldr	q0, [x8, x0]
	str	q0, [x30, #1824]
	add	x8, x30, #2088
	ldr	q0, [x8]
	str	q0, [sp, #10176]
	cmp	w2, #0
	b.le	LBB17_586
; %bb.584:
	ldr	s2, [x19, #2360]
	ldr	s0, [x19, #2364]
	ldr	s1, [x19, #2376]
	fneg	s2, s2
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2128
	ldr	s3, [sp, #10188]
	mov	x10, x2
	ldr	x11, [sp, #768]                 ; 8-byte Folded Reload
LBB17_585:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x11, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x11], #4
	subs	x10, x10, #1
	b.ne	LBB17_585
LBB17_586:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1984
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #2352]
	str	q0, [sp, #9040]
	cmp	w2, #0
	b.le	LBB17_589
; %bb.587:
	ldr	s2, [x19, #2624]
	ldr	s0, [x19, #2628]
	ldr	s1, [x19, #2640]
	fneg	s2, s2
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #992
	ldr	s3, [sp, #9052]
	mov	x9, x2
	mov	x10, x12
LBB17_588:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x8], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x9, x9, #1
	b.ne	LBB17_588
LBB17_589:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #848
	ldr	q0, [x8, x0]
	str	q0, [x30, #2352]
	add	x8, x30, #2616
	ldr	q0, [x8]
	str	q0, [sp, #7904]
	cmp	w2, #0
	b.le	LBB17_592
; %bb.590:
	ldr	s2, [x19, #2888]
	ldr	s0, [x19, #2892]
	ldr	s1, [x19, #2904]
	fneg	s2, s2
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3952
	ldr	s3, [sp, #7916]
	mov	x10, x2
	ldr	x11, [sp, #776]                 ; 8-byte Folded Reload
LBB17_591:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x11, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x11], #4
	subs	x10, x10, #1
	b.ne	LBB17_591
LBB17_592:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3808
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #2880]
	str	q0, [sp, #6768]
	cmp	w2, #0
	b.le	LBB17_595
; %bb.593:
	ldr	s2, [x19, #3152]
	ldr	s0, [x19, #3156]
	ldr	s1, [x19, #3168]
	fneg	s2, s2
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2816
	ldr	s3, [sp, #6780]
	mov	x9, x2
	mov	x10, x13
LBB17_594:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x8], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x9, x9, #1
	b.ne	LBB17_594
LBB17_595:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2672
	ldr	q0, [x8, x0]
	str	q0, [x30, #2880]
	add	x8, x30, #3144
	ldr	q0, [x8]
	str	q0, [sp, #5632]
	cmp	w2, #0
	b.le	LBB17_598
; %bb.596:
	ldr	s2, [x19, #3416]
	ldr	s0, [x19, #3420]
	ldr	s1, [x19, #3432]
	fneg	s2, s2
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1680
	ldr	s3, [sp, #5644]
	mov	x10, x2
	mov	x11, x28
LBB17_597:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x11, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x11], #4
	subs	x10, x10, #1
	b.ne	LBB17_597
LBB17_598:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1536
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #3408]
	str	q0, [sp, #4496]
	cmp	w2, #0
	b.le	LBB17_601
; %bb.599:
	ldr	s2, [x19, #3680]
	ldr	s0, [x19, #3684]
	ldr	s1, [x19, #3696]
	fneg	s2, s2
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #544
	ldr	s3, [sp, #4508]
	mov	x9, x2
	mov	x10, x27
LBB17_600:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x8], #4
	ldur	s5, [x10, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x10], #4
	subs	x9, x9, #1
	b.ne	LBB17_600
LBB17_601:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #400
	ldr	q0, [x8, x0]
	str	q0, [x30, #3408]
	add	x8, x30, #3544
	ldr	q0, [x8]
	str	q0, [sp, #3920]
	cmp	w2, #0
	b.le	LBB17_604
; %bb.602:
	ldr	s2, [x19, #3824]
	ldr	s0, [x19, #3828]
	ldr	s1, [x19, #3832]
	fneg	s2, s2
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #544
	ldr	s3, [sp, #3932]
	mov	x10, x2
	mov	x11, x26
LBB17_603:                              ; =>This Inner Loop Header: Depth=1
	ldr	s4, [x9], #4
	ldur	s5, [x11, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s0, s5, s3
	fmadd	s3, s2, s3, s4
	str	s3, [x11], #4
	subs	x10, x10, #1
	b.ne	LBB17_603
LBB17_604:
	add	x9, sp, #3920
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30]
	str	q0, [sp, #19120]
	cmp	w2, #0
	b.le	LBB17_607
; %bb.605:
	ldr	s0, [x19, #232]
	ldr	s1, [x19, #272]
	ldr	s2, [x19, #276]
	ldr	s5, [x19, #280]
	ldr	s3, [x19, #284]
	ldr	s4, [x19, #288]
	fneg	s5, s5
	add	x8, sp, #2896
	ldr	s7, [x8, #16380]
	add	x8, sp, #2748
	ldr	s6, [x8, #16380]
	add	x8, sp, #2752
	ldr	s16, [x8, #16380]
	mov	x8, x2
	mov	x9, x25
LBB17_606:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x24]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x24, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x24, x24, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_606
LBB17_607:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2736
	ldr	q0, [x8, x0]
	str	q0, [x30]
	add	x8, x30, #280
	ldr	q0, [x8]
	str	q0, [sp, #17984]
	cmp	w2, #0
	ldr	x11, [sp, #736]                 ; 8-byte Folded Reload
	ldr	x24, [sp, #728]                 ; 8-byte Folded Reload
	b.le	LBB17_610
; %bb.608:
	ldr	s0, [x19, #512]
	ldr	s1, [x19, #552]
	ldr	s2, [x19, #556]
	ldr	s5, [x19, #560]
	ldr	s3, [x19, #564]
	ldr	s4, [x19, #568]
	fneg	s5, s5
	add	x9, sp, #1760
	ldr	s7, [x9, #16380]
	add	x9, sp, #1612
	ldr	s6, [x9, #16380]
	add	x9, sp, #1616
	ldr	s16, [x9, #16380]
	mov	x9, x2
	ldr	x10, [sp, #3296]                ; 8-byte Folded Reload
LBB17_609:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x24]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x24, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x24, x24, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_609
LBB17_610:
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #1600
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #544]
	str	q0, [sp, #16848]
	cmp	w2, #0
	ldr	x10, [sp, #744]                 ; 8-byte Folded Reload
	b.le	LBB17_613
; %bb.611:
	ldr	s0, [x19, #776]
	ldr	s1, [x19, #816]
	ldr	s2, [x19, #820]
	ldr	s5, [x19, #824]
	ldr	s3, [x19, #828]
	ldr	s4, [x19, #832]
	fneg	s5, s5
	add	x8, sp, #624
	ldr	s7, [x8, #16380]
	add	x8, sp, #476
	ldr	s6, [x8, #16380]
	add	x8, sp, #480
	ldr	s16, [x8, #16380]
	mov	x8, x2
	ldr	x9, [sp, #3280]                 ; 8-byte Folded Reload
LBB17_612:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_612
LBB17_613:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #464
	ldr	q0, [x8, x0]
	str	q0, [x30, #544]
	add	x8, x30, #808
	ldr	q0, [x8]
	str	q0, [sp, #15712]
	cmp	w2, #0
	ldr	x24, [sp, #712]                 ; 8-byte Folded Reload
	b.le	LBB17_616
; %bb.614:
	ldr	s0, [x19, #1040]
	ldr	s1, [x19, #1080]
	ldr	s2, [x19, #1084]
	ldr	s5, [x19, #1088]
	ldr	s3, [x19, #1092]
	ldr	s4, [x19, #1096]
	fneg	s5, s5
	ldr	s7, [sp, #15868]
	ldr	s6, [sp, #15720]
	ldr	s16, [sp, #15724]
	mov	x9, x2
	mov	x10, x23
LBB17_615:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x24]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x24, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x24, x24, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_615
LBB17_616:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3424
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #1072]
	str	q0, [sp, #14576]
	cmp	w2, #0
	ldr	x10, [sp, #720]                 ; 8-byte Folded Reload
	b.le	LBB17_619
; %bb.617:
	ldr	s0, [x19, #1304]
	ldr	s1, [x19, #1344]
	ldr	s2, [x19, #1348]
	ldr	s5, [x19, #1352]
	ldr	s3, [x19, #1356]
	ldr	s4, [x19, #1360]
	fneg	s5, s5
	ldr	s7, [sp, #14732]
	ldr	s6, [sp, #14584]
	ldr	s16, [sp, #14588]
	mov	x8, x2
	ldr	x9, [sp, #3288]                 ; 8-byte Folded Reload
LBB17_618:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_618
LBB17_619:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2288
	ldr	q0, [x8, x0]
	str	q0, [x30, #1072]
	add	x8, x30, #1336
	ldr	q0, [x8]
	str	q0, [sp, #13440]
	cmp	w2, #0
	ldr	x4, [sp, #552]                  ; 8-byte Folded Reload
	b.le	LBB17_622
; %bb.620:
	ldr	s0, [x19, #1568]
	ldr	s1, [x19, #1608]
	ldr	s2, [x19, #1612]
	ldr	s5, [x19, #1616]
	ldr	s3, [x19, #1620]
	ldr	s4, [x19, #1624]
	fneg	s5, s5
	ldr	s7, [sp, #13596]
	ldr	s6, [sp, #13448]
	ldr	s16, [sp, #13452]
	mov	x9, x2
	mov	x10, x20
LBB17_621:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x11]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x11, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x11, x11, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_621
LBB17_622:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #1152
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #1600]
	str	q0, [sp, #12304]
	cmp	w2, #0
	ldr	x10, [sp, #752]                 ; 8-byte Folded Reload
	b.le	LBB17_625
; %bb.623:
	ldr	s0, [x19, #1832]
	ldr	s1, [x19, #1872]
	ldr	s2, [x19, #1876]
	ldr	s5, [x19, #1880]
	ldr	s3, [x19, #1884]
	ldr	s4, [x19, #1888]
	fneg	s5, s5
	ldr	s7, [sp, #12460]
	ldr	s6, [sp, #12312]
	ldr	s16, [sp, #12316]
	mov	x8, x2
	ldr	x9, [sp, #3304]                 ; 8-byte Folded Reload
LBB17_624:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_624
LBB17_625:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #16
	ldr	q0, [x8, x0]
	str	q0, [x30, #1600]
	add	x8, x30, #1864
	ldr	q0, [x8]
	str	q0, [sp, #11168]
	cmp	w2, #0
	ldr	x11, [sp, #760]                 ; 8-byte Folded Reload
	b.le	LBB17_628
; %bb.626:
	ldr	s0, [x19, #2096]
	ldr	s1, [x19, #2136]
	ldr	s2, [x19, #2140]
	ldr	s5, [x19, #2144]
	ldr	s3, [x19, #2148]
	ldr	s4, [x19, #2152]
	fneg	s5, s5
	ldr	s7, [sp, #11324]
	ldr	s6, [sp, #11176]
	ldr	s16, [sp, #11180]
	mov	x9, x2
	mov	x10, x3
LBB17_627:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x11]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x11, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x11, x11, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_627
LBB17_628:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2976
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #2128]
	str	q0, [sp, #10032]
	cmp	w2, #0
	ldr	x10, [sp, #768]                 ; 8-byte Folded Reload
	b.le	LBB17_631
; %bb.629:
	ldr	s0, [x19, #2360]
	ldr	s1, [x19, #2400]
	ldr	s2, [x19, #2404]
	ldr	s5, [x19, #2408]
	ldr	s3, [x19, #2412]
	ldr	s4, [x19, #2416]
	fneg	s5, s5
	ldr	s7, [sp, #10188]
	ldr	s6, [sp, #10040]
	ldr	s16, [sp, #10044]
	mov	x8, x2
	mov	x9, x22
LBB17_630:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_630
LBB17_631:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1840
	ldr	q0, [x8, x0]
	str	q0, [x30, #2128]
	add	x8, x30, #2392
	ldr	q0, [x8]
	str	q0, [sp, #8896]
	cmp	w2, #0
	b.le	LBB17_634
; %bb.632:
	ldr	s0, [x19, #2624]
	ldr	s1, [x19, #2664]
	ldr	s2, [x19, #2668]
	ldr	s5, [x19, #2672]
	ldr	s3, [x19, #2676]
	ldr	s4, [x19, #2680]
	fneg	s5, s5
	ldr	s7, [sp, #9052]
	ldr	s6, [sp, #8904]
	ldr	s16, [sp, #8908]
	mov	x9, x2
	mov	x10, x1
LBB17_633:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x12]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x12, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x12, x12, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_633
LBB17_634:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #704
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #2656]
	str	q0, [sp, #7760]
	cmp	w2, #0
	ldr	x10, [sp, #776]                 ; 8-byte Folded Reload
	b.le	LBB17_637
; %bb.635:
	ldr	s0, [x19, #2888]
	ldr	s1, [x19, #2928]
	ldr	s2, [x19, #2932]
	ldr	s5, [x19, #2936]
	ldr	s3, [x19, #2940]
	ldr	s4, [x19, #2944]
	fneg	s5, s5
	ldr	s7, [sp, #7916]
	ldr	s6, [sp, #7768]
	ldr	s16, [sp, #7772]
	mov	x8, x2
	mov	x9, x7
LBB17_636:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_636
LBB17_637:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #3664
	ldr	q0, [x8, x0]
	str	q0, [x30, #2656]
	add	x8, x30, #2920
	ldr	q0, [x8]
	str	q0, [sp, #6624]
	cmp	w2, #0
	b.le	LBB17_640
; %bb.638:
	ldr	s0, [x19, #3152]
	ldr	s1, [x19, #3192]
	ldr	s2, [x19, #3196]
	ldr	s5, [x19, #3200]
	ldr	s3, [x19, #3204]
	ldr	s4, [x19, #3208]
	fneg	s5, s5
	ldr	s7, [sp, #6780]
	ldr	s6, [sp, #6632]
	ldr	s16, [sp, #6636]
	mov	x9, x2
	mov	x10, x17
LBB17_639:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x13]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x13, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x13, x13, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_639
LBB17_640:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2528
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #3184]
	str	q0, [sp, #5488]
	cmp	w2, #0
	b.le	LBB17_643
; %bb.641:
	ldr	s0, [x19, #3416]
	ldr	s1, [x19, #3456]
	ldr	s2, [x19, #3460]
	ldr	s5, [x19, #3464]
	ldr	s3, [x19, #3468]
	ldr	s4, [x19, #3472]
	fneg	s5, s5
	ldr	s7, [sp, #5644]
	ldr	s6, [sp, #5496]
	ldr	s16, [sp, #5500]
	mov	x8, x2
	ldr	x9, [sp, #3312]                 ; 8-byte Folded Reload
LBB17_642:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x28]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x28, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x28, x28, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_642
LBB17_643:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1392
	ldr	q0, [x8, x0]
	str	q0, [x30, #3184]
	add	x8, x30, #3448
	ldr	q0, [x8]
	str	q0, [sp, #4352]
	cmp	w2, #0
	b.le	LBB17_646
; %bb.644:
	ldr	s0, [x19, #3680]
	ldr	s1, [x19, #3720]
	ldr	s2, [x19, #3724]
	ldr	s5, [x19, #3728]
	ldr	s3, [x19, #3732]
	ldr	s4, [x19, #3736]
	fneg	s5, s5
	ldr	s7, [sp, #4508]
	ldr	s6, [sp, #4360]
	ldr	s16, [sp, #4364]
	mov	x9, x2
	mov	x10, x16
LBB17_645:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x27]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x27, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x27, x27, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_645
LBB17_646:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #256
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #3584]
	str	q0, [sp, #3776]
	cmp	w2, #0
	b.le	LBB17_649
; %bb.647:
	ldr	s0, [x19, #3824]
	ldr	s1, [x19, #3856]
	ldr	s2, [x19, #3860]
	ldr	s5, [x19, #3864]
	ldr	s3, [x19, #3868]
	ldr	s4, [x19, #3872]
	fneg	s5, s5
	ldr	s7, [sp, #3932]
	ldr	s6, [sp, #3784]
	ldr	s16, [sp, #3788]
	mov	x8, x2
	ldr	x9, [sp, #3320]                 ; 8-byte Folded Reload
LBB17_648:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x26]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x26, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x26, x26, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_648
LBB17_649:
	add	x8, sp, #3776
	ldr	q0, [x8, x0]
	str	q0, [x30, #3584]
	ldur	q0, [x30, #40]
	str	q0, [sp, #18976]
	cmp	w2, #0
	b.le	LBB17_652
; %bb.650:
	ldr	s0, [x19, #280]
	ldr	s1, [x19, #312]
	ldr	s2, [x19, #316]
	ldr	s5, [x19, #320]
	ldr	s3, [x19, #324]
	ldr	s4, [x19, #328]
	fneg	s5, s5
	add	x8, sp, #2752
	ldr	s7, [x8, #16380]
	add	x8, sp, #2604
	ldr	s6, [x8, #16380]
	add	x8, sp, #2608
	ldr	s16, [x8, #16380]
	mov	x8, x2
	ldr	x9, [sp, #784]                  ; 8-byte Folded Reload
LBB17_651:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x25]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x25, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x25, x25, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_651
LBB17_652:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2592
	ldr	q0, [x8, x0]
	stur	q0, [x30, #40]
	ldr	q0, [x30, #320]
	str	q0, [sp, #17840]
	cmp	w2, #0
	ldr	x10, [sp, #3296]                ; 8-byte Folded Reload
	ldr	x5, [sp, #536]                  ; 8-byte Folded Reload
	b.le	LBB17_655
; %bb.653:
	ldr	s0, [x19, #560]
	ldr	s1, [x19, #592]
	ldr	s2, [x19, #596]
	ldr	s5, [x19, #600]
	ldr	s3, [x19, #604]
	ldr	s4, [x19, #608]
	fneg	s5, s5
	add	x8, sp, #1616
	ldr	s7, [x8, #16380]
	add	x8, sp, #1468
	ldr	s6, [x8, #16380]
	add	x8, sp, #1472
	ldr	s16, [x8, #16380]
	mov	x8, x2
	ldr	x9, [sp, #800]                  ; 8-byte Folded Reload
LBB17_654:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x10]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x10, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x10, x10, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_654
LBB17_655:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1456
	ldr	q0, [x8, x0]
	str	q0, [x30, #320]
	add	x8, x30, #584
	ldr	q0, [x8]
	str	q0, [sp, #16704]
	cmp	w2, #0
	ldr	x12, [sp, #3280]                ; 8-byte Folded Reload
	b.le	LBB17_658
; %bb.656:
	ldr	s0, [x19, #824]
	ldr	s1, [x19, #856]
	ldr	s2, [x19, #860]
	ldr	s5, [x19, #864]
	ldr	s3, [x19, #868]
	ldr	s4, [x19, #872]
	fneg	s5, s5
	add	x9, sp, #480
	ldr	s7, [x9, #16380]
	add	x9, sp, #332
	ldr	s6, [x9, #16380]
	add	x9, sp, #336
	ldr	s16, [x9, #16380]
	mov	x9, x2
	mov	x10, x15
LBB17_657:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x12]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x12, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x12, x12, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_657
LBB17_658:
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #320
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #848]
	str	q0, [sp, #15568]
	cmp	w2, #0
	b.le	LBB17_661
; %bb.659:
	ldr	s0, [x19, #1088]
	ldr	s1, [x19, #1120]
	ldr	s2, [x19, #1124]
	ldr	s5, [x19, #1128]
	ldr	s3, [x19, #1132]
	ldr	s4, [x19, #1136]
	fneg	s5, s5
	ldr	s7, [sp, #15724]
	ldr	s6, [sp, #15576]
	ldr	s16, [sp, #15580]
	mov	x8, x2
	ldr	x9, [sp, #3328]                 ; 8-byte Folded Reload
LBB17_660:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x23]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x23, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x23, x23, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_660
LBB17_661:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3280
	ldr	q0, [x8, x0]
	str	q0, [x30, #848]
	add	x8, x30, #1112
	ldr	q0, [x8]
	str	q0, [sp, #14432]
	cmp	w2, #0
	ldr	x12, [sp, #3288]                ; 8-byte Folded Reload
	b.le	LBB17_664
; %bb.662:
	ldr	s0, [x19, #1352]
	ldr	s1, [x19, #1384]
	ldr	s2, [x19, #1388]
	ldr	s5, [x19, #1392]
	ldr	s3, [x19, #1396]
	ldr	s4, [x19, #1400]
	fneg	s5, s5
	ldr	s7, [sp, #14588]
	ldr	s6, [sp, #14440]
	ldr	s16, [sp, #14444]
	mov	x9, x2
	mov	x10, x14
LBB17_663:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x12]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x12, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x12, x12, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_663
LBB17_664:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2144
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #1376]
	str	q0, [sp, #13296]
	cmp	w2, #0
	b.le	LBB17_667
; %bb.665:
	ldr	s0, [x19, #1616]
	ldr	s1, [x19, #1648]
	ldr	s2, [x19, #1652]
	ldr	s5, [x19, #1656]
	ldr	s3, [x19, #1660]
	ldr	s4, [x19, #1664]
	fneg	s5, s5
	ldr	s7, [sp, #13452]
	ldr	s6, [sp, #13304]
	ldr	s16, [sp, #13308]
	mov	x8, x2
	ldr	x9, [sp, #792]                  ; 8-byte Folded Reload
LBB17_666:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x20]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x20, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x20, x20, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_666
LBB17_667:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #1008
	ldr	q0, [x8, x0]
	str	q0, [x30, #1376]
	add	x8, x30, #1640
	ldr	q0, [x8]
	str	q0, [sp, #12160]
	cmp	w2, #0
	ldr	x12, [sp, #3304]                ; 8-byte Folded Reload
	b.le	LBB17_670
; %bb.668:
	ldr	s0, [x19, #1880]
	ldr	s1, [x19, #1912]
	ldr	s2, [x19, #1916]
	ldr	s5, [x19, #1920]
	ldr	s3, [x19, #1924]
	ldr	s4, [x19, #1928]
	fneg	s5, s5
	ldr	s7, [sp, #12316]
	ldr	s6, [sp, #12168]
	ldr	s16, [sp, #12172]
	mov	x9, x2
	ldr	x10, [sp, #808]                 ; 8-byte Folded Reload
LBB17_669:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x12]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x12, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x12, x12, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_669
LBB17_670:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3968
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #1904]
	str	q0, [sp, #11024]
	cmp	w2, #0
	b.le	LBB17_673
; %bb.671:
	ldr	s0, [x19, #2144]
	ldr	s1, [x19, #2176]
	ldr	s2, [x19, #2180]
	ldr	s5, [x19, #2184]
	ldr	s3, [x19, #2188]
	ldr	s4, [x19, #2192]
	fneg	s5, s5
	ldr	s7, [sp, #11180]
	ldr	s6, [sp, #11032]
	ldr	s16, [sp, #11036]
	mov	x8, x2
	mov	x9, x21
LBB17_672:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x3]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x3, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x3, x3, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_672
LBB17_673:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2832
	ldr	q0, [x8, x0]
	str	q0, [x30, #1904]
	add	x8, x30, #2168
	ldr	q0, [x8]
	str	q0, [sp, #9888]
	cmp	w2, #0
	ldr	x13, [sp, #520]                 ; 8-byte Folded Reload
	b.le	LBB17_676
; %bb.674:
	ldr	s0, [x19, #2408]
	ldr	s1, [x19, #2440]
	ldr	s2, [x19, #2444]
	ldr	s5, [x19, #2448]
	ldr	s3, [x19, #2452]
	ldr	s4, [x19, #2456]
	fneg	s5, s5
	ldr	s7, [sp, #10044]
	ldr	s6, [sp, #9896]
	ldr	s16, [sp, #9900]
	mov	x9, x2
	mov	x10, x13
LBB17_675:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x22]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x22, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x22, x22, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_675
LBB17_676:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1696
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #2432]
	str	q0, [sp, #8752]
	cmp	w2, #0
	ldr	x11, [sp, #568]                 ; 8-byte Folded Reload
	ldr	x3, [sp, #560]                  ; 8-byte Folded Reload
	b.le	LBB17_679
; %bb.677:
	ldr	s0, [x19, #2672]
	ldr	s1, [x19, #2704]
	ldr	s2, [x19, #2708]
	ldr	s5, [x19, #2712]
	ldr	s3, [x19, #2716]
	ldr	s4, [x19, #2720]
	fneg	s5, s5
	ldr	s7, [sp, #8908]
	ldr	s6, [sp, #8760]
	ldr	s16, [sp, #8764]
	mov	x8, x2
	mov	x9, x6
LBB17_678:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x1]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x1, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x1, x1, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_678
LBB17_679:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #560
	ldr	q0, [x8, x0]
	str	q0, [x30, #2432]
	add	x8, x30, #2696
	ldr	q0, [x8]
	str	q0, [sp, #7616]
	cmp	w2, #0
	b.le	LBB17_682
; %bb.680:
	ldr	s0, [x19, #2936]
	ldr	s1, [x19, #2968]
	ldr	s2, [x19, #2972]
	ldr	s5, [x19, #2976]
	ldr	s3, [x19, #2980]
	ldr	s4, [x19, #2984]
	fneg	s5, s5
	ldr	s7, [sp, #7772]
	ldr	s6, [sp, #7624]
	ldr	s16, [sp, #7628]
	mov	x9, x2
	mov	x10, x5
LBB17_681:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x7]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x7, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x7, x7, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_681
LBB17_682:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3520
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #2960]
	str	q0, [sp, #6480]
	cmp	w2, #0
	ldr	x1, [sp, #544]                  ; 8-byte Folded Reload
	b.le	LBB17_685
; %bb.683:
	ldr	s0, [x19, #3200]
	ldr	s1, [x19, #3232]
	ldr	s2, [x19, #3236]
	ldr	s5, [x19, #3240]
	ldr	s3, [x19, #3244]
	ldr	s4, [x19, #3248]
	fneg	s5, s5
	ldr	s7, [sp, #6636]
	ldr	s6, [sp, #6488]
	ldr	s16, [sp, #6492]
	mov	x8, x2
	mov	x9, x1
LBB17_684:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x17]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x17, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x17, x17, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_684
LBB17_685:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2384
	ldr	q0, [x8, x0]
	str	q0, [x30, #2960]
	add	x8, x30, #3224
	ldr	q0, [x8]
	str	q0, [sp, #5344]
	cmp	w2, #0
	ldr	x12, [sp, #3312]                ; 8-byte Folded Reload
	b.le	LBB17_688
; %bb.686:
	ldr	s0, [x19, #3464]
	ldr	s1, [x19, #3496]
	ldr	s2, [x19, #3500]
	ldr	s5, [x19, #3504]
	ldr	s3, [x19, #3508]
	ldr	s4, [x19, #3512]
	fneg	s5, s5
	ldr	s7, [sp, #5500]
	ldr	s6, [sp, #5352]
	ldr	s16, [sp, #5356]
	mov	x9, x2
	mov	x10, x4
LBB17_687:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x12]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x12, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x12, x12, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_687
LBB17_688:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1248
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x30, #3488]
	str	q0, [sp, #4208]
	cmp	w2, #0
	b.le	LBB17_691
; %bb.689:
	ldr	s0, [x19, #3728]
	ldr	s1, [x19, #3760]
	ldr	s2, [x19, #3764]
	ldr	s5, [x19, #3768]
	ldr	s3, [x19, #3772]
	ldr	s4, [x19, #3776]
	fneg	s5, s5
	ldr	s7, [sp, #4364]
	ldr	s6, [sp, #4216]
	ldr	s16, [sp, #4220]
	mov	x8, x2
	mov	x9, x3
LBB17_690:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x16]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x16, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x9], #4
	add	x16, x16, #4
	fmov	s7, s17
	subs	x8, x8, #1
	b.ne	LBB17_690
LBB17_691:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #112
	ldr	q0, [x8, x0]
	str	q0, [x30, #3488]
	add	x8, x30, #3620
	ldr	q0, [x8]
	str	q0, [sp, #3632]
	cmp	w2, #0
	ldr	x12, [sp, #3320]                ; 8-byte Folded Reload
	b.le	LBB17_694
; %bb.692:
	ldr	s0, [x19, #3864]
	ldr	s1, [x19, #3892]
	ldr	s2, [x19, #3896]
	ldr	s5, [x19, #3900]
	ldr	s3, [x19, #3904]
	ldr	s4, [x19, #3908]
	fneg	s5, s5
	ldr	s7, [sp, #3788]
	ldr	s6, [sp, #3640]
	ldr	s16, [sp, #3644]
	mov	x9, x2
	mov	x10, x11
LBB17_693:                              ; =>This Inner Loop Header: Depth=1
	fmul	s7, s2, s7
	ldr	s17, [x12]
	fmadd	s7, s1, s17, s7
	ldur	s18, [x12, #-8]
	fmadd	s7, s1, s18, s7
	fmul	s18, s4, s16
	fmadd	s6, s3, s6, s18
	fmul	s18, s6, s5
	fmov	s6, s16
	fmadd	s16, s0, s7, s18
	str	s16, [x10], #4
	add	x12, x12, #4
	fmov	s7, s17
	subs	x9, x9, #1
	b.ne	LBB17_693
LBB17_694:
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #2448
	add	x17, x9, #16
	add	x9, sp, #3632
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldur	q0, [x30, #84]
	str	q0, [sp, #18832]
	cmp	w2, #0
	ldr	x10, [sp, #784]                 ; 8-byte Folded Reload
	b.le	LBB17_697
; %bb.695:
	ldr	s0, [x19, #320]
	ldr	s1, [x19, #368]
	ldr	s2, [x19, #372]
	add	x8, sp, #2464
	ldr	s3, [x8, #16380]
	mov	x8, x2
	mov	x9, x17
	add	x12, sp, #2608
	ldr	s4, [x12, #16380]
LBB17_696:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x10]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x10, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s3, s12, s4
	str	s3, [x9], #4
	add	x10, x10, #4
	fmov	s4, s5
	subs	x8, x8, #1
	b.ne	LBB17_696
LBB17_697:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1312
	add	x16, x8, #16
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #2448
	ldr	q0, [x8, x0]
	stur	q0, [x30, #84]
	ldr	q0, [x19, #640]
	str	q0, [sp, #17696]
	cmp	w2, #0
	ldr	x10, [sp, #800]                 ; 8-byte Folded Reload
	b.le	LBB17_700
; %bb.698:
	ldr	s0, [x19, #600]
	ldr	s1, [x19, #632]
	ldr	s2, [x19, #636]
	add	x8, sp, #1328
	ldr	s3, [x8, #16380]
	mov	x8, x2
	mov	x9, x16
	add	x12, sp, #1472
	ldr	s4, [x12, #16380]
LBB17_699:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x10]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x10, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x9], #4
	add	x10, x10, #4
	fmov	s4, s5
	subs	x8, x8, #1
	b.ne	LBB17_699
LBB17_700:
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #1312
	ldr	q0, [x8, x0]
	add	x8, sp, #4, lsl #12             ; =16384
	add	x8, x8, #176
	add	x7, x8, #16
	str	q0, [x19, #640]
	add	x8, x30, #612
	ldr	q0, [x8]
	str	q0, [sp, #16560]
	cmp	w2, #0
	b.le	LBB17_703
; %bb.701:
	ldr	s0, [x19, #864]
	ldr	s1, [x19, #896]
	ldr	s2, [x19, #900]
	add	x9, sp, #192
	ldr	s3, [x9, #16380]
	mov	x9, x2
	mov	x10, x7
	add	x12, sp, #336
	ldr	s4, [x12, #16380]
LBB17_702:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x15]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x15, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x10], #4
	add	x15, x15, #4
	fmov	s4, s5
	subs	x9, x9, #1
	b.ne	LBB17_702
LBB17_703:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #3136
	add	x15, x9, #16
	add	x9, sp, #4, lsl #12             ; =16384
	add	x9, x9, #176
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x19, #1168]
	str	q0, [sp, #15424]
	cmp	w2, #0
	ldr	x10, [sp, #3328]                ; 8-byte Folded Reload
	b.le	LBB17_706
; %bb.704:
	ldr	s0, [x19, #1128]
	ldr	s1, [x19, #1160]
	ldr	s2, [x19, #1164]
	ldr	s3, [sp, #15436]
	mov	x8, x2
	mov	x9, x15
	ldr	s4, [sp, #15580]
LBB17_705:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x10]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x10, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x9], #4
	add	x10, x10, #4
	fmov	s4, s5
	subs	x8, x8, #1
	b.ne	LBB17_705
LBB17_706:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #3136
	ldr	q0, [x8, x0]
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #2000
	add	x20, x8, #16
	str	q0, [x19, #1168]
	add	x8, x30, #1140
	ldr	q0, [x8]
	str	q0, [sp, #14288]
	cmp	w2, #0
	b.le	LBB17_709
; %bb.707:
	ldr	s0, [x19, #1392]
	ldr	s1, [x19, #1424]
	ldr	s2, [x19, #1428]
	ldr	s3, [sp, #14300]
	mov	x9, x2
	mov	x10, x20
	ldr	s4, [sp, #14444]
LBB17_708:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x14]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x14, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x10], #4
	add	x14, x14, #4
	fmov	s4, s5
	subs	x9, x9, #1
	b.ne	LBB17_708
LBB17_709:
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #864
	add	x14, x9, #16
	add	x9, sp, #3, lsl #12             ; =12288
	add	x9, x9, #2000
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x19, #1696]
	str	q0, [sp, #13152]
	cmp	w2, #0
	ldr	x10, [sp, #792]                 ; 8-byte Folded Reload
	b.le	LBB17_712
; %bb.710:
	ldr	s0, [x19, #1656]
	ldr	s1, [x19, #1688]
	ldr	s2, [x19, #1692]
	ldr	s3, [sp, #13164]
	mov	x8, x2
	mov	x9, x14
	ldr	s4, [sp, #13308]
LBB17_711:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x10]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x10, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x9], #4
	add	x10, x10, #4
	fmov	s4, s5
	subs	x8, x8, #1
	b.ne	LBB17_711
LBB17_712:
	add	x8, sp, #3, lsl #12             ; =12288
	add	x8, x8, #864
	ldr	q0, [x8, x0]
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #3824
	add	x22, x8, #16
	str	q0, [x19, #1696]
	add	x8, x30, #1668
	ldr	q0, [x8]
	str	q0, [sp, #12016]
	cmp	w2, #0
	ldr	x12, [sp, #808]                 ; 8-byte Folded Reload
	b.le	LBB17_715
; %bb.713:
	ldr	s0, [x19, #1920]
	ldr	s1, [x19, #1952]
	ldr	s2, [x19, #1956]
	ldr	s3, [sp, #12028]
	mov	x9, x2
	mov	x10, x22
	ldr	s4, [sp, #12172]
LBB17_714:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x12]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x12, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x10], #4
	add	x12, x12, #4
	fmov	s4, s5
	subs	x9, x9, #1
	b.ne	LBB17_714
LBB17_715:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #2688
	add	x23, x9, #16
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #3824
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x19, #2224]
	str	q0, [sp, #10880]
	cmp	w2, #0
	b.le	LBB17_718
; %bb.716:
	ldr	s0, [x19, #2184]
	ldr	s1, [x19, #2216]
	ldr	s2, [x19, #2220]
	ldr	s3, [sp, #10892]
	mov	x8, x2
	mov	x9, x23
	ldr	s4, [sp, #11036]
LBB17_717:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x21]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x21, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x9], #4
	add	x21, x21, #4
	fmov	s4, s5
	subs	x8, x8, #1
	b.ne	LBB17_717
LBB17_718:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #2688
	ldr	q0, [x8, x0]
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #1552
	add	x21, x8, #16
	str	q0, [x19, #2224]
	add	x8, x30, #2196
	ldr	q0, [x8]
	str	q0, [sp, #9744]
	cmp	w2, #0
	b.le	LBB17_721
; %bb.719:
	ldr	s0, [x19, #2448]
	ldr	s1, [x19, #2480]
	ldr	s2, [x19, #2484]
	ldr	s3, [sp, #9756]
	mov	x9, x2
	mov	x10, x21
	ldr	s4, [sp, #9900]
LBB17_720:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x13]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x13, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x10], #4
	add	x13, x13, #4
	fmov	s4, s5
	subs	x9, x9, #1
	b.ne	LBB17_720
LBB17_721:
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #416
	add	x24, x9, #16
	add	x9, sp, #2, lsl #12             ; =8192
	add	x9, x9, #1552
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x19, #2752]
	str	q0, [sp, #8608]
	cmp	w2, #0
	b.le	LBB17_724
; %bb.722:
	ldr	s0, [x19, #2712]
	ldr	s1, [x19, #2744]
	ldr	s2, [x19, #2748]
	ldr	s3, [sp, #8620]
	mov	x8, x2
	mov	x9, x24
	ldr	s4, [sp, #8764]
LBB17_723:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x6]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x6, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x9], #4
	add	x6, x6, #4
	fmov	s4, s5
	subs	x8, x8, #1
	b.ne	LBB17_723
LBB17_724:
	add	x8, sp, #2, lsl #12             ; =8192
	add	x8, x8, #416
	ldr	q0, [x8, x0]
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #3376
	add	x28, x8, #16
	str	q0, [x19, #2752]
	add	x8, x30, #2724
	ldr	q0, [x8]
	str	q0, [sp, #7472]
	cmp	w2, #0
	b.le	LBB17_727
; %bb.725:
	ldr	s0, [x19, #2976]
	ldr	s1, [x19, #3008]
	ldr	s2, [x19, #3012]
	ldr	s3, [sp, #7484]
	mov	x9, x2
	mov	x10, x28
	ldr	s4, [sp, #7628]
LBB17_726:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x5]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x5, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x10], #4
	add	x5, x5, #4
	fmov	s4, s5
	subs	x9, x9, #1
	b.ne	LBB17_726
LBB17_727:
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #2240
	add	x27, x9, #16
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #3376
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x19, #3280]
	str	q0, [sp, #6336]
	cmp	w2, #0
	b.le	LBB17_730
; %bb.728:
	ldr	s0, [x19, #3240]
	ldr	s1, [x19, #3272]
	ldr	s2, [x19, #3276]
	ldr	s3, [sp, #6348]
	mov	x8, x2
	mov	x9, x27
	ldr	s4, [sp, #6492]
LBB17_729:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x1]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x1, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x9], #4
	add	x1, x1, #4
	fmov	s4, s5
	subs	x8, x8, #1
	b.ne	LBB17_729
LBB17_730:
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #2240
	ldr	q0, [x8, x0]
	add	x8, sp, #1, lsl #12             ; =4096
	add	x8, x8, #1104
	add	x25, x8, #16
	str	q0, [x19, #3280]
	add	x8, x30, #3252
	ldr	q0, [x8]
	str	q0, [sp, #5200]
	cmp	w2, #0
	b.le	LBB17_733
; %bb.731:
	ldr	s0, [x19, #3504]
	ldr	s1, [x19, #3536]
	ldr	s2, [x19, #3540]
	ldr	s3, [sp, #5212]
	mov	x9, x2
	mov	x10, x25
	ldr	s4, [sp, #5356]
LBB17_732:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x4]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x4, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x10], #4
	add	x4, x4, #4
	fmov	s4, s5
	subs	x9, x9, #1
	b.ne	LBB17_732
LBB17_733:
	add	x9, sp, #4064
	add	x26, x9, #16
	add	x9, sp, #1, lsl #12             ; =4096
	add	x9, x9, #1104
	ldr	q0, [x9, x0]
	str	q0, [x8]
	ldr	q0, [x19, #3808]
	str	q0, [sp, #4064]
	cmp	w2, #0
	b.le	LBB17_736
; %bb.734:
	ldr	s0, [x19, #3768]
	ldr	s1, [x19, #3800]
	ldr	s2, [x19, #3804]
	ldr	s3, [sp, #4076]
	mov	x8, x2
	mov	x9, x26
	ldr	s4, [sp, #4220]
LBB17_735:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x3]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x3, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x9], #4
	add	x3, x3, #4
	fmov	s4, s5
	subs	x8, x8, #1
	b.ne	LBB17_735
LBB17_736:
	add	x8, sp, #4064
	ldr	q0, [x8, x0]
	str	q0, [x19, #3808]
	add	x8, x19, #3936
	ldr	q0, [x19, #3936]
	str	q0, [sp, #3488]
	cmp	w2, #0
	b.le	LBB17_742
; %bb.737:
	ldr	x12, [sp, #3192]                ; 8-byte Folded Reload
	mov	w13, w12
	add	x9, sp, #3488
	add	x3, x9, #16
	ldr	s0, [x19, #3900]
	ldr	s1, [x19, #3928]
	ldr	s2, [x19, #3932]
	ldr	s3, [sp, #3500]
	mov	x9, x2
	mov	x10, x3
	ldr	s4, [sp, #3644]
LBB17_738:                              ; =>This Inner Loop Header: Depth=1
	fmul	s4, s2, s4
	ldr	s5, [x11]
	fmadd	s4, s1, s5, s4
	ldur	s6, [x11, #-8]
	fmadd	s4, s1, s6, s4
	fmul	s4, s0, s4
	fabs	s4, s4
	fmul	s4, s13, s4
	fmadd	s3, s12, s3, s4
	str	s3, [x10], #4
	add	x11, x11, #4
	fmov	s4, s5
	subs	x9, x9, #1
	b.ne	LBB17_738
; %bb.739:
	add	x9, sp, #3488
	ldr	q0, [x9, x0]
	str	q0, [x8]
	cmp	w2, #0
	b.le	LBB17_776
; %bb.740:
	str	x3, [sp, #3304]                 ; 8-byte Folded Spill
	str	x24, [sp, #3336]                ; 8-byte Folded Spill
	str	x21, [sp, #3328]                ; 8-byte Folded Spill
	str	x13, [sp, #3344]                ; 8-byte Folded Spill
	str	x23, [sp, #3320]                ; 8-byte Folded Spill
	str	x22, [sp, #3312]                ; 8-byte Folded Spill
	str	x14, [sp, #3352]                ; 8-byte Folded Spill
	mov	x24, x20
	mov	x23, x15
	mov	x21, x7
	mov	x20, x17
	mov	x22, x16
	mvn	w8, w12
	ldr	w9, [sp, #12]                   ; 4-byte Folded Reload
	add	w8, w8, w9
	ubfiz	x8, x8, #2, #32
	add	x0, sp, #3360
	add	x1, sp, #4, lsl #12             ; =16384
	add	x1, x1, #3024
	add	x2, x8, #4
	bl	_memcpy
	ldr	x10, [sp, #3120]                ; 8-byte Folded Reload
	cmp	w10, #3
	b.hi	LBB17_743
; %bb.741:
	mov	x8, #0                          ; =0x0
	mov	x15, x24
	ldr	x16, [sp, #3312]                ; 8-byte Folded Reload
	ldr	x3, [sp, #3320]                 ; 8-byte Folded Reload
	ldr	x24, [sp, #3328]                ; 8-byte Folded Reload
	b	LBB17_747
LBB17_742:
	add	x9, sp, #3488
	ldr	q0, [x9, x0]
	str	q0, [x8]
	b	LBB17_776
LBB17_743:
	and	x8, x10, #0x7ffffffc
	mov	x9, x8
LBB17_744:                              ; =>This Inner Loop Header: Depth=1
	subs	x9, x9, #4
	b.ne	LBB17_744
; %bb.745:
	cmp	x8, x10
	mov	x15, x24
	ldr	x16, [sp, #3312]                ; 8-byte Folded Reload
	ldr	x3, [sp, #3320]                 ; 8-byte Folded Reload
	ldr	x24, [sp, #3328]                ; 8-byte Folded Reload
	b.ne	LBB17_747
; %bb.746:
	sub	x8, x8, #1
	b	LBB17_750
LBB17_747:
	mov	w9, #1                          ; =0x1
	sub	x8, x9, x8
LBB17_748:                              ; =>This Inner Loop Header: Depth=1
	sub	x8, x8, #1
	add	x9, x10, x8
	cmp	x9, #1
	b.ne	LBB17_748
; %bb.749:
	neg	x8, x8
LBB17_750:
	ldr	x9, [sp, #3304]                 ; 8-byte Folded Reload
	ldr	s0, [x9, x8, lsl #2]
	str	s0, [sp, #3328]                 ; 4-byte Folded Spill
	ldr	s0, [x26, x8, lsl #2]
	str	s0, [sp, #3320]                 ; 4-byte Folded Spill
	ldr	s0, [x25, x8, lsl #2]
	str	s0, [sp, #3312]                 ; 4-byte Folded Spill
	ldr	s0, [x27, x8, lsl #2]
	str	s0, [sp, #3304]                 ; 4-byte Folded Spill
	ldr	s0, [x28, x8, lsl #2]
	str	s0, [sp, #3288]                 ; 4-byte Folded Spill
	ldr	x9, [sp, #3336]                 ; 8-byte Folded Reload
	ldr	s0, [x9, x8, lsl #2]
	str	s0, [sp, #3264]                 ; 4-byte Folded Spill
	ldr	s0, [x24, x8, lsl #2]
	str	s0, [sp, #3248]                 ; 4-byte Folded Spill
	ldr	s0, [x3, x8, lsl #2]
	str	s0, [sp, #3232]                 ; 4-byte Folded Spill
	ldr	s8, [x16, x8, lsl #2]
	ldr	x9, [sp, #3352]                 ; 8-byte Folded Reload
	ldr	s9, [x9, x8, lsl #2]
	ldr	s10, [x15, x8, lsl #2]
	ldr	s11, [x23, x8, lsl #2]
	ldr	s12, [x21, x8, lsl #2]
	ldr	s13, [x22, x8, lsl #2]
	ldr	s0, [x20, x8, lsl #2]
	bl	_log10f
	fmov	s14, #20.00000000
	ldr	s15, [sp, #340]                 ; 4-byte Folded Reload
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	str	d0, [sp, #3352]                 ; 8-byte Folded Spill
	fmov	s0, s13
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	str	d0, [sp, #3336]                 ; 8-byte Folded Spill
	fmov	s0, s12
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	str	d0, [sp, #3296]                 ; 8-byte Folded Spill
	fmov	s0, s11
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	str	d0, [sp, #3280]                 ; 8-byte Folded Spill
	fmov	s0, s10
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	str	d0, [sp, #3272]                 ; 8-byte Folded Spill
	fmov	s0, s9
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	str	d0, [sp, #3256]                 ; 8-byte Folded Spill
	fmov	s0, s8
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	str	d0, [sp, #3240]                 ; 8-byte Folded Spill
	ldr	s0, [sp, #3232]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	str	d0, [sp, #3232]                 ; 8-byte Folded Spill
	ldr	s0, [sp, #3248]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d13, s0
	ldr	s0, [sp, #3264]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d12, s0
	ldr	s0, [sp, #3288]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d11, s0
	ldr	s0, [sp, #3304]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d10, s0
	ldr	s0, [sp, #3312]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d9, s0
	ldr	s0, [sp, #3320]                 ; 4-byte Folded Reload
	bl	_log10f
	fmadd	s0, s0, s14, s15
	fcvt	d8, s0
	ldr	s0, [sp, #3328]                 ; 4-byte Folded Reload
	bl	_log10f
	ldr	d1, [sp, #3352]                 ; 8-byte Folded Reload
	str	d1, [x19, #3960]
	fmadd	s0, s0, s14, s15
	fcvt	d0, s0
	ldr	d1, [sp, #3336]                 ; 8-byte Folded Reload
	str	d1, [x19, #3968]
	ldr	d1, [sp, #3296]                 ; 8-byte Folded Reload
	str	d1, [x19, #3976]
	ldr	d1, [sp, #3280]                 ; 8-byte Folded Reload
	str	d1, [x19, #3984]
	ldr	d1, [sp, #3272]                 ; 8-byte Folded Reload
	str	d1, [x19, #3992]
	ldr	d1, [sp, #3256]                 ; 8-byte Folded Reload
	str	d1, [x19, #4000]
	ldr	d1, [sp, #3240]                 ; 8-byte Folded Reload
	str	d1, [x19, #4008]
	ldr	d1, [sp, #3232]                 ; 8-byte Folded Reload
	str	d1, [x19, #4016]
	str	d13, [x19, #4024]
	str	d12, [x19, #4032]
	str	d11, [x19, #4040]
	str	d10, [x19, #4048]
	str	d9, [x19, #4056]
	str	d8, [x19, #4064]
	str	d0, [x19, #4072]
	ldr	x13, [sp, #3120]                ; 8-byte Folded Reload
	cmp	w13, #1
	b.ne	LBB17_752
; %bb.751:
	mov	x8, #0                          ; =0x0
	ldr	x14, [sp, #3344]                ; 8-byte Folded Reload
	b	LBB17_761
LBB17_752:
	cmp	w13, #16
	ldr	x14, [sp, #3344]                ; 8-byte Folded Reload
	b.hs	LBB17_754
; %bb.753:
	mov	x8, #0                          ; =0x0
	b	LBB17_758
LBB17_754:
	and	x8, x13, #0x7ffffff0
	ldr	x9, [sp, #344]                  ; 8-byte Folded Reload
	add	x9, x9, x14, lsl #3
	add	x9, x9, #64
	add	x10, sp, #3360
	add	x10, x10, #32
	mov	x11, x8
LBB17_755:                              ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x10, #-32]
	ldp	q2, q3, [x10], #64
	fcvtl	v4.2d, v0.2s
	fcvtl2	v0.2d, v0.4s
	fcvtl	v5.2d, v1.2s
	fcvtl2	v1.2d, v1.4s
	fcvtl	v6.2d, v2.2s
	fcvtl2	v2.2d, v2.4s
	fcvtl	v7.2d, v3.2s
	fcvtl2	v3.2d, v3.4s
	stp	q4, q0, [x9, #-64]
	stp	q5, q1, [x9, #-32]
	stp	q6, q2, [x9]
	stp	q7, q3, [x9, #32]
	add	x9, x9, #128
	subs	x11, x11, #16
	b.ne	LBB17_755
; %bb.756:
	cmp	x8, x13
	b.eq	LBB17_763
; %bb.757:
	tst	x13, #0xe
	b.eq	LBB17_761
LBB17_758:
	mov	x11, x8
	and	x8, x13, #0x7ffffffe
	add	x9, sp, #3360
	add	x9, x9, x11, lsl #2
	lsl	x10, x11, #3
	add	x10, x10, x14, lsl #3
	ldr	x12, [sp, #344]                 ; 8-byte Folded Reload
	add	x10, x12, x10
	sub	x11, x11, x8
LBB17_759:                              ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x9], #8
	fcvtl	v0.2d, v0.2s
	str	q0, [x10], #16
	adds	x11, x11, #2
	b.ne	LBB17_759
; %bb.760:
	cmp	x8, x13
	b.eq	LBB17_763
LBB17_761:
	lsl	x9, x8, #3
	add	x9, x9, x14, lsl #3
	ldr	x10, [sp, #344]                 ; 8-byte Folded Reload
	add	x9, x10, x9
	add	x10, sp, #3360
	add	x10, x10, x8, lsl #2
	sub	x8, x13, x8
LBB17_762:                              ; =>This Inner Loop Header: Depth=1
	ldr	s0, [x10], #4
	fcvt	d0, s0
	str	d0, [x9], #8
	subs	x8, x8, #1
	b.ne	LBB17_762
LBB17_763:
	cmp	w13, #1
	b.ne	LBB17_765
; %bb.764:
	mov	x8, #0                          ; =0x0
	b	LBB17_774
LBB17_765:
	cmp	w13, #16
	b.hs	LBB17_767
; %bb.766:
	mov	x8, #0                          ; =0x0
	b	LBB17_771
LBB17_767:
	and	x8, x13, #0x7ffffff0
	ldr	x9, [sp, #352]                  ; 8-byte Folded Reload
	add	x9, x9, x14, lsl #3
	add	x9, x9, #64
	add	x10, sp, #3360
	add	x10, x10, #32
	mov	x11, x8
LBB17_768:                              ; =>This Inner Loop Header: Depth=1
	ldp	q0, q1, [x10, #-32]
	ldp	q2, q3, [x10], #64
	fcvtl	v4.2d, v0.2s
	fcvtl2	v0.2d, v0.4s
	fcvtl	v5.2d, v1.2s
	fcvtl2	v1.2d, v1.4s
	fcvtl	v6.2d, v2.2s
	fcvtl2	v2.2d, v2.4s
	fcvtl	v7.2d, v3.2s
	fcvtl2	v3.2d, v3.4s
	stp	q4, q0, [x9, #-64]
	stp	q5, q1, [x9, #-32]
	stp	q6, q2, [x9]
	stp	q7, q3, [x9, #32]
	add	x9, x9, #128
	subs	x11, x11, #16
	b.ne	LBB17_768
; %bb.769:
	cmp	x8, x13
	b.eq	LBB17_776
; %bb.770:
	tst	x13, #0xe
	b.eq	LBB17_774
LBB17_771:
	mov	x11, x8
	and	x8, x13, #0x7ffffffe
	add	x9, sp, #3360
	add	x9, x9, x11, lsl #2
	lsl	x10, x11, #3
	add	x10, x10, x14, lsl #3
	ldr	x12, [sp, #352]                 ; 8-byte Folded Reload
	add	x10, x12, x10
	sub	x11, x11, x8
LBB17_772:                              ; =>This Inner Loop Header: Depth=1
	ldr	d0, [x9], #8
	fcvtl	v0.2d, v0.2s
	str	q0, [x10], #16
	adds	x11, x11, #2
	b.ne	LBB17_772
; %bb.773:
	cmp	x8, x13
	b.eq	LBB17_776
LBB17_774:
	lsl	x9, x8, #3
	add	x9, x9, x14, lsl #3
	ldr	x10, [sp, #352]                 ; 8-byte Folded Reload
	add	x9, x10, x9
	add	x10, sp, #3360
	add	x10, x10, x8, lsl #2
	sub	x8, x13, x8
LBB17_775:                              ; =>This Inner Loop Header: Depth=1
	ldr	s0, [x10], #4
	fcvt	d0, s0
	str	d0, [x9], #8
	subs	x8, x8, #1
	b.ne	LBB17_775
LBB17_776:
	ldur	x8, [x29, #-168]
Lloh285:
	adrp	x9, ___stack_chk_guard@GOTPAGE
Lloh286:
	ldr	x9, [x9, ___stack_chk_guard@GOTPAGEOFF]
Lloh287:
	ldr	x9, [x9]
	cmp	x9, x8
	b.ne	LBB17_778
; %bb.777:
	add	sp, sp, #5, lsl #12             ; =20480
	add	sp, sp, #1024
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
LBB17_778:
	bl	___stack_chk_fail
	.loh AdrpLdrGotLdr	Lloh278, Lloh279, Lloh280
	.loh AdrpAdd	Lloh281, Lloh282
	.loh AdrpAdd	Lloh283, Lloh284
	.loh AdrpLdrGotLdr	Lloh285, Lloh286, Lloh287
	.loh AdrpLdrGot	Lloh276, Lloh277
	.cfi_endproc
                                        ; -- End function
	.globl	__ZN3dsp7computeEdiPPdS1_       ; -- Begin function _ZN3dsp7computeEdiPPdS1_
	.weak_def_can_be_hidden	__ZN3dsp7computeEdiPPdS1_
	.p2align	2
__ZN3dsp7computeEdiPPdS1_:              ; @_ZN3dsp7computeEdiPPdS1_
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


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; MOJO:

_inspect_compute:
	.cfi_startproc
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
	sub	sp, sp, #4, lsl #12
	sub	sp, sp, #3792
	.cfi_def_cfa_offset 20336
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
	str	x1, [sp, #19904]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3520
	; InlineAsm Start
	; InlineAsm End
	str	x2, [sp, #19904]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3520
	; InlineAsm Start
	; InlineAsm End
	ldp	x9, x8, [x2]
	str	x9, [sp, #1720]
	str	x8, [sp, #1712]
	ldr	d10, [x0, #8]
	mov	w21, #4719
	movk	w21, #14979, lsl #16
	ldr	d0, [x0, #32]
	fcvt	s0, d0
	mov	w8, #52429
	movk	w8, #15692, lsl #16
	fmov	s1, w8
	fmul	s1, s0, s1
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	mov.16b	v8, v0
	ldr	d0, [x19, #56]
	movi.2d	v11, #0000000000000000
	mov	x8, #3931642474694443008
	fmov	d1, x8
	fcmp	d0, d1
	movi.2d	v12, #0000000000000000
	b.le	LBB0_2
	fcvt	s0, d0
	ldr	s1, [x19, #72]
	fneg	s1, s1
	fdiv	s0, s1, s0
	mov	w8, #49318
	movk	w8, #17072, lsl #16
	fmov	s1, w8
	fminnm	s0, s0, s1
	mov	w8, #49317
	movk	w8, #49840, lsl #16
	fmov	s1, w8
	fmaxnm	s0, s0, s1
	mov	w8, #43579
	movk	w8, #16312, lsl #16
	fmov	s1, w8
	fmov	s2, #0.50000000
	fmadd	s1, s0, s1, s2
	frintm	s3, s1
	mov	w8, #29208
	movk	w8, #48945, lsl #16
	fmov	s4, w8
	fmadd	s3, s3, s4, s0
	mov	w8, #2913
	movk	w8, #15030, lsl #16
	fmov	s4, w8
	mov	w8, #3329
	movk	w8, #14672, lsl #16
	fmov	s5, w8
	fmadd	s4, s3, s5, s4
	mov	w8, #34953
	movk	w8, #15368, lsl #16
	fmov	s5, w8
	fmadd	s4, s4, s3, s5
	mov	w8, #43691
	movk	w8, #15658, lsl #16
	fmov	s5, w8
	fmadd	s4, s4, s3, s5
	mov	w8, #43691
	movk	w8, #15914, lsl #16
	fmov	s5, w8
	fmadd	s4, s4, s3, s5
	fmadd	s2, s4, s3, s2
	fmov	s4, #1.00000000
	fmadd	s2, s2, s3, s4
	fcvtms	w8, s1
	fmadd	s1, s2, s3, s4
	mov	w9, #1065353216
	add	w8, w9, w8, lsl #23
	fmov	s2, w8
	fmul	s1, s1, s2
	fmaxnm	s12, s1, s0
LBB0_2:
	add	x8, sp, #3856
	add	x8, x8, #16
	str	x8, [sp, #1736]
	add	x20, sp, #1, lsl #12
	add	x20, x20, #32
	fmov	s9, w21
	ldr	d0, [x19, #80]
	fcvt	s0, d0
	mov	w8, #-1035730944
	fmov	s1, w8
	fadd	s0, s0, s1
	mov	w8, #43691
	movk	w8, #15786, lsl #16
	fmov	s1, w8
	fcvt	s10, d10
	fmul	s1, s0, s1
	add	x21, sp, #1, lsl #12
	add	x21, x21, #3440
	add	x22, sp, #1, lsl #12
	add	x22, x22, #3584
	add	x23, sp, #1, lsl #12
	add	x23, x23, #3728
	add	x24, sp, #1, lsl #12
	add	x24, x24, #3872
	add	x25, sp, #1, lsl #12
	add	x25, x25, #4016
	add	x26, sp, #2, lsl #12
	add	x26, x26, #64
	add	x27, sp, #2, lsl #12
	add	x27, x27, #208
	add	x28, sp, #2, lsl #12
	add	x28, x28, #480
	fmov	s0, #2.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	mov	w8, #1138491392
	fmov	s1, w8
	fmul	s0, s0, s1
	fmov	s13, #1.00000000
	fsub	s1, s13, s12
	ldr	d2, [x19, #160]
	fcvt	s2, d2
	mov	w8, #4719
	movk	w8, #14979, lsl #16
	fmov	s3, w8
	ldr	d4, [x19, #184]
	fcvt	s4, d4
	fcvtzs	w8, s4
	str	w8, [sp, #1732]
	ldr	d4, [x19, #352]
	fcvt	s4, d4
	fmul	s5, s4, s3
	fcmp	s5, #0.0
	b.le	LBB0_4
	ldr	s5, [x19, #360]
	fneg	s5, s5
	fdiv	s4, s5, s4
	mov	w8, #49318
	movk	w8, #17072, lsl #16
	fmov	s5, w8
	fminnm	s4, s4, s5
	mov	w8, #49317
	movk	w8, #49840, lsl #16
	fmov	s5, w8
	fmaxnm	s4, s4, s5
	mov	w8, #43579
	movk	w8, #16312, lsl #16
	fmov	s5, w8
	fmov	s6, #0.50000000
	fmadd	s5, s4, s5, s6
	frintm	s7, s5
	mov	w8, #29208
	movk	w8, #48945, lsl #16
	fmov	s16, w8
	fmadd	s7, s7, s16, s4
	mov	w8, #2913
	movk	w8, #15030, lsl #16
	fmov	s16, w8
	mov	w8, #3329
	movk	w8, #14672, lsl #16
	fmov	s17, w8
	fmadd	s16, s7, s17, s16
	mov	w8, #34953
	movk	w8, #15368, lsl #16
	fmov	s17, w8
	fmadd	s16, s16, s7, s17
	mov	w8, #43691
	movk	w8, #15658, lsl #16
	fmov	s17, w8
	fmadd	s16, s16, s7, s17
	mov	w8, #43691
	movk	w8, #15914, lsl #16
	fmov	s17, w8
	fmadd	s16, s16, s7, s17
	fmadd	s6, s16, s7, s6
	fmadd	s6, s6, s7, s13
	fcvtms	w8, s5
	fmadd	s5, s6, s7, s13
	mov	w9, #1065353216
	add	w8, w9, w8, lsl #23
	fmov	s6, w8
	fmul	s5, s5, s6
	fmaxnm	s11, s5, s4
LBB0_4:
	add	x9, x20, #16
	mov	x12, #0
	mov	w8, #48759
	movk	w8, #16255, lsl #16
	fmov	s14, w8
	mov	w8, #23950
	movk	w8, #16403, lsl #16
	fmov	s15, w8
	mov	w8, #49318
	movk	w8, #17072, lsl #16
	str	w8, [sp, #1684]
	mov	w8, #49317
	movk	w8, #49840, lsl #16
	str	w8, [sp, #1680]
	mov	w8, #43579
	movk	w8, #16312, lsl #16
	str	w8, [sp, #1676]
	mov	w8, #29208
	movk	w8, #48945, lsl #16
	fmov	s4, w8
	mov	w8, #2913
	movk	w8, #15030, lsl #16
	fmov	s5, w8
	mov	w8, #3329
	movk	w8, #14672, lsl #16
	fmov	s6, w8
	mov	w8, #34953
	movk	w8, #15368, lsl #16
	fmov	s7, w8
	mov	w8, #43691
	movk	w8, #15658, lsl #16
	fmov	s16, w8
	mov	w8, #43691
	movk	w8, #15914, lsl #16
	fmov	s17, w8
	add	x8, sp, #1, lsl #12
	add	x8, x8, #176
	add	x8, x8, #16
	str	x8, [sp, #1640]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #320
	add	x8, x8, #16
	str	x8, [sp, #1632]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #464
	add	x8, x8, #16
	str	x8, [sp, #1624]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #608
	add	x13, x8, #16
	add	x8, sp, #1, lsl #12
	add	x8, x8, #752
	add	x14, x8, #16
	add	x8, sp, #1, lsl #12
	add	x8, x8, #896
	add	x8, x8, #16
	str	x8, [sp, #1600]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1168
	add	x8, x8, #16
	str	x8, [sp, #1592]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1312
	add	x15, x8, #16
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1456
	add	x8, x8, #16
	str	x8, [sp, #1576]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1600
	add	x8, x8, #16
	str	x8, [sp, #1568]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1744
	add	x16, x8, #16
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1888
	add	x17, x8, #16
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2032
	add	x8, x8, #16
	str	x8, [sp, #1544]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2304
	add	x8, x8, #16
	str	x8, [sp, #1536]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2448
	add	x8, x8, #16
	str	x8, [sp, #1528]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2592
	add	x8, x8, #16
	str	x8, [sp, #1520]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2736
	add	x8, x8, #16
	str	x8, [sp, #1512]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2880
	add	x8, x8, #16
	str	x8, [sp, #1504]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3024
	add	x0, x8, #16
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3168
	add	x8, x8, #16
	str	x8, [sp, #1488]
	add	x8, x21, #16
	str	x8, [sp, #1480]
	add	x8, x22, #16
	str	x8, [sp, #1472]
	add	x8, x23, #16
	str	x8, [sp, #1464]
	add	x8, x24, #16
	str	x8, [sp, #1456]
	mov	x24, x9
	add	x8, x25, #16
	str	x8, [sp, #1448]
	add	x1, x26, #16
	add	x8, x27, #16
	str	x8, [sp, #1432]
	add	x8, x28, #16
	str	x8, [sp, #1424]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #624
	add	x8, x8, #16
	str	x8, [sp, #1416]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #768
	add	x8, x8, #16
	str	x8, [sp, #1408]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #912
	add	x8, x8, #16
	str	x8, [sp, #1400]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1056
	add	x8, x8, #16
	str	x8, [sp, #1392]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1200
	add	x2, x8, #16
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1344
	add	x8, x8, #16
	str	x8, [sp, #1376]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1616
	add	x8, x8, #16
	str	x8, [sp, #1368]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1760
	add	x8, x8, #16
	str	x8, [sp, #1360]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1904
	add	x8, x8, #16
	str	x8, [sp, #1352]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2048
	add	x8, x8, #16
	str	x8, [sp, #1344]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2192
	add	x8, x8, #16
	str	x8, [sp, #1336]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2336
	add	x3, x8, #16
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2480
	add	x8, x8, #16
	str	x8, [sp, #1320]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2752
	add	x8, x8, #16
	str	x8, [sp, #1312]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2896
	add	x8, x8, #16
	str	x8, [sp, #1304]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3040
	add	x8, x8, #16
	str	x8, [sp, #1296]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3184
	add	x8, x8, #16
	str	x8, [sp, #1288]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3328
	add	x8, x8, #16
	str	x8, [sp, #1280]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3472
	add	x4, x8, #16
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3616
	add	x8, x8, #16
	str	x8, [sp, #1264]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3888
	add	x8, x8, #16
	str	x8, [sp, #1256]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #4032
	add	x8, x8, #16
	str	x8, [sp, #1248]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #80
	add	x8, x8, #16
	str	x8, [sp, #1240]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #224
	add	x8, x8, #16
	str	x8, [sp, #1232]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #368
	add	x8, x8, #16
	str	x8, [sp, #1224]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #512
	add	x5, x8, #16
	add	x8, sp, #3, lsl #12
	add	x8, x8, #656
	add	x8, x8, #16
	str	x8, [sp, #1208]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #928
	add	x8, x8, #16
	str	x8, [sp, #1200]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1072
	add	x8, x8, #16
	str	x8, [sp, #1192]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1216
	add	x8, x8, #16
	str	x8, [sp, #1184]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1360
	add	x8, x8, #16
	str	x8, [sp, #1176]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1504
	add	x8, x8, #16
	str	x8, [sp, #1168]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1648
	add	x6, x8, #16
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1792
	add	x8, x8, #16
	str	x8, [sp, #1152]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2064
	add	x8, x8, #16
	str	x8, [sp, #1144]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2208
	add	x8, x8, #16
	str	x8, [sp, #1136]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2352
	add	x8, x8, #16
	str	x8, [sp, #1128]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2496
	add	x8, x8, #16
	str	x8, [sp, #1120]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2640
	add	x8, x8, #16
	str	x8, [sp, #1112]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2784
	add	x7, x8, #16
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2928
	add	x8, x8, #16
	str	x8, [sp, #1096]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3200
	add	x8, x8, #16
	str	x8, [sp, #1088]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3344
	add	x8, x8, #16
	str	x8, [sp, #1080]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3488
	add	x8, x8, #16
	str	x8, [sp, #1072]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3632
	add	x8, x8, #16
	str	x8, [sp, #1064]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3776
	add	x8, x8, #16
	str	x8, [sp, #1056]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3920
	add	x30, x8, #16
	add	x8, sp, #3, lsl #12
	add	x8, x8, #4064
	add	x8, x8, #16
	str	x8, [sp, #1040]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #240
	add	x8, x8, #16
	str	x8, [sp, #1032]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #384
	add	x8, x8, #16
	str	x8, [sp, #1024]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #528
	add	x8, x8, #16
	str	x8, [sp, #1016]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #672
	add	x8, x8, #16
	str	x8, [sp, #1008]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #816
	add	x8, x8, #16
	str	x8, [sp, #1000]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #960
	add	x8, x8, #16
	str	x8, [sp, #2008]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1104
	add	x8, x8, #16
	str	x8, [sp, #992]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1376
	add	x8, x8, #16
	str	x8, [sp, #984]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1520
	add	x8, x8, #16
	str	x8, [sp, #976]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1664
	add	x8, x8, #16
	str	x8, [sp, #968]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1808
	add	x8, x8, #16
	str	x8, [sp, #960]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2096
	add	x22, x8, #16
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2240
	add	x8, x8, #16
	str	x8, [sp, #952]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2512
	add	x8, x8, #16
	str	x8, [sp, #2000]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2656
	add	x27, x8, #16
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2800
	add	x28, x8, #16
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2944
	add	x8, x8, #16
	str	x8, [sp, #944]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3088
	add	x8, x8, #16
	str	x8, [sp, #1992]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3232
	add	x21, x8, #16
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3376
	add	x25, x8, #16
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3520
	add	x8, x8, #16
	str	x8, [sp, #936]
	fmul	s18, s10, s9
	str	s18, [sp, #932]
	fmul	s18, s8, s9
	str	s18, [sp, #928]
	fmul	s1, s1, s0
	fmul	s0, s2, s3
	str	s0, [sp, #920]
	ldr	d0, [x19, #3952]
	fcvt	s0, d0
	str	q0, [sp, #2016]
	dup.4s	v0, v0[0]
	str	q0, [sp, #896]
	fsub	s0, s13, s11
	str	s0, [sp, #892]
	ldr	w8, [sp, #1732]
	cmp	w8, #0
	add	x8, sp, #3024
	add	x8, x8, #12
	str	x8, [sp, #880]
	add	x8, sp, #2064
	add	x8, x8, #16
	str	x8, [sp, #2040]
	add	x8, sp, #2208
	add	x8, x8, #16
	str	x8, [sp, #1984]
	add	x8, sp, #2352
	add	x10, x8, #16
	add	x8, sp, #2880
	add	x8, x8, #16
	str	x8, [sp, #1976]
	add	x8, sp, #3024
	add	x8, x8, #16
	str	x8, [sp, #872]
	add	x8, sp, #3168
	add	x11, x8, #16
	add	x8, sp, #3312
	add	x8, x8, #16
	str	x8, [sp, #2048]
	add	x8, sp, #3712
	add	x8, x8, #16
	str	x8, [sp, #848]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1952
	add	x8, x8, #16
	str	x8, [sp, #840]
	add	x9, sp, #3456
	ldr	x8, [sp, #1736]
	csel	x8, x8, x9, eq
	str	x8, [sp, #832]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #608
	add	x8, x8, #128
	str	x8, [sp, #824]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #752
	add	x8, x8, #128
	str	x8, [sp, #816]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #896
	add	x8, x8, #128
	str	x8, [sp, #808]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1744
	add	x8, x8, #128
	str	x8, [sp, #800]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1888
	add	x8, x8, #128
	str	x8, [sp, #792]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2032
	add	x8, x8, #128
	str	x8, [sp, #784]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2880
	add	x8, x8, #128
	str	x8, [sp, #776]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3024
	add	x8, x8, #128
	str	x8, [sp, #768]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3168
	add	x8, x8, #128
	str	x8, [sp, #760]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #4016
	add	x8, x8, #128
	str	x8, [sp, #752]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #64
	add	x8, x8, #128
	str	x8, [sp, #744]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #208
	add	x8, x8, #128
	str	x8, [sp, #736]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1056
	add	x8, x8, #128
	str	x8, [sp, #728]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1200
	add	x8, x8, #128
	str	x8, [sp, #720]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1344
	add	x8, x8, #128
	str	x8, [sp, #712]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2192
	add	x8, x8, #128
	str	x8, [sp, #704]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2336
	add	x8, x8, #128
	str	x8, [sp, #696]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2480
	add	x8, x8, #128
	str	x8, [sp, #688]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3328
	add	x8, x8, #128
	str	x8, [sp, #680]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3472
	add	x8, x8, #128
	str	x8, [sp, #672]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3616
	add	x8, x8, #128
	str	x8, [sp, #664]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #368
	add	x8, x8, #128
	str	x8, [sp, #656]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #512
	add	x8, x8, #128
	str	x8, [sp, #648]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #656
	add	x8, x8, #128
	str	x8, [sp, #640]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1504
	add	x8, x8, #128
	str	x8, [sp, #632]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1648
	add	x8, x8, #128
	str	x8, [sp, #624]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1792
	add	x8, x8, #128
	str	x8, [sp, #616]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2640
	add	x8, x8, #128
	str	x8, [sp, #608]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2784
	add	x8, x8, #128
	str	x8, [sp, #600]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2928
	add	x8, x8, #128
	str	x8, [sp, #592]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3776
	add	x8, x8, #128
	str	x8, [sp, #584]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3920
	add	x8, x8, #128
	str	x8, [sp, #576]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #4064
	add	x8, x8, #128
	str	x8, [sp, #568]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #816
	add	x8, x8, #128
	str	x8, [sp, #560]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #960
	add	x8, x8, #128
	str	x8, [sp, #552]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1104
	add	x8, x8, #128
	str	x8, [sp, #544]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1952
	add	x8, x8, #128
	str	x8, [sp, #536]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2096
	add	x8, x8, #128
	str	x8, [sp, #528]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2240
	add	x8, x8, #128
	str	x8, [sp, #520]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #32
	add	x9, x8, #128
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1168
	add	x8, x8, #128
	stp	x8, x9, [sp, #504]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2304
	add	x9, x8, #128
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3440
	add	x8, x8, #128
	stp	x8, x9, [sp, #488]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #480
	add	x9, x8, #128
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1616
	add	x8, x8, #128
	stp	x8, x9, [sp, #472]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2752
	add	x9, x8, #128
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3888
	add	x8, x8, #128
	stp	x8, x9, [sp, #456]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #928
	add	x9, x8, #128
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2064
	add	x8, x8, #128
	stp	x8, x9, [sp, #440]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3200
	add	x9, x8, #128
	add	x8, sp, #4, lsl #12
	add	x8, x8, #240
	add	x8, x8, #128
	stp	x8, x9, [sp, #424]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1376
	add	x9, x8, #128
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2512
	add	x8, x8, #128
	stp	x8, x9, [sp, #408]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3088
	add	x9, x8, #128
	add	x8, sp, #1, lsl #12
	add	x8, x8, #176
	add	x8, x8, #128
	stp	x8, x9, [sp, #392]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1312
	add	x9, x8, #128
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2448
	add	x8, x8, #128
	stp	x8, x9, [sp, #376]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3584
	add	x9, x8, #128
	add	x8, sp, #2, lsl #12
	add	x8, x8, #624
	add	x8, x8, #128
	stp	x8, x9, [sp, #360]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1760
	add	x9, x8, #128
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2896
	add	x8, x8, #128
	stp	x8, x9, [sp, #344]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #4032
	add	x9, x8, #128
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1072
	add	x8, x8, #128
	stp	x8, x9, [sp, #328]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2208
	add	x9, x8, #128
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3344
	add	x8, x8, #128
	stp	x8, x9, [sp, #312]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #384
	add	x9, x8, #128
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1520
	add	x8, x8, #128
	stp	x8, x9, [sp, #296]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2656
	add	x9, x8, #128
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3232
	add	x8, x8, #128
	stp	x8, x9, [sp, #280]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #320
	add	x9, x8, #128
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1456
	add	x8, x8, #128
	stp	x8, x9, [sp, #264]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2592
	add	x9, x8, #128
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3728
	add	x8, x8, #128
	stp	x8, x9, [sp, #248]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #768
	add	x9, x8, #128
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1904
	add	x8, x8, #128
	stp	x8, x9, [sp, #232]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3040
	add	x9, x8, #128
	add	x8, sp, #3, lsl #12
	add	x8, x8, #80
	add	x8, x8, #128
	stp	x8, x9, [sp, #216]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1216
	add	x9, x8, #128
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2352
	add	x8, x8, #128
	stp	x8, x9, [sp, #200]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3488
	add	x9, x8, #128
	add	x8, sp, #4, lsl #12
	add	x8, x8, #528
	add	x8, x8, #128
	stp	x8, x9, [sp, #184]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1664
	add	x9, x8, #128
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2800
	add	x8, x8, #128
	stp	x8, x9, [sp, #168]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3376
	add	x9, x8, #128
	add	x8, sp, #1, lsl #12
	add	x8, x8, #464
	add	x8, x8, #128
	stp	x8, x9, [sp, #152]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1600
	add	x9, x8, #128
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2736
	add	x8, x8, #128
	stp	x8, x9, [sp, #136]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3872
	add	x9, x8, #128
	add	x8, sp, #2, lsl #12
	add	x8, x8, #912
	add	x8, x8, #128
	stp	x8, x9, [sp, #120]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2048
	add	x9, x8, #128
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3184
	add	x8, x8, #128
	stp	x8, x9, [sp, #104]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #224
	add	x9, x8, #128
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1360
	add	x8, x8, #128
	stp	x8, x9, [sp, #88]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #2496
	add	x9, x8, #128
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3632
	add	x8, x8, #128
	stp	x8, x9, [sp, #72]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #672
	add	x9, x8, #128
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1808
	add	x8, x8, #128
	stp	x8, x9, [sp, #56]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2944
	add	x9, x8, #128
	add	x8, sp, #4, lsl #12
	add	x8, x8, #3520
	add	x8, x8, #128
	stp	x8, x9, [sp, #40]
	mov	x23, #-4294967296
	mov	x26, #4294967296
	mov	x20, #-8589934592
	mov	w9, #1
	str	s11, [sp, #1708]
	str	s12, [sp, #1704]
	str	x24, [sp, #1696]
	str	s14, [sp, #1692]
	str	s15, [sp, #1688]
	str	s4, [sp, #1672]
	str	s5, [sp, #1668]
	str	s6, [sp, #1664]
	str	s7, [sp, #1660]
	str	s16, [sp, #1656]
	str	s17, [sp, #1652]
	str	x13, [sp, #1616]
	str	x14, [sp, #1608]
	str	x15, [sp, #1584]
	str	x16, [sp, #1560]
	str	x17, [sp, #1552]
	str	x0, [sp, #1496]
	str	x1, [sp, #1440]
	str	x2, [sp, #1384]
	str	x3, [sp, #1328]
	str	x4, [sp, #1272]
	str	x5, [sp, #1216]
	str	x6, [sp, #1160]
	str	x7, [sp, #1104]
	str	x30, [sp, #1048]
	str	s1, [sp, #924]
	str	x10, [sp, #2056]
	str	x11, [sp, #864]
	str	x22, [sp, #856]
	stp	x28, x27, [sp, #24]
	stp	x25, x21, [sp, #8]
LBB0_5:
	mov	x8, #0
	str	w9, [sp, #1972]
	ldur	q0, [x19, #88]
	str	q0, [sp, #2352]
LBB0_6:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	x11, [sp, #2056]
	ldr	s0, [x11, x10]
	ldr	x10, [sp, #2056]
	fmadd	s0, s12, s0, s1
	str	s0, [x10, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_6
	str	x12, [sp, #1960]
	mov	x8, #0
	add	x9, sp, #2352
	ldur	q0, [x9, #128]
	stur	q0, [x19, #88]
	ldr	s0, [x19, #104]
	ldr	s8, [sp, #1684]
	ldr	s9, [sp, #1680]
	ldr	s10, [sp, #1676]
	add	x9, sp, #2496
LBB0_8:
	ldr	s1, [x10, x8]
	fmul	s1, s0, s1
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB0_8
	mov	x24, #0
	add	x21, sp, #2624
LBB0_10:
	ldr	s0, [x9, x24]
	bl	_sinf
	add	x9, sp, #2496
	str	s0, [x21, x24]
	add	x24, x24, #4
	cmp	x24, #128
	b.ne	LBB0_10
	mov	x24, #0
	add	x28, sp, #2496
	add	x21, sp, #2752
LBB0_12:
	ldr	s0, [x28, x24]
	bl	_cosf
	str	s0, [x21, x24]
	add	x24, x24, #4
	cmp	x24, #128
	b.ne	LBB0_12
	mov	x8, #0
	ldur	q0, [x19, #124]
	str	q0, [sp, #3024]
	ldr	x9, [sp, #872]
	mov	w10, #1
LBB0_14:
	str	w10, [x9, x8, lsl #2]
	add	w8, w8, #1
	sxtw	x8, w8
	cmp	x8, #32
	b.lt	LBB0_14
	mov	x8, #0
	add	x9, sp, #3024
	ldur	q0, [x9, #128]
	stur	q0, [x19, #124]
	ldur	q0, [x19, #40]
	str	q0, [sp, #2208]
	ldr	x13, [sp, #1736]
	ldr	w14, [sp, #1732]
	ldr	s1, [sp, #928]
	ldr	x11, [sp, #880]
	add	x12, x19, #404
	ldr	x15, [sp, #1984]
	ldr	x28, [sp, #24]
	add	x30, sp, #3584
LBB0_16:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s0, [x15, x10]
	fmadd	s0, s0, s14, s1
	str	s0, [x15, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_16
	mov	x8, #0
	add	x9, sp, #2208
	ldur	q0, [x9, #128]
	stur	q0, [x19, #40]
	ldur	q0, [x19, #108]
	str	q0, [sp, #2880]
	ldur	q0, [x19, #140]
	str	q0, [sp, #3168]
	ldr	x9, [sp, #1960]
	lsl	x9, x9, #3
	ldr	x10, [sp, #1720]
	add	x10, x10, x9
	str	x10, [sp, #1952]
	ldr	x10, [sp, #1712]
	add	x9, x10, x9
	str	x9, [sp, #1960]
	ldr	s0, [sp, #3180]
	ldr	s1, [sp, #2892]
	ldr	s6, [sp, #1668]
	ldr	s7, [sp, #1664]
	ldr	s16, [sp, #1660]
	ldr	s17, [sp, #1656]
	ldr	s18, [sp, #1652]
	ldr	x15, [sp, #1608]
	ldr	x16, [sp, #1560]
	ldr	x17, [sp, #1552]
	ldr	x0, [sp, #1496]
	ldr	x1, [sp, #1440]
	ldr	x2, [sp, #1384]
	ldr	x3, [sp, #1328]
	ldr	x4, [sp, #1272]
	ldr	x5, [sp, #1216]
	ldr	x6, [sp, #1160]
	ldr	x7, [sp, #1104]
	fmov	s19, #0.50000000
	movi.2d	v20, #0000000000000000
	fmov	s21, #-1.00000000
	ldr	x10, [sp, #1976]
	ldr	x24, [sp, #864]
	mov	w27, #1
	add	x21, sp, #2624
	add	x25, sp, #2752
LBB0_18:
	ldr	s2, [x21, x8]
	ldr	s3, [x25, x8]
	fmul	s4, s1, s3
	fmadd	s4, s0, s2, s4
	str	s4, [x10, x8]
	ldr	w9, [x11, x8]
	sub	w9, w27, w9
	scvtf	s5, w9
	fmadd	s0, s0, s3, s5
	fmsub	s0, s2, s1, s0
	str	s0, [x24, x8]
	add	x8, x8, #4
	mov.16b	v1, v4
	cmp	x8, #128
	b.ne	LBB0_18
	mov	x8, #0
	add	x9, sp, #2880
	ldur	q0, [x9, #128]
	stur	q0, [x19, #108]
	add	x9, sp, #3168
	ldur	q0, [x9, #128]
	stur	q0, [x19, #140]
	ldur	q0, [x19, #16]
	str	q0, [sp, #2064]
	ldr	s1, [sp, #932]
	ldr	x11, [sp, #2040]
LBB0_20:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s0, [x11, x10]
	fmadd	s0, s0, s14, s1
	str	s0, [x11, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_20
	mov	x8, #0
	add	x9, sp, #2064
	ldur	q0, [x9, #128]
	stur	q0, [x19, #16]
	ldur	q0, [x19, #168]
	str	q0, [sp, #3312]
	ldr	s5, [sp, #1672]
	ldr	s1, [sp, #920]
	ldr	x24, [sp, #2048]
	ldr	x27, [sp, #32]
	ldp	x25, x21, [sp, #8]
LBB0_22:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s0, [x24, x10]
	fmadd	s0, s0, s14, s1
	str	s0, [x24, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_22
	mov	x8, #0
	add	x9, sp, #3312
	ldur	q0, [x9, #128]
	stur	q0, [x19, #168]
	ldr	x9, [sp, #1984]
	ldr	x10, [sp, #1976]
	add	x24, sp, #3456
LBB0_24:
	ldr	s0, [x9, x8]
	ldr	s1, [x10, x8]
	fmul	s0, s0, s1
	str	s0, [x24, x8]
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB0_24
	mov	x8, #0
	ldr	x9, [sp, #2048]
	ldr	x22, [sp, #856]
	b	LBB0_28
LBB0_26:
	fmul	s1, s1, s15
	fminnm	s1, s1, s8
	fmaxnm	s1, s1, s9
	fmadd	s2, s1, s10, s19
	frintm	s3, s2
	fcvtms	w9, s2
	mov	w10, #1065353216
	add	w9, w10, w9, lsl #23
	fmov	s2, w9
	fmadd	s3, s3, s5, s1
	fmadd	s4, s3, s7, s6
	fmadd	s4, s4, s3, s16
	fmadd	s4, s4, s3, s17
	fmadd	s4, s4, s3, s18
	fmadd	s4, s4, s3, s19
	fmadd	s4, s4, s3, s13
	fmadd	s3, s4, s3, s13
	fmul	s2, s3, s2
	fmaxnm	s1, s2, s1
LBB0_27:
	ldr	s2, [x11, x8, lsl #2]
	fmadd	s0, s0, s1, s2
	fminnm	s0, s0, s13
	fmaxnm	s0, s0, s21
	str	s0, [x30, x8, lsl #2]
	add	x8, x8, #1
	cmp	x8, #32
	ldr	x9, [sp, #2048]
	b.eq	LBB0_42
LBB0_28:
	movi.2d	v0, #0000000000000000
	cbz	w14, LBB0_32
	ldr	s1, [x9, x8, lsl #2]
	fadd	s1, s1, s1
	fcmp	s1, s13
	b.pl	LBB0_33
LBB0_30:
	fcmp	s1, #0.0
	b.pl	LBB0_34
	fneg	s2, s1
	fmov	w9, s2
	mov	w10, #150
	sub	w10, w10, w9, lsr #23
	mov	w11, #-1
	lsl	w10, w11, w10
	lsr	w11, w9, #24
	cmp	w11, #75
	ldr	x11, [sp, #2040]
	mov	w30, #2147483647
	csel	w10, w10, w30, lo
	add	x30, sp, #3584
	and	w9, w10, w9
	fmov	s2, w9
	fcmp	s1, s21
	fcsel	s2, s20, s2, gt
	fneg	s2, s2
	fcmp	s2, s1
	b.eq	LBB0_37
	b	LBB0_26
LBB0_32:
	ldr	s0, [x24, x8, lsl #2]
	ldr	s1, [x9, x8, lsl #2]
	fadd	s1, s1, s1
	fcmp	s1, s13
	b.mi	LBB0_30
LBB0_33:
	fmov	w9, s1
	lsr	w10, w9, #23
	mov	x30, x19
	mov	x19, x28
	mov	w28, #150
	subs	w10, w28, w10, uxtb
	mov	x28, x19
	mov	x19, x30
	mov	w30, #-1
	lsl	w10, w30, w10
	add	x30, sp, #3584
	csinv	w10, w10, wzr, hi
	and	w9, w10, w9
	fmov	s2, w9
	fcmp	s2, s1
	b.eq	LBB0_37
	b	LBB0_26
LBB0_34:
	b.ne	LBB0_36
	mov.16b	v2, v1
	fcmp	s2, s1
	b.eq	LBB0_37
	b	LBB0_26
LBB0_36:
	movi.2d	v2, #0000000000000000
	fcmp	s2, s1
	b.ne	LBB0_26
LBB0_37:
	fcvtzs	w9, s2
	cmp	w9, #0
	cneg	w10, w9, mi
	cmp	w10, #1
	b.lt	LBB0_40
	fmov	s2, #10.00000000
	fmov	s1, #1.00000000
LBB0_39:
	fmul	s3, s1, s2
	tst	w10, #0x1
	fcsel	s1, s1, s3, eq
	fmul	s2, s2, s2
	lsr	w10, w10, #1
	cbnz	w10, LBB0_39
	b	LBB0_41
LBB0_40:
	fmov	s1, #1.00000000
LBB0_41:
	fdiv	s2, s13, s1
	cmp	w9, #0
	fcsel	s1, s2, s1, mi
	b	LBB0_27
LBB0_42:
	mov	x8, #0
	ldur	q0, [x19, #192]
	str	q0, [sp, #3712]
	ldr	x11, [sp, #848]
	mov	w9, #43691
	movk	w9, #48810, lsl #16
LBB0_43:
	ldr	s0, [x30, x8]
	fmul	s1, s0, s0
	fmov	s2, w9
	fmadd	s1, s1, s2, s13
	fmul	s0, s0, s1
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB0_43
	mov	x8, #0
	add	x9, sp, #3712
	ldur	q0, [x9, #128]
	stur	q0, [x19, #192]
	ldur	q0, [x19, #208]
	str	q0, [sp, #3856]
	ldr	x14, [sp, #1616]
	mov	w24, #47186
	movk	w24, #16254, lsl #16
LBB0_45:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s0, [x13, x10]
	fmov	s1, w24
	ldr	s2, [x11, x8, lsl #2]
	fmadd	s0, s0, s1, s2
	ldr	s1, [x11, x10]
	fsub	s0, s0, s1
	str	s0, [x13, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_45
	mov	x8, #0
	add	x9, sp, #3856
	ldur	q0, [x9, #128]
	stur	q0, [x19, #208]
	ldr	x9, [sp, #832]
	add	x10, sp, #4000
LBB0_47:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB0_47
	mov	x8, #0
	ldr	x13, [sp, #1632]
	add	x9, sp, #1, lsl #12
	add	x9, x9, #608
	ldr	x24, [sp, #1048]
LBB0_49:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_49
	ldr	s0, [x19, #392]
	ldr	s1, [x19, #400]
	ldr	s2, [x19, #396]
	add	x8, sp, #4000
	mov	x9, x14
	mov	w10, #32
	ldr	s3, [sp, #4716]
LBB0_51:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_51
	mov	x8, #0
	ldr	x9, [sp, #824]
LBB0_53:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_53
	mov	x8, #0
	add	x12, x19, #444
	add	x9, sp, #1, lsl #12
	add	x9, x9, #752
LBB0_55:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_55
	mov	x8, #0
	ldr	s2, [x19, #424]
	ldr	s3, [x19, #428]
	ldr	s4, [x19, #436]
	ldr	s5, [x19, #440]
	ldr	s1, [x19, #432]
LBB0_57:
	ldr	s6, [x14, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x14, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x14, x11]
	ldr	s16, [x15, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x15, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x15, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_57
	mov	x8, #0
	ldr	x9, [sp, #816]
LBB0_59:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_59
	mov	x8, #0
	ldr	x14, [sp, #1600]
	add	x12, x19, #480
	add	x9, sp, #1, lsl #12
	add	x9, x9, #896
LBB0_61:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_61
	mov	x8, #0
	ldr	s2, [x19, #460]
	ldr	s3, [x19, #464]
	ldr	s4, [x19, #472]
	ldr	s5, [x19, #476]
	ldr	s0, [x19, #468]
LBB0_63:
	ldr	s6, [x15, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x15, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x15, x11]
	ldr	s16, [x14, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x14, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x14, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_63
	mov	x8, #0
	ldr	x9, [sp, #808]
LBB0_65:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_65
	mov	x8, #0
	ldr	d1, [x19, #496]
	mov	x9, x14
	ldr	x15, [sp, #1584]
	add	x11, x19, #668
	add	x10, sp, #1, lsl #12
	add	x10, x10, #1040
LBB0_67:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_67
	mov	x8, #0
	ldr	x14, [sp, #1592]
	add	x12, x19, #708
	add	x9, sp, #1, lsl #12
	add	x9, x9, #1744
LBB0_69:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_69
	ldr	s0, [x19, #656]
	ldr	s1, [x19, #664]
	ldr	s2, [x19, #660]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1040
	mov	x9, x16
	mov	w10, #32
	ldr	s3, [sp, #5852]
LBB0_71:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_71
	mov	x8, #0
	ldr	x9, [sp, #800]
LBB0_73:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_73
	mov	x8, #0
	add	x9, sp, #1, lsl #12
	add	x9, x9, #1888
LBB0_75:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_75
	mov	x8, #0
	ldr	s2, [x19, #688]
	ldr	s3, [x19, #692]
	ldr	s4, [x19, #700]
	ldr	s5, [x19, #704]
	ldr	s1, [x19, #696]
LBB0_77:
	ldr	s6, [x16, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x16, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x16, x11]
	ldr	s16, [x17, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x17, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x17, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_77
	mov	x8, #0
	ldr	x9, [sp, #792]
LBB0_79:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_79
	mov	x8, #0
	ldr	x16, [sp, #1544]
	add	x12, x19, #744
	add	x9, sp, #1, lsl #12
	add	x9, x9, #2032
LBB0_81:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_81
	mov	x8, #0
	ldr	s2, [x19, #724]
	ldr	s3, [x19, #728]
	ldr	s4, [x19, #736]
	ldr	s5, [x19, #740]
	ldr	s0, [x19, #732]
LBB0_83:
	ldr	s6, [x17, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x17, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x17, x11]
	ldr	s16, [x16, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x16, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x16, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_83
	mov	x8, #0
	ldr	x9, [sp, #784]
LBB0_85:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_85
	mov	x8, #0
	ldr	d1, [x19, #760]
	mov	x9, x16
	ldr	x17, [sp, #1504]
	add	x11, x19, #932
	add	x10, sp, #1, lsl #12
	add	x10, x10, #2176
LBB0_87:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_87
	mov	x8, #0
	ldr	x16, [sp, #1536]
	add	x12, x19, #972
	add	x9, sp, #1, lsl #12
	add	x9, x9, #2880
LBB0_89:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_89
	ldr	s0, [x19, #920]
	ldr	s1, [x19, #928]
	ldr	s2, [x19, #924]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2176
	mov	x9, x17
	mov	w10, #32
	ldr	s3, [sp, #6988]
LBB0_91:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_91
	mov	x8, #0
	ldr	x9, [sp, #776]
LBB0_93:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_93
	mov	x8, #0
	add	x9, sp, #1, lsl #12
	add	x9, x9, #3024
LBB0_95:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_95
	mov	x8, #0
	ldr	s2, [x19, #952]
	ldr	s3, [x19, #956]
	ldr	s4, [x19, #964]
	ldr	s5, [x19, #968]
	ldr	s1, [x19, #960]
LBB0_97:
	ldr	s6, [x17, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x17, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x17, x11]
	ldr	s16, [x0, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x0, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x0, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_97
	mov	x8, #0
	ldr	x9, [sp, #768]
LBB0_99:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_99
	mov	x8, #0
	ldr	x17, [sp, #1488]
	add	x12, x19, #1008
	add	x9, sp, #1, lsl #12
	add	x9, x9, #3168
LBB0_101:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_101
	mov	x8, #0
	ldr	s2, [x19, #988]
	ldr	s3, [x19, #992]
	ldr	s4, [x19, #1000]
	ldr	s5, [x19, #1004]
	ldr	s0, [x19, #996]
LBB0_103:
	ldr	s6, [x0, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x0, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x0, x11]
	ldr	s16, [x17, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x17, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x17, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_103
	mov	x8, #0
	ldr	x9, [sp, #760]
LBB0_105:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_105
	mov	x8, #0
	ldr	d1, [x19, #1024]
	mov	x9, x17
	ldr	x0, [sp, #1448]
	add	x11, x19, #1196
	add	x10, sp, #1, lsl #12
	add	x10, x10, #3312
LBB0_107:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_107
	mov	x8, #0
	ldr	x17, [sp, #1480]
	add	x12, x19, #1236
	add	x9, sp, #1, lsl #12
	add	x9, x9, #4016
LBB0_109:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_109
	ldr	s0, [x19, #1184]
	ldr	s1, [x19, #1192]
	ldr	s2, [x19, #1188]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3312
	mov	x9, x0
	mov	w10, #32
	ldr	s3, [sp, #8124]
LBB0_111:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_111
	mov	x8, #0
	ldr	x9, [sp, #752]
LBB0_113:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_113
	mov	x8, #0
	add	x9, sp, #2, lsl #12
	add	x9, x9, #64
LBB0_115:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_115
	mov	x8, #0
	ldr	s2, [x19, #1216]
	ldr	s3, [x19, #1220]
	ldr	s4, [x19, #1228]
	ldr	s5, [x19, #1232]
	ldr	s1, [x19, #1224]
LBB0_117:
	ldr	s6, [x0, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x0, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x0, x11]
	ldr	s16, [x1, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x1, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x1, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_117
	mov	x8, #0
	ldr	x9, [sp, #744]
LBB0_119:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_119
	mov	x8, #0
	ldr	x0, [sp, #1432]
	add	x12, x19, #1272
	add	x9, sp, #2, lsl #12
	add	x9, x9, #208
LBB0_121:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_121
	mov	x8, #0
	ldr	s2, [x19, #1252]
	ldr	s3, [x19, #1256]
	ldr	s4, [x19, #1264]
	ldr	s5, [x19, #1268]
	ldr	s0, [x19, #1260]
LBB0_123:
	ldr	s6, [x1, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x1, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x1, x11]
	ldr	s16, [x0, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x0, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x0, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_123
	mov	x8, #0
	ldr	x9, [sp, #736]
LBB0_125:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_125
	mov	x8, #0
	ldr	d1, [x19, #1288]
	mov	x9, x0
	ldr	x1, [sp, #1392]
	add	x11, x19, #1460
	add	x10, sp, #2, lsl #12
	add	x10, x10, #352
LBB0_127:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_127
	mov	x8, #0
	ldr	x0, [sp, #1424]
	add	x12, x19, #1500
	add	x9, sp, #2, lsl #12
	add	x9, x9, #1056
LBB0_129:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_129
	ldr	s0, [x19, #1448]
	ldr	s1, [x19, #1456]
	ldr	s2, [x19, #1452]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #352
	mov	x9, x1
	mov	w10, #32
	ldr	s3, [sp, #9260]
LBB0_131:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_131
	mov	x8, #0
	ldr	x9, [sp, #728]
LBB0_133:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_133
	mov	x8, #0
	add	x9, sp, #2, lsl #12
	add	x9, x9, #1200
LBB0_135:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_135
	mov	x8, #0
	ldr	s2, [x19, #1480]
	ldr	s3, [x19, #1484]
	ldr	s4, [x19, #1492]
	ldr	s5, [x19, #1496]
	ldr	s1, [x19, #1488]
LBB0_137:
	ldr	s6, [x1, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x1, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x1, x11]
	ldr	s16, [x2, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x2, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x2, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_137
	mov	x8, #0
	ldr	x9, [sp, #720]
LBB0_139:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_139
	mov	x8, #0
	ldr	x1, [sp, #1376]
	add	x12, x19, #1536
	add	x9, sp, #2, lsl #12
	add	x9, x9, #1344
LBB0_141:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_141
	mov	x8, #0
	ldr	s2, [x19, #1516]
	ldr	s3, [x19, #1520]
	ldr	s4, [x19, #1528]
	ldr	s5, [x19, #1532]
	ldr	s0, [x19, #1524]
LBB0_143:
	ldr	s6, [x2, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x2, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x2, x11]
	ldr	s16, [x1, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x1, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x1, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_143
	mov	x8, #0
	ldr	x9, [sp, #712]
LBB0_145:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_145
	mov	x8, #0
	ldr	d1, [x19, #1552]
	mov	x9, x1
	ldr	x2, [sp, #1336]
	add	x11, x19, #1724
	add	x10, sp, #2, lsl #12
	add	x10, x10, #1488
LBB0_147:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_147
	mov	x8, #0
	ldr	x1, [sp, #1368]
	add	x12, x19, #1764
	add	x9, sp, #2, lsl #12
	add	x9, x9, #2192
LBB0_149:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_149
	ldr	s0, [x19, #1712]
	ldr	s1, [x19, #1720]
	ldr	s2, [x19, #1716]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1488
	mov	x9, x2
	mov	w10, #32
	ldr	s3, [sp, #10396]
LBB0_151:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_151
	mov	x8, #0
	ldr	x9, [sp, #704]
LBB0_153:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_153
	mov	x8, #0
	add	x9, sp, #2, lsl #12
	add	x9, x9, #2336
LBB0_155:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_155
	mov	x8, #0
	ldr	s2, [x19, #1744]
	ldr	s3, [x19, #1748]
	ldr	s4, [x19, #1756]
	ldr	s5, [x19, #1760]
	ldr	s1, [x19, #1752]
LBB0_157:
	ldr	s6, [x2, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x2, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x2, x11]
	ldr	s16, [x3, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x3, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x3, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_157
	mov	x8, #0
	ldr	x9, [sp, #696]
LBB0_159:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_159
	mov	x8, #0
	ldr	x2, [sp, #1320]
	add	x12, x19, #1800
	add	x9, sp, #2, lsl #12
	add	x9, x9, #2480
LBB0_161:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_161
	mov	x8, #0
	ldr	s2, [x19, #1780]
	ldr	s3, [x19, #1784]
	ldr	s4, [x19, #1792]
	ldr	s5, [x19, #1796]
	ldr	s0, [x19, #1788]
LBB0_163:
	ldr	s6, [x3, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x3, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x3, x11]
	ldr	s16, [x2, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x2, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x2, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_163
	mov	x8, #0
	ldr	x9, [sp, #688]
LBB0_165:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_165
	mov	x8, #0
	ldr	d1, [x19, #1816]
	mov	x9, x2
	ldr	x3, [sp, #1280]
	add	x11, x19, #1988
	add	x10, sp, #2, lsl #12
	add	x10, x10, #2624
LBB0_167:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_167
	mov	x8, #0
	ldr	x2, [sp, #1312]
	add	x12, x19, #2028
	add	x9, sp, #2, lsl #12
	add	x9, x9, #3328
LBB0_169:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_169
	ldr	s0, [x19, #1976]
	ldr	s1, [x19, #1984]
	ldr	s2, [x19, #1980]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2624
	mov	x9, x3
	mov	w10, #32
	ldr	s3, [sp, #11532]
LBB0_171:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_171
	mov	x8, #0
	ldr	x9, [sp, #680]
LBB0_173:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_173
	mov	x8, #0
	add	x9, sp, #2, lsl #12
	add	x9, x9, #3472
LBB0_175:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_175
	mov	x8, #0
	ldr	s2, [x19, #2008]
	ldr	s3, [x19, #2012]
	ldr	s4, [x19, #2020]
	ldr	s5, [x19, #2024]
	ldr	s1, [x19, #2016]
LBB0_177:
	ldr	s6, [x3, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x3, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x3, x11]
	ldr	s16, [x4, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x4, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x4, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_177
	mov	x8, #0
	ldr	x9, [sp, #672]
LBB0_179:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_179
	mov	x8, #0
	ldr	x3, [sp, #1264]
	add	x12, x19, #2064
	add	x9, sp, #2, lsl #12
	add	x9, x9, #3616
LBB0_181:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_181
	mov	x8, #0
	ldr	s2, [x19, #2044]
	ldr	s3, [x19, #2048]
	ldr	s4, [x19, #2056]
	ldr	s5, [x19, #2060]
	ldr	s0, [x19, #2052]
LBB0_183:
	ldr	s6, [x4, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x4, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x4, x11]
	ldr	s16, [x3, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x3, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x3, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_183
	mov	x8, #0
	ldr	x9, [sp, #664]
LBB0_185:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_185
	mov	x8, #0
	ldr	d1, [x19, #2080]
	mov	x9, x3
	ldr	x4, [sp, #1224]
	add	x11, x19, #2252
	add	x10, sp, #2, lsl #12
	add	x10, x10, #3760
LBB0_187:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_187
	mov	x8, #0
	ldr	x3, [sp, #1256]
	add	x12, x19, #2292
	add	x9, sp, #3, lsl #12
	add	x9, x9, #368
LBB0_189:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_189
	ldr	s0, [x19, #2240]
	ldr	s1, [x19, #2248]
	ldr	s2, [x19, #2244]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3760
	mov	x9, x4
	mov	w10, #32
	ldr	s3, [sp, #12668]
LBB0_191:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_191
	mov	x8, #0
	ldr	x9, [sp, #656]
LBB0_193:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_193
	mov	x8, #0
	add	x9, sp, #3, lsl #12
	add	x9, x9, #512
LBB0_195:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_195
	mov	x8, #0
	ldr	s2, [x19, #2272]
	ldr	s3, [x19, #2276]
	ldr	s4, [x19, #2284]
	ldr	s5, [x19, #2288]
	ldr	s1, [x19, #2280]
LBB0_197:
	ldr	s6, [x4, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x4, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x4, x11]
	ldr	s16, [x5, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x5, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x5, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_197
	mov	x8, #0
	ldr	x9, [sp, #648]
LBB0_199:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_199
	mov	x8, #0
	ldr	x4, [sp, #1208]
	add	x12, x19, #2328
	add	x9, sp, #3, lsl #12
	add	x9, x9, #656
LBB0_201:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_201
	mov	x8, #0
	ldr	s2, [x19, #2308]
	ldr	s3, [x19, #2312]
	ldr	s4, [x19, #2320]
	ldr	s5, [x19, #2324]
	ldr	s0, [x19, #2316]
LBB0_203:
	ldr	s6, [x5, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x5, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x5, x11]
	ldr	s16, [x4, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x4, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x4, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_203
	mov	x8, #0
	ldr	x9, [sp, #640]
LBB0_205:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_205
	mov	x8, #0
	ldr	d1, [x19, #2344]
	mov	x9, x4
	ldr	x5, [sp, #1168]
	add	x11, x19, #2516
	add	x10, sp, #3, lsl #12
	add	x10, x10, #800
LBB0_207:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_207
	mov	x8, #0
	ldr	x4, [sp, #1200]
	add	x12, x19, #2556
	add	x9, sp, #3, lsl #12
	add	x9, x9, #1504
LBB0_209:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_209
	ldr	s0, [x19, #2504]
	ldr	s1, [x19, #2512]
	ldr	s2, [x19, #2508]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #800
	mov	x9, x5
	mov	w10, #32
	ldr	s3, [sp, #13804]
LBB0_211:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_211
	mov	x8, #0
	ldr	x9, [sp, #632]
LBB0_213:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_213
	mov	x8, #0
	add	x9, sp, #3, lsl #12
	add	x9, x9, #1648
LBB0_215:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_215
	mov	x8, #0
	ldr	s2, [x19, #2536]
	ldr	s3, [x19, #2540]
	ldr	s4, [x19, #2548]
	ldr	s5, [x19, #2552]
	ldr	s1, [x19, #2544]
LBB0_217:
	ldr	s6, [x5, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x5, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x5, x11]
	ldr	s16, [x6, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x6, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x6, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_217
	mov	x8, #0
	ldr	x9, [sp, #624]
LBB0_219:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_219
	mov	x8, #0
	ldr	x5, [sp, #1152]
	add	x12, x19, #2592
	add	x9, sp, #3, lsl #12
	add	x9, x9, #1792
LBB0_221:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_221
	mov	x8, #0
	ldr	s2, [x19, #2572]
	ldr	s3, [x19, #2576]
	ldr	s4, [x19, #2584]
	ldr	s5, [x19, #2588]
	ldr	s0, [x19, #2580]
LBB0_223:
	ldr	s6, [x6, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x6, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x6, x11]
	ldr	s16, [x5, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x5, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x5, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_223
	mov	x8, #0
	ldr	x9, [sp, #616]
LBB0_225:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_225
	mov	x8, #0
	ldr	d1, [x19, #2608]
	mov	x9, x5
	ldr	x6, [sp, #1112]
	add	x11, x19, #2780
	add	x10, sp, #3, lsl #12
	add	x10, x10, #1936
LBB0_227:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_227
	mov	x8, #0
	ldr	x5, [sp, #1144]
	add	x12, x19, #2820
	add	x9, sp, #3, lsl #12
	add	x9, x9, #2640
LBB0_229:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_229
	ldr	s0, [x19, #2768]
	ldr	s1, [x19, #2776]
	ldr	s2, [x19, #2772]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1936
	mov	x9, x6
	mov	w10, #32
	ldr	s3, [sp, #14940]
LBB0_231:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_231
	mov	x8, #0
	ldr	x9, [sp, #608]
LBB0_233:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_233
	mov	x8, #0
	add	x9, sp, #3, lsl #12
	add	x9, x9, #2784
LBB0_235:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_235
	mov	x8, #0
	ldr	s2, [x19, #2800]
	ldr	s3, [x19, #2804]
	ldr	s4, [x19, #2812]
	ldr	s5, [x19, #2816]
	ldr	s1, [x19, #2808]
LBB0_237:
	ldr	s6, [x6, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x6, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x6, x11]
	ldr	s16, [x7, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x7, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x7, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_237
	mov	x8, #0
	ldr	x9, [sp, #600]
LBB0_239:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_239
	mov	x8, #0
	ldr	x6, [sp, #1096]
	add	x12, x19, #2856
	add	x9, sp, #3, lsl #12
	add	x9, x9, #2928
LBB0_241:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_241
	mov	x8, #0
	ldr	s2, [x19, #2836]
	ldr	s3, [x19, #2840]
	ldr	s4, [x19, #2848]
	ldr	s5, [x19, #2852]
	ldr	s0, [x19, #2844]
LBB0_243:
	ldr	s6, [x7, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x7, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x7, x11]
	ldr	s16, [x6, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x6, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x6, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_243
	mov	x8, #0
	ldr	x9, [sp, #592]
LBB0_245:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_245
	mov	x8, #0
	ldr	d1, [x19, #2872]
	mov	x9, x6
	ldr	x7, [sp, #1056]
	add	x11, x19, #3044
	add	x10, sp, #3, lsl #12
	add	x10, x10, #3072
LBB0_247:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_247
	mov	x8, #0
	ldr	x6, [sp, #1088]
	add	x12, x19, #3084
	add	x9, sp, #3, lsl #12
	add	x9, x9, #3776
LBB0_249:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_249
	ldr	s0, [x19, #3032]
	ldr	s1, [x19, #3040]
	ldr	s2, [x19, #3036]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3072
	mov	x9, x7
	mov	w10, #32
	ldr	s3, [sp, #16076]
LBB0_251:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_251
	mov	x8, #0
	ldr	x9, [sp, #584]
LBB0_253:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_253
	mov	x8, #0
	add	x9, sp, #3, lsl #12
	add	x9, x9, #3920
LBB0_255:
	ldr	s1, [x12, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_255
	mov	x8, #0
	ldr	s2, [x19, #3064]
	ldr	s3, [x19, #3068]
	ldr	s4, [x19, #3076]
	ldr	s5, [x19, #3080]
	ldr	s1, [x19, #3072]
LBB0_257:
	ldr	s6, [x7, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x7, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x7, x11]
	ldr	s16, [x24, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x24, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x24, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_257
	mov	x8, #0
	ldr	x9, [sp, #576]
LBB0_259:
	ldr	s0, [x9, x8]
	str	s0, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_259
	mov	x8, #0
	ldr	x7, [sp, #1040]
	add	x12, x19, #3120
	add	x9, sp, #3, lsl #12
	add	x9, x9, #4064
LBB0_261:
	ldr	s0, [x12, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_261
	mov	x8, #0
	ldr	s2, [x19, #3100]
	ldr	s3, [x19, #3104]
	ldr	s4, [x19, #3112]
	ldr	s5, [x19, #3116]
	ldr	s0, [x19, #3108]
LBB0_263:
	ldr	s6, [x24, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x24, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x24, x11]
	ldr	s16, [x7, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x7, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x7, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_263
	mov	x8, #0
	ldr	x9, [sp, #568]
LBB0_265:
	ldr	s1, [x9, x8]
	str	s1, [x12, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_265
	mov	x8, #0
	ldr	d1, [x19, #3136]
	mov	x9, x7
	ldr	x30, [sp, #1000]
	add	x11, x19, #3308
	add	x10, sp, #4, lsl #12
	add	x10, x10, #112
LBB0_267:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_267
	mov	x8, #0
	ldr	x7, [sp, #1032]
	add	x9, sp, #4, lsl #12
	add	x9, x9, #816
LBB0_269:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_269
	ldr	s0, [x19, #3296]
	ldr	s1, [x19, #3304]
	ldr	s2, [x19, #3300]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #112
	mov	x9, x30
	mov	w10, #32
	add	x12, sp, #832
	ldr	s3, [x12, #16380]
LBB0_271:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_271
	mov	x8, #0
	ldr	x9, [sp, #560]
LBB0_273:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_273
	mov	x8, #0
	add	x9, x19, #3348
	add	x10, sp, #4, lsl #12
	add	x10, x10, #960
LBB0_275:
	ldr	s1, [x9, x8]
	str	s1, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_275
	mov	x8, #0
	ldr	s2, [x19, #3328]
	ldr	s3, [x19, #3332]
	ldr	s4, [x19, #3340]
	ldr	s5, [x19, #3344]
	ldr	s1, [x19, #3336]
	ldr	x12, [sp, #2008]
LBB0_277:
	ldr	s6, [x30, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x30, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x30, x11]
	ldr	s16, [x12, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x12, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x12, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_277
	mov	x8, #0
	add	x9, x19, #3348
	ldr	x10, [sp, #552]
LBB0_279:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_279
	mov	x8, #0
	ldr	x30, [sp, #2008]
	ldr	x12, [sp, #992]
	add	x9, x19, #3384
	add	x10, sp, #4, lsl #12
	add	x10, x10, #1104
LBB0_281:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_281
	mov	x8, #0
	ldr	s2, [x19, #3364]
	ldr	s3, [x19, #3368]
	ldr	s4, [x19, #3376]
	ldr	s5, [x19, #3380]
	ldr	s0, [x19, #3372]
LBB0_283:
	ldr	s6, [x30, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x30, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x30, x11]
	ldr	s16, [x12, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x12, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x12, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_283
	mov	x8, #0
	add	x9, x19, #3384
	ldr	x10, [sp, #544]
LBB0_285:
	ldr	s1, [x10, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_285
	mov	x8, #0
	ldr	d1, [x19, #3400]
	mov	x9, x12
	ldr	x30, [sp, #984]
	add	x11, x19, #3572
	add	x10, sp, #4, lsl #12
	add	x10, x10, #1248
LBB0_287:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_287
	mov	x8, #0
	ldr	x12, [sp, #952]
	add	x9, sp, #4, lsl #12
	add	x9, x9, #1952
LBB0_289:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_289
	ldr	s0, [x19, #3560]
	ldr	s1, [x19, #3568]
	ldr	s2, [x19, #3564]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1248
	add	x24, sp, #4, lsl #12
	add	x24, x24, #1952
	add	x9, x24, #16
	mov	w10, #32
	ldr	s3, [x24, #12]
LBB0_291:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_291
	mov	x8, #0
	ldr	x9, [sp, #536]
LBB0_293:
	ldr	s1, [x9, x8]
	str	s1, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_293
	mov	x8, #0
	add	x9, x19, #3612
	add	x10, sp, #4, lsl #12
	add	x10, x10, #2096
LBB0_295:
	ldr	s1, [x9, x8]
	str	s1, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_295
	mov	x8, #0
	ldr	s2, [x19, #3592]
	ldr	s3, [x19, #3596]
	ldr	s4, [x19, #3604]
	ldr	s5, [x19, #3608]
	ldr	s1, [x19, #3600]
	ldr	x24, [sp, #840]
LBB0_297:
	ldr	s6, [x24, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x24, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x24, x11]
	ldr	s16, [x22, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x22, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s1, s7
	fnmsub	s6, s0, s6, s7
	str	s6, [x22, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_297
	mov	x8, #0
	add	x9, x19, #3612
	ldr	x10, [sp, #528]
LBB0_299:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_299
	mov	x8, #0
	add	x9, x19, #3648
	ldr	x24, [sp, #1696]
	add	x10, sp, #4, lsl #12
	add	x10, x10, #2240
LBB0_301:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_301
	mov	x8, #0
	ldr	s2, [x19, #3628]
	ldr	s3, [x19, #3632]
	ldr	s4, [x19, #3640]
	ldr	s5, [x19, #3644]
	ldr	s0, [x19, #3636]
LBB0_303:
	ldr	s6, [x22, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x22, x10]
	fmul	s7, s3, s7
	fmadd	s6, s2, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x22, x11]
	ldr	s16, [x12, x11]
	fmadd	s6, s2, s7, s6
	ldr	s7, [x12, x10]
	fmul	s7, s5, s7
	fmadd	s7, s4, s16, s7
	fmul	s7, s0, s7
	fnmsub	s6, s1, s6, s7
	str	s6, [x12, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_303
	mov	x8, #0
	add	x9, x19, #3648
	ldr	x10, [sp, #520]
LBB0_305:
	ldr	s1, [x10, x8]
	str	s1, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_305
	mov	x8, #0
	ldr	d1, [x19, #3664]
	mov	x9, x12
	add	x11, x19, #252
	add	x10, sp, #4, lsl #12
	add	x10, x10, #2384
LBB0_307:
	ldr	s2, [x9]
	ldur	d3, [x9, #-8]
	fmul.2s	v3, v1, v3
	mov	s4, v3[1]
	fmadd	s2, s1, s2, s4
	fadd	s2, s2, s3
	fmul	s2, s0, s2
	str	s2, [x10, x8, lsl #2]
	add	x8, x8, #1
	add	x9, x9, #4
	cmp	x8, #32
	b.ne	LBB0_307
	mov	x8, #0
	add	x9, sp, #1, lsl #12
	add	x9, x9, #32
LBB0_309:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_309
	ldr	s0, [x19, #248]
	ldp	s1, s2, [x19, #232]
	add	x8, sp, #4000
	mov	x9, x24
	mov	w10, #32
	ldr	s3, [sp, #4140]
LBB0_311:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s0, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s1, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_311
	mov	x8, #0
	ldr	x9, [sp, #512]
LBB0_313:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_313
	mov	x8, #0
	add	x11, x19, #532
	add	x9, sp, #1, lsl #12
	add	x9, x9, #1168
LBB0_315:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_315
	ldr	s0, [x19, #512]
	ldr	s1, [x19, #528]
	ldr	s2, [x19, #516]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #1040
	mov	x9, x14
	mov	w10, #32
	ldr	s3, [sp, #5276]
LBB0_317:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_317
	mov	x8, #0
	ldr	x9, [sp, #504]
LBB0_319:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_319
	mov	x8, #0
	add	x11, x19, #796
	add	x9, sp, #1, lsl #12
	add	x9, x9, #2304
LBB0_321:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_321
	ldr	s0, [x19, #776]
	ldr	s1, [x19, #792]
	ldr	s2, [x19, #780]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #2176
	mov	x9, x16
	mov	w10, #32
	ldr	s3, [sp, #6412]
LBB0_323:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_323
	mov	x8, #0
	ldr	x9, [sp, #496]
LBB0_325:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_325
	mov	x8, #0
	add	x11, x19, #1060
	add	x9, sp, #1, lsl #12
	add	x9, x9, #3440
LBB0_327:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_327
	ldr	s0, [x19, #1040]
	ldr	s1, [x19, #1056]
	ldr	s2, [x19, #1044]
	add	x8, sp, #1, lsl #12
	add	x8, x8, #3312
	mov	x9, x17
	mov	w10, #32
	ldr	s3, [sp, #7548]
LBB0_329:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_329
	mov	x8, #0
	ldr	x9, [sp, #488]
LBB0_331:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_331
	mov	x8, #0
	add	x11, x19, #1324
	add	x9, sp, #2, lsl #12
	add	x9, x9, #480
LBB0_333:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_333
	ldr	s0, [x19, #1304]
	ldr	s1, [x19, #1320]
	ldr	s2, [x19, #1308]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #352
	mov	x9, x0
	mov	w10, #32
	ldr	s3, [sp, #8684]
LBB0_335:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_335
	mov	x8, #0
	ldr	x9, [sp, #480]
LBB0_337:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_337
	mov	x8, #0
	add	x11, x19, #1588
	add	x9, sp, #2, lsl #12
	add	x9, x9, #1616
LBB0_339:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_339
	ldr	s0, [x19, #1568]
	ldr	s1, [x19, #1584]
	ldr	s2, [x19, #1572]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #1488
	mov	x9, x1
	mov	w10, #32
	ldr	s3, [sp, #9820]
LBB0_341:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_341
	mov	x8, #0
	ldr	x9, [sp, #472]
LBB0_343:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_343
	mov	x8, #0
	add	x11, x19, #1852
	add	x9, sp, #2, lsl #12
	add	x9, x9, #2752
LBB0_345:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_345
	ldr	s0, [x19, #1832]
	ldr	s1, [x19, #1848]
	ldr	s2, [x19, #1836]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #2624
	mov	x9, x2
	mov	w10, #32
	ldr	s3, [sp, #10956]
LBB0_347:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_347
	mov	x8, #0
	ldr	x9, [sp, #464]
LBB0_349:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_349
	mov	x8, #0
	add	x11, x19, #2116
	add	x9, sp, #2, lsl #12
	add	x9, x9, #3888
LBB0_351:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_351
	ldr	s0, [x19, #2096]
	ldr	s1, [x19, #2112]
	ldr	s2, [x19, #2100]
	add	x8, sp, #2, lsl #12
	add	x8, x8, #3760
	mov	x9, x3
	mov	w10, #32
	ldr	s3, [sp, #12092]
LBB0_353:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_353
	mov	x8, #0
	ldr	x9, [sp, #456]
LBB0_355:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_355
	mov	x8, #0
	add	x11, x19, #2380
	add	x9, sp, #3, lsl #12
	add	x9, x9, #928
LBB0_357:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_357
	ldr	s0, [x19, #2360]
	ldr	s1, [x19, #2376]
	ldr	s2, [x19, #2364]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #800
	mov	x9, x4
	mov	w10, #32
	ldr	s3, [sp, #13228]
LBB0_359:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_359
	mov	x8, #0
	ldr	x9, [sp, #448]
LBB0_361:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_361
	mov	x8, #0
	add	x11, x19, #2644
	add	x9, sp, #3, lsl #12
	add	x9, x9, #2064
LBB0_363:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_363
	ldr	s0, [x19, #2624]
	ldr	s1, [x19, #2640]
	ldr	s2, [x19, #2628]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #1936
	mov	x9, x5
	mov	w10, #32
	ldr	s3, [sp, #14364]
LBB0_365:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_365
	mov	x8, #0
	ldr	x9, [sp, #440]
LBB0_367:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_367
	mov	x8, #0
	add	x11, x19, #2908
	add	x9, sp, #3, lsl #12
	add	x9, x9, #3200
LBB0_369:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_369
	ldr	s0, [x19, #2888]
	ldr	s1, [x19, #2904]
	ldr	s2, [x19, #2892]
	add	x8, sp, #3, lsl #12
	add	x8, x8, #3072
	mov	x9, x6
	mov	w10, #32
	ldr	s3, [sp, #15500]
LBB0_371:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_371
	mov	x8, #0
	ldr	x9, [sp, #432]
LBB0_373:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_373
	mov	x8, #0
	add	x11, x19, #3172
	add	x9, sp, #4, lsl #12
	add	x9, x9, #240
LBB0_375:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_375
	ldr	s0, [x19, #3152]
	ldr	s1, [x19, #3168]
	ldr	s2, [x19, #3156]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #112
	mov	x9, x7
	mov	w10, #32
	add	x12, sp, #256
	ldr	s3, [x12, #16380]
LBB0_377:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_377
	mov	x8, #0
	ldr	x9, [sp, #424]
LBB0_379:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_379
	mov	x8, #0
	add	x11, x19, #3436
	add	x9, sp, #4, lsl #12
	add	x9, x9, #1376
LBB0_381:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_381
	ldr	s0, [x19, #3416]
	ldr	s1, [x19, #3432]
	ldr	s2, [x19, #3420]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #1248
	mov	x9, x30
	mov	w10, #32
	add	x12, sp, #1392
	ldr	s3, [x12, #16380]
LBB0_383:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_383
	mov	x8, #0
	ldr	x9, [sp, #416]
LBB0_385:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_385
	mov	x8, #0
	add	x11, x19, #3700
	add	x9, sp, #4, lsl #12
	add	x9, x9, #2512
LBB0_387:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_387
	ldr	s0, [x19, #3680]
	ldr	s1, [x19, #3696]
	ldr	s2, [x19, #3684]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2384
	ldr	x9, [sp, #2000]
	mov	w10, #32
	add	x12, sp, #4, lsl #12
	add	x12, x12, #1952
	ldr	s3, [x12, #572]
LBB0_389:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_389
	mov	x8, #0
	ldr	x9, [sp, #408]
LBB0_391:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_391
	mov	x8, #0
	add	x11, x19, #3836
	add	x9, sp, #4, lsl #12
	add	x9, x9, #3088
LBB0_393:
	ldr	s0, [x11, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_393
	ldr	s0, [x19, #3824]
	ldr	s1, [x19, #3832]
	ldr	s2, [x19, #3828]
	add	x8, sp, #4, lsl #12
	add	x8, x8, #2384
	ldr	x9, [sp, #1992]
	mov	w10, #32
	add	x12, sp, #4, lsl #12
	add	x12, x12, #1952
	ldr	s3, [x12, #1148]
LBB0_395:
	ldr	s4, [x8], #4
	ldur	s5, [x9, #-8]
	fmul	s3, s1, s3
	fmadd	s3, s2, s5, s3
	fmsub	s3, s0, s3, s4
	str	s3, [x9], #4
	subs	x10, x10, #1
	b.ne	LBB0_395
	mov	x8, #0
	ldr	x12, [sp, #1640]
	ldr	x9, [sp, #400]
LBB0_397:
	ldr	s0, [x9, x8]
	str	s0, [x11, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_397
	mov	x8, #0
	add	x9, x19, #292
	add	x10, sp, #1, lsl #12
	add	x10, x10, #176
LBB0_399:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_399
	mov	x8, #0
	ldr	s0, [x19, #272]
	ldr	s1, [x19, #276]
	ldr	s2, [x19, #232]
	ldr	s3, [x19, #284]
	ldr	s4, [x19, #288]
	ldr	s5, [x19, #280]
LBB0_401:
	ldr	s6, [x24, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x24, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x24, x11]
	ldr	s16, [x12, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x12, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x12, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_401
	mov	x8, #0
	add	x9, x19, #292
	ldr	x10, [sp, #392]
LBB0_403:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_403
	mov	x8, #0
	add	x9, x19, #572
	add	x10, sp, #1, lsl #12
	add	x10, x10, #1312
LBB0_405:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_405
	mov	x8, #0
	ldr	s0, [x19, #552]
	ldr	s1, [x19, #556]
	ldr	s2, [x19, #512]
	ldr	s3, [x19, #564]
	ldr	s4, [x19, #568]
	ldr	s5, [x19, #560]
LBB0_407:
	ldr	s6, [x14, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x14, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x14, x11]
	ldr	s16, [x15, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x15, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x15, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_407
	mov	x8, #0
	add	x9, x19, #572
	ldr	x10, [sp, #384]
LBB0_409:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_409
	mov	x8, #0
	ldr	x14, [sp, #1528]
	add	x9, x19, #836
	add	x10, sp, #1, lsl #12
	add	x10, x10, #2448
LBB0_411:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_411
	mov	x8, #0
	ldr	s0, [x19, #816]
	ldr	s1, [x19, #820]
	ldr	s2, [x19, #776]
	ldr	s3, [x19, #828]
	ldr	s4, [x19, #832]
	ldr	s5, [x19, #824]
LBB0_413:
	ldr	s6, [x16, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x16, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x16, x11]
	ldr	s16, [x14, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x14, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x14, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_413
	mov	x8, #0
	add	x9, x19, #836
	ldr	x10, [sp, #376]
LBB0_415:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_415
	mov	x8, #0
	ldr	x16, [sp, #1472]
	add	x9, x19, #1100
	add	x10, sp, #1, lsl #12
	add	x10, x10, #3584
LBB0_417:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_417
	mov	x8, #0
	ldr	s0, [x19, #1080]
	ldr	s1, [x19, #1084]
	ldr	s2, [x19, #1040]
	ldr	s3, [x19, #1092]
	ldr	s4, [x19, #1096]
	ldr	s5, [x19, #1088]
LBB0_419:
	ldr	s6, [x17, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x17, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x17, x11]
	ldr	s16, [x16, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x16, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x16, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_419
	mov	x8, #0
	add	x9, x19, #1100
	ldr	x10, [sp, #368]
LBB0_421:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_421
	mov	x8, #0
	ldr	x17, [sp, #1416]
	add	x9, x19, #1364
	add	x10, sp, #2, lsl #12
	add	x10, x10, #624
LBB0_423:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_423
	mov	x8, #0
	ldr	s0, [x19, #1344]
	ldr	s1, [x19, #1348]
	ldr	s2, [x19, #1304]
	ldr	s3, [x19, #1356]
	ldr	s4, [x19, #1360]
	ldr	s5, [x19, #1352]
LBB0_425:
	ldr	s6, [x0, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x0, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x0, x11]
	ldr	s16, [x17, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x17, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x17, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_425
	mov	x8, #0
	add	x9, x19, #1364
	ldr	x10, [sp, #360]
LBB0_427:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_427
	mov	x8, #0
	ldr	x0, [sp, #1360]
	add	x9, x19, #1628
	add	x10, sp, #2, lsl #12
	add	x10, x10, #1760
LBB0_429:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_429
	mov	x8, #0
	ldr	s0, [x19, #1608]
	ldr	s1, [x19, #1612]
	ldr	s2, [x19, #1568]
	ldr	s3, [x19, #1620]
	ldr	s4, [x19, #1624]
	ldr	s5, [x19, #1616]
LBB0_431:
	ldr	s6, [x1, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x1, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x1, x11]
	ldr	s16, [x0, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x0, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x0, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_431
	mov	x8, #0
	add	x9, x19, #1628
	ldr	x10, [sp, #352]
LBB0_433:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_433
	mov	x8, #0
	ldr	x1, [sp, #1304]
	add	x9, x19, #1892
	add	x10, sp, #2, lsl #12
	add	x10, x10, #2896
LBB0_435:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_435
	mov	x8, #0
	ldr	s0, [x19, #1872]
	ldr	s1, [x19, #1876]
	ldr	s2, [x19, #1832]
	ldr	s3, [x19, #1884]
	ldr	s4, [x19, #1888]
	ldr	s5, [x19, #1880]
LBB0_437:
	ldr	s6, [x2, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x2, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x2, x11]
	ldr	s16, [x1, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x1, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x1, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_437
	mov	x8, #0
	add	x9, x19, #1892
	ldr	x10, [sp, #344]
LBB0_439:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_439
	mov	x8, #0
	ldr	x2, [sp, #1248]
	add	x9, x19, #2156
	add	x10, sp, #2, lsl #12
	add	x10, x10, #4032
LBB0_441:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_441
	mov	x8, #0
	ldr	s0, [x19, #2136]
	ldr	s1, [x19, #2140]
	ldr	s2, [x19, #2096]
	ldr	s3, [x19, #2148]
	ldr	s4, [x19, #2152]
	ldr	s5, [x19, #2144]
LBB0_443:
	ldr	s6, [x3, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x3, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x3, x11]
	ldr	s16, [x2, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x2, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x2, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_443
	mov	x8, #0
	add	x9, x19, #2156
	ldr	x10, [sp, #336]
LBB0_445:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_445
	mov	x8, #0
	ldr	x3, [sp, #1192]
	add	x9, x19, #2420
	add	x10, sp, #3, lsl #12
	add	x10, x10, #1072
LBB0_447:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_447
	mov	x8, #0
	ldr	s0, [x19, #2400]
	ldr	s1, [x19, #2404]
	ldr	s2, [x19, #2360]
	ldr	s3, [x19, #2412]
	ldr	s4, [x19, #2416]
	ldr	s5, [x19, #2408]
LBB0_449:
	ldr	s6, [x4, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x4, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x4, x11]
	ldr	s16, [x3, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x3, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x3, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_449
	mov	x8, #0
	add	x9, x19, #2420
	ldr	x10, [sp, #328]
LBB0_451:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_451
	mov	x8, #0
	ldr	x4, [sp, #1136]
	add	x9, x19, #2684
	add	x10, sp, #3, lsl #12
	add	x10, x10, #2208
LBB0_453:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_453
	mov	x8, #0
	ldr	s0, [x19, #2664]
	ldr	s1, [x19, #2668]
	ldr	s2, [x19, #2624]
	ldr	s3, [x19, #2676]
	ldr	s4, [x19, #2680]
	ldr	s5, [x19, #2672]
LBB0_455:
	ldr	s6, [x5, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x5, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x5, x11]
	ldr	s16, [x4, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x4, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x4, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_455
	mov	x8, #0
	add	x9, x19, #2684
	ldr	x10, [sp, #320]
LBB0_457:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_457
	mov	x8, #0
	ldr	x5, [sp, #1080]
	add	x9, x19, #2948
	add	x10, sp, #3, lsl #12
	add	x10, x10, #3344
LBB0_459:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_459
	mov	x8, #0
	ldr	s0, [x19, #2928]
	ldr	s1, [x19, #2932]
	ldr	s2, [x19, #2888]
	ldr	s3, [x19, #2940]
	ldr	s4, [x19, #2944]
	ldr	s5, [x19, #2936]
LBB0_461:
	ldr	s6, [x6, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x6, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x6, x11]
	ldr	s16, [x5, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x5, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x5, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_461
	mov	x8, #0
	add	x9, x19, #2948
	ldr	x10, [sp, #312]
LBB0_463:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_463
	mov	x8, #0
	ldr	x6, [sp, #1024]
	add	x9, x19, #3212
	add	x10, sp, #4, lsl #12
	add	x10, x10, #384
LBB0_465:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_465
	mov	x8, #0
	ldr	s0, [x19, #3192]
	ldr	s1, [x19, #3196]
	ldr	s2, [x19, #3152]
	ldr	s3, [x19, #3204]
	ldr	s4, [x19, #3208]
	ldr	s5, [x19, #3200]
LBB0_467:
	ldr	s6, [x7, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x7, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x7, x11]
	ldr	s16, [x6, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x6, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x6, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_467
	mov	x8, #0
	add	x9, x19, #3212
	ldr	x10, [sp, #304]
LBB0_469:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_469
	mov	x8, #0
	ldr	x7, [sp, #976]
	add	x9, x19, #3476
	add	x10, sp, #4, lsl #12
	add	x10, x10, #1520
LBB0_471:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_471
	mov	x8, #0
	ldr	s0, [x19, #3456]
	ldr	s1, [x19, #3460]
	ldr	s2, [x19, #3416]
	ldr	s3, [x19, #3468]
	ldr	s4, [x19, #3472]
	ldr	s5, [x19, #3464]
LBB0_473:
	ldr	s6, [x30, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x30, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x30, x11]
	ldr	s16, [x7, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x7, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x7, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_473
	mov	x8, #0
	add	x9, x19, #3476
	ldr	x10, [sp, #296]
LBB0_475:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_475
	mov	x8, #0
	ldr	x30, [sp, #2000]
	add	x9, x19, #3740
	add	x10, sp, #4, lsl #12
	add	x10, x10, #2656
LBB0_477:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_477
	mov	x8, #0
	ldr	s0, [x19, #3720]
	ldr	s1, [x19, #3724]
	ldr	s2, [x19, #3680]
	ldr	s3, [x19, #3732]
	ldr	s4, [x19, #3736]
	ldr	s5, [x19, #3728]
LBB0_479:
	ldr	s6, [x30, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x30, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x30, x11]
	ldr	s16, [x27, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x27, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x27, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_479
	mov	x8, #0
	add	x9, x19, #3740
	ldr	x10, [sp, #288]
LBB0_481:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_481
	mov	x8, #0
	ldr	x30, [sp, #1992]
	add	x9, x19, #3876
	add	x10, sp, #4, lsl #12
	add	x10, x10, #3232
LBB0_483:
	ldr	s0, [x9, x8]
	str	s0, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_483
	mov	x8, #0
	ldr	s0, [x19, #3856]
	ldr	s1, [x19, #3860]
	ldr	s2, [x19, #3824]
	ldr	s3, [x19, #3868]
	ldr	s4, [x19, #3872]
	ldr	s5, [x19, #3864]
LBB0_485:
	ldr	s6, [x30, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x30, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x30, x11]
	ldr	s16, [x21, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x21, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x21, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_485
	mov	x8, #0
	add	x9, x19, #3876
	ldr	x10, [sp, #280]
LBB0_487:
	ldr	s0, [x10, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_487
	mov	x8, #0
	add	x30, x19, #332
	add	x9, sp, #1, lsl #12
	add	x9, x9, #320
LBB0_489:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_489
	mov	x8, #0
	ldr	s0, [x19, #312]
	ldr	s1, [x19, #316]
	ldr	s2, [x19, #280]
	ldr	s3, [x19, #324]
	ldr	s4, [x19, #328]
	ldr	s5, [x19, #320]
LBB0_491:
	ldr	s6, [x12, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x12, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x12, x11]
	ldr	s16, [x13, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x13, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x13, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_491
	mov	x8, #0
	ldr	x9, [sp, #272]
LBB0_493:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_493
	mov	x8, #0
	ldr	x12, [sp, #1576]
	add	x30, x19, #612
	add	x9, sp, #1, lsl #12
	add	x9, x9, #1456
LBB0_495:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_495
	mov	x8, #0
	ldr	s0, [x19, #592]
	ldr	s1, [x19, #596]
	ldr	s2, [x19, #560]
	ldr	s3, [x19, #604]
	ldr	s4, [x19, #608]
	ldr	s5, [x19, #600]
LBB0_497:
	ldr	s6, [x15, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x15, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x15, x11]
	ldr	s16, [x12, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x12, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x12, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_497
	mov	x8, #0
	ldr	x9, [sp, #264]
LBB0_499:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_499
	mov	x8, #0
	ldr	x15, [sp, #1520]
	add	x30, x19, #876
	add	x9, sp, #1, lsl #12
	add	x9, x9, #2592
LBB0_501:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_501
	mov	x8, #0
	ldr	s0, [x19, #856]
	ldr	s1, [x19, #860]
	ldr	s2, [x19, #824]
	ldr	s3, [x19, #868]
	ldr	s4, [x19, #872]
	ldr	s5, [x19, #864]
LBB0_503:
	ldr	s6, [x14, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x14, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x14, x11]
	ldr	s16, [x15, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x15, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x15, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_503
	mov	x8, #0
	ldr	x9, [sp, #256]
LBB0_505:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_505
	mov	x8, #0
	ldr	x14, [sp, #1464]
	add	x30, x19, #1140
	add	x9, sp, #1, lsl #12
	add	x9, x9, #3728
LBB0_507:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_507
	mov	x8, #0
	ldr	s0, [x19, #1120]
	ldr	s1, [x19, #1124]
	ldr	s2, [x19, #1088]
	ldr	s3, [x19, #1132]
	ldr	s4, [x19, #1136]
	ldr	s5, [x19, #1128]
LBB0_509:
	ldr	s6, [x16, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x16, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x16, x11]
	ldr	s16, [x14, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x14, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x14, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_509
	mov	x8, #0
	ldr	x9, [sp, #248]
LBB0_511:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_511
	mov	x8, #0
	ldr	x16, [sp, #1408]
	add	x30, x19, #1404
	add	x9, sp, #2, lsl #12
	add	x9, x9, #768
LBB0_513:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_513
	mov	x8, #0
	ldr	s0, [x19, #1384]
	ldr	s1, [x19, #1388]
	ldr	s2, [x19, #1352]
	ldr	s3, [x19, #1396]
	ldr	s4, [x19, #1400]
	ldr	s5, [x19, #1392]
LBB0_515:
	ldr	s6, [x17, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x17, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x17, x11]
	ldr	s16, [x16, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x16, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x16, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_515
	mov	x8, #0
	ldr	x9, [sp, #240]
LBB0_517:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_517
	mov	x8, #0
	ldr	x17, [sp, #1352]
	add	x30, x19, #1668
	add	x9, sp, #2, lsl #12
	add	x9, x9, #1904
LBB0_519:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_519
	mov	x8, #0
	ldr	s0, [x19, #1648]
	ldr	s1, [x19, #1652]
	ldr	s2, [x19, #1616]
	ldr	s3, [x19, #1660]
	ldr	s4, [x19, #1664]
	ldr	s5, [x19, #1656]
LBB0_521:
	ldr	s6, [x0, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x0, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x0, x11]
	ldr	s16, [x17, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x17, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x17, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_521
	mov	x8, #0
	ldr	x9, [sp, #232]
LBB0_523:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_523
	mov	x8, #0
	ldr	x0, [sp, #1296]
	add	x30, x19, #1932
	add	x9, sp, #2, lsl #12
	add	x9, x9, #3040
LBB0_525:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_525
	mov	x8, #0
	ldr	s0, [x19, #1912]
	ldr	s1, [x19, #1916]
	ldr	s2, [x19, #1880]
	ldr	s3, [x19, #1924]
	ldr	s4, [x19, #1928]
	ldr	s5, [x19, #1920]
LBB0_527:
	ldr	s6, [x1, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x1, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x1, x11]
	ldr	s16, [x0, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x0, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x0, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_527
	mov	x8, #0
	ldr	x9, [sp, #224]
LBB0_529:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_529
	mov	x8, #0
	ldr	x1, [sp, #1240]
	add	x30, x19, #2196
	add	x9, sp, #3, lsl #12
	add	x9, x9, #80
LBB0_531:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_531
	mov	x8, #0
	ldr	s0, [x19, #2176]
	ldr	s1, [x19, #2180]
	ldr	s2, [x19, #2144]
	ldr	s3, [x19, #2188]
	ldr	s4, [x19, #2192]
	ldr	s5, [x19, #2184]
LBB0_533:
	ldr	s6, [x2, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x2, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x2, x11]
	ldr	s16, [x1, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x1, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x1, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_533
	mov	x8, #0
	ldr	x9, [sp, #216]
LBB0_535:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_535
	mov	x8, #0
	ldr	x2, [sp, #1184]
	add	x30, x19, #2460
	add	x9, sp, #3, lsl #12
	add	x9, x9, #1216
LBB0_537:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_537
	mov	x8, #0
	ldr	s0, [x19, #2440]
	ldr	s1, [x19, #2444]
	ldr	s2, [x19, #2408]
	ldr	s3, [x19, #2452]
	ldr	s4, [x19, #2456]
	ldr	s5, [x19, #2448]
LBB0_539:
	ldr	s6, [x3, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x3, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x3, x11]
	ldr	s16, [x2, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x2, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x2, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_539
	mov	x8, #0
	ldr	x9, [sp, #208]
LBB0_541:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_541
	mov	x8, #0
	ldr	x3, [sp, #1128]
	add	x30, x19, #2724
	add	x9, sp, #3, lsl #12
	add	x9, x9, #2352
LBB0_543:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_543
	mov	x8, #0
	ldr	s0, [x19, #2704]
	ldr	s1, [x19, #2708]
	ldr	s2, [x19, #2672]
	ldr	s3, [x19, #2716]
	ldr	s4, [x19, #2720]
	ldr	s5, [x19, #2712]
LBB0_545:
	ldr	s6, [x4, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x4, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x4, x11]
	ldr	s16, [x3, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x3, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x3, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_545
	mov	x8, #0
	ldr	x9, [sp, #200]
LBB0_547:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_547
	mov	x8, #0
	ldr	x4, [sp, #1072]
	add	x30, x19, #2988
	add	x9, sp, #3, lsl #12
	add	x9, x9, #3488
LBB0_549:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_549
	mov	x8, #0
	ldr	s0, [x19, #2968]
	ldr	s1, [x19, #2972]
	ldr	s2, [x19, #2936]
	ldr	s3, [x19, #2980]
	ldr	s4, [x19, #2984]
	ldr	s5, [x19, #2976]
LBB0_551:
	ldr	s6, [x5, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x5, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x5, x11]
	ldr	s16, [x4, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x4, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x4, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_551
	mov	x8, #0
	ldr	x9, [sp, #192]
LBB0_553:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_553
	mov	x8, #0
	ldr	x5, [sp, #1016]
	add	x30, x19, #3252
	add	x9, sp, #4, lsl #12
	add	x9, x9, #528
LBB0_555:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_555
	mov	x8, #0
	ldr	s0, [x19, #3232]
	ldr	s1, [x19, #3236]
	ldr	s2, [x19, #3200]
	ldr	s3, [x19, #3244]
	ldr	s4, [x19, #3248]
	ldr	s5, [x19, #3240]
LBB0_557:
	ldr	s6, [x6, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x6, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x6, x11]
	ldr	s16, [x5, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x5, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x5, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_557
	mov	x8, #0
	ldr	x9, [sp, #184]
LBB0_559:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_559
	mov	x8, #0
	ldr	x6, [sp, #968]
	add	x30, x19, #3516
	add	x9, sp, #4, lsl #12
	add	x9, x9, #1664
LBB0_561:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_561
	mov	x8, #0
	ldr	s0, [x19, #3496]
	ldr	s1, [x19, #3500]
	ldr	s2, [x19, #3464]
	ldr	s3, [x19, #3508]
	ldr	s4, [x19, #3512]
	ldr	s5, [x19, #3504]
LBB0_563:
	ldr	s6, [x7, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x7, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x7, x11]
	ldr	s16, [x6, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x6, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x6, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_563
	mov	x8, #0
	ldr	x9, [sp, #176]
LBB0_565:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_565
	mov	x8, #0
	ldr	x7, [sp, #936]
	add	x30, x19, #3780
	add	x9, sp, #4, lsl #12
	add	x9, x9, #2800
LBB0_567:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_567
	mov	x8, #0
	ldr	s0, [x19, #3760]
	ldr	s1, [x19, #3764]
	ldr	s2, [x19, #3728]
	ldr	s3, [x19, #3772]
	ldr	s4, [x19, #3776]
	ldr	s5, [x19, #3768]
LBB0_569:
	ldr	s6, [x27, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x27, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x27, x11]
	ldr	s16, [x28, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x28, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x28, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_569
	mov	x8, #0
	ldr	x9, [sp, #168]
LBB0_571:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_571
	mov	x8, #0
	add	x30, x19, #3912
	add	x9, sp, #4, lsl #12
	add	x9, x9, #3376
LBB0_573:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_573
	mov	x8, #0
	ldr	s0, [x19, #3892]
	ldr	s1, [x19, #3896]
	ldr	s2, [x19, #3864]
	ldr	s3, [x19, #3904]
	ldr	s4, [x19, #3908]
	ldr	s5, [x19, #3900]
LBB0_575:
	ldr	s6, [x21, x8, lsl #2]
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s7, [x21, x10]
	fmul	s7, s1, s7
	fmadd	s6, s0, s6, s7
	add	x11, x9, x20
	asr	x11, x11, #30
	ldr	s7, [x21, x11]
	ldr	s16, [x25, x11]
	fmadd	s6, s0, s7, s6
	ldr	s7, [x25, x10]
	fmul	s7, s4, s7
	fmadd	s7, s3, s16, s7
	fmul	s7, s5, s7
	fnmsub	s6, s2, s6, s7
	str	s6, [x25, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_575
	mov	x8, #0
	ldr	x9, [sp, #160]
LBB0_577:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_577
	mov	x8, #0
	ldr	x11, [sp, #1624]
	ldr	s6, [sp, #892]
	add	x30, x19, #376
	add	x9, sp, #1, lsl #12
	add	x9, x9, #464
LBB0_579:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_579
	mov	x8, #0
	ldr	s0, [x19, #368]
	ldr	s1, [x19, #372]
	ldr	s2, [x19, #320]
LBB0_581:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x11, x10]
	ldr	s4, [x13, x8, lsl #2]
	ldr	s5, [x13, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x13, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x11, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_581
	mov	x8, #0
	ldr	x9, [sp, #152]
LBB0_583:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_583
	mov	x8, #0
	ldr	x13, [sp, #1568]
	add	x30, x19, #640
	add	x9, sp, #1, lsl #12
	add	x9, x9, #1600
LBB0_585:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_585
	mov	x8, #0
	ldr	s0, [x19, #632]
	ldr	s1, [x19, #636]
	ldr	s2, [x19, #600]
LBB0_587:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x13, x10]
	ldr	s4, [x12, x8, lsl #2]
	ldr	s5, [x12, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x12, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x13, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_587
	mov	x8, #0
	ldr	x9, [sp, #144]
LBB0_589:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_589
	mov	x8, #0
	ldr	x12, [sp, #1512]
	add	x30, x19, #904
	add	x9, sp, #1, lsl #12
	add	x9, x9, #2736
LBB0_591:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_591
	mov	x8, #0
	ldr	s0, [x19, #896]
	ldr	s1, [x19, #900]
	ldr	s2, [x19, #864]
LBB0_593:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x12, x10]
	ldr	s4, [x15, x8, lsl #2]
	ldr	s5, [x15, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x15, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x12, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_593
	mov	x8, #0
	ldr	x9, [sp, #136]
LBB0_595:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_595
	mov	x8, #0
	ldr	x15, [sp, #1456]
	add	x30, x19, #1168
	add	x9, sp, #1, lsl #12
	add	x9, x9, #3872
LBB0_597:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_597
	mov	x8, #0
	ldr	s0, [x19, #1160]
	ldr	s1, [x19, #1164]
	ldr	s2, [x19, #1128]
LBB0_599:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x15, x10]
	ldr	s4, [x14, x8, lsl #2]
	ldr	s5, [x14, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x14, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x15, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_599
	mov	x8, #0
	ldr	x9, [sp, #128]
LBB0_601:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_601
	mov	x8, #0
	ldr	x14, [sp, #1400]
	add	x30, x19, #1432
	add	x9, sp, #2, lsl #12
	add	x9, x9, #912
LBB0_603:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_603
	mov	x8, #0
	ldr	s0, [x19, #1424]
	ldr	s1, [x19, #1428]
	ldr	s2, [x19, #1392]
LBB0_605:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x14, x10]
	ldr	s4, [x16, x8, lsl #2]
	ldr	s5, [x16, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x16, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x14, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_605
	mov	x8, #0
	ldr	x9, [sp, #120]
LBB0_607:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_607
	mov	x8, #0
	ldr	x16, [sp, #1344]
	add	x30, x19, #1696
	add	x9, sp, #2, lsl #12
	add	x9, x9, #2048
LBB0_609:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_609
	mov	x8, #0
	ldr	s0, [x19, #1688]
	ldr	s1, [x19, #1692]
	ldr	s2, [x19, #1656]
LBB0_611:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x16, x10]
	ldr	s4, [x17, x8, lsl #2]
	ldr	s5, [x17, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x17, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x16, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_611
	mov	x8, #0
	ldr	x9, [sp, #112]
LBB0_613:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_613
	mov	x8, #0
	ldr	x17, [sp, #1288]
	add	x30, x19, #1960
	add	x9, sp, #2, lsl #12
	add	x9, x9, #3184
LBB0_615:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_615
	mov	x8, #0
	ldr	s0, [x19, #1952]
	ldr	s1, [x19, #1956]
	ldr	s2, [x19, #1920]
LBB0_617:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x17, x10]
	ldr	s4, [x0, x8, lsl #2]
	ldr	s5, [x0, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x0, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x17, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_617
	mov	x8, #0
	ldr	x9, [sp, #104]
LBB0_619:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_619
	mov	x8, #0
	ldr	x0, [sp, #1232]
	add	x30, x19, #2224
	add	x9, sp, #3, lsl #12
	add	x9, x9, #224
LBB0_621:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_621
	mov	x8, #0
	ldr	s0, [x19, #2216]
	ldr	s1, [x19, #2220]
	ldr	s2, [x19, #2184]
LBB0_623:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x0, x10]
	ldr	s4, [x1, x8, lsl #2]
	ldr	s5, [x1, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x1, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x0, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_623
	mov	x8, #0
	ldr	x9, [sp, #96]
LBB0_625:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_625
	mov	x8, #0
	ldr	x1, [sp, #1176]
	add	x30, x19, #2488
	add	x9, sp, #3, lsl #12
	add	x9, x9, #1360
LBB0_627:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_627
	mov	x8, #0
	ldr	s0, [x19, #2480]
	ldr	s1, [x19, #2484]
	ldr	s2, [x19, #2448]
LBB0_629:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x1, x10]
	ldr	s4, [x2, x8, lsl #2]
	ldr	s5, [x2, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x2, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x1, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_629
	mov	x8, #0
	ldr	x9, [sp, #88]
LBB0_631:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_631
	mov	x8, #0
	ldr	x2, [sp, #1120]
	add	x30, x19, #2752
	add	x9, sp, #3, lsl #12
	add	x9, x9, #2496
LBB0_633:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_633
	mov	x8, #0
	ldr	s0, [x19, #2744]
	ldr	s1, [x19, #2748]
	ldr	s2, [x19, #2712]
LBB0_635:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x2, x10]
	ldr	s4, [x3, x8, lsl #2]
	ldr	s5, [x3, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x3, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x2, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_635
	mov	x8, #0
	ldr	x9, [sp, #80]
LBB0_637:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_637
	mov	x8, #0
	ldr	x3, [sp, #1064]
	add	x30, x19, #3016
	add	x9, sp, #3, lsl #12
	add	x9, x9, #3632
LBB0_639:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_639
	mov	x8, #0
	ldr	s0, [x19, #3008]
	ldr	s1, [x19, #3012]
	ldr	s2, [x19, #2976]
LBB0_641:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x3, x10]
	ldr	s4, [x4, x8, lsl #2]
	ldr	s5, [x4, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x4, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x3, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_641
	mov	x8, #0
	ldr	x9, [sp, #72]
LBB0_643:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_643
	mov	x8, #0
	ldr	x4, [sp, #1008]
	add	x30, x19, #3280
	add	x9, sp, #4, lsl #12
	add	x9, x9, #672
LBB0_645:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_645
	mov	x8, #0
	ldr	s0, [x19, #3272]
	ldr	s1, [x19, #3276]
	ldr	s2, [x19, #3240]
LBB0_647:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x4, x10]
	ldr	s4, [x5, x8, lsl #2]
	ldr	s5, [x5, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x5, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x4, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_647
	mov	x8, #0
	ldr	x9, [sp, #64]
LBB0_649:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_649
	mov	x8, #0
	ldr	x5, [sp, #960]
	add	x30, x19, #3544
	add	x9, sp, #4, lsl #12
	add	x9, x9, #1808
LBB0_651:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_651
	mov	x8, #0
	ldr	s0, [x19, #3536]
	ldr	s1, [x19, #3540]
	ldr	s2, [x19, #3504]
LBB0_653:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x5, x10]
	ldr	s4, [x6, x8, lsl #2]
	ldr	s5, [x6, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x6, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x5, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_653
	mov	x8, #0
	ldr	x9, [sp, #56]
LBB0_655:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_655
	mov	x8, #0
	ldr	x6, [sp, #944]
	add	x30, x19, #3808
	add	x9, sp, #4, lsl #12
	add	x9, x9, #2944
LBB0_657:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_657
	mov	x8, #0
	ldr	s0, [x19, #3800]
	ldr	s1, [x19, #3804]
	ldr	s2, [x19, #3768]
LBB0_659:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x6, x10]
	ldr	s4, [x28, x8, lsl #2]
	ldr	s5, [x28, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x28, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x6, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_659
	mov	x8, #0
	ldr	x9, [sp, #48]
LBB0_661:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_661
	mov	x8, #0
	add	x30, x19, #3936
	add	x9, sp, #4, lsl #12
	add	x9, x9, #3520
LBB0_663:
	ldr	s0, [x30, x8]
	str	s0, [x9, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_663
	mov	x8, #0
	ldr	s0, [x19, #3928]
	ldr	s1, [x19, #3932]
	ldr	s2, [x19, #3900]
LBB0_665:
	lsl	x9, x8, #32
	add	x10, x9, x23
	asr	x10, x10, #30
	ldr	s3, [x7, x10]
	ldr	s4, [x25, x8, lsl #2]
	ldr	s5, [x25, x10]
	fmul	s5, s1, s5
	fmadd	s4, s0, s4, s5
	add	x10, x9, x20
	asr	x10, x10, #30
	ldr	s5, [x25, x10]
	fmadd	s4, s0, s5, s4
	fmul	s4, s2, s4
	fabs	s4, s4
	fmul	s4, s6, s4
	fmadd	s3, s11, s3, s4
	str	s3, [x7, x8, lsl #2]
	add	x8, x9, x26
	asr	x8, x8, #32
	cmp	x8, #32
	b.lt	LBB0_665
	mov	x8, #0
	ldr	x9, [sp, #40]
LBB0_667:
	ldr	s0, [x9, x8]
	str	s0, [x30, x8]
	add	x8, x8, #4
	cmp	x8, #16
	b.ne	LBB0_667
	mov	x8, #0
	add	x9, sp, #4000
	add	x10, sp, #4, lsl #12
	add	x10, x10, #3664
LBB0_669:
	ldr	s0, [x11, x8]
	ldr	s13, [x13, x8]
	ldr	s12, [x12, x8]
	ldr	s11, [x15, x8]
	ldr	s10, [x14, x8]
	ldr	s9, [x16, x8]
	ldr	s8, [x17, x8]
	ldr	s15, [x0, x8]
	ldr	s14, [x1, x8]
	ldr	s7, [x2, x8]
	ldr	s6, [x3, x8]
	ldr	s5, [x4, x8]
	ldr	s4, [x5, x8]
	ldr	s3, [x6, x8]
	ldr	s2, [x7, x8]
	ldr	s1, [x9, x8]
	str	s1, [x10, x8]
	add	x8, x8, #4
	cmp	x8, #128
	b.ne	LBB0_669
	str	s2, [sp, #1756]
	str	s3, [sp, #1752]
	str	s4, [sp, #1748]
	str	s5, [sp, #1808]
	str	s6, [sp, #1824]
	str	s7, [sp, #1872]
	bl	_log10f
	str	q0, [sp, #1776]
	mov.16b	v0, v13
	bl	_log10f
	str	q0, [sp, #1936]
	mov.16b	v0, v12
	bl	_log10f
	str	q0, [sp, #1920]
	mov.16b	v0, v11
	bl	_log10f
	str	q0, [sp, #1888]
	mov.16b	v0, v10
	bl	_log10f
	str	q0, [sp, #1760]
	mov.16b	v0, v9
	bl	_log10f
	str	q0, [sp, #1904]
	mov.16b	v0, v8
	bl	_log10f
	str	q0, [sp, #1856]
	mov.16b	v0, v15
	bl	_log10f
	str	q0, [sp, #1840]
	mov.16b	v0, v14
	bl	_log10f
	str	q0, [sp, #1792]
	ldr	s0, [sp, #1872]
	bl	_log10f
	str	q0, [sp, #1872]
	ldr	s0, [sp, #1824]
	bl	_log10f
	str	q0, [sp, #1824]
	ldr	s0, [sp, #1808]
	bl	_log10f
	str	q0, [sp, #1808]
	ldr	s0, [sp, #1748]
	bl	_log10f
	fmov	s10, #20.00000000
	ldr	q1, [sp, #2016]
	fmadd	s0, s0, s10, s1
	fcvt	d8, s0
	ldr	s0, [sp, #1752]
	bl	_log10f
	ldr	q1, [sp, #2016]
	fmadd	s0, s0, s10, s1
	fcvt	d9, s0
	ldr	s0, [sp, #1756]
	bl	_log10f
	mov	x8, #0
	ldr	q1, [sp, #2016]
	fmadd	s0, s0, s10, s1
	ldr	q1, [sp, #1776]
	ldr	q2, [sp, #1936]
	mov.s	v1[1], v2[0]
	ldr	q2, [sp, #1920]
	mov.s	v1[2], v2[0]
	fcvt	d0, s0
	ldr	q2, [sp, #1888]
	mov.s	v1[3], v2[0]
	mov.16b	v2, v1
	ldr	q3, [sp, #896]
	mov.16b	v1, v3
	fmov.4s	v4, #20.00000000
	fmla.4s	v1, v2, v4
	fcvtl	v2.2d, v1.2s
	fcvtl2	v1.2d, v1.4s
	ldr	q5, [sp, #1760]
	ldr	q6, [sp, #1904]
	mov.s	v5[1], v6[0]
	ldr	q6, [sp, #1856]
	mov.s	v5[2], v6[0]
	add	x9, x19, #3960
	stp	q2, q1, [x9]
	ldr	q1, [sp, #1840]
	mov.s	v5[3], v1[0]
	mov.16b	v1, v3
	fmla.4s	v1, v5, v4
	fcvtl	v2.2d, v1.2s
	fcvtl2	v1.2d, v1.4s
	ldr	q5, [sp, #1792]
	ldr	q6, [sp, #1872]
	mov.s	v5[1], v6[0]
	ldr	q6, [sp, #1824]
	mov.s	v5[2], v6[0]
	stp	q2, q1, [x9, #32]
	ldr	q1, [sp, #1808]
	mov.s	v5[3], v1[0]
	mov.16b	v1, v3
	fmla.4s	v1, v5, v4
	fcvtl	v2.2d, v1.2s
	fcvtl2	v1.2d, v1.4s
	stp	q2, q1, [x9, #64]
	str	d8, [x19, #4056]
	str	d9, [x19, #4064]
	str	d0, [x19, #4072]
	add	x9, sp, #4, lsl #12
	add	x9, x9, #3664
	ldr	x10, [sp, #1952]
LBB0_671:
	ldr	s0, [x9, x8, lsl #2]
	fcvt	d0, s0
	str	d0, [x10, x8, lsl #3]
	add	x8, x8, #1
	cmp	x8, #32
	b.ne	LBB0_671
	mov	x8, #0
	ldr	s11, [sp, #1708]
	ldr	s12, [sp, #1704]
	fmov	s13, #1.00000000
	ldr	s14, [sp, #1692]
	ldr	s15, [sp, #1688]
	ldr	s1, [sp, #924]
	ldr	x12, [sp, #1960]
LBB0_673:
	ldr	s0, [x9, x8, lsl #2]
	fcvt	d0, s0
	str	d0, [x12, x8, lsl #3]
	add	x8, x8, #1
	cmp	x8, #32
	b.ne	LBB0_673
	mov	w9, #0
	mov	w12, #32
	ldr	w8, [sp, #1972]
	tbnz	w8, #0, LBB0_5
	;MEMBARRIER
	add	sp, sp, #4, lsl #12
	add	sp, sp, #3792
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
	.cfi_endproc
