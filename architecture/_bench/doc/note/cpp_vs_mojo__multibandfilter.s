;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; C++ 32bit
	sub	sp, sp, #400
	stp	d15, d14, [sp, #272]            ; 16-byte Folded Spill
	stp	d13, d12, [sp, #288]            ; 16-byte Folded Spill
	stp	d11, d10, [sp, #304]            ; 16-byte Folded Spill
	stp	d9, d8, [sp, #320]              ; 16-byte Folded Spill
	stp	x28, x27, [sp, #336]            ; 16-byte Folded Spill
	stp	x22, x21, [sp, #352]            ; 16-byte Folded Spill
	stp	x20, x19, [sp, #368]            ; 16-byte Folded Spill
	stp	x29, x30, [sp, #384]            ; 16-byte Folded Spill
	add	x29, sp, #384
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w27, -56
	.cfi_offset w28, -64
	.cfi_offset b8, -72
	.cfi_offset b9, -80
	.cfi_offset b10, -88
	.cfi_offset b11, -96
	.cfi_offset b12, -104
	.cfi_offset b13, -112
	.cfi_offset b14, -120
	.cfi_offset b15, -128
	mov	x20, x1
	mov	x19, x0
	ldr	x21, [x2]
	ldr	x22, [x3]
	ldr	s10, [x0, #12]
	ldr	d0, [x0, #16]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	str	s0, [sp, #112]                  ; 4-byte Folded Spill
	ldp	d0, d1, [x19, #24]
	str	d1, [sp, #120]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	mov	w8, #52429                      ; =0xcccd
	movk	w8, #48460, lsl #16
	fmov	s12, w8
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #116]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #40]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	str	s0, [sp, #128]                  ; 4-byte Folded Spill
	ldp	d0, d1, [x19, #48]
	str	d1, [sp, #136]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #132]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #64]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	str	s0, [sp, #144]                  ; 4-byte Folded Spill
	ldp	d0, d1, [x19, #72]
	str	d1, [sp, #152]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #148]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #88]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s14, s0
	ldp	d0, d1, [x19, #96]
	str	d1, [sp, #168]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #164]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #112]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s9, s0
	ldp	d0, d1, [x19, #120]
	str	d1, [sp, #184]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #180]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #136]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s13, s0
	ldp	d0, d1, [x19, #144]
	stur	d1, [x29, #-184]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	stur	s0, [x29, #-188]                ; 4-byte Folded Spill
	ldr	d0, [x19, #160]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s11, s0
	ldp	d0, d1, [x19, #168]
	stur	d1, [x29, #-168]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	stur	s0, [x29, #-172]                ; 4-byte Folded Spill
	ldr	d0, [x19, #184]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s15, s0
	ldp	d0, d1, [x19, #192]
	stur	d1, [x29, #-152]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	stur	s0, [x29, #-156]                ; 4-byte Folded Spill
	ldr	d0, [x19, #208]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s8, s0
	ldp	d0, d1, [x19, #216]
	stur	d1, [x29, #-136]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	stur	s0, [x29, #-140]                ; 4-byte Folded Spill
	ldr	d0, [x19, #232]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s10, s0
	ldp	d0, d1, [x19, #240]
	stur	d1, [x29, #-120]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	cmp	w20, #1
	b.lt	LBB17_4
; %bb.1:
	ldr	s31, [sp, #112]                 ; 4-byte Folded Reload
	fmul	s2, s31, s31
	fmov	s1, #-1.00000000
	fadd	s16, s2, s1
	ldr	s30, [sp, #128]                 ; 4-byte Folded Reload
	fmul	s2, s30, s30
	fadd	s17, s2, s1
	ldr	s29, [sp, #144]                 ; 4-byte Folded Reload
	fmul	s2, s29, s29
	fadd	s18, s2, s1
	fmul	s2, s14, s14
	fadd	s19, s2, s1
	fmul	s2, s9, s9
	fadd	s20, s2, s1
	fmul	s2, s13, s13
	fadd	s21, s2, s1
	fmul	s2, s11, s11
	fadd	s22, s2, s1
	fmul	s2, s15, s15
	fadd	s23, s2, s1
	fmul	s2, s8, s8
	fadd	s24, s2, s1
	fmul	s2, s10, s10
	fadd	s1, s2, s1
	ldur	d2, [x29, #-120]                ; 8-byte Folded Reload
	fcvt	s3, d2
	fdiv	s4, s0, s3
	fmov	s0, #1.00000000
	fadd	s2, s10, s4
	fmadd	s2, s10, s2, s0
	fsub	s4, s10, s4
	fmadd	s5, s10, s4, s0
	fdiv	s3, s0, s3
	fadd	s4, s10, s3
	fmadd	s4, s10, s4, s0
	stp	s4, s5, [x29, #-124]            ; 8-byte Folded Spill
	fsub	s3, s3, s10
	fmsub	s3, s10, s3, s0
	stur	s3, [x29, #-128]                ; 4-byte Folded Spill
	ldur	d3, [x29, #-136]                ; 8-byte Folded Reload
	fcvt	s4, d3
	ldur	s3, [x29, #-140]                ; 4-byte Folded Reload
	fdiv	s5, s3, s4
	fadd	s3, s8, s5
	fmadd	s3, s8, s3, s0
	fsub	s5, s8, s5
	fmadd	s6, s8, s5, s0
	fdiv	s4, s0, s4
	fadd	s5, s8, s4
	fmadd	s5, s8, s5, s0
	stp	s5, s6, [x29, #-140]            ; 8-byte Folded Spill
	fsub	s4, s4, s8
	fmsub	s4, s8, s4, s0
	stur	s4, [x29, #-144]                ; 4-byte Folded Spill
	ldur	d4, [x29, #-152]                ; 8-byte Folded Reload
	fcvt	s5, d4
	ldur	s4, [x29, #-156]                ; 4-byte Folded Reload
	fdiv	s6, s4, s5
	fadd	s4, s15, s6
	fmadd	s4, s15, s4, s0
	fsub	s6, s15, s6
	fmadd	s7, s15, s6, s0
	fdiv	s5, s0, s5
	fadd	s6, s15, s5
	fmadd	s6, s15, s6, s0
	stp	s6, s7, [x29, #-156]            ; 8-byte Folded Spill
	fsub	s5, s5, s15
	fmsub	s5, s15, s5, s0
	stur	s5, [x29, #-160]                ; 4-byte Folded Spill
	ldur	d5, [x29, #-168]                ; 8-byte Folded Reload
	fcvt	s6, d5
	ldur	s5, [x29, #-172]                ; 4-byte Folded Reload
	fdiv	s7, s5, s6
	fadd	s5, s11, s7
	fmadd	s5, s11, s5, s0
	fsub	s7, s11, s7
	fmadd	s7, s11, s7, s0
	stur	s7, [x29, #-168]                ; 4-byte Folded Spill
	fdiv	s6, s0, s6
	fadd	s7, s11, s6
	fmadd	s7, s11, s7, s0
	fsub	s6, s6, s11
	fmsub	s6, s11, s6, s0
	stp	s6, s7, [x29, #-176]            ; 8-byte Folded Spill
	ldur	d6, [x29, #-184]                ; 8-byte Folded Reload
	fcvt	s7, d6
	ldur	s6, [x29, #-188]                ; 4-byte Folded Reload
	fdiv	s25, s6, s7
	fadd	s6, s13, s25
	fmadd	s6, s13, s6, s0
	fsub	s25, s13, s25
	fmadd	s26, s13, s25, s0
	fdiv	s7, s0, s7
	fadd	s25, s13, s7
	fmadd	s25, s13, s25, s0
	stp	s25, s26, [x29, #-188]          ; 8-byte Folded Spill
	fsub	s7, s7, s13
	fmsub	s7, s13, s7, s0
	str	s7, [sp, #192]                  ; 4-byte Folded Spill
	ldr	d7, [sp, #184]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #180]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s26, s9, s25
	fmadd	s26, s9, s26, s0
	fsub	s25, s9, s25
	fmadd	s27, s9, s25, s0
	fdiv	s7, s0, s7
	fadd	s25, s9, s7
	fmadd	s25, s9, s25, s0
	stp	s25, s27, [sp, #180]            ; 8-byte Folded Spill
	fsub	s7, s7, s9
	fmsub	s7, s9, s7, s0
	str	s7, [sp, #176]                  ; 4-byte Folded Spill
	ldr	d7, [sp, #168]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #164]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s27, s14, s25
	fmadd	s27, s14, s27, s0
	fsub	s25, s14, s25
	fmadd	s28, s14, s25, s0
	fdiv	s7, s0, s7
	fadd	s25, s14, s7
	fmadd	s25, s14, s25, s0
	stp	s25, s28, [sp, #164]            ; 8-byte Folded Spill
	fsub	s7, s7, s14
	fmsub	s7, s14, s7, s0
	str	s7, [sp, #160]                  ; 4-byte Folded Spill
	ldr	d7, [sp, #152]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #148]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s28, s29, s25
	fmadd	s28, s29, s28, s0
	fsub	s25, s29, s25
	fmadd	s25, s29, s25, s0
	str	s25, [sp, #152]                 ; 4-byte Folded Spill
	fdiv	s7, s0, s7
	fadd	s25, s29, s7
	fmadd	s25, s29, s25, s0
	fsub	s7, s7, s29
	fmsub	s7, s29, s7, s0
	stp	s7, s25, [sp, #144]             ; 8-byte Folded Spill
	ldr	d7, [sp, #136]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #132]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s29, s30, s25
	fmadd	s29, s30, s29, s0
	fsub	s25, s30, s25
	fmadd	s25, s30, s25, s0
	str	s25, [sp, #136]                 ; 4-byte Folded Spill
	fdiv	s7, s0, s7
	fadd	s25, s30, s7
	fmadd	s25, s30, s25, s0
	fsub	s7, s7, s30
	fmsub	s7, s30, s7, s0
	stp	s7, s25, [sp, #128]             ; 8-byte Folded Spill
	ldr	d7, [sp, #120]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #116]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s30, s31, s25
	fmadd	s30, s31, s30, s0
	fsub	s25, s31, s25
	fmadd	s25, s31, s25, s0
	str	s25, [sp, #120]                 ; 4-byte Folded Spill
	fdiv	s7, s0, s7
	fadd	s25, s31, s7
	fmadd	s25, s31, s25, s0
	fsub	s7, s7, s31
	fmsub	s7, s31, s7, s0
	stp	s7, s25, [sp, #112]             ; 8-byte Folded Spill
	fdiv	s7, s0, s30
	fdiv	s25, s0, s29
	fdiv	s29, s0, s28
	fdiv	s27, s0, s27
	fdiv	s26, s0, s26
	fdiv	s6, s0, s6
	fdiv	s5, s0, s5
	fdiv	s4, s0, s4
	fdiv	s3, s0, s3
	fdiv	s2, s0, s2
	fadd	s0, s16, s16
	str	s0, [sp, #76]                   ; 4-byte Folded Spill
	fadd	s0, s17, s17
	str	s0, [sp, #72]                   ; 4-byte Folded Spill
	fadd	s0, s18, s18
	str	s0, [sp, #68]                   ; 4-byte Folded Spill
	fadd	s0, s19, s19
	str	s0, [sp, #64]                   ; 4-byte Folded Spill
	fadd	s0, s20, s20
	str	s0, [sp, #60]                   ; 4-byte Folded Spill
	fadd	s0, s21, s21
	str	s0, [sp, #56]                   ; 4-byte Folded Spill
	fadd	s0, s22, s22
	str	s0, [sp, #52]                   ; 4-byte Folded Spill
	fadd	s0, s23, s23
	str	s0, [sp, #48]                   ; 4-byte Folded Spill
	fadd	s0, s24, s24
	str	s0, [sp, #44]                   ; 4-byte Folded Spill
	fadd	s0, s1, s1
	str	s0, [sp, #40]                   ; 4-byte Folded Spill
	mov	w8, w20
	ldr	s9, [x19, #260]
	ldr	s12, [x19, #264]
	ldr	s8, [x19, #272]
	ldr	s13, [x19, #276]
	ldr	s31, [x19, #284]
	ldr	s14, [x19, #288]
	ldr	s30, [x19, #296]
	ldr	s15, [x19, #300]
	ldr	s28, [x19, #308]
	ldr	s0, [x19, #312]
	ldr	s24, [x19, #320]
	ldr	s16, [x19, #324]
	stp	s2, s3, [sp, #80]               ; 8-byte Folded Spill
	fneg	s1, s2
	str	s1, [sp, #36]                   ; 4-byte Folded Spill
	fneg	s2, s3
	stp	s4, s5, [sp, #88]               ; 8-byte Folded Spill
	fneg	s1, s4
	stp	s1, s2, [sp, #28]               ; 8-byte Folded Spill
	fneg	s2, s5
	stp	s6, s26, [sp, #96]              ; 8-byte Folded Spill
	fneg	s1, s6
	stp	s1, s2, [sp, #20]               ; 8-byte Folded Spill
	fneg	s2, s26
	stp	s27, s29, [sp, #104]            ; 8-byte Folded Spill
	fneg	s1, s27
	stp	s1, s2, [sp, #12]               ; 8-byte Folded Spill
	fneg	s2, s29
	fmov	s11, s25
	fneg	s1, s25
	stp	s1, s2, [sp, #4]                ; 8-byte Folded Spill
	fmov	s10, s7
	fneg	s1, s7
	str	s1, [sp]                        ; 4-byte Folded Spill
	ldr	s19, [x19, #332]
	ldr	s7, [x19, #336]
	ldr	s6, [x19, #344]
	ldr	s3, [x19, #348]
	ldr	s18, [x19, #356]
	ldr	s2, [x19, #360]
	ldr	s1, [x19, #368]
	ldr	s29, [x19, #372]
LBB17_2:                                ; =>This Inner Loop Header: Depth=1
	fmov	s23, s9
	fmov	s22, s8
	fmov	s21, s31
	fmov	s5, s30
	fmov	s20, s28
	fmov	s4, s24
	fmov	s26, s19
	fmov	s25, s6
	fmov	s27, s18
	fmov	s17, s1
	ldp	s19, s1, [sp, #36]              ; 8-byte Folded Reload
	fmul	s1, s1, s9
	ldr	d6, [x21], #8
	fcvt	s6, d6
	ldur	s18, [x29, #-120]               ; 4-byte Folded Reload
	fmadd	s18, s18, s12, s1
	fmadd	s9, s19, s18, s6
	ldr	s6, [sp, #44]                   ; 4-byte Folded Reload
	fmul	s6, s6, s8
	ldp	s18, s19, [x29, #-128]          ; 8-byte Folded Reload
	fmadd	s1, s19, s9, s1
	fmadd	s1, s18, s12, s1
	ldur	s18, [x29, #-136]               ; 4-byte Folded Reload
	fmadd	s18, s18, s13, s6
	ldr	s19, [sp, #32]                  ; 4-byte Folded Reload
	fmul	s18, s18, s19
	ldr	s19, [sp, #80]                  ; 4-byte Folded Reload
	fmadd	s8, s19, s1, s18
	ldr	s1, [sp, #48]                   ; 4-byte Folded Reload
	fmul	s1, s1, s31
	ldp	s18, s19, [x29, #-144]          ; 8-byte Folded Reload
	fmadd	s6, s19, s8, s6
	fmadd	s6, s18, s13, s6
	ldur	s18, [x29, #-152]               ; 4-byte Folded Reload
	fmadd	s18, s18, s14, s1
	ldr	s19, [sp, #28]                  ; 4-byte Folded Reload
	fmul	s18, s18, s19
	ldr	s19, [sp, #84]                  ; 4-byte Folded Reload
	fmadd	s31, s19, s6, s18
	ldr	s6, [sp, #52]                   ; 4-byte Folded Reload
	fmul	s6, s6, s30
	ldp	s18, s19, [x29, #-160]          ; 8-byte Folded Reload
	fmadd	s1, s19, s31, s1
	fmadd	s1, s18, s14, s1
	ldur	s18, [x29, #-168]               ; 4-byte Folded Reload
	fmadd	s18, s18, s15, s6
	ldr	s19, [sp, #24]                  ; 4-byte Folded Reload
	fmul	s18, s18, s19
	ldr	s19, [sp, #88]                  ; 4-byte Folded Reload
	fmadd	s30, s19, s1, s18
	ldr	s1, [sp, #56]                   ; 4-byte Folded Reload
	fmul	s1, s1, s28
	ldp	s18, s19, [x29, #-176]          ; 8-byte Folded Reload
	fmadd	s6, s19, s30, s6
	fmadd	s6, s18, s15, s6
	ldur	s18, [x29, #-184]               ; 4-byte Folded Reload
	fmadd	s18, s18, s0, s1
	ldr	s19, [sp, #20]                  ; 4-byte Folded Reload
	fmul	s18, s18, s19
	ldr	s19, [sp, #92]                  ; 4-byte Folded Reload
	fmadd	s28, s19, s6, s18
	ldr	s6, [sp, #60]                   ; 4-byte Folded Reload
	fmul	s6, s6, s24
	ldur	s18, [x29, #-188]               ; 4-byte Folded Reload
	fmadd	s1, s18, s28, s1
	ldr	s18, [sp, #192]                 ; 4-byte Folded Reload
	fmadd	s0, s18, s0, s1
	ldr	s1, [sp, #184]                  ; 4-byte Folded Reload
	fmadd	s1, s1, s16, s6
	ldr	s18, [sp, #16]                  ; 4-byte Folded Reload
	fmul	s1, s1, s18
	ldr	s18, [sp, #96]                  ; 4-byte Folded Reload
	fmadd	s24, s18, s0, s1
	ldr	s0, [sp, #64]                   ; 4-byte Folded Reload
	fmul	s0, s0, s26
	ldr	s1, [sp, #180]                  ; 4-byte Folded Reload
	fmadd	s1, s1, s24, s6
	ldr	s6, [sp, #176]                  ; 4-byte Folded Reload
	fmadd	s1, s6, s16, s1
	ldr	s6, [sp, #168]                  ; 4-byte Folded Reload
	fmadd	s6, s6, s7, s0
	ldr	s16, [sp, #12]                  ; 4-byte Folded Reload
	fmul	s6, s6, s16
	ldr	s16, [sp, #100]                 ; 4-byte Folded Reload
	fmadd	s19, s16, s1, s6
	ldr	s1, [sp, #68]                   ; 4-byte Folded Reload
	fmul	s1, s1, s25
	ldr	s6, [sp, #164]                  ; 4-byte Folded Reload
	fmadd	s0, s6, s19, s0
	ldr	s6, [sp, #160]                  ; 4-byte Folded Reload
	fmadd	s0, s6, s7, s0
	ldr	s6, [sp, #152]                  ; 4-byte Folded Reload
	fmadd	s6, s6, s3, s1
	ldr	s7, [sp, #8]                    ; 4-byte Folded Reload
	fmul	s6, s6, s7
	ldr	s7, [sp, #104]                  ; 4-byte Folded Reload
	fmadd	s6, s7, s0, s6
	ldr	s0, [sp, #72]                   ; 4-byte Folded Reload
	fmul	s0, s0, s27
	ldr	s7, [sp, #148]                  ; 4-byte Folded Reload
	fmadd	s1, s7, s6, s1
	ldr	s7, [sp, #144]                  ; 4-byte Folded Reload
	fmadd	s1, s7, s3, s1
	ldr	s3, [sp, #136]                  ; 4-byte Folded Reload
	fmadd	s3, s3, s2, s0
	ldr	s7, [sp, #4]                    ; 4-byte Folded Reload
	fmul	s3, s3, s7
	ldr	s7, [sp, #108]                  ; 4-byte Folded Reload
	fmadd	s18, s7, s1, s3
	ldr	s1, [sp, #76]                   ; 4-byte Folded Reload
	fmul	s3, s1, s17
	ldp	s1, s7, [sp, #128]              ; 8-byte Folded Reload
	fmadd	s0, s7, s18, s0
	fmadd	s0, s1, s2, s0
	ldr	s1, [sp, #120]                  ; 4-byte Folded Reload
	fmadd	s1, s1, s29, s3
	ldr	s2, [sp]                        ; 4-byte Folded Reload
	fmul	s1, s1, s2
	fmadd	s1, s11, s0, s1
	ldp	s2, s0, [sp, #112]              ; 8-byte Folded Reload
	fmadd	s0, s0, s1, s3
	fmadd	s0, s2, s29, s0
	fmul	s0, s10, s0
	fcvt	d0, s0
	str	d0, [x22], #8
	fmov	s29, s17
	fmov	s2, s27
	fmov	s3, s25
	fmov	s7, s26
	fmov	s16, s4
	fmov	s0, s20
	fmov	s15, s5
	fmov	s14, s21
	fmov	s13, s22
	fmov	s12, s23
	subs	x8, x8, #1
	b.ne	LBB17_2
; %bb.3:
	str	s9, [x19, #260]
	str	s23, [x19, #264]
	str	s9, [x19, #256]
	str	s8, [x19, #272]
	str	s22, [x19, #276]
	str	s8, [x19, #268]
	str	s31, [x19, #284]
	str	s21, [x19, #288]
	str	s31, [x19, #280]
	str	s30, [x19, #296]
	str	s5, [x19, #300]
	str	s30, [x19, #292]
	str	s28, [x19, #308]
	str	s20, [x19, #312]
	str	s28, [x19, #304]
	str	s24, [x19, #320]
	str	s4, [x19, #324]
	str	s24, [x19, #316]
	str	s19, [x19, #332]
	str	s26, [x19, #336]
	str	s19, [x19, #328]
	str	s6, [x19, #344]
	str	s25, [x19, #348]
	str	s6, [x19, #340]
	str	s18, [x19, #356]
	str	s27, [x19, #360]
	str	s18, [x19, #352]
	str	s1, [x19, #368]
	str	s17, [x19, #372]
	str	s1, [x19, #364]
LBB17_4:
	ldp	x29, x30, [sp, #384]            ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #368]            ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #352]            ; 16-byte Folded Reload
	ldp	x28, x27, [sp, #336]            ; 16-byte Folded Reload
	ldp	d9, d8, [sp, #320]              ; 16-byte Folded Reload
	ldp	d11, d10, [sp, #304]            ; 16-byte Folded Reload
	ldp	d13, d12, [sp, #288]            ; 16-byte Folded Reload
	ldp	d15, d14, [sp, #272]            ; 16-byte Folded Reload
	add	sp, sp, #400
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; C++ 64bit
	sub	sp, sp, #400
	stp	d15, d14, [sp, #272]            ; 16-byte Folded Spill
	stp	d13, d12, [sp, #288]            ; 16-byte Folded Spill
	stp	d11, d10, [sp, #304]            ; 16-byte Folded Spill
	stp	d9, d8, [sp, #320]              ; 16-byte Folded Spill
	stp	x28, x27, [sp, #336]            ; 16-byte Folded Spill
	stp	x22, x21, [sp, #352]            ; 16-byte Folded Spill
	stp	x20, x19, [sp, #368]            ; 16-byte Folded Spill
	stp	x29, x30, [sp, #384]            ; 16-byte Folded Spill
	add	x29, sp, #384
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w27, -56
	.cfi_offset w28, -64
	.cfi_offset b8, -72
	.cfi_offset b9, -80
	.cfi_offset b10, -88
	.cfi_offset b11, -96
	.cfi_offset b12, -104
	.cfi_offset b13, -112
	.cfi_offset b14, -120
	.cfi_offset b15, -128
	mov	x20, x1
	mov	x19, x0
	ldr	x21, [x2]
	ldr	x22, [x3]
	ldr	s10, [x0, #12]
	ldr	d0, [x0, #16]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	str	s0, [sp, #112]                  ; 4-byte Folded Spill
	ldp	d0, d1, [x19, #24]
	str	d1, [sp, #120]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	mov	w8, #52429                      ; =0xcccd
	movk	w8, #48460, lsl #16
	fmov	s12, w8
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #116]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #40]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	str	s0, [sp, #128]                  ; 4-byte Folded Spill
	ldp	d0, d1, [x19, #48]
	str	d1, [sp, #136]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #132]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #64]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	str	s0, [sp, #144]                  ; 4-byte Folded Spill
	ldp	d0, d1, [x19, #72]
	str	d1, [sp, #152]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #148]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #88]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s14, s0
	ldp	d0, d1, [x19, #96]
	str	d1, [sp, #168]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #164]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #112]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s9, s0
	ldp	d0, d1, [x19, #120]
	str	d1, [sp, #184]                  ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	str	s0, [sp, #180]                  ; 4-byte Folded Spill
	ldr	d0, [x19, #136]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s13, s0
	ldp	d0, d1, [x19, #144]
	stur	d1, [x29, #-184]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	stur	s0, [x29, #-188]                ; 4-byte Folded Spill
	ldr	d0, [x19, #160]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s11, s0
	ldp	d0, d1, [x19, #168]
	stur	d1, [x29, #-168]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	stur	s0, [x29, #-172]                ; 4-byte Folded Spill
	ldr	d0, [x19, #184]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s15, s0
	ldp	d0, d1, [x19, #192]
	stur	d1, [x29, #-152]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	stur	s0, [x29, #-156]                ; 4-byte Folded Spill
	ldr	d0, [x19, #208]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s8, s0
	ldp	d0, d1, [x19, #216]
	stur	d1, [x29, #-136]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	stur	s0, [x29, #-140]                ; 4-byte Folded Spill
	ldr	d0, [x19, #232]
	fcvt	s0, d0
	fmul	s0, s10, s0
	bl	_tanf
	fmov	s10, s0
	ldp	d0, d1, [x19, #240]
	stur	d1, [x29, #-120]                ; 8-byte Folded Spill
	fcvt	s0, d0
	fmul	s0, s0, s12
	bl	___exp10f
	cmp	w20, #1
	b.lt	LBB17_4
; %bb.1:
	ldr	s31, [sp, #112]                 ; 4-byte Folded Reload
	fmul	s2, s31, s31
	fmov	s1, #-1.00000000
	fadd	s16, s2, s1
	ldr	s30, [sp, #128]                 ; 4-byte Folded Reload
	fmul	s2, s30, s30
	fadd	s17, s2, s1
	ldr	s29, [sp, #144]                 ; 4-byte Folded Reload
	fmul	s2, s29, s29
	fadd	s18, s2, s1
	fmul	s2, s14, s14
	fadd	s19, s2, s1
	fmul	s2, s9, s9
	fadd	s20, s2, s1
	fmul	s2, s13, s13
	fadd	s21, s2, s1
	fmul	s2, s11, s11
	fadd	s22, s2, s1
	fmul	s2, s15, s15
	fadd	s23, s2, s1
	fmul	s2, s8, s8
	fadd	s24, s2, s1
	fmul	s2, s10, s10
	fadd	s1, s2, s1
	ldur	d2, [x29, #-120]                ; 8-byte Folded Reload
	fcvt	s3, d2
	fdiv	s4, s0, s3
	fmov	s0, #1.00000000
	fadd	s2, s10, s4
	fmadd	s2, s10, s2, s0
	fsub	s4, s10, s4
	fmadd	s5, s10, s4, s0
	fdiv	s3, s0, s3
	fadd	s4, s10, s3
	fmadd	s4, s10, s4, s0
	stp	s4, s5, [x29, #-124]            ; 8-byte Folded Spill
	fsub	s3, s3, s10
	fmsub	s3, s10, s3, s0
	stur	s3, [x29, #-128]                ; 4-byte Folded Spill
	ldur	d3, [x29, #-136]                ; 8-byte Folded Reload
	fcvt	s4, d3
	ldur	s3, [x29, #-140]                ; 4-byte Folded Reload
	fdiv	s5, s3, s4
	fadd	s3, s8, s5
	fmadd	s3, s8, s3, s0
	fsub	s5, s8, s5
	fmadd	s6, s8, s5, s0
	fdiv	s4, s0, s4
	fadd	s5, s8, s4
	fmadd	s5, s8, s5, s0
	stp	s5, s6, [x29, #-140]            ; 8-byte Folded Spill
	fsub	s4, s4, s8
	fmsub	s4, s8, s4, s0
	stur	s4, [x29, #-144]                ; 4-byte Folded Spill
	ldur	d4, [x29, #-152]                ; 8-byte Folded Reload
	fcvt	s5, d4
	ldur	s4, [x29, #-156]                ; 4-byte Folded Reload
	fdiv	s6, s4, s5
	fadd	s4, s15, s6
	fmadd	s4, s15, s4, s0
	fsub	s6, s15, s6
	fmadd	s7, s15, s6, s0
	fdiv	s5, s0, s5
	fadd	s6, s15, s5
	fmadd	s6, s15, s6, s0
	stp	s6, s7, [x29, #-156]            ; 8-byte Folded Spill
	fsub	s5, s5, s15
	fmsub	s5, s15, s5, s0
	stur	s5, [x29, #-160]                ; 4-byte Folded Spill
	ldur	d5, [x29, #-168]                ; 8-byte Folded Reload
	fcvt	s6, d5
	ldur	s5, [x29, #-172]                ; 4-byte Folded Reload
	fdiv	s7, s5, s6
	fadd	s5, s11, s7
	fmadd	s5, s11, s5, s0
	fsub	s7, s11, s7
	fmadd	s7, s11, s7, s0
	stur	s7, [x29, #-168]                ; 4-byte Folded Spill
	fdiv	s6, s0, s6
	fadd	s7, s11, s6
	fmadd	s7, s11, s7, s0
	fsub	s6, s6, s11
	fmsub	s6, s11, s6, s0
	stp	s6, s7, [x29, #-176]            ; 8-byte Folded Spill
	ldur	d6, [x29, #-184]                ; 8-byte Folded Reload
	fcvt	s7, d6
	ldur	s6, [x29, #-188]                ; 4-byte Folded Reload
	fdiv	s25, s6, s7
	fadd	s6, s13, s25
	fmadd	s6, s13, s6, s0
	fsub	s25, s13, s25
	fmadd	s26, s13, s25, s0
	fdiv	s7, s0, s7
	fadd	s25, s13, s7
	fmadd	s25, s13, s25, s0
	stp	s25, s26, [x29, #-188]          ; 8-byte Folded Spill
	fsub	s7, s7, s13
	fmsub	s7, s13, s7, s0
	str	s7, [sp, #192]                  ; 4-byte Folded Spill
	ldr	d7, [sp, #184]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #180]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s26, s9, s25
	fmadd	s26, s9, s26, s0
	fsub	s25, s9, s25
	fmadd	s27, s9, s25, s0
	fdiv	s7, s0, s7
	fadd	s25, s9, s7
	fmadd	s25, s9, s25, s0
	stp	s25, s27, [sp, #180]            ; 8-byte Folded Spill
	fsub	s7, s7, s9
	fmsub	s7, s9, s7, s0
	str	s7, [sp, #176]                  ; 4-byte Folded Spill
	ldr	d7, [sp, #168]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #164]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s27, s14, s25
	fmadd	s27, s14, s27, s0
	fsub	s25, s14, s25
	fmadd	s28, s14, s25, s0
	fdiv	s7, s0, s7
	fadd	s25, s14, s7
	fmadd	s25, s14, s25, s0
	stp	s25, s28, [sp, #164]            ; 8-byte Folded Spill
	fsub	s7, s7, s14
	fmsub	s7, s14, s7, s0
	str	s7, [sp, #160]                  ; 4-byte Folded Spill
	ldr	d7, [sp, #152]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #148]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s28, s29, s25
	fmadd	s28, s29, s28, s0
	fsub	s25, s29, s25
	fmadd	s25, s29, s25, s0
	str	s25, [sp, #152]                 ; 4-byte Folded Spill
	fdiv	s7, s0, s7
	fadd	s25, s29, s7
	fmadd	s25, s29, s25, s0
	fsub	s7, s7, s29
	fmsub	s7, s29, s7, s0
	stp	s7, s25, [sp, #144]             ; 8-byte Folded Spill
	ldr	d7, [sp, #136]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #132]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s29, s30, s25
	fmadd	s29, s30, s29, s0
	fsub	s25, s30, s25
	fmadd	s25, s30, s25, s0
	str	s25, [sp, #136]                 ; 4-byte Folded Spill
	fdiv	s7, s0, s7
	fadd	s25, s30, s7
	fmadd	s25, s30, s25, s0
	fsub	s7, s7, s30
	fmsub	s7, s30, s7, s0
	stp	s7, s25, [sp, #128]             ; 8-byte Folded Spill
	ldr	d7, [sp, #120]                  ; 8-byte Folded Reload
	fcvt	s7, d7
	ldr	s25, [sp, #116]                 ; 4-byte Folded Reload
	fdiv	s25, s25, s7
	fadd	s30, s31, s25
	fmadd	s30, s31, s30, s0
	fsub	s25, s31, s25
	fmadd	s25, s31, s25, s0
	str	s25, [sp, #120]                 ; 4-byte Folded Spill
	fdiv	s7, s0, s7
	fadd	s25, s31, s7
	fmadd	s25, s31, s25, s0
	fsub	s7, s7, s31
	fmsub	s7, s31, s7, s0
	stp	s7, s25, [sp, #112]             ; 8-byte Folded Spill
	fdiv	s7, s0, s30
	fdiv	s25, s0, s29
	fdiv	s29, s0, s28
	fdiv	s27, s0, s27
	fdiv	s26, s0, s26
	fdiv	s6, s0, s6
	fdiv	s5, s0, s5
	fdiv	s4, s0, s4
	fdiv	s3, s0, s3
	fdiv	s2, s0, s2
	fadd	s0, s16, s16
	str	s0, [sp, #76]                   ; 4-byte Folded Spill
	fadd	s0, s17, s17
	str	s0, [sp, #72]                   ; 4-byte Folded Spill
	fadd	s0, s18, s18
	str	s0, [sp, #68]                   ; 4-byte Folded Spill
	fadd	s0, s19, s19
	str	s0, [sp, #64]                   ; 4-byte Folded Spill
	fadd	s0, s20, s20
	str	s0, [sp, #60]                   ; 4-byte Folded Spill
	fadd	s0, s21, s21
	str	s0, [sp, #56]                   ; 4-byte Folded Spill
	fadd	s0, s22, s22
	str	s0, [sp, #52]                   ; 4-byte Folded Spill
	fadd	s0, s23, s23
	str	s0, [sp, #48]                   ; 4-byte Folded Spill
	fadd	s0, s24, s24
	str	s0, [sp, #44]                   ; 4-byte Folded Spill
	fadd	s0, s1, s1
	str	s0, [sp, #40]                   ; 4-byte Folded Spill
	mov	w8, w20
	ldr	s9, [x19, #260]
	ldr	s12, [x19, #264]
	ldr	s8, [x19, #272]
	ldr	s13, [x19, #276]
	ldr	s31, [x19, #284]
	ldr	s14, [x19, #288]
	ldr	s30, [x19, #296]
	ldr	s15, [x19, #300]
	ldr	s28, [x19, #308]
	ldr	s0, [x19, #312]
	ldr	s24, [x19, #320]
	ldr	s16, [x19, #324]
	stp	s2, s3, [sp, #80]               ; 8-byte Folded Spill
	fneg	s1, s2
	str	s1, [sp, #36]                   ; 4-byte Folded Spill
	fneg	s2, s3
	stp	s4, s5, [sp, #88]               ; 8-byte Folded Spill
	fneg	s1, s4
	stp	s1, s2, [sp, #28]               ; 8-byte Folded Spill
	fneg	s2, s5
	stp	s6, s26, [sp, #96]              ; 8-byte Folded Spill
	fneg	s1, s6
	stp	s1, s2, [sp, #20]               ; 8-byte Folded Spill
	fneg	s2, s26
	stp	s27, s29, [sp, #104]            ; 8-byte Folded Spill
	fneg	s1, s27
	stp	s1, s2, [sp, #12]               ; 8-byte Folded Spill
	fneg	s2, s29
	fmov	s11, s25
	fneg	s1, s25
	stp	s1, s2, [sp, #4]                ; 8-byte Folded Spill
	fmov	s10, s7
	fneg	s1, s7
	str	s1, [sp]                        ; 4-byte Folded Spill
	ldr	s19, [x19, #332]
	ldr	s7, [x19, #336]
	ldr	s6, [x19, #344]
	ldr	s3, [x19, #348]
	ldr	s18, [x19, #356]
	ldr	s2, [x19, #360]
	ldr	s1, [x19, #368]
	ldr	s29, [x19, #372]
LBB17_2:                                ; =>This Inner Loop Header: Depth=1
	fmov	s23, s9
	fmov	s22, s8
	fmov	s21, s31
	fmov	s5, s30
	fmov	s20, s28
	fmov	s4, s24
	fmov	s26, s19
	fmov	s25, s6
	fmov	s27, s18
	fmov	s17, s1
	ldp	s19, s1, [sp, #36]              ; 8-byte Folded Reload
	fmul	s1, s1, s9
	ldr	d6, [x21], #8
	fcvt	s6, d6
	ldur	s18, [x29, #-120]               ; 4-byte Folded Reload
	fmadd	s18, s18, s12, s1
	fmadd	s9, s19, s18, s6
	ldr	s6, [sp, #44]                   ; 4-byte Folded Reload
	fmul	s6, s6, s8
	ldp	s18, s19, [x29, #-128]          ; 8-byte Folded Reload
	fmadd	s1, s19, s9, s1
	fmadd	s1, s18, s12, s1
	ldur	s18, [x29, #-136]               ; 4-byte Folded Reload
	fmadd	s18, s18, s13, s6
	ldr	s19, [sp, #32]                  ; 4-byte Folded Reload
	fmul	s18, s18, s19
	ldr	s19, [sp, #80]                  ; 4-byte Folded Reload
	fmadd	s8, s19, s1, s18
	ldr	s1, [sp, #48]                   ; 4-byte Folded Reload
	fmul	s1, s1, s31
	ldp	s18, s19, [x29, #-144]          ; 8-byte Folded Reload
	fmadd	s6, s19, s8, s6
	fmadd	s6, s18, s13, s6
	ldur	s18, [x29, #-152]               ; 4-byte Folded Reload
	fmadd	s18, s18, s14, s1
	ldr	s19, [sp, #28]                  ; 4-byte Folded Reload
	fmul	s18, s18, s19
	ldr	s19, [sp, #84]                  ; 4-byte Folded Reload
	fmadd	s31, s19, s6, s18
	ldr	s6, [sp, #52]                   ; 4-byte Folded Reload
	fmul	s6, s6, s30
	ldp	s18, s19, [x29, #-160]          ; 8-byte Folded Reload
	fmadd	s1, s19, s31, s1
	fmadd	s1, s18, s14, s1
	ldur	s18, [x29, #-168]               ; 4-byte Folded Reload
	fmadd	s18, s18, s15, s6
	ldr	s19, [sp, #24]                  ; 4-byte Folded Reload
	fmul	s18, s18, s19
	ldr	s19, [sp, #88]                  ; 4-byte Folded Reload
	fmadd	s30, s19, s1, s18
	ldr	s1, [sp, #56]                   ; 4-byte Folded Reload
	fmul	s1, s1, s28
	ldp	s18, s19, [x29, #-176]          ; 8-byte Folded Reload
	fmadd	s6, s19, s30, s6
	fmadd	s6, s18, s15, s6
	ldur	s18, [x29, #-184]               ; 4-byte Folded Reload
	fmadd	s18, s18, s0, s1
	ldr	s19, [sp, #20]                  ; 4-byte Folded Reload
	fmul	s18, s18, s19
	ldr	s19, [sp, #92]                  ; 4-byte Folded Reload
	fmadd	s28, s19, s6, s18
	ldr	s6, [sp, #60]                   ; 4-byte Folded Reload
	fmul	s6, s6, s24
	ldur	s18, [x29, #-188]               ; 4-byte Folded Reload
	fmadd	s1, s18, s28, s1
	ldr	s18, [sp, #192]                 ; 4-byte Folded Reload
	fmadd	s0, s18, s0, s1
	ldr	s1, [sp, #184]                  ; 4-byte Folded Reload
	fmadd	s1, s1, s16, s6
	ldr	s18, [sp, #16]                  ; 4-byte Folded Reload
	fmul	s1, s1, s18
	ldr	s18, [sp, #96]                  ; 4-byte Folded Reload
	fmadd	s24, s18, s0, s1
	ldr	s0, [sp, #64]                   ; 4-byte Folded Reload
	fmul	s0, s0, s26
	ldr	s1, [sp, #180]                  ; 4-byte Folded Reload
	fmadd	s1, s1, s24, s6
	ldr	s6, [sp, #176]                  ; 4-byte Folded Reload
	fmadd	s1, s6, s16, s1
	ldr	s6, [sp, #168]                  ; 4-byte Folded Reload
	fmadd	s6, s6, s7, s0
	ldr	s16, [sp, #12]                  ; 4-byte Folded Reload
	fmul	s6, s6, s16
	ldr	s16, [sp, #100]                 ; 4-byte Folded Reload
	fmadd	s19, s16, s1, s6
	ldr	s1, [sp, #68]                   ; 4-byte Folded Reload
	fmul	s1, s1, s25
	ldr	s6, [sp, #164]                  ; 4-byte Folded Reload
	fmadd	s0, s6, s19, s0
	ldr	s6, [sp, #160]                  ; 4-byte Folded Reload
	fmadd	s0, s6, s7, s0
	ldr	s6, [sp, #152]                  ; 4-byte Folded Reload
	fmadd	s6, s6, s3, s1
	ldr	s7, [sp, #8]                    ; 4-byte Folded Reload
	fmul	s6, s6, s7
	ldr	s7, [sp, #104]                  ; 4-byte Folded Reload
	fmadd	s6, s7, s0, s6
	ldr	s0, [sp, #72]                   ; 4-byte Folded Reload
	fmul	s0, s0, s27
	ldr	s7, [sp, #148]                  ; 4-byte Folded Reload
	fmadd	s1, s7, s6, s1
	ldr	s7, [sp, #144]                  ; 4-byte Folded Reload
	fmadd	s1, s7, s3, s1
	ldr	s3, [sp, #136]                  ; 4-byte Folded Reload
	fmadd	s3, s3, s2, s0
	ldr	s7, [sp, #4]                    ; 4-byte Folded Reload
	fmul	s3, s3, s7
	ldr	s7, [sp, #108]                  ; 4-byte Folded Reload
	fmadd	s18, s7, s1, s3
	ldr	s1, [sp, #76]                   ; 4-byte Folded Reload
	fmul	s3, s1, s17
	ldp	s1, s7, [sp, #128]              ; 8-byte Folded Reload
	fmadd	s0, s7, s18, s0
	fmadd	s0, s1, s2, s0
	ldr	s1, [sp, #120]                  ; 4-byte Folded Reload
	fmadd	s1, s1, s29, s3
	ldr	s2, [sp]                        ; 4-byte Folded Reload
	fmul	s1, s1, s2
	fmadd	s1, s11, s0, s1
	ldp	s2, s0, [sp, #112]              ; 8-byte Folded Reload
	fmadd	s0, s0, s1, s3
	fmadd	s0, s2, s29, s0
	fmul	s0, s10, s0
	fcvt	d0, s0
	str	d0, [x22], #8
	fmov	s29, s17
	fmov	s2, s27
	fmov	s3, s25
	fmov	s7, s26
	fmov	s16, s4
	fmov	s0, s20
	fmov	s15, s5
	fmov	s14, s21
	fmov	s13, s22
	fmov	s12, s23
	subs	x8, x8, #1
	b.ne	LBB17_2
; %bb.3:
	str	s9, [x19, #260]
	str	s23, [x19, #264]
	str	s9, [x19, #256]
	str	s8, [x19, #272]
	str	s22, [x19, #276]
	str	s8, [x19, #268]
	str	s31, [x19, #284]
	str	s21, [x19, #288]
	str	s31, [x19, #280]
	str	s30, [x19, #296]
	str	s5, [x19, #300]
	str	s30, [x19, #292]
	str	s28, [x19, #308]
	str	s20, [x19, #312]
	str	s28, [x19, #304]
	str	s24, [x19, #320]
	str	s4, [x19, #324]
	str	s24, [x19, #316]
	str	s19, [x19, #332]
	str	s26, [x19, #336]
	str	s19, [x19, #328]
	str	s6, [x19, #344]
	str	s25, [x19, #348]
	str	s6, [x19, #340]
	str	s18, [x19, #356]
	str	s27, [x19, #360]
	str	s18, [x19, #352]
	str	s1, [x19, #368]
	str	s17, [x19, #372]
	str	s1, [x19, #364]
LBB17_4:
	ldp	x29, x30, [sp, #384]            ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #368]            ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #352]            ; 16-byte Folded Reload
	ldp	x28, x27, [sp, #336]            ; 16-byte Folded Reload
	ldp	d9, d8, [sp, #320]              ; 16-byte Folded Reload
	ldp	d11, d10, [sp, #304]            ; 16-byte Folded Reload
	ldp	d13, d12, [sp, #288]            ; 16-byte Folded Reload
	ldp	d15, d14, [sp, #272]            ; 16-byte Folded Reload
	add	sp, sp, #400
	ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Mojo 32bit
_inspect_compute:
	sub	sp, sp, #288
	stp	d15, d14, [sp, #176]
	stp	d13, d12, [sp, #192]
	stp	d11, d10, [sp, #208]
	stp	d9, d8, [sp, #224]
	stp	x22, x21, [sp, #240]
	stp	x20, x19, [sp, #256]
	stp	x29, x30, [sp, #272]
	mov	x19, x0
	str	x1, [sp, #168]
	add	x8, sp, #168
	; InlineAsm Start
	; InlineAsm End
	str	x2, [sp, #168]
	; InlineAsm Start
	; InlineAsm End
	ldr	x20, [x1]
	ldr	x21, [x2]
	ldp	s9, s0, [x0, #8]
	fmul	s0, s0, s9
	bl	_tanf
	mov.16b	v10, v0
	ldp	s0, s8, [x19, #16]
	str	s8, [sp, #20]
	mov	w8, #52429
	movk	w8, #48460, lsl #16
	fmov	s2, w8
	fmul	s1, s0, s2
	mov.16b	v13, v2
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s8
	stp	s10, s0, [sp, #12]
	fadd	s0, s10, s0
	fmov	s1, #1.00000000
	fmadd	s0, s10, s0, s1
	fdiv	s3, s1, s0
	fmov	s11, #1.00000000
	fmov	s0, #-1.00000000
	fmadd	s0, s10, s10, s0
	fmov	s14, #-1.00000000
	fadd	s0, s0, s0
	stp	s0, s3, [sp, #160]
	ldr	s0, [x19, #24]
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v10, v0
	ldp	s0, s8, [x19, #28]
	str	s8, [sp, #8]
	fmul	s1, s0, s13
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s8
	str	s0, [sp, #24]
	str	s10, [sp, #4]
	fadd	s0, s10, s0
	fmadd	s0, s10, s0, s11
	fdiv	s3, s11, s0
	fmadd	s0, s10, s10, s14
	fadd	s0, s0, s0
	stp	s0, s3, [sp, #152]
	ldr	s0, [x19, #36]
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v10, v0
	ldp	s0, s8, [x19, #40]
	str	s8, [sp, #32]
	fmul	s1, s0, s13
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s8
	str	s0, [sp, #36]
	str	s10, [sp, #28]
	fadd	s0, s10, s0
	fmadd	s0, s10, s0, s11
	fdiv	s11, s11, s0
	fmadd	s0, s10, s10, s14
	fadd	s0, s0, s0
	str	s0, [sp, #148]
	ldr	s0, [x19, #48]
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v14, v0
	ldp	s0, s10, [x19, #52]
	str	s10, [sp, #44]
	mov.16b	v8, v13
	fmul	s1, s0, s13
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s10
	str	s0, [sp, #48]
	str	s14, [sp, #40]
	fadd	s0, s14, s0
	fmov	s1, #1.00000000
	fmadd	s0, s14, s0, s1
	fdiv	s13, s1, s0
	fmov	s10, #-1.00000000
	fmadd	s0, s14, s14, s10
	fadd	s0, s0, s0
	str	s0, [sp, #144]
	ldr	s0, [x19, #60]
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v15, v0
	ldp	s0, s14, [x19, #64]
	str	s14, [sp, #56]
	fmul	s1, s0, s8
	mov.16b	v12, v8
	str	s8, [sp, #120]
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s14
	str	s0, [sp, #60]
	str	s15, [sp, #52]
	fadd	s0, s15, s0
	fmov	s1, #1.00000000
	fmadd	s0, s15, s0, s1
	fdiv	s14, s1, s0
	fmadd	s0, s15, s15, s10
	fadd	s0, s0, s0
	str	s0, [sp, #140]
	ldr	s0, [x19, #72]
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v10, v0
	ldp	s0, s8, [x19, #76]
	str	s8, [sp, #68]
	fmul	s1, s0, s12
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s8
	str	s0, [sp, #72]
	str	s10, [sp, #64]
	fadd	s0, s10, s0
	fmov	s1, #1.00000000
	fmadd	s0, s10, s0, s1
	fdiv	s15, s1, s0
	fmov	s0, #-1.00000000
	fmadd	s0, s10, s10, s0
	fadd	s0, s0, s0
	str	s0, [sp, #136]
	ldr	s0, [x19, #84]
	fmul	s0, s9, s0
	str	s9, [sp, #116]
	bl	_tanf
	mov.16b	v12, v0
	ldp	s0, s10, [x19, #88]
	str	s10, [sp, #80]
	ldr	s8, [sp, #120]
	fmul	s1, s0, s8
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s10
	str	s0, [sp, #84]
	str	s12, [sp, #76]
	fadd	s0, s12, s0
	fmov	s1, #1.00000000
	fmadd	s0, s12, s0, s1
	fdiv	s10, s1, s0
	fmov	s0, #-1.00000000
	fmadd	s0, s12, s12, s0
	fadd	s0, s0, s0
	str	s0, [sp, #132]
	ldr	s0, [x19, #96]
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v9, v0
	ldp	s0, s12, [x19, #100]
	str	s12, [sp, #92]
	fmul	s1, s0, s8
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s12
	str	s0, [sp, #96]
	str	s9, [sp, #88]
	fadd	s0, s9, s0
	fmov	s1, #1.00000000
	fmadd	s0, s9, s0, s1
	fdiv	s8, s1, s0
	fmov	s0, #-1.00000000
	fmadd	s0, s9, s9, s0
	fadd	s0, s0, s0
	str	s0, [sp, #128]
	ldr	s0, [x19, #108]
	ldr	s9, [sp, #116]
	fmul	s0, s9, s0
	bl	_tanf
	ldr	s12, [x19, #116]
	stp	s0, s12, [sp, #100]
	ldr	s0, [x19, #112]
	ldr	s1, [sp, #120]
	fmul	s1, s0, s1
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s12
	str	s0, [sp, #108]
	ldr	s1, [sp, #100]
	fadd	s0, s1, s0
	fmov	s2, #1.00000000
	fmadd	s0, s1, s0, s2
	fdiv	s12, s2, s0
	fmov	s0, #-1.00000000
	fmadd	s0, s1, s1, s0
	fadd	s0, s0, s0
	str	s0, [sp, #124]
	ldr	s0, [x19, #120]
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v9, v0
	ldp	s0, s2, [x19, #124]
	str	s2, [sp, #116]
	ldr	s1, [sp, #120]
	fmul	s1, s0, s1
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	mov	x8, #0
	ldr	s3, [sp, #116]
	fdiv	s0, s0, s3
	fadd	s1, s9, s0
	fmov	s2, #1.00000000
	fmadd	s5, s9, s1, s2
	fmov	s1, #-1.00000000
	fmadd	s6, s9, s9, s1
	fsub	s0, s9, s0
	fmadd	s4, s9, s0, s2
	fdiv	s0, s2, s3
	fadd	s1, s9, s0
	fmadd	s1, s9, s1, s2
	stp	s1, s4, [sp, #116]
	fsub	s0, s0, s9
	fmsub	s1, s9, s0, s2
	ldr	s2, [sp, #100]
	ldr	s0, [sp, #108]
	fsub	s0, s2, s0
	fmov	s16, #1.00000000
	fmadd	s0, s2, s0, s16
	stp	s0, s1, [sp, #108]
	ldr	s0, [sp, #104]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	fsub	s0, s0, s2
	fmsub	s0, s2, s0, s16
	stp	s0, s1, [sp, #100]
	ldr	s2, [sp, #88]
	ldr	s0, [sp, #96]
	fsub	s0, s2, s0
	fmadd	s3, s2, s0, s16
	ldr	s0, [sp, #92]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	stp	s1, s3, [sp, #92]
	fsub	s0, s0, s2
	fmsub	s1, s2, s0, s16
	ldr	s2, [sp, #76]
	ldr	s0, [sp, #84]
	fsub	s0, s2, s0
	fmadd	s0, s2, s0, s16
	stp	s0, s1, [sp, #84]
	ldr	s0, [sp, #80]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	fsub	s0, s0, s2
	fmsub	s0, s2, s0, s16
	stp	s0, s1, [sp, #76]
	ldr	s2, [sp, #64]
	ldr	s0, [sp, #72]
	fsub	s0, s2, s0
	fmadd	s3, s2, s0, s16
	ldr	s0, [sp, #68]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	stp	s1, s3, [sp, #68]
	fsub	s0, s0, s2
	fmsub	s1, s2, s0, s16
	ldr	s2, [sp, #52]
	ldr	s0, [sp, #60]
	fsub	s0, s2, s0
	fmadd	s0, s2, s0, s16
	stp	s0, s1, [sp, #60]
	ldr	s0, [sp, #56]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	fsub	s0, s0, s2
	fmsub	s0, s2, s0, s16
	stp	s0, s1, [sp, #52]
	ldr	s2, [sp, #40]
	ldr	s0, [sp, #48]
	fsub	s0, s2, s0
	fmadd	s3, s2, s0, s16
	ldr	s0, [sp, #44]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	stp	s1, s3, [sp, #44]
	fsub	s0, s0, s2
	fmsub	s1, s2, s0, s16
	ldr	s2, [sp, #28]
	ldr	s0, [sp, #36]
	fsub	s0, s2, s0
	fmadd	s0, s2, s0, s16
	stp	s0, s1, [sp, #36]
	ldr	s0, [sp, #32]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	fsub	s0, s0, s2
	fmsub	s0, s2, s0, s16
	stp	s0, s1, [sp, #28]
	ldr	s2, [sp, #4]
	ldp	s3, s0, [sp, #20]
	fsub	s0, s2, s0
	fmadd	s0, s2, s0, s16
	str	s0, [sp, #24]
	ldp	s0, s7, [sp, #8]
	fdiv	s1, s16, s0
	fadd	s0, s2, s1
	fmadd	s0, s2, s0, s16
	fsub	s1, s1, s2
	fmsub	s1, s2, s1, s16
	ldr	s2, [sp, #16]
	fsub	s2, s7, s2
	fmadd	s2, s7, s2, s16
	fdiv	s4, s16, s3
	fadd	s3, s7, s4
	fmadd	s3, s7, s3, s16
	fsub	s4, s4, s7
	fmsub	s4, s7, s4, s16
	fdiv	s5, s16, s5
	fadd	s6, s6, s6
	ldp	s29, s22, [x19, #136]
	ldp	s27, s21, [x19, #148]
	ldp	s28, s20, [x19, #160]
	ldp	s26, s19, [x19, #172]
	ldp	s25, s18, [x19, #184]
	ldp	s24, s17, [x19, #196]
	ldp	s23, s16, [x19, #208]
	ldp	s30, s7, [x19, #220]
LBB0_1:
	fmul	s29, s6, s29
	ldr	s31, [x20, x8]
	ldr	s9, [sp, #120]
	fmadd	s9, s9, s22, s29
	fmsub	s31, s5, s9, s31
	str	s31, [x19, #132]
	ldr	s9, [sp, #116]
	fmadd	s29, s9, s31, s29
	ldr	s31, [sp, #124]
	fmul	s27, s31, s27
	ldr	s31, [sp, #112]
	fmadd	s22, s31, s22, s29
	ldr	s29, [sp, #108]
	fmadd	s29, s29, s21, s27
	fmul	s29, s12, s29
	fnmsub	s22, s5, s22, s29
	str	s22, [x19, #144]
	ldr	s29, [sp, #128]
	fmul	s28, s29, s28
	ldr	s29, [sp, #104]
	fmadd	s22, s29, s22, s27
	ldr	s27, [sp, #100]
	fmadd	s21, s27, s21, s22
	ldr	s22, [sp, #96]
	fmadd	s22, s22, s20, s28
	fmul	s22, s8, s22
	fnmsub	s21, s12, s21, s22
	str	s21, [x19, #156]
	ldr	s22, [sp, #132]
	fmul	s22, s22, s26
	ldp	s26, s27, [sp, #88]
	fmadd	s21, s27, s21, s28
	fmadd	s20, s26, s20, s21
	ldr	s21, [sp, #84]
	fmadd	s21, s21, s19, s22
	fmul	s21, s10, s21
	fnmsub	s20, s8, s20, s21
	str	s20, [x19, #168]
	ldr	s21, [sp, #136]
	fmul	s21, s21, s25
	ldr	s25, [sp, #80]
	fmadd	s20, s25, s20, s22
	ldr	s22, [sp, #76]
	fmadd	s19, s22, s19, s20
	ldp	s22, s20, [sp, #68]
	fmadd	s20, s20, s18, s21
	fmul	s20, s15, s20
	fnmsub	s19, s10, s19, s20
	str	s19, [x19, #180]
	ldr	s20, [sp, #140]
	fmul	s20, s20, s24
	fmadd	s19, s22, s19, s21
	ldr	s21, [sp, #64]
	fmadd	s18, s21, s18, s19
	ldp	s21, s19, [sp, #56]
	fmadd	s19, s19, s17, s20
	fmul	s19, s14, s19
	fnmsub	s18, s15, s18, s19
	str	s18, [x19, #192]
	ldr	s19, [sp, #144]
	fmul	s19, s19, s23
	fmadd	s18, s21, s18, s20
	ldr	s20, [sp, #52]
	fmadd	s17, s20, s17, s18
	ldp	s20, s18, [sp, #44]
	fmadd	s18, s18, s16, s19
	fmul	s18, s13, s18
	fnmsub	s17, s14, s17, s18
	str	s17, [x19, #204]
	ldr	s18, [sp, #148]
	fmul	s18, s18, s30
	fmadd	s17, s20, s17, s19
	ldr	s19, [sp, #40]
	fmadd	s16, s19, s16, s17
	ldr	s17, [sp, #36]
	fmadd	s17, s17, s7, s18
	fmul	s17, s11, s17
	fnmsub	s16, s13, s16, s17
	str	s16, [x19, #216]
	ldp	s17, s19, [x19, #232]
	ldp	s20, s21, [sp, #152]
	fmul	s17, s20, s17
	ldr	s20, [sp, #32]
	fmadd	s16, s20, s16, s18
	ldr	s18, [sp, #28]
	fmadd	s7, s18, s7, s16
	ldr	s16, [sp, #24]
	fmadd	s16, s16, s19, s17
	fmul	s16, s21, s16
	fnmsub	s7, s11, s7, s16
	str	s7, [x19, #228]
	ldp	s16, s18, [x19, #244]
	ldr	s20, [sp, #160]
	fmul	s16, s20, s16
	fmadd	s7, s0, s7, s17
	fmadd	s7, s1, s19, s7
	fmadd	s17, s2, s18, s16
	ldr	s19, [sp, #164]
	fmul	s17, s19, s17
	fnmsub	s7, s21, s7, s17
	str	s7, [x19, #240]
	fmadd	s7, s3, s7, s16
	fmadd	s7, s4, s18, s7
	fmul	s7, s19, s7
	str	s7, [x21, x8]
	ldr	s22, [x19, #136]
	ldur	d29, [x19, #132]
	str	d29, [x19, #136]
	ldr	s21, [x19, #148]
	ldr	d27, [x19, #144]
	stur	d27, [x19, #148]
	ldr	s20, [x19, #160]
	ldur	d28, [x19, #156]
	str	d28, [x19, #160]
	ldr	s19, [x19, #172]
	ldr	d26, [x19, #168]
	stur	d26, [x19, #172]
	ldr	s18, [x19, #184]
	ldur	d25, [x19, #180]
	str	d25, [x19, #184]
	ldr	s17, [x19, #196]
	ldr	d24, [x19, #192]
	stur	d24, [x19, #196]
	ldr	s16, [x19, #208]
	ldur	d23, [x19, #204]
	str	d23, [x19, #208]
	ldr	s7, [x19, #220]
	ldur	d30, [x19, #228]
	str	d30, [x19, #232]
	ldr	d30, [x19, #240]
	stur	d30, [x19, #244]
	ldr	d30, [x19, #216]
	stur	d30, [x19, #220]
	add	x8, x8, #4
	cmp	x8, #256
	b.ne	LBB0_1
	;MEMBARRIER
	ldp	x29, x30, [sp, #272]
	ldp	x20, x19, [sp, #256]
	ldp	x22, x21, [sp, #240]
	ldp	d9, d8, [sp, #224]
	ldp	d11, d10, [sp, #208]
	ldp	d13, d12, [sp, #192]
	ldp	d15, d14, [sp, #176]
	add	sp, sp, #288
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Mojo 64bit
_inspect_compute:
	sub	sp, sp, #304
	stp	d15, d14, [sp, #176]
	stp	d13, d12, [sp, #192]
	stp	d11, d10, [sp, #208]
	stp	d9, d8, [sp, #224]
	stp	x28, x27, [sp, #240]
	stp	x22, x21, [sp, #256]
	stp	x20, x19, [sp, #272]
	stp	x29, x30, [sp, #288]
	mov	x19, x0
	add	x20, x0, #260
	str	x1, [sp, #168]
	add	x8, sp, #168
	; InlineAsm Start
	; InlineAsm End
	str	x2, [sp, #168]
	; InlineAsm Start
	; InlineAsm End
	ldr	x21, [x1]
	ldr	x22, [x2]
	ldr	d0, [x0, #16]
	fcvt	s0, d0
	ldr	s9, [x0, #12]
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v8, v0
	ldp	d1, d0, [x19, #24]
	fcvt	s10, d0
	str	s10, [sp, #20]
	fcvt	s0, d1
	mov	w8, #52429
	movk	w8, #48460, lsl #16
	fmov	s2, w8
	fmul	s1, s0, s2
	mov.16b	v12, v2
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s10
	stp	s8, s0, [sp, #12]
	fadd	s0, s8, s0
	fmov	s1, #1.00000000
	fmadd	s0, s8, s0, s1
	fdiv	s3, s1, s0
	fmov	s0, #-1.00000000
	fmadd	s0, s8, s8, s0
	fmov	s13, #-1.00000000
	fadd	s0, s0, s0
	stp	s0, s3, [sp, #160]
	ldr	d0, [x19, #40]
	fcvt	s0, d0
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v8, v0
	ldp	d1, d0, [x19, #48]
	fcvt	s10, d0
	str	s10, [sp, #8]
	fcvt	s0, d1
	fmul	s1, s0, s12
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s10
	stp	s8, s0, [sp]
	fadd	s0, s8, s0
	fmov	s1, #1.00000000
	fmadd	s0, s8, s0, s1
	fdiv	s3, s1, s0
	fmadd	s0, s8, s8, s13
	fadd	s0, s0, s0
	stp	s0, s3, [sp, #152]
	ldr	d0, [x19, #64]
	fcvt	s0, d0
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v8, v0
	ldp	d1, d0, [x19, #72]
	fcvt	s10, d0
	str	s10, [sp, #28]
	fcvt	s0, d1
	fmul	s1, s0, s12
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s10
	str	s0, [sp, #32]
	str	s8, [sp, #24]
	fadd	s0, s8, s0
	fmov	s1, #1.00000000
	fmadd	s0, s8, s0, s1
	fdiv	s3, s1, s0
	fmadd	s0, s8, s8, s13
	fadd	s0, s0, s0
	stp	s0, s3, [sp, #144]
	ldr	d0, [x19, #88]
	fcvt	s0, d0
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v8, v0
	ldp	d1, d0, [x19, #96]
	fcvt	s10, d0
	str	s10, [sp, #40]
	fcvt	s0, d1
	fmul	s1, s0, s12
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s10
	str	s0, [sp, #44]
	str	s8, [sp, #36]
	fadd	s0, s8, s0
	fmov	s1, #1.00000000
	fmadd	s0, s8, s0, s1
	fdiv	s14, s1, s0
	fmadd	s0, s8, s8, s13
	fadd	s0, s0, s0
	str	s0, [sp, #140]
	ldr	d0, [x19, #112]
	fcvt	s0, d0
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v8, v0
	ldp	d1, d0, [x19, #120]
	fcvt	s10, d0
	str	s10, [sp, #52]
	fcvt	s0, d1
	fmul	s1, s0, s12
	mov.16b	v11, v12
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s10
	str	s0, [sp, #56]
	mov.16b	v1, v8
	str	s8, [sp, #48]
	fadd	s0, s8, s0
	fmov	s2, #1.00000000
	fmadd	s0, s8, s0, s2
	fdiv	s13, s2, s0
	fmov	s8, #-1.00000000
	fmadd	s0, s1, s1, s8
	fadd	s0, s0, s0
	str	s0, [sp, #136]
	ldr	d0, [x19, #136]
	fcvt	s0, d0
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v10, v0
	ldp	d1, d0, [x19, #144]
	fcvt	s12, d0
	str	s12, [sp, #64]
	fcvt	s0, d1
	fmul	s1, s0, s11
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s12
	str	s0, [sp, #68]
	str	s10, [sp, #60]
	fadd	s0, s10, s0
	fmov	s1, #1.00000000
	fmadd	s0, s10, s0, s1
	fdiv	s15, s1, s0
	fmadd	s0, s10, s10, s8
	fadd	s0, s0, s0
	str	s0, [sp, #132]
	ldr	d0, [x19, #160]
	fcvt	s0, d0
	fmul	s0, s9, s0
	str	s9, [sp, #116]
	bl	_tanf
	mov.16b	v8, v0
	ldp	d1, d0, [x19, #168]
	fcvt	s12, d0
	str	s12, [sp, #76]
	fcvt	s0, d1
	mov.16b	v10, v11
	fmul	s1, s0, s11
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s12
	str	s0, [sp, #80]
	mov.16b	v1, v8
	str	s8, [sp, #72]
	fadd	s0, s8, s0
	fmov	s2, #1.00000000
	fmadd	s0, s8, s0, s2
	fdiv	s8, s2, s0
	fmov	s0, #-1.00000000
	fmadd	s0, s1, s1, s0
	fadd	s0, s0, s0
	str	s0, [sp, #128]
	ldr	d0, [x19, #184]
	fcvt	s0, d0
	fmul	s0, s9, s0
	bl	_tanf
	mov.16b	v12, v0
	ldp	d1, d0, [x19, #192]
	fcvt	s11, d0
	str	s11, [sp, #88]
	fcvt	s0, d1
	fmul	s1, s0, s10
	mov.16b	v9, v10
	str	s10, [sp, #112]
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s11
	str	s0, [sp, #92]
	str	s12, [sp, #84]
	fadd	s0, s12, s0
	fmov	s1, #1.00000000
	fmadd	s0, s12, s0, s1
	fdiv	s10, s1, s0
	fmov	s0, #-1.00000000
	fmadd	s0, s12, s12, s0
	fadd	s0, s0, s0
	str	s0, [sp, #124]
	ldr	d0, [x19, #208]
	fcvt	s0, d0
	ldr	s1, [sp, #116]
	fmul	s0, s1, s0
	bl	_tanf
	mov.16b	v11, v0
	ldp	d1, d0, [x19, #216]
	fcvt	s12, d0
	str	s12, [sp, #100]
	fcvt	s0, d1
	fmul	s1, s0, s9
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	fdiv	s0, s0, s12
	str	s0, [sp, #104]
	str	s11, [sp, #96]
	fadd	s0, s11, s0
	fmov	s1, #1.00000000
	fmadd	s0, s11, s0, s1
	fdiv	s12, s1, s0
	fmov	s0, #-1.00000000
	fmadd	s0, s11, s11, s0
	fadd	s0, s0, s0
	str	s0, [sp, #120]
	ldr	d0, [x19, #232]
	fcvt	s0, d0
	ldr	s1, [sp, #116]
	fmul	s0, s1, s0
	bl	_tanf
	mov.16b	v9, v0
	ldp	d1, d0, [x19, #240]
	fcvt	s11, d0
	fcvt	s0, d1
	ldr	s1, [sp, #112]
	fmul	s1, s0, s1
	fmov	s0, #10.00000000
	bl	"_std::math::math::pow[::Powable]($0,$0),T=[typevalue<#kgen.instref<\"std::builtin::simd::SIMD,dtype=f32,size=1\">>, scalar<f32>]"
	mov	x8, #0
	fdiv	s0, s0, s11
	fadd	s1, s9, s0
	fmov	s16, #1.00000000
	fmadd	s5, s9, s1, s16
	fmov	s1, #-1.00000000
	fmadd	s6, s9, s9, s1
	fsub	s0, s9, s0
	fmadd	s2, s9, s0, s16
	fdiv	s0, s16, s11
	fadd	s1, s9, s0
	fmadd	s1, s9, s1, s16
	stp	s1, s2, [sp, #112]
	fsub	s0, s0, s9
	fmsub	s1, s9, s0, s16
	ldr	s2, [sp, #96]
	ldr	s0, [sp, #104]
	fsub	s0, s2, s0
	fmadd	s0, s2, s0, s16
	stp	s0, s1, [sp, #104]
	ldr	s0, [sp, #100]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	fsub	s0, s0, s2
	fmsub	s0, s2, s0, s16
	stp	s0, s1, [sp, #96]
	ldr	s2, [sp, #84]
	ldr	s0, [sp, #92]
	fsub	s0, s2, s0
	fmadd	s3, s2, s0, s16
	ldr	s0, [sp, #88]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	stp	s1, s3, [sp, #88]
	fsub	s0, s0, s2
	fmsub	s1, s2, s0, s16
	ldr	s2, [sp, #72]
	ldr	s0, [sp, #80]
	fsub	s0, s2, s0
	fmadd	s0, s2, s0, s16
	stp	s0, s1, [sp, #80]
	ldr	s0, [sp, #76]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	fsub	s0, s0, s2
	fmsub	s0, s2, s0, s16
	stp	s0, s1, [sp, #72]
	ldr	s2, [sp, #60]
	ldr	s0, [sp, #68]
	fsub	s0, s2, s0
	fmadd	s3, s2, s0, s16
	ldr	s0, [sp, #64]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	stp	s1, s3, [sp, #64]
	fsub	s0, s0, s2
	fmsub	s1, s2, s0, s16
	ldr	s2, [sp, #48]
	ldr	s0, [sp, #56]
	fsub	s0, s2, s0
	fmadd	s0, s2, s0, s16
	stp	s0, s1, [sp, #56]
	ldr	s0, [sp, #52]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	fsub	s0, s0, s2
	fmsub	s0, s2, s0, s16
	stp	s0, s1, [sp, #48]
	ldr	s2, [sp, #36]
	ldr	s0, [sp, #44]
	fsub	s0, s2, s0
	fmadd	s3, s2, s0, s16
	ldr	s0, [sp, #40]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	stp	s1, s3, [sp, #40]
	fsub	s0, s0, s2
	fmsub	s1, s2, s0, s16
	ldr	s2, [sp, #24]
	ldr	s0, [sp, #32]
	fsub	s0, s2, s0
	fmadd	s0, s2, s0, s16
	stp	s0, s1, [sp, #32]
	ldr	s0, [sp, #28]
	fdiv	s0, s16, s0
	fadd	s1, s2, s0
	fmadd	s1, s2, s1, s16
	fsub	s0, s0, s2
	fmsub	s0, s2, s0, s16
	stp	s0, s1, [sp, #24]
	ldp	s2, s0, [sp]
	fsub	s0, s2, s0
	fmadd	s9, s2, s0, s16
	ldp	s0, s7, [sp, #8]
	fdiv	s1, s16, s0
	fadd	s0, s2, s1
	fmadd	s0, s2, s0, s16
	fsub	s1, s1, s2
	fmsub	s1, s2, s1, s16
	ldp	s2, s3, [sp, #16]
	fsub	s2, s7, s2
	fmadd	s2, s7, s2, s16
	fdiv	s4, s16, s3
	fadd	s3, s7, s4
	fmadd	s3, s7, s3, s16
	fsub	s4, s4, s7
	fmsub	s4, s7, s4, s16
	fdiv	s5, s16, s5
	fadd	s6, s6, s6
	ldr	s29, [x19, #260]
	ldr	s22, [x19, #264]
	ldr	s27, [x19, #272]
	ldr	s21, [x19, #276]
	ldr	s28, [x19, #284]
	ldr	s20, [x19, #288]
	ldr	s26, [x19, #296]
	ldr	s19, [x19, #300]
	ldr	s25, [x19, #308]
	ldr	s18, [x19, #312]
	ldr	s24, [x19, #320]
	ldr	s17, [x19, #324]
	ldr	s23, [x19, #332]
	ldr	s16, [x19, #336]
	ldr	s11, [x19, #344]
	ldr	s7, [x19, #348]
LBB0_1:
	ldr	d30, [x21, x8]
	fmul	s29, s6, s29
	fcvt	s30, d30
	ldr	s31, [sp, #116]
	fmadd	s31, s31, s22, s29
	fmsub	s30, s5, s31, s30
	str	s30, [x19, #256]
	ldr	s31, [sp, #112]
	fmadd	s29, s31, s30, s29
	ldr	s30, [sp, #120]
	fmul	s27, s30, s27
	ldr	s30, [sp, #108]
	fmadd	s22, s30, s22, s29
	ldr	s29, [sp, #104]
	fmadd	s29, s29, s21, s27
	fmul	s29, s12, s29
	fnmsub	s22, s5, s22, s29
	str	s22, [x19, #268]
	ldr	s29, [sp, #124]
	fmul	s28, s29, s28
	ldr	s29, [sp, #100]
	fmadd	s22, s29, s22, s27
	ldr	s27, [sp, #96]
	fmadd	s21, s27, s21, s22
	ldr	s22, [sp, #92]
	fmadd	s22, s22, s20, s28
	fmul	s22, s10, s22
	fnmsub	s21, s12, s21, s22
	str	s21, [x19, #280]
	ldr	s22, [sp, #128]
	fmul	s22, s22, s26
	ldp	s26, s27, [sp, #84]
	fmadd	s21, s27, s21, s28
	fmadd	s20, s26, s20, s21
	ldr	s21, [sp, #80]
	fmadd	s21, s21, s19, s22
	fmul	s21, s8, s21
	fnmsub	s20, s10, s20, s21
	str	s20, [x19, #292]
	ldr	s21, [sp, #132]
	fmul	s21, s21, s25
	ldr	s25, [sp, #76]
	fmadd	s20, s25, s20, s22
	ldr	s22, [sp, #72]
	fmadd	s19, s22, s19, s20
	ldp	s22, s20, [sp, #64]
	fmadd	s20, s20, s18, s21
	fmul	s20, s15, s20
	fnmsub	s19, s8, s19, s20
	str	s19, [x19, #304]
	ldr	s20, [sp, #136]
	fmul	s20, s20, s24
	fmadd	s19, s22, s19, s21
	ldr	s21, [sp, #60]
	fmadd	s18, s21, s18, s19
	ldp	s21, s19, [sp, #52]
	fmadd	s19, s19, s17, s20
	fmul	s19, s13, s19
	fnmsub	s18, s15, s18, s19
	str	s18, [x19, #316]
	ldr	s19, [sp, #140]
	fmul	s19, s19, s23
	fmadd	s18, s21, s18, s20
	ldr	s20, [sp, #48]
	fmadd	s17, s20, s17, s18
	ldp	s20, s18, [sp, #40]
	fmadd	s18, s18, s16, s19
	fmul	s18, s14, s18
	fnmsub	s17, s13, s17, s18
	str	s17, [x19, #328]
	ldp	s18, s21, [sp, #144]
	fmul	s18, s18, s11
	fmadd	s17, s20, s17, s19
	ldr	s19, [sp, #36]
	fmadd	s16, s19, s16, s17
	ldr	s17, [sp, #32]
	fmadd	s17, s17, s7, s18
	fmul	s17, s21, s17
	fnmsub	s16, s14, s16, s17
	str	s16, [x19, #340]
	ldr	s17, [x19, #356]
	ldp	s19, s20, [sp, #152]
	fmul	s17, s19, s17
	ldr	s19, [sp, #28]
	fmadd	s16, s19, s16, s18
	ldr	s18, [sp, #24]
	fmadd	s7, s18, s7, s16
	ldr	s16, [x19, #360]
	fmadd	s18, s9, s16, s17
	fmul	s18, s20, s18
	fnmsub	s7, s21, s7, s18
	str	s7, [x19, #352]
	ldr	s18, [x19, #368]
	ldp	s21, s19, [sp, #160]
	fmul	s18, s21, s18
	fmadd	s7, s0, s7, s17
	fmadd	s7, s1, s16, s7
	ldr	s16, [x19, #372]
	fmadd	s17, s2, s16, s18
	fmul	s17, s19, s17
	fnmsub	s7, s20, s7, s17
	str	s7, [x19, #364]
	fmadd	s7, s3, s7, s18
	fmadd	s7, s4, s16, s7
	fmul	s7, s19, s7
	fcvt	d7, s7
	str	d7, [x22, x8]
	ldr	s22, [x19, #260]
	ldr	d29, [x19, #256]
	str	d29, [x20]
	ldr	s21, [x19, #272]
	ldr	d27, [x20, #8]
	str	d27, [x19, #272]
	ldr	s20, [x19, #284]
	ldr	d28, [x19, #280]
	str	d28, [x20, #24]
	ldr	s19, [x19, #296]
	ldr	d26, [x20, #32]
	str	d26, [x19, #296]
	ldr	s18, [x19, #308]
	ldr	d25, [x19, #304]
	str	d25, [x20, #48]
	ldr	s17, [x19, #320]
	ldr	d24, [x20, #56]
	str	d24, [x19, #320]
	ldr	s16, [x19, #332]
	ldr	d23, [x19, #328]
	str	d23, [x20, #72]
	ldr	s7, [x19, #344]
	ldr	d30, [x19, #352]
	str	d30, [x20, #96]
	ldr	d30, [x20, #104]
	str	d30, [x19, #368]
	ldr	d11, [x20, #80]
	str	d11, [x19, #344]
	add	x8, x8, #8
	cmp	x8, #512
	b.ne	LBB0_1
	;MEMBARRIER
	ldp	x29, x30, [sp, #288]
	ldp	x20, x19, [sp, #272]
	ldp	x22, x21, [sp, #256]
	ldp	x28, x27, [sp, #240]
	ldp	d9, d8, [sp, #224]
	ldp	d11, d10, [sp, #208]
	ldp	d13, d12, [sp, #192]
	ldp	d15, d14, [sp, #176]
	add	sp, sp, #304
	ret


