#if	!defined(INTRINSIC)

#define REALNAME	ASMNAME
#define PROLOGUE \
	.text; \
	.globl REALNAME;\
	.type REALNAME, %function;\
REALNAME:;

#define EPILOGUE \
	.size REALNAME, .-REALNAME;

#define REGISTERSAVE \
	sub 	sp, sp, #STACKSIZE;\
    str     r4,  [sp, #0];\
	str		r5,  [sp, #4];\
	str		r6,  [sp, #8];\
	str		r7,  [sp, #12];\
	str		r8,  [sp, #16];\
    str 	r9,	 [sp, #20];\
	str		r10, [sp, #24];\
	str 	r11, [sp, #28];\

#define REGISTERREVERT\
	ldr     r4,  [sp, #0];\
	ldr		r5,  [sp, #4];\
	ldr		r6,  [sp, #8];\
	ldr		r7,  [sp, #12];\
	ldr		r8,  [sp, #16];\
    ldr 	r9,	 [sp, #20];\
	ldr		r10, [sp, #24];\
	ldr 	r11, [sp, #28];\
	add    sp, sp, #STACKSIZE;\
	bx lr;


// 13 GENERAL REGISTERS SUPPORTED BY ARM
// r0-r3 ARE USED TO PASS PARAMETERS
#define	ireg0	r0
#define ireg1	r1
#define ireg2	r2
#define ireg3	r3
#define ireg4	r4
#define ireg5	r5
#define ireg6	r6
#define ireg7	r7
#define ireg8	r8
#define ireg9	r9
#define ireg10	r10
#define ireg11	r11
#define ireg12	r12
#if defined(GEMM)
#define ireg13	r1  
#endif
#define SPREG	sp

// ASM INSTRUCTIONS
#define STACKLDI(a, b, c)		ldr c, [sp,  b]
#define STACKSTI(a, b, c)		str c, [sp,  b]
#define SHLI(a, b, c)			lsl c, a, b
#define SHRI(a, b, c)			asr c, a, b
#define MOVI(a, b)				mov b, a
#define ADDI(a, b, c)			add c, a, b
#define ADDSHLI(a, b, c, d)		add d, a, b, asl c
#define SUBI(a, b, c)			sub c, a, b
#define SUBSHLI(a, b, c, d)	  	sub d, a, b, asl c
#define MLSI(a, b, c, d)		mls d, a, b, c
#define CMPI(x, y)				cmp x, y
#define JLEI(x)					ble x
#define JLTI(x)					blt x
#define JEI(x)					beq x
#define JGTI(x)					bgt x
#define JGEI(x)					bge x
#define TESTI(a, b)				and a, b

// 128-BIT REGISTERS
#define _4_reg0		q8
#define _4_reg1		q9
#define _4_reg2		q10
#define _4_reg3		q11
#define _4_reg4		q12
#define _4_reg5		q13
#define _4_reg6		q14
#define _4_reg7		q15
#define _4_reg8		q0
#define _4_reg9		q1
#define _4_reg10	q2
#define _4_reg11	q3
#define _4_reg12	q4
#define _4_reg13	q5
#define _4_reg14	q6
#define _4_reg15	q7

// 64-BIT REGISTERS(32 qi=>(d2i, d2i+1))
#define _2_reg0		d16
#define _2_reg1		d17
#define _2_reg2		d18
#define _2_reg3		d19
#define _2_reg4		d20
#define _2_reg5		d21
#define _2_reg6		d22
#define _2_reg7		d23
#define _2_reg8		d24
#define _2_reg9		d25
#define _2_reg10	d26
#define _2_reg11	d27
#define _2_reg12	d28
#define _2_reg13	d29
#define _2_reg14	d30
#define _2_reg15	d31
#define _2_reg16	d0
#define _2_reg17	d1
#define _2_reg18	d2
#define _2_reg19	d3
#define _2_reg20	d4
#define _2_reg21	d5
#define _2_reg22	d6
#define _2_reg23	d7
#define _2_reg24	d8
#define _2_reg25	d9
#define _2_reg26	d10
#define _2_reg27	d11
#define _2_reg28	d12
#define _2_reg29	d13
#define _2_reg30	d14
#define _2_reg31	d15

//32-bit REGISTERS(64)
#define _1_reg0		s32
#define _1_reg1		s33
#define _1_reg2		s34
#define _1_reg3		s35
#define _1_reg4		s36
#define _1_reg5		s37
#define _1_reg6		s38
#define _1_reg7		s39
#define _1_reg8		s40
#define _1_reg9		s41
#define _1_reg10	s42
#define _1_reg11	s43
#define _1_reg12	s44
#define _1_reg13	s45
#define _1_reg14	s46
#define _1_reg15	s47
#define _1_reg16	s48
#define _1_reg17	s40
#define _1_reg18	s50
#define _1_reg19	s51
#define _1_reg20	s52
#define _1_reg21	s53
#define _1_reg22	s54
#define _1_reg23	s55
#define _1_reg24	s56
#define _1_reg25	s57
#define _1_reg26	s58
#define _1_reg27	s59
#define _1_reg28	s60
#define _1_reg29	s61
#define _1_reg30	s62
#define _1_reg31	s63
#define _1_reg32	s0
#define _1_reg33	s1
#define _1_reg34	s2
#define _1_reg35	s3
#define _1_reg36	s4
#define _1_reg37	s5
#define _1_reg38	s6
#define _1_reg39	s7
#define _1_reg40	s8
#define _1_reg41	s9
#define _1_reg42	s10
#define _1_reg43	s11
#define _1_reg44	s12
#define _1_reg45	s13
#define _1_reg46	s14
#define _1_reg47	s15
#define _1_reg48	s16
#define _1_reg49	s17
#define _1_reg50	s18
#define _1_reg51	s19
#define _1_reg52	s20
#define _1_reg53	s21
#define _1_reg54	s22
#define _1_reg55	s23
#define _1_reg56	s24
#define _1_reg57	s25
#define _1_reg58	s26
#define _1_reg59	s27
#define _1_reg60	s28
#define _1_reg61	s29
#define _1_reg62	s30
#define _1_reg63	s31

#if	defined(DOUBLE)
#else	/*IF !DEFINED(DOUBLE)*/
#define MASKIMM0	0
#define MASKIMM1	1
#define MASKIMM2	0
#define MASKIMM3	1
#define VLDE4x(a, b, c1, c2)	vld1.f32 {c1[], c2[]}, [a] !
#define VXOR4(a, b, c)			veor.f32 c, a, b 
//#define VXOR1(a, b, c)			eor c, a, b 
#if defined (GEMM)
#define VLD4(a, b, c)			vld1.f32 {c}, [a:128] !
#define VLDU4(a, b, c)			vld1.f32 {c}, [a] ! 
#define VLDU2(a, b, c)			vld1.f32 {c}, [a] !
#define VLD1(a, b, c)			flds c, [a, b]
#else 
#define VLD4(a, b, c)			vld1.f32 {c}, [a] !
#define VLDU4(a, b, c)			vld1.f32 {c}, [a] 
#endif
#define VLD1(a, b, c)			flds c, [a, b]
#define VLDU4x(a, b, c)			vld1.f32 {c}, [a]  
#define VFMAmask4(a, b, c, d) 	vmla.f32 c, a, b[d]
#define VFMAmask2(a, b, c, d) 	vmla.f32 c, a, b[d]
#define VFMA4(a, b, c, d)		vmla.f32 c, a, b
#define VFMA1(a, b, c, d)		fmacs c, a, b
#define VMUL4(a, b, c)			vmul.f32 c, a, b
#define VMUL1(a, b, c)			fmuls c, a, b
#define VADD4(a, b, c)			vadd.f32 c, a, b
#define VADD2(a, b, c)			vadd.f32 c, a, b
#define VADD1(a, b, c)			fadds c, a, b
#define VST4(a, b, c)			vst1.f32 {c}, [a] !
#define VST2(a, b, c)			vst1.f32 {c}, [a] !
#define VST1(a, b, c)			fsts c, [a, b]
#endif	/*IF DEFINED(DOUBLE)*/

#else	/*IF DEFINED(INTRINSIC)*/

#include <arm_neon.h>
typedef FLOAT REGTYPE_1;
#if	defined(DOUBLE)
#else	/*IF !DEFINED(DOUBLE)*/
#define REGTYPE_4 				float32x4_t
#define VXOR(a, b, c)			c = vdupq_n_f32(0.0)
#define VLD4(a, b, c)			c = vld1q_f32(a+b)
#define VST4(a, b, c)			vst1q_f32(a+b, c)
#define VLDE4(a, b, c)  		c = vld1q_dup_f32(a+b)
#define VMUL4(a, b, c)			c = vmulq_f32(a, b)
#define VADD4(a, b, c)			c = vaddq_f32(a, b)
#define VFMA4(a, b, c)  		c = vmlaq_f32(c, a, b)
#endif /*IF DEFINED(DOUBLE)*/

#endif /*IF !DEFINED(INTRINSIC)*/
